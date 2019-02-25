/**
 * \file
 * \brief standard symbolic constants and types.
 *
 * \internal
 * \par modification history:
 * - 150529 deo, 增加 ftruncate,fsync
 * - 150417 deo, 增加 truncate
 * - 140822 orz, first implementation.
 * \endinternal
 */

#ifndef __UNISTD_H /* { */
#define __UNISTD_H

#include "io/aw_unistd.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
#define close		aw_close
#define read		aw_read
#define write		aw_write
#define lseek		aw_lseek
#define rmdir		aw_rmdir
#define unlink		aw_unlink
#define rename		aw_rename
#define truncate	aw_truncate
#define ftruncate	aw_ftruncate
#define getcwd		aw_getcwd
#define chdir		aw_chdir
#define fsync		aw_fsync

#ifdef __cplusplus
}
#endif

#endif /* } __UNISTD_H */

/* end of file */
