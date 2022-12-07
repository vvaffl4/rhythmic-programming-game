package protobeat.composer.gui;

import protobeat.common.core.context.ContextHolder;
import protobeat.common.core.context.ProtobeatContext;
import protobeat.common.core.ServiceManager;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import java.awt.*;

public class EmbeddedPanel extends JPanel {
	protected final ProtobeatContext context;
	protected final ServiceManager serviceManager;

	public EmbeddedPanel() {
		this.context = ContextHolder.getInstance().getContext();
		this.serviceManager = context.getServiceManager();

	}

	protected void embed(JPanel toEmbed) {
		setLayout(new BorderLayout());
		add(toEmbed, BorderLayout.CENTER);
	}
}
