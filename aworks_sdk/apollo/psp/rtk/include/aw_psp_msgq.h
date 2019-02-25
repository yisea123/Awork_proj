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
 * \brief AWorks1.0 消息队列平台相关标准定义头文件
 *
 * \internal
 * \par modification history:
 * - 1.10 15-09-15  dcf, 变更msgq, memcpy不关中断
 * - 1.10 13-03-06  zen, first implementation
 * \endinternal
 */

#ifndef __AW_PSP_MSGQ_H
#define __AW_PSP_MSGQ_H

#include "rtk.h"
#include "aw_types.h"
#include "aw_compiler.h"

/******************************************************************************/
#define AW_PSP_MSGQ_WAIT_FOREVER        WAIT_FOREVER
#define AW_PSP_MSGQ_NO_WAIT             0

/******************************************************************************/
#define AW_PSP_MSGQ_Q_FIFO              0x00
#define AW_PSP_MSGQ_Q_PRIORITY          0x01

/******************************************************************************/
#define AW_PSP_MSGQ_RPI_NORMAL          0
#define AW_PSP_MSGQ_PRI_URGENT          1

/******************************************************************************/
typedef struct rtk_msgq *aw_psp_msgq_id_t;

/******************************************************************************/
#define AW_PSP_MSGQ_DECL(msgq, msg_num, msg_size)  MSGQ_DECL(msgq, msg_size, msg_num)

#define AW_PSP_MSGQ_DECL_STATIC(msgq, msg_num, msg_size)  \
            static AW_PSP_MSGQ_DECL(msgq, msg_num, msg_size)

#define AW_PSP_MSGQ_IMPORT(msgq) extern struct msgq##struct_nav msgq

/* todo: options are not used */
#define AW_PSP_MSGQ_INIT(msgq, msg_num, msg_size, options)  MSGQ_INIT((msgq), msg_size, msg_num)

/* todo: priority is not used; the return value is different */
#define AW_PSP_MSGQ_RECEIVE(msgq, p_buf, nbytes, timeout) \
            msgq_receive(&(msgq).super, p_buf, nbytes, timeout)

/* todo: priority is not used; the return value is different */
#define AW_PSP_MSGQ_SEND(msgq, p_buf, nbytes, timeout, priority) \
            msgq_send(&(msgq).super, p_buf, nbytes, timeout)

#define AW_PSP_MSGQ_TERMINATE(msgq) \
            msgq_terminate(&(msgq).super)

#define AW_PSP_MSGQ_VALID(msgq)         ((msgq).super.sem_rd.type != SEM_TYPE_NULL)
#define AW_PSP_MSGQ_SET_INVALID(msgq)   do { (msgq).super.sem_rd.type = SEM_TYPE_NULL; } while (0)

/******************************************************************************/
aw_static_inline aw_err_t aw_msgq_receive(aw_psp_msgq_id_t msgq_id,
                                          void             *p_buf,
                                          size_t            nbytes,
                                          int               timeout)
{
    return msgq_receive(msgq_id, p_buf, nbytes, timeout);
}

/******************************************************************************/
aw_static_inline aw_err_t aw_msgq_send(aw_psp_msgq_id_t msgq_id,
                                       void             *p_buf,
                                       size_t            nbytes,
                                       int               timeout,
                                       int               priority)
{
    return msgq_send(msgq_id, p_buf, nbytes, timeout);
}

/******************************************************************************/
aw_static_inline aw_err_t aw_msgq_terminate(aw_psp_msgq_id_t msgq_id)
{
    return msgq_terminate(msgq_id);
}

/******************************************************************************/
aw_static_inline bool_t aw_msgq_valid(aw_psp_msgq_id_t msgq_id)
{
    if ((msgq_id != NULL) &&
        (msgq_id->sem_rd.type != SEM_TYPE_NULL)) {
        return TRUE;
    }

    return FALSE;
}

#endif  /* __AW_PSP_MSGQ_H */

/* end of file */
