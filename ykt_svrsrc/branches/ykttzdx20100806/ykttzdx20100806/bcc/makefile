BINFILE=ksbcc dbfshow test64
SOURCE= \
bulinkthread\
bulistenthread\
dbf\
DRTPRecvThread\
drtp_di\
logfile\
mutex\
MWThread\
ForwardThread\
PushThread\
sysgvars\
WThread\
cpack\
mypub\
profile\
slist\
stdafx\
tcp\
KSLog
 
# й╣ож

APPDIR= ./

APINCL= -I$(APPDIR)
#DB2PATH=/home/db2inst1/sqllib

LIBS=-lstdc++ -lpthread
APLIBS=-L./ -ldrtplib -lkcrypto -lboost_thread
INCLD= -I./
CC= g++
#CCFLAGS=-DVIEWMSG
CCFLAGS= -D_DRTP_V4 -D_MT -DSUNOS -g -Wall

# =====================================================
all:$(BINFILE)
	mv ksbcc ksbcc64
	@echo        "all" is updated.

ksbcc:ksbcc.o $(SOURCE:=.o)
	rm -f ${APPDIR}$@
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o ${APPDIR}$@ $@.o $(SOURCE:=.o) $(APLIBS)

dbfshow:dbfshow.o dbf.o
	rm -f ${APPDIR}$@
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o ${APPDIR}$@ $@.o dbf.o 
	
test64:test64.o KSLog.o mutex.o mypub.o
	rm -f ${APPDIR}$@
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o ${APPDIR}$@ $@.o KSLog.o mutex.o mypub.o

.SUFFIXES:.c
.c.o:
	$(CC) -c $(CCFLAGS) $(INCLD) $*.c

.SUFFIXES:.cpp
.cpp.o:
	$(CC) -c $(CCFLAGS) $(INCLD) $*.cpp

# =====================================================
