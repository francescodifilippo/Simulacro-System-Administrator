CC = gcc
YFLAGS = -d
AM_CFLAGS = -g -O2 -rdynamic -c 
LDFLAG= -lbsmod -L../lib 
CP = cp
noinst_PROGRAMS=MOD_BOOLREG.so
MOD_BOOLREG.so: MOD_BOOLREG.o
	$(CC) -shared MOD_BOOLREG.o $(LDFLAG) -o MOD_BOOLREG.so
	$(CP) MOD_BOOLREG.so ../../
	
MOD_BOOLREG.o: MOD_BOOLREG.c
	$(CC) $(AM_CFLAGS) MOD_BOOLREG.c -o MOD_BOOLREG.o
