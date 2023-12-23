#pragma once 
#include "diy_watch/time.h"
#include <vector>

namespace diy_watch 
{

class USBSerial
{
public:
    enum class Command
    {
        GetBoardInfo = 's',
        SetTime = 't'
    };

    USBSerial();

    bool update(); ///< returns if a valid time is ready
    Time getTime();
private:
    Time time;
    std::vector<uint8_t> buffer;
};

}