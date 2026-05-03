/*


controlSystem::controlSystem(bool mode){
modebool= mode //0= Manual Control Mode; 1=Auto Control Mode (received via mqtt as flag)
}

Control::onmessageReceived(){
//analyze the mqtt messages received, then set flags used in other voids
returnnnnn data so it can be accessed by other functions??
return both of them
setMotorON //boolean 
setPumpON //boolean
}

void controlSystem::motorControl(){
//if auto mode
    //if 
        //if temperatature is not within the acceptable threshold
            if(Temp_Level= High_Temp){
            call motorControl::MotorON}
        // if temperature is within acceptable 
        //elif (Temp_Level != High_Temp){
            call motorControl::MotorOFF}
// if manual mode
    //if there is on request received 
        call motorControl::MotorON
    // if there is off request received
        call motorControl::MotorOFF 
}






void controlSystem::pumpControl(){
//if auto mode
    //if water tank level ok and soil humidity low
        call pumpControl::PumpON

    //if soil humidity high [within the acceptable threshold]
        call pumpControl::PumpOFF
    
    //if water tank level low and soil humidity low
        call pumpControl::PumpAlarm //you stop pump and forward an alarm message
    


    // if manual mode
        //if there is on request received 
        call pumpControl::PumpON
        // if there is off request received
        call pumpControl::PumpOFF 
        //if waterlevel is low and you try to turn on the pump
        call pumpControl::PumpAlarmManual

}

void controlSystem::publishcontrolInst
//sends the message to esp to turn on or off actuators ??
setMotor
setPump
sendPumpAlarm

*/