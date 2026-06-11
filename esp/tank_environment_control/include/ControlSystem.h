
#if !defined(CONTROL_SYSTEM_H)
#define CONTROL_SYSTEM_H

#include "readLM35.h" // so we guarantee Temp_status is persistently well defined
#include "readSoilHumidity.h"
#include "readWaterLevel.h"
#include <Arduino.h>


class ControlSystem
{
public:
    ControlSystem(); //class constructor
    void onMessageReceived(char* topic , String payloadRec);
    void motorControl();
    void pumpControl();
    void pumpAlarm();
    void controlevaluate();
    String publishControlStatus();

private:
    /* data */

char* topic_received;
String payload_received;

// my to be received topics
const char* TOPIC_PUMP  = "control/pump";
const char* TOPIC_MOTOR = "control/motor";
const char* TOPIC_MODE  = "control/mode";

//variables received via mqtt
bool pump_on_request;
bool motor_on_request;
bool manual_on_request;


//flags set after conditions evaluation
bool pump_set_on;
bool motor_set_on;
bool pump_man_mode_alarm_flag;
bool pump_auto_mode_alarm_flag;




int modebool; //contains the mode of control; 0= Manual Control Mode; 1=Auto Control Mode (received via mqtt as flag)
_State Temp_status;
_Hstate soil_hmdt_status;
_waterstate water_level_status;


};




#endif // MACRO

