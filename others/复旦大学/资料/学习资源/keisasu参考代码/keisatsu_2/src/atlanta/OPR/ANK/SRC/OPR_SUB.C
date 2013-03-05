/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_SUB.C
*	Author		: 渡辺一章
*	Date		: 1996/10/23
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: オペレーションサブルーチン集
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\lst_def.h"
#include	"\src\atlanta\define\scn_def.h"		/* T.Nose 1997/08/11 */
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\sysexec.h"
#include	"\src\atlanta\define\sysprint.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\atlanta\define\man_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_v\scn_data.h"	/* T.Nose 1997/08/11 */
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#include	"\src\atlanta\ext_v\cmn_tbl.h"
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\satsuki2\define\scn_pro.h"
#include	"\src\atlanta\satsuki2\define\scn_def.h"
 #elif defined(STOCKHM2)
#include	"\src\atlanta\stockhm2\define\scn_pro.h"
#include	"\src\atlanta\stockhm2\define\scn_def.h"
 #else
#include	"\src\atlanta\hinoki\define\scn_pro.h"
#include	"\src\atlanta\hinoki\define\scn_def.h"
 #endif
#include	"\src\atlanta\define\unisw_c.h"	/* added by H.Hirao 1999/02/19 */
#endif
#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif

#if (PRO_MULTI_LINE == ENABLE)	/* 1997/06/23 Y.Matsukuma	*/
#include	"\src\atlanta\define\sys_line.h"
#include	"\src\atlanta\define\mlt_pro.h"
#endif

#if (PRO_CONTINUOUS_POLLING == ENABLE)
#include	"\src\atlanta\define\syscntpl.h"
#endif

#if (PRO_PRINT_TYPE == LASER)	/* F100デュアル動作の制限対策 1997/12/26 M.Kotani */
#include	"\src\atlanta\prt\sp322\define\prn_pro.h"
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B)	/* by K.Watanabe 1998/03/05 */
#include	"\src\atlanta\define\mntsw_i.h"
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/28 */
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\hinoki\define\m_param.h"
#include	"\src\atlanta\ext_v\man_data.h"
#endif 		/* End of (defined (KEISATSU)) */

/* Prototype
void	OPR_Initial(void);
UBYTE   CheckReservedCommandExist(void);
UBYTE	CheckReservedBatchExist(void);
UBYTE	FigureCalculation(UWORD);
void	MainTaskExecWait(void);
void	OPR_SubMessageReceiveTask(void);
void	FinalMemoryPrintOperation(UBYTE, UWORD, UBYTE);
UBYTE	CheckMemDocPrinting(UBYTE, UWORD);
UBYTE	CheckMemDocStoring(UBYTE, UWORD);
void	FinalListPrintOperation(UBYTE);
UWORD	GetStringGapPoint(UBYTE *, UBYTE);
UBYTE	GetBCD_StringLength(UBYTE *);
UBYTE	CheckAndGetSubDialEmptyArea(void);
UBYTE	SetToCheckBuffer(UBYTE *, UBYTE);
UBYTE	CheckMaxFigureOver(UBYTE);
UBYTE	CheckInputRangeOver(UWORD, UWORD);
UBYTE	CheckNumberOnlyInput(void);
UBYTE	CheckNumberFigureRange(UBYTE, UWORD, UWORD);
UBYTE	CheckDirectDialNumberInput(void);
UBYTE	CheckInputDialMarkOnly(void);
UBYTE	CheckCountryDialNumber(void);
UBYTE	CheckGroupDialStoreStatus(UBYTE);
UBYTE	ErrorPositionSet(void);
UBYTE	CheckCommandNumber(void);
void	ConvertAstToPinMark(void);
UBYTE	CheckOnetouchPinNumberStore(UBYTE);
UBYTE	CheckSpeedPinNumberStore(UBYTE);
UBYTE	CheckGroupPinNumberStore(UBYTE);
#if (PRO_PIN_ACCESS == ENABLE)
UBYTE	CheckProgramPinNumberStore(UBYTE);
#endif
UBYTE	FinalBroadcastCheck(UBYTE);
UBYTE	CheckScanStartEnable(UBYTE);
#if (PRO_FBS == ENABLE)
UBYTE	BookDocSizeSetOperation(UBYTE);
#endif
UBYTE	CheckPrintOperationEnable(void);
UBYTE	ClearCompleteDisplayOperation(UBYTE *);
UBYTE	ChildCompleteOperation(void);
UBYTE	CheckProtectPasscodeSet(void);
UBYTE	ChangeNumberToASC_Code(UBYTE);
#if (PRO_KEYPANEL == PANEL_ANZU_L)
UBYTE	GetOnetouchSideCode(UBYTE);
#endif
UBYTE	ChangeNumberToOnetouch(UBYTE *, UBYTE);
UBYTE	ChangeASC_CodeToNumber(UBYTE);
UBYTE	CheckFaxComExecute(void);
UBYTE	CheckLeapYear(UBYTE);
UBYTE	GetDayFromMonth(UBYTE, UBYTE);
UBYTE	CheckMemoryOver(void);
#if (PRO_MULTI_LINE == ENABLE)	1997/06/23 Y.Matsukuma
UBYTE	InputPbxCheck(UBYTE);
UBYTE	MultiLineBusy(void);
UBYTE	MultiOptAllLineBusy(void);
#endif
UBYTE	CheckReservedContPollingExist(void);
void	SetDialDataToDispBuffer(UBYTE, struct SYS_CommandData_t *, UBYTE *);
UBYTE	CheckSettingDataLength(UBYTE, UWORD);
UBYTE	CheckOnetouchData(UBYTE);
UBYTE	SetOnetouchCode(UBYTE *, UBYTE, UBYTE);
UBYTE	CheckProgramOnetouchData(UBYTE);
UBYTE	CheckTelephoneUsing(void);
UBYTE	GetPaperSize(UBYTE);
void	CheckOperationValid(UBYTE *);
UBYTE	Check_BCD_StringCompare(UBYTE *, UBYTE *, UBYTE);
#if (PRO_KEYPANEL == PANEL_ANZU_L)
UBYTE	ChangeOnetouchCode(UWORD);
#endif
UBYTE	CheckCopyDocStore(void);
UBYTE	CheckExceptCopyDocStore(void);
UBYTE	ConfirmKeyInputOperation(UBYTE *, UBYTE *, UBYTE, UBYTE);
#if defined(FRA)
UBYTE	CheckSameNumber();
UBYTE	CheckBCDCompare(UBYTE *, UBYTE *, UBYTE);
#endif
#if (PRO_DIAL_NAME_DISP == ENABLE) || (PRO_NEW_DIAL_OPR == ENABLE)
UBYTE	GetCursorPositionDataKind(UBYTE, UWORD *, UWORD *);
#endif
#if (PRO_DIAL_NAME_DISP == ENABLE)
UBYTE	SetOnetouchSpeedDialName(UBYTE *, UBYTE, UWORD);
#endif
*/

UBYTE CHK_OPRSameDocumentAccess(UBYTE CommandKind, UBYTE CommandNumber);	/* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */

/*************************************************************************
	module		:[オペレーション初期化処理]
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
	date		:[1995/05/26]
	author		:[江口,渡辺一章]
*************************************************************************/
void OPR_Initial(void)
{
	NewKeyCode = OPR_NO_KEY;
	OldKeyCode = OPR_NO_KEY;
	HitKeyTime = 0;
	NoKeyTime = 0;
	NoKeyFlag = 0;
	KeyPortNumber = 0;
	OPR_InhibitKeyScan = 0;
#if (PRO_CONT_KEY_INPUT == ENABLE)
	ContinuousKeyHit = FALSE;
	ContinuousKeyTimer = 0;
	ContinuousKeyInputEnable = TRUE;
#endif

	/** ＴＩＤ初期化 */
	tskno_OPR_BuzzerTask     = 0xffff;					/* ブザータスク								*/
	tskno_OPR_DispFlashTask  = 0xffff;					/* 点滅表示制御用タスク						*/
	tskno_OPR_SheetCheckTask = 0xffff;					/* シート切り替えチェックタスク				*/
	tskno_OPR_KeyTimerTask   = 0xffff;					/* キー待ち用タイマータスク					*/
	tskno_OPR_ChildTimerTask = 0xffff;					/* チャイルド表示用タイマータスク			*/
	tskno_OPR_ParamDispTask  = 0xffff;					/* コピーパラメーター優先表示用タイマータスク*/

	/** タイマー値初期化 */
/*	GetKeyTimer.Time        = key_wait_time;			/  キー待ち時間は関数の中でセットします		*/
	GetKeyTimer.SendMBX     = mbxno.OPR_Task;
	GetKeyTimer.ReturnValue = MSG_GET_KEY_TIMEUP;

/*	ChildTimer.Time        = 200;						/  チャイルド表示時間は起動前にセットします	*/
	ChildTimer.SendMBX     = mbxno.OPR_Task;
	ChildTimer.ReturnValue = MSG_CHILD_TIMEUP;

#if (PRO_COPY_FAX_MODE == ENABLE)
	ParamDispTimer.Time        = 300;					/* コピーパラメーター優先表示時間（３秒）	*/
	ParamDispTimer.SendMBX     = mbxno.OPR_Task;
	ParamDispTimer.ReturnValue = MSG_PARAM_DISP_TIMEUP;
#endif

	/** 表示用バッファのクリア */
	CMN_MemorySetNULL(SubTitleDisplayBuffer,     OPR_DISPLAY_MAX, ' ');
	CMN_MemorySetNULL(DisplayBufferHigh,         OPR_DISPLAY_MAX, ' ');
	CMN_MemorySetNULL(DisplayBufferLow,          OPR_DISPLAY_MAX, ' ');
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_MemorySetNULL(FunctionDisplayBufferLow,  OPR_DISPLAY_MAX, ' ');

	/** 各種フラグの初期化 */
	OPR_TelBookTelephoneFlag = 0;						/* 電話帳による電話要求						*/
	OPR_BatchTxEnableFlag    = FALSE;					/* 一括送信許可フラグ						*/
	OPR_ChildErrorFlag       = OPR_NO_ERROR;			/* 操作エラー番号							*/
	SettingCommandFileNumber = NO_SETTING_COMMAND_FILE;	/* 登録中のコマンドファイル番号				*/
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/11/13 Y.Matsukuma */
	IsIdleDisplay            = 0;						/* アイドルカウンタ表示フラグ				*/
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
 #if (PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By H.Fujimura 1999/04/02 */
	OPR_SpecialDoctorReportFlag = 0;					/* 医師会特ＲＯＭ用メッセージ送信フラグ		*/
 #endif
#endif

	/** ブーリアン変数の初期化 */
	IsFlashDisplayHigh = FALSE;							/* 上段点滅表示制御							*/
	IsFlashDisplayLow  = FALSE;							/* 下段点滅表示制御							*/
#if (PRO_FBS == ENABLE)
	IsBookDocSizeSet   = FALSE;							/* ブック原稿サイズが設定されたかどうか		*/
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1997/11/25 */
	IsSettingDensity   = FALSE;							/* 濃度設定中のチェック用					*/
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* By H.Fujimura 1999/02/17 */
	IsSingleKeyOperation = TRUE;						/* 単一オペレーション有効					*/
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec H.C.H 2003/11/07 */
	IsDocumentSet = FALSE;
	IsDocumentStoring = FALSE;
#endif


#if (0)	/* OPR_Task()の中で行います */
//	/** コピーモード用変数の初期化 */
//	CopyParameterClear();
#endif

	/* 枚数指定オペレーション実行済みフラグを削除し、ページ枚数で兼用する */
	SpecialCommandValue.Page = 0;						/* ページ枚数								*/

#if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/16 */
	/* ＣＧＲＡＭデータ書き込み制御用 */
	OPR_Writed_CGRAM_Address = NULL;					/* 現在書き込まれているＣＧＲＡＭのアドレス	*/
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)	/* by K.Watanabe 1997/11/27 */
	/* 濃度設定表示中に使用する濃度変更キー */
	OPR_ChangeDensityKey = NO_KEYCODE;					/* 濃度変更キー								*/
#endif

#if (PRO_COPY_FAX_MODE == ENABLE)	/* by K.Watanabe 1997/12/05 */
	OPR_CopyParamCheck = OPR_NO_PARAM_CHK;				/* 用紙・倍率確認状態						*/
#endif
}

/*************************************************************************
	module		:[通信予約コマンドの有無のチェック]
	function	:[
		1.
	]
	return		:[
				TRUE:予約あり
				FALSE:予約なし
				]
	common		:[
				SYB_CommandFile
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/26]
	author		:[江口]
*************************************************************************/
UBYTE CheckReservedCommandExist(void)
{
	UBYTE	com_file;
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	exec_file;
#endif
	UWORD	exec_file;

	for (com_file = 0; com_file < SYS_COM_FILE_MAX; com_file++) {
		/** 予約中のコマンドの有無を調べる */
		if (SYB_CommandFile[com_file].Status == SYS_CMD_WAITING) {
			return (TRUE);
		}
		/** 実行待ちのコマンドの有無を調べる */
		if (SYB_CommandFile[com_file].Status == SYS_CMD_EXECUTE) {
			for (exec_file = 0; exec_file < SYS_EXEC_QUEUE_MAX; exec_file++) {
				if ((SYB_ExecQueue[exec_file].Status == SYS_EXEC_WAITING)
				||	(SYB_ExecQueue[exec_file].Status == SYS_EXEC_FORWARD_WAITING)) {
					if ((SYB_ExecQueue[exec_file].Kind == SYS_COMMAND_TRX)
					&&	(SYB_ExecQueue[exec_file].Number.Command == com_file))  {
						return (TRUE);
					}
				}
			}
		}
	}
    return (FALSE);
}

/*************************************************************************
	module		:[実行中のコマンドの有無を調べる]
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
	date		:[1996/06/05]
	author		:[江口]
*************************************************************************/
UBYTE CheckExecuteCommandExist(void)
{
	UBYTE	com_file;

	for (com_file = 0; com_file < SYS_COM_FILE_MAX; com_file++) {
		if (CheckExecuteCommand(SYS_COMMAND_TRX, com_file) < SYS_EXEC_QUEUE_MAX) {
			return (TRUE);
		}
	}
	return (FALSE);
}

/*************************************************************************
	module		:[リダイアル待ちのキューの有無を調べる]
	function	:[
		1.実行待ち状態のキューのなかにリダイアル待ちのキューの有無を調べる
		2.リダイアル待ちかどうかはリダイアルタイムがセットされているかいないかで判断する
	]
	return		:[
					TRUE:リダイアル待ちキューあり
					FALSE:リダイアル待ちキューなし
				]
	common		:[]
	condition	:[]
	comment		:[コマンドが存在することを確認してから]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/06/10]
	author		:[江口]
*************************************************************************/
UBYTE CheckRedialQueueExist(void)
{
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	queue_no;
#endif
	UWORD	queue_no;

	for (queue_no = 0; queue_no < SYS_EXEC_QUEUE_MAX; queue_no++) {
		if ((SYB_ExecQueue[queue_no].Status == SYS_EXEC_WAITING)
		||	(SYB_ExecQueue[queue_no].Status == SYS_EXEC_FORWARD_WAITING)) {
			if (SYB_ExecQueue[queue_no].RedialTime > 0) {
#if defined(KEISATSU)	/* 警察FAX DVT_ID77 Modify by SMuratec 夏 2005/12/20 */				
				if (((SYB_ExecQueueKeisatsu[queue_no].Line == SYS_LINE_KANYU) && CheckIsKanyuLine()) ||
					((SYB_ExecQueueKeisatsu[queue_no].Line != SYS_LINE_KANYU) && !CheckIsKanyuLine())) {
					return (TRUE);
				}
#else
				return (TRUE);
#endif
			}
		}
	}
	return (FALSE);
}

/*************************************************************************
	module		:[一括送信コマンドの有無をチェック]
	function	:[
		1.
	]
	return		:[
				TRUE:予約あり
				FALSE:予約なし
				]
	common		:[SYB_BatchTxFile]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/04]
	author		:[江口]
*************************************************************************/
UBYTE CheckReservedBatchExist(void)
{
#if (PRO_BATCH_TX == ENABLE)
	UBYTE	batch_file;
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	exec_file;
#endif
	UWORD	exec_file;

	for (batch_file = 0; batch_file < SYS_BATCH_FILE_MAX; batch_file++) {
		/** 予約中のコマンドの有無を調べる */
		if (SYB_BatchTxFile[batch_file].Status == SYS_CMD_WAITING) {
			return (TRUE);
		}
		/** 実行待ちのコマンドの有無を調べる */
		if (SYB_BatchTxFile[batch_file].Status == SYS_CMD_EXECUTE) {
			for (exec_file = 0; exec_file < SYS_EXEC_QUEUE_MAX; exec_file++) {
				if ((SYB_ExecQueue[exec_file].Status == SYS_EXEC_WAITING)
				||	(SYB_ExecQueue[exec_file].Status == SYS_EXEC_FORWARD_WAITING)) {
					if ((SYB_ExecQueue[exec_file].Kind == SYS_BATCH_TX)
					&&	(SYB_ExecQueue[exec_file].Number.Batch == batch_file))  {
						return (TRUE);
					}
				}
			}
		}
	}
	return (FALSE);
#else
	return (FALSE);
#endif	/* (PRO_BATCH_TX == ENABLE) */
}

#if (PRO_BATCH_TX_RESERVE_LIST == ENABLE) /* By H.Fujimura 1999/01/06 */
/*************************************************************************
	module		:[実行中の一括送信コマンドの有無を調べる]
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
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
UBYTE CheckExecuteBatchExist(void)
{
#if (PRO_BATCH_TX == ENABLE)
	UBYTE	batch_file;

	for (batch_file = 0; batch_file < SYS_BATCH_FILE_MAX; batch_file++) {
		if (CheckExecuteCommand(SYS_BATCH_TX, batch_file) < SYS_EXEC_QUEUE_MAX) {
			return (TRUE);
		}
	}
	return (FALSE);
#else
	return (FALSE);
#endif	/* (PRO_BATCH_TX == ENABLE) */
}
#endif	/* (PRO_BATCH_TX_RESERVE_LIST == ENABLE) */

/*************************************************************************
	module		:[桁数計算]
	function	:[
		1.指定されたUnsigned Int型の数値の桁数を計算する
	]
	return		:[桁数]
	common		:[]
	condition	:[]
	comment		:[Ｈ８から移植]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/20]
	author		:[江口]
*************************************************************************/
UBYTE FigureCalculation(UWORD Value)	/*数値*/
{
	UBYTE	figure;		/*桁数*/

	figure = 0;
	while (Value >= 1 ) {
		Value /= 10;
		figure++;
	}
	return(figure);
}

/*************************************************************************
	module		:[メインタスクの実行待ち関数]
	function	:[
					メインタスクの実行待ち関数
					メインタスクにメッセージを送信した後、メインから
					メッセージの返答をまつ.
					キータスクのメッセージは無視.
				]
	common		:[
		mbxno	:
	]
	condition	:[]
	comment		:[メインの処理をV53の方を流用すると、メインとOPRの間に中間タスクが存在し、
				　OPRからのメッセージは直接MANにMANからのメッセージは１度中間タスクを
				　介してOPRに送信されます 1995/04/27 Eguchi
				  中間タスクをどこかのファイルに定義する必要があります
				]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[93/12/02]
	author		:[増田次郎]
*************************************************************************/
void MainTaskExecWait(void)
{
	MESSAGE_t *rx_message;

	while (1) {
		rcv_msg(mbxno.OPR_MAN_MessageTask , &rx_message);
		if ((rx_message->Item    == FROM_MAIN)
		&&	(rx_message->Message == MSG_EXIT)) {
			break;
		}
	}
}

/*************************************************************************
	module		:[メインタスクからオペレーションタスクへのメッセージを中継する]
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
	date		:[1995/01/18]
	author		:[野瀬敏弘]
*************************************************************************/
void OPR_SubMessageReceiveTask(void)
{
	UWORD	msg;
	UWORD	sub_msg;
	MESSAGE_t *MessageControl;
	MESSAGE_t MainTaskMessage;

	while(1) {
		rcv_msg(mbxno.OPR_SubMessageTask, &MessageControl); /** タスクからメッセージ受信 */
		msg = MessageControl->Message;
		sub_msg = MessageControl->SubMessage1;
		snd_msg(mbxno.OPR_Sub_MANTask, &MainTaskMessage);

		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = msg;
		MainTaskMessage.SubMessage1 = sub_msg;
		snd_msg(mbxno.OPR_Task,&MainTaskMessage);
	}
}

