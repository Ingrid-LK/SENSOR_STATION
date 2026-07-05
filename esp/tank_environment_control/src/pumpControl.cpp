#include "PumpControl.h"
#include <Arduino.h>


//define the constructor declaration
PumpControl::PumpControl(int pinprelay){
pump_relay_pin = pinprelay;
}

void PumpControl::setup(){
pinMode(pump_relay_pin, OUTPUT);
}


void PumpControl::PumpON(){
digitalWrite(pump_relay_pin,HIGH); //PUMP is on

}

    
void PumpControl::PumpOFF(){
digitalWrite(pump_relay_pin,LOW); // PUMP is off 


}
