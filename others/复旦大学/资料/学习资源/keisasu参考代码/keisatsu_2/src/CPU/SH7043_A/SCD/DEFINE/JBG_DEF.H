/*
 *  jgb_def.h  1997/01/22  T.82(JBIG) 定義  By M.Kotani
 */
#ifndef	jbg_def_h
	#define	jbg_def_h

#include	"\src\atlanta\define\product.h"

#define JBG_DEBUG 0
/***********************************************************************
*          BY:   M.Kotani
*        DATE:   1997/01/22
*        TYPE:   DEFINE
* VAR TO HOLD:   N/A
* DESCRIPTION:   最大値定義
************************************************************************/
#define JBG_BYTE_MARGIN_LEFT		1				/** ４画素 */
#define JBG_BYTE_MARGIN_RIGHT		1				/** ２画素 */
#define JBG_MAX_REFERENCE_X		(912 + JBG_BYTE_MARGIN_LEFT + JBG_BYTE_MARGIN_RIGHT)	/** 参照ライン(A3 600DPI)7296Dots */
#define JBG_MAX_REFERENCE_Y		3		/** 参照ライン(3 Lines) (y, y-1. y-2)*/
#define JBG_MAX_CX				1024	/** コンテクスト２値１０画素＝１０２４値*/
#define JBG_MAX_ST				113		/** 確率推定ステータス ０～１１２＝１１３値*/
/***********************************************************************
*          BY:   M.Kotani
*        DATE:   1997/01/30
*        TYPE:   DEFINE
* VAR TO HOLD:   JBG_DecodeEndStatus
* DESCRIPTION:   デコード終了時の状態
************************************************************************/
#define JBG_BIT_RESET	0x01				/** ストライプ終了時にパラメータリセット要求あり */
#define JBG_BIT_END		0x02				/** ストライプ正常終了 */
#define JBG_BIT_ABORT	0x04				/** ストライプ異常終了 */
#define JBG_BIT_ERROR	0x80				/** デコードエラー発生 */
/***********************************************************************
*          BY:   M.Kotani
*        DATE:   1997/01/24
*        TYPE:   DEFINE
* VAR TO HOLD:   N/A
* DESCRIPTION:   記号化された定数
************************************************************************/
#define JBG_SYMBOL_ABORT	0x04	/** アボート */
#define JBG_SYMBOL_ATMOVE	0x06	/** ＡＴ移動 */
#define JBG_SYMBOL_COMMENT	0x07	/** プライベートコメント */
#define JBG_SYMBOL_ESC		0xff	/** エスケープ */
#define JBG_SYMBOL_NEWLEN	0x05	/** 新しい長さ */
#define JBG_SYMBOL_RESERVE	0x01	/** リザーブ */
#define JBG_SYMBOL_SDNORM	0x02	/** ストライプデータ終了 */
#define JBG_SYMBOL_SDRST	0x03	/** ストライプデータ終了時のリセット */
#define JBG_SYMBOL_STUFF	0x00	/** スタッフ */
/***********************************************************************
*          BY:   M.Kotani
*        DATE:   1997/01/23
*        TYPE:   DEFINE
* VAR TO HOLD:   N/A
* DESCRIPTION:   オーダーバイトのビット定義
************************************************************************/
#define JBG_BIT_SMID	0x01	/** 中央のループインデックスはストライプ	（Ｔ．８５では０固定） */
#define JBG_BIT_ILEAVE	0x02	/** インタリーブされた複数のビットプレーン	（Ｔ．８５では０固定） */
#define JBG_BIT_SEQ		0x04	/** シーケンシャル							（Ｔ．８５では０固定） */
#define JBG_BIT_HITOLO	0x08	/** 上位から下位へ							（Ｔ．８５では０固定） */
/***********************************************************************
*          BY:   M.Kotani
*        DATE:   1997/01/23
*        TYPE:   DEFINE
* VAR TO HOLD:   N/A
* DESCRIPTION:   オプションバイトのビット定義
************************************************************************/
#define JBG_BIT_DPLAST	0x01	/** 最後のＤＰ								（Ｔ．８５では０固定） */
#define JBG_BIT_DPPRIV	0x02	/** プライベートＤＰ						（Ｔ．８５では０固定） */
#define JBG_BIT_DPON	0x04	/** ＤＰ使用								（Ｔ．８５では０固定） */
#define JBG_BIT_TPBON	0x08	/** 最低解像度レイヤのＴＰ使用　０：ＯＦＦ、１：ＯＮ */
#define JBG_BIT_TPDON	0x10	/** 差分レイヤのＴＰを使用する				（Ｔ．８５では０固定） */
#define JBG_BIT_VLENGTH	0x20	/** ０：ＮＥＷＬＥＮを使用しない、１：ＮＥＷＬＥＮ使用をする */
#define JBG_BIT_LRLTWO	0x40	/** ０：３ラインテンプレート、１：２ラインテンプレート */
/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/01/23
*             TYPE:  struct
*      VAR TO HOLD:  JBG_BIH
*      DESCRIPTION:  ＢＩＨ定義(bi-level image header)
************************************************************************/
struct JBG_BIH_Data_t {	/** ２０バイト */
	UBYTE	DL;			/** 送るべき最初のレイヤ	（Ｔ．８５では０固定） */
	UBYTE	D;			/** 差分レイヤの数			（Ｔ．８５では０固定） */
	UBYTE	P;			/** ビットプレーン数		（Ｔ．８５では１固定） */
	UBYTE	dummy;		/** フィルバイト			（Ｔ．８２で０固定） */
	UDWORD	XD;			/** 水平方向の画素数（Ｔ．８５ではＧ３はＴ．４、Ｇ４はＴ．５６３に準拠） */
	UDWORD	YD;			/** 垂直方向の画素数（Ｔ．８２で１～４２９４９６７２９５） */
	UDWORD	L0;			/** 最低解像度のストライブのライン数（Ｔ．８５で１２８ライン固定、独自手順で変更可能） */
	UBYTE	MX;			/** ＡＴ画素に許される最大水平オフセット（Ｔ．８５では０～１２７） */
	UBYTE	MY;			/** ＡＴ画素に許される最大垂直オフセット（Ｔ．８５では０固定） */
	UBYTE	Order;		/** ＳＣＤの順序（オーダービット定義参照） */
	UBYTE	Options;	/** オプション（オプションビット定義参照） */
};
/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/01/30
*             TYPE:  struct
*      VAR TO HOLD:  JBG_ATMOVE
*      DESCRIPTION:  ＡＴＭＯＶＥ
************************************************************************/
struct JBG_ATMOVE_Data_t {	/** ８バイト */
	UBYTE	Esc;
	UBYTE	Atmove;
	UDWORD	Yat;
	UBYTE	Tx;
	UBYTE	Ty;
};
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/30
*	   DESCRIPTION:	 T.82(JBIG) ＮＥＷＬＥＮ
*		 REFERENCE:
************************************************************************/
struct JBG_NEWLEN_Data_t {	/** ６バイト */
	UBYTE	Esc;
	UBYTE	Newlen;
	UDWORD	Yd;
};
/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1997/01/30
*	   DESCRIPTION:	 T.82(JBIG) ＣＯＭＭＥＮＴ
*		 REFERENCE:
************************************************************************/
struct JBG_COMMENT_Data_t {	/** ６バイト */
	UBYTE	Esc;
	UBYTE	Comment;
	UDWORD	Lc;
};

#endif
