#include "readDHT22.h"
//extern DHT dht_read;

#include "DHT.h"


readDHT22::readDHT22(int pin) : dht(pin, DHT22)
{
hmdt_pin = pin;
}


//if it goes bad probably should be a char 
//and not simply float

 float readDHT22::get_hmdt(){
 if (millis() - last_read >= read_interval) {
  last_read = millis();

   unsigned char result = dht.read();
        if (result == DHT_OK) {
            hmdt_value = dht.humidity;
        } else {
            Serial.println("DHT read failed, error: ");
            Serial.println(result);
        }
      }
    
return hmdt_value;
     
}






/*
#define DHTPIN 2     // what pin we're connected to

DHT dht_read(DHTPIN, DHT22);
*/

  /*
void setup() 
{
    Serial.begin(9600); 
    Serial.println("************ DHTxx test! ************");
    delay(2000);
}


void loop() 
{
  switch(dht.read())
  {
    case DHT_OK:
      Serial.print("Humidity: "); 
      Serial.print(dht.humidity);
      Serial.print(" %\t");
      Serial.print("Temperature: "); 
      Serial.print(dht.temperature);
      Serial.println(" *C");
      break;
    case DHT_ERR_CHECK:
        Serial.println("DHT CHECK ERROR");break;
    case DHT_ERR_TIMEOUT:
        Serial.println("DHT TIMEOUT EEROR");break;
    default:
        Serial.println("UNKNOWN EEROR");break;
    }
    delay(2000);
}
*/