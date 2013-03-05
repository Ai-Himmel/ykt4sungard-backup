/* By M.Kotnai 1996/10/14 */
#include "\src\atlanta\define\cdc_blk.h"
#include "\src\atlanta\define\cdc_def.h"
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 Sep.7,1993
*		 FILE NAME:	 cdc_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 ｺｰﾃﾞｯｸ ﾚｼﾞｽﾀ変数参照 For MN86063
*		 REFERENCE:
************************************************************************/
/* CODEC REGISTER SETTING STATUS */
extern UWORD CodecMSCR_DTCR_Status[];	/*R/W ﾏｽﾀｺﾝﾄﾛｰﾙ,ﾃﾞｰﾀｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
extern UWORD CodecCDCR_Status[];		/*R/W 符号化,復号化ｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
extern UWORD CodecCMDR_Status[];		/*W	  ｺﾏﾝﾄﾞﾚｼﾞｽﾀ*/
extern UWORD CodecSTIR_Status[];		/*R	  状態,割り込みﾚｼﾞｽﾀ*/
extern UWORD CodecDMCR_DMIR_Status[];	/*R/W DMA転送ｺﾝﾄﾛｰﾙ,割り込みﾚｼﾞｽﾀ*/
extern UWORD CodecMAR_Status[];			/*R/W ﾒﾓﾘｱﾄﾞﾚｽﾚｼﾞｽﾀ*/
extern UWORD CodecPBR_Status[];			/*R/W ﾊﾟﾗﾒｰﾀﾊﾞｯﾌｧﾚｼﾞｽﾀ*/
extern UWORD CodecHDMR_MODR_Status[];	/*R/W ﾊｰﾄﾞﾏｽｸﾚｼﾞｽﾀ,ﾓｰﾄﾞﾚｼﾞｽﾀ Only MN86064*/
extern UWORD CodecTSTR_Status[];		/*R/W ﾃｽﾄﾚｼﾞｽﾀ Only MN86064 (アクセスしないでください)*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
extern UWORD CodecC_QMIR_Status[];		/*R   JBIG符号化 QM割り込みレジスタ*/
extern UWORD CodecD_QMIR_Status[];		/*R   JBIG符号化 QM割り込みレジスタ*/
#endif
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 Sep.7,1993
*		 FILE NAME:	 cdc_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 ｺｰﾃﾞｯｸ ﾊﾟﾗﾒｰﾀ ﾚｼﾞｽﾀ変数参照 For MN86063
*		 REFERENCE:
************************************************************************/
/* CODEC PARAMETER REGISTER SETTING STATUS */
extern struct CodecParameterRegisterData_t CodecParameterRegister[];	/*ｺｰﾃﾞｯｸﾊﾟﾗﾒｰﾀ*/
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 Oct.21,1993
*		 FILE NAME:	 cdc_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 ｺｰﾃﾞｯｸの使用状況格納用変数定義 For MN86063
*		 REFERENCE:	 cdc_def.hのCodecIDがｾｯﾄされる
************************************************************************/
extern UBYTE CodecGetID[];				/*ｺｰﾃﾞｯｸを使用しているID*/
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 Apr.22,1994
*		 FILE NAME:	 cdc_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 イメージバッファの使用状態
*		 REFERENCE:	 codec.hの状態がセットされる
************************************************************************/
extern UBYTE CDC_ImageBufferStatus[];	/*[0]=ScannerImageBuffer [1]=PrinterImageBuffer*/
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 Aug.19,1994
*		 FILE NAME:	 cdc_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 コーデックＤＭＡの完了フラグ
*		 REFERENCE:
************************************************************************/
extern UWORD CDC1_DMA1_EndFlag;
extern UWORD CDC0_DMA0_EndFlag;

/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 Nov.16,1994
*		 FILE NAME:	 cdc_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 コーデックＤＭＡの完了カウンタ
*		 REFERENCE:
************************************************************************/
extern UWORD CDC0_DMA0_EndCounter;

/* #if(1) */
/************************************************************************
*				BY:	 坂本直史
*			  DATE:	 Feb.14,1995
*		 FILE NAME:	 cdc_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 杏テスト用
*		 REFERENCE:
************************************************************************/
extern	UBYTE	SetInLineNumber;
extern	UBYTE	InLineNumber;
extern	UBYTE	FinishInLineNumber;
extern	UBYTE	InLineResetFlag;
extern	UBYTE	CDC_INT_SCNLineNumber;
	/* '95,03,22 */
extern	UWORD		CDC_SCN_CommandStartCount;
extern	UWORD		CDC_SCN_CommandEndCount;
extern	UWORD		CDC_COM_CommandStartCount;
extern	UWORD		CDC_COM_CommandEndCount;
extern	UWORD		CDC_COM_ErrorLineCounter;
/* #endif */
/* for Debag By T.Yamaguchi 96/07/03 */
extern	UBYTE	CodecExecutingFlag;		/* コーデック実行中フラグ */

extern UWORD CDC_DocumentScanLine;	/* FBS原稿の残り読取りライン数(減算する) T.Nose 1997/02/01 */
extern UBYTE CDC_WaitingCDC0_DMA0_END; /**IDPからイメージメモリ53LinesのDMA終了を待つ 1997/05/09 H.Yoshikawa */

extern UWORD DEBUG_CDC_DecodeError;	/* debug */

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
extern UBYTE Is_JBIG_Restart;	/**	JBIGリスタート */
extern struct JBG_BIH_Data_t CDC_JBG_BIH;	/** ２０バイト */
extern UBYTE dummy_line;
#endif

#if (PRO_SCN_CODEC_TYPE == SOFTWARE) /* 1998/11/04 By H.Hirao */
extern UWORD tskno_CDC_STxDMA_Task;
#endif
#if (PRO_PRINTER_RX == ENABLE) /* 1998/11/17 by H.Hirao */
extern UWORD tskno_CDC_PRxDMA_Task;
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*1999.2.5 K.Kawata */
extern UWORD tskno_CDC_PRxDMA_Task;
#endif
#if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
extern UWORD CDC_ReadPageCount;
#endif
