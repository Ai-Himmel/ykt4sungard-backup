#------------------------------------------------------------------------
#   POPLAR/ANZU_L   リストのメイクファイル
#------------------------------------------------------------------------
WORD	= \src\atlanta\wording
MON		= \src\atlanta\mon
MAKE	= \src\atlanta\make
SRC		= \src\atlanta\src
DEFINE	= \src\atlanta\define
DEFV	= \src\atlanta\def_v
EXTV	= \src\atlanta\ext_v
#
CC		= shc
ASM		= asmsh

!if ("$(MODEL)" == "ANZU_L") || ("$(MODEL)" == "ANZU_V")
OPTION	= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=0  /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
#!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLAR_L")
#!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLAR_L") || ("$(MODEL)" == "POPLAR_N")
!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLR_BN") || ("$(MODEL)" == "POPLAR_L") || ("$(MODEL)" == "POPLAR_N")
!if ("$(COUNTRY)" == "JPN") || ("$(COUNTRY)" == "JP1")
OPTION	= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=1 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!else
OPTION	= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
#OPTION_ND	= /op=1 /size      /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
!endif
!if ("$(MODEL)" == "POPLAR_H")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=1 /size      /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

!if ("$(MODEL)" == "SAKAKI")
OPTION		= /op=0 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=1 /size      /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI2") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU")) || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
!if ("$(COUNTRY)" == "JPN")
#最適化します 1999/01/24
OPTION		= /op=1 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=1 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!else
#クラス１入れたらＲＯＭが溢れたので最適化します by H.Hirao 1999/01/13
OPTION		= /op=1 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=1 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
!endif

ASM_OPT	= /cpu=sh2 /debug /object=$*.obj
LNK		= lnk /subcommand=\src\atlanta\make\lst.sub
OBJECT	= \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-----------------------------------------------------------------------------
#	ﾘｽﾄﾓｼﾞｭｰﾙのﾘﾝｸを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\lst.lnk:	\src\atlanta\make\lst.sub \
			$(OBJECT)\lst_main.obj	\
			$(OBJECT)\lst_batb.obj	\
			$(OBJECT)\lst_batd.obj	\
			$(OBJECT)\lst_dmry.obj	\
			$(OBJECT)\lst_fnc.obj	\
			$(OBJECT)\lst_jnl.obj	\
			$(OBJECT)\lst_prg.obj	\
			$(OBJECT)\lst_spd.obj	\
			$(OBJECT)\lst_tch.obj	\
			$(OBJECT)\lst_tx.obj	\
			$(OBJECT)\lst_cmd.obj	\
			$(OBJECT)\lst_cvr.obj	\
			$(OBJECT)\lst_dcmd.obj	\
			$(OBJECT)\lst_dpol.obj	\
			$(OBJECT)\lst_dscr.obj	\
			$(OBJECT)\lst_grp.obj	\
			$(OBJECT)\lst_msga.obj	\
			$(OBJECT)\lst_msgb.obj	\
			$(OBJECT)\lst_msgc.obj	\
			$(OBJECT)\lst_msge.obj	\
			$(OBJECT)\lst_msw.obj	\
			$(OBJECT)\lst_pdwn.obj	\
			$(OBJECT)\lst_rcr.obj	\
			$(OBJECT)\lst_rscr.obj	\
			$(OBJECT)\lst_scr.obj	\
			$(OBJECT)\lst_tcr.obj	\
			$(OBJECT)\lst_t30.obj	\
			$(OBJECT)\lst_name.obj	\
			$(OBJECT)\lst_date.obj	\
			$(OBJECT)\lst_prn.obj	\
			$(OBJECT)\lst_prm.obj	\
			$(OBJECT)\LST_D56.obj	\
			$(OBJECT)\LST_IMG.obj	\
			$(OBJECT)\lst_code.obj	\
			$(OBJECT)\lst_cost.obj	\
#			$(OBJECT)\lst_dbat.obj	\
#不要 By H.Hirao Mar.05,1996			$(OBJECT)\lst_mltp.obj	\
#			$(OBJECT)\lst_msgh.obj	\
#不要 By H.Hirao Mar.05,1996			$(OBJECT)\lst_ctx.obj	\
#不要 By H.Hirao Mar.05,1996			$(OBJECT)\lst_msgf.obj	\
#未使用			$(OBJECT)\lst_str.obj	\
#不要 By H.Hirao Mar.05,1996			$(OBJECT)\lst_tti.obj	\
#不要 By H.Hirao Mar.08,1996			$(OBJECT)\lst_jrnl.obj	\
#不要		$(OBJECT)\LST_PTN.obj	\
#工場ファンクションメニュー追加 By H.Hirao Mar.28.1996
			$(OBJECT)\LST_FRY.obj	\
