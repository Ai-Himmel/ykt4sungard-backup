/************************************************************************
*	System		: HINOKI
*	File Name	: OPR_ND.C
*	Author		: 藤村春夫
*	Date		: 1999/01/07
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ナンバーディスプレイオペレーション
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysonet.h"
#include	"\src\atlanta\define\sysspeed.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\memsw\define\mem_sw_b.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\ini_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#include	"\src\atlanta\define\country.h"
#include	"\src\atlanta\define\param.h"

#include	"\src\atlanta\define\stng_pro.h"

#include	"\src\atlanta\ext_v\cmn_tbl.h"

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
/*************************************************************************
	module		:[ナンバーディスプレイ登録オペレーション]
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
	date		:[1999/01/07]
	author		:[藤村春夫]
*************************************************************************/
void	EnterNumberDisplay(void)
{
	UBYTE	set_cnt;	/* ナンバーディスプレイ登録数 */
	UBYTE	is_new;		/* 新規/上書き入力 */

	/* セット番号の初期化 */
	OPR_Buf.ND_Ctrl.SelectNumber = 0;

	/* ナンバーディスプレイ登録数取得 */
	set_cnt = Get_ND_Count();

	while (1) {
		if (set_cnt > 0) {
			/* ナンバーディスプレイ登録番号の選択 */
			if (ND_SelectNumber(set_cnt) == OPR_END) {
				return;
			}
		}
		if (SYB_NumberDisplay[OPR_Buf.ND_Ctrl.SelectNumber].Dial[0] == NULL) {	/* 未登録 */
			is_new = TRUE;	/* 新規入力 */
		}
		else {	/* 登録済 */
			is_new = FALSE;	/* 上書き入力 */
		}
		while (1) {
			/* ナンバーディスプレイデータの登録 */
			CMN_MemorySet(OPR_Buf.ND_Ctrl.DisplayBuffer, (UWORD)(ND_FIGURE_MAX + 2), NULL);
			CMN_UnsignedIntToASC(OPR_Buf.ND_Ctrl.DisplayBuffer,
								 OPR_Buf.ND_Ctrl.SelectNumber + OPR_ND_MIN,
								 ND_FIGURE_MAX,
								 '0');
			OPR_Buf.ND_Ctrl.DisplayBuffer[ND_FIGURE_MAX] = ':';
			if (ND_Input(&SYB_NumberDisplay[OPR_Buf.ND_Ctrl.SelectNumber],
						 OPR_Buf.ND_Ctrl.DisplayBuffer) == OPR_END) {
				return;
			}
			if (SYB_NumberDisplay[OPR_Buf.ND_Ctrl.SelectNumber].Dial[0] == NULL) {	/* 未登録 */
				/* ナンバーディスプレイデータを詰める */
				Shift_ND_Data();
				break;
			}
			/* ナンバーディスプレイ登録番号を進める */
			if (OPR_Buf.ND_Ctrl.SelectNumber == (UBYTE)(SYS_ND_MAX - 1)) {
				OPR_Buf.ND_Ctrl.SelectNumber = 0;
			}
			else {
				OPR_Buf.ND_Ctrl.SelectNumber++;
			}
			if (is_new == FALSE) {	/* 上書き入力 */
				break;
			}
		}
		if (is_new == TRUE) {	/* 新規入力 */
			OPR_Buf.ND_Ctrl.SelectNumber = 0;
		}
		/* ナンバーディスプレイ登録数取得 */
		set_cnt = Get_ND_Count();
		if (set_cnt == 0) {
			return;
		}
	}
}

