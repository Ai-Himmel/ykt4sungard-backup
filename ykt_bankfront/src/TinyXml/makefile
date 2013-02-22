include $(HOME)/src/mak/mkstand.mak
TARGET=libtinyxml.a
LIBDIR=../../lib

SOURCE= \
tinystr\
tinyxml\
tinyxmlerror\
tinyxmlparser

# =====================================================
all:$(TARGET)
	mv $(TARGET) $(LIBDIR)
	@echo $(TARGET) is moved to $(LIBDIR)
	
clean:
	@./.clean
	rm -f *.o $(TARGET)
$(TARGET):$(SOURCE:=.o)
	$(AR) $(ARFLAGS) $@ $(SOURCE:=.o)
