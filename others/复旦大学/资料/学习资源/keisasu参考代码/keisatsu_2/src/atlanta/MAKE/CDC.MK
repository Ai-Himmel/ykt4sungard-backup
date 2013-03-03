#------------------------------------------------------------------------
#   POPLAR/ANZU_L   コーデック部(CDC)のメイクファイル
#   1996/10/14		Transplanted from \src\kobe\anzu\make By M.Kotnai
#------------------------------------------------------------------------
#
DEFINE	 	= \src\atlanta\define
DEFINESH	= \src\atlanta\sh7043\define
DEFV 		= \src\atlanta\def_v
DEFVSH		= \src\atlanta\sh7043\def_v
EXTV		= \src\atlanta\ext_v
EXTVSH		= \src\atlanta\sh7043\ext_v
SRC			= \src\atlanta\src
SRCSH		= \src\atlanta\sh7043\src
WORDING		= \src\atlanta\wording
MONSH		= \src\atlanta\sh7043\mon
MAKE		= \src\atlanta\make
#
MSWDEFINE	= \src\memsw\define
PROTO_TYPE =	$(DEFINE)\protype.h
MEMORY_SWITCH =	$(MSWDEFINE)\mem_sw_a.h	$(MSWDEFINE)\mem_sw_b.h	\
				$(MSWDEFINE)\mem_sw_c.h	$(MSWDEFINE)\mem_sw_d.h	\
				$(MSWDEFINE)\mem_sw_e.h	$(MSWDEFINE)\mem_sw_f.h	\
				$(MSWDEFINE)\mem_sw_g.h	$(MSWDEFINE)\mem_sw_h.h	\
				$(MSWDEFINE)\mem_sw_i.h	$(MSWDEFINE)\mem_sw_j.h
#
#-----------------------------------------------------------------------------
#   ｺﾏﾝﾄﾞ名を定義
#-----------------------------------------------------------------------------
CC          = shc
ASM         = asmsh
LNK         = lnk /subcommand=\src\atlanta\make\CDC.sub
#-----------------------------------------------------------------------------
#   引数を定義
#-----------------------------------------------------------------------------
OPTION      = /op=0 /deb /def=($(MODEL),$(COUNTRY)) /cp=sh2
#!if ("$(MODEL)" == "POPLAR_B")
!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLR_BN")
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!if ("$(COUNTRY)" == "USA")
OPTION	= /op=1 /size /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
!endif
!if ("$(MODEL)" == "POPLAR_H")
#OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
#初期デバッグ中なのでオプションなしにします。デバッグ終了後戻します
OPTION = /op=0 /deb /def=($(MODEL),$(COUNTRY)) /cp=sh2
!endif

ASM_OPT     = /cpu=$(CPU_OPT) /debug /object=$*.obj
#-----------------------------------------------------------------------------
#   オブジェクトディレクトリを定義
#-----------------------------------------------------------------------------
OBJECT      = \src\atlanta\$(MODEL)\work\$(COUNTRY)
#
#-----------------------------------------------------------------------------
#   コーデックモジュールのリンクを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\cdc.lnk:	\src\atlanta\make\cdc.SUB	\
			$(OBJECT)\cdc_mscr.obj		\
			$(OBJECT)\cdc_cdcr.obj		\
			$(OBJECT)\cdc_cmd.obj		\
			$(OBJECT)\cdc_cntl.obj		\
			$(OBJECT)\cdc_dmcr.obj		\
			$(OBJECT)\cdc_dtcr.obj		\
			$(OBJECT)\cdc_init.obj		\
			$(OBJECT)\cdc_main.obj		\
			$(OBJECT)\cdc_parm.obj		\
			$(OBJECT)\cdc_stir.obj		\
			$(OBJECT)\cdc_stup.obj		\
			$(OBJECT)\cdc_sub.obj		\
			$(OBJECT)\cdc_ctx.obj		\
			$(OBJECT)\cdc_modr.obj		\
			$(OBJECT)\cdc_hdmr.obj		\
#			$(OBJECT)\cdc_test.obj		\
			$(OBJECT)\cdc_tbl.obj		\
			$(OBJECT)\cdc_int.obj
		$(LNK)

