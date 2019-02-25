#ifndef INCLUDED_WWD_BUS_PROTOCOL_H
#define INCLUDED_WWD_BUS_PROTOCOL_H

#if defined(AW_DRV_AWBL_CYW43362_WIFI_SDIO)
#include "SDIO/wwd_bus_protocol.h"
#elif defined(AW_DRV_AWBL_CYW43362_WIFI_SPI)
#include "SPI/wwd_bus_protocol.h"
#else
#error "Specify wwd bus protocol pls."
#endif

#endif
