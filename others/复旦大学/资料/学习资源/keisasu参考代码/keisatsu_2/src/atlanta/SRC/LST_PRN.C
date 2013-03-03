/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_PRN.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: キャラクタプリントのイメージ展開
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\apl_msg.h"		/* メッセージ関係のデファイン */
#include "\src\atlanta\define\std.h"			/* 標準定義 */
#include "\src\atlanta\define\sys_stat.h"		/* リスト関係のデファイン */
#include "\src\atlanta\define\sysdoc.h"			/* 記録紙ｻｲｽﾞのﾃﾞﾌｧｲﾝ */

#include "\src\atlanta\define\lst_def.h"		/* リスト関係のデファイン */

#include "\src\atlanta\define\cmn_pro.h"		/* 共通関数のプロトタイプ宣言 */
#include "\src\atlanta\define\lst_pro.h"		/* リストプリントのプロトタイプ宣言 */
#include "\src\atlanta\define\uni_pro.h"		/* 機種固有関数のプロトタイプ宣言 */

#include "\src\atlanta\ext_v\font_tbl.h"
#include "\src\atlanta\ext_v\lst_data.h"		/* リスト関係のextern宣言 */
#include "\src\atlanta\ext_v\lst_tbl.h"			/* リスト関係のextern宣言 */
#include "\src\atlanta\ext_v\sys_data.h"		/* 上下段記録紙ﾀｲﾌﾟのextern宣言 */

#if (PRO_PANEL == ANK)
#include "\src\atlanta\opr\ank\define\opr_def.h"
#include "\src\atlanta\opr\ank\define\opr_pro.h"
#endif
#if (PRO_PANEL == KANJI)
#include "\src\atlanta\opr\kanji\define\opr_def.h"
#include "\src\atlanta\opr\kanji\define\lcd_def.h"
#include "\src\atlanta\opr\kanji\define\opr_pro.h"
#include "\src\atlanta\opr\kanji\ext_v\fnt_tbl.h"	/* ワンタッチの表示を[]->絵文字に変更 By O.Kimoto 1998/01/22 */
#endif
#if (PRO_PRINT_TYPE == LED)
#include "\src\atlanta\prt\ph3\define\prn_def.h"
#include "\src\atlanta\prt\ph3\ext_v\prn_data.h"
#endif
#if (PRO_PRINT_TYPE == LASER)
#include "\src\atlanta\prt\sp322\define\prn_def.h"
#include "\src\atlanta\prt\sp322\ext_v\prn_data.h"
#endif
#if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)
#ifdef LST_DEBUG
#include "\src\atlanta\sim_lst\define\cg_rom.h"
#else
#include "\src\atlanta\ext_v\cg_rom.h"
#endif
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/*  By O.Kimoto 1998/11/06 */
/*************************************************************************
	module		:[8ビットフォントデータを2倍に引き伸ばし、16ビットデータを作る]
	function	:[
		1.
	]
	return		:[変換後の16ビットデータ]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/09/07]
	auther		:[石橋正和]
*************************************************************************/
UWORD		GetTwiceFontData(
			UBYTE byte_data) /* 変換元データ */
{
#if 0
//	UWORD word_data = 0; /* 変換後データ */
//	UBYTE bit = 0x01;
//	UWORD two_bit = 0x0003;
//
//	while (bit) {
//		if (byte_data & bit) {
//			word_data |= two_bit;
//		}
//
//		bit <<= 1;
//		two_bit <<= 2;
//	}
//
//	return(word_data);
#endif
#if (PRO_CPU == SH7043)
	return((UWORD)(((UWORD)(TwiceData[((byte_data & 0xF0) >> 4)]) << 8) | (UWORD)TwiceData[(byte_data & 0x0F)]));
#else
	return((UWORD)((UWORD)TwiceData[((byte_data & 0xF0) >> 4)] | ((UWORD)TwiceData[(byte_data & 0x0F)] << 8)));
#endif
}
#else
/*************************************************************************
	module		:[8ビットフォントデータを2倍に引き伸ばし、16ビットデータを作る]
	function	:[
		1.
	]
	return		:[変換後の16ビットデータ]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/09/07]
	auther		:[石橋正和]
*************************************************************************/
UWORD		GetTwiceFontData(
			UBYTE byte_data) /* 変換元データ */
{
#if 0
//	UWORD word_data = 0; /* 変換後データ */
//	UBYTE bit = 0x01;
//	UWORD two_bit = 0x0003;
//
//	while (bit) {
//		if (byte_data & bit) {
//			word_data |= two_bit;
//		}
//
//		bit <<= 1;
//		two_bit <<= 2;
//	}
//
//	return(word_data);
#endif
	return((UWORD)((UWORD)TwiceData[((byte_data & 0xF0) >> 4)] | ((UWORD)TwiceData[(byte_data & 0x0F)] << 8)));
}

#endif


