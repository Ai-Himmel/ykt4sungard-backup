#------------------------------------------------------------------------
#   POPLAR/ANZU_L	SH7043固有データメイクファイル
#   1996/10/14		Transplanted from \src\kobe\anzu\sh\make By T.Nose
#------------------------------------------------------------------------
DEFINE 		= \src\atlanta\define
DEFINE_MDM	= \src\atlanta\mdm\orange\define
DEFV 		= \src\atlanta\def_v
EXTV		= \src\atlanta\ext_v
SRC			= \src\atlanta\src
WORD		= \src\atlanta\wording
DEFINESH 	= \src\cpu\sh7043_a\irom\define
DEFVSH		= \src\cpu\sh7043_a\irom\def_v
EXTVSH		= \src\cpu\sh7043_a\irom\ext_v
MONSH		= \src\cpu\sh7043_a\irom\mon
MAKE		= \src\atlanta\make
#
MSWDEFINE	= \src\memsw\define
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
LNK         = lnk /subcommand=\src\cpu\sh7043_a\make\SHDATA.sub
OBJECT      = \src\atlanta\$(MODEL)\work\$(COUNTRY)
#
#-----------------------------------------------------------------------------
#   桐用ﾃﾞｰﾀﾓｼﾞｭｰﾙのﾘﾝｸを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\SHdata2.lnk:		\src\cpu\sh7043_a\make\SHdata.SUB	\
	$(OBJECT)\defv_mon.obj	\
	$(OBJECT)\defv_mbx.obj	\
	$(OBJECT)\defv_sem.obj	\
	$(OBJECT)\defv_stk.obj
        $(LNK)
#
#-----------------------------------------------------------------------------
#   ﾘｱﾙﾀｲﾑﾓﾆﾀﾓｼﾞｭｰﾙのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
$(OBJECT)\defv_mon.obj:		$(DEFVSH)\defv_mon.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\sh7043\define\def_mon.h		\
					\src\cpu\sh7043_a\irom\define\def_mon.h		\
				\src\atlanta\sh7043\define\def_tcb.h		\
					\src\atlanta\define\message.h		\
					\src\cpu\sh7043_a\irom\define\def_tcb.h		\
				\src\atlanta\sh7043\define\def_scb.h		\
					\src\cpu\sh7043_a\irom\define\def_scb.h
	$(CC) $(OPTION) $(DEFVSH)\defv_mon.c
#
$(OBJECT)\defv_mbx.obj:		$(DEFVSH)\defv_mbx.c	\
				\src\atlanta\sh7043\define\def_mbxn.h		\
					\src\atlanta\define\product.h		\
					\src\cpu\sh7043_a\irom\define\def_mbxn.h
	$(CC) $(OPTION) $(DEFVSH)\defv_mbx.c
#
$(OBJECT)\defv_sem.obj:		$(DEFVSH)\defv_sem.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\sh7043\define\def_semn.h		\
					\src\cpu\sh7043_a\irom\define\def_semn.h
	$(CC) $(OPTION) $(DEFVSH)\defv_sem.c
#
$(OBJECT)\defv_stk.obj:		$(DEFVSH)\defv_stk.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\sh7043\define\def_mon.h		\
					\src\cpu\sh7043_a\irom\define\def_mon.h
	$(CC) $(OPTION) $(DEFVSH)\defv_stk.c
