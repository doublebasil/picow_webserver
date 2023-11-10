#!/bin/bash
# Uploads the .uf2 to the pico

UF2_PATH="./build/source/plant_watering.uf2"

# Check the .uf2 is there
if ! [ -f $UF2_PATH ]; then
    echo uf2 not found
    exit
fi

# Use picotool if available
if which picotool >/dev/null; then
    # Flash the binary and reboot into application mode
    picotool load $UF2_PATH && \
    picotool reboot
else
    echo picotool not found, attempting to use cp
    cp $UF2_PATH /media/$USER/RPI-RP2/
fi