/*************************************************************************
	module		:[ナンバーディスプレイ登録番号の選択]
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
	date		:[1999/01/07]
	author		:[藤村春夫]
*************************************************************************/
UBYTE	ND_SelectNumber(UBYTE set_cnt)	/* ナンバーディスプレイ登録数 */
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	set_no;

	/* 数字入力作業用バッファクリア */
	ClearCharacterInput();

	while (1) {
		/* ナンバーディスプレイ登録番号選択中の表示 */
		Display_ND_SelectNumber();

		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case KEY_TIME_UP:
		case STOP:
			return (OPR_END);	/* 終了 */
		case ENTER:
			/* ナンバーディスプレイ登録番号入力中 */
			if (CharacterInput.CursorPosition > 0) {
				NackBuzzer();
			}
			else {
				return (OPR_CONTINUE);
			}
			break;
		case FUNCTION:
			/* ナンバーディスプレイ登録番号入力中 */
			if (CharacterInput.CursorPosition > 0) {
				NackBuzzer();
			}
			else {
				/* ナンバーディスプレイ登録番号を進める */
				if (OPR_Buf.ND_Ctrl.SelectNumber == set_cnt) {
					OPR_Buf.ND_Ctrl.SelectNumber = 0;
				}
				else {
					if (OPR_Buf.ND_Ctrl.SelectNumber == (UBYTE)(SYS_ND_MAX - 1)) {
						OPR_Buf.ND_Ctrl.SelectNumber = 0;
					}
					else {
						OPR_Buf.ND_Ctrl.SelectNumber++;
					}
				}
			}
			break;
		case LEFT_ARROW:
			/* ナンバーディスプレイ登録番号入力中 */
			if (CharacterInput.CursorPosition > 0) {
				NackBuzzer();
			}
			else {
				/* ナンバーディスプレイ登録番号を戻す */
				if (OPR_Buf.ND_Ctrl.SelectNumber == 0) {
					if (set_cnt == SYS_ND_MAX) {
						OPR_Buf.ND_Ctrl.SelectNumber = (UBYTE)(SYS_ND_MAX - 1);
					}
					else {
						OPR_Buf.ND_Ctrl.SelectNumber = set_cnt;
					}
				}
				else {
					OPR_Buf.ND_Ctrl.SelectNumber--;
				}
			}
			break;
		case CLEAR:
			/* ナンバーディスプレイ登録番号入力中 */
			if (CharacterInput.CursorPosition > 0) {
				CharacterInput.CursorPosition--;
				CharacterInput.Buffer[CharacterInput.CursorPosition] = NULL;
			}
			else {
				if (SYB_NumberDisplay[OPR_Buf.ND_Ctrl.SelectNumber].Dial[0] == NULL) {	/* 未登録 */
					NackBuzzer();
					break;
				}
				/* ナンバーディスプレイデータを詰める */
				Shift_ND_Data();
				/* ナンバーディスプレイ登録数取得 */
				set_cnt = Get_ND_Count();
				if (set_cnt == 0) {
					return (OPR_CONTINUE);
				}
			}
			break;
		case NUMBER:
			CharacterInput.Buffer[CharacterInput.CursorPosition] = key;
			CharacterInput.CursorPosition++;
			if (CharacterInput.CursorPosition == ND_FIGURE_MAX) {
				set_no = (UBYTE)CMN_ASC_ToUnsignedInt(CharacterInput.Buffer, CharacterInput.CursorPosition);
				if ((UBYTE)(set_no - OPR_ND_MIN) < 0
				 || (UBYTE)(set_no - OPR_ND_MIN) > set_cnt
				 || (UBYTE)(set_no - OPR_ND_MIN) > (UBYTE)(SYS_ND_MAX - 1)) {
					NackBuzzer();
				}
				else {
					OPR_Buf.ND_Ctrl.SelectNumber = (UBYTE)(set_no - OPR_ND_MIN);
				}
				/* 数字入力作業用バッファクリア */
				ClearCharacterInput();
			}
			break;
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[ナンバーディスプレイ登録番号選択中の表示]
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
	date		:[1999/01/07]
	author		:[藤村春夫]
*************************************************************************/
UBYTE	Display_ND_SelectNumber(void)
{
	/* 上段表示「ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ 」*/
	/* 下段表示「01:ｾｯﾄ ｻﾚﾃｲﾏｾﾝ      」*/

	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	CMN_StringCopy(FunctionDisplayBufferHigh, D2W_ND_SelectNumber);	/* "ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ " */

	/* ナンバーディスプレイ登録番号入力中 */
	if (CharacterInput.CursorPosition > 0) {
		CMN_StringCopy(FunctionDisplayBufferLow, CharacterInput.Buffer);
	}
	else {
		CMN_MemorySet(OPR_Buf.ND_Ctrl.DisplayBuffer, (UWORD)(ND_FIGURE_MAX + 2), NULL);
		CMN_UnsignedIntToASC(OPR_Buf.ND_Ctrl.DisplayBuffer,
							 OPR_Buf.ND_Ctrl.SelectNumber + OPR_ND_MIN,
							 ND_FIGURE_MAX,
							 '0');
		OPR_Buf.ND_Ctrl.DisplayBuffer[ND_FIGURE_MAX] = ':';
		CMN_StringCopy(FunctionDisplayBufferLow, OPR_Buf.ND_Ctrl.DisplayBuffer);
#if (0)	/* 未登録の場合、"ｾｯﾄ ｻﾚﾃｲﾏｾﾝ"を表示します。By H.Fujimura 1999/02/09 */
//		if (SYB_NumberDisplay[OPR_Buf.ND_Ctrl.SelectNumber].Dial[0] != NULL) {	/* 登録済 */
//			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[ND_FIGURE_MAX + 1],
//									 &SYB_NumberDisplay[OPR_Buf.ND_Ctrl.SelectNumber].Dial[0],
//									 (UBYTE)(OPR_DISPLAY_MAX - (ND_FIGURE_MAX + 1)));
//		}
#else
		if (SYB_NumberDisplay[OPR_Buf.ND_Ctrl.SelectNumber].Dial[0] == NULL) {	/* 未登録 */
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[ND_FIGURE_MAX + 1],
									 D2W_NoNumberStored,
									 (UBYTE)(OPR_DISPLAY_MAX - (ND_FIGURE_MAX + 1)));
		}
		else {	/* 登録済 */
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[ND_FIGURE_MAX + 1],
									 &SYB_NumberDisplay[OPR_Buf.ND_Ctrl.SelectNumber].Dial[0],
									 (UBYTE)(OPR_DISPLAY_MAX - (ND_FIGURE_MAX + 1)));
		}
#endif
	}

	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	DisplayStringLow(0, FunctionDisplayBufferLow);
}

