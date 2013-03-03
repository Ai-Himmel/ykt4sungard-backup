# =============================================================================
# =	 ﾏｸﾛ定義																  #
# =============================================================================
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

#!if ("$(MODEL)" == "POPLAR_B")
#!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLAR_N")
!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLR_BN") || ("$(MODEL)" == "POPLAR_N")
OPTION		= /op=0 /deb       /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=1 /deb /size /cp=sh2 /def=($(MODEL),$(COUNTRY))

#OPTION_ND	= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!if ("$(COUNTRY)" == "USA")
OPTION_ND	= /op=0 /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
!endif
#!if ("$(MODEL)" == "POPLAR_L") || ("$(MODEL)" == "POPLAR_N") || ("$(MODEL)" == "ANZU_L") || ("$(MODEL)" == "ANZU_V")
!if ("$(MODEL)" == "POPLAR_L") || ("$(MODEL)" == "ANZU_L") || ("$(MODEL)" == "ANZU_V")
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

!if ("$(MODEL)" == "POPLAR_H")
#オプションの付け方が反対です。
#OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
#OPTION_ND	= /op=0 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION		= /op=0 /deb       /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=1 /deb /size /cp=sh2 /def=($(MODEL),$(COUNTRY))
#OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
#OPTION_ND	= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

!if ("$(MODEL)" == "SAKAKI")
OPTION		= /op=0 /deb       /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=0 /deb       /cp=sh2 /def=($(MODEL),$(COUNTRY))
#OPTION_ND	= /op=1 /deb /size /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

!if ("$(MODEL)" == "HINOKI")
#最適化します 1999/01/24
OPTION		= /op=0 /deb       /cp=sh2 /def=($(MODEL),$(COUNTRY))
#OPTION_ND	= /op=0 /deb       /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=1 /deb /size /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

!if ("$(MODEL)" == "HINOKI2") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU") || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
#最適化します 1999/01/24
OPTION		= /op=0 /deb       /cp=sh2 /def=($(MODEL),$(COUNTRY))
#OPTION_ND	= /op=0 /deb       /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=1 /deb /size /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

OPTION2		= /op=0 /deb /def=($(MODEL),$(COUNTRY),$(CPU)) /cp=$(CPU_OPT)
ASM_OPT		= /cpu=$(CPU_OPT) /debug /object=$*.obj
MACHINE_DEF = sh
CMD_SUFX	= sub
LNK			= lnk /subcommand=\src\atlanta\make\ncu.sub
OBJECT		 = \src\atlanta\$(MODEL)\work\$(COUNTRY)


# =============================================================================
# =	 ﾓｼﾞｭｰﾙ ﾒｲｸ																  #
# =============================================================================
$(OBJECT)\NCU.lnk :	\src\atlanta\make\NCU.$(CMD_SUFX)	\
				$(OBJECT)\NCU_MAIN.OBJ	\
				$(OBJECT)\NCU_TEL0.OBJ	\
				$(OBJECT)\NCU_TEL1.OBJ	\
				$(OBJECT)\NCU_OH.OBJ	\
				$(OBJECT)\NCU_RING.OBJ	\
				$(OBJECT)\NCU_GRS.OBJ	\
				$(OBJECT)\NCU_RBT.OBJ	\
				$(OBJECT)\NCU_TAD.OBJ	\
				$(OBJECT)\NCU_RLY.OBJ	\
				$(OBJECT)\NCU_D_IN.OBJ	\
				$(OBJECT)\NCU_INT.OBJ
		$(LNK)


# =============================================================================
# =	 ｺﾝﾊﾟｲﾙ																	  #
# =============================================================================
$(OBJECT)\NCU_MAIN.OBJ:	$(SRC)\NCU_MAIN.C	\
				\src\atlanta\define\product.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\sys_remo.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\ctry_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\buzzer.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\ncu_pro.h		\
				\src\atlanta\define\ncu_stat.h		\
				\src\atlanta\define\ncu_msg.h		\
				\src\atlanta\define\ncu_ret.h		\
				\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\ncu_def.h		\
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
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\ncu_data.h		\
				\src\atlanta\ext_v\ncu_tbl.h		\
				\src\atlanta\ext_v\sys_port.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\def_tib.h
		$(CC)	$(OPTION_ND)	$(SRC)\NCU_MAIN.C
#
$(OBJECT)\NCU_TEL0.OBJ:	$(SRC)\NCU_TEL0.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\ncu_pro.h		\
				\src\atlanta\define\ncu_stat.h		\
				\src\atlanta\define\ncu_msg.h		\
				\src\atlanta\define\ncu_ret.h		\
				\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\ncu_def.h		\
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
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\atd_data.h		\
				\src\atlanta\ext_v\ncu_data.h		\
				\src\atlanta\ext_v\ncu_tbl.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\def_tib.h
#		$(CC)	$(OPTION_ND)	$(SRC)\NCU_TEL0.C
		$(CC)	$(OPTION)	$(SRC)\NCU_TEL0.C
#
$(OBJECT)\NCU_TEL1.OBJ:	$(SRC)\NCU_TEL1.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\ctry_pro.h		\
					\src\atlanta\define\atd_def.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\ncu_pro.h		\
				\src\atlanta\define\ncu_stat.h		\
				\src\atlanta\define\ncu_msg.h		\
				\src\atlanta\define\ncu_ret.h		\
				\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\ncu_def.h		\
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
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\ncu_data.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\opr\ank\define\opr_def.h		\
				\src\atlanta\define\param.h		\
				\src\atlanta\ext_v\atd_data.h
