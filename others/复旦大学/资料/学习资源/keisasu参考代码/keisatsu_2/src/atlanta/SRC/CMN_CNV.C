/************************************************************************
*	System		: POPLAR/ANZU-L
*	File Name	: CMN_CNV.C
*	Author		: 橘正樹
*	Date		: 1996/11/02
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニタ
*	Description	:
*	Maintenance	:
*				: Original:\src\kobe\anzu\src\cmn_data.c
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysmax.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\syscomf.h"
#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\cmn_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\cmn_tbl.h"

#if (PRO_PANEL == KANJI)				/* 漢字対応操作パネル */
#include "\src\atlanta\opr\kanji\define\opr_def.h" /* added by H.Kubo 1998/06/03 */
#include "\src\atlanta\opr\kanji\ext_v\opr_data.h"
#endif


/*************************************************************************
	module		:[int型をアスキ－列(NULL含む)に変換]
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
	date		:[1993/12/10]
	author		:[吉川弘康]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
void	CMN_UnsignedIntToASC_NULLFlsRom(
UBYTE	*dst_string,	/* 変換先アドレス */
UWORD	data,			/* 変換される数字 */
UBYTE	size,			/* 変換桁数 */
UBYTE	pad_data)		/* 上位桁0データを置き換える文字 */
#else
void	CMN_UnsignedIntToASC_NULL(
UBYTE	*dst_string,	/* 変換先アドレス */
UWORD	data,			/* 変換される数字 */
UBYTE	size,			/* 変換桁数 */
UBYTE	pad_data)		/* 上位桁0データを置き換える文字 */
#endif
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

/*************************************************************************
	module		:[int型をアスキー列(NULL含まず)に変換]
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
	date		:[1993/12/25]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_UnsignedIntToASC(
UBYTE	*dst_string,	/* 変換先アドレス */
UWORD	data,			/* 変換される数字 */
UBYTE	size,			/* 変換桁数 */
UBYTE	pad_data)		/* 上位桁0データを置き換える文字 */
{
	UBYTE tmp_buf[20];

	CMN_UnsignedIntToASC_NULL((UBYTE *)tmp_buf, data, size, pad_data);
	CMN_StringCopy(dst_string,(UBYTE *)tmp_buf);
}

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

/*************************************************************************
	module		:[long型を１６進でアスキ－列(NULL含む)に変換]
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
	date		:[1994/ 5/14]
	author		:[奥村明]
*************************************************************************/
void	CMN_UnsignedLongToHexASC_NULL(
UBYTE	*dst_string,	/* 変換先アドレス */
UDWORD	data,			/* 変換される数字 */
UBYTE	size,			/* 変換桁数 */
UBYTE	pad_data)		/* 上位桁0データを置き換える文字 */
{
	register UWORD length;			/* 有効数字桁数 */
	UBYTE string;					/* 変換される文字	*/

	length = 0;
	if (data == 0) {
		dst_string[length++] = '0';
	}
	else {
		for (; data != 0; length++) {
			if (size != 0 && length >= size) {
				break;
			}
			if ((data % 16) >= 10) {
				string = (UBYTE)((data % 16) - 10 + 'A');
			}
			else {
				string = (UBYTE)((data % 16) + '0');
			}
			dst_string[length] = string;
			data /= 16;
		}
	}
	if (size != 0) {
		for (;length < size; length++) {
			dst_string[length] = pad_data;
		}
	}
	dst_string[length] = '\0';
	CMN_StringReverse(dst_string);
}

/*************************************************************************
	module		:[アスキー列の指定文字数分をint型データに変換]
	function	:[
		1.
	]
	return		:[0～9999:int型データ
				  0xFFFF :アスキー列に数字以外の文字がある
						 :変換文字数が4を越えている
	]
	common		:[]
	condition	:[]
	comment		:[変換文字数は4文字以内]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/11]
	author		:[吉川弘康]
*************************************************************************/
UWORD	CMN_ASC_ToUnsignedInt(
UBYTE	*src_ptr,		/* 変換元アドレス */
UBYTE	size)			/* 変換文字数 */
{
	UBYTE y;
    UWORD z;

    z = 0;

	if (size > 4) {
		return (0xFFFF);
	}

	for (; size != 0; size--) {
		y = *src_ptr++;
		if (!CMN_isdigit(y)) {
			return(0xFFFF);
		}
		else {
			z = z * 10 + (UWORD)(y - '0');
		}
	}
	return (z);
}

