/*************************************************************************
*	System			: POPLAR/ANZU-L
*	File Name		: man_scnm.c
*	Author			:
*	Date			: 1997/06/09
*	RealTimeOS		: RISCモニタ
*	Description		: メインタスクMAN_Task()のメッセージ処理部
*					: スキャナ関連部
*	Module Name		: MAN_FromDocumentIn()
*					: MAN_FromSCN_GearBackLashTask()
*					: MAN_FromDocStore()
*					: MAN_FromDocumentOut()
*					: MAN_FromSCN_StampTestTask()
*					: MAN_FromSCN_MirrorMoveTask()
*					:MAN_FromSCN_DocOutTestTask()
*	Maintenance		:
*
*	Copyright (C) 1997 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
/*定義ファイル*/
/*SYS*/
#include  "\src\atlanta\define\product.h"
#include  "\src\atlanta\define\message.h"
#include  "\src\atlanta\define\apl_msg.h"
#include  "\src\atlanta\define\std.h"
#include  "\src\atlanta\define\sys_stat.h"
#include  "\src\atlanta\define\sysdoc.h"
/*MON*/
#include  "\src\atlanta\sh7043\define\def_tib.h"
#include  "\src\atlanta\sh7043\define\def_evtn.h"
/*SCN*/
#include  "\src\atlanta\define\sysscan.h"
/*MEM*/
#include  "\src\atlanta\define\mem_def.h"
/* CDC */
#include  "\src\atlanta\define\cdc_def.h"

/*参照ファイル*/
/*SYS*/
#include  "\src\atlanta\ext_v\bkupram.h"
#include  "\src\atlanta\ext_v\sys_data.h"
#include  "\src\atlanta\ext_v\man_data.h"
/*MON*/
#include  "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include  "\src\atlanta\sh7043\ext_v\extv_sem.h"
/*SCN*/
#include  "\src\atlanta\define\mntsw_a.h"
#include  "\src\atlanta\define\mntsw_c.h"
#include  "\src\atlanta\ext_v\scn_data.h"
#include  "\src\atlanta\ext_v\scn_tbl.h"
/*OPR*/
#if (PRO_PANEL == ANK)
#include  "\src\atlanta\opr\ank\ext_v\opr_data.h"
#endif
#if (PRO_PANEL == KANJI)
#include  "\src\atlanta\opr\kanji\ext_v\opr_data.h"
#endif
/*PRN*/
#if (PRO_PRINT_TYPE == LED)
#include  "\src\atlanta\prt\ph3\ext_v\prn_data.h"
#endif
#if (PRO_CIPHER == ENABLE)
#include  "\src\atlanta\scd\ext_v\cph_data.h"
#include  "\src\atlanta\ext_v\ini_tbl.h"/*	By Y.Suzuki 1997/09/04	*/
#endif

/*プロトタイプ宣言*/
#include  "\src\memsw\define\mems_pro.h"
#include  "\src\atlanta\define\uni_pro.h"
#include  "\src\atlanta\define\mon_pro.h"
#include  "\src\atlanta\define\man_pro.h"
#include  "\src\atlanta\define\mem_pro.h"
#include  "\src\atlanta\define\scn_pro.h"
#include  "\src\atlanta\define\cmn_pro.h"

#include  "\src\atlanta\sh7043\define\io_pro.h" /* Added by H.Kubo 1997/08/13  */

/* For Checker T.Nose 1997/10/21 */
void LampOff(void);

#if (PRO_DOC_IN == ENABLE)
/*************************************************************************
	module		:[原稿繰り込みタスクからのメッセージ処理]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		コンパイル時の"out of heap space"解消のために
		メッセージ処理を抜き出しました。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/12]
	author		:[小谷正樹]
*************************************************************************/
void	MAN_FromDocumentIn(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;
	UWORD	doc_item;
	UWORD	doc_message;
	UWORD	doc_sub_message1;
	UWORD	doc_sub_message2;

	doc_item = item;
	doc_message = message;
	doc_sub_message1 = sub_message1;
	doc_sub_message2 = sub_message2;

	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	snd_msg(mbxno.SCN_Task, &MainTaskMessage); /** 同期用メッセージ */
	if (tskno_DocumentInTask != 0xffff) {
		del_tsk(&tskno_DocumentInTask); /** 原稿繰り込みタスクの停止 */
	}
	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FEED_IN;
	SCN_StopDS1OffDetect = 0;			/* 1996/08/14 By N.Sakamoto */
	switch (doc_message) {
	case MSG_DOCUMENT_IN_SETUP:
		break;
	case MSG_DOCUMENT_IN_NOTHING: /** 原稿引き抜き処理 */
		if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)
		 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_IN)) {
			SCN_Init();
			if( tskno_SCN_GearBackLashTask == 0xffff ) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
				cre_tsk(&tskno_SCN_GearBackLashTask, TSK_SCN_GEARBACKLASHTASK, 0 );
			}
			/*	SCN_GearBackLashTaskの二重Cleateと原稿繰込動作が起動されない状態の防止 5 lines Insert By N.S. 1996/05/07 */
			else{
				del_tsk(&tskno_SCN_GearBackLashTask);
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
				cre_tsk(&tskno_SCN_GearBackLashTask, TSK_SCN_GEARBACKLASHTASK, 0 );
			}
		}
		break;
	case MSG_DOCUMENT_IN_ERROR: /** 繰り込み不良時のエラー処理 */
		SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FEED_ERROR; /** フィード・エラーをセット */
		break;
	case MSG_DOCUMENT_IN_LAMP_ERROR: /* ランプ・エラー時の処理 */
		SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_LAMP_ERROR; /** ランプ・エラーをセット */
		break;
	default: /** あり得ない */
		break;
	}
}
#endif


/*************************************************************************
	module		:[ギア・バック・ラッシュタスクからのメッセージ処理]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		コンパイル時の"out of heap space"解消のために
		メッセージ処理を抜き出しました。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/12]
	author		:[小谷正樹]
*************************************************************************/
void	MAN_FromSCN_GearBackLashTask(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;
	UWORD	doc_item;
	UWORD	doc_message;
	UWORD	doc_sub_message1;
	UWORD	doc_sub_message2;

	doc_item = item;
	doc_message = message;
	doc_sub_message1 = sub_message1;
	doc_sub_message2 = sub_message2;

	GearBackLashRequest = FALSE;

	/* タイムアウト発生時の再起動処理  1997/05/09 s.takeuchi */
	CMN_DisableInterrupt();
	GearBackLashTimer = 0;
	if (GearBackLashTimeout) {
		GearBackLashTimeout = FALSE;
		if (GearBackLashRetryCount > 0) {
			GearBackLashRequest = TRUE;
		}
	}
	else {
		GearBackLashRetryCount = 0;
	}
	CMN_EnableInterrupt();

	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	snd_msg(mbxno.SCN_GearBackLashTask, &MainTaskMessage); /** Jan.24,1995 同期用メッセージ */
	if (tskno_SCN_GearBackLashTask != 0xffff) {
		del_tsk(&tskno_SCN_GearBackLashTask);	/** ギア・バック・ラッシュ・タスクの停止	*/
	}
	switch (doc_message) {
	case MSG_SCN_GEAR_BACK_LASH_END:
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY);
		break;
	default:
		break;
	}

	/* ギアバックラッシュ中にSCANNER_BUSYをクリアさせないため追加  1997/05/10 s.takeuchi */
	SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_GEAR_BACKLASH);

}


