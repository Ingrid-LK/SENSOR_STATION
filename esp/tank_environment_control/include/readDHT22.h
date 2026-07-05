#if !defined(DHT22_H)
#define DHT22_H

#include "DHT.h"



class readDHT22
{
private:
    /* data */
    DHT dht;  // initialize DHT library

    int hmdt_pin;
    float hmdt_value;

      //timer functions
    unsigned long last_read = 0;
    
    //big interval to avoid interferring with other pins when reading DHT22
    unsigned long read_interval = 10000;  
    
public:
    readDHT22(int pin);
    float get_hmdt();
    

};



#endif // MACRO
