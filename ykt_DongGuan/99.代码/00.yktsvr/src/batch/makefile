include $(HOME)/ykt/src/db/mkstand.mak
TARGET=busposdeal balasrv

SOURCE= 

BINDIR=$(HOME)/ykt/bin

#APLIBS=-L $(HOME)/ykt/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
APLIBS=-L$(HOME)/ykt/lib -lstdc++  -lbccpub -lpubdb -lxpack -lbupubs

# =====================================================
all:$(TARGET)

clean:
	@./.cleanbatch.sh
	@rm -f *.o *.bnd *.lis tp*
dataclean:dataclean.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@  $@.o $(APLIBS) $(LIBSUDF)
	strip $@	
	mv $@  $(BINDIR)
balasrv:balasrv.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@  $@.o $(APLIBS) $(LIBSUDF)
	strip $@	
	mv $@  $(BINDIR)
dayendbala:dayendbala.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@  $@.o $(APLIBS) $(LIBSUDF)
	strip $@	
	mv $@  $(BINDIR)
posdtlacc:posdtlacc.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	strip $@	
	mv $@ $(BINDIR)
colposdtl:colposdtl.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	strip $@	
	mv $@ $(BINDIR)
transpackacc:transpackacc.o $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	strip $@	
	mv $@ $(BINDIR)
bankchksvr:bankchksvr.o $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF) -lbccclt
	strip $@	
	mv $@ $(BINDIR)

busposdeal:busposdeal.o  $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF) -lbccclt -lfiletrans
	strip $@	
	mv $@ $(BINDIR)
	cp busposparse.py genbusresult.py $(BINDIR)
	