#Add By H.Hirao 1996/06/27
			$(OBJECT)\lst_msgs.obj	\
#Add By H.Hirao 1996/08/21
			$(OBJECT)\lst_cl1.obj	\
#Add By 1997/03/13  By T.Yamaguchi
            $(OBJECT)\lst_r288.obj	\
#Add By 1997/04/16  By M.Kuwahara
            $(OBJECT)\lst_box.obj	\
#Add By 1997/04/18  By M.Kuwahara
            $(OBJECT)\lst_ddoc.obj	\
#Add By 1997/04/18  By M.Kuwahara
            $(OBJECT)\lst_fcdd.obj	\
#Add By 1997/04/20  By M.Kuwahara
            $(OBJECT)\lst_rx.obj	\
#Add By 1997/05/13  By M.Kuwahara
            $(OBJECT)\lst_junk.obj	\
#Add By 1997/05/20  By M.Kuwahara
            $(OBJECT)\lst_serv.obj	\
#Add By 1997/06/12  By M.Kuwahara
            $(OBJECT)\lst_cph.obj	\
#Add By 1997/06/13  By M.Kuwahara
            $(OBJECT)\lst_keyb.obj	\
            $(OBJECT)\lst_key.obj	\
#Add By 1997/09/19  By M.Kuwahara
            $(OBJECT)\lst_ord.obj	\
#Add By 1997/11/21  By M.Kuwahara
            $(OBJECT)\lst_dcph.obj	\
#Add By 1998/07/01  By M.Kuwahara
            $(OBJECT)\lst_nd.obj	\
            $(OBJECT)\lst_warp.obj	\
            $(OBJECT)\lst_mcr.obj	\
#Add By 1998/10/01  By M.Kuwahara
            $(OBJECT)\lst_ndj.obj	\
#Add By 2002/08/22  By M.Maeda
            $(OBJECT)\lst_crl.obj	
		$(LNK)

#-----------------------------------------------------------------------------
#	ﾘｽﾄﾓｼﾞｭｰﾙのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
$(OBJECT)\lst_batb.obj:	$(SRC)\lst_batb.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
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
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\opr\ank\define\opr_def.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_batb.c
#
$(OBJECT)\lst_batd.obj:	$(SRC)\lst_batd.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\opr\ank\define\opr_def.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_batd.c
#
$(OBJECT)\lst_code.obj:	$(SRC)\lst_code.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
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
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_code.c
#
$(OBJECT)\lst_cost.obj:	$(SRC)\lst_cost.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\ext_v\bkupram.h		\
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
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\define\sysmax.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_cost.c
#
$(OBJECT)\lst_dbat.obj:	$(SRC)\lst_dbat.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\opr\ank\define\opr_def.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_dbat.c
#
$(OBJECT)\lst_dmry.obj:	$(SRC)\lst_dmry.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
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
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\define\stng_pro.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_dmry.c
#
$(OBJECT)\lst_fnc.obj:	$(SRC)\lst_fnc.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\ext_v\rom_tbl.h		\
				\src\atlanta\define\keycode.h		\
				\src\atlanta\define\ctry_pro.h		\
					\src\atlanta\define\ncu_def.h		\
				\src\atlanta\define\MNT_SW.H		\
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
				\src\atlanta\opr\ank\define\opr_def.h		\
				\src\atlanta\opr\ank\ext_v\opr_tbl.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_fnc.c
#		$(CC)	$(OPTION) $(SRC)\lst_fnc.c
#
$(OBJECT)\lst_jnl.obj:	$(SRC)\lst_jnl.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\sysmax.h		\
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
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\lst_wrd.h
#		$(CC)	$(OPTION_ND) $(SRC)\lst_jnl.c
		$(CC)	$(OPTION) $(SRC)\lst_jnl.c
#
$(OBJECT)\lst_mltp.obj:	$(SRC)\lst_mltp.c
		$(CC)	$(OPTION_ND) $(SRC)\lst_mltp.c
