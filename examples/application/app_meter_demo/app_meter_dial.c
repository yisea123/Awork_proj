#include "app_meter.h"


/**
 * \brief ����ָ����״����
 */
static const GUI_POINT __g_needle[] = {
    { -3,  -48},
    { 0,   -70},
    { 3,   -48},
};


/**
 * \brief ����ָ����Ϣ�ṹ��
 */
typedef struct {
    
    GUI_AUTODEV_INFO  AutoDevInfo;     /* Information about what has to be displayed */
    GUI_POINT         aPoints[GUI_COUNTOF(__g_needle)];   /* Polygon data */
    GUI_MEMDEV_Handle hMemBk;
    float             angle;
    int               data; 
} needle_param_t;


needle_param_t  speed_needle;
needle_param_t  rpm_needle;


/**
 * \brief �ٶȱ���ָ�����ֵ����
 */
static void __speed_needle_draw(void *p_arg)
{
    char buf[4] = {0};
    needle_param_t * p_param = (needle_param_t *)p_arg;
    
    /* ���Ʊ��� */
    if (p_param->AutoDevInfo.DrawFixed) {
        GUI_MEMDEV_Write(p_param->hMemBk );
    }
    
    /* ����ָ�� */
    GUI_SetColor(GUI_RED);
    GUI_AA_FillPolygon(p_param->aPoints, GUI_COUNTOF(__g_needle), 118, 197);
    
    /* ��ֵ��ʾ */
    if (p_param->AutoDevInfo.DrawFixed) {
        GUI_SetFont(&GUI_FontD36x48);
        GUI_SetTextMode(GUI_TM_TRANS);  
        GUI_SetColor(GUI_CYAN);
        sprintf(buf,"%d", p_param->data);
        GUI_DispStringHCenterAt(buf, 118, 174 );
    }  
}


/**
 * \brief ��ʾ�ٶȱ���
 */
void  meter_dis_speedometer (int speed)
{
    GUI_AUTODEV AutoDev;  
    
    if (speed <= 0) {
        speed = 0;
    } else if (speed >= SPEED_MAX) {
        speed = SPEED_MAX;
    }
    
    speed_needle.angle = 120 - speed * 6;
    speed_needle.angle *= 3.1415926f / 180.0;
    speed_needle.data = speed;
    
    /* ��תָ�뵽Ŀ��Ƕ� */
    GUI_RotatePolygon(speed_needle.aPoints,  __g_needle, GUI_COUNTOF(__g_needle), speed_needle.angle);

    /* �����Զ��豸���� */
    GUI_MEMDEV_CreateAuto(&AutoDev); 
    
    /* ʹ���Զ��豸������л��� */
    GUI_MEMDEV_DrawAuto(&AutoDev, &speed_needle.AutoDevInfo, &__speed_needle_draw, &speed_needle);  
    
    /* ɾ���Զ��豸���� */
    GUI_MEMDEV_DeleteAuto(&AutoDev);
}


/******************************************************************************/

/**
 * \brief ת�ٱ���ָ�����ֵ����
 */
static void __rpm_needle_draw (void *p_arg)
{
    char buf[4] = {0};
    
    needle_param_t * p_param = (needle_param_t *)p_arg;
    
    /* ���Ʊ��� */
    if (p_param->AutoDevInfo.DrawFixed) {
        GUI_MEMDEV_Write(p_param->hMemBk );
    }
    
    /* ����ָ�� */
    GUI_SetColor(GUI_RED);
    GUI_AA_FillPolygon(p_param->aPoints, GUI_COUNTOF(__g_needle), 682, 198);
    
    /* ��ֵ��ʾ */
    if (p_param->AutoDevInfo.DrawFixed) {
        GUI_SetFont(&GUI_FontD36x48);
        GUI_SetTextMode(GUI_TM_TRANS);  
        GUI_SetColor(GUI_CYAN);
        sprintf(buf,"%d", p_param->data);
        GUI_DispStringHCenterAt(buf, 685, 174 );
    }  
}


/**
 * \brief ��ʾת�ٱ���
 */
void  meter_dis_tachometer (int rpm)
{
    GUI_AUTODEV AutoDev;  
    
    if (rpm <= 0) {
        rpm = 0;
    } else if (rpm >= RPM_MAX) {
        rpm = RPM_MAX;
    }
    
    rpm_needle.angle = 120 - rpm * 0.06;
    rpm_needle.angle *= 3.1415926f / 180.0;
    
    if (rpm < 1000) {
        rpm_needle.data = 0;
    } else if (rpm < 2000) {
        rpm_needle.data = 1;
    } else if (rpm < 3000) {
        rpm_needle.data = 2;
    } else if (rpm < 4000) {
        rpm_needle.data = 3;
    } else {
        rpm_needle.data = 4;
    }
    
    /* ��תָ�뵽Ŀ��Ƕ� */
    GUI_RotatePolygon(rpm_needle.aPoints,  __g_needle, GUI_COUNTOF(__g_needle), rpm_needle.angle);

    /* �����Զ��豸���� */
    GUI_MEMDEV_CreateAuto(&AutoDev); 
    
    /* ʹ���Զ��豸������л��� */
    GUI_MEMDEV_DrawAuto(&AutoDev, &rpm_needle.AutoDevInfo, &__rpm_needle_draw, &rpm_needle);  


    /* ɾ���Զ��豸���� */
    GUI_MEMDEV_DeleteAuto(&AutoDev);
}


/**
 * \brief ��ʾ�������
 */
void meter_dis_kilometer (uint32_t km)
{
    GUI_MEMDEV_Handle h_mem;

    char buf[10] = {0};
    if (km >= KM_MAX) {
        km = KM_MAX;
    }
    
    h_mem = GUI_MEMDEV_CreateEx(332, 428, 135, 25, GUI_MEMDEV_NOTRANS);
    GUI_MEMDEV_Select(h_mem);

    /* ������� */
    GUI_SetColor(0xb0b0b);
    GUI_FillRect(332 , 428, 332 + 135 , 428 + 25);
    
    /* ��ʾ��ֵ */
    GUI_SetFont(&GUI_Font32B_ASCII);
    GUI_SetTextMode(GUI_TM_TRANS);  
    GUI_SetColor(GUI_CYAN);
    sprintf(buf,"%d", (int)km);
    GUI_DispStringHCenterAt(buf, 400, 426 ); 

    GUI_MEMDEV_Select(0);
    GUI_MEMDEV_WriteAt(h_mem, 332, 428);
    GUI_MEMDEV_Delete(h_mem);
}



/**
 * \brief �洢�ٶȱ��̵ı���
 */
void save_speedometer_bk (void)
{
    speed_needle.hMemBk = GUI_MEMDEV_CreateFixed(45, 125, 148, 112,
                                                 GUI_MEMDEV_HASTRANS,
                                                 GUI_MEMDEV_APILIST_32,
                                                 GUI_COLOR_CONV_8888);

    /* ����Ļ���ݿ������洢�豸 */
    GUI_MEMDEV_CopyFromLCD(speed_needle.hMemBk);
}



/**
 * \brief �洢ת�ٱ��̵ı���
 */
void save_tachometer_bk (void)
{  
    rpm_needle.hMemBk = GUI_MEMDEV_CreateFixed(610, 125, 148, 112,
                                               GUI_MEMDEV_HASTRANS,
                                               GUI_MEMDEV_APILIST_32,
                                               GUI_COLOR_CONV_8888);
   
    GUI_MEMDEV_CopyFromLCD(rpm_needle.hMemBk);
}

/* end of file */
