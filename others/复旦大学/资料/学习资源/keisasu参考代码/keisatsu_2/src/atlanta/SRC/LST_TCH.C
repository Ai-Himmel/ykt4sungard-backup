/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_TCH.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ダイヤルリスト（ワンタッチ）
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include	"\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
/*#include	"\src\memsw\define\mem_sw_h.h" /*1996/04/17 Eguchi*/

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"

/*************************************************************************
	module		:[ダイヤルリスト（ワンタッチ）]
	functiom	:[ダイヤルリスト（ワンタッチ）を印刷する]
	common		:[
		List			:
		SYB_OnetouchDial:
	]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/28]
	author		:[豊田浩子]
*************************************************************************/
WORD				Print_OnetouchDial_List(
						 void )			/*なし*/
{
	UBYTE 	i;						/*loop*/
	UBYTE 	page;					/*ﾍﾟｰｼﾞ*/
	UBYTE 	line_cnt;				/*残り印刷可能行数*/
	UBYTE 	search_str[LST_COMP_LEN+1];/*ｻｰﾁ文字列*/
	UBYTE 	kind;					/*ｻｰﾁ種類*/
	WORD	one_cnt;				/*ﾜﾝﾀｯﾁﾃﾞｰﾀ番号*/
	register WORD	ret;			/*実行結果*/
												/*LST_SEARCH_ASCII*/
												/*LST_SEARCH_NUMBER*/
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
	UBYTE 	next_line;				/* ｻｰﾁ行数 */
#else
	UBYTE 	sub_dial_flag;			/* 転送先があれば1 */
#endif

	page = 1;
	one_cnt = -1;
	CMN_MemorySetNULL( search_str, LST_COMP_LEN, ' ' );

	if ( CHK_DialListPrint() ) {		/* I:0-6 */
		kind = LST_SEARCH_ASCII;
	}
	else {
		kind = LST_SEARCH_NUMBER;
	}

#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
	next_line = OnetouchDataNextSearch( kind, &one_cnt, search_str);	/*ﾃﾞｰﾀ頭出し */
#else
	OnetouchDataNextSearch( kind, &one_cnt, search_str, &sub_dial_flag );	/*ﾃﾞｰﾀ頭出し (引数追加 95/06/27 石橋正和) */
#endif

	while ( one_cnt != (WORD)SYS_ONETOUCH_MAX ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		if ( page == 1 ) {
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*印刷可能行数ｾｯﾄ*/
		}
		else {
			line_cnt = (UBYTE)(PaperSizeLen() - 4);/*印刷可能行数ｾｯﾄ*/
		}
		if ( (ret = Print_SpeedDial_List_Head(0, page, LST_ONETOUCHDIAL_LIST) ) != OK ) {	/*ﾍｯﾀﾞ印刷*/
			return ( ret );
		}

		for ( i = 0;; i++ ) {
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
			/*印刷予定行数が印刷可能か判断*/
			if (next_line >= line_cnt || line_cnt < 2 ) {
				break;
			}
			if ( (ret = Print_Dial_List_Specifi(LST_ONETOUCH, page, i, one_cnt, &line_cnt ) ) != OK ) {	/*1明細印刷*/
				return ( ret );
			}
			next_line = OnetouchDataNextSearch( kind, &one_cnt, search_str);	/*次ﾃﾞｰﾀｻｰﾁ */
#else
			/*印刷予定行数が印刷可能か判断*/
			if ((sub_dial_flag && (line_cnt < 3)) || line_cnt < 2 ) { /* 条件変更 95/06/27 石橋正和 */
				break;
			}
			if ( (ret = Print_OnetouchDial_List_Specifi(page, i, (UBYTE)one_cnt, &line_cnt) ) != OK ) {	/*1明細印刷*/
				return ( ret );
			}
			OnetouchDataNextSearch( kind, &one_cnt, search_str, &sub_dial_flag );	/*次ﾃﾞｰﾀｻｰﾁ (引数追加 95/06/27 石橋正和) */
#endif
			if ( one_cnt == (WORD)SYS_ONETOUCH_MAX ) {
				break;
			}
		}

		if ( (ret = Print_SpeedDial_List_Head(1, page, LST_ONETOUCHDIAL_LIST) ) != OK ) {	/*ﾌｯﾀ印刷*/
			return ( ret );
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	/**  個別設定の時は属性リストを出力する  */
	if (CHK_SpeedDialSparateSet()) {
		if ( (ret = PrintDialAttributeList(LST_ONETOUCHDIAL_LIST)) != OK) {
			return (ret);
		}
	}
	return ( OK );
}
/*************************************************************************
	module		:[ダイヤルリスト（ワンタッチ）の１明細印刷]
	functiom	:[ダイヤルリスト（ワンタッチ）の１明細を印刷する。]
	common		:[
		List				:
		SYB_OnetouchDial	:
	]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/28]
	author		:[豊田浩子]
*************************************************************************/
#if (PRO_DIAL_LIST_GROUP == DISABLE)	/* by K.Watanabe 1999/05/24 */
WORD				Print_OnetouchDial_List_Specifi(
						 UBYTE Page,		/*ページ*/
						 UBYTE Line,		/*現在明細数*/
						 UBYTE OnetouchCnt,	/*ワンタッチダイヤル番号*/
						 UBYTE *LineCnt )	/*印字行位置*/
{
	register WORD	ret;					/*実行結果*/

#if defined(KEISATSU)		/* 警察ＦＡＸ属性追加 Added by SMuratec 夏 2005/07/21 */
	UBYTE	kei_buf[4];
	UBYTE	kei_pos;
	kei_pos = 0;
#endif
	
#if 0	/* プレフィックス＋ダイヤル番号で40桁を超えても折り返して印字しないので、大島さん確認の上、リストでの展開は止めます by K.Watanabe 2004/11/12 */
//#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/10 *//* by K.Watanabe 2004/10/12 */
//	UWORD	length;
#endif			/*	End of defined(STOCKHM2)	*/

	if ( Page > 1 && Line == 0 ) {
		/*・・・・・・・・・・・・─・*/
		Print_Dial_List_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	else {
		/*・・・・・・・・・・・・─・*/
		Print_Dial_List_Line( 2, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	/*・xＸx・xxxxxx・xxxxxxxxx・xxxxxxxx│*/
	Print_Dial_List_Line( 3, List.S.Print, List.S.Attribute );
	/* No. */
	/* List.S.Print[2-1] = '[';
	List.S.Print[4-1] = ']';
	List.S.Print[3-1] = CMN_OffsetToOnetouchCode( OnetouchCnt ); */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	if ( CMN_OffsetToOnetouchCode( OnetouchCnt ) <= 0x7A ){ /* ﾜﾝﾀｯﾁ記号が変更(ANZU) 96/01/10 H.HIRAO */
		List.S.Print[2-1] = CMN_OffsetToOnetouchCode( OnetouchCnt );
	} else{
		List.S.Print[2-1] = 0x55;	/* 'U'のASCIIｺ-ﾄﾞ */
		List.S.Print[3-1] = CMN_OffsetToOnetouchCode( OnetouchCnt ) & (UBYTE)0x0F | (UBYTE)0x30; /* U1～U8記号をつくる*/	}
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_PANEL == ANK)
		List.S.Print[5-1] = '[';
		List.S.Print[8-1] = ']';
		CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(CMN_OffsetToOnetouchCode( OnetouchCnt ) - 0x40), 2, '0' );
 #endif
 #if (PRO_PANEL == KANJI)
 		/* ワンタッチの表示を[]->絵文字に変更 By O.Kimoto 1998/01/22 */
		List.S.Print[5-1] = LCD_PICFONT;
		List.S.Print[6-1] = LCD_PICFONT_LOWER;
		CMN_UnsignedIntToASC( &List.S.Print[7-1], (UWORD)(CMN_OffsetToOnetouchCode( OnetouchCnt ) - 0x40), 2, '0' );
 #endif
#endif
	/*相手先名*/
	/* CMN_StringCopy( &List.S.Print[6-1], SYB_OnetouchDial[OnetouchCnt].DialData.Onetouch.Name ); */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
 #if (PRO_MINOLTA_TEST_FUNC == DISABLE)	/* 1998/07/23 Y.Matsukuma */
	CMN_StringCopy( &List.S.Print[7-1], SYB_OnetouchDial[OnetouchCnt].Name ); /* 97/01/22 M.Kuwahara */
 #endif
#else	/* PANEL_POPLA_B/L/H */
	CMN_StringCopy( &List.S.Print[10-1], SYB_OnetouchDial[OnetouchCnt].Name ); /* 変更(ANZU) 95/12/14 H.HIRAO */
#endif

	
#if defined(KEISATSU)	/* 警察ＦＡＸ属性追加 Added by SMuratec 夏 2005/07/21 */
	/* SYB_OnetouchDial[OnetouchCnt].Keisatsu から、属性バッファを作成 */
	if (SYB_OnetouchDial[OnetouchCnt].Keisatsu & SYS_KEISATSU_KEIDEN){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "ｹ", 1);
		kei_pos++;
	}
	else if (SYB_OnetouchDial[OnetouchCnt].Keisatsu & SYS_KEISATSU_KANYU){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "ｶ", 1);
		kei_pos++;
	}

	if (SYB_OnetouchDial[OnetouchCnt].Keisatsu & SYS_KEISATSU_ISSEI){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "ｲ", 1);
		kei_pos++;
	}
	else if (SYB_OnetouchDial[OnetouchCnt].Keisatsu & SYS_KEISATSU_KOBETSU){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "ｺ", 1);
		kei_pos++;
	}

	if (SYB_OnetouchDial[OnetouchCnt].Keisatsu & SYS_KEISATSU_SCRAMBLE_ON){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "S", 1);
		kei_pos++;
	}
	else if (SYB_OnetouchDial[OnetouchCnt].Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "N", 1);
		kei_pos++;
	}

	if (SYB_OnetouchDial[OnetouchCnt].Keisatsu & SYS_KEISATSU_KYOTSU){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "ｷ", 1);
		kei_pos++;
	}
	else if (SYB_OnetouchDial[OnetouchCnt].Keisatsu & SYS_KEISATSU_SENYO){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "ｾ", 1);
		kei_pos++;
	}
	
	/* 属性がある、40桁番号の場合ご注意してください。*/
	if(kei_pos > 0){
		CMN_StringCopy( &List.S.Print[35-1], kei_buf ); 
		/*ﾀﾞｲﾔﾙ番号*/
		CMN_BCD_ToASC_String( List.S.Work, SYB_OnetouchDial[OnetouchCnt].Dial ); /* 変更(ANZU) 95/12/14 H.HIRAO */
		CMN_StringCopy( &List.S.Print[35+kei_pos-1], List.S.Work );
	}
	else{
		
		CMN_BCD_ToASC_String( List.S.Work, SYB_OnetouchDial[OnetouchCnt].Dial ); /* 変更(ANZU) 95/12/14 H.HIRAO */
		CMN_StringCopy( &List.S.Print[35-1], List.S.Work );
	}

