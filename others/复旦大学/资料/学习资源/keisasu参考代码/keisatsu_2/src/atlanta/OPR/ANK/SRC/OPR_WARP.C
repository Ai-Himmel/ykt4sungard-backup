/************************************************************************
*	System		: HINOKI
*	File Name	: OPR_WARP.C
*	Author		: 藤村春夫
*	Date		: 1999/01/07
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ＦＡＸワープオペレーション
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

#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
/*************************************************************************
	module		:[ＦＡＸワープ登録オペレーション]
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
void	EnterFaxWarp(void)
{
	UBYTE	set_cnt;	/* ＦＡＸワープ登録数 */
	UBYTE	is_new;		/* 新規/上書き入力 */

	/* セット番号の初期化 */
	OPR_Buf.WarpCtrl.SelectNumber = 0;

	/* ＦＡＸワープ登録数取得 */
	set_cnt = GetWarpCount();

	while (1) {
		if (set_cnt > 0) {
			/* ＦＡＸワープ登録番号の選択 */
			if (WarpSelectNumber(set_cnt) == OPR_END) {
				return;
			}
		}
		if (SYB_WarpFile[OPR_Buf.WarpCtrl.SelectNumber].Status == SYS_WARP_EMPTY) {	/* 未登録 */
			is_new = TRUE;	/* 新規入力 */
		}
		else {	/* 登録済 */
			is_new = FALSE;	/* 上書き入力 */
		}
		while (1) {
			/* ＦＡＸワープデータの登録 */
			CMN_MemorySet(OPR_Buf.WarpCtrl.DisplayBuffer, (UWORD)(WARP_FIGURE_MAX + 2), NULL);
			CMN_UnsignedIntToASC(OPR_Buf.WarpCtrl.DisplayBuffer,
								 OPR_Buf.WarpCtrl.SelectNumber + OPR_WARP_MIN,
								 WARP_FIGURE_MAX,
								 '0');
			OPR_Buf.WarpCtrl.DisplayBuffer[WARP_FIGURE_MAX] = ':';
			if (WarpInput(&SYB_WarpFile[OPR_Buf.WarpCtrl.SelectNumber],
						  OPR_Buf.WarpCtrl.DisplayBuffer) == OPR_END) {
				return;
			}
			if (SYB_WarpFile[OPR_Buf.WarpCtrl.SelectNumber].Status == SYS_WARP_EMPTY) {	/* 未登録 */
				/* ＦＡＸワープデータを詰める */
				ShiftWarpData();
				break;
			}
			/* ＦＡＸワープ登録番号を進める */
			if (OPR_Buf.WarpCtrl.SelectNumber == (UBYTE)(SYS_WARP_MAX - 1)) {
				OPR_Buf.WarpCtrl.SelectNumber = 0;
			}
			else {
				OPR_Buf.WarpCtrl.SelectNumber++;
			}
			if (is_new == FALSE) {	/* 上書き入力 */
				break;
			}
		}
		if (is_new == TRUE) {	/* 新規入力 */
			OPR_Buf.WarpCtrl.SelectNumber = 0;
		}
		/* ＦＡＸワープ登録数取得 */
		set_cnt = GetWarpCount();
		if (set_cnt == 0) {
			return;
		}
	}
}

