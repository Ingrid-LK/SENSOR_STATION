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
//if motor on flag is set, regulate the speed via the potentiometer

void motorControl::MotorON(){

//motor is ON, read pot and set speed
    potValue = analogRead(pot_pin); //int
    
    // only control speed with pot, not use it to turn off the motor    
   int motor_speed = map(potValue, 0, 4095, 1000, 4095);  // pot only controls upper half

    ledcWrite(0, motor_speed);
   


           motorRunning = true;

}




//message received to turn off controlSystem.cpp
void motorControl::MotorOFF(){

    ledcWrite(0, 0);

    motorRunning = false;

}


 





