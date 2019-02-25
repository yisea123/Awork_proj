#include "aworks.h"
#include "app_meter.h"
#include "aw_task.h"
#include "aw_sem.h"
#include "aw_time.h"


/* �Ǳ����������� */
#define __METER_TASK_PRIO          10
#define __METER_TASK_STACK_SIZE    (4 * 1024)
AW_TASK_DECL_STATIC(__meter_task, __METER_TASK_STACK_SIZE);
AW_MUTEX_DECL(disp_lock);


extern void app_meter_task_init (void);


/* ϵͳ��ʼʱ�����Ǳ��̽����Ԫ�صı���ͼƬ */
void  meter_load_img (void)
{    
    /* ��ʾ�Ǳ��̱���ͼƬ */
    GUI_DrawBitmap(&bmp_background, 0, 0);

    /* �ٶȱ��� */
    GUI_DrawBitmap(&bmp_speedmeter_bg, 8, 87);

    /* ת�ٱ��� */
    GUI_DrawBitmap(&bmp_rpmmeter_bg, 574, 87);

    /* ��ʾ��Ƶ��ؽ��� */
    GUI_DrawBitmap(&bmp_bmcamera, 240, 120);
    
    /* ����״̬��ʾ */

    /* ����״̬ */
    GUI_DrawBitmap(&bmp_work_off, 630, 55);

    /* ��ת��� */
    GUI_DrawBitmap(&bmp_leftlight_disable, 240, 86);

    /* �г��� */
    GUI_DrawBitmap(&bmp_frontlight_disable, 290, 86);

    /* ����� */
    GUI_DrawBitmap(&bmp_headlightlow_disable, 338, 86);

    /* Զ��� */
    GUI_DrawBitmap(&bmp_headlighthigh_disable, 385, 86);

    /* ����� */
    GUI_DrawBitmap(&bmp_foglightrear_disable, 432, 86);

    /* ǰ��� */
    GUI_DrawBitmap(&bmp_foglightfont_disable, 480, 86);

    /* ��ת��� */
    GUI_DrawBitmap(&bmp_rightlight_disable, 525, 86);

    /* ����ָʾ�� */
    
    /* ��𾯸�ָʾ�� */
    GUI_DrawBitmap(&bmp_battery_disable, 240, 376);

    /* ���������Ͼ���ָʾ�� */
    GUI_DrawBitmap(&bmp_engine_disable, 290, 376);

    /* ����ѹ������ָʾ�� */
    GUI_DrawBitmap(&bmp_engineoil_disable, 340, 376);

    /* ����ϵͳ����ָʾ�� */
    GUI_DrawBitmap(&bmp_fix_disable, 395, 376);

    /* �ƶ�ϵͳ�澯ָʾ�� */
    GUI_DrawBitmap(&bmp_barke_disable, 440, 376);

    /* ��ȫ������ָʾ�� */
    GUI_DrawBitmap(&bmp_safebelt_disable, 490, 376);

    /* ���ž���ָʾ�� */
    GUI_DrawBitmap(&bmp_cardoor_disable, 535, 376);

    /* ȼ�ͱ� */
    GUI_DrawBitmap(&bmp_oil_static, 74, 304);

    /* ˮ�±� */
    GUI_DrawBitmap(&bmp_water_static, 596, 304);
}


/* ����ʱ�� */
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


/* �Ǳ���Demo������� */
void app_meter_demo (void)
{

    int  oil_val    = 0;
    int  water_temp = 9;
    uint8_t dis_state = 0;

    /* ��ʼ��GUI */
    GUI_Init();    
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();

    /* �����Ǳ��̸�Ԫ�صı���ͼƬ */
    meter_load_img();

    /* �����ٶȱ��̵ı��� */
    save_speedometer_bk();

    /* ����ת�ٱ��̵ı��� */
    save_tachometer_bk();

    /* ��ʼ���Ǳ������� */
    app_meter_task_init();

    /* ʹ�ܿ���� */
    GUI_AA_SetFactor(6);

    /* ����ϵͳʱ�� */
    __set_time();

    /* ��ʼ�������ź��� */
    AW_MUTEX_INIT(disp_lock, AW_SEM_Q_PRIORITY);

    AW_FOREVER {

        AW_MUTEX_LOCK(disp_lock, AW_WAIT_FOREVER);

        /* ����������ˮ��״̬��ʾ */
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

        /* ����ʱ����ʾ */
        meter_dis_time (kDisplay_on);

        AW_MUTEX_UNLOCK(disp_lock);

        GUI_Delay(500);
    }
}


/* �������� */
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

        /* �����ٶȱ��� */
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

        /* ����ת�ٱ��� */
        meter_dis_tachometer(rpm);

        /* ��������� */
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
    AW_TASK_INIT(__meter_task,                  /* ����ʵ�� */
                 "meter_task",                  /* �������� */
                 __METER_TASK_PRIO,             /* �������ȼ� */
                 __METER_TASK_STACK_SIZE,       /* �����ջ��С */
                 __meter_task_entry,            /* ������ں��� */
                 NULL);                         /* ������ڲ��� */

    /* �������� */
    AW_TASK_STARTUP(__meter_task);
}

/* end of file */
