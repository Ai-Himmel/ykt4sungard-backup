# =============================================================================
# =	 ﾏｸﾛ定義																  #
# =============================================================================
##By S.K Dec.12,1995 CC = cl
##By S.K Dec.12,1995 LNK = xlink86E
#
DEFINE	= \src\atlanta\define
DEFV	= \src\atlanta\def_v
EXTV	= \src\atlanta\ext_v
SRC		= \src\atlanta\src
WORD	= \src\atlanta\wording
MON		= \src\atlanta\mon
MAKE	= \src\atlanta\make
MSWDEFINE	= \src\memsw\define
#
#V53_PROTO_TYPE =	$(DEFINE)\protype.h
MEMORY_SWITCH =	$(MSWDEFINE)\mem_sw_a.h		$(MSWDEFINE)\mem_sw_b.h		\
				$(MSWDEFINE)\mem_sw_c.h		$(MSWDEFINE)\mem_sw_d.h		\
				$(MSWDEFINE)\mem_sw_e.h		$(MSWDEFINE)\mem_sw_f.h		\
				$(MSWDEFINE)\mem_sw_g.h		$(MSWDEFINE)\mem_sw_h.h		\
				$(MSWDEFINE)\mem_sw_i.h		$(MSWDEFINE)\mem_sw_j.h
#
#-----------------------------------------------------------------------------
#	ｺﾏﾝﾄﾞ名を定義
#-----------------------------------------------------------------------------
CC			= shc
ASM			= asmsh

#!if ("$(MODEL)" == "ANZU_L") || ("$(MODEL)" == "ANZU_V") || ("$(MODEL)" == "POPLAR_L")
!if ("$(MODEL)" == "ANZU_L") || ("$(MODEL)" == "POPLAR_L") || ("$(MODEL)" == "POPLAR_N")
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
#!if ("$(MODEL)" == "POPLAR_B") 1999/05/13 by T.Soneoka
!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLR_BN")
!if ("$(COUNTRY)" == "JPN") || ("$(COUNTRY)" == "FRA") || ("$(COUNTRY)" == "JP1")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!else
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
!endif
!if ("$(MODEL)" == "POPLAR_H")
!if ("$(COUNTRY)" == "GBR")
OPTION		= /op=1 /size /cp=sh2 /def=($(MODEL),$(COUNTRY))
!else
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
!endif
#デバッグ用にANZU_Vでｵﾌﾟﾃｨﾏｲｽﾞをかけます。by Y.Tanimoto 1998/03/13
!if ("$(MODEL)" == "ANZU_V")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

!if ("$(MODEL)" == "SAKAKI")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI2") || ("$(MODEL)" == "HINOKI3")) || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
#最適化します 1999/01/24
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

!if ("$(MODEL)" == "KEISATSU")
#最適化します 2005/11/17
OPTION		= /op=1 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

ASM_OPT		= /cpu=$(CPU_OPT) /debug /object=$*.obj
MACHINE_DEF = sh
CMD_SUFX	= sub
LNK			= lnk /subcommand=\src\atlanta\make\ATD.sub
OBJECT		= \src\atlanta\$(MODEL)\work\$(COUNTRY)


# =============================================================================
# =	 ﾓｼﾞｭｰﾙ ﾒｲｸ																  #
# =============================================================================
$(OBJECT)\ATD.lnk :	\src\atlanta\make\ATD.$(CMD_SUFX)	\
				$(OBJECT)\ATD_OUTD.obj	$(OBJECT)\ATD_TN.obj													\
				$(OBJECT)\ATD_D2T.obj	$(OBJECT)\ATD_LC.obj	$(OBJECT)\ATD_AFTN.obj	$(OBJECT)\ATD_DSE.obj	\
				$(OBJECT)\ATD_MAIN.obj	$(OBJECT)\ATD_FREQ.obj	$(OBJECT)\ATD_DT.obj	$(OBJECT)\ATDFLTOF.obj	\
				$(OBJECT)\ATD_LCOF.obj	$(OBJECT)\ATDRELAY.obj													\
				$(OBJECT)\ATD_CNG.obj	$(OBJECT)\ATD_STOP.obj													\
				$(OBJECT)\ATDMCRYT.OBJ
#By S.K		$(LNK) @\src\atlanta\make\ATD.cmd
		$(LNK)


# =============================================================================
# =	 ｺﾝﾊﾟｲﾙ																	  #
# =============================================================================
$(OBJECT)\ATD_OUTD.obj :	\src\atlanta\SRC\ATD_OUTD.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\ctry_pro.h		\
					\src\atlanta\define\ncu_def.h		\
						\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\status.h		\
				\src\memsw\define\mem_sw_a.h		\
				\src\atlanta\ext_v\atd_data.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\sysscan.h
		$(CC) $(OPTION) \src\atlanta\SRC\ATD_OUTD.c

