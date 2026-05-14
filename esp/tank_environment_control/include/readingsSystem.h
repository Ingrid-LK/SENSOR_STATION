
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
  float lighInt;
  float hmdt_value;
  int water_value; //dont know if i just dont get the state and send it via storage in other variable

public:
    //temperature reading
    //humidity reading
    //water level
    //publishing to mqtt broker
    readingsSystem();
    float getTempValue();
    float getSoilHMDTvalue();
    int getWaterLevel();
    float getPhotoresValue();// dont know if here comes value or mapping state
    float getHMDTvalue();

};



#endif
