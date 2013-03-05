/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_BATB.C
*	Author		: 桑原 美紀
*	Date		: 1997/09/19
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 消耗品発注票
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\sysdial.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\lst_def.h"
#include "\src\atlanta\define\unisw_h.h"

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\lst_pro.h"
#include "\src\atlanta\define\uni_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\lst_data.h"
#include "\src\atlanta\ext_v\lst_wrd.h"
#include "\src\atlanta\ext_v\lst_tbl.h"
#include "\src\atlanta\ext_v\rom_tbl.h"
#include "\src\atlanta\ext_v\sys_data.h"

/*************************************************************************
	module		:[消耗品発注票印刷]
	function	:[消耗品発注票を印刷する]
	common		:[
		List				:
	]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/09/19]
	author		:[桑原美紀]
*************************************************************************/
WORD					Print_ConsumerOrder_Sheet(
						 void )					/*なし*/
{
	register WORD	ret;			/*実行結果*/
	UBYTE	i;						/*loop*/
	UBYTE	length;					/*発信元社名の文字数*/
	UBYTE	item;					/*発注品目*//* By M.Tachibana 1998/01/31 */

#if defined(JPN) /* 日本仕様 と 海外仕様でフォーマットが異なります By S.Fukui Oct.21,1997 */
	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* 見出し */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
	AttributeSet( &List.S.Print[28-1], &List.S.Attribute[28-1], PWRD_ConsumerOrderSheet_K, LST_NOT );  /* modified by honda 32 -> 28 */
 #else
	AttributeSet( &List.S.Print[32-1], &List.S.Attribute[32-1], PWRD_ConsumerOrderSheet, LST_XXX_TWI_XXX );
 #endif
	if ( (ret = CharacterPrint( (UBYTE)LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/**現在時間 */
#if (0)			/* 時間の列に発注元社名も出力する為 97/12/12 By M.Kuwahara */
//	if ( (ret = CurrentTimePrint( 60-1 )) != OK ) {
//		return ( ret );
//	}
#endif
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	if ( SYB_ConsumerOrder.FromCompany[0] != 0x00 ) {	/* 発注元社名が入力されている時 */
		CMN_StringCopy( &List.S.Print[2-1], SYB_ConsumerOrder.FromCompany);
		length = CMN_StringLength( SYB_ConsumerOrder.FromCompany );
	}
	else{
/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
 #if (PRO_LINENUMBER == TWICE_LINE)
		CMN_StringCopy( &List.S.Print[2-1], &SYB_TTI_Buffer[0][0]);
		length = CMN_StringLength( SYB_TTI_Buffer[0] );
 #else
		CMN_StringCopy( &List.S.Print[2-1], SYB_TTI_Buffer);
		length = CMN_StringLength( SYB_TTI_Buffer );
 #endif
	}

 #if (PRO_LINENUMBER == TWICE_LINE)
	if (( SYB_ConsumerOrder.FromCompany[0] != 0x00 ) ||	/* 発注元社名かＴＴＩが入力されている時、"様"をセット */
		( SYB_TTI_Buffer[0][0] != 0x00 )) {
 #else
	if (( SYB_ConsumerOrder.FromCompany[0] != 0x00 ) ||	/* 発注元社名かＴＴＩが入力されている時、"様"をセット */
		( SYB_TTI_Buffer[0] != 0x00 )) {
 #endif
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		List.S.Print[4+length-1]	= 0x97;		/* '様' */
		List.S.Print[5+length-1]	= 0x6c;
 #endif
	}

	TimeDataAscii( OFF, SYB_CurrentTime, List.S.Work, 0 );
	CMN_StringCopy( &List.S.Print[60-1], List.S.Work);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* "トナーの交換が必要になりました。" 以下１７行追加 97/12/12 By M.Kuwahara */
	/* ﾄﾅｰ発注とﾄﾅｰ/ﾄﾞﾗﾑ発注をｽｲｯﾁで判別 97/12/19 By M.Kuwahara */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	if (( CHK_UNI_OrderListPrint() & DRUM_ORDER_LIST_PRINT ) == DRUM_ORDER_LIST_PRINT ) {
		AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_OrderTonerDrumChange, LST_NOT );
	}
	else {
		AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_OrderTonerChange, LST_NOT );
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* "お手数ですが、この用紙を使ってご注文下さい。" */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_OrderSheet, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* 発注先得意先コード */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_ToOrder, LST_NOT );
	AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_CustomerCode, LST_NOT );
	List.S.Print[26-1]	= ':';
	CMN_StringCopy( &List.S.Print[28-1], SYB_ConsumerOrder.ToCustomerCode);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* 発注先社名 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_DistributorName, LST_NOT );
	List.S.Print[26-1]	= ':';
	CMN_StringCopy( &List.S.Print[28-1], SYB_ConsumerOrder.ToCompany);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* 発注元得意先コード */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_FromOrder, LST_NOT );
	AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_CustomerCode, LST_NOT );
	List.S.Print[26-1]	= ':';
	CMN_StringCopy( &List.S.Print[28-1], SYB_ConsumerOrder.FromCustomerCode);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* 発注元社名 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_CustomerName, LST_NOT );
	List.S.Print[26-1]	= ':';
	if ( SYB_ConsumerOrder.FromCompany[0] != 0x00 ) {	/* 発注元社名が入力されている時 */
		CMN_StringCopy( &List.S.Print[28-1], SYB_ConsumerOrder.FromCompany);
	}
	else{

/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
 #if (PRO_LINENUMBER == TWICE_LINE)
		CMN_StringCopy( &List.S.Print[28-1], &SYB_TTI_Buffer[0][0]);
 #else
		CMN_StringCopy( &List.S.Print[28-1], SYB_TTI_Buffer);
 #endif

	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* 発注元部課名 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_Section, LST_NOT );
	List.S.Print[26-1]	= ':';
	CMN_StringCopy( &List.S.Print[28-1], SYB_ConsumerOrder.FromSection);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* 発注元ＴＥＬ */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_Tel, LST_NOT );
	List.S.Print[26-1]	= ':';
	CMN_StringCopy( &List.S.Print[28-1], SYB_ConsumerOrder.FromTelNumber);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* 発注元ＦＡＸ */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_Fax, LST_NOT );
	List.S.Print[26-1]	= ':';

