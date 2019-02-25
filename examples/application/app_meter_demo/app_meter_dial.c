#include "app_meter.h"


/**
 * \brief 表盘指针形状定义
 */
static const GUI_POINT __g_needle[] = {
    { -3,  -48},
    { 0,   -70},
    { 3,   -48},
};


/**
 * \brief 表盘指针信息结构体
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
 * \brief 速度表盘指针和数值绘制
 */
static void __speed_needle_draw(void *p_arg)
{
    char buf[4] = {0};
    needle_param_t * p_param = (needle_param_t *)p_arg;
    
    /* 绘制背景 */
    if (p_param->AutoDevInfo.DrawFixed) {
        GUI_MEMDEV_Write(p_param->hMemBk );
    }
    
    /* 绘制指针 */
    GUI_SetColor(GUI_RED);
    GUI_AA_FillPolygon(p_param->aPoints, GUI_COUNTOF(__g_needle), 118, 197);
    
    /* 数值显示 */
    if (p_param->AutoDevInfo.DrawFixed) {
        GUI_SetFont(&GUI_FontD36x48);
        GUI_SetTextMode(GUI_TM_TRANS);  
        GUI_SetColor(GUI_CYAN);
        sprintf(buf,"%d", p_param->data);
        GUI_DispStringHCenterAt(buf, 118, 174 );
    }  
}


/**
 * \brief 显示速度表盘
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
    
    /* 旋转指针到目标角度 */
    GUI_RotatePolygon(speed_needle.aPoints,  __g_needle, GUI_COUNTOF(__g_needle), speed_needle.angle);

    /* 创建自动设备对象 */
    GUI_MEMDEV_CreateAuto(&AutoDev); 
    
    /* 使用自动设备对象进行绘制 */
    GUI_MEMDEV_DrawAuto(&AutoDev, &speed_needle.AutoDevInfo, &__speed_needle_draw, &speed_needle);  
    
    /* 删除自动设备对象 */
    GUI_MEMDEV_DeleteAuto(&AutoDev);
}


/******************************************************************************/

/**
 * \brief 转速表盘指针和数值绘制
 */
static void __rpm_needle_draw (void *p_arg)
{
    char buf[4] = {0};
    
    needle_param_t * p_param = (needle_param_t *)p_arg;
    
    /* 绘制背景 */
    if (p_param->AutoDevInfo.DrawFixed) {
        GUI_MEMDEV_Write(p_param->hMemBk );
    }
    
    /* 绘制指针 */
    GUI_SetColor(GUI_RED);
    GUI_AA_FillPolygon(p_param->aPoints, GUI_COUNTOF(__g_needle), 682, 198);
    
    /* 数值显示 */
    if (p_param->AutoDevInfo.DrawFixed) {
        GUI_SetFont(&GUI_FontD36x48);
        GUI_SetTextMode(GUI_TM_TRANS);  
        GUI_SetColor(GUI_CYAN);
        sprintf(buf,"%d", p_param->data);
        GUI_DispStringHCenterAt(buf, 685, 174 );
    }  
}


/**
 * \brief 显示转速表盘
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
    
    /* 旋转指针到目标角度 */
    GUI_RotatePolygon(rpm_needle.aPoints,  __g_needle, GUI_COUNTOF(__g_needle), rpm_needle.angle);

    /* 创建自动设备对象 */
    GUI_MEMDEV_CreateAuto(&AutoDev); 
    
    /* 使用自动设备对象进行绘制 */
    GUI_MEMDEV_DrawAuto(&AutoDev, &rpm_needle.AutoDevInfo, &__rpm_needle_draw, &rpm_needle);  


    /* 删除自动设备对象 */
    GUI_MEMDEV_DeleteAuto(&AutoDev);
}


/**
 * \brief 显示总里程数
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

    /* 清除背景 */
    GUI_SetColor(0xb0b0b);
    GUI_FillRect(332 , 428, 332 + 135 , 428 + 25);
    
    /* 显示数值 */
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
 * \brief 存储速度表盘的背景
 */
void save_speedometer_bk (void)
{
    speed_needle.hMemBk = GUI_MEMDEV_CreateFixed(45, 125, 148, 112,
                                                 GUI_MEMDEV_HASTRANS,
                                                 GUI_MEMDEV_APILIST_32,
                                                 GUI_COLOR_CONV_8888);

    /* 将屏幕数据拷贝到存储设备 */
    GUI_MEMDEV_CopyFromLCD(speed_needle.hMemBk);
}



/**
 * \brief 存储转速表盘的背景
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
