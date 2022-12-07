package protobeat.common.core.audio;

import javazoom.jl.decoder.JavaLayerException;
import javazoom.jl.decoder.SampleBuffer;
import javazoom.jl.player.AudioDevice;

public class AudioFrame {
	private short[] buffer;

	public AudioFrame(SampleBuffer sampleBuffer) {
		this.buffer = new short[sampleBuffer.getBufferLength()];
		System.arraycopy(sampleBuffer.getBuffer(), 0, this.buffer, 0, sampleBuffer.getBufferLength());
	}

	public void writeTo(AudioDevice audio) throws JavaLayerException {
		audio.write(buffer, 0, buffer.length);
	}
}
