include ./mkstand.mak
LIBDIR=$(HOME)/ykt/lib
TARGET=libpubdb.a

SOURCE=\
esqlc\
apply\
cardinfo\
operaccdtl\
cardbatch\
cardfactory\
cardmadeinfo\
merchdev\
merchbal\
merchday\
cardledger\
cardsnctl\
cardseqnoctl\
devnoctl\
unit\
unitcfg\
blacklist\
makecardlist\
cardnoctl\
dpsdtl\
paydtl\
bookset\
actpara\
operauth\
period\
vchtype\
vchnoctl\
voucher\
vchctrl\
vchentry\
subjday\
subjmonth\
subjyear\
subjmap\
settlectl\
mealtype\
merch\
pkg\
pkgfile\
refno\
pos\
bank\
bankchkdtl\
bankchkfile\
banktransdtl\
front\
frontcfg\
branch\
cfgver\
dictionary\
machinecode\
opersite\
transtype\
seqnoctl\
card\
carddtl\
cardtype\
cardphytype\
posdtl\
cfgsplit\
moduleauth\
transcode\
subsystem\
subsyspara\
syskey\
phydevice\
customer\
subject\
operdtl\
site\
syspara\
cardbitmap\
operator\
area\
psamcard\
keys\
paypara\
merchpara\
merchwork


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
	@./.cleandb.sh
	@rm -f  $(PUBIND)/dbincl/*stru.h
	@rm -f *.o $(TARGET) *stru.h  *.c *.bnd tp* *.lis

install:$(TARGET)
	@cp *_stru.h $(PUBIND)/dbincl
	@./.gendb.sh
	@cp $(TARGET) $(LIBDIR)
	@echo $(TARGET) is moved to $(LIBDIR)

$(TARGET):$(SOURCE:=.o)
	$(AR) $(ARFLAGS) $@ $(SOURCE:=.o)
