#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <errno.h>
#include "common.h"

int running = 1;
int clients_count = 0;
int clients_queue_ids[MAX_CLIENTS];

void int_handler(int sig) {
    printf("Received signal %d\n", sig);
    running = 0;
}

void remove_queue(void) {
    printf("Removing server queue\n");
    msgctl(msgget(SERVER_QUEUE_KEY, IPC_CREAT | 0666), IPC_RMID, NULL);
}

void handle_list_request(int client_id) {
    printf("Received list request from client %d\n", client_id);
    message response;
    response.type = client_id;
    sprintf(response.text, "Active clients: %d\n", clients_count);
    msgsnd(clients_queue_ids[client_id], &response, sizeof(message) - sizeof(long), 0);
}

void handle_all_message(int client_id, char *message_text) {
    printf("Received all message from client %d: %s\n", client_id, message_text);
    message response;
    response.type = ALL_MSG_TYPE;
    response.client_id = client_id;
    response.timestamp = time(NULL);
    sprintf(response.text, "[%d][%s]: %s\n", client_id, ctime(&response.timestamp), message_text);
    int i;
    for (i = 0; i < clients_count; i++) {
        if (i != client_id) {
            msgsnd(clients_queue_ids[i], &response, sizeof(message) - sizeof(long), 0);
        }
    }
}

void handle_one_message(int client_id, int recipient_id, char *message_text) {
    printf("Received one message from client %d to client %d: %s\n", client_id, recipient_id, message_text);
    if (recipient_id < 0 || recipient_id >= clients_count || recipient_id == client_id) {
        printf("Invalid recipient ID\n");
        return;
    }
    message response;
    response.type = ONE_MSG_TYPE;
    response.client_id = client_id;
    response.timestamp = time(NULL);
    sprintf(response.text, "[%d][%s]: %s\n", client_id, ctime(&response.timestamp), message_text);
    msgsnd(clients_queue_ids[recipient_id], &response, sizeof(message) - sizeof(long), 0);
}

void handle_stop_message(int client_id) {
    printf("Received stop message from client %d\n", client_id);
    clients_queue_ids[client_id] = -1;
}

void handle_message(message *msg) {
    switch (msg->type) {
        case STOP_MSG_TYPE:
            handle_stop_message(msg->client_id);
            break;
        case LIST_MSG_TYPE:
            handle_list_request(msg->client_id);
            break;
        case ALL_MSG_TYPE:
            handle_all_message(msg->client_id, msg->text);
            break;
        case ONE_MSG_TYPE:
            handle_one_message(msg->client_id, msg->client_id, msg->text);
            break;
        default:
            printf("Invalid message type\n");
    }
}

int main(void) {
    atexit(remove_queue);
    signal(SIGINT, int_handler);
    printf("Server started, PID: %d\n", getpid());
    int server_queue_id = msgget(SERVER_QUEUE_KEY, IPC_CREAT | 0666);
    if (server_queue_id == -1) {
        perror("msgget error");
        exit(1);
    }
    while (running) {
        message msg;
        if (msgrcv(server_queue_id, &msg, sizeof(message) - sizeof(long), 0, IPC_NOWAIT) == -1) {
            if (errno != ENOMSG) {
                perror("msgrcv error");
                exit(1);
            }
        } else {
            handle_message(&msg);
        }
        int i;
        for (i = 0; i < MAX_CLIENTS; i++) {
            if (clients_queue_ids[i] != -1) {
                if (msgrcv(clients_queue_ids[i], &msg, sizeof(message) - sizeof(long), 0, IPC_NOWAIT) == -1) {
                    if (errno != ENOMSG) {
                        perror("msgrcv error");
                        exit(1);
                    }
                } else {
                    handle_message(&msg);
                }
            }
        }
    }
    return 0;
}