#
$(OBJECT)\lst_msgh.obj:	$(SRC)\lst_msgh.c
		$(CC)	$(OPTION_ND) $(SRC)\lst_msgh.c
#
$(OBJECT)\lst_prg.obj:	$(SRC)\lst_prg.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h
                $(CC)   $(OPTION_ND) $(SRC)\lst_prg.c
#
$(OBJECT)\lst_prm.obj:	$(SRC)\lst_prm.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\ctry_pro.h		\
					\src\atlanta\define\ncu_def.h		\
						\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\lst_def.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\mlt_pro.h		\
				\src\atlanta\define\uni_pro.h		\
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
					\src\atlanta\define\sysmemrx.h		\
					\src\atlanta\define\syscost.h		\
					\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysdeprt.h		\
					\src\atlanta\define\systbok.h		\
					\src\atlanta\define\sysopspd.h		\
					\src\atlanta\define\sysringm.h		\
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_tbl.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\ext_v\rom_tbl.h		\
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h		\
				\src\atlanta\opr\ank\ext_v\opr_tbl.h		\
					\src\atlanta\define\keycode.h		\
					\src\atlanta\opr\ank\define\opr_def.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_prm.c
#		$(CC)	$(OPTION) $(SRC)\lst_prm.c
#
$(OBJECT)\lst_spd.obj:	$(SRC)\lst_spd.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
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
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\ext_v\rom_tbl.h		\
				\src\atlanta\opr\ank\define\opr_def.h
#		$(CC)	$(OPTION_ND) $(SRC)\lst_spd.c
		$(CC)	$(OPTION) $(SRC)\lst_spd.c
#
$(OBJECT)\lst_tch.obj:	$(SRC)\lst_tch.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
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
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h
#		$(CC)	$(OPTION_ND) $(SRC)\lst_tch.c
		$(CC)	$(OPTION) $(SRC)\lst_tch.c
#
#1994/06/08 キャラクタ送信イメージ展開 石橋正和
$(OBJECT)\lst_tx.obj:		$(SRC)\lst_tx.c		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mem_def.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\ext_v\lst_data.h		\
					\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
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
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\message.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\mlt_data.h
	$(CC) $(OPTION_ND)	$(SRC)\lst_tx.c
#
# リストプリントイメージ展開 石橋正和
$(OBJECT)\lst_prn.obj:	$(SRC)\lst_prn.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\lst_def.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\ext_v\lst_tbl.h		\
				\src\atlanta\ext_v\lst_data.h		\
					\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\opr\ank\define\opr_def.h		\
					\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysonet.h		\
				\src\atlanta\opr\ank\define\opr_pro.h		\
					\src\atlanta\define\sysspeed.h
	$(CC) $(OPTION)	$(SRC)\lst_prn.c
#
#1994/3/30
$(OBJECT)\lst_cmd.obj:	$(SRC)\lst_cmd.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h
		$(CC)	$(OPTION) $(SRC)\lst_cmd.c
#
$(OBJECT)\lst_ctx.obj:	$(SRC)\lst_ctx.c
		$(CC)	$(OPTION_ND) $(SRC)\lst_ctx.c
#
$(OBJECT)\lst_cvr.obj:	$(SRC)\lst_cvr.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h
		$(CC)	$(OPTION) $(SRC)\lst_cvr.c
#		$(CC)	$(OPTION_ND) $(SRC)\lst_cvr.c # H.Kubo 1998/08/18
#
$(OBJECT)\lst_date.obj:	$(SRC)\lst_date.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\wording.h		\
				\src\atlanta\define\fcm_pro.h		\
				\src\atlanta\ext_v\lst_data.h		\
					\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\ext_v\lst_tbl.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\SYSMAX.h		\
					\src\atlanta\define\sysbatch.h		\
						\src\atlanta\define\sysdial.h		\
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
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\memsw\define\mems_pro.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\atlanta\opr\ank\define\opr_def.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_date.c
#
$(OBJECT)\lst_dcmd.obj:	$(SRC)\lst_dcmd.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\syscntpl.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_dcmd.c
#
$(OBJECT)\lst_dpol.obj:	$(SRC)\lst_dpol.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_pdwn.h		\
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
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_dpol.c
#
$(OBJECT)\lst_dscr.obj:	$(SRC)\lst_dscr.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\ext_v\bkupram.h		\
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
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\opr\ank\define\opr_def.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_dscr.c
#
$(OBJECT)\lst_grp.obj:	$(SRC)\lst_grp.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysspeed.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sysonep.h		\
					\src\atlanta\define\sysonet.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysbatch.h		\
						\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\syscomf.h		\
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
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\opr\ank\define\opr_def.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_grp.c
#
$(OBJECT)\lst_msga.obj:	$(SRC)\lst_msga.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\lst_data.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_msga.c
#
$(OBJECT)\lst_msgb.obj:	$(SRC)\lst_msgb.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
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
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\syscomf.h		\
				\src\atlanta\opr\ank\define\opr_def.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_msgb.c