/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
 #if (PRO_LINENUMBER == TWICE_LINE)
	CMN_StringCopy( &List.S.Print[28-1], &SYB_ID_Buffer[0][0]);
 #else
	CMN_StringCopy( &List.S.Print[28-1], SYB_ID_Buffer);
 #endif

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* 発注元担当者名 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_ChargeName, LST_NOT );
	List.S.Print[26-1]	= ':';
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
	List.S.Print[49-1]	= 0x88;		/* '印' */
	List.S.Print[50-1]	= 0xf3;
 #endif
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_MemorySet( &List.S.Print[28-1], 20, LST_KLINE_ );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* モデル名 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_ModelName, LST_NOT );
	List.S.Print[13-1]	= ':';
	for( i = 0; LST_ModelChangeTable[i].FromModel[0] != 0x00; i++ ) {	/* 該当モデル名まで検索 */
		if ( CMN_StringCompare(ROM_Revision, LST_ModelChangeTable[i].FromModel, 5) == 0 ) {
			CMN_StringCopy( &List.S.Print[15-1], LST_ModelChangeTable[i].ToModel);
			break;
		}
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* シリアルＮｏ． */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_SeirialNumber, LST_NOT );
	List.S.Print[13-1]	= ':';
	CMN_StringCopy( &List.S.Print[15-1], SYB_ConsumerOrder.SerialNumber);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* 設置日 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_InstallDate, LST_NOT );
	List.S.Print[13-1]	= ':';
	if ( SYB_ConsumerOrder.InstallDate != NULL ) {		/** 設置日がｾｯﾄされていない時は無し 1998/02/27 By M.Kuwahara */
		CriterionMinuteToDayTimeAsc( SYB_ConsumerOrder.InstallDate/60, LST_YYMMDD, List.S.Work );
		CMN_StringCopy( &List.S.Print[15-1], List.S.Work );
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* 発注品目 */
	/*
	** ListCloseによりプリントページ数が加算され発注品目が
	** 変わる可能性があるため	By M.Tachibana 1998/01/31
	*/
	item = SYB_ConsumerOrderListRequest;	/* By M.Tachibana 1998/01/31 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_OrderItem, LST_NOT );
	List.S.Print[13-1]	= ':';
	/* ﾄﾅｰ発注とﾄﾅｰ/ﾄﾞﾗﾑ発注をｽｲｯﾁで判別 97/12/19 By M.Kuwahara */
	switch( CHK_UNI_OrderListPrint() ) {
	case	TONER_ORDER_LIST_PRINT:
		AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_TonerOrder1, LST_NOT );
		break;
	case	DRUM_ORDER_LIST_PRINT:
		AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_DrumOrder1, LST_NOT );
		break;
	default:
