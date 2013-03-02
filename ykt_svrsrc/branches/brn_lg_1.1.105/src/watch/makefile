
TARGET=monitor

SOURCE= \
Monitor\
M800204\
M800702\
M800741\
M800771\
M800781\
M800784



DB2PATH=/opt/IBM/db2/V8.1

CC= gcc
CCFLAGS= -D_DRTP_V4 -D_MT -DSUNOS -g -Wall 

LIBS=-lstdc++ -lpthread -lsocket -lnsl
APLIBS=-L $(HOME)/ykt/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
LIBSUDF= -L$(DB2PATH)/lib -ldb2 -ldb2apie
INCLD= -I./ -I../public -I$(HOME)/ykt/src/include -I$(HOME)/ykt/src/include/dbincl -I$(DB2PATH)/include

# =====================================================
all:$(TARGET)

para:   GlobalParaMonitor.sqc                         
	db2 connect to $(YKT_DBNAME) user $(YKT_USER) using $(YKT_PWD)
	db2 prep GlobalParaMonitor.sqc output GlobalParaMonitor.c bindfile using GlobalParaMonitor.bnd
	db2 bind GlobalParaMonitor.bnd
	db2 connect reset
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS)  -o GlobalParaMonitor

clean:
	@rm -f *.o *.bnd $(TARGET)
install:$(TARGET)
	mv $(TARGET) $(HOME)/ykt/bin
	
.SUFFIXES: .o .c .cpp .sqc

$(TARGET):$(SOURCE:=.o) $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libpubdb.a
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(SOURCE:=.o) $(APLIBS) $(LIBSUDF)

.c.o:
	$(CC) -c $(CCFLAGS) $(INCLD) $*.c

.cpp.o:
	$(CC) -c $(CCFLAGS) $(INCLD) $*.cpp

.sqc.c:
	db2 connect to $(YKT_DBNAME) user $(YKT_USER) using $(YKT_PWD)
	db2 prep $*.sqc output $*.c bindfile using $*.bnd
	db2 bind $*.bnd
	db2 connect reset

        
# =====================================================
