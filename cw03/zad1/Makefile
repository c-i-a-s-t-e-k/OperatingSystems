LIB=
COMP=gcc
CFLAGS=-Wall
TEST=
MAIN=create_proceses.c

all:
	make main

library: $(LIB).c
	$(COMP) $(CFLAGS) -c $(LIB).c
	ar cr $(LIB).a $(LIB).o

main: $(MAIN)
	$(COMP) $(CFLAGS) $(MAIN) -o proceses.exe

clean:
	rm -f *.o *.gch *.a *.so *.exe *.test.txt