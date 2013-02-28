include $(HOME)/ykt/src/db/mkstand.mak
TARGET=libbccpub.a
LIBDIR=../../lib

SOURCE= \
daysettle\
actfunc\
acctrans\
transfunc\
callbu\
bufunc\
mac\
pubfunc\
dbfunc\
d3des\
Base64\
md5\
rsa\
rijndael-alg-fst\
rijndael-api-fst\
gnudes\
cpucard\
yktclt


# =====================================================
all:$(TARGET)
	mv $(TARGET) $(LIBDIR)
	@echo $(TARGET) is moved to $(LIBDIR)
	
clean:
	@./.cleanpublic.sh
	rm -f *.o $(TARGET) tp*


$(TARGET):$(SOURCE:=.o)  $(LIBDIR)/libpubdb.a
	$(AR) $(ARFLAGS) $@ $(SOURCE:=.o)
