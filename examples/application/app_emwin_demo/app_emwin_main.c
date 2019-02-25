/*
 * app_emwin_main.c
 *
 *  Created on: 2018年5月11日
 *      Author: wengyedong
 */

#include "aworks.h"
#include "GUI.h"


extern void app_ts_init (void);
extern void app_desktop_init (void);



void app_emwin_demo (void)
{
    /* 初始化GUI */
    GUI_Init();

    /* 触摸支持 */
    app_ts_init();

    /* 桌面应用 */
    app_desktop_init();
}
