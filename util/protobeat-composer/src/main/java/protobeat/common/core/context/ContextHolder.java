package protobeat.common.core.context;

public class ContextHolder {
	private final static ContextHolder instance = new ContextHolder();
	public static ContextHolder getInstance() {return instance;}

	private ProtobeatContext context = new ProtobeatContext();
	private ContextHolder() {}

	public ProtobeatContext getContext() {
		return context;
	}
}
