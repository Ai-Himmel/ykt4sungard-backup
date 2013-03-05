/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_INST.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 設置モードオペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\mem_def.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#if (PRO_MODEM == ORANGE3) /* By H.Fujimura 1999/01/06 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#endif
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include 	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\man_pro.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\ext_v\extv_sem.h"
#endif

#if (PRO_MULTI_LINE == ENABLE)
#include	"\src\atlanta\define\sys_opt.h"
#include	"\src\atlanta\define\unisw_a.h"
#include	"\src\atlanta\define\mlt_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\memsw\define\mems_pro.h"
#endif
#if defined(TWN)	/* by M.H  17.Feb '98 */
#include	"\src\atlanta\define\stng_pro.h"
#endif

#if defined(STOCKHM2)	/* ダイヤルトーン検出対応 by SMuratec 夏 2004/7/13 */
#include	"\src\memsw\define\mems_pro.h"
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec K.W.Q 2005/06/08 */
#include	"\src\atlanta\hinoki\define\m_param.h"
#include	"\src\atlanta\define\sysrxsw.h"
/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
#include	"\src\atlanta\define\sysnd.h"
#include	"\src\atlanta\define\ncu_stat.h"
#include	"\src\atlanta\ext_v\ncu_data.h"
#endif		/* End of (defined (KEISATSU)) */


/* Prototype
void	UserInstallOperation(void);
UBYTE	SetDateAndTime(void);
UBYTE	CheckCalenderInput(void);
void	SetClockData(UBYTE);
#if defined(USA)
UBYTE	SetDayLightSaving(void);
#endif
UBYTE	EnterYourTTI(void);
UBYTE	TTI_FaxNumberInput(void);
UBYTE	TTI_NameInput(void);
UBYTE	TTI_ID_NameInput(void);
UBYTE	SetPhoneType(void);
UBYTE	SetAutoReceiveMode(void);
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/ by K.Watanabe 1997/12/10 /
UBYTE	ConfirmPrintSettingList(void);
#endif
#if (PRO_MULTI_LINE == ENABLE)
UBYTE	EnterMultiLineYourTTI(UBYTE);
UBYTE	SetMultiLinePhoneType(UBYTE);
UBYTE	SetMultiLineTxRx(void);
UBYTE	SetMultiLineLineType(void);
UBYTE	SetPstnAccessNumber(void);
#endif
*/

/*************************************************************************
	module		:[設置モードオペレーション]
	function	:[
		1.以下の項目を順番にセットする。
		,時計セット
		,夏時間自動切り替えセット
		,ＴＴＩセット
		,回線セット
		,受信モードセット
		,機器設定リスト
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/18]
	author		:[江口]
*************************************************************************/
void UserInstallOperation(void)
{
#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/29 */
	UBYTE	i;
#endif
#if (PRO_MULTI_LINE == ENABLE)
	UBYTE	line_ck;
	UBYTE	bord_ck;

	line_ck = 0;
	bord_ck = 0;
#endif

	/*----------------------*/
	/** 時計セット 			*/
	/*----------------------*/
	if (SetDateAndTime() == NG) {	/* STOP */
		return;
	}

#if defined(USA)
	/*------------------------------*/
	/** 夏時間自動切り替えのセット	*/
	/*------------------------------*/
	if (SetDayLightSaving() == NG) {	/* STOP */
		return;
	}
#endif

#if (PRO_MULTI_LINE == DISABLE)
	/*----------------------*/
	/** ＴＴＩセット		*/
	/*----------------------*/
	if (EnterYourTTI() == NG) {	/* STOP */
		return;
	}
	
 #if !defined(SATSUKI2) /* SATSUKI2では回線セットは行いません。by Y.Kano 2003/09/17 *//* Mod by SMuratec C.P 2004/06/15 for STOCKHM2 */
	/*----------------------*/
	/** 回線セット			*/
	/*----------------------*/
	if (SetPhoneType() == NG) {	/* STOP */
		return;
	}
 #endif

 #if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/10/10 */
 	if (SetKeidenDialTone() == NG ) {
		return;
	}
 #endif		/* End of (defined (KEISATSU)) */

 /* ダイヤルトーン検出対応 by SMuratec 夏 2004/7/13 */
 #if defined(STOCKHM2) || defined(HINOKI3)	/* Add by Y.Kano 2004/11/25 */
 	if (SetDialTone() == NG ){
		return;
	} 
 #endif

 #if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/09 */
 	if (SetDefaultLine() == NG ){
		return;
	} 
 	if (SetDefaultCOMMethod() == NG ){
		return;
	} 
 	if (SetKeidenScramleOn() == NG ){
		return;
	} 
 	if (SetKanyuScramleOn() == NG ){
		return;
	} 
	return;
 #endif		/* End of (defined (KEISATSU)) */

#else
	bord_ck = OPT_CountModems();	 /* 回線の数を待避 */
	for (OPR_InstallOptionLine = 0; OPR_InstallOptionLine < SYS_OPTION_BOARD_MAX; OPR_InstallOptionLine++) {
		/* いくつめのボードかを検索、前と同じ値であればボードがないものとみなす */
		if ((OPR_InstallLineCount = OPT_GetMultiLinrNumber(OPR_InstallOptionLine)) != line_ck) {
			line_ck = OPR_InstallLineCount;	/* 次にチェックするため待避 */
			/*----------------------*/
			/** ＴＴＩセット		*/
			/*----------------------*/
#if defined(TWN)		/* by M.H  17.Feb '98 for TUR */
			if(CHK_HardDipProtection()==NO){
				if (EnterMultiLineYourTTI(bord_ck) == NG) {	/* STOP */
					return;
				}
			}
#else
			if (EnterMultiLineYourTTI(bord_ck) == NG) {	/* STOP */
				return;
			}
#endif

			/*----------------------*/
			/** 回線セット			*/
			/*----------------------*/
			if (SetMultiLinePhoneType(bord_ck) == NG) {	/* STOP */
				return;
			}

			/* 一回線しかない場合、送受信モード、外線内線セットの登録はなし */
			if (bord_ck == 1) {
				break;
			}

			/*----------------------*/
			/** 送受信モードセット	*/
			/*----------------------*/
			if (SetMultiLineTxRx() == NG) {	/* STOP */
				return;
			}

			/*----------------------*/
			/** 外線内線セット		*/
			/*----------------------*/
			if (SetMultiLineLineType() == NG) {	/* STOP */
				return;
			}
		}
	}
#endif	/* (PRO_MULTI_LINE == DISABLE) */

#if (PRO_AUTO_RX_SWITCH == ENABLE)
	/*#if !defined(USA)*/ /* USA仕様は、FAX Ready と TEL Ready のみのため、このオペレーションを削除します 1997/12/02 */
	/* 1997/12/19	F100R
	 * TEL/FAX,ANS/FAX切り替えは条件コンパイルではなく メンテＳＷで入れます
	*/
	/*----------------------*/
	/**	 受信モードセット	*/
	/*----------------------*/
	if (CMN_CheckTelFaxSuport()) {	/* TEL/FAX、ANS/FAXサポートする */
		if (SetAutoReceiveMode() == NG) {	/* STOP */
			return;
		}
	}

#else
	/*----------------------*/
	/**	 受信モードセット	*/
	/*----------------------*/
	if (SetAutoReceiveMode() == NG) {	/* STOP */
		return;
	}
#endif

#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/29 */
	/*----------------------*/
	/** マルチＴＴＩセット	*/
	/*----------------------*/
	for (i = 1; i <= SYS_MULTI_MAX; i++) {
		if (EnterMultiYourTTI(i) == NG) {	/* STOP */
			return;
		}
	}
#endif

#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* by K.Watanabe 1997/12/10 */
	/*----------------------*/
	/** 設定リストプリント	*/
	/*----------------------*/
	if (ConfirmPrintSettingList() == NG) {	/* STOP */
		return;
	}
#endif
}

