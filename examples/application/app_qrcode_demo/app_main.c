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
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_buzzer.h"

#include "string.h"

#include "GUI.H"
#include "WM.H"
#include "TEXT.H"


extern void *app_video_create (WM_HWIN hwin,
                               int x, int y,
                               int xsize, int ysize,
                               void  *p_arg,
                               void (*pfn_img) (void *p_arg, void *img, int width, int height));


extern void app_video_destroy (void *handle);

extern void *app_qrc_create (int   max_width,
                             int   max_height,
                             void  *p_arg,
                             void (*pfn_done) (void *p_arg, bool_t found, void *p_dat, int len));
extern void app_qrc_destroy (void *handle);
extern aw_err_t app_qrc_once (void *handle,
                              void *img,
                              int   width,
                              int   height);



#define __MAIN_TSK_STACK  10 * 1024
AW_TASK_DECL_STATIC(__main_tsk, __MAIN_TSK_STACK);



#define __QRC_BUF_SIZE  128




/******************************************************************************/
aw_local void __win_back_cb (WM_MESSAGE *pMsg)
{
    switch (pMsg->MsgId) {
    case WM_PAINT:
        /* 设置背景颜色  */
        GUI_SetBkColor(GUI_LIGHTGRAY);
        GUI_Clear();
        break;

    default:
        WM_DefaultProc(pMsg);
        break;

    }
}




/******************************************************************************/
aw_local void __qrc_done (void *p_arg, bool_t found, void *p_dat, int len)
{
    if (found) {
        /* 二维码识别成功 */
        len = min(len, __QRC_BUF_SIZE);
        memcpy(p_arg, p_dat, len);
        aw_kprintf("%s\r\n", p_dat);
        aw_buzzer_beep(50);
    }
}




/******************************************************************************/
aw_local void __img_get (void *p_arg, void *img, int width, int height)
{
    /* 将摄像头捕获的画面交给二维码识别程序进行识别 */
    app_qrc_once(p_arg, img, width, height);
}




/******************************************************************************/
void __main_tsk_handle (void *p_arg)
{
    WM_HWIN          hwin = -1;
    void            *video_handle = NULL;
    void            *qrc_handle = NULL;
    aw_local char    qr_str[__QRC_BUF_SIZE];
    TEXT_Handle      htext = -1;

    GUI_Init();

    /* 创建一个背景窗口 */
    hwin = WM_CreateWindowAsChild(0, 0,
                                  LCD_GetXSize(),
                                  LCD_GetYSize(),
                                  WM_HBKWIN,
                                  WM_CF_SHOW,
                                  __win_back_cb,
                                  sizeof(WM_HMEM));

    /* 文本框，用于显示二维码内容 */
    htext = TEXT_CreateEx(330, 10, 145, 200,
                          hwin,
                          WM_CF_SHOW,
                          TEXT_CF_LEFT | TEXT_CF_VCENTER | WM_CF_SHOW,
                          GUI_ID_TEXT0,
                          "");
    TEXT_SetWrapMode(htext, GUI_WRAPMODE_CHAR);

    /* 创建一个二维码识别程序 */
    qrc_handle = app_qrc_create(320, 240, qr_str, __qrc_done);
    if (qrc_handle == NULL) {
        goto __failed;
    }

    /* 创建一个摄像头显示程序 */
    video_handle = app_video_create(hwin, 0, 0, 326, 272, qrc_handle, __img_get);
    if (video_handle == NULL) {
        goto __failed;
    }

    AW_FOREVER {
        /* 更新二维码内容显示 */
        TEXT_SetText(htext, qr_str);
        GUI_Exec();
        aw_mdelay(10);
    }

__failed:
    if (hwin > 0) {
        WM_DetachWindow(hwin);
    }
    if (qrc_handle) {
        app_qrc_destroy(qrc_handle);
    }
    if (video_handle) {
        app_video_destroy(video_handle);
    }

    AW_TASK_TERMINATE(__main_tsk);
}




/******************************************************************************/
void app_demo_qrc_main (void)
{
    AW_TASK_INIT(__main_tsk,
                 "QRC main",
                 10,
                 __MAIN_TSK_STACK ,
                 __main_tsk_handle,
                 (void *)NULL);

    AW_TASK_STARTUP(__main_tsk);
}
