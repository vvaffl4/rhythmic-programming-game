package protobeat.composer;

import protobeat.composer.service.ServiceConstructor;

public class ProtobeatComposer {
	public static void main(String[] arguments) {
		final ServiceConstructor serviceConstructor = new ServiceConstructor();
		Runtime.getRuntime().addShutdownHook(new Thread(serviceConstructor::shutdown));
	}
}
