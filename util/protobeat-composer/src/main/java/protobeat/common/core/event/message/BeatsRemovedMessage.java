package protobeat.common.core.event.message;

import protobeat.common.core.model.Beat;

import java.util.ArrayList;

public class BeatsRemovedMessage extends BeatsChangedMessage {
	public BeatsRemovedMessage() {
	}

	public BeatsRemovedMessage(ArrayList<Beat> removedBeats) {
		super(removedBeats);
	}
}
