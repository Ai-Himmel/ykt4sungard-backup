/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_DATE.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 日時操作
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"
#include	"\src\atlanta\define\wording.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_tbl.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"

#include	"\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include	"\src\memsw\define\mem_sw_b.h" /*1996/04/17 Eguchi */

#if ( PRO_PANEL == ANK )
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#endif
#if ( PRO_PANEL == KANJI )
#include	"\src\atlanta\opr\kanji\define\opr_def.h"
#endif
#if (PRO_MULTI_LINE == ENABLE)	/* 1997/06/24 Y.Matsukuma */
#include	"\src\atlanta\define\mlt_pro.h"
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && (PRO_OKI == ENABLE)	/* by K.Watanabe 1998/10/02 */
#include	"\src\atlanta\define\mntsw_a.h"
#endif

/*************************************************************************
	module		:[TIME_DATA_t型日時、ｱｽｷｰ文字列変換]
	function	:[TIME_DATA_t型の日時をｱｽｷｰ文字列に変換する。]
	common		:[]
	condition	:[
		ｶﾚﾝﾀﾞﾀｲﾌﾟ切替ﾁｪｯｸ
		,	ON ->ｶﾚﾝﾀﾞﾀｲﾌﾟ切替ﾁｪｯｸを行う
		,	OFF->ｶﾚﾝﾀﾞﾀｲﾌﾟ切替ﾁｪｯｸを行わない
	]
	comment		:[
		unsigned long型の日時を、”'YY年MM月DD日 (W) HH:MM”
		（”'99年Z9月Z9日 (X) Z9:99”）”）のｱｽｷｰ文字列に変換する。
		（”XXX Z9 '99”）USAの時
		94/12/09 By j.masuda
			CHNを追加。
	]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
void				TimeDataAscii(
						 UBYTE DateTypeChange,		/*ｶﾚﾝﾀﾞﾀｲﾌﾟ切替ﾁｪｯｸ*/
						 CONST UDWORD Current,		/*変換元日時値*/
						 register UBYTE* AscString,/*変換先ｱｽｷｰ文字列*/
						 UBYTE line_number)			/* 回線番号 */
{
	UBYTE	wrk_str[3];		/*変換work*/
	UBYTE	i;				/*work*/
	UBYTE	wd_number;		/*SYB_WordingNumber*/
	UBYTE	warning;

	/*  By O.Kimoto 1997/07/10 */
	if (line_number == 0) {
		warning = 1;	/* 内蔵回線用 */
	}
	else {
#if (PRO_MULTI_LINE == ENABLE)
		warning = 0;	/* 外付け回線用 */
#else
		warning = 1;	/* 内蔵回線用 */
#endif
	}

	CMN_LongTimeToBCD( (TIME_DATA_t *)&ListTime.Year, Current );

	CMN_MemorySetNULL( AscString, 20, ' ' );

	wd_number = DateTypeGet();
	/*ｶﾚﾝﾀﾞｰﾀｲﾌﾟﾁｪﾝｼﾞが有効となっている時*/
	if (warning == 1) {
		if ((DateTypeChange == ON) && (FCM_PtnrChkCalendarTypeChange() != 0)) {	/* 属性を見る様に変更 '96.03.29 By T.Y */
			switch ( wd_number ) {
			case	JPN_CLOCK_TYPE:
				wd_number = USA_CLOCK_TYPE;
				break;
			case	USA_CLOCK_TYPE:
				wd_number = EUR_CLOCK_TYPE;
				break;
			case	EUR_CLOCK_TYPE:
				wd_number = USA_CLOCK_TYPE;
				break;
			}
		}
	}
	else {
		if ((DateTypeChange == ON) && ( OPT_CHK_CalendarTypeChange(line_number))) {
			switch ( wd_number ) {
			case	JPN_CLOCK_TYPE:
				wd_number = USA_CLOCK_TYPE;
				break;
			case	USA_CLOCK_TYPE:
				wd_number = EUR_CLOCK_TYPE;
				break;
			case	EUR_CLOCK_TYPE:
				wd_number = USA_CLOCK_TYPE;
				break;
			}
		}
	}

#if defined(CHN)	/*94/12/09 By j.masuda*/
	AscString[0] = ' ';
	AscString[1] = ' ';
	AscString[6] = 0x11;
	AscString[9] = 0x12;
	AscString[12] = 0x13;
	if( ListTime.Year >= 92 ){
		AscString[2] = '1';
		AscString[3] = '9';
	}
	else{
		AscString[2] = '2';
		AscString[3] = '0';
	}
	CMN_BCD_To2ASC_String( wrk_str, ListTime.Year, '0' );	/*年*/
	CMN_StringCopyNum( &AscString[4], wrk_str, 2 );
	CMN_BCD_To2ASC_String( wrk_str, ListTime.Month, ' ' );	/*月*/
	CMN_StringCopyNum( &AscString[7], wrk_str, 2 );
	CMN_BCD_To2ASC_String( wrk_str, ListTime.Date, ' ' );	/*日*/
	CMN_StringCopyNum( &AscString[10], wrk_str, 2 ); /*1996/03/12 Eguchi */

#else
	switch ( wd_number ) {
	case	JPN_CLOCK_TYPE:										/*JPN*/
		/* 2060年以降、リストの日付が1900年代に戻る。下記対策が水平展開できていなかった。2003/03/31 T.Takagi */
		/* 時計の設定を2060年以後にすると、待機画面での時間表示が1960年を表示する不具合：AntWarpからのバグフィード・バック M.Iida 200/07/12 */
		if (ListTime.Year >= 0x92 ){
			AscString[0] = '1';
			AscString[1] = '9';
		}
		else {
			AscString[0] = '2';
			AscString[1] = '0';
		}
		AscString[11] = '(';
		AscString[13] = ')';
		AscString[4] = LST_A_NEN;
		AscString[7] = LST_A_GETU;
		AscString[10] = LST_A_NICHI;
		CMN_BCD_To2ASC_String( wrk_str, ListTime.Year, '0' );	/*年*/
		CMN_StringCopyNum( &AscString[2], wrk_str, 2 );
		CMN_BCD_To2ASC_String( wrk_str, ListTime.Month, ' ' );	/*月*/
		CMN_StringCopyNum( &AscString[5], wrk_str, 2);
		CMN_BCD_To2ASC_String( wrk_str, ListTime.Date, ' ' );	/*日*/
		CMN_StringCopyNum( &AscString[8], wrk_str, 2);
		CMN_BCD_To2ASC_String( wrk_str, ListTime.Week, '0' );	/*曜日*/
		AscString[12] = (UBYTE)(LST_A_NICHI + wrk_str[1] - '0' -1);
		break;

	case	USA_CLOCK_TYPE:										/*USA*/
		/* 2060年以降、リストの日付が1900年代に戻る。下記対策が水平展開できていなかった。2003/03/31 T.Takagi */
		/* 時計の設定を2060年以後にすると、待機画面での時間表示が1960年を表示する不具合：AntWarpからのバグフィード・バック M.Iida 200/07/12 */
		if (ListTime.Year >= 0x92 ){
			AscString[9] = '1';
			AscString[10] = '9';
		}
		else {
			AscString[9] = '2';
			AscString[10] = '0';
		}
		CMN_BCD_To2ASC_String( wrk_str, ListTime.Year, '0' );	/*年*/
		CMN_StringCopyNum( &AscString[11], wrk_str, 2 );
		i = (UBYTE)( ((ListTime.Month>>4)*10) + (ListTime.Month & 0x0f) );
		if ( 1 <= i && i <= 12 ) {
			CMN_StringCopyNum( &AscString[2], &PWRD_Year_Eng[i-1][0], 3 );	/*月*/
		}
		CMN_BCD_To2ASC_String( wrk_str, ListTime.Date, ' ' );	/*日*/
		CMN_StringCopyNum( &AscString[6], wrk_str, 2 );/*1996/03/12 Eguchi */
		break;

	case	EUR_CLOCK_TYPE:										/*EURO*/
		/* 2060年以降、リストの日付が1900年代に戻る。下記対策が水平展開できていなかった。2003/03/31 T.Takagi */
		/* 時計の設定を2060年以後にすると、待機画面での時間表示が1960年を表示する不具合：AntWarpからのバグフィード・バック M.Iida 200/07/12 */
		if (ListTime.Year >= 0x92 ){
			AscString[9] = '1';
			AscString[10] = '9';
		}
		else {
			AscString[9] = '2';
			AscString[10] = '0';
		}
		CMN_BCD_To2ASC_String( wrk_str, ListTime.Year, '0' );	/*年*/
		CMN_StringCopyNum( &AscString[11], wrk_str, 2);
		i = (UBYTE)( ((ListTime.Month>>4)*10) + (ListTime.Month & 0x0f) );
		if ( 1 <= i && i <= 12 ) {
			CMN_StringCopyNum( &AscString[5], &PWRD_Year_Eng[i-1][0], 3 );	/*月*/
		}
		CMN_BCD_To2ASC_String( wrk_str, ListTime.Date, ' ' );	/*日*/
		CMN_StringCopyNum( &AscString[2], wrk_str, 2 );
		break;
	}
#endif

	AscString[17] = ':';
	CMN_BCD_To2ASC_String( wrk_str, ListTime.Hour, ' ' );			/*時*/
	CMN_StringCopyNum( &AscString[15], wrk_str, 2); /*1996/03/12 Eguchi*/
	CMN_BCD_To2ASC_String( wrk_str, ListTime.Minute, '0' );			/*分*/
	CMN_StringCopyNum( &AscString[18], wrk_str, 2 ); /*1996/03/12 Eguchi */
}

