/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      AWorks.support@zlg.cn
*******************************************************************************/
/**
 * \file gbk2utf8.h
 * \brief
 *
 * \internal
 * \par modification history:
 * - 2016-4-4 rongjiayu, first implementation.
 * \endinternal
 */


#ifndef __GBK2UTF8_H
#define __GBK2UTF8_H

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/
uint8_t awgui_gbk2utf8 (char    *p_utf8_buf,
                        uint32_t    utf8_buf_size,
                        const char *p_gbk);

#ifdef __cplusplus
}
#endif

#endif /* __GBK2UTF8_H */

/* end of file */