//
// Created by kostia on 11/25/24.
//

#include "WiFiManager.h"

WiFiManager::WiFiManager(const char* ssid, const char* password)
    : ssid(ssid), password(password)
{
}

void WiFiManager::connect()
{
    if (WiFi.status() == WL_CONNECTED) return;

    Serial.print("Connecting to the Wi-Fi network: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nWi-Fi connection established!");
    Serial.print("IP-address: ");
    Serial.println(WiFi.localIP());
}

bool WiFiManager::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::disconnect()
{
    WiFi.disconnect();
    Serial.println("Wi-Fi is disconnected.");
}
