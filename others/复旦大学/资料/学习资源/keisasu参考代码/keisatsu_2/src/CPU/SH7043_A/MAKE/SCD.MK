#------------------------------------------------------------------------
#   ポプラ ﾒｲｸ･ﾌｧｲﾙ
#   ソフトコーデック関連ファイル By Y.Suzuki 1996/10/24
#------------------------------------------------------------------------
# =============================================================================
# =  ｻﾌｨｯｸｽ ﾘｽﾄ                                                               #
# =============================================================================
.SUFFIXES: .obj .c .src
#
# =============================================================================
# =  ﾏｸﾛ定義                                                                  #
# =============================================================================
DEFINE 		= \src\atlanta\define
DEFV 		= \src\atlanta\def_v
EXTV		= \src\atlanta\ext_v
SRC			= \src\atlanta\src
WORD		= \src\atlanta\wording
MON			= \src\atlanta\mon
MAKE		= \src\atlanta\make

DEFINESH 	= \src\cpu\SH7043_a\irom\define
DEFVSH		= \src\cpu\SH7043_a\irom\def_v
EXTVSH		= \src\cpu\SH7043_a\irom\ext_v
DEFINESC 	= \src\cpu\sh7043_a\scd\define
DEFVSC 		= \src\cpu\sh7043_a\scd\def_v
EXTVSC 		= \src\cpu\sh7043_a\scd\ext_v
SRCSC		= \src\cpu\sh7043_a\scd\src
DEFINEAL 	= \src\cpu\sh7043_a\scd\aliroo\define
SRCAL 		= \src\cpu\sh7043_a\scd\aliroo\src

#
PROTO_TYPE 	= $(DEFINE)\protype.h
#-----------------------------------------------------------------------------
CC          = shc
ASM         = asmsh
#
#ソフトコーデックファイルの内最適化onのファイルのデバック情報をはずす By Y.Suzuki 1998/02/20
OPTION      = /op=0 /deb /def=($(MODEL),$(COUNTRY)) /cp=sh2
OPTIONA2    = /op=0 /deb /def=($(MODEL),$(COUNTRY)) /cp=sh2 /se=(p=PALR)
OPTIONMS    = /op=1 /def=($(MODEL),$(COUNTRY)) /cp=sh2 /sp
OPTION2     = /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY)) /se=(d=DRLBUF)
#新ﾏｽｸ変更 SCD参照変数は内蔵RAMへ移動
#OPTION3     = /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY)) /se=(d=DSCDDATA)
OPTION3     = /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY)) /se=(d=DSCDDATAI)
OPTIONS2	= /op=0 /deb /def=($(MODEL),$(COUNTRY)) /cp=sh2 /se=(C=CSCD_TBL)

OPTIONS     = /op=1 /deb /def=($(MODEL),$(COUNTRY)) /cp=sh2 /sp /se=(p=PSCD)
OPTIOND     = /op=0 /deb /def=($(MODEL),$(COUNTRY)) /cp=sh2 /sp /se=(p=PSCD)
OPTIONASI   = /op=1 /deb /def=($(MODEL),$(COUNTRY),_EMBED) /cp=sh2 /size
OPTIONA     = /op=0 /deb /def=($(MODEL),$(COUNTRY),_EMBED) /cp=sh2
OPTIONASP   = /op=1 /def=($(MODEL),$(COUNTRY),_EMBED) /cp=sh2 /sp
# d=DALRを追加  By Y.Suzuki 1998/03/05
# 上記追加によりコンパイルコマンドが長くなりすぎてメイク不可能になったんで
# p=PALRは、ソースの中に記述してセグメント名をつけます。
#OPTIONAD    = /op=0 /deb /def=($(MODEL),$(COUNTRY),_EMBED) /cp=sh2 /se=(d=DALR,b=BALR_DATA,c=CALR_TBL)
#OPTIONADSP   = /op=1 /deb /def=($(MODEL),$(COUNTRY),_EMBED) /cp=sh2 /se=(d=DALR,b=BALR_DATA,c=CALR_TBL) /sp
OPTIONAD    = /op=0 /deb /def=($(MODEL),$(COUNTRY),_EMBED) /cp=sh2
OPTIONADSP   = /op=1 /deb /def=($(MODEL),$(COUNTRY),_EMBED) /cp=sh2 /sp
ASM_OPT_DE  = /cpu=sh2 /debug /object=$*.obj
ASM_OPT     = /cpu=sh2 /object=$*.obj
#ASM_OPT     = /cpu=$(CPU_OPT) /debug /object=$*.obj
MACHINE_DEF = sh
CMD_SUFX	= sub
#LNK         = lnk /subcommand=\src\atlanta\make\aliroo\scd.sub