/*************************************************************************
	module		:[原稿蓄積タスクからのメッセージ処理]
	function	:[
		原稿蓄積タスクからのメッセージを解析し、必要な処理する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		コンパイル時の"out of heap space"解消のために
		原稿蓄積タスクからのメッセージ処理を抜き出しました。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/12]
	author		:[小谷正樹]
*************************************************************************/
void	MAN_FromDocStore(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	UBYTE is_mem_over_wait = TRUE;
	MESSAGE_t	MainTaskMessage;
	MESSAGE_t	*MessageControl;
	UWORD	doc_item;
	UWORD	doc_message;
	UWORD	doc_sub_message1;
	UWORD	doc_sub_message2;

	doc_item = item;
	doc_message = message;
	doc_sub_message1 = sub_message1;
	doc_sub_message2 = sub_message2;

	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	if (doc_message == MSG_SCN_DOCSTORE_1PAGE_START) { /* 表示更新用同期メッセージ */
		snd_msg(mbxno.SCN_Sub, &MainTaskMessage); /** 同期用メッセージ */
	}
	else {
		snd_msg(mbxno.SCN_Task, &MainTaskMessage); /** 同期用メッセージ */
	}

	/**	「１ページ蓄積開始」と「１ページ蓄積完了」以外のメッセージの時に、
	**	蓄積タスクを終了する
	*/
	if ((doc_message != MSG_SCN_DOCSTORE_1PAGE_START)
	&&	(doc_message != MSG_SCN_DOCSTORE_1PAGE_FINISH)) {
		if (tskno_SCN_DocumentStoreTask != 0xffff) {
			del_tsk(&tskno_SCN_DocumentStoreTask);	/** 蓄積タスクの停止	*/
		}
	}

	switch (doc_message) {
	/****************************************************************/
	/* 原稿蓄積タスク-正常終了処理									*/
	/****************************************************************/
	case MSG_SCN_DOCSTORE_OK: /** 蓄積正常終了であれば */

		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY); /** スキャナー使用中の解除 */
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_DOC_STORE);/** 原稿蓄積中を解除 */
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_JAM_RECOVER_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START;

#if (PRO_FBS == ENABLE)
		/** ADF読み取りで正常終了したら、ギアバックラッシュを予約する */
		if (SYS_ScannerExecMode == SCN_ADF) {
			GearBackLashRequest = TRUE;
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
			if (CHK_UNI_MirrorReadyModeVariable()) { /* ミラーキャリッジ待機位置可動仕様 */
				SCN_MirrorReadyPosition = READY_POSITION_ADF; /* 待機位置をADFにする */
			}
		}
		else { /* FBS読取りの場合 */
			/* FBS読取りが終了した時点でFBSカバーが開いていたらFBSを待機位置とする */
			if (CHK_UNI_MirrorReadyModeVariable()) { /* ミラーキャリッジ待機位置可動仕様 */
				if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_BOOK_OPEN) {
					SCN_MirrorReadyPosition = READY_POSITION_FBS;
				}
				else {
					SCN_MirrorReadyPosition = READY_POSITION_ADF;
				}
			}
		}
#else
		GearBackLashRequest = TRUE;
