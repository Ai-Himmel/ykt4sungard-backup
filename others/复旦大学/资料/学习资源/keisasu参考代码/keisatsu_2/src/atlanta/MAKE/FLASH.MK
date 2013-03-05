#------------------------------------------------------------------------
#	POPLAR_B/POPLAR_L/ANZU_L	フラッシュメモリ部のメイクファイル
#	1997/04/24		Transplanted from \src\atlanta\make By M.Kuwahara
#------------------------------------------------------------------------
SRC			= \src\ATLANTA\FLA\src
DEFV		= \src\ATLANTA\FLA\def_v
SRC2		= \src\ATLANTA\FLA\src2

#-----------------------------------------------------------------------------
#	コマンド名を定義
#-----------------------------------------------------------------------------
CC			= shc
ASM			= asmsh
!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU") || ("$(MODEL)" == "HINOKI2")) || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
LNK			= lnk /subcommand=\src\atlanta\make\iu_flash.sub
!else
LNK			= lnk /subcommand=\src\ATLANTA\make\flash.sub
!endif

#-----------------------------------------------------------------------------
#	引数を定義
#-----------------------------------------------------------------------------
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
S_OPTION	= /op=1 /deb /cp=$(CPU_OPT) /def=($(MODEL),$(COUNTRY),$(CPU))
ASM_OPT		= /cpu=sh2 /debug /object=$*.obj

#-----------------------------------------------------------------------------
#	オブジェクトディレクトリを定義
#-----------------------------------------------------------------------------
OBJECT		= \src\atlanta\$(MODEL)\work\$(COUNTRY)
#OBJECT		= \src\ATLANTA\FLA\work\$(MODEL)

#-----------------------------------------------------------------------------
#	オペレーションモジュールのリンクを定義
#-----------------------------------------------------------------------------
$(OBJECT)\flash.lnk:	\src\ATLANTA\make\iu_flash.sub	\
#			$(OBJECT)\vector.obj	\
#			$(OBJECT)\rom_tbl.obj	\
#			$(OBJECT)\sys_data.obj	\
!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU") || ("$(MODEL)" == "HINOKI2")) || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
			$(OBJECT)\Flaenty.obj	\
!else
			$(OBJECT)\Fla_enty.obj	\
!endif
			$(OBJECT)\Flaicpu.obj	\
#			$(OBJECT)\Flatenty.obj	\
#			$(OBJECT)\int_err.obj	\
			$(OBJECT)\fla_pol.obj	\
			$(OBJECT)\fla_sum.obj	\
			$(OBJECT)\fla_tgl.obj	\
			$(OBJECT)\fla_auto.obj	\
			$(OBJECT)\fla_cers.obj	\
			$(OBJECT)\fla_main.obj	\
			$(OBJECT)\fla_pro.obj	\
			$(OBJECT)\fla_rsm.obj	\
			$(OBJECT)\fla_rst0.obj	\
			$(OBJECT)\fla_rst1.obj	\
			$(OBJECT)\fla_sers.obj	\
			$(OBJECT)\fla_sus.obj	\
			$(OBJECT)\fla_tbl.obj	\
			$(OBJECT)\Fla_itim.obj	\
			$(OBJECT)\Fla_buzz.obj	\
			$(OBJECT)\Fla_io.obj	\
			$(OBJECT)\Fla_iorw.obj	\
			$(OBJECT)\Fla_str.obj	\
			$(OBJECT)\Fla_sub.obj	\
			$(OBJECT)\Fla_oves.obj	\
			$(OBJECT)\Fla_sube.obj	\
#!if ("$(MODEL)" != "POPLAR_H")
#			$(OBJECT)\Fla_lcda.obj
#!endif
#!if ("$(MODEL)" == "POPLAR_H")
#			$(OBJECT)\Fla_lcdk.obj
!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU") || ("$(MODEL)" == "HINOKI2")) || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
			$(OBJECT)\hino_int.obj	\
			$(OBJECT)\iu_uniq.obj
!else
			$(OBJECT)\Fla_lcd.obj
!endif
#			$(OBJECT)\LCD_buf.obj
#!endif
		$(LNK)

#-----------------------------------------------------------------------------
#	オペレーションモジュールのメイクファイル部
#-----------------------------------------------------------------------------
#$(OBJECT)\vector.obj:	$(DEFV)\vector.c	\
#				\src\atlanta\define\product.h
#		$(CC) $(OPTION) /section=c=VECTOR $(DEFV)\vector.c
#
#$(OBJECT)\rom_tbl.obj:	$(DEFV)\rom_tbl.c	\
#				\src\atlanta\define\product.h
#		$(CC) $(OPTION) $(DEFV)\rom_tbl.c
#
#$(OBJECT)\sys_data.obj:	$(DEFV)\sys_data.c
#		$(CC) $(OPTION) $(DEFV)\sys_data.c
#
!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU") || ("$(MODEL)" == "HINOKI2")) || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
$(OBJECT)\Flaenty.obj:	$(SRC)\Flaenty.src
		$(ASM) $(SRC)\Flaenty.src $(ASM_OPT)