/*************************************************************************
	module		:[全角１文字分のフォントイメージデータ作成]
	function	:[
		1.全角１文字に対する任意の１ラインのイメージデータを作成
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/06/08]
	auther		:[石橋正和,渡辺一章]
*************************************************************************/
#if (PRO_PANEL == KANJI) || ( PRO_JIS_CODE == ENABLE )
void GetWordCharacterImage(
		UBYTE *string,		/* 展開する文字の先頭バイトのポインタ */
		UBYTE *attribute,	/* 展開する文字のアトリビュートの先頭バイトのポインタ */
		UBYTE *image_buff,	/* 展開したイメージのバッファ */
		UBYTE xc)			/* 展開する文字のx座標 */
{
	UDWORD	address;	/* CGの全角文字フォントの先頭アドレス(17Bit)／漢字フォントテーブルの配列番号 */
	UWORD	offset;
	UWORD	pos;
	UWORD	high;		/* 展開する文字の上位バイト */
	UWORD	low;		/* 展開する文字の下位バイト */
	UBYTE	line;

	high = *string;
	low = *(string + 1);

#if (PRO_PANEL == KANJI)
	/* ワンタッチの表示を[]->絵文字に変更 By O.Kimoto 1998/01/22 */
	/** ICHOU追加 -- 指文字の印字（ワンタッチキーの表現のため）*/
	if (*string >= LCD_PICFONT && *(string + 1) == LCD_PICFONT_LOWER) {	/** 指文字の場合（アトリビュート処理はない）*/
		line = 0;
		for (pos = (UWORD)xc; pos < 1280; pos += 80) {
			/** 前半分のドットパターンを格納 */
			(*(image_buff + pos))     = (UBYTE)(LCD_PictureFontPattern[*string & 0xf][line] & 0xff);
			line++;
			/** 後半分のドットパターンを格納 */
			(*(image_buff + pos + 1)) = (UBYTE)(LCD_PictureFontPattern[*string & 0xf][line] & 0xff);
			line++;
		}
		return;
	}
#endif

	if (GetFontAddress(&address, high, low) == CG_ADDRESS) {	/* CGからﾌｫﾝﾄﾃﾞｰﾀを取得する時(JIS第1水準) */
		offset = (UWORD)(address & 0xFFFF);

		if (address & 0x10000L) {
			switch (*attribute) {
			case LST_INV_XXX_XXX:	/** 反転の場合 */
				for (pos = (UWORD)xc; pos < 1280; pos += 80) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = (UBYTE)~CG_ROM1[offset++];
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = (UBYTE)~CG_ROM1[offset++];
				}
				break;
			case LST_MES_XXX_XXX:	/** 網掛けの場合 */
				pos = (UWORD)xc;
				for (line = 0; line < 16; line++) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = (UBYTE)(CG_ROM1[offset++] | PrintMeshData[line]);
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = (UBYTE)(CG_ROM1[offset++] | PrintMeshData[line]);
					pos += 80;
				}
				break;
			default:				/** 修飾なしの場合 */
				for (pos = (UWORD)xc; pos < 1280; pos += 80) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = (UBYTE)CG_ROM1[offset++];
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = (UBYTE)CG_ROM1[offset++];
				}
			}
		}
		else {
			switch (*attribute) {
			case LST_INV_XXX_XXX:	/** 反転の場合 */
				for (pos = (UWORD)xc; pos < 1280; pos += 80) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = (UBYTE)~CG_ROM0[offset++];
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = (UBYTE)~CG_ROM0[offset++];
				}
				break;
			case LST_MES_XXX_XXX:	/** 網掛けの場合 */
				pos = (UWORD)xc;
				for (line = 0; line < 16; line++) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = (UBYTE)(CG_ROM0[offset++] | PrintMeshData[line]);
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = (UBYTE)(CG_ROM0[offset++] | PrintMeshData[line]);
					pos += 80;
				}
				break;
			default:				/** 修飾なしの場合 */
				for (pos = (UWORD)xc; pos < 1280; pos += 80) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = (UBYTE)CG_ROM0[offset++];
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = (UBYTE)CG_ROM0[offset++];
				}
			}
		}
	}
	else {														/* 漢字ﾌｫﾝﾄﾃｰﾌﾞﾙからﾌｫﾝﾄﾃﾞｰﾀを取得する時(JIS第2水準) */
		offset = 0;

		switch (*attribute) {
		case LST_INV_XXX_XXX:	/** 反転の場合 */
			for (pos = (UWORD)xc; pos < 1280; pos += 80) {
				/** 前半分のドットパターンを格納 */
				(*(image_buff + pos)) = ~Kanji2[address].FontData[offset++];
				/** 後半分のドットパターンを格納 */
				(*(image_buff + pos + 1)) = ~Kanji2[address].FontData[offset++];
			}
			break;
		case LST_MES_XXX_XXX:	/** 網掛けの場合 */
			pos = (UWORD)xc;
			for (line = 0; line < 16; line++) {
				/** 前半分のドットパターンを格納 */
				(*(image_buff + pos)) = (UBYTE)(Kanji2[address].FontData[offset++] | PrintMeshData[line]);
				/** 後半分のドットパターンを格納 */
				(*(image_buff + pos + 1)) = (UBYTE)(Kanji2[address].FontData[offset++] | PrintMeshData[line]);
				pos += 80;
			}
			break;
		default:				/** 修飾なしの場合 */
			for (pos = (UWORD)xc; pos < 1280; pos += 80) {
				/** 前半分のドットパターンを格納 */
				(*(image_buff + pos)) = Kanji2[address].FontData[offset++];
				/** 後半分のドットパターンを格納 */
				(*(image_buff + pos + 1)) = Kanji2[address].FontData[offset++];
			}
		}
	}
}
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)
/*************************************************************************
	module		:[全角１文字分の主走査２倍のフォントイメージデータ作成]
	function	:[
		1.全角１文字に対する任意の主走査２倍の１ラインのイメージデータを作成
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1998/9/1]
	auther		:[K.Kawata]
*************************************************************************/
#if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)
void  GetTwiceWordCharacterImage(
		UBYTE *string,			/* 展開する文字の先頭バイトのポインタ */
		UBYTE *attribute,		/* 展開する文字のアトリビュートの先頭バイトのポインタ */
		UWORD *image_buff,		/* 展開したイメージのバッファ */
		UBYTE xc)				/* 展開する文字のx座標 */
{
	UDWORD	address;	/* CGの全角文字フォントの先頭アドレス(17Bit)／漢字フォントテーブルの配列番号 */
	UWORD	offset;
	UWORD	pos;
	UWORD	high;		/* 展開する文字の上位バイト */
	UWORD	low;		/* 展開する文字の下位バイト */
	UBYTE	line;

	high = *string;
	low = *(string + 1);

#if (PRO_PANEL == KANJI)
	/* ワンタッチの表示を[]->絵文字に変更 By O.Kimoto 1998/01/22 */
	/** ICHOU追加 -- 指文字の印字（ワンタッチキーの表現のため）*/
	if (*string >= LCD_PICFONT && *(string + 1) == LCD_PICFONT_LOWER) {	/** 指文字の場合（アトリビュート処理はない）*/
		line = 0;
		pos = (UWORD)xc;
/*		for (line = 0; line < 16; line++) {*/	/* 1998/11/10 By M.Kuwahara */
		for (pos = (UWORD)xc; pos < 2048; pos += 128) {
			/** 前半分のドットパターンを格納 */
			(*(image_buff + pos))     = ~GetTwiceFontData((UBYTE)(LCD_PictureFontPattern[*string & 0xf][line] & 0xff));
			line++;
			/** 後半分のドットパターンを格納 */
			(*(image_buff + pos + 1)) = ~GetTwiceFontData((UBYTE)(LCD_PictureFontPattern[*string & 0xf][line] & 0xff));
			line++;
/*			pos += 128;	/*  By O.Kimoto 1998/11/06 *//* 1998/11/10 By M.Kuwahara */
		}
		return;
	}
#endif

	if (GetFontAddress(&address, high, low) == CG_ADDRESS) {	/* CGからﾌｫﾝﾄﾃﾞｰﾀを取得する時(JIS第1水準) */
		offset = (UWORD)(address & 0xFFFF);

		if (address & 0x10000L) {
			switch (*attribute) {
			case LST_INV_XXX_XXX:	/** 反転の場合 */
				for (pos = (UWORD)xc; pos < 2048; pos += 128) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = GetTwiceFontData((UBYTE)CG_ROM1[offset++]);
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = GetTwiceFontData((UBYTE)CG_ROM1[offset++]);
				}
				break;
			case LST_MES_XXX_XXX:	/** 網掛けの場合 */
				pos = (UWORD)xc;
				for (line = 0; line < 16; line++) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = ~GetTwiceFontData((UBYTE)(CG_ROM1[offset++] | PrintMeshData[line]));
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = ~GetTwiceFontData((UBYTE)(CG_ROM1[offset++] | PrintMeshData[line]));
					pos += 128;
				}
				break;
			default:				/** 修飾なしの場合 */
				for (pos = (UWORD)xc; pos < 2048; pos += 128) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = ~GetTwiceFontData(CG_ROM1[offset++]);
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = ~GetTwiceFontData(CG_ROM1[offset++]);
				}
			}
		}
		else {
			switch (*attribute) {
			case LST_INV_XXX_XXX:	/** 反転の場合 */
				for (pos = (UWORD)xc; pos < 2048; pos += 128) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = GetTwiceFontData((UBYTE)CG_ROM0[offset++]);
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = GetTwiceFontData((UBYTE)CG_ROM0[offset++]);
				}
				break;
			case LST_MES_XXX_XXX:	/** 網掛けの場合 */
				pos = (UWORD)xc;
				for (line = 0; line < 16; line++) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = ~GetTwiceFontData((UBYTE)(CG_ROM0[offset++] | PrintMeshData[line]));
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = ~GetTwiceFontData((UBYTE)(CG_ROM0[offset++] | PrintMeshData[line]));
					pos += 128;
				}
				break;
			default:				/** 修飾なしの場合 */
				for (pos = (UWORD)xc; pos < 2048; pos += 128) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = ~GetTwiceFontData(CG_ROM0[offset++]);
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = ~GetTwiceFontData(CG_ROM0[offset++]);
				}
			}
		}
	}
	else {							/* 漢字ﾌｫﾝﾄﾃｰﾌﾞﾙからﾌｫﾝﾄﾃﾞｰﾀを取得する時(JIS第2水準) */
		offset = 0;

		switch (*attribute) {
		case LST_INV_XXX_XXX:	/** 反転の場合 */
			for (pos = (UWORD)xc; pos < 2048; pos += 128) {
				/** 前半分のドットパターンを格納 */
				(*(image_buff + pos)) = GetTwiceFontData(Kanji2[address].FontData[offset++]);
				/** 後半分のドットパターンを格納 */
				(*(image_buff + pos + 1)) = GetTwiceFontData(Kanji2[address].FontData[offset++]);
			}
			break;
		case LST_MES_XXX_XXX:	/** 網掛けの場合 */
			pos = (UWORD)xc;
			for (line = 0; line < 16; line++) {
				/** 前半分のドットパターンを格納 */
				(*(image_buff + pos)) = ~GetTwiceFontData((UBYTE)(Kanji2[address].FontData[offset++] | PrintMeshData[line]));
				/** 後半分のドットパターンを格納 */
				(*(image_buff + pos + 1)) = ~GetTwiceFontData((UBYTE)(Kanji2[address].FontData[offset++] | PrintMeshData[line]));
				pos += 128;
			}
			break;
		default:				/** 修飾なしの場合 */
			for (pos = (UWORD)xc; pos < 2048; pos += 128) {
				/** 前半分のドットパターンを格納 */
				(*(image_buff + pos)) = ~GetTwiceFontData(Kanji2[address].FontData[offset++]);
				/** 後半分のドットパターンを格納 */
				(*(image_buff + pos + 1)) = ~GetTwiceFontData(Kanji2[address].FontData[offset++]);
			}
		}
	}
}
#endif

