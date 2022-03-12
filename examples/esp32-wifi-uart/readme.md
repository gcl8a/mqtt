# MQTT example

A basic MQTT example for the ESP32 that uses non-blocking connection checking. The program will listen for strings of the form, `topic:message` on *both* `Serial` (for testing) and `Serial2` (for using the ESP32 as a WiFi board) and publish them to the MQTT broker of your choice. 

See the `readme.md` in the root directory for setting up credentials. You will need to set the team number at the top of `main.cpp`:

```
const int teamNumber <your_team_number>
```

The code also declares a simple *callback* function and subscribes to topics corresponding to your team number. Messages are printed by default to both `Serial` and `Serial2` in the same `topic:message` format (with the team name stripped). Note that by default, *any message you send to the broker will be repeated back* (since the code subscribes to all topics related to your team). To avoid this (and potenial deadlocks), edit the subscribed topics in `setup()`. For pointers on how to use wildcards, see [this page](https://www.ibm.com/docs/en/ibm-mq/7.5?topic=SSFKSJ_7.5.0/com.ibm.mq.javadoc.doc/WMQMQxrCClasses/wildcard.html).