/*************************************************************************
	module		:[ナンバーディスプレイデータの登録]
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
	date		:[1999/01/07]
	author		:[藤村春夫]
*************************************************************************/
UBYTE	ND_Input(struct SYS_NumberDisplayTable *NumberDisplay, UBYTE *DisplayBuffer)
{
	UBYTE	position;

	position = CMN_StringLength(DisplayBuffer);

	if (NumberDisplay->Dial[0] == NULL) {	/* 未登録 */
		/* ナンバーディスプレイデータの初期化 */
		Clear_ND_Data(NumberDisplay);
	}

	/*--------------*/
	/* ダイヤル番号 */
	/*--------------*/
	/* 上段表示「01:ﾀﾞｲﾔﾙ ﾊﾞﾝｺﾞｳ     」*/
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, DisplayBuffer);
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[position],
							 D2W_FaxNumber,
							 (UBYTE)(OPR_DISPLAY_MAX - position));
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	/* ダイヤル番号入力 */
	if (ND_DialNumberInput(&NumberDisplay->Dial[0]) == NG) {
		return (OPR_END);	/* 終了 */
	}

	/* 文字入力で登録されたデータを格納 */
	StoreCharacterInputValue(&NumberDisplay->Dial[0], ASC_DATA_TYPE);

	if (NumberDisplay->Dial[0] == NULL) {	/* 未登録 */
		/* ナンバーディスプレイデータの初期化 */
		Clear_ND_Data(NumberDisplay);
		return (OPR_CONTINUE);
	}

	/*----------*/
	/* 相手先名 */
	/*----------*/
	/* 上段表示「01:ｱｲﾃｻｷﾒｲ          」*/
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, DisplayBuffer);
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[position],
							 D2W_RemoteName,
							 (UBYTE)(OPR_DISPLAY_MAX - position));
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	/* 相手先名入力 */
	if (DialNameInput(&NumberDisplay->Name[0]) == NG) {
		return (OPR_END);	/* 終了 */
	}

	/* 文字入力で登録されたデータを格納 */
	StoreCharacterInputValue(&NumberDisplay->Name[0], ASC_DATA_TYPE);

