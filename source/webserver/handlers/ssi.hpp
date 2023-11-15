#ifndef SSI_HPP
#define SSI_HPP

#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "sysdata.h"

void ssi_init( tSysData *sysDataPtr );

#endif /* SSI_HPP */
