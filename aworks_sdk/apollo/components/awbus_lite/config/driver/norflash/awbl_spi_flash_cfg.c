
#include "apollo.h"
#include "awbus_lite.h"
#include "driver/norflash/awbl_spi_flash.h"
#include "driver/norflash/awbl_spi_flash_nvram.h"

#ifdef AW_CFG_SPI_FLASH_NVRAM
AWBL_METHOD_IMPORT(awbl_nvram_get);
AWBL_METHOD_IMPORT(awbl_nvram_set);
#endif

aw_const struct awbl_dev_method g_spi_flash_methods[] = {
#ifdef AW_CFG_SPI_FLASH_NVRAM
    AWBL_METHOD(awbl_nvram_get, awbl_spi_flash_nvram_get),
    AWBL_METHOD(awbl_nvram_set, awbl_spi_flash_nvram_set),
#endif
    AWBL_METHOD_END
};



void awbl_spi_flash_cfg (void)
{
    awbl_spi_flash_lib_init();
}


