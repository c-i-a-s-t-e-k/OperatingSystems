#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>


int dir_size(char* path, char* before_inform){
    DIR* dir = opendir(path);
    struct dirent* dr;
    struct stat stat1;
    long long dirr_size = 0;
    long size;
    while ((dr = readdir(dir)) != NULL){
        stat(dr->d_name, &stat1);
        if (!S_ISDIR(stat1.st_mode)){
            size = ((long) stat1.st_size);
            printf("%s", before_inform);
            printf("%s: %ld B\n", dr->d_name, size);
            dirr_size += ((long long) size);
        }
    }
    closedir(dir);
    return dirr_size;
}