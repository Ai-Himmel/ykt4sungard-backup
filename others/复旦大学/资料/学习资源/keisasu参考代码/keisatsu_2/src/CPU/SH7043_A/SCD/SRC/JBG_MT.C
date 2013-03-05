/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/01/27
*        FILE NAME:  jbg_mt.c
*       Task ID No:
*      DESCRIPTION:  ＭＴ(Model templates)
*                    T.82(JBIG)によるモデルテンプレートモジュールのファイル群
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
		T.82(JBIG)による復号化ＭＴ(Model templates)処理
	]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		ＣＸを獲得する
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/27]
	author		:[小谷正樹]
*************************************************************************/
void JBG_MT(void)
{
	if (JBG_BIH.Options & JBG_BIT_LRLTWO) {	/** ＬＲＬＴＷＯが１の場合は２ラインテンプレートを使用する */
		JBG_Get2LinesCx();
	}
	else {
		JBG_Get3LinesCx();
	}
}


/*************************************************************************
	module		:[
		T.85(JBIG)によるＣＸ(コンテクスト)作成
	]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		JBG_Cx, JBG_Pix, TpValue, DpValue
	]
	condition	:[
		JBG_ReferenceLineX_Ptrがセットされていること
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/27]
	author		:[小谷正樹]
*************************************************************************/
void JBG_MakePixCxTpValueDpValue(void)
{
	JBG_DpValue = 2;	/** Ｔ．８５では２固定 */
	if (JBG_BIH.Options & JBG_BIT_LRLTWO) {	/** ＬＲＬＴＷＯが１の場合は２ラインテンプレートを使用する */
		/*  XXXXXA */
		/* XXXX? */
		if (!JBG_ReferenceLineX_Ptr) {	/** ＳＬＮＴＰの場合 */
			JBG_Cx = 0x195;	/* 01 1001 0101 */
			JBG_Pix = JBG_SlntpY;	/** 算術符号器用の画素をセット */
			JBG_TpValue = 2;
		}
		else {	/** 通常画素の場合 */
			if (JBG_LntpY) {	/** 予測不能のため算術符号器を使用する */
				JBG_Get2LinesCx();
				JBG_TpValue = 2;
			}
			else {	/** 典型的予測的中 */
				JBG_TpValue = 0;
			}
		}
	}
	else {	/** ３ラインテンプレート */
		/*  XXX */
		/* XXXXA */
		/* XX? */
		if (!JBG_ReferenceLineX_Ptr) {	/** ＳＬＮＴＰの場合 */
			JBG_Cx = 0xe5;	/* 00 1110 0101 */
			JBG_Pix = JBG_SlntpY;	/** 算術符号器用の画素をセット */
			JBG_TpValue = 2;
		}
		else {	/** 通常画素の場合 */
			if (JBG_LntpY) {	/** 予測不能のため算術符号器を使用する */
				JBG_Get3LinesCx();
				JBG_TpValue = 2;
			}
			else {	/** 典型的予測的中 */
				JBG_TpValue = 0;
			}
		}
	}
}


