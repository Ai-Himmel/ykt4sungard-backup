/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/01/24
*        FILE NAME:  jbg_init.c
*       Task ID No:
*      DESCRIPTION:  T.82(JBIG)ドライバーの初期化関数群
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:
*        REFERENCE:
*************************************************************************/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\jbg_def.h"
#include "\src\cpu\sh7043_a\scd\define\jbg_pro.h"
#include "\src\cpu\sh7043_a\scd\ext_v\jbg_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\jbg_tbl.h"
#else
#include "\src\atlanta\scd\define\jbg_def.h"
#include "\src\atlanta\scd\define\jbg_pro.h"
#include "\src\atlanta\scd\ext_v\jbg_data.h"
#include "\src\atlanta\scd\ext_v\jbg_tbl.h"
#endif

/*************************************************************************
	module		:[
		T.82(JBIG)ドライバー大域変数の初期化
	]
	function	:[
		1.大域変数の初期化
	]
	return		:[なし]
	common		:[
	]
	condition	:[
		タスククリエイト時にのみコールされる
	]
	comment		:[
		すべての大域変数が初期化される
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/24]
	author		:[小谷正樹]
*************************************************************************/
void JBG_InitializeGlobalValue(void)
{
	UWORD loop1;
	UWORD loop2;

	for (loop1 = 0; loop1 < JBG_MAX_REFERENCE_Y; loop1++) {
		for (loop2 = 0; loop2 < JBG_MAX_REFERENCE_X; loop2++) {
			JBG_ReferenceLineBuffer[loop1][loop2] = 0;	/** 参照ラインの初期化 */
		}
	}
	JBG_ReferenceLineX_Ptr = JBG_BYTE_MARGIN_LEFT * 8;	/** 参照ラインＸポインタの初期化 */
	JBG_ReferenceLineY_Ptr = 2;		/** 参照ラインＹポインタの初期化 ２番目の配列を使用する */
	JBG_PreLineY_Ptr = 1;			/** 前参照ラインＹポインタの初期化 １番目の配列を使用する */
	JBG_PrePreLineY_Ptr = 0;		/** 前々参照ラインＹポインタの初期化 ０番目の配列を使用する */
	JBG_PrePreLineCx = 0;			/** 前々参照ラインコンテクストの初期化 */
	JBG_PreLineCx = 0;				/** 前参照ラインコンテクストの初期化 */
	JBG_LineCx = 0;					/** 参照ラインコンテクストの初期化 */
	JBG_PrePix = 0;					/** 前画素 */
	JBG_PrePrePix = 0;				/** 前々画素 */
	JBG_SlntpY = 0;					/** ＳＬＮＴＰ　ｙ */
	JBG_LntpY = 1;					/** ＬＮＴＰ　ｙ （画像最上のラインは１にセットする）*/
	JBG_LntpY_1 = 1;				/** ＬＮＴＰ　ｙ－１ （画像最上のラインは１にセットする）*/
	JBG_RequestATMOVE = 0;			/** ＡＴＭＯＶＥフローティングマーカーセグメントの作成要求 */
	JBG_RequestNEWLWN = 0;			/** ＮＥＷＬＥＮフローティングマーカーセグメントの作成要求 */
	JBG_RequestCOMMENT = 0;			/** ＣＯＭＭＥＮＴフローティングマーカーセグメントの作成要求 */
	JBG_RequestSDNORM = 0;			/** ＳＤＮＯＲＭの作成要求 */
	JBG_RequestSDRST = 0;			/** ＳＤＲＳＴの作成要求 */
	JBG_EncodeLineCount = 0;		/** 符号化しているライン */
	JBG_DecodeLineCount = 0;		/** 符号化しているライン */
	JBG_EncodeStripeCount = 0;		/** 符号化しているストライプ番号 */
	JBG_DecodeStripeCount = 0;		/** 復号化しているストライプ番号 */
	JBG_DecodeStripeLineCount = 0;	/** ストライプ中の復号化しているライン */
	JBG_IsDecodeSDE = 0;			/** ＳＤＥを復号化中 */
	JBG_DecodeEndStatus = 0;		/** デコード終了時の状態 */
	JBG_PixByteP = 0;				/** ワードのイメージデータ */
	JBG_PixByteBitP = 0;			/** ワードのイメージデータのビット位置 MSB Fast*/
	JBG_RlCounter = 0;				/** ＲＬカウンタの初期化 */
	JBG_RlPix = 1;					/** ＲＬの白黒論理を黒で初期化 */
	JBG_IsFirstScd = 1;				/** 最初のＳＣＤ（出力しないようにするため） */
	JGB_NullCount = 0;				/** ストライプ最後のＮＵＬＬの個数 */
	/** ＢＩＨの初期化 */
	JBG_BIH.DL = 0;			/** 送るべき最初のレイヤ	（Ｔ．８５では０固定） */
	JBG_BIH.D = 0;			/** 差分レイヤの数			（Ｔ．８５では０固定） */
	JBG_BIH.P = 0;			/** ビットプレーン数		（Ｔ．８５では１固定） */
	JBG_BIH.dummy = 0;		/** フィルバイト			（Ｔ．８２で０固定） */
	JBG_BIH.XD = 0;			/** 水平方向の画素数（Ｔ．８５ではＧ３はＴ．４、Ｇ４はＴ．５６３に準拠） */
	JBG_BIH.YD = 0;			/** 垂直方向の画素数（Ｔ．８２で１～４２９４９６７２９５） */
	JBG_BIH.L0 = 0;			/** 最低解像度のストライブのライン数（Ｔ．８５で１２８ライン固定、独自手順で変更可能） */
	JBG_BIH.MX = 0;			/** ＡＴ画素に許される最大水平オフセット（Ｔ．８５では０～１２７） */
	JBG_BIH.MY = 0;			/** ＡＴ画素に許される最大垂直オフセット（Ｔ．８５では０固定） */
	JBG_BIH.Order = 0;		/** ＳＣＤの順序（オーダービット定義参照） */
	JBG_BIH.Options = 0;	/** オプション（オプションビット定義参照） */
	/** ＡＴＭＯＶＥの初期化 */
	JBG_ATMOVE.Esc = 0;
	JBG_ATMOVE.Atmove = 0;
	JBG_ATMOVE.Yat = 0;
	JBG_ATMOVE.Tx = 0;
	JBG_ATMOVE.Ty = 0;
	/** ＮＥＷＬＥＮの初期化 */
	JBG_NEWLEN.Esc = 0;
	JBG_NEWLEN.Newlen = 0;
	JBG_NEWLEN.Yd = 0;
	/** ＣＯＭＭＥＮＴの初期化 */
	JBG_COMMENT.Esc = 0;
	JBG_COMMENT.Comment = 0;
	JBG_COMMENT.Lc = 0;
}


