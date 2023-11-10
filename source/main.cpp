#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int main( void )
{
    stdio_init_all();
    
    if( cyw43_arch_init() )
    {
        printf( "WiFi module could not be initialised\n" );
        return -1;
    }

    while( 1 )
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(500);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(500);
    }
}