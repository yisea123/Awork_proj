/*
 * app_emwin_main.c
 *
 *  Created on: 2018��5��11��
 *      Author: wengyedong
 */

#include "aworks.h"
#include "GUI.h"


extern void app_ts_init (void);
extern void app_desktop_init (void);



void app_emwin_demo (void)
{
    /* ��ʼ��GUI */
    GUI_Init();

    /* ����֧�� */
    app_ts_init();

    /* ����Ӧ�� */
    app_desktop_init();
}