#-----------------------------------------------------------------------------
#   コーデックモジュールのメイクファイル部
#-----------------------------------------------------------------------------
#
$(OBJECT)\cdc_mscr.obj:	$(SRC)\cdc_mscr.c	\
				\src\atlanta\define\cdc_pro.h		\
					\src\atlanta\define\product.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\ext_v\cdc_data.h		\
					\src\atlanta\define\cdc_blk.h		\
				\src\atlanta\ext_v\cdc_tbl.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\mon_pro.h
		$(CC) $(OPTION) $(SRC)\cdc_mscr.c
#
$(OBJECT)\cdc_cdcr.obj:	$(SRC)\cdc_cdcr.c	\
				\src\atlanta\define\cdc_pro.h		\
					\src\atlanta\define\product.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\ext_v\cdc_data.h		\
					\src\atlanta\define\cdc_blk.h		\
				\src\atlanta\ext_v\cdc_tbl.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h
		$(CC) $(OPTION) $(SRC)\cdc_cdcr.c
#
$(OBJECT)\cdc_cmd.obj:	$(SRC)\cdc_cmd.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\cdc_pro.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\ext_v\cdc_data.h		\
					\src\atlanta\define\cdc_blk.h		\
				\src\atlanta\ext_v\cdc_tbl.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\sh7043\define\def_evtn.h
		$(CC) $(OPTION) $(SRC)\cdc_cmd.c
#
$(OBJECT)\cdc_cntl.obj:	$(SRC)\cdc_cntl.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\cdc_pro.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\ext_v\cdc_data.h		\
					\src\atlanta\define\cdc_blk.h		\
				\src\atlanta\ext_v\cdc_tbl.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\sysprint.h
		$(CC) $(OPTION) $(SRC)\cdc_cntl.c
#
$(OBJECT)\cdc_dmcr.obj:	$(SRC)\cdc_dmcr.c	\
				\src\atlanta\define\cdc_pro.h		\
					\src\atlanta\define\product.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\ext_v\cdc_data.h		\
					\src\atlanta\define\cdc_blk.h		\
				\src\atlanta\ext_v\cdc_tbl.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h
		$(CC) $(OPTION) $(SRC)\cdc_dmcr.c
#
$(OBJECT)\cdc_dtcr.obj:	$(SRC)\cdc_dtcr.c	\
				\src\atlanta\define\cdc_pro.h		\
					\src\atlanta\define\product.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\ext_v\cdc_data.h		\
					\src\atlanta\define\cdc_blk.h		\
				\src\atlanta\ext_v\cdc_tbl.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h
		$(CC) $(OPTION) $(SRC)\cdc_dtcr.c
#
$(OBJECT)\cdc_init.obj:	$(SRC)\cdc_init.c	\
				\src\atlanta\define\cdc_pro.h		\
					\src\atlanta\define\product.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\define\cdc_blk.h		\
				\src\atlanta\ext_v\cdc_data.h		\
				\src\atlanta\ext_v\cdc_tbl.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h
		$(CC) $(OPTION) $(SRC)\cdc_init.c
#
$(OBJECT)\cdc_main.obj:	$(SRC)\cdc_main.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sysdblk.h		\
				\src\atlanta\define\mntsw_a.h		\
				\src\atlanta\define\mntsw_b.h		\
				\src\atlanta\define\mntsw_c.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\define\cdc_blk.h		\
				\src\atlanta\define\scn_def.h		\
				\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\lst_def.h		\
				\src\atlanta\define\dma_def.h		\
					\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\define\dma_blk.h		\
				\src\atlanta\define\mntsw_e.h		\
				\src\atlanta\sh7043\define\sh_SYS.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\SYSMAX.h		\
					\src\atlanta\define\sysbatch.h		\
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
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\ext_v\cdc_data.h		\
				\src\atlanta\ext_v\cdc_tbl.h		\
				\src\atlanta\ext_v\scn_data.h		\
				\src\atlanta\ext_v\mem_data.h		\
				\src\atlanta\ext_v\fcm_data.H		\
				\src\atlanta\ext_v\lst_data.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\ext_v\dma_data.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cdc_pro.h		\
				\src\atlanta\define\scn_pro.h		\
				\src\atlanta\sh7043\define\io_pro.h
		$(CC) $(OPTION) $(SRC)\cdc_main.c
