package protobeat.common.core;

import protobeat.common.core.context.ContextHolder;
import protobeat.common.core.context.ProtobeatContext;

public class Service {
	protected final ServiceManager serviceManager;
	protected final ProtobeatContext context;

	public Service(ServiceManager serviceManager) {
		this.serviceManager = serviceManager;
		context = ContextHolder.getInstance().getContext();
	}
}
