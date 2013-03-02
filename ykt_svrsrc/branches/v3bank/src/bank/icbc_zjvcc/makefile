include $(HOME)/bank/src/mak/mkstand.mak
TARGET=libbi2.so
LIBDIR=../../../lib/
BINDIR=../../../bin/
INCLUDES=-I./ -I$(HOME)/bank/src/include $(INCLD)
SOURCE= bank_icbc_zjvcc tcp_update

THIRDDIR=

CFLAGS_SHLIB =-fPIC 
LDFLAGS_SHLIB =-shared
CFLAGS=-DLINUX

.SUFFIXES:.c .o .cpp .lo .h
# =====================================================
all:$(TARGET)
	cp $(TARGET) $(LIBDIR)

clean:
	rm -f $(TARGET) $(THIRDDIR) *.lo

$(TARGET):$(SOURCE:=.lo) $(THIRDDIR) 
	$(CXX) $(LDFLAGS_SHLIB) -o $@ $^ 

.cpp.lo:
	$(CXX) -c $(INCLUDES) $(CFLAGS) $(CFLAGS_SHLIB) $< -o $@
