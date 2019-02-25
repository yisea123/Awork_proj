/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief Nand head file
 *
 * \internal
 * \par modification history:
 * - 1.00 17-3-22  vih, first implementation
 * \endinternal
 */

#ifndef __AWBL_NAND_H
#define __AWBL_NAND_H

#ifdef __cplusplus
extern "C" {
#endif    /* __cplusplus    */

#include "apollo.h"
#include "awbus_lite.h"
#include "awbl_nand_bus.h"
#include "mtd/aw_mtd.h"
#include "aw_sem.h"


/** \brief NandFlash�������� */
#define AWBL_NAND_DRV_NAME        "awbl_nand_drv_name"

/**
 * \name nand flash chip attribute
 * @{
 */

/** \brief SAMSUNG K9F2G08ʱ�� */
#define NANDFLASH_K9F2G08_TIMING \
    20, \
    5, \
    15, \
    5, \
    15, \
    5, \
    15, \
    5, \
    15, \
    20, \
    25, \
    30, \
    30, \
    100, \
    10, \
    15, \
    30

/** \brief SAMSUNG K9F2G08 ECCУ��ǿ�� */
#define NANDFLASH_K9F2G08_ECC_STRENGTH \
    4

/** \brief SAMSUNG K9F2G08оƬ��Ϣ */
#define NANDFLASH_K9F2G08 \
    2048, \
    64, \
    64, \
    2048, \
    0, \
    8, \
    128*1024,\
    256*1024*1024, \
    0xEC, \
    0xDA

/** \brief MXIC MX30LF1G08ʱ�� */
#define NANDFLASH_MX30LF1G08_TIMING \
    20, \
    5, \
    15, \
    5, \
    15, \
    5, \
    5, \
    5, \
    15, \
    20, \
    25, \
    50, \
    30, \
    50, \
    15, \
    15, \
    30

/** \brief MXIC MX30LF1G08 ECCУ��ǿ�� */
#define NANDFLASH_MX30LF1G08_ECC_STRENGTH \
    4

/** \brief MXIC MX30LF1G08оƬ��Ϣ */
#define NANDFLASH_MX30LF1G08 \
    2048, \
    64, \
    64, \
    1024, \
    0, \
    8, \
    128*1024,\
    128*1024*1024, \
    0xC2, \
    0xF1

/** \brief MXIC MX30LF2G28ʱ�� */
#define NANDFLASH_MX30LF2G28_TIMING \
    15, \
    5, \
    10, \
    5, \
    10, \
    5, \
    7, \
    5, \
    10, \
    16, \
    25, \
    50, \
    20, \
    100, \
    10, \
    10, \
    20

/** \brief MXIC MX30LF2G28 ECCУ��ǿ�� */
#define NANDFLASH_MX30LF2G28_ECC_STRENGTH \
    8

/** \brief MXIC MX30LF2G28оƬ��Ϣ */
#define NANDFLASH_MX30LF2G28\
    2048, \
    112, \
    64, \
    2048, \
    0, \
    8, \
    128*1024,\
    128*1024*2048, \
    0xC2, \
    0xDA

/** \brief SPANSION S34ML01G2ʱ�� */
#define NANDFLASH_S34ML01G2_TIMING \
    20, \
    5, \
    10, \
    5, \
    10, \
    5, \
    10, \
    5, \
    12, \
    20, \
    25, \
    30, \
    25, \
    100, \
    10, \
    12, \
    25

/** \brief SPANSION S34ML01G2 ECCУ��ǿ�� */
#define NANDFLASH_S34ML01G2_ECC_STRENGTH \
    4

/** \brief SPANSION S34ML01G2оƬ��Ϣ */
#define NANDFLASH_S34ML01G2\
    2048, \
    64, \
    64, \
    1024, \
    0, \
    8, \
    128*1024, \
    128*1024*1024, \
    0x01, \
    0xF1

/** \brief SPANSION S34ML02G2ʱ�� */
#define NANDFLASH_S34ML02G2_TIMING \
    20, \
    5, \
    10, \
    5, \
    10, \
    5, \
    10, \
    15, \
    12, \
    20, \
    25, \
    30, \
    25, \
    100, \
    10, \
    12, \
    25

/** \brief SPANSION S34ML02G2 ECCУ��ǿ�� */
#define NANDFLASH_S34ML02G2_ECC_STRENGTH \
    4

/** \brief SPANSION S34ML02G2оƬ��Ϣ */
#define NANDFLASH_S34ML02G2\
    2048, \
    128, \
    64, \
    2048, \
    0, \
    8, \
    128*1024, \
    128*1024*2048, \
    0x01, \
    0xDA

/**
 * @} nand flash chip attribute
 */

/* standard command */
#define AWBL_NANDFLASH_CMD_READ0             0
#define AWBL_NANDFLASH_CMD_READ1             1
#define AWBL_NANDFLASH_CMD_RNDOUT            5
#define AWBL_NANDFLASH_CMD_PAGEPROG          0x10
#define AWBL_NANDFLASH_CMD_READOOB           0x50
#define AWBL_NANDFLASH_CMD_ERASE1            0x60
#define AWBL_NANDFLASH_CMD_STATUS            0x70
#define AWBL_NANDFLASH_CMD_SEQIN             0x80
#define AWBL_NANDFLASH_CMD_RNDIN             0x85
#define AWBL_NANDFLASH_CMD_READID            0x90
#define AWBL_NANDFLASH_CMD_ERASE2            0xd0
#define AWBL_NANDFLASH_CMD_PARAM             0xec
#define AWBL_NANDFLASH_CMD_GET_FEATURES      0xee
#define AWBL_NANDFLASH_CMD_SET_FEATURES      0xef
#define AWBL_NANDFLASH_CMD_RESET             0xff
#define AWBL_NANDFLASH_CMD_LOCK              0x2a
#define AWBL_NANDFLASH_CMD_UNLOCK1           0x23
#define AWBL_NANDFLASH_CMD_UNLOCK2           0x24
/* expand command for large page */
#define AWBL_NANDFLASH_CMD_READSTART         0x30
#define AWBL_NANDFLASH_CMD_RNDOUTSTART       0xE0
#define AWBL_NANDFLASH_CMD_CACHEDPROG        0x15


#define AWBL_NANDFLASH_ECC_NO_ERR           0x00
#define AWBL_NANDFLASH_ECC_ERR_CORRECTED    0x01
#define AWBL_NANDFLASH_ECC_ERR_UNCORRECTED  0x02

/**
 * \brief  ioctl������ѡ��
 */
typedef enum awbl_nand_ioctl_req {

    /** \brief ��ȡҳ��С */
    AWBL_NAND_PAGE_SIZE,

    /** \brief ��ȡÿ����ҳ������ */
    AWBL_NAND_PAGE_NUM_PER_BLK,

    /** \brief ��ȡ���С */
    AWBL_NAND_BLK_SIZE,

    /** \brief ��ȡ��������� */
    AWBL_NAND_BLK_NUM,

    /** \brief ��ȡ���õ�oob��С */
    AWBL_NAND_OOB_SIZE,

    /** \brief ��ȡƬ��С  */
    AWBL_NAND_CHIP_SIZE,

} awbl_nand_ioctl_req_t;


struct awbl_nand_chip;

/** \brief  NandFlashоƬ������ʱ�� */
struct awbl_nand_timing {

    /* ns for all */
    uint8_t        tcs;        /**< \brief CE setup */
    uint8_t        tch;        /**< \brief CE hold */
    uint8_t        tcls;       /**< \brief CLE setup */
    uint8_t        tclh;       /**< \brief CLE hold */
    uint8_t        tals;       /**< \brief ALE setup */
    uint8_t        talh;       /**< \brief ALE hold */
    uint8_t        tds;        /**< \brief data setup */
    uint8_t        tdh;        /**< \brief data hold */
    uint8_t        trp;        /**< \brief RE pulse width */
    uint8_t        trea;       /**< \brief RE access time */
    uint8_t        tcea;       /**< \brief CE access time */
    uint8_t        tchz;       /**< \brief CE high to output Hi-Z */
    uint8_t        trc;        /**< \brief read cycle time */
    uint8_t        trhz;       /**< \brief RE high to output Hi-Z */
    uint8_t        tclr;       /**< \brief CLE to RE delay */
    uint8_t        twp;        /**< \brief WE pulse width */
    uint8_t        twc;        /**< \brief WE high hold time */
};

/**
 * \brief ECCģʽ
 */
typedef enum awbl_nand_ecc_mode {

    AWBL_NAND_ECC_MODE_NONE = 0,    /**< \brief ��ECC */
    AWBL_NAND_ECC_MODE_SW_HAM,      /**< \brief ʹ�����ECC�������� */
    AWBL_NAND_ECC_MODE_SW_BCH,      /**< \brief ʹ�����ECC��BCH�㷨 */

    AWBL_NAND_ECC_MODE_HW,          /**< \brief ʹ��Ӳ��ECC */
    AWBL_NAND_ECC_MODE_HW_OOBFIRST  /**< \brief ʹ��Ӳ��ECC���ȶ�ȡOOB���� */

} awbl_nand_ecc_mode_t;


/**
 * \brief OOB������Ϣ
 */
struct awbl_nand_ooblayout {
    const struct aw_mtd_oob_space *ptr_eccpos;  /**< \brief ָ��ECCλ���������� */
    int                            cnt_eccpos;  /**< \brief ECCλ�����������Ա���� */
    const struct aw_mtd_oob_space *ptr_freepos; /**< \brief ָ�����λ���������� */
    int                            cnt_freepos; /**< \brief ����λ�����������Ա���� */
};


struct awbl_nand_chip_ecc_serv {
    void (*hwctl)         (struct awbl_nand_chip      *p_this, int mode);

    int (*calculate)      (struct awbl_nand_chip      *p_this,
                           const uint8_t              *dat,
                           uint8_t                    *ecc_code);

    int (*correct)        (struct awbl_nand_chip      *p_this,
                           uint8_t                    *dat,
                           uint8_t                    *read_ecc,
                           uint8_t                    *calc_ecc);

    int (*read_page_raw)  (struct awbl_nand_chip      *p_this,
                           uint8_t                    *buf,
                           bool_t                      oob_required,
                           uint32_t                    page);

    int (*write_page_raw) (struct awbl_nand_chip      *p_this,
                           uint8_t                    *buf,
                           bool_t                      oob_required,
                           uint32_t                    page);

    int (*read_page)      (struct awbl_nand_chip      *p_this,
                           uint8_t                    *buf,
                           uint32_t                    page);

    int (*write_page)     (struct awbl_nand_chip      *p_this,
                           uint8_t                    *buf,
                           uint32_t                    page);

    int (*write_oob_raw)  (struct awbl_nand_chip *p_this, uint32_t page);

    int (*read_oob_raw)   (struct awbl_nand_chip *p_this, uint32_t page);

    int (*read_oob)       (struct awbl_nand_chip *p_this, uint32_t page);

    int (*write_oob)      (struct awbl_nand_chip *p_this, uint32_t page);

    int (*read_oob_free)       (struct awbl_nand_chip *p_this,
                                uint32_t page,
                                uint32_t offs,
                                char    *data,
                                uint32_t data_len);

    int (*write_oob_free)      (struct awbl_nand_chip *p_this,
                                uint32_t page,
                                uint32_t offs,
                                char    *data,
                                uint32_t data_len);

    int (*read_oob_ecc)       (struct awbl_nand_chip *p_this,
                               uint32_t page,
                               uint8_t *ecc,
                               bool_t   need_read_oob);

    int (*write_oob_ecc)      (struct awbl_nand_chip *p_this,
                               uint32_t page,
                               uint8_t *ecc,
                               bool_t   need_write_oob);
};

struct awbl_nand_chip_ecc {
    awbl_nand_ecc_mode_t mode;

    int steps;
    int size;
    int bytes;
    int total_bytes;
    int strength;
    int prepad;
    int postpad;
    uint32_t options;
    uint8_t *ecc_buf;
    void *priv;

    struct awbl_nand_chip_ecc_serv *p_serv;
};


struct awbl_nand_buffers {

    /** \brief ��ż���õ���ECC�Ļ�����,��СΪoob_layout��ecc�ĳ��� */
    uint8_t *calc_ecc;

    /** \brief oob�Ļ���������СΪoobsize */
    uint8_t *oob_buf;

    /** \brief ���ݻ��棬page+oobsize */
    uint8_t *data_buf;
};

/** \brief NandFlash������Ϣ */
struct awbl_nand_partition {

    /** \brief �������� */
    const char                  *name;

    /** \brief ������ʼ���� */
    uint32_t                     start_blk_num;

    /** \brief ������ֹ���� */
    uint32_t                     end_blk_num;

        /** \brief ��ʼҳƫ�� */
    size_t                       page_offset;
};

struct awbl_nand_chip_serv {

    int     (*write_buf)      (struct awbl_nand_chip *p_this,
                               uint32_t page,
                               uint32_t col,
                               uint8_t *buf,
                               int      len,
                               bool_t   oob_required);

    int     (*read_buf)       (struct awbl_nand_chip *p_this,
                               uint32_t page,
                               uint32_t col,
                               uint8_t *buf,
                               int      len,
                               bool_t   oob_required);

    bool_t   (*block_is_bad)  (struct awbl_nand_chip *p_this, uint32_t page);

    int      (*block_markbad) (struct awbl_nand_chip *p_this, uint32_t page);

    int      (*erase)         (struct awbl_nand_chip *p_this, uint32_t page);

    int      (*reset)         (struct awbl_nand_chip *p_this);
};

struct awbl_nand_chip {

    /** \brief �����豸 */
    struct awbl_dev            awdev;

    struct aw_mtd_info         mtd;
    struct aw_mtd_part_info   *p_mtd_part;
    uint8_t                    mtd_part_cnt;

    AW_MUTEX_DECL(op_mutex);

    struct awbl_nand_chip_serv serv;

    struct awbl_nandbus       *p_bus;

    void                      *p_cur_chip;

    int                        chip_delay;

    uint32_t                   options;
    uint32_t                   bbt_options;

    /** \brief log2(page_size) */
    int                        page_shift;

    int                        phys_erase_shift;

    int                        bbt_erase_shift;
    int                        erase_align_mask;

    /** \brief ������λ������ڿ��п���ʼλ�õ�ƫ�� */
    uint8_t                    bad_blk_byte_offs;

    int                        chip_shift;
    int                        numchips;
    uint64_t                   chipsize;
    int                        pagemask;
    int                        pagebuf;
    uint32_t                   pagebuf_bitflips;
    int                        subpagesize;
    uint8_t                    bits_per_cell;

    uint16_t                   ecc_strength_ds;
    uint16_t                   ecc_step_ds;

    int                        badblockpos;
    int                        badblockbits;

    int                        read_retries;

    int                        error;

    uint8_t                   *p_oob_poi;

    /** \brief ÿҳ���������С */
    uint8_t                    oob_size;

    struct awbl_nand_chip_ecc  ecc;
    struct awbl_nand_buffers  *buffers;

    /** \brief oob���� */
    struct aw_mtd_oob_layout   oob_layout;

    const struct awbl_nand_partition *p_partition_tab;

    const struct awbl_nand_ooblayout *p_nand_ooblayout;

    /** \brief �������� */
    int                               npartition;

    bool_t                            nand_init;

    void                             *priv;
};


/**
 * \brief nand�����ݣ���ecc���飬���ܿ�ҳ
 *
 * \param[in] p_chip          : nand�豸�ṹ��
 * \param[in] page            : Ҫ����ҳ��ַ
 * \param[in] col             : Ҫ����ҳ�ڵ�ַ
 * \param[in] buf             : ������ݵ�buf
 * \param[in] len             : ������
 *
 * \retval �����ɹ�����AW_OK, ���򷵻�aw_err_t�Ĵ�������
 */
aw_err_t awbl_nand_read ( struct awbl_nand_chip *p_chip,
						  uint32_t               page,
						  uint32_t               col,
						  uint8_t               *buf,
						  int                    len);

/**
 * \brief nandд���ݣ���ecc���飬���ܿ�ҳ
 *
 * \param[in] p_chip          : nand�豸�ṹ��
 * \param[in] page            : ҳ��ַ
 * \param[in] col             : ҳ�ڵ�ַ
 * \param[in] buf             : ������ݵ�buf
 * \param[in] len             : �����ĳ���
 *
 * \retval �����ɹ�����AW_OK, ���򷵻�aw_err_t�Ĵ�������
 */
aw_err_t awbl_nand_write ( struct awbl_nand_chip *p_chip,
						   uint32_t               page,
						   uint32_t               col,
						   uint8_t               *buf,
						   int                    len);

/**
 * \brief nandҳ�����ݣ���ecc���飬һ�β�������Ϊһ��ҳ
 *
 * \param[in] p_chip          : nand�豸�ṹ��
 * \param[in] ipage           : ҳ��ַ
 * \param[out] buf            : ������ݵ�buf
 *
 * \retval �����ɹ�����AW_OK, ���򷵻�aw_err_t�Ĵ�������
 */
aw_err_t awbl_nand_page_read ( struct awbl_nand_chip *p_chip,
							   uint8_t               *buf,
							   uint32_t               ipage);

/**
 * \brief nandҳд���ݣ���ecc���飬һ�β�������Ϊһ��ҳ
 *
 * \param[in] p_chip          : nand�豸�ṹ��
 * \param[in] ipage           : ҳ��ַ
 * \param[in] buf             : ������ݵ�buf
 *
 * \retval �����ɹ�����AW_OK, ���򷵻�aw_err_t�Ĵ�������
 */
aw_err_t awbl_nand_page_write ( struct awbl_nand_chip *p_chip,
								uint8_t               *buf,
								uint32_t               ipage);

/**
 * \brief дoob����free��
 *
 * \param[in] p_chip          : nand�豸�ṹ��
 * \param[in] ipage           : ҳ��ַ
 * \param[in] offs            : ��free����ƫ��
 * \param[in] oob_data        : ����buff
 * \param[in] data_len        : д�볤��
 *
 * \retval  �����ɹ�����AW_OK, ���򷵻�aw_err_t�Ĵ�������
 *
 * \note    ��oob��д��ʱ��Ӧ��֪��free���Ĵ�С����д���Ȳ��ɳ���free���Ĵ�С��
 *          ����awbl_nand_ioctl(p_chip, AWBL_NAND_OOB_SIZE, &free_szie);
 *          �ɵõ�free���Ĵ�С
 */
aw_err_t awbl_nand_oob_write ( struct awbl_nand_chip    *p_chip,
							   uint32_t                  ipage,
							   uint32_t                  offs,
							   char                     *oob_data,
							   uint32_t                  data_len);

/**
  * \brief ��oob����free��
 *
 * \param[in] p_chip          : nand�豸�ṹ��
 * \param[in] ipage           : ҳ��ַ
 * \param[in] offs            : ��free����ƫ��
 * \param[in] oob_data        : ����buff
 * \param[in] data_len        : ������
 *
 * \retval �����ɹ�����AW_OK, ���򷵻�aw_err_t�Ĵ�������
 *
 * \note    ��oob����дʱ��Ӧ��֪��free���Ĵ�С����д���Ȳ��ɳ���free���Ĵ�С��
 *          ����awbl_nand_ioctl(p_chip, AWBL_NAND_OOB_SIZE, &free_szie);
 *          �ɵõ�free���Ĵ�С
 */
aw_err_t awbl_nand_oob_read ( struct awbl_nand_chip    *p_chip,
							  uint32_t                  ipage,
							  uint32_t                  offs,
							  char                     *oob_data,
							  uint32_t                  data_len);

/**
 * \brief �����
 *
 * \param[in] p_chip          : nand�豸�ṹ��
 * \param[in] iblk            : ���ַ
 *
 * \retval �����ɹ�����AW_OK, ���򷵻�aw_err_t�Ĵ�������
 */
aw_err_t awbl_nand_blk_erase (struct awbl_nand_chip *p_chip,
							  uint32_t               iblk);

/**
 * \brief �жϻ���
 *
 * \param[in] p_chip          : nand�豸�ṹ��
 * \param[in] iblk            : ���ַ
 *
 * \retval �����жϽ��
 */
bool_t awbl_nand_blk_is_bad ( struct awbl_nand_chip *p_chip,
							  uint32_t               iblk);

/**
 * \brief ��ǻ���
 *
 * \param[in] p_chip          : nand�豸�ṹ��
 * \param[in] iblk            : ���ַ
 *
 * \retval �����ɹ�����AW_OK, ���򷵻�aw_err_t�Ĵ�������
 */
aw_err_t awbl_nand_blk_markbad ( struct awbl_nand_chip *p_chip,
								 uint32_t               iblk);



/**
 * \brief IOCTL
 *
 * \param[in]     p_chip          : nand�豸�ṹ��
 * \param[in]     req             : ����
 * \param[in/out] dat             : ���ݵ�ַ
 *
 * \retval �����ɹ�����AW_OK, ���򷵻�aw_err_t�Ĵ�������
 *
 * \par ����
 * \code
 *
 *  uint32_t dat = 0;
 *
 *  //��ȡ��nandflash��ҳ��С
 *  awbl_nand_ioctl(p_chip, AWBL_NAND_PAGE_SIZE, &dat);
 */
aw_err_t awbl_nand_ioctl (  struct awbl_nand_chip *p_chip,
                            awbl_nand_ioctl_req_t  req,
                            void                  *dat);



struct awbl_nand_chip *awbl_mtd_get_nand(struct aw_mtd_info *mtd);

struct awbl_nand_chip *awbl_mtd_set_nand(struct aw_mtd_info *mtd, void *p_nand);


void *awbl_nand_get_data(struct awbl_nand_chip *p_nand);

void awbl_nand_set_data(struct awbl_nand_chip *p_nand, void *priv);

/*
 * Check if it is a SLC nand.
 * The !nand_is_slc() can be used to check the MLC/TLC nand chips.
 * We do not distinguish the MLC and TLC now.
 */
bool_t awbl_nand_is_slc(struct awbl_nand_chip *chip);

/**
 * \brief nand�������Ĺ���
 *
 * \param p_nand             : nand�ṹ��
 * \param priv               : ˽������
 * \param p_partition_tab    : �������ַ
 * \param npartitions        : ����������
 * \param p_nand_ooblayout   : oob���ֵ�ַ
 * \param ecc_strength       : ecc strength
 * \param ecc_mode           : ecc mode
 * \param chip_size          : Ƭ��С
 * \param blk_size           : ���С
 * \param page_size          : ҳ��С
 * \param oob_size           : oob��С
 * \param bad_blk_byte_offs  : �����ǵ�ƫ��
 * \param bits_per_cell      : ÿ��cell�ܴ洢��bit����
 *
 * \retval  aw_err_t
 */
aw_err_t awbl_nand_chip_make(
    struct awbl_nand_chip            *p_nand,
    void                             *priv,
    const struct awbl_nand_partition *p_partition_tab,
    int                               npartitions,
    const struct awbl_nand_ooblayout *p_nand_ooblayout,
    uint32_t                          ecc_strength,
    enum awbl_nand_ecc_mode           ecc_mode,
    uint64_t                          chip_size,
    uint32_t                          blk_size,
    uint16_t                          page_size,
    uint8_t                           oob_size,
    uint8_t                           bad_blk_byte_offs,
    uint8_t                           bits_per_cell);

aw_err_t awbl_nand_scan_tail(struct awbl_nand_chip *p_nand);

aw_err_t awbl_nand_read_id (struct awbl_nand_chip *p_nand,
                            uint8_t               *p_ids,
                            uint8_t                id_len);
#endif /* __AWBL_NAND_H */

