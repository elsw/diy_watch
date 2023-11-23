# DIY Watch firmware

This is the firmware for the DIY watch to run the raspberry pi RP2040 microcontroller

## Build Setup

I am using VSCode to program,build and test the RP2040 firmware on WSL, based from [this](https://paulbupejr.com/raspberry-pi-pico-windows-development/) tutorial

Install WSL Ubuntu 22 from the windows store

Install VSCode with the following extensions
```
Remote – WSL
C/C++
CMake Tools. 
```

Open up a terminal inside your WSL instance, and install dependancies
```
sudo apt-get update
sudo apt-get upgrade
sudo apt install git cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential
```

Install the Pico SDK

```
cd /home/$USER
sudo git clone -b master https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
sudo git submodule update --init
```

Open VSCode, connect VSCode to the WSL instance then configure the CMake extension:
```
Settings Gear -> Settings -> Extensions -> CMake Tools configuration -> Build Envirnoment
```
Add the Item `PICO_SDK_PATH` and set the Value `/home/$YOURUSER/pico-sdk`

Click on the Cmake kit button at the bottom and select the compiler: `arm-none-eabi`

You can now build the program. Hold down the BOOLSEL button and copy the file `build/diy_watch.uf2` to the pico

## Debugging the Code

Requires a SWD interface connected to your computer

TODO auto mount devices in WSL?

The debugging setup is configured in the .vscode/launch.json file.

Press F5...

## References

[Driving multiplexed LCD directly](https://ww1.microchip.com/downloads/en/Appnotes/doc8103.pdf)