#elif (PRO_PRINT_TYPE == THERMAL)	/* HINOKI */
/*************************************************************************
	module		:[全角１文字分の主走査２倍のフォントイメージデータ作成]
	function	:[
		1.全角１文字に対する任意の主走査２倍の１ラインのイメージデータを作成
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[
		この関数は未使用ですよ。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/09/06]
	auther		:[石橋正和,渡辺一章]
*************************************************************************/
 #if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)
void  GetTwiceWordCharacterImage(
		UBYTE *string,			/* 展開する文字の先頭バイトのポインタ */
		UBYTE *attribute,		/* 展開する文字のアトリビュートの先頭バイトのポインタ */
		UWORD *image_buff,		/* 展開したイメージのバッファ *//* Change UBYTE to UWORD By O.Kimoto 1998/11/06 */
		UBYTE xc)				/* 展開する文字のx座標 */
{
	UDWORD	address;	/* CGの全角文字フォントの先頭アドレス(17Bit)／漢字フォントテーブルの配列番号 */
	UWORD	offset;
	UWORD	pos;
	UWORD	high;		/* 展開する文字の上位バイト */
	UWORD	low;		/* 展開する文字の下位バイト */
	UBYTE	line;

	high = *string;
	low = *(string + 1);

 #if (PRO_PANEL == KANJI)
	/* ワンタッチの表示を[]->絵文字に変更 By O.Kimoto 1998/01/22 */
	/** ICHOU追加 -- 指文字の印字（ワンタッチキーの表現のため）*/
	if (*string >= LCD_PICFONT && *(string + 1) == LCD_PICFONT_LOWER) {	/** 指文字の場合（アトリビュート処理はない）*/
		line = 0;
		for (pos = (UWORD)xc; pos < 1280; pos += 80) {
			/** 前半分のドットパターンを格納 */
			(*(image_buff + pos))     = GetTwiceFontData((UBYTE)(LCD_PictureFontPattern[*string & 0xf][line] & 0xff));
			line++;
			/** 後半分のドットパターンを格納 */
			(*(image_buff + pos + 1)) = GetTwiceFontData((UBYTE)(LCD_PictureFontPattern[*string & 0xf][line] & 0xff));
			line++;
		}
		return;
	}
 #endif

	if (GetFontAddress(&address, high, low) == CG_ADDRESS) {	/* CGからﾌｫﾝﾄﾃﾞｰﾀを取得する時(JIS第1水準) */
		offset = (UWORD)(address & 0xFFFF);

		if (address & 0x10000L) {
			switch (*attribute) {
			case LST_INV_XXX_XXX:	/** 反転の場合 */
				for (pos = (UWORD)xc; pos < 1280; pos += 80) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos))     = GetTwiceFontData((UBYTE)~CG_ROM1[offset++]);
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = GetTwiceFontData((UBYTE)~CG_ROM1[offset++]);
				}
				break;
			case LST_MES_XXX_XXX:	/** 網掛けの場合 */
				pos = (UWORD)xc;
				for (line = 0; line < 16; line++) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = GetTwiceFontData((UBYTE)(CG_ROM1[offset++] | PrintMeshData[line]));
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = GetTwiceFontData((UBYTE)(CG_ROM1[offset++] | PrintMeshData[line]));
					pos += 80;
				}
				break;
			default:				/** 修飾なしの場合 */
				for (pos = (UWORD)xc; pos < 1280; pos += 80) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos))     = GetTwiceFontData(CG_ROM1[offset++]);
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = GetTwiceFontData(CG_ROM1[offset++]);
				}
			}
		}
		else {
			switch (*attribute) {
			case LST_INV_XXX_XXX:	/** 反転の場合 */
				for (pos = (UWORD)xc; pos < 1280; pos += 80) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = GetTwiceFontData((UBYTE)~CG_ROM0[offset++]);
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = GetTwiceFontData((UBYTE)~CG_ROM0[offset++]);
				}
				break;
			case LST_MES_XXX_XXX:	/** 網掛けの場合 */
				pos = (UWORD)xc;
				for (line = 0; line < 16; line++) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = GetTwiceFontData((UBYTE)(CG_ROM0[offset++] | PrintMeshData[line]));
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = GetTwiceFontData((UBYTE)(CG_ROM0[offset++] | PrintMeshData[line]));
					pos += 80;
				}
				break;
			default:				/** 修飾なしの場合 */
				for (pos = (UWORD)xc; pos < 1280; pos += 80) {
					/** 前半分のドットパターンを格納 */
					(*(image_buff + pos)) = GetTwiceFontData(CG_ROM0[offset++]);
					/** 後半分のドットパターンを格納 */
					(*(image_buff + pos + 1)) = GetTwiceFontData(CG_ROM0[offset++]);
				}
			}
		}
	}
	else {							/* 漢字ﾌｫﾝﾄﾃｰﾌﾞﾙからﾌｫﾝﾄﾃﾞｰﾀを取得する時(JIS第2水準) */
		offset = 0;

		switch (*attribute) {
		case LST_INV_XXX_XXX:	/** 反転の場合 */
			for (pos = (UWORD)xc; pos < 1280; pos += 80) {
				/** 前半分のドットパターンを格納 */
				(*(image_buff + pos)) = GetTwiceFontData(~Kanji2[address].FontData[offset++]);
				/** 後半分のドットパターンを格納 */
				(*(image_buff + pos + 1)) = GetTwiceFontData(~Kanji2[address].FontData[offset++]);
			}
			break;
		case LST_MES_XXX_XXX:	/** 網掛けの場合 */
			pos = (UWORD)xc;
			for (line = 0; line < 16; line++) {
				/** 前半分のドットパターンを格納 */
				(*(image_buff + pos)) = GetTwiceFontData((UBYTE)(Kanji2[address].FontData[offset++] | PrintMeshData[line]));
				/** 後半分のドットパターンを格納 */
				(*(image_buff + pos + 1)) = GetTwiceFontData((UBYTE)(Kanji2[address].FontData[offset++] | PrintMeshData[line]));
				pos += 80;
			}
			break;
		default:				/** 修飾なしの場合 */
			for (pos = (UWORD)xc; pos < 1280; pos += 80) {
				/** 前半分のドットパターンを格納 */
				(*(image_buff + pos)) = GetTwiceFontData(Kanji2[address].FontData[offset++]);
				/** 後半分のドットパターンを格納 */
				(*(image_buff + pos + 1)) = GetTwiceFontData(Kanji2[address].FontData[offset++]);
				/* pos += 128; 不要 by O.Kimoto 1999/01/14 */
			}
		}
	}
}
 #endif