#endif

		switch (SYS_DocumentStoreItem) { /** 原稿の種別を解析 */
		case SYS_MEM_TX_FILE: /** メモリ送信ファイル */
#if (PRO_FBS == ENABLE)	/* By M.Kotani 97/05/29 */
			/* 次原稿ありの場合、次原稿蓄積開始オペレーション */
			if (SYS_NextBookDocument == TRUE) {
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_NEXT_SCAN_START_OPR;
#if (0) /* OPR_Task からタイマーを起動するように変更 */
//				/* 次原稿オペレーションタイマーを起動（６０秒） */
//				if (timer_next_scan_complete == 0xff) {
//					CMN_MultiTimer10msStart(&timer_next_scan_complete,&NextScanStartOperation);
//				}
#endif
			}
			/* 次原稿なしの場合、蓄積完了表示 */
			else {
				/* メモリ送信コマンド・ファイルの登録 */
				MemoryTxDocStoreOK(SYS_COMMAND_TRX);
				/* 原稿蓄積完了表示起動 */
				if (timer_store_fax_complete == 0xff) {
					CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
				}
			}
#else	/**(PRO_FBS == DISENABLE)*/	/* By M.Kotani 97/05/29 */
			/* メモリ送信コマンド・ファイルの登録 */
			MemoryTxDocStoreOK(SYS_COMMAND_TRX);
			/* 原稿蓄積完了表示起動 */
			if (timer_store_fax_complete == 0xff) {
				CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
			}
#endif
			break;
#if (PRO_BATCH_TX == ENABLE)
		case SYS_MEM_BATCH_TX_FILE1: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE2: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE3: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE4: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE5: /** 一括送信原稿なら */
#if (PRO_FBS == ENABLE)	/* By M.Kotani 97/05/29 */
			/* 次原稿ありの場合、次原稿蓄積開始オペレーション */
			if (SYS_NextBookDocument == TRUE) {
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_NEXT_SCAN_START_OPR;
#if (0) /* OPR_Task からタイマーを起動するように変更 */
//				/* 次原稿オペレーションタイマーを起動（６０秒） */
//				if (timer_next_scan_complete == 0xff) {
//					CMN_MultiTimer10msStart(&timer_next_scan_complete,&NextScanStartOperation);
//				}
#endif
			}
			/* 次原稿なしの場合、蓄積完了表示 */
			else {
				/* メモリ送信コマンド・ファイルの登録 */
				MemoryTxDocStoreOK(SYS_BATCH_TX);
				/* 原稿蓄積完了表示起動 */
				if (timer_store_fax_complete == 0xff) {
					CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
				}
			}
#else	/**(PRO_FBS == DISENABLE)*/	/* By M.Kotani 97/05/29 */
			/* メモリ送信コマンド・ファイルの登録 */
			MemoryTxDocStoreOK(SYS_BATCH_TX);
			/* 原稿蓄積完了表示起動 */
			if (timer_store_fax_complete == 0xff) {
				CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
			}
#endif /* PRO_FBS end */
			break;
#endif /* PRO_BATCH_TX end */
		case SYS_MEM_MULTI_COPY_FILE: /** マルチ・コピ・ファイル */
			MultiCopyDocStoreOK(); /** マルチ・コピー・ファイルの登録 */
#if (PRO_FBS == ENABLE)
			if ((SYS_ScannerExecMode == SCN_ADF) && (timer_store_copy_complete == 0xFF)) {
				CMN_MultiTimer10msStart(&timer_store_copy_complete, &StoreCompleteMessage);
			}
#else
			if (timer_store_copy_complete == 0xFF) {
				CMN_MultiTimer10msStart(&timer_store_copy_complete, &StoreCompleteMessage);
			}
#endif
			break;
		case SYS_MEM_MANUAL_COPY_FILE: /* 手差しコピーファイル */
			ManualCopyDocStoreOK();	/* 手差しコピーファイルの登録 */
#if (PRO_FBS == ENABLE)
			if ((SYS_ScannerExecMode == SCN_ADF) && (timer_store_copy_complete == 0xFF)) {
				CMN_MultiTimer10msStart(&timer_store_copy_complete, &StoreCompleteMessage);
			}
#else
			if (timer_store_copy_complete == 0xFF) {
				CMN_MultiTimer10msStart(&timer_store_copy_complete, &StoreCompleteMessage);
			}
#endif
			break;
		case SYS_MEM_POLLING_FILE: /** ポーリング・ファイル */
#if (PRO_FBS == ENABLE)	/* By M.Kotani 97/05/29 */
			/* 次原稿ありの場合、次原稿蓄積開始オペレーション */
			if (SYS_NextBookDocument == TRUE) {
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_NEXT_SCAN_START_OPR;
#if (0) /* OPR_Task からタイマーを起動するように変更 */
//				/* 次原稿オペレーションタイマーを起動（６０秒） */
//				if (timer_next_scan_complete == 0xff) {
//					CMN_MultiTimer10msStart(&timer_next_scan_complete,&NextScanStartOperation);
//				}
#endif
			}
			/* 次原稿なしの場合、蓄積完了表示 */
			else {
				SYB_PollingDocumentStatus = 1; /*	* ポーリング原稿有りセット */
#if (PRO_MULTI_LINE == ENABLE)
				SYB_PollingDocExclusiveFlag = SYS_EXIST_AND_NO_SENDING;	/* ポーリング原稿があるかどうかの変数 */
#endif
				/* 原稿蓄積完了表示起動 */
				if (timer_store_fax_complete == 0xff) {
					CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
				}
			}
#else	/**(PRO_FBS == DISENABLE)*/	/* By M.Kotani 97/05/29 */
			SYB_PollingDocumentStatus = 1; /*	* ポーリング原稿有りセット */
#if (PRO_MULTI_LINE == ENABLE)
			SYB_PollingDocExclusiveFlag = SYS_EXIST_AND_NO_SENDING;	/* ポーリング原稿があるかどうかの変数 */
#endif
			/* 原稿蓄積完了表示起動 */
			if (timer_store_fax_complete == 0xff) {
				CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
			}
#endif /* PRO_FBS end */
			break;
		case SYS_MEM_DB_POLLING_FILE: /** 検索ポーリング・ファイル */
#if (PRO_FBS == ENABLE)	/* By M.Kotani 97/05/29 */
			/* 次原稿ありの場合、次原稿蓄積開始オペレーション */
			if (SYS_NextBookDocument == TRUE) {
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_NEXT_SCAN_START_OPR;
#if (0) /* OPR_Task からタイマーを起動するように変更 */
//				/* 次原稿オペレーションタイマーを起動（６０秒） */
//				if (timer_next_scan_complete == 0xff) {
//					CMN_MultiTimer10msStart(&timer_next_scan_complete,&NextScanStartOperation);
//				}
#endif
			}
			/* 次原稿なしの場合、蓄積完了表示 */
			else {
				SYB_DB_PollingDocumentStatus = 1; /** 検索ポーリング有りセット */
				/* 原稿蓄積完了表示起動 */
				if (timer_store_fax_complete == 0xff) {
					CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
				}
			}
#else	/**(PRO_FBS == DISENABLE)*/	/* By M.Kotani 97/05/29 */
			SYB_DB_PollingDocumentStatus = 1; /** 検索ポーリング有りセット */
			/* 原稿蓄積完了表示起動 */
			if (timer_store_fax_complete == 0xff) {
				CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
			}
#endif /* PRO_FBS end */
			break;
#if (PRO_CLASS1 == ENABLE)	/* Add By Y.Tanimoto 1996/06/26 */
		case SYS_MEM_CLASS1_TX_FILE:	/* CLASS1 ローカルスキャン・ファイル */
			SYB_CL1_LocalScanDocStatus = 1; /**ローカルスキャン原稿有りセット *//*1996/09/24 Eguchi */
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = CL1_SCAN_REQ;
			MainTaskMessage.SubMessage1 = SYS_CLASS1_SCAN_MEMORY;
			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
			break;
#endif
#if (PRO_F_CODE == ENABLE)	/* 1997/03/11  By T.Yamaguchi */
		case SYS_MEM_SUB_BULLETIN_FILE:	/* Ｆコード原稿蓄積起動 */
#if (PRO_FBS == ENABLE)
			/* 次原稿ありの場合、次原稿蓄積開始オペレーション */
			if (SYS_NextBookDocument == TRUE) {
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_NEXT_SCAN_START_OPR;
#if (0) /* OPR_Task からタイマーを起動するように変更 */
//				/* 次原稿オペレーションタイマーを起動（６０秒） */
//				if (timer_next_scan_complete == 0xff) {
//					CMN_MultiTimer10msStart(&timer_next_scan_complete,&NextScanStartOperation);
//				}
#endif
			}
			/* 次原稿なしの場合、蓄積完了表示 */
			else {
				FcodeDocStoreOK(SYS_DocumentStoreBoxNumber);
				/* 原稿蓄積完了表示起動 */
				if (timer_store_fax_complete == 0xff) {
					CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
				}
			}
#else /* (PRO_FBS == DISABLE) */
			/* 原稿蓄積完了表示起動 */
			if (timer_store_fax_complete == 0xff) {
				CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
			}
#endif /* PRO_FBS end */
			break;
#endif
#if (PRO_CIPHER == ENABLE)
		case SYS_MEM_CIPHER_FILE:
  #if (PRO_FBS == ENABLE)	/* By M.Kotani 97/05/29 */
			/* 次原稿ありの場合、次原稿蓄積開始オペレーション */
			if (ScrambleOn == 1) {/*	By Y.Suzuki 1997/09/04	*/
				if (SYS_NextBookDocument == TRUE) {
					SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_NEXT_SCAN_START_OPR;
#if (0) /* OPR_Task からタイマーを起動するように変更 */
//					/* 次原稿オペレーションタイマーを起動（６０秒） */
//					if (timer_next_scan_complete == 0xff) {
//						CMN_MultiTimer10msStart(&timer_next_scan_complete,&NextScanStartOperation);
//					}
#endif
				}
				/* 次原稿なしの場合、蓄積完了表示 */
				else {
					/* 原稿蓄積完了表示起動 */
					if (timer_store_fax_complete == 0xff) {
						CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
					}
				}
 			}
  #else	/**(PRO_FBS == DISENABLE)*/	/* By M.Kotani 97/05/29 */
			/* 原稿蓄積完了表示起動 */
			if (ScrambleOn == 1) {/*	By Y.Suzuki 1997/09/04	*/
				if (timer_store_fax_complete == 0xff) {
					CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
				}
			}
  #endif
			if (ScrambleOn == 1) {/*	By Y.Suzuki 1997/09/04	*/
				SYS_CipherComExec = SYS_CIPHER_EXEC;
				SYS_MachineStatus[SYS_CIPHER_STATUS] = SYS_SCRAMBLE_EXEC;
				CipherReadIndex.Item = SYS_DocumentStoreItem;
				CipherReadIndex.No = SYS_DocumentStoreNo;
				CipherReadIndex.Page = SYS_DocumentStorePage;
				CipherReadIndex.BoxNumber = 0;
				CipherData.StartPageNo = 1;
				/*	暗号化タスク起動	*/
				cre_tsk(&tskno_SCD_CipherTask,TSK_SCD_CIPHERTASK,0);
			}
			break;
#endif /* PRO_CIPHER end */
		default: /** 原稿の種別不適当 */
			/**	 有りえない */
			break;
		}

#if (PRO_FBS == ENABLE)	/* by K.Watanabe '97.09/11 */
		/* 電話中にポーリング蓄積等をされると、UpdateLCD()では次原稿蓄積の確認表示が出来ないので、
		** ジャムリカバー等と同様に、オペレーションでイベントを受けるロジックに変更します
		*/
		if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_NEXT_SCAN_START_OPR) {
			snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
			rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
		}
