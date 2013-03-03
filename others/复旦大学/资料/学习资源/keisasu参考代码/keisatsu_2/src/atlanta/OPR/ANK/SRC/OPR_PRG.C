/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_PRG.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: プログラムワンタッチオペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
#include	"\src\atlanta\define\fcm_def.h"
#endif
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysonet.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
#include	"\src\atlanta\define\sys_infd.h"
#include	"\src\atlanta\ext_v\sys_inf.h"
#include	"\src\atlanta\ext_v\bkupram.h"
#endif

#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
#include	"\src\atlanta\define\syslocal.h"
#endif

/* Prototype
void	EnterProgramOneTouch(void);
void	PRG_OnetouchInitial(void);
UBYTE	SetPrograming(void);
void	DisplaySetPrograming(void);
void	GetProgramOnetouchDial(UBYTE);
void	GetProgramOnetouchOption(UBYTE);
void	GetProgramTime(UDWORD);
UBYTE	ProgramEnter(UBYTE);
void	SetProgramingDialNumber(UBYTE);
void	SetProgramingTime(UBYTE);
void	SetProgramingOption(UBYTE, UBYTE);
void	EraseProgramOneTouch(void);
void	PrintProgramOneTouchList(void);
void	ClearProgramOnetouchRecord(UBYTE);
UBYTE	SelectProgramOnetouch(void);
void	DisplayProgramSelect(void);
void	ProgramForwordOperation(void);
void	ProgramBackOperation(void);
UBYTE	CheckProgramStoreStatus(UBYTE);
*/

/*************************************************************************
	module		:[プログラムワンタッチ登録]
	function	:[
		1.指定のワンタッチにプログラムを登録する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[Ｈ８から移植]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/19]
	author		:[江口]
*************************************************************************/
void EnterProgramOneTouch(void)
{
#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
	UBYTE	prg_no;
	UBYTE	status;
	UBYTE	i;		/* 選択肢個数 */
	UBYTE	j;		/* 登録するデータ */
#endif
	/* 初期化 */
	PRG_OnetouchInitial();
	while (1) {
		/* 登録するワンタッチの決定 */
		/* 選択したプログラムワンタッチ番号は OPR_Buf.ProgOntchCtrl.SelectNumber */

		if (SelectProgramOnetouch() == OPR_END) {	/* ＳＴＯＰ */
			return;
		}
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		if (SYB_INF_ProgramOnetouchStatus[OPR_Buf.ProgOntchCtrl.SelectNumber] != SYS_INF_P_ONETOUCH_MAILGROUP) {
			/* プログラム登録 */
			if (SetPrograming() == OK) {	/* 登録完了 */
				SpecialCommandValue.CommandOption.Item = SYS_CHAR_TX;
				SpecialCommandValue.CommandTime = 0;
				ProgramForwordOperation();	/* ワンタッチを進める */
			}
			else {							/* 登録中断 */
				/*終了*/
				return;
			}
		}
		else {
			NackBuzzer();
		}
#else
		/* プログラム登録 */
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/17 Y.Matsukuma */
		if (CMN_CheckPrinting()	== TRUE) {	/* テストプリント中 */
			OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;
			NackBuzzer();
			return;
		}

		if (CheckProgramStoreStatus(OPR_Buf.ProgOntchCtrl.SelectNumber) == OPR_PRG_NO_STORED) {
			CMN_MemorySet(&(SYB_OnetouchDial[OPR_Buf.ProgOntchCtrl.SelectNumber].Name[0]), SYS_DIAL_NAME_MAX, NULL);
		}

		if (DialNameInput(&(SYB_OnetouchDial[OPR_Buf.ProgOntchCtrl.SelectNumber].Name[0])) == OK) {	/* 登録完了 */
			StoreCharacterInputValue(&(SYB_OnetouchDial[OPR_Buf.ProgOntchCtrl.SelectNumber].Name[0]), ASC_DATA_TYPE);

			if (SYB_OnetouchDial[OPR_Buf.ProgOntchCtrl.SelectNumber].Name[0] == NULL) {
				SYB_ProgramOnetouch[OPR_Buf.ProgOntchCtrl.SelectNumber].Status = SYS_CMD_EMPTY;
			}
			else {
				SYB_ProgramOnetouch[OPR_Buf.ProgOntchCtrl.SelectNumber].Status = SYS_CMD_SETTING;
			}
 #else
  #if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
		prg_no = OPR_Buf.ProgOntchCtrl.SelectNumber;
		status = CheckProgramStoreStatus(prg_no);
		/*------------------------------------------*/
		/* 拡張版プログラムワンタッチ登録内容の選択 */
		/*------------------------------------------*/
		if (status == OPR_PRG_NO_STORED) {	/* 未登録					*/
			j = 0;
			if (SelectData(OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer,
						   D2W_ProgramItem[0],						/* "    ﾄｳﾛｸ ﾅｲﾖｳ: ﾂｳｼﾝ " */
						   3,
						   &j,
						   0xFF,
						   NO_KEYTYPE) == OPR_CANCELED) {	/* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
				return;
			}
			SetSingleKeyToProgram(prg_no);	/* プログラムワンタッチにシングルキーを登録 */
		}
		/* 拡張版プログラムワンタッチ登録（リスト）*/
		if ((status == OPR_PRG_LIST) || (status == OPR_PRG_NO_STORED && j == 1)) {
			for (i = 0, j = 0; OPR_ProgramList[i].Item != 0xFE; i++) {
				if (status == OPR_PRG_LIST) {
					if (OPR_ProgramList[i].Item == SYB_ProgramOnetouch[prg_no].EntryData.ListItem) {
						j = i;
					}
				}
			}
			if (SelectData(OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer,
						   D2W_ProgramList[0],						/* "    ﾜﾝﾀｯﾁﾀﾞｲﾔﾙ ﾘｽﾄ  " */
						   i,
						   &j,
						   0xFF,
						   NO_KEYTYPE) == OPR_CANCELED) {	/* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
				return;
			}
			SYB_ProgramOnetouch[prg_no].EntryData.ListItem = OPR_ProgramList[j].Item;
			SYB_ProgramOnetouch[prg_no].Item = SYS_PROGRAM_LIST;	/* リスト */
			SetSingleKeyToProgram(prg_no);	/* プログラムワンタッチにシングルキーを登録 */
			ProgramForwordOperation();	/* ワンタッチを進める */
			continue;
		}
		/* 拡張版プログラムワンタッチ登録（蓄積）*/
		if ((status == OPR_PRG_STORE) || (status == OPR_PRG_NO_STORED && j == 2)) {
			for (i = 0, j = 0; OPR_ProgramStore[i].Item != 0xFE; i++) {
				if (status == OPR_PRG_STORE) {
					if ((OPR_ProgramStore[i].Item == SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Item)
					 || ((SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Item == MSG_STORE_DBPOLLING_DOC)
					 && (OPR_ProgramStore[i].Item == MSG_STORE_POLLING_DOC))) {
						j = i;
					}
				}
			}
			if (SelectData(OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer,
						   D2W_ProgramStore[0],						/* "    ﾎﾟｰﾘﾝｸﾞ ﾁｸｾｷ    " */
						   i,
						   &j,
						   0xFF,
						   NO_KEYTYPE) == OPR_CANCELED) {	/* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
				return;
			}
			if ((OPR_ProgramStore[j].SetFunction)(prg_no) == NG) {
				return;
			}
			SYB_ProgramOnetouch[prg_no].Item = SYS_PROGRAM_STORE;	/* 蓄積 */
			SetSingleKeyToProgram(prg_no);	/* プログラムワンタッチにシングルキーを登録 */
			ProgramForwordOperation();	/* ワンタッチを進める */
			continue;
		}
  #endif
		if (SetPrograming() == OK) {	/* 登録完了 */
 #endif
			SpecialCommandValue.CommandOption.Item = SYS_CHAR_TX;
			SpecialCommandValue.CommandTime = 0;
 #if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
			SetSingleKeyToProgram(prg_no);	/* プログラムワンタッチにシングルキーを登録 */
 #endif
			ProgramForwordOperation();	/* ワンタッチを進める */
		}
		else {							/* 登録中断 */
			/*終了*/
			return;
		}
#endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/12 by K.Okada */
	}
}

/*************************************************************************
	module		:[プログラムワンタッチ初期化処理]
	function	:[
		1.
	]
	return		:[]
	common		:[
		OPR_Buf.
		FunctionDisplayBuffer
		SpecialCommandValue
	]
	condition	:[]
	comment		:[Ｈ８から移植]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/19]
	author		:[江口,渡辺一章]
*************************************************************************/
void PRG_OnetouchInitial(void)
{
	/* オペレーションバッファをクリア */
	OPR_Buf.ProgOntchCtrl.SelectNumber = 0;	/* プログラムワンタッチの先頭のオフセット */
	CMN_MemorySet(OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer, 5 ,NULL);

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)
 #if defined(HINOKI3)	/* by K.Watanabe 2004/10/18 */
	OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer[0] = OPR_PROGRAM_MARK;
	CMN_UnsignedIntToASC(&OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer[1],
						 OPR_Buf.ProgOntchCtrl.SelectNumber + OPR_PRG_NUMBER_MIN,
						 1,
						 '0');
	OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer[2] = ':';
 #else
	CMN_UnsignedIntToASC(&OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer[0],
						 OPR_Buf.ProgOntchCtrl.SelectNumber + OPR_PRG_NUMBER_MIN,
						 2,
						 '0');
	OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer[2] = ':';
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer[0] = OPR_PROGRAM_MARK;
	CMN_UnsignedIntToASC(&OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer[1],
						 OPR_Buf.ProgOntchCtrl.SelectNumber + OPR_PRG_NUMBER_MIN,
						 2,
						 '0');
	OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer[3] = ':';
#endif

	/* 表示に使用するバッファをクリア */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	/* 応用機能登録バッファをクリア */
	SpecialCommandValue.CommandOption.Item = SYS_CHAR_TX;	/* 未登録の意味にしようしている */
	SpecialCommandValue.CommandTime = 0x00000000UL;	/* コマンド発信時間が登録されなかった時のためにクリアーしておく */
}

/*************************************************************************
	module		:[プログラム登録]
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
	date		:[1995/08/31]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE SetPrograming(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	prog_no;
	UBYTE	is_batch_tx_enable;

	/** 初期化 */
	CommandInputInitial();		/* コマンド登録用バッファを初期化 */
	InputNumber.InputDialType = PROGRAM_DIAL_TYPE;
	SetPinCheckStatus();
	ComOptionInputInitial();	/* 応用通信登録用バッファを初期化 */

	/*-------------------------------------------------------*/
	/** プログラムワンタッチの内容を作業用バッファに展開する */
	/*-------------------------------------------------------*/
	prog_no = OPR_Buf.ProgOntchCtrl.SelectNumber;
	if (CheckProgramStoreStatus(prog_no) == OPR_PRG_NO_STORED) {	/* 未登録 */
		/* 初期化されていない可能性があるので初期化する */
		ClearProgramOnetouchRecord(prog_no);
	}
	GetProgramOnetouchDial(prog_no);
	GetProgramOnetouchOption(prog_no);

#if (PRO_EXT_P_ONETOUCH == ENABLE)
	/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
	GetProgramTime(SYB_ProgramOnetouch[prog_no].EntryData.Command.ExecTime);
#else
	GetProgramTime(SYB_ProgramOnetouch[prog_no].ExecTime);
#endif

#if (PRO_BATCH_TX == ENABLE)
	/* 一括送信が登録されている時は、ここで処理します */
	switch (CheckProgramStoreStatus(prog_no)) {
	case OPR_PRG_NO_STORED:	/* 未登録 */
		is_batch_tx_enable = TRUE;	/* 一括送信登録可能 */
		break;
	case OPR_PRG_BATCH_TX:	/* 一括送信 */
		if (BatchTransmissionOperation() == OK) {	/* いきなりボックス番号入力に移行 */
			SetProgramBatchBox(prog_no);
			return (OK);
		}
		else {
			return (NG);
		}
		break;
	default:				/* 一括送信以外が登録されている */
		is_batch_tx_enable = FALSE;	/* 一括送信登録不可能 */
		break;
	}
#else
	is_batch_tx_enable = FALSE;	/* 一括送信登録不可能 */
#endif

	while (1) {
		/* ＬＣＤ表示 */
		DisplaySetPrograming();

		/* キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

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

		case SPECIAL:		/* 応用通信 */
			/* 初期登録で一度番号を入力し、クリアキーでダイヤルを消した後に応用通信キーを押しても、
			** 一括送信のメニューが出てこない不具合の修正のために、直前で毎回 OPR_BatchTxEnableFlagを
			** セットし直すように変更しました by K.Watanabe 1997/11/06
			*/
			if (is_batch_tx_enable) {	/* 一括送信登録可能な時 */
				OPR_BatchTxEnableFlag = TRUE;	/* 一括送信登録可能 */
			}
			else {
				OPR_BatchTxEnableFlag = FALSE;	/* 一括送信登録不可能 */
			}
			if (CheckInputCommandDialNumber() == TRUE) {	/* 番号入力後、応用通信キーが押された時 */
				if (CheckCommandNumber() == OK) {	/* 入力済みの番号が正しい場合 */
					OPR_BatchTxEnableFlag = FALSE;	/* 一括送信登録不可能 */
				}
				else {
					/* 応用通信登録不可 */
					NackBuzzer();
					break;
				}
			}

			if (SpecialCommandOperation(OPR_PRG_OPE) == OK) {
				if (SpecialCommandValue.CommandOption.Item == SYS_BATCH_MEMORY_TX) { /* 一括送信が登録された */
					SetProgramBatchBox(prog_no);
					return (OK);
				}
			}
			else {
				CursorOff();
				return (NG);
			}
			break;

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
			if (ProgramEnter(prog_no) == OPR_END) { /* 登録完了 */
				CursorOff();
				return (OK);
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
	module		:[プログラム登録中表示]
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
	date		:[1995/11/27]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplaySetPrograming(void)
{
	if (CheckChildErrorDisplayReq() == TRUE) {	/* エラーなどのチャイルド表示要求がある場合 */
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay() == TRUE) { /*チャイルド表示中 */
		return;
	}

	/* 上段表示[P01:Fax Number     ] */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer);
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/10/06 Y.Matsukuma */
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[3], D2W_SelectOnetouch, (UBYTE)17);
 #else
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[3], D2W_FaxNumber, (UBYTE)17);
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/17 Y.Matsukuma */
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[4], D2W_SelectOnetouch, (UBYTE)16);
 #else
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[4], D2W_FaxNumber, (UBYTE)16);
 #endif
#endif
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	/* 下段表示[123456789_         ] */
	DisplayCommandNumber();
}