/*************************************************************************
	module		:[ＦＡＸワープ登録番号の選択]
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
UBYTE	WarpSelectNumber(UBYTE set_cnt)	/* ＦＡＸワープ登録数 */
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	set_no;

	/* 数字入力作業用バッファクリア */
	ClearCharacterInput();

	while (1) {
		/* ＦＡＸワープ登録番号選択中の表示 */
		DisplayWarpSelectNumber();

		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case KEY_TIME_UP:
		case STOP:
			return (OPR_END);	/* 終了 */
		case ENTER:
			/* ＦＡＸワープ登録番号入力中 */
			if (CharacterInput.CursorPosition > 0) {
				NackBuzzer();
			}
			else {
				return (OPR_CONTINUE);
			}
			break;
		case FUNCTION:
			/* ＦＡＸワープ登録番号入力中 */
			if (CharacterInput.CursorPosition > 0) {
				NackBuzzer();
			}
			else {
				/* ＦＡＸワープ登録番号を進める */
				if (OPR_Buf.WarpCtrl.SelectNumber == set_cnt) {
					OPR_Buf.WarpCtrl.SelectNumber = 0;
				}
				else {
					if (OPR_Buf.WarpCtrl.SelectNumber == (UBYTE)(SYS_WARP_MAX - 1)) {
						OPR_Buf.WarpCtrl.SelectNumber = 0;
					}
					else {
						OPR_Buf.WarpCtrl.SelectNumber++;
					}
				}
			}
			break;
		case LEFT_ARROW:
			/* ＦＡＸワープ登録番号入力中 */
			if (CharacterInput.CursorPosition > 0) {
				NackBuzzer();
			}
			else {
				/* ＦＡＸワープ登録番号を戻す */
				if (OPR_Buf.WarpCtrl.SelectNumber == 0) {
					if (set_cnt == SYS_WARP_MAX) {
						OPR_Buf.WarpCtrl.SelectNumber = (UBYTE)(SYS_WARP_MAX - 1);
					}
					else {
						OPR_Buf.WarpCtrl.SelectNumber = set_cnt;
					}
				}
				else {
					OPR_Buf.WarpCtrl.SelectNumber--;
				}
			}
			break;
		case CLEAR:
			/* ＦＡＸワープ登録番号入力中 */
			if (CharacterInput.CursorPosition > 0) {
				CharacterInput.CursorPosition--;
				CharacterInput.Buffer[CharacterInput.CursorPosition] = NULL;
			}
			else {
				if (SYB_WarpFile[OPR_Buf.WarpCtrl.SelectNumber].Status == SYS_WARP_EMPTY) {	/* 未登録 */
					NackBuzzer();
					break;
				}
				/* ＦＡＸワープデータを詰める */
				ShiftWarpData();
				/* ＦＡＸワープ登録数取得 */
				set_cnt = GetWarpCount();
				if (set_cnt == 0) {
					return (OPR_CONTINUE);
				}
			}
			break;
		case NUMBER:
			CharacterInput.Buffer[CharacterInput.CursorPosition] = key;
			CharacterInput.CursorPosition++;
			if (CharacterInput.CursorPosition == WARP_FIGURE_MAX) {
				set_no = (UBYTE)CMN_ASC_ToUnsignedInt(CharacterInput.Buffer, CharacterInput.CursorPosition);
				if ((UBYTE)(set_no - OPR_WARP_MIN) < 0
				 || (UBYTE)(set_no - OPR_WARP_MIN) > set_cnt
				 || (UBYTE)(set_no - OPR_WARP_MIN) > (UBYTE)(SYS_WARP_MAX - 1)) {
					NackBuzzer();
				}
				else {
					OPR_Buf.WarpCtrl.SelectNumber = (UBYTE)(set_no - OPR_WARP_MIN);
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
	module		:[ＦＡＸワープ登録番号選択中の表示]
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
UBYTE	DisplayWarpSelectNumber(void)
{
	/* 上段表示「ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ 」*/
	/* 下段表示「1:ｾｯﾄ ｻﾚﾃｲﾏｾﾝ       」*/

	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	CMN_StringCopy(FunctionDisplayBufferHigh, D2W_WarpSelectNumber);	/* "ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ " */

	/* ＦＡＸワープ登録番号入力中 */
	if (CharacterInput.CursorPosition > 0) {
		CMN_StringCopy(FunctionDisplayBufferLow, CharacterInput.Buffer);
	}
	else {
		CMN_MemorySet(OPR_Buf.WarpCtrl.DisplayBuffer, (UWORD)(WARP_FIGURE_MAX + 2), NULL);
		CMN_UnsignedIntToASC(OPR_Buf.WarpCtrl.DisplayBuffer,
							 OPR_Buf.WarpCtrl.SelectNumber + OPR_WARP_MIN,
							 WARP_FIGURE_MAX,
							 '0');
		OPR_Buf.WarpCtrl.DisplayBuffer[WARP_FIGURE_MAX] = ':';
		CMN_StringCopy(FunctionDisplayBufferLow, OPR_Buf.WarpCtrl.DisplayBuffer);
#if (0)	/* 未登録の場合、"ｾｯﾄ ｻﾚﾃｲﾏｾﾝ"を表示します。By H.Fujimura 1999/02/09 */
//		if (SYB_WarpFile[OPR_Buf.WarpCtrl.SelectNumber].Status != SYS_WARP_EMPTY) {	/* 登録済 */
//			SetDialDataToDispBuffer2(OPR_TX_DISPLAY,
//									 SYB_WarpFile[OPR_Buf.WarpCtrl.SelectNumber].Direct,
//									 SYB_WarpFile[OPR_Buf.WarpCtrl.SelectNumber].Onetouch,
//									 SYB_WarpFile[OPR_Buf.WarpCtrl.SelectNumber].Speed,
//									 SYB_WarpFile[OPR_Buf.WarpCtrl.SelectNumber].Group,
//									 DisplayBufferLow);
//			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[WARP_FIGURE_MAX + 1],
//									 DisplayBufferLow,
//									 (UBYTE)(OPR_DISPLAY_MAX - (WARP_FIGURE_MAX + 1)));
//		}
#else
		if (SYB_WarpFile[OPR_Buf.WarpCtrl.SelectNumber].Status == SYS_WARP_EMPTY) {	/* 未登録 */
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[WARP_FIGURE_MAX + 1],
									 D2W_NoNumberStored,
									 (UBYTE)(OPR_DISPLAY_MAX - (WARP_FIGURE_MAX + 1)));
		}
		else {	/* 登録済 */
			SetDialDataToDispBuffer2(OPR_TX_DISPLAY,
									 SYB_WarpFile[OPR_Buf.WarpCtrl.SelectNumber].Direct,
									 SYB_WarpFile[OPR_Buf.WarpCtrl.SelectNumber].Onetouch,
									 SYB_WarpFile[OPR_Buf.WarpCtrl.SelectNumber].Speed,
									 SYB_WarpFile[OPR_Buf.WarpCtrl.SelectNumber].Group,
									 DisplayBufferLow);
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[WARP_FIGURE_MAX + 1],
									 DisplayBufferLow,
									 (UBYTE)(OPR_DISPLAY_MAX - (WARP_FIGURE_MAX + 1)));

 #if (PRO_PREFIX_KEY == ENABLE)	/* by K.Watanabe 2004/11/12 */
			/* プレフィックス番号展開処理 */
			ChangeDisplayBuffer(FunctionDisplayBufferLow);
 #endif
		}
#endif
	}

	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	DisplayStringLow(0, FunctionDisplayBufferLow);
}

/*************************************************************************
	module		:[ＦＡＸワープデータの登録]
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
UBYTE	WarpInput(struct SYS_SubDialData_t *WarpFile, UBYTE *DisplayBuffer)
{
	UBYTE	position;

	position = CMN_StringLength(DisplayBuffer);

	if (WarpFile->Status == SYS_WARP_EMPTY) {	/* 未登録 */
		/* ＦＡＸワープデータの初期化 */
		ClearWarpData(WarpFile);
	}

	/*----------*/
	/* 転送番号 */
	/*----------*/
	/* 上段表示「01:ﾃﾝｿｳ ﾊﾞﾝｺﾞｳ      」*/
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, DisplayBuffer);

