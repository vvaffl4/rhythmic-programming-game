package protobeat.composer.util;

import java.io.File;

public class FileUtil {
	public static File makeSureEndsWith(File file, String end) {
		String absolutePath = file.getAbsolutePath();
		if (!absolutePath.toLowerCase().endsWith(end.toLowerCase())) {
			absolutePath += end;
			return new File(absolutePath);
		}

		return file;
	}
}
