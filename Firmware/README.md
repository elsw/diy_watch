# DIY Watch firmware

This is the firmware for the DIY watch to run the raspberry pi RP2040 microcontroller.

We are using [embassy](https://github.com/embassy-rs/embassy) to support Rust code on the RP2040,

## Programming Setup

- WSL - Ubuntu 24

- RP2040 as a pico probe, attached to main RP2040
    Grab a pre-compiled `debugprobe_on_pico.uf2` binary from [debug probe git](https://github.com/raspberrypi/debugprobe/releases)
    Hold down BOOTSEL, connect your pico and drag and drop the binary.

- VSCode with extensions:
 - rust-analyser
 - rs-probe

## Installation

Install rust: `curl --proto '=https' --tlsv1.2 https://sh.rustup.rs -sSf | sh`

Install rs-probe: `curl -LsSf https://github.com/probe-rs/probe-rs/releases/latest/download/probe-rs-tools-installer.sh | sh`

Follow [these](https://probe.rs/docs/getting-started/probe-setup/#linux-udev-rules) instructions to setup udev rules for the probe

Forward probe USB device from windows:
```
Download usbipd from https://github.com/dorssel/usbipd-win/releases
```
Open powershell with admin & list devices with
```
usbipd list
```
Note the hardware ID of your device and create a script somewhere nice like 'cd ~' with:
```                                                                                                            
# pico_debug_wsl.ps1
$HW_ID="2e8a:000c"
usbipd bind --hardware-id $HW_ID
usbipd attach --wsl --hardware-id $HW_ID
```
and save to something like `pico_debug_wsl.ps1`
you may also need to `set-executionpolicy remotesigned` to enable local scripts

Check the probe is recognized in WSL correctly with `probe-rs list`

## Test RP2040 setup

```
git clone https://github.com/embassy-rs/embassy.git
cd embassy/examples/rp
cargo build --bin blinky --release
cargo run --bin blinky --release
```

## Debugging
Info on setting up
https://probe.rs/docs/tools/debugger/

## References

[embassy](https://github.com/embassy-rs/embassy)
[probe-rs](https://probe.rs/docs/)
[RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)ro    
[Raspberry Pi Pico C/C++ SDK](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)
[Driving multiplexed LCD directly](https://ww1.microchip.com/downloads/en/Appnotes/doc8103.pdf)



 
