#include "readSoilHumidity.h"
#include <Arduino.h>


//class construction
readSoilHumidity::readSoilHumidity(int pin){
sensor_pin = pin;
lowest_acceptable_HMDT = 3000; // analog reading
max_acceptable_HMDT = 1700; //analog reading
soil_state = dry;
}

//return humidity reading value
float readSoilHumidity::getSoilHMDT(){

    if (millis() - last_read >= read_interval) {
        last_read = millis();
        soil_HMDT = analogRead(sensor_pin);
       // Serial.print("soil hmdt:");
       // Serial.println(soil_HMDT);
        //map(value, fromLow, fromHigh, toLow, toHigh)
        Serial.println(soil_HMDT);
        percentage_hmdt = map(soil_HMDT, 490, 4095, 100, 0);  // 4095 means dry soil, Map the analog value to a percentage value between 0 and 100
    }
return percentage_hmdt;
//delay(500); //already know we gotta change here
}

//return indicator that provides the soil humidity evaluation result
_Hstate readSoilHumidity::getSoilHMDT_state(){
    if (soil_HMDT >= lowest_acceptable_HMDT){
    soil_state = dry;
    } else if (soil_HMDT <= max_acceptable_HMDT)
    {
        soil_state = excess;
    }else {
    soil_state = good;
    }
    Serial.println(soil_state);
 return soil_state;
    }


