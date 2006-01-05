AM_YFLAGS = -d
AM_CFLAGS = -g -O2 -rdynamic -pthread  

bin_PROGRAMS = reaction

reaction_LDADD = -lm -ldl
reaction_SOURCES = reaction.c runtime.c \
                  module.c \
                  context.c \
                  lex.l \
                  gram.y \
                  reaction.h \
                  intern.h \
                  gram.h \
                  blib.c \
                  blib.h

clean:
	rm -f *.o *.so
