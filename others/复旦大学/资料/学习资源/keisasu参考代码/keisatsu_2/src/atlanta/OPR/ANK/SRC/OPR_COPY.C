/************************************************************************
*	System		: POPLAR_L/ANZU_L
*	File Name	: OPR_COPY.C
*	Author		: 渡辺一章
*	Date		: 1996/10/18
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: コピーオペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\sysmcopy.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L)
#include	"\src\atlanta\define\uni_pro.h"		/* by K.Watanabe 1999/08/23 */
#endif

/* Prototype
#if (PRO_COPY_FAX_MODE == DISABLE)
void	CopyKeyOperation(void);
UBYTE	InputMultiCopyReserveNumber(void);
void	DisplayCopyNumberInput(void);
void	MultiCopyOperation(void);
UBYTE	GetMultiCopyFile(void);
void	SetMultiCopyFile(void);
#endif	/ (PRO_COPY_FAX_MODE == DISABLE) /
*/

#if (PRO_COPY_FAX_MODE == DISABLE)
/*************************************************************************
	module		:[コピー処理]
	function	:[
		1.コピーキーが押された時の処理を行います
		2.スキャン可能かチェックします
		3.可能であれば部数入力を行います
		4.不可能であれはカーソルをOFFして終了します。
		5.部数入力後、マルチコピーオペレーションを実行します

		1.ダイヤル番号入力中・同報キーが押されている・応用通信キーが押されている時は、
		　コピーモードには移行できません。
		2.マルチコピーオペレーションを実行します。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ANZUにはスキャナコピーがないことを前提としています。]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/14]
	author		:[江口,渡辺一章]
*************************************************************************/
void CopyKeyOperation(void)
{
	/* 優先モードをＦｉｎｅにする。1996/08/30　Eguchi */
	UBYTE	primary_mode;

#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	/*-------------------------*/
	/** コピー禁止中は、不可能 */
	/**  97/11/13 T.Fukumoto   */
	/*-------------------------*/
	if (CHK_CopyProtectON()) {
		NackBuzzer();
		OPR_ChildErrorFlag = COPY_PROTECT_ERROR;			/* "ｺﾋﾟｰｷﾝｼ ﾁｭｳﾃﾞｽ      " */
		return;
	}
#endif

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* Added by SMuratec 李 2004/4/15 */
 #if 0 /* QAT修正：コピー予約可能 By SMuratec 李 2004/11/15 */
	if ( SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY ) {
		NackBuzzer();
		return;
	}
 #else
	if (IsScanReserved ) {
		NackBuzzer();
		return;
	}
	else if ( SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY ) {
		IsScanTx = TRUE;
	}
 #endif
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
	/*-----------------------*/
	/** スキャン可能か調べる */
	/*-----------------------*/
#if (0)	/* Add By O.Kimoto 1999/07/19 */
** 	if ((CheckScanStartEnable(OPR_DOC_SET_CHK_ONLY) != OPR_SCAN_ENABLE) || (CheckMemoryOver() == TRUE)) [
#else
	if ((CheckScanStartEnable(OPR_DOC_SET_CHK_ONLY) != OPR_SCAN_ENABLE) 
		|| (CheckMemoryOver() == TRUE)
		|| (CheckScanDisableCondition() == TRUE)) {
#endif

		/** スキャン不可能 */
		NackBuzzer();
		return;
	}

#if (PRO_PRINT_TYPE != THERMAL)	/* Add By H.Fujimura 1998/12/28 */
 /*#if (PRO_KEYPANEL == PANEL_POPLAR_L) 1999/11/15 Y.Murata 条件変更 */	/* by K.Watanabe 1999/08/23 */
 #if defined(POPLAR_L)	/* 条件変更 NTTは関係ない */
	/* ポプラＬのコピー画質の初期値を、ユニークＳＷにて持たす様にします */
	/* 上記修正ミスしてました。By Y.Suzuki 1900/04/14 */
	if (CHK_UNI_SelectableCopyMode()) {/* By Y.Suzuki 1999/11/29 */
		SYB_ModeSw = CHK_UNI_CopyPrimaryMode();
		ModeLedOn();
	}
	/* 以下を追加します。Y.Suzuki 2000/04/14 */
	else {
		primary_mode = CHK_PrimaryMode();
		if ((primary_mode == SYS_NORMAL) && (primary_mode == SYB_ModeSw)) {
			SYB_ModeSw = SYS_FINE;
			ModeLedOn();
		}
	}
	/*ここまで Y.Suzuki 2000/04/14 */
 #else
  #if defined(POPLAR_F)
	#if defined(JP1)
		/* 新Ｖ７４０ */
		if (CHK_UNI_SelectableCopyMode()) {
			primary_mode = CHK_UNI_CopyPrimaryMode();
			switch (primary_mode) {
			case SYS_NORMAL:
				/* Nothing */
				break;
			case SYS_FINE:
				if (SYB_ModeSw == SYS_NORMAL) {
					SYB_ModeSw = SYS_FINE;
				}
				break;
			case SYS_SFINE:
				if ((SYB_ModeSw == SYS_NORMAL) || (SYB_ModeSw == SYS_FINE)) {
					SYB_ModeSw = SYS_SFINE;
				}
				break;
			case SYS_GRAY64:
				if ((SYB_ModeSw == SYS_NORMAL) || (SYB_ModeSw == SYS_FINE) || (SYB_ModeSw == SYS_SFINE)) {
					SYB_ModeSw = SYS_GRAY64;
				}
				break;
			default:
				SYB_ModeSw = SYS_FINE;
				break;
			}
			ModeLedOn();
		}
		else {
			primary_mode = CHK_PrimaryMode();
			if ((primary_mode == SYS_NORMAL) && (primary_mode == SYB_ModeSw)) {
				SYB_ModeSw = SYS_FINE;
				ModeLedOn();
			}
		}

	#else
		/* 新Ｌ４００ */
		primary_mode = CHK_PrimaryMode();
		if ((primary_mode == SYS_NORMAL) && (primary_mode == SYB_ModeSw)) {
			SYB_ModeSw = SYS_FINE;
			ModeLedOn();
		}

	#endif
  #else
		/* ポプラ／アンスＬ */
		/*-------------------------------------*
		 * 優先モードをＦｉｎｅにする。
		 * 変更依頼ありByＭＢＳ
		 * 1996/08/30 Eguchi 
		 *-------------------------------------*/
		primary_mode = CHK_PrimaryMode();
		if ((primary_mode == SYS_NORMAL) && (primary_mode == SYB_ModeSw)) {
			SYB_ModeSw = SYS_FINE;
			ModeLedOn();
		}

  #endif
 #endif
#endif

	/*-------------------------------------*/
	/** コピー部数の入力処理をおこなう	   */
	/*-------------------------------------*/
	if (InputMultiCopyReserveNumber() == OPR_END) {	/* 部数入力中止（ストップキー) */
		return;
	}

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* QAT修正：コピー予約可能 By SMuratec 李 2004/11/15 */
	if (IsScanReserved ) {
		NackBuzzer();
		return;
	}
	else if ( SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY ) {
		IsScanTx = TRUE;
	}
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

	/*---------------------------------*/
	/** もう一度スキャンできるか調べる */
	/*  部数入力中に原稿引き抜き等で   */
	/*  コピーできない状況になっていな */
	/*  いか調べる					   */
	/*---------------------------------*/
	if ((CheckScanStartEnable(OPR_DOC_SET_CHK_ONLY) != OPR_SCAN_ENABLE)
		|| (CheckMemoryOver() == TRUE)
		|| (CheckScanDisableCondition() == TRUE)
#if defined (HINOKI2) || defined (HINOKI3) || defined (SATSUKI2) || defined (STOCKHM2)/* オーバーヒート状態でのシングルコピーをナックではじく処理追加 2002/02/27 T.Takagi */
		|| ((SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) && (OPR_Buf.CopyCtrl.NumberInputFlag == 0))
#endif
	   )
	{
		/* スキャン不可能 */
		NackBuzzer();
		return;
	}

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* QAT修正：コピー予約可能 By SMuratec 李 2004/11/15 */
	if ( (OPR_Buf.CopyCtrl.NumberInputFlag == 0) /* リアルタイムコピー */
		&& ( (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER)
		 	 || (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_INK)
		 	 || (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM)
		 	 || (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP) )
		) { 
	}
	else if ( !IsScanReserved ) {
		IsScanReserved = TRUE;
		IsCopyReserved = TRUE;
		if ( !ScanReservingOperation() ) {
			IsScanReserved = FALSE;	
			IsCopyReserved = FALSE;
			return;
		}
		else {
			IsScanReserved = FALSE;	
			IsCopyReserved = FALSE;
		}
	}
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

	/*-----------------------------*/
	/** マルチコピー処理実行	   */
	/*-----------------------------*/
	MultiCopyOperation();
}

/*************************************************************************
	module		:[コピー部数入力処理]
	function	:[
		1.コピー部数は1から９９
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/14]
	author		:[江口]
*************************************************************************/
UBYTE InputMultiCopyReserveNumber(void)
{
	UBYTE	key;		/* 入力ｷｰﾃﾞｰﾀ */
	UBYTE	keytype;

	/* ワーク変数初期化 */
	OPR_Buf.CopyCtrl.ReserveNumber = 1;
	OPR_Buf.CopyCtrl.ReserveNumberBuffer[0] = '0';
	OPR_Buf.CopyCtrl.ReserveNumberBuffer[1] = '1';
	OPR_Buf.CopyCtrl.ReserveNumberBuffer[2] = NULL;
	OPR_Buf.CopyCtrl.NumberInputFlag = 0;
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');

	key = OPR_NO_KEY;	/* 前回キー入力値用に初期化します */

	while (1) {
		/** コピー部数入力画面の表示 */
		DisplayCopyNumberInput();

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {	 /**入力キーによる処理*/
		case NUMBER:
			if (OPR_Buf.CopyCtrl.NumberInputFlag == 0) {	/** 部数(数字）未入力 */
				OPR_Buf.CopyCtrl.ReserveNumberBuffer[1] = key;
			}
			else {											/** 部数（数字）入力済み */
				OPR_Buf.CopyCtrl.ReserveNumberBuffer[0] = OPR_Buf.CopyCtrl.ReserveNumberBuffer[1];
				OPR_Buf.CopyCtrl.ReserveNumberBuffer[1] = key;
			}
			OPR_Buf.CopyCtrl.NumberInputFlag = 1;
			break;

		case STOP:					/**ストップキー入力*/
			return (OPR_END);		/**コピーオペレーション終了*/

		case KEY_TIME_UP:			/**キー待ちタイムオーバー*/
#if (PRO_PRINT_TYPE == THERMAL)	/* Add By H.Fujimura 1998/12/28 */
			return (OPR_END);		/**コピーオペレーション終了*/
#endif
		case COPY:					/**コピーキー入力*/
			/* ここの処理はマルチコピーしかないことを前提にしている */
			if (OPR_Buf.CopyCtrl.NumberInputFlag == 0) {	/** 部数入力されていない */	/* シングルコピー時はここを通る。上のコメント間違い 2002/02/27 T.Takagi */
				OPR_Buf.CopyCtrl.ReserveNumber = 1;	/** 部数入力されていない場合は１部のマルチコピーをする */
				return (OPR_CONTINUE);				/** 部数入力終了->コピー開始 */
			}
			else {											/** 部数入力されている */
				/** 部数を計算 */
				OPR_Buf.CopyCtrl.ReserveNumber = (UBYTE)CMN_ASC_ToUnsignedInt(OPR_Buf.CopyCtrl.ReserveNumberBuffer, 2);
				/** 入力値を調べる */
				if (OPR_Buf.CopyCtrl.ReserveNumber == 0) {	/** 0が部数として入力された場合*/
	 				NackBuzzer();
					OPR_ChildErrorFlag = INVALID_COPY_NUMBER_ERROR;	/* "1-99 ｦ ﾄﾞｳｿﾞ        " */
				}
				else {						/** ０以外が部数入力されている */
					return (OPR_CONTINUE);	/** 部数入力終了->コピー開始 */
				}
			}
			break;

		case SINGLE:			SingleKeyOperation(key);
			break;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[コピー部数入力中の画面表示]
	function	:[
		1.
	]
	return		:[]
	common		:[
		D2W_SetCopyUnits
		D2W_CopyEnter
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/09/26]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayCopyNumberInput(void)
{
	if (CheckChildErrorDisplayReq() == TRUE) {	/** エラー等でチャイルド表示要求あり */
		/** 操作エラー表示実行 */
		DisplayChildError();
		return;
	}

	if (CheckChildDisplay() == TRUE) {	/** チャイルド表示中 */
		return;
	}

	CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SetCopyUnits);	/* "ｺﾋﾟｰﾌﾞｽｳ ｦ ﾄﾞｳｿﾞ    " */
	CMN_StringCopy(&FunctionDisplayBufferHigh[18], OPR_Buf.CopyCtrl.ReserveNumberBuffer);
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	/** 下段点滅表示 */
	FlashDisplayStringLow(D2W_CopyStop);	/* "         ｺﾋﾟｰ/ｽﾄｯﾌﾟ " */
}

/*************************************************************************
	module		:[マルチコピー処理]
	function	:[
		1マルチコピーファイルに空きがあるかチェックします
		2.空きがなければ終了します
		3.空きがあれば、必要なデータをセットします
		4.マルチコピー起動のメッセージをメインに送信します
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/14]
	author		:[江口]
*************************************************************************/
void MultiCopyOperation(void)
{
#if (PRO_PRINT_TYPE == THERMAL)	/* 1998/10/07 by T.Soneoka */
#if (0)
** 	/* リアルタイムコピーの起動条件は、「コピー」「コピー」です。
** 	** by O.Kimoto 1998/11/09
** 	*/
**	if (OPR_Buf.CopyCtrl.ReserveNumber == 1) [
#else
	if (OPR_Buf.CopyCtrl.NumberInputFlag == 0) {
#endif
		if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)) { /** プリンタ使用中以外のとき */
			/* 優先モードをＦｉｎｅにする。By H.Fujimura 1998/12/28 */
 #if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
			if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM) {	/** クラス１実行中 */
				ChildDisplayStringLow(D2W_PC_FAX_InUse);		/* "PC-FAX ｼﾖｳﾁｭｳ       " */
				NackBuzzer();
			}
			else {
				if (SYB_ModeSw == SYS_NORMAL) {
					SYB_ModeSw = SYS_FINE;
					ModeLedOn();
				}
				OperationMessageToMain.Message = MSG_REALTIME_COPY;		/* リアルタイムコピー */
				snd_msg( mbxno.MAN_Task, &OperationMessageToMain );
				MainTaskExecWait();
			}
 #else
			if (SYB_ModeSw == SYS_NORMAL) {
				SYB_ModeSw = SYS_FINE;
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
				ModeLedOn();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
			}
#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* Modify by SMuratec 李 2004/06/16 */
			if (SYB_ModeSw == SYS_NORMAL || SYB_ModeSw == SYS_FINE ) {
				SYB_ModeSw = SYS_SFINE;
			}
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
			OperationMessageToMain.Message = MSG_REALTIME_COPY;		/* リアルタイムコピー */
			snd_msg( mbxno.MAN_Task, &OperationMessageToMain );
			MainTaskExecWait();
 #endif
		} else {
			OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;
			NackBuzzer();
		}
	} else {
		if (GetMultiCopyFile() < SYS_MULTI_COPY_MAX) { /** マルチコピー管理テーブルの確保 */
			/** 確保マルチコピー管理テーブルにデータをセット */
			SetMultiCopyFile();

			/**メインタスクにマルチコピー起動メッセージを送信*/
			OperationMessageToMain.Message= MSG_STORE_MULTI_COPY_DOC;
			snd_msg( mbxno.MAN_Task, &OperationMessageToMain );
			MainTaskExecWait();
		}
		else {
			NackBuzzer();
		}
	}
#else
	if (GetMultiCopyFile() < SYS_MULTI_COPY_MAX) { /** マルチコピー管理テーブルの確保 */
		/** 確保マルチコピー管理テーブルにデータをセット */
		SetMultiCopyFile();

		/**メインタスクにマルチコピー起動メッセージを送信*/
		OperationMessageToMain.Message= MSG_STORE_MULTI_COPY_DOC;
		snd_msg( mbxno.MAN_Task, &OperationMessageToMain );
		MainTaskExecWait();
	}
	else {
		NackBuzzer();
	}
#endif
}

/*************************************************************************
	module		:[マルチコピー管理テーブルを確保する。]
	function	:[
		1.マルチコピー管理テーブルの空きをサーチする。
		2.空き領域があれば確保する。
	]
	return		:[0～SYS_MULTI_COPY_MAX：管理テーブル番号]
	common		:[
		SYB_MultiCopyFile
		SYB_MultiCopyWritePoint
	]
	condition	:[]
	comment		:[SYB_MultiCopyFileはリング形式になっている]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/09/26]
	author		:[江口]
*************************************************************************/
UBYTE GetMultiCopyFile(void)
{
	UBYTE	count;

	for (count = 0; count < SYS_MULTI_COPY_MAX; count++) { /* 管理テーブルを一周するまで */
		if (SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Status == SYS_MCOPY_EMPTY) { /* 空き */
			SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Status = SYS_MCOPY_STORE;  /* 確保する */

			return (SYB_MultiCopyWritePoint); /* 確保した管理テーブルの番号を返す */
		}
		else {
			SYB_MultiCopyWritePoint++;
			if (SYB_MultiCopyWritePoint >= SYS_MULTI_COPY_MAX) {
				SYB_MultiCopyWritePoint = 0;
			}
		}
	}
	return (SYS_MULTI_COPY_MAX); /* 確保できない */

}

/*************************************************************************
	module		:[マルチコピー管理テーブルにデータをセット]
	function	:[
		1.確保済みのマルチコピー管理テーブルに以下のデータをセット。
　		2.コピー部数のセット。
		3.カセットをセット
		4.ソーティングコピー設定のセット
		5.縮小率のセット
	]
	return		:[なし]
	common		:[
		SYB_MultiCopyFile
		SYB_MultiCopyWritePoint
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/09/26]
	author		:[江口]
*************************************************************************/
void SetMultiCopyFile(void)
{
	/** コピー部数をセット */
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].ReserveNumber = OPR_Buf.CopyCtrl.ReserveNumber;

	/** 記録紙カセットをセット */
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Cassette = SYS_AUTO_CASSETTE;/*自動選択*/

 #if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
 	/* ポプラＬでソートノンソートの切り替え使用につきコメントを削除した 1997/11/13  By T.Yamaguchi */
	/** ソーティングコピー設定をセット */
	if (CHK_NonSortCopy()) {
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].SortType = SYS_NONE_SORT;
	}
	else {
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].SortType = SYS_SORT;
	}
 #else
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].SortType = SYS_SORT; /* 1996/05/24 Eguchi */
 #endif

	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].ScanType = SYS_ADF_SCAN;	/* By M.Tachibana 1997/12/27 */

	/** 縮小率をセット */
	switch (CHK_CopyFixedReduction()) {
	case 0:	/** 自動縮小 */
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Reduction = SYS_AUTO_REDUCTION;
		break;
	case 1:	/** １００％ */
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Reduction = 100;
		break;
	case 2:	/** ９７％   */
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Reduction = 97;
		break;
	case 3:	/** ９１％   */
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Reduction = 91;
		break;
	case 4:	/** ８１％   */
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Reduction = 81;
		break;
	case 5:	/** ７５％   */
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Reduction = 75;
		break;
	}
}

#endif	/* (PRO_COPY_FAX_MODE == DISABLE) */