#
$(OBJECT)\cdc_parm.obj:	$(SRC)\cdc_parm.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\cdc_pro.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\define\cdc_blk.h		\
				\src\atlanta\ext_v\cdc_data.h		\
				\src\atlanta\ext_v\cdc_tbl.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h
		$(CC) $(OPTION) $(SRC)\cdc_parm.c
#
$(OBJECT)\cdc_stir.obj:	$(SRC)\cdc_stir.c	\
				\src\atlanta\define\cdc_pro.h		\
					\src\atlanta\define\product.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\ext_v\cdc_data.h		\
					\src\atlanta\define\cdc_blk.h
		$(CC) $(OPTION) $(SRC)\cdc_stir.c
#
$(OBJECT)\cdc_stup.obj:	$(SRC)\cdc_stup.c	\
				\src\atlanta\define\cdc_pro.h		\
					\src\atlanta\define\product.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\define\cdc_blk.h		\
				\src\atlanta\ext_v\cdc_data.h		\
				\src\atlanta\ext_v\cdc_tbl.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\sysscan.h
		$(CC) $(OPTION) $(SRC)\cdc_stup.c
#
$(OBJECT)\cdc_sub.obj:	$(SRC)\cdc_sub.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\cdc_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mntsw_c.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
				\src\atlanta\ext_v\scn_data.h		\
					\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\ext_v\scn_tbl.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysonet.h		\
					\src\atlanta\define\sysexec.h		\
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
				\src\atlanta\ext_v\sys_port.h		\
				\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\ext_v\cdc_data.h		\
					\src\atlanta\define\cdc_blk.h
		$(CC) $(OPTION) $(SRC)\cdc_sub.c
#
$(OBJECT)\cdc_ctx.obj:	$(SRC)\cdc_ctx.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\dma_def.h		\
					\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\define\dma_blk.h		\
				\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\cdc_pro.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\define\cdc_blk.h		\
				\src\atlanta\define\mem_pro.h		\
					\src\atlanta\ext_v\memertbl.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\lst_def.h		\
				\src\atlanta\define\lst_pro.h		\
					\src\atlanta\define\message.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\dma_data.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\ext_v\cdc_data.h		\
				\src\atlanta\ext_v\cdc_tbl.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
				\src\atlanta\define\apl_msg.h
		$(CC) $(OPTION) $(SRC)\cdc_ctx.c
#
$(OBJECT)\cdc_tbl.obj:	$(DEFV)\cdc_tbl.c	\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(DEFV)\cdc_tbl.c

$(OBJECT)\cdc_modr.obj:	$(SRC)\cdc_modr.c	\
				\src\atlanta\define\cdc_pro.h		\
					\src\atlanta\define\product.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\ext_v\cdc_data.h		\
					\src\atlanta\define\cdc_blk.h		\
				\src\atlanta\ext_v\cdc_tbl.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h
		$(CC) $(OPTION) $(SRC)\cdc_modr.c
#
$(OBJECT)\cdc_hdmr.obj:	$(SRC)\cdc_hdmr.c	\
				\src\atlanta\define\cdc_pro.h		\
					\src\atlanta\define\product.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\ext_v\cdc_data.h		\
					\src\atlanta\define\cdc_blk.h		\
				\src\atlanta\ext_v\cdc_tbl.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h
		$(CC) $(OPTION) $(SRC)\cdc_hdmr.c
#
$(OBJECT)\cdc_test.obj:	$(SRC)\cdc_test.c
		$(CC) $(OPTION) $(SRC)\cdc_test.c
#
$(OBJECT)\cdc_int.obj:	$(SRC)\cdc_int.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\ext_v\cdc_data.h		\
					\src\atlanta\define\cdc_blk.h		\
				\src\atlanta\ext_v\scn_data.h		\
					\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\ext_v\scn_tbl.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\cdc_pro.h		\
				\src\atlanta\define\scn_pro.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\define\scn_io.h		\
				\src\atlanta\ext_v\cdc_tbl.h		\
				\src\atlanta\define\mntsw_g.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\SYSMAX.h		\
					\src\atlanta\define\sysbatch.h		\
						\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysonet.h		\
					\src\atlanta\define\sysexec.h		\
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
					\src\atlanta\define\dpr_def.h
		$(CC) $(OPTION) $(SRC)\cdc_int.c
#
