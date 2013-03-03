/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_BTX.C
*	Author		: 渡辺一章
*	Date		: 1996/10/17
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 一括送信オペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\mem_def.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\sysbatch.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\sysdial.h"
#include	"\src\atlanta\define\sysonet.h"
#include	"\src\atlanta\define\sysspeed.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#include	"\src\atlanta\define\cmn_def.h"

/* Prototype
#if (PRO_BATCH_TX == ENABLE)
void	SetBatchBox(void);
void	PrintBatchBoxList(void);
void	EraseBatchBox(void);
void	PrintBatchDocumentList(void);
void	PrintBatchTxDocument(void);
void	EraseBatchTxDocument(void);
UBYTE	SelectBatchBox(void);
void	DisplayBatchBoxSelect(void);
UBYTE	EnterBatchTxData(void);
UBYTE	EnterBatchTxDialNumber(void);
UBYTE	CheckValidKeyForBatchDial(UBYTE, UBYTE);
UBYTE	BatchDialEnter(UBYTE);
void	DisplayBatchTxDialNumberInput(void);
UBYTE	EnterBatchTxTime(void);
UBYTE	EnterBatchTxName(void);
void	SetBatchDialAndTime(void);
void	ClearBatchBoxData(void);
void	BatchBoxNumberForword(void);
void	BatchBoxNumberBack(void);
void	GetBatchTxDialNumber(UBYTE, UBYTE *, UWORD);
UBYTE	CheckBatchTxFileStatus(UBYTE);
#endif	/ (PRO_BATCH_TX == ENABLE) /
*/

