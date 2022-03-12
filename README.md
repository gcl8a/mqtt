# mqtt

An Arduino wrapper for [PubSubClient](https://pubsubclient.knolleary.net) that manages connectivity. The wrapper functions make use of non-blocking connection checking. 

To use the library, you will need to create a file, `wifi_credentials.h`, that declares:

* WiFi credentials:

    ```
    const char* ssid = "<your ssid>";
    const char* password = "<your network password>";
    ```

* MQTT credentials:

    ```
    const char* mqtt_server = "<mqtt-server-name>";
    #define mqtt_port <mqtt port>
    #define MQTT_USER "<username>"
    #define MQTT_PASSWORD "<password>"
    ```

The `wifi_credentials.h` file can live wherever you want, so long as it can be found by the compiler. If you put it in the `src` folder of your project, be sure to add it to your `.gitignore` file. Better is to put it in a local directory on your machine and point to it using `lib_extra_dirs`. **You will need to edit `platformio.ini` to point to the correct directory.**