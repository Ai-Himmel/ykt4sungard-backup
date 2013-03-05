/************************************************************************
*	System		: POPLAR/ANZU-L
*	File Name	: CMN_STR.C
*	Author		: 橘正樹
*	Date		: 1996/11/02
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニタ
*	Description	:
*	Maintenance	:
*				: Original:\src\kobe\anzu\src\cmn_str.c
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\font_def.h" /* Added by SMuratec L.Z.W 2003/08/13 */
#include "\src\atlanta\ext_v\font_tbl.h" /* Added by SMuratec L.Z.W 2003/08/13 */
#include "\src\atlanta\opr\ank\define\opr_def.h" /* Added by SMuratec L.Z.W 2003/08/13 */
#include "\src\atlanta\ext_v\bkupram.h"

#if (PRO_PANEL == ANK)
#include "\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#endif
#if (PRO_PANEL == KANJI)	/* 追加 By O.Kimoto 1997/06/25 */
#include "\src\atlanta\opr\kanji\ext_v\wording.h"
#endif
#include "\src\atlanta\ext_v\lst_wrd.h"
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && (PRO_OKI == ENABLE)	/* by K.Watanabe 1998/10/02 */
#include "\src\atlanta\define\mntsw_a.h"
#include "\src\atlanta\define\param.h"		/* by K.Watanabe 1998/10/22 */
#endif
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)  *//* SANYO仕様の追加 2000/02/25 N.Kondo */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SANYO仕様の追加 2000/02/25 N.Kondo */
#include "\src\atlanta\ext_v\rom_tbl.h"
extern CONST UBYTE	D2W_SF_Receive[];
extern CONST UBYTE	D2W_SF_Hook[];
extern CONST UBYTE	D2W_SF_Contrast[];
extern CONST UBYTE	D2W_SF_Receive_S[];
extern CONST UBYTE	D2W_SF_Hook_S[];
extern CONST UBYTE	D2W_SF_Contrast_S[];
#endif

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
#include	"\src\atlanta\define\status.h"
#endif

/*************************************************************************
	module		:[文字列のNULLまでｺﾋﾟｰ]
	function	:[
		1.
	]
	return		:[コピー後のコピー先アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/08]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	*CMN_StringCopyNULL(
UBYTE		*dst_ptr,		/* コピー先アドレス */
CONST UBYTE	*src_ptr)		/* コピー元アドレス */
{
	/*------------------------------*/
	/** コピー元文字列のアドレス変換*/
	/*------------------------------*/
	src_ptr = CalculateStringAddress((UBYTE *)src_ptr); /* 1996/03/12 Eguchi */
	while (*dst_ptr++ = *src_ptr++);
	return(dst_ptr);
}

/*************************************************************************
	module		:[文字列の指定文字数又NULLまでコピー]
	function	:[
		1.指定文字数内にNULLがある場合は、NULLを含んでコピーする
		1.指定文字数内にNULLがない場合は、指定文字+NULLをコピーする
	]
	return		:[コピー後のコピー先アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/08]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	*CMN_StringCopyNumOrNULL(
UBYTE			*dst_ptr,		/* コピー先アドレス */
CONST UBYTE		*src_ptr,		/* コピー元アドレス */
register WORD	str_cnt)		/* コピー文字数 */
{
	/*------------------------------*/
	/** コピー元文字列のアドレス変換*/
	/*------------------------------*/
	src_ptr = CalculateStringAddress((UBYTE *)src_ptr); /* 1996/03/12 Eguchi */
	for (; str_cnt > 0; str_cnt--) {
		if (!(*dst_ptr++ = *src_ptr++)) {
			break;
		}
	}
	*dst_ptr++ = NULL;
	return (dst_ptr);
}

/*************************************************************************
	module		:[文字列のコピー]
	function	:[
		1.NULLを含まずにコピーする
	]
	return		:[コピー後のコピー先アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/09]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	*CMN_StringCopy(
UBYTE		*dst_ptr,		/* コピー先アドレス */
CONST UBYTE	*src_ptr)		/* コピー元アドレス */
{
	/*------------------------------*/
	/** コピー元文字列のアドレス変換*/
	/*------------------------------*/
	src_ptr = CalculateStringAddress((UBYTE *)src_ptr); /* 1996/03/12 Eguchi */
	while (*src_ptr != NULL) {
		*dst_ptr++ = *src_ptr++;
	}
	return(dst_ptr);
}


/*************************************************************************
	module		:[文字列の指定文字数コピー]
	function	:[
		1.
	]
	return		:[コピー後のコピー先アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/09]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	*CMN_StringCopyNum(
UBYTE			*dst_ptr,		/* コピー先アドレス */
CONST UBYTE		*src_ptr,		/* コピー元アドレス */
register WORD	str_cnt)		/* コピー文字数 */
{
	/*------------------------------*/
	/** コピー元文字列のアドレス変換*/
	/*------------------------------*/
	src_ptr = CalculateStringAddress((UBYTE *)src_ptr); /* 1996/03/12 Eguchi */
	for (; str_cnt > 0; str_cnt--) {
		*dst_ptr++ = *src_ptr++;
	}
	return(dst_ptr);
}