#スクランブルなし用リンク By Y.Suzuki 1998/02/20
LNK         = lnk /subcommand=\src\cpu\sh7043_a\make\scd.sub

OBJECT      = \src\atlanta\$(MODEL)\work\$(COUNTRY)


#-----------------------------------------------------------------------------
#   ﾘｽｸ用ｿﾌﾄｺｰﾃﾞｯｸﾓｼﾞｭｰﾙのﾘﾝｸを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\scd2.lnk:		\src\cpu\sh7043_a\make\scd.$(CMD_SUFX)\
	$(OBJECT)\encode.obj	\
	$(OBJECT)\decode.obj	\
	$(OBJECT)\scd_cntl.obj	\
	$(OBJECT)\scd_redc.obj	\
	$(OBJECT)\scdrxpix.obj	\
	$(OBJECT)\scdmerx.obj	\
	$(OBJECT)\scdtx.obj		\
	$(OBJECT)\scdchtx.obj	\
	$(OBJECT)\scdmgrx.obj	\
	$(OBJECT)\scdfunc.obj	\
	$(OBJECT)\scdtxpix.obj	\
# Data.sub から移動しました。By O.Kimoto 1998/09/14
	$(OBJECT)\scd_data.obj	\
	$(OBJECT)\scdrlbuf.obj	\
	$(OBJECT)\cph_data.obj	\
	$(OBJECT)\ini_sct.obj	\
	$(OBJECT)\scd_tbl.obj	\
	$(OBJECT)\reductbl.obj	\
	$(OBJECT)\scdptbl.obj	\
#下記の機種以外には、スクランブル入れない By Y.Suzuki 1998/02/20
!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "SAKAKI") || ("$(MODEL)" == "HINOKI2") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU") || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2"))
	$(OBJECT)\scdcph.obj
!else
	$(OBJECT)\scdcph.obj	\
	$(OBJECT)\inifreep.obj	\
	$(OBJECT)\ALRANDML.obj	\
	$(OBJECT)\ALRANDOM.obj	\
	$(OBJECT)\DESCRDLL.obj	\
	$(OBJECT)\DRAW.obj	\
	$(OBJECT)\DROPLINE.obj	\
#	$(OBJECT)\EMBED.obj	\
	$(OBJECT)\EMBIO.obj	\
	$(OBJECT)\ENCRYPT.obj	\
	$(OBJECT)\ENCRYPT2.obj	\
	$(OBJECT)\FITPAGE.obj	\
	$(OBJECT)\GETCODE.obj	\
	$(OBJECT)\GETRECT.obj	\
	$(OBJECT)\MATCH.obj	\
	$(OBJECT)\MURATAFC.obj	\
	$(OBJECT)\SCRAMDLL.obj	\
	$(OBJECT)\SEGMENT.obj	\
	$(OBJECT)\SETUP.obj	\
	$(OBJECT)\SORTELM.obj	\
	$(OBJECT)\TRNSFRM.obj	\
	$(OBJECT)\UTILITY.obj	\
	$(OBJECT)\CPHPTBL.obj	\
	$(OBJECT)\ALRPTBL.obj	\
	$(OBJECT)\ALR_DATA.obj	\
	$(OBJECT)\CONSTANT.obj
!endif
        del $(OBJECT)\scd2.lnk
        $(LNK)
#-----------------------------------------------------------------------------
#   ｿﾌﾄｺｰﾃﾞｯｸﾓｼﾞｭｰﾙのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
$(OBJECT)\ENCODE.obj:       $(SRCSC)\ENCODE.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdoc.h		\
							\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
								\src\cpu\sh7043_a\irom\define\def_tcb.h		\
									\src\atlanta\define\message.h		\
								\src\cpu\sh7043_a\irom\define\def_scb.h		\
								\src\cpu\sh7043_a\irom\define\def_semn.h		\
								\src\cpu\sh7043_a\irom\define\def_mbxn.h		\
								\src\atlanta\define\mem_def.h		\
								\src\atlanta\define\dma_blk.h		\
								\src\atlanta\define\sysmax.h
    $(CC) $(OPTIONS) $(SRCSC)\ENCODE.c
