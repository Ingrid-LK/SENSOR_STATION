#if !defined(PUMP_CONTROL_H)
#define PUMP_CONTROL_H

class PumpControl
{
private:
    /* data */
    int pump_relay_pin;



public:
    PumpControl(int pinprelay);
    void setup();
    void PumpON();
    void PumpOFF();
    bool PumpAlarmAuto();
    bool PumpAlarmManual();
    
};




#endif // MACRO