/*************************************************************************
	module		:[メモリープリント最終処理]
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
	date		:[1995/07/13]
	author		:[江口,渡辺一章]
*************************************************************************/
void FinalMemoryPrintOperation(UBYTE print_item, UWORD file_number, UBYTE box_number)
{
	UBYTE	command_item;	/* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/02 */
	UBYTE	command_no;		/* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/02 */

	if (CheckPrintOperationEnable() == TRUE) {	/* プリント可能であれば */

#if (PRO_PRINT_TYPE == LASER)	/* F100デュアル動作の制限対策 1997/12/26 M.Kotani */
		if (CMN_CheckF100Model()) {
			if (CheckScannerSending()) {
				OPR_ChildErrorFlag = SCANNER_USE_ERROR;	/* Scanner In Use */
				NackBuzzer();
				return;
			}
		}
#endif

		/* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/02 */
		switch (print_item) {
		case SYS_MEM_POLLING_FILE:
			/* SYB_PollingDocExclusiveFlagの最下位4ﾋﾞｯﾄには回線番号が入っているので、
			** それ以外のビットをチェックして、何も立っていなければ、どこかの回線で
			** 原稿を送信中（ハンドシェーク中）と言うことになる
			*/
			if ((SYB_PollingDocExclusiveFlag & 0xFFF0) == 0x0000) {
				OPR_ChildErrorFlag = LINE_BUSY_ERROR; /** "通信中です"のエラー表示 */
				NackBuzzer();
				return;
			}
			break;
		case SYS_MEM_BATCH_TX_FILE1:
		case SYS_MEM_BATCH_TX_FILE2:
		case SYS_MEM_BATCH_TX_FILE3:
		case SYS_MEM_BATCH_TX_FILE4:
		case SYS_MEM_BATCH_TX_FILE5:
		case SYS_MEM_TX_FILE:
			if (print_item == SYS_MEM_TX_FILE) {
				command_item = SYS_COMMAND_TRX;
				command_no = (UBYTE)file_number;
			}
			else {
				command_item = SYS_BATCH_TX;
				command_no = (UBYTE)(print_item - SYS_MEM_BATCH_TX_FILE1);
			}
			if (!CHK_OPRSameDocumentAccess(command_item, (UBYTE)command_no)) {
				OPR_ChildErrorFlag = LINE_BUSY_ERROR; /** "通信中です"のエラー表示 */
				NackBuzzer();
				return;
			}
			break;
			
		case SYS_MEM_SECURE_RX_FILE:
 			/* 同一ボックスにおいて、プリント処理とプリント起動処理がぶつかると、タスクの優先順位の関係や、メッセージの
 			** 受け渡しの関係で、原稿が存在しないのにプリント起動命令が発行される場合がある。（最悪の場合、白紙が１枚でる。）
 			** よって、上部で原稿の有無は確認しているが、ここで、パスワード入力後再度原稿の有無をチェックするようにする。
 			** by O.Kiomto 1999/03/03
 			*/
			if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) == SYS_IMAGE_PRINT ) {
				OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;
				NackBuzzer();
				return;
			}
			else {

#if (0)
** 	/* 同一ボックスにすでに親展受信原稿がある状態で、さらに受信を行っているとき、
** 	** 既存の受信原稿をプリントしようとすると、「原稿が有りません」となってしまう。
** 	** by O.Kimoto 1999/03/18
** 	*/
** 	/*
** 	** MEM_CountTotalPage()の戻り値は次の通り。原稿の有無確認方法変更。
** 	** 原稿無し：MEM_NO_INDEX(0xFFFF)
** 	** 原稿有り：０以外のページ数
** 	** By S.Kawasaki 1996/08/10
** 	*/
** 	/** 原稿の有無のチェック */
**				if ((SYB_MailBox[file_number].Status != SYS_MAILBOX_RECEIVE)
**				   	|| (MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE,file_number, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX)) {
**					NackBuzzer();
**					OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
**					return;
**				}
#else
				if ((SYB_MailBox[file_number].Status == SYS_MAILBOX_RECEIVING)					/* 親展受信原稿有り */
					|| (SYB_MailBox[file_number].Status == SYS_MAILBOX_RCV_TO_RECEVING)) {		/* 親展受信原稿ありのＢＯＸに受信中の原稿有り */
					NackBuzzer();
					OPR_ChildErrorFlag = BOX_IN_USE_ERROR;	/* "ﾎﾞｯｸｽ ｼﾖｳﾁｭｳ        " */
					return;
				}
				if ((SYB_MailBox[file_number].Status != SYS_MAILBOX_RECEIVE)
					|| (MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE,file_number, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX)) { /** 原稿がない By S.Kawasaki 1996/08/10 */
					NackBuzzer();
					OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
					return;
				}
#endif

			}
			break;

#if (PRO_F_CODE == ENABLE)	/*条件コンパイルが入っていなかったので追加．M.Kotani 1999/11/18*/
		/* バグバグ
		** by O.Kimoto 1999/03/19
		*/
		case SYS_MEM_SUB_BULLETIN_FILE:
		case SYS_MEM_SUB_SECURE_FILE:
			if ((SYB_SubAddressBoxTable[OPR_FcodeData.BoxNumber].DataStatus != SYS_SUB_ADDRESS_BOX_STORED)
				&& (SYB_SubAddressBoxTable[OPR_FcodeData.BoxNumber].DataStatus != SYS_SUB_ADDRESS_BOX_RECEIVE)) {
				/* 選択されたＢＯＸが受信中・送信中・蓄積中・消去中・プリント中の時 */
				NackBuzzer();
				OPR_ChildErrorFlag = BOX_IN_USE_ERROR;			/* "ﾎﾞｯｸｽ ｼﾖｳﾁｭｳ        " */
				return;
			}
			break;

#endif
		}
		/* メモリ送信中の確認プリント不具合（ここまで） By O.Kimoto 1998/09/02 */

		SYS_DocumentPrintItem = print_item;
		SYS_DocumentPrintNo = file_number;

#if (PRO_F_CODE == ENABLE)
		/* サブアドレスＢＯＸ蓄積原稿プリントの時は、ＢＯＸ番号を指定します */
		if ((print_item == SYS_MEM_SUB_BULLETIN_FILE) || (print_item == SYS_MEM_SUB_SECURE_FILE)) {
			SYS_DocumentPrintBoxNumber = box_number;
		}
#endif

		/*OperationMessageToMain.Item = FROM_OPERATION; 1996/07/08 Eguchi */
		OperationMessageToMain.Message = MSG_MEMORY_PRINT;
		snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
		MainTaskExecWait();
	}
}

/*************************************************************************
	module		:[指定された原稿が印字中か調べる]
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
	date		:[1996/05/17]
	author		:[江口]
*************************************************************************/
UBYTE CheckMemDocPrinting(UBYTE item, UWORD number)
{

	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)
	&&  (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)
	&& 	(SYS_DocumentPrintItem 	== item)
	&& 	(SYS_DocumentPrintNo 	== number)) { /** 消去しようとしている原稿が印字中の場合 */
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[指定した原稿を蓄積中か調べる]
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
	date		:[1996/05/17]
	author		:[江口]
*************************************************************************/
UBYTE CheckMemDocStoring(UBYTE item, UWORD number)
{
	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)
	&&	(SYS_MachineStatus[SYS_MACHINE_STATUS]  & SYS_DOC_STORE)
	&&	(SYS_DocumentStoreItem == item)
	&&	(SYS_DocumentStoreNo   == number)) { /** 消去しようとしている原稿が蓄積中 (条件がこれでいいか再確認要1995/10/16)*/
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[リストプリント起動メッセージ送信]
	function	:[
		1.メインタスクにリストプリント起動メッセージを送信する
		2.リストプリント種別は引数でもらう
	]
	return		:[]
	common		:[
				SYS_DocumentPrintItem
				OperationMessage
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/04/04]
	author		:[江口]
*************************************************************************/
void FinalListPrintOperation(UBYTE list_kind)
{
	if (CheckPrintOperationEnable() == TRUE) { /* プリント可能 */
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/* デュアル・トリプル動作の制限対策 1997/12/03 Y.Matsukuma */
		if ((CMN_CheckScanEnable() == FALSE) 
		&& ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_IN) == 0)
		&& ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT) == 0)) {
			OPR_ChildErrorFlag = SCANNER_USE_ERROR;	/* Scanner In Use */
			NackBuzzer();
			return;
		}
#endif
		SYS_DocumentPrintItem = list_kind;
		/*OperationMessageToMain.Item = FROM_OPERATION; 1996/07/08 Eguchi */
		OperationMessageToMain.Message = MSG_LIST_PRINT;
		snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
		MainTaskExecWait();
	}
}

/*************************************************************************
	module		:[最初の','.' ',\0の位置]
	function	:[
		1.与えられた文字列のなかで最初に区切り文字が出てくる位置を求める。
	]
	return		:[位置：与えられた文字列の先頭からのオフセット数（バイト数）]
	common		:[]
	condition	:[文字列の最後は必ずＮＵＬＬであること]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/08/31]
	author		:[江口]
*************************************************************************/
UWORD GetStringGapPoint(UBYTE *SRC_String, UBYTE Period)
{
	UWORD	length;

	/* 検査文字列がワーディングの場合の処理を追加（SelectData()用） by K.Watanabe 1998/08/24 */
	SRC_String = CalculateStringAddress(SRC_String);

	length = 0;
	while ((*SRC_String != NULL) && (*SRC_String != Period)) {	/* ＮＵＬＬ或いは区切りまで */
		length++;
		SRC_String++;
	}
	return (length);
}

/*************************************************************************
	module		:[ＢＣＤ形式のストリングの長さを求める]
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
	date		:[1995/12/13]
	author		:[江口]
*************************************************************************/
UBYTE GetBCD_StringLength(UBYTE *String)
{
	UBYTE	length;
	UBYTE	data;

	length = 0;

	while (1) {
		if (length%2) {/* 奇数 */
			data = (UBYTE)(*String & 0x0F);
		}
		else { /* 偶数 */
			data = (UBYTE)((*String & 0xF0) >> 4);
		}
		if (data == 0x0F) {/* 終了コード */
			break;
		}

		length++;
		if (length%2 == 0) {/*偶数*/
			String++;
		}
	}
	return (length);
}

/*各種チェック関数*/

/*************************************************************************
	module		:[転送番号登録状態のチェック]
	function	:[
		1.転送番号格納エリアに空きがあるか調べる。
	]
	return		:[
				FF:SYB_SubDialに空きなし
				0-9:SYB_SubDialの空き領域のオフセット
				]
	common		:[SYB_SubDial]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/04/13]
	author		:[江口]
*************************************************************************/
UBYTE CheckAndGetSubDialEmptyArea(void)
{
	UBYTE	i;

	for (i = 0; i < SYS_SUB_DIAL_MAX; i++) {
		if ((SYB_SubDial[i][0] & 0xF0) == 0xF0) {	/* 転送先番号が登録されていない*/
			return (i);
		}
	}
	return (0xFF);
}

/*** チェック用のバッファを用意する */
/*************************************************************************
	module		:[チェック対象データを得る]
	function	:[
		1.チェックの対象となるデータをチェック用のバッファに格納する
		2.ＮＵＬＬ又は指定された文字までコピーする
		3.ＮＵＬＬ又は指定された文字はコピーしない
		4.コピーした文字数を上位関数に返す
	]
	return		:[]
	common		:[OPR_CharacterCheckBuffer:チェック用バッファ]
	condition	:[]
	comment		:[セットするデータはチェック用バッファのサイズ以下であることが前提]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/24]
	author		:[江口]
*************************************************************************/
UBYTE SetToCheckBuffer(UBYTE *ASC_String,	/* コピー元 */
					   UBYTE gap_character)	/* コピー終了文字 */
{
	UBYTE	length;

	CMN_MemorySet(OPR_CharacterCheckBuffer, OPR_CHECK_BUFFER_MAX, NULL);

	for (length = 0; length < (UBYTE)(OPR_CHECK_BUFFER_MAX - 1); length++) {
		if ((ASC_String[length] != gap_character) && (ASC_String[length] != NULL)) {
			OPR_CharacterCheckBuffer[length] = ASC_String[length];
		}
		else {
			break;
		}
	}
	return (length);
}

/*************************************************************************
	module		:[桁数オーバーのチェック]
	function	:[
		1.電話番号入力等の桁数チェックを行う
	]
	return		:[
				TRUE:桁数オーバー
				FALSE:桁数内
				]
	common		:[OPR_CharacterCheckBuffer:チェック用バッファ]
	condition	:[チェックする対象となるデータをあらかじめチェック用のバッファにいれておくこと
				  255桁を越えるものはチェックできない]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/24]
	author		:[江口]
*************************************************************************/
UBYTE CheckMaxFigureOver(UBYTE max_figure)
{
	if (max_figure == NULL) { /* 桁数チェック不要 */
		return (FALSE);
	}
	if (CMN_StringLength(OPR_CharacterCheckBuffer) > max_figure) {
		OPR_CharacterCheckPoint = max_figure;
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[入力範囲のチェック]
	function	:[
		1.入力された値があらかじめ定められている範囲に収まっているかチェック
	]
	return		:[]
	common		:[OPR_CharacterCheckBuffer:チェック用バッファ]
	condition	:[チェックする対象となるデータをあらかじめチェック用のバッファにいれておくこと]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/24]
	author		:[江口]
*************************************************************************/
UBYTE CheckInputRangeOver(UWORD min_value, UWORD max_value)
{
	UWORD	data;
	UBYTE	length;

	if ((min_value == max_value)
	&&	(max_value == NULL)) { /* 範囲チェック不要 */
		return (FALSE);
	}
	OPR_CharacterCheckPoint = 0;
	length = CMN_StringLength(OPR_CharacterCheckBuffer);
	data = CMN_ASC_ToUnsignedInt(OPR_CharacterCheckBuffer, length);

	if ((data >= min_value)
	&&	(data <= max_value)) {
		return (FALSE);
	}
	return (TRUE);
}

/*************************************************************************
	module		:[数字のみの入力のチェック]
	function	:[
		1.数字のみ入力されているか調べる
	]
	return		:[]
	common		:[OPR_CharacterCheckBuffer:チェック用バッファ]
	condition	:[チェックする対象となるデータをあらかじめチェック用のバッファにいれておくこと
				  データが入力されているかあらかじめチェックしてからコールすること]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/24]
	author		:[江口]
*************************************************************************/
UBYTE CheckNumberOnlyInput(void)
{
	OPR_CharacterCheckPoint = 0; /* チェック位置（エラー箇所も保持)*/

	while (OPR_CharacterCheckPoint < (UBYTE)(OPR_CHECK_BUFFER_MAX - 1)) {
		if (OPR_CharacterCheckBuffer[OPR_CharacterCheckPoint] == NULL) {
			return (TRUE);
		}
		if (CMN_isdigit(OPR_CharacterCheckBuffer[OPR_CharacterCheckPoint]) == 0) {
			return (FALSE);
		}
		OPR_CharacterCheckPoint++;
	}
	return (TRUE);
}

/*************************************************************************
	module		:[数字入力のチェック]
	function	:[
		1.数字のみの入力、桁数オーバー、入力範囲オーバーをチェック
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/30]
	author		:[江口]
*************************************************************************/
UBYTE CheckNumberFigureRange(UBYTE max_figure,	/*桁数*/
							 UWORD minimum,		/*最小値*/
							 UWORD maximum)		/*最大値*/
{
	/** 数字以外が入力されていないがチェックする */
	if (CheckNumberOnlyInput() == FALSE) {
		return (INVALID_NUMBER_ERROR);
	}

	if (CheckMaxFigureOver(max_figure) == TRUE) {			/* 桁数オーバー */
		return (TOO_MANY_DIGITS_ERROR);
	}

	if (CheckInputRangeOver(minimum , maximum) == TRUE) {	/* 範囲外の数値 */
		return (INPUT_RANGE_OVER_ERROR);
	}

	return (OPR_NO_ERROR);
}

/*************************************************************************
	module		:[ダイレクトダイアル入力チェック]
	function	:[
		1.テンキー入力されたダイアルデータの入力値チェック
		2.ワンタッチ／短縮の電話番号、転送番号のチェックに使用。
		3.コマンド登録時の相手先ＦＡＸ番号のチェックに使用。
		4.ダイアル番号のみ入力されていないかのチェック。
		5.国別によるダイアル記号入力のチェック。
		6.桁数オーバーのチェックはこの関数をコールする前に行ってください.
	]
	return		:[エラー情報]
	common		:[OPR_CharacterCheckBuffer:チェック用バッファ]
	condition	:[チェックする対象となるデータをあらかじめチェック用のバッファにいれておくこと]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/24]
	author		:[江口]
*************************************************************************/
UBYTE CheckDirectDialNumberInput(void)
{
	/** ダイアル記号のみの入力でないかチェック */
	if (CheckInputDialMarkOnly() == TRUE) { /* ダイアル記号しか入力されていない */
		OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
		return (NG);
	}
	/** 国別コードによるチェック */
	if (CheckCountryDialNumber() == NG) { /* 国別パラメータによるダイアル記号のチェック */
		OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
		return (NG);
	}
	OPR_ChildErrorFlag = OPR_NO_ERROR;
}

/*************************************************************************
	module		:[ダイアル記号しか入力されていないかチェック]
	function	:[
		1.
	]
	return		:[]
	common		:[OPR_CharacterCheckBuffer:チェック用バッファ]
	condition	:[
		チェックする対象となるデータをあらかじめチェック用のバッファにいれておくこと
		　データの終了コードは必ずＮＵＬＬであること
		  データが入力されていることをあらかじめチェックしてからコールすること
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/24]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE CheckInputDialMarkOnly(void)
{
	UBYTE	data;	/*ﾀﾞｲﾔﾙ1文字*/

	OPR_CharacterCheckPoint = 0;

	while ((data = OPR_CharacterCheckBuffer[OPR_CharacterCheckPoint]) != NULL) {
		if ((TEN_0_KEY <= data && data <= TEN_9_KEY)
#if (PRO_NEW_DIAL_OPR2 == DISABLE) || defined (KEISATSU)	/* ＃・＊だけの直接ダイヤルを弾きます by K.Watanabe 1998/05/07 */
															/* 警察FAX 06/03/16 石橋正和 */
		 || (data == TEN_SHARP_KEY)
		 || (data == TEN_AST_KEY)
#endif
		 || (CheckOnetouchData(data) != OPR_EXCEPT_ONETOUCH)
		 || (data == OPR_SPEED_MARK)
		 || (data == OPR_GROUP_MARK)) {
			return (FALSE);
		}
		OPR_CharacterCheckPoint++;
		if (OPR_CharacterCheckPoint >= (UBYTE)(OPR_CHECK_BUFFER_MAX - 1)) { /* 念のための処理です */
			return (FALSE);
		}
	}
	OPR_CharacterCheckPoint = 0;
	return (TRUE);
}

/*************************************************************************
	module		:[国別コードによるダイアル番号のチェック]
	function	:[
	]
	return		:[]
	common		:[OPR_CharacterCheckBuffer:チェック用バッファ]
	condition	:[チェックする対象となるデータをあらかじめチェック用のバッファにいれておくこと]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/24]
	author		:[江口]
*************************************************************************/
UBYTE CheckCountryDialNumber(void)
{
	UBYTE	pre_data;
	UBYTE	result;
	UBYTE	pause_count;

	result = OK;		/*OK*/
	pause_count = 0;

	for (OPR_CharacterCheckPoint = 0; OPR_CharacterCheckPoint < (UBYTE)(OPR_CHECK_BUFFER_MAX - 1); OPR_CharacterCheckPoint++) {
		if ((OPR_CharacterCheckBuffer[OPR_CharacterCheckPoint] == NULL)
		||	(OPR_CharacterCheckBuffer[OPR_CharacterCheckPoint] == ' ' )) {
			break;
		}
		switch (OPR_CharacterCheckBuffer[OPR_CharacterCheckPoint]) {
		case '!':
			pause_count = 0;
			if (pre_data == '-') { /* -!:トーン */
				if (CTRY_SignalChange() == 0) {
					result = NG;
				}
			}
			else if (CTRY_1DT_Detect() == 0) {
				result = NG;
			}
			break;
		case '/':
			if (pre_data == '-') { /* -/:ポーズ */
				pause_count++;
				if (CTRY_PauseKey() == 0) {
					result = NG;
				}
				else {
					if (CTRY_PauseCount() == 0) {
						pause_count = 0;
					}
					else {
						if (pause_count > CTRY_PauseCount()) {
							result = NG;
						}
					}
				}
			}
			else {
				pause_count = 0;
				if (CTRY_2DT_Detect() == 0) {
					result = NG;
				}
			}
			break;
		case '-':
			break;
		default:
			pause_count = 0;
			break;
		}
		pre_data = OPR_CharacterCheckBuffer[OPR_CharacterCheckPoint];
		if (result == NG) {
			break;
		}
	}
	return (result);
}

/*************************************************************************
	module		:[グループ番号の登録状態のチェック]
	function	:[
		1.与えられたグループ番号がワンタッチダイアル或いは短縮ダイアルに
		, 登録されているかチェックする
	]
	return		:[
		0:未登録
		１以上：登録済み（メンバー数)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/29]
	author		:[江口]
*************************************************************************/
UBYTE CheckGroupDialStoreStatus(UBYTE group_number)
{
	/*******************************************
	 * 引数で与えられたグループ番号が登録
	 * されているかいないか検査する
	 *******************************************/
	UBYTE	i;
	UBYTE	member_count;
	UDWORD	group_bit;

	member_count = 0;

	/* グループ番号をビットアサインに変換 */
	if (group_number != 0) {
		group_bit = (UDWORD)0x00000001 << (group_number - 1);
	}
	else {
		group_bit = 0xFFFFFFFF;
	}

	/*
	 * なんか処理が重いので関数コールをやめた
	 * 1996/05/26　Eguchi　TBD
	 */

#if (0)
//	/*---------------------------------*/
//	/* 短縮ダイアルに設定されているか  */
//	/*---------------------------------*/
//	for (i = 0; i < SYS_SPEED_DIAL_MAX; i++) {
//		if (CheckSpeedStoreStatus(i) == OK) {	/* 短縮ダイアルが登録されている */
//			if (SYB_SpeedDial[i].Group & group_bit) {	/* 登録されている */
//				member_count++;
//			}
//		}
//	}

//	/*---------------------------------*/
//	/* ワンタッチに登録されているか	   */
//	/*---------------------------------*/
//	for (i = 0; i < SYS_ONETOUCH_MAX; i++) {
//		onetouch = CMN_OffsetToOnetouchCode(i);
//		if (CheckOnetouchStoreStatus(onetouch) == OK) {	/* ワンタッチダイアルが登録されている*/
//			if (SYB_OnetouchDial[i].Group & group_bit) {
//				member_count++;
//			}
//		}
//	}
//	return (member_count);
#endif

	/*---------------------------------*/
	/* 短縮ダイアルに設定されているか  */
	/*---------------------------------*/
	for (i = 0; i < SYS_SPEED_DIAL_MAX; i++) {
		if (((SYB_SpeedDial[i].Dial[0] & 0xF0) != 0xF0) && (SYB_SpeedDial[i].Group & group_bit)) {
			member_count++;
		}
	}

	/*---------------------------------*/
	/* ワンタッチに登録されているか	   */
	/*---------------------------------*/
	for (i = 0; i < SYS_ONETOUCH_MAX; i++) {
		if (((SYB_OnetouchDial[i].Dial[0] & 0xF0) != 0xF0) && (SYB_OnetouchDial[i].Group & group_bit)) {
			member_count++;
		}
	}

	return (member_count);
}

