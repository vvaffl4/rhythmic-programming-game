package protobeat.common.core.event.message;

import lombok.Data;
import protobeat.common.core.model.Beat;

import java.util.ArrayList;
import java.util.List;

@Data
public class BeatsChangedMessage implements EventMessage {
	protected List<Beat> changedBeats = new ArrayList<>();

	public BeatsChangedMessage() {
	}

	public BeatsChangedMessage(List<Beat> beatList) {
		changedBeats = beatList;
	}
}
