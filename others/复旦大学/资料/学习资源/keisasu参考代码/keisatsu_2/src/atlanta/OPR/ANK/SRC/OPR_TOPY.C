/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_TOP.C
*	Author		: 渡辺一章
*	Date		: 1996/10/23
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: オペレーションメインルーチン
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\mem_def.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\sysprint.h"
#include	"\src\atlanta\define\sysrxsw.h"
#include	"\src\atlanta\define\sysscan.h"
#include	"\src\atlanta\define\mntsw_c.h"
#if (PRO_MODEM == ORANGE3)
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#endif
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\atlanta\define\mntsw_i.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\sh7043\define\sh_port.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include	"\src\atlanta\sh7043\ext_v\extv_sem.h"
#endif

#if (PRO_MULTI_LINE == ENABLE)
#include	"\src\atlanta\define\mlt_pro.h"
#endif

#if (PRO_CIPHER == ENABLE)
#include	"\src\atlanta\scd\ext_v\cph_data.h"
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /*1998/05/28 Eguchi*/
extern UBYTE INF_DEBUG_IsStopReceive;
#endif

#if (PRO_CLASS1 == ENABLE) /* S.Fukui Jun.19,1998 */
#include "\src\atlanta\define\cl1_def.h"
#endif

/* Prototype
void	OPR_Task(void);
void	OperationStart(void);
void	OperationEnd(void);
void	HookKeyOperation(void);
void	StopKeyOperation(void);
#if (PRO_CIPHER == ENABLE)
void	ConfirmStopCipherExecuting(void);
#endif
void	MemoryOverOperation(void);
void	JamRecoverOperation(UBYTE);
#if (PRO_FBS == ENABLE)
void	NextDocStoreOperation(void);
#endif
#if (PRO_CIPHER == ENABLE)
void	DifferentKeyOperation(void);
#endif
void	DisplayChildError(void);
UBYTE	OperationProtectReset(UBYTE);
*/

/*************************************************************************
	module		:[オペレーションタスクメイン]
	function	:[
		1.ファーストキーを取り込み、各オペレーションに分岐する
	]
	return		:[なし]
	common		:[
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/17]
	author		:[江口,渡辺一章]
*************************************************************************/
void OPR_Task(void)
{
	UBYTE	key;		/* キー入力 */
	UBYTE	keytype;	/* キー入力 */
#if (PRO_COPY_FAX_MODE == ENABLE)
	UBYTE	last_key;	/* 前回キー入力値 */
#endif

	/** 子タスク生成 1995/04/10 Eguchi*/
	cre_tsk(&tskno_OPR_SheetCheckTask, TSK_OPR_CHECKSHEETTASK,   0);	/** ワンタッチシートチェックタスク起動	*/
	cre_tsk(&tskno_OPR_KeyTask,        TSK_OPR_KEYTASK,          0);	/** キースキャンタスク起動				*/
	cre_tsk(&tskno_OPR_BuzzerTask,     TSK_CMN_BUZZERTASK,       0);	/** ブザータスク起動					*/
	cre_tsk(&tskno_OPR_DispFlashTask,  TSK_OPR_DISPLAYFLASHTASK, 0);	/** 点滅表示用タスク起動				*/

	/** ＬＥＤの初期化 */
	LED_Initial();

	/** メッセージのItem初期化 */
	OperationMessageToMain.Item = FROM_OPERATION;

#if (PRO_COPY_FAX_MODE == ENABLE)
	/* コピーモード設定値の初期化（必ずCMN_InitializeAllBackUpRAM()の後にCALLする事）
	** もともとは、MAN_InitializeRAM()で実行していたがカセットの初期段数を決定するのに
	** センサータスクの情報が必要になるので、OPR_Task()に移動しました
	*/
	ClearCopyParameter();

	key = OPR_NO_KEY;	/* 前回キー入力値用に初期化します */
#endif

	while (1) {	/** 無限ループ */
#if (PRO_COPY_FAX_MODE == ENABLE)
		last_key = key;	/* 前回キー入力値の退避 */
#endif

		/** キー取り込み */
#if (PRO_COPY_FAX_MODE == ENABLE)
		/* １分間キーが未入力の時は、コピーパラメータを初期化する仕様なので、キーの待ち時間にて対応します */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);	/* １分間キー待ち */
#else
		OPR_GetKey(KEY_WAIT_FOREVER);		/* 無限待ち */
#endif
		key     = GetInputKeyCode();
		keytype = GetInputKeyType();

		OperationStart();

#if (PRO_PRINT_TYPE == LED)
		/* パワーＯＮ時のウォームアップ中は、キー操作禁止 */
		if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PRINTER_POWER_ON) {
#if (0)	/* by K.Watanabe 1998/04/30 */
// #if (PRO_KEYPANEL == PANEL_POPLAR_B)
//			/* 電源ONした時に、何も押していないのにNackが鳴る現象のデバッグ用に追加 by K.Watanabe 1998/04/28 */
//			DisplayPrinterWarmUp();
// #endif
#endif
			NackBuzzer();
			OperationEnd();
			continue;
		}
#endif

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
		/* フラッシュＲＯＭ書き換え中なら、キー入力させない */
		if (SYB_FlashROM_WriteStatus != NO_STATUS) {
			if ((key == OPR_GET_KEY_TIMEUP) || (key == OPR_SHEET_CHANGE)) {
				/* ﾜﾝﾀｯﾁｼｰﾄ切り替え時、コピーパラメーター優先表示のタイムオーバーの時ﾅｯｸならさない */
			}
			else {
				NackBuzzer();
			}
			OperationEnd();
			continue;
		}
#endif

		/* オペレーションプロテクトのチェック */
		if (OperationProtectReset(keytype) == NG) {
			if (CheckChildErrorDisplayReq() == TRUE) {	/* エラー等のチャイルド表示要求があれば */
				DisplayChildError();	/* チャイルド表示実行 */
			}
			OperationEnd();
			continue;
		}

		/* 現在の状態より押されたキーが有効かどうかをチェックします */
		CheckOperationValid(&keytype);

#if (PRO_COPY_FAX_MODE == ENABLE)
		if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
			/* CopyOperation()では、コピーモード専用の処理しか行っていないので、それ以外はメインで処理を行います */
			if (CopyOperation(key, keytype, last_key) == TRUE) {	/* 既に処理をおこなった場合 */
				keytype = NO_EFFECT;	/* メインでは処理は行いません */
			}
		}
