COMP=gcc
CFLAGS=-Wall
IPCFLAGS=-lrt
MAIN=hair_salon.c
TEST=test.c
LIB=
HAIRD=hairdresser.c
CLIENT=client.c

all:
	make main

library: $(LIB).c
	$(COMP) $(CFLAGS) -c $(LIB).c
	ar cr $(LIB).a $(LIB).o

client: $(CLIENT)
	$(COMP) $(CFLAGS) $(CLIENT) -o client.exe $(IPCFLAGS)

hairdresser: $(HAIRD)
	$(COMP) $(CFLAGS) $(HAIRD) -o hairdresser.exe $(IPCFLAGS)

main: $(MAIN)
	make hairdresser
	make client
	$(COMP) $(CFLAGS) $(MAIN) -o salon.exe $(IPCFLAGS)


#tests: $(MAIN)
#	$(COMP) $(CFLAGS) $(TEST) -o test_find.exe -L . $(LIB).a

clean:
	rm -f *.o *.gch *.a *.so *.exe *.test.txt