package protobeat.composer.gui.component.inputrecorder;

import lombok.Data;

@Data
public class LaneTrackerItem {
	private float start;

	public LaneTrackerItem(float start) {
		this.start = start;
	}

	public float delta(float now) {
		return now - start;
	}
}
