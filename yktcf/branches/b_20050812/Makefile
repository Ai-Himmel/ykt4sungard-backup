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

MODULE_DIRS= cardinfo
#blkmodule \
#newcard

files = $(foreach d,$(MODULE_DIRS), $(SRC)/modules/$(d))


yktcf:build-dist

build-dist:
	@echo "====================================>src"
	@cd $(TOP)/$(SRC) && $(MAKE) -f $(MKFILE)
	@echo "src<===================================="

build-so:
	@echo "==================================>module"
#	$(MAKE) -C $(SRC)/modules/blkmodule
#	$(MAKE) -C $(SRC)/modules/newcard
	$(MAKE) -C $(SRC)/modules/cardinfo
	@echo "module<=================================="

clean-so:
	@echo "==================================>module"
#	$(MAKE) -C $(SRC)/modules/blkmodule clean
#	$(MAKE) -C $(SRC)/modules/newcard clean
	$(MAKE) -C $(SRC)/modules/cardinfo clean
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
