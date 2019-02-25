#ifndef __APP_METER_H
#define __APP_METER_H

#include "stdint.h"
#include "res/include_res.h"
#include "GUI.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"


/**
 * \brief 工作状态
 */
typedef enum _work_state {
    
    kPower_on = 0,
    kPower_off
    
} work_state_t;


/**
 * \brief 显示状态
 */
typedef enum _dis_state {
    
    kDisplay_on = 0,
    kDisplay_off
    
} dis_state_t;



/**
 * \brief 车灯状态
 */
typedef enum _light_state {

    kLight_on = 0,
    kLight_off

} light_state_t;



/**
 * \brief 警告状态
 */
typedef enum _alarm_state {

    kAlarm_on = 0,
    kAlarm_off

} alarm_state_t;



#define SPEED_MAX   (40)         /**< \brief 表盘速度显示的最大值 */
#define RPM_MAX     (4000)       /**< \brief 表盘转速显示的最大值 */
#define KM_MAX      (999999999)  /**< \brief 总里程的最大值 */
#define OIL_MAX     (8)          /**< \brief 油量的最大值 */
#define TEMP_MAX    (8)          /**< \brief 水温的最大值 */


/******************************************************************************/


/**
 * \brief 仪表工作状态指示灯
 * \param[in] work_state 仪表工作状态
 *
 * \return  无
 */
void meter_dis_work_state (work_state_t work_state);


/**
 * \brief 左转灯指示
 * \param[in] light_state 车灯状态
 *
 * \return  无
 */
void meter_dis_leftlight (light_state_t light_state);


/**
 * \brief 行车灯指示
 * \param[in] light_state 车灯状态
 *
 * \return  无
 */
void meter_dis_frontlight (light_state_t light_state);


/**
 * \brief 近光灯指示
 * \param[in] light_state 车灯状态
 *
 * \return  无
 */
void meter_dis_headlightlow (light_state_t light_state);



/**
 * \brief 远光灯指示
 * \param[in] light_state 车灯状态
 *
 * \return  无
 */
void meter_dis_headlighthigh (light_state_t light_state);


/**
 * \brief 后雾灯指示
 * \param[in] light_state 车灯状态
 *
 * \return  无
 */
void meter_dis_foglightrear (light_state_t light_state);


/**
 * \brief 前雾灯指示
 * \param[in] light_state 车灯状态
 *
 * \return  无
 */
void meter_dis_foglightfont (light_state_t light_state);


/**
 * \brief 右转指示灯
 * \param[in] light_state 车灯状态
 *
 * \return  无
 */
void meter_dis_rightlight(light_state_t light_state);


/******************************************************************************/


/**
 * \brief 点火警告指示灯
 * \param[in] alarm_state 警告状态
 *
 * \return  无
 */
void meter_dis_battery (alarm_state_t alarm_state);


/**
 * \brief 发动机故障警告指示灯
 * \param[in] alarm_state 警告状态
 *
 * \return  无
 */
void meter_dis_engine (alarm_state_t alarm_state);


/**
 * \brief 机油压力警告指示灯
 * \param[in] alarm_state 警告状态
 *
 * \return  无
 */
void meter_dis_engineoil (alarm_state_t alarm_state);


/**
 * \brief 传动系统警告指示灯
 * \param[in] alarm_state 警告状态
 *
 * \return  无
 */
void meter_dis_fix (alarm_state_t alarm_state);


/**
 * \brief 制动系统警告指示灯
 * \param[in] alarm_state 警告状态
 *
 * \return  无
 */
void meter_dis_barke (alarm_state_t alarm_state);


/**
 * \brief 安全带警告指示灯
 * \param[in] alarm_state 警告状态
 *
 * \return  无
 */
void meter_dis_safebelt (alarm_state_t alarm_state);


/**
 * \brief 车门警告指示灯
 * \param[in] alarm_state 警告状态
 *
 * \return  无
 */
void meter_dis_cardoor (alarm_state_t alarm_state);



/******************************************************************************/


/**
 * \brief 显示速度表盘
 * \param[in] speed 速度值
 *
 * \return  无
 */
void  meter_dis_speedometer (int speed);

/**
 * \brief 显示转速表盘
 * \param[in] rpm 转速值
 *
 * \return  无
 */
void  meter_dis_tachometer (int rpm);


/**
 * \brief 存储速度表盘的背景
 * \param[in] 无
 *
 * \return    无
 */
void save_speedometer_bk (void);


/**
 * \brief 存储转速表盘的背景
 * \param[in] 无
 *
 * \return    无
 */
void save_tachometer_bk (void);


/******************************************************************************/


/**
 * \brief 显示总里程数
 * \param[in] km  行车的累计公里数
 *
 * \return    无
 */
void meter_dis_kilometer (uint32_t km);


/**
 * \brief 显示日期和时间信息
 * \param[in] dis_state  显示状态
 *
 * \return    无
 */
void meter_dis_time (dis_state_t dis_state);


/**
 * \brief 油量状态显示
 * \param[in] oil  油量
 *
 * \return    无
 */
void  meter_dis_oil (uint8_t oil);


/**
 * \brief 水温状态显示
 * \param[in] oil 水温
 *
 * \return    无
 */
void  meter_dis_water_temp (uint8_t temp);



#endif

/* end of file */
