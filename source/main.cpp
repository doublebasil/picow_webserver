#include <string.h>
#include <stdlib.h>

#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwipopts.h" // Required for compile, copied from https://github.com/krzmaz/pico-w-webserver-example, you can also find simlar files in pico-examples

#include "sysdata.hpp"
#include "wifi.hpp"

int main( void )
{
    // Create the global data struct
    tSysData sysData;

    // Initialise the debug output
    stdio_init_all();

    // cyw43 related setup
    wifi_init( &sysData );

    wifi_runServer( &sysData );

    while( 1 )
    {
        sleep_ms( 1000U );
        printf("test\n");
    }
}