#if (0)	/* フォーマット変更 By M.Tachibana 1998/01/31 */
		AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_TonerOrder1, LST_NOT );
		AttributeSet( &List.S.Print[28-1], &List.S.Attribute[28-1], PWRD_DrumOrder1, LST_NOT );
		/* トナー警告後、未交換ならドラム交換要求時でも反転印字します。*/
		if ( SYB_PrinterLifeMonitor.TonerLifeCount > 0 ) {
			CMN_MemorySet( &List.S.Attribute[15-1], 5, LST_INV_XXX_XXX );
		}
		/* ドラム警告後、未交換ならトナー交換要求時でも反転印字します。*/
		if ( SYB_PrinterLifeMonitor.DrumLifeCount > (UDWORD)PRN_DrumPrintMax ) {
			CMN_MemorySet( &List.S.Attribute[28-1], 5, LST_INV_XXX_XXX );
		}
#endif
		switch (item){
		case SYS_ORDER_ITEM_TONER:
			AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_TonerOrder1, LST_NOT );
			break;
		case SYS_ORDER_ITEM_DRUM:
			AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_DrumOrder1, LST_NOT );
			break;
		default:	/* SYS_ORDER_ITEM_TONER|SYS_ORDER_ITEM_DRUM */
			AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_TonerOrder1, LST_NOT );
			AttributeSet( &List.S.Print[28-1], &List.S.Attribute[28-1], PWRD_DrumOrder1, LST_NOT );
			break;
		}
		break;
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* 備考 */	/* 備考欄５行から３行に変更 97/12/12 By M.Kuwahara */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
#if (0)	/* 専用のﾜｰﾃﾞｨﾝｸﾞがあるので、そちらを使用します by K.Watanabe 1998/08/24 */
//	AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1], PWRD_Note, LST_NOT );
#endif
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_Remarks, LST_NOT );
	List.S.Print[13-1]	= ':';
	for ( i = 0; i < 3; i++ ) {
		if ( i != 0 ) {
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		}
		CMN_MemorySet( &List.S.Print[15-1], 60, LST_KLINE10 );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		if (i != 2) {		/* 最後のラインは改行無し */
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
		}
	}

	/* ドラム印字枚数／ソフトウェアバージョン */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_UnsignedLongToASC(&List.S.Print[61-1], SYB_PrinterLifeMonitor.DrumLifeCount, 5, ' ');	/* Int -> Long By M.Tachibana 1997/12/12 */
	List.S.Print[66-1]	= '/';
/*	CMN_StringCopyNum( &List.S.Print[67-1], &ROM_Revision[10], 6); */	/* 97/11/29 By M.Kuwahara */
	CMN_StringCopyNumNotNULL( &List.S.Print[67-1], &ROM_Revision[10], 6);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*１行印字（改行）*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}

/*	SYB_ConsumerOrderListRequest = 0;	By M.Tachibana 1998/01/31 */
	SYB_ConsumerOrderListRequest &= ~item;
	return ( OK );

#elif defined(US1)	/* if defined(JPN) *//* これは海外仕様Pitney Bowes（ＵＳ１）のフォーマット orderbythonda1998/11/11 */

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}


	/**********/
	/* 見出し */
	/**********/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
	AttributeSet( &List.S.Print[32-1], &List.S.Attribute[32-1], PWRD_ConsumerOrderSheet_K, LST_NOT );
 #else
