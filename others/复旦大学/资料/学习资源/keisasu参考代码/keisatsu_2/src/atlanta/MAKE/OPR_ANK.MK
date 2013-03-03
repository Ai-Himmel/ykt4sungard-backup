#------------------------------------------------------------------------
#	POPLAR_B/POPLAR_L/ANZU_L	オペレーション部のメイクファイル
#	1996/10/16		Transplanted from \src\kobe\anzu\make By K.Watanabe
#------------------------------------------------------------------------
SRC			= \src\atlanta\opr\ank\src
OPRDEFV		= \src\atlanta\opr\ank\def_v

#-----------------------------------------------------------------------------
#	コマンド名を定義
#-----------------------------------------------------------------------------
CC			= shc
ASM			= asmsh
LNK			= lnk /subcommand=\src\atlanta\make\opr_ank.sub

#-----------------------------------------------------------------------------
#	引数を定義
#-----------------------------------------------------------------------------
#!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLAR_N")
!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLR_BN") || ("$(MODEL)" == "POPLAR_N")
OPTION		= /op=0 /deb  /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=1 /deb /size /cp=sh2 /def=($(MODEL),$(COUNTRY))
!else
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI2") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU")) || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
#クラス１入れたらＲＯＭが溢れたので最適化します by H.Hirao 1999/01/13
#ＪＰＮも最適化します 1999/01/24
OPTION		= /op=1 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=1 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

S_OPTION	= /op=1 /deb /cp=$(CPU_OPT) /def=($(MODEL),$(COUNTRY),$(CPU))
ASM_OPT		= /cpu=sh2 /debug /object=$*.obj

#-----------------------------------------------------------------------------
#	オブジェクトディレクトリを定義
#-----------------------------------------------------------------------------
OBJECT		= \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-----------------------------------------------------------------------------
#	オペレーションモジュールのリンクを定義（ファイル名を昇順に記述）
#-----------------------------------------------------------------------------
$(OBJECT)\opr.lnk:	\src\atlanta\make\opr_ank.sub	\
			$(OBJECT)\opr_btx.obj	\
			$(OBJECT)\opr_ciph.obj	\
			$(OBJECT)\opr_cl1.obj	\
			$(OBJECT)\opr_com.obj	\
			$(OBJECT)\opr_copy.obj	\
			$(OBJECT)\opr_cpym.obj	\
			$(OBJECT)\opr_dial.obj	\
			$(OBJECT)\opr_disp.obj	\
			$(OBJECT)\opr_dpt.obj	\
			$(OBJECT)\opr_fcod.obj	\
			$(OBJECT)\opr_flsh.obj	\
			$(OBJECT)\opr_fnc.obj	\
			$(OBJECT)\opr_fncs.obj	\
			$(OBJECT)\opr_inst.obj	\
			$(OBJECT)\opr_int.obj	\
			$(OBJECT)\opr_key.obj	\
			$(OBJECT)\opr_lcd.obj	\
			$(OBJECT)\opr_mer.obj	\
			$(OBJECT)\opr_name.obj	\
			$(OBJECT)\opr_num.obj	\
			$(OBJECT)\opr_okey.obj	\
			$(OBJECT)\opr_one.obj	\
			$(OBJECT)\opr_pol.obj	\
			$(OBJECT)\opr_prg.obj	\
			$(OBJECT)\opr_prm.obj	\
			$(OBJECT)\opr_prn.obj	\
			$(OBJECT)\opr_ram.obj	\
			$(OBJECT)\opr_rsv.obj	\
			$(OBJECT)\opr_scur.obj	\
			$(OBJECT)\opr_serv.obj	\
			$(OBJECT)\opr_sett.obj	\
			$(OBJECT)\opr_spd.obj	\
			$(OBJECT)\opr_spe.obj	\
			$(OBJECT)\opr_sub.obj	\
			$(OBJECT)\opr_tbok.obj	\
			$(OBJECT)\opr_tel.obj	\
			$(OBJECT)\opr_top.obj	\
#	/* Add By H.Fujimura 1998/10/07 */
			$(OBJECT)\opr_nd.obj	\
