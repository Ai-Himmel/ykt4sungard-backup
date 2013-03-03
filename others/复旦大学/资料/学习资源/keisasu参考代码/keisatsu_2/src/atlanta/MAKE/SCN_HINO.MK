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
LNK         = lnk /subcommand=\src\atlanta\make\scn_hino.sub
!endif




OBJECT      = \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-----------------------------------------------------------------------------
#   ﾎﾟﾌﾟﾗ用ﾃﾞｰﾀﾓｼﾞｭｰﾙのﾘﾝｸを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\scn_hino.lnk:		\src\atlanta\make\scn_hino.sub	\
			$(OBJECT)\SCN_DATH.obj	\
			$(OBJECT)\SCN_INTH.obj	\
			$(OBJECT)\SCN_BUF.obj	\
			$(OBJECT)\SCN_DOC.obj	\
			$(OBJECT)\SCN_IP.obj	\
			$(OBJECT)\SCN_SENS.obj	\
			$(OBJECT)\SCNSHADE.obj	\
			$(OBJECT)\SCNSTAMP.obj	\
			$(OBJECT)\SCANNER.obj	\
			$(OBJECT)\SCNPOWER.obj	\
			$(OBJECT)\SCNSTORE.obj	\
			$(OBJECT)\SCN_MISC.obj	\
			$(OBJECT)\SCN_MTR.obj	\
			$(OBJECT)\SCN_INZ.obj	\
			$(OBJECT)\SCNDOCIN.obj	\
			$(OBJECT)\SCN_ENC.obj
        $(LNK)
#-----------------------------------------------------------------------------
#   ﾘｱﾙﾀｲﾑﾓﾆﾀﾓｼﾞｭｰﾙのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
$(OBJECT)\SCN_DATH.obj:	$(IU_DEFV)\SCN_DATH.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\hinoki\define\scn_def.h
	$(CC)	$(OPTION) $(IU_DEFV)\SCN_DATH.c
#
$(OBJECT)\SCN_INTH.obj:	$(IU_SRC)\SCN_INTH.c \
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\hinoki\define\scn_def.h		\
				\src\atlanta\hinoki\define\scn_pro.h		\
					\src\atlanta\define\message.h		\
				\src\atlanta\hinoki\ext_v\scn_dath.h		\
				\src\atlanta\hinoki\ext_v\scn_tbl.h		\
				\src\cpu\sh7043_a\irom\define\def_evtn.h		\
				\src\cpu\sh7043_a\irom\define\sh_port.h		\
					\src\atlanta\hinoki\define\hinoport.h		\
				\src\cpu\sh7043_a\irom\define\io_pro.h		\
							\src\atlanta\define\mem_def.h		\
							\src\atlanta\define\dma_blk.h		\
							\src\atlanta\define\sysmax.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
	$(CC)	$(OPTION) $(IU_SRC)\SCN_INTH.c
#
$(OBJECT)\SCN_BUF.obj:	$(IU_SRC)\SCN_BUF.c \
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\hinoki\define\scn_pro.h		\
					\src\atlanta\define\message.h		\
				\src\atlanta\hinoki\define\scn_def.h		\
				\src\atlanta\hinoki\ext_v\page_mem.h		\
				\src\atlanta\hinoki\ext_v\scn_dath.h		\
				\src\atlanta\hinoki\ext_v\scn_tbl.h		\
				\src\atlanta\hinoki\ext_v\ga_buf.h		\
								\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
									\src\cpu\sh7043_a\irom\define\def_tcb.h		\
									\src\cpu\sh7043_a\irom\define\def_scb.h		\
									\src\cpu\sh7043_a\irom\define\def_semn.h		\
									\src\cpu\sh7043_a\irom\define\def_mbxn.h		\
									\src\atlanta\define\mem_def.h		\
									\src\atlanta\define\dma_blk.h		\
									\src\atlanta\define\sysmax.h
	$(CC)	$(OPTION) $(IU_SRC)\SCN_BUF.c
#
$(OBJECT)\SCN_DOC.obj:	$(IU_SRC)\SCN_DOC.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mntsw_c.h		\
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
	$(CC)	$(OPTION) $(IU_SRC)\SCN_DOC.c
#
$(OBJECT)\SCN_ENC.obj:	$(IU_SRC)\SCN_ENC.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\mem_pro.h		\
					\src\atlanta\ext_v\memertbl.h		\
						\src\atlanta\define\mem_def.h		\
						\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
							\src\cpu\sh7043_a\irom\define\def_tcb.h		\
							\src\cpu\sh7043_a\irom\define\def_scb.h		\
							\src\cpu\sh7043_a\irom\define\def_semn.h		\
							\src\cpu\sh7043_a\irom\define\def_mbxn.h		\
							\src\atlanta\define\dma_blk.h		\
							\src\atlanta\define\sysmax.h
	$(CC)	$(OPTION) $(IU_SRC)\SCN_ENC.c
