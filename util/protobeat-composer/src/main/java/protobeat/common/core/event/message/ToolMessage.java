package protobeat.common.core.event.message;

import lombok.Data;
import protobeat.common.core.pbenum.ComposerToolType;

@Data
public class ToolMessage implements EventMessage {
	private ComposerToolType toolType = ComposerToolType.NONE;

	public ToolMessage() {
	}

	public ToolMessage(ComposerToolType toolType) {
		this.toolType = toolType;
	}
}
