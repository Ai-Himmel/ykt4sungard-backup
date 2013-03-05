/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/01/23
*        FILE NAME:  jbg_bih.c
*       Task ID No:
*      DESCRIPTION:  ＢＩＨ(bi-level image header)
*                    T.82(JBIG)によるＢＩＨを操作する為のファイル群
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
		T.85(JBIG)によるＢＩＨ作成
	]
	function	:[
		1.ＢＩＨのデフォルト値をセットする
		2.ＸＤをセットする
		3.ＸＹをセットする
		4.できあがったＢＩＨを出力する
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/24]
	author		:[小谷正樹]
*************************************************************************/
void JBG_MakeBIH(void)
{
	JBG_ResetBIH();				/** ＢＩＨのデフォルト値をセットする */
	JBG_BIH.XD = 1728;			/** ＸＤをセットする */
	JBG_BIH.YD = 0xffffffff;	/** ＹＤをセットする */
	JBG_BIH.L0 = 128;			/** Ｌ０をセットする */
	JBG_BIH.MX = 0;				/** ＡＴ画素に許される最大水平オフセットをセットする */
	JBG_SetBIH_LRLTWO(0);		/** ＬＲＬＴＷＯを設定する */
	JBG_SetBIH_VLENGTH(1);		/** ＶＬＥＮＧＴＨを設定する */
	JBG_SetBIH_TPBON(0);		/** ＴＰＢＯＮを設定する */
	JBG_EncodeBIH();			/** できあがったＢＩＨを出力する */
}


/*************************************************************************
	module		:[
		T.85(JBIG)によるＢＩＨ初期化処理
	]
	function	:[
		1.ＢＩＨのデフォルト値をセットする
	]
	return		:[なし]
	common		:[
		BIH
	]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/24]
	author		:[小谷正樹]
*************************************************************************/
void JBG_ResetBIH(void)
{
	JBG_BIH.DL		= (UBYTE)0;				/** 送るべき最初のレイヤ	（Ｔ．８５では０固定） */
	JBG_BIH.D		= (UBYTE)0;				/** 差分レイヤの数			（Ｔ．８５では０固定） */
	JBG_BIH.P		= (UBYTE)1;				/** ビットプレーン数		（Ｔ．８５では１固定） */
	JBG_BIH.dummy	= (UBYTE)0;				/** フィルバイト			（Ｔ．８２で０固定） */
	JBG_BIH.XD		= (UDWORD)1;				/** 水平方向の画素数（Ｔ．８５ではＧ３はＴ．４、Ｇ４はＴ．５６３に準拠） */
	JBG_BIH.YD		= (UDWORD)0xffffffff;	/** 垂直方向の画素数（Ｔ．８２で１～４２９４９６７２９５） */
	JBG_BIH.L0		= (UDWORD)128;			/** 最低解像度のストライブのライン数（Ｔ．８５で１２８ライン固定、独自手順で変更可能） */
	JBG_BIH.MX		= (UBYTE)127;			/** ＡＴ画素に許される最大水平オフセット（Ｔ．８５では０～１２７） */
	JBG_BIH.MY		= (UBYTE)0;				/** ＡＴ画素に許される最大垂直オフセット（Ｔ．８５では０固定） */
	JBG_BIH.Order	= (UBYTE)0x00;			/** ＳＣＤの順序（オーダービット定義参照） */
	JBG_BIH.Options	= (UBYTE)0x00;			/** オプション（オプションビット定義参照） */
}


/*************************************************************************
	module		:[
		T.85(JBIG)によるＬＲＬＴＷＯのビットセット処理
	]
	function	:[
		1.ＬＲＬＴＷＯを設定する
	]
	return		:[なし]
	common		:[
		BIH
	]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/14]
	author		:[小谷正樹]
*************************************************************************/
void JBG_SetBIH_LRLTWO(UBYTE lrltwo)
{
	if (lrltwo) {
		JBG_BIH.Options |= JBG_BIT_LRLTWO;
	}
	else {
		JBG_BIH.Options &= ~JBG_BIT_LRLTWO;
	}
}