#endif
		break;

	/****************************************************************/
	/* 原稿蓄積タスク-メモリ・オーバー処理							*/
	/****************************************************************/
	case MSG_SCN_DOCSTORE_MEM_OVER: /** 蓄積メモリー・オーバー時の処理 */
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_JAM_RECOVER_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START;
		/*	村田仕様用の原稿蓄積メモリオーバー処理
		**	※FX仕様は削除	1996/10/31 s.takeuchi
		*/

		switch (SYS_DocumentStoreItem) { /** 原稿の種別を解析 */
		case SYS_MEM_TX_FILE:
		case SYS_MEM_MULTI_COPY_FILE:
		case SYS_MEM_MANUAL_COPY_FILE:
		case SYS_MEM_POLLING_FILE:
		case SYS_MEM_DB_POLLING_FILE:
#if (PRO_BATCH_TX == ENABLE)
		case SYS_MEM_BATCH_TX_FILE1:
		case SYS_MEM_BATCH_TX_FILE2:
		case SYS_MEM_BATCH_TX_FILE3:
		case SYS_MEM_BATCH_TX_FILE4:
		case SYS_MEM_BATCH_TX_FILE5:
#endif
#if (PRO_CLASS1 == ENABLE)
		case SYS_MEM_CLASS1_TX_FILE:
#endif
#if (PRO_F_CODE == ENABLE)	/* 1997/03/11  By T.Yamaguchi */
		case SYS_MEM_SUB_BULLETIN_FILE:	/* Ｆコード原稿蓄積起動 */
#endif
#if (PRO_CIPHER == ENABLE)
		case SYS_MEM_CIPHER_FILE:/**	暗号化前原稿 By Y.Suzuki 1997/06/10	*/
			if ((ScrambleOn == 0) && (SYS_DocumentStoreItem == SYS_MEM_CIPHER_FILE)) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY); /** スキャナ-開放 */
				SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_DOC_STORE); /** 蓄積終了 */
				break;
			}
#endif
			/** １ページ以上蓄積ならキー入力待ち（ＦＩＰ以外）*/
			if ((MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber)!= MEM_NO_INDEX) /* １ページ以上蓄積されている */
			 && (SYS_DocumentStoreItem != SYS_MEM_FIP_FILE) /* FIPファイルでない */
			 &&	!CMN_CheckScanFilePrinting())  {
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_MEMORY_OVER_OPR; /** オペレーション経由のメモリ・オーバーをセット */
				snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);/* OPR_Task -> OPR_SubMessageTask Jan.18,1995 By T.Nose */
				rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl); /* By S.K Jan.24,1995 */
				is_mem_over_wait = TRUE;
			}
			else {
				switch (SYS_DocumentStoreItem)	{ /** 原稿の種別を解析 */
				case SYS_MEM_TX_FILE: /** メモリ送信ファイル */
#if (PRO_CIPHER == ENABLE)
				case SYS_MEM_CIPHER_FILE:/**	暗号化前原稿 By Y.Suzuki 1997/06/10	*/
					if ((SYS_DocumentStoreItem == SYS_MEM_CIPHER_FILE) && (ScrambleOn == 0)) {
						break;
					}
#endif
					if (SYS_DocumentStoreItem != SYS_MEM_CIPHER_FILE) {
						MemoryTxDocStoreNG(SYS_COMMAND_TRX); /** メモリ送信コマンド・ファイルのキャンセル */
					}
					if (CHK_UNI_MemoryOverMessagePrint()) { /** メモリ・オーバー・メッセージ印字ON? */
															/* UNI :NEw MEMORY SWITCH 対応1996/04/16 Eguchi */
						SYS_MemoryOverListRequest = 1; /** メモリ・オーバー印字要求セット */
					}
					break;
#if (PRO_BATCH_TX == ENABLE)
				case SYS_MEM_BATCH_TX_FILE1: /** 一括送信原稿なら */
				case SYS_MEM_BATCH_TX_FILE2: /** 一括送信原稿なら */
				case SYS_MEM_BATCH_TX_FILE3: /** 一括送信原稿なら */
				case SYS_MEM_BATCH_TX_FILE4: /** 一括送信原稿なら */
				case SYS_MEM_BATCH_TX_FILE5: /** 一括送信原稿なら */
					MemoryTxDocStoreNG(SYS_BATCH_TX); /** 一括送信コマンド・ファイルのキャンセル */
					if (CHK_UNI_MemoryOverMessagePrint()) { /** メモリ・オーバー・メッセージ印字ON? */
						SYS_MemoryOverListRequest = 1; /** メモリ・オーバー印字要求セット */
					}
					break;
#endif
				case SYS_MEM_POLLING_FILE: /** ポーリング・ファイル */
				case SYS_MEM_DB_POLLING_FILE: /** 検索ポーリング・ファイル */
					/** ポーリング原稿、検索ポーリング原稿のメモリ・オーバー時のリスト出力 */
					if (CHK_UNI_MemoryOverMessagePrint()) { /** メモリ・オーバー・メッセージ印字ON? */
						SYS_MemoryOverListRequest = 1;
					}
					break;
				case SYS_MEM_MULTI_COPY_FILE: /** マルチ・コピー・ファイル */
					/* コピープリント中ならメモリオーバーとして登録する	 1996/12/18 s.takeuchi */
					if (CMN_CheckScanFilePrinting()) {
						MultiCopyDocStoreMemoryOver();
					}
					else {	/* 通常のメモリオーバー処理 */
						MultiCopyDocStoreNG(); /** マルチ・コピー・ファイルのキャンセル */
					}
					break;
				case SYS_MEM_MANUAL_COPY_FILE: /** 手差しコピーファイル */
					SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START;
					/* コピープリント中ならメモリオーバーとして登録する	 1996/12/18 s.takeuchi */
					if (CMN_CheckScanFilePrinting()) {
						ManualCopyDocStoreMemoryOver();
					}
					else {	/* 通常のメモリオーバー処理 */
						ManualCopyDocStoreNG(); /** 手差しコピーファイルのキャンセル */
					}
					break;
#if (PRO_CLASS1 == ENABLE)
				case SYS_MEM_CLASS1_TX_FILE:	/* CLASS1 ローカルスキャン・ファイル */
					SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FAXMODEM; /** CLASS1動作中クリア	*/
					MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
					break;
#endif
#if (PRO_F_CODE == ENABLE)	/* 1997/03/11  By T.Yamaguchi */
				case SYS_MEM_SUB_BULLETIN_FILE:	/* Ｆコード原稿蓄積起動 */
					/** Ｆコード原稿のメモリ・オーバー時のリスト出力 */
					FcodeDocStoreNG(SYS_DocumentStoreBoxNumber);
					if (CHK_UNI_MemoryOverMessagePrint()) { /** メモリ・オーバー・メッセージ印字ON? */
						SYS_MemoryOverListRequest = 1;
					}
					break;
#endif
				default:
					break;
				}
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY); /* スキャナ-開放 */
				SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_DOC_STORE); /* 蓄積終了 */
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_MEMORY_OVER; /** メモリ・オーバー・セット */
			}
			break;
		default: /**  有りえない */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY); /** スキャナ-開放 */
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_DOC_STORE); /** 蓄積終了 */
			break;
		}
		break;

	/****************************************************************/
	/* 原稿蓄積タスク-停止処理										   */
	/****************************************************************/
	case MSG_SCN_DOCSTORE_STOPSW_ON: /** 蓄積停止処理	*/
#if (PRO_FBS == ENABLE)
		if (CHK_UNI_MirrorReadyModeVariable()) { /* ミラーキャリッジ待機位置切替え可能仕様 */
			/* 蓄積の中断は無条件でＡＤＦ位置へ */
			SCN_MirrorReadyPosition = READY_POSITION_ADF;
		}
