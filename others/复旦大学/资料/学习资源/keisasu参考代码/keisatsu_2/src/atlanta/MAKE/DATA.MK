#------------------------------------------------------------------------
#   POPLAR ﾒｲｸ･ﾌｧｲﾙ By Y.Suzuki 1996/10/14
#	とりあえずANZUの下から移植しました。
#   各大機能担当の方で追加、修正願います。
#
#	機種毎で異なるファイルがあるので、それらは該当するメークモジュールに
#	移動させます。（OPR_DATA/MDM_DATA)	By O.Kimoto 1997/09/04
#
#------------------------------------------------------------------------
DEFINE 		= \src\atlanta\define
DEFV 		= \src\atlanta\def_v
DEFVP 		= \src\atlanta\prt\thermal\def_v
DEFVSC 		= \src\atlanta\scd\def_v
EXTV		= \src\atlanta\ext_v
EXTVSC 		= \src\atlanta\scd\ext_v
MDM_OG_DEFV = \src\atlanta\mdm\orange\def_v
SRC			= \src\atlanta\src
WORD		= \src\atlanta\wording
MON			= \src\atlanta\mon
MAKE		= \src\atlanta\make
MSWDEFINE	= \src\memsw\define
SRCSC		= \src\atlanta\scd\src
#以下は不要です。
# !if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLAR_L") || ("$(MODEL)" == "ANZU_L")
# OPRDEFV		= \src\atlanta\opr\ank\def_v
# !endif
# !if ("$(MODEL)" == "POPLAR_H")
# OPRDEFV		= \src\atlanta\opr\kanji\def_v
# !endif


#
#-----------------------------------------------------------------------------
#   ｺﾏﾝﾄﾞ名を定義
#-----------------------------------------------------------------------------
CC          = shc
ASM         = asmsh
PTIONO      = /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION2     = /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY)) /se=(d=DRLBUF)
OPTION3     = /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY)) /se=(d=DSCDDATA)
ASM_OPT     = /cpu=$(CPU_OPT) /debug /object=$*.obj

OPTION      = /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
ASM_OPT     = /cpu=sh2 /debug /object=$*.obj

#LNK         = lnk /subcommand=\src\atlanta\make\data.sub

!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU") || ("$(MODEL)" == "SAKAKI") || ("$(MODEL)" == "HINOKI2")) || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
#ＮｅｗＭａｓｋ対応機種用リンク by O.Kimoto 1998/09/14
# 元々、data.mkには、ソフトコーデック用やスクランブル用が入っていたので、それらを
# 独立させた。
LNK         = lnk /subcommand=\src\atlanta\make\data2.sub
NEW_MASK	= 1
!else
LNK         = lnk /subcommand=\src\atlanta\make\data.sub
NEW_MASK	= 0
!endif




OBJECT      = \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-----------------------------------------------------------------------------
#   ﾎﾟﾌﾟﾗ用ﾃﾞｰﾀﾓｼﾞｭｰﾙのﾘﾝｸを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\data.lnk:		\src\atlanta\make\data2.sub	\
	$(OBJECT)\sys_data.obj	\
	$(OBJECT)\memindex.obj	\
	$(OBJECT)\sys_port.obj	\
	$(OBJECT)\bkupram.obj	\
	$(OBJECT)\atd_data.obj	\
#	$(OBJECT)\mdm_data.obj	\	#各オペレーションメークファイルに移動しました。By O.Kimoto 1997/09/04
#	$(OBJECT)\mdm_ebuf.obj	\	#各オペレーションメークファイルに移動しました。By O.Kimoto 1997/09/04
	$(OBJECT)\ncu_data.obj	\
	$(OBJECT)\fcm_data.obj	\
#	$(OBJECT)\opr_data.obj	\	#各オペレーションメークファイルに移動しました。By O.Kimoto 1997/09/04
	$(OBJECT)\lst_data.obj	\
