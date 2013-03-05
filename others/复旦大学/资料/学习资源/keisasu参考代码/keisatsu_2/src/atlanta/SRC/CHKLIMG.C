/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_IMG.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: テストパターンプリント
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\mntsw_h.h"	/* SYB_MaintenanceSwitch[H] */
#include "\src\atlanta\define\std.h"

#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\lst_def.h"

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\lst_pro.h"
#include "\src\atlanta\define\mon_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"		/* SYB_MaintenanceSwitch */
#include "\src\atlanta\ext_v\lst_data.h"

#if (PRO_PRINT_TYPE == LED)
#include "\src\atlanta\prt\ph3\ext_v\prn_data.h"
#include "\src\atlanta\prt\ph3\ext_v\prn_tbl.h"
#endif

#if (PRO_PRINT_TYPE == LASER)
#include "\src\atlanta\prt\sp322\ext_v\prn_data.h"
#include "\src\atlanta\prt\sp322\ext_v\prn_tbl.h"
#endif

WORD	PrintLinePattern2(void);
WORD	PrintVariousPattern(UBYTE);

CONST UBYTE	DEBUG_Pattern = 0;
CONST UBYTE	TestPattern1Page = 2;	/* 0:連続  1:1枚  2:複合(大分要求) */
CONST UBYTE	LED_Pattern = 0;		/* 0:通常  1:2回繰り返し */

/*************************************************************************
	module		:[格子パターン印刷]
	function	:[格子パターンを1枚印刷する
	]
	return		:[印刷結果]
	common		:[]
	condition	:[]
	commment	:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/07/20]
	author		:[石橋正和]
*************************************************************************/
WORD			PrintKoushiPattern(void)
{
	UBYTE flag;		/* 黒/白反転フラグ */
	WORD result;			/* 実行結果 */
	UWORD i;
	UBYTE line;
	UWORD trans_time = 0;
	UWORD total_trans_time; /* 全転送回数 */
#if (PRO_PRINT_TYPE == LASER)	/* 1998/02/12 Y.Matsukuma */
	UWORD paper_width; /** 紙幅 by H.H 1996/11/15 */
#endif

	flag = 0;
	
	if ((result = CharacterPrint(LST_OPEN)) != OK) { /** リストオープン */
		return (result);
	}

	/* 以降 LST_A4_WORD_WIDTH -> LST_WORD_WIDTHに変更　1996/12/10 By M.Tachibana */

	/** G/Aの仕様により、白ﾃﾞｰﾀを9ﾗｲﾝ転送する */ /* For ANZU By H.Hirao 1996/04/04 */
	CMN_WordMemorySet( &FontImageBuffer.HeadImage[0], LST_WORD_WIDTH, 0); /** 白ﾃﾞｰﾀをいれる */
	for ( i = 0; i < 9; i++ ) { /** 9ﾗｲﾝ転送 */
		result = ListHeadPrint();
		if ( result != OK ) {
			return (result);
		}
	}
	
	/**	9ﾗｲﾝ分差し引く Add By H.Hirao 1996/06/10	*/
	total_trans_time = (PRN_PrintClockCounter[SelectedPaper][VARTICAL] - 9)/4;	/* For ANZU By H.Hirao 1996/04/04 */
	/*total_trans_time = PRN_PrintClockCounter[SelectedPaper][VARTICAL]/4;*/
	total_trans_time--;		/* add by M.Tachibana 1996/12/16 */

#if (PRO_PRINT_TYPE == LASER)	/* 1998/02/12 Y.Matsukuma */
		if ( (PRN_PrintClockCounter[SelectedPaper][HORIZONTAL] >> 4) <= LST_A4_WORD_WIDTH ) {
			/**
			*** ４ビット右シフトさせてるのは、ビット単位をワード単位に変更している
			**/
			paper_width = PRN_PrintClockCounter[SelectedPaper][HORIZONTAL] >> 4;
		}
		else {
			paper_width = LST_A4_WORD_WIDTH;
		}
#endif

	while(1) { /** ページの終わりまでループ */
		/** イメージバッファにデータをセット */ /* LST_A3_WORD_WIDTH -> LST_A4_WORD_WIDTH (杏）By H.Hirao 1996/02/23 */
		CMN_WordMemorySet( &FontImageBuffer.Image[0][0], (LST_WORD_WIDTH << 2), 0); /** 4倍する */
#if (PRO_PRINT_TYPE == LASER)	/* 1998/02/12 Y.Matsukuma */
		if (flag == 0) {
			for (line = 0; line < 4; line++) {
				for (i = 0; i < paper_width; i+= 16) {
					CMN_WordMemorySet( (&FontImageBuffer.Image[line][0] + i), 8, 0xFFFF); /** ビットアサインだから 8*16 dotのデータ */
				}
			}
		}
		else {
			for (line = 0; line < 4; line++) {
			/*	for (i = 8; i < (LST_A4_WORD_WIDTH - 8); i+= 16) { @* For ANZU By H.Hirao 1996/02/23 */
				for (i = 8; i < (paper_width - 8); i+= 16) {
					CMN_WordMemorySet( (&FontImageBuffer.Image[line][0] + i), 8, 0xFFFF);
				}
			}
		}
#else
		if (flag == 0) {
			for (line = 0; line < 4; line++) {
#if (PRO_PRINTER == DPI400)			/* 1998/03/04 By M.Kuwahara */
				for (i = 0; i < LST_WORD_WIDTH; i+= 16) {
					CMN_WordMemorySet( (&FontImageBuffer.Image[line][0] + i), 8, 0xFFFF); /** ビットアサインだから 8*16 dotのデータ */
				}
#else
				for (i = 0; i < LST_WORD_WIDTH; i+= 8) {
					CMN_WordMemorySet( (&FontImageBuffer.Image[line][0] + i), 4, 0xFFFF); /** ビットアサインだから 4*16 dotのデータ */
				}
#endif
			}
		}
		else {
			for (line = 0; line < 4; line++) {
			/*	for (i = 8; i < (LST_A4_WORD_WIDTH - 8); i+= 16) { @* For ANZU By H.Hirao 1996/02/23 */
#if (PRO_PRINTER == DPI400)			/* 1998/03/04 By M.Kuwahara */
				for (i = 8; i < LST_WORD_WIDTH; i+= 16) {
					CMN_WordMemorySet( (&FontImageBuffer.Image[line][0] + i), 8, 0xFFFF);
				}
#else
				for (i = 4; i < LST_WORD_WIDTH; i+= 8) {
					CMN_WordMemorySet( (&FontImageBuffer.Image[line][0] + i), 4, 0xFFFF);
				}
#endif
			}
		}
#endif
		/** 128(4*32)ライン分ループ(縦に1格子プリント) */
		for (i = 0; i < 32; i++) {
		/*	result = CharacterPrint(LST_IMAGE_PRINT);	*/
			result = ListImagePrint();
			if (result != OK) { /** エラーが起こればリターン */
				return(result);
			}
			trans_time++;
			if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
				return(ListClose()); /** プリンタをクローズする */
			}
		}
		flag ^= 1;
	}
}