#if (PRO_BATCH_TX == ENABLE)
/*************************************************************************
	module		:[一括送信ボックス登録]
	function	:[
		1.一括送信ボックスの登録を実行
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ＢＯＸ番号 -> 表示は１から。内部では０から
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/09/21]
	author		:[江口]
*************************************************************************/
void SetBatchBox(void)
{
	/* 一括送信用ワークバッファをクリア */
	OPR_Buf.BatTxCtrl.SelectNumber = 0;
	OPR_Buf.BatTxCtrl.ProgramTime = 0x00000000UL;
	OPR_Buf.BatTxCtrl.DialNumber.Item = SYS_EMPTY_DIAL;
	CMN_MemorySet(OPR_Buf.BatTxCtrl.DialNumber.FaxNumber.Direct, SYS_DIRECT_DIAL_MAX, 0xFF);
	CMN_MemorySet(OPR_Buf.BatTxCtrl.Name, SYS_BATCH_NAME_MAX, NULL);

	while (1) {
		/** 一括送信ボックスを選択 */
		switch (SelectBatchBox()) {
		case OPR_END:/* STOP */
			return;
		case BATCH_BOX_NOT_ENTRY: /* 未登録 */
		case BATCH_BOX_EMPTY:	  /* 未使用 */
			/* 一括送信ボックス登録 */
			if (EnterBatchTxData() == OPR_END) {
				return;
			}
			/* ボックス番号を進める */
			BatchBoxNumberForword();
			break;
		default:	/* 蓄積中、予約中、実行中、・・・ */
			OPR_ChildErrorFlag = BATCH_DOCUMENT_STORED_ERROR;
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[一括送信ボックスリストプリント]
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
	date		:[1995/09/21]
	author		:[江口]
*************************************************************************/
void PrintBatchBoxList(void)
{
	UBYTE	i;

	/** 一括送信ボックス登録状態を調べる */
	for (i = 0; i < SYS_BATCH_FILE_MAX; i++) {
		if (CheckBatchTxFileStatus(i) != BATCH_BOX_NOT_ENTRY) {/**	登録されている */
			/** リストプリント実行処理(メインにメッセージ送信) */
			FinalListPrintOperation(LST_BATCHTXBOX_LIST);
			return;
		}
	}
	/** 未登録の場合エラーフラグをセットして終了 */
	OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR; /* エラーメッセージ要検討 */
	NackBuzzer();
}

/*************************************************************************
	module		:[一括送信ボックス消去]
	function	:[
		1.登録済みの一括送信ボックスの削除を行う。
		2.選択されたボックスが次のような状態の場合削除できない
		,	1,原稿蓄積中
		,	2,原稿登録済み、原稿プリント中
		,	3,送信中
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ボックス消去・原稿クリア・プリント等の条件を再度、検討する必要がある 1995/10/12
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/09/21]
	author		:[江口]
*************************************************************************/
void EraseBatchBox(void)
{
	/* 一括送信ボックスを選択 */
	/* 原稿蓄積等でボックスが使用されていたら消去しない*/

	UBYTE	erase_step;
	UBYTE	sel_status;

	erase_step = ERASE_ITEM_SELECT_STEP;
	OPR_Buf.BatTxCtrl.SelectNumber = 0;

	while (1) {
		switch (erase_step) { /** 消去オペレーション段階毎の処理　*/
		case ERASE_ITEM_SELECT_STEP:	/** ボックス選択状態 */
			sel_status = SelectBatchBox();
			if (sel_status == OPR_END) { /** 一括送信ボックス選択中止（ストップ) */
				return; /** 終了　*/
			}
			else if (sel_status == BATCH_BOX_EMPTY) { /** 未使用 */
				/** 消去可能なので消去確認の段階に進む　*/
				erase_step = ERASE_CONFIRM_STEP;
			}
			else {/** 使用中(実行中、予約中、蓄積中)または未登録 */
				NackBuzzer();
				if (sel_status != BATCH_BOX_NOT_ENTRY) {
					OPR_ChildErrorFlag = BATCH_DOCUMENT_STORED_ERROR;
				}
			}
			break;
		case ERASE_CONFIRM_STEP:	/** クリア確認状態 */
			switch (ConfirmKeyInputOperation(D2W_EraseBatchBoxMode, D2W_CheckProgramEnter, ENTER, FUNCTION)) {
			case CONFIRM_EXEC:	/* 実行 */
				/** 一括送信ボックス消去実行 */
				ClearBatchBoxData();
				erase_step = ERASE_COMPLETE_STEP;
				break;
			case CONFIRM_ABORT:	/* 取り消し */
				/* 消去中止。ボックス選択状態に戻る */
				erase_step = ERASE_ITEM_SELECT_STEP;
				break;
			case OPR_END:		/* 中止・タイムアップ */
				return;
			default:
				break;
			}
			break;
		case ERASE_COMPLETE_STEP:	/* 消去完了表示 */
			if (ClearCompleteDisplayOperation(D2W_EraseBatchBoxMode) == OPR_CONTINUE) {
				erase_step = ERASE_ITEM_SELECT_STEP;
				BatchBoxNumberForword();
			}
			else {/*STOP*/
				return;
			}
			break;
		default:
			break;
		}
	}
}

/*************************************************************************
	module		:[一括送信原稿リストプリント]
	function	:[
		1.全ての一括送信ボックスに対する原稿の登録状態をプリントする
		2.プリント起動条件は以下のようにする。
		,　登録されているボックスが存在する。
		,　少なくとも一つのボックスに１ファイル以上原稿が蓄積されている。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/09/21]
	author		:[江口]
*************************************************************************/
void PrintBatchDocumentList(void)
{
	UBYTE	box_status;
	UBYTE	box_no;
	UBYTE	index_no;
	UBYTE	document_exist;
	UBYTE	not_entry_cnt;

	document_exist = not_entry_cnt = 0;

	for (box_no = 0; box_no < SYS_BATCH_FILE_MAX; box_no++) {
		/** 一括送信ボックスの状態を調べる */
		box_status = CheckBatchTxFileStatus(box_no);

		switch (box_status) {
		case BATCH_BOX_STORING:	  	/* 蓄積中 */
		case BATCH_BOX_WAITING:		/* 予約中 */
		case BATCH_BOX_EXECUTE:		/* 実行中 */
			/** 蓄積済みの原稿の有無を調べる */
			for (index_no = 0; index_no < SYS_BATCH_INDEX_MAX; index_no++) {
				if (SYB_BatchTxFile[box_no].IndexNo[index_no] == SYS_BAT_DOC_STORE) {/** 原稿蓄積済み */
					document_exist = 1;
					break;
				}
			}
			break;
		case BATCH_BOX_EMPTY:	  	/* 未使用（原稿なし）*/
		case BATCH_BOX_ERASED:		/* コマンド消去   */
		case BATCH_BOX_POWER_OFF:	/* 電源ＯＦＦ */
			break;
		case BATCH_BOX_NOT_ENTRY:	/* 未登録 */
			not_entry_cnt++;
			break;
		default:
			break;
		}

		/** 原稿が登録されている場合、リスト起動メッセージを送信して終了 */
		if (document_exist == 1) {
			FinalListPrintOperation(LST_BATCHTXDOC_LIST);
			return;
		}
	}

	/* ここにくるのは原稿がどのボックスにも登録されていないか、登録されているボックスがない場合 */
	if (not_entry_cnt == SYS_BATCH_FILE_MAX) { /**登録済みのボックスがない */
		OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
		NackBuzzer();
	}
	else { /** どのボックスにも原稿が登録されていない */
		OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
		NackBuzzer();
	}
}

/*************************************************************************
	module		:[一括送信原稿プリント]
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
	date		:[1995/09/21]
	author		:[江口]
*************************************************************************/
void PrintBatchTxDocument(void)
{
	UWORD	index_no;
	UBYTE	box_no;
	UBYTE	item;
	UBYTE	box_status;

	DisplayStringHigh(0 , D2W_PrintBatchDocMode);
	/** 一括送信ボックスを選択 */
	if (NumberInput(OPR_BATCH_BOX_NUMBER_INPUT) == NG) {/**入力中にストップキー */
		return;
	}

	/**ボックスの状態(未登録・蓄積中・予約中・・・)を調べる */
	box_no = (UBYTE)CharacterInputToNumber();
	box_no -= OPR_BATCH_FILE_MIN;/* ボックス番号：表示、入力;１ ～。内部処理;０～ */

	/** 選択されたボックスの状態を調べる */
	box_status = CheckBatchTxFileStatus(box_no);
	if (box_status != BATCH_BOX_WAITING) { /** 未登録、原稿なし（未使用）、蓄積中、実行中・・・ */
		/* リダイアル待ちの間もプリントできないことになるが・・・TBD */

		/** プリントせずに終了 */
		NackBuzzer();
		if (box_status == BATCH_BOX_NOT_ENTRY) {
			OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
	}
		if (box_status == BATCH_BOX_EMPTY) {
			OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
		}
		return;
	}

	/** プリントを行うファイル（IndexNo)を選択 */
	if (NumberInput(OPR_BATCH_INDEX_NUMBER_INPUT) == NG) {
		return;
	}

	/** ファイル番号入力中にステータスが変化していないか調べる */
	if (CheckBatchTxFileStatus(box_no) != BATCH_BOX_WAITING) {/** 予約中以外 この場合実行中しかない*/
		NackBuzzer();
		return;
	}

	/** 指定されたファイル番号の原稿の有無を調べる */
	index_no = CharacterInputToNumber();
	if (SYB_BatchTxFile[box_no].IndexNo[index_no] == SYS_BAT_DOC_EMPTY) { /** 原稿なし */
		NackBuzzer();
		OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
		return;
	}

	if (SYB_BatchTxFile[box_no].IndexNo[index_no] == SYS_BAT_DOC_STORING) {/* 蓄積中-->このぱすはないやろなー */
		NackBuzzer();
		return;
	}

	/** 原稿が存在する場合プリント起動メッセージを送信 */
	item = (UBYTE)(SYS_MEM_BATCH_TX_FILE1 + box_no);
	FinalMemoryPrintOperation(item, index_no, NULL);	/* プリント中の場合、このなかで弾かれる */
}

/*************************************************************************
	module		:[一括送信原稿消去]
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
	date		:[1995/09/21]
	author		:[江口,渡辺一章]
*************************************************************************/
void EraseBatchTxDocument(void)
{
	UWORD	index_no;
	UBYTE	box_no;
	UBYTE	item;
	UBYTE	i;
	UBYTE	doc_flag;
	UBYTE	old_status;
	UBYTE	box_status;

	index_no = 0;

	DisplayStringHigh(0 , D2W_EraseBatchDocumentMode);

	/** 一括送信ボックスを選択 */
	if (NumberInput(OPR_BATCH_BOX_NUMBER_INPUT) == NG) {
		return;
	}
	/* ボックスの状態(未登録・蓄積中・予約中・・・)を調べる */

	box_no = (UBYTE)CharacterInputToNumber();
	box_no -= OPR_BATCH_FILE_MIN;

	/** 選択されたボックスの使用状態を調べる */
	box_status = CheckBatchTxFileStatus(box_no);
	if (box_status != BATCH_BOX_WAITING) { /** 未登録、原稿なし（未使用）、蓄積中、実行中・・ */
		/** 消去せずに終了*/
		NackBuzzer();
		if (box_status == BATCH_BOX_NOT_ENTRY) {/*未登録のボックスを選択 */
			OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
		}
		if (box_status == BATCH_BOX_EMPTY) { /* 未使用 */
			OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
		}
		return;
	}

	/* ステータスが操作中に実行中にならんように一時的にステータスを変更 */
	/* 消去動作を優先させる*/
	old_status = SYB_BatchTxFile[box_no].Status;
	SYB_BatchTxFile[box_no].Status = SYS_CMD_SETTING;

	/** ファイル番号（IndexNo)を入力 */
	if (NumberInput(OPR_BATCH_INDEX_NUMBER_INPUT) == NG) {/* 番号入力中止 */
		SYB_BatchTxFile[box_no].Status = old_status; /* ステータスを戻しておく */
		return;
	}

	/* 原稿の有無を調べる */
	index_no = CharacterInputToNumber();
	if (SYB_BatchTxFile[box_no].IndexNo[index_no] == SYS_BAT_DOC_EMPTY) {
		NackBuzzer();
		OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
		SYB_BatchTxFile[box_no].Status = old_status; /* ステータスを戻しておく */
		return;
	}
	if (SYB_BatchTxFile[box_no].IndexNo[index_no] == SYS_BAT_DOC_STORING) { /*これは多分ないやろなー */
		NackBuzzer();
		SYB_BatchTxFile[box_no].Status = old_status; /* ステータスを戻しておく */
		return;
	}

	item = (UBYTE)(SYS_MEM_BATCH_TX_FILE1 + box_no);
	if (CheckMemDocPrinting(item , index_no) == TRUE) { /** その一括送信原稿を印字中の場合 */
		NackBuzzer();
		if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PRINTER_CLEANING) {
			OPR_ChildErrorFlag = PRINTER_CLEANING_ERROR;	/* "ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ      " */
		}
		else {
			OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;		/* "ﾌﾟﾘﾝﾄﾁｭｳ ﾃﾞｽ        " */
		}
		SYB_BatchTxFile[box_no].Status = old_status; 	/* ステータスを戻しておく */
		return;
	}

	/* その一括送信原稿を印字中でない場合 */
	if (ConfirmKeyInputOperation(D2W_EraseBatchDocumentMode,	/* "ｲｯｶﾂ ｿｳｼﾝ ｹﾞﾝｺｳ ｸﾘｱ " */
								 D2W_CheckProgramEnter,			/* "ｶｸﾆﾝ        ｷﾉｳ/ｾｯﾄ " */
								 ENTER,
								 FUNCTION) == CONFIRM_EXEC) {	/* 消去確認 */

		/** 原稿消去 */
		MEM_ClearDocAndFATArea(item, index_no, MEM_IGNORE_BOX_NUMBER);
		SYB_BatchTxFile[box_no].IndexNo[index_no] = SYS_BAT_DOC_EMPTY;
		doc_flag = 0;
		for (i = 0; i < SYS_BATCH_INDEX_MAX; i++) { /** 他に原稿が残っているかチェック */
			if (SYB_BatchTxFile[box_no].IndexNo[i]) { /** まだ他に原稿が残っている場合 */
				doc_flag = 1;
				break;
			}
		}
		if (!doc_flag) { /** 原稿が残っていない場合 */
			SYB_BatchTxFile[box_no].Status = SYS_CMD_EMPTY;
		}
		else {
			SYB_BatchTxFile[box_no].Status = old_status; /* ステータスを戻しておく */
		}
		ChildDisplayStringLow(D2W_ClearComplete);			/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
	}
	else {
		SYB_BatchTxFile[box_no].Status = old_status; /* ステータスを戻しておく */
	}
}

/*************************************************************************
	module		:[一括送信ボックス選択]
	function	:[
		1.セット／消去するためのボックス番号を選択する。
	]
	return		:[
				OPR_END(0)
				BATCH_BOX_NOT_ENTRY(1)
				BATCH_BOX_STORING(2)
				BATCH_BOX_WAITING(3)
				BATCH_BOX_EXECUTE(3)
				BATCH_BOX_ERASED(4)
				BATCH_BOX_POWER_OFF(5)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/11]
	author		:[江口]
*************************************************************************/
UBYTE SelectBatchBox(void)
{
	UBYTE	key;
	UBYTE	keytype;

	while (1) {
		/** 一括送信ボックス選択中の表示処理*/
		DisplayBatchBoxSelect();

		/** キー取り込 */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/*----------------------------*/
		/* 取り込んだキーに対する処理 */
		/*----------------------------*/
		switch (keytype) {/** 取り込んだキー毎の処理 */
		case KEY_TIME_UP: /**１分間キー入力なし */
		case STOP:		  /** ストップ */
			/** オペレーション終了をリターン */
			return (OPR_END);

		case ENTER:/**セットキー */
			/** ボックス仕様状況をリターン */
			return (CheckBatchTxFileStatus(OPR_Buf.BatTxCtrl.SelectNumber));

		case FUNCTION:/**機能キー*/
			BatchBoxNumberForword(); /** ボックス番号を進める 1→２→・・ */
			break;

		case LEFT_ARROW:/**左カーソルキー*/
			BatchBoxNumberBack();	/** ボックス番号を戻す ５→４→・・*/
			break;

		case NUMBER:/**数字キー*/
			if (TEN_1_KEY <=key && key <= TEN_5_KEY) {	/** ダイレクトに選択 */
				OPR_Buf.BatTxCtrl.SelectNumber = (UBYTE)(ChangeASC_CodeToNumber(key) - OPR_BATCH_FILE_MIN);
			}
			else {
				NackBuzzer();
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
	module		:[一括送信ボックス選択中の表示]
	function	:[
		1.ＬＣＤ上段に固定文字列を表示
		2.ＬＣＤ下段に選択中のボックス番号と、登録状態を表示
		, 登録状態は登録されている場合、ＦＡＸ番号表示、未登録の場合固定ワーディング表示
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		注）ボックス番号は、内部で処理する場合は０から始まるが、
			表示する時は１からになるので気をつけること
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/11]
	author		:[江口]
*************************************************************************/
void DisplayBatchBoxSelect(void)
{
	UBYTE	box_no;

	/* 上段:[Select Batch Box    ] */
	/* 下段:[ＢＯＸ番号＋ＦＡＸ番号 */

	if (CheckChildErrorDisplayReq() == TRUE) {
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay() == TRUE) {
		return;
	}

	box_no = OPR_Buf.BatTxCtrl.SelectNumber;

	/* 下段表示文字列の作成 */
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	FunctionDisplayBufferLow[0] = ChangeNumberToASC_Code((UBYTE)(box_no + OPR_BATCH_FILE_MIN));
	FunctionDisplayBufferLow[1] = ':';

	/* ダイアルデータが登録されていない場合のみ固定ワーディングをコピー */
	if (CheckBatchTxFileStatus(box_no) == BATCH_BOX_NOT_ENTRY) {/** 未登録 */
		CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[2], D2W_NoNumberStored, 18);
	}
	else {
		GetBatchTxDialNumber(box_no, &FunctionDisplayBufferLow[2], 18);
 #if (PRO_PREFIX_KEY == ENABLE)	/* by K.Watanabe 2004/11/12 */
		/* プレフィックス番号展開処理 */
		ChangeDisplayBuffer(FunctionDisplayBufferLow);
 #endif
	}

	DisplayStringHigh(0, D2W_SelectBatchBoxNumber);	/* "ﾎﾞｯｸｽ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ  " */
	DisplayStringLow(0, FunctionDisplayBufferLow);
}

/*************************************************************************
	module		:[一括送信ボックスデータ登録]
	function	:[
		1.一括送信ファイルに相手先ダイアル番号、送信指定時刻、相手先名を登録する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/12]
	author		:[江口]
*************************************************************************/
UBYTE EnterBatchTxData(void)
{
	/** 指定されたボックスが未登録の場合,初期化する */
	if (SYB_BatchTxFile[OPR_Buf.BatTxCtrl.SelectNumber].DialNumber[0].Item == SYS_EMPTY_DIAL) {
		ClearBatchBoxData();
	}

	/** ワークエリアを初期化する */
	OPR_Buf.BatTxCtrl.DialNumber.Item = SYS_EMPTY_DIAL;
	CMN_MemorySet(OPR_Buf.BatTxCtrl.DialNumber.FaxNumber.Direct, SYS_DIRECT_DIAL_MAX, 0xFF);
#if (PRO_PIN_ACCESS == ENABLE)
	CMN_MemorySet(OPR_Buf.BatTxCtrl.DialNumber.PIN_Number, SYS_PIN_MAX, 0xFF);
#endif
	CMN_MemorySet(OPR_Buf.BatTxCtrl.Name, SYS_DIAL_NAME_MAX, NULL);
	OPR_Buf.BatTxCtrl.ProgramTime = 0x00000000UL;

	/** ＦＡＸ番号の登録 */
	if (EnterBatchTxDialNumber() == NG) {
		return (NG);
	}

	/** ダイアル番号が登録されているか調べる */
	if (OPR_Buf.BatTxCtrl.DialNumber.Item == SYS_EMPTY_DIAL) { /* 消去された */
		/** ボックス消去とみなす */
		ClearBatchBoxData();
		return (OK);
	}

	/** 送信時刻の入力 */
	if (EnterBatchTxTime() == NG) {
		return (NG);
	}

	/** ダイアル番号と送信時刻をセットする */
	SetBatchDialAndTime();

	/** 相手先名の入力  */
	if (EnterBatchTxName() == NG) {
		return (NG);
	}
	return (OK);
}

/*************************************************************************
	module		:[一括送信ＦＡＸ番号入力]
	function	:[
		1.一括送信の相手先番号の入力を行う
		2.相手先番号として、４０桁以内の直接ダイアル、ワンタッチダイアル、短縮ダイアルが指定できる
		3.同報入力はできないものとする。
	]
	return		:[なし]
	common		:[
		InputNumber
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/12]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE EnterBatchTxDialNumber(void)
{
	UBYTE 	key;
	UBYTE	keytype;
	UBYTE	box_no;
	UBYTE	dial_item;
	UBYTE	data;
#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/29 */
	UBYTE	i;
#endif

	/** 初期化 */
	CommandInputInitial(); 							/* コマンド登録用バッファを初期化 */
	InputNumber.InputDialType = BATCH_DIAL_TYPE; 	/* 1996/01/10 Eguchi */
	SetPinCheckStatus();							/* ＰＩＮ番号の入力チェック状況をセット */
	box_no = OPR_Buf.BatTxCtrl.SelectNumber;
	dial_item = SYB_BatchTxFile[box_no].DialNumber[0].Item;
	GetBatchTxDialNumber(box_no, InputNumber.Buffer, OPR_INPUT_NUMBER_BUFFER_MAX);
#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/29 */
	if (SYB_BatchTxFile[box_no].DialNumber[0].Item == SYS_DIRECT_DIAL) {/* ダイレクトダイアル：ＡＳＣＩＩでセット */
		if ((SYB_BatchTxFile[box_no].DialNumber[0].PIN_Number[0] & 0xF0) != 0xF0) {
			i = CMN_StringLength(InputNumber.Buffer);
			*(InputNumber.Buffer + i++) = OPR_PIN_MARK;
			CMN_BCD_ToASC_StringNum(InputNumber.Buffer + i, SYB_BatchTxFile[box_no].DialNumber[0].PIN_Number, (UBYTE)1);
		}
	}
#endif
	InputNumber.WritePosition = GetStringGapPoint(InputNumber.Buffer, NULL);
	InputNumber.CursorPosition = InputNumber.WritePosition;

	while (1) {
		/*--------------------------------*/
		/* ＬＣＤ表示					  */
		/*--------------------------------*/
		DisplayBatchTxDialNumberInput();

		/** キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		if (CheckValidKeyForBatchDial(dial_item, keytype) == FALSE) {
			NackBuzzer();
		}
		else {
#if (PRO_NEW_DIAL_OPR2 == ENABLE)
			/* 直接ダイヤル入力桁数・件数チェック by K.Watanabe 1998/05/07 */
			if (CheckInputDirectDial(keytype) == FALSE) {
				NackBuzzer();
				continue;
			}
#endif

			switch (keytype) {	/* 取り込んだキーのキー種別毎の処理 */
			case AST:		/*   *   */
			case SHARP:		/*   #   */
				InputNumberTenKeySet(key);
				break;
			case NUMBER:	/* 0 - 9 */
				if (InputNumber.Buffer[InputNumber.CursorPosition] == OPR_SPEED_MARK) {
					NackBuzzer();
				}
				else {
					InputNumberTenKeySet(key);
				}
				break;
			case ONETOUCH:	/* ワンタッチキー入力 */
				if (CheckInputOnetouchEnable(key) == TRUE) {
					InputNumberOnetouchSet(key);
				}
				break;
			case SPEED:/* 短縮 */
				InputNumberGroupSpeedMarkSet(key);
				break;
			case REDIAL:	/* リダイアル/ポーズキー */
				InputNumberDialMarkSet(PAUSE_MARK);
				break;
#if !defined(JPN) || (PRO_KEYPANEL == PANEL_ANZU_L)
			case FLASH: /* フラッシュキー */
				InputNumberDialMarkSet(FLASH_MARK);
				break;
#endif
			case FUNCTION:	/* 機能キー */
				/* カーソル移動 ー＞ */
				InputNumberCursorRight();
				break;
			case LEFT_ARROW:
				/* カーソル移動 ＜ー */
				InputNumberCursorLeft();
				break;
			case CLEAR:		/* クリアキー */
				/* データクリア実行 */
				InputNumberDataClear();
				break;
			case DIALMARK:	/* ダイアル記号キー */
				InputNumberDialCharacterSet();
				break;
#if (PRO_KEYPANEL == PANEL_POPLAR_L || PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/07/25 */
			case TONE:		/* トーンキー 		*/	/* 追加 97/11/13 T.Fukumoto */
				InputNumberDialMarkSet(TONE_MARK);
				break;
#endif
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
			case MERCURY:	/* マーキュリーキー *//*1996/09/18 Eguchi */
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
			case STOP:		/* ストップキー */
				CursorOff();
				return (NG);
			case ENTER:		/* セットキー */
				if (BatchDialEnter(dial_item) == OK) {
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

		/* 入力中のダイアル種別をセット */
		if (CheckInputCommandDialNumber() == FALSE) {
			/*バッファが空*/
			dial_item = SYS_EMPTY_DIAL;
		}
		else {
			if (dial_item == SYS_EMPTY_DIAL) {
				data = InputNumber.Buffer[0];
				/* 短縮ダイヤルの時 */
				if (data == OPR_SPEED_MARK) {
					dial_item = SYS_SPEED_DIAL;
				}
				/* ワンタッチダイヤルの時 */
				else if (CheckOnetouchData(data) != OPR_EXCEPT_ONETOUCH) {
					dial_item = SYS_ONETOUCH_DIAL;
				}
				/* 直接ダイヤルの時 */
				else {
					dial_item = SYS_DIRECT_DIAL;
				}
			}
		}
	}
}

/*************************************************************************
	module		:[一括送信ボックスのダイアル番号入力時のキー入力チェック]
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
	date		:[1996/01/10]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE CheckValidKeyForBatchDial(UBYTE dial_item, UBYTE key_type)
{
	UBYTE	ret;

	ret = FALSE;

	switch (key_type) {
	case STOP:
	case KEY_TIME_UP:
	case NO_EFFECT:
	case ENTER:
	case CLEAR:
	case FUNCTION:
	case LEFT_ARROW:
		ret = TRUE;
		break;
	case AST:
	case SHARP:
	case DIALMARK:
#if (PRO_KEYPANEL == PANEL_POPLAR_L || PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/07/25 */
	case TONE:		/* 追加 97/11/13 T.Fukumoto */
#endif
	case REDIAL:
#if !defined(JPN) || (PRO_KEYPANEL == PANEL_ANZU_L)
	case FLASH:
#endif
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	case MERCURY:
#endif
#if defined(DEU)/* for GroundKey '98/03/11 M.HARADA */
	case GROUND:
#endif
#if (PRO_MULTI_LINE == ENABLE)
 #if (PRO_KEYPANEL == PANEL_POPLAR_B)	/* by K.Watanabe 1998/01/16 */
	case COPY_RESET:
 #else
	case HOLD:
 #endif
#endif
		if ((dial_item == SYS_EMPTY_DIAL) || (dial_item == SYS_DIRECT_DIAL)) {
			ret = TRUE;
		}
		break;
	case NUMBER:
		if ((dial_item == SYS_EMPTY_DIAL)
		||	(dial_item == SYS_SPEED_DIAL)
		||	(dial_item == SYS_DIRECT_DIAL)) {
			ret = TRUE;
		}
		break;
	case SPEED:
	case ONETOUCH:
		if (dial_item == SYS_EMPTY_DIAL) {
			ret = TRUE;
		}
		break;
	}
	return (ret);
}

/*************************************************************************
	module		:[一括送信ボックスのダイアル番号入力の最終処理]
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
	date		:[1996/01/10]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE BatchDialEnter(UBYTE dial_item)
{
	UWORD	length;		/* わーく　*/
	UWORD	dial_length;/* だいある番号の長さ(Direct)　*/
	UWORD	pin_length; /* ぴん番号の長さ(Direct)　*/

	length = dial_length = pin_length = 0;

	if (CheckInputCommandDialNumber() == FALSE) { /** 未入力状態でセットキーがおされた場合 */
		/** 正常終了をかえす */
		return (OK);
	}

	/** 入力されている場合、入力データのチェックを行う */
	if (CheckCommandNumber() == NG) {
		NackBuzzer();
		return (NG);
	}

	switch (dial_item) {
	case SYS_ONETOUCH_DIAL:
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
		OPR_Buf.BatTxCtrl.DialNumber.FaxNumber.Onetouch
		 = ChangeNumberToOnetouch(&InputNumber.Buffer[1], ONETOUCH_OFFSET);
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		/* Ａ～Ｚ，ａ～ｚの時 */
		if (CheckOnetouchData(InputNumber.Buffer[0]) == OPR_ONETOUCH_ALPHABET) {
			OPR_Buf.BatTxCtrl.DialNumber.FaxNumber.Onetouch = CMN_OnetouchCodeToOffset(InputNumber.Buffer[0]);
		}
		/* Ｕ１～Ｕ８の時 */
		else {
			OPR_Buf.BatTxCtrl.DialNumber.FaxNumber.Onetouch
			 = ChangeNumberToOnetouch(&InputNumber.Buffer[1], ONETOUCH_OFFSET);
		}
#endif
		break;

	case SYS_SPEED_DIAL:
		length = GetStringGapPoint(&InputNumber.Buffer[1], NULL);
		if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮の時 */
			OPR_Buf.BatTxCtrl.DialNumber.FaxNumber.Speed
			 = CMN_ASC_ToUnsignedInt(&InputNumber.Buffer[1], (UBYTE)length) - OPR_SPEED_DIAL_MIN;
		}
		else {									/* 任意短縮の時 */
			OPR_Buf.BatTxCtrl.DialNumber.FaxNumber.Speed
			 = SetOptionalSpeedStatus(CMN_ASC_ToUnsignedInt(&InputNumber.Buffer[1], (UBYTE)length));
		}
		break;

	case SYS_DIRECT_DIAL:
		length = GetStringGapPoint(&InputNumber.Buffer[0], NULL);
#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/29 */
		dial_length = GetStringGapPoint(&InputNumber.Buffer[0], (UBYTE)OPR_PIN_MARK);
		if (length - (dial_length + 1) >= 0) {
			pin_length  = length - (dial_length + 1);
		}
		else {
			dial_length = length;
			pin_length  = 0;
		}
#else
		dial_length = length;
		pin_length  = 0;
		if (InputNumber.PIN_NumberCheck == YES) {
			/** ダイアル番号はチェック済みなので必ずＰＩＮ番号は入力されている筈 */
			dial_length = GetStringGapPoint(&InputNumber.Buffer[0], (UBYTE)OPR_PIN_MARK);
			pin_length  = length - (dial_length + 1);
		}
#endif
		/* ダイアル番号をセット */
		CMN_ASC_ToBCD_StringNum(OPR_Buf.BatTxCtrl.DialNumber.FaxNumber.Direct, InputNumber.Buffer, (UBYTE)dial_length);
		if (pin_length > 0) {	/* ＰＩＮ番号あり */
			if (pin_length > (SYS_PIN_MAX * 2)) {	/* 8桁以上のＰＩＮ番号 */
				pin_length = (SYS_PIN_MAX * 2);
			}
#if (PRO_PIN_ACCESS == ENABLE)
			/* ＰＩＮ番号をセット */
			CMN_ASC_ToBCD_StringNum(OPR_Buf.BatTxCtrl.DialNumber.PIN_Number,
									&InputNumber.Buffer[dial_length + 1],
									(UBYTE)pin_length);
#endif
		}
		break;
	}

	OPR_Buf.BatTxCtrl.DialNumber.Item = dial_item;
	return (OK);
}

/*************************************************************************
	module		:[ボックスデータ登録中の表示]
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
	date		:[1995/10/12]
	author		:[江口]
*************************************************************************/
void DisplayBatchTxDialNumberInput(void)
{
	/* 上段「ＢＯＸ番号：Ｆａｘ　Ｎｕｍｂｅｒ　　　　　」*/
	/* 下段「入力データ								   」*/

	if (CheckChildErrorDisplayReq() == TRUE) {
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay() == TRUE) {
		return;
	}

	/* 上段文字列 */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	FunctionDisplayBufferHigh[0] = ChangeNumberToASC_Code(OPR_Buf.BatTxCtrl.SelectNumber) + (UBYTE)OPR_BATCH_FILE_MIN;
	FunctionDisplayBufferHigh[1] = ':';
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[2], D2W_FaxNumber, 18 );
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	/* 下段文字列 */
	DisplayCommandNumber();
}

/*************************************************************************
	module		:[一括送信ボックス。送信時刻入力]
	function	:[
		1.
	]
	return		:[]
	common		:[SpecialCommandValue:CommandTime]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/12]
	author		:[江口]
*************************************************************************/
UBYTE EnterBatchTxTime(void)
{
	/* 上段表示を行う */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	FunctionDisplayBufferHigh[0] = ChangeNumberToASC_Code(OPR_Buf.BatTxCtrl.SelectNumber) + (UBYTE)OPR_BATCH_FILE_MIN;
	FunctionDisplayBufferHigh[1] = ':';
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[2], D2W_TranssmissionTime, 18);
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	/* 設定値を取り出す */
	GetProgramTime(SYB_BatchTxFile[OPR_Buf.BatTxCtrl.SelectNumber].ProgramTime);

	/* 時間入力実行 */
	return (ProgramTimeInput());
}