#if defined(STOCKHM2) || defined(HINOKI3)	/* ダイヤルトーン検出対応 by SMuratec 夏 2004/7/13 */ /* Add by Y.Kano 2004/11/25 */
/*************************************************************************
	module		:[ダイヤルトーン検出]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2004/07/13]
	author		:[SMuratec 夏]
*************************************************************************/
UBYTE SetDialTone(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	memsw;

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
#if defined (KEISATSU) /* 警察FAX Added by SMuratec K.W.Q 2005/06/07 */
	DisplayStringHigh(0, D2W_KanyuDialToneOn);	/* "ｶﾆｭｳ ﾀﾞｲﾔﾙ ﾄｰﾝ　:" */
#else
	DisplayStringHigh(0, D2W_DialToneOn);		/* "ﾀﾞｲﾔﾙﾄｰﾝ ｹﾝｼｭﾂ :" */
#endif		/* End of (defined (KEISATSU)) */

	if (!CHK_DialToneOrTimeupAvailable()) {
		DisplayStringHigh(16, D2W_On);  
		memsw = TRUE;					 
	}
	else {
		DisplayStringHigh(16, D2W_Off);   
		memsw = FALSE;					 
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
		case LEFT_ARROW:	/* 左矢印キー */
			if (memsw) {
				DisplayStringHigh(16, D2W_Off);  /* ダイヤルトーン修正 O.Oshima 2004/04/20 */
				memsw = FALSE;					/* ダイヤルトーン修正 O.Oshima 2004/04/20 */
			}
			else {
				DisplayStringHigh(16, D2W_On); /* ダイヤルトーン修正 O.Oshima 2004/04/20 */
				memsw = TRUE;					/* ダイヤルトーン修正 O.Oshima 2004/04/20 */
			}
			break;
		case ENTER:
			CHK_SetDialToneOrTimeAvailable(!memsw);
			return (OK);
		case STOP:
		case KEY_TIME_UP:
			return (NG);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}
#endif	/* End of defined(STOCKHM2) || defined(HINOKI3) */

/*************************************************************************
	module		:[時計セット機能。]
	function	:[
		1.カレンダーのセットを行う
	]
	return		:[なし]
	common		:[
		SYB_CurrentTime
		CharacterInput
	]
	condition	:[]
	comment		:[PRG - H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/2/17]
	author		:[江口]
*************************************************************************/
UBYTE SetDateAndTime(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	old_year;
	/* 追加 1997/07/25 Y.Matsukuma */
	UBYTE	old_current[10];

	/*-------------------*/
	/**  初期化処理		 */
	/*-------------------*/
	ClearCharacterInput();
	SetLongTimeToCharacterInput(SYB_CurrentTime, CALENDER_TYPE);
	CharacterInput.WritePosition = 9;
	CharacterInput.LcdDisplayPosition = 5;

	/** 設定前の年を取り出す *//* サマータイムのための処理 1995/12/21 Eguchi*/
	old_year = CMN_DecimalToBCD((UBYTE)CMN_ASC_ToUnsignedInt(CharacterInput.Buffer, 2));

	/* 設定前のカレンダーを待避  追加 1997/08/05 Y.Matsukuma*/
	CMN_StringCopyNum(old_current, CharacterInput.Buffer, 10);

	DisplayStringHigh(0, D2W_InputTime );

	/* 編集　*/
	while (1) {
		/** 表示処理 */
		DisplayTimeInput(CALENDER_TYPE);

		/** キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) { /** 入力されたキーに対する処理 */
		case NUMBER:	/** 数字（0 - 9) */
			FixedNumberDataSet(key);
			break;

		case STOP:			/** ストップキー */
		case KEY_TIME_UP:	/** １分間キー入力なし */
			/** 終了 */
			CursorOff();
			return (NG);

		case FUNCTION:	/**機能キー */
			/** カーソル右移動 */
			CursorRightRotation();
			break;

		case LEFT_ARROW:/** 左カーソルキー */
			/** カーソル左キー*/
			CursorLeftRotation();
			break;

		case ENTER:		/** セットキー */
			/** 入力データのチェックを行う */
			/* カレンダーが変更されているかチェック  追加 1997/08/05 Y.Matsukuma */
			if (CMN_StringCompare(old_current, CharacterInput.Buffer, 10) == STRCMP_EQUAL) {
				/**  消耗品発注日の設置日が何もｾｯﾄされていない時、現在時刻を登録 1998/02/27 By M.Kuwahara */
				if ( SYB_ConsumerOrder.InstallDate == NULL ) {
					SYB_ConsumerOrder.InstallDate	= SYB_CurrentTime;
				}
				return(OK);	/* 更新されていなければ、RTCにセットしない */
			}

			if (CheckCalenderInput() == OK) {
				/** オペレーションで登録された日時をRTCにセット */
				SetClockData(old_year);
				/**  消耗品発注日の設置日が何もｾｯﾄされていない時、現在時刻を登録 1998/02/27 By M.Kuwahara */
				if ( SYB_ConsumerOrder.InstallDate == NULL ) {
					SYB_ConsumerOrder.InstallDate = CMN_BCD_TimeToLong(&CurrentTimeInBCD);
				}

				CursorOff();
				return (OK);
			}
			CharacterInput.CursorPosition = 0;
			NackBuzzer();
			break;

#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif

		case NO_EFFECT:
		case OPR_NO_KEY:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[カレンダー入力。入力値チェック]
	function	:[
		1.入力された年月日時分が最小値と最大値の間に収まっているか調べる。
		2.入力された年月日が正当かチェックする。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/03]
	author		:[江口]
*************************************************************************/
UBYTE CheckCalenderInput(void)
{
	UBYTE	year;
	UBYTE	month;
	UBYTE	day;
	UBYTE	hour;
	UBYTE	minute;
	UBYTE	leap_flag;

	year   = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 2);
	month  = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[2], 2);
	day    = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[4], 2);
	hour   = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[6], 2);
	minute = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[8], 2);
	leap_flag = CheckLeapYear(year);

	if ((year <= 99)
	 && (1 <= month && month <= 12)
	 && (1 <= day && day <= 31)
	 && (hour <= 23)
	 && (minute <= 59)) {		 /* 最大値、最小値に収まっている */
		if (MaxDayTable[leap_flag][month] >= day) {	 /* 入力された日数が正しい */
			return (OK);
		}
	}
	return (NG);
}

/*************************************************************************
	module		:[現在日時（CurrentTime）データセット]
	function	:[
		1.現在日時（CurrentTime）にDigitValue.Bufferの日時をセット
	]
	return		:[なし]
	common		:[
		CurrentTimeInBCD:
		DigitValue:アスキーデータ
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/2/17]
	author		:[S.Kawasaki]
*************************************************************************/
void SetClockData(UBYTE old_year)
{
	UDWORD	long_time;

	/** ASCIIで入力された時間をBCDに変換 */
	StoreCharacterInputValue(OperationTime.BCD_StringTime, BCD_DATA_TYPE);

	/** セマフォの獲得 19960329 */
	wai_sem(semno.rtc);

	/* 現在時刻の構造体にセット */
	CurrentTimeInBCD.Year   = OperationTime.BCD_StructTime.Year;	/* 年 */
	CurrentTimeInBCD.Month  = OperationTime.BCD_StructTime.Month;	/* 月 */
	CurrentTimeInBCD.Date   = OperationTime.BCD_StructTime.Date;	/* 日 */
	CurrentTimeInBCD.Hour   = OperationTime.BCD_StructTime.Hour;	/* 時 */
	CurrentTimeInBCD.Minute = OperationTime.BCD_StructTime.Minute;	/* 分 */
	CurrentTimeInBCD.Second = 0;									/* 秒 */
	CMN_LongTimeToBCD((TIME_DATA_t *)&CurrentTimeInBCD, CMN_BCD_TimeToLong((TIME_DATA_t *)&CurrentTimeInBCD));

	/* サマータイムのための処理 1995/12/21 Eguchi */
	if (old_year == CurrentTimeInBCD.Year) { /** 年が更新されなかった場合 */
		long_time = CMN_BCD_TimeToLong(&CurrentTimeInBCD);
		SetSummerTimeStatus(long_time); /** セットされた時刻がサマータイム中の時刻かどうか調べる */
	}
	/** 登録されたＢＣＤ時刻をＲＴＣに書き込む */
	WriteCurrentTime();

	/** セマフォの解放 19960329 */
	sig_sem(semno.rtc);
}

