randlibsw.so: randlibsw.c
	$(CC) $(CFLAGS) randlibsw.c -fPIC -shared -o randlibsw.so
randlibhw.so: randlibhw.c
	$(CC) $(CFLAGS) randlibhw.c -fPIC -shared -o randlibhw.so
randmain: randmain.o randcpuid.o
	$(CC) $(CFLAGS) randmain.o randcpuid.o -ldl -Wl,-rpath=$(PWD) -o randmain
