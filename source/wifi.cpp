#include "wifi.hpp"
#include "config.h"

int wifi_init( tSysData* sysDataPtr )
{
    // From this webpage: https://arduino-pico.readthedocs.io/en/latest/wifi.html
    // It seems that the wifi chip can be in station (STA) mode or access point (AP) mode
    // I'm using STA mode because that's what other people have done
    cyw43_arch_enable_sta_mode();

    // Set the power management mode
    cyw43_wifi_pm(&cyw43_state, cyw43_pm_value(CYW43_NO_POWERSAVE_MODE, 20, 1, 1, 1));

    return 0;
}

int wifi_runServer( tSysData* sysDataPtr )
{
    return 0;
}
