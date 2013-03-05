#------------------------------------------------------------------------
#   POPLAR/ANZU_L   リアルタイムモニター(MON)のメイクファイル
#   1996/10/15		Transplanted from \src\kobe\anzu\sh\make By T.Nose
#------------------------------------------------------------------------

# =============================================================================
# =  ｻﾌｨｯｸｽ ﾘｽﾄ                                                               #
# =============================================================================
.SUFFIXES: .obj .c .src

# =============================================================================
# =  ﾏｸﾛ定義                                                                  #
# =============================================================================
DEFINE		= \src\atlanta\define
EXT_V		= \src\atlanta\ext_v
MON_SH		= \src\cpu\sh7043_a\irom\mon
DEFINE_SH	= \src\cpu\sh7043_a\irom\define
EXTV_SH		= \src\cpu\sh7043_a\irom\ext_v
DEFV_SH		= \src\cpu\sh7043_a\irom\def_v
POPB_SRC	= \src\atlanta\poplar_b\src
POPH_SRC	= \src\atlanta\poplar_h\src
SAKAKI_SRC	= \src\atlanta\sakaki\src

#-----------------------------------------------------------------------------
#   ｺﾏﾝﾄﾞ名を定義
#-----------------------------------------------------------------------------
CC          = shc
ASM         = asmsh
OPTION      = /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
ASM_OPT_DE  = /cpu=sh2 /debug /object=$*.obj
ASM_OPT     = /cpu=sh2 /object=$*.obj
ASM_OPT_IF  = /cpu=sh2 /debug /object=$*.obj /def=MODEL_TYPE=$(MODEL),CTRY_TYPE=$(COUNTRY) /* WDT追加O.Oshima 2004/08/25 */
LNK         = lnk /subcommand=\src\cpu\sh7043_a\make\mon.sub
OBJECT      = \src\atlanta\$(MODEL)\work\$(COUNTRY)

# =============================================================================
# =  推論定義                                                                 #
# =============================================================================
.c.obj:
	$(CC) $(OPTION) $<

.src.obj:
	$(ASM) $< $(ASM_OPT)

# =============================================================================
# =  ﾓｼﾞｭｰﾙ ﾒｲｸ                                                               #
# =============================================================================
mon2.lnk:	\src\cpu\sh7043_a\make\mon.sub	\
				$(OBJECT)\mon_init.obj		\
				$(OBJECT)\cre_redy.obj		\
				$(OBJECT)\del_redy.obj		\
				$(OBJECT)\schedule.obj		\
				$(OBJECT)\rdy_func.obj		\
				$(OBJECT)\cre_tsk.obj		\
				$(OBJECT)\del_tsk.obj		\
				$(OBJECT)\wai_tsk.obj		\
				$(OBJECT)\exi_tsk.obj		\
				$(OBJECT)\cre_sem.obj		\
				$(OBJECT)\del_sem.obj		\
				$(OBJECT)\wai_sem.obj		\
				$(OBJECT)\sig_sem.obj		\
				$(OBJECT)\chk_sem.obj		\
				$(OBJECT)\idet_evt.obj		\
				$(OBJECT)\det_evt.obj		\
				$(OBJECT)\wai_evt.obj		\
				$(OBJECT)\wai_1sht.obj		\
				$(OBJECT)\cre_mbx.obj		\
				$(OBJECT)\del_mbx.obj		\
				$(OBJECT)\snd_msg.obj		\
				$(OBJECT)\rcv_msg.obj		\
				$(OBJECT)\chk_mbx.obj		\
				$(OBJECT)\mon_itim.obj		\
				$(OBJECT)\mon_err.obj		\
				$(OBJECT)\wup_tsk.obj		\
				$(OBJECT)\mon_timi.obj		\
				$(OBJECT)\mon_time.obj		\
				$(OBJECT)\chk_rcv.obj		\
				$(OBJECT)\chksemvl.obj
			$(LNK)

# =============================================================================
# =  ｺﾝﾊﾟｲﾙ                                                                   #
# =============================================================================
$(OBJECT)\mon_init.obj :$(MON_SH)\mon_init.c		\
				\src\atlanta\define\product.h		\
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
				$(CC) $(OPTION) $(MON_SH)\mon_init.c

