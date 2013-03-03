#------------------------------------------------------------------------
#   POPLAR/ANZU_L   メイン部(MAN)のメイクファイル
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
LNK         = lnk /subcommand=\src\atlanta\make\MAN.sub
#-----------------------------------------------------------------------------
#   引数を定義
#-----------------------------------------------------------------------------
!if ("$(MODEL)" == "POPLAR_H")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_NOP	= /op=0       /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!else
OPTION      = /op=0 /deb /def=($(MODEL),$(COUNTRY)) /cp=sh2
OPTION_NOP  = /op=0 /deb /def=($(MODEL),$(COUNTRY)) /cp=sh2
!endif
#!if ("$(MODEL)" == "POPLAR_B")
!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLR_BN") 
!if ("$(COUNTRY)" == "JPN")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
#OPTION		= /op=0       /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_NOP	= /op=0       /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
!endif

!if ("$(MODEL)" == "SAKAKI")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_NOP	= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

ASM_OPT     = /cpu=$(CPU_OPT) /debug /object=$*.obj
#-----------------------------------------------------------------------------
#   オブジェクトディレクトリを定義
#-----------------------------------------------------------------------------
OBJECT      = \src\atlanta\$(MODEL)\work\$(COUNTRY)
#
#-----------------------------------------------------------------------------
#   ﾒｲﾓｼﾞｭｰﾙのﾘﾝｸを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\man.lnk:   \src\atlanta\make\man.SUB	\
			$(OBJECT)\man_init.obj	\
			$(OBJECT)\man_main.obj	\
			$(OBJECT)\man_msge.obj	\
			$(OBJECT)\man_scnm.obj	\
			$(OBJECT)\man_prtm.obj	\
			$(OBJECT)\man_oprm.obj	\
			$(OBJECT)\man_comm.obj	\
			$(OBJECT)\man_optm.obj	\
			$(OBJECT)\man_idle.obj	\
			$(OBJECT)\man_timr.obj	\
			$(OBJECT)\man_sens.obj	\
			$(OBJECT)\man_exec.obj	\
			$(OBJECT)\man_sub.obj	\
			$(OBJECT)\man_buzr.obj	\
			$(OBJECT)\man_led.obj	\
			$(OBJECT)\man_mult.obj	\
			$(OBJECT)\man_dmy.obj
		$(LNK)

#-----------------------------------------------------------------------------
#   ﾒｲﾝﾓｼﾞｭｰﾙのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
#
$(OBJECT)\man_init.obj:   $(SRC)\man_init.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\mntsw_a.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\def_semn.h		\
				\src\atlanta\define\cdc_def.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\dma_def.h		\
					\src\atlanta\sh7043\define\sh_port.h		\
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
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
				\src\atlanta\ext_v\sys_port.h		\
				\src\atlanta\ext_v\man_data.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\sh7043\ext_v\extv_sem.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\ext_v\cdc_data.h		\
					\src\atlanta\define\cdc_blk.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\lst_def.h		\
						\src\atlanta\define\sysdoc.h		\
				\src\atlanta\ext_v\fcm_data.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\ncu_data.h		\
					\src\atlanta\define\ncu_def.h		\
					\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\ext_v\scn_data.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\dma_data.h		\
					\src\atlanta\define\dma_blk.h		\
				\src\atlanta\ext_v\cmn_data.h		\
					\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\scn_pro.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\opr\ank\define\opr_pro.h		\
				\src\atlanta\ext_v\rom_tbl.h
       $(CC)	$(OPTION) $(SRC)\man_init.c
#
$(OBJECT)\man_main.obj:   $(SRC)\man_main.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mntsw_c.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\syscntpl.h		\
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
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\fip_def.h		\
				\src\atlanta\ext_v\man_data.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\ext_v\scn_data.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\ext_v\scn_tbl.h		\
					\src\atlanta\define\lst_def.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\scn_pro.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\opr\ank\define\opr_pro.h
       $(CC) 	$(OPTION) $(SRC)\man_main.c
