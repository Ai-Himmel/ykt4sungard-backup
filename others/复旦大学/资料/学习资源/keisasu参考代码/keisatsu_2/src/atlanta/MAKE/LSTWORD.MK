#------------------------------------------------------------------------
#   POPLAR_B/POPLAR_L/ANZU_L   リストワーディング部のメイクファイル
#------------------------------------------------------------------------
SRC		= \src\atlanta\src
DEFINE	= \src\atlanta\define
DEFV	= \src\atlanta\def_v
EXTV	= \src\atlanta\ext_v
MON		= \src\atlanta\mon
MAKE	= \src\atlanta\make
WORD	= \src\atlanta\wording
#
CC		= shc
ASM		= asmsh
#OPTION	= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION	= /op=0 /nodeb /cp=sh2 /def=($(MODEL),$(COUNTRY))
ASM_OPT	= /cpu=sh2 /debug /object=$*.obj
LNK		= lnk /subcommand=\src\atlanta\make\lstword.sub
OBJECT	= \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-----------------------------------------------------------------------------
#	ﾘｽﾄﾜｰﾃﾞｨﾝｸﾞのﾘﾝｸを定義
#-----------------------------------------------------------------------------
$(OBJECT)\lstword.lnk:	\src\atlanta\make\lstword.sub \
						$(OBJECT)\LST_WRD0.obj 	\
						$(OBJECT)\LST_WRD1.obj  \
						$(OBJECT)\LST_WRD2.obj 	\
						$(OBJECT)\LST_WRD3.obj
					$(LNK)

#-----------------------------------------------------------------------------
#	ﾘｽﾄﾜｰﾃﾞｨﾝｸﾞのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
$(OBJECT)\LST_WRD0.obj:	$(WORD)\lst_wrd0.c
	$(CC) $(OPTION) $(WORD)\lst_wrd0.c
#
$(OBJECT)\LST_WRD1.obj:	$(WORD)\lst_wrd1.c			\
						$(WORD)\lst_wkan.c			\
						$(WORD)\lst_wusa.c			\
						$(WORD)\lst_wfra.c			\
!if ("$(MODEL)" != "KEISATSU")
						$(WORD)\lst_wdeu.c			\
						$(WORD)\lst_wesp.c			\
						$(WORD)\lst_wita.c			\
						$(WORD)\lst_wjpn.c			\
						$(WORD)\lst_wswe.c			\
!endif
#!if ("$(MODEL)" == "POPLAR_B")
!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLR_BN")
						$(WORD)\oki_ldeu.c			\
						$(WORD)\oki_ldnk.c			\
						$(WORD)\oki_lesp.c			\
						$(WORD)\oki_lita.c			\
						$(WORD)\oki_lnld.c			\
						$(WORD)\oki_lnor.c			\
						$(WORD)\oki_lswe.c			\
!endif
						$(DEFINE)\wording.h
	$(CC) $(OPTION) $(WORD)\lst_wrd1.c
#
$(OBJECT)\LST_WRD2.obj:	$(WORD)\lst_wrd2.c			\
						$(WORD)\lst_wkan.c			\
						$(WORD)\lst_wusa.c			\
						$(WORD)\lst_wfra.c			\
!if ("$(MODEL)" != "KEISATSU")
						$(WORD)\lst_wdeu.c			\
						$(WORD)\lst_wesp.c			\
						$(WORD)\lst_wita.c			\
						$(WORD)\lst_wjpn.c			\
						$(WORD)\lst_wswe.c			\
!endif
#!if ("$(MODEL)" == "POPLAR_B")
!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLR_BN")
						$(WORD)\oki_ldeu.c			\
						$(WORD)\oki_ldnk.c			\
						$(WORD)\oki_lesp.c			\
						$(WORD)\oki_lita.c			\
						$(WORD)\oki_lnld.c			\
						$(WORD)\oki_lnor.c			\
						$(WORD)\oki_lswe.c			\
!endif
						$(DEFINE)\wording.h
	$(CC) $(OPTION) $(WORD)\lst_wrd2.c
#
$(OBJECT)\LST_WRD3.obj:	$(WORD)\lst_wrd3.c			\
						$(WORD)\lst_wkan.c			\
						$(WORD)\lst_wusa.c			\
						$(WORD)\lst_wfra.c			\
!if ("$(MODEL)" != "KEISATSU")
						$(WORD)\lst_wdeu.c			\
						$(WORD)\lst_wesp.c			\
						$(WORD)\lst_wita.c			\
						$(WORD)\lst_wjpn.c			\
						$(WORD)\lst_wswe.c			\
!endif
#!if ("$(MODEL)" == "POPLAR_B")
!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLR_BN") 
						$(WORD)\oki_ldeu.c			\
						$(WORD)\oki_ldnk.c			\
						$(WORD)\oki_lesp.c			\
						$(WORD)\oki_lita.c			\
						$(WORD)\oki_lnld.c			\
						$(WORD)\oki_lnor.c			\
						$(WORD)\oki_lswe.c			\
!endif
						$(DEFINE)\wording.h
	$(CC) $(OPTION) $(WORD)\lst_wrd3.c
#
