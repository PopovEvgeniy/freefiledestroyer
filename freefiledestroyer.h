#if defined _MSC_VER && _MSC_VER>=1400
  #pragma warning(disable : 4996)
#endif

#ifndef _WIN32
#define _LARGEFILE64_SOURCE
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
#define lseek64 _lseeki64
#else
#include <unistd.h>
#define TARGET_FILE_MODE O_RDWR|O_LARGEFILE
#define TARGET_FILE_PERMISSIONS S_IRUSR|S_IWUSR
#endif