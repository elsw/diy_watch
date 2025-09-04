# binary_watch

This is a project to create a homecrew binary watch to fit inside a analogue wrist watch

## issues

- No Vcc out of the LTC4071 chip, swapped LBSEL to set the `Low Battery Connect` to 3.6V but never get any voltage out. Change to MCP73833? also cheaper. [reference curcuit](https://learn.adafruit.com/li-ion-and-lipoly-batteries/downloads)
- Cannot debug RP2040 code, got it working once but not again, I think it's something up with the cdoe itself, debugging reliable blink code though... (change to pico 2??) (try embassy???)

## TODO

- BUY https://thepihut.com/products/adafruit-usb-liion-lipoly-charger (check still in stock for JLC)
- Recreate breadboard setup, test in rust
- Check fit with exsisting PCB
- Change PCB to 4 layer, swap bootsel for pure smd option or remove switch completely? check it this frees enough space for MCP73833
- Find connector I could solder to the back for SWD

## Components
```
Cheap 6 digit LCD display
Raspberry Pi RP2040 Microchip
LIR2032 40mAH button Battery
DS3231 real time clock
charging chip TODO
```