package cool.team;

import java.util.Map;

public class MessageHandler {
    public void handle(MessageType type, Map<String, String> params) {
        switch (type) {
            case ADD_USER:
                handleAddUser(params);
                break;
            case DELETE_USER:
                handleDeleteUser(params);
                break;
            default:
                handleUnknown(params);
                break;
        }
    }

    private void handleAddUser(Map<String, String> params) {
        String username = params.get("username");
        System.out.println("Processing ADD_USER with username: " + username);
        // Add logic for handling "add user"
    }

    private void handleDeleteUser(Map<String, String> params) {
        String username = params.get("username");
        System.out.println("Processing DELETE_USER with username: " + username);
        // Add logic for handling "delete user"
    }

    private void handleUnknown(Map<String, String> params) {
        System.out.println("Processing UNKNOWN type with params: " + params);
        // Handle unknown message types
    }
}