/*************************************************************************
	module		:[升目パターン印刷]
	function	:[升目パターンを印刷する]
	return		:[印刷結果]
	common		:[
	]
	condition	:[]
	commment	:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/08/20]
	author		:[石橋正和]
*************************************************************************/
WORD			PrintMasumePattern(void)
{
	WORD result;		/* 実行結果 */
	/* UWORD val[4][2]; */		/* 対角線を書く前の値を保存しておく */
	/* UWORD offset[4][2]; */	/* 対角線を書く配列のオフセット */
	UWORD *address3;
	UWORD total_trans_time;
	UWORD trans_time = 0;
	UWORD i;
	UBYTE line;
	UBYTE first_flag;
	UWORD paper_width; /* 紙幅 by H.H 1996/11/15 */
	/* UWORD a; */
	/* UWORD b; */
	/* **********************
	 プリントする対角線を
		y = (a/b)x
		y = a -(a/b)x
		とする
	********************** */
	
	address3 = (UWORD *)&FontImageBuffer.Image[3][0];
	
	if ((result = CharacterPrint(LST_OPEN)) != OK) { /** リストオープン */
		return (result);
	}

	/* 以降 LST_A4_WORD_WIDTH -> LST_WORD_WIDTHに変更　1996/12/10 By M.Tachibana */

	/** LST_OPENしてからでないとSelectedPaperはきまらない 1997/05/09 */
	/** コーデックの性能制限により、紙幅は、304ワードなので、それ以上の紙幅は、設定できません */
#if (PRO_PRINT_TYPE == LASER)
	if ( (PRN_PrintClockCounter[SelectedPaper][HORIZONTAL] >> 4) <= LST_WORD_WIDTH ) {
		/**
		*** ４ビット右シフトさせてるのは、ビット単位をワード単位に変更している
		**/
		paper_width = PRN_PrintClockCounter[SelectedPaper][HORIZONTAL] >> 4;
	}
	else {
		paper_width = LST_WORD_WIDTH;
	}
#endif
#if (PRO_PRINT_TYPE == LED)
	paper_width = LST_WORD_WIDTH;
#endif

	/** G/Aの仕様により、白ﾃﾞｰﾀを9ﾗｲﾝ転送する */ /* For ANZU By H.Hirao 1996/04/04 */
	CMN_WordMemorySet( &FontImageBuffer.HeadImage[0], LST_WORD_WIDTH, 0); /** 白ﾃﾞｰﾀをいれる */
	for ( i = 0; i < 9; i++ ) { /** 9ﾗｲﾝ転送 */
		result = ListHeadPrint();
		if ( result != OK ) {
			return (result);
		}
	}

	/** イメージバッファにデータをセット */
#if (PRO_PRINT_TYPE == LASER)	/* 1998/02/13 Y.Matsukuma */
	CMN_WordMemorySet( &FontImageBuffer.Image[0][0], (paper_width - 16), 0xFFFF);
	CMN_WordMemorySet( &FontImageBuffer.Image[1][0], 3*(LST_WORD_WIDTH), 0);
	for (line = 1; line < 4; line++) {
		FontImageBuffer.Image[line][0] = 0x0080;
		for (i = 15; i < (paper_width - 15); i+= 16) {
			FontImageBuffer.Image[line][i] = 0x0100;
		}
	}
#else
/*	CMN_WordMemorySet( &FontImageBuffer.Image[0][0], (LST_A4_WORD_WIDTH - 16), 0xFFFF); @* For ANZU By H.Hirao 1996/02/23 */
/*	CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0xFFFF);	@* 97/08/12 For POPLAR By M.Kuwahara */
	CMN_WordMemorySet( &FontImageBuffer.Image[0][0], paper_width, 0xFFFF);
	CMN_WordMemorySet( &FontImageBuffer.Image[1][0], 3*(LST_WORD_WIDTH), 0);
	for (line = 1; line < 4; line++) {
		FontImageBuffer.Image[line][0] = 0x0080;

	/*	for (i = 15; i < (LST_A4_WORD_WIDTH - 15); i+= 16) { @* For ANZU By H.Hirao 1996/02/23 */
/*		for (i = 15; i < LST_WORD_WIDTH; i+= 16) {	@* 97/08/12 By M.Kuwahara */
 #if (PRO_PRINTER == DPI400)			/* 1998/03/04 By M.Kuwahara */
		for (i = 15; i < paper_width; i+= 16) {
			FontImageBuffer.Image[line][i] = 0x0100;
		}
 #else
		for (i = 7; i < paper_width; i+= 8) {
			FontImageBuffer.Image[line][i] = 0x0100;
		}
 #endif
		/* SetDiagonalLine(offset, val, a, b, column, line); */ /** 対角線のセット */
	}
#endif

	/**	9ﾗｲﾝ分差し引く Add By H.Hirao 1996/06/10	*/
	total_trans_time = (PRN_PrintClockCounter[SelectedPaper][VARTICAL] - 9)/4;	/* For ANZU By H.Hirao 1996/04/04 */
	/*total_trans_time = PRN_PrintClockCounter[SelectedPaper][VARTICAL]/4;*/
	total_trans_time--;		/* add by M.Tachibana 1996/12/16 */


#if (0)	/*defined(POPLAR_B)*/	/* By M.Tachibana 1997/12/03 */
	/*--------------------------------------------------------------------
	**	テスト用
	*/
	if (SYB_MaintenanceSwitch[MNT_SW_H0] != 0) {
		switch (SYB_MaintenanceSwitch[MNT_SW_H0] & 0x7f) {
		case 0x01:
			CMN_WordMemorySet(&FontImageBuffer.Image[0][0], LST_WORD_WIDTH*4, 0x0000);
			CMN_WordMemorySet(&FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0xFFFF);
			break;
		case 0x02:
		/*	CMN_WordMemorySet(&FontImageBuffer.Image[0][0], LST_WORD_WIDTH*4, 0xcccc); */
			CMN_WordMemorySet(&FontImageBuffer.Image[0][0], LST_WORD_WIDTH*4, 0x8888);
			break;
		case 0x04:
			CMN_WordMemorySet(&FontImageBuffer.Image[0][0], LST_WORD_WIDTH*4, 0x0000);
			CMN_WordMemorySet(&FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0xFFFF);
			CMN_WordMemorySet(&FontImageBuffer.Image[2][0], LST_WORD_WIDTH, 0xFFFF);
			break;
		case 0x03:
			CMN_WordMemorySet(&FontImageBuffer.Image[0][0], LST_WORD_WIDTH*4, 0x0000);
			for (i = 0; i < 4; i++) {
				FontImageBuffer.Image[i][3] = 0x0001;						/* Ｂ４左端４ｍｍ */
				FontImageBuffer.Image[i][26] = 0x0001;						/* Ａ４左端４ｍｍ */
				FontImageBuffer.Image[i][LST_WORD_WIDTH/2 - 1] = 0x0001;	/* 中央 */
				FontImageBuffer.Image[i][LST_WORD_WIDTH/2] = 0x8000;		/* 中央 */
				FontImageBuffer.Image[i][LST_WORD_WIDTH - 26 - 1] = 0x8000;	/* Ａ４右端４ｍｍ */
				FontImageBuffer.Image[i][LST_WORD_WIDTH - 3 - 1] = 0x8000;	/* Ｂ４右端４ｍｍ */
			}
			break;
		default:
			CMN_WordMemorySet(&FontImageBuffer.Image[0][0], LST_WORD_WIDTH*4, 0x0000);
			break;
		}
		while(1) { /** ページの終わりまでループ */
			result = ListImagePrint();
			if (result != OK) { /** エラーが起こればリターン */
				return(result);
			}
			trans_time++;
			if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
				return(ListClose()); /** プリンタをクローズする */
			}
		}
	}
