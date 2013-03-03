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
LNK			= lnk /subcommand=\src\atlanta\make\FCM_COMP.sub
#-----------------------------------------------------------------------------
#	引数を定義
#-----------------------------------------------------------------------------
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))

#!if ("$(MODEL)" == "POPLAR_B")
!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLR_BN")
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!if ("$(COUNTRY)" == "USA")
OPTION	= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
#/* By M.Tachibana 1998/04/28 */
!if ("$(COUNTRY)" == "JPN") || ("$(COUNTRY)" == "JP1")
OPTION	= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
!endif

#!if ("$(MODEL)" == "POPLAR_H")
!if ("$(MODEL)" == "POPLAR_H") || ("$(MODEL)" == "POPLAR_N") || ("$(MODEL)" == "SAKAKI") || ("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI2") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU") || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
#ヒノキ最適化します 1999/01/24
OPTION	= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

#デバッグ用にANZU_Vでｵﾌﾟﾃｨﾏｲｽﾞをかけます。by Y.Tanimoto 1998/03/13
!if ("$(MODEL)" == "ANZU_V")
OPTION	= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
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
$(OBJECT)\fcm_comp.lnk :	\src\atlanta\make\fcm_comp.$(CMD_SUFX) \
			$(OBJECT)\fcm_tcmp.obj	\
			$(OBJECT)\fcm_rcmp.obj	\
			$(OBJECT)\fcm_pcmp.obj	\
			$(OBJECT)\fcm_tcks.obj	\
			$(OBJECT)\fcm_rcks.obj	\
			$(OBJECT)\fcmfif1.obj	\
			$(OBJECT)\fcmfif2.obj	\
			$(OBJECT)\fcmidchk.obj	\
			$(OBJECT)\fcmfrms.obj	\
			$(OBJECT)\fcmmkctc.obj	\
			$(OBJECT)\fcmdis.obj	\
			$(OBJECT)\fcmdcs.obj	\
			$(OBJECT)\fcmdtc.obj	\
			$(OBJECT)\fcmnsf.obj	\
			$(OBJECT)\fcmnss.obj	\
			$(OBJECT)\fcmnsc.obj
	$(LNK)

#---------------------------------------------------------------#
#	コンパチチェック、フレーム作成モジュールのメイクファイル部	#
#---------------------------------------------------------------#
$(OBJECT)\FCM_TCMP.obj :	$(SRC)\FCM_TCMP.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\define\SYSDOC.H		\
				\src\atlanta\define\STD.H		\
				\src\atlanta\define\FCM_DEF.H		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\BKUPRAM.H		\
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
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\FCM_PRO.H		\
				\src\atlanta\define\CTRY_PRO.H		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\ncu_def.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\STNG_PRO.H		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\define\SCN_PRO.H
	$(CC) $(OPTION) $(SRC)\FCM_TCMP.c

$(OBJECT)\FCM_RCMP.obj :	$(SRC)\FCM_RCMP.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\FCM_DEF.H		\
				\src\atlanta\define\STD.H		\
				\src\atlanta\define\SYSDOC.H		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\mem_def.H		\
				\src\atlanta\ext_v\BKUPRAM.H		\
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
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\message.h		\
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\FCM_PRO.H		\
				\src\atlanta\define\MEM_PRO.H		\
				\src\atlanta\define\APL_MSG.H		\
				\src\atlanta\define\MON_PRO.H		\
				\src\atlanta\define\CTRY_PRO.H		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\ncu_def.h		\
				\src\atlanta\define\STNG_PRO.H		\
				\src\atlanta\define\CMN_PRO.H		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\define\SYS_STAT.H		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\ext_v\ROM_TBL.H
	$(CC) $(OPTION) $(SRC)\FCM_RCMP.c

