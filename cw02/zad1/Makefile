LIB=translate
COMP=gcc
CFLAGS=-Wall
TEST=time_test.c
MAIN=translate_main.c

all:
	make library
	make time_test
	make main

library: $(LIB).c
	$(COMP) $(CFLAGS) -c $(LIB).c
	ar cr $(LIB).a $(LIB).o

time_test: $(TEST) $(LIB).a
	$(COMP) $(CFLAGS) $(TEST) -o translate_test.exe -L . $(LIB).a

main: $(MAIN) $(LIB).a
	$(COMP) $(CFLAGS) $(MAIN) -o translate.exe -L . $(LIB).a

clean:
	rm -f *.o *.gch *.a *.so *.exe *.test.txt