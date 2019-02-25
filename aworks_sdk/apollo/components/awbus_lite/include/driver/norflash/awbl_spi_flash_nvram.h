/*
 * awbl_spi_flash_mtd.h
 *
 *  Created on: 2017Äê8ÔÂ31ÈÕ
 *      Author: wengyedong
 */

#ifndef __AWBL_SPI_FLASH_NVRAM_H
#define __AWBL_SPI_FLASH_NVRAM_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "driver/norflash/awbl_spi_flash.h"
#include "awbl_nvram.h"




struct awbl_spi_flash_nvram_info {
    const struct awbl_nvram_segment   *p_seglst;
    uint_t                             seglst_count;
    uint8_t                           *p_blk_buf;     /**< \brief buffer for NVRAM to write */
};




aw_err_t awbl_spi_flash_nvram_get (struct awbl_dev *p_awdev,
                                   char            *p_name,
                                   int              unit,
                                   void            *p_buf,
                                   int              offset,
                                   int              len);

aw_err_t awbl_spi_flash_nvram_set (struct awbl_dev *p_awdev,
                                   char            *p_name,
                                   int              unit,
                                   char            *p_buf,
                                   int              offset,
                                   int              len);


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_SPI_FLASH_NVRAM_H */
