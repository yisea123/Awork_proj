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
 * \brief AWBus SATA bus type implementation (lite)
 *
 * \internal
 * \par modification history:
 * - 1.00 17-06-07  anu, first implementation
 * \endinternal
 */

#ifndef __AWBL_SATABUS_H
#define __AWBL_SATABUS_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "awbus_lite.h"
#include "aw_delayed_work.h"
#include "aw_sem.h"

struct awbl_satabus_host;

typedef uint32_t awbl_satabus_cmd_req_flag_t;
#define AWBL_SATABUS_CMD_REQ_FLAG_ATAPI          (0X0001) /* 该命令为ATAPI 命令包 */
#define AWBL_SATABUS_CMD_REQ_FLAG_LBA            (0X0002) /* 该设备支持LBA寻址 */
#define AWBL_SATABUS_CMD_REQ_FLAG_LBA48          (0X0004) /* 该设备支持LBA48寻址 */
#define AWBL_SATABUS_CMD_REQ_FLAG_NCQ            (0X0008) /* 该设备支持NCQ */
#define AWBL_SATABUS_CMD_REQ_FLAG_WRITE          (0X0010) /* 命令为写操作 */

#define AWBL_SATABUS_ATAPI_CMD_LEN        16    /* atapi 的命令长度 */

/* sata bus stat */
typedef uint8_t awbl_satabus_host_stat_t;
#define AWBL_SATABUS_HOST_STAT_NONE      (0X00) /* 无 */
#define AWBL_SATABUS_HOST_STAT_ERR       (0X01) /* 错误操作 */
#define AWBL_SATABUS_HOST_STAT_PLUG      (0X02) /* 插拔操作 */
#define AWBL_SATABUS_HOST_STAT_REQC      (0X03) /* 请求取消操作 */
#define AWBL_SATABUS_HOST_STAT_PRESET    (0X04) /* 端口复位操作 */
#define AWBL_SATABUS_HOST_STAT_PSTOP     (0X05) /* 端口停止操作 */

typedef enum awbl_satabus_dev_type {

    AWBL_SATABUS_DEV_TYPE_DISK = 0, /* 设备类型大存储容量类型 */
    AWBL_SATABUS_DEV_TYPE_CDROM   , /* 光驱类型 */
    AWBL_SATABUS_DEV_TYPE_ILLEGAL , /* 设备类型无效类型 */

} awbl_satabus_dev_type_t;

#define AWBL_SATABUS_DEV_MAX_NUM          32 /* 最大的设备数目 一端口一设备 AHCI最大32端口 */

/* 端口连接状态 */
typedef struct awbl_satabus_host_port_link_stat {

    bool_t is_change;        /* 是否发生过变化 */

    bool_t is_online;        /* 是否在线 */

} awbl_satabus_host_port_link_stat_t;

/* 主机控制器具备的功能信息 */
typedef struct awbl_satabus_host_cap_info {

    uint32_t port_max_num;   /* 最大的端口数量  */

} awbl_satabus_host_cap_info_t;

/* 命令请求执行后设备状态  */
typedef struct awbl_satabus_dev_stat {

    awbl_satabus_host_stat_t host_stat; /**< 主机状态 */

    uint8_t  status;         /**< Completion status    */
    uint8_t  error;          /**< Error type 若上层是ATA/ATAPI命令集 具体错误可以参考 awbl_ata_err_code_t  */
    uint8_t  device;         /**< Device head          */
    uint16_t sector_cnt;     /**< Sector count         */

    union {
        uint64_t dw;
        struct {
            uint8_t  low;        /**< LBA Low              */
            uint8_t  mid;        /**< LBA Mid              */
            uint8_t  high;       /**< LBA High             */
            uint8_t  low_exp;    /**< LBA Low_exp          */
            uint8_t  mid_exp;    /**< LBA Mid_exp          */
            uint8_t  high_exp;   /**< LBA High_exp         */
        } byte;
    } lba;

} awbl_satabus_dev_stat_t;

