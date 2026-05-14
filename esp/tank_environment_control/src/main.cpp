#include <Arduino.h>
#include <WiFi.h> //wifi library
#include <PubSubClient.h> //mqtt 

//custom objects
#include "ControlSystem.h"
#include "motorControl.h"
#include "PumpControl.h"
#include "readLM35.h"
#include "readDHT22.h"
#include "readSoilHumidity.h"
#include "readWaterLevel.h"
#include "readPhotoresistor.h"


//pins
const int motor_pin=1;
const int pot_pin= 2;
const int pump_pin=3;
const int lm35pin=4;
const int dht22pin=5;
const int soilsensorpin=6;
const int watersensorpin=7;
const int photorespin=8;

//initialize control and reading object class created
ControlSystem control;
motorControl motorcontrol(motor_pin, pot_pin);
PumpControl pumpcontrol(pump_pin);
readLM35 readtemp(lm35pin);
readDHT22 readHMDT(dht22pin);
readSoilHumidity readsoil(soilsensorpin);
readWaterLevel readWtrLevel(watersensorpin);
/*
readPhotoresistor readlighInt (photorespin);
*/






// Connections
const char* TOPIC_PUMP  = "control/pump";
const char* TOPIC_MOTOR = "control/motor";
const char* TOPIC_MODE  = "control/mode";

//  Credentials for WIFI Connection 
const char* ssid = "Cudy-4CC6";
const char* password = "password123";
const char* mqtt_server = "192.168.1.68";

//create an instance of a mqtt client object
WiFiClient TCP_Client;
PubSubClient client(TCP_Client);



// receive, convert, log and direct messages arrived
void callback(char* topic, byte* payload, unsigned int length) {
  
  //convert received payload into usable format
  String payloadRec = String ((char*) payload, length);
  

  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  Serial.println(payloadRec);

  //direct message received to control block
  control.onMessageReceived(topic, payloadRec); //from control cpp
}








//non blocking reconnect
/*If the client loses
 its connection, it attempts to reconnect without blocking the main loop. */
long lastReconnectAttempt = 0;
boolean reconnect() {
  if (client.connect("esp32_1")) {
    Serial.println("hello again, world");
    //insert subscribed topics
    client.subscribe(TOPIC_MODE);
    client.subscribe(TOPIC_MOTOR);
    client.subscribe(TOPIC_PUMP);
    return client.connected();} else {
    Serial.println("Reconnection failed.");
    return 0;}
}








void setup() {


//*******init pins******* */

















//***************init WiFi connection**********************
Serial.println(); 
Serial.print("Connecting to ");Serial.println(ssid);

WiFi.mode(WIFI_STA); // esp connects to access point (in this case, a router)
WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
  delay(500); //maybe since it's setup, only happens once, there isn't a big issue for a delay in here, it doesnt block much 
  Serial.print(".");}
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

//**********************MQTT****************************
// init MQTT client
client.setServer(mqtt_server, 1883); //set server 
client.setCallback(callback); //call back function so we can receive messages

//boolean connect (clientID, [username, password], [willTopic, willQoS, willRetain, willMessage], [cleanSession])
//connecting by providing our mqtt id
//gotta check the parameters because i actually want the will retain, i want when someone to connect be able to receive the last topic
client.connect("esp32_1","ing_at_home","limitless",NULL,NULL,NULL,NULL,false);


//subscribe to control topics
//subscribe(topic,qos)
client.subscribe("test");
client.subscribe("ctrMotor");
client.subscribe("ctrEVin");
client.subscribe("ctrEVout");

lastReconnectAttempt = 0; //dont actually know if it is still necessary after i have already written it on the top



// init sensors and actuator pins

}

void loop() {
  
//Non blocking way of keeping connection alive. Reconnection attempt with 5 seconds delay for each attempt. Non blocking loop
  if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    //client.loop checks if new mqtt message has arrived
    //Calls callback and handles keep alive method
    client.loop();
  }




// call reading:publishState()

//periodically call
// control::evaluateFlags()


 
}

