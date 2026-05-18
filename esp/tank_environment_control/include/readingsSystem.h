
#ifndef READINGS_SYSTEM_H
#define READINGS_SYSTEM_H


#include "readDHT22.h"
#include "readLM35.h"
#include "readSoilHumidity.h"
#include "readWaterLevel.h"
#include "readPhotoresistor.h"




class readingsSystem
{
private:
    /* data */ 
  float temp_value;
  float soil_hmdt_value;
  String lighInt;
  float hmdt_value;
  _waterstate water_value; //dont know if i just dont get the state and send it via storage in other variable

public:
    //temperature reading
    //humidity reading
    //water level
    //publishing to mqtt broker
    readingsSystem();
    void evaluate();
    float getTempValue();
    float getSoilHMDTvalue();
    _waterstate getWaterLevel();
    String getPhotoresValue();// dont know if here comes value or mapping state
    float getHMDTvalue();
    String publishReadings();

};



#endif
