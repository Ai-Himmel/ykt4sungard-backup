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

#if defined(HINOKI2) || defined(HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)	/* 印字中はオーバーヒートはチェックしません by O.Kimoto 2002/02/25 */
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\define\sys_stat.h"
#endif

#if (defined(POPLAR_H) && defined(JP0)) /* V851 チェッカー By H.Fujimura 2002/07/15 */
#include "\src\atlanta\ext_v\sys_data.h"
#endif

CONST UBYTE	DEBUG_Pattern = 0;

#if (0) /*defined(POPLAR_F)*/
void	LST_LineMemoryCopy(UWORD data0, UWORD data1, UWORD data2, UWORD data3);
WORD	PrintHalfTonePattern1(void);
WORD	PrintHalfTonePattern2(void);
#endif

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
WORD	PrintKoushiPattern(void)
{
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1998.8.26 K.Kawata */
UWORD	i;			/*loop*/
UBYTE	flg;		/*黒／白反転ﾌﾗｸﾞ*/
UBYTE	line_cnt;	/*印刷行数*/
WORD	ret;		/*実行結果*/


	TestPaternPrintOpen();
	flg = 0;
	line_cnt = 0;
	for (;;) {
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE, 0xff);
		if ( flg == 0 ) {
			for (i = 0; i <= (UWORD)(LST_BYTE_SIZE); i += 16) {
				CMN_MemorySet((UBYTE*)&List.Image[i], 8, 0x00);
			}
		}
		else {
			for (i = 8; i <= (UWORD)(LST_BYTE_SIZE); i += 16) {
				CMN_MemorySet((UBYTE*)&List.Image[i], 8, 0x00);
			}
		}
		for (i = 0; i < 64; i++) {
			if ((ret = CharacterPrint(LST_IMAGE_PRINT)) != OK) {
				CharacterPrint(LST_CLOSE);
				return (ret);
			}
		}
		flg ^= 0xff;
		line_cnt += 2;
		if ((UBYTE)(line_cnt + 2) > PaperSizeLen()) {
			break;
		}
	}
	CharacterPrint(LST_CLOSE);
	
	return(OK);

#elif (PRO_PRINT_TYPE == THERMAL)	/* Add by O.Kimoto 1998/11/17 */
UWORD	i;			/*loop*/
UBYTE	flg;		/*黒／白反転ﾌﾗｸﾞ*/
UBYTE	line_cnt;	/*印刷行数*/
WORD	ret;		/*実行結果*/


	TestPaternPrintOpen();
	flg = 0;
	line_cnt = 0;
	for (;;) {
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE, 0x00);
		
#if defined(STOCKHM2)	/* Modify by SMuratec K.W.Q 2004/11/03 */
		if ( flg == 0 ) {
			for (i = 6; i <= (UWORD)(LST_BYTE_SIZE); i += 16) {
				CMN_MemorySet((UBYTE*)&List.Image[i], 8, 0xff);
			}
		}
		else {
			for (i = 14; i <= (UWORD)(LST_BYTE_SIZE); i += 16) {
				CMN_MemorySet((UBYTE*)&List.Image[i], 8, 0xff);
			}
		}
		
		CMN_MemorySet((UBYTE*)&List.Image[LST_BYTE_SIZE - 6], 10, 0x00);
#else
		if ( flg == 0 ) {
			for (i = 0; i <= (UWORD)(LST_BYTE_SIZE); i += 16) {
				CMN_MemorySet((UBYTE*)&List.Image[i], 8, 0xff);
			}
		}
		else {
			for (i = 8; i <= (UWORD)(LST_BYTE_SIZE); i += 16) {
				CMN_MemorySet((UBYTE*)&List.Image[i], 8, 0xff);
			}
		}