/*************************************************************************
	module		:[秒値、分’秒”形式文字列変換]
	function	:[秒値を、分’秒”形式の文字列に変換する。]
	common		:[]
	condition	:[
		変換方法
			'0' = 前ｾﾞﾛ埋め
			' ' = 前ｽﾍﾟｰｽ埋め
			0	= 前ｽﾍﾟｰｽ削除
	]
	comment		:[
		変換元秒値を、”MM'SS"”の形の文字列に変換し、変換先分秒文字列に
		セットする。
		変換方法により、変換結果が以下のように変化する。（分の所のみで、
		秒は常に”99"”となる。
		'0' -> ｱｽｷｰ文字列に変換した数値の前の余白を’０’で埋める。
		' '-> ｱｽｷｰ文字列に変換した数値の前の余白を’　’で埋める。
		0, -> ｱｽｷｰ文字列に変換した数値の前の余白を削除する。

		near call を far call に変更	Line 162
	]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
void				SecondToMinuteSecondAsc(
						 register UWORD Second,		/*変換元秒値*/
						 register UBYTE *AscString,/*変換先分秒文字列*/
						 UBYTE Mode )				/*変換方法*/
{
	UWORD	second_w;			/*秒w*/
	UWORD	minute_w;			/*分w*/
	UWORD	i;

	AscString[0] = NULL;
	second_w = Second % 60;
	minute_w = Second / 60;
	CMN_UnsignedIntToASC_NULL( AscString, minute_w, 2, Mode );
	i = CMN_StringLength(AscString);
	AscString[i] = '\x27';
	AscString[i+1] = NULL;
	CMN_UnsignedIntToASC_NULL( &AscString[CMN_StringLength(AscString)], second_w, 2, '0' );
	i = CMN_StringLength(AscString);
	AscString[i] = '\x22';
	AscString[i+1] = NULL;
}

