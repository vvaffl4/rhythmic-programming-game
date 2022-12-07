package protobeat.composer.gui.form;

import javax.swing.filechooser.FileFilter;
import java.io.File;

public class JSONFileFilter extends FileFilter {
	@Override
	public boolean accept(File file) {
		return file.getAbsolutePath().endsWith(".json") || file.isDirectory();
	}

	@Override
	public String getDescription() {
		return "JSON File";
	}
}