#endif
		switch (SYS_DocumentStoreItem)	{ /** 原稿の種別を解析 */
		case SYS_MEM_TX_FILE: /** メモリ送信ファイル */
#if (PRO_CIPHER == ENABLE)
		case SYS_MEM_CIPHER_FILE:/**	暗号化前原稿 By Y.Suzuki 1997/07/11	*/
			if ((SYS_DocumentStoreItem == SYS_MEM_CIPHER_FILE) && (ScrambleOn == 0)) {
				break;
			}
#endif
			MemoryTxDocStoreNG(SYS_COMMAND_TRX); /** メモリ送信コマンド・ファイルのキャンセル */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber); /** 原稿消去 Mar.11.1997  By T.Yamaguchi */
			break;
#if (PRO_BATCH_TX == ENABLE)
		case SYS_MEM_BATCH_TX_FILE1: /** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE2: /** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE3: /** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE4: /** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE5: /** 一括送信原稿 */
			MemoryTxDocStoreNG(SYS_BATCH_TX); /** メモリ送信コマンド・ファイルのキャンセル */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /** 原稿消去 */
			break;
#endif
		case SYS_MEM_MULTI_COPY_FILE: /** マルチ・コピー・ファイル */
			/* コピープリント中なら停止でも登録する  1996/12/18 s.takeuchi */
			if (CMN_CheckScanFilePrinting()) {
				MultiCopyDocStoreOK(); /** マルチ・コピー・ファイルの登録 */
			}
			else {
				MultiCopyDocStoreNG(); /** マルチ・コピー・ファイルのキャンセル */
				MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /** 原稿消去 */
			}
			break;
		case SYS_MEM_MANUAL_COPY_FILE: /** 手差し・コピー・ファイル */
			/* コピープリント中なら停止でも登録する  1996/12/18 s.takeuchi */
			if (CMN_CheckScanFilePrinting()) {
				ManualCopyDocStoreOK(); /** 手差しコピーファイルの登録 */
			}
			else {
				ManualCopyDocStoreNG(); /** 手差し・コピー・ファイルのキャンセル */
				MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /** 原稿消去 */
			}
			break;
		case SYS_MEM_POLLING_FILE: /** ポーリング・ファイル */
		case SYS_MEM_DB_POLLING_FILE: /** 検索ポーリング・ファイル */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /** 原稿消去 */
			break;
#if (PRO_CLASS1 == ENABLE)	/* Add By Y.Tanimoto 1996/06/26 */
		case SYS_MEM_CLASS1_TX_FILE:	/* CLASS1 ローカルスキャン・ファイル */
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FAXMODEM; /** CLASS1動作中クリア	*/
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
			break;
#endif
#if (PRO_F_CODE == ENABLE)	/* 1997/03/11  By T.Yamaguchi */
		case SYS_MEM_SUB_BULLETIN_FILE:	/* Ｆコード原稿蓄積起動 */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber); /** 原稿消去 Mar.11.1997  By T.Yamaguchi */
			FcodeDocStoreNG(SYS_DocumentStoreBoxNumber);
			break;
#endif
		default: /** 有り得ない */
			break;
		}
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY); /** スキャナ-開放 */
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_DOC_STORE); /** 蓄積終了 */

		/* 停止処理追加(原稿なければギアバックラッシュを予約する)  1997/04/18 s.takeuchi */
#if (PRO_FBS == ENABLE)
		if (SYS_ScannerExecMode == SCN_ADF) {
			if (!DS1() && !DS2()) {
				GearBackLashRequest = TRUE;
			}
		}
#else
		if (!DS1() && !DS2()) {
			GearBackLashRequest = TRUE;
		}
#endif
		break;
	/****************************************************************/
	/* 原稿蓄積一ページ蓄積終了										*/
	/* 表示更新用													*/
	/* 蓄積処理としては何も実行しない								*/
	/****************************************************************/
	case MSG_SCN_DOCSTORE_1PAGE_FINISH:		/* １ページ蓄積完了 */
		switch (SYS_DocumentStoreItem) {
		case SYS_MEM_MULTI_COPY_FILE:
			SYB_MultiCopyFile[SYB_MultiCopyWritePoint].StorePage++;
#if (PRO_FBS == ENABLE)
			if (SYS_ScannerExecMode == SCN_FBS) {
				/* ここでマシンステータスの蓄積中解除と完了表示の起動を行っていたが
				** 完了表示が２回出ていたので削除。他にすることなし。
				*/
			}
			else {
				/* ＴＢＤ 実施する場合はここにいれる
				** ＡＤＦで１ページ読取り完了時、選択された記録紙に画データが納まらないとき、
				** 記録紙選択／確認のオペレーションを行う
				*/
				/* ＡＤＦ原稿サイズ入力 by T.Soneoka 1997/03/10
				** ＡＤＦ蓄積枚数が１枚目のとき
				** １．ＡＤＦ蓄積完了した原稿サイズと倍率より用紙を確定する
				** ２．用紙確定できる場合
				**     ①SYS_MultiCopyFile[].Cassetteに設定する
				** ３．用紙確定できない場合
				**     ①マシンステータスを設定する
				**     ②ＡＤＦ用紙選択オペレーションを実行するためメッセージ送信する
				*/
			}
#endif
			break;
		case SYS_MEM_MANUAL_COPY_FILE:
			SYB_ManualCopyFile.StorePage++;
			break;
		default:
			break;
		}
		break;
	case MSG_SCN_DOCSTORE_1PAGE_START:
		break;
	/****************************************************************/
	/* 原稿蓄積タスク-エラー処理									*/
	/****************************************************************/
	case MSG_SCN_DOCSTORE_MAXLINE_OVER: /* 継続ジャムオペレーション */
	case MSG_SCN_DOCSTORE_DOC_ERROR:
	case MSG_SCN_DOCSTORE_TOP_COVER_OPEN:
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_JAM_RECOVER_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START;
		/* ADFカバー開の時はFEED_ERRORを立てない  1996/10/31 s.takeuchi */
#if (PRO_SEPERATE_24V == DISABLE)
#if (PRO_FBS == ENABLE)
		if (!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN)
		 || ((SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) && (SYS_ScannerExecMode == SCN_ADF))) {
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FEED_ERROR;
		}
#else /* PRO_FBS else */
		if (!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN)) {
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FEED_ERROR;
		}
#endif /* PRO_FBS end */
#else /* PRO_SEPERATE_24V else */
		if (!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN)) {
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FEED_ERROR;
		}
#endif /* PRO_SEPERATE_24V end */
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_DOC_STORE);
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY);

		if (SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE) {
			if (SYB_MultiCopyFile[SYB_MultiCopyWritePoint].SortType == SYS_NONE_SORT) {
			/* ノン･ソートマルチコピーの場合は中断→終了 */
				if (((message == MSG_SCN_DOCSTORE_DOC_ERROR) || (message == MSG_SCN_DOCSTORE_TOP_COVER_OPEN))
				 && CMN_CheckScanFilePrinting()) {
				/* "00/00 00"と表示されるため、プリント中ならDOC_ERRORでも登録する  1997/05/22 s.takeuchi */
					MultiCopyDocStoreOK();
				}
				else {
					MultiCopyDocStoreNG();
					MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
				}
				break;
			}
			else {
				if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYB_MultiCopyReadPoint, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX) {
					/* ソートマルチコピーで一枚も蓄積されていなければ 中断→終了*/
					MultiCopyDocStoreNG();
					MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去 */
					break;
				}
			}
		}
		if (SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE) {
			if (SYB_ManualCopyFile.SortType == SYS_NONE_SORT) {
				if (((message == MSG_SCN_DOCSTORE_DOC_ERROR) || (message == MSG_SCN_DOCSTORE_TOP_COVER_OPEN))
				 && CMN_CheckScanFilePrinting()) {
				/* "00/00 00"と表示されるため、プリント中ならDOC_ERRORでも登録する  1997/05/22 s.takeuchi */
					ManualCopyDocStoreOK();
				}
				else {
					ManualCopyDocStoreNG();
					MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
				}
				break;
			}
			else {
				if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX) { /* 1ページも蓄積されていなければ */
					ManualCopyDocStoreNG();
					MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去 */
					break;
				}
			}
		}
