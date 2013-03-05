#------------------------------------------------------------------------
#	HINOKI2		モデム部(MDM_FM336)のメイクファイル
#------------------------------------------------------------------------

#---------------------------#
#	ディレクトリマクロ		#
#---------------------------#
#
MODEL_DIR = \src\atlanta

#
DEFINE		= $(MODEL_DIR)\define
DEFV		= $(MODEL_DIR)\def_v
EXTV		= $(MODEL_DIR)\ext_v
SRC			= $(MODEL_DIR)\mdm\fm336\src
MDM_RW_DEF	= $(MODEL_DIR)\mdm\fm336\def_v
MAKE		= $(MODEL_DIR)\make
WORDING		= \src\atlanta\wording

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
LNK			= lnk /subcommand=\src\atlanta\make\MDM.sub
#-----------------------------------------------------------------------------
#	引数を定義
#-----------------------------------------------------------------------------
NOPT_OPTION	= /op=0       /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
INTOPTION	= /op=0       /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
#OPTION		= /op=1 /size /deb /cp=sh2 /def=($(MODEL),$(COUNTRY))
#ASM_OPT	= /cpu=$(CPU_OPT) /debug /object=$*.obj
#OPTION		= /op=0       /deb /def=($(MODEL),$(COUNTRY),$(CPU)) /cp=$(CPU_OPT)

#-----------------------------------------------------------------------------
#	オブジェクトディレクトリを定義
#-----------------------------------------------------------------------------
MACHINE_DEF = sh
CMD_SUFX	= sub
OBJECT		= $(MODEL_DIR)\$(MODEL)\work\$(COUNTRY)

#-----------------------------------------------------------------------------
#	ﾓﾃﾞﾑﾓｼﾞｭｰﾙのﾘﾝｸを定義
#-----------------------------------------------------------------------------
#
$(OBJECT)\mdm.lnk:	$(MAKE)\mdm.$(CMD_SUFX)	\
				$(OBJECT)\mdm.obj			\
				$(OBJECT)\mdm_cmd.obj		\
				$(OBJECT)\mdm_crc.obj		\
				$(OBJECT)\mdm_dsp.obj		\
				$(OBJECT)\mdm_dtmf.obj		\
				$(OBJECT)\mdm_ecm.obj		\
				$(OBJECT)\mdm_fact.obj		\
				$(OBJECT)\mdm_fltr.obj		\
				$(OBJECT)\mdm_fsk.obj		\
				$(OBJECT)\mdm_func.obj		\
				$(OBJECT)\mdm_g3.obj		\
				$(OBJECT)\mdm_int.obj		\
				$(OBJECT)\mdm_io.obj		\
#				$(OBJECT)\mdm_nd.obj		\
#				$(OBJECT)\mdm_nddt.obj		\
				$(OBJECT)\mdm_sub.obj		\
#				$(OBJECT)\mdm_sub2.obj		\
				$(OBJECT)\mdm_tcf.obj		\
				$(OBJECT)\mdm_tone.obj		\
#				$(OBJECT)\mdm_v23.obj		\
				$(OBJECT)\mdm_v8.obj		\
				$(OBJECT)\mdmrxpix.obj		\
				$(OBJECT)\mdmtxpix.obj		\
				$(OBJECT)\mdm_data.obj		\
				$(OBJECT)\mdm_ebuf.obj		\
				$(OBJECT)\mdm_tbl.obj		\
				$(OBJECT)\mdm_tblc.obj		\
				$(OBJECT)\mdmertbl.obj          \
				$(OBJECT)\mdm_mldy.obj
		$(LNK)
#-----------------------------------------------------------------------------
#	ﾓﾃﾞﾑﾓｼﾞｭｰﾙのﾒｲｸﾌｧｲﾙ部
#-----------------------------------------------------------------------------
#
$(OBJECT)\mdm.obj:		$(SRC)\mdm.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm.c

$(OBJECT)\mdm_cmd.obj:	$(SRC)\mdm_cmd.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_cmd.c

$(OBJECT)\mdm_crc.obj:	$(SRC)\mdm_crc.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_crc.c

$(OBJECT)\mdm_dsp.obj:	$(SRC)\mdm_dsp.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_dsp.c

