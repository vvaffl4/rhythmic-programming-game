package protobeat.common.core.audio;

import java.util.ArrayList;

public class AudioTrack {
	private ArrayList<AudioFrame> frames = new ArrayList<>();
	private int currentFrame = 0;

	public void add(AudioFrame frame) {
		frames.add(frame);
	}

	public AudioFrame next() {
		if (currentFrame >= frames.size()) {
			currentFrame = 0;
		}
		AudioFrame frame = frames.get(currentFrame);
		currentFrame++;
		return frame;
	}

	public long getCurrentFrame() {
		return currentFrame;
	}

	public void setCurrentFrame(long currentFrame) {
		this.currentFrame = (int) currentFrame;
	}

	public int length() {
		return frames.size();
	}
}
