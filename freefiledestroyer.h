#ifdef _WIN32
#define TARGET_FILE_MODE O_RDWR|O_BINARY
#define file_seek _lseeki64
#endif

#ifndef _WIN32
#define _LARGEFILE64_SOURCE
#define TARGET_FILE_MODE O_RDWR|O_LARGEFILE
#define file_seek lseek64
#endif

#include <sys/stat.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>