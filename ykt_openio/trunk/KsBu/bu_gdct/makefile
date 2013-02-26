TARGET=gdct_bu
INCLDIR=-I../ -I./

CC=g++

CPPDEFS = -Wall -D_DYNAMIC_LOAD
LIBS=-L../ -lbupubs -lxpack

OBJS=\
F851001\
F851002\
F851003\
gdctpub\
LoadDll\
bufunc

PUBS=\
../ksbu\
../tcpsock

all: $(TARGET) clear

gdct_bu: $(OBJS:=.o) $(PUBS:=.o)
	$(CC)  $(OBJS:=.o) ksbu.o tcpsock.o -o $@ $(LIBS)
	mv $@ ../../bin/

.SUFFIXES: .cpp .o

.cpp.o:
	$(CC) -c -g $(CPPDEFS) $(INCLDIR) $*.cpp

clear:
	rm *.o

