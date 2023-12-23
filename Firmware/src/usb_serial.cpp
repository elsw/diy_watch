#include "diy_watch/usb_serial.h"
#include "diy_watch/version.h"
#include "pico/stdlib.h"
#include <iostream>

namespace diy_watch 
{

constexpr uint timeout_us = 1000;

USBSerial::USBSerial()
{
    stdio_init_all();
}

bool USBSerial::update()
{
    buffer.clear();
    bool got_char = true;
    while(got_char)
    {
        int ret = getchar_timeout_us(timeout_us);
        if(ret != PICO_ERROR_TIMEOUT)
        {
            buffer.push_back(ret);
        }
        else
        {
            got_char = false;
        }
    }

    if(buffer.size() > 0)
    {
        if(buffer[0] == static_cast<uint8_t>(Command::GetBoardInfo))
        {
            std::cout << "DIY Watch v" << major << "." << minor << std::endl;
        }
        else if (buffer[0] == static_cast<uint8_t>(Command::SetTime))
        {
            if(buffer.size() >= 4)
            {
                time.hours = buffer[1];
                time.minutes = buffer[2];
                time.seconds = buffer[3];
                return true;
            }
        }
    }
    return false;
}

Time USBSerial::getTime()
{
    return time;
}

}