#endif

		/** 取り込んだキーに対する処理 */
		switch (keytype) {	/* キータイプで分岐する *//* モジュールに渡す（実際に処理に使う)のはキーコード */
		case HOOK:			/* フック／会話予約			*/
			HookKeyOperation();
			break;

		case FUNCTION:		/* 機能キー					*/
			FunctionOperation();
			if (SpecialCommandValue.Page != 0) {	/** 枚数指定オペレーションが実行された場合 */
				/** コマンドオペレーションを実行する */
				CommandOperation(OPR_NO_KEY, NO_EFFECT);
			}
			break;

		case REVIEW:		/* 通信確認キー				*/
			ReviewCommandOperation();
			break;

		case STOP:			/* ストップキー				*/
			StopKeyOperation();
#if (0)
//#if (PRO_PC_PRINT == ENABLE)	/* 追加 by M.Kuwahara 1998/02/12 */
//			SYS_MachineStatus[SYS_ERROR_STATUS] &= ~SYS_ERROR_PC_MEMORY_OVER;
//			SYS_PcMemoryOverDispRequest = 0;	/* PCメモリオーバ表示消去の為 */
//#endif
#endif
			break;

#if (PRO_COPY_FAX_MODE == ENABLE)
		case COPY_FAX:		/* コピー／ファクスキー		*/
			CopyFaxKeyOperation();
			break;
#else
		case COPY:			/* コピーキー				*/
			CopyKeyOperation();
			break;
#endif

#if (PRO_FBS == ENABLE)
		case NEXT_DOC:		/* 次原稿キー				*/
			/* ここで次原稿の変更を行うのは、ＡＤＦに原稿がセットされた直後か、原稿読み取り中なので
			** CommandOperation()をcallすると表示が上書きされてしまうので、直接関数をcallします
			** 逆にＡＤＦに原稿が設定されていない時は、ブック原稿サイズが設定されていないと次原稿の
			** 設定は行えないので、ここでは変更しません（CommandOperation()の中からcallします）
			*/
			BookNextDocumentSet(key, FALSE);
			break;
		case BOOK_DOC_SIZE:	/* ブック原稿サイズキー		*/
			/* 原稿蓄積中にCommandOperation()に入ってしまうと、送信・原稿読み取りが開始されないまま
			** 抜けてしまうために、次原稿がなしに初期化されてしまうので、事前に判断を追加します
			** by K.Watanabe 1998/02/13
			*/
			if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {
				NackBuzzer();
			}
			else {
				CommandOperation(key, keytype);
			}
			break;
		case KEY_TIME_UP:	/* キー待ちタイムオーバー	*/
			/* コピースキャン中以外の時、コピーモードのパラメータを初期化します */
			if (!CheckCopyDocStore()) {
				if (SYB_MaintenanceSwitch[MNT_SW_C6] & 0x02) {
					break; /* 連続コピーテストの時はリセットしない T.Nose 1998/01/14 */
				}
				ClearCopyParameter();
			}
			break;
#endif	/* (PRO_FBS == ENABLE) */

		case REDIAL:		/* リダイヤルキー			*/	/* ｵﾌﾌｯｸの状態になったらすでにTeloperation()に入っているはず */
/* ＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮ対応 1998/03/12 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			if (CMN_CheckAramcoModel() == 1) {
				NackBuzzer();
				break;
			}
#endif
		case BROADCAST:		/* 同報キー					*/
		case SPECIAL:		/* 応用通信キー				*/
		case GROUP:			/* グループキー				*/
		case DIALMARK:		/* ダイアル記号キー			*/
		case SPEED:			/* 短縮キー					*/
		case AST:			/* テンキー ＊				*/
		case SHARP:			/* テンキー ＃				*/
		case NUMBER:		/* テンキー					*/
		case ONETOUCH:		/* ワンタッチキー			*/
		case PROGRAM:		/* プログラムワンタッチキー	*/
#if (PRO_KEYPANEL == PANEL_POPLAR_L)
		case TONE:			/* トーンキー				*/	/* 追加 97/11/13 T.Fukumoto */
#endif
#if !defined(JPN) || (PRO_KEYPANEL == PANEL_ANZU_L)
		case FLASH:			/* フラッシュキー			*/
#endif
#if defined(GBR)	/* 1996/06/26 H,Yagi */
		case MERCURY:
#endif
#if defined(DEU)	/* for GroundKey '98/03/11 M.HARADA */
		case GROUND:
#endif
			CommandOperation(key, keytype);
			if (OPR_TelBookTelephoneFlag) { /* コマンドオペレーション中に電話帳オペレーションを行い。結果電話発呼の場合 */
				TelOperation(OPR_TELBOOK_TEL, NO_EFFECT);
			}
			break;

#if (PRO_MULTI_LINE == ENABLE)		/* 移動･追加 97/11/05 T.Fukumoto */
 #if (PRO_KEYPANEL == PANEL_POPLAR_B)	/* by K.Watanabe 1998/01/16 */
		case COPY_RESET:	/* コピーリセットキー		*/
 #else
		case HOLD:			/* 保留キー					*/
 #endif
 #if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)
			/* ２回線以上ない時は、セットできない */
			if (OPT_CountModems() <= 1) {
				NackBuzzer();
				break;
			}
 #endif
			CommandOperation(key, keytype);	/* 内線番号を示す「！」を入力 */
			if (OPR_TelBookTelephoneFlag) { /* コマンドオペレーション中に電話帳オペレーションを行い。結果電話発呼の場合 */
				TelOperation(OPR_TELBOOK_TEL, NO_EFFECT);
			}
			break;
#endif

#if (PRO_KEYPANEL == PANEL_ANZU_L) /* デバッグモード、アイドルカウンタ表示用 1997/11/13 Y.Matsukuma */
		case LEFT_ARROW:	/* 左矢印キー				*/
			if ( SYB_MaintenanceSwitch[MNT_SW_I4] & 0x80 ){
				if (IsIdleDisplay == 0) {
					IsIdleDisplay = 1;
				}
				else {
					IsIdleDisplay = 0;
				}
			}
			else {
				NackBuzzer();
			}
			break;
#endif

		case SINGLE:		/* 単一オペレーションキー	*/
			SingleKeyOperation(key);
			break;

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/05/15 Y.Matsukuma */
		case CLEAR:
			ClearMinoltaTestPrintArea();
			break;
#endif

		case NO_EFFECT:
			/* このなかにはメモリーオーバーオペレーション、電話状態変化のメッセージも含まれる
			** 処理はループの最後でまとめてやる
			** ステータスがセットされてからメッセージが送信されるので問題は無いはず
			*/
			break;

		case ERROR_OPERATION:	/* 現在の状態では無効なキー */
			NackBuzzer();
			break;

		default:			/* その他のキーの処理		*/
			NackBuzzer();
			break;
		}

#if (PRO_PC_PRINT == ENABLE)	/* 追加 by M.Kuwahara 1998/02/20 */
		if ( keytype != KEY_TIME_UP ) {
			SYS_MachineStatus[SYS_ERROR_STATUS] &= ~SYS_ERROR_PC_MEMORY_OVER;
			SYS_PcMemoryOverDispRequest = 0;	/* PCメモリオーバ表示消去の為 */
		}
#endif
		if (CheckChildErrorDisplayReq() == TRUE) { /* エラー等のチャイルド表示要求があれば*/
			DisplayChildError();  /* チャイルド表示実行 */
		}

		/* これ以下に追加する異常処理は、必ず TelOperation()の最後にも同様に追加すること
		** （電話中にポーリング蓄積等の処理がされた場合 TelOperation()の中しか走っていないため）
		*/

		/** メモリーオーバー処理 */
		if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MEMORY_OVER_OPR) {
			MemoryOverOperation();
		}

		/** ジャムリカバー処理 */
		if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_JAM_RECOVER_OPR) {
			JamRecoverOperation(SCN_ADF);
		}

		/** ＦＢＳ読み取り中断リカバー処理 */
		if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FBS_RECOVER_OPR) {
			JamRecoverOperation(SCN_FBS);
		}

