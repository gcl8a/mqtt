# MQTT client example

This example runs on an ATmega32U4 (e.g., as on a [Pololu Romi](https://www.pololu.com/docs/0J69)) and can be used to test the ESP32 code in a separate example.

**Note that level-shifting is required or you will damage your ESP32.**

Connect `TXD1` on the 32U4 to `RX2` on the ESP32. **Level-shifting is required!** If you want to receive messages on the 32U4, you will need to connect `TX2` on the ESP32 to `RXD1` on the 32U4.

To send a message, simple call, as demonstrated in `sendMessage()`:

```
Serial1.println("<topic>:<message>");
```
Note that the ESP32 code relies on a newline character to recognize string termination. `Serial1` must be set up with a baud rate of 115200 (unless you change the ESP32 example, in which case you can use whatever you want, so long as they agree).

To receive messages, you'll need to write code to look for strings with the format, `topic:message`, on `Serial1`. As with sending messages, such strings are newline terminated. This example does not implement message reception.

For more information on MQTT, see [this page](https://www.hivemq.com/mqtt-essentials/). In particular, [Part 5](https://www.hivemq.com/blog/mqtt-essentials-part-5-mqtt-topics-best-practices/) explains the topic structure and how to use wildcards.

If you need a client for you computer, [MQTT Explorer](http://mqtt-explorer.com) is easy to use, but any client should work.