#else	
	/* CMN_BCD_ToASC_String( (UBYTE *)List.S.Work, SYB_OnetouchDial[OnetouchCnt].DialData.Onetouch.Dial ); */
	CMN_BCD_ToASC_String( List.S.Work, SYB_OnetouchDial[OnetouchCnt].Dial ); /* 変更(ANZU) 95/12/14 H.HIRAO */
#endif

#if (PRO_KEYPANEL == PANEL_ANZU_L)
	CMN_StringCopy( &List.S.Print[24-1], List.S.Work );
	/*ｸﾞﾙｰﾌﾟNo*/
	/* GroupToShortString(
	  SYB_OnetouchDial[OnetouchCnt].DialData.Onetouch.Group, List.S.Work ); */
	GroupToShortString(
	  SYB_OnetouchDial[OnetouchCnt].Group, List.S.Work ); /* 変更(ANZU) 95/12/14 H.HIRAO */
	CMN_StringCopy( &List.S.Print[65-1], List.S.Work );
#else	/* PANEL_POPLA_B/L/H */
 #if 0	/* プレフィックス＋ダイヤル番号で40桁を超えても折り返して印字しないので、大島さん確認の上、リストでの展開は止めます by K.Watanabe 2004/11/12 */
// #if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/09 *//* by K.Watanabe 2004/10/12 */
//			if (List.S.Work[0] == '!'){
//				length = CMN_StringLength(SYB_MercuryDialBuffer);	/* マキュリー登録桁 */
//
//				List.S.Print[34] = '[';
//				if (length > 38){
//					CMN_StringCopyNumUntilNull( &List.S.Print[35], SYB_MercuryDialBuffer, 39);
//				}
//				else{
//					List.S.Print[35 + length] = ']';
//					
//					CMN_StringCopyNumUntilNull( &List.S.Print[35], SYB_MercuryDialBuffer, length);
//					CMN_StringCopyNumUntilNull( &List.S.Print[36 + length], &List.S.Work[1],
//						(38 - length) );
//				}
//			}
//			else{
//				CMN_StringCopy( &List.S.Print[35-1], List.S.Work );
//			}
 #else
  #if !defined(KEISATSU)	/* 警察ＦＡＸ属性追加 Added by SMuratec 夏 2005/07/21 */
	CMN_StringCopy( &List.S.Print[35-1], List.S.Work );
  #endif
 #endif		/*	End of defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE) */