#endif					/*	End of defined(STOCKHM2)	*/
		
		for (i = 0; i < 64; i++) {
			if ((ret = CharacterPrint(LST_IMAGE_PRINT)) != OK) {
				CharacterPrint(LST_CLOSE);
				return (ret);
			}
		}
		flg ^= 0xff;
		line_cnt += 2;
		if ((UBYTE)(line_cnt + 2) > PaperSizeLen()) {
			break;
		}
	}
	CharacterPrint(LST_CLOSE);

#if defined(HINOKI2) || defined(HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)	/* 印字中はオーバーヒートはチェックしません by O.Kimoto 2002/02/25 */
	if((SYS_MachineStatus[SYS_PRINTER_STATUS2] &SYS_PRINTER_HIGH_TEMP) == SYS_PRINTER_HIGH_TEMP) {
		return(NG);
	}
	else {
		return(OK);
	}
#else
	return(OK);
#endif

#else
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
#endif
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
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1998.9.17 K.Kawata */
UWORD	i;			/*loop*/
UWORD	line_cnt;	/*印刷行数（イメージライン）*/
UWORD	ret;		/*実行結果*/

	TestPaternPrintOpen();
	line_cnt = (PaperSizeLen()-1)*32;
	for (;;) {
		/*横線*/
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE, 0x00);
		line_cnt--;
		if ((ret = CharacterPrint(LST_IMAGE_PRINT)) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
		if (line_cnt <= 0) {
			break;
		}
		/*縦線*/
		/*縦は黒線を含めて３０ｍｍとする*/
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE, 0xff);
		for (i = 0; i <= (UWORD)(LST_BYTE_SIZE); i+= 16*2) {
			List.Image[i] = 0x7f;
		}
		for (i = 0; i < 230 && line_cnt > 0 ; i++, line_cnt--) {
			if ((ret = CharacterPrint( LST_IMAGE_PRINT)) != OK) {
				CharacterPrint(LST_CLOSE);
				return (ret);
			}
		}
		if (line_cnt <= 0) {
			break;
		}
	}
	CharacterPrint(LST_CLOSE);

	return(OK);

#elif (PRO_PRINT_TYPE == THERMAL)
UWORD	i;			/*loop*/
UWORD	line_cnt;	/*印刷行数（イメージライン）*/
UWORD	ret;		/*実行結果*/

	TestPaternPrintOpen();
	line_cnt = (PaperSizeLen()-1)*32;
	for (;;) {
		/*横線*/
#if defined(STOCKHM2)	/* Modify by SMuratec K.W.Q 2004/11/03 */
		CMN_MemorySet((UBYTE*)&List.Image[6], LST_BYTE_SIZE - 12, 0xff);
#else
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE, 0xff);
#endif					/*	End of defined(STOCKHM2)	*/

		line_cnt--;
		if ((ret = CharacterPrint(LST_IMAGE_PRINT)) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
		if (line_cnt <= 0) {
			break;
		}
		/*縦線*/
		/*縦は黒線を含めて３０ｍｍとする*/
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE, 0x00);
		
#if defined(STOCKHM2)	/* Modify by SMuratec K.W.Q 2004/11/03 */
		for (i = 16; i <= (UWORD)(LST_BYTE_SIZE - 6); i+= 16*2) {
#else
		for (i = 0; i <= (UWORD)(LST_BYTE_SIZE); i+= 16*2) {
#endif					/*	End of defined(STOCKHM2)	*/

			List.Image[i] = 0x80;
		}
		for (i = 0; i < 230 && line_cnt > 0 ; i++, line_cnt--) {
			if ((ret = CharacterPrint( LST_IMAGE_PRINT)) != OK) {
				CharacterPrint(LST_CLOSE);
				return (ret);
			}
		}
		if (line_cnt <= 0) {
			break;
		}
	}
	CharacterPrint(LST_CLOSE);

#if defined(HINOKI2) || defined(HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)	/* 印字中はオーバーヒートはチェックしません by O.Kimoto 2002/02/25 */
	if((SYS_MachineStatus[SYS_PRINTER_STATUS2] &SYS_PRINTER_HIGH_TEMP) == SYS_PRINTER_HIGH_TEMP) {
		return(NG);
	}
	else {
		return(OK);
	}
