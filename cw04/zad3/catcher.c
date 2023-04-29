#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int change_counter = -1;
int last_mode = -1;
int mode = 0;
int done = 1;

void handle_mode1(){
    for(int i=1; i<=100; i++){
        printf("%d ", i);
    }
    printf("\n");
}
void handle_mode2(){
    time_t timer;
    struct tm * actualTime;
    time( & timer );
    actualTime = localtime( & timer );
    printf("%s\n", asctime(actualTime));
}

void handle_mode3(){
    printf("%d\n", change_counter);
}
void handle_mode4(){
    time_t timer;
    struct tm * actualTime;
    time( & timer );
    actualTime = localtime(&timer);
    printf("%s\n", asctime(actualTime));
    sleep(1);
}
void handle_mode5(){
    printf("mode 5\n");
    exit(EXIT_SUCCESS);
}


void handleSIGUSR1(int signum, siginfo_t *siginfo, void *extra){
    int sig;
    if(signum == SIGUSR1){
//        printf("\nhandle start\n");
        sigset_t sigset;
        sigemptyset(&sigset);
        sigaddset(&sigset, SIGUSR1);
        if(kill(siginfo->si_pid, SIGUSR1)==-1){
            perror("kill problem");
        }else{
//            printf("sended acces allowance to %d\n", siginfo->si_pid);
        }
        if(sigwait(&sigset, &sig) == -1)
            perror("sigsuspend error");
        else{
//            printf("confirmation granted\n");
            if(last_mode != siginfo->si_int){
                change_counter++;
            }
            mode = siginfo->si_int;
            done = 0;
//            printf("\nhandle end\n");
            return;
        }
    }
}

int main() {
    printf("programme start pid:%d\n", getpid());
    struct sigaction new_action;
    new_action.sa_flags = SA_SIGINFO;
    new_action.sa_sigaction = &handleSIGUSR1;
    sigemptyset(&new_action.sa_mask);
    if(sigaction(SIGUSR1, &new_action, NULL) == -1){
        perror("sigaction error");
        exit(EXIT_FAILURE);
    }
    while (1){
        if (done){
            continue;
        }
        switch (mode) {
            case 1:
                handle_mode1();
                break;
            case 2:
                handle_mode2();
                break;
            case 3:
                handle_mode3();
                break;
            case 4:
                handle_mode4();
                break;
            case 5:
                handle_mode5();
                break;
            default:
                perror("unexepected mode");
                break;
        }
        if (mode != 4)
            done = 1;
    }
}