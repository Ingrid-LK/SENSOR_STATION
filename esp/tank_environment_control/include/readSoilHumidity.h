#if !defined(READ_SOIL_HUMIDITY_H)
#define READ_SOIL_HUMIDITY_H


enum _Hstate{
    dry,
    good,
    excess
};




class readSoilHumidity
{
private:
    /* data */
    int sensor_pin;
    double soil_HMDT;
    //analogRead=4095 dry soil; from 2120 wet/good; from 1470 excess water
    double lowest_acceptable_HMDT;
    double max_acceptable_HMDT;
    int percentage_hmdt;
    _Hstate soil_state;



    //timer functions
    unsigned long last_read = 0;
    unsigned long read_interval = 500;  
    
public:
    readSoilHumidity(int pin);
    float getSoilHMDT();
    _Hstate getSoilHMDT_state();
};



#endif // MACRO
