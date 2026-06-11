#include "readingsSystem.h"
#include <Arduino.h>
#include <ArduinoJson.h>


#include "readDHT22.h"
extern readDHT22 readHMDT;

#include "readLM35.h"
extern readLM35 readtemp;

#include "readSoilHumidity.h"
extern readSoilHumidity readsoil;

#include "readWaterLevel.h"
extern readWaterLevel readWtrLevel;


#include "readPhotoresistor.h"
extern readPhotoresistor readlighInt;





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
    hmdt_value = readHMDT.get_hmdt();
    return hmdt_value;

}

String readingsSystem::getWaterLevel(){
    //return/acess the value from level sensor
    water_value = readWtrLevel.getWaterlevel();
    if (water_value == empty){
        water_level= "low"; // changed empty to low because in real life the sensor was put higher than expected
    } else if (water_value == full){
        water_level= "full";
    }
return water_level;
}

String readingsSystem::getSoilHMDTvalue(){
    //return/acess the value from soil 
    readsoil.getSoilHMDT();
    soil_hmdt_value = readsoil.getSoilHMDT_state();
    switch (soil_state_string)
    {
    case dry: return "dry";
    case good: return "good";
    case excess: return "excess";
    default:    return "unknown";
    }
}

String readingsSystem::getPhotoresValue(){
    //return/acess the value from 
    readlighInt.readPhoto();
    lighInt = readlighInt.getLightEval();
    return lighInt;
}

//orchestrate functions calling
void readingsSystem::evaluate(){
        getTempValue();
//        getSoilHMDTvalue(); //maybe delete this
        getWaterLevel();
        getPhotoresValue();
        getHMDTvalue();
}


String readingsSystem::publishReadings(){
    JsonDocument readsdoc; 

    readsdoc["temperature"]= temp_value;
    readsdoc["humidity"]= hmdt_value;
    readsdoc["light"] = lighInt;

    readsdoc["tank_level"]= water_level;

    
   // readsdoc["soil_humidity"]=soil_hmdt_value;

    readsdoc["soil_humidity"]= getSoilHMDTvalue();

String ReadingsOutput; // destination string for the updates

serializeJson(readsdoc, ReadingsOutput);

return ReadingsOutput;

}



// now create a
//getAllReadings() //this is the thing that will be called in the main.cpp
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