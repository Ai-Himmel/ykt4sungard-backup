CC=gcc
CXX=g++
RM=rm
TARGET=byteorder 

LIBS=
CFLAGS=

.SUFFIXES: .c .o .cpp .py

.PHONY: clean



byteorder:byteorder.o
	$(CC) -o $@ $(LIBS) $^

clean:
	@$(RM) -f $(TARGET) *.o

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

