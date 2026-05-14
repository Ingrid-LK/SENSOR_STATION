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
public:
    readWaterLevel(int sensor_pin);
    void setup();
    _waterstate getWaterlevel();
    
};




#endif // MACRO