/*************************************************************************
	module		:[エラー箇所のセット]
	function	:[
		1.チェックした結果エラーが生じた場所を返す
	]
	return		:[]
	common		:[OPR_CharacterCheckBuffer:チェック用バッファ]
	condition	:[チェックする対象となるデータをあらかじめチェック用のバッファにいれておくこと]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/24]
	author		:[江口]
*************************************************************************/
UBYTE ErrorPositionSet(void)
{
	return (OPR_CharacterCheckPoint);
}

/*************************************************************************
	module		:[コマンドダイアル番号チェック]
	function	:[
		1.コマンド入力、プログラムワンタッチ登録、一括送信ボックス入力で
		  入力されたダイアル番号のチェック
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
UBYTE CheckCommandNumber(void)
{
	UBYTE	remote_count;			/* 宛先数							*/
	UBYTE	data;					/* バッファ入力データ				*/
	UBYTE	group;					/* グループ番号						*/
	UBYTE	onetouch;				/* ワンタッチ記号					*/
	UBYTE	onetouch_kind;			/* ワンタッチ種類					*/
	UBYTE	record_no;				/* 短縮ダイヤルレコードオフセット	*/
	UBYTE	input_direct_count;		/* 入力直接ダイヤル数				*/
	UBYTE	input_onetouch_count;	/* 入力ワンタッチ数					*/
	UBYTE	input_speed_count;		/* 入力短縮数						*/
	UBYTE	input_group_count;		/* 入力グループ数					*/
	UWORD	length;					/* １宛先単位のデータ長				*/
	UWORD	cursor;					/* カーソル位置退避用				*/
	UWORD	dial_length;			/* ダイアル番号長					*/
	UWORD	pin_length;				/* ＰＩＮ番号長						*/
	UWORD	pin_mark_position;		/* ＰＩＮマーク位置					*/
	UWORD	speed;					/* 短縮番号							*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
	UBYTE	status;					/* ワンタッチの使用状況				*/
#endif

	remote_count = 0;
	length = 0;
	cursor = 0;
	pin_mark_position = 0;
	dial_length = 0;
	pin_length = 0;
	input_direct_count = 0;
	input_onetouch_count = 0;
	input_speed_count = 0;
	input_group_count = 0;

	InputNumber.CursorPosition = 0;	/*カーソルを先頭に移動*/

	if (InputNumber.Buffer[0] == NULL) {	/* 未入力 */
		OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
		return (NG);
	}

#if (PRO_NEW_DIAL_OPR2 == DISABLE)	/* by K.Watanabe 1998/04/23 */
	if (InputNumber.PIN_NumberCheck == YES) {	/* ＰＩＮ番号が必要である */
		ConvertAstToPinMark();	/* "*"をＰＩＮを表すコードに変換 */
	}
#endif

	OPR_ChildErrorFlag = OPR_NO_ERROR;
	/*-----------------------------------------------*/
	/* バッファ全部(入力された分のみ）調べ終わるまで */
	/*-----------------------------------------------*/
	while (1) {
		data = InputNumber.Buffer[InputNumber.CursorPosition];
		if (data == NULL) {	/** 終了記号 */
			/** 同報最終チェック */
			InputNumber.MultiNumberStatus = FinalBroadcastCheck(remote_count);
			return (OK);
		}
		else if (data != ',') {	/** 区切りの記号ではない */
			remote_count++;
#if (0)	/* 1997/10/14 Y.Matsukuma */
//#if (PRO_KEYPANEL == PANEL_ANZU_L)
//			if (remote_count > SYS_COM_DIAL_MAX) {
//				OPR_ChildErrorFlag = TOO_MANY_LOCATION_ERROR;	/* "ﾊﾞﾝｺﾞｳ 10ｶｼｮ ｲﾅｲ    " */
//				return (NG);
//			}
//#endif
#endif
		}
 #if defined(STOCKHM2) /* DVT：Add by SMuratec C.P 2004/08/27 for プレフィクスダイアルの場合 */
		if(InputNumber.CursorPosition == 0) {
			if(data == '!') {
				InputNumber.CursorPosition++;
			}
		}
		else {
			if(InputNumber.Buffer[InputNumber.CursorPosition - 1] == ',') {
				if(data == '!') {
					InputNumber.CursorPosition++;
				}
			}
		}
 #endif	
		/*--------------------------*/
		/* ワンタッチダイアルの場合 */
		/*--------------------------*/
		onetouch_kind = CheckOnetouchData(data);
		if (onetouch_kind != OPR_EXCEPT_ONETOUCH) {	/* チェックしたデータがワンタッチの時 */
			/* ワンタッチのキーコードを取得します */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
			onetouch = ChangeNumberToOnetouch(&InputNumber.Buffer[InputNumber.CursorPosition + 1], ONETOUCH_CODE);
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			/* Ａ～Ｚ，ａ～ｚの時 */
			if (onetouch_kind == OPR_ONETOUCH_ALPHABET) {
				onetouch = data;
			}
			/* Ｕ１～Ｕ８の時 */
			else {
				/* U1  */
				/* ~   */
				onetouch = ChangeNumberToOnetouch(&InputNumber.Buffer[InputNumber.CursorPosition + 1], ONETOUCH_CODE);
			}
#endif
			/* ワンタッチの登録状態を調べます */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
			status = CheckOnetouchStoreStatus(onetouch);
			if (status == SYS_INF_ONETOUCH_MAILADDRESS) {
				OPR_ChildErrorFlag = MAIL_ADDRESS_STORED_ERROR;
			}
			else if (status == SYS_INF_ONETOUCH_NO_ENTRY) {
				OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
			}
#else
			if (CheckOnetouchStoreStatus(onetouch) == NG) {	/* 未登録である */
				OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
			}
#endif
			else {											/* 登録されている */
				if ((InputNumber.PIN_NumberCheck == YES)				/* ＰＩＮ番号チェックが必要 */
				 && (CheckOnetouchPinNumberStore(onetouch) == FALSE)) {	/* ＰＩＮ番号がない */
					OPR_ChildErrorFlag = NO_PIN_NUMBER_ERROR;
				}
				else {													/* エラーなし */
					input_onetouch_count++;
					InputNumber.CursorPosition++;
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
					/* ［０１］の数字とかっこの分を更に進める */
					InputNumber.CursorPosition += 3;
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
					/* Ｕ１～Ｕ８の場合、数字の分を更に進める */
					if (onetouch_kind == OPR_ONETOUCH_NUMBER) {
						InputNumber.CursorPosition++;
					}
#endif
				}
			}
		}

		/*--------------------------------------*/
		/* 短縮ダイアル・グループダイアルの場合 */
		/*--------------------------------------*/
		else if ((data == OPR_SPEED_MARK) || (data == OPR_GROUP_MARK)) {	/* 短縮またはグループ */
			InputNumber.CursorPosition++;	/* 短縮記号、グループ記号をとばす */
			cursor = InputNumber.CursorPosition;	/* カーソル位置を退避 */
			for (length = 0; InputNumber.Buffer[cursor] != NULL && InputNumber.Buffer[cursor] != ','; length++,cursor++) {
				if (CMN_isdigit(InputNumber.Buffer[cursor]) == 0) {	/* 数字でない */
					OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
					break;
				}
			}
			if (length == 0) {	/* 短縮・グループの番号が未入力の時 */
				OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
			}
			if (OPR_ChildErrorFlag == INVALID_NUMBER_ERROR) {	/* エラーあり */
#if (PRO_NEW_DIAL_OPR2 == ENABLE)	/* by K.Watanabe 1998/05/07 */
				if (length != 0) {	/* 短縮・グループ番号に数字以外が入力されていた時 */
					/* 注）(PRO_NEW_DIAL_OPR == ENABLE)の時は入力時に弾いているので、ここに来る事はありません */
					InputNumber.CursorPosition--;		/* 短縮・グループ記号にカーソルを移動 */
				}
#else
				InputNumber.CursorPosition = cursor;	/* エラー位置にカーソルを移動 */
#endif
			}
			else {												/* エラーなし */
				/*--------------------*/
				/* 短縮ダイアルの場合 */
				/*--------------------*/
				if (data == OPR_SPEED_MARK) {
					if (length > SPEED_FIGURE_MAX) {	/* 桁数オーバー */
						OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;
#if (PRO_NEW_DIAL_OPR2 == ENABLE)	/* by K.Watanabe 1998/05/07 */
						InputNumber.CursorPosition--;					/* 短縮記号にカーソルを移動 */
#else
						InputNumber.CursorPosition += SPEED_FIGURE_MAX;	/* エラー位置にセット */
#endif
					}
					else {								/* 桁数オーバーしていない */
						/* 短縮番号計算 */
						speed = CMN_ASC_ToUnsignedInt(&InputNumber.Buffer[InputNumber.CursorPosition], (UBYTE)length);
						if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮 */
							if ((speed < OPR_SPEED_DIAL_MIN) || (speed > SYS_SPEED_DIAL_MAX)) { /* 最大最小値を越えている */
								OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
								InputNumber.CursorPosition--;	/* Ｓの下 */
							}
							else {																/* 正しい番号 */
								/* 短縮の登録状態を調べます */
								speed -= OPR_SPEED_DIAL_MIN;	/* 入力１から。内部：０から */
								if (CheckSpeedStoreStatus((UBYTE)speed) == NG) {	/* 登録されていない */
									OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
									InputNumber.CursorPosition--;	/* Ｓの下 */
								}
								else {												/* 登録されている */
									if ((InputNumber.PIN_NumberCheck == YES)
									 && (CheckSpeedPinNumberStore((UBYTE)speed) == FALSE)) {
										/* ＰＩＮ番号が登録されていない*/
										OPR_ChildErrorFlag = NO_PIN_NUMBER_ERROR;
										InputNumber.CursorPosition--; /* Ｓの下 */
									}
									else {	/* エラーなし */
										input_speed_count++;
										/* 次の宛先データのためにカーソル位置を進める */
										InputNumber.CursorPosition += length;
									}
								}
							}
						}
						else {									/* 任意短縮の時 */
							if (speed > OPR_OPTIONAL_SPEED_MAX) {	/* 最大値を越えている */
								OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
								InputNumber.CursorPosition--;	/* Ｓの下 */
							}
							else {									/* 正しい番号 */
								/* 短縮の登録状態を調べます */
								record_no = SetOptionalSpeedStatus(speed);
								if ((record_no == 0xFF) || (CheckSpeedStoreStatus(record_no) == NG)) {	/* 登録されていない */
									OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
									InputNumber.CursorPosition--;	/* Ｓの下 */
								}
								else {																	/* 登録されている */
									if ((InputNumber.PIN_NumberCheck == YES)
									 && (CheckSpeedPinNumberStore(record_no) == FALSE)) {
										/* ＰＩＮ番号が登録されていない */
										OPR_ChildErrorFlag = NO_PIN_NUMBER_ERROR;
										InputNumber.CursorPosition--;	/* Ｓの下 */
									}
									else {	/* エラーなし */
										input_speed_count++;
										/* 次の宛先データのためにカーソル位置を進める */
										InputNumber.CursorPosition += length;
									}
								}
							}
						}
					}
				}
				/*----------------------------*/
				/* グループダイアルの場合	  */
				/*----------------------------*/
				else {	/* グループ */
					if (length > GROUP_FIGURE_MAX) {	/* 桁数オーバー */
						OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;
#if (PRO_NEW_DIAL_OPR2 == ENABLE)	/* by K.Watanabe 1998/05/07 */
						InputNumber.CursorPosition--;						/* グループ記号にカーソルを移動 */
#else
						InputNumber.CursorPosition += GROUP_FIGURE_MAX;		/* エラー位置にカーソル移動 */
#endif
					}
					else {
						/* グループ番号の計算 */
						group = (UBYTE)CMN_ASC_ToUnsignedInt(&InputNumber.Buffer[InputNumber.CursorPosition],
															 (UBYTE)length);
						if (group > SYS_GROUP_NUMBER_MAX) {	/* 最大値を越えている */
							OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
							InputNumber.CursorPosition--;	/* Gの下 */
						}
						else {								/* 正しい番号 */
							if (CheckGroupDialStoreStatus(group) == 0) {	/* 登録されていない(メンバーがない) */
								OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
								InputNumber.CursorPosition--;	/* Gの下 */
							}
							else {											/* 登録されている */
								if ((InputNumber.PIN_NumberCheck == YES) && (CheckGroupPinNumberStore(group) == FALSE)) {
									/* ＰＩＮ番号が登録されていないメンバーを含む */
									OPR_ChildErrorFlag = NO_PIN_NUMBER_ERROR;
									InputNumber.CursorPosition--;	/* Gの下 */
								}
								else {	/* エラーなし */
									input_group_count++;
									InputNumber.CursorPosition += length;
								}
							}
						}
					}
				}
			}
		}
		/*------------------------------*/
		/* その他（ダイレクト／コンマ） */
		/*------------------------------*/
		else {	/* その他 */
			if (data == ',') {	/* コンマ */
				/* とばす */
				InputNumber.CursorPosition++;
			}
			/*--------------------*/
			/* ダイレクトダイアル */
			/*--------------------*/
			else {
				/* 直接ダイヤルの最大同報数のチェック */
				if (input_direct_count >= SYS_COM_DIRECT_DIAL_MAX) {	/** 最大数が入力されている */
					OPR_ChildErrorFlag = TOO_MANY_DIRECT_DIAL_ERROR;	/* "ﾁｮｸｾﾂﾀﾞｲﾔﾙ 20ｶｼｮ ｲﾅｲ" */
				}
				else {
					cursor = InputNumber.CursorPosition;	/* カーソル位置を退避 */
					pin_mark_position = 0;
					/* ＰＩＮの区切りの記号（'*'）の位置を求める */
					for (length = 0; InputNumber.Buffer[cursor] != NULL && InputNumber.Buffer[cursor] != ','; length++,cursor++) {
						if (InputNumber.Buffer[cursor] == OPR_PIN_MARK) {
							pin_mark_position = cursor - InputNumber.CursorPosition;
						}
					}
					/* ダイアル番号の桁数とＰＩＮ番号の桁数を計算 */
					if (pin_mark_position != 0) {	/* ＰＩＮの区切りの記号あり */
						dial_length = pin_mark_position;
						pin_length  = length - (pin_mark_position + 1);
					}
					else {							/* ＰＩＮ番号の区切りの＊がない */
						dial_length = length;
						pin_length = 0;
					}

					/* ダイヤル番号＋ＰＩＮ番号で最大桁数のチェックをしていましたが、別々に桁数チェックするように変更します */
					if (dial_length > (SYS_DIRECT_DIAL_MAX - 1) * 2) {	/* ダイアル番号長さが最大桁数を越える 98/04/17 By T.Fukumoto */
						OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;
						InputNumber.CursorPosition += (SYS_DIRECT_DIAL_MAX - 1) * 2;
					}
					else {											/* 桁数オーバーしない */
						/*------------------------------*/
						/* ダイアル番号のチェックを行う */
						/*------------------------------*/
						CMN_MemorySet(OPR_CharacterCheckBuffer, OPR_CHECK_BUFFER_MAX, NULL);
						OPR_CharacterCheckPoint = 0;
						CMN_StringCopyNum(OPR_CharacterCheckBuffer,
										  &InputNumber.Buffer[InputNumber.CursorPosition],
										  dial_length);
						if (CheckDirectDialNumberInput() == NG) {	/* ダイレクトダイアル番号エラー */
							InputNumber.CursorPosition += ErrorPositionSet();	/* エラー位置にカーソル移動 */
						}
						else {										/* 番号エラーなし */
#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/29 */
								if (pin_length == 0) {	/* ＰＩＮ番号が入力されていない */
									InputNumber.CursorPosition += length;
								}
								else {									/* ＰＩＮ番号が入力されている */
									/* ＰＩＮ番号の最大桁数を越えている 98/04/17 Add By T.Fukumoto */
									if (pin_length > 1) {
										OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;
										InputNumber.CursorPosition += (dial_length + 1 + (1));
									}
									else {
										/* ＰＩＮの番号のチェックは別にせんでいい */
										InputNumber.CursorPosition += length;
									}
								}
#else
							if (InputNumber.PIN_NumberCheck == YES) {	/* PIN番号のチェックが必要 */
								if (pin_length == 0) {	/* ＰＩＮ番号が入力されていない */
									OPR_ChildErrorFlag = NO_PIN_NUMBER_ERROR;
									InputNumber.CursorPosition += length;
								}
								else {									/* ＰＩＮ番号が入力されている */
									/* ＰＩＮ番号の最大桁数を越えている 98/04/17 Add By T.Fukumoto */
									if (pin_length > SYS_PIN_MAX * 2) {
										OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;
										InputNumber.CursorPosition += (dial_length + 1 + (SYS_PIN_MAX * 2));
									}
									else {
										/* ＰＩＮの番号のチェックは別にせんでいい */
										InputNumber.CursorPosition += length;
									}
								}
							}
							else {
								InputNumber.CursorPosition += length;
							}
#endif
							input_direct_count++;
						}
					}
				}
			}
		}

		if (OPR_ChildErrorFlag != OPR_NO_ERROR) {	/* エラーがある場合 */
			return (NG);
		}
	}
}

/*************************************************************************
	module		:[＊をＰＩＮ番号の区切りの＊に変換する]
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
void ConvertAstToPinMark(void)
{
	UBYTE	data;
	UWORD	pin_mark_position;
	UWORD	cursor;

	pin_mark_position = cursor = 0;

	while (1) {
		data = InputNumber.Buffer[cursor];
		if (data == NULL) {
			return;
		}
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
		if ((data == DIRECT_ADDRESS_MARK)
		 || (CheckOnetouchData(data) != OPR_EXCEPT_ONETOUCH)
		 || (data == OPR_SPEED_MARK)
		 || (data == OPR_GROUP_MARK)) {
			cursor += GetStringGapPoint(&InputNumber.Buffer[cursor], ',');
		}
#else
		if ((CheckOnetouchData(data) != OPR_EXCEPT_ONETOUCH)
		 || (data == OPR_SPEED_MARK)
		 || (data == OPR_GROUP_MARK)) {
			cursor += GetStringGapPoint(&InputNumber.Buffer[cursor], ',');
		}
#endif
		else {
			if (data == ',') {
				cursor++;
			}
			else {
				pin_mark_position = cursor;
				pin_mark_position++;
				while ((InputNumber.Buffer[pin_mark_position] != NULL) && (InputNumber.Buffer[pin_mark_position] != ',')) {
					if (InputNumber.Buffer[pin_mark_position] == OPR_PIN_MARK) {
						InputNumber.Buffer[pin_mark_position] = '*';
						break;
					}
					pin_mark_position++;
				}
				pin_mark_position = cursor;
				pin_mark_position++;
				while ((InputNumber.Buffer[pin_mark_position] != NULL) && (InputNumber.Buffer[pin_mark_position] != ',')) {
					if (InputNumber.Buffer[pin_mark_position] == '*') {
						InputNumber.Buffer[pin_mark_position] = OPR_PIN_MARK;
						break;
					}
					pin_mark_position++;
				}
				cursor += GetStringGapPoint(&InputNumber.Buffer[cursor], ',');
			}
		}
	}
}

/*************************************************************************
	module		:[指定されたワンタッチにＰＩＮ番号が入力されているか]
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
	author		:[江口]
*************************************************************************/
UBYTE CheckOnetouchPinNumberStore(UBYTE onetouch)
{
	UBYTE	position;

#if (PRO_PIN_ACCESS == ENABLE)
	position = CMN_OnetouchCodeToOffset(onetouch);
	if ((SYB_OnetouchDial[position].PIN_Number[0] & 0xF0) != 0xF0) {
		return (TRUE);
	}
#endif
	return (FALSE);
}

/*************************************************************************
	module		:[短縮番号のＰＩＮ番号チェック]
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
	author		:[江口]
*************************************************************************/
UBYTE CheckSpeedPinNumberStore(UBYTE speed)
{
#if (PRO_PIN_ACCESS == ENABLE)
	if ((SYB_SpeedDial[speed].PIN_Number[0] & 0xF0) != 0xF0) {
		return (TRUE);
	}
#endif
	return (FALSE);
}

