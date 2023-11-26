# DIY Watch firmware

This is the firmware for the DIY watch to run the raspberry pi RP2040 microcontroller

## References

[RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
[Raspberry Pi Pico C/C++ SDK](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)


# Windows Setup

Windows support seems better than the Ubunutu support for pic development

Download and install the [Windows Pico Installer](https://www.raspberrypi.com/news/raspberry-pi-pico-windows-installer/)

Open the `Pico - Visual Studio Code` shortcut from start menu, build the cmake and select the Kit `arm-none-eabi` (you may need to scan for kits first)

## Debugging

Grab a pre-compiled picoprobe binary from [here](https://github.com/Fabien-Chouteau/picoprobe-pcb#install-the-picoprobe-software)

Hold down BOOTSEL, connect your pico and drag and drop the picoprobe.

The the USB drivers you may need to download [zadig](https://zadig.akeo.ie/)

Select `Picoprobe (interface 2)` and set the USB driver to `WinUSB`
 
# WSL Ubuntu Build Setup (still not able to debug on this D:)

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

### Install openOCD for pico

```
sudo apt install automake autoconf build-essential texinfo libtool libftdi-dev libusb-1.0-0-dev pkg-config
git clone https://github.com/raspberrypi/openocd.git --branch rp2040-v0.12.0 --depth=1 --no-single-branch
cd openocd
./bootstrap
./configure
make -j4
```

### Flash picoprobe onto a Pico

```
https://github.com/raspberrypi/picoprobe.git
cd picoprobe
mkdir build
cd build
cmake ..
make
```

Hold BOOLSEL, connect your pico that will become the debugger and copy across `picoprobe.elf`

### Add usb support to WSL

Install the .msi installer for [usbipd](https://github.com/dorssel/usbipd-win/releases) for windows 

Inside your WSL instance, install teh USBIP tools
```
sudo apt install linux-tools-generic hwdata
sudo update-alternatives --install /usr/local/bin/usbip usbip /usr/lib/linux-tools/*-generic/usbip 20
```

Open up command line with admin priveliges in windoes and input
```
usbipd wsl list
```
attach the ` USB Mass Storage Device, RP2 Boot` with:
```
usbipd wsl attach --busid <busid>
```
in WSL `lsusb` should now show `Raspberry Pi RP2 Boot`

TODO auto mount devices in WSL?

The debugging setup is configured in the .vscode/launch.json file.

Press F5...

## References

[Driving multiplexed LCD directly](https://ww1.microchip.com/downloads/en/Appnotes/doc8103.pdf)