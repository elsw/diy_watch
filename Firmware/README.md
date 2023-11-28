# DIY Watch firmware

This is the firmware for the DIY watch to run the raspberry pi RP2040 microcontroller

## References

[RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
[Raspberry Pi Pico C/C++ SDK](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)


# Windows Setup (debugging no WORK!)

Windows support seems better than the Ubunutu support for pic development

Download and install the [Windows Pico Installer](https://www.raspberrypi.com/news/raspberry-pi-pico-windows-installer/)

Open the `Pico - Visual Studio Code` shortcut from start menu, build the cmake and select the Kit `arm-none-eabi` (you may need to scan for kits first)

## Debugging

Grab a pre-compiled picoprobe binary.. TODO find source.

Hold down BOOTSEL, connect your pico and drag and drop the picoprobe.

If you have the right version it should appear as a CMIS_DAP device

The the USB drivers you may need to download [zadig](https://zadig.akeo.ie/)

Select `Picoprobe (interface 2)` and set the USB driver to `WinUSB`
 
# WSL Ubuntu Build Setup

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

Open VSCode and connect VSCode to the WSL instance then configure the CMake extension:
```
Settings Gear -> Settings -> Extensions -> CMake Tools configuration -> Build Envirnoment
```
Add the Item `PICO_SDK_PATH` and set the Value `/home/$YOURUSER/pico-sdk`

You may also need to add to your `~/.bashrc`
```
export PICO_SDK_PATH=/home/$YOURUSER/pico-sdk
```
unclear on this

Click on the Cmake kit button at the bottom and select the compiler: `arm-none-eabi`

You can now build the program. Hold down the BOOLSEL button and copy the file `build/diy_watch.uf2` to the pico

## Debugging the Code

### Install openOCD for pico

```
sudo apt install automake autoconf build-essential texinfo libtool libftdi-dev libusb-1.0-0-dev pkg-config
git clone https://github.com/raspberrypi/openocd.git --branch rp2040-v0.12.0 --depth=1 --no-single-branch
cd openocd
./bootstrap
./configure --enable-picoprobe
make -j4
sudo make install
```

### Flash picoprobe onto a Pico

```
git clone https://github.com/raspberrypi/picoprobe.git
cd picoprobe
git submodule update --init
mkdir build
cd build
cmake ..
make
```

Hold BOOLSEL, connect your pico that will become the debugger and copy across `picoprobe.elf`

### Add usb support to WSL

Install the .msi installer for [usbipd](https://github.com/dorssel/usbipd-win/releases) for windows 

Inside your WSL instance, install the USBIP tools
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

### Test out your openocd build

Checkout pico examples:
```
git clone https://github.com/raspberrypi/pico-examples
mkdir build
cd build
cmake ..
make
```
This try use your custom openocd build to upload a program
```
cd /home/steve/openocd
openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "program /home/steve/pico-examples/build/blink/blink.elf verify reset exit"
```

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

GDB errors...

## References

[Driving multiplexed LCD directly](https://ww1.microchip.com/downloads/en/Appnotes/doc8103.pdf)