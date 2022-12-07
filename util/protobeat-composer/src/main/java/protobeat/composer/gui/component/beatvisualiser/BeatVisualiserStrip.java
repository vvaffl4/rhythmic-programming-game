package protobeat.composer.gui.component.beatvisualiser;

import protobeat.common.core.ServiceManager;
import protobeat.common.core.context.AudioFilePropertiesAdapter;
import protobeat.common.core.context.ContextHolder;
import protobeat.common.core.context.ProtobeatContext;
import protobeat.common.core.event.EventListener;
import protobeat.common.core.event.message.*;
import protobeat.common.core.model.Beat;
import protobeat.composer.util.PixelUtil;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.HashMap;

import static java.awt.image.BufferedImage.TYPE_INT_RGB;
import static protobeat.common.constant.ComposerContants.STRIP_HEIGHT;

public class BeatVisualiserStrip extends JPanel {
	private final BeatVisualiserStripPainter painter;
	private final ProtobeatContext context;
	private final ServiceManager serviceManager;
	private AudioFilePropertiesAdapter adapter = new AudioFilePropertiesAdapter(new HashMap<>());
	private BufferedImage image;
	private PositionChangedListener positionChangedListener;

	public BeatVisualiserStrip() {
		this.context = ContextHolder.getInstance().getContext();
		this.serviceManager = context.getServiceManager();
		this.painter = new BeatVisualiserStripPainter(this, context, serviceManager);

		serviceManager.bus().addListener(new EventListener<EventMessage>() {
			@Override
			public void onMessage(EventMessage message) {
				if (message instanceof PlayerBufferStateChangedMessage) {
					onBufferStateChanged((PlayerBufferStateChangedMessage) message);
					return;
				}

				if (message instanceof PlayerPositionChangedMessage) {
					onPositionChanged((PlayerPositionChangedMessage) message);
					return;
				}

				if (message instanceof BeatSelectionChangedMessage) {
					onBeatSelectionChanged((BeatSelectionChangedMessage) message);
					return;
				}

				if (message instanceof BeatsChangedMessage) {
					onBeatsChanged((BeatsChangedMessage) message);
				}

				if (message instanceof BPMChangedMessage) {
					repaintLater();
				}
			}
		});

		addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent mouseEvent) {
				System.out.println(mouseEvent.getPoint());

				super.mousePressed(mouseEvent);
			}

			@Override
			public void mouseReleased(MouseEvent mouseEvent) {
				System.out.println(mouseEvent.getPoint());

				super.mouseReleased(mouseEvent);
			}

			@Override
			public void mouseClicked(MouseEvent mouseEvent) {
				ArrayList<Beat> changedBeats = new ArrayList<>();
				for (Beat beat : context.getLevel().getBeats()) {
					boolean old = beat.isSelected();
					beat.setSelected(PixelUtil.beatToScreen(beat, image).contains(mouseEvent.getPoint()));
					if (old != beat.isSelected()) {
						changedBeats.add(beat);
					}
				}

				if (changedBeats.size() > 0) {
					serviceManager.bus().emit(new BeatSelectionChangedMessage(changedBeats));
				}
			}
		});

		addMouseMotionListener(new MouseAdapter() {
			@Override
			public void mouseMoved(MouseEvent mouseEvent) {
				ArrayList<Beat> changedBeats = new ArrayList<>();
				for (Beat beat : context.getLevel().getBeats()) {
					boolean old = beat.isHover();
					beat.setHover(PixelUtil.beatToScreen(beat, image).contains(mouseEvent.getPoint()) && !beat.isSelected());
					if (old != beat.isHover()) {
						changedBeats.add(beat);
					}
				}

				if (changedBeats.size() > 0) {
					serviceManager.bus().emit(new BeatSelectionChangedMessage(changedBeats));
				}
			}
		});
	}

	private void onBeatsChanged(BeatsChangedMessage message) {
		repaintLater();
	}

	private void onBeatSelectionChanged(BeatSelectionChangedMessage message) {
		painter.paintBeats(message.getChangedBeats());
		repaintLater();
	}

	private void onPositionChanged(PlayerPositionChangedMessage message) {
		painter.setLastPositionChangedMessage(message);
		repaintLater();

		if (positionChangedListener != null) {
			positionChangedListener.onPositionChanged();
		}
	}

	private void onBufferStateChanged(PlayerBufferStateChangedMessage message) {
		if (message.isBuffering()) {
			this.image = new BufferedImage(10, 10, BufferedImage.TYPE_INT_RGB);
			return;
		}

		this.adapter = context.getCurrentFilePropertiesAdapter();
		synchronized (this) {
			this.image = new BufferedImage((int) (adapter.durationInSeconds() * context.getPixelsPerSecond()), STRIP_HEIGHT, TYPE_INT_RGB);

			Dimension dimension = new Dimension(image.getWidth(), image.getHeight());
			setMinimumSize(dimension);
			setPreferredSize(dimension);
			setSize(dimension);
		}

		repaintLater();
	}

	@Override
	public void paint(Graphics graphics) {
		synchronized (this) {
			painter.paint();
			graphics.drawImage(image, 0, 0, null);
		}
	}

	public BufferedImage getImage() {
		return image;
	}

	public BeatVisualiserStripPainter getPainter() {
		return painter;
	}

	public PositionChangedListener getPositionChangedListener() {
		return positionChangedListener;
	}

	public void setPositionChangedListener(PositionChangedListener positionChangedListener) {
		this.positionChangedListener = positionChangedListener;
	}

	public interface PositionChangedListener {
		void onPositionChanged();
	}

	private void repaintLater() {
		SwingUtilities.invokeLater(this::repaint);
	}
}
