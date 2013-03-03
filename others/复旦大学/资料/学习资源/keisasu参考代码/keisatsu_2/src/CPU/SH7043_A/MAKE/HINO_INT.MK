#------------------------------------------------------------------------
#   POPLAR/ANZU_L   äÑçûÇ›(INT)ÇÃÉÅÉCÉNÉtÉ@ÉCÉã
#   1996/10/15		Transplanted from \src\kobe\anzu\sh\make By T.Nose
#------------------------------------------------------------------------
DEFINE      = \src\atlanta\define
DEFV       	= \src\atlanta\def_v
EXTV       	= \src\atlanta\ext_v
SRC        	= \src\atlanta\src
WORD       	= \src\atlanta\wording
MAKE       	= \src\atlanta\make
DEFINE_SH	=\src\cpu\sh7043_a\irom\define
SRC_SH		=\src\cpu\sh7043_a\irom\src
EXTV_SH		=\src\cpu\sh7043_a\irom\ext_v
DEFV_SH		=\src\cpu\sh7043_a\irom\def_v
MDM_OG_DEFINE = \src\atlanta\mdm\orange\define
MDM_OG_DEFV   = \src\atlanta\mdm\orange\def_v
MDM_OG_EXTV   = \src\atlanta\mdm\orange\ext_v
MDM_OG_SRC    = \src\atlanta\mdm\orange\src
POPB_SRC	= \src\atlanta\poplar_b\src
POPH_SRC	= \src\atlanta\poplar_h\src
SAKI_SRC	= \src\atlanta\sakaki\src
HINO_SRC	= \src\atlanta\hinoki\src
HINO_DEFINE	= \src\atlanta\hinoki\define

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
LNK         = lnk /subcommand=\src\cpu\sh7043_a\make\INT.sub
OBJECT      = \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-----------------------------------------------------------------------------
#   äÑçûèàóùÅiÇhÇmÇsÅjÅ^ÇlÇ`ÇrÇlÉÇÉWÉÖÅ[ÉãÇÃÇkÇâÇéÇãíËã`
#-----------------------------------------------------------------------------
$(OBJECT)\int2.lnk:	\src\cpu\sh7043_a\make\INT.sub	\
				$(OBJECT)\int_enty.obj	\
				$(OBJECT)\hinoenty.obj	\
				$(OBJECT)\int_tim.obj	\
				$(OBJECT)\int_err.obj	\
				$(OBJECT)\int_ext.obj
		$(LNK)

#-----------------------------------------------------------------------------
#   äÑçûèàóùÅiÇhÇmÇsÅjÅ^ÇlÇ`ÇrÇlÉÇÉWÉÖÅ[ÉãÇÃÇbÇèÇçÇêÇâÇåÇÖíËã`
#-----------------------------------------------------------------------------
#$(OBJECT)\int_enty.obj:	$(SRC_SH)\int_enty.src	\
#			$(DEFINE_SH)\mon_mac.hdr	\
#			$(DEFINE_SH)\def_mon.hdr	\
#			$(EXTV_SH)\extv_mon.hdr
#		$(ASM)	$(SRC_SH)\int_enty.src $(ASM_OPT)
# äÑçûÇ›ã÷é~éûä‘ë™íË T.Nose 1998/01/17



!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLAR_L")
$(OBJECT)\int_enty.obj:	$(POPB_SRC)\int_enty.src	\
			$(DEFINE_SH)\mon_mac.hdr	\
			$(DEFINE_SH)\def_mon.hdr	\
			$(EXTV_SH)\extv_mon.hdr
		$(ASM)	$(POPB_SRC)\int_enty.src $(ASM_OPT)
!else
# /* ÉÇÉjÉ^Å[ïsãÔçáã~çœ By O.Kimoto 1998/02/16 */
# !if ("$(MODEL)" == "POPLAR_H") && ("$(COUNTRY)" == "JPN")
!if ("$(MODEL)" == "POPLAR_H")
$(OBJECT)\int_enty.obj:	$(POPH_SRC)\int_enty.src	\
			$(DEFINE_SH)\mon_mac.hdr	\
			$(DEFINE_SH)\def_mon.hdr	\
			$(EXTV_SH)\extv_mon.hdr
		$(ASM)	$(POPH_SRC)\int_enty.src $(ASM_OPT)
!else
!if ("$(MODEL)" == "SAKAKI")
$(OBJECT)\int_enty.obj:	$(SAKI_SRC)\int_enty.src	\
			$(DEFINE_SH)\mon_mac.hdr	\
			$(DEFINE_SH)\def_mon.hdr	\
			$(EXTV_SH)\extv_mon.hdr
		$(ASM)	$(SAKI_SRC)\int_enty.src $(ASM_OPT)
!else
$(OBJECT)\int_enty.obj:	$(SRC_SH)\int_enty.src	\
			$(DEFINE_SH)\mon_mac.hdr	\
			$(DEFINE_SH)\def_mon.hdr	\
			$(EXTV_SH)\extv_mon.hdr
		$(ASM)	$(SRC_SH)\int_enty.src $(ASM_OPT)
!endif
!endif
!endif

# SCI_INTÉtÉ@ÉCÉã
$(OBJECT)\hinoenty.obj:	$(HINO_SRC)\hinoenty.src	\
			$(DEFINE_SH)\def_mon.hdr	\
			$(HINO_DEFINE)\hino_mac.hdr	\
			$(EXTV_SH)\extv_mon.hdr
		$(ASM)	$(HINO_SRC)\hinoenty.src $(ASM_OPT)

$(OBJECT)\int_tim.obj:	$(SRC_SH)\int_tim.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
							\src\atlanta\define\mem_def.h		\
							\src\atlanta\define\dma_blk.h		\
							\src\atlanta\define\sysmax.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
												\src\atlanta\define\message.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
		$(CC) $(OPTION)	$(SRC_SH)\int_tim.c
#
# # äÑçûÇ›ã÷é~éûä‘ë™íË O.Kimoto 1998/02/12
# !if ("$(MODEL)" == "POPLAR_H") && ("$(COUNTRY)" == "JPN")
# $(OBJECT)\int_err.obj:	$(POPH_SRC)\int_err.src
# 		$(ASM)	$(POPH_SRC)\int_err.src $(ASM_OPT)
# !else
# $(OBJECT)\int_err.obj:	$(SRC_SH)\int_err.src
# 		$(ASM)	$(SRC_SH)\int_err.src $(ASM_OPT)
# !endif
$(OBJECT)\int_err.obj:	$(SRC_SH)\int_err.src
		$(ASM)	$(SRC_SH)\int_err.src $(ASM_OPT)
#
$(OBJECT)\int_ext.obj:	$(SRC_SH)\int_ext.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
							\src\atlanta\define\mem_def.h		\
							\src\atlanta\define\dma_blk.h		\
							\src\atlanta\define\sysmax.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
												\src\atlanta\define\message.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
		$(CC) $(OPTION) $(SRC_SH)\int_ext.c
#
