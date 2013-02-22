# vim: tabstop=4
TARGET=libfiletrans.a
CC=gcc34
CXX=g++34
CXXFLAGS=-fPIC
LDFLAGS=-shared
LIBS=-Llib -lbccclt
MV=mv
RM=rm
ARFLAGS=-r
AR=ar

SOURCES=\
libfiletrans


.SUFFIXES: .cpp .o

all:$(TARGET)

libfiletrans.so:$(SOURCES:=.o)
	$(CXX) -o $@ $(SOURCES:=.o) $(LIBS) $(LDFLAGS)

libfiletrans.a:$(SOURCES:=.o)
	$(AR) $(ARFLAGS) $@ $(SOURCES:=.o)

install:$(TARGET)
	$(MV) $(TARGET) ../dist/

clean:
	$(RM) -f *.o $(TARGET)

.cpp.o:
	$(CXX) -c $*.cpp $(CXXFLAGS)		