/*************************************************************************
	module		:[夏時間切り替えセット]
	function	:[
		1.夏時間切り替えを自動で行うか否かの設定を行う。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/21]
	author		:[江口]
*************************************************************************/
#if defined(USA)
UBYTE SetDayLightSaving(void)
{
	/** ＯＮ／ＯＦＦ切り替えオペレーション実行 */
	if (EnterSettingStatus(D2W_DayLightSaving,
						   D2W_Off2,
	 					   2,
						   SETTING_STATUS_23,
						   OPR_VALID_CHECK_NOT_NEED,
	 					   DAYLIGHT_SAVING_AUTO) == OK) {	/* 登録完了 */
		return (OK);
	}
	return (NG);
}
#endif	/* defined(USA) */

/*************************************************************************
	module		:[発信元名登録機能]
	function	:[
		1.発信元ＦＡＸ番号の登録及び発信元名の登録を行う
	]
	return		:[なし]
	common		:[
		SYB_ID_Buffer:
		SYB_TTI_Buffer:
#if (PRO_JIS_CODE == ENABLE)
		SYB_TTI_ID_Buffer:
#endif
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/2/17]
	author		:[S.Kawasaki,渡辺一章]
*************************************************************************/
UBYTE EnterYourTTI(void)
{
	/** 自機ＦＡＸ番号入力 */
	DisplayStringHigh(0, D2W_EnterYourFaxNumber);	/* "ﾊｯｼﾝﾓﾄ ﾌｧｸｽ ﾊﾞﾝｺﾞｳ  " */
	if (TTI_FaxNumberInput() == OK) {
		/* 入力データをセット */
#if defined (KEISATSU)		/* 警察FAX DVT_ID14 Modify by SMuratec K.W.Q 2005/11/04 */
		StoreCharacterInputValue(SYB_ID_Buffer[0], ASC_DATA_TYPE);
		StoreCharacterInputValue(SYB_ID_Buffer[1], ASC_DATA_TYPE);
#else
		StoreCharacterInputValue(SYB_ID_Buffer, ASC_DATA_TYPE);
#endif		/* End of (defined (KEISATSU)) */

		/** 自機、名前入力 */
		DisplayStringHigh(0, D2W_EnterYourName);	/* "ﾊｯｼﾝﾓﾄ ﾒｲ           " */
		if (TTI_NameInput() == OK) {
			/* 入力データをセット */
#if (PRO_JIS_CODE == ENABLE)
 #if defined (KEISATSU)		/* 警察FAX DVT_ID14 Modify by SMuratec K.W.Q 2005/11/04 */
			StoreCharacterInputValue(SYB_TTI_Buffer[0], ASC_JIS_DATA_TYPE);
			StoreCharacterInputValue(SYB_TTI_Buffer[1], ASC_JIS_DATA_TYPE);
 #else
			StoreCharacterInputValue(SYB_TTI_Buffer, ASC_JIS_DATA_TYPE);
 #endif		/* End of (defined (KEISATSU)) */

			/** 自機、カナＩＤ入力 */
			DisplayStringHigh(0, D2W_EnterYourKanaName);	/* "ﾊｯｼﾝﾓﾄ ｶﾅID         " */
			if (TTI_ID_NameInput() == OK) {
				/* 入力データをセット */
 #if defined (KEISATSU)		/* 警察FAX DVT_ID14 Modify by SMuratec K.W.Q 2005/11/04 */
				StoreCharacterInputValue(SYB_TTI_ID_Buffer[0], ASC_DATA_TYPE);
				StoreCharacterInputValue(SYB_TTI_ID_Buffer[1], ASC_DATA_TYPE);
 #else
				StoreCharacterInputValue(SYB_TTI_ID_Buffer, ASC_DATA_TYPE);
 #endif		/* End of (defined (KEISATSU)) */
				return (OK);
			}
#else
			StoreCharacterInputValue(SYB_TTI_Buffer, ASC_DATA_TYPE);
			return (OK);
#endif
		}
	}
	return (NG); /* 終了 */
}

/*************************************************************************
	module		:[ＴＴＩのＦＡＸ番号の入力]
	function	:[
		1.発信元ＦＡＸ番号の登録を行う
		2.発信元ＦＡＸ番号は２０桁以内
	]
	return		:[
				OK:登録完了
				NG:登録中止
				]
	common		:[
					CharacterInput
					SYB_ID_Buffer
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/09]
	author		:[江口]
*************************************************************************/
UBYTE TTI_FaxNumberInput(void)
{
	UBYTE	key;			/* ｷｰ取り込みﾃﾞｰﾀ     */

	/** 初期化 */
	ClearCharacterInput();
#if (PRO_MULTI_LINE == DISABLE)
	CMN_StringCopy(CharacterInput.Buffer, SYB_ID_Buffer);
#else
	if (OPR_InstallOptionLine == 0) {
		CMN_StringCopy(CharacterInput.Buffer, SYB_ID_Buffer);
	}
	else {
		CMN_StringCopy(CharacterInput.Buffer, SYB_Option_ID_Buffer[OPR_InstallOptionLine]);
	}
#endif
	CharacterInput.MaxFigure = SYS_ID_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

	/** データ入力 */
	while (1) {

		/** 下段に登録状況を表示 */
		DisplayNumberInput();

		/** キー取り込み */
		key = NumberInputKeyGet();

		switch (key) {
		case STOP_KEY:			/* ストップキー */
			/* 終了 */
			CursorOff();
			return (NG);
		case SET_KEY:			/* セットキー	*/
			/* 終了 */
			CursorOff();
			return (OK);
		case DIAL_MARK_KEY:		/* ダイアル記号キー */
			/* バッファの先頭なら＋、それ以外の場合ーをセットする */
			if ((CharacterInput.Buffer[0] == NULL) || (CharacterInput.CursorPosition == 0)) {
				if (CharacterInput.Buffer[0] == '+') {
					NackBuzzer();
					break;
				}
				else {
					key = '+';
				}
			}
			else {
				key = '-';
			}
			CharacterDataSet_FigureCheck(key);
			break;
#if 0 /* (PRO_KEYPANEL == PANEL_HINOKI) */ /* とりあえず保留 */
 #if (PRO_POST_OFFICE == ENABLE)	/* 郵政局特ROM スペースを入力できるようにする 2002/06/20 T.Takagi */
		case ONETOUCH_26_KEY:	/* スペースキー */
			key = ' ';
			CharacterDataSet_FigureCheck(key);
			break;
 #endif			
#endif
		case OPR_NO_KEY:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[発信元名入力]
	function	:[
		1.発信元名の登録を行う。
		2.発信元名は２２桁以内
	]
	return		:[]
	common		:[
		CharacterInput
		SYB_TTI_Buffer
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/29]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE TTI_NameInput(void)
{
	ClearCharacterInput();
	SetCharacterInputMode();	/* 文字入力モード初期化 */
	/* 前回入力値を名前入力用バッファに展開する */
#if (PRO_MULTI_LINE == DISABLE)
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/09/27 */
	OPR_SetRegisteredDataToBuf(CharacterInput.Buffer, SYB_TTI_Buffer, 0);	/* 前回登録データをセット */
 #else
 	SetCharacterInputBuf(SYB_TTI_Buffer);
 #endif
#else
	if (OPR_InstallOptionLine == 0) {
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/09/27 */
		OPR_SetRegisteredDataToBuf(CharacterInput.Buffer, SYB_TTI_Buffer, 0);	/* 前回登録データをセット */
 #else
		SetCharacterInputBuf(SYB_TTI_Buffer);
 #endif
	}
	else {
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/09/27 */
		OPR_SetRegisteredDataToBuf(CharacterInput.Buffer, SYB_Option_TTI_Buffer[OPR_InstallOptionLine], 0);	/* 前回登録データをセット */
 #else
		SetCharacterInputBuf(SYB_Option_TTI_Buffer[OPR_InstallOptionLine]);
 #endif
	}
#endif
	CharacterInput.MaxFigure = SYS_TTI_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_ENABLE)) {
		return(OK);
	}
	else {
		return(NG);
	}
#else
	return (NameInput(OPR_KANJI_ENABLE));
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[発信元名（カナＩＤ）入力]
	function	:[
		1.発信元名（カナＩＤ）の登録を行う
		2.発信元名は１６文字以内
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/19]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_JIS_CODE == ENABLE)
UBYTE TTI_ID_NameInput(void)
{
	ClearCharacterInput();
	SetCharacterInputMode();	/* 文字入力モード初期化 */
#if (PRO_MULTI_LINE == DISABLE)
	CMN_StringCopy(CharacterInput.Buffer, SYB_TTI_ID_Buffer);
#else
	if (OPR_InstallOptionLine == 0) {
		CMN_StringCopy(CharacterInput.Buffer, SYB_TTI_ID_Buffer);
	}
	else {
		CMN_StringCopy(CharacterInput.Buffer, SYB_Option_TTI_ID_Buffer[OPR_InstallOptionLine]);
	}
#endif
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;
	CharacterInput.MaxFigure = SYS_TTI_ID_MAX - 1;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_DISABLE)) {
		return(OK);
	}
	else {
		return(NG);
	}
