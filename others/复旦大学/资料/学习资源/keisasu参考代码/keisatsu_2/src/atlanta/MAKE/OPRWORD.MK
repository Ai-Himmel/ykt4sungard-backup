#------------------------------------------------------------------------
#	POPLAR/ANZU_L	オペレーションワーディング部のメイクファイル
#------------------------------------------------------------------------
DEFINE		= \src\atlanta\define
#!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLAR_L") || ("$(MODEL)" == "ANZU_L") || ("$(MODEL)" == "ANZU_V")
#!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLAR_N") || ("$(MODEL)" == "POPLAR_L") || ("$(MODEL)" == "ANZU_L") || ("$(MODEL)" == "ANZU_V")
!if ("$(MODEL)" == "POPLAR_B") || ("$(MODEL)" == "POPLR_BN") || ("$(MODEL)" == "POPLAR_N") || ("$(MODEL)" == "POPLAR_L") || ("$(MODEL)" == "ANZU_L") || ("$(MODEL)" == "ANZU_V")
WORD		= \src\atlanta\opr\ank\wording
!endif
!if ("$(MODEL)" == "POPLAR_H")
WORD		= \src\atlanta\opr\kanji\wording
!endif
!if ("$(MODEL)" == "SAKAKI")
WORD		= \src\atlanta\opr\kanji\wording
!endif
!if (("$(MODEL)" == "HINOKI") || ("$(MODEL)" == "HINOKI2") || ("$(MODEL)" == "HINOKI3") || ("$(MODEL)" == "KEISATSU")) || ("$(MODEL)" == "SATSUKI2") || ("$(MODEL)" == "STOCKHM2")
WORD		= \src\atlanta\opr\ank\wording
!endif

#-----------------------------------------------------------------------------
#	コマンド名を定義
#-----------------------------------------------------------------------------
CC			= shc
ASM			= asmsh
LNK			= lnk /subcommand=\src\atlanta\make\oprword.sub

#-----------------------------------------------------------------------------
#	引数を定義
#-----------------------------------------------------------------------------
OPTION		= /op=0 /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))

#!if ("$(MODEL)" != "POPLAR_H")
#OPTION_ND	= /op=0 /nodeb /cp=sh2 /def=($(MODEL),$(COUNTRY))
#!endif
!if ("$(MODEL)" == "POPLAR_H") || ("$(MODEL)" == "SAKAKI")
OPTION_ND	= /op=0 /l /cp=sh2 /def=($(MODEL),$(COUNTRY))
!else
OPTION_ND	= /op=0 /nodeb /cp=sh2 /def=($(MODEL),$(COUNTRY))
!endif

S_OPTION	= /op=1 /deb /cp=$(CPU_OPT) /def=($(MODEL),$(COUNTRY),$(CPU))
ASM_OPT		= /cpu=sh2 /debug /object=$*.obj

#-----------------------------------------------------------------------------
#	オブジェクトディレクトリを定義
#-----------------------------------------------------------------------------
OBJECT		= \src\atlanta\$(MODEL)\work\$(COUNTRY)

#-----------------------------------------------------------------------------
#	オペレーションワーディングのリンクを定義
#-----------------------------------------------------------------------------
$(OBJECT)\oprword.lnk:	\src\atlanta\make\oprword.sub	\
			$(OBJECT)\opr_wrd0.obj	\
			$(OBJECT)\opr_wrd1.obj	\
			$(OBJECT)\opr_wrd2.obj	\
			$(OBJECT)\opr_wrd3.obj
		$(LNK)

#-----------------------------------------------------------------------------
#	オペレーションワーディングのメイクファイル部
#-----------------------------------------------------------------------------
$(OBJECT)\opr_wrd0.obj:	$(WORD)\opr_wrd0.c	\
!if ("$(MODEL)" == "POPLR_BN")
	$(WORD)\ntt_wrd0.c						\
!endif
	$(DEFINE)\product.h
		$(CC) $(OPTION_ND) $(WORD)\opr_wrd0.c
#
$(OBJECT)\opr_wrd1.obj:	$(WORD)\opr_wrd1.c	\
	$(DEFINE)\product.h						\
	$(DEFINE)\wording.h						\
!if ("$(MODEL)" == "POPLR_BN")
	$(WORD)\ntt_wjpn.c						\
	$(WORD)\ntt_wusa.c
!else
!if ("$(MODEL)" == "POPLAR_B")
	$(WORD)\oki_odeu.c						\
	$(WORD)\oki_odnk.c						\
	$(WORD)\oki_oesp.c						\
	$(WORD)\oki_oita.c						\
	$(WORD)\oki_onld.c						\
	$(WORD)\oki_onor.c						\
	$(WORD)\oki_oswe.c						\
!endif
!if ("$(MODEL)" != "KEISATSU")
	$(WORD)\opr_wdeu.c						\
	$(WORD)\opr_wesp.c						\
	$(WORD)\opr_wita.c						\
	$(WORD)\opr_wswe.c						\
!endif
	$(WORD)\opr_wjpn.c						\
	$(WORD)\opr_wusa.c						\
	$(WORD)\opr_wfra.c
!endif
		$(CC) $(OPTION_ND) $(WORD)\opr_wrd1.c
#
$(OBJECT)\opr_wrd2.obj:	$(WORD)\opr_wrd2.c	\
	$(DEFINE)\product.h						\
	$(DEFINE)\wording.h						\
!if ("$(MODEL)" == "POPLR_BN")
	$(WORD)\ntt_wjpn.c						\
	$(WORD)\ntt_wusa.c
!else
!if ("$(MODEL)" == "POPLAR_B")
	$(WORD)\oki_odeu.c						\
	$(WORD)\oki_odnk.c						\
	$(WORD)\oki_oesp.c						\
	$(WORD)\oki_oita.c						\
	$(WORD)\oki_onld.c						\
	$(WORD)\oki_onor.c						\
	$(WORD)\oki_oswe.c						\
!endif
!if ("$(MODEL)" != "KEISATSU")
	$(WORD)\opr_wdeu.c						\
	$(WORD)\opr_wesp.c						\
	$(WORD)\opr_wita.c						\
	$(WORD)\opr_wswe.c						\
!endif
	$(WORD)\opr_wjpn.c						\
	$(WORD)\opr_wusa.c						\
	$(WORD)\opr_wfra.c
!endif
		$(CC) $(OPTION_ND) $(WORD)\opr_wrd2.c
#
$(OBJECT)\opr_wrd3.obj:	$(WORD)\opr_wrd3.c	\
	$(DEFINE)\product.h						\
	$(DEFINE)\wording.h						\
!if ("$(MODEL)" == "POPLR_BN")
	$(WORD)\ntt_wjpn.c						\
	$(WORD)\ntt_wusa.c
!else
!if ("$(MODEL)" == "POPLAR_B")
	$(WORD)\oki_odeu.c						\
	$(WORD)\oki_odnk.c						\
	$(WORD)\oki_oesp.c						\
	$(WORD)\oki_oita.c						\
	$(WORD)\oki_onld.c						\
	$(WORD)\oki_onor.c						\
	$(WORD)\oki_oswe.c						\
!endif
!if ("$(MODEL)" != "KEISATSU")
	$(WORD)\opr_wdeu.c						\
	$(WORD)\opr_wesp.c						\
	$(WORD)\opr_wita.c						\
	$(WORD)\opr_wswe.c						\
!endif
	$(WORD)\opr_wjpn.c						\
	$(WORD)\opr_wusa.c						\
	$(WORD)\opr_wfra.c
!endif
		$(CC) $(OPTION_ND) $(WORD)\opr_wrd3.c
#
