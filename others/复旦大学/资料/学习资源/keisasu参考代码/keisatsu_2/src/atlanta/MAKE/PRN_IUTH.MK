#------------------------------------------------------------------------
#   HINOKI	プリンタメイクファイル
#------------------------------------------------------------------------
SRC		= \src\atlanta\src
DEFINE 		= \src\atlanta\define
DEFV 		= \src\atlanta\def_v
EXTV		= \src\atlanta\ext_v
SRC_IUTH	= \src\atlanta\prt\iu_therm\src
DEFINE_TRML	= \src\atlanta\prt\iu_therm\define
DEFV_TRML	= \src\atlanta\prt\iu_therm\def_v
EXTV_TRML	= \src\atlanta\prt\iu_therm\ext_v
MONSH		= \src\atlanta\sh7043\mon
MAKE		= \src\atlanta\make

#-----------------------------------------------------------------------------
#	RISC結合用ﾏｸﾛ
#-----------------------------------------------------------------------------
#
CC			= shc
ASM			= asmsh

!if ("$(MODEL)" == "KEISATSU")
#最適化します 2005/11/17
OPTION		= /op=1 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!else
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
ASM_OPT		= /cpu=sh2 /debug /object=$*.obj
LNK			= lnk /subcommand=\src\atlanta\make\prn_iuth.sub
OBJECT      = \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-----------------------------------------------------------------------------
#	ﾌﾟﾘﾝﾀﾓｼﾞｭｰﾙのﾘﾝｸを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\print.lnk:	\src\atlanta\make\prn_iuth.sub	\
			$(OBJECT)\PRT_TBL.obj			\
			$(OBJECT)\PRT_DATA.obj			\
#			$(OBJECT)\PRT_DEC.obj			\
			$(OBJECT)\PRT_DIRC.obj			\
#			$(OBJECT)\PRT_DMA.obj			\
			$(OBJECT)\PRT_DRV.obj			\
			$(OBJECT)\PRT_INT.obj			\
#			$(OBJECT)\PRT_PAGE.obj			\
			$(OBJECT)\PRTLIFE.obj			\
#			$(OBJECT)\PRTPGEND.obj			\
			$(OBJECT)\PRTPRIMG.obj			\
#			$(OBJECT)\PRTQUEUE.obj			\
#			$(OBJECT)\PRTRESET.obj			\
			$(OBJECT)\PRTENGIN.obj			\
			$(OBJECT)\PRTMAINM.obj			\
			$(OBJECT)\PRTMKIMG.obj			\
			$(OBJECT)\PRTPAPER.obj			\
			$(OBJECT)\PRTPOWER.obj			\
			$(OBJECT)\PRT_INZ.obj			\
#			$(OBJECT)\PRT_LST.obj			\
			$(OBJECT)\PRT_MTR.obj			\
#			$(OBJECT)\PRT_ADDQ.obj			\
			$(OBJECT)\PRTTHRML.obj			\
#			$(OBJECT)\PRTWATCH.obj			\
			$(OBJECT)\PRTPGMEM.obj			\
			$(OBJECT)\PRN_MAIN.obj			\
			$(OBJECT)\PRN_QUE.obj			\
			$(OBJECT)\PRN_INIT.obj			\
			$(OBJECT)\PRN_DRV.obj			\
			$(OBJECT)\PRN_IMG.obj			\
			$(OBJECT)\PRN_DATA.obj
			
 		$(LNK)
#-----------------------------------------------------------------------------
#	ﾌﾟﾘﾝﾀﾓｼﾞｭｰﾙのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
#
$(OBJECT)\PRT_TBL.obj: $(DEFV_TRML)\PRT_TBL.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\hinoki\define\scn_def.h		\
				\src\atlanta\prt\iu_therm\define\prt_drv.h		\
					\src\atlanta\prt\iu_therm\define\prtqueue.h		\
						\src\atlanta\define\mem_def.h		\
				\src\cpu\sh7043_a\irom\define\sh_port.h		\
					\src\atlanta\hinoki\define\hinoport.h
	$(CC)	$(OPTION)	$(DEFV_TRML)\PRT_TBL.c