#	/* Add By H.Fujimura 1998/10/07 */
			$(OBJECT)\opr_warp.obj	\
			$(OBJECT)\ntt_disp.obj	\
#	ＨＩＮＯＫＩ３でメイク通らないので条件文は外します
#!if ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
#	/* add by Y.Kano 2003/08/27 */
			$(OBJECT)\opr_vol.obj	\
#	/* add by Y.Kano 2003/09/04 */
			$(OBJECT)\opr_char.obj	\
#	/* add by Y.Kano 2003/09/04 */
			$(OBJECT)\opr_chkr.obj	\
#	/* add by Y.Kano 2003/08/27 */
#!endif
			$(OBJECT)\key_tbl.obj	\
			$(OBJECT)\opr_tbl.obj	\
			$(OBJECT)\opr_data.obj
			
		$(LNK)

#-----------------------------------------------------------------------------
#       オペレーションモジュールのメイクファイル部
#-----------------------------------------------------------------------------
$(OBJECT)\opr_btx.obj:  $(SRC)\opr_btx.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\mem_def.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sysbatch.h          \
				\src\atlanta\define\syscomf.h           \
				\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\sysmax.h            \
				\src\atlanta\define\sysonet.h           \
				\src\atlanta\define\sysspeed.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\mem_pro.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_btx.c
#
$(OBJECT)\opr_ciph.obj: $(SRC)\opr_ciph.c       \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\mem_def.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysdoc.h            \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
					\src\atlanta\define\sysmcopy.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\syskey.h            \
					\src\atlanta\define\syscph.h            \
					\src\atlanta\define\dpr_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\message.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sys_opt.h           \
					\src\atlanta\define\sysdisp.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
					\src\atlanta\define\keycode.h           \
						\src\atlanta\opr\ank\define\keycode.h           \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_ciph.c
#
$(OBJECT)\opr_cl1.obj:  $(SRC)\opr_cl1.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\cmn_def.h           \
				\src\atlanta\define\fcm_def.h           \
				\src\atlanta\define\param.h             \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\sysdoc.h            \
				\src\atlanta\define\syslocal.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\ctry_pro.h          \
					\src\atlanta\define\ncu_def.h           \
						\src\atlanta\define\ncu_cnst.h          \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC) $(OPTION_ND) $(SRC)\opr_cl1.c
#
$(OBJECT)\opr_com.obj:  $(SRC)\opr_com.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\cmn_def.h           \
				\src\atlanta\define\fcm_def.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysdial.h           \
				\src\atlanta\define\syslocal.h          \
				\src\atlanta\define\sysonet.h           \
				\src\atlanta\define\sysscan.h           \
				\src\atlanta\define\sysspeed.h          \
					\src\atlanta\define\sysmax.h            \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\ctry_pro.h          \
					\src\atlanta\define\ncu_def.h           \
						\src\atlanta\define\ncu_cnst.h          \
				\src\atlanta\define\mem_pro.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\fip_def.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h
#		$(CC) $(OPTION) $(SRC)\opr_com.c
		$(CC) $(OPTION_ND) $(SRC)\opr_com.c
#
$(OBJECT)\opr_copy.obj: $(SRC)\opr_copy.c       \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\sysdoc.h            \
				\src\atlanta\define\sysmcopy.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC) $(OPTION_ND) $(SRC)\opr_copy.c
#
$(OBJECT)\opr_cpym.obj: $(SRC)\opr_cpym.c       \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\sysdoc.h            \
				\src\atlanta\define\sysmcopy.h          \
				\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h           \
				\src\atlanta\sh7043\define\io_pro.h
		$(CC) $(OPTION_ND) $(SRC)\opr_cpym.c
#
$(OBJECT)\opr_dial.obj: $(SRC)\opr_dial.c       \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\country.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\param.h             \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\syscomf.h           \
						\src\atlanta\define\sysdial.h           \
				\src\atlanta\define\sysspeed.h          \
					\src\atlanta\define\sysmax.h            \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\time.h              \
				\src\memsw\define\mem_sw_b.h            \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\cmn_tbl.h            \
				\src\atlanta\ext_v\ini_tbl.h            \
					\src\atlanta\define\status.h            \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_dial.c
