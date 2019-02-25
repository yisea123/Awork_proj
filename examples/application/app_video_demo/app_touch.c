/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

#include "app_video.h"
#include "aw_ts.h"

/* 触摸任务配置 */
#define __TOUCH_TASK_PRIO          2
#define __TOUCH_TASK_STACK_SIZE    (8 * 1024)
AW_TASK_DECL_STATIC(__touch_task, __TOUCH_TASK_STACK_SIZE);
AW_SEMB_DECL_STATIC(__g_wait);




/********************************************************************************/
int app_ts_calibrate (aw_ts_id                 id,
                      aw_ts_lib_calibration_t *p_cal)
{
    int                 i;
    struct aw_ts_state  sta;
    const GUI_CURSOR   *p_cursor;
    int                 cursor_show;

    /* 清屏 */
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    GUI_Exec();
    /* 设置光标 */
    cursor_show = GUI_CURSOR_GetState();
    p_cursor    = GUI_CURSOR_Select(&GUI_CursorCrossM);
    GUI_CURSOR_Show();

    /* 初始化触摸数据 */
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

    p_cal->cal_res_x = LCD_GetXSize();
    p_cal->cal_res_y = LCD_GetYSize();

    /* 五点触摸 */
    for (i = 0; i < 5; i++) {
        GUI_SetBkColor(GUI_WHITE);
        GUI_SetColor(GUI_BLACK);
        GUI_SetTextAlign(GUI_TA_HCENTER);
        GUI_SetFont(&GUI_Font16_ASCII);
        GUI_DispStringAt("AWorks Touch Subsystem Calibration\n",  LCD_GetXSize() / 2,  LCD_GetYSize() / 2 - 20);

        /* 显示光标 */
        GUI_CURSOR_SetPosition(p_cal->log[i].x, p_cal->log[i].y);

        while (1) {
            /* 等待获取光标所在位置触摸数据 */
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

    /* 恢复光标 */
    GUI_CURSOR_Select(p_cursor);
    if (cursor_show) {
        GUI_CURSOR_Show();
    } else {
        GUI_CURSOR_Hide();
    }

    return 0;
}




/********************************************************************************/
aw_local void __touch_task_entry (void *p_arg)
{
    GUI_PID_STATE           th;
    struct aw_ts_state      ts;
    aw_ts_id                sys_ts;
    aw_ts_lib_calibration_t cal;

    /* 获取触摸设备 */
    sys_ts = aw_ts_serv_id_get("480x272", 0, 0);
    if (sys_ts == NULL) {
        while (1);//todo
    }

    /* 判断是否设备支持触摸校准 */
    if (aw_ts_calc_flag_get(sys_ts)) {
        /* 加载系统触摸数据 */
        if (aw_ts_calc_data_read(sys_ts) != AW_OK) {
            /* 没有有效数据，进行校准 */
            do {
                if (app_ts_calibrate(sys_ts, &cal) < 0) {
                    //todo
                }
            } while (aw_ts_calibrate(sys_ts, &cal) != AW_OK);
            /* 校准成功，保存触摸数据 */
            aw_ts_calc_data_write(sys_ts);
        }
    } else {
        /* 电容屏需要进行XY转换 */
        aw_ts_set_orientation(sys_ts, AW_TS_SWAP_XY);
    }

    /* 发送触摸完成消息 */
    AW_SEMB_GIVE(__g_wait);

    AW_FOREVER {
        /* 持续获取触摸状态 */
        if (aw_ts_exec(sys_ts, &ts, 1) >= 0) {
            th.x        = ts.x;
            th.y        = ts.y;
            th.Pressed  = ts.pressed;
            th.Layer    = 0;
            GUI_TOUCH_StoreStateEx(&th);
            GUI_CURSOR_SetPositionEx(th.x, th.y, 0);
        }
        aw_mdelay(10);
    }
}




/********************************************************************************/
void app_touch_task (void)
{
    /* 初始化一个信号量，用户等待触摸校准 */
    if (AW_SEMB_INIT(__g_wait, 0, AW_SEM_Q_PRIORITY) == NULL) {
        //todo
        return;
    }

    /* 创建触摸服务任务 */
    AW_TASK_INIT(__touch_task,                  /* 任务实体 */
                 "touch",                       /* 任务名字 */
                 __TOUCH_TASK_PRIO,             /* 任务优先级 */
                 __TOUCH_TASK_STACK_SIZE,       /* 任务堆栈大小 */
                 __touch_task_entry,           /* 任务入口函数 */
                 NULL);                         /* 任务入口参数 */
    /* 启动任务 */
    AW_TASK_STARTUP(__touch_task);

    /* 等待触摸数据 */
    AW_SEMB_TAKE(__g_wait, AW_SEM_WAIT_FOREVER);
}