#
!else
$(OBJECT)\Fla_enty.obj:	$(SRC)\Fla_enty.src
		$(ASM) $(SRC)\Fla_enty.src $(ASM_OPT)
#
!endif
$(OBJECT)\Flaicpu.obj:	$(SRC)\Flaicpu.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\Flaicpu.c
#
#$(OBJECT)\Flatenty.obj:	$(SRC)\Flatenty.src
#		$(ASM) $(SRC)\Flatenty.src $(ASM_OPT)
#
#$(OBJECT)\int_err.obj:	$(SRC)\int_err.src
#		$(ASM) $(SRC)\int_err.src $(ASM_OPT)
#
$(OBJECT)\fla_pol.obj:	$(SRC)\fla_pol.c	\
				\src\atlanta\define\product.h		\
				\src\ATLANTA\FLA\define\fla_pro.h		\
				\src\ATLANTA\FLA\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_pol.c
#
$(OBJECT)\fla_sum.obj:	$(SRC)\fla_sum.c	\
				\src\atlanta\define\product.h		\
				\src\ATLANTA\FLA\define\fla_pro.h		\
				\src\ATLANTA\FLA\define\fla_def.h		\
				\src\ATLANTA\FLA\ext_v\fla_tbl.h
		$(CC) $(OPTION) $(SRC)\fla_sum.c
#
$(OBJECT)\fla_tgl.obj:	$(SRC)\fla_tgl.c	\
				\src\atlanta\define\product.h		\
				\src\ATLANTA\FLA\define\fla_pro.h		\
				\src\ATLANTA\FLA\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_tgl.c
#
$(OBJECT)\fla_auto.obj:	$(SRC)\fla_auto.c	\
				\src\atlanta\define\product.h		\
				\src\ATLANTA\FLA\define\fla_pro.h		\
				\src\ATLANTA\FLA\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_auto.c
#
$(OBJECT)\fla_cers.obj:	$(SRC)\fla_cers.c	\
				\src\atlanta\define\product.h		\
				\src\ATLANTA\FLA\define\fla_pro.h		\
				\src\ATLANTA\FLA\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_cers.c
#
$(OBJECT)\fla_main.obj:	$(SRC)\fla_main.c	\
				\src\atlanta\define\product.h		\
				\src\ATLANTA\FLA\define\fla_pro.h		\
				\src\ATLANTA\FLA\define\fla_def.h		\
				\src\ATLANTA\FLA\ext_v\fla_tbl.h		\
				\src\ATLANTA\FLA\define\sys_pro.h		\
				\src\ATLANTA\FLA\define\sys_def.h
		$(CC) $(OPTION) $(SRC)\fla_main.c
#
$(OBJECT)\fla_pro.obj:	$(SRC)\fla_pro.c	\
				\src\atlanta\define\product.h		\
				\src\ATLANTA\FLA\define\fla_pro.h		\
				\src\ATLANTA\FLA\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_pro.c
#
$(OBJECT)\fla_rsm.obj:	$(SRC)\fla_rsm.c	\
				\src\atlanta\define\product.h		\
				\src\ATLANTA\FLA\define\fla_pro.h		\
				\src\ATLANTA\FLA\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_rsm.c
#
$(OBJECT)\fla_rst0.obj:	$(SRC)\fla_rst0.c	\
				\src\atlanta\define\product.h		\
				\src\ATLANTA\FLA\define\fla_pro.h		\
				\src\ATLANTA\FLA\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_rst0.c
#
$(OBJECT)\fla_rst1.obj:	$(SRC)\fla_rst1.c	\
				\src\atlanta\define\product.h		\
				\src\ATLANTA\FLA\define\fla_pro.h		\
				\src\ATLANTA\FLA\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_rst1.c
#
$(OBJECT)\fla_sers.obj:	$(SRC)\fla_sers.c	\
				\src\atlanta\define\product.h		\
				\src\ATLANTA\FLA\define\fla_pro.h		\
				\src\ATLANTA\FLA\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_sers.c
#
$(OBJECT)\fla_sus.obj:	$(SRC)\fla_sus.c	\
				\src\atlanta\define\product.h		\
				\src\ATLANTA\FLA\define\fla_pro.h		\
				\src\ATLANTA\FLA\define\fla_def.h
		$(CC) $(OPTION) $(SRC)\fla_sus.c
#
$(OBJECT)\fla_tbl.obj:	$(DEFV)\fla_tbl.c	\
				\src\atlanta\define\product.h		\
				\src\ATLANTA\FLA\define\fla_def.h		\
				\src\ATLANTA\FLA\ext_v\fla_tbl.h
		$(CC) $(OPTION) $(DEFV)\fla_tbl.c
