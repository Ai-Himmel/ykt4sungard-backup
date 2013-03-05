/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_JUNK.C
*	Author		: 桑原 美紀
*	Date		: 1997/05/13
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ジャンクメール防止ダイヤルリスト
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdial.h"

#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\lst_def.h"

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\lst_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\lst_data.h"
#include "\src\atlanta\ext_v\lst_wrd.h"

/*************************************************************************
	module		:[ジャンクメール防止ダイヤルリスト印刷]
	function	:[ジャンクメール防止ダイヤルリストを印刷する]
	common		:[
		List							:
		SYB_JunkMailProtectDialBuffer	:
	]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/04/16]
	author		:[桑原美紀]
*************************************************************************/
WORD	Print_BlockJunkFax_List(
						 void )					/*なし*/
{
	UBYTE	page;					/*ﾍﾟｰｼﾞ*/
	UBYTE	dial_cnt;				/*ﾃﾞｰﾀ番号*/
	UBYTE	line_cnt;				/*行数*/
	UBYTE	i;						/*ﾙｰﾌﾟ*/
	register WORD	ret;			/*実行結果*/

	page = 1;
	dial_cnt = 0;
	while ( dial_cnt < SYS_JUNK_DIAL_MAX ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		if ( page == 1 ) {
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*印刷可能行数ｾｯﾄ*/
		}
		else {
			line_cnt = (UBYTE)(PaperSizeLen() - 4);/*印刷可能行数ｾｯﾄ*/
		}
		if ( (ret = Print_BlockJunkFax_List_Head( 0, page ) ) != OK ) {/*ﾍｯﾀﾞ印刷*/
			return ( ret );
		}
		for( i = 0;;i++ ){
			if( line_cnt <= 2 ){
				break;
			}
			while( dial_cnt < SYS_JUNK_DIAL_MAX ){
				if( SYB_JunkMailProtectDialBuffer[dial_cnt][0] != 0xff ){
					break;
				}
				dial_cnt++;
			}
			if ( dial_cnt >= SYS_JUNK_DIAL_MAX ) {
				break;
			}

			if ( (ret = Print_BlockJunk_List_Specifi( page, i, &dial_cnt) ) != OK ) {	/*1行（３明細）印刷*/
				return ( ret );
			}
			line_cnt	-= 2;
		}
		if ( (ret = Print_BlockJunkFax_List_Head( 1, page) ) != OK ) {	/*ﾌｯﾀ印刷*/
			return ( ret );
		}
		if (( ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}

		page++;
	}
	return ( OK );
}
/*************************************************************************
	module		:[ジャンクメール防止ダイヤルリストヘッダ印刷]
	functiom	:[ジャンクメール防止ダイヤルリストのヘッダを印刷する]
	common		:[
		List	:
	]
	condition	:[
		ﾍｯﾀﾞ種類
			0->ﾍﾟｰｼﾞ先頭見出し
			1->ﾍﾟｰｼﾞｴﾝﾄﾞ見出し
	]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/05/13]
	author		:[桑原美紀]
*************************************************************************/
WORD				Print_BlockJunkFax_List_Head(
						 UBYTE Category,	/*ヘッダ種類*/
						 UBYTE Page )		/*ページ*/
{
	register WORD	ret;					/*実行結果*/

	if ( Category == 0 ) {
		if ( Page == 1 ) {
			/* １行改行＋発信元名，発信元番号＋２行改行印刷＋見出し＋１行改行 */
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			if ( (ret = Print_Head1_Common( PWRD_BlockJunkList_K,
			 LST_NOT,14-1 )) != OK ) {
				return ( ret );
			}
#else
			if ( (ret = Print_Head1_Common( PWRD_BlockJunkList,
			  LST_XXX_TWI_XXX, 14-1 )) != OK ) {
				return ( ret );
			}
#endif

			/* Page */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			CMN_MemorySetNULL( List.S.Work, 20, ' ' );
			List.S.Print[12-1] = 'P';
			List.S.Print[13-1] = '.';
			CMN_UnsignedIntToASC( &List.S.Print[14-1], (UWORD)Page, 3, 0 );
			/*現在時間*/
			TimeDataAscii(OFF, SYB_CurrentTime, List.S.Work, 0);
			CMN_StringCopy( &List.S.Print[45-1], List.S.Work );
			/* モード */
/*			switch( SYB_SettingStatus[SETTING_STATUS_2] ){*/
			switch( CHK_BlockJunkFaxMode() ){			/* 97/10/21 By M.Kuwahara */
			case	BLOCK_JUNK_FAX_OFF:
				AttributeSet( &List.S.Print[30-1], &List.S.Attribute[30-1]
						,PWRD_Off, LST_NOT );
				break;
			case	BLOCK_JUNK_FAX_MODE1:
				AttributeSet( &List.S.Print[29-1], &List.S.Attribute[29-1]
						,PWRD_Mode1, LST_NOT );
				break;
			case	BLOCK_JUNK_FAX_MODE2:
				AttributeSet( &List.S.Print[29-1], &List.S.Attribute[29-1]
						,PWRD_Mode2, LST_NOT );
				break;
			case	BLOCK_JUNK_FAX_MODE3:
				AttributeSet( &List.S.Print[29-1], &List.S.Attribute[29-1]
						,PWRD_Mode3, LST_NOT );
				break;
			default:
				break;
			}
			if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/* ┌─┬────┬────┬────┬──┬──┐ */
			Print_BlockJunk_List_Line( 0, List.S.Print, List.S.Attribute );
			if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/* │No.│ﾀﾞｲﾔﾙ番号│No.│ﾀﾞｲﾔﾙ番号│No.│ﾀﾞｲﾔﾙ番号│ */
			Print_BlockJunk_List_Line( 1, List.S.Print, List.S.Attribute );
			if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
		else {
			/*１行印字（改行）*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
			/* Page */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			CMN_MemorySetNULL( List.S.Work, 20, ' ' );
			List.S.Print[12-1] = 'P';
			List.S.Print[13-1] = '.';
			CMN_UnsignedIntToASC( &List.S.Print[14-1], (UWORD)Page, 3, 0 );

			/* ┌─┬────┬────┬────┬──┬──┐ */
			Print_BlockJunk_List_Line( 0, List.S.Print, List.S.Attribute );
			if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
	}
	else {
		/* └─┴────┴────┴────┴──┴──┘	 */
		Print_BlockJunk_List_Line( 4, List.S.Print, List.S.Attribute );
		if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*１行印字（改行）*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
	}
	return( OK );
}

/*************************************************************************
	module		:[ジャンクメール防止ダイヤルリストの１明細印刷]
	functiom	:[ジャンクメール防止ダイヤルリストの１明細を印刷する。]
	common		:[
	]
	condition	:[
	]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/05/13]
	author		:[桑原美紀]
*************************************************************************/
WORD					Print_BlockJunk_List_Specifi(
						 UBYTE Page,			/* ﾍﾟｰｼﾞ */
						 UBYTE Line,			/* 行数 */
						 UBYTE *DialCnt )		/*ＢＯＸ番号*/
{
	UBYTE	dial;
	UBYTE	i;
	register WORD	ret;						/*実行結果*/

	dial	= *DialCnt;

	if ( Page == 1 || Line > 0 ) {
		/* ├-─┼-───-┼-─┼-───-┼-─┼--───┤ */
		Print_BlockJunk_List_Line( 2, List.S.Print, List.S.Attribute );
		if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}

	/* │99.│xxxxxxxx│99.│xxxxxxxx│99.│xxxxxxxx│ */
	Print_BlockJunk_List_Line( 3, List.S.Print, List.S.Attribute );
	i	= 0;
	while( i < 3 ){
		if( SYB_JunkMailProtectDialBuffer[dial][0] != 0xff ){
			/* No. */
			CMN_UnsignedIntToASC( &List.S.Print[(i*18)+12-1], (UWORD)(dial + 1), 2, ' ' );
			/* ダイヤル番号 */
			CMN_BCD_ToASC_String( &List.S.Print[(i*18)+18-1], &SYB_JunkMailProtectDialBuffer[dial][0] );
			i++;
		}
		dial++;
		if( dial >= SYS_JUNK_DIAL_MAX ){
			break;
		}
	}

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	*DialCnt	= dial;
	return( OK );
}

/*************************************************************************
	module		:[ジャンクメール防止ダイヤルリストの横区切り罫線作成]
	function	:[ジャンクメール防止ダイヤルリストの横区切り罫線を作成する。]
	common		:[]
	condition	:[
		罫線種類
			case	0:
			 ┌-─┬-────┬─-┬-────┬-─┬-────┐

			case	1:
			 │No.│ﾀﾞｲﾔﾙ番号│No.│ﾀﾞｲﾔﾙ番号│No.│ﾀﾞｲﾔﾙ番号│

			case	2:
			 ├-─┼-────┼-─┼-────┼-─┼-────┤ 

			case	3:
			 │	  │		 │	  │		 │   │  	     │ 

			case	4:
			 └-─┴-────┴-─┴-────┴-─┴-────┘
	]
	commment	:[]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/05/13]
	author		:[桑原美紀]
*************************************************************************/
void				Print_BlockJunk_List_Line( 
						UBYTE Category,				 /*罫線種類*/
						register UBYTE *AscString,	 /*印刷文字列*/
						register UBYTE *AttString)	 /*修飾文字列*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0 :
			/* ┌─┬────┬─┬────┬─┬────┐ */
			AscString[11-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[12-1], 54, LST_KLINE_);
			AscString[15-1] = LST_KLINE8;
			AscString[29-1] = LST_KLINE8;
			AscString[33-1] = LST_KLINE8;
			AscString[47-1] = LST_KLINE8;
			AscString[51-1] = LST_KLINE8;
			AscString[65-1] = LST_KLINE9;
			break;
		case 1 :
			/* │No.│ﾀﾞｲﾔﾙ番号│No.│ﾀﾞｲﾔﾙ番号│No.│ﾀﾞｲﾔﾙ番号│ */
			AscString[11-1] = LST_KLINEI;
			AttributeSet( &AscString[12-1], &AttString[12-1]
					, PWRD_No, LST_NOT );
			AscString[15-1] = LST_KLINEI;
			AttributeSet( &AscString[17-1], &AttString[17-1]
					,PWRD_TelNum, LST_NOT );
			AscString[29-1] = LST_KLINEI;
			AttributeSet( &AscString[30-1], &AttString[30-1]
					,PWRD_No, LST_NOT );
			AscString[33-1] = LST_KLINEI;
			AttributeSet( &AscString[35-1], &AttString[35-1]
					,PWRD_TelNum, LST_NOT );
			AscString[47-1] = LST_KLINEI;
			AttributeSet( &AscString[48-1], &AttString[48-1]
					,PWRD_No, LST_NOT );
			AscString[51-1] = LST_KLINEI;
			AttributeSet( &AscString[53-1], &AttString[53-1]
					,PWRD_TelNum, LST_NOT );
			AscString[65-1] = LST_KLINEI;
			break;
		case 2 :
			/* ├─┼────┼─┼────┼─┼───┤ */
			AscString[11-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[12-1], 54, LST_KLINE_);
			AscString[15-1] = LST_KLINE5;
			AscString[29-1] = LST_KLINE5;
			AscString[33-1] = LST_KLINE5;
			AscString[47-1] = LST_KLINE5;
			AscString[51-1] = LST_KLINE5;
			AscString[65-1] = LST_KLINE6;
			break;
		case 3 :
			/* │  │		 │	 │	 	   │  │       │ */
			AscString[11-1] = LST_KLINEI;
			AscString[15-1] = LST_KLINEI;
			AscString[29-1] = LST_KLINEI;
			AscString[33-1] = LST_KLINEI;
			AscString[47-1] = LST_KLINEI;
			AscString[51-1] = LST_KLINEI;
			AscString[65-1] = LST_KLINEI;
			break;
		case 4:
			/* └─┴────┴─┴────┴─┴───┘ */
			AscString[11-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[12-1], 54, LST_KLINE_);
			AscString[15-1] = LST_KLINE2;
			AscString[29-1] = LST_KLINE2;
			AscString[33-1] = LST_KLINE2;
			AscString[47-1] = LST_KLINE2;
			AscString[51-1] = LST_KLINE2;
			AscString[65-1] = LST_KLINE3;
			break;
	}
}
