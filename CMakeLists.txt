# I'll mess with this when everything is working
cmake_minimum_required(VERSION 3.18)

# include(submodules/pico-sdk/pico_sdk_version.cmake)
include(submodules/pico-sdk/external/pico_sdk_import.cmake)

project(plant_watering C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17) # CXX is c++

pico_sdk_init()

add_compile_options(-Wall -Werror)

add_subdirectory(source)
