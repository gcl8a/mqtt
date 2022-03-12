#include <Arduino.h>
#include <PubSubClient.h>
#include <mqtt.h>

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

void loop() 
{
    if(checkSerial())
    {   
        if(!client.connected()) 
        {
            reconnect();
        }

        client.publish("teamlewin/s0", rxString.c_str());

        Serial.println(rxString);
        rxString = "";
    }
    if(checkSerial2())
    {   
        if(!client.connected()) 
        {
            reconnect();
        }

        client.publish("teamlewin/s2", rx2String.c_str());

        Serial.println(rx2String);
        rx2String = "";
    }
}