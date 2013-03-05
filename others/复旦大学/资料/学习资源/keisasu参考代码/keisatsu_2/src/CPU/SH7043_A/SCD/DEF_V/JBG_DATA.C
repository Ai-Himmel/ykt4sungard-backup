/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/22
*		 FILE NAME:	 jbg_data.c
*		Task ID No:	 Not Valid
*	   DESCRIPTION:	 T.82(JBIG) 用大域変数
*		 REFERENCE:
************************************************************************/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\jbg_def.h"
#else
#include "\src\atlanta\scd\define\jbg_def.h"
#endif

/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/24
*	   DESCRIPTION:	 T.82(JBIG) 入出力アドレスポインタ
*		 REFERENCE:
************************************************************************/
UBYTE	far *JBG_ImagePtr = 0;
UBYTE	far *JBG_CodePtr = 0;
UWORD	far *JBG_RlPtr = 0;
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/22
*	   DESCRIPTION:	 T.82(JBIG) ＢＩＨ(bi-level image header)
*		 REFERENCE:
************************************************************************/
struct JBG_BIH_Data_t JBG_BIH = {0};	/** ２０バイト */
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/30
*	   DESCRIPTION:	 T.82(JBIG) ＡＴＭＯＶＥ
*		 REFERENCE:
************************************************************************/
struct JBG_ATMOVE_Data_t JBG_ATMOVE = {0};	/** ８バイト */
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/30
*	   DESCRIPTION:	 T.82(JBIG) ＮＥＷＬＥＮ
*		 REFERENCE:
************************************************************************/
struct JBG_NEWLEN_Data_t JBG_NEWLEN = {0};	/** ６バイト */
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/30
*	   DESCRIPTION:	 T.82(JBIG) ＣＯＭＭＥＮＴ
*		 REFERENCE:
************************************************************************/
struct JBG_COMMENT_Data_t JBG_COMMENT = {0};	/** ６バイト */
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/22
*	   DESCRIPTION:	 T.82(JBIG) ＡＡＥ／ＡＡＤ用大域変数(Adaptive Arithmetic Encoder/Decoder)
*		 REFERENCE:
************************************************************************/
UDWORD	JBG_C_Register = 0;			/** コードレジスタ */
UDWORD	JBG_A_Register = 0;			/** インタバルサイズレジスタ */
UDWORD	JBG_CT_Counter = 0;			/** ビットカウンタ */
UDWORD	JBG_SC_StackCounter = 0;	/** 0xffバイトのスタックカウンタ */
UWORD	JBG_St[JBG_MAX_CX] = {0};	/** 状態 */
UBYTE	JBG_Mps[JBG_MAX_CX] = {0};	/** 優勢シンボル */
UBYTE	JBG_Pix = 0;				/** 画素 */
UWORD	JBG_Cx = 0;					/** コンテクスト */
UBYTE	JBG_TpValue = 0;			/** ＴＰ値 */
UBYTE	JBG_DpValue = 0;			/** ＤＰ値 */
UWORD	JBG_Buffer = 0;				/** バッファ */
UWORD	JBG_Ec = 0;					/** イベントカウンタ */
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/27
*	   DESCRIPTION:	 T.82(JBIG) ＴＰＢ用大域変数(Typical Prediction (Bottom))
*		 REFERENCE:
************************************************************************/
UBYTE JBG_SlntpY = 0;	/** ＳＬＮＴＰ　ｙ */
UBYTE JBG_LntpY = 0;	/** ＬＮＴＰ　ｙ */
UBYTE JBG_LntpY_1 = 0;	/** ＬＮＴＰ　ｙ－１ */
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/24
*	   DESCRIPTION:	 T.82(JBIG) ドライバが使用する大域変数
*		 REFERENCE:
************************************************************************/
UBYTE	JBG_RequestATMOVE = 0;			/** ＡＴＭＯＶＥフローティングマーカーセグメントの作成要求 */
UBYTE	JBG_RequestNEWLWN = 0;			/** ＮＥＷＬＥＮフローティングマーカーセグメントの作成要求 */
UBYTE	JBG_RequestCOMMENT = 0;			/** ＣＯＭＭＥＮＴフローティングマーカーセグメントの作成要求 */
UBYTE	JBG_RequestSDNORM = 0;			/** ＳＤＮＯＲＭの作成要求 */
UBYTE	JBG_RequestSDRST = 0;			/** ＳＤＲＳＴの作成要求 */
UDWORD 	JBG_EncodeLineCount = 0;		/** 符号化しているライン */
UDWORD 	JBG_DecodeLineCount = 0;		/** 復号化しているライン */
UDWORD 	JBG_EncodeStripeCount = 0;		/** 符号化しているストライプ番号 */
UDWORD 	JBG_DecodeStripeCount = 0;		/** 復号化しているストライプ番号 */
UDWORD 	JBG_EncodeStripeLineCount = 0;	/** ストライプ中の符号化しているライン */
UDWORD 	JBG_DecodeStripeLineCount = 0;	/** ストライプ中の復号化しているライン */
UBYTE 	JBG_IsDecodeSDE = 0;			/** ＳＤＥを復号化中 */
UBYTE	JBG_DecodeEndStatus = 0;		/** デコード終了時の状態 */
UWORD	JBG_PixByteP = 0;				/** バイトのイメージデータ */
UWORD	JBG_PixByteBitP = 0;			/** バイトのイメージデータのビット位置 */
UWORD	JBG_RlCounter = 0;				/** ＲＬカウンタ */
UBYTE	JBG_RlPix = 0;					/** ＲＬの白黒論理 */
UBYTE	JBG_IsFirstScd = 0;				/** 最初のＳＣＤ（出力しないようにするため） */
UWORD	JGB_NullCount = 0;				/** ストライプ最後のＮＵＬＬの個数 */
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/24
*	   DESCRIPTION:	 T.82(JBIG) 参照ラインバッファ（３ラインテンプレートに対応）
*		 REFERENCE:
************************************************************************/
UBYTE	JBG_ReferenceLineBuffer[JBG_MAX_REFERENCE_Y][JBG_MAX_REFERENCE_X] = {0};
UWORD	JBG_ReferenceLineX_Ptr = 0;
UBYTE	JBG_ReferenceLineY_Ptr = 0;
UBYTE	JBG_PreLineY_Ptr = 0;
UBYTE	JBG_PrePreLineY_Ptr = 0;
UBYTE	JBG_PrePreLineCx = 0;		/** 前々参照ラインコンテクスト */
UBYTE	JBG_PreLineCx = 0;			/** 前参照ラインコンテクスト */
UBYTE	JBG_LineCx = 0;				/** 参照ラインコンテクスト */
UBYTE	JBG_PrePrePix = 0;			/** 前々画素 */
UBYTE	JBG_PrePix = 0;				/** 前画素 */