#    $(CC) $(OPTIOND) $(SRCSC)\ENCODE.c

$(OBJECT)\DECODE.obj:       $(SRCSC)\DECODE.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mntsw_f.h		\
				\src\cpu\sh7043_a\scd\define\scd_def.h		\
				\src\cpu\sh7043_a\scd\define\scdpro.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\mem_def.h		\
					\src\cpu\sh7043_a\scd\ext_v\scdptbl.h		\
						\src\cpu\sh7043_a\scd\define\scdirpro.h		\
				\src\cpu\sh7043_a\scd\define\scd.h		\
				\src\cpu\sh7043_a\scd\ext_v\scd_tbl.h		\
				\src\cpu\sh7043_a\scd\ext_v\scd_data.h		\
							\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
								\src\cpu\sh7043_a\irom\define\def_tcb.h		\
								\src\cpu\sh7043_a\irom\define\def_scb.h		\
								\src\cpu\sh7043_a\irom\define\def_semn.h		\
								\src\cpu\sh7043_a\irom\define\def_mbxn.h		\
								\src\atlanta\define\dma_blk.h		\
								\src\atlanta\define\sysmax.h
    $(CC) $(OPTIONS) /l /sh=ob $(SRCSC)\DECODE.c
#    $(CC) $(OPTIOND) $(SRCSC)\DECODE.c

$(OBJECT)\SCD_CNTL.obj:       $(SRCSC)\SCD_CNTL.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\mem_pro.h		\
					\src\atlanta\ext_v\memertbl.h		\
						\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
							\src\cpu\sh7043_a\irom\define\def_tcb.h		\
							\src\cpu\sh7043_a\irom\define\def_scb.h		\
							\src\cpu\sh7043_a\irom\define\def_semn.h		\
							\src\cpu\sh7043_a\irom\define\def_mbxn.h		\
							\src\atlanta\define\dma_blk.h		\
							\src\atlanta\define\sysmax.h
#   $(CC) $(OPTIOND) $(SRCSC)\SCD_CNTL.c
   $(CC) $(OPTIONS) /l /sh=ob $(SRCSC)\SCD_CNTL.c

$(OBJECT)\SCD_REDC.obj:       $(SRCSC)\SCD_REDC.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\mem_def.h		\
				\src\cpu\sh7043_a\scd\define\scd_def.h		\
				\src\cpu\sh7043_a\scd\define\scd.h		\
				\src\cpu\sh7043_a\scd\define\scdpro.h		\
					\src\cpu\sh7043_a\scd\ext_v\scdptbl.h		\
						\src\cpu\sh7043_a\scd\define\scdirpro.h		\
				\src\cpu\sh7043_a\scd\ext_v\scd_data.h		\
					\src\atlanta\define\message.h		\
				\src\cpu\sh7043_a\scd\ext_v\reductbl.h
    $(CC) $(OPTIONS) $(SRCSC)\SCD_REDC.c
#    $(CC) $(OPTIOND) $(SRCSC)\SCD_REDC.c
#    $(CC) $(OPTIONMS) $(SRCSC)\SCD_REDC.c

$(OBJECT)\SCDRXPIX.obj:       $(SRCSC)\SCDRXPIX.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\fcm_def.h		\
				\src\memsw\define\mems_pro.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\uni_pro.h		\
							\src\atlanta\define\dma_blk.h		\
							\src\atlanta\define\sysmax.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
												\src\atlanta\define\message.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
#    $(CC) $(OPTION) $(SRCSC)\SCDRXPIX.c
    $(CC) $(OPTIONMS) $(SRCSC)\SCDRXPIX.c

$(OBJECT)\scdmerx.obj:       $(SRCSC)\scdmerx.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\mntsw_f.h		\
				\src\atlanta\define\uni_pro.h		\
							\src\atlanta\define\mem_def.h		\
							\src\atlanta\define\dma_blk.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
    $(CC) $(OPTION) $(SRCSC)\scdmerx.c

