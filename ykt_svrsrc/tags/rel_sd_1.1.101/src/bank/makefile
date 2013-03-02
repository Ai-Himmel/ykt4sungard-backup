
BANKBU=bank_bu

BUSOURCE= \
bdefine\
mypub\
shem\
stdafx\
fdsvrall\
bankdb\
transinfo\
bank\
do_subsidy\
F900077

GUARD=bank_guard
GUARDSRC= \
bankguard\
shem\
bankdb\
bank

DB2PATH=/opt/IBM/db2/V8.1

CC= gcc
CCFLAGS= -D_DRTP_V4 -D_MT -DSUNOS -g -Wall -DDEBUG

LIBS=-lstdc++ -lpthread 
APLIBS=-L $(HOME)/ykt/lib  -lbccpub -lpubdb 
#-ldrtplib -lkcrypto -lboost_thread 
LIBSUDF= -L$(DB2PATH)/lib -ldb2 -ldb2apie
INCLD= -I./ -I../public -I$(HOME)/ykt/src/include -I$(HOME)/ykt/src/include/dbincl -I$(DB2PATH)/include

# =====================================================
all:$(BANKBU) $(GUARD)

clean:
	@rm -f *.o *.bnd $(BANKBU) $(GUARD)
	
.SUFFIXES: .o .c .cpp .sqc .sqC

$(GUARD):$(GUARDSRC:=.o)
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(GUARDSRC:=.o) $(APLIBS) $(LIBSUDF)

$(BANKBU):$(BUSOURCE:=.o)
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(BUSOURCE:=.o) $(APLIBS) $(LIBSUDF)

.c.o:
	$(CC) -c $(CCFLAGS) $(INCLD) $*.c

.cpp.o:
	$(CC) -c $(CCFLAGS) $(INCLD) $*.cpp

.sqc.c:
	db2 connect to ykt user bank using bank
	db2 prep $*.sqc output $*.c bindfile using $*.bnd
	db2 bind $*.bnd
	db2 connect reset

.sqC.cpp:
	db2 connect to ykt user bank using bank
	db2 prep $< output $@ bindfile using $*.bnd 
	db2 bind $*.bnd
	db2 connect reset
        
# =====================================================
