/*******************************************************************************
*                                  AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn
* e-mail:      support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief MiniPort ZLG72128 例程
 *
 * - 操作步骤：
 *   1. 在 aw_prj_params.h 头文件里使能
 *     - AW_DEV_MINIPORT_ZLG72128
 *     - 对用平台的I2C设备宏(和ZLG72128连接的I2C设备)
 *   2. 根据硬件连接修改 awbl_hwconf_xxxxx_i2c0.h 文件内的相关配置；
 *   3. 具体配置需查看 awbl_hwconf_miniport_zlg72128.h；
 *   4. 将 PACK 板与底板连接，然后将 MiniPort ZLG72128 板与
 *      PACK 板的 MiniPort 接口连接。
 *
 * - 实验现象：
 *   1. 按下一个按键，两位数码管显示按键编号的二进制；
 *   2. 偶数编号时，数码管闪烁，奇数编号时，数码管不闪烁。
 *
 * \par 源代码
 * \snippet demo_miniport_zlg72128.c src_miniport_zlg72128
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-28 pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_zlg72128
 * \copydoc demo_miniport_zlg72128.c
 */

/** [src_miniport_zlg72128] */
#include "aworks.h"
#include "aw_task.h"
#include "aw_digitron_disp.h"
#include "aw_delay.h"
#include "aw_input.h"
#include "aw_job_queue.h"
#include "aw_vdebug.h"

#define    __DIGITRON_DISP_ID    0    /**< \brief 数码管显示器 ID */

/**
 * \brief 按键事件处理函数
 */
aw_local void __input_key_proc (aw_input_event_t *p_input_data, void *p_usr_data)
{
    struct aw_input_event    *p_input_ev = NULL;
    struct aw_input_key_data *p_key_data = NULL;
    struct aw_input_ptr_data *p_ptr_data = NULL;

    p_input_ev = p_input_data;
    p_key_data = (struct aw_input_key_data *)p_input_data;
    p_ptr_data = (struct aw_input_ptr_data *)p_input_data;

    if ((AW_INPUT_EV_KEY != p_input_ev->ev_type) && (AW_INPUT_EV_ABS != p_input_ev->ev_type)) {
        return;
    }

    switch (p_key_data->key_code) {

    case KEY_0:

        /* 显示 00 */
        if (p_key_data->key_state != 0) {
            aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 0, TRUE);
            aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 1, TRUE);
            aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 0, '0');
            aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 1, '0');
        }
        break;

    case KEY_1:

        /* 显示 01 */
        if (p_key_data->key_state != 0) {
            aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 0, FALSE);
            aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 1, FALSE);
            aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 0, '0');
            aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 1, '1');
        }
        break;

    case KEY_2:

        /* 显示 10 */
        if (p_key_data->key_state != 0) {
            aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 0, TRUE);
            aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 1, TRUE);
            aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 0, '1');
            aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 1, '0');
        }
        break;

    case KEY_3:

        /* 显示 11 */
        if (p_key_data->key_state != 0) {
            aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 0, FALSE);
            aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 1, FALSE);
            aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 0, '1');
            aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 1, '1');
        }
        break;

    default:
        break;
    }
}

/**
 * \brief MiniPort ZLG72128 Demo
 *
 * \param 无
 *
 * \return 无
 */
void demo_miniport_zlg72128_entry (void)
{
    int i   = 0;
    int num = 0;

    aw_local struct aw_input_handler input_handler;

    aw_input_handler_register(&input_handler, __input_key_proc, NULL);

    aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 0, '0');
    aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 1, '0');

    aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 0, TRUE);
    aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 1, TRUE);

}

/** [src_miniport_zlg72128] */

/* end of file */
