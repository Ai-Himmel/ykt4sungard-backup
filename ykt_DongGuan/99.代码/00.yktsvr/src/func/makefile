include $(HOME)/ykt/src/db/mkstand.mak
TARGET=yktbu

SOURCE= \
ksbu\
busqc\
F1001\
F2001\
F2002\
F2004\
F2005\
F2006\
F2007\
F2008\
F2009\
F2010\
F2011\
F2012\
F2013\
F2014\
F2015\
F2016\
F2017\
F2018\
F2019\
F2020\
F2021\
F2022\
F2023\
F2024\
F2025\
F2026\
F2027\
F2029\
F2030\
F2031\
F2032\
F2033\
F2034\
F2035\
F2036\
F2037\
F2038\
F3001\
F3002\
F820301\
F820302\
F820311\
F820321\
F820331\
F820332\
F820341\
F820350\
F820351\
F820352\
F820402\
F820404\
F820405\
F820501\
F820502\
F820511\
F820522\
F846101\
F846109\
F846312\
F846322\
F846501\
F846703\
F846705\
F846706\
F846707\
F846709\
F846711\
F846714\
F846715\
F846716\
F846719\
F846730\
F846731\
F846732\
F846733\
F846734\
F846735\
F846801\
F846802\
F846736\
F846737\
F847150\
F850005\
F850035\
F850040\
F850041\
F850050\
F850060\
F850061\
F850062\
F850063\
F850064\
F850065\
F850066\
F850070\
F850071\
F850072\
F851001\
F851002\
F851003\
F851004\
F950990\
F950999\
F990099

BINDIR=$(HOME)/ykt/bin

#APLIBS=-L $(HOME)/ykt/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
APLIBS=-L$(HOME)/ykt/lib -lstdc++  -lbccpub -lpubdb -lxpack -lbupubs

# =====================================================
all:$(TARGET)

clean:
	@./.cleanfunc.sh
	@rm -f *.o *.bnd *.lis tp*
#注意下一行不能修改,为了保证每次编译时版本的编译日期信息正确,强制要求只要有程序改动,则ksbu.cpp每次都要编译(闻剑添加)
ksbu.o:$(SOURCE:=.o)

yktbu:$(SOURCE:=.o) $(HOME)/ykt/lib/libbccpub.a $(HOME)/ykt/lib/libpubdb.a
	$(CXX) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(SOURCE:=.o) $(APLIBS) $(LIBSUDF)
	strip $@
	mv $@ $(BINDIR)
yktsvrmon:yktsvrmon.o
	$(CXX) $(CCFLAGS) -o $@ $@.o
	strip $@	
	mv yktmon   $(BINDIR)
