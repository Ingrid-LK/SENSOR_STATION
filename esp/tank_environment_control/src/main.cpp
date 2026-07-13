#include <Arduino.h>
#include <WiFi.h> //wifi library
#include <PubSubClient.h> //mqtt 

//custom classes
#include "ControlSystem.h"
#include "motorControl.h"
#include "PumpControl.h"
#include "readLM35.h"
#include "readDHT22.h"
#include "readSoilHumidity.h"
#include "readWaterLevel.h"
#include "readPhotoresistor.h"
#include "readingsSystem.h"
#include "credentials.h"




//define necessary pins


const int motor_pin=17;
const int pot_pin= 34;
const int pump_pin=19;
const int lm35pin=36;
const int dht22pin=25;
const int soilsensorpin=33;
const int watersensorpin=23;
const int photorespin=35;

//timer variables
//control cpp evaluate timer
unsigned long last_c_evaluate=0;

//readings cpp evaluate timer
unsigned long last_r_evaluate=0;


//initialize control and reading object class created
ControlSystem control;
readingsSystem readings;
motorControl motorcontrol(motor_pin, pot_pin);
PumpControl pumpcontrol(pump_pin);
readLM35 readtemp(lm35pin);

//DHT dht_read(dht22pin, DHT22);
readDHT22 readHMDT(dht22pin);

readSoilHumidity readsoil(soilsensorpin);
readWaterLevel readWtrLevel(watersensorpin);
readPhotoresistor readlighInt (photorespin);







// Topics subscribed to
const char* TOPIC_PUMP  = "control/pump";
const char* TOPIC_MOTOR = "control/motor";
const char* TOPIC_MODE  = "control/mode";



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
  control.onMessageReceived(topic, payloadRec); //to control.cpp
}








//non blocking reconnect
/*If the client loses
 its connection, it attempts to reconnect without blocking the main loop. */
long lastReconnectAttempt = 0;
boolean reconnect() {
  if (client.connect("esp32_1",mqtt_user,mqtt_pass,"status/connection",1,true,"esp 32 offline",false))

  {
    client.publish("status/connection", "esp32 online", true); // to publish esp online again
    Serial.println("hello again, world");
    //insert subscribed topics
    // subscribe with QoS 1
    client.subscribe(TOPIC_MODE, 1);
    client.subscribe(TOPIC_MOTOR, 1);
    client.subscribe(TOPIC_PUMP, 1);
    return client.connected();} else {
    Serial.println("Reconnection failed.");
    Serial.println(client.state());
    return 0;}
}








void setup() {

Serial.begin(115200);

//*******init necessary pins******* */
readtemp.setup();
readWtrLevel.setup();
pumpcontrol.setup();
motorcontrol.setup();



//***************init WiFi connection**********************
Serial.println(); 
Serial.print("Connecting to ");Serial.println(wifi_ssid);

WiFi.mode(WIFI_STA); // esp connects to access point (in this project, a router)
WiFi.begin(wifi_ssid, wifi_password);

while (WiFi.status() != WL_CONNECTED) {
  delay(500);  
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
//QOS = 1 since is the standard in IOT
//clean session false — broker remembers the client and queues any missed QoS 1 messages while it was offline, delivering them when it reconnects
client.connect("esp32_1",mqtt_user,mqtt_pass,"status/connection",1,true,"esp 32 offline",false);


//subscribe to control topics
//subscribe(topic,qos)
client.publish("status/connection", "esp32 online", true); // to publish esp as online 

// subscribe with QoS 1
client.subscribe(TOPIC_MODE,1);
client.subscribe(TOPIC_MOTOR,1);
client.subscribe(TOPIC_PUMP,1);

Serial.println("MQTT ON"); //for debugging reasons



}

void loop() {

//MQTT SUBSCRIPTION
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



//MQTT PUBLISHING sensor data every 500ms
if (millis() - last_r_evaluate >= 500){
  last_r_evaluate = millis();
  readings.evaluate();
  /* topic:    "status/sensors"*/
  String r_payload = readings.publishReadings();
  //retained message = true
  client.publish("status/sensors", r_payload.c_str(), true);
  //Serial.println(r_payload); //debugging analog pins
}


//MQTT PUBLISHING New control status every 1500ms
if (millis() - last_c_evaluate >= 1500){
  last_c_evaluate= millis();  
  control.controlevaluate();  
  /* topic:    "status/control"
  payload:  {"pump":"on","motor":"off","pump_alarm":"off","motor_alarm":"off","mode":"auto"}*/
  String c_payload = control.publishControlStatus();
  //retained message = true
  client.publish("status/control", c_payload.c_str(), true);
  //Serial.println("sent actuator data");
}


}

