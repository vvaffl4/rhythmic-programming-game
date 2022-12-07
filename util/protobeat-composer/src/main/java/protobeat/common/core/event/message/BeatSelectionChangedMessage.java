package protobeat.common.core.event.message;

import lombok.Data;
import protobeat.common.core.model.Beat;

import java.util.ArrayList;

@Data
public class BeatSelectionChangedMessage implements EventMessage {
	private final ArrayList<Beat> changedBeats;

	public BeatSelectionChangedMessage(ArrayList<Beat> changedBeats) {
		this.changedBeats = changedBeats;
	}
}