#if (0)
** 	/* ＦＡＸワープ転送先番号用ワーディング変更 By O.Kimoto 1999/02/08 */
** 	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[position],
** 							 D2W_AltNumber,
** 							 (UBYTE)(OPR_DISPLAY_MAX - position));
#else
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[position],
							 D2W_WarpAltNumber,
							 (UBYTE)(OPR_DISPLAY_MAX - position));
#endif

	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	/* 転送番号入力 */
	if (WarpAltNumberInput(WarpFile) == NG) {
		return (OPR_END);	/* 終了 */
	}

	if (WarpFile->Status == SYS_WARP_EMPTY) {	/* 未登録 */
		/* ＦＡＸワープデータの初期化 */
		ClearWarpData(WarpFile);
		return (OPR_CONTINUE);
	}

	/*----------*/
	/* 指定時刻 */
	/*----------*/
	/* 上段表示「01:ｼﾃｲ ｼﾞｺｸ         」*/
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, DisplayBuffer);
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[position],
							 D2W_WarpTime,
							 (UBYTE)(OPR_DISPLAY_MAX - position));
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	/* 指定時刻入力 */
	if (WarpTimeInput(WarpFile) == NG) {
		return (OPR_END);	/* 終了 */
	}

	/*--------------*/
	/* 同時プリント */
	/*--------------*/
	if (SelectData(DisplayBuffer,
				   D2W_SelectWarpRxDocPrint[0],	/* "   ﾄﾞｳｼﾞ ﾌﾟﾘﾝﾄ: OFF " */
				   2,
				   &WarpFile->Option,
				   WARP_OPTION_PRINT,
				   NO_KEYTYPE) == OPR_CANCELED) {	/* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		return (OPR_END);	/* 終了 */
	}

	return (OPR_CONTINUE);
}