/*	AttributeSet( &List.S.Print[12-1], &List.S.Attribute[12-1], PWRD_ConsumerOrderSheet, LST_XXX_TWI_XXX ); */
	AttributeSet( &List.S.Print[8-1], &List.S.Attribute[8-1], PWRD_ConsumerOrderSheet, LST_XXX_TWI_XXX );
/*	AttributeSet( &List.S.Print[12-1], &List.S.Attribute[12-1], PWRD_ConsumerOrderSheet, LST_NOT ); */
 #endif
	if ( (ret = CharacterPrint( (UBYTE)LST_PRINT )) != OK ) {
		return ( ret );
	}

	/***********/
	/* 見出し2 */
	/***********/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
	AttributeSet( &List.S.Print[32-1], &List.S.Attribute[32-1], PWRD_ConsumerOrderSheet_K, LST_NOT );
 #else
	AttributeSet( &List.S.Print[19-1], &List.S.Attribute[19-1], PWRD_ConsumerOrderSheet2, LST_XXX_TWI_XXX );
 #endif
	if ( (ret = CharacterPrint( (UBYTE)LST_PRINT )) != OK ) {
		return ( ret );
	}


	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}


	/************/
	/**現在時間 */
	/************/
	if ( (ret = CurrentTimePrint( 60-1 )) != OK ) {
		return ( ret );
	}
	
 #if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN) /* orderbythonda1998/05/18 */
	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
 #endif


	/***********************************************************************************/
	/* "Your machine's display indicates that either the Toner Cartridge or Drum Unit" */
	/***********************************************************************************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_OrderTonerDrumChange, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	/***************************/
	/* "requires replacement." */
	/***************************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_OrderTonerDrumChange2, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}


	/********************************************************************************/
	/* "To order replacements by phone, call xxxxxxxxxxxxxx, or fill out this form" */
	/********************************************************************************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_OrderSheet, LST_NOT );
	AttributeSet( &List.S.Print[39-1], &List.S.Attribute[39-1], SYB_ToCompanyTelNumber, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	/***********************************/
	/* "and fax it to xxxxxxxxxxxxxx." */
	/***********************************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_OrderSheet2, LST_NOT );
/*	AttributeSet( &List.S.Print[40-1], &List.S.Attribute[40-1], SYB_ToCompanyFaxNumber, LST_NOT ); */
	AttributeSet( &List.S.Print[16-1], &List.S.Attribute[16-1], SYB_ToCompanyFaxNumber, LST_NOT );
