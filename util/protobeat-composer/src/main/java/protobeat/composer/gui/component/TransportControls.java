package protobeat.composer.gui.component;

import com.intellij.uiDesigner.core.GridConstraints;
import com.intellij.uiDesigner.core.GridLayoutManager;
import com.intellij.uiDesigner.core.Spacer;
import protobeat.common.core.audio.AudioTrack;
import protobeat.common.core.event.EventListener;
import protobeat.common.core.event.message.*;
import protobeat.common.core.pbenum.TransportControlType;
import protobeat.composer.gui.EmbeddedPanel;

import javax.swing.*;
import java.awt.*;

public class TransportControls extends EmbeddedPanel {
	private final String recordingLabelText;
	private JPanel content;
	private JButton playButton;
	private JButton pauseButton;
	private JPanel controls;
	private JPanel statusPanel;
	private JLabel songNameLabel;
	private JLabel durationLabel;
	private JPanel row0;
	private JPanel row1;
	private JSlider transportSlider;
	private JLabel positionLabel;
	private JLabel bufferingLabel;
	private JButton recordButton;
	private JLabel recordingLabel;
	private boolean sliderChangeLock = false;

	public TransportControls() {
		playButton.addActionListener(actionEvent -> serviceManager.bus().emit(new AudioTransportMessage(TransportControlType.PLAY)));
		pauseButton.addActionListener(actionEvent -> serviceManager.bus().emit(new AudioTransportMessage(TransportControlType.PAUSE)));
		recordButton.addActionListener(actionEvent -> {
			serviceManager.bus().emit(new AudioTransportMessage(TransportControlType.RECORD));
			serviceManager.bus().emit(new AudioTransportMessage(TransportControlType.PLAY));
		});

		bufferingLabel.setText("");
		this.recordingLabelText = recordingLabel.getText();
		recordingLabel.setText("");

		transportSlider.addChangeListener(changeEvent -> {
			if (sliderChangeLock) return;

			AudioTransportMessage message = new AudioTransportMessage(TransportControlType.SEEK);
			message.setTransportSeek(transportSlider.getValue());
			serviceManager.bus().emit(message);
		});

		serviceManager.bus().addListener(new EventListener<EventMessage>() {
			@Override
			public void onMessage(EventMessage message) {
				if (message instanceof AudioFileChangedMessage) {
					onAudioFileChanged((AudioFileChangedMessage) message);
				}
				if (message instanceof PlayerPositionChangedMessage) {
					onPlayerPositionChanged((PlayerPositionChangedMessage) message);
				}
				if (message instanceof PlayerBufferStateChangedMessage) {
					onBufferStateChanged((PlayerBufferStateChangedMessage) message);
				}
				if (message instanceof InputRecorderStateChangedMessage) {
					onInputRecorderStateChanged((InputRecorderStateChangedMessage) message);
				}
			}
		});

		embed(content);
	}

	private void onInputRecorderStateChanged(InputRecorderStateChangedMessage message) {
		recordingLabel.setText(message.isRecording() ? recordingLabelText : "");
	}

	private void onBufferStateChanged(PlayerBufferStateChangedMessage message) {
		bufferingLabel.setText(message.isBuffering() ? "BUFFERING" : "");
		if (message.isBuffering()) return;

		final AudioTrack audioTrack = message.getPlayer().getAudioTrack();
		durationLabel.setText("Duration: " + audioTrack.length());
		transportSlider.setMaximum(audioTrack.length());
		transportSlider.setValue(0);
	}

	private void onPlayerPositionChanged(PlayerPositionChangedMessage message) {
		sliderChangeLock = true;
		transportSlider.setValue((int) message.getPosition());
		positionLabel.setText("Position: " + message.getPosition());
		sliderChangeLock = false;
	}

