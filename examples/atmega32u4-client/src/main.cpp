#include <Arduino.h>
#include <Button.h>

Button buttonA(14);

/**
 * sendMessage creates a string of the form
 *      topic:message
 * which is what the corresponding ESP32 code expects.
 * */
void sendMessage(const String& topic, const String& message)
{
    Serial1.println(topic + String(':') + message);
}

String serString1;
bool checkSerial1(void)
{
    while(Serial1.available())
    {
        char c = Serial1.read();
        serString1 += c;

        if(c == '\n')
        {
            return true;
        }
    }

    return false;
}

void setup() 
{
    Serial.begin(115200);
    delay(100);  //give it a moment to bring up the Serial

    Serial.println("setup()");

    Serial1.begin(115200);
    digitalWrite(0, HIGH); // Set internal pullup on RX1 to avoid spurious signals

    buttonA.init();

    Serial.println("/setup()");
}

/**
 * This basic example sends the time (from millis()) every
 * five seconds. See the `readme.md` in the root directory of this repo for 
 * how to set up the WiFi. 
 * */
void loop() 
{
    static uint32_t lastSend = 0;
    uint32_t currTime = millis();
    if(currTime - lastSend >= 5000) //send every five seconds
    {
        lastSend = currTime;
        sendMessage("timer/time", String(currTime));
    }

    // Check to see if we've received anything
    if(checkSerial1())
    {
        Serial.print("Rec'd:\t");
        Serial.print(serString1);
        serString1 = "";
    }

    // Defaults to just sending one message, but increase the message count
    // if you want to test how fast you can send
    static int msgCountToSend = 0;
    if(buttonA.checkButtonPress()) msgCountToSend = 1;

    while(msgCountToSend)
    {
        sendMessage("button/time", String(currTime + msgCountToSend--));
    }
}