//
// Created by ciastek on 27.04.23.
//

#ifndef SYSOP_MESSAGE_BUFFOR_H
#define SYSOP_MESSAGE_BUFFOR_H

#include "project_salon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>


// czasy robienia fryzur tablica powinna być długości HAIRSTYLES_N
const int hairstyles_times[HAIRSTYLES_N] = {1,2,3,4,5};

#endif //SYSOP_MESSAGE_BUFFOR_H
