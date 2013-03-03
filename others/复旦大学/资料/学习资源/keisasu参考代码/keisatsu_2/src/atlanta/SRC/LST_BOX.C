/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_BOX.C
*	Author		: 桑原 美紀
*	Date		: 1997/04/15
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: サブアドレスＢＯＸリスト
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
	module		:[サブアドレスＢＯＸリスト印刷]
	function	:[サブアドレスＢＯＸリストを印刷する]
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
WORD					Print_F_CodeBox_List(
						 void )					/*なし*/
{
	UBYTE	i;						/*loop*/
	UBYTE	page;					/*ﾍﾟｰｼﾞ*/
	UBYTE	box_cnt;				/*ﾃﾞｰﾀ番号*/
	UBYTE	line_cnt;				/*行数*/
	register WORD	ret;			/*実行結果*/
#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
	UBYTE	j;
	UBYTE	item;
	UBYTE	box_cnt_for_separator;	/* 罫線を書くときに参照するＢＯＸ番号 by H.Kubo 1999/01/12 */
	j = 0;
	item = 0;
#endif

	for ( i = 0; i < SUB_ADDRESS_BOX_MAX; i++ ) {	/* データ存在チェック */
		if( SYB_SubAddressBoxTable[i].Status != SUB_ADDRESS_BOX_EMPTY ){
			break;
		}
	}
	if( i >= SUB_ADDRESS_BOX_MAX ){
		return( MSG_PRN_LST_NO_LIST );
	}

	page = 1;
	box_cnt = 0;
#if (PRO_FCODE_RELAY == ENABLE)
	box_cnt_for_separator = 0; /* added by H.Kubo 1999/01/12 */
#endif

#if (1)		/* 初期化忘れ対応 by Y.kano 2005/03/01 */
	DialCheckBitPointer = 0;		/** ビットポインタを初期化 */
#endif

	while ( box_cnt != SUB_ADDRESS_BOX_MAX ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		if ( page == 1 ) {
/*			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*印刷可能行数ｾｯﾄ*/
			line_cnt = (UBYTE)(PaperSizeLen() - 13);/*印刷可能行数ｾｯﾄ*/	/*97/10/22 By M.Kuwahara */
		}
		else {
/*			line_cnt = (UBYTE)(PaperSizeLen() - 4);/*印刷可能行数ｾｯﾄ*/	/*97/10/22 By M.Kuwahara */
			line_cnt = (UBYTE)(PaperSizeLen() - 5);/*印刷可能行数ｾｯﾄ*/
		}
#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
		if ( (ret = Print_Box_List_Head( 0, page, box_cnt ) ) != OK ) {/*ﾍｯﾀﾞ印刷*/
			return ( ret );
		}
		i = 0;
		for ( ;; ) {
			if (line_cnt < 2) {
				break;
			}
			if (item == 0) {	/* ﾎﾞｯｸｽ名、ｻﾌﾞｱﾄﾞﾚｽ等の出力 */
				F_CodeDataNextSearch( 1, &box_cnt );			/*次ﾃﾞｰﾀｻｰﾁ*/
				box_cnt_for_separator	= box_cnt; /* added by H.Kubo 1999/01/12 */
				if ( box_cnt == SUB_ADDRESS_BOX_MAX ) {
					break;
				}
				if ( (ret = Print_Box_List_Specifi( page ,i, box_cnt) ) != OK ) {	/*1明細印刷*/
					return ( ret );
				}
				line_cnt -= 2;
			}
			if (SYB_SubAddressBoxTable[box_cnt].Status == SUB_ADDRESS_RELAY_BOX) {	/* 中継の時 */
				if (item == 0) {
					item = 1;
					j	= 0;
					DialCheckPointer	= SYS_ONETOUCH_DIAL;
					DialCheckBitPointer	= 0;
				}
				if (line_cnt < 2) {	/* １行もかけない時 */
					break;
				}
				if ( (ret = Print_BoxExecData_Specifi( &j, &line_cnt, &item, box_cnt) ) != OK ) {	/*1明細印刷*/
					return ( ret );
				}
				if (line_cnt <= 0) {
					break;
				}
			}
			i++;
			box_cnt++;
			if (line_cnt < 2) { /* ページの最後の罫線が次のＢＯＸの下用の罫線になるバグ対策 by H.Kubo 1999/01/12 */
				break;
			}
		}
 #if 0 /* ページの最後の罫線が次のＢＯＸの下用の罫線になるバグ対策 by H.Kubo 1999/1/12 */
@@		if ( (ret = Print_Box_List_Head( 1, page, box_cnt) ) != OK ) {	/*ﾌｯﾀ印刷*/
@@			return ( ret );
@@		}
 #else
		if ( (ret = Print_Box_List_Head( 1, page, box_cnt_for_separator) ) != OK ) {	/*ﾌｯﾀ印刷*/
			return ( ret );
		}
 #endif
#else
		if ( (ret = Print_Box_List_Head( 0, page ) ) != OK ) {/*ﾍｯﾀﾞ印刷*/
			return ( ret );
		}
		for ( i = 0; line_cnt >= 2; i++, line_cnt -= 2 ) {
			F_CodeDataNextSearch( 1, &box_cnt );			/*次ﾃﾞｰﾀｻｰﾁ*/
			if ( box_cnt == SUB_ADDRESS_BOX_MAX ) {
				break;
			}
			if ( (ret = Print_Box_List_Specifi( page ,i, box_cnt) ) != OK ) {	/*1明細印刷*/
				return ( ret );
			}
			box_cnt++;
		}
		if ( (ret = Print_Box_List_Head( 1, page) ) != OK ) {	/*ﾌｯﾀ印刷*/
			return ( ret );
		}
#endif
		if ( box_cnt == SUB_ADDRESS_BOX_MAX ) {		/* 全ての印字終了時 */
			line_cnt--;
			if( line_cnt < 1 ){			/* ページ替え有りの時 */
				if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
					return ( ret );
				}
				if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
					return ( ret );
				}
			}
#if (0)
//			/* "ｵﾌﾟｼｮﾝ  1:ｼﾞｭｼﾝｷﾝｼ 2:ｳﾜｶﾞｷ 3:ﾄﾞｳｼﾞﾌﾟﾘﾝﾄ 4:ｿｳｼﾝｼﾞｹﾞﾝｺｳｼｮｳｷｮ" */
//			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
//			AttributeSet( &List.S.Print[18-1], &List.S.Attribute[18-1], PWRD_BoxOption, LST_NOT );
//			List.S.Print[25-1] = '1';
//			List.S.Print[26-1] = ':';
//			AttributeSet( &List.S.Print[27-1], &List.S.Attribute[27-1], PWRD_RecvProtect, LST_NOT );
//			List.S.Print[38-1] = '2';
//			List.S.Print[39-1] = ':';
//			AttributeSet( &List.S.Print[40-1], &List.S.Attribute[40-1], PWRD_RxPrint, LST_NOT );
//			List.S.Print[51-1] = '3';
//			List.S.Print[52-1] = ':';
//			AttributeSet( &List.S.Print[53-1], &List.S.Attribute[53-1], PWRD_Replace, LST_NOT );
//			List.S.Print[61-1] = '4';
//			List.S.Print[62-1] = ':';
//			AttributeSet( &List.S.Print[63-1], &List.S.Attribute[63-1], PWRD_TransErase, LST_NOT );
//			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
//				return ( ret );
//			}
#endif
		}
		else{
			F_CodeDataNextSearch( 1, &box_cnt );			/*次ﾃﾞｰﾀｻｰﾁ*/
		}

		if ( box_cnt == SUB_ADDRESS_BOX_MAX ) {		/* 全ての印字終了時 */
			/* "ｵﾌﾟｼｮﾝ  1:ｼﾞｭｼﾝｷﾝｼ 2:ｳﾜｶﾞｷ 3:ﾄﾞｳｼﾞﾌﾟﾘﾝﾄ 4:ｿｳｼﾝｼﾞｹﾞﾝｺｳｼｮｳｷｮ" */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[18-1], &List.S.Attribute[18-1], PWRD_Note, LST_NOT );
			List.S.Print[25-1] = '1';
			List.S.Print[26-1] = ':';
			AttributeSet( &List.S.Print[27-1], &List.S.Attribute[27-1], PWRD_RecvProtect, LST_NOT );
			List.S.Print[38-1] = '2';
			List.S.Print[39-1] = ':';
			AttributeSet( &List.S.Print[40-1], &List.S.Attribute[40-1], PWRD_RxPrint, LST_NOT );
			List.S.Print[51-1] = '3';
			List.S.Print[52-1] = ':';
			AttributeSet( &List.S.Print[53-1], &List.S.Attribute[53-1], PWRD_Replace, LST_NOT );
			List.S.Print[61-1] = '4';
			List.S.Print[62-1] = ':';
			AttributeSet( &List.S.Print[63-1], &List.S.Attribute[63-1], PWRD_TransErase, LST_NOT );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/10/09 By M.Kuwahara */
		/*１行印字（改行）*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
#endif
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	return ( OK );
}
/*************************************************************************
	module		:[サブアドレスＢＯＸリストヘッダ印刷]
	functiom	:[サブアドレスＢＯＸリストのヘッダを印刷する]
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
	date		:[97/04/17]
	author		:[桑原美紀]
*************************************************************************/
#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
WORD				Print_Box_List_Head(
						 UBYTE Category,	/*ヘッダ種類*/
						 UBYTE Page,		/*ページ*/
					   	 UBYTE BoxCnt )		/*ＢＯＸ番号*/
