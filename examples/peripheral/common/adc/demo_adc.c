/*******************************************************************************
*                                  AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn
* e-mail:      support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ADC读取采样电压例程(同步读取)
 *
 * - 操作步骤：
 *   1. 本例程需在aw_prj_params.h头文件里使能
 *      - 对应平台的 ADC1 宏
 *      - 对应平台的串口宏
 *      - AW_COM_CONSOLE
 * - 实验现象：
 *   1. 串口每隔500ms，打印出连续采样到的5个电压值。
 *
 * - 备注：
 *   1. 用户可在对应平台的 awbl_hwconf_xxxxxx_adc1.h 文件中中修改adc参数配置;
 *   2. 如果工程在初始化时出错，请查看此demo所使用GPIO是否存在引脚复用。
 *
 * \par 源代码
 * \snippet demo_adc.c src_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 16-03-23  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_adc
 * \copydoc demo_adc.c
 */

/** [src_adc] */
#include "aworks.h"
#include "aw_delay.h"
#include "aw_adc.h"
#include "aw_vdebug.h"
#include "string.h"

/* ADC通道号 */
#define ADC_CHANNEL    0

/* 进行5次采样 */
#define SAMPLES_NUM    5

/**
 * \brief ADC 同步读取电压值 demo
 * \return 无
 */
void demo_adc_entry (void)
{
    uint16_t adc_val[SAMPLES_NUM];
    uint32_t vol_val[SAMPLES_NUM];
    int      i;

    memset(adc_val, 0, sizeof(adc_val));

    while(1) {
    
        /* 读取通道的AD值 */
        aw_adc_sync_read(ADC_CHANNEL, adc_val, SAMPLES_NUM, FALSE);

        /* 转换为实际电压值 */
        aw_adc_val_to_mv(ADC_CHANNEL, adc_val, SAMPLES_NUM, vol_val);

        for (i = 0; i < SAMPLES_NUM; i++) {
            aw_kprintf(" %d conversion result : %dmV\n", i + 1, vol_val[i]);
        }
        aw_mdelay(500);
        aw_kprintf("\r\n");
    }
}

/** [src_adc] */
 
/* end of file */
