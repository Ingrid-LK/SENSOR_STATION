#include "motorControl.h"
#include <Arduino.h>



//class construction
motorControl::motorControl(int pinmot, int pinpot){
motor_pin = pinmot;
pot_pin= pinpot;
motorRunning = false; //boolean
}


//setup of pins of motor and pot
void motorControl::setup(){
//pinMode (motor_pin, OUTPUT);
//pinMode(pot_pin, INPUT);
ledcSetup(0, 5000, 12); //5000khz
ledcAttachPin(motor_pin, 0);
//analog write/read is auto, isnt it?
}



//mqtt message received to turn on from controlSystem.cpp
//if motor on flag is set, regulate the speed via the potentiometer
//digital write pin

void motorControl::MotorON(){

//motor is ON, read pot and set speed
    potValue = analogRead(pot_pin); //int
    
    // i only want to control speed with pot, dont want it to turn off the motor    
   int motor_speed = map(potValue, 0, 4095, 1000, 4095);  // pot only controls upper half

    ledcWrite(0, motor_speed);
    /* highTime = potValue;        //int, HIGH duration
    lowTime = 4096 - potValue;  //int, LOW duration



    digitalWrite(motor_pin, HIGH);
        delayMicroseconds(highTime); // another alternative for delay
        digitalWrite(motor_pin, LOW);
        delayMicroseconds(lowTime);*/


           motorRunning = true;

}




//mqtt message received to turn off controlSystem.cpp
    //digital write pin
void motorControl::MotorOFF(){

    ledcWrite(0, 0);
    //digitalWrite(motor_pin, LOW);

    motorRunning = false;

}


    
//update the status page with the new state of motor
//HOWWWWWW? MY LOVE??????





