#------------------------------------------------------------------------
#   POPLAR/ANZU_L   DMAのメイクファイル
#   1996/11/14		Transplanted from \src\kobe\anzu\sh\make By T.Nose
#------------------------------------------------------------------------
DEFINE 	= \src\atlanta\define
DEFINESH	= \src\atlanta\sh7043\define
DEFV 	= \src\atlanta\def_v
DEFVSH	= \src\atlanta\sh7043\def_v
EXTV	= \src\atlanta\ext_v
EXTVSH	= \src\atlanta\sh7043\ext_v
SRC		= \src\atlanta\src
SRCSH	= \src\atlanta\sh7043\src
WORDING	= \src\atlanta\wording
MONSH	= \src\atlanta\sh7043\mon
MAKE	= \src\atlanta\make
#
MSWDEFINE	= \src\memsw\define
PROTO_TYPE =	$(DEFINE)\protype.h
MEMORY_SWITCH =	$(MSWDEFINE)\mem_sw_a.h	$(MSWDEFINE)\mem_sw_b.h	\
				$(MSWDEFINE)\mem_sw_c.h	$(MSWDEFINE)\mem_sw_d.h	\
				$(MSWDEFINE)\mem_sw_e.h	$(MSWDEFINE)\mem_sw_f.h	\
				$(MSWDEFINE)\mem_sw_g.h	$(MSWDEFINE)\mem_sw_h.h	\
				$(MSWDEFINE)\mem_sw_i.h	$(MSWDEFINE)\mem_sw_j.h
#
CC      = shc
ASM     = asmsh
OPTION  = /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))

#/* 最適化するとスタックを浪費するので止めます。 By O.Kimoto 1998/03/02 */
#!if ("$(MODEL)" == "POPLAR_H")
#OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
#!endif

ASM_OPT = /cpu=sh2 /debug /object=$*.obj
LNK     = lnk /subcommand=\src\atlanta\make\dma.sub
OBJECT  = \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-----------------------------------------------------------------------------
#	DMAモジュールのリンクを定義
#-----------------------------------------------------------------------------
$(OBJECT)\dma.lnk:	\src\atlanta\make\dma.sub	\
			$(OBJECT)\dma_dbca.obj		$(OBJECT)\dma_dbcc.obj		$(OBJECT)\dma_dch.obj		$(OBJECT)\dma_ddc.obj	\
			$(OBJECT)\dma_dmd.obj		$(OBJECT)\dma_dmk.obj		$(OBJECT)\dma_dst.obj		$(OBJECT)\dma_stup.obj	\
			$(OBJECT)\dma_ini.obj		$(OBJECT)\dma_func.obj		$(OBJECT)\dma_int.obj		$(OBJECT)\dma_sh.obj	\
			$(OBJECT)\dma_dtc.obj
		$(LNK)
#-----------------------------------------------------------------------------
#	DMAﾄﾞﾗｲﾊﾞｰﾓｼﾞｭｰﾙのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
$(OBJECT)\dma_dbca.obj:	$(SRC)\dma_dbca.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\dma_def.h		\
				\src\atlanta\define\dma_blk.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\sh7043\define\sh_port.h
		$(CC)	$(OPTION) $(SRC)\dma_dbca.c
#
$(OBJECT)\dma_dbcc.obj:	$(SRC)\dma_dbcc.c					\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\dma_def.h		\
				\src\atlanta\define\dma_blk.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\sh7043\define\sh_port.h
		$(CC)	$(OPTION) $(SRC)\dma_dbcc.c
#
$(OBJECT)\dma_dch.obj:	$(SRC)\dma_dch.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\dma_def.h		\
					\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h
		$(CC)	$(OPTION) $(SRC)\dma_dch.c
#
$(OBJECT)\dma_ddc.obj:	$(SRC)\dma_ddc.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\dma_def.h		\
				\src\atlanta\define\dma_blk.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\sh7043\define\sh_port.h
		$(CC)	$(OPTION) $(SRC)\dma_ddc.c
#
$(OBJECT)\dma_dmd.obj:	$(SRC)\dma_dmd.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\dma_def.h		\
				\src\atlanta\define\dma_blk.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\sh7043\define\sh_port.h
		$(CC)	$(OPTION) $(SRC)\dma_dmd.c
#
$(OBJECT)\dma_dmk.obj:	$(SRC)\dma_dmk.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\dma_def.h		\
					\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\define\dma_blk.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h
		$(CC)	$(OPTION) $(SRC)\dma_dmk.c
#
$(OBJECT)\dma_dst.obj:	$(SRC)\dma_dst.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\dma_pro.h		\
				\src\atlanta\sh7043\define\sh_port.h
		$(CC)	$(OPTION) $(SRC)\dma_dst.c
#
$(OBJECT)\dma_stup.obj:	$(SRC)\dma_stup.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\dma_def.h		\
					\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\define\dma_blk.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h
		$(CC)	$(OPTION) $(SRC)\dma_stup.c
#
$(OBJECT)\dma_ini.obj:	$(SRC)\dma_ini.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\dma_def.h		\
				\src\atlanta\sh7043\define\sh_port.h
		$(CC)	$(OPTION) $(SRC)\dma_ini.c
#
$(OBJECT)\dma_func.obj:	$(SRC)\dma_func.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\dma_def.h		\
					\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h
		$(CC)	$(OPTION) $(SRC)\dma_func.c
#
$(OBJECT)\dma_int.obj:	$(SRC)\dma_int.c
		$(CC)	$(OPTION) $(SRC)\dma_int.c
#
$(OBJECT)\dma_sh.obj:	$(SRCSH)\dma_sh.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\dma_def.h		\
					\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\define\dma_pro.h		\
				\src\atlanta\sh7043\define\sh_sys.h
		$(CC)	$(OPTION) $(SRCSH)\dma_sh.c
#
$(OBJECT)\dma_dtc.obj:	$(SRCSH)\dma_dtc.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\dma_blk.h		\
				\src\atlanta\define\dma_def.h		\
					\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\ext_v\dma_data.h		\
				\src\atlanta\sh7043\define\sh_sys.h
		$(CC)	$(OPTION) $(SRCSH)\dma_dtc.c
