#------------------------------------------------------------------------
#   POPLAR ﾒｲｸ･ﾌｧｲﾙ By Y.Suzuki 1996/10/14
#	とりあえずANZUの下から移植しました。
#   各大機能担当の方で追加、修正願います。
#
#	機種毎で異なるファイルがあるので、それらは該当するメークモジュールに
#	移動させます。（OPR_DATA/MDM_DATA)	By O.Kimoto 1997/09/04
#
#------------------------------------------------------------------------
DEFINE 		= \src\atlanta\define
DEFV 		= \src\atlanta\def_v
DEFVP 		= \src\atlanta\prt\thermal\def_v
DEFVSC 		= \src\atlanta\scd\def_v
EXTV		= \src\atlanta\ext_v
EXTVSC 		= \src\atlanta\scd\ext_v
MDM_OG_DEFV = \src\atlanta\mdm\orange\def_v
SRC			= \src\atlanta\src
WORD		= \src\atlanta\wording
MON			= \src\atlanta\mon
MAKE		= \src\atlanta\make
MSWDEFINE	= \src\memsw\define
SRCSC		= \src\atlanta\scd\src
IU_DEFV		= \src\atlanta\hinoki\def_v
IU_SRC		= \src\atlanta\hinoki\src
DEFINE_SH	=\src\cpu\sh7043_a\irom\define
SRC_SH		=\src\cpu\sh7043_a\irom\src
EXTV_SH		=\src\cpu\sh7043_a\irom\ext_v
DEFV_SH		=\src\cpu\sh7043_a\irom\def_v

#
#-----------------------------------------------------------------------------
#   ｺﾏﾝﾄﾞ名を定義
#-----------------------------------------------------------------------------
CC          = shc
ASM         = asmsh
PTIONO      = /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION2     = /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY)) /se=(d=DRLBUF)
OPTION3     = /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY)) /se=(d=DSCDDATA)
ASM_OPT     = /cpu=$(CPU_OPT) /debug /object=$*.obj

OPTION      = /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
ASM_OPT     = /cpu=sh2 /debug /object=$*.obj

#LNK         = lnk /subcommand=\src\atlanta\make\data.sub

!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI2")) || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU") || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
#ＮｅｗＭａｓｋ対応機種用リンク by O.Kimoto 1998/09/14
# 元々、data.mkには、ソフトコーデック用やスクランブル用が入っていたので、それらを
# 独立させた。
LNK         = lnk /subcommand=\src\atlanta\make\iu_data.sub
!endif




OBJECT      = \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-----------------------------------------------------------------------------
#   ﾎﾟﾌﾟﾗ用ﾃﾞｰﾀﾓｼﾞｭｰﾙのﾘﾝｸを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\iu_data.lnk:		\src\atlanta\make\iu_data.sub	\
			$(OBJECT)\SREG.obj	\
			$(OBJECT)\GA_REG.obj	\
			$(OBJECT)\CPU_REG.obj	\
			$(OBJECT)\INI_GA.obj	\
			$(OBJECT)\INT_GA.obj	\
			$(OBJECT)\KEY_SCN.obj	\
			$(OBJECT)\LCD.obj		\
			$(OBJECT)\HINOENTY.obj	\
			$(OBJECT)\HINO_BUZ.obj	\
			$(OBJECT)\DUMMY.obj		\
			$(OBJECT)\GA_BUF.obj	\
			$(OBJECT)\PAGE_MEM.obj	\
			$(OBJECT)\iu_cdc.obj	\
			$(OBJECT)\scdc_dat.obj	\
			$(OBJECT)\CHK_MPR.obj	\
			$(OBJECT)\rt_copy.obj	\
			$(OBJECT)\sci_ctrl.obj	\
			$(OBJECT)\sci_irpt.obj	\
			$(OBJECT)\sci_dat.obj
			
        $(LNK)
#-----------------------------------------------------------------------------
#   ﾘｱﾙﾀｲﾑﾓﾆﾀﾓｼﾞｭｰﾙのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
$(OBJECT)\sreg.obj:   $(IU_DEFV)\sreg.c	\
				\src\atlanta\define\product.h
        $(CC)   $(OPTION) $(IU_DEFV)\sreg.c
#
$(OBJECT)\ga_reg.obj:   $(IU_DEFV)\ga_reg.c	\
				\src\atlanta\define\product.h
        $(CC)   $(OPTION) $(IU_DEFV)\ga_reg.c
#
$(OBJECT)\cpu_reg.obj:   $(IU_DEFV)\cpu_reg.c	\
				\src\atlanta\define\product.h
        $(CC)   $(OPTION) $(IU_DEFV)\cpu_reg.c
#
$(OBJECT)\ini_ga.obj:   $(IU_SRC)\ini_ga.c	\
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
        $(CC)   $(OPTION) $(IU_SRC)\ini_ga.c
