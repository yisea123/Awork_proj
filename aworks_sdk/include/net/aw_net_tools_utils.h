#include "aworks.h"

#include "aw_wifi_types.h"

#include "net/aw_net.h"
#include "net/aw_netif.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int aw_net_tools_str_2_ip4_msk (const char *str, struct in_addr *ip, struct in_addr *nm);

const char *aw_net_tools_netif_type_2_str (aw_netif_type_t type);

aw_wifi_country_code_t aw_net_tools_hlp_str_2_wifi_ccode (const char *str);
void aw_net_tools_hlp_wifi_ccode_2_str (aw_wifi_country_code_t ccode, char * const str);

/* end of file */
