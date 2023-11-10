#ifndef SYSDATA_HPP
#define SYSDATA_HPP

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    wifiUninitialised_e,
    wifiMax_e,
} eWifiStatus;

typedef struct
{
    eWifiStatus wifiStatus = wifiUninitialised_e;
} tSysData;

#endif /* SYSDATA_HPP */
