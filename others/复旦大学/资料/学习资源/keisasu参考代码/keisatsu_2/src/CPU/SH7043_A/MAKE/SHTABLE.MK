#------------------------------------------------------------------------
#   POPLAR/ANZU_L	SH7043固有テーブルメイクファイル
#   1996/10/14		Transplanted from \src\kobe\anzu\sh\make By T.Nose
#------------------------------------------------------------------------
DEFINE 		= \src\atlanta\define
DEFV 		= \src\atlanta\def_v
EXTV		= \src\atlanta\ext_v
SRC			= \src\atlanta\src
WORD		= \src\atlanta\wording
MAKE		= \src\atlanta\make

DEFINESH 	= \src\cpu\sh7043_a\irom\define
DEFVSH		= \src\cpu\sh7043_a\irom\def_v
EXTVSH		= \src\cpu\sh7043_a\irom\ext_v
MONSH		= \src\cpu\sh7043_a\irom\mon

DEFVPOPB	= \src\atlanta\poplar_b\def_v
DEFVPOPH	= \src\atlanta\poplar_h\def_v
#
MSWDEFINE	= \src\memsw\define
PROTO_TYPE 	= $(DEFINE)\protype.h
MEMORY_SWITCH =	$(MSWDEFINE)\mem_sw_a.h	$(MSWDEFINE)\mem_sw_b.h	\
				$(MSWDEFINE)\mem_sw_c.h	$(MSWDEFINE)\mem_sw_d.h	\
				$(MSWDEFINE)\mem_sw_e.h	$(MSWDEFINE)\mem_sw_f.h	\
				$(MSWDEFINE)\mem_sw_g.h	$(MSWDEFINE)\mem_sw_h.h	\
				$(MSWDEFINE)\mem_sw_i.h	$(MSWDEFINE)\mem_sw_j.h

CC          = shc
ASM         = asmsh
OPTION      = /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
ASM_OPT     = /cpu=sh2 /debug /object=$*.obj
LNK         = lnk /subcommand=\src\cpu\sh7043_a\make\SHTABLE.sub
OBJECT      = \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-----------------------------------------------------------------------------
#   桐用ﾃﾞｰﾀﾓｼﾞｭｰﾙのﾘﾝｸを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\SHTABLE2.lnk:		\src\cpu\sh7043_a\make\SHTABLE.SUB	\
							$(OBJECT)\DEFV_FNC.OBJ	\
							$(OBJECT)\DEFV_TIB.OBJ	\
							$(OBJECT)\MON_TBL.OBJ	\
							$(OBJECT)\VECTOR.obj	\
							$(OBJECT)\REF_TBL.obj	\
							$(OBJECT)\INT_TBL.OBJ
        $(LNK)
#-----------------------------------------------------------------------------
#   ﾘｱﾙﾀｲﾑﾓﾆﾀﾓｼﾞｭｰﾙのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
#割込み禁止期間測定用
#!if ("$(MODEL)" == "POPLAR_B") && ("$(COUNTRY)" == "JPN")
#$(OBJECT)\DEFV_FNC.OBJ:		$(DEFVPOPB)\DEFV_FNC.C	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\sh7043\define\mon_func.h
#	$(CC) $(OPTION) $(DEFVPOPB)\DEFV_FNC.C
#!else
#割込み禁止期間測定用	by O.Kimoto 1998/02/12
#!if ("$(MODEL)" == "POPLAR_H") && ("$(COUNTRY)" == "JPN")
#$(OBJECT)\DEFV_FNC.OBJ:		$(DEFVPOPH)\DEFV_FNC.C	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\sh7043\define\mon_func.h
#	$(CC) $(OPTION) $(DEFVPOPH)\DEFV_FNC.C
#!else
#!if ("$(MODEL)" == "POPLAR_L")
# 割込み禁止時間測定 By Y.Suzuki 1998/02/17
#$(OBJECT)\DEFV_FNC.OBJ:		$(DEFVPOPB)\DEFV_FNC.C	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\sh7043\define\mon_func.h
#	$(CC) $(OPTION) $(DEFVPOPB)\DEFV_FNC.C
#!else
$(OBJECT)\DEFV_FNC.OBJ:		$(DEFVSH)\DEFV_FNC.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\sh7043\define\mon_func.h		\
					\src\cpu\sh7043_a\irom\define\mon_func.h
	$(CC) $(OPTION) $(DEFVSH)\DEFV_FNC.C
