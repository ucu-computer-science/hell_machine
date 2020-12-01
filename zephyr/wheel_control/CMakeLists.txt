# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.14.1)

set(BOARD nucleo_h743zi)
set(DTC_OVERLAY_FILE boards/nucleo_h743zi.overlay)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(blinky)


target_sources(app PRIVATE src/main.c)
