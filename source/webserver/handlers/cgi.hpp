#ifndef CGI_HPP
#define CGI_HPP

#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "sysdata.h"

#define NUM_OF_CGI_HANDLERS     ( 2 )

void cgi_init( tSysData *sysDataPtr );

#endif /* CGI_HPP */
