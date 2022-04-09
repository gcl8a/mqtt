#include <Arduino.h>

/**
 * sendMessage creates a string of the form
 *      topic:message
 * which is what the corresponding ESP32 code expects.
 * */
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

/**
 * This basic example sends the time (from millis()) to an MQTT broker every
 * five seconds. See the readme in the matching ESP32 code for instructions 
 * on how to set up credentials.
 * */
void loop() 
{
    static uint32_t lastSend = 0;
    uint32_t currTime = millis();
    if(currTime - lastSend >= 5000) //send every five seconds
    {
        lastSend = currTime;
        sendMessage("time", String(currTime));
    }
}