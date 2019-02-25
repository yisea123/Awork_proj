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
 * \brief Modbus�û������ļ�
 *
 * \internal
 * \par modification history
 * - 1.02 2015-05-13  cod, Modify for aworks1.0, fix code style
 * - 1.01 2012-12-04  liuweiyun, Modify for aworks1.0, fix code style
 * - 1.00 2012-05-13  ygy, first implementation
 * \endinternal
 */

#ifndef __AW_MB_CONFIG_H /* { */
#define __AW_MB_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_mb_config
 * \copydoc aw_mb_config.h
 * @{
 */

/** \note ���ļ���������ΪĬ�����ã����ɿ��ֱ���޸ĺ궨����Ч */

/** \brief �ӻ�ͨ��ģʽ���� */
#define AW_MB_SERIAL_RTU_ENABLE    1   /**< \brief ����RTUģʽ */
#define AW_MB_SERIAL_ASCII_ENABLE  1   /**< \brief ����ASCIIģʽ */
#define AW_MB_TCP_ENABLE           1   /**< \brief TCP/IPģʽ */

/** \brief ��վͨ��ģʽ���� */
#define AW_MB_MASTER_RTU_ENABLE    1   /**< \brief ����RTUģʽ */
#define AW_MB_MASTER_ASCII_ENABLE  1   /**< \brief ����ASCIIģʽ */
#define AW_MB_MASTER_TCP_ENABLE    1   /**< \brief TCP/IPģʽ */

/**
 * \brief �������ADU����
 * - �ó��Ȱ����ӻ���ַ�ͼ������ݳ���
 * - ����ĳЩӦ�ã����ܲ���Ҫ�ܳ���һ֡���ݣ����Կ����ʵ������Խ���RAMʹ��
 * - RTUģʽ����Ϊ4~256�� ASCIIģʽ����Ϊ3~255
 */
#define AW_MB_MAX_SER_PDU_LENGTH   256

/**
 * \brief ʹ�ܽ���˫���壨RTU��ASCIIģʽ��
 * ���ʹ�ܸ����ã���ʹ��2*AW_MB_MAX_SER_PDU_LENGTH RAM�ռ���������PDU����֡��
 * ʹ�øù��ܣ����Ա�֤�ڵ�һ֡����ʱ����һ֡���ݵ���ʱ����֤�ڶ�֡����������
 */
#define AW_MB_SER_PDU_RECV_BUF_ENABLE  1

/**
 * \brief TCPģʽ�����ADU����
 * - ����ĳЩӦ�ã����ܲ���Ҫ�ܳ���һ֡���ݣ����Կ����ʵ������Խ���RAMʹ��
 */
#define AW_MB_MAX_TCP_ADU_LENGTH   263

/**
 * \brief RTUģʽT3.5ʱ�����ã���λ��΢�룩
 * - ��RTUģʽ�У������Ŷ�t3.5��֡���ӳ�ʱ�䣩����Ĵ����жϵĴ���
 *   �ڽϸߵ�ͨ�Ų������£��⽫����CPU�������أ�
 *   ��˵�������С�ڻ����19200λ/�������£������ϸ�������������ʱ
 * - ���������ʴ���19200λ/��ʱ��Ӧ��ʹ�ù̶�ֵ������֡���ӳ�ʱ������Ϊ1.750ms
 * - ��ʹ��ASCIIģʽʱ������Ҫ�Ըú��������
 */
#define AW_MB_SERIAL_RTU_BAUDRATE_OVER_19200_FRAME_DELAY_US    1750ul

/**
 * \brief ASCIIģʽ�ַ��䳬ʱ����
 * ��ASCIIģʽ�У��ַ��䳬ʱʱ��û�й̶������Ը��ݾ�������������
 */
#define AW_MB_ASCII_TIMEOUT_SEC    1

/**
 * \brief �û�����չע�������������
 * ����ʹ��aw_mb_slave_register_handler������ע�Ṧ�����������ʱ����ע��������
 */
#define AW_MB_FUNC_CODE_HANDLER_MAX    4

/**
 * \brief ��վ�Ƿ�ʹ��Ӳ����ʱ��(Ĭ��ʹ�������ʱ��)
 */
#define AW_MB_SLAVE_USED_HW_TIMER   1

/**
 * \brief Ĭ�ϴ�վ���������������������Ĭ��������ʱ���ر����罨�������ӣ�
 */
#define AW_MB_SLAVE_TCP_CONNECT_NUM   4

/**
 * \brief ��վ�ȴ���վӦ��ʱʱ�䣨���룩
 */
#define AW_MB_MASTER_TIMEOUT_MS_RESPOND  2000
#if ((AW_MB_MASTER_TIMEOUT_MS_RESPOND < 50)  ||\
     (AW_MB_MASTER_TIMEOUT_MS_RESPOND > 100000))
#error "AW_MB_MASTER_TIMEOUT_MS_RESPOND value must be in 50~100000ms"
#endif

/**
 * \brief ��վ�㲥ʱ��ת���ӳ�ʱ�䣨���룩
 */
#define AW_MB_MASTER_DELAY_MS_CONVERT   100

/**
 * \brief ��վ�û�����չע�������������
 * ����ʹ��aw_mb_master_funcode_register������ע�Ṧ�����������ʱ����ע��������
 */
#define AW_MB_MASTER_FUNCODE_HANDLER_MAX  4

/**
 * \brief TCPģʽ�µ�Ԫ��ʾ��ʹ�ô�վ��ַʹ��
 * - ����ĳЩӦ�ã���Modbus���������ӵ�������·����ʹ�õ�Ԫ��ʾ��ʶ���վ��ַ
 * - ��ʹ�ܣ���Ԫ��ʾ������Ŀ���վ��ַʹ�ã�����ʹ�ܣ���Ԫ��ʾ��ֵĬ��Ϊ0xFF
 */
#define AW_MB_TCP_UID_AS_SLAVEADDR   0

/**
 * \brief ��վTCPģʽ�£�Ĭ�����ӳ�ʱʱ��(ms)
 */
#define AW_MB_TCP_CONNECT_TIMEOUT    5000

#ifdef __cplusplus
}
#endif

/** @} grp_aw_if_mb_config */

#endif /* } __AW_MB_CONFIG_H */

/* end of file */
