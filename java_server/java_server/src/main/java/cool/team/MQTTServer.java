package cool.team;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.eclipse.paho.client.mqttv3.*;

import java.io.IOException;
import java.util.Iterator;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MQTTServer {
    private static final String BROKER_URL = "tcp://127.0.0.1:1883";
    private static final String CLIENT_ID = "MQTTServer";
    private static final String TOPIC = "#";

    private static final String USERNAME = "admin"; // Replace with your username
    private static final String PASSWORD = "password"; // Replace with your password

    private final MqttClient client;
    private final ExecutorService threadPool;
    private final MessageHandler messageHandler;
    private final ObjectMapper objectMapper;

    public MQTTServer() throws MqttException {
        client = new MqttClient(BROKER_URL, CLIENT_ID);
        threadPool = Executors.newCachedThreadPool();
        messageHandler = new MessageHandler();
        objectMapper = new ObjectMapper(); // Jackson's object mapper for JSON parsing
    }

    public void start() throws MqttException {
        MqttConnectOptions options = new MqttConnectOptions();
        options.setUserName(USERNAME); // Set username
        options.setPassword(PASSWORD.toCharArray()); // Set password
        options.setCleanSession(true); // Optionally enable clean session

        client.setCallback(new MqttCallback() {
            @Override
            public void connectionLost(Throwable cause) {
                System.out.println("Connection lost: " + cause.getMessage());
            }

            @Override
            public void messageArrived(String topic, MqttMessage message) {
                threadPool.submit(() -> processMessage(new String(message.getPayload())));
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken token) {
                System.out.println("Message delivery complete.");
            }
        });

        client.connect(options);
        System.out.println("Connected to broker: " + BROKER_URL);

        client.subscribe(TOPIC);
        System.out.println("Subscribed to topic: " + TOPIC);
    }

    public void stop() throws MqttException {
        threadPool.shutdown();
        if (client.isConnected()) {
            client.disconnect();
        }
        System.out.println("MQTT server stopped.");
    }

    private void processMessage(String payload) {
        System.out.println("Received message: " + payload);

        try {
            // Parse the payload as JSON
            JsonNode rootNode = objectMapper.readTree(payload);

            // Extract the message type
            String msgTypeString = rootNode.path("msg_type").asText();
            MessageType msgType = MessageType.fromString(msgTypeString);

            // Collect the rest of the parameters into a Map
            Map<String, String> params = convertJsonNodeToMap(rootNode);

            // Delegate to the handler
            messageHandler.handle(msgType, params);

        } catch (IOException e) {
            System.out.println("Failed to parse message as JSON: " + e.getMessage());
        }
    }

    private Map<String, String> convertJsonNodeToMap(JsonNode node) {
        // Iterate through the JSON fields and map them to a Map<String, String>
        Map<String, String> map = new java.util.HashMap<>();
        Iterator<String> fieldNames = node.fieldNames();

        while (fieldNames.hasNext()) {
            String fieldName = fieldNames.next();
            if (!fieldName.equals("msg_type")) {  // Don't include msg_type in the map
                map.put(fieldName, node.path(fieldName).asText());
            }
        }
        return map;
    }

    public static void main(String[] args) {
        try {
            MQTTServer server = new MQTTServer();
            server.start();

            System.out.println("Press Enter to stop the server...");
            System.in.read();

            server.stop();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}