#if (PRO_FBS == ENABLE)
		/** 次原稿蓄積確認処理 */
		if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_NEXT_SCAN_START_OPR) {
			NextDocStoreOperation();
		}
#endif

#if (PRO_CIPHER == ENABLE)
		/* 復号化時キー間違い処理 */
		if (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_WRONG_KEY_ERROR) {
			DifferentKeyOperation();
		}
#endif

		/** 電話使用中の場合 */
		if (CheckTelephoneUsing()) {
			TelOperation(OPR_TEL_OPERATION, NO_EFFECT);
		}

		/** オペレーション終了処理 */
		OperationEnd();
	}
}

/*************************************************************************
	module		:[オペレーション開始セット]
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
	date		:[1995/10/13]
	author		:[江口]
*************************************************************************/
void OperationStart(void)
{
	/** オペレーション中のステータスをセット */
	SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_OPERATE;
	SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY;
}

/*************************************************************************
	module		:[オペレーション終了セット]
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
	date		:[1995/10/13]
	author		:[江口]
*************************************************************************/
void OperationEnd(void)
{
	/** オペレーション中のステータスをクリア */
	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_OPERATE;
	SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PANEL_BUSY;

	/** メインにオペレーション終了のメッセージを送信 */
	OperationMessageToMain.Message = MSG_DISPLAY_IDLE;
	snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
	MainTaskExecWait();
}

/*************************************************************************
	module		:[フックキーオペレーション]
	function	:[
		1.待機状態においてフックキーを押された時の処理を行う
		2.通信中であれば、会話予約のセット／リセットを行う
		3.通信中でなければ、フックキーフラグのセット

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
void HookKeyOperation(void)
{
	/*---------------------------------------------------*/
	/* 通信中であれば会話予約のセット・リセットをおこなう*/
	/* 通信中でなければ電話オペレーションに移行			 */
	/* 1995/03/13 Eguchi								 */
	/*---------------------------------------------------*/
	if (CheckFaxComExecute() == TRUE) {	/** 通信中　*/
		if (CMN_ChangeVoiceSwitch() == FALSE) {/**会話予約のセット・リセット*/
			NackBuzzer();
		}
		if (SYS_VoiceSwitch) {
			HookLedOn();
		}
		else {
			HookLedOff();
		}
	}
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* (ICHOUより）S.Fukui June 6,1998 */
	else if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_LINE_BUSY)
 	 &&	(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_FAXMODEM)) {	/* Class1で回線使用中 */
		NackBuzzer();
	}
	/* Class1ダイヤルイン対応  */
	else if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_LINE_BUSY)
	 &&	(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_DIAL_IN)
	 &&	(SYS_CL1_Status & CL1_DIALIN_CALLED)) {		/* Class1でダイヤルイン呼び出し中 */
		NackBuzzer();
	}
	/* Class1 F網対応  */
	else if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRE_LINE_BUSY)
	 &&	(SYS_CL1_Status & CL1_FNET_CALLED)) {		/* Class1でF網呼び出し中 */
		NackBuzzer();
	}
#endif
	else {	/*待機状態からフックキー押された*/
		HookKeySet();
	}
}

/*************************************************************************
	module		:[ＳＴＯＰキーが押されたときの処理]
	function	:[
		1.ＳＴＯＰキーが押されたときの処理
		2.停止する優先順位
		,	1:エラー表示（コールエラーは除く)
		,	2:スキャナ
		,		・スキャナ送信中止
		,		・原稿蓄積中止
		,		・原稿排出処理
		,	3:プリント
		,		・マルチコピー
		,		・代行受信以外のイメージプリント停止（代行受信プリントは止めれない)
		，		・リプリントしないリストプリント:チェックメッセージは止めない.
	]
	common		:[
		SYS_MachineStatus:
		FaxComPerformingFlag:
		OperationMessageToMain:
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/26]
	author		:[江口,渡辺一章]
*************************************************************************/
void StopKeyOperation(void)
{
	UBYTE	lst_kind;
	UBYTE	stop_enable;
#if (PRO_MULTI_LINE == ENABLE)
	UBYTE	line_number;
#endif

	/********************************************/
 	/* 優先順位１：エラー解除		  			*/
	/*			   1:メモリーオーバーエラー解除 */
	/*			   2:通信エラー解除				*/
	/*			   3:枚数エラー解除				*/
	/*			   上記以外のエラーは停止キーで */
	/*			   解除できない					*/
	/********************************************/
#if defined(GBR)
	/* 受信完了アラーム鳴動終了 */
	if (SYS_AudibleAlarmStatus & 0x02) { /** 受信完了アラーム鳴動中 */
		SYS_AudibleAlarmStatus &= ~0x01; /** 受信完了アラーム鳴動要求クリア */
		return;
	}
#endif

	/* メモリーオーバー */
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MEMORY_OVER) {
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_MEMORY_OVER;
		return;
	}

	/* 通信エラー */
	if ((SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_FAXCOM) && (!CHK_ReadyModeCopy())) {
		SYS_MachineStatus[SYS_ERROR_STATUS] &= ~SYS_ERROR_FAXCOM;
		return;
	}

	/* 原稿蓄積枚数と設定枚数が不一致 */
	if ((SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_PAGE_ERROR) && (!CHK_ReadyModeCopy())) {
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_PAGE_ERROR;
		return;
	}

#if (PRO_CLASS1 == ENABLE) /* 1996/09/13 Eguchi */
	/* クラス１自動初期設定エラー */
	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_CLASS1_INIT) {
		SYS_MachineStatus[SYS_ERROR_STATUS] &= ~SYS_ERROR_CLASS1_INIT;
		return;
	}
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/28 by Y.Tanimoto */
	/* InternetFAX設置オペレーションエラー */
	if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_INF_INIT) {
		SYS_MachineStatus[SYS_ERROR_STATUS] &= ~SYS_ERROR_INF_INIT;
		return;
	}
#endif

#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1998/06/12 */
	/* スクランブル原稿長エラー */
	if ((SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_SCRAMBLE_LENGTH_ERROR) && (!CHK_ReadyModeCopy())) {
		SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_SCRAMBLE_LENGTH_ERROR;
		return;
	}
#endif

	/****************************************/
	/* 優先順位２：スキャナ使用中の動作停止 */
	/* 			   1:スキャナーコピー停止	*/
	/*			   2:スキャナー送信停止	    */
	/*			   3:原稿蓄積停止			*/
	/*			   4:原稿排出				*/
	/****************************************/
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_SCANNER_COPY) {	/** スキャナコピー中 */
		SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_SCANNER_COPY;	/** シングルコピー中止 */
		return;
	}

#if (PRO_MULTI_LINE == ENABLE)
	line_number = OPT_CHK_ScannerTxExecute();
	if (line_number != 0xFF) {
		if (line_number == 0) {
			SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_FAXCOM;	/** 通信停止 */
		}
		else {
			SYS_OptionLineStop(line_number);
		}
		return;
	}
#else
	if (FaxComPerformingFlag) {	/** 通信中 */
		if (SYS_FaxComTxType == SYS_SCANNER_TX) {	/** スキャナ送信実行中 */
			SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_FAXCOM;	/** 通信停止 */
			return;
		}
	}
