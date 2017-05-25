#include <AP_HAL/AP_HAL.h>
#include "DroniadaProxy.h"

//TODO: better to use AP_SerialManager here, like in ardupilot/libraries/AP_RangeFinder/AP_RangeFinder_LightWareSerial.cpp for example

extern const AP_HAL::HAL& hal;

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
    	hal.uartE->printf("%.3f second char: %c\n", AP_HAL::millis()*0.001f, c);
    }
    
}
