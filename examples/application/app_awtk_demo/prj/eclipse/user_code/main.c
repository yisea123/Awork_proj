/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_led.h"
#include "aw_delay.h"
#include "aw_emwin_fb.h"

#define LED 0

#define TK_STACK_SIZE 64 * 1024

extern aw_emwin_fb_info_t* aworks_lcd_init(void);
extern int gui_app_start(int lcd_w, int lcd_h) ;
extern void app_ts_init (void);


aw_local void __task_entry(void *p_arg)
{
  aw_emwin_fb_info_t* fb = aworks_lcd_init();

  gui_app_start(fb->x_res, fb->y_res);
}




void app_awtk_demo (void)
{
  /* ��������ʵ�壬����ջ�ռ��СΪ4096  */
  AW_TASK_DECL_STATIC(lcd_task, TK_STACK_SIZE);

  AW_TASK_INIT(lcd_task,      /* ����ʵ�� */
               "awtk_task",   /* �������� */
               5,             /* �������ȼ� */
               TK_STACK_SIZE, /* �����ջ��С */
               __task_entry,  /* ������ں��� */
               NULL);         /* ������ڲ��� */

  AW_TASK_STARTUP(lcd_task); /* �������� */
}




int aw_main()
{
    aw_kprintf("\r\nApplication Start. \r\n");

    app_ts_init();
    app_awtk_demo();

    while (1) {
        aw_led_toggle(LED);
        aw_mdelay(500);
    }

    return 0;
}


/* end of file*/
