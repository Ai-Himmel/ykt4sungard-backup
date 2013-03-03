#------------------------------------------------------------------------
#   POPLAR/ANZU_L	共通モジュールメイクファイル
#------------------------------------------------------------------------
SRC			= \src\atlanta\src
DEFINE 		= \src\atlanta\define
DEFV 		= \src\atlanta\def_v
EXTV		= \src\atlanta\ext_v
SRCSH		= \src\atlanta\sh7043\src
DEFINESH	= \src\atlanta\sh7043\define
DEFVSH		= \src\atlanta\sh7043\def_v
EXTVSH		= \src\atlanta\sh7043\ext_v
MONSH		= \src\atlanta\sh7043\mon
MAKE		= \src\atlanta\make
POPB_SRC	= \src\atlanta\poplar_b\src
POPH_SRC	= \src\atlanta\poplar_h\src

#-----------------------------------------------------------------------------
#	RISC結合用ﾏｸﾛ
#-----------------------------------------------------------------------------
#
CC			= shc
ASM			= asmsh

#!if ("$(MODEL)" != "POPLAR_H")
#OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
#OPTION_ND	= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
#OPTION_DEV  = /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
#!endif
!if ("$(MODEL)" == "POPLAR_H")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=1 /size      /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_DEV	= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!else
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_DEV  = /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

!if ("$(MODEL)" == "SAKAKI")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=1 /size /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_DEV	= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU") || ("$(MODEL)" == "HINOKI2") || ("$(MODEL)" == "SATSUKI2")) || ("$(MODEL)" == "STOCKHM2")
OPTION		= /op=0  /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=0  /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_DEV	= /op=0  /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif


ASM_OPT		= /cpu=sh2 /debug /object=$*.obj
LNK			= lnk /subcommand=\src\atlanta\make\cmn.sub
OBJECT      = \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-----------------------------------------------------------------------------
#	共通ﾓｼﾞｭｰﾙのﾘﾝｸを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\cmn.lnk:	\src\atlanta\make\cmn.sub	\
			$(OBJECT)\cmn_buzz.obj			\
			$(OBJECT)\cmn_chk.obj			\
			$(OBJECT)\cmn_com.obj			\
			$(OBJECT)\cmn_ctry.obj			\
			$(OBJECT)\cmn_cnv.obj			\
			$(OBJECT)\cmn_ini.obj			\
			$(OBJECT)\cmn_rst.obj			\
			$(OBJECT)\cmn_stng.obj			\
			$(OBJECT)\cmn_str.obj			\
			$(OBJECT)\cmn_tup.obj			\
			$(OBJECT)\cmn_io.obj			\
			$(OBJECT)\cmn_tmr.obj			\
			$(OBJECT)\cmn_iorw.obj			\
			$(OBJECT)\cmn_iset.obj			\
			$(OBJECT)\cmnuni_a.obj			\
			$(OBJECT)\cmnuni_b.obj			\
			$(OBJECT)\cmnuni_c.obj			\
			$(OBJECT)\cmnuni_d.obj			\
			$(OBJECT)\cmnuni_e.obj			\
			$(OBJECT)\cmnuni_f.obj			\
			$(OBJECT)\cmnuni_g.obj			\
			$(OBJECT)\cmnuni_h.obj			\
			$(OBJECT)\cmnuni_i.obj			\
			$(OBJECT)\cmnuni_j.obj			\
#Add By 1998/09/02  By M.Kuwahara
			$(OBJECT)\cmn_warp.obj
#			$(OBJECT)\cmn_dbg.obj
		$(LNK)
#-----------------------------------------------------------------------------
#	共通ﾓｼﾞｭｰﾙのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
#
$(OBJECT)\cmn_buzz.obj:	$(SRC)\cmn_buzz.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\buzzer.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\scn_def.h		\
				\src\atlanta\define\scn_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\\ext_v\sys_port.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC)	$(OPTION_ND) $(SRC)\cmn_buzz.c
#
$(OBJECT)\cmn_chk.obj:	$(SRC)\cmn_chk.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\mem_def.h
		$(CC)	$(OPTION) $(SRC)\cmn_chk.c
#
$(OBJECT)\cmn_com.obj:	$(SRC)\cmn_com.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
						\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sysbatch.h		\
				\src\atlanta\define\sys_stat.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h
		$(CC)	$(OPTION) $(SRC)\cmn_com.c
#
$(OBJECT)\cmn_ctry.obj:	$(SRC)\cmn_ctry.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\param.h		\
				\src\atlanta\define\stng_pro.h		\
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
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\cmn_tbl.h		\
					\src\atlanta\define\country.h		\
				\src\atlanta\ext_v\atd_tbl.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\ext_v\ncu_tbl.h		\
					\src\atlanta\define\ncu_def.h		\
				\src\atlanta\ext_v\rom_tbl.h		\
				\src\atlanta\define\status.h
		$(CC)	$(OPTION_ND) $(SRC)\cmn_ctry.c
