add_executable(plant_watering 
    main.cpp
    wifi.cpp
    )

target_link_libraries(plant_watering
    pico_stdlib
    pico_cyw43_arch_none # Wifi stuff
    )

# By default make only produces a .elf
# This function produces .uf2 and others
pico_add_extra_outputs(plant_watering)