/*************************************************************************
	module		:[文字列の指定文字数コピー]
	function	:[
		1.指定文字数ないにnullを検出したらコピーをやめる。
			nullは、コピーしない。
	]
	return		:[コピー後のコピー先アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/5/19]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE	*CMN_StringCopyNumUntilNull(
UBYTE			*dst_ptr,		/* コピー先アドレス */
CONST UBYTE		*src_ptr,		/* コピー元アドレス */
register WORD	str_cnt)		/* コピー文字数 */
{
	/*------------------------------*/
	/** コピー元文字列のアドレス変換*/
	/*------------------------------*/
	src_ptr = CalculateStringAddress((UBYTE *)src_ptr); /* 1996/03/12 Eguchi */
	for (; (str_cnt > 0)&&(*src_ptr != NULL); str_cnt--) {
	/* 指定文字数内にNULLがあればコピーをやめる By Y.Suzuki 1998/05/19 */
		*dst_ptr++ = *src_ptr++;
	}
	return(dst_ptr);
}

/*************************************************************************
	module		:[int型データの指定データ数コピー]
	function	:[
		1.
	]
	return		:[コピー後のコピー先アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/02/05]
	author		:[吉川弘康]
*************************************************************************/
UWORD	*CMN_IntDataCopyNum(
UWORD			*dst_ptr,		/* コピー先アドレス */
UWORD			*src_ptr,		/* コピー元アドレス */
register WORD	str_cnt)		/* コピー文字数 */
{
	for (; str_cnt > 0; str_cnt--) {
		*dst_ptr++ = *src_ptr++;
	}
	return(dst_ptr);
}

/*************************************************************************
	module		:[メモリセット+NULL]
	function	:[
		1.最終桁にNULLをセットする
	]
	return		:[メモリセット後のセット先アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/09]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	*CMN_MemorySetNULL(
UBYTE	*dst_ptr,		/* セット先アドレス */
UWORD	size,			/* セット文字数 */
UBYTE	data)			/* セット文字 */
{
	while (size--) {
		*dst_ptr++ = data;
	}
	*dst_ptr++ = NULL;
	return(dst_ptr);
}

/*************************************************************************
	module		:[メモリセット]
	function	:[
		1.
	]
	return		:[メモリセット後のセット先アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/09]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	*CMN_MemorySet(
UBYTE	*dst_ptr,		/* セット先アドレス */
UWORD	size,			/* セット文字数 */
UBYTE	data)			/* セット文字 */
{
	while (size--) {
		*dst_ptr++ = data;
	}
	return(dst_ptr);
}

/*************************************************************************
	module		:[メモリセット(ワード単位)]
	function	:[
		1.
	]
	return		:[メモリセット後のセット先アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/07/20]
	author		:[石橋正和]
*************************************************************************/
UWORD	*CMN_WordMemorySet(
UWORD	*dst_ptr,		/* セット先アドレス */
UWORD	size,			/* セットワード数 */
UWORD	data)			/* セットデータ */
{
	while (size--) {
		*dst_ptr++ = data;
	}
	return(dst_ptr);
}

/*************************************************************************
	module		:[ビット反転]
	function	:[
		1.
	]
	return		:[ビット反転結果]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/09]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_MSB_LSB_Invert(UBYTE data)	/* 1バイト */
{
	UBYTE	ret;

	ret = 0;
	if (data & 0x01) {
		ret |= 0x80;
	}
	if (data & 0x02) {
		ret |= 0x40;
	}
	if (data & 0x04) {
		ret |= 0x20;
	}
	if (data & 0x08) {
		ret |= 0x10;
	}
	if (data & 0x10) {
		ret |= 0x08;
	}
	if (data & 0x20) {
		ret |= 0x04;
	}
	if (data & 0x40) {
		ret |= 0x02;
	}
	if (data & 0x80) {
		ret |= 0x01;
	}
	return (ret);
}

/*************************************************************************
	module		:[文字列長の獲得]
	function	:[
		1.終了コードをNULLとし、NULLをふくまない長さ
	]
	return		:[文字列長]
	common		:[]
	condition	:[最終桁+1にはNULLをセットしておくこと]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/09]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_StringLength(CONST UBYTE *string)
{
	UBYTE i;

	/*------------------------------*/
	/** 文字列のアドレス変換		*/
	/*------------------------------*/
	string = CalculateStringAddress((UBYTE *)string); /* 1996/03/12 Eguchi */
	for (i = 0; *string++ != NULL; i++);
	return (i);
}

/*************************************************************************
	module		:[CRまでの文字列長の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/09]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_StringLengthCR(CONST UBYTE *string)
{

	UBYTE i;

	/*------------------------------*/
	/** 文字列のアドレス変換		*/
	/*------------------------------*/
	string = CalculateStringAddress((UBYTE *)string); /* 1996/03/12 Eguchi */
	for (i = 0; *string != NULL && *string != CR; i++ ) {
		string++;
	}
	return (i);
}

/*************************************************************************
	module		:[空白(0x20)までの文字列長の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/08/21]
	author		:[石橋正和]
*************************************************************************/
UBYTE	CMN_StringLengthSP(UBYTE *string)
{

	UBYTE i;

	/*------------------------------*/
	/** 文字列のアドレス変換		*/
	/*------------------------------*/
	string = CalculateStringAddress(string); /* 1996/03/12 Eguchi */
	for (i = 0; *string != NULL && *string != ' '; i++ ) {
		string++;
	}
	return (i);
}

