package protobeat.common.core.event.message;

import lombok.Data;

import java.io.File;

@Data
public class SetAudioFileEventMessage implements EventMessage {
	private File audioFile;

	public SetAudioFileEventMessage(File audioFile) {
		this.audioFile = audioFile;
	}
}
