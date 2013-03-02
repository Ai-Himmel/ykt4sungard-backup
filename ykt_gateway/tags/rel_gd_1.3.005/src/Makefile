########################################################################
##   ykt_agent Makefile 
# 	 一卡通网关
# 	 copyright 2006-2007 SunGard Kingstar Corp.
# 	 Auth 汤成 (Cash) 
# 	 mailto : cheng.tang@kingstargroup.com
########################################################################

##  configure for gcc/g++ compiler
CC=gcc
CXX=g++

##  target name
TARGET=gwmain

##  debug flag
DEBUG = 1

## bitendian config
# 1 : for little endian 
# 2 : for big endian
BITENDIAN = 1


########################################################################
#  DO NOT modify the following configure
#
OS=$(shell uname)
LIBS=-L../lib/linux -ldrtplib -lboost_thread -lkcrypto -lbccpub -lcurl
#
INCLUDE=-I../include/

CFLAGS=
CXXFLAGS=-DKSG_HD_DEV_SUPPORT -D_DRTP_V4 -D_MT -DNO_LONGLONG_TYPE -pthread -fpermissive \
	-Wno-ctor-dtor-privacy
LDFLAGS=-lstdc++ -lpthread -lboost_thread-gcc-mt -lACE -lboost_filesystem-gcc-mt

ifeq ($(DEBUG),1)
CFLAGS += -g
CXXFLAGS += -g
endif

ifeq ($(BITENDIAN),1)
CXXFLAGS += -DX86_ARCH
CFLAGS += -DX86_ARCH
else
CXXFLAGS += -DSPARC_ARCH
CFLAGS += -DSPARC_ARCH
endif

ifeq ($(OS),Linux)
CFLAGS+=-DLINUX
CXXFLAGS+=-DLINUX
endif

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
tinyxmlparser\
iptool\
proactor_def\
task_scheduler\
hundure/gcu3devnode\
hundure/hundure_def\
hundure/ncu3devnode\
hundure/rac2000devnode


STATIC_OBJS=$(SOURCES:=.o)

.SUFFIXES:.c .cpp .o .h .inc

.PHONY: clean

$(TARGET):$(STATIC_OBJS)
	echo $^
	$(CXX) -o $(TARGET) $^ $(LDFLAGS) $(LIBS)
	-mkdir -p ../bin/nix
	mv $@ ../bin/nix/

clean:
	@ $(RM) -f $(TARGET) *.o */*.o

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDE) -c -o $@ $<


