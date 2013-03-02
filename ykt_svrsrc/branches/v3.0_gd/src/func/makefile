include $(HOME)/ykt/src/db/mkstand.mak
#TARGET=$(YKT_BU) rcv_acc blksvr dayendbala start
TARGET=$(YKT_BU) posdtlacc dayendbala statdiffacc colposdtl chkaccsvr ca_gzdxc_gdct

SOURCE= \
ksbu\
busqc\
F240000\
F240157\
F240001\
F240002\
F240003\
F240004\
F240005\
F240006\
F240007\
F240008\
F240009\
F240010\
F240011\
F240020\
F240021\
F240022\
F700000\
F700001\
F700002\
F820001\
F820002\
F820003\
F820005\
F820101\
F820102\
F820103\
F820105\
F820108\
F820110\
F820111\
F820112\
F820113\
F820114\
F820301\
F820302\
F820311\
F820321\
F820331\
F820332\
F820341\
F820342\
F820350\
F820351\
F820352\
F820402\
F820404\
F820405\
F820502\
F820511\
F820522\
F841600\
F841601\
F841602\
F841605\
F841609\
F841610\
F841700\
F842001\
F842501\
F843335\
F843340\
F843341\
F843342\
F843343\
F843351\
F843355\
F843356\
F843357\
F843358\
F843359\
F843360\
F843361\
F843362\
F843363\
F843364\
F843370\
F843371\
F843373\
F845000\
F845001\
F846101\
F846102\
F846103\
F846104\
F846105\
F846106\
F846107\
F846108\
F846109\
F846110\
F846111\
F846112\
F846115\
F846116\
F846201\
F846202\
F846203\
F846204\
F846205\
F846301\
F846302\
F846303\
F846305\
F846307\
F846308\
F846309\
F846310\
F846311\
F846312\
F846313\
F846314\
F846315\
F846316\
F846317\
F846318\
F846320\
F846321\
F846322\
F846329\
F846330\
F846331\
F846332\
F846333\
F846334\
F846335\
F846336\
F846337\
F846338\
F846401\
F846402\
F846403\
F846404\
F846501\
F846502\
F846600\
F846601\
F846602\
F846603\
F846605\
F846606\
F846701\
F846702\
F846703\
F846704\
F846705\
F846706\
F846707\
F846708\
F846709\
F846710\
F846711\
F846712\
F846713\
F846714\
F846715\
F846716\
F846717\
F846718\
F846719\
F846720\
F846721\
F846722\
F847102\
F847111\
F847127\
F847130\
F847131\
F847132\
F847136\
F847137\
F847150\
F847166\
F847173\
F847185\
F847198\
F847226\
F847227\
F847228\
F847229\
F847230\
F847231\
F847232\
F847302\
F847310\
F847316\
F847317\
F847318\
F847319\
F847320\
F847321\
F848004\
F848250\
F848251\
F848252\
F848254\
F848255\
F848256\
F848257\
F848258\
F848259\
F848260\
F848264\
F848265\
F848266\
F848267\
F848268\
F848269\
F848270\
F848273\
extchk\
F849001\
F849002\
F849003\
F849004\
F849005\
F849006\
F849007\
F850000\
F850001\
F850002\
F850003\
F850005\
F850006\
F850007\
F850010\
F860001\
F930001\
F930002\
F930003\
F930004\
F930005\
F930006\
F930007\
F930008\
F930009\
F930010\
F930011\
F930012\
F930013\
F930014\
F930015\
F930016\
F930017\
F930018\
F930019\
F930020\
F930021\
F930022\
F930031\
F930033\
F930034\
F930036\
F930037\
F930039\
F930046\
F930051\
F930052\
F930053\
F930054\
F930055\
F930056\
F930057\
F930058\
F930060\
F930061\
F930066\
F930071\
F930098\
F930099\
F930101\
F930121\
F930122\
F930123\
F940005\
F950001\
F950002\
F950003\
F950004\
F950005\
F950006\
F950007\
F950008\
F950009\
F950010\
F950029\
F950031\
F950032\
F950040\
F950041\
F950043\
F950050\
F950051\
F950052\
F950053\
F950055\
F950065\
F950099\
F950100\
F950101\
F950102\
F950998\
F950999\
payment\
F900121\
F900122\
F900150\
F900172\
F900173\
F900174\
F900175\
F900210\
F900212\
F900213\
F900230\
F900240\
F900260\
F900281\
F900282\
F900283\
F9212\
F9213\
F960001

#F820121\
#F848250\

#F820122\
#F820123\
#F820124\
#F820131\
#F820132\
#F820133\
#F820134\

BLKSVR_SRC= \
blksvr \
blkhndr


BINDIR=$(HOME)/ykt/bin

#APLIBS=-L $(HOME)/ykt/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
#-lrijndael
APLIBS=-L$(HOME)/ykt/lib -lstdc++ -lbccpub -lxpack -lbupubs  -lpubdb  -lrijndael

# =====================================================
all:$(TARGET)

clean:
	@rm -f *.o *.bnd *.lis tp*
	@.gend.sh

ksbu.o:ksbu.cpp BDFunc.inl

$(YKT_BU):$(SOURCE:=.o) $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(SOURCE:=.o) $(APLIBS) $(LIBSUDF)
	mv $@ $(BINDIR)
bucron:bucron.o busqc.o F847321.o $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ bucron.o busqc.o F847321.o $(APLIBS) $(LIBSUDF)
	strip bucron
	mv $@ $(BINDIR)
posdtlacc:posdtlacc.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	mv posdtlacc $(BINDIR)
statdiffacc:statdiffacc.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	mv statdiffacc $(BINDIR)
colposdtl:colposdtl.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	mv colposdtl $(BINDIR)
chkaccsvr:chkaccsvr.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	mv chkaccsvr $(BINDIR)
ca_gzdxc_gdct:ca_gzdxc_gdct.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	mv ca_gzdxc_gdct $(BINDIR)
blksvr:$(BLKSVR_SRC:=.o) $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -ldl -o $@ $(BLKSVR_SRC:=.o) $(APLIBS) $(LIBSUDF)
	mv blksvr $(BINDIR)
syn_db:syn_db.o $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	mv $@ $(BINDIR)
infosync:infosync.o
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	mv $@ $(BINDIR)
start:start.o
	$(CXX) $(CCFLAGS) -o $@ $@.o
	mv start   $(BINDIR)
dayendbala:dayendbala.o $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@  $@.o $(APLIBS) $(LIBSUDF)
	mv dayendbala $(BINDIR)

getbaladata:getbaladata.o $(HOME)/ykt/lib/libpubdb.a $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libbupubs.a $(HOME)/ykt/lib/libxpack.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@  $@.o $(APLIBS) $(LIBSUDF)
	strip $@
	mv $@ $(BINDIR)
	
install:
	mv ykt_bu $(BINDIR)
	mv rcv_acc $(BINDIR)
	mv bala $(BINDIR)