/*************************************************************************
	module		:[アスキー列の指定文字数分を16進数としてint型データに変換]
	function	:[
		1.
	]
	return		:[0～0xFFFF:int型データ
	]
	common		:[]
	condition	:[]
	comment		:[変換文字数は4文字以内
					A～Fは大文字のみ
					この関数を呼ぶ前にバッファの内容の妥当性をチェックすること]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/07/27]
	author		:[石橋正和]
*************************************************************************/
UWORD	CMN_ASC_ToUnsignedIntHex(
UBYTE	*src_ptr,		/* 変換元アドレス */
UBYTE	size)			/* 変換文字数 */
{
	UBYTE y;
    UWORD z;

    z = 0;

	for (; size != 0; size--) {
		y = *src_ptr++;
		if (y <= '9') {
			y -= '0';
		}
		else {
			y -= ('A' - 0x0A);
		}
		z = z * 0x10 + y;
	}
	return (z);
}

/*************************************************************************
	module		:[ダイヤルBCD列をアスキー列に変換]
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
void	CMN_BCD_ToASC_String(
UBYTE	*ASC_ptr,		/* 変換先アドレス */
UBYTE	*BCD_ptr)		/* 変換元アドレス */
{
	while (((*BCD_ptr & 0xF0) != 0xF0) && ((*BCD_ptr & 0x0F) != 0x0F)) {
		*ASC_ptr++ = CMN_BCD_ToASC((UBYTE)((*BCD_ptr & 0xF0) >> 4));
		*ASC_ptr++ = CMN_BCD_ToASC((UBYTE)(*BCD_ptr++ & 0x0F));
	}
	if (((*BCD_ptr & 0xF0) != 0xF0) && ((*BCD_ptr & 0x0F) == 0x0F)) {
		*ASC_ptr++ = CMN_BCD_ToASC((UBYTE)((*BCD_ptr & 0xF0) >> 4));
	}
	*ASC_ptr = NULL;
}

/*************************************************************************
	module		:[BCDコードをアスキーコードに変換]
	function	:[
		1.
	]
	return		:[村田BCDコードに対応するアスキーコード]
	common		:[]
	condition	:[]
	comment		:[AP/VUL系村田標準に準拠]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/10]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_BCD_ToASC(UBYTE BCD)	/* 変換前BCDコード */
{
	if (BCD <10) {
		return((UBYTE)(BCD + '0'));
	}
	switch (BCD) {
	case 0x0A:
		return('*');
	case 0x0B:
		return('#');
	case 0x0C:
		return('/');	/* '-'->'/' By H.Y 1994/06/24 */
	case 0x0D:
		return('-');	/* '/'->'-' By H.Y 1994/06/24 */
	case 0x0E:
		return('!');
	}
}

/*************************************************************************
	module		:[Ｆコード用データバッファBCD列をアスキー列に変換]
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
	date		:[1997/04/28]
	author		:[山口哲治]
*************************************************************************/
void	CMN_FCODE_BCD_ToASC_String(
UBYTE	*ASC_ptr,		/* 変換先アドレス */
UBYTE	*BCD_ptr)		/* 変換元アドレス */
{
	while (((*BCD_ptr & 0xF0) != 0xF0) && ((*BCD_ptr & 0x0F) != 0x0F)) {
		*ASC_ptr++ = CMN_FCODE_BCD_ToASC((UBYTE)((*BCD_ptr & 0xF0) >> 4));
		*ASC_ptr++ = CMN_FCODE_BCD_ToASC((UBYTE)(*BCD_ptr++ & 0x0F));
	}
	if (((*BCD_ptr & 0xF0) != 0xF0) && ((*BCD_ptr & 0x0F) == 0x0F)) {
		*ASC_ptr++ = CMN_FCODE_BCD_ToASC((UBYTE)((*BCD_ptr & 0xF0) >> 4));
	}
	*ASC_ptr = NULL;
}
/*************************************************************************
	module		:[Ｆコード用データバッファBCD列をアスキー列に変換
					＊、＃、スペースを途中にいれない処理				]
	function	:[
		1.BCD列のﾃﾞｰﾀが0～9までの値のものをｱｽｷｰ列に変換
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/04/28]
	author		:[山口哲治]
*************************************************************************/
void	CMN_BCD_Number_ToASC_String(
UBYTE	*ASC_ptr,		/* 変換先アドレス */
UBYTE	*BCD_ptr)		/* 変換元アドレス */
{
	while (((*BCD_ptr & 0xF0) != 0xF0) && ((*BCD_ptr & 0x0F) != 0x0F)) {
		if (((*BCD_ptr & 0xF0) >> 4) < 0x0A ) {	/* 0～9なら */
			*ASC_ptr++ = CMN_FCODE_BCD_ToASC((UBYTE)((*BCD_ptr & 0xF0) >> 4));
		}
		if ((*BCD_ptr & 0x0F) < 0x0A) {		/* 0～9なら */
			*ASC_ptr++ = CMN_FCODE_BCD_ToASC((UBYTE)(*BCD_ptr & 0x0F));
		}
		*BCD_ptr++;
	}
	if (((*BCD_ptr & 0xF0) != 0xF0) && ((*BCD_ptr & 0x0F) == 0x0F)) {
		if (((*BCD_ptr & 0xF0) >> 4) < 0x0A) {	/* 0～9なら */
			*ASC_ptr++ = CMN_FCODE_BCD_ToASC((UBYTE)((*BCD_ptr & 0xF0) >> 4));
		}
	}
	*ASC_ptr = NULL;
}

