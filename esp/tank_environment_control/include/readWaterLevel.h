#if !defined(READ_WATER_LEVEL_H)
#define READ_WATER_LEVEL_H


enum _waterstate{
    empty,
    full
};



class readWaterLevel
{
private:
    /* data */
    int water_level;
    int level_sensor_pin;
    _waterstate waterstate;

    //timer functions
    unsigned long last_read = 0;
    unsigned long read_interval = 500;  

public:
    readWaterLevel(int sensor_pin);
    void setup();
    _waterstate getWaterlevel();
    
};




#endif // MACRO