$(OBJECT)\ATD_TN.obj :	\src\atlanta\SRC\ATD_TN.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\ctry_pro.h		\
					\src\atlanta\define\ncu_def.h		\
						\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\ext_v\atd_tbl.h		\
				\src\atlanta\ext_v\atd_data.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\param.h		\
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
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h
		$(CC) $(OPTION) \src\atlanta\SRC\ATD_TN.c

$(OBJECT)\ATD_D2T.obj :	\src\atlanta\SRC\ATD_D2T.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\ctry_pro.h		\
					\src\atlanta\define\ncu_def.h		\
						\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\timer10.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\SH7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC) $(OPTION) \src\atlanta\SRC\ATD_D2T.c

$(OBJECT)\ATD_LC.obj :	\src\atlanta\SRC\ATD_LC.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\ext_v\atd_data.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC) $(OPTION) \src\atlanta\SRC\ATD_LC.c

$(OBJECT)\ATD_AFTN.obj :	\src\atlanta\SRC\ATD_AFTN.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\ctry_pro.h		\
					\src\atlanta\define\ncu_def.h		\
						\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\time.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\atlanta\define\fcm_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\std.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\SH7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
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
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\atd_data.h		\
				\src\atlanta\ext_v\atd_tbl.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\sh7043\define\def_tib.h
		$(CC) $(OPTION) \src\atlanta\SRC\ATD_AFTN.c

$(OBJECT)\ATD_DSE.obj :	\src\atlanta\SRC\ATD_DSE.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\ext_v\atd_data.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\io_pro.h
		$(CC) $(OPTION) \src\atlanta\SRC\ATD_DSE.c

$(OBJECT)\ATD_MAIN.obj :	\src\atlanta\SRC\ATD_MAIN.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\ncu_pro.h		\
					\src\atlanta\define\ncu_def.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\ncu_stat.h		\
				\src\atlanta\define\sys_stat.h		\
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
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\atd_data.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\param.h		\
				\src\atlanta\ext_v\ncu_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\uni_pro.h
		$(CC) $(OPTION) \src\atlanta\SRC\ATD_MAIN.c

$(OBJECT)\ATD_FREQ.obj :	\src\atlanta\SRC\ATD_FREQ.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\ctry_pro.h		\
					\src\atlanta\define\ncu_def.h		\
						\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\fcm_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\ext_v\atd_tbl.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysbatch.h		\
						\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\sh7043\define\def_evtn.h
		$(CC) $(OPTION) \src\atlanta\SRC\ATD_FREQ.c

$(OBJECT)\ATD_DT.obj :	\src\atlanta\SRC\ATD_DT.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\ctry_pro.h		\
					\src\atlanta\define\ncu_def.h		\
						\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysbatch.h		\
						\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\atd_data.h		\
				\src\atlanta\define\param.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\def_tib.h
		$(CC) $(OPTION) \src\atlanta\SRC\ATD_DT.c

$(OBJECT)\ATDFLTOF.obj :	\src\atlanta\SRC\ATDFLTOF.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\ext_v\atd_tbl.h		\
				\src\atlanta\sh7043\define\def_evtn.h
		$(CC) $(OPTION) \src\atlanta\SRC\ATDFLTOF.c

$(OBJECT)\ATD_LCOF.obj :	\src\atlanta\SRC\ATD_LCOF.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\io_pro.h
		$(CC) $(OPTION) \src\atlanta\SRC\ATD_LCOF.c

$(OBJECT)\ATDRELAY.obj :	\src\atlanta\SRC\ATDRELAY.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\sh7043\define\io_pro.h
		$(CC) $(OPTION) \src\atlanta\SRC\ATDRELAY.c

$(OBJECT)\ATD_CNG.obj :	\src\atlanta\SRC\ATD_CNG.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\ctry_pro.h		\
					\src\atlanta\define\ncu_def.h		\
						\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\ext_v\atd_tbl.h		\
				\src\atlanta\ext_v\atd_data.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
						\src\atlanta\define\mem_def.h		\
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
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h
		$(CC) $(OPTION) \src\atlanta\SRC\ATD_CNG.c

$(OBJECT)\ATD_STOP.obj :	\src\atlanta\SRC\ATD_STOP.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC) $(OPTION) \SRC\atlanta\SRC\ATD_STOP.c

$(OBJECT)\ATDMCRYT.obj :	\src\atlanta\SRC\ATDMCRYT.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\ctry_pro.h		\
					\src\atlanta\define\ncu_def.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\time.h		\
				\src\memsw\define\mems_pro.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\ext_v\atd_tbl.h		\
				\src\atlanta\ext_v\atd_data.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\define\ncu_stat.h		\
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
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\ncu_data.h		\
					\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysscan.h
		$(CC) $(OPTION) \SRC\atlanta\SRC\ATDMCRYT.c
