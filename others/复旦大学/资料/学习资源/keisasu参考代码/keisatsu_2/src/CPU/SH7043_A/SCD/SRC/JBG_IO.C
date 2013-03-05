/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/01/27
*        FILE NAME:  jbg_io.c
*       Task ID No:
*      DESCRIPTION:  T.82(JBIG)による入出力を操作する為のファイル群
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
		T.82(JBIG)による符号化するためイメージを参照ラインに読み込む
	]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/27]
	author		:[小谷正樹]
*************************************************************************/
void JBG_ReadImageLine(void)
{
	UWORD loop;
	UWORD start_ptr;
	UWORD end_ptr;
	UWORD byte_ptr;
	UBYTE bit_ptr;

	for (loop = 0; loop < JBG_MAX_REFERENCE_X; loop++) {
		JBG_ReferenceLineBuffer[JBG_ReferenceLineY_Ptr][loop] = 0;	/** 参照ラインの初期化 */
	}
	start_ptr = (UWORD)(JBG_BYTE_MARGIN_LEFT * 8);	/** 復号化ラインのＸポインタの初期化 */
	end_ptr = (UWORD)(JBG_BIH.XD + (JBG_BYTE_MARGIN_LEFT * 8));	/*１ライン終了位置*/
	for (loop = start_ptr; loop < end_ptr; loop++) {	/** 参照ラインの代入 */
		byte_ptr = loop / 8;
		bit_ptr = (UBYTE)(7 - (loop % 8));
		JBG_ReferenceLineBuffer[JBG_ReferenceLineY_Ptr][byte_ptr] |= (JBG_ReadPix() << bit_ptr);	/*目的画素の論理*/
	}
}


/*************************************************************************
	module		:[
		T.82(JBIG)によるデコード時ＬＮＴＰが０の時は前ラインを出力する
	]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
	]
	condition	:[
		AAD_InitDec();がコールされていること
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/03]
	author		:[小谷正樹]
*************************************************************************/
void JBG_CopyReferenceLine(void)
{
	UWORD loop;

	for (loop = 0; loop < JBG_MAX_REFERENCE_X; loop++) {
		JBG_ReferenceLineBuffer[JBG_ReferenceLineY_Ptr][loop] = JBG_ReferenceLineBuffer[JBG_PreLineY_Ptr][loop];	/** 参照ラインの代入 */
	}
}


/*************************************************************************
	module		:[
		T.82(JBIG)による符号化時に獲得した符号ＳＣＤデータをメモリに出力する
	]
	function	:[
		1.ＳＣＤの最初のバイトを取り除く
		2.ＰＳＣＤを作成する
		3.ＰＳＣＤを出力する
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/15]
	author		:[小谷正樹]
*************************************************************************/
void JBG_WritePscd(UBYTE data)
{
	if (JBG_IsFirstScd) {
		JBG_IsFirstScd = 0;
	}
	else {
		if (data) {
			while (JGB_NullCount) {
				JBG_WriteBid(0x00);
				JGB_NullCount--;
			}
			JBG_WriteBid(data);
			if (data == JBG_SYMBOL_ESC) {	/** 0xFF */
				JBG_WriteBid(JBG_SYMBOL_STUFF);	/** スタッフを挿入する 0x00 */
			}
		}
		else {
			JGB_NullCount++;
		}
	}
}


/*************************************************************************
	module		:[
		T.82(JBIG)による符号化時に獲得した符号ＢＩＤデータをメモリに出力する
	]
	function	:[
		1.ＢＩＤを出力する
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/15]
	author		:[小谷正樹]
*************************************************************************/
void JBG_WriteBid(UBYTE data)
{
#if (JBG_DEBUG)
	WriteBID(data);
#endif
}


/*************************************************************************
	module		:[
		T.82(JBIG)によるイメージの参照ラインを次のラインに更新する
	]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/08]
	author		:[小谷正樹]
*************************************************************************/
void JBG_IncrementReferenceLineY(void)
{
	JBG_PrePreLineY_Ptr = JBG_PreLineY_Ptr;
	JBG_PreLineY_Ptr = JBG_ReferenceLineY_Ptr;
	JBG_ReferenceLineY_Ptr++;	/** 参照ラインポインタの更新 */
	if (JBG_ReferenceLineY_Ptr == JBG_MAX_REFERENCE_Y) {
		JBG_ReferenceLineY_Ptr = 0;
	}
}