/*	AttributeSet( &List.S.Print[38-1], &List.S.Attribute[38-1], SYB_ToCompanyFaxNumber, LST_NOT ); */
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}


	/**************/
	/* 発注先社名 */
	/**************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_ToOrder, LST_NOT );
/*	List.S.Print[8-1]	= ':'; */
/*	AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_DistributorName, LST_NOT ); */
	CMN_StringCopy( &List.S.Print[7-1], SYB_ConsumerOrder.ToCompany);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}


	/**************/
	/* 発注元社名 */
	/**************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_FromOrder, LST_NOT );
/*	List.S.Print[8-1]	= ':'; */
/*	AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_CustomerName, LST_NOT ); */
	if ( SYB_ConsumerOrder.FromCompany[0] != 0x00 ) {	/* 発注元社名が入力されている時 */
		CMN_StringCopy( &List.S.Print[14-1], SYB_ConsumerOrder.FromCompany);
	}
	else{

/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
 #if (PRO_LINENUMBER == TWICE_LINE)
		CMN_StringCopy( &List.S.Print[31-1], &SYB_TTI_Buffer[0][0]);
 #else
		CMN_StringCopy( &List.S.Print[31-1], SYB_TTI_Buffer);
 #endif

	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/****************/
	/* 発注元部課名 */
	/****************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
/*	AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_Section, LST_NOT ); */
	CMN_StringCopy( &List.S.Print[14-1], SYB_ConsumerOrder.FromSection);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

 #if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)

	/******************/
	/* 発注元部課名２ *//* orderbythonda1998/05/18 */
	/******************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_StringCopy( &List.S.Print[14-1], SYB_ConsumerOrderFromSection2);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
 #endif


 #if (0)	/* orderbythonda1998/11/11 */
	/****************/
	/* 発注元ＦＡＸ */
	/****************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_Fax, LST_NOT );

/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
 #if (PRO_LINENUMBER == TWICE_LINE)
	CMN_StringCopy( &List.S.Print[31-1], &SYB_ID_Buffer[0][0]);
 #else
	CMN_StringCopy( &List.S.Print[31-1], SYB_ID_Buffer);
 #endif
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
 #endif


	/****************/
	/* 発注元ＴＥＬ */
	/****************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
/*	AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_Tel, LST_NOT ); */
	CMN_StringCopy( &List.S.Print[14-1], SYB_ConsumerOrder.FromTelNumber);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


 #if (0)	/* orderbythonda1998/11/11 */
	/**********************/
	/* 発注元得意先コード */
	/**********************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_CustomerCode, LST_NOT );
	CMN_StringCopy( &List.S.Print[31-1], SYB_ConsumerOrder.FromCustomerCode);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
 #endif


	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}


	/************/
	/* モデル名 */
	/************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_ModelName, LST_NOT );
	for( i = 0; LST_ModelChangeTable[i].FromModel[0] != 0x00; i++ ) {	/* 該当モデル名まで検索 */
		if ( CMN_StringCompare(ROM_Revision, LST_ModelChangeTable[i].FromModel, 5) == 0 ) {
			CMN_StringCopy( &List.S.Print[14-1], LST_ModelChangeTable[i].ToModel);
			break;
		}
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/******************/
	/* シリアルＮｏ． */
	/******************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_SeirialNumber, LST_NOT );
	CMN_StringCopy( &List.S.Print[14-1], SYB_ConsumerOrder.SerialNumber);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


 #if (0)	/* orderbythonda1998/11/11 */
	/**********/
	/* 設置日 */
	/**********/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_InstallDate, LST_NOT );
	if ( SYB_ConsumerOrder.InstallDate != NULL ) {		/** 設置日がｾｯﾄされていない時は無し 1998/02/27 By M.Kuwahara */
		CriterionMinuteToDayTimeAsc( SYB_ConsumerOrder.InstallDate/60, LST_YYMMDD, List.S.Work );
		CMN_StringCopy( &List.S.Print[31-1], List.S.Work );
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
 #endif


	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}


	/*********************/
	/* 発注品目 (トナー）*/
	/*********************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_OrderItem, LST_NOT );
	AttributeSet( &List.S.Print[21-1], &List.S.Attribute[21-1], PWRD_TonerOrder1, LST_NOT );
			/* トナー警告後、未交換ならドラム交換要求時でも反転印字します。 By S.Fukui Nov.25,1997 */
	if ( SYB_PrinterLifeMonitor.TonerLifeCount > 0 ) {
		CMN_MemorySet( &List.S.Attribute[21-1], 5, LST_INV_XXX_XXX );
	}
	CMN_MemorySet( &List.S.Print[39-1], 5, LST_KLINE10 );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}


	/**********************/
	/* 発注品目 （ドラム）*/
	/**********************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[21-1], &List.S.Attribute[21-1], PWRD_DrumOrder1, LST_NOT );
			/* ドラム警告後、未交換ならトナー交換要求時でも反転印字します。 By S.Fukui Nov.25,1997 */
	if ( SYB_PrinterLifeMonitor.DrumLifeCount > (UDWORD)PRN_DrumPrintMax ) {
		CMN_MemorySet( &List.S.Attribute[21-1], 5, LST_INV_XXX_XXX );
	}
	CMN_MemorySet( &List.S.Print[39-1], 5, LST_KLINE10 );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}


	/********/
	/* 備考 */ /* 備考欄４行から２行に変更 By S.Fukui Dec.26,1997 */
	/********/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_Remarks, LST_NOT );
 #if (0)	/* orderbythonda1998/11/11 */
	for ( i = 0; i < 2; i++ ) {
		if ( i != 0 ) {
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		}
		CMN_MemorySet( &List.S.Print[10-1], 65, LST_KLINE10 );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
	}
 #endif
	CMN_MemorySet( &List.S.Print[41-1], 34, LST_KLINE10 );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}


	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_MemorySet( &List.S.Print[2-1], 73, LST_KLINE10 );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}


	/**************************/
	/* サイン ＆ 活字体記入欄 */
	/**************************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_ChargeName, LST_NOT );
	AttributeSet( &List.S.Print[50-1], &List.S.Attribute[50-1], PWRD_BlockLetters, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/* １行改行 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_MemorySet( &List.S.Print[2-1], 73, LST_KLINE_ );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/******************************************/
	/* ドラム印字枚数／ソフトウェアバージョン */
	/******************************************/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
 #if (0)	/* ordetbythonda1998/11/4 *//* ドラム印字枚数は載せない */
	CMN_UnsignedLongToASC(&List.S.Print[61-1], SYB_PrinterLifeMonitor.DrumLifeCount, 5, ' ');	/* Int -> Long By M.Tachibana 1997/12/12 */
	List.S.Print[66-1]	= '/';
 #endif
