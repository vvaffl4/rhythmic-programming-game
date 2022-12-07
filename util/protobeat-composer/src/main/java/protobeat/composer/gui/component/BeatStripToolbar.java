package protobeat.composer.gui.component;

import protobeat.common.constant.ProtobeatCommonConstants;
import protobeat.common.core.context.AudioFilePropertiesAdapter;
import protobeat.common.core.event.message.BeatsChangedMessage;
import protobeat.common.core.event.message.BeatsRemovedMessage;
import protobeat.common.core.event.message.ToolMessage;
import protobeat.common.core.model.Beat;
import protobeat.common.core.model.Level;
import protobeat.common.core.pbenum.ComposerToolType;
import protobeat.composer.gui.EmbeddedPanel;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.util.ArrayList;

public class BeatStripToolbar extends EmbeddedPanel {
	private JPanel content;
	private JButton deleteBeatButton;
	private JButton resetLevelButton;
	private JButton moveToolButton;
	private JButton disableToolsButton;
	private JButton quantizeButton;
	private JButton moveRightButton;
	private JButton moveLeftButton;
	private JButton changeLaneButton;
	private JButton moveAllRightButton;
	private JButton moveAllLeftButton;
	private final float CLOSE_ENOUGH = .001f;
	private final float NORMALIZE_TRESHOLD = 200;

	public BeatStripToolbar() {
		embed(content);

		deleteBeatButton.addActionListener(actionEvent -> {
			int rmcounter = 0;
			for (Beat beat : context.getSelection()) {
				if (context.getLevel().getBeats().remove(beat)) {
					rmcounter++;
				}
			}

			if (rmcounter > 0) {
				serviceManager.bus().emit(new BeatsRemovedMessage());
			}
		});

		resetLevelButton.addActionListener(actionEvent -> {
			final int dialogResult = JOptionPane.showConfirmDialog(
				BeatStripToolbar.this,
				"Doing this resets the level, are you sure?",
				"Are you sure?",
				JOptionPane.OK_CANCEL_OPTION
			);


			if (dialogResult == JOptionPane.OK_OPTION) {
				String songName = context.getLevel().getSongName();
				Level level = new Level();
				level.setSongName(songName);
				context.setLevel(level);

				serviceManager.bus().emit(new BeatsChangedMessage());
			}
		});

		quantizeButton.addActionListener(this::onQuantizeButtonClick);

		moveToolButton.addActionListener(actionEvent -> serviceManager.bus().emit(new ToolMessage(ComposerToolType.MOVE)));
		disableToolsButton.addActionListener(actionEvent -> serviceManager.bus().emit(new ToolMessage(ComposerToolType.NONE)));

		//moveRightButton.addActionListener(actionEvent -> serviceManager.bus().emit(new ToolMessage(ComposerToolType.MOVE_RIGHT)));
		moveLeftButton.addActionListener(this::moveBeatLeft);
		moveRightButton.addActionListener(this::moveBeatRight);
		changeLaneButton.addActionListener(this::changeBeatLane);

		moveAllRightButton.addActionListener(this::moveAllBeatsRight);
		moveAllLeftButton.addActionListener(this::moveAllBeatsLeft);
	}

	private void moveAllBeatsLeft(ActionEvent actionEvent) {
		float bps = (float) context.getLevel().getBpm() / 60;
		float distance = 1000f / bps / 2;
		boolean foundSelected = false;
		// Super ultra mega jank
		ArrayList<Beat> beatsToMove = new ArrayList<>();
		ArrayList<Beat> beatsToCheck = new ArrayList<>();
		int counter = 0;
		for (Beat beat : context.getLevel().getBeats()) {
			if (beat.isSelected()) foundSelected = true;
			if (foundSelected) beatsToMove.add(beat);
			else {
				if (counter % 2 == 0) beatsToCheck.add(0, beat);
				else beatsToCheck.add(1, beat);
				counter++;
			}
		}
		for (Beat beat : beatsToMove) {
			if ((beat.getPosition() - distance) < 0) break;
			for (Beat prev : beatsToCheck) {
				if (beat.getPosition() - distance == prev.getPosition() && beat.getLane() == prev.getLane()) {
					return;
				}
			}
			beat.setPosition(beat.getPosition() - distance);
		}
		serviceManager.bus().emit(new BeatsChangedMessage());
	}

