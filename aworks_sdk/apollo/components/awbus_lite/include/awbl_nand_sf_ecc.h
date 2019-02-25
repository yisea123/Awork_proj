/*******************************************************************************
*                                 AWorks
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
 * \brief nand controler software ecc driver head file
 *
 * \internal
 * \par modification history:
 * - 1.00 17-3-22  vih, first implementation
 * \endinternal
 */

#ifndef __AWBL_NAND_SF_ECC_H
#define __AWBL_NAND_SF_ECC_H


#include "awbl_nand.h"
#include "apollo.h"
#include "aw_soft_bch.h"

/**
 * \brief ECCУ��ӿ�ʵ��(HAM)
 */
int awbl_nand_correct_ham (
         struct awbl_nand_chip            *p_nand,
         uint8_t                          *p_buf,
         uint8_t                          *read_ecc,
         uint8_t                          *calc_ecc);

int awbl_nand_calculate_ham (
         struct awbl_nand_chip            *p_nand,
         const uint8_t                    *p_buf,
         uint8_t                          *ecc_buf);

aw_err_t awbl_nand_bch_init(struct awbl_nand_chip *p_nand);

/**
 * \brief ECC����ӿ�ʵ��(BCH)
 */
int awbl_nand_calculate_bch (
        struct awbl_nand_chip            *p_nand,
        const uint8_t                    *p_buf,
        uint8_t                          *ecc_buf);

/**
 * \brief ECCУ��ӿ�ʵ��(BCH)
 *
 * \retval  0       : �޴���
 *          -EBADMSG: �����޷������Ĵ���
 *          > 0     : �����ķ�תλ��
 */
int awbl_nand_correct_bch (
        struct awbl_nand_chip            *p_nand,
        uint8_t                          *p_buf,
        uint8_t                          *read_ecc,
        uint8_t                          *calc_ecc);



#endif  /* __AWBL_NAND_SF_ECC_H */
