#include "ControlSystem.h"
#include <Arduino.h>




ControlSystem::ControlSystem(){

//initialize by everything off
modebool= 1; //0= Manual Control Mode; 1=Auto Control Mode (received via mqtt as flag)
pump_on_request = false;
motor_on_request = false;
manual_on_request = false;
}

//receive control instructions and organize mqtt messages received
void ControlSystem::onMessageReceived( char* topic, String payload){

    /*analyze the mqtt messages received, 
then set flags used in other voids
//returnnnnn data so it can be accessed by other functions
////In Arduino, comparing a String with == to a string literal can work 
but it's considered unreliable*/

//member variables are where we store the data we use
topic_received = topic;
payload_received = payload;

//Analyse and set flags according to the message received
if (strcmp(topic_received, TOPIC_MODE) == 0){
    if(payload_received.equals("man")){
        manual_on_request= true;} else {
        manual_on_request = false;
        }

    } 
    else if (strcmp(topic, TOPIC_MOTOR) == 0){
        if(payload_received.equals("on")){
        motor_on_request= true;} else {
        motor_on_request = false;
        }
    } 
    else if (strcmp(topic, TOPIC_PUMP) == 0){
        if(payload_received.equals("on")){
        pump_on_request= true;} else {
        pump_on_request = false;
        }

    }

    }



//dont know if it is needed or not 
/*int Control::evaluateFlags(){
//reads flags + sensor values, decides actions
return both of them
setMotorON //boolean 
setPumpON //boolean
}*/

//Motor Control
void ControlSystem::motorControl(){
//if auto mode
if (manual_on_request == false){
        //if temperatature is not within the acceptable threshold
            if(Temp_Level == High_Temp){ //these variables gotta be extern or public in class
            //call function that turns on motor 
            motorControl.MotorON();}
        // if temperature is within acceptable 
        else if (Temp_Level != High_Temp){
            //call function that turn off the motor
            motorControl.MotorOFF();}
        }

// if manual mode
if (manual_on_request == true){
    //if there is on request received
    if (motor_on_request == true){ 
    //call function that turns on motor
        motorControl.MotorON();
    }
    // if there is off request received
    else if (motor_on_request == false){
        //call function that turns off the motor
        motorControl.MotorOFF(); 
}
}
}




//control pump
// tentar usar switch case aqui, just for vibes
void controlSystem::pumpControl(){
//if auto mode
    //if water tank level ok and soil humidity low
        call pumpControl::PumpON

    //if soil humidity high [within the acceptable threshold]
        call pumpControl::PumpOFF
    
    //if water tank level low and soil humidity low
        call pumpControl::PumpAlarm //you stop pump and forward an alarm message
    


    // if manual mode
        //if there is on request received 
        call pumpControl::PumpON
        // if there is off request received
        call pumpControl::PumpOFF 
        //if waterlevel is low and you try to turn on the pump
        call pumpControl::PumpAlarmManual

}



  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);




//publish state of actuators via mqtt
void controlSystem::publishcontrolInst
//sends the message to esp to turn on or off actuators ??
Motorset //on or off
Pumpset //on or off
sendPumpAlarm