	private void moveAllBeatsRight(ActionEvent actionEvent) {
		float bps = (float) context.getLevel().getBpm() / 60;
		float distance = 1000f / bps / 2;
		boolean foundSelected = false;
		for (Beat beat : context.getLevel().getBeats()) {
			if (beat.isSelected()) foundSelected = true;
			if (foundSelected) beat.setPosition(beat.getPosition() + distance);
		}
		serviceManager.bus().emit(new BeatsChangedMessage());
	}

	private void moveBeatLeft(ActionEvent actionEvent) {
		float bps = (float) context.getLevel().getBpm() / 60;
		float distance = 1000f / bps / 2;
		Beat previous = null;
		for (Beat current : context.getLevel().getBeats()) {
			if (previous != null) {
				if (current.isSelected() && (previous.getPosition() != (current.getPosition() - distance) || current.getLane() != previous.getLane())) {
					current.setPosition(current.getPosition() - distance);
					serviceManager.bus().emit(new BeatsChangedMessage());
					break;
				}
			}
			previous = current;
		}
	}

	private void moveBeatRight(ActionEvent actionEvent) {
		float bps = (float) context.getLevel().getBpm() / 60;
		float distance = 1000f / bps / 2;
		Beat current = null;
		for (Beat next : context.getLevel().getBeats()) {
			if (current != null) {
				if (current.isSelected() && (next.getPosition() != (current.getPosition() + distance) || current.getLane() != next.getLane())) {
					current.setPosition(current.getPosition() + distance);
					serviceManager.bus().emit(new BeatsChangedMessage());
					break;
				}
			}
			current = next;
		}
	}

	private void changeBeatLane(ActionEvent actionEvent) {
		// Warning: High jank levels detected
		for (Beat beat : context.getLevel().getBeats()) {
			if (beat.isSelected()) {
				if (beat.getLane() == ProtobeatCommonConstants.CONST_LANE_LEFT)
					beat.setLane(ProtobeatCommonConstants.CONST_LANE_RIGHT);
				else beat.setLane(ProtobeatCommonConstants.CONST_LANE_LEFT);
				serviceManager.bus().emit(new BeatsChangedMessage());
			}
		}
	}

	private void onQuantizeButtonClick(ActionEvent actionEvent) {
		final AudioFilePropertiesAdapter adapter = context.getCurrentFilePropertiesAdapter();
		float halfTicks = adapter.durationInMinutes() * (float) context.getLevel().getBpm() * 2f;
		float bps = (float) context.getLevel().getBpm() / 60;
		float distance = 1000f / bps / 2;

		System.out.printf("Quantize params:\nhalfTicks = %f\nbps=%f\ndistance=%f\n", halfTicks, bps, distance);

		ArrayList<Beat> changedBeats = new ArrayList<>();
		for (Beat beat : context.getLevel().getBeats()) {
			float oldPosition = beat.getPosition();

			float remain = beat.getPosition() % distance;
			if (remain > 0 && remain < CLOSE_ENOUGH) {
				continue;
			}

			if (remain > distance / 2) {
				// Too early
				float delta = distance - remain;
				beat.setPosition(beat.getPosition() + delta);
			} else {
				// Too late
				beat.setPosition(beat.getPosition() - remain);
			}

			if (oldPosition != beat.getPosition()) {
				changedBeats.add(beat);
			}
		}

		ArrayList<Beat> deletedBeats = new ArrayList<>();
		for (Beat beat : context.getLevel().getBeats()) {
			for (Beat beat2 : context.getLevel().getBeats()) {
				if (beatsOverlap(beat, beat2)) {
					deletedBeats.add(beat);
				}
			}
		}
		for (Beat beat : deletedBeats) {
			context.getLevel().getBeats().remove(beat);
		}

		System.out.printf("Removed %d overlapping beats\n", deletedBeats.size());

		for (Beat beat : context.getLevel().getBeats()) {
			if (beat.getDuration() <= NORMALIZE_TRESHOLD) {
				beat.setDuration(100);
				if (!changedBeats.contains(beat)) {
					changedBeats.add(beat);
				}
			}
		}

		changedBeats.removeAll(deletedBeats);

		serviceManager.bus().emit(new BeatsChangedMessage(changedBeats));
		serviceManager.bus().emit(new BeatsRemovedMessage(deletedBeats));
	}