#endif

/*************************************************************************
	module		:[半角１文字分のフォントイメージデータ作成]
	function	:[
		1.半角１文字に対する任意の１ラインのイメージデータを作成
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/06/08]
	auther		:[石橋正和]
*************************************************************************/
void	GetByteCharacterImage(
		UBYTE ascii,			/* 展開する文字のアスキーコード */
		UBYTE attribute,		/* 展開する文字のアトリビュート */
		UBYTE *image_buff,		/* 展開したイメージのバッファ */
		/* UBYTE xc */			/* 展開する文字のx座標 */ /* 半角と全角が混在するためxiに変更(ANZU) 96/01/26 H.HIRAO */
		UBYTE xi)				/* 展開したイメージのx座標 */ /* 追加 (ANZU) 96/01/26 H.HIRAO */
{
	UWORD pos;
	UBYTE line;
 #if (PRO_PRINT_TYPE == THERMAL)
  #if defined (TWN)
	UWORD data;	/* added by H.Hirao 1999/03/11 */
  #endif
 #endif

	pos = (UWORD)xi;
	switch (attribute) {
	case LST_INV_XXX_XXX: /** 反転の場合 */
		for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
			*(image_buff + pos) = (UBYTE)~ByteFont[ascii][line];
			pos += 80;
		}
		break;
	case LST_MES_XXX_XXX: /** 網掛けの場合 */
		for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
			*(image_buff + pos) = (unsigned char)(ByteFont[ascii][line] | PrintMeshData[line]);
			pos += 80;
		}
		break;
 #if (PRO_PRINT_TYPE == THERMAL)
  #if defined (TWN)
  	/* added by H.Hirao 1999/03/11 */
	case LST_INV_TWI_XXX:
		for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
			data = GetTwiceFontData((UBYTE)~ByteFont[ascii][line]);
			*(image_buff + pos) = (UBYTE)((data & 0xFF00) >> 8);
			*(image_buff + pos + 1) = (UBYTE)(data & 0x00FF);
			pos += 80;
		}
		break;
	case LST_MES_TWI_XXX:
	case LST_XXX_TWI_XXX:
		for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
			data = GetTwiceFontData((UBYTE)ByteFont[ascii][line]);
			*(image_buff + pos) = (UBYTE)((data & 0xFF00) >> 8);
			*(image_buff + pos + 1) = (UBYTE)(data & 0x00FF);
			pos += 80;
		}
		break;
  #endif
 #endif
	default: /** 修飾なしの場合 */
		/* スピードアップのため、スペースの場合は、フォントテーブルをアクセスせずに直接０を格納します */
		if (ascii == ' ') { /** スペースの場合 */
			for (pos; pos < 1280; pos += 80) { /** ドットパターンを格納 */
				*(image_buff + pos) = 0;
			}
		}
		else {
			for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
				*(image_buff + pos) = ByteFont[ascii][line];
				pos += 80;
			}
		}
	}
}

#if (PRO_PRINT_TYPE == THERMAL_TRANS)
/*************************************************************************
	module		:[半角１文字分の主走査２倍のフォントイメージデータ作成]
	function	:[
		1.半角１文字に対する任意の主走査２倍の１ラインのイメージデータを作成
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/09/07]
	auther		:[石橋正和]
*************************************************************************/
void	GetTwiceByteCharacterImage(
		UBYTE ascii,			/* 展開する文字のアスキーコード */
		UBYTE attribute,		/* 展開する文字のアトリビュート */
		UWORD *image_buff,		/* 展開したイメージのバッファ */
		UBYTE xi)				/* 展開したイメージのx座標 */
{
	UWORD pos;
	UBYTE line;

	pos = (UWORD)xi;
	switch (attribute) {
	case LST_INV_TWI_XXX: /** 反転の場合 */
	case LST_INV_XXX_XXX: /** 反転の場合 */	/* 1998/09/17 By M.Kuwahara */
		for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
			*(image_buff + pos) = GetTwiceFontData((UBYTE)ByteFont[ascii][line]);
			pos += 128;
		}
		break;
	case LST_MES_TWI_XXX: /** 網掛けの場合 */
		for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
			*(image_buff + pos) = ~GetTwiceFontData((UBYTE)(ByteFont[ascii][line] | PrintMeshData[line]));
			pos += 128;
		}
		break;
	default: /** 修飾なしの場合 */
		if (ascii == ' ') { /** スペースの場合 */
			for (pos; pos < 2048; pos += 128) { /** ドットパターンを格納 */
				*(image_buff + pos) = 0xffff;
			}
		}
		else {
			for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
				*(image_buff + pos) = ~GetTwiceFontData((UBYTE)ByteFont[ascii][line]);
				pos += 128;
			}
		}
	}
}

