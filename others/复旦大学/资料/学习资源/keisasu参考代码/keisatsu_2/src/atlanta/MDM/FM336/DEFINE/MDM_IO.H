/*--------------------------------------------------------------------*/
/* プロジェクト : POPLAR_F                                            */
/* ファイル名   : mdm_io.h                                            */
/* 作成者       :                                                     */
/* 日  付       : 99/10/06                                            */
/* 概  要       : V53                                                 */
/*              : I/Oポート定義                                       */
/* 修正履歴     : Oct.30,1995 Assigned By O.K                         */
/*                ＲＩＳＣ用にアドレスを再定義 by O.Kimoto 1997/06/13 */
/*--------------------------------------------------------------------*/
#ifndef mdm_io_h
	#define	mdm_io_h 1
	
#include "\src\atlanta\define\product.h"

#if defined(HINOKI) || defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2) /* HINOKI2 2001/11/13 T.Takagi */
	#define	MDM_R288F_BASE_PORT	0x0090C000
#else
	#define	MDM_R288F_BASE_PORT	0x00C40101
#endif
	
/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（００Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_00_PORT		(MDM_R288F_BASE_PORT+0x0000)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_00_PORT		(MDM_R288F_BASE_PORT+0x0000)
#endif

 /** Address Define **/
 #define RBUFFER_PORT		MDM_REG_00_PORT

 /** Bit Define **/
 /** 受信データバッファ **/
 #define IO_BIT_RBUFFER		0xFF

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（０１Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_01_PORT		(MDM_R288F_BASE_PORT+0x0002)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_01_PORT		(MDM_R288F_BASE_PORT+0x0001)
#endif
 
 /** Address Define **/
 #define RXP_PORT			MDM_REG_01_PORT
 #define RXHF_PORT			MDM_REG_01_PORT
 #define TXHF_PORT			MDM_REG_01_PORT
 #define VPAUSE_PORT			MDM_REG_01_PORT
 #define VOLUME_PORT			MDM_REG_01_PORT

 /** Bit Define **/
 #define IO_BIT_RXP				0x0001
 #define IO_BIT_RXHF			0x0002
 #define IO_BIT_TXHF			0x0004
 #define IO_BIT_VPAUSE			0x0020
 #define IO_BIT_VOLUME			0x00C0
  #define IO_BIT_VOLUME1			0x0040
  #define IO_BIT_VOLUME2			0x0080
   #define VOLUME_OFF					0x0000	/** Speaker OFF **/
   #define VOLUME_LARGE					0x0080	/** Speaker attenuation =  0 dB(High volume) **/
   #define VOLUME_MID					0x0040	/** Speaker attenuation =  6 dB(Medium volume) **/
   #define VOLUME_SMALL					0x00C0	/** Speaker attenuation = 12 dB(Low volume) **/

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（０２Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_02_PORT		(MDM_R288F_BASE_PORT+0x0004)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_02_PORT		(MDM_R288F_BASE_PORT+0x0002)
#endif

 /** Address Define **/
 #define CODBITS_PORT		MDM_REG_02_PORT
 #define V54PE_PORT			MDM_REG_02_PORT
 #define V54AE_PORT			MDM_REG_02_PORT
 #define SCDE_PORT			MDM_REG_02_PORT
 #define V54TE_PORT			MDM_REG_02_PORT
 #define SDCEN_PORT			MDM_REG_02_PORT
 #define RTSDE_PORT			MDM_REG_02_PORT
 #define CDEN_PORT			MDM_REG_02_PORT
 #define DCDEN_PORT			MDM_REG_02_PORT
 #define S511_PORT			MDM_REG_02_PORT
 #define SQDIS_PORT			MDM_REG_02_PORT
 #define TDE_PORT			MDM_REG_02_PORT

 /** Bit Define **/
 #define IO_BIT_CODBIT				0x0003
  #define IO_BIT_V54PE			0x0001
  #define IO_BIT_V54AE			0x0002
 #define IO_BIT_SCDE_V54TE			0x0004
 #define IO_BIT_SDCEN_RTSDE			0x0008
 #define IO_BIT_CDEN				0x0010
 #define IO_BIT_DCDEN_S511			0x0020
 #define IO_BIT_SQDIS				0x0040
 #define IO_BIT_TDE					0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（０３Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_03_PORT		(MDM_R288F_BASE_PORT+0x0006)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_03_PORT		(MDM_R288F_BASE_PORT+0x0003)
#endif

 /** Address Define **/
 #define GTS_PORT			MDM_REG_03_PORT
 #define GTE_PORT			MDM_REG_03_PORT
 #define SDIS_PORT			MDM_REG_03_PORT
 #define ARC_PORT			MDM_REG_03_PORT
 #define RLSDE_PORT			MDM_REG_03_PORT
 #define SRCEN_PORT			MDM_REG_03_PORT
 #define SEPT_PORT			MDM_REG_03_PORT
 #define EPT_PORT			MDM_REG_03_PORT

 /** Bit Define **/
 #define IO_BIT_GTS				0x0001
 #define IO_BIT_GTE				0x0002
 #define IO_BIT_SDIS			0x0004
 #define IO_BIT_ARC				0x0008
 #define IO_BIT_RLSDE			0x0010
 #define IO_BIT_SRCEN			0x0020
 #define IO_BIT_SEPT			0x0040
 #define IO_BIT_EPT				0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（０４Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_04_PORT		(MDM_R288F_BASE_PORT+0x0008)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_04_PORT		(MDM_R288F_BASE_PORT+0x0004)
#endif

 /** Address Define **/
 #define STRN_PORT			MDM_REG_04_PORT
 #define TOD_PORT			MDM_REG_04_PORT
 #define NRZIEN_PORT		MDM_REG_04_PORT
 #define EQFZ_PORT			MDM_REG_04_PORT
 #define FIFOEN_PORT		MDM_REG_04_PORT
 #define V32BS_PORT			MDM_REG_04_PORT
 #define EQT2_PORT			MDM_REG_04_PORT
 #define RB_PORT			MDM_REG_04_PORT
 
 /** Bit Define **/
 #define IO_BIT_STRN			0x0001
 #define IO_BIT_TOD				0x0002
 #define IO_BIT_NRZIEN			0x0004
 #define IO_BIT_EQFZ			0x0008
 #define IO_BIT_FIFOEN			0x0010
 #define IO_BIT_V32BS			0x0020
 #define IO_BIT_EQT2			0x0040
 #define IO_BIT_RB				0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（０５Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_05_PORT		(MDM_R288F_BASE_PORT+0x000A)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_05_PORT		(MDM_R288F_BASE_PORT+0x0005)
