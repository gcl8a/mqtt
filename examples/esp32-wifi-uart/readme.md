# MQTT example

A basic MQTT example for the ESP32 that uses non-blocking connection checking. The program will listen for strings of the form, 

`topic:message` 

on *both* `Serial` (for testing) and `Serial2` (for using the ESP32 as a WiFi board) and publish them to the MQTT broker of your choice. 

See the `readme.md` in the root directory of this repo for how to set up credentials. 

For this example, you will need to set the team number at the top of `main.cpp`:

```
const int teamNumber = <your_team_number>;
```

The code also declares a simple *callback function* and subscribes to topics corresponding to your team number. Messages are printed by default to both `Serial` and `Serial2` in the same `topic:message` format (with the team name stripped). Note that by default, *any message you send to the broker will be repeated back* (since the code subscribes to all topics related to your team). To avoid this (and potenial deadlocks), edit the subscribed topics in `setup()`. The default functionality is good for testing.

For more information on MQTT, see [this page](https://www.hivemq.com/mqtt-essentials/). In particular, [Part 5](https://www.hivemq.com/blog/mqtt-essentials-part-5-mqtt-topics-best-practices/) explains the topic structure and how to use wildcards.

If you need a client for you computer, [MQTT Explorer](http://mqtt-explorer.com) is easy to use, but any client should work.