/*************************************************************************
	module		:[一括送信ボックス。名前入力]
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
	date		:[1995/10/12]
	author		:[江口]
*************************************************************************/
UBYTE EnterBatchTxName(void)
{
	UBYTE	box_no;

	box_no = OPR_Buf.BatTxCtrl.SelectNumber;

	/* 初期化 */
	ClearCharacterInput();
	SetCharacterInputMode();	/* 文字入力モード初期化 */
	CMN_StringCopy(CharacterInput.Buffer, SYB_BatchTxFile[box_no].Name);
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;
	CharacterInput.MaxFigure = SYS_BATCH_NAME_MAX - 1;

	/* 上段表示を実行 */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	FunctionDisplayBufferHigh[0] = ChangeNumberToASC_Code(box_no) + (UBYTE)OPR_BATCH_FILE_MIN;
	FunctionDisplayBufferHigh[1] = ':';
	CMN_StringCopyNum(&FunctionDisplayBufferHigh[2], D2W_RemoteName, 18);
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	/* 名前入力実行 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_DISABLE)) {
#else 
	if (NameInput(OPR_KANJI_DISABLE) == OK) {
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		StoreCharacterInputValue(SYB_BatchTxFile[box_no].Name, ASC_DATA_TYPE);
		return (OK);
	}
	return (NG);
}

/*************************************************************************
	module		:[一括送信ボックス。データ登録]
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
	date		:[1995/10/12]
	author		:[江口]
*************************************************************************/
void SetBatchDialAndTime(void)
{
	UBYTE	box_no;
	UBYTE	flag;

	box_no = OPR_Buf.BatTxCtrl.SelectNumber;

	SYB_BatchTxFile[box_no].DialNumber[0].Item = SYS_EMPTY_DIAL;
#if (PRO_PIN_ACCESS == ENABLE)
	/*ＰＩＮ番号もクリアする*/
	CMN_MemorySet(SYB_BatchTxFile[box_no].DialNumber[0].PIN_Number, SYS_PIN_MAX, 0xFF);
#endif
	CMN_MemorySet(SYB_BatchTxFile[box_no].DialNumber[0].FaxNumber.Direct, SYS_DIRECT_DIAL_MAX, 0xFF);/*注*/
	SYB_BatchTxFile[box_no].ProgramTime = 0x00000000UL;
	SYB_BatchTxFile[box_no].ExecTime    = 0x00000000UL;

	/* ダイアル番号のセット */
	SYB_BatchTxFile[box_no].DialNumber[0].Item = OPR_Buf.BatTxCtrl.DialNumber.Item;
	switch (SYB_BatchTxFile[box_no].DialNumber[0].Item) {
	case SYS_ONETOUCH_DIAL:
		SYB_BatchTxFile[box_no].DialNumber[0].FaxNumber.Onetouch = OPR_Buf.BatTxCtrl.DialNumber.FaxNumber.Onetouch;
		break;
	case SYS_SPEED_DIAL:
		SYB_BatchTxFile[box_no].DialNumber[0].FaxNumber.Speed = OPR_Buf.BatTxCtrl.DialNumber.FaxNumber.Speed;
		break;
	case SYS_DIRECT_DIAL:
		/*ダイアル番号のセット*/
		CMN_StringCopyNum(SYB_BatchTxFile[box_no].DialNumber[0].FaxNumber.Direct,
						  OPR_Buf.BatTxCtrl.DialNumber.FaxNumber.Direct,
						  SYS_DIRECT_DIAL_MAX);
#if (PRO_PIN_ACCESS == ENABLE)
		/*ＰＩＮ番号のセット */
		CMN_StringCopyNum(SYB_BatchTxFile[box_no].DialNumber[0].PIN_Number,
						  OPR_Buf.BatTxCtrl.DialNumber.PIN_Number,
						  SYS_PIN_MAX);
#endif
		break;
	}

	/* 送信時刻のセット */
	flag = 0;
	if (SpecialCommandValue.CommandTime & 0x80000000UL) { /* ０日が指定された */
		SpecialCommandValue.CommandTime &= ~0x80000000UL;
		flag = 1;
	}
	/* 分を秒に直す */
	SYB_BatchTxFile[box_no].ProgramTime = SpecialCommandValue.CommandTime*60;
	if (flag) {
		SYB_BatchTxFile[box_no].ProgramTime |= 0x80000000UL;
	}
}

/*************************************************************************
	module		:[一括送信ボックスデータの削除]
	function	:[
		1.選択された一括送信ボックスを初期化する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/12]
	author		:[江口]
*************************************************************************/
void ClearBatchBoxData(void)
{
	UBYTE 	prog_no;
	UBYTE	box_no;

	box_no = OPR_Buf.BatTxCtrl.SelectNumber;

	/** 使用状況を未使用にする */
	SYB_BatchTxFile[box_no].Status = SYS_CMD_EMPTY;

	/** ダイアル種別をダイアルなしにする */
	SYB_BatchTxFile[box_no].DialNumber[0].Item = SYS_EMPTY_DIAL;
	/** ダイアル番号を0xFFでクリアする */
	CMN_MemorySet(SYB_BatchTxFile[box_no].DialNumber[0].FaxNumber.Direct, SYS_DIRECT_DIAL_MAX, 0xFF);/*注*/
#if (PRO_PIN_ACCESS == ENABLE)
	/** ＰＩＮ番号を0xFFでクリアする */
	CMN_MemorySet(SYB_BatchTxFile[box_no].DialNumber[0].PIN_Number, SYS_PIN_MAX, 0xFF);
#endif
	/** 時間をクリアする */
	SYB_BatchTxFile[box_no].ProgramTime = 0x00000000UL;
	SYB_BatchTxFile[box_no].ExecTime    = 0x00000000UL;
	/** インデックス（原稿登録状況）をクリア */
	CMN_WordMemorySet(SYB_BatchTxFile[box_no].IndexNo, SYS_BATCH_INDEX_MAX, SYS_BAT_DOC_EMPTY);
	/** ボックス名をNULLでクリア */
	CMN_MemorySet(SYB_BatchTxFile[box_no].Name, SYS_BATCH_NAME_MAX, NULL);

	for (prog_no = 0; prog_no < SYS_PROGRAM_MAX; prog_no++) {	/* プログラムワンタッチの番号を調べ、クリアする */

#if (PRO_EXT_P_ONETOUCH == ENABLE)
		/* 拡張プログラムワンタッチ対応 By O.Kimoto 1998/09/07 */
		if ((CheckProgramStoreStatus(prog_no) == OPR_PRG_BATCH_TX)
		 && (SYB_ProgramOnetouch[prog_no].EntryData.Command.Option.OptionNumber.BatchNumber == box_no)) {
			ClearProgramOnetouchRecord(prog_no);
		}
#else
		if ((CheckProgramStoreStatus(prog_no) == OPR_PRG_BATCH_TX)
		 && (SYB_ProgramOnetouch[prog_no].Option.OptionNumber.BatchNumber == box_no)) {
			ClearProgramOnetouchRecord(prog_no);
		}
#endif

	}
}

/*************************************************************************
	module		:[一括送信ボックス番号を進める]
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
	date		:[1995/10/12]
	author		:[江口]
*************************************************************************/
void BatchBoxNumberForword(void)
{
	if (OPR_Buf.BatTxCtrl.SelectNumber == SYS_BATCH_FILE_MAX - 1) {
		OPR_Buf.BatTxCtrl.SelectNumber = 0;
	}
	else {
		OPR_Buf.BatTxCtrl.SelectNumber++;
	}
}

/*************************************************************************
	module		:[一括送信ボックス番号を戻す]
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
	date		:[1995/10/12]
	author		:[江口]
*************************************************************************/
void BatchBoxNumberBack(void)
{
	if (OPR_Buf.BatTxCtrl.SelectNumber == 0) {
		OPR_Buf.BatTxCtrl.SelectNumber = SYS_BATCH_FILE_MAX - 1;
	}
	else {
		OPR_Buf.BatTxCtrl.SelectNumber--;
	}
}

/*************************************************************************
	module		:[一括送信ボックスのダイアル番号を取り出す]
	function	:[
		1.一括送信のダイアル番号を編集用のバッファにセットする。
		2.もしＰＩＮ番号がセットされていても、編集用のバッファにはＰＩＮ番号を
		，セットしてはいけない。（ＬＣＤ表示をマスクするため)
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/12]
	author		:[江口,渡辺一章]
*************************************************************************/
void GetBatchTxDialNumber(UBYTE box_no, UBYTE *DST_Buffer, UWORD count)
{
	UBYTE	onetouch;
	UWORD	number;		/* 任意短縮番号 */
	/* PIN番号は表示しない */

	switch (SYB_BatchTxFile[box_no].DialNumber[0].Item) {
	case SYS_EMPTY_DIAL: /* ダイアルデータなし */
		break;
	case SYS_DIRECT_DIAL:/* ダイレクトダイアル：ＡＳＣＩＩでセット */
		CMN_BCD_ToASC_StringNum(DST_Buffer, SYB_BatchTxFile[box_no].DialNumber[0].FaxNumber.Direct, (UBYTE)count);
		break;
	case SYS_ONETOUCH_DIAL:/* ワンタッチ */
		onetouch = CMN_OffsetToOnetouchCode(SYB_BatchTxFile[box_no].DialNumber[0].FaxNumber.Onetouch);
		SetOnetouchCode(DST_Buffer, onetouch, OPR_SET_ONETOUCH_CODE);
		break;
	case SYS_SPEED_DIAL:
		*DST_Buffer++ = OPR_SPEED_MARK;
		if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮 */
			CMN_UnsignedIntToASC(DST_Buffer,
								 SYB_BatchTxFile[box_no].DialNumber[0].FaxNumber.Speed + OPR_SPEED_DIAL_MIN,
								 3,
								 '0');
		}
		else{			/* 任意短縮の時 */
			number = GetRecordFromNumber( SYB_BatchTxFile[box_no].DialNumber[0].FaxNumber.Speed );
			if( number != 0xFFFF ){
				CMN_UnsignedIntToASC(DST_Buffer, number, 3, '0');
			}
			else{
				CMN_MemorySet(DST_Buffer, 3, (UBYTE)0x2A);
			}
		}
		break;
	default:
		break;
	}
}

