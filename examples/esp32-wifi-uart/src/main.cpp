#include <Arduino.h>
#include <PubSubClient.h>
#include <mqtt.h>

const String teamName("team00/");

void setup() 
{
    delay(1000);

    Serial.begin(115200);
    Serial.println(F("Starting"));

    setup_mqtt();
}

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

    String topic = str.substring(0, iCol);
    topic = teamName + topic;
    String message = str.substring(iCol + 1);

    bool success = client.publish(topic.c_str(), message.c_str());
    str = "";

    return success;
}

void loop() 
{
    if(checkSerial()) publishMQTT(rxString);
    if(checkSerial2()) publishMQTT(rx2String);
}