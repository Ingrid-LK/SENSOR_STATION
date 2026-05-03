
#ifndef READINGS_SYSTEM_H
#define READINGS_SYSTEM_H


enum _State{
    Normal, //0
    High_Temp //1
};

class readingsSystem
{
private:
    /* data */
    _State Temp_Level
public:
    //temperature reading
    //humidity reading
    //water level
    //publishing to mqtt broker
    readingsSystem(/* args */);
    ~readingsSystem();
};

readingsSystem::readingsSystem(/* args */)
{
}

readingsSystem::~readingsSystem()
{
}





#endif