/*************************************************************************
	module		:[グループのＰＩＮ番号チェック]
	function	:[
		1.指定されたグループ番号のメンバーにＰＩＮ番号が登録されていないものがあるか
		, 調べる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/10]
	author		:[江口]
*************************************************************************/
UBYTE CheckGroupPinNumberStore(UBYTE group)
{
#if (PRO_PIN_ACCESS == ENABLE)
	/*******************************************
	 * 引数で与えられたグループ番号が登録
	 * されているかいないか検査する
	 *******************************************/
	UBYTE	i;
	UBYTE	member_count;
	UBYTE	onetouch;
	UDWORD	group_bit;

	member_count = 0;

	/* グループ番号をビットアサインに変換 */
	if (group != 0) {
		group_bit = (UDWORD)0x00000001 << (group - 1);
	}
	else {
		group_bit = 0xFFFFFFFF;
	}

	/*---------------------------------*/
	/* ワンタッチに登録されているか	   */
	/*---------------------------------*/
	for (i = 0; i < SYS_ONETOUCH_MAX; i++) {
		onetouch = CMN_OffsetToOnetouchCode(i);
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		if ((CheckOnetouchStoreStatus(onetouch) == SYS_INF_ONETOUCH_FAXNUMBER)			/* ワンタッチダイアルが登録されている */
		 && (SYB_OnetouchDial[i].Group & group_bit)				/* グループのメンバーに含まれる */
		 && (CheckOnetouchPinNumberStore(onetouch) == FALSE)) {	/* ＰＩＮ番号がセットされていない */
#else
		if ((CheckOnetouchStoreStatus(onetouch) == OK)			/* ワンタッチダイアルが登録されている */
		 && (SYB_OnetouchDial[i].Group & group_bit)				/* グループのメンバーに含まれる */
		 && (CheckOnetouchPinNumberStore(onetouch) == FALSE)) {	/* ＰＩＮ番号がセットされていない */
#endif
			return (FALSE);
		}
	}

	/*---------------------------------*/
	/* 短縮ダイアルに設定されているか  */
	/*---------------------------------*/
	for (i = 0; i < SYS_SPEED_DIAL_MAX; i++) {
		if ((CheckSpeedStoreStatus(i) == OK)			/* 短縮ダイアルが登録されている */
		 && (SYB_SpeedDial[i].Group & group_bit)		/* グループのメンバーに含まれる */
		 && (CheckSpeedPinNumberStore(i) == FALSE)) {	/* ＰＩＮ番号がセットされていない */
			return (FALSE);
		}
	}

	return (TRUE);
#else
	return (FALSE);
#endif
}

/*************************************************************************
	module		:[プログラムワンタッチのＰＩＮ番号の登録状態のチェック]
	function	:[
		1.プログラムワンタッチの宛先番号にＰＩＮ番号がセットされているか
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/10]
	author		:[江口]
*************************************************************************/
#if (PRO_PIN_ACCESS == ENABLE)
UBYTE CheckProgramPinNumberStore(UBYTE program)
{
	UBYTE	dial;
	UBYTE	error;
	struct	SYS_CommandData_t	*prg_pointer;

	error = 0;
#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/03/17 */
	prg_pointer = &SYB_ProgramOnetouch[program].EntryData.Command;
#else
	prg_pointer = &SYB_ProgramOnetouch[program];
#endif

	/* 各ダイヤルに対するＰＩＮ番号がセットされているかチェック 97/06/18  By M.Kuwahara */
	/* 直接ダイヤル */
	for( dial = 0; dial < SYS_COM_DIRECT_DIAL_MAX; dial++ ){
		if(( prg_pointer->DialNumber.Direct[dial][0] & 0xF0 ) != 0xF0 ){
			if ((prg_pointer->DialNumber.PIN_Number[dial][0] & 0xF0) == 0xF0) {
				return( FALSE );
			}
		}
	}
	/* 短縮ダイヤル */
	for( dial = 0; dial < SYS_SPEED_DIAL_MAX; dial++ ){
		if (CMN_CheckBitAssign( (UBYTE *) prg_pointer->DialNumber.Speed, dial) == TRUE) {
			if (CheckSpeedPinNumberStore((UBYTE)dial) == FALSE) {
				return( FALSE );
			}
		}
	}
	/* ワンタッチダイヤル */
	for( dial = 0; dial < SYS_ONETOUCH_MAX; dial++ ){
		if (CMN_CheckBitAssign( (UBYTE *) prg_pointer->DialNumber.Onetouch, dial) == TRUE) {
			/* CheckOnetouchPinNumberStore()の引数としてキーコードを渡さないといけないのに
			** オフセットを渡していたのを修正しました。 98/05/08 By T.Fukumoto
			*/
			/* if (CheckOnetouchPinNumberStore((UBYTE)dial) == FALSE) [ */
			if (CheckOnetouchPinNumberStore(CMN_OffsetToOnetouchCode((UBYTE)dial)) == FALSE) {
				return( FALSE );
			}
		}
	}
	/* グループ */
	/* CheckGroupPinNumberStore()の引数の値が間違っていたのを修正しました。
	** また無駄な処理を省くためにグループ番号0と、0以外のグループの処理を分けます。
	** By T.Fukumoto 98/05/11
	*/
	if (prg_pointer->DialNumber.Group == 0xffffffff) {
		if (CheckGroupPinNumberStore(0) == FALSE) {
			return( FALSE );
		}
	}
	else {
		for (dial = 0; dial < SYS_GROUP_NUMBER_MAX; dial++) {
			if (CMN_CheckLongBitAssign(prg_pointer->DialNumber.Group, dial) == TRUE) {
				if (CheckGroupPinNumberStore((UBYTE)(dial + 1)) == FALSE) {
					return( FALSE );
				}
			}
		}
	}
	return (TRUE);
}
#endif	/* (PRO_PIN_ACCESS == ENABLE) */

/*************************************************************************
	module		:[同報入力の最終チェック]
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
	date		:[1995/12/20]
	author		:[江口]
*************************************************************************/
UBYTE FinalBroadcastCheck(UBYTE count)
{
	UBYTE	group_number;
	UBYTE	member_count;
	UWORD	length;
	UDWORD	group_bit;

	group_bit = (UDWORD)0;
	member_count = 0;

	if (count > 1) { /* 同報の最終チェック */
		return ((UBYTE)1);
	}
	else { /* Only One Location 1995/12/19 Eguchi */
		if (InputNumber.Buffer[0] == OPR_GROUP_MARK) { /* グループ入力 */
			length = GetStringGapPoint(&InputNumber.Buffer[1], ',');
			group_number = (UBYTE)CMN_ASC_ToUnsignedInt(&InputNumber.Buffer[1], (UBYTE)length);
			member_count = CheckGroupDialStoreStatus(group_number);
			if (member_count >= (UBYTE)2) { /* ２箇所以上 */
				return ((UBYTE)1); /* 同報 */
			}
			else {
				return ((UBYTE)0);
			}
		}
		return ((UBYTE)0);
	}
}

/*************************************************************************
	module		:[原稿読み取り開始可能検査]
	function	:[
		1.マルチコピー時、蓄積時に読みとりが可能かチェック
		2.スキャン不可能な場合、NACKを鳴らし、必要であればエラー表示を出し終了します
	]
	return		:[
		OPR_SCAN_DISABLE:読み取り不可能
		OPR_SCAN_ENABLE	:読み取り可能
		OPR_SCAN_STOP	:ブック原稿サイズ入力中止・タイムアップ
						 （doc_setting_modeが、OPR_DOC_SET_CHK_INP_SETか、OPR_DOC_SET_CHK_INP_STRの時のみ）
	]
	common		:[]
	condition	:[]
	comment		:[
		引数説明
			doc_setting_mode	：原稿読み取り時、原稿がセットされているかのチェックを行うか
				OPR_DOC_SET_NO_CHK			チェックを行いません
				OPR_DOC_SET_CHK_ONLY		チェックを行い、エラー表示のみ行います
				［以下ポプラＢのみ］
				OPR_DOC_SET_CHK_INP_SET		ﾁｪｯｸを行い、ｴﾗｰ表示とﾌﾞｯｸ原稿ｻｲｽﾞ入力を行います（ｾｯﾄｷｰで終了）
				OPR_DOC_SET_CHK_INP_STR		ﾁｪｯｸを行い、ｴﾗｰ表示とﾌﾞｯｸ原稿ｻｲｽﾞ入力を行います（ｽﾀｰﾄｷｰで終了）
				OPR_DOC_SET_CHK_MANUAL_TRX	ﾁｪｯｸを行い、ｴﾗｰ表示のみ行います（ﾌﾞｯｸ原稿未設定のｴﾗｰ表示はしません）

		注）手動送受信のチェックで、この関数を呼んだ時に、繰り込みエラー等が起こっていると、
		　　普通は、[                    ]と表示する所が、[ｼﾞｭｼﾝ               ]と表示されますが、
		　　　　　　[ｼﾞｭｼﾝ               ]　　　　　　　　[ｹﾞﾝｺｳｾｯﾄ ﾔﾘﾅｵｼﾃｸﾀﾞｻｲ]
		　　アンズ・イチョウも同じ仕様になっているので、合わせておきます
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/14]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE CheckScanStartEnable(UBYTE doc_setting_mode)
{
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FEED_ERROR) {	/** 繰り込み不良 */
		OPR_ChildErrorFlag = RESET_DOCUMENT_ERROR;	/* "ｹﾞﾝｺｳｾｯﾄ ﾔﾘﾅｵｼﾃｸﾀﾞｻｲ" */
		return(OPR_SCAN_DISABLE);
	}

	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_LAMP_ERROR) {	/** ランプエラー */
		return(OPR_SCAN_DISABLE);
	}

	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MIRROR_ERROR) {	/** ミラーキャリッジエラー */
		return(OPR_SCAN_DISABLE);
	}

	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_IN) {	/** 繰り込み中 */
		return(OPR_SCAN_DISABLE);
	}

	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT) {	/** 排出中 */
		return(OPR_SCAN_DISABLE);
	}

#if (PRO_FBS == ENABLE)
	/* ＦＢＳからの原稿読み取り時は、スキャナーカバーのオープンは関係ありません */
	if ((CMN_CheckScannerCoverClose() == FALSE)		/** スキャナカバーオープン */
	 && (CMN_CheckScanDocOnFeeder() == TRUE)) {		/** ＡＤＦに原稿がセットされている */
		return(OPR_SCAN_DISABLE);
	}
#else
	if (CMN_CheckScannerCoverClose() == FALSE) {	/** スキャナカバーオープン */
		return(OPR_SCAN_DISABLE);
	}
#endif

	if (CMN_CheckFeederCommandEmpty() == FALSE) {	/** スキャナ送信予約中 */
		OPR_ChildErrorFlag = FEEDER_IN_USE_ERROR;	/* "ｹﾞﾝｺｳ ｶﾞ ｾｯﾄ ｻﾚﾃｲﾏｽ " */
		return(OPR_SCAN_DISABLE);
	}

#if (PRO_FBS == ENABLE)
	/* ＡＤＦからの読み取り時に、ブック原稿押さえカバーが開いていればエラーです
	** 注）ＦＢＳからの読み取り時は、ブック原稿押さえカバーが開いていてもかまいません
	*/
	if ((SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_BOOK_OPEN)	/** ブック原稿押さえカバーオープン */
	 && (CMN_CheckScanDocOnFeeder() == TRUE)) {						/** ＡＤＦに原稿がセットされている */
		OPR_ChildErrorFlag = BOOK_COVER_OPEN_ERROR;	/* "ﾌﾞｯｸｶﾊﾞｰ ｦ ﾄｼﾞﾃｸﾀﾞｻｲ" */
		return(OPR_SCAN_DISABLE);
	}

#if (PRO_PREHEAT == ENABLE) /* 寒冷地 PreHeat T.Nose 1999/01/25 */
	if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT) {
		return(OPR_SCAN_DISABLE);
	}
#endif

	/* FBSカバー開、又はDS1 ONでミラーキャリッジ移動中の処理。
	** もう一つ下のifブロックより先でなければならない。
	** T.Nose 1997/08/11
	*/
	if ((SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MIRROR_BUSY)
	 && ((SCN_MirrorTaskControl == MIRROR_TASK_TO_ADF_READY)
	  || (SCN_MirrorTaskControl == MIRROR_TASK_TO_FBS_READY)
	  || (SCN_MirrorTaskControl == MIRROR_TASK_INITIALIZE))) {
		OPR_ChildErrorFlag = SCAN_PREPARING_ERROR;	/* "ﾖﾐﾄﾘ ｼﾞｭﾝﾋﾞﾁｭｳ ﾃﾞｽ  " */
		return(OPR_SCAN_DISABLE);
	}
#endif
#if (PRO_UPPER_COVER == ENABLE) /* トップカバーの条件追加 1998/01/19  By T.Yamaguchi */
	/*
	** ＡＤＦからの読み取り時に、トップカバーが開いていればエラーです
	*/
	if ((SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_BOOK_OPEN)	/** トップカバーオープン */
	 && (CMN_CheckScanDocOnFeeder() == TRUE)) {						/** ＡＤＦに原稿がセットされている */
		OPR_ChildErrorFlag = TOP_COVER_OPEN_ERROR;	/* "ﾄｯﾌﾟｶﾊﾞｰ ｦ ﾄｼﾞﾃｸﾀﾞｻｲ" */
		return(OPR_SCAN_DISABLE);
	}
#endif

	/* 原稿排出直後に送信のスタートキーを押すと、"ｹﾞﾝｺｳ ﾖﾐﾄﾘﾁｭｳ ﾃﾞｽ   "の表示が出ていたので、
	** 対応策として条件を追加しました
	** by K.Watanabe 1997/11/27
	*/
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {	/** 原稿蓄積中 */
		OPR_ChildErrorFlag = SCANNER_USE_ERROR;		/* "ｹﾞﾝｺｳ ﾖﾐﾄﾘﾁｭｳ ﾃﾞｽ   " */
		return(OPR_SCAN_DISABLE);
	}

	if (CMN_CheckScanEnable() == FALSE) {	/** スキャナ使用中 */
#if (0)	/* by K.Watanabe 1997/11/27 */
//		OPR_ChildErrorFlag = SCANNER_USE_ERROR;		/* "ｹﾞﾝｺｳ ﾖﾐﾄﾘﾁｭｳ ﾃﾞｽ   " */
#endif
		return(OPR_SCAN_DISABLE);
	}

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* by K.Watanabe 1997/12/08 */
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {	/* プリンターカバーオープン */
		return(OPR_SCAN_DISABLE);
	}
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B)	/* by K.Watanabe 1998/03/05 */
	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_MOMENT_TOP_COVER_OPEN) {	/* プリンターカバーオープン（RXIL瞬断） */
		/* 実機での動作確認用に、メンテナンススイッチに記録します */
		SYB_MaintenanceSwitch[MNT_SW_I3] |= 0x80;	/* I:3-7をONします */
		return(OPR_SCAN_DISABLE);
	}
#endif

	if (doc_setting_mode != OPR_DOC_SET_NO_CHK) {	/* 原稿がセットされていない時は、エラー扱いにする時 */
		if (CMN_CheckDocumentOnFeeder() == FALSE) {	/* ＡＤＦに原稿がセットされていない時 */
#if (PRO_FBS == ENABLE)
			/* 原稿枚数指定されている場合は、ＡＤＦからの送信しか受け付けません */
			if (SpecialCommandValue.Page != 0) {	/** 原稿枚数が設定されている時 */
				OPR_ChildErrorFlag = INSERT_DOCUMENT_ERROR;	/* "ｹﾞﾝｺｳ ｦ ｾｯﾄ ｼﾃｸﾀﾞｻｲ " */
				return(OPR_SCAN_DISABLE);
			}

			/*----------------------------------------------*/
			/* ブック原稿サイズが設定されているかのチェック */
			/*----------------------------------------------*/
			/* ＦＢＳに原稿がセットされていて（ＡＤＦに原稿がセットされていない）、
			** ブック原稿サイズが未設定の時は読み取りできません
			*/
			if (!IsBookDocSizeSet) {	/* ブック原稿サイズが未設定の時 */
				if ((doc_setting_mode == OPR_DOC_SET_CHK_INP_SET) || (doc_setting_mode == OPR_DOC_SET_CHK_INP_STR)) {
					/* 原稿サイズ入力をここで行う時 */
					return(BookDocSizeSetOperation(doc_setting_mode));
				}
				else {
					/* 原稿サイズ入力は呼び出しもとの関数で入力か、手動送受信のチェックの時 */
					if (doc_setting_mode != OPR_DOC_SET_CHK_MANUAL_TRX) {	/* 手動送受信チェック以外の時 */
						/* 手動送受信チェックの時で、ここまで来た場合は手動受信の時なので、エラー表示は行いません */
						OPR_ChildErrorFlag = BOOK_SIZE_NO_SET_ERROR;	/* "ｻｲｽﾞ ｦ ｾｯﾃｲ ｼﾃｸﾀﾞｻｲ " */
					}
					return(OPR_SCAN_DISABLE);
				}
			}
#else
			if (doc_setting_mode != OPR_DOC_SET_CHK_MANUAL_TRX) {	/* 手動送受信チェック以外の時 */
				OPR_ChildErrorFlag = INSERT_DOCUMENT_ERROR;	/* "ｹﾞﾝｺｳ ｦ ｾｯﾄ ｼﾃｸﾀﾞｻｲ " */
			}
			return(OPR_SCAN_DISABLE);
#endif
		}
		else {
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
			/* ポプラではＡＤＦに原稿があっても、DS2()がONしている時（読み取り途中でのメモリオーバー等）は、
			** 原稿の読み取りを行いません
			*/
			if (CMN_CheckScanDocOnFeeder() == FALSE) {	/* ＡＤＦに読み取り可能な原稿がセットされていない時 */
				return(OPR_SCAN_DISABLE);
			}
#else
			/* アンズは、SCN_DocumentStatusで判断し、SCN_DOC_END_OF_SCANなら、原稿の読み取りを行いません */
			/* 1997/12/09 Y.Matsukuma */
			if (SCN_DocumentStatus == SCN_DOC_END_OF_SCAN && DS2() != 0) {
				OPR_ChildErrorFlag = RESET_DOCUMENT_ERROR;
				return(OPR_SCAN_DISABLE);
			}
#endif
		}
	}

/* 一番下に移しました 1997/12/05 Y.Matsukuma */
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/* デュアル・トリプル動作の制限対策 1997/09/30 Y.Matsukuma */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_LIST_PRINT) {	/** リストプリント中 */
		OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;	/* Printer In Use */
		return(OPR_SCAN_DISABLE);
	}
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) {	/** リストプリント中 */
		switch (SYS_DocumentPrintClass) {
		case SYS_PRINT_CLASS_LIST_MEMORY:
		case SYS_PRINT_CLASS_LIST_MONITOR:
		case SYS_PRINT_CLASS_LIST_BA_MEMORY:
		case SYS_PRINT_CLASS_LIST_BA_MONITOR:
		case SYS_PRINT_CLASS_LIST_CIPHER:
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/27 */
		case SYS_PRINT_CLASS_RETURNED_MAIL:		/** ｲﾝﾀｰﾈｯﾄFAXの不達通知の印字 */
 #endif
			OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;	/* Printer In Use */
			return(OPR_SCAN_DISABLE);
		default:
			break;
		}
	}
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	/* 1998/11/18 Add by T.Soneoka */
	if (QueryDocPosition() == DOC_POS_NO_DOCUMENT) {
		OPR_ChildErrorFlag = RESET_DOCUMENT_ERROR;	/* "ｹﾞﾝｺｳｾｯﾄ ﾔﾘﾅｵｼﾃｸﾀﾞｻｲ" */
		return(OPR_SCAN_DISABLE);
	}

/*
** ＤＵＡＬ制限変更のため
** 1999/02/18 by T.Soneoka
*/
#if (0)
**	if (!QueryMultiEnable()) {
**		return(OPR_SCAN_DISABLE);
**	}
#else
	if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) ||	(CHK_UNI_V34ReceiveType() != V34_MRX_TO_MRX)) {
		/* プリンタ受信のときは原稿蓄積を拒否します */
		if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)
		&& (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & (SYS_IMAGE_PRINT | SYS_LIST_PRINT | SYS_MULTI_COPY)))
		&& (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_LINE_BUSY)
		&& (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) {
			return(OPR_SCAN_DISABLE);
		}
	}
 #if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* Added by SMuratec C.P 2004/07/01 for Tx Motor */
  #if 0 /* QAT修正 Modified by SMuratec 李 2004/11/09 */
	if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {
		return(OPR_SCAN_DISABLE);
  #else
 	/* QAT修正:スキャンナー予約中のスキャン禁止 Added by SMuratec 李 2004/11/09 */
	if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY
		|| IsScanReserved) {
  		if ( !IsScanTx ) {
			if (doc_setting_mode != OPR_DOC_SET_CHK_MANUAL_TRX) {	/* 手動送受信チェック以外の時 */
				if (IsScanReserved) {
					if (IsCopyReserved) {
						OPR_ChildErrorFlag = NOT_COMPLETE_COPY_ERROR;
					}
					else {
						OPR_ChildErrorFlag = NOT_COMPLETE_STORED_ERROR;
					}
				}
			}
			return(OPR_SCAN_DISABLE);
		}
		else {
			IsScanTx = FALSE;
		}
  #endif
	}
 #endif

#endif
#endif

	return(OPR_SCAN_ENABLE);
}

/*************************************************************************
	module		:[ブック原稿サイズ入力オペレーション]
	function	:[
		1.ブック原稿サイズ・次原稿の設定のみ受け付けます
	]
	return		:[
		OPR_SCAN_ENABLE	:ブック原稿サイズ設定完了
		OPR_SCAN_STOP	:入力中止・タイムアップ
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/09]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_FBS == ENABLE)
UBYTE BookDocSizeSetOperation(UBYTE doc_setting_mode)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	last_key;	/* 前回キー入力値 */
	UBYTE	is_loop_end;
	UBYTE	ret;

	key = OPR_NO_KEY;
	is_loop_end = FALSE;
	ret = OPR_SCAN_STOP;

	while (is_loop_end != TRUE) {

		/* 下段の表示 */
		if (CheckChildDisplay() == FALSE) {	/* チャイルド表示中でない時 */
			if (!IsBookDocSizeSet) {	/* ブック原稿サイズが未設定の時 */
				ClearDisplayHigh();
				DisplayStringLow(0, D2W_BookSizeNoSet);			/* "ｻｲｽﾞ ｦ ｾｯﾃｲ ｼﾃｸﾀﾞｻｲ " */
			}
			else {
				if (doc_setting_mode == OPR_DOC_SET_CHK_INP_SET) {
					DisplayStringHigh(0, D2W_PressEnterKey);	/* "ｾｯﾄｷｰ ｦ ﾄﾞｳｿﾞ       " */
				}
				else {
					DisplayStringHigh(0, D2W_PressStart);		/* "ｽﾀｰﾄｷｰ ｦ ﾄﾞｳｿﾞ      " */
				}
				ClearDisplayLow();
			}
		}

		last_key = key;	/* 前回キー入力値の退避 */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case STOP:			/* ストップキー				*/
		case KEY_TIME_UP:	/* キー待ちタイムオーバー	*/
			SYS_NextBookDocument = FALSE;	/* 次原稿確認を無しに初期化 */
			IsBookDocSizeSet = FALSE;		/* ブック原稿サイズを未設定に初期化 */
			is_loop_end = TRUE;
			break;
		case ENTER:			/* セットキー				*/
			if (doc_setting_mode == OPR_DOC_SET_CHK_INP_SET) {	/* セットキーにて蓄積を開始する時 */
				if ((IsBookDocSizeSet) || (CMN_CheckScanDocOnFeeder() == TRUE)) {
					/* ブック原稿サイズが設定されたか、ＡＤＦに原稿がセットされた時 */
					ret = OPR_SCAN_ENABLE;
					is_loop_end = TRUE;
				}
				else {
					NackBuzzer();
				}
			}
			else {
				NackBuzzer();
			}
			break;
		case START:			/* スタートキー				*/
			if (doc_setting_mode == OPR_DOC_SET_CHK_INP_STR) {	/* スタートキーにて蓄積を開始する時 */
				if ((IsBookDocSizeSet) || (CMN_CheckScanDocOnFeeder() == TRUE)) {
					/* ブック原稿サイズが設定されたか、ＡＤＦに原稿がセットされた時 */
					ret = OPR_SCAN_ENABLE;
					is_loop_end = TRUE;
				}
				else {
					NackBuzzer();
				}
			}
			else {
				NackBuzzer();
			}
			break;
		case NEXT_DOC:		/* 次原稿キー				*/
			BookNextDocumentSet(last_key, TRUE);
			break;
		case BOOK_DOC_SIZE:	/* ブック原稿サイズキー		*/
			BookDocumentSizeSet(OPR_BOOK_SIZE_OPE, last_key);
			break;
		case SINGLE:		/* 単一オペレーションキー	*/
			SingleKeyOperation(key);
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}

	return(ret);
}
#endif	/* (PRO_FBS == ENABLE) */