#endif
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	*LineCnt -= 2;
#if !defined (KEISATSU) /* 05/04/12 石橋正和 */
	/* if ( SYB_OnetouchDial[OnetouchCnt].DialData.Onetouch.SubDialPosition != 0xFF ) { */
	if (SYB_OnetouchDial[OnetouchCnt].SubDialPosition != 0xFF ) { /* 変更(ANZU) 95/12/14 H.HIRAO */
		/*・	・（転送先）・xxxxxxxxx・	 ・	  │*/
		Print_Dial_List_Line( 3, List.S.Print, List.S.Attribute );
		/*（転送先）*/
#if (PRO_KEYPANEL == PANEL_ANZU_L)						/* POPLA_L対応 1997/03/07 M.Kuwahara */
		AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_AltNo, LST_NOT );
#else	/* PANEL_POPLA_B/L/H */
		AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_AltNo, LST_NOT );
#endif
		/*転送先*/
		/* CMN_BCD_ToASC_String( (UBYTE *)List.S.Work,
		  &SYB_SubDial[SYB_OnetouchDial[OnetouchCnt].DialData.Onetouch.SubDialPosition][0] ); */
		CMN_BCD_ToASC_String( List.S.Work,
		  &SYB_SubDial[SYB_OnetouchDial[OnetouchCnt].SubDialPosition][0] ); /* 変更(ANZU) 95/12/14 H.HIRAO */
