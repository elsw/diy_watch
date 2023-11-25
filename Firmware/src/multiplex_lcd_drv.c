#include "pico.h"
#include "hardware/pio.h"
#include "multiplex_lcd.pio.h"
//#include "bl"

//One set of data pins per 32 bit number
uint32_t lcd_out[multiplex_lcd_drv_COM_PINS];

//Lookup table for creating digits.
// 10 different digits (0 to 9)
// 8 Segments A to G & P (7 Seg plus a dot)
// In out LCD the maxtrix is split up per digit
// bits   2 1
// COM1 = B A
// COM2 = G F
// COM3 = C E
// COM4 = P D
//Shift up 2 access next digit, see LCD_Panel.PNG for full pinout
static const uint8_t digit_lookup[10][multiplex_lcd_drv_COM_PINS] = {
                            {3,3,3,0}, //0
                            {1,2,0,0}, //1
                            {3,1,2,2}, //2
                            {3,3,0,2}, //3
                            {1,2,1,2}, //4
                            {3,1,2,2}, //5
                            {2,3,3,2}, //6
                            {3,2,0,0}, //7
                            {3,3,3,2}, //8
                            {3,2,1,2}, //9
                            };

/* Setup LCD
* PIO - PIO instance pio0 or pio1
* sm - State machine to use, find a free one using pio_claim_unused_sm
* offset - memory offset of the allocated memory, get allocation using pio_add_program
* pin - base pin to initialise, Will initiale this pin plus the next TOTAL_PINS defined in the .pio file
*/
static inline void multiplex_lcd_init(PIO pio, uint sm, uint offset, uint pin_base) 
{
    pio_sm_config c = multiplex_lcd_drv_program_get_default_config(offset);

    bool shift_right = true;
    bool autopull = true;
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
}

/*
* Given sequence of 6 digits calculate buffer stream to send to .pio LCD driver
*/
static inline void update_multiplex_lcd_output(uint8_t * buf)
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