#
$(OBJECT)\cmn_cnv.obj:	$(SRC)\cmn_cnv.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
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
				\src\atlanta\ext_v\cmn_tbl.h		\
					\src\atlanta\define\country.h
		$(CC)	$(OPTION_DEV) $(SRC)\cmn_cnv.c
#
$(OBJECT)\cmn_ini.obj:	$(SRC)\cmn_ini.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\ctry_pro.h		\
					\src\atlanta\define\ncu_def.h		\
						\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\uni_sw.h		\
					\src\atlanta\define\unisw_a.h		\
					\src\atlanta\define\unisw_b.h		\
					\src\atlanta\define\unisw_c.h		\
					\src\atlanta\define\unisw_d.h		\
					\src\atlanta\define\unisw_e.h		\
					\src\atlanta\define\unisw_f.h		\
					\src\atlanta\define\unisw_g.h		\
					\src\atlanta\define\unisw_h.h		\
					\src\atlanta\define\unisw_i.h		\
					\src\atlanta\define\unisw_j.h		\
				\src\atlanta\define\param.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\memsw\define\mem_sw_a.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\atlanta\define\mntsw_c.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
				\src\atlanta\ext_v\rom_tbl.h		\
				\src\atlanta\ext_v\ini_tbl.h		\
					\src\atlanta\define\status.h		\
				\src\atlanta\ext_v\cmn_tbl.h		\
					\src\atlanta\define\country.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
					\src\atlanta\define\lst_def.h		\
						\src\atlanta\define\sysdoc.h		\
					\src\atlanta\define\dma_def.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\sh7043\define\def_semn.h		\
				\src\atlanta\sh7043\ext_v\extv_sem.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\syscntpl.h
                $(CC)   $(OPTION) /l /sh=ob $(SRC)\cmn_ini.c
#
$(OBJECT)\cmn_rst.obj:	$(SRC)\cmn_rst.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\syslocal.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
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
					\src\atlanta\define\fip_def.h
		$(CC)	$(OPTION_ND) $(SRC)\cmn_rst.c
#
$(OBJECT)\cmn_stng.obj:	$(SRC)\cmn_stng.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\sys_remo.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\memsw\define\mems_pro.h		\
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
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\define\mntsw_e.h
		$(CC)	$(OPTION_ND) $(SRC)\cmn_stng.c
#
$(OBJECT)\cmn_str.obj:	$(SRC)\cmn_str.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
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
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
					\src\atlanta\define\lst_def.h		\
						\src\atlanta\define\sysdoc.h
		$(CC)	$(OPTION_DEV) $(SRC)\cmn_str.c
#
$(OBJECT)\cmn_tup.obj:	$(SRC)\cmn_tup.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\evttomsg.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\ext_v\cmn_data.h		\
					\src\atlanta\define\cmn_def.h
		$(CC)	$(OPTION) $(SRC)\cmn_tup.c
#
$(OBJECT)\cmn_io.obj:	$(SRCSH)\cmn_io.c	\
				\src\atlanta\hinoki\src\hino_io.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\syslocal.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\unisw_h.h		\
				\src\atlanta\define\uni_pro.h		\
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
					\src\atlanta\define\syscntpl.h	\
					\src\atlanta\define\syspcrx.h	\
					\src\atlanta\define\dpr_def.h	\
					\src\atlanta\define\sysfcode.h	\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h	\
					\src\atlanta\define\sysdial.h	\
					\src\atlanta\define\fip_def.h	\
				\src\atlanta\ext_v\scn_data.h		\
					\src\atlanta\define\mem_def.h	\
					\src\atlanta\define\message.h	\
					\src\atlanta\define\scn_def.h	\
				\src\atlanta\ext_v\sys_port.h		\
				\src\atlanta\sh7043\define\sh_port.h	\
				\src\atlanta\sh7043\define\sh_sys.h	\
				\src\atlanta\sh7043\define\io_pro.h
		$(CC)	$(OPTION) /l /sh=ob $(SRCSH)\cmn_io.c
#
$(OBJECT)\cmn_tmr.obj:	$(SRCSH)\cmn_tmr.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\sh7043\define\sh_sys.h
		$(CC)	$(OPTION) $(SRCSH)\cmn_tmr.c
#
!if ("$(MODEL)" == "ANZU_L") || ("$(MODEL)" == "ANZU_V")
$(OBJECT)\cmn_iorw.obj:	\src\atlanta\$(MODEL)\src\cmn_iorw.src
		$(ASM)	\src\atlanta\$(MODEL)\src\cmn_iorw.src $(ASM_OPT)