/*************************************************************************
	module		:[Ｆコード用データバッファBCD列をアスキー列に変換
					スペースを途中にいれない処理(*,#は有効）	]
	function	:[
		1.BCD列のﾃﾞｰﾀが0～9,0xA,0xBまでの値のものをｱｽｷｰ列に変換
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/04/28]
	author		:[山口哲治]
*************************************************************************/
void	CMN_NoSpaceBCD_ToASC_String(
UBYTE	*ASC_ptr,		/* 変換先アドレス */
UBYTE	*BCD_ptr)		/* 変換元アドレス */
{
	while (((*BCD_ptr & 0xF0) != 0xF0) && ((*BCD_ptr & 0x0F) != 0x0F)) {
		if (((*BCD_ptr & 0xF0) >> 4) < 0x0C ) {	/* 0～9,*,#なら */
			*ASC_ptr++ = CMN_FCODE_BCD_ToASC((UBYTE)((*BCD_ptr & 0xF0) >> 4));
		}
		if ((*BCD_ptr & 0x0F) < 0x0C) {		/* 0～9,*,#なら */
			*ASC_ptr++ = CMN_FCODE_BCD_ToASC((UBYTE)(*BCD_ptr & 0x0F));
		}
		*BCD_ptr++;
	}
	if (((*BCD_ptr & 0xF0) != 0xF0) && ((*BCD_ptr & 0x0F) == 0x0F)) {
		if (((*BCD_ptr & 0xF0) >> 4) < 0x0C) {	/* 0～9,*,#なら */
			*ASC_ptr++ = CMN_FCODE_BCD_ToASC((UBYTE)((*BCD_ptr & 0xF0) >> 4));
		}
	}
	*ASC_ptr = NULL;
}


/*************************************************************************
	module		:[F_CODE用BCDコードをアスキーコードに変換]
	function	:[
		1.
	]
	return		:[Ｆコード用BCDコードに対応するアスキーコード]
	common		:[]
	condition	:[０～９と＊、＃を通常通り、その他はスペースに変換する]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/04/28]
	author		:[山口哲治]
*************************************************************************/
UBYTE	CMN_FCODE_BCD_ToASC(UBYTE BCD)	/* 変換前BCDコード */
{
	if (BCD <10) {
		return((UBYTE)(BCD + '0'));
	}
	switch (BCD) {
	case 0x0A:
		return('*');
	case 0x0B:
		return('#');
	case 0x0C:
		return(' ');	/* Ｆコードデータバッファでは、0x0Cが入っている */
	default:	/*	未使用に付き空白をかえしましょう	by A.O*/
		return(' ');
	}
}

/*************************************************************************
	module		:[BCDコードをアスキーコードに変換]
	function	:[
		1.
	]
	return		:[FXBCDコードに対応するアスキーコード]
	common		:[]
	condition	:[]
	comment		:[FX標準に準拠]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/11/21]
	author		:[奥村明]
*************************************************************************/
UBYTE	CMN_FXBCD_ToASC(UBYTE BCD)	/* 変換前BCDコード */
{
	if (BCD <10) {
		return((UBYTE)(BCD + '0'));
	}
	switch (BCD) {
	case 0x0A:
		return('#');
	case 0x0B:
		return('*');
	default:	/*	未使用に付き空白をかえしましょう	by A.O*/
		return(' ');
	}
}

/*************************************************************************
	module		:[ダイヤルアスキー列をBCD列に変換]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[この関数を呼ぶ前に変換先アドレスの内容を0xFFクリアすること]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/10]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_ASC_ToBCD_String(
UBYTE	*BCD_ptr,		/* 変換先アドレス */
UBYTE	*ASC_ptr)		/* 変換元アドレス */
{
	register WORD i;
	UBYTE a;
	UBYTE b;

	i = 0;
	for (i = 0; i < SYS_TEL_2DIGIT_MAX; i++) {
		a = *ASC_ptr++;
		b = *ASC_ptr++;
		*BCD_ptr++ = (UBYTE)((CMN_ASC_ToBCD(a) << 4) + CMN_ASC_ToBCD(b));
		if (a == NULL || b == NULL) {
			break;
		}
	}
}

