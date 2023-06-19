#include <mqtt.h>
#include <wifi_credentials.h>

WiFiClient wifiClient;
PubSubClient client(wifiClient);

const uint32_t KEEP_ALIVE_INTERVAL = 120; // two minutes

uint32_t wifiCxnRetryInterval = 5000;
uint32_t lastWiFiCxnAttempt = -wifiCxnRetryInterval; // so we start right away
bool connecting = false;

/**
 * This is non-blocking. You must call it repeatedly if you want to check/ensure
 * a connection. It maintains an internal clock so that you can call reconnect as
 * often as you want, but it won't throttle (unless you assert forctReconnect).
*/
bool wifi_reconnect(bool forceReconnect)
{
  if(WiFi.status() != WL_CONNECTED)
  {
    if(millis() - lastWiFiCxnAttempt > wifiCxnRetryInterval || forceReconnect)
    {
      Serial.print("\nMy MAC address is ");
      Serial.print(WiFi.macAddress());

      Serial.print("\nConnecting to ");
      Serial.print(ssid);

      lastWiFiCxnAttempt = millis();

      WiFi.begin(ssid, password);

      connecting = true;
    }
  }

  // use separate if for when the above connects
  if(WiFi.status() == WL_CONNECTED)
  {
    // if we've trying to connect, let us know we succeeded
    if(connecting)
    {
      Serial.print("\nConnected with IP address: ");
      Serial.println(WiFi.localIP());

      connecting = false;
    }

    return true;
  }

  return false;
}

uint32_t lastMQTTCxnAttempt = 0;
uint32_t mqttCxnRetryInterval = 1500;

/**
 * Also non-blocking. It first checks to see if the wifi is connected and then 
 * attempts to connect to the MQTT broker. 
*/
bool mqtt_reconnect(void (*subscriptions)(void)) 
{
  bool wifi_cxn = wifi_reconnect();

  if(!wifi_cxn) return false;

  //try to reconnect once
  if(!client.connected()) 
  {
    if(millis() - lastMQTTCxnAttempt > mqttCxnRetryInterval)
    {
      lastMQTTCxnAttempt = millis();

      client.setServer(mqtt_server, mqtt_port);
      client.setKeepAlive(KEEP_ALIVE_INTERVAL);

      // Create client ID derived from this device's MAC address
      String clientId = "Client-";
      clientId += String(WiFi.macAddress());

      Serial.print("Attempting cxn as: ");
      Serial.println(clientId);
      
      // Attempt to connect
      if(client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) 
      {
        Serial.println("Connected to broker");
        subscriptions();
        return true;
      } 

      else 
      {
        Serial.print("Failed with Error = ");
        Serial.print(client.state());
        Serial.println("; will try again");

        return false;
      }
    }

    return false;
  }

  return true;
}
