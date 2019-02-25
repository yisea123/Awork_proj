/**
 * \file
 * \brief file control options.
 *
 * \internal
 * \par modification history:
 * - 140822 orz, first implementation.
 * \endinternal
 */

#ifndef __FCNTL_H /* { */
#define __FCNTL_H

#include "io/aw_fcntl.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
#define creat   aw_create
#define open    aw_open
#define fcntl   aw_fcntl

#ifdef __cplusplus
}
#endif

#endif /* } __FCNTL_H */

/* end of file */