#endif
 
 /** Address Define **/
 #define STOFF_PORT			MDM_REG_05_PORT
 #define TTDIS_PORT			MDM_REG_05_PORT
 #define CEQ_PORT			MDM_REG_05_PORT
 #define TXSQ_PORT			MDM_REG_05_PORT
 #define FECSQ_PORT			MDM_REG_05_PORT
 #define ECSQ_PORT			MDM_REG_05_PORT
 #define ECFZ_PORT			MDM_REG_05_PORT

 /** Bit Define **/
 #define IO_BIT_STOFF			0x0002
 #define IO_BIT_TTDIS			0x0004
 #define IO_BIT_CEQ				0x0008
 #define IO_BIT_TXSQ			0x0010
 #define IO_BIT_FECSQ			0x0020 /* Forced CC mode (FCCR) in P22 Release Note */
 #define IO_BIT_ECSQ			0x0040
 #define IO_BIT_ECFZ			0x0080
 #define IO_BIT_FCCR_FM336		0x0080 /* Forced CC mode (FCCR) for FM336 by H.Kubo 1999/04/08 */

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（０６Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_06_PORT		(MDM_R288F_BASE_PORT+0x000C)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_06_PORT		(MDM_R288F_BASE_PORT+0x0006)
#endif

 /** Address Define **/
 #define WDSZ_PORT			MDM_REG_06_PORT
 #define DECBITS_PORT		MDM_REG_06_PORT
 #define STB_PORT			MDM_REG_06_PORT
 #define PEN_PORT			MDM_REG_06_PORT
 #define HDLC_PORT			MDM_REG_06_PORT
 #define CCRTN_PORT			MDM_REG_06_PORT		/* Add By O.Kimoto 1996/05/29 */
 #define EXOS_PORT			MDM_REG_06_PORT
 #define RTDIS_PORT			MDM_REG_06_PORT

 /** Bit Define **/
 #define IO_BIT_WDSZ_DECBITS	0x0003
  #define IO_BIT_WDSZ1_DECBITS1		0x0001
  #define IO_BIT_WDSZ2_DECBITS2		0x0002
   #define WDSZ_5BITS					0x0000
   #define WDSZ_6BITS					0x0002
   #define WDSZ_7BITS					0x0001
   #define WDSZ_8BITS					0x0003
   	#define CHAR_5							0x00
   	#define CHAR_6							0x01
   	#define CHAR_7							0x02
   	#define CHAR_8							0x03
 #define IO_BIT_STB				0x0004
 #define IO_BIT_PEN				0x0008
 #define IO_BIT_HDLC			0x0010
 #define IO_BIT_CCRTN			0x0020		/* Add By O.Kimoto 1996/05/29 */
 #define IO_BIT_EXOS			0x0040
 #define IO_BIT_RTDIS			0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（０７Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_07_PORT		(MDM_R288F_BASE_PORT+0x000E)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_07_PORT		(MDM_R288F_BASE_PORT+0x0007)
#endif

 /** Address Define **/
 #define MHLD_PORT			MDM_REG_07_PORT
 #define RA_PORT			MDM_REG_07_PORT
 #define L3ACT_PORT			MDM_REG_07_PORT
 #define DDIS_PORT			MDM_REG_07_PORT
 #define L2ACT_PORT			MDM_REG_07_PORT
 #define RDL_PORT			MDM_REG_07_PORT
 #define RDLE_PORT			MDM_REG_07_PORT

 /** Bit Define **/
 #define IO_BIT_MHLD			0x0001
 #define IO_BIT_RA				0x0002
 #define IO_BIT_L3ACT			0x0008
 #define IO_BIT_DDIS			0x0010
 #define IO_BIT_L2ACT			0x0020
 #define IO_BIT_RDL				0x0040
 #define IO_BIT_RDLE			0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（０８Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_08_PORT		(MDM_R288F_BASE_PORT+0x0010)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_08_PORT		(MDM_R288F_BASE_PORT+0x0008)
#endif

 /** Address Define **/
 #define RTS_PORT			MDM_REG_08_PORT
 #define RTRN_PORT			MDM_REG_08_PORT
 #define V54P_PORT			MDM_REG_08_PORT
 #define V54A_PORT			MDM_REG_08_PORT
 #define V54T_PORT			MDM_REG_08_PORT
 #define V21S_PORT			MDM_REG_08_PORT
 #define TPDM_PORT			MDM_REG_08_PORT
 #define ASYN_PORT			MDM_REG_08_PORT
 
 /** Bit Define **/
 #define IO_BIT_RTS				0x0001
 #define IO_BIT_RTRN			0x0002
 #define IO_BIT_V54P			0x0004
 #define IO_BIT_V54A			0x0008
 #define IO_BIT_V54T			0x0010
 #define IO_BIT_V21S			0x0020
 #define IO_BIT_TPDM			0x0040
 #define IO_BIT_ASYN			0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（０９Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_09_PORT		(MDM_R288F_BASE_PORT+0x0012)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_09_PORT		(MDM_R288F_BASE_PORT+0x0009)