#endif

#if (PRO_FBS == ENABLE)
	/* マルチコピーＦＣＯＴ中の停止処理 ICHOUよりコピー By M.Tachibana 1997/05/20*/
	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) &&
		(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_MULTI_COPY) &&
		(SYB_MultiCopyFile[SYB_MultiCopyReadPoint].Status != SYS_MCOPY_EMPTY) &&
		(SYB_MultiCopyFile[SYB_MultiCopyReadPoint].ScanType == SYS_FBS_SCAN) &&
		(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY) &&
		(SYB_MultiCopyReadPoint == SYB_MultiCopyWritePoint)) {
		SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_DOC_STORE;
		SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_IMAGE_PRINT;
		return;
	}
#endif

	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {	/** 蓄積中 */
		SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_DOC_STORE;	/** 原稿蓄積中止 */
		return;
	}

#if (PRO_FBS == ENABLE) /* T.Nose 1997/03/26 */
	if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_IN)				/** 原稿繰り込み中でない */
	 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)				/** 原稿排出中でない */
	 && !(SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FEED_ERROR)	/** 原稿繰り込み不良でない */
	 && !(SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MIRROR_BUSY)	/** ミラーキャリッジ移動中でない */
	 && !(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN)		/** スキャナカバーが開いていない */
	 && !(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_BOOK_OPEN)) {		/** ブックカバーが開いていない */
		if ((DS2()) || (DS1() && (SYB_MaintenanceSwitch[MNT_SW_C3] & FEED_OUT_TEST))) {
			if (CMN_CheckFeederCommandEmpty() == TRUE) {	/** フィーダー送信コマンドが無い */
				/** 原稿排出処理 */
				OperationMessageToMain.Message = MSG_FEED_OUT_DOC;
				snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
				MainTaskExecWait();
				return;
			}
		}
	}
#else
	if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_IN)				/** 原稿繰り込み中でない */
	 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)				/** 原稿排出中でない */
	 && !(SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FEED_ERROR)	/** 原稿繰り込み不良でない */
 #if (PRO_UPPER_COVER == ENABLE) /* トップカバーの条件追加 1998/01/19  By T.Yamaguchi */
	 && !(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_BOOK_OPEN)		/** ブックカバーが開いていない */
 #endif
	 && !(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN)) {	/** スキャナカバーが開いていない */
 /* T.Nose 1998/02/15 */
 #if (PRO_DOC_IN == ENABLE) /* ANZU_L */
		if (CMN_CheckDocumentOnFeeder() == TRUE)
 #else /* POPLAR_L */
		if ((DS2()) || (DS1() && (SYB_MaintenanceSwitch[MNT_SW_C3] & FEED_OUT_TEST)))
 #endif
		{	/** フィーダに原稿がある */
			if (CMN_CheckFeederCommandEmpty() == TRUE) {	/** フィーダー送信コマンドが無い */
				/** 原稿排出処理 */
				OperationMessageToMain.Message = MSG_FEED_OUT_DOC;
				snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
				MainTaskExecWait();
				return;
			}
		}
	}
#endif

	/************************************************/
	/* 優先順位３：プリント動作停止		  			*/
	/*			   1:マルチコピープリント 			*/
	/*			   2:手差しコピープリント 			*/
	/*			   3:代行受信以外のイメージプリント */
	/*			   4:リカバーしないリストプリント	*/
	/************************************************/
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_MULTI_COPY) {
		if (SYS_DocumentPrintItem == SYS_MEM_MULTI_COPY_FILE) {	/* マルチコピー原稿 */
			SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_IMAGE_PRINT;	/** マルチコピープリント中止 */
			return;
		}
	}

	if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_MANUAL_COPY) {
		if (SYS_DocumentPrintItem == SYS_MEM_MANUAL_COPY_FILE) {	/* 手差しコピー原稿 */
			SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_IMAGE_PRINT;	/** 手差しコピープリント中止 */
			return;
		}
	}

	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) {
		/* 原稿付きチェックメッセージの停止をオペレーションでガードするかしないか */
		stop_enable = FALSE;
		switch (SYS_DocumentPrintClass) {
		case SYS_PRINT_CLASS_LIST_MEMORY:		/* 原稿付きチェックメッセージの場合 */
		case SYS_PRINT_CLASS_LIST_MONITOR:		/* モニターレポートの場合 */
		case SYS_PRINT_CLASS_LIST_BA_MEMORY:	/* 一括送信原稿チェックメッセージの場合（原稿付き） */
		case SYS_PRINT_CLASS_LIST_BA_MONITOR:	/* 一括送信モニターレポート */
			if (CHK_StopMemCheckMsg()) {	/* 原稿付きチェックメッセージをストップでとめていい */
				stop_enable = TRUE;
			}
			break;
#if (PRO_CIPHER == ENABLE)	/* Add By T.Fukumoto 98/01/29 */
		case SYS_PRINT_CLASS_LIST_CIPHER:		/* 暗号化受信原稿通知(原稿付き)は、スットプキーを無効にします */
			break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/27 */
		case SYS_PRINT_CLASS_RETURNED_MAIL:		/** ｲﾝﾀｰﾈｯﾄFAXの不達通知の印字。ストップキーでは止まりません　*/
			break;
#endif
		default:
			switch (SYS_DocumentPrintItem) {
			case SYS_MEM_RX_FILE:			/* メモリ受信原稿 */
			case SYS_MEM_SECURE_RX_FILE:	/* 親展受信原稿 */
/* #if (PRO_CLASS1 == DISABLE) */
#if (PRO_CLASS1 == ENABLE)	/* ローカルプリントはＦＡＸ側での中断はせず、ＰＣからの中断のみとします。 By S.Fukui May 15,1998 */
			case SYS_MEM_CL1_RX_FILE:		/* クラス１ ローカルプリント用原稿 */
#endif
#if (PRO_PC_PRINT == ENABLE)	/* ＰＣプリントの原稿は、ストップキーを無効にします by K.Watanabe 1997/11/13 */
			case SYS_MEM_PC_RX_FILE:		/* ＰＣプリントファイル */

	#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* ﾐﾉﾙﾀ8ppmﾃｽﾄ 1998/05/14 Y.Murata */
				if (SYS_MinoltaTestFuncData[SYS_DocumentPrintNo].Status == SYS_FUNC_TEST_DATA_PRINT) {
					stop_enable = TRUE;
				}
	#endif

#endif
				break;
			default:
				stop_enable = TRUE;
				break;
			}
			break;
		}

		if (stop_enable) {
			SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_IMAGE_PRINT;	/** 原稿印字中止 */
			return;
		}
	}

	/* 停止しても再プリントするものに関しては停止できないように変更する */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_LIST_PRINT) {
		if (SYS_DocumentPrintItem < LST_STOP_ENABLE_LINE) {	/* ストップキーにて停止可能な時 */
			SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_LIST_PRINT;	/** リストプリント中止 */
			return;
		}
	}

