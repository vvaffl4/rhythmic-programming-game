package protobeat.composer.gui.component.inputrecorder;

import protobeat.common.core.Keymapping;
import protobeat.common.core.ServiceManager;
import protobeat.common.core.context.AudioFilePropertiesAdapter;
import protobeat.common.core.context.ContextHolder;
import protobeat.common.core.context.ProtobeatContext;
import protobeat.common.core.event.EventListener;
import protobeat.common.core.event.message.*;
import protobeat.common.core.model.Beat;
import protobeat.common.core.pbenum.TransportControlType;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.HashMap;

import static protobeat.common.constant.ProtobeatCommonConstants.CONST_LANE_LEFT;
import static protobeat.common.constant.ProtobeatCommonConstants.CONST_LANE_RIGHT;

public class InputRecorderComponent extends JPanel {
	private final ProtobeatContext context;
	private final ServiceManager serviceManager;
	private boolean recording = false;

	private HashMap<Character, LaneTrackerItem> laneTracker = new HashMap<>();
	private PlayerPositionChangedMessage positionMessage;

	public InputRecorderComponent() {
		this.context = ContextHolder.getInstance().getContext();
		this.serviceManager = context.getServiceManager();

		setMinimumSize(new Dimension(200, 50));
		setBackground(Color.pink);

		serviceManager.bus().addListener(new EventListener<EventMessage>() {
			@Override
			public void onMessage(EventMessage message) {
				if (message instanceof AudioTransportMessage) {
					onAudioTransportMessage((AudioTransportMessage) message);
				}

				if (message instanceof PlayerPositionChangedMessage) {
					onPlayerPositionChanged((PlayerPositionChangedMessage) message);
				}
			}
		});

		addKeyListener(new KeyAdapter() {
			Keymapping keymapping = context.getKeymapping();

			@Override
			public void keyPressed(KeyEvent keyEvent) {
				if (!recording) return;

				if (keyEvent.getKeyCode() == keymapping.getLeftLaneTrigger()) {
					onLaneDown(CONST_LANE_LEFT);
				} else if (keyEvent.getKeyCode() == keymapping.getRightLaneTrigger()) {
					onLaneDown(CONST_LANE_RIGHT);
				}
			}

			@Override
			public void keyReleased(KeyEvent keyEvent) {
				if (keyEvent.getKeyCode() == keymapping.getLeftLaneTrigger()) {
					onLaneUp(CONST_LANE_LEFT);
				} else if (keyEvent.getKeyCode() == keymapping.getRightLaneTrigger()) {
					onLaneUp(CONST_LANE_RIGHT);
				}
			}
		});
	}

	private void onPlayerPositionChanged(PlayerPositionChangedMessage message) {
		this.positionMessage = message;
		if (recording) setRecording(recording);
	}

	private void onLaneUp(char lane) {
		if (!laneTracker.containsKey(lane)) return;

		LaneTrackerItem trackerItem = laneTracker.get(lane);
		laneTracker.remove(lane);
		if (positionMessage == null) return;

		final AudioFilePropertiesAdapter adapter = context.getCurrentFilePropertiesAdapter();
		float now = positionMessage.getScalarPosition() * adapter.durationInMs();

		Beat beat = new Beat();
		beat.setPosition(trackerItem.getStart());
		beat.setDuration(trackerItem.delta(now));
		beat.setLane(lane);

		context.getLevel().getBeats().add(beat);
		serviceManager.bus().emit(new BeatAddedMessage());
	}

	private void onLaneDown(char lane) {
		if (laneTracker.containsKey(lane)) return;

		final AudioFilePropertiesAdapter adapter = context.getCurrentFilePropertiesAdapter();
		LaneTrackerItem trackerItem = new LaneTrackerItem(positionMessage.getScalarPosition() * adapter.durationInMs());
		laneTracker.put(lane, trackerItem);
	}

	private void onAudioTransportMessage(AudioTransportMessage message) {
		switch (message.getTransportControlType()) {
			case RECORD:
				if(context.getLevel().getBpm() == 0) {
					System.out.println("You forgot to enter a BPM!");
					setRecording(false);
					setBackground(Color.blue);

					Thread thread = new Thread(() -> {
						try {
							Thread.sleep(100);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
						serviceManager.bus().emit(new AudioTransportMessage(TransportControlType.PAUSE));
						AudioTransportMessage seekMessage = new AudioTransportMessage(TransportControlType.SEEK);
						seekMessage.setTransportSeek(0);
						serviceManager.bus().emit(seekMessage);
					});

					thread.start();
				}
				else {
					setRecording(true);
					setBackground(Color.orange);
				}
				break;
			case PAUSE:
			case STOP:
				setRecording(false);
				setBackground(Color.red);
				break;
			default:
				setBackground(Color.pink);
				break;
		}
	}

	private void setRecording(boolean b) {
		requestFocus(b);
		boolean update = b != recording;
		this.recording = b;

		if (update) {
			serviceManager.bus().emit(new InputRecorderStateChangedMessage(recording));
		}
	}
}