/*************************************************************************
	module		:[秒値 -> 時 : 分 : 秒  形式文字列変換]
	function	:[秒値を、時 : 分 : 秒  形式の文字列に変換する。]
	common		:[]
	condition	:[
		変換方法
			'0' = 前ｾﾞﾛ埋め
			' ' = 前ｽﾍﾟｰｽ埋め
			0	= 前ｽﾍﾟｰｽ削除
	]
	comment		:[
		変換元秒値を、”HH : MM : SS ”の形の文字列に変換し、変換先分秒文字列に
		セットする。
		変換方法により、変換結果が以下のように変化する。（時の所のみで、
		分 秒は常に”99 ”となる。
		'0' -> ｱｽｷｰ文字列に変換した数値の前の余白を’０’で埋める。
		' '-> ｱｽｷｰ文字列に変換した数値の前の余白を’　’で埋める。
		0, -> ｱｽｷｰ文字列に変換した数値の前の余白を削除する。
		簡易料金管理の通信時間表記部分に使用してます。
		
		near call を far call に変更	Line 162
		SecondToMinuteSecondAsc()から引用
	]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/12/09]
	author		:[本多智幸]
*************************************************************************/
void				SecondToHourMinuteSecondAsc(
						 register UDWORD Second,		/*変換元秒値*/
						 register UBYTE *AscString,/*変換先時分秒文字列*/
						 UBYTE Mode )				/*変換方法*/
{
	UWORD	i;
	UWORD	second_w;			/* 秒w */
	UWORD	minute_w;			/* 分w */
    UDWORD	hour_w;				/* 時w */

	AscString[0] = NULL;
	second_w = (UWORD)(Second % 60);
	minute_w = (UWORD)((Second % 3600)/ 60);
	hour_w   = (UDWORD)(( Second / 60 ) / 60);

	CMN_UnsignedLongToASC_NULL( AscString, hour_w, 3, Mode );
	i = CMN_StringLength(AscString);
	AscString[i] = '\x3A';	/* : */
	AscString[i+1] = NULL;

	CMN_UnsignedIntToASC_NULL( &AscString[CMN_StringLength(AscString)], minute_w, 2, '0' );
	i = CMN_StringLength(AscString);
	AscString[i] = '\x3A';	/* : */
	AscString[i+1] = NULL;

	CMN_UnsignedIntToASC_NULL( &AscString[CMN_StringLength(AscString)], second_w, 2, '0' );
	i = CMN_StringLength(AscString);
	AscString[i+1] = NULL;
}