#if (PRO_CIPHER == ENABLE)/* By Y.Suzuki 1997/12/08 */
	/*スキャナ送信予約があるときにスクランブル停止できなっかったのでここに移動した。*/
	/*By Y.Suzuki 1998/06/26*/
	/* 暗号化・復号化中の停止 */
	if (((SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_SCRAMBLE_EXEC)
	  || (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_EXEC))
	 && (!CHK_ReadyModeCopy())) {
		ConfirmStopCipherExecuting();
		return;
	}

	/* 暗号化エラーの解除 */
	if ((SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_SCRAMBLE_ERROR) && (!CHK_ReadyModeCopy())) {
		SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_SCRAMBLE_ERROR;
		return;
	}

	/* 復号化エラーの解除 */
	if ((SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_ERROR) && (!CHK_ReadyModeCopy())) {
		SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DESCRAMBLE_ERROR;
		return;
	}
	/* 暗号化メモリーオーバーエラーの解除 By Y.Suzuki 1998/04/18*/
	if ((SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_SCRAMBLE_MEM_OVER) && (!CHK_ReadyModeCopy())) {
		SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_SCRAMBLE_MEM_OVER;
		return;
	}

	/* 復号化メモリーオーバーエラーの解除 By Y.Suzuki 1998/04/18*/
	if ((SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_MEM_OVER) && (!CHK_ReadyModeCopy())) {
		SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DESCRAMBLE_MEM_OVER;
		return;
	}
#endif

	if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_IN)					/** 原稿繰り込み中でない */
	 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)					/** 原稿排出中でない */
	 && !(SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FEED_ERROR)) {	/** 原稿繰り込み不良でない */
		if (CMN_CheckDocumentOnFeeder() == TRUE) {	/* フィーダに原稿がある */
			if (CMN_CheckFeederCommandEmpty() == FALSE) {	/* フィーダー送信コマンドがある */
				NackBuzzer();
				return;
			}
		}
	}

#if (PRO_COPY_FAX_MODE == ENABLE)
	/* コピーモードで、手差しが選択されている時は、用紙をカセットに戻します */
	if ((CHK_ReadyModeCopy()) && (OPR_CopyData.Cassette == SYS_MANUAL_CASSETTE)) {
		OPR_CopyData.Cassette = ClearCopyCassette();	/* カセット段数の初期化 */

		/* ＡＤＦに原稿がセットされている時は、原稿サイズ・記録紙サイズに
		** 合わせた倍率を表示する必要があるので、倍率も変更します
		*/
		if (CMN_CheckDocumentOnFeeder() == TRUE) {	/* ADFに原稿がｾｯﾄされている時 */
			OPR_CopyData.Reduction = ClearCopyMagnifi();
		}
		SYS_ManualPaperSize = SYS_NO_PAPER;	/* 手差し記録紙サイズに記録紙なしをセットします */
		OPR_CopyData.OHPMode = FALSE;		/* ＯＨＰモードをオフ（記録紙）にします */

		/* 原稿表示をしていたら濃度表示に戻します by K.Watanabe 1997/12/19 */
		IsMagnifiKeyInput = FALSE;	/* 拡大・縮小キー押下チェック用変数ＯＦＦ */
		return;
	}
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/05/28 Eguchi */
	/*FOR DEBUG*/
	if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_DIALUP_INTERNET_FAX) {
		INF_DEBUG_IsStopReceive = TRUE;
		return;
	}
#endif


	NackBuzzer();
}

/*************************************************************************
	module		:[暗号化・復号化実行中止確認処理]
	function	:[
		1.暗号化・復号化処理を中止するかを確認します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/05/25]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_CIPHER == ENABLE)
void ConfirmStopCipherExecuting(void)
{
	UBYTE	*wording_ptr;	/* ワーディングポインター	*/
	UBYTE	is_loop_end;	/* ループ終了判断用			*/

	if (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_SCRAMBLE_EXEC) {	/* スクランブル中の時 */
		wording_ptr = D2W_StopCipherExecute;	/* "ｽｸﾗﾝﾌﾞﾙ ﾁｭｳｼ        " */
	}
	else {															/* スクランブル解除中の時 */
		wording_ptr = D2W_StopDecipherExecute;	/* "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ﾁｭｳｼ  " */
	}

	/* 注）本当は以下の処理は、ConfirmKeyInputOperation()を使用すれば良いのだが、スクランブル中は
	** 　　点滅表示を使用できない（等間隔で点滅しない）ので、あえて関数を使用しません
	*/

	DisplayStringHigh(0, wording_ptr);
	DisplayStringLow(0, D2W_EnterClesr);	/* "            ｾｯﾄ/ｸﾘｱ " */

	is_loop_end = FALSE;
	while (is_loop_end != TRUE) {
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);

		switch (GetInputKeyType()) {
		case ENTER:			/* セットキー	*/
			CipherStopOn = 1;	/* スクランブル・デスクランブルを中止します */
			is_loop_end = TRUE;
			break;
		case CLEAR:			/* クリアキー	*/
		case STOP:			/* ストップキー	*/
		case KEY_TIME_UP:	/* タイムアップ	*/
			is_loop_end = TRUE;
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}
#endif	/* (PRO_CIPHER == ENABLE) */