/*************************************************************************
	module		:[プリント可能かチェックする]
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
	date		:[1995/07/13]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE CheckPrintOperationEnable(void)
{
	if (CMN_CheckPrintEnable(SYS_IMAGE_PRINT) == TRUE) { /* 記録紙、カバー、プリンターエラーのチェック */	/*種類を追加 M.Kotani 1997/10/16*/
		return (TRUE);
	}
	else {
		NackBuzzer();
		if (CMN_CheckPrinting() == TRUE) { /* プリント中 */
			if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PRINTER_CLEANING) {
				OPR_ChildErrorFlag = PRINTER_CLEANING_ERROR;	/* "ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ      " */
			}
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* By H.Fujimura 1999/02/03 */
			else if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM) {	/* CLASS1動作中 */
				ChildDisplayStringLow(D2W_PC_FAX_InUse);		/* "PC-FAX ｼﾖｳﾁｭｳ       " */
			}
#endif
			else {
				OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;		/* "ﾌﾟﾘﾝﾄﾁｭｳ ﾃﾞｽ        " */
			}
		}
		return (FALSE);
	}
	/* 条件等が今後追加、変更があるかもしれません。1995/07/13　Eguchi */
}

/*************************************************************************
	module		:[クリア完了オペレーション]
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
	date		:[1995/07/07]
	author		:[江口]
*************************************************************************/
UBYTE ClearCompleteDisplayOperation(UBYTE *sub_title)
{
	DisplayStringHigh(0, sub_title);
	ChildDisplayStringLow(D2W_ClearComplete);	/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */

	return (ChildCompleteOperation());
}

/*************************************************************************
	module		:[チャイルド表示中断オペレーション]
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
	date		:[1996/01/06]
	author		:[江口]
*************************************************************************/
UBYTE ChildCompleteOperation(void)
{
	UBYTE	key;
	UBYTE	keytype;

	while (1) {
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case STOP:
			return (OPR_END);
		case NO_EFFECT:
			if (key == OPR_CHILD_TIMEUP) {
				return (OPR_CONTINUE);
			}
			break;
		default:
			return (OPR_CONTINUE);
		}
	}
}

/*************************************************************************
	module		:[プロテクトパスコードが登録されているか調べる]
	function	:[
		1.
	]
	return		:[
				TRUE:登録済み
				FALSE:未登録
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/07]
	author		:[江口]
*************************************************************************/
UBYTE CheckProtectPasscodeSet(void)
{
	if (SYB_ProtectPasscode == 0) { /* パスコードが０ */
		return (FALSE);
	}
	return (TRUE);
}

/*************************************************************************
	module		:[数字をＡＳＣＩＩコードに変換]
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
	date		:[1996/01/06]
	author		:[江口]
*************************************************************************/
UBYTE ChangeNumberToASC_Code(UBYTE number)
{
	return ((number | (UBYTE)0x30));
}

/*************************************************************************
	module		:[ＡＳＣＩＩコードを数字に変換]
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
	date		:[1996/01/06]
	author		:[江口]
*************************************************************************/
UBYTE ChangeASC_CodeToNumber(UBYTE code)
{
	return ((code & ~(UBYTE)0x30));
}

/*************************************************************************
	module		:[]
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
	date		:[1996/01/06]
	author		:[江口]
*************************************************************************/
#if (PRO_KEYPANEL == PANEL_ANZU_L)
UBYTE GetOnetouchSideCode(UBYTE onetouch)
{
	UBYTE	code;

	/* ワンタッチＵ１～Ｕ８の添字の１～８のＡＳＣＩＩコードを求める */
	code = onetouch - (UBYTE)ONETOUCH_U1_KEY;
	code |= (UBYTE)0x30;
	code += (UBYTE)1;

	return (code);
}
#endif

/*************************************************************************
	module		:[ワンタッチの数字からワンタッチ記号を求める]
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
	date		:[1996/01/06]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE ChangeNumberToOnetouch(UBYTE *number_address, UBYTE mode)
{
	UBYTE	onetouch_number;	/* ワンタッチの数字部分 */
	UBYTE	ret;				/* リターン値 */

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	/* ［０１］～［７２］の１～７２よりワンタッチコードを求める */
	onetouch_number = (UBYTE)(CMN_ASC_ToUnsignedInt(number_address, (UBYTE)OPR_ONETOUCH_NUMBER_FIGURE));
	onetouch_number -= (UBYTE)1;

	if (mode == ONETOUCH_CODE) {	/* ワンタッチのコードを返す */
		ret = (UBYTE)ONETOUCH_01_KEY + onetouch_number;
	}
	else {							/* ワンタッチのオフセットを返す */
		ret = CMN_OnetouchCodeToOffset((UBYTE)(ONETOUCH_01_KEY + onetouch_number));
	}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	/* Ｕ１～Ｕ８の添字の１～８よりワンタッチコードを求める */
	onetouch_number = *number_address & ~(UBYTE)0x30;
	onetouch_number -= (UBYTE)1;

	if (mode == ONETOUCH_CODE) {	/* ワンタッチのコードを返す */
		ret = (UBYTE)ONETOUCH_U1_KEY + onetouch_number;	/* 変更	*onetouch_number 1997/06/16 Y.Matsukuma */
	}
	else {	/*mode == ONETOUCH_OFFSET ワンタッチのオフセットを返す */
		ret = CMN_OnetouchCodeToOffset((UBYTE)(ONETOUCH_U1_KEY + onetouch_number)); /* 変更	*onetouch_number */
	}
#endif

	return(ret);
}

/*************************************************************************
	module		:[通信中か調べる]
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
	date		:[1996/01/06]
	author		:[江口]
*************************************************************************/
UBYTE CheckFaxComExecute(void)
{
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/07/26 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)
	 && (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_LINE_BUSY)) {
		if ( (SYS_InternalLineNumber == SYS_STD_LINE_COM) && CheckIsKanyuLine()) {
			return(TRUE);
		}
		else if ((SYS_InternalLineNumber == SYS_EXT_LINE_COM) && (!CheckIsKanyuLine())) {
			return(TRUE);
		}
		else {
			return(FALSE);
		}
	}
	return(FALSE);
#else
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)
	 && (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_LINE_BUSY)) {
		return(TRUE);
	}
	return(FALSE);
#endif		/* End of (defined (KEISATSU)) */
}

/*************************************************************************
	module		:[閏年の判断]
	function	:[
		1.
	]
	return		:[
		1:閏年
		0:閏年でない
	]
	common		:[
		OperationTime:
	]
	condition	:[]
	comment		:[H8から移植,戻り値の論理を変更]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/06/03]
	author		:[江口]
*************************************************************************/
UBYTE CheckLeapYear(UBYTE year)
{
	return((UBYTE)(!(year % 4)));
}

/*************************************************************************
	module		:[年月から日数を計算]
	function	:[
		1.
	]
	return		:[日数]
	common		:[MaxDayTable]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/06/14]
	author		:[江口]
*************************************************************************/
UBYTE GetDayFromMonth(UBYTE year,
					  UBYTE month)	/*月*//*ｍｏｎｔｈ！＝（ＢＣＤ）*/
{
	UBYTE	leap_flag;

	leap_flag = CheckLeapYear(year);
	return(MaxDayTable[leap_flag][month]);
}

/*************************************************************************
	module		:[メモリオーバーのチェックをします]
	function	:[
	]
	return		:[
				TRUE:メモリオーバー
				FALSE:メモリオーバーではない
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/06/20]
	author		:[松隈]
*************************************************************************/
UBYTE CheckMemoryOver(void)
{
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MEMORY_OVER) {	/**メモリーオーバー */
		return (TRUE);
	}
	return(FALSE);
}


#if (PRO_MULTI_LINE == ENABLE)		/* 1997/06/23 Y.Matsukuma */
/*************************************************************************
	module		:[内線入力をチェック]
	function	:[
		1.内線記号'！'を１宛先１つ入力させるためのチェック
		2.先頭に！が入ってはいけない
	]
	return		:[
				TRUE:内線記号入力出来る
				FALSE:内線記号入力できない
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/12/18]
	author		:[松隈]
*************************************************************************/
UBYTE	InputPbxCheck(UBYTE kind)
{
	UWORD 	i;
	UWORD	j;
	UBYTE	pbx_ck;		/* 内線記号のカウント */

	pbx_ck   = 0;

	/* 格納されるバッファごとに調べる */
	if (kind == OPR_CHARACTER_INP) {	/* ワンタッチ・短縮の場合 */
		for (i = 0; i < CharacterInput.WritePosition; i++) {
			if (CharacterInput.Buffer[i] == '!') {
				return(FALSE);
			}
		}
		if (CharacterInput.CursorPosition == 0) {	/* 1997/11/06 Y.Matsukuma */
			return(FALSE);
		}
		return(TRUE);
	}
	else {	/* 直接・一括送信・プログラムワンタッチの場合 */
		for (j = InputNumber.CursorPosition; j > 0; j--) {
			if ((InputNumber.Buffer[j] == ',') 
				&& (j != InputNumber.CursorPosition)){	/* いきなりコンマならぬけない */
				if (++j == InputNumber.CursorPosition) {	/* 先頭に！が入ってはいけないため */
					return(FALSE);
				}
				break;
			}
		}
		for (; j < InputNumber.WritePosition; j++) {
			if (InputNumber.Buffer[j] == '!') {
				pbx_ck++;
				break;
			}
			if (InputNumber.Buffer[j] == ',') {
				pbx_ck = 0;
				break;
			}
		}
		if ((pbx_ck == 0) && (InputNumber.CursorPosition != 0)) {
			return(TRUE);
		}
		return(FALSE);
	}
}

/*************************************************************************
	module		:[マルチ回線通信状態]
	function	:[
		1.ホストが通信中か、オプションボードが通信中か。
	]
	return		:[０：    ホスト通信中
				  ０以上：オプションボード通信中
				  0xFF：  通信なし]
	common		:[]
	condition	:[]
	comment		:[優先順位は、ホストが一番上]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/01/27]
	author		:[松隈]
*************************************************************************/
UBYTE	MultiLineBusy(void)
{
	UBYTE	i;

	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) { /** ホスト通信中なら */
		return(0);
	}
	for (i = 1; i < SYS_OPTION_BOARD_MAX; i++ ) {	/* <= を < に変更  1997/09/03 Y.Matsukuma */
		if (CHK_OptionLineBusy(i)) { /** オプション通信中なら */

			/* D65B-010 By O.Kimoto 1997/06/18 */
			if ((SYS_OptionLineStatus[i] & SYS_OPTION_FAXMODEM) == SYS_OPTION_FAXMODEM) {
				continue;
			}
			else {
				return(i);
			}
		}
	}
	return(0xFF);/* 通信なし */
}

/*************************************************************************
	module		:[マルチ回線オプションボード通信数]
	function	:[
		1.オプションボードのみの通信合計数
	]
	return		:[通信合計数]
	common		:[]
	condition	:[]
	comment		:[現在オプションボードで通信してる総数]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/01/27]
	author		:[松隈]
*************************************************************************/
UBYTE	MultiOptAllLineBusy(void)
{
	UBYTE	i;
	UBYTE	busy_cnt;

	busy_cnt = 0;

	for (i = 1; i < SYS_OPTION_BOARD_MAX; i++ ) {	/* <= を < に変更  1997/12/04 Y.Matsukuma */
		if (CHK_OptionLineBusy(i)) { /** オプション通信中なら */

			/* D65B-010 By O.Kimoto 1997/06/18 */
			if ((SYS_OptionLineStatus[i] & SYS_OPTION_FAXMODEM) == SYS_OPTION_FAXMODEM) {
				continue;
			}
			else {
				busy_cnt++;
			}

		}
	}
	return(busy_cnt);/* 通信合計 */
}
#endif	/* (PRO_MULTI_LINE == ENABLE) */

/*************************************************************************
	module		:[連続ポーリング予約の有無を調べる]
	function	:[
		1.
	]
	return		:[
		TRUE:予約あり
		FALSE:予約なし
	]
	common		:[
		SYB_ContinuousPolling
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/11/12]
	author		:[江口]
*************************************************************************/
UBYTE CheckReservedContPollingExist(void)
{
#if defined(POPLAR_F)
	UWORD	exec_file;
#endif

#if (PRO_CONTINUOUS_POLLING == ENABLE)
	if (SYB_ContinuousPolling.Status == SYS_CMD_WAITING) {
		return (TRUE);
	}

 #if defined(POPLAR_F)
	/* 1999/11/19 Y.Murata
	 * 新Ｌ４００は、連続ポーリングは７０秒間隔に発呼するように仕様変更。ＪＡＴＥ違反のため。
	 * よって、予約中表示は出すようにします。
	*/
	/** 実行待ちのコマンドの有無を調べる */
	if (SYB_ContinuousPolling.Status == SYS_CMD_EXECUTE) {
		for (exec_file = 0; exec_file < SYS_EXEC_QUEUE_MAX; exec_file++) {
			if ((SYB_ExecQueue[exec_file].Status == SYS_EXEC_WAITING)
			||	(SYB_ExecQueue[exec_file].Status == SYS_EXEC_FORWARD_WAITING)) {
				if (SYB_ExecQueue[exec_file].Kind == SYS_CONTINUOUS_POLLING) {
					return (TRUE);
				}
			}
		}
	}
 #endif

	return (FALSE);
#else
	return (FALSE);
#endif
}

/*************************************************************************
	module		:[ダイヤルデータ表示用バッファ展開処理]
	function	:[
		1.ビットアサインでセットされているダイヤルデータを表示用に編集し、バッファにセットします。
	]
	return		:[最終セット位置の次の位置]
	common		:[]
	condition	:[]
	comment		:[
		メモリ送信原稿蓄積時の表示から呼ばれた時、表示用ﾊﾞｯﾌｧのサイズを超えてセットしてしまうため
		いったん作業用ﾊﾞｯﾌｧにセットしてから、表示用ﾊﾞｯﾌｧにセットしなおすように変更します。
		作業用ﾊﾞｯﾌｧには、( "," + ﾀﾞｲｱﾙ40桁 + "*" ＋ PIN番号8桁 + NULL ) → 51Byte をとります。
		1998/03/25 By T.Fukumoto
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/12/27]
	author		:[渡辺一章]
*************************************************************************/
void SetDialDataToDispBuffer(UBYTE set_kind, struct SYS_CommandData_t *com_ptr, UBYTE *disp_buffer)
{
	UBYTE	i;				/* ﾙｰﾌﾟ変数 */
	UBYTE	count;			/* 直接ﾀﾞｲﾔﾙ取得用ｶｳﾝﾀ */
	UBYTE	dial_data;		/* 直接ﾀﾞｲﾔﾙ取得用ﾊﾞｯﾌｧ */
	UBYTE	data_count;		/* 相手先数 */
	UWORD	disp_position;	/* 入力位置 */
	UWORD	no;				/* 任意短縮番号 */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	UBYTE	onetouch;
#endif
	UWORD			data_position;								/* 作業用入力位置 */
	static UBYTE	data_buffer[OPR_TELCONTROL_BUFFER_MAX + 1];	/* 作業用ﾊﾞｯﾌｧ */

	disp_position = 0;
	data_count = 1;

	/*------------------------------*/
	/* ワンタッチダイヤルの展開処理 */
	/*------------------------------*/
	for (i = 0; i < SYS_ONETOUCH_MAX; i++) {
		if (CMN_CheckBitAssign(com_ptr->DialNumber.Onetouch, i) == TRUE) {
			data_position = 0;												/* 作業用入力位置の初期化 */
			CMN_MemorySetNULL(data_buffer, OPR_TELCONTROL_BUFFER_MAX, ' ');	/* 作業用ﾊﾞｯﾌｧの初期化 */

			/* 複数宛先の場合、宛先の番号と番号の間に区切りの','を挿入する */
			if (disp_position) {
				data_buffer[data_position++] = ',';
				data_count++;
			}
#if (PRO_DIAL_NAME_DISP == ENABLE)	/* by K.Watanabe 1998/03/20 */
			if (set_kind == OPR_TX_DISPLAY) {	/* メモリ送信原稿蓄積時の表示から呼ばれた時 */
				/* ワンタッチの相手先名（ダイヤル番号）をバッファにセットします */
				data_position += SetOnetouchSpeedDialName(&data_buffer[data_position], OPR_CURSOR_ONETOUCH, i);

				/* メモリ送信原稿蓄積時の表示で２０桁を超えた時 */
				if (CheckSettingDataLength(set_kind, disp_position + data_position) == FALSE) {
					/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開し、処理を抜けます */
					CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, OPR_DISPLAY_MAX - disp_position );
					return;
				}

				/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開します */
				CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, data_position );
				disp_position += data_position;
				continue;
			}
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
			data_buffer[data_position++] = OPR_ONETOUCH_MARK_LEFT;
			CMN_UnsignedIntToASC(&data_buffer[data_position], (UWORD)(i + 1), 2, '0');
			data_position += 2;
			data_buffer[data_position++] = OPR_ONETOUCH_MARK_RIGHT;
#else	/* (PRO_KEYPANEL == PANEL_ANZU_L) */
			if (i <= 51) {
				/* Ａからｚ */
				data_buffer[data_position] = OnetouchTable[i];
			}
			else {
				/* Ｕ１からＵ８ */
				data_buffer[data_position] = OPR_ONETOUCH_MARK;
				data_position++;
				onetouch = i;
				CMN_UnsignedIntToASC(&data_buffer[data_position], (UWORD)(onetouch - 51), 1, '0');
			}
			data_position += OPR_ONETOUCH_NUMBER_FIGURE;
#endif
			/* メモリ送信原稿蓄積時の表示で２０桁を超えた時 */
			if (CheckSettingDataLength(set_kind, disp_position + data_position) == FALSE) {
				/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開し、処理を抜けます */
				CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, OPR_DISPLAY_MAX - disp_position );
				return;
			}

			/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開します */
			CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, data_position );
			disp_position += data_position;
		}
	}

	/*------------------------*/
	/* 短縮ダイヤルの展開処理 */
	/*------------------------*/
	for (i = 0; i < SYS_SPEED_DIAL_MAX; i++) {
		if (CMN_CheckBitAssign(com_ptr->DialNumber.Speed, i) == TRUE) {
			data_position = 0;												/* 作業用入力位置の初期化 */
			CMN_MemorySetNULL(data_buffer, OPR_TELCONTROL_BUFFER_MAX, ' ');	/* 作業用ﾊﾞｯﾌｧの初期化 */

			/* 複数宛先の場合、宛先の番号と番号の間に区切りの','を挿入する */
			if (disp_position) {
				data_buffer[data_position++] = ',';
				data_count++;
			}
#if (PRO_DIAL_NAME_DISP == ENABLE)	/* by K.Watanabe 1998/03/23 */
			if (set_kind == OPR_TX_DISPLAY) {	/* メモリ送信原稿蓄積時の表示から呼ばれた時 */
				/* 短縮の相手先名（ダイヤル番号）をバッファにセットします */
				data_position += SetOnetouchSpeedDialName(&data_buffer[data_position], OPR_CURSOR_SPEED, i);

				/* メモリ送信原稿蓄積時の表示で２０桁を超えた時 */
				if (CheckSettingDataLength(set_kind, disp_position + data_position) == FALSE) {
					/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開し、処理を抜けます */
					CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, OPR_DISPLAY_MAX - disp_position );
					return;
				}

				/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開します */
				CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, data_position );
				disp_position += data_position;
				continue;
			}