#elif (PRO_PRINT_TYPE == THERMAL)
/*************************************************************************
	module		:[半角１文字分の主走査２倍のフォントイメージデータ作成]
	function	:[
		1.半角１文字に対する任意の主走査２倍の１ラインのイメージデータを作成
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/09/07]
	auther		:[石橋正和]
*************************************************************************/
void	GetTwiceByteCharacterImage(
		UBYTE ascii,			/* 展開する文字のアスキーコード */
		UBYTE attribute,		/* 展開する文字のアトリビュート */
		UWORD *image_buff,		/* 展開したイメージのバッファ *//* Change UBYTE to UWORD By O.Kimoto 1998/11/06 */
		UBYTE xi)				/* 展開したイメージのx座標 */
{

#if defined(TWN)	/* For TWN Debug By O.Kimoto 1999/02/03 */
	UWORD tmp_image;
#endif

	UWORD pos;
	UBYTE line;

	pos = (UWORD)xi;
	switch (attribute) {
	case LST_INV_TWI_XXX: /** 反転の場合 */

#if defined(TWN)	/* For TWN Debug By O.Kimoto 1999/02/03 */
		for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
			tmp_image = GetTwiceFontData((UBYTE)~ByteFont[ascii][line]);
			*(image_buff + pos    ) = GetTwiceFontData((UBYTE)((tmp_image & 0xff00) >> 8));
			*(image_buff + pos + 1) = GetTwiceFontData((UBYTE)(tmp_image & 0x00ff));
			pos += 80;
		}
		break;
#endif

	case LST_INV_XXX_XXX: /** 反転の場合 */	/* 1998/09/17 By M.Kuwahara */
		for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
			*(image_buff + pos) = GetTwiceFontData((UBYTE)~ByteFont[ascii][line]);
			pos += 80;
		}
		break;
	case LST_MES_TWI_XXX: /** 網掛けの場合 */
#if defined(TWN)
	case LST_XXX_TWI_XXX: /** 横倍角の場合 added by H.Hirao 1999/03/11 */
#endif
	/* ＨＩＮＯＫＩは網掛け文字をプリントすると非常に見にくいので、網掛けは行いません。 by O.Kimoto 1999/02/04 */
#if defined(TWN)	/* For TWN Debug By O.Kimoto 1999/02/03 */
		for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
			tmp_image = GetTwiceFontData((UBYTE)ByteFont[ascii][line]);
			*(image_buff + pos    ) = GetTwiceFontData((UBYTE)((tmp_image & 0xff00) >> 8));
			*(image_buff + pos + 1) = GetTwiceFontData((UBYTE)(tmp_image & 0x00ff));
			pos += 80;
		}
#else
		for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
			*(image_buff + pos) = GetTwiceFontData((UBYTE)ByteFont[ascii][line]);
			pos += 80;
		}
#endif

		break;
	default: /** 修飾なしの場合 */
		if (ascii == ' ') { /** スペースの場合 */
			for (pos; pos < 1280; pos += 80) { /** ドットパターンを格納 */
				*(image_buff + pos) = 0x0000;
			}
		}
		else {
			for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
				*(image_buff + pos) = GetTwiceFontData((UBYTE)ByteFont[ascii][line]);
				pos += 80;
			}
		}
	}
}
#else
/*************************************************************************
	module		:[半角１文字分の主走査２倍のフォントイメージデータ作成]
	function	:[
		1.半角１文字に対する任意の主走査２倍の１ラインのイメージデータを作成
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/09/07]
	auther		:[石橋正和]
*************************************************************************/
void	GetTwiceByteCharacterImage(
		UBYTE ascii,			/* 展開する文字のアスキーコード */
		UBYTE attribute,		/* 展開する文字のアトリビュート */
		UBYTE *image_buff,		/* 展開したイメージのバッファ */
		UBYTE xi)				/* 展開したイメージのx座標 */
{
	UWORD pos;
	UBYTE line;

	pos = (UWORD)xi;
	switch (attribute) {
	case LST_INV_TWI_XXX: /** 反転の場合 */
		for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
			*(image_buff + pos) = (UBYTE)((GetTwiceFontData((UBYTE)~ByteFont[ascii][line])) & 0x00ff);
			*(image_buff + pos + 1) = (UBYTE)(((GetTwiceFontData((UBYTE)~ByteFont[ascii][line])) & 0xff00) >> 8);
			pos += 80;
		}
		break;
	case LST_MES_TWI_XXX: /** 網掛けの場合 */
		for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
			*(image_buff + pos) = ((unsigned char)(GetTwiceFontData((unsigned char)ByteFont[ascii][line]) & 0x00ff)) | PrintMeshData[line];
			*(image_buff + pos + 1) = ((unsigned char)((GetTwiceFontData((unsigned char)(ByteFont[ascii][line])) & 0xff00) >> 8)) | PrintMeshData[line];
			pos += 80;
		}
		break;
	default: /** 修飾なしの場合 */
		if (ascii == ' ') { /** スペースの場合 */
			for (pos; pos < 1280; pos += 80) { /** ドットパターンを格納 */
				*(image_buff + pos) = 0;
				*(image_buff + pos + 1) = 0;
			}
		}
		else {
			for (line = 0; line < 16; line++) { /** ドットパターンを格納 */
				*(image_buff + pos) = (UBYTE)(GetTwiceFontData(ByteFont[ascii][line]) & 0x00ff);
				*(image_buff + pos + 1) = (UBYTE)((GetTwiceFontData(ByteFont[ascii][line]) & 0xff00) >> 8);
				pos += 80;
			}
		}
	}
}
#endif


