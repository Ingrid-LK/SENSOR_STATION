#include "motorControl.h"
#include <Arduino.h>




////define the constructor declaration
motorControl::motorControl(int pinmot, int pinpot){
motor_pin = pinmot;
pot_pin= pinpot;
motorRunning = false; //boolean
}


//setup of pins of motor and pot
void motorControl::setup(){
analogSetPinAttenuation(pot_pin, ADC_11db); //help reduce ADC interference between pins
    //To generate PWM signals or analog outputs on an ESP32 we use LEDC library
ledcSetup(0, 5000, 12); //5000khz
ledcAttachPin(motor_pin, 0);
}



//instruction received to turn on from controlSystem.cpp
// this method is called
//if motor on flag is set, regulate the speed via the potentiometer
void motorControl::MotorON(){

// dummy read to clear previous ADC pin crosstalk
analogRead(pot_pin);
delay(50);

//motor is ON, read pot and set speed
potValue = analogRead(pot_pin); //int
    
int motor_speed; 

    // only control speed with pot, not use it to turn off the motor    
  if (potValue < 100) {  // pot was not touched
        motor_speed = 2000;  // default startup speed
    } else {

        motor_speed = map(potValue, 0, 4095, 1000, 4095);  // pot only controls upper half
    }

ledcWrite(0, motor_speed);
   


motorRunning = true;

}


//message received to turn off 
//this method is called in controlSystem.cpp
void motorControl::MotorOFF(){

    ledcWrite(0, 0);

    motorRunning = false;

}


 








/*


#include "motorControl.h"
#include <Arduino.h>




////define the constructor declaration
motorControl::motorControl(int pinmot, int pinpot){
motor_pin = pinmot;
pot_pin= pinpot;
motorRunning = false; //boolean
}


//setup of pins of motor and pot
void motorControl::setup(){

    //To generate PWM signals or analog outputs on an ESP32 we use LEDC library
ledcSetup(0, 5000, 12); //5000khz
ledcAttachPin(motor_pin, 0);
}



//instruction received to turn on from controlSystem.cpp
// this method is called
//if motor on flag is set, regulate the speed via the potentiometer
void motorControl::MotorON(){

//motor is ON, read pot and set speed
    potValue = analogRead(pot_pin); //int
    
    // only control speed with pot, not use it to turn off the motor    
   int motor_speed = map(potValue, 0, 4095, 1000, 4095);  // pot only controls upper half

    ledcWrite(0, motor_speed);
   


           motorRunning = true;

}


//message received to turn off 
//this method is called in controlSystem.cpp
void motorControl::MotorOFF(){

    ledcWrite(0, 0);

    motorRunning = false;

}



*/