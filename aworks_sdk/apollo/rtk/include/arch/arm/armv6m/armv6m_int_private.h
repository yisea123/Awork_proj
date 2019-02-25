/*******************************************************************************
*                                 AnyWhere
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ARMv6-M interrupt library private header file
 *
 * \internal
 * \par modification history:
 * - 1.00 12-09-04  zen, first implementation
 * \endinternal 
 */

#ifndef __ARMV6M_INT_PRIVATE_H
#define __ARMV6M_INT_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/** 
 * \brief interrupt's isr information
 */
struct __int_isr_info {

    /** \brief isr callback function */
    aw_pfuncvoid_t pfunc_isr;

    /** \brief argument for\a __isrinfo::pfunc_isr */
    void *p_arg;
};

/**
 * \brief armv6m interrupt library initialization
 *
 * \param[in]   p_infos pointer to isr information memeory
 * \param[in]   count   the count of isr information
 * \param[in]   p_map   pointer to isr map memory
 */
void armv6m_int_init2(struct __int_isr_info *p_infos, 
                      size_t                 count, 
                      uint8_t               *p_map);

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __ARMV6M_INT_PRIVATE_H */

/* end of file */
