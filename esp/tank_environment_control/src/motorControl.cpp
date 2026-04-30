/*

//class construction
motorControl::motorControl(int pinmot, int pinpot){
motor_pin = pinmot;
pot_pin= pinpot;
motorRunnig = false; //boolean
}

//setup of pins of motor and pot
void motorControl::setup(){
pinMode (motor_pin, OUTPUT);
pinMode(pot_pin, INPUT);
//analog write/read is auto, isnt it?
}



//mqtt message received to turn on from controlSystem.cpp
//if motor on flag is set, regulate the speed via the potentiometer
//digital write pin
//void motorControl::MotorON(){

//motor is ON, read pot and set speed
    potValue = analogRead(pot); //int
    highTime = potValue;        //int, HIGH duration
    lowTime = 4096 - potValue;  //int, LOW duration

    
   motorRunning = true
        digitalWrite(pwmPin, HIGH);
        delayMicroseconds(highTime); // another alternative for delay
        digitalWrite(pwmPin, LOW);
        delayMicroseconds(lowTime);
}




//mqtt message received to turn off controlSystem.cpp
    //digital write pin
//void motorControl::MotorOFF(){

    digitalWrite(pwmPin, LOW);
    motorRunning = false;

}


    
//update the status page with the new state of motor
//HOWWWWWW? MY LOVE??????





*/