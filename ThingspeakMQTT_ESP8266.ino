#include "PubSubClient.h"
#include <ESP8266WiFi.h> //ESP8266WiFi.h
#include <credentials.h>  //This is a personal file containing web credentials

const char* ssid = WAN_SSID;
const char* password = WAN_PW;

char* topic = "channels/<YOURchannelID>/publish/<YOURchannelAPI>"; //channels/<channelID>/publish/API
char* server = "mqtt.thingspeak.com";

WiFiClient wifiClient;
PubSubClient client(server, 1883, wifiClient);

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}


void setup() {
  Serial.begin(115200);
  delay(10);
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

String clientName="ESP-Thingspeak";
  Serial.print("Connecting to ");
  Serial.print(server);
  Serial.print(" as ");
  Serial.println(clientName);
  
  if (client.connect((char*) clientName.c_str())) {
    Serial.println("Connected to MQTT broker");
    Serial.print("Topic is: ");
    Serial.println(topic);
    
    if (client.publish(topic, "hello from ESP8266")) {
      Serial.println("Publish ok");
    }
    else {
      Serial.println("Publish failed");
    }
  }
  else {
    Serial.println("MQTT connect failed");
    Serial.println("Will reset and try again...");
    abort();
  }
}

void loop() {
  static int counter = 0;
  String payload="field1=";
  payload+=micros();
  payload+="&field2=";
  payload+=counter;
  payload+="&status=MQTTPUBLISH";
  
  if (client.connected()){
    Serial.print("Sending payload: ");
    Serial.println(payload);
    
    if (client.publish(topic, (char*) payload.c_str())) {
      Serial.println("Publish ok");
    }
    else {
      Serial.println("Publish failed");
    }
  }
  ++counter;
  delay(20000);
}


