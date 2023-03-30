LIB=lock_for_argv
COMP=gcc
CFLAGS=-Wall
TEST=test.c
MAIN=
CATCHER=catcher.c
SENDER=sender.c

all:
	make main

library: $(LIB).c
	$(COMP) $(CFLAGS) -c $(LIB).c
	ar cr $(LIB).a $(LIB).o

main: $(MAIN)
	$(COMP) $(CFLAGS) $(CATCHER) -o catcher.exe
	$(COMP) $(CFLAGS) $(SENDER) -o sender.exe

tests: $(MAIN)
	$(COMP) $(CFLAGS) $(TEST) -o test_find.exe -L . $(LIB).a

clean:
	rm -f *.o *.gch *.a *.so *.exe *.test.txt