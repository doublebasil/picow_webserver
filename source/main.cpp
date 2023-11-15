#include "pico/stdlib.h"

#include "sysdata.hpp"
#include "webserver/webserver.hpp"

int main( void )
{
    // Create the global data struct
    tSysData sysData;

    // Initialise the debug output
    stdio_init_all();

    // cyw43 related setup
    wifi_init( &sysData );

    wifi_runServer();

    for( ;; ) {}
}
