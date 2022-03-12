# MQTT example

A basic MQTT example for the ESP32 that uses non-blocking connection checking. The program will listen for strings of the form, `topic:message` on *both* `Serial` (for testing) and `Serial2` (for using the ESP32 as a WiFi board) and publish them to the MQTT broker of your choice. 

See the `readme.md` in the root directory for setting up credentials. You will need to set the team number at the top of `main.cpp`:

```
const int teamNumber <your_team_number>
```

The code also declares a simple *callback* function and subscribes to topics corresponding to your team number. Messages are printed by default to both `Serial` and `Serial2` in the same `topic:message` format (with the team name stripped).