!else
$(OBJECT)\cmn_iorw.obj:	$(SRCSH)\cmn_iorw.src
		$(ASM)	$(SRCSH)\cmn_iorw.src $(ASM_OPT)
!endif
#
#!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLAR_L")
#!if ("$(MODEL)" == "POPLAR_B")
#$(OBJECT)\cmn_iset.obj: $(POPB_SRC)\cmn_iset.src
#		$(ASM)	$(POPB_SRC)\cmn_iset.src $(ASM_OPT)
#!else
# # 割込み禁止時間測定 O.Kimoto 1998/02/12
# !if ("$(MODEL)" == "POPLAR_H")
# $(OBJECT)\cmn_iset.obj: $(POPH_SRC)\cmn_iset.src
# 		$(ASM)	$(POPH_SRC)\cmn_iset.src $(ASM_OPT)
# !else
# $(OBJECT)\cmn_iset.obj: $(SRCSH)\cmn_iset.src
# 		$(ASM)	$(SRCSH)\cmn_iset.src $(ASM_OPT)
# !endif
$(OBJECT)\cmn_iset.obj: $(SRCSH)\cmn_iset.src
		$(ASM)	$(SRCSH)\cmn_iset.src $(ASM_OPT)
#!endif
#$(OBJECT)\cmn_iset.obj: $(SRCSH)\cmn_iset.src
#		$(ASM)	$(SRCSH)\cmn_iset.src $(ASM_OPT)
#
$(OBJECT)\cmnuni_a.obj:	$(SRC)\cmnuni_a.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\unisw_a.h		\
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
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\define\uni_pro.h
		$(CC)	$(OPTION_ND) $(SRC)\cmnuni_a.c
#
$(OBJECT)\cmnuni_b.obj:	$(SRC)\cmnuni_b.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\unisw_b.h		\
				\src\atlanta\define\uni_pro.h		\
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
		$(CC)	$(OPTION_ND) $(SRC)\cmnuni_b.c
#
$(OBJECT)\cmnuni_c.obj:	$(SRC)\cmnuni_c.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\unisw_c.h		\
				\src\atlanta\define\uni_pro.h		\
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
		$(CC)	$(OPTION_ND) $(SRC)\cmnuni_c.c
#
$(OBJECT)\cmnuni_d.obj:	$(SRC)\cmnuni_d.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\unisw_d.h		\
				\src\atlanta\define\uni_pro.h		\
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
		$(CC)	$(OPTION_ND) $(SRC)\cmnuni_d.c
#
$(OBJECT)\cmnuni_e.obj:	$(SRC)\cmnuni_e.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\unisw_e.h		\
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
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\define\uni_pro.h
		$(CC)	$(OPTION_ND) $(SRC)\cmnuni_e.c
#
$(OBJECT)\cmnuni_f.obj:	$(SRC)\cmnuni_f.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\unisw_f.h		\
				\src\atlanta\define\uni_pro.h		\
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
		$(CC)	$(OPTION) $(SRC)\cmnuni_f.c
#		$(CC)	$(OPTION_ND) $(SRC)\cmnuni_f.c
#
$(OBJECT)\cmnuni_g.obj:	$(SRC)\cmnuni_g.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\unisw_g.h		\
				\src\atlanta\define\uni_pro.h		\
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
		$(CC)	$(OPTION_ND) $(SRC)\cmnuni_g.c
#
$(OBJECT)\cmnuni_h.obj:	$(SRC)\cmnuni_h.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\unisw_h.h		\
				\src\atlanta\define\uni_pro.h		\
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
		$(CC)	$(OPTION_ND) $(SRC)\cmnuni_h.c
#
$(OBJECT)\cmnuni_i.obj:	$(SRC)\cmnuni_i.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\unisw_i.h		\
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
		$(CC)	$(OPTION_ND) $(SRC)\cmnuni_i.c
#
$(OBJECT)\cmnuni_j.obj:	$(SRC)\cmnuni_j.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\unisw_j.h		\
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
		$(CC)	$(OPTION_ND) $(SRC)\cmnuni_j.c
$(OBJECT)\cmn_warp.obj:	$(SRC)\cmn_warp.c	
		$(CC)	$(OPTION) $(SRC)\cmn_warp.c
#
#ＦＣＯＤＥ送信でリセットがかかる件 T.Nose 1997/08/07
#$(OBJECT)\cmn_dbg.obj:	$(SRCSH)\cmn_dbg.src
#		$(ASM)	$(SRCSH)\cmn_dbg.src $(ASM_OPT)

