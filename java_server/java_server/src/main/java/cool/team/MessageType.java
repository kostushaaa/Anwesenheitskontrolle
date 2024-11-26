package cool.team;

public enum MessageType {
    ADD_USER,
    DELETE_USER,
    UNKNOWN;

    public static MessageType fromString(String type) {
        try {
            return MessageType.valueOf(type.toUpperCase());
        } catch (IllegalArgumentException e) {
            return UNKNOWN;
        }
    }
}