#
$(OBJECT)\Fla_itim.obj:	$(SRC)\Fla_itim.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\Fla_itim.c
#
$(OBJECT)\Fla_buzz.obj:	$(SRC)\Fla_buzz.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\Fla_buzz.c
#
$(OBJECT)\Fla_io.obj:	$(SRC)\Fla_io.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\Fla_io.c
#
!if ("$(MODEL)" == "ANZU_L") || ("$(MODEL)" == "ANZU_V")
$(OBJECT)\Fla_iorw.obj:	$(SRC2)\Fla_iorw.src
		$(ASM) $(SRC2)\Fla_iorw.src $(ASM_OPT)
!else
$(OBJECT)\Fla_iorw.obj:	$(SRC)\Fla_iorw.src
		$(ASM) $(SRC)\Fla_iorw.src $(ASM_OPT)
!endif
#
$(OBJECT)\Fla_sub.obj:	$(SRC)\Fla_sub.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\Fla_sub.c
#
$(OBJECT)\Fla_oves.obj:	$(SRC)\Fla_oves.c	\
				\src\atlanta\define\product.h		\
				\src\ATLANTA\FLA\define\fla_pro.h		\
				\src\ATLANTA\FLA\define\fla_def.h	\
				\src\ATLANTA\FLA\ext_v\fla_tbl.h	\
				\src\ATLANTA\ext_v\bkupram.h
		$(CC) $(OPTION) $(SRC)\Fla_oves.c
#

#!if ("$(MODEL)" != "POPLAR_H")
#$(OBJECT)\Fla_lcda.obj:	$(SRC)\Fla_lcda.c	\
#				\src\atlanta\define\product.h
#		$(CC) $(OPTION) $(SRC)\Fla_lcda.c
#!endif
#!if ("$(MODEL)" == "POPLAR_H")
#$(OBJECT)\Fla_lcdk.obj:	$(SRC)\Fla_lcdk.c	\
#				\src\atlanta\define\product.h
#		$(CC) $(OPTION) $(SRC)\Fla_lcdk.c
#
$(OBJECT)\Fla_lcd.obj:	$(SRC)\Fla_lcd.c	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\opr\ank\define\opr_def.h		\
					\src\atlanta\define\syscomf.h		\
						\src\atlanta\define\sysdial.h		\
					\src\atlanta\define\sysdoc.h		\
					\src\atlanta\define\sysmax.h		\
					\src\atlanta\define\sysonet.h		\
						\src\atlanta\define\sysspeed.h		\
					\src\atlanta\define\time.h		\
#					\src\atlanta\define\sys_infd.h		\
				\src\atlanta\sh7043\define\sh_port.h		\
#					\src\atlanta\poplar_b\define\popbport.h		\
#					\src\atlanta\poplar_l\define\poplport.h		\
#					\src\atlanta\poplar_n\define\popnport.h		\
#					\src\atlanta\poplar_h\define\pophport.h		\
#					\src\atlanta\anzu_l\define\anzuport.h		\
				\src\ATLANTA\FLA\define\sys_def.h		\
				\src\ATLANTA\FLA\define\sys_pro.h		\
				\src\ATLANTA\ext_v\sys_port.h		\
				\src\ATLANTA\define\scn_def.h		\
#				\src\atlanta\opr\kanji\define\opr_def.h		\
					\src\atlanta\define\keycode.h
#						\src\atlanta\opr\ank\define\keycode.h		\
#						\src\atlanta\opr\kanji\define\keycode.h		\
#				\src\atlanta\opr\kanji\define\lcd_def.h
		$(CC) $(OPTION) $(SRC)\fla_lcd.c

#$(OBJECT)\lcd_buf.obj:	$(DEFV)\lcd_buf.c	\
#				\src\atlanta\define\product.h
#		$(CC) $(OPTION) $(DEFV)\lcd_buf.c
#!endif

#
$(OBJECT)\Fla_str.obj:	$(SRC)\Fla_str.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\Fla_str.c
#
$(OBJECT)\Fla_sube.obj:	$(SRC)\Fla_sube.c	\
				\src\atlanta\define\product.h	\
				\src\atlanta\define\fcm_def.h	\
				\src\atlanta\define\sysmax.h	\
				\src\atlanta\ext_v\bkupram.h	\
				\src\atlanta\ext_v\rom_tbl.h
		$(CC) $(OPTION) $(SRC)\Fla_sube.c
#
!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU") || ("$(MODEL)" == "HINOKI2")) || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
$(OBJECT)\hino_int.obj:	$(SRC)\hino_int.src
		$(ASM) $(SRC)\hino_int.src $(ASM_OPT)
#
$(OBJECT)\iu_uniq.obj:	$(SRC)\iu_uniq.c	\
				\src\atlanta\define\product.h
		$(CC) $(OPTION) $(SRC)\iu_uniq.c
!endif
#