#endif
			data_buffer[data_position++] = OPR_SPEED_MARK;
			if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮の時 */
				CMN_UnsignedIntToASC(&data_buffer[data_position],(UWORD)(i + OPR_SPEED_DIAL_MIN),SPEED_FIGURE_MAX,'0');
				data_position += SPEED_FIGURE_MAX;
			}
			else{									/* 任意短縮の時 */
				no = GetRecordFromNumber(i);
				if (no != 0xFFFF) {
					CMN_UnsignedIntToASC(&data_buffer[data_position], no, SPEED_FIGURE_MAX, '0');
					data_position += SPEED_FIGURE_MAX;
				}
				else {
					CMN_MemorySet(&data_buffer[data_position], SPEED_FIGURE_MAX, '*');
					data_position += SPEED_FIGURE_MAX;
				}
			}

			/* メモリ送信原稿蓄積時の表示で２０桁を超えた時 */
			if (CheckSettingDataLength(set_kind, disp_position + data_position) == FALSE) {
				/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開し、処理を抜けます */
				CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, OPR_DISPLAY_MAX - disp_position );
				return;
			}

			/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開します */
			CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, data_position );
			disp_position += data_position;
		}
	}

	/*------------------------*/
	/* 直接ダイヤルの展開処理 */
	/*------------------------*/
	for (i = 0; i < SYS_COM_DIRECT_DIAL_MAX; i++) {
		if ((com_ptr->DialNumber.Direct[i][0] & 0xF0) != 0xF0) {
			data_position = 0;												/* 作業用入力位置の初期化 */
			CMN_MemorySetNULL(data_buffer, OPR_TELCONTROL_BUFFER_MAX, ' ');	/* 作業用ﾊﾞｯﾌｧの初期化 */

			/* 複数宛先の場合、宛先の番号と番号の間に区切りの','を挿入する */
			if (disp_position) {
				data_buffer[data_position++] = ',';
				data_count++;
			}
			count = 0;
			while (1) {
				dial_data = com_ptr->DialNumber.Direct[i][count];
				if (((dial_data & 0xF0) != 0xF0) && ((dial_data & 0x0F) != 0x0F)) {
					data_buffer[data_position++] = CMN_BCD_ToASC((UBYTE)((dial_data & 0xF0) >> 4));
					data_buffer[data_position++] = CMN_BCD_ToASC((UBYTE)(dial_data & 0x0F));
					count++;
				}
				else {
					if (((dial_data & 0xF0) != 0xF0) && ((dial_data & 0x0F) == 0x0F)) {
						data_buffer[data_position++] = CMN_BCD_ToASC((UBYTE)((dial_data & 0xF0) >> 4));
						break;
					}
					else {
						break;
					}
				}
			}

			/* メモリ送信原稿蓄積時の表示で２０桁を超えた時 */
			if (CheckSettingDataLength(set_kind, disp_position + data_position) == FALSE) {
				/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開し、処理を抜けます */
				CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, OPR_DISPLAY_MAX - disp_position );
				return;
			}

			/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開します */
			CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, data_position );
			disp_position += data_position;

#if (PRO_PIN_ACCESS == ENABLE)
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/29 */
			if (set_kind == OPR_PROGRAM_EXECUTE || set_kind == OPR_PROGRAM_DISPLAY) {
				if ((com_ptr->DialNumber.PIN_Number[i][0] & 0xF0) != 0xF0) {
				/* ピン番号が必要なとき（この時、必ずピン番号はセットされているはず） */
					*(disp_buffer + disp_position++) = OPR_PIN_MARK;
					CMN_BCD_ToASC_StringNum(disp_buffer + disp_position,
											&com_ptr->DialNumber.PIN_Number[i][0],
											SYS_PIN_MAX * 2);
					/* PIN番号をdisp_bufferにセットしたあと、disp_positionをインクリメントしていなかったため、
					** 複数の直接ダイヤルや、グループが登録されているときは、PIN番号がセットされていなかった。
					** 98/05/08 Add By T.Fukumoto
					*/
					disp_position += GetStringGapPoint(disp_buffer + disp_position, ',');
				}
			}
 #else
			/* プログラムワンタッチ登録からCallされた時は、ＰＩＮ番号が登録されていてもＰＩＮ番号はコピーしない
			** →再編集の時は消去されるものとするから
			** プログラム送信コマンド展開からCallされた時も作業用バッファにセットしていたため、PIN番号がセットされていなかった。
			** →直接disp_bufferにセットするように戻します｡ 1998/05/08 T．Fukumoto
			*/
			if (set_kind == OPR_PROGRAM_EXECUTE) {	/* プログラム送信コマンド展開からCallされた時 */
				if (InputNumber.PIN_NumberCheck == YES) {
				/* ピン番号が必要なとき（この時、必ずピン番号はセットされているはず） */
					*(disp_buffer + disp_position++) = OPR_PIN_MARK;
					CMN_BCD_ToASC_StringNum(disp_buffer + disp_position,
											&com_ptr->DialNumber.PIN_Number[i][0],
											SYS_PIN_MAX * 2);
					/* PIN番号をdisp_bufferにセットしたあと、disp_positionをインクリメントしていなかったため、
					** 複数の直接ダイヤルや、グループが登録されているときは、PIN番号がセットされていなかった。
					** 98/05/08 Add By T.Fukumoto
					*/
					disp_position += GetStringGapPoint(disp_buffer + disp_position, ',');
				}
			}
 #endif
#endif
		}
	}

	/*---------------------*/
	/* グループの展開処理  */
	/*---------------------*/
	if (com_ptr->DialNumber.Group == 0xffffffff) {
		data_position = 0;												/* 作業用入力位置の初期化 */
		CMN_MemorySetNULL(data_buffer, OPR_TELCONTROL_BUFFER_MAX, ' ');	/* 作業用ﾊﾞｯﾌｧの初期化 */

		/* 複数宛先の場合、宛先の番号と番号の間に区切りの','を挿入する */
		if (disp_position) {
			data_buffer[data_position++] = ',';
			data_count++;
		}
		data_buffer[data_position++] = OPR_GROUP_MARK;
		data_buffer[data_position++] = '0';

		/* メモリ送信原稿蓄積時の表示で２０桁を超えた時 */
		if (CheckSettingDataLength(set_kind, disp_position + data_position) == FALSE) {
			/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開し、処理を抜けます */
			CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, OPR_DISPLAY_MAX - disp_position );
			return;
		}

		/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開します */
		CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, data_position );
		disp_position += data_position;
	}
	else {
		for (i = 0; i < SYS_GROUP_NUMBER_MAX; i++) {
			if (CMN_CheckLongBitAssign(com_ptr->DialNumber.Group, i) == TRUE) {
				data_position = 0;												/* 作業用入力位置の初期化 */
				CMN_MemorySetNULL(data_buffer, OPR_TELCONTROL_BUFFER_MAX, ' ');	/* 作業用ﾊﾞｯﾌｧの初期化 */

				/* 複数宛先の場合、宛先の番号と番号の間に区切りの','を挿入する */
				if (disp_position) {
					data_buffer[data_position++] = ',';
					data_count++;
				}
				/** グループのマークをセット */
				data_buffer[data_position++] = OPR_GROUP_MARK;
				/* グループ番号をセット */
				CMN_UnsignedIntToASC(&data_buffer[data_position], (UWORD)(i + 1), GROUP_FIGURE_MAX, '0');
				data_position += GROUP_FIGURE_MAX;

				/* メモリ送信原稿蓄積時の表示で２０桁を超えた時 */
				if (CheckSettingDataLength(set_kind, disp_position + data_position) == FALSE) {
					/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開し、処理を抜けます */
					CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, OPR_DISPLAY_MAX - disp_position );
					return;
				}

				/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開します */
				CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, data_position );
				disp_position += data_position;
			}
		}
	}

#if (0) /* 1998/03/27 By T.Fukumoto */
//	メモリ送信原稿蓄積時の表示から呼ばれた時、表示用ﾊﾞｯﾌｧのサイズを超えてセットしてしまうため
//	いったん作業用ﾊﾞｯﾌｧにセットしてから、表示用ﾊﾞｯﾌｧにセットしなおすように変更します。
//	/*------------------------------*/
//	/* ワンタッチダイヤルの展開処理 */
//	/*------------------------------*/
//	for (i = 0; i < SYS_ONETOUCH_MAX; i++) {
//		if (CheckSettingDataLength(set_kind, disp_position) == FALSE) {	/* ﾒﾓﾘ送信原稿蓄積時の表示で20文字を超えた時 */
//			break;
//		}
//		if (CMN_CheckBitAssign(com_ptr->DialNumber.Onetouch, i) == TRUE) {
//			/* 複数宛先の場合、宛先の番号と番号の間に区切りの','を挿入する */
//			if (disp_position) {
//				*(disp_buffer + disp_position++) = ',';
//				data_count++;
//			}
//#if (PRO_DIAL_NAME_DISP == ENABLE)	/* by K.Watanabe 1998/03/20 */
//			if (set_kind == OPR_TX_DISPLAY) {	/* メモリ送信原稿蓄積時の表示から呼ばれた時 */
//				/* ワンタッチの相手先名（ダイヤル番号）をバッファにセットします */
//				disp_position += SetOnetouchSpeedDialName(&data_buffer[data_position], OPR_CURSOR_ONETOUCH, i);
//				continue;
//			}
//#endif
//#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI)
//			*(disp_buffer + disp_position++) = OPR_ONETOUCH_MARK_LEFT;
//			CMN_UnsignedIntToASC(disp_buffer + disp_position, (UWORD)(i + 1), 2, '0');
//			disp_position += 2;
//			*(disp_buffer + disp_position++) = OPR_ONETOUCH_MARK_RIGHT;
//#else	/* (PRO_KEYPANEL == PANEL_ANZU_L) */
//			if (i <= 51) {
//				/* Ａからｚ */
//				*(disp_buffer + disp_position) = OnetouchTable[i];
//			}
//			else {
//				/* Ｕ１からＵ８ */
//				*(disp_buffer + disp_position) = OPR_ONETOUCH_MARK;
//				disp_position++;
//				onetouch = i;
//				CMN_UnsignedIntToASC(disp_buffer + disp_position, (UWORD)(onetouch - 51), 1, '0');
//			}
//			disp_position += OPR_ONETOUCH_NUMBER_FIGURE;
//#endif
//		}
//	}
//
//	/*------------------------*/
//	/* 短縮ダイヤルの展開処理 */
//	/*------------------------*/
//	for (i = 0; i < SYS_SPEED_DIAL_MAX; i++) {
//		if (CheckSettingDataLength(set_kind, disp_position) == FALSE) {	/* ﾒﾓﾘ送信原稿蓄積時の表示で20文字を超えた時 */
//			break;
//		}
//		if (CMN_CheckBitAssign(com_ptr->DialNumber.Speed, i) == TRUE) {
//			/* 複数宛先の場合、宛先の番号と番号の間に区切りの','を挿入する */
//			if (disp_position) {
//				*(disp_buffer + disp_position++) = ',';
//				data_count++;
//			}
//#if (PRO_DIAL_NAME_DISP == ENABLE)	/* by K.Watanabe 1998/03/23 */
//			if (set_kind == OPR_TX_DISPLAY) {	/* メモリ送信原稿蓄積時の表示から呼ばれた時 */
//				/* 短縮の相手先名（ダイヤル番号）をバッファにセットします */
//				disp_position += SetOnetouchSpeedDialName(&data_buffer[data_position], OPR_CURSOR_SPEED, i);
//				continue;
//			}
//#endif
//			*(disp_buffer + disp_position++) = OPR_SPEED_MARK;
//			if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮の時 */
//				CMN_UnsignedIntToASC(disp_buffer + disp_position,(UWORD)(i + OPR_SPEED_DIAL_MIN),SPEED_FIGURE_MAX,'0');
//				disp_position += SPEED_FIGURE_MAX;
//			}
//			else{									/* 任意短縮の時 */
//				no = GetRecordFromNumber(i);
//				if (no != 0xFFFF) {
//					CMN_UnsignedIntToASC(disp_buffer + disp_position, no, SPEED_FIGURE_MAX, '0');
//					disp_position += SPEED_FIGURE_MAX;
//				}
//				else {
//					CMN_MemorySet(disp_buffer + disp_position, SPEED_FIGURE_MAX, '*');
//					disp_position += SPEED_FIGURE_MAX;
//				}
//			}
//		}
//	}
//
//	/*------------------------*/
//	/* 直接ダイヤルの展開処理 */
//	/*------------------------*/
//	for (i = 0; i < SYS_COM_DIRECT_DIAL_MAX; i++) {
//		if (CheckSettingDataLength(set_kind, disp_position) == FALSE) {	/* ﾒﾓﾘ送信原稿蓄積時の表示で20文字を超えた時 */
//			break;
//		}
//		if ((com_ptr->DialNumber.Direct[i][0] & 0xF0) != 0xF0) {
//			/* 複数宛先の場合、宛先の番号と番号の間に区切りの','を挿入する */
//			if (disp_position) {
//				*(disp_buffer + disp_position++) = ',';
//				data_count++;
//			}
//			count = 0;
//			while (1) {
//				dial_data = com_ptr->DialNumber.Direct[i][count];
//				if (((dial_data & 0xF0) != 0xF0) && ((dial_data & 0x0F) != 0x0F)) {
//					*(disp_buffer + disp_position++) = CMN_BCD_ToASC((UBYTE)((dial_data & 0xF0) >> 4));
//					*(disp_buffer + disp_position++) = CMN_BCD_ToASC((UBYTE)(dial_data & 0x0F));
//					count++;
//				}
//				else {
//					if (((dial_data & 0xF0) != 0xF0) && ((dial_data & 0x0F) == 0x0F)) {
//						*(disp_buffer + disp_position++) = CMN_BCD_ToASC((UBYTE)((dial_data & 0xF0) >> 4));
//						break;
//					}
//					else {
//						break;
//					}
//				}
//			}
//
//#if (PRO_PIN_ACCESS == ENABLE)
//			/* プログラムワンタッチ登録からCallされた時は、ＰＩＮ番号が登録されていてもＰＩＮ番号はコピーしない
//			** →再編集の時は消去されるものとするから
//			*/
//			if (set_kind == OPR_PROGRAM_EXECUTE) {	/* プログラム送信コマンド展開からCallされた時 */
//				if (InputNumber.PIN_NumberCheck == YES) {
//				/* ピン番号が必要なとき（この時、必ずピン番号はセットされているはず） */
//					*(disp_buffer + disp_position++) = OPR_PIN_MARK;
//					CMN_BCD_ToASC_StringNum(disp_buffer + disp_position,
//											&com_ptr->DialNumber.PIN_Number[i][0],
//											SYS_PIN_MAX * 2);
//				}
//			}
//#endif
//		}
//	}
//
//	/*---------------------*/
//	/* グループの展開処理  */
//	/*---------------------*/
//	if (com_ptr->DialNumber.Group == 0xffffffff) {
//		if (CheckSettingDataLength(set_kind, disp_position) == TRUE) {	/* ﾒﾓﾘ送信原稿蓄積時の表示で20文字を超えていない時 */
//			/* 複数宛先の場合、宛先の番号と番号の間に区切りの','を挿入する */
//			if (disp_position) {
//				*(disp_buffer + disp_position++) = ',';
//				data_count++;
//			}
//			*(disp_buffer + disp_position++) = OPR_GROUP_MARK;
//			*(disp_buffer + disp_position++) = '0';
//		}
//	}
//	else {
//		for (i = 0; i < SYS_GROUP_NUMBER_MAX; i++) {
//			if (CheckSettingDataLength(set_kind, disp_position) == FALSE) {	/* ﾒﾓﾘ送信原稿蓄積時の表示で20文字を超えた時 */
//				break;
//			}
//			if (CMN_CheckLongBitAssign(com_ptr->DialNumber.Group, i) == TRUE) {
//				/* 複数宛先の場合、宛先の番号と番号の間に区切りの','を挿入する */
//				if (disp_position) {
//					*(disp_buffer + disp_position++) = ',';
//					data_count++;
//				}
//				/** グループのマークをセット */
//				*(disp_buffer + disp_position++) = OPR_GROUP_MARK;
//				/* グループ番号をセット */
//				CMN_UnsignedIntToASC(disp_buffer + disp_position, (UWORD)(i + 1), GROUP_FIGURE_MAX, '0');
//				disp_position += GROUP_FIGURE_MAX;
//			}
//		}
//	}
#endif	/* 1998/03/27 By T.Fukumoto */

	/* プログラムワンタッチ登録からCallされた時 */
	if (set_kind == OPR_PROGRAM_DISPLAY) {
		if (GetStringGapPoint(&InputNumber.Buffer[0], ',') < disp_position) {	/* 同報の時 */
			InputNumber.MultiNumberStatus = 1;
		}

		/*--------------------------------*/
		/* カーソルをデータの後に移動する */
		/*--------------------------------*/
		InputNumber.WritePosition = disp_position;
		InputNumber.CursorPosition = disp_position;
	}

	/* プログラム送信コマンド展開からCallされた時 */
	if (set_kind == OPR_PROGRAM_EXECUTE) {
		/* プログラムワンタッチのダイアル番号が歯抜けに登録されることはないので、
		** data_countの値をそのまま宛先数として信用していい
		*/
		InputNumber.MultiNumberStatus = FinalBroadcastCheck(data_count);

		/*----------------------------------*/
		/* カーソルをデータの後に移動する   */
		/*----------------------------------*/
		InputNumber.WritePosition = disp_position;
		InputNumber.CursorPosition = disp_position;
	}
}

/*************************************************************************
	module		:[送信相手先表示　文字数チェック]
	function	:[
		1.表示用バッファが２０文字をこえていないかを調べます
	]
	return		:[
		TRUE	:送信相手先表示でない or 送信相手先表示で２０文字未満
		FALSE	:送信相手先表示で２０文字以上
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/12/27]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckSettingDataLength(UBYTE set_kind, UWORD disp_position)
{
	UBYTE	ret;	/* リターン値 */

	ret = TRUE;

	if (set_kind == OPR_TX_DISPLAY) {	/* 送信時表示から呼ばれた時 */
		if (disp_position >= OPR_DISPLAY_MAX) {	/* ２０文字以上セットした時 */
			ret = FALSE;
		}
	}

	return(ret);
}

/*************************************************************************
	module		:[ワンタッチダイヤル検査]
	function	:[
		1.指定のデータがワンタッチかを調べます
	]
	return		:[
		OPR_EXCEPT_ONETOUCH		:ワンタッチダイヤル以外
		（ポプラのみ）
		OPR_ONETOUCH_DIAL		:ワンタッチダイヤル
		（アンズのみ）
		OPR_ONETOUCH_ALPHABET	:ワンタッチダイヤル（Ａ～Ｚ，ａ～ｚ）
		OPR_ONETOUCH_NUMBER		:ワンタッチダイヤル（Ｕ１～Ｕ８）
	]
	common		:[]
	condition	:[]
	comment		:[
		PRO_DIALUP_INTERNET_FAX		1998/03/13	by K.Okada
			アルファベットでワンタッチを判断する機種の場合、
			ダイレクトメールアドレス中のアルファベットではない
			ことをチェックしてから、コールする必要がある。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/01/29]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckOnetouchData(UBYTE data)
{
	UBYTE	ret;	/* リターン値 */

	ret = OPR_EXCEPT_ONETOUCH;			/* リターン値にワンタッチダイヤル以外をセット */

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	/* ワンタッチの時（［０１］の'［'で判断します） */
	if (data == OPR_ONETOUCH_MARK_LEFT) {
		ret = OPR_ONETOUCH_DIAL;		/* リターン値にワンタッチダイヤルをセット */
	}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	/* ワンタッチのＡ～Ｚ，ａ～ｚの時 */
	if (((data >= ONETOUCH_A_KEY) && (data <= ONETOUCH_Z_KEY))
	 || ((data >= ONETOUCH_a_KEY) && (data <= ONETOUCH_z_KEY))) {
		ret = OPR_ONETOUCH_ALPHABET;	/* リターン値にワンタッチダイヤル（Ａ～Ｚ，ａ～ｚ）をセット */
	}
	/* ワンタッチのＵ１～Ｕ８の時（Ｕ１～Ｕ８の'Ｕ'で判断します） */
	else if (data == OPR_ONETOUCH_MARK) {
		ret = OPR_ONETOUCH_NUMBER;		/* リターン値にワンタッチダイヤル（Ｕ１～Ｕ８）をセット */
	}
#endif

	return(ret);
}

/*************************************************************************
	module		:[ワンタッチ記号セット]
	function	:[
		1.ワンタッチ記号を、指定されたバッファにセットします
	]
	return		:[セットしたワンタッチ記号の長さ]
	common		:[]
	condition	:[]
	comment		:[
		引数説明
			*buffer		:ワンタッチ記号をセットするバッファのアドレス
			data		:ワンタッチのキーコード
			set_kind	:ワンタッチ記号のセット内容（ポプラ専用です）
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/01/29]
	author		:[渡辺一章]
*************************************************************************/
UBYTE SetOnetouchCode(UBYTE *buffer, UBYTE data, UBYTE set_kind)
{
	UBYTE	length;		/* ワンタッチ記号の長さ */

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	if (set_kind == OPR_SET_ONETOUCH_CODE) {	/* かっこをつけてワンタッチ番号をセットする場合 */
		*buffer = OPR_ONETOUCH_MARK_LEFT;			/* '[' */
		data = (UBYTE)(CMN_OnetouchCodeToOffset(data) + 1);	/* ワンタッチのキーコードをワンタッチ番号にかえる */
		CMN_UnsignedIntToASC(buffer + 1, data, OPR_ONETOUCH_NUMBER_FIGURE, '0');
		*(buffer + 3) = OPR_ONETOUCH_MARK_RIGHT;	/* ']' */
		length = 4;
	}
	else {										/* ワンタッチ番号のみセットする場合 */
		data = (UBYTE)(CMN_OnetouchCodeToOffset(data) + 1);	/* ワンタッチのキーコードをワンタッチ番号にかえる */
		CMN_UnsignedIntToASC(buffer, data, OPR_ONETOUCH_NUMBER_FIGURE, '0');
		length = 2;
	}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	if (((data >= ONETOUCH_A_KEY) && (data <= ONETOUCH_Z_KEY))
	 || ((data >= ONETOUCH_a_KEY) && (data <= ONETOUCH_z_KEY))) {	/* Ａ～Ｚ，ａ～ｚの時 */
		*buffer = data;
		length = 1;
	}
	else {															/* Ｕ１～Ｕ８の時 */
		*buffer = OPR_ONETOUCH_MARK;				/* 'U' */
		*(buffer + 1) = GetOnetouchSideCode(data);	/* '1' - '8' */
		length = 2;
	}
#endif

	return(length);
}