#endif

 /** Address Define **/
 #define DTR_PORT			MDM_REG_09_PORT
 #define RRTSE_PORT			MDM_REG_09_PORT
 #define DATA_PORT			MDM_REG_09_PORT
 #define LL_PORT			MDM_REG_09_PORT
 #define ORG_PORT			MDM_REG_09_PORT
 #define DTMF_PORT			MDM_REG_09_PORT
 #define CC_PORT			MDM_REG_09_PORT
 #define NV25_PORT			MDM_REG_09_PORT
 
 /** Bit Define **/
 #define IO_BIT_DTR				0x0001
 #define IO_BIT_RRTSE			0x0002
 #define MDM_IO_BIT_DATA			0x0004
 #define IO_BIT_LL				0x0008
 #define IO_BIT_ORG				0x0010
 #define IO_BIT_DTMF			0x0020
 #define IO_BIT_CC				0x0040
  #define CONTROL_CHANNEL_1200		0x0000
  #define CONTROL_CHANNEL_2400		0x0040
 #define IO_BIT_NV25			0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（０ＡＨ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_0A_PORT		(MDM_R288F_BASE_PORT+0x0014)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_0A_PORT		(MDM_R288F_BASE_PORT+0x000A)
#endif

 /** Address Define **/
 #define SYNCD_PORT			MDM_REG_0A_PORT
 #define FLAGS_PORT			MDM_REG_0A_PORT
 #define CRCS_PORT			MDM_REG_0A_PORT
 #define OE_PORT			MDM_REG_0A_PORT
 #define FE_PORT			MDM_REG_0A_PORT
 #define PE_PORT			MDM_REG_0A_PORT
 #define FLAGDT_PORT		MDM_REG_0A_PORT
 #define PNSUC_PORT			MDM_REG_0A_PORT
 
 /** Bit Define **/
 #define IO_BIT_SYNCD			0x0001
 #define IO_BIT_FLAGS			0x0002
 #define IO_BIT_CRCS			0x0004
 #define IO_BIT_OE				0x0008
 #define IO_BIT_FE				0x0010
 #define IO_BIT_PE				0x0020
 #define IO_BIT_FLAGDT			0x0040
 #define IO_BIT_PNSUC			0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（０ＢＨ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_0B_PORT		(MDM_R288F_BASE_PORT+0x0016)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_0B_PORT		(MDM_R288F_BASE_PORT+0x000B)
#endif

 /** Address Define **/
 #define EQMAT_PORT			MDM_REG_0B_PORT
 #define DISDET_PORT		MDM_REG_0B_PORT
 #define ATBEL_PORT			MDM_REG_0B_PORT
 #define ATV25_PORT			MDM_REG_0B_PORT
 #define TONEC_PORT			MDM_REG_0B_PORT
 #define TONEB_PORT			MDM_REG_0B_PORT
 #define TONEA_PORT			MDM_REG_0B_PORT
 
 /** Bit Define **/
 #define IO_BIT_EQMAT			0x0001
 #define IO_BIT_DISDET			0x0002
 #define IO_BIT_ATBEL			0x0004
 #define IO_BIT_ATV25			0x0010
 #define IO_BIT_TONEC			0x0020
 #define IO_BIT_TONEB			0x0040
 #define IO_BIT_TONEA			0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（０ＣＨ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_0C_PORT		(MDM_R288F_BASE_PORT+0x0018)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_0C_PORT		(MDM_R288F_BASE_PORT+0x000C)
#endif

 /** Address Define **/
 #define RSEQ_PORT			MDM_REG_0C_PORT
 #define RXFNE_PORT			MDM_REG_0C_PORT
 #define SNDET_PORT			MDM_REG_0C_PORT
 #define SDET_PORT			MDM_REG_0C_PORT
 #define CCDET_PORT			MDM_REG_0C_PORT
 #define DET800_PORT		MDM_REG_0C_PORT
 #define CADET_PORT			MDM_REG_0C_PORT
 #define NEGDET_PORT		MDM_REG_0C_PORT
 #define ACDET_PORT			MDM_REG_0C_PORT
 #define MODEOK_PORT		MDM_REG_0C_PORT
 #define AADET_PORT			MDM_REG_0C_PORT
 #define PROBED_PORT		MDM_REG_0C_PORT
 #define TPMT_PORT			MDM_REG_0C_PORT
 #define PCOFF_PORT			MDM_REG_0C_PORT
 
 /** Bit Define **/
 #define IO_BIT_RSEQ			0x0001
 #define IO_BIT_RXFNE			0x0002
 #define IO_BIT_SNDET			0x0004
 #define IO_BIT_SDET			0x0008
 #define IO_BIT_CCDET_DET800	0x0010	/* CCMode in P22 Release Note. */
 #define IO_BIT_TPMT			0x0010	/* Transmit Pipe Empty (TPMT) in P26 Release Note */
 #define IO_BIT_CADET_NEGDET	0x0020
 #define IO_BIT_ACDET_MODEOK	0x0040
 #define IO_BIT_AADET_PROBED	0x0080
 #define IO_BIT_PCOFF			0x0080 /* For 26P added by H.Kubo 1998/10/30 */
 

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（０ＤＨ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_0D_PORT		(MDM_R288F_BASE_PORT+0x001A)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_0D_PORT		(MDM_R288F_BASE_PORT+0x000D)
#endif

 /** Address Define **/
 #define HKAB_PORT			MDM_REG_0D_PORT
 #define TXFNE_PORT			MDM_REG_0D_PORT
 #define SADET_PORT			MDM_REG_0D_PORT
 #define DETID_PORT			MDM_REG_0D_PORT
 #define U1DET_PORT			MDM_REG_0D_PORT
 #define ECTRN_PORT			MDM_REG_0D_PORT
 #define SCR1_PORT			MDM_REG_0D_PORT
 #define S1DET_PORT			MDM_REG_0D_PORT
 #define PNDET_PORT			MDM_REG_0D_PORT
 #define P2DET_PORT			MDM_REG_0D_PORT
 
 /** Bit Define **/
 #define IO_BIT_HKAB			0x0001
 #define IO_BIT_TXFNF			0x0002
 #define IO_BIT_SADET_DETID		0x0004
 #define IO_BIT_U1DET_EXTRN		0x0008
 #define IO_BIT_SCR1			0x0010
 #define IO_BIT_S1DET			0x0020
 #define IO_BIT_PNDET			0x0040
 #define IO_BIT_P2DET			0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（０ＥＨ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_0E_PORT		(MDM_R288F_BASE_PORT+0x001C)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_0E_PORT		(MDM_R288F_BASE_PORT+0x000E)
