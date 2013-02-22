# Makefile for systems with GNU tools
CC 	=	g++
INSTALL	=	install
#CFLAGS = -D_DRTP_V4 -D_MT -DSUNOS -ggdb -Wall -D_GDBTEST_ -DDEBUG
CFLAGS = -D_DRTP_V4 -D_MT -DDEBUG -O2 -Wall -D_GDBTEST_ 
LINK_FLAGS= -ldl
LD_CFLAGS= -fpic
INCLUDES = -I../include
#LIBS = -lstdc++ -lpthread -lsocket -lnsl -lm
LIBS = -lstdc++ -lpthread
APPLIBS = -L../lib/linux  -ldrtplib -lkcrypto -lboost_thread -lbccpub
#APPLIBS = -L../lib/solaris  -ldrtplib -lkcrypto -lboost_thread -lbccpub
VPATH = ../include
BIN = ../bin/yktcf

OBJS = \
drtpcall.o \
servers.o \
parseconf.o \
kcc_conf.o \
kcc_util.o \
main.o \
md5.c	\

.SUFFIXES:
.SUFFIXES:.c .o

$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $(LINK_FLAGS) $(INCLUDES) $(LIBS) -o $@ $(OBJS) $(APPLIBS)

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) $(LD_CFLAGS) $<

build-obj:$(OBJS)

.PHONY: clean
clean:
	-rm *.o

