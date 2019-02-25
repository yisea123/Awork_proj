/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief �ⲿʹ�õ������ļ�
 *
 * �û��ڴ��ļ��жԴ���ģ�����ز�����������
 *
 * \internal
 * \par modification history:
 * - 1.00 12-10-31  orz, first implementation
 * \endinternal
 */

#ifndef __AWBL_SERIAL_USRCFG_H
#define __AWBL_SERIAL_USRCFG_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \brief ϵͳ���ж˿ڸ���
 *
 * ��ǰ֧�ֵ����˿ڸ���Ϊ10����Ӧ�ø���ʵ�ʵ�Ӳ�������޸ġ�
 * ���õĶ˿ڸ�����Ӧ�ó���10����
 */
#define AW_NUM_COM      		2

/**
 * \name ���ж˿ڵ��շ������С����
 * \brief ���õĴ��ж˿ڣ���ų���AW_NUM_COM�������ò������á�
 * @{
 */

#define AW_COM0_TX_BUF_SIZE     128 /**< \brief COM0 ���ͻ����С */
#define AW_COM0_RX_BUF_SIZE     128 /**< \brief COM0 ���ջ����С */

#define AW_COM1_TX_BUF_SIZE     128 /**< \brief COM1 ���ͻ����С */
#define AW_COM1_RX_BUF_SIZE     128 /**< \brief COM1 ���ջ����С */

#define AW_COM2_TX_BUF_SIZE     128 /**< \brief COM2 ���ͻ����С */
#define AW_COM2_RX_BUF_SIZE     128 /**< \brief COM2 ���ջ����С */

#define AW_COM3_TX_BUF_SIZE     128 /**< \brief COM3 ���ͻ����С */
#define AW_COM3_RX_BUF_SIZE     128 /**< \brief COM3 ���ջ����С */

#define AW_COM4_TX_BUF_SIZE     128 /**< \brief COM4 ���ͻ����С */
#define AW_COM4_RX_BUF_SIZE     128 /**< \brief COM4 ���ջ����С */

#define AW_COM5_TX_BUF_SIZE     128 /**< \brief COM5 ���ͻ����С */
#define AW_COM5_RX_BUF_SIZE     128 /**< \brief COM5 ���ջ����С */

#define AW_COM6_TX_BUF_SIZE     128 /**< \brief COM6 ���ͻ����С */
#define AW_COM6_RX_BUF_SIZE     128 /**< \brief COM6 ���ջ����С */

#define AW_COM7_TX_BUF_SIZE     128 /**< \brief COM7 ���ͻ����С */
#define AW_COM7_RX_BUF_SIZE     128 /**< \brief COM7 ���ջ����С */

#define AW_COM8_TX_BUF_SIZE     128 /**< \brief COM8 ���ͻ����С */
#define AW_COM8_RX_BUF_SIZE     128 /**< \brief COM8 ���ջ����С */

#define AW_COM9_TX_BUF_SIZE     128 /**< \brief COM9 ���ͻ����С */
#define AW_COM9_RX_BUF_SIZE     128 /**< \brief COM9 ���ջ����С */

/** @} */

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AWBL_SERIAL_USRCFG_H */

/* end of file */
