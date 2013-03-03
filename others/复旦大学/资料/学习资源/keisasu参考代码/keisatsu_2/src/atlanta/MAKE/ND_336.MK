
# =============================================================================
# =	 Ï¸Û’è‹`																  #
# =============================================================================
DEFINE	= \src\atlanta\define
DEFV	= \src\atlanta\def_v
EXTV	= \src\atlanta\ext_v
SRC		= \src\atlanta\src
MDM_DEFINE	= \src\atlanta\mdm\fm336\define
MDM_DEFV	= \src\atlanta\mdm\fm336\def_v
MDM_EXTV	= \src\atlanta\mdm\fm336\ext_v
MDM_SRC = \src\atlanta\mdm\fm336\src
SH_DEFINE  = \src\atlanta\sh7043\define
WORD	= \src\atlanta\wording
MON		= \src\atlanta\mon
MAKE	= \src\atlanta\make
MSWDEFINE	= \src\memsw\define
#
#-----------------------------------------------------------------------------
#	ºÏÝÄÞ–¼‚ð’è‹`
#-----------------------------------------------------------------------------
CC			= shc
ASM			= asmsh

OPTION		= /op=0 /deb       /cp=sh2 /def=($(MODEL),$(COUNTRY))
OPTION_ND	= /op=1 /deb /size /cp=sh2 /def=($(MODEL),$(COUNTRY))
ASM_OPT		= /cpu=$(CPU_OPT) /debug /object=$*.obj
MACHINE_DEF = sh
CMD_SUFX	= sub
LNK			= lnk /subcommand=\src\atlanta\make\nd.sub
OBJECT		 = \src\atlanta\$(MODEL)\work\$(COUNTRY)


# =============================================================================
# =	 Ó¼Þ­°Ù Ò²¸																  #
# =============================================================================
$(OBJECT)\ND.lnk :	\src\atlanta\make\ND.$(CMD_SUFX)	\
				$(OBJECT)\CMN_ND.OBJ	\
				$(OBJECT)\CMN_NDHS.OBJ	\
				$(OBJECT)\NCU_ND.OBJ	\
				$(OBJECT)\NCU_NDDN.OBJ	\
				$(OBJECT)\MDM_ND.OBJ	\
				$(OBJECT)\MDM_V23.OBJ	\
				$(OBJECT)\MDM_NDDT.OBJ	
		$(LNK)
# =============================================================================
# =	 ºÝÊß²Ù																	  #
# =============================================================================
$(OBJECT)\NCU_ND.OBJ:	$(SRC)\NCU_ND.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\message.h		\
				\src\atlanta\define\apl_msg.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\sh7043\define\def_mbxn.h	\
				\src\atlanta\sh7043\ext_v\extv_mbx.h	\
				\src\atlanta\define\ncu_stat.h		\
				\src\atlanta\define\ncu_msg.h		\
				\src\atlanta\define\ncu_def.h		\
				\src\atlanta\define\atd_def.h		\
				\src\atlanta\sh7043\define\def_tib.h	\
				\src\atlanta\ext_v\bkupram.h		\
				\src\atlanta\define\status.h		\
				\src\atlanta\mdm\fm336\define\mdm_def.h \
				\src\atlanta\mdm\fm336\define\mdmnddef.h 
		$(CC)	$(OPTION)	$(SRC)\NCU_ND.C
#
$(OBJECT)\NCU_NDDN.OBJ:	$(SRC)\NCU_NDDN.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\ext_v\bkupram.h		\
				\src\atlanta\define\status.h		
		$(CC)	$(OPTION)	$(SRC)\NCU_NDDN.C
#
$(OBJECT)\CMN_ND.OBJ:	$(SRC)\CMN_ND.C	\
				\src\atlanta\define\product.h \
				\src\atlanta\define\std.h \
				\src\atlanta\define\cmn_nd.h \
				\src\atlanta\define\cmn_ndhs.h 
		$(CC)	$(OPTION)	$(SRC)\CMN_ND.C
#
$(OBJECT)\CMN_NDHS.OBJ:	$(SRC)\CMN_NDHS.C	\
				\src\atlanta\define\product.h \
				\src\atlanta\define\std.h \
				\src\atlanta\define\cmn_nd.h \
				\src\atlanta\ext_v\bkupram.h \
				\src\atlanta\define\cmn_ndhs.h \
				\src\atlanta\define\cmn_pro.h
		$(CC)	$(OPTION)	$(SRC)\CMN_NDHS.C
#
$(OBJECT)\MDM_ND.OBJ:	$(MDM_SRC)\MDM_ND.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\mdm\fm336\define\mdm_def.h \
				\src\atlanta\mdm\fm336\ext_v\mdm_data.h \
				\src\atlanta\mdm\fm336\define\mdmnddef.h \
				\src\atlanta\mdm\fm336\define\mdmndpro.h \
				\src\atlanta\define\apl_msg.h \
				\src\atlanta\define\mon_pro.h \
				\src\atlanta\define\timer10.h \
				\src\atlanta\sh7043\define\def_evtn.h \
				\src\atlanta\sh7043\define\def_evtn.h \
				\src\atlanta\sh7043\define\def_tib.h \
				\src\atlanta\define\ncu_pro.h
		$(CC)	$(OPTION)	$(MDM_SRC)\MDM_ND.C
#
$(OBJECT)\MDM_NDDT.OBJ:	$(MDM_SRC)\MDM_NDDT.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\mdm\fm336\define\mdmnddef.h 
		$(CC)	$(OPTION)	$(MDM_SRC)\MDM_NDDT.C
#
$(OBJECT)\MDM_V23.OBJ:	$(MDM_SRC)\MDM_V23.C	\
				\src\atlanta\define\product.h		\
				\src\atlanta\define\std.h		\
				\src\atlanta\mdm\fm336\define\mdm_def.h \
				\src\atlanta\mdm\fm336\ext_v\mdm_data.h \
				\src\atlanta\mdm\fm336\define\mdm_io.h	\
				\src\atlanta\mdm\fm336\define\mdm_bps.h	\
				\src\atlanta\mdm\fm336\define\mdmnddef.h \
				\src\atlanta\define\mon_pro.h		\
				\src\atlanta\define\dma_blk.h		\
				\src\atlanta\define\dma_def.h		\
				\src\atlanta\ext_v\bkupram.h		\
				\src\atlanta\define\mntsw_c.h		\
				\src\atlanta\sh7043\define\def_evtn.h	
		$(CC)	$(OPTION)	$(MDM_SRC)\MDM_V23.C
#
