/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_RSV.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 通信確認オペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\mem_def.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\sysbatch.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\sysexec.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if defined(STOCKHM2) /* DVT : add by SMuratec C.P 2004/09/08 */
#include	"\src\atlanta\ext_v\fcm_data.h"
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
/* define */
#include	"\src\atlanta\define\sys_infd.h"
/* ext_v */
#include	"\src\atlanta\ext_v\sys_inf.h"
#endif

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif

#if (PRO_MULTI_LINE == ENABLE)
#include	"\src\atlanta\define\mlt_pro.h"
#endif

#if (PRO_RELAYED_REPORT == ENABLE)	/* Add By H.Fujimura 1999/02/05 */
#include 	"\src\atlanta\define\mntsw_b.h"
#endif

#if (PRO_CIPHER == ENABLE)	/* Add By T.Fukumoto 98/01/29 */
#include	"\src\atlanta\scd\ext_v\cph_data.h"
#endif

#if (PRO_COMM_RESULT_REVIEW == ENABLE)
#include	"\src\atlanta\define\sysjrnl.h"
#include	"\src\atlanta\define\lst_def.h"
#endif

/* Prototype
void	ReviewCommandOperation(void);
UBYTE	SelectReviewOperationType(void);
UBYTE	ConfirmClearCommandOperation(void);
void	ClearReviewControlData(void);
UBYTE	SetCommandPointer(UBYTE);
UBYTE	CheckCommandReviewMode(void);
UBYTE	SearchExecQueue(UBYTE, UBYTE);
UBYTE	CheckExecQueueBeforeStart(UBYTE);
UBYTE	CheckExecuteExecQueue(UBYTE);
UBYTE	CheckExecKindNumber(UBYTE, UBYTE, UBYTE);
UBYTE	CheckExecuteCommand(UBYTE, UBYTE);
UBYTE	ClearReviewCommandData(void);
UBYTE	CheckCommandPrinting(UBYTE, UBYTE);
UBYTE	CheckAllClearExecQueue(UBYTE, UBYTE);
UBYTE	CheckAllClearCommandDial(UBYTE);
void	ClearAllExecQueueData(UBYTE, UBYTE);
void	ResetAllScannerParameter(void);
void	ClearCommandBatchFile(UBYTE, UBYTE);
UBYTE	CheckBroadCastCommand(void);
void	ResetExecPointer(void);
UBYTE	SetExecPointer(UBYTE);
void	ChangeCommandReviewMode(void);
UBYTE	CheckCommandBatchStatus(UBYTE, UBYTE);
void	DisplayReviewCommand(void);
UBYTE	SetCheckConfirmReport(void);
#if (PRO_MULTI_LINE == ENABLE)
UBYTE	MultiDisplaySelect(void);
void	MultiOverWriteDisplayData(UBYTE);
#endif
void	DisplaySpeedDialSet(UBYTE, UWORD);
UBYTE	SearchDialData(struct SYS_DialData_t *, UBYTE *, UBYTE *);
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) (コマンドファイルの参照位置のセット) Added by SMuratec L.Z.W 2003/10/24
UBYTE SetBackCommand(UBYTE);
#endif
*/