/*************************************************************************
	module		:[メモリオーバー、オペレーション]
	function	:[
		1.原稿蓄積中にメモリーオーバーが生じた時の処理を行う
		2.メモリ送信時、メモリ蓄積分のみ送信するか、それともキャンセルするかオペレータに促す
		3.ポーリング等の蓄積時、メモリ蓄積分のみ蓄積するか、それともキャンセルするかオペレータに促す
		4.コピー時、メモリ蓄積分のみコピーするか、それともキャンセルするかオペレータに促す
	]
	return		:[なし]
	common		:[
		OperationMessageToMain	:
		SYS_DocumentStoreItem	:
	]
	condition	:[]
	comment		:[Ｈ８から移植]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/26]
	author		:[江口,渡辺一章]
*************************************************************************/
void MemoryOverOperation(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	restart_key;	/* 実行内容継続キー */
	UBYTE	is_loop_end;	/* ループ終了で使用 */

	is_loop_end = FALSE;

	/* 上段の表示 */
	DisplayStringHigh(0, D2W_MemoryOverFlow);				/* "ﾒﾓﾘ ｵｰﾊﾞｰ ﾃﾞｽ       " */

	/* 下段の表示（蓄積の種類によりワーディングを変えます） */
	switch (SYS_DocumentStoreItem) {
	case SYS_MEM_TX_FILE:			/* メモリー送信原稿							*/
	case SYS_MEM_BATCH_TX_FILE1:	/* 一括送信原稿：ボックス１					*/
	case SYS_MEM_BATCH_TX_FILE2:	/* 一括送信原稿：ボックス２					*/
	case SYS_MEM_BATCH_TX_FILE3:	/* 一括送信原稿：ボックス３					*/
	case SYS_MEM_BATCH_TX_FILE4:	/* 一括送信原稿：ボックス４					*/
	case SYS_MEM_BATCH_TX_FILE5:	/* 一括送信原稿：ボックス５					*/
	case SYS_MEM_CLASS1_TX_FILE:	/* ローカルスキャン用送信原稿				*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/25 by K.Okada */
	case SYS_MEM_MAIL_TX_FILE:		/* メール送信原稿							*/
#endif
		FlashDisplayStringLow(D2W_MemoryOverStartClear);	/* "ﾒﾓﾘ ﾌﾞﾝﾉﾐ  ｽﾀｰﾄ/ｸﾘｱ " */
		restart_key = START;
		break;
	case SYS_MEM_POLLING_FILE:		/* ポーリング原稿							*/
	case SYS_MEM_DB_POLLING_FILE:	/* 検索ポーリング原稿						*/
#if (PRO_F_CODE == ENABLE)
	case SYS_MEM_SUB_BULLETIN_FILE:	/* サブアドレス通信原稿（掲示板蓄積原稿）	*/
#endif
		FlashDisplayStringLow(D2W_MemoryOverEnterClear);	/* "ﾒﾓﾘ ﾌﾞﾝﾉﾐ   ｾｯﾄ/ｸﾘｱ " */
		restart_key = ENTER;
		break;
	case SYS_MEM_MULTI_COPY_FILE:	/* マルチコピー原稿							*/
	case SYS_MEM_MANUAL_COPY_FILE:	/* 手差しコピー原稿							*/
#if (PRO_COPY_FAX_MODE == ENABLE)
		/* ポプラＢにはコピーキーが無いのでコピー時のメモリオーバーでもスタートキーを使用します */
		FlashDisplayStringLow(D2W_MemoryOverStartClear);	/* "ﾒﾓﾘ ﾌﾞﾝﾉﾐ  ｽﾀｰﾄ/ｸﾘｱ " */
		restart_key = START;
#else
		FlashDisplayStringLow(D2W_MemoryOverCopyClear);		/* "ﾒﾓﾘ ﾌﾞﾝﾉﾐ  ｺﾋﾟｰ/ｸﾘｱ " */
		restart_key = COPY;
#endif
		break;
	default:
		return;
	}

	while (is_loop_end != TRUE) {
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);	/* キー待ち１分 */
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case START:
		case ENTER:
		case COPY:
			if (restart_key == keytype) {	/* 読み取り開始したキーと同じキーの時 */
				is_loop_end = TRUE;
				OperationMessageToMain.Message = MSG_MEMORY_OVER_ENTER;
			}
			else {							/* 読み取り開始したキーと違うキーの時 */
				NackBuzzer();
			}
			break;
		case STOP:
		case CLEAR:
			is_loop_end = TRUE;
			OperationMessageToMain.Message = MSG_MEMORY_OVER_CANCEL;
			break;
		case KEY_TIME_UP:
			is_loop_end = TRUE;
			OperationMessageToMain.Message = MSG_MEMORY_OVER_TIME_UP;
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

	snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
	MainTaskExecWait();
}