#endif

	result = ListImagePrint(); /** 最初の1回分のイメージ転送 */
	if (result != OK) { /** エラーが起こればリターン */
		return(result);
	}
	trans_time++;
	first_flag = 1;

	/** イメージバッファにデータをセット */
	CMN_WordMemorySet(&FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);
	FontImageBuffer.Image[0][0] = 0x0080;
#if (PRO_PRINT_TYPE == LASER)	/* 1998/02/13 Y.Matsukuma */
	for (i = 15; i < (paper_width - 15); i+= 16) {
		FontImageBuffer.Image[0][i] = 0x0100;
	}
	while(1) { /** ページの終わりまでループ */
		/** 252(4*63)ライン分ループ */
		for (i = 0; i < (UWORD)(63 - first_flag); i++) {
			result = ListImagePrint();
			if (result != OK) { /** エラーが起こればリターン */
				return(result);
			}
			trans_time++;
			if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
				return(ListClose()); /** プリンタをクローズする */
			}

		}
		first_flag = 0;
		CMN_WordMemorySet(&FontImageBuffer.Image[3][0], (paper_width - 16), 0xFFFF);

		result = ListImagePrint();
		if (result != OK) { /** エラーが起こればリターン */
			return(result);
		}
		trans_time++;
		if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
			return(ListClose()); /** プリンタをクローズする */
		}

		/** イメージバッファにデータをセット */
		CMN_WordMemorySet(&FontImageBuffer.Image[3][0], LST_WORD_WIDTH, 0);
		FontImageBuffer.Image[3][0] = 0x0080;
		for (i = 15; i < (paper_width - 15); i+= 16) {
			FontImageBuffer.Image[3][i] = 0x0100;
		}
	}
#else
/*	for (i = 15; i < (LST_A4_WORD_WIDTH - 15); i+= 16) { @* For ANZU By H.Hirao 1996/02/23 */
/*	for (i = 15; i < LST_A4_WORD_WIDTH; i+= 16) {			@* 97/08/12 For POPLAR By M.Kuwahara */
 #if (PRO_PRINTER == DPI400)			/* 1998/03/04 By M.Kuwahara */
	for (i = 15; i < paper_width; i+= 16) {
		FontImageBuffer.Image[0][i] = 0x0100;
	}
 #else
	for (i = 7; i < paper_width; i+= 8) {
		FontImageBuffer.Image[0][i] = 0x0100;
	}
 #endif
	while(1) { /** ページの終わりまでループ */
		/** 252(4*63)ライン分ループ */
		for (i = 0; i < (UWORD)(63 - first_flag); i++) {
			result = ListImagePrint();
			if (result != OK) { /** エラーが起こればリターン */
				return(result);
			}
			trans_time++;
			if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
				return(ListClose()); /** プリンタをクローズする */
			}

		}
		first_flag = 0;
	/*	CMN_WordMemorySet(address3, (LST_A4_WORD_WIDTH - 16), 0xFFFF); @* For ANZU By H.Hirao 1996/02/23 */
		CMN_WordMemorySet(&FontImageBuffer.Image[3][0], LST_WORD_WIDTH, 0xFFFF);

		result = ListImagePrint();
		if (result != OK) { /** エラーが起こればリターン */
			return(result);
		}
		trans_time++;
		if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
			return(ListClose()); /** プリンタをクローズする */
		}

		/** イメージバッファにデータをセット */
		CMN_WordMemorySet(&FontImageBuffer.Image[3][0], LST_WORD_WIDTH, 0);
		FontImageBuffer.Image[3][0] = 0x0080;
	/*	for (i = 15; i < (LST_A4_WORD_WIDTH - 15); i+= 16) { @* For ANZU By H.Hirao 1996/02/23 */
/*		for (i = 15; i < LST_WORD_WIDTH; i+= 16) {	@* 97/08/12 For POPLAR By M.Kuwahara */
 #if (PRO_PRINTER == DPI400)			/* 1998/03/04 By M.Kuwahara */
		for (i = 15; i < paper_width; i+= 16) {
			FontImageBuffer.Image[3][i] = 0x0100;
		}
 #else
		for (i = 7; i < paper_width; i+= 8) {
			FontImageBuffer.Image[3][i] = 0x0100;
		}
 #endif
	}
#endif
}

