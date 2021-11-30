# mqtt
 wrapper for PubSubClient

You'll need to make wifi_credentials.h, that contains:

const char* ssid = "<your ssid>";
const char* password = "<your network password>";

for example,

// WPI Open
 const char* ssid = "WPI-Open";
 const char* password = "";

//RBE
const char* ssid = "RBE";
const char* password = "";

And mqtt credentials:

// cloudmqtt credentials
const char* mqtt_server = "<mqtt-server-name>";
#define mqtt_port <mqtt port>
#define MQTT_USER "<username>"
#define MQTT_PASSWORD "<password>"

for example

// robomqtt credientials
const char* mqtt_server = "robomqtt.cs.wpi.edu";
#define mqtt_port 1883
#define MQTT_USER "<teamNN>"
#define MQTT_PASSWORD "<password provided>"
