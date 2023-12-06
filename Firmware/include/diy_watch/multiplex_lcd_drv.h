#include "multiplex_lcd.pio.h"

class MultiplexLCDDriver
{
public:

    /*
    * PIO - PIO instance pio0 or pio1
    * sm - State machine to use, find a free one using pio_claim_unused_sm
    * offset - memory offset of the allocated memory, get allocation using pio_add_program
    * pin - base pin to initialise, Will initiale this pin plus the next TOTAL_PINS defined in the .pio file
    */
    MultiplexLCDDriver(PIO pio, uint sm, uint offset, uint pin_base,uint target_cycle_frequency);

    /*
    * Given sequence of 6 digits calculate buffer stream to send to .pio LCD driver
    */
    void UpdateOutput(uint8_t * buf);
    /*
    * Call when the PIO FIFO is empty to re-push the LCD data
    */
    void FIFOEmpty();

private:    
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
    static constexpr uint8_t digit_lookup[10][multiplex_lcd_drv_COM_PINS] = {
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



    //One set of data pins per 32 bit number
    uint32_t lcd_out[multiplex_lcd_drv_COM_PINS];
    PIO pio;
    uint sm;
};












