/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_FCDD.C
*	Author		: 桑原 美紀
*	Date		: 1997/04/15
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: サブアドレスＢＯＸ蓄積原稿リスト
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdial.h"

#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\lst_def.h"

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\lst_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\lst_data.h"
#include "\src\atlanta\ext_v\lst_wrd.h"

#if (PRO_F_CODE == ENABLE)
/*************************************************************************
	module		:[サブアドレスＢＯＸ蓄積原稿リスト印刷]
	function	:[サブアドレスＢＯＸ蓄積原稿リストを印刷する]
	common		:[
		List					:
		SYB_SubAddressBoxTable	:
	]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/04/15]
	author		:[桑原美紀]
*************************************************************************/
WORD					Print_F_CodeDoc_List(
						 void )					/*なし*/
{
	UBYTE	i;						/*loop*/
	UBYTE	page;					/*ﾍﾟｰｼﾞ*/
	UBYTE	box_cnt;				/*ﾃﾞｰﾀ番号*/
	UBYTE	page_line;				/*1ﾍﾟｰｼﾞﾗｲﾝ数*/
	UBYTE	line_cnt;				/*行数*/
	register WORD	ret;			/*実行結果*/

	page = 1;
	box_cnt = 0;
	while ( box_cnt != SUB_ADDRESS_BOX_MAX ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		if ( page == 1 ) {
			page_line = (UBYTE)(PaperSizeLen() - 11);/*印刷可能行数ｾｯﾄ*/
		}
		else {
			page_line = (UBYTE)(PaperSizeLen() - 4);/*印刷可能行数ｾｯﾄ*/
		}
		if ( (ret = Print_CodeDoc_List_Head( 0, page ) ) != OK ) {/*ﾍｯﾀﾞ印刷*/
			return ( ret );
		}
		line_cnt	= 0;
		for ( i = 0;; i++ ) {
			F_CodeDataNextSearch( 4, &box_cnt );			/*次ﾃﾞｰﾀｻｰﾁ*/
			if ( box_cnt == SUB_ADDRESS_BOX_MAX ) {
				break;
			}
			if( Get_CodeDocCount( box_cnt ) >= 19 ){	/** 原稿No.の個数取得 **/
				line_cnt	+= 3;
			}
			else{
				line_cnt	+= 2;
			}
			if ( page_line < (UBYTE)(line_cnt +1) ) {
				break;
			}
			if ( (ret = Print_CodeDoc_List_Specifi( page ,i, box_cnt) ) != OK ) {	/*1明細印刷*/
				return ( ret );
			}
			box_cnt++;
		}
		if ( (ret = Print_CodeDoc_List_Head( 1, page) ) != OK ) {	/*ﾌｯﾀ印刷*/
			return ( ret );
		}
		if ( box_cnt != SUB_ADDRESS_BOX_MAX ) {		/* データ存在時 */
			F_CodeDataNextSearch( 4, &box_cnt );			/*次ﾃﾞｰﾀｻｰﾁ*/
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	return ( OK );

}

/*************************************************************************
	module		:[サブアドレスＢＯＸ蓄積原稿リストヘッダ印刷]
	functiom	:[サブアドレスＢＯＸ蓄積原稿リストのヘッダを印刷する]
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
	date		:[97/04/18]
	author		:[桑原美紀]
*************************************************************************/
WORD				Print_CodeDoc_List_Head(
						 UBYTE Category,	/*ヘッダ種類*/
						 UBYTE Page )		/*ページ*/
{
	register WORD	ret;					/*実行結果*/

	if ( Category == 0 ) {
		if ( Page == 1 ) {
			/* １行改行＋発信元名，発信元番号＋２行改行印刷＋見出し＋１行改行 */
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			if ( (ret = Print_Head1_Common( PWRD_F_CodeDoc_List_K, LST_NOT,11-1 )) != OK ) {
				return ( ret );
			}
#else
			if ( (ret = Print_Head1_Common( PWRD_F_CodeDoc_List, LST_XXX_TWI_XXX, 11-1 )) != OK ) {
				return ( ret );
			}
#endif

			/*現在時間*/
			/*Page 現在時間*/
			if ( (ret = PageTimePrint( Page, 2-1, 60-1 )) != OK ) {
				return ( ret );
			}

			/* ┌─┬───┬───────────────┐ */

			Print_F_CodeDoc_List_Line( 0, List.S.Print, List.S.Attribute );
			if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/* │No.│ﾎﾞｯｸｽ名│ 原稿No		 		 	│ */
			Print_F_CodeDoc_List_Line( 1, List.S.Print, List.S.Attribute );
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
			if ( (ret = PagePrint( Page, 2-1 )) != OK ) {
				return ( ret );
			}
		}
	}
	else {
		/* └─┴────┴──────────┘	 */
		Print_F_CodeDoc_List_Line( 4, List.S.Print, List.S.Attribute );
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
	module		:[サブアドレスＢＯＸ蓄積原稿の横区切り罫線作成]
	function	:[サブアドレスＢＯＸ蓄積原稿の横区切り罫線を作成する。]
	common		:[]
	condition	:[
		罫線種類
			case	0:
			 ┌──┬────┬──────────┐

			case	1:
			 │ No.│ﾎﾞｯｸｽ名 │		原稿No		   │

			case	2:
			 ├──┼────┼──────────┤ 

			case	3:
			 │	   │		 │		  			   │

			case	4:
			 └──┴────┴──────────┘
	]
	commment	:[]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/04/15]
	author		:[桑原美紀]
*************************************************************************/
void				Print_F_CodeDoc_List_Line( 
						 UBYTE Category,				 /*罫線種類*/
						 register UBYTE *AscString,		 /*印刷文字列*/
						 register UBYTE *AttString)		 /*修飾文字列*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0 :
			/* ┌─┬────┬──┬────────┐ 　サブアドレス蓄積原稿リスト　*/
			AscString[1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_);
			AscString[5-1] = LST_KLINE8;
			AscString[22-1] = LST_KLINE8;
			AscString[30-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE9;
			break;
		case 1 :
			/* │Box│ﾎﾞｯｸｽ名│種別│		原稿No.    │*/
			AscString[1-1] = LST_KLINEI;
			AttributeSet( &AscString[2-1], &AttString[2-1]
					,PWRD_Box, LST_NOT );
			AscString[5-1] = LST_KLINEI;
			AttributeSet( &AscString[9-1], &AttString[9-1]
					,PWRD_BoxName, LST_NOT );
			AscString[22-1] = LST_KLINEI;
			AttributeSet( &AscString[24-1], &AttString[24-1]
					,PWRD_Kind, LST_NOT );
			AscString[30-1] = LST_KLINEI;
			AttributeSet( &AscString[46-1], &AttString[46-1]
					,PWRD_DocumentsNo, LST_NOT );
			AscString[80-1] = LST_KLINEI;
			break;
		case 2 :
			/* ├─┼────┼──┼────────┤ */
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_);
			AscString[5-1] = LST_KLINE5;
			AscString[22-1] = LST_KLINE5;
			AscString[30-1] = LST_KLINE5;
			AscString[80-1] = LST_KLINE6;
			break;
		case 3 :
			/* │  │		 │		 │		          │ */
			AscString[1-1] = LST_KLINEI;
			AscString[5-1] = LST_KLINEI;
			AscString[22-1] = LST_KLINEI;
			AscString[30-1] = LST_KLINEI;
			AscString[80-1] = LST_KLINEI;
			break;
		case 4:
			/* └─┴────┴──┴────────┘	 */
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_);
			AscString[5-1] = LST_KLINE2;
			AscString[22-1] = LST_KLINE2;
			AscString[30-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE3;
			break;
	}
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ蓄積原稿リストの１明細印刷]
	functiom	:[サブアドレスＢＯＸ蓄積原稿リストの１明細を印刷する。]
	common		:[
	]
	condition	:[
	]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/04/18]
	author		:[桑原美紀]