##	$(OBJECT)\fx_data.obj	\
##	$(OBJECT)\fip_data.obj	\
	$(OBJECT)\man_data.obj	\
	$(OBJECT)\cdc_data.obj	\
	$(OBJECT)\scn_data.obj	\
#	$(OBJECT)\prn_data.obj	\
#	$(OBJECT)\pat_data.obj	\
	$(OBJECT)\dma_data.obj	\
!if ("$(NEW_MASK)" == "0")
	$(OBJECT)\scd_data.obj	\
	$(OBJECT)\scdrlbuf.obj	\
	$(OBJECT)\cph_data.obj	\
	$(OBJECT)\ini_sct.obj	\
!endif
	$(OBJECT)\comfile.obj	\
    $(OBJECT)\mlt_data.obj	\
#    $(OBJECT)\rot_data.obj	\
	$(OBJECT)\cmn_data.obj
        $(LNK)
#-----------------------------------------------------------------------------
#   ﾘｱﾙﾀｲﾑﾓﾆﾀﾓｼﾞｭｰﾙのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
$(OBJECT)\sys_data.obj:   $(DEFV)\sys_data.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\time.h		\
				\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\define\fip_def.h		\
				\src\atlanta\define\sysscan.h
        $(CC)   $(OPTION) $(DEFV)\sys_data.c
#
$(OBJECT)\bkupram.obj:    $(DEFV)\bkupram.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sysmailb.h		\
				\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\define\sysbatch.h		\
					\src\atlanta\define\sysdial.h		\
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
					\src\atlanta\define\mem_def.h
        $(CC)   $(OPTION) $(DEFV)\bkupram.c
#
$(OBJECT)\sys_port.obj:   $(DEFV)\sys_port.c	\
				\src\atlanta\define\product.h
        $(CC)   $(OPTION) $(DEFV)\sys_port.c
#
$(OBJECT)\atd_data.obj:   $(DEFV)\atd_data.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\atd_def.h
        $(CC) 	$(OPTION) $(DEFV)\atd_data.c
#
#-----------------------------------------------------------------------------
#   ﾒﾓﾘ管理 ﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
$(OBJECT)\memindex.obj:   $(DEFV)\memindex.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mem_def.h
        $(CC) $(OPTION) $(DEFV)\memindex.c
#
#-----------------------------------------------------------------------------
#   ﾒﾓﾘ管理 使用ﾃﾞｰﾀのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
# Jan.10,1994	->	Nov.22,94	to bkupram.c
#
#$(OBJECT)\mem_data.obj:   $(DEFV)\mem_data.c
#      $(CC) $(OPTION) $(DEFV)\mem_data.c
#
#
#以下は各オペレーション用メークファイルに移動させます By O.Kimoto 1997/09/04
# #-----------------------------------------------------------------------------
# #   ﾓﾃﾞﾑﾃﾞｰﾀ
# #-----------------------------------------------------------------------------
# $(OBJECT)\mdm_data.obj:   $(MDM_OG_DEFV)\mdm_data.c	\
# 				\src\atlanta\define\product.h		\
# 				\src\atlanta\define\mem_def.h		\
# 				\src\atlanta\mdm\orange\define\mdm_def.h		\
# 					\src\atlanta\mdm\orange\define\mdm_pro.h		\
# 					\src\atlanta\define\dma_def.h		\
# 						\src\atlanta\sh7043\define\sh_port.h		\
# 					\src\atlanta\define\dma_pro.h		\
# 				\src\atlanta\define\message.h
#      $(CC) $(OPTION) $(MDM_OG_DEFV)\mdm_data.c
# #
# $(OBJECT)\mdm_ebuf.obj:   $(MDM_OG_DEFV)\mdm_ebuf.c	\
# 				\src\atlanta\define\product.h		\
# 				\src\atlanta\mdm\orange\define\mdm_def.h		\
# 					\src\atlanta\mdm\orange\define\mdm_pro.h		\
# 					\src\atlanta\define\dma_def.h		\
# 						\src\atlanta\sh7043\define\sh_port.h		\
# 					\src\atlanta\define\dma_pro.h
#     $(CC) $(OPTION) $(MDM_OG_DEFV)\mdm_ebuf.c
#
$(OBJECT)\ncu_data.obj:   $(DEFV)\ncu_data.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\ncu_def.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\ncu_cnst.h
    $(CC)   $(OPTION) $(DEFV)\ncu_data.c