/*************************************************************************
	module		:[
		T.85(JBIG)による復号化するための画データを取り出す
	]
	function	:[
	]
	return		:[
		１バイトのＰＩＸ
	]
	common		:[]
	condition	:[
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/14]
	author		:[小谷正樹]
*************************************************************************/
UBYTE JBG_ReadPix(void)
{
	if (!JBG_RlCounter) {
		do {
			if (JBG_RlPix) {
				JBG_RlPix = 0;
			}
			else {
				JBG_RlPix = 1;
			}
			JBG_RlCounter = *JBG_RlPtr;	/** ＲＬバッファから２バイト読みとる */
			JBG_RlPtr++;		/** ＲＬバッファポインタをインクリメントする */
		} while (!JBG_RlCounter);
	}
	JBG_RlCounter--;
#if (JBG_DEBUG)
	TestData++;
	if (TestData == (UDWORD)((UDWORD)1728 * (UDWORD)1152 + 1)) {
		check4();
	}
#endif
	return (JBG_RlPix);
}


/*************************************************************************
	module		:[
		T.85(JBIG)によるＢＩＤから１バイト読み出す
	]
	function	:[
		1.ＢＩＤから１バイト読みとる
		2.コードポインタをインクリメントする
	]
	return		:[
		１バイトのＢＩＤ
	]
	common		:[]
	condition	:[
		JBG_CodePtrがセットされていること
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/28]
	author		:[小谷正樹]
*************************************************************************/
UBYTE JBG_ReadBID(void)
{
	UBYTE bid;

	bid = *JBG_CodePtr;	/** ＳＣＤから１バイト読みとる */
	JBG_CodePtr++;		/** コードポインタをインクリメントする */
#if (JBG_DEBUG)
	if (TestData == (679 * 16 + 8)) {
		check4();
	}
	TestData++;
#endif
	return (bid);
}


/*************************************************************************
	module		:[
		T.85(JBIG)によるＢＩＤ(bi-level image data)を復号化するため解析処理する
	]
	function	:[
		1.ＢＩＤから１バイト読み出す
		2.
	]
	return		:[
		１バイトのＳＣＤ
	]
	common		:[]
	condition	:[
		JBG_CodePtrがセットされていること
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/28]
	author		:[小谷正樹]
*************************************************************************/
UBYTE JBG_ReadSCD(void)
{
	UBYTE bid;
	UBYTE esc;

	while (1) {	/** ｃｏｎｔｉｎｕｅ以外ループしない */
		bid = JBG_ReadBID();	/** ＢＩＤから１バイト読みとる */
		if (bid == JBG_SYMBOL_ESC) {	/** ＢＩＤがＥＳＣの時のみ例外処理を行う */
			esc = JBG_ReadBID();	/** ＥＳＣの内容を解析するため、さらにＢＩＤから１バイト読みとる */
			switch (esc) {
			case JBG_SYMBOL_STUFF:		/** 0x00 スタッフ */
				break;
			case JBG_SYMBOL_SDNORM:	/** 0x02 ストライプデータ終了 */
			case JBG_SYMBOL_SDRST:		/** 0x03 ストライプデータ終了時のリセット */
			case JBG_SYMBOL_ABORT:		/** 0x04 アボート */
				JBG_DecodeEndStatus |= esc;	/** ストライプ終了。そのときのステータスをセット */
				bid = 0;	/** ＢＩＤを０にする */
				break;	/** ＳＤＥ処理終了 */
			case JBG_SYMBOL_ATMOVE:	/** 0x06 ＡＴ移動 */
			case JBG_SYMBOL_COMMENT:	/** 0x07 プライベートコメント */
			case JBG_SYMBOL_NEWLEN:	/** 0x05 新しい長さ */
				if (!JBG_IsDecodeSDE) {
					switch (esc) {
					case JBG_SYMBOL_ATMOVE:	/** 0x06 ＡＴ移動 */
						JBG_ResetATMOVE();	/** ＡＴＭＯＶＥ再セット */
						continue;
					case JBG_SYMBOL_COMMENT:	/** 0x07 プライベートコメント */
						JBG_ResetCOMMENT();	/** ＣＯＭＭＥＮＴ再セット */
						continue;
					case JBG_SYMBOL_NEWLEN:	/** 0x05 新しい長さ */
						JBG_ResetNEWLEN();	/** ＮＥＷＬＥＮ再セット */
						continue;
					default:
						break;
					}
				}
				/** ＳＤＥデコード中の時はＢＲＥＡＫはしません！エラーとする */
			case JBG_SYMBOL_ESC:		/** 0xff エスケープ */
			case JBG_SYMBOL_RESERVE:	/** 0x01 リザーブ */
			default:
				JBG_DecodeEndStatus |= JBG_BIT_ERROR;	/** デコードエラー発生 */
				break;
			}
		}
		break;
	}
	if (JBG_DecodeEndStatus) {
		JBG_IsDecodeSDE = 0;		/** ＳＤＥを復号化中をクリア */
	}
	else {
		JBG_IsDecodeSDE = 1;		/** ＳＤＥを復号化中をセット */
	}
	return (bid);
}


