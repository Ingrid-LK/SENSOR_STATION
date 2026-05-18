#if !defined(DHT22_H)
#define DHT22_H

#include "DHT.h"



class readDHT22
{
private:
    /* data */
    int hmdt_pin;
    float hmdt_value;

      //timer functions
    unsigned long last_read = 0;
    unsigned long read_interval = 500;  
    
public:
    readDHT22(int pin);
    float get_hmdt();
};



#endif // MACRO
