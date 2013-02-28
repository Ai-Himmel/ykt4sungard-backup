include $(HOME)/ykt/src/db/mkstand.mak
TARGET=shopsync smsvr

BINDIR=$(HOME)/ykt/bin

APLIBS=-L$(HOME)/ykt/lib -lstdc++ -lbccpub -lxpack -lbupubs  -lpubdb -lcurl

# =====================================================

all : $(TARGET)

shopsync:shopsync.o $(HOME)/ykt/lib/libpubdb.a $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libbupubs.a $(HOME)/ykt/lib/libxpack.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@  $@.o $(APLIBS) $(LIBSUDF)
	strip $@
	mv $@ $(BINDIR)

smsvr:smsvr.o $(HOME)/ykt/lib/libpubdb.a $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libbupubs.a $(HOME)/ykt/lib/libxpack.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@  $@.o $(APLIBS) $(LIBSUDF)
	strip $@
	mv $@ $(BINDIR)
	
clean:
	@rm -f *.o *.eC *.lis *.log

