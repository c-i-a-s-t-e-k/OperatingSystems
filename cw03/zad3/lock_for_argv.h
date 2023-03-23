

#ifndef SYSOP_LOCK_FOR_ARGV_H
#define SYSOP_LOCK_FOR_ARGV_H
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <ftw.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PATH_LEN 1024

void find(char* path, char *pattern);

#endif //SYSOP_LOCK_FOR_ARGV_H
