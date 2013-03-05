/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_TCH.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/19
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: サービスレポート
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\syslifem.h"
#include	"\src\atlanta\define\sysmax.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\mlt_pro.h"	/* 追加 1997/10/07 Y.Matsukuma */

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\fcm_tbl.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_v\rom_tbl.h"

#if (PRO_PRINT_TYPE == LED)
#include	"\src\atlanta\prt\ph3\ext_v\prn_data.h"
#endif

#define	SERVICE_REPORT_DATA_MAX		12			/* 処理するライン数、項目数 */
#define FAXCOM_ERROR_ONE_LINE		4			/* 通信状態の1行に出力する項目数 */

/*************************************************************************
	module		:[サービスレポート]
	functiom	:[サービスレポートを印刷する]
	common		:[
		List					:
		SYB_LifeMonitor			:
		FaxComErrorMonitorTable	:

		２回線用に変更しました。1997/10/07 Y.Matsukuma

	]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/05/19]
	author		:[桑原美紀]
*************************************************************************/
WORD				Print_ServiceReport(
						 void )			/*なし*/
{
	UBYTE 	page;					/*ﾍﾟｰｼﾞ*/
	UBYTE	set_no;					/*ｻｰﾋﾞｽ処理番号*/
	UBYTE 	line_cnt;				/*残り印刷可能行数*/
	UBYTE	err_set;				/*通信状態必要行数*/
	UBYTE	err_line;				/*通信状態現在行数*/
	UBYTE	stack_cnt;				/*回線印字用*/
	UBYTE	board_cnt;				/*回線の数*/
	register WORD	ret;			/*実行結果*/

	page = 1;
	set_no = 0;
	err_line	= 0;
	err_set	= Get_FaxComErrorLine();		/* 通信状態出力の必要ライン数取得 */
	stack_cnt = 0;
	board_cnt = OPT_CountModems();			/* 通信回線数取得 */

	while ( set_no < SERVICE_REPORT_DATA_MAX ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		if ( page == 1 ) {
/*			line_cnt = (UBYTE)(PaperSizeLen() - 9);/*印刷可能行数ｾｯﾄ*/
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*印刷可能行数ｾｯﾄ*/
		}
		else {
			line_cnt = (UBYTE)(PaperSizeLen() - 3);/*印刷可能行数ｾｯﾄ*/
		}
		if ( (ret = ServiceReport_Head( 0, page ) ) != OK ) {	/*ﾍｯﾀﾞ印刷*/
			return ( ret );
		}
		while( line_cnt > 1 ){
			if ( set_no == SERVICE_REPORT_DATA_MAX ) {		/* 全て出力したか？ */
				break;
			}
			if( set_no == SERVICE_REPORT_DATA_MAX - 1 ){	/* 通信状態出力の時 */
				if(( err_set - err_line ) <= 0 ){		/* 通信状態を全て出力したか？ */
					stack_cnt++;
					if ((board_cnt == stack_cnt) || (stack_cnt > 1)) {	/* 2回線以降はひとまとまりで出力 */
						set_no++;
						break;
					}
					err_set	= Get_FaxComErrorLine();		/* 通信状態出力の必要ライン数取得 */
					err_line = 0;
				}
				if ((board_cnt > 1) && (err_line == 0)) {	/* ライン番号印字 */
					Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
					AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1],
	  						PWRD_LineNumber, LST_NOT );
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
					++stack_cnt;
					if (stack_cnt == 1) {
						AttributeSet( &List.S.Print[13-1], &List.S.Attribute[13-1], PWRD_LineName[0], LST_NOT );
						List.S.Print[17-1] = '/';
						AttributeSet( &List.S.Print[18-1], &List.S.Attribute[13-1], PWRD_LineName[1], LST_NOT );
					}
					else {
						AttributeSet( &List.S.Print[13-1], &List.S.Attribute[13-1], PWRD_LineName[2], LST_NOT );
					}
#else
					CMN_UnsignedIntToASC( &List.S.Print[13-1], ++stack_cnt, 1, '0' );
#endif
					if ((stack_cnt == 2) && (board_cnt > 2)) {
						List.S.Print[14-1] = '-';
						CMN_UnsignedIntToASC( &List.S.Print[15-1], board_cnt, 1, '0' );
					}
					if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
						return ( ret );
					}
					stack_cnt--;
					line_cnt--;
				}
				if(( ret = Print_FaxComError_Specifi( err_line, stack_cnt )) != OK ){	/* 通信状態1行分印刷 */
					return( ret );
				}
				line_cnt--;
				err_line++;
			}
			else {											/* プリンタ状態出力の時 */
				if ( (ret = Print_ServiceReport_Specifi( set_no )) != OK ) {	/*1明細印刷*/
					return ( ret );
				}
				if ( set_no == 7 ) {	/* TL,TR,TD行の時、２行出力している為 97/10/16 By M.Kuwahara */
					line_cnt--;
				}
				line_cnt--;
				set_no++;
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 印字制限 1997/10/08 Y.Matsukuma */
				if (set_no == 1) {
					set_no = 10;
				}
#endif
			}
		}
		if ( (ret = ServiceReport_Head( 1, page ) ) != OK ) {	/*ﾌｯﾀ印刷*/
			return ( ret );
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	return ( OK );
}