/*************************************************************************
	module		:[通信確認オペレーション]
	function	:[
		1.通信待ち確認消去オペレーションと通信証状況確認オペレーションの選択を行う
		2.通信確認キーで 下記オペレーション切替え
			・通信待ち確認消去オペレーション（最初の待ち通信表示）
			・通信証状況確認オペレーション  （初期設定値）
		3.機能キーで 
		    ・通信待ち確認消去の場合：次の通信待ち表示（順次）
			・通信状況確認    の場合：ＯＮ／ＯＦＦの選択
		4.ストップキー又はキー待ちタイムオーバーで終了
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/10/01]
	author		:[福井知史]
*************************************************************************/
void ReviewCommandOperation(void)
{
	UBYTE	type;		/* 0:予約確認 1:通信証セット */
	UBYTE	ret;

	type = 0;

	while (1) {
		switch (type) {
		case 0:
#if (PRO_KEYPANEL == PANEL_STOCKHM2) /* Mod by SMuratec C.P 2004/06/10 for V195通信結果と予約確認画面の表示*/
			ret = SelectReviewCommandOperation();
#else
			ret = ConfirmClearCommandOperation();
#endif	/* End of (PRO_KEYPANEL == PANEL_STOCKHM2) */
			break;
		case 1:
			ret = SetCheckConfirmReport();
			break;
 #if (PRO_MULTI_LINE == ENABLE)
		case 2:
			ret = MultiDisplaySelect();
			break;
 #endif
		default:	/* イレギュラーパス */
			ret = OPR_CANCELED;
			break;
		}
		
		switch (ret) {
		case OPR_CHANGED_MODE:		/* 通信確認キー押下時 */
 #if (PRO_MULTI_LINE == DISABLE)
			type ^= 0x01;
 #else
			/* ユニットスイッチｉ３の０ビット目が立ってて、しかも回線が２つ以上あれば有効 */
			if ((CHK_UNI_MultiDisplayEnable() != 0) && (OPT_CountModems() != 1)) {
				if (type == 2) {
					type = 0;
				}
				else {
					type++;
				}
			}
			else {
				type ^= 0x01;
			}
 #endif
			break;
		case OPR_CANCELED:			/* 停止キー 又は１分間キー入力なし */
			return;
		case NO_EFFECT:				/* 追加 Mar.16,1998 */
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}
#if (PRO_KEYPANEL == PANEL_STOCKHM2) /* Mod by SMuratec C.P 2004/06/10 for V195通信結果と予約確認画面の表示*/
/*************************************************************************
	module		:[通信確認オペレーション]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2004/06/10]
	author		:[陳萍]
*************************************************************************/
void ConfirmClearResultCommand(void)
{
	/*①　通信状態判断 */
	/* 初期化 */
	ClearReviewControlData();

	/* 参照位置の初期設定 */
	
	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_LINE_BUSY) && SYS_ConfirmTxRxFlag) { /* 受信状態 */
		/* ①通信中止確認画面を表示　
		   ②[確認]を押す場合：中止通信　
		   ③[取消]を押すと「中止通信」動作を削除 */		
		   
		ConfirmClearCommandOperation();

	}
	else { /* 非通信状態*/
	
		SelectReviewCommandOperation();
	} 
}
#endif
/*************************************************************************
	module		:[予約コマンド確認消去オペレーション]
	function	:[
		1.
	]
	return		:[
		OPR_CHANGED_MODE	:REVIEWキー押下時（次のモードに移行する為）
		OPR_CANCELED		:STOPキー押下時、またはタイムオーバー時
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/22]
	author		:[江口,松隈,渡辺一章]
*************************************************************************/
UBYTE ConfirmClearCommandOperation(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	status;

	/* 初期化 */

 #if defined(STOCKHM2)	/* Mod by SMuratec C.P 2004/06/10 */
	/* V195の通信結果表示仕様のため */
 #else
	ClearReviewControlData();
 #endif

	/* 参照位置の初期設定 */
	
	if (SetCommandPointer(COMMAND_FIRST_REVIEW) == OPR_END) { /* コマンドがなにもない */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (コマンドがなにもないので、F250では表示必要有りません。) Modified by SMuratec L.Z.W 2003/09/10 */
		OPR_ChildErrorFlag = NO_COMMAND_ERROR;
		NackBuzzer();
		return(OPR_CANCELED);
#else
		/************************************
		**↑メールコマンドも無いかチェック
		**  SetCommandPointer()に追加
		************************************/
		OPR_ChildErrorFlag = OPR_NO_ERROR;		/* これ入れてもいいか要確認 NO_COMMAND_ERROR削除してます*/
		DisplayStringHigh(0,D2W_NoCommand);
		/* 下段点滅表示 */
		FlashDisplayStringLow(D2W_ReviewStop);	/* "      ﾂｳｼﾝｶｸﾆﾝ/ｽﾄｯﾌﾟ" */
		while(1) {
			OPR_GetKey(KEY_WAIT_ONE_MINUTE);
			key = GetInputKeyCode();
			keytype = GetInputKeyType();

			switch (keytype) {
			case REVIEW:
 #if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
				status = SelectReviewCommandOperation();	/* 予約確認キーオペレーション選択 */

				if (status == OPR_CONTINUE) {
					return(OPR_CHANGED_MODE);
				}
				else {
					/* OPR_ENDが返ってきたら通信予約確認オペレーション終了 */
					return(OPR_CANCELED); 
				}
 #else
				return(OPR_CHANGED_MODE);

 #endif
			case STOP:
			case KEY_TIME_UP:
				return(OPR_CANCELED);
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
			case SINGLE:		/* 単一オペレーションキー */
				SingleKeyOperation(key);
				break;
#endif
			case NO_EFFECT:		/* 追加 By S.Fukui Mar.16,1998 */
				break;
			default:
				NackBuzzer();
				break;
			}
		}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
	}

	status = OPR_CONTINUE;

	while (status != OPR_END) {
		DisplayReviewCommand();	/** メールコマンドの表示を追加 */

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case REVIEW:	/* 通信確認キー */
 #if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
			status = SelectReviewCommandOperation();	/* 予約確認キーオペレーション選択 */

			if (status == OPR_CONTINUE) {
				return(OPR_CHANGED_MODE);
			}

			/* OPR_ENDが返ってきたら通信予約確認オペレーション終了 */
			break;
 #else
			return(OPR_CHANGED_MODE);

 #endif
		case FUNCTION:
			if (CheckCommandReviewMode() == OPR_COMMAND_REVIEW) { /* コマンド単位の確認消去の場合 */
				status = SetCommandPointer(COMMAND_REVIEW_MODE); /** メールコマンドサーチを追加 */

			}
			else { /*同報の宛先単位の消去モードの場合 */
				status = SetExecPointer(COMMAND_REVIEW_MODE);
			}
			break;
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (コマンドファイル参照位置のセット) Added by SMuratec L.Z.W 2003/10/24 */
		case LEFT_ARROW:
			if (CheckCommandReviewMode() == OPR_COMMAND_REVIEW) { /* コマンド単位の確認消去の場合 */
				status = SetBackCommand(COMMAND_REVIEW_MODE); 

			}
			else { /*同報の宛先単位の消去モードの場合 */
				NackBuzzer();
			}
			break;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		case BROADCAST:
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
			/*******************************************
			** メールコマンドについては
			** ChangeCommandReviewMode()の処理を行わない
			*******************************************/
			if ((OPR_Buf.ReviewCtrl.CommandKind == SYS_INF_MAIL_TX_CMD)
			||	(OPR_Buf.ReviewCtrl.CommandKind == SYS_INF_MAIL_RX_CMD)
			||	(OPR_Buf.ReviewCtrl.CommandKind == SYS_INF_MAIL_NO_CMD)) {
				NackBuzzer();
			}
			else {
				ChangeCommandReviewMode();
			}
#else
			ChangeCommandReviewMode();
#endif
			break;
		case CLEAR:	/* クリアキー */
			status = ConfirmKeyInputOperation(FunctionDisplayBufferHigh, D2W_CheckProgramClear, CLEAR, FUNCTION);
			if (status == CONFIRM_EXEC) {
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
				/**************************
				** メールコマンドクリア
				**************************/
				if ((OPR_Buf.ReviewCtrl.CommandKind == SYS_INF_MAIL_TX_CMD)
				||	(OPR_Buf.ReviewCtrl.CommandKind == SYS_INF_MAIL_RX_CMD)
				||	(OPR_Buf.ReviewCtrl.CommandKind == SYS_INF_MAIL_NO_CMD)) {
					status = EraseMailCommand();
				}
				else {
					status = ClearReviewCommandData();	/* 消去実行 */
				}
#else
				status = ClearReviewCommandData();	/* 消去実行 */
#endif
			}
			break;
		case STOP:
		case KEY_TIME_UP:
			status = OPR_END;
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
	return(OPR_CANCELED); 
}
/*************************************************************************
	module		:[通信確認オペレーション初期化処理]
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
	date		:[1996/01/22]
	author		:[江口]
*************************************************************************/
void ClearReviewControlData(void)
{
	OPR_Buf.ReviewCtrl.CommandPointer    = 0xFF;
	OPR_Buf.ReviewCtrl.ExecItem          = SYS_EMPTY_DIAL;
	OPR_Buf.ReviewCtrl.ExecPointer       = 0xFF;
	OPR_Buf.ReviewCtrl.ReviewMode        = OPR_COMMAND_REVIEW;
	OPR_Buf.ReviewCtrl.SearchCommandType = OPR_EXECUTE_COMMAND;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
	/****************
	** 初期化追加
	****************/
	CMN_MemorySet(&OPR_Buf.ReviewCtrl.UserNameOrID[0], OPR_USER_NAME_OR_ID_MAX, ' ');
	CMN_MemorySet(&OPR_Buf.ReviewCtrl.InputBuffer[0], OPR_INPUT_BUFFER_MAX, ' ');
#endif
}

/*************************************************************************
	module		:[コマンドファイル、一括送信ファイルの参照位置のセット]
	function	:[
		1.

	]g
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/26]
	author		:[江口,松隈,渡辺一章]
*************************************************************************/
UBYTE SetCommandPointer(UBYTE mode)
{
	UBYTE	i;					/* ループ変数 */
	UBYTE	status;				/* コマンドの状態 */
	UBYTE	com_set_ok;			/* １：コマンドあり、０：コマンドなし */
	UBYTE	same_command;		/* 検索の結果見つかったコマンドが前回参照していたコマンドと同じ時１にセット */
	UBYTE	max_number;
	UBYTE	kind;				/* コマンド種別（コマンドファイルか一括送信か */
	UBYTE	file_number;		/* コマンド番号または一括送信ファイル番号 */
	UBYTE	search_com;			/* 検索しているコマンドの種類 */
	UBYTE	next_search_com;	/* 次に検索するコマンドの種類 */

	com_set_ok = 0;
	same_command = 0;
	search_com  = OPR_Buf.ReviewCtrl.SearchCommandType;	/* 現在検索（参照）しているｺﾏﾝﾄﾞの種類を獲得 */
	file_number = OPR_Buf.ReviewCtrl.CommandPointer;	/* 現在の参照位置（ｺﾏﾝﾄﾞ番号、一括送信ﾌｧｲﾙ番号）を獲得 */

	if (file_number == 0xFF) {		/* 初期値 */
		file_number = 0;
	}
	else {
		/* 参照位置をすすめる。現在参照している位置の次から検索を始める
		** コマンドファイルの最大値をこえても問題ない。先頭に戻すとまずい
		** 最後まできたら検索するコマンドの種類がかわるため
		*/
		file_number++;
	}

	for (i = 0; i < OPR_MAX_COM_SEARCH; i++) {	/* 各検索モードすべてチェックするまで */
		switch (search_com) {
		case OPR_EXECUTE_COMMAND:	/** 実行中のコマンドを参照中 */
		case OPR_WAITING_COMMAND:	/** 実行待ち、予約中のコマンドファイルを参照中 */
			kind = SYS_COMMAND_TRX;
			max_number = SYS_COM_FILE_MAX;
			/* 次の検索モード（検索するコマンドの種類)をセット */
			if (search_com == OPR_EXECUTE_COMMAND) {
#if (PRO_BATCH_TX == ENABLE)
				/** 実行中のコマンドがない場合は実行中の一括送信を探す */
				next_search_com = OPR_EXECUTE_BATCH;
#else
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
				next_search_com = OPR_EXECUTE_CONTPOLL;
 #else
				/** 実行中のコマンドがない場合は実行待ち、予約中のコマンドを探す */
				next_search_com = OPR_WAITING_COMMAND;
 #endif
#endif
			}
			else {
#if (PRO_BATCH_TX == ENABLE)
				/** 実行まち、予約中のコマンドがない場合は実行待ち、予約中の一括送信を探す */
				next_search_com = OPR_WAITING_BATCH;
#else
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
				next_search_com = OPR_WAITING_CONTPOLL;
 #else
				/** 実行まち、予約中のコマンドがない場合は実行中のコマンドを探す */
				next_search_com = OPR_EXECUTE_COMMAND;
 #endif
#endif
			}
			break;

#if (PRO_BATCH_TX == ENABLE)
		case OPR_EXECUTE_BATCH:		/** 実行中の一括送信 */
		case OPR_WAITING_BATCH:		/** 実行待ち、予約中の一括送信 */
			kind = SYS_BATCH_TX;
			max_number = SYS_BATCH_FILE_MAX;

			/* 次の検索モード（検索するコマンドの種類)をセット */
			if (search_com == OPR_EXECUTE_BATCH) {
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
				next_search_com = OPR_EXECUTE_CONTPOLL;
 #else
				/** 実行中の一括送信がない場合は実行待ち、予約中のコマンドを探す */
				next_search_com = OPR_WAITING_COMMAND;
 #endif
			}
			else {
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
				next_search_com = OPR_WAITING_CONTPOLL;
 #else
				/** 実行まち、予約中の一括送信がない場合は実行中のコマンドを探す */
				next_search_com = OPR_EXECUTE_COMMAND;
 #endif
			}
			break;
#endif

#if (PRO_CONTINUOUS_POLLING == ENABLE)
		case OPR_EXECUTE_CONTPOLL:		/** 実行中の連続ポーリング */
		case OPR_WAITING_CONTPOLL:		/** 実行待ち、予約中の連続ポーリング */
			kind = SYS_CONTINUOUS_POLLING;
			max_number = SYS_CONT_POLLING_MAX;
			/* 次の検索モード（検索するコマンドの種類)をセット */
			if (search_com == OPR_EXECUTE_CONTPOLL) {
				/** 実行中の一括送信がない場合は実行待ち、予約中のコマンドを探す */
				next_search_com = OPR_WAITING_COMMAND;
			}
			else {
				/** 実行まち、予約中の一括送信がない場合は実行中のコマンドを探す */
				next_search_com = OPR_EXECUTE_COMMAND;
			}
			break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		/********************************************
		** サーチコマンドに対するパラメータセット
		********************************************/
		case OPR_EXECUTE_MAILTRX:
		case OPR_WAITING_MAILTRX:
			max_number = SYS_INF_MAIL_COM_MAX;
			/* 次の検索モード（検索するコマンドの種類)をセット */
			if (search_com == OPR_EXECUTE_MAILTRX) {
				/** 実行待ち、予約中のコマンドを探す */
				next_search_com = OPR_WAITING_COMMAND;
			}
			else {
				/** 実行中のコマンドを探す */
				next_search_com = OPR_EXECUTE_COMMAND;
			}
			break;
#endif
		default:
			break;
		}

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		/******************************
		** 次のサーチコマンドセット
		******************************/
		if ((next_search_com == OPR_WAITING_COMMAND)
			&& (search_com != OPR_EXECUTE_MAILTRX)) {
			next_search_com = OPR_EXECUTE_MAILTRX;
		}
		else {
			if ((next_search_com == OPR_EXECUTE_COMMAND)
				&& (search_com != OPR_WAITING_MAILTRX)) {
				next_search_com = OPR_WAITING_MAILTRX;
			}
		}
		switch (search_com) {
		case OPR_EXECUTE_COMMAND:
		case OPR_WAITING_COMMAND:
 #if (PRO_BATCH_TX == ENABLE)
		case OPR_EXECUTE_BATCH:
		case OPR_WAITING_BATCH:
 #endif
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
		case OPR_EXECUTE_CONTPOLL:
		case OPR_WAITING_CONTPOLL:
 #endif
			/** 各検索モードに対するコマンドの検索を実行 */
			for (; file_number < max_number; file_number++) {	/* コマンドファイル、または一括送信ファイルを１周するまで */

				/** コマンドの登録状態を獲得 */
				status = CheckCommandBatchStatus(kind, file_number);

				if (status == SYS_CMD_EXECUTE) {	/** キューに展開されていてかつ、実行中か実行前 */
					/* 実行中のコマンドかどうか調べる */
					if (CheckExecuteCommand(kind, file_number) < SYS_EXEC_QUEUE_MAX) {	/** 指定されたｺﾏﾝﾄﾞに対するｷｭｰが実行中 */
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
						/** 検索しているのが、実行中のコマンドか一括送信か連続ポーリングの場合 */
						if ((search_com == OPR_EXECUTE_COMMAND)
						 || (search_com == OPR_EXECUTE_BATCH)
						 || (search_com == OPR_EXECUTE_CONTPOLL)) {
							break;	/*見つかったのでループを抜ける */
						}
 #else
  #if (PRO_BATCH_TX == ENABLE)
						/** 検索しているのが、実行中のコマンドか一括送信の場合 */
						if ((search_com == OPR_EXECUTE_COMMAND)
						 || (search_com == OPR_EXECUTE_BATCH)) {
							break;	/*見つかったのでループを抜ける */
						}
  #else
						/** 検索しているのが、実行中のコマンドの場合 */
						if (search_com == OPR_EXECUTE_COMMAND) {
							break;	/*見つかったのでループを抜ける */
						}
  #endif
 #endif
					}
					else {	/** 指定されたコマンドに対するキューが実行待ち */
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
						if ((search_com == OPR_WAITING_COMMAND)
						 || (search_com == OPR_WAITING_BATCH)
						 || (search_com == OPR_WAITING_CONTPOLL)) {
							break;
						}
 #else
  #if (PRO_BATCH_TX == ENABLE)
						if ((search_com == OPR_WAITING_COMMAND)
						 || (search_com == OPR_WAITING_BATCH)) {
							break;
						}
  #else
						if (search_com == OPR_WAITING_COMMAND) {
							break;
						}
  #endif
 #endif
					}
				}
				else if (status == SYS_CMD_WAITING) { /* 予約中 */
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
					if ((search_com == OPR_WAITING_COMMAND)
					 || (search_com == OPR_WAITING_BATCH)
					 || (search_com == OPR_WAITING_CONTPOLL)) {
						break;
					}
 #else
  #if (PRO_BATCH_TX == ENABLE)
					if ((search_com == OPR_WAITING_COMMAND)
					 || (search_com == OPR_WAITING_BATCH)) {
						break;
					}
  #else
					if (search_com == OPR_WAITING_COMMAND) {
						break;
					}
  #endif
 #endif
				}
			}
		break;
		/**************************
		** メールコマンドサーチ
		**************************/
		case OPR_EXECUTE_MAILTRX:
		case OPR_WAITING_MAILTRX:
			for (; file_number < max_number; file_number++) {
				status = CheckMailCommandStatus(file_number);
				if (status == OPR_MAIL_CMD_EXECUTE) {
					if (search_com == OPR_EXECUTE_MAILTRX) {
						if ((SYS_INF_MailCommand[file_number].Kind == SYS_INF_MAIL_TX)
						||	(SYS_INF_MailCommand[file_number].Kind == SYS_INF_MAIL_TXRX)) {
							kind = SYS_INF_MAIL_TX_CMD;	/** 通信の種類 */
							OPR_INF_TempAddressInput.Offset = 0;
							CMN_MemorySet(&OPR_INF_TempAddressInput.Buffer[0], OPR_INPUT_BUFFER_MAX, ' ');
							GetAddressInputBuffer(file_number);	/** 宛先を獲得 */
						}
						else if ((SYS_INF_MailCommand[file_number].Kind == SYS_INF_MAIL_MANUAL_RX)
							||   (SYS_INF_MailCommand[file_number].Kind == SYS_INF_MAIL_AUTO_RX)
							||   (SYS_INF_MailCommand[file_number].Kind == SYS_INF_MAIL_AUTO_CHK)){
							kind = SYS_INF_MAIL_RX_CMD;	/** 通信の種類 */
							CMN_MemorySet(&OPR_INF_UserData.TempUserData[0], OPR_USER_DATA_TEMP_MAX, ' ');
							GetNameOrPOP_LoginID(&OPR_INF_UserData.TempUserData[0], file_number);	/** コマンドを起動したユーザ名かPOP IDを獲得 */
						}
						else {
							kind = SYS_INF_MAIL_NO_CMD;	/** 通信の種類(無いはず) */
						}
						break;
					}
				}
				else if (status == OPR_MAIL_CMD_WAITING) {
					if (search_com == OPR_WAITING_MAILTRX) {
						if ((SYS_INF_MailCommand[file_number].Kind == SYS_INF_MAIL_TX)
						||	(SYS_INF_MailCommand[file_number].Kind == SYS_INF_MAIL_TXRX)) {
							kind = SYS_INF_MAIL_TX_CMD;	/** 通信の種類 */
							OPR_INF_TempAddressInput.Offset = 0;
							CMN_MemorySet(&OPR_INF_TempAddressInput.Buffer[0], OPR_INPUT_BUFFER_MAX, ' ');
							GetAddressInputBuffer(file_number);	/** 宛先を獲得 */
						}
						else if ((SYS_INF_MailCommand[file_number].Kind == SYS_INF_MAIL_MANUAL_RX)
							||   (SYS_INF_MailCommand[file_number].Kind == SYS_INF_MAIL_AUTO_RX)
							||   (SYS_INF_MailCommand[file_number].Kind == SYS_INF_MAIL_AUTO_CHK)){
							kind = SYS_INF_MAIL_RX_CMD;	/** 通信の種類 */
							CMN_MemorySet(&OPR_INF_UserData.TempUserData[0], OPR_USER_DATA_TEMP_MAX, ' ');
							GetNameOrPOP_LoginID(&OPR_INF_UserData.TempUserData[0], file_number);	/** コマンドを起動したユーザ名かPOP IDを獲得 */
						}
						else {
							kind = SYS_INF_MAIL_NO_CMD;	/** 通信の種類(無いはず) */
						}
						break;
					}
				}
			}
		break;
		}
#else
		/** 各検索モードに対するコマンドの検索を実行 */
		for (; file_number < max_number; file_number++) {	/* コマンドファイル、または一括送信ファイルを１周するまで */

			/** コマンドの登録状態を獲得 */
			status = CheckCommandBatchStatus(kind, file_number);

			if (status == SYS_CMD_EXECUTE) {	/** キューに展開されていてかつ、実行中か実行前 */
				/* 実行中のコマンドかどうか調べる */
				if (CheckExecuteCommand(kind, file_number) < SYS_EXEC_QUEUE_MAX) {	/** 指定されたｺﾏﾝﾄﾞに対するｷｭｰが実行中 */
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
					/** 検索しているのが、実行中のコマンドか一括送信か連続ポーリングの場合 */
					if ((search_com == OPR_EXECUTE_COMMAND)
					 || (search_com == OPR_EXECUTE_BATCH)
					 || (search_com == OPR_EXECUTE_CONTPOLL)) {
						break;	/*見つかったのでループを抜ける */
					}
 #else
  #if (PRO_BATCH_TX == ENABLE)
					/** 検索しているのが、実行中のコマンドか一括送信の場合 */
					if ((search_com == OPR_EXECUTE_COMMAND)
					 || (search_com == OPR_EXECUTE_BATCH)) {
						break;	/*見つかったのでループを抜ける */
					}
  #else
					/** 検索しているのが、実行中のコマンドの場合 */
					if (search_com == OPR_EXECUTE_COMMAND) {
						break;	/*見つかったのでループを抜ける */
					}
  #endif
 #endif
				}
				else {	/** 指定されたコマンドに対するキューが実行待ち */
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
					if ((search_com == OPR_WAITING_COMMAND)
					 || (search_com == OPR_WAITING_BATCH)
					 || (search_com == OPR_WAITING_CONTPOLL)) {
						break;
					}
 #else
  #if (PRO_BATCH_TX == ENABLE)
					if ((search_com == OPR_WAITING_COMMAND)
					 || (search_com == OPR_WAITING_BATCH)) {
						break;
					}
  #else
					if (search_com == OPR_WAITING_COMMAND) {
						break;
					}
  #endif
 #endif
				}
			}
			else if (status == SYS_CMD_WAITING) { /* 予約中 */
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
				if ((search_com == OPR_WAITING_COMMAND)
				 || (search_com == OPR_WAITING_BATCH)
				 || (search_com == OPR_WAITING_CONTPOLL)) {
					break;
				}
 #else
  #if (PRO_BATCH_TX == ENABLE)
				if ((search_com == OPR_WAITING_COMMAND)
				 || (search_com == OPR_WAITING_BATCH)) {
					break;
				}
  #else
				if (search_com == OPR_WAITING_COMMAND) {
					break;
				}
  #endif
 #endif
			}
		}
#endif	/*	PRO_DIALUP_INTERNET_FAX 1998/03/12 by K.Okada */

		if (file_number >= max_number) {	/** 該当するコマンドがない */
			search_com = next_search_com;	/* 検索モードを次のモードに変更 */
			file_number = 0;	/* ファイル番号を初期化(先頭から検索させる) */
		}
		else {
			/* コマンドあり */
			if ((search_com == OPR_Buf.ReviewCtrl.SearchCommandType)
			 && (file_number == OPR_Buf.ReviewCtrl.CommandPointer)) {
				/* Same Command */
				same_command = 1;
			}
			com_set_ok = 1;
			break; /* 検索終了 */
		}
	}

	if (com_set_ok) {
		if (same_command) {	/* 前回参照していたもの以外コマンドがない */
			/* エラー表示を出す */
			/* 終了はしない */
			NackBuzzer();
			OPR_ChildErrorFlag = NO_COMMAND_ERROR;
		}
		else {
			OPR_Buf.ReviewCtrl.CommandPointer = file_number;
			OPR_Buf.ReviewCtrl.SearchCommandType = search_com;
			OPR_Buf.ReviewCtrl.CommandKind = kind;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
			if (kind == SYS_INF_MAIL_TX_CMD) {
				/************
				** 宛先を確保
				************/
				CMN_StringCopyNumNotNULL(&OPR_Buf.ReviewCtrl.InputBuffer[0],&OPR_INF_TempAddressInput.Buffer[0],OPR_INPUT_BUFFER_MAX);
			}
			else if (kind == SYS_INF_MAIL_RX_CMD) {
				/**********************************
				** ユーザ名かIDをあらかじめ確保
				**********************************/
				CMN_StringCopyNumNotNULL(&OPR_Buf.ReviewCtrl.UserNameOrID[0],&OPR_INF_UserData.TempUserData[0],OPR_USER_NAME_OR_ID_MAX);
			}
#endif
		}
		return (OPR_CONTINUE);
	}
	else {	/* 実行中、実行前、予約中のコマンドがなにもない */
		/* エラー表示を出す */
		/* 終了する */
		if (mode == COMMAND_REVIEW_MODE) { /* 1996/04/08 消去後のポインターの再設定以外であればエラー表示をだす */
			NackBuzzer();
			OPR_ChildErrorFlag = NO_COMMAND_ERROR;
		}
		return (OPR_END);
	}
}

/*************************************************************************
	module		:[予約確認オペレーションモードを獲得]
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
	date		:[1996/01/22]
	author		:[江口]
*************************************************************************/
UBYTE CheckCommandReviewMode(void)
{
	return (OPR_Buf.ReviewCtrl.ReviewMode);
}

/*************************************************************************
	module		:[指定されたコマンド／一括がキューに展開されているか調べる]
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
	date		:[1996/01/22]
	author		:[江口]
*************************************************************************/
UBYTE SearchExecQueue(UBYTE kind,			/**コマンド種別（コマンドファイルか一括送信か)*/
					  UBYTE file_number)	/**コマンド番号 */
{
	UBYTE	exec_file;

	/* コマンドファイル番号からキューを逆引き */
	for (exec_file = 0; exec_file < SYS_EXEC_QUEUE_MAX; exec_file++) {
		if ((CheckExecQueueBeforeStart(exec_file) == TRUE)					/* 発呼前のコマンドである */
		 && (CheckExecKindNumber(kind, file_number, exec_file) == OK)) {	/* 指定されたコマンドに関するキューである */
			return (exec_file);
		}
	}
	return (SYS_EXEC_QUEUE_MAX);
}

/*************************************************************************
	module		:[指定されたキューが実行中か実行待ちの物か調べる]
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
	date		:[1996/01/22]
	author		:[江口]
*************************************************************************/
UBYTE CheckExecQueueBeforeStart(UBYTE exec_file)
{
	UBYTE	status;

	status = SYB_ExecQueue[exec_file].Status;
	if ((status == SYS_EXEC_EXECUTE)			/* 通信中					*/
	||	(status == SYS_EXEC_FORWARD_EXECUTE)	/* 転送ダイヤル送信中		*/
	||	(status == SYS_EXEC_WAITING)			/* ダイヤル待ち状態			*/
	||	(status == SYS_EXEC_FORWARD_WAITING)) {	/* 転送ダイヤル待ち状態中	*/
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[指定されたキューが実行中か調べる]
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
	date		:[1996/01/22]
	author		:[江口]
*************************************************************************/
UBYTE CheckExecuteExecQueue(UBYTE exec_file)
{
	if ((SYB_ExecQueue[exec_file].Status == SYS_EXEC_EXECUTE)				/* 通信中				*/
	||	(SYB_ExecQueue[exec_file].Status == SYS_EXEC_FORWARD_EXECUTE)) {	/* 転送ダイヤル送信中	*/
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[指定されたコマンドに対するキューか調べる]
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
	date		:[1996/01/22]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE CheckExecKindNumber(UBYTE kind, UBYTE number, UBYTE exec_file)
{
	switch (kind) {
	case SYS_COMMAND_TRX:
		if ((SYB_ExecQueue[exec_file].Kind == kind) && (SYB_ExecQueue[exec_file].Number.Command == number)) {
			return (OK);
		}
		break;

#if (PRO_BATCH_TX == ENABLE)
	case SYS_BATCH_TX:
		if ((SYB_ExecQueue[exec_file].Kind == kind) && (SYB_ExecQueue[exec_file].Number.Batch == number)) {
			return (OK);
		}
		break;
#endif

#if (PRO_CONTINUOUS_POLLING == ENABLE)
	case SYS_CONTINUOUS_POLLING:
		if ((SYB_ExecQueue[exec_file].Kind == kind) && (SYB_ExecQueue[exec_file].Number.ContPolling == number)) {
			return (OK);
		}
		break;
#endif

	default:
		break;
	}
	return (NG);
}

/*************************************************************************
	module		:[実行中のコマンドか調べる]
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
	date		:[1996/01/22]
	author		:[江口]
*************************************************************************/
UBYTE CheckExecuteCommand(UBYTE kind, UBYTE number)
{
	UBYTE	exec_file;

	for (exec_file = 0; exec_file < SYS_EXEC_QUEUE_MAX; exec_file++) {
		if ((CheckExecuteExecQueue(exec_file) 				== TRUE)
		&&	(CheckExecKindNumber(kind , number , exec_file) == OK  )) { /** 指定されたコマンドに対するキューが実行中である */
			return (exec_file);
		}
	}
	return (SYS_EXEC_QUEUE_MAX);
}

/*************************************************************************
	module		:[予約消去]
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
	date		:[1996/01/22]
	author		:[江口,松隈,渡辺一章]
*************************************************************************/
UBYTE ClearReviewCommandData(void)
{
	/*
	**・必ず消去できる条件か調べてから消去すること
	**・消去できるキューは実行中か実行待ちのものに限る
	**・キューを消去する場合
	**　StatusをERASEDにする
	**　同報コマンドでない場合は対応するコマンドのStatusをERASEDにする
	**　同報コマンドでない場合でかつスキャナーコマンドの場合、各種スキャナーデータをクリア
	**・コマンド,一括を消去する場合
	**　対応するキューがある場合、キューのステータスをERASEDにする
	**　スキャナーコマンドの場合、各種スキャナーデータをクリアする
	**　コマンドのステータスをERASEDにする
	**・キューに展開されていないコマンドの１宛先を消去する場合
	**　ダイアルナンバーのステータスをEMPTYにする
	*/

	UBYTE	file_number;	/* コマンドファイル番号・一括送信ファイル番号 */
	UBYTE	kind;			/* コマンドファイルか一括送信か */
	UBYTE	exec_item;		/* キュー種別 */	/* 97/03/21 */
	UBYTE	exec_pointer;	/* キュー番号 */
	UBYTE	status;
	UBYTE	review_mode;	/* コマンド単位の確認消去モードかキュー単位の確認消去モードか */
	struct	SYS_DialData_t *dp;	/* 97/03/21 */

	file_number = OPR_Buf.ReviewCtrl.CommandPointer;
	kind = OPR_Buf.ReviewCtrl.CommandKind;

#if (PRO_RELAYED_REPORT == ENABLE)	/* Add By H.Fujimura 1999/02/05 */
	if (SYB_CommandFile[file_number].Option.Item == SYS_RELAYED_TX_REPORT) {
		if ( SYB_MaintenanceSwitch[MNT_SW_B8] & RELAYED_TX_REPORT_COMM_EREASE ) {
			/** 不達通知プリントＯＮで,中継配信のチェックメッセージをプリント中なら	**
			**	「プリント中です」表示でクリア不可とする							*/
			if (CHK_RelayedReportPrint()) {
				if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)
				&&	(SYS_DocumentPrintItem == SYS_MEM_TX_FILE)
				&&	(SYS_DocumentPrintNo == SYB_CommandFile[file_number]
											.Option.OptionNumber.RelaySourceID[0])) {
					NackBuzzer();
					OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;		/* "ﾌﾟﾘﾝﾄﾁｭｳ ﾃﾞｽ        " */
					return (OPR_CONTINUE);
				}
			}
		}
		else {
			NackBuzzer();
			OPR_ChildErrorFlag = LINE_BUSY_ERROR;		/* "ﾂｳｼﾝﾁｭｳ ﾃﾞｽ         " */
			return (OPR_CONTINUE);
		}
	}
#endif

#if (PRO_CIPHER == ENABLE)	/* Add By T.Fukumoto 98/01/29 */
	/* 指定されたコマンドがスクランブル送信予約で、予約原稿がスクランブル解除中の時は、消去できません
	** 注１）デスクランブルが完了してからでないと、プリントを開始しない仕様なので、プリント中に消去されても
	** 　　  問題はありません（デスクランブル後は、データが別になるため）
	** 注２）スクランブル送信予約原稿のプリント中は、SYS_DocumentPrintItemにはSYS_MEM_TX_DECIPHER_FILEが
	**       セットされているため、CheckCommandPrinting()ではプリント中と判断されません
	*/
	if ((SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_EXEC)	/* デスクランブル中         */
	 && (SYB_CommandFile[file_number].Option.Item == SYS_CIPHER_TX)		/* 暗号化原稿               */
	 && ((UWORD)file_number == CipherReadIndex.No)						/* コマンド番号             */
	 && (SYS_CipherComExec == SYS_TX_DOC_DECIPHER_EXEC)) {				/* 送信予約原稿暗号化解除中 */
		NackBuzzer();
		OPR_ChildErrorFlag = DECIPHERING_ERROR;	/* "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ﾁｭｳﾃﾞｽ" */
		return (OPR_CONTINUE);
	}
#endif

	if (CheckCommandPrinting(kind, file_number) == TRUE) {	/* 指定されたコマンドがプリント中 */
		/* コマンド消去できない */
		NackBuzzer();
		if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PRINTER_CLEANING) {
			OPR_ChildErrorFlag = PRINTER_CLEANING_ERROR;	/* "ｼﾊﾞﾗｸ ｵﾏﾁｸﾀﾞｻｲ      " */
		}
		else {
			OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;		/* "ﾌﾟﾘﾝﾄﾁｭｳ ﾃﾞｽ        " */
		}
		return (OPR_CONTINUE);
	}

	status = CheckCommandBatchStatus(kind , file_number);
	review_mode = CheckCommandReviewMode();

	switch (review_mode) {
	case OPR_COMMAND_REVIEW: /** コマンド単位の確認消去モード *//*コマンドファイル、一括送信ファイルを参照 */
		if (status == SYS_CMD_EXECUTE) { /**キューに展開されている場合 */
			/** 対応するキューを消去する */
			ClearAllExecQueueData(kind , file_number);

			/** スキャナーコマンドの場合,各種スキャナデータをクリアする */
			/* 一括送信はありえない */
			if ((kind == SYS_COMMAND_TRX) && (CMN_CheckScannerTxCommand(file_number) == TRUE)) {
				ResetAllScannerParameter();
			}

			/** 指定されたコマンドファイルもしくは一括送信ファイルを消去する */
			/*-----------------------------------------------------------------------*/
			/* 指定されたコマンドに対応するキューが全て消去されていないと消去できない*/
			/* ERRORの場合、チェックメッセージをかく必要があるので消去しない。		 */
			/* -> チェックメッセージ印字後メインで消去する							 */
			/* OKの場合、モニターレポートをかくかもしれないので消去しない。			 */
			/* -> レポート印字後メインで消去する							 		 */
			/* 但し上記の仕様にした場合、コマンド消去後もコマンドファイルが解放されない */
			/* 場合(チェックメッセージを書こうとして、紙がない場合）があるので、新たな */
			/* 予約ができなくなる可能性がある.											*/
			/* なお、上記の仕様は変更される可能性があります。1996/01/20 Eguchi			*/
			/*--------------------------------------------------------------------------*/
			if (CheckAllClearExecQueue(kind ,file_number) == TRUE) { /** 対応するキューが全て消去された */
				ClearCommandBatchFile(kind , file_number);/** 指定されたコマンドを消去 */
			}
		}
		else if (status == SYS_CMD_WAITING) { /*キューに展開されていない */
			/* スキャナーコマンドの場合,各種スキャナデータをクリアする */
			/* 一括送信はありえない */
			if ((kind == SYS_COMMAND_TRX) && (CMN_CheckScannerTxCommand(file_number) == TRUE)) {
				ResetAllScannerParameter();
			}

#if (PRO_RELAYED_REPORT == ENABLE)	/* Add By H.Fujimura 1999/02/05 */
			if  (SYB_CommandFile[file_number].Option.Item == SYS_RELAYED_TX_REPORT) { /* 不達通知コマンドに対しては、*/
				/* 親の中継配信コマンドも消す。*/
				CMN_ClearCommandArea(SYS_COMMAND_TRX, SYB_CommandFile[file_number].Option.OptionNumber.RelaySourceID[0]);
			}
#endif

			/* コマンドを消去 */
			ClearCommandBatchFile(kind , file_number);
		}
		break;

	case OPR_EXEC_REVIEW:  /*同報の宛先単位の確認消去モードでキューに展開されている場合 *//* この場合は一括送信はないはず */
		exec_pointer = OPR_Buf.ReviewCtrl.ExecPointer;	/* 参照位置の取り出し */
		if (CheckExecQueueBeforeStart(exec_pointer) == TRUE) { /*消去しようとしているキューが実行中か実行待ち又は実行中->消去可能 */
															   /*クリアしようとした時に実行中の通信が終了していたような場合を想定してこの処理をいれる */
			/* 消去実行 */
			SYB_ExecQueue[exec_pointer].Status = SYS_EXEC_ERASED;
			if (CheckAllClearExecQueue(kind ,file_number) == TRUE) {/*結果的にすべてのキューが消去された*/
																   /*同報を宛先単位で消去していき、結果的に全ての宛先を消去した */
				/* コマンドを消去する */
				ClearCommandBatchFile(kind , file_number);
			}
		}
		break;

	case OPR_COM_DIAL_REVIEW:  /*同報の宛先単位の確認消去モードでキューに展開されていない場合 *//* この場合は一括送信はないはず */
		/* ExecPointerがコマンドファイルのダイアル番号の配列オフセット値を保持している時 */
		exec_item    = OPR_Buf.ReviewCtrl.ExecItem;		/* 参照位置の取り出し *//* 97/03/21 */
		exec_pointer = OPR_Buf.ReviewCtrl.ExecPointer;	/* 参照位置の取り出し */

#if (PRO_CONTINUOUS_POLLING == ENABLE)
		if (kind == SYS_COMMAND_TRX) {
			dp	= &SYB_CommandFile[file_number].DialNumber;
		}
		else {	/* 連続ポーリング */
			dp	= &SYB_ContinuousPolling.DialNumber;
		}
#else
		dp	= &SYB_CommandFile[file_number].DialNumber;
#endif
		switch( exec_item ){
		case	SYS_DIRECT_DIAL:		/* 直接ダイヤル */
			dp->Direct[exec_pointer][0]	= 0xf0;
			break;
		case	SYS_ONETOUCH_DIAL:		/* ワンタッチダイヤル */
			CMN_ClearBitAssign((UBYTE *)&dp->Onetouch, exec_pointer);
			break;
		case	SYS_SPEED_DIAL:			/* 短縮ダイヤル */
			CMN_ClearBitAssign((UBYTE *)&dp->Speed, exec_pointer);
			break;
		case	SYS_GROUP_DIAL:			/* グループダイヤル */
			CMN_ClearLongBitAssign((UDWORD *)&dp->Group, exec_pointer);
			break;
		}
		if (CheckAllClearCommandDial(file_number) == TRUE) { /* 全てのダイアルデータが消去された */
			/* コマンドを消去する */
			ClearCommandBatchFile(kind, file_number);
		}
		break;
	}

	/* メインタスクにコマンド消去のメッセージを送信 */
#if (PRO_CONTINUOUS_POLLING == ENABLE)
	if (kind == SYS_CONTINUOUS_POLLING) {	/* 連続ポーリング */
		OperationMessageToMain.Message = MSG_ERASE_CONTINUOUS_POLLING;
	}
	else {
		OperationMessageToMain.Message = MSG_ERASE_COMMAND;
	}
#else
	OperationMessageToMain.Message = MSG_ERASE_COMMAND;
#endif
	snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
	MainTaskExecWait();

	/* 消去完了表示 */
	if (ClearCompleteDisplayOperation(FunctionDisplayBufferHigh) == OPR_END) {
		return (OPR_END);
	}

	/*----------------------------------------------------------------------------------*/
	/* 	消去実行後の各データの再設定 													*/
	/*  コマンドを消去した場合 															*/
	/*    コマンドポインターの再設定を行う												*/
	/*  同報(キューに展開されている)の１宛先を消去した場合								*/
	/*  同報(キューに展開されていない）の１宛先を消去した場合							*/
	/*	  まだ同じコマンドに対する宛先データがある場合は実行ポインター進める 			*/
	/*	  同一コマンドに対する宛先データを全て消去した場合、コマンド消去モードに移る	*/
	/*----------------------------------------------------------------------------------*/
	if (review_mode == OPR_COMMAND_REVIEW) {/** コマンド単位の確認消去モードにおいて消去実行 */
		return (SetCommandPointer(COMMAND_CLEAR_MODE));
	}
	else { /**コマンドの各宛先単位の確認消去モードにおいて消去実行 */
		return (SetExecPointer(COMMAND_CLEAR_MODE));
	}
}

/*************************************************************************
	module		:[消去しようとしているコマンドがプリント中か調べる]
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
	date		:[1996/01/22]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE CheckCommandPrinting(UBYTE kind, UBYTE number)
{
	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)
	 && (SYS_MachineStatus[SYS_MACHINE_STATUS]  & SYS_IMAGE_PRINT )) {	/* プリント中 */

		switch (kind) {
		case SYS_COMMAND_TRX:
			if ((SYS_DocumentPrintItem == (UBYTE)SYS_MEM_TX_FILE) && (SYS_DocumentPrintNo == (UWORD)number)) {
				return (TRUE);
			}
			break;

#if (PRO_BATCH_TX == ENABLE)
		case SYS_BATCH_TX:
			if (SYS_DocumentPrintItem == (UBYTE)SYS_MEM_BATCH_TX_FILE1 + number) {
				return (TRUE);
			}
			break;
#endif

#if 0
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
//		case SYS_CONTINUOUS_POLLING:
//			if ((SYS_DocumentPrintItem == (UBYTE)SYS_MEM_TX_FILE) && (SYS_DocumentPrintNo == (UWORD)number)) {
//				return (TRUE);
//			}
//			break;
 #endif
#endif
		default:
			break;
		}
	}
	return (FALSE);
}

