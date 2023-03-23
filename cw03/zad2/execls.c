#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void process_hello(){
    pid_t child_pid = fork();
    if(child_pid == 0){
        printf("ppid:%d\tpid:%d\n", (int)getppid(), (int)getpid());
        exit(EXIT_SUCCESS);
    } else return;
}

int main(int argument_count, char *arg_arr[]){
    if(argument_count<1) {
        fprintf(stderr, "WRONG ARGUMENTS NUMBER");
        exit(EXIT_FAILURE);
    }
    int n = atoi(arg_arr[1]);
    printf("Programme starts pid:%d\n", getpid());
    for(int i = 0; i < n; i++){
        process_hello();
    }

    exit(EXIT_SUCCESS);
}
