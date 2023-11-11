#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwipopts.h" // Required for compile, copied from https://github.com/krzmaz/pico-w-webserver-example, you can also find simlar files in pico-examples

#include "sysdata.hpp"

int wifi_init( tSysData* sysDataPtr );

int wifi_runServer( tSysData* sysDataPtr );
