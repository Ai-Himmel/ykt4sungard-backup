include ./mkstand.mak
LIBDIR=$(HOME)/ykt/lib
TARGET=libpubdb.a

SOURCE=\
esqlc\
accdtl\
shopacc\
inneracc\
netacc\
bankcard\
dpsoper\
dpsoperpos\
dpsshoppos\
dictionary\
shoppos\
shoppostmp\
machinecode\
opersite\
cardver\
cardnochange\
cardaccdiff\
transtype\
cfgfee\
cfgshopfee\
cfgtrans\
seqnoctl\
branch\
card\
carddtl\
cardistdtl\
transdtl\
cardtype\
cardright\
custtype\
paymentdtl\
posdtl\
posdtltmp\
posseqno\
cfgpayment\
cfgver\
cfgsplit\
dept\
device\
devicetmp\
drdevcardlist\
drevtdtl\
drhday\
drtime\
drgrp\
drdtl\
drweektime\
drhdaytime\
drgrpmem\
drtimgrp\
drgrpoperrht\
drdevweek\
drdevtime\
drdevhday\
drdevtg\
moduleauth\
account\
transcode\
shop\
subsystem\
subsyspara\
syskey\
phydevice\
authcard\
customer\
custtmp\
subject\
operdtl\
operright\
site\
subsidy\
syspara\
feetype\
cardbitmap\
cardbook\
mealtype\
shopmeal\
operator\
area\
specialty\
cfgrakeoff\
purse\
tasklog\
plantask\
devmntr\
bankchkbill\
msglist\
pushtask\
vtransdtl\

#bankcomp\
#cadlosinf\
#difftransfer
#vrpttolg
#spefee\
#rptactive\
#rptbanktransfer\
#rptcardbalance\
#rpterr\
#rptoper\
#rptrichdebt\
#rptshpbalance\
#rpttranscomp
#v1rptcar\
#v2rpterr\
#vrpttot\
#vrptoper\
#vshpdptfee\
#vrptactive\
#cutinfoupd\
#cardlist\
#writefailed\
#device_collect_log
#cutrelation\
#cutrltntmp\
#grpcashrpt\
#opgroups\
#thirdpartsys\
#subdept\
#subdept_v\
#subjbal\
#subsidytmp\
#shoptree\
#rptdevm\
#vrptdevm\
#grpcashrpt\
#blacksht\
#devmntr\
#attend\
#rptfile\
#actdaysum\
#trdcdshp\
#trdcode\



# =====================================================
all:$(TARGET)
	@echo $(TARGET) is up to date

clean:
	@./.clean.sh
	@rm -f  $(PUBIND)/dbincl/*stru.h
	@rm -f *.o $(TARGET) *stru.h  *.c *.bnd tp* *.lis

install:$(TARGET)
	@cp *_stru.h $(PUBIND)/dbincl
	@./.gendb.sh
	@cp $(TARGET) $(LIBDIR)
	@echo $(TARGET) is moved to $(LIBDIR)

$(TARGET):$(SOURCE:=.o)
	$(AR) $(ARFLAGS) $@ $(SOURCE:=.o)