/*************************************************************************
	module		:[プログラムワンタッチ前回登録内容セット]
	function	:[
		1.プログラムワンタッチの前回の登録内容を編集用かつ表示用にバッファにセットする
	]
	return		:[なし]
	common		:[
		SYB_ProgramOnetouch
		InputNumber
	]
	condition	:[InputNumber.をクリアしてからコールすること]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[]
	author		:[江口,渡辺一章]
*************************************************************************/
void GetProgramOnetouchDial(UBYTE prg_no)	/* ワンタッチ記号 */
{
#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
	SetDialDataToDispBuffer(OPR_PROGRAM_DISPLAY, &SYB_ProgramOnetouch[prg_no].EntryData.Command, InputNumber.Buffer);
#else
	SetDialDataToDispBuffer(OPR_PROGRAM_DISPLAY, &SYB_ProgramOnetouch[prg_no], InputNumber.Buffer);
#endif
}

/*************************************************************************
	module		:[プログラムワンタッチの応用機能を編集用にセットする]
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
	date		:[1995/12/01]
	author		:[江口,渡辺一章]
*************************************************************************/
void GetProgramOnetouchOption(UBYTE prog_no)
{
	UBYTE	i;					/* ループ変数 */
#if (PRO_F_CODE == ENABLE)	/* 1997/06/25 Y.Matsukuma */
	UBYTE	fcode_data_pos;		/* Ｆコードデータ格納バッファの配列番号 */
#endif
#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1998/01/13 */
	UBYTE	key_number;		/* キーブック番号 */
#endif

	/*-------------------------------*/
	/* 応用機能をバッファに展開 	 */
	/*-------------------------------*/
#if (PRO_EXT_P_ONETOUCH == ENABLE)
	/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
	SpecialCommandValue.CommandOption.Item = SYB_ProgramOnetouch[prog_no].EntryData.Command.Option.Item;
#else
	SpecialCommandValue.CommandOption.Item = SYB_ProgramOnetouch[prog_no].Option.Item;
#endif

	/* 通信種別毎の処理 */
	switch (SpecialCommandValue.CommandOption.Item) {
	case SYS_CHAR_TX:
		break;
	case SYS_SCANNER_SECURE_TX:			/* スキャナ親展送信		*/
#if (PRO_EXT_P_ONETOUCH == ENABLE)
		/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
		SpecialCommandValue.CommandOption.OptionNumber.SecureNumber
		 = SYB_ProgramOnetouch[prog_no].EntryData.Command.Option.OptionNumber.SecureNumber;
#else
		SpecialCommandValue.CommandOption.OptionNumber.SecureNumber
		 = SYB_ProgramOnetouch[prog_no].Option.OptionNumber.SecureNumber;
#endif
		break;
	case SYS_SCANNER_RELAY_BROADCAST:	/* スキャナ中継指示送信	*/
#if (PRO_EXT_P_ONETOUCH == ENABLE)
		/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
		SpecialCommandValue.CommandOption.OptionNumber.RelayGroupNumber
		 = SYB_ProgramOnetouch[prog_no].EntryData.Command.Option.OptionNumber.RelayGroupNumber;
#else
		SpecialCommandValue.CommandOption.OptionNumber.RelayGroupNumber
		 = SYB_ProgramOnetouch[prog_no].Option.OptionNumber.RelayGroupNumber;
#endif
		break;
	case SYS_DB_POLLING_RX:				/* 検索ポーリング受信	*/
		for (i = 0; i < SYS_DATA_BASE_MAX; i++) {
#if (PRO_EXT_P_ONETOUCH == ENABLE)
			/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
			SpecialCommandValue.CommandOption.OptionNumber.DatabaseNumber[i]
			 = SYB_ProgramOnetouch[prog_no].EntryData.Command.Option.OptionNumber.DatabaseNumber[i];
			if (SYB_ProgramOnetouch[prog_no].EntryData.Command.Option.OptionNumber.DatabaseNumber[i] == 0xFFFF) {/*未登録コード */
				break;
			}
#else
			SpecialCommandValue.CommandOption.OptionNumber.DatabaseNumber[i]
			 = SYB_ProgramOnetouch[prog_no].Option.OptionNumber.DatabaseNumber[i];
			if (SYB_ProgramOnetouch[prog_no].Option.OptionNumber.DatabaseNumber[i] == 0xFFFF) {/*未登録コード */
				break;
			}
#endif
		}
		break;
	case SYS_BATCH_MEMORY_TX:			/* 一括送信				*/
#if (PRO_EXT_P_ONETOUCH == ENABLE)
		/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
		SpecialCommandValue.CommandOption.OptionNumber.BatchNumber
		= SYB_ProgramOnetouch[prog_no].EntryData.Command.Option.OptionNumber.BatchNumber;
#else
		SpecialCommandValue.CommandOption.OptionNumber.BatchNumber
		= SYB_ProgramOnetouch[prog_no].Option.OptionNumber.BatchNumber;
#endif
		break;
#if (PRO_F_CODE == ENABLE)
	case SYS_SCANNER_SUB_ADDRESS_TX:	/* Ｆコードスキャナ送信	*/
	case SYS_SELECT_POLLING_RX:			/* 選択ポーリング受信	*/
		/* Ｆコードデータ格納バッファの配列番号をセットします */
#if (PRO_EXT_P_ONETOUCH == ENABLE)
		/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
		CMN_StringCopyNum(SpecialCommandValue.CommandOption.OptionNumber.FcodeDataPosition,
						  SYB_ProgramOnetouch[prog_no].EntryData.Command.Option.OptionNumber.FcodeDataPosition,
						  2);
#else
		CMN_StringCopyNum(SpecialCommandValue.CommandOption.OptionNumber.FcodeDataPosition,
						  SYB_ProgramOnetouch[prog_no].Option.OptionNumber.FcodeDataPosition,
						  2);
#endif
		fcode_data_pos = SpecialCommandValue.CommandOption.OptionNumber.FcodeDataPosition[0];

		if (fcode_data_pos != 0xFF) {	/* ｻﾌﾞｱﾄﾞﾚｽ番号が登録されている時(elseはありえませんが念のために判断します) */
			/* サブアドレス番号をＢＣＤからＡＳＣＩＩに変換します */
			CMN_FCODE_BCD_ToASC_String(OPR_FcodeData.SubAddress,
									   SYB_FcodeNumberPDataBuffer[fcode_data_pos].SYS_SubAddressNumber);

			/* 通信パスワード番号をＢＣＤからＡＳＣＩＩに変換します */
			CMN_FCODE_BCD_ToASC_String(OPR_FcodeData.Password,
									   SYB_FcodeNumberPDataBuffer[fcode_data_pos].SYS_PassWordNumber);
		}
		break;
#endif
#if (PRO_CIPHER == ENABLE)
	case SYS_CIPHER_TX:					/* 暗号化送信			*/
		OPR_CipherData.SetKeyMode = SYB_CipherPData[prog_no].SetKeyMode;				/* キー入力の設定方法	*/
		OPR_CipherData.KeyBookNumber = SYB_CipherPData[prog_no].KeyNumber;				/* キー番号				*/
		CMN_StringCopyNULL(OPR_CipherData.Key, SYB_CipherPData[prog_no].Key);			/* 暗号化キー			*/
		CMN_StringCopyNULL(OPR_CipherData.KeyClue, SYB_CipherPData[prog_no].KeyClue);	/* 暗号化キーのヒント	*/
		OPR_CipherData.KeyExtensionOn = SYB_CipherPData[prog_no].KeyExtensionOn;		/* 拡張キー設定			*/

		/* 直接入力されている以外の時は、キーブックの内容が変更されたり、デフォルトキーが変更されたり
		** している可能性があるので、最新のキーにセットし直します
		** 注）プログラムワンタッチの送信の時にしか関係はありませんが、登録の時でも特に問題は無いので、
		** 　　登録・送信の判断は行いません
		*/
		key_number = 0xFF;
		switch (OPR_CipherData.SetKeyMode) {	/* キー入力種別のチェック */
		case SYS_CIPHER_KEY_DEFAULT:	/* デフォルトキーを使用	*/
			key_number = SYB_KeyBookData.DefaultKeyNo;
			break;
		case SYS_CIPHER_KEY_BOOK:		/* キーブックから選択	*/
			key_number = OPR_CipherData.KeyBookNumber;
			break;
		case SYS_CIPHER_KEY_DIRECT:		/* 直接入力				*/
			/* 直接入力の時は、関係ありません */
			break;
		default:
			break;
		}
		if (key_number != 0xFF) {
			/** 暗号化キー */
			CMN_StringCopyNULL(OPR_CipherData.Key, SYB_KeyBookData.SYB_KeyData[key_number].Key);

			/** 暗号化キーのヒント */
			CMN_StringCopyNULL(OPR_CipherData.KeyClue, SYB_KeyBookData.SYB_KeyData[key_number].KeyClue);
		}
		break;
#endif
	default:
		break;
	}
}

