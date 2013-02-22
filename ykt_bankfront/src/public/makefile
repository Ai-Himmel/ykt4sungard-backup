include $(HOME)/src/mak/mkstand.mak
TARGET=libbccpub.a
LIBDIR=../../lib

SOURCE= \
pubfunc\
express\
mutex\
mypub\
mac\
profile\
d3des\
Base64\
md5\
profile


# =====================================================
all:$(TARGET)
	mv $(TARGET) $(LIBDIR)
	@echo $(TARGET) is moved to $(LIBDIR)
	
clean:
	rm -f *.o $(TARGET)


$(TARGET):$(SOURCE:=.o)
	$(AR) $(ARFLAGS) $@ $(SOURCE:=.o)
