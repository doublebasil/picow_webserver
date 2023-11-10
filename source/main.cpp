#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "sysdata.hpp"
#include "wifi.hpp"

int main( void )
{
    // Create the global data struct
    tSysData sysData;

    // Initialise the debug output
    stdio_init_all();

    // Init wifi chip, this is also needed for the built-in led
    wifi_init( &sysData );

    wifi_runServer( &sysData );

    while( 1 );
}
