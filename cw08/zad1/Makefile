CC = gcc
CFLAGS = -Wall

all: life
	
life: grid.c life.c
	$(CC) $(CFLAGS) -lpthread grid.c life.c -o life -lncursesw
	
clean:
	rm -f life
