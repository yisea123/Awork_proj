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
 * \brief CRC ����
 *
 * \internal
 * \par modification history
 * - 1.00 12-11-14  tee, first implementation
 * \endinternal
 */

#ifndef __AWBL_CRC_H
#define __AWBL_CRC_H

#include "aw_common.h"
#include "awbus_lite.h"
#include "aw_crc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup awbl_crc  
 * @{
 */



/** \brief crc serve functions */
struct awbl_crc_functions {
 
    /** \brief ��ʼ�� */
    aw_err_t (*pfunc_init) (void *p_drv,aw_crc_pattern_t *p_pattern);

    /** \brief ����CRCֵ */
    aw_err_t (*pfunc_cal) (void *p_drv,uint8_t *p_data,uint32_t nbytes);
 
    /** \brief �õ�CRCֵ,Ӳ��CRCͬʱ���ͷ�Ӳ��CRC */
    aw_err_t (*pfunc_final) (void *p_drv,uint32_t *p_crcvalue);
};

struct awbl_crc_drv_info {   
    struct awbl_crc_functions *p_servfuncs; 
    void                      *p_drv;
};

struct awbl_crc_serch_info {
    aw_crc_pattern_t         *p_pattern;
    bool_t                    is_searched;  /**< \brief TRUE if is_searched */  
    struct awbl_crc_drv_info  drv_info;
};
       
/** \brief timer method awbl_timer_func_get return this type */
typedef aw_err_t (*pfunc_crc_func_get_t) (struct awbl_dev            *p_dev,
                                          struct awbl_crc_drv_info   *p_drv_info);


/** \brief import crc method,use to get the crc functions */
AWBL_METHOD_IMPORT(awbl_crcserv_get);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AWBL_TIMER_H */

/* end of file */