$(OBJECT)\cre_redy.obj :$(MON_SH)\cre_redy.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\cre_redy.src $(ASM_OPT)

$(OBJECT)\del_redy.obj :$(MON_SH)\del_redy.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\del_redy.src $(ASM_OPT)

# # 割込み禁止時間測定 O.Kimoto 1998/02/12
# !if ("$(MODEL)" == "POPLAR_H") && ("$(COUNTRY)" == "JPN")
# $(OBJECT)\schedule.obj :$(POPH_SRC)\schedule.src		\
# 						$(DEFINE_SH)\def_mon.hdr		\
# 						$(DEFINE_SH)\mon_mac.hdr		\
# 						$(EXTV_SH)\extv_mon.hdr
# 				$(ASM)	$(POPH_SRC)\schedule.src $(ASM_OPT)
# !else
# $(OBJECT)\schedule.obj :$(MON_SH)\schedule.src		\
# 						$(DEFINE_SH)\def_mon.hdr		\
# 						$(DEFINE_SH)\mon_mac.hdr		\
# 						$(EXTV_SH)\extv_mon.hdr
# 				$(ASM)	$(MON_SH)\schedule.src $(ASM_OPT)
# !endif
$(OBJECT)\schedule.obj :$(MON_SH)\schedule.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\schedule.src $(ASM_OPT)

$(OBJECT)\rdy_func.obj :$(MON_SH)\rdy_func.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\rdy_func.src $(ASM_OPT)

$(OBJECT)\cre_tsk.obj :$(MON_SH)\cre_tsk.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\cre_tsk.src $(ASM_OPT)

$(OBJECT)\del_tsk.obj :$(MON_SH)\del_tsk.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\del_tsk.src $(ASM_OPT)

$(OBJECT)\wai_tsk.obj :$(MON_SH)\wai_tsk.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\wai_tsk.src $(ASM_OPT)

$(OBJECT)\exi_tsk.obj :$(MON_SH)\exi_tsk.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\exi_tsk.src $(ASM_OPT)

$(OBJECT)\cre_sem.obj :$(MON_SH)\cre_sem.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\cre_sem.src $(ASM_OPT)

$(OBJECT)\del_sem.obj :$(MON_SH)\del_sem.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\del_sem.src $(ASM_OPT)

# # 割込み禁止時間測定 O.Kimoto 1998/02/12
# !if ("$(MODEL)" == "POPLAR_H") && ("$(COUNTRY)" == "JPN")
# $(OBJECT)\wai_sem.obj :$(POPH_SRC)\wai_sem.src		\
# 						$(DEFINE_SH)\def_mon.hdr		\
# 						$(DEFINE_SH)\mon_mac.hdr		\
# 						$(EXTV_SH)\extv_mon.hdr
# 				$(ASM)	$(POPH_SRC)\wai_sem.src $(ASM_OPT)
# !else
# $(OBJECT)\wai_sem.obj :$(MON_SH)\wai_sem.src		\
# 						$(DEFINE_SH)\def_mon.hdr		\
# 						$(DEFINE_SH)\mon_mac.hdr		\
# 						$(EXTV_SH)\extv_mon.hdr
# 				$(ASM)	$(MON_SH)\wai_sem.src $(ASM_OPT)
# !endif
$(OBJECT)\wai_sem.obj :$(MON_SH)\wai_sem.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\wai_sem.src $(ASM_OPT)

# # 割込み禁止時間測定 O.Kimoto 1998/02/12
# !if ("$(MODEL)" == "POPLAR_H") && ("$(COUNTRY)" == "JPN")
# $(OBJECT)\sig_sem.obj :$(POPH_SRC)\sig_sem.src		\
# 						$(DEFINE_SH)\def_mon.hdr		\
# 						$(DEFINE_SH)\mon_mac.hdr		\
# 						$(EXTV_SH)\extv_mon.hdr
# 				$(ASM)	$(POPH_SRC)\sig_sem.src $(ASM_OPT)
# !else
# $(OBJECT)\sig_sem.obj :$(MON_SH)\sig_sem.src		\
# 						$(DEFINE_SH)\def_mon.hdr		\
# 						$(DEFINE_SH)\mon_mac.hdr		\
# 						$(EXTV_SH)\extv_mon.hdr
# 				$(ASM)	$(MON_SH)\sig_sem.src $(ASM_OPT)
# !endif
$(OBJECT)\sig_sem.obj :$(MON_SH)\sig_sem.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\sig_sem.src $(ASM_OPT)

