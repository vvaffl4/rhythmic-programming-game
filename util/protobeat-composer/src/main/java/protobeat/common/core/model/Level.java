package protobeat.common.core.model;

import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.databind.annotation.JsonSerialize;
import lombok.Data;

import java.util.ArrayList;
import java.util.List;

@Data
@JsonSerialize
public class Level {
	@JsonProperty("beats")
	private List<Beat> beats = new ArrayList<>();
	@JsonProperty("songName")
	private String songName;
	@JsonProperty("lengthMillis")
	private float lengthMillis;
	@JsonProperty("lengthSeconds")
	private float lengthSeconds;
	@JsonProperty("lengthMinutes")
	private float lengthMinutes;
	@JsonProperty("bpm")
	private int bpm;
}