#endif

 /** Address Define **/
 #define SPEED_PORT			MDM_REG_0E_PORT
 #define RRDET_PORT			MDM_REG_0E_PORT
 #define BRKD_PORT			MDM_REG_0E_PORT
 #define RTDET_PORT			MDM_REG_0E_PORT
 
 /** Bit Define **/
 #define IO_BIT_SPEED			0x001F	/** Change By O.K Jan.18,1996 **/
  #define IO_BIT_SPEED1				0x0001
  #define IO_BIT_SPEED2				0x0002
  #define IO_BIT_SPEED3				0x0004
  #define IO_BIT_SPEED4				0x0008
  #define IO_BIT_SPEED5				0x0010	/** Add By O.K Jan.18,1996 **/
   #define SPEED_0_300PPS				0x0000
   #define SPEED_600PPS					0x0001
   #define SPEED_1200PPS				0x0002
   #define SPEED_2400PPS				0x0003
   #define SPEED_4800PPS				0x0004
   #define SPEED_7200PPS				0x0008	/* 5->8 1996/02/13 Y.M */
   #define SPEED_9600PPS				0x0005	/* 6->5 1996/02/13 Y.M */
   #define SPEED_12000PPS				0x0006	/* 7->6 1996/02/13 Y.M */
   #define SPEED_14400PPS				0x0007	/* 8->7 1996/02/13 Y.M */
   #define SPEED_16800PPS				0x0009
   #define SPEED_19200PPS				0x000A
   #define SPEED_21600PPS				0x000B
   #define SPEED_24000PPS				0x000C
   #define SPEED_26400PPS				0x000D
   #define SPEED_28800PPS				0x000E
   #define SPEED_31200PPS				0x000F
   #define SPEED_33600PPS				0x0010
 #define IO_BIT_RREDT			0x0020
 #define IO_BIT_BRKD			0x0040
 #define IO_BIT_RTDET			0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（０ＦＨ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_0F_PORT		(MDM_R288F_BASE_PORT+0x001E)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_0F_PORT		(MDM_R288F_BASE_PORT+0x000F)
#endif

 /** Address Define **/
 #define V54DT_PORT			MDM_REG_0F_PORT
 #define RTSDT_PORT			MDM_REG_0F_PORT
 #define TM_PORT			MDM_REG_0F_PORT
 #define RI_PORT			MDM_REG_0F_PORT
 #define DSR_PORT			MDM_REG_0F_PORT
 #define CTS_PORT			MDM_REG_0F_PORT
 #define FED_PORT			MDM_REG_0F_PORT
 #define RLSD_PORT			MDM_REG_0F_PORT
 
 /** Bit Define **/
 #define IO_BIT_V54DT			0x0001
 #define IO_BIT_RTSDT			0x0002
 #define IO_BIT_TM				0x0004
 #define MDM_IO_BIT_RI				0x0008
 #define IO_BIT_DSR				0x0010
 #define IO_BIT_CTS				0x0020
 #define IO_BIT_FED				0x0040
 #define IO_BIT_RLSD			0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１０Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_10_PORT		(MDM_R288F_BASE_PORT+0x0020)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_10_PORT		(MDM_R288F_BASE_PORT+0x0010)
#endif

 /** Address Define **/
 #define TBUFFER_PORT		MDM_REG_10_PORT
 
 /** Bit Define **/
 /** 送信用データバッファ **/
 #define IO_BIT_TBUFFER		0xFF

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１１Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_11_PORT		(MDM_R288F_BASE_PORT+0x0022)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_11_PORT		(MDM_R288F_BASE_PORT+0x0011)
#endif

 /** Address Define **/
 #define TXP_PORT			MDM_REG_11_PORT
 #define TEOF_PORT			MDM_REG_11_PORT
 #define V23HDX_PORT		MDM_REG_11_PORT
 #define RXV_PORT			MDM_REG_11_PORT
 #define TXV_PORT			MDM_REG_11_PORT
 #define PARSL_PORT			MDM_REG_11_PORT
 #define BRKS_PORT			MDM_REG_11_PORT
 
 /** Bit Define **/
 #define IO_BIT_TXP				0x0001
 #define IO_BIT_TEOF			0x0002
 #define IO_BIT_V23HDX			0x0004
 #define IO_BIT_RXV				0x0008
 #define IO_BIT_TXV				0x0010
 #define IO_BIT_PARSL			0x0060
  #define IO_BIT_TARSL1				0x0020
  #define IO_BIT_TARSL2				0x0040
  #define IO_BIT_PARSL1				0x0020 /* added by H.Kubo 1998/08/31 */
  #define IO_BIT_PARSL2				0x0040 /* added by H.Kubo 1998/08/31 */
	   #define STUFF_SELECT			0x0000
	   #define SPACE_SELECT			0x0020
	   #define EVEN_SELECT			0x0040
	   #define ODD_SELECT			0x0060
		   #define STUFF_PARITY			0x00
		   #define SPACE_PARITY			0x01
		   #define EVEN_PARITY			0x02
		   #define ODD_PARITY			0x03
 #define IO_BIT_BRKS			0x0080
 
/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１２Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_12_PORT		(MDM_R288F_BASE_PORT+0x0024)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_12_PORT		(MDM_R288F_BASE_PORT+0x0012)
#endif

 /** Address Define **/
 #define CONF_PORT			MDM_REG_12_PORT

 /** Bit Define **/
 #define IO_BIT_CONF		0xFF
 /** モデム コンフィギュレーション **/