/*************************************************************************
	module		:[プログラムワンタッチ/一括送信の送信時刻を取り出す]
	function	:[
		1.プログラムワンタッチ、一括送信の送信指定時刻を、秒数を分数になおして
		，編集用のバッファにセットする。
	]
	return		:[]
	common		:[
		SpecialCommandValue  :CommandTime :積算分数 
		SYB_ProgramOnetouch[]:ExecTime    :月始めからの積算秒数 
	]
	condition	:[]
	comment		:[
		86400 = 24*60*60:１日の秒数
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/01]
	author		:[江口]
*************************************************************************/
void GetProgramTime(UDWORD time)
{
	UBYTE	flag;

	flag = FALSE;
	if (time & 0x80000000UL) {
		time &= ~0x80000000UL;
		flag = TRUE;
	}
	/*秒を分に直す */
	SpecialCommandValue.CommandTime = time/60;

	if (flag) {
		SpecialCommandValue.CommandTime |= 0x80000000UL;
	}
}

/*************************************************************************
	module		:[プログラムワンタッチ登録最終処理]
	function	:[
		1.登録された内容をチェックする。
		2.ワンタッチ構造体にセットする。
	]
	return		:[
		OPR_CONTINUE:やり直し
		OPR_END		:終了
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/30]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE ProgramEnter(UBYTE prg_no)
{
	UBYTE	option_item;	/* 応用通信種別 */
	UBYTE	ret;

	ret = OPR_END;

	/* 登録する番号が正しいかを調べる */
	if (CheckCommandNumber() == OK) { /* 正しい */
		CursorOff();
		/* 電話番号、指定時刻、応用機能をプログラムワンタッチ構造体にセットする */

		/* 登録するプログラムが変更の時、前に登録されていた応用通信種別を覚えておきます
		** （Ｆコードの登録をされていた場合に必要なために追加）
		*/
#if (PRO_EXT_P_ONETOUCH == ENABLE)
		/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
		option_item = SYB_ProgramOnetouch[prg_no].EntryData.Command.Option.Item;
#else
		option_item = SYB_ProgramOnetouch[prg_no].Option.Item;
#endif

		ClearProgramOnetouchRecord(prg_no); /* 一回初期化 */
#if (PRO_PIN_ACCESS == ENABLE)
		/* ダイアルをセットする所で、ＰＩＮアクセスのモードを参照しているから,セットする */
 #if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/03/29 */
		SetCommandPinAccessMode(&SYB_ProgramOnetouch[prg_no].EntryData.Command);	/* ＰＩＮアクセスモードをセット */
 #else
		SetCommandPinAccessMode(&SYB_ProgramOnetouch[prg_no]);	/* ＰＩＮアクセスモードをセット */
 #endif
#endif
		SetProgramingDialNumber(prg_no);
		SetProgramingTime(prg_no);
		SetProgramingOption(prg_no, option_item);

#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
		SYB_ProgramOnetouch[prg_no].Item = SYS_PROGRAM_COMMAND;	/* 通信予約 */
		SYB_ProgramOnetouch[prg_no].EntryData.Command.Status = SYS_CMD_SETTING;	/* セット中にする */
#else
		SYB_ProgramOnetouch[prg_no].Status = SYS_CMD_SETTING;	/* セット中にする */
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
		SYB_INF_ProgramOnetouchStatus[prg_no] = SYS_INF_P_ONETOUCH_PROGRAM;
		SYB_INF_MailGroup[prg_no][0] = 0x00;
#endif
	}
	else {	/* 入力値が正しくない */
		if (InputNumber.WritePosition == 0) { /* 未入力（バッファが空) */
			/* 何も登録されずにセットキーのみ押された時、
			  (相手先番号が入力されていない状態でセットが押された時)
			   指定されたワンタッチキーの内容を消去する 		*/
			OPR_ChildErrorFlag = OPR_NO_ERROR;
			ClearProgramOnetouchRecord(prg_no);
		}
		else {
			NackBuzzer();
			ret = OPR_CONTINUE;
		}
	}
	return (ret);
}

