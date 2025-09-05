# binary_watch

This is a project to create a homecrew binary watch to fit inside a analogue wrist watch

## issues

- No Vcc out of the LTC4071 chip, swapped LBSEL to set the `Low Battery Connect` to 3.6V but never get any voltage out. Change to MCP73833? also cheaper. [reference curcuit](https://learn.adafruit.com/li-ion-and-lipoly-batteries/downloads)
- Cannot debug RP2040 code, got it working once but not again, I think it's something up with the cdoe itself, debugging reliable blink code though... (change to pico 2??) (try embassy???)

## TODO

- Swap battery charger for MCP73833
- Recreate breadboard setup, test in rust
- Change PCB to 4 layer
- Change programming port for 3 pin JST SH (pico probe standard)
- Romove bool sel switch in favour of solder pads
- Swap LIR battery with space for lipo
- Add charging state LED

## Components
```
Cheap 6 digit LCD display
Raspberry Pi RP2040 Microchip
150mah lipo - https://thepihut.com/products/150mah-3-7v-lipo-battery
DS3231 real time clock
charging chip (breakout https://www.adafruit.com/product/259)
Standarise programming port on pico probe wire (1mm JST-SH, SM03B-SRSS-TB)
```