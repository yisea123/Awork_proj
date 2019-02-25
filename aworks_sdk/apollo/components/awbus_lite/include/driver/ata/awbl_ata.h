/*******************************************************************************
*                                 Apollo
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
 * \brief ATA class
 *
 * \internal
 * \par modification history:
 * - 1.00 17-06-24  anu, first implementation
 * \endinternal
 */

#ifndef __AWBL_ATA_H
#define __AWBL_ATA_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#define AWBL_ATA_LBA_MAX_ADDR                  (0X01 << 28) /* LBA28最大的寻址地址 */

/* ATA Command type Definitions 下面的命令表请参考ATA-ATAPI-6 Annex E */
typedef uint8_t awbl_ata_cmd_type_t;

/* ATA Reset */
#define AWBL_ATA_CMD_DEV_RESET                 (0x01u)  /**< Reset the IDE Interface (ATA Bus)    */
#define AWBL_ATA_CMD_DEV_UNRESET               (0x02u)  /**< Un-Reset the IDE Interface (ATA Bus) */

/* ATA Set Feature command Sub Commmand defines */
#define AWBL_ATA_CMD_SET_MULT                  (0xC6u)  /**< Enable ATA Multiple Read/Write  */
#define AWBL_ATA_CMD_SET_SPEED                 (0x03u)  /**< Enable support for DMA/UDMA Modes */
#define AWBL_ATA_CMD_SET_ENBREMSTATUS          (0x95u)  /**< Enable Removable Media Status notification */
#define AWBL_ATA_CMD_SET_DISREMSTATUS          (0x31u)  /**< Disable Removable Media Status notification */

/* ATA READ command Flavours */
#define AWBL_ATA_CMD_READ                      (0x20u)  /**< Read PIO Sectors              */
#define AWBL_ATA_CMD_READ_MUL                  (0xC4u)  /**< Read PIO Multiple Sectors     */
#define AWBL_ATA_CMD_READ_DMA                  (0xC8u)  /**< Read using DMA (Ultra/MW)     */
#define AWBL_ATA_CMD_READ_DMA_QED              (0xC7u)  /**< Read DMA in Queued Mode       */
#define AWBL_ATA_CMD_READ_EXT                  (0x24u)  /**< Read PIO Sectors 48 Bit mode  */
#define AWBL_ATA_CMD_READ_MUL_EXT              (0x29u)  /**< Read PIO Multiple 48 Bit mode */
#define AWBL_ATA_CMD_READ_DMA_EXT              (0x25u)  /**< Read DMA 48 Bit Mode mode     */
#define AWBL_ATA_CMD_READ_DMA_QED_EXT          (0x26u)  /**< Read DMA Queued 48 Bit mode   */

/* ATA WRITE command Flavours */
#define AWBL_ATA_CMD_WRITE                     (0x30u)  /**< Write PIO Sectors              */
#define AWBL_ATA_CMD_WRITE_MUL                 (0xC5u)  /**< Write PIO Multiple Sectors     */
#define AWBL_ATA_CMD_WRITE_DMA                 (0xCAu)  /**< Write using DMA (Ultra/MW)     */
#define AWBL_ATA_CMD_WRITE_DMA_QED             (0xCCu)  /**< Write DMA in Queued Mode       */
#define AWBL_ATA_CMD_WRITE_EXT                 (0x34u)  /**< Write PIO Sectors 48 Bit mode  */
#define AWBL_ATA_CMD_WRITE_MUL_EXT             (0x39u)  /**< Write PIO Multiple 48 Bit mode */
#define AWBL_ATA_CMD_WRITE_DMA_EXT             (0x35u)  /**< Write DMA 48 Bit Mode mode     */
#define AWBL_ATA_CMD_WRITE_DMA_QUEUED_EXT      (0x36u)  /**< Write DMA Queued 48 Bit mode   */
#define AWBL_ATA_CMD_CFA_WRITE_WO_ERASE        (0x38u)  /**< CFA Write Sectors without erase */
#define AWBL_ATA_CMD_CFA_WRITE_MUL_WO_ERASE    (0xCDu)  /**< CFA Write Mult Sectors without Erase   */
#define AWBL_ATA_CMD_CFA_ERASE                 (0xC0u)  /**< CFA Sector Erase               */

