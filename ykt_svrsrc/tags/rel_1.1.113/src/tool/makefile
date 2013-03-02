
#TARGET=query insert update delete $(SOURCE:=.sqc)
TARGET=testsqc dbcrt
MV=mv
SOURCE= \
testsqc

#F820516
DB2PATH=/opt/IBM/db2/V8.1
FRE=W
CC= gcc
CXX= g++
CCFLAGS= -D_DRTP_V4 -D_MT -DSUNOS  -Wall -ggdb

LIBS=-lstdc++ -lpthread -lsocket -lnsl
APLIBS=-L $(HOME)/ykt/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
LIBSUDF= -L$(DB2PATH)/lib -ldb2 -ldb2apie
INCLD= -I./ -I../public -I$(HOME)/ykt/src/include -I$(HOME)/ykt/src/include/dbincl -I$(DB2PATH)/include

# =====================================================
all:$(TARGET)

clean:
	@rm -f $(SOURCE:=.sqc)	
install:
	cp $(SOURCE:=.sqc) $(WSN)
	#@cp query $(HOME)/fdbin
	#@cp insert $(HOME)/fdbin
	#@cp update $(HOME)/fdbin
	#@cp delete $(HOME)/fdbin

.SUFFIXES: .o .c .cpp .sqc .cfg .del .upd .ins
dbcrt:dbcrt.o
	$(CXX) -o $@ dbcrt.o -lpcrecpp
	$(MV) $@ $(HOME)/ykt/bin
testapp:$$@.o $(HOME)/fdlib/libbccpub.a $(HOME)/fdlib/libpubdb.a
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o  $(LIBSUDF) $(APLIBS)
testacc:$$@.o $(HOME)/fdlib/libbccpub.a $(HOME)/fdlib/libpubdb.a
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o  $(LIBSUDF) $(APLIBS)
testsqc:$$@.o $(HOME)/fdlib/libbccpub.a $(HOME)/fdlib/libpubdb.a
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o  $(LIBSUDF) $(APLIBS)
test_black:$$@.o $(HOME)/fdlib/libbccpub.a $(HOME)/fdlib/libpubdb.a
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o  $(LIBSUDF) $(APLIBS)
db_arr_add:$$@.o $(HOME)/fdlib/libbccpub.a $(HOME)/fdlib/libpubdb.a
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o  $(LIBSUDF) $(APLIBS)
test_char:$$@.o $(HOME)/fdlib/libbccpub.a $(HOME)/fdlib/libpubdb.a
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o  $(LIBSUDF) $(APLIBS)
test_utf8:$$@.o $(HOME)/fdlib/libbccpub.a $(HOME)/fdlib/libpubdb.a
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o  $(LIBSUDF) $(APLIBS)
query:$$@.o 
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o  $(LIBSUDF) $(APLIBS)

.c.o:
	$(CC) -c $(CCFLAGS) $(INCLD) $*.c

.cpp.o:
	$(CXX) -c $(CCFLAGS) $(INCLD) $*.cpp

.sqc.c:
	db2 connect to ykt user db2inst4 using db2inst4
	db2 prep $< output $@ bindfile using $*.bnd
	db2 bind $*.bnd
	db2 connect reset
.cfg.sqc:
	query $<
.ins.sqc:
	insert $<
.upd.sqc:
	update $<
.del.sqc:
	delete $<
# =====================================================
