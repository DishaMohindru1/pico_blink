cmake_minimum_required(VERSION 3.19)

# Set CMake policies to enable IN_LIST operator
cmake_policy(SET CMP0057 NEW)

# Set compilers explicitly
set(CMAKE_C_COMPILER /usr/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER /usr/bin/arm-none-eabi-gcc)

# Include the SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Define the project
project(task_2)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Create an executable for the task_2 project
add_executable(task_2 main.c)

# Link the required libraries
target_link_libraries(task_2 pico_stdlib)

# Enable USB output (for serial console over USB)
pico_enable_stdio_usb(task_2 1)

# Disable UART output (if not needed)
pico_enable_stdio_uart(task_2 0)

# Create map/bin/hex/uf2 files to allow flashing the Raspberry Pi Pico
pico_add_extra_outputs(task_2)

