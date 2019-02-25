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

/* ������������ */
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

    /* ���� */
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    GUI_Exec();
    /* ���ù�� */
    cursor_show = GUI_CURSOR_GetState();
    p_cursor    = GUI_CURSOR_Select(&GUI_CursorCrossM);
    GUI_CURSOR_Show();

    /* ��ʼ���������� */
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

    /* ��㴥�� */
    for (i = 0; i < 5; i++) {
        GUI_SetBkColor(GUI_WHITE);
        GUI_SetColor(GUI_BLACK);
        GUI_SetTextAlign(GUI_TA_HCENTER);
        GUI_SetFont(&GUI_Font16_ASCII);
        GUI_DispStringAt("AWorks Touch Subsystem Calibration\n",  LCD_GetXSize() / 2,  LCD_GetYSize() / 2 - 20);

        /* ��ʾ��� */
        GUI_CURSOR_SetPosition(p_cal->log[i].x, p_cal->log[i].y);

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

    /* �ָ���� */
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

    /* ��ȡ�����豸 */
    sys_ts = aw_ts_serv_id_get("480x272", 0, 0);
    if (sys_ts == NULL) {
        while (1);//todo
    }

    /* �ж��Ƿ��豸֧�ִ���У׼ */
    if (aw_ts_calc_flag_get(sys_ts)) {
        /* ����ϵͳ�������� */
        if (aw_ts_calc_data_read(sys_ts) != AW_OK) {
            /* û����Ч���ݣ�����У׼ */
            do {
                if (app_ts_calibrate(sys_ts, &cal) < 0) {
                    //todo
                }
            } while (aw_ts_calibrate(sys_ts, &cal) != AW_OK);
            /* У׼�ɹ������津������ */
            aw_ts_calc_data_write(sys_ts);
        }
    } else {
        /* ��������Ҫ����XYת�� */
        aw_ts_set_orientation(sys_ts, AW_TS_SWAP_XY);
    }

    /* ���ʹ��������Ϣ */
    AW_SEMB_GIVE(__g_wait);

    AW_FOREVER {
        /* ������ȡ����״̬ */
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
    /* ��ʼ��һ���ź������û��ȴ�����У׼ */
    if (AW_SEMB_INIT(__g_wait, 0, AW_SEM_Q_PRIORITY) == NULL) {
        //todo
        return;
    }

    /* ���������������� */
    AW_TASK_INIT(__touch_task,                  /* ����ʵ�� */
                 "touch",                       /* �������� */
                 __TOUCH_TASK_PRIO,             /* �������ȼ� */
                 __TOUCH_TASK_STACK_SIZE,       /* �����ջ��С */
                 __touch_task_entry,           /* ������ں��� */
                 NULL);                         /* ������ڲ��� */
    /* �������� */
    AW_TASK_STARTUP(__touch_task);

    /* �ȴ��������� */
    AW_SEMB_TAKE(__g_wait, AW_SEM_WAIT_FOREVER);
}
