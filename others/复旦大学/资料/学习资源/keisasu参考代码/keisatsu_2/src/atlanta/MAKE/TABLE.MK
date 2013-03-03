#------------------------------------------------------------------------
#   POPLAR/ANZU_L   データー・テーブル(ＴＢＬ)モジュールのメイクファイル
#------------------------------------------------------------------------
DEFINE		= \src\atlanta\define
DEFV		= \src\atlanta\def_v
EXTV		= \src\atlanta\ext_v
SRC			= \src\atlanta\src
WORD		= \src\atlanta\wording
MDM_OG_DEFV	= \src\atlanta\mdm\orange\def_v
DEFVSC		= \src\atlanta\scd\def_v
MSWDEFINE	= \src\memsw\define
#!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLAR_L") || ("$(MODEL)" == "ANZU_L") || ("$(MODEL)" == "ANZU_V")
#!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLAR_L") || ("$(MODEL)" == "POPLAR_N") || ("$(MODEL)" == "ANZU_L") || ("$(MODEL)" == "ANZU_V")
!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLR_BN") || ("$(MODEL)" == "POPLAR_L") || ("$(MODEL)" == "POPLAR_N") || ("$(MODEL)" == "ANZU_L") || ("$(MODEL)" == "ANZU_V")
OPRDEFV		= \src\atlanta\opr\ank\def_v
!endif
!if ("$(MODEL)" == "POPLAR_H")
OPRDEFV		= \src\atlanta\opr\kanji\def_v
!endif
!if ("$(MODEL)" == "SAKAKI")
OPRDEFV		= \src\atlanta\opr\kanji\def_v
!endif
!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI2") || ("$(MODEL)" == "HINOKI3")) || ("$(MODEL)" == "KEISATSU") || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
OPRDEFV		= \src\atlanta\opr\ank\def_v
!endif

#
#-----------------------------------------------------------------------------
#	マクロを定義
#-----------------------------------------------------------------------------
CC			= shc
ASM			= asmsh
OPTION		= /op=0 /deb /def=($(MODEL),$(COUNTRY)) /cp=sh2
OPTION_ND	= /op=1  /cp=sh2 /def=($(MODEL),$(COUNTRY))
#By Y.Suzuki 96/6/7 scd_tbl を高速RAMに割り付けるため
OPTIONS		= /op=0 /deb /def=($(MODEL),$(COUNTRY)) /cp=sh2 /se=(C=CSCD_TBL)
ASM_OPT		= /cpu=$(CPU_OPT) /debug /object=$*.obj

# LNK			= lnk /subcommand=\src\atlanta\make\table.sub
!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU") || ("$(MODEL)" == "SAKAKI") || ("$(MODEL)" == "HINOKI2")) || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
#ＮｅｗＭａｓｋ対応機種用リンク by O.Kimoto 1998/09/14
# 元々、data.mkには、ソフトコーデック用やスクランブル用が入っていたので、それらを
# 独立させた。
LNK			= lnk /subcommand=\src\atlanta\make\table2.sub
NEW_MASK	= 1
!else
LNK			= lnk /subcommand=\src\atlanta\make\table.sub
NEW_MASK	= 0
!endif



OBJECT		= \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-----------------------------------------------------------------------------
#	データー・テーブル(ＴＢＬ)モジュールのＬｉｎｋ定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\table.lnk:   \src\atlanta\make\table2.sub \
			$(OBJECT)\rom_tbl.obj	\
			$(OBJECT)\cpu_tbl.obj	\
			$(OBJECT)\ini_tbl.obj	\
			$(OBJECT)\cmn_tbl.obj	\
			$(OBJECT)\scn_tbl.obj	\
			$(OBJECT)\atd_tbl.obj	\
			$(OBJECT)\ctry_tbl.obj	\
			$(OBJECT)\ncu_tbl.obj	\
