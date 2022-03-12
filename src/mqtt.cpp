#include <mqtt.h>
#include <wifi_credentials.h>

WiFiClient wifiClient;
PubSubClient client(wifiClient);

const uint32_t KEEP_ALIVE_INTERVAL = 20;

void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println(WiFi.macAddress());
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

uint32_t lastWiFiCxnAttempt = 0;
uint32_t wifiCxnRetryInterval = 10000;

bool wifi_reconnect(void)
{
  if(WiFi.status() != WL_CONNECTED)
  {
    if(millis() - lastWiFiCxnAttempt > wifiCxnRetryInterval)
    {
      lastWiFiCxnAttempt = millis();
      WiFi.begin(ssid, password);
      
      randomSeed(micros());

      if(WiFi.status() == WL_CONNECTED) return true;
    }

    return false;
  }

  return true;
}

uint32_t lastCxnAttempt = 0;
uint32_t cxnRetryInterval = 1500;

bool reconnect() 
{
  if(!wifi_reconnect()) return false;

  //try to reconnect once
  if(!client.connected()) 
  {
    if(millis() - lastCxnAttempt > cxnRetryInterval)
    {
      lastCxnAttempt = millis();

      Serial.print("MQTT cxn...");
      
      // Create a random client ID
      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);
      
      // Attempt to connect
      if(client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) 
      {
        Serial.println("connected");
        return true;
      } 

      else 
      {
        Serial.print("failed, rc = ");
        Serial.print(client.state());
        Serial.println("; will try again");

        return false;
      }
    }

    return false;
  }

  return true;
}

void callback(char* topic, byte *payload, unsigned int length) 
{
    Serial.println(topic);
    Serial.print(':');  
    Serial.write(payload, length);
    Serial.println();
}

void setup_mqtt() 
{
    Serial.println("setup_mqtt");

    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
    // client.setCallback(callback);
    client.setKeepAlive(KEEP_ALIVE_INTERVAL);
    reconnect();

    Serial.println("/setup_mqtt");
}
