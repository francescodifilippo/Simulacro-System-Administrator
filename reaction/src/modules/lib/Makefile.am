CC = gcc
YFLAGS = -d
AM_CFLAGS = -g -O2 -rdynamic -c 
AR = /usr/bin/ar
ARFLAGS = cr
LIBNAME = libbsmod.a

noinst_PROGRAMS=managebuffer.o
managebuffer.o : managebuffer.c
	$(CC) $(AM_CFLAGS) managebuffer.c -o managebuffer.o
	$(AR) $(ARFLAGS) $(LIBNAME) managebuffer.o
clean:
	rm -f *.o *.a
