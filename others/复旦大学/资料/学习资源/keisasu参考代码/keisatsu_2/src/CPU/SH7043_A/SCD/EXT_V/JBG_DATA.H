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
extern UBYTE	far *JBG_ImagePtr;
extern UBYTE	far *JBG_CodePtr;
extern UWORD		far *JBG_RlPtr;
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/22
*	   DESCRIPTION:	 T.82(JBIG) ＢＩＨ(bi-level image header)
*		 REFERENCE:
************************************************************************/
extern struct JBG_BIH_Data_t JBG_BIH;	/** ２０バイト */
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/30
*	   DESCRIPTION:	 T.82(JBIG) ＡＴＭＯＶＥ
*		 REFERENCE:
************************************************************************/
extern struct JBG_ATMOVE_Data_t JBG_ATMOVE;	/** ８バイト */
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/30
*	   DESCRIPTION:	 T.82(JBIG) ＮＥＷＬＥＮ
*		 REFERENCE:
************************************************************************/
extern struct JBG_NEWLEN_Data_t JBG_NEWLEN;	/** ６バイト */
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/30
*	   DESCRIPTION:	 T.82(JBIG) ＣＯＭＭＥＮＴ
*		 REFERENCE:
************************************************************************/
extern struct JBG_COMMENT_Data_t JBG_COMMENT;	/** ６バイト */
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/22
*	   DESCRIPTION:	 T.82(JBIG) ＡＡＥ／ＡＡＤ用大域変数(Adaptive Arithmetic Encoder/Decoder)
*		 REFERENCE:
************************************************************************/
extern UDWORD	JBG_C_Register;			/** コードレジスタ */
extern UDWORD	JBG_A_Register;			/** インタバルサイズレジスタ */
extern UDWORD	JBG_CT_Counter;			/** ビットカウンタ */
extern UDWORD	JBG_SC_StackCounter;	/** 0xffバイトのスタックカウンタ */
extern UWORD		JBG_St[JBG_MAX_CX];		/** 状態 */
extern UBYTE	JBG_Mps[JBG_MAX_CX];	/** 優勢シンボル */
extern UBYTE	JBG_Pix;				/** 画素 */
extern UWORD		JBG_Cx;					/** コンテクスト */
extern UBYTE	JBG_TpValue;			/** ＴＰ値 */
extern UBYTE	JBG_DpValue;			/** ＤＰ値 */
extern UWORD		JBG_Buffer;				/** バッファ */
extern UWORD		JBG_Ec;					/** イベントカウンタ */
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/27
*	   DESCRIPTION:	 T.82(JBIG) ＴＰＢ用大域変数(Typical Prediction (Bottom))
*		 REFERENCE:
************************************************************************/
extern UBYTE JBG_SlntpY;	/** ＳＬＮＴＰ　ｙ */
extern UBYTE JBG_LntpY;		/** ＬＮＴＰ　ｙ */
extern UBYTE JBG_LntpY_1;	/** ＬＮＴＰ　ｙ－１ */
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/24
*	   DESCRIPTION:	 T.82(JBIG) ドライバが使用する大域変数
*		 REFERENCE:
************************************************************************/
extern UBYTE	JBG_RequestATMOVE;			/** ＡＴＭＯＶＥフローティングマーカーセグメントの作成要求 */
extern UBYTE	JBG_RequestNEWLWN;			/** ＮＥＷＬＥＮフローティングマーカーセグメントの作成要求 */
extern UBYTE	JBG_RequestCOMMENT;			/** ＣＯＭＭＥＮＴフローティングマーカーセグメントの作成要求 */
extern UBYTE	JBG_RequestSDNORM;			/** ＳＤＮＯＲＭの作成要求 */
extern UBYTE	JBG_RequestSDRST;			/** ＳＤＲＳＴの作成要求 */
extern UDWORD 	JBG_EncodeLineCount;		/** 符号化しているライン */
extern UDWORD 	JBG_DecodeLineCount;		/** 復号化しているライン */
extern UDWORD 	JBG_EncodeStripeCount;		/** 符号化しているストライプ番号 */
extern UDWORD 	JBG_DecodeStripeCount;		/** 復号化しているストライプ番号 */
extern UDWORD 	JBG_EncodeStripeLineCount;	/** ストライプ中の符号化しているライン */
extern UDWORD 	JBG_DecodeStripeLineCount;	/** ストライプ中の復号化しているライン */
extern UBYTE 	JBG_IsDecodeSDE;			/** ＳＤＥを復号化中 */
extern UBYTE	JBG_DecodeEndStatus;		/** デコード終了時の状態 */
extern UWORD		JBG_PixByteP;				/** バイトのイメージデータ */
extern UWORD		JBG_PixByteBitP;			/** バイトのイメージデータのビット位置 */
extern UWORD		JBG_RlCounter;				/** ＲＬカウンタ */
extern UBYTE	JBG_RlPix;					/** ＲＬの白黒論理 */
extern UBYTE	JBG_IsFirstScd;				/** 最初のＳＣＤ（出力しないようにするため） */
extern UWORD		JGB_NullCount;				/** ストライプ最後のＮＵＬＬの個数 */
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/24
*	   DESCRIPTION:	 T.82(JBIG) 参照ラインバッファ（３ラインテンプレートに対応）
*		 REFERENCE:
************************************************************************/
extern UBYTE	JBG_ReferenceLineBuffer[JBG_MAX_REFERENCE_Y][JBG_MAX_REFERENCE_X];
extern UWORD		JBG_ReferenceLineX_Ptr;
extern UBYTE	JBG_ReferenceLineY_Ptr;
extern UBYTE	JBG_PreLineY_Ptr;
extern UBYTE	JBG_PrePreLineY_Ptr;
extern UBYTE	JBG_PrePreLineCx;	/** 前々参照ラインコンテクスト */
extern UBYTE	JBG_PreLineCx;		/** 前参照ラインコンテクスト */
extern UBYTE	JBG_LineCx;			/** 参照ラインコンテクスト */
extern UBYTE	JBG_PrePrePix;			/** 前々画素 */
extern UBYTE	JBG_PrePix;			/** 前画素 */