#if (PRO_PRINT_TYPE == LED )
/*************************************************************************
	module		:[ラインパターン印刷]
	function	:[ラインパターンを1枚印刷する
		出力パターン
			1. 先端余白
			2. 黒帯 10mm(154ﾗｲﾝ)
			3. 白帯 10mm(154ﾗｲﾝ)
			4. 縦線１ [10101010]	黒：白	[1:1]	各 7mm(108ﾗｲﾝ)
			5. 縦線２ [01010101]			[1:1]
			6. 横線							[1:1]
			7. 縦線１ [10010010]			[1:2]
			8. 縦線２ [01001001]			[1:2]
			9. 縦線３ [00100100]			[1:2]
			10.横線							[1:2]
			11.縦線１ [10001000]			[1:3]
			12.縦線２ [01000100]			[1:3]
			13.縦線３ [00100010]			[1:3]
			14.縦線４ [00010001]			[1:3]
			15.横線							[1:3]
			16.縦線１ [11001100]			[2:2]
			17.横線							[2:2]
			18.縦線１ [11000110]			[2:3]
			19.横線							[2:3]
			20.白帯 7mm(108ﾗｲﾝ)
			21.ハーフトーンパターン１  20mm(308ﾗｲﾝ)
					  [10101010]
					  [01010101]
					  [10101010]
			22.チェッカーフラグ				** 97/12/08 Add By M.Kuwahara 
			23.ハーフトーンパターン２  20mm(308ﾗｲﾝ) -> 90mm(1384ﾗｲﾝ) ** 97/12/08 By M.Kuwahara
					  [10001000]
					  [00000000]
					  [00100010]
					  [00000000]
			24.残り全白
	]
	return		:[印刷結果]
	common		:[]
	condition	:[]
	commment	:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/07/17]
	author		:[桑原美紀]
*************************************************************************/
WORD			PrintLinePattern(void)
{
	UBYTE type;
	UBYTE line;
	WORD  result;			/* 実行結果 */
	UWORD i;
	UWORD data;				/* 初期データ */
	UWORD trans_time = 0;
	UWORD total_trans_time; /* 全転送回数 */

	
	if ((result = CharacterPrint(LST_OPEN)) != OK) { /** リストオープン */
		return (result);
	}

	total_trans_time = PRN_PrintClockCounter[SelectedPaper][VARTICAL];
	/** G/Aの仕様により、白ﾃﾞｰﾀを9ﾗｲﾝ転送する */
	trans_time	+= 9;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet( &FontImageBuffer.HeadImage[0], LST_WORD_WIDTH, 0); /** 白ﾃﾞｰﾀをいれる */
	for ( i = 0; i < 9; i++ ) { /** 9ﾗｲﾝ転送 */
		result = ListHeadPrint();
		if ( result != OK ) {
			return (result);
		}
	}

	/** 黒帯 10mm(154ﾗｲﾝ) */
	trans_time	+= 154;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0xFFFF);
	if((result = PrintLinePatternImage( 154, 1 )) != OK){
		return(result);
	}

	/** 白帯 10mm(154ﾗｲﾝ) */
	trans_time	+= 154;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);
	if((result = PrintLinePatternImage( 154, 1 )) != OK){
		return(result);
	}

	/** 縦線１ [10101010]	黒：白	[1:1]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0xAAAA);
	if((result = PrintLinePatternImage( 108, 1 )) != OK){
		return(result);
	}

	/** 縦線２ [01010101]	黒：白	[1:1]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0x5555);
	if((result = PrintLinePatternImage( 108, 1 )) != OK){
		return(result);
	}

	/** 横線				黒：白	[1:1]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0xFFFF);
	CMN_WordMemorySet((&FontImageBuffer.Image[1][0]), LST_WORD_WIDTH, 0);
	if((result = PrintLinePatternImage( 54, 2 )) != OK){
		return(result);
	}

	/** 縦線１ [10010010]	黒：白	[1:2]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);	/* クリア */
	for (line = 0; line < 4; line++) {
		data	= 0x9249;
		for ( i = 0; i < LST_WORD_WIDTH; i++ ) {
			FontImageBuffer.Image[line][i] = data;
			if(( data & 0x000F ) == 0x0004 ){
				data	<<= 1;
				data	|= 0x0001;
			}
			else{
				data	<<= 1;
			}
		}
	}
	if((result = PrintLinePatternImage( 108, 1 )) != OK){
		return(result);
	}

	/** 縦線２ [01001001]	黒：白	[1:2]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);	/* クリア */
	for (line = 0; line < 4; line++) {
		data	= 0x4924;
		for ( i = 0; i < LST_WORD_WIDTH; i++ ) {
			FontImageBuffer.Image[line][i] = data;
			if(( data & 0x000F ) == 0x0004 ){
				data	<<= 1;
				data	|= 0x0001;
			}
			else{
				data	<<= 1;
			}
		}
	}
	if((result = PrintLinePatternImage( 108, 1 )) != OK){
		return(result);
	}

	/** 縦線３ [00100100]	黒：白	[1:2]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);	/* クリア */
	for (line = 0; line < 4; line++) {
		data	= 0x2492;
		for ( i = 0; i < LST_WORD_WIDTH; i++) {
			FontImageBuffer.Image[line][i] = data;
			if(( data & 0x000F ) == 0x0004 ){
				data	<<= 1;
				data	|= 0x0001;
			}
			else{
				data	<<= 1;
			}
		}
	}
	if((result = PrintLinePatternImage( 108, 1 )) != OK){
		return(result);
	}

	/** 横線				黒：白	[1:2]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0xFFFF);
	CMN_WordMemorySet((&FontImageBuffer.Image[1][0]), LST_WORD_WIDTH*2, 0);
	if((result = PrintLinePatternImage( 36, 3 )) != OK){
		return(result);
	}

	/** 縦線１ [10001000]	黒：白	[1:3]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0x8888);
	if((result = PrintLinePatternImage( 108, 1 )) != OK){
		return(result);
	}

	/** 縦線２ [01000100]	黒：白	[1:3]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0x4444);
	if((result = PrintLinePatternImage( 108, 1 )) != OK){
		return(result);
	}

	/** 縦線３ [00100010]	黒：白	[1:3]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0x2222);
	if((result = PrintLinePatternImage( 108, 1 )) != OK){
		return(result);
	}

	/** 縦線４ [00010001]	黒：白	[1:3]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0x1111);
	if((result = PrintLinePatternImage( 108, 1 )) != OK){
		return(result);
	}

	/** 横線				黒：白	[1:3]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0xFFFF);
	CMN_WordMemorySet((&FontImageBuffer.Image[1][0]), LST_WORD_WIDTH*3, 0);
	if((result = PrintLinePatternImage( 27, 4 )) != OK){
		return(result);
	}

	/** 縦線１ [11001100]	黒：白	[2:2]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0xCCCC);
	if((result = PrintLinePatternImage( 108, 1 )) != OK){
		return(result);
	}

	/** 横線				黒：白	[2:2]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH*2, 0xFFFF);
	CMN_WordMemorySet((&FontImageBuffer.Image[2][0]), LST_WORD_WIDTH*2, 0);
	if((result = PrintLinePatternImage( 27, 4 )) != OK){
		return(result);
	}

	/** 縦線１ [11000110]	黒：白	[2:3]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0); /* クリア */
	for (line = 0; line < 4; line++) {
		data	= 0xC631;
		for ( i = 0; i < LST_WORD_WIDTH; i++) {
			FontImageBuffer.Image[line][i] = data;
			if((( data & 0x000F ) == 0x0001 ) ||
			   (( data & 0x000F ) == 0x0008 )){
				data	<<= 1;
				data	|= 0x0001;
			}
			else{
				data	<<= 1;
			}
		}
	}
	if((result = PrintLinePatternImage( 108, 1 )) != OK){
		return(result);
	}

	/** 横線				黒：白	[2:3]	7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	i = 0;
	type = 1;
	while( i < 108 ){
		if( type == 0 ){
			CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);
			CMN_WordMemorySet( &FontImageBuffer.Image[1][0], LST_WORD_WIDTH, 0);
			i	 += 2;
			if((result = PrintLinePatternImage( 1, 2 )) != OK){
				return(result);
			}
		}
		else{
			CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0xFFFF);
			CMN_WordMemorySet( &FontImageBuffer.Image[1][0], LST_WORD_WIDTH, 0xFFFF);
			CMN_WordMemorySet( &FontImageBuffer.Image[2][0], LST_WORD_WIDTH, 0xFFFF);
			i	 += 3;
			if((result = PrintLinePatternImage( 1, 3 )) != OK){
				return(result);
			}
		}
		type ^= 0x01;
	}

	/** 白帯 7mm(108ﾗｲﾝ) */
	trans_time	+= 108;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);	/* クリア */
	if((result = PrintLinePatternImage( 108, 1 )) != OK){
		return(result);
	}

	/** ハーフトーンパターン１  20mm(308ﾗｲﾝ) */
	trans_time	+= 308;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0xAAAA);	/*	[10101010] */
	CMN_WordMemorySet((&FontImageBuffer.Image[1][0]), LST_WORD_WIDTH, 0x5555); 	/*	[01010101] */
	if((result = PrintLinePatternImage( 154, 2 )) != OK){
		return(result);
	}

	/** チェッカーフラグ	128ﾗｲﾝ  97/12/08 Add By M.Kuwahara */
	trans_time	+= 128;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);
