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
 * \brief CANopen�������ӻ������ļ�
 *
 * \internal
 * \par modification history:
 * - 1.00 18-05-31  anu, modify
 * - 1.00 15-11-16  cae, first implementation
 * \endinternal
 */

#ifndef __AW_COP_H
#define __AW_COP_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_cop
 * \copydoc aw_cop.h
 * @{
 */

#include "aw_types.h"

/**
 * \name CANopen ��Ϣ
 * \anchor grp_aw_cop_max_slaves
 * @{
 */

#define AW_COP_MAX_SLAVES         127    /**< \brief ���ӻ����� */

/** @} */

/**
 * \name CANopen �ڵ�
 * \anchor grp_aw_cop_node_id
 * @{
 */

#define AW_COP_NODE_ID_MAX        0x7F   /**< \brief ���ڵ�ID */
#define AW_COP_NODE_ID_INVAILD    0x00   /**< \brief ��Ч�ڵ�ID */
#define AW_COP_NODE_ID_ALL        0x00   /**< \brief ���нڵ�ID */

/** @} */

/**
 * \name CANopen ID
 * \anchor grp_aw_cop_id
 * @{
 */

#define AW_COP_ID_SYNC_CLEAR    0x80000080L /**< \brief ���ͬ������ID */
#define AW_COP_ID_TIME_STAMP    0x100       /**< \brief ʱ�������ID */
#define AW_COP_ID_SDO_SND       0x580       /**< \brief �������ݶ�����ID */
#define AW_COP_ID_SDO_RCV       0x600       /**< \brief �������ݶ�����ID */

/** @} */

/**
 * \name CANopen �������
 * \anchor grp_aw_cop_err_t
 * @{
 */

typedef int aw_cop_err_t;               /**< \brief �������                            */
#define AW_COP_ERR_NO_ERROR         0   /**< \brief û�д���                            */
#define AW_COP_ERR_LOADLIB          11  /**< \brief װ��DLLʧ��                      */
#define AW_COP_ERR_GETPROC          12  /**< \brief ��ȡ������ַʧ��             */
#define AW_COP_ERR_OPENED           13  /**< \brief �豸�Ѿ�����                 */
#define AW_COP_ERR_NOTEXIST         14  /**< \brief �豸������                         */
#define AW_COP_ERR_STARTDEV         15  /**< \brief ����CANopen�豸ʧ��       */
#define AW_COP_ERR_NOTOPEN          16  /**< \brief �豸û�д�                     */
#define AW_COP_ERR_INVALIDPARAM     17  /**< \brief ��Ч����                             */
#define AW_COP_ERR_INVALIDHANDLE    18  /**< \brief ��Ч���豸���                  */
#define AW_COP_ERR_CLOSEDEV         19  /**< \brief �޷��ر��豸                      */
#define AW_COP_ERR_INSTALLDRIVER    20  /**< \brief ������װ����ȷ                  */
#define AW_COP_ERR_BUFFERTOOSMALL   22  /**< \brief �洢�ռ�̫С                      */
#define AW_COP_ERR_INTERNAL         23  /**< \brief δ֪�ڲ�����                      */
#define AW_COP_ERR_TIMEOUT          29  /**< \brief �ȴ���ʱ                              */
#define AW_COP_ERR_SLAVEEXIST       30  /**< \brief ��վ�Ѵ���                          */
#define AW_COP_ERR_SLAVENOTEXIST    31  /**< \brief ��վ������                          */
#define AW_COP_ERR_SLAVETABFUL      32  /**< \brief ��վע������                      */
#define AW_COP_ERR_SENDFAILED       33  /**< \brief ��������ʧ��                      */
#define AW_COP_ERR_NODATA           34  /**< \brief û������                             */
#define AW_COP_ERR_GETSTATUS        35  /**< \brief ��ȡ��վ״̬ʧ��              */
#define AW_COP_ERR_NOTIMPLEMENT     36  /**< \brief ����û��ʵ��                      */
#define AW_COP_ERR_NOTSTARTED       37  /**< \brief δ����CANopen          */
#define AW_COP_ERR_SDOABORT         38  /**< \brief SDO ������ֹ                      */
#define AW_COP_ERR_PDOTABFULL       39  /**< \brief PDO ע������                      */
#define AW_COP_ERR_PDONOTREGISTER   40  /**< \brief PDO δע��                          */
#define AW_COP_ERR_CHNLNOTINIT      41  /**< \brief δ��ʼ��ͨ������               */
#define AW_COP_ERR_QUEUECREATE      42  /**< \brief ��������ʧ��                       */

/** @} */

/** \brief CANopen PDO�������ݶ�����Ϣ */
typedef struct aw_cop_pdo_msg {

    uint8_t  node_id;          /**< \brief ��վ��ַ          */
    uint32_t pdo_id;           /**< \brief PDO����            */
    uint8_t  pdo_len;          /**< \brief PDO���ݳ���    */
    uint8_t  pdo_data[8];      /**< \brief PDO����            */

} aw_cop_pdo_msg_t;

/** \brief CANopen ������������ */
typedef struct aw_cop_emcy_msg {

    uint8_t  node_id;          /**< \brief ��վ��ַ                           */
    uint16_t err_code;         /**< \brief �����������                    */
    uint8_t  err_reg_code;     /**< \brief ��ǰ����Ĵ���ֵ            */
    uint8_t  err_specific[5];  /**< \brief �Զ���������                */

} aw_cop_emcy_msg_t;

/** \brief CANopen ʱ�� */
typedef struct aw_cop_time {

    uint16_t year;             /**< \brief ��     */
    uint8_t  month;            /**< \brief ��     */
    uint8_t  day;              /**< \brief ��     */
    uint8_t  hour;             /**< \brief Сʱ */
    uint8_t  minute;           /**< \brief ���� */
    uint8_t  second;           /**< \brief ��     */
    uint16_t millisecond;      /**< \brief ����  */

} aw_cop_time_t;

/** @} grp_aw_if_cop */

#ifdef __cplusplus
}
#endif

#endif /* __AW_COP_H */

/* end of file */
