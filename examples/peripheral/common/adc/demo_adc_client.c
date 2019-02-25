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
 * \brief ADC利用客户端获取采样电压例程
 *
 * 一般使用客户端是为了满足较为复杂的电压采样要求，用户可根据实际需求进行灵活的
 * 配置。
 *
 * - 操作步骤：
 *   1. 本例程需在aw_prj_params.h头文件里使能
 *      - 对应开发平台的ADC1宏.
 *      - 对应平台的串口宏
 *      - AW_COM_CONSOLE
 * - 实验现象：
 *   1. 串口每隔1s打印出当前采样序列的电压值。
 *
 * - 备注：
 *   1. 用户可在对应平台的 awbl_hwconf_xxxxxx_adc1.h 文件中中修改adc参数配置;
 *   2. 如果工程在初始化时出错，请查看此demo所使用GPIO是否存在引脚复用。
 *
 * \par 源代码
 * \snippet demo_adc_client.c src_adc_client
 *
 * \internal
 * \par Modification History
 * - 1.00 15-03-24  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_adc_client
 * \copydoc demo_adc_client.c
 */

/** [src_adc_client] */
#include "aworks.h"
#include "aw_delay.h"
#include "aw_adc.h"
#include "aw_vdebug.h"
#include "aw_msgq.h"

/* ADC通道号
 *
 * 说明："LRADC0", 0,
 *       "LRADC1", 1,
 *       "LRADC6", 6,
 *       "HSADC",  23,
 */
#define ADC_CHANNEL    0

#define SAMPLES_NUM    5            /* 进行5次采样  */
#define ADC_READ_CNT   20           /* 读取ADC数    */
/******************************************************************************/

/** adc complete data*/
struct adc_complete {
    int stat;    /**< \brief 转换结果  */
    int seq;     /**< \brief 转换序列  */
};
/******************************************************************************/
/* 消息队列   */
AW_MSGQ_DECL_STATIC(adc_msgq, 20, sizeof(struct adc_complete));

static uint16_t __adc_val0[ADC_READ_CNT];  /* adc接收缓冲区0   */
static uint16_t __adc_val1[ADC_READ_CNT];  /* adc接收缓冲区1   */
static uint32_t __vol_val[ADC_READ_CNT];   /* adc转换缓冲区  */

/******************************************************************************/
/**
 * \brief ADC转换完成回调
 * \param[in] p_arg : 任务参数
 * \param[in] stat  : 转换结果标志
 * \return 无
 */
static void __adc_complete_cb (void *p_arg, int stat)
{
    struct adc_complete msg = {stat, (int)p_arg};
    
    /* 发送一个消息 */
    AW_MSGQ_SEND(adc_msgq,
                 &msg,
                 sizeof(struct adc_complete),
                 AW_MSGQ_NO_WAIT,
                 AW_MSGQ_PRI_NORMAL);
}

/**
 * \brief ADC 客户端 demo
 * \return 无
 */
void demo_adc_client_entry (void)
{
    aw_adc_client_t     client;
    aw_adc_buf_desc_t   desc[2];
    struct adc_complete info;
    uint32_t            i;

    AW_MSGQ_INIT(adc_msgq, 20, sizeof(struct adc_complete), AW_SEM_Q_PRIORITY);

    /* ADC缓冲区描述符0 */
    aw_adc_mkbufdesc(&desc[0], __adc_val0, ADC_READ_CNT, __adc_complete_cb, (void *)0);

    /* ADC缓冲区描述符1*/
    aw_adc_mkbufdesc(&desc[1], __adc_val1, ADC_READ_CNT, __adc_complete_cb, (void *)1);

    /* 初始化ADC客户端 */
    aw_adc_client_init(&client, ADC_CHANNEL, FALSE);

    /* 持续转换 */
    aw_adc_client_start(&client, desc, 2, 0);
    
    while(1) {

        AW_MSGQ_RECEIVE(adc_msgq,
                        &info,
                        sizeof(struct adc_complete),
                        AW_MSGQ_WAIT_FOREVER);

        if (info.stat != AW_OK) {
            aw_kprintf("缓冲区 %d 转换出错！！！\r\n",info.seq);
        } else {

            if (info.seq == 0) {
                aw_kprintf("seq 0 complete!\r\n");
                aw_adc_val_to_mv(ADC_CHANNEL, __adc_val0, ADC_READ_CNT, __vol_val);
            }
            if (info.seq == 1) {
                aw_kprintf("seq 1 complete!\r\n");
                aw_adc_val_to_mv(ADC_CHANNEL, __adc_val1, ADC_READ_CNT, __vol_val);
            }

            for (i = 0; i < ADC_READ_CNT; i++) {
                aw_kprintf("%d conversion result : %dmV\n", i + 1, __vol_val[i]);
            }
        }

        aw_mdelay(1000);
    }
}

/** [src_adc_client] */
 
/* end of file */
