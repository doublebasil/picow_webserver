#include "webserver.hpp"
#include "ssi.hpp"
#include "cgi.hpp"
#include "config.h"

/* Some notes:
SSI = Server Side Includes, CGI = Common Gateway Interface
SSI is for updating the HTML. Look for <!--#tagName-->> in a .shtml file
CGI is for changing the data on the pico, based on user interaction on the web

LWIP is Light-weight IP, it's a TCP IP stack and it's basically magic
All we need to do is make the .shtmls, and the ssi and cgi handlers
everything else is handled by the lwip libraries, afaik
*/

// Declare pointer to my big data struct
static tSysData* m_sysDataPtr;

int wifi_init( tSysData* sysDataPtr )
{
    m_sysDataPtr = sysDataPtr;

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

int wifi_runServer()
{
    printf( "Attempting to connect to WiFi\n" );
    m_sysDataPtr->wifiStatus = wifi_connecting_e;
    
    int result = cyw43_arch_wifi_connect_timeout_ms( WIFI_SSID, 
        WIFI_PASSWORD, 
        CYW43_AUTH_WPA2_AES_PSK, 
        30000 );
    
    if( result != 0 )
    {
        printf( "Could not connect\n" );
        m_sysDataPtr->wifiStatus = wifi_connectionFailed_e;
        return 1;
    }

    printf( "Connection successful\n" );
    m_sysDataPtr->wifiStatus = wifi_connected_e;

    // Find what IP has been assigned to the pico
    extern cyw43_t cyw43_state;
    // IPv4 is always 32 bits, and is separated into 4 groups of 8 bits
    uint32_t ipAddress = cyw43_state.netif[CYW43_ITF_STA].ip_addr.addr;
    // Print the IP to terminal so you know what to connect to
    printf( "IP Address: %lu.%lu.%lu.%lu\n", ipAddress & 0xFF, (ipAddress >> 8) & 0xFF, (ipAddress >> 16) & 0xFF, ipAddress >> 24 );

    // This is a pico-sdk function. Does some big brain tcp-pcb stuff, don't need to understand
    httpd_init();

    // Init SSI and CGI as we'll need both
    ssi_init( m_sysDataPtr );
    cgi_init( m_sysDataPtr );

    // Flicker the on-board LED to indicate web server is initialised
    for( int i = 0; i < 3; ++i )
    {
        cyw43_arch_gpio_put( CYW43_WL_GPIO_LED_PIN, 1 );
        sleep_ms( 200 );
        cyw43_arch_gpio_put( CYW43_WL_GPIO_LED_PIN, 0 );
        sleep_ms( 200 );
    }

    return 0;
}

