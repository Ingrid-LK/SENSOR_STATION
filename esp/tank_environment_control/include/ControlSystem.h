

#if !defined(CONTROL_SYSTEM_H)
#define CONTROL_SYSTEM_H

#include "readLM35.h" // so we guarantee Temp_status is persistently well defined


class ControlSystem
{

public:
    ControlSystem(); //class constructor
    void onMessageReceived(char* topic , String payloadRec);
    void motorControl();
    void pumpControl();
    String publishControlIns();

private:
    /* data */

char* topic_received;
String payload_received;

// my topics
const char* TOPIC_PUMP  = "control/pump";
const char* TOPIC_MOTOR = "control/motor";
const char* TOPIC_MODE  = "control/mode";

//variables
bool pump_on_request;
bool motor_on_request;
bool manual_on_request;
int modebool; //contains the mode of control; 0= Manual Control Mode; 1=Auto Control Mode (received via mqtt as flag)
_State Temp_status;



};




#endif // MACRO