#			$(OBJECT)\key_tbl.obj	\	/* OPR_ANKに移動 by O.Kimoto 1997/07/17 */
#			$(OBJECT)\pat_tbl.obj	\
			$(OBJECT)\lst_tbl.obj	\
#			$(OBJECT)\mdm_tbl.obj	\		#各オペレーションメークファイルに移動しました。By O.Kimoto 1997/09/04
			$(OBJECT)\fcm_tbl.obj	\
!if ("$(NEW_MASK)" == "0")
			$(OBJECT)\scd_tbl.obj	\
			$(OBJECT)\reductbl.obj	\
			$(OBJECT)\scdptbl.obj	\
!endif
#			$(OBJECT)\opr_tbl.obj	\	/* OPR_ANKに移動 by O.Kimoto 1997/07/17 */
#			$(OBJECT)\dpr_tbl.obj	\
			$(OBJECT)\dma_tbl.obj	\
			$(OBJECT)\cg_rom0.obj	\
			$(OBJECT)\cg_rom1.obj	\
			$(OBJECT)\mlt_tbl.obj	\
#			$(OBJECT)\mdmertbl.obj	\		#各オペレーションメークファイルに移動しました。By O.Kimoto 1997/09/04
			$(OBJECT)\memertbl.obj	\
			$(OBJECT)\opt_tbl.obj	\
			$(OBJECT)\pro_tbl.obj	\
			$(OBJECT)\font_tbl.obj
#By S.K Dec.12,1995		 $(LNK) @\src\atlnata\make\table.cmd
		$(LNK)

#-----------------------------------------------------------------------------
#	ＴＡＢＬＥモジュールのＣｏｍｐｉｌｅ定義
#-----------------------------------------------------------------------------
#
#-----------------------------------------------------------------------------
#	ＲＯＭテーブル
#-----------------------------------------------------------------------------
$(OBJECT)\rom_tbl.obj:	  $(DEFV)\rom_tbl.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\rom_def.h
		$(CC)	$(OPTION) $(DEFV)\rom_tbl.c
#
#-----------------------------------------------------------------------------
#	ＣＰＵテーブル
#-----------------------------------------------------------------------------
$(OBJECT)\cpu_tbl.obj:	  $(DEFV)\cpu_tbl.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysmax.h
		$(CC)	$(OPTION) $(DEFV)\cpu_tbl.c
#
#-----------------------------------------------------------------------------
#	ＩＮＩテーブル
#-----------------------------------------------------------------------------
$(OBJECT)\ini_tbl.obj:	  $(DEFV)\ini_tbl.c	\
					\src\atlanta\define\product.h		\
					\src\atlanta\define\status.h		\
					\src\atlanta\ext_v\scn_tbl.h		\
						\src\atlanta\define\scn_def.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\hinoki\def_v\ini_tbl.c
		$(CC)	$(OPTION) $(DEFV)\ini_tbl.c
#
#-----------------------------------------------------------------------------
#	ＣＭＮテーブル
#-----------------------------------------------------------------------------
$(OBJECT)\cmn_tbl.obj:	  $(DEFV)\cmn_tbl.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\keycode.h		\
					\src\atlanta\opr\ank\define\keycode.h
		$(CC)	$(OPTION) $(DEFV)\cmn_tbl.c
#
#-----------------------------------------------------------------------------
#	ＳＣＮテーブル
#-----------------------------------------------------------------------------
$(OBJECT)\scn_tbl.obj :	$(DEFV)\scn_tbl.c	\
					\src\atlanta\define\product.h		\
					\src\atlanta\define\std.h		\
					\src\atlanta\define\scn_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\hinoki\def_v\scn_tbl.c		\
					\src\atlanta\hinoki\define\scn_def.h		\
					\src\atlanta\hinoki\ext_v\scn_tbl.h		\
					\src\cpu\sh7043_a\irom\define\sh_port.h		\
						\src\atlanta\hinoki\define\hinoport.h
				$(CC) $(OPTION) $(DEFV)\scn_tbl.c
