package protobeat.common.core;

import protobeat.common.core.event.EventEmitter;
import protobeat.common.core.event.message.EventMessage;

import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;

public class ServiceManager {
	private EventEmitter<EventMessage> bus = new EventEmitter<>();
	private ArrayList<Service> services = new ArrayList<>();

	public EventEmitter<EventMessage> bus() {
		return bus;
	}

	public ServiceManager addService(Service service) {
		services.add(service);
		return this;
	}
}
