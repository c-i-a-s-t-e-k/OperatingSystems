//
// Created by ciastek on 21.04.23.
//

#ifndef SYSOP_COMMON_H
#define SYSOP_COMMON_H
#define MAX_CLIENTS 10

#define SERVER_QUEUE_KEY 1234

#define INIT_MSG_TYPE 1

#define LIST_MSG_TYPE 2

#define ALL_MSG_TYPE 3

#define ONE_MSG_TYPE 4

#define STOP_MSG_TYPE 5

#define MSG_BUFFER_SIZE 256

#define MSG_TYPE_COUNT 5

typedef struct {
    long type;
    char text[MSG_BUFFER_SIZE];
    int client_id;
    time_t timestamp;
} message;

#endif //SYSOP_COMMON_H
