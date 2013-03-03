/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_LCD.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ＬＣＤドライバーモジュール
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\font_def.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#if (PRO_MODEM == ORANGE3)	/* Add By H.Fujimura 1998/12/28 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#endif
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\font_tbl.h"
#include	"\src\atlanta\ext_v\sys_port.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#if (PRO_OKI == ENABLE)	/* by K.Watanabe 1999/02/09 */
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#endif

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\sh_port.h"
#include	"\src\atlanta\sh7043\ext_v\extv_sem.h"
#endif

#if (PRO_ANK_TO_KANJI == ENABLE)	/* by K.Watanabe 1999/06/15 */
#include	"\src\atlanta\ext_v\cg_rom.h"
#include	"\src\atlanta\ext_v\lst_tbl.h"
#endif

/*
#if (PRO_KEYPANEL != PANEL_HINOKI)
 #if (PRO_ANK_TO_KANJI == ENABLE)
void	LCD_RegisterSet(UDWORD, UBYTE);
void	LCD_Initialize(void);
void	ClearByteCharacterDotPattern(UBYTE, UBYTE);
void	DisplayString(UBYTE, UBYTE *);
void	DisplayString0(UBYTE *);
void	DisplayString1(UBYTE *);
void	DisplayString2(UBYTE *);
void	DisplayString3(UBYTE *);
void	DisplayStringWithRightSpace0(UBYTE *);
void	DisplayStringWithRightSpace1(UBYTE *);
void	DisplayStringWithoutLeftSpace(UBYTE, UBYTE *);
void	DisplayBlinkString(UBYTE, UBYTE *);
void	NormalString(UBYTE, UBYTE);
void	BlinkString(UBYTE, UBYTE);
void	ClearString(UBYTE, UBYTE);
void	ClearString0(void);
void	ClearString1(void);
void	ClearString2(void);
void	ClearString3(void);
void	ClearDisplay(void);
void	ContinuouslyClearString(UBYTE, UBYTE);
void	ReverseChar(UBYTE);
void	NormalChar(UBYTE);
void	ClearChar(UBYTE);
void	DisplayShiftJIS(UBYTE, UWORD);
void	PagingON_ForInputJapanese(void);
void	PagingOFF(void);
UBYTE	CheckFontJIS2(UWORD, UWORD);
void	GetByteCharacterDotPattern(UBYTE, UBYTE, UBYTE, UWORD);
void	GetWordCharacterDotPattern(UBYTE, UBYTE, UBYTE, UBYTE, UWORD);
void	GetPictureFontDotPattern(UBYTE, UBYTE, UBYTE, UWORD);
void	Get2ndWordCharacterDotPattern(UBYTE, UBYTE, UBYTE, UBYTE, UWORD);
void	DisplayStringAttribute(UBYTE, UBYTE *, UWORD);
void	DisplayStringToProperPosition(UBYTE, UBYTE, UBYTE *);
void	ChangeCharacterAttribute(UBYTE, UWORD);
void	DisplayStringWithRightSpace(UBYTE, UBYTE *);
void	ChangeStringAttribute(UBYTE, UBYTE, UWORD);
void	DisplayCursorON(UBYTE);
void	DisplayCursorOFF(void);
 #else	/ (PRO_ANK_TO_KANJI == DISABLE) /
void	LCD_SoftWearTimer(UWORD);
void	LCD_WriteInstruction(UBYTE);
void	LCD_BusyFlagWait(UWORD);
void	LCD_WriteData(UBYTE);
void	WriteCGRAM(UBYTE *);
void	LCD_Initialize(void);
void	InitializeCGRAM_Data(void);
UBYTE	CheckSpecialCharacter(UBYTE);
void	CheckChangeCGRAM(UBYTE *);
 #endif	/ (PRO_ANK_TO_KANJI == ENABLE) /
void	DisplayStringHigh(UBYTE, UBYTE *);
void	DisplayStringLow(UBYTE, UBYTE *);
void	CursorOn(UBYTE);
void	CursorOff(void);
void	DisplayChar(UBYTE, UBYTE);
void	ClearDisplayHigh(void);
void	ClearDisplayLow(void);
void	DisplayFlashStringHigh(UBYTE, UBYTE *);
void	DisplayFlashStringLow(UBYTE, UBYTE *);
void	DisplayAllBlack(void);
#endif	/ (PRO_KEYPANEL != PANEL_HINOKI) /
#if (PRO_JIS_CODE == ENABLE)
UWORD	JIS_ToShiftJIS(UWORD);
void	ShiftJIS_ToJIS(UWORD *, UWORD *);
UBYTE	GetFontAddress(UDWORD *, UWORD, UWORD);
UBYTE	CheckJIS1Code(UWORD);
UBYTE	CheckFontJIS2Code(UWORD);
UBYTE	CheckShiftJISCode(UBYTE, UBYTE);
#endif
*/


#if (PRO_KEYPANEL != PANEL_HINOKI) && (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2)	/* ＨＩＮＯＫＩ タイプ *//* 1998/09/21 by T.Soneoka */
 #if (PRO_ANK_TO_KANJI == ENABLE)	/* by K.Watanabe 1999/06/15 */
/*************************************************************************
	module		:[LCTCのレジスタのセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  LCD_RegisterSet(
		UDWORD address,	/* セットするレジスタのアドレス */
		UBYTE data)		/* セットするデータ */
{
	outp(address, data);
}

/*************************************************************************
	module		:[LCD表示の初期設定]
	function	:[
		1.フレームバッファのアドレスを指定する
		2.LCTCを1RAMグラフィックに設定する
		3.LCTCをリセットする
		4.全画面クリア
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/05/13]
	auther		:[石橋正和]
*************************************************************************/
void  LCD_Initialize(void)
{
	/** ＶＲＡＭ のアドレスを指定 */
	LCD_Display = (UBYTE *)&LCD_PageRAM[0];

	/** LCTCの内部レジスタの初期設定 */
	LCD_RegisterSet( LCTC_REG1, 0x18);						/* R1: モードレジスタ（1/8分周に設定) */
	LCD_RegisterSet( LCTC_REG2, LCD_WIDTH );				/* R2: 水平表示文字数 */
	LCD_RegisterSet( LCTC_REG3, 64 );						/* R3: 水平同期パルス幅 */
	LCD_RegisterSet( LCTC_REG4, 2 );						/* R4: サイクルスチールイネーブル幅 */
	LCD_RegisterSet( LCTC_REG5, LCD_HEIGHT*LCD_DOT_LINE );	/* R5: 垂直ライン数 */
	LCD_RegisterSet( LCTC_REG6, 0 );						/* R6: 表示開始アドレス（下位）*/
	LCD_RegisterSet( LCTC_REG7, 0 );						/* R7: 表示開始アドレス（上位）*/
	LCD_RegisterSet( LCTC_REG8, 0 );						/* R8: Ｍ出力周期可変レジスタ */

	/** ＶＲＡＭのクリア */
	ClearDisplay();

	/** LCD表示開始 */
	LCD_RegisterSet( LCTC_REG1, 0x1c );
}

/*************************************************************************
	module		:[フレームバッファ内の半角1文字分のドットパターンとアトリビュートをクリア]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  ClearByteCharacterDotPattern(
		UBYTE xc,		/* LCD上の半角文字のx座標(0～29) */
		UBYTE yc)		/* LCD上の半角文字のy座標(0～3)  */
{
	UWORD  voffset;	/* ＶＲＡＭの転送位置 */
	UWORD * putptr;
	UWORD  vrambit;
	UBYTE line;

	voffset = yc * LCD_DOT_LINE * LCD_WIDTH + xc;

	if( voffset & 1 ) {		/** 奇数バイトの時 */
		voffset &= 0xfffe;	/** アドレスをワード境界に合わせる */
		for (line = 0; line < 16; line++) { /** 16ライン分ループ */
			putptr = (UWORD *)(LCD_Display + voffset + (line * LCD_WIDTH));
			vrambit = *putptr;
			*putptr = (UWORD)(vrambit & 0x00ff);
		}
	} else {
		for (line = 0; line < 16; line++) { /** 16ライン分ループ */
			putptr = (UWORD *)(LCD_Display + voffset + (line * LCD_WIDTH));
			vrambit = *putptr;
			*putptr = (UWORD)(vrambit & 0x0ff00);
		}
	}

	/** 仮想フレームバッファの更新 */
	LCD_VirtualFrameBuffer[yc][xc] = ' ';
}

/*************************************************************************
	module		:[任意の位置にストリングを出力]
	function	:[
		1.ストリングがLCDの最右端を越える場合は、以下を表示しない
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  DisplayString(
        UBYTE dsp_pos,		/* 表示する位置(0～119) */
        UBYTE *string)	/* 入力するストリング   */
{
	DisplayStringAttribute(dsp_pos, string, ATTRIBUTE_NORMAL);
}

/*************************************************************************
	module		:[1段目にストリングを出力]
	function	:[
		1.ストリングがLCDの最右端を越える場合は、以下を表示しない
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  DisplayString0(
		UBYTE *string)	/* 表示するストリング */
{
	DisplayStringAttribute((UBYTE)0, string, ATTRIBUTE_NORMAL);
}

/*************************************************************************
	module		:[2段目にストリングを出力]
	function	:[
		1.ストリングがLCDの最右端を越える場合は、以下を表示しない
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  DisplayString1(
		UBYTE *string)	/* 表示するストリング */
{
	DisplayStringAttribute((UBYTE)30, string, ATTRIBUTE_NORMAL);
}

/*************************************************************************
	module		:[3段目にストリングを出力]
	function	:[
		1.ストリングがLCDの最右端を越える場合は、以下を表示しない
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  DisplayString2(
		UBYTE *string)	/* 入力するストリング */
{
	DisplayStringAttribute((UBYTE)60, string, ATTRIBUTE_NORMAL);
}

/*************************************************************************
	module		:[4段目にストリングを出力]
	function	:[
		1.ストリングがLCDの最右端を越える場合は、以下を表示しない
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1999/06/16]
	auther		:[渡辺一章]
*************************************************************************/
void  DisplayString3(
		UBYTE *string)	/* 入力するストリング */
{
	DisplayStringAttribute((UBYTE)90, string, ATTRIBUTE_NORMAL);
}

/*************************************************************************
	module		:[1段目に右の余白をクリアしてストリングを出力]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/06/09]
	auther		:[石橋正和]
*************************************************************************/
void  DisplayStringWithRightSpace0(
		UBYTE *string)		/* 表示するストリング */
{
	DisplayStringWithRightSpace(0, string);
}

/*************************************************************************
	module		:[2段目に右の余白をクリアしてストリングを出力]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/06/09]
	auther		:[石橋正和]
*************************************************************************/
void  DisplayStringWithRightSpace1(
		UBYTE *string)		/* 表示するストリング */
{
	DisplayStringWithRightSpace(30, string);
}