#if (PRO_F_CODE == ENABLE)	/* 1997/03/11  By T.Yamaguchi */
		if (SYS_DocumentStoreItem == SYS_MEM_SUB_BULLETIN_FILE) {
			if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber) == MEM_NO_INDEX) { /* 1ページも蓄積されていなければ */
				MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber); /* 蓄積原稿の消去 */
				FcodeDocStoreNG(SYS_DocumentStoreBoxNumber);
				break;
			}
		}
#endif
		else {
#if 0	/* 変更 1997/06/02 By T.Yamaguchi */
**			if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX) @ /* 1ページも蓄積されていなければ */
**				MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去 */
#endif
			if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber) == MEM_NO_INDEX) { /* 1ページも蓄積されていなければ */
				MemoryTxDocStoreNG(SYS_COMMAND_TRX); /** メモリ送信コマンド・ファイルのキャンセル */
				MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber); /* 蓄積原稿の消去 */
				break;
			}
		}
		if (doc_message == MSG_SCN_DOCSTORE_TOP_COVER_OPEN) {
			DocumentResetOperation = TRUE; /* ジャム／ＦＢＳリカバーオペレーション指示 */
		}
		else {
			/* ジャムリカバーオペレーション指示 */
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_JAM_RECOVER_OPR;
			snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
			rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
		}
		break;
	case MSG_SCN_DOCSTORE_NO_DOCUMENT:
	case MSG_SCN_DOCSTORE_LAMP_ERROR:
	case MSG_SCN_DOCSTORE_STR_PAGE_ERROR:
	case MSG_SCN_DOCSTORE_MIRROR_ERROR:
	default:
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_JAM_RECOVER_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START;
		/** 蓄積タスク・エラー処理 */
		switch (SYS_DocumentStoreItem) { /** 原稿の種別を解析 */
		case SYS_MEM_TX_FILE: /** メモリ送信ファイル */
#if (PRO_CIPHER == ENABLE)
		case SYS_MEM_CIPHER_FILE:/**	暗号化前原稿 By Y.Suzuki 1997/07/11	*/
			if ((SYS_DocumentStoreItem == SYS_MEM_CIPHER_FILE) && (ScrambleOn == 0)) {
				break;
			}
#endif
			MemoryTxDocStoreNG(SYS_COMMAND_TRX); /** メモリ送信コマンド・ファイルのキャンセル */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber); /** 原稿消去 */
			break;
#if (PRO_BATCH_TX == ENABLE)
		case SYS_MEM_BATCH_TX_FILE1: /** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE2: /** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE3: /** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE4: /** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE5: /** 一括送信原稿 */
			MemoryTxDocStoreNG(SYS_BATCH_TX); /** メモリ送信コマンド・ファイルのキャンセル */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /** 原稿消去 */
			break;
#endif
		case SYS_MEM_MULTI_COPY_FILE: /** マルチ・コピー・ファイル */
			MultiCopyDocStoreNG(); /* マルチ・コピー・ファイルのキャンセル */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /** 原稿消去 */
			break;
		/* ICHOU変更 by T.Soneoka 1996/08/07 */
		case SYS_MEM_MANUAL_COPY_FILE: /** 手差し・コピー・ファイル */
			ManualCopyDocStoreNG(); /* 手差し・コピー・ファイルのキャンセル */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /** 原稿消去 */
			break;
		case SYS_MEM_POLLING_FILE: /** ポーリング・ファイル */
		case SYS_MEM_DB_POLLING_FILE: /** 検索ポーリング・ファイル */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /** 蓄積原稿の消去 */
			break;
#if (PRO_CLASS1 == ENABLE)	/* Add By Y.Tanimoto 1996/06/26 */
		case SYS_MEM_CLASS1_TX_FILE:	/* CLASS1 ローカルスキャン・ファイル */
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FAXMODEM; /** CLASS1動作中クリア	*/
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
			break;
#endif
#if (PRO_F_CODE == ENABLE)	/* 1997/03/11  By T.Yamaguchi */
		case SYS_MEM_SUB_BULLETIN_FILE:	/* Ｆコード原稿蓄積起動 */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber); /** 原稿消去 Mar.11.1997  By T.Yamaguchi */
			FcodeDocStoreNG(SYS_DocumentStoreBoxNumber);
			break;
#endif
		default:
			break;
		}
		if (doc_message == MSG_SCN_DOCSTORE_LAMP_ERROR) { /** ランプ・エラーなら */
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_LAMP_ERROR; /** ランプ・エラーをセット */
		}
		else if (doc_message == MSG_SCN_DOCSTORE_STR_PAGE_ERROR) {
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_PAGE_ERROR;	/** 指定枚数ページエラー */	/*	SYS_SCANNER_PAGE_ERRORはどこでクリアするのか？ オペレーション */

			/**	枚数指定＞読み取り枚数 の時はSCN_Task内で排出後
			**	ピックアップローラーを上げるための要求をセットする
			*/	/* 1997/03/12 s.takeuchi */
			GearBackLashRequest = TRUE;
		}
#if (PRO_FBS == ENABLE)
		else if ((doc_message == MSG_SCN_DOCSTORE_MIRROR_ERROR)
		 && !(SYB_MaintenanceSwitch[MNT_SW_C6] & IGNORE_MIRROR_ERROR)) {
			/* 原稿蓄積がミラーエラーなら、スキャナの状態をミラーエラーにする */
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_MIRROR_ERROR;
		}
#endif
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY); /** スキャナ-開放 */
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_DOC_STORE); /** 蓄積終了 */
		break;
	}

	/* 蓄積終了後の初期化処理 */
	switch (SYS_DocumentStoreItem) { /** 原稿の種別を解析 */
	case SYS_MEM_TX_FILE: /** メモリ送信ファイル */
#if (PRO_BATCH_TX == ENABLE)
	case SYS_MEM_BATCH_TX_FILE1: /** 一括送信原稿 */
	case SYS_MEM_BATCH_TX_FILE2: /** 一括送信原稿 */
	case SYS_MEM_BATCH_TX_FILE3: /** 一括送信原稿 */
	case SYS_MEM_BATCH_TX_FILE4: /** 一括送信原稿 */
	case SYS_MEM_BATCH_TX_FILE5: /** 一括送信原稿 */
#endif
#if (PRO_F_CODE == ENABLE)	/* 1997/03/11  By T.Yamaguchi */
	case SYS_MEM_SUB_BULLETIN_FILE:	/* Ｆコード原稿蓄積起動 */
#endif
	case SYS_MEM_POLLING_FILE: /** ポーリング・ファイル */
	case SYS_MEM_DB_POLLING_FILE: /** 検索ポーリング・ファイル */
#if (PRO_CIPHER == ENABLE)
	case SYS_MEM_CIPHER_FILE:/**	暗号化前原稿 By Y.Suzuki 1997/07/11	*/
#endif
#if (PRO_COPY_FAX_MODE == DISABLE)	/**1997/08/21 By M.Kotani*/
	case SYS_MEM_MULTI_COPY_FILE: /** マルチ・コピー・ファイル */
	case SYS_MEM_MANUAL_COPY_FILE: /** 手差し・コピー・ファイル */
#endif
#if (PRO_CIPHER == ENABLE)/*	By Y.Suzuki 1997/09/04	*/
		if ((SYS_DocumentStoreItem == SYS_MEM_CIPHER_FILE) && (ScrambleOn == 0)) {
			break;
		}
#endif
		if ((doc_message != MSG_SCN_DOCSTORE_1PAGE_START)
		 &&	(doc_message != MSG_SCN_DOCSTORE_1PAGE_FINISH)
		 && (doc_message != MSG_SCN_DOCSTORE_DOC_ERROR)
		 && (doc_message != MSG_SCN_DOCSTORE_MAXLINE_OVER)) {
			if ((!(SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_NEXT_SCAN_OPR))
			 && (!(SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_NEXT_SCAN_START_OPR))) {
				CMN_ResetMemoyFeederTx();
				CMN_ResetStamp();
				CMN_ResetPrimaryMode();
				CMN_ResetPrimaryContrast(); /** 濃度のリセット処理とLEDをリセット */
				CMN_ResetConfirmationReport(); /* By S.K Sep.19,1994 */
			}
		}
		break;
#if (PRO_COPY_FAX_MODE == ENABLE)	/**1997/08/21 By M.Kotani*/
	case SYS_MEM_MULTI_COPY_FILE: /** マルチ・コピー・ファイル */
	case SYS_MEM_MANUAL_COPY_FILE: /** 手差し・コピー・ファイル */
#endif
#if (PRO_PRINT_TYPE == LED)
		PRN_1PageReceived = 1;	/* 受信中原稿待ちしているプリントタスクを再動作させる */
#endif
		break;
	default:
		break;
	}

