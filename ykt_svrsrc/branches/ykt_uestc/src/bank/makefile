include $(HOME)/ykt/src/db/mkstand.mak
BANKBU=bank_bu

BUSOURCE= \
budb\
bdefine\
mypub\
shem\
stdafx\
fdsvrall\
bankdb\
transinfo\
bank\
do_subsidy\
F900077

GUARD=bank_guard
GUARDSRC= \
budb\
bankguard\
shem\
bankdb\
bank

# =====================================================
all:$(BANKBU) $(GUARD)

clean:
	@rm -f *.sqc *.sqC *.o *.bnd *.lis tp* $(BANKBU) $(GUARD)
	

$(GUARD):$(GUARDSRC:=.o)
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(GUARDSRC:=.o) $(APLIBS) $(LIBSUDF)

$(BANKBU):$(BUSOURCE:=.o)
	$(CC) $(CCFLAGS) $(INCLD) $(LIBS) -o $@ $(BUSOURCE:=.o) $(APLIBS) $(LIBSUDF)
