#include "readSoilHumidity.h"
#include <Arduino.h>


//class construction
readSoilHumidity::readSoilHumidity(int pin){
sensor_pin = pin;
lowest_acceptable_HMDT = 2500; // analog reading
soil_state = dry;
}

//return humidity reading value
float readSoilHumidity::getSoilHMDT(){
    soil_HMDT = analogRead(sensor_pin);
    percentage_hmdt = map(soil_HMDT, 490, 4095, 100, 0);  // 4095 means dry soil, Map the analog value to a percentage value between 0 and 100
return percentage_hmdt;
delay(500); //already know we gotta change here
}

//return indicator that provides the soil humidity evaluation result
_Hstate readSoilHumidity::getSoilHMDT_state(){
    if (soil_HMDT <= lowest_acceptable_HMDT){
    soil_state = dry;
    } else if (soil_HMDT > max_acceptable_HMDT)
    {
        soil_state = excess;
    }else {
    soil_state = good;
    }
 return soil_state;
    }


