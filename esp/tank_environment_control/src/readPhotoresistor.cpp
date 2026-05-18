#include <Arduino.h>
#include "readPhotoresistor.h"

readPhotoresistor::readPhotoresistor(int pin){
  photo_pin = pin;
}

void readPhotoresistor::readPhoto(){
  if (millis() - last_read >= read_interval) {
        last_read = millis();
        photores_value= analogRead(photo_pin);

      //map(value, fromLow, fromHigh, toLow, toHigh)
        mapped_light_value = map (photores_value, 0, 4095, 0, 100);

        if (mapped_light_value <= 30){
          light_state = "LOW";
        }else {
          light_state = "GOOD";
        }
      }
}

String readPhotoresistor::getLightEval(){
return light_state;
}