#if (PRO_FBS == ENABLE)
	/* 次原稿指示変数、ブック原稿サイズ設定フラグの初期化 */
	if (!(SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_NEXT_SCAN_START_OPR)
	 && (doc_message != MSG_SCN_DOCSTORE_1PAGE_START)
	 && (doc_message != MSG_SCN_DOCSTORE_1PAGE_FINISH)
	 && (doc_message != MSG_SCN_DOCSTORE_DOC_ERROR)
	 && (doc_message != MSG_SCN_DOCSTORE_MAXLINE_OVER)) {
		SYS_NextBookDocument = FALSE;
		IsBookDocSizeSet = FALSE;
	}
#endif

#if (PRO_FBS == ENABLE)
	/**	ミラーキャリッジを待機位置まで引き戻す
	**	ただし、以下の条件の時は引き戻さない
	**		１ページ蓄積開始、１ページ蓄積完了、ミラーエラーの時
	*/
	if ((doc_message != MSG_SCN_DOCSTORE_1PAGE_START)
	 &&	(doc_message != MSG_SCN_DOCSTORE_1PAGE_FINISH)
	 &&	!(SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MIRROR_ERROR)) {
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
		if (SCN_MirrorReadyPosition == READY_POSITION_ADF) { /* 待機位置ＡＤＦ */
			if ((SCN_MirrorCarriageStatus == MIRROR_HS_ON) /* ADF→FBS移動中の停止処理 */
			/* || (SCN_MirrorCarriageStatus == MIRROR_FBS_SCANNING) @* FBS読取り中の停止処理 */
			 || (SCN_MirrorCarriageStatus == MIRROR_MOVE_ABORT_STOP)) { /* FBS読取り中の停止処理 */
				MirrorTaskInstruction = MIRROR_TASK_TO_ADF_READY;
			}
			else { /* FBS読取り終了の時 */
				MirrorTaskInstruction = MIRROR_TASK_FBS_END_TO_ADF;
			}
		}
		else { /* 待機位置ＦＢＳ */
			MirrorTaskInstruction = MIRROR_TASK_TO_READY;
		}
		MirrorTaskRequest = TRUE;
	}
#endif
}


/*************************************************************************
	module		:[原稿排出タスクからのメッセージ処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/12]
	author		:[小谷正樹]
*************************************************************************/
void	MAN_FromDocumentOut(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;
	UWORD	doc_item;
	UWORD	doc_message;
	UWORD	doc_sub_message1;
	UWORD	doc_sub_message2;

	doc_item = item;
	doc_message = message;
	doc_sub_message1 = sub_message1;
	doc_sub_message2 = sub_message2;

	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	snd_msg(mbxno.SCN_Task, &MainTaskMessage); /** 同期用メッセージ */
	if (tskno_DocumentOutTask != 0xffff) {
		del_tsk(&tskno_DocumentOutTask); /** 原稿排出タスクの停止 */
	}
	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FEED_OUT;
	SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_SCANNER_BUSY;
	CMN_ResetMemoyFeederTx(); /** Aug.24,1994 QAT */
	switch (doc_message) {
	case MSG_DOCUMENT_OUT_OK:
		break;
	case MSG_DOCUMENT_OUT_ERROR:
		/* ADFカバー開の時はFEED_ERRORを立てない  1996/10/31 s.takeuchi */
		if (!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN)) {
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FEED_ERROR; /** フィードエラー */
		}
	case MSG_DOCUMENT_OUT_NEXTPAGE_OK:/* このようなエラーは無い（桐には）*/
		break;
	case MSG_DOCUMENT_OUT_NEXTPAGE_ERROR:
		SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FEED_ERROR; /*** フィード・エラーをセット */
		break;
	}

	/*	ICHOUでのADF原稿排出時はミラーは待機位置にあるはずなので、
	**	原稿排出タスク終了処理ではギアバックラッシュを予約するだけで良い
	**		1996/08/10 s.takeuchi
	*/
	GearBackLashRequest = TRUE;	/** ギアバックラッシュ予約する */	/* 1996/07/24 s.takeuchi */

}


/*************************************************************************
	module		:[済スタンプテストタスクからのメッセージ処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/12]
	author		:[小谷正樹]
*************************************************************************/
void	MAN_FromSCN_StampTestTask(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;
	UWORD	doc_item;
	UWORD	doc_message;
	UWORD	doc_sub_message1;
	UWORD	doc_sub_message2;

	doc_item = item;
	doc_message = message;
	doc_sub_message1 = sub_message1;
	doc_sub_message2 = sub_message2;

	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	snd_msg(mbxno.SCN_Task, &MainTaskMessage); /** 同期用メッセージ */
	if (tskno_SCN_StampTestTask != 0xffff) {
		del_tsk(&tskno_SCN_StampTestTask); /** スタンプ・テストタスクの停止 */
	}
	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FEED_OUT;
	SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_SCANNER_BUSY;
	switch (doc_message) {
	case MSG_DOCUMENT_OUT_OK:
		break;
	case MSG_DOCUMENT_OUT_ERROR:
		/* ADFカバー開の時はFEED_ERRORを立てない  1996/10/31 s.takeuchi */
		if (!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN)) {
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FEED_ERROR; /** フィードエラー */
		}
	case MSG_DOCUMENT_OUT_NEXTPAGE_OK:/* このようなエラーは無い（桐には）*/
		break;
	case MSG_DOCUMENT_OUT_NEXTPAGE_ERROR:
		SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FEED_ERROR; /*** フィード・エラーをセット */
		break;
	}
#if (0)
/*#if (PRO_PRINT_TYPE == LASER)*/
	if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS]&SYS_SCANNER_BUSY) &&
		!(SYS_MachineStatus[SYS_MACHINE_STATUS]&(SYS_FEED_IN+SYS_FEED_OUT))) { /* 7/29/1994 */
	/*	SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;			'96,03,13 By N.S. */
		SCN_Init();
		if( tskno_SCN_GearBackLashTask == 0xffff ){						/* '96,03,13 By N.S. */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;	/* '96,03,13 By N.S. */
			cre_tsk(&tskno_SCN_GearBackLashTask, TSK_SCN_GEARBACKLASHTASK, 0 );
		}
		/*	SCN_GearBackLashTaskの二重Cleateと原稿繰込動作が起動されない状態の防止 5 lines Insert By N.S. 1996/05/07 */
		else{
			del_tsk(&tskno_SCN_GearBackLashTask);
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
			cre_tsk(&tskno_SCN_GearBackLashTask, TSK_SCN_GEARBACKLASHTASK, 0 );
		}
	}
