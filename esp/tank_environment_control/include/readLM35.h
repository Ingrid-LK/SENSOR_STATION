#if !defined(READ_LM35_H)
#define READ_LM35_H

enum _State{
    normal_temp, //0
    high_temp //1

};

class readLM35
{


private:
int Temp_pin;
double diode_offset_voltage;
int  maximum_acceptable_temp;
float temperature_in_celsius;
_State Temp_State;


 //timer functions
unsigned long last_read = 0;
unsigned long read_interval = 1000;   //previous was 2000
 
public:
readLM35(int pin);
void setup();
float readTemp();
_State gettempEval();



};




#endif // MACRO