#else
	return (NameInput(OPR_KANJI_DISABLE));
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}
#endif

/*************************************************************************
	module		:[回線セット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/30]
	author		:[江口]
*************************************************************************/
UBYTE SetPhoneType(void)
{
	UBYTE	*wording;

 #if defined(USA) || defined(GBR) || defined(AUS) || defined(TWN) || defined(SGP) || defined(DEU) || defined(EC1) || defined(EUR)
	wording = D2W_Pulse10;
 #else
	wording = D2W_10pps;
 #endif

 #if defined (KEISATSU) /* 警察FAX Added by SMuratec K.W.Q 2005/06/07 */
	if (EnterSettingStatus(D2W_SelectKeidenPhoneType,
						   wording,
	 					   3,
	 					   SETTING_STATUS_29,
	 					   OPR_LINE_TYPE,
						   (DIAL_SPEED_20PPS_EXT | LINE_TYPE_TONE_EXT)) == NG) {
		return (NG);
	}
	if (EnterSettingStatus(D2W_SelectKanyuPhoneType,
						   wording,
	 					   3,
	 					   SETTING_STATUS_0,
	 					   OPR_LINE_TYPE,
						   (DIAL_SPEED_20PPS | LINE_TYPE_TONE)) == NG) {
		return (NG);
	}
	
	return (OK);
 #else
	if (EnterSettingStatus(D2W_SelectPhoneType,
						   wording,
	 					   3,
	 					   SETTING_STATUS_0,
	 					   OPR_LINE_TYPE,
						   (DIAL_SPEED_20PPS | LINE_TYPE_TONE)) == OK) {
		return (OK);
	}
	
	return (NG);
 #endif		/* End of (defined (KEISATSU)) */
}

/*************************************************************************
	module		:[自動受信モードセット]
	function	:[
		1.自動受信モードの切り替えを実行
		2.以下のモードがあり
		,	・Ｔｅｌ　Ｒｅａｄｙ
		,	・Ｆａｘ　Ｒｅａｄｙ
		,	・Ｆａｘ／Ｔｅｌ　Ｒｅａｄｙ　：電話ＦＡＸ待機、ＦＡＸ優先。杏から追加
		,	・Ｔｅｌ／Ｆａｘ　Ｒｅａｄｙ　：電話ＦＡＸ待機、電話優先。　杏から追加
		,	・Ａｎｓ／Ｆａｘ　Ｒｅａｄｙ
		,	. ＤＩＡＬ＿Ｉｎ　Ｒｅａｄｙ　：ダイヤルイン
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/30]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE SetAutoReceiveMode(void)
{

 #if (PRO_KEYPANEL == PANEL_SATSUKI2) /* DIAL_INの追加 by Y.Kano 2003/08/26 *//*Del STOCKHM2 by SMuratec C.P 2004/07/23 */
	if ((SYB_SettingStatus[SETTING_STATUS_3] & 0xf0) == DIAL_IN_ON) {	/* ダイヤルイン待機の場合、オペレーション用に置き換える。*/
		SYB_SettingStatus[SETTING_STATUS_3] &= 0x0f;
		SYB_SettingStatus[SETTING_STATUS_3] |= DIALIN_MODE;
	}
	if (EnterSettingStatus(D2W_Null,
						   D2W_TelReady,	/* "ﾃﾞﾝﾜ ﾀｲｷ            " */
						   6,
						   SETTING_STATUS_3,
						   OPR_RECEIVE_MODE,
						   (MANUAL_RX_MODE      | AUTO_RX_MODE_FAX | AUTO_RX_MODE_FAXTEL |
							AUTO_RX_MODE_TELFAX | AUTO_RX_MODE_ANSFAX | DIALIN_MODE)) == OK) {

		if ((SYB_SettingStatus[SETTING_STATUS_3] & 0xf0) == DIALIN_MODE ) {	/* ダイヤルイン設定の時のみ処理する。*/
			SetDialIn();
			SYB_SettingStatus[SETTING_STATUS_3] &= 0x0f;	/* 下位データを残す。*/
			SYB_SettingStatus[SETTING_STATUS_3] |= DIAL_IN_ON;	/* 通常使用するダイヤルインのステータスをセット */
		}
		else {	/* ダイヤルイン待機以外は番号未登録エラーを解除。by Y.Kano 2003/10/21 */
			SYS_MachineStatus[SYS_ERROR_STATUS] &= ~SYS_ERROR_NO_DIAL_IN_NUMBER; /* 番号未登録エラーを解除しておく */
		}
 #else
	if (EnterSettingStatus(D2W_Null,
						   D2W_TelReady,	/* "ﾃﾞﾝﾜ ﾀｲｷ            " */
						   5,
						   SETTING_STATUS_3,
						   OPR_RECEIVE_MODE,
						   (MANUAL_RX_MODE      | AUTO_RX_MODE_FAX | AUTO_RX_MODE_FAXTEL |
							AUTO_RX_MODE_TELFAX | AUTO_RX_MODE_ANSFAX)) == OK) {
 #endif
 #if (PRO_AUTO_RX_SWITCH == DISABLE)	/* by K.Watanabe 1997/11/06 */
		/* 電話中に自動受信から手動受信に変更されると、電話終了までＬＥＤが更新されない
		** （OPR_Task()が走らないと更新されないため）ので、ここでも更新を行うようにします
		*/
		UpdateLED();
 #endif
		return (OK);
	}
	
	return (NG);
}

/*************************************************************************
	module		:[機器設定リスト]
	function	:[
		1.機器設定リストの印字の起動をかける
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/19]
	author		:[江口]
*************************************************************************/
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* by K.Watanabe 1997/12/10 */
UBYTE ConfirmPrintSettingList(void)
{
	if (ConfirmKeyInputOperation(D2W_PrintSettingList, D2W_EnterStop, ENTER, STOP) == CONFIRM_EXEC) {
		FinalListPrintOperation(LST_PARAMETER_LIST); /* メインにリスト起動メッセージ送信 1995/04/04 Egu*/
		return (OK);
	}
	return (NG);
}
#endif

