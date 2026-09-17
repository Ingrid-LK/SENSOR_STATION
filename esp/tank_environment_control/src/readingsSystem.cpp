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





//define the constructor declaration
readingsSystem::readingsSystem(){
}


//Return/access sensor readings

float readingsSystem::getTempValue(){

    //access the value from lm35 sensor
    temp_value = readtemp.readTemp();
    return temp_value;
}


float readingsSystem::getHMDTvalue(){
    //access the value from DHT22 sensor
    hmdt_value = readHMDT.get_hmdt();
    return hmdt_value;

}

String readingsSystem::getWaterLevel(){
    //access the value from level sensor
    water_value = readWtrLevel.getWaterlevel();
    if (water_value == empty){
        water_level= "low"; 
    } else if (water_value == full){
        water_level= "full";
    }
return water_level;
}

String readingsSystem::getSoilHMDTvalue(){
    //access the value from soil 
    readsoil.getSoilHMDT();
    soil_state_string = readsoil.getSoilHMDT_state();
    switch (soil_state_string)
    {
    case dry: return "dry";
    case good: return "good";
    case excess: return "excess";
    default:    return "unknown";
    }
}

String readingsSystem::getPhotoresValue(){
    //access the value from 
    readlighInt.readPhoto();
    lighInt = readlighInt.getLightEval();
    return lighInt;
}

//orchestrate functions calling
void readingsSystem::evaluate(){
        getTempValue();
        getWaterLevel();
        getPhotoresValue();
        getHMDTvalue();
}

// Organizes control information that will be published via MQTT in JSON TEXT
String readingsSystem::publishReadings(){
    JsonDocument readsdoc; 

    readsdoc["temperature"]= temp_value;
    readsdoc["humidity"]= hmdt_value;
    readsdoc["light"] = lighInt;

    readsdoc["tank_level"]= water_level;


    readsdoc["soil_humidity"]= getSoilHMDTvalue();

String ReadingsOutput; // destination string for the updates

serializeJson(readsdoc, ReadingsOutput);

return ReadingsOutput; //String that will be published

}