#
#-----------------------------------------------------------------------------
#	ＡＴＤテーブル
#-----------------------------------------------------------------------------
$(OBJECT)\atd_tbl.obj:	  $(DEFV)\atd_tbl.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\atd_def.h
		$(CC)	$(OPTION) $(DEFV)\atd_tbl.c
#
#-----------------------------------------------------------------------------
#	ＣＴＲＹテーブル
#-----------------------------------------------------------------------------
$(OBJECT)\ctry_tbl.obj:	  $(DEFV)\ctry_tbl.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\country.h		\
				\src\atlanta\def_v\ctry_jpn.c		\
				\src\atlanta\def_v\ctry_usa.c		\
				\src\atlanta\def_v\ctry_aus.c		\
				\src\atlanta\def_v\ctry_gbr.c		\
				\src\atlanta\def_v\ctry_fra.c		\
				\src\atlanta\def_v\ctry_deu.c		\
				\src\atlanta\def_v\ctry_twn.c		\
				\src\atlanta\def_v\ctry_EC1.c
		$(CC)	$(OPTION) $(DEFV)\ctry_tbl.c
#
#-----------------------------------------------------------------------------
#	ＮＣＵテーブル
#-----------------------------------------------------------------------------
$(OBJECT)\ncu_tbl.obj:	  $(DEFV)\ncu_tbl.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\ncu_def.h		\
					\src\atlanta\define\ncu_cnst.h		\
				\src\atlanta\define\sysmax.h
		$(CC)	$(OPTION) $(DEFV)\ncu_tbl.c
