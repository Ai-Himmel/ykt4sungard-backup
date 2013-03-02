include $(HOME)/bank/src/mak/mkstand.mak
SERVER=bank_gateway

BUSOURCE= \
bank_gateway


BINDIR=$(HOME)/bank/bin

#APLIBS=-L $(HOME)/bank/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
#APLIBS=-L $(HOME)/bank/lib -lstdc++ -lxpack -lksshmt -lbupubs -lbccpub -lpubdb -lbi -lbccclt
APLIBS=-L $(HOME)/bank/lib -lstdc++ -lxpack -lbupubs -lbccpub  -lbccclt

# =====================================================
all:$(SERVER)

clean:
	@rm -f *.o *.bnd *.lis tp*


$(SERVER):$(BUSOURCE:=.o) $(HOME)/bank/lib/libbccpub.a
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(BUSOURCE:=.o) $(APLIBS)
	mv $@ $(BINDIR)

