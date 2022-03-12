#include <Arduino.h>
#include <PubSubClient.h>
#include <mqtt.h>

const int teamNumber = 0;

String rxString;
bool checkSerial(void)
{
    if(Serial.available())
    {
        char c = Serial.read();
        if(c == '\n') return true;
        else if (c != '\r') rxString += c;
    }

    return false;
}

String rx2String;
bool checkSerial2(void)
{
    if(Serial2.available())
    {
        char c = Serial2.read();
        if(c == '\n') return true;
        else if (c != '\r') rx2String += c;
    }

    return false;
}

bool publishMQTT(String& str)
{
    Serial.println(str);

    int iCol = str.indexOf(':');
    if(iCol == -1) 
    {
        Serial.println("Failed to find delimiter");
        str = "";
        return false;
    }

    reconnect(); // checks if connected and attempts to reconnect

    String topic = String("team") + String (teamNumber) + String('/') + str.substring(0, iCol);
    String message = str.substring(iCol + 1);

    bool success = client.publish(topic.c_str(), message.c_str());
    str = "";

    return success;
}

void callback(char* topic, byte *payload, unsigned int length) 
{
    Serial.println(topic);
    Serial.print(':');  
    Serial.write(payload, length);
    Serial.println();

    Serial2.println(topic);
    Serial2.print(':');  
    Serial2.write(payload, length);
    Serial2.println();
}

void setup() 
{
    Serial.begin(115200);
    delay(500);  //give it a moment to bring up the Serial

    Serial.println("setup()");

    Serial2.begin(115200);

    setup_mqtt();

    client.setCallback(callback);

    String topics = String("team") + String(teamNumber);
    client.subscribe(topics.c_str());

    Serial.println("/setup()");
}

void loop() 
{
    if(checkSerial()) publishMQTT(rxString);
    if(checkSerial2()) publishMQTT(rx2String);
}