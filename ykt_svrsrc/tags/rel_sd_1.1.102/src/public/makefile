
TARGET=libbccpub.a
LIBDIR=../../lib
DB2PATH=/opt/IBM/db2/V8.1
INCLD= -I./ -I../public -I$(HOME)/ykt/src/include -I$(HOME)/ykt/src/include/dbincl -I$(DB2PATH)/include

SOURCE= \
express\
logfile\
mutex\
mypub\
mac\
profile\
slist\
cpack\
tcp\
svrlink\
pubfunc\
budb\
dbfunc\
dbfunc_foo\
account\
d3des\
Base64

CC=gcc
UNAME=`uname`
ifeq ($(UNAME),SunOS)
	AR=/usr/ccs/bin/ar
else
	AR=/usr/bin/ar
endif

CCFLAGS=-D_DRTP_V4 -D_MT -DSUNOS  -Wall -DSUN  -O2
ARFLAGS=-r

# =====================================================
all:$(TARGET)
	mv $(TARGET) $(LIBDIR)
	@echo $(TARGET) is moved to $(LIBDIR)
	
clean:
	@./.clean
	rm -f *.o $(TARGET)

.SUFFIXES: .o .c .cpp .sqc

$(TARGET):$(SOURCE:=.o)  $(LIBDIR)/libpubdb.a
	$(AR) $(ARFLAGS) $@ $(SOURCE:=.o)
.c.o:
	$(CC) -c $(CCFLAGS) $(INCLD)  $*.c

.cpp.o:
	$(CC) -c $(CCFLAGS) $(INCLD) $*.cpp
.sqc.c:
	db2 connect to $(YKT_DBNAME) user $(YKT_USER) using $(YKT_PWD)
	db2 prep $< output $@ bindfile using $*.bnd
	db2 bind $*.bnd
	db2 connect reset