/*************************************************************************
	module		:[ダイヤルアスキー列をBCD列に変換]
	function	:[
		1.桁数指定する
	]
	return		:[]
	common		:[]
	condition	:[この関数を呼ぶ前に変換先アドレスの内容を0xFFクリアすること]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/10/22]
	author		:[山口]
*************************************************************************/
void	CMN_ASC_ToBCD_StringNumber(
UBYTE	*BCD_ptr,		/* 変換先アドレス */
UBYTE	*ASC_ptr,		/* 変換元アドレス */
UBYTE	figure)			/* 指定桁数 */
{
	UWORD i;
	UBYTE a;
	UBYTE b;

	i = 0;
	for (i = 0; i < figure; i++) {
		a = *ASC_ptr++;
		b = *ASC_ptr++;
		*BCD_ptr++ = (UBYTE)((CMN_ASC_ToBCD(a) << 4) + CMN_ASC_ToBCD(b));
		if (a == NULL || b == NULL) {
			break;
		}
	}
}

/*************************************************************************
	module		:[アスキーコードをBCDコードに変換]
	function	:[
		1.
	]
	return		:[変換後BCDコード]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/10]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_ASC_ToBCD(UBYTE ASC)	/* 変換前アスキーコード */
{
	if ((ASC >= '0') && (ASC <= '9')) {
		return((UBYTE)(ASC & 0x0f));
	}
	switch(ASC) {
#if (PRO_PIN_ACCESS == ENABLE) /* added by H.Kubo 1998/06/03 */
 #if (PRO_PANEL == KANJI)
	case OPR_PIN_MARK: /* '*' が PIN の区切り記号となっているので、 '*' と同じ値に変換します。 H.Kubo 1998/06/03 */
 #endif
#endif
	case '*':
		return(0x0A);
	case '#':
		return(0x0B);
	case '-':				/* '/'->'-' By H.Y 1994/06/24 */
		return(0x0D);
	case '!':
		return(0x0E);
	case '\0':
		return(0x0F);
	default:	/* '/' ' ' '+' 1997/10/23  By T.Yamaguchi */
		return(0x0C);
	}
}

/*************************************************************************
	module		:[アスキーコードをFX仕様BCDコードに変換]
	function	:[
		1.
	]
	return		:[変換後BCDコード]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/4/19]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE	CMN_ASC_ToFXBCD(UBYTE ASC)	/* 変換前アスキーコード */
{
	if ((ASC >= '0') && (ASC <= '9')) {
		return((UBYTE)(ASC & 0x0f));
	}
	switch(ASC) {
	case '*':
		return(0x0B);
	case '#':
		return(0x0C);
	}
}

/*************************************************************************
	module		:[struct型BCD時間をlong型時間に変換]
	function	:[
		1.
	]
	return		:[long型時間]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/10]
	author		:[吉川弘康]
*************************************************************************/
UDWORD	CMN_BCD_TimeToLong(TIME_DATA_t *BCD_time)	/* struct型BCD時間 */
{
	UBYTE dif_year;		/* 現在の年から92年を引いた差 */
	UBYTE dif_month;	/* 現在の月から一月を引いた差 */
	UBYTE dif_day;		/* 現在の日から一日を引いた差 */
	UBYTE dif_hour;		/* 現在の時(hour) */
	UBYTE dif_minute;	/* 現在の分(minute) */
	UBYTE dif_second;	/* 現在の秒(second) */
	UDWORD add_day;		/* 閏年や月毎の日数の違いのため追加する日数 */

	/* ２０００年から２０９１年の時 */

	if (BCD_time->Year < 0x92) {

		/* ＢＣＤを普通の１６進に変換したものに８年加える */

		dif_year = (UBYTE)(CMN_BCD_ToDecimal(BCD_time->Year) + 8);
	}

	/* 現在の年が１９９２年から１９９９年の時 */

	else {
		dif_year = (UBYTE)(BCD_time->Year - 0x92);
	}
	dif_month = (UBYTE)(CMN_BCD_ToDecimal(BCD_time->Month) - 1);
	dif_day = (UBYTE)(CMN_BCD_ToDecimal(BCD_time->Date) - 1);
	dif_hour = CMN_BCD_ToDecimal(BCD_time->Hour);
	dif_minute = CMN_BCD_ToDecimal(BCD_time->Minute);
	dif_second = CMN_BCD_ToDecimal(BCD_time->Second);
	add_day = (UDWORD)dif_year/4 + 1;	/* 閏年の時の日数加算 */

	/* 閏年ではあるが２月２９日以前の時 */

	if ((dif_year % 4 == 0) && (dif_month < 2)) {
		add_day = add_day - 1;
	}
	add_day = add_day + (UDWORD)dif_month*30;  /* 一ヶ月を３０日として月数を乗算 */

	/* 月ごとの日数の違いに応じて日数加減 */

	switch (dif_month) {
	case 1:
	case 5:
	case 6:
		add_day = add_day + 1;
		break;
	case 2:
		add_day = add_day - 1;
		break;
	case 7:
		add_day = add_day + 2;
		break;
	case 8:
	case 9:
		add_day = add_day + 3;
		break;
	case 10:
	case 11:
		add_day = add_day + 4;
		break;
	}

	/* 秒積算して　UDWORD 型に変換 */

	return((UDWORD)dif_year * 365 * 24 * 60 * 60
		 + (UDWORD)(dif_day + add_day) * 24 * 60 * 60
		 + (UDWORD)dif_hour * 60 * 60
		 + (UDWORD)dif_minute * 60
		 + (UDWORD)dif_second);
}

