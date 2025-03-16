CC = gcc
YFLAGS = -d
AM_CFLAGS = -g -O2 -rdynamic -c 
LDFLAG= -lbsmod -L../lib 
CP = cp
noinst_PROGRAMS=MOD_REG.so
MOD_REG.so: MOD_REG.o
	$(CC) -shared MOD_REG.o $(LDFLAG) -o MOD_REG.so
	$(CP) MOD_REG.so ../../
	
MOD_REG.o: MOD_REG.c
	$(CC) $(AM_CFLAGS) MOD_REG.c -o MOD_REG.o
