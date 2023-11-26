// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ----------------- //
// multiplex_lcd_drv //
// ----------------- //

#define multiplex_lcd_drv_wrap_target 0
#define multiplex_lcd_drv_wrap 8

#define multiplex_lcd_drv_DIGITS 6
#define multiplex_lcd_drv_COM_PINS 4
#define multiplex_lcd_drv_TOTAL_PINS 14

static const uint16_t multiplex_lcd_drv_program_instructions[] = {
            //     .wrap_target
    0x80a0, //  0: pull   block                      
    0x6084, //  1: out    pindirs, 4                 
    0x602e, //  2: out    x, 14                      
    0xbf01, //  3: mov    pins, x                [31]
    0xbf09, //  4: mov    pins, !x               [31]
    0xa04d, //  5: mov    y, !status                 
    0x0068, //  6: jmp    !y, 8                      
    0x0000, //  7: jmp    0                          
    0xc000, //  8: irq    nowait 0                   
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program multiplex_lcd_drv_program = {
    .instructions = multiplex_lcd_drv_program_instructions,
    .length = 9,
    .origin = -1,
};

static inline pio_sm_config multiplex_lcd_drv_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + multiplex_lcd_drv_wrap_target, offset + multiplex_lcd_drv_wrap);
    return c;
}
#endif