/* SATABUS 的命令请求 */
typedef struct awbl_satabus_cmd_req {

    struct awbl_satabus_cmd_req *p_next;     /**< \brief the next segment or NULL */

    union {
        struct awbl_sata_cmd_ata {
            uint8_t  cmd_type;   /* 若上层是ATA/ATAPI命令集，可参考 awbl_ata_cmd_type_t */
            uint8_t  features;   /* 若上层是ATA/ATAPI命令集，可参考 awbl_ata_fis_feature_t */
            uint16_t sector_cnt; /* 扇区的个数 */
            union {
                /* 计算方法可以参考 awbl_ata_identify_data_t 有描述如何进行计算 */
                uint64_t lba;
                struct {
                    uint16_t cylinder; /* 柱面 : 0 到 Cylinders - 1   */
                    uint16_t head;     /* 磁头 : 0 到 Heads - 1   */
                    uint16_t sector;   /* 扇区 : 1 到 Sectors per track (注意是从 1 开始) */
                } chs;
            } seek;
        } ata;

        struct awbl_sata_cmd_atapi {
            uint8_t  cmd_type;          /* 若上层是ATA/ATAPI命令集，可参考 awbl_ata_cmd_type_t */
            uint8_t  features;          /* 若上层是ATA/ATAPI命令集，可参考 awbl_ata_fis_feature_t */
            uint16_t sector_cnt;        /* 扇区的个数 */
            uint8_t  cmd_pkt[AWBL_SATABUS_ATAPI_CMD_LEN];
        } atapi;
    } cmd;

    awbl_satabus_cmd_req_flag_t flag; /* 命令请求的标志 */

    uint8_t  *p_buffer;               /**< Data Buffer                      */
    uint32_t  trans_cnt;              /**< Total Number of bytes            */

    awbl_satabus_dev_stat_t dev_stat;

    aw_err_t (*pfn_complete_cb) (
            struct awbl_satabus_cmd_req *p_req, void *p_arg); /* 请求完成后的回调函数 */

    void *p_arg; /* 请求完成后的回调函数参数，应用需要可设置 */

} awbl_satabus_cmd_req_t;

/** \brief SATA Bus host controller driver information  */
struct awbl_satabus_host_drv_funs {

    /* reset port */
    aw_err_t (*pfn_port_reset) (
            struct awbl_satabus_host *p_host, uint32_t port_num);

    /* get controller info */
    aw_err_t (*pfn_cap_info_get) (struct awbl_satabus_host     *p_host,
                                  awbl_satabus_host_cap_info_t *p_cap_info);

    /* port is connect or disconnect */
    aw_err_t (*pfn_port_link_stat_get) (
            struct awbl_satabus_host           *p_host,
            uint32_t                            port_num,
            awbl_satabus_host_port_link_stat_t *p_link_stat);

    /* command request */
    aw_err_t (*pfn_cmd_request) (
            struct awbl_satabus_host *p_host,
            uint32_t                  port_num,
            awbl_satabus_cmd_req_t   *p_req);

    /* cancle command request */
    aw_err_t (*pfn_cmd_request_cancel) (
            struct awbl_satabus_host *p_host,
            uint32_t                  port_num,
            awbl_satabus_cmd_req_t   *p_req);

};

/** \brief SATA Bus host information  */
struct awbl_satabus_host_info {

    uint8_t bus_index;     /** \brief bus ID */

};

/** \brief SATA Bus dev information  */
struct awbl_satabus_dev_info {

    struct awbl_drvinfo super;

    awbl_satabus_dev_type_t type;

};

/** \brief SATA Bus host controller  */
struct awbl_satabus_host {

    struct awbl_busctlr      bus_ctrl;

    struct awbl_satabus_dev *p_dev[AWBL_SATABUS_DEV_MAX_NUM];/** \brief memory for device */

    struct aw_delayed_work   dwork_detect;  /** \brief period works for slot */

    struct awbl_satabus_host_info *p_info;

    struct awbl_satabus_host_drv_funs *p_drvfuns;

    uint32_t dev_created;                   /** \brief 每位代表某个端口的设备创建情况 1为已经创建  */

    awbl_satabus_host_cap_info_t cap_info;  /** \brief 主机控制器具备的功能信息 */

};

/** \brief SATA Bus device  */
struct awbl_satabus_dev {

    struct awbl_dev           super;
    struct awbl_devhcf        devhcf;        /** \brief device information */
    struct awbl_satabus_host *p_host;        /** \brief sata host controller */

    AW_SEMB_DECL(opt_semb);                  /** \brief 用于同步操作的二进制信号量 */

    char name[20];                           /** \brief card name */

    uint32_t port_num;                       /** \brief 对应的端口号 */

    void *p_drv;                             /** \brief 驱动，供驱动层使用  */
};

aw_err_t awbl_satabus_cmd_request_sync (
        struct awbl_satabus_dev *p_dev, awbl_satabus_cmd_req_t *p_req);

aw_err_t awbl_satabus_cmd_request_async (
        struct awbl_satabus_dev *p_dev,
        awbl_satabus_cmd_req_t  *p_req);

aw_err_t awbl_satabus_cmd_request_cancel (
        struct awbl_satabus_dev *p_dev,
        awbl_satabus_cmd_req_t  *p_req);

aw_err_t awbl_satabus_create (struct awbl_satabus_host          *p_host,
                              struct awbl_satabus_host_info     *p_info,
                              struct awbl_satabus_host_drv_funs *p_drvfuns);

void awbl_satabus_init (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_SATABUS_H */