/*************************************************************************
	module		:[プログラムワンタッチ、電話番号セット]
	function	:[
		1.入力された電話番号をプログラムワンタッチ構造体にセットする。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/31]
	author		:[江口,渡辺一章]
*************************************************************************/
void SetProgramingDialNumber(UBYTE prg_no)
{
#if (PRO_PIN_ACCESS == ENABLE)
 #if (PRO_EXT_P_ONETOUCH == ENABLE)
	/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
	SetDialNumber(&SYB_ProgramOnetouch[prg_no].EntryData.Command.DialNumber, SYB_ProgramOnetouch[prg_no].EntryData.Command.PIN_AccessMode);
 #else
	SetDialNumber(&SYB_ProgramOnetouch[prg_no].DialNumber, SYB_ProgramOnetouch[prg_no].PIN_AccessMode);
 #endif

#else
	/* ＰＩＮ機能なしの時は、ＰＩＮアクセスモードは関係ないので、とりあえずＰＩＮアクセスしないを渡す */
 #if (PRO_EXT_P_ONETOUCH == ENABLE)
	/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
	SetDialNumber(&SYB_ProgramOnetouch[prg_no].EntryData.Command.DialNumber, PIN_ACCESS_OFF);
 #else
	SetDialNumber(&SYB_ProgramOnetouch[prg_no].DialNumber, PIN_ACCESS_OFF);
 #endif
#endif
}

/*************************************************************************
	module		:[プログラムワンタッチ指定時刻セット]
	function	:[
		1.月始めからの積算秒数をセットする
	]
	return		:[]
	common		:[
		SYB_ProgramOnetouch:ExecTime->積算秒数
		SpecialCommandValue:CommandTime->積算分数
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/31]
	author		:[江口]
*************************************************************************/
void SetProgramingTime(UBYTE prg_no)	/* プログラムワンタッチ */
{
	UBYTE	flag;

	flag = FALSE;
	if (SpecialCommandValue.CommandTime & 0x80000000UL) {
		SpecialCommandValue.CommandTime &= ~0x80000000UL;
		flag = TRUE;
	}
	/* 分を秒に直す */
#if (PRO_EXT_P_ONETOUCH == ENABLE)
	/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
	SYB_ProgramOnetouch[prg_no].EntryData.Command.ExecTime = SpecialCommandValue.CommandTime * 60;
	if (flag) {
		SYB_ProgramOnetouch[prg_no].EntryData.Command.ExecTime |= 0x80000000UL;
	}
#else
	SYB_ProgramOnetouch[prg_no].ExecTime = SpecialCommandValue.CommandTime * 60;
	if (flag) {
		SYB_ProgramOnetouch[prg_no].ExecTime |= 0x80000000UL;
	}
#endif
}

/*************************************************************************
	module		:[プログラムワンタッチ応用機能セット]
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
	date		:[1995/08/31]
	author		:[江口,渡辺一章]
*************************************************************************/
void SetProgramingOption(UBYTE prg_no, UBYTE option_item)
{
	UBYTE	item;

	/* 応用機能種別のセット */
	/* SpecialCommandValue.CommandOption.Itemは応用機能オペレーション中でセットされる */

	item = SpecialCommandValue.CommandOption.Item;
	switch (item) {
	case SYS_CHAR_TX:				/* キャラクタ送信 *//* この場合、応用機能未登録の意味で使用 ,この場合ExecTimeは０*/
	case SYS_DELAYED_SCANNER_TX:	/* 時刻指定スキャナ送信 */
		if (InputNumber.MultiNumberStatus == 1) { /** 同報入力された */
			item = SYS_DELAYED_BROADCAST;
		}
		break;
	case SYS_DELAYED_BROADCAST:		/* 順次同報送信 */
		if (InputNumber.MultiNumberStatus == 0) {/* 同報入力されなかった */
			/* もともと同報入力されていたものが再編集され、同報入力でなくなった場合 */
			/* かつこの場合、応用機能はセットされていない							*/
			if (SpecialCommandValue.CommandTime == 0x00000000UL) { /* 時刻が指定されていない */
				item = SYS_CHAR_TX; /* 応用機能未登録をセットする */
			}
			else {
				item = SYS_DELAYED_SCANNER_TX;
			}
		}
		break;
	default:
		break;
	}

#if (PRO_EXT_P_ONETOUCH == ENABLE)
	/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
	SYB_ProgramOnetouch[prg_no].EntryData.Command.Option.Item = item;
#else
	SYB_ProgramOnetouch[prg_no].Option.Item = item;
#endif

#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
	SetCommandOptionNumber(&SYB_ProgramOnetouch[prg_no].EntryData.Command, OPR_PRG_OPE, option_item);
#else
	SetCommandOptionNumber(&SYB_ProgramOnetouch[prg_no], OPR_PRG_OPE, option_item);
#endif
}

/*************************************************************************
	module		:[プログラムワンタッチ消去]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-C2]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/04/10]
	author		:[江口]
*************************************************************************/
void EraseProgramOneTouch(void)
{
	UBYTE	erase_step;

	erase_step = ERASE_ITEM_SELECT_STEP;
	PRG_OnetouchInitial();

	while (1) {
		switch (erase_step) {
		case ERASE_ITEM_SELECT_STEP:	/* 選択状態 */
			if (SelectProgramOnetouch() == OPR_END) { /* STOP */
				/* 終了 */
				return;
			}
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
			if (SYB_INF_ProgramOnetouchStatus[OPR_Buf.ProgOntchCtrl.SelectNumber] == SYS_INF_P_ONETOUCH_PROGRAM) {
				erase_step = ERASE_CONFIRM_STEP;
			}
#else
			/* 登録状態をえる*/
			if (CheckProgramStoreStatus(OPR_Buf.ProgOntchCtrl.SelectNumber) != OPR_PRG_NO_STORED) {
				erase_step = ERASE_CONFIRM_STEP;
			}
#endif
			else {
				NackBuzzer();
			}
			break;
		case ERASE_CONFIRM_STEP:	/* クリア確認状態 */
			switch (ConfirmKeyInputOperation(D2W_EraseProgramOnetouch, D2W_CheckProgramEnter, ENTER, FUNCTION)) {
			case CONFIRM_EXEC:	/* 実行 */
				/* ワンタッチ消去実行 */
				ClearProgramOnetouchRecord(OPR_Buf.ProgOntchCtrl.SelectNumber);
				erase_step = ERASE_COMPLETE_STEP;
				break;
			case CONFIRM_ABORT:	/* 取り消し */
				erase_step = ERASE_ITEM_SELECT_STEP;/* 戻る */
				break;
			case OPR_END:		/* 中止・タイムアップ */
				return;	
			default:
				break;
			}
			break;
		case ERASE_COMPLETE_STEP:	/* 消去完了表示 */
			if (ClearCompleteDisplayOperation(D2W_EraseProgramOnetouch) == OPR_CONTINUE) {
				erase_step = ERASE_ITEM_SELECT_STEP;
				ProgramForwordOperation();
			}
			else {
				return;
			}
			break;
		default:
			break;
		}
	}
}

