#include "readSoilHumidity.h"
#include <Arduino.h>


//class construction
readSoilHumidity::readSoilHumidity(int pin){
sensor_pin = pin;
lowest_acceptable_HMDT = 30.0; // don't know yet the real values to insert
soil_state = dry;
}

//return humidity reading value
float readSoilHumidity::getSoilHMDT(){
    soil_HMDT = analogRead(sensor_pin);
return soil_HMDT;
delay(500); //already know we gotta change here
}

//return indicator that provides the soil humidity evaluation result
_Wstate readSoilHumidity::getSoilHMDT_state(){
    if (soil_HMDT < lowest_acceptable_HMDT){
    soil_state = dry;
    } else {
    soil_state = good;
    }
 return soil_state;
    }


