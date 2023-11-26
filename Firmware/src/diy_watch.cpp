#include "pico/stdlib.h"

const uint LED_PIN = PICO_DEFAULT_LED_PIN;
const uint RTC_1HZ_PIN = 15;

/*void pio_irh() {
  if (pio0_hw->irq & 1) {
    pio0_hw->irq = 1;

  } else if (pio0_hw->irq & 2) {
    pio0_hw->irq = 2;

    // PIO0 IRQ1 fired
  }
}

...

// Enable IRQ0 & 1 on PIO0
irq_set_exclusive_handler(PIO0_IRQ_0, pio_irh);
irq_set_enabled(PIO0_IRQ_0, true);
pio0_hw->inte0 = PIO_IRQ0_INTE_SM0_BITS | PIO_IRQ0_INTE_SM1_BITS;*/

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

    gpio_set_irq_enabled_with_callback(21, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);

    while (true) 
    {
        sleep_ms(250);
    }
}