#
$(OBJECT)\opr_disp.obj: $(SRC)\opr_disp.c       \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\fcm_def.h           \
				\src\atlanta\define\mntsw_a.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\sysdoc.h            \
				\src\atlanta\define\sysprint.h          \
				\src\atlanta\define\sysrxsw.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\lst_pro.h           \
				\src\atlanta\define\mem_pro.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\fcm_data.h           \
					\src\atlanta\define\message.h           \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\lst_wrd.h            \
					\src\atlanta\define\lst_def.h           \
				\src\atlanta\ext_v\man_data.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
						\src\atlanta\define\dma_def.h           \
							\src\atlanta\sh7043\define\sh_port.h            \
						\src\atlanta\define\dma_pro.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\sysmcopy.h          \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
					\src\atlanta\define\keycode.h           \
					\src\atlanta\ext_v\bkupram.h            \
						\src\atlanta\define\sysmailb.h          \
						\src\atlanta\define\sysexec.h           \
						\src\atlanta\define\syslifem.h          \
						\src\atlanta\define\sysshad.h           \
						\src\atlanta\define\sysdiali.h          \
						\src\atlanta\define\sysmemrx.h          \
						\src\atlanta\define\syscost.h           \
						\src\atlanta\define\syst30.h            \
						\src\atlanta\define\sysdeprt.h          \
						\src\atlanta\define\systbok.h           \
						\src\atlanta\define\sysopspd.h          \
						\src\atlanta\define\sysringm.h          \
							\src\atlanta\define\ncu_cnst.h          \
						\src\atlanta\define\syscntpl.h          \
						\src\atlanta\define\sysfcode.h          \
						\src\atlanta\define\syspcrx.h           \
						\src\atlanta\define\dpr_def.h           \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION) $(SRC)\opr_disp.c
#
$(OBJECT)\opr_dpt.obj:  $(SRC)\opr_dpt.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sysbatch.h          \
				\src\atlanta\define\syscomf.h           \
				\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\sysmax.h            \
				\src\atlanta\define\sysonet.h           \
				\src\atlanta\define\sysspeed.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\time.h              \
				\src\memsw\define\mem_sw_b.h            \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\ini_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_dpt.c
#
$(OBJECT)\opr_fcod.obj: $(SRC)\opr_fcod.c       \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\mem_def.h           \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\sysmax.h            \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysdoc.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\mem_pro.h           \
					\src\atlanta\ext_v\memertbl.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_fcod.c
#
$(OBJECT)\opr_flsh.obj: $(SRC)\opr_flsh.c       \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\timer10.h           \
					\src\atlanta\define\dma_def.h           \
						\src\atlanta\sh7043\define\sh_port.h            \
					\src\atlanta\define\dma_pro.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
						\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\sysdoc.h            \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\sh7043\define\def_tib.h            \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
					\src\atlanta\define\sysmcopy.h          \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h           \
				\src\atlanta\sh7043\ext_v\extv_sem.h            \
					\src\atlanta\sh7043\define\def_semn.h
		$(CC) $(OPTION) $(SRC)\opr_flsh.c
#
$(OBJECT)\opr_fnc.obj:  $(SRC)\opr_fnc.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
						\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\ctry_pro.h          \
					\src\atlanta\define\ncu_def.h           \
						\src\atlanta\define\ncu_cnst.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\ext_v\sys_data.h           \
				\src\atlanta\ext_v\ini_tbl.h
		$(CC) $(OPTION_ND) $(SRC)\opr_fnc.c
#
$(OBJECT)\opr_fncs.obj: $(SRC)\opr_fncs.c       \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\fcm_def.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\mem_def.h           \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysdial.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\ctry_pro.h          \
					\src\atlanta\define\ncu_def.h           \
						\src\atlanta\define\ncu_cnst.h          \
				\src\atlanta\define\man_pro.h           \
				\src\atlanta\define\mem_pro.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC) $(OPTION_ND) $(SRC)\opr_fncs.c