/*************************************************************************
	module		:[任意の位置に左に空白を作らずにストリングを出力]
	function	:[
		1.ストリングの先頭に半角スペースがあれば、それは表示しない
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/05/24]
	auther		:[石橋正和]
*************************************************************************/
void  DisplayStringWithoutLeftSpace(
		UBYTE	pos,		/* 表示する位置   */
		UBYTE	*string)	/* 表示するストリング */
{

	/* 本来はこんな所でワーディングアドレスを変換する必要はないのですが
	** ＩＣＨＯＵのプログラムを流用するため、暫定的に処理します
	** 実際に表示するときはＬＣＤドライバーの方で行います。
	** By O.Kimoto 1997/10/10
	*/
	string = CalculateStringAddress(string);

	while (*string == ' ') {
		string++;
	}

	DisplayString(pos, string);
}

/*************************************************************************
	module		:[任意の位置にストリングを点滅させて表示]
	function	:[
		1.ストリングがLCDの最右端を越える場合は、以下を表示しない
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  DisplayBlinkString(
		UBYTE	dsp_pos,	/* 表示する位置(0～119) */
		UBYTE	*string)	/* 表示するストリング   */
{
	DisplayStringAttribute(dsp_pos, string, ATTRIBUTE_BLINK);
}

/*************************************************************************
	module		:[既にある文字を任意の位置から指定文字数を通常表示]
	function	:[
		1.文字数がLCDの最右端を越える場合は、以下を処理しない
		2.既に通常表示していればそのまま
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/05/13]
	auther		:[石橋正和]
*************************************************************************/
void  NormalString(
		UBYTE pos,		/* 反転する位置(0～119)  */
		UBYTE rvs_cnt)	/* 反転する文字数(1～30) */
{
	ChangeStringAttribute(pos, rvs_cnt, ATTRIBUTE_NORMAL);
}

/*************************************************************************
	module		:[既にある文字を任意の位置から指定文字数を点滅させる]
	function	:[
		1.文字数がLCDの最右端を越える場合は、以下を処理しない
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  BlinkString(
		UBYTE pos,			/* 点滅する位置(0～119)  */
		UBYTE blink_cnt)	/* 点滅する文字数(1～30) */
{
	ChangeStringAttribute(pos, blink_cnt, ATTRIBUTE_BLINK);
}

/*************************************************************************
	module		:[任意の位置から指定文字数を消去]
	function	:[
		1.文字数がLCDの最右端を越える場合は、以下を処理しない
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  ClearString(
		UBYTE dsp_pos,	/* 消去する位置(0～119)  */
		UBYTE clr_cnt)	/* 消去する文字数(1～30) */
{
	UBYTE x0; /* x座標の初期値 */
	UBYTE xe; /* x座標の最終値 */
	UBYTE xc; /* x座標 */
	UBYTE yc; /* y座標 */

	if (dsp_pos >= LCD_TOTAL_CHARACTERS) {
		return; /** 位置が120以上なら何もしない */
	}

	yc = (UBYTE)(dsp_pos / LCD_WIDTH);
	x0 = (UBYTE)(dsp_pos % LCD_WIDTH);

	xe = (UBYTE)(x0 +clr_cnt -1);
	if (xe > (UBYTE)(LCD_WIDTH - 1)) {
		xe = (UBYTE)(LCD_WIDTH - 1);
	}

	for (xc = x0; xc <= xe; xc++) {
		ClearByteCharacterDotPattern(xc, yc);
	}
}

/*************************************************************************
	module		:[1段目を消去]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和、清水政貴]
*************************************************************************/
void  ClearString0(void)
{
	UWORD	count;
	UWORD	*lcd_buf_ptr;

	lcd_buf_ptr = (UWORD *)(LCD_Display + (0 * LCD_DOT_LINE * LCD_WIDTH));

	for (count = 0; count < ((LCD_DOT_LINE * LCD_WIDTH) / 2); count ++) {
		*(lcd_buf_ptr + count) = 0;
	}

	for (count = 0; count < LCD_WIDTH; count ++) {
		LCD_VirtualFrameBuffer[0][count] = 0x20;
	}
}

/*************************************************************************
	module		:[2段目を消去]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和、清水政貴]
*************************************************************************/
void  ClearString1(void)
{
	UWORD	count;
	UWORD	*lcd_buf_ptr;

	lcd_buf_ptr = (UWORD *)(LCD_Display + (1 * LCD_DOT_LINE * LCD_WIDTH));
	for (count = 0; count < ((LCD_DOT_LINE * LCD_WIDTH) / 2); count ++) {
		*(lcd_buf_ptr + count) = 0;
	}

	for (count = 0; count < LCD_WIDTH; count ++) {
		LCD_VirtualFrameBuffer[1][count] = 0x20;
	}
}

/*************************************************************************
	module		:[3段目を消去]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和、清水政貴]
*************************************************************************/
void  ClearString2(void)
{
	UWORD	count;
	UWORD	*lcd_buf_ptr;

	lcd_buf_ptr = (UWORD *)(LCD_Display + (2 * LCD_DOT_LINE * LCD_WIDTH));
	for (count = 0; count < ((LCD_DOT_LINE * LCD_WIDTH) / 2); count ++) {
		*(lcd_buf_ptr + count) = 0;
	}

	for (count = 0; count < LCD_WIDTH; count ++) {
		LCD_VirtualFrameBuffer[2][count] = 0x20;
	}
}

/*************************************************************************
	module		:[4段目を消去]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1999/06/16]
	auther		:[渡辺一章]
*************************************************************************/
void  ClearString3(void)
{
	UWORD	count;
	UWORD	*lcd_buf_ptr;

	lcd_buf_ptr = (UWORD *)(LCD_Display + (3 * LCD_DOT_LINE * LCD_WIDTH));
	for (count = 0; count < ((LCD_DOT_LINE * LCD_WIDTH) / 2); count ++) {
		*(lcd_buf_ptr + count) = 0;
	}

	for (count = 0; count < LCD_WIDTH; count ++) {
		LCD_VirtualFrameBuffer[3][count] = 0x20;
	}
}

/*************************************************************************
	module		:[全画面消去]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void	ClearDisplay(void)
{
	UWORD	count1;
	UWORD	count2;
	UWORD	*lcd_buf_ptr;

	lcd_buf_ptr = (UWORD *)(LCD_Display + (0 * LCD_DOT_LINE * LCD_WIDTH));

	for (count1 = 0; count1 < ((LCD_HEIGHT * LCD_DOT_LINE * LCD_WIDTH)/2); count1 ++) {
		*(lcd_buf_ptr + count1) = 0;
	}

	for (count1 = 0; count1 < LCD_HEIGHT; count1 ++) {
		for (count2 = 0; count2 < LCD_WIDTH; count2 ++) {
			LCD_VirtualFrameBuffer[count1][count2] = 0x20;
		}
	}
}

/*************************************************************************
	module		:[任意の位置から指定文字数を連続して消去]
	function	:[
		1.文字数が最右端を越える場合、次の行を続けて消去
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/05/25]
	auther		:[石橋正和]
*************************************************************************/
void  ContinuouslyClearString(
		UBYTE	pos,	/* 表示する位置(0～119) */
		UBYTE	cnt)	/* 消去する文字数       */
{
	UBYTE i;

	for (i = 0; i < cnt; i++) {
		ClearChar((UBYTE)(pos + i));
	}
}

/*************************************************************************
	module		:[任意の位置の文字を反転]
	function	:[
		1.既に反転していればそのまま
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  ReverseChar(
		UBYTE	pos)	/* 反転する位置(0～119) */
{
	ChangeCharacterAttribute(pos, ATTRIBUTE_REVERSE);
}

/*************************************************************************
	module		:[任意の位置の文字を通常表示にする]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  NormalChar(
		UBYTE	pos)	/* 反転する位置(0～119) */
{
	ChangeCharacterAttribute(pos, ATTRIBUTE_NORMAL);
}

/*************************************************************************
	module		:[任意の位置の文字を消去]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  ClearChar(
		UBYTE dsp_pos)	/* 消去する位置(0～119) */
{
	UBYTE xc; /* x座標 */
	UBYTE yc; /* y座標 */

	if (dsp_pos >= LCD_TOTAL_CHARACTERS) {
		return; /** 位置が120以上なら何もしない */
	}

	yc = (UBYTE)(dsp_pos/LCD_WIDTH);
	xc = (UBYTE)(dsp_pos%LCD_WIDTH);

	ClearByteCharacterDotPattern(xc, yc);
}

/*************************************************************************
	module		:[任意のシフトJISコードの全角文字を指定の位置に表示]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/05/25]
	auther		:[石橋正和]
*************************************************************************/
void  DisplayShiftJIS(
		UBYTE pos,			/* 表示する位置(0～118) */
		UWORD code)			/* シフトJISコード */
{
	UBYTE string[3];

	string[0] = (UBYTE)(code >> 8);
	string[1] = (UBYTE)(0x00FF & code);
	string[2] = '\0';

	DisplayString(pos, (UBYTE *)&string[0]);
}

/*************************************************************************
	module		:[日本語入力のためのLCDページング]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/05/25]
	auther		:[石橋正和]
*************************************************************************/
void  PagingON_ForInputJapanese(void)
{
	/** 次ページのアドレスを指定する */
	LCD_Display = (UBYTE *)&LCD_PageRAM[0] + LCTC_VRAM_1PAGE_SIZE;
	ClearDisplay(); /** 全画面クリア */

	/** ＬＣＤＣへアドレスを出力 */
	LCD_RegisterSet(LCTC_REG6, (LCTC_VRAM_1PAGE_SIZE  & 0xff) );
	LCD_RegisterSet(LCTC_REG7, (LCTC_VRAM_1PAGE_SIZE >> 8)    );
}

/*************************************************************************
	module		:[LCDページングオフ]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/05/25]
	auther		:[石橋正和]
*************************************************************************/
void  PagingOFF(void)
{
	LCD_Display = (UBYTE *)&LCD_PageRAM[0];	/** ＶＲＡＭアドレスを指定する */

	/** レジスタへアドレスを出力 */
	LCD_RegisterSet(LCTC_REG6, 0);
	LCD_RegisterSet(LCTC_REG7, 0);

	CursorPosition = LCD_WIDTH*3;
}

UBYTE CheckFontJIS2(UWORD high, UWORD low)
{
	UBYTE ret;
	UWORD code;	/* シフトＪＩＳコード 1998/10/08 By M.Kuwahara */

	ret = KANJI2_NONE;

	/* 引数のコードが、シフトJISのコードかを調べます */
	if (((high >= SHIFT_JIS_2_HIGH_MIN) && (high <= SHIFT_JIS_2_HIGH_MAX))
	 && ((low >= SHIFT_JIS_LOW_MIN) && (low <= SHIFT_JIS_LOW_MAX))) {
		ret = TRUE;
	}
	else {
		/* 第２水準なのに上記の範囲に入っていないコードを、ここでチェックします 1998/10/08 By M.Kuwahara */
		/* 対応文字：㈱㈲佛壺巖廣檜條	*/
		code = (UWORD)((high << 8) | low);
		if ((code == 0x878A) ||
			(code == 0x878B) ||
			((code >= 0x98C5) && (code <= 0x9E8A))) {
			ret = TRUE;
		}
	}

	return(ret);
}

