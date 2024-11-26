//
// Created by kostia on 11/25/24.
//

#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <Arduino.h>
#include <WiFiClient.h>
#include <PubSubClient.h>


class MQTTClient
{
public:
    MQTTClient(const char* broker, uint16_t port, const char* clientId);

    void begin(WiFiClient& wifiClient);
    bool connect();
    void disconnect();
    bool isConnected() const;
    void publish(const char* topic, const char* payload);
    void subscribe(const char* topic);
    void loop();

    void setCallback(MQTT_CALLBACK_SIGNATURE);

private:
    const char* broker;
    uint16_t port;
    const char* clientID;
    WiFiClient wifiClient;
    PubSubClient& mqttClient;
};


#endif //MQTTCLIENT_H
