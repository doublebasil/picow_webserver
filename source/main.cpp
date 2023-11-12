#include <string.h>
#include <stdlib.h>

#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwipopts.h" // Required for compile, copied from https://github.com/krzmaz/pico-w-webserver-example, you can find similar files in pico-examples

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

    wifi_runServer();

    // while( 1 )
    // {
    //     sleep_ms( 1000U );
    //     printf("End of main\n");
    //     cyw43_arch_gpio_put( CYW43_WL_GPIO_LED_PIN, 1 );
    //     sleep_ms( 1000U );
    //     cyw43_arch_gpio_put( CYW43_WL_GPIO_LED_PIN, 0 );
    // }

    // cyw43_arch_gpio_put( CYW43_WL_GPIO_LED_PIN, 1 );

    for( ;; ) {}
}
