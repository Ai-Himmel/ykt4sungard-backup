#/**********************************************************************************************************************
#	@(#)$Id: s1.mk,v 1.4 2005/07/01 10:00:01 mi93007 Exp $
#	Create        : 2005/06/08
#	Author        : 石橋正和
#	Description   : S1モジュールmakefile
#	Maintenance   : 
#	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
#**********************************************************************************************************************/
#---------------------------#
#	ディレクトリマクロ		#
#---------------------------#
DEFINE		= \src\atlanta\define
DEFINESH	= \src\atlanta\sh7043\define
DEFV		= \src\atlanta\def_v
DEFVSH		= \src\atlanta\sh7043\def_v
EXTV		= \src\atlanta\ext_v
EXTVSH		= \src\atlanta\sh7043\ext_v
SRC			= \src\atlanta\src
SRCSH		= \src\atlanta\sh7043\src
WORDING		= \src\atlanta\wording
MONSH		= \src\atlanta\sh7043\mon
MAKE		= \src\atlanta\make
#
MSWDEFINE	= \src\memsw\define
PROTO_TYPE =	$(DEFINE)\protype.h
MEMORY_SWITCH =	$(MSWDEFINE)\mem_sw_a.h	$(MSWDEFINE)\mem_sw_b.h	\
				$(MSWDEFINE)\mem_sw_c.h	$(MSWDEFINE)\mem_sw_d.h	\
				$(MSWDEFINE)\mem_sw_e.h	$(MSWDEFINE)\mem_sw_f.h	\
				$(MSWDEFINE)\mem_sw_g.h	$(MSWDEFINE)\mem_sw_h.h	\
				$(MSWDEFINE)\mem_sw_i.h	$(MSWDEFINE)\mem_sw_j.h
#
#-----------------------------------------------------------------------------
#	ｺﾏﾝﾄﾞ名を定義
#-----------------------------------------------------------------------------
CC			= shc
ASM			= asmsh
LNK			= lnk /subcommand=\src\atlanta\make\s1.sub
#-----------------------------------------------------------------------------
#	引数を定義
#-----------------------------------------------------------------------------
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_NO	= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
#最適化
#OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
#OPTION_NO	= /op=1 /size   /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))

ASM_OPT		= /cpu=$(CPU_OPT) /debug /object=$*.obj
#-----------------------------------------------------------------------------
#	オブジェクトディレクトリを定義
#-----------------------------------------------------------------------------
MACHINE_DEF = sh
CMD_SUFX	= sub
OBJECT		= \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-------------------------------------------#
#	S1モジュールのリンク					#
#-------------------------------------------#
$(OBJECT)\s1.lnk :	\src\atlanta\make\s1.$(CMD_SUFX)	\
			$(OBJECT)\s1_reg.obj	\
			$(OBJECT)\s1_int.obj	\
			$(OBJECT)\s1_tcf.obj	\
			$(OBJECT)\s1_data.obj
	$(LNK)

#---------------------------------------#
#	S1モジュールのメイクファイル部		#
#---------------------------------------#
$(OBJECT)\s1_reg.obj :	$(SRC)\s1_reg.c			\
				\src\atlanta\define\product.h	\
				\src\atlanta\define\s1_pro.h	\
				\src\atlanta\define\s1_def.h	\
				\src\atlanta\ext_v\s1_data.h
	$(CC) $(OPTION_NO) $(SRC)\s1_reg.c

$(OBJECT)\s1_int.obj :	$(SRC)\s1_int.c			\
				\src\atlanta\define\product.h	\
				\src\atlanta\define\s1_pro.h
	$(CC) $(OPTION_NO) $(SRC)\s1_int.c

$(OBJECT)\s1_tcf.obj :	$(SRC)\s1_tcf.c			\
				\src\atlanta\define\product.h	\
				\src\atlanta\define\mon_pro.h	\
				\src\atlanta\define\s1_pro.h
	$(CC) $(OPTION_NO) $(SRC)\s1_tcf.c

$(OBJECT)\s1_data.obj :	$(DEFV)\s1_data.c		\
				\src\atlanta\define\s1_def.h	\
				\src\atlanta\ext_v\s1_data.h
	$(CC) $(OPTION) $(DEFV)\s1_data.c
#
