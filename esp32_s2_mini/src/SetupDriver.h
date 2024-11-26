//
// Created by kostia on 11/26/24.
//

#ifndef SETUPDRIVER_H
#define SETUPDRIVER_H

#include <Arduino.h>
#include "WiFiManager.h"
#include "MQTTClient.h"

class SetupDriver {
public:
    SetupDriver(const char* wifiSSID, const char* wifiPassword,
                const char* mqttBroker, uint16_t mqttPort,
                const char* mqttClientID);

    void initialize();
    void maintainConnection();
    MQTTClient& getMQTTClient();

private:
    WiFiManager wifiManager;
    WiFiClient wifiClient;
    MQTTClient mqttClient;

    const char* mqttBroker;
    uint16_t mqttPort;
    const char* mqttClientID;
};



#endif //SETUPDRIVER_H
