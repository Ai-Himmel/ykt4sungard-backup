include $(HOME)/bank/src/mak/mkstand.mak
BANKBU=bank_bu

BUSOURCE= \
ksbu\
F2401\
F250001\
F250002\
F250003\
F250004\
F250006\
F260001\
F260002\
F260006\
F270001\
F950996\
F900077

GUARD=bankguard

GUARDSRC= \
bankguard

COMMON_SRC=\
transinfo

BINDIR=$(HOME)/bank/bin

#APLIBS=-L $(HOME)/bank/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
#APLIBS=-L $(HOME)/bank/lib -lstdc++ -lxpack -lksshmt -lbupubs -lbccpub -lpubdb -lbi -lbccclt
APLIBS=-L $(HOME)/bank/lib -lbi -lbi2 -lstdc++ -lxpack -lbupubs -lbccpub -lbccclt
#APLIBS=-L $(HOME)/bank/lib -lbi -lstdc++ -lxpack -lbupubs -lbccpub -lbccclt

# =====================================================     
all:$(BANKBU)

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
