#include "lock_for_argv.h"

int check_file(char* filename, char* pattern){
    size_t n = strlen(pattern);
    char str[n];
    FILE* file = fopen(filename,"r");
    if(file != NULL){
        fread(str, sizeof(char), n, file);
        fclose(file);
        for(int i=0;i<n;i++){
            if(str[i] != pattern[i]) return 0;
        }
        return 1;
    }
    else{
        fprintf(stderr, "FILE ACCESS DENIAL %s\n", filename);
        return 0;
    }
}
void start_new_process(char* dir_name, char *pattern){
    pid_t child_pid = fork();
    if(child_pid == 0){
        find(dir_name, pattern);
        exit(EXIT_SUCCESS);
    } else return;
}

void find(char* path, char *pattern){
    DIR* dir = opendir(path);
    if(dir == NULL){
        perror("OPENDIR ERROR\n");
        exit(EXIT_FAILURE);
    }
    if(chdir(path)==-1){
        perror("CHDIR ERROR\n");
        exit(EXIT_FAILURE);
    }
    char real_path[MAX_PATH_LEN];
    struct dirent* dr;
    struct stat stat1;
    while ((dr = readdir(dir)) != NULL){
        stat(dr->d_name, &stat1);
        if ((dr->d_type == DT_REG) && check_file(dr->d_name, pattern)){
            realpath(dr->d_name, real_path);
            printf("%s\n", real_path);
        }
        if((dr->d_type == DT_DIR) && !(strcmp(dr->d_name, ".") == 0 || strcmp(dr->d_name, "..") == 0)){
            start_new_process(dr->d_name, pattern);
            }
        }
    closedir(dir);
}