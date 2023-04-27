#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


int main(int arg_number, char *arg_arr[]) {
    printf("programme start pid:%d\n", getpid());
    if (arg_number < 3) {
        perror("zła liczba argumentów");
        exit(EXIT_FAILURE);
    }
//    int tmp;
    int salon_PID = atoi(arg_arr[1]);
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    int hairstyle_num = atoi(arg_arr[2]);
    printf("comannd: %d\n", hairstyle_num);
    union sigval signalvalue;
    signalvalue.sival_int = hairstyle_num;
    if (sigqueue(salon_PID, SIGUSR1, signalvalue)==-1) {
        perror("sigqueue error");
        exit(EXIT_FAILURE);
    } else{
        printf("signal sended\n");
    }
//    if(sigwait(&sigset, &tmp) == -1)
//        perror("sigsuspend error");
//    else{
//        if(kill(catcher_PID, SIGUSR1)==-1)perror("\tconfirmation problem\n");
//        else printf("\tconfirmation sended\n");
//    }
    exit(EXIT_SUCCESS);
}