#
$(OBJECT)\fcm_data.obj:   $(DEFV)\fcm_data.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sysbatch.h		\
				\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\define\mem_def.h
    $(CC) $(OPTION) $(DEFV)\fcm_data.c
#

#以下は各オペレーション用メークファイルに移動させます By O.Kimoto 1997/09/04
# #-----------------------------------------------------------------------------
# #  オペレーション用データ
# #-----------------------------------------------------------------------------
# $(OBJECT)\opr_data.obj:   $(OPRDEFV)\opr_data.c	\
# 				\src\atlanta\define\product.h		\
# 				\src\atlanta\define\message.h		\
# 				\src\atlanta\define\sysmax.h		\
# 				\src\atlanta\define\sysmcopy.h		\
# 				\src\atlanta\opr\ank\define\opr_def.h		\
# 					\src\atlanta\define\syscomf.h		\
# 						\src\atlanta\define\sysdial.h		\
# 					\src\atlanta\define\sysonet.h		\
# 						\src\atlanta\define\sysspeed.h		\
# 					\src\atlanta\define\time.h
#     $(CC) $(OPTION) $(OPRDEFV)\opr_data.c
#
$(OBJECT)\lst_data.obj:   $(DEFV)\lst_data.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\lst_def.h		\
					\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\time.h		\
				\src\atlanta\define\timer10.h
    $(CC) $(OPTION) $(DEFV)\lst_data.c
#
#-----------------------------------------------------------------------------
#   MAN用データ
#-----------------------------------------------------------------------------
$(OBJECT)\man_data.obj:       $(DEFV)\man_data.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\sysmax.h
    $(CC) $(OPTION) $(DEFV)\man_data.c
#
#-----------------------------------------------------------------------------
#   CDC用データ
#-----------------------------------------------------------------------------
$(OBJECT)\cdc_data.obj:			$(DEFV)\cdc_data.c	\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\define\cdc_blk.h		\
					\src\atlanta\define\product.h
	$(CC)	$(OPTION)	$(DEFV)\cdc_data.c
#
#-----------------------------------------------------------------------------
#   SCN用データ
#-----------------------------------------------------------------------------
$(OBJECT)\scn_data.obj :		$(DEFV)\scn_data.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\scn_def.h		\
				\src\atlanta\define\sysmcopy.h
	$(CC) $(OPTION) $(DEFV)\scn_data.c
#
#-----------------------------------------------------------------------------
# ﾌﾟﾘﾝﾀ使用ﾃﾞｰﾀ
#-----------------------------------------------------------------------------

#$(OBJECT)\prn_data.obj:	$(DEFVP)\prn_data.c
#		$(CC)	$(OPTION) $(DEFVP)\prn_data.c
#-----------------------------------------------------------------------------
#   PAT_JRNL用データ
#-----------------------------------------------------------------------------
#$(OBJECT)\pat_data.obj:       $(DEFV)\pat_data.c	\
#				\src\atlanta\define\product.h		\
#				\src\atlanta\define\lst_def.h		\
#					\src\atlanta\define\sysdoc.h		\
#				\src\atlanta\define\pat_def.h		\
#				\src\atlanta\define\std.h		\
#				\src\atlanta\define\sysjrnl.h		\
#					\src\atlanta\define\sysmax.h
#    $(CC) $(OPTION) $(DEFV)\pat_data.c
#-----------------------------------------------------------------------------
#   DMA_TC用データ
#-----------------------------------------------------------------------------
$(OBJECT)\dma_data.obj:       $(DEFV)\dma_data.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\dma_blk.h
    $(CC) $(OPTION) $(DEFV)\dma_data.c
