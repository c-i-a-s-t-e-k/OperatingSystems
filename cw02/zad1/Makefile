LIB=translate
COMP=gcc
CFLAGS=-Wall
TEST=time_test.c

all:
	make library
	make time_test

library: $(LIB).c
	$(COMP) $(CFLAGS) -c $(LIB).c
	ar cr $(LIB).a $(LIB).o

time_test: $(TEST)
	$(COMP) $(CFLAGS) $(TEST) -o translate_test.exe -L . $(LIB).a

clean:
	rm -f *.o *.gch *.a *.so *.exe *.test.txt