/*************************************************************************
	module		:[指定されたコマンドに対するキューが全て消去されたか調べる]
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
	date		:[1996/01/22]
	author		:[江口]
*************************************************************************/
UBYTE CheckAllClearExecQueue(UBYTE kind,	/* コマンド種別 */
							 UBYTE number)	/* コマンド番号 */
{
	UBYTE	exec_file;

	for (exec_file = 0; exec_file < SYS_EXEC_QUEUE_MAX; exec_file++) {
		if (CheckExecKindNumber(kind , number , exec_file) == OK) { /*指定されたコマンドに対するキューである */
			if ((SYB_ExecQueue[exec_file].Status != SYS_EXEC_ERASED)
			&&	(SYB_ExecQueue[exec_file].Status != SYS_EXEC_EMPTY )) {/*実行終了/エラー終了/実行中/実行前*/
				return (FALSE);
			}
		}
	}
	return (TRUE);
}

/*************************************************************************
	module		:[指定されたコマンドのダイアル番号が全て消去されたか調べる]
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
	date		:[1996/01/22]
	author		:[江口,松隈,渡辺一章]
*************************************************************************/
UBYTE CheckAllClearCommandDial(UBYTE file_number)
{
	UBYTE	i;
	UBYTE	kind;
	struct	SYS_DialData_t *dp;

#if (PRO_CONTINUOUS_POLLING == ENABLE)
	kind = OPR_Buf.ReviewCtrl.CommandKind;	/* キューのkindと同じ*/
#endif

#if (PRO_CONTINUOUS_POLLING == ENABLE)
	if (kind == SYS_COMMAND_TRX) {
		dp = &SYB_CommandFile[file_number].DialNumber;
	}
	else {	/* 連続ポーリング */
		dp = &SYB_ContinuousPolling.DialNumber;
	}
#else
#if (0)
** 	/* 連続ポーリングが無効の機種の場合、Kindが初期化不良となります。
** 	** でも、ここ以外のソースを見ると、無条件でコマンドファイルを指しても問題ない。
** 	** by O.Kimoto 1999/02/10
** 	*/
** 	if (kind == SYS_COMMAND_TRX) {
** 		dp = &SYB_CommandFile[file_number].DialNumber;
** 	}
#else
	dp = &SYB_CommandFile[file_number].DialNumber;
#endif

#endif
	for (i = 0; i < SYS_ONETOUCH_MAX; i++) {		/* ワンタッチダイヤル */
		if (CMN_CheckBitAssign(dp->Onetouch, i) == TRUE) {
			return(FALSE);
		}
	}

	for (i = 0; i < SYS_SPEED_DIAL_MAX; i++) {		/* 短縮ダイヤル */
		if (CMN_CheckBitAssign(dp->Speed, i) == TRUE) {
			return(FALSE);
		}
	}

	for (i = 0; i < SYS_COM_DIRECT_DIAL_MAX; i++) {	/* 直接ダイヤル */
		if ((dp->Direct[i][0] & 0xF0) != 0xF0) {
			return(FALSE);
		}
	}

	for (i = 0; i < SYS_GROUP_NUMBER_MAX; i++) {	/* グループ */
		if (CMN_CheckLongBitAssign(dp->Group, i) == TRUE) {
			return(FALSE);
		}
	}
	return (TRUE);
}