#if (PRO_MULTI_LINE == ENABLE)
/*************************************************************************
	module		:[２回線用発信元名登録機能]
	function	:[
		1.１回線目と２回線目以降の、発信元ＦＡＸ番号の登録、及び発信元名の登録を行う
	]
	common		:[
		SYB_ID_Buffer:
		SYB_TTI_Buffer:
	]
	condition	:[]
	commment	:[]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[96/11/19]
	author		:[松隈]
*************************************************************************/
UBYTE EnterMultiLineYourTTI(UBYTE Bord)
{
	UBYTE	*id_buffer;		/* ＩＤ入力バッファ			*/
	UBYTE	*tti_buffer;	/* ＴＴＩ入力バッファ		*/
	UBYTE	*tti_id_buffer;	/* ＴＴＩ　ＩＤ入力バッファ	*/

	if (OPR_InstallOptionLine == 0) {
		id_buffer = SYB_ID_Buffer;
		tti_buffer = SYB_TTI_Buffer;
		tti_id_buffer = SYB_TTI_ID_Buffer;
	}
	else {
		id_buffer = SYB_Option_ID_Buffer[OPR_InstallOptionLine];
		tti_buffer = SYB_Option_TTI_Buffer[OPR_InstallOptionLine];
		tti_id_buffer = SYB_Option_TTI_ID_Buffer[OPR_InstallOptionLine];
	}

	/** 自機ＦＡＸ番号入力 */
	if (Bord == 1) {
		DisplayStringHigh(0, D2W_EnterYourFaxNumber);	/* "Your Fax Number     " */
	}
	else {
		DisplayStringHigh(0, D2W_MultiYourFaxNumber);	/* "ﾊｯｼﾝﾓﾄ ﾌｧｸｽﾊﾞﾝｺﾞｳ( )" */
		DisplayChar(18, ChangeNumberToASC_Code(OPR_InstallLineCount));
	}
	if (TTI_FaxNumberInput() == OK) {
		/* 入力データをセット */
		StoreCharacterInputValue(id_buffer, ASC_DATA_TYPE);

		/** 自機、名前入力 */
		if (Bord == 1) {
			DisplayStringHigh(0, D2W_EnterYourName);	/* "Your Name           " */
		}
		else {
			DisplayStringHigh(0, D2W_MultiYourName);	/* "ﾊｯｼﾝﾓﾄﾒｲ( )         " */
			DisplayChar(9, ChangeNumberToASC_Code(OPR_InstallLineCount));
		}
		if (TTI_NameInput() == OK) {
			/* 入力データをセット */
#if (PRO_JIS_CODE == ENABLE)
			StoreCharacterInputValue(tti_buffer, ASC_JIS_DATA_TYPE);

			/** 自機、カナＩＤ入力 */
			if (Bord == 1) {
				DisplayStringHigh(0, D2W_EnterYourKanaName);	/* "ﾊｯｼﾝﾓﾄ ｶﾅID         " */
			}
			else {
				DisplayStringHigh(0, D2W_MultiYourKanaName);	/* "ｶﾅID    ( )         " */
				DisplayChar(9, ChangeNumberToASC_Code(OPR_InstallLineCount));
			}
			if (TTI_ID_NameInput() == OK) {
				/* 入力データをセット */
				StoreCharacterInputValue(tti_id_buffer, ASC_DATA_TYPE);
				return (OK);
			}
#else
			StoreCharacterInputValue(tti_buffer, ASC_DATA_TYPE);
			return (OK);
#endif
		}
	}
	return (NG); /* 終了 */
}

/*************************************************************************
	module		:[２回線用回線セット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/11/19]
	author		:[松隈]
*************************************************************************/
UBYTE SetMultiLinePhoneType(UBYTE Bord)
{
	UBYTE	*wording;
	UBYTE	set_status;
	UBYTE	set_value;

#if defined(USA) || defined(GBR) || defined(AUS) || defined(TWN) || defined(SGP) || defined(FRA) || defined(EC1) || defined(EC2) || defined(EC3) || defined(DEU) || defined(EUR)
	wording = D2W_Pulse10;
#else
	wording = D2W_10pps;
#endif

	/* 上段表示のワーディングを作る */
	if (Bord == 1) {
		CMN_StringCopyNULL(DisplayBufferHigh, D2W_SelectPhoneType);	/* "ﾀﾞｲﾔﾙ ﾀｲﾌﾟ   :      " */
	}
	else {
		CMN_StringCopyNULL(DisplayBufferHigh, D2W_MultiPhoneType);	/* "ﾀﾞｲﾔﾙ ﾀｲﾌﾟ( ):      " */
		DisplayBufferHigh[11] = ChangeNumberToASC_Code(OPR_InstallLineCount);
	}

	switch (OPR_InstallOptionLine) {
	case 0:
		set_status = SETTING_STATUS_0;
		set_value = (DIAL_SPEED_20PPS | LINE_TYPE_TONE);
		break;
	case 1:
		set_status = SETTING_STATUS_0;
		set_value = (DIAL_SPEED_20PPS_1 | LINE_TYPE_TONE_1);
		break;
	case 2:
		set_status = SETTING_STATUS_0;
		set_value = (DIAL_SPEED_20PPS_2 | LINE_TYPE_TONE_2);
		break;
	case 3:
		set_status = SETTING_STATUS_28;
		set_value = (DIAL_SPEED_20PPS_3 | LINE_TYPE_TONE_3);
		break;
	case 4:
		set_status = SETTING_STATUS_28;
		set_value = (DIAL_SPEED_20PPS_4 | LINE_TYPE_TONE_4);
		break;
	case 5:
		set_status = SETTING_STATUS_28;
		set_value = (DIAL_SPEED_20PPS_5 | LINE_TYPE_TONE_5);
		break;
	case 6:
		set_status = SETTING_STATUS_29;
		set_value = (DIAL_SPEED_20PPS_6 | LINE_TYPE_TONE_6);
		break;
	case 7:
		set_status = SETTING_STATUS_29;
		set_value = (DIAL_SPEED_20PPS_7 | LINE_TYPE_TONE_7);
		break;
	case 8:
		set_status = SETTING_STATUS_29;
		set_value = (DIAL_SPEED_20PPS_8 | LINE_TYPE_TONE_8);
		break;
	}

	if (EnterSettingStatus(DisplayBufferHigh,
						   wording,
						   3,
						   set_status,
						   OPR_LINE_TYPE,
						   set_value) == OK) {
		return (OK);
	}
	return (NG);
}

/*************************************************************************
	module		:[送受信モードセット]
	function	:[
		1.送受信可能or送信専用or受信専用の選択
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/11/19]
	author		:[松隈,渡辺一章]
*************************************************************************/
UBYTE SetMultiLineTxRx(void)
{
	UBYTE	line_tx_rx;	/* 回線属性 */

	/* 上段表示ワーディングの設定 */
	CMN_StringCopyNULL(DisplayBufferHigh, D2W_MultiTxRx);	/* "ｿｳｼﾝ/ｼﾞｭｼﾝ( ):      " */
	DisplayBufferHigh[11] = ChangeNumberToASC_Code(OPR_InstallLineCount);

	/* 設定済みの回線属性を取得します */
	line_tx_rx = OPT_CHK_UNI_LineTxRx(OPR_InstallOptionLine);

	/* 回線属性の設定 */
	if (SelectData(DisplayBufferHigh,	/* "ｿｳｼﾝ/ｼﾞｭｼﾝ(1):      " */
				   D2W_SelectTxRx,		/* "              Tx/Rx " */
				   3,
				   &line_tx_rx,
				   EXCLUSIVE_TRX | EXCLUSIVE_TX | EXCLUSIVE_RX,
				   NO_KEYTYPE) == OPR_CANCELED) {	/* 登録中止又は、タイムアップの時 */
		return(NG);
	}

	switch (OPR_InstallOptionLine) {
	case 0:
		SET_UNI_Line0_TxRx(line_tx_rx);
		break;
	case 1:
		SET_UNI_Line1_TxRx(line_tx_rx);
		break;
	case 2:
		SET_UNI_Line2_TxRx(line_tx_rx);
		break;
	case 3:
		SET_UNI_Line3_TxRx(line_tx_rx);
		break;
	case 4:
		SET_UNI_Line4_TxRx(line_tx_rx);
		break;
	case 5:
		SET_UNI_Line5_TxRx(line_tx_rx);
		break;
	case 6:
		SET_UNI_Line6_TxRx(line_tx_rx);
		break;
	case 7:
		SET_UNI_Line7_TxRx(line_tx_rx);
		break;
	case 8:
		SET_UNI_Line8_TxRx(line_tx_rx);
		break;
	default:
		break;
	}

	return(OK);
}

