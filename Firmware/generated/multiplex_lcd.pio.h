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
#define multiplex_lcd_drv_wrap 4

#define multiplex_lcd_drv_DIGITS 6
#define multiplex_lcd_drv_COM_PINS 4
#define multiplex_lcd_drv_TOTAL_PINS 14

static const uint16_t multiplex_lcd_drv_program_instructions[] = {
            //     .wrap_target
    0x6084, //  0: out    pindirs, 4                 
    0x602e, //  1: out    x, 14                      
    0xbf01, //  2: mov    pins, x                [31]
    0xbf09, //  3: mov    pins, !x               [31]
    0x0000, //  4: jmp    0                          
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program multiplex_lcd_drv_program = {
    .instructions = multiplex_lcd_drv_program_instructions,
    .length = 5,
    .origin = -1,
};

static inline pio_sm_config multiplex_lcd_drv_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + multiplex_lcd_drv_wrap_target, offset + multiplex_lcd_drv_wrap);
    return c;
}
#endif

