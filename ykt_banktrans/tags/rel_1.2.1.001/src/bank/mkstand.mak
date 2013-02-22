APLIBS=-L$(HOME)/bank/lib -ldrtplib -lkcrypto -lboost_thread -lbccpub -lpubdb
PUBIND=$(HOME)/bank/src/include


ACT=$(HOME)/bank/bin/dbcrt
PREPROCESSOR_C=gcc -x c -E -P -DESQL=""
PREPROCESSOR_CXX=g++ -x c -E -P -DESQL=""
UNAME=$(shell uname)
ifeq ($(UNAME),SunOS)
	CC=gcc
	CXX=g++
	LIBS=-lstdc++ -lpthread -lsocket -lnsl -lm
	CCFLAGS=-D_DRTP_V4 -D_MT -DSUNOS -Wall $(USEROPTS)
	CXXFLAGS= -D_DRTP_V4 -D_MT -Wall  -DSUNOS $(USEROPTS)
endif
ifeq ($(UNAME),HP-UX)
	CC=aCC
	CXX=aCC
	PREPROCESSOR_C=aCC -E -DESQL=""
	PREPROCESSOR_CXX=aCC -E -DESQL=""
	LIBS=-lpthread 
	CCFLAGS= -mt -D_DRTP_V4 -DUNIX -DHP_UX -Agcc -AC99 -Wall $(USEROPTS)
	CXXFLAGS= -mt -D_DRTP_V4 -DUNIX -DHP_UX -Ag++ -Wall $(USEROPTS)
endif
ifeq ($(UNAME),Linux)
	CC=gcc
	CXX=g++
	LIBS=-lstdc++ -lpthread -lnsl
	CCFLAGS= -D_DRTP_V4 -D_MT -Wall  -DLINUX -Wall $(USEROPTS)
	CXXFLAGS= -D_DRTP_V4 -D_MT -Wall  -DLINUX -Wall $(USEROPTS)
endif
ARFLAGS=-r

INCLD= -I./ -I$(HOME)/bank/src/buinc -I$(HOME)/bank/src/public -I$(HOME)/bank/src/include 

.SUFFIXES: .o .c .cpp .sqc .sqC .act .ec .eC

.c.o:
	$(CC) -c $(CCFLAGS) $(INCLD) $(INCLUDE) $*.c

.cpp.o:
	$(CXX) -c $(CCFLAGS) $(INCLD) $*.cpp
