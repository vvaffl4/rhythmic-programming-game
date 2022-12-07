package protobeat.common.core.event.message;

import protobeat.common.core.audio.BufferedPlayer;
import lombok.Data;

@Data
public class PlayerBufferStateChangedMessage implements EventMessage {
	private final BufferedPlayer player;
	private final boolean buffering;

	public PlayerBufferStateChangedMessage(BufferedPlayer player, boolean buffering) {
		this.player = player;
		this.buffering = buffering;
	}
}
