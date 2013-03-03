/*	By Y.Suzuki 1996/10/12	*/
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\cdc_blk.h"

/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 Sep.7,1993
*		 FILE NAME:	 cdc_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 ｺｰﾃﾞｯｸ ﾚｼﾞｽﾀ変数定義 For MN86063
*		 REFERENCE:
************************************************************************/
/* CODEC REGISTER SETTING STATUS */
UWORD CodecMSCR_DTCR_Status[CODEC_MAX]	= {0};	/*R/W ﾏｽﾀｺﾝﾄﾛｰﾙ,ﾃﾞｰﾀｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
UWORD CodecCDCR_Status[CODEC_MAX]		= {0};	/*R/W 符号化,復号化ｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
UWORD CodecCMDR_Status[CODEC_MAX]		= {0};	/*W	  ｺﾏﾝﾄﾞﾚｼﾞｽﾀ*/
UWORD CodecSTIR_Status[CODEC_MAX]		= {0};	/*R	  状態,割り込みﾚｼﾞｽﾀ*/
UWORD CodecDMCR_DMIR_Status[CODEC_MAX]	= {0};	/*R/W DMA転送ｺﾝﾄﾛｰﾙ,割り込みﾚｼﾞｽﾀ*/
UWORD CodecMAR_Status[CODEC_MAX]		= {0};	/*R/W ﾒﾓﾘｱﾄﾞﾚｽﾚｼﾞｽﾀ*/
UWORD CodecPBR_Status[CODEC_MAX]		= {0};	/*R/W ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧﾚｼﾞｽﾀ*/
UWORD CodecHDMR_MODR_Status[CODEC_MAX]	= {0};	/*R/W ﾊｰﾄﾞﾏｽｸﾚｼﾞｽﾀ,ﾓｰﾄﾞﾚｼﾞｽﾀ Only MN86064*/
UWORD CodecTSTR_Status[CODEC_MAX]		= {0};	/*R/W ﾃｽﾄﾚｼﾞｽﾀ Only MN86064 (アクセスしないでください)*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
UWORD CodecC_QMIR_Status[CODEC_MAX]		= {0};	/*R   JBIG符号化 QM割り込みレジスタ*/
UWORD CodecD_QMIR_Status[CODEC_MAX]		= {0};	/*R   JBIG符号化 QM割り込みレジスタ*/
#endif
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 Sep.7,1993
*		 FILE NAME:	 cdc_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 ｺｰﾃﾞｯｸ ﾊﾟﾗﾒｰﾀ ﾚｼﾞｽﾀ変数定義 For MN86063
*		 REFERENCE:
************************************************************************/
/* CODEC PARAMETER REGISTER SETTING STATUS */
struct CodecParameterRegisterData_t CodecParameterRegister[CODEC_MAX] = {0};	/*ｺｰﾃﾞｯｸﾊﾟﾗﾒｰﾀ*/
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 Oct.21,1993
*		 FILE NAME:	 cdc_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 ｺｰﾃﾞｯｸの使用状況格納用変数定義 For MN86063
*		 REFERENCE:	 cdc_def.hのCodecIDがｾｯﾄされる
************************************************************************/
UBYTE CodecGetID[CODEC_MAX] = {0};	/*ｺｰﾃﾞｯｸを使用しているID*/
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 Apr.22,1994
*		 FILE NAME:	 cdc_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 イメージバッファの使用状態
*		 REFERENCE:	 cdc_def.hの状態がセットされる
************************************************************************/
UBYTE CDC_ImageBufferStatus[CODEC_MAX] = {0};	/*[0]=ScannerImageBuffer [1]=PrinterImageBuffer*/

/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 Aug.19,1994
*		 FILE NAME:	 cdc_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 コーデックＤＭＡの完了フラグ
*		 REFERENCE:
************************************************************************/
UWORD CDC1_DMA1_EndFlag = 0;
UWORD CDC0_DMA0_EndFlag = 0;

/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 Nov.16,1994
*		 FILE NAME:	 cdc_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 コーデックＤＭＡの完了カウンタ
*		 REFERENCE:
************************************************************************/
UWORD CDC0_DMA0_EndCounter = 0;


/* #if(0) */
/************************************************************************
*				BY:	 坂本直史
*			  DATE:	 Feb.14,1995
*		 FILE NAME:	 cdc_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 杏テスト用
*		 REFERENCE:
************************************************************************/
UBYTE	SetInLineNumber			  = 0;
UBYTE	InLineNumber			  = 0;
UBYTE	FinishInLineNumber		  = 0;
UBYTE	InLineResetFlag			  = 0;
UBYTE	CDC_INT_SCNLineNumber	  = 0;
	/* '95,03,22 */
UWORD				CDC_SCN_CommandStartCount = 0;
UWORD				CDC_SCN_CommandEndCount	  = 0;
UWORD				CDC_COM_CommandStartCount = 0;
UWORD				CDC_COM_CommandEndCount	  = 0;
UWORD				CDC_COM_ErrorLineCounter  = 0;
/* #endif */

/* for Debag By T.Yamaguchi 96/07/03 */
UBYTE	CodecExecutingFlag		  = 0;		/* コーデック実行中フラグ */


#if (PRO_CPU == SH7043)
/************************************************************************
*				BY:	 野瀬敏弘
*			  DATE:	 05/15/1996
*		 FILE NAME:	 cdc_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 RISCコーデックテスト用
*		 REFERENCE:
************************************************************************/
UWORD DEBUG_AddressBuffer[30][2] = {0};
UBYTE DEBUG_DMA_Counter = 0;
UBYTE DEBUG_EncodeCounter = 0;
UBYTE DEBUG_ScanLine = 0;
#endif

UWORD CDC_DocumentScanLine = 0;		/* FBS原稿の残り読取りライン数(減算する) T.Nose 1997/02/01 */
UBYTE CDC_WaitingCDC0_DMA0_END = 0; /**IDPからイメージメモリ53LinesのDMA終了を待つ 1997/05/09 H.Yoshikawa */

UWORD DEBUG_CDC_DecodeError = 0;	/* debug */

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
UBYTE Is_JBIG_Restart = 0;	/**	JBIGリスタート */
struct JBG_BIH_Data_t CDC_JBG_BIH = {0};	/** ２０バイト */
UBYTE dummy_line = 0;
#endif

#if (PRO_SCN_CODEC_TYPE == SOFTWARE) /* 1998/11/04 by H.Hirao */
UWORD tskno_CDC_STxDMA_Task = 0;
#endif
#if (PRO_PRINTER_RX == ENABLE) /* 1998/11/17 by H.Hirao */
UWORD tskno_CDC_PRxDMA_Task = 0;
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*1999.2.5 K.Kawata */
UWORD tskno_CDC_PRxDMA_Task = 0;
#endif
#if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
UWORD CDC_ReadPageCount = 0;
#endif