*************************************************************************/
WORD					Print_CodeDoc_List_Specifi(
						 UBYTE Page,		/*ページ*/
						 UBYTE Line,		/*現在明細数*/
						 UBYTE BoxCnt )		/*ＢＯＸ番号*/
{
	register WORD	ret;						/*実行結果*/

	if ( Page > 1 && Line == 0 ) {
		/* ┌─┬───┬───────────────┐ */
		Print_F_CodeDoc_List_Line( 0, List.S.Print, List.S.Attribute );
		if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	else {
		/* ├─┼───┼───────────┤ */
		Print_F_CodeDoc_List_Line( 2, List.S.Print, List.S.Attribute );
		if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}

	/* │99│xxxxxx│xxxxxxxxxxxxxxxxxxxxxx│ */
	Print_F_CodeDoc_List_Line( 3, List.S.Print, List.S.Attribute );
	/* Ｎｏ． */
	CMN_UnsignedIntToASC( &List.S.Print[2-1], (UWORD)(BoxCnt + 1), 2, ' ' );
	/* ボックス名 */
	CMN_StringCopy( &List.S.Print[6-1], SYB_SubAddressBoxTable[BoxCnt].BoxName );
	/* 種類 */
	switch( SYB_SubAddressBoxTable[BoxCnt].Status ){
	case	SUB_ADDRESS_BULLETIN_BOX:		/* 掲示板 */
		CMN_StringCopy( &List.S.Print[23-1], PWRD_NoticeBoard );
		break;
	case	SUB_ADDRESS_SECURE_BOX:			/* 親展 */
		CMN_StringCopy( &List.S.Print[23-1], PWRD_Secure );
		break;
	case	SUB_ADDRESS_RELAY_BOX:			/* 中継 */
		CMN_StringCopy( &List.S.Print[23-1], PWRD_Relay );
		break;
	default:
		break;
	}
	/* 原稿Ｎｏ． */
#if 0	/* 1999/10/21 Y.Murata NAGANOより*/
//	Print_F_CodeDocNo_Specifi( BoxCnt );
#endif
	if ((ret = Print_F_CodeDocNo_Specifi( BoxCnt )) != OK) {
		return (ret);
	}
	return( OK );
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ蓄積原稿リスト原稿番号明細印刷]
	functiom	:[サブアドレスＢＯＸ蓄積原稿リストの原稿番号を印刷する]
	common		:[
		List				:
		SYB_BatchTxFile		:
	]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/04/15]
	author		:[桑原美紀]
