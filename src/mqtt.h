#pragma once

#if defined(ESP8266)
#include <ESP8266WiFi.h>  //ESP8266 Core WiFi Library
#elif defined(ESP32)
#include <WiFi.h>         //ESP32 Core WiFi Library
#else
#include <WiFi.h>
#endif

#include <PubSubClient.h>

bool wifi_reconnect(bool forceReconnect = false);
bool mqtt_reconnect(String* subscriptions, uint8_t subcount);

extern WiFiClient wifiClient;
extern PubSubClient client;