/*************************************************************************
	module		:[半角1文字分のドットパターンとアトリビュートをフレームバッファに格納]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  GetByteCharacterDotPattern(
		UBYTE xc,		/* LCD上の半角文字のx座標(0～29) */
		UBYTE yc,		/* LCD上の半角文字のy座標(0～3)  */
		UBYTE ascii,	/* 半角ASCIIコード               */
		UWORD attr)		/* 文字のアトリビュート          */
{
	UWORD voffset;		/* ＶＲＡＭの転送位置 */
	UWORD vrambit;
	UWORD * putptr;
	UBYTE reverse;		/* アトリビュートをソフトウェアで行うための変数 */
	UBYTE line;

	reverse = 0;
	if( attr == ATTRIBUTE_REVERSE) {	/** アトリビュートが反転機能 */
     	reverse = 0xff;		/** ソフトウェア反転ビットＯＮ */
	}
	voffset = (yc * LCD_DOT_LINE * LCD_WIDTH + xc);

	/* ＰＩＮ対応 by O.Kimoto 1998/01/26 */
	if (ascii == OPR_PIN_MARK) {
		ascii = '*';
	}

	if( voffset & 1 ) {		/** 奇数バイトの書き込み */
		voffset &= 0xfffe;       	/** 転送位置をワード境界に合わせる */
		for (line = 0; line < 16; line++) {	/** １６ライン繰り替えす */
			putptr  = (UWORD *)(LCD_Display + voffset + (line * LCD_WIDTH));	/** フォントデータを書き込む */
			vrambit = *putptr;
			*putptr = (vrambit & 0x00ff) | (UWORD)(ByteFont[ascii][line] ^ reverse) << 8;
		}
	} else {
		for (line = 0; line < 16; line++) {	/** １６ライン繰り替えす */
			putptr  = (UWORD *)(LCD_Display + voffset + (line * LCD_WIDTH));	/** フォントデータを書き込む */
			vrambit = *putptr;
			*putptr = (vrambit & 0xff00) | (UWORD)(ByteFont[ascii][line] ^ reverse);
		}
	}

	/** 仮想フレームバッファへ出力 */
	LCD_VirtualFrameBuffer[yc][xc] = (attr & 0xff00) | ascii;
}

/*************************************************************************
	module		:[全角1文字分のドットパターンをフレームバッファに格納]
	function	:[
		1.CGのアドレスを算出
		2.16ライン分のドットパターンをフレームバッファに格納
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  GetWordCharacterDotPattern(
		UBYTE xc,	/* LCD上の半角文字のx座標(0～29) */
		UBYTE yc,	/* LCD上の半角文字のy座標(0～3)  */
		UBYTE high,	/* シフトJIS上位バイト           */
		UBYTE low,	/* シフトJIS下位バイト           */
		UWORD attr)	/* 文字のアトリビュート          */
{
	UDWORD	address;	/* CGの論理アドレス(セグメント:オフセット) */
	UWORD	offset;
	UWORD	voffset;	/* ＶＲＡＭの転送位置 */
	UWORD	vrambit;
	UWORD	*putptr;
	UBYTE	line;
	UBYTE	reverse;	/* アトリビュートをソフトウェアで行うための変数 */

	(void)GetFontAddress(&address, high, low);	/* CGからﾌｫﾝﾄﾃﾞｰﾀを取得する時(JIS第1水準) */

	reverse = 0;
	if( attr == ATTRIBUTE_REVERSE) {	/** アトリビュートが反転機能 */
     	reverse = 0x0ff;		/** ソフトウェア反転ビットを立てる */
	}
	voffset = (yc * LCD_DOT_LINE * LCD_WIDTH + xc);
	offset  = (UWORD)(address & 0xFFFF);

	if( voffset & 1 ) {		/** 転送先アドレスが奇数の時 */
		voffset &= 0xfffe;	/** アドレスをワード境界にする */
		for (line = 0; line < 16; ++line) {		/** １６ラインくり返し */
			putptr  = (UWORD *)(LCD_Display + voffset + (line * LCD_WIDTH));	/** フォントデータを書き込む */
			vrambit = *putptr;

			if (address & 0x10000L) {	/** ＣＧＲＯＭ１要求 */
				*putptr = (vrambit & 0x00ff) | (UWORD)(CG_ROM1[offset++] ^ reverse) << 8;
			}
			else {						/** ＣＧＲＯＭ０要求 */
				*putptr = (vrambit & 0x00ff) | (UWORD)(CG_ROM0[offset++] ^ reverse) << 8;
			}

			putptr++;
			vrambit = *putptr;

			if (address & 0x10000L) {	/** ＣＧＲＯＭ１要求 */
				*putptr = (vrambit & 0xff00) | CG_ROM1[offset++] ^ reverse;
			}
			else {						/** ＣＧＲＯＭ０要求 */
				*putptr = (vrambit & 0xff00) | CG_ROM0[offset++] ^ reverse;
			}
		}
	} else {
		for (line = 0; line < 16; ++line) {
			putptr  = (UWORD *)(LCD_Display + voffset + (line * LCD_WIDTH));	/** フォントデータを書き込む */

			if (address & 0x10000L) {	/** ＣＧＲＯＭ１要求 */
				*putptr = (CG_ROM1[offset] ^ reverse) | (UWORD)(CG_ROM1[offset + 1] ^ reverse) << 8;
			}
			else {						/** ＣＧＲＯＭ０要求 */
				*putptr = (CG_ROM0[offset] ^ reverse) | (UWORD)(CG_ROM0[offset + 1] ^ reverse) << 8;
			}

			offset += 2;
		}
	}

	/** 仮想フレームバッファへ出力 */
	LCD_VirtualFrameBuffer[yc][xc    ] = (attr & 0xff00) | high;
	LCD_VirtualFrameBuffer[yc][xc + 1] = (attr & 0xff00) | low;
}

/*************************************************************************
	module		:[全角1文字分の絵文字をフレームバッファへ転送する]
	function	:[
		1.アドレスを算出
		2.16ライン分のドットパターンをフレームバッファに格納
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1996/06/10]
	auther		:[清水 政貴]
*************************************************************************/
void  GetPictureFontDotPattern(
		UBYTE xc,	/* LCD上の半角文字のx座標(0～29) */
		UBYTE yc,	/* LCD上の半角文字のy座標(0～3)  */
		UBYTE no,	/* 絵文字番号 */
		UWORD attr)	/* 文字のアトリビュート          */
{
	UWORD	voffset;	/* ＶＲＡＭの転送位置 */
	UWORD	vrambit;
	UWORD	*putptr;
	UWORD	offset;
	UBYTE	line;
	UBYTE	reverse;	/* アトリビュートをソフトウェアで行うための変数 */

	reverse = 0;
	if( attr == ATTRIBUTE_REVERSE) {	/** アトリビュートが反転機能 */
     	reverse = 0xff;	/** ソフトウェア反転ビットを立てる */
	}
	voffset = (yc * LCD_DOT_LINE * LCD_WIDTH + xc);
	offset = 0;

	if( voffset & 1 ) {		/** 転送先アドレスが奇数の時 */
		voffset &= 0xfffe;	/** アドレスをワード境界にする */
		for (line = 0; line < 16; ++line) {		/** １６ラインくり返し */
			putptr  = (UWORD *)(LCD_Display + voffset + (line * LCD_WIDTH));	/** フォントデータを書き込む */
			vrambit = *putptr;
			*putptr = (vrambit & 0x00ff) | (UWORD)(LCD_PictureFontPattern[no][offset++] ^ reverse) << 8;
			putptr++;
			vrambit = *putptr;
			*putptr = (vrambit & 0xff00) | LCD_PictureFontPattern[no][offset++] ^ reverse;
		}
	} else {
		for (line = 0; line < 16; ++line) {		/** １６ラインくり返し */
			putptr  = (UWORD *)(LCD_Display + voffset + (line * LCD_WIDTH));	/** フォントデータを書き込む */
			*putptr = (UWORD)(LCD_PictureFontPattern[no][offset] ^ reverse) | (UWORD)(LCD_PictureFontPattern[no][offset + 1] ^ reverse) << 8;
			offset += 2;
		}
	}

	/** 仮想フレームバッファへ出力 */
	LCD_VirtualFrameBuffer[yc][xc    ] = (attr & 0xff00) | (LCD_PICFONT + no);
	LCD_VirtualFrameBuffer[yc][xc + 1] = (attr & 0xff00) | (LCD_PICFONT_LOWER);
}

/*************************************************************************
	module		:[全角1文字分のドットパターンをフレームバッファに格納]
	function	:[
		1.CGのアドレスを算出
		2.16ライン分のドットパターンをフレームバッファに格納
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  Get2ndWordCharacterDotPattern(
		UBYTE xc,	/* LCD上の半角文字のx座標(0～29) */
		UBYTE yc,	/* LCD上の半角文字のy座標(0～3)  */
		UBYTE high,	/* シフトJIS上位バイト           */
		UBYTE low,	/* シフトJIS下位バイト           */
		UWORD attr)	/* 文字のアトリビュート          */
{
	UDWORD	address;	/* CGの論理アドレス(セグメント:オフセット) */
	UWORD	offset;
	UWORD	voffset;	/* ＶＲＡＭの転送位置 */
	UWORD	vrambit;
	UWORD	*putptr;
	UBYTE	line;
	UBYTE	reverse;	/* アトリビュートをソフトウェアで行うための変数 */

	(void)GetFontAddress(&address, high, low);	/* CGからﾌｫﾝﾄﾃﾞｰﾀを取得する時(JIS第1水準) */

	reverse = 0;
	if( attr == ATTRIBUTE_REVERSE) {	/** アトリビュートが反転機能 */
     	reverse = 0x0ff;		/** ソフトウェア反転ビットを立てる */
	}
	voffset = (yc * LCD_DOT_LINE * LCD_WIDTH + xc);
	offset = 0;

	if( voffset & 1 ) {		/** 転送先アドレスが奇数の時 */
		voffset &= 0xfffe;	/** アドレスをワード境界にする */
		for (line = 0; line < 16; ++line) {		/** １６ラインくり返し */
			putptr  = (UWORD *)(LCD_Display + voffset + (line * LCD_WIDTH));	/** フォントデータを書き込む */
			vrambit = *putptr;
			*putptr = (vrambit & 0x00ff) | (UWORD)(Kanji2[address].FontData[offset++] ^ reverse) << 8;
			putptr++;
			vrambit = *putptr;
			*putptr = (vrambit & 0xff00) | Kanji2[address].FontData[offset++] ^ reverse;
		
		}
	} else {
		for (line = 0; line < 16; ++line) {
			putptr  = (UWORD *)(LCD_Display + voffset + (line * LCD_WIDTH));	/** フォントデータを書き込む */
			*putptr = (Kanji2[address].FontData[offset] ^ reverse) | (UWORD)(Kanji2[address].FontData[offset + 1] ^ reverse) << 8;
			offset += 2;
		}
	}

	/** 仮想フレームバッファへ出力 */
	LCD_VirtualFrameBuffer[yc][xc    ] = (attr & 0xff00) | high;
	LCD_VirtualFrameBuffer[yc][xc + 1] = (attr & 0xff00) | low;
}