#
$(OBJECT)\opr_inst.obj: $(SRC)\opr_inst.c       \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\mem_def.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
					\src\atlanta\define\dma_def.h           \
						\src\atlanta\sh7043\define\sh_port.h            \
					\src\atlanta\define\dma_pro.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\man_pro.h           \
				\src\atlanta\define\mem_pro.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_sem.h            \
					\src\atlanta\sh7043\define\def_semn.h
		$(CC) $(OPTION_ND) $(SRC)\opr_inst.c
#
$(OBJECT)\opr_int.obj:  $(SRC)\opr_int.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysspeed.h          \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\opr\ank\ext_v\key_tbl.h            \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\sh7043\define\def_evtn.h           \
				\src\atlanta\sh7043\define\sh_port.h
		$(CC) $(OPTION) $(SRC)\opr_int.c
#
$(OBJECT)\opr_key.obj:  $(SRC)\opr_key.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\buzzer.h            \
					\src\atlanta\define\scn_def.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\message.h           \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\timer10.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\sh7043\define\def_evtn.h           \
				\src\atlanta\sh7043\define\def_tib.h            \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\opr\ank\ext_v\key_tbl.h            \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h           \
				\src\atlanta\sh7043\define\sh_port.h
		$(CC) $(OPTION) $(SRC)\opr_key.c
#
$(OBJECT)\opr_lcd.obj:  $(SRC)\opr_lcd.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\keycode.h           \
					\src\atlanta\define\dma_def.h           \
					\src\atlanta\define\dma_pro.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
						\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\sys_port.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\sh7043\ext_v\extv_sem.h            \
					\src\atlanta\sh7043\define\def_semn.h           \
				\src\atlanta\sh7043\define\sh_port.h
		$(CC) $(OPTION) $(SRC)\opr_lcd.c
#
$(OBJECT)\opr_mer.obj:  $(SRC)\opr_mer.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\cmn_def.h           \
				\src\atlanta\define\fcm_def.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\param.h             \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\sysdoc.h            \
				\src\atlanta\define\syslocal.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\ctry_pro.h          \
					\src\atlanta\define\ncu_def.h           \
						\src\atlanta\define\ncu_cnst.h          \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_mer.c
#
$(OBJECT)\opr_name.obj: $(SRC)\opr_name.c       \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\cmn_def.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
						\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
					\src\atlanta\define\sysmcopy.h          \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
					\src\atlanta\ext_v\bkupram.h            \
						\src\atlanta\define\sysbatch.h          \
						\src\atlanta\define\sysmailb.h          \
						\src\atlanta\define\sysjrnl.h           \
						\src\atlanta\define\sysexec.h           \
						\src\atlanta\define\syslifem.h          \
						\src\atlanta\define\sysshad.h           \
						\src\atlanta\define\sysdiali.h          \
						\src\atlanta\define\sysmemrx.h          \
						\src\atlanta\define\syscost.h           \
						\src\atlanta\define\syst30.h            \
						\src\atlanta\define\sysdeprt.h          \
						\src\atlanta\define\systbok.h           \
						\src\atlanta\define\sysopspd.h          \
						\src\atlanta\define\sysringm.h          \
							\src\atlanta\define\ncu_cnst.h          \
						\src\atlanta\define\syscntpl.h          \
						\src\atlanta\define\sysfcode.h          \
						\src\atlanta\define\syspcrx.h           \
						\src\atlanta\define\dpr_def.h           \
							\src\atlanta\define\mem_def.h           \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_name.c
#
$(OBJECT)\opr_num.obj:  $(SRC)\opr_num.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysdial.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\ctry_pro.h          \
					\src\atlanta\define\ncu_def.h           \
						\src\atlanta\define\ncu_cnst.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_num.c
#
$(OBJECT)\opr_okey.obj: $(SRC)\opr_okey.c       \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\sysdoc.h            \
				\src\atlanta\define\syslocal.h          \
				\src\atlanta\define\sysrxsw.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\define\uni_pro.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_okey.c
