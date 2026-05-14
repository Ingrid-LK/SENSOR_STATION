#if !defined(READ_SOIL_HUMIDITY_H)
#define READ_SOIL_HUMIDTY_H


enum _Wstate{
    dry,
    good
};

class readSoilHumidity
{
private:
    /* data */
    int sensor_pin;
    double soil_HMDT;
    double lowest_acceptable_HMDT;
    _Wstate soil_state;
public:
    readSoilHumidity(int pin);
    float getSoilHMDT();
    _Wstate getSoilHMDT_state();
};



#endif // MACRO
