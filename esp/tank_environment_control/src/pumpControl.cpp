#include "PumpControl.h"
#include <Arduino.h>


//class construction
PumpControl::PumpControl(int pinprelay){
pump_relay_pin = pinprelay;
}

void PumpControl::setup(){
pinMode(pump_relay_pin, OUTPUT);
digitalWrite(pump_relay_pin,HIGH); //after initializing , make sure PUMP is off by default
}


void PumpControl::PumpON(){
digitalWrite(pump_relay_pin,LOW); //PUMP is on

}

    
void PumpControl::PumpOFF(){
digitalWrite(pump_relay_pin,HIGH); // PUMP is off 


}
    

    // dont know what to do over here yet, since auto and manual is already in controlsystem.cpp
    // and over here we just should evaluate the conditions
    //if water tank level low and soil humidity low
bool PumpControl::PumpAlarmAuto(){ 
//you stop pump IF ON and forward an alarm message VIA MQTT
//return alarm message?
}

bool PumpControl::PumpAlarmManual(){
//if in manual mode and you try to turn on the pump and forward an alarm message VIA MQTT
//return alarm message?
}