#else
WORD				Print_Box_List_Head(
						 UBYTE Category,	/*ヘッダ種類*/
						 UBYTE Page )		/*ページ*/
#endif
{
	register WORD	ret;					/*実行結果*/
#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
	WORD	i; /* UBYTE => WORD Changed by H.Kubo 1999/01/06 */
#endif

	if ( Category == 0 ) {
		if ( Page == 1 ) {
			/* １行改行＋発信元名，発信元番号＋２行改行印刷＋見出し＋１行改行 */
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			if ( (ret = Print_Head1_Common( PWRD_F_CodeBox_List_K,
			 LST_NOT,20-1 )) != OK ) {
				return ( ret );
			}
#else
			if ( (ret = Print_Head1_Common( PWRD_F_CodeBox_List,
			  LST_XXX_TWI_XXX, 20-1 )) != OK ) {
				return ( ret );
			}
#endif

			/*現在時間*/
			/*Page 現在時間*/
			if ( (ret = PageTimePrint( Page, 2-1, 60-1 )) != OK ) {
				return ( ret );
			}

			/* ┌─┬────┬────┬────┬──┬──┐ */
			Print_F_CodeBox_List_Line( 0, List.S.Print, List.S.Attribute );
			if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/* │Box│ﾎﾞｯｸｽ名│ SUBｱﾄﾞﾚｽ番号│通信ﾊﾟｽﾜｰﾄﾞ番号│種類│ｵﾌﾟｼｮﾝ│ */
			Print_F_CodeBox_List_Line( 1, List.S.Print, List.S.Attribute );
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
#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
		if ( BoxCnt == SUB_ADDRESS_BOX_MAX ) {
			i = BoxCnt - 1;
		}
		else {
			i = BoxCnt;
		}
		/* └─┴────┴────┴────┴──┴──┘	 */
		Print_F_CodeBox_List_Line( 4, List.S.Print, List.S.Attribute );
 #if (0)	/* SYB_SubAddressBoxTable[0]が検索されない。By H.Fujimura 1999/01/05 */
 **		for (; i > 0; i--) {		/* 前明細がＦ中継か検索 */
 #else
		for (; i >= 0; i--) {		/* 前明細がＦ中継か検索 */
 #endif
		    if((SYB_SubAddressBoxTable[i].Status == SUB_ADDRESS_BULLETIN_BOX) ||	/* Ｆ親展又はＦ掲示板の時 */
		       (SYB_SubAddressBoxTable[i].Status == SUB_ADDRESS_SECURE_BOX)) {	
				break;
			}
		    if(SYB_SubAddressBoxTable[i].Status == SUB_ADDRESS_RELAY_BOX) {	/* Ｆ中継の時 */
				/* └─┴────┴───────────────┘	 */
				Print_F_CodeBox_List_Line( 8, List.S.Print, List.S.Attribute );
				break;
			}
		}
#else
		/* └─┴────┴────┴────┴──┴──┘	 */
		Print_F_CodeBox_List_Line( 4, List.S.Print, List.S.Attribute );
#endif
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
	module		:[サブアドレスリスト ネクスト サーチ］
	functiom	:[サブアドレスリストの次デ－タをサーチする]
	common		:[
	]
	condition	:[
	]
	commment	:[]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/04/17]
	author		:[桑原美紀]
*************************************************************************/
void				F_CodeDataNextSearch(
						 UBYTE SoFlag,/*検索種類*/
						 register UBYTE *DataCnt )	/*データ番号*/
{
	UBYTE	i;

	switch( SoFlag ){		/* 検索種類 */
	case	1:				/* ＢＯＸ登録時 */
		for ( i = (*DataCnt); i < SUB_ADDRESS_BOX_MAX; i++ ) {
			if ( SYB_SubAddressBoxTable[i].Status != SUB_ADDRESS_BOX_EMPTY ) {
				break;
			}
		}
		break;
	case	2:				/* 消去メッセージの時 */
		for ( i = (*DataCnt); i < SUB_ADDRESS_BOX_MAX; i++ ) {
			if ( SYB_SubAddressBoxTable[i].MessageStatus == SYS_SUB_ADDRESS_BOX_ERASED_MSG ) {
				break;
			}
		}
		break;
	case	3:				/* 受信通知の時 */
		for ( i = (*DataCnt); i < SUB_ADDRESS_BOX_MAX; i++ ) {
			if ( (SYB_SubAddressBoxTable[i].Status != SUB_ADDRESS_BOX_EMPTY)	/* ｻﾌﾞｱﾄﾞﾚｽＢＯＸ登録済み */
			   &&((SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_RECEIVE)	/* 受信原稿あり */
				||(SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_STORED))	/* 受信中に蓄積した */
			   &&(SYB_SubAddressBoxTable[i].MessageStatus == SYS_SUB_ADDRESS_BOX_RCV_MSG) ) {	/* ｻﾌﾞｱﾄﾞﾚｽBOX受信通知ﾌﾟﾘﾝﾄ要求 */
				break;
			}
		}
		break;
	case	4:				/* 蓄積原稿リストの時 */
		for ( i = (*DataCnt); i < SUB_ADDRESS_BOX_MAX; i++ ) {
			if (SYB_SubAddressBoxTable[i].Status != SUB_ADDRESS_BOX_EMPTY) {	/* ｻﾌﾞｱﾄﾞﾚｽＢＯＸ登録済み */
				break;
			}
		}
		break;
	default:
		break;
	}
	(*DataCnt)	= i;
}

/*************************************************************************
	module		:[サブアドレスＢＯＸリストの１明細印刷]
	functiom	:[サブアドレスＢＯＸリストの１明細を印刷する。]
	common		:[
	]
	condition	:[
	]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/04/17]
	author		:[桑原美紀]
*************************************************************************/
WORD					Print_Box_List_Specifi(
						 UBYTE Page,		/*ページ*/
						 UBYTE Line,		/*現在明細数*/
						 UBYTE BoxCnt )		/*ＢＯＸ番号*/
{
	register WORD	ret;						/*実行結果*/
#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
	UBYTE	i;
#endif

	if ( Page > 1 && Line == 0 ) {
		/* ┌──┬────┬──────┬────────┬──┬───┐*/
		Print_F_CodeBox_List_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	else {
#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
		/* ├─┼────┼────┼────┼──┼──┤ */
		Print_F_CodeBox_List_Line( 2, List.S.Print, List.S.Attribute );
		if (BoxCnt != 0) {
 #if (0)	/* SYB_SubAddressBoxTable[0]が検索されない。By H.Fujimura 1999/01/05 */
 **			for (i = BoxCnt - 1; i > 0; i--) {		/* 前明細がＦ中継か検索 */
 #else
			for (i = BoxCnt - 1; i >= 0; i--) {		/* 前明細がＦ中継か検索 */
 #endif
			    if((SYB_SubAddressBoxTable[i].Status == SUB_ADDRESS_BULLETIN_BOX) ||	/* Ｆ親展又はＦ掲示板の時 */
			       (SYB_SubAddressBoxTable[i].Status == SUB_ADDRESS_SECURE_BOX)) {	
					break;
				}
			    if(SYB_SubAddressBoxTable[i].Status == SUB_ADDRESS_RELAY_BOX) {	/* Ｆ中継の時 */
					/* ├─┼────┼────┬────┬──┬──┤ */
					Print_F_CodeBox_List_Line( 7, List.S.Print, List.S.Attribute );
					break;
				}
			}
		}
#else
		/* ├─┼────┼────┼────┼──┼──┤ */
		Print_F_CodeBox_List_Line( 2, List.S.Print, List.S.Attribute );
#endif
		if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}

	/* │99│xxxxxxx│xxxxxxxxxxxxxxx│xxxxxxx│xxxxxxx│xxxxxxx│ */
	Print_F_CodeBox_List_Line( 3, List.S.Print, List.S.Attribute );
	/* Ｂｏｘ */
	CMN_UnsignedIntToASC( &List.S.Print[2-1], (UWORD)(BoxCnt + 1), 2, ' ' );
	/* ボックス名 */
	CMN_StringCopy( &List.S.Print[6-1], SYB_SubAddressBoxTable[BoxCnt].BoxName );
	/* ＳＵＢアドレス番号 */
	CMN_StringCopy( &List.S.Print[23-1], SYB_SubAddressBoxTable[BoxCnt].SubAddress );
	/* 通信パスワード番号 */
	CMN_StringCopy( &List.S.Print[44-1], SYB_SubAddressBoxTable[BoxCnt].PassWord );
	/* 種類 */
	switch( SYB_SubAddressBoxTable[BoxCnt].Status ){
	case	SUB_ADDRESS_BULLETIN_BOX:		/* 掲示板 */
		CMN_StringCopy( &List.S.Print[65-1], PWRD_NoticeBoard );
		break;
	case	SUB_ADDRESS_SECURE_BOX:			/* 親展 */
		CMN_StringCopy( &List.S.Print[65-1], PWRD_Secure );
		break;
	case	SUB_ADDRESS_RELAY_BOX:			/* 中継 */
		CMN_StringCopy( &List.S.Print[65-1], PWRD_Relay );
		break;
	default:
		break;
	}
	/* オプション */
	if( SYB_SubAddressBoxTable[BoxCnt].Status == SUB_ADDRESS_BULLETIN_BOX ){		/* 掲示板の時 */
		OptionToShortString( SYB_SubAddressBoxTable[BoxCnt].Option, &List.S.Print[73-1] );
	}
	if( SYB_SubAddressBoxTable[BoxCnt].Status == SUB_ADDRESS_SECURE_BOX ){		/* 親展の時 */
		if( SYB_SubAddressBoxTable[BoxCnt].HoldTime != 0 ){		/* 保持時間が０の時表示無し */
			CMN_UnsignedIntToASC( &List.S.Print[73-1], 
				(UWORD)(SYB_SubAddressBoxTable[BoxCnt].HoldTime), 2, ' ' );
			AttributeSet( &List.S.Print[76-1], &List.S.Attribute[76-1], PWRD_Days, LST_NOT );
		}
	}

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	return( OK );
}

/*************************************************************************
	module		:[サブアドレス／ＢＯＸリストの横区切り罫線作成]
	function	:[サブアドレス／ＢＯＸリストの横区切り罫線を作成する。]
	common		:[]
	condition	:[
		罫線種類
			case	0:
			┌──┬────┬──────┬────────┬──┬───┐

			case	1:
			│Box │ﾎﾞｯｸｽ名 │SUBｱﾄﾞﾚｽ番号│通信ﾊﾟｽﾜｰﾄﾞ番号 │種類│ｵﾌﾟｼｮﾝ│

			case	2:
			├──┼────┼──────┼────────┼──┼───┤ 

			case	3:
			│	  │		│			  │				│    │	  │ 

			case	4:
			└──┴────┴──────┴────────┴──┴───┘

			case	5:
			｜    ｜        ├──────┴────────┴──┴───┤

			case	6:
			│    │	    │	      		            				  │

			case	7:
			├──┼────┼──────┬────────┬──┬───┤

			case	8:
			└──┴────┴──────────────────────┘

			case	9:
			┌──┬────┬──────────────────────┐
	]
	commment	:[]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/04/14]
	author		:[桑原美紀]
*************************************************************************/
void				Print_F_CodeBox_List_Line( 
						UBYTE Category,				 /*罫線種類*/
						register UBYTE *AscString,	 /*印刷文字列*/
						register UBYTE *AttString)	 /*修飾文字列*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0 :
			/* ┌─┬────┬────┬────┬──┬──┐ 　サブアドレスＢＯＸリスト　*/
			AscString[1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_);
			AscString[5-1] = LST_KLINE8;
			AscString[22-1] = LST_KLINE8;
			AscString[43-1] = LST_KLINE8;
			AscString[64-1] = LST_KLINE8;
			AscString[72-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE9;
			break;
		case 1 :
			/* │Box│ﾎﾞｯｸｽ名│SUBｱﾄﾞﾚｽ番号│通信ﾊﾟｽﾜｰﾄﾞ番号│種別│ｵﾌﾟｼｮﾝ│ */
			AscString[1-1] = LST_KLINEI;
			AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_Box, LST_NOT );
			AscString[5-1] = LST_KLINEI;
			AttributeSet( &AscString[9-1], &AttString[9-1],PWRD_BoxName, LST_NOT );
			AscString[22-1] = LST_KLINEI;
			AttributeSet( &AscString[26-1], &AttString[26-1],PWRD_SubAddress, LST_NOT );
			AscString[43-1] = LST_KLINEI;
			AttributeSet( &AscString[45-1], &AttString[45-1],PWRD_CommPasscode, LST_NOT );
			AscString[64-1] = LST_KLINEI;
			AttributeSet( &AscString[66-1], &AttString[66-1],PWRD_Kind, LST_NOT );
			AscString[72-1] = LST_KLINEI;
			AttributeSet( &AscString[73-1], &AttString[73-1],PWRD_Note, LST_NOT );
			AscString[80-1] = LST_KLINEI;
			break;
		case 2 :
			/* ├─┼────┼────┼────┼──┼──┤ */
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_);
			AscString[5-1] = LST_KLINE5;
			AscString[22-1] = LST_KLINE5;
			AscString[43-1] = LST_KLINE5;
			AscString[64-1] = LST_KLINE5;
			AscString[72-1] = LST_KLINE5;
			AscString[80-1] = LST_KLINE6;
			break;
		case 3 :
			/* │  │		 │		   │		 │    │    │ */
			AscString[1-1] = LST_KLINEI;
			AscString[5-1] = LST_KLINEI;
			AscString[22-1] = LST_KLINEI;
			AscString[43-1] = LST_KLINEI;
			AscString[64-1] = LST_KLINEI;
			AscString[72-1] = LST_KLINEI;
			AscString[80-1] = LST_KLINEI;
			break;
		case 4:
			/* └─┴────┴────┴────┴──┴──┘	 */
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_);
			AscString[5-1] = LST_KLINE2;
			AscString[22-1] = LST_KLINE2;
			AscString[43-1] = LST_KLINE2;
			AscString[64-1] = LST_KLINE2;
			AscString[72-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE3;
			break;
#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
		case 5:
			/* |   |          ├────┴────┴──┴──┤ */
			AscString[1-1] = LST_KLINEI;
			AscString[5-1] = LST_KLINEI;
			AscString[22-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[23-1], 57, LST_KLINE_);
			AscString[43-1] = LST_KLINE2;
			AscString[64-1] = LST_KLINE2;
			AscString[72-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE6;
			break;
		case 6 :
			/* │  │		 │		     		              │ */
			AscString[1-1] = LST_KLINEI;
			AscString[5-1] = LST_KLINEI;
			AscString[22-1] = LST_KLINEI;
			AscString[80-1] = LST_KLINEI;
			break;
		case 7 :
			/* ├─┼────┼────┬────┬──┬──┤ */
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_);
			AscString[5-1] = LST_KLINE5;
			AscString[22-1] = LST_KLINE5;
			AscString[43-1] = LST_KLINE8;
			AscString[64-1] = LST_KLINE8;
			AscString[72-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE6;
			break;
		case 8:
			/* └─┴────┴───────────────┘	 */
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_);
			AscString[5-1] = LST_KLINE2;
			AscString[22-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE3;
			break;
		case 9 :
			/* ┌─┬────┬───────────────┐ 　サブアドレスＢＯＸリスト　*/
			AscString[1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_);
			AscString[5-1] = LST_KLINE8;
			AscString[22-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE9;
			break;
#endif
	}
}


/*************************************************************************
	module		:[ｵﾌﾟｼｮﾝﾃﾞｰﾀ、略称型文字列変換。]
	function	:[ｵﾌﾟｼｮﾝﾃﾞｰﾀを略称型の文字列に変換する。]
	common		:[
	]
	condition	:[]
	commment	:[ｵﾌﾟｼｮﾝﾃﾞｰﾀを文字列に変換しｸﾞﾙｰﾌﾟ文字列にｾｯﾄする。
					]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/04/15]
	author		:[桑原美紀]
*************************************************************************/
void				OptionToShortString(
						 UBYTE OptionData,				/*ｵﾌﾟｼｮﾝﾃﾞｰﾀ*/
						 register UBYTE* OptionString )	/*ｵﾌﾟｼｮﾝ文字列*/
{
/*	UBYTE	i;			/*loop*/
/*	UDWORD	j;			/*ｵﾌﾟｼｮﾝﾋﾞｯﾄ*/
	UBYTE	k;			/*ﾃﾞｰﾀ数*/

	CMN_MemorySet( OptionString, 7, ' ' ) ;
#if (0)
	j = 1;
	k = 0;
	for ( i = 1; i <= 4; i++ ) {
		if ( (OptionData & j) == j ) {
			if ( k > 0 ) {
				OptionString[k*2-1] = ',';
			}
			CMN_UnsignedIntToASC( &OptionString[k*2], (UWORD)(i), 1, ' ' );
			k++;
		}
		j <<= 1;
	}
#endif
	k	= 0;
	/* 受信禁止設定 */
 	if ((OptionData & SUB_ADDRESS_OPTION_RECEIVE) != 0x00){
		OptionString[k*2] = '1';
		k++;
	}

	/* 受信原稿プリント許可 */
 	if ((OptionData & SUB_ADDRESS_OPTION_PRINT) != 0x00){
		if( k > 0 ){
			OptionString[k*2-1] = ',';
		}
		OptionString[k*2] = '2';
		k++;
	}

	/* 受信原稿上書き許可 */
 	if ((OptionData & SUB_ADDRESS_OPTION_DOC_ADD) != 0x00){
		if( k > 0 ){
			OptionString[k*2-1] = ',';
		}
		OptionString[k*2] = '3';
		k++;
	}

	/* 送信原稿消去許可 */
 	if ((OptionData & SUB_ADDRESS_OPTION_ERASE) != 0x00){
		if( k > 0 ){
			OptionString[k*2-1] = ',';
		}
		OptionString[k*2] = '4';
		k++;
	}
}

/*************************************************************************
	module		:[Ｆコード中継データの１明細印刷]
	functiom	:[Ｆコード中継データの１明細を印刷する。]
	common		:[
		List				:
		SYB_SubAddressBoxTable		:
	]
	condition	:[
	]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/09/16]
	author		:[桑原美紀]
*************************************************************************/
#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/16 Add By M.Kuwahara */
WORD			Print_BoxExecData_Specifi( 
					 UBYTE	*Line, 
					 UBYTE	*LineCnt, 
					 UBYTE	*Item, 
					 UBYTE	BoxCnt ) 	/*1明細印刷*/
{
	UBYTE	i;
	struct SYS_DialData_t	*dial;
	register WORD	ret;					/*実行結果*/

	if (*LineCnt == (PaperSizeLen() - 5)) {	/* ２ページ目以降の先頭行の時 */
		/* ┌─┬────┬───────────────┐ */
		Print_F_CodeBox_List_Line( 9, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*LineCnt)--;
	}
	else {
		if ((*Item == 1) &&	/* 配信先の１行目 */
			(*Line == 0)) {
			/* |   |          ├────┴────┴──┴──┤ */
			Print_F_CodeBox_List_Line( 5, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			(*LineCnt)--;
		}
	}

	for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
		dial->Onetouch[i] = SYB_SubAddressBoxTable[BoxCnt].Onetouch[i];
	}
	for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
		dial->Speed[i] = SYB_SubAddressBoxTable[BoxCnt].Speed[i];
	}
	dial->Group = SYB_SubAddressBoxTable[BoxCnt].Group;

	while( *LineCnt != 0 ){
		Print_F_CodeBox_List_Line( 6, List.S.Print, List.S.Attribute );
		switch (*Item) {		/* 出力項目番号 */
		case	1:	/* 配信先出力 */
			if (*Line == 0) {
				List.S.Print[6-1] = '(';
				AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_RelayName, LST_NOT );
				List.S.Print[13-1] = ')';
			}
			/** ﾀﾞｲﾔﾙ番号の文字列変換 */
			ret = ProgramDataDialToString( dial, SYS_PRG_DIAL_MAX, List.S.Work, *Line );
			CMN_StringCopy( &List.S.Print[23-1], List.S.Work );
			if (DialCheckPointer == SYS_EMPTY_DIAL) {	/* 全明細内容出力 */
				(*Item) = 2;
			}
			else {
				(*Line)++;
			}
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			(*LineCnt)--;
			break;
		case	2:	/* 発信元付属出力 */
			/*�､(発信元)�､XXXXXXXXX�､*/
			List.S.Print[6-1] = '(';
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_PutSubscriber, LST_NOT );
			List.S.Print[13-1] = ')';
			if (SYB_SubAddressBoxTable[BoxCnt].Option & SUB_ADDRESS_OPTION_TTI_INSIDE) { /** 上書きとなっている場合 */
				AttributeSet( &List.S.Print[23-1], &List.S.Attribute[23-1], PWRD_Replace, LST_NOT );
			}
			else if (SYB_SubAddressBoxTable[BoxCnt].Option & SUB_ADDRESS_OPTION_TTI_AVAIL) { /** 外付けとなっている場合 */
				AttributeSet( &List.S.Print[23-1], &List.S.Attribute[23-1], PWRD_Avail, LST_NOT );
			}
			else {
				AttributeSet( &List.S.Print[23-1], &List.S.Attribute[23-1], PWRD_NoTTI, LST_NOT );
			}
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			(*LineCnt)--;
			(*Item) = 3;
			break;
		case	3:	/* 同時ﾌﾟﾘﾝﾄ */
			/*�､(同時ﾌﾟﾘﾝﾄ)�､XXX                �､*/
			List.S.Print[6-1] = '(';
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_RxPrint, LST_NOT );
			List.S.Print[17-1] = ')';
			if (SYB_SubAddressBoxTable[BoxCnt].Option & SUB_ADDRESS_OPTION_PRINT) {
				AttributeSet( &List.S.Print[23-1], &List.S.Attribute[23-1], PWRD_On, LST_NOT );
			}
			else {
				AttributeSet( &List.S.Print[23-1], &List.S.Attribute[23-1], PWRD_Off, LST_NOT );
			}
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			(*LineCnt)--;
			(*Item) = 0;
			return( OK );
			break;
		default:
			break;
		}
	}
	return( OK );
}


#endif	/* PRO_FCODE_RELAY == ENABLE */

#endif