#
$(OBJECT)\lst_msgc.obj:	$(SRC)\lst_msgc.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
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
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\lst_wrd.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_msgc.c
#
$(OBJECT)\lst_msge.obj:	$(SRC)\lst_msge.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
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
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\mem_def.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_msge.c
#
$(OBJECT)\lst_msgf.obj:	$(SRC)\lst_msgf.c
		$(CC)	$(OPTION_ND) $(SRC)\lst_msgf.c
#
$(OBJECT)\lst_msw.obj:	$(SRC)\lst_msw.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\param.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\ext_v\atd_tbl.h		\
				\src\atlanta\ext_v\bkupram.h		\
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
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\cmn_tbl.h		\
					\src\atlanta\define\country.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\ext_v\ini_tbl.h		\
					\src\atlanta\define\status.h		\
				\src\atlanta\define\unisw_g.h		\
				\src\atlanta\define\mntsw_a.h		\
					\src\atlanta\define\mem_def.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_msw.c
#
$(OBJECT)\lst_name.obj:	$(SRC)\lst_name.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\mem_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysdoc.h		\
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
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_tbl.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\opr\ank\define\opr_def.h		\
				\src\atlanta\opr\ank\define\opr_pro.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_name.c
#
$(OBJECT)\lst_pdwn.obj:	$(SRC)\lst_pdwn.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\sys_pdwn.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mem_pro.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\define\syscntpl.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_pdwn.c
#
#lst_ptn.obj:	$(SRC)\lst_ptn.c	\
#		$(CC)	$(OPTION_ND) $(SRC)\lst_ptn.c
#
$(OBJECT)\lst_rcr.obj:	$(SRC)\lst_rcr.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\message.h		\
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
						\src\atlanta\define\ncu_cnst.h		\
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_rcr.c
#
$(OBJECT)\lst_rscr.obj:	$(SRC)\lst_rscr.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\opr\ank\define\opr_def.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_rscr.c
#
$(OBJECT)\lst_scr.obj:	$(SRC)\lst_scr.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysbatch.h		\
						\src\atlanta\define\sysdial.h		\
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
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\opr\ank\define\opr_def.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_scr.c
#
$(OBJECT)\lst_str.obj:	$(SRC)\lst_str.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_str.c
#
$(OBJECT)\lst_tcr.obj:	$(SRC)\lst_tcr.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
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
						\src\atlanta\define\ncu_cnst.h		\
					\src\atlanta\define\syscntpl.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\ext_v\fcm_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\opr\ank\define\opr_def.h
		$(CC)	$(OPTION_ND) $(SRC)\lst_tcr.c
#
$(OBJECT)\lst_tti.obj:	$(SRC)\lst_tti.c
		$(CC)	$(OPTION_ND) $(SRC)\lst_tti.c
#
$(OBJECT)\lst_t30.obj:	$(SRC)\lst_t30.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mntsw_a.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\stng_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\syst30.h		\
				\src\atlanta\define\sysjrnl.h		\
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
					\src\atlanta\define\message.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\mem_data.h		\
				\src\atlanta\ext_v\rom_tbl.h		\
				\src\atlanta\ext_v\lst_tbl.h		\
					\src\atlanta\define\dma_def.h		\
						\src\atlanta\sh7043\define\sh_port.h		\
					\src\atlanta\define\dma_pro.h		\
				\src\atlanta\sh7043\define\def_mon.h		\
				\src\atlanta\sh7043\ext_v\extv_mon.h		\
					\src\atlanta\sh7043\define\def_tcb.h		\
					\src\atlanta\sh7043\define\def_scb.h		\
					\src\atlanta\sh7043\define\def_tib.h