/*************************************************************************
	module		:[指定されたコマンドに対する実行キューを全て消去]
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
	date		:[1996/01/22]
	author		:[江口]
*************************************************************************/
void ClearAllExecQueueData(UBYTE kind, UBYTE number)
{
	UBYTE	exec_file;

	/*----------------------------------------------------------------------------------------------*/
	/* 指定されたコマンドに対応するキューを全て消去する 											*/
	/* 但し、消去可能なキューは実行中か実行前のものに限る（StatusがEXEC_EXECUTE,EXEC_WAITING) 		*/
	/* 同じコマンドに対するキューでも、実行が終了しているもの（EXEC_ERROR/EXEC_OK)のものは消去しない*/
	/* 上記の仕様は変更される可能性があります 1996/01/20 Eguchi 									*/
	/*----------------------------------------------------------------------------------------------*/
	for (exec_file = 0; exec_file < SYS_EXEC_QUEUE_MAX; exec_file++) { /* キュー全て検索する */
		if ((CheckExecQueueBeforeStart(exec_file)		   == TRUE)   /* 実行中または実行前のキューである　*/
		&&	(CheckExecKindNumber(kind , number ,exec_file) == OK  )) {/* 指定されたコマンドデータとキューが一致するか調べる */
			SYB_ExecQueue[exec_file].Status = SYS_EXEC_ERASED;
		}
	}
}

/*************************************************************************
	module		:[各種スキャナーデータをリセット]
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
	date		:[1996/01/22]
	author		:[江口]
*************************************************************************/
void ResetAllScannerParameter(void)
{
	CMN_ResetMemoyFeederTx();	/* メモリー送信をリセット */
	CMN_ResetStamp();			/* スタンプ設定をリセット */
	CMN_ResetPrimaryMode(); 	/* モードをリセット */
	CMN_ResetPrimaryContrast();	/* 濃度をリセット */
	CMN_ResetConfirmationReport();/* 通信状況をリセット */
#if (PRO_RED_SCAN == ENABLE)	/* 朱色読み取り 2002/03/05 T.Takagi */
	CMN_ResetRedScan();			/* 朱色読み取りをリセット */
#endif
}

/*************************************************************************
	module		:[指定されたコマンドを消去]
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
	date		:[1996/01/22]
	author		:[江口,渡辺一章]
*************************************************************************/
void ClearCommandBatchFile(UBYTE kind, UBYTE file_number)
{
	/* 指定されたコマンドファイルもしくは一括送信ファイルを消去する */
	switch (kind) {
	case SYS_COMMAND_TRX:
		SYB_CommandFile[file_number].Status = SYS_CMD_ERASED;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
		SYB_CommandStatus[file_number] = SYS_CMD_ERASED;
#endif
		break;

#if (PRO_BATCH_TX == ENABLE)
	case SYS_BATCH_TX:
		SYB_BatchTxFile[file_number].Status = SYS_CMD_ERASED;
		break;
#endif

#if (PRO_CONTINUOUS_POLLING == ENABLE)
	case SYS_CONTINUOUS_POLLING:
		SYB_ContinuousPolling.Status = SYS_CMD_ERASED;
		break;
#endif

	default:
		break;
	}
}

/*************************************************************************
	module		:[指定されたコマンドが同報コマンドか調べる]
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
	date		:[1996/01/22]
	author		:[江口,松隈,渡辺一章]
*************************************************************************/
UBYTE CheckBroadCastCommand(void)
{
	UBYTE	number;
	UBYTE	status;
	UBYTE	loop;
	UBYTE	counter;
#if (PRO_CONTINUOUS_POLLING == ENABLE)
	UBYTE	kind;
#endif
	struct	SYS_DialData_t *dp;

	/*現在参照しているコマンドが同報コマンドかどうか調べる */
	/* 返値 */
	/* FALSE :0 */
	/* OPR_EXEC_BROADCAST:1,キューに展開されている同報 */
	/* OPR_WAIT_BROADCAST:2,キューに展開されていない同報  */

#if (PRO_BATCH_TX == ENABLE)
	if (OPR_Buf.ReviewCtrl.CommandKind == SYS_BATCH_TX) {	/* 一括送信 */
		/* 一括送信の場合、同報はできない */
		return (FALSE);
	}
#endif

	number = OPR_Buf.ReviewCtrl.CommandPointer;
	counter = 0;
#if (PRO_CONTINUOUS_POLLING == ENABLE)
	kind = OPR_Buf.ReviewCtrl.CommandKind;	/* キューのkindと同じ*/
	if (kind == SYS_COMMAND_TRX) {
		status = CheckCommandBatchStatus(SYS_COMMAND_TRX, number);
	}
	else {	/* 連続ポーリング */
		status = CheckCommandBatchStatus(SYS_CONTINUOUS_POLLING, number);
	}
#else
	status = CheckCommandBatchStatus(SYS_COMMAND_TRX, number);
#endif

	if (status == SYS_CMD_EXECUTE) {		/* キューに展開されている */
		/* キューに展開されている数を求める */
		for (loop = 0; loop < SYS_EXEC_QUEUE_MAX; loop++) {
#if (PRO_CONTINUOUS_POLLING == ENABLE)
			if (kind == SYS_COMMAND_TRX) {
				if ((CheckExecQueueBeforeStart(loop) == TRUE)
				 && (CheckExecKindNumber(SYS_COMMAND_TRX, number, loop) == OK)) {
					counter++;
				}
			}
			else {	/* 連続ポーリング */
				if ((CheckExecQueueBeforeStart(loop) == TRUE)
				 && (CheckExecKindNumber(SYS_CONTINUOUS_POLLING, number, loop) == OK)) {
					counter++;
				}
			}
#else
			if ((CheckExecQueueBeforeStart(loop) == TRUE)
			 && (CheckExecKindNumber(SYS_COMMAND_TRX, number, loop) == OK)) {
				counter++;
			}
#endif
			if (counter > 1) {
				return (OPR_EXEC_BROADCAST);
			}
		}
	}
	else if (status == SYS_CMD_WAITING) {	/*予約中 */
#if (PRO_CONTINUOUS_POLLING == ENABLE)
		if (kind == SYS_COMMAND_TRX) {
			dp = &SYB_CommandFile[number].DialNumber;
		}
		else {	/* 連続ポーリング */
			dp = &SYB_ContinuousPolling.DialNumber;
		}
#else
		dp = &SYB_CommandFile[number].DialNumber;
#endif
		for (loop = 0; loop < SYS_ONETOUCH_MAX; loop++) {			/* ワンタッチダイヤル */
			if (CMN_CheckBitAssign(dp->Onetouch, loop) == TRUE) {
				counter++;
			}
		}

		for (loop = 0; loop < SYS_SPEED_DIAL_MAX; loop++) {			/* 短縮ダイヤル */
			if (CMN_CheckBitAssign(dp->Speed, loop) == TRUE) {
				counter++;
			}
		}

		for (loop = 0; loop < SYS_COM_DIRECT_DIAL_MAX; loop++) {	/* 直接ダイヤル */
			if ((dp->Direct[loop][0] & 0xF0) != 0xF0) {
				counter++;
			}
		}

		for (loop = 0; loop < SYS_GROUP_NUMBER_MAX; loop++) {		/* グループ */
			if (CMN_CheckLongBitAssign(dp->Group, loop) == TRUE) {
				counter++;
			}
		}
		if (counter > 1) {
			return (OPR_WAIT_BROADCAST);
		}
	}
	return (FALSE);
}

/*************************************************************************
	module		:[実行キューを指すポインターの初期化]
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
	date		:[1996/01/22]
	author		:[江口,松隈,渡辺一章]
*************************************************************************/
void ResetExecPointer(void)
{
	/* 同報コマンドのコマンド単位の消去確認モードから同報の宛先単位の消去確認モードに移行した時に実行される */
	/* 上記以外の時には実行されない -> したらあかん */
	/* 既にコマンドがキューに展開されている時はExecQueue[]の配列オフセット値がセットされる */
	/* 予約中のコマンドの場合、DialNumber[]の配列オフセット値がセットされる */

	UBYTE	number;
	UBYTE	loop;
	UBYTE	review_mode;
#if (PRO_CONTINUOUS_POLLING == ENABLE)
	UBYTE	kind;
#endif
	UBYTE	is_item_set;	/* 97/03/21 */
	struct	SYS_DialData_t *dp;	/* 97/03/21 */

	number = OPR_Buf.ReviewCtrl.CommandPointer;
	review_mode = CheckCommandReviewMode();
#if (PRO_CONTINUOUS_POLLING == ENABLE)
	kind = OPR_Buf.ReviewCtrl.CommandKind;
#endif

	if (review_mode == OPR_EXEC_REVIEW) { /* キューに展開済みのコマンドの場合 */
#if (PRO_CONTINUOUS_POLLING == ENABLE)
		if (kind == SYS_COMMAND_TRX) {
			if ((loop = CheckExecuteCommand(SYS_COMMAND_TRX, number)) < SYS_EXEC_QUEUE_MAX) {
				/* 対応するキューが実行中の場合 */
				/* キューをセットする 			*/
				OPR_Buf.ReviewCtrl.ExecPointer = loop;
			}
			else { /*実行中のコマンドはない*/
				/* ExecQueueを先頭からサーチして、対象のコマンドに対応するキューを検索し、その配列オフセットをセット */
				if ((loop = SearchExecQueue(SYS_COMMAND_TRX, number)) < SYS_EXEC_QUEUE_MAX) {
					OPR_Buf.ReviewCtrl.ExecPointer = loop;
				}
			}
		}
		else {	/* 連続ポーリング */
			if ((loop = CheckExecuteCommand(SYS_CONTINUOUS_POLLING, number)) < SYS_EXEC_QUEUE_MAX) {
				/* 対応するキューが実行中の場合 */
				/* キューをセットする 			*/
				OPR_Buf.ReviewCtrl.ExecPointer = loop;
			}
			else { /*実行中のコマンドはない*/
				/* ExecQueueを先頭からサーチして、対象のコマンドに対応するキューを検索し、その配列オフセットをセット */
				if ((loop = SearchExecQueue(SYS_CONTINUOUS_POLLING, number)) < SYS_EXEC_QUEUE_MAX) {
					OPR_Buf.ReviewCtrl.ExecPointer = loop;
				}
			}
		}
#else
		if ((loop = CheckExecuteCommand(SYS_COMMAND_TRX, number)) < SYS_EXEC_QUEUE_MAX) {
			/* 対応するキューが実行中の場合 */
			/* キューをセットする 			*/
			OPR_Buf.ReviewCtrl.ExecPointer = loop;
		}
		else { /*実行中のコマンドはない*/
			/* ExecQueueを先頭からサーチして、対象のコマンドに対応するキューを検索し、その配列オフセットをセット */
			if ((loop = SearchExecQueue(SYS_COMMAND_TRX, number)) < SYS_EXEC_QUEUE_MAX) {
				OPR_Buf.ReviewCtrl.ExecPointer = loop;
			}
		}
#endif	/* (PRO_CONTINUOUS_POLLING == ENABLE) */
	}
	else if (review_mode == OPR_COM_DIAL_REVIEW) { /* キューに展開されていないコマンドの場合 */
#if (PRO_CONTINUOUS_POLLING == ENABLE)	/* 追加 98/01/27 T.Fukumoto */
		if (kind == SYS_COMMAND_TRX) {
			dp = &SYB_CommandFile[number].DialNumber;
		}
		else {	/* 連続ポーリング */
			dp = &SYB_ContinuousPolling.DialNumber;
		}
#else
		dp = &SYB_CommandFile[number].DialNumber;
#endif
		/* コマンドのダイアル番号の配列をサーチする */
		is_item_set	= FALSE;
		for (loop = 0; loop < SYS_ONETOUCH_MAX; loop++) {			/* ワンタッチダイヤル */
			if (CMN_CheckBitAssign(dp->Onetouch, loop) == TRUE) {
				OPR_Buf.ReviewCtrl.ExecPointer = loop;
				OPR_Buf.ReviewCtrl.ExecItem = SYS_ONETOUCH_DIAL;
				is_item_set = TRUE;
				break;
			}
		}

		if( is_item_set == FALSE ){
			for (loop = 0; loop < SYS_SPEED_DIAL_MAX; loop++) {			/* 短縮ダイヤル */
				if (CMN_CheckBitAssign(dp->Speed, loop) == TRUE) {
					OPR_Buf.ReviewCtrl.ExecPointer = loop;
					OPR_Buf.ReviewCtrl.ExecItem = SYS_SPEED_DIAL;
					is_item_set = TRUE;
					break;
				}
			}
		}

		if( is_item_set == FALSE ){
			for (loop = 0; loop < SYS_GROUP_NUMBER_MAX; loop++) {		/* グループ */
				if (CMN_CheckLongBitAssign(dp->Group, loop) == TRUE) {
					OPR_Buf.ReviewCtrl.ExecPointer = loop;
					OPR_Buf.ReviewCtrl.ExecItem = SYS_GROUP_DIAL;
					is_item_set = TRUE;
					break;
				}
			}
		}

		if( is_item_set == FALSE ){
			for (loop = 0; loop < SYS_COM_DIRECT_DIAL_MAX; loop++) {	/* 直接ダイヤル */
				if ((dp->Direct[loop][0] & 0xF0) != 0xF0) {
					OPR_Buf.ReviewCtrl.ExecPointer = loop;
					OPR_Buf.ReviewCtrl.ExecItem = SYS_DIRECT_DIAL;
					is_item_set = TRUE;
					break;
				}
			}
		}
	}
}

