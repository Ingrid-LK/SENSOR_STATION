#include "readingsSystem.h"
#include <Arduino.h>

#include "readDHT22.h"
extern readDHT22 readHMDT;

#include "readLM35.h"
extern readLM35 readtemp;

#include "readSoilHumidity.h"
extern readSoilHumidity readsoil;

#include "readWaterLevel.h"
extern readWaterLevel readWtrLevel;

/*
#include "readPhotoresistor.h"
extern readPhotoresistor readLighInt;
*/




//class constructor
readingsSystem::readingsSystem(){
}

float readingsSystem::getTempValue(){
    //return/acess the value from lm35 sensor
    temp_value = readtemp.readTemp();
    return temp_value;
}


float readingsSystem::getHMDTvalue(){
    //return/acess the value from DHT22 sensor
    //hmdt_value = readHMDT.

}

int readingsSystem::getWaterLevel(){
    //return/acess the value from level sensor
    water_value = readWtrLevel.getWaterlevel();
    return water_value;
}

float readingsSystem::getSoilHMDTvalue(){
    //return/acess the value from soil sensor
    soil_hmdt_value = readsoil.getSoilHMDT();
    return soil_hmdt_value;
}

float readingsSystem::getPhotoresValue(){
    //return/acess the value from photoresistor
    //lighInt = readLighInt.
}

// now create a
getAllReadings() //this is the thing that will be called in the main.cpp
                //it will encapsulate everything and you wont need to call each of them

//that organizes all the data in a array and then in the json document
//that will be sent via mqtt

/*
//publish sensor data
readingsSystem::publishReadings(){
    //send sensor data gathered by the previous functions
    //via mqtt
    }


*/