#if (0)	/** SYS_SPD.Hを参照してください。 BY O.K Dec.14,1995 **/
  #define V8_CLEARDOWN			0xAF
  #define V8					0xAA
  #define V34TCM_33600			0xCE
  #define V34TCM_31200			0xCD
  #define V34TCM_28800			0xCC
  #define V34TCM_26400			0xCB
  #define V34TCM_24000			0xCA
  #define V34TCM_21600			0xC9
  #define V34TCM_19200			0xC8
  #define V34TCM_16800			0xC7
  #define V34TCM_14400			0xC6
  #define V34TCM_12000			0xC5
  #define V34TCM_9600			0xC4
  #define V34TCM_7200			0xC3
  #define V34TCM_4800			0xC2
  #define V34TCM_2400			0xC1
  #define V34_CLEARDOWN			0xC0
  #define V33TCM_14400			0x31
  #define V33TCM_12000			0x32
  #define V33TCM_9600			0x34
  #define V33TCM_7200			0x38
  #define V17TCM_14400			0xB1
  #define V17TCM_12000			0xB2
  #define V17TCM_9600			0xB4
  #define V17TCM_7200			0xB8
  #define V29_9600				0x14
  #define V29_7200				0x12
  #define V29_4800				0x11
  #define V27TER_4800			0x02
  #define V27TER_2400			0x01
  #define V21_0_300				0xA0
  #define V21_CHANNEL2_300		0xA8
  #define TRANSMIT_SINGLE_TONE	0x80
  #define TRANSMIT_DUAL_TONE	0x83
  #define DIALING				0x81
  #define DTMF_RECEIVER			0x86
#endif

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１３Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_13_PORT		(MDM_R288F_BASE_PORT+0x0026)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_13_PORT		(MDM_R288F_BASE_PORT+0x0013)
#endif

 /** Address Define **/
 #define TXCLK_PORT			MDM_REG_13_PORT
 #define RTH_PORT			MDM_REG_13_PORT
 #define TLVL_PORT			MDM_REG_13_PORT
 
 /** Bit Define **/
 #define IO_BIT_TXCLK			0x0003
  #define IO_BIT_TXCLK1				0x0001
  #define IO_BIT_TXCLK2				0x0002
   #define TXCLK_INTERNAL				0x0000
   #define TXCLK_EXTERNAL				0x0002
   #define TXCLK_SLAVE					0x0003
   	#define TXCLK_0							0x00
   	#define TXCLK_2							0x01
   	#define TXCLK_3							0x02
 #define IO_BIT_RTH				0x000C
  #define IO_BIT_RTH1				0x0004
  #define IO_BIT_RTH2				0x0008
   #define RTH_LOWEST					0x0000	/** ON=-43dBm / OFF=-48dBm **/
   #define RTH_LOWER					0x0004	/** ON=-33dBm / OFF=-38dBm **/
   #define RTH_HIGHER					0x0008	/** ON=-26dBm / OFF=-31dBm **/
   #define RTH_HIGHEST					0x000C	/** ON=-16dBm / OFF=-21dBm **/
    #define RTH_0							0
    #define RTH_1							1
    #define RTH_2							2
    #define RTH_3							3
 #define IO_BIT_TLVL			0x00F0
  #define IO_BIT_TLVL1				0x0010
  #define IO_BIT_TLVL2				0x0020
  #define IO_BIT_TLVL3				0x0040
  #define IO_BIT_TLVL4				0x0080
   #define TLVL_0DBM					0x0000
   #define TLVL_1DBM					0x0010
   #define TLVL_2DBM					0x0020
   #define TLVL_3DBM					0x0030
   #define TLVL_4DBM					0x0040
   #define TLVL_5DBM					0x0050
   #define TLVL_6DBM					0x0060
   #define TLVL_7DBM					0x0070
   #define TLVL_8DBM					0x0080
   #define TLVL_9DBM					0x0090
   #define TLVL_10DBM					0x00A0
   #define TLVL_11DBM					0x00B0
   #define TLVL_12DBM					0x00C0
   #define TLVL_13DBM					0x00D0
   #define TLVL_14DBM					0x00E0
   #define TLVL_15DBM					0x00F0

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１４Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_14_PORT		(MDM_R288F_BASE_PORT+0x0028)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_14_PORT		(MDM_R288F_BASE_PORT+0x0014)
#endif

 /** Address Define **/
 #define ABCODE_PORT		MDM_REG_14_PORT

 /** Bit Define **/
 #define IO_BIT_ABCODE		0xFF
 /** ＡＢＣ コード **/

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１５Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_15_PORT		(MDM_R288F_BASE_PORT+0x002A)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_15_PORT		(MDM_R288F_BASE_PORT+0x0015)
#endif

 /** Address Define **/
 #define RARC_PORT			MDM_REG_15_PORT
 #define EXL3_PORT			MDM_REG_15_PORT
 #define RREN_PORT			MDM_REG_15_PORT
 #define AUTO_PORT			MDM_REG_15_PORT
 #define HWRWK_PORT			MDM_REG_15_PORT
 #define RDWK_PORT			MDM_REG_15_PORT
 #define SLEEP_PORT			MDM_REG_15_PORT
 
 /** Bit Define **/
 #define IO_BIT_EARC			0x0001
 #define IO_BIT_EXL3			0x0002
 #define IO_BIT_RREN			0x0004
 #define IO_BIT_AUTO			0x0008
 #define IO_BIT_HWRWK			0x0010
 #define IO_BIT_RDWK			0x0020
 #define IO_BIT_SLEEP			0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１６Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_16_PORT		(MDM_R288F_BASE_PORT+0x002C)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_16_PORT		(MDM_R288F_BASE_PORT+0x0016)
