#include <AP_HAL/AP_HAL.h>
#include "DroniadaProxy.h"

extern const AP_HAL::HAL& hal;

void DroniadaProxy::init()
{
    if (hal.uartE == NULL) {
        return;
    }
    hal.uartE->begin(57600);
}

void DroniadaProxy::update()
{
    if (hal.uartE == NULL) {
        return;
    }
    hal.uartE->printf("Hello on uartE at %.3f seconds\n", AP_HAL::millis()*0.001f);
}
