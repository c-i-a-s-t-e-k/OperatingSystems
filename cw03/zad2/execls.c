#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argument_count, char *arg_arr[]){
    if(argument_count<1) {
        fprintf(stderr, "WRONG ARGUMENTS NUMBER");
        exit(EXIT_FAILURE);
    }
    printf("%s", arg_arr[1]);
    execl("/bin/ls", "ls", arg_arr[1], "-l",NULL);
    exit(EXIT_SUCCESS);
}
