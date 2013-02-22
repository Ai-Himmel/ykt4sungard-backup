include $(HOME)/bank/src/bank/mkstand.mak
TARGET=libbi.so
LIBDIR=../../lib
INCLUDES=-I./ -I$(HOME)/bank/src/include
SOURCE= \

#THIRDDIR=$(HOME)/bank/src/thirdlib/Third_MAC.o
THIRDDIR=
OBJS = \
	bank_gd.lo\
	iso_8583.lo\
	stdfunc.lo\
	tcp.lo\
	iso8583.lo
#   bank_gd.lo
CFLAGS_SHLIB = -fPIC
LDFLAGS_SHLIB =-shared
CFLAGS=-DLINUX

.SUFFIXES:.c .o .cpp .lo .h
# =====================================================
all:$(TARGET)
	mv $(TARGET) $(LIBDIR)
	@echo $(TARGET) is moved to $(LIBDIR)
	

clean:
	rm -f *.o $(TARGET) *.lo


$(TARGET):$(SOURCE:=.o) $(OBJS)  
	$(CXX) $(LDFLAGS_SHLIB) -o $@  $(OBJS) $(SOURCE:=.o) $(THIRDDIR)


#	$(AR) $(ARFLAGS) $@ $(SOURCE:=.o)
.cpp.o:
	$(CXX) -c $(INCLUDES) $(CFLAGS) $<

.cpp.lo:
	$(CXX) -c $(INCLUDES) $(CFLAGS) $(CFLAGS_SHLIB) $< && mv $*.o $*.lo