/*	CMN_StringCopyNum( &List.S.Print[67-1], &ROM_Revision[10], 6);*/	/* 97/11/29 By M.Kuwahara */
	CMN_StringCopyNumNotNULL( &List.S.Print[67-1], &ROM_Revision[10], 6);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/*１行印字（改行）*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}

	SYB_ConsumerOrderListRequest = 0;
	return ( OK );

#else	/* これ以下は海外仕様でPitney Bowes（ＵＳ１）以外のフォーマット orderbythonda1998/11/11 */

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* 見出し */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
	AttributeSet( &List.S.Print[32-1], &List.S.Attribute[32-1], PWRD_ConsumerOrderSheet_K, LST_NOT );
 #else
	AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_ConsumerOrderSheet, LST_XXX_TWI_XXX );
 #endif
	if ( (ret = CharacterPrint( (UBYTE)LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/**現在時間 */
	if ( (ret = CurrentTimePrint( 60-1 )) != OK ) {
		return ( ret );
	}
	
 #if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN) /* orderbythonda1998/05/18 */
	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
 #endif
	/* "トナーの交換が必要になりました。"  By S.Fukui Dec.26,1997 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_OrderTonerDrumChange, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* "お手数ですが、この用紙を使ってご注文下さい。" */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1], PWRD_OrderSheet, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* 発注先社名 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_ToOrder, LST_NOT );
	List.S.Print[8-1]	= ':';
	AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_DistributorName, LST_NOT );
	CMN_StringCopy( &List.S.Print[31-1], SYB_ConsumerOrder.ToCompany);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* 発注元得意先コード */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_FromOrder, LST_NOT );
	List.S.Print[8-1]	= ':';
	AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_CustomerName, LST_NOT );

	if ( SYB_ConsumerOrder.FromCompany[0] != 0x00 ) {	/* 発注元社名が入力されている時 */
		CMN_StringCopy( &List.S.Print[31-1], SYB_ConsumerOrder.FromCompany);
	}
	else{

/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
 #if (PRO_LINENUMBER == TWICE_LINE)
		CMN_StringCopy( &List.S.Print[31-1], &SYB_TTI_Buffer[0][0]);
 #else
		CMN_StringCopy( &List.S.Print[31-1], SYB_TTI_Buffer);
 #endif

	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/* 発注元ＦＡＸ */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_Fax, LST_NOT );

