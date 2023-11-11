#include "wifi.hpp"
#include "config.h"

int wifi_init( tSysData* sysDataPtr )
{
    // From this webpage: https://arduino-pico.readthedocs.io/en/latest/wifi.html
    // WiFi can be in station (STA) mode or access point (AP) mode
    // I'm using STA mode because that's what other people have done

    cyw43_arch_init();

    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    cyw43_arch_enable_sta_mode();

    // Set the power management mode
    cyw43_wifi_pm(&cyw43_state, cyw43_pm_value(CYW43_NO_POWERSAVE_MODE, 20, 1, 1, 1));

    return 0;
}

int wifi_runServer( tSysData* sysDataPtr )
{
    printf( "Attempting to connect to WiFi\n" );
    
    int result = 0;
    result = cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000);
    
    if( result != 0 )
    {
        printf( "Could not connect\n" );
        return 1;
    }
    else
        printf( "Connection successful" );

    return 0;
}
