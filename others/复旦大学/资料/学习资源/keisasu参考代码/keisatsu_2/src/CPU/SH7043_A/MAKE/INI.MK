#------------------------------------------------------------------------
#   POPLAR/ANZU_L   初期化部(INI)のメイクファイル
#   1996/10/14		Transplanted from \src\kobe\anzu\sh\make By T.Nose
#------------------------------------------------------------------------

DEFINE 		= \src\atlanta\define
DEFV 		= \src\atlanta\def_v
EXTV		= \src\atlanta\ext_v
SRC			= \src\atlanta\src
WORDING		= \src\atlanta\wording

DEFINESH	= \src\cpu\sh7043_a\irom\define
DEFVSH 		= \src\cpu\sh7043_a\irom\def_v
EXTVSH		= \src\cpu\sh7043_a\irom\ext_v
SRCSH		= \src\cpu\sh7043_a\irom\src
MONSH		= \src\cpu\sh7043_a\irom\mon

MAKE		= \src\atlanta\make

POPB_SRC	= \src\atlanta\poplar_b\src

#
MSWDEFINE	= \src\memsw\define
PROTO_TYPE 	=	$(DEFINE)\protype.h
MEMORY_SWITCH =	$(MSWDEFINE)\mem_sw_a.h	$(MSWDEFINE)\mem_sw_b.h	\
				$(MSWDEFINE)\mem_sw_c.h	$(MSWDEFINE)\mem_sw_d.h	\
				$(MSWDEFINE)\mem_sw_e.h	$(MSWDEFINE)\mem_sw_f.h	\
				$(MSWDEFINE)\mem_sw_g.h	$(MSWDEFINE)\mem_sw_h.h	\
				$(MSWDEFINE)\mem_sw_i.h	$(MSWDEFINE)\mem_sw_j.h
#
CC          = shc
ASM         = asmsh
OPTION      = /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
ASM_OPT     = /cpu=sh2 /debug /object=$*.obj
LNK         = lnk /subcommand=\src\cpu\sh7043_a\make\INI.sub
OBJECT      = \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-----------------------------------------------------------------------------
#	桐用ｽﾀ-ﾄｱｯﾌﾟﾓｼﾞｭｰﾙのﾘﾝｸを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\ini2.lnk:	\src\cpu\sh7043_a\make\ini.SUB	\
#				$(OBJECT)\ini_cpu.obj	\
				$(OBJECT)\ini_cpui.obj	\
				$(OBJECT)\ini_cpuo.obj	\
#				$(OBJECT)\ini_cput.obj	\
				$(OBJECT)\ini_enty.obj
		$(LNK)
#-----------------------------------------------------------------------------
#	ｽﾀ-ﾄｱｯﾌﾟﾓｼﾞｭｰﾙのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
$(OBJECT)\ini_cpui.obj:	$(SRCSH)\ini_cpui.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\irom\define\sh_sys.h		\
					\src\atlanta\hinoki\define\hino_sys.h		\
				\src\cpu\sh7043_a\irom\define\cpu_def.h		\
					\src\atlanta\hinoki\define\hino_cpu.h		\
				\src\atlanta\sh7043\define\sh_sys.h		\
				\src\atlanta\sh7043\define\cpu_def.h
		$(CC) $(OPTION) $(SRCSH)\ini_cpui.c
#
$(OBJECT)\ini_cpuo.obj:	$(SRCSH)\ini_cpuo.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\irom\define\sh_sys.h		\
					\src\atlanta\hinoki\define\hino_sys.h		\
				\src\cpu\sh7043_a\irom\define\cpu_def.h		\
					\src\atlanta\hinoki\define\hino_cpu.h		\
				\src\atlanta\sh7043\define\sh_sys.h		\
				\src\atlanta\sh7043\define\cpu_def.h		\
				\src\atlanta\define\mntsw_a.h		\
				\src\atlanta\define\mntsw_f.h		\
				\src\atlanta\define\dma_pro.h		\
							\src\atlanta\define\mem_def.h		\
							\src\atlanta\define\dma_blk.h		\
							\src\atlanta\define\sysmax.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
												\src\atlanta\define\message.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
		$(CC) $(OPTION) $(SRCSH)\ini_cpuo.c
#
$(OBJECT)\ini_enty.obj :$(SRCSH)\ini_enty.src	\
				$(DEFINESH)\def_mon.hdr
				$(ASM)	$(SRCSH)\ini_enty.src $(ASM_OPT)
#