/*************************************************************************
	module		:[プログラムワンタッチリスト]
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
	date		:[1995/08/31]
	author		:[江口]
*************************************************************************/
void PrintProgramOneTouchList(void)
{
	UBYTE	prg_no;

	/* ワンタッチテーブルをサーチ */
	for (prg_no = 0; prg_no < SYS_PROGRAM_MAX; prg_no++) {
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		if (SYB_INF_ProgramOnetouchStatus[prg_no] == SYS_INF_P_ONETOUCH_PROGRAM) {
			FinalListPrintOperation(LST_PROGRAM_LIST); /* メインにリスト起動メッセージ送信 1995/04/04 Egu*/
			return;
		}
#else
		if (CheckProgramStoreStatus(prg_no) != OPR_PRG_NO_STORED) {
			FinalListPrintOperation(LST_PROGRAM_LIST); /* メインにリスト起動メッセージ送信 1995/04/04 Egu*/
			return;
		}
#endif
	}
	/*登録データなし*/
	NackBuzzer();
	OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
}

/*************************************************************************
	module		:[プログラムワンタッチデータクリア]
	function	:[
		1.ステータスをＥＭＰＴＹ（未使用）にする。
		2.ダイアル番号をクリアする。
		3.応用機能のItemを初期化する。
		4.指定時刻を初期化する.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/27]
	author		:[江口]
*************************************************************************/
void ClearProgramOnetouchRecord(UBYTE prog_no)
{
#if (PRO_F_CODE == ENABLE)
	UBYTE	fcode_data_pos;		/* Ｆコードデータ格納バッファの配列番号 */
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
	SYB_INF_ProgramOnetouchStatus[prog_no] = SYS_INF_P_ONETOUCH_NO_ENTRY;
#endif

#if (PRO_EXT_P_ONETOUCH == DISABLE) /* By H.Fujimura 1999/01/21 */
	/* ステータスを未使用にする */
	SYB_ProgramOnetouch[prog_no].Status = SYS_CMD_EMPTY; /* 念のため */
#endif

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/17 Y.Matsukuma */
	CMN_MemorySet(&(SYB_OnetouchDial[prog_no].Name[0]), SYS_DIAL_NAME_MAX, NULL);
#endif

#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
	switch (CheckProgramStoreStatus(prog_no)) {
 #if (PRO_F_CODE == ENABLE)
	case OPR_PRG_FCODE_TX:			/** Ｆコード送信 */
	case OPR_PRG_FCODE_POLL:		/** Ｆコードポーリング受信 */
		fcode_data_pos = SYB_ProgramOnetouch[prog_no].EntryData.Command.Option.OptionNumber.FcodeDataPosition[0];
		SYB_FcodeNumberPDataBuffer[fcode_data_pos].SYS_SubAddressNumber[0] = 0xFF;
		SYB_FcodeNumberPDataBuffer[fcode_data_pos].SYS_PassWordNumber[0] = 0xFF;
		break;
 #endif
 #if (PRO_CIPHER == ENABLE)
	case OPR_PRG_CIPHER_TX:			/** 暗号化送信 */
		CMN_ClearCipherPData(prog_no);
		break;
 #endif
	default:
		break;
	}
#else
 #if (PRO_F_CODE == ENABLE)
	/* Ｆコードデータ格納バッファのクリア */
	if ((SYB_ProgramOnetouch[prog_no].Option.Item == SYS_SCANNER_SUB_ADDRESS_TX)	/* Ｆコードスキャナ送信	*/
	 || (SYB_ProgramOnetouch[prog_no].Option.Item == SYS_SELECT_POLLING_RX)) {		/* 選択ポーリング受信	*/
		fcode_data_pos = SYB_ProgramOnetouch[prog_no].Option.OptionNumber.FcodeDataPosition[0];
		SYB_FcodeNumberPDataBuffer[fcode_data_pos].SYS_SubAddressNumber[0] = 0xFF;
		SYB_FcodeNumberPDataBuffer[fcode_data_pos].SYS_PassWordNumber[0] = 0xFF;
	}
 #endif
 #if (PRO_CIPHER == ENABLE)
	/* 暗号化データバッファのクリア */
	if (SYB_ProgramOnetouch[prog_no].Option.Item == SYS_CIPHER_TX) {	/* 暗号化送信 */
		CMN_ClearCipherPData(prog_no);
	}
 #endif
#endif

#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
	ClearCommandFileData(&SYB_ProgramOnetouch[prog_no].EntryData.Command);
#else
	ClearCommandFileData(&SYB_ProgramOnetouch[prog_no]);
#endif

#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
	/* ステータスを未使用にする */
	SYB_ProgramOnetouch[prog_no].Item = SYS_PROGRAM_EMPTY;	/* 未使用 */
	SYB_ProgramOnetouch[prog_no].EntryData.Command.Status = SYS_CMD_EMPTY; /* 念のため */
#endif
}