/* ATA Generic command Defines */
#define AWBL_ATA_CMD_DEV_DIAGNOSTIC            (0x90u)  /**< execute device diagnostic      */
#define AWBL_ATA_CMD_IDENTIFY                  (0xECu)  /**< Identify ATA Device            */
#define AWBL_ATA_CMD_MEDIA_CARD_TYPE           (0xD1u)  /**< check media card type          */
#define AWBL_ATA_CMD_MEDIA_STATUS              (0xDAu)  /**< Removable Media Status         */
#define AWBL_ATA_CMD_MEDIA_EJECT               (0xEDu)  /**< Eject the Media in the device  */
#define AWBL_ATA_CMD_MEDIA_LOCK                (0xDEu)  /**< Lock the Media in the device   */
#define AWBL_ATA_CMD_MEDIA_UNLOCK              (0xDFu)  /**< Un-Lock the Media in the device  */
#define AWBL_ATA_CMD_SET_FEATURES              (0xEFu)  /**< Set Device Features            */
#define AWBL_ATA_CMD_SET_MUL_MODE              (0xC6u)  /**< Set the device in multiple mode */
#define AWBL_ATA_CMD_READ_MAX_SECT             (0xF8u)  /**< Get the max user addressable sect */
#define AWBL_ATA_CMD_GET_MEDSTAT               (0xDAu)  /**< Get the Medis Status */

/* ATA Power Save command Defines */
#define AWBL_ATA_CMD_PWR_SLEEP                 (0xE6u)  /**< Set the device to Sleep mode  */
#define AWBL_ATA_CMD_PWR_STDBY                 (0xE2u)  /**< Set the device to Standby mode  */
#define AWBL_ATA_CMD_PWR_IDLE                  (0xE3u)  /**< Set the device to Idle mode  */
#define AWBL_ATA_CMD_PWR_CHECK                 (0xE5u)  /**< Get the device power  */

/* ATAPI device specific ATA Command Defines */
#define AWBL_ATA_CMD_ATAPI_IDENTIFY            (0xA1u)  /**< Identify a ATAPI Device        */
#define AWBL_ATA_CMD_ATAPI_RESET               (0x08u)  /**< Reset a ATAPI device           */
#define AWBL_ATA_CMD_ATAPI_PACKET              (0xA0u)  /**< ATAPI Command init command     */

/* SET FEATURES register definitions */
typedef uint8_t awbl_ata_fis_feature_t; /* 该功能在cmd_type为AWBL_ATA_CMD_SET_FEATURES 下才有效 其他为0 */

#define AWBL_ATA_FIS_FEATURE_NONE               0x00    /* none */
#define AWBL_ATA_FIS_FEATURE_ENABLE_8BIT        0x01    /* enable 8bit data transfer    */
#define AWBL_ATA_FIS_FEATURE_ENABLE_WCACHE      0x02    /* enable write cache           */
#define AWBL_ATA_FIS_FEATURE_SET_RWMODE         0x03    /* set transfer mode            */
#define AWBL_ATA_FIS_FEATURE_ENABLE_APM         0x05    /* en advanced power management */
#define AWBL_ATA_FIS_FEATURE_DISABLE_RETRY      0x33    /* disable retry                */
#define AWBL_ATA_FIS_FEATURE_SET_LENGTH         0x44    /* length vendor specific bytes */
#define AWBL_ATA_FIS_FEATURE_SET_CACHE          0x54    /* set cache segments           */
#define AWBL_ATA_FIS_FEATURE_DISABLE_LOOK       0x55    /* dis read look-ahead feature  */
#define AWBL_ATA_FIS_FEATURE_DISABLE_REVE       0x66    /* dis reverting to power on def*/
#define AWBL_ATA_FIS_FEATURE_DISABLE_ECC        0x77    /* disable ECC                  */
#define AWBL_ATA_FIS_FEATURE_DISABLE_8BIT       0x81    /* disable 8bit data transfer   */
#define AWBL_ATA_FIS_FEATURE_DISABLE_WCACHE     0x82    /* disable write cache          */
#define AWBL_ATA_FIS_FEATURE_DISABLE_APM        0x85    /* dis advanced power management*/
#define AWBL_ATA_FIS_FEATURE_ENABLE_ECC         0x88    /* enable ECC                   */
#define AWBL_ATA_FIS_FEATURE_ENABLE_RETRY       0x99    /* enable retries               */
#define AWBL_ATA_FIS_FEATURE_ENABLE_LOOK        0xAA    /* en read look-ahead feature   */
#define AWBL_ATA_FIS_FEATURE_SET_PREFETCH       0xAB    /* set maximum prefetch         */
#define AWBL_ATA_FIS_FEATURE_SET_4BYTES         0xBB    /* 4 bytes vendor specific bytes*/
#define AWBL_ATA_FIS_FEATURE_ENABLE_REVE        0xCC    /* en reverting to power on def */