#if (PRO_PRINTER == DPI400)			/* 1998/03/04 By M.Kuwahara */
	for (i = 0; i < LST_WORD_WIDTH; i+= 16) {
		CMN_WordMemorySet( (&FontImageBuffer.Image[0][0] + i), 8, 0xFFFF); /** ﾋﾞｯﾄｱｻｲﾝだから 8*16 dotのﾃﾞｰﾀ */
	}
#else
	for (i = 0; i < LST_WORD_WIDTH; i+= 8) {
		CMN_WordMemorySet( (&FontImageBuffer.Image[0][0] + i), 4, 0xFFFF); /** ﾋﾞｯﾄｱｻｲﾝだから 4*16 dotのﾃﾞｰﾀ */
	}
#endif
	if((result = PrintLinePatternImage( 128, 1 )) != OK){
		return(result);
	}

	/** ハーフトーンパターン２  20mm(308ﾗｲﾝ) */	/* 20mm(308ﾗｲﾝ) -> 90mm(1384ﾗｲﾝ) 97/12/08 By M.Kuwahara */
	/* 90mm(1384ﾗｲﾝ) -> 約75mm(1152ﾗｲﾝ) By M.Tachibana 1998/02/24 */
/*	trans_time	+= 308;*/
/*	trans_time	+= 1384;	By M.Tachibana 1998/02/24 */
	trans_time	+= 1152;

	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0x8888);	/* [10001000] */
	CMN_WordMemorySet((&FontImageBuffer.Image[1][0]), LST_WORD_WIDTH, 0x0000); 	/* [00000000] */
	CMN_WordMemorySet((&FontImageBuffer.Image[2][0]), LST_WORD_WIDTH, 0x2222); 	/* [00100010] */
	CMN_WordMemorySet((&FontImageBuffer.Image[3][0]), LST_WORD_WIDTH, 0x0000);	/* [00000000] */
/*	if((result = PrintLinePatternImage( 77, 4 )) != OK){*/
	if((result = PrintLinePatternImage( 128, 4 )) != OK){	/* 512 Line */
		return(result);
	}
	if((result = PrintLinePatternImage( 128, 4 )) != OK){	/* 512 Line */
		return(result);
	}
/*	if((result = PrintLinePatternImage( 90, 4 )) != OK){	By M.Tachibana 1998/02/24 */
	if((result = PrintLinePatternImage( 32, 4 )) != OK){	/* 128 Line */
		return(result);
	}

#if (0)
	/**	今までｾｯﾄしたﾗｲﾝ分を差し引く */
	/* 7mmの白帯ができるはずなのに、1mmぐらいしか空かないのでとりあえず値を増やしておく (+ 92ﾗｲﾝ) */
	total_trans_time = (PRN_PrintClockCounter[SelectedPaper][VARTICAL] - 2769) / 4;
	total_trans_time--;
#endif
	total_trans_time /= 4;
	total_trans_time--;
	/** 残り全白 */
	CMN_WordMemorySet( &FontImageBuffer.Image[0][0], (LST_WORD_WIDTH << 2), 0); /** 4倍する */
	while( 1 ){
		if((result = PrintLinePatternImage( 1, 4 )) != OK){
			return(result);
		}
		trans_time++;
		if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
			return(ListClose()); /** プリンタをクローズする */
		}
	}
}