/*************************************************************************
	module		:[ＦＡＸワープデータ（転送番号）の入力]
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
UBYTE	WarpAltNumberInput(struct SYS_SubDialData_t *WarpFile)
{
	UBYTE	key;
	UBYTE	keytype;
	UWORD	buf_count;		/* ダイヤルデータ位置					*/
	UBYTE	direct_count;	/* 直接ダイヤル件数						*/
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/09/18 */
	UBYTE	chk_bef_key;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

	/** 初期化 */
	CommandInputInitial();		/* コマンド登録用バッファを初期化 */
	InputNumber.InputDialType = PROGRAM_DIAL_TYPE;
	SetPinCheckStatus();
	SetDialDataToDispBuffer2(OPR_PROGRAM_DISPLAY,
							 WarpFile->Direct,
							 WarpFile->Onetouch,
							 WarpFile->Speed,
							 WarpFile->Group,
							 InputNumber.Buffer);

	while (1) {
		/* 下段表示[123456789_         ] */
		if (CheckChildErrorDisplayReq() == TRUE) {	/* チャイルド表示要求有り */
			DisplayChildError();
		}
		else if (CheckChildDisplay() == FALSE) {	/* チャイルド表示中でない */
			DisplayCommandNumber();
		}

		/* キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/09/18 */
		chk_bef_key = key;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

		/* 短縮・グループキーの直後のデータ入力チェック */
		if (CheckSpeedGroupAfterEnableKey(keytype) == FALSE) {
			NackBuzzer();
			continue;
		}

#if (PRO_NEW_DIAL_OPR == ENABLE)
		/* 入力データ（短縮・グループ）の登録チェック by K.Watanabe 1998/04/02 */
		if (CheckRegistrationData(keytype) == FALSE) {
			NackBuzzer();
			continue;
		}

		/* ダイヤルデータ入力チェック by K.Watanabe 1998/03/24 */
		if (CheckInputDialData(keytype) == FALSE) {
			NackBuzzer();
			continue;
		}
#endif

#if (PRO_NEW_DIAL_OPR2 == ENABLE)
		/* 直接ダイヤル入力桁数・件数チェック by K.Watanabe 1998/04/17 */
		if (CheckInputDirectDial(keytype) == FALSE) {
			NackBuzzer();
			continue;
		}
#endif

		switch (keytype) {	/* 取り込んだキーのキー種別毎の処理 */
		case AST:			/*   *   */
		case NUMBER:		/* 0 - 9 */
		case SHARP:			/*   #   */
			InputNumberTenKeySet(key);
			break;

		case ONETOUCH:		/* ワンタッチキー入力 */
			if (CheckInputOnetouchEnable(key) == TRUE) {
				InputNumberOnetouchSet(key);
			}
			break;

		case SPEED:			/* 短縮 */
		case GROUP:			/* グループキー */
			InputNumberGroupSpeedMarkSet(key);
			break;

		case BROADCAST:		/* 同報キー */
			BroadcastMarkSet();
			break;

		case REDIAL:		/* リダイアル/ポーズキー */
			InputNumberDialMarkSet(PAUSE_MARK);
			break;

#if !defined(JPN) || (PRO_KEYPANEL == PANEL_ANZU_L)
		case FLASH:			/* フラッシュキー */
			InputNumberDialMarkSet(FLASH_MARK);
			break;
#endif

		case FUNCTION:		/* 機能キー */
			/* カーソル移動　ー＞ */
			InputNumberCursorRight();
			break;

		case LEFT_ARROW:
			/* カーソル移動　＜ー */
			InputNumberCursorLeft();
			break;

		case CLEAR:			/* クリアキー */
			/* データクリア実行 */
			InputNumberDataClear();
			break;

		case DIALMARK:		/* ダイアル記号キー */
			InputNumberDialCharacterSet();
			break;

#if (PRO_KEYPANEL == PANEL_POPLAR_L || PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/07/25 */
		case TONE:			/* トーンキー 		*/	/* 追加 97/11/13 T.Fukumoto */
			InputNumberDialMarkSet(TONE_MARK);
			break;
#endif

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
		case MERCURY:		/* マーキュリーキー *//*1996/09/18 Eguchi */
			InputNumberDialMarkSet(MERCURY_MARK);
			break;
#endif
#if defined(DEU)	/* for GroundKey '98/03/11 M.HARADA */
		case GROUND:
			if(CHK_UNI_GroundkeyCheck()){
				InputNumberDialMarkSet(PAUSE_MARK);
			}else{
				NackBuzzer();
			}
			break;
#endif

#if (PRO_MULTI_LINE == ENABLE)
 #if (PRO_KEYPANEL == PANEL_POPLAR_B)	/* by K.Watanabe 1998/01/16 */
		case COPY_RESET:	/* コピーリセットキー */
 #else
		case HOLD:			/* 保留キー */
 #endif
			/* 内線番号を示す「！」を保留キーにて入力 */
			InputNumberDialMarkSet(MULTI_TEL_MARK);
			break;
#endif

		case KEY_TIME_UP:	/* キー入力なしで１分間経過 */
		case STOP:			/* ストップキー */
			CursorOff();
			return (NG);

		case ENTER:			/* セットキー */
			/* 登録する番号が正しいかを調べる */
			if (CheckCommandNumber() == OK) { /* 正しい */
				ClearDialNumber2(WarpFile->Direct, WarpFile->Onetouch, WarpFile->Speed, &WarpFile->Group);
				SetDialNumber2(WarpFile->Direct, WarpFile->Onetouch, WarpFile->Speed, &WarpFile->Group);
				WarpFile->Status = SYS_WARP_SETTING;	/* 登録済 */
				CursorOff();
				return (OK);
			}
			else {	/* 入力値が正しくない */
				if (InputNumber.WritePosition == 0) { /* 未入力（バッファが空) */
					OPR_ChildErrorFlag = OPR_NO_ERROR;
					WarpFile->Status = SYS_WARP_EMPTY;	/* 未登録 */
					CursorOff();
					return (OK);
				}
				else {
					NackBuzzer();
				}
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

		/* 現在入力されている直接ダイヤルの件数を取得します */
		buf_count = 0;
		direct_count = 0;
		while (buf_count < InputNumber.WritePosition) {	/* 入力されているデータを全てチェックするまで */
			if (CheckInputNumberCode(InputNumber.Buffer[buf_count]) == FALSE) {	/* 直接ダイヤルの時 */
				direct_count++;
			}
			/* 次のダイヤルデータまで進めます */
			buf_count += GetStringGapPoint(&InputNumber.Buffer[buf_count], ',');
			buf_count++;
		}
		if (direct_count >= 2) {	/* 直接ダイヤルが既に、最大登録数入力されている時 */
			/* データクリア実行 */
			InputNumberDataClear();
			OPR_ChildErrorFlag = TOO_MANY_RELAY_DIRECT_ERROR;	/* "ﾁｮｸｾﾂﾀﾞｲﾔﾙ 1ｶｼｮ ｲﾅｲ " */
			NackBuzzer();
		}
	}
}

/*************************************************************************
	module		:[ＦＡＸワープデータ（指定時刻）の入力]
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
UBYTE	WarpTimeInput(struct SYS_SubDialData_t *WarpFile)
{
	UBYTE	key;
	UBYTE	keytype;

	/* 数字入力作業用バッファの初期化 */
	ClearCharacterInput();
	CharacterInput.WritePosition = 9;
	CMN_MemorySet(CharacterInput.Buffer, 10, '*');
	if (WarpFile->StartWeek != SYS_NO_DAY) {	/* 開始曜日指定有り */
		CharacterInput.Buffer[0] = WarpFile->StartWeek + '0';
	}
	if (WarpFile->StartTime != 0xFFFF) {		/* 開始時間指定有り */
		CMN_UnsignedIntToASC(&CharacterInput.Buffer[1], (UWORD)(WarpFile->StartTime/60), 2, '0');
		CMN_UnsignedIntToASC(&CharacterInput.Buffer[3], (UWORD)(WarpFile->StartTime%60), 2, '0');
	}
	if (WarpFile->EndWeek != SYS_NO_DAY) {		/* 終了曜日指定有り */
		CharacterInput.Buffer[5] = WarpFile->EndWeek + '0';
	}
	if (WarpFile->EndTime != 0xFFFF) {			/* 終了時間指定有り */
		CMN_UnsignedIntToASC(&CharacterInput.Buffer[6], (UWORD)(WarpFile->EndTime/60), 2, '0');
		CMN_UnsignedIntToASC(&CharacterInput.Buffer[8], (UWORD)(WarpFile->EndTime%60), 2, '0');
	}

	while (1) {
		/* ＦＡＸワープデータ（指定時刻）入力中の表示 */
		DisplayWarpTimeInput();

		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case AST:
		case NUMBER:
			if ((CharacterInput.CursorPosition == 0 || CharacterInput.CursorPosition == 5)	/* 曜日入力 */
			 && (key > TEN_6_KEY)) {
				NackBuzzer();
			}
			else {
				FixedNumberDataSet(key);
			}
			break;
		case FUNCTION:
			CursorRightRotation();
			break;
		case LEFT_ARROW:
			CursorLeftRotation();
			break;
		case ENTER:
			/* ＦＡＸワープデータ（指定時刻）のセット */
			if (EnterWarpTimeInput(WarpFile) == NG) {
				NackBuzzer();
			}
			else {
				return (OK);
			}
			break;
		case CLEAR:
			CMN_MemorySet(CharacterInput.Buffer, 10, '*');
			CharacterInput.CursorPosition = 0;
			break;
		case STOP:
		case KEY_TIME_UP:
			return (NG);
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
	module		:[ＦＡＸワープデータ（指定時刻）入力中の表示]
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
void	DisplayWarpTimeInput(void)
{
	/* 下段表示「(W) HH:MM--(W) HH:MM」*/
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	if (CharacterInput.Buffer[0] == '*') {
		CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[0], D2W_WarpWeek[7], 3);
	}
	else {
		CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[0], D2W_WarpWeek[CharacterInput.Buffer[0]-'0'], 3);
	}
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[4], &CharacterInput.Buffer[1], 2);
	FunctionDisplayBufferLow[6] = ':';
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[7], &CharacterInput.Buffer[3], 2);
	FunctionDisplayBufferLow[9] = '-';
	FunctionDisplayBufferLow[10] = '-';
	if (CharacterInput.Buffer[5] == '*') {
		CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[11], D2W_WarpWeek[7], 3);
	}
	else {
		CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[11], D2W_WarpWeek[CharacterInput.Buffer[5]-'0'], 3);
	}
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[15], &CharacterInput.Buffer[6], 2);
	FunctionDisplayBufferLow[17] = ':';
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[18], &CharacterInput.Buffer[8], 2);
	DisplayStringLow(0, FunctionDisplayBufferLow);

	/* カーソル表示「(W) HH:MM--(W) HH:MM」 */
	switch (CharacterInput.CursorPosition) {
	case 0:
		CursorOn((UBYTE)(OPR_LCD_LOWER_ADD + CharacterInput.CursorPosition + 1));
		break;
	case 1:
	case 2:
		CursorOn((UBYTE)(OPR_LCD_LOWER_ADD + CharacterInput.CursorPosition + 3));
		break;
	case 3:
	case 4:
		CursorOn((UBYTE)(OPR_LCD_LOWER_ADD + CharacterInput.CursorPosition + 4));
		break;
	case 5:
		CursorOn((UBYTE)(OPR_LCD_LOWER_ADD + CharacterInput.CursorPosition + 7));
		break;
	case 6:
	case 7:
		CursorOn((UBYTE)(OPR_LCD_LOWER_ADD + CharacterInput.CursorPosition + 9));
		break;
	case 8:
	case 9:
		CursorOn((UBYTE)(OPR_LCD_LOWER_ADD + CharacterInput.CursorPosition + 10));
		break;
	}
}