/*************************************************************************
	module		:[文字列比較]
	function	:[
		1.2つの文字列を辞書式の順序で比較する
	]
	return		:[
		1.STRCMP_LOWER(-1):string1がstring2より小さい
		2.STRCMP_EQUAL( 0):string1とstring2は等しい
		3.STRCMP_UPPER( 1):string1がstring2より大きい
	]
	common		:[
		1."12"と"123"では"12"の方が小さい
		2.""と"1"では"1"の方が小さい
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/09]
	author		:[吉川弘康]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UBYTE	CMN_StringCompareFlsRom(
UBYTE	*string1,		/* 比較する文字列 */
UBYTE	*string2,		/* 比較する文字列 */
UBYTE	size)			/* 比較する文字列長 */
#else
UBYTE	CMN_StringCompare(
UBYTE	*string1,		/* 比較する文字列 */
UBYTE	*string2,		/* 比較する文字列 */
UBYTE	size)			/* 比較する文字列長 */
#endif
{
	UBYTE	ret;				/* 比較結果 */
	UBYTE	i;					/* loop */
	register UWORD	char1;				/* String1の１ﾊﾞｲﾄ */
	register UWORD	char2;				/* String2の１ﾊﾞｲﾄ */

	/*------------------------------*/
	/**	文字列のアドレス変換		*/
	/*------------------------------*/
	string1 = CalculateStringAddress(string1); /* 1996/03/12 Eguchi */
	string2 = CalculateStringAddress(string2); /* 1996/03/12 Eguchi */

	ret = STRCMP_EQUAL;
	for (i = 0; i < size; i++) {
		if (*string1 != *string2) {
			char1 = *string1;
			if (char1 == 0 && i == 0) {
				char1 = 0x100;
			}
			char2 = *string2;
			if (char2 == 0 && i == 0) {
				char2 = 0x100;
			}
			if (char1 < char2) {
				ret = STRCMP_LOWER;
			}
			else {
				ret = STRCMP_UPPER;
			}
			break;
		}
		if (*string1 == NULL && *string2 == NULL) {
			break;
		}
		string1++;
		string2++;
	}
	return (ret);
}

/*************************************************************************
	module		:[文字列比較]
	function	:[
		1.2つの文字列を辞書式の順序で比較する
	]
	return		:[
		1.STRCMP_LOWER(-1):string1がstring2より小さい
		2.STRCMP_EQUAL( 0):string1とstring2は等しい
		3.STRCMP_UPPER( 1):string1がstring2より大きい
	]
	common		:[
		1."12"と"123"では"12"の方が小さい
		2.""と"1"では"1"の方が小さい
	]
	condition	:[]
	comment		:[
		CalculateStringAddress()でCMN_StringCompare()を
		使用した場合の再帰呼び出しを防ぐために新規作成
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2000/02/25]
	author		:[近藤伸行]
*************************************************************************/
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)  *//* SANYO仕様の追加 2000/02/25 N.Kondo */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SANYO仕様の追加 2000/02/25 N.Kondo */
UBYTE	CMN_StringCompare2(
UBYTE	*string1,		/* 比較する文字列 */
UBYTE	*string2,		/* 比較する文字列 */
UBYTE	size)			/* 比較する文字列長 */

{
	UBYTE	ret;				/* 比較結果 */
	UBYTE	i;					/* loop */
	register UWORD	char1;		/* String1の１ﾊﾞｲﾄ */
	register UWORD	char2;		/* String2の１ﾊﾞｲﾄ */

	ret = STRCMP_EQUAL;
	for (i = 0; i < size; i++) {
		if (*string1 != *string2) {
			char1 = *string1;
			if (char1 == 0 && i == 0) {
				char1 = 0x100;
			}
			char2 = *string2;
			if (char2 == 0 && i == 0) {
				char2 = 0x100;
			}
			if (char1 < char2) {
				ret = STRCMP_LOWER;
			}
			else {
				ret = STRCMP_UPPER;
			}
			break;
		}
		if (*string1 == NULL && *string2 == NULL) {
			break;
		}
		string1++;
		string2++;
	}
	return (ret);
}
#endif

/*************************************************************************
	module		:[文字列の反転]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/10]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_StringReverse(UBYTE *string)
{
	register WORD i;
	register WORD j;
	BYTE	c;

	j = CMN_StringLength(string) - 1;

	for (i = 0; i < j; i ++, j --) {
		c = string[i];
		string[i] = string[j];
		string[j] = c;
	}
	return;
}

/*************************************************************************
	module		:[指定文字が数字が否かの確認]
	function	:[
		1.
	]
	return		:[0:数字でない
				  1:数字
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/11]
	author		:[吉川弘康]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UBYTE	CMN_isdigitFlsRom(UBYTE data)
#else
UBYTE	CMN_isdigit(UBYTE data)
#endif
{
	if (data < '0' || data > '9') {
		return(0);
	}
	else {
		return(1);
	}
}

/*************************************************************************
	module		:[文字列を指定文字数コピー]
	function	:[
		1.指定文字数までにNULLがある場合その時点でコピーは終了。
		2.NULLはコピーしない
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[\src\kobe\anzu\src\OPR_SUB.Cからcmn_anz.cへ移動
				  \src\kobe\anzu\src\cmn_anz.cからのコピー
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/10/13]
	author		:[江口]
*************************************************************************/
UBYTE	*CMN_StringCopyNumNotNULL(
UBYTE	*DST_String,	/** コピー先の先頭アドレス */
UBYTE	*SRC_String,	/** コピー元文字列の先頭アドレス */
UBYTE	CopyCount)		/** コピー文字数 */
{

	/*-------------------------------------*/
	/* コピー元文字列のアドレス変換		   */
	/*-------------------------------------*/
	SRC_String = CalculateStringAddress(SRC_String); /* 1996/03/12 Eguchi */

	for ( ; (CopyCount > 0)&&(*SRC_String != NULL); CopyCount--) {
			*DST_String++ = *SRC_String++;
	}
	return (DST_String);
}

