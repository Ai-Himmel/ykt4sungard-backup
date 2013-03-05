#------------------------------------------------------------------------
#   POPLAR/ANZU_L   メモリ管理部(MEM)のメイクファイル
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
LNK         = lnk /subcommand=\src\atlanta\make\MEM.sub
#-----------------------------------------------------------------------------
#   引数を定義
#-----------------------------------------------------------------------------
#!if ("$(MODEL)" != "POPLAR_H")
#OPTION      = /op=0 /deb /def=($(MODEL),$(COUNTRY)) /cp=sh2
#!endif
!if ("$(MODEL)" == "POPLAR_H")
OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!else
OPTION      = /op=0 /deb /def=($(MODEL),$(COUNTRY)) /cp=sh2
!endif

ASM_OPT     = /cpu=$(CPU_OPT) /debug /object=$*.obj
#-----------------------------------------------------------------------------
#   オブジェクトディレクトリを定義
#-----------------------------------------------------------------------------
OBJECT      = \src\atlanta\$(MODEL)\work\$(COUNTRY)
#
#-----------------------------------------------------------------------------
#	桐用ﾒﾓﾘ管理ﾓｼﾞｭｰﾙのﾘﾝｸを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\mem.lnk:   \src\atlanta\make\mem.SUB	\
			$(OBJECT)\memcheck.obj					\
			$(OBJECT)\memclear.obj					\
			$(OBJECT)\memcount.obj					\
			$(OBJECT)\memdual.obj					\
			$(OBJECT)\memfat.obj					\
			$(OBJECT)\memread.obj					\
			$(OBJECT)\memwrite.obj
		$(LNK)
#-----------------------------------------------------------------------------
#	ﾒﾓﾘ管理ﾓｼﾞｭｰﾙのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
#
$(OBJECT)\memcheck.obj:	$(SRC)\memcheck.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\mem_pro.h		\
					\src\atlanta\ext_v\memertbl.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\mem_data.h		\
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
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h
		$(CC) $(OPTION) $(SRC)\memcheck.c
#
$(OBJECT)\memclear.obj:	$(SRC)\memclear.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\man_pro.h		\
				\src\atlanta\define\mem_pro.h		\
					\src\atlanta\ext_v\memertbl.h		\
				\src\atlanta\define\mem_def.h		\
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
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h		\
				\src\atlanta\ext_v\mem_data.h
		$(CC) $(OPTION) $(SRC)\memclear.c
#
$(OBJECT)\memcount.obj:	$(SRC)\memcount.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\mem_pro.h		\
					\src\atlanta\ext_v\memertbl.h		\
				\src\atlanta\define\mem_def.h		\
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
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h		\
				\src\atlanta\ext_v\mem_data.h
		$(CC) $(OPTION) $(SRC)\memcount.c
#
$(OBJECT)\memdual.obj:	$(SRC)\memdual.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\mem_pro.h		\
					\src\atlanta\ext_v\memertbl.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\mem_data.h		\
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
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h
		$(CC) $(OPTION) $(SRC)\memdual.c
#
$(OBJECT)\memfat.obj:	$(SRC)\memfat.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\mem_pro.h		\
					\src\atlanta\ext_v\memertbl.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\param.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
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
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h		\
				\src\atlanta\ext_v\mem_data.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
				\src\atlanta\define\unisw_h.h
		$(CC) $(OPTION) $(SRC)\memfat.c
#
$(OBJECT)\memread.obj:	$(SRC)\memread.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\mem_pro.h		\
					\src\atlanta\ext_v\memertbl.h		\
				\src\atlanta\ext_v\mem_data.h		\
					\src\atlanta\define\MEM_DEF.H		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
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
					\src\atlanta\define\sysfcode.h		\
					\src\atlanta\define\syspcrx.h		\
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\dma_def.h		\
					\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\define\dma_blk.h		\
				\src\atlanta\define\mntsw_a.h		\
				\src\atlanta\sh7043\define\def_evtn.h
		$(CC) $(OPTION) $(SRC)\memread.c
#
$(OBJECT)\memwrite.obj:	$(SRC)\memwrite.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\cmn_pro.h		\
					\src\atlanta\define\timer10.h		\
					\src\atlanta\define\atd_def.h		\
					\src\atlanta\define\time.h		\
					\src\atlanta\define\sysmcopy.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\mem_pro.h		\
					\src\atlanta\ext_v\memertbl.h		\
				\src\atlanta\define\mem_def.h		\
				\src\atlanta\define\sys_stat.h		\
				\src\atlanta\ext_v\mem_data.h		\
				\src\atlanta\ext_v\sys_data.h		\
					\src\atlanta\define\message.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysdblk.h		\
					\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysjrnl.h		\
					\src\atlanta\define\fip_def.h		\
					\src\atlanta\define\sys_opt.h		\
					\src\atlanta\define\sysdisp.h		\
					\src\atlanta\define\sysscan.h		\
				\src\atlanta\ext_v\BKUPRAM.H		\
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
					\src\atlanta\define\syskey.h		\
					\src\atlanta\define\syscph.h		\
					\src\atlanta\define\dpr_def.h		\
				\src\atlanta\define\dma_pro.h		\
				\src\atlanta\define\dma_def.h		\
					\src\atlanta\sh7043\define\sh_port.h		\
				\src\atlanta\define\dma_blk.h		\
				\src\atlanta\define\mntsw_a.h		\
				\src\atlanta\sh7043\define\def_evtn.h
		$(CC) $(OPTION) $(SRC)\memwrite.c
#