/*************************************************************************
	module		:[ＦＡＸワープデータ（指定時刻）のセット]
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
UBYTE	EnterWarpTimeInput(struct SYS_SubDialData_t *WarpFile)
{
	UBYTE	start_ast_cnt;
	UBYTE	end_ast_cnt;
	UBYTE	i;
	UBYTE	start_hour;		/* 開始時間（時）*/
	UBYTE	start_minute;	/* 開始時間（分）*/
	UBYTE	end_hour;		/* 終了時間（時）*/
	UBYTE	end_minute;		/* 終了時間（分）*/

	/* 曜日チェック */
	if (CharacterInput.Buffer[0] == '*' && CharacterInput.Buffer[5] == '*') {		/* 曜日指定無し */
		WarpFile->StartWeek = SYS_NO_DAY;
		WarpFile->EndWeek = SYS_NO_DAY;
	}
	else if (CharacterInput.Buffer[0] != '*' && CharacterInput.Buffer[5] != '*') {	/* 曜日指定有り */
		WarpFile->StartWeek = CharacterInput.Buffer[0] - '0';
		WarpFile->EndWeek = CharacterInput.Buffer[5] - '0';
	}
	else if (CharacterInput.Buffer[0] == '*') {
		CharacterInput.CursorPosition = 0;
		return (NG);
	}
	else {
		CharacterInput.CursorPosition = 5;
		return (NG);
	}

	/* 時間チェック */
	start_ast_cnt = 0;
	for (i = 1; i < 5; i++ ){
		if (CharacterInput.Buffer[i] == '*') {
			start_ast_cnt++;
		}
	}
	end_ast_cnt = 0;
	for (i = 6; i < 10; i++ ){
		if (CharacterInput.Buffer[i] == '*') {
			end_ast_cnt++;
		}
	}
	if (start_ast_cnt == 4 && end_ast_cnt == 4) {		/* 時間指定無し */
		WarpFile->StartTime = 0xFFFF;
		WarpFile->EndTime = 0xFFFF;
	}
	else if (start_ast_cnt == 0 && end_ast_cnt == 0) {	/* 時間指定有り */
		start_hour = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[1], 2);	/* 開始時間（時）*/
		if (start_hour > 23) {
			CharacterInput.CursorPosition = 1;
			return (NG);
		}
		start_minute = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[3], 2);	/* 開始時間（分）*/
		if (start_minute > 59) {
			CharacterInput.CursorPosition = 3;
			return (NG);
		}
		end_hour = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[6], 2);		/* 終了時間（時）*/
		if (end_hour > 23) {
			CharacterInput.CursorPosition = 6;
			return (NG);
		}
		end_minute = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[8], 2);	/* 終了時間（分）*/
		if (end_minute > 59) {
			CharacterInput.CursorPosition = 8;
			return (NG);
		}
		WarpFile->StartTime = (UWORD)start_hour;
		WarpFile->StartTime *= 60;
		WarpFile->StartTime += (UWORD)start_minute;
		WarpFile->EndTime = (UWORD)end_hour;
		WarpFile->EndTime *= 60;
		WarpFile->EndTime += (UWORD)end_minute;
	}
	else if (start_ast_cnt != 0) {
		CharacterInput.CursorPosition = (UBYTE)(GetStringGapPoint(&CharacterInput.Buffer[1], '*') + 1);
		return (NG);
	}
	else {
		CharacterInput.CursorPosition = (UBYTE)(GetStringGapPoint(&CharacterInput.Buffer[6], '*') + 6);
		return (NG);
	}
	return (OK);
}