/*************************************************************************
*	ＬＥＤパターン改造版
*************************************************************************/
WORD			PrintLinePattern2(void)
{
	UBYTE type;
	UBYTE line;
	UBYTE loop;
	WORD  result;			/* 実行結果 */
	UWORD i;
	UWORD data;				/* 初期データ */
	UWORD trans_time = 0;
	UWORD total_trans_time; /* 全転送回数 */

	
	if ((result = CharacterPrint(LST_OPEN)) != OK) { /** リストオープン */
		return (result);
	}

	total_trans_time = PRN_PrintClockCounter[SelectedPaper][VARTICAL];
	/** G/Aの仕様により、白ﾃﾞｰﾀを9ﾗｲﾝ転送する */
	trans_time	+= 9;
	if ( total_trans_time < trans_time ) {
		return(ListClose()); /** プリンタをクローズする */
	}
	CMN_WordMemorySet( &FontImageBuffer.HeadImage[0], LST_WORD_WIDTH, 0); /** 白ﾃﾞｰﾀをいれる */
	for ( i = 0; i < 9; i++ ) { /** 9ﾗｲﾝ転送 */
		result = ListHeadPrint();
		if ( result != OK ) {
			return (result);
		}
	}

	for (loop = 0; loop < 2; loop++) {

		/** 黒帯 10mm(154ﾗｲﾝ) */
		trans_time	+= 154;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0xFFFF);
		if((result = PrintLinePatternImage( 154, 1 )) != OK){
			return(result);
		}

		/** 白帯 10mm(154ﾗｲﾝ) */
		trans_time	+= 154;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);
		if((result = PrintLinePatternImage( 154, 1 )) != OK){
			return(result);
		}

		/** 縦線１ [10101010]	黒：白	[1:1]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0xAAAA);
		if((result = PrintLinePatternImage( 108, 1 )) != OK){
			return(result);
		}

		/** 縦線２ [01010101]	黒：白	[1:1]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0x5555);
		if((result = PrintLinePatternImage( 108, 1 )) != OK){
			return(result);
		}

		/** 横線				黒：白	[1:1]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0xFFFF);
		CMN_WordMemorySet((&FontImageBuffer.Image[1][0]), LST_WORD_WIDTH, 0);
		if((result = PrintLinePatternImage( 54, 2 )) != OK){
			return(result);
		}

		/** 縦線１ [10010010]	黒：白	[1:2]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);	/* クリア */
		for (line = 0; line < 4; line++) {
			data	= 0x9249;
			for ( i = 0; i < LST_WORD_WIDTH; i++ ) {
				FontImageBuffer.Image[line][i] = data;
				if(( data & 0x000F ) == 0x0004 ){
					data	<<= 1;
					data	|= 0x0001;
				}
				else{
					data	<<= 1;
				}
			}
		}
		if((result = PrintLinePatternImage( 108, 1 )) != OK){
			return(result);
		}

		/** 縦線２ [01001001]	黒：白	[1:2]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);	/* クリア */
		for (line = 0; line < 4; line++) {
			data	= 0x4924;
			for ( i = 0; i < LST_WORD_WIDTH; i++ ) {
				FontImageBuffer.Image[line][i] = data;
				if(( data & 0x000F ) == 0x0004 ){
					data	<<= 1;
					data	|= 0x0001;
				}
				else{
					data	<<= 1;
				}
			}
		}
		if((result = PrintLinePatternImage( 108, 1 )) != OK){
			return(result);
		}

		/** 縦線３ [00100100]	黒：白	[1:2]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);	/* クリア */
		for (line = 0; line < 4; line++) {
			data	= 0x2492;
			for ( i = 0; i < LST_WORD_WIDTH; i++) {
				FontImageBuffer.Image[line][i] = data;
				if(( data & 0x000F ) == 0x0004 ){
					data	<<= 1;
					data	|= 0x0001;
				}
				else{
					data	<<= 1;
				}
			}
		}
		if((result = PrintLinePatternImage( 108, 1 )) != OK){
			return(result);
		}

		/** 横線				黒：白	[1:2]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0xFFFF);
		CMN_WordMemorySet((&FontImageBuffer.Image[1][0]), LST_WORD_WIDTH*2, 0);
		if((result = PrintLinePatternImage( 36, 3 )) != OK){
			return(result);
		}

		/** 縦線１ [10001000]	黒：白	[1:3]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0x8888);
		if((result = PrintLinePatternImage( 108, 1 )) != OK){
			return(result);
		}

		/** 縦線２ [01000100]	黒：白	[1:3]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0x4444);
		if((result = PrintLinePatternImage( 108, 1 )) != OK){
			return(result);
		}

		/** 縦線３ [00100010]	黒：白	[1:3]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0x2222);
		if((result = PrintLinePatternImage( 108, 1 )) != OK){
			return(result);
		}

		/** 縦線４ [00010001]	黒：白	[1:3]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0x1111);
		if((result = PrintLinePatternImage( 108, 1 )) != OK){
			return(result);
		}

		/** 横線				黒：白	[1:3]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0xFFFF);
		CMN_WordMemorySet((&FontImageBuffer.Image[1][0]), LST_WORD_WIDTH*3, 0);
		if((result = PrintLinePatternImage( 27, 4 )) != OK){
			return(result);
		}

		/** 縦線１ [11001100]	黒：白	[2:2]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0xCCCC);
		if((result = PrintLinePatternImage( 108, 1 )) != OK){
			return(result);
		}

		/** 横線				黒：白	[2:2]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH*2, 0xFFFF);
		CMN_WordMemorySet((&FontImageBuffer.Image[2][0]), LST_WORD_WIDTH*2, 0);
		if((result = PrintLinePatternImage( 27, 4 )) != OK){
			return(result);
		}

		/** 縦線１ [11000110]	黒：白	[2:3]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0); /* クリア */
		for (line = 0; line < 4; line++) {
			data	= 0xC631;
			for ( i = 0; i < LST_WORD_WIDTH; i++) {
				FontImageBuffer.Image[line][i] = data;
				if((( data & 0x000F ) == 0x0001 ) ||
				   (( data & 0x000F ) == 0x0008 )){
					data	<<= 1;
					data	|= 0x0001;
				}
				else{
					data	<<= 1;
				}
			}
		}
		if((result = PrintLinePatternImage( 108, 1 )) != OK){
			return(result);
		}

		/** 横線				黒：白	[2:3]	7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		i = 0;
		type = 1;
		while( i < 108 ){
			if( type == 0 ){
				CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);
				CMN_WordMemorySet( &FontImageBuffer.Image[1][0], LST_WORD_WIDTH, 0);
				i	 += 2;
				if((result = PrintLinePatternImage( 1, 2 )) != OK){
					return(result);
				}
			}
			else{
				CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0xFFFF);
				CMN_WordMemorySet( &FontImageBuffer.Image[1][0], LST_WORD_WIDTH, 0xFFFF);
				CMN_WordMemorySet( &FontImageBuffer.Image[2][0], LST_WORD_WIDTH, 0xFFFF);
				i	 += 3;
				if((result = PrintLinePatternImage( 1, 3 )) != OK){
					return(result);
				}
			}
			type ^= 0x01;
		}

		/** 白帯 7mm(108ﾗｲﾝ) */
		trans_time	+= 108;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);	/* クリア */
		if((result = PrintLinePatternImage( 108, 1 )) != OK){
			return(result);
		}