#-----------------------------------------------------------------------------
#   ｿﾌﾄｺｰﾃﾞｯｸ用ﾃﾞｰﾀﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
$(OBJECT)\scd_data.obj:       $(DEFVSC)\scd_data.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\scd\define\scd.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\message.h
    $(CC) $(OPTION3) $(DEFVSC)\scd_data.c
#-----------------------------------------------------------------------------
#   ｿﾌﾄｺｰﾃﾞｯｸ用rlﾊﾞｯﾌｧﾒｲｸ部
#-----------------------------------------------------------------------------
$(OBJECT)\scdrlbuf.obj:       $(DEFVSC)\scdrlbuf.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\scd\define\scd.h		\
					\src\atlanta\define\mem_def.h
    $(CC) $(OPTION2) $(DEFVSC)\scdrlbuf.c
#-----------------------------------------------------------------------------
#   共通部ﾃﾞｰﾀﾒｲｸ部 T.Nose.1996/11/19
#-----------------------------------------------------------------------------
$(OBJECT)\cmn_data.obj:       $(DEFV)\cmn_data.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\timer10.h		\
				\src\atlanta\define\cmn_def.h
    $(CC) $(OPTION) $(DEFV)\cmn_data.c
#-----------------------------------------------------------------------------
#   コマンドファイル（ＤＲＡＭ配置）
#-----------------------------------------------------------------------------
$(OBJECT)\comfile.obj:       $(DEFV)\comfile.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\syscomf.h		\
					\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sysfcode.h
    $(CC) $(OPTION) $(DEFV)\comfile.c
#-----------------------------------------------------------------------------
#   オプションボード用データバッファメイク部 Add By O.Kimoto 1996/11/15
# 本来はData.MKに記述するべきところですが、メイクファイル共通化が困難な為
# ここに入れておきます。　尚、セグメントはData.mkと一緒です。 By O.Kimoto 1996/11/19
#-----------------------------------------------------------------------------
#1997/03/13  By T.Yamaguchi
$(OBJECT)\mlt_data.obj:       $(DEFV)\mlt_data.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\syst30.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sys_opt.h		\
				\src\atlanta\define\sysdial.h		\
				\src\atlanta\define\sysjrnl.h		\
				\src\atlanta\define\message.h
    $(CC) $(OPTION) $(DEFV)\mlt_data.c
#-----------------------------------------------------------------------------
#   回転受信ﾃﾞｰﾀﾒｲｸ部 M.Kotani 1997/04/11
#-----------------------------------------------------------------------------
#$(OBJECT)\rot_data.obj:       $(DEFV)\rot_data.c	\
#				\src\atlanta\define\rot_def.h
#    $(CC) $(OPTION) $(DEFV)\rot_data.c
#------------------------------------------------------------------------------------------
#	スクランブルモジュールの使用するCライブラリのため Ｂセクションの先頭を示すシンボルです。
#------------------------------------------------------------------------------------------
$(OBJECT)\ini_sct.obj :$(SRCSC)\ini_sct.src
				$(ASM)	$(SRCSC)\ini_sct.src $(ASM_OPT)
#-----------------------------------------------------------------------------
#   暗号化受信ﾃﾞｰﾀﾒｲｸ部 By Y.Suzuki 1997/06/17
#-----------------------------------------------------------------------------
$(OBJECT)\cph_data.obj:       $(DEFVSC)\cph_data.c	\
				\src\atlanta\scd\define\cph_def.h		\
					\src\atlanta\define\product.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\scd\define\scd.h		\
				\src\atlanta\define\mem_def.h
    $(CC) $(OPTION) $(DEFVSC)\cph_data.c
