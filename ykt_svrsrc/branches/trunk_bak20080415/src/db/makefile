include ./mkstand.mak
LIBDIR=$(HOME)/ykt/lib
TARGET=libpubdb.a

SOURCE=\
esqlc\
account\
actdaysum\
blacksht\
bankcomp\
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
doorholiday\
subsidy\
subsidytmp\
cursyspara\
feetype\
subslog\
sbparams\
writefailed\
device_collect_log\
shoptree\
cutrelation\
cutrltntmp\
grpcashrpt\
opgroups\
mealtype\
shopmeal\
rptdevm\
vrptdevm\
grpcashrpt\
operator\
operauthcd\
drtimsec\
doorweek\
drhldtim\
doorgrp\
groupmem\
drtimgrp\
drgrprht\
drdevwk\
drdevtmsc\
drdevhld\
drdevtg\
drevent\
subdept\
subdept_v\
area\
thirdpartsys\
speciality\
trdcdshp\
devmntr



#vrpttolg
# =====================================================
all:$(TARGET)
	@echo $(TARGET) is up to date

clean:
	@./.clean.sh
	@rm -f  $(PUBIND)/dbincl/*stru.h
	@rm -f *.o $(TARGET) *stru.h  *.c *.bnd tp* *.lis

install:$(TARGET)
	@cp *_stru.h $(PUBIND)/dbincl
	@cp esqlc.h $(PUBIND)
	@./.gendb.sh
	@cp $(TARGET) $(LIBDIR)
	@echo $(TARGET) is moved to $(LIBDIR)

$(TARGET):$(SOURCE:=.o)
	$(AR) $(ARFLAGS) $@ $(SOURCE:=.o)
