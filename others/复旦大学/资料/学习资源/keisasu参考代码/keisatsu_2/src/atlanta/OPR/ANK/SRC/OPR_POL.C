/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_POL.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ポーリングオペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\mem_def.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if defined(POPLAR_F)
#include	"\src\atlanta\ext_v\fcm_data.h"
#endif

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif

#if (PRO_MULTI_LINE == ENABLE)
#include	"\src\atlanta\define\sys_opt.h"
#endif

/* Prototype
void	StorePollingDocument(void);
void	ErasePollingDocument(void);
void	PrintPollingDocument(void);
void	PollingOperation(UBYTE);
*/

/*************************************************************************
	module		:[ポーリング原稿蓄積]
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
	date		:[1995/07/05]
	author		:[江口]
*************************************************************************/
void StorePollingDocument(void)
{
	DisplayStringHigh(0, D2W_StorePollingDocument);	/* "ﾎﾟｰﾘﾝｸﾞ ｹﾞﾝｺｳ ﾁｸｾｷ  " */
	PollingOperation(STORE_POLLING_DOC);
}

/*************************************************************************
	module		:[ポーリング原稿消去]
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
	date		:[1995/07/05]
	author		:[江口]
*************************************************************************/
void ErasePollingDocument(void)
{
	DisplayStringHigh(0, D2W_ErasePollingDocument);	/* "ﾎﾟｰﾘﾝｸﾞ ｹﾞﾝｺｳ ｸﾘｱ   " */
	PollingOperation(ERASE_POLLING_DOC);
}

/*************************************************************************
	module		:[ポーリング原稿印字]
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
	date		:[1995/07/05]
	author		:[江口]
*************************************************************************/
void PrintPollingDocument(void)
{
	DisplayStringHigh(0, D2W_PrintPollingDocument);	/* "ﾎﾟｰﾘﾝｸﾞ ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ " */
	PollingOperation(PRINT_POLLING_DOC);
}

