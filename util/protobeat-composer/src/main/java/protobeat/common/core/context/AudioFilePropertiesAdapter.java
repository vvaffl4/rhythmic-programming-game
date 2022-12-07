package protobeat.common.core.context;

import java.util.Map;

import static protobeat.common.constant.ProtobeatCommonConstants.*;

public class AudioFilePropertiesAdapter {
	private static final String DURATION = "duration";
	private final Map<String, Object> properties;

	public AudioFilePropertiesAdapter(Map<String, Object> properties) {

		this.properties = properties;
	}

	public long duration() {
		if (properties.containsKey(DURATION)) {
			return (long) properties.get(DURATION);
		}

		return -1;
	}

	public float durationInMs() {
		if (properties.containsKey(PROP_LENGTH_MS)) {
			return (float) properties.get(PROP_LENGTH_MS);
		}

		return -1f;
	}

	public float durationInSeconds() {
		if (properties.containsKey(PROP_LENGTH_SECONDS)) {
			return (float) properties.get(PROP_LENGTH_SECONDS);
		}

		return -1f;
	}

	public float durationInMinutes() {
		if (properties.containsKey(PROP_LENGTH_MIN)) {
			return (float) properties.get(PROP_LENGTH_MIN);
		}

		return -1f;
	}
}