#else
	return(OK);
#endif

#else
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

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1988.6.1 K.Kawata */
#elif (PRO_PRINT_TYPE == THERMAL)	/* For HINOKI By O.Kimoto 1998/09/07 */
	/* 未だ、なにも入っていません。
	** 曽根岡殿、宜しく！
	*/
#else
	total_trans_time = (PRN_PrintClockCounter[SelectedPaper][VARTICAL] - 9)/4;	/* For ANZU By H.Hirao 1996/04/04 */
	/*total_trans_time = PRN_PrintClockCounter[SelectedPaper][VARTICAL]/4;*/
	total_trans_time--;		/* add by M.Tachibana 1996/12/16 */
#endif

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
#endif
}


#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1998.9.17 K.Kawata */
/*************************************************************************
	module		:[複数行イメージ印刷]
	function	:[複数行イメージデータを印刷する]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300(日立マイコン)]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
UWORD	Loop_Image(UWORD Count)	/*縦ﾄﾞｯﾄ数*/
{
UWORD	i;		/*loop*/
UWORD	ret;	/*実行結果*/

	for (i = 0; i < Count; i++) {
		if ((ret = CharacterPrint( LST_IMAGE_PRINT)) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
	}
	return (OK);
}
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
WORD	PrintLinePattern(void)
{
UWORD	i;			/*loop*/
UBYTE	j;			/*loop*/
UWORD	k;			/*work*/
UBYTE*	img_pt1;	/*Image pointer*/
UBYTE*	img_pt2;	/*Image pointer*/
UBYTE*	img_pt3;	/*Image pointer*/
UBYTE	black_bit;	/*naname sen balck*/
UWORD	ret;		/*実行結果*/

	TestPaternPrintOpen();
	/*斜線*/
	CMN_MemorySet((UBYTE*)List.Image, LST_BYTE_SIZE, 0xff);
	img_pt1 = &List.Image[0];
	img_pt2 = &List.Image[LST_BYTE_SIZE/3];
	img_pt3 = &List.Image[LST_BYTE_SIZE/3*2];
	black_bit = 0x7f;
	k = (PaperSizeLen()*32) - (LST_IMG_Y_KK1*7*2 + 2);
	for (i = 0; i < k; i++) {
		*img_pt1 = black_bit;
		*img_pt2 = black_bit;
		*img_pt3 = black_bit;
		List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		if ((ret = CharacterPrint(LST_IMAGE_PRINT)) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
		List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		black_bit >>= 1;
		black_bit |= 0x80;
		if (black_bit == 0xff) {
			black_bit = 0x7f;
			*img_pt1 = 0xff;
			*img_pt2 = 0xff;
			*img_pt3 = 0xff;
			img_pt1++;
			if (img_pt1-&List.Image[0] >= LST_BYTE_SIZE) {
				img_pt1 = &List.Image[0];
			}
			img_pt2++;
			if (img_pt2-&List.Image[0] >= LST_BYTE_SIZE) {
				img_pt2 = &List.Image[0];
			}
			img_pt3++;
			if (img_pt3-&List.Image[0] >= LST_BYTE_SIZE) {
				img_pt3 = &List.Image[0];
			}
		}
	}
	/*白、灰、黒、縞１、縞２、縞３、縞４*/
	for (j = 0; j < 2; j++) {
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE, 0xff);	/*白*/
		List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		if ((ret = Loop_Image( LST_IMG_Y_KK1 )) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
		for (i = 0; i < LST_IMG_Y_KK1/2; i++) {		/*灰（黒／白）*/
			CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE, 0x00);
			List.Image[LST_KK_LINE_1] ^= 0x18;
			List.Image[LST_KK_LINE_2] ^= 0x18;
			if ((ret = CharacterPrint( LST_IMAGE_PRINT )) != OK) {
				CharacterPrint(LST_CLOSE);
				return (ret);
			}
			CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE, 0xff );
			List.Image[LST_KK_LINE_1] ^= 0x18;
			List.Image[LST_KK_LINE_2] ^= 0x18;
			if ((ret = CharacterPrint( LST_IMAGE_PRINT )) != OK) {
				CharacterPrint(LST_CLOSE);
				return (ret);
			}
		}
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE, 0x66);	/*灰（黒｜白）*/
		List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		if ((ret = Loop_Image(LST_IMG_Y_KK1)) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
		CMN_MemorySet((UBYTE *)&List.Image[0], LST_BYTE_SIZE+2, 0xff);	/*縞１*/
		for (i = 0; i <= (LST_BYTE_SIZE+1-1); i += 1*2) {
			CMN_MemorySet((UBYTE*)&List.Image[i], 1, 0x00);
		}
		List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		if ((ret = Loop_Image( LST_IMG_Y_KK1 )) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE+2, 0xff);	/*縞２*/
		for (i = 1; i <= LST_BYTE_SIZE; i += 2) {
			CMN_MemorySet((UBYTE*)&List.Image[i], 1, 0x00);
		}
		List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		if ((ret = Loop_Image( LST_IMG_Y_KK1 )) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE+4, 0xff);	/*縞３*/
		for (i = 0; i <= LST_BYTE_SIZE; i += 4*2) {
			CMN_MemorySet((UBYTE*)&List.Image[i], 4, 0x00);
		}
		List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		if ((ret = Loop_Image( LST_IMG_Y_KK1 )) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE+4, 0xff);	/*縞４*/
		for (i = 4; i <= LST_BYTE_SIZE; i += 4*2) {
			CMN_MemorySet((UBYTE*)&List.Image[i], 4, 0x00);
		}
		List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		if ((ret = Loop_Image( LST_IMG_Y_KK1 )) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
	}
	CharacterPrint(LST_CLOSE);
	
	return(OK);

}
#endif

#if (PRO_PRINT_TYPE == THERMAL)	/* 1998.9.17 K.Kawata */
/*************************************************************************
	module		:[複数行イメージ印刷]
	function	:[複数行イメージデータを印刷する]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300(日立マイコン)]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
UWORD	Loop_Image(UWORD Count)	/*縦ﾄﾞｯﾄ数*/
{
UWORD	i;		/*loop*/
UWORD	ret;	/*実行結果*/

	for (i = 0; i < Count; i++) {
		if ((ret = CharacterPrint( LST_IMAGE_PRINT)) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
	}
	return (OK);
}
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
WORD	PrintLinePattern(void)
{
UWORD	i;			/*loop*/
UBYTE	j;			/*loop*/
UWORD	k;			/*work*/
UBYTE*	img_pt1;	/*Image pointer*/
UBYTE*	img_pt2;	/*Image pointer*/
UBYTE*	img_pt3;	/*Image pointer*/
UBYTE	black_bit;	/*naname sen balck*/
UWORD	ret;		/*実行結果*/

	TestPaternPrintOpen();
	/*斜線*/
	CMN_MemorySet((UBYTE*)List.Image, LST_BYTE_SIZE, 0x00);
 #if defined(STOCKHM2)	/* Modify by SMuratec K.W.Q 2004/11/03 */
	img_pt1 = &List.Image[6];
 #else
	img_pt1 = &List.Image[0];
 #endif					/* End of defined(STOCKHM2)	*/

	img_pt2 = &List.Image[LST_BYTE_SIZE/3];
	img_pt3 = &List.Image[LST_BYTE_SIZE/3*2];
	black_bit = 0x80;
	k = (PaperSizeLen()*32) - (LST_IMG_Y_KK1*7*2 + 2);
	for (i = 0; i < k; i++) {
		*img_pt1 = black_bit;
		*img_pt2 = black_bit;
		*img_pt3 = black_bit;
		List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		if ((ret = CharacterPrint(LST_IMAGE_PRINT)) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
		List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		black_bit >>= 1;
		if (black_bit == 0x00) {
			black_bit = 0x80;
			*img_pt1 = 0x00;
			*img_pt2 = 0x00;
			*img_pt3 = 0x00;

 #if defined(STOCKHM2)	/* Modify by SMuratec K.W.Q 2004/11/03 */
			img_pt1++;
			if (img_pt1-&List.Image[0] >= LST_BYTE_SIZE	- 6) {
				img_pt1 = &List.Image[6];
			}
			img_pt2++;
			if (img_pt2-&List.Image[0] >= LST_BYTE_SIZE - 6) {
				img_pt2 = &List.Image[6];
			}
			img_pt3++;
			if (img_pt3-&List.Image[0] >= LST_BYTE_SIZE - 6) {
				img_pt3 = &List.Image[6];
			}
 #else
			img_pt1++;
			if (img_pt1-&List.Image[0] >= LST_BYTE_SIZE) {
				img_pt1 = &List.Image[0];
			}
			img_pt2++;
			if (img_pt2-&List.Image[0] >= LST_BYTE_SIZE) {
				img_pt2 = &List.Image[0];
			}
			img_pt3++;
			if (img_pt3-&List.Image[0] >= LST_BYTE_SIZE) {
				img_pt3 = &List.Image[0];
			}
 #endif 					/*	End of defined(STOCKHM2)	*/
		}
	}
	/*白、灰、黒、縞１、縞２、縞３、縞４*/
	for (j = 0; j < 2; j++) {
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE, 0x00);	/*白*/
		List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		if ((ret = Loop_Image( LST_IMG_Y_KK1 )) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
		for (i = 0; i < LST_IMG_Y_KK1/2; i++) {		/*灰（黒／白）*/
 #if defined(STOCKHM2)	/* Modify by SMuratec K.W.Q 2004/11/03 */
			CMN_MemorySet((UBYTE*)&List.Image[6], LST_BYTE_SIZE - 12, 0xff);
 #else
			CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE, 0xff);
 #endif 					/*	End of defined(STOCKHM2)	*/

			List.Image[LST_KK_LINE_1] ^= 0x18;
			List.Image[LST_KK_LINE_2] ^= 0x18;
			if ((ret = CharacterPrint( LST_IMAGE_PRINT )) != OK) {
				CharacterPrint(LST_CLOSE);
				return (ret);
			}
			CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE, 0x00 );
			List.Image[LST_KK_LINE_1] ^= 0x18;
			List.Image[LST_KK_LINE_2] ^= 0x18;
			if ((ret = CharacterPrint( LST_IMAGE_PRINT )) != OK) {
				CharacterPrint(LST_CLOSE);
				return (ret);
			}
		}
		
 #if defined(STOCKHM2)	/* Modify by SMuratec K.W.Q 2004/11/03 */
		CMN_MemorySet((UBYTE*)&List.Image[6], LST_BYTE_SIZE, 0xcc);	/*灰（黒｜白）*/
 		CMN_MemorySet((UBYTE*)&List.Image[LST_BYTE_SIZE - 6], 10, 0x00);
 #else
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE, 0xcc);	/*灰（黒｜白）*/
 #endif 					/*	End of defined(STOCKHM2)	*/
		
		List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		if ((ret = Loop_Image(LST_IMG_Y_KK1)) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}

		CMN_MemorySet((UBYTE *)&List.Image[0], LST_BYTE_SIZE+2, 0x00);	/*縞１*/

 #if defined(STOCKHM2)	/* Modify by SMuratec K.W.Q 2004/11/03 */
		for (i = 6; i <= (LST_BYTE_SIZE); i += 1*2) {
 #else
		for (i = 0; i <= (LST_BYTE_SIZE+1-1); i += 1*2) {
 #endif 					/*	End of defined(STOCKHM2)	*/

			CMN_MemorySet((UBYTE*)&List.Image[i], 1, 0xff);
		}
 #if defined(STOCKHM2)	/* Modify by SMuratec K.W.Q 2004/11/03 */
		CMN_MemorySet((UBYTE*)&List.Image[LST_BYTE_SIZE - 6], 10, 0x00);
 #endif 					/*	End of defined(STOCKHM2)	*/
     	List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		if ((ret = Loop_Image( LST_IMG_Y_KK1 )) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE+2, 0x00);	/*縞２*/

 #if defined(STOCKHM2)	/* Modify by SMuratec K.W.Q 2004/11/03 */
		for (i = 7; i <= LST_BYTE_SIZE; i += 2) {
 #else
		for (i = 1; i <= LST_BYTE_SIZE; i += 2) {
 #endif 					/*	End of defined(STOCKHM2)	*/

			CMN_MemorySet((UBYTE*)&List.Image[i], 1, 0xff);
		}

 #if defined(STOCKHM2)	/* Modify by SMuratec K.W.Q 2004/11/03 */
		CMN_MemorySet((UBYTE*)&List.Image[LST_BYTE_SIZE - 6], 10, 0x00);
 #endif 					/*	End of defined(STOCKHM2)	*/
 
		List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		if ((ret = Loop_Image( LST_IMG_Y_KK1 )) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE+4, 0x00);	/*縞３*/
		
 #if defined(STOCKHM2)	/* Modify by SMuratec K.W.Q 2004/11/03 */
		for (i = 6; i <= LST_BYTE_SIZE; i += 4*2) {
 #else
		for (i = 0; i <= LST_BYTE_SIZE; i += 4*2) {
 #endif 					/*	End of defined(STOCKHM2)	*/

			CMN_MemorySet((UBYTE*)&List.Image[i], 4, 0xff);
		}

 #if defined(STOCKHM2)	/* Modify by SMuratec K.W.Q 2004/11/03 */
		CMN_MemorySet((UBYTE*)&List.Image[LST_BYTE_SIZE - 6], 10, 0x00);
 #endif 					/*	End of defined(STOCKHM2)	*/
 
		List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		if ((ret = Loop_Image( LST_IMG_Y_KK1 )) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
		CMN_MemorySet((UBYTE*)&List.Image[0], LST_BYTE_SIZE+4, 0x00);	/*縞４*/
		
 #if defined(STOCKHM2)	/* Modify by SMuratec K.W.Q 2004/11/03 */
		for (i = 10; i <= LST_BYTE_SIZE; i += 4*2) {
 #else
		for (i = 4; i <= LST_BYTE_SIZE; i += 4*2) {
 #endif 					/*	End of defined(STOCKHM2)	*/
			CMN_MemorySet((UBYTE*)&List.Image[i], 4, 0xff);
		}

 #if defined(STOCKHM2)	/* Modify by SMuratec K.W.Q 2004/11/03 */
		CMN_MemorySet((UBYTE*)&List.Image[LST_BYTE_SIZE - 6], 10, 0x00);
 #endif 					/*	End of defined(STOCKHM2)	*/
 
		List.Image[LST_KK_LINE_1] ^= 0x18;
		List.Image[LST_KK_LINE_2] ^= 0x18;
		if ((ret = Loop_Image( LST_IMG_Y_KK1 )) != OK) {
			CharacterPrint(LST_CLOSE);
			return (ret);
		}
	}
	CharacterPrint(LST_CLOSE);

#if defined(HINOKI2) || defined(HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)	/* 印字中はオーバーヒートはチェックしません by O.Kimoto 2002/02/25 */
	if((SYS_MachineStatus[SYS_PRINTER_STATUS2] &SYS_PRINTER_HIGH_TEMP) == SYS_PRINTER_HIGH_TEMP) {
		return(NG);
	}
	else {
		return(OK);
	}
#else
	return(OK);
#endif

}
#endif
#if (PRO_PRINT_TYPE == LED)
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
WORD	PrintLinePattern(void)
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

	switch (pattern) {
#if (0)	/*defined(POPLAR_F)*/
** 	case LST_PATTERN1:
** 		while (1) {
** 			if ((result = PrintHalfTonePattern1()) != OK) {
** 				return(result);
** 			}
** 		}
** 	case LST_PATTERN2:
** 		while (1) {
** 			if ((result = PrintHalfTonePattern2()) != OK) {
** 				return(result);
** 			}
** 		}
#else
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
#endif
#if( PRO_PRINT_TYPE == THERMAL_TRANS) || ( PRO_PRINT_TYPE == THERMAL)	/* Add THERMAL by O.Kimoto 1998/11/17 */
	case LST_PATTERN3:
		while (1) {
			if ((result = PrintLinePattern()) != OK) {
				return(result);
			}
		}
#endif
#if( PRO_PRINT_TYPE == LED )
	case LST_PATTERN3:
 #if (defined(POPLAR_H) && defined(JP0)) /* V851 チェッカー By H.Fujimura 2002/07/15 */
		if ((SYS_CheckerMode == CHECKER_PRINTER_ASSY) || (SYS_CheckerMode == CHECKER_MAIN_TEST)) {	/* プリンタチェッカー・メイン基盤の時 */
			if ((result = PrintLinePattern()) != OK) {
				if (SYS_CheckerMode == CHECKER_PRINTER_ASSY) {
					CHKR_BackupToPaperSize();
				}
				return(result);
			}
			/* ADD 2002/01/22 H.Iehara */
			if (SYS_CheckerMode == CHECKER_PRINTER_ASSY) {	/* 2002.02.08 H.Nishimura メイン基板でカセット設定クリアされるから */
				CHKR_BackupToPaperSize();
			}
			break;
		}
 #endif
		while (1) {
			if ((result = PrintLinePattern()) != OK) {
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
#if (defined(POPLAR_H) && defined(JP0)) /* V851 チェッカー By H.Fujimura 2002/07/15 */
	/********************/
	/* プロセステスト用 */
	/********************/
	case LST_PATTERN8:
		ImagePrintTest();
		break;
	case LST_PATTERN12: /* チェッカー用 */
		if (SYS_CheckerMode == CHECKER_PRINTER_ASSY) {
			if ((result = PrintLinePattern()) != OK) {
				return(result);
			}
			ImagePrintTest();
		}
		break;
#endif
	default:
		break;
	}
	return (OK);
}



#if (0)	/*defined(POPLAR_F)*/
void	LST_LineMemoryCopy(UWORD data0, UWORD data1, UWORD data2, UWORD data3)
{
	UWORD	i;

	for (i = 0; i < LST_WORD_WIDTH; i++) {
		FontImageBuffer.Image[0][i] = data0;
		FontImageBuffer.Image[1][i] = data1;
		FontImageBuffer.Image[2][i] = data2;
		FontImageBuffer.Image[3][i] = data3;
	}
}

/*************************************************************************
	module		:[ハーフトーンパターン印刷]
	function	:[ハーフトーンパターンを1枚印刷する
	]
	return		:[印刷結果]
	common		:[]
	condition	:[]
	commment	:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1999/12/21]
	author		:[橘正樹]
*************************************************************************/
WORD	PrintHalfTonePattern1(void)
{
	UBYTE top;
	UBYTE line;
	WORD  result;			/* 実行結果 */
	UWORD total_trans_time; /* 全転送回数 */
	UWORD trans_time = 0;

	
	if ((result = CharacterPrint(LST_OPEN)) != OK) { /** リストオープン */
		return (result);
	}

	total_trans_time = (PRN_PrintClockCounter[SelectedPaper][VARTICAL] - 9)/4;

	/*total_trans_time /= 2;*/
	total_trans_time--;

	while( 1 ){

		LST_LineMemoryCopy(0xC0C0,0xC0C0,0x0000,0x0000);
		if((result = PrintLinePatternImage( 1, 4 )) != OK){
			return(result);
		}
		trans_time++;
		if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
			return(ListClose()); /** プリンタをクローズする */
		}

		LST_LineMemoryCopy(0x0C0C,0x0C0C,0x0000,0x0000);
		if((result = PrintLinePatternImage( 1, 4 )) != OK){
			return(result);
		}
		trans_time++;
		if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
			return(ListClose()); /** プリンタをクローズする */
		}

#if (0)
		/* 0xC0C0 */
		if ((result = ListImageLinePrint(1/*, 0*/)) != OK) {
			return(result);
		}
		if ((result = ListImageLinePrint(1/*, 0*/)) != OK) {
			return(result);
		}
		trans_time++;
		if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
			return(ListClose()); /** プリンタをクローズする */
		}
		/* 0x0000 */
		if ((result = ListImageLinePrint(2/*, 2*/)) != OK) {
			return(result);
		}
		trans_time++;
		if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
			return(ListClose()); /** プリンタをクローズする */
		}
		/* 0x0C0C */
		if ((result = ListImageLinePrint(1/*, 1*/)) != OK) {
			return(result);
		}
		if ((result = ListImageLinePrint(1/*, 1*/)) != OK) {
			return(result);
		}
		trans_time++;
		if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
			return(ListClose()); /** プリンタをクローズする */
		}
		/* 0x0000 */
		if ((result = ListImageLinePrint(2/*, 2*/)) != OK) {
			return(result);
		}
		trans_time++;
		if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
			return(ListClose()); /** プリンタをクローズする */
		}
#endif

	}
}