/*************************************************************************
	module		:[実行キューを指すポインターを更新]
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
	date		:[1996/01/22]
	author		:[江口,松隈,渡辺一章]
*************************************************************************/
UBYTE SetExecPointer(UBYTE mode)
{
	UBYTE	review_mode;
	UBYTE	number;
	UBYTE	kind;
	UBYTE	exec_item;		/* 97/03/21 */
	UBYTE	exec_pointer;
	UBYTE	exec_loop;
	UWORD	loop;
	UWORD	loop_count_max;
	struct	SYS_DialData_t *dp;	/* 97/03/21 */

	review_mode = CheckCommandReviewMode();
	exec_pointer = OPR_Buf.ReviewCtrl.ExecPointer;
	exec_item = OPR_Buf.ReviewCtrl.ExecItem;
	kind = OPR_Buf.ReviewCtrl.CommandKind;	/* キューのkindと同じ*/
	number = OPR_Buf.ReviewCtrl.CommandPointer;

	if (review_mode == OPR_EXEC_REVIEW) {	/** 実行キューを参照中　*/
		loop_count_max = SYS_EXEC_QUEUE_MAX;
		exec_loop	= SYS_EXEC_QUEUE_MAX;
		exec_pointer++; /** 参照位置を進める */
		if (exec_pointer >= exec_loop) {
			/** すすめすぎたらもどす */
			exec_pointer = 0;
		}
	}
	else { /** コマンドファイルのダイアルナンバーを参照中 */
		loop_count_max = SYS_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX + SYS_GROUP_NUMBER_MAX + SYS_COM_DIRECT_DIAL_MAX;
		switch(exec_item) {
		case SYS_ONETOUCH_DIAL:
			exec_loop = SYS_ONETOUCH_MAX;
			break;
		case SYS_SPEED_DIAL:
			exec_loop = SYS_SPEED_DIAL_MAX;
			break;
		case SYS_GROUP_DIAL:
			exec_loop = SYS_GROUP_NUMBER_MAX;
			break;
		case SYS_DIRECT_DIAL:
			exec_loop = SYS_COM_DIRECT_DIAL_MAX;
			break;
		}
		exec_pointer++; /** 参照位置を進める */
		if (exec_pointer >= exec_loop) {
			/** すすめすぎたらもどす */
			exec_pointer = 0;
			switch(exec_item) {
			case SYS_ONETOUCH_DIAL:
				exec_loop = SYS_SPEED_DIAL_MAX;
				exec_item = SYS_SPEED_DIAL;
				break;
			case SYS_SPEED_DIAL:
				exec_loop = SYS_GROUP_NUMBER_MAX;
				exec_item = SYS_GROUP_DIAL;
				break;
			case SYS_GROUP_DIAL:
				exec_loop = SYS_COM_DIRECT_DIAL_MAX;
				exec_item = SYS_DIRECT_DIAL;
				break;
			case SYS_DIRECT_DIAL:
				exec_loop = SYS_ONETOUCH_MAX;
				exec_item = SYS_ONETOUCH_DIAL;
				break;
			}
		}
	}

	for (loop = 0 ; loop < loop_count_max; loop++) {
		if (review_mode == OPR_EXEC_REVIEW) {
			if ((CheckExecQueueBeforeStart(exec_pointer) == TRUE)			/** 実行中か実行待ちのキューである */
			 && (CheckExecKindNumber(kind, number, exec_pointer) == OK)) {	/** 同一コマンドに対するキューである */
				/** 検索終了 */
				break;
			}
			exec_pointer++;			/* 97/03/21 */
			if (exec_pointer >= exec_loop) {
				exec_pointer = 0;
			}
		}
		else { /** コマンドのダイアル番号を参照中　*/
#if (PRO_CONTINUOUS_POLLING == ENABLE)
			if (kind == SYS_COMMAND_TRX) {
				dp	= &SYB_CommandFile[number].DialNumber;
			}
			else {	/* 連続ポーリング */
				dp	= &SYB_ContinuousPolling.DialNumber;
			}
#else
			dp	= &SYB_CommandFile[number].DialNumber;
#endif
			if( exec_item == SYS_ONETOUCH_DIAL ){
				if (CMN_CheckBitAssign(dp->Onetouch, exec_pointer) == TRUE) {
					break;
				}
			}
			if( exec_item == SYS_SPEED_DIAL){
				if (CMN_CheckBitAssign(dp->Speed, exec_pointer) == TRUE) {
					break;
				}
			}
			if( exec_item == SYS_GROUP_DIAL ){
				if (CMN_CheckLongBitAssign(dp->Group, exec_pointer) == TRUE) {
					break;
				}
			}
			if( exec_item == SYS_DIRECT_DIAL ){
				if ((dp->Direct[exec_pointer][0] & 0xF0) != 0xF0) {
					break;
				}
			}

			exec_pointer++;
			if (exec_pointer >= exec_loop) {
				switch(exec_item) {
				case SYS_ONETOUCH_DIAL:
					exec_item = SYS_SPEED_DIAL;
					exec_loop = SYS_SPEED_DIAL_MAX;
					exec_pointer = 0;
					break;
				case SYS_SPEED_DIAL:
					exec_item = SYS_GROUP_DIAL;
					exec_loop = SYS_GROUP_NUMBER_MAX;
					exec_pointer = 0;
					break;
				case SYS_GROUP_DIAL:
					exec_item = SYS_DIRECT_DIAL;
					exec_loop = SYS_COM_DIRECT_DIAL_MAX;
					exec_pointer = 0;
					break;
				case SYS_DIRECT_DIAL:
					exec_item = SYS_ONETOUCH_DIAL;
					exec_loop = SYS_ONETOUCH_MAX;
					exec_pointer = 0;
					break;
				}
			}
		}
	}
	if (loop >= loop_count_max) {
		/*指定されたコマンドに対するキューがない */
		/*スクロールしていく内に全てのキューが実行終了した場合あるいはすべてのキューが消去されて場合
		　などがここにくる */
		/*宛先単位の消去確認モードを抜けて、コマンド単位の消去確認モードに移行 */
		/*エラーメッセージをどうするか  */
		OPR_Buf.ReviewCtrl.ReviewMode = OPR_COMMAND_REVIEW;
		return (SetCommandPointer(mode));
	}
	else if ((exec_pointer == OPR_Buf.ReviewCtrl.ExecPointer) && (exec_item == OPR_Buf.ReviewCtrl.ExecItem)) {
		/* 前回参照していたもの以外にない */
		NackBuzzer();
		OPR_ChildErrorFlag = NO_COMMAND_ERROR;
		return (OPR_CONTINUE);
	}
	else { /* キューあり */
		OPR_Buf.ReviewCtrl.ExecPointer = exec_pointer;
		OPR_Buf.ReviewCtrl.ExecItem = exec_item;
		return (OPR_CONTINUE);
	}
}

/*************************************************************************
	module		:[同報キーが押された時の処理]
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
	date		:[1996/01/22]
	author		:[江口,渡辺一章]
*************************************************************************/
void ChangeCommandReviewMode(void)
{
	/*--------------------------------------------------*/
	/* 同報キーがおされた時に実行される				  	*/
	/* 現在のコマンド確認消去モードにより処理を行う		*/
	/* 1.コマンド単位の確認消去コマンドの場合			*/
	/*   現在参照しているコマンドが同報コマンドの場合   */
	/*	 コマンド確認消去モードを同報の各宛先単位の		*/
	/*	 確認消去モードにセットする   					*/
	/*   同報コマンドじゃない場合は無効(Nack)			*/
	/* 2.同報の各宛先単位の確認消去尾モードの場合		*/
	/*   コマンド単位の確認消去モードにセットする。		*/
	/*--------------------------------------------------*/
	switch (CheckCommandReviewMode()) {
	case OPR_COMMAND_REVIEW:	/* コマンド単位の確認消去モード */
		/* 同報コマンドであれば、下の階層（同報の宛先単位の消去確認モード）に移行 */
		switch (CheckBroadCastCommand()) {
		case OPR_EXEC_BROADCAST:	/* 同報コマンドでかつキューに展開されている */
			OPR_Buf.ReviewCtrl.ReviewMode = OPR_EXEC_REVIEW;
			break;
		case OPR_WAIT_BROADCAST:	/* 同報コマンドで、キューには展開されていない */
			OPR_Buf.ReviewCtrl.ReviewMode = OPR_COM_DIAL_REVIEW;
			break;
		default:
			NackBuzzer();
			break;
		}
		break;
	case OPR_EXEC_REVIEW:		/* 同報の宛先単位の確認消去モード(キューに展開済み) */
	case OPR_COM_DIAL_REVIEW:	/* 同報の宛先単位の確認消去モード(キューに未展開) 	*/
		/* 上位の階層に移行 */
		OPR_Buf.ReviewCtrl.ReviewMode = OPR_COMMAND_REVIEW;
		break;
	default:
		break;
	}

	if (CheckCommandReviewMode() != OPR_COMMAND_REVIEW) {	/* 下の階層に移行した場合 */
		ResetExecPointer();		/* キューの参照位置を初期化 */
	}
}

/*************************************************************************
	module		:[コマンドの状態を調べる]
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
	date		:[1996/01/22]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE CheckCommandBatchStatus(UBYTE kind, UBYTE number)
{
	UBYTE	status;

	switch (kind) {
	case SYS_COMMAND_TRX:
		status = SYB_CommandFile[number].Status;
		break;

#if (PRO_BATCH_TX == ENABLE)
	case SYS_BATCH_TX:
		status = SYB_BatchTxFile[number].Status;
		break;
#endif

#if (PRO_CONTINUOUS_POLLING == ENABLE)
	case SYS_CONTINUOUS_POLLING:
		status = SYB_ContinuousPolling.Status;
		break;
#endif

	default:
		break;
	}

	if (status == SYS_CMD_EXECUTE) {	/* 実行中（キューに展開されている） */
		if (SearchExecQueue(kind, number) < SYS_EXEC_QUEUE_MAX) {	/* 実行中か又は実行まち */
			status = SYS_CMD_EXECUTE;
		}
		else {	/* 実行中、実行待ち以外ー＞対象外とする */
			status = SYS_CMD_EMPTY;
		}
	}
	return (status);
}

/*************************************************************************
	module		:[表示]
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
	date		:[1996/01/22]
	author		:[江口,松隈,渡辺一章]
*************************************************************************/
void DisplayReviewCommand(void)
{
	/* 上段表示 */
	/* コマンド番号とコマンドの内容（ダイアル番号を表示) */
	/* 同報の場合、ワンタッチ・短縮を優先的に表示していく */
	/* 通常のコマンドと一括送信のコマンドはコマンド番号の前にコマンドはＣ、*/
	/* 一括送信はＢをつけることにより区別する*/
	/* 同報コマンドの場合は、相手先名を表示せずに、Broadcastと表示しておく  */
	/* -> ダイレクトダイアルと同報が区別できない場合がある					*/

	UBYTE	dial_number;
	UBYTE	item;
	UBYTE	kind;					/* コマンド種別 */
	UBYTE	number;					/* コマンド番号 */
	UBYTE	exec_file;
	UBYTE	onetouch;
	struct	SYS_DialData_t *dp;
	struct	SYS_BatchTxDialData_t *bdp;
	struct	SYS_ExecDialData_t *edp;
	UBYTE	exec_pointer;
	UBYTE	exec_item;

	if (CheckChildErrorDisplayReq() == TRUE) {
		DisplayChildError();
		return;
	}

	if (CheckChildDisplay() == TRUE) {
		return;
	}

	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');

	switch (CheckCommandReviewMode()) {
	case OPR_COMMAND_REVIEW:/* コマンド単位の確認・消去モード *//* コマンドファイル・一括送信ファイルを参照している*/
		number = OPR_Buf.ReviewCtrl.CommandPointer;
		kind = OPR_Buf.ReviewCtrl.CommandKind;

		switch (kind) {
		case SYS_COMMAND_TRX:
#if (PRO_OKI == ENABLE)	/* 海外では短縮等の頭文字が英語と違うので、変更できるようにします by K.Watanabe 1999/02/09 */
			FunctionDisplayBufferHigh[0] = *CalculateStringAddress(&D2W_HeadCharacter_Command);
#else
			FunctionDisplayBufferHigh[0] = 'C';
#endif
			CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[1], (UWORD)number, 2, '0');
			break;
#if (PRO_BATCH_TX == ENABLE)
		case SYS_BATCH_TX:
 #if (PRO_OKI == ENABLE)	/* 海外では短縮等の頭文字が英語と違うので、変更できるようにします by K.Watanabe 1999/02/09 */
			FunctionDisplayBufferHigh[0] = *CalculateStringAddress(&D2W_HeadCharacter_Batch);
 #else
			FunctionDisplayBufferHigh[0] = 'B';
 #endif
			CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[1], (UWORD)(number + OPR_BATCH_FILE_MIN), 2, '0');
			break;
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE)
		case SYS_CONTINUOUS_POLLING:
 #if (PRO_OKI == ENABLE)	/* 海外では短縮等の頭文字が英語と違うので、変更できるようにします by K.Watanabe 1999/02/09 */
			FunctionDisplayBufferHigh[0] = *CalculateStringAddress(&D2W_HeadCharacter_Polling);
 #else
			FunctionDisplayBufferHigh[0] = 'P';
 #endif
			CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[1], (UWORD)number, 2, '0');
			break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		/**************************
		** メールコマンドの場合
		**************************/
		case SYS_INF_MAIL_TX_CMD:
				FunctionDisplayBufferHigh[0] = 'T';
				CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[1], (UWORD)number, 2, '0');
				break;
		case SYS_INF_MAIL_RX_CMD:
				FunctionDisplayBufferHigh[0] = 'R';
				CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[1], (UWORD)number, 2, '0');
				break;
#endif
		default:
			break;
		}

		FunctionDisplayBufferHigh[3] = ':';

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		if ((kind == SYS_INF_MAIL_TX_CMD)	/** メール送信コマンド */
		||	(kind == SYS_INF_MAIL_NO_CMD)) {/* メールコマンドが無い状態でここに来るはずはないが念のため */
			CMN_StringCopyNum(	&FunctionDisplayBufferHigh[4],
								&OPR_Buf.ReviewCtrl.InputBuffer[0],
								(OPR_DISPLAY_MAX-4));
		}
		else if (kind == SYS_INF_MAIL_RX_CMD) {	/** メール受信コマンド */
				CMN_StringCopyNum(	&FunctionDisplayBufferHigh[4],
									&OPR_Buf.ReviewCtrl.UserNameOrID[0],
									(OPR_DISPLAY_MAX-4));
		}
		else {
			if (CheckBroadCastCommand() != FALSE) {	/* 同報の場合 */
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[4], D2W_SF_Broadcast, 16);
			}
			else {									/* 同報でない場合 */
				switch (CheckCommandBatchStatus(kind, number)) {
				case SYS_CMD_EXECUTE:	/* キューに展開されている */
					exec_file = SearchExecQueue(kind , number);
					edp = &SYB_ExecQueue[exec_file].ExecDial;

					switch (edp->Item) {
					case SYS_ONETOUCH_DIAL:
						onetouch = CMN_OffsetToOnetouchCode(edp->ExecNumber.Onetouch);
						SetOnetouchCode(&FunctionDisplayBufferHigh[4], onetouch, OPR_SET_ONETOUCH_CODE);
						break;

					case SYS_SPEED_DIAL:
						DisplaySpeedDialSet( 4, edp->ExecNumber.Speed );
						break;

					case SYS_DIRECT_DIAL:
						switch (kind) {
						case SYS_COMMAND_TRX:
							dp = &SYB_CommandFile[number].DialNumber;
							break;
 #if (PRO_BATCH_TX == ENABLE)
						case SYS_BATCH_TX:
							bdp = &SYB_BatchTxFile[number].DialNumber[0];
							break;
 #endif
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
						case SYS_CONTINUOUS_POLLING:
							dp = &SYB_ContinuousPolling.DialNumber;
							break;
 #endif
						default:
							break;
						}

						if( kind == SYS_BATCH_TX ){		/* 一括送信の時	97/03/21 */
							CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferHigh[4], &bdp->FaxNumber.Direct[0], 16);
						}else{
							CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferHigh[4], &dp->Direct[edp->ExecNumber.Command][0], 16);
						}
						break;
					}
					break;
				case SYS_CMD_WAITING:	/* 予約中 */
					switch (kind) {
					case SYS_COMMAND_TRX:
						dp = &SYB_CommandFile[number].DialNumber;
						break;
 #if (PRO_BATCH_TX == ENABLE)
					case SYS_BATCH_TX:
						bdp = &SYB_BatchTxFile[number].DialNumber[0];
						break;
 #endif
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
					case SYS_CONTINUOUS_POLLING:
						dp = &SYB_ContinuousPolling.DialNumber;
						break;
 #endif
					default:
						break;
					}

					if( kind == SYS_BATCH_TX ){	/* 一括送信 */
						switch (bdp->Item){	
						case SYS_ONETOUCH_DIAL:
							onetouch = CMN_OffsetToOnetouchCode(bdp->FaxNumber.Onetouch);
							SetOnetouchCode(&FunctionDisplayBufferHigh[4], onetouch, OPR_SET_ONETOUCH_CODE);
							break;
						case SYS_SPEED_DIAL:
							DisplaySpeedDialSet( 4, bdp->FaxNumber.Speed );
							break;
						case SYS_DIRECT_DIAL:
							CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferHigh[4], &bdp->FaxNumber.Direct[0], 16);
							break;
						case SYS_GROUP_DIAL:
							FunctionDisplayBufferHigh[4] = OPR_GROUP_MARK;
							CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[5], bdp->FaxNumber.Group, GROUP_FIGURE_MAX,'0');
							break;
						}
					}
					else {	/* 一括送信以外 */
						item	= SYS_ONETOUCH_DIAL;
						dial_number	= 0;
						if (SearchDialData( dp, &item, &dial_number ) == FALSE) {
							break;
						}
						switch( item ){
						case	SYS_ONETOUCH_DIAL:		/* ワンタッチダイヤル */
							onetouch = CMN_OffsetToOnetouchCode(dial_number);
							SetOnetouchCode(&FunctionDisplayBufferHigh[4], onetouch, OPR_SET_ONETOUCH_CODE);
							break;
						case	SYS_SPEED_DIAL:			/* 短縮ダイヤル */
							DisplaySpeedDialSet( 4, dial_number );
							break;
						case	SYS_GROUP_DIAL:			/* グループダイヤル */
							FunctionDisplayBufferHigh[4] = OPR_GROUP_MARK;
							CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[5], dial_number+1, GROUP_FIGURE_MAX, '0');
							break;
						case	SYS_DIRECT_DIAL:		/* 直接ダイヤル */
							CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferHigh[4], &dp->Direct[dial_number][0], 16);
							break;
						}
					}
					break;
				default:
					break;
				}
			}
		}
