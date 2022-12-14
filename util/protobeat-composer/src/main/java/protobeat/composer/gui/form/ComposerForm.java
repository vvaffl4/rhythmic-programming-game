package protobeat.composer.gui.form;

import com.intellij.uiDesigner.core.GridConstraints;
import com.intellij.uiDesigner.core.GridLayoutManager;
import protobeat.common.core.ServiceManager;
import protobeat.common.core.event.EventListener;
import protobeat.common.core.event.message.EventMessage;
import protobeat.common.core.event.message.RequestFileOpenMessage;
import protobeat.common.core.event.message.SetAudioFileEventMessage;
import protobeat.composer.gui.component.ApplicationToolbar;
import protobeat.composer.gui.component.BeatStripToolbar;
import protobeat.composer.gui.component.UserPropertiesPane;
import protobeat.composer.gui.component.inputrecorder.InputRecorderComponent;
import protobeat.composer.gui.component.beatvisualiser.ScrollableBeatVisualiser;
import protobeat.composer.gui.component.TransportControls;

import javax.swing.*;
import java.awt.*;
import java.io.File;

import static protobeat.common.constant.ComposerContants.COMPOSER_WINDOW_MINSIZE;
import static protobeat.common.constant.ComposerContants.COMPOSER_WINDOW_TITLE;

public class ComposerForm extends JFrame {
	private JPanel content;
	private JPanel beatVisualiserContainer;
	private JPanel inputRecorderContainer;
	private final JFileChooser mp3FileChooser = new JFileChooser();
	private final ServiceManager serviceManager;

	public ComposerForm(ServiceManager serviceManager) {
		super(COMPOSER_WINDOW_TITLE);
		this.serviceManager = serviceManager;

		Dimension dimension = COMPOSER_WINDOW_MINSIZE;
		setMinimumSize(dimension);
		setSize(dimension);
		setResizable(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		setContentPane(content);

		setupFileChooser();
		addBusListeners();
	}

	private void addBusListeners() {
		serviceManager.bus().addListener(new EventListener<EventMessage>() {
			@Override
			public void onMessage(EventMessage message) {
				if (message instanceof RequestFileOpenMessage) {
					mp3FileChooser.showOpenDialog(ComposerForm.this);
				}
			}
		});
	}

	private void setupFileChooser() {
		mp3FileChooser.setFileFilter(new MP3FileFilter());

		mp3FileChooser.addActionListener(actionEvent -> {
			if (actionEvent.getActionCommand().equals("ApproveSelection")) {
				final File selectedFile = mp3FileChooser.getSelectedFile().getAbsoluteFile();
				serviceManager.bus().emit(new SetAudioFileEventMessage(selectedFile));
			}
		});
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
		content.setLayout(new GridLayoutManager(4, 1, new Insets(0, 0, 0, 0), -1, -1));
		final ApplicationToolbar nestedForm1 = new ApplicationToolbar();
		content.add(nestedForm1.$$$getRootComponent$$$(), new GridConstraints(0, 0, 1, 1, GridConstraints.ANCHOR_NORTH, GridConstraints.FILL_HORIZONTAL, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_WANT_GROW, 1, null, null, null, 0, false));
		beatVisualiserContainer = new JPanel();
		beatVisualiserContainer.setLayout(new GridLayoutManager(2, 1, new Insets(0, 0, 0, 0), -1, -1));
		content.add(beatVisualiserContainer, new GridConstraints(3, 0, 1, 1, GridConstraints.ANCHOR_SOUTH, GridConstraints.FILL_HORIZONTAL, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, null, null, null, 0, false));
		final ScrollableBeatVisualiser scrollableBeatVisualiser1 = new ScrollableBeatVisualiser();
		beatVisualiserContainer.add(scrollableBeatVisualiser1, new GridConstraints(1, 0, 1, 1, GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, null, null, null, 0, false));
		final BeatStripToolbar nestedForm2 = new BeatStripToolbar();
		beatVisualiserContainer.add(nestedForm2.$$$getRootComponent$$$(), new GridConstraints(0, 0, 1, 1, GridConstraints.ANCHOR_SOUTHWEST, GridConstraints.FILL_NONE, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, null, null, null, 0, false));
		inputRecorderContainer = new JPanel();
		inputRecorderContainer.setLayout(new GridLayoutManager(1, 2, new Insets(0, 0, 0, 0), -1, -1));
		content.add(inputRecorderContainer, new GridConstraints(2, 0, 1, 1, GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_BOTH, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, null, null, null, 0, false));
		final InputRecorderComponent inputRecorderComponent1 = new InputRecorderComponent();
		inputRecorderContainer.add(inputRecorderComponent1, new GridConstraints(0, 0, 1, 1, GridConstraints.ANCHOR_CENTER, GridConstraints.FILL_NONE, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, null, null, null, 0, false));
		final UserPropertiesPane nestedForm3 = new UserPropertiesPane();
		inputRecorderContainer.add(nestedForm3.$$$getRootComponent$$$(), new GridConstraints(0, 1, 1, 1, GridConstraints.ANCHOR_NORTHEAST, GridConstraints.FILL_NONE, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, null, null, null, 0, false));
		final TransportControls nestedForm4 = new TransportControls();
		content.add(nestedForm4.$$$getRootComponent$$$(), new GridConstraints(1, 0, 1, 1, GridConstraints.ANCHOR_NORTH, GridConstraints.FILL_HORIZONTAL, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_WANT_GROW, GridConstraints.SIZEPOLICY_CAN_SHRINK | GridConstraints.SIZEPOLICY_CAN_GROW, null, null, null, 0, false));
	}

	/**
	 * @noinspection ALL
	 */
	public JComponent $$$getRootComponent$$$() {
		return content;
	}
}
