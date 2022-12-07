package protobeat.common.core.event.message;

import protobeat.common.core.audio.PausablePlayer;
import lombok.Data;

@Data
public class AudioFileChangedMessage implements EventMessage {
	private final PausablePlayer player;

	public AudioFileChangedMessage(PausablePlayer player) {
		this.player = player;
	}
}
