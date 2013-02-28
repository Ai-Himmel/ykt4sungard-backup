include $(HOME)/ykt/src/db/mkstand.mak
TARGET=bubank

SOURCE= \
ksbu\
busqc\
bankfunc\
F5000\
F5001\
F5002\
F5003\
F5004\
F5005\
F5101\
F5102

INCLD+=-I../buinc


BINDIR=$(HOME)/ykt/bin

#APLIBS=-L $(HOME)/ykt/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
APLIBS=-L$(HOME)/ykt/lib -lstdc++  -lbccpub -lpubdb -lxpack -lbupubs -lrt

# =====================================================
all:$(TARGET)

clean:
	@rm -f *.o *.bnd *.lis tp*
#注意下一行不能修改,为了保证每次编译时版本的编译日期信息正确,强制要求只要有程序改动,则ksbu.cpp每次都要编译(闻剑添加)
ksbu.o:$(SOURCE:=.o)

$(TARGET):$(SOURCE:=.o) $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(SOURCE:=.o) $(APLIBS) $(LIBSUDF)
	strip $@
	mv $@ $(BINDIR)
	