/*************************************************************************
	module		:[文字列のアドレスの計算]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
					\src\kobe\anzu\src\cmn_anz.cからのコピー
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/03/11]
	author		:[江口]
*************************************************************************/
UBYTE	*CalculateStringAddress(UBYTE *Address)
{
#if (PRO_CPU == SH7043)
	UBYTE	*word_top_adr;	/* 国別ﾜｰﾃﾞｨﾝｸﾞの先頭ｱﾄﾞﾚｽ by K.Watanabe 1998/10/22 */
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/* #if (PRO_KEYPANEL == PANEL_HINOKI)  *//* SANYO仕様の追加 2000/02/24 N.Kondo */
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SANYO仕様の追加 2000/02/24 N.Kondo */
	/* SANYO仕様のみ一部のワーディングを変更する必要があるが、
	** ROMを共通で管理する為に、ここで直接ワーディングを変換します
	*/
  #if (0)
	/* HINOKI IIのSanyo OEM（SFX-78M）が決定したのでそれに従い下記を修正します。 By O.Kimoto 2002/09/24 */
	if (CMN_StringCompare2(ROM_Revision, "SFX77", 5) == STRCMP_EQUAL) {	/* SANYO仕様の時 */
  #else
	if ((CMN_StringCompare2(ROM_Revision, "SFX77", 5) == STRCMP_EQUAL) 	/* F350 SANYO OEM 仕様の時 */
		|| (CMN_StringCompare2(ROM_Revision, "SFX78", 5) == STRCMP_EQUAL)) {	/* SANYO仕様の時 */
  #endif


		/* ＬＣＤ用ワーディング */
		if (Address == D2W_DocFine) {
			Address = D2W_DocFine_S;
		}
		else if (Address == D2W_DocSFine) {
			Address = D2W_DocSFine_S;
		}
		else if (Address == &D2W_ProgramTxModeSW[2][3]) {
			Address = &D2W_ProgramTxModeSW_S[2][3];
		}
		else if (Address == &D2W_ProgramTxModeSW[3][3]) {
			Address = &D2W_ProgramTxModeSW_S[3][3];
		}
		else if (Address == D2W_PrimaryModeFine) {
			Address = D2W_PrimaryModeFine_S;
		}
		else if (Address == D2W_PrimaryModeSFine) {
			Address = D2W_PrimaryModeSFine_S;
		}
		else if (Address == &D2W_ProgramContrastSW[1][3]) {
			Address = &D2W_ProgramContrastSW_S[1][3];
		}
		else if (Address == &D2W_ProgramContrastSW[3][3]) {
			Address = &D2W_ProgramContrastSW_S[3][3];
		}
		else if (Address == D2W_SelectPrimaryContrast) {
			Address = D2W_SelectPrimaryContrast_S;
		}
		else if (Address == D2W_PrimaryContrastLight) {
			Address = D2W_PrimaryContrastLight_S;
		}
		else if (Address == D2W_PrimaryContrastDark) {
			Address = D2W_PrimaryContrastDark_S;
		}
		else if (Address == D2W_CallReservation) {
			Address = D2W_CallReservation_S;
		}
		else if (Address == D2W_SF_Receive) {
			Address = D2W_SF_Receive_S;
		}
		else if (Address == D2W_SF_Hook) {
			Address = D2W_SF_Hook_S;
		}
		else if (Address == D2W_SF_Contrast) {
			Address = D2W_SF_Contrast_S;
		}

		/* リスト用ワーディング */
		else if (Address == PWRD_Fine) {
			Address = PWRD_Fine_S;
		}
		else if (Address == PWRD_SFine) {
			Address = PWRD_SFine_S;
		}
		else if (Address == PWRD_Contrast) {
			Address = PWRD_Contrast_S;
		}
		else if (Address == PWRD_Dark) {
			Address = PWRD_Dark_S;
		}
		else if (Address == PWRD_Light) {
			Address = PWRD_Light_S;
		}
	}
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/* #endif	*//* (PRO_KEYPANEL == PANEL_HINOKI) */
 #endif	/* (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) */

 #if (PRO_KEYPANEL == PANEL_POPLAR_B) && (PRO_OKI == ENABLE)	/* by K.Watanabe 1998/10/02 */
	/* 英語ワーディング固定の時は、第０ワーディング（マルチワーディング参照用のワーディング）を
	** 使用するので、アドレス計算は必要ありません
	*/
	if (SYB_MaintenanceSwitch[MNT_SW_A8] & FIXED_ENG_WORDING) {	/* 英語ワーディング固定表示の時 */
		return(Address);
	}
 #endif

 #if (PRO_PANEL == ANK)
	if ((D2W_WordingHead < Address) && (Address < D2W_WordingTail)) {
		/* 選択されているワーディングの先頭アドレスを取得します */
		switch (SYB_WordingNumber) {	/* 選択されているワーディングを調べます */
		case 1:		/* 第１ワーディングの時 */
			word_top_adr = D2W_1stWordingTop;
			break;
		case 2:		/* 第２ワーディングの時 */
			word_top_adr = D2W_2ndWordingTop;
			break;
  #if !defined(JPN)
		case 3:		/* 第３ワーディングの時 */
			word_top_adr = D2W_3rdWordingTop;
			break;
  #endif
		default:	/* それ以外の時（ありえない） */
			SaveReturnAddressAndJumpBegin();
			break;
		}

		/* 沖ヨーロッパ仕様では、ＲＯＭ管理の都合上、ワーディングの組み合わせが同じ国は、同じＲＯＭにしてあるので、
		** ワーディングの順番が違う国に関しては、ここで対応します（DNK･NOR → NOR, FIN･SWE → SWE）
		*/
  #if (PRO_KEYPANEL == PANEL_POPLAR_B) && (PRO_OKI == ENABLE) && defined(NOR)	/* by K.Watanabe 1998/10/22 */
		if (SYB_MachineParameter[COUNTRY_CODE] == COUNTRY_CODE_DNK) {	/* デンマークの時 */
			switch (SYB_WordingNumber) {	/* 選択されているワーディングを調べます */
			case 1:		/* 第１ワーディングの時 */
				word_top_adr = D2W_3rdWordingTop;	/* デンマーク語の先頭アドレスをセットします */
				break;
			case 3:		/* 第３ワーディングの時 */
				word_top_adr = D2W_1stWordingTop;	/* ノルウェー語の先頭アドレスをセットします */
				break;
			default:
				break;
			}
		}
  #elif (PRO_KEYPANEL == PANEL_POPLAR_B) && (PRO_OKI == ENABLE) && defined(SWE)
		if (SYB_MachineParameter[COUNTRY_CODE] == COUNTRY_CODE_FIN) {	/* フィンランドの時 */
			switch (SYB_WordingNumber) {	/* 選択されているワーディングを調べます */
			case 1:		/* 第１ワーディングの時 */
				word_top_adr = D2W_2ndWordingTop;	/* 英語の先頭アドレスをセットします */
				break;
			case 2:		/* 第２ワーディングの時 */
				word_top_adr = D2W_1stWordingTop;	/* スェーデン語の先頭アドレスをセットします */
				break;
			default:
				break;
			}
		}
  #endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) && (PRO_OKI == ENABLE) && defined(NOR) */

		return((UBYTE *)(word_top_adr + (Address - D2W_WordingTop)));
	}
 #endif	/* (PRO_PANEL == ANK) */

 #if (PRO_PANEL == KANJI)	/* 追加 By O.Kimoto 1997/06/25 */
	if ((D4W_WordingHead < Address) && (Address < D4W_WordingTail)) {
		switch (SYB_WordingNumber) {
		case 1:		/* 表示中のワーディングが第１ワーディングなら */
			return((UBYTE *)(D4W_1stWordingTop + (Address - D4W_WordingTop)));
		case 2:		/* 表示中のワーディングが第２ワーディングなら */
  #if (PRO_DUMMY_WORDING == ENABLE) /* By H.Fujimura 2002/07/11 */
			return((UBYTE *)(D4W_2ndWordingTop + (Address - D4W_WordingTop)));
  #else
			return((UBYTE *)(D4W_WordingTop + (Address - D4W_WordingTop)));
  #endif
  #if !defined(JPN)
		case 3:		/* 表示中のワーディングが第３ワーディングなら */
			return((UBYTE *)(D4W_3rdWordingTop + (Address - D4W_WordingTop)));
  #endif
		default:	/* ありえない */
			SaveReturnAddressAndJumpBegin();
		}
	}
 #endif

	if ((PWRD_HEAD < Address) && (Address < PWRD_TAIL)) {
#if (0)	/* 沖ヨーロッパ仕様の変更に合わせて変更します by K.Watanabe 1998/10/22 */
//		switch (SYB_WordingNumber) {
//		case 1:		/* 表示中のワーディングが第１ワーディングなら */
//			return((UBYTE *)(PWRD_1stWordingTop + (Address - PWRD_WordingTop)));
//		case 2:		/* 表示中のワーディングが第２ワーディングなら */
//			return((UBYTE *)(PWRD_2ndWordingTop + (Address - PWRD_WordingTop)));
// #if !defined(JPN)
//		case 3:		/* 表示中のワーディングが第３ワーディングなら */
//			return((UBYTE *)(PWRD_3rdWordingTop + (Address - PWRD_WordingTop)));
// #endif
//		default:	/* ありえない */
//			SaveReturnAddressAndJumpBegin();
//		}
#endif

		/* 選択されているワーディングの先頭アドレスを取得します */
		switch (SYB_WordingNumber) {	/* 選択されているワーディングを調べます */
		case 1:		/* 第１ワーディングの時 */
			word_top_adr = PWRD_1stWordingTop;
			break;
		case 2:		/* 第２ワーディングの時 */
   #if (PRO_DUMMY_WORDING == ENABLE) /* By H.Fujimura 2002/07/11 */
			word_top_adr = PWRD_2ndWordingTop;
   #else
			word_top_adr = PWRD_WordingTop;
   #endif
			break;
   #if !defined(JPN)
		case 3:		/* 第３ワーディングの時 */
			word_top_adr = PWRD_3rdWordingTop;
			break;
   #endif
		default:	/* それ以外の時（ありえない） */
			SaveReturnAddressAndJumpBegin();
			break;
		}

		/* 沖ヨーロッパ仕様では、ＲＯＭ管理の都合上、ワーディングの組み合わせが同じ国は、同じＲＯＭにしてあるので、
		** ワーディングの順番が違う国に関しては、ここで対応します（DNK･NOR → NOR, FIN･SWE → SWE）
		*/
  #if (PRO_KEYPANEL == PANEL_POPLAR_B) && (PRO_OKI == ENABLE) && defined(NOR)
		if (SYB_MachineParameter[COUNTRY_CODE] == COUNTRY_CODE_DNK) {	/* デンマークの時 */
			switch (SYB_WordingNumber) {	/* 選択されているワーディングを調べます */
			case 1:		/* 第１ワーディングの時 */
				word_top_adr = PWRD_3rdWordingTop;	/* デンマーク語の先頭アドレスをセットします */
				break;
			case 3:		/* 第３ワーディングの時 */
				word_top_adr = PWRD_1stWordingTop;	/* ノルウェー語の先頭アドレスをセットします */
				break;
			default:
				break;
			}
		}
  #elif (PRO_KEYPANEL == PANEL_POPLAR_B) && (PRO_OKI == ENABLE) && defined(SWE)
		if (SYB_MachineParameter[COUNTRY_CODE] == COUNTRY_CODE_FIN) {	/* フィンランドの時 */
			switch (SYB_WordingNumber) {	/* 選択されているワーディングを調べます */
			case 1:		/* 第１ワーディングの時 */
				word_top_adr = PWRD_2ndWordingTop;	/* 英語の先頭アドレスをセットします */
				break;
			case 2:		/* 第２ワーディングの時 */
				word_top_adr = PWRD_1stWordingTop;	/* スェーデン語の先頭アドレスをセットします */
				break;
			default:
				break;
			}
		}
  #endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) && (PRO_OKI == ENABLE) && defined(NOR) */

		return((UBYTE *)(word_top_adr + (Address - PWRD_WordingTop)));
	}

	return (Address);
#endif	/* (PRO_CPU == SH7043) */
}

/* ↓●ICHOU追加 by T.Soneoka 1996/05/08 */
/*************************************************************************
	module		:[指定されたビット位置の０／１をチェックする]
	function	:[
		1.
	]
	return		:[TRUE: ビットが１
				  FALSE:ビットが０
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/05/08]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE CMN_CheckBitAssign(UBYTE *buf, UBYTE pos)
{
	if (buf[((UBYTE)(pos)>>3)] & (0x01 << (pos & 0x07))) {
		return (TRUE);
	}
	else {
		return (FALSE);
	}
}

/* ↓●ICHOU追加 by T.Soneoka 1996/05/08 */
/*************************************************************************
	module		:[指定されたビット位置に１セットする]
	function	:[
		1.
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/05/08]
	author		:[曽根岡拓]
*************************************************************************/
void CMN_SetBitAssign(UBYTE *buf, UBYTE pos)
{
	buf[((UBYTE)(pos)>>3)] |= (0x01 << (pos & 0x07));
}

/* ↓●ICHOU追加 by T.Soneoka 1996/05/08 */
/*************************************************************************
	module		:[指定されたビット位置に０セットする]
	function	:[
		1.
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/05/23]
	author		:[曽根岡拓]
*************************************************************************/
void CMN_ClearBitAssign(UBYTE *buf, UBYTE pos)
{
	buf[((UBYTE)(pos)>>3)] &= ~(0x01 << (pos & 0x07));
}

/*************************************************************************
	module		:[指定されたビット位置の０／１をチェックする（ロング変数用）]
	function	:[
		1.
	]
	return		:[TRUE: ビットが１
				  FALSE:ビットが０
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/03/25]
	author		:[桑原美紀]
*************************************************************************/
UBYTE CMN_CheckLongBitAssign(UDWORD buf, UBYTE pos)
{
	if (buf & (0x01 << pos)) {
		return (TRUE);
	}
	else {
		return (FALSE);
	}
}

/*************************************************************************
	module		:[指定されたビット位置に１セットする（ロング変数用）]
	function	:[
		1.
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/03/25]
	author		:[桑原美紀]
*************************************************************************/
void CMN_SetLongBitAssign(UDWORD *buf, UBYTE pos)
{
	*buf |= (0x01 << pos);
}

/*************************************************************************
	module		:[指定されたビット位置に０セットする（ロング変数用）]
	function	:[
		1.
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/03/25]
	author		:[桑原美紀]
*************************************************************************/
void CMN_ClearLongBitAssign(UDWORD *buf, UBYTE pos)
{
	*buf &= ~(0x01 << pos);
}

/*************************************************************************
	module		:[文字列の挿入]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2001/06/08]
	author		:[石橋正和]
*************************************************************************/
#if (PRO_FORVAL_LCR1 == ENABLE) || (PRO_PREFIX_KEY == ENABLE)	/* By H.Fujimura 2002/07/11 *//* by K.Watanabe 2004/11/10 */
UBYTE* CMN_InsertString(
			UBYTE* pdst,		/* 挿入先文字列(NULL終端) */
			CONST UBYTE* psrc,	/* 挿入する文字列(NULL終端) */
			UWORD index)		/* 何文字目の後に挿入するか */
{
	UWORD dst_length;
	UWORD src_length;
	UBYTE* pstr;
	UWORD i;
	
	dst_length = CMN_StringLength(pdst);
	src_length = CMN_StringLength(psrc);
	
	pstr = pdst + dst_length;
	
	for (i = 0; i < dst_length - index + 1; i++) {
		*(pstr + src_length) = *pstr;
		pstr--;
	}
	
	return (CMN_StringCopy(pdst + index, psrc));
}
#endif

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC 設定表示 By M.Maeda 2003/02/07 */
/*************************************************************************
	module		:[リモートダイアル転送の設定ダイアル番号をASCII文字列で返す  REMOTE_RX_FUNC]
	function	:[
		※ 4バイトのバッファへのポインタを引数で渡してください
	]
	return		:[
		リモートダイアル転送番号の有効桁数(0～3)
		リモートダイアル転送OFFのときは0
	]
	date		:[2003/02/04]
	author		:[]
*************************************************************************/
UBYTE	CMN_GetRemoteTransferDialString(UBYTE * str)
{
	UBYTE	dial_bcd[4];	/* BCD 1桁を1byteとして格納 */
	UBYTE	dial_max = 0;	/* 検出ダイヤル有効桁数 */
	UBYTE	count = 0;
	UBYTE	is_tone = FALSE;
	UBYTE	is_dp_ng = FALSE;

	/* バッファ初期化 */
	for (count = 0; count < 4; count++) {
		*(str + count) = NULL;
	}

	if (CHK_TEL2FaxTransferAvailable()) {	/* 外付け電話の転送受信機能 */
		if (CHK_RemoteTransferDial()) {			/* リモートダイアル転送を行うか(転送受信有効設定の時のみ有効) */
			/* リモートダイアル転送検出番号チェック */
			dial_bcd[0] = CHK_RemoteTransferDialNumber1();		/* 1桁目 */
			if (dial_bcd[0] == 0x00) {		/* メモリSW設定が'0'の時は'5'で動作する */
				dial_bcd[0] = 0x05;
			}
			dial_bcd[1] = CHK_RemoteTransferDialNumber2();		/* 2桁目 */
			if (dial_bcd[1] == 0x00) {		/* メモリSW設定が'0'の時は'5'で動作する */
				dial_bcd[1] = 0x05;
			}
			dial_max = 2;		/* 2桁検出(デフォルト) */

#if (PRO_LINENUMBER == TWICE_LINE) /* 拡張回線の場合は拡張回線ダイヤルの種別を見るようにします By M.Maeda 2003/02/21 */
			if (!CHK_Phone2ExtLineOn()) {	/* 標準回線 */
				/* 標準回線設定チェック */
				if (CHK_DialType() & LINE_TYPE_TONE) {
					is_tone = TRUE;
				}
			}
			else {							/* 拡張回線 */
				/* 拡張回線設定チェック */
				if (CHK_DialTypeExt() & LINE_TYPE_TONE_EXT) {
					is_tone = TRUE;
				}
			}
			if (CHK_RemoteTransferForcedDTMF()) {	/* パルス設定でも強制的にDTMFのほうを検出する */
				is_tone = TRUE;
			}
#else
			/* 回線設定チェック */
			if (CHK_DialType() & LINE_TYPE_TONE) {
				is_tone = TRUE;
			}
			else {
				is_tone = FALSE;
				if (CHK_RemoteTransferForcedDTMF()) {	/* パルス設定でも強制的にDTMFのほうを検出する */
					is_tone = TRUE;
				}
			}
#endif
			/* トーン／パルス個別の転送設定チェック */
			if (is_tone) {							/* トーン設定 */
				if (CHK_RemoteTransfer3ThNumber()) {	/* リモートダイアル転送ＤＴＭＦ時３桁検出とする */
					dial_max = 3;							/* 3桁検出 */
					dial_bcd[2] = CMN_ASC_ToBCD('#');		/* 3桁目は'#'固定 */
				}
			}
			else {									/* パルス設定 */
				if (CHK_RemoteTransferDialOne()) {		/* リモートダイアル転送のＤＰ時、１桁目だけ検出する */
					dial_max = 1;							/* 1桁検出 */
				}
			}

			/* 有効桁数分のBCDをASCII変換しながらリターンバッファにセット */
			for (count = 0; count < dial_max; count++) {
				if (dial_bcd[count] >= 0x0C) {		/* 0x0C以上は'0'を検出する */
					dial_bcd[count] = CMN_ASC_ToBCD('0');
				}
				*(str + count) = CMN_BCD_ToASC(dial_bcd[count]);

				/* パルスの場合、0x0A(*),0x0B(#)が含まれているかチェック */
				if (!is_tone) {
					if ((dial_bcd[count] == 0x0A) || (dial_bcd[count] == 0x0B)) {
						is_dp_ng = TRUE;
					}
				}
			}

			/* パルスで0x0A(*),0x0B(#)が1桁でも含まれているとNGなのでマスク */
			if (!is_tone && is_dp_ng) {
				for (count = 0; count < dial_max; count++) {
					*(str + count) = 'x';		/* ※マスクしたことが分かるようにします */
				}
			}
		}
		else if (CHK_RemoteTransferOnHook()) {	/* オンフック転送を行うか(転送受信有効設定の時のみ有効) */
		}
	}

	return (dial_max);
}
#endif	/* REMOTE_RX_FUNC 設定表示 */

#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 移植 by SMuratec L.Z.W 2003/08/13 */
#if (PRO_JIS_CODE == ENABLE)
/*************************************************************************
	module		:[ＪＩＳ第１水準コード検査]
	function	:[
		1.指定のコードがJIS第１水準のコードかどうかを調べます
	]
	return		:[
		TRUE:	JIS第１水準コード
		FALSE:	JIS第１水準以外のコード
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[CMN]
	date		:[1997/04/08]
	auther		:[渡辺一章]
*************************************************************************/
UBYTE CMN_CheckJIS1Code(CONST UWORD code)
{
	UBYTE	high_byte;		/* コードの上位バイト */
	UBYTE	low_byte;		/* コードの下位バイト */
	UBYTE	is_jis_code;	/* JISコードか？ */

	high_byte = (UBYTE)((0xFF00 & code) >> 8);
	low_byte = (UBYTE)(0x00FF & code);
	is_jis_code = FALSE;

	/* 引数のJISコードが、JIS第１水準のJISコードかを調べます */
	if (((high_byte == 0x21 || (0x30 <= high_byte && high_byte <= 0x4E))
	  && (0x21 <= low_byte && low_byte <= 0x7E))	/* 記号，頭文字ア～レ	*/
	 || (0x2221 <= code && code <= 0x222E)			/* 記号					*/
	 || (0x2330 <= code && code <= 0x2339)			/* 数字					*/
	 || (0x2341 <= code && code <= 0x235A)			/* 英字（大）			*/
	 || (0x2361 <= code && code <= 0x237A)			/* 英字（小）			*/
	 || (0x2421 <= code && code <= 0x2473)			/* ひらがな				*/
	 || (0x2521 <= code && code <= 0x2576)			/* カタカナ				*/
	 || (0x2621 <= code && code <= 0x2638)			/* ギリシャ文字（大）	*/
	 || (0x2641 <= code && code <= 0x2658)			/* ギリシャ文字（小）	*/
	 || (0x2721 <= code && code <= 0x2741)			/* ロシア文字（大）		*/
	 || (0x2751 <= code && code <= 0x2771)			/* ロシア文字（小）		*/
	 || (0x4F21 <= code && code <= 0x4F53)) {		/* 頭文字ロ・ワ			*/
		is_jis_code = TRUE;
	}

	return (is_jis_code);
}

/*************************************************************************
	module		:[フォント定義ＪＩＳ第２水準コード検査]
	function	:[
		1.指定のコードがJIS第２水準のコードかどうかを調べます
		2.ただし、全てのJIS第２水準と比較する訳ではなく、
		　フォント定義されているJIS第２水準コードのみを対象とします
	]
	return		:[
		０～KANJI2_TABLE_MAX	:フォント定義されているテーブル番号
		KANJI2_NONE				:JIS第２水準（フォント定義されている）コード以外
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[CMN]
	date		:[1997/04/09]
	auther		:[渡辺一章]
*************************************************************************/
UBYTE CMN_CheckFontJIS2Code(CONST UWORD code)
{
	UBYTE	i;						/* ループ変数 */
	UBYTE	jis2_code_table_number;	/* JIS第二水準のテーブル番号 */

	jis2_code_table_number = KANJI2_NONE;

	for (i = 0; i < KANJI2_TABLE_MAX; i++) {
#if defined(LONDON)
		if (CG_ROM_JIS_2[i].Code == code) {	/* フォント定義されているJIS第２水準のJISコードの時 */
#else
		if (Kanji2[i].Code == code) {	/* フォント定義されているJIS第２水準のJISコードの時 */
#endif
			jis2_code_table_number = i;
			break;
		}
	}

	return (jis2_code_table_number);
}

/*************************************************************************
	module		:[シフトＪＩＳコード検査]
	function	:[
		1.指定のコードがシフトJIS（第１水準・第２水準）のコードかを調べます
	]
	return		:[
		TRUE:	シフトJISコード
		FALSE:	シフトJIS以外のコード
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[CMN]
	date		:[1997/04/09]
	auther		:[渡辺一章]
*************************************************************************/
UBYTE CMN_CheckShiftJISCode(CONST UBYTE high_byte, CONST UBYTE low_byte)
{
	UBYTE	is_s_jis_code;	/* シフトJISコードか？ */

	is_s_jis_code = FALSE;

	/* 引数のコードが、シフトJISのコードかを調べます */
	if (((high_byte >= SHIFT_JIS_1_HIGH_MIN) && (high_byte <= SHIFT_JIS_1_HIGH_MAX)
	  || (high_byte >= SHIFT_JIS_2_HIGH_MIN) && (high_byte <= SHIFT_JIS_2_HIGH_MAX))
	 && ((low_byte >= SHIFT_JIS_LOW_MIN) && (low_byte <= SHIFT_JIS_LOW_MAX))) {
		is_s_jis_code = TRUE;
	}

	return (is_s_jis_code);
}
#endif	/* (PRO_JIS_CODE == ENABLE) */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) */
