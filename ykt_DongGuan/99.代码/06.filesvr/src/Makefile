TARGET=filesvr
CXX=g++
CC=gcc34
LDFLAGS=
CXXFLAGS=-Wall -g
LIBS=-L../lib -lpthread -lbccsvr -ldrtplib -lboost_thread -lkcrypto
CP=/bin/cp
RM=/bin/rm

SOURCES=\
filesvr\
funclist\
mypub\
profile\
F9001\
F950998\
F950999

.SUFFIXES: .cpp 

all:$(TARGET) install

$(TARGET):$(SOURCES:=.o)
	$(CXX) -o $@ $(SOURCES:=.o) $(LIBS)

install:$(TARGET)
	$(CP) $(TARGET) ../bin/

clean:
	$(RM) -f *.o $(TARGET)

.cpp.o:
	$(CXX) -c $*.cpp $(CXXFLAGS)

