#ifndef SYSOP_LIBZAD1_H
#define SYSOP_LIBZAD1_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 1024

typedef struct{
    char ** data;
    size_t n;
    size_t size;
}DataTable;

DataTable createDataTable(size_t size);
void wc(DataTable table, char *fileName);
char* getFromDataTable(DataTable table, int i);
void eraseFromDataTable(DataTable table, int i);
void clearDataTable(DataTable table);

#endif //SYSOP_LIBZAD1_H
