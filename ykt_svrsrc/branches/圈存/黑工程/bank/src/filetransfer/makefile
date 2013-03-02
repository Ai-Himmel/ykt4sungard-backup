include $(HOME)/bank/src/mak/mkstand.mak
TARGET=filetransbu

SOURCE=\
ksbu\
bufunc\
FPutFile

ORATESTSRC=\
esqlc\
oratest

BINDIR=$(HOME)/bank/bin

APLIBS=-L$(HOME)/bank/lib -lbi2 -lstdc++ -lxpack -lbupubs -lbccpub -lbccclt

# =====================================================
all:$(TARGET)

clean:
	@rm -f *.o tp*
filetransbu:$(SOURCE:=.o) 
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@  $(SOURCE:=.o)  $(APLIBS)
	strip $@	
	mv $@  $(BINDIR)
