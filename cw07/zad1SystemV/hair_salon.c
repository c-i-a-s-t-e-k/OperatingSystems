#include "hair_salon.h"
int N, M, P;
pid_t* hairdressers;
int msqid, shmid;

void handleSIGINT(int signum){
    if(signum == SIGINT){
        for(int i =0;i<M;i++){
            kill(hairdressers[i], SIGTERM);
        }
        free(hairdressers);
//        usunięcie kolejki komunikatów
        if (msgctl(msqid, IPC_RMID, NULL) == -1) {
            perror("msgctl error");
            exit(EXIT_FAILURE);
        }
//        usunięcie pamięci współdzielonej
        if (shmctl(shmid, IPC_RMID, 0) == -1) {
            perror("shmctl");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
}

void handleSIGUSR1(int signum, siginfo_t *siginfo, void *extra){
    if(signum == SIGUSR1){
        int hairstyle_id = siginfo->si_int;
        if (hairstyle_id < HAIRSTYLES_N && hairstyle_id > -1){
            struct ms_buf message;
            message.ms_type = SALON_REQUEST;
            sprintf(message.ms_text, "%d", hairstyle_id);
            if (msgsnd(msqid, &message, MSG_SIZE, 0) == -1) {
                perror("msgsnd");
                exit(EXIT_FAILURE);
            }
        } else{
            perror("wrong hairstyle index");
        }
    }
}

void set_signal_handler(int signum, void (*handler)(int)){
    struct sigaction new_action;
    sigemptyset(&new_action.sa_mask);
    sigaddset(&new_action.sa_mask, SIGUSR1);
    new_action.sa_handler = handler;
    new_action.sa_flags=0;
    if(sigaction(signum, &new_action, NULL) == -1){
        perror("sigaction error");
        exit(EXIT_FAILURE);
    }
}

int create_message_queue(char *pathname, key_t* key){
    *key = ftok(pathname, PROJECT_CHAR);
    if ((msqid = msgget(*key, IPC_EXCL | IPC_CREAT | 0666))){
        perror("msqget failure");
        exit(EXIT_FAILURE);
    }
    return msqid;
}

int create_shared_memory(char *pathname, key_t* key){
    *key = ftok(pathname, PROJECT_CHAR);
    if ((shmid = shmget(*key,sizeof(int)*HAIRSTYLES_N,IPC_EXCL | IPC_CREAT | 0666))){
        perror("shmget failure");
        exit(EXIT_FAILURE);
    }
    return shmid;
}

void fill_shm_with_hairstyles(){
    int * shm_ptr;
    if ((shm_ptr = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat error");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < HAIRSTYLES_N; i++) {
        shm_ptr[i] = hairstyles_times[i];
    }
}

//tworzy procesy reprezentujące fryzjerów
void create_hairdressers(key_t key_msq, key_t key_shm){
    int child_pid;
    char msq_str[62];
    char shm_str[62];
    sprintf(msq_str, "%d", key_msq);
    sprintf(shm_str, "%d", key_shm);
    char *args = {"hairdresser.exe", msq_str, shm_str};

    for(int i =0; i < M; i++){
        child_pid = fork();
        if (child_pid == -1){
            perror("fork failure");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0){
            execvp(&args[0], &args);
            perror("execvp failure");
            exit(EXIT_FAILURE);
        } else{
            hairdressers[i] = child_pid;
        }
    }
}


int main(int argc, char *argv[]) {
//    sprawdzanie poprawnei ilości argumentów oraz ich przypisanie do zmiennych
    if (argc < 3){
        perror("invalids arguments number");
        exit(EXIT_FAILURE);
    }
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    if (M < N){
        perror("invalids arguments number");
        exit(EXIT_FAILURE);
    }
    hairdressers = calloc(M, sizeof(pid_t));
    P = atoi(argv[3]);
    key_t *key_msq;
    key_t *key_shm;
//    ustawienie handlera do obsługi klienta
    struct sigaction new_action;
    new_action.sa_flags = SA_SIGINFO;
    new_action.sa_sigaction = &handleSIGUSR1;
    sigemptyset(&new_action.sa_mask);
    if(sigaction(SIGUSR1, &new_action, NULL) == -1){
        perror("sigaction error");
        exit(EXIT_FAILURE);
    }
    create_message_queue(argv[0], key_msq);
    create_shared_memory(argv[0], key_shm);
    fill_shm_with_hairstyles();

    printf("programme start pid:%d\n", getpid());
}