#!/bin/bash
# Uploads the .uf2 to the pico

# Check the .uf2 is there
if ! [ -f "./build/src/plant_watering.uf2" ]; then
    echo uf2 not found
    exit
fi

# Use picotool if available
if which picotool >/dev/null; then
    # Flash the binary
    picotool load ./build/src/plant_watering.uf2
    # Reboot the pico to get it out of bootsel mode
    picotool reboot
else
    echo picotool not found, attempting to use cp
    cp ./build/src/plant_watering.uf2 /media/$USER/RPI-RP2/
fi
