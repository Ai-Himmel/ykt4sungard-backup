# Makefile for systems with GNU tools
CC 	=	g++32
UNAME = $(shell uname)
INSTALL	=	install

ifeq ($(UNAME),SunOS)
CFLAGS = -D_DRTP_V4 -D_MT -DSUNOS -O2 -Wall -D_GDBTEST_ -DDEBUG
LIBS = -lstdc++ -lpthread -lsocket -lnsl -lm
APPLIBS = -L../lib/solaris  -ldrtplib -lkcrypto -lboost_thread -lbccpub
else
CFLAGS = -D_DRTP_V4 -D_MT -DDEBUG -O2 -ggdb -Wall -D_GDBTEST_ 
LIBS = -lstdc++ -lpthread
APPLIBS = -L../lib/linux  -ldrtplib -lkcrypto -lboost_thread -lbccpub
endif

LINK_FLAGS= -ldl
LD_CFLAGS= -fpic
INCLUDES = -I../include
VPATH = ../include
BIN = test

SOURCES=$(wildcard *.c)

ifeq ($SOURCES,)
SOURCES=$(shell ls *.c)
endif

OBJS=$(SOURCES:.c=.o)

ifeq ($OBJS,)
OBJS =\
testkccutil.o
endif

OTHEROBJS=\
../src/kcc_util.o\
../src/kcc_conf.o\
../src/md5.o


.SUFFIXES:
.SUFFIXES:.c .o

$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $(LINK_FLAGS) $(INCLUDES) $(LIBS) -o $@ $(OBJS) $(OTHEROBJS) $(APPLIBS)

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) $(LD_CFLAGS) $<

build-obj:$(OBJS)

.PHONY: clean
clean:
	@rm *.o $(BIN)

