/************************************************************************
*	System		: SAKAKI
*	File Name	: GA_DATA.C
*	Author		: 吉川弘康
*	Date		: 1998/05/28
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 
*	Maintenance	: MOMIJI用からSAKAKI用に変更した。
*				  MD9401/MD9402へのアクセスはWORDで行うように変更する。MOMIJIではBYTEであった。
*				  該当する変数をUBYTEからUWORDに変更する。1998/06/25
*
*	Copyright (C) 1998 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
/************************************************
 * ＭＤ９４０１用各状態変数
 *	木元　修
 *	Jan,10,1994
 ************************************************/
/** ＭＤ９４０１用各状態変数 **/
/** スムージングＧ／Ａ **/
UWORD	BK1_1_Status	= 0;		/** バスＩ／Ｆレジスタ **/
UWORD	BK2_Status		= 0;		/** ＲＡＭＩ／Ｆレジスタ **/
UWORD	BK4_1_Status	= 0;		/** 検索コードレジスタ１ **/
UWORD	BK4_2_Status	= 0;		/** 検索コードレジスタ２ **/
UWORD	BK4_3_Status	= 0;		/** 検索コードレジスタ３ **/
UWORD	BK4_4_Status	= 0;		/** 検索コードレジスタ４ **/
UWORD	BK4_5_Status	= 0;		/** 検索コードレジスタ５ **/
UWORD	BK4_6_Status	= 0;		/** 検索コードレジスタ６ **/
UWORD	SUNO_Status		= 0;		/** スムージング／ノッチレジスタ **/
UWORD	VNO_Status		= 0;		/** 縦ノッチレジスタ **/
UWORD	HNO_Status		= 0;		/** 横ノッチレジスタ１ **/
UWORD	KORITU_W_Status	= 0;		/** 孤立点レジスタ１ **/
UWORD	KORITU_B_Status	= 0;		/** 孤立点レジスタ２ **/
UWORD	SYSSR_Status	= 0;		/** システムステータス（エッジ検出）レジスタ **/
UWORD	BK6_Status		= 0;		/** スルーレジスタ **/
UWORD	BK1_2_Status	= 0;		/** 拡大レジスタ **/
/**  **/
UWORD	A_MCR1_Status	= 0;		/** Ａモーター（　ＴＸモーター）コントロールレジスター１ **/
UWORD	A_MCR2_Status	= 0;		/** Ａモーター（　ＴＸモーター）コントロールレジスター２ **/
UWORD	B_MCR1_Status	= 0;		/** Ｂモーター（　ＲＸモーター）コントロールレジスター１ **/
UWORD	B_MCR2_Status	= 0;		/** Ｂモーター（　ＲＸモーター）コントロールレジスター２ **/
UWORD	C_MCR1_Status	= 0;		/** Ｃモーター（ＩＤＦモーター）コントロールレジスター１ **/
UWORD	C_MCR2_Status	= 0;		/** Ｃモーター（ＩＤＦモーター）コントロールレジスター２ **/
UWORD	SYSCR_Status	= 0;		/** システムコントロールレジスタ **/
UWORD	TRCR_Status		= 0;		/** コントロールレジスタ **/
UWORD	TROSS_Status	= 0;		/** 出力転送開始スタート設定レジスタ **/
UWORD	TROF1_Status	= 0;		/** 出力データ転送１フォーマットレジスタ **/
UWORD	TROF2_Status	= 0;		/** 出力データ転送２フォーマットレジスタ **/
UWORD	STCR1_Status	= 0;		/** コントロールレジスタ１（ヒートパルス幅設定レジスタ） **/
UWORD	STCR2_Status	= 0;		/** コントロールレジスタ２ **/
UWORD	STCR3_Status	= 0;		/** コントロールレジスタ３ **/
UWORD	STCR4_Status	= 0;		/** コントロールレジスタ４ **/
UWORD	TRISA_Status	= 0;		/** 入力データスタートアドレスレジスタ **/
UWORD	TRIEA_Status	= 0;		/** 入力データエンドアドレスレジスタ **/
UWORD	SCR_Status		= 0;		/** システムステータスレジスタ１ **/
UWORD	SMCR_Status		= 0;		/** システムステータスレジスタ２ **/
UWORD	STCR5_Status	= 0;		/** コントロールレジスタ４ **/

/** ＭＤ９４０２用各状態変数 **/
UWORD	M01_Status		= 0;		/** ＭＤ９４０２　アドレス０５７０Ｈ用ステータス **/
UWORD	M02_Status		= 0;		/** ＭＤ９４０２　アドレス０５７２Ｈ用ステータス **/
UWORD	M03_Status		= 0;		/** ＭＤ９４０２　アドレス０５７４Ｈ用ステータス **/
UWORD	M04_Status		= 0;		/** ＭＤ９４０２　アドレス０５７６Ｈ用ステータス **/
UWORD	M05_Status		= 0;		/** ＭＤ９４０２　アドレス０５７８Ｈ用ステータス **/
UWORD	M06_Status		= 0;		/** ＭＤ９４０２　アドレス０５７ＡＨ用ステータス **/
UWORD	M07_Status		= 0;		/** ＭＤ９４０２　アドレス０５７ＣＨ用ステータス **/
UWORD	M08_Status		= 0;		/** ＭＤ９４０２　アドレス０５７ＥＨ用ステータス **/
UWORD	M09_Status		= 0;		/** ＭＤ９４０２　アドレス０５８０Ｈ用ステータス **/
UWORD	M0A_Status		= 0;		/** ＭＤ９４０２　アドレス０５８２Ｈ用ステータス **/
UWORD	M0B_Status		= 0;		/** ＭＤ９４０２　アドレス０５８４Ｈ用ステータス **/
UWORD	M0C_Status		= 0;		/** ＭＤ９４０２　アドレス０５８６Ｈ用ステータス **/

#if (0)	/* 1998/06/25 */
//UWORD  ga_register00[45] = {0};	/**  By O.K Aug,22,1994 **/
//UWORD  ga_register01[45] = {0};	/**  By O.K Aug,22,1994 **/
//UWORD  ga_register10[45] = {0};	/**  By O.K Aug,22,1994 **/
//UWORD  ga_register11[45] = {0};	/**  By O.K Aug,22,1994 **/
#endif

UBYTE DIPPST_Req = 0;				/* 1998/10/12 */
UBYTE AdjustTimerInterrupt = 0;	/* 1998/10/12 */

UBYTE  ScnMotorPhase = 0;	/**  By O.K Sep,06,1994 **/
UBYTE  HeadRegisterRank = 0;	/**  By O.K Sep,14,1994 **/
UBYTE  GaInterruptFlag = 0;	/** By O.K Oct,13,1994 **/
UBYTE  GA_BuzzerFlag = 0;	/** By O.K Nov,02,1994 **/