/*************************************************************************
	module		:[BCDを10進数に変換]
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
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_BCD_ToDecimal(UBYTE BCD)	/* 変換前BCD */
{
	return((UBYTE)((BCD >> 4) * 10 + (BCD & 0x0f)));
}

/*************************************************************************
	module		:[long型時間をstruct型BCD時間に変換]
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
void	CMN_LongTimeToBCD(
TIME_DATA_t	*BCD_time,	/* struct型BCD時間 */
UDWORD		long_time)	/* long型時間 */
{
	WORD	i;
	WORD	j;
	UDWORD	u;
	UDWORD	v;
	UDWORD	w;

	BCD_time->Second = CMN_DecimalToBCD((UBYTE)(long_time % 60));
	u = long_time / 60;

	BCD_time->Minute = CMN_DecimalToBCD((UBYTE)(u % 60));
	u /= 60;

	BCD_time->Hour = CMN_DecimalToBCD((UBYTE)(u % 24));
	u /= 24;

	switch (u % 7) {
	case 0:
	case 1:
	case 2:
	case 3:
		BCD_time->Week = (UBYTE)(u % 7 + 4);
		break;
	case 4:
	case 5:
	case 6:
		BCD_time->Week = (UBYTE)(u % 7 - 3);
	}

	j = 0;
	i = 92;
	v = 366;
	w = 0;
	while (u >= v)  {
		i++;
		w = v;
		v += 365;
		j = i % 4;
		if (j == 0) {
			v++;
		}
	}
	if (i >= 100) {
		i -= 100;
	}
	BCD_time->Year = CMN_DecimalToBCD((UBYTE)i);

	i = (WORD)(u - w);
	if (i < 31)  {
		BCD_time->Month = 1;
		BCD_time->Date = CMN_DecimalToBCD((UBYTE)(i + 1));
		return;
	}
	i -= 31;
	if ((j == 0 && i < 29) || (j != 0 && i < 28))  {
		BCD_time->Month = 0x02;
		BCD_time->Date = CMN_DecimalToBCD((UBYTE)(i + 1));
		return;
	}
	if (j == 0) {
		i -= 29;
	}
	else {
		i -= 28;
	}
	if (i < 31)  {
		BCD_time->Month = 0x03;
		BCD_time->Date = CMN_DecimalToBCD((UBYTE)(i + 1));
		return;
	}
	i -= 31;
	if (i < 30)  {
		BCD_time->Month = 0x04;
		BCD_time->Date = CMN_DecimalToBCD((UBYTE)(i + 1));
		return;
	}
	i -= 30;
	if (i < 31)  {
		BCD_time->Month = 0x05;
		BCD_time->Date = CMN_DecimalToBCD((UBYTE)(i + 1));
		return;
	}
	i -= 31;
	if (i < 30)  {
		BCD_time->Month = 0x06;
		BCD_time->Date = CMN_DecimalToBCD((UBYTE)(i + 1));
		return;
	}
	i -= 30;
	if (i < 31)  {
		BCD_time->Month = 0x07;
		BCD_time->Date = CMN_DecimalToBCD((UBYTE)(i + 1));
		return;
	}
	i -= 31;
	if (i < 31)  {
		BCD_time->Month = 0x08;
		BCD_time->Date = CMN_DecimalToBCD((UBYTE)(i + 1));
		return;
	}
	i -= 31;
	if (i < 30)  {
		BCD_time->Month = 0x09;
		BCD_time->Date = CMN_DecimalToBCD((UBYTE)(i + 1));
		return;
	}
	i -= 30;
	if (i < 31)  {
		BCD_time->Month = 0x10;
		BCD_time->Date = CMN_DecimalToBCD((UBYTE)(i + 1));
		return;
	}
	i -= 31;
	if (i < 30)  {
		BCD_time->Month = 0x11;
		BCD_time->Date = CMN_DecimalToBCD((UBYTE)(i + 1));
		return;
	}
	i -= 30;
	BCD_time->Month = 0x12;
	BCD_time->Date = CMN_DecimalToBCD((UBYTE)(i + 1));
	return;
}

