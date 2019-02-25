/*******************************************************************************
*                                  AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn
* e-mail:      support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief 摄像头例程(rgb565格式，通过frame buffer显示画面)
 *
 * - 操作步骤：
 *   1. 本例程需在aw_prj_params.h头文件里使能
 *      - 对应平台的串口宏
 *      - AW_COM_CONSOLE
 *      - AW_DEV_xxxx_CSI(xxxx代表具体硬件平台名称)
 *      - AW_DEV_OV7725
 *   2. 将板子中的DURX、DUTX通过USB转串口和PC连接，串口调试助手设置：
 *      波特率为115200，8位数据长度，1个停止位，无流控
 *   3. 在awbl_hwconf_ov7725.h配置文件中修改像素格式为 RGB565;
 *
 * - 实验现象：
 *   1. 串口打印调试信息。
 *   2. 显示屏上显示摄像头拍摄到的画面。
 *
 * - 备注：
 *   1. 如果工程在初始化时出错，请在配置文件 awbl_hwconf_ov7725.h 和 awbl_hwconf_xxxxx_csi.h
 *   (xxxx代表具体硬件平台名称)中查看此demo所使用GPIO是否存在引脚复用。
 *   2. raw格式，一个像素是用1个字节表示;
 *   3. rgb565格式，一个像素是2个字节；
 *   4. rgb888格式，一个像素是3个字节表示；
 *   5. 在摄像头分辨率为640 x 480 、显示屏分辨率尺寸为480 x 272的情况下(即：摄像头分辨率  > 显示屏分辨率)，
 *      该例程在显示屏上显示的一帧画面只是摄像头一帧画面的一部分
 *
 * \par 源代码
 * \snippet demo_camera_rgb565.c src_camera_rgb565
 *
 * \internal
 * \par Modification History
 * - 1.01 18-07-25 lqy, modification.
 * - 1.00 18-07-24 sls, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_camera_rgb565
 * \copydoc demo_camera_rgb565.c
 */

/** [src_camera_rgb565] */

#include "Aworks.h"
#include "aw_vdebug.h"
#include "aw_camera.h"
#include "GUI.h"
#include "aw_system.h"
#include "aw_types.h"
#include <stdio.h>
#include "aw_task.h"
#include "aw_emwin_fb.h"
#include <string.h>
#include "aw_mem.h"

/* 摄像头名称 */
#define __CAMERA_NAME              "ov7725"

#define __TEST_DEV_EMWIN_FB        "imx1050_emwin_fb"  /*根据具体平台修改*/

/**
 * \brief设置VIDEO和PHOTO的分辨率
 * 支持的分辨率有： 640 X 480 、320 X 240
 */
#define __VIDEO_RES                 AW_RESOLUTION_SET(640, 480)
#define __PHOTO_RES                 AW_RESOLUTION_SET(640, 480)

void __test_camera_rgb565_task (void) {

    aw_err_t ret = 0;
    struct aw_camera_cfg cfg;
    void *fd = NULL;
    aw_tick_t      t1,t2;
    void * buf = NULL;
    aw_emwin_fb_info_t *p_fb;
    int frame_ms = 0;
    int i = 0;
    uint8_t *p_buf;
    size_t   __g_x_res;     /* 显示屏x方向尺寸 */
    size_t   __g_y_res;     /* 显示屏y方向尺寸 */

    /* 打开摄像头 */
    fd = aw_camera_open(__CAMERA_NAME);
    if (fd == NULL) {
        aw_kprintf("camera_open error! \n\r");
    }

    /* 配置摄像头分辨率*/
    cfg.photo_resolution = __PHOTO_RES;
    cfg.video_resolution = __VIDEO_RES;

    ret = aw_camera_cfg(fd, &cfg);
    if(ret != AW_OK){
        aw_kprintf("aw_camera_cfg error,code:%d\r\n",ret);
        return ;
    }

    /* 打开帧缓冲设备 */
    p_fb = aw_emwin_fb_open(__TEST_DEV_EMWIN_FB, 0);

    __g_x_res = p_fb->x_res;
    __g_y_res = p_fb->y_res;
    p_buf = (uint8_t *)aw_mem_alloc(__g_x_res * __g_y_res * 2 );
    memset(p_buf, 0, __g_x_res * __g_y_res * 2);

    /* 初始化帧缓冲设备  */
    aw_emwin_fb_init(p_fb, (uint32_t *)p_buf, 0);

    /* 打开背光并运行面板 */
    aw_emwin_fb_backlight(p_fb, 100);
    aw_emwin_fb_run(p_fb);

    while (1) {
        t1 = aw_sys_tick_get();

        /* 获取摄像头的一帧预览地址 */
        ret = aw_camera_get_video_buf(fd, &buf);

        if (ret == AW_OK) {

            /* 判断摄像头的分辨率，计算拷贝的尺寸 ,在LCD上显示图像  */
            if (__VIDEO_RES == AW_RESOLUTION_SET(320, 240)) {
                for (i = 0; i < 240; i ++) {
                    memcpy((uint8_t*)p_buf + __g_x_res * 2 * i, (uint8_t*)buf + 320 * 2 * i, 320 * 2);
                }
            } else if (__VIDEO_RES == AW_RESOLUTION_SET(640, 480)) {
                for (i = 0; i < ((__g_y_res >= 480) ? 480 : __g_y_res); i ++) {
                    memcpy((uint8_t*)p_buf + __g_x_res * 2 * i, (uint8_t*)buf + 640 * 2 * i, ((__g_x_res > 640) ? 640 : __g_x_res) * 2);
                }
            }

            /* 释放摄像头的一帧预览地址 */
            ret = aw_camera_release_video_buf(fd, buf);
            if (ret != AW_OK) {
                aw_kprintf("get relase video error!\r\n");
                continue ;
            }

        }

        sprintf(buf, "%d f/s.\n", frame_ms);
        aw_kprintf("%s\r\n",buf);

        /* 计算帧率 */
        t2 = aw_sys_tick_get();
        frame_ms = 1000 / aw_ticks_to_ms(t2 - t1);
    }
    return ;
}

/**
 * /brief 摄像头(rgb565格式)例程入口函数
 */
void demo_camera_rgb565_entry(void)
{

    aw_kprintf("demo_camera_rgb565 test...\n");

    AW_TASK_DECL_STATIC(__camera_rgb565_lcd_show, 1024 * 20 );

    /* 初始化任务LCD显示任务 */
    AW_TASK_INIT(__camera_rgb565_lcd_show,                /* 任务实体 */
               "__camera_lcd_show",                /* 任务名字 */
               3,                                  /* 任务优先级 */
               1024 * 20 ,                         /* 任务堆栈大小 */
               __test_camera_rgb565_task,             /* 任务入口函数 */
               (void *)NULL);                      /* 任务入口参数 */

    /* 启动任务__camera_lcd_show */
    AW_TASK_STARTUP(__camera_rgb565_lcd_show);

}
/** [src_camera_rgb565] */

/* end of file */