#$(OBJECT)\scdmetx.obj:       $(SRCSC)\scdmetx.c
#    $(CC) $(OPTION) $(SRCSC)\scdmetx.c

$(OBJECT)\scdtx.obj:       $(SRCSC)\scdtx.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\mntsw_f.h		\
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
					\src\atlanta\define\sysorder.h		\
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sys_infd.h		\
					\src\atlanta\define\syswarp.h		\
					\src\atlanta\define\sysnd.h		\
					\src\atlanta\define\sysmcr.h		\
							\src\atlanta\define\dma_blk.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
    $(CC) $(OPTION) $(SRCSC)\scdtx.c

$(OBJECT)\scdchtx.obj:       $(SRCSC)\scdchtx.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\lst_pro.h		\
				\src\atlanta\define\cdc_def.h		\
				\src\atlanta\define\mntsw_f.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\syspcrx.h		\
							\src\atlanta\define\dma_blk.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
    $(CC) $(OPTION) /l /sh=ob $(SRCSC)\scdchtx.c

$(OBJECT)\scdmgrx.obj:       $(SRCSC)\scdmgrx.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\mntsw_f.h		\
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
					\src\atlanta\define\sysorder.h		\
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h		\
						\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sys_infd.h		\
					\src\atlanta\define\syswarp.h		\
					\src\atlanta\define\sysnd.h		\
					\src\atlanta\define\sysmcr.h		\
							\src\atlanta\define\dma_blk.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
												\src\atlanta\define\message.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
    $(CC) $(OPTION) $(SRCSC)\scdmgrx.c

#$(OBJECT)\scdmgtx.obj:       $(SRCSC)\scdmgtx.c
#    $(CC) $(OPTION) $(SRCSC)\scdmgtx.c

$(OBJECT)\scdfunc.obj:       $(SRCSC)\scdfunc.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\sysdoc.h		\
				\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\syspcrx.h		\
							\src\atlanta\define\dma_blk.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
    $(CC) $(OPTION) $(SRCSC)\scdfunc.c

$(OBJECT)\SCDTXPIX.obj:       $(SRCSC)\SCDTXPIX.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
							\src\atlanta\define\mem_def.h		\
							\src\atlanta\define\dma_blk.h		\
							\src\atlanta\define\sysmax.h		\
										\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
											\src\cpu\sh7043_a\irom\define\def_tcb.h		\
												\src\atlanta\define\message.h		\
											\src\cpu\sh7043_a\irom\define\def_scb.h		\
											\src\cpu\sh7043_a\irom\define\def_semn.h		\
											\src\cpu\sh7043_a\irom\define\def_mbxn.h
#    $(CC) $(OPTION) $(SRCSC)\SCDTXPIX.c
    $(CC) $(OPTIONMS) $(SRCSC)\SCDTXPIX.c

$(OBJECT)\SCDCPH.obj:       $(SRCSC)\SCDCPH.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mem_pro.h		\
					\src\atlanta\ext_v\memertbl.h		\
						\src\atlanta\define\mem_def.h		\
						\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h		\
							\src\cpu\sh7043_a\irom\define\def_tcb.h		\
								\src\atlanta\define\message.h		\
							\src\cpu\sh7043_a\irom\define\def_scb.h		\
							\src\cpu\sh7043_a\irom\define\def_semn.h		\
							\src\cpu\sh7043_a\irom\define\def_mbxn.h		\
							\src\atlanta\define\dma_blk.h		\
							\src\atlanta\define\sysmax.h
   $(CC) $(OPTION) /l /sh=ob $(SRCSC)\SCDCPH.c
#   $(CC) $(OPTIONA2) $(SRCSC)\SCDCPH.c
#
#
$(OBJECT)\inifreep.obj :$(SRCSC)\inifreep.src
				$(ASM)	$(SRCSC)\inifreep.src $(ASM_OPT)
#
#
#$(OBJECT)\ini_sct.obj :$(SRCSC)\ini_sct.src
#				$(ASM)	$(SRCSC)\ini_sct.src $(ASM_OPT)
#
#以下アリロ用メイク By Y.Suzuki 1997/09/17
#
$(OBJECT)\ALRANDML.obj:       $(SRCAL)\ALRANDML.c
#   $(CC) $(OPTIONAD) $(SRCAL)\ALRANDML.c
   $(CC) $(OPTIONADSP) $(SRCAL)\ALRANDML.c