/*************************************************************************
	module		:[分値、日時分形式文字列変換。]
	function	:[分値を、日時分式の文字列に変換する。]
	common		:[]
	condition	:[
		変換形式
		,	LST_DATE_HOUR_MINUTE = 日時分形式
		,	LST_HOUR_MINUTE		= 時分形式
	]
	comment		:[
		変換元分値を、変換形式に従い変換し、変換先日時分文字列にｾｯﾄする。
		変換形式により、変換結果が以下のように変化する。
		,	LST_DATE_HOUR_MINUTE -> ”Z9,Z9:99”
		,	LST_HOUR_MINUTE		-> ”Z9:99”
	]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
void				MinuteToDayHourMinuteAsc(
						 register UWORD Minute,		/*変換元分値*/
						 /* register UBYTE * AscString, */ /*変換先日時分文字列*/
						 UBYTE *AscString, /* near->far 96/02/14 H.Hirao */
						 UBYTE Mode )				/*変換形式*/
{
	if ( Mode == LST_DATE_HOUR_MINUTE ) {
		CMN_UnsignedIntToASC_NULL(AscString, (UWORD)(Minute / (24*60)), 2, ' ');
		*(AscString+2) = ',';
		Minute = Minute % (24*60);
		CMN_UnsignedIntToASC_NULL((AscString+3), (UWORD)(Minute / (60)), 2, ' ');
		*(AscString+5) = ':';
		CMN_UnsignedIntToASC_NULL((AscString+6), (UWORD)(Minute % (60)), 2, '0');
	}
	else {
		CMN_UnsignedIntToASC_NULL((AscString+0), (UWORD)(Minute / (60)), 2, ' ');
		*(AscString+2) = ':';
		CMN_UnsignedIntToASC_NULL((AscString+3), (UWORD)(Minute % (60)), 2, ' ');
	}
}