#
$(OBJECT)\SCN_IP.obj:	$(IU_SRC)\SCN_IP.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysshad.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mon_pro.h		\
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
	$(CC)	$(OPTION) $(IU_SRC)\SCN_IP.c
#
$(OBJECT)\SCN_SENS.obj:	$(IU_SRC)\SCN_SENS.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\hinoki\define\scn_pro.h		\
					\src\atlanta\define\message.h		\
				\src\atlanta\hinoki\define\scn_def.h		\
				\src\atlanta\hinoki\ext_v\scn_tbl.h		\
				\src\atlanta\hinoki\ext_v\scn_dath.h		\
				\src\cpu\sh7043_a\irom\define\sh_port.h		\
					\src\atlanta\hinoki\define\hinoport.h		\
				\src\cpu\sh7043_a\irom\define\io_pro.h		\
							\src\atlanta\define\mem_def.h		\
							\src\atlanta\define\dma_blk.h		\
							\src\atlanta\define\sysmax.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
	$(CC)	$(OPTION) $(IU_SRC)\SCN_SENS.c
#
$(OBJECT)\SCNSHADE.obj:	$(IU_SRC)\SCNSHADE.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\scn_def.h		\
				\src\atlanta\ext_v\scn_data.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\sys_data.h		\
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
	$(CC)	$(OPTION) $(IU_SRC)\SCNSHADE.c
#
$(OBJECT)\SCNSTAMP.obj:	$(IU_SRC)\SCNSTAMP.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\syslocal.h		\
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
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
	$(CC)	$(OPTION) $(IU_SRC)\SCNSTAMP.c
#
$(OBJECT)\SCANNER.obj:	$(IU_SRC)\SCANNER.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\message.h		\
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
	$(CC)	$(OPTION) $(IU_SRC)\SCANNER.c
#
$(OBJECT)\SCNPOWER.obj:	$(IU_SRC)\SCNPOWER.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\hinoki\define\scn_def.h		\
				\src\atlanta\hinoki\define\scn_pro.h		\
					\src\atlanta\define\message.h		\
				\src\atlanta\hinoki\ext_v\scn_dath.h		\
				\src\atlanta\hinoki\ext_v\scn_tbl.h
	$(CC)	$(OPTION) $(IU_SRC)\SCNPOWER.c
#
$(OBJECT)\SCNSTORE.obj:	$(IU_SRC)\SCNSTORE.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\scn_def.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\ext_v\scn_data.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\sys_data.h		\
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
	$(CC)	$(OPTION) $(IU_SRC)\SCNSTORE.c
#
$(OBJECT)\SCN_MISC.obj:	$(IU_SRC)\SCN_MISC.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\hinoki\define\scn_pro.h		\
				\src\atlanta\hinoki\define\scn_def.h		\
				\src\atlanta\hinoki\ext_v\scn_dath.h		\
				\src\atlanta\hinoki\ext_v\ga_buf.h		\
								\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
									\src\cpu\sh7043_a\irom\define\def_tcb.h		\
									\src\cpu\sh7043_a\irom\define\def_scb.h		\
									\src\cpu\sh7043_a\irom\define\def_semn.h		\
									\src\cpu\sh7043_a\irom\define\def_mbxn.h		\
									\src\atlanta\define\mem_def.h		\
									\src\atlanta\define\dma_blk.h		\
									\src\atlanta\define\sysmax.h
	$(CC)	$(OPTION) $(IU_SRC)\SCN_MISC.c
#
$(OBJECT)\SCN_MTR.obj:	$(IU_SRC)\SCN_MTR.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\mntsw_h.h		\
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
	$(CC)	$(OPTION) $(IU_SRC)\SCN_MTR.c
#
$(OBJECT)\SCN_INZ.obj:	$(IU_SRC)\SCN_INZ.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
						\src\atlanta\define\mem_def.h		\
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
	$(CC)	$(OPTION) $(IU_SRC)\SCN_INZ.c
#
$(OBJECT)\SCNDOCIN.obj:	$(IU_SRC)\SCNDOCIN.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\ext_v\scn_data.h		\
					\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\hinoki\define\scn_def.h		\
				\src\atlanta\hinoki\define\scn_pro.h		\
				\src\atlanta\hinoki\ext_v\scn_dath.h		\
				\src\atlanta\hinoki\ext_v\scn_tbl.h		\
				\src\cpu\sh7043_a\irom\define\def_evtn.h		\
				\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h		\
					\src\cpu\sh7043_a\irom\define\def_mbxn.h		\
					\src\atlanta\sh7043\define\def_mbxn.h
	$(CC)	$(OPTION) $(IU_SRC)\SCNDOCIN.c
#
