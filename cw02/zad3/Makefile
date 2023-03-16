LIB=dirsize
COMP=gcc
CFLAGS=-Wall
TEST=
MAIN=dir_used_memory.c

all:
	make library
	make main

library: $(LIB).c
	$(COMP) $(CFLAGS) -c $(LIB).c
	ar cr $(LIB).a $(LIB).o

main: $(MAIN)
	$(COMP) $(CFLAGS) $(MAIN) -o dir_size.exe -L . $(LIB).a

clean:
	rm -f *.o *.gch *.a *.so *.exe *.test.txt