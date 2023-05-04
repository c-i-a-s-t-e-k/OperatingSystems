#include "grid.h"
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <ncurses.h>
#include <signal.h>
#include <unistd.h>

const int grid_width = 30;
const int grid_height = 30;
pthread_t *threads;
char *tmp_src;
char *tmp_dst;

void create_resources(){
    threads = malloc(sizeof(pthread_t)*grid_width * grid_height);
    tmp_dst = malloc(sizeof(char)*grid_width * grid_height);
}

void clan_resources(){
    free(threads);
    free(tmp_dst);
}

char *create_grid()
{
    return malloc(sizeof(char) * grid_width * grid_height);
}

void handle_signal(int sig) {}

void *thead_cell(void* arg) {
    int i = ((int*)arg)[0];
    int j = ((int*)arg)[1];
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("SIGACTION");
    }
    int *signum = malloc(sizeof(int));
    while (true){
        sigwait(&set, signum);
        if(*signum == SIGUSR1) {
            tmp_dst[i * grid_width + j] = is_alive(i, j);
        } else {
            free(signum);
            perror("wrong signal");
        }
    }
}

void destroy_grid(char *grid)
{
    free(grid);
}

void draw_grid(char *grid)
{
    for (int i = 0; i < grid_height; ++i)
    {
        // Two characters for more uniform spaces (vertical vs horizontal)
        for (int j = 0; j < grid_width; ++j)
        {
            if (grid[i * grid_width + j])
            {
                mvprintw(i, j * 2, "■");
                mvprintw(i, j * 2 + 1, " ");
            }
            else
            {
                mvprintw(i, j * 2, " ");
                mvprintw(i, j * 2 + 1, " ");
            }
        }
    }

    refresh();
}

void init_grid(char *grid)
{
    for (int i = 0; i < grid_width * grid_height; ++i)
        grid[i] = rand() % 2 == 0;
    int arg[2];
    for (int i = 0; i < grid_width * grid_height; ++i){
        arg[0] = i / grid_width;
        arg[1] = i % grid_width;
        pthread_create(&threads[i], NULL, thead_cell, arg);
    }
}

bool is_alive(int row, int col)
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            int r = row + i;
            int c = col + j;
            if (r < 0 || r >= grid_height || c < 0 || c >= grid_width)
            {
                continue;
            }
            if (tmp_src[grid_width * r + c])
            {
                count++;
            }
        }
    }

    if (tmp_src[row * grid_width + col])
    {
        if (count == 2 || count == 3)
            return true;
        else
            return false;
    }
    else
    {
        if (count == 3)
            return true;
        else
            return false;
    }
}

char *update_grid(char *src)
{
    tmp_src = src;
    for(int i = 0; i < grid_height * grid_width; ++i)
        pthread_kill(threads[i], SIGUSR1);
    return tmp_dst;
}