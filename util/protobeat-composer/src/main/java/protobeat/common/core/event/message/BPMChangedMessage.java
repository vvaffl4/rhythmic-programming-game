package protobeat.common.core.event.message;

import lombok.Data;

@Data
public class BPMChangedMessage implements EventMessage {
    private int bpm;

    public BPMChangedMessage(int bpm) {
        this.bpm = bpm;
    }

    public BPMChangedMessage(Object value) throws Exception {
        this((int) value);
    }
}
