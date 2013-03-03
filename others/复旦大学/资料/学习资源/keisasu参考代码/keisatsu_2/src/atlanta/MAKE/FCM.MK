#------------------------------------------------------------------------
#	POPLAR/ANZU_L	通信部(FCM)のメイクファイル
#	Nov.19.1996	 By T.Yamaguchi		Transplanted from \src\kobe\anzu\make
#------------------------------------------------------------------------

#---------------------------#
#	ディレクトリマクロ		#
#---------------------------#
DEFINE		= \src\atlanta\define
DEFINESH	= \src\atlanta\sh7043\define
DEFV		= \src\atlanta\def_v
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
#	ｺﾏﾝﾄﾞ名を定義
#-----------------------------------------------------------------------------
CC			= shc
ASM			= asmsh
LNK			= lnk /subcommand=\src\atlanta\make\FCM.sub
#-----------------------------------------------------------------------------
#	引数を定義
#-----------------------------------------------------------------------------
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_NO	= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI2") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU")) || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
#最適化します 1999/01/24
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_NO	= /op=1 /size   /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

!if ("$(MODEL)" == "POPLAR_H")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_NO	= /op=1 /size   /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

#/* By M.Tachibana 1998/04/28 */
#!if ("$(MODEL)" == "POPLAR_B")
!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLR_BN")
!if ("$(COUNTRY)" == "JPN") || ("$(COUNTRY)" == "JP1")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_NO	= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
!endif

#ROMが溢れているので最適化します 1998/05/06  By T.Yamaguchi
!if ("$(MODEL)" == "POPLAR_N")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_NO	= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif


#デバッグ用にANZU_Vでｵﾌﾟﾃｨﾏｲｽﾞをかけます。by Y.Tanimoto 1998/03/13
!if ("$(MODEL)" == "ANZU_V")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_NO	= /op=1 /size   /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

!if ("$(MODEL)" == "SAKAKI")
OPTION		= /op=1 /size  /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_NO	= /op=1 /size  /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

#OPTION		= /op=0 /deb /def=($(MODEL),$(COUNTRY),$(CPU)) /cp=$(CPU_OPT)
ASM_OPT		= /cpu=$(CPU_OPT) /debug /object=$*.obj
#-----------------------------------------------------------------------------
#	オブジェクトディレクトリを定義
#-----------------------------------------------------------------------------
MACHINE_DEF = sh
CMD_SUFX	= sub
OBJECT		= \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-------------------------------------------#
#	通信モジュールのリンク,Ｖ５３(ANZU)用	#
#-------------------------------------------#
$(OBJECT)\fcm.lnk :	\src\atlanta\make\fcm.$(CMD_SUFX)	\
			$(OBJECT)\fcm_main.obj	\
			$(OBJECT)\fcm_init.obj	\
			$(OBJECT)\fcm_getd.obj	\
			$(OBJECT)\fcm_fcom.obj	\
			$(OBJECT)\fcm_spd.obj	\
			$(OBJECT)\fcm_diag.obj	\
			$(OBJECT)\fcm_jrnl.obj	\
			$(OBJECT)\fcm_rely.obj	\
			$(OBJECT)\fcm_last.obj	\
			$(OBJECT)\fcm_txb.obj	\
			$(OBJECT)\fcm_txb1.obj	\
			$(OBJECT)\fcm_rxb.obj	\
			$(OBJECT)\fcm_rxb1.obj	\
			$(OBJECT)\fcm_polb.obj	\
			$(OBJECT)\fcm_fsub.obj	\
			$(OBJECT)\fcm_ph_e.obj	\
			$(OBJECT)\fcmtxc.obj	\
			$(OBJECT)\fcmtxd.obj	\
			$(OBJECT)\fcmtxds.obj	\
			$(OBJECT)\fcmrxc.obj	\
			$(OBJECT)\fcmrxcs.obj	\
			$(OBJECT)\fcmrxd.obj	\
			$(OBJECT)\fcm_fxtl.obj	\
			$(OBJECT)\fcmfxtl2.obj	\
			$(OBJECT)\fcmhookt.obj	\
			$(OBJECT)\fcm_cost.obj	\
			$(OBJECT)\fcm_fcd.obj	\
			$(OBJECT)\fcm_chk.obj	\
			$(OBJECT)\fcm_ptnr.obj	\
			$(OBJECT)\fcm_srtx.obj	\
			$(OBJECT)\fcm_srrx.obj
	$(LNK)

