/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief frame buffer����
 *
 * - �������裺
 *   1. ��Ҫ��aw_prj_params.hͷ�ļ���ʹ��
 *      - AW_COM_CONSOLE
 *      - ��Ӧƽ̨�Ĵ��ں�
 *      - ʹ�õ���ʾ���ĺ�
 *
 * - ʵ������
 *   1. �Ƚ�����ĻУ׼��
 *   2. ��Ļ�м����������ʾ�������������7�����ƣ�
 *   3. �����Ļ�м���ʾһ����ɫ�ĺ��ߣ��ұ���ʾһ����ɫ�����ߣ�
 *   4. ��Ļ���Ͻ���ʾ��AWorks��;
 *   5. ������Ļ������Ļ�ϻ��㡣
 *
 * \par Դ����
 * \snippet demo_lcd.c src_lcd
 *
 * \internal
 * \par Modification history
 * - 1.00 18-07-16  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_lcd
 * \copydoc demo_lcd.c
 */

/** [src_lcd] */
#include "aworks.h"
#include "GUI/GUI.h"
#include "aw_ts.h"
#include "aw_emwin_fb.h"
#include <string.h>
#include "aw_mem.h"
#include "aw_vdebug.h"
#include "aw_delay.h"

/* ��ģ */
static uint8_t __g_my_words[] =
{0x00,0x00,0x00,0x18,0x3C,0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0x00,0x00,0x00,0x00, //A
0x00,0x00,0x00,0x63,0x63,0x63,0x6B,0x6B,0x6B,0x36,0x36,0x36,0x00,0x00,0x00,0x00,  //W
0x00,0x00,0x00,0x00,0x00,0x3C,0x66,0x66,0x66,0x66,0x66,0x3C,0x00,0x00,0x00,0x00,  //o
0x00,0x00,0x00,0x00,0x00,0x66,0x6E,0x70,0x60,0x60,0x60,0x60,0x00,0x00,0x00,0x00,  //r
0x00,0x00,0x00,0x60,0x60,0x66,0x66,0x6C,0x78,0x6C,0x66,0x66,0x00,0x00,0x00,0x00,  //k
0x00,0x00,0x00,0x00,0x00,0x3E,0x60,0x60,0x3C,0x06,0x06,0x7C,0x00,0x00,0x00,0x00}; //s

static uint16_t __g_pen_color; /* ������ɫ */
static size_t   __g_x_res;     /* x����ߴ� */
static size_t   __g_y_res;     /* y����ߴ� */
static uint16_t *__gp_frame_buffer;  /* frame buffer��ַ */

/* ���û�����ɫ */
static void __set_pen_color (uint8_t r, uint8_t g, uint8_t b)
{
    __g_pen_color = (r << 11) | (g << 6) | b;
}

/**
 * \brief ����һ����
 */
static void __draw_point (int x, int y)
{
    __gp_frame_buffer[y * __g_x_res + x] = __g_pen_color;
}

/* ������������ */
static void swap(int *p1, int *p2)
{
    int t;

    t = *p1;
    *p1 = *p2;
    *p2 = t;
}

/**
 * \brief ����һ������
 */
static void __draw_v_line (int x, int y1, int y2)
{
    int i;
    if (y1 > y2) {
        swap(&y1, &y2);
    }
    for (i = y1; i <= y2; i++) {
        __gp_frame_buffer[i * __g_x_res + x] = __g_pen_color;
    }
}

/**
 * \brief ����һ������
 */
static void __draw_h_line (int x1, int x2, int y)
{
    int i;
    if (x1 > x2) {
        swap(&x1, &x2);
    }
    for (i = x1; i <= x2; i++) {
        __gp_frame_buffer[y * __g_x_res + i] = __g_pen_color;
    }
}

/**
 * \brief ����һ������
 */
