/*
 * awbl_spi_flash_mtd.h
 *
 *  Created on: 2017Äê8ÔÂ31ÈÕ
 *      Author: wengyedong
 */

#ifndef __AWBL_SPI_FLASH_MTD_H
#define __AWBL_SPI_FLASH_MTD_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "driver/norflash/awbl_spi_flash.h"
#include "mtd/aw_mtd.h"




struct awbl_spi_flash_mtd_info {
    uint_t      start_blk;
    uint_t      nblks;
};




struct awbl_spi_flash_mtd {
    struct aw_mtd_info                     mtd;
    struct awbl_spi_flash_dev             *p_flash;
    const struct awbl_spi_flash_mtd_info  *p_info;

    off_t     erase_align_mask;       /** \brief mask erase align on block boundary */
    int       addr_offset;            /** \brief start address in the full chip */
};




aw_err_t awbl_spi_flash_mtd_init (struct awbl_spi_flash_dev *p_flash,
                                  void                      *p_obj,
                                  const void                *p_info);



#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_SPI_FLASH_MTD_H */
