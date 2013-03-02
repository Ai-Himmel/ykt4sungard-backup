include $(HOME)/bank/src/mak/mkstand.mak
TARGET=libbi.so
LIBDIR=../../../lib/
BINDIR=../../../bin/
INCLUDES=-I./ -I$(HOME)/bank/src/include $(INCLD)
SOURCE= \
tcp_update\
iso8583\
stdfunc\
bank_boc_dlmu
#THIRDDIR=$(HOME)/bank/src/thirdlib/Third_MAC.o
THIRDDIR=


CFLAGS_SHLIB = -fPIC
LDFLAGS_SHLIB =-shared
CFLAGS=-DLINUX

.SUFFIXES:.c .o .cpp .lo .h
# =====================================================
all:$(TARGET)
	cp $(TARGET) $(LIBDIR)
	mv $(TARGET) $(BINDIR)
	@echo $(TARGET) is moved to $(LIBDIR)
	

clean:
	rm -f *.o $(TARGET) *.lo


libbi.so:$(SOURCE:=.lo) 
	$(CXX) $(LDFLAGS_SHLIB) -o $@  $(SOURCE:=.lo)  $(THIRDDIR)

.cpp.o:
	$(CXX) -c $(INCLUDES) $(CFLAGS) $<

.cpp.lo:
	$(CXX) -c $(INCLUDES) $(CFLAGS) $(CFLAGS_SHLIB) $< && mv $*.o $*.lo
