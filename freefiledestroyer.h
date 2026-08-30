#if defined _MSC_VER && _MSC_VER>=1400
  #pragma warning(disable : 4996)
#endif

#ifndef _WIN32
#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64
#define __USE_FILE_OFFSET64
#endif

#ifdef __HAIKU__
#define B_USE_POSITIVE_POSIX_ERRORS
#endif

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#ifdef _WIN32
#include <io.h>
#define TARGET_FILE_MODE O_RDWR|O_BINARY
#define TARGET_FILE_PERMISSIONS S_IREAD|S_IWRITE
#define file_seek _lseeki64
#define file_sync _commit
#define ssize_t ptrdiff_t
#else
#include <unistd.h>
#define TARGET_FILE_MODE O_RDWR
#define TARGET_FILE_PERMISSIONS S_IRUSR|S_IWUSR
#define file_seek lseek
#define file_sync fsync
#endif

#ifndef EINTR
#define try_again 0
#else
#define try_again (errno==EINTR)
#endif