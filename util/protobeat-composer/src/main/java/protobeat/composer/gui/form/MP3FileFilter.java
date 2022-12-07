package protobeat.composer.gui.form;

import javax.swing.filechooser.FileFilter;
import java.io.File;

public class MP3FileFilter extends FileFilter {
	@Override
	public boolean accept(File file) {
		if (file.isDirectory()) {
			return true;
		}
		return file.getName().toLowerCase().endsWith(".mp3");
	}

	@Override
	public String getDescription() {
		return "MP3 File";
	}
}