#
#-----------------------------------------------------------------------------
#	ＯＰＲテーブル
#-----------------------------------------------------------------------------
#/* OPR_ANKに移動 By O.Kimoto 1997/07/16 */
#$(OBJECT)\opr_tbl.obj:	  $(OPRDEFV)\opr_tbl.c	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\define\keycode.h		\
#				\src\atlanta\define\std.h		\
#				\src\atlanta\define\status.h		\
#				\src\atlanta\define\syscomf.h		\
#					\src\atlanta\define\sysdial.h		\
#				\src\atlanta\define\sysdoc.h		\
#				\src\atlanta\define\sysmax.h		\
#				\src\atlanta\define\sysonet.h		\
#					\src\atlanta\define\sysspeed.h		\
#				\src\atlanta\opr\ank\define\opr_def.h		\
#					\src\atlanta\define\time.h		\
#				\src\atlanta\opr\ank\define\opr_pro.h		\
#				\src\atlanta\ext_v\bkupram.h		\
#					\src\atlanta\define\sysbatch.h		\
#					\src\atlanta\define\sysmailb.h		\
#					\src\atlanta\define\sysjrnl.h		\
#					\src\atlanta\define\sysexec.h		\
#					\src\atlanta\define\sysmcopy.h		\
#					\src\atlanta\define\syslifem.h		\
#					\src\atlanta\define\sysshad.h		\
#					\src\atlanta\define\sysdiali.h		\
#					\src\atlanta\define\sysmemrx.h		\
#					\src\atlanta\define\syscost.h		\
#					\src\atlanta\define\syst30.h		\
#					\src\atlanta\define\sysdeprt.h		\
#					\src\atlanta\define\systbok.h		\
#					\src\atlanta\define\sysopspd.h		\
#					\src\atlanta\define\sysringm.h		\
#						\src\atlanta\define\ncu_cnst.h		\
#					\src\atlanta\define\syscntpl.h		\
#					\src\atlanta\define\syspcrx.h		\
#					\src\atlanta\define\dpr_def.h		\
#						\src\atlanta\define\mem_def.h		\
#					\src\atlanta\define\sysfcode.h		\
#				\src\atlanta\opr\ank\ext_v\opr_wrd0.h
#		$(CC)	$(OPTION) $(OPRDEFV)\opr_tbl.c
#
#-----------------------------------------------------------------------------
#	ＫＥＹテーブル
#-----------------------------------------------------------------------------
#/* OPR_ANKに移動 By O.Kimoto 1997/07/16 */
#$(OBJECT)\key_tbl.obj:	  $(DEFV)\key_tbl.c	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\define\keycode.h		\
#				\src\atlanta\define\std.h		\
#				\src\atlanta\opr\ank\define\opr_def.h		\
#					\src\atlanta\define\syscomf.h		\
#						\src\atlanta\define\sysdial.h		\
#					\src\atlanta\define\sysmax.h		\
#					\src\atlanta\define\sysonet.h		\
#						\src\atlanta\define\sysspeed.h		\
#					\src\atlanta\define\time.h		\
#				\src\atlanta\sh7043\define\sh_port.h
#		$(CC)	$(OPTION) $(DEFV)\key_tbl.c
#
#各オペレーションメークファイルに移動しました。By O.Kimoto 1997/09/04
# #-----------------------------------------------------------------------------
# #	ＭＤＭテーブル
# #-----------------------------------------------------------------------------
# $(OBJECT)\mdm_tbl.obj:	  $(MDM_OG_DEFV)\mdm_tbl.c	\
# 				\src\atlanta\define\product.h		\
# 				\src\atlanta\mdm\orange\define\mdm_def.h		\
# 					\src\atlanta\mdm\orange\define\mdm_pro.h		\
# 					\src\atlanta\define\dma_def.h		\
# 						\src\atlanta\sh7043\define\sh_port.h		\
# 					\src\atlanta\define\dma_pro.h		\
# 				\src\atlanta\ext_v\bkupram.h		\
# 					\src\atlanta\define\SYSMAX.h		\
# 					\src\atlanta\define\sysbatch.h		\
# 						\src\atlanta\define\sysdial.h		\
# 					\src\atlanta\define\sysmailb.h		\
# 					\src\atlanta\define\sysjrnl.h		\
# 					\src\atlanta\define\syscomf.h		\
# 					\src\atlanta\define\sysonet.h		\
# 					\src\atlanta\define\sysexec.h		\
# 					\src\atlanta\define\sysmcopy.h		\
# 					\src\atlanta\define\syslifem.h		\
# 					\src\atlanta\define\sysshad.h		\
# 					\src\atlanta\define\sysspeed.h		\
# 					\src\atlanta\define\sysdiali.h		\
# 					\src\atlanta\define\sysmemrx.h		\
# 					\src\atlanta\define\syscost.h		\
# 					\src\atlanta\define\syst30.h		\
# 					\src\atlanta\define\sysdeprt.h		\
# 					\src\atlanta\define\systbok.h		\
# 					\src\atlanta\define\sysopspd.h		\
# 					\src\atlanta\define\sysringm.h		\
# 						\src\atlanta\define\ncu_cnst.h		\
# 					\src\atlanta\define\syscntpl.h		\
# 					\src\atlanta\define\syspcrx.h		\
# 					\src\atlanta\define\dpr_def.h		\
# 						\src\atlanta\define\mem_def.h		\
# 					\src\atlanta\define\sysfcode.h
# 	$(CC) $(OPTION) $(MDM_OG_DEFV)\mdm_tbl.c
#
#-----------------------------------------------------------------------------
#	ＦＣＭテーブル
#-----------------------------------------------------------------------------
$(OBJECT)\fcm_tbl.obj:	  $(DEFV)\fcm_tbl.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\mem_def.h
	$(CC) $(OPTION) $(DEFV)\fcm_tbl.c
#
#-----------------------------------------------------------------------------
#	ＬＳＴテーブル
#-----------------------------------------------------------------------------
$(OBJECT)\lst_tbl.obj:	  $(DEFV)\lst_tbl.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\fcm_def.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\std.h
	$(CC) $(OPTION) $(DEFV)\lst_tbl.c