#endif

 /** Address Define **/
 #define SECRXB_PORT		MDM_REG_16_PORT

 /** Bit Define **/
 #define IO_BIT_SECRXB		0xFF
 /** 第２受信バッファ **/
 
 /** Receiver Handshake Phase **/
 #define RX_PHASE1		0x00
 #define RX_PHASE2		0x20
 #define RX_PHASE3		0x40
 #define RX_PHASE4		0x60

 /** Receiver Handshake Phase 1 Status **/
 /** Originate Mode Receiver State **/
 #define ORG_LOOKING_FOR_ANSAM			0x00
 #define ORG_FOUND_ANSAM_LOOKING_FOR_JM	0x01
 #define ORG_FOUND_JM					0x02
 
 /** Answer Mode Receiver State **/
 #define ANS_LOOKING_FOR_CI_OR_CM		0x00
 #define ANS_FOUND_CI_LOOKING_FOR_CM	0x01
 #define ANS_FOUND_CM_LOOKING_FOR_CJ	0x02
 #define ANS_CJ_DETECED					0x03

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１７Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_17_PORT		(MDM_R288F_BASE_PORT+0x002E)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_17_PORT		(MDM_R288F_BASE_PORT+0x0017)
#endif

 /** Address Define **/
 #define SECTXB_PORT		MDM_REG_17_PORT

 /** Bit Define **/
 #define IO_BIT_SECTXB		0xFF
 /** 第２送信バッファ **/

 /** Transmitter Handshake Phase **/
 #define TX_PHASE1		0x00
 #define TX_PHASE2		0x20
 #define TX_PHASE3		0x40
 #define TX_PHASE4		0x60

 /** Receiver Handshake Phase 1 Status **/
 /** Originate Mode Receiver State **/
 #define ORG_PAUSING_400MS			0x00	/** Pausing 400ms (Transmitting silence)	**/
 #define ORG_SENDING_CI				0x01	/** Sending CI 								**/
 #define ORG_SENDING_LONG_SILENCE	0x02	/** Sending Silence (500ms or 1000ms)		**/
 #define ORG_SENDING_CM				0x03	/** Sending CM								**/
 #define ORG_SENDING_CJ				0x04	/** Sending CJ								**/
 #define ORG_SENDING_SHORT_SILENCE	0x05	/** Sending Silence (75ms)					**/
 
 /** Answer Mode Receiver State **/
 #define ANS_SENDING_ANSAM			0x00	/** Sending ANSam							**/
 #define ANS_SENDING_JM				0x01	/** Sending JM								**/
 #define ANS_SENDING_SHORT_SILENCE	0x02	/** Sending Silence (75ms)					**/

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１８Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_18_PORT		(MDM_R288F_BASE_PORT+0x0030)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_18_PORT		(MDM_R288F_BASE_PORT+0x0018)
#endif

 /** Address Define **/
 #define MEDAL_PORT			MDM_REG_18_PORT
 
 /** Bit Define **/
 #define IO_BIT_MEDAL		0xFF
 /** メモリデータ ＬＳＢ **/

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１９Ｈ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_19_PORT		(MDM_R288F_BASE_PORT+0x0032)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_19_PORT		(MDM_R288F_BASE_PORT+0x0019)
#endif

 /** Address Define **/
 #define MEDAM_PORT			MDM_REG_19_PORT
 
 /** Bit Define **/
 #define IO_BIT_MEDAM		0xFF
 /** メモリデータ ＭＳＢ **/

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１ＡＨ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_1A_PORT		(MDM_R288F_BASE_PORT+0x0034)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_1A_PORT		(MDM_R288F_BASE_PORT+0x001A)
#endif

 /** Address Define **/
 #define SECEN_PORT			MDM_REG_1A_PORT
 #define SCIBE_PORT			MDM_REG_1A_PORT
 #define SCOBF_PORT			MDM_REG_1A_PORT
 #define DMAE_PORT			MDM_REG_1A_PORT
 #define RION_PORT			MDM_REG_1A_PORT
 #define RIEN_PORT			MDM_REG_1A_PORT
 #define SFRES_PORT			MDM_REG_1A_PORT
 
 /** Bit Define **/
 #define IO_BIT_SECEN			0x0001
 #define IO_BIT_SCIBE			0x0002
 #define IO_BIT_SCOBF			0x0004
 #define IO_BIT_DMAE			0x0010
 #define IO_BIT_RION			0x0020
 #define IO_BIT_RIEN			0x0040
 #define IO_BIT_SFRES			0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１ＢＨ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_1B_PORT		(MDM_R288F_BASE_PORT+0x0036)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_1B_PORT		(MDM_R288F_BASE_PORT+0x001B)
#endif

 /** Address Define **/
 #define DTMFW_PORT			MDM_REG_1B_PORT
 #define DTMFD_PORT			MDM_REG_1B_PORT
 #define OTS_PORT			MDM_REG_1B_PORT
 #define DTDET_PORT			MDM_REG_1B_PORT
 #define EDET_PORT			MDM_REG_1B_PORT
 
 /** Bit Define **/
 #define IO_BIT_DTMFW			0x000F
  #define IO_BIT_DTMFW1				0x0001
  #define IO_BIT_DTMFW2				0x0002
  #define IO_BIT_DTMFW3				0x0004
  #define IO_BIT_DTMFW4				0x0008
 #define IO_BIT_DTMFD			0x0010
 #define IO_BIT_OTS				0x0020
 #define IO_BIT_DTDET			0x0040
 #define IO_BIT_EDET			0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１ＣＨ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_1C_PORT		(MDM_R288F_BASE_PORT+0x0038)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_1C_PORT		(MDM_R288F_BASE_PORT+0x001C)
#endif

 /** Address Define **/
 #define MEADDL_PORT		MDM_REG_1C_PORT
 
 /** Bit Define **/
 #define IO_BIT_MEADDL		0xFF
 /** メモリアクセスアドレス 下位 (8Bit) **/

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１ＤＨ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_1D_PORT		(MDM_R288F_BASE_PORT+0x003A)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_1D_PORT		(MDM_R288F_BASE_PORT+0x001D)
#endif

 /** Address Define **/
 #define MEADDH_PORT	MDM_REG_1D_PORT
 #define MEMCR_PORT		MDM_REG_1D_PORT
 #define MEMW_PORT		MDM_REG_1D_PORT
 #define MEACC_PORT		MDM_REG_1D_PORT

 /** Bit Define **/
 #define IO_BIT_MEADDH			0x000F
 /** メモリアクセスアドレス 上位 (4Bit) **/
 #define IO_BIT_MEMCR			0x0010
 #define IO_BIT_MEMW			0x0020
 #define IO_BIT_4800			0x0040	/** For Accessing $4802/$4803 by O.Kimoto 1996/12/20 */
 #define IO_BIT_MEACC			0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１ＥＨ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_1E_PORT		(MDM_R288F_BASE_PORT+0x003C)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_1E_PORT		(MDM_R288F_BASE_PORT+0x001E)
