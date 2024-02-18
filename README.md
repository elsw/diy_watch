# binary_watch

This is a project to create a homecrew binary watch to fit inside a analogue wrist watch

## TODO

- SDA Pullup
- SCL Pullup
- RTC_INT Pullup
- Move 3V3 reg input from BATT to Vcc
- More space for micro USB
- USB data resistors
- Push button fit?

## Components
```
Raspberry Pi RP2040 Microchip
LIR2032 40mAH button Battery
```
[Coil for wirelsss charging](https://www.mouser.co.uk/ProductDetail/Wurth-Elektronik/760308101216?qs=16w8nSHsg3uUA0dFoYycuw%3D%3D)


## Example Project

https://www.waveshare.com/wiki/RP2040-LCD-1.28

## Display Ideas

### binary LEDs

Needs a 400mah lipo to last around 25 hours always on

### EInk screen 

[Watch eink](https://www.aliexpress.com/item/1005005791100921.html) no docs
Would fit maybe

Too LONG
[Just screen](https://www.aliexpress.com/item/33044560386.html?spm=a2g0o.productlist.main.37.11d8xICCxICCuu)
[Interface board](https://www.aliexpress.com/item/1005004633084221.html?spm=a2g0o.detail.1000023.1.7d38UkA5UkA5Mj)
[E-Ink mini display](https://www.waveshare.com/1.54inch-e-paper-module.htm)
```
Should last about a week refreshing every minute using the 40mah battery i think
```

### LCD Panel

[small  3 digit screen 11.938mm long](https://www.aliexpress.com/item/1005005194797350.html)

[Small 6 digit 25mm long](https://www.aliexpress.com/item/32324866141.html)

[128x128 LCD](https://www.digikey.co.uk/en/products/detail/sharp-microelectronics/LS013B7DH03/5300387)

[round 128 x 128 LCD](https://uk.farnell.com/midas/mdcog128128b-fptlw/lcd-display-fstn-128-x-128-pixel/dp/3407285)

## Battteries

[45 mah coin cell](https://uk.rs-online.com/web/p/button-batteries/1834291)

[450mah round lipo](https://www.aliexpress.com/item/4000126677395.html)

## Prototype

[SMD to header](https://www.digikey.co.uk/en/products/detail/adafruit-industries-llc/1207/5022796)