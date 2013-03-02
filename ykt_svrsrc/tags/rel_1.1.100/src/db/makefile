TARGET=libpubdb.a
LIBDIR=$(HOME)/ykt/lib
DB2PATH=/opt/IBM/db2/V8.1
PUBIND=$(HOME)/ykt/src/include
INCLD= -I./ -I../public -I$(HOME)/ykt/src/include -I$(HOME)/ykt/src/include/dbincl -I$(DB2PATH)/include
ACT=$(HOME)/ykt/bin/dbcrt
CC=gcc
AR=/usr/ccs/bin/ar

CCFLAGS=-D_DRTP_V4 -D_MT -DSUNOS  -Wall -O2
ARFLAGS=-r

SOURCE=\
pubdb\
account\
actdaysum\
blacksht\
card\
cardstrut\
cadlosinf\
cfgsplit\
cfgtxfee\
dept\
device\
difftransfer\
meslist\
rptactive\
rptbanktransfer\
rptcardbalance\
rpterr\
rptoper\
rptrichdebt\
rptshpbalance\
rpttranscomp\
shp\
shppos\
shpposlog\
spefee\
subbalance\
subupd\
subsys\
syskey\
savdtl\
tradelog\
warrant\
phydevice\
authcard\
customer\
customtmp\
coshis\
subject\
cuttypefee\
tradeserial\
rcvdtl\
histrlog\
histrserial\
v1rptcar\
v2rpterr\
vrpttot\
vrptoper\
vshpdptfee\
vrptactive\
cutinfoupd\
cardlist\
txdtl\
operright\
groupmem\
group\
devworktime\
doorholiday\
doordevhld



#vrpttolg
# =====================================================
all:$(TARGET)
	@echo $(TARGET) is up to date
	
clean:
	@.clean.sh
	@rm -f  $(PUBIND)/dbincl/*stru.h
	@rm -f *.o $(TARGET) *stru.h  *.c *.bnd
	
install:$(TARGET)
	@cp *_stru.h $(PUBIND)/dbincl
	@.gendb.sh
	@cp $(TARGET) $(LIBDIR)
	@echo $(TARGET) is moved to $(LIBDIR)

.SUFFIXES: .o .c .cpp .act .sqc

$(TARGET):$(SOURCE:=.o)
	$(AR) $(ARFLAGS) $@ $(SOURCE:=.o)

.c.o:
	$(CC) -c $(CCFLAGS) $(INCLD) $(INCLUDE) $*.c

.cpp.o:
	$(CC) -c $(CCFLAGS) $(INCLD) $*.cpp
	
.sqc.c:
	db2 connect to $(YKT_DBNAME) user $(YKT_USER) using $(YKT_PWD)
	db2 prep $< output $@ bindfile using $*.bnd
	db2 bind $*.bnd
	db2 connect reset
	
.act.sqc:
	$(ACT)   $<
