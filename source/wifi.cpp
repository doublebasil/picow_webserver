#include "wifi.hpp"
#include "config.h"

// cyw43_arch_gpio_put( CYW43_WL_GPIO_LED_PIN, 1 );

// Module function prototypes -------------------------------------------------
// Server Side Includes functions
static int ssi_init( void );
// Common Gateway Interface functions
static int cgi_init( void );

int wifi_init( tSysData* sysDataPtr )
{
    // Init cyw43 architecture, this is for the pico's wifi chip
    if( cyw43_arch_init() != 0 )
    {
        sysDataPtr->wifiStatus = wifi_initFailed_e;
        return 1;
    }

    // I'm using STA (station) mode, not AP mode, becuase that's what other people have done
    cyw43_arch_enable_sta_mode();

    // Set the power management mode
    if( cyw43_wifi_pm( &cyw43_state, cyw43_pm_value( CYW43_NO_POWERSAVE_MODE, 20, 1, 1, 1 ) ) != 0 )
    {
        sysDataPtr->wifiStatus = wifi_initFailed_e;
        return 1;
    }

    return 0; // Success!
}

int wifi_runServer( tSysData* sysDataPtr )
{
    printf( "Attempting to connect to WiFi\n" );
    sysDataPtr->wifiStatus = wifi_connecting_e;
    
    int result = cyw43_arch_wifi_connect_timeout_ms( WIFI_SSID, 
        WIFI_PASSWORD, 
        CYW43_AUTH_WPA2_AES_PSK, 
        30000 );
    
    if( result != 0 )
    {
        printf( "Could not connect\n" );
        sysDataPtr->wifiStatus = wifi_connectionFailed_e;
        return 1;
    }
    else
    {
        printf( "Connection successful" );
        sysDataPtr->wifiStatus = wifi_connected_e;
    }

    // This is a pico-sdk function for setting up threads related to running a http server?
    httpd_init();

    // We need an ssi-cgi server, so need to init both
    ssi_init();
    cgi_init();

    return 0;
}

// Server Side Includes functions
static int ssi_init( void )
{
    return 0;
}

// Common Gateway Interface functions
static int cgi_init( void )
{
    return 0;
}