/*************************************************************************
	module		:[任意の位置にアトリビュートを加えてストリングを出力]
	function	:[
		1.ストリングがLCDの最右端を越える場合は、以下を表示しない
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  DisplayStringAttribute(
		UBYTE	dsp_pos,	/* 表示する位置(0～119) */
		UBYTE	*string,	/* 入力するストリング   */
		UWORD	attr)		/* 文字のアトリビュート */
{
	UBYTE x0;        /* x座標の初期値 */
	UBYTE xc;        /* x座標 */
	UBYTE yc;        /* y座標 */
	UBYTE c;
	UBYTE c1;

	string = CalculateStringAddress(string);	/* マルチワーディングアドレス変換 By O.Kimoto 1997/09/18 */

	if (dsp_pos >= LCD_TOTAL_CHARACTERS) { /** 位置が120以上の場合 */
		return;              /** リターン */
	}
	yc = dsp_pos / LCD_WIDTH; /** 座標の算出 */
	x0 = dsp_pos % LCD_WIDTH;

	for (xc = x0; xc < LCD_WIDTH; xc++) { /** LCDの枠いっぱいに書き切るまでループ */
		c  = *(string + (xc - x0));
		c1 = *(string + (xc - x0) + 1);
		if (c == '\0') { /** NULLなら終了 */
			break;
		}

		if (c >= LCD_PICFONT && c1 == LCD_PICFONT_LOWER) {		/** 絵文字コードの場合 */
			if (xc == LCD_WIDTH - 1) { /** 枠の1つ手前の場合 */
				GetByteCharacterDotPattern(xc, yc, ' ', attr); /* 半角スペースを表示 */
				break; /** 終了 */
			}

			GetPictureFontDotPattern(xc, yc, (UBYTE)(c & 0xf), attr); /** 絵文字表示 */
			xc++; /** x座標を半角分進める */
			continue;
		}

		/* 第２水準対応 By O.Kimoto 1998/01/28 */
		if (CheckFontJIS2(c, c1)!= KANJI2_NONE) {
			if (xc == LCD_WIDTH - 1) { /** 枠の1つ手前の場合 */
				GetByteCharacterDotPattern(xc, yc, ' ', attr); /* 半角スペースを表示 */
				break; /** 終了 */
			}
			Get2ndWordCharacterDotPattern(xc, yc, c, *(string + (xc - x0 + 1)), attr); /** フレームバッファにドットパターンを格納 */
			xc++; /** x座標を半角分進める */
		}
		else if (c >= WORD_CHARACTER_MIN && c <= WORD_CHARACTER_MAX) { /** 全角の場合(第1水準) */
			if (xc == LCD_WIDTH - 1) { /** 枠の1つ手前の場合 */
				GetByteCharacterDotPattern(xc, yc, ' ', attr); /* 半角スペースを表示 */
				break; /** 終了 */
			}
			GetWordCharacterDotPattern(xc, yc, c, *(string + (xc - x0 + 1)), attr); /** フレームバッファにドットパターンを格納 */
			xc++; /** x座標を半角分進める */
		}
		else { /** 半角の場合 */
			GetByteCharacterDotPattern(xc, yc, c, attr); /** フレームバッファにドットパターンを格納 */
		}
	}
}

/*************************************************************************
	module		:[任意の位置に任意の位置までストリングを出力]
	function	:[
		1.ストリングが指定した位置、若しくは最右端を越える場合は、以下を表示しない
		2.指定した位置までにNULLがある場合は、以降指定した位置までクリアする
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/07/19]
	auther		:[石橋正和]
*************************************************************************/
void  DisplayStringToProperPosition(
		UBYTE	dsp_pos,	/* 表示する位置(0～119) */
		UBYTE	end_pos,	/* 表示を終了する位置(0～119) */
		UBYTE	*string)	/* 入力するストリング   */
{
	UBYTE x0;	/* x座標の初期値 */
	UBYTE xc;	/* x座標 */
	UBYTE yc;	/* y座標 */
	UBYTE xe;	/* 表示を終えるx座標 */
	UBYTE c;
	UBYTE c1;

	string = CalculateStringAddress(string);	/* マルチワーディングアドレス変換 By O.Kimoto 1997/09/18 */

	if (dsp_pos >= LCD_TOTAL_CHARACTERS || dsp_pos > end_pos) {
		return;
	}

	yc = (UBYTE)(dsp_pos/LCD_WIDTH); /** 座標の算出 */
	x0 = (UBYTE)(dsp_pos%LCD_WIDTH);

	if (end_pos > (UBYTE)(dsp_pos - x0 + LCD_WIDTH - 1)) { /** 右端を越える場合 */
		end_pos = (UBYTE)(dsp_pos - x0 + LCD_WIDTH - 1); /** 右端まで表示 */
	}

	xe = end_pos%LCD_WIDTH;

	for (xc = x0; xc <= xe; xc++) {
		c  = *(string + (xc - x0));
		c1 = *(string + (xc - x0) + 1);
		if (c == '\0') { /* NULLなら以降半角スペースを表示 */
			for (; xc <= xe; xc++) {
				GetByteCharacterDotPattern(xc, yc, ' ', ATTRIBUTE_NORMAL);
			}
			break;
		}

		if (c >= LCD_PICFONT && c1 == LCD_PICFONT_LOWER) {		/** 絵文字コードの場合 */
			if (xc == LCD_WIDTH - 1) { /** 枠の1つ手前の場合 */
				GetByteCharacterDotPattern(xc, yc, ' ', ATTRIBUTE_NORMAL); /* 半角スペースを表示 */
				break; /** 終了 */
			}
			GetPictureFontDotPattern(xc, yc, (UBYTE)(c & 0xf), ATTRIBUTE_NORMAL); /** 絵文字表示 */
			xc++; /** x座標を半角分進める */
			continue;
		}

		/* 第２水準対応 By O.Kimoto 1998/01/28 */
		if (CheckFontJIS2(c, c1)!= KANJI2_NONE) {
			if (xc == xe) { /** 端の1つ手前である場合 */
				GetByteCharacterDotPattern(xc, yc, ' ', ATTRIBUTE_NORMAL); /* 半角スペースを表示 */
				break; /** 終了 */
			}
			Get2ndWordCharacterDotPattern(xc, yc, c, *(string + (xc - x0 + 1)), ATTRIBUTE_NORMAL);
			xc++; /** x座標を半角分進める */
		}
		else if (c >= WORD_CHARACTER_MIN && c <= WORD_CHARACTER_MAX) { /** 全角の場合(第1水準) */
			if (xc == xe) { /** 端の1つ手前である場合 */
				GetByteCharacterDotPattern(xc, yc, ' ', ATTRIBUTE_NORMAL); /* 半角スペースを表示 */
				break; /** 終了 */
			}
			/** フレームバッファにアトリビュートとドットパターンを格納 */
			GetWordCharacterDotPattern(xc, yc, c, *(string + (xc - x0 + 1)), ATTRIBUTE_NORMAL);
			xc++; /** x座標を半角分進める */
		}
		else { /* 半角の場合 */
			/** フレームバッファにアトリビュートとドットパターンを格納 */
			GetByteCharacterDotPattern(xc, yc, c, ATTRIBUTE_NORMAL);
		}
	}
}

/*************************************************************************
	module		:[既に表示している半角1文字分のアトリビュートを変更]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  ChangeCharacterAttribute(
		UBYTE dsp_pos,	/* 文字の位置(0～119) */
		UWORD attr)		/* 文字のアトリビュート */
{
	UWORD  voffset;	/* ＶＲＡＭの転送位置 */
	UWORD * putptr;
	UWORD  vrambit;
	UBYTE xc;		/* LCD上の半角文字のx座標 */
	UBYTE yc;		/* LCD上の半角文字のy座標 */
	UBYTE line;

	if (dsp_pos >= LCD_TOTAL_CHARACTERS) {
		return;
	}

	yc = dsp_pos / LCD_WIDTH; /** 座標の算出 */
	xc = dsp_pos % LCD_WIDTH;

	voffset = yc * LCD_DOT_LINE * LCD_WIDTH + xc;
	if( attr == ATTRIBUTE_BLINK ) {	/** 点滅アトリビュートが指定された */
		return;		/** リターン */
	}

	if( attr != (LCD_VirtualFrameBuffer[yc][xc] | 0xff) ) {		/** アトリビュートが変更された */
		if( voffset & 1 ) {		/** 転送先アドレスが奇数の時 */
			voffset &= 0xfffe;	/** 転送アドレスをワード境界に合わせる */
			for (line = 0; line < 16; ++line) {
				putptr = (UWORD *)(LCD_Display + voffset + (line * LCD_WIDTH));
				vrambit = *putptr;
				*putptr = (UWORD)(vrambit ^0xff00);
			}
		} else {
			for (line = 0; line < 16; ++line) {
				putptr = (UWORD *)(LCD_Display + voffset + (line * LCD_WIDTH));
				vrambit = *putptr;
				*putptr = (UWORD)(vrambit ^0x00ff);
			}
		}

		/** アトリビュートの更新 */
		LCD_VirtualFrameBuffer[yc][xc] &= 0xff;
		LCD_VirtualFrameBuffer[yc][xc] |= attr & 0xff00;
	}
}

/*************************************************************************
	module		:[任意の位置に右の余白をクリアしてストリングを出力]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/06/09]
	auther		:[石橋正和]
*************************************************************************/
void  DisplayStringWithRightSpace(
		UBYTE	pos,		/* 表示する位置   */
		UBYTE	*string)	/* 表示するストリング */
{
	UBYTE	*str;
	UWORD	length;

	str = string;

	str = CalculateStringAddress(str);	/* マルチワーディングアドレス変換 By O.Kimoto 1997/11/17 */

	for (length = 0; *str++ != '\0'; length++) {
	}

	DisplayString(pos, string);

	if (pos%LCD_WIDTH + length < LCD_WIDTH) {
		ClearString((UBYTE)(pos + length), (UBYTE)(LCD_WIDTH - (pos % LCD_WIDTH + length)));
	}
}

/*************************************************************************
	module		:[既にある文字のアトリビュートを任意の位置から指定文字数を変更]
	function	:[
		1.文字数がLCDの最右端を越える場合は、以下を処理しない
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  ChangeStringAttribute(
		UBYTE pos,	/* 変更する位置(0～119)  */
		UBYTE cnt,	/* 変更する文字数(1～30) */
		UWORD attr)	/* 変更するアトリビュート */
{
	UBYTE pos0;		/* 反転する位置の初期値 */
	UBYTE pos_e;	/* 反転する位置の最終値 */

	if (pos >= LCD_TOTAL_CHARACTERS) {
		return; /** 位置が120以上なら何もしない */
	}

	pos0 = pos;
	pos_e = (UBYTE)(pos0 + cnt -1);
	if (pos_e > (UBYTE)(LCD_WIDTH * (pos0 / LCD_WIDTH + 1) - 1)) {
		pos_e = (UBYTE)(LCD_WIDTH * (pos0 / LCD_WIDTH + 1) - 1);
	}

	for (pos = pos0; pos <= pos_e; pos++) {
		ChangeCharacterAttribute(pos, attr); /** 文字のアトリビュートを変更 */
	}
}