#if (0)
//		/** ハーフトーンパターン１  20mm(308ﾗｲﾝ) */
//		trans_time	+= 308;
//		if ( total_trans_time < trans_time ) {
//			return(ListClose()); /** プリンタをクローズする */
//		}
//		CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0xAAAA);	/*	[10101010] */
//		CMN_WordMemorySet((&FontImageBuffer.Image[1][0]), LST_WORD_WIDTH, 0x5555); 	/*	[01010101] */
//		if((result = PrintLinePatternImage( 154, 2 )) != OK){
//			return(result);
//		}
#endif

		/** チェッカーフラグ	128ﾗｲﾝ  97/12/08 Add By M.Kuwahara */
		trans_time	+= 128;
		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);
#if (PRO_PRINTER == DPI400)			/* 1998/03/04 By M.Kuwahara */
		for (i = 0; i < LST_WORD_WIDTH; i+= 16) {
			CMN_WordMemorySet( (&FontImageBuffer.Image[0][0] + i), 8, 0xFFFF); /** ﾋﾞｯﾄｱｻｲﾝだから 8*16 dotのﾃﾞｰﾀ */
		}
#else
		for (i = 0; i < LST_WORD_WIDTH; i+= 8) {
			CMN_WordMemorySet( (&FontImageBuffer.Image[0][0] + i), 4, 0xFFFF); /** ﾋﾞｯﾄｱｻｲﾝだから 4*16 dotのﾃﾞｰﾀ */
		}
#endif
		if((result = PrintLinePatternImage( 128, 1 )) != OK){
			return(result);
		}

		/** ハーフトーンパターン２  20mm(308ﾗｲﾝ) */	/* 20mm(308ﾗｲﾝ) -> 90mm(1384ﾗｲﾝ) 97/12/08 By M.Kuwahara */
		/* 90mm(1384ﾗｲﾝ) -> 約75mm(1152ﾗｲﾝ) By M.Tachibana 1998/02/24 */
		trans_time	+= 308;
	/*	trans_time	+= 1384;	By M.Tachibana 1998/02/24 */
	/*	trans_time	+= 1152;	*/

		if ( total_trans_time < trans_time ) {
			return(ListClose()); /** プリンタをクローズする */
		}
		CMN_WordMemorySet((&FontImageBuffer.Image[0][0]), LST_WORD_WIDTH, 0x8888);	/* [10001000] */
		CMN_WordMemorySet((&FontImageBuffer.Image[1][0]), LST_WORD_WIDTH, 0x0000); 	/* [00000000] */
		CMN_WordMemorySet((&FontImageBuffer.Image[2][0]), LST_WORD_WIDTH, 0x2222); 	/* [00100010] */
		CMN_WordMemorySet((&FontImageBuffer.Image[3][0]), LST_WORD_WIDTH, 0x0000);	/* [00000000] */
		if((result = PrintLinePatternImage( 77, 4 )) != OK){
			return(result);
		}
#if (0)
		if((result = PrintLinePatternImage( 128, 4 )) != OK){	/* 512 Line */
			return(result);
		}
		if((result = PrintLinePatternImage( 128, 4 )) != OK){	/* 512 Line */
			return(result);
		}
	/*	if((result = PrintLinePatternImage( 90, 4 )) != OK){	By M.Tachibana 1998/02/24 */
		if((result = PrintLinePatternImage( 32, 4 )) != OK){	/* 128 Line */
			return(result);
		}
#endif

		if (loop == 0) {

			/** 白帯 13mm(200ﾗｲﾝ) */
			trans_time	+= 200;
			if ( total_trans_time < trans_time ) {
				return(ListClose()); /** プリンタをクローズする */
			}
			CMN_WordMemorySet( &FontImageBuffer.Image[0][0], LST_WORD_WIDTH, 0);	/* クリア */
			if((result = PrintLinePatternImage( 200, 1 )) != OK){
				return(result);
			}

		}
		else {

#if (0)
			/**	今までｾｯﾄしたﾗｲﾝ分を差し引く */
			/* 7mmの白帯ができるはずなのに、1mmぐらいしか空かないのでとりあえず値を増やしておく (+ 92ﾗｲﾝ) */
			total_trans_time = (PRN_PrintClockCounter[SelectedPaper][VARTICAL] - 2769) / 4;
			total_trans_time--;
#endif
			total_trans_time /= 4;
			total_trans_time--;
			/** 残り全白 */
			CMN_WordMemorySet( &FontImageBuffer.Image[0][0], (LST_WORD_WIDTH << 2), 0); /** 4倍する */
			while( 1 ){
				if((result = PrintLinePatternImage( 1, 4 )) != OK){
					return(result);
				}
				trans_time++;
				if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
					return(ListClose()); /** プリンタをクローズする */
				}
			}

		}

	}
}


/*************************************************************************
	module		:[テストラインパターン印刷]
	function	:[テストパターンの指定ライン分を印刷する
	]
	return		:[印刷結果]
	common		:[]
	condition	:[]
	commment	:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/07/19]
	author		:[桑原美紀]
*************************************************************************/
WORD	PrintLinePatternImage(
					 UBYTE 	Line,			/* 出力ライン数 */
					 UBYTE	SetCount )		/* 使用するライン数 */
{
	UBYTE	i;
	WORD	result;

	for( i = 0; i < Line; i++ ){
		result = ListImageLinePrint(SetCount);
		if (result != OK) { /** エラーが起こればリターン */
			return(result);
		}
	}
	return(OK);
}
#endif