/*************************************************************************
	module		:[ラダーパターン印刷]
	function	:[ラダーパターンを1枚印刷する
	]
	return		:[印刷結果]
	common		:[]
	condition	:[]
	commment	:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1999/12/21]
	author		:[橘正樹]
*************************************************************************/
WORD	PrintHalfTonePattern2(void)
{
	UBYTE top;
	UBYTE line;
	WORD  result;			/* 実行結果 */
	UWORD total_trans_time; /* 全転送回数 */
	UWORD trans_time = 0;

	
	if ((result = CharacterPrint(LST_OPEN)) != OK) { /** リストオープン */
		return (result);
	}

	total_trans_time = (PRN_PrintClockCounter[SelectedPaper][VARTICAL] - 9);

	/*total_trans_time /= 2;*/
	total_trans_time--;

	while( 1 ){

		LST_LineMemoryCopy(0xFFFF,0xFFFF,0x0000,0x0000);
		if((result = PrintLinePatternImage( 1, 2 )) != OK){
			return(result);
		}
		trans_time++;
		trans_time++;
		if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
			return(ListClose()); /** プリンタをクローズする */
		}

		LST_LineMemoryCopy(0x0000,0x0000,0x0000,0x0000);
		if((result = PrintLinePatternImage( 1, 4 )) != OK){
			return(result);
		}
		trans_time++;
		trans_time++;
		trans_time++;
		trans_time++;
		if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
			return(ListClose()); /** プリンタをクローズする */
		}

#if (0)
		/* 黒：2line */
		result = ListImageLinePrint(2/*, 0*/);
		if (result != OK) { /** エラーが起こればリターン */
			return(result);
		}
		trans_time++;
		if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
			return(ListClose()); /** プリンタをクローズする */
		}
		/* 白：2line × 2 */
		for( line = 0; line < 2; line++ ){
			result = ListImageLinePrint(2/*, 2*/);
			if (result != OK) { /** エラーが起こればリターン */
				return(result);
			}
			trans_time++;
			if (trans_time >= total_trans_time) { /** ページの最後まで出力した場合 */
				return(ListClose()); /** プリンタをクローズする */
			}
		}
#endif

	}
}
#endif
