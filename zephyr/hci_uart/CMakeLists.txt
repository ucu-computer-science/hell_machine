# SPDX-License-Identifier: Apache-2.0
set(BOARD nucleo_h743zi)
cmake_minimum_required(VERSION 3.13.1)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hci_uart)

include_directories(inc)

target_sources(app PRIVATE src/main.c
        src/controls.c inc/controls.h
        )
