include ../db/mkstand.mak
INCLDIR=-I../buinc

CC=g++

CPPDEFS = -DSUNOS -Wall

OBJS=PackC.o PackHandle.o XPack.o

all:libxpack.a

libxpack.a: $(OBJS)
	$(AR) -rv libxpack.a $(OBJS)
	mv  libxpack.a ../../lib

#.SUFFIXES: .cpp .o

#.cpp.o:
#	$(CC) -c -g $(CPPDEFS) $(INCLDIR) $< -o $@

clean:
	rm *.o

