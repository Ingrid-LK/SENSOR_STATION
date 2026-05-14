#if !defined(MOTOR_CONTROL_H)
#define MOTOR_CONTROL_H


class motorControl
{


public:
    motorControl(int pinmot, int pinpot);
    void setup();
    void MotorON();
    void MotorOFF();
    

private:
    /* data */
    int motor_pin;
    int pot_pin;
    bool motorRunning;
    double potValue;
    double highTime;
    double lowTime;

};






#endif // MACRO