/*************************************************************************
	module		:[ポーリングオペレーション]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[同じ原稿に対する蓄積・プリント・消去が同時に行われる場合
				　の処理をもう一度検討すること　1995/10/14 Eguchi
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/05]
	author		:[江口,渡辺一章]
*************************************************************************/
void PollingOperation(UBYTE mode)
{
	UBYTE	i;
	UBYTE	item;			/* 原稿種別 */
	UBYTE	db_polling;		/* 1:検索ﾎﾟｰﾘﾝｸﾞ 0:通常ﾎﾟｰﾘﾝｸﾞ */
	UBYTE	is_storing;		/* 蓄積中フラグ */
	UBYTE	is_printing;	/* プリント中フラグ */
	UBYTE	input_item;		/* NumberInput()の引数 */
	UWORD	number;			/* ファイル番号 */
	UWORD	document_exist;	/* 原稿有無フラグ */

	/*-------------------------------------------*/
	/** 検索ポーリングか通常ポーリングかを調べる */
	/*-------------------------------------------*/
	if (CTRY_DB_PolingTx() == 0) {	/** 検索ポーリングなし */
		db_polling = 0;
	}
	else {							/** 検索ポーリング有り */
		/** ファイル番号入力 */
		if (mode == STORE_POLLING_DOC) {	/* ポーリング原稿蓄積の時 */
			input_item = OPR_STORE_POLLING_NUMBER_INPUT;
		}
		else {								/* ポーリング原稿消去・プリントの時 */
			input_item = OPR_POLLING_FILE_NUMBER_INPUT;
		}

		if (NumberInput(input_item) == OK) {
			if (CheckCharacterInputEmpty() == TRUE) { /** 未入力 */
				db_polling = 0;	/** 通常ポーリング */
			}
			else {
				db_polling = 1;	/** 検索ポーリング */
			}
		}
		else {
			return;
		}
	}

	/*-----------------------------------------*/
	/** ファイル種別とファイル番号をセットする */
	/*-----------------------------------------*/
	if (db_polling) { /* 検索ポーリングの場合 */
		item = SYS_MEM_DB_POLLING_FILE;
		number = CharacterInputToNumber();
	}
	else {
		item = SYS_MEM_POLLING_FILE;
		number = 0;
	}
	/*---------------------*/
	/** 原稿の有無を調べる */
	/*---------------------*/
	document_exist = MEM_CountTotalPage(item, number, MEM_IGNORE_BOX_NUMBER);

	/*-------------------------*/
	/** 原稿の使用状況を調べる */
	/*-------------------------*/
	is_printing = CheckMemDocPrinting(item, number);
	is_storing = CheckMemDocStoring(item, number);

	/*-------------------------------------*/
	/** オペレーション種別に応じて処理実行 */
	/*-------------------------------------*/
	switch (mode) {
	/*--------------------*/
	/* ポーリング原稿蓄積 */
	/*--------------------*/
	case STORE_POLLING_DOC:	/** ポーリング原稿蓄積 */
		if (document_exist != MEM_NO_INDEX) {	/** 既に原稿が存在する */
			NackBuzzer();
			OPR_ChildErrorFlag = ALREADY_POLLING_STORED_ERROR;
		}
		else {
			/* 蓄積できる状態かを調べます */
			switch (CheckScanStartEnable(OPR_DOC_SET_CHK_INP_SET)) {
			case OPR_SCAN_ENABLE:	/* 原稿読み取り可能な時 */
#if (0)	/* Add By O.Kimoto 1999/07/19 */
** 				if (CheckMemoryOver() == FALSE) [
#else
				if ((CheckMemoryOver() == FALSE) && (CheckScanDisableCondition() == FALSE)) {
#endif
					if (db_polling) {
						OperationMessageToMain.Message = MSG_STORE_DBPOLLING_DOC;
						OperationMessageToMain.SubMessage1 = number;
					}
					else {
						OperationMessageToMain.Message = MSG_STORE_POLLING_DOC;
					}
					snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
					MainTaskExecWait();
				}
				else {
					NackBuzzer();
				}
				break;
			case OPR_SCAN_DISABLE:	/* 原稿読み取り不可能な時 */
				NackBuzzer();
				break;
			case OPR_SCAN_STOP:		/* ブック原稿サイズ入力中に停止又は、タイムアップした時 */
				/* ナックは鳴らしません */
				break;
			default:
				break;
			}
		}
		break;
	/*--------------------*/
	/* ポーリング原稿消去 */
	/*--------------------*/
	case ERASE_POLLING_DOC:	/** ポーリング原稿消去 */

		/*
		 *消去前の確認オペレーションの有無を要検討
		 *KIRI/MONIJI: 確認あり
		 *LAVENDER/SATUKI:確認なし
		 *1996/05/20　Eguchi　TBD
		 */
		if (document_exist != MEM_NO_INDEX) {	/** 原稿が存在する */
			if (is_printing == FALSE && is_storing == FALSE) {	/** 指定された原稿がプリント中、蓄積中でない.消去できる */

#if defined(POPLAR_F)
				/* 原稿を送信中（ハンドシェーク中）*/
				if (db_polling) { /** 検索ポーリングの場合 */
					if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {
						if (TxMemoryFileItem == SYS_MEM_DB_POLLING_FILE) {
							OPR_ChildErrorFlag = LINE_BUSY_ERROR; /** "通信中です"のエラー表示 */
							NackBuzzer();
							return;
						}
					}
				}
				else {	/* 通常ポーリング */
					if ((SYB_PollingDocExclusiveFlag & 0xFFF0) == 0x0000) {
						OPR_ChildErrorFlag = LINE_BUSY_ERROR; /** "通信中です"のエラー表示 */
						NackBuzzer();
						return;
					}
				}
#endif

				MEM_ClearDocAndFATArea(item, number, MEM_IGNORE_BOX_NUMBER);	/**原稿消去実行 */

				if (db_polling) { /** 検索ポーリングの場合 */
					/**ポーリング原稿の有無を調べる */
					for (i = 0; i < 100; i++) {
						if (MEM_CountTotalPage(item , i, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {
							break;
						}
					}
					if (i == 100) {
						SYB_DB_PollingDocumentStatus = 0;
					}
				}
				else { /* 通常ポーリング */
					SYB_PollingDocumentStatus = 0;
#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
** #if (PRO_MULTI_LINE == ENABLE)
** 					SYB_PollingDocExclusiveFlag = SYS_POLL_DOC_NO_EXIST;	/* ポーリング原稿があるかどうかの変数 */
** #endif
#else
					SYB_PollingDocExclusiveFlag = SYS_POLL_DOC_NO_EXIST;	/* ポーリング原稿があるかどうかの変数 */
#endif

				}
				ChildDisplayStringLow(D2W_ClearComplete);		/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
			}
			else { /** 指定された原稿が使用中（プリント中など)で消去できない*/
				if (is_printing == TRUE) {/* プリント中 */
					if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PRINTER_CLEANING) {
						OPR_ChildErrorFlag = PRINTER_CLEANING_ERROR;	/* "ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ      " */
					}
					else {
						OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;		/* "ﾌﾟﾘﾝﾄﾁｭｳ ﾃﾞｽ        " */
					}
				}
				else { /* 蓄積中 */
					OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
				}
				NackBuzzer();
			}
		}
		else { /** 蓄積原稿が存在しない */
			OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
			NackBuzzer();
		}
		break;
	/*------------------------*/
	/* ポーリング原稿プリント */
	/*------------------------*/
	case PRINT_POLLING_DOC:	/** ポーリング原稿プリント　*/
		if (document_exist != MEM_NO_INDEX) { /** 原稿が存在する */
			if (is_storing == TRUE) {
				OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
				NackBuzzer();
			}
			else {
				FinalMemoryPrintOperation(item, number, NULL);	/* メインにプリント起動メッセージを送信 */
			}
		}
		else {	/** 原稿が存在しない */
			NackBuzzer();
			OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
		}
		break;
	default:
		break;
	}
}

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* Add By H.Fujimura 1999/01/05 */
/*************************************************************************
	module		:[ポーリング原稿蓄積登録]
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
	date		:[1999/01/05]
	author		:[藤村春夫]
*************************************************************************/
UBYTE	SetStorePollingDocument(UBYTE prg_no)
{
	UBYTE	db_polling;		/* 1:検索ﾎﾟｰﾘﾝｸﾞ 0:通常ﾎﾟｰﾘﾝｸﾞ */

	/*-------------------------------------------*/
	/** 検索ポーリングか通常ポーリングかを調べる */
	/*-------------------------------------------*/
	if (CTRY_DB_PolingTx() == 0) {	/** 検索ポーリングなし */
		db_polling = 0;
	}
	else {							/** 検索ポーリング有り */
		/* 初期値をセットする */
		ClearCharacterInput();
		if (SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Item == MSG_STORE_DBPOLLING_DOC) {
			CMN_UnsignedIntToASC(CharacterInput.Buffer,
								 SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Point,
								 2,
								 '0');
		}
		CharacterInput.LcdDisplayPosition = 15;
		CharacterInput.MaxFigure = 2;
		CharacterInput.FixedWordingHigh = (UBYTE *)D2W_StorePollingDocument;	/* "ﾎﾟｰﾘﾝｸﾞ ｹﾞﾝｺｳ ﾁｸｾｷ  " */
		CharacterInput.FixedWordingLow = (UBYTE *)D2W_InputFileNumber;			/* "ﾌｧｲﾙ ﾊﾞﾝｺﾞｳ:        " */
		CharacterInput.IsNoInputEnable = TRUE;	/* データ未入力可能 */
		CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
		CharacterInput.CursorPosition = CharacterInput.WritePosition;

		/** ファイル番号入力 */
		if (NumberInput(OPR_NUMBER_INPUT_NO_INITIAL) == OK) {
			if (CheckCharacterInputEmpty() == TRUE) { /** 未入力 */
				db_polling = 0;	/** 通常ポーリング */
			}
			else {
				db_polling = 1;	/** 検索ポーリング */
			}
		}
		else {
			return (NG);
		}
	}

	/*-----------------------------------------*/
	/** ファイル種別とファイル番号をセットする */
	/*-----------------------------------------*/
	if (db_polling) { /* 検索ポーリングの場合 */
		SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Item = MSG_STORE_DBPOLLING_DOC;
		SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Point = CharacterInputToNumber();
	}
	else {
		SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Item = MSG_STORE_POLLING_DOC;
	}

	return (OK);
}

/*************************************************************************
	module		:[ポーリング原稿蓄積実行]
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
	date		:[1999/01/05]
	author		:[藤村春夫]
*************************************************************************/
void	EnterStorePollingDocument(UBYTE prg_no)
{
	UBYTE	item;			/* 原稿種別 */
	UBYTE	db_polling;		/* 1:検索ﾎﾟｰﾘﾝｸﾞ 0:通常ﾎﾟｰﾘﾝｸﾞ */
	UWORD	number;			/* ファイル番号 */

	/*-------------------------------------------*/
	/** 検索ポーリングか通常ポーリングかを調べる */
	/*-------------------------------------------*/
	if (CTRY_DB_PolingTx() == 0) {	/** 検索ポーリングなし */
		db_polling = 0;
	}
	else {							/** 検索ポーリング有り */
		if (SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Item == MSG_STORE_POLLING_DOC) {
			db_polling = 0;	/** 通常ポーリング */
		}
		else {
			db_polling = 1;	/** 検索ポーリング */
		}
	}

	/*-----------------------------------------*/
	/** ファイル種別とファイル番号をセットする */
	/*-----------------------------------------*/
	if (db_polling) { /* 検索ポーリングの場合 */
		item = SYS_MEM_DB_POLLING_FILE;
		number = SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Point;
	}
	else {
		item = SYS_MEM_POLLING_FILE;
		number = 0;
	}

	/*--------------------*/
	/* ポーリング原稿蓄積 */
	/*--------------------*/
	if (MEM_CountTotalPage(item, number, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {	/** 既に原稿が存在する */
		NackBuzzer();
		OPR_ChildErrorFlag = ALREADY_POLLING_STORED_ERROR;
	}
	else {
		/* 蓄積できる状態かを調べます */
		switch (CheckScanStartEnable(OPR_DOC_SET_CHK_INP_SET)) {
		case OPR_SCAN_ENABLE:	/* 原稿読み取り可能な時 */
#if (0)	/* Add By O.Kimoto 1999/07/19 */
** 			if (CheckMemoryOver() == FALSE) [
#else
			if ((CheckMemoryOver() == FALSE) && (CheckScanDisableCondition() == FALSE)) {
#endif
				SetProgramToSingleKey(prg_no);	/* シングルキーにプログラムワンタッチの値をセット */
				if (db_polling) {
					OperationMessageToMain.Message = MSG_STORE_DBPOLLING_DOC;
					OperationMessageToMain.SubMessage1 = number;
				}
				else {
					OperationMessageToMain.Message = MSG_STORE_POLLING_DOC;
				}
				snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
				MainTaskExecWait();
			}
			else {
				NackBuzzer();
			}
			break;
		case OPR_SCAN_DISABLE:	/* 原稿読み取り不可能な時 */
			NackBuzzer();
			break;
		case OPR_SCAN_STOP:		/* ブック原稿サイズ入力中に停止又は、タイムアップした時 */
			/* ナックは鳴らしません */
			break;
		default:
			break;
		}
	}
}
#endif	/* (PRO_EXT_P_ONETOUCH == ENABLE) */
