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
 * \brief ͨ��shell�������LCD��ʾ���ʹ�����
 * - �������裺
 *   1. ��Ҫ��aw_prj_params.hͷ�ļ���ʹ��
 *      - AW_COM_CONSOLE
 *      - ��Ӧƽ̨�Ĵ��ں�
 *      - ��Ӧ��ʾ���ĺ�
 *      - ��Ӧ�������ĺ�
 *
 * - ʵ������
 *   1. ִ��"lcd -c"����ӡ����ʹ�õ���ɫ
 *   2. ִ��"lcd -c +��ɫ"������Ļ����䴿ɫ
 *   3. ִ�� "lcd -c +��ɫ1 -v +��ɫ2",����Ļ����佥��ɫ����ֱ�ݶȣ�
 *   4. ִ�� "lcd -c +��ɫ1 -h +��ɫ2",����Ļ����佥��ɫ��ˮƽ�ݶȣ�
 *   5. ִ�� "lcd -j" ��ĻУ׼
 *   6. ִ�� "lcd -b +���⼶�� ",������Ļ���⣬���⼶��Ϊ0-100�����ڴ˷�Χ�İ�100��
 *
 * - ��ע��
 *   1. ��ɫ����ֱ������16�������������0xǰ׺��һЩ���õ���ɫҲ��ֱ��������ɫ��
 *
 * \par Դ����
 * \snippet app_buzzer.c app_buzzer
 *
 * \internal
 * \par Modification History
 * - 1.00 18-07-11  sdq, first implementation.
 * \endinternal
 */

/** [src_app_lcd] */
#include "aworks.h"                     /* ��ͷ�ļ����뱻���Ȱ��� */
#include "aw_shell.h"
#include "aw_vdebug.h"
#include "aw_ts.h"
#include "app_config.h"
#include "GUI.h"
#include "stdio.h"
#include "string.h"
#include "aw_emwin_fb.h"
#include "aw_serial.h"
#include "aw_delay.h"

#ifdef APP_LCD

#define TEST_DEV_EMWIN_FB       "imx1050_emwin_fb"  /*���ݾ���ƽ̨�޸�*/

/******************************************************************************/
/**
 * \brief ��ctrl+C�˳�
 */
aw_local bool_t  __ctlc_is_press (void)
{
    char  ch = 0;

    uint32_t    size;

    size = aw_serial_read(0, (void *)&ch, 1);

    if ((size == 1) && (ch == 0x03)) {
        return  TRUE;
    }

    return  FALSE;
}

/**
 * \brief ��ĻУ׼
 */
