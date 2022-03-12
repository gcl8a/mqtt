#pragma once

#if defined(ESP8266)
#include <ESP8266WiFi.h>  //ESP8266 Core WiFi Library
#elif defined(ESP32)
#include <WiFi.h>         //ESP32 Core WiFi Library
#else
#include <WiFi.h>
#endif

#include <PubSubClient.h>

void setup_wifi();
bool wifi_reconnect(void);
bool reconnect();
//void callback(char* topic, byte *payload, unsigned int length);
void setup_mqtt();

extern WiFiClient wifiClient;
extern PubSubClient client;
