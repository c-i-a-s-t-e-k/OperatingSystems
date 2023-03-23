LIB=lock_for_argv
COMP=gcc
CFLAGS=-Wall
TEST=test.c
MAIN=find_main.c

all:
	make library
	make main
	make tests

library: $(LIB).c
	$(COMP) $(CFLAGS) -c $(LIB).c
	ar cr $(LIB).a $(LIB).o

main: $(MAIN)
	$(COMP) $(CFLAGS) $(MAIN) -o find.exe -L . $(LIB).a

tests: $(MAIN)
	$(COMP) $(CFLAGS) $(TEST) -o test_find.exe -L . $(LIB).a

clean:
	rm -f *.o *.gch *.a *.so *.exe *.test.txt