include $(HOME)/bank/src/db/mkstand.mak
BANKBU=ykt_bu

BUSOURCE= \
ksbu\
F250001\
F250002\
F250003\
F250004\
F250006\
F260001\
F260002\
F260006\
F900077

GUARD=bankguard

GUARDSRC= \
bankguard

COMMON_SRC=\
shem\
transinfo

BANK_FRONT_ASY=ZHBankFront

BANKF_FRONT_SRC=\
ZHBankFront\
tcp

BINDIR=$(HOME)/bank/bin

#APLIBS=-L $(HOME)/bank/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
#APLIBS=-L $(HOME)/bank/lib -lstdc++ -lxpack -lksshmt -lbupubs -lbccpub -lpubdb -lbi -lbccclt
APLIBS=-L $(HOME)/bank/lib -lstdc++ -lxpack -lbupubs -lbccpub -lbi -lbccclt
APLIBS2=-L $(HOME)/bank/lib -lstdc++ -lxpack -lbccpub -lbccclt

# =====================================================
all:$(BANKBU) $(GUARD) $(BANK_FRONT_ASY)

clean:
	@rm -f *.o *.bnd *.lis tp*

ksbu.o:ksbu.cpp BDFunc.inl

$(BANKBU):$(BUSOURCE:=.o) $(COMMON_SRC:=.o) $(HOME)/bank/lib/libbccpub.a
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(COMMON_SRC:=.o) $(BUSOURCE:=.o) $(APLIBS)
	mv $@ $(BINDIR)

$(GUARD):$(GUARDSRC:=.o) $(COMMON_SRC:=.o) $(HOME)/bank/lib/libbccpub.a 
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(GUARDSRC:=.o) $(COMMON_SRC:=.o) $(APLIBS)
	mv $@ $(BINDIR)

$(BANK_FRONT_ASY):$(BANKF_FRONT_SRC:=.o) $(HOME)/bank/lib/libbccpub.a
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(BANKF_FRONT_SRC:=.o) $(APLIBS2)
	mv $@ $(BINDIR)
	
install:
	mv bank_bu $(BINDIR)
	mv rcv_acc $(BINDIR)
	mv bala $(BINDIR)
