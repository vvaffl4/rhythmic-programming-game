package protobeat.composer.gui.component.beatvisualiser;

import protobeat.composer.util.DimensionUtil;

import javax.swing.*;
import java.awt.*;

import static protobeat.common.constant.ComposerContants.COMPOSER_WINDOW_MINSIZE;
import static protobeat.common.constant.ComposerContants.STRIP_HEIGHT;

public class ScrollableBeatVisualiser extends JScrollPane {
	private BeatVisualiserStrip visualizerStrip;

	public ScrollableBeatVisualiser() {
		this.visualizerStrip = new BeatVisualiserStrip();
		viewport.add(visualizerStrip);

		Dimension minimumSize = new Dimension(COMPOSER_WINDOW_MINSIZE.width, STRIP_HEIGHT);
		Dimension biggerMinimumSize = DimensionUtil.add(minimumSize, 0, 20);
		viewport.setMinimumSize(minimumSize);
		setMinimumSize(biggerMinimumSize);

		setBackground(Color.black);

		visualizerStrip.setPositionChangedListener(this::onPositionChanged);
	}

	private void onPositionChanged() {
		SwingUtilities.invokeLater(() -> {
			int playheadPosition = visualizerStrip.getPainter().getPlayHeadPosition();
			Rectangle rectangle = new Rectangle(playheadPosition - viewport.getViewPosition().x, STRIP_HEIGHT, STRIP_HEIGHT * 2, STRIP_HEIGHT);
			viewport.scrollRectToVisible(rectangle);
		});
	}
}
