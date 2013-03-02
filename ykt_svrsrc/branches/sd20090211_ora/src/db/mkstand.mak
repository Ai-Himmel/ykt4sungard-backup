APLIBS=-L$(HOME)/ykt/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
PUBIND=$(HOME)/ykt/src/include
PREPCOMP_CXX=proc code=cpp cpp_suffix=cpp maxopencursors=50 MODE=ANSI TYPE_CODE=ANSI CLOSE_ON_COMMIT=yes def_sqlcode=yes dynamic=ANSI define=ESQL_ORA LINES=YES config="$(HOME)/ykt/bin/proccfg.cfg" include="/usr/include"  include="$(ORACLE_HOME)/precomp/public" include="$(ORACLE_HOME)/rdbms/public" include="$(HOME)/ykt/src/buinc" include="$(HOME)/ykt/src/include" include="$(HOME)/ykt/src/include/dbincl" include="$(HOME)/ykt/src/public" $(PROC_OPTS)

PREPCOMP_C=proc maxopencursors=50 MODE=ANSI TYPE_CODE=ANSI CLOSE_ON_COMMIT=yes def_sqlcode=yes dynamic=ANSI define=ESQL_ORA LINES=YES config="$(HOME)/ykt/bin/proccfg.cfg" include="/usr/include"  include="$(ORACLE_HOME)/precomp/public" include="$(ORACLE_HOME)/rdbms/public" include="$(HOME)/ykt/src/buinc" include="$(HOME)/ykt/src/include" include="$(HOME)/ykt/src/include/dbincl" include="$(HOME)/ykt/src/public" $(PROC_OPTS)

ACT=$(HOME)/ykt/bin/dbcrt
PREPROCESSOR_C=gcc -x c -E -P -DESQL=""
PREPROCESSOR_CXX=g++ -x c -E -P -DESQL=""
STRIP=/usr/bin/strip
UNAME=$(shell uname)
ifeq ($(UNAME),SunOS)
	CC=gcc
	CXX=g++
	LIBS=-lstdc++ -lpthread -lsocket -lnsl -lm
	CCFLAGS=-D_DRTP_V4 -D_MT -DSUNOS -Wall $(USEROPTS)
	CXXFLAGS= -D_DRTP_V4 -D_MT -Wall  -DSUNOS $(USEROPTS)
	LIB_SUFFIX=32
	AR=/usr/ccs/bin/ar
endif
ifeq ($(UNAME),HP-UX)
	CC=gcc
	CXX=g++
	LIBS=-lstdc++ -lpthread -lnsl
	CCFLAGS= -D_DRTP_V4 -D_MT -Wall  -DLINUX -Wall $(USEROPTS)
	CXXFLAGS= -D_DRTP_V4 -D_MT -Wall  -DLINUX -Wall $(USEROPTS)
	LIB_SUFFIX=32
endif
ifeq ($(UNAME),Linux)
	CC=gcc
	CXX=g++
	LIBS=-lstdc++ -lpthread -lnsl
	CCFLAGS= -D_DRTP_V4 -D_MT -Wall  -DLINUX -Wall $(USEROPTS)
	CXXFLAGS= -D_DRTP_V4 -D_MT -Wall  -DLINUX -Wall $(USEROPTS)
	LIB_SUFFIX=
endif
ifeq ($(UNAME),AIX)
	CC=gcc
	CXX=g++
	LIBS=-lstdc++ -lpthread -lnsl
	CCFLAGS= -D_DRTP_V4 -D_MT -Wall  -DAIX -Wall $(USEROPTS)
	CXXFLAGS= -D_DRTP_V4 -D_MT -Wall  -DAIX -Wall $(USEROPTS)
	LIB_SUFFIX=32
endif
ARFLAGS=-r

ifeq ($(DBTYPE),DB2)
	INCLD= -I./ -I$(HOME)/ykt/src/buinc -I$(HOME)/ykt/src/public -I$(HOME)/ykt/src/include -I$(HOME)/ykt/src/include/dbincl -I$(DB2PATH)/include
	CCFLAGS += -DESQL_DB2
	LIBSUDF=-lstdc++ -L$(DB2PATH)/lib -ldb2 -ldb2apie
else
	INCLD= -I./ -I$(HOME)/ykt/src/buinc -I$(HOME)/ykt/src/public -I$(HOME)/ykt/src/include -I$(HOME)/ykt/src/include/dbincl -I$(ORACLE_HOME)/precomp/public -I$(ORACLE_HOME)/rdbms/public
	CCFLAGS += -DESQL_ORA
	LIBSUDF=-lstdc++ -L$(ORACLE_HOME)/lib$(LIB_SUFFIX) -lclntsh \
			`cat $(ORACLE_HOME)/lib$(LIB_SUFFIX)/ldflags` \
			`cat $(ORACLE_HOME)/lib$(LIB_SUFFIX)/sysliblist`
endif

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

.act.eC:
	@if [ $(DBTYPE) = DB2 ]; then \
		$(ACT) $< $@ 0; \
	else \
		$(ACT) $< $@ 1; \
	fi

.sqc.ec:
	@if [ $(DBTYPE) = DB2 ]; \
	then \
		$(PREPROCESSOR_C) -DESQL_DB2 $(USEROPTS) $< > $@; \
	else \
		$(PREPROCESSOR_C) -DESQL_ORA $(USEROPTS) $< > $@; \
	fi

.sqC.eC:
	@if [ $(DBTYPE) = DB2 ]; \
	then \
		$(PREPROCESSOR_CXX) -DESQL_DB2 $(USEROPTS) $< > $@; \
	else \
		$(PREPROCESSOR_CXX)  -DESQL_ORA $(USEROPTS) $< > $@; \
	fi

