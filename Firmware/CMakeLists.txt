# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(diy_watch C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

include_directories(include)

# Add executable. Default name is the project name, version 0.1

add_executable(${PROJECT_NAME}
    src/diy_watch.cpp
    src/multiplex_lcd_drv.cpp
    src/RTClib.cpp
    src/RTC_DS3231.cpp
    src/usb_serial.cpp
)

pico_set_program_name(diy_watch "diy_watch")
pico_set_program_version(diy_watch "0.1")

# Generate PIO header
#pico_generate_pio_header(diy_watch ${CMAKE_CURRENT_LIST_DIR}/blink.pio)
pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/src/multiplex_lcd.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(diy_watch 0)
pico_enable_stdio_usb(diy_watch 1)

# Add the standard library to the build
target_link_libraries(diy_watch
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(diy_watch PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(diy_watch 
        hardware_i2c
        hardware_pio
        )

pico_add_extra_outputs(diy_watch)

