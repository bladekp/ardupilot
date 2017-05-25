#pragma once

class DroniadaProxy
{
public:
    void init();
    void update();

    struct droniada 
    {
    	unsigned char major; //1B
    	unsigned char minor; //1B
    	unsigned short int rssi; //2B
    	unsigned long int crc; //8B
    } d;

};
