LIB=reverse
COMP=gcc
CFLAGS=-Wall
TEST=time_test.c
MAIN=reverse_main.c

all:
	make library
	make main
	make tests

library: $(LIB).c
	$(COMP) $(CFLAGS) -c $(LIB).c
	ar cr $(LIB).a $(LIB).o

main: $(MAIN)
	$(COMP) $(CFLAGS) $(MAIN) -o reverse.exe -L . $(LIB).a

tests: $(TEST)
	$(COMP) $(CFLAGS) $(TEST) -o reverse_time_test.exe -L . $(LIB).a


clean:
	rm -f *.o *.gch *.a *.so *.exe *.test.txt