/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
 #if (PRO_LINENUMBER == TWICE_LINE)
	CMN_StringCopy( &List.S.Print[31-1], &SYB_ID_Buffer[0][0]);
 #else
	CMN_StringCopy( &List.S.Print[31-1], SYB_ID_Buffer);
 #endif
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/* 発注元ＴＥＬ */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_Tel, LST_NOT );
	CMN_StringCopy( &List.S.Print[31-1], SYB_ConsumerOrder.FromTelNumber);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* 発注元部課名 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_Section, LST_NOT );
	CMN_StringCopy( &List.S.Print[31-1], SYB_ConsumerOrder.FromSection);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)
	/* 発注元部課名２ *//* orderbythonda1998/05/18 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_StringCopy( &List.S.Print[31-1], SYB_ConsumerOrderFromSection2);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
#endif

	/* 発注元得意先コード */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_CustomerCode, LST_NOT );
	CMN_StringCopy( &List.S.Print[31-1], SYB_ConsumerOrder.FromCustomerCode);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}


	/* モデル名 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_ModelName, LST_NOT );
	for( i = 0; LST_ModelChangeTable[i].FromModel[0] != 0x00; i++ ) {	/* 該当モデル名まで検索 */
		if ( CMN_StringCompare(ROM_Revision, LST_ModelChangeTable[i].FromModel, 5) == 0 ) {
			CMN_StringCopy( &List.S.Print[31-1], LST_ModelChangeTable[i].ToModel);
			break;
		}
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* シリアルＮｏ． */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_SeirialNumber, LST_NOT );
	CMN_StringCopy( &List.S.Print[31-1], SYB_ConsumerOrder.SerialNumber);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* 設置日 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_InstallDate, LST_NOT );
	if ( SYB_ConsumerOrder.InstallDate != NULL ) {		/** 設置日がｾｯﾄされていない時は無し 1998/02/27 By M.Kuwahara */
		CriterionMinuteToDayTimeAsc( SYB_ConsumerOrder.InstallDate/60, LST_YYMMDD, List.S.Work );
		CMN_StringCopy( &List.S.Print[31-1], List.S.Work );
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* 発注品目 (トナー）*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_OrderItem, LST_NOT );
	AttributeSet( &List.S.Print[31-1], &List.S.Attribute[31-1], PWRD_TonerOrder1, LST_NOT );

			/* トナー警告後、未交換ならドラム交換要求時でも反転印字します。 By S.Fukui Nov.25,1997 */
	if ( SYB_PrinterLifeMonitor.TonerLifeCount > 0 ) {
		CMN_MemorySet( &List.S.Attribute[31-1], 5, LST_INV_XXX_XXX );
	}

	CMN_MemorySet( &List.S.Print[39-1], 5, LST_KLINE10 );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* 発注品目 （ドラム）*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[31-1], &List.S.Attribute[31-1], PWRD_DrumOrder1, LST_NOT );
			/* ドラム警告後、未交換ならトナー交換要求時でも反転印字します。 By S.Fukui Nov.25,1997 */
	if ( SYB_PrinterLifeMonitor.DrumLifeCount > (UDWORD)PRN_DrumPrintMax ) {
		CMN_MemorySet( &List.S.Attribute[31-1], 5, LST_INV_XXX_XXX );
	}
	CMN_MemorySet( &List.S.Print[39-1], 5, LST_KLINE10 );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* 備考 */ /* 備考欄４行から２行に変更 By S.Fukui Dec.26,1997 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_Remarks, LST_NOT );
	for ( i = 0; i < 2; i++ ) {
		if ( i != 0 ) {
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		}
		CMN_MemorySet( &List.S.Print[10-1], 65, LST_KLINE10 );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
	}


	/* サイン ＆ 活字体記入欄 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_ChargeName, LST_NOT );
	AttributeSet( &List.S.Print[37-1], &List.S.Attribute[37-1], PWRD_BlockLetters, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* １行改行 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_MemorySet( &List.S.Print[2-1], 73, LST_KLINE_ );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/* ドラム印字枚数／ソフトウェアバージョン */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_UnsignedLongToASC(&List.S.Print[61-1], SYB_PrinterLifeMonitor.DrumLifeCount, 5, ' ');	/* Int -> Long By M.Tachibana 1997/12/12 */
	List.S.Print[66-1]	= '/';
/*	CMN_StringCopyNum( &List.S.Print[67-1], &ROM_Revision[10], 6);*/	/* 97/11/29 By M.Kuwahara */
	CMN_StringCopyNumNotNULL( &List.S.Print[67-1], &ROM_Revision[10], 6);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*１行印字（改行）*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}

	SYB_ConsumerOrderListRequest = 0;
	return ( OK );
#endif

}