/*************************************************************************
	module		:[任意の位置にカーソルを表示]
	function	:[
		1.文字と重なる場合は文字を反転
		2.前からあるカーソルは消去
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  DisplayCursorON(
		UBYTE position)	/* 表示するカーソルの位置(0～119) */
{
	UBYTE xc;		/* x座標 */
	UBYTE yc;		/* y座標 */
	UBYTE prtchr;	/* カーソルを表示する位置にあるキャラクタ */
	UBYTE prtchr2;	/* 第２水準対応 By O.Kimoto 1998/01/29 */
	UWORD  voffset;	/* カーソルを表示するＶＲＡＭアドレス */

	yc		= (UBYTE)(position / LCD_WIDTH);	/** 座標を算出 */
	xc		= (UBYTE)(position % LCD_WIDTH);
	voffset = yc * LCD_DOT_LINE * LCD_WIDTH + xc;	/** ＶＲＡＭアドレスを計算 */
	prtchr	= (UBYTE)(LCD_VirtualFrameBuffer[yc][xc] & 0x00ff);
	prtchr2	= (UBYTE)(LCD_VirtualFrameBuffer[yc][xc+1] & 0x00ff);	/* 第２水準対応 By O.Kimoto 1998/01/29 */

	DisplayCursorOFF(); /** 前のカーソルを消す */
	if (prtchr == ' ') { /** 空白部にカーソルを表示する場合 */
		if( voffset & 1 ) {
			*(UWORD *)( LCD_Display + voffset + (14*LCD_WIDTH) - 1) |= 0xff00;
		} else {
			*(UWORD *)( LCD_Display + voffset + (14*LCD_WIDTH)) |= 0x00ff;
		}
	}
	else { /** 文字上にカーソルを表示する場合 */
		ReverseChar(position); /** 文字を反転 */

		/* 第２水準対応 By O.Kimoto 1998/01/29 */
		if ((CheckFontJIS2(prtchr, prtchr2)!= KANJI2_NONE)
			|| ((prtchr >= WORD_CHARACTER_MIN) && (prtchr <= WORD_CHARACTER_MAX) || (prtchr >= LCD_PICFONT))) {
			/** 全角の場合(第1水準) 、絵文字の場合*/
			ReverseChar((UBYTE)(position + 1));
		}
	}
	CursorPosition = position;
}

/*************************************************************************
	module		:[カーソルを消す]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  DisplayCursorOFF(void)
{
	UBYTE xc;		/* x座標 */
	UBYTE yc;		/* y座標 */
	UBYTE prtchr;	/* カーソルを表示する位置にあるキャラクタ */
	UBYTE prtchr2;	/* 第２水準対応 By O.Kimoto 1998/01/29 */

	yc		= (UBYTE)(CursorPosition / LCD_WIDTH);	/** 座標を算出 */
	xc		= (UBYTE)(CursorPosition % LCD_WIDTH);
	prtchr	= (UBYTE)(LCD_VirtualFrameBuffer[yc][xc] & 0x00ff);
	prtchr2	= (UBYTE)(LCD_VirtualFrameBuffer[yc][xc+1] & 0x00ff);	/* 第２水準対応 By O.Kimoto 1998/01/29 */

	if (prtchr == (UWORD)' ') { /** 既にカーソルが空白部にあるかもしれない場合 */
		ClearChar(CursorPosition); /** 前のカーソルのある場所をクリア */
	}
	else { /** 既にカーソルが文字上にあるかもしれない場合 */
		NormalChar(CursorPosition); /** 前のカーソルのある場所を通常表示 */
		/* 第２水準対応 By O.Kimoto 1998/01/29 */
		if ((CheckFontJIS2(prtchr, prtchr2)!= KANJI2_NONE)
			|| ((prtchr >= WORD_CHARACTER_MIN) && (prtchr <= WORD_CHARACTER_MAX) || (prtchr >= LCD_PICFONT))) {
			/** 全角の場合(第1水準) */
			NormalChar((UBYTE)(CursorPosition + 1));
		}
	}
}

 #else	/* (PRO_ANK_TO_KANJI == DISABLE)	*/
/*************************************************************************
	module		:[ソフトウェアタイマー]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ループ１回あたりの処理時間は約３usec（V53エミュレータ実測値)]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/23]
	author		:[江口]
*************************************************************************/
void LCD_SoftWearTimer(UWORD time)
{
	while (time > 0) {
		time--;
	}
}

/*************************************************************************
	module		:[インストラクション発行]
	function	:[
		1.ＬＣＤコントローラにインストラクション（コマンド）を発行する。
	]
	return		:[]
	common		:[
		SYS_LCDC_PortStatus
		SYS_LCD_DataPortStatus
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/23]
	author		:[江口]
*************************************************************************/
void LCD_WriteInstruction(UBYTE instruction)
{
	/*--------------------------*/
	/*RS ->0:IR Registerを選択	*/
	/*R/W->0:Writeに設定		*/
	/*ENABLE->0					*/
	/*--------------------------*/
	SYS_LCDC_PortStatus &= ~(IO_BIT_RS | IO_BIT_R_W | IO_BIT_E);
	outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

	/*---------------------------*/
	/*ENABLE->1					 */
	/*ﾃﾞｰﾀ書き込み開始			 */
	/*---------------------------*/
	SYS_LCDC_PortStatus |= IO_BIT_E;
	outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

	/*---------------------------------------------------*/
	/*IR Registerにﾃﾞｰﾀ書き込み	    					 */
	/*---------------------------------------------------*/
	SYS_LCD_DataPortStatus = instruction;
	outpw(LCD_DATA_PORT, (UWORD)SYS_LCD_DataPortStatus);

	/*----------------------------*/
	/*ENABLE -> 0				  */
	/*ﾃﾞｰﾀ書き込み終了			  */
	/*LCDC内部動作開始(Busyｾｯﾄ)	  */
	/*----------------------------*/
	SYS_LCDC_PortStatus &= ~IO_BIT_E;
	outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);
}

/*************************************************************************
	module		:[ビジーフラグ待ち]
	function	:[
		1.ＬＣＤコントローラに内部処理終了を待ちます
	]
	return		:[]
	common		:[
		SYS_LCDC_PortStatus
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/27]
	author		:[江口]
*************************************************************************/
void LCD_BusyFlagWait(UWORD time)	/*ループ回数(待ち時間 500 or 200）*/
{
	UBYTE	busy;

	/*---------------------------*/
	/* RS 	  -> 0:IRﾚｼﾞｽﾀを選択 */
	/* R/W	  -> 1:Readに設定	 */
	/* ENABLE -> 0				 */
	/*---------------------------*/
	SYS_LCDC_PortStatus |= IO_BIT_R_W;					/* R/W    を 1(R) */
	SYS_LCDC_PortStatus &= ~(IO_BIT_RS | IO_BIT_E);		/* Enable を 0    */
														/* RS     を 0    */
	outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

	for ( ;time > 0; time--) {
		/*---------------------------*/
		/* ENABLE -> 1				 */
		/* ﾃﾞｰﾀ読み込み開始			 */
		/*---------------------------*/
		SYS_LCDC_PortStatus |= IO_BIT_E;
		outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

		LCD_SoftWearTimer(1);	/* 最低で220nsウェイトを置く By M.Tachibana 1997/05/12 */

		/*----------------------------*/
		/*ﾃﾞｰﾀ(BusyFlag)読み込み	  */
		/*----------------------------*/
		busy = (UBYTE)inpw(LCD_BUSY_PORT);

		/*----------------------------*/
		/*ENABLE -> 0				  */
		/*----------------------------*/
		SYS_LCDC_PortStatus &= ~IO_BIT_E;
		outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);
		LCD_SoftWearTimer(1);	/* 最低で220nsウェイトを置く By M.Kotani 1997/08/06 */
#if (PRO_KEYPANEL == PANEL_ANZU_L)		/* あんず＿Ｌタイプ */
		if (!(busy & IO_BIT_LCDBUSY)) {		/* Busyがこけている->内部処理終了 */
			return;
		}
#else
		if (busy & IO_BIT_LCDBUSY) {		/* Busyがこけている->内部処理終了 */
			return;
		}
#endif
	}

	/* E設 中西さんからの依頼 Busy Flag がこけない時LCDCをリセットする
	** リセットフラグを立てる。
	** MAN_AfterMessagecheck()内でLCD_Initialize()をコールする。
	** T.Nose 1997/12/01
	*/
	DEBUG_LCD_ResetFlag = 1; /* リセットフラグを立てる */
}

/*************************************************************************
	module		:[ＬＣＤデータ書き込み]
	function	:[
		1.CGRAM／DDRAMにデータを書き込む
	]
	return		:[]
	common		:[
		SYS_LCDC_PortStatus
		SYS_LCD_DataPortStatus
	]
	condition	:[]
	comment		:[
		CGRAM/DDRAMのどちらかを選択してからコールすること
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/23]
	author		:[江口]
*************************************************************************/
void LCD_WriteData(UBYTE data)
{
	/*-------------------------------*/
	/* RS 		-> 1:DRを選択		 */
	/* R/W	　　-> 0:Writeに設定	 */
	/* ENABLE   -> 0				 */
	/*-------------------------------*/
	SYS_LCDC_PortStatus |= IO_BIT_RS;					/* RS     を 1    *//*ﾃﾞｰﾀﾚｼﾞｽﾀを選択*/
	SYS_LCDC_PortStatus &= ~(IO_BIT_R_W | IO_BIT_E);	/* R/W    を 0(W) *//*WRITEに設定*/
														/* Enable を 0    */
	outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

	/*-------------------------------*/
	/* ENABLE -> 1					 */
	/* ﾃﾞｰﾀ書き込み開始			     */
	/* 書き込む所はDDRAM/CGRAM		 */
	/*-------------------------------*/
	SYS_LCDC_PortStatus |= IO_BIT_E;		/* Enable を 1 *//*WRITEのﾄﾘｶﾞ*/
	outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

	/*-------------------------------*/
	/* DR Registerへﾃﾞｰﾀ書き込み	 */
	/*-------------------------------*/
	SYS_LCD_DataPortStatus = data;
	outpw(LCD_DATA_PORT, (UWORD)SYS_LCD_DataPortStatus);

	/*-------------------------------*/
	/* ENABLE -> 0					 */
	/* ﾃﾞｰﾀ書き込み終了				 */
	/* LCDC内部動作開始(Busy Set)	 */
	/*-------------------------------*/
	SYS_LCDC_PortStatus &= ~IO_BIT_E;		/* Enable を 0 */
	outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);
}

/*************************************************************************
	module		:[ＣＧＲＡＭにイメージデータを書き込む]
	function	:[
		1.
	]
	return		:[なし]
	common		:[SYS_LCD_DataPortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口,渡辺一章]
*************************************************************************/
void WriteCGRAM(UBYTE *pointer)
{
	UBYTE	i;	/* ループ変数 */

	/* 書き込むＣＧＲＡＭが、現在書き込まれているＣＧＲＡＭと同じ時は、何もしません */
	if (pointer == OPR_Writed_CGRAM_Address) {
		return;
	}

	OPR_Writed_CGRAM_Address = pointer;

	/* CGRAMを選択 */
	LCD_WriteInstruction(LCD_CGRAM_ADDRESS);

	/* 内部処理が終了するまで、或いは次のコマンドを実行してもいいくらい十分時間が経過するまで待つ */
	LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	for (i = 0; i < LCD_CGRAM_WRITE_DATA_COUNT; i++) {	/* （１文字あたり８byte）×（８文字） */
		LCD_WriteData(*pointer);
		LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
		pointer++;
	}
}

