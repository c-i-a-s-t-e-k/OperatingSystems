#include "reverse.h"
#include <stdio.h>

int main(int argument_count, char *arg_arr[]){
    if(argument_count<4) fprintf(stderr, "niepoprawna ilość argumentow");
    reverse(arg_arr[1], arg_arr[2], 1024);
}