/*************************************************************************
	module		:[外線／内線設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/11/19]
	author		:[松隈,渡辺一章]
*************************************************************************/
UBYTE SetMultiLineLineType(void)
{
	UBYTE	line_pstn_pbx;		/* 回線種別 */
	UBYTE	line_cnt_dsp_byte;

	/* 上段表示ワーディングの設定 */
	CMN_StringCopyNULL(DisplayBufferHigh, D2W_MultiLineType);	/* "ﾗｲﾝ ﾀｲﾌﾟ  (9):      " */

	/* 国別のワーディングの違いを吸収するために、回線の表示位置を求めます */
	line_cnt_dsp_byte = (UBYTE)GetStringGapPoint(DisplayBufferHigh, '9');
	DisplayBufferHigh[line_cnt_dsp_byte] = ChangeNumberToASC_Code(OPR_InstallLineCount);

	/* 設定済みの回線種別を取得します */
	line_pstn_pbx = OPT_CHK_Pbx(OPR_InstallOptionLine);

	/* 回線種別の設定 */
	if (SelectData(DisplayBufferHigh,	/* "ﾗｲﾝ ﾀｲﾌﾟ  (1):      " */
				   D2W_SelectLinePstn,	/* "              ｶﾞｲｾﾝ " */
				   2,
				   &line_pstn_pbx,
				   TRUE,
				   NO_KEYTYPE) == OPR_CANCELED) {	/* 登録中止又は、タイムアップの時 */
		return(NG);
	}

	/* 設定されたモードをセットし、内線であれば、外線接続番号を登録します */
	if (line_pstn_pbx) {	/* 内線の時 */
		if (SetPstnAccessNumber() == NG) {
			return (NG);
		}
	}
	else {					/* 外線の時 */
		SYB_PbxAccessNumber[OPR_InstallOptionLine][0] = 0xFF;
	}

	switch (OPR_InstallOptionLine) {
	case 0:
		CHK_SetPBX(line_pstn_pbx);
		break;
	case 1:
		CHK_SetPBX1(line_pstn_pbx);
		break;
	case 2:
		CHK_SetPBX2(line_pstn_pbx);
		break;
	case 3:
		CHK_SetPBX3(line_pstn_pbx);
		break;
	case 4:
		CHK_SetPBX4(line_pstn_pbx);
		break;
	case 5:
		CHK_SetPBX5(line_pstn_pbx);
		break;
	case 6:
		CHK_SetPBX6(line_pstn_pbx);
		break;
	case 7:
		CHK_SetPBX7(line_pstn_pbx);
		break;
	case 8:
		CHK_SetPBX8(line_pstn_pbx);
		break;
	default:
		break;
	}

	return(OK);
}

/*************************************************************************
	module		:[ＰＳＴＮアクセス番号入力]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/11/29]
	author		:[松隈]
*************************************************************************/
UBYTE SetPstnAccessNumber(void)
{
	UBYTE	key;	/* ｷｰ取り込みﾃﾞｰﾀ */

	/** 初期化 */
	ClearCharacterInput();
	CMN_MemorySet(CharacterInput.Buffer, SYS_ACCESS_NUMBER_MAX, NULL);

	if (SYB_PbxAccessNumber[OPR_InstallOptionLine][0] != 0xFF) {
		/* 登録済みの番号を代入 */
		CMN_BCD_ToASC_StringNum(CharacterInput.Buffer,
								SYB_PbxAccessNumber[OPR_InstallOptionLine],
								(UBYTE)SYS_ACCESS_NUMBER_MAX * 2);
	}
	CharacterInput.MaxFigure = 10;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

	/* 上段表示 */
	DisplayStringHigh(0, D2W_SetAccessNumber);	/* "ｶﾞｲｾﾝ ｾﾂｿﾞｸﾊﾞﾝｺﾞｳ( )" */
	DisplayChar(18, ChangeNumberToASC_Code(OPR_InstallLineCount));

	/** データ入力 */
	while (1) {

		/** 下段に登録状況を表示 */
		DisplayNumberInput();

		/** キー取り込み */
		key = NumberInputKeyGet();
		switch (key) {
			case STOP_KEY:			/* ストップキー */
				/* 終了 */
				CursorOff();
				return (NG);

			case SET_KEY:			/* セットキー	*/
				/* 入力データをセット */
				StoreCharacterInputValue(SYB_PbxAccessNumber[OPR_InstallOptionLine], BCD_DATA_TYPE);
				CursorOff();
				return (OK);

			case TEN_SHARP_KEY:
			case TEN_AST_KEY:
/*				CharacterInputDataSet(key); 関数の中身が変わったため 1998/01/06 Y.Matsukuma */
				CharacterDataSet_FigureCheck(key);
				break;

			case OPR_NO_KEY:
				break;
			default:
				NackBuzzer();
				break;
		}
	}
}
#endif	/* (PRO_MULTI_LINE == ENABLE) */

#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/29 */
/*************************************************************************
	module		:[マルチ発信元名登録機能]
	function	:[
		1.マルチ発信元ＦＡＸ番号の登録及びマルチ発信元名の登録を行う
	]
	return		:[なし]
	common		:[
		SYB_Multi_ID_Buffer[i-1]:
		SYB_Multi_TTI_Buffer[i-1]:
#if (PRO_JIS_CODE == ENABLE)
		SYB_Multi_TTI_ID_Buffer[i-1]:
#endif
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/03/29]
	author		:[藤村春夫]
*************************************************************************/
UBYTE	EnterMultiYourTTI(UBYTE i)
{
	/** 自機ＦＡＸ番号入力 */
	DisplayStringHigh(0, D2W_MultiYourFaxNumber);	/* "ﾊｯｼﾝﾓﾄ ﾌｧｸｽﾊﾞﾝｺﾞｳ( )" */
	DisplayChar(18, ChangeNumberToASC_Code(i));
	if (Multi_TTI_FaxNumberInput(i) == OK) {
		/* 入力データをセット */
		StoreCharacterInputValue(SYB_Multi_ID_Buffer[i-1], ASC_DATA_TYPE);

		/** 自機、名前入力 */
		DisplayStringHigh(0, D2W_MultiYourName);	/* "ﾊｯｼﾝﾓﾄﾒｲ( )         " */
		DisplayChar(9, ChangeNumberToASC_Code(i));
		if (Multi_TTI_NameInput(i) == OK) {
			/* 入力データをセット */
#if (PRO_JIS_CODE == ENABLE)
			StoreCharacterInputValue(SYB_Multi_TTI_Buffer[i-1], ASC_JIS_DATA_TYPE);

			/** 自機、カナＩＤ入力 */
			DisplayStringHigh(0, D2W_MultiYourKanaName);	/* "ｶﾅID    ( )         " */
			DisplayChar(9, ChangeNumberToASC_Code(i));
			if (Multi_TTI_ID_NameInput(i) == OK) {
				/* 入力データをセット */
				StoreCharacterInputValue(SYB_Multi_TTI_ID_Buffer[i-1], ASC_DATA_TYPE);
				return (OK);
			}
#else
			StoreCharacterInputValue(SYB_Multi_TTI_Buffer[i-1], ASC_DATA_TYPE);
			return (OK);
#endif
		}
	}
	return (NG); /* 終了 */
}

