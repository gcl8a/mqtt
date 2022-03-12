# MQTT Romi example

This example works with the `ESP32-wifi-uart` example to allow you to connect an ATmega32U4 (e.g., as on a [Pololu Romi](https://www.pololu.com/docs/0J69) or Arduino Leonardo) to an MQTT broker. The ESP32 will manage the MQTT connectivity; this code interacts with the ESP32 through a UART connection.

**Note that level-shifting is required or you will damage your ESP32.**

Connect `TXD1` on the 32U4 to `RX2` on the ESP32. **Level-shifting is required!** If you want to receive messages on the 32U4, you will need to connect `TX2` on the ESP32 to `RXD1` on the 32U4.

To send a message, use the `sendMessage()` function. See the code for the parameters.

Note that the ESP32 code relies on a newline character to recognize string termination. `Serial1` must be set up with a baud rate of 115200 (unless you change the ESP32 example, in which case you can use whatever you want, so long as they agree).

This example does not implement message reception. To receive messages, you'll need to write code to look for strings with the format, `topic:message`, on `Serial1`. As with sending messages, such strings are newline terminated. 

For more information on MQTT, see [this page](https://www.hivemq.com/mqtt-essentials/). In particular, [Part 5](https://www.hivemq.com/blog/mqtt-essentials-part-5-mqtt-topics-best-practices/) explains the topic structure and how to use wildcards.

If you need a client for you computer, [MQTT Explorer](http://mqtt-explorer.com) is easy to use, but any client should work.

If you need code to test your Serial connections, you can use the example code [here](https://github.com/gcl8a/romi-uart-comm).