#else
		if (CheckBroadCastCommand() != FALSE) {	/* 同報の場合 */
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferHigh[4], D2W_SF_Broadcast, 16);
		}
		else {									/* 同報でない場合 */
			switch (CheckCommandBatchStatus(kind, number)) {
			case SYS_CMD_EXECUTE:	/* キューに展開されている */
				exec_file = SearchExecQueue(kind , number);
				edp = &SYB_ExecQueue[exec_file].ExecDial;

				switch (edp->Item) {
				case SYS_ONETOUCH_DIAL:
					onetouch = CMN_OffsetToOnetouchCode(edp->ExecNumber.Onetouch);
					SetOnetouchCode(&FunctionDisplayBufferHigh[4], onetouch, OPR_SET_ONETOUCH_CODE);
					break;

				case SYS_SPEED_DIAL:
					DisplaySpeedDialSet( 4, edp->ExecNumber.Speed );
					break;

				case SYS_DIRECT_DIAL:
					switch (kind) {
					case SYS_COMMAND_TRX:
						dp = &SYB_CommandFile[number].DialNumber;
						break;
 #if (PRO_BATCH_TX == ENABLE)
					case SYS_BATCH_TX:
						bdp = &SYB_BatchTxFile[number].DialNumber[0];
						break;
 #endif
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
					case SYS_CONTINUOUS_POLLING:
						dp = &SYB_ContinuousPolling.DialNumber;
						break;
 #endif
					default:
						break;
					}

					if( kind == SYS_BATCH_TX ){		/* 一括送信の時	97/03/21 */
						CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferHigh[4], &bdp->FaxNumber.Direct[0], 16);
					}else{
						CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferHigh[4], &dp->Direct[edp->ExecNumber.Command][0], 16);
					}
					break;
				}
				break;
			case SYS_CMD_WAITING:	/* 予約中 */
				switch (kind) {
				case SYS_COMMAND_TRX:
					dp = &SYB_CommandFile[number].DialNumber;
					break;
 #if (PRO_BATCH_TX == ENABLE)
				case SYS_BATCH_TX:
					bdp = &SYB_BatchTxFile[number].DialNumber[0];
					break;
 #endif
 #if (PRO_CONTINUOUS_POLLING == ENABLE)
				case SYS_CONTINUOUS_POLLING:
					dp = &SYB_ContinuousPolling.DialNumber;
					break;
 #endif
				default:
					break;
				}

				if( kind == SYS_BATCH_TX ){	/* 一括送信 */
					switch (bdp->Item){	
					case SYS_ONETOUCH_DIAL:
						onetouch = CMN_OffsetToOnetouchCode(bdp->FaxNumber.Onetouch);
						SetOnetouchCode(&FunctionDisplayBufferHigh[4], onetouch, OPR_SET_ONETOUCH_CODE);
						break;
					case SYS_SPEED_DIAL:
						DisplaySpeedDialSet( 4, bdp->FaxNumber.Speed );
						break;
					case SYS_DIRECT_DIAL:
						CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferHigh[4], &bdp->FaxNumber.Direct[0], 16);
						break;
					case SYS_GROUP_DIAL:
						FunctionDisplayBufferHigh[4] = OPR_GROUP_MARK;
						CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[5], bdp->FaxNumber.Group, GROUP_FIGURE_MAX,'0');						break;
					}
				}
				else {	/* 一括送信以外 */
					item	= SYS_ONETOUCH_DIAL;
					dial_number	= 0;
					if (SearchDialData( dp, &item, &dial_number ) == FALSE) {
						break;
					}
					switch( item ){
					case	SYS_ONETOUCH_DIAL:		/* ワンタッチダイヤル */
						onetouch = CMN_OffsetToOnetouchCode(dial_number);
						SetOnetouchCode(&FunctionDisplayBufferHigh[4], onetouch, OPR_SET_ONETOUCH_CODE);
						break;
					case	SYS_SPEED_DIAL:			/* 短縮ダイヤル */
						DisplaySpeedDialSet( 4, dial_number );
						break;
					case	SYS_GROUP_DIAL:			/* グループダイヤル */
						FunctionDisplayBufferHigh[4] = OPR_GROUP_MARK;
						CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[5], dial_number+1, GROUP_FIGURE_MAX, '0');
						break;
					case	SYS_DIRECT_DIAL:		/* 直接ダイヤル */
						CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferHigh[4], &dp->Direct[dial_number][0], 16);
						break;
					}
				}
				break;
			default:
				break;
			}
		}
#endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/12 by K.Okada */
		break;
	case OPR_EXEC_REVIEW:	/* 同報の宛先ごとの確認消去モード（キューに展開されている )*/
		edp = &SYB_ExecQueue[OPR_Buf.ReviewCtrl.ExecPointer].ExecDial;
		switch (edp->Item) {
		case SYS_ONETOUCH_DIAL:
			onetouch = CMN_OffsetToOnetouchCode(edp->ExecNumber.Onetouch);
			SetOnetouchCode(&FunctionDisplayBufferHigh[0], onetouch, OPR_SET_ONETOUCH_CODE);
			break;

		case SYS_SPEED_DIAL:
			DisplaySpeedDialSet( 0, edp->ExecNumber.Speed );
			break;

		case SYS_DIRECT_DIAL:
#if (PRO_CONTINUOUS_POLLING == ENABLE)
			if (OPR_Buf.ReviewCtrl.CommandKind == SYS_COMMAND_TRX) {
				dp = &SYB_CommandFile[SYB_ExecQueue[OPR_Buf.ReviewCtrl.ExecPointer].Number.Command].DialNumber;
			}
			else {
				dp = &SYB_ContinuousPolling.DialNumber;
			}
#else
			dp = &SYB_CommandFile[SYB_ExecQueue[OPR_Buf.ReviewCtrl.ExecPointer].Number.Command].DialNumber;
#endif
			CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferHigh[0],
									&dp->Direct[edp->ExecNumber.Command][0],
									OPR_DISPLAY_MAX);
			break;
		}
		break;
	case OPR_COM_DIAL_REVIEW:/* 同報の宛先ごとの確認消去モード（キューに展開されてない )*/
		number = OPR_Buf.ReviewCtrl.CommandPointer;
		exec_pointer = OPR_Buf.ReviewCtrl.ExecPointer;	/* 97/03/21 */
		exec_item = OPR_Buf.ReviewCtrl.ExecItem;		/* 97/03/21 */
#if (PRO_CONTINUOUS_POLLING == ENABLE)
		if (OPR_Buf.ReviewCtrl.CommandKind == SYS_COMMAND_TRX) {
			dp = &SYB_CommandFile[number].DialNumber;
		}
		else {
			dp = &SYB_ContinuousPolling.DialNumber;
		}
#else
		dp = &SYB_CommandFile[number].DialNumber;
#endif
		switch (exec_item) {
		case SYS_ONETOUCH_DIAL:
			onetouch = CMN_OffsetToOnetouchCode(exec_pointer);
			SetOnetouchCode(&FunctionDisplayBufferHigh[0], onetouch, OPR_SET_ONETOUCH_CODE);
			break;;
		case SYS_SPEED_DIAL:
			DisplaySpeedDialSet( 0, exec_pointer );
			break;
		case SYS_DIRECT_DIAL:
			CMN_BCD_ToASC_StringNum(FunctionDisplayBufferHigh, &dp->Direct[exec_pointer][0], OPR_DISPLAY_MAX);
			break;
		case SYS_GROUP_DIAL:
			FunctionDisplayBufferHigh[0] = OPR_GROUP_MARK;
			CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[1], exec_pointer+1, GROUP_FIGURE_MAX, '0');
			break;
		}
		break;
	default:
		break;
	}

#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P 2004/07/14 for prefix *//* by K.Watanabe 2004/11/12 */
	ChangeDisplayBuffer(FunctionDisplayBufferHigh);
#endif

	/* 上段表示 */
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	/* 下段点滅表示 */
	/* FlashDisplayStringLow(D2W_ReviewClear);	*//* "       ﾂｳｼﾝｶｸﾆﾝ/ｸﾘｱ " */
	FlashDisplayStringLow(D2W_ProgramClear);	  /* "            ｷﾉｳ/ｸﾘｱ "に変更  By S.Fukui Oct.1,1997 */
}

/*************************************************************************
	module		:[通信証状況確認オペレーション]
	function	:[
		1.
	]
	return		:[
		OPR_CHANGED_MODE :REVIEWキー押下時（次のモードに移行する為）
		OPR_CANCELED	 :STOPキー押下時、またはタイムオーバー時
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/28]
	author		:[江口,渡辺一章,福井]
*************************************************************************/
UBYTE SetCheckConfirmReport(void)
{
	UBYTE	status;
	UBYTE	report;
	UBYTE	ret;

	if (SYB_ConfirmationReportSwitch == NO_CONFIRMATION_REPORT) {
		status = FALSE;
	}
	else {
		status = TRUE;
	}
	ret = SelectData(D2W_ConfirmReport,	/* "ﾂｳｼﾝｼｮｳ        :    " */
					 D2W_Off2,			/* "                OFF " */
					 2,
					 &status,
					 TRUE,
					 REVIEW);

	if (ret == OPR_ENTERED) {
		if (status == TRUE) {	/* ONにセットされた時 */
			if (CTRY_RCR() && CHK_RCR_ON()) {	/* 機器設定の設定値が受領証の時 */
				report = RCR_REQUEST;
			}
			else {								/* 機器設定の設定値が送信証の時 */
				report = TCR_REQUEST;
			}
		}
		else {					/* OFFにセットされた時 */
			report = NO_CONFIRMATION_REPORT;
		}
		SYB_ConfirmationReportSwitch = report;
		return(OPR_CANCELED);	/* モード選択完了させる為 に OPR_CANCELEDを使用 */
	}
	
	return(ret);	/* OPR_CHANGED_MODE/OPR_CANCELED が戻り値 */
}

