#ifndef HYPEROS_USERLAND_LIBRARIES_LIBC_SYS_TYPES_H_
#define HYPEROS_USERLAND_LIBRARIES_LIBC_SYS_TYPES_H_

#include <stdint.h>
#include <sys/cdefs.h>

typedef __WINT_TYPE__ wint_t;

typedef uint32_t uid_t;
typedef uint32_t gid_t;
typedef int pid_t;

typedef int32_t ssize_t;

typedef uint32_t ino_t;
typedef int32_t off_t;

typedef uint32_t dev_t;
typedef uint32_t mode_t;
typedef uint32_t nlink_t;
typedef uint32_t blksize_t;
typedef uint32_t blkcnt_t;
typedef uint32_t time_t;
typedef uint32_t suseconds_t;
typedef uint32_t clock_t;
typedef uint32_t socklen_t;

struct timeval
{
    time_t tv_sec;
    suseconds_t tv_usec;
};

struct stat
{
    dev_t st_dev;
    ino_t st_ino;
    mode_t st_mode;
    nlink_t st_nlink;
    uid_t st_uid;
    gid_t st_gid;
    dev_t st_rdev;
    off_t st_size;
    blksize_t st_blksize;
    blkcnt_t st_blocks;
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;
};

#define NULL 0

#endif