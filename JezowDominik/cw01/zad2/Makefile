COMP=gcc
CFLAGS=-Wall
LIB=libzad1
REPL=replzad2.c

all:
	make static_library
	make shared_library
	make exe_static
	make exe_shared
	make exe_dlopen

static_library: $(LIB).c
	$(COMP) $(CFLAGS) -c $(LIB).c
	ar cr $(LIB).a $(LIB).o

shared_library: $(LIB).c
	$(COMP) $(CFLAGS) -c -fPIC $(LIB).c
	$(COMP) $(CFLAGS) -shared -o $(LIB).so $(LIB).o

exe_static: $(LIB).c $(REPL)
	$(COMP) $(CFLAGS) $(REPL) -o wc_repl_static.exe -L . $(LIB).a

exe_shared: $(LIB).c $(REPL)
	$(COMP) $(CFLAGS) -o wc_repl_shared.exe -L . $(LIB).so

exe_dlopen: $(LIB).c $(REPL)
	$(COMP) $(CFLAGS) $(REPL) -o wc_repl_dlopen.exe -ldl -D USE_DLL


clean:
	rm -f *.o *.gch *.a *.so *.exe test.in *.txt