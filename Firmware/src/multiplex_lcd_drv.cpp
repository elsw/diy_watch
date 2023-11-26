#include "diy_watch/multiplex_lcd_drv.h"
#include "pico.h"
#include "hardware/pio.h"

MultiplexLCDDriver::MultiplexLCDDriver(PIO pio, uint sm, uint offset, uint pin_base):
  pio(pio),
  sm(sm)
{
    pio_sm_config c = multiplex_lcd_drv_program_get_default_config(offset);

    bool shift_right = true;
    bool autopull = false;
    uint pull_thresfold = multiplex_lcd_drv_TOTAL_PINS;
    sm_config_set_out_shift(&c, shift_right, autopull, pull_thresfold);

    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);

    //Init all GPIO pins
    for(uint i=pin_base; i< pin_base + multiplex_lcd_drv_TOTAL_PINS; i++) {
        pio_gpio_init(pio, i);
    }

    // Set COM pins default input, so they default to 1/2 v+
    pio_sm_set_consecutive_pindirs(pio, sm, pin_base, multiplex_lcd_drv_COM_PINS, false);
    // Set Data pins out output
    pio_sm_set_consecutive_pindirs(pio, sm, pin_base + multiplex_lcd_drv_COM_PINS, multiplex_lcd_drv_TOTAL_PINS - multiplex_lcd_drv_COM_PINS, true);

    // Load our configuration, and jump to the start of the program
    pio_sm_init(pio, sm, offset, &c);
    // Set the state machine running
    pio_sm_set_enabled(pio, sm, true);

    // when TX fifo is less than 0(n), y will become all-ones, otherwise all-zeroes
    sm_config_set_mov_status (&c, STATUS_TX_LESSTHAN , 1 ) ;
}


void MultiplexLCDDriver::UpdateOutput(uint8_t * buf)
{
    //Clear Buffer and re-setup COM sequence
    for(unsigned i = 0 ; i < multiplex_lcd_drv_COM_PINS ; i++)
    {
        //For 4 coms and 10 data lines, first 4 bits is pin direction, next 4 is COM state, next 10 is data state
        lcd_out[i] = (1 << i) + (1 << (multiplex_lcd_drv_COM_PINS + i));
    }
    //Now loop through digits, adding the data to lcd_out buffer
    for(unsigned i = 0 ; i < multiplex_lcd_drv_DIGITS ; i++)
    {
        //Get data that will create the chosen digit
        uint8_t digit[multiplex_lcd_drv_COM_PINS]; 
        for(unsigned j = 0 ; j < multiplex_lcd_drv_COM_PINS ; j++)
        {
           digit[j] = digit_lookup[buf[i]][j];
        }
        uint8_t shift_amount = (multiplex_lcd_drv_COM_PINS * 2) + (i * 2); //shift up the data 2 bits per digit plus the width of data the common lines use
        //Add data to each COM line
        for(unsigned j = 0 ; j < multiplex_lcd_drv_COM_PINS ; j++)
        {
            lcd_out[j] &= (digit[j] << shift_amount);
        }
    }
}

void MultiplexLCDDriver::FIFOEmpty()
{
  for(unsigned i = 0 ; i < multiplex_lcd_drv_COM_PINS ; i++)
  {
    pio_sm_put(pio,sm,lcd_out[i]);
  }
}