#!endif
#!endif
#!endif
#
$(OBJECT)\VECTOR.obj:       $(DEFVSH)\VECTOR.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\sh7043\define\def_mon.h		\
					\src\cpu\sh7043_a\irom\define\def_mon.h		\
				\src\atlanta\hinoki\def_v\vector.c
# 新ﾏｽｸ変更
#    $(CC) $(OPTION) /section=c=VECTOR $(DEFVSH)\VECTOR.c
    $(CC) $(OPTION) $(DEFVSH)\VECTOR.c
#
$(OBJECT)\DEFV_TIB.obj:       $(DEFVSH)\DEFV_TIB.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\irom\define\def_tib.h		\
					\src\atlanta\hinoki\define\hino_tib.h		\
					\src\atlanta\sh7043\define\tib_pro.h		\
						\src\cpu\sh7043_a\irom\define\tib_pro.h		\
							\src\atlanta\hinoki\define\tib_pro.h		\
					\src\atlanta\sh7043\define\mon_func.h		\
						\src\cpu\sh7043_a\irom\define\mon_func.h
    $(CC) $(OPTION) $(DEFVSH)\DEFV_TIB.c
#
$(OBJECT)\MON_TBL.obj:		$(DEFVSH)\MON_TBL.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\sh7043\define\mon_func.h		\
					\src\cpu\sh7043_a\irom\define\mon_func.h		\
				\src\atlanta\sh7043\define\def_mon.h		\
					\src\cpu\sh7043_a\irom\define\def_mon.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
					\src\cpu\sh7043_a\irom\define\def_tib.h		\
						\src\atlanta\hinoki\define\hino_tib.h		\
				\src\atlanta\sh7043\ext_v\extv_mon.h		\
					\src\cpu\sh7043_a\irom\ext_v\extv_mon.h		\
						\src\cpu\sh7043_a\irom\define\def_tcb.h		\
						\src\cpu\sh7043_a\irom\define\def_scb.h		\
					\src\atlanta\sh7043\define\def_tcb.h		\
						\src\atlanta\define\message.h		\
					\src\atlanta\sh7043\define\def_scb.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h		\
						\src\cpu\sh7043_a\irom\define\def_mbxn.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\ext_v\extv_sem.h		\
					\src\cpu\sh7043_a\irom\ext_v\extv_sem.h		\
						\src\cpu\sh7043_a\irom\define\def_semn.h		\
					\src\atlanta\sh7043\define\def_semn.h
	$(CC) $(OPTION) $(DEFVSH)\MON_TBL.c
#

#
#	間接参照用ポインター	/*  By O.Kimoto 1998/09/08 */
#
$(OBJECT)\REF_TBL.obj:		$(DEFVSH)\REF_TBL.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\irom\define\mon_func.h		\
				\src\cpu\sh7043_a\irom\define\def_mon.h		\
				\src\cpu\sh7043_a\irom\define\def_tib.h		\
					\src\atlanta\hinoki\define\hino_tib.h		\
				\src\cpu\sh7043_a\irom\ext_v\extv_mon.h		\
					\src\cpu\sh7043_a\irom\define\def_tcb.h		\
						\src\atlanta\define\message.h		\
					\src\cpu\sh7043_a\irom\define\def_scb.h		\
					\src\atlanta\sh7043\define\def_mon.h		\
					\src\atlanta\sh7043\define\def_tcb.h		\
					\src\atlanta\sh7043\define\def_scb.h		\
					\src\atlanta\sh7043\define\def_tib.h		\
				\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h		\
					\src\cpu\sh7043_a\irom\define\def_mbxn.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\cpu\sh7043_a\irom\ext_v\extv_sem.h		\
					\src\cpu\sh7043_a\irom\define\def_semn.h		\
					\src\atlanta\sh7043\define\def_semn.h		\
				\src\atlanta\define\memerpro.h		\
					\src\atlanta\define\MEM_DEF.H
	$(CC) $(OPTION) /l /sh=ob $(DEFVSH)\REF_TBL.c

$(OBJECT)\INT_TBL.obj:		$(DEFVSH)\INT_TBL.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\hinoki\def_v\hino_int.c
	$(CC) $(OPTION) $(DEFVSH)\INT_TBL.c
