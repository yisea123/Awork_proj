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

#ifdef AW_IMG_PRJ_BUILD

/**
 * \file
 * \brief AWorks1.0 starting up flow control file
 *
 * \internal
 * \par History
 * - 1.10 13-01-10  zen, change start up flow, this file will be included by
 *                  aw_prj_config.c
 * - 1.00 12-11-28  or2, first implementation. 姝ゆ枃浠惰prjconfig.c鍖呭惈銆�?* \endinternal
 */

/*
 *  For aworks1.0:
 *
 *------------------------------------------------------------------------------
 *  Image Project:
 *
 *  aw_prj_usr_app_init.c:                                aw_prj_usr_app_init()
 *                                                                     .
 *  aw_prj_config.c: aw_prj_early_init()    aw_prj_task_level_init()  /|\
 *                           .                        .                |
 *                          /|\                      /|\               |
 *                           |                        |                |
 *                           |                        |                |
 *---------------------------|-----------------------------------------|--------
 *  AWorks PSP               |                        |                |
 *                           |                        |                |
 *  aw_psp_usr_app_init.c:   |                        |    aw_psp_usr_app_init()
 *                           |                        |                .
 *  aw_psp_startup.c:   aw_psp_early_init() aw_psp_task_level_init()  /|\
 *                           .                        .                |
 *                          /|\                      /|\               |
 *                           |                        |                |
 *                           |                        |                |
 *---------------------------|------------------------|----------------|--------
 *  Aworks1.0                |                        |                |
 *                           |                        |                |
 *  aworks_startup.c: aworks_startup()----> aworks_task_level_init() --|
 *                    .         |                         |
 *                   /|\        |                         |
 *                    |         |                         |
 *                    |        \|/                       \|/
 *                    |         .                         .
 *  BSP:              |  aw_bsp_early_init()      aw_bsp_task_level_init()
 *                    |
 *                    |
 *                __main()
 *                   /|\
 *                    |
 *--------------------|---------------------------------------------------------
 *  hw reset  --------|
 */

void aw_bsp_early_init(void);
void aw_psp_early_init(void);

void aw_bsp_task_level_init(void);
void aw_psp_task_level_init(void);

int aw_psp_usr_app_init(void);

void target_init (void);

/**
 *  \fn aw_psp_task_level_init
 *  \brief 绗竴涓换鍔� */
void aworks_task_level_init(void)
{
    aw_bsp_task_level_init();
    aw_psp_task_level_init();

    aw_psp_usr_app_init();
}

/**
 *  \brief AWorks1.0 C environment entry
 */
int main (void)
{
    AW_TASK_DECL_STATIC(info, AW_CFG_MAIN_TASK_STACK_SIZE );

    target_init();

    kernel_init();
    aw_bsp_early_init();
    aw_psp_early_init();

    /* start main task */
    AW_TASK_INIT( info,
                  "aw_main",
                  AW_CFG_MAIN_TASK_PRIO,
                  AW_CFG_MAIN_TASK_STACK_SIZE,
                  aworks_task_level_init,
                  (void *)0x00);

    AW_TASK_STARTUP(info);

    os_startup();

    return 0;
}

#endif /* AW_IMG_PRJ_BUILD */
