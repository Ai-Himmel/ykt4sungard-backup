include $(HOME)/ykt/src/db/mkstand.mak
TARGET=libbccpub.a
LIBDIR=../../lib

SOURCE= \
acctrans\
callbu\
mac\
pubfunc\
dbfunc\
dbfunc_foo\
interfacefunc\
doorfunc\
d3des\
Base64\
md5\
rsa\
rijndael-alg-fst\
rijndael-api-fst\
gnudes\
cpucard


# =====================================================
all:$(TARGET)
	mv $(TARGET) $(LIBDIR)
	@echo $(TARGET) is moved to $(LIBDIR)
	
clean:
	@./.clean
	rm -f *.o $(TARGET) tp*


$(TARGET):$(SOURCE:=.o)  $(LIBDIR)/libpubdb.a
	$(AR) $(ARFLAGS) $@ $(SOURCE:=.o)
