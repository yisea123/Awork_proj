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
 * \brief ����ͷ����(rgb565��ʽ��ͨ��frame buffer��ʾ����)
 *
 * - �������裺
 *   1. ����������aw_prj_params.hͷ�ļ���ʹ��
 *      - ��Ӧƽ̨�Ĵ��ں�
 *      - AW_COM_CONSOLE
 *      - AW_DEV_xxxx_CSI(xxxx�������Ӳ��ƽ̨����)
 *      - AW_DEV_OV7725
 *   2. �������е�DURX��DUTXͨ��USBת���ں�PC���ӣ����ڵ����������ã�
 *      ������Ϊ115200��8λ���ݳ��ȣ�1��ֹͣλ��������
 *   3. ��awbl_hwconf_ov7725.h�����ļ����޸����ظ�ʽΪ RGB565;
 *
 * - ʵ������
 *   1. ���ڴ�ӡ������Ϣ��
 *   2. ��ʾ������ʾ����ͷ���㵽�Ļ��档
 *
 * - ��ע��
 *   1. ��������ڳ�ʼ��ʱ�������������ļ� awbl_hwconf_ov7725.h �� awbl_hwconf_xxxxx_csi.h
 *   (xxxx�������Ӳ��ƽ̨����)�в鿴��demo��ʹ��GPIO�Ƿ�������Ÿ��á�
 *   2. raw��ʽ��һ����������1���ֽڱ�ʾ;
 *   3. rgb565��ʽ��һ��������2���ֽڣ�
 *   4. rgb888��ʽ��һ��������3���ֽڱ�ʾ��
 *   5. ������ͷ�ֱ���Ϊ640 x 480 ����ʾ���ֱ��ʳߴ�Ϊ480 x 272�������(��������ͷ�ֱ���  > ��ʾ���ֱ���)��
 *      ����������ʾ������ʾ��һ֡����ֻ������ͷһ֡�����һ����
 *
 * \par Դ����
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

/* ����ͷ���� */
#define __CAMERA_NAME              "ov7725"

#define __TEST_DEV_EMWIN_FB        "imx1050_emwin_fb"  /*���ݾ���ƽ̨�޸�*/

/**
 * \brief����VIDEO��PHOTO�ķֱ���
 * ֧�ֵķֱ����У� 640 X 480 ��320 X 240
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
    size_t   __g_x_res;     /* ��ʾ��x����ߴ� */
    size_t   __g_y_res;     /* ��ʾ��y����ߴ� */

    /* ������ͷ */
    fd = aw_camera_open(__CAMERA_NAME);
    if (fd == NULL) {
        aw_kprintf("camera_open error! \n\r");
    }

    /* ��������ͷ�ֱ���*/
    cfg.photo_resolution = __PHOTO_RES;
    cfg.video_resolution = __VIDEO_RES;

    ret = aw_camera_cfg(fd, &cfg);
    if(ret != AW_OK){
        aw_kprintf("aw_camera_cfg error,code:%d\r\n",ret);
        return ;
    }

    /* ��֡�����豸 */
    p_fb = aw_emwin_fb_open(__TEST_DEV_EMWIN_FB, 0);

    __g_x_res = p_fb->x_res;
    __g_y_res = p_fb->y_res;
    p_buf = (uint8_t *)aw_mem_alloc(__g_x_res * __g_y_res * 2 );
    memset(p_buf, 0, __g_x_res * __g_y_res * 2);

    /* ��ʼ��֡�����豸  */
    aw_emwin_fb_init(p_fb, (uint32_t *)p_buf, 0);

    /* �򿪱��Ⲣ������� */
    aw_emwin_fb_backlight(p_fb, 100);
    aw_emwin_fb_run(p_fb);

    while (1) {
        t1 = aw_sys_tick_get();

        /* ��ȡ����ͷ��һ֡Ԥ����ַ */
        ret = aw_camera_get_video_buf(fd, &buf);

        if (ret == AW_OK) {

            /* �ж�����ͷ�ķֱ��ʣ����㿽���ĳߴ� ,��LCD����ʾͼ��  */
            if (__VIDEO_RES == AW_RESOLUTION_SET(320, 240)) {
                for (i = 0; i < 240; i ++) {
                    memcpy((uint8_t*)p_buf + __g_x_res * 2 * i, (uint8_t*)buf + 320 * 2 * i, 320 * 2);
                }
            } else if (__VIDEO_RES == AW_RESOLUTION_SET(640, 480)) {
                for (i = 0; i < ((__g_y_res >= 480) ? 480 : __g_y_res); i ++) {
                    memcpy((uint8_t*)p_buf + __g_x_res * 2 * i, (uint8_t*)buf + 640 * 2 * i, ((__g_x_res > 640) ? 640 : __g_x_res) * 2);
                }
            }

            /* �ͷ�����ͷ��һ֡Ԥ����ַ */
            ret = aw_camera_release_video_buf(fd, buf);
            if (ret != AW_OK) {
                aw_kprintf("get relase video error!\r\n");
                continue ;
            }

        }

        sprintf(buf, "%d f/s.\n", frame_ms);
        aw_kprintf("%s\r\n",buf);

        /* ����֡�� */
        t2 = aw_sys_tick_get();
        frame_ms = 1000 / aw_ticks_to_ms(t2 - t1);
    }
    return ;
}

/**
 * /brief ����ͷ(rgb565��ʽ)������ں���
 */
void demo_camera_rgb565_entry(void)
{

    aw_kprintf("demo_camera_rgb565 test...\n");

    AW_TASK_DECL_STATIC(__camera_rgb565_lcd_show, 1024 * 20 );

    /* ��ʼ������LCD��ʾ���� */
    AW_TASK_INIT(__camera_rgb565_lcd_show,                /* ����ʵ�� */
               "__camera_lcd_show",                /* �������� */
               3,                                  /* �������ȼ� */
               1024 * 20 ,                         /* �����ջ��С */
               __test_camera_rgb565_task,             /* ������ں��� */
               (void *)NULL);                      /* ������ڲ��� */

    /* ��������__camera_lcd_show */
    AW_TASK_STARTUP(__camera_rgb565_lcd_show);

}
/** [src_camera_rgb565] */

/* end of file */