$(OBJECT)\FCM_PCMP.obj :	$(SRC)\FCM_PCMP.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\define\FCM_DEF.H		\
				\src\atlanta\define\STD.H		\
				\src\atlanta\define\mem_def.H		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\BKUPRAM.H		\
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
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\message.h		\
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\FCM_PRO.H		\
				\src\atlanta\define\CTRY_PRO.H		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\ncu_def.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\MEM_PRO.H		\
				\src\atlanta\define\uni_pro.h
	$(CC) $(OPTION) $(SRC)\FCM_PCMP.c

$(OBJECT)\FCM_TCKS.obj :	$(SRC)\FCM_TCKS.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\define\FCM_DEF.H		\
				\src\atlanta\define\SYSDOC.H		\
				\src\atlanta\define\STD.H		\
				\src\atlanta\define\mem_def.H		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\SYSBATCH.H		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\ext_v\BKUPRAM.H		\
					\src\atlanta\define\SYSMAX.h		\
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
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\message.h		\
				\src\atlanta\define\FCM_PRO.H		\
				\src\atlanta\define\CMN_PRO.H		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\MEM_PRO.H		\
				\src\atlanta\define\STNG_PRO.H		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\UNI_PRO.H
	$(CC) $(OPTION) $(SRC)\FCM_TCKS.c

$(OBJECT)\FCM_RCKS.obj :	$(SRC)\FCM_RCKS.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\define\FCM_DEF.H		\
				\src\atlanta\define\SYSDOC.H		\
				\src\atlanta\define\STD.H		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\BKUPRAM.H		\
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
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\FCM_PRO.H		\
				\src\atlanta\define\UNI_PRO.H
	$(CC) $(OPTION) $(SRC)\FCM_RCKS.c

$(OBJECT)\FCMFIF1.obj :	$(SRC)\FCMFIF1.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\define\SYSDOC.H		\
				\src\atlanta\define\FCM_DEF.H		\
				\src\atlanta\define\STD.H		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\mem_def.H		\
				\src\atlanta\define\SYS_STAT.H		\
				\src\atlanta\ext_v\BKUPRAM.H		\
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
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\message.h		\
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\MEM_DATA.H		\
				\src\atlanta\define\FCM_PRO.H		\
				\src\atlanta\define\MEM_PRO.H
	$(CC) $(OPTION) $(SRC)\FCMFIF1.c

$(OBJECT)\FCMFIF2.obj :	$(SRC)\FCMFIF2.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\define\SYSMAILB.H		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\SYSDIAL.H		\
				\src\atlanta\define\FCM_DEF.H		\
				\src\atlanta\define\mem_def.H		\
				\src\atlanta\define\STD.H		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\BKUPRAM.H		\
					\src\atlanta\define\sysbatch.h		\
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
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\message.h		\
				\src\atlanta\define\FCM_PRO.H		\
				\src\atlanta\define\STNG_PRO.H		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\MEM_PRO.H		\
				\src\atlanta\define\CMN_PRO.H		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\UNI_PRO.H		\
				\src\atlanta\opr\ank\define\OPR_PRO.H		\
				\src\atlanta\define\sysnd.h		\
				\src\atlanta\ext_v\ROM_TBL.h
	$(CC) $(OPTION) $(SRC)\FCMFIF2.c

$(OBJECT)\FCMIDCHK.obj:	$(SRC)\FCMIDCHK.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\define\SYSMAX.H		\
				\src\atlanta\define\SYSONET.H		\
					\src\atlanta\define\syscomf.h		\
				\src\atlanta\define\SYSSPEED.H		\
				\src\atlanta\define\FCM_PRO.H		\
					\src\atlanta\define\time.h		\
				\src\atlanta\ext_v\BKUPRAM.H		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysjrnl.h		\
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
				\src\atlanta\define\STD.H		\
				\src\atlanta\define\FCM_DEF.H		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\ROM_TBL.H
	$(CC) $(OPTION) $(SRC)\FCMIDCHK.c

