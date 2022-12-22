#include <Arduino.h>
#include <PubSubClient.h>
#include <mqtt.h>
#include <button.h>

// use the button for forcing a message (for testing)
Button bootButton(0);

String rxString;
bool checkSerial(void)
{
    while(Serial.available())
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
    while(Serial2.available())
    {
        char c = Serial2.read();
        if(c == '\n') return true;
        else if (c != '\r') rx2String += c;
    }

    return false;
}

/**
 * publishMQTT parses a message (received as "topic:message" over Serial) 
 * and appends the topic/message to the team number and sends it to an MQTT broker.
 * The MQTT packet will have the format
 * 
 *      "teamN/topic/message"
 * 
 * */
bool publishMQTT(String& str)
{
    // for debugging; comment out if you don't need this
    Serial.println(str);

    /**
     * On the Serial, messages must be formatted topic:msg. If we don't find a colon, then 
     * ignore the message.
    */
    int iColon = str.indexOf(':');
    if(iColon == -1) 
    {
        Serial.println("Failed to find delimiter");
        str = "";
        return false;
    }

    /**
     * Checks if connected and attempts to reconnect. If we're not connected, we'll likely lose the 
     * message below, since it takes a moment to actually reconnect. You can make the connection blocking
     * by testing client.connected()
    */
    mqtt_reconnect(); 

    String topic = String("team") + String (teamNumber) + String('/') + str.substring(0, iColon);
    String message = str.substring(iColon + 1);

    bool success = client.publish(topic.c_str(), message.c_str());
    str = "";

    return success;
}

/**
 * callback() gets called whenever we receive a message for this team  
 * (i.e., "teamN"). It strips off the team name and sends "topic:message"
 * over the UART.
 * */
void callback(char* topic, byte *payload, unsigned int length) 
{
    // These two lines can be commented out; they are used for testing and don't affect functionality
    Serial.print("Full topic: ");
    Serial.println(topic);

    String strTopic(topic);

    Serial.print(strTopic.substring(strTopic.indexOf('/') + 1));
    Serial.print(':');  
    Serial.write(payload, length);
    Serial.println();

    Serial2.print(strTopic.substring(strTopic.indexOf('/') + 1));
    Serial2.print(':');  
    Serial2.write(payload, length);
    Serial2.println();
}

void setup() 
{
    Serial.begin(115200);
    delay(100);  //give us a moment to bring up the Serial

    Serial.println("setup()");

    Serial2.begin(115200);

    /**
     * Sets the callback function that gets called for every message received from the broker.
    */
    client.setCallback(callback);

    /**
     * We'll block while we connect. Connection can be done asynchronously, but we need to be connected
     * before we subscribe to topics.
    */
    while(!client.connected()) 
    {
        mqtt_reconnect();
    }

    /**
     * Subscribes to ALL topics for your team by default (including messages this robot sends!)
     * which is great for testing, but will eat up resources. Be sure to change your subscriptions
     * for the final implementation
    */
    String topics = String("team") + String(teamNumber) + String("/#");
    client.subscribe(topics.c_str());

    /**
     * Using button class, so must call init()
    */
    bootButton.init();

    Serial.println("/setup()");
}

void loop() 
{
    // mqtt_reconnect() tests for a cxn and reconnects, if needed
    if(!client.loop()) {mqtt_reconnect();}
    
    if(checkSerial()) publishMQTT(rxString);
    if(checkSerial2()) publishMQTT(rx2String);

    // For testing connectivity:
    if(bootButton.checkButtonPress()) {String bStr("robot1/button0:1"); publishMQTT(bStr);}    
}