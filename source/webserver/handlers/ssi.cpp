#include "ssi.hpp"

/* 
Note on __not_in_flash and __time_critical_func
These are attributes to arrays and functions respectively, which are defined in
the pico-sdk. They tell the compiler to always keep something in RAM, whereas 
a normally declared array or function might get moved back to flash to make space
in RAM. By keeping something in RAM, you know you can always access it quickly.
This eliminates the potential for "flash latency", which could mess up something
that needs to happen quickly
*/

// A pointer to the system data struct
static tSysData *m_sysDataPtr;

static const char* __not_in_flash("httpd") m_ssiTags[] = {
    "btnState",
    "btnBg",
};

static uint16_t __time_critical_func( m_ssiHandler )(int tagIndex, char *pcInsert, int iInsertLen);

void ssi_init( tSysData *sysDataPtr )
{
    m_sysDataPtr = sysDataPtr;

    // Ensure that the m_ssiTags don't exceed the maximum length
    for( size_t i = 0; i < LWIP_ARRAYSIZE( m_ssiTags ); ++i )
    {
        // I think an assert will get the program stuck here if a tag is too long
        LWIP_ASSERT( "An SSI tag exceeds LWIP_HTTPD_MAX_TAG_NAME_LEN",
                    strlen( m_ssiTags[i] ) <= LWIP_HTTPD_MAX_TAG_NAME_LEN );
    }

    // Tell the pico-sdk to use our m_ssiHandler function
    http_set_ssi_handler( m_ssiHandler,
                          m_ssiTags,
                          LWIP_ARRAYSIZE( m_ssiTags ) );
}

// Module specific functions

// Define an m_ssiHandler function as time-critical (reduces flash latency)
static uint16_t __time_critical_func( m_ssiHandler )(int tagIndex, char *pcInsert, int iInsertLen)
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
