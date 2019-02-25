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
 * \brief emwin����
 *
 * - �������裺
 *   1. ��Ҫ��aw_prj_params.hͷ�ļ���ʹ��
 *      - AW_COM_CONSOLE
 *      - ��Ӧƽ̨�Ĵ��ں�
 *      - ��Ӧ��ʾ���ĺ�
 *
 * - ʵ������
 *   1. ��ʾ������ɫΪ��ɫ;
 *   2. ������ɫ100*100������������Ļ���ƶ���
 *
 * \par Դ����
 * \snippet demo_emwin.c src_emwin
 *
 * \internal
 * \par Modification history
 * - 1.00 18-06-27  lqy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_emwin
 * \copydoc demo_emwin.c
 */

/** [src_emwin] */
#include "aworks.h"
#include "GUI.h"
#include "aw_delay.h"
#include "string.h"
#include "aw_vdebug.h"

/**
 * \brief emwin �������
 * \return ��
 */
aw_err_t demo_emwin_entry (void)
{
    int x_size, y_size;
    int x = 0, y = 0;
    const int rect_len = 100;   /* �����α߳� */
    int stage = 0;

    aw_kprintf("demo_emwin...\n");

    GUI_Init();

    x_size = LCD_GetXSize();
    y_size = LCD_GetYSize();
    while (1) {
        GUI_SetColor(0x00ff0000);

        switch (stage) {
        case 0:
            x++;
            if (x == x_size - rect_len - 1) {
                stage++;
            }
            break;

        case 1:
            y++;
            if (y == y_size - rect_len - 1) {
                stage++;
            }
            break;

        case 2:
            x--;
            if (x == 0) {
                stage++;
            }
            break;

        case 3:
            y--;
            if (y == 0) {
                stage = 0;
            }
        }

        GUI_MULTIBUF_Begin();
        GUI_SetColor(0x0000FF00);

        /* ��䱳��  */
        GUI_FillRect(0 , 0 , x_size - 1, y_size - 1);
        GUI_SetColor(0x00ff0000);

        /* �ػ�  */
        GUI_FillRect(x, y, 100 + x, 100 + y);
        GUI_MULTIBUF_End();
    }

    return AW_OK;
}

/** [src_emwin] */

/* end of file */
