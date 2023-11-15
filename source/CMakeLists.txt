add_executable(${PROJECT_NAME}
    main.cpp
    webserver/webserver.cpp
    )

# Adding a directory here means anything within this project can include it
# Might be the wrong way to do it but I couldn't figure out the right way
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}           # Contains config.h and sysdata.h which may be used anywhere
    ${CMAKE_CURRENT_LIST_DIR}/webserver # pico-sdk (a submodule) needs to use see lwipopts.h and fs_data.c, which is in our source folder
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