/*************************************************************************
	module		:[マルチ表示選択]
	function	:[
		1.
	]
	return		:[
		OPR_CHANGED_MODE :REVIEWキー押下時（次のモードに移行する為）
		OPR_CANCELED	 :STOPキー押下時、またはタイムオーバー時
    ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/01/21]
	author		:[松隈,福井]
*************************************************************************/
#if (PRO_MULTI_LINE == ENABLE)
UBYTE MultiDisplaySelect(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	line_max;
	UBYTE	disp_cnt;
	UBYTE	disp_inp;
	UBYTE	line[SYS_OPTION_BOARD_MAX];
	UBYTE	i;

	line_max = 0;
	disp_cnt = 0;

	if (OPT_GetMultiLinrNumber(0) != 0) {	/* ホストを見る */
		line[line_max] = 0;
	}
	for (i = 1; i < SYS_OPTION_BOARD_MAX; i++ ) {
		if (CHK_OptionLineExist(i) == 1) {	/* ライン数およびボードナンバーを検索 */
			line_max++;
			line[line_max] = i;
		}
	}

	while (1) {
		/* 状態表示 */
		MultiOverWriteDisplayData(line[disp_cnt]);
		disp_inp = disp_cnt;	/* 表示のため待避 */
		disp_inp++;

		DisplayChar(17, '(');
		DisplayChar(18, ChangeNumberToASC_Code((UBYTE)disp_inp));
		DisplayChar(19, ')');

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case REVIEW:
			return(OPR_CHANGED_MODE);
		case STOP:			/* 停止キー */
		case KEY_TIME_UP:	/* １分間キー入力なし */
			return(OPR_CANCELED);
		case FUNCTION:
			if (disp_cnt == line_max) {
				disp_cnt = 0;
			}
			else {
				disp_cnt++;
			}
			break;
		case LEFT_ARROW:
			if (disp_cnt == 0) {
				disp_cnt = line_max;
			}
			else {
				disp_cnt--;
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
	module		:[マルチ表示用通信状態]
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
	date		:[1997/01/28]
	author		:[松隈]
*************************************************************************/
void MultiOverWriteDisplayData(UBYTE line_number)
{
	UBYTE	data;

	data = SYS_Display.SYS_FaxCommStage;/* データを待避する */

	/* ホスト */
	if (line_number == 0) {
		if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {	/** 通信中なら */
			OverWriteDisplayData(line_number);	/* 1997/06/11 Y.Matsukuma */
/*			SYS_Display.SYS_FaxCommStage = SYS_FaxCommStage;*/
		}
		else {
			DisplayIdle();
			return;
		}
	}
	/* オプションボード */
	else {
		if (CHK_OptionLineBusy(line_number)) {	/** 通信中なら */
			OverWriteDisplayData(line_number);	/* 1997/06/11 Y.Matsukuma */
/*			SYS_Display.SYS_FaxCommStage = SYS_Opt[line_number].SYS_FaxCommStage;*/
		}
		else {
			DisplayIdle();
			return;
		}
	}

	DisplayFaxCom();
	SYS_Display.SYS_FaxCommStage = data;	/* データを戻す */
}
#endif	/* (PRO_MULTI_LINE == ENABLE) */


/*************************************************************************
	module		:[短縮表示のセット]
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
	date		:[1997/09/24]
	author		:[桑原美紀]
*************************************************************************/
void	DisplaySpeedDialSet(
			UBYTE	Pos,				/* セット位置 */
			UWORD	SpeedNumber )		/* 短縮番号 */
{
	UWORD	option_number;	/* 任意短縮番号 */

	FunctionDisplayBufferHigh[Pos] = OPR_SPEED_MARK;
	if(CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮の時 */
		CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[Pos+1],
						 SpeedNumber + OPR_SPEED_DIAL_MIN,
						 SPEED_FIGURE_MAX,
						 '0');
	}
	else{		/* 任意短縮の時 */
		option_number = GetRecordFromNumber(SpeedNumber);
		if( option_number != 0xFFFF ){
			CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[Pos+1],
								 option_number,
								 SPEED_FIGURE_MAX,
								 '0');
		}
		else{
			CMN_MemorySet(&FunctionDisplayBufferHigh[Pos+1], SPEED_FIGURE_MAX, '*');
		}
	}
}


/*************************************************************************
	module		:[表示ダイヤル番号の検索]
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
	date		:[1997/09/24]
	author		:[桑原美紀]
*************************************************************************/
UBYTE	SearchDialData(
			struct SYS_DialData_t *Dial,/* ダイヤルデータ */
			UBYTE	*Item,				/* ダイヤル種別 */
			UBYTE	*Number)			/* ダイヤル */
{
	UBYTE	is_item_set;
	UBYTE	i;

	is_item_set = FALSE;

	while( is_item_set == FALSE ){
		switch( *Item ){
		case	SYS_ONETOUCH_DIAL:
			for (i = *Number; i < SYS_ONETOUCH_MAX; i++) {
				if (CMN_CheckBitAssign(Dial->Onetouch, i) == TRUE) {
					*Number	= i;
					is_item_set = TRUE;
					break;
				}
			}
			if (is_item_set == TRUE) {
				break;
			}
			*Item	= SYS_SPEED_DIAL;
			*Number	= 0;
			break;
		case	SYS_SPEED_DIAL:
			for (i = *Number; i < SYS_SPEED_DIAL_MAX; i++) {
				if (CMN_CheckBitAssign(Dial->Speed, i) == TRUE) {
					*Number	= i;
					is_item_set = TRUE;
					break;
				}
			}
			if (is_item_set == TRUE) {
				break;
			}
			*Item	= SYS_GROUP_DIAL;
			*Number	= 0;
			break;
		case	SYS_GROUP_DIAL:
			for (i = *Number; i < SYS_GROUP_NUMBER_MAX; i++) {
				if (CMN_CheckLongBitAssign(Dial->Group, i) == TRUE) {
					*Number	= i;
					is_item_set = TRUE;
					break;
				}
			}
			if (is_item_set == TRUE) {
				break;
			}
			*Item	= SYS_DIRECT_DIAL;
			*Number	= 0;
			break;
		case	SYS_DIRECT_DIAL:
			for (i = *Number; i < SYS_COM_DIRECT_DIAL_MAX; i++) {
				if ((Dial->Direct[i][0] & 0xF0) != 0xF0) {
					*Number	= i;
					is_item_set = TRUE;
					break;
				}
			}
			if ( is_item_set == TRUE ) {
				break;
			}
			return( FALSE );
		}
	}
	return( TRUE );
}

#if (0)  /* 通信予約消去／通信証メニュー表示する オリジナルソース保存 */
/*************************************************************************
//	module		:[通信確認オペレーション]
//	function	:[
//		1.通信待ち確認消去オペレーションと通信証状況確認オペレーションの選択を行う
//		2.通信確認キーで通信待ち確認消去オペレーションと通信証状況確認オペレーションを切り替え
//		3.セットキーでオペレーションの種類を選択して各オペレーションに分岐
//		4.ストップキー又はキー待ちタイムオーバーで終了
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[OPR]
//	date		:[1995/11/28]
//	author		:[江口,渡辺一章]
//*************************************************************************/
//void ReviewCommandOperation(void)
//{
//	UBYTE	key;
//	UBYTE	keytype;
//	UBYTE	type;		/* 0:予約確認 1:通信証セット */
//
//#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_HINOKI)
//	/* すぐに実行中のコマンドが消せるように、通信中止／確認キーが押された時に、
//	** 送信中のコマンドがあれば、メニュー選択を飛ばしていきなり通信確認オペレーションを
//	** 実行します（仕様変更） 97'09.02 by K.Watanabe
//	*/
//	if ((SYS_CurrentExecutingCommand->Status == SYS_EXEC_EXECUTE)				/* 通信中				*/
//	 || (SYS_CurrentExecutingCommand->Status == SYS_EXEC_FORWARD_EXECUTE)) {	/* 転送ダイヤル送信中	*/
//		ConfirmClearCommandOperation();	/* 予約確認オペレーション */
//		return;
//	}
//#endif
//
//	type = 0;
//
//	/* 下段点滅表示 */
//	FlashDisplayStringLow(D2W_ReviewEnter);	/* "       ﾂｳｼﾝｶｸﾆﾝ/ｾｯﾄ " */
//
//	while (1) {
//		/* 上段表示 */
//		/* "1 ﾂｳｼﾝﾖﾔｸ ｶｸﾆﾝ      " */
//		/* "2 ﾂｳｼﾝｼｮｳ ｼﾞｮｳｷｮｳ   " */
//		CMN_StringCopy(FunctionDisplayBufferHigh, (D2W_ConfirmCommandsMode + (OPR_WORDING_LEN * type)));
//		FunctionDisplayBufferHigh[0] = ChangeNumberToASC_Code((UBYTE)(type + 1));
//		DisplayStringHigh(0, FunctionDisplayBufferHigh);
//
//		/* キー取り込み */
//		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
//		key = GetInputKeyCode();
//		keytype = GetInputKeyType();
//
//		switch (keytype) {
//		case REVIEW:		/* 通信確認キー */
//#if (PRO_MULTI_LINE == DISABLE)
//			type ^= 0x01;
//#else
//			/* ユニットスイッチｉ３の０ビット目が立ってて、しかも回線が２つ以上あれば有効 */
//			if ((CHK_UNI_MultiDisplayEnable() != 0) && (OPT_CountModems() != 1)) {
//				if (type == 2) {
//					type = 0;
//				}
//				else {
//					type++;
//				}
//			}
//			else {
//				type ^= 0x01;
//			}
//#endif
//			break;
//		case STOP:			/* 停止キー */
//		case KEY_TIME_UP:	/* １分間キー入力なし */
//			return;
//		case ENTER:			/* セットキー */
//			/* 処理実行 */
//			switch (type) {
//			case 0:
//				ConfirmClearCommandOperation();	/* 予約確認オペレーション */
//				break;
//			case 1:
//				SetCheckConfirmReport();		/* 通信証状況確認オペレーション */
//				break;
//#if (PRO_MULTI_LINE == ENABLE)
//			case 2:
//				MultiDisplaySelect();			/* 回線ごとの状態表示選択 */
//				break;
//#endif
//			default:
//				break;
//			}
//			return;
//		case NO_EFFECT:
//			break;
//		default:
//			NackBuzzer();
//			break;
//		}
//	}
//}
//
///*************************************************************************
//	module		:[予約コマンド確認消去オペレーション]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[OPR]
//	date		:[1996/01/22]
//	author		:[江口,松隈,渡辺一章]
//*************************************************************************/
//UBYTE ConfirmClearCommandOperation(void)
//{
//	UBYTE	key;
//	UBYTE	keytype;
//	UBYTE	status;
//
//	/* 初期化 */
//	ClearReviewControlData();
//	status = OPR_CONTINUE;
//
//	/* 参照位置の初期設定 */
//	if (SetCommandPointer(COMMAND_REVIEW_MODE) == OPR_END) { /* コマンドがなにもない */
//		return;
//	}
//
//	/* 下段の点滅文字列の変更,及び点滅一時中断  */
//	DisplayStringLow(0, D2W_ReviewClear);
//
//	while (status != OPR_END) {
//		/* 表示 */
//		DisplayReviewCommand();
//
//		/** キー取り込み */
//		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
//		key = GetInputKeyCode();
//		keytype = GetInputKeyType();
//
//		switch (keytype) {
//		case REVIEW:	/* 通信確認キー */
//			if (CheckCommandReviewMode() == OPR_COMMAND_REVIEW) { /* コマンド単位の確認消去の場合 */
//				status = SetCommandPointer(COMMAND_REVIEW_MODE);
//			}
//			else { /*同報の宛先単位の消去モードの場合 */
//				status = SetExecPointer(COMMAND_REVIEW_MODE);
//			}
//			break;
//		case BROADCAST:
//			ChangeCommandReviewMode();
//			break;
//		case CLEAR:	/* クリアキー */
//			status = ConfirmKeyInputOperation(FunctionDisplayBufferHigh, D2W_CheckProgramClear, CLEAR, FUNCTION);
//			if (status == CONFIRM_EXEC) {
//				status = ClearReviewCommandData();	/* 消去実行 */
//			}
//			break;
//		case STOP:
//		case KEY_TIME_UP:
//			status = OPR_END;
//			break;
//		case NO_EFFECT:
//			break;
//		default:
//			NackBuzzer();
//			break;
//		}
//	}
//}
//
//*************************************************************************
//	module		:[通信証状況確認オペレーション]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[OPR]
//	date		:[1995/11/28]
//	author		:[江口,渡辺一章]
//*************************************************************************/
//UBYTE SetCheckConfirmReport(void)
//{
//	UBYTE	status;
//	UBYTE	report;
//
//	if (SYB_ConfirmationReportSwitch == NO_CONFIRMATION_REPORT) {
//		status = FALSE;
//	}
//	else {
//		status = TRUE;
//	}
//
//	if (SelectData(D2W_ConfirmReport,	/* "ﾂｳｼﾝｼｮｳ        :\0   " */
//				   D2W_Off2,			/* "                OFF " */
//				   2,
//				   &status,
//				   TRUE,
//				   NO_KEYTYPE) == OPR_ENTERED) {	/* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
//		if (status == TRUE) {	/* ONにセットされた時 */
//			if (CTRY_RCR() && CHK_RCR_ON()) {	/* 機器設定の設定値が受領証の時 */
//				report = RCR_REQUEST;
//			}
//			else {								/* 機器設定の設定値が送信証の時 */
//				report = TCR_REQUEST;
//			}
//		}
//		else {					/* OFFにセットされた時 */
//			report = NO_CONFIRMATION_REPORT;
//		}
//		SYB_ConfirmationReportSwitch = report;
//	}
//}
//
//
#endif	/* 通信予約消去／通信証メニュー表示する オリジナルソース保存 */


#if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* 通信結果表示 */
/*
// POPLAR_H2/SAKAKI2でも“PRO_COM_RESULT”というdefine名で
// 通信結果表示の条件コンパイルを入れています．
// しかし，SAKAKI2では「結果表示中にENTERを押すと表示している
// 通信結果をプリントする」機能を入れています．
// HINOKI2に結果表示のリストプリントは入れません．
// HINOKI2でそっちの名前を使ってしまうと，HINOKIとSAKAKIは
// 同じロール感熱紙でLSTのソースが共通なので，リストプリントの
// 条件が入ってきてしまいます．
// ゆえに，define名は別のままにします．
// 
// POPLAR_H2にはリストプリントは入っていませんが，こちらは
// 普通紙なので，ソースは条件で切り分けられています．
// by J.Kishida 2002/10/03
*/
/*************************************************************************
	module		:[予約確認キーオペレーション選択]
	function	:[
		1.以下の項目を順番にセットする。
		,予約確認
		,通信結果
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/09/20]
	author		:[近藤]
*************************************************************************/
UBYTE	SelectReviewCommandOperation(void)
{
	OPR_ReviewCommandOprNextStep = OPR_COMMUNICATION_RESULT;

	while (1) {
		switch (OPR_ReviewCommandOprNextStep) {
		case OPR_COMMAND_CONTINUE:				/* 予約確認続行		*/
#if (0)
			/*
			// AMSでは通信結果表示の次が予約確認だったので，途中で
			// 通信予約が実行されてコマンドが0になっていないか
			// 確認する必要がありました．
			// しかし，ATLANTAでは予約確認キーで送信証ON/OFFをセット
			// するので，通信結果表示の次は必ず送信証ON/OFFが来ます．
			// よって，通信予約を見に行く必要はありません．
			// by J.Kishida 2002/09/23
			*/
			//if (command == OPR_COMMAND) {
			//	/* 初期化 */
			//	ClearReviewControlData();
			//	/* 参照位置の初期設定 */
			//	if (SetCommandPointer(COMMAND_FIRST_REVIEW) == OPR_END) { /* コマンドがなにもない */
			//		NackBuzzer();
			//		/*OPR_ErrorWordingLow = D2W_NoCommand;*/
			//		DisplayStringLow(0, D2W_NoCommand);
			//		return(OPR_END);
			//	}
			//	return(OPR_CONTINUE);
			//}
			//else {
			//	return(OPR_CONTINUE);
			//}
#else
			return(OPR_CONTINUE);
#endif

		case OPR_COMMAND_END:					/* 予約確認終了		*/
			return(OPR_END);

#if (0)	/* 戻るキー無し by J.Kishida 2002/09/15 */
		//case OPR_COMMAND_BACK:					/* 予約確認戻る		*/
		//	return (OPR_END);
		//	break;
#endif
		case OPR_COMMUNICATION_RESULT:			/* 通信結果表示		*/
			SelectCommandResult();
			break;

		default:
			return(OPR_END);

		}
	}
}


/*************************************************************************
	module		:[通信結果移行オペレーション]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/08/30]
	author		:[近藤]
*************************************************************************/
UBYTE	SelectCommandResult(void)
{
	UBYTE	key;		/* 入力ｷｰﾃﾞｰﾀ */
	UBYTE	keytype;
	UBYTE	is_loop_end;

	key = OPR_NO_KEY;	/* 前回キー入力値用に初期化します */
	is_loop_end = FALSE;

	while (!is_loop_end) {

		/** 確認画面の表示 通信結果/予約 */
		DisplaySelectCommandResult();

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {	 /**入力キーによる処理*/
		case REVIEW:		/* 通信確認キー */
#if defined(STOCKHM2)	/* Mod by SMuratec C.P 2004/06/10 for V195 */
			NackBuzzer();
			break;
#else
			OPR_ReviewCommandOprNextStep = OPR_COMMAND_CONTINUE;	/* 予約確認続行		*/
			is_loop_end = TRUE;
			break;
#endif

#if defined(STOCKHM2)	/* Add by SMuratec C.P 2004/06/10 for V195 */
		case FUNCTION:	/* 右矢印キー */
		case LEFT_ARROW:		/* 左矢印キー */
			
			if (OPR_ReviewCommandOprNextStep == OPR_COMMUNICATION_RESULT){
				OPR_ReviewCommandOprNextStep = OPR_COMMAND_REVIEW_WAIT;
			}
			else{
				OPR_ReviewCommandOprNextStep = OPR_COMMUNICATION_RESULT;
			}
			break;
#endif

		case ENTER:					/**セットキー入力*/
#if defined(STOCKHM2) /* Mod by SMuratec C.P 2004/06/10 通信結果画面と予約確認画面のため */
			if (OPR_ReviewCommandOprNextStep == OPR_COMMUNICATION_RESULT){
				if(CommandResult() != OPR_CONTINUE) {
					OPR_ReviewCommandOprNextStep = OPR_COMMAND_END;	/* 通信結果表示終了	*/
					is_loop_end = TRUE;
				}
			}
			else{
				if(ConfirmClearCommandOperation() != OPR_CONTINUE) {
					OPR_ReviewCommandOprNextStep = OPR_COMMAND_END;	/* 予約確認終了		*/
					is_loop_end = TRUE;
				}
			}
#else
			/*if(CommandResult() != OPR_BACK) [*//* 戻るキー無し by J.Kishida 2002/09/15 */
			if(CommandResult() != OPR_CONTINUE) {
				OPR_ReviewCommandOprNextStep = OPR_COMMAND_END;	/* 予約確認終了		*/
				is_loop_end = TRUE;
			}
#endif
			break;

		case STOP:					/**ストップキー入力*/
		case KEY_TIME_UP:			/**キー待ちタイムオーバー*/
			OPR_ReviewCommandOprNextStep = OPR_COMMAND_END;	/* 予約確認終了		*/
			is_loop_end = TRUE;
			break;

#if (0)	/* 戻るキー無し by J.Kishida 2002/09/15 */
		//case BACK:					/* 戻るキー */
		//	OPR_ReviewCommandOprNextStep = OPR_COMMAND_BACK;	/* 予約確認戻る		*/
		//	is_loop_end = TRUE;
		//	break;
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
	module		:[通信結果移行オペレーション表示]
	function	:[
		1.
	]
	return		:[]
	common		:[
	]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/08/30]
	author		:[近藤]
*************************************************************************/
void	DisplaySelectCommandResult(void)
{
	/*if (OPR_ErrorWordingLow != NULL) [*/
	if (CheckChildErrorDisplayReq() == TRUE) {
		DisplayChildError();
		return;
	}

	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
#if defined(STOCKHM2) /* Mod by SMuratec C.P 2004/06/10 for V195通信結果表示の仕様 */
	if (OPR_ReviewCommandOprNextStep == OPR_COMMUNICATION_RESULT){
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_CommResultList);	/* "ﾂｳｼﾝｹｯｶ ｶｸﾆﾝ        " */
	}
	else{
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_CommConfirm);		/* "ﾖﾔｸ ｶｸﾆﾝ            " */
	}
#else
	CMN_StringCopy(FunctionDisplayBufferHigh, D2W_CommResultList);		/* "ﾂｳｼﾝｹｯｶ ｶｸﾆﾝ        " */
#endif

	DisplayStringHigh(0, FunctionDisplayBufferHigh);

#if defined(STOCKHM2) /* Mod by SMuratec C.P 2004/06/10 for V195 */
	/** 下段点滅表示 */
 	FlashDisplayStringLow(D2W_ProgramEnter);							/* "       ｷﾉｳ/ｾｯﾄ " */
#else
	/** 下段点滅表示 */
 	FlashDisplayStringLow(D2W_CommunicationConfirmEnter);				/* "       ﾂｳｼﾝｶｸﾆﾝ/ｾｯﾄ " */
#endif

}
/*************************************************************************
	module		:[通信結果表示]
	function	:[
		ジャーナルデータ(MAX:100件)の新しいものからＭＡＸ７０件までを表示します。
	]
	return		:[CONTINUE/END]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2000/09/18]
	author		:[石橋,近藤]
*************************************************************************/
UBYTE	CommandResult(void)
{
	UBYTE start_pos;	/* データ開始位置 */
	UBYTE data_max;		/* データ件数 */
	UBYTE i;			/* データ参照用インデックス */
	UBYTE count;
	UBYTE key;
	UBYTE keytype;
		
	UWORD	document_printNo_bak = 0; /* Added by SMuratec C.P 2004/06/21 */

	if (SYB_JournalFile[0].Number == 0xFFFF) {			/* 通信管理記録がない場合 	*/
		NackBuzzer();
		/*OPR_ErrorWordingLow = D2W_NoCommandResult;*/
		/*ChildDisplayStringLow(D2W_NoCommandResult);*/	/* "ﾂｳｼﾝｹｯｶ ｶｸﾆﾝ"の点滅表示がかぶさってしまうので見えない */
		OPR_ChildErrorFlag = NO_COMMAND_RESULT_ERROR;	/* "ﾂｳｼﾝｹｯｶ ｱﾘﾏｾﾝ       " */

		/*return(OPR_BACK);*//* 戻るキー無し by J.Kishida 2002/09/15 */
		return(OPR_CONTINUE);
	}

	/*----------------------------------------------------*/
	/* 通信管理記録データスタート位置とデータ件数の獲得   */
	/*----------------------------------------------------*/
	if (SYB_JournalFile[SYB_JournalPoint].Number == 0xffff) {	/* データがまだ一周していない */
		start_pos = i = (SYB_JournalPoint - 1);
		if (SYB_JournalPoint > SYS_JOURNAL_MAX - 30) {
			data_max = SYS_JOURNAL_MAX - 30;
		} else {
			data_max = SYB_JournalPoint;
		}
	}
	else {		/* 一周している場合 */
		if (SYB_JournalPoint) {
			start_pos = i = (SYB_JournalPoint - 1);
		} else {
			start_pos = i = (SYS_JOURNAL_MAX - 1);
		}
		data_max = SYS_JOURNAL_MAX - 30;
	}

	count = 1;
	while (1) {
		/*----------------------------------*/
		/* 表示 							*/
		/*----------------------------------*/
		DisplayResult(i, data_max, count);

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		/*case ARROW_UP:*/		/* 上矢印キー *//* Modified by J.Kishida 2002/09/15 */
		case LEFT_ARROW:		/* 左矢印キー */
			if (i == start_pos) {		/* 先頭位置の場合(回さない) */
				NackBuzzer();
				break;
			}
			i++;
			if (i > (SYS_JOURNAL_MAX - 1)) {
				i = 0;
			}
			count--;
			break;
		/*case ARROW_DOWN:*/	/* 下矢印キー *//* Modified by J.Kishida 2002/09/15 */
		case FUNCTION:			/* 機能／右矢印キー */
			if (count >= data_max) {
				NackBuzzer();
				break;
			}
			if (i == 0) {	/* データの先頭の場合 */
				i = SYS_JOURNAL_MAX - 1;
			} else {
				i--;
			}
			count++;
			break;
		case ENTER:
#if (0)	/* 個別プリント機能無し by J.Kishida 2002/09/15 */
			//PrintCommandResultList(i);
			//return (OPR_END);
#else
 #if defined(STOCKHM2) /* Mod by SMuratec C.P for V195 通信結果表示プリント */
			document_printNo_bak = SYS_DocumentPrintNo;
			SYS_DocumentPrintNo = i;
			FinalListPrintOperation(LST_COM_RESULT_LIST);
			SYS_DocumentPrintNo = document_printNo_bak;
			document_printNo_bak = 0;
 #else
			NackBuzzer();
 #endif
			break;
#endif
		case STOP:			/* ストップ				*/
		case KEY_TIME_UP:	/* キー入力時間制限タイムアップ				*/
			return (OPR_END);
#if (0)	/* 戻るキー無し by J.Kishida 2002/09/15 */
		//case BACK:			/* 戻るキー */
		//	return (OPR_BACK);
#endif
		case NO_EFFECT:	/* 画質キーや濃度キーを押した時にNackが鳴るので追加 by J.Kishida 2002/10/16 */
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}


/*************************************************************************
	module		:[通信結果１件分の表示を行います]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2000/09/18]
	author		:[石橋,近藤]
*************************************************************************/
void	DisplayResult(UBYTE index, UBYTE data_max, UBYTE count)
{
#if defined(STOCKHM2) /* DVT : mod by SMuratec C.P 2004/09/09 */
	UBYTE	wk[OPR_DISPLAY_MAX + 1];

	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	/*- １行目 ------------------------------------------------------------------------*/
	/* 送信・受信 	*/
	if (SYB_JournalFile[index].Type == TXTYPE) {	/* "ソウシン" */
		CMN_StringCopy(&FunctionDisplayBufferHigh[0], (UBYTE*)D2W_Transmit);
	} else {
		CMN_StringCopy(&FunctionDisplayBufferHigh[0], (UBYTE*)D2W_Receive);
	}
	/* 開始日時		*/
	CMN_MemorySetNULL(wk, OPR_DISPLAY_MAX, ' ');
	CriterionMinuteToDayTimeAsc(SYB_JournalFile[index].StartTime / 60, LST_MMDDHHMM1, wk);
	CMN_StringCopy(&FunctionDisplayBufferHigh[6], wk );

	/*- ２行目 ------------------------------------------------------------------------*/
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	/* 結果			*/
	OPR_CommunicationResult(SYB_JournalFile[index].Result, &FunctionDisplayBufferLow[0]);
	if (CHK_UNI_MultiT30Monitor()) {		/* マルチＴ３０ */
		/* Ｔ３０シリアル番号用 */
		/*if (SYB_T30MonitorDRAM_Status[index] == 1) [*/
		if (((SYS_T30Monitor + index)->JournalType != SYS_T30_EMPTY)
		&&  ((SYS_T30Monitor + index)->WritePointer != 0)) {
			CMN_UnsignedIntToASC( &FunctionDisplayBufferLow[3], (UWORD)index, 3, ' ' );
		}
		else {
			CMN_MemorySet(&FunctionDisplayBufferLow[3], 3, '-');
		}
	}
	else {	/* 通常の通番出力 */
		CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[3], (UWORD)SYB_JournalFile[index].Number, 3, '0');
	}

	FunctionDisplayBufferLow[6] = ':';		/* ':' */

	/* 相手先名		*/
	CMN_StringCopyNumUntilNull(&FunctionDisplayBufferLow[7], SYB_JournalFile[index].RemoteID_TTI, 12);

	ChangeDisplayBuffer(FunctionDisplayBufferLow);

	/* ↑↓の表示 */
	CMN_MemorySetNULL(&FunctionDisplayBufferLow[16],4,' ');
	if (data_max != 1) {	/* データが１件のみの場合はなにも表示しない */
		if (count == 1) {			/* 先頭データの場合 */
			FunctionDisplayBufferLow[19] = '\x7E';					/* -> */
		}
		else if (count == data_max) {	/* 最終データの場合 */
			FunctionDisplayBufferLow[19] = '\x7F';					/* <- */
		}
		else {
			FunctionDisplayBufferLow[17] = '\x7F';					/* <- */
			FunctionDisplayBufferLow[18] = '/';						/* '/' */
			FunctionDisplayBufferLow[19] = '\x7E';					/* -> */
		}
	}
	
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	DisplayStringLow(0, FunctionDisplayBufferLow);

#else /* DVT : mod by SMuratec C.P 2004/09/09 */
/*******************************************************************************************************************************/
	UBYTE	wk[OPR_DISPLAY_MAX + 1];

	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	/*- １行目 ------------------------------------------------------------------------*/
	/* 送信・受信 	*/
	if (SYB_JournalFile[index].Type == TXTYPE) {	/* "送信" */
		CMN_StringCopy(&FunctionDisplayBufferHigh[0], (UBYTE*)D2W_Tx);
	} else {
		CMN_StringCopy(&FunctionDisplayBufferHigh[0], (UBYTE*)D2W_Rx);
	}

	/* 村田仕様のみ通番を表示するよう変更(ＣＳ要求) */
	/* No.XXX */
	if (CHK_UNI_MultiT30Monitor()) {		/* マルチＴ３０ */
		/* Ｔ３０シリアル番号用 */
		/*if (SYB_T30MonitorDRAM_Status[index] == 1) [*/
		if (((SYS_T30Monitor + index)->JournalType != SYS_T30_EMPTY)
		&&  ((SYS_T30Monitor + index)->WritePointer != 0)) {
			CMN_UnsignedIntToASC( &FunctionDisplayBufferHigh[2], (UWORD)index, 3, ' ' );
		}
		else {
			CMN_MemorySet(&FunctionDisplayBufferHigh[2], 3, '-');
		}
	}
	else {	/* 通常の通番出力 */
		CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[2], (UWORD)SYB_JournalFile[index].Number, 3, '0');
	}

	FunctionDisplayBufferHigh[5] = ':';		/* ':' */

	/* 相手先名		*/
	CMN_StringCopyNumUntilNull(&FunctionDisplayBufferHigh[6], SYB_JournalFile[index].RemoteID_TTI, 14);


	/*- ２行目 ------------------------------------------------------------------------*/
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	/* 結果			*/
	OPR_CommunicationResult(SYB_JournalFile[index].Result, &FunctionDisplayBufferLow[0]);

	/* 開始日時		*/
	CMN_MemorySetNULL(wk, OPR_DISPLAY_MAX, ' ');
#if defined(STOCKHM2) /* Mod by SMuratec C.P 2004/06/10 for V195通信結果年、月、時、分の表示 */
	CriterionMinuteToDayTimeAsc(SYB_JournalFile[index].StartTime / 60, LST_MMDDHHMM1, wk);
#else
	CriterionMinuteToDayTimeAsc(SYB_JournalFile[index].StartTime / 60, LST_MMDDHHMM, wk);
#endif
	CMN_StringCopy(&FunctionDisplayBufferLow[4], wk );

	/* ↑↓の表示 */
	if (data_max != 1) {	/* データが１件のみの場合はなにも表示しない */
		if (count == 1) {			/* 先頭データの場合 */
			/*FunctionDisplayBufferLow[19] = OPR_CG_DOWN_ARROW;*/	/* ↓ */
#if defined(STOCKHM2) /* Mod by SMuratec C.P 2004/06/10 for V195通信結果年、月、時、分の表示 */
			FunctionDisplayBufferLow[19] = '\x7E';					/* -> */
#else
			FunctionDisplayBufferLow[19] = D2W_SF_Program[0];		/* > */
#endif
		}
		else if (count == data_max) {	/* 最終データの場合 */
			/*FunctionDisplayBufferLow[19] = OPR_CG_UP_ARROW;*/		/* ↑ */
#if defined(STOCKHM2) /* Mod by SMuratec C.P 2004/06/10 for V195通信結果年、月、時、分の表示 */
			FunctionDisplayBufferLow[19] = '\x7F';					/* <- */
#else
			FunctionDisplayBufferLow[19] = D2W_SF_CursorLeft[0];	/* < */
#endif
		}
		else {
#if (0)
			//FunctionDisplayBufferLow[17] = OPR_CG_DOWN_ARROW;		/* ↓ */
			//FunctionDisplayBufferLow[18] = '/';					/* '/' */
			//FunctionDisplayBufferLow[19] = OPR_CG_UP_ARROW;		/* ↑ */
#else
			/*
			// そのまま“↓”を“>”，“↑”を“<”に置き換えただけでは
			// 中間のときに“>/<”になってしまいます．
			// “</>”になるように変更します．
			// by J.Kishida 2002/09/26
			*/
 #if defined(STOCKHM2) /* Mod by SMuratec C.P 2004/06/10 for V195通信結果年、月、時、分の表示 */
			FunctionDisplayBufferLow[17] = '\x7F';					/* <- */
			FunctionDisplayBufferLow[18] = '/';						/* '/' */
			FunctionDisplayBufferLow[19] = '\x7E';					/* -> */
 #else
			FunctionDisplayBufferLow[17] = D2W_SF_CursorLeft[0];	/* < */
			FunctionDisplayBufferLow[18] = '/';						/* '/' */
			FunctionDisplayBufferLow[19] = D2W_SF_Program[0];		/* > */
 #endif
#endif
		}
	}

#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P 2004/07/14 for prefix *//* by K.Watanabe 2004/12/16 */
	ChangeDisplayBuffer(FunctionDisplayBufferHigh);
#endif
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	DisplayStringLow(0, FunctionDisplayBufferLow);
#endif /* DVT : mod by SMuratec C.P 2004/09/09 */
}