#if (PRO_KEYPANEL == PANEL_ANZU_L)						/* POPLA_L対応 1997/03/07 M.Kuwahara */
		CMN_StringCopy( &List.S.Print[24-1], List.S.Work );
#else	/* PANEL_POPLA_B/L/H */
 #if 0	/* プレフィックス＋ダイヤル番号で40桁を超えても折り返して印字しないので、大島さん確認の上、リストでの展開は止めます by K.Watanabe 2004/11/12 */
// #if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/09 *//* by K.Watanabe 2004/10/12 */
//			if (List.S.Work[0] == '!'){
//				length = CMN_StringLength(SYB_MercuryDialBuffer);	/* マキュリー登録桁 */
//
//				List.S.Print[34] = '[';
//				if (length > 38){
//					CMN_StringCopyNumUntilNull( &List.S.Print[35], SYB_MercuryDialBuffer, 39);
//				}
//				else{
//					List.S.Print[35 + length] = ']';
//					
//					CMN_StringCopyNumUntilNull( &List.S.Print[35], SYB_MercuryDialBuffer, length);
//					CMN_StringCopyNumUntilNull( &List.S.Print[36 + length], &List.S.Work[1],
//						(38 - length) );
//				}
//			}
//			else{
//				CMN_StringCopy( &List.S.Print[35-1], List.S.Work );
//			}
 #else
		CMN_StringCopy( &List.S.Print[35-1], List.S.Work );
 #endif		/*	End of defined(STOCKHM2)	*/
