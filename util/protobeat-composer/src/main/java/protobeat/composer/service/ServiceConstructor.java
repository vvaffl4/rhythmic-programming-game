package protobeat.composer.service;

import protobeat.common.core.context.ContextHolder;
import protobeat.common.core.context.ProtobeatContext;
import protobeat.common.core.ServiceManager;
import protobeat.common.core.event.message.BeforeShutdownMessage;
import protobeat.common.core.service.AudioService;

public class ServiceConstructor {
	public ServiceConstructor() {
		final ProtobeatContext context = ContextHolder.getInstance().getContext();
		final ServiceManager serviceManager = context.getServiceManager();

		context.getServiceManager()
				.addService(new AudioService(serviceManager))
				.addService(new SwingService(serviceManager));
	}

	public void shutdown() {
		ContextHolder.getInstance().getContext().getServiceManager().bus().emit(new BeforeShutdownMessage());
	}
}
