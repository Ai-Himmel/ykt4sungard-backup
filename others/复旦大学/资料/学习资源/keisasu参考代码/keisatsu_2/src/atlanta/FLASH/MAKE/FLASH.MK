#------------------------------------------------------------------------
#	POPLAR_B/POPLAR_L/ANZU_L	フラッシュメモリ部のメイクファイル
#	1997/04/24		Transplanted from \src\atlanta\make By M.Kuwahara
#------------------------------------------------------------------------
SRC			= \src\atlanta\flash\src
DEFV		= \src\atlanta\flash\def_v

#-----------------------------------------------------------------------------
#	コマンド名を定義
#-----------------------------------------------------------------------------
CC			= shc
ASM			= asmsh

LNK			= lnk /subcommand=\src\atlanta\flash\make\flash.sub
#-----------------------------------------------------------------------------
#	引数を定義
#-----------------------------------------------------------------------------
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION2		= /op=0 /deb /cp=sh2 /Code=asmcode /def=($(MODEL),$(COUNTRY))
S_OPTION	= /op=1 /deb /cp=$(CPU_OPT) /def=($(MODEL),$(COUNTRY),$(CPU))
ASM_OPT		= /cpu=sh2 /debug /object=$*.obj

#-----------------------------------------------------------------------------
#	オブジェクトディレクトリを定義
#-----------------------------------------------------------------------------
#OBJECT		= \src\atlanta\$(MODEL)\work\$(COUNTRY)
OBJECT		= \src\atlanta\flash\work\$(MODEL)
!if ("$(MODEL)" == "POPLAR_H") && ("$(COUNTRY)" == "JP0")
OBJECT		= \src\atlanta\flash\work\$(MODEL)\$(COUNTRY)
!endif

#-----------------------------------------------------------------------------
#	オペレーションモジュールのリンクを定義
#-----------------------------------------------------------------------------
$(OBJECT)\flash.lnk:	\src\atlanta\flash\make\flash.sub	\
			$(OBJECT)\fla_pol.obj	\
			$(OBJECT)\fla_sum.obj	\
			$(OBJECT)\fla_tgl.obj	\
			$(OBJECT)\fla_auto.obj	\
			$(OBJECT)\fla_cers.obj	\
			$(OBJECT)\fla_main.obj	\
			$(OBJECT)\fla_pro.obj	\
			$(OBJECT)\fla_rsm.obj	\
			$(OBJECT)\fla_rst0.obj	\
			$(OBJECT)\fla_rst1.obj	\
			$(OBJECT)\fla_sers.obj	\
			$(OBJECT)\fla_sus.obj	\
			$(OBJECT)\fla_oves.obj	\
			$(OBJECT)\fla_tbl.obj   \
			$(OBJECT)\jig_led.obj
		$(LNK)

#-----------------------------------------------------------------------------
#	オペレーションモジュールのメイクファイル部
#-----------------------------------------------------------------------------
$(OBJECT)\fla_pol.obj:	$(SRC)\fla_pol.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\flash\define\fla_pro.h		\
				\src\atlanta\flash\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_pol.c
#
$(OBJECT)\fla_sum.obj:	$(SRC)\fla_sum.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\flash\define\fla_pro.h		\
				\src\atlanta\flash\define\fla_def.h		\
				\src\atlanta\flash\ext_v\fla_tbl.h
		$(CC) $(OPTION) $(SRC)\fla_sum.c
#
$(OBJECT)\fla_tgl.obj:	$(SRC)\fla_tgl.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\flash\define\fla_pro.h		\
				\src\atlanta\flash\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_tgl.c
#
$(OBJECT)\fla_auto.obj:	$(SRC)\fla_auto.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\flash\define\fla_pro.h		\
				\src\atlanta\flash\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_auto.c
#		$(CC) $(OPTION2) $(SRC)\fla_auto.c
#
$(OBJECT)\fla_cers.obj:	$(SRC)\fla_cers.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\flash\define\fla_pro.h		\
				\src\atlanta\flash\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_cers.c
#
$(OBJECT)\fla_main.obj:	$(SRC)\fla_main.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\flash\define\fla_pro.h		\
				\src\atlanta\flash\define\fla_def.h		\
				\src\atlanta\flash\ext_v\fla_tbl.h		\
				\src\atlanta\flash\define\sys_pro.h		\
				\src\atlanta\flash\define\sys_def.h
		$(CC) $(OPTION) $(SRC)\fla_main.c
#
$(OBJECT)\fla_pro.obj:	$(SRC)\fla_pro.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\flash\define\fla_pro.h		\
				\src\atlanta\flash\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_pro.c
#
$(OBJECT)\fla_rsm.obj:	$(SRC)\fla_rsm.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\flash\define\fla_pro.h		\
				\src\atlanta\flash\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_rsm.c
#
$(OBJECT)\fla_rst0.obj:	$(SRC)\fla_rst0.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\flash\define\fla_pro.h		\
				\src\atlanta\flash\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_rst0.c
#
$(OBJECT)\fla_rst1.obj:	$(SRC)\fla_rst1.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\flash\define\fla_pro.h		\
				\src\atlanta\flash\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_rst1.c
#
$(OBJECT)\fla_sers.obj:	$(SRC)\fla_sers.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\flash\define\fla_pro.h		\
				\src\atlanta\flash\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_sers.c
#
$(OBJECT)\fla_sus.obj:	$(SRC)\fla_sus.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\flash\define\fla_pro.h		\
				\src\atlanta\flash\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_sus.c
#
$(OBJECT)\fla_oves.obj:	$(SRC)\fla_oves.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\flash\define\fla_pro.h		\
				\src\atlanta\flash\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_oves.c
#
$(OBJECT)\fla_tbl.obj:	$(DEFV)\fla_tbl.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\flash\define\fla_def.h		\
				\src\atlanta\flash\ext_v\fla_tbl.h
		$(CC) $(OPTION) $(DEFV)\fla_tbl.c
#
$(OBJECT)\jig_led.obj:	$(SRC)\jig_led.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\flash\define\jig_led.h		\
				\src\atlanta\flash\define\sys_pro.h		\
				\src\atlanta\flash\ext_v\sys_data.h
		$(CC) $(OPTION) $(SRC)\jig_led.c
#
