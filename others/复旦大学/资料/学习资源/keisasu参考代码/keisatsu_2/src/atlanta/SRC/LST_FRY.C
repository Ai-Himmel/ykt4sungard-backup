/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_FRY.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 工場メニュー
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include 	"\src\atlanta\define\std.h"

#include	"\src\atlanta\define\lst_def.h"

#include 	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include	"\src\atlanta\ext_v\lst_data.h"
#include 	"\src\atlanta\ext_v\lst_wrd.h"
#include 	"\src\atlanta\ext_v\sys_data.h"	/* 95/03/27 By j.masuda */

#if (PRO_CLASS1 == ENABLE)	/* '96.02/13 By T.Isobe */
#include 	"\src\atlanta\define\cl1_def.h"
#include 	"\src\atlanta\ext_v\cl1_data.h"
#endif
#if (PRO_FIP == ENABLE)		/* '96.02/14 By K.Watanabe */
#include 	"\src\atlanta\define\fip_def.h"	/* 95/03/27 By j.masuda */
#endif

#if (PRO_PANEL == ANK)	/* Add by O.Kimoto 1998/11/12 */
/* 下記リストはＡＮＫ（20文字×2行）だけが必要です。
** by O.Kimoto 1998/11/20
*/
/*************************************************************************
	module		:[工場メニュー印刷]
	function	:[工場メニューを印刷する]
	common		:[
		List	:
		PWRD_FunctionList
		PWRD_LedTest
		PWRD_LcdTest
		PWRD_Pane1keytest
		PWRD_SramCheck
		PWRD_DramCheck
		PWRD_RTCTest
		PWRD_DramCheck
		PWRD_RTCTest
		PWRD_Rs232cTest
	]
	condition	:[]
	commment	:[
		修正履歴
		95/03/27	By j.masuda
			ＲＳ２３２ｃを追加。
		'96.02/09	:クラス１対応により処理を追加

		1996/04/01	By H.Hirao
			"Feeder Test", "LifeMonitor Clr"を削除
	]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
WORD 			Print_Fact_Menu(
						 void )				/*なし*/
{
	UBYTE			i; 					/*loop*/
	CONST UBYTE 	*p_prn;				/*印刷文字列*/
	register WORD	ret;				/*実行結果*/
	UBYTE			loop_c;				/*ループ*/

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/*２行印字（改行）*/
	if ( (ret = CharacterPrint( LST_LINE_FEED +2 )) != OK ) {
		return ( ret );
	}

	/*明細印刷（ﾒﾓﾘ節約の為この様にしている）*/
	loop_c = 'G'; /** For ANZU By H.Hirao 1996/04/02 */
	/* loop_c = 'I'; */	/*FIPなし*/
#if (PRO_FIP == ENABLE)			/*95/03/27 By j.masuda*/
	if ( SYS_RS232C_Exist == 1 && SYS_FIP_Status == FIP_IDLE ) {
		loop_c = 'H'; /** For ANZU By H.Hirao 1996/04/02 */
		/* loop_c = 'J'; */	/* FIPあり */
	}
#endif
#if (PRO_CLASS1 == ENABLE)		/* '96.02/09 By K.Watanabe */
	if ( SYS_RS232C_Exist == 1 && SYS_CL1_Status == CL1_IDLE ) {
		loop_c = 'H'; /** For ANZU By H.Hirao 1996/04/02 */
		/* loop_c = 'J'; */	/* CLASS1あり */
	}
#endif

	for ( i = 'A'; i <= loop_c; i++ ) {
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/11/11 */
		CMN_UnsignedIntToASC(&List.S.Print[6-1], (UWORD)(i - 'A' + 1), 2, '0');
		List.S.Print[8-1] = '.';
#else
		List.S.Print[6-1] = i;
		List.S.Print[7-1] = '.';
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		switch ( i ) {
			case 'A':
				p_prn = PWRD_FunctionList;
				break;
			case 'B':
				p_prn = PWRD_LedTest;
				break;
			case 'C':
				p_prn = PWRD_LcdTest;
				break;
			case 'D':
				p_prn = PWRD_Pane1keytest;
				break;
			case 'E':
				p_prn = PWRD_SramCheck; /** For ANZU By H.Hirao 1996/04/01 */
				/* p_prn = PWRD_FeedoutDoc;
				List.S.Print[20] = ' '; */	/*KIRIとﾜｰﾃﾞｨﾝｸﾞを共通にしている為*/
				break;
			case 'F':
				p_prn = PWRD_DramCheck; /** For ANZU By H.Hirao 1996/04/01 */
				/* p_prn = PWRD_LifemonitorClr; */
				break;
			case 'G':
				p_prn = PWRD_RTCTest; /** For ANZU By H.Hirao 1996/04/01 */
				/* p_prn = PWRD_SramCheck; */
				break;
			/* case 'H':
				p_prn = PWRD_DramCheck;
				break;
			case 'I':
				p_prn = PWRD_RTCTest;
				break;
			case 'J': */						/* 95/03/27 By j.masuda */
			case 'H':
				p_prn = PWRD_Rs232cTest;
				break;
		}
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/11/11 */
		CMN_StringCopy( &List.S.Print[10-1], p_prn );
#else
		CMN_StringCopy( &List.S.Print[9-1], p_prn );
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		if ( i < loop_c ) {
			/*１行印字（改行）*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
		}
	}
	/*１行印字（改行）*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	return ( OK );
}
#endif

