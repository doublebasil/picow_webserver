#include "wifi.hpp"
#include "config.h"

// Note LWIP is Light-weight IP

// SERVER SIDE INCLUDES MODULE DATA
/* __not_in_flash is a pico-sdk macro which ensures this array will be placed in RAM
I presume this is for speed
When declared as __not_in_flash, the array needs a group name, which is "httpd"
By default, the tags have a maximum length of 8. See ssi_init where this is checked
*/
static const char* __not_in_flash("httpd") ssiTags[] = {
    "Tom",
    "Snowy",
    "Jerry", // I don't know what these tags are for yet, so I'll change them later
    "Boo",
    "Rud",
};

// SERVER SIDE INCLUDES MODULE FUNCTIONS
static void ssi_init( void );
// Define an ssi_handler function as time-critical
static uint16_t __time_critical_func( ssiHandler )(int tagIndex, char *pcInsert, int iInsertLen)
{
    size_t printed;
    switch( tagIndex )
    {
        case 0: // "Tom"
        {
            printed = snprintf( pcInsert, iInsertLen, "Tom, here is a random number :) %d", rand() );
            break;
        }
        case 1: // "Snowy"
        {
            printed = snprintf( pcInsert, iInsertLen, "Snowy, here is a random number :) %d", rand() );
            break;
        }
        case 2:
        case 3:
        case 4:
        default:
        {
            printed = snprintf( pcInsert, iInsertLen, "cba to add these" );
            break;
        }
    }

    // Ensure 'printed' can fit in a 16 bit variable
    LWIP_ASSERT( "Variable 'printed' too large for 16 bits", printed < 0xFFFF );

    return (uint16_t) printed;
}

// COMMON GATEWAY INTERFACE MODULE FUNCTIONS
static int cgi_init( void );

// PUBLIC MODULE FUNCTIONS
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

    printf( "Connection successful\n" );
    sysDataPtr->wifiStatus = wifi_connected_e;

    // Find what IP has been assigned to the pico
    extern cyw43_t cyw43_state;
    // IPv4 is always 32 bits, and is separated into 4 groups of 8 bits
    uint32_t ipAddress = cyw43_state.netif[CYW43_ITF_STA].ip_addr.addr;
    printf( "IP Address: %lu.%lu.%lu.%lu\n", ipAddress & 0xFF, (ipAddress >> 8) & 0xFF, (ipAddress >> 16) & 0xFF, ipAddress >> 24 );

    // This is a pico-sdk function. Does some clever tcp-pcb stuff idk
    httpd_init();

    // We need an ssi-cgi server
    ssi_init();
    cgi_init();

    return 0;
}

// Server Side Includes functions
static void ssi_init( void )
{
    // Ensure that the ssiTags don't exceed the maximum length
    for( size_t i = 0; i < LWIP_ARRAYSIZE( ssiTags ); ++i )
    {
        // I think an assert will get the program stuck here if a tag is too long
        LWIP_ASSERT( "An SSI tag exceeds LWIP_HTTPD_MAX_TAG_NAME_LEN",
                    strlen( ssiTags[i] ) <= LWIP_HTTPD_MAX_TAG_NAME_LEN );
    }

    // Tell the pico-sdk to use our ssiHandler function
    http_set_ssi_handler( ssiHandler,
                          ssiTags,
                          LWIP_ARRAYSIZE( ssiTags ) );
}

// Common Gateway Interface functions
static int cgi_init( void )
{
    return 0;
}