	private boolean beatsOverlap(Beat beat, Beat beat2) {
		if (beat.equals(beat2)) return false;
		if (beat.getLane() != beat2.getLane()) return false;

		float b1left = beat.getPosition();
		float b1right = beat.getPosition() + beat.getDuration();

		float b2left = beat2.getPosition();
		float b2right = beat2.getPosition() + beat2.getDuration();

		if (b2left > b1left && b2left < b1right) {
			// Left side of beat2 is within beat
			return true;
		}

		if (b2right > b1left && b2right < b1right) {
			// Right side of beat2 is within beat
			return true;
		}

		return false;
	}

	{
// GUI initializer generated by IntelliJ IDEA GUI Designer
// >>> IMPORTANT!! <<<
// DO NOT EDIT OR ADD ANY CODE HERE!
		$$$setupUI$$$();
	}

	/**
	 * Method generated by IntelliJ IDEA GUI Designer
	 * >>> IMPORTANT!! <<<
	 * DO NOT edit this method OR call it in your code!
	 *
	 * @noinspection ALL
	 */
	private void $$$setupUI$$$() {
		content = new JPanel();
		content.setLayout(new FlowLayout(FlowLayout.LEFT, 5, 5));
		deleteBeatButton = new JButton();
		deleteBeatButton.setIcon(new ImageIcon(getClass().getResource("/protobeat/composer/res/eraser@16.png")));
		deleteBeatButton.setText("Remove");
		content.add(deleteBeatButton);
		resetLevelButton = new JButton();
		resetLevelButton.setIcon(new ImageIcon(getClass().getResource("/protobeat/composer/res/rotate-left@16.png")));
		resetLevelButton.setText("Reset");
		resetLevelButton.setToolTipText("F*** go back");
		content.add(resetLevelButton);
		disableToolsButton = new JButton();
		disableToolsButton.setIcon(new ImageIcon(getClass().getResource("/protobeat/composer/res/ban@16.png")));
		disableToolsButton.setText("");
		content.add(disableToolsButton);
		quantizeButton = new JButton();
		quantizeButton.setText("Quantize");
		content.add(quantizeButton);
		moveToolButton = new JButton();
		moveToolButton.setIcon(new ImageIcon(getClass().getResource("/protobeat/composer/res/arrows@16.png")));
		moveToolButton.setText("Move");
		content.add(moveToolButton);
		moveLeftButton = new JButton();
		moveLeftButton.setText("Move Left");
		content.add(moveLeftButton);
		moveRightButton = new JButton();
		moveRightButton.setText("Move Right");
		content.add(moveRightButton);
		changeLaneButton = new JButton();
		changeLaneButton.setText("Change Lane");
		content.add(changeLaneButton);
		moveAllLeftButton = new JButton();
		moveAllLeftButton.setText("Move All Left");
		content.add(moveAllLeftButton);
		moveAllRightButton = new JButton();
		moveAllRightButton.setText("Move All Right");
		content.add(moveAllRightButton);
	}

	/**
	 * @noinspection ALL
	 */
	public JComponent $$$getRootComponent$$$() {
		return content;
	}
}
