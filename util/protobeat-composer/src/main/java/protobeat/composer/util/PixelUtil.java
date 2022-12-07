package protobeat.composer.util;

import protobeat.common.core.context.AudioFilePropertiesAdapter;
import protobeat.common.core.context.ContextHolder;
import protobeat.common.core.model.Beat;

import java.awt.*;
import java.awt.image.BufferedImage;

import static protobeat.common.constant.ProtobeatCommonConstants.CONST_LANE_LEFT;
import static protobeat.common.constant.ProtobeatCommonConstants.CONST_LANE_RIGHT;
import static protobeat.common.constant.ComposerContants.STRIP_HEIGHT;

public class PixelUtil {
	public static Rectangle beatToScreen(Beat beat, BufferedImage image) {
		final AudioFilePropertiesAdapter adapter = ContextHolder.getInstance().getContext().getCurrentFilePropertiesAdapter();
		int beatLeftPosition = (int) ((beat.getPosition() / adapter.durationInMs()) * (float) image.getWidth());
		int beatWidth = (int) ((beat.getDuration() / adapter.durationInMs()) * (float) image.getWidth());

		int vertStart = 0;
		if (beat.getLane() == CONST_LANE_LEFT) {
			vertStart = STRIP_HEIGHT / 4;
		} else if (beat.getLane() == CONST_LANE_RIGHT) {
			vertStart = (STRIP_HEIGHT / 4) * 3;
		}
		vertStart -= 5;

		return new Rectangle(beatLeftPosition, vertStart, Math.max(10, beatWidth), 10);
	}
}