/*************************************************************************
	module		:[ＬＣＤドライバ初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void LCD_Initialize(void)
{
	/** 15msec以上待つ */
/*	LCD_SoftWearTimer(7000);	@* 約19msec:Ｖ５３エミュレータ実測値 */
	LCD_SoftWearTimer(9000);	/* 約??msec:ＲＩＳＣエミュレータ実測値 */

	/** ファンクションセット */
	LCD_WriteInstruction(LCD_FUNCTION_SET);
	/** 4,1msec以上待つ */
/*	LCD_SoftWearTimer(2100);	@* 約6msec:Ｖ５３エミュレータ実測値 */
	LCD_SoftWearTimer(3000);	/* 約??msec:ＲＩＳＣエミュレータ実測値 */

	/** ファンクションセット */
	LCD_WriteInstruction(LCD_FUNCTION_SET);
	/** 100usec以上待つ */
/*	LCD_SoftWearTimer(170);		@* 約566usec:Ｖ５３エミュレータ実測値 */
	LCD_SoftWearTimer(250);		/* 約??msec:ＲＩＳＣエミュレータ実測値 */

	/** ファンクションセット */
	LCD_WriteInstruction(LCD_FUNCTION_SET);
	/** 15msec以上待つ */
/*	LCD_SoftWearTimer(7000);	@* 約19msec:Ｖ５３エミュレータ実測値 */
	LCD_SoftWearTimer(9000);	/* 約??msec:ＲＩＳＣエミュレータ実測値 */

	/** ファンクションセット */
	LCD_WriteInstruction(LCD_FUNCTION_SET);
	LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/** 表示ＯＦＦ */
	LCD_WriteInstruction(LCD_DISPLAY_OFF);
	LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/** 表示クリア */
	LCD_WriteInstruction(LCD_CLEAR_DISPLAY);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME10MSEC);

	/** エントリーモードセット */
	LCD_WriteInstruction(LCD_ENTRY_MODE);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/* 注）POPLAR_Bでオールラムクリアを実行されると、モードだけコピーモードに初期化されてしまい、
	** 　　ＣＧＲＡＭは日付表示用のままなので、CMN_InitializeAllBackUpRAM()でも初期化します
	*/
	LCD_SoftWearTimer(3000);	/* ここにウエイトを置かないとＣＧＲＡＭにうまくセットできない */
	/** ＣＧＲＡＭにデータをセット */
	InitializeCGRAM_Data();

	/** 表示ＯＮ */
	LCD_WriteInstruction(LCD_DISPLAY_ON);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/** 表示クリア */
	LCD_WriteInstruction(LCD_CLEAR_DISPLAY);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME10MSEC);
}

/*************************************************************************
	module		:[ＣＧＲＡＭ書き込みデータ初期化]
	function	:[
		1.機種・国・状態により、ＣＧＲＡＭに初期データを書き込みます
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/26]
	author		:[渡辺一章]
*************************************************************************/
void InitializeCGRAM_Data(void)
{
#if !(PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズでは、ＣＧＲＡＭは使用していません */
 #if defined(JPN)	/* 日本の時 */
	if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
		WriteCGRAM((UBYTE *)CG_RamTableCopyModeDensity);	/* コピーモード原稿濃度表示用のﾃﾞｰﾀをCGRAMに書き込みます */
	}
	else {						/* ファクスモードの時 */
		WriteCGRAM((UBYTE *)CG_RamTableFaxReadyKanji);		/* 日付表示用のﾃﾞｰﾀをCGRAMに書き込みます */
	}
 #else				/* 日本以外の時 */
  #if (PRO_COPY_FAX_MODE == ENABLE)		/* ポプラＢ対応  By S.Fukui  Sep.29,1997 */
	WriteCGRAM((UBYTE *)CG_RamTableCopyModeDensity);	/* コピーモード原稿濃度表示用のﾃﾞｰﾀをCGRAMに書き込みます */
  #else
	WriteCGRAM((UBYTE *)CG_RamTableDensityVolumeSet);	/* 濃度・ボリューム設定用のﾃﾞｰﾀをCGRAMに書き込みます */
  #endif
 #endif
#endif
}

/*************************************************************************
	module		:[特殊文字処理]
	function	:[
		1.Ⅰ,Ⅱ,Ⅲ,Ⅳに対する処理を行う-> ＡＮＺＵではいらなくなった 1995/12/12
		2.グループ記号、短縮記号に対する処理をおこなう
		3.ワンタッチ記号の、ＰＩＮ記号に対する処理を行う
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/25]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE CheckSpecialCharacter(UBYTE character)
{
	UBYTE	ret_value;

	ret_value = character;

	switch (character) {
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	case OPR_ONETOUCH_MARK_LEFT:	/* ワンタッチ［０１］～［７２］の左かっこ */
	case OPR_PROGRAM_MARK_LEFT:		/* プログラムワンタッチ［７３］～［８０］の左かっこ */
		ret_value = '[';
		break;
	case OPR_ONETOUCH_MARK_RIGHT:	/* ワンタッチ［０１］～［７２］の右かっこ */
	case OPR_PROGRAM_MARK_RIGHT:	/* プログラムワンタッチ［７３］～［８０］の右かっこ */
		ret_value = ']';
		break;
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	case OPR_ONETOUCH_MARK:			/* ワンタッチＵ１～Ｕ８のＵ */
		ret_value = 'U';
		break;
	case OPR_PROGRAM_MARK:			/* プログラムワンタッチＰ１～Ｐ１２のＰ */
		ret_value = 'P';
		break;
#endif
	case OPR_SPEED_MARK:			/* 短縮記号 */
#if (PRO_OKI == ENABLE)	/* 海外では短縮等の頭文字が英語と違うので、変更できるようにします by K.Watanabe 1999/02/09 */
		ret_value = *CalculateStringAddress(&D2W_HeadCharacter_Speed);
#else
		ret_value = 'S';
#endif
		break;
	case OPR_GROUP_MARK:			/* グループ記号 */
		ret_value = 'G';
		break;
	case OPR_PIN_MARK:				/* ＰＩＮ記号 */
		ret_value = '*';
		break;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/03/12 by K.Okada */
	/******************
	** 記号置き換え
	******************/
	case DIRECT_ADDRESS_MARK: /* 直接アドレス開始記号 + */
		ret_value = '+';
		break;
#endif
#if (PRO_JIS_CODE == ENABLE)
	case OPR_KANJI_CODE_MARK_LEFT:	/* 漢字コードの左かっこ */
		ret_value = '(';
		break;
	case OPR_KANJI_CODE_MARK_RIGHT:	/* 漢字コードの右かっこ */
		ret_value = ')';
		break;
#endif
	case OPR_PAPER_SIZE_R:			/* 紙サイズのＲを表すグラフィック（ﾜｰﾃﾞｨﾝｸﾞで直接使用） */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		ret_value = 0xF5;
#endif
		ret_value = OPR_CG_FONT_5;
		break;
	default:
		break;
	}

#if !(PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬでは、スピーカーボリューム調整の時のみ変換します 1997/11/19 Y.Matsukuma */
	/*
	** ＣＧＲＡＭをアクセスするために変換する
	** ユーザーフォントコード	０ｘ１０～０ｘ１７（割り当て）　←　０ｘＦ０～０ｘＦ７から変更
	** ＣＧＲＡＭコード			０ｘ００～０ｘ０７（固定）
	*/
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//	if ((ret_value >= 0xF0) && (ret_value <= 0xF7)) {
//		ret_value -= 0xF0;
//	}
#endif
	if ((ret_value >= OPR_CG_FONT_0) && (ret_value <= OPR_CG_FONT_7)) {
		ret_value -= OPR_CG_FONT_0;
	}
#else
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/23 */
	if (TelControl.NcuStatus & OPR_HOOKKEY_OFFHOOK) {
 #else
	if (TelControl.NcuStatus == OPR_HOOKKEY_OFFHOOK) {
 #endif /* defined (KEISATSU) */
#if (0)	/* 海外ではCGRAMと特殊文字の文字ｺｰﾄﾞが重複するので、CGRAMｱｸｾｽ用のｺｰﾄﾞを変更します by K.Watanabe 1998/10/26 */
//		if ((ret_value >= 0xF0) && (ret_value <= 0xF7)) {
//			ret_value -= 0xF0;
//		}
#endif
		if ((ret_value >= OPR_CG_FONT_0) && (ret_value <= OPR_CG_FONT_7)) {
			ret_value -= OPR_CG_FONT_0;
		}
	}
#endif
	return (ret_value);
}

/*************************************************************************
	module		:[ＣＧＲＡＭ書き換え検査]
	function	:[
		1.表示する文字列の中に、縦原稿を表すコードがあれば、ＣＧＲＡＭを
		　使用するので、書き換えます
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/08/26]
	author		:[渡辺一章]
*************************************************************************/
void CheckChangeCGRAM(UBYTE *string)
{
	UBYTE	i;	/* ループ変数 */

	for (i = 0; i < OPR_DISPLAY_MAX; i++) {
		if (*string == NULL) {
			break;
		}
		if (*string++ == OPR_PAPER_SIZE_R) {	/* 文字列の中に、縦原稿があった時 */
			/* ＣＧＲＡＭに縦原稿表示用のデータを書き込みます */
			WriteCGRAM((UBYTE *)CG_RamTableCopyModeDensity);
			break;
		}
	}
}
 #endif	/* (PRO_ANK_TO_KANJI == ENABLE)	*/

/*************************************************************************
	module		:[ＬＣＤ上段に文字列を表示]
	function	:[
	#if (PRO_ANK_TO_KANJI == DISABLE)
		1.LCDの上段の指定された位置に文字列を表示
		2.表示位置:０～１９
	#else
		1.ＬＣＤ３段目の指定された位置に文字列を表示
		2.位置指定：０～１９　→　表示位置:６０～７９
	#endif
	]
	return		:[]
	common		:[
		DisplayBufferHigh
		SYS_LCD_DataPortStatus
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/21]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayStringHigh(UBYTE pos,		/*表示位置(0～19)*/
					   UBYTE *string)	/*表示文字列*/
{
 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/15 */
	UBYTE	write_data;
	UBYTE	counter;
	UBYTE	ddram_address;

	/*---------------------------*/
	/** 表示文字列のアドレス変換 */
	/*---------------------------*/
	string = CalculateStringAddress(string);

	/*-------------------------*/
	/** ＣＧＲＡＭ書き換え検査 */
	/*-------------------------*/
	CheckChangeCGRAM(string);

	/** セマフォの獲得 1995/12/14*/
	wai_sem(semno.lcd);

	/** カーソルをＯＦＦする 1996/01/06 Eguchi */
	CursorOff();

	/*--------------------------------------------*/
	/** DDRAMアドレスセット(表示開始位置のセット) */
	/*--------------------------------------------*/
	/* DDRAMを選択 */
	ddram_address = (UBYTE)DDRAM_FIRST_ROW_ADDRESS + pos;	/* DDRAM_FIRST_ROW_ADDRESS = 0x80*/
	LCD_WriteInstruction(ddram_address);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/*-----------------------*/
	/** 表示文字列の書き込み */
	/*-----------------------*/
	for (counter = 0; counter < OPR_DISPLAY_MAX; counter++) {
		write_data = *string++;
		if (write_data == 0x00) {	/* NULLの場合書き込み終了（文字列の最後にはNULLをいれておく） */
			break;
		}

		/** 特殊文字（Ⅰ,Ⅱ,Ⅲ等）に対する変換処理 */
		write_data = CheckSpecialCharacter(write_data);

		/*----------------------------------------*/
		/** 表示文字データの書き込み(ＬＣＤ表示） */
		/*----------------------------------------*/
		LCD_WriteData(write_data);
    	LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
	}

	/** 点滅表示を停止する */
	StopFunctionFlashHigh();

	/** セマフォの解放 1995/12/14*/
	sig_sem(semno.lcd);

 #else	/* (PRO_ANK_TO_KANJI == ENABLE) */
	DisplayStringAttribute((UBYTE)(60 + pos), string, ATTRIBUTE_NORMAL);

 #endif	/* (PRO_ANK_TO_KANJI == DISABLE) */
}