#
$(OBJECT)\opr_one.obj:  $(SRC)\opr_one.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\syscomf.h           \
						\src\atlanta\define\sysdial.h           \
				\src\atlanta\define\sysspeed.h          \
					\src\atlanta\define\sysmax.h            \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\time.h              \
				\src\memsw\define\mem_sw_b.h            \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\ini_tbl.h            \
					\src\atlanta\define\status.h            \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_one.c
#
$(OBJECT)\opr_pol.obj:  $(SRC)\opr_pol.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\mem_def.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\ctry_pro.h          \
					\src\atlanta\define\ncu_def.h           \
						\src\atlanta\define\ncu_cnst.h          \
				\src\atlanta\define\mem_pro.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
					\src\atlanta\define\keycode.h           \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC) $(OPTION_ND) $(SRC)\opr_pol.c
#
$(OBJECT)\opr_prg.obj:  $(SRC)\opr_prg.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\cmn_def.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\sysspeed.h          \
					\src\atlanta\define\syscomf.h           \
						\src\atlanta\define\sysdial.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_prg.c
#
$(OBJECT)\opr_prm.obj:  $(SRC)\opr_prm.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\cmn_def.h           \
				\src\atlanta\define\fcm_def.h           \
				\src\atlanta\define\param.h             \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\sysdoc.h            \
				\src\atlanta\define\syslocal.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\ctry_pro.h          \
					\src\atlanta\define\ncu_def.h           \
						\src\atlanta\define\ncu_cnst.h          \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_prm.c
#
$(OBJECT)\opr_prn.obj:  $(SRC)\opr_prn.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sysbatch.h          \
				\src\atlanta\define\syscomf.h           \
				\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\sysmax.h            \
				\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\sysjrnl.h           \
				\src\atlanta\define\sysonet.h           \
				\src\atlanta\define\sysspeed.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\time.h              \
				\src\memsw\define\mem_sw_b.h            \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\ini_tbl.h            \
					\src\atlanta\define\status.h            \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC) $(OPTION_ND) $(SRC)\opr_prn.c
#
$(OBJECT)\opr_ram.obj:  $(SRC)\opr_ram.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\syslifem.h          \
				\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysmax.h            \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\sh7043\define\def_tib.h            \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\lst_pro.h           \
				\src\atlanta\define\man_pro.h           \
				\src\atlanta\define\mem_pro.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
				\src\atlanta\ext_v\mem_data.h           \
					\src\atlanta\define\MEM_DEF.H           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\ext_v\sys_port.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h           \
				\src\atlanta\sh7043\define\sh_port.h
		$(CC) $(OPTION) $(SRC)\opr_ram.c
#
$(OBJECT)\opr_rsv.obj:  $(SRC)\opr_rsv.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\fcm_def.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\mem_def.h           \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysdial.h           \
				\src\atlanta\define\syscomf.h           \
				\src\atlanta\define\sysexec.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\ctry_pro.h          \
					\src\atlanta\define\ncu_def.h           \
						\src\atlanta\define\ncu_cnst.h          \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC) $(OPTION_ND) $(SRC)\opr_rsv.c
#
$(OBJECT)\opr_scur.obj: $(SRC)\opr_scur.c       \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\mem_def.h           \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\sysmax.h            \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\mem_pro.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_scur.c
#
$(OBJECT)\opr_serv.obj: $(SRC)\opr_serv.c       \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\mntsw_a.h           \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\syslifem.h          \
				\src\atlanta\define\syslocal.h          \
				\src\atlanta\define\sysrxsw.h           \
				\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\dma_def.h           \
						\src\atlanta\sh7043\define\sh_port.h            \
					\src\atlanta\define\dma_pro.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\sh7043\define\def_tib.h            \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\lst_pro.h           \
				\src\atlanta\define\man_pro.h           \
				\src\atlanta\define\mem_pro.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
				\src\atlanta\ext_v\fcm_data.h           \
					\src\atlanta\define\message.h           \
					\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\mem_data.h           \
				\src\atlanta\ext_v\rom_tbl.h            \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\ext_v\sys_port.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h           \
				\src\atlanta\sh7043\define\io_pro.h             \
				\src\atlanta\sh7043\define\sh_sys.h
		$(CC) $(OPTION_ND) $(SRC)\opr_serv.c