/*************************************************************************
	module		:[１ラインフォントイメージデータ作成]
	function	:[
		1.文字列に対する任意の１ラインのイメージデータを作成
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[94/09/20 引数near→far]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/06/08]
	auther		:[石橋正和]
*************************************************************************/
void	GetOneLineCharacterImage(
		UBYTE *string,		/* 展開する文字列の先頭アドレス */
		UBYTE *attribute,	/* 展開する文字列アトリビュートの先頭アドレス */
		UBYTE *image_buff)	/* 展開したイメージのバッファ */
{
	UBYTE xc;
	UBYTE xi = 0; /* 追加(ANZU) 96/01/26 H.HIRAO */

	for (xc = 0; xc < 80; xc++) {
#if (PRO_PANEL == KANJI) || ( PRO_JIS_CODE == ENABLE ) /* For ANZU By S.K Dec.16,1995 */
		/* ポプラでJIS第２水準の漢字も一部追加になったため、先頭アドレスも
		** 0x81～0x9Fと0xE0～0xECの２ヶ所の判断が必要になるので判断を変更します
		** by K.Watanabe 1997/04/10
		*/
/*		if (*string >= WORD_CHARACTER_MIN && *string <= WORD_CHARACTER_MAX) {	/** 全角の場合(第1水準) */
		if (CheckShiftJISCode(*string, *(string + 1))) {	/** 全角の場合（ｼﾌﾄJIS第1・第2水準） */
			GetWordCharacterImage(string, attribute, image_buff, xc);
			xc++;		/* x座標を半角分進める */
			xi += 2;	/* 追加 97/01/30 M.Kuwahara */
			string++;
			attribute++;
		}
#if (PRO_PANEL == KANJI)
 		/* ワンタッチの表示を[]->絵文字に変更 By O.Kimoto 1998/01/22 */
		else if (*string >= LCD_PICFONT && *(string + 1) == LCD_PICFONT_LOWER) {
			GetWordCharacterImage(string, attribute, image_buff, xc);
			xc++;		/* x座標を半角分進める */
			xi += 2;	/* 追加 97/01/30 M.Kuwahara */
			string++;
			attribute++;
		}
#endif

		else {																	/** 半角の場合 */
#endif /* KANJI */
/*#if (PRO_PANEL == ANK) /* For ANZU by h.hirao 96/01/29 */
			if (xi >= 80) { /* イメージの中身が640dotになれば抜ける */ /* 以下１７行追加(ANZU) 96/01/26 H.HIRAO */
				break;
			}
			switch (*attribute) { /* とりあえずアンズのリストに用いる属性はこれだけ、必要に応じて付け加えてください */
			case LST_XXX_TWI_XXX: /* 横倍角 */
			case LST_INV_TWI_XXX: /* 横倍角+反転 */
			case LST_MES_TWI_XXX: /* 横倍角+網掛け */

#if (0)
** /* ＨＩＮＯＫＩのＴＷＮで、半角文字を横４倍／縦２倍にする必要がある。 By O.Kimoto 1999/02/03 */
** #if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/09/11 By M.Kuwahara */
** 				GetTwiceByteCharacterImage(*string, *attribute, (UWORD *)&image_buff ,xi);
** /*				GetTwiceByteCharacterImage(*string, *attribute, image_buff ,xi);*/
** #else
** 				GetTwiceByteCharacterImage(*string, *attribute, image_buff ,xi);
** #endif
#else
 #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1998/09/11 By M.Kuwahara */
				GetTwiceByteCharacterImage(*string, *attribute, (UWORD *)&image_buff ,xi);
 #elif (PRO_PRINT_TYPE == THERMAL)	/* 1998/09/11 By M.Kuwahara */
  #if defined (TWN)
  				/* by H.Hirao 1999/03/11 */
				if (*string == ' ') {
					if (*attribute == LST_INV_TWI_XXX) {
						*attribute = LST_INV_XXX_XXX;
					}
					else if (*attribute == LST_MES_TWI_XXX) {
						*attribute = LST_MES_XXX_XXX;
					}
					else if (*attribute == LST_XXX_TWI_XXX) {
						*attribute = LST_NOT;
					}
					else {
					}
					GetByteCharacterImage(*string, *attribute, image_buff, xi);
					xi ++;
				}
				else {
					GetByteCharacterImage(*string, *attribute, image_buff, xi);
					xi += 2;
				}
  #else
				GetTwiceByteCharacterImage(*string, *attribute, (UWORD *)image_buff ,xi);
  #endif
  #if (0)	/* defined(TWN) comment by H.Hirao 1999/03/11 */
  //			xi += 2; /* 座標を全角分進める */
  #endif
 #else
				GetTwiceByteCharacterImage(*string, *attribute, image_buff ,xi);
 #endif

#endif
 #if (PRO_PRINT_TYPE == THERMAL)
  #if defined (TWN)
				/* スペースは半角にします by H.Hirao 1999/03/11 */
  #else
				xi += 2; /* 座標を全角分進める */
  #endif
 #else
				xi += 2; /* 座標を全角分進める */
 #endif
				break;
			default:
				if (xc != xi) { /* 横倍角と半角が同じ行にある時、キャラクタ列とイメージ列をあわせる */
					string = string + (xi - xc);
					attribute = attribute + (xi - xc);
					xc = xi;
				}
				GetByteCharacterImage(*string, *attribute, image_buff, xi);
				xi++; /* 座標を半角分進める */
				break;
			}
/*#endif /* ANK */
#if (PRO_PANEL == KANJI) || ( PRO_JIS_CODE == ENABLE ) /* For ANZU By S.K Dec.16,1995 */
		}
#endif /* KANJI */
		string++;
		attribute++;
	}
}


#if (PRO_PRINT_TYPE == THERMAL_TRANS)
/*************************************************************************
	module		:[主走査２倍の１ラインフォントイメージデータ作成]
	function	:[
		1.文字列に対する任意の主走査２倍の１ラインのイメージデータを作成
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyward		:[LST]
	date		:[1998/9/1]
	auther		:[K.Kawata]
*************************************************************************/
void GetOneTwiceLineCharacterImage(
		UBYTE *string,		/* 展開する文字列の先頭アドレス */
		UBYTE *attribute,	/* 展開する文字列アトリビュートの先頭アドレス */
		UWORD *image_buff)	/* 展開したイメージのバッファ */
{
UBYTE xc;

#if (PRO_PANEL == KANJI) || ( PRO_JIS_CODE == ENABLE )
	for (xc = 0; xc < 80; xc ++) {
		if (CheckShiftJISCode(*string, *(string + 1))) {	/* 全角の場合（ｼﾌﾄJIS第1・第2水準） */
			GetTwiceWordCharacterImage(string, attribute, image_buff, xc);
			xc++;	/* x座標を半角分進める */
			string++;
			attribute++;
		}

#if (PRO_PANEL == KANJI)
	/* ワンタッチの表示を[]->絵文字に変更 By O.Kimoto 1998/01/22 */
	/** ICHOU追加 -- 指文字の印字（ワンタッチキーの表現のため）*/
		else if (*string >= LCD_PICFONT && *(string + 1) == LCD_PICFONT_LOWER) {/* ワンタッチの表示を絵文字 */
			GetTwiceWordCharacterImage(string, attribute, image_buff, xc);
			xc++;	/* x座標を半角分進める */
			string++;
			attribute++;
		}
#endif

		else { /* 半角の場合 */
			GetTwiceByteCharacterImage(*string, *attribute, image_buff, xc);
		}
		string++;
		attribute++;
	}
#endif

}

