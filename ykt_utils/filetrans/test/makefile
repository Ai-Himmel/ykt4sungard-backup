# vim: tabstop=4
TARGET=test
CC=gcc34
CXX=g++34
CXXFLAGS=
LDFLAGS=
LIBS=-L../lib -L../dist -lpthread -lfiletrans -ldrtplib -lboost_thread -lbccclt
MV=mv
RM=rm
ARFLAGS=-r
AR=ar
CP=cp

SOURCES=\
test

.SUFFIXES: .cpp .o

all:$(TARGET) install

install:$(TARGET)
	$(CP) ../lib/libbccclt.so ../bin/
	$(MV) $(TARGET) ../bin/

test:$(SOURCES:=.o)
	$(CXX) -o $@ $(SOURCES:=.o) $(LIBS) $(LDFLAGS)

clean:
	$(RM) -f *.o $(TARGET)

.cpp.o:
	$(CXX) -c $*.cpp $(CXXFLAGS)		
