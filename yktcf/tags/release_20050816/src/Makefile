# Makefile for systems with GNU tools
CC 	=	g++
UNAME = $(shell uname)
INSTALL	=	install

ifeq ($(UNAME),SunOS)
CFLAGS = -D_DRTP_V4 -D_MT -DSUNOS -O2 -Wall -D_GDBTEST_ -DDEBUG
LIBS = -lstdc++ -lpthread -lsocket -lnsl -lm
APPLIBS = -L../lib/solaris  -ldrtplib -lkcrypto -lboost_thread -lbccpub
else
CFLAGS = -D_DRTP_V4 -D_MT -DDEBUG -O2 -Wall -D_GDBTEST_ 
LIBS = -lstdc++ -lpthread
APPLIBS = -L../lib/linux  -ldrtplib -lkcrypto -lboost_thread -lbccpub
endif

LINK_FLAGS= -ldl
LD_CFLAGS= -fpic
INCLUDES = -I../include
VPATH = ../include
BIN = ../bin/yktcf

SOURCES=$(wildcard *.c)

ifeq ($SOURCES,)
SOURCES=$(shell ls *.c)
endif

OBJS=$(SOURCES:.c=.o)

ifeq ($OBJS,)
OBJS = \
drtpcall.o \
servers.o \
parseconf.o \
kcc_conf.o \
kcc_util.o \
main.o \
md5.c	
endif

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