#
$(OBJECT)\opr_sett.obj: $(SRC)\opr_sett.c       \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
						\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_sett.c
#
$(OBJECT)\opr_spd.obj:  $(SRC)\opr_spd.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\syscomf.h           \
						\src\atlanta\define\sysdial.h           \
				\src\atlanta\define\sysspeed.h          \
					\src\atlanta\define\sysmax.h            \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\time.h              \
				\src\memsw\define\mem_sw_b.h            \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\ini_tbl.h            \
					\src\atlanta\define\status.h            \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_spd.c
#
$(OBJECT)\opr_spe.obj:  $(SRC)\opr_spe.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysdial.h           \
				\src\atlanta\define\syscomf.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\ctry_pro.h          \
					\src\atlanta\define\ncu_def.h           \
						\src\atlanta\define\ncu_cnst.h          \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC) $(OPTION_ND) $(SRC)\opr_spe.c
#
$(OBJECT)\opr_sub.obj:  $(SRC)\opr_sub.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\lst_def.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysdial.h           \
				\src\atlanta\define\sysdoc.h            \
				\src\atlanta\define\sysexec.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\ctry_pro.h          \
					\src\atlanta\define\ncu_def.h           \
						\src\atlanta\define\ncu_cnst.h          \
				\src\atlanta\define\man_pro.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\lst_data.h           \
				\src\atlanta\ext_v\lst_wrd.h            \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h           \
				\src\atlanta\define\syscntpl.h          \
				\src\atlanta\define\scn_def.h           \
				\src\atlanta\ext_v\scn_data.h
		$(CC) $(OPTION) /l /sh=ob $(SRC)\opr_sub.c
#
$(OBJECT)\opr_tbok.obj: $(SRC)\opr_tbok.c       \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\cmn_def.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION_ND) $(SRC)\opr_tbok.c
#
$(OBJECT)\opr_tel.obj:  $(SRC)\opr_tel.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\cmn_def.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\ctry_pro.h          \
					\src\atlanta\define\ncu_def.h           \
						\src\atlanta\define\ncu_cnst.h          \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC) $(OPTION_ND) $(SRC)\opr_tel.c
#
$(OBJECT)\opr_top.obj:  $(SRC)\opr_top.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\cmn_def.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\mem_def.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysdial.h           \
				\src\atlanta\define\sysprint.h          \
				\src\atlanta\define\sysrxsw.h           \
				\src\atlanta\define\mntsw_c.h           \
					\src\atlanta\define\dma_def.h           \
						\src\atlanta\sh7043\define\sh_port.h            \
					\src\atlanta\define\dma_pro.h           \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\sh7043\define\def_tib.h            \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
				\src\atlanta\ext_v\fcm_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
				\src\atlanta\opr\ank\ext_v\opr_tbl.h            \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h           \
				\src\atlanta\sh7043\ext_v\extv_sem.h            \
					\src\atlanta\sh7043\define\def_semn.h
		$(CC) $(OPTION_ND) $(SRC)\opr_top.c
#	/* Add By H.Fujimura 1998/10/07 */
$(OBJECT)\opr_nd.obj:  $(SRC)\opr_nd.c        \
				\src\atlanta\define\product.h				\
				\src\atlanta\define\apl_msg.h				\
				\src\atlanta\define\keycode.h				\
				\src\atlanta\define\std.h				\
				\src\atlanta\define\sysonet.h				\
				\src\atlanta\define\sysspeed.h				\
				\src\atlanta\opr\ank\define\opr_def.h				\
				\src\memsw\define\mem_sw_b.h				\
				\src\atlanta\define\cmn_pro.h				\
				\src\atlanta\define\fcm_pro.h				\
				\src\atlanta\define\uni_pro.h				\
				\src\atlanta\opr\ank\define\opr_pro.h				\
				\src\memsw\define\mems_pro.h				\
				\src\atlanta\ext_v\bkupram.h				\
				\src\atlanta\ext_v\ini_tbl.h				\
				\src\atlanta\opr\ank\ext_v\opr_data.h				\
				\src\atlanta\opr\ank\ext_v\opr_tbl.h				\
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h				\
				\src\atlanta\define\country.h				\
				\src\atlanta\define\param.h				\
				\src\atlanta\define\stng_pro.h				\
				\src\atlanta\ext_v\cmn_tbl.h
		$(CC) $(OPTION_ND) $(SRC)\opr_nd.c
