//
// Created by ciastek on 28.04.23.
//

#ifndef SYSOP_PROJECT_SALON_H
#define SYSOP_PROJECT_SALON_H

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

char project_path[1024];

#endif //SYSOP_PROJECT_SALON_H