#---------------------------------------#
#	通信モジュールのメイクファイル部	#
#---------------------------------------#
$(OBJECT)\FCM_MAIN.obj :	$(SRC)\FCM_MAIN.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\scn_data.h		\
					\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\ext_v\bkupram.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h
	$(CC) $(OPTION_NO) $(SRC)\FCM_MAIN.c

$(OBJECT)\FCM_INIT.obj :	$(SRC)\FCM_INIT.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\fcm_pro.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\memsw\define\mem_sw_c.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\uni_pro.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysmailb.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\fcm_data.h
	$(CC) $(OPTION) $(SRC)\FCM_INIT.c

$(OBJECT)\FCM_GETD.obj :	$(SRC)\FCM_GETD.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\SYSMAX.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysjrnl.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\std.h
	$(CC) $(OPTION) $(SRC)\FCM_GETD.c

$(OBJECT)\FCM_FCOM.obj :	$(SRC)\FCM_FCOM.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\atd_def.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h
	$(CC) $(OPTION) $(SRC)\FCM_FCOM.c

$(OBJECT)\FCM_SPD.obj :	$(SRC)\FCM_SPD.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\unisw_b.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\rom_tbl.h		\
				\src\atlanta\ext_v\atd_tbl.h		\
					\src\atlanta\define\atd_def.h
	$(CC) $(OPTION) $(SRC)\FCM_SPD.c

$(OBJECT)\FCM_DIAG.obj :	$(SRC)\FCM_DIAG.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\std.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\SYSMAX.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysjrnl.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h		\
				\src\atlanta\ext_v\rom_tbl.h
	$(CC) $(OPTION) $(SRC)\FCM_DIAG.c

$(OBJECT)\FCM_JRNL.obj :	$(SRC)\FCM_JRNL.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\fcm_pro.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\rom_tbl.h		\
					\src\atlanta\define\message.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysmailb.h		\
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
					\src\atlanta\define\sysdeprt.h		\
					\src\atlanta\define\systbok.h		\
					\src\atlanta\define\sysopspd.h		\
					\src\atlanta\define\sysringm.h		\
						\src\atlanta\define\ncu_cnst.h		\
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\lst_def.h		\
						\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\uni_pro.h
	$(CC) $(OPTION) $(SRC)\FCM_JRNL.c

$(OBJECT)\FCM_RELY.obj :	$(SRC)\FCM_RELY.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\ncu_pro.h		\
					\src\atlanta\define\ncu_def.h		\
						\src\atlanta\define\ncu_cnst.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysmailb.h		\
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
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h
	$(CC) $(OPTION) $(SRC)\FCM_RELY.c

$(OBJECT)\FCM_LAST.obj :	$(SRC)\FCM_LAST.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\opr\ank\define\opr_pro.h		\
					\src\atlanta\define\sysspeed.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\mem_def.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\sys_remo.h		\
				\src\atlanta\define\std.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\SYSMAX.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\sysonet.h		\
					\src\atlanta\define\sysexec.h		\
					\src\atlanta\define\sysmcopy.h		\
					\src\atlanta\define\syslifem.h		\
					\src\atlanta\define\sysshad.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h		\
				\src\atlanta\ext_v\atd_tbl.h		\
				\src\atlanta\define\sys_opt.h
	$(CC) $(OPTION) $(SRC)\FCM_LAST.c

$(OBJECT)\FCM_TXB.obj :	$(SRC)\FCM_TXB.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\scn_def.h		\
				\src\atlanta\define\scn_pro.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\ext_v\bkupram.h		\
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
					\src\atlanta\define\sysdeprt.h		\
					\src\atlanta\define\systbok.h		\
					\src\atlanta\define\sysopspd.h		\
					\src\atlanta\define\sysringm.h		\
						\src\atlanta\define\ncu_cnst.h		\
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mntsw_b.h
	$(CC) $(OPTION) $(SRC)\FCM_TXB.c

$(OBJECT)\FCM_TXB1.obj :	$(SRC)\FCM_TXB1.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\std.h		\
					\src\atlanta\define\dma_def.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysmailb.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\define\mntsw_b.h
	$(CC) $(OPTION) $(SRC)\FCM_TXB1.c

$(OBJECT)\FCM_RXB.obj :	$(SRC)\FCM_RXB.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\mem_def.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\memsw\define\mem_sw_c.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\std.h
	$(CC) $(OPTION) $(SRC)\FCM_RXB.c

