/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn
* e-mail:      support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief
 *
 * \internal
 * \par modification history:
 * - 170923, vih, first implementation.
 * \endinternal
 */


#ifndef __AW_LFFS_FD_H
#define __AW_LFFS_FD_H


#ifdef __cplusplus
extern "C"{
#endif

#include "aworks.h"
#include "aw_lffs_os.h"

/**
 * \brief POSIX dirent
 */
typedef struct aw_lffs_dirent {
    int d_ino;                          /* inode number (serial number of this object) */
    int d_off;                          /* offset to this dirent */
    unsigned short int d_reclen;        /* length of this aw_lffs_dirent */
    unsigned short int d_namelen;       /* length of this d_name */
    unsigned char d_type;               /* type of this record */
    char d_name[256];                   /* name of this object */
} aw_lffs_dirent_t;

/**
 * \brief POSIX stat
 */
struct aw_lffs_stat {
    int         st_dev;     /* ID of device containing file */
    int         st_ino;     /* inode number */
    int         st_mode;    /* protection */
    int         st_nlink;   /* number of hard links */
    int         st_uid;     /* user ID of owner */
    int         st_gid;     /* group ID of owner */
    int         st_rdev;    /* device ID (if special file) */
    long        st_size;    /* total size, in bytes */
    int         st_blksize; /* blocksize for filesystem I/O */
    int         st_blocks;  /* number of blocks allocated */
    unsigned int    st_atime;   /* time of last access */
    unsigned int    st_mtime;   /* time of last modification */
    unsigned int    st_ctime;   /* time of last status change */
};

typedef struct aw_lffs_dir_info aw_lffs_dir_info_t;

/* POSIX complaint file system APIs */

int aw_lffs_open (const char *name, int oflag, ...);
int aw_lffs_close (int fd);
int aw_lffs_read (int fd, void *data, int len);
int aw_lffs_write (int fd, const void *data, int len);
long aw_lffs_seek (int fd, long offset, int origin);
long aw_lffs_tell (int fd);
int aw_lffs_eof (int fd);
int aw_lffs_flush (int fd);
int aw_lffs_rename (const char *old_name, const char *new_name);
int aw_lffs_remove (const char *name);
int aw_lffs_ftruncate (int fd, long remain);

int aw_lffs_mkdir (const char *name, ...);
int aw_lffs_rmdir (const char *name);

int aw_lffs_stat (const char *name, struct aw_lffs_stat *buf);
int aw_lffs_lstat (const char *name, struct aw_lffs_stat *buf);
int aw_lffs_fstat (int fd, struct aw_lffs_stat *buf);

int aw_lffs_closedir (aw_lffs_dir_info_t *dirp);
aw_lffs_dir_info_t * aw_lffs_opendir (const char *path);
struct aw_lffs_dirent * aw_lffs_readdir (aw_lffs_dir_info_t *dirp);

void aw_lffs_rewinddir (aw_lffs_dir_info_t *dirp);


int aw_lffs_get_error (void);
int aw_lffs_set_error (int err);

int aw_lffs_version (void);
int aw_lffs_format (const char *mount_point);

long aw_lffs_space_total (const char *mount_point);
long aw_lffs_space_used (const char *mount_point);
long aw_lffs_space_free (const char *mount_point);

void aw_lffs_flush_all (const char *mount_point);

#ifdef __cplusplus
}
#endif

#endif /* __AW_LFFS_FD_H */

/* end of __AW_LFFS_FD_H */




