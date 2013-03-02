include $(HOME)/ykt/src/db/mkstand.mak
TARGET=libbccpub.a
LIBDIR=../../lib

SOURCE= \
express\
mutex\
mypub\
mac\
profile\
pubfunc\
dbfunc\
dbfunc_foo\
account\
d3des\
Base64\
md5\
rsa\
rijndael-alg-fst\
rijndael-api-fst\
callbu


# =====================================================
all:$(TARGET)
	mv $(TARGET) $(LIBDIR)
	@echo $(TARGET) is moved to $(LIBDIR)
	
clean:
	@./.clean
	rm -f *.o $(TARGET)


$(TARGET):$(SOURCE:=.o)  $(LIBDIR)/libpubdb.a
	$(AR) $(ARFLAGS) $@ $(SOURCE:=.o)
