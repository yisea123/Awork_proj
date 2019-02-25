/*
 * awbl_nor_flash.h
 *
 *  Created on: 2015-5-20
 *      Author: ehf
 */

#ifndef AWBL_NOR_FLASH_H_
#define AWBL_NOR_FLASH_H_

#include "aw_spi.h"
#include "awbl_nvram.h"
#include "aw_sem.h"

#define AWBL_NOR_FLASH_NAME   "awbl_nor_flash"

typedef struct awbl_nor_flash_devinfo{
	aw_const struct awbl_nvram_segment *p_seg_list;
	uint32_t   seg_count;

	uint32_t   base_addr;						/* norflash在系统中起始地址 */
	uint8_t    byte_mode;					/* 数据宽度 8/16*/
	uint32_t  sector_size;						/* 扇区大小 */
	uint32_t  sector_cnt;						/* 扇区数量 */
	uint32_t  reserved_sectors;			/* 保留扇区数 */

	const char *name;
	uint8_t    *p_bulk_buff;
    void (*pfunc_plfm_init)(void);
}awbl_nor_flash_devinfo_t;

/**
 * \brief nor flash 设备实例
 */
typedef struct awbl_nor_flash_dev {
    struct awbl_dev nor_dev;
	AW_MUTEX_DECL(devlock);             /** \brief 设备锁 */
} awbl_nor_flash_dev_t;

/**
 * \brief nor flash driver register
 */
void awbl_nor_flash_drv_register (void);

#endif /* AWBL_NOR_FLASH_H_ */