#	/* Add By H.Fujimura 1998/10/07 */
$(OBJECT)\opr_warp.obj:  $(SRC)\opr_warp.c        \
				\src\atlanta\define\product.h				\
				\src\atlanta\define\apl_msg.h				\
				\src\atlanta\define\keycode.h				\
				\src\atlanta\define\std.h				\
				\src\atlanta\define\sysonet.h				\
				\src\atlanta\define\sysspeed.h				\
				\src\atlanta\opr\ank\define\opr_def.h				\
				\src\memsw\define\mem_sw_b.h				\
				\src\atlanta\define\cmn_pro.h				\
				\src\atlanta\define\fcm_pro.h				\
				\src\atlanta\define\uni_pro.h				\
				\src\atlanta\opr\ank\define\opr_pro.h				\
				\src\memsw\define\mems_pro.h				\
				\src\atlanta\ext_v\bkupram.h				\
				\src\atlanta\ext_v\ini_tbl.h				\
				\src\atlanta\opr\ank\ext_v\opr_data.h				\
				\src\atlanta\opr\ank\ext_v\opr_tbl.h				\
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h				\
				\src\atlanta\define\country.h				\
				\src\atlanta\define\param.h				\
				\src\atlanta\define\stng_pro.h				\
				\src\atlanta\ext_v\cmn_tbl.h
		$(CC) $(OPTION_ND) $(SRC)\opr_warp.c
#
$(OBJECT)\ntt_disp.obj: $(SRC)\ntt_disp.c       \
				\src\atlanta\define\product.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\mntsw_a.h		\
				\src\atlanta\define\mntsw_b.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\sysprint.h		\
				\src\atlanta\define\sysrxsw.h		\
				\src\atlanta\define\sysscan.h		\
				\src\atlanta\opr\ank\define\opr_def.h		\
					\src\atlanta\define\syscomf.h		\
						\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysonet.h		\
						\src\atlanta\define\sysspeed.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sys_infd.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
							\src\atlanta\define\dma_blk.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
												\src\atlanta\define\message.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
		$(CC) $(OPTION) $(SRC)\ntt_disp.c
#	/* Add by Y.Kano 2003/08/27 */
#!if ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")	# /* add by Y.Kano 2003/10/27 */
$(OBJECT)\opr_vol.obj:  $(SRC)\opr_vol.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\cmn_def.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\ctry_pro.h          \
					\src\atlanta\define\ncu_def.h           \
						\src\atlanta\define\ncu_cnst.h          \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC) $(OPTION_ND) $(SRC)\opr_vol.c
#
#	/* Add by Y.Kano 2003/09/04 */
$(OBJECT)\opr_char.obj:  $(SRC)\opr_char.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\cmn_def.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\ctry_pro.h          \
					\src\atlanta\define\ncu_def.h           \
						\src\atlanta\define\ncu_cnst.h          \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC) $(OPTION_ND) $(SRC)\opr_char.c
#
#	/* Add by Y.Kano 2003/09/11 */
$(OBJECT)\opr_chkr.obj:  $(SRC)\opr_chkr.c        \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\apl_msg.h           \
				\src\atlanta\define\cmn_def.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\sys_stat.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\define\cmn_pro.h           \
					\src\atlanta\define\timer10.h           \
					\src\atlanta\define\atd_def.h           \
				\src\atlanta\define\ctry_pro.h          \
					\src\atlanta\define\ncu_def.h           \
						\src\atlanta\define\ncu_cnst.h          \
				\src\atlanta\define\mon_pro.h           \
				\src\atlanta\define\stng_pro.h          \
				\src\atlanta\opr\ank\define\opr_pro.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\memsw\define\mems_pro.h            \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\sysfcode.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
				\src\atlanta\ext_v\sys_data.h           \
					\src\atlanta\define\sysdblk.h           \
					\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\fip_def.h           \
					\src\atlanta\define\sysscan.h           \
				\src\atlanta\opr\ank\ext_v\opr_data.h           \
					\src\atlanta\define\message.h           \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h           \
				\src\atlanta\sh7043\ext_v\extv_mbx.h            \
					\src\atlanta\sh7043\define\def_mbxn.h
		$(CC) $(OPTION) $(SRC)\opr_chkr.c
