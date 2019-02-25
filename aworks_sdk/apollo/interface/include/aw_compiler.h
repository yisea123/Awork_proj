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
 * \brief ��������ض���ͷ�ļ�
 *
 * \internal
 * \par modification history:
 * - 1.10 14-09-28	zen, move some defines to aw_psp_complier.h
 * - 1.01 14-08-12  orz, add define of restrict
 * - 1.00 13-01-15  orz, move defines from aw_common.h
 * \endinternal
 */

#ifndef __AW_COMPILER /* { */
#define __AW_COMPILER

#include "aw_psp_compiler.h"


#define aw_inline			aw_psp_inline			/** \brief inline ����  */
#define aw_static_inline	aw_psp_static_inline	/** \biref static inline ���� */

#define aw_section(x)		aw_psp_section(x)		/** \brief __section() ���� */

#define aw_inline			aw_psp_inline
#define aw_static_inline 	aw_psp_static_inline

#define aw_local  			aw_psp_local
#define aw_const    		aw_psp_const
#define aw_import   		aw_psp_import
#define aw_export			aw_psp_export

#endif /* } __AW_COMPILER */

/* end of file */
