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
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\std.h"

#include "\src\atlanta\flash\define\sys_pro.h"
#include "\src\atlanta\flash\ext_v\sys_data.h"

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
	module		:[文字列のコピー]
	function	:[
		1.NULLを含まずにコピーする
		2.アドレスを計算する必要が無いので削除している 97/07/14 By M.Kuwahara
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
	while (*src_ptr != NULL) {
		*dst_ptr++ = *src_ptr++;
	}
	return(dst_ptr);
}


/* CMN_CNV.Cの関数 */
/*************************************************************************
	module		:[ＨＥＸコードをＡＳＣ文字列に変換]
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
	date		:[1996/02/20]
	author		:[江口]
*************************************************************************/
void	CMN_HexToASC(
UBYTE	*DST_String,	/* ＡＳＣ文字列 */
UDWORD	HexCode,		/* 変換ヘキサコード */
UBYTE	Count)			/* 変換文字数 		 */
{
	UBYTE	shift_count;
	UBYTE	data;
	UBYTE	asc;

	while (Count > 0) {
		shift_count = (UBYTE)(4 * (Count - 1));

		data = (UBYTE)((HexCode & (0x0000000FUL << shift_count)) >> shift_count);

		if (data <= 0x09) { /* 0 - 9 */
			asc = (UBYTE)('0' + data);
		}
		else { /* A - F */
			data -= 0x0A;
			asc =(UBYTE)('A' + data);
		}
		*DST_String++ = asc;
		Count--;
	}
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

	for (i = 0; *string++ != NULL; i++);
	return (i);
}


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


/* CMN_CNV.Cの関数 */
/*************************************************************************
	module		:[long型をアスキ－列(NULL含む)に変換]
	function	:[
		1.最終文字に続く文字にはNULLをセットする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[sizeが0の場合、変換後の全桁数を有効とする]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/ 3/24]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_UnsignedLongToASC_NULL(
UBYTE	*dst_string,	/* 変換先アドレス */
UDWORD	data,			/* 変換される数字 */
UBYTE	size,			/* 変換桁数 */
UBYTE	pad_data)		/* 上位桁0データを置き換える文字 */
{
	register UWORD length;			/* 有効数字桁数 */

	length = 0;
	if (data == 0) {
		dst_string[length++] = '0';
	}
	else {
		for (; data != 0; length++) {
			if (size != 0 && length >= size) {
				break;
			}
			dst_string[length] = (UBYTE)((data % 10) + '0');
			data /= 10;
		}
	}
	if (size != 0) {
		for (;length < size; length++) {
			dst_string[length] = pad_data;
		}
	}
	dst_string[length] = NULL;
	CMN_StringReverse(dst_string);
}


/* CMN_CNV.Cの関数 */
/*************************************************************************
	module		:[long型をアスキー列(NULL含まず)に変換]
	function	:[
		1.最終文字に続く文字にはNULLをセットしない
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[最大変換桁数:19桁]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/ 3/24]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_UnsignedLongToASC(
UBYTE	*dst_string,	/* 変換先アドレス */
UDWORD	data,			/* 変換される数字 */
UBYTE	size,			/* 変換桁数 */
UBYTE	pad_data)		/* 上位桁0データを置き換える文字 */
{
	UBYTE tmp_buf[20];

	CMN_UnsignedLongToASC_NULL((UBYTE *)tmp_buf, data, size, pad_data);
	CMN_StringCopy(dst_string, (UBYTE *)tmp_buf);
}


