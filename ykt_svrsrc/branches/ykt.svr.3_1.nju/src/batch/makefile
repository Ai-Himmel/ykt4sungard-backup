include $(HOME)/ykt/src/db/mkstand.mak
TARGET=posdtlacc colposdtl dayendbala dataclean statdiffacc nm_bank_acccheck nm_bank_acccheck ahut_bank_acccheck getbaladata  waterdtlacc

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
dayendbala:dayendbala.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@  $@.o $(APLIBS) $(LIBSUDF)
	strip $@	
	mv $@  $(BINDIR)
posdtlacc:posdtlacc.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	strip $@	
	mv $@ $(BINDIR)
waterdtlacc:waterdtlacc.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	strip $@	
	mv $@ $(BINDIR)
getbaladata:getbaladata.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	strip $@	
	mv $@ $(BINDIR)
statdiffacc:statdiffacc.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	strip $@
	mv $@ $(BINDIR)
colposdtl:colposdtl.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	strip $@	
	mv $@ $(BINDIR)
ahut_bank_acccheck:ahut_bank_acccheck.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	strip $@	
	mv $@ $(BINDIR)
nm_bank_acccheck:nm_bank_acccheck.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	strip $@	
	mv $@ $(BINDIR)
nj_bank_acccheck:nj_bank_acccheck.o $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $@.o $(APLIBS) $(LIBSUDF)
	strip $@	
	mv $@ $(BINDIR)
transdtlrev:$(TRANSDTLREV_SRC:=.o) $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(TRANSDTLREV_SRC:=.o) $(APLIBS) $(LIBSUDF)
	strip $@	
	mv $@ $(BINDIR)
