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
 * \brief MiniPort ZLG72128 ����
 *
 * - �������裺
 *   1. �� aw_prj_params.h ͷ�ļ���ʹ��
 *     - AW_DEV_MINIPORT_ZLG72128
 *     - ����ƽ̨��I2C�豸��(��ZLG72128���ӵ�I2C�豸)
 *   2. ����Ӳ�������޸� awbl_hwconf_xxxxx_i2c0.h �ļ��ڵ�������ã�
 *   3. ����������鿴 awbl_hwconf_miniport_zlg72128.h��
 *   4. �� PACK ����װ����ӣ�Ȼ�� MiniPort ZLG72128 ����
 *      PACK ��� MiniPort �ӿ����ӡ�
 *
 * - ʵ������
 *   1. ����һ����������λ�������ʾ������ŵĶ����ƣ�
 *   2. ż�����ʱ���������˸���������ʱ������ܲ���˸��
 *
 * \par Դ����
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

#define    __DIGITRON_DISP_ID    0    /**< \brief �������ʾ�� ID */

/**
 * \brief �����¼�������
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

        /* ��ʾ 00 */
        if (p_key_data->key_state != 0) {
            aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 0, TRUE);
            aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 1, TRUE);
            aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 0, '0');
            aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 1, '0');
        }
        break;

    case KEY_1:

        /* ��ʾ 01 */
        if (p_key_data->key_state != 0) {
            aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 0, FALSE);
            aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 1, FALSE);
            aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 0, '0');
            aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 1, '1');
        }
        break;

    case KEY_2:

        /* ��ʾ 10 */
        if (p_key_data->key_state != 0) {
            aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 0, TRUE);
            aw_digitron_disp_blink_set(__DIGITRON_DISP_ID, 1, TRUE);
            aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 0, '1');
            aw_digitron_disp_char_at(__DIGITRON_DISP_ID, 1, '0');
        }
        break;

    case KEY_3:

        /* ��ʾ 11 */
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
 * \param ��
 *
 * \return ��
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
