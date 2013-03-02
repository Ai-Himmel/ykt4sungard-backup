include $(HOME)/bank/src/mak/mkstand.mak
INCLDIR=-I../buinc

CC=g++34

CPPDEFS = -DLINUX -Wall

OBJS=PackC.o PackHandle.o XPack.o

all:libxpack.a

libxpack.a: $(OBJS)
	$(AR) -rv libxpack.a $(OBJS)
	mv -f libxpack.a ../../lib

#.SUFFIXES: .cpp .o

#.cpp.o:
#	$(CC) -c -g $(CPPDEFS) $(INCLDIR) $< -o $@

clean:
	rm -f *.o

