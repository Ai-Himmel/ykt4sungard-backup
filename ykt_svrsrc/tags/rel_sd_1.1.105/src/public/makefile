TARGET=libbccpub.a
LIBDIR=../../lib
DB2PATH=/home/db2inst1/sqllib
INCLD= -I./ -I../public -I$(HOME)/ykt/src/include -I$(HOME)/ykt/src/include/dbincl -I$(DB2PATH)/include
UNAME=$(shell uname)

ifeq ($(UNAME),SunOS)
	CC=gcc
	CXX=g++
	LIBS=-lstdc++ -lpthread -lsocket -lnsl -lm
	CCFLAGS= -D_DRTP_V4 -D_MT -Wall -O2 -DSUNOS
	CXXFLAGS= -D_DRTP_V4 -D_MT -Wall -O2 -DSUNOS
endif
ifeq ($(UNAME),HP-UX)
	CC=aCC
	CXX=aCC
	LIBS=-lpthread
	CCFLAGS= -mt -D_DRTP_V4  -DUNIX -DHP_UX -Agcc -AC99
	CXXFLAGS= -mt -D_DRTP_V4 -DUNIX -DHP_UX -Ag++
endif
ifeq ($(UNAME),Linux)
	CC=gcc
	LIBS=-lstdc++ -lpthread -lnsl
	CCFLAGS= -D_DRTP_V4 -D_MT -Wall -O2
	CXXFLAGS= -D_DRTP_V4 -D_MT -Wall -O2
endif

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

ifeq ($(UNAME),SunOS)
	AR=/usr/ccs/bin/ar
else
	AR=/usr/bin/ar
endif

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
	$(CXX) -c $(CXXFLAGS) $(INCLD) $*.cpp
	
.sqc.c:
	db2 connect to $(YKT_DBNAME) user $(YKT_USER) using $(YKT_PWD)
	db2 prep $< output $@ bindfile using $*.bnd
	db2 bind $*.bnd
	db2 connect reset
