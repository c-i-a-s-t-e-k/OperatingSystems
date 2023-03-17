#include <stdio.h>
#include "../../JezowDominik/cw02/zad1/translate.h"

int main(int args, char* args_arr[]){
    if(args < 5) fprintf(stderr, "nieprawidłowa ilość argumentów\n");
    else tr_sys(args_arr[1][0], args_arr[1][0], args_arr[1], args_arr[1]);
}