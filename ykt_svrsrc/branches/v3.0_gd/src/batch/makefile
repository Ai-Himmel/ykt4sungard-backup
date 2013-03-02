include $(HOME)/ykt/src/db/mkstand.mak
#TARGET=$(YKT_BU) rcv_acc blksvr dayendbala start
TARGET=dataclean

SOURCE= 

BINDIR=$(HOME)/ykt/bin

#APLIBS=-L $(HOME)/ykt/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
APLIBS=-L$(HOME)/ykt/lib -lstdc++ -lxpack -lbupubs -lbccpub -lpubdb

# =====================================================
all:$(TARGET)

clean:
	@rm -f *.o *.bnd *.lis tp*
	@.gend.sh
dataclean:dataclean.o $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@  $@.o $(APLIBS) $(LIBSUDF)
	mv dataclean $(BINDIR)
install:
	mv dataclean $(BINDIR)