/*************************************************************************
	module		:[
		T.85(JBIG)による２ラインテンプレート時のＣＸ(コンテクスト)作成
	]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		JBG_Cx, JBG_Pix
	]
	condition	:[
		JBG_ReferenceLineX_Ptrがセットされていること
	]
	comment		:[
		void JBG_AAD(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/27]
	author		:[小谷正樹]
*************************************************************************/
void JBG_Get2LinesCx(void)
{
	UWORD target;
	UWORD byte_ptr;
	UBYTE bit_ptr;
	UWORD target_ptr;

	JBG_Cx = 0;	/* 初期化する */
	/** 前ラインのコンテクストを獲得する */
	if (JBG_BIH.MX) {	/** ＡＴＭＯＶＥするとき */
		if ((JBG_ATMOVE.Tx) && (JBG_DecodeStripeLineCount >= JBG_ATMOVE.Yat)) {	/** ＡＴＭＯＶＥするとき */
			byte_ptr = (JBG_ReferenceLineX_Ptr + 1) / 8;
			bit_ptr = (UBYTE)(7 - ((JBG_ReferenceLineX_Ptr + 1) % 8));
			target = JBG_ReferenceLineBuffer[JBG_PreLineY_Ptr][byte_ptr] & (1 << bit_ptr);	/*目的画素の論理*/
			JBG_PreLineCx <<= 1;		/** 前参照ラインコンテクストを１ビットシフトする */
			JBG_PreLineCx &= 0x1c;		/** 下位５ビットのみ有効 */
			if (target) {
				JBG_PreLineCx |= 2;
			}
			if (JBG_ReferenceLineX_Ptr < JBG_ATMOVE.Tx) {
				target_ptr = 0;
			}
			else {
				target_ptr = JBG_ReferenceLineX_Ptr - JBG_ATMOVE.Tx;
			}
			byte_ptr = target_ptr / 8;
			bit_ptr = (UBYTE)(7 - (target_ptr % 8));
			target = JBG_ReferenceLineBuffer[JBG_ReferenceLineY_Ptr][byte_ptr] & (1 << bit_ptr);	/*目的画素の論理*/
			if (target) {
				JBG_PreLineCx |= 1;
			}
		}
	}
	else {
		byte_ptr = (JBG_ReferenceLineX_Ptr + 2) / 8;
		bit_ptr = (UBYTE)(7 - ((JBG_ReferenceLineX_Ptr + 2) % 8));
		target = JBG_ReferenceLineBuffer[JBG_PreLineY_Ptr][byte_ptr] & (1 << bit_ptr);	/*目的画素の論理*/
		JBG_PreLineCx <<= 1;		/** 前参照ラインコンテクストを１ビットシフトする */
		JBG_PreLineCx &= 0x3e;		/** 下位６ビットのみ有効 */
		if (target) {
			JBG_PreLineCx |= 1;
		}
	}
	/** 現ラインのコンテクストを獲得する */
	byte_ptr = (JBG_ReferenceLineX_Ptr - 1) / 8;
	bit_ptr = (UBYTE)(7 - ((JBG_ReferenceLineX_Ptr - 1) % 8));
	target = JBG_ReferenceLineBuffer[JBG_ReferenceLineY_Ptr][byte_ptr] & (1 << bit_ptr);	/*目的画素の論理*/
	JBG_LineCx <<= 1;		/** 参照ラインコンテクストを１ビットシフトする */
	JBG_LineCx &= 0x1e;		/** 下位５ビットのみ有効 */
	if (target) {
		JBG_LineCx |= 1;
	}
	/** ２ラインテンプレート時のコンテクストを獲得する */
	JBG_Cx += JBG_PreLineCx << 5;
	JBG_Cx += JBG_LineCx;
}