$(OBJECT)\chk_sem.obj :$(MON_SH)\chk_sem.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\chk_sem.src $(ASM_OPT)

$(OBJECT)\idet_evt.obj :$(MON_SH)\idet_evt.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\idet_evt.src $(ASM_OPT)

# # 割込み禁止時間測定 O.Kimoto 1998/02/12
# !if ("$(MODEL)" == "POPLAR_H") && ("$(COUNTRY)" == "JPN")
# $(OBJECT)\det_evt.obj :$(POPH_SRC)\det_evt.src		\
# 						$(DEFINE_SH)\def_mon.hdr		\
# 						$(DEFINE_SH)\mon_mac.hdr		\
# 						$(EXTV_SH)\extv_mon.hdr
# 				$(ASM)	$(POPH_SRC)\det_evt.src $(ASM_OPT)
# !else
# $(OBJECT)\det_evt.obj :$(MON_SH)\det_evt.src		\
# 						$(DEFINE_SH)\def_mon.hdr		\
# 						$(DEFINE_SH)\mon_mac.hdr		\
# 						$(EXTV_SH)\extv_mon.hdr
# 				$(ASM)	$(MON_SH)\det_evt.src $(ASM_OPT)
# !endif
$(OBJECT)\det_evt.obj :$(MON_SH)\det_evt.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\det_evt.src $(ASM_OPT)

$(OBJECT)\wai_evt.obj :$(MON_SH)\wai_evt.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\wai_evt.src $(ASM_OPT)

$(OBJECT)\wai_1sht.obj :$(MON_SH)\wai_1sht.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\wai_1sht.src $(ASM_OPT)

$(OBJECT)\cre_mbx.obj :$(MON_SH)\cre_mbx.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\cre_mbx.src $(ASM_OPT)

$(OBJECT)\del_mbx.obj :$(MON_SH)\del_mbx.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\del_mbx.src $(ASM_OPT)

$(OBJECT)\snd_msg.obj :$(MON_SH)\snd_msg.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\snd_msg.src $(ASM_OPT)

$(OBJECT)\rcv_msg.obj :$(MON_SH)\rcv_msg.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\rcv_msg.src $(ASM_OPT)

$(OBJECT)\chk_mbx.obj :$(MON_SH)\chk_mbx.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\chk_mbx.src $(ASM_OPT)

$(OBJECT)\mon_itim.obj :$(MON_SH)\mon_itim.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\mon_itim.src $(ASM_OPT)

$(OBJECT)\mon_err.obj :$(MON_SH)\mon_err.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\mon_err.src $(ASM_OPT_DE)

$(OBJECT)\wup_tsk.obj :$(MON_SH)\wup_tsk.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(DEFINE_SH)\mon_mac.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\wup_tsk.src $(ASM_OPT)

$(OBJECT)\mon_timi.obj :$(MON_SH)\mon_timi.c		\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\irom\define\sh_sys.h		\
					\src\atlanta\hinoki\define\hino_sys.h		\
				\src\atlanta\sh7043\define\sh_sys.h
				$(CC) $(OPTION) /section=p=MON $(MON_SH)\mon_timi.c

$(OBJECT)\chk_rcv.obj :$(MON_SH)\chk_rcv.src		\
						$(DEFINE_SH)\def_mon.hdr		\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\chk_rcv.src $(ASM_OPT)

$(OBJECT)\mon_time.obj :$(MON_SH)\mon_time.c		\
				\src\atlanta\define\product.h		\
				\src\cpu\sh7043_a\irom\define\sh_sys.h		\
					\src\atlanta\hinoki\define\hino_sys.h		\
				\src\atlanta\sh7043\define\sh_sys.h
				$(CC) $(OPTION) $(MON_SH)\mon_time.c

$(OBJECT)\chksemvl.obj :$(MON_SH)\chksemvl.src		\
						$(DEFINE_SH)\def_mon.hdr	\
						$(EXTV_SH)\extv_mon.hdr
				$(ASM)	$(MON_SH)\chksemvl.src $(ASM_OPT)