/*************************************************************************
	module		:[ＬＣＤ下段に文字列を表示]
	function	:[
	#if (PRO_ANK_TO_KANJI == DISABLE)
		1.LCD下段の指定された位置に文字列を表示
	#else
		1.ＬＣＤ４段目の指定された位置に文字列を表示
		2.位置指定：０～１９　→　表示位置:９０～１０９
	#endif
	]
	return		:[]
	common		:[
		DisplayBufferLow
		SYS_LCD_DataPortStatus
	]
	condition	:[点滅表示には使用しないこと]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void DisplayStringLow(UBYTE pos,		/*表示位置(0～19)*/
					  UBYTE *string)	/*表示文字列*/
{
 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/15 */
	UBYTE	write_data;
	UBYTE	counter;
	UBYTE	ddram_address;

	/*---------------------------*/
	/** 表示文字列のアドレス変換 */
	/*---------------------------*/
	string = CalculateStringAddress(string);

	/*-------------------------*/
	/** ＣＧＲＡＭ書き換え検査 */
	/*-------------------------*/
	CheckChangeCGRAM(string);

	/** セマフォの獲得 1995/12/14*/
	wai_sem(semno.lcd);

	/** カーソルをＯＦＦする 1996/01/06 Eguchi */
	CursorOff();

	/*----------------------------------------------*/
	/** DDRAMのアドレスセット(表示開始位置のセット) */
	/*----------------------------------------------*/
	ddram_address = (UBYTE)DDRAM_SECOND_ROW_ADDRESS + pos;	/*DDRAM_SECOND_ROW_ADDRESS = 0xc0*/
	LCD_WriteInstruction(ddram_address);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/*-----------------------*/
	/** 表示文字列の書き込み */
	/*-----------------------*/
	for (counter = 0; counter < OPR_DISPLAY_MAX; counter++) {
		write_data = *string++;
		if (write_data == 0x00) {	/* NULLの場合書き込み終了（文字列の最後にはNULLをいれておく） */
			break;
		}

		/** 特殊文字（Ⅰ,Ⅱ,Ⅲ等）に対する変換処理 */
		write_data = CheckSpecialCharacter(write_data);

		/*----------------------------------------*/
		/** 表示文字データの書き込み(ＬＣＤ表示） */
		/*----------------------------------------*/
		LCD_WriteData(write_data);
    	LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
	}

	/** 点滅表示を停止する 1995/12/16 Eguchi */
	/* 点滅中に点滅タスク以外のタスクが表示を書き換えるには点滅をやめる時であるとする */
	StopFunctionFlashLow();

	/** セマフォの解放 1995/12/14*/
	sig_sem(semno.lcd);

 #else	/* (PRO_ANK_TO_KANJI == ENABLE) */
	DisplayStringAttribute((UBYTE)(90 + pos), string, ATTRIBUTE_NORMAL);

 #endif	/* (PRO_ANK_TO_KANJI == DISABLE) */
}

/*************************************************************************
	module		:[指定された位置にカーソルを表示]
	function	:[
	#if (PRO_ANK_TO_KANJI == DISABLE)
		1.引数で指定された位置にカーソルを表示させる
		2.表示位置：上段→０～１９、下段→２０～３９
	#endif
	]
	return		:[]
	common		:[SYS_LCD_DataPortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void CursorOn(UBYTE pos)	/*表示位置(0～39)*/
{
 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/15 */
	UBYTE	ddram_adr;

	/** セマフォの獲得 1995/12/14*/
	wai_sem(semno.lcd);
	/*-----------------------------------*/
	/** カーソル表示位置のアドレスを計算 */
	/*-----------------------------------*/
	if (pos < 20) { /*上段*/
		ddram_adr = (UBYTE)DDRAM_FIRST_ROW_ADDRESS + pos;
	}
	else {							/*下段*/
		pos -= 20;
		ddram_adr = (UBYTE)DDRAM_SECOND_ROW_ADDRESS + pos;
	}
	
	/*----------------------*/
	/** DDRAMアドレスセット */
	/*----------------------*/
	LCD_WriteInstruction(ddram_adr);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/*---------------*/
	/** カーソル表示 */
	/*---------------*/
	LCD_WriteInstruction(LCD_CURSOR_ON);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/** セマフォの解放 1995/12/14*/
	sig_sem(semno.lcd);

 #else	/* (PRO_ANK_TO_KANJI == ENABLE) */
	DisplayCursorON(pos);

 #endif	/* (PRO_ANK_TO_KANJI == DISABLE) */
}

/*************************************************************************
	module		:[カーソルＯＦＦ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void CursorOff(void)
{
 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/15 */
	LCD_WriteInstruction(LCD_CURSOR_OFF);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

 #else
	DisplayCursorOFF();

 #endif
}

/*************************************************************************
	module		:[指定した位置に一文字表示]
	function	:[
		1.引数で指定された位置に一文字表示する
	#if (PRO_ANK_TO_KANJI == DISABLE)
		2.表示位置：上段ｰ>0～19､下段->20～39
	#else
	#endif
	]
	return		:[]
	common		:[SYS_LCD_DataPortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayChar(UBYTE pos,			/*表示位置 0-39*/
				 UBYTE dsp_char)	/*表示文字*/
{
 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/15 */
	UBYTE	ddram_adr;

	/** セマフォの獲得 1995/12/14*/
	wai_sem(semno.lcd);

	/** カーソルをＯＦＦする 1996/01/06 Eguchi */
	CursorOff();

	/*-------------------------*/
	/** 表示位置のアドレス計算 */
	/*-------------------------*/
	if (pos < 20) {
		ddram_adr = (UBYTE)DDRAM_FIRST_ROW_ADDRESS + pos;
	}
	else {
		pos -= 20;
		ddram_adr = (UBYTE)DDRAM_SECOND_ROW_ADDRESS + pos;
	}

	/*----------------------------------------*/
	/** DDRAMアドレスセット(表示位置のセット) */
	/*----------------------------------------*/
	LCD_WriteInstruction(ddram_adr);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	
	/* 文字がNULLの場合終了 */
	if (dsp_char == 0x00) {
		return;
	}

	/** 特殊文字（Ⅰ,Ⅱ,Ⅲ等）に対する処理 */
	dsp_char = CheckSpecialCharacter(dsp_char);

	/*-------------*/
	/** 文字を表示 */
	/*-------------*/
	LCD_WriteData(dsp_char);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/** セマフォの解放 1995/12/14*/
	sig_sem(semno.lcd);

 #else	/* (PRO_ANK_TO_KANJI == ENABLE) */
	UBYTE xc;        /* x座標 */
	UBYTE yc;        /* y座標 */

	if (pos >= LCD_TOTAL_CHARACTERS) {
		return; /** 位置が120以上なら何もしない */
	}

	yc = pos / LCD_WIDTH;
	xc = pos % LCD_WIDTH;
	GetByteCharacterDotPattern(xc, yc, dsp_char, ATTRIBUTE_NORMAL);

 #endif	/* (PRO_ANK_TO_KANJI == DISABLE) */
}

/*************************************************************************
	module		:[ＬＣＤ上段表示クリア]
	function	:[
	#if (PRO_ANK_TO_KANJI == DISABLE)
		1.LCD上段の表示をクリア(スペースを書き込む）
	#else
		1.ＬＣＤ３段目の表示をクリア(スペースを書き込む）
	#endif
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口,渡辺一章]
*************************************************************************/
void ClearDisplayHigh(void)
{
 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/15 */
	UBYTE	clear_buffer[OPR_WORDING_LEN];

	CMN_MemorySetNULL(clear_buffer, OPR_DISPLAY_MAX, ' ');
	DisplayStringHigh(0, clear_buffer);

 #else
	ClearString2();

 #endif
}

/*************************************************************************
	module		:[ＬＣＤ下段表示クリア]
	function	:[
	#if (PRO_ANK_TO_KANJI == DISABLE)
		1.ＬＣＤ下段の表示をクリアする（スペースを書き込む）
	#else
		1.ＬＣＤ４段目の表示をクリア(スペースを書き込む）
	#endif
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口,渡辺一章]
*************************************************************************/
void ClearDisplayLow(void)
{
 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/15 */
	UBYTE	clear_buffer[OPR_WORDING_LEN];

	CMN_MemorySetNULL(clear_buffer, OPR_DISPLAY_MAX, ' ');
	DisplayStringLow(0, clear_buffer);

 #else
	ClearString3();

 #endif
}

/*************************************************************************
	module		:[ＬＣＤ上段に文字列を表示]
	function	:[
		1.LCDの上段の指定された位置に文字列を表示
		2.点滅表示専用の関数です
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/25]
	author		:[渡辺一章]
*************************************************************************/
void DisplayFlashStringHigh(UBYTE pos,		/*表示位置(0～19)*/
							UBYTE *string)	/*表示文字列*/
{
 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/15 */
	UBYTE	write_data;
	UBYTE	counter;
	UBYTE	ddram_address;

	/*---------------------------*/
	/** 表示文字列のアドレス変換 */
	/*---------------------------*/
	string = CalculateStringAddress(string);

	/*-------------------------*/
	/** ＣＧＲＡＭ書き換え検査 */
	/*-------------------------*/
	CheckChangeCGRAM(string);

	/** カーソルをＯＦＦする 1996/01/06 Eguchi */
	CursorOff();

	/*--------------------------------------------*/
	/** DDRAMアドレスセット(表示開始位置のセット) */
	/*--------------------------------------------*/
	/* DDRAMを選択 */
	ddram_address = (UBYTE)DDRAM_FIRST_ROW_ADDRESS + pos;	/* DDRAM_FIRST_ROW_ADDRESS = 0x80*/
	LCD_WriteInstruction(ddram_address);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/*-----------------------*/
	/** 表示文字列の書き込み */
	/*-----------------------*/
	for (counter = 0; counter < OPR_DISPLAY_MAX; counter++) {
		write_data = *string++;
		if (write_data == 0x00) {	/* NULLの場合書き込み終了（文字列の最後にはNULLをいれておく） */
			break;
		}

		/** 特殊文字（Ⅰ,Ⅱ,Ⅲ等）に対する変換処理 */
		write_data = CheckSpecialCharacter(write_data);

		/*-----------------------------------------*/
		/** 表示文字データの書き込み（ＬＣＤ表示） */
		/*-----------------------------------------*/
		LCD_WriteData(write_data);
		LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
	}
 #else	/* (PRO_ANK_TO_KANJI == ENABLE) */

 #endif	/* (PRO_ANK_TO_KANJI == DISABLE) */
}

