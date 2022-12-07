package protobeat.common.core.event.message;

import lombok.Data;

@Data
public class InputRecorderStateChangedMessage implements EventMessage {
	private final boolean recording;

	public InputRecorderStateChangedMessage(boolean recording) {
		this.recording = recording;
	}
}