#endif

 /** Address Define **/
 #define RDBF_PORT			MDM_REG_1E_PORT
 #define RDBIE_PORT			MDM_REG_1E_PORT
 #define TDBE_PORT			MDM_REG_1E_PORT
 #define TDBIE_PORT			MDM_REG_1E_PORT
 #define RDBIA_PORT			MDM_REG_1E_PORT
 #define TDBIA_PORT			MDM_REG_1E_PORT

 /** Bit Define **/
 #define IO_BIT_RDBF			0x0001
 #define IO_BIT_RDBIE			0x0004
 #define IO_BIT_TDBE			0x0008
 #define IO_BIT_TDBIE			0x0020
 #define IO_BIT_RDBIA			0x0040
 #define IO_BIT_TDBIA			0x0080

/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Oct.30,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムインターフェースＲＡＭ（１ＦＨ）関係
************************************************************************/
#if (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_16BIT)	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define MDM_REG_1F_PORT		(MDM_R288F_BASE_PORT+0x003E)
#elif (PRO_MODEM_AREA_BUS_WIDTH == BUS_WIDTH_8BIT)
	#define MDM_REG_1F_PORT		(MDM_R288F_BASE_PORT+0x001F)
#endif

 /** Address Define **/
 #define NEWC_PORT			MDM_REG_1F_PORT
 #define NCIE_PORT			MDM_REG_1F_PORT
 #define NEWS_PORT			MDM_REG_1F_PORT
 #define NSIE_PORT			MDM_REG_1F_PORT
 #define RCIA_PORT			MDM_REG_1F_PORT
 #define NSIA_PORT			MDM_REG_1F_PORT
 
 /** Bit Define **/
 #define IO_BIT_NEWC			0x0001
 #define IO_BIT_NCIE			0x0004
 #define IO_BIT_NEWS			0x0008
 #define IO_BIT_NSIE			0x0010
 #define IO_BIT_NCIA			0x0040
 #define IO_BIT_NSIA			0x0080


/*********************************************************************** 
*          BY:   O.Kimoto
*        DATE:   Nov.17,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムＩｎｔｅｒＦａｃｅ Ｍｅｍｏｒｙ Ａｃｃｅｓｓ用テーブル構造体
************************************************************************/
struct	MDM_I_O_Memory_t {
	UDWORD Address;
	UBYTE BitPosition;
	UBYTE BitType;
};

#define SW_TYPE 	0
#define VALUE_TYPE	1


#define POS_RBUFFER		  0

#define POS_RXP			  1
#define POS_RXHF		  2
#define POS_TXHF		  3
#define POS_DMY01_3		  4
#define POS_DMY01_4		  5
#define POS_VPAUSE		  6
#define POS_VOLUME		  7

#define POS_CODBITS		  8
#define POS_V54PE		  9
#define POS_V54AE		 10
#define POS_V54TE 		 11
#define POS_SCDE		 POS_V54TE
#define POS_RTSDE		 12
#define POS_SDCEN		 POS_RTSDE
#define POS_DMY02_4		 13
#define POS_CDEN		 POS_DMY02_4
#define POS_S511		 14
#define POS_DCDEN		 POS_S511
#define POS_SQDIS		 15
#define POS_TDE			 16

#define POS_GTS			 17
#define POS_GTE			 18
#define POS_SDIS		 19
#define POS_ARC			 20
#define POS_RLSDE		 21
#define POS_SRCEN		 22
#define POS_SEPT		 23
#define POS_EPT			 24

#define POS_STRN		 25
#define POS_TOD			 26
#define POS_NRZIEN		 27
#define POS_EQFZ		 28
#define POS_FIFOEN		 29
#define POS_V32BS		 30
#define POS_EQT2		 31
#define POS_RB			 32

#define POS_DMY05_0		 33
#define POS_STOFF		 34
#define POS_TTDIS		 35
#define POS_CEQ			 36
#define POS_TXSQ		 37
#define POS_FECSQ		 38
#define POS_FCCR		 POS_FECSQ /* added by H.Kubo 1998/11/12 */
#define POS_ECSQ		 39
#define POS_ECFZ		 40
#define POS_FCCR_FM336	 40

#define POS_WDSZ		 41
#define POS_DECBITS		 POS_WDSZ
#define POS_STB			 42
#define POS_PEN			 43
#define POS_HDLC		 44
#define POS_DMY06_5		 45
#define POS_EXOS		 46
#define POS_RTDIS		 47

#define POS_MHLD		 48
#define POS_RA			 49
#define POS_DMY07_2		 50
#define POS_L3ACT		 51
#define POS_DDIS		 52
#define POS_L2ACT		 53
#define POS_RDL			 54
#define POS_RDLE		 55

#define POS_RTS			 56
#define POS_RTRN		 57
#define POS_V54P		 58
#define POS_V54A		 59
#define POS_V54T		 60
#define POS_V21S		 61
#define POS_TPDM		 62
#define POS_ASYN		 63

#define POS_DTR			 64
#define POS_RRTSE		 65
#define POS_DATA		 66
#define POS_LL			 67
#define POS_ORG			 68
#define POS_DTMF		 69
#define POS_CC			 70
#define POS_NV25		 71

#define POS_SYNCD		 72
#define POS_FLAGS		 73
#define POS_CRCS		 74
#define POS_OE			 75
#define POS_FE			 76
#define POS_PE			 77
#define POS_FLAGDT		 78
#define POS_PNSUC		 79

#define POS_EQMAT		 80
#define POS_DISDET		 81
#define POS_DMY0B_2		 82
#define POS_ATBEL		 83
#define POS_ATV25		 84
#define POS_TONEC		 85
#define POS_TONEB		 86
#define POS_TONEA		 87

#define POS_RSEQ		 88
#define POS_RXFNE		 89
#define POS_SNDET		 90
#define POS_SDET		 91
#define POS_CCDET		 92
#define POS_DET800		 POS_CCDET
#define POS_TPMT		 POS_CCDET /* added by H.Kubo 1998/10/01 */
#define POS_CADET		 93
#define POS_NEGDET		 POS_CADET
#define POS_ACDET		 94
#define POS_MODEOK		 POS_ACDET
#define POS_AADET		 95
#define POS_PROBED		 POS_AADET
#define POS_PCOFF		95 /* For 26P added by H.Kubo 1998/10/30 */

