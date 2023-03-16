COMP=gcc
CFLAGS=-Wall
LIB=libzad1

all:
	make static_library
	make shared_library

static_library: $(LIB).c
	$(COMP) $(CFLAGS) -c $(LIB).c
	ar cr $(LIB).a $(LIB).o

shared_library: $(LIB).c
	$(COMP) $(CFLAGS) -c -fPIC $(LIB).c
	$(COMP) $(CFLAGS) -shared -o $(LIB).so $(LIB).o

clean:
	rm -f *.o *.gch *.a *.so