cmake_minimum_required(VERSION 3.18)

# I think Perl is needed for generating CGI stuff
find_package(Perl)
if(NOT PERL_FOUND)
    message(FATAL_ERROR "Perl is needed for generating the fsdata.c file")
endif()

set(PROJECT_NAME pico_w_project)
set(PICO_BOARD pico_w)

include(submodules/pico-sdk/external/pico_sdk_import.cmake)

project(${PROJECT_NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17) # CXX is c++

add_compile_options(-Wall -Werror)

pico_sdk_init()

add_subdirectory(source)
