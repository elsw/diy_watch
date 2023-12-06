#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "multiplex_lcd.pio.h"
#include "diy_watch/multiplex_lcd_drv.h"

const uint LED_PIN = PICO_DEFAULT_LED_PIN;
const uint RTC_1HZ_PIN = 18;
const uint LCD_BASE_PIN = 0;
const uint TARGET_LCD_CYCLE_HZ = 250; //4ms per cycle, 4 cycles per refresh

void pio_irh() {
  /*if (pio0_hw->irq & 1) {
    pio0_hw->irq = 1;

  } else if (pio0_hw->irq & 2) {
    pio0_hw->irq = 2;

    // PIO0 IRQ1 fired
  }*/
}

void gpio_callback(uint gpio, uint32_t events) 
{
    if(gpio==RTC_1HZ_PIN)
    {
        //Increment time
        gpio_put(LED_PIN,!gpio_get(LED_PIN));
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
    uint sm = pio_claim_unused_sm(pio, true);
    //Initialise driver
    MultiplexLCDDriver lcd(pio,sm,offset,LCD_BASE_PIN,TARGET_LCD_CYCLE_HZ);

    //gpio_set_irq_enabled_with_callback(RTC_1HZ_PIN, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);

    // Enable IRQ0 & 1 on PIO0
    /*irq_set_exclusive_handler(PIO0_IRQ_0, pio_irh);
    irq_set_enabled(PIO0_IRQ_0, true);
    pio0_hw->inte0 = PIO_IRQ0_INTE_SM0_BITS | PIO_IRQ0_INTE_SM1_BITS;*/

    while (true) 
    {
        sleep_ms(100);
        gpio_callback(RTC_1HZ_PIN,0);
        pio_sm_put_blocking(pio,sm,0x00004001);
    }
}