#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BUFFOR_SIZE 1024

#ifndef SYSOP_REVERSE_H
#define SYSOP_REVERSE_H
void reverse(char* ifile, char* oflie, size_t block_size);
#endif //SYSOP_REVERSE_H
