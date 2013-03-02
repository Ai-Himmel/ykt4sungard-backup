CC=gcc
CXX=g++
LIBS=-lstdc++ -lpthread
APLIBS=-L $(HOME)/ykt/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
DB2PATH=/opt/ibm/db2/V9.1
PUBIND=$(HOME)/ykt/src/include
PREPCOMP_CXX=proc code=cpp cpp_suffix=cpp maxopencursors=50 MODE=ANSI TYPE_CODE=ANSI CLOSE_ON_COMMIT=NO def_sqlcode=yes dynamic=ANSI define=ESQL_ORA LINES=YES config="$(HOME)/ykt/bin/proccfg.cfg" include="/usr/include"  include="$(ORACLE_HOME)/precomp/public" include="$(ORACLE_HOME)/rdbms/public" include="$(HOME)/ykt/src/include" include="$(HOME)/ykt/src/include/dbincl" include="$(HOME)/ykt/src/public"

PREPCOMP_C=proc maxopencursors=50 MODE=ANSI TYPE_CODE=ANSI CLOSE_ON_COMMIT=NO def_sqlcode=yes dynamic=ANSI define=ESQL_ORA LINES=YES config="$(HOME)/ykt/bin/proccfg.cfg" include="/usr/include"  include="$(ORACLE_HOME)/precomp/public" include="$(ORACLE_HOME)/rdbms/public" include="$(HOME)/ykt/src/include" include="$(HOME)/ykt/src/include/dbincl" include="$(HOME)/ykt/src/public" 

ifeq ($(DBTYPE),DB2)
	INCLD= -I./ -I../public -I$(HOME)/ykt/src/include -I$(HOME)/ykt/src/include/dbincl -I$(DB2PATH)/include
	CCFLAGS=-D_DRTP_V4 -D_MT -DSUNOS  -DESQL_DB2 -Wall -O2
	LIBSUDF=-lstdc++ -L$(DB2PATH)/lib -ldb2 -ldb2apie
else
	INCLD= -I./ -I../public -I$(HOME)/ykt/src/include -I$(HOME)/ykt/src/include/dbincl -I$(ORACLE_HOME)/precomp/public -I$(ORACLE_HOME)/rdbms/public
	CCFLAGS=-D_DRTP_V4 -D_MT -DSUNOS -DESQL_ORA -Wall -O2
	LIBSUDF=-lstdc++ -L$(ORACLE_HOME)/lib -lclntsh \
			`cat $(ORACLE_HOME)/lib/ldflags` \
			`cat $(ORACLE_HOME)/lib/sysliblist`
endif
ACT=$(HOME)/ykt/bin/dbcrt

UNAME=$(shell uname)
ifeq ($(UNAME),SunOS)
	AR=/usr/ccs/bin/ar
else
	AR=/usr/bin/ar
endif
ARFLAGS=-r

.SUFFIXES: .o .c .cpp .sqc .sqC .act .ec .eC

.c.o:
	$(CC) -c $(CCFLAGS) $(INCLD) $(INCLUDE) $*.c

.cpp.o:
	$(CXX) -c $(CCFLAGS) $(INCLD) $*.cpp

.ec.c:
	@if [ $(DBTYPE) = DB2 ]; \
	then \
		db2 connect to $(YKT_DBNAME) user $(YKT_USER) using $(YKT_PWD);\
		db2 prep $< output $@ bindfile using $*.bnd target c;\
		db2 bind $*.bnd;\
		db2 connect reset;\
	else \
		$(PREPCOMP_C) $<; \
	fi

.eC.cpp:
	@if [ $(DBTYPE) = DB2 ]; \
	then \
		db2 connect to $(YKT_DBNAME) user $(YKT_USER) using $(YKT_PWD);\
		db2 prep $< output $@ bindfile using $*.bnd target cplusplus;\
		db2 bind $*.bnd;\
		db2 connect reset;\
	else \
		$(PREPCOMP_CXX) $<; \
	fi

.act.ec:
	$(ACT) $< $@

.sqc.ec:
	@if [ $(DBTYPE) = DB2 ]; \
	then \
		gcc -x c -E -P -DESQL="" -DESQL_DB2 $< > $@; \
	else \
		gcc -x c -E -P -DESQL="" -DESQL_ORA $< > $@; \
	fi

.sqC.eC:
	@if [ $(DBTYPE) = DB2 ]; \
	then \
		gcc -x c++ -E -P -DESQL="" -DESQL_DB2 $< > $@; \
	else \
		gcc -x c++ -E -P -DESQL=""  -DESQL_ORA $< > $@; \
	fi

