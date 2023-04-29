#include "project_salon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

int *times;

void hair_cut(int hairstyle_id){
    sleep(times[hairstyle_id]);
    printf("for now nothing");
}

// funkcja otwiera kolejke komunikatów za pomocą klucza podanego w argumęcie i czeka na odpowiednie komunikaty
int main() {
//    sprawdzanie poprawnei ilości argumentów
    key_t key_msq = ftok(project_path, PROJECT_CHAR);
    key_t key_shm = ftok(project_path, PROJECT_CHAR);

    printf("HD %d, %d\n", key_msq, key_shm);
//    otwarcie kolejki komunikatów
    int msqid;
    if ((msqid = msgget(key_msq, IPC_EXCL)) == -1){
        perror("msgget failure");
        exit(EXIT_FAILURE);
    }
//    otwarcie pamięci współdzielonej, oraz pobranie danych
    int shmid;
    if ((shmid = shmget(key_shm, sizeof(int)*HAIRSTYLES_N , IPC_EXCL)) == -1){
        perror("shmget failure");
        exit(EXIT_FAILURE);
    }
    times = (int*) shmat(shmid, NULL, 0);
    if (times == (int*) -1) {
        perror("shmat error");
        exit(EXIT_FAILURE);
    }

//    oczekiwanie na komunikaty w nieskończonej pętli
    struct ms_buf message;
    while (1){
        if (msgrcv(msqid, &message, MSG_SIZE, SALON_REQUEST, 0) == -1){
            perror("msgrcv failure");
            exit(EXIT_FAILURE);
        }
        hair_cut(atoi(message.ms_text));
    }
}