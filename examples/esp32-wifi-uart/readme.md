## MQTT example

A basic MQTT example with non-blocking connection checking.

You will need to create a file, wifi_credentials.h, that declares both:

the wifi credentials:

const char* ssid = "<your ssid>";
const char* password = "<your network password>";

and mqtt credentials:

 const char* mqtt_server = "<mqtt-server-name>";
 #define mqtt_port <mqtt port>
 #define MQTT_USER "<username>"
 #define MQTT_PASSWORD "<password>"