#
$(OBJECT)\int_ga.obj:   $(IU_SRC)\int_ga.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\hinoki\define\hinoport.h		\
				\src\atlanta\opr\ank\define\opr_pro.h		\
							\src\atlanta\define\mem_def.h		\
							\src\atlanta\define\dma_blk.h		\
							\src\atlanta\define\sysmax.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
												\src\atlanta\define\message.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
        $(CC)   $(OPTION) $(IU_SRC)\int_ga.c
#
$(OBJECT)\key_scn.obj:   $(IU_SRC)\key_scn.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\opr\ank\ext_v\opr_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\opr\ank\define\opr_def.h		\
						\src\atlanta\define\syscomf.h		\
							\src\atlanta\define\sysdial.h		\
						\src\atlanta\define\sysdoc.h		\
						\src\atlanta\define\sysonet.h		\
							\src\atlanta\define\sysspeed.h		\
						\src\atlanta\define\time.h		\
						\src\atlanta\define\sys_infd.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
					\src\cpu\sh7043_a\irom\define\def_evtn.h
        $(CC)   $(OPTION) $(IU_SRC)\key_scn.c
#
$(OBJECT)\lcd.obj:   $(IU_SRC)\lcd.c	\
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
        $(CC)   $(OPTION) $(IU_SRC)\lcd.c
#
$(OBJECT)\hinoenty.obj:	$(IU_SRC)\hinoenty.src	\
			$(DEFINE_SH)\mon_mac.hdr	\
			$(DEFINE_SH)\def_mon.hdr	\
			$(EXTV_SH)\extv_mon.hdr
		$(ASM)	$(IU_SRC)\hinoenty.src $(ASM_OPT)
#
$(OBJECT)\hino_buz.obj:   $(IU_SRC)\hino_buz.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\buzzer.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\std.h		\
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
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
        $(CC)   $(OPTION) $(IU_SRC)\hino_buz.c
#
$(OBJECT)\dummy.obj:   $(IU_SRC)\dummy.c
        $(CC)   $(OPTION) $(IU_SRC)\dummy.c
#
$(OBJECT)\ga_buf.obj:   $(IU_DEFV)\ga_buf.c \
				\src\atlanta\define\product.h
        $(CC)   $(OPTION) $(IU_DEFV)\ga_buf.c
#
$(OBJECT)\page_mem.obj:   $(IU_DEFV)\page_mem.c \
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\hinoki\define\scn_def.h
        $(CC)   $(OPTION) $(IU_DEFV)\page_mem.c
#
$(OBJECT)\chk_mpr.obj:   $(IU_SRC)\chk_mpr.c \
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\SYSMAX.h		\
					\src\atlanta\define\sysbatch.h		\
						\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysonet.h		\
					\src\atlanta\define\sysexec.h		\
					\src\atlanta\define\sysmcopy.h		\
					\src\atlanta\define\syslifem.h		\
					\src\atlanta\define\sysshad.h		\
					\src\atlanta\define\sysspeed.h		\
					\src\atlanta\define\sysdiali.h		\
					\src\atlanta\define\sysmemrx.h		\
					\src\atlanta\define\syscost.h		\
					\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysdeprt.h		\
					\src\atlanta\define\systbok.h		\
					\src\atlanta\define\sysopspd.h		\
					\src\atlanta\define\sysringm.h		\
						\src\atlanta\define\ncu_cnst.h		\
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\sysorder.h		\
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sys_infd.h		\
					\src\atlanta\define\syswarp.h		\
					\src\atlanta\define\sysnd.h		\
					\src\atlanta\define\sysmcr.h		\
							\src\atlanta\define\dma_blk.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
												\src\atlanta\define\message.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
        $(CC)   $(OPTION) $(IU_SRC)\chk_mpr.c
#
$(OBJECT)\iu_cdc.obj:   $(IU_SRC)\iu_cdc.c \
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mntsw_a.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\syspcrx.h		\
							\src\atlanta\define\dma_blk.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
        $(CC)   $(OPTION) $(IU_SRC)\iu_cdc.c
#
$(OBJECT)\scdc_dat.obj:   $(IU_DEFV)\scdc_dat.c \
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mem_def.h		\
				\src\cpu\sh7043_a\scd\define\scd.h
        $(CC)   $(OPTION) $(IU_DEFV)\scdc_dat.c
#
$(OBJECT)\rt_copy.obj:   $(IU_SRC)\rt_copy.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\realtcpy.h
        $(CC)   $(OPTION) $(IU_SRC)\rt_copy.c
#
$(OBJECT)\sci_ctrl.obj:   $(IU_SRC)\sci_ctrl.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h
        $(CC)   $(OPTION) $(IU_SRC)\sci_ctrl.c
#
$(OBJECT)\sci_irpt.obj:   $(IU_SRC)\sci_irpt.c	\
				\src\atlanta\define\product.h	\
				\src\atlanta\define\std.h
        $(CC)   $(OPTION) $(IU_SRC)\sci_irpt.c
#
$(OBJECT)\sci_dat.obj:   $(IU_DEFV)\sci_dat.c	\
				\src\atlanta\define\product.h	\
				\src\atlanta\define\std.h
        $(CC)   $(OPTION) $(IU_DEFV)\sci_dat.c
#