/*************************************************************************
	module		:[ＬＣＤ下段に文字列を表示]
	function	:[
		1.LCD下段の指定された位置に文字列を表示
		2.点滅表示専用の関数です
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void DisplayFlashStringLow(UBYTE pos,		/*表示位置(0～19)*/
						   UBYTE *string)	/*表示文字列*/
{
 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/15 */
	UBYTE	write_data;
	UBYTE	counter;
	UBYTE	ddram_address;

	/*---------------------------*/
	/** 表示文字列のアドレス変換 */
	/*---------------------------*/
	string = CalculateStringAddress(string);

	/*-------------------------*/
	/** ＣＧＲＡＭ書き換え検査 */
	/*-------------------------*/
	CheckChangeCGRAM(string);

	/** カーソルをＯＦＦする 1996/01/06 Eguchi */
	CursorOff();

	/*----------------------------------------------*/
	/** DDRAMのアドレスセット(表示開始位置のセット) */
	/*----------------------------------------------*/
	ddram_address = (UBYTE)DDRAM_SECOND_ROW_ADDRESS + pos;	/*DDRAM_SECOND_ROW_ADDRESS = 0xc0*/
	LCD_WriteInstruction(ddram_address);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/*-----------------------*/
	/** 表示文字列の書き込み */
	/*-----------------------*/
	for (counter = 0; counter < OPR_DISPLAY_MAX; counter++) {
		write_data = *string++;
		if (write_data == 0x00) {	/* NULLの場合書き込み終了（文字列の最後にはNULLをいれておく） */
			break;
		}

		/** 特殊文字（Ⅰ,Ⅱ,Ⅲ等）に対する変換処理 */
		write_data = CheckSpecialCharacter(write_data);

		/*----------------------------------------*/
		/** 表示文字データの書き込み(ＬＣＤ表示） */
		/*----------------------------------------*/
		LCD_WriteData(write_data);
    	LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
	}
 #else	/* (PRO_ANK_TO_KANJI == ENABLE) */

 #endif	/* (PRO_ANK_TO_KANJI == DISABLE) */
}

/*************************************************************************
	module		:[]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[]
	author		:[]
*************************************************************************/
void DisplayAllBlack(void)
{
	CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, 0xFF);
 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/15 */
	DisplayStringHigh(0, DisplayBufferHigh);
	DisplayStringLow(0, DisplayBufferHigh);

 #else
	DisplayString0(DisplayBufferHigh);
	DisplayString1(DisplayBufferHigh);
	DisplayString2(DisplayBufferHigh);
	DisplayString3(DisplayBufferHigh);

 #endif
}
#endif	/* #if (PRO_KEYPANEL != PANEL_HINOKI) && (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */

#if (PRO_JIS_CODE == ENABLE)	/* By M.Tachibana 1997/02/08 */
/*************************************************************************
	module		:[JISからシフトJISへの変換]
	function	:[
		1.JISコード（第１・第２水準）をシフトJISコードに変換します
	]
	return		:[シフトJISコード]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/09/16]
	auther		:[石橋正和]
*************************************************************************/
UWORD JIS_ToShiftJIS(UWORD jis_code)	/* JISコード */
{
	UWORD	high;	/* JISコードの上位バイト */
	UWORD	low;	/* JISコードの下位バイト */

	high = (jis_code >> 8) & 0x00FF;
	low = jis_code & 0x00FF;

	if (high & 1) {
		low += 0x001F;
	}
	else {
		low += 0x007D;
	}

	high = (high - 0x0021 >> 1) + 0x0081;

	if (low >= 0x007F) {
		low++;
	}
	if (high > 0x009F) {
		high += 0x0040;
		}

	return((high << 8) | low);
}

/*************************************************************************
	module		:[シフトJISからJISへの変換]
	function	:[
		1.シフトJISコードをJISコード（第１・第２水準）に変換します
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和,渡辺一章]
*************************************************************************/
void ShiftJIS_ToJIS(UWORD *high,	/* シフトJISコードの上位バイト(JISコードに変換) */
					UWORD *low)		/* シフトJISコードの下位バイト(JISコードに変換) */
{
	/** 上位バイトの処理 */
	if (*high <= 0x9f) {
		*high -= 0x71;
	}
	else {
		*high -= 0xb1;
	}
	*high = *high * 2 + 1;

	/** 下位バイトの処理 */
	if (*low > 0x7f) {
		(*low)--;
	}
	if (*low >= 0x9e) {
		*low -= 0x7d;
		(*high)++;
	}
	else {
		*low -= 0x1f;
	}
}

/*************************************************************************
	module		:[全角文字フォントの先頭アドレス／配列番号を得る]
	function	:[
		1.シフトJISコードをJISコードに変換します
		2.JIS第１水準の時、
		　・コードをCGの文字コードに変換します
		　・文字コードからＣＧの先頭アドレスを求めます
		3.JIS第２水準の時、
		　・漢字フォントテーブルの配列番号を求めます
	]
	return		:[
		CG_ADDRESS	:JIS第1水準（ｱﾄﾞﾚｽにCG(HITACHI HN62321BPAA0)の全角文字ﾌｫﾝﾄの先頭ｱﾄﾞﾚｽをｾｯﾄ）
		FONT_DATA_NO:JIS第2水準（ｱﾄﾞﾚｽに漢字ﾌｫﾝﾄﾃｰﾌﾞﾙの配列番号をｾｯﾄ）
	]
	common		:[]
	condition	:[]
	comment		:[
		現状の仕様では、
			JIS第１水準　→　ＣＧＲＯＭにフォントデータを定義
			JIS第２水準　→　漢字フォントテーブルにいくつかのフォントデータを定義
		となっているので、JIS第２水準の全てを使用できる訳ではありません

		将来JIS第２水準もＣＧＲＯＭに持つようになった場合には、変更が必要です
	]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1997/04/10]
	auther		:[渡辺一章]
*************************************************************************/
UBYTE GetFontAddress(UDWORD *address,	/* 全角文字ﾌｫﾝﾄの先頭ｱﾄﾞﾚｽ(JIS第1水準)／漢字ﾌｫﾝﾄﾃｰﾌﾞﾙの配列番号(JIS第2水準) */
					 UWORD  high,		/* シフトJISの上位バイト */
					 UWORD  low)		/* シフトJISの下位バイト */
{
	UBYTE	ret;	/* リターン値 */

	/* シフトJISコードをJISコードへ変換します */
	ShiftJIS_ToJIS(&high, &low);

	if (CheckJIS1Code((high << 8) | low)) {	/* JIS第１水準のコードの時 */
		if ((high & 0x0020) && (~high & 0x0010)) {	/** 非漢字の場合 */
			high = ((low & 0x0060) >> 2) | (high & 0x0007);
			low &= 0x001F;
		}
		else {										/** 漢字（JIS第1水準）の場合 */
			high = ((high & 0x0040) >> 2) | (high & 0x000F);
			low &= 0x007F;
		}

		/* ＣＧの先頭アドレスをセットします */
		*address = (UDWORD)((high << 7) | low) << 5;

		/* JIS第１水準の時は、ＣＧからフォントデータを取得します */
		ret = CG_ADDRESS;
	}
	else {									/* JIS第２水準のコードの時 */
		/* 漢字フォントテーブルの配列番号をセットします */
		*address = CheckFontJIS2Code((high << 8) | low);

		/* JIS第２水準の時は、漢字フォントテーブルからフォントデータを取得します */
		ret = FONT_DATA_NO;
	}

	return(ret);
}

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
	keyward		:[OPR]
	date		:[1997/04/08]
	auther		:[渡辺一章]
*************************************************************************/
UBYTE CheckJIS1Code(UWORD code)
{
	UBYTE	high;	/* コードの上位バイト */
	UBYTE	low;	/* コードの下位バイト */
	UBYTE	ret;	/* リターン値 */

	high = (UBYTE)((0xFF00 & code) >> 8);
	low = (UBYTE)(0x00FF & code);
	ret = FALSE;

	/* 引数のJISコードが、JIS第１水準のJISコードかを調べます */
	if (((high == 0x21 || (0x30 <= high && high <= 0x4E)) && (0x21 <= low && low <= 0x7E))	/* 記号，頭文字ア～レ	*/
	 || (0x2221 <= code && code <= 0x222E)		/* 記号					*/
	 || (0x2330 <= code && code <= 0x2339)		/* 数字					*/
	 || (0x2341 <= code && code <= 0x235A)		/* 英字（大）			*/
	 || (0x2361 <= code && code <= 0x237A)		/* 英字（小）			*/
	 || (0x2421 <= code && code <= 0x2473)		/* ひらがな				*/
	 || (0x2521 <= code && code <= 0x2576)		/* カタカナ				*/
	 || (0x2621 <= code && code <= 0x2638)		/* ギリシャ文字（大）	*/
	 || (0x2641 <= code && code <= 0x2658)		/* ギリシャ文字（小）	*/
	 || (0x2721 <= code && code <= 0x2741)		/* ロシア文字（大）		*/
	 || (0x2751 <= code && code <= 0x2771)		/* ロシア文字（小）		*/
	 || (0x4F21 <= code && code <= 0x4F53)) {	/* 頭文字ロ・ワ			*/
		ret = TRUE;
	}

	return(ret);
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
	keyward		:[OPR]
	date		:[1997/04/09]
	auther		:[渡辺一章]
*************************************************************************/
UBYTE CheckFontJIS2Code(UWORD code)
{
	UBYTE	i;		/* ループ変数 */
	UBYTE	ret;	/* リターン値 */

	ret = KANJI2_NONE;

	for (i = 0; i < KANJI2_TABLE_MAX; i++) {
		if (Kanji2[i].Code == code) {	/* フォント定義されているJIS第２水準のJISコードの時 */
			ret = i;
			break;
		}
	}

	return(ret);
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
	keyward		:[OPR]
	date		:[1997/04/09]
	auther		:[渡辺一章]
*************************************************************************/
UBYTE CheckShiftJISCode(UBYTE high, UBYTE low)
{
	UBYTE	ret;	/* リターン値 */

	ret = FALSE;

	/* 引数のコードが、シフトJISのコードかを調べます */
	if (((high >= SHIFT_JIS_1_HIGH_MIN) && (high <= SHIFT_JIS_1_HIGH_MAX)
	  || (high >= SHIFT_JIS_2_HIGH_MIN) && (high <= SHIFT_JIS_2_HIGH_MAX))
	 && ((low >= SHIFT_JIS_LOW_MIN) && (low <= SHIFT_JIS_LOW_MAX))) {
		ret = TRUE;
	}

	return(ret);
}

#endif	/* (PRO_JIS_CODE == ENABLE) */