/*************************************************************************
	module		:[ＦＡＸワープ登録数取得]
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
UBYTE	GetWarpCount(void)
{
	UBYTE	i;

	for (i = 0; i < SYS_WARP_MAX; i++) {
		if (SYB_WarpFile[i].Status == SYS_WARP_EMPTY) {	/* 未登録 */
			break;
		}
	}
	return(i);
}

/*************************************************************************
	module		:[ＦＡＸワープデータを詰める]
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
void	ShiftWarpData(void)
{
	UBYTE	loop;
	UBYTE	i;

	for (loop = OPR_Buf.WarpCtrl.SelectNumber; loop < (UBYTE)(SYS_WARP_MAX - 1); loop++) {
		SYB_WarpFile[loop].Status		= SYB_WarpFile[loop+1].Status;
		for (i = 0; i < SYS_TEL_2DIGIT_MAX; i++) {
			SYB_WarpFile[loop].Direct[i] = SYB_WarpFile[loop+1].Direct[i];
		}
		for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
			SYB_WarpFile[loop].Onetouch[i] = SYB_WarpFile[loop+1].Onetouch[i];
		}
		for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
			SYB_WarpFile[loop].Speed[i] = SYB_WarpFile[loop+1].Speed[i];
		}
		SYB_WarpFile[loop].Group		= SYB_WarpFile[loop+1].Group;
		SYB_WarpFile[loop].StartWeek	= SYB_WarpFile[loop+1].StartWeek;
		SYB_WarpFile[loop].EndWeek	= SYB_WarpFile[loop+1].EndWeek;
		SYB_WarpFile[loop].StartTime	= SYB_WarpFile[loop+1].StartTime;
		SYB_WarpFile[loop].EndTime	= SYB_WarpFile[loop+1].EndTime;
		SYB_WarpFile[loop].Option		= SYB_WarpFile[loop+1].Option;
	}
	if (loop == (UBYTE)(SYS_WARP_MAX - 1)) {
		/* ＦＡＸワープデータの初期化 */
		ClearWarpData(&SYB_WarpFile[loop]);
	}
}

