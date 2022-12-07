package protobeat.common.core.event;

import java.util.ArrayList;
import java.util.List;

public class EventEmitter<T> {
	private List<EventListener<T>> eventListeners = new ArrayList<>();

	public void addListener(EventListener<T> eventListener) {
		eventListeners.add(eventListener);
	}

	public boolean removeListener(EventListener<T> eventListener) {
		return eventListeners.remove(eventListener);
	}

	public void emit(T message) {
		eventListeners.forEach(eventListener -> eventListener.onMessage(message));
	}
}
