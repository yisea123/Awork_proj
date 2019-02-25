#include "aworks.h"
#include "app_meter.h"
#include "aw_task.h"
#include "aw_sem.h"
#include "aw_time.h"


/* 仪表盘任务配置 */
#define __METER_TASK_PRIO          10
#define __METER_TASK_STACK_SIZE    (4 * 1024)
AW_TASK_DECL_STATIC(__meter_task, __METER_TASK_STACK_SIZE);
AW_MUTEX_DECL(disp_lock);


extern void app_meter_task_init (void);


/* 系统初始时加载仪表盘界面各元素的背景图片 */
void  meter_load_img (void)
{    
    /* 显示仪表盘背景图片 */
    GUI_DrawBitmap(&bmp_background, 0, 0);

    /* 速度表盘 */
    GUI_DrawBitmap(&bmp_speedmeter_bg, 8, 87);

    /* 转速表盘 */
    GUI_DrawBitmap(&bmp_rpmmeter_bg, 574, 87);

    /* 显示视频监控界面 */
    GUI_DrawBitmap(&bmp_bmcamera, 240, 120);
    
    /* 车灯状态显示 */

    /* 工作状态 */
    GUI_DrawBitmap(&bmp_work_off, 630, 55);

    /* 左转向灯 */
    GUI_DrawBitmap(&bmp_leftlight_disable, 240, 86);

    /* 行车灯 */
    GUI_DrawBitmap(&bmp_frontlight_disable, 290, 86);

    /* 近光灯 */
    GUI_DrawBitmap(&bmp_headlightlow_disable, 338, 86);

    /* 远光灯 */
    GUI_DrawBitmap(&bmp_headlighthigh_disable, 385, 86);

    /* 后雾灯 */
    GUI_DrawBitmap(&bmp_foglightrear_disable, 432, 86);

    /* 前雾灯 */
    GUI_DrawBitmap(&bmp_foglightfont_disable, 480, 86);

    /* 右转向灯 */
    GUI_DrawBitmap(&bmp_rightlight_disable, 525, 86);

    /* 警告指示灯 */
    
    /* 点火警告指示灯 */
    GUI_DrawBitmap(&bmp_battery_disable, 240, 376);

    /* 发动机故障警告指示灯 */
    GUI_DrawBitmap(&bmp_engine_disable, 290, 376);

    /* 机油压力警告指示灯 */
    GUI_DrawBitmap(&bmp_engineoil_disable, 340, 376);

    /* 传动系统警告指示灯 */
    GUI_DrawBitmap(&bmp_fix_disable, 395, 376);

    /* 制动系统告警指示灯 */
    GUI_DrawBitmap(&bmp_barke_disable, 440, 376);

    /* 安全带警告指示灯 */
    GUI_DrawBitmap(&bmp_safebelt_disable, 490, 376);

    /* 车门警告指示灯 */
    GUI_DrawBitmap(&bmp_cardoor_disable, 535, 376);

    /* 燃油表 */
    GUI_DrawBitmap(&bmp_oil_static, 74, 304);

    /* 水温表 */
    GUI_DrawBitmap(&bmp_water_static, 596, 304);
}


/* 设置时间 */
aw_local void __set_time (void)
{
    aw_tm_t tm;
    tm.tm_year = 2018 - 1900;
    tm.tm_mon = 7;
    tm.tm_mday = 13;
    tm.tm_hour = 13;
    tm.tm_min = 0,
    tm.tm_sec = 0;
    aw_tm_set (&tm);
}