/*************************************************************************
	module		:[積算分、日時文字列変換。]
	function	:[
		１９９２年１月１日を基準とした分の積算値を、日時の文字列に変換する。
	]
	common		:[]
	condition	:[
		変換種類	LST_YYMMDD		年月日週
		,			LST_DDHHMM		日時分
		,			LST_MMDDHHMM	月日時分
		,			LST_DDMMHHMM	日月時分
	]
	comment		:[
		変換元積算分を、変換種類に従って文字列に変換する。
		変換種類＝LST_YYMMDDなら	['YY年MM月DD日 (W)]（99年Z9月Z9日 (X)）に変換。USAなら[MMM DD 'YY]
		変換種類＝LST_DDHHMMなら	[DD,HH:MM]（Z9,Z9:Z9）に変換
		変換種類＝LST_MMDDHHMMなら	[MM/DD HH:MM]（Z9/Z9 Z9:Z9）に変換
		変換種類＝LST_DDMMHHMMなら	[DD/MM HH:MM]（Z9/Z9 Z9:Z9）に変換
	]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
void				CriterionMinuteToDayTimeAsc(
						 UDWORD Second,				/*変換元積算分*/
						 UBYTE Kind,				/*変換種類*/
						 register UBYTE *AscString )/*変換先文字列*/
{
	DWORD	day_w;			/*通算日*/
	UDWORD	day_add;		/*月による日数加算値*/
	UDWORD	day_bk;			/*月による日数加算値*/
	UBYTE	wrk_str[3];		/*変換work*/
	UBYTE	i;				/*loop*/
	UBYTE	year;			/*年*/
	UBYTE	month;			/*月*/
	UBYTE	day;			/*日*/
	UBYTE	week;			/*曜*/
	UBYTE	hour;			/*時*/
	UBYTE	minute;			/*分*/
	UBYTE	wd_number;		/*SYB_WordingNumber*/
	UDWORD	test;			/*test*/

	test = Second;
	hour = (UBYTE)( (Second % (24*60)) / 60 );
	minute = (UBYTE)( Second % 60 );
	day_w = Second / (24*60);

	switch ( day_w % 7 ) {
	case 0:
		week = 4;  /*水曜日*/
		break;
	case 1:
		week = 5;  /*木曜日*/
		break;
	case 2:
		week = 6;  /*金曜日*/
		break;
	case 3:
		week = 7;  /*土曜日*/
		break;
	case 4:
		week = 1;  /*日曜日*/
		break;
	case 5:
		week = 2;  /*月曜日*/
		break;
	case 6:
		week = 3;  /*火曜日*/
		break;
	}

	year = 92;
	for ( i = 0; i < 255; i++ ) {
		if ( i % 4 == 0 ) {
			if ( day_w - 366 < 0 ) break;
			day_w -= 366;
		}
		else {
			if ( day_w - 365 < 0 ) break;
			day_w -= 365;
		}
		year ++;
	}
	if ( year >= 100 ) year -= 100;

	day_add = 0;
	day_bk = 0;
	for ( i = 1; i <= 12; i++ ) {
		switch ( i ) {
		case 1:
			day_add += 31;
			break;
		case 2:
			if ( year % 4 == 0 ) {
				day_add += 29;
			}
			else {
				day_add += 28;
			}
			break;
		case 3:
			day_add += 31;
			break;
		case 4:
			day_add += 30;
			break;
		case 5:
			day_add += 31;
			break;
		case 6:
			day_add += 30;
			break;
		case 7:
			day_add += 31;
			break;
		case 8:
			day_add += 31;
			break;
		case 9:
			day_add += 30;
			break;
		case 10:
			day_add += 31;
			break;
		case 11:
			day_add += 30;
			break;
		case 12:
			day_add += 31;
			break;
		}
		if ( day_w < (DWORD)day_add ) {
			month = i;
			day = (UBYTE)( day_w - day_bk +1 );
			break;
		}
		day_bk = day_add;
	}

	switch ( Kind ) {
	case LST_YYMMDD:
		wd_number = DateTypeGet();
		CMN_MemorySetNULL( AscString, 14, ' ' );

		switch ( wd_number ) {
		case JPN_CLOCK_TYPE:	/*JPN*/
			if ( year >= 92 ) {
				AscString[0] = '1';
				AscString[1] = '9';
			}
			else {
				AscString[0] = '2';
				AscString[1] = '0';
			}
			AscString[11] = '(';
			AscString[13] = ')';
			AscString[4] = LST_A_NEN;
			AscString[7] = LST_A_GETU;
			AscString[10] = LST_A_NICHI;
			CMN_UnsignedIntToASC( &AscString[2], (UWORD)year,2, '0' );		/*年*/
			CMN_UnsignedIntToASC( &AscString[5], (UWORD)month,2, ' ' );		/*月*/
			CMN_UnsignedIntToASC( &AscString[8], (UWORD)day,2, ' ' );		/*日*/
			CMN_BCD_To2ASC_String( wrk_str, week, '0' );					/*曜日*/
			AscString[12] = (UBYTE)( LST_A_NICHI + wrk_str[1] - '0' -1 );
			break;

		case USA_CLOCK_TYPE:	/*USA*/
			if ( year >= 92 ) {
				AscString[9] = '1';
				AscString[10] = '9';
			}
			else {
				AscString[9] = '2';
				AscString[10] = '0';
			}
			CMN_UnsignedIntToASC( &AscString[11], (UWORD)year,2, '0' );		/*年*/
			if ( month <= i && i <= month ) {
				CMN_StringCopyNum( &AscString[2],
			  	&PWRD_Year_Eng[month-1][0], 3 ); /*1996/03/12 Eguchi */		/*月*/
			}
			CMN_UnsignedIntToASC( &AscString[6],(UWORD)day, 2, ' ' );		/*日*/
			break;

		case EUR_CLOCK_TYPE:	/*EURO*/
			if ( year >= 92 ) {
				AscString[9] = '1';
				AscString[10] = '9';
			}
			else {
				AscString[9] = '2';
				AscString[10] = '0';
			}
			CMN_UnsignedIntToASC( &AscString[11], (UWORD)year,2, '0' );		/* 年 */
			if ( month <= i && i <= month ) {
				CMN_StringCopyNum( &AscString[5],
			  	&PWRD_Year_Eng[month-1][0], 3 ); /*1996/03/12 Eguchi */		/* 月 */
			}
			CMN_UnsignedIntToASC( &AscString[2], (UWORD)day,2, ' ' );		/* 日 */
			break;
		}
		break;
	case LST_DDHHMM:
		CMN_MemorySetNULL( AscString, 8, ' ' );
		AscString[2] = ',';
		AscString[5] = ':';
		CMN_UnsignedIntToASC( &AscString[0], (UWORD)day, 2, ' ' );		/* 日 */
		CMN_UnsignedIntToASC( &AscString[3], (UWORD)hour, 2, ' ' );		/* 時 */
		CMN_UnsignedIntToASC( &AscString[6], (UWORD)minute, 2, '0');	/* 分 */
		break;
	case LST_MMDDHHMM:
		CMN_MemorySetNULL( AscString, 11, ' ' );
		AscString[2] = '/';
		AscString[8] = ':';
		CMN_UnsignedIntToASC( &AscString[0], (UWORD)month, 2, ' ' );	/* 月 */
		CMN_UnsignedIntToASC( &AscString[3], (UWORD)day, 2, ' ' );		/* 日 */
		CMN_UnsignedIntToASC( &AscString[6], (UWORD)hour, 2, ' ' );		/* 時 */
		CMN_UnsignedIntToASC( &AscString[9], (UWORD)minute, 2, '0');	/* 分 */
		break;
#if defined(STOCKHM2) /* Add by SMuratec C.P 2004/06/10 */
	case LST_MMDDHHMM1:
		CMN_MemorySetNULL( AscString, 12, ' ' );
		wd_number = DateTypeGet();
		/* 固定で出力されていた日付を国別に分割します。*/
		switch(wd_number) {
		case JPN_CLOCK_TYPE:								/*JPN*/
			AscString[2] = OPR_CG_FONT_1;	/* 月 OPR_FONT_MONTH */
			AscString[5] = OPR_CG_FONT_0;	/* 日 OPR_FONT_DAY */
			AscString[9] = ':';
			CMN_UnsignedIntToASC( &AscString[0], (UWORD)month, 2, ' ' );	/* 月 */
			CMN_UnsignedIntToASC( &AscString[3], (UWORD)day, 2, ' ' );		/* 日 */
			CMN_UnsignedIntToASC( &AscString[7], (UWORD)hour, 2, ' ' );		/* 時 */
			CMN_UnsignedIntToASC( &AscString[10], (UWORD)minute, 2, '0');	/* 分 */
			break;
		case USA_CLOCK_TYPE:								/*USA*/
			AscString[2] = '/';
			AscString[8] = ':';
			CMN_UnsignedIntToASC( &AscString[0], (UWORD)month, 2, ' ' );	/* 月 */
			CMN_UnsignedIntToASC( &AscString[3], (UWORD)day, 2, ' ' );		/* 日 */
			CMN_UnsignedIntToASC( &AscString[6], (UWORD)hour, 2, ' ' );		/* 時 */
			CMN_UnsignedIntToASC( &AscString[9], (UWORD)minute, 2, '0');	/* 分 */
			break;
		case EUR_CLOCK_TYPE:								/*EURO*/
			AscString[2] = '/';
			AscString[8] = ':';
			CMN_UnsignedIntToASC( &AscString[0], (UWORD)day, 2, ' ' );		/* 日 */
			CMN_UnsignedIntToASC( &AscString[3], (UWORD)month, 2, ' ' );	/* 月 */
			CMN_UnsignedIntToASC( &AscString[6], (UWORD)hour, 2, ' ' );		/* 時 */
			CMN_UnsignedIntToASC( &AscString[9], (UWORD)minute, 2, '0');	/* 分 */
			break;
		}
		break;
	case LST_MMDDHHMM2:
		CMN_MemorySetNULL( AscString, 12, ' ' );
		wd_number = DateTypeGet();
		/* 固定で出力されていた日付を国別に分割します。 */
		switch (wd_number) {
		case JPN_CLOCK_TYPE:								/*JPN*/
			AscString[2] = LST_A_GETU;
			AscString[5] = LST_A_NICHI;
			AscString[9] = ':';
			CMN_UnsignedIntToASC( &AscString[0], (UWORD)month, 2, ' ' );	/* 月 */
			CMN_UnsignedIntToASC( &AscString[3], (UWORD)day, 2, ' ' );		/* 日 */
			CMN_UnsignedIntToASC( &AscString[7], (UWORD)hour, 2, ' ' );		/* 時 */
			CMN_UnsignedIntToASC( &AscString[10], (UWORD)minute, 2, '0');	/* 分 */
			break;
		case USA_CLOCK_TYPE:								/*USA*/
			AscString[2] = '/';
			AscString[8] = ':';
			CMN_UnsignedIntToASC( &AscString[0], (UWORD)month, 2, ' ' );	/* 月 */
			CMN_UnsignedIntToASC( &AscString[3], (UWORD)day, 2, ' ' );		/* 日 */
			CMN_UnsignedIntToASC( &AscString[6], (UWORD)hour, 2, ' ' );		/* 時 */
			CMN_UnsignedIntToASC( &AscString[9], (UWORD)minute, 2, '0');	/* 分 */
			break;
		case EUR_CLOCK_TYPE:								/*EURO*/
			AscString[2] = '/';
			AscString[8] = ':';
			CMN_UnsignedIntToASC( &AscString[0], (UWORD)day, 2, ' ' );		/* 日 */
			CMN_UnsignedIntToASC( &AscString[3], (UWORD)month, 2, ' ' );	/* 月 */
			CMN_UnsignedIntToASC( &AscString[6], (UWORD)hour, 2, ' ' );		/* 時 */
			CMN_UnsignedIntToASC( &AscString[9], (UWORD)minute, 2, '0');	/* 分 */
			break;
		}
		break;
#endif
#if (PRO_OKI == ENABLE)	/* 沖ヨーロッパ仕様では、月／日を日／月に変更します by K.Watanabe 1998/10/13 */
	case LST_DDMMHHMM:
		CMN_MemorySetNULL(AscString, 11, ' ');
		AscString[2] = '/';
		AscString[8] = ':';
		CMN_UnsignedIntToASC( &AscString[0], (UWORD)day, 2, ' ' );		/* 日 */
		CMN_UnsignedIntToASC( &AscString[3], (UWORD)month, 2, ' ' );	/* 月 */
		CMN_UnsignedIntToASC( &AscString[6], (UWORD)hour, 2, ' ' );		/* 時 */
		CMN_UnsignedIntToASC( &AscString[9], (UWORD)minute, 2, '0');	/* 分 */
		break;
#endif

	/* 西暦４桁対応 bythonda1999/11/16	*/
	/* ICHOUから移植してきました		*/
	case LST_YYYYMMDDHHMM1:
	case LST_YYYYMMDDHHMM2:
		CMN_MemorySetNULL( AscString, 16, ' ' );
		if( Kind == LST_YYYYMMDDHHMM1 ) {	/*  */
			AscString[10] = ',';
		}
		AscString[13] = ':';
		wd_number = DateTypeGet();
		switch ( wd_number ) {
			case	JPN_CLOCK_TYPE:								/*JPN*/
				AscString[4]  = '/';
				AscString[7]  = '/';
				if ( year >= 92 )
					CMN_UnsignedIntToASC( &AscString[0], 19, 2, '0' );
				else
					CMN_UnsignedIntToASC( &AscString[0], 20, 2, '0' );
				CMN_UnsignedIntToASC( &AscString[2],  (UWORD)year,   2, '0' );
																	/*年*/
				CMN_UnsignedIntToASC( &AscString[5],  (UWORD)month,  2, ' ' );
																	/*月*/
				CMN_UnsignedIntToASC( &AscString[8],  (UWORD)day,    2, ' ' );
																	/*日*/
				break;
			case USA_CLOCK_TYPE:
				AscString[2]  = '/';
				AscString[5]  = '/';
				CMN_UnsignedIntToASC( &AscString[0],  (UWORD)month,  2, ' ' );
																	/*月*/
				CMN_UnsignedIntToASC( &AscString[3],  (UWORD)day,    2, ' ' );
																	/*日*/
				if ( year >= 92 )
					CMN_UnsignedIntToASC( &AscString[6], 19, 2, '0' );
				else
					CMN_UnsignedIntToASC( &AscString[6], 20, 2, '0' );
				CMN_UnsignedIntToASC( &AscString[8],  (UWORD)year,   2, '0' );
																	/*年*/
				break;
			case EUR_CLOCK_TYPE:
				AscString[2]  = '/';
				AscString[5]  = '/';
				CMN_UnsignedIntToASC( &AscString[0],  (UWORD)day,    2, ' ' );
																	/*日*/
				CMN_UnsignedIntToASC( &AscString[3],  (UWORD)month,  2, ' ' );
																	/*月*/
				if ( year >= 92 )
					CMN_UnsignedIntToASC( &AscString[6], 19, 2, '0' );
				else
					CMN_UnsignedIntToASC( &AscString[6], 20, 2, '0' );
				CMN_UnsignedIntToASC( &AscString[8],  (UWORD)year,   2, '0' );
																	/*年*/
				break;
		}
		CMN_UnsignedIntToASC( &AscString[11], (UWORD)hour,   2, ' ' );
															/*時*/
		CMN_UnsignedIntToASC( &AscString[14], (UWORD)minute, 2, '0' );
													/*分*/
		break;
	default:
		break;
	}
}

