#include <AP_HAL/AP_HAL.h>
#include "DroniadaProxy.h"

//TODO: better to use AP_SerialManager here, like in ardupilot/libraries/AP_RangeFinder/AP_RangeFinder_LightWareSerial.cpp for example

extern const AP_HAL::HAL& hal;

//TODO move this typedef to header file
typedef struct droniada 
{
    unsigned char major; //1B
    unsigned char minor; //1B
    unsigned short int rssi; //2B
    unsigned long int crc; //8B
} Droniada;

unsigned char buff[12];
int data_length = 0;

void DroniadaProxy::init()
{
    if (hal.uartE == NULL) {
        return;
    }
    hal.uartE->begin(57600);
}

//currently 10Hz loop
void DroniadaProxy::update()
{
    if (hal.uartE == NULL) {
        return;
    }
    
    int16_t nbytes = hal.uartE->available();
    while (nbytes-- > 0) {
        char c = hal.uartE->read();
    	if (data_length < 2){
		if (c == 0x33){ //TODO: change to 0xAA
			data_length++;
		} else {
			data_length = 0;
		}
		break;	
	}
	buff[data_length++ - 2] = c;
	if(data_length == 14){
		data_length = 0;
		Droniada d;
		d.major = buff[0];
		d.minor = buff[1];
		d.rssi = (buff[3] << 8) + buff[2];
		//TODO d.crc = ... , and check CRC
		hal.uartE->printf("Major: %c Minor: %c, Rssi: %d,", d.major, d.minor, d.rssi);
	}
    }
    
}
