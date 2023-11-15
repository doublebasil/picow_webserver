#include "cgi.hpp"

// Pointer to system data struct
static tSysData *m_sysDataPtr;

static const char* m_cgiHandler1( int iIndex, int iNumParams, char *pcParam[], char *pcValue[] );

static const tCGI m_cgiHandlers[NUM_OF_CGI_HANDLERS] =
{
    {
        "/led.cgi", m_cgiHandler1
    },
};

void cgi_init( tSysData *sysDataPtr )
{
    m_sysDataPtr = sysDataPtr;

    http_set_cgi_handlers( m_cgiHandlers, NUM_OF_CGI_HANDLERS );
}

// Define a cgiHandler, you could declare multiple
static const char* m_cgiHandler1( int iIndex, int iNumParams, char *pcParam[], char *pcValue[] )
{
    int i;

    printf( "m_cgiHandler1 called with index %d\n", iIndex );

    /* Check the query string
     * Allegedly, a request to turn on LED2 and LED4 would be "/something.cgi?led=2&led=4"
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