$(OBJECT)\mdm_dtmf.obj:	$(SRC)\mdm_dtmf.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_dtmf.c

$(OBJECT)\mdm_ecm.obj:	$(SRC)\mdm_ecm.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_ecm.c

$(OBJECT)\mdm_fact.obj:	$(SRC)\mdm_fact.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_fact.c

$(OBJECT)\mdm_fltr.obj:	$(SRC)\mdm_fltr.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_fltr.c

$(OBJECT)\mdm_fsk.obj:	$(SRC)\mdm_fsk.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_fsk.c

$(OBJECT)\mdm_func.obj:	$(SRC)\mdm_func.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_func.c

$(OBJECT)\mdm_g3.obj:		$(SRC)\mdm_g3.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_g3.c

$(OBJECT)\mdm_int.obj:	$(SRC)\mdm_int.c		
	$(CC) $(INTOPTION) $(SRC)\mdm_int.c

$(OBJECT)\mdm_io.obj:	$(SRC)\mdm_io.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_io.c

#
#$(OBJECT)\mdm_nd.obj:	$(SRC)\mdm_nd.c		
#	$(CC) $(NOPT_OPTION) $(SRC)\mdm_nd.c

#
#$(OBJECT)\mdm_nddt.obj:	$(SRC)\mdm_nddt.c		
#	$(CC) $(NOPT_OPTION) $(SRC)\mdm_nddt.c

$(OBJECT)\mdm_sub.obj:	$(SRC)\mdm_sub.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_sub.c
#
#$(OBJECT)\mdm_sub2.obj:	$(SRC)\mdm_sub2.c		
#	$(CC) $(NOPT_OPTION) $(SRC)\mdm_sub2.c

$(OBJECT)\mdm_tcf.obj:	$(SRC)\mdm_tcf.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_tcf.c

$(OBJECT)\mdm_tone.obj:	$(SRC)\mdm_tone.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_tone.c

#
#$(OBJECT)\mdm_v23.obj:	$(SRC)\mdm_v23.c		
#	$(CC) $(NOPT_OPTION) $(SRC)\mdm_v23.c

$(OBJECT)\mdm_v8.obj:	$(SRC)\mdm_v8.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_v8.c

$(OBJECT)\mdmrxpix.obj:	$(SRC)\mdmrxpix.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdmrxpix.c

$(OBJECT)\mdmtxpix.obj:	$(SRC)\mdmtxpix.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdmtxpix.c

$(OBJECT)\mdm_data.obj:	$(MDM_RW_DEF)\mdm_data.c		
	$(CC) $(NOPT_OPTION) $(MDM_RW_DEF)\mdm_data.c

$(OBJECT)\mdm_ebuf.obj:	$(MDM_RW_DEF)\mdm_ebuf.c		
	$(CC) $(NOPT_OPTION) $(MDM_RW_DEF)\mdm_ebuf.c

$(OBJECT)\mdm_tbl.obj:	$(MDM_RW_DEF)\mdm_tbl.c		
	$(CC) $(NOPT_OPTION) $(MDM_RW_DEF)\mdm_tbl.c

$(OBJECT)\mdm_tblc.obj:	$(MDM_RW_DEF)\mdm_tblc.c		
	$(CC) $(NOPT_OPTION) $(MDM_RW_DEF)\mdm_tblc.c

$(OBJECT)\mdm_mldy.obj:	$(SRC)\mdm_mldy.c		
	$(CC) $(NOPT_OPTION) $(SRC)\mdm_mldy.c


#各オペレーションメークファイルに移動しました。By O.Kimoto 1997/09/04
#-----------------------------------------------------------------------------
#	ｿﾌﾄｺｰﾃﾞｯｸﾃｰﾌﾞﾙ By Y.Suzuki 1997/04/1
#	内部ＲＯＭから参照する、外部ＲＯＭモジュールアドレス固定用
#-----------------------------------------------------------------------------
$(OBJECT)\mdmertbl.obj:	  $(MDM_RW_DEF)\mdmertbl.c	
		$(CC)	$(NOPT_OPTION) $(MDM_RW_DEF)\mdmertbl.c