#if (PRO_PRINT_TYPE == LED )
/*************************************************************************
	module		:[パターン印刷]
	function	:[]
	return		:[印刷結果]
	common		:[
	]
	condition	:[]
	commment	:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/03/19]
	author		:[橘正樹]
*************************************************************************/
WORD			PrintVariousPattern(
UBYTE	pattern )
{
	WORD result;		/* 実行結果 */
	UWORD total_trans_time;
	UWORD trans_time = 0;
	UWORD i;
	
	if ((result = CharacterPrint(LST_OPEN)) != OK) { /** リストオープン */
		return (result);
	}

	/* 以降 LST_A4_WORD_WIDTH -> LST_WORD_WIDTHに変更　1996/12/10 By M.Tachibana */

	/** G/Aの仕様により、白ﾃﾞｰﾀを9ﾗｲﾝ転送する */ /* For ANZU By H.Hirao 1996/04/04 */
	CMN_WordMemorySet( &FontImageBuffer.HeadImage[0], LST_WORD_WIDTH, 0); /** 白ﾃﾞｰﾀをいれる */
	for ( i = 0; i < 9; i++ ) { /** 9ﾗｲﾝ転送 */
		result = ListHeadPrint();
		if ( result != OK ) {
			return (result);
		}
	}

	/**	9ﾗｲﾝ分差し引く Add By H.Hirao 1996/06/10	*/
	total_trans_time = (PRN_PrintClockCounter[SelectedPaper][VARTICAL] - 9)/4;	/* For ANZU By H.Hirao 1996/04/04 */
	/*total_trans_time = PRN_PrintClockCounter[SelectedPaper][VARTICAL]/4;*/
	total_trans_time--;		/* add by M.Tachibana 1996/12/16 */

	/*--------------------------------------------------------------------
	**	全黒／全白プリント
	*/
	switch (pattern) {
	case 1:
		CMN_WordMemorySet(&FontImageBuffer.Image[0][0], LST_WORD_WIDTH*4, 0xFFFF);
		break;
	default:
		CMN_WordMemorySet(&FontImageBuffer.Image[0][0], LST_WORD_WIDTH*4, 0x0000);
		break;
	}

	while(1) { /** ページの終わりまでループ */
		result = ListImagePrint();
		if (result != OK) { /** エラーが起こればリターン */
			return(result);
		}
		trans_time++;
		if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
			return(ListClose()); /** プリンタをクローズする */
		}
	}
}
#endif


/*************************************************************************
	module		:[テストパターン印刷]
	function	:[テストパターンを印刷する
	]
	return		:[印刷結果]
	common		:[]
	condition	:[]
	commment	:[上位関数がH8と共通のため、同様のブラックボックスとなっている。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/07/20]
	author		:[石橋正和]
*************************************************************************/
WORD			Print_Pattern_Print(
		 UBYTE pattern)	/* パターン（1-7）*/
{
	/* UWORD i; */		/*loop*/
	/* UBYTE j; */	/*loop*/
	WORD result;			/*実行結果*/

	if (TestPattern1Page == 0) {

		switch (pattern) {
		case LST_PATTERN1: 		/* 格子連続 */
			while (1) {
				if ((result = PrintKoushiPattern()) != OK) {
					return(result);
				}
			}
		/* case LST_PATTERN3: */ /* 升目連続 */
		case LST_PATTERN2:
			while (1) {
				if ((result = PrintMasumePattern()) != OK) {
					return(result);
				}
			}
#if( PRO_PRINT_TYPE == LED )
		case LST_PATTERN3:
			while (1) {
				if (LED_Pattern == 0) {
					if ((result = PrintLinePattern()) != OK) {
						return(result);
					}
				}
				else {
					if ((result = PrintLinePattern2()) != OK) {
						return(result);
					}
				}
			}
		case LST_PATTERN4:	/* 全黒 By M.Tachibana 1998/03/19 */
			while (1) {
				if ((result = PrintVariousPattern(1)) != OK) {
					return(result);
				}
			}
		case LST_PATTERN5:	/* 全白 By M.Tachibana 1998/03/19 */
			while (1) {
				if ((result = PrintVariousPattern(0)) != OK) {
					return(result);
				}
			}
#endif
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 1996/09/25 by K.Watanabe */
		case LST_PATTERN10:	/* ＰＣからの格子パターンプリント */
			return(PrintKoushiPattern());
		case LST_PATTERN11:	/* ＰＣからの升目パターンプリント */
			return(PrintMasumePattern());
#endif
		default:
			break;
		}

	}
	else if (TestPattern1Page == 1) {

		switch (pattern) {
		case LST_PATTERN1: 		/* 格子連続 */
			if ((result = PrintKoushiPattern()) != OK) {
				return(result);
			}
			break;
		/* case LST_PATTERN3: */ /* 升目連続 */
		case LST_PATTERN2:
			if ((result = PrintMasumePattern()) != OK) {
				return(result);
			}
			break;
#if( PRO_PRINT_TYPE == LED )
		case LST_PATTERN3:
			if (LED_Pattern == 0) {
				if ((result = PrintLinePattern()) != OK) {
					return(result);
				}
			}
			else {
				if ((result = PrintLinePattern2()) != OK) {
					return(result);
				}
			}
			break;
		case LST_PATTERN4:	/* 全黒 By M.Tachibana 1998/03/19 */
			if ((result = PrintVariousPattern(1)) != OK) {
				return(result);
			}
			break;
		case LST_PATTERN5:	/* 全白 By M.Tachibana 1998/03/19 */
			if ((result = PrintVariousPattern(0)) != OK) {
				return(result);
			}
			break;
#endif
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 1996/09/25 by K.Watanabe */
		case LST_PATTERN10:	/* ＰＣからの格子パターンプリント */
			return(PrintKoushiPattern());
			break;
		case LST_PATTERN11:	/* ＰＣからの升目パターンプリント */
			return(PrintMasumePattern());
			break;
#endif
		default:
			break;
		}

	}
	else {

		switch (pattern) {
#if( PRO_PRINT_TYPE == LED )
		case LST_PATTERN1:	/* LEDパターン1枚 *//* ワンタッチＡ */
			if ((result = PrintLinePattern()) != OK) {
				return(result);
			}
			break;
		case LST_PATTERN2:	/* LEDパターン連続 *//* ワンタッチＣ */
			while (1) {
				if ((result = PrintLinePattern()) != OK) {
					return(result);
				}
			}
			break;
		case LST_PATTERN3: 	/* 手差し升目パターン1枚 *//* ワンタッチＤ */
			if ((result = PrintMasumePattern()) != OK) {
				return(result);
			}
			break;
		case LST_PATTERN4: 	/* 手差し→ＬＥＤ→評価 *//* ワンタッチＥ */
 #if (PRO_MANUAL_CASSETTE == ENABLE)
			/* ① 手差し升目パターン1枚 */
			SYB_MaintenanceSwitch[MNT_SW_H6] = 0x01;
			if ((result = PrintMasumePattern()) != OK) {
				return(result);
			}
			LST_CleaningEnd();
			LST_PageCounter = 0;
 #endif
			/* ② LEDパターン1枚 */
			SYB_MaintenanceSwitch[MNT_SW_H6] = 0;
			if ((result = PrintLinePattern()) != OK) {
				return(result);
			}
			/* ③ 画質評価パターン */
			if ((CMN_CheckPaperExist() == TRUE) && (CMN_CheckNoPrinterError() == TRUE)) {
				ImagePrintTest();
			}
			LST_CleaningEnd();
			break;
#endif
		default:
			break;
		}

	}

	return (OK);
}

