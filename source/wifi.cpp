#include "wifi.hpp"

int wifi_init()
{
    /*
    From this webpage: https://arduino-pico.readthedocs.io/en/latest/wifi.html
    It seems that the wifi chip can be in station (STA) mode or access point (AP) mode
    I'm using STA mode because that's what other people have done
    */
    cyw43_arch_enable_sta_mode();
}