#		$(CC)	$(OPTION_ND)	$(SRC)\NCU_TEL1.C
		$(CC)	$(OPTION)	$(SRC)\NCU_TEL1.C
#
$(OBJECT)\NCU_OH.OBJ:	$(SRC)\NCU_OH.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\sysdiali.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\buzzer.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\ncu_pro.h		\
				\src\atlanta\define\ncu_stat.h		\
				\src\atlanta\define\ncu_msg.h		\
				\src\atlanta\define\ncu_ret.h		\
				\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\ncu_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
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
				\src\atlanta\ext_v\sys_port.h		\
				\src\atlanta\ext_v\ncu_data.h		\
				\src\atlanta\ext_v\ncu_tbl.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\ext_v\atd_tbl.h
		$(CC)	$(OPTION_ND)	$(SRC)\NCU_OH.C
#
$(OBJECT)\NCU_RING.OBJ:	$(SRC)\NCU_RING.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\ctry_pro.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\ncu_pro.h		\
				\src\atlanta\define\ncu_stat.h		\
				\src\atlanta\define\ncu_msg.h		\
				\src\atlanta\define\ncu_ret.h		\
				\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\ncu_def.h		\
				\src\atlanta\define\param.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
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
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\ncu_data.h		\
				\src\atlanta\ext_v\ncu_tbl.h		\
				\src\atlanta\ext_v\sys_port.h		\
				\src\atlanta\sh7043\define\sh_sys.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\def_tib.h
#		$(CC)	$(OPTION_ND)	$(SRC)\NCU_RING.C
		$(CC)	$(OPTION)	$(SRC)\NCU_RING.C
#
$(OBJECT)\NCU_RBT.OBJ:	$(SRC)\NCU_RBT.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\sysdiali.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\fcm_pro.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\ctry_pro.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\cmn_pro.h		\
				\src\atlanta\define\ncu_pro.h		\
				\src\atlanta\define\ncu_stat.h		\
				\src\atlanta\define\ncu_msg.h		\
				\src\atlanta\define\ncu_ret.h		\
				\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\ncu_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
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
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\ncu_data.h		\
				\src\atlanta\ext_v\ncu_tbl.h		\
				\src\atlanta\ext_v\atd_data.h		\
				\src\atlanta\ext_v\sys_port.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\sh_sys.h
		$(CC)	$(OPTION_ND)	$(SRC)\NCU_RBT.C
#
$(OBJECT)\NCU_GRS.OBJ:	$(SRC)\NCU_GRS.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\sysdiali.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\buzzer.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\scn_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\ctry_pro.h		\
				\src\atlanta\define\atd_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\ncu_pro.h		\
				\src\atlanta\define\ncu_stat.h		\
				\src\atlanta\define\ncu_msg.h		\
				\src\atlanta\define\ncu_ret.h		\
				\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\ncu_def.h		\
					\src\atlanta\define\dma_def.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\ncu_data.h		\
				\src\atlanta\ext_v\ncu_tbl.h		\
				\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\ext_v\sys_port.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC)	$(OPTION_ND)	$(SRC)\NCU_GRS.C
#
$(OBJECT)\NCU_RLY.OBJ:	$(SRC)\NCU_RLY.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\ctry_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\ncu_pro.h		\
				\src\atlanta\define\ncu_stat.h		\
				\src\atlanta\define\ncu_ret.h		\
				\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\ncu_def.h		\
					\src\atlanta\define\dma_def.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\sys_port.h		\
				\src\atlanta\ext_v\ncu_data.h		\
					\src\atlanta\define\message.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC)	$(OPTION)	$(SRC)\NCU_RLY.C
#
$(OBJECT)\NCU_TAD.OBJ:	$(SRC)\NCU_TAD.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\time.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\ncu_pro.h		\
				\src\atlanta\define\ncu_stat.h		\
				\src\atlanta\define\ncu_msg.h		\
				\src\atlanta\define\ncu_ret.h		\
				\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\ncu_def.h		\
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
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\ncu_data.h		\
				\src\atlanta\ext_v\ncu_tbl.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\io_pro.h
		$(CC)	$(OPTION_ND)	$(SRC)\NCU_TAD.C
#
$(OBJECT)\NCU_D_IN.OBJ:	$(SRC)\NCU_D_IN.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\ncu_stat.h		\
				\src\atlanta\define\ncu_msg.h		\
				\src\atlanta\define\ncu_ret.h		\
				\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\ncu_def.h		\
				\src\atlanta\define\ncu_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\memsw\define\mems_pro.h		\
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
				\src\atlanta\ext_v\ncu_tbl.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\sh_port.h
		$(CC)	$(OPTION_ND)	$(SRC)\NCU_D_IN.C
#
$(OBJECT)\NCU_INT.OBJ:	$(SRC)\NCU_INT.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\ncu_stat.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\memsw\define\mem_sw_a.h		\
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
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\ncu_data.h		\
					\src\atlanta\define\ncu_def.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\ext_v\sys_port.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\sh7043\define\sh_sys.h		\
				\src\atlanta\sh7043\define\def_evtn.h
		$(CC)	$(OPTION)	$(SRC)\NCU_INT.C