#
$(OBJECT)\man_msge.obj:   $(SRC)\man_msge.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mntsw_c.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\syscntpl.h		\
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
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\fip_def.h		\
				\src\atlanta\ext_v\man_data.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\ext_v\extv_sem.h		\
					\src\atlanta\sh7043\define\def_semn.h		\
				\src\atlanta\define\mntsw_a.h		\
				\src\atlanta\ext_v\scn_data.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\ext_v\scn_tbl.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\scn_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\opr\ank\define\opr_pro.h
       $(CC) 	$(OPTION) $(SRC)\man_msge.c
#
$(OBJECT)\man_scnm.obj:   $(SRC)\man_scnm.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mntsw_c.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\syscntpl.h		\
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
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\fip_def.h		\
				\src\atlanta\ext_v\man_data.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\ext_v\extv_sem.h		\
					\src\atlanta\sh7043\define\def_semn.h		\
				\src\atlanta\define\mntsw_a.h		\
				\src\atlanta\ext_v\scn_data.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\ext_v\scn_tbl.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\scn_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\opr\ank\define\opr_pro.h
       $(CC) 	$(OPTION) $(SRC)\man_scnm.c
#
$(OBJECT)\man_prtm.obj:   $(SRC)\man_prtm.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mntsw_c.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\syscntpl.h		\
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
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\fip_def.h		\
				\src\atlanta\ext_v\man_data.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\ext_v\extv_sem.h		\
					\src\atlanta\sh7043\define\def_semn.h		\
				\src\atlanta\define\mntsw_a.h		\
				\src\atlanta\ext_v\scn_data.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\ext_v\scn_tbl.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\scn_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\opr\ank\define\opr_pro.h
       $(CC) 	$(OPTION) $(SRC)\man_prtm.c
#
$(OBJECT)\man_oprm.obj:   $(SRC)\man_oprm.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mntsw_c.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\syscntpl.h		\
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
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\fip_def.h		\
				\src\atlanta\ext_v\man_data.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\ext_v\extv_sem.h		\
					\src\atlanta\sh7043\define\def_semn.h		\
				\src\atlanta\define\mntsw_a.h		\
				\src\atlanta\ext_v\scn_data.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\ext_v\scn_tbl.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\scn_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\opr\ank\define\opr_pro.h
       $(CC) 	$(OPTION) $(SRC)\man_oprm.c
#
$(OBJECT)\man_comm.obj:   $(SRC)\man_comm.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mntsw_c.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\syscntpl.h		\
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
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\fip_def.h		\
				\src\atlanta\ext_v\man_data.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\ext_v\extv_sem.h		\
					\src\atlanta\sh7043\define\def_semn.h		\
				\src\atlanta\define\mntsw_a.h		\
				\src\atlanta\ext_v\scn_data.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\ext_v\scn_tbl.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\scn_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\opr\ank\define\opr_pro.h
       $(CC) 	$(OPTION) $(SRC)\man_comm.c
#
$(OBJECT)\man_optm.obj:   $(SRC)\man_optm.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mntsw_c.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\syscntpl.h		\
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
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\fip_def.h		\
				\src\atlanta\ext_v\man_data.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\sh7043\ext_v\extv_sem.h		\
					\src\atlanta\sh7043\define\def_semn.h		\
				\src\atlanta\define\mntsw_a.h		\
				\src\atlanta\ext_v\scn_data.h		\
					\src\atlanta\define\scn_def.h		\
				\src\atlanta\ext_v\scn_tbl.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\scn_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\opr\ank\define\opr_pro.h
       $(CC) 	$(OPTION_NOP) $(SRC)\man_optm.c
#
$(OBJECT)\man_idle.obj:   $(SRC)\man_idle.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h
        $(CC) 	$(OPTION) $(SRC)\man_idle.c