$(OBJECT)\FCMFRMS.obj :	$(SRC)\FCMFRMS.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\define\FCM_DEF.H		\
				\src\atlanta\define\STD.H		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\FCM_PRO.H
	$(CC) $(OPTION) $(SRC)\FCMFRMS.c

$(OBJECT)\FCMMKCTC.obj :	$(SRC)\FCMMKCTC.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\define\SYSMAX.H		\
				\src\atlanta\define\STD.H		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\FCM_DEF.H		\
				\src\atlanta\define\SYSDOC.H		\
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\FCM_PRO.H
	$(CC) $(OPTION) $(SRC)\FCMMKCTC.c

$(OBJECT)\FCMDIS.obj :	$(SRC)\FCMDIS.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\define\STD.H		\
				\src\atlanta\define\FCM_DEF.H		\
				\src\atlanta\define\SYSDOC.H		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\BKUPRAM.H		\
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
				\src\atlanta\define\FCM_PRO.H		\
				\src\atlanta\define\STNG_PRO.H		\
				\src\atlanta\define\CMN_PRO.H		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\sys_opt.h
		$(CC) $(OPTION) $(SRC)\FCMDIS.c

$(OBJECT)\FCMNSF.obj :	$(SRC)\FCMNSF.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\define\STD.H		\
				\src\atlanta\define\FCM_DEF.H		\
				\src\atlanta\define\SYSDOC.H		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\BKUPRAM.H		\
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
				\src\atlanta\ext_v\ROM_TBL.H		\
				\src\atlanta\define\FCM_PRO.H		\
				\src\atlanta\define\MEM_PRO.H		\
				\src\atlanta\define\CTRY_PRO.H		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\ncu_def.h		\
				\src\atlanta\define\CMN_PRO.H		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\define\STNG_PRO.H		\
				\src\atlanta\define\SYSMAX.H		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\UNI_PRO.H
		$(CC) $(OPTION) $(SRC)\FCMNSF.c

$(OBJECT)\FCMDCS.obj :	$(SRC)\FCMDCS.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\define\FCM_DEF.H		\
				\src\atlanta\define\SYSDOC.H		\
				\src\atlanta\define\STD.H		\
				\src\atlanta\define\SYSCOMF.H		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\FCM_PRO.H
		$(CC) $(OPTION) $(SRC)\FCMDCS.c

$(OBJECT)\FCMNSS.obj :	$(SRC)\FCMNSS.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\define\FCM_DEF.H		\
				\src\atlanta\define\SYSDOC.H		\
				\src\atlanta\define\STD.H		\
				\src\atlanta\define\SYSCOMF.H		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\FCM_PRO.H		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\ext_v\BKUPRAM.H		\
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
				\src\atlanta\define\UNI_PRO.H
		$(CC) $(OPTION) $(SRC)\FCMNSS.c

$(OBJECT)\FCMDTC.obj :	$(SRC)\FCMDTC.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\define\FCM_DEF.H		\
				\src\atlanta\define\SYSDOC.H		\
				\src\atlanta\define\SYSCOMF.H		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\STD.H		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\bkupram.H		\
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
				\src\atlanta\define\FCM_PRO.H		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\CMN_PRO.H		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h
		$(CC) $(OPTION) $(SRC)\FCMDTC.c

$(OBJECT)\FCMNSC.obj :	$(SRC)\FCMNSC.c		\
				\src\atlanta\define\PRODUCT.H		\
				\src\atlanta\define\FCM_DEF.H		\
				\src\atlanta\define\SYSDOC.H		\
				\src\atlanta\define\SYSCOMF.H		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\STD.H		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\FCM_DATA.H		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\SYS_DATA.H		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\FCM_PRO.H		\
				\src\atlanta\define\CMN_PRO.H		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\STNG_PRO.H		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\UNI_PRO.H		\
				\src\atlanta\ext_v\BKUPRAM.H		\
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
					\src\atlanta\define\sysfcode.h
		$(CC) $(OPTION) $(SRC)\FCMNSC.c
