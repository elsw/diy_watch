# DIY Watch firmware

This is the firmware for the DIY watch to run the raspberry pi RP2040 microcontroller

## References

[RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
[Raspberry Pi Pico C/C++ SDK](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)
[Driving multiplexed LCD directly](https://ww1.microchip.com/downloads/en/Appnotes/doc8103.pdf)


# Windows Setup

Install VS code and install the pico extension. Import this folder using the pico import tool.

## Debugging

Grab a pre-compiled picoprobe binary.. TODO find source.

Hold down BOOTSEL, connect your pico and drag and drop the picoprobe.

If you have the right version it should appear as a CMIS_DAP device

The the USB drivers you may need to download [zadig](https://zadig.akeo.ie/)

Select `Picoprobe (interface 2)` and set the USB driver to `WinUSB`
 
### Debugging with VSCode

Is this required?
```
sudo apt update
sudo apt install binutils-multiarch
cd /usr/bin
ln -s /usr/bin/objdump objdump-multiarch
ln -s /usr/bin/nm nm-multiarch 
```

Does it need in the launch?
```
"openOCDLaunchCommands": [
                "adapter speed 5000"
            ],
```

The debugging setup is configured in the .vscode/launch.json file.

Hitting
```
OpenOCD: GDB Server Quit Unexpectedly, cannot find device, WSL limitation?
```

## Debugger wiring



## References