/*************************************************************************
	module		:[ジャムリカバー　オペレーション]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/15]
	author		:[渡辺一章]
*************************************************************************/
void JamRecoverOperation(UBYTE jam_position)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	restart_key;	/* 実行内容継続キー */
	UBYTE	is_loop_end;	/* ループ終了で使用 */

	is_loop_end = FALSE;
	CMN_MemorySetNULL(DisplayBufferHigh , OPR_DISPLAY_MAX , ' ');

	/* 上段表示用ワーディングのセット */
	if (jam_position == SCN_ADF) {	/* ＡＤＦ読み取り中のジャムの時 */
		CMN_StringCopy(DisplayBufferHigh, D2W_DocumentJam);			/* "ｹﾞﾝｺｳｶﾞ ﾂﾏﾘﾏｼﾀ      " */
	}
	else {							/* ＦＢＳ読み取り中にプリンターカバーが開閉された時 */
		CMN_StringCopy(DisplayBufferHigh, D2W_InterruptDocScan);	/* "ﾖﾐﾄﾘｶﾞ ﾁｭｳﾀﾞﾝ ｻﾚﾏｼﾀ " */
	}

	/* ジャムリカバーを行うかどうかの確認 */
	switch (ConfirmKeyInputOperation(DisplayBufferHigh, D2W_NextScanEnterClear, ENTER, CLEAR)) {
																	/* "ﾂﾂﾞｷﾉ ﾖﾐﾄﾘ  ｾｯﾄ/ｸﾘｱ " */
	case CONFIRM_EXEC:	/* 実行 */
		/* 上段表示ワーディングの作成 */
		if (jam_position == SCN_ADF) {	/* ＡＤＦ読み取り中のジャムの時 */
			CMN_StringCopy(&DisplayBufferHigh[0], D2W_ResetPageNumber);					/* "  ﾍﾟｰｼﾞｶﾗ ｾｯﾄｼﾅｵｼﾃ  " */
			/* ジャムしたページを表示用バッファにセットします */
#if defined(JPN)	/* ページ表示位置が国で違うので注意 By S.Fukui Oct.6,1997 */
			if (SYB_WordingNumber == 1) {	/* 日本語だけこのパスを通る */
				CMN_UnsignedIntToASC(&DisplayBufferHigh[0], SYS_DocumentStorePage, 2, ' ');	/* "99ﾍﾟｰｼﾞｶﾗ ｾｯﾄｼﾅｵｼﾃ  " */
			}
			else {							/* 日本仕様でも日本語以外の対応 */
				CMN_UnsignedIntToASC(&DisplayBufferHigh[1], SYS_DocumentStorePage, 2, ' ');	/* "p99. Reset Document " */
			}
#else
			CMN_UnsignedIntToASC(&DisplayBufferHigh[1], SYS_DocumentStorePage, 2, ' ');	/* "p99. Reset Document " */
#endif
		}
		else {							/* ＦＢＳ読み取り中にプリンターカバーが開閉された時 */
			CMN_StringCopy(&DisplayBufferHigh[0], D2W_ResetDocumentSet);				/* "ｹﾞﾝｺｳﾉ ｾｯﾄｦ ﾔﾘﾅｵｼﾃ  " */
		}

		/* 下段表示ワーディングの作成（蓄積の種類によりワーディングを変えます） */
		switch (SYS_DocumentStoreItem) {
		case SYS_MEM_TX_FILE:			/* メモリー送信原稿							*/
		case SYS_MEM_BATCH_TX_FILE1:	/* 一括送信原稿：ボックス１					*/
		case SYS_MEM_BATCH_TX_FILE2:	/* 一括送信原稿：ボックス２					*/
		case SYS_MEM_BATCH_TX_FILE3:	/* 一括送信原稿：ボックス３					*/
		case SYS_MEM_BATCH_TX_FILE4:	/* 一括送信原稿：ボックス４					*/
		case SYS_MEM_BATCH_TX_FILE5:	/* 一括送信原稿：ボックス５					*/
		case SYS_MEM_CLASS1_TX_FILE:	/* ローカルスキャン用送信原稿				*/
#if (PRO_CIPHER == ENABLE)
		case SYS_MEM_CIPHER_FILE:		/* 暗号化前原稿								*/
#endif
			CMN_StringCopy(DisplayBufferLow, D2W_PleasePressStartKey);	/* "ｽﾀｰﾄｷｰ ｦ ｵｼﾃｸﾀﾞｻｲ   " */
			restart_key = START;
			break;
		case SYS_MEM_POLLING_FILE:		/* ポーリング原稿							*/
		case SYS_MEM_DB_POLLING_FILE:	/* 検索ポーリング原稿						*/
#if (PRO_F_CODE == ENABLE)
		case SYS_MEM_SUB_BULLETIN_FILE:	/* サブアドレス通信原稿（掲示板蓄積原稿）	*/
#endif
			CMN_StringCopy(DisplayBufferLow, D2W_PleasePressEnterKey);	/* "ｾｯﾄｷｰ ｦ ｵｼﾃｸﾀﾞｻｲ    " */
			restart_key = ENTER;
			break;
		case SYS_MEM_MULTI_COPY_FILE:	/* マルチコピー原稿							*/
		case SYS_MEM_MANUAL_COPY_FILE:	/* 手差しコピー原稿							*/
#if (PRO_COPY_FAX_MODE == ENABLE)
			/* ポプラＢにはコピーキーが無いのでコピー時のメモリオーバーでもスタートキーを使用します */
			CMN_StringCopy(DisplayBufferLow, D2W_PleasePressStartKey);	/* "ｽﾀｰﾄｷｰ ｦ ｵｼﾃｸﾀﾞｻｲ   " */
			restart_key = START;
#else
			CMN_StringCopy(DisplayBufferLow, D2W_PleasePressCopyKey);	/* "ｺﾋﾟｰｷｰ ｦ ｵｼﾃｸﾀﾞｻｲ   " */
			restart_key = COPY;
#endif
			break;
		default:
			CMN_StringCopy(DisplayBufferLow, D2W_PleasePressStartKey);	/* "ｽﾀｰﾄｷｰ ｦ ｵｼﾃｸﾀﾞｻｲ   " */
			restart_key = START;
			break;
		}

		key = OPR_NO_KEY;	/* 前回キー入力値用に初期化します */

		/* 読み取りを再開するためのキー入力を行います */
		while (is_loop_end != TRUE) {
			if (CheckChildDisplay() == FALSE) {	/** チャイルド未表示の時 */
				/* 上下段の表示 */
				DisplayStringHigh(0, DisplayBufferHigh);
				DisplayStringLow(0, DisplayBufferLow);
			}

			OPR_GetKey(KEY_WAIT_ONE_MINUTE);	/* キー待ち１分 */
			key = GetInputKeyCode();
			keytype = GetInputKeyType();

			switch (keytype) {
			case START:			/* スタートキー				*/
			case ENTER:			/* セットキー				*/
			case COPY:			/* コピーキー				*/
				if (restart_key == keytype) {	/* 読み取り開始したキーと同じキーの時 */
					/* ＡＤＦの時：エラーが解除されている・原稿がセットされている・スキャナーカバーが閉じている時、
					** 　　　　　　読み取りを再開します
					** ＦＢＳの時：プリンターカバーが閉じている時、読み取りを再開します
					*/
					if (((jam_position == SCN_ADF)
					  && !(SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FEED_ERROR)
					  && (CMN_CheckScanDocOnFeeder() == TRUE)
					  && (CMN_CheckScannerCoverClose() == TRUE))
					 || ((jam_position == SCN_FBS)
					  && (!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN)
					   && !(SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_MOMENT_TOP_COVER_OPEN)))) { /* by K.Watanabe 1998/03/05 */
						/* 読み取りを再開し、読み取り終了後、処理を行います */
						OperationMessageToMain.Message = MSG_SCAN_CONT_START;	/* 読み取り開始メッセージ通知 */
						is_loop_end = TRUE;
					}
					else {
						NackBuzzer();
					}
				}
				else {							/* 読み取り開始したキーと違うキーの時 */
					NackBuzzer();
				}
				break;
			case STOP:			/* ストップキー				*/
				/* 読み取った原稿を破棄し、処理を中止します */
				OperationMessageToMain.Message = MSG_SCAN_CONT_ABORT;		/* 読み取り中止メッセージ通知 */
				is_loop_end = TRUE;
				break;
			case KEY_TIME_UP:	/* キー待ちタイムオーバー	*/
				OperationMessageToMain.Message = MSG_SCAN_CONT_END;			/* 読み取り終了メッセージ通知 */
				is_loop_end = TRUE;
				break;
			case SINGLE:
				SingleKeyOperation(key);
				break;
			case NO_EFFECT:
				break;
			default:
				NackBuzzer();
				break;
			}
		}
		break;
	case CONFIRM_ABORT:	/* 取り消し */
	case OPR_END:		/* 中止・タイムアップ */
		/* 読み取った原稿を破棄し、処理を中止します */
		OperationMessageToMain.Message = MSG_SCAN_CONT_ABORT;	/* 読み取り中止メッセージ通知 */
		break;
	default:
		break;
	}

	/* メインに選択された処理のメッセージを送ります */
	snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
	MainTaskExecWait();
}

