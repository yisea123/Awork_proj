/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2013 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief 触摸屏校准数据存储及分析
 *
 * \internal
 * \par modification history
 * - 1.00 18-03-22  nwt, first implementation.
 * \endinternal
 */
#include "aworks.h"
#include "aw_ts.h"
#include "aw_nvram.h"
#include "fs/aw_mount.h"
#include "io/aw_fcntl.h"
#include "io/aw_unistd.h"
#include "string.h"

#define __MOUNT_NAME "/mnt"
#define __FILE_NAME  __MOUNT_NAME"/cal_data"
#define __FS_EN      0

#ifdef AW_DEV_HW800480F
aw_local const char *__g_ts_dev = "TS800X480";
#else
aw_local const char *__g_ts_dev = "TS480X272";
#endif


#if __FS_EN
aw_local void __fs_init (void)
{
    aw_err_t                ret;
    int                     retry = 3;
    struct aw_fs_format_arg arg = {"nand", 4096, 0};
    static bool_t           init = FALSE;

    if (init) {
        return;
    }

    do {
        ret = aw_mount("/mnt", "/dev/mtd", "lffs", 0);
        if (ret != AW_OK) {
            ret = aw_make_fs("/dev/mtd", "lffs", &arg);
            if (ret != AW_OK) {
                return;
            }
        }
    } while ((ret != AW_OK) && retry--);

    if (ret == AW_OK) {
        init = TRUE;
    }
}
#endif



int ts_calc_data_read (void *p_cacl_info, int len)
{
    int  ret = AW_OK, flag_len;
    char buf[24];

#if __FS_EN
    int fd = -1;
#endif

    flag_len = strlen(__g_ts_dev);

#if __FS_EN
    __fs_init();
    fd = aw_open(__FILE_NAME, O_RDONLY, 7777);
    if (fd >= 0) {
        ret = aw_read(fd, buf, flag_len);
        if (ret == len) {
            if (strncmp(buf, __g_ts_dev, flag_len) == 0) {
                ret = aw_read(fd, p_cacl_info, len);
                if (ret != len) {
                    ret = -AW_EIO;
                } else {
                    ret = AW_OK;
                }
            } else {
                ret = -AW_EBADF;
            }
        } else {
            ret = -AW_EIO;
        }
    }

    if (fd >= 0) {
        aw_close(fd);
    }
#else
    ret = aw_nvram_get("calc_data", 0, buf, 0, flag_len);
    if (strncmp(buf, __g_ts_dev, flag_len)) {
        return -AW_EINVAL;
    }
    ret = aw_nvram_get("calc_data", 0, (char *)p_cacl_info, flag_len, len);
#endif

    return ret;
}


int ts_calc_data_write (void *p_cacl_info, int len)
{
    int ret = AW_OK, flag_len;

#if __FS_EN
    int fd = -1;
#endif

    flag_len = strlen(__g_ts_dev);

#if __FS_EN
    __fs_init();
    fd = aw_open(__FILE_NAME, O_RDWR | O_CREAT | O_TRUNC, 7777);
    if (fd >= 0) {
        ret = aw_write(fd, __g_ts_dev, flag_len);
        if (ret == len) {
            ret = aw_write(fd, p_cacl_info, len);
            if (ret != len) {
                ret = -AW_EIO;
            } else {
                ret = AW_OK;
            }
        } else {
            ret = -AW_EIO;
        }
    }

    if (fd >= 0) {
        aw_close(fd);
    }
#else
    ret = aw_nvram_set("calc_data", 0, (char *)__g_ts_dev, 0, flag_len);
    if (ret != AW_OK) {
        return ret;
    }

    ret = aw_nvram_set("calc_data", 0, (char *)p_cacl_info, flag_len, len);
#endif

    return ret;
}