#endif
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		*LineCnt -= 1;
	}
#endif /* !defined (KEISATSU) */
	return ( OK );
}
#endif	/* (PRO_DIAL_LIST_GROUP == DISABLE) */

/*************************************************************************
	module		:[ワンタッチダイヤル ネクスト サーチ］
	functiom	:[ワンタッチダイヤルの次をサーチする]
	common		:[
		SYB_OnetouchDial	:
	]
	condition	:[
		サーチ方法
		,	LST_SEARCH_NUMBER
		,	LST_SEARCH_ASCII
		ワンタッチダイヤルデータ番号
		,	データエンド->SYS_ONETOUCH_MAX
	]
	commment	:[]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/28]
	author		:[豊田浩子]
*************************************************************************/
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
UBYTE				OnetouchDataNextSearch(
						 UBYTE Kind,		/*サーチ方法*/
						 WORD* OnetouchCnt,	/*ワンタッチダイヤルデータ番号*/
						 UBYTE *SearchStr)	/*現在サーチ文字*/
#else
void				OnetouchDataNextSearch(
						 UBYTE Kind,		/*サーチ方法*/
						 WORD* OnetouchCnt,	/*ワンタッチダイヤルデータ番号*/
						 UBYTE *SearchStr,	/*現在サーチ文字*/
						 UBYTE *sub_dial_flag)	/* 転送先があれば1 */
