#ifndef __APP_METER_H
#define __APP_METER_H

#include "stdint.h"
#include "res/include_res.h"
#include "GUI.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"


/**
 * \brief ����״̬
 */
typedef enum _work_state {
    
    kPower_on = 0,
    kPower_off
    
} work_state_t;


/**
 * \brief ��ʾ״̬
 */
typedef enum _dis_state {
    
    kDisplay_on = 0,
    kDisplay_off
    
} dis_state_t;



/**
 * \brief ����״̬
 */
typedef enum _light_state {

    kLight_on = 0,
    kLight_off

} light_state_t;



/**
 * \brief ����״̬
 */
typedef enum _alarm_state {

    kAlarm_on = 0,
    kAlarm_off

} alarm_state_t;



#define SPEED_MAX   (40)         /**< \brief �����ٶ���ʾ�����ֵ */
#define RPM_MAX     (4000)       /**< \brief ����ת����ʾ�����ֵ */
#define KM_MAX      (999999999)  /**< \brief ����̵����ֵ */
#define OIL_MAX     (8)          /**< \brief ���������ֵ */
#define TEMP_MAX    (8)          /**< \brief ˮ�µ����ֵ */


/******************************************************************************/


/**
 * \brief �Ǳ���״ָ̬ʾ��
 * \param[in] work_state �Ǳ���״̬
 *
 * \return  ��
 */
void meter_dis_work_state (work_state_t work_state);


/**
 * \brief ��ת��ָʾ
 * \param[in] light_state ����״̬
 *
 * \return  ��
 */
void meter_dis_leftlight (light_state_t light_state);


/**
 * \brief �г���ָʾ
 * \param[in] light_state ����״̬
 *
 * \return  ��
 */
void meter_dis_frontlight (light_state_t light_state);


/**
 * \brief �����ָʾ
 * \param[in] light_state ����״̬
 *
 * \return  ��
 */
void meter_dis_headlightlow (light_state_t light_state);



/**
 * \brief Զ���ָʾ
 * \param[in] light_state ����״̬
 *
 * \return  ��
 */
void meter_dis_headlighthigh (light_state_t light_state);


/**
 * \brief �����ָʾ
 * \param[in] light_state ����״̬
 *
 * \return  ��
 */
void meter_dis_foglightrear (light_state_t light_state);


/**
 * \brief ǰ���ָʾ
 * \param[in] light_state ����״̬
 *
 * \return  ��
 */
void meter_dis_foglightfont (light_state_t light_state);


/**
 * \brief ��תָʾ��
 * \param[in] light_state ����״̬
 *
 * \return  ��
 */
void meter_dis_rightlight(light_state_t light_state);


/******************************************************************************/


/**
 * \brief ��𾯸�ָʾ��
 * \param[in] alarm_state ����״̬
 *
 * \return  ��
 */
void meter_dis_battery (alarm_state_t alarm_state);


/**
 * \brief ���������Ͼ���ָʾ��
 * \param[in] alarm_state ����״̬
 *
 * \return  ��
 */
void meter_dis_engine (alarm_state_t alarm_state);


/**
 * \brief ����ѹ������ָʾ��
 * \param[in] alarm_state ����״̬
 *
 * \return  ��
 */
void meter_dis_engineoil (alarm_state_t alarm_state);


/**
 * \brief ����ϵͳ����ָʾ��
 * \param[in] alarm_state ����״̬
 *
 * \return  ��
 */
void meter_dis_fix (alarm_state_t alarm_state);


/**
 * \brief �ƶ�ϵͳ����ָʾ��
 * \param[in] alarm_state ����״̬
 *
 * \return  ��
 */
void meter_dis_barke (alarm_state_t alarm_state);


/**
 * \brief ��ȫ������ָʾ��
 * \param[in] alarm_state ����״̬
 *
 * \return  ��
 */
void meter_dis_safebelt (alarm_state_t alarm_state);


/**
 * \brief ���ž���ָʾ��
 * \param[in] alarm_state ����״̬
 *
 * \return  ��
 */
void meter_dis_cardoor (alarm_state_t alarm_state);



/******************************************************************************/


/**
 * \brief ��ʾ�ٶȱ���
 * \param[in] speed �ٶ�ֵ
 *
 * \return  ��
 */
void  meter_dis_speedometer (int speed);

/**
 * \brief ��ʾת�ٱ���
 * \param[in] rpm ת��ֵ
 *
 * \return  ��
 */
void  meter_dis_tachometer (int rpm);


/**
 * \brief �洢�ٶȱ��̵ı���
 * \param[in] ��
 *
 * \return    ��
 */
void save_speedometer_bk (void);


/**
 * \brief �洢ת�ٱ��̵ı���
 * \param[in] ��
 *
 * \return    ��
 */
void save_tachometer_bk (void);


/******************************************************************************/


/**
 * \brief ��ʾ�������
 * \param[in] km  �г����ۼƹ�����
 *
 * \return    ��
 */
void meter_dis_kilometer (uint32_t km);


/**
 * \brief ��ʾ���ں�ʱ����Ϣ
 * \param[in] dis_state  ��ʾ״̬
 *
 * \return    ��
 */
void meter_dis_time (dis_state_t dis_state);


/**
 * \brief ����״̬��ʾ
 * \param[in] oil  ����
 *
 * \return    ��
 */
void  meter_dis_oil (uint8_t oil);


/**
 * \brief ˮ��״̬��ʾ
 * \param[in] oil ˮ��
 *
 * \return    ��
 */
void  meter_dis_water_temp (uint8_t temp);



#endif

/* end of file */
