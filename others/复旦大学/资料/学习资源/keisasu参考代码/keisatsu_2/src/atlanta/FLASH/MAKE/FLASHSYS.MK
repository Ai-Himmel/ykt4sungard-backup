#------------------------------------------------------------------------
#	POPLAR_B/POPLAR_L/ANZU_L	フラッシュシステム部のメイクファイル
#------------------------------------------------------------------------
SRC			= \src\atlanta\flash\src
DEFV		= \src\atlanta\flash\def_v
SRC2		= \src\atlanta\flash\src2

#-----------------------------------------------------------------------------
#	コマンド名を定義
#-----------------------------------------------------------------------------
CC			= shc
ASM			= asmsh
#LNK			= lnk /subcommand=\src\atlanta\flash\make\flashsys.sub


!if ("$(MODEL)" != "POPLAR_H") && ("$(MODEL)" != "SAKAKI")
!if ("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI2") || ("$(MODEL)" == "SATSUKI2")
LNK			= lnk /subcommand=\src\atlanta\flash\make\flssys1.sub
!else
LNK			= lnk /subcommand=\src\atlanta\flash\make\flssysa.sub
!endif
!endif

!if ("$(MODEL)" == "POPLAR_H") || ("$(MODEL)" == "SAKAKI")
LNK			= lnk /subcommand=\src\atlanta\flash\make\flssysk.sub
!endif


#-----------------------------------------------------------------------------
#	引数を定義
#-----------------------------------------------------------------------------
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
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
$(OBJECT)\flashsys.lnk:	\src\atlanta\flash\make\flashsys.sub	\
			$(OBJECT)\vector.obj	\
			$(OBJECT)\rom_tbl.obj	\
			$(OBJECT)\sys_data.obj	\
			$(OBJECT)\ini_enty.obj	\
			$(OBJECT)\ini_cpu.obj	\
			$(OBJECT)\int_enty.obj	\
			$(OBJECT)\int_err.obj	\
			$(OBJECT)\int_tim.obj	\
			$(OBJECT)\cmn_buzz.obj	\
			$(OBJECT)\cmn_io.obj	\
			$(OBJECT)\cmn_iorw.obj	\
			$(OBJECT)\cmn_str.obj	\
			$(OBJECT)\scn_sub.obj	\
!if ("$(MODEL)" != "POPLAR_H") && ("$(MODEL)" != "SAKAKI")
 !if ("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI2") || ("$(MODEL)" == "SATSUKI2")
			$(OBJECT)\hino_int.obj	\
			$(OBJECT)\cpu_reg.obj	\
			$(OBJECT)\ga_reg.obj	\
			$(OBJECT)\iu_uniq.obj
 !else
			$(OBJECT)\opr_lcda.obj
 !endif
!endif
!if ("$(MODEL)" == "POPLAR_H") || ("$(MODEL)" == "SAKAKI")
			$(OBJECT)\opr_lcdk.obj	\
			$(OBJECT)\lcd_buf.obj
!endif
		$(LNK)

#-----------------------------------------------------------------------------
#	モジュールのメイクファイル部
#-----------------------------------------------------------------------------
$(OBJECT)\vector.obj:	$(DEFV)\vector.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) /section=c=VECTOR $(DEFV)\vector.c
#
$(OBJECT)\rom_tbl.obj:	$(DEFV)\rom_tbl.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(DEFV)\rom_tbl.c
#
$(OBJECT)\sys_data.obj:	$(DEFV)\sys_data.c
		$(CC) $(OPTION) $(DEFV)\sys_data.c
#
$(OBJECT)\ini_enty.obj:	$(SRC)\ini_enty.src
		$(ASM) $(SRC)\ini_enty.src $(ASM_OPT)
#
$(OBJECT)\ini_cpu.obj:	$(SRC)\ini_cpu.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\ini_cpu.c
#
$(OBJECT)\int_enty.obj:	$(SRC)\int_enty.src
		$(ASM) $(SRC)\int_enty.src $(ASM_OPT)
#
$(OBJECT)\int_err.obj:	$(SRC)\int_err.src
		$(ASM) $(SRC)\int_err.src $(ASM_OPT)
#
$(OBJECT)\int_tim.obj:	$(SRC)\int_tim.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\int_tim.c
#
$(OBJECT)\cmn_buzz.obj:	$(SRC)\cmn_buzz.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\cmn_buzz.c
#
$(OBJECT)\cmn_io.obj:	$(SRC)\cmn_io.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\cmn_io.c
#
!if ("$(MODEL)" == "ANZU_L")
$(OBJECT)\cmn_iorw.obj:	$(SRC2)\cmn_iorw.src
		$(ASM) $(SRC2)\cmn_iorw.src $(ASM_OPT)
!else
$(OBJECT)\cmn_iorw.obj:	$(SRC)\cmn_iorw.src
		$(ASM) $(SRC)\cmn_iorw.src $(ASM_OPT)
!endif
#
$(OBJECT)\scn_sub.obj:	$(SRC)\scn_sub.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\scn_sub.c
#
!if ("$(MODEL)" != "POPLAR_H")
$(OBJECT)\opr_lcda.obj:	$(SRC)\opr_lcda.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\opr_lcda.c
!endif
!if ("$(MODEL)" == "POPLAR_H") || ("$(MODEL)" == "SAKAKI")
$(OBJECT)\opr_lcdk.obj:	$(SRC)\opr_lcdk.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\opr_lcdk.c
#
$(OBJECT)\lcd_buf.obj:	$(DEFV)\lcd_buf.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(DEFV)\lcd_buf.c
!endif

#
$(OBJECT)\cmn_str.obj:	$(SRC)\cmn_str.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\cmn_str.c
#
!if ("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI2") || ("$(MODEL)" == "SATSUKI2")
$(OBJECT)\hino_int.obj:	$(SRC)\hino_int.src
		$(ASM) $(SRC)\hino_int.src $(ASM_OPT)
#
$(OBJECT)\cpu_reg.obj:	$(DEFV)\cpu_reg.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(DEFV)\cpu_reg.c
#
$(OBJECT)\ga_reg.obj:	$(DEFV)\ga_reg.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(DEFV)\ga_reg.c
#
$(OBJECT)\iu_uniq.obj:	$(SRC)\iu_uniq.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\iu_uniq.c
!endif
