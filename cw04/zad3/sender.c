#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

pid_t catcher_PID;


void handleSIGUSR1(int signum){
    if(signum == SIGUSR1){
        printf("\tget siggnal to confirm\n");
        if(kill(catcher_PID, SIGUSR1)==-1)perror("\tconfirmation problem\n");
    }
}

void set_signal_handler(){
    struct sigaction new_action;
    sigemptyset(&new_action.sa_mask);
    sigaddset(&new_action.sa_mask, SIGUSR1);
    new_action.sa_handler = handleSIGUSR1;
    new_action.sa_flags=0;
    if(sigaction(SIGUSR1, &new_action, NULL) == -1){
        perror("sigaction error");
        exit(EXIT_FAILURE);
    }
}

int main(int arg_number, char *arg_arr[]) {
    printf("programme start pid:%d\n", getpid());
    if (arg_number < 2) {
        perror("zła liczba argumentów");
        exit(EXIT_FAILURE);
    }
    int tmp;
    set_signal_handler();
    catcher_PID = atoi(arg_arr[1]);
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    for(int i=2; i<arg_number; i++){
        int a = atoi(arg_arr[i]);
        printf("comannd: %d\n", a);
        union sigval signalvalue;
        signalvalue.sival_int = atoi(arg_arr[i]);

        if (sigqueue(catcher_PID, SIGUSR1, signalvalue)==-1) {
            perror("sigqueue error");
            exit(EXIT_FAILURE);
        } else{
            printf("signal sended\n");
        }
        if(sigwait(&sigset, &tmp) == -1)
            perror("sigsuspend error");
        else{
            if(kill(catcher_PID, SIGUSR1)==-1)perror("\tconfirmation problem\n");
            else printf("\tconfirmation sended\n");
        }
    }
    exit(EXIT_SUCCESS);
}