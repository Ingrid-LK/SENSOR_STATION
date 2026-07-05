
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
  String water_level;
  String soil_hmdt_value;
  String lighInt;
  
  _Hstate soil_state_string;
  float hmdt_value;
  _waterstate water_value; 

public:
    readingsSystem();
    void evaluate();
    float getTempValue();
    String getSoilHMDTvalue();
    String getWaterLevel();
    String getPhotoresValue();
    float getHMDTvalue();
    String publishReadings();

};



#endif
