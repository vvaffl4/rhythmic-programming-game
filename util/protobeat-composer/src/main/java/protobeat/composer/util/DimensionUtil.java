package protobeat.composer.util;

import java.awt.*;

public class DimensionUtil {
	public static Dimension add(Dimension left, int x, int y) {
		return new Dimension(left.width + x, left.height + y);
	}
}