/*************************************************************************
	module		:[マルチＴＴＩのＦＡＸ番号の入力]
	function	:[
		1.マルチ発信元ＦＡＸ番号の登録を行う
		2.マルチ発信元ＦＡＸ番号は２０桁以内
	]
	return		:[
				OK:登録完了
				NG:登録中止
				]
	common		:[
					CharacterInput
					SYB_Multi_ID_Buffer[i-1]
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/03/29]
	author		:[藤村春夫]
*************************************************************************/
UBYTE	Multi_TTI_FaxNumberInput(UBYTE i)
{
	UBYTE	key;			/* ｷｰ取り込みﾃﾞｰﾀ     */

	/** 初期化 */
	ClearCharacterInput();
	CMN_StringCopy(CharacterInput.Buffer, SYB_Multi_ID_Buffer[i-1]);
	CharacterInput.MaxFigure = SYS_ID_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

	/** データ入力 */
	while (1) {

		/** 下段に登録状況を表示 */
		DisplayNumberInput();

		/** キー取り込み */
		key = NumberInputKeyGet();

		switch (key) {
		case STOP_KEY:			/* ストップキー */
			/* 終了 */
			CursorOff();
			return (NG);
		case SET_KEY:			/* セットキー	*/
			/* 終了 */
			CursorOff();
			return (OK);
		case DIAL_MARK_KEY:		/* ダイアル記号キー */
			/* バッファの先頭なら＋、それ以外の場合ーをセットする */
			if ((CharacterInput.Buffer[0] == NULL) || (CharacterInput.CursorPosition == 0)) {
				if (CharacterInput.Buffer[0] == '+') {
					NackBuzzer();
					break;
				}
				else {
					key = '+';
				}
			}
			else {
				key = '-';
			}
			CharacterDataSet_FigureCheck(key);
			break;
		case OPR_NO_KEY:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[マルチ発信元名入力]
	function	:[
		1.マルチ発信元名の登録を行う。
		2.マルチ発信元名は２２桁以内
	]
	return		:[]
	common		:[
		CharacterInput
		SYB_Multi_TTI_Buffer[i-1]
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/03/29]
	author		:[藤村春夫]
*************************************************************************/
UBYTE	Multi_TTI_NameInput(UBYTE i)
{
	ClearCharacterInput();
	SetCharacterInputMode();	/* 文字入力モード初期化 */
	/* 前回入力値を名前入力用バッファに展開する */
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/09/27 */
	OPR_SetRegisteredDataToBuf(CharacterInput.Buffer, SYB_Multi_TTI_Buffer[i-1], 0);	/* 前回登録データをセット */
 #else
	SetCharacterInputBuf(SYB_Multi_TTI_Buffer[i-1]);
 #endif
	CharacterInput.MaxFigure = SYS_TTI_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_ENABLE)) {
		return(OK);
	}
	else {
		return(NG);
	}
#else 
	return (NameInput(OPR_KANJI_ENABLE));
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[マルチ発信元名（カナＩＤ）入力]
	function	:[
		1.マルチ発信元名（カナＩＤ）の登録を行う
		2.マルチ発信元名は１６文字以内
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/03/29]
	author		:[藤村春夫]
*************************************************************************/
#if (PRO_JIS_CODE == ENABLE)
UBYTE	Multi_TTI_ID_NameInput(UBYTE i)
{
	ClearCharacterInput();
	SetCharacterInputMode();	/* 文字入力モード初期化 */
	CMN_StringCopy(CharacterInput.Buffer, SYB_Multi_TTI_ID_Buffer[i-1]);
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;
	CharacterInput.MaxFigure = SYS_TTI_ID_MAX - 1;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_DISABLE)) {
		return(OK);
	}
	else {
		return(NG);
	}
#else
	return (NameInput(OPR_KANJI_DISABLE));
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}
#endif

#endif	/* (PRO_MULTI_TTI == ENABLE) */

#if defined (KEISATSU) /* 警察FAX Added by SMuratec K.W.Q 2005/06/02 */
/*************************************************************************
	module		:[回線のデフォルトを選択]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2005/06/07]
	author		:[SMuratec Kan]
*************************************************************************/
UBYTE SetDefaultLine(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	parasw;

	ClearDisplayHigh();
	ClearDisplayLow();

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_DefaultLine);	/* "ﾕｳｾﾝ ｶｲｾﾝ      :" */

	if (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_LINE_HOJI) {
		DisplayStringHigh(15, D2W_Hoji);
		parasw = 2;
	}
	else {
		switch (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_LINE_KANYU){
		case DEFAULT_LINE_KEIDEN:
			DisplayStringHigh(15, D2W_Keiden);
			parasw = 0;
			break;
		case DEFAULT_LINE_KANYU:
			DisplayStringHigh(15, D2W_Kanyu);
			parasw = 1;
			break;
		default :
			DisplayStringHigh(15, D2W_Keiden);
			parasw = 0;
			break;
		}
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
			parasw++;
			if (parasw == 3)
			{
				parasw = 0;
			}
			
			switch(parasw){
			case 0:
				DisplayStringHigh(15, D2W_Keiden);
				break;
			case 1:
				DisplayStringHigh(15, D2W_Kanyu);
				break;
			case 2:
				DisplayStringHigh(15, D2W_Hoji);
				break;
			default:
				DisplayStringHigh(15, D2W_Keiden);
				break;
			}
			break;
		case LEFT_ARROW:	/* 左矢印キー */
			if (parasw == 0)
			{
				parasw = 3;
			}
			parasw--;
			
			switch(parasw){
			case 0:
				DisplayStringHigh(15, D2W_Keiden);
				break;
			case 1:
				DisplayStringHigh(15, D2W_Kanyu);
				break;
			case 2:
				DisplayStringHigh(15, D2W_Hoji);
				break;
			default:
				DisplayStringHigh(15, D2W_Keiden);
				break;
			}
			break;
		case ENTER:
/* 警察FAX DVT_ID4 Modify by SMuratec K.W.Q 2005/10/28 */
#if (0)
			SYB_MachineParameter[M_PARA_SW_I0] &= ~DEFAULT_LINE_MASK;
			
			switch(parasw)
			{
			case 0:
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_LINE_KEIDEN;
				break;
			case 1:
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_LINE_KANYU;
				break;
				
			case 2:
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_LINE_HOJI;
				break;
			default:
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_LINE_KEIDEN;
				break;
			}
#else
			switch(parasw)
			{
			case 0:
				SYB_MachineParameter[M_PARA_SW_I0] &= ~DEFAULT_LINE_MASK;
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_LINE_KEIDEN;
				break;
			case 1:
				SYB_MachineParameter[M_PARA_SW_I0] &= ~DEFAULT_LINE_MASK;
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_LINE_KANYU;
				break;
				
			case 2:
#if 0	/* 警察FAX DVT_ID84 Deleted by SMuratec 夏 2005/01/12 */			
				SYB_MachineParameter[M_PARA_SW_I0] &= ~DEFAULT_LINE_MASK; /* 追加 06/01/11 石橋正和 */
#endif
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_LINE_HOJI;
				break;
			default:
				SYB_MachineParameter[M_PARA_SW_I0] &= ~DEFAULT_LINE_MASK;
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_LINE_KEIDEN;
				break;
			}
#endif

#if (0)		/* 警察FAX DVT_ID29 Modify by SMuratec K.W.Q 2005/11/09 */
			AttributeTimeoutCheck = 1;
#else
			AttributeTimeoutCheck = 1;

			/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/29 */
			if ((CHK_NumberDisplayON() && (SYS_RingCounter == 0) && (RingStatus & CI_STD_LINE))
				|| (NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))
				|| (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_ND_DISPLAY)) { /* ナンバーディスプレイ起動している場合 */
				return (OK);
			}
			else 
			if (AttributeTimeoutCheck &&
				(!(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_HOOK_KEY_OFF_HOOK) && 
				!(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_STD_OFFHOOK) &&
				!(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_EXT_OFFHOOK))) {

				SetKeisatsuSettings();
				AttributeTimeoutCheck = 0;
				NCU_HdstShift();
			}
