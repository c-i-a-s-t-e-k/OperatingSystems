#pragma once
#include <stdbool.h>

char *create_grid();
void destroy_grid(char *grid);
void draw_grid(char *grid);
void init_grid(char *grid);
bool is_alive(int row, int col);
char *update_grid(char *src);
void *thead_cell(void* arg);
void create_resources();
void clan_resources();