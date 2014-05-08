/*
MQTT example using Pub/Sub adaptation of LED "Blinky" introductory program
  - file: "led_mqtt.ino", v1.0 (ready for GitHub publishing)
  - connects to an MQTT server, either providing username
    and password (MQTT v3.1) or w/o them (version <= MQTT v3.0)
  - upon connecting to broker, publishes a topic; then, this client (Yun)
      attempts to subscibe to that same topic. If it is successful, the
      Yun will blink it's LED13 twice per second, every second that it's
      connected to the broker.
  
  - developed by German Kutsy, Litmus Automation LLC. (2014)
*/
#include <PubSubClient.h>
#include <YunClient.h>
#include <Bridge.h>

YunClient yun;

uint8_t server[] = {10,0,0,15};       // user input reqd
uint16_t port = 1883;                 // user input reqd

char* username = "rAnDoM_chars";      // user input reqd
char* password= "kgrem142";           // user input reqd
char* clientId = "Cliengratzi_2343";  // user input reqd
char* projectId = "LoopPersonalId";   // user input reqd
char* deviceName = "yun";             // user input reqd
char* jsonKV = "[Value:ON]";          // user input reqd
boolean cleanSession = true;

void callback(char *topic, byte *payload, unsigned int length) {
    // used for callback
}

// no username, no password (version <= MQTT v3.0)
PubSubClient litmus(server,port,callback,yun,clientId,projectId,deviceName,jsonKV,cleanSession);
// username/password used (MQTT v3.1)
//PubSubClient litmus(server,port,callback,yun,username,password,clientId,projectId,deviceName,jsonKV,cleanSession);

const int ledPin =  13; // the ONLY LED pin on Arduino Yun

void setup() {
  Bridge.begin();
  pinMode(ledPin, OUTPUT);
  litmus.loop();
  litmus.connect();
}

void loop() {
  litmus.publish("change_to_your_stream",jsonKV); // user input reqd
    
  boolean success = litmus.subscribe("change_to_your_stream"); // sub to pub'd topic above
  if (success) {
     digitalWrite(ledPin,HIGH);
     delay(400);
     digitalWrite(ledPin,LOW);
     delay(400);
  }
}

