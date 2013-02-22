include $(HOME)/bank/src/db/mkstand.mak
BANKBU=ykt_bu

BUSOURCE= \
ksbu\
F250001\
F250002\
F250003\
F260001\
F260002\
F900077

GUARD=bankguard

GUARDSRC= \
bankguard

COMMON_SRC=\
shem\
transinfo

BINDIR=$(HOME)/bank/bin

#APLIBS=-L $(HOME)/bank/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
#APLIBS=-L $(HOME)/bank/lib -lstdc++ -lxpack -lksshmt -lbupubs -lbccpub -lpubdb -lbi -lbccclt
APLIBS=-L $(HOME)/bank/lib -lstdc++ -lxpack -lbupubs -lbccpub -lbi -lbccclt

# =====================================================
all:$(BANKBU) $(GUARD)

clean:
	@rm -f *.o *.bnd *.lis tp*

ksbu.o:ksbu.cpp BDFunc.inl

$(BANKBU):$(BUSOURCE:=.o) $(COMMON_SRC:=.o) $(HOME)/bank/lib/libbccpub.a 
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(COMMON_SRC:=.o) $(BUSOURCE:=.o) $(APLIBS)
	mv $@ $(BINDIR)

$(GUARD):$(GUARDSRC:=.o) $(COMMON_SRC:=.o) $(HOME)/bank/lib/libbccpub.a 
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(GUARDSRC:=.o) $(COMMON_SRC:=.o) $(APLIBS)
	mv $@ $(BINDIR)

install:
	mv bank_bu $(BINDIR)
	mv rcv_acc $(BINDIR)
	mv bala $(BINDIR)
