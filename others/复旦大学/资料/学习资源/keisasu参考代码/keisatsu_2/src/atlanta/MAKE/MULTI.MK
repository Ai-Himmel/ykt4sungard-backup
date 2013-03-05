#------------------------------------------------------------------------
#	POPLAR/ANZU_L	２回線部(MULTI)のメイクファイル
#	Nov.19.1996	 By T.Yamaguchi		Transplanted from \src\kobe\anzu\make
#------------------------------------------------------------------------
#
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
LNK			= lnk /subcommand=\src\atlanta\make\multi.sub
#-----------------------------------------------------------------------------
#	引数を定義
#-----------------------------------------------------------------------------
!if ("$(MODEL)" == "POPLAR_H") || ("$(MODEL)" == "SAKAKI")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
#OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!else
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
#!if ("$(MODEL)" == "POPLAR_B")
!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLR_BN")
!if ("$(COUNTRY)" == "JPN") || ("$(COUNTRY)" == "EUR")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif
!endif


ASM_OPT		= /cpu=$(CPU_OPT) /debug /object=$*.obj
#-----------------------------------------------------------------------------
#	オブジェクトディレクトリを定義
#-----------------------------------------------------------------------------
OBJECT		= \src\atlanta\$(MODEL)\work\$(COUNTRY)
#
#-----------------------------------------------------------------------------
#   ２回線ﾓｼﾞｭｰﾙのﾘﾝｸを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\multi.lnk:	\src\atlanta\make\multi.SUB	\
            $(OBJECT)\mlt_main.obj	\
            $(OBJECT)\mlt_sub.obj	\
            $(OBJECT)\mlt_poll.obj
#  lst_r288.obj	\
#  mlt_data.obj	\
#  mlt_tbl.obj
        $(LNK)
#-----------------------------------------------------------------------------
#   ﾒｲﾝﾓｼﾞｭｰﾙのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
$(OBJECT)\mlt_main.obj:   $(SRC)\mlt_main.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\sys_line.h		\
				\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\mlt_pro.h		\
				\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\message.h		\
				\src\atlanta\define\mem_pro.h		\
					\src\atlanta\ext_v\memertbl.h		\
				\src\atlanta\define\unisw_a.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\cmn_def.h		\
				\src\atlanta\sh7043\define\io_pro.h		\
				\src\atlanta\define\sysprint.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\sysscan.h		\
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
				\src\atlanta\ext_v\mlt_data.h		\
				\src\atlanta\ext_v\mlt_tbl.h		\
				\src\atlanta\ext_v\fcm_data.h
        $(CC)	$(OPTION) $(SRC)\mlt_main.c
#
$(OBJECT)\mlt_sub.obj:   $(SRC)\mlt_sub.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\sys_line.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\mlt_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\mem_def.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\mlt_data.h		\
					\src\atlanta\define\syst30.h		\
					\src\atlanta\define\dpr_def.h		\
				\src\atlanta\ext_v\bkupram.h		\
					\src\atlanta\define\sysbatch.h		\
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
					\src\atlanta\define\sysorder.h		\
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
				\src\memsw\define\mems_pro.h
        $(CC)	$(OPTION) $(SRC)\mlt_sub.c
#-----------------------------------------------------------------------------
# ２回線仕様時のポーリング排他処理関係ファイルメイク部
# By O.Kimoto 1996/12/20
#-----------------------------------------------------------------------------
$(OBJECT)\mlt_poll.obj:       $(SRC)\mlt_poll.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\atlanta\define\sys_line.h		\
				\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\mlt_pro.h		\
				\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\message.h		\
				\src\atlanta\define\mem_pro.h		\
					\src\atlanta\ext_v\memertbl.h		\
				\src\atlanta\define\unisw_a.h		\
				\src\atlanta\define\uni_pro.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\man_pro.h		\
				\src\memsw\define\mem_sw_b.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\sysscan.h		\
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
				\src\atlanta\ext_v\mlt_data.h
        $(CC)	$(OPTION) $(SRC)\mlt_poll.c
#
#-----------------------------------------------------------------------------
# ２回線仕様時の回線選択用テーブルメイク部
# By O.Kimoto 1997/01/17
#-----------------------------------------------------------------------------
#1997/03/13  By T.Yamaguchi TABLE.MKに移動
#$(OBJECT)\mlt_tbl.obj:       $(DEFV)\mlt_tbl.c
#        $(CC)	$(COPTION) $(DEFV)\mlt_tbl.C
#-----------------------------------------------------------------------------
#   オプションボード用データバッファメイク部 Add By O.Kimoto 1996/11/15
# 本来はData.MKに記述するべきところですが、メイクファイル共通化が困難な為
# ここに入れておきます。　尚、セグメントはData.mkと一緒です。 By O.Kimoto 1996/11/19
#-----------------------------------------------------------------------------
#mlt_data.obj:       $(DEFV)\mlt_data.c		data.MK に移動 1997/03/13  By T.Yamaguchi
#    $(CC) $(DOPTION) $(DEFV)\mlt_data.c
#-----------------------------------------------------------------------------
#   オプションボード用Ｒ２８８Ｆモデムステータスモニターファイルメイク部
# 本来はLST.MKに記述するべきところですが、メイクファイル共通化が困難な為
# ここに入れておきます。　尚、セグメントはLST.mkと一緒です。 By O.Kimoto 1996/12/20
#-----------------------------------------------------------------------------
#lst_r288.obj:       $(SRC)\lst_r288.c	   LST.MKに移動 1997/03/13  By T.Yamaguchi
#    $(CC)	$(LOPTION) $(SRC)\lst_r288.C