#
$(OBJECT)\man_timr.obj:   $(SRC)\man_timr.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\sys_day.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mnt_sw.h		\
					\src\atlanta\define\mntsw_a.h		\
					\src\atlanta\define\mntsw_b.h		\
					\src\atlanta\define\mntsw_c.h		\
					\src\atlanta\define\mntsw_d.h		\
					\src\atlanta\define\mntsw_e.h		\
					\src\atlanta\define\mntsw_f.h		\
					\src\atlanta\define\mntsw_g.h		\
					\src\atlanta\define\mntsw_h.h		\
					\src\atlanta\define\mntsw_i.h		\
					\src\atlanta\define\mntsw_j.h		\
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
					\src\atlanta\define\fip_def.h		\
				\src\atlanta\ext_v\sys_port.h		\
				\src\atlanta\ext_v\mem_data.h		\
				\src\atlanta\ext_v\man_data.h		\
					\src\atlanta\define\dma_def.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\sh7043\define\def_semn.h		\
				\src\atlanta\sh7043\ext_v\extv_sem.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
				\src\atlanta\opr\ank\define\opr_pro.h
        $(CC)   $(OPTION) $(SRC)\man_timr.c
#
$(OBJECT)\man_sens.obj:   $(SRC)\man_sens.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
					\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysmcopy.h		\
					\src\atlanta\define\sysmemrx.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\SYSMAX.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysonet.h		\
					\src\atlanta\define\sysexec.h		\
					\src\atlanta\define\syslifem.h		\
					\src\atlanta\define\sysshad.h		\
					\src\atlanta\define\sysspeed.h		\
					\src\atlanta\define\sysdiali.h		\
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
					\src\atlanta\define\fip_def.h
        $(CC)   $(OPTION) $(SRC)\man_sens.c
#
$(OBJECT)\man_exec.obj:   $(SRC)\man_exec.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\syscomf.h		\
				\src\atlanta\define\sysexec.h		\
				\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sysmemrx.h		\
					\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysonet.h		\
					\src\atlanta\define\syslifem.h		\
					\src\atlanta\define\sysshad.h		\
					\src\atlanta\define\sysspeed.h		\
					\src\atlanta\define\sysdiali.h		\
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
					\src\atlanta\define\fip_def.h		\
				\src\atlanta\define\syscntpl.h
        $(CC)   $(OPTION) $(SRC)\man_exec.c
#
$(OBJECT)\man_sub.obj:    $(SRC)\man_sub.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sys_pdwn.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sysexec.h		\
				\src\atlanta\sh7043\define\def_semn.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\syspcrx.h		\
				\src\atlanta\define\fip_def.h		\
				\src\atlanta\define\syscntpl.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\SYSMAX.h		\
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
					\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysdeprt.h		\
					\src\atlanta\define\systbok.h		\
					\src\atlanta\define\sysopspd.h		\
					\src\atlanta\define\sysringm.h		\
						\src\atlanta\define\ncu_cnst.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
				\src\atlanta\ext_v\man_data.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\sh7043\ext_v\extv_sem.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\message.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\opr\ank\define\opr_pro.h
        $(CC)   $(OPTION) $(SRC)\man_sub.c
#
$(OBJECT)\man_buzr.obj:   $(SRC)\man_buzr.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\unisw_f.h		\
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\stng_pro.h		\
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
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\man_data.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
				\src\atlanta\opr\ank\define\opr_pro.h
        $(CC)   $(OPTION) $(SRC)\man_buzr.c
#
$(OBJECT)\man_led.obj:   $(SRC)\man_led.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\syslocal.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\stng_pro.h		\
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
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
				\src\atlanta\ext_v\sys_port.h		\
				\src\atlanta\sh7043\define\sh_port.h
        $(CC)   $(OPTION) $(SRC)\man_led.c
#
$(OBJECT)\man_mult.obj:	$(SRC)\man_mult.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sys_line.h		\
				\src\atlanta\define\sysmjnl.h		\
				\src\atlanta\define\sys_opt.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sysbatch.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\syspcrx.h		\
							\src\atlanta\define\dma_blk.h
		$(CC)	$(OPTION) $(SRC)\man_mult.c

$(OBJECT)\man_dmy.obj:    $(SRC)\man_dmy.c	\
				\src\atlanta\define\product.h
        $(CC)   $(OPTION) $(SRC)\man_dmy.c