static void __draw_rect (int x1, int x2, int y1, int y2)
{
    int i;

    if (x1 > x2) {
        swap(&x1, &x2);
    }
    if (y1 > y2) {
        swap(&y1, &y2);
    }

    for (i = y1; i <= y2; i++) {
        __draw_h_line(x1, x2, i);
    }
}

/* �������� */
static void __draw_words(int x, int y, uint8_t *p_words, int words_len)
{
    int i, j, k;
    for (i = 0; i < words_len / 16; i++) {
        for (j = 0; j < 16; j++) {
            for (k = 7; k >= 0; k--) {
                if ((p_words[i * 16 + j] >> k) & 1) {
                    __draw_point(x + (8 * i) + (7 - k), y + j);
                }
            }
        }
    }
}

/* ���ƹ�꣨���׹�꣩ */
static void __draw_cursor (int x, int y, int size)
{
    __set_pen_color(0x1f, 0x3f, 0x1f);
    __draw_h_line(x - size, x + size, y);
    __draw_v_line(x, y - size, y + size);
}

/* ����Ĳ�����Ҫ�ͻ��ƹ��ʱ�����һģһ�� */
static void __clear_cursor (int x, int y, int size)
{
    __set_pen_color(0, 0, 0);
    __draw_h_line(x - size, x + size, y);
    __draw_v_line(x, y - size, y + size);
}

/* ����У׼ */
static int __app_ts_calibrate (aw_ts_id                 id,
                               aw_ts_lib_calibration_t *p_cal)
{
    int                 i;
    struct aw_ts_state  sta;

    /* ��ʼ���������� */
    p_cal->log[0].x = 60 - 1;
    p_cal->log[0].y = 60 - 1;
    p_cal->log[1].x = __g_x_res - 60 - 1;
    p_cal->log[1].y = 60 - 1;
    p_cal->log[2].x = __g_x_res - 60 - 1;
    p_cal->log[2].y = __g_y_res - 60 - 1;
    p_cal->log[3].x = 60 - 1;
    p_cal->log[3].y = __g_y_res - 60 - 1;
    p_cal->log[4].x = __g_x_res / 2 - 1;
    p_cal->log[4].y = __g_y_res / 2 - 1;

    p_cal->cal_res_x = __g_x_res;
    p_cal->cal_res_y = __g_y_res;

    /* ��㴥�� */
    for (i = 0; i < 5; i++) {
        /* ��ʾ��� */

        if (i != 0) {
            __clear_cursor(p_cal->log[i - 1].x, p_cal->log[i - 1].y, 5);
        }
        __draw_cursor(p_cal->log[i].x, p_cal->log[i].y, 5);


        while (1) {
            /* �ȴ���ȡ�������λ�ô������� */
            if ((aw_ts_get_phys(id, &sta, 1) > 0) &&
                (sta.pressed == TRUE)) {
                p_cal->phy[i].x = sta.x;
                p_cal->phy[i].y = sta.y;

                aw_kprintf("\n x=%d, y=%d \r\n", (uint32_t)sta.x, (uint32_t)sta.y);
                while(1) {
                    aw_mdelay(500);
                    if ((aw_ts_get_phys(id, &sta, 1) == AW_OK) &&
                        (sta.pressed == FALSE)) {
                        break;
                    }
                }
                break;
            }
            aw_mdelay(10);
        }
    }

    __clear_cursor(p_cal->log[i - 1].x, p_cal->log[i - 1].y, 5);

    return 0;
}

