cmake_minimum_required(VERSION 3.5)
project(buttonComponent CXX ASM)

set(CMAKE_CXX_STANDARD 20)

pico_sdk_init()

add_library( buttonComponent
    button.hpp
    button.cpp
    )

target_link_libraries( buttonComponent
  pico_stdlib 
  # hardware_gpio
  # Using Pico W
  pico_cyw43_arch_none
)

target_include_directories(buttonComponent PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")