*************************************************************************/
WORD				Print_F_CodeDocNo_Specifi(
						 UBYTE BoxNo ) 				/*サブアドレスＢｏｘＮｏ．*/
{
	UBYTE	i;			/*loop*/
	UBYTE	DocNo;		/*原稿Ｎｏ*/
	register WORD	ret;		/*実行結果*/

	i = 0;
	CMN_MemorySetNULL( List.S.Work, 48, ' ');
	for ( DocNo = 0; DocNo < SYS_SUBADDRESS_BOX_INDEX_MAX; DocNo++ ) {
		if(( SYB_SubAddressBoxTable[BoxNo].StoredDocBit & (0x01 << DocNo)) != 0x00 ){
			if ( i == 16) {
				CMN_StringCopy( &List.S.Print[31-1], List.S.Work );
				if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
				i = 0;
				CMN_MemorySetNULL( List.S.Work, 48, ' ');
				Print_F_CodeDoc_List_Line( 3, List.S.Print, List.S.Attribute);
			}
			if ( i > 0 ) {
				List.S.Work[i*3-1] = ',';
			}
			CMN_UnsignedIntToASC( &List.S.Work[i*3], (UWORD)DocNo+1, 2, ' ');
			i++;
		}
	}
	CMN_StringCopy( &List.S.Print[31-1], List.S.Work );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ蓄積原稿リスト原稿番号カウント取得]
	functiom	:[サブアドレスＢＯＸ蓄積原稿リストの原稿番号の数を取得する]
	common		:[
	]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/04/20]
	author		:[桑原美紀]
*************************************************************************/
UBYTE				Get_CodeDocCount(
						 UBYTE BoxNo ) 				/*サブアドレスＢｏｘＮｏ．*/
{
	UBYTE	doc_no;
	UBYTE	count;

	count	= 0;
	for ( doc_no = 0; doc_no < SYS_SUBADDRESS_BOX_INDEX_MAX; doc_no++ ) {
		if(( SYB_SubAddressBoxTable[BoxNo].StoredDocBit & (0x01 << doc_no)) != 0x00 ){
			count++;
		}
	}
	return( count );
}

#endif
