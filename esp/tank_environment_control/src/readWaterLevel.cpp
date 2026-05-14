#include "readWaterLevel.h"
#include <Arduino.h>

readWaterLevel::readWaterLevel(int sensor_pin){
level_sensor_pin= sensor_pin;
water_level = 0;// 1 <-> water present; 0<-> water not present
waterstate = full;
}

void readWaterLevel:: setup() {
  pinMode(level_sensor_pin, INPUT);
}

_waterstate readWaterLevel:: getWaterlevel(){

water_level = digitalRead(level_sensor_pin);

if (water_level == 0){
waterstate = empty;
} else if (water_level == 1){
waterstate = full;
}
return waterstate;

delay(500); // already know we gotta change here

}


/*
void loop() {
  // put your main code here, to run repeatedly:
      /*•	Low level output: < 0.1 V
      •	High level output: > 4.6 V  */
/*   liquidLevel = digitalRead(levelSensorPin);
    Serial.print("liquidLevel= "); 
    Serial.println(liquidLevel);
    delay(500);

*/