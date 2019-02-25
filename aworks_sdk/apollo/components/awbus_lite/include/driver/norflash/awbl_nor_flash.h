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

	uint32_t   base_addr;						/* norflash��ϵͳ����ʼ��ַ */
	uint8_t    byte_mode;					/* ���ݿ�� 8/16*/
	uint32_t  sector_size;						/* ������С */
	uint32_t  sector_cnt;						/* �������� */
	uint32_t  reserved_sectors;			/* ���������� */

	const char *name;
	uint8_t    *p_bulk_buff;
    void (*pfunc_plfm_init)(void);
}awbl_nor_flash_devinfo_t;

/**
 * \brief nor flash �豸ʵ��
 */
typedef struct awbl_nor_flash_dev {
    struct awbl_dev nor_dev;
	AW_MUTEX_DECL(devlock);             /** \brief �豸�� */
} awbl_nor_flash_dev_t;

/**
 * \brief nor flash driver register
 */
void awbl_nor_flash_drv_register (void);

#endif /* AWBL_NOR_FLASH_H_ */
