package protobeat.composer.gui.component.beatvisualiser;

import protobeat.common.core.ServiceManager;
import protobeat.common.core.context.AudioFilePropertiesAdapter;
import protobeat.common.core.context.ProtobeatContext;
import protobeat.common.core.event.message.PlayerPositionChangedMessage;
import protobeat.common.core.model.Beat;
import protobeat.composer.util.PixelUtil;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.util.ArrayList;

import static protobeat.common.constant.ComposerContants.*;

public class BeatVisualiserStripPainter {
	private final BeatVisualiserStrip parent;
	private final ProtobeatContext context;
	private final ServiceManager serviceManager;
	private PlayerPositionChangedMessage lastPositionChangedMessage;
	private int playHeadPosition = 0;

	public BeatVisualiserStripPainter(BeatVisualiserStrip parent, ProtobeatContext context, ServiceManager serviceManager) {
		this.parent = parent;
		this.context = context;
		this.serviceManager = serviceManager;
	}

	public void paint() {
		final BufferedImage image = parent.getImage();
		if (image == null) return;

		final AudioFilePropertiesAdapter adapter = context.getCurrentFilePropertiesAdapter();
		final Graphics2D graphics = image.createGraphics();

		// Clear
		graphics.setColor(STRIP_BG_COLOR);
		graphics.fillRect(0, 0, image.getWidth(), image.getHeight());

		float bps = context.getLevel().getBpm() / 60f * 2;
		float numberOfBars = adapter.durationInSeconds() * bps;

		// Draw bars
		graphics.setColor(STRIP_BAR_COLOR);
		for (float bar = 0f; bar < numberOfBars; bar++) {
			int x_a = (int) (bar * context.getPixelsPerSecond() / bps);
			if(bar % 2 == 0) graphics.setStroke(new BasicStroke(3));
			else graphics.setStroke(new BasicStroke(1));
			graphics.drawLine(x_a, 0, x_a, STRIP_HEIGHT);
		}
		graphics.setStroke(new BasicStroke(1));

		// Draw beats
		for (Beat beat : context.getLevel().getBeats()) {
			paintBeat(graphics, beat);
		}

		// Draw cursor
		if (lastPositionChangedMessage != null) {
			playHeadPosition = (int) (image.getWidth() * lastPositionChangedMessage.getScalarPosition());
		}
		paintCursor(graphics, playHeadPosition);

		graphics.dispose();
	}

	private void paintBeat(Graphics2D graphics, Beat beat) {
		final BufferedImage image = parent.getImage();
		final Rectangle dimensions = PixelUtil.beatToScreen(beat, image);

		if (beat.isHover()) {
			graphics.setColor(Color.white);
		} else {
			graphics.setColor(beat.isSelected() ? Color.pink : Color.blue);
		}
		graphics.fillRect(dimensions.x-5, dimensions.y, dimensions.width, dimensions.height);

		graphics.setColor(Color.black);
		graphics.drawRect(dimensions.x-5, dimensions.y, dimensions.width, dimensions.height);
	}

	private void paintCursor(Graphics2D graphics, int cursorPosition) {
		paintCursor(graphics, cursorPosition, Color.red);
	}

	private void paintCursor(Graphics2D graphics, int cursorPosition, Color color) {
		graphics.setColor(color);
		graphics.drawLine(cursorPosition, 0, cursorPosition, STRIP_HEIGHT);
	}

	public void setLastPositionChangedMessage(PlayerPositionChangedMessage message) {
		this.lastPositionChangedMessage = message;
	}

	public void paintBeats(ArrayList<Beat> changedBeats) {
		final BufferedImage image = parent.getImage();
		final Graphics2D graphics = image.createGraphics();

		for (Beat beat : changedBeats) {
			paintBeat(graphics, beat);
		}

		graphics.dispose();
	}

	public int getPlayHeadPosition() {
		return playHeadPosition;
	}
}
