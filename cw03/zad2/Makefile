LIB=
COMP=gcc
CFLAGS=-Wall
TEST=
MAIN=execls.c

all:
	make main

library: $(LIB).c
	$(COMP) $(CFLAGS) -c $(LIB).c
	ar cr $(LIB).a $(LIB).o

main: $(MAIN)
	$(COMP) $(CFLAGS) $(MAIN) -o ls.exe

clean:
	rm -f *.o *.gch *.a *.so *.exe *.test.txt