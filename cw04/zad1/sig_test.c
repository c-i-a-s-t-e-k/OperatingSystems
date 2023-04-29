#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handleSIGUSR1(int signum){
    if(signum == SIGUSR1){
        printf("handle start");
        sleep(10);
        printf("handle end");
        exit(EXIT_SUCCESS);
    } else{
        perror("catch wrong signal\nprogramme stop");
        exit(EXIT_FAILURE);
    }
}

int main(int arg_number, char *arg_arr[]){
    if(arg_number < 2) {
        perror("zła liczba argumentów");
        exit(EXIT_FAILURE);
    }
    printf("programme start pid:%d", getpid());

    switch (arg_arr[1][1]) {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case expression:
    }
}