/* 仪表盘Demo程序入口 */
void app_meter_demo (void)
{

    int  oil_val    = 0;
    int  water_temp = 9;
    uint8_t dis_state = 0;

    /* 初始化GUI */
    GUI_Init();    
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();

    /* 加载仪表盘各元素的背景图片 */
    meter_load_img();

    /* 保存速度表盘的背景 */
    save_speedometer_bk();

    /* 保存转速表盘的背景 */
    save_tachometer_bk();

    /* 初始化仪表盘任务 */
    app_meter_task_init();

    /* 使能抗锯齿 */
    GUI_AA_SetFactor(6);

    /* 设置系统时间 */
    __set_time();

    /* 初始化互斥信号量 */
    AW_MUTEX_INIT(disp_lock, AW_SEM_Q_PRIORITY);

    AW_FOREVER {

        AW_MUTEX_LOCK(disp_lock, AW_WAIT_FOREVER);

        /* 更新油量和水温状态显示 */
        meter_dis_oil(oil_val);
        meter_dis_water_temp(water_temp);

        if ((oil_val++) > OIL_MAX) {
            oil_val = 0;
        }

        if ((water_temp--) <= 0) {
            water_temp = TEMP_MAX;
        }

        switch (dis_state) {

        case 0:
            meter_dis_work_state(kPower_on);
            meter_dis_rightlight(kLight_off);
            meter_dis_cardoor(kAlarm_off);
            break;
        case 1:
            meter_dis_work_state(kPower_off);
            meter_dis_leftlight(kLight_on);
            meter_dis_battery(kAlarm_on);
            break;
        case 2:
            meter_dis_leftlight(kLight_off);
            meter_dis_battery(kAlarm_off);

            meter_dis_frontlight(kLight_on);
            meter_dis_engine(kAlarm_on);
            break;
        case 3:
            meter_dis_frontlight(kLight_off);
            meter_dis_engine(kAlarm_off);

            meter_dis_headlightlow(kLight_on);
            meter_dis_engineoil(kAlarm_on);
            break;

        case 4:
            meter_dis_headlightlow(kLight_off);
            meter_dis_engineoil(kAlarm_off);

            meter_dis_headlighthigh(kLight_on);
            meter_dis_fix(kAlarm_on);
            break;

        case 5:
            meter_dis_headlighthigh(kLight_off);
            meter_dis_fix(kAlarm_off);

            meter_dis_foglightrear(kLight_on);
            meter_dis_barke(kAlarm_on);
            break;

        case 6:
            meter_dis_foglightrear(kLight_off);
            meter_dis_barke(kAlarm_off);

            meter_dis_foglightfont(kLight_on);
            meter_dis_safebelt(kAlarm_on);
            break;

        case 7:
            meter_dis_foglightfont(kLight_off);
            meter_dis_safebelt(kAlarm_off);

            meter_dis_rightlight(kLight_on);
            meter_dis_cardoor(kAlarm_on);
            break;
        }

        dis_state++;
        if (dis_state > 7) {
            dis_state = 0;
        }

        /* 更新时间显示 */
        meter_dis_time (kDisplay_on);

        AW_MUTEX_UNLOCK(disp_lock);

        GUI_Delay(500);
    }
}


/* 表盘任务 */
aw_local void __meter_task_entry (void *p_arg)
{
    int speed = 0;
    int rpm   = 0;

    uint8_t  sp_flag  = 0;
    uint8_t  rpm_flag = 0;
    uint32_t km_val   = 0;

    AW_FOREVER {

        AW_MUTEX_LOCK(disp_lock, AW_WAIT_FOREVER);

        if (sp_flag == 0) {
            speed++;
            if (speed >= SPEED_MAX) {
                sp_flag = 1;
            }
        } else if (sp_flag == 1) {
            speed--;
            if (speed <= 0) {
                sp_flag = 0;
            }
        }

        /* 更新速度表盘 */
        meter_dis_speedometer(speed);

        if (rpm_flag == 0) {
            rpm += 100;
            if (rpm >= RPM_MAX) {
                rpm_flag = 1;
            }
        } else if (rpm_flag == 1) {
            rpm -= 100;
            if (rpm <= 0) {
                rpm_flag = 0;
            }
        }

        /* 更新转速表盘 */
        meter_dis_tachometer(rpm);

        /* 更新总里程 */
        km_val++;
        if (km_val > KM_MAX) {
            km_val = 0;
        }
        meter_dis_kilometer(km_val);
        AW_MUTEX_UNLOCK(disp_lock);

        GUI_Delay(10);

    }
}

void app_meter_task_init (void)
{
    AW_TASK_INIT(__meter_task,                  /* 任务实体 */
                 "meter_task",                  /* 任务名字 */
                 __METER_TASK_PRIO,             /* 任务优先级 */
                 __METER_TASK_STACK_SIZE,       /* 任务堆栈大小 */
                 __meter_task_entry,            /* 任务入口函数 */
                 NULL);                         /* 任务入口参数 */

    /* 启动任务 */
    AW_TASK_STARTUP(__meter_task);
}

/* end of file */