/*************************************************************************
	module		:[日付ﾀｲﾌﾟ。]
	function	:[日付のﾀｲﾌﾟを返す。]
	common		:[
		SYB_WordingNumber	:
		MachineParameter	:
	]
	condition	:[]
	comment		:[]
	return		:[日付ﾀｲﾌﾟ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
UBYTE		DateTypeGet( void )
{
	UBYTE	DateType;			/*日付ﾀｲﾌﾟ*/

#if defined(SEA)
	/* Add By Okumura & Ohara '93/8/12 */
	if (SYB_MachineParameter[0] == 0 ) {	/* TWN */
		switch (SYB_WordingNumber) {
		case 1:
			DateType = USA_CLOCK_TYPE;
			break;
		case 2:
			DateType = USA_CLOCK_TYPE;
			break;
		case 3:
			DateType = USA_CLOCK_TYPE;
			break;
		default:
			break;
		}
	}
	else {									/* TUR,UAE,SGP,THA,HKG,IND,IDN,MYS */
		switch (SYB_WordingNumber) {
		case 1:
			DateType = EUR_CLOCK_TYPE;
			break;
		case 2:
			DateType = EUR_CLOCK_TYPE;
			break;
		case 3:
			DateType = EUR_CLOCK_TYPE;
			break;
		default:
			break;
		}
	}
#else
	switch (SYB_WordingNumber) {
	case 1:
		DateType = DATE_WORDING_1;
		break;
	case 2:
		DateType = DATE_WORDING_2;
		break;
	case 3:
		DateType = DATE_WORDING_3;
		break;
	default:
		break;
	}
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && (PRO_OKI == ENABLE)	/* by K.Watanabe 1998/10/02 */
	if (SYB_MaintenanceSwitch[MNT_SW_A8] & FIXED_ENG_WORDING) {	/* 英語ワーディング固定表示の時 */
		DateType = USA_CLOCK_TYPE;
	}
#endif

	return(DateType);
}