/*************************************************************************
	module		:[プログラムワンタッチダイヤル検査]
	function	:[
		1.指定のデータがプログラムワンタッチかを調べます
	]
	return		:[
		TRUE	:プログラムワンタッチ
		FALSE	:プログラムワンタッチ以外
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/11/13]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckProgramOnetouchData(UBYTE data)
{
	UBYTE	ret;	/* リターン値 */

	ret = FALSE;

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
 #if defined(HINOKI3)	/* by K.Watanabe 2004/10/18 */
	/* プログラムワンタッチワンタッチの時（P1～P5の'P'で判断します） */
	if (data == OPR_PROGRAM_MARK) {
		ret = TRUE;
	}
 #else
	/* プログラムワンタッチの時（［７３］の'［'で判断します） */
	if (data == OPR_PROGRAM_MARK_LEFT) {
		ret = TRUE;
	}
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	/* プログラムワンタッチワンタッチの時（Ｐ１～Ｐ８の'Ｐ'で判断します） */
	if (data == OPR_PROGRAM_MARK) {
		ret = TRUE;
	}
#endif

	return(ret);
}

/*************************************************************************
	module		:[電話状態検査]
	function	:[
		1.
	]
	return		:[
		TRUE	:電話使用中（オフフック・フックキーＯＮ）
		FALSE	:電話未使用
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/04]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckTelephoneUsing(void)
{
	UBYTE	ret;	/* リターン値 */

	ret = FALSE;

#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/07/22 */
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_HOOK_KEY_OFF_HOOK) ||
		((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL1_OFF_HOOK) && CheckIsKanyuLine()) ||
		((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL2_OFF_HOOK) && !(CheckIsKanyuLine()))) {
 
 #if 0 /* 警察FAX DVT by SMuratec 夏 2005/11/19 */
		if (((SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP) == 0)
		 && ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_BRC_LINE_VOLT_CHK) == 0)) {
		/** ハングアップエラーでない or ブランチ検出用回線電圧測定中でない */
			ret = TRUE;
		}
 #else
		if ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_BRC_LINE_VOLT_CHK) == 0) {
		/** ハングアップエラーでない or ブランチ検出用回線電圧測定中でない */
			ret = TRUE;
		}
		if ((SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP) == 0){
			ret = TRUE;
		}
		else{
			if ((Hangup_Line & SYS_TWICE_LINE_HANGUP) == SYS_TWICE_LINE_HANGUP){
				ret = FALSE;
			}
			else if (((Hangup_Line & SYS_LINE_KANYU_HANGUP) && !CheckIsKanyuLine())||
		  		((Hangup_Line & SYS_LINE_KEIDEN_HANGUP) && CheckIsKanyuLine())){
				ret = TRUE;
			}
			else{
				ret = FALSE;
			}
		}
 	
 #endif

	}
#else
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_TELEPHONE) {	/* 受話器上がりの時 */
		if (((SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP) == 0)
		 && ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_BRC_LINE_VOLT_CHK) == 0)) {
		/** ハングアップエラーでない or ブランチ検出用回線電圧測定中でない */
			ret = TRUE;
		}
	}
#endif		/* End of (defined (KEISATSU)) */

	return(ret);
}

/*************************************************************************
	module		:[指定カセットの記録紙サイズ獲得]
	function	:[
		1.指定されたカセット・手差しにセットされている記録紙サイズを返します
	]
	return		:[SYSDOC.Hに定義されている記録紙サイズ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/24]
	author		:[渡辺一章]
*************************************************************************/
UBYTE GetPaperSize(UBYTE cassette)
{
	UBYTE	paper_size;		/* 記録紙サイズ */

	switch (cassette) {
	case SYS_AUTO_CASSETTE:		/* 自動選択・指定なし */
	/* ポプラＢ(日本仕様)では自動選択・指定なしはできません */
#if (PRO_ADF_AUTO_CASSETTE == ENABLE)
	/* 自動カセット選択時、原稿幅から抽出した縮小率表示の為、サイズを返します。 By S.Fukui Jan.23,1998 */
		switch (PRN_GetPrintCassette(CMN_GetDocumentScanSize())) {
			case SYS_1ST_CASSETTE:		/* １段目カセット選択 */
				paper_size = SYS_Paper1Size;
				break;
			case SYS_2ND_CASSETTE:		/* ２段目カセット選択 */
				paper_size = SYS_Paper2Size;
				break;
			case SYS_3RD_CASSETTE:		/* ３段目カセット選択 */
				paper_size = SYS_Paper3Size;
				break;
			default:	/* 自動カセット選択時に手差しカセットは存在しないためこのパスは通らない。By S.Fukui Feb.19,1998 */
				paper_size = SYS_Paper1Size;
				break;
		}
#endif
		break;
	case SYS_1ST_CASSETTE:		/* １段目カセット選択 */
		paper_size = SYS_Paper1Size;
		break;
	case SYS_2ND_CASSETTE:		/* ２段目カセット選択 */
		paper_size = SYS_Paper2Size;
		break;
	case SYS_3RD_CASSETTE:		/* ３段目カセット選択 */
		paper_size = SYS_Paper3Size;
		break;
	case SYS_MANUAL_CASSETTE:	/* 手差しカセット選択 */
		paper_size = SYS_ManualPaperSize;
		break;
	default:
		break;
	}

	return(paper_size);
}

/*************************************************************************
	module		:[キー操作有効／無効検査]
	function	:[
		1.現在の機器状態より、押されたキーが有効かどうかをチェックします
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/28]
	author		:[渡辺一章]
*************************************************************************/
void CheckOperationValid(UBYTE *key_type)
{
#if (PRO_COPY_FAX_MODE == ENABLE)
	if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
		/* 用紙選択のカセット→手差しの変更確認中の時は、以下のキーは受け付けません */
		if (IsCassetteManualChange) {	/* カセット→手差しへの変更確認の時 */
			if ((*key_type == LEFT_ARROW)		/* 左矢印キー				*/
			 || (*key_type == FUNCTION)			/* 機能／右矢印キー			*/
			 || (*key_type == MAGNIFICATION)	/* 拡大キー					*/
			 || (*key_type == REDUCTION)		/* 縮小キー					*/
			 || (*key_type == SORT)				/* ソート・ダイヤル記号キー	*/
			 || (*key_type == SHARP)			/* テンキー ＃				*/
			 || (*key_type == START)) {			/* スタートキー				*/
				*key_type = ERROR_OPERATION;	/* 現在の状態では無効なキー	*/
			}
		}

		/* コピーモードで倍率入力中の時は、以下のキーは受け付けません */
		if (OPR_NumberKeyInputMode == OPR_COPY_MAGNIFI_INPUT_MODE) {	/* コピー倍率入力中 */
			if ((*key_type == LEFT_ARROW)		/* 左矢印キー				*/
			 || (*key_type == FUNCTION)			/* 機能／右矢印キー			*/
			 || (*key_type == MAGNIFICATION)	/* 拡大キー					*/
			 || (*key_type == REDUCTION)		/* 縮小キー					*/
			 || (*key_type == SORT)				/* ソート・ダイヤル記号キー	*/
			 || (*key_type == PAPER_SELECT)) {	/* 用紙選択キー				*/
				*key_type = ERROR_OPERATION;	/* 現在の状態では無効なキー	*/
			}
		}
	}
	else {						/* ファクスモードの時 */
		/* コピー以外の原稿蓄積で次原稿ありが選択されている時は、以下のキーしか受け付けません */
		if ((CheckExceptCopyDocStore()) && (SYS_NextBookDocument == TRUE)) {
			if ((*key_type != NEXT_DOC)			/* 次原稿キー				*/
			 && (*key_type != STOP)				/* ストップキー				*/
			 && (*key_type != COPY_FAX)			/* コピー／ファクスキー		*/
			 && (*key_type != BOOK_DOC_SIZE)	/* ブック原稿サイズキー		*/
			 && (*key_type != SINGLE)			/* 単一オペレーションキー	*/
			 && (*key_type != KEY_TIME_UP)		/* キー待ち終了				*/
			 && (*key_type != NO_EFFECT)) {		/* キーが押された以外		*/
				*key_type = ERROR_OPERATION;	/* 現在の状態では無効なキー	*/
			}
		}
	}
#endif
}

/*************************************************************************
	module		:[ＢＣＤ形式のストリングの比較]
	function	:[
				1.ＢＣＤ形式のストリング同士の比較
					( 0xff 又は 比較文字数まで )
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/20]
	author		:[桑原美紀]
*************************************************************************/
UBYTE Check_BCD_StringCompare(
						UBYTE *String1,				/* 比較ＢＣＤ文字列 */
						UBYTE *String2,				/* 比較ＢＣＤ文字列 */
						UBYTE StrLen )
{
	UBYTE	length;
	UBYTE	data1;
	UBYTE	data2;

	length = 0;

	for( length = 0; length < StrLen; length++ ){
		if (length%2) {/* 奇数 */
			data1 = (UBYTE)(*String1 & 0x0F);
			data2 = (UBYTE)(*String2 & 0x0F);
		}
		else { /* 偶数 */
			data1 = (UBYTE)((*String1 & 0xF0) >> 4);
			data2 = (UBYTE)((*String2 & 0xF0) >> 4);
		}
		if ( data1 != data2 ){		/* 同じﾃﾞｰﾀか */
			return( NG );
		}
		if (data1 == 0x0F) {		/* 終了コード */
			return( OK );
		}
		if((length+1)%2 == 0){		/* 偶数の時 */
			String1++;
			String2++;
		}
	}
	return( OK );
}

#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/07/11 Y.Matsukuma */
/*************************************************************************
	module		:[ワンタッチコードを数字におきかえる]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ＡからＵ８までを、それぞれ００・・・５９におきかえる]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/11]
	author		:[松隈]
*************************************************************************/
UBYTE	ChangeOnetouchCode(UWORD cursor_pos)
{
	UBYTE	data;

	data = InputNumber.Buffer[cursor_pos];

	if (data >= 0x31 && data <= 0x38) {	/* Ｕ１からＵ８の時 */
		data = data + 0x50;
		cursor_pos--;
	}
	data = (UBYTE)CMN_OnetouchCodeToOffset(data);	/* ワンタッチのキーコードをワンタッチ番号にかえる */
	return(data);
}
#endif

/*************************************************************************
	module		:[コピー原稿蓄積中検査]
	function	:[
		1.蓄積中の原稿がコピー原稿がどうかを調べます
	]
	return		:[
		TRUE	:コピー原稿の蓄積中
		FALSE	:蓄積中でないか、コピー原稿以外の原稿蓄積中
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/09/12]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckCopyDocStore(void)
{
	UBYTE	ret;

	ret = FALSE;

	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)		/* 原稿蓄積中			*/
	 && ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)			/* マルチコピーファイル	*/
	  || (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE))) {	/* 手差しコピーファイル	*/
		ret = TRUE;
	}

	return(ret);
}

/*************************************************************************
	module		:[コピー原稿以外の蓄積中検査]
	function	:[
		1.蓄積中の原稿がコピー原稿以外かどうかを調べます
	]
	return		:[
		TRUE	:コピー原稿以外の原稿蓄積中
		FALSE	:蓄積中でないか、コピー原稿の蓄積中
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/09/12]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckExceptCopyDocStore(void)
{
	UBYTE	ret;

	ret = FALSE;

	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)		/* 原稿蓄積中					*/
	 && ((SYS_DocumentStoreItem != SYS_MEM_MULTI_COPY_FILE)			/* マルチコピーファイルでない	*/
	  && (SYS_DocumentStoreItem != SYS_MEM_MANUAL_COPY_FILE))) {	/* 手差しコピーファイルでない	*/
		ret = TRUE;
	}

	return(ret);
}

/*************************************************************************
	module		:[実行・取り消し確認オペレーション]
	function	:[
		1.処理を実行するかの確認を行います
	]
	return		:[
		OPR_END			:中止・タイムアップ
		CONFIRM_EXEC	:実行
		CONFIRM_ABORT	:取り消し
	]
	common		:[]
	condition	:[]
	comment		:[
		引数説明
			*title_word		:上段表示ワーディングのポインター
			*confirm_word	:下段点滅表示ワーディングのポインター
			exec_key		:実行を行うキータイプ
			cancel_key		:取り消しを行うキータイプ

		注）ストップキーは無条件に中止を行います
		　　また、取り消しがストップキーの時は、return値は OPR_ENDを返します
		　　（この場合は CONFIRM_ABORTが返る事はありません）
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/11/07]
	author		:[渡辺一章]
************************************************************************/
UBYTE ConfirmKeyInputOperation(UBYTE *title_word, UBYTE *confirm_word, UBYTE exec_key, UBYTE cancel_key)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	ret;

	ret = 0xff;

	/* 画面表示 */
	DisplayStringHigh(0, title_word);
	FlashDisplayStringLow(confirm_word);

	while (ret == 0xff) {
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case STOP:			/* ストップキー */
		case KEY_TIME_UP:	/* タイムアップ */
			ret = OPR_END;
			break;
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif
		case NO_EFFECT:
			break;
		default:
			if (keytype == exec_key) {			/* 押されたキーが実行を行うキーの時 */
				ret = CONFIRM_EXEC;
			}
			else if (keytype == cancel_key) {	/* 押されたキーが取り消しを行うキーの時 */
				ret = CONFIRM_ABORT;
			}
			else {								/* 関係ないキーの時 */
				NackBuzzer();
			}
			break;
		}
	}
	return(ret);
}

#if defined(FRA)
/*************************************************************************
	module		:[（フランス仕様）ワンタッチ／短縮番号 重複番号チェック]
	function	:[
		1.	登録するﾀﾞｲﾔﾙ番号がﾜﾝﾀｯﾁに登録されていないかを調べる
		2.	登録するﾀﾞｲﾔﾙ番号が短縮に登録されていないかを調べる
	]
	return		:[
				ＴＲＵＥ	：ワンタッチ／短縮番号に同じ番号が存在する
				ＦＡＬＳＥ	：ワンタッチ／短縮番号に一致する番号がない
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/04]
	author		:[原田、福井]
*************************************************************************/
UBYTE CheckSameNumber()
{
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	i;		/* ﾙｰﾌﾟｶｳﾝﾄ変数 */
//	UBYTE	onetouchspeed_no;
#endif
	UWORD	i;		/* ﾙｰﾌﾟｶｳﾝﾄ変数 */
	UWORD	onetouchspeed_no;

	onetouchspeed_no = OPR_Buf.OntchSpdCtrl.SelectNumber;
	/* ASCデータから BCDデータに変換 */
	CMN_MemorySet(BCD_CheckBuffer , SYS_TEL_2DIGIT_MAX , 0xFF);
	CMN_ASC_ToBCD_StringNum(BCD_CheckBuffer,				/* 変換先アドレス */
							OPR_CharacterCheckBuffer,		/* 変換元アドレス */
							41);							/* ワンタッチ/短縮番号桁数＋１*/
	/*-------------------------------------------------------*/
	/** 登録するﾀﾞｲﾔﾙ番号がﾜﾝﾀｯﾁに登録されていないかを調べる */
	/*-------------------------------------------------------*/
	for ( i = 0; i < SYS_ONETOUCH_MAX ; i++ ) {
		if ((SYB_OnetouchDial[i].Dial[0] & 0xF0) != 0xF0 ) {			/** 登録されているﾜﾝﾀｯﾁが見つかった時 */
			if ((onetouchspeed_no < SYS_ONETOUCH_MAX) && (onetouchspeed_no == i)) {
				continue;
			} 
			if ( CheckBCDCompare( SYB_OnetouchDial[i].Dial,
							 BCD_CheckBuffer,
							 SYS_TEL_2DIGIT_MAX )
				 == TRUE ) {	/** 登録するﾀﾞｲﾔﾙ番号とﾜﾝﾀｯﾁのﾀﾞｲﾔﾙ番号を比較する */
				return( TRUE );
			}
		}
	}
	/*-------------------------------------------------------*/
	/** 登録するﾀﾞｲﾔﾙ番号が短縮に登録されていないかを調べる */
	/*-------------------------------------------------------*/
	for ( i = 0; i < SYS_SPEED_DIAL_MAX ; i++ ) {
		if ((SYB_SpeedDial[i].Dial[0] & 0xF0) != 0xF0 ) {			/** 登録されている短縮が見つかった時 */
			if ((onetouchspeed_no >= SYS_ONETOUCH_MAX) && ((onetouchspeed_no - SYS_ONETOUCH_MAX) == i)) {
				continue;
			}
			if ( CheckBCDCompare( SYB_SpeedDial[i].Dial,
							 BCD_CheckBuffer,
							 SYS_TEL_2DIGIT_MAX )
				 == TRUE ) {	/** 登録するﾀﾞｲﾔﾙ番号とﾜﾝﾀｯﾁのﾀﾞｲﾔﾙ番号を比較する */
				return( TRUE );
			}
		}
	}
	return( FALSE );
}

/*************************************************************************
	module		:[ＢＣＤダイヤル番号比較]
	function	:[
		1.２つのＢＣＤダイヤル番号を比較する
	]
	return		:[
		ＴＲＵＥ  ：等しい
		ＦＡＬＳＥ：等しくない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/04]
	author		:[原田、福井]
*************************************************************************/
UBYTE CheckBCDCompare(UBYTE *buffer1,		/* 比較するＢＣＤ列 */
				      UBYTE *buffer2,		/* 比較するＢＣＤ列 */
				      UBYTE compare_len)	/* 比較する長さ */
{
	UBYTE	i;		/* ﾙｰﾌﾟ変数 */

	for ( i = 0; i < compare_len; i++ ) {
		if ( *(buffer1 + i) != *(buffer2 + i) ) {
			return( FALSE );
		}
	}

	return( TRUE );
}
#endif

/*************************************************************************
	module		:[カーソル位置データ種別獲得]
	function	:[
		1.ダイヤル番号入力バッファでカーソル位置のデータの種別を調べます
		　注）カーソル位置が同報記号上の時は、カーソル位置より前のデータ種別を返します
	]
	return		:[
		OPR_CURSOR_DATA_NONE	:データが未入力
		OPR_CURSOR_DIRECT_DIAL	:カーソル位置のデータが直接ダイヤル
		OPR_CURSOR_ONETOUCH		:          〃          ワンタッチ
		OPR_CURSOR_SPEED		:          〃          短縮
		OPR_CURSOR_GROUP		:          〃          グループ
		OPR_CURSOR_DIRECT_ADDRESS:			〃			直接メールアドレス（ｲﾝﾀｰﾈｯﾄFAX用）
		OPR_CURSOR_INVALID_DATA	:無効なデータ（ダイヤル記号のみ）
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/03/12]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_DIAL_NAME_DISP == ENABLE) || (PRO_NEW_DIAL_OPR == ENABLE)
UBYTE GetCursorPositionDataKind(UBYTE is_get_data_info, UWORD *data_top_pos, UWORD *data_number)
{
	UWORD	i;				/* ループ変数									*/
	UWORD	data_head_pos;	/* カーソル位置のデータの先頭位置				*/
	UWORD	data_len;		/* 短縮番号・グループ番号・直接ダイヤルの桁数	*/
	UBYTE	*data_ptr;		/* 入力バッファのアドレス						*/
	UBYTE	onetouch_kind;	/* ワンタッチ種類（アンズで使用）				*/

	/* データ未登録時は、処理を行いません */
	if (InputNumber.WritePosition == 0) {
		return(OPR_CURSOR_DATA_NONE);	/* データが未入力 */
	}

	/* 現在のカーソル位置のダイヤル種別を調べるために、カーソル位置より前方にある同報記号か、
	** 入力バッファの先頭を検索します
	*/
	for (data_head_pos = InputNumber.CursorPosition; data_head_pos > 0; data_head_pos--) {	/* 入力バッファの先頭まで */
		if (InputNumber.Buffer[data_head_pos - 1] == ',') {	/* 検索位置が同報記号になった時 */
			break;
		}
	}
	data_ptr = &InputNumber.Buffer[data_head_pos];	/* カーソル位置のデータの先頭（短縮記号等）のアドレスをセット */

	if (is_get_data_info) {	/* カーソル位置のデータの情報が必要な時 */
		/* 同報記号の次の位置をセットします（ワンタッチの左かっこ・短縮記号等の位置） */
		*data_top_pos = data_head_pos;
	}

	if ((onetouch_kind = CheckOnetouchData(*data_ptr)) != OPR_EXCEPT_ONETOUCH) {	/* カーソル位置のデータがワンタッチの時 */
		if (is_get_data_info) {	/* カーソル位置のデータの情報が必要な時 */
 #if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
			data_ptr++;	/* 入力バッファのアドレスを、ワンタッチ番号の先頭に進めます */
			/* ワンタッチの配列番号を取得します */
			*data_number = (UWORD)ChangeNumberToOnetouch(data_ptr, ONETOUCH_OFFSET);
 #endif
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			/* Ａ～Ｚ，ａ～ｚの時 */
			if (onetouch_kind == OPR_ONETOUCH_ALPHABET) {
				*data_number = CMN_OnetouchCodeToOffset(*data_ptr);
			}
			/* Ｕ１～Ｕ８の時 */
			else {
				data_ptr++;
				*data_number = (UWORD)ChangeNumberToOnetouch(data_ptr, ONETOUCH_OFFSET);
			}
 #endif
		}
		return(OPR_CURSOR_ONETOUCH);	/* カーソル位置のデータがワンタッチ */
	}
	else if (*data_ptr == OPR_SPEED_MARK) {						/* カーソル位置のデータが短縮の時 */
		if (is_get_data_info) {	/* カーソル位置のデータの情報が必要な時 */
			data_ptr++;	/* 入力バッファのアドレスを、短縮番号の先頭に進めます */
			data_len = GetStringGapPoint(data_ptr, ',');	/* 短縮番号の桁数を取得します */
			if (data_len > SPEED_FIGURE_MAX) {	/* 短縮番号が最大桁数を超えている時 */
				/* 番号エラー判断用に、最大値をセットします */
				*data_number = 0xFFFF;
			}
			else {											/* 短縮番号が有効範囲内の時 */
				/* 短縮の配列番号を取得します */
				if (CHK_UNI_OptionalSpeedDial() == 0) {	/* 通常の短縮の時 */
#if (0)	/* 短縮０指定の後、同報キーを押すと"ｹﾀｽｳ ｵｰﾊﾞｰ ﾃﾞｽ      "のエラー表示をする不具合対応
		** （本当は"ﾀﾀﾞｼｲ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ"が正解です） by K.Watanabe 1999/01/25
		*/
//					*data_number = CMN_ASC_ToUnsignedInt(data_ptr, data_len) - OPR_SPEED_DIAL_MIN;
#endif
					*data_number = CMN_ASC_ToUnsignedInt(data_ptr, data_len);
					if ((OPR_SPEED_DIAL_MIN > 0) && (*data_number == 0)) {	/* 短縮最小値が１以上で、短縮０指定の時 */
						*data_number = SYS_SPEED_DIAL_MAX;	/* 範囲指定エラーになるように短縮最大値の次をセットします */
					}
					else {
						*data_number -= OPR_SPEED_DIAL_MIN;	/* 短縮番号を配列番号に変換します */
					}
				}
				else {									/* 任意短縮の時 */
					*data_number = SetOptionalSpeedStatus(CMN_ASC_ToUnsignedInt(data_ptr, data_len));
					if (*data_number == 0xFF) {	/* 任意短縮未登録の時 */
						/* 短縮未登録エラー判断用の値をセットします */
						*data_number = 0xFFFE;
					}
				}
			}
		}
		return(OPR_CURSOR_SPEED);	/* カーソル位置のデータが短縮 */
	}
	else if (*data_ptr == OPR_GROUP_MARK) {						/* カーソル位置のデータがグループの時 */
		if (is_get_data_info) {	/* カーソル位置のデータの情報が必要な時 */
			data_ptr++;	/* 入力バッファのアドレスを、グループ番号の先頭に進めます */
			data_len = GetStringGapPoint(data_ptr, ',');	/* グループ番号の桁数を取得します */
			if (data_len > GROUP_FIGURE_MAX) {	/* グループ番号が最大桁数を超えている時 */
				/* 番号エラー判断用に、最大値をセットします */
				*data_number = 0xFFFF;
			}
			else {									/* グループ番号が有効範囲内の時 */
				/* グループ番号を取得します */
				*data_number = CMN_ASC_ToUnsignedInt(data_ptr, data_len);
			}
		}
		return(OPR_CURSOR_GROUP);	/* カーソル位置のデータがグループ */
	}
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/13 by K.Okada */
	else if (*data_ptr == DIRECT_ADDRESS_MARK) {
		return (OPR_CURSOR_DIRECT_ADDRESS);
	}
 #endif
	else {														/* カーソル位置のデータが直接ダイヤルの時 */
		/* 直接ダイヤルの中に、数字があるかを調べます（'-/'等だけの時は、データ未入力を返します） */
		data_len = GetStringGapPoint(data_ptr, ',');	/* 直接ダイヤルの桁数を取得します */
		if (data_len == 0) {	/* データ未入力（カーソル先頭以外）の時 */
			/* カーソル位置が先頭でなく、データの桁数が０と言うのは、ダイヤルデータ入力後に
			** 同報キーが押された後しかありえないので、この場合はデータ未入力を返しておきます
			*/
			return(OPR_CURSOR_DATA_NONE);	/* データが未入力 */
		}
		else {
			for (i = 0; i < data_len; i++) {	/* 直接ダイヤルの最後まで */
				if (CMN_isdigit(*data_ptr++)) {	/* 直接ダイヤルの中で数字が見つかった時 */
					return(OPR_CURSOR_DIRECT_DIAL);	/* カーソル位置のデータが直接ダイヤル */
				}
			}
			return(OPR_CURSOR_INVALID_DATA);	/* 無効なデータ（ダイヤル記号のみ） */
		}
	}
}
#endif	/* (PRO_DIAL_NAME_DISP == ENABLE) || (PRO_NEW_DIAL_OPR == ENABLE) */

