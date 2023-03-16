LIB=dirsize
COMP=gcc
CFLAGS=-Wall
TEST=
MAIN=dir_used_memory_all_tree.c

all:
	make main2

library: $(LIB).c
	$(COMP) $(CFLAGS) -c $(LIB).c
	ar cr $(LIB).a $(LIB).o

main: $(MAIN)
	$(COMP) $(CFLAGS) $(MAIN) -o dir_size.exe -L . $(LIB).a

main2: $(MAIN)
	$(COMP) $(CFLAGS) $(MAIN) -o dir_size.exe

clean:
	rm -f *.o *.gch *.a *.so *.exe *.test.txt