/*************************************************************************
	module		:[次原稿蓄積確認オペレーション]
	function	:[
		1.次原稿読み取り開始／送信開始・読み取り終了の確認を行います
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/09/11]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_FBS == ENABLE)
void NextDocStoreOperation(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	last_key;		/* 前回キー入力値 */
	UBYTE	restart_key;	/* 実行内容継続キー */
	UBYTE	is_loop_end;	/* ループ終了で使用 */

	if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
		return;
	}

	key = OPR_NO_KEY;	/* 前回キー入力値用に初期化します */
	is_loop_end = FALSE;

	/* 上段表示ワーディングのセット */
	CMN_StringCopy(DisplayBufferHigh, D2W_NextBookDocScanStart);	/* "ﾖﾐﾄﾘ ｶｲｼ → ｼﾞｹﾞﾝｺｳｷｰ" */

	/* 下段表示ワーディングのセット */
	switch (SYS_DocumentStoreItem) {	/* 原稿の種別を解析 */
	case SYS_MEM_TX_FILE:			/* メモリー送信原稿			*/
#if (PRO_CIPHER == ENABLE)
	case SYS_MEM_CIPHER_FILE:		/* 暗号化前原稿				*/
#endif
#if (PRO_CLASS1 == ENABLE)
	case SYS_MEM_CLASS1_TX_FILE:	/** FBSからのﾛｰｶﾙｽｷｬﾝ処理追加  By S.Fukui Jan.27,1998 */
#endif

		CMN_StringCopy(DisplayBufferLow, D2W_NextBookDocTxStart);	/* "ｿｳｼﾝ ｶｲｼ → ｽﾀｰﾄｷｰ   " */
		restart_key = START;
		break;
	case SYS_MEM_BATCH_TX_FILE1:	/* バッチ送信原稿			*/
	case SYS_MEM_BATCH_TX_FILE2:	/* バッチ送信原稿			*/
	case SYS_MEM_BATCH_TX_FILE3:	/* バッチ送信原稿			*/
	case SYS_MEM_BATCH_TX_FILE4:	/* バッチ送信原稿			*/
	case SYS_MEM_BATCH_TX_FILE5:	/* バッチ送信原稿			*/
	case SYS_MEM_POLLING_FILE:		/* ポーリング送信原稿		*/
	case SYS_MEM_DB_POLLING_FILE:	/* 検索ポーリング送信原稿	*/
#if (PRO_F_CODE == ENABLE)
	case SYS_MEM_SUB_BULLETIN_FILE:	/* 掲示板蓄積原稿			*/
#endif
		CMN_StringCopy(DisplayBufferLow, D2W_NextBookDocScanEnd);	/* "ﾖﾐﾄﾘ ｼｭｳﾘｮｳ → ｾｯﾄｷｰ " */
		restart_key = ENTER;
		break;
	default:
		CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');
		break;
	}

	while (is_loop_end != TRUE) {
		/* 上下段の表示 */
		if (CheckChildErrorDisplayReq() == TRUE) {	/* エラー等でチャイルド表示要求あり */
			ClearDisplayHigh();
			DisplayChildError();
		}
		else if (CheckChildDisplay() == FALSE) {
			DisplayStringHigh(0, DisplayBufferHigh);
			DisplayStringLow(0, DisplayBufferLow);
		}

		last_key = key;	/* 前回キー入力値の退避 */

		OPR_GetKey(KEY_WAIT_ONE_MINUTE);	/* キー待ち１分 */
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NEXT_DOC:		/* 次原稿キー				*/
			if (CheckScanStartEnable(OPR_DOC_SET_CHK_ONLY) == OPR_SCAN_ENABLE) {	/* 読み取りが可能な時 */
				/* メインに読み取り開始のメッセージを送ります */
				OperationMessageToMain.Message = MSG_SCAN_CONT_START;	/* 読み取り開始メッセージ通知 */
				is_loop_end = TRUE;
			}
			else {																	/* 読み取りが不可能な時 */
				NackBuzzer();
			}
			break;
		case START:			/* スタートキー				*/
		case ENTER:			/* セットキー				*/
			if (restart_key == keytype) {	/* 読み取り開始したキーと同じキーの時 */
				/* メインに読み取り終了のメッセージを送ります */
				OperationMessageToMain.Message = MSG_SCAN_CONT_END;		/* 読み取り終了メッセージ通知 */
				is_loop_end = TRUE;
			}
			else {
				NackBuzzer();
			}
			break;
		case STOP:			/* ストップキー				*/
			/* 読み取った原稿を破棄し、処理を中止します */
			OperationMessageToMain.Message = MSG_SCAN_CONT_ABORT;		/* 読み取り中止メッセージ通知 */
			is_loop_end = TRUE;
			break;
		case KEY_TIME_UP:	/* キー待ちタイムオーバー	*/
			/* メインに読み取り終了のメッセージを送ります */
			OperationMessageToMain.Message = MSG_SCAN_CONT_END;			/* 読み取り終了メッセージ通知 */
			is_loop_end = TRUE;
			break;
		case BOOK_DOC_SIZE:	/* ブック原稿サイズキー		*/
			BookDocumentSizeSet(OPR_MAIN_OPE, last_key);
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

	/* メインに選択された処理のメッセージを送ります */
	snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
	MainTaskExecWait();
}
#endif	/* (PRO_FBS == ENABLE) */

/*************************************************************************
	module		:[暗号化解除時キー間違いオペレーション]
	function	:[
		1.暗号化解除開始後、指定のキーが間違いと判断された時、解除を続けるか
		　どうかを確認します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/12]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_CIPHER == ENABLE)
void DifferentKeyOperation(void)
{
	UBYTE	is_decipher_cont;	/* 解除継続／中断判断用 */

	is_decipher_cont = FALSE;	/* 解除中断をセット */

	if (ConfirmKeyInputOperation(D2W_DecipherKeyError,			/* "ｷｰﾜｰﾄﾞ ｶﾞ ﾁｶﾞｲﾏｽ    " */
								 D2W_ConfirmDecipherContinue,	/* "ｶｲｼﾞｮ ｹｲｿﾞｸ ｾｯﾄ/ｸﾘｱ " */
								 ENTER,
								 CLEAR) == CONFIRM_EXEC) {	/* 解除継続の時 */
		is_decipher_cont = TRUE;	/* 解除継続をセット */
	}

	/* メインに暗号化解除の継続／中断のメッセージを送ります */
	OperationMessageToMain.Message = MSG_OPT_DECIPHER_FROM_OPR;
	OperationMessageToMain.SubMessage1 = is_decipher_cont;
	snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
	MainTaskExecWait();
}
#endif

/*************************************************************************
	module		:[操作エラー表示]
	function	:[
		1.OPR_ChildErrorFlagにセットされているエラータイプに相当するエラーメッセージを表示する
		2.OPR_ChildErrorFlagにセットされるエラータイプの番号とワーディングの登録順は必ず一致させること
		　でないと表示がずれる
		3.新たに追加する場合は最後に追加していくこと
	]
	return		:[]
	common		:[OPR_ChildErrorFlag]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/12/04]
	author		:[江口]
*************************************************************************/
void DisplayChildError(void)
{
	if (OPR_ChildErrorFlag != OPR_NO_ERROR) {	/* エラー表示要求あり */
		ChildDisplayStringLow(D2W_InvalidNumber + (((UBYTE)(OPR_ChildErrorFlag - 1)) * OPR_WORDING_LEN));
		OPR_ChildErrorFlag = OPR_NO_ERROR;	/* エラーフラグをクリアしておく */
	}
}

/*************************************************************************
	module		:[オペレーションプロテクト解除オペレーション]
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
	date		:[1996/02/06]
	author		:[江口]
*************************************************************************/
UBYTE OperationProtectReset(UBYTE keytype)
{
	UWORD	passcode;

	/* プロテクトの対象となるキー入力かどうか調べる */
	if (keytype == NO_EFFECT) {
		return (OK);
	}
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)	/* 97/12/05 Add By M.Kuwahara */
	if (keytype == STOP) {
		return (OK);
	}
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)	/* by K.Watanabe 1997/12/05 */
	/* ポプラＢでは、コピーパラメーター初期化用に、１分キー入力を使用しているため、タイムアップも無視します */
	if (keytype == KEY_TIME_UP) {
		return (OK);
	}
#endif

	/* プロテクトがかかっているか調べる */
	if (CHK_OperationProtect() == 0) { /*プロテクトＯＦＦ */
		return (OK);
	}

	/* プロテクトＯＮの状態では必ずパスコードあり */

	/* 上段表示 */
	DisplayStringHigh(0, D2W_OperationProtected);	/* "ｵﾍﾟﾚｰｼｮﾝ ﾌﾟﾛﾃｸﾄ     " */

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)	/* 97/12/05 Add By M.Kuwahara */
	/* パスコード入力 */
	if ((passcode = EnterPassCodeProtect(D2W_EnterProtectPasscode)) == 0xFFFF) {
		/* 入力途中でストップキー */
		return (NG);
	}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	/* パスコード入力 */
	if ((passcode = EnterPassCode(SYB_ProtectPasscode, CHK_PASS_CODE_ENTER, D2W_EnterProtectPasscode)) == 0xFFFF) {
		/* 入力途中でストップキー */
		return (NG);
	}
#endif

	/* パスコードチェック */
	if (passcode != SYB_ProtectPasscode) { /* パスコード不一致 */
		OPR_ChildErrorFlag = INVALID_PROTECT_PASSCODE_ERROR;	/* "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ｶﾞ ﾁｶﾞｲﾏｽ" */
		NackBuzzer();
		return (NG);
	}
	return (OK);
}
