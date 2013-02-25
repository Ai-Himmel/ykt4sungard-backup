# Makefile for libbupub.so libbupubs.a
# .so search path:
# LD_LIBRARY_PATH   :   Solaris; UnixWare; IRIX; Alpha OSF; FreeBSD; Linux
# LIBPATH:      AIX
# SHLIB_PATH:       HPUX
# AIX version

.SUFFIXES: .cpp .o

CPP = g++34

CPPDEFS = -DLINUX -DBUPUBLIB -Wall -ggdb

INC= -I../buinc

.cpp.o:
	$(CPP) -c $(CPPDEFS) -g $(INC) $< -o $@

OBJS = bupub.o bdefine.o logfile.o mypub.o profile.o slist.o stdafx.o svrlink.o tcp.o

ALL: libbupub.so libbupubs.a clean

libbupub.so: $(OBJS)
#	$(CPP) -shared $(OBJS) -L../lib -lpackc -o $@
	$(CPP) -shared $(OBJS) -o $@


libbupubs.a: $(OBJS)
	ar -rv $@ $(OBJS)
	mv  $@ ../../lib


#AIX:
#   mv $@ $(LIBPATH)
#LINUX;Solaris;UnixWare;IRIX;Alpha OSF; FreeBSD:
#   mv $@ $(LD_LIBRARY_PATH)
#HPUX:
#   mv $@ $(SHLIB_PATH)

clean:
	rm -f *.o
