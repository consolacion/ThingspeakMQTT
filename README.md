# ThingspeakMQTT
Using MQTT to upload data to Thingspeak
#
The regular way to upload values to Thingspeak is via the Thingspeak API. There is another way as well: through MQTT. Thingspeak has recently added an MQTT broker for this at mqtt.thingspeak.com:1883.

There are two topics one can use:
To upload more than 1 field in one go use:
channels/YOURchannelID/publish/YOURchannelAPI

To upload an individual channel use:
channels/YOURchannelID/publish/fields/field1/YOURchannelAPI (just using field1 as example)

In the first case, the payload string is as follows: field1=value1&field2=value2&status=MQTTPUBLISH

In the second case the payload string is just value1

In the program below I am using the PubSubClient from Knolleary. The "credentials.h" file is a file that defines my WiFi credentials, you can either create such a file yourself or just insert your wificredentials.

I am using an ESP8266 to make the connection but ofcourse it is also possible to use an Arduino with Ethernet connection when you make the proper changes  in this file in order to connect to Ethernet.

To avoid using again a DHT11 as an example, I show uploading variables by using micros() and a counter
