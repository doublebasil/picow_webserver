cmake_minimum_required(VERSION 3.18)

# Perl is used to convert html files into magical c arrays which the magical web libraries use
find_package(Perl)
if(NOT PERL_FOUND)
    message(FATAL_ERROR "Perl is needed for generating the fsdata.c file")
endif()

# Run the makefsdata script to generate the autogen_fsdata.c file from html files
execute_process(COMMAND
    perl ${CMAKE_CURRENT_LIST_DIR}/utils/makefsdata  # Location of the makefsdata script
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/html # Folder that contains all the html files
    ECHO_OUTPUT_VARIABLE
    ECHO_ERROR_VARIABLE
    )

set(PROJECT_NAME pico_w_project)
set(PICO_BOARD pico_w)

include(submodules/pico-sdk/external/pico_sdk_import.cmake)

project(${PROJECT_NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17) # CXX is c++

add_compile_options(-Wall -Werror)

pico_sdk_init()

add_subdirectory(source)
