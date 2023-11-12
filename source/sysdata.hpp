#ifndef SYSDATA_HPP
#define SYSDATA_HPP

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    wifi_uninitialised_e,
    wifi_initFailed_e,
    wifi_notConnected_e,
    wifi_connecting_e,
    wifi_connectionFailed_e,
    wifi_connected_e,
    wifi_max_e,
} eWifiStatus;

typedef struct
{
    eWifiStatus wifiStatus = wifi_uninitialised_e;
} tSysData;

#endif /* SYSDATA_HPP */