/*************************************************************************
	module		:[一括送信ボックスの状態を調べる]
	function	:[
		1.
	]
	return		:[]
	common		:[
		OPR_END(0)
		BATCH_BOX_NOT_ENTRY(1)
		BATCH_BOX_EMPTY	(2)
		BATCH_BOX_STORING(3)
		BATCH_BOX_WAITING(4)
		BATCH_BOX_EXECUTE(5)
		BATCH_BOX_ERASED(6)
		BATCH_BOX_POWER_OFF(7)
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/04/19]
	author		:[江口]
*************************************************************************/
UBYTE CheckBatchTxFileStatus(UBYTE box_no)
{
	UBYTE	status;
	struct	SYS_BatchTxData_t *bp;

	bp = &SYB_BatchTxFile[box_no];

	if (bp->DialNumber[0].Item == SYS_EMPTY_DIAL) {
		status = BATCH_BOX_NOT_ENTRY;
	}
	else {
		switch (bp->Status) {
		case SYS_CMD_EMPTY:	/* 未使用 */
			status = BATCH_BOX_EMPTY;
			break;
		case SYS_CMD_SETTING:/* 蓄積中　*/
			status = BATCH_BOX_STORING;
			break;
		case SYS_CMD_WAITING:/* 予約中　*/
			status = BATCH_BOX_WAITING;
			break;
		case SYS_CMD_EXECUTE:/* 実行中（キューに展開すみ)*/
			status = BATCH_BOX_EXECUTE;
			break;
		case SYS_CMD_ERASED: /* 消去すみ、消去中 */
			status = BATCH_BOX_ERASED;
			break;
		case SYS_CMD_POWER_OFF:/* 電源断 */
			status = BATCH_BOX_POWER_OFF;
			break;
		default:
			break;
		}
	}
	return (status);
}
#endif	/* (PRO_BATCH_TX == ENABLE) */
