package protobeat.common.core.event.message;

import lombok.Data;
import protobeat.common.core.pbenum.TransportControlType;

@Data
public class AudioTransportMessage implements EventMessage {
	private final TransportControlType transportControlType;
	private long transportSeek = 0;

	public AudioTransportMessage(TransportControlType transportControlType) {
		this.transportControlType = transportControlType;
	}
}