#if (0)
/*デバッグ用*/
UBYTE far JBG_ImageBuffer[0xffff] = {0};
UBYTE far JBG_CodeBuffer[0xffff] = {0};
extern const UBYTE BieTable[];
extern UWORD far RlTable[];
#endif
/*************************************************************************
	module		:[
		T.82(JBIG)ドライバーの入出力アドレスを初期化
	]
	function	:[
		1.ポインタ変数に入出力アドレス代入
	]
	return		:[なし]
	common		:[
	]
	condition	:[
		大域変数の初期化後にコールされる
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/24]
	author		:[小谷正樹]
*************************************************************************/
void JBG_SetEncodeIO_Address(void)
{
#if (0)
	JBG_ImagePtr = (UBYTE far *)&JBG_ImageBuffer[0];
	JBG_CodePtr = (UBYTE far *)&JBG_CodeBuffer[0];
	JBG_RlPtr = (UWORD far *)&RlTable[0];
	JBG_CodePtr = (UBYTE far *)&JBG_CodeBuffer[0];
#endif
}


/*************************************************************************
	module		:[
		T.82(JBIG)ドライバーの入出力アドレスを初期化
	]
	function	:[
		1.ポインタ変数に入出力アドレス代入
	]
	return		:[なし]
	common		:[
	]
	condition	:[
		大域変数の初期化後にコールされる
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/24]
	author		:[小谷正樹]
*************************************************************************/
void JBG_SetDecodeIO_Address(void)
{
#if (0)
	JBG_ImagePtr = (UBYTE far *)&JBG_ImageBuffer[0];
	JBG_CodePtr = (UBYTE far *)&JBG_CodeBuffer[0];
	JBG_ImagePtr = (UBYTE far *)&JBG_ImageBuffer[0];
	JBG_CodePtr = (UBYTE far *)&BieTable[0];
#endif
}


