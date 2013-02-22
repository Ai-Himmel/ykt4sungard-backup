include $(HOME)/src/mak/mkstand.mak
BANKBU=bfbu

BUSOURCE= \
ksbu\
httppost\
myparameters\
mycpack\
F1001\
F1002\
F1003\
F1004\
F1005\
F1006

COMMON_SRC=

BINDIR=$(HOME)/bin

#APLIBS=-L $(HOME)/bank/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
#APLIBS=-L $(HOME)/bank/lib -lstdc++ -lxpack -lksshmt -lbupubs -lbccpub -lpubdb -lbi -lbccclt
#APLIBS=-L $(HOME)/bankfront/lib -lstdc++ -lxpack -lbupubs -lbccpub -lbi -lbccclt
APLIBS=-L $(HOME)/lib -lstdc++ -lbupubs -lbccpub -lxpack  -lcurl -ltinyxml

# =====================================================
all:$(BANKBU) $(GUARD)

clean:
	@rm -f *.o *.bnd *.lis tp*

ksbu.o:ksbu.cpp BDFunc.inl

$(BANKBU):$(BUSOURCE:=.o) $(COMMON_SRC:=.o) $(HOME)/lib/libbccpub.a 
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(COMMON_SRC:=.o) $(BUSOURCE:=.o) $(APLIBS)
	mv $@ $(BINDIR)

install:
	mv $(BANKBU) $(BINDIR)