/*************************************************************************
	module		:[通信結果]
	function	:[
	]
	common		:[]
	condition	:[
	]
	commment	:[
	]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[2001/08/30]
	author		:[近藤]
*************************************************************************/
void	OPR_CommunicationResult(UWORD Result,				/* 通信結果 */
							 UBYTE *ResultName)			/* 通信ﾓｰﾄﾞ名 */
{
	switch ( Result & 0x0C00 ) {
	case NO_ERROR:
		CMN_StringCopy( ResultName, D2W_SF_OK);
		break;
	case TRANSMITERROR:
	case RECEIVEERROR:
	case DIALERROR:
		CMN_StringCopy( ResultName, D2W_SF_NG);
		break;
	}
}
#endif	/* (PRO_COMM_RESULT_REVIEW == ENABLE) */

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)
/*************************************************************************
	module		:[コマンドファイルの参照位置のセット]
	function	:[
		1.

	]g
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/10/24]
	author		:[SMuratec L.Z.W]
*************************************************************************/
UBYTE SetBackCommand(UBYTE mode)
{
	UBYTE	i;					/* ループ変数 */
	UBYTE	status;				/* コマンドの状態 */
	UBYTE	com_set_ok;			/* １：コマンドあり、０：コマンドなし */
	UBYTE	same_command;		/* 検索の結果見つかったコマンドが前回参照していたコマンドと同じ時１にセット */
	UBYTE	kind;				/* コマンド種別（コマンドファイルか一括送信か */
	UBYTE	file_number;		/* コマンド番号または一括送信ファイル番号 */
	UBYTE	search_com;			/* 検索しているコマンドの種類 */
	UBYTE	next_search_com;	/* 次に検索するコマンドの種類 */

	com_set_ok = 0;
	same_command = 0;
	search_com  = OPR_Buf.ReviewCtrl.SearchCommandType;	/* 現在検索（参照）しているｺﾏﾝﾄﾞの種類を獲得 */
	file_number = OPR_Buf.ReviewCtrl.CommandPointer;	/* 現在の参照位置（ｺﾏﾝﾄﾞ番号、一括送信ﾌｧｲﾙ番号）を獲得 */

	if (file_number > 0 && file_number <= SYS_COM_FILE_MAX) {
		file_number --;
	}
	else {
		file_number = SYS_COM_FILE_MAX - 1;
		if (search_com == OPR_EXECUTE_COMMAND) {
			search_com = OPR_WAITING_COMMAND;
		}
		else {
			search_com = OPR_EXECUTE_COMMAND;
		}
	}

	for (i = 0; i < OPR_MAX_COM_SEARCH; i++) {	/* 各検索モードすべてチェックするまで */
		switch (search_com) {
		case OPR_EXECUTE_COMMAND:	/** 実行中のコマンドを参照中 */
		case OPR_WAITING_COMMAND:	/** 実行待ち、予約中のコマンドファイルを参照中 */
			kind = SYS_COMMAND_TRX;
			/* 次の検索モード（検索するコマンドの種類)をセット */
			if (search_com == OPR_EXECUTE_COMMAND) {
				/** 実行中のコマンドがない場合は実行待ち、予約中のコマンドを探す */
				next_search_com = OPR_WAITING_COMMAND;
			}
			else {
				/** 実行まち、予約中のコマンドがない場合は実行中のコマンドを探す */
				next_search_com = OPR_EXECUTE_COMMAND;
			}
			break;
		default:
			break;
		}

		/** 各検索モードに対するコマンドの検索を実行 */
		for (; file_number != 0xFF; file_number--) {	/* コマンドファイル、または一括送信ファイルを１周するまで */

			/** コマンドの登録状態を獲得 */
			status = CheckCommandBatchStatus(kind, file_number);

			if (status == SYS_CMD_EXECUTE) {	/** キューに展開されていてかつ、実行中か実行前 */
				/* 実行中のコマンドかどうか調べる */
				if (CheckExecuteCommand(kind, file_number) < SYS_EXEC_QUEUE_MAX /** 指定されたｺﾏﾝﾄﾞに対するｷｭｰが実行中 */
					&& search_com == OPR_EXECUTE_COMMAND) {	/** 検索しているのが、実行中のコマンドの場合 */
					break;	/*見つかったのでループを抜ける */
				}
				else if (search_com == OPR_EXECUTE_COMMAND) {	/** 指定されたコマンドに対するキューが実行待ち */
					break;
				}
				else {
					search_com = OPR_WAITING_COMMAND;
				}
			}
			else if (status == SYS_CMD_WAITING) { /* 予約中 */
				if (search_com == OPR_WAITING_COMMAND) {
					break;
				}
			}
		}

		if (file_number == 0xFF) {	/** 該当するコマンドがない */
			search_com = next_search_com;	/* 検索モードを次のモードに変更 */
			file_number = SYS_COM_FILE_MAX - 1;	/* ファイル番号を初期化(先頭から検索させる) */
		}
		else {
			/* コマンドあり */
			if ((search_com == OPR_Buf.ReviewCtrl.SearchCommandType)
			 && (file_number == OPR_Buf.ReviewCtrl.CommandPointer)) {
				/* Same Command */
				same_command = 1;
			}
			com_set_ok = 1;
			break; /* 検索終了 */
		}
	}

	if (com_set_ok) {
		if (same_command) {	/* 前回参照していたもの以外コマンドがない */
			/* エラー表示を出す */
			/* 終了はしない */
			NackBuzzer();
			OPR_ChildErrorFlag = NO_COMMAND_ERROR;
		}
		else {
			OPR_Buf.ReviewCtrl.CommandPointer = file_number;
			OPR_Buf.ReviewCtrl.SearchCommandType = search_com;
			OPR_Buf.ReviewCtrl.CommandKind = kind;
		}
		return (OPR_CONTINUE);
	}
	else {	/* 実行中、実行前、予約中のコマンドがなにもない */
		/* エラー表示を出す */
		/* 終了する */
		if (mode == COMMAND_REVIEW_MODE) { /* 1996/04/08 消去後のポインターの再設定以外であればエラー表示をだす */
			NackBuzzer();
			OPR_ChildErrorFlag = NO_COMMAND_ERROR;
		}
		return (OPR_END);
	}
}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
