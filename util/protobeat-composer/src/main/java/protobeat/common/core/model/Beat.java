package protobeat.common.core.model;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.databind.annotation.JsonSerialize;
import lombok.Data;

import static protobeat.common.constant.ProtobeatCommonConstants.CONST_LANE_LEFT;

@Data
@JsonSerialize
public class Beat {
	@JsonProperty("position")
	private float position = 0f;
	@JsonProperty("duration")
	private float duration = 1f;
	@JsonProperty("lane")
	private char lane = CONST_LANE_LEFT;

	@JsonIgnore
	private boolean selected = false;
	@JsonIgnore
	private boolean hover = false;
}
