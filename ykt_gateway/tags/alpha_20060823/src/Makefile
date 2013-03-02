CC=gcc
CXX=g++
TARGET=gwmain

LIBS=-L../lib/linux  -lpthread -lACE -lboost_thread-gcc-mt -lboost_filesystem-gcc-mt -ldrtplib -lkcrypto -lbccpub
INCLUDE=-I../include/
CFLAGS=
CXXFLAGS=-DLINUX -DKSG_HD_DEV_SUPPORT -DX86_ARCH -fpermissive

#SOURCES=$(wildcard *.cpp)
SOURCES=\
CIniFile\
devfactory\
device\
DRTPHelper\
executor\
F8583\
ftplib\
ksgateway\
logcallback\
md5c\
des\
netutil\
osutil\
pubfunc\
rijndael-alg-fst\
rijndael-api-fst\
scheduler\
stdafx\
taskdef\
taskqueue\
thread\
999dev/999devnode\
devnode/devnode\
hddev/hddevnode\
hddev/hdsvr\
impl/execimpl\
impl/schdimpl\
unix/gwmain\
tinystr\
tinyxml\
tinyxmlerror\
tinyxmlparser


STATIC_OBJS=$(SOURCES:=.o)

.SUFFIXES:.c .cpp .o .h .inc

.PHONY: clean

$(TARGET):$(STATIC_OBJS)
	echo $^
	$(CXX) -o $(TARGET) $^ $(LIBS)

clean:
	@ $(RM) -f $(TARGET) *.o */*.o

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDE) -c -o $@ $<


