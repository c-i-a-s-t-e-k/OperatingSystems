#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <ftw.h>
#include <unistd.h>

#define MAX_N 128

long long dirr_size;

int handle_file(const char* fname, const struct stat* sbuf, int flags){
    long size;
    if (!S_ISDIR(sbuf->st_mode)){
        size = ((long) sbuf->st_size);
        printf("%s: %ld B\n", fname, size);
        dirr_size += ((long long) size);
    }
    return 0;
}

long long dir_size(char *path, int n){
    long long dir_size = 0;
    ftw(path, handle_file, n);
    return dir_size;
}

int main(int argument_count, char *arg_arr[]){
    char* path;
    if(argument_count<1) path=".";
    else path=arg_arr[1];
    printf("summary size: %lld B\n", dir_size(path, MAX_N));
}