/* Infromation structure (FIS) status */
typedef uint8_t awbl_ata_fis_status_t; /* 其他位无定义 */

#define AWBL_ATA_FIS_STATUS_BUSY                (1 << 7)     /* BSY status bit */
#define AWBL_ATA_FIS_STATUS_DRDY                (1 << 6)     /* device ready */
#define AWBL_ATA_FIS_STATUS_DF                  (1 << 5)     /* device fault */
#define AWBL_ATA_FIS_STATUS_DRQ                 (1 << 3)     /* data request i/o */
#define AWBL_ATA_FIS_STATUS_ERR                 (1 << 0)     /* have an error */

/* Infromation structure (FIS) device */
typedef uint8_t awbl_ata_fis_device_t; /* 第7bit 5bit 必须为1 */

#define AWBL_ATA_FIS_DEVICE_LBA                 (1 << 6)     /* 选择寻址方式 改为为1代表LBA寻址 为0代表CHS寻址  */
#define AWBL_ATA_FIS_DEVICE_DEV1                (1 << 4)     /* 为1代表从机 为0代表主机 */
#define AWBL_ATA_FIS_DEVICE_ADDR                (0XF << 0)   /* LBA模式下代表高位地址 CHS模式下代表磁头号 */


/* Infromation structure (FIS) types */
typedef uint8_t awbl_ata_fis_type_t;

#define AWBL_ATA_FIS_TYPE_H2D                0x27    /* Host to Device FIS */
#define AWBL_ATA_FIS_TYPE_D2H                0x34    /* Device to Host FIS */
#define AWBL_ATA_FIS_TYPE_DMA_ACTIVE         0x39    /* DMA Activate FIS */
#define AWBL_ATA_FIS_TYPE_DMA_SETUP          0x41    /* DMA setup FIS */
#define AWBL_ATA_FIS_TYPE_DATA               0x46    /* DATA FIS */
#define AWBL_ATA_FIS_TYPE_BIST               0x58    /* BIST FIS */
#define AWBL_ATA_FIS_TYPE_PIO_SETUP          0x5F    /* PIO Setup FIS */
#define AWBL_ATA_FIS_TYPE_SETDEVBITS         0xA1    /* SetDevice bits FIS */

/* bit definitions of IDENTIFY DEVICE capabilities */
typedef uint8_t awbl_ata_identify_device_cap_t;

#define AWBL_ATA_IDENTIFY_DEVICE_CAP_LBA     (1 << 9) /* LBA spupported */
#define AWBL_ATA_IDENTIFY_DEVICE_CAP_DMA     (1 << 8) /* DMA spupported */

/* bit definitions of IDENTIFY DEVICE command set */
typedef uint8_t awbl_ata_identify_device_cmd_set_t;

#define AWBL_ATA_IDENTIFY_DEVICE_CMD_SET_LBA48        (1 << 10) /* LBA48 spupported */
#define AWBL_ATA_IDENTIFY_DEVICE_CMD_SET_NCQ          (1 << 2 ) /* READ/WRITE DMA QUEUED command supported */

/* bit definitions of IDENTIFY DEVICE capabilities */
typedef uint8_t awbl_ata_identify_device_sector_size_t;

#define AWBL_ATA_IDENTIFY_DEVICE_SECTOR_SIZE_LSPPS    (0X0F) /*  logical sectors per physical sector */

typedef uint8_t awbl_ata_err_code_t;
/* 00h              *//* No error detected / no additional information */
/* 01h              *//* Self-test passed */
/* 03h              *//* Write / Erase failed */
/* 05h              *//* Self-test or diagnostic failed */
/* 09h              *//* Miscellaneous error */
/* 0Bh              *//* Vendor specific */
/* 0Ch              *//* Corrupted media format */
/* 0D-0Fh           *//* Vendor specific */
/* 10h              *//* ID Not Found / ID Error */
/* 11h              *//* Uncorrectable ECC error */
/* 14h              *//* ID Not Found */
/* 18h              *//* Corrected ECC error */
/* 1Dh, 1Eh         *//* Vendor specific */
/* 1Fh              *//* Data transfer error / command aborted */
/* 20h              *//* Invalid command */
/* 21h              *//* Invalid address */
/* 22-23h           *//* Vendor specific */
/* 27h              *//* Write protect violation */
/* 2Fh              *//* Address overflow (address too large) */
/* 30-34h           *//* Self-test or diagnostic failed */
/* 35h, 36h         *//* Supply or generated voltage out of tolerance */
/* 37h, 3Eh         *//* Self-test or diagnostic failed */
/* 38h              *//* Corrupted media format */
/* 39h              *//* Vendor specific */
/* 3Ah              *//* Spare sectors exhausted */
/* 3Bh 3Ch, 3Fh     *//* Corrupted media format */
/* 3Dh              *//* Vendor specific */
/* All other values *//* Reserved */

