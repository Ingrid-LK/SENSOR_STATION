#include "readLM35.h"
#include <Arduino.h>



//class constructor
readLM35::readLM35(int pin_LM35){
Temp_pin = pin_LM35;
diode_offset_voltage = 0.87; //float type (put in header file); 2 diodes ~0.4 voltage drop each, my actual value measured
maximum_acceptable_temp = 35; //temperature can not be higher than 35 degrees
Temp_State = normal_temp;
}

void readLM35::setup(){
//analog readings dont need pinMode definition
 analogSetPinAttenuation(Temp_pin, ADC_11db);  // set attenuation specifically for LM35, forces allowing reading up to 3.3V

}


// Read and Return the temperature value
float readLM35::readTemp(){ //will it be float or double; also it gotta be public

float raw_adc_number = 0;

   //sensor reading delay
  if (millis() - last_read >= read_interval) {
        last_read = millis();
      // STEP 1 — Read the raw number from the ESP32 ADC (0 to 4095)
        for (int i = 0; i < 10; i++) {
          //+= simply means "add to itself":
            raw_adc_number += analogRead(Temp_pin); 
            delay(10); // change here
        }
        raw_adc_number = raw_adc_number / 10.0;  // average of readings to reduce noise
        
        // STEP 2 — Convert raw number to the voltage the LM35 is outputting
        float volts_from_sensor = raw_adc_number * (3.3 / 4095.0);

        // subtract the offset to recover the true sensor voltage
        float true_sensor_voltage = volts_from_sensor - diode_offset_voltage;

        // STEP 3 — Convert voltage to temperature
        // LM35 outputs 0.010V per degree
        temperature_in_celsius =  true_sensor_voltage/ 0.010;
      }
  return temperature_in_celsius;
    }



//return indicator that provides the temperature evaluation result
_State readLM35::gettempEval(){
if (temperature_in_celsius >= maximum_acceptable_temp){
Temp_State = high_temp;
} else {
Temp_State = normal_temp; 
}
return Temp_State;
}
