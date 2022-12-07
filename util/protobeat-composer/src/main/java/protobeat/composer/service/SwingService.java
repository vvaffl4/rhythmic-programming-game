package protobeat.composer.service;

import org.pushingpixels.substance.api.skin.SubstanceOfficeBlue2007LookAndFeel;
import org.pushingpixels.substance.api.skin.SubstanceTwilightLookAndFeel;
import protobeat.common.core.FailBucket;
import protobeat.common.core.Service;
import protobeat.common.core.ServiceManager;
import protobeat.composer.gui.form.ComposerForm;

import javax.swing.*;

import static protobeat.common.constant.ComposerContants.COMPOSER_LOOK_AND_FEEL;

public class SwingService extends Service {
	private ComposerForm composerForm;

	public SwingService(ServiceManager serviceManager) {
		super(serviceManager);

		JFrame.setDefaultLookAndFeelDecorated(true);
		SwingUtilities.invokeLater(() -> {
			try {
				UIManager.setLookAndFeel(COMPOSER_LOOK_AND_FEEL);
			} catch (Exception e) {
				FailBucket.accept(e);
			}
		});

		SwingUtilities.invokeLater(() -> {
			composerForm = new ComposerForm(serviceManager);
			composerForm.setLocationRelativeTo(null);
			composerForm.setVisible(true);
		});
	}
}