aw_local aw_ts_id __touch_handel (void)
{
    aw_ts_id                sys_ts;
    aw_ts_lib_calibration_t cal;

    /* ��ȡ�����豸 */
    sys_ts = aw_ts_serv_id_get("480x272", 0, 0);

    if (sys_ts == NULL) {
        aw_kprintf("get touch server failed\r\n");
        while (1);
    }

    /* �ж��Ƿ��豸֧�ִ���У׼ */
    if (aw_ts_calc_flag_get(sys_ts)) {
        /* ����ϵͳ�������� */
        if (aw_ts_calc_data_read(sys_ts) != AW_OK) {
            /* û����Ч���ݣ�����У׼ */
            do {
                __app_ts_calibrate(sys_ts, &cal);
            } while (aw_ts_calibrate(sys_ts, &cal) != AW_OK);
            /* У׼�ɹ������津������ */
            aw_ts_calc_data_write(sys_ts);
        }
    } else {
        /* ��������Ҫ����XYת�� */
        aw_ts_set_orientation(sys_ts, AW_TS_SWAP_XY);
    }

    return sys_ts;
}

void demo_lcd_entry (void)
{
    aw_emwin_fb_info_t *p_fb;
    uint8_t            *p_buf;
    int i, ylen;
    struct aw_ts_state      ts;
    aw_ts_id                sys_ts;
    uint8_t color[][3] = {{0x1f, 0x00, 0x00},   //��ɫ
                          {0x00, 0x3f, 0x00},   //��ɫ
                          {0x00, 0x00, 0x1f},   //��ɫ
                          {0x1f, 0x3f, 0x00},   //��ɫ
                          {0x1f, 0x00, 0x1f},   //��ɫ
                          {0x00, 0x3f, 0x1f},   //��ɫ
                          {0x1f, 0x3f, 0x1f}};  //��ɫ

    /* ����ʾ��� */
    p_fb = aw_emwin_fb_open("imx1050_emwin_fb", 0);
    if (p_fb == NULL) {
        aw_kprintf("FB open failed.\r\n");
        return;
    }

    __g_x_res = p_fb->x_res;
    __g_y_res = p_fb->y_res;

    /* �����ڴ���Ϊ�Դ�ʹ�� */
    p_buf = aw_mem_align(p_fb->x_res * p_fb->y_res * 2, 4);
    if (p_buf == NULL) {
        aw_kprintf("allocate memory failed.\r\n");
        return;
    }

    __gp_frame_buffer = (uint16_t *)p_buf;
    memset(p_buf, 0, p_fb->x_res * p_fb->y_res * 2);

    /* Ϊ��ʾ��������Դ� */
    aw_emwin_fb_init(p_fb, (uint32_t*)p_buf, AW_FB_HORIZONTAL_SCREEN);

    /* �򿪱��Ⲣ������� */
    aw_emwin_fb_backlight(p_fb, 100);
    aw_emwin_fb_run(p_fb);

    /* ����У׼ */
    sys_ts = __touch_handel();
    memset(p_buf, 0, p_fb->x_res * p_fb->y_res * 2);

    __set_pen_color(0x1f, 0, 0);    /* ����һ������ */
    __draw_v_line(p_fb->x_res / 8 * 7, 0, p_fb->y_res);
    __set_pen_color(0, 0x3f, 0);    /* ����һ������ */
    __draw_h_line(0, p_fb->x_res / 4, p_fb->y_res / 2);

    /* ���Ʋ��� */
    ylen = p_fb->y_res / AW_NELEMENTS(color);
    for (i = 0; i < AW_NELEMENTS(color); i++) {
        __set_pen_color(color[i][0], color[i][1], color[i][2]);
        __draw_rect(p_fb->x_res / 4,
                    p_fb->x_res / 4 * 3,
                    ylen * i,
                    ylen * (i + 1));
    }

    /* �������� */
    __draw_words(0, 0, __g_my_words, sizeof(__g_my_words));

    /* �������� */
    while (1) {
        /* ������ȡ����״̬ */
        if (aw_ts_exec(sys_ts, &ts, 1) >= 0) {
            if (ts.x < p_fb->x_res && ts.y < p_fb->y_res) {
                __draw_point(ts.x, ts.y);
            }
        }

        aw_mdelay(10);
    }
}
/** [src_lcd] */

/* end of file */