#if (PRO_RX_DOC_TRANSFER == ENABLE) && (!defined (KEISATSU))	/* Add By H.Fujimura 1999/01/07 */
	/*--------------------------*/
	/* ＦＡＸワープデータの登録 */
	/*--------------------------*/
	if (WarpInput(&NumberDisplay->WarpData, DisplayBuffer) == OPR_END) {
		return (OPR_END);	/* 終了 */
	}
#endif

	return (OPR_CONTINUE);
}

/*************************************************************************
	module		:[ナンバーディスプレイデータ（ダイヤル番号）の入力]
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
	date		:[1999/01/07]
	author		:[藤村春夫]
*************************************************************************/
UBYTE	ND_DialNumberInput(UBYTE *stored_data)	/* 登録済みデータ */
{
	UBYTE	key;			/* ｷｰ取り込みﾃﾞｰﾀ     */

	/** 初期化 */
	ClearCharacterInput();
	CMN_StringCopy(CharacterInput.Buffer, stored_data);
	CharacterInput.MaxFigure = SYS_DIRECT_DIAL_MAX - 1;
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
			CharacterDataSet_FigureCheck('-');
			break;
		case TEN_AST_KEY:		/* * */
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
	module		:[ナンバーディスプレイ登録数取得]
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
	date		:[1999/01/07]
	author		:[藤村春夫]
*************************************************************************/
UBYTE	Get_ND_Count(void)
{
	UBYTE	i;

	for (i = 0; i < SYS_ND_MAX; i++) {
		if (SYB_NumberDisplay[i].Dial[0] == NULL) {	/* 未登録 */
			break;
		}
	}
	return(i);
}

/*************************************************************************
	module		:[ナンバーディスプレイデータを詰める]
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
	date		:[1999/01/07]
	author		:[藤村春夫]
*************************************************************************/
void	Shift_ND_Data(void)
{
	UBYTE	loop;
	UBYTE	i;

	for (loop = OPR_Buf.ND_Ctrl.SelectNumber; loop < (UBYTE)(SYS_ND_MAX - 1); loop++) {
		CMN_StringCopyNum( (UBYTE *)&SYB_NumberDisplay[loop].Dial[0], 
						   (UBYTE *)&SYB_NumberDisplay[loop+1].Dial[0], 
						   SYS_DIRECT_DIAL_MAX );
		CMN_StringCopyNum( (UBYTE *)&SYB_NumberDisplay[loop].Name[0], 
						   (UBYTE *)&SYB_NumberDisplay[loop+1].Name[0], 
						   SYS_DIAL_NAME_MAX );
		SYB_NumberDisplay[loop].WarpData.Status		= SYB_NumberDisplay[loop+1].WarpData.Status;
		for (i = 0; i < SYS_TEL_2DIGIT_MAX; i++) {
			SYB_NumberDisplay[loop].WarpData.Direct[i] = SYB_NumberDisplay[loop+1].WarpData.Direct[i];
		}
		for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
			SYB_NumberDisplay[loop].WarpData.Onetouch[i] = SYB_NumberDisplay[loop+1].WarpData.Onetouch[i];
		}
		for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
			SYB_NumberDisplay[loop].WarpData.Speed[i] = SYB_NumberDisplay[loop+1].WarpData.Speed[i];
		}
		SYB_NumberDisplay[loop].WarpData.Group		= SYB_NumberDisplay[loop+1].WarpData.Group;
		SYB_NumberDisplay[loop].WarpData.StartWeek	= SYB_NumberDisplay[loop+1].WarpData.StartWeek;
		SYB_NumberDisplay[loop].WarpData.EndWeek	= SYB_NumberDisplay[loop+1].WarpData.EndWeek;
		SYB_NumberDisplay[loop].WarpData.StartTime	= SYB_NumberDisplay[loop+1].WarpData.StartTime;
		SYB_NumberDisplay[loop].WarpData.EndTime	= SYB_NumberDisplay[loop+1].WarpData.EndTime;
		SYB_NumberDisplay[loop].WarpData.Option		= SYB_NumberDisplay[loop+1].WarpData.Option;
	}
	if (loop == (UBYTE)(SYS_ND_MAX - 1)) {
		/* ナンバーディスプレイデータの初期化 */
		Clear_ND_Data(&SYB_NumberDisplay[loop]);
	}
}