/*
    存取控制块

  CHS (Cylinder/Head/Sector)
    一共 24 个 bit 位, 其中前 10 位表示 cylinder, 中间 8 位表示 head, 后面 6 位表示 sector
    柱面 : 0 到 Cylinders - 1
    磁头 : 0 到 Heads - 1
    扇区 : 1 到 Sectors per track (注意是从 1 开始)
    磁盘最大容量为: (1024 * 256 * 63 * 512) / 1048576 = 8064 MB (1 M = 1048576 Bytes)

  LBA (Logical Block Addressing)
    LBA 是一个整数, 通过转换成 CHS 格式完成磁盘具体寻址, ATA1:28个bit 寻址128G ATA2:48 个 bit 位寻址, 最大寻址 128 PB

  NS为每磁道的扇区数  NH为每柱面的磁头数 C柱面编号 H磁头编号 S逻辑扇区编号
  CHS -> LBA
    LBA = NH * NS * C + NS * H + S - 1
  LBA -> CHS
    C = (LBA / NS) / NH
    H = (LBA / NS) % NH
    S = (LBA % NS) + 1
*/
/* IDENTIFY DEVICE information Data structure defined based on ATAPI7 specification(T13/1532D) */
typedef struct awbl_ata_identify_data {

    uint16_t general_conf;           /* 00      : general configuration */
    uint16_t num_cylinders;          /* 01      : number of cylinders (default CHS trans) */
    uint16_t specific_conf;          /* 02      : specific configuration */
    uint16_t num_heads;              /* 03      : number of heads (default CHS trans) */
    uint16_t num_ub_per_track;       /* 04      : number of unformatted bytes per track */
    uint16_t num_ub_per_sector;      /* 05      : number of unformatted bytes per sector */
    uint16_t num_sectors;            /* 06      : number of sectors per track (default CHS trans) */
    uint16_t rsv5[2];                /* 07-08   : number of sectors per card */
    uint16_t rsv6;                   /* 09      : reserved */
    uint16_t serial[10];             /* 10-19   : serial number (string) */
    uint16_t rsv7;                   /* 20      : buffer type (dual ported) */
    uint16_t rsv8;                   /* 21      : buffer size in 512 increments */
    uint16_t rsv9;                   /* 22      : number of ECC bytes passed on R/W Long cmds */
    uint16_t fw_rev[4];              /* 23-26   : firmware revision (string) */
    uint16_t model_num[20];          /* 27-46   : model number (string) */
    uint16_t rw_mult_support;        /* 47      : max number of sectors on R/W multiple cmds */
    uint16_t rsv10;                  /* 48      : reserved */
    uint16_t capabilities[2];        /* 49-50   : LBA, DMA, IORDY support indicator */
    uint16_t rsv11;                  /* 51      : PIO data transfer cycle timing mode */
    uint16_t rsv12;                  /* 52      : single word DMA data transfer cycle timing mode */
    uint16_t cur_field_validity;     /* 53      : words 54-58 validity (0 == not valid) */
    uint16_t rsv13;                  /* 54      : number of current cylinders */
    uint16_t rsv14;                  /* 55      : number of current heads */
    uint16_t rsv15;                  /* 56      : number of current sectors per track */
    uint16_t rsv16[2];               /* 57-58   : current capacity in sectors */
    uint16_t mult_sectors;           /* 59      : multiple sector setting */
    uint16_t lba_total_sectors[2];   /* 60-61   : total sectors in LBA mode */
    uint16_t rsv17;                  /* 62      : single word DMA support */
    uint16_t mw_dma;                 /* 63      : multi word DMA support */
    uint16_t apio_modes;             /* 64      : advanced PIO transfer mode supported */
    uint16_t min_dma_timing;         /* 65      : minimum multiword DMA transfer cycle */
    uint16_t rec_dma_timing;         /* 66      : recommended multiword DMA cycle */
    uint16_t min_pio_timing;         /* 67      : min PIO transfer time without flow control */
    uint16_t min_pio_iordy_timing;   /* 68      : min PIO transfer time with IORDY flow control */
    uint16_t rsv18[6];               /* 69-74   : reserved */
    uint16_t queue_depth;            /* 75      : queue depth */
    uint16_t rsv19[4];               /* 76-79   : reserved for SATA */
    uint16_t major_ver;              /* 80      : major version number */
    uint16_t minor_ver;              /* 81      : minor version number */
    uint16_t cmd_set_supp[3];        /* 82-84   : command set supported */
    uint16_t cmd_set_enabled[3];     /* 85-87   : command set/feature enabled */
    uint16_t ultra_dma_mode;         /* 88      : ultra dma modes */
    uint16_t sec_ers_unit_time;      /* 89      : time required for security erase unit completion */
    uint16_t enhance_sec_ers_time;   /* 90      : time required for enhanced security erase completion */
    uint16_t current_pm_val;         /* 91      : current advanced power management value */
    uint16_t master_pwd_rev;         /* 92      : master password revision code */
    uint16_t hw_conf_tst_result;     /* 93      : hardware configuration test result */
    uint16_t acoustic_mng_val;       /* 94      : automatic acoustic management value */
    uint16_t stream_min_req_sz;      /* 95      : stream minimum request size */
    uint16_t stream_trans_time_dma;  /* 96      : streaming transfer time - dma */
    uint16_t stream_access_latency;  /* 97      : streaming access latency - dma and pio */
    uint16_t stream_perf_gran[2];    /* 98-99   : streaming performance granularity */
    uint16_t max_48b_lba_addr[4];    /* 100-103 : maximum user lba for 48b address feature set */
    uint16_t stream_trans_time_pio;  /* 104     : streaming transfer time - pio */
    uint16_t rsv20;                  /* 105     : reserved */
    uint16_t sector_size;            /* 106     : physical sector size/logical sector size */
    uint16_t inter_seek_delay_us;    /* 107     : inter-seek delay for ISO-7799 acoustic testing in ms */
    uint16_t world_wide_name[4];     /* 108-111 : world wide name */
    uint16_t rsv21[4];               /* 112-115 : reserved for world wide name extension to 128bits */
    uint16_t rsv22;                  /* 116     : reserved for technical report */
    uint16_t sector_sz_in_word[2];   /* 117-118 : words per logical sector */
    uint16_t rsv23[8];               /* 119-126 : reserved */
    uint16_t rem_stat_notify_supp;   /* 127     : removable mdedia status notification feature set support */
    uint16_t security_status;        /* 128     : security status */
    uint16_t vendor_specific[31];    /* 129-159 : vendor specific */
    uint16_t cfa_pwr_mode_1;         /* 160     : CFA power mode 1 */
    uint16_t rsv24[15];              /* 161-175 : reserved for assignment by the CF association */
    uint16_t sn[30];                 /* 176-205 : current media serial number */
    uint16_t rsv25[49];              /* 206-254 : reserved */
    uint16_t integrity;              /* 255     : 15-8 -> checksum; 7-0 -> signature; */

} awbl_ata_identify_data_t;