	private void onAudioFileChanged(AudioFileChangedMessage message) {
		songNameLabel.setText(context.currentAudioFileName());
		transportSlider.setValue(0);
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
		content.setLayout(new GridLayoutManager(2, 1, new Insets(0, 0, 0, 0), -1, -1));
		row0 = new JPanel();
		row0.setLayout(new GridLayoutManager(3, 2, new Insets(0, 0, 0, 0), -1, -1));
		content.add(row0, new GridConstraints(0, 0, 1, 1, GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_WANT_GROW, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, null, null, null, 0, false));
		controls = new JPanel();
		controls.setLayout(new FlowLayout(FlowLayout.LEFT, 5, 5));
		row0.add(controls, new GridConstraints(0, 0, 1, 1, GridConstraints.ANCHOR_NORTHWEST, GridConstraints.FILL_NONE, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_WANT_GROW, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, null, new Dimension(259, 52), null, 0, false));
		playButton = new JButton();
		playButton.setIcon(new ImageIcon(getClass().getResource("/protobeat/composer/res/play@32.png")));
		playButton.setText("");
		controls.add(playButton);
		pauseButton = new JButton();
		pauseButton.setIcon(new ImageIcon(getClass().getResource("/protobeat/composer/res/pause@32.png")));
		pauseButton.setText("");
		controls.add(pauseButton);
		recordButton = new JButton();
		recordButton.setIcon(new ImageIcon(getClass().getResource("/protobeat/composer/res/circle@32.png")));
		recordButton.setText("");
		controls.add(recordButton);
		statusPanel = new JPanel();
		statusPanel.setLayout(new GridLayoutManager(4, 1, new Insets(0, 0, 0, 0), -1, -1));
		row0.add(statusPanel, new GridConstraints(0, 1, 1, 1, GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_WANT_GROW, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, null, null, null, 0, false));
		songNameLabel = new JLabel();
		songNameLabel.setText("> Song name");
		statusPanel.add(songNameLabel, new GridConstraints(0, 0, 1, 1, GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE, GridConstraints.SIZEPOLICY_FIXED, GridConstraints.SIZEPOLICY_FIXED, null, new Dimension(235, 16), null, 0, false));
		durationLabel = new JLabel();
		durationLabel.setText("> Duration");
		statusPanel.add(durationLabel, new GridConstraints(1, 0, 1, 1, GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE, GridConstraints.SIZEPOLICY_FIXED, GridConstraints.SIZEPOLICY_FIXED, null, null, null, 0, false));
		positionLabel = new JLabel();
		positionLabel.setText("> Position");
		statusPanel.add(positionLabel, new GridConstraints(2, 0, 1, 1, GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE, GridConstraints.SIZEPOLICY_FIXED, GridConstraints.SIZEPOLICY_FIXED, null, null, null, 0, false));
		bufferingLabel = new JLabel();
		bufferingLabel.setEnabled(true);
		bufferingLabel.setText("BUFFERING");
		statusPanel.add(bufferingLabel, new GridConstraints(3, 0, 1, 1, GridConstraints.ANCHOR_WEST, GridConstraints.FILL_NONE, GridConstraints.SIZEPOLICY_FIXED, GridConstraints.SIZEPOLICY_FIXED, null, null, null, 0, false));
		recordingLabel = new JLabel();
		Font recordingLabelFont = this.$$$getFont$$$(null, Font.BOLD, 16, recordingLabel.getFont());
		if (recordingLabelFont != null) recordingLabel.setFont(recordingLabelFont);
		recordingLabel.setForeground(new Color(-4520438));
		recordingLabel.setText("RECORDING");
		row0.add(recordingLabel, new GridConstraints(1, 0, 1, 1, GridConstraints.ANCHOR_NORTHWEST, GridConstraints.FILL_NONE, GridConstraints.SIZEPOLICY_FIXED, GridConstraints.SIZEPOLICY_FIXED, null, null, null, 1, false));
		final Spacer spacer1 = new Spacer();
		row0.add(spacer1, new GridConstraints(2, 0, 1, 1, GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_VERTICAL, 1, GridConstraints.SIZEPOLICY_WANT_GROW, null, null, null, 0, false));
		row1 = new JPanel();
		row1.setLayout(new GridLayoutManager(1, 1, new Insets(0, 0, 0, 0), -1, -1));
		content.add(row1, new GridConstraints(1, 0, 1, 1, GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, null, null, null, 0, false));
		transportSlider = new JSlider();
		row1.add(transportSlider, new GridConstraints(0, 0, 1, 1, GridConstraints.ANCHOR_WEST, GridConstraints.FILL_HORIZONTAL, GridConstraints.SIZEPOLICY_WANT_GROW, GridConstraints.SIZEPOLICY_FIXED, null, null, null, 0, false));
	}

	/**
	 * @noinspection ALL
	 */
	private Font $$$getFont$$$(String fontName, int style, int size, Font currentFont) {
		if (currentFont == null) return null;
		String resultName;
		if (fontName == null) {
			resultName = currentFont.getName();
		} else {
			Font testFont = new Font(fontName, Font.PLAIN, 10);
			if (testFont.canDisplay('a') && testFont.canDisplay('1')) {
				resultName = fontName;
			} else {
				resultName = currentFont.getName();
			}
		}
		return new Font(resultName, style >= 0 ? style : currentFont.getStyle(), size >= 0 ? size : currentFont.getSize());
	}

	/**
	 * @noinspection ALL
	 */
	public JComponent $$$getRootComponent$$$() {
		return content;
	}
}
