//
// Created by kostia on 11/25/24.
//

#include "MQTTClient.h"

MQTTClient::MQTTClient(const char* broker, uint16_t port, const char* clientID)
    : broker(broker), port(port), clientID(clientID), wifiClient(wifiClient), mqttClient(mqttClient)
{
}

void MQTTClient::begin(WiFiClient& wifiClient)
{
    mqttClient.setClient(wifiClient);
    mqttClient.setServer(broker, port);
}

bool MQTTClient::connect()
{
    if (mqttClient.connected()) return true;
    Serial.println("Connecting to MQTT broker:");
    Serial.println(broker);

    if (mqttClient.connect(broker))
    {
        Serial.println("MQTT connected successfully");
        return true;
    }
    else
    {
        Serial.println("MQTT connection failed");
        Serial.println(mqttClient.state());
        return false;
    }
}

void MQTTClient::disconnect()
{
    if (mqttClient.connected())
    {
        mqttClient.disconnect();
        Serial.println("MQTT connection broken");
    }
}

bool MQTTClient::isConnected() const
{
    return mqttClient.connected();
}

void MQTTClient::publish(const char* topic, const char* payload)
{
    if (mqttClient.connected())
    {
        mqttClient.publish(topic, payload);
        Serial.printf("Published message: [%s] %s\n", topic, payload);
    }
    else
    {
        Serial.println("Failed to publish message, connection to broker lost.");
    }
}

void MQTTClient::subscribe(const char* topic)
{
    if (mqttClient.connected())
    {
        mqttClient.subscribe(topic);
        Serial.printf("Subscribe to topic: %s\n", topic);
    }
    else
    {
        Serial.println("Failed to subscribe, connection to broker lost.");
    }
}

void MQTTClient::loop()
{
    if (mqttClient.connected())
    {
        mqttClient.loop();
    }
}

void MQTTClient::setCallback(MQTT_CALLBACK_SIGNATURE)
{
    mqttClient.setCallback(callback);
}