aw_local int __calibrate (aw_ts_id                 id,
                          aw_ts_lib_calibration_t *p_cal)
{
    int                 i;
    struct aw_ts_state  sta;
    const GUI_CURSOR   *cursor;
    int                 cur_sta;
    int                 ret = 0;

    /* ��䱳��ɫ */
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();

    /* ���ù��Ϊʮ���Ͳ�����ɹ������ */
    cursor  = GUI_CURSOR_Select(&GUI_CursorCrossM);
    cur_sta = GUI_CURSOR_GetState();
    GUI_CURSOR_Show();

    p_cal->log[0].x = 60 - 1;
    p_cal->log[0].y = 60 - 1;
    p_cal->log[1].x = LCD_GetXSize() - 60 - 1;
    p_cal->log[1].y = 60 - 1;
    p_cal->log[2].x = LCD_GetXSize() - 60 - 1;
    p_cal->log[2].y = LCD_GetYSize() - 60 - 1;
    p_cal->log[3].x = 60 - 1;
    p_cal->log[3].y = LCD_GetYSize() - 60 - 1;
    p_cal->log[4].x = LCD_GetXSize() / 2 - 1;
    p_cal->log[4].y = LCD_GetYSize() / 2 - 1;

    for (i = 0; i < 5; i++) {
        /* ��ʾ��ʾ��Ϣ */
        GUI_SetColor(GUI_BLACK);
        GUI_SetTextAlign(GUI_TA_HCENTER);
        GUI_SetFont(&GUI_Font16_ASCII);
        GUI_DispStringAt("AWorks Touch Subsystem Calibration\n",  LCD_GetXSize() / 2,  LCD_GetYSize() / 2 - 20);

        /* ������ʾ��� */
        GUI_CURSOR_SetPosition(p_cal->log[i].x, p_cal->log[i].y);
        GUI_Exec();

        /* �ȴ��������� */
        while (1) {
            if ((aw_ts_get_phys(id, &sta, 1) > 0) &&
                (sta.pressed == TRUE)) {
                /* ��ô����� */
                p_cal->phy[i].x = sta.x;
                p_cal->phy[i].y = sta.y;

                aw_kprintf("\n x=%d, y=%d \r\n", (uint32_t)sta.x, (uint32_t)sta.y);
                while(1) {
                    aw_mdelay(500);
                    /* �ȴ������ͷ� */
                    if ((aw_ts_exec(id, &sta, 1) == AW_OK) &&
                        (sta.pressed == FALSE)) {
                        break;
                    }
                }
                break;
            }
            aw_mdelay(10);

            /* �ж��Ƿ�Ҫ��ֹ���� */
            if (__ctlc_is_press()) {
                aw_kprintf("\nControl-C\n^C\n\n");
                GUI_Clear();
                ret = -1;
                goto __exit;
            }
        }
    }

__exit:
    /* �ظ������Ϣ */
    GUI_CURSOR_Select(cursor);
    if (cur_sta) {
        GUI_CURSOR_Show();
    } else {
        GUI_CURSOR_Hide();
    }

    return ret;
}

/* ����ɫ���ַ���Ӧ���� */
struct color_opt {
    GUI_COLOR color;
    const char *p_str;
};

static struct color_opt __g_color_coll[] = {
        {GUI_BLUE,         "blue"},
        {GUI_GREEN,        "green"},
        {GUI_RED,          "red"},
        {GUI_CYAN,         "cyan"},
        {GUI_MAGENTA,      "magenta"},
        {GUI_YELLOW,       "yellow"},
        {GUI_LIGHTBLUE,    "lightblue"},
        {GUI_LIGHTGREEN,   "lightgreen"},
        {GUI_LIGHTRED,     "lightred"},
        {GUI_LIGHTCYAN,    "lightcyan"},
        {GUI_LIGHTMAGENTA, "lightmagenta"},
        {GUI_LIGHTYELLOW,  "lightyellow"},
        {GUI_DARKBLUE,     "darkblue"},
        {GUI_DARKGREEN,    "darkgreen"},
        {GUI_DARKRED,      "darkred"},
        {GUI_DARKCYAN,     "darkcyan"},
        {GUI_DARKMAGENTA,  "darkmagenta"},
        {GUI_DARKYELLOW,   "darkyellow"},
        {GUI_WHITE,        "white"},
        {GUI_LIGHTGRAY,    "lightgray"},
        {GUI_GRAY,         "gray"},
        {GUI_DARKGRAY,     "darkgray"},
        {GUI_BLACK,        "black"},
        {GUI_BROWN,        "brown"},
        {GUI_ORANGE,       "orange"},
};

/**
 * \brief �����ַ���ƥ����ɫ
 *
 * \param[in] color��֧�ֵ���ɫ��
 * \param[in] color_num�����а�������ɫ����
 * \param[in] p_str����ʾ��ɫ���ַ���
 *
 * \retval ƥ�䵽����ɫ
 */
aw_local GUI_COLOR __parse_color (struct color_opt *p_my_color,
                                  uint32_t color_num,
                                  const char *p_str)
{
    uint32_t i;
    GUI_COLOR color;

    for (i = 0; i < color_num; i++) {
        if (!strcmp(p_my_color[i].p_str, p_str)) {
            return p_my_color[i].color;
        }
    }

    /* ����û��ƥ�䵽��ƥ��16������ */
    sscanf(p_str, "%x", (unsigned int*)&color);
    color &= 0xFFFFFF;  /* ȡ����Чλ��*/

    return color;
}