/*************************************************************************
	module		:[10進数をBCDに変換]
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
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_DecimalToBCD(UBYTE decimal)	/* 変換前10進数 */
{
	return((UBYTE)((decimal / 10) * 16 + (decimal % 10)));
}

/*************************************************************************
	module		:[2桁BCDを2桁アスキー列に変換]
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
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_BCD_To2ASC_String(
UBYTE	*ASC_ptr,		/* 変換後アドレス */
UBYTE	BCD,			/* 変換前BCD */
UBYTE	pad_data)		/* 上位桁0データを置き換える文字 */
{
	if ((BCD & 0x0F) == 0x0F) {
		ASC_ptr[0] = pad_data;
		ASC_ptr[1] = (UBYTE)((BCD >> 4) + '0');
	}
	else if ((BCD & 0xF0) == 0x00) {
		ASC_ptr[0] = pad_data;
		ASC_ptr[1] = (UBYTE)((BCD & 0x0F)  + '0');
	}
	else {
		ASC_ptr[0] = (UBYTE)((BCD >> 4) + '0');
		ASC_ptr[1] = (UBYTE)((BCD & 0x0F) + '0');
	}
}

/*************************************************************************
	module		:[10進数を16進数に変換]
	function	:[
		1.
	]
	return		:[変換後16進数]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_DecimalToHex(UBYTE decimal)	/* 変換前10進数 */
{
	if (decimal < 10) {
		return ((UBYTE)(decimal + '0'));
	}
	else {
		return ((UBYTE)(decimal + 'A' - 10));
	}
}

/*************************************************************************
	module		:[ワンタッチの配列オフセット値をコードに変換]
	function	:[
		1.
	]
	return		:[ワンタッチコード]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/10]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_OffsetToOnetouchCode(UBYTE one_pos)	/* 配列オフセット値 */
{
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/*#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_SAKAKI) || (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_SAKAKI) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)			/* Add by Y.Kano 2003/07/11 */
	return(OnetouchTable[one_pos]);
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_H)
	/** ICHOU変更 -- めくりキーのシート状態を見る */
	/* 裏面 */
	if ((one_pos >= 40) && (one_pos <= 71)) {
		return((UBYTE)(OnetouchTable[(UBYTE)(one_pos - 40)] + 40));
	}
	/* 表面 */
	else {
		return(OnetouchTable[one_pos]);
	}
#endif
}

/*************************************************************************
	module		:[ワンタッチコードを配列オフセット値に変換]
	function	:[
		1.
	]
	return		:[ワンタッチダイヤルの配列オフセット値]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/10]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_OnetouchCodeToOffset(UBYTE onetouch)	/* ワンタッチコード */
{
	UBYTE i;

	for (i = 0; i < SYS_2ND_ONETOUCH_MAX + SYS_ONETOUCH_MAX; i++) {
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/*#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_SAKAKI) || (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_SAKAKI) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)			/* Add by Y.Kano 2003/07/11 */
		if (onetouch == OnetouchTable[i]) {
			return(i);
		}
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_H)
		/* ICHOUのCMN_DATA.Cよりコピー By O.Kimoto 1997/07/16 */
		if (onetouch == OnetouchTable[i]) {
			/** ICHOU変更 -- めくりキーのシート状態を見る */
			switch (OnetouchSheetStatus) {	/** 常にシート状態を監視しているタスク(opr_keyの中)がセットしている変数 */
			case ONETOUCH_SHEET0:	/** 表面 */
				return(i);

			case ONETOUCH_SHEET1:	/** 裏面 */
				return((unsigned char)(i + 40));

			default:
				return(i);
			}
		}
#endif
	}
}