/*************************************************************************
	module		:[ＦＡＸワープデータの初期化]
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
void	ClearWarpData(struct SYS_SubDialData_t *WarpFile)
{
	WarpFile->Status	= SYS_WARP_EMPTY;	/* 未登録 */
	ClearDialNumber2(WarpFile->Direct, WarpFile->Onetouch, WarpFile->Speed, &WarpFile->Group);
	WarpFile->StartWeek	= SYS_NO_DAY;		/* 曜日指定無し */
	WarpFile->EndWeek	= SYS_NO_DAY;		/* 曜日指定無し */
	WarpFile->StartTime	= 0xFFFF;
	WarpFile->EndTime	= 0xFFFF;
	WarpFile->Option	= WARP_OPTION_NONE;	/* オプション設定なし */
}

/*************************************************************************
	module		:[ＦＡＸワープリストオペレーション]
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
void	PrintFaxWarpList(void)
{
	UBYTE	i;

	for (i = 0; i < SYS_WARP_MAX; i++ ){
		if (SYB_WarpFile[i].Status != SYS_WARP_EMPTY) {	/* 登録済 */
			/* リストプリント起動メッセージ送信 */
			FinalListPrintOperation(LST_WARP_LIST);
			return;
		}
	}
	NackBuzzer();
	OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
}

/*************************************************************************
	module		:[ＦＡＸワープ設定オペレーション]
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
void	SetFaxWarp(void)
{
	/* ＦＡＸワープＯＮ／ＯＦＦ切り替え */
	if (EnterSettingStatus(D2W_SetFaxWarp,			/* "FAXﾜｰﾌﾟ:\0           " */
						   D2W_Off2,				/* "                OFF " */
						   2,
						   SETTING_STATUS_30,
						   OPR_VALID_CHECK_NOT_NEED,
						   WARP_MODE_ON) == OK) {
		ChildDisplaySetCompleted(D2W_EnterFaxWarp);	/* "FAXﾜｰﾌﾟ ｾｯﾄ         " */
	}
}
#endif	/* (PRO_RX_DOC_TRANSFER == ENABLE) */
