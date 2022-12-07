package protobeat.common.core.audio;

import javazoom.jl.decoder.*;
import javazoom.jl.player.AudioDevice;
import javazoom.jl.player.FactoryRegistry;
import protobeat.common.core.FailBucket;

import java.io.InputStream;

public class BufferedPlayer {
	private final Bitstream bitstream;
	private AudioDevice audio;
	private final Decoder decoder = new Decoder();

	private boolean buffering = false;
	private AudioTrack audioTrack = new AudioTrack();

	private BufferStateChangedListener bufferStateChangedListener;

	public BufferedPlayer(InputStream stream) throws JavaLayerException {
		this(stream, null);
	}

	public BufferedPlayer(InputStream stream, AudioDevice device) throws JavaLayerException {
		this.bitstream = new Bitstream(stream);
		if (device == null) {
			this.audio = FactoryRegistry.systemRegistry().createAudioDevice();
		} else {
			this.audio = device;
		}

		this.audio.open(this.decoder);
	}

	private void setBuffering(boolean b) {
		this.buffering = b;
		if (bufferStateChangedListener != null) {
			bufferStateChangedListener.onBufferStateChanged(b);
		}
	}

	private void bufferFrames() {
		audioTrack = new AudioTrack();
		setBuffering(true);

		while (true) {
			try {
				Header header = bitstream.readFrame();
				if (header == null) break;

				SampleBuffer sampleBuffer = (SampleBuffer) decoder.decodeFrame(header, bitstream);
				AudioFrame frame = new AudioFrame(sampleBuffer);
				audioTrack.add(frame);
				bitstream.closeFrame();
			} catch (BitstreamException e) {
				break;
			} catch (DecoderException e) {
				e.printStackTrace();
			}
		}

		setBuffering(false);
	}

	public boolean play(int nFrames) throws JavaLayerException {
		if (buffering) {
			while (buffering) {
				System.out.println("Waiting for buffering");
			}
		}

		for (int i = 0; i < nFrames; i++) {
			final AudioFrame frame = audioTrack.next();
			synchronized (this) {
				if (audio != null) {
					frame.writeTo(audio);
				}
			}
		}

		return true;
	}


	public long getPosition() {
		return audioTrack.getCurrentFrame();
	}

	public void close() {
		if (audio != null) {
			audio.close();
			audio = null;

			try {
				bitstream.close();
			} catch (BitstreamException e) {
				FailBucket.accept(e);
			}
		}
	}

	public void seek(long transportSeek) {
		audioTrack.setCurrentFrame(transportSeek);
	}

	public AudioTrack getAudioTrack() {
		return audioTrack;
	}

	public BufferStateChangedListener getBufferStateChangedListener() {
		return bufferStateChangedListener;
	}

	public void setBufferStateChangedListener(BufferStateChangedListener bufferStateChangedListener) {
		this.bufferStateChangedListener = bufferStateChangedListener;
	}

	public void buffer() {
		Thread thread = new Thread(this::bufferFrames);
		thread.start();
	}
}