#
$(OBJECT)\PRT_DATA.obj: $(DEFV_TRML)\PRT_DATA.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\hinoki\define\scn_def.h		\
				\src\atlanta\prt\iu_therm\define\prt_drv.h		\
				\src\atlanta\prt\iu_therm\define\prtqueue.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\prt\iu_therm\define\prt_def.h
	$(CC)	$(OPTION)	$(DEFV_TRML)\PRT_DATA.c
#
#$(OBJECT)\PRT_DEC.obj: $(SRC_IUTH)\PRT_DEC.c	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\define\std.h		\
#				\src\atlanta\define\message.h		\
#				\src\atlanta\define\sysdoc.h		\
#				\src\atlanta\prt\iu_therm\ext_v\prt_data.h		\
#					\src\atlanta\hinoki\define\scn_def.h		\
#					\src\atlanta\prt\iu_therm\define\prt_drv.h		\
#					\src\atlanta\prt\iu_therm\define\prtqueue.h		\
#						\src\atlanta\define\mem_def.h		\
#					\src\atlanta\prt\iu_therm\define\prt_def.h		\
#				\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h
#	$(CC)	$(OPTION)	$(SRC_IUTH)\PRT_DEC.c
#
$(OBJECT)\PRT_DIRC.obj: $(SRC_IUTH)\PRT_DIRC.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\memfile.h		\
				\src\atlanta\ext_v\sys_data.h		\
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
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRT_DIRC.c
#
#$(OBJECT)\PRT_DMA.obj: $(SRC_IUTH)\PRT_DMA.c	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\define\std.h		\
#				\src\atlanta\define\mon_pro.h		\
#				\src\atlanta\prt\iu_therm\define\prt_dma.h		\
#				\src\cpu\sh7043_a\irom\define\sh_sys.h		\
#					\src\atlanta\hinoki\define\hino_sys.h		\
#				\src\cpu\sh7043_a\irom\define\sh_port.h		\
#					\src\atlanta\hinoki\define\hinoport.h		\
#				\src\atlanta\prt\iu_therm\ext_v\prt_data.h		\
#					\src\atlanta\hinoki\define\scn_def.h		\
#					\src\atlanta\prt\iu_therm\define\prt_drv.h		\
#					\src\atlanta\prt\iu_therm\define\prtqueue.h		\
#						\src\atlanta\define\mem_def.h		\
#					\src\atlanta\prt\iu_therm\define\prt_def.h		\
#				\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h		\
#				\src\cpu\sh7043_a\irom\define\io_pro.h		\
#							\src\atlanta\define\dma_blk.h		\
#							\src\atlanta\define\sysmax.h		\
#										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
#											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
#												\src\atlanta\define\message.h		\
#											\src\cpu\sh7043_a\irom\define\def_scb.h		\
#											\src\cpu\sh7043_a\irom\define\def_semn.h		\
#											\src\cpu\sh7043_a\irom\define\def_mbxn.h
#	$(CC)	$(OPTION)	$(SRC_IUTH)\PRT_DMA.c
#
$(OBJECT)\PRT_DRV.obj: $(SRC_IUTH)\PRT_DRV.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\prt\iu_therm\ext_v\prt_data.h		\
					\src\atlanta\hinoki\define\scn_def.h		\
					\src\atlanta\prt\iu_therm\define\prt_drv.h		\
					\src\atlanta\prt\iu_therm\define\prtqueue.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\prt\iu_therm\define\prt_def.h		\
				\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h		\
				\src\atlanta\prt\iu_therm\define\prt_pro.h		\
				\src\atlanta\hinoki\define\scn_pro.h		\
					\src\atlanta\define\message.h		\
				\src\atlanta\hinoki\define\mpr_pro.h		\
				\src\cpu\sh7043_a\irom\define\def_evtn.h
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRT_DRV.c
#
$(OBJECT)\PRT_INT.obj: $(SRC_IUTH)\PRT_INT.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\sysdoc.h		\
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
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRT_INT.c
#
#$(OBJECT)\PRT_PAGE.obj: $(SRC_IUTH)\PRT_PAGE.c	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\define\std.h		\
#				\src\atlanta\prt\iu_therm\define\prt_def.h		\
#				\src\atlanta\prt\iu_therm\define\prtqueue.h		\
#					\src\atlanta\define\mem_def.h		\
#				\src\atlanta\prt\iu_therm\define\prt_drv.h		\
#				\src\atlanta\prt\iu_therm\define\prt_pro.h		\
#				\src\atlanta\prt\iu_therm\ext_v\prt_data.h		\
#					\src\atlanta\hinoki\define\scn_def.h		\
#				\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h
#	$(CC)	$(OPTION)	$(SRC_IUTH)\PRT_PAGE.c
#
$(OBJECT)\PRTLIFE.obj: $(SRC_IUTH)\PRTLIFE.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
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
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRTLIFE.c
#
#$(OBJECT)\PRTPGEND.obj: $(SRC_IUTH)\PRTPGEND.c	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\define\std.h		\
#				\src\atlanta\prt\iu_therm\ext_v\prt_data.h		\
#					\src\atlanta\hinoki\define\scn_def.h		\
#					\src\atlanta\prt\iu_therm\define\prt_drv.h		\
#					\src\atlanta\prt\iu_therm\define\prtqueue.h		\
#						\src\atlanta\define\mem_def.h		\
#				\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h		\
#				\src\atlanta\prt\iu_therm\define\prt_def.h		\
#				\src\atlanta\prt\iu_therm\define\prt_pro.h
#	$(CC)	$(OPTION)	$(SRC_IUTH)\PRTPGEND.c
#
$(OBJECT)\PRTPRIMG.obj: $(SRC_IUTH)\PRTPRIMG.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\ext_v\sys_data.h		\
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
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRTPRIMG.c
#
#$(OBJECT)\PRTQUEUE.obj: $(SRC_IUTH)\PRTQUEUE.c	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\define\std.h		\
#				\src\atlanta\prt\iu_therm\ext_v\prt_data.h		\
#					\src\atlanta\hinoki\define\scn_def.h		\
#					\src\atlanta\prt\iu_therm\define\prt_drv.h		\
#					\src\atlanta\prt\iu_therm\define\prtqueue.h		\
#						\src\atlanta\define\mem_def.h		\
#				\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h		\
#				\src\atlanta\prt\iu_therm\define\prt_def.h		\
#				\src\atlanta\prt\iu_therm\define\prt_pro.h
#	$(CC)	$(OPTION)	$(SRC_IUTH)\PRTQUEUE.c
#
#$(OBJECT)\PRTRESET.obj: $(SRC_IUTH)\PRTRESET.c	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\define\std.h		\
#				\src\atlanta\define\mon_pro.h		\
#				\src\atlanta\define\uni_pro.h		\
#							\src\atlanta\define\mem_def.h		\
#							\src\atlanta\define\dma_blk.h		\
#							\src\atlanta\define\sysmax.h		\
#										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
#											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
#												\src\atlanta\define\message.h		\
#											\src\cpu\sh7043_a\irom\define\def_scb.h		\
#											\src\cpu\sh7043_a\irom\define\def_semn.h		\
#											\src\cpu\sh7043_a\irom\define\def_mbxn.h
#	$(CC)	$(OPTION)	$(SRC_IUTH)\PRTRESET.c
#
$(OBJECT)\PRTENGIN.obj: $(SRC_IUTH)\PRTENGIN.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\status.h		\
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
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRTENGIN.c
#
$(OBJECT)\PRTMAINM.obj: $(SRC_IUTH)\PRTMAINM.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\dma_pro.h		\
							\src\atlanta\define\dma_blk.h		\
							\src\atlanta\define\sysmax.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRTMAINM.c