#
$(OBJECT)\ALRANDOM.obj:       $(SRCAL)\ALRANDOM.c
#   $(CC) $(OPTIONAD) $(SRCAL)\ALRANDOM.c
   $(CC) $(OPTIONADSP) $(SRCAL)\ALRANDOM.c
#
$(OBJECT)\DESCRDLL.obj:       $(SRCAL)\DESCRDLL.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scramdll.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\constant.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\config.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h		\
					\src\cpu\sh7043_a\scd\define\cph_def.h		\
						\src\atlanta\define\sysmax.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\readimg.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\utility.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\resource.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\setup.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\writeimg.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\getrect.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\getcode.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\trsnfrm.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\sortelm.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\desutil.h		\
				\src\cpu\sh7043_a\scd\define\cphpro.h		\
					\src\cpu\sh7043_a\scd\define\scd.h		\
						\src\atlanta\define\mem_def.h		\
					\src\cpu\sh7043_a\scd\ext_v\cphptbl.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\segment.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\upsidpcx.h
#   $(CC) $(OPTIONAD) $(SRCAL)\DESCRDLL.c
   $(CC) $(OPTIONADSP) $(SRCAL)\DESCRDLL.c
#
$(OBJECT)\DRAW.obj:       $(SRCAL)\DRAW.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scramdll.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\constant.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\config.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h		\
					\src\cpu\sh7043_a\scd\define\cph_def.h		\
						\src\atlanta\define\sysmax.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\utility.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\resource.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\draw.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\gnrl_mac.h
#   $(CC) $(OPTIONAD) $(SRCAL)\DRAW.c
   $(CC) $(OPTIONADSP) $(SRCAL)\DRAW.c
#
$(OBJECT)\DROPLINE.obj:       $(SRCAL)\DROPLINE.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scramdll.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\constant.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\config.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h		\
					\src\cpu\sh7043_a\scd\define\cph_def.h		\
						\src\atlanta\define\sysmax.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\descrdll.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\gnrl_mac.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\utility.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\resource.h
#   $(CC) $(OPTIONAD) $(SRCAL)\DROPLINE.c
   $(CC) $(OPTIONADSP) $(SRCAL)\DROPLINE.c
#
#$(OBJECT)\EMBED.obj:       $(SRCAL)\EMBED.c
#   $(CC) $(OPTIONAD) $(SRCAL)\EMBED.c
#
$(OBJECT)\EMBIO.obj:       $(SRCAL)\EMBIO.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scramdll.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\constant.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\config.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h		\
					\src\cpu\sh7043_a\scd\define\cph_def.h		\
						\src\atlanta\define\sysmax.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\gnrl_mac.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\resource.h		\
				\src\cpu\sh7043_a\scd\define\cphpro.h		\
					\src\cpu\sh7043_a\scd\define\scd.h		\
						\src\atlanta\define\mem_def.h		\
					\src\cpu\sh7043_a\scd\ext_v\cphptbl.h
#   $(CC) $(OPTIONAD) $(SRCAL)\EMBIO.c
   $(CC) $(OPTIONADSP) $(SRCAL)\EMBIO.c
#
$(OBJECT)\ENCRYPT.obj:       $(SRCAL)\ENCRYPT.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\utility.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\resource.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\encrypt.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\alrandom.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h
#   $(CC) $(OPTIONAD) $(SRCAL)\ENCRYPT.c
   $(CC) $(OPTIONADSP) $(SRCAL)\ENCRYPT.c
#
$(OBJECT)\ENCRYPT2.obj:       $(SRCAL)\ENCRYPT2.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\utility.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\resource.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\encrypt2.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\alrandml.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h
#   $(CC) $(OPTIONAD) $(SRCAL)\ENCRYPT2.c
   $(CC) $(OPTIONADSP) $(SRCAL)\ENCRYPT2.c
#
$(OBJECT)\FITPAGE.obj:       $(SRCAL)\FITPAGE.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scramdll.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\constant.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\config.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h		\
					\src\cpu\sh7043_a\scd\define\cph_def.h		\
						\src\atlanta\define\sysmax.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\gnrl_mac.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\utility.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\resource.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\readimg.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\setup.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\writeimg.h		\
				\src\cpu\sh7043_a\scd\define\cphpro.h		\
					\src\cpu\sh7043_a\scd\define\scd.h		\
						\src\atlanta\define\mem_def.h		\
					\src\cpu\sh7043_a\scd\ext_v\cphptbl.h