/*************************************************************************
	module		:[ワンタッチ・短縮相手先名表示]
	function	:[
		1.指定されたワンタッチ・短縮の相手先名が登録されていれば表示し、
		　未登録の時は、ダイヤル番号を表示します
	]
	return		:[相手先名・ダイヤル番号桁数]
	common		:[]
	condition	:[
		この関数は、必ず登録されているデータに対してのみ使用する事
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/03/17]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_DIAL_NAME_DISP == ENABLE)
UBYTE SetOnetouchSpeedDialName(UBYTE *dsp_buf, UBYTE data_kind, UWORD data_number)
{
	UBYTE	ret;								/* リターン値	*/
	struct SYS_SpeedDialData_t	*dial_data_ptr;	/* ワンタッチ・短縮ダイヤルデータのポインター */
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/15 by K.Okada */
	UBYTE	fax_number_flag;
	struct SYS_INF_OnetouchData_t *mail_onetouch_ptr;
 #endif

 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/15 by K.Okada */
	fax_number_flag = 1;
	/* ダイヤルデータのポインターをセットします */
	if (data_kind == OPR_CURSOR_ONETOUCH) {	/* ワンタッチの相手先名を表示する時 */
		if (SYB_INF_OnetouchStatus[data_number] == SYS_INF_ONETOUCH_FAXNUMBER) {
			dial_data_ptr = &SYB_OnetouchDial[data_number];
		}
		else if (SYB_INF_OnetouchStatus[data_number] == SYS_INF_ONETOUCH_MAILADDRESS) {
			mail_onetouch_ptr = &SYB_INF_Onetouch[data_number];
			fax_number_flag = 0;
		}
	}
	else {									/* 短縮の相手先名を表示する時 */
		dial_data_ptr = &SYB_SpeedDial[data_number];
	}

	if (fax_number_flag) {
		/* 相手先名（相手先番号）を指定のバッファに格納します */
		if (dial_data_ptr->Name[0] != NULL) {	/* 相手先名が登録されている時 */
			/* 表示用バッファに相手先名をコピー */
			CMN_StringCopy(dsp_buf, dial_data_ptr->Name);
			ret = CMN_StringLength(dial_data_ptr->Name);
		}
		else {									/* 相手先名が未登録の時 */
			/* 表示用バッファにダイヤル番号をコピー */
			CMN_BCD_ToASC_StringNum(dsp_buf, dial_data_ptr->Dial, OPR_DISPLAY_MAX);
			ret = GetBCD_StringLength(dial_data_ptr->Dial);
		}
	}
	else {
		if (mail_onetouch_ptr->Name[0] != NULL) {
			CMN_StringCopyNumNotNULL(dsp_buf, mail_onetouch_ptr->Name, OPR_DISPLAY_MAX);
			if ((ret = CMN_StringLength(mail_onetouch_ptr->Name)) >= OPR_DISPLAY_MAX) {
				ret = OPR_DISPLAY_MAX;
			}
		}
		else {
			CMN_StringCopyNumNotNULL(dsp_buf, mail_onetouch_ptr->MailAddress, OPR_DISPLAY_MAX);
			if ((ret = CMN_StringLength(mail_onetouch_ptr->MailAddress)) >= OPR_DISPLAY_MAX) {
				ret = OPR_DISPLAY_MAX;
			}
		}
	}
 #else
	/* ダイヤルデータのポインターをセットします */
	if (data_kind == OPR_CURSOR_ONETOUCH) {	/* ワンタッチの相手先名を表示する時 */
		dial_data_ptr = &SYB_OnetouchDial[data_number];
	}
	else {									/* 短縮の相手先名を表示する時 */
		dial_data_ptr = &SYB_SpeedDial[data_number];
	}

	/* 相手先名（相手先番号）を指定のバッファに格納します */
	if (dial_data_ptr->Name[0] != NULL) {	/* 相手先名が登録されている時 */
		/* 表示用バッファに相手先名をコピー */
		CMN_StringCopy(dsp_buf, dial_data_ptr->Name);
		ret = CMN_StringLength(dial_data_ptr->Name);
	}
	else {									/* 相手先名が未登録の時 */
		/* 表示用バッファにダイヤル番号をコピー */
		CMN_BCD_ToASC_StringNum(dsp_buf, dial_data_ptr->Dial, OPR_DISPLAY_MAX);
		ret = GetBCD_StringLength(dial_data_ptr->Dial);
	}
 #endif	/* PRO_DIALUP_INTERNET_FAX 1998/04/15 by K.Okada */

	return(ret);
}
#endif	/* (PRO_DIAL_NAME_DISP == ENABLE) */

#if (PRO_RX_DOC_TRANSFER == ENABLE) || (PRO_FCODE_RELAY == ENABLE) /* By H.Fujimura 1999/01/06 */
/*************************************************************************
	module		:[ダイヤルデータ表示用バッファ展開処理]
	function	:[
		1.ビットアサインでセットされているダイヤルデータを表示用に編集し、バッファにセットします。
	]
	return		:[最終セット位置の次の位置]
	common		:[]
	condition	:[]
	comment		:[
		メモリ送信原稿蓄積時の表示から呼ばれた時、表示用ﾊﾞｯﾌｧのサイズを超えてセットしてしまうため
		いったん作業用ﾊﾞｯﾌｧにセットしてから、表示用ﾊﾞｯﾌｧにセットしなおすように変更します。
		作業用ﾊﾞｯﾌｧには、( "," + ﾀﾞｲｱﾙ40桁 + "*" ＋ PIN番号8桁 + NULL ) → 51Byte をとります。
		1998/03/25 By T.Fukumoto
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
void SetDialDataToDispBuffer2(UBYTE set_kind, UBYTE *Direct, UBYTE *Onetouch, UBYTE *Speed, UDWORD Group, UBYTE *disp_buffer)
{
	UBYTE	i;				/* ﾙｰﾌﾟ変数 */
	UBYTE	count;			/* 直接ﾀﾞｲﾔﾙ取得用ｶｳﾝﾀ */
	UBYTE	dial_data;		/* 直接ﾀﾞｲﾔﾙ取得用ﾊﾞｯﾌｧ */
	UBYTE	data_count;		/* 相手先数 */
	UWORD	disp_position;	/* 入力位置 */
	UWORD	no;				/* 任意短縮番号 */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	UBYTE	onetouch;
#endif
	UWORD			data_position;								/* 作業用入力位置 */
	static UBYTE	data_buffer[OPR_TELCONTROL_BUFFER_MAX + 1];	/* 作業用ﾊﾞｯﾌｧ */

	disp_position = 0;
	data_count = 1;

	/*------------------------------*/
	/* ワンタッチダイヤルの展開処理 */
	/*------------------------------*/
	for (i = 0; i < SYS_ONETOUCH_MAX; i++) {
		if (CMN_CheckBitAssign(Onetouch, i) == TRUE) {
			data_position = 0;												/* 作業用入力位置の初期化 */
			CMN_MemorySetNULL(data_buffer, OPR_TELCONTROL_BUFFER_MAX, ' ');	/* 作業用ﾊﾞｯﾌｧの初期化 */

			/* 複数宛先の場合、宛先の番号と番号の間に区切りの','を挿入する */
			if (disp_position) {
				data_buffer[data_position++] = ',';
				data_count++;
			}
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
			data_buffer[data_position++] = OPR_ONETOUCH_MARK_LEFT;
			CMN_UnsignedIntToASC(&data_buffer[data_position], (UWORD)(i + 1), 2, '0');
			data_position += 2;
			data_buffer[data_position++] = OPR_ONETOUCH_MARK_RIGHT;
#else	/* (PRO_KEYPANEL == PANEL_ANZU_L) */
			if (i <= 51) {
				/* Ａからｚ */
				data_buffer[data_position] = OnetouchTable[i];
			}
			else {
				/* Ｕ１からＵ８ */
				data_buffer[data_position] = OPR_ONETOUCH_MARK;
				data_position++;
				onetouch = i;
				CMN_UnsignedIntToASC(&data_buffer[data_position], (UWORD)(onetouch - 51), 1, '0');
			}
			data_position += OPR_ONETOUCH_NUMBER_FIGURE;
#endif
			/* メモリ送信原稿蓄積時の表示で２０桁を超えた時 */
			if (CheckSettingDataLength(set_kind, disp_position + data_position) == FALSE) {
				/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開し、処理を抜けます */
				CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, OPR_DISPLAY_MAX - disp_position );
				return;
			}

			/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開します */
			CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, data_position );
			disp_position += data_position;
		}
	}

	/*------------------------*/
	/* 短縮ダイヤルの展開処理 */
	/*------------------------*/
	for (i = 0; i < SYS_SPEED_DIAL_MAX; i++) {
		if (CMN_CheckBitAssign(Speed, i) == TRUE) {
			data_position = 0;												/* 作業用入力位置の初期化 */
			CMN_MemorySetNULL(data_buffer, OPR_TELCONTROL_BUFFER_MAX, ' ');	/* 作業用ﾊﾞｯﾌｧの初期化 */

			/* 複数宛先の場合、宛先の番号と番号の間に区切りの','を挿入する */
			if (disp_position) {
				data_buffer[data_position++] = ',';
				data_count++;
			}
			data_buffer[data_position++] = OPR_SPEED_MARK;
			if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮の時 */
				CMN_UnsignedIntToASC(&data_buffer[data_position],(UWORD)(i + OPR_SPEED_DIAL_MIN),SPEED_FIGURE_MAX,'0');
				data_position += SPEED_FIGURE_MAX;
			}
			else{									/* 任意短縮の時 */
				no = GetRecordFromNumber(i);
				if (no != 0xFFFF) {
					CMN_UnsignedIntToASC(&data_buffer[data_position], no, SPEED_FIGURE_MAX, '0');
					data_position += SPEED_FIGURE_MAX;
				}
				else {
					CMN_MemorySet(&data_buffer[data_position], SPEED_FIGURE_MAX, '*');
					data_position += SPEED_FIGURE_MAX;
				}
			}

			/* メモリ送信原稿蓄積時の表示で２０桁を超えた時 */
			if (CheckSettingDataLength(set_kind, disp_position + data_position) == FALSE) {
				/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開し、処理を抜けます */
				CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, OPR_DISPLAY_MAX - disp_position );
				return;
			}

			/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開します */
			CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, data_position );
			disp_position += data_position;
		}
	}

	/*------------------------*/
	/* 直接ダイヤルの展開処理 */
	/*------------------------*/
	if (Direct != NULL) {
		if ((Direct[0] & 0xF0) != 0xF0) {
			data_position = 0;												/* 作業用入力位置の初期化 */
			CMN_MemorySetNULL(data_buffer, OPR_TELCONTROL_BUFFER_MAX, ' ');	/* 作業用ﾊﾞｯﾌｧの初期化 */

			/* 複数宛先の場合、宛先の番号と番号の間に区切りの','を挿入する */
			if (disp_position) {
				data_buffer[data_position++] = ',';
				data_count++;
			}
			count = 0;
			while (1) {
				dial_data = Direct[count];
				if (((dial_data & 0xF0) != 0xF0) && ((dial_data & 0x0F) != 0x0F)) {
					data_buffer[data_position++] = CMN_BCD_ToASC((UBYTE)((dial_data & 0xF0) >> 4));
					data_buffer[data_position++] = CMN_BCD_ToASC((UBYTE)(dial_data & 0x0F));
					count++;
				}
				else {
					if (((dial_data & 0xF0) != 0xF0) && ((dial_data & 0x0F) == 0x0F)) {
						data_buffer[data_position++] = CMN_BCD_ToASC((UBYTE)((dial_data & 0xF0) >> 4));
						break;
					}
					else {
						break;
					}
				}
			}

			/* メモリ送信原稿蓄積時の表示で２０桁を超えた時 */
			if (CheckSettingDataLength(set_kind, disp_position + data_position) == FALSE) {
				/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開し、処理を抜けます */
				CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, OPR_DISPLAY_MAX - disp_position );
				return;
			}

			/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開します */
			CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, data_position );
			disp_position += data_position;
		}
	}

	/*---------------------*/
	/* グループの展開処理  */
	/*---------------------*/
	if (Group == 0xffffffff) {
		data_position = 0;												/* 作業用入力位置の初期化 */
		CMN_MemorySetNULL(data_buffer, OPR_TELCONTROL_BUFFER_MAX, ' ');	/* 作業用ﾊﾞｯﾌｧの初期化 */

		/* 複数宛先の場合、宛先の番号と番号の間に区切りの','を挿入する */
		if (disp_position) {
			data_buffer[data_position++] = ',';
			data_count++;
		}
		data_buffer[data_position++] = OPR_GROUP_MARK;
		data_buffer[data_position++] = '0';

		/* メモリ送信原稿蓄積時の表示で２０桁を超えた時 */
		if (CheckSettingDataLength(set_kind, disp_position + data_position) == FALSE) {
			/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開し、処理を抜けます */
			CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, OPR_DISPLAY_MAX - disp_position );
			return;
		}

		/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開します */
		CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, data_position );
		disp_position += data_position;
	}
	else {
		for (i = 0; i < SYS_GROUP_NUMBER_MAX; i++) {
			if (CMN_CheckLongBitAssign(Group, i) == TRUE) {
				data_position = 0;												/* 作業用入力位置の初期化 */
				CMN_MemorySetNULL(data_buffer, OPR_TELCONTROL_BUFFER_MAX, ' ');	/* 作業用ﾊﾞｯﾌｧの初期化 */

				/* 複数宛先の場合、宛先の番号と番号の間に区切りの','を挿入する */
				if (disp_position) {
					data_buffer[data_position++] = ',';
					data_count++;
				}
				/** グループのマークをセット */
				data_buffer[data_position++] = OPR_GROUP_MARK;
				/* グループ番号をセット */
				CMN_UnsignedIntToASC(&data_buffer[data_position], (UWORD)(i + 1), GROUP_FIGURE_MAX, '0');
				data_position += GROUP_FIGURE_MAX;

				/* メモリ送信原稿蓄積時の表示で２０桁を超えた時 */
				if (CheckSettingDataLength(set_kind, disp_position + data_position) == FALSE) {
					/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開し、処理を抜けます */
					CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, OPR_DISPLAY_MAX - disp_position );
					return;
				}

				/* 作業用ﾊﾞｯﾌｧから表示用ﾊﾞｯﾌｧに展開します */
				CMN_StringCopyNumNotNULL(disp_buffer + disp_position, data_buffer, data_position );
				disp_position += data_position;
			}
		}
	}

	/* プログラムワンタッチ登録からCallされた時 */
	if (set_kind == OPR_PROGRAM_DISPLAY) {
		if (GetStringGapPoint(&InputNumber.Buffer[0], ',') < disp_position) {	/* 同報の時 */
			InputNumber.MultiNumberStatus = 1;
		}

		/*--------------------------------*/
		/* カーソルをデータの後に移動する */
		/*--------------------------------*/
		InputNumber.WritePosition = disp_position;
		InputNumber.CursorPosition = disp_position;
	}

	/* プログラム送信コマンド展開からCallされた時 */
	if (set_kind == OPR_PROGRAM_EXECUTE) {
		/* プログラムワンタッチのダイアル番号が歯抜けに登録されることはないので、
		** data_countの値をそのまま宛先数として信用していい
		*/
		InputNumber.MultiNumberStatus = FinalBroadcastCheck(data_count);

		/*----------------------------------*/
		/* カーソルをデータの後に移動する   */
		/*----------------------------------*/
		InputNumber.WritePosition = disp_position;
		InputNumber.CursorPosition = disp_position;
	}
}
#endif	/* (PRO_RX_DOC_TRANSFER == ENABLE) || (PRO_FCODE_RELAY == ENABLE) */


/*************************************************************************
	module		:[原稿読み取り不可能状態検査]
	function	:[
		1.ジャムリカバー動作等の読み取り継続確認のエラーをチェックします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		1.ソートコピー原稿読み取り開始後に、ダイヤル番号を押す
		2.２枚目の原稿読み取り中にジャムを起こす
		3.ジャム解除後、原稿をセットしてスタートキーを押す
		4.コマンド消去できない送信を開始する（その後、コピーもできなくなる）
		上記不具合修正の為に、読み取り開始時にジャムリカバーオペレーション等が
		起こっているかをチェックする様にします
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/07/15]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckScanDisableCondition(void)
{
	if ((SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MEMORY_OVER_OPR)		/* メモリーオーバー処理 */
		|| (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_JAM_RECOVER_OPR)	/* ジャムリカバー処理 */

#if (PRO_CIPHER == ENABLE)
		|| (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_WRONG_KEY_ERROR)				/** 復号化時キー間違い処理 */
		|| (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_FIRST_PAGE)		/** 受信暗号化原稿消去確認処理 */
#endif

		|| (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FBS_RECOVER_OPR)) {	/* ＦＢＳ読み取り中断リカバー処理 */
		return(TRUE);
	}
	else {
		return(FALSE);
	}
}

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/18 */
UBYTE CheckIsKanyuLine(void)
{
	if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_LINE) {
		return(TRUE);
	}
	else {
		return(FALSE);
	}
	
	return(FALSE);
}

UBYTE CheckIsKobetsuMode(void)
{
	if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_MODE) {
		return(TRUE);
	}
	else {
		return(FALSE);
	}
	
	return(FALSE);
}

UBYTE CheckIsScrambleOFF(void)
{
	if (CheckIsKanyuLine()) {		/*	加入回線	*/
		if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SCRAMBLE_KANYU) {
			return(TRUE);
		}
		else {
			return(FALSE);
		}
	}
	else {							/*	警電回線	*/
		if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SCRAMBLE_KEIDEN) {
			return(TRUE);
		}
		else {
			return(FALSE);
		}
	}
	
	return(FALSE);
}

UBYTE CheckIsSenyou(void)
{
	if (SYB_SettingStatus[SETTING_STATUS_31] & SETTING_SENYOU) {
		return(TRUE);
	}
	else {
		return(FALSE);
	}
	
	return(FALSE);
}

UBYTE CheckKeidenRxPriorityON(void)
{
	if (SYB_MachineParameter[M_PARA_SW_I0] & KEIDEN_RX_PRIORITY) {
		return(TRUE);
	}
	else {
		return(FALSE);
	}

	return(FALSE);
}
#endif		/* End of (defined (KEISATSU)) */