/*************************************************************************
	module		:[ＢＣＤ形式のダイアルデータをＡＳＣ形式に変換]
	function	:[
		1.ＢＣＤ形式のダイアル文字列を指定された文字数（ASCの文字）分ＡＳＣ形式に変換。
		2.指定された文字数分あるいは終了コードが検出された時点で終了
		3.終了コードはNULLに変換しないー＞NULLはセットしない
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
	date		:[1995/09/01]
	author		:[江口]
*************************************************************************/
void	CMN_BCD_ToASC_StringNum(
UBYTE	*ASC_String,		/** コピー先のバッファ（ASC）の先頭アドレス*/
UBYTE	*BCD_String,		/** コピー元文字列（BCD)の先頭アドレス */
UBYTE	ASC_Count)			/** コピーされる文字数(ASC) */
{
	UBYTE even; /* コピー先のコピー位置が偶数位置か奇数位置か*/
						/* 0:奇数, 1:偶数 */
	UBYTE bcd_data;

	even = 1; /* 初期化：ASC_String[0]から始まるので偶数にしておく*/

	for ( ;ASC_Count > 0; ASC_Count--) {
		if (even) {	/* 偶数 */
			bcd_data = (UBYTE)((*BCD_String & 0xF0) >> 4); /* 上位４ビットを変換 */
		}
		else {	/* 奇数 */
			bcd_data = (*BCD_String & 0x0F); /* 下位４ビットを変換 */
			BCD_String++; /* 進めておく */
		}
		if (bcd_data == 0x0F) { /* 終了コード */
			return;
		}
		*ASC_String++ = CMN_BCD_ToASC(bcd_data);
		even ^= 0x01; /* 奇数偶数を反転*/
	}
}

/*************************************************************************
	module		:[ＡＳＣ形式のダイアル文字列をＢＣＤ形式に変換]
	function	:[
		1.  ＡＳＣ形式のダイアル文字列を指定文字数分、ＢＣＤ文字列に変換。
		2． 指定文字列分変換するまであるいは終了文字（ＮＵＬＬ）が検出されるまで変換
		3.	終了文字（ＮＵＬＬ）は変換しない。
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
	date		:[1995/09/01]
	author		:[江口]
*************************************************************************/
void	CMN_ASC_ToBCD_StringNum(
UBYTE	*BCD_String,		/** コピー先のバッファ(BCD)の先頭アドレス */
UBYTE	*ASC_String,		/** コピー元の文字列(ASC)の先頭アドレス  */
UBYTE	ASC_Count)			/** コピー文字数(ASC) */
{
	UBYTE	even;		/* 読み出し位置が奇数位置か偶数位置かを保持*/
						/* 0:奇数,1:偶数 */

	even = 1;

	for (; ASC_Count > 0; ASC_Count--) {
		if (*ASC_String == NULL) {
			return;
		}
		if (even) { /* 偶数 */
			*BCD_String &= 0x0F;
			*BCD_String |= CMN_ASC_ToBCD((UBYTE)(*ASC_String)) << 4;
		}
		else { /* 奇数 */
			*BCD_String &= 0xF0;
			*BCD_String |= CMN_ASC_ToBCD((UBYTE)(*ASC_String));
			BCD_String++;
		}
		even ^= 0x01;
		ASC_String++;
	}
}

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

#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 移植 by SMuratec L.Z.W 2003/08/13 */
#if (PRO_JIS_CODE == ENABLE)
/*************************************************************************
	module		:[JISコードからシフトJISコードへの変換]
	function	:[
		1.JISコード（第１・第２水準）をシフトJISコードに変換します
	]
	return		:[シフトJISコード]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[CMN]
	date		:[1994/09/16]
	auther		:[石橋正和]
*************************************************************************/
UWORD CMN_JIS_ToShiftJIS(CONST UWORD jis_code)	/* JISコード */
{
	UWORD	s_jis_high_byte;	/* シフトJISコードの上位バイト */
	UWORD	s_jis_low_byte;		/* シフトJISコードの下位バイト */

	s_jis_high_byte = (jis_code >> 8) & 0x00FF;
	s_jis_low_byte = jis_code & 0x00FF;

	if (s_jis_high_byte & 1) {
		s_jis_low_byte += 0x001F;
	}
	else {
		s_jis_low_byte += 0x007D;
	}

	s_jis_high_byte = (s_jis_high_byte - 0x0021 >> 1) + 0x0081;

	if (s_jis_low_byte >= 0x007F) {
		s_jis_low_byte++;
	}
	if (s_jis_high_byte > 0x009F) {
		s_jis_high_byte += 0x0040;
	}

	return ((s_jis_high_byte << 8) | s_jis_low_byte);
}

