#pragma once

#include <queue>

class DroniadaItem
{
public:
    unsigned char major;
    unsigned char minor;
    unsigned char rssi;    
    uint64_t micros64;
};

class DroniadaProxy
{
public:
    void init();
    void update();

    std::queue<DroniadaItem*> beacons;

};
