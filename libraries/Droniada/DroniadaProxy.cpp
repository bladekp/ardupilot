#include <AP_HAL/AP_HAL.h>
#include "DroniadaProxy.h"
#include <queue>

//TODO: better to use AP_SerialManager here, like in ardupilot/libraries/AP_RangeFinder/AP_RangeFinder_LightWareSerial.cpp for example

extern const AP_HAL::HAL& hal;

unsigned char buff[3];
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
        unsigned char c = hal.uartE->read();
    	if (data_length < 2){
		if (c == 0x05){
			data_length++;
		} else {
			data_length = 0;
		}
		break;	
	}
	buff[data_length++ - 2] = c;
	if(data_length == 5){
		data_length = 0;
		DroniadaItem* d = new DroniadaItem;
		d->major = buff[0];
		d->minor = buff[1];
		d->rssi = buff[2];
		d->micros64 = AP_HAL::micros64();
		beacons.push(d);
		//hal.uartD->printf("Beacon %d %d %d",buff[0], buff[1], buff[2]);
	}
    }
    
}
