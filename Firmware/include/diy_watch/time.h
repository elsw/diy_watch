#pragma once
#include "stdint.h"

namespace diy_watch 
{

class Time
{
public:
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
};

}