CC = gcc
YFLAGS = -d
AM_CFLAGS = -g -O2 -rdynamic -c 
LDFLAG= -lbsmod -L../lib 
CP = cp
noinst_PROGRAMS=MOD_CONNECT.so
MOD_CONNECT.so: MOD_CONNECT.o
	$(CC) -shared MOD_CONNECT.o $(LDFLAG) -o MOD_CONNECT.so
	$(CP) MOD_CONNECT.so ../../
	
MOD_CONNECT.o: MOD_CONNECT.c
	$(CC) $(AM_CFLAGS) MOD_CONNECT.c -o MOD_CONNECT.o
