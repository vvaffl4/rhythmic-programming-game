package protobeat.common.core.event.message;

import lombok.Data;

@Data
public class PlayerPositionChangedMessage implements EventMessage {
	private final long position;
	private final int trackLength;
	private final float scalarPosition;

	public PlayerPositionChangedMessage(long position, int trackLength) {
		this.position = position;
		this.trackLength = trackLength;
		this.scalarPosition = (float) position / (float) trackLength;
	}
}
