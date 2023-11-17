#include <stdio.h>

#include "pico/stdlib.h"

#include "sysdata.h"
#include "webserver.hpp"
#include "config.h"

int main( void )
{
    // Create the global data struct
    tSysData sysData;

    // Initialise the debug output
    stdio_init_all();
    // Wait for the stdio to initialise
    sleep_ms( 800U );
    // Tell the user their SSID
    printf( "BOOT: Note your SSID=" );
    printf( WIFI_SSID );
    printf( "\n" );

    // cyw43 related setup
    wifi_init( &sysData );

    wifi_runServer();

    for( ;; ) {}
}
