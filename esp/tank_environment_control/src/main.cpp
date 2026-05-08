#include <Arduino.h>
#include <WiFi.h> //wifi library
#include <PubSubClient.h> //mqtt library

//variables for callback function
char received_topic[128];
byte received_payload[128];
unsigned int received_length;
bool received_msg = false;

//  Credentials for WIFI Connection 
const char* ssid = "Cudy-4CC6";
const char* password = "password123";
const char* mqtt_server = "192.168.1.68";

//create an instance of a mqtt client object
WiFiClient TCP_Client;
PubSubClient client(TCP_Client);



// Handle messages arrived
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  //read received payload till the end
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    messageTemp += (char)payload[i];
  }
  Serial.println();

  
  // Copy the payload to the new buffer, allowing data to persist outside the scope of the callback function
  //strcpy() is for topic strings
  //memcpy() for binary payloads
  strcpy(received_topic, topic);
  memcpy(received_payload, payload, length);
  received_msg = true;
  received_length = length;


  
 /* if (strcmp(topic,"pir1Status")==0){
    // whatever you want for this topic //i think it relates on acttions
  }

  if (strcmp(topic,"red")==0) {
    // obvioulsy state of my red LED
  }

  if (strcmp(topic,"blue")==0) {
    // this one is blue...
  }  

   if (strcmp(topic,"green")==0) {
   // i forgot, is this orange?
  }  */
}






//non blocking reconnect
/*If the client loses
 its connection, it attempts to reconnect without blocking the main loop. */
long lastReconnectAttempt = 0;
boolean reconnect() {
  if (client.connect("esp32_1")) {
    Serial.println("hello again, world");
    //insert subscribed topics
    client.subscribe("pir1Status");
    client.subscribe("red");
    client.subscribe("green");
    client.subscribe("blue");
    return client.connected();} else {
    Serial.println("Reconnection failed.");
    return 0;}
}








void setup() {

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
    // Client connected
    client.loop();
  }




  


// call reading:publishState()

//periodically call
// control::evaluateFlags()


 
}

