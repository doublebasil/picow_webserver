#include "webserver.hpp"
#include "config.h"

#define NUM_OF_CGI_HANDLERS ( 1 )

// SSI is for updating the HTML, and is controlled by the pico
// CGI is for changing the data on the pico, based on user interaction on the web

// Note LWIP is Light-weight IP, it's a TCP IP stack and it's basically magic

tSysData* m_sysDataPtr;

// SERVER SIDE INCLUDES MODULE DATA
/* __not_in_flash is a pico-sdk macro which ensures this array will be placed in RAM
This is a "premature optimisation" which prevents flash latency
When declared as __not_in_flash, the array needs a group name, which is "httpd"
By default, the tags have a maximum length of 8. See ssi_init where this is checked
*/
static const char* __not_in_flash("httpd") ssiTags[] = {
    "btnState",
    "btnBg",
};

// SERVER SIDE INCLUDES MODULE FUNCTIONS
static void ssi_init( void );
// Define an ssiHandler function as time-critical (reduces flash latency)
static uint16_t __time_critical_func( ssiHandler )(int tagIndex, char *pcInsert, int iInsertLen)
{
    size_t printed;
    bool ledState;
    switch( tagIndex )
    {
        case 0: // "btnState"
        {
            // This is for changing the html checkbox to checked or not
            ledState = m_sysDataPtr->builtInLedState;
            if( ledState == true )
                printed = snprintf( pcInsert, iInsertLen, "checked" );
            else
                printed = snprintf( pcInsert, iInsertLen, " " );
            
            break;
        }
        case 1: // "btnBg"
        {
            // Update the text background based on the LED state
            ledState = m_sysDataPtr->builtInLedState;
            if( ledState == true )
                printed = snprintf( pcInsert, iInsertLen, "\"background-color:green;\"" );
            else
                printed = snprintf( pcInsert, iInsertLen, "\"background-color:red;\"" );

            break;
        }
        default:
        {
            printed = 0;
            break;
        }
    }

    // Ensure 'printed' can fit in a 16 bit variable
    LWIP_ASSERT( "Variable 'printed' too large for 16 bits", printed < 0xFFFF );

    return (uint16_t) printed;
}

// COMMON GATEWAY INTERFACE MODULE FUNCTIONS
static void cgi_init( void );

// COMMON GATEWAY INTERFACE MODULE DATA
static const tCGI cgiHandlers[NUM_OF_CGI_HANDLERS] =
{
    {
        "/led.cgi", cgiHandler1
    },
};

// PUBLIC MODULE FUNCTIONS
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
    printf( "IP Address: %lu.%lu.%lu.%lu\n", ipAddress & 0xFF, (ipAddress >> 8) & 0xFF, (ipAddress >> 16) & 0xFF, ipAddress >> 24 );

    // This is a pico-sdk function. Does some clever tcp-pcb stuff idk
    httpd_init();

    // We need an ssi-cgi server
    ssi_init();
    cgi_init();

    return 0;
}

// SERVER SIDE INCLUDES MODULE FUNCTIONS
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

// COMMON GATEWAY INTERFACE MODULE FUNCTIONS
static void cgi_init( void )
{
    http_set_cgi_handlers( cgiHandlers, NUM_OF_CGI_HANDLERS );
}

const char* cgiHandler1( int iIndex, int iNumParams, char *pcParam[], char *pcValue[] )
{
    int i;

    printf( "cgiHandler1 called with index %d\n", iIndex );

    /* Check the query string
     * Allgedly, a request to turn on LED2 and LED4 would be "/something.cgi?led=2&led=4"
     */

    // If no response is given, turn led off
    bool newState = false;

    for( i = 0; i < iNumParams; ++i )
    {
        if( strcmp( pcParam[i], "led" ) == 0 )
        {
            // Strings are equal
            newState = true;
        }
    }

    cyw43_arch_gpio_put( CYW43_WL_GPIO_LED_PIN, newState );
    m_sysDataPtr->builtInLedState = newState;

    return "/index.shtml";
}
