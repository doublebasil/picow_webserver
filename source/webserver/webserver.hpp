#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include <stdint.h>

#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwipopts.h" // Required for compile, copied from https://github.com/krzmaz/pico-w-webserver-example, you can find similar files in pico-examples

#include "sysdata.h"

int wifi_init( tSysData* sysDataPtr );

int wifi_runServer();

// Define a cgiHandler
const char* cgiHandler1( int iIndex, int iNumParams, char *pcParam[], char *pcValue[] );

#endif /* WEBSERVER_HPP */