/*************************************************************************
	module		:[プログラムワンタッチ選択]
	function	:[
		1.登録するプログラムワンタッチを選択
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/27]
	author		:[江口]
*************************************************************************/
UBYTE SelectProgramOnetouch(void)
{
	UBYTE	key;
	UBYTE	keytype;

	DisplayStringHigh(0 , D2W_SelectProgramOnetouch); /* 上段表示[Select Program No.  ] */

	while (1) {
		DisplayProgramSelect();	/* 下段表示 [P01:Delayed         ] */

		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();
	
		switch (keytype) {
		case FUNCTION:		/* 機能キー */
			/* プログラムを進める */
			ProgramForwordOperation();
			break;
		case LEFT_ARROW:	/* ＜キー */
			/* プログラムを戻す */
			ProgramBackOperation();
			break;
		case KEY_TIME_UP:
		case STOP:
			/*終了*/
			return (OPR_END);
		case ENTER:
			/* プログラムキー決定 */
			return (OPR_CONTINUE);
		case PROGRAM:		/* プログラムワンタッチキー */
#if defined (KEISATSU)		/* 警察FAX DVT_ID5 Modify start by SMuratec K.W.Q 2005/10/28 */
			if (key > (OPR_TOP_PROGRAM_KEY + SYS_PROGRAM_MAX - 1)) {
				NackBuzzer();
			}
			else {
				OPR_Buf.ProgOntchCtrl.SelectNumber = key - (UBYTE)OPR_TOP_PROGRAM_KEY;
			}
#else
			OPR_Buf.ProgOntchCtrl.SelectNumber = key - (UBYTE)OPR_TOP_PROGRAM_KEY;
#endif		/* 警察FAX DVT_ID Modify end by SMuratec K.W.Q 2005/10/28 */
			break;
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif
		case NO_EFFECT:
			/* ナックをならさへんため */
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[プログラムワンタッチ選択中下段表示]
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
	date		:[1995/11/27]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayProgramSelect(void)
{
	UBYTE	program;
	UBYTE	copy_length;	/* コピー最大長 */
	UBYTE	*copy_buffer;	/* コピー開始アドレス */
#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
	UBYTE	i;
#endif

	program = OPR_Buf.ProgOntchCtrl.SelectNumber;

	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	/* 選択されているプログラムワンタッチをセットします */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
 #if defined(HINOKI3)	/* by K.Watanabe 2004/10/19 */
	CMN_UnsignedIntToASC(&OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer[1], program + OPR_PRG_NUMBER_MIN, 1, '0');
 #else
	CMN_UnsignedIntToASC(&OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer[0], program + OPR_PRG_NUMBER_MIN, 2, '0');
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	CMN_UnsignedIntToASC(&OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer[1], program + OPR_PRG_NUMBER_MIN, 2, '0');
#endif
	CMN_StringCopy(FunctionDisplayBufferLow, OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer);

	/* 機種によりプログラムワンタッチの表示方法が違うので、それを考慮します */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	copy_buffer = &FunctionDisplayBufferLow[3];
	copy_length = 17;
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	copy_buffer = &FunctionDisplayBufferLow[4];
	copy_length = 16;
#endif

	/* 登録状態により表示文字列を選択 */
	switch (CheckProgramStoreStatus(program)) {
	case OPR_PRG_NO_STORED:			/* 登録されていない */
		/* [73:ｾｯﾄ ｻﾚﾃｲﾏｾﾝ      ] */
		/* [P01:ｾｯﾄ ｻﾚﾃｲﾏｾﾝ     ] */
		CMN_StringCopyNumOrNULL(copy_buffer, D2W_NoNumberStored, copy_length);
		break;
	case OPR_PRG_DELAYED_TX:		/** 時刻指定送信 */
		/* [73:ｼﾞｺｸｼﾃｲ ｿｳｼﾝ     ] */
		/* [P01:ｼﾞｺｸｼﾃｲ ｿｳｼﾝ    ] */
		CMN_StringCopyNumOrNULL(copy_buffer, D2W_DelayedTransmission, copy_length);
		break;
	case OPR_PRG_SECURE_TX:			/** 親展送信 */
		/* [73:ｼﾝﾃﾝｿｳｼﾝ         ] */
		/* [P01:ｼﾝﾃﾝｿｳｼﾝ        ] */
		CMN_StringCopyNumOrNULL(copy_buffer, D2W_SecureTransmission, copy_length);
		break;
	case OPR_PRG_RELAY_BROADCAST:	/** 中継指示送信 */
		/* [73:ﾁｭｳｹｲｼｼﾞ ｿｳｼﾝ    ] */
		/* [P01:ﾁｭｳｹｲｼｼﾞ ｿｳｼﾝ   ] */
		CMN_StringCopyNumOrNULL(copy_buffer, D2W_RelayTransmission, copy_length);
		break;
	case OPR_PRG_POLLING_RX:		/** ポーリング受信  */
		/* [73:ﾎﾟｰﾘﾝｸﾞ          ] */
		/* [P01:ﾎﾟｰﾘﾝｸﾞ         ] */
		CMN_StringCopyNumOrNULL(copy_buffer, D2W_PollingCommunication, copy_length);
		break;
	case OPR_PRG_BATCH_TX:			/** 一括送信 */
		/* [73:ｲｯｶﾂ ｿｳｼﾝ        ] */
		/* [P01:ｲｯｶﾂ ｿｳｼﾝ       ] */
		CMN_StringCopyNumOrNULL(copy_buffer, D2W_BatchTransmission, copy_length);
		break;
#if (PRO_F_CODE == ENABLE)
	case OPR_PRG_FCODE_TX:			/** Ｆコード送信 */
		/* [73:Fｺｰﾄﾞ ｿｳｼﾝ       ] */
		CMN_StringCopyNumOrNULL(copy_buffer, &D2W_SetFcodeTransmission[2], copy_length);
		break;
	case OPR_PRG_FCODE_POLL:		/** Ｆコードポーリング受信 */
		/* [73:Fｺｰﾄﾞ ﾎﾟｰﾘﾝｸﾞ    ] */
		CMN_StringCopyNumOrNULL(copy_buffer, &D2W_SetFcodePolling[2], copy_length);
		break;
#endif
#if (PRO_CIPHER == ENABLE)
	case OPR_PRG_CIPHER_TX:			/** 暗号化送信 */
		/* [73:ｽｸﾗﾝﾌﾞﾙ ｿｳｼﾝ     ] */
		CMN_StringCopyNumOrNULL(copy_buffer, &D2W_SetCipherTransmission[2], copy_length);
		break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
	case OPR_PRG_MAIL_GROUP:
		CMN_StringCopyNumOrNULL(copy_buffer, D2W_MailGroupSetting, copy_length);
		break;
#endif
#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
	case OPR_PRG_LIST:				/* リスト					*/
		for (i = 0; OPR_ProgramList[i].Item != 0xFE; i++) {
			if (OPR_ProgramList[i].Item == SYB_ProgramOnetouch[program].EntryData.ListItem) {
				CMN_StringCopyNumNotNULL(copy_buffer, &D2W_ProgramList[i][3], copy_length);
				break;
			}
		}
		break;
	case OPR_PRG_STORE:				/* 蓄積						*/
		for (i = 0; OPR_ProgramStore[i].Item != 0xFE; i++) {
			if ((OPR_ProgramStore[i].Item == SYB_ProgramOnetouch[program].EntryData.StoreData.Item)
			 || ((SYB_ProgramOnetouch[program].EntryData.StoreData.Item == MSG_STORE_DBPOLLING_DOC)
			 && (OPR_ProgramStore[i].Item == MSG_STORE_POLLING_DOC))) {
				CMN_StringCopyNumNotNULL(copy_buffer, &D2W_ProgramStore[i][3], copy_length);
				break;
			}
		}
		break;
#endif
	default:
		break;
	}

	/* 下段表示書き換え */
	DisplayStringLow(0, FunctionDisplayBufferLow);
}

/*************************************************************************
	module		:[プログラムワンタッチを進める]
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
	date		:[1995/11/27]
	author		:[江口]
*************************************************************************/
void ProgramForwordOperation(void)
{
	if (OPR_Buf.ProgOntchCtrl.SelectNumber == (SYS_PROGRAM_MAX - 1)) {
		OPR_Buf.ProgOntchCtrl.SelectNumber = 0;
	}
	else {
		OPR_Buf.ProgOntchCtrl.SelectNumber++;
	}
}

/*************************************************************************
	module		:[プログラムワンタッチを戻す]
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
	date		:[1995/11/27]
	author		:[江口]
*************************************************************************/
void ProgramBackOperation(void)
{
	if (OPR_Buf.ProgOntchCtrl.SelectNumber == 0) {
		OPR_Buf.ProgOntchCtrl.SelectNumber = SYS_PROGRAM_MAX - 1;
	}
	else {
		OPR_Buf.ProgOntchCtrl.SelectNumber--;
	}
}

/*************************************************************************
	module		:[プログラムワンタッチ登録状態チェック]
	function	:[
		1.プログラムワンタッチの登録状態を得る
	]
	return		:[
		OPR_PRG_NO_STORED
		OPR_PRG_DELAYED_TX
		OPR_PRG_SECURE_TX
		OPR_PRG_RELAY_BROADCAST
		OPR_PRG_POLLING_RX
		OPR_PRG_BATCH_TX
#if (PRO_F_CODE == ENABLE)
		OPR_PRG_FCODE_TX
		OPR_PRG_FCODE_POLL
#endif
#if (PRO_CIPHER == ENABLE)
		OPR_PRG_CIPHER_TX
#endif
	]
	common		:[SYB_ProgramOnetouch]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/27]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE CheckProgramStoreStatus(UBYTE prg_no)
{
	UBYTE	status;

	status = OPR_PRG_NO_STORED;

#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
	if (SYB_ProgramOnetouch[prg_no].Item == SYS_PROGRAM_EMPTY) {	/* 未使用 */
		return (OPR_PRG_NO_STORED);
	}
	if (SYB_ProgramOnetouch[prg_no].Item == SYS_PROGRAM_LIST) {		/* リスト */
		return (OPR_PRG_LIST);
	}
	if (SYB_ProgramOnetouch[prg_no].Item == SYS_PROGRAM_STORE) {	/* 蓄積 */
		return (OPR_PRG_STORE);
	}
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
	if (SYB_INF_ProgramOnetouchStatus[prg_no] == SYS_INF_P_ONETOUCH_NO_ENTRY) {
		status = OPR_PRG_NO_STORED;
	}
	else if (SYB_INF_ProgramOnetouchStatus[prg_no] == SYS_INF_P_ONETOUCH_MAILGROUP) {
		status = OPR_PRG_MAIL_GROUP;
	}
	else {
		switch (SYB_ProgramOnetouch[prg_no].Option.Item) {
		case SYS_CHAR_TX:					/* キャラクタ送信		*/
		case SYS_DELAYED_SCANNER_TX:		/* 時刻指定スキャナ送信	*/
		case SYS_DELAYED_BROADCAST:			/* 順次同報送信			*/
			status = OPR_PRG_DELAYED_TX;
			break;
		case SYS_SCANNER_SECURE_TX:			/* スキャナ親展送信		*/
			status = OPR_PRG_SECURE_TX;
			break;
		case SYS_SCANNER_RELAY_BROADCAST:	/* スキャナ中継指示送信	*/
			status = OPR_PRG_RELAY_BROADCAST;
			break;
		case SYS_POLLING_RX:				/* ポーリング受信		*/
		case SYS_DB_POLLING_RX:				/* 検索ポーリング受信	*/
			status = OPR_PRG_POLLING_RX;
			break;
		case SYS_BATCH_MEMORY_TX:			/* 一括送信				*/
			status = OPR_PRG_BATCH_TX;
			break;
 #if (PRO_F_CODE == ENABLE)
		case SYS_SCANNER_SUB_ADDRESS_TX:	/* Ｆコードスキャナ送信	*/
			status = OPR_PRG_FCODE_TX;
			break;
		case SYS_SELECT_POLLING_RX:			/* 選択ポーリング受信	*/
			status = OPR_PRG_FCODE_POLL;
			break;
 #endif
 #if (PRO_CIPHER == ENABLE)
		case SYS_CIPHER_TX:					/* 暗号化送信			*/
			status = OPR_PRG_CIPHER_TX;
			break;
 #endif
		default:
			break;
		}
	}
#else
 #if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
	if (SYB_ProgramOnetouch[prg_no].EntryData.Command.Status == SYS_CMD_EMPTY) {	/* プログラムワンタッチが未登録の時 */
 #else
	if (SYB_ProgramOnetouch[prg_no].Status == SYS_CMD_EMPTY) {	/* プログラムワンタッチが未登録の時 */
 #endif
		status = OPR_PRG_NO_STORED;
	}
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/08/18 Y.Matsukuma */
	else {
		status = OPR_PRG_DELAYED_TX;
	}
 #else
	else {														/* プログラムワンタッチが登録済みの時 */
 #if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
		switch (SYB_ProgramOnetouch[prg_no].EntryData.Command.Option.Item) {
 #else
		switch (SYB_ProgramOnetouch[prg_no].Option.Item) {
 #endif
		case SYS_CHAR_TX:					/* キャラクタ送信		*/
		case SYS_DELAYED_SCANNER_TX:		/* 時刻指定スキャナ送信	*/
		case SYS_DELAYED_BROADCAST:			/* 順次同報送信			*/
			status = OPR_PRG_DELAYED_TX;
			break;
		case SYS_SCANNER_SECURE_TX:			/* スキャナ親展送信		*/
			status = OPR_PRG_SECURE_TX;
			break;
		case SYS_SCANNER_RELAY_BROADCAST:	/* スキャナ中継指示送信	*/
			status = OPR_PRG_RELAY_BROADCAST;
			break;
		case SYS_POLLING_RX:				/* ポーリング受信		*/
		case SYS_DB_POLLING_RX:				/* 検索ポーリング受信	*/
			status = OPR_PRG_POLLING_RX;
			break;
		case SYS_BATCH_MEMORY_TX:			/* 一括送信				*/
			status = OPR_PRG_BATCH_TX;
			break;
  #if (PRO_F_CODE == ENABLE)
		case SYS_SCANNER_SUB_ADDRESS_TX:	/* Ｆコードスキャナ送信	*/
			status = OPR_PRG_FCODE_TX;
			break;
		case SYS_SELECT_POLLING_RX:			/* 選択ポーリング受信	*/
			status = OPR_PRG_FCODE_POLL;
			break;
  #endif
  #if (PRO_CIPHER == ENABLE)
		case SYS_CIPHER_TX:					/* 暗号化送信			*/
			status = OPR_PRG_CIPHER_TX;
			break;
  #endif
		default:
			break;
		}
	}
 #endif  /* PRO_MINOLTA_TEST_FUNC   1998/08/18 Y.Matsukuma */
#endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/12 by K.Okada */
	return (status);
}

/*************************************************************************
	module		:[プログラムワンタッチに一括送信ＢＯＸ登録]
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
	date		:[1997/05/22]
	author		:[桑原]
*************************************************************************/
void	SetProgramBatchBox(UBYTE prog_no)
{
	struct	SYS_CommandData_t	*ptr;

#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
	ptr = &SYB_ProgramOnetouch[prog_no].EntryData.Command;
#else
	ptr = &SYB_ProgramOnetouch[prog_no];
#endif
	ClearProgramOnetouchRecord(prog_no);

	ptr->Option.Item = SYS_BATCH_MEMORY_TX;
	ptr->Option.OptionNumber.BatchNumber = SpecialCommandValue.CommandOption.OptionNumber.BatchNumber;
#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
	SYB_ProgramOnetouch[prog_no].Item = SYS_PROGRAM_COMMAND;	/* 通信予約 */
#endif
	ptr->Status = SYS_CMD_SETTING;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
	SYB_INF_ProgramOnetouchStatus[prog_no] = SYS_INF_P_ONETOUCH_PROGRAM;
	SYB_INF_MailGroup[prog_no][0] = 0x00;
#endif
}

#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/21 */
/*************************************************************************
	module		:[プログラムワンタッチにシングルキーを登録]
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
	date		:[1999/01/21]
	author		:[藤村春夫]
*************************************************************************/
void	SetSingleKeyToProgram(UBYTE prg_no)
{
	UBYTE	i;				/* 選択肢個数 */
	UBYTE	j;				/* 登録するデータ */
	UBYTE	PrimaryMode;	/* 優先モード */
	UBYTE	TxMode;			/* 送信モード */

	/*------------*/
	/* 画質の選択 */
	/*------------*/
	switch (CheckProgramStoreStatus(prg_no)) {
	case OPR_PRG_NO_STORED:		/* 未登録					*/
	case OPR_PRG_POLLING_RX:	/* ポーリング受信			*/
	case OPR_PRG_FCODE_POLL:	/* Ｆコードポーリング受信	*/
	case OPR_PRG_LIST:			/* リスト					*/
		SYB_ProgramOnetouch[prg_no].TxModeSW = 0xFF;
		break;
	default:
		PrimaryMode = GetPrimaryMode(SYB_ProgramOnetouch[prg_no].TxModeSW);	/* 優先モードの獲得 */
		for (i = 0, j = 0; OPR_ProgramTxModeSW[i] != 0xFE; i++) {
			if (OPR_ProgramTxModeSW[i] == PrimaryMode) {
				j = i;
			}
		}
		if (SelectData(OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer,
					   D2W_ProgramTxModeSW[0],					/* "    ｶﾞｼﾂ: ---       " */
					   i,
					   &j,
					   0xFF,
					   NO_KEYTYPE) == OPR_CANCELED) {	/* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
			return;
		}
		TxMode = GetTxMode(OPR_ProgramTxModeSW[j]);	/* 送信モードの獲得 */
		SYB_ProgramOnetouch[prg_no].TxModeSW = TxMode;
		break;
	}

	/*------------*/
	/* 濃度の選択 */
	/*------------*/
	switch (CheckProgramStoreStatus(prg_no)) {
	case OPR_PRG_NO_STORED:		/* 未登録					*/
	case OPR_PRG_POLLING_RX:	/* ポーリング受信			*/
	case OPR_PRG_FCODE_POLL:	/* Ｆコードポーリング受信	*/
	case OPR_PRG_LIST:			/* リスト					*/
		SYB_ProgramOnetouch[prg_no].ContrastSW = 0xFF;
		break;
	default:
		for (i = 0, j = 0; OPR_ProgramContrastSW[i] != 0xFE; i++) {
			if (OPR_ProgramContrastSW[i] == SYB_ProgramOnetouch[prg_no].ContrastSW) {
				j = i;
			}
		}
		if (SelectData(OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer,
					   D2W_ProgramContrastSW[0],				/* "    ﾉｳﾄﾞ:       --- " */
					   i,
					   &j,
					   0xFF,
					   NO_KEYTYPE) == OPR_CANCELED) {	/* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
			return;
		}
		SYB_ProgramOnetouch[prg_no].ContrastSW = OPR_ProgramContrastSW[j];
		break;
	}

	/*------------------*/
	/* 済スタンプの選択 */
	/*------------------*/
#if defined(KEISATSU)		/* Modify start by SMuratec K.W.Q 2005/07/01 */
	/* スミスタプ機能を削除 */
	SYB_ProgramOnetouch[prg_no].StampSW = 0xFF;
	
#else
	
	switch (CheckProgramStoreStatus(prg_no)) {
	case OPR_PRG_NO_STORED:		/* 未登録					*/
	case OPR_PRG_POLLING_RX:	/* ポーリング受信			*/
	case OPR_PRG_FCODE_POLL:	/* Ｆコードポーリング受信	*/
	case OPR_PRG_LIST:			/* リスト					*/
	case OPR_PRG_STORE:			/* 蓄積						*/
		SYB_ProgramOnetouch[prg_no].StampSW = 0xFF;
		break;
	default:
		for (i = 0, j = 0; OPR_ProgramStampSW[i] != 0xFE; i++) {
			if (OPR_ProgramStampSW[i] == SYB_ProgramOnetouch[prg_no].StampSW) {
				j = i;
			}
		}
		if (SelectData(OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer,
					   D2W_ProgramStampSW[0],					/* "    ｽﾐｽﾀﾝﾌﾟ:    --- " */
					   i,
					   &j,
					   0xFF,
					   NO_KEYTYPE) == OPR_CANCELED) {	/* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
			return;
		}
		SYB_ProgramOnetouch[prg_no].StampSW = OPR_ProgramStampSW[j];
		break;
	}
#endif	/* Modify end by SMuratec K.W.Q 2005/07/01 */

	/*------------------*/
	/* メモリ送信の選択 */
	/*------------------*/
	switch (CheckProgramStoreStatus(prg_no)) {
	case OPR_PRG_NO_STORED:		/* 未登録					*/
	case OPR_PRG_POLLING_RX:	/* ポーリング受信			*/
	case OPR_PRG_FCODE_POLL:	/* Ｆコードポーリング受信	*/
	case OPR_PRG_LIST:			/* リスト					*/
	case OPR_PRG_STORE:			/* 蓄積						*/
			SYB_ProgramOnetouch[prg_no].MemoryTxSW = 0xFF;
		break;
	case OPR_PRG_BATCH_TX:		/* 一括送信					*/
			SYB_ProgramOnetouch[prg_no].MemoryTxSW = SYS_MEMORY_TX_ON;
		break;
	default:
		if (InputNumber.MultiNumberStatus) {	/** 同報の時（宛先が複数箇所指定されている） */
			SYB_ProgramOnetouch[prg_no].MemoryTxSW = SYS_MEMORY_TX_ON;
		}
		else {
			for (i = 0, j = 0; OPR_ProgramMemoryTxSW[i] != 0xFE; i++) {
				if (OPR_ProgramMemoryTxSW[i] == SYB_ProgramOnetouch[prg_no].MemoryTxSW) {
					j = i;
				}
			}
			if (SelectData(OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer,
						   D2W_ProgramMemoryTxSW[0],				/* "    ﾒﾓﾘｿｳｼﾝ:    --- " */
						   i,
						   &j,
						   0xFF,
						   NO_KEYTYPE) == OPR_CANCELED) {	/* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
				return;
			}
			SYB_ProgramOnetouch[prg_no].MemoryTxSW = OPR_ProgramMemoryTxSW[j];
		}
		break;
	}

	/*--------------*/
	/* 通信証の選択 */
	/*--------------*/
	switch (CheckProgramStoreStatus(prg_no)) {
	case OPR_PRG_NO_STORED:		/* 未登録					*/
	case OPR_PRG_POLLING_RX:	/* ポーリング受信			*/
	case OPR_PRG_FCODE_POLL:	/* Ｆコードポーリング受信	*/
	case OPR_PRG_LIST:			/* リスト					*/
	case OPR_PRG_STORE:			/* 蓄積						*/
		SYB_ProgramOnetouch[prg_no].ConfirmSW = 0xFF;
		break;
	case OPR_PRG_BATCH_TX:		/* 一括送信					*/
		SYB_ProgramOnetouch[prg_no].ConfirmSW = TCR_REQUEST;	/* 送信証 */
		break;
	default:
		for (i = 0, j = 0; OPR_ProgramConfirmSW[i] != 0xFE; i++) {
			if (OPR_ProgramConfirmSW[i] == SYB_ProgramOnetouch[prg_no].ConfirmSW) {
				j = i;
			}
		}
		if (!CTRY_RCR()) {	/* 受領証機能無効 */
			i--;
		}
		if (SelectData(OPR_Buf.ProgOntchCtrl.SelectNumberDisplayBuffer,
					   D2W_ProgramConfirmSW[0],					/* "    ﾂｳｼﾝｼｮｳ:    --- " */
					   i,
					   &j,
					   0xFF,
					   NO_KEYTYPE) == OPR_CANCELED) {	/* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
			return;
		}
		SYB_ProgramOnetouch[prg_no].ConfirmSW = OPR_ProgramConfirmSW[j];
		break;
	}
}

/*************************************************************************
	module		:[優先モードの獲得]
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
	date		:[1999/01/21]
	author		:[藤村春夫]
*************************************************************************/
UBYTE	GetPrimaryMode(UBYTE TxMode)
{
	switch (TxMode) {
	case SYS_NORMAL:
		return(PRIMARY_MODE_NORMAL);
	case SYS_FINE:
		return(PRIMARY_MODE_FINE);
	case SYS_EFINE:
	case SYS_HFINE:
	case SYS_SFINE:
		return(PRIMARY_MODE_SFINE);
	case SYS_GRAY64_SEP:
	case SYS_GRAY64:
	case SYS_GRAY16_SEP:
	case SYS_GRAY16:
		return(PRIMARY_MODE_GRAY);
	default:
		return(TxMode);
	}
}

/*************************************************************************
	module		:[送信モードの獲得]
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
	date		:[1999/01/21]
	author		:[藤村春夫]
*************************************************************************/
UBYTE	GetTxMode(UBYTE PrimaryMode)
{
	switch (PrimaryMode) {
	case PRIMARY_MODE_NORMAL:
		return(SYS_NORMAL);
	case PRIMARY_MODE_FINE:
		return(SYS_FINE);
	case PRIMARY_MODE_SFINE:

		if( SYB_MaintenanceSwitch[40] & 0x02 ){		/* 1996/06/17 By N.Sakamoto */
			return(SYS_EFINE);
		}
		else{
			if (CHK_UNI_HyperFineON()) { /** ハイパーファインである場合 '96,04,15 UNI By N.S.*/
				return(SYS_HFINE);
			}
			else { /** スーパーファインである場合 */
				return(SYS_SFINE);
			}
		}
	case PRIMARY_MODE_GRAY:
		if (CHK_Halftone64ON()) {		/** 64階調である場合 */
			if (CHK_Halftone2ON()) {	/** 写真2である場合 */
				return(SYS_GRAY64_SEP);
			}
			else {						/** 写真1である場合 */
				return(SYS_GRAY64);
			}
		}
		else {							/** 16階調である場合 */
			if (CHK_Halftone2ON()) {	/** 写真2である場合 */
				return(SYS_GRAY16_SEP);
			}
			else {						/** 写真1である場合 */
				return(SYS_GRAY16);
			}
		}
	default:
		return(PrimaryMode);
	}
}

/*************************************************************************
	module		:[シングルキーにプログラムワンタッチの値をセット]
	function	:[
		1.プログラムワンタッチに登録されているキーのみ（0xFF以外）を
		  それぞれのシングルキーにセット
		2.シングルキーの登録には以下のものがある
				送信モード（画質）
				濃度
				済スタンプ
				メモリ／スキャナ送信
				通信証
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/21]
	author		:[藤村春夫]
*************************************************************************/
void	SetProgramToSingleKey(UBYTE prg_no)
{

	/**	送信モード（画質）	*/
	if (SYB_ProgramOnetouch[prg_no].TxModeSW != 0xFF) {
		SYB_ModeSw	= SYB_ProgramOnetouch[prg_no].TxModeSW;
	}

	/**	濃度				*/
	if (SYB_ProgramOnetouch[prg_no].ContrastSW != 0xFF) {
		SYB_DensitySw	= SYB_ProgramOnetouch[prg_no].ContrastSW;
	}

	/** 済スタンプ			*/
	if (SYB_ProgramOnetouch[prg_no].StampSW != 0xFF) {
		if (SYB_ProgramOnetouch[prg_no].StampSW	== 0) {	/* ＯＦＦの時 */
			SYB_LocalStatus[0] &= ~SYS_STAMP_ON;
		}
		else {	/* ＯＮの時 */
			SYB_LocalStatus[0] |= SYS_STAMP_ON;
		}

	}

	/** メモリ／スキャナ送信*/
	if (SYB_ProgramOnetouch[prg_no].MemoryTxSW != 0xFF) {
		if (SYB_ProgramOnetouch[prg_no].MemoryTxSW == 0) {	/* ＯＦＦの時 */
			SYB_LocalStatus[0] &= ~SYS_MEMORY_TX_ON;
		}
		else {	/* ＯＮの時 */
			SYB_LocalStatus[0] |= SYS_MEMORY_TX_ON;
		}
	}

	/**	通信証				*/
	if (SYB_ProgramOnetouch[prg_no].ConfirmSW != 0xFF) {
		SYB_ConfirmationReportSwitch	= SYB_ProgramOnetouch[prg_no].ConfirmSW;
	}

	UpdateLED();
}
#endif	/* (PRO_EXT_P_ONETOUCH == ENABLE) */