#elif (PRO_PRINT_TYPE == THERMAL)	/* HINOKI */
/*************************************************************************
	module		:[主走査２倍の１ラインフォントイメージデータ作成]
	function	:[
		1.文字列に対する任意の主走査２倍の１ラインのイメージデータを作成
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyward		:[LST]
	date		:[1998/9/1]
	auther		:[K.Kawata]
*************************************************************************/
void GetOneTwiceLineCharacterImage(
		UBYTE *string,		/* 展開する文字列の先頭アドレス */
		UBYTE *attribute,	/* 展開する文字列アトリビュートの先頭アドレス */
		UWORD *image_buff)	/* 展開したイメージのバッファ *//* Change UBYTE to UWORD By O.Kimoto 1998/11/06 */
{
	UBYTE xc;
#if defined(TWN)	/* for TWN Debug by O.Kimoto 1999/02/04 */
	UBYTE xc_sub;

	/* TWNのList Printで、倍角文字を含む行の後ろの罫線が消える不具合対策 2002/09/30 T.Takagi */
	UBYTE *tmp_string;
	UBYTE *tmp_attribute;	

	tmp_string = string;
	tmp_attribute = attribute;
#endif
#if (PRO_PANEL == KANJI) || ( PRO_JIS_CODE == ENABLE )
	for (xc = 0; xc < 80; xc ++) {
		if (CheckShiftJISCode(*string, *(string + 1))) {	/* 全角の場合（ｼﾌﾄJIS第1・第2水準） */
			GetTwiceWordCharacterImage(string, attribute, image_buff, xc);
			xc++;	/* x座標を半角分進める */
			string++;
			attribute++;
		}

 #if (PRO_PANEL == KANJI)
	/* ワンタッチの表示を[]->絵文字に変更 By O.Kimoto 1998/01/22 */
	/** ICHOU追加 -- 指文字の印字（ワンタッチキーの表現のため）*/
		else if (*string >= LCD_PICFONT && *(string + 1) == LCD_PICFONT_LOWER) {/* ワンタッチの表示を絵文字 */
			GetTwiceWordCharacterImage(string, attribute, image_buff, xc);
			xc++;	/* x座標を半角分進める */
			string++;
			attribute++;
		}
 #endif

		else { /* 半角の場合 */
			GetTwiceByteCharacterImage(*string, *attribute, image_buff, xc);
		}
		string++;
		attribute++;
	}
#else
	/* PRO_JIS_CODE == DISABLE by O.Kimoto 1999/02/02 */
 #if defined(TWN)	/* for TWN Debug by O.Kimoto 1999/02/04 */
	xc_sub = 0;
	for (xc = 0; xc < 80, xc_sub < 80; xc ++) {
		if ((*string >= 0x15) && (*string <= 0x1F)) {	/* 罫線文字かどうか？ */
			GetTwiceByteCharacterImage(*string, *attribute, image_buff, xc);
		}
		else if (*string == ' ') {
			if (*attribute == LST_INV_TWI_XXX) {
				*attribute = LST_INV_XXX_XXX;
			}
			else if (*attribute == LST_MES_TWI_XXX) {
				*attribute = LST_MES_XXX_XXX;
			}
			else if (*attribute == LST_XXX_TWI_XXX) {
				*attribute = LST_NOT;
			}
			else {
			}
			GetTwiceByteCharacterImage(*string, *attribute, image_buff, xc_sub);
		}
		else {
			GetTwiceByteCharacterImage(*string, *attribute, image_buff, xc_sub);
		}
 #if (0)
 //		if ((*attribute == LST_INV_TWI_XXX) || (*attribute == LST_MES_TWI_XXX)) {
 #else
		if ((*attribute == LST_INV_TWI_XXX) || (*attribute == LST_MES_TWI_XXX) || (*attribute == LST_XXX_TWI_XXX)) {
 #endif
			if (*string != ' ') {	/* スペースの場合は、横２倍（実際は４倍）はしません。*/
				xc_sub ++;
			}
		}
		string++;
		attribute++;
		xc_sub ++;
	}

	/* TWNのList Printで、倍角文字を含む行の後ろの罫線が消える不具合 2002/09/30 T.Takagi **
    ** 上のfor loopで、罫線がスペースで上書きされていたので、もう一度ここで展開する。    */
	for (xc = 0; xc < 80; xc ++) {
		if ((*tmp_string >= 0x15) && (*tmp_string <= 0x1F)) {	/* 罫線文字かどうか？ */
			GetTwiceByteCharacterImage(*tmp_string, *tmp_attribute, image_buff, xc);
		}
		tmp_string++;
		tmp_attribute++;
	}
 #else /* !TWN */
	for (xc = 0; xc < 80; xc ++) {
		GetTwiceByteCharacterImage(*string, *attribute, image_buff, xc);
		string++;
		attribute++;
	}
 #endif	/* end of defined (TWN) */
#endif
}

#endif

