#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdbool.h>
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITERATIONS 64

int main()
{
	srand(time(NULL));
	setlocale(LC_CTYPE, "");
	initscr(); // Start curses mode
    create_resources();

	char *foreground = create_grid();
	char *background;
	char *tmp;

	init_grid(foreground);

	for(int i = 0; i < ITERATIONS; i++)
	{
		draw_grid(foreground);
		usleep(500 * 1000);

		// Step simulation
        background = update_grid(foreground);
		tmp = foreground;
		foreground = background;
		background = tmp;
	}

	endwin(); // End curses mode
    clan_resources();
	return 0;
}
