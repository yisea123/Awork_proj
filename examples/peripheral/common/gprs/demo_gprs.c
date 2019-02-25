/*******************************************************************************
*                                 AWorks
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
 * \brief GPRS���̣���������ʾGPRS�豸���Ͷ��ź�����ͨ�ŵĹ���
 *
 * - ��������:
 *   1. aw_prj_params.h ��ʹ�ܣ�
 *      - ��Ӧƽ̨��USBH��
 *      - ����Ӧƽ̨���ں�
 *      - AW_COM_CONSOLE
 *      - ��Ӧ��GPRS�豸��(���磺AW_DEV_GPRS_ME909S)
 *   2. ��GPRSģ����뿪�����USB HOST0�ӿڣ�
 *   3. �ڵ����ϴ� TCP&UDP ���������������������������
 *
 * - ʵ������:
 *   1. �ֻ��ͻ��˻��յ����ţ�Hello,i'm aworks��
 *   1. ���ڴ�ӡ�� GPRS�豸��������ĵ�����Ϣ���Լ�����˷��͵�������Ϣ��
 *   2. TCP&UDP ��������յ�GPRS�豸���͵����ݣ�
 *      ���ڴ�ӡTCP&UDP��λ�����͵����ݡ�
 *
 * - ��ע:
 *   1.ƽ̨֧�ֵ�GPRS�豸Ŀǰ��sim800,me909,u9300,��Ӧ�豸��������鿴��Ӧ�ĳ�ʼ���ļ�awbl_hwconf_gprs_xxxxx.h��
 * \code
 *
 * \endcode
 *
 * \par Դ����
 * \snippet demo_gprs.c src_gprs
 *
 * \internal
 * \par modification history:
 * - 1.00 18-07-12 lqy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_gprs
 * \copydoc demo_gprs.c
 */

/** [src_gprs] */

#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_gprs.h"
#include <string.h>
#include "aw_delay.h"

/* gprs�豸id��ţ��û�����ݾ���gprs�豸���� awbl_hwconf_gprs_xxxxx.h�����ļ��в���id�� */
#define TEST_GPRS_DEV                   2

/* ʹ��TCPЭ���������� */
#define TEST_GPRS_MODE                  "TCP"

/*���ʵķ�����IP���û�����ݾ�������޸�*/
#define TEST_SERVER_IP                  "121.33.243.38"

/*���ʵķ������˿ڣ��û�����ݾ�������޸�*/
#define TEST_SEEVER_PORT                51237

/*socket����������0��ʼ*/
#define TEST_SCOKET_HD                  0

/* ����ʹ���ֻ��ţ��û����޸�, */
#define TEST_PHONE_NUM                  "+8618529453675"

/*
 * \brief GPRS ����ͨ���������
 * \return ��
 */
void demo_gprs_entry(void)
{
    aw_err_t ret = AW_ERROR;
    uint8_t p_buf[1000];

    /**
     * /brief gprs�豸�ϵ粢��ʼ��
     * id 0 - u9300c �豸
     * id 1 - sim800 �豸
     * id 2 - me909 �豸
     * ����id������ awbl_hwconf_gprs_xxxxx.h�����ļ��в���
     * note �û�����ݾ���gprs�豸��ʹ�ö�Ӧ��ID
     */
    ret = aw_gprs_power_on(TEST_GPRS_DEV);
    if(ret != AW_OK){
        aw_kprintf("aw_gprs_power_on error:%d\r\n",ret);
        return ;
    }

    /*���Ͷ���*/
    ret = aw_gprs_sms_send(TEST_GPRS_DEV,"Hello,i'm aworks!",17,TEST_PHONE_NUM);
    if(ret != AW_OK){
        aw_kprintf("aw_gprs_sms_send error:%d\r\n",ret);
        goto exit;
    }

    /* ����GPRS���� */
    ret = aw_gprs_start(TEST_GPRS_DEV,TEST_GPRS_MODE,TEST_SERVER_IP,TEST_SEEVER_PORT,3000);
    if(ret < AW_OK){
        aw_kprintf("aw_gprs_start error:%d\r\n",ret);
        goto exit;
    }

    while(1){
        /*��ջ�����*/
        memset(p_buf,'\0',sizeof(p_buf));
        /*���շ������˷��͵����ݣ�������*/
        ret = aw_gprs_recv(TEST_GPRS_DEV,TEST_SCOKET_HD,p_buf,sizeof(p_buf));
        if(ret > 0){
            aw_kprintf("recv:%s\r\n",p_buf);
        }

        /*��������˷�������*/
        aw_gprs_send(TEST_GPRS_DEV,TEST_SCOKET_HD,"Hello i'm aworks!\r\n",19,100);
        aw_mdelay(1000);
    }

exit:
    /*�ر�gprs����*/
    aw_gprs_close(TEST_GPRS_DEV,TEST_SCOKET_HD);
    /*�ر�gprs�豸*/
    aw_gprs_power_off(TEST_GPRS_DEV);

    return ;
}

/** [src_gprs] */

/* end of file */