/*************************************************************************
	module		:[キャラクタ、イメージプリント]
	function	:[
		1.引数に応じてオープン、プリント、クローズ等を行う
	]
	return		:[エラーの有無]
	common		:[なし]
	condition	:[]
	comment		:[リストプリントの上位関数がSATSUKI/LAVENDARと共通のため、このような
					ソースの構造となっている
					なぜ引数でswitch/caseさせるのか?
					別々の関数とするべき
					引数のビットアサインは余分な処理が全体に及ぶ
	]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/06/08]
	auther		:[石橋正和]
*************************************************************************/
WORD	CharacterPrint(
		UBYTE mode)		/* モード */
{
	UBYTE print_mode;
	WORD result;

	print_mode = (UBYTE)(mode & 0xF0);

	if (mode == (LST_PRINT | LST_ERR_CLOSE_NOT)) { /** リストプリントランでエラーが起こってもクローズしない場合 */
		print_mode = LST_PRINT_ERR_CLOSE_NOT;
	}
	else if ((mode & 0xF8) == (LST_LINE_FEED | LST_ERR_CLOSE_NOT)) { /** 改行でエラーが起こってもクローズしない場合 */
		print_mode = LST_LINE_FEED_ERR_CLOSE_NOT;
	}

	switch (print_mode) {
	case LST_PRE_OPEN:			/** プリOPEN */
		result = OK;
		break;
	case LST_OPEN:				/** プリントOPEN */
		result = ListOpen();
		break;
	case LST_PRINT:				/** プリントRUN */
		result = ListPrintRun();
		break;
	case LST_PRINT_ERR_CLOSE_NOT: /** プリントRUN(エラー処理なし) */
		ListPrintRunWithoutError();
		result = OK;
		break;
	case LST_LINE_FEED:			/** 改行 */
		result = ListLineFeed((UBYTE)(mode & 0x07));
		break;
	case LST_LINE_FEED_ERR_CLOSE_NOT:/** 改行(エラー処理なし) */
		ListLineFeedWithoutError((UBYTE)(mode & 0x07));
		result = OK;
		break;
	case LST_IMAGE_PRINT:		/** イメージプリントRUN（テストプリント） */
		result = ListImagePrint();
		break;
	case LST_CLOSE:				/** プリントCLOSE */
		result = ListClose();
		break;
	case LST_PRE_CLOSE:			/** プリCLOSE */
		result = OK;
		break;
	}

#if (0) /* 紅葉 */
//	switch (print_mode) {
//	case LST_PRE_OPEN:			/** プリOPEN */
//		result = ListPreOpen();
//		break;
//	case LST_OPEN:				/** プリントOPEN */
//		result = ListOpen();
//		break;
//	case LST_PRINT:				/** プリントRUN */
//	case LST_LINE_FEED:			/** 改行 */
//	case LST_IMAGE_PRINT:		/** イメージプリントRUN（テストプリント） */
//		if ( (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_LIST_PRINT) != 0 ) {
//			/** ストップキーが押された場合 */
//			result = MSG_PRN_LST_STOPSW_ON;
//		}
//		else {
//			switch (print_mode) {
//			case LST_PRINT:				/** プリントRUN */
//				result = ListPrintRun();
//				break;
//			case LST_LINE_FEED:			/** 改行 */
//				result = ListLineFeed((UBYTE)(mode & 0x07));
//				break;
//			case LST_IMAGE_PRINT:		/** イメージプリントRUN（テストプリント） */
//				result = ListImagePrint();
//				break;
//			}
//		}
//		if ( (print_mode & LST_ERR_CLOSE_NOT) == 0 && result != PRN_OK ) {
//			/** エラー発生時にクローズするモードで、結果がOKでない場合 */
//			if ( result == MSG_PRN_LST_STOPSW_ON ) { /* ストップキーが押された場合 */
//				ListClose();
//			}
//			else {
//				result = ListClose();
//			}
//		}
//		break;
//	case LST_CLOSE:				/** プリントCLOSE */
//		result = ListClose();
//		break;
//	case LST_PRE_CLOSE:			/** プリCLOSE */
//		result = ListPreClose();
//		break;
//	}
#endif
	return(result);
}

/*************************************************************************
	module		:[文字列修飾セット]
	function	:[文字列とその修飾をセットする。]
	common		:[]
	condition	:[
	]
	commment	:[H8と同じ関数として定義(上位関数が共通のため)
	]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/06/13]
	author		:[石橋正和]
*************************************************************************/
void	AttributeSet(
		register UBYTE *prn_string,		/* 印刷文字列 */
		register UBYTE *att_string,		/* 修飾文字列 */
		CONST UBYTE *set_string,	/* ｾｯﾄ元文字列 */
		UBYTE attribute )				/* 修飾 */
{
	UWORD	length;

	CMN_StringCopy(prn_string, set_string);

	length = CMN_StringLength(set_string);
	CMN_MemorySet(att_string, length, attribute);
}

/*************************************************************************
	module		:[用紙種類別、印刷可能行数]
	function	:[
		1.用紙種類毎の印刷可能行数
	]
	common		:[]
	condition	:[]
	commment	:[
		この関数はプリントのオープンが行われた後でしか、有効でない。
		H8と同じ関数として定義(上位関数が共通のため)。

		#if (PRO_PAPER_TYPE == CUT_PAPER)
		この上の条件コンパイル削除します 1997/11/12 Y.Matsukuma
	]
	return		:[印刷可能行数]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/06/15]
	author		:[豊田浩子]
*************************************************************************/
UBYTE		PaperSizeLen(void)
{
	if (CHK_UNI_ListFormat3x3()) {
		switch ( PaperKind() ) {
		case	SYS_LT_PAPER:
			return ( LST_LETTER_LEN_75 );
			break;
		case	SYS_B4_PAPER:
			return ( LST_B4_LEN_75 );
			break;
		case	SYS_LG_PAPER:
			return ( LST_LEGAL_LEN_75 );
			break;
		case	SYS_A3_PAPER:
			return ( LST_A3_LEN_75 );
			break;
		case	SYS_A4R_PAPER:
			return ( LST_A4R_LEN_75 );
			break;
		case	SYS_B5_PAPER:
			return ( LST_B5_LEN_75 );
			break;
		case	SYS_A5_PAPER:
			return ( LST_A5_LEN_75 );
			break;
		case	SYS_A5R_PAPER:
			return ( LST_A5R_LEN_75 );
			break;
		case	SYS_B5R_PAPER:
			return ( LST_B5R_LEN_75 );
			break;
		default:					/*上記以外は全てA4とする*/
			return ( LST_A4_LEN_75 );
			break;
		}
		return ( LST_A4_LEN_75 );
	}
	else {
		switch ( PaperKind() ) {
		case	SYS_LT_PAPER:
			return ( LST_LETTER_LEN );
			break;
		case	SYS_B4_PAPER:
			return ( LST_B4_LEN );
			break;
		case	SYS_LG_PAPER:
			return ( LST_LEGAL_LEN );
			break;
		case	SYS_A3_PAPER:
			return ( LST_A3_LEN );
			break;
		case	SYS_A4R_PAPER:
			return ( LST_A4R_LEN );
			break;
		case	SYS_B5_PAPER:
			return ( LST_B5_LEN );
			break;
		case	SYS_A5_PAPER:
			return ( LST_A5_LEN );
			break;
		case	SYS_A5R_PAPER:
			return ( LST_A5R_LEN );
			break;
		case	SYS_B5R_PAPER:
			return ( LST_B5R_LEN );
			break;
		default:					/*上記以外は全てA4とする*/
			return ( LST_A4_LEN );
			break;
		}
		return ( LST_A4_LEN );
	}
}

/*************************************************************************
	module		:[用紙種類]
	function	:[
		1.用紙種類
	]
	common		:[]
	condition	:[]
	commment	:[
		この関数はプリントのオープンが行われた後でしか、有効でない。
	]
	return		:[用紙種類-SYS_A4_PAPERなど]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/06/15]
	author		:[豊田浩子]
*************************************************************************/
UBYTE		PaperKind(void)		/*なし*/
{
	UBYTE	i;			/*work*/

#if (PRO_PAPER_TYPE == CUT_PAPER)  /* KIRI */
 #if defined(STOCKHM2)		/* Added by SMuratec K.W.Q 2004/03/29 */
	i = SYS_Paper1Size;
 #else
	i = SelectedPaper;
 #endif
#else	/*ﾛｰﾙﾍﾟｰﾊﾟｰ*/
	i = SYS_Paper1Size;
#endif
	return ( i );
}
