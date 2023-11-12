# Run the makefsdata script to generate the autogen_fsdata.c file
execute_process(COMMAND
    perl ${CMAKE_CURRENT_LIST_DIR}/web/makefsdata
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    ECHO_OUTPUT_VARIABLE
    ECHO_ERROR_VARIABLE
    )

add_executable(${PROJECT_NAME} 
    main.cpp
    wifi.cpp
    )

# pico-sdk (a submodule) needs to use see lwipopts.h and fs_data.c, which is in our source folder
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    )

target_link_libraries(${PROJECT_NAME}
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
    pico_stdlib
    )

# Enable USB and UART for serial output
pico_enable_stdio_usb(${PROJECT_NAME} TRUE)
pico_enable_stdio_uart(${PROJECT_NAME} TRUE)

# By default make only produces a .elf, this function allows uf2 and others to be generated
pico_add_extra_outputs(${PROJECT_NAME})