#define POS_HKAB		 96
#define POS_TXFNE		 97
#define POS_SADET		 98
#define POS_DETID		 POS_SADET
#define POS_U1DET		 99
#define POS_ECTRN		 POS_U1DET
#define POS_SCR1		100
#define POS_S1DET		101
#define POS_PNDET		102
#define POS_P2DET		103

#define POS_SPEED		104
#define POS_RREDT		105
#define POS_BRKD		106
#define POS_RTDET		107
#define POS_V54DT		108
#define POS_RTSDT		109

#define POS_TM			110
#define POS_RI			111
#define POS_DSR			112
#define POS_CTS			113
#define POS_FED			114
#define POS_RLSD		115

#define POS_TBUFFER		116

#define POS_TXP			117
#define POS_TEOF		118
#define POS_V23HDX		119
#define POS_RXV			120
#define POS_TXV			121
#define POS_PARSL		122
#define POS_BRKS		123

#define POS_CONF		124

#define POS_TXCLK		125
#define POS_RTH			126
#define POS_TLVL		127

#define POS_ABCODE		128

#define POS_EARC		129
#define POS_EXL3		130
#define POS_RREN		131
#define POS_AUTO		132
#define POS_HWRWK		133
#define POS_RDWK		134
#define POS_DMY15_6		135
#define POS_SLEEP		136

#define POS_SECRXB		137

#define POS_SECTXB		138

#define POS_MEDAL		139

#define POS_MEDAM		140

#define POS_SECEN		141
#define POS_SCIBE		142
#define POS_SCOBF		143
#define POS_DMY1A_3		144
#define POS_DMAE		145
#define POS_RION		146
#define POS_RIEN		147
#define POS_SFRES		148

#define POS_DTMFW		149
#define POS_DTMFD		150
#define POS_OTS			151
#define POS_DTDET		152
#define POS_EDET		153

#define POS_MEADDL		154

#define POS_MEADDH		155
#define POS_MEMCR		156
#define POS_MEMW		157
#define POS_4800		158	/* For Accessing $4802/$4803 By O.Kimoto 1996/12/20 */
#define POS_MEACC		159

#define POS_RDBF		160
#define POS_DMY1E_1		161
#define POS_RDBIE		162
#define POS_TDBE		163
#define POS_DMY1E_4		164
#define POS_TDBIE		165
#define POS_RDBIA		166
#define POS_TDBIA		167

#define POS_NEWC		168
#define POS_DMY1F_1		169
#define POS_NCIE		170
#define POS_NEWS		171
#define POS_NSIE		172
#define POS_DMY1F_5		173
#define POS_NCIA		174
#define POS_NSIA		175

 /*********************************************************************** 
 *          BY:   O.Kimoto
 *        DATE:   Nov.17,1995
*        TYPE:   DEFINE
* VAR TO HOLD:
* DESCRIPTION:   モデムＤＳＰインターフェースＲＡＭ関係
************************************************************************/
#define HIGH_FREQUENCY	1
#define LOW_FREQUENCY	0
#define INHIBIT			0xFFFF

#define MDM_BIT_0		0x0001
#define MDM_BIT_1		0x0002
#define MDM_BIT_2		0x0004
#define MDM_BIT_3		0x0008
#define MDM_BIT_4		0x0010
#define MDM_BIT_5		0x0020
#define MDM_BIT_6		0x0040
#define MDM_BIT_7		0x0080
#define MDM_BIT_8		0x0100
#define MDM_BIT_9		0x0200
#define MDM_BIT_A		0x0400
#define MDM_BIT_B		0x0800
#define MDM_BIT_C		0x1000
#define MDM_BIT_D		0x2000
#define MDM_BIT_E		0x4000
#define MDM_BIT_F		0x8000

#define HIGH_FREQUENCY	1
#define LOW_FREQUENCY	0

/** Trellis Mapping(TX) **/
#define TRELLIS_16_4D	0x00
#define TRELLIS_32_4D	0x10
#define TRELLIS_64_4D	0x18

/** Selected Symbol Rate **/
#define SYMBOL_2400		0
#define SYMBOL_2800		2
#define SYMBOL_3000		3
#define SYMBOL_3200		4
#define SYMBOL_3429		5

/** V.34 Phase 2 Guard Tone Level **/
#define NORMAL_POWER	1
#define UNDER__7DB		0

#define MDM_SPEED_0_300		0
#define MDM_SPEED_600		1
#define MDM_SPEED_1200		2
#define MDM_SPEED_2400		3
#define MDM_SPEED_4800		4
#define MDM_SPEED_7200		5
#define MDM_SPEED_9600		6
#define MDM_SPEED_12000		7
#define MDM_SPEED_14400		8
#define MDM_SPEED_16800		9
#define MDM_SPEED_19200		10
#define MDM_SPEED_21600		11
#define MDM_SPEED_24000		12
#define MDM_SPEED_26400		13
#define MDM_SPEED_28800		14
#define MDM_SPEED_31200		15
#define MDM_SPEED_33600		16

#define MDM_MASK_SPEED_2400			0x0001
#define MDM_MASK_SPEED_4800			0x0002
#define MDM_MASK_SPEED_7200			0x0004
#define MDM_MASK_SPEED_9600			0x0008
#define MDM_MASK_SPEED_12000		0x0010
#define MDM_MASK_SPEED_14400		0x0020
#define MDM_MASK_SPEED_16800		0x0040
#define MDM_MASK_SPEED_19200		0x0080
#define MDM_MASK_SPEED_21600		0x0100
#define MDM_MASK_SPEED_24000		0x0200
#define MDM_MASK_SPEED_26400		0x0400
#define MDM_MASK_SPEED_28800		0x0800
#define MDM_MASK_SPEED_31200		0x1000
#define MDM_MASK_SPEED_33600		0x2000

#endif