#   $(CC) $(OPTIONAD) $(SRCAL)\FITPAGE.c
   $(CC) $(OPTIONADSP) $(SRCAL)\FITPAGE.c
#
$(OBJECT)\GETCODE.obj:       $(SRCAL)\GETCODE.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scramdll.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\constant.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\config.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h		\
					\src\cpu\sh7043_a\scd\define\cph_def.h		\
						\src\atlanta\define\sysmax.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\descrdll.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\utility.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\resource.h		\
				\src\cpu\sh7043_a\scd\define\cphpro.h		\
					\src\cpu\sh7043_a\scd\define\scd.h		\
						\src\atlanta\define\mem_def.h		\
					\src\cpu\sh7043_a\scd\ext_v\cphptbl.h
   $(CC) $(OPTIONAD) $(SRCAL)\GETCODE.c
#   $(CC) $(OPTIONADSP) $(SRCAL)\GETCODE.c エラーになる
#
$(OBJECT)\GETRECT.obj:       $(SRCAL)\GETRECT.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scramdll.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\constant.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\config.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h		\
					\src\cpu\sh7043_a\scd\define\cph_def.h		\
						\src\atlanta\define\sysmax.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\utility.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\resource.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\readimg.h		\
				\src\cpu\sh7043_a\scd\define\cphpro.h		\
					\src\cpu\sh7043_a\scd\define\scd.h		\
						\src\atlanta\define\mem_def.h		\
					\src\cpu\sh7043_a\scd\ext_v\cphptbl.h
#   $(CC) $(OPTIONAD) $(SRCAL)\GETRECT.c
   $(CC) $(OPTIONADSP) $(SRCAL)\GETRECT.c
#
$(OBJECT)\MATCH.obj:       $(SRCAL)\MATCH.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\constant.h
#   $(CC) $(OPTIONAD) $(SRCAL)\MATCH.c
   $(CC) $(OPTIONADSP) $(SRCAL)\MATCH.c
#
$(OBJECT)\MURATAFC.obj:       $(SRCAL)\MURATAFC.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\cpu\sh7043_a\scd\ext_v\cph_data.h		\
					\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\message.h		\
					\src\cpu\sh7043_a\scd\define\cph_def.h		\
						\src\atlanta\define\sysmax.h		\
					\src\cpu\sh7043_a\scd\define\scd.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\muratafc.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\resource.h		\
				\src\cpu\sh7043_a\scd\define\cphpro.h		\
					\src\cpu\sh7043_a\scd\ext_v\cphptbl.h
#   $(CC) $(OPTIONAD) $(SRCAL)\MURATAFC.c
   $(CC) $(OPTIONADSP) $(SRCAL)\MURATAFC.c
#
$(OBJECT)\SCRAMDLL.obj:       $(SRCAL)\SCRAMDLL.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scramdll.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\constant.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\config.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h		\
					\src\cpu\sh7043_a\scd\define\cph_def.h		\
						\src\atlanta\define\sysmax.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\readimg.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\utility.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\resource.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scrutil.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\draw.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\setup.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\writeimg.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\getrect.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\gnrl_mac.h		\
				\src\cpu\sh7043_a\scd\define\cphpro.h		\
					\src\cpu\sh7043_a\scd\define\scd.h		\
						\src\atlanta\define\mem_def.h		\
					\src\cpu\sh7043_a\scd\ext_v\cphptbl.h
#   $(CC) $(OPTIONAD) $(SRCAL)\SCRAMDLL.c
   $(CC) $(OPTIONADSP) $(SRCAL)\SCRAMDLL.c
#
$(OBJECT)\SEGMENT.obj:       $(SRCAL)\SEGMENT.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scramdll.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\constant.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\config.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h		\
					\src\cpu\sh7043_a\scd\define\cph_def.h		\
						\src\atlanta\define\sysmax.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\descrdll.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\utility.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\resource.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\readimg.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\match.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\dropline.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\desutil.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\setup.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\writeimg.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\gnrl_mac.h		\
				\src\cpu\sh7043_a\scd\define\cphpro.h		\
					\src\cpu\sh7043_a\scd\define\scd.h		\
						\src\atlanta\define\mem_def.h		\
					\src\cpu\sh7043_a\scd\ext_v\cphptbl.h