/*************************************************************************
	module		:[
		T.85(JBIG)による３ラインテンプレート時のＣＸ(コンテクスト)作成
	]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		JBG_Cx, JBG_Pix
	]
	condition	:[
		JBG_ReferenceLineX_Ptrがセットされていること
	]
	comment		:[
		void JBG_AAD(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/27]
	author		:[小谷正樹]
*************************************************************************/
void JBG_Get3LinesCx(void)
{
	UWORD target;
	UWORD target_ptr;
	UWORD byte_ptr;
	UBYTE bit_ptr;

	/** 前々ラインのコンテクストを獲得する */
	byte_ptr = (JBG_ReferenceLineX_Ptr + 1) / 8;
	bit_ptr = (UBYTE)((JBG_ReferenceLineX_Ptr + 1) % 8);
	JBG_PrePreLineCx &= 0x03;	/** 下位２ビットのみ有効 */
	JBG_PrePreLineCx <<= 1;		/** 前々参照ラインコンテクストを１ビットシフトする */
	if (JBG_ReferenceLineBuffer[JBG_PrePreLineY_Ptr][byte_ptr] & (0x80 >> bit_ptr)) {	/*目的画素の論理*/
		JBG_PrePreLineCx++;
	}
	/** 前ラインのコンテクストを獲得する */
	if (JBG_BIH.MX) {	/** ＡＴＭＯＶＥするとき */
		if ((JBG_ATMOVE.Tx) && (JBG_DecodeStripeLineCount >= JBG_ATMOVE.Yat)) {	/** ＡＴＭＯＶＥするとき */
			byte_ptr = (JBG_ReferenceLineX_Ptr + 1) / 8;
			bit_ptr = (UBYTE)(7 - ((JBG_ReferenceLineX_Ptr + 1) % 8));
			target = JBG_ReferenceLineBuffer[JBG_PreLineY_Ptr][byte_ptr] & (1 << bit_ptr);	/*目的画素の論理*/
			JBG_PreLineCx <<= 1;		/** 前参照ラインコンテクストを１ビットシフトする */
			JBG_PreLineCx &= 0x1c;		/** 下位５ビットのみ有効 */
			if (target) {
				JBG_PreLineCx |= 2;
			}
			if (JBG_ReferenceLineX_Ptr < JBG_ATMOVE.Tx) {
				target_ptr = 0;
			}
			else {
				target_ptr = JBG_ReferenceLineX_Ptr - JBG_ATMOVE.Tx;
			}
			byte_ptr = target_ptr / 8;
			bit_ptr = (UBYTE)(7 - (target_ptr % 8));
			target = JBG_ReferenceLineBuffer[JBG_ReferenceLineY_Ptr][byte_ptr] & (1 << bit_ptr);	/*目的画素の論理*/
			if (target) {
				JBG_PreLineCx |= 1;
			}
		}
	}
	else {
		if (bit_ptr < 7) {	/** １画素進める */
			bit_ptr++;
		}
		else {
			byte_ptr++;
			bit_ptr = 0;
		}
		JBG_PreLineCx &= 0x0f;		/** 下位４ビットのみ有効 */
		JBG_PreLineCx <<= 1;		/** 前参照ラインコンテクストを１ビットシフトする */
		if (JBG_ReferenceLineBuffer[JBG_PreLineY_Ptr][byte_ptr] & (0x80 >> bit_ptr)) {	/*目的画素の論理*/
			JBG_PreLineCx++;
		}
	}
	/** 現ラインのコンテクストを獲得する */
	JBG_LineCx = (UBYTE)(JBG_PrePrePix << 1) | JBG_PrePix;	/** 現ラインのコンテクスト作成のため */
#if (0)
;;	JBG_LineCx <<= 1;		/** 参照ラインコンテクストを１ビットシフトする */
;;	JBG_LineCx &= 0x02;		/** 下位２ビットのみ有効 */
;;	JBG_LineCx += JBG_PrePix;
#endif
	/** ３ラインテンプレート時のコンテクストを獲得する */
	JBG_Cx = JBG_PrePreLineCx << 7;	/* 初期化する */
	JBG_Cx += JBG_PreLineCx << 2;
	JBG_Cx += JBG_LineCx;
}


/*************************************************************************
	module		:[
		T.85(JBIG)によるＳＬＮＴＰ時のＣＸ(コンテクスト)作成
	]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		JBG_Cx
	]
	condition	:[]
	comment		:[
		void JBG_DecodeTPB(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/12]
	author		:[小谷正樹]
*************************************************************************/
void JBG_GetSlntpCx(void)
{
	if (JBG_BIH.Options & JBG_BIT_LRLTWO) {	/** ＬＲＬＴＷＯが１の場合は２ラインテンプレートを使用する */
		/*  XXXXXA */
		/* XXXX? */
		JBG_Cx = 0x195;	/* 01 1001 0101 */
	}
	else {	/** ３ラインテンプレート */
		/*  XXX */
		/* XXXXA */
		/* XX? */
		JBG_Cx = 0xe5;	/* 00 1110 0101 */
	}
}


/*************************************************************************
	module		:[
		T.85(JBIG)によるライン先頭時のＣＸ(コンテクスト)の初期化
	]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		JBG_PrePreLineCx
		JBG_PreLineCx
		JBG_LineCx
	]
	condition	:[]
	comment		:[
		void JBG_AAD(void)
		よりコールされる
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/12]
	author		:[小谷正樹]
*************************************************************************/
void JBG_ResetCx(void)
{
	JBG_PrePreLineCx = 0;	/** 参照コンテクストの初期化 */
	JBG_PreLineCx = 0;		/** 参照コンテクストの初期化 */
	JBG_LineCx = 0;			/** 参照コンテクストの初期化 */
}
