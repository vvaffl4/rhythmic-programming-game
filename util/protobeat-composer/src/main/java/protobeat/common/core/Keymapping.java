package protobeat.common.core;

import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.databind.annotation.JsonSerialize;
import lombok.Data;

import java.awt.event.KeyEvent;

@Data
@JsonSerialize
public class Keymapping {
	@JsonProperty
	private int leftLaneTrigger = KeyEvent.VK_Z;
	@JsonProperty
	private int rightLaneTrigger = KeyEvent.VK_PERIOD;
	@JsonProperty
	private int moveBeatRightTrigger = KeyEvent.VK_RIGHT;
	@JsonProperty
	private int moveBeatLeftTrigger = KeyEvent.VK_LEFT;
}