/*************************************************************************
	module		:[ナンバーディスプレイデータの初期化]
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
	date		:[1999/01/07]
	author		:[藤村春夫]
*************************************************************************/
void	Clear_ND_Data(struct SYS_NumberDisplayTable *NumberDisplay)
{
	NumberDisplay->Dial[0]			= '\0';
	NumberDisplay->Name[0]			= '\0';
	NumberDisplay->WarpData.Status	= SYS_WARP_EMPTY;	/* 未登録 */
}

/*************************************************************************
	module		:[ナンバーディスプレイリストオペレーション]
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
	date		:[1999/01/07]
	author		:[藤村春夫]
*************************************************************************/
void	PrintNumberDisplayList(void)
{
	UBYTE	i;

	for (i = 0; i < SYS_ND_MAX; i++) {
		if (SYB_NumberDisplay[i].Dial[0] != NULL) {	/* 登録済 */
			/* リストプリント起動メッセージ送信 */
			FinalListPrintOperation(LST_ND_LIST);
			return;
		}
	}
	NackBuzzer();
	OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
}

/*************************************************************************
	module		:[ナンバーディスプレイ設定オペレーション]
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
	date		:[1999/01/07]
	author		:[藤村春夫]
*************************************************************************/
void	SetNumberDisplay(void)
{
	/* 電話機接続設定 */
	if (EnterSettingStatus(D2W_ND_TelMode[0],				/* "ﾃﾞﾝﾜｷ ｾﾂｿﾞｸ:\0       " */
						   D2W_ND_TelMode[1],				/* "               OFF  " */
						   2,
						   SETTING_STATUS_30,
						   OPR_VALID_CHECK_NOT_NEED,
						   ND_TEL2_ND_ON) == NG) {
		return;
	}

	/* ナンバーディスプレイＯＮ／ＯＦＦ切り替え */
	if (EnterSettingStatus(D2W_SetNumberDisplay,			/* "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ:\0     " */
						   D2W_Off2,						/* "                OFF " */
						   2,
						   SETTING_STATUS_30,
						   OPR_VALID_CHECK_NOT_NEED,
						   ND_MODE_ON) == NG) {
		return;
	}
#if !defined (KEISATSU) /* 警察FAX 05/05/07 石橋正和 */
	else {
		/* 停電時ダイヤルインＣＰＵにＮＤ設定を通知 T.Nose 1998/11/20 */
		if (CHK_NumberDisplayON()) {
			SetDICPU_Disable();	/* ナンバーディスプレイＯＮ */
		}
		else {
			SetDICPU_Enable();	/* ナンバーディスプレイＯＦＦ */
		}
	}
#endif

#if (PRO_NUMBER_DISPLAY_WARP == ENABLE) && (!defined (KEISATSU))	/* Add By H.Fujimura 1999/01/07 */
	/* ＮＤワープＯＮ／ＯＦＦ切り替え */
	if (EnterSettingStatus(D2W_Set_ND_Warp,					/* "NDﾜｰﾌﾟ:\0            " */
						   D2W_Off2,						/* "                OFF " */
						   2,
						   SETTING_STATUS_30,
						   OPR_VALID_CHECK_NOT_NEED,
						   ND_WARP_ON) == NG) {
		return;
	}
#endif

	ChildDisplaySetCompleted(D2W_EnterNumberDisplay);	/* "ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ｾｯﾄ   " */
}
#endif	/* (PRO_NUMBER_DISPLAY == ENABLE) */
