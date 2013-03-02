# Makefile for libbupub.so libbupubs.a
# .so search path:
# LD_LIBRARY_PATH   : 	Solaris; UnixWare; IRIX; Alpha OSF; FreeBSD; Linux
# LIBPATH:		AIX
# SHLIB_PATH:   	HPUX
# AIX version
include ../db/mkstand.mak

#.SUFFIXES: .cpp .o

#CPP = g++

#CPPDEFS = -DSUNOS -DBUPUBLIB -Wall -ggdb

INC= -I../buinc

#.cpp.o:
#	$(CPP) -c $(CPPDEFS) -g $(INC) $< -o $@

OBJS = bupub.o bdefine.o logfile.o mypub.o profile.o slist.o stdafx.o svrlink.o tcp.o

#ALL: libbupub.so libbupubs.a clean
ALL:libbupubs.a

libbupub.so: $(OBJS)
#	g++ -shared $(OBJS) -L../lib -lpackc -o $@
	g++ -shared $(OBJS) -o $@


libbupubs.a: $(OBJS)
	$(AR) -rv $@ $(OBJS)
	mv libbupubs.a ../../lib


#AIX:
#	mv $@ $(LIBPATH)
#LINUX;Solaris;UnixWare;IRIX;Alpha OSF; FreeBSD:
#	mv $@ $(LD_LIBRARY_PATH)
#HPUX:
#	mv $@ $(SHLIB_PATH)

clean:
	rm -f *.o
