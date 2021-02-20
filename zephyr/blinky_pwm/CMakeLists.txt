cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr)
project(blink_led)

set(BOARD nucleo_h743zi)

target_sources(app PRIVATE src/main.c)