/*#endif*/
#endif
	/*	メッセージ処理の後でタスクを起動する	 1996/08/10 s.takeuchi
	**	ICHOUでのスタンプテスト時はミラーは待機位置にあるはずなので、
	**	スタンプテストタスク終了処理ではギアバックラッシュを予約するだけで良い
	*/
	GearBackLashRequest = TRUE;	/** ギアバックラッシュを予約する */
}


#if (PRO_FBS == ENABLE)		/* POPLAR_B用	1997/01/21 T.Nose */
/*************************************************************************
	module		:[ミラーキャリッジ移動タスクからのメッセージ処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/07]
	author		:[吉川弘康]
*************************************************************************/
void	MAN_FromSCN_MirrorMoveTask(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;
	UWORD	doc_item;
	UWORD	doc_message;
	UWORD	doc_sub_message1;
	UWORD	doc_sub_message2;

	doc_item = item;
	doc_message = message;
	doc_sub_message1 = sub_message1;
	doc_sub_message2 = sub_message2;

	/** 同期用メッセージを送信し、ミラータスクを削除 */
	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	snd_msg( mbxno.SCN_MirrorMoveTask, &MainTaskMessage );
	if (tskno_SCN_MirrorMoveTask != 0xffff) {
		/* SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_MIRROR_BUSY;  1996/10/31 */
		del_tsk( &tskno_SCN_MirrorMoveTask );
	}

	if (doc_message == MSG_MIRROR_MOVE_OK) {	/** 正常に終了した */

		switch (SCN_MirrorTaskControl) {	/** ミラーキャリッジの動作指定 */
		case	MIRROR_TASK_INITIALIZE:	/** 電源ON時の初期化 */
			/** ミラー初期化中ビットをクリアしてスキャナを開放する */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_SCANNER_BUSY;
			SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_MIRROR_INIT|SYS_SCANNER_MIRROR_BUSY);

			/* 次原稿読取開始指示がある場合（プリンタカバーが開閉された） */
			if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_NEXT_SCAN_START) {
				/* 次原稿読取開始処理 */
				MAN_NextScanStart();
			}
			break;
		case	MIRROR_TASK_TO_READY:	/** 読み取り後の初期化 */
		case	MIRROR_TASK_TO_FBS_READY:	/* FBS待機位置への初期化 */
			/** スキャナを開放する */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_SCANNER_BUSY;
			SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_MIRROR_BUSY;
			/* 次原稿読取開始指示がある場合 */
			if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_NEXT_SCAN_START) {
				/* 次原稿読取開始処理 */
				MAN_NextScanStart();
			}
			break;
		case	MIRROR_TASK_TO_ADF:		/** ADF部への移動 */
			/** 読取り位置への移動完了とする */
			SYS_IsMirrorScanReady = TRUE;

			/* ADF読み取り前の準備中表示のため  1997/03/05 s.takeuchi */
			SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_PREPARATION_ADF);
			break;
		case	MIRROR_TASK_TO_FBS:		/** FBS部への移動 */
			/*
			**	D71サブASSY検査用(FBS)
			*/
			SYS_IsMirrorScanReady = TRUE;
			MirrorTaskInstruction = MIRROR_TASK_TO_ADF_READY;
			MirrorTaskRequest = TRUE;
			break;
		case	MIRROR_TASK_FCOT_READY:		/** FCOTコピー用待機位置への移動 */
			/** FCOTの時はMirror Busyを解除する */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_SCANNER_BUSY;	/* 1997/01/08 */
			SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_MIRROR_BUSY;
			SYS_IsMirrorScanReady = TRUE;
			/* LampOffTimer = 3;	@** ランプOFF用タイマーをセット(3分後にOFF) POPLAR_B で削除 T.Nose */
			break;
		case	MIRROR_TASK_TRANSPORT:		/** 輸送用の固定位置への移動 */
			SYB_ScannerTransportMode = TRUE;	/** 輸送モードを設定 */
			/** スキャナ使用禁止にするため、ミラー初期化中ビットなどはクリアしない */
			break;
		case	MIRROR_TASK_FBS_END_TO_ADF:	/** FBS読取り終了位置からADF読み取り位置への移動 */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_SCANNER_BUSY;
			SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_MIRROR_BUSY;
			SYS_IsMirrorScanReady = TRUE;
			break;
		case	MIRROR_TASK_TO_ADF_READY:	/** ADF待機位置への初期化 */
			/*
			**	D71サブASSY検査用(FBS)
			*/
			SYS_IsMirrorScanReady = TRUE;
			MirrorTaskInstruction = MIRROR_TASK_CCD_ADJUST;
			MirrorTaskRequest = TRUE;
			break;
		case	MIRROR_TASK_CCD_ADJUST:
			/*
			**	D71サブASSY検査用(FBS)
			*/
			LampOff();
			break;
		default:
			break;
		}
	}
	else {		/** エラーで終了した */
		/** ミラーキャリッジの移動が異常終了すると
		**	スキャナの状態をエラーにして、スキャナを開放する
		*/
		switch (doc_sub_message1) {
		case	MIRROR_MOVE_ERROR:
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_MIRROR_ERROR;
			break;
		case	MIRROR_MOVE_LAMP_ERROR:
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_LAMP_ERROR;
			break;
		}

		/**	ミラーの初期化エラーではスキャナを開放する
		**	(ADF/FBS読取り時は読み取り側のメッセージ処理で開放する)
		*/
		if ((SCN_MirrorTaskControl != MIRROR_TASK_TO_ADF)
		&&	(SCN_MirrorTaskControl != MIRROR_TASK_TO_FBS)) {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_SCANNER_BUSY;
		}

		/* ADF読み取り前の準備中表示のため  1997/03/05 s.takeuchi */
		if ((SCN_MirrorTaskControl == MIRROR_TASK_TO_ADF)
		 || (SCN_MirrorTaskControl == MIRROR_TASK_TO_FBS)) {
			SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_PREPARATION_ADF);
		}
	}
}
#endif	/* (PRO_FBS == ENABLE) */


/*************************************************************************
	module		:[原稿排出テストタスクからのメッセージ処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1997/05/23]
	author		:[野瀬敏弘]
*************************************************************************/
void MAN_FromSCN_DocOutTestTask(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;
	UWORD	doc_item;
	UWORD	doc_message;
	UWORD	doc_sub_message1;
	UWORD	doc_sub_message2;

	doc_item = item;
	doc_message = message;
	doc_sub_message1 = sub_message1;
	doc_sub_message2 = sub_message2;

	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	snd_msg(mbxno.SCN_Task, &MainTaskMessage); /** 同期用メッセージ */

	switch (doc_message) {
	case MSG_DOC_OUT_COVER_ERROR:
		SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_SCANNER_OPEN;
		break;
	case MSG_DOC_OUT_FEED_ERROR:
		SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FEED_ERROR;
		break;
	case MSG_DOC_OUT_COMPLETE:
	default:
		break;
	}

	/* スキャナを開放 */
	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FEED_OUT;
	SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_SCANNER_BUSY;

	/* 原稿排出テストタスクの削除 */
	if (tskno_SCN_DocumentStoreTask != 0xFFFF) {
		del_tsk(&tskno_SCN_DocumentStoreTask);
	}

	/* ギアバックラッシュの予約 */
	GearBackLashRequest = TRUE;
}