/*************************************************************************
	module		:[
		T.85(JBIG)によるＶＬＥＮＧＴＨのビットセット処理
	]
	function	:[
		1.ＶＬＥＮＧＴＨを設定する
	]
	return		:[なし]
	common		:[
		BIH
	]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/14]
	author		:[小谷正樹]
*************************************************************************/
void JBG_SetBIH_VLENGTH(UBYTE vlength)
{
	if (vlength) {
		JBG_BIH.Options |= JBG_BIT_VLENGTH;
	}
	else {
		JBG_BIH.Options &= ~JBG_BIT_VLENGTH;
	}
}


/*************************************************************************
	module		:[
		T.85(JBIG)によるＴＰＢＯＮのビットセット処理
	]
	function	:[
		1.ＴＰＢＯＮを設定する
	]
	return		:[なし]
	common		:[
		BIH
	]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/24]
	author		:[小谷正樹]
*************************************************************************/
void JBG_SetBIH_TPBON(UBYTE tpbon)
{
	if (tpbon) {
		JBG_BIH.Options |= JBG_BIT_TPBON;
	}
	else {
		JBG_BIH.Options &= ~JBG_BIT_TPBON;
	}
}


/*************************************************************************
	module		:[
		T.85(JBIG)によるＢＩＨを出力する
	]
	function	:[
		1.できあがったＢＩＨを出力する
	]
	return		:[なし]
	common		:[
		BIH
	]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/24]
	author		:[小谷正樹]
*************************************************************************/
void JBG_EncodeBIH(void)
{
	UBYTE loop;
	UBYTE *src;

#if (JBG_DEBUG)
	JBG_BIH.XD =
	((UDWORD)*((UBYTE *)&JBG_BIH.XD + 0)) * 256 * 256 * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.XD + 1)) * 256 * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.XD + 2)) * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.XD + 3));
	JBG_BIH.YD =
	((UDWORD)*((UBYTE *)&JBG_BIH.YD + 0)) * 256 * 256 * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.YD + 1)) * 256 * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.YD + 2)) * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.YD + 3));
	JBG_BIH.L0 =
	((UDWORD)*((UBYTE *)&JBG_BIH.L0 + 0)) * 256 * 256 * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.L0 + 1)) * 256 * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.L0 + 2)) * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.L0 + 3));
#endif
	src = (UBYTE *)&JBG_BIH;
	for (loop = 0; loop < 20; loop++) {
#if (JBG_DEBUG)
		DumpByte(src);
#endif
		*JBG_CodePtr = *src;
		JBG_CodePtr++;
		src++;
	}
#if (JBG_DEBUG)
	JBG_BIH.XD =
	((UDWORD)*((UBYTE *)&JBG_BIH.XD + 0)) * 256 * 256 * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.XD + 1)) * 256 * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.XD + 2)) * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.XD + 3));
	JBG_BIH.YD =
	((UDWORD)*((UBYTE *)&JBG_BIH.YD + 0)) * 256 * 256 * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.YD + 1)) * 256 * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.YD + 2)) * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.YD + 3));
	JBG_BIH.L0 =
	((UDWORD)*((UBYTE *)&JBG_BIH.L0 + 0)) * 256 * 256 * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.L0 + 1)) * 256 * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.L0 + 2)) * 256 +
	((UDWORD)*((UBYTE *)&JBG_BIH.L0 + 3));
#endif
}


/*************************************************************************
	module		:[
		T.85(JBIG)によるＢＩＨを読み込み
	]
	function	:[
		1.受信したＢＩＨを大域変数にセットする
	]
	return		:[なし]
	common		:[
		BIH
	]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/28]
	author		:[小谷正樹]
*************************************************************************/
void JBG_DecodeBIH(void)
{
	UBYTE loop;
	UBYTE *dst;

	dst = (UBYTE *)&JBG_BIH;
	for (loop = 0; loop < 20; loop++) {
		*dst = *JBG_CodePtr;
		JBG_CodePtr++;
		dst++;
	}
}

