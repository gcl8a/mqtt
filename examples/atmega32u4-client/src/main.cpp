#include <Arduino.h>

void sendMessage(const String& topic, const String& message)
{
    Serial1.println(topic + String(':') + message);
}

void setup() 
{
    Serial.begin(115200);
    delay(500);  //give it a moment to bring up the Serial

    Serial.println("setup()");

    Serial1.begin(115200);

    Serial.println("/setup()");
}

void loop() 
{
    static uint32_t lastSend = 0;
    uint32_t currTime = millis();
    if(currTime - lastSend > 5000) //send every five seconds
    {
        lastSend = currTime;
        sendMessage("time", String(currTime));
    }
}