#   $(CC) $(OPTIONAD) $(SRCAL)\SEGMENT.c
   $(CC) $(OPTIONADSP) $(SRCAL)\SEGMENT.c
#
$(OBJECT)\SETUP.obj:       $(SRCAL)\SETUP.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scramdll.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\constant.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\config.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h		\
					\src\cpu\sh7043_a\scd\define\cph_def.h		\
						\src\atlanta\define\sysmax.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\utility.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\resource.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\encrypt.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\encrypt2.h		\
				\src\cpu\sh7043_a\scd\define\cphpro.h		\
					\src\cpu\sh7043_a\scd\define\scd.h		\
						\src\atlanta\define\mem_def.h		\
					\src\cpu\sh7043_a\scd\ext_v\cphptbl.h
   $(CC) $(OPTIONAD) $(SRCAL)\SETUP.c
#   $(CC) $(OPTIONADSP) $(SRCAL)\SETUP.c /* ここからコールするcallocでアドレスエラーする By Y.Suzuki 1998/01/09
#
$(OBJECT)\SORTELM.obj:       $(SRCAL)\SORTELM.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scramdll.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\constant.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\config.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h		\
					\src\cpu\sh7043_a\scd\define\cph_def.h		\
						\src\atlanta\define\sysmax.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\descrdll.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\utility.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\resource.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\gnrl_mac.h		\
				\src\cpu\sh7043_a\scd\define\cphpro.h		\
					\src\cpu\sh7043_a\scd\define\scd.h		\
						\src\atlanta\define\mem_def.h		\
					\src\cpu\sh7043_a\scd\ext_v\cphptbl.h
#   $(CC) $(OPTIONAD) $(SRCAL)\SORTELM.c
   $(CC) $(OPTIONADSP) $(SRCAL)\SORTELM.c
#
$(OBJECT)\TRNSFRM.obj:       $(SRCAL)\TRNSFRM.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scramdll.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\constant.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\config.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h		\
					\src\cpu\sh7043_a\scd\define\cph_def.h		\
						\src\atlanta\define\sysmax.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\descrdll.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\utility.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\resource.h		\
				\src\cpu\sh7043_a\scd\define\cphpro.h		\
					\src\cpu\sh7043_a\scd\define\scd.h		\
						\src\atlanta\define\mem_def.h		\
					\src\cpu\sh7043_a\scd\ext_v\cphptbl.h
   $(CC) $(OPTIONAD) $(SRCAL)\TRNSFRM.c
#   $(CC) $(OPTIONADSP) $(SRCAL)\TRNSFRM.c スタックオーバーフローしたんで最適化やめてみる
#   $(CC) $(OPTIONADSP) $(SRCAL)\TRNSFRM.c
#
$(OBJECT)\UTILITY.obj:       $(SRCAL)\UTILITY.c	\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\utility.h		\
					\src\cpu\sh7043_a\scd\aliroo\define\resource.h		\
				\src\cpu\sh7043_a\scd\aliroo\define\scrdlapi.h
				progress.h
#   $(CC) $(OPTIONAD) $(SRCAL)\UTILITY.c
   $(CC) $(OPTIONADSP) $(SRCAL)\UTILITY.c
#
$(OBJECT)\CONSTANT.obj:       $(SRCAL)\CONSTANT.c
#   $(CC) $(OPTIONAD) $(SRCAL)\CONSTANT.c
   $(CC) $(OPTIONADSP) $(SRCAL)\CONSTANT.c
#
#-----------------------------------------------------------------------------
#	ｿﾌﾄｺｰﾃﾞｯｸﾃｰﾌﾞﾙ By Y.Suzuki 1998/2/18
#	フラッシュＲＯＭから参照する、拡張ＲＯＭモジュールアドレス固定用
#-----------------------------------------------------------------------------
$(OBJECT)\alrptbl.obj:	  $(DEFVSC)\alrptbl.c
		$(CC)	$(OPTION) $(DEFVSC)\alrptbl.c
