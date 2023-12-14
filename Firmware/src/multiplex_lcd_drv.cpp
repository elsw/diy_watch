#include "diy_watch/multiplex_lcd_drv.h"
#include "pico.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include <cmath>

//all 1s for direction for bits equal to number of data pins
constexpr uint32_t DATA_PINS_HIGH = (static_cast<int>(std::pow(2,multiplex_lcd_drv_DATA_PINS)) - 1) << (multiplex_lcd_drv_TOTAL_PINS + multiplex_lcd_drv_COMMON_PINS);
//all 1s for data for bits equal to number of common pins
constexpr uint32_t COMMON_PINS_HIGH = (static_cast<int>(std::pow(2,multiplex_lcd_drv_COMMON_PINS)) - 1);

MultiplexLCDDriver::MultiplexLCDDriver(PIO pio, uint sm, uint offset, uint pin_base,uint target_cycle_frequency):
  pio(pio),
  sm(sm)
{
    pio_sm_config c = multiplex_lcd_drv_program_get_default_config(offset);

    sm_config_set_out_pins(&c,pin_base,multiplex_lcd_drv_TOTAL_PINS);

    //Init all GPIO pins
    for(uint i=pin_base; i< pin_base + multiplex_lcd_drv_TOTAL_PINS; i++) {
        pio_gpio_init(pio, i);
    }

    bool shift_right = true;
    bool autopull = false;
    uint pull_thresfold = multiplex_lcd_drv_TOTAL_PINS;
    sm_config_set_out_shift(&c, shift_right, autopull, pull_thresfold);

    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);

    // Set all pins as output
    pio_sm_set_consecutive_pindirs(pio, sm, pin_base, multiplex_lcd_drv_TOTAL_PINS, true);

    // when TX fifo is less than 0(n), y will become all-ones, otherwise all-zeroes
    sm_config_set_mov_status (&c, STATUS_TX_LESSTHAN , 1 ) ;

    int cycles_per_loop = (multiplex_lcd_drv_WAIT_CYCLES * 2) + 6;
    float div = clock_get_hz(clk_sys) / (target_cycle_frequency * cycles_per_loop);
    sm_config_set_clkdiv(&c, div);

    // Load our configuration, and jump to the start of the program
    pio_sm_init(pio, sm, offset, &c);
    // Set the state machine running
    pio_sm_set_enabled(pio, sm, true);
}


void MultiplexLCDDriver::UpdateOutput(uint8_t * buf)
{
    //Clear Buffer and re-setup COM sequence
    for(unsigned i = 0 ; i < multiplex_lcd_drv_COMMON_PINS ; i++)
    {
        //First 14 bits is data, next 14 is pin directions. Start with all data pin directions as output
        lcd_out[i] = DATA_PINS_HIGH;
        // Add common pins data (0 for active data pin)
        lcd_out[i] |= (COMMON_PINS_HIGH ^ (1 << i));
        //common direction (1 for active set output)
        lcd_out[i] |= (1 << (multiplex_lcd_drv_TOTAL_PINS + i));
    }
    //Now loop through digits, adding the data to lcd_out buffer
    /*for(unsigned i = 0 ; i < multiplex_lcd_drv_DIGITS ; i++)
    {
        //Get data that will create the chosen digit
        uint8_t digit[multiplex_lcd_drv_COM_PINS]; 
        for(unsigned j = 0 ; j < multiplex_lcd_drv_COM_PINS ; j++)
        {
          digit[j] = digit_lookup[buf[i]][j];
        }
        uint8_t shift_amount = (multiplex_lcd_drv_COM_PINS) + (i * 2); //shift up the data 2 bits per digit plus the width of data the common lines use
        //Add data to each COM line
        for(unsigned j = 0 ; j < multiplex_lcd_drv_COM_PINS ; j++)
        {
            lcd_out[j] |= (digit[j] << shift_amount);
        }
    }*/
    return;
}

void MultiplexLCDDriver::FIFOEmpty()
{
  for(unsigned i = 0 ; i < multiplex_lcd_drv_COMMON_PINS ; i++)
  {
    pio_sm_put(pio,sm,lcd_out[i]);
  }
}