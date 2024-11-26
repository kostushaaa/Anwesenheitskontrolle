//
// Created by kostia on 11/25/24.
//

#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <Arduino.h>
#include <WiFi.h>

class WiFiManager
{
public:
    WiFiManager(const char* ssid, const char* password);
    void connect();
    bool isConnected();
    void disconnect();

private:
    const char* ssid;
    const char* password;
};


#endif //WIFIMANAGER_H
