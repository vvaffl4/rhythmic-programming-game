package protobeat.common.core.context;

import com.fasterxml.jackson.core.util.DefaultPrettyPrinter;
import com.fasterxml.jackson.databind.ObjectMapper;
import lombok.Data;
import protobeat.common.core.Keymapping;
import protobeat.common.core.ServiceManager;
import protobeat.common.core.model.Beat;
import protobeat.common.core.model.Level;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static protobeat.common.constant.ComposerContants.PIXELS_PER_SECOND;

@Data
public class ProtobeatContext {
	private ServiceManager serviceManager = new ServiceManager();
	private Keymapping keymapping = new Keymapping();
	private Map<String, Object> currentFileProperties;
	private File currentAudioFile;
	private final ObjectMapper objectMapper = new ObjectMapper();
	private AudioFilePropertiesAdapter currentFilePropertiesAdapter = new AudioFilePropertiesAdapter(new HashMap<>());
	private Level level = new Level();
	private int pixelsPerSecond = PIXELS_PER_SECOND;

	public ProtobeatContext() {
		objectMapper.setDefaultPrettyPrinter(new DefaultPrettyPrinter());
	}

	public String currentAudioFileName() {
		return currentAudioFile.getName();
	}

	public void setCurrentFileProperties(Map<String, Object> properties) {
		this.currentFileProperties = properties;
		this.currentFilePropertiesAdapter = new AudioFilePropertiesAdapter(properties);
	}

	public AudioFilePropertiesAdapter adapter() {
		return currentFilePropertiesAdapter;
	}

	public void setCurrentAudioFile(File file) {
		currentAudioFile = file;
		level.setSongName(currentAudioFileName());
	}

	public List<Beat> getSelection() {
		ArrayList<Beat> selection = new ArrayList<>();
		level.getBeats().forEach(beat -> {
			if (beat.isSelected()) selection.add(beat);
		});

		return selection;
	}
}