#
$(OBJECT)\PRTMKIMG.obj: $(SRC_IUTH)\PRTMKIMG.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\mon_pro.h		\
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
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRTMKIMG.c
#
$(OBJECT)\PRTPAPER.obj: $(SRC_IUTH)\PRTPAPER.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\prt\iu_therm\ext_v\prt_data.h		\
					\src\atlanta\hinoki\define\scn_def.h		\
					\src\atlanta\prt\iu_therm\define\prt_drv.h		\
				\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h		\
				\src\atlanta\prt\iu_therm\define\prt_def.h		\
				\src\atlanta\prt\iu_therm\define\prt_pro.h		\
				\src\atlanta\hinoki\define\mpr_pro.h		\
				\src\atlanta\prt\iu_therm\ext_v\prn_data.h		\
					\src\atlanta\define\sysmcopy.h		\
					\src\atlanta\define\sysmemrx.h		\
						\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\syslifem.h		\
					\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\dma_blk.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\syscph.h		\
						\src\atlanta\define\sysmax.h		\
						\src\cpu\sh7043_a\scd\define\scd.h		\
				\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
					\src\cpu\sh7043_a\irom\define\def_tcb.h		\
					\src\cpu\sh7043_a\irom\define\def_scb.h		\
					\src\cpu\sh7043_a\irom\define\def_semn.h		\
					\src\cpu\sh7043_a\irom\define\def_mbxn.h
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRTPAPER.c
#
$(OBJECT)\PRTPOWER.obj: $(SRC_IUTH)\PRTPOWER.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\prt\iu_therm\ext_v\prt_data.h		\
					\src\atlanta\prt\iu_therm\define\prt_drv.h		\
					\src\atlanta\prt\iu_therm\define\prtqueue.h		\
						\src\atlanta\define\mem_def.h		\
				\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h		\
				\src\atlanta\prt\iu_therm\define\prt_def.h		\
				\src\atlanta\prt\iu_therm\define\prt_pro.h		\
				\src\atlanta\hinoki\define\scn_def.h		\
				\src\atlanta\hinoki\ext_v\scn_data.h		\
					\src\atlanta\define\message.h
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRTPOWER.c
#
$(OBJECT)\PRT_INZ.obj: $(SRC_IUTH)\PRT_INZ.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\sys_stat.h		\
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
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRT_INZ.c
#
#$(OBJECT)\PRT_LST.obj: $(SRC_IUTH)\PRT_LST.c	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\define\std.h		\
#				\src\atlanta\define\mon_pro.h		\
#				\src\atlanta\define\message.h		\
#				\src\atlanta\define\sysdoc.h		\
#				\src\atlanta\prt\iu_therm\ext_v\prt_data.h		\
#					\src\atlanta\hinoki\define\scn_def.h		\
#					\src\atlanta\prt\iu_therm\define\prt_drv.h		\
#					\src\atlanta\prt\iu_therm\define\prtqueue.h		\
#						\src\atlanta\define\mem_def.h		\
#				\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h		\
#				\src\atlanta\prt\iu_therm\define\prt_def.h		\
#				\src\atlanta\prt\iu_therm\define\lst_def.h		\
#				\src\atlanta\prt\iu_therm\define\prt_pro.h
#	$(CC)	$(OPTION)	$(SRC_IUTH)\PRT_LST.c
#
$(OBJECT)\PRT_MTR.obj: $(SRC_IUTH)\PRT_MTR.c	\
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
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRT_MTR.c
#
#$(OBJECT)\PRT_ADDQ.obj: $(SRC_IUTH)\PRT_ADDQ.c	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\define\std.h		\
#				\src\atlanta\define\mem_def.h		\
#				\src\atlanta\define\memfile.h		\
#				\src\atlanta\define\message.h		\
#				\src\atlanta\define\apl_msg.h		\
#				\src\atlanta\define\sysprint.h		\
#				\src\atlanta\define\mon_pro.h		\
#				\src\atlanta\ext_v\sys_data.h		\
#					\src\atlanta\define\sysmax.h		\
#					\src\atlanta\define\time.h		\
#					\src\atlanta\define\sysdblk.h		\
#					\src\atlanta\define\sysdial.h		\
#					\src\atlanta\define\sysjrnl.h		\
#					\src\atlanta\define\fip_def.h		\
#					\src\atlanta\define\sys_opt.h		\
#					\src\atlanta\define\sysdisp.h		\
#					\src\atlanta\define\syspcrx.h		\
#							\src\atlanta\define\dma_blk.h		\
#										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
#											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
#											\src\cpu\sh7043_a\irom\define\def_scb.h		\
#											\src\cpu\sh7043_a\irom\define\def_semn.h		\
#											\src\cpu\sh7043_a\irom\define\def_mbxn.h
#	$(CC)	$(OPTION)	$(SRC_IUTH)\PRT_ADDQ.c
#
$(OBJECT)\PRTTHRML.obj: $(SRC_IUTH)\PRTTHRML.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\sysdoc.h		\
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
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRTTHRML.c
#
#$(OBJECT)\PRTWATCH.obj: $(SRC_IUTH)\PRTWATCH.c	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\define\std.h		\
#				\src\atlanta\define\mon_pro.h		\
#				\src\atlanta\define\sysdoc.h		\
#				\src\atlanta\define\message.h		\
#				\src\atlanta\define\apl_msg.h		\
#				\src\atlanta\define\man_pro.h		\
#				\src\atlanta\prt\iu_therm\ext_v\prt_data.h		\
#					\src\atlanta\hinoki\define\scn_def.h		\
#					\src\atlanta\prt\iu_therm\define\prt_drv.h		\
#					\src\atlanta\prt\iu_therm\define\prtqueue.h		\
#						\src\atlanta\define\mem_def.h		\
#				\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h		\
#				\src\atlanta\prt\iu_therm\define\prt_def.h		\
#				\src\atlanta\prt\iu_therm\define\prt_pro.h		\
#				\src\cpu\sh7043_a\irom\define\sh_port.h		\
#					\src\atlanta\hinoki\define\hinoport.h		\
#				\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h		\
#					\src\cpu\sh7043_a\irom\define\def_mbxn.h		\
#					\src\atlanta\sh7043\define\def_mbxn.h		\
#				\src\cpu\sh7043_a\irom\define\def_tib.h		\
#					\src\atlanta\hinoki\define\hino_tib.h		\
#				\src\cpu\sh7043_a\irom\define\def_evtn.h
#	$(CC)	$(OPTION)	$(SRC_IUTH)\PRTWATCH.c
#
$(OBJECT)\PRTPGMEM.obj: $(SRC_IUTH)\PRTPGMEM.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\sysdoc.h		\
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
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRTPGMEM.c
#
$(OBJECT)\PRN_MAIN.obj: $(SRC_IUTH)\PRN_MAIN.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\sysprint.h		\
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
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRN_MAIN.c