#
#-----------------------------------------------------------------------------
#	PAT_JRNL用 ROM データ
#-----------------------------------------------------------------------------
#$(OBJECT)\pat_tbl.obj:	  $(DEFV)\pat_tbl.c	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\define\pat_def.h		\
#				\src\atlanta\define\std.h
#	$(CC) $(OPTION) $(DEFV)\pat_tbl.c
#
#-----------------------------------------------------------------------------
#	ｿﾌﾄｺｰﾃﾞｯｸﾃｰﾌﾞﾙ
#-----------------------------------------------------------------------------
$(OBJECT)\scd_tbl.obj:	  $(DEFVSC)\scd_tbl.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\def_v\scd_tbl.c		\
					\src\atlanta\define\mem_def.h		\
					\src\cpu\sh7043_a\scd\define\scd_def.h		\
					\src\cpu\sh7043_a\scd\define\scd.h		\
					\src\cpu\sh7043_a\scd\ext_v\scd_data.h		\
				\src\atlanta\scd\define\scd_def.h		\
				\src\atlanta\scd\define\scd.h		\
				\src\atlanta\scd\ext_v\scd_data.h		\
					\src\atlanta\define\sysdoc.h		\
					\src\atlanta\define\message.h
		$(CC)	$(OPTIONS) $(DEFVSC)\scd_tbl.c
#
$(OBJECT)\reductbl.obj :	$(DEFVSC)\reductbl.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\def_v\reductbl.c
		$(CC) $(OPTIONS) $(DEFVSC)\reductbl.c
#
#-----------------------------------------------------------------------------
#	ＤＰＲテーブル
#-----------------------------------------------------------------------------
#$(OBJECT)\dpr_tbl.obj:	  $(DEFV)\dpr_tbl.c	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\define\dpr_def.h		\
#					\src\atlanta\define\mem_def.h
#		$(CC)	$(OPTION) $(DEFV)\dpr_tbl.c
#
#-----------------------------------------------------------------------------
#	ＤＭＡ（ＤＴＣ）テーブル
#-----------------------------------------------------------------------------
$(OBJECT)\dma_tbl.obj:	  $(DEFV)\dma_tbl.c	\
				\src\atlanta\define\product.h
		$(CC)	$(OPTION) $(DEFV)\dma_tbl.c
#
#-----------------------------------------------------------------------------
#	ＣＧＲＯＭ０テーブル
#-----------------------------------------------------------------------------
!if ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
$(OBJECT)\cg_rom0.obj:	  $(DEFV)\cg_rom0s.c	\
!else
$(OBJECT)\cg_rom0.obj:	  $(DEFV)\cg_rom0.c	\
!endif
				\src\atlanta\define\product.h
		$(CC)	$(OPTION) $(DEFV)\cg_rom0.c
#
#-----------------------------------------------------------------------------
#	ＣＧＲＯＭ１テーブル
#-----------------------------------------------------------------------------
!if ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
$(OBJECT)\cg_rom1.obj:	  $(DEFV)\cg_rom1s.c	\
!else
$(OBJECT)\cg_rom1.obj:	  $(DEFV)\cg_rom1.c	\
!endif
				\src\atlanta\define\product.h
		$(CC)	$(OPTION) $(DEFV)\cg_rom1.c
#
#-----------------------------------------------------------------------------
# ２回線仕様時の回線選択用テーブルメイク部
# By O.Kimoto 1997/01/17
#-----------------------------------------------------------------------------
#1997/03/13  By T.Yamaguchi TABLE.MKに移動
$(OBJECT)\mlt_tbl.obj:       $(DEFV)\mlt_tbl.c
        $(CC)	$(OPTION) $(DEFV)\mlt_tbl.C
