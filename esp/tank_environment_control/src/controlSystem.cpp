#include "ControlSystem.h"
#include <Arduino.h>
#include <ArduinoJson.h>


#include "motorControl.h"
extern motorControl motorcontrol; //extern, so the compiler can find the object initialized in the main.cpp

#include "PumpControl.h"
extern PumpControl pumpcontrol;

#include "readLM35.h"
extern readLM35 readtemp;

#include "readSoilHumidity.h"
extern readSoilHumidity readsoil;

#include "readWaterLevel.h"
extern readWaterLevel readWtrLevel;



//define the constructor declaration
ControlSystem::ControlSystem(){

//initialize every flag as false
modebool= 1; //0= Manual Control Mode; 1=Auto Control Mode (received via mqtt)
pump_on_request = false;
motor_on_request = false;
manual_on_request = false;
pump_set_on = false;
motor_set_on = false;
}

//receive and organize mqtt control messages
//already called by callback function in subscribe
void ControlSystem::onMessageReceived( char* topic, String payload){

    /*analyze the mqtt messages received,  then set flags used in other methods and return data so it can be accessed by other functions
     In Arduino, comparing a String with ""=="" to a string literal can work  but it's considered unreliable*/

topic_received = topic; 
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
            if(Temp_status == high_temp){ 
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
void ControlSystem::pumpControl(){
water_level_status = readWtrLevel.getWaterlevel();
soil_hmdt_status= readsoil.getSoilHMDT_state(); 

//if auto mode
if (manual_on_request == false){
    //if water tank level ok and soil humidity low
        if (water_level_status == full && soil_hmdt_status == dry  )
        {  /* code */
         pumpcontrol.PumpON();
         pump_set_on = true;
        } else if (water_level_status == empty || soil_hmdt_status == excess) 
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
if (manual_on_request == true){
        //if there is on request received 
        if (pump_on_request == true){ 
        pumpcontrol.PumpON();
        pump_set_on = true;} 
        else if (pump_on_request == false){
        // if there is off request received
        pumpcontrol.PumpOFF(); 
        pump_set_on = false;}
        

        }

    }


void ControlSystem::pumpAlarm(){


//if Manual Mode ^ WATER LEVEL LOW ^ PUMP ON REQUEST = TRUE --> SET ALARM flag
if (manual_on_request == true && pump_set_on == true && water_level_status == empty){
    pump_man_mode_alarm_flag = true;
} else {pump_man_mode_alarm_flag =false;}


//if Auto Mode ^ WATER LEVEL LOW ^ PUMP ON REQUEST = TRUE --> SET ALARM flag
// this is more like a warning because we alredy now the pump will not automatically turn on
if (manual_on_request == false && water_level_status == empty && soil_hmdt_status == dry){
    pump_auto_mode_alarm_flag = true;
} else {pump_auto_mode_alarm_flag= false;}



}






//orchestrate functions calling
void ControlSystem::controlevaluate(){
motorControl();
pumpControl();
pumpAlarm();
}

// Organizes control information that will be published via MQTT in JSON TEXT
String ControlSystem::publishControlStatus(){
    
 JsonDocument doc;  // where data will be written to 

//Fill the json document
// variable = (condition) ? "value if true" : "value if false";
doc["mode"] = (manual_on_request) ? "man" : "auto"; 
doc["motor"] = (motor_set_on) ? "on" : "off";
doc["pump"] = (pump_set_on) ? "on" : "off";
doc["pump_manual_alarm"] = (pump_man_mode_alarm_flag) ? "on" : "off";
doc["pump_auto_alarm"] = (pump_auto_mode_alarm_flag) ? "on" : "off";



String ControlOutput; // destination string for the updates

serializeJson(doc, ControlOutput);

return ControlOutput; //String that will be published
}


