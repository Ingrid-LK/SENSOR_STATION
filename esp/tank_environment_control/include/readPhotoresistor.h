#ifndef READ_PHOTORESISTOR_H
#define READ_PHOTORESISTOR_H




class readPhotoresistor
{
private:
    /* data */
    int mapped_light_value;
    int photo_pin;
    float photores_value;
    String light_state;

    //timer functions
    unsigned long last_read = 0;
    unsigned long read_interval = 2000;  

public:
    readPhotoresistor(int pin);
    void readPhoto();
    String getLightEval();

};



#endif