$(OBJECT)\FCM_RXB1.obj :	$(SRC)\FCM_RXB1.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\ncu_pro.h		\
					\src\atlanta\define\ncu_def.h		\
						\src\atlanta\define\ncu_cnst.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysmailb.h		\
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
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h
	$(CC) $(OPTION) $(SRC)\FCM_RXB1.c

$(OBJECT)\FCM_POLB.obj :	$(SRC)\FCM_POLB.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\SYSMAX.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysjrnl.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\fcm_data.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\define\uni_pro.h
	$(CC) $(OPTION) $(SRC)\FCM_POLB.c

$(OBJECT)\FCM_FSUB.obj :	$(SRC)\FCM_FSUB.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\sysscan.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h
	$(CC) $(OPTION) $(SRC)\FCM_FSUB.c

$(OBJECT)\FCMTXC.obj	:	$(SRC)\FCMTXC.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\sysonet.h		\
					\src\atlanta\define\sysmcopy.h		\
					\src\atlanta\define\syslifem.h		\
					\src\atlanta\define\sysshad.h		\
					\src\atlanta\define\sysspeed.h		\
					\src\atlanta\define\sysdiali.h		\
					\src\atlanta\define\sysmemrx.h		\
					\src\atlanta\define\syscost.h		\
					\src\atlanta\define\sysdeprt.h		\
					\src\atlanta\define\systbok.h		\
					\src\atlanta\define\sysopspd.h		\
					\src\atlanta\define\sysringm.h		\
						\src\atlanta\define\ncu_cnst.h		\
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\scn_pro.h		\
				\src\atlanta\define\sysexec.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h		\
				\src\atlanta\define\mntsw_b.h		\
				\src\atlanta\define\std.h
	$(CC) $(OPTION) $(SRC)\FCMTXC.c

$(OBJECT)\FCMTXD.obj	:	$(SRC)\FCMTXD.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\syst30.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\man_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysbatch.h
	$(CC) $(OPTION) $(SRC)\FCMTXD.c

$(OBJECT)\FCMTXDS.obj	:	$(SRC)\FCMTXDS.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\syslocal.h		\
				\src\atlanta\define\syst30.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\sysonet.h		\
					\src\atlanta\define\sysexec.h		\
					\src\atlanta\define\sysmcopy.h		\
					\src\atlanta\define\syslifem.h		\
					\src\atlanta\define\sysshad.h		\
					\src\atlanta\define\sysspeed.h		\
					\src\atlanta\define\sysdiali.h		\
					\src\atlanta\define\sysmemrx.h		\
					\src\atlanta\define\syscost.h		\
					\src\atlanta\define\sysdeprt.h		\
					\src\atlanta\define\systbok.h		\
					\src\atlanta\define\sysopspd.h		\
					\src\atlanta\define\sysringm.h		\
						\src\atlanta\define\ncu_cnst.h		\
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\message.h
	$(CC) $(OPTION) $(SRC)\FCMTXDS.c

$(OBJECT)\FCMRXC.obj	:	$(SRC)\FCMRXC.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\ext_v\bkupram.h		\
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
					\src\atlanta\define\sysdeprt.h		\
					\src\atlanta\define\systbok.h		\
					\src\atlanta\define\sysopspd.h		\
					\src\atlanta\define\sysringm.h		\
						\src\atlanta\define\ncu_cnst.h		\
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\message.h
	$(CC) $(OPTION) $(SRC)\FCMRXC.c

$(OBJECT)\FCMRXCS.obj	:	$(SRC)\FCMRXCS.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\fcm_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\opr\ank\define\opr_pro.h		\
					\src\atlanta\define\sysspeed.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysonet.h		\
					\src\atlanta\define\sysexec.h		\
					\src\atlanta\define\sysmcopy.h		\
					\src\atlanta\define\syslifem.h		\
					\src\atlanta\define\sysshad.h		\
					\src\atlanta\define\sysdiali.h		\
					\src\atlanta\define\sysmemrx.h		\
					\src\atlanta\define\syscost.h		\
					\src\atlanta\define\sysdeprt.h		\
					\src\atlanta\define\systbok.h		\
					\src\atlanta\define\sysopspd.h		\
					\src\atlanta\define\sysringm.h		\
						\src\atlanta\define\ncu_cnst.h		\
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
					\src\atlanta\define\message.h		\
				\src\atlanta\ext_v\fcm_data.h
	$(CC) $(OPTION) $(SRC)\FCMRXCS.c