#endif
{
	UBYTE 	onetouch;			/*ﾜﾝﾀｯﾁﾀﾞｲﾔﾙﾃﾞｰﾀ番号*/
	UBYTE 	i;					/*loop*/
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
	UBYTE	j;
	UBYTE	grp_cnt;
	UBYTE	length;
	UBYTE	next_line;
#endif

#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
	j = 1;
	next_line = 1;
	grp_cnt = 0;
#endif

	if ( Kind == LST_SEARCH_NUMBER ) {
		/*配列順のｻｰﾁ*/
		for ( i = (UBYTE)((*OnetouchCnt)+1); i < SYS_ONETOUCH_MAX; i++ ) {
			/* if ( SYB_OnetouchDial[i].Status == SYS_ONETOUCH_STORED
			  && SYB_OnetouchDial[i].DialData.Onetouch.Dial[0] != 0xff ) { */

#if (0)
** 			/* ＩＣＨＯＵからのフィードバック By O.Kimoto 1998/03/30 */
** 			/*
** 			** リモート診断が未登録ならＦ０を書く場合があるのでＦＦで見ているとおかしくなる
** 			** 1997/10/03 M.Shimizu
** 			*/
** 			if ( SYB_OnetouchDial[i].Dial[0] != LST_DIAL_NOT ) { /* 構造体変更(ANZU) By H.Hirao 1995/12/14 */
** 				break;
** 			}
#else
			if ( (SYB_OnetouchDial[i].Dial[0] & 0xF0) != 0xF0 ) {
				break;
			}
#endif

		}
		onetouch = i;
	}
	else {
		/*名称ｱｽｷｰ順のｻｰﾁ*/
		onetouch = (UBYTE)((*OnetouchCnt)+1);
		OnetouchStrEqSearch( &onetouch, SearchStr );
		if ( onetouch == SYS_ONETOUCH_MAX ) {
			OnetouchStrGtSearch( &onetouch, SearchStr );
		}
	}
	/*結果ｾｯﾄ*/
	*OnetouchCnt = (WORD)onetouch;

#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
	/* 次に印刷するワンタッチが無い時には、行数の計算は必要ないので省きます
	** 注）省かないと、場合によってはRAMがつぶれる可能性があります
	*/
	if (*OnetouchCnt != (WORD)SYS_ONETOUCH_MAX) {
		/* 行数を計算 */
		/* ﾀﾞｲﾔﾙ */
		length = GetBCD_StringLength(SYB_OnetouchDial[onetouch].Dial);
		if (length > 20) {
			next_line++;
		}
		
		
		
#if !defined (KEISATSU) /* 05/04/12 石橋正和 */
		/* ｻﾌﾞﾀﾞｲﾔﾙ */
		if ( SYB_OnetouchDial[onetouch].SubDialPosition != 0xFF ) {
			next_line++;
			length = GetBCD_StringLength(SYB_SubDial[SYB_OnetouchDial[onetouch].SubDialPosition]);
			if (length > 20) {
				next_line++;
			}
		}
#endif

		for ( i = 1; i <= SYS_GROUP_NUMBER_MAX; i++ ) {
			if ( (SYB_OnetouchDial[onetouch].Group & j) == j ) {
				grp_cnt++;
			}
			j <<= 1;
		}

		if (next_line < 2 && grp_cnt > 9) {
			next_line++;
		}
		if (next_line < 3 && grp_cnt > 18) {
			next_line++;
		}
		if (next_line < 4 && grp_cnt > 27) {
			next_line++;
		}
	}
	return(next_line);
#else

#if defined (KEISATSU) /* 警察FAX 05/04/12 石橋正和 */
	*sub_dial_flag = 0;
#else
	if (SYB_OnetouchDial[onetouch].SubDialPosition == 0xFF) { /* 構造体変更(ANZU) By H.Hirao 1995/12/14 */
		/** 転送先がない場合 */
		*sub_dial_flag = 0;
	}
	else { /** 転送先がある場合 */
		*sub_dial_flag = 1;
	}
#endif

#endif	/* (PRO_DIAL_LIST_GROUP == ENABLE) */
}

