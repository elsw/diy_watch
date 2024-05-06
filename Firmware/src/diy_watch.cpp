#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/i2c.h"
#include "multiplex_lcd.pio.h"
#include "diy_watch/multiplex_lcd_drv.h"
#include "diy_watch/RTClib.h"
#include "diy_watch/usb_serial.h"
#include <iostream>
#include <stdio.h>

const uint LED_PIN = PICO_DEFAULT_LED_PIN;
const uint RTC_1HZ_PIN = 18;

const uint LCD_BASE_PIN = 0;
const uint LCD_SM = 1; //LCD State Machine
const uint TARGET_LCD_CYCLE_HZ = 250; //4ms per cycle, 4 cycles per refresh

MultiplexLCDDriver::Ptr lcd;
unsigned seconds = 0;
unsigned minutes = 0;
unsigned hours = 0;

void pio_irh() 
{
  lcd->FIFOEmpty();
  pio0_hw->irq = 1;
}

void gpio_callback(uint gpio, uint32_t events) 
{
    if(gpio==RTC_1HZ_PIN)
    {
        //Increment time
        gpio_put(LED_PIN,!gpio_get(LED_PIN));
        uint8_t digits[6];
        seconds++;
        if(seconds > 59)
        {
          minutes++;
          seconds = 0;
          if(minutes > 59)
          {
            hours++;
            minutes = 0;
            if(hours > 24)
            {
              hours = 0;
            }
          }
        }
        digits[0] = seconds % 10;
        digits[1] = seconds / 10;
        digits[2] = minutes % 10;
        digits[3] = minutes / 10;
        digits[4] = hours % 10;
        digits[5] = hours / 10;

        lcd->UpdateOutput(digits);
    }
}

int main()
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    //Init LCD PIO Driver
    PIO pio = pio0;
    //Load program into memory
    uint offset = pio_add_program(pio, &multiplex_lcd_drv_program);
    //Claim state machine
    pio_sm_claim(pio, LCD_SM);
    //Initialise driver
    lcd = std::make_shared<MultiplexLCDDriver>(pio,LCD_SM,offset,LCD_BASE_PIN,TARGET_LCD_CYCLE_HZ);

    gpio_init(RTC_1HZ_PIN);
    gpio_set_dir(RTC_1HZ_PIN, GPIO_IN);
    gpio_set_irq_enabled_with_callback(RTC_1HZ_PIN, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);

    // Enable IRQ0 on PIO0
    irq_set_exclusive_handler(PIO0_IRQ_0, pio_irh);
    pio0_hw->inte0 = PIO_IRQ0_INTE_SM0_BITS;

    //sm_config_set_mov_status (&c, STATUS_TX_LESSTHAN , 1 )

    //Enable IRQ from LCD PIO code
    irq_set_enabled(PIO0_IRQ_0, true);
    pio_sm_put(pio0,LCD_SM,0x00000000);

    RTC_DS3231 rtc;
    rtc.writeSqwPinMode(Ds3231SqwPinMode::DS3231_SquareWave1Hz);

    //check the setting has taken
    Ds3231SqwPinMode mode = rtc.readSqwPinMode();
    std::cout << "DIY Watch v " << static_cast<int>(mode) << std::endl;

    diy_watch::USBSerial usb;

    while (true) 
    {
      bool got_time_update = usb.update();
      if(got_time_update)
      {
        diy_watch::Time time = usb.getTime();
        seconds = time.seconds;
        minutes = time.minutes;
        hours = time.hours;
      }

      //sleep_ms(1000);
      //gpio_callback(RTC_1HZ_PIN, 0) ;
    }
}