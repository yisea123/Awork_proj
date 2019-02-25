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
 * \brief 通过shell命令控制LCD显示屏和触摸屏
 * - 操作步骤：
 *   1. 需要在aw_prj_params.h头文件里使能
 *      - AW_COM_CONSOLE
 *      - 对应平台的串口宏
 *      - 对应显示屏的宏
 *      - 对应触摸屏的宏
 *
 * - 实验现象：
 *   1. 执行"lcd -c"，打印可以使用的颜色
 *   2. 执行"lcd -c +颜色"，在屏幕上填充纯色
 *   3. 执行 "lcd -c +颜色1 -v +颜色2",在屏幕上填充渐变色（垂直梯度）
 *   4. 执行 "lcd -c +颜色1 -h +颜色2",在屏幕上填充渐变色（水平梯度）
 *   5. 执行 "lcd -j" 屏幕校准
 *   6. 执行 "lcd -b +背光级别 ",调整屏幕背光，背光级别为0-100，不在此范围的按100算
 *
 * - 备注：
 *   1. 颜色可以直接输入16进制数，必须加0x前缀，一些常用的颜色也可直接输入颜色。
 *
 * \par 源代码
 * \snippet app_buzzer.c app_buzzer
 *
 * \internal
 * \par Modification History
 * - 1.00 18-07-11  sdq, first implementation.
 * \endinternal
 */

/** [src_app_lcd] */
#include "aworks.h"                     /* 此头文件必须被首先包含 */
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

#define TEST_DEV_EMWIN_FB       "imx1050_emwin_fb"  /*根据具体平台修改*/

/******************************************************************************/
/**
 * \brief 按ctrl+C退出
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
 * \brief 屏幕校准
 */
aw_local int __calibrate (aw_ts_id                 id,
                          aw_ts_lib_calibration_t *p_cal)
{
    int                 i;
    struct aw_ts_state  sta;
    const GUI_CURSOR   *cursor;
    int                 cur_sta;
    int                 ret = 0;

    /* 填充背景色 */
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();

    /* 设置光标为十字型并保存旧光标类型 */
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
        /* 显示提示信息 */
        GUI_SetColor(GUI_BLACK);
        GUI_SetTextAlign(GUI_TA_HCENTER);
        GUI_SetFont(&GUI_Font16_ASCII);
        GUI_DispStringAt("AWorks Touch Subsystem Calibration\n",  LCD_GetXSize() / 2,  LCD_GetYSize() / 2 - 20);

        /* 绘制提示光标 */
        GUI_CURSOR_SetPosition(p_cal->log[i].x, p_cal->log[i].y);
        GUI_Exec();

        /* 等待触摸数据 */
        while (1) {
            if ((aw_ts_get_phys(id, &sta, 1) > 0) &&
                (sta.pressed == TRUE)) {
                /* 获得触摸点 */
                p_cal->phy[i].x = sta.x;
                p_cal->phy[i].y = sta.y;

                aw_kprintf("\n x=%d, y=%d \r\n", (uint32_t)sta.x, (uint32_t)sta.y);
                while(1) {
                    aw_mdelay(500);
                    /* 等待触摸释放 */
                    if ((aw_ts_exec(id, &sta, 1) == AW_OK) &&
                        (sta.pressed == FALSE)) {
                        break;
                    }
                }
                break;
            }
            aw_mdelay(10);

            /* 判断是否要终止程序 */
            if (__ctlc_is_press()) {
                aw_kprintf("\nControl-C\n^C\n\n");
                GUI_Clear();
                ret = -1;
                goto __exit;
            }
        }
    }

__exit:
    /* 回复光标信息 */
    GUI_CURSOR_Select(cursor);
    if (cur_sta) {
        GUI_CURSOR_Show();
    } else {
        GUI_CURSOR_Hide();
    }

    return ret;
}

/* 将颜色和字符对应起来 */
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
 * \brief 根据字符串匹配颜色
 *
 * \param[in] color：支持的颜色库
 * \param[in] color_num：库中包含的颜色个数
 * \param[in] p_str：表示颜色的字符串
 *
 * \retval 匹配到的颜色
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

    /* 库中没有匹配到则匹配16进制数 */
    sscanf(p_str, "%x", (unsigned int*)&color);
    color &= 0xFFFFFF;  /* 取出有效位数*/

    return color;
}


/**
 * \brief 根据字符串匹配颜色
 *
 * \param[in] color：支持的颜色库
 * \param[in] color_num：库中包含的颜色个数
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

    uint8_t cg_flag = 0;    /* b2为1表示需要设置颜色，b1为1表示梯度颜色，b0为1表示水平梯度 */
    GUI_COLOR color1, color2;

    while (1) {
        if (aw_shell_args_get(p_user, "-j", 0) == AW_OK) {
            /* 屏幕校准 */
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

    /* 设置屏幕颜色 */
    if (cg_flag) {
        if (cg_flag & (1 << 1)) {   /* 渐变色 */
            if (cg_flag & 1) {      /* 水平梯度 */
                GUI_DrawGradientH(0,
                                  0,
                                  LCD_GetXSizeMax(),
                                  LCD_GetYSizeMax(),
                                  color1,
                                  color2);
            } else {                /* 垂直梯度 */
                GUI_DrawGradientV(0,
                                  0,
                                  LCD_GetXSizeMax(),
                                  LCD_GetYSizeMax(),
                                  color1,
                                  color2);
            }
        } else {                    /* 纯色 */
            GUI_SetColor(color1);
            GUI_FillRect(0, 0, LCD_GetXSizeMax(), LCD_GetYSizeMax());
        }
    }

    return ret;
}
#endif /* APP_LCD */