/**
 * \brief �����ַ���ƥ����ɫ
 *
 * \param[in] color��֧�ֵ���ɫ��
 * \param[in] color_num�����а�������ɫ����
 */
static void __print_color_opt (struct color_opt *p_my_color,
                               uint32_t          color_num)
{
    uint32_t i;

    for (i = 0; i < color_num; i++) {
        aw_kprintf("%s\r\n", p_my_color[i].p_str);
    }
}

/******************************************************************************/
int app_lcd (int argc, char **argv, struct aw_shell_user *p_user)
{
    aw_ts_id                sys_ts;
    aw_ts_lib_calibration_t cal;
    aw_emwin_fb_info_t     *p_emwin_fb = NULL;
    int                    ret = 0;
    int                    bk_bright = 0;

    uint8_t cg_flag = 0;    /* b2Ϊ1��ʾ��Ҫ������ɫ��b1Ϊ1��ʾ�ݶ���ɫ��b0Ϊ1��ʾˮƽ�ݶ� */
    GUI_COLOR color1, color2;

    while (1) {
        if (aw_shell_args_get(p_user, "-j", 0) == AW_OK) {
            /* ��ĻУ׼ */
            sys_ts = aw_ts_serv_id_get("480x272", 0x00, 0x00);
            do {
                if (__calibrate(sys_ts, &cal) < 0) {
                    return AW_OK;
                }
            } while (aw_ts_calibrate(sys_ts, &cal) != AW_OK);
            aw_ts_calc_data_write(sys_ts);

            GUI_CURSOR_Hide();
        } else if (aw_shell_args_get(p_user, "-b", 1) == AW_OK) {
            p_emwin_fb = aw_emwin_fb_open(TEST_DEV_EMWIN_FB, 0);
            if(p_emwin_fb == NULL) {
                aw_kprintf("aw_emwin_fb_open error!\r\n");
                break;
            }
            bk_bright = aw_shell_long_arg(p_user, 1);

            aw_emwin_fb_backlight(p_emwin_fb, bk_bright);
        } else if (aw_shell_args_get(p_user, "-c", 1) == AW_OK) {
            cg_flag |= 1 << 2;
            color1 = __parse_color(__g_color_coll,
                                   AW_NELEMENTS(__g_color_coll),
                                   aw_shell_str_arg(p_user, 1));
        }  else if (aw_shell_args_get(p_user, "-c", 0) == AW_OK) {
            __print_color_opt(__g_color_coll, AW_NELEMENTS(__g_color_coll));
        } else if (aw_shell_args_get(p_user, "-v", 1) == AW_OK) {
            cg_flag |= 1 << 1;
            color2 = __parse_color(__g_color_coll,
                                   AW_NELEMENTS(__g_color_coll),
                                   aw_shell_str_arg(p_user, 1));
        } else if (aw_shell_args_get(p_user, "-h", 1) == AW_OK) {
            cg_flag |= 1 << 1;
            cg_flag |= 1 << 0;
            color2 = __parse_color(__g_color_coll,
                                   AW_NELEMENTS(__g_color_coll),
                                   aw_shell_str_arg(p_user, 1));
        } else {
            break;
        }
    }

    /* ������Ļ��ɫ */
    if (cg_flag) {
        if (cg_flag & (1 << 1)) {   /* ����ɫ */
            if (cg_flag & 1) {      /* ˮƽ�ݶ� */
                GUI_DrawGradientH(0,
                                  0,
                                  LCD_GetXSizeMax(),
                                  LCD_GetYSizeMax(),
                                  color1,
                                  color2);
            } else {                /* ��ֱ�ݶ� */
                GUI_DrawGradientV(0,
                                  0,
                                  LCD_GetXSizeMax(),
                                  LCD_GetYSizeMax(),
                                  color1,
                                  color2);
            }
        } else {                    /* ��ɫ */
            GUI_SetColor(color1);
            GUI_FillRect(0, 0, LCD_GetXSizeMax(), LCD_GetYSizeMax());
        }
    }

    return ret;
}
#endif /* APP_LCD */
