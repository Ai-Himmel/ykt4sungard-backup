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
LNK			= lnk /subcommand=\src\atlanta\make\FCM_V34.sub
#-----------------------------------------------------------------------------
#	引数を定義
#-----------------------------------------------------------------------------
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))

!if ("$(MODEL)" == "POPLAR_H")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

!if ("$(MODEL)" == "SAKAKI")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU") || ("$(MODEL)" == "HINOKI2")) || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
#最適化します 1999/01/24
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
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
$(OBJECT)\fcm_v34.lnk :	\src\atlanta\make\fcm_v34.$(CMD_SUFX)	\
			$(OBJECT)\fcm_comd.obj	\
			$(OBJECT)\fcm_v34.obj	\
			$(OBJECT)\fcm_v8.obj	\
			$(OBJECT)\fcm_v8sb.obj	\
			$(OBJECT)\fcm_stup.obj
			
	$(LNK)

#---------------------------------------#
#	通信モジュールのメイクファイル部	#
#---------------------------------------#
$(OBJECT)\fcm_comd.obj	:	$(SRC)\fcm_comd.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\sysscan.h		\
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
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h
	$(CC) $(OPTION) $(SRC)\fcm_comd.c

$(OBJECT)\fcm_v34.obj	:	$(SRC)\fcm_v34.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysonet.h		\
					\src\atlanta\define\sysexec.h		\
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
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h
	$(CC) $(OPTION) $(SRC)\fcm_v34.c

$(OBJECT)\fcm_v8.obj	:	$(SRC)\fcm_v8.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
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
					\src\atlanta\define\sysdeprt.h		\
					\src\atlanta\define\systbok.h		\
					\src\atlanta\define\sysopspd.h		\
					\src\atlanta\define\sysringm.h		\
						\src\atlanta\define\ncu_cnst.h		\
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\unisw_d.h
	$(CC) $(OPTION) $(SRC)\fcm_v8.c

$(OBJECT)\fcm_v8sb.obj	:	$(SRC)\fcm_v8sb.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysonet.h		\
					\src\atlanta\define\sysexec.h		\
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
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h		\
				\src\atlanta\ext_v\atd_data.h
	$(CC) $(OPTION) $(SRC)\fcm_v8sb.c

$(OBJECT)\fcm_stup.obj	:	$(SRC)\fcm_stup.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
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
					\src\atlanta\define\sysdeprt.h		\
					\src\atlanta\define\systbok.h		\
					\src\atlanta\define\sysopspd.h		\
					\src\atlanta\define\sysringm.h		\
						\src\atlanta\define\ncu_cnst.h		\
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h
	$(CC) $(OPTION) $(SRC)\fcm_stup.c
