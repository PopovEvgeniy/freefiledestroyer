#if defined _MSC_VER && _MSC_VER>=1400
  #pragma warning(disable : 4996)
#endif

#ifndef _WIN32
#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64
#define __USE_FILE_OFFSET64
#endif

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef _WIN32
#include <io.h>
#define TARGET_FILE_MODE O_RDWR|O_BINARY
#define TARGET_FILE_PERMISSIONS S_IREAD|S_IWRITE
#define file_seek _lseeki64
#else
#include <unistd.h>
#define TARGET_FILE_MODE O_RDWR
#define TARGET_FILE_PERMISSIONS S_IRUSR|S_IWUSR
#define file_seek lseek
#endif