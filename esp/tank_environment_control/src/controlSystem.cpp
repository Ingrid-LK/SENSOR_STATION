#include "ControlSystem.h"
#include <Arduino.h>
#include <ArduinoJson.h>


#include "motorControl.h"
extern motorControl motorcontrol; //so the compiler can find the object initialized in the main.cpp

#include "PumpControl.h"
extern PumpControl pumpcontrol;

#include "readLM35.h"
extern readLM35 readtemp;

#include "readSoilHumidity.h"
extern readSoilHumidity readsoil;

#include "readWaterLevel.h"
extern readWaterLevel readWtrLevel;



//class construction
ControlSystem::ControlSystem(){

//initialize by everything off
modebool= 1; //0= Manual Control Mode; 1=Auto Control Mode (received via mqtt as flag)
pump_on_request = false;
motor_on_request = false;
manual_on_request = false;
pump_set_on = false;
motor_set_on = false;
}

//receive control instructions and organize mqtt messages received
//already called by callback function in subscribe
void ControlSystem::onMessageReceived( char* topic, String payload){

    /*analyze the mqtt messages received, 
then set flags used in other voids
//returnnnnn data so it can be accessed by other functions
////In Arduino, comparing a String with == to a string literal can work 
but it's considered unreliable*/

//member variables are where we store the data we use
topic_received = topic; //you're making it a string, can you do it or call a char instead?
payload_received = payload;

//Analyse and set flags according to the message received
if (strcmp(topic_received, TOPIC_MODE) == 0){
    if(payload_received.equals("manual")){
        manual_on_request= true;} else if 
        (payload_received.equals("auto"))
        {
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





//Motor Control
void ControlSystem::motorControl(){
Temp_status = readtemp.gettempEval();
    //if auto mode
if (manual_on_request == false){
        //if temperatature is not within the acceptable threshold
            if(Temp_status == high_temp){ //these variables gotta be extern or public in class
            //call function that turns on motor 
            motorcontrol.MotorON();
            motor_set_on = true;}
        // if temperature is within acceptable 
        else if (Temp_status != high_temp){
            //call function that turn off the motor
            motorcontrol.MotorOFF();
            motor_set_on= false;}
        }

// if manual mode
if (manual_on_request == true){
    //if there is on request received
    if (motor_on_request == true){ 
    //call function that turns on motor
        motorcontrol.MotorON();
        motor_set_on=true;
    }
    // if there is off request received
    else if (motor_on_request == false){
        //call function that turns off the motor
        motorcontrol.MotorOFF();
        motor_set_on=false; 
}
}
}




//control pump
// tentar usar switch case aqui, just for vibes
void ControlSystem::pumpControl(){
water_level_status = readWtrLevel.getWaterlevel();
soil_hmdt_status= readsoil.getSoilHMDT_state(); 
//falta get humidity and water level read

//if auto mode
if (manual_on_request == false){
    //if water tank level ok and soil humidity low
        if (water_level_status == full && soil_hmdt_status == dry  )
        {  /* code */
         pumpcontrol.PumpON();
         pump_set_on = true;
        } else if (water_level_status == empty || soil_hmdt_status == excess) //|| soul_hmdt_status == good; i still dont think humidity should turn off my water pump
        {
            //if soil humidity high [within the acceptable threshold]
        pumpcontrol.PumpOFF();
        pump_set_on = false;
        }
      
    }
//if water tank level low and soil humidity low
//if (manual_on_request == false && alarmflagset)  
//pumpcontrol.PumpAlarm(); //you stop pump and forward an alarm message
    

    // if manual mode
    // if manual mode
if (manual_on_request == true){
        //if there is on request received 
        if (pump_on_request == true){ 
        pumpcontrol.PumpON();
        pump_set_on = true;} 
        else if (pump_on_request == false){
        // if there is off request received
        pumpcontrol.PumpOFF(); 
        pump_set_on = false;}
        
        //if waterlevel is low and you try to turn on the pump  
//        pumpcontrol.PumpAlarmManual();

        }

    }


void ControlSystem::pumpAlarm(){


//if Manual Mode ^ WATER LEVEL LOW ^ PUMP ON REQUEST = TRUE --> SET ALARM flag
// This would be a extreme priority alarm
if (manual_on_request == true && pump_set_on == true && water_level_status == full){
    pump_man_mode_alarm_flag = true;
} else {pump_man_mode_alarm_flag =false;}





// this is more like a warning because we alredy now the pump will not turn on
//but the gist is that we want it to turn on
if (manual_on_request == false && water_level_status == empty && soil_hmdt_status == dry){
    pump_auto_mode_alarm_flag = true;
} else {pump_auto_mode_alarm_flag= false;}



}











/* what in essence gotta be done
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);

*/

//orchestrate functions calling
void ControlSystem::controlevaluate(){
motorControl();
pumpControl();
pumpAlarm();
}

// Method that organizes control information that will be published via MQTT
String ControlSystem::publishControlStatus(){
    
 JsonDocument doc;  // where my data will live

//Fill the json document
// variable = (condition) ? "value if true" : "value if false";
doc["mode"] = (manual_on_request) ? "man" : "auto"; //man or auto
doc["motor"] = (motor_set_on) ? "on" : "off";
doc["pump"] = (pump_set_on) ? "on" : "off";
doc["pump_manual_alarm"] = (pump_man_mode_alarm_flag) ? "on" : "off";
doc["pump_auto_alarm"] = (pump_auto_mode_alarm_flag) ? "on" : "off";



String ControlOutput; 

serializeJson(doc, ControlOutput);

return ControlOutput; //String that will be published
}


