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
 * \brief Input Service Configuration.
 *
 * \internal
 * \par modification history:
 * - 1.00 14-09-01  ops, first implementation.
 * \endinternal
 */

#include "aw_msgq.h"
#include "aw_input.h"
#include "awbl_input.h"

void awbl_input_ev_mgr_register(void)
{

	awbl_input_event_init();

#ifdef AW_COM_INPUT_EV_KEY

	awbl_input_event_key_init();

#endif /* AW_COM_AWBL_INPUT_EV_KEY */

#ifdef AW_COM_INPUT_EV_ABS

	awbl_input_event_abs_init();

#endif /* AW_COM_AWBL_INPUT_ABS */

#ifdef AW_COM_INPUT_EV_REL

	awbl_input_event_rel_init();

#endif /* AW_COM_AWBL_INPUT_EV_REL */

}
