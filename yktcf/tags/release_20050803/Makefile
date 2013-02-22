# Makefile for systems with GNU tools
# $Id$
CC 	= g++
CTAGS = ctags
SRC = src
TOP = $(shell pwd)
MKFILE = Makefile
CD = cd
INSTALL	=	install
VPATH = src
MAKE = make

MODULE_DIRS= blkmodule 

files = $(foreach d,$(MODULE_DIRS), $(SRC)/modules/$(d)/)


yktcf:build-dist

build-dist:
	@echo "====================================>src"
	@cd $(TOP)/$(SRC) && $(MAKE) -f $(MKFILE)
	@echo "src<===================================="

build-so:
	@echo "==================================>module"
	$(MAKE) -C $(files)
	@echo "module<=================================="

clean-so:
	@echo "==================================>module"
	$(MAKE) -C $(files) clean
	@echo "module<=================================="
	

all:yktcf build-so

TAGS:
	@echo "generate ctags..."
	@-find $(TOP) -print | grep -E "\.h|\.c" | xargs ctags

.PHONY: clean run clean-so

clean:clean-so
	-rm bin/yktcf src/*.o pid/*.pid yktcf.pid

run:
	bin/yktcf
