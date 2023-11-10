#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "wifi.hpp"

int main( void )
{
    stdio_init_all();
    
    if( cyw43_arch_init() )
    {
        printf( "WiFi module could not be initialised\n" );
        return -1;
    }

    wifi_init();
}