/*************************************************************************
	module		:[シフトJISコードからJISコードへの変換]
	function	:[
		1.シフトJISコードをJISコード（第１・第２水準）に変換します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[CMN]
	date		:[1994/01/24]
	auther		:[石橋正和,渡辺一章]
*************************************************************************/
void CMN_ShiftJIS_ToJIS(UWORD *high_byte,	/* シフトJISコードの上位バイト(JISコードに変換) */
						UWORD *low_byte)	/* シフトJISコードの下位バイト(JISコードに変換) */
{
	/* 上位バイトの処理 */
	if (*high_byte <= 0x9f) {
		*high_byte -= 0x71;
	}
	else {
		*high_byte -= 0xb1;
	}
	*high_byte = *high_byte * 2 + 1;

	/* 下位バイトの処理 */
	if (*low_byte > 0x7f) {
		(*low_byte)--;
	}
	if (*low_byte >= 0x9e) {
		*low_byte -= 0x7d;
		(*high_byte)++;
	}
	else {
		*low_byte -= 0x1f;
	}
}

/*************************************************************************
	module		:[シフトJISコードからASCII列の区点コードへの変換]
	function	:[
		1.シフトJISコードを、ASCII文字列の４桁の区点コードに変換します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		区点コード＝JISコードの上位・下位バイトからそれぞれ20hを引いた値を
					それぞれ10進数に直して合わせた値
	]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[CMN]
	date		:[2001/04/04]
	auther		:[渡辺一章]
*************************************************************************/
void CMN_ShiftJIS_ToASC_KUTEN_Code(UWORD *high_byte,	/* シフトJISコードの上位バイト(JISコードに変換) */
								   UWORD *low_byte,		/* シフトJISコードの下位バイト(JISコードに変換) */
								   UBYTE *asc_buf_ptr)	/* 区点コード格納用バッファ */
{
	/* データの流れ
	** 例）亜（シフトJISコード＝889Fh、JISコード＝3021h、区点コード＝1601）
	** 88h, 9Fh								：引数
	**                   ↓
	** 88h → 30h, 9Fh → 21h				：シフトJISコードを、JISコードに変換
	**                   ↓
	** 30h → 10h, 21h → 01h				：JISコードを16進の区点コードに変換
	**                   ↓
	** 10h → "16", 01h → "01"				：16進の区点コードをASCIIに変換
	** "1601"								：ASCII列の区点コードの完成
	*/

	/* シフトJISコードをJISコードに変換 */
	CMN_ShiftJIS_ToJIS(high_byte, low_byte);

	/* JISコードから区点コードに変換 */
	*high_byte -= 0x20;
	*low_byte -= 0x20;

	/* 16進の区点コードを10進のASCIIに変換 */
	CMN_UnsignedIntToASC(asc_buf_ptr, *high_byte, 2, '0');
	CMN_UnsignedIntToASC(asc_buf_ptr + 2, *low_byte, 2, '0');
}

/*************************************************************************
	module		:[ASCII列の区点コードをJISコードに変換]
	function	:[
		1.ASCII文字列の４桁の区点コードを、JISコードに変換します
	]
	return		:[JISコード]
	common		:[]
	condition	:[引数のバッファには４桁の数字が入っている事]
	comment		:[
		区点コード＝JISコードの上位・下位バイトからそれぞれ20hを引いた値を
					それぞれ10進数に直して合わせた値
	]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[CMN]
	date		:[2001/04/04]
	auther		:[渡辺一章]
*************************************************************************/
UWORD CMN_ASC_KUTEN_CodeToJIS(CONST UBYTE *asc_buf_ptr)	/* 区点コード格納バッファ */
{
	UWORD	jis_code;

	/* データの流れ
	** 例）亜（区点コード＝1601、JISコード＝3021h）
	** "1601"								：引数
	**                   ↓
	** "16" → 10h + 20h → 30h → 3000h	：区（最初の２桁）を１６進数に変換し、20Hを加算
	** "01" → 01h + 20h → 21h				：点（最後の２桁）を１６進数に変換し、20Hを加算
	** 3000h + 21h → 3021h					：戻り値（区＋点の計算）
	*/

	/* 区をJISの上位バイトに変換 */
	jis_code = (CMN_ASC_ToUnsignedInt(asc_buf_ptr, 2) + 0x20) << 8;

	/* 点をJISの下位バイトに変換 */
	jis_code += (CMN_ASC_ToUnsignedInt(asc_buf_ptr + 2, 2) + 0x20);

	return (jis_code);
}
#endif	/* (PRO_JIS_CODE == ENABLE) */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) */