/**
 * \brief ATA/ATAPI Device Command Completion Status Definitions
 *
 * This defines the structure for Collection of ATA/ATAPI device Command
 * completion status.
 */
typedef struct awbl_ata_dev_stat {

    uint8_t  error;          /**< Error                */
    uint8_t  int_reason;     /**< Bus Release,Cmd/Data */
    uint8_t  lba_low;        /**< LBA Low              */
    uint8_t  lba_mid;        /**< LBA Mid              */
    uint8_t  lba_high;       /**< LBA High             */
    uint8_t  device;         /**< Device head          */
    uint8_t  stat;           /**< Completion status    */
    uint32_t err_byte;       /**< Number of Bytes tranferred */

} awbl_ata_dev_stat_t;

/* 电源控制类型 */
typedef uint8_t awbl_ata_pwr_type_t;
#define AWBL_ATA_PWR_TYPE_IDLE      0
#define AWBL_ATA_PWR_TYPE_STANDBY   1
#define AWBL_ATA_PWR_TYPE_SLEEP     2

/* Automatic Standby timer periods */
typedef uint8_t awbl_ata_pwr_time_t;
/*
 * 0 (00h)           :  Timeout disabled
 * 1-240 (01h-F0h)   : (value * 5) seconds
 * 241-251 (F1h-FBh) : ((value - 240) * 30) minutes
 * 252 (FCh)         :  21 minutes
 * 253 (FDh)         :  Period between 8 hours and 12 hours
 * 254 (Feh)         :  Reserved
 * 255 (FFh)         :  21 min 15 seconds
 * NOTE: Times are approximate.
*/

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_ATA_H */
