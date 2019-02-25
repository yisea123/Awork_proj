/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief �̵��������ӿ�
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ�
 * \code
 * #include "aw_relay.h"
 * \endcode
 * 
 * \par ʹ��ʾ��
 * \code
 * #include "aw_relay.h"
 *
 * aw_relay_on(RELAY1);      // �̵���1�պ�
 * aw_relay_off(RELAY1);     // �̵���1�Ͽ�
 * \endcode
 *
 * \internal
 * \par modification history
 * - 1.00 14-07-30  hbt, first implementation.
 * \endinternal
 */

#ifndef __AW_RELAY_H
#define __AW_RELAY_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_relay
 * \copydoc aw_relay.h
 * @{
 */

#include "aw_types.h"


/**
 * \brief �̵����պ�
 * \param id   �̵�����ţ����ñ���ɾ���ƽ̨����
 */
void aw_relay_on (unsigned int id);

/**
 * \brief �̵����Ͽ�
 * \param id   �̵�����ţ����ñ���ɾ���ƽ̨����
 */
void aw_relay_off (unsigned int id);

/** @} grp_aw_if_relay */

#ifdef __cplusplus
}
#endif

#endif /* __AW_RELAY_H */

/* end of file */
