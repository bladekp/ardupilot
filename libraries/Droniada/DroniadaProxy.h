#pragma once

#include <queue>

class DroniadaItem
{
public:
    unsigned char major;
    unsigned char minor;
    unsigned char rssi;    
};

class DroniadaProxy
{
public:
    void init();
    void update();

    std::queue<DroniadaItem*> beacons;

};