$(OBJECT)\FCMRXD.obj	:	$(SRC)\FCMRXD.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\ext_v\atd_tbl.h		\
				\src\atlanta\ext_v\atd_data.h		\
				\src\atlanta\define\uni_pro.h
	$(CC) $(OPTION) $(SRC)\FCMRXD.c

$(OBJECT)\FCM_PH_E.obj :	$(SRC)\FCM_PH_E.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysbatch.h		\
						\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h
	$(CC) $(OPTION) $(SRC)\FCM_PH_E.c

$(OBJECT)\FCM_FXTL.obj :	$(SRC)\FCM_FXTL.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\ncu_def.h		\
				\src\atlanta\define\ncu_msg.h		\
				\src\memsw\define\mem_sw_c.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysmailb.h		\
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
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h
	$(CC) $(OPTION) $(SRC)\FCM_FXTL.c

$(OBJECT)\FCMHOOKT.obj :	$(SRC)\FCMHOOKT.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\ncu_stat.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysbatch.h		\
						\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\ncu_data.h		\
					\src\atlanta\define\ncu_def.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\sh7043\define\io_pro.h
	$(CC) $(OPTION) $(SRC)\FCMHOOKT.c

$(OBJECT)\FCM_COST.obj :	$(SRC)\FCM_COST.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\syscost.h		\
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
					\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysdeprt.h		\
					\src\atlanta\define\systbok.h		\
					\src\atlanta\define\sysopspd.h		\
					\src\atlanta\define\sysringm.h		\
						\src\atlanta\define\ncu_cnst.h		\
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\mem_def.h
	$(CC) $(OPTION) $(SRC)\FCM_COST.c

$(OBJECT)\FCM_fcd.obj :	$(SRC)\FCM_fcd.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\sysspeed.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\syst30.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\param.h		\
				\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysonet.h		\
					\src\atlanta\define\sysexec.h		\
					\src\atlanta\define\sysmcopy.h		\
					\src\atlanta\define\syslifem.h		\
					\src\atlanta\define\sysshad.h		\
					\src\atlanta\define\sysdiali.h		\
					\src\atlanta\define\sysmemrx.h		\
					\src\atlanta\define\syscost.h		\
					\src\atlanta\define\sysdeprt.h		\
					\src\atlanta\define\systbok.h		\
					\src\atlanta\define\sysopspd.h		\
					\src\atlanta\define\sysringm.h		\
						\src\atlanta\define\ncu_cnst.h		\
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
				\src\atlanta\ext_v\atd_data.h
	$(CC) $(OPTION) $(SRC)\FCM_FCD.c

$(OBJECT)\FCM_CHK.obj :$(SRC)\FCM_CHK.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\scn_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\fcm_pro.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mlt_pro.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysdoc.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\scn_def.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\lst_def.h		\
				\src\atlanta\define\pro_def.h		\
				\src\atlanta\define\param.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysmailb.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\scn_data.h		\
				\src\atlanta\ext_v\mlt_data.h		\
					\src\atlanta\define\sys_opt.h
	$(CC) $(OPTION) $(SRC)\FCM_CHK.c

$(OBJECT)\FCM_PTNR.obj :$(SRC)\FCM_PTNR.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sysspeed.h		\
				\src\atlanta\define\sysonet.h		\
					\src\atlanta\define\syscomf.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysexec.h		\
					\src\atlanta\define\sysmcopy.h		\
					\src\atlanta\define\syslifem.h		\
					\src\atlanta\define\sysshad.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\mem_def.h
	$(CC) $(OPTION) $(SRC)\FCM_PTNR.c
#
#
$(OBJECT)\FCMFXTL2.obj :	$(SRC)\FCMFXTL2.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\ncu_def.h		\
				\src\atlanta\define\ncu_msg.h		\
				\src\memsw\define\mem_sw_c.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysmailb.h		\
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
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h
	$(CC) $(OPTION) $(SRC)\FCMFXTL2.c
#
$(OBJECT)\fcm_srtx.obj :	$(SRC)\fcm_srtx.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\ncu_def.h		\
				\src\atlanta\define\ncu_msg.h		\
				\src\memsw\define\mem_sw_c.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysmailb.h		\
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
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h
	$(CC) $(OPTION) $(SRC)\fcm_srtx.c
#
$(OBJECT)\fcm_srrx.obj :	$(SRC)\fcm_srrx.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\ncu_def.h		\
				\src\atlanta\define\ncu_msg.h		\
				\src\memsw\define\mem_sw_c.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysmailb.h		\
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
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h
	$(CC) $(OPTION) $(SRC)\fcm_srrx.c
#
