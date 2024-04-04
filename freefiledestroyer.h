#ifdef _WIN32
#define TARGET_FILE_MODE O_RDWR|O_BINARY
#define lseek64 _lseeki64
#else
#define _LARGEFILE64_SOURCE
#define TARGET_FILE_MODE O_RDWR|O_LARGEFILE
#endif

#include <sys/stat.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>