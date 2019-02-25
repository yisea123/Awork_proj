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
 * \brief AWBus 中断控制器接口头文件
 *
 * 使用本模块需要包含以下头文件：
 * \code
 * #include "awbl_intcltr.h"
 * \endcode
 *
 * 本模块管理 AWBus 上的所有中断控制器。
 *
 * \internal
 * \par modification history:
 * - 1.00 12-11-06  zen, first implemetation
 * \endinternal
 */

#ifndef __AWBL_INTCTLR_H
#define __AWBL_INTCTLR_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \brief AWBus intctlr 服务的配置信息
 */
struct awbl_intctlr_servinfo {

    /** \brief 支持的起始中断号 */
    int inum_start;

    /** \brief 支持的结束中断号 */
    int inum_end;
};

/**
 * \brief AWBus intctlr 服务函数
 */
struct awbl_intctlr_servfuncs {

    /* \brief 连接中断服务函数 */
    aw_err_t (*pfunc_int_connect)(void            *p_cookie,
                                  int              inum,
                                  aw_pfuncvoid_t   pfunc_isr,
                                  void            *p_arg);

    /* \brief 断开中断服务函数 */
    aw_err_t (*pfunc_int_disconnect)(void            *p_cookie,
                                     int              inum,
                                     aw_pfuncvoid_t   pfunc_isr,
                                     void            *p_arg);

    /* \brief 中断使能服务函数 */
    aw_err_t (*pfunc_int_enable)(void *p_cookie, int inum);

    /* \brief 中断使能服务函数 */
    aw_err_t (*pfunc_int_disable)(void *p_cookie, int inum);

};

/**
 * \brief AWBus 中断控制器服务
 */
struct awbl_intctlr_service {

    /** \brief 指向下一个 intctlr 服务 */
    struct awbl_intctlr_service *p_next;

    /** \brief intctlr 服务的配置信息 */
    const struct awbl_intctlr_servinfo *p_servinfo;

    /** \brief intctlr 服务的服务函数 */
    const struct awbl_intctlr_servfuncs *p_servfuncs;

    /**
     * \brief intctlr 服务自定义的数据
     *
     * 此参数在 intctlr 接口模块搜索服务时由驱动设置，
     * 在调用服务函数时作为第一个参数。
     */
    void *p_cookie;
};

/**
 * \brief AWBus 中断控制器服务初始化
 *
 * \attention 本函数应当在 awbl_dev_init1() 之后、在 awbl_dev_init2() 之前调用
 */
void awbl_intctlr_init(void);

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AWBL_INTCTLR_H */

/* end of file */