/*************************************************************************
	module		:[ワンタッチダイヤル同一名称サーチ]
	functiom	:[ワンタッチダイヤルの同一名称をサーチする]
	common		:[
		SYB_OnetouchDial	:
	]
	condition	:[
		ワンタッチダイヤルデータ番号
		,	データエンド->SYS_ONETOUCH_MAX
	]
	commment	:[]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/28]
	author		:[豊田浩子]
*************************************************************************/
void				OnetouchStrEqSearch(
						 UBYTE *OnetouchCnt,/*ワンタッチダイヤルデータ番号*/
						 UBYTE *SearchStr )	/*現在サーチ文字*/
{
	UBYTE	i;				/*loop*/

	for ( i = *OnetouchCnt; i < SYS_ONETOUCH_MAX; i++ ) {
		/* if ( SYB_OnetouchDial[i].Status == SYS_ONETOUCH_STORED &&
			SYB_OnetouchDial[i].DialData.Onetouch.Dial[0] != 0xff ) { */

#if (0)
** 		/* ＩＣＨＯＵからのフィードバック By O.Kimoto 1998/03/30 */
** 		/*
** 		** リモート診断が未登録ならＦ０を書く場合があるのでＦＦで見ているとおかしくなる
** 		** 1997/10/03 M.Shimizu
** 		*/
** 		if ( SYB_OnetouchDial[i].Dial[0] != LST_DIAL_NOT ) [ /* 変更(ANZU) 95/12/14 H.HIRAO */
#else
		if ( (SYB_OnetouchDial[i].Dial[0] & 0xF0) != 0xF0 ) {
#endif

			if ( CMN_StringCompare( SearchStr, SYB_OnetouchDial[i].
			  Name, LST_COMP_LEN ) == STRCMP_EQUAL ) { /* 変更(ANZU) 95/12/14 H.HIRAO */
				break;
			}
		}
	}
	*OnetouchCnt = i;
}
/*************************************************************************
	module		:[ワンタッチダイヤルGREATER名称サーチ］
	functiom	:[ワンタッチダイヤルGREATER名称をサーチする]
	common		:[
		SYB_OnetouchDial	:
	]
	condition	:[
		ワンタッチダイヤルデータ番号
		,	データエンド－＞SYS_ONETOUCH_MAX
	]
	commment	:[]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/28]
	author		:[豊田浩子]
*************************************************************************/
void				OnetouchStrGtSearch(
						 UBYTE *OnetouchCnt,	/*ワンタッチダイヤルデータ番号*/
						 UBYTE *SearchStr )		/*現在サーチ文字*/
{
	UBYTE	i;					/*loop*/
	UBYTE	j;					/*GT point*/
	UBYTE	set_f;				/*comp_pt set flag*/
											/*OFF - > 未ｾｯﾄ*/
											/*ON  - > 済ｾｯﾄ*/
	UBYTE	*comp_pt;		/*compear pointer*/

	*OnetouchCnt = 0;
	j = 0xff;
	set_f = OFF;

	for ( i = *OnetouchCnt; i < SYS_ONETOUCH_MAX; i++ ) {
		/* if ( SYB_OnetouchDial[i].Status == SYS_ONETOUCH_STORED &&
			SYB_OnetouchDial[i].DialData.Onetouch.Dial[0] != 0xff ) { */

#if(0)
** 		/* ＩＣＨＯＵからのフィードバック By O.Kimoto 1998/03/30 */
** 		/*
** 		** リモート診断が未登録ならＦ０を書く場合があるのでＦＦで見ているとおかしくなる
** 		** 1997/10/03 M.Shimizu
** 		*/
** 		if ( SYB_OnetouchDial[i].Dial[0] != LST_DIAL_NOT ) [ /* 変更(ANZU) 95/12/14 H.HIRAO */
#else
		if ( (SYB_OnetouchDial[i].Dial[0] & 0xF0) != 0xF0 ) {
#endif

			if ( CMN_StringCompare( SearchStr, SYB_OnetouchDial[i].
			  Name, LST_COMP_LEN ) == STRCMP_LOWER ) { /* 変更(ANZU) 95/12/14 H.HIRAO */
				if ( set_f == OFF ) {
					comp_pt = SYB_OnetouchDial[i].Name; /* 変更(ANZU) 95/12/14 H.HIRAO */
					j = i;
					set_f = ON;
				}
				else {
					if ( CMN_StringCompare( comp_pt,
					  SYB_OnetouchDial[i].Name,
					  LST_COMP_LEN ) == STRCMP_UPPER ) {
						comp_pt = SYB_OnetouchDial[i].Name; /* 変更(ANZU) 95/12/14 H.HIRAO */
						j = i;
					}
				}
			}
		}
	}
	if ( j == 0xff ) {
		*OnetouchCnt = SYS_ONETOUCH_MAX;
	}
	else {
		*OnetouchCnt = j;
		CMN_StringCopyNum( SearchStr, comp_pt , LST_COMP_LEN );
		SearchStr[LST_COMP_LEN] = NULL;
	}
}