$(OBJECT)\PRN_QUE.obj: $(SRC_IUTH)\PRN_QUE.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\sysmemrx.h		\
					\src\atlanta\define\sysjrnl.h		\
						\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\mntsw_c.h		\
				\src\atlanta\define\mntsw_h.h		\
				\src\atlanta\define\mnt_sw.h		\
					\src\atlanta\define\mntsw_a.h		\
					\src\atlanta\define\mntsw_b.h		\
					\src\atlanta\define\mntsw_d.h		\
					\src\atlanta\define\mntsw_e.h		\
					\src\atlanta\define\mntsw_f.h		\
					\src\atlanta\define\mntsw_g.h		\
					\src\atlanta\define\mntsw_i.h		\
					\src\atlanta\define\mntsw_j.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
							\src\atlanta\define\dma_blk.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
												\src\atlanta\define\message.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRN_QUE.c

$(OBJECT)\PRN_INIT.obj: $(SRC_IUTH)\PRN_INIT.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\syslifem.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
							\src\atlanta\define\mem_def.h		\
							\src\atlanta\define\dma_blk.h		\
							\src\atlanta\define\sysmax.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
												\src\atlanta\define\message.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRN_INIT.c

$(OBJECT)\PRN_DRV.obj: $(SRC_IUTH)\PRN_DRV.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
							\src\atlanta\define\dma_blk.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
												\src\atlanta\define\message.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRN_DRV.c

$(OBJECT)\PRN_IMG.obj: $(SRC_IUTH)\PRN_IMG.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\mem_pro.h		\
					\src\atlanta\ext_v\memertbl.h		\
						\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
							\src\cpu\sh7043_a\irom\define\def_tcb.h		\
							\src\cpu\sh7043_a\irom\define\def_scb.h		\
							\src\cpu\sh7043_a\irom\define\def_semn.h		\
							\src\cpu\sh7043_a\irom\define\def_mbxn.h		\
							\src\atlanta\define\dma_blk.h		\
							\src\atlanta\define\sysmax.h
	$(CC)	$(OPTION)	$(SRC_IUTH)\PRN_IMG.c
#
$(OBJECT)\PRN_DATA.obj: $(DEFV_TRML)\PRN_DATA.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\sysmemrx.h		\
					\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\define\syslifem.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\dma_blk.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\syscph.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sysdoc.h		\
					\src\cpu\sh7043_a\scd\define\scd.h
	$(CC)	$(OPTION)	$(DEFV_TRML)\PRN_DATA.c

