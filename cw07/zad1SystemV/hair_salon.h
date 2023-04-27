//
// Created by ciastek on 27.04.23.
//

#ifndef SYSOP_MESSAGE_BUFFOR_H
#define SYSOP_MESSAGE_BUFFOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>

#define MSG_SIZE 256
#define SALON_REQUEST 1
#define CLIENT_REQUEST 2
#define PROJECT_CHAR 'H'
#define HAIRSTYLES_N 5

// struktura wysyłanych do kolejki wiadomości
struct ms_buf {
    long ms_type;
    char ms_text[MSG_SIZE];
};

// czasy robienia fryzur tablica powinna być długości HAIRSTYLES_N
const int hairstyles_times[HAIRSTYLES_N] = {1,5,7,10,4};
#endif //SYSOP_MESSAGE_BUFFOR_H
