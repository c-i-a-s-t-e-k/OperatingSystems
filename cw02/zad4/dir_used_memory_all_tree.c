#include <stdio.h>
#include "dirsize.h"


int main(int argument_count, char *arg_arr[]){
    char* path;
    if(argument_count<1) path=".";
    else path=arg_arr[1];
    printf("summary size: %lld B\n", dir_size(path, " "));
}
