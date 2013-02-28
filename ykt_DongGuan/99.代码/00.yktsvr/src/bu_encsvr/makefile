include $(HOME)/ykt/src/db/mkstand.mak
TARGET=buencsvr

CCFLAGS+=-g

SOURCE= \
ksbu\
F1001\
F1002\
F1003\
encsvrfunc



BINDIR=$(HOME)/ykt/bin

#APLIBS=-L $(HOME)/ykt/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
APLIBS=-L$(HOME)/ykt/lib -lstdc++ -lbupubs -lxpack

# =====================================================
all:$(TARGET)

clean:
	@rm -f *.o *.bnd *.lis tp*
#注意下一行不能修改,为了保证每次编译时版本的编译日期信息正确,强制要求只要有程序改动,则ksbu.cpp每次都要编译(闻剑添加)
ksbu.o:$(SOURCE:=.o)

$(TARGET):$(SOURCE:=.o) $(HOME)/ykt/lib/libbccpub.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(SOURCE:=.o) $(APLIBS) $(LIBSUDF)
	strip $@
	mv $@ $(BINDIR)
	