#		$(CC)	$(OPTION) $(SRC)\lst_t30.c
!if ("$(MODEL)" == "SAKAKI")
		$(CC)	$(OPTION) $(SRC)\lst_t30.c
!else
		$(CC)	$(OPTION_ND) $(SRC)\lst_t30.c
!endif
#
$(OBJECT)\lst_main.obj:	$(SRC)\lst_main.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\lst_def.h		\
				\src\atlanta\ext_v\lst_data.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\timer10.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
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
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\sh7043\ext_v\extv_mbx.h		\
					\src\atlanta\sh7043\define\def_mbxn.h		\
					\src\atlanta\define\mem_def.h
		$(CC)	$(OPTION) $(SRC)\lst_main.c
#
$(OBJECT)\lst_jrnl.obj:	$(SRC)\lst_jrnl.c
		$(CC)	$(OPTION_ND) $(SRC)\lst_jrnl.c
#
$(OBJECT)\lst_img.obj:	$(SRC)\lst_img.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\ext_v\lst_data.h		\
					\src\atlanta\define\sysjrnl.h		\
						\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysmcopy.h		\
					\src\atlanta\define\sysmemrx.h		\
					\src\atlanta\define\mem_def.h
#		$(CC) $(OPTION_ND) $(SRC)\lst_img.c
		$(CC) $(OPTION) $(SRC)\lst_img.c
#
#V53依存部から共通へ変更 By S.Kawasaki 1996/03/06
$(OBJECT)\lst_d56.obj:	$(SRC)\lst_d56.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\mntsw_c.h		\
				\src\atlanta\define\lst_def.h		\
				\src\atlanta\define\dma_def.h		\
					\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\define\dma_blk.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\cdc_pro.h		\
				\src\atlanta\ext_v\dma_data.h		\
				\src\atlanta\ext_v\lst_data.h		\
					\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\ext_v\cdc_data.h		\
					\src\atlanta\define\cdc_blk.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
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
				\src\atlanta\sh7043\define\def_tib.h		\
				\src\atlanta\sh7043\define\def_evtn.h		\
					\src\atlanta\define\mem_def.h
		$(CC) $(OPTION) $(SRC)\lst_d56.c
#
#工場ファンクションメニュー追加 By H.Hirao Mar.28.1996
$(OBJECT)\lst_fry.obj:	$(SRC)\lst_fry.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\ext_v\lst_data.h		\
					\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysscan.h
		$(CC) $(OPTION_ND) $(SRC)\lst_fry.c
#
# Add By H.Hirao 1996/06/27
$(OBJECT)\lst_msgs.obj:	$(SRC)\lst_msgs.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
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
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysfcode.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h
		$(CC) $(OPTION_ND) $(SRC)\lst_msgs.c
#
# Add By H.Hirao 1996/08/21
$(OBJECT)\lst_cl1.obj:	$(SRC)\lst_cl1.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\fcm_def.h		\
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
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\ext_v\rom_tbl.h		\
				\src\atlanta\ext_v\lst_tbl.h
		$(CC) $(OPTION_ND) $(SRC)\lst_cl1.c
#
# Add By M.Kuwahara 1997/04/16
$(OBJECT)\lst_box.obj:	$(SRC)\lst_box.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
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
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h
		$(CC) $(OPTION_ND) $(SRC)\lst_box.c
#
# Add By M.Kuwahara 1997/04/16
$(OBJECT)\lst_ddoc.obj:	$(SRC)\lst_ddoc.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
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
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h
		$(CC) $(OPTION_ND) $(SRC)\lst_ddoc.c
#
# Add By M.Kuwahara 1997/04/18
$(OBJECT)\lst_fcdd.obj:	$(SRC)\lst_fcdd.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
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
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h
		$(CC) $(OPTION_ND) $(SRC)\lst_fcdd.c
#
# Add By M.Kuwahara 1997/04/20
$(OBJECT)\lst_rx.obj:	$(SRC)\lst_rx.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
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
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h
		$(CC) $(OPTION_ND) $(SRC)\lst_rx.c
#
# Add By M.Kuwahara 1997/04/20
$(OBJECT)\lst_junk.obj:	$(SRC)\lst_junk.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\ext_v\bkupram.h		\
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
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h
		$(CC) $(OPTION_ND) $(SRC)\lst_junk.c
