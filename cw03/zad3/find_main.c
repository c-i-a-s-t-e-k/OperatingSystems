#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lock_for_argv.h"

#define MAX_LEN 255

int main(int argument_count, char *arg_arr[]){
    if(argument_count<2) {
        fprintf(stderr, "WRONG ARGUMENTS NUMBER");
        exit(EXIT_FAILURE);
    }
    if(strlen(arg_arr[2]) > MAX_LEN)
        exit(EXIT_FAILURE);
    find(arg_arr[1], arg_arr[2]);
    exit(EXIT_SUCCESS);
}