#
#-----------------------------------------------------------------------------
#	ｿﾌﾄｺｰﾃﾞｯｸﾃｰﾌﾞﾙ By Y.Suzuki 1997/03/18
#	外部ＲＯＭから参照する、内部ＲＯＭモジュールアドレス固定用
#-----------------------------------------------------------------------------
$(OBJECT)\scdptbl.obj:	  $(DEFVSC)\scdptbl.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\def_v\scdptbl.c		\
					\src\cpu\sh7043_a\scd\define\scdirpro.h		\
						\src\cpu\sh7043_a\scd\define\scd.h		\
					\src\cpu\sh7043_a\scd\ext_v\scdrlbuf.h		\
						\src\atlanta\define\sysdoc.h		\
						\src\cpu\sh7043_a\scd\define\scd_def.h		\
						\src\atlanta\scd\define\scd_def.h		\
					\src\atlanta\scd\ext_v\scdrlbuf.h		\
				\src\atlanta\scd\define\scdirpro.h		\
					\src\atlanta\scd\define\scd.h		\
						\src\atlanta\define\mem_def.h
		$(CC)	$(OPTION) $(DEFVSC)\scdptbl.c
#
#-----------------------------------------------------------------------------
# ２回線仕様時のホストの能力テーブルメイク部
# By M.Kotani 1997/03/24
#-----------------------------------------------------------------------------
$(OBJECT)\pro_tbl.obj:       $(DEFV)\pro_tbl.c		\
				\src\atlanta\define\product.h		\
					\src\atlanta\define\pro_def.h		\
				\src\atlanta\hinoki\def_v\pro_tbl.c
		$(CC)	$(OPTION) $(DEFV)\pro_tbl.C
#
#各オペレーションメークファイルに移動しました。By O.Kimoto 1997/09/04
# #-----------------------------------------------------------------------------
# #	ｿﾌﾄｺｰﾃﾞｯｸﾃｰﾌﾞﾙ By Y.Suzuki 1997/04/1
# #	内部ＲＯＭから参照する、外部ＲＯＭモジュールアドレス固定用
# #-----------------------------------------------------------------------------
# $(OBJECT)\mdmertbl.obj:	  $(MDM_OG_DEFV)\mdmertbl.c	\
# 				\src\atlanta\define\product.h		\
# 				\src\atlanta\mdm\orange\define\mdmerpro.h
# 		$(CC)	$(OPTION) $(MDM_OG_DEFV)\mdmertbl.c
#
#-----------------------------------------------------------------------------
#	ｿﾌﾄｺｰﾃﾞｯｸﾃｰﾌﾞﾙ By Y.Suzuki 1997/04/1
#	内部ＲＯＭから参照する、外部ＲＯＭモジュールアドレス固定用
#-----------------------------------------------------------------------------
$(OBJECT)\memertbl.obj:	  $(DEFV)\memertbl.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\memerpro.h		\
				\src\atlanta\define\mem_def.h
		$(CC)	$(OPTION) $(DEFV)\memertbl.c
#
#-----------------------------------------------------------------------------
#	フォントテーブル（ＪＩＳ第２水準）				by K.Watanabe 1997/04/09
#-----------------------------------------------------------------------------
!if ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
$(OBJECT)\font_tbl.obj:	$(DEFV)\fonttbls.c	\
!else
$(OBJECT)\font_tbl.obj:	$(DEFV)\font_tbl.c	\
!endif
				\src\atlanta\define\product.h		\
				\src\atlanta\define\font_def.h
		$(CC) $(OPTION) $(DEFV)\font_tbl.c
#
#-----------------------------------------------------------------------------
# ２回線オプション用テーブルメイク部
# 1997/09/10 Y.Murata
#-----------------------------------------------------------------------------
$(OBJECT)\opt_tbl.obj:       $(DEFV)\opt_tbl.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\hinoki\def_v\opt_tbl.c
        $(CC)	$(OPTION) $(DEFV)\opt_tbl.C
#