#endif
			return (OK);
		case STOP:
		case KEY_TIME_UP:
			return (NG);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}

UBYTE SetDefaultCOMMethod(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	parasw;

	ClearDisplayHigh();
	ClearDisplayLow();
	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_DefaultCOMMethod);	/* "ﾕｳｾﾝ ﾎｳｼｷ      :" */
	
	if (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_COM_METHOD_HOJI) {
		DisplayStringHigh(15, D2W_Hoji);
		parasw = 2;
	}
	else {
		switch (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_COM_METHOD_KOBETSU){
		case DEFAULT_COM_METHOD_ISSEI:
			DisplayStringHigh(15, D2W_Issei);
			parasw = 0;
			break;
		case DEFAULT_COM_METHOD_KOBETSU:
			DisplayStringHigh(15, D2W_Kobetsu);
			parasw = 1;
			break;
		default :
			DisplayStringHigh(15, D2W_Issei);
			parasw = 0;
			break;
		}
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
			parasw++;
			if (parasw == 3)
			{
				parasw = 0;
			}
			
			switch(parasw){
			case 0:
				DisplayStringHigh(15, D2W_Issei);
				break;
			case 1:
				DisplayStringHigh(15, D2W_Kobetsu);
				break;
			case 2:
				DisplayStringHigh(15, D2W_Hoji);
				break;
			default:
				DisplayStringHigh(15, D2W_Issei);
				break;
			}
			break;
		case LEFT_ARROW:	/* 左矢印キー */
			if (parasw == 0)
			{
				parasw = 3;
			}
			parasw--;
			
			switch(parasw){
			case 0:
				DisplayStringHigh(15, D2W_Issei);
				break;
			case 1:
				DisplayStringHigh(15, D2W_Kobetsu);
				break;
			case 2:
				DisplayStringHigh(15, D2W_Hoji);
				break;
			default:
				DisplayStringHigh(15, D2W_Issei);
				break;
			}
			break;
		case ENTER:
/* 警察FAX DVT_ID4 Modify by SMuratec K.W.Q 2005/10/28 */
#if (0)
			SYB_MachineParameter[M_PARA_SW_I0] &= ~DEFAULT_COM_METHOD_MASK;
			
			switch(parasw)
			{
			case 0:
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_COM_METHOD_ISSEI;
				break;
			case 1:
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_COM_METHOD_KOBETSU;
				break;
				
			case 2:
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_COM_METHOD_HOJI;
				break;
			default:
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_COM_METHOD_ISSEI;
				break;
			}
#else
			switch(parasw)
			{
			case 0:
				SYB_MachineParameter[M_PARA_SW_I0] &= ~DEFAULT_COM_METHOD_MASK;
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_COM_METHOD_ISSEI;
				break;
			case 1:
				SYB_MachineParameter[M_PARA_SW_I0] &= ~DEFAULT_COM_METHOD_MASK;
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_COM_METHOD_KOBETSU;
				break;
				
			case 2:
#if 0	/* 警察FAX DVT_ID84 Deleted by SMuratec 夏 2005/01/12 */			
				SYB_MachineParameter[M_PARA_SW_I0] &= ~DEFAULT_COM_METHOD_MASK; /* 追加 06/01/11 石橋正和 */
#endif
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_COM_METHOD_HOJI;
				break;
			default:
				SYB_MachineParameter[M_PARA_SW_I0] &= ~DEFAULT_COM_METHOD_MASK;
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_COM_METHOD_ISSEI;
				break;
			}
#endif

#if (0)		/* 警察FAX DVT_ID30 Modify by SMuratec K.W.Q 2005/11/09 */
			AttributeTimeoutCheck = 1;
#else
			if (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_COM_METHOD_KOBETSU){
				SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_MODE;
			}
			else{
				SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_MODE;
			}
#endif

			return (OK);
		case STOP:
		case KEY_TIME_UP:
			return (NG);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}

UBYTE SetKeidenScramleOn(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	parasw;

	ClearDisplayHigh();
	ClearDisplayLow();

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_KeidenScramleOn);		/* "ｹｲﾃﾞﾝ S ﾕｳｾﾝ   :" */

	if (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_KEIDEN_SCRAMLE_ON) {
		DisplayStringHigh(15, D2W_On);  
		parasw = TRUE;					 
	}
	else {
		DisplayStringHigh(15, D2W_Off);   
		parasw = FALSE;					 
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
		case LEFT_ARROW:	/* 左矢印キー */
			if (parasw) {
				DisplayStringHigh(15, D2W_Off);
				parasw = FALSE;
			}
			else {
				DisplayStringHigh(15, D2W_On);
				parasw = TRUE;
			}
			break;
		case ENTER:
			if(parasw){
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_KEIDEN_SCRAMLE_ON;
			}
			else{
				SYB_MachineParameter[M_PARA_SW_I0] &= ~DEFAULT_KEIDEN_SCRAMLE_ON;
			}
			
#if (0)		/* 警察FAX DVT_ID31 Modify by SMuratec K.W.Q 2005/11/09 */
			AttributeTimeoutCheck = 1;
#else
			if (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_KEIDEN_SCRAMLE_ON){
				SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SCRAMBLE_KEIDEN;
			}
			else{
				SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_SCRAMBLE_KEIDEN;
			}
#endif

			return (OK);
		case STOP:
		case KEY_TIME_UP:
			return (NG);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}

UBYTE SetKanyuScramleOn(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	parasw;

	ClearDisplayHigh();
	ClearDisplayLow();

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_KanyuScramleOn);		/* "ｶﾆｭｳ S ﾕｳｾﾝ    :" */
	
	if (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_KANYU_SCRAMLE_ON) {
		DisplayStringHigh(15, D2W_On);  
		parasw = TRUE;					 
	}
	else {
		DisplayStringHigh(15, D2W_Off);   
		parasw = FALSE;					 
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
		case LEFT_ARROW:	/* 左矢印キー */
			if (parasw) {
				DisplayStringHigh(15, D2W_Off);
				parasw = FALSE;
			}
			else {
				DisplayStringHigh(15, D2W_On);
				parasw = TRUE;
			}
			break;
		case ENTER:
			if(parasw){
				SYB_MachineParameter[M_PARA_SW_I0] |= DEFAULT_KANYU_SCRAMLE_ON;
			}
			else{
				SYB_MachineParameter[M_PARA_SW_I0] &= ~DEFAULT_KANYU_SCRAMLE_ON;
			}
			
#if (0)		/* 警察FAX DVT_ID32 Modify by SMuratec K.W.Q 2005/11/09 */
			AttributeTimeoutCheck = 1;
#else
			if (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_KANYU_SCRAMLE_ON){
				SYB_SettingStatus[SETTING_STATUS_31] &= ~SETTING_SCRAMBLE_KANYU;
			}
			else{
				SYB_SettingStatus[SETTING_STATUS_31] |= SETTING_SCRAMBLE_KANYU;
			}
#endif

			return (OK);
		case STOP:
		case KEY_TIME_UP:
			return (NG);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}
#endif		/* End of (defined (KEISATSU)) */
