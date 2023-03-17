#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <ftw.h>
#include <unistd.h>

long long dir_size(char* path, char* before_inform){
    DIR* dir = opendir(path);
    printf("%s -->\n", path);
    struct dirent* dr;
    struct stat stat1;
    long long dirr_size = 0;
    long size;
    long loc;
    while ((dr = readdir(dir)) != NULL){
        stat(dr->d_name, &stat1);
        if (!S_ISDIR(stat1.st_mode)){
            size = ((long) stat1.st_size);
            printf("%s", before_inform);
            printf("%s: %ld B\n", dr->d_name, size);
            dirr_size += ((long long) size);
        }
        if(S_ISDIR(stat1.st_mode)){
            if (strcmp(dr->d_name, ".") == 0 || strcmp(dr->d_name, "..") == 0){
//                printf("%s, %d, %d\n", dr->d_name, strcmp(dr->d_name, "."), strcmp(dr->d_name, "..") );
            }
            else {
                printf("directory: %s,   %d %d\n", dr->d_name, S_ISREG(stat1.st_mode), S_ISDIR(stat1.st_mode));
                loc = telldir(dir);
                closedir(dir);
                dirr_size += dir_size(dr->d_name, " ");
                dir = opendir(path);
                seekdir(dir, loc);
            }
        }
    }
    closedir(dir);
    return dirr_size;
}

//long long dirr_size;
//
//int handle_file(const char* fname, const struct stat* sbuf, int flags){
//    long size;
//    if (!S_ISDIR(sbuf->st_mode)){
//        size = ((long) sbuf->st_size);
//        printf("%s: %ld B\n", fname, size);
//        dirr_size += ((long long) size);
//    }
//    return 0;
//}
//
//
//long long dir_size(char *path, int n){
//    long long dir_size = 0;
//    ftw(path, handle_file, n);
//    return dir_size;
//}