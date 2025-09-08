# DIY Watch firmware

This is the firmware for the DIY watch to run the raspberry pi RP2040 microcontroller

## Installation

Install rust: `curl --proto '=https' --tlsv1.2 https://sh.rustup.rs -sSf | sh`

Install rs-probe: `curl -LsSf https://github.com/probe-rs/probe-rs/releases/latest/download/probe-rs-tools-installer.sh | sh`

## Programming Setup

VSCode with extensions:
 - rust-analyser
 - rs-probe

## References

[RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
[Raspberry Pi Pico C/C++ SDK](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)
[Driving multiplexed LCD directly](https://ww1.microchip.com/downloads/en/Appnotes/doc8103.pdf)

# Windows Setup

Install VS code and install the pico extension. Import this folder using the pico import tool.

I've had issues with linux, for pico 1 seems like windwso is easier, for pico2 linux might be fine

## Debugging

Grab a pre-compiled `debugprobe_on_pico.uf2` binary from [debug probe git](https://github.com/raspberrypi/debugprobe/releases)

Hold down BOOTSEL, connect your pico and drag and drop the binary.

The the USB drivers you may need to download [zadig](https://zadig.akeo.ie/)

If you have the right version it should appear as a CMIS_DAP device

Select `Picoprobe (interface 2)` and set the USB driver to `WinUSB`

At time of writing I am using pico SDK version `v2.2.0` and pico debug probe `v2.2.3`
 