#
#-----------------------------------------------------------------------------
#	ｿﾌﾄｺｰﾃﾞｯｸﾃｰﾌﾞﾙ By Y.Suzuki 1998/2/18
#	拡張ＲＯＭから参照する、フラッシュＲＯＭモジュールアドレス固定用
#-----------------------------------------------------------------------------
$(OBJECT)\cphptbl.obj:	  $(DEFVSC)\cphptbl.c
		$(CC)	$(OPTION) $(DEFVSC)\cphptbl.c
#
#-----------------------------------------------------------------------------
#	ｿﾌﾄｺｰﾃﾞｯｸﾃｰﾌﾞﾙ By Y.Suzuki 1998/2/18
#	拡張ＲＯＭから参照する、3月9日以降追加されるALIROO 大域変数
#-----------------------------------------------------------------------------
$(OBJECT)\alr_data.obj:	  $(DEFVSC)\alr_data.c
		$(CC)	$(OPTION) $(DEFVSC)\alr_data.c
#

#-----------------------------------------------------------------------------
#   ｿﾌﾄｺｰﾃﾞｯｸ用ﾃﾞｰﾀﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
$(OBJECT)\scd_data.obj:       $(DEFVSC)\scd_data.c	\
				\src\atlanta\define\product.h		\
					\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\message.h
    $(CC) $(OPTION3) $(DEFVSC)\scd_data.c
#-----------------------------------------------------------------------------
#   ｿﾌﾄｺｰﾃﾞｯｸ用rlﾊﾞｯﾌｧﾒｲｸ部
#-----------------------------------------------------------------------------
$(OBJECT)\scdrlbuf.obj:       $(DEFVSC)\scdrlbuf.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\sysdoc.h		\
					\src\atlanta\define\mem_def.h
#新ﾏｽｸ変更 ｿｰｽ内部でｾｸｼｮﾝ名をつけます
#    $(CC) $(OPTION2) $(DEFVSC)\scdrlbuf.c
    $(CC) $(OPTION) $(DEFVSC)\scdrlbuf.c
#-----------------------------------------------------------------------------
#   暗号化受信ﾃﾞｰﾀﾒｲｸ部 By Y.Suzuki 1997/06/17
#-----------------------------------------------------------------------------
$(OBJECT)\cph_data.obj:       $(DEFVSC)\cph_data.c	\
					\src\atlanta\define\product.h		\
					\src\atlanta\define\sysmax.h		\
				\src\atlanta\define\mem_def.h
    $(CC) $(OPTION) $(DEFVSC)\cph_data.c
#------------------------------------------------------------------------------------------
#	スクランブルモジュールの使用するCライブラリのため Ｂセクションの先頭を示すシンボルです。
#------------------------------------------------------------------------------------------
$(OBJECT)\ini_sct.obj :$(SRCSC)\ini_sct.src
				$(ASM)	$(SRCSC)\ini_sct.src $(ASM_OPT)
#-----------------------------------------------------------------------------
#	ｿﾌﾄｺｰﾃﾞｯｸﾃｰﾌﾞﾙ
#-----------------------------------------------------------------------------
$(OBJECT)\scd_tbl.obj:	  $(DEFVSC)\scd_tbl.c	\
				\src\atlanta\define\product.h		\
					\src\atlanta\define\mem_def.h		\
					\src\atlanta\define\sysdoc.h		\
					\src\atlanta\define\message.h
#新ﾏｽｸ変更 ﾒﾓﾘ管理のCONSTを追加し、外ROMに置くのでｿｰｽ内でｾｸｼｮﾝをつけます
#		$(CC)	$(OPTIONS) $(DEFVSC)\scd_tbl.c
		$(CC)	$(OPTION) $(DEFVSC)\scd_tbl.c
#
$(OBJECT)\reductbl.obj :	$(DEFVSC)\reductbl.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTIONS2) $(DEFVSC)\reductbl.c
#-----------------------------------------------------------------------------
#	ｿﾌﾄｺｰﾃﾞｯｸﾃｰﾌﾞﾙ By Y.Suzuki 1997/03/18
#	外部ＲＯＭから参照する、内部ＲＯＭモジュールアドレス固定用
#-----------------------------------------------------------------------------
$(OBJECT)\scdptbl.obj:	  $(DEFVSC)\scdptbl.c	\
				\src\atlanta\define\product.h		\
						\src\atlanta\define\mem_def.h
		$(CC)	$(OPTION) $(DEFVSC)\scdptbl.c
#
