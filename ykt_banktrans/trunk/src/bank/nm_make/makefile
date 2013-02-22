include $(HOME)/bank/src/bank/mkstand.mak
TARGET=libbi2.so
LIBDIR=../../../lib/
BINDIR=../../../bin/
INCLUDES=-I./ -I$(HOME)/bank/src/include $(INCLD)
SOURCE= \

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


libbi2.so:bank_ccb_nm.lo 
	$(CXX) $(LDFLAGS_SHLIB) -o $@  bank_ccb_nm.lo  $(THIRDDIR)


.cpp.o:
	$(CXX) -c $(INCLUDES) $(CFLAGS) $<

.cpp.lo:
	$(CXX) -c $(INCLUDES) $(CFLAGS) $(CFLAGS_SHLIB) $< && mv $*.o $*.lo