/*************************************************************************
	module		:[サービスレポートヘッダ印刷]
	functiom	:[サービスレポートのヘッダを印刷する]
	common		:[
		List			:
		SYB_LifeMonitor	:
		FaxComErrorMonitorTable
	]
	condition	:[
		ヘッダ種類
		,	0->ページ先頭見出し
		,	1->ページエンド見出し
	]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/25]
	author		:[豊田浩子]
*************************************************************************/
WORD				ServiceReport_Head(
						 UBYTE Category,		/*ヘッダ種類*/
						 UBYTE Page)			/*ページ*/
{
	register WORD	ret;					/*実行結果*/

	if ( Category == 0 ) {
		if ( Page == 1 ) {
			/*１改行＋発信元名、番号印刷＋２改行＋見出し＋１改行*/
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			if ( (ret = Print_Head1_Common( PWRD_ServiceReport_K,
					 LST_NOT,24-1 )) != OK ) {
				return ( ret );
			}

#else
			if ( (ret = Print_Head1_Common( PWRD_ServiceReport,
			  LST_XXX_TWI_XXX, 24-1 )) != OK ) {
				return ( ret );
			}
#endif
			/*現在時間*/
			if ( (ret = CurrentTimePrint( 58-1 )) != OK ) {
				return ( ret );
			}

			/* 機種名 バージョン名 */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			CMN_StringCopy( &List.S.Print[1-1], ROM_Revision );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			/*１行印字（改行）*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
		}
		else {
			/*１行印字（改行）*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
		}
	}
	else {
		/*１行印字（改行）*/		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
	}
	return ( OK );
}

/*************************************************************************
	module		:[サービスレポートの１明細印刷]
	functiom	:[サービスレポートの１明細を印刷する。]
	common		:[
	]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/05/19]
	author		:[桑原美紀]
*************************************************************************/
WORD				Print_ServiceReport_Specifi(
						 UBYTE SetNo )
{
	UBYTE			i;
	register WORD	ret;					/*実行結果*/

	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	switch( SetNo ){				/* 処理番号 */
/*#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) @* 1997/10/08 Y.Matsukuma */
#if (PRO_PRINT_TYPE == LED)	/* By M.Tachibana 1997/12/19 */
	case	0:						/* S, P, T */
		List.S.Print[1-1]	= 'S';
		List.S.Print[3-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[4-1], SYB_LifeMonitor.ScanCount, 6, '0' );
		List.S.Print[13-1]	= 'P';	/* ↑ Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
		List.S.Print[15-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[16-1], SYB_LifeMonitor.PrintCount, 6, '0' );
		List.S.Print[25-1]	= 'T';	/* ↑ Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
		List.S.Print[27-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[28-1], SYB_LifeMonitor.TransmitCount, 6, '0' );
									/* ↑ Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
		break;
	case	1:						/* J1:C1,C2,C3,M */
		List.S.Print[1-1]	= 'J';
		List.S.Print[2-1]	= '1';
		List.S.Print[3-1]	= ':';
		CMN_UnsignedIntToASC( &List.S.Print[4-1], SYB_PrinterLifeMonitor.Jam1Cassette1Count
											    + SYB_PrinterLifeMonitor.Jam1Cassette2Count
											    + SYB_PrinterLifeMonitor.Jam1Cassette3Count
											    + SYB_PrinterLifeMonitor.Jam1ManualCount, 5, '0' );
		List.S.Print[13-1]	= 'C';
		List.S.Print[14-1]	= '1';
		List.S.Print[15-1]	= ':';
		CMN_UnsignedIntToASC( &List.S.Print[16-1], SYB_PrinterLifeMonitor.Jam1Cassette1Count, 5, '0' );
		List.S.Print[25-1]	= 'C';
		List.S.Print[26-1]	= '2';
		List.S.Print[27-1]	= ':';
		CMN_UnsignedIntToASC( &List.S.Print[28-1], SYB_PrinterLifeMonitor.Jam1Cassette2Count, 5, '0' );
		List.S.Print[37-1]	= 'C';
		List.S.Print[38-1]	= '3';
		List.S.Print[39-1]	= ':';
		CMN_UnsignedIntToASC( &List.S.Print[40-1], SYB_PrinterLifeMonitor.Jam1Cassette3Count, 5, '0' );
		List.S.Print[49-1]	= 'M';
		List.S.Print[51-1]	= ':';
		CMN_UnsignedIntToASC( &List.S.Print[52-1], SYB_PrinterLifeMonitor.Jam1ManualCount, 5, '0' );
		break;
	case	2:						/* J2 */
		List.S.Print[1-1]	= 'J';
		List.S.Print[2-1]	= '2';
		List.S.Print[3-1]	= ':';
		CMN_UnsignedIntToASC( &List.S.Print[4-1], SYB_PrinterLifeMonitor.Jam2Count, 5, '0' );
		break;
	case	3:						/* J3 */
		List.S.Print[1-1]	= 'J';
		List.S.Print[2-1]	= '3';
		List.S.Print[3-1]	= ':';
		CMN_UnsignedIntToASC( &List.S.Print[4-1], SYB_PrinterLifeMonitor.Jam3Count, 5, '0' );
		break;
	case	4:						/* B4, A4, B5R, A5R, F4 */
		List.S.Print[1-1]	= 'B';
		List.S.Print[2-1]	= '4';
		List.S.Print[3-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[4-1], SYB_PrinterLifeMonitor.B4_TotalCount, 5, '0' );
		List.S.Print[13-1]	= 'A';
		List.S.Print[14-1]	= '4';
		List.S.Print[15-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[16-1], SYB_PrinterLifeMonitor.A4_TotalCount, 5, '0' );
		List.S.Print[25-1]	= 'B';
		List.S.Print[26-1]	= '5';
		List.S.Print[27-1]	= 'R';
		List.S.Print[28-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[29-1], SYB_PrinterLifeMonitor.B5R_TotalCount, 5, '0' );
		List.S.Print[37-1]	= 'A';
		List.S.Print[38-1]	= '5';
		List.S.Print[39-1]	= 'R';
		List.S.Print[40-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[41-1], SYB_PrinterLifeMonitor.A5R_TotalCount, 5, '0' );
		List.S.Print[49-1]	= 'F';
		List.S.Print[50-1]	= '4';
		List.S.Print[51-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[52-1], SYB_PrinterLifeMonitor.F4_TotalCount, 5, '0' );
		break;
	case	5:						/* LT, LG, B5, A5, A6 */
		List.S.Print[1-1]	= 'L';
		List.S.Print[2-1]	= 'T';
		List.S.Print[3-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[4-1], SYB_PrinterLifeMonitor.LT_TotalCount, 5, '0' );
		List.S.Print[13-1]	= 'L';
		List.S.Print[14-1]	= 'G';
		List.S.Print[15-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[16-1], SYB_PrinterLifeMonitor.LG_TotalCount, 5, '0' );
		List.S.Print[25-1]	= 'B';
		List.S.Print[26-1]	= '5';
		List.S.Print[28-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[29-1], SYB_PrinterLifeMonitor.B5_TotalCount, 5, '0' );
		List.S.Print[37-1]	= 'A';
		List.S.Print[38-1]	= '5';
		List.S.Print[40-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[41-1], SYB_PrinterLifeMonitor.A5_TotalCount, 5, '0' );
		List.S.Print[49-1]	= 'A';
		List.S.Print[50-1]	= '6';
		List.S.Print[51-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[52-1], SYB_PrinterLifeMonitor.A6_TotalCount, 5, '0' );
		break;
	case	6:						/* TP, MP */
		List.S.Print[1-1]	= 'T';
		List.S.Print[2-1]	= 'P';
		List.S.Print[3-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[4-1], SYB_PrinterLifeMonitor.TotalPageCount, 5, '0' );
		List.S.Print[13-1]	= 'M';
		List.S.Print[14-1]	= 'P';
		List.S.Print[15-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[16-1], SYB_PrinterLifeMonitor.ManualTotalCount, 5, '0' );
		break;
	case	7:						/* TL, TR, TD */
		List.S.Print[1-1]	= 'T';
		List.S.Print[2-1]	= 'L';
		List.S.Print[3-1]	= ':';
		CMN_UnsignedIntToASC( &List.S.Print[4-1], SYB_PrinterLifeMonitor.TonerLifeCount, 5, '0' );
		List.S.Print[13-1]	= 'T';
		List.S.Print[14-1]	= 'R';
		List.S.Print[15-1]	= ':';
		CMN_UnsignedIntToASC( &List.S.Print[16-1], SYB_PrinterLifeMonitor.TonerReplaceCount, 5, '0' );
		List.S.Print[25-1]	= 'T';
		List.S.Print[26-1]	= 'D';
		List.S.Print[27-1]	= ':';
		for( i = 0; i < SYS_LIFE_TONER_DATA_MAX; i++ ){
			CMN_UnsignedIntToASC( &List.S.Print[28 + (4 * i)], (UWORD)SYB_PrinterLifeMonitor.TonerData[i], 3, '0');
			if( i < SYS_LIFE_TONER_DATA_MAX - 1 ){
				List.S.Print[31 + (4 * i )]	= '.';
			}
		}
/******** For Test 1997/08/22 By M.Tachibana *********/
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		for( i = 0; i < SYS_LIFE_TONER_DATA_MAX; i++ ){
			CMN_UnsignedIntToASC( &List.S.Print[28 + (4 * i)], (UWORD)PRN_TonerCycleData[i], 3, '0');
		}
/******** For Test End *******/
		break;
	case	8:						/* DL, DR */
		List.S.Print[1-1]	= 'D';
		List.S.Print[2-1]	= 'L';
		List.S.Print[3-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[4-1], SYB_PrinterLifeMonitor.DrumLifeCount, 6, '0' );
		List.S.Print[13-1]	= 'D';	/* ↑ Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
		List.S.Print[14-1]	= 'R';
		List.S.Print[15-1]	= ':';
		CMN_UnsignedIntToASC( &List.S.Print[16-1], SYB_PrinterLifeMonitor.DrumReplaceCount, 5, '0' );
		break;
	case	9:						/* FL, FR */
		List.S.Print[1-1]	= 'F';
		List.S.Print[2-1]	= 'L';
		List.S.Print[3-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[4-1], SYB_PrinterLifeMonitor.FuserLifeCount, 6, '0' );
		List.S.Print[13-1]	= 'F';	/* ↑ Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
		List.S.Print[14-1]	= 'R';
		List.S.Print[15-1]	= ':';
		CMN_UnsignedIntToASC( &List.S.Print[16-1], SYB_PrinterLifeMonitor.FuserReplaceCount, 5, '0' );
		break;
	case	10:						/* RL, RR */
		List.S.Print[1-1]	= 'R';
		List.S.Print[2-1]	= 'L';
		List.S.Print[3-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[4-1], SYB_PrinterLifeMonitor.TransferLifeCount, 6, '0' );
		List.S.Print[13-1]	= 'R';	/* ↑ Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
		List.S.Print[14-1]	= 'R';
		List.S.Print[15-1]	= ':';
		CMN_UnsignedIntToASC( &List.S.Print[16-1], SYB_PrinterLifeMonitor.TransferReplaceCount, 5, '0' );
		break;
#else	/* (for ANZU_L) */
	case	0:						/* S, P, T, DL, DR */
		List.S.Print[1-1]	= 'S';
		List.S.Print[3-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[4-1], SYB_LifeMonitor.ScanCount, 6, '0' );
		List.S.Print[13-1]	= 'P';	/* ↑ Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
		List.S.Print[15-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[16-1], SYB_LifeMonitor.PrintCount, 6, '0' );
		List.S.Print[25-1]	= 'T';	/* ↑ Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
		List.S.Print[27-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[28-1], SYB_LifeMonitor.TransmitCount, 6, '0' );
		List.S.Print[37-1]	= 'D';	/* ↑ Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
		List.S.Print[38-1]	= 'L';
		List.S.Print[39-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[40-1], SYB_LifeMonitor.DrumLifeCount, 6, '0' );
		List.S.Print[49-1]	= 'D';	/* ↑ Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
		List.S.Print[50-1]	= 'R';
		List.S.Print[51-1]	= ':';
		CMN_UnsignedLongToASC( &List.S.Print[52-1], SYB_LifeMonitor.DrumReplaceCount, 6, '0' );
									/* ↑ Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
		break;
#endif
	default:
		break;
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

/*************************************************************************
	module		:[通信状態必要行数の取得]
	functiom	:[通信状態の必要行数を取得する。]
	common		:[
	]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/06/24]
	author		:[桑原美紀]
*************************************************************************/
UBYTE	Get_FaxComErrorLine( void )
{
	UBYTE	i;
	UBYTE	line;

	for( i = 0; i < SYS_FAXCOM_ERROR_MONITOR_MAX; i++ ){
		if( FaxComErrorMonitorTable[i] == 0xffff ){
			break;
		}
	}
	if(( i % FAXCOM_ERROR_ONE_LINE ) == 0 ){
		line = i / (UBYTE)FAXCOM_ERROR_ONE_LINE;
	}
	else{
		line = (UBYTE)(( i / FAXCOM_ERROR_ONE_LINE ) + 1);
	}
	return( line );
}

/*************************************************************************
	module		:[通信状態出力]
	functiom	:[通信状態を1行分ずつ出力する]
	common		:[
		1.通信状態は1行に4項目分ずつセット
		2.通信状態は以下の種類がある
			TRANSMITERROR	0x0800
			RECEIVEERROR	0x0400
			DIALERROR		0x0C00
	]
	condition	:[]
	commment	:[２回線対応のため変更 1997/10/07 Y.Matsukuma ]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/06/24]
	author		:[桑原美紀]
*************************************************************************/
WORD	Print_FaxComError_Specifi( 
					UBYTE	err_line,
					UBYTE	stack_cnt )
{
	UBYTE	pos;			/* 出力位置 */
	UBYTE	i;
	register WORD	ret;

	pos	= 0;
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	for( i = err_line * (UBYTE)FAXCOM_ERROR_ONE_LINE; i < SYS_FAXCOM_ERROR_MONITOR_MAX; i++ ){
		if( pos >= FAXCOM_ERROR_ONE_LINE ){
			break;
		}

		if( FaxComErrorMonitorTable[i] == 0xffff ){		/* 終了か？ */
			break;
		}
		switch( FaxComErrorMonitorTable[i] & 0x0f00 ){
		case	TRANSMITERROR:
			List.S.Print[1 + (pos * 20) - 1]	= 'T';
			break;
		case	RECEIVEERROR:
			List.S.Print[1 + (pos * 20) - 1]	= 'R';
			break;
		case	DIALERROR:
			List.S.Print[1 + (pos * 20) - 1]	= 'D';
			break;
		}
		List.S.Print[2 + (pos * 20) - 1]	= '.';
		CMN_HexToASC( &List.S.Print[3 + (pos * 20) - 1],
					 (UWORD)((FaxComErrorMonitorTable[i] & 0x00f0) >> 4),
					 1 );
		List.S.Print[4 + (pos * 20) - 1]	= '.';
		CMN_HexToASC( &List.S.Print[5 + (pos * 20) - 1],
					 ((UWORD)FaxComErrorMonitorTable[i] & 0x000f),
					 1 );
		CMN_UnsignedIntToASC( &List.S.Print[8 + (pos * 20) - 1],
							 (UWORD)SYB_FaxComErrorMonitor[stack_cnt][i].MML_Count,
							 5, '0' );
		List.S.Print[13 + (pos * 20) - 1]	= ':';
		CMN_UnsignedIntToASC( &List.S.Print[14 + (pos * 20) - 1],
							 (UWORD)SYB_FaxComErrorMonitor[stack_cnt][i].OtherCount,
							 5, '0' );
		pos++;
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	return( OK );
}