#
# Add By M.Kuwahara 1997/05/20
$(OBJECT)\lst_serv.obj:	$(SRC)\lst_serv.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
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
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\rom_tbl.h		\
				\src\atlanta\ext_v\lst_data.h		\
				\src\atlanta\ext_v\lst_wrd.h
		$(CC) $(OPTION_ND) $(SRC)\lst_serv.c
#
# Add By M.Kuwahara 1997/06/12
$(OBJECT)\lst_cph.obj:	$(SRC)\lst_cph.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\ext_v\bkupram.h		\
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
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\lst_data.h		\
					\src\atlanta\define\sys_opt.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
#				\src\atlanta\define\sysciph.h		\
				\src\atlanta\define\sysmax.h
		$(CC) $(OPTION_ND) $(SRC)\lst_cph.c
#
# Add By M.Kuwahara 1997/06/12
$(OBJECT)\lst_keyb.obj:	$(SRC)\lst_keyb.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\ext_v\bkupram.h		\
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
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\lst_data.h		\
					\src\atlanta\define\sys_opt.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\define\sysmax.h
		$(CC) $(OPTION_ND) $(SRC)\lst_keyb.c
#
# Add By M.Kuwahara 1997/06/12
$(OBJECT)\lst_key.obj:	$(SRC)\lst_key.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\ext_v\bkupram.h		\
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
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\lst_data.h		\
					\src\atlanta\define\sys_opt.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\define\sysmax.h
		$(CC) $(OPTION_ND) $(SRC)\lst_key.c
#
# Add By M.Kuwahara 1997/09/19
$(OBJECT)\lst_ord.obj:	$(SRC)\lst_ord.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\ext_v\bkupram.h		\
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
				\src\atlanta\ext_v\lst_data.h		\
					\src\atlanta\define\sys_opt.h		\
				\src\atlanta\ext_v\lst_wrd.h		\
				\src\atlanta\ext_v\rom_tbl.h
		$(CC) $(OPTION) $(SRC)\lst_ord.c

# Add By M.Kuwahara 1997//21
$(OBJECT)\lst_dcph.obj:	$(SRC)\lst_dcph.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_pdwn.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\lst_pro.h		\
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
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\lst_data.h		\
					\src\atlanta\define\sys_opt.h		\
				\src\atlanta\ext_v\lst_wrd.h
		$(CC) $(OPTION) $(SRC)\lst_dcph.c
# Add By M.Kuwahara 1998/07/01
$(OBJECT)\lst_nd.obj:	$(SRC)\lst_nd.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
							\src\atlanta\define\mem_def.h		\
							\src\atlanta\define\dma_blk.h
		$(CC) $(OPTION) $(SRC)\lst_nd.c
# Add By M.Kuwahara 1998/07/01
$(OBJECT)\lst_warp.obj:	$(SRC)\lst_warp.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
							\src\atlanta\define\mem_def.h		\
							\src\atlanta\define\dma_blk.h
		$(CC) $(OPTION) $(SRC)\lst_warp.c
# Add By M.Kuwahara 1998/07/01
$(OBJECT)\lst_mcr.obj:	$(SRC)\lst_mcr.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysmailb.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
							\src\atlanta\define\mem_def.h		\
							\src\atlanta\define\dma_blk.h
		$(CC) $(OPTION_ND) $(SRC)\lst_mcr.c
# Add By M.Kuwahara 1998/10/01
$(OBJECT)\lst_ndj.obj:	$(SRC)\lst_ndj.c
		$(CC) $(OPTION) $(SRC)\lst_ndj.c
# Add By M.Maeda 2002/08/22
$(OBJECT)\lst_crl.obj:	$(SRC)\lst_crl.c
		$(CC) $(OPTION) $(SRC)\lst_crl.c

#
#1997/03/13  By T.Yamaguchi
#-----------------------------------------------------------------------------
#   オプションボード用Ｒ２８８Ｆモデムステータスモニターファイルメイク部
# 本来はLST.MKに記述するべきところですが、メイクファイル共通化が困難な為
# ここに入れておきます。　尚、セグメントはLST.mkと一緒です。 By O.Kimoto 1996/12/20
#-----------------------------------------------------------------------------
$(OBJECT)\lst_r288.obj:	$(SRC)\lst_r288.c
		$(CC) $(OPTION_ND) $(SRC)\lst_r288.c
#
