package protobeat.common.core.service;

import javazoom.jl.decoder.JavaLayerException;
import org.tritonus.share.sampled.file.TAudioFileFormat;
import protobeat.common.core.FailBucket;
import protobeat.common.core.Service;
import protobeat.common.core.ServiceManager;
import protobeat.common.core.audio.PausablePlayer;
import protobeat.common.core.event.EventListener;
import protobeat.common.core.event.message.*;

import javax.sound.sampled.AudioFileFormat;
import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.UnsupportedAudioFileException;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import static protobeat.common.constant.ProtobeatCommonConstants.*;

public class AudioService extends Service {
	private PausablePlayer player;

	public AudioService(ServiceManager serviceManager) {
		super(serviceManager);

		serviceManager.bus().addListener(new EventListener<EventMessage>() {
			@Override
			public void onMessage(EventMessage eventMessage) {
				if (eventMessage instanceof SetAudioFileEventMessage) {
					onSetAudioFileMessage((SetAudioFileEventMessage) eventMessage);
				} else if (eventMessage instanceof AudioTransportMessage) {
					onAudioTransportMessage((AudioTransportMessage) eventMessage);
				} else if (eventMessage instanceof BeforeShutdownMessage) {
					onBeforeShutdown();
				}
			}
		});
	}

	private void onBeforeShutdown() {
		killPlayer();
	}

	private void onAudioTransportMessage(AudioTransportMessage message) {
		switch (message.getTransportControlType()) {
			case PLAY:
				playAudio();
				break;
			case PAUSE:
				pauseAudio();
				break;
			case STOP:
				stopAudio();
				break;
			case SEEK:
				player.getInnerPlayer().seek(message.getTransportSeek());
				break;
		}
	}

	private void stopAudio() {
		if (player != null) {
			player.pause();
		}
	}

	private void pauseAudio() {
		if (player != null) {
			player.pause();
		}
	}

	private void playAudio() {
		if (player != null) {
			try {
				player.play();
			} catch (JavaLayerException e) {
				FailBucket.accept(e);
			}
		}
	}

	private void killPlayer() {
		if (player != null) {
			player.close();
			player = null;
		}
	}

	private void onSetAudioFileMessage(SetAudioFileEventMessage message) {
		killPlayer();

		try {
			final AudioFileFormat audioFileFormat = AudioSystem.getAudioFileFormat(message.getAudioFile());
			final AudioFormat format = audioFileFormat.getFormat();
			float length = (int) audioFileFormat.properties().get("mp3.length.frames") / (float) audioFileFormat.properties().get("mp3.framerate.fps");
			float lengthMinutes = length / 60f;

			final Map<String, Object> properties = new HashMap<>(audioFileFormat.properties());
			properties.put(PROP_LENGTH_SECONDS, length);
			properties.put(PROP_LENGTH_MS, length * 1000f);
			properties.put(PROP_LENGTH_MIN, lengthMinutes);

			if (audioFileFormat instanceof TAudioFileFormat) {
				context.setCurrentFileProperties(properties);
			}
		} catch (UnsupportedAudioFileException | IOException e) {
			FailBucket.accept(e);
		}

		try {
			FileInputStream fileInputStream = new FileInputStream(message.getAudioFile());
			context.setCurrentAudioFile(message.getAudioFile());
			player = new PausablePlayer(fileInputStream);
			player.getInnerPlayer().setBufferStateChangedListener(b -> serviceManager.bus().emit(new PlayerBufferStateChangedMessage(player.getInnerPlayer(), b)));
			player.getInnerPlayer().buffer();

			player.setPositionChangedListener(this::playerPositionChanged);

		} catch (FileNotFoundException | JavaLayerException e) {
			FailBucket.accept(e);
		}

		serviceManager.bus().emit(new AudioFileChangedMessage(player));
	}

	private void playerPositionChanged(long position) {
		serviceManager.bus().emit(new PlayerPositionChangedMessage(position, player.getInnerPlayer().getAudioTrack().length()));
	}
}
