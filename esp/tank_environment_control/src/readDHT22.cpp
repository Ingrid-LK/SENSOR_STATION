#include "readDHT22.h"
#include "DHT.h"


readDHT22::readDHT22(int pin){
hmdt_pin = pin;
}


//if it goes bad probably should be a char 
//and not simply float


float readDHT22::get_hmdt(){

DHT dht_read(hmdt_pin, DHT22);

 if (millis() - last_read >= read_interval) {
  last_read = millis();
    switch(dht_read.read())
    {
      case DHT_OK:
        hmdt_value=dht_read.humidity;
      return hmdt_value;
        break;
      case DHT_ERR_CHECK:
          Serial.println("DHT CHECK ERROR");break;
      case DHT_ERR_TIMEOUT:
          Serial.println("DHT TIMEOUT EEROR");break;
      default:
          Serial.println("UNKNOWN EEROR");break;
      }
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