#!endif	# /* add by Y.Kano 2003/10/27 */
#
#-----------------------------------------------------------------------------
#       ＫＥＹテーブル
#-----------------------------------------------------------------------------
#/* OPR_ANKに移動 By O.Kimoto 1997/07/16 */
$(OBJECT)\key_tbl.obj:    $(OPRDEFV)\key_tbl.c  \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
						\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\sysmax.h            \
					\src\atlanta\define\sysonet.h           \
						\src\atlanta\define\sysspeed.h          \
					\src\atlanta\define\time.h              \
				\src\atlanta\sh7043\define\sh_port.h
		$(CC) $(OPTION_ND) $(OPRDEFV)\key_tbl.c
#
#-----------------------------------------------------------------------------
#       ＯＰＲテーブル
#-----------------------------------------------------------------------------
#/* OPR_ANKに移動 By O.Kimoto 1997/07/16 */
$(OBJECT)\opr_tbl.obj:    $(OPRDEFV)\opr_tbl.c  \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\keycode.h           \
				\src\atlanta\define\std.h               \
				\src\atlanta\define\status.h            \
				\src\atlanta\define\syscomf.h           \
					\src\atlanta\define\sysdial.h           \
				\src\atlanta\define\sysdoc.h            \
				\src\atlanta\define\sysmax.h            \
				\src\atlanta\define\sysonet.h           \
					\src\atlanta\define\sysspeed.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\time.h              \
				\src\atlanta\opr\ank\define\opr_pro.h           \
				\src\atlanta\ext_v\bkupram.h            \
					\src\atlanta\define\sysbatch.h          \
					\src\atlanta\define\sysmailb.h          \
					\src\atlanta\define\sysjrnl.h           \
					\src\atlanta\define\sysexec.h           \
					\src\atlanta\define\sysmcopy.h          \
					\src\atlanta\define\syslifem.h          \
					\src\atlanta\define\sysshad.h           \
					\src\atlanta\define\sysdiali.h          \
					\src\atlanta\define\sysmemrx.h          \
					\src\atlanta\define\syscost.h           \
					\src\atlanta\define\syst30.h            \
					\src\atlanta\define\sysdeprt.h          \
					\src\atlanta\define\systbok.h           \
					\src\atlanta\define\sysopspd.h          \
					\src\atlanta\define\sysringm.h          \
						\src\atlanta\define\ncu_cnst.h          \
					\src\atlanta\define\syscntpl.h          \
					\src\atlanta\define\syspcrx.h           \
					\src\atlanta\define\dpr_def.h           \
						\src\atlanta\define\mem_def.h           \
					\src\atlanta\define\sysfcode.h          \
				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
		$(CC) $(OPTION) $(OPRDEFV)\opr_tbl.c

#以下は各オペレーション用メークファイルに移動させます By O.Kimoto 1997/09/04
#-----------------------------------------------------------------------------
#  オペレーション用データ
#-----------------------------------------------------------------------------
$(OBJECT)\opr_data.obj:   $(OPRDEFV)\opr_data.c \
				\src\atlanta\define\product.h           \
				\src\atlanta\define\message.h           \
				\src\atlanta\define\sysmax.h            \
				\src\atlanta\define\sysmcopy.h          \
				\src\atlanta\opr\ank\define\opr_def.h           \
					\src\atlanta\define\syscomf.h           \
						\src\atlanta\define\sysdial.h           \
					\src\atlanta\define\sysonet.h           \
						\src\atlanta\define\sysspeed.h          \
					\src\atlanta\define\time.h
		$(CC) $(OPTION) $(OPRDEFV)\opr_data.c


