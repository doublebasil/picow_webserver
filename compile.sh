#!/bin/bash
# Build script my plant watering pico-w project

# -DPICO_BOARD=pico_w builds for pico w, not pico
# -B build means cmake creates the build folder if needed
# && means make is only run if cmake was successful
# -j tells make how many cpu threads to use
# $(getconf _NPROCESSORS_ONLN) is the number of threads yout pc has
# -j $(getconf _NPROCESSORS_ONLN) tells make to use all your cores
# This is much faster, but will use more cpu
# -C build tells make what folder to build from/in


# If submodules not found, git submodule update to download sdk
if [ ! -d "submodules" ]; then
    git submodule update --init --recursive
    # Must be recursive as the sdk has wifi submodules
fi

# Build files
cmake -B build && \
make -j $(getconf _NPROCESSORS_ONLN) -C build

# If user runs ./compile u then follow up by running the upload script
if test "$1" = "u"; then
    bash upload.sh
fi
