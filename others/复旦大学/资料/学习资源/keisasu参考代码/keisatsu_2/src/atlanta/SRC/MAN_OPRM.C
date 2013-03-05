/*************************************************************************
*	System			: POPLAR/ANZU-L
*	File Name		: man_oprm.c
*	Author			:
*	Date			: 1997/06/09
*	RealTimeOS		: RISCモニタ
*	Description		: メインタスクMAN_Task()のメッセージ処理部
*					: オペレーション関連部
*	Module Name		: MAN_FromOperation()
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
#include  "\src\atlanta\define\sysprint.h"
#include  "\src\atlanta\define\sysrxsw.h"
#include  "\src\atlanta\define\syscomf.h"
#include  "\src\atlanta\define\sysmax.h"
#include  "\src\atlanta\define\sys_opt.h"
#include  "\src\atlanta\define\fcm_def.h"
#include  "\src\atlanta\define\sysdoc.h"
#include  "\src\atlanta\define\sysmjnl.h"
#include  "\src\atlanta\define\memfile.h"
/*MON*/
#include  "\src\atlanta\sh7043\define\def_tib.h"
#include  "\src\atlanta\sh7043\define\def_evtn.h"
/*SCN*/
#include  "\src\atlanta\define\sysscan.h"
/*MEM*/
#include  "\src\atlanta\define\mem_def.h"
/* 連続ポーリング機能 */
#if (PRO_CONTINUOUS_POLLING == ENABLE)
#include  "\src\atlanta\define\syscntpl.h"
#endif
/*OPR*/
#if (PRO_PANEL == ANK)
#include  "\src\atlanta\opr\ank\define\opr_def.h"
#endif
#if (PRO_PANEL == KANJI) /* Added by H.Kubo 1997/08/13 */
#include  "\src\atlanta\opr\kanji\define\opr_def.h"
#endif

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
#include  "\src\atlanta\ext_v\scn_data.h"
#include  "\src\atlanta\ext_v\scn_tbl.h"
#if (PRO_PRINT_TYPE == LASER)
#include  "\src\atlanta\prt\sp322\ext_v\prn_data.h"
#endif
/*OPR*/
#if (PRO_PANEL == ANK)
#include  "\src\atlanta\opr\ank\ext_v\opr_data.h"
#endif
#if (PRO_PANEL == KANJI)
#include  "\src\atlanta\opr\kanji\ext_v\opr_data.h"
#endif
#if (PRO_CLASS1 == ENABLE)
#include  "\src\atlanta\ext_v\cl1_data.h"
#endif
#if (PRO_CIPHER == ENABLE)
#include  "\src\atlanta\define\syscph.h"
#include "\src\atlanta\scd\ext_v\cph_data.h"
#endif
#if (PRO_FBS == ENABLE)
#include "\src\atlanta\define\mntsw_c.h"
#endif
/*プロトタイプ宣言*/
#include  "\src\memsw\define\mems_pro.h"
#include  "\src\atlanta\define\uni_pro.h"
#include  "\src\atlanta\define\mon_pro.h"
#include  "\src\atlanta\define\man_pro.h"
#include  "\src\atlanta\define\mem_pro.h"
#include  "\src\atlanta\define\stng_pro.h"
#include  "\src\atlanta\define\cmn_pro.h"
#include  "\src\atlanta\define\scn_pro.h"
#include  "\src\atlanta\sh7043\define\io_pro.h"
#if (PRO_SECURITY_RX == ENABLE)
	void	AllClearPrintProtect(void);
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
#include  "\src\atlanta\ext_v\sys_inf.h"
#endif

#include "\src\atlanta\define\unisw_c.h"

#if (1)	/* リアルタイムコピーの時、プリント不可の場合、ナック音を鳴らす。by Y.kano 2005/03/18 */
#include  "\src\atlanta\opr\ank\define\opr_pro.h"
#endif

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/11 */
#include	"\src\atlanta\ext_v\fcm_data.h"
#endif 		/* End of (defined (KEISATSU)) */

#if defined(KEISATSU)	/* 警察FAX DVT_ID33 Modify by SMuratec 夏 2005/11/12 */
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#endif

/*************************************************************************
	module		:[オペレーションタスクからのメッセージ処理]
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
void	MAN_FromOperation(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;
	UWORD page;
	UWORD	opr_item;
	UWORD	opr_message;
	UWORD	opr_sub_message1;
	UWORD	opr_sub_message2;
	UBYTE	mem_rx_no;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/06/09 Eguchi */
	MESSAGE_t	*MessageControl;
#endif

	opr_item = item;
	opr_message = message;
	opr_sub_message1 = sub_message1;
	opr_sub_message2 = sub_message2;

	switch (opr_message) { /** オペレーションの種類を解析 */
	/****************************************************************/
	/* オペレーション・タスク-原稿蓄積起動処理						*/
	/****************************************************************/
	case MSG_STORE_MEMORY_TX_DOC:		/* メモリ送信原稿蓄積起動			*/
	case MSG_STORE_MEMORY_BATCH_TX_DOC:	/* 一括送信原稿蓄積起動				*/
	case MSG_STORE_POLLING_DOC:			/* ポーリング送信原稿蓄積起動		*/
	case MSG_STORE_DBPOLLING_DOC:		/* 検索ポーリング送信原稿蓄積起動	*/
	case MSG_STORE_MULTI_COPY_DOC:		/* マルチコピー原稿蓄積起動			*/
	case MSG_STORE_MANUAL_COPY_DOC:		/* 手差し・コピー・ファイル			*/
	case MSG_STORE_FCODE_BOX_DOC:		/* Ｆコード原稿蓄積起動				*/
	case MSG_STORE_CIPHER_DOC:			/* 暗号化前原稿の蓄積起動 By Y.Suzuki 1997/06/10 */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
	case MSG_STORE_MAIL_TX_DOC:			/* メール用送信原稿蓄積起動		*/
	case MSG_STORE_MIXED_TX_DOC:		/* メール＆ＦＡＸ混在同報原稿蓄積起動	*/
#endif
#if (0) /* (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103) @* added by H.Hirao 1998/12/17 comment by H.Hirao 1998/12/28 */
		if (CMN_CheckScanEnable() && CMN_CheckFeederCommandEmpty() && QueryDocStoreEnable()) {
#else
		if (CMN_CheckScanEnable() && CMN_CheckFeederCommandEmpty()) { /* スキャナーーが未使用であれば*/
#endif
#if (PRO_FAX_AND_1COPY == ENABLE)	/* 1999/02/18 */
			SYS_FaxAnd1CopyEnable = FALSE;
#endif

			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FEED_IN;
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= (SYS_SCANNER_BUSY); /* スキャナー資源確保*/
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_DOC_STORE; /* 原稿蓄積をセット */
			switch (opr_message) { /* 原稿種別解析 */
			case MSG_STORE_MEMORY_TX_DOC:		/* メモリ送信ファイル */
				SYS_DocumentStoreItem = SYS_MEM_TX_FILE;
				SYS_DocumentStoreNo	  = opr_sub_message1; /* コマンドNo.に相当*/
				SYS_DocumentStorePage = 1; /* SYB_CommandFile[SYS_DocumentStoreNo].Page; */
				SYS_DocumentStoreBoxNumber = 0;	/* 1997/03/13  By T.Yamaguchi */
				SYS_MultiProgramFlag = 0;
#if (PRO_FAX_AND_1COPY == ENABLE)	/* 1999/02/18 */
				if (CHK_UNI_FaxAnd1Copy()) {
					SYS_FaxAnd1CopyEnable = TRUE;
					SYS_FCOT_PrintStartRequest = FALSE;
					SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Status = SYS_MCOPY_STORE; /* 蓄積開始～蓄積完了までのステータス登録 */
					SYB_MultiCopyFile[SYB_MultiCopyWritePoint].StorePage = 0;
					SYB_MultiCopyFile[SYB_MultiCopyWritePoint].PrintPage = 1;
					SYB_MultiCopyFile[SYB_MultiCopyWritePoint].ExecutiveNumber = 1;
				}
#endif
				break;
#if (PRO_BATCH_TX == ENABLE)
			case MSG_STORE_MEMORY_BATCH_TX_DOC:	/* メモリ一括送信ファイル */
				SYS_DocumentStoreItem = (UBYTE)(SYS_MEM_BATCH_TX_FILE1+opr_sub_message1); /** 一括送信番号(BOX No) */
				SYS_DocumentStoreNo	  = opr_sub_message2; /** メイル・ボックス番号に相当 *//* By H.Y 1994/08/20 */
				SYS_DocumentStorePage = 1;
				SYS_DocumentStoreBoxNumber = 0;	/* 1997/03/13  By T.Yamaguchi */
				/* 蓄積開始時にはインデックスのステータスを蓄積が開始されたことがわかる値にセットしたほうが良い TBD	 */
				SYB_BatchTxFile[opr_sub_message1].IndexNo[opr_sub_message2] = SYS_BAT_DOC_STORING; /** 登録原稿蓄積中をセット *//* By H.Y 1994/08/15 */
				SYS_MultiProgramFlag = 0;
				break;
#endif
			case MSG_STORE_POLLING_DOC:			/* ポーリング・ファイル */
				SYS_DocumentStoreItem = SYS_MEM_POLLING_FILE;
				SYS_DocumentStoreNo	  = 0;
				SYS_DocumentStorePage = 1;
				SYS_DocumentStoreBoxNumber = 0;	/* 1997/03/13  By T.Yamaguchi */
				SYS_MultiProgramFlag = 0;
				break;
			case MSG_STORE_DBPOLLING_DOC:		/* 検索ポーリング・ファイル */
				SYS_DocumentStoreItem = SYS_MEM_DB_POLLING_FILE;
				SYS_DocumentStoreNo	  = opr_sub_message1; /* メイル・ボックスNo.に相当*/
				SYS_DocumentStorePage = 1;
				SYS_DocumentStoreBoxNumber = 0;	/* 1997/03/13  By T.Yamaguchi */
				SYS_MultiProgramFlag = 0;
				break;
			case MSG_STORE_MULTI_COPY_DOC:		/* マルチ・コピー・ファイル */
				SYS_FCOT_PrintStartRequest = FALSE;
				SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Status = SYS_MCOPY_STORE; /* 蓄積開始～蓄積完了までのステータス登録 */
				SYB_MultiCopyFile[SYB_MultiCopyWritePoint].StorePage = 0;
				SYB_MultiCopyFile[SYB_MultiCopyWritePoint].PrintPage = 1;
				SYB_MultiCopyFile[SYB_MultiCopyWritePoint].ExecutiveNumber = 1;
				SYS_DocumentStoreItem = SYS_MEM_MULTI_COPY_FILE;
				SYS_DocumentStoreNo	  = (UWORD)SYB_MultiCopyWritePoint;
				SYS_DocumentStorePage = 1;
				SYS_DocumentStoreBoxNumber = 0;	/* 1997/03/13  By T.Yamaguchi */
				SYS_MultiProgramFlag = 0;

#if (0)
** /* ＰＯＰＬＡＲ＿Ｈはコピー時の読み取りモードは初期値のみが高画質とな
** ** それ以外は送信時と同一範囲となりましたので、以下のフラグは削除します
** ** By O.Kimoto 1998/03/2
** */
** #if (PRO_PANEL == KANJI)	/* Add By O.Kimoto 1998/01/30 */
** 				CopyOperationFlag = FALSE;	/* Add By O.Kimoto 1998/01/05 */
** #endif
#endif
				break;
			case MSG_STORE_MANUAL_COPY_DOC:		/* 手差し・コピー・ファイル */
				SYS_FCOT_PrintStartRequest = FALSE;
				SYB_ManualCopyFile.Status = SYS_MCOPY_STORE; /* 蓄積開始～蓄積完了までのステータス登録 */
				SYB_ManualCopyFile.StorePage = 0;
				SYB_ManualCopyFile.PrintPage = 1;
				SYB_ManualCopyFile.ExecutiveNumber = 1;
				SYS_DocumentStoreItem = SYS_MEM_MANUAL_COPY_FILE;
				SYS_DocumentStoreNo	  = 0;
				SYS_DocumentStorePage = 1;
				SYS_DocumentStoreBoxNumber = 0;	/* 1997/03/13  By T.Yamaguchi */
				SYS_MultiProgramFlag = 0;

#if (0)
** /* ＰＯＰＬＡＲ＿Ｈはコピー時の読み取りモードは初期値のみが高画質とな
** ** それ以外は送信時と同一範囲となりましたので、以下のフラグは削除します
** ** By O.Kimoto 1998/03/2
** */
** #if (PRO_PANEL == KANJI)	/* Add By O.Kimoto 1998/01/30 */
** 				CopyOperationFlag = FALSE;	/* Add By O.Kimoto 1998/01/05 */
** #endif
#endif

				break;
#if (PRO_F_CODE == ENABLE)	/* 1997/03/11  By T.Yamaguchi */
			case MSG_STORE_FCODE_BOX_DOC:		/* Ｆコード原稿蓄積起動 */
				SYS_DocumentStoreItem = SYS_MEM_SUB_BULLETIN_FILE;
				SYS_DocumentStoreNo	  = opr_sub_message1; /* メイル・ボックスNo.に相当*/
				SYS_DocumentStoreBoxNumber = (UBYTE)(opr_sub_message2);
				SYS_DocumentStorePage = 1;
				SYS_MultiProgramFlag = 0;
				if (SYS_DocumentStoreNo == 0) {	/* 上書き蓄積の場合は原稿を先に消去してから蓄積開始する */
					MEM_ClearDoc(SYS_DocumentStoreItem, MEM_ALL_NO, SYS_DocumentStoreBoxNumber);
					SYB_SubAddressBoxTable[SYS_DocumentStoreBoxNumber - 1].StoredDocBit = 0;	/* 受信蓄積ファイル番号リセット */
					SYS_DocumentStoreNo = 1;	/* 蓄積ファイル番号１をセットする */
				}
				SYB_SubAddressBoxTable[SYS_DocumentStoreBoxNumber - 1].DataStatus = SYS_SUB_ADDRESS_BOX_STORING;
				SYB_SubAddressBoxTable[SYS_DocumentStoreBoxNumber - 1].ScnStoringNo = SYS_DocumentStoreNo;	/* 蓄積中原稿番号 */
				break;
#endif
#if (PRO_CIPHER == ENABLE)	/*	By Y.Suzuki 1997/06/10	*/
			case MSG_STORE_CIPHER_DOC:
				if (ScrambleOn == 0) {/*	By Y.Suzuki 1997/09/04	*/
					break;
				}
				SYS_DocumentStoreItem = SYS_MEM_CIPHER_FILE;
			/*	SYS_MachineStatus[SYS_CIPHER_STATUS] = SYS_SCRAMBLE_EXEC;By Y.suzuki 980207 */
				SYS_DocumentStoreNo	  = opr_sub_message1; /* コマンドNo.に相当*/
				SYS_DocumentStorePage = 1; /* SYB_CommandFile[SYS_DocumentStoreNo].Page; */
				SYS_DocumentStoreBoxNumber = 0;	/* 1997/03/13  By T.Yamaguchi */
				SYS_MultiProgramFlag = 0;
			/*	SYS_CipherComExec = SYS_CIPHER_EXEC;By Y.suzuki 980207 */
				break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
			case MSG_STORE_MAIL_TX_DOC:		/* メール用送信原稿蓄積起動		*/
				SYS_DocumentStoreItem = SYS_MEM_MAIL_TX_FILE;
				SYS_DocumentStoreNo	  = opr_sub_message1; /* コマンド番号*/
				SYS_DocumentStorePage = 1;
				SYS_DocumentStoreBoxNumber = 0;
				SYS_MultiProgramFlag = 0;
				break;
			case MSG_STORE_MIXED_TX_DOC:	/* メール＆ＦＡＸ混在同報原稿蓄積起動	*/
				SYS_DocumentStoreItem = SYS_MEM_MAIL_TX_FILE;
				SYS_DocumentStoreNo	  = opr_sub_message1; /* コマンド番号*/
				SYS_DocumentStorePage = 1;
				SYS_DocumentStoreBoxNumber = 0;
				SYS_MultiProgramFlag = 0;
				SYS_INF_MixedTxRequest = TRUE;	/* MAIL&FAX混在同報を指示　*/
				SYS_INF_MixedTxFaxCommandNo = opr_sub_message2;	/* FAXのコマンド番号セット　*/
				break;
#endif
			default:
				break;
			}

#if (PRO_FBS == ENABLE)
			if (CMN_CheckDocumentOnFeeder() == TRUE) {
				SYS_ScannerExecMode = SCN_ADF;
				MirrorTaskInstruction = MIRROR_TASK_TO_ADF;
				if (CHK_UNI_MirrorReadyModeVariable()) {
					SCN_MirrorReadyPosition = READY_POSITION_ADF;
				}
			}
			else {
				SYS_ScannerExecMode = SCN_FBS;
				MirrorTaskInstruction = MIRROR_TASK_TO_FBS;
			}

			/** ミラーを読み取り開始位置へ移動させる */
			SYS_IsMirrorScanReady = FALSE;
			MirrorTaskRequest = TRUE;

#endif /* (PRO_FBS == ENABLE) */

			/* スキャン開始時にモーターが動かなくなることがあるため
			*  起動前にスキャナを初期化する
			*		1997/06/02 s.takeuchi
			*/

#if (PRO_IMAGE_PROCESSOR != IMAGE_PROCESSOR_LC82103)	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
			SCN_Init();
#endif

			cre_tsk(&tskno_SCN_DocumentStoreTask, TSK_SCN_TASK, 0); /* 原稿蓄積タスク起動 */
		}
		break;
	/****************************************************************/
	/* オペレーション・タスク-メモリ・プリント起動処理				*/
	/****************************************************************/
	case MSG_MEMORY_PRINT: /* メモリ送信原稿/ポーリング送信原稿/検索ポーリング送信原稿/ 親展受信原稿/リモートＦＡＸ原稿プリント起動 */	/*種類を追加 M.Kotani 1997/10/16*/
		if (CMN_CheckPrintEnable(SYS_IMAGE_PRINT))	 { /* プリンタ使用可能であれば */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中をセット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* イメージ・プリント中セット */
			SYS_DocumentPrintPageNo = 1; /* 1ページ目から印字開始 */
			SYS_DocumentPrintClass = SYS_PRINT_CLASS;
			cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* メモリ・プリント・タスク起動 */
		}
		break;
	/****************************************************************/
	/* オペレーション・タスク-リスト・プリント起動処理 Jan.8,1993	*/
	/****************************************************************/
	case MSG_LIST_PRINT:
		if (CMN_CheckPrintEnable(SYS_LIST_PRINT))	 {	/*種類を追加 M.Kotani 1997/10/16*/
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /* リスト・プリント実行中をセット */
			SYS_DocumentPrintPageNo = 1;
#if (PRO_PAT_JOURNAL == ENABLE)
			if (SYS_DocumentPrintItem == LST_JOURNAL_LIST) {
				cre_tsk(&tskno_JournalPrintTask, TSK_PRN_JOURNALPRINTTASK, 0);	/*	ジャーナルプリントタスク起動	*/
			}
			else {
				cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /* リスト・プリント・タスク起動 */
			}
#else
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /* リスト・プリント・タスク起動 */
#endif
#if (PRO_FBS == ENABLE)
			/* 機械屋さんからのDVT仕様要求。
			** テストパターンプリントと同時にミラーキャリッジを読取り動作させる
			** T.Nose 1997/10/04
			*/
			if ((SYS_DocumentPrintItem == LST_PATTERN_PRINT)
			 && (SYB_MaintenanceSwitch[MNT_SW_C9] & TEST_PRINT_MIRROR_MOVE)) {
				SYS_ScannerExecMode = SCN_FBS;
				MirrorTaskInstruction = MIRROR_TASK_TO_FBS;
				MirrorTaskRequest = TRUE;
			}
#endif
		}
		break;
	/****************************************************************/
	/* オペレーション・タスク-通信コマンド・ファイル操作			*/
	/****************************************************************/
	case MSG_ENTER_COMMAND: /* スキャナー送信またはポーリング受信起動 */
		break;
	case MSG_ERASE_COMMAND:
	case MSG_ERASE_EXECQUEUE:
		/*----------------------------------------------*/
		/*	コマンドファイル,ExecQueueファイルの取消	*/
		/*----------------------------------------------*/
		MAN_MltFaxComStop();

#if (PRO_PRINT_TYPE == LASER)
		if (CMN_CheckF100Model()) {	/* for F100R D65RL 1997/12/05 */
			CMN_DisableInterrupt();	/**	割り込み禁止	*/
			PRN_1PageReceived = 1;
			det_evt(EVT_PRN_RESTART);
			CMN_EnableInterrupt();	/**	割り込み許可	*/
		}
#endif

#if 0
**		if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) &&
**			(SYS_FaxComType == SYS_COMMAND_EXECUTE)){
**			CommandErased = 1;
**			if (SYS_CurrentExecutingCommand->Status == SYS_EXEC_ERASED) { /* 実行中のコマンドを消去 */
**				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_FAXCOM;
**			}
**		}
**		else { /* 待ち行列にセットされたコマンドを消去 */
**			/* 一括送信登録と通常コマンド登録の区別が必要 TBD */
**			DeleteCommandFileExecQueueFile(); /* TBD */
**		}
#endif
		break;
#if (PRO_CONTINUOUS_POLLING == ENABLE)	/* 連続ポーリング処理追加　1996/10/18　Eguchi */
	/*******************************************************************
	 * 連続ポーリングコマンド消去操作実行
	 * 別に分ける必要はないのですが、切り分けやすいように一応わけました
	 ******************************************************************/
	case MSG_ERASE_CONTINUOUS_POLLING:	/** 連続ポーリングコマンド消去実行 */
 #if (PRO_MULTI_LINE == ENABLE)	/* 1997/03/06 Y.Matsukuma */
		MAN_MltFaxComStop();
 #else
		if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) &&
			(SYS_FaxComType == SYS_COMMAND_EXECUTE)){
			/* 通信中の場合 *//*CommnadErasedのフラグはいらない */
			if (SYS_CurrentExecutingCommand->Status == SYS_EXEC_ERASED) {	/* 実行中のコマンドを消去 */
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_FAXCOM;
			}
		}
		else {
			DeleteContinuousPollingCommand();
		}
 #endif
		break;
#endif
	/****************************************************************/
	/* オペレーション・タスク-フック/保留ボタン操作					*/
	/****************************************************************/
	case MSG_INTER_CALL_START:					/* Add by TH92115 1994/06/02 */
		/*--------------------------------*/
		/*	TEL1からの内線呼出を行います  */
		/*--------------------------------*/
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |=  SYS_LINE_BUSY;
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_INTER_CALL;		/* 内線呼出中セット */
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = MSG_TEL1_INTER_CALLING_START;
		snd_msg(mbxno.NCU_TelephoneOperationTask, &MainTaskMessage);
		break;
	case MSG_HOLD_TRANS_START:					/* Add by TH92115 1994/06/02 */
		/*--------------------------------*/
		/*	TEL1からの保留転送を行います  */
		/*--------------------------------*/
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_HOLD_TRANSFER;		/* 保留転送中セット */
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = MSG_TEL1_HOLD_TRANSFER_START;
		snd_msg(mbxno.NCU_TelephoneOperationTask, &MainTaskMessage);
		break;
	/****************************************************************/
	/* オペレーション・タスク-手動送信操作							*/
	/****************************************************************/
	case MSG_MANUAL_TX:
		if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
			/*--------------------------*/
			/*	指令送信が起動された	*/
			/*--------------------------*/
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY; /* スキャナ使用中セット	  以上２行追加 1994/05/17 Y.Murata */

			if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_IDLE) {
				/* 手動送信時の属性 1997/01/27 Y.Murata */
				SYS_ScannerTxAbility0 = SYS_MemorySwitch[10];
				SYS_ScannerTxAbility1 = SYS_MemorySwitch[11];
				SYS_ScannerTxAbility2 = SYS_MemorySwitch[12];
				SYS_ScannerTxAbility3 = SYS_MemorySwitch[13];
				/* 個別属性セーブ */
				SYS_FaxComAbility0[0] = SYS_MemorySwitch[10];
				SYS_FaxComAbility1[0] = SYS_MemorySwitch[11];
				SYS_FaxComAbility2[0] = SYS_MemorySwitch[12];
				SYS_FaxComAbility3[0] = SYS_MemorySwitch[13];

				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK
															 + SYS_BRANCH_OFF_HOOK
															 + SYS_HOOK_KEY_OFF_HOOK
															 + SYS_TAD
															 + SYS_DIAL_IN
															 + SYS_INTER_COM
															 + SYS_INTER_CALL
															 + SYS_LINE_HOLD
															 + SYS_HOLD_TRANSFER
															 + SYS_TRIPLE_COM);

				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = MSG_ISSEI_TX;	/* 指令起動信号による一斉指令送信 */
				snd_msg(mbxno.MDM_Task, &MainTaskMessage);
			}
			break;
		}
		else {
			/*--------------------------*/
			/*	手動送信が起動された	*/
			/*--------------------------*/
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_LINE_BUSY); /* 多機能電話で回線使用中セットされているがとりあえずここで強引にクリア */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/3 */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_HOOK_KEY_OFF_HOOK;
#if !defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/21 */
			SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	標準ライン通信中	*/
#endif /* defined (KEISATSU) */
#endif
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY; /* スキャナ使用中セット	  以上２行追加 1994/05/17 Y.Murata */
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/21 */
			if (SYS_STD_LINE_COM == SYS_InternalLineNumber) {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL1_OFF_HOOK;
			}
			else {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL2_OFF_HOOK;
			}
			
			if (CMN_CheckTwiceLineEnable(SYS_InternalLineNumber)) { 					/* 回線使用可能か確認 */
#else /* !defined (KEISATSU) */
			if (CMN_CheckLineEnable()) { /* 回線使用可能か確認 */ /* 内蔵モデムがない場合はＦ１５０を参照してね */
#endif /* defined (KEISATSU) */
				/* 受領証受信時に代行受信ｷｰﾌﾟﾅﾝﾊﾞｰを覚えておく1997/03/19  By T.Yamaguchi */
				if (SYB_ConfirmationReportSwitch == RCR_REQUEST) {
					/* SYB_MemoryRxPrintWritePoint = (UBYTE)(CMN_GetMultiLineReceiveNumber((UBYTE)0)); */
					SYB_MemoryRxPrintWritePoint = (UBYTE)(MAN_GetMultiLineReceiveNumber((UBYTE)0));
					if (SYB_MemoryRxPrintWritePoint == 0xFF) {
						/* Nothing */
						/* SaveReturnAddressAndJumpBegin(); */	/* ここに来るのはおかしい */
					}
				}
				/* 手動送信時の属性 1997/01/27 Y.Murata */
				SYS_ScannerTxAbility0 = SYS_MemorySwitch[10];
				SYS_ScannerTxAbility1 = SYS_MemorySwitch[11];
				SYS_ScannerTxAbility2 = SYS_MemorySwitch[12];
				SYS_ScannerTxAbility3 = SYS_MemorySwitch[13];
				/* 個別属性セーブ */
				SYS_FaxComAbility0[0] = SYS_MemorySwitch[10];
				SYS_FaxComAbility1[0] = SYS_MemorySwitch[11];
				SYS_FaxComAbility2[0] = SYS_MemorySwitch[12];
				SYS_FaxComAbility3[0] = SYS_MemorySwitch[13];

				SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE); /* 多機能電話使用中をクリア */
				/* 多機能電話ステータス全てクリア */
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/21 */
				if (SYS_STD_LINE_COM == SYS_InternalLineNumber) {
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL1_OFF_HOOK;
				}
				else {
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL2_OFF_HOOK;
				}
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_BRANCH_OFF_HOOK
#else /* !defined (KEISATSU) */
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK
															 + SYS_TEL2_OFF_HOOK
															 + SYS_BRANCH_OFF_HOOK
#endif /* defined (KEISATSU) */
															 + SYS_HOOK_KEY_OFF_HOOK
															 + SYS_TAD
															 + SYS_DIAL_IN
															 + SYS_INTER_COM
															 + SYS_INTER_CALL
															 + SYS_LINE_HOLD
															 + SYS_HOLD_TRANSFER
															 + SYS_TRIPLE_COM);
#if (PRO_FBS == ENABLE)
				/* POPLAR_B の手動送信はADFだけです T.Nose 1997/10/17 */
				SYS_ScannerExecMode = SCN_ADF;
#endif

				del_tsk(&tskno_NCU_TelephoneOperation);
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY); /* CI検出中クリア */
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY; /* 回線使用中セット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXCOM; /* 通信実行中セット */

				cre_tsk(&tskno_FCM_Task, TSK_FCM_TASK, 0); /* 通信タスク起動 */
				MainTaskMessage.Item = FROM_MAIN;
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/08/11 */
				if (SYS_InternalLineNumber == SYS_EXT_LINE_COM && 
					FCM_ExecutingS1Info.Protocol == SYS_PROTOCOL_ISSEI) {
					MainTaskMessage.Message = SYS_ISSEI_TX; /* 一斉指令送信 */
				}
				else {
					MainTaskMessage.Message = SYS_MANUAL_TX; /* 手動送信を指定 */
				}
#else
				MainTaskMessage.Message = SYS_MANUAL_TX; /* 手動送信を指定 */
#endif		/* End of (defined (KEISATSU)) */
				MainTaskMessage.SubMessage1 = 0;
				snd_msg(mbxno.FCM_Task, &MainTaskMessage);
			}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/21 */
			else {
				if (SYS_STD_LINE_COM == SYS_InternalLineNumber) {
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_TEL1_OFF_HOOK;
				}
				else {
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_TEL2_OFF_HOOK;
				}
			}
#endif /* defined (KEISATSU) */

		}

		break;
	/****************************************************************/
	/* オペレーション・タスク-手動受信操作　						*/
	/****************************************************************/
	case MSG_MANUAL_RX:
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_LINE_BUSY); /* 多機能電話で回線使用中セットされているがとりあえずここで強引にクリア 1994/05/17 Y.Murata */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/3 */
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_HOOK_KEY_OFF_HOOK;
#if !defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/21 */
		SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	標準ライン通信中	*/
#endif /* defined (KEISATSU) */
#endif
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/21 */
		if (SYS_STD_LINE_COM == SYS_InternalLineNumber) {
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL1_OFF_HOOK;
		}
		else {
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL2_OFF_HOOK;
		}
		if (CMN_CheckTwiceLineEnable(SYS_InternalLineNumber)) { /* 回線使用可能か確認 */
#else /* !defined (KEISATSU) */
		if (CMN_CheckLineEnable()) { /* 回線使用可能か確認 */
#endif /* defined (KEISATSU) */
			/* SYB_MemoryRxPrintWritePoint = (UBYTE)(CMN_CheckMultiLineReceiveNumber((UBYTE)0, MANUAL_RECEIVE)); */
			/* if (SYB_MemoryRxPrintWritePoint != 0xFF) { */
			mem_rx_no = (UBYTE)(MAN_CheckMultiLineReceiveEnable((UBYTE)0, MANUAL_RECEIVE));
  #if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/11/11 */
	#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
			if (QueryAutoCalledEnable(1)) {	/* changed by H.Hirao Dec.29.1998 */
	#else
  			if ((mem_rx_no < SYS_MEMORY_RX_MAX) || QueryPRxEnable()) {
	#endif
  #else
    #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.8 K.Kawata */
	  		if ((mem_rx_no < SYS_MEMORY_RX_MAX) || (QueryPRxEnable() && QueryWarpAndSecurityDisable())) {
    #else
			if (mem_rx_no < SYS_MEMORY_RX_MAX) {
    #endif
  #endif
				/* 個別属性セーブ */
				SYS_FaxComAbility0[0] = SYS_MemorySwitch[10];
				SYS_FaxComAbility1[0] = SYS_MemorySwitch[11];
				SYS_FaxComAbility2[0] = SYS_MemorySwitch[12];
				SYS_FaxComAbility3[0] = SYS_MemorySwitch[13];

				SYB_MemoryRxPrintWritePoint = mem_rx_no;	/* 1997/02/10 Y.Murata */
				SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE); /* 多機能電話使用中をクリア */
				/* 多機能電話ステータス全てクリア */
			/* 多機能電話ステータス全てクリア */
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/21 */
				if (SYS_STD_LINE_COM == SYS_InternalLineNumber) {
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL1_OFF_HOOK;
				}
				else {
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL2_OFF_HOOK;
				}
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_BRANCH_OFF_HOOK
#else /* !defined (KEISATSU) */
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK
															 + SYS_TEL2_OFF_HOOK
															 + SYS_BRANCH_OFF_HOOK
#endif /* defined (KEISATSU) */
															 + SYS_HOOK_KEY_OFF_HOOK
															 + SYS_TAD
															 + SYS_DIAL_IN
															 + SYS_INTER_COM
															 + SYS_INTER_CALL
															 + SYS_LINE_HOLD
															 + SYS_HOLD_TRANSFER
															 + SYS_TRIPLE_COM);
				del_tsk(&tskno_NCU_TelephoneOperation);
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY); /* CI検出中クリア */
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY; /* 回線使用中セット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXCOM; /* 通信実行中セット */
#if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/11/11 */
				/*
				** プリンタ受信する可能性のあるときだけSYS_PRINTER_BUSYをセットします
				** 1999/02/22 by H.Hirao
				*/
 #if (0)
 //				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;/* プリンタ使用中セット */
 #else
				if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) ||	(CHK_UNI_V34ReceiveType() != V34_MRX_TO_MRX)) {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
				}
 #endif
#endif

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/02 */
** #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1996/11/13 */
** 				CMN_GetPollingDocRight(SYS_SEND_INTERNAL_LINE);
** #endif
#else
				CMN_GetPollingDocRight(SYS_SEND_INTERNAL_LINE);
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/5 K.Kawata*/
				PRN_ChechRxPrintCallProc();
#endif

				cre_tsk(&tskno_FCM_Task, TSK_FCM_TASK, 0); /* 通信タスク起動 */
				MainTaskMessage.Item = FROM_MAIN;
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/08/11 */
				if (SYS_InternalLineNumber == SYS_EXT_LINE_COM && 
					FCM_ExecutingS1Info.Protocol == SYS_PROTOCOL_ISSEI) {
					MainTaskMessage.Message = SYS_ISSEI_RX; /* 一斉指令受信 */
				}
				else {
					MainTaskMessage.Message = SYS_MANUAL_RX; /* 手動受信を指定 */
				}
#else
				MainTaskMessage.Message = SYS_MANUAL_RX; /* 手動受信を指定 */
#endif		/* End of (defined (KEISATSU)) */
				MainTaskMessage.SubMessage1 = 0;
				snd_msg(mbxno.FCM_Task, &MainTaskMessage);
			}
			else {	/* メモリフルまたは、代行受信フル */
#if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/12/29 */
				/* メモリは有るのに、原稿蓄積中は、着信しない場合、代行受信管理バッファをつかみっぱなしになる
				*/
				if (mem_rx_no < SYS_MEMORY_RX_MAX) {
					SYB_MemoryRxPrint[mem_rx_no].Status = SYS_MEMORY_RX_EMPTY;
				}
#endif
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY; /* 多機能電話で回線使用中セットされているがとりあえずここで強引にクリア 1994/05/17 Y.Murata */
			}
		}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/21 */
		else {
			if (SYS_STD_LINE_COM == SYS_InternalLineNumber) {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_TEL1_OFF_HOOK;
			}
			else {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_TEL2_OFF_HOOK;
			}
		}
#endif /* defined (KEISATSU) */
		break;
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
	case MSG_CLASS1_MANUAL_RX:
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_LINE_BUSY); /* 多機能電話で回線使用中セットされているがとりあえずここで強引にクリア 1994/05/17 Y.Murata */
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE); /* 多機能電話使用中をクリア */
		/* 多機能電話ステータス全てクリア */
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK
														 + SYS_TEL2_OFF_HOOK
														 + SYS_BRANCH_OFF_HOOK
														 + SYS_HOOK_KEY_OFF_HOOK
														 + SYS_TAD
														 + SYS_DIAL_IN
														 + SYS_INTER_COM
														 + SYS_INTER_CALL
														 + SYS_LINE_HOLD
														 + SYS_HOLD_TRANSFER
														 + SYS_TRIPLE_COM);
		del_tsk(&tskno_NCU_TelephoneOperation);
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY); /* CI検出中クリア */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY; 		/* 回線使用中セット */
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM; 			/* 通信実行中セット */
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = CL1_MANUAL_RX_REQ;
		snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		break;
#endif  /* PRO_CL1_TELFAX_LAN == ENABLE */

	/****************************************************************/
	/* オペレーション・タスク-手動ポーリング操作 7/15/1994	桐、椛	*/
	/****************************************************************/
	case MSG_MANUAL_POLLING:
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_LINE_BUSY); /* 多機能電話で回線使用中セットされているがとりあえずここで強引にクリア 1994/05/17 Y.Murata */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/3 */
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_HOOK_KEY_OFF_HOOK;
#if !defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/21 */
		SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	標準ライン通信中	*/
#endif /* defined (KEISATSU) */
#endif
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/21 */
		if (SYS_STD_LINE_COM == SYS_InternalLineNumber) {
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL1_OFF_HOOK;
		}
		else {
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL2_OFF_HOOK;
		}
		if (CMN_CheckTwiceLineEnable(SYS_InternalLineNumber)) { /* 回線使用可能か確認 */
#else /* !defined (KEISATSU) */
		if (CMN_CheckLineEnable()) { /* 回線使用可能か確認 */
#endif /* defined (KEISATSU) */
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE); /* 多機能電話使用中をクリア */
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/21 */
			if (SYS_STD_LINE_COM == SYS_InternalLineNumber) {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL1_OFF_HOOK;
			}
			else {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL2_OFF_HOOK;
			}
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_BRANCH_OFF_HOOK
#else /* !defined (KEISATSU) */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK
														 + SYS_TEL2_OFF_HOOK
														 + SYS_BRANCH_OFF_HOOK
#endif /* defined (KEISATSU) */
														 + SYS_HOOK_KEY_OFF_HOOK
														 + SYS_TAD
														 + SYS_DIAL_IN
														 + SYS_INTER_COM
														 + SYS_INTER_CALL
														 + SYS_LINE_HOLD
														 + SYS_HOLD_TRANSFER
														 + SYS_TRIPLE_COM); /* 多機能電話ステータス全てクリア */
			del_tsk(&tskno_NCU_TelephoneOperation);
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY); /* CI検出中クリア */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY; /* 回線使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXCOM; /* 通信実行中セット */
#if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/11/11 */
			/*
			** プリンタ受信する可能性のあるときだけSYS_PRINTER_BUSYをセットします
			** 1999/02/22 by H.Hirao
			*/
 #if (0)
 //			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;/* プリンタ使用中セット */
 #else
			if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) ||	(CHK_UNI_V34ReceiveType() != V34_MRX_TO_MRX)) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;/* プリンタ使用中セット */
			}
 #endif
#endif

			cre_tsk(&tskno_FCM_Task, TSK_FCM_TASK, 0); /* 通信タスク起動 */
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = SYS_MANUAL_POLLING; /* 手動受信を指定 */
			MainTaskMessage.SubMessage1 = 0;
			snd_msg(mbxno.FCM_Task, &MainTaskMessage);
		}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/21 */
		else {
			if (SYS_STD_LINE_COM == SYS_InternalLineNumber) {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_TEL1_OFF_HOOK;
			}
			else {
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_TEL2_OFF_HOOK;
			}
		}
#endif /* defined (KEISATSU) */
		break;
	/****************************************************************/
	/* オペレーション・タスク-メモリ・オーバー時の登録操作			*/
	/****************************************************************/
	case MSG_MEMORY_OVER_ENTER:	/* メモリ・オーバー時の登録 */
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_MEMORY_OVER_OPR);
		switch (SYS_DocumentStoreItem)	{ /* 原稿の種別を解析 */
		case SYS_MEM_TX_FILE: /* メモリ送信ファイル */
			if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) { /* １ペ-ジ以上蓄積されていれば */
				MemoryTxDocStoreOK(SYS_COMMAND_TRX); /* メモリ送信コマンド・ファイルの登録 */
			}
			else {
				MemoryTxDocStoreNG(SYS_COMMAND_TRX);
				MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber); /* 蓄積原稿の消去、作業中のファイルも含めて */
			}
			break;
		case SYS_MEM_MULTI_COPY_FILE: /* マルチ・コピーファイル */
			if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYB_MultiCopyReadPoint, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) { /* 1ページ以上蓄積されていれば */
				MultiCopyDocStoreOK(); /* マルチ・コピー・ファイルの登録 TBD */
			}
			else {
				MultiCopyDocStoreNG();
				MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去、作業中のファイルも含めて */
			}
			break;
		case SYS_MEM_MANUAL_COPY_FILE: /* 手差し・コピーファイル */
			if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) { /* 1ページ以上蓄積されていれば */
				ManualCopyDocStoreOK(); /* 手差し・コピー・ファイルの登録 TBD */
			}
			else {
				ManualCopyDocStoreNG();
				MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去、作業中のファイルも含めて */
			}
			break;
		case SYS_MEM_POLLING_FILE: /* ポ-リング・ファイル */
			SYB_PollingDocumentStatus = 1; /* ポーリング原稿有りセット */

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
** #if (PRO_MULTI_LINE == ENABLE)
** 			SYB_PollingDocExclusiveFlag = SYS_EXIST_AND_NO_SENDING;	/* ポーリング原稿があるかどうかの変数 */
** #endif
#else
			SYB_PollingDocExclusiveFlag = SYS_EXIST_AND_NO_SENDING;	/* ポーリング原稿があるかどうかの変数 */
#endif

			break;
		case SYS_MEM_DB_POLLING_FILE: /* 検索ポーリング・ファイル */
			SYB_DB_PollingDocumentStatus = 1; /*  検索ポーリング有りセット */
			break;
#if (PRO_BATCH_TX == ENABLE)
		case SYS_MEM_BATCH_TX_FILE1: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE2: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE3: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE4: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE5: /** 一括送信原稿なら */
			/*
			** MEM_CountTotalPage()の戻り値は次の通り。原稿の有無確認方法変更。
			** 原稿無し：MEM_NO_INDEX(0xFFFF)
			** 原稿有り：０以外のページ数
			** By S.Kawasaki 1996/08/10
			*/
			/* if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER) ) { @* １ペ-ジ以上蓄積されていれば By S.Kawasaki 1996/08/10 */
			if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) { /* １ペ-ジ以上蓄積されていれば */
				MemoryTxDocStoreOK(SYS_BATCH_TX); /* 一括送信コマンド・ファイルの登録 */
			}
			else {
				MemoryTxDocStoreNG(SYS_BATCH_TX);
				MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去、作業中のファイルも含めて */
			}
			break;
#endif
#if (PRO_CLASS1 == ENABLE)
		case SYS_MEM_CLASS1_TX_FILE:
			/*
			** MEM_CountTotalPage()の戻り値は次の通り。原稿の有無確認方法変更。
			** 原稿無し：MEM_NO_INDEX(0xFFFF)
			** 原稿有り：０以外のページ数
			** By S.Kawasaki 1996/08/10
			*/
			/* if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER) ) { @* １ペ-ジ以上蓄積されていれば By S.Kawasaki 1996/08/10 */
			if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX ) { /* １ペ-ジ以上蓄積されていれば */
				SYB_CL1_LocalScanDocStatus = 1; /**ローカルスキャン原稿有りセット *//*1996/09/24 Eguchi */
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = CL1_SCAN_REQ;
				MainTaskMessage.SubMessage1 = SYS_CLASS1_SCAN_MEMORY;
				snd_msg(mbxno.CL1_Task, &MainTaskMessage);
			}
			else {
				SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FAXMODEM; /** CLASS1動作中クリア	*/
				MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
			}
			break;
#endif
#if (PRO_F_CODE == ENABLE)	/* 1997/03/11  By T.Yamaguchi */
		case SYS_MEM_SUB_BULLETIN_FILE:	/* Ｆコード原稿蓄積起動 */
			if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber) != MEM_NO_INDEX) { /* １ペ-ジ以上蓄積されていれば */
				FcodeDocStoreOK(SYS_DocumentStoreBoxNumber);
			}
			else {
				MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber); /* 蓄積原稿の消去、作業中のファイルも含めて */
				FcodeDocStoreNG(SYS_DocumentStoreBoxNumber);
			}
			break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
		case SYS_MEM_MAIL_TX_FILE: /* メモリ送信ファイル */
			if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {
				MailTxDocStoreOK();
			}
			else {
				MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
				MailTxDocStoreNG();
			}
			break;
#endif
		default: /* 有り得ない */
			break;
		}
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_SCANNER_BUSY; /* スキャナー使用中解除 */
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_DOC_STORE; /* 蓄積中解除 */
		break;
	/****************************************************************/
	/* オペレーション・タスク-メモリ・オーバー時キャンセル操作		*/
	/****************************************************************/
	case MSG_MEMORY_OVER_CANCEL:
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_MEMORY_OVER_OPR);
		switch (SYS_DocumentStoreItem) { /* 原稿の種別を解析 */
		case SYS_MEM_TX_FILE: /* メモリ送信ファイル */
			MemoryTxDocStoreNG(SYS_COMMAND_TRX);
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber); /* 蓄積原稿の消去、作業中のファイルも含めて */
			break;
#if (PRO_BATCH_TX == ENABLE)
		case SYS_MEM_BATCH_TX_FILE1: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE2: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE3: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE4: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE5: /** 一括送信原稿なら */
			MemoryTxDocStoreNG(SYS_BATCH_TX); /** メモリ送信コマンド・ファイルのキャンセル */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /** 原稿消去 */
		break;
#endif
		case SYS_MEM_MULTI_COPY_FILE: /* マルチ・コピー・ファイル */
			MultiCopyDocStoreNG();
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去、作業中のファイルも含めて */
			break;
		case SYS_MEM_MANUAL_COPY_FILE: /* 手差し・コピー・ファイル */
			ManualCopyDocStoreNG();
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去 */
			break;
		case SYS_MEM_POLLING_FILE: /* ポーリング・ファイル */
		case SYS_MEM_DB_POLLING_FILE: /* 検索ポーリング・ファイル */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去、作業中のファイルも含めて */
			break;
#if (PRO_CLASS1 == ENABLE)
		case SYS_MEM_CLASS1_TX_FILE:
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FAXMODEM; /** CLASS1動作中クリア	*/
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
			break;
#endif
#if (PRO_F_CODE == ENABLE)	/* 1997/03/11  By T.Yamaguchi */
		case SYS_MEM_SUB_BULLETIN_FILE:	/* Ｆコード原稿蓄積起動 */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber); /* 蓄積原稿の消去、作業中のファイルも含めて */
			FcodeDocStoreNG(SYS_DocumentStoreBoxNumber);
			break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
	case SYS_MEM_MAIL_TX_FILE:
		MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
		MailTxDocStoreNG();
		break;
#endif
		default:
			break;
		}
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_SCANNER_BUSY; /* スキャナー使用中解除 */
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_DOC_STORE; /* 蓄積中解除 */
		break;
	/****************************************************************/
	/* オペレーション・タスク-メモリ・オーバー時タイム・オーバー操作*/
	/****************************************************************/
	case MSG_MEMORY_OVER_TIME_UP:
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_MEMORY_OVER_OPR);
		SYS_MachineStatus[SYS_SCANNER_STATUS] |= (SYS_SCANNER_MEMORY_OVER);
		switch (SYS_DocumentStoreItem) { /* 原稿の種別を解析 */
#if (PRO_CLASS1 == ENABLE)
		case SYS_MEM_CLASS1_TX_FILE:
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FAXMODEM; /** CLASS1動作中クリア	*/
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
			break;
#endif
		case SYS_MEM_TX_FILE: /* メモリ送信ファイル */
			MemoryTxDocStoreNG(SYS_COMMAND_TRX);
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber); /* 蓄積原稿の消去、作業中のファイルも含めて */
			if (CHK_UNI_MemoryOverMessagePrint()) { /** メモリ・オーバー・メッセージ印字ON? */
													/* UNI->Ｎｅｗ　Ｍｅｍｏｒｙ　Ｓｗｉｔｃｈ対応 */
				SYS_MemoryOverListRequest = 1;
			}
			break;
#if (PRO_BATCH_TX == ENABLE) /* Added by T.Nose 1995.03.09 */
		case SYS_MEM_BATCH_TX_FILE1: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE2: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE3: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE4: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE5: /** 一括送信原稿なら */
			MemoryTxDocStoreNG(SYS_BATCH_TX); /** メモリ送信コマンド・ファイルのキャンセル */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /** 原稿消去 */
			if (CHK_UNI_MemoryOverMessagePrint()) { /** メモリ・オーバー・メッセージ印字ON? */
													/* UNI→New Memory Switch 対応 1996/04/16 Eguchi */
				SYS_MemoryOverListRequest = 1;
			}
		break;
#endif
		case SYS_MEM_POLLING_FILE: /* ポーリング・ファイル */
		case SYS_MEM_DB_POLLING_FILE: /* 検索ポーリング・ファイル */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去、作業中のファイルも含めて */
			if (CHK_UNI_MemoryOverMessagePrint()) { /** メモリ・オーバー・メッセージ印字ON? */
													/* UNI→New Memory Switch 対応 1996/04/16 Eguchi */
				SYS_MemoryOverListRequest = 1;
			}
			break;
		case SYS_MEM_MULTI_COPY_FILE: /* マルチ・コピーファイル */
			/*
			** MEM_CountTotalPage()の戻り値は次の通り。原稿の有無確認方法変更。
			** 原稿無し：MEM_NO_INDEX(0xFFFF)
			** 原稿有り：０以外のページ数
			** By S.Kawasaki 1996/08/10
			*/
			/* if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYB_MultiCopyReadPoint, MEM_IGNORE_BOX_NUMBER) ) { @* 1ページ以上蓄積されていれば By S.Kawasaki 1996/08/10 */
			if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYB_MultiCopyReadPoint, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX ) { /* 1ページ以上蓄積されていれば */
				MultiCopyDocStoreOK();
			}
			else {
				MultiCopyDocStoreNG();
				MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去、作業中のファイルも含めて */
			}
			break;
		case SYS_MEM_MANUAL_COPY_FILE: /* 手差し・コピーファイル */
			if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX ) { /* 1ページ以上蓄積されていれば */
				ManualCopyDocStoreOK();
			}
			else {
				ManualCopyDocStoreNG();
				MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿の消去、作業中のファイルも含めて */
			}
			break;
#if (PRO_F_CODE == ENABLE)	/* 1997/03/11  By T.Yamaguchi */
		case SYS_MEM_SUB_BULLETIN_FILE:	/* Ｆコード原稿蓄積起動 */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber); /* 蓄積原稿の消去、作業中のファイルも含めて */
			FcodeDocStoreNG(SYS_DocumentStoreBoxNumber);
			if (CHK_UNI_MemoryOverMessagePrint()) { /** メモリ・オーバー・メッセージ印字ON? */
				SYS_MemoryOverListRequest = 1;
			}
			break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
		case SYS_MEM_MAIL_TX_FILE:
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
			MailTxDocStoreNG();
			break;
#endif
		default: /* 有り得ない */
			break;
		}
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_SCANNER_BUSY; /* スキャナー使用中解除 */
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_DOC_STORE; /* 蓄積中解除 */
		break;
	/****************************************************************/
	/* オペレーション・タスク-ダイアル・イン番号登録操作　　		*/
	/****************************************************************/
	case MSG_DIAL_IN_NUMBER_STORE:
		SYS_MachineStatus[SYS_ERROR_STATUS] &= ~(SYS_ERROR_NO_DIAL_IN_NUMBER); /* ダイアル・イン番号無しエラーをクリア */
		break;
	/****************************************************************/
	/* オペレーション・タスク-原稿排出操作　　　　　　				*/
	/****************************************************************/
	case MSG_FEED_OUT_DOC:
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_FEED_ERROR; /* スキャナーフィードエラーを解除 */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;		  /* スキャナー使用中をセット */
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FEED_OUT;			  /* イメージ・プリント中セット */
		cre_tsk(&tskno_DocumentOutTask, TSK_MAN_DOCUMENTOUTTASK, 0);  /* 原稿排出タスク起動	 */
		break;
	case MSG_SERV_FEED_OUT_DOC: /* 取り敢えず椛のみ */
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_FEED_ERROR;	/* スキャナーフィードエラーを解除 */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;			/* スキャナー使用中をセット */
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FEED_OUT;				/* イメージ・プリント中セット */
		cre_tsk(&tskno_SCN_StampTestTask, TSK_SCN_DOCUMENTOUTTESTTASK, 0);	/* 原稿排出テストタスク起動 */
		break;
	case MSG_SERV_STAMP_TEST:
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_FEED_ERROR;	/* スキャナーフィードエラーを解除 */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;			/* スキャナー使用中をセット */
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FEED_OUT;				/* イメージ・プリント中セット */
		cre_tsk(&tskno_SCN_StampTestTask, TSK_SCN_STAMPTESTTASK, 0);		/* スタンプ・テストタスク起動	 */
		break;
	case MSG_SERV_RS232C_TEST:
#if (PRO_CLASS1 == ENABLE)	/* Add By Y.Tanimoto 96.04.09 */
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = CL1_TEST_CMD;
		MainTaskMessage.SubMessage1 = opr_sub_message1;
		snd_msg(mbxno.CL1_Task, &MainTaskMessage);
#endif
		break;
	case MSG_SERV_AUTO_INIT:
#if (PRO_CLASS1 == ENABLE)	/* Add By Y.Tanimoto 96.04.09 */
	/*	if ((SYS_CL1_RxEnableFlag == 1) && (SYS_CL1_Status == CL1_IDLE)) @ */
	/*	if ((SYS_CL1_RxEnableFlag == 1) && (SYS_CL1_Status == 0)) @↓に変更　1996/09/24 */
 #if (PRO_RS_INTERNAL == ENABLE)
		/* クラス１のデュアル制限を行う by H.Hirao 1999/02/01 */
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM)
		&&	(SYS_CL1_RxEnableFlag == 1)
		&&	(SYS_CL1_Status == 0)
		&&	QueryClass1Enable(2)) {
 #else
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM)
		&&	(SYS_CL1_RxEnableFlag == 1)
		&&	(SYS_CL1_Status == 0)) {
 #endif
			SYS_MachineStatus[SYS_ERROR_STATUS] &= ~SYS_ERROR_CLASS1_INIT;/*1996/09/20 Eguchi */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM; /*1996/09/17 Eguchi */
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = CL1_INIT_REQ;
			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		}
#endif
		break;
	case MSG_SERV_START:
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY;	/* 回線使用中にセット */
		del_tsk(&tskno_NCU_Task);
		break;
	case MSG_SERV_END:
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_LINE_BUSY;	/* 回線使用中をクリア */
		cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0);
		SYS_VariableTimer = 5;			/* 1994/10/15 Y.Murata */
		break;
	case MSG_UPDATE_DISPLAY: /* 7/12/1994 */
		break;
	case MSG_PRINT_DEMO_DOC:		  /* ラベンダ:デモ用ﾄﾞｷｭﾒﾝﾄﾌﾟﾘﾝﾄ 1994/08/23 Y.Murata */
		break;
#if (PRO_SECURITY_RX == ENABLE)
	/*************************************/
	/* セキュリティ受信機能追加			 */
	/* 1996/04/27 Eguchi				 */
	/*************************************/
	case MSG_PRINT_PROTECT_OFF:		  /* 受信原稿プリント要求 1995/12/23 Eguchi */
		/** プロテクト設定の状態でメモリー内にある原稿のプリント */
		/* プロテクトを解除する */
		AllClearPrintProtect();
#endif
		break;
#if (PRO_CLASS1 == ENABLE)	/* by Y.Tanimoto 1996/06/26 */
	/****************************************************************/
	/* オペレーション・タスク-ローカルスキャン原稿蓄積起動処理		*/
	/****************************************************************/
	case MSG_STORE_CLASS1_TX_DOC:
	/*	if ((SYS_CL1_RxEnableFlag == 1) && (SYS_CL1_Status == CL1_IDLE)*/
	/*	if ((SYS_CL1_RxEnableFlag == 1) && (SYS_CL1_Status == 0)*/
 #if (PRO_RS_INTERNAL == ENABLE)
		/* クラス１のデュアル制限を行う by H.Hirao 1999/02/01 */
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM)
		 && (SYS_CL1_RxEnableFlag == 1) && (SYS_CL1_Status == 0)
		 && CMN_CheckScanEnable() && CMN_CheckFeederCommandEmpty() && QueryClass1Enable(2)) { /* スキャナーーが未使用であれば*/
 #else
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM)
		 && (SYS_CL1_RxEnableFlag == 1) && (SYS_CL1_Status == 0)
		 && CMN_CheckScanEnable() && CMN_CheckFeederCommandEmpty()) { /* スキャナーーが未使用であれば*/
 #endif
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM;	/* CLASS1動作中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FEED_IN;
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= (SYS_SCANNER_BUSY); /* スキャナー資源確保*/
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_DOC_STORE; /* 原稿蓄積をセット */
			SYS_DocumentStoreItem = SYS_MEM_CLASS1_TX_FILE;
			SYS_DocumentStoreNo	  = 0;
			SYS_DocumentStorePage = 1;
			SYS_MultiProgramFlag = 0;
			CL1_TxMemoryFileItem = SYS_MEM_CLASS1_TX_FILE;
			CL1_TxMemoryFileNo[0] = 0;
			CL1_TxMemoryFilePage = 1;

 #if (PRO_FBS == ENABLE)		/* FBSからのﾛｰｶﾙｽｷｬﾝ処理追加  By S.Fukui Jan.27,1998 */
			if (CMN_CheckDocumentOnFeeder() == TRUE) {
				SYS_ScannerExecMode = SCN_ADF;
				MirrorTaskInstruction = MIRROR_TASK_TO_ADF;
				if (CHK_UNI_MirrorReadyModeVariable()) {
					SCN_MirrorReadyPosition = READY_POSITION_ADF;
				}
			}
			else {
				SYS_ScannerExecMode = SCN_FBS;
				MirrorTaskInstruction = MIRROR_TASK_TO_FBS;
			}

			/** ミラーを読み取り開始位置へ移動させる */
			SYS_IsMirrorScanReady = FALSE;
			MirrorTaskRequest = TRUE;

 #endif /* (PRO_FBS == ENABLE) */


#if (PRO_IMAGE_PROCESSOR != IMAGE_PROCESSOR_LC82103)	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
			SCN_Init(); /* 追加 T.Nose 1997/10/02 */
#endif

			cre_tsk(&tskno_SCN_DocumentStoreTask, TSK_SCN_TASK, 0); /* 原稿蓄積タスク起動 */
		}
		break;
#endif
	case MSG_SERV_SHADING_START:	/** 手動シェーディング取り込み開始 */
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~(SYS_SCANNER_LAMP_ERROR);
#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)	/* 1998/09/29 by T.Soneoka */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_DOC_STORE;
		cre_tsk(&tskno_SCN_GetShade, TSK_SCN_GETSHADETASK, 0);
#else
 #if (PRO_FBS == ENABLE)	/* POPLAR_B FBS用手動シェーディング取り込み */
		/** ミラーキャリッジをADF読み取り位置へ移動させる */
		MirrorTaskInstruction = MIRROR_TASK_TO_ADF;
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
		SYS_IsMirrorScanReady = FALSE;
		MirrorTaskRequest = TRUE;	/* ミラータスク起動方法を変更  1996/11/20 */
 #endif
#endif
		break;
	case MSG_SERV_SHADING_END:		/** 手動シェーディング取り込み終了 */
#if (PRO_FBS == ENABLE)	/* POPLAR_B FBS用手動シェーディング取り込み */
		/* ＡＤＦに原稿をセットした時、ＡＤＦ側でミラーが止まらなくなる件
		** ミラーを初期化する T.Nose 1997/12/20
		*/
		if ((SYB_MaintenanceSwitch[MNT_SW_C0] & MIRROR_MOVE_FORCE_END)
		 && (DEBUG_OperationExitFlag == 1)) {
			DEBUG_OperationExitFlag = 0;
			/* エラーの場合、ミラータスクの終了処理で初期化要求を出すので
			** ここでは何もしない
			*/
			break;
		}

		/** ミラーキャリッジを待機位置へ移動させる(初期化) */
		if (SCN_MirrorReadyPosition == READY_POSITION_ADF) { /* ＡＤＦ待機位置設定の場合 */
			MirrorTaskInstruction = MIRROR_TASK_TO_ADF_READY; /* ＡＤＦ待機位置へ移動 */
		}
		else { /* ＦＢＳ待機位置設定の場合 */
			MirrorTaskInstruction = MIRROR_TASK_TO_READY; /* ＦＢＳ待機位置へ移動 */
		}
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
		MirrorTaskRequest = TRUE;	/* ミラータスク起動方法を変更  1996/11/20 */
#endif
		break;
	/******************************************/
	/* ジャムリカバー／次原稿ＯＰ蓄積起動処理 */
	/******************************************/
	case MSG_SCAN_CONT_START:
		if (timer_next_scan_complete != 0xff) {
			CMN_MultiTimer10msStop(&timer_next_scan_complete);
		}
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_NEXT_SCAN_START;
#if (PRO_PANEL == KANJI)
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_OPERATE)) {
			InitializeSoftKey(WAIT_STATE);
		}
#endif

#if (PRO_FBS == ENABLE)
		if (DS1()) {
			SYS_ScannerExecMode = SCN_ADF;
		}
		else {
			SYS_ScannerExecMode = SCN_FBS;
		}

		/* ミラーキャリッジタスク起動して、所定の読み取り待機位置へ移動する */
		if (SYS_ScannerExecMode == SCN_ADF) {
			MirrorTaskInstruction = MIRROR_TASK_TO_ADF;
		}
		else {
			MirrorTaskInstruction = MIRROR_TASK_TO_FBS;
		}

		/* ミラータスクが待機中の場合 */
		if (!(SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MIRROR_BUSY)) {
			/* 次原稿読取開始処理 */
			MAN_NextScanStart();
		}
#else /* PRO_FBS else */
		MAN_NextScanStart();
#endif /* PRO_FBS end */

		break;
	/******************************************/
	/* ジャムリカバー／次原稿ＯＰ蓄積終了処理 */
	/******************************************/
	case MSG_SCAN_CONT_END:
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_JAM_RECOVER_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_FBS_RECOVER_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START;
#if (PRO_PANEL == KANJI) /* POPLAR_H で必要? 1997/05/04 T.Nose */
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_OPERATE)) {
			InitializeSoftKey(WAIT_STATE);
		}
#endif
		switch (SYS_DocumentStoreItem) { /** 原稿の種別を解析 */
		case SYS_MEM_MULTI_COPY_FILE: /** マルチ・コピ・ファイル */
			MultiCopyDocStoreOK(); /** マルチ・コピー・ファイルの登録 */
			if (timer_store_copy_complete == 0xFF) {
				CMN_MultiTimer10msStart(&timer_store_copy_complete, &StoreCompleteMessage);
			}
			break;
		case SYS_MEM_MANUAL_COPY_FILE: /* 手差しコピーファイル */
			ManualCopyDocStoreOK();	/* 手差しコピーファイルの登録 */
			if (timer_store_copy_complete == 0xFF) {
				CMN_MultiTimer10msStart(&timer_store_copy_complete, &StoreCompleteMessage);
			}
			break;
		case SYS_MEM_TX_FILE: /** メモリ送信ファイル */
			/* メモリ送信コマンド・ファイルの登録 */
			MemoryTxDocStoreOK(SYS_COMMAND_TRX);
			/* 原稿蓄積完了表示起動 */
			if (timer_store_fax_complete == 0xff) {
				CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
			}
			break;
#if (PRO_BATCH_TX == ENABLE)
		case SYS_MEM_BATCH_TX_FILE1: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE2: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE3: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE4: /** 一括送信原稿なら */
		case SYS_MEM_BATCH_TX_FILE5: /** 一括送信原稿なら */
			/* 一括送信コマンド・ファイルの登録 */
			MemoryTxDocStoreOK(SYS_BATCH_TX);
			/* 原稿蓄積完了表示起動 */
			if (timer_store_fax_complete == 0xff) {
				CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
			}
			break;
#endif
		case SYS_MEM_POLLING_FILE: /** ポーリング・ファイル */
			SYB_PollingDocumentStatus = 1; /** ポーリング原稿有りセット */

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
** #if (PRO_MULTI_LINE == ENABLE)
** 			SYB_PollingDocExclusiveFlag = SYS_EXIST_AND_NO_SENDING;	/* ポーリング原稿があるかどうかの変数 */
** #endif
#else
			SYB_PollingDocExclusiveFlag = SYS_EXIST_AND_NO_SENDING;	/* ポーリング原稿があるかどうかの変数 */
#endif

			/* 原稿蓄積完了表示起動 */
			if (timer_store_fax_complete == 0xff) {
				CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
			}
			break;
		case SYS_MEM_DB_POLLING_FILE: /** 検索ポーリング・ファイル */
			SYB_DB_PollingDocumentStatus = 1; /** 検索ポーリング有りセット */
			/* 原稿蓄積完了表示起動 */
			if (timer_store_fax_complete == 0xff) {
				CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
			}
			break;
#if (PRO_F_CODE == ENABLE)
		case SYS_MEM_SUB_BULLETIN_FILE:	/* Ｆコード */
			/* Ｆコード原稿の登録 */
			FcodeDocStoreOK(SYS_DocumentStoreBoxNumber);
			/* 原稿蓄積完了表示起動 */
			if (timer_store_fax_complete == 0xff) {
				CMN_MultiTimer10msStart(&timer_store_fax_complete,&StoreCompleteMessage);
			}
		break;
#endif

#if (PRO_CIPHER == ENABLE)	/*	By Y.Suzuki 1997/07/11	*/
		case SYS_MEM_CIPHER_FILE:
			if(ScrambleOn == 1) {
				SYS_CipherComExec = SYS_CIPHER_EXEC;
				SYS_MachineStatus[SYS_CIPHER_STATUS] = SYS_SCRAMBLE_EXEC;
				CipherReadIndex.Item = SYS_DocumentStoreItem;
				CipherReadIndex.No = SYS_DocumentStoreNo;
				CipherReadIndex.Page = 1;
				CipherReadIndex.BoxNumber = 0;
				CipherData.StartPageNo = 1;
				/*	暗号化タスク起動	*/
				cre_tsk(&tskno_SCD_CipherTask,TSK_SCD_CIPHERTASK,0);
			}
			break;
#endif

#if (PRO_CLASS1 == ENABLE)	/* FBSからのﾛｰｶﾙｽｷｬﾝ処理追加  By S.Fukui Jan.27,1998 */
 #if (PRO_FBS == ENABLE)
		case SYS_MEM_CLASS1_TX_FILE:
			SYB_CL1_LocalScanDocStatus = 1; /**ローカルスキャン原稿有りセット */
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = CL1_SCAN_REQ;
			MainTaskMessage.SubMessage1 = SYS_CLASS1_SCAN_MEMORY;
			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
			break;
 #endif	/* PRO_FBS    == ENABLE */
#endif /* PRO_CLASS1 == ENABLE */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
		case SYS_MEM_MAIL_TX_FILE: /* メモリ送信ファイル */
			if (MEM_CountTotalPage(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {
				MailTxDocStoreOK();
			}
			else {
				MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
				MailTxDocStoreNG();
			}
			break;
#endif
		default:
			break;
		}

		CMN_ResetMemoyFeederTx();
		CMN_ResetStamp();

#if (0)
** 		/* ＰＯＰＬＡＲ＿Ｈには、コピー待機モードは有りません。
** 		** ＲＯＭ容量も厳しいので、少しですが以下の処理は削除します。 By O.Kimoto 1998/08/31 */
** 		if (CHK_ReadyModeCopy()) { /* コピーモードならば */
** 			if (CHK_UNI_HyperFineON()) { /** ハイパーファインである場合 */
** 				SYB_CopyModeSw = SYS_HFINE;;
** 			}
** 			else { /** スーパーファインである場合 */
** 				SYB_CopyModeSw = SYS_SFINE;;
** 			}
** 			SYB_ModeSw = SYB_CopyModeSw;
** 		}
** 		else {
** 			CMN_ResetPrimaryMode();
** 		}
#else
 #if (PRO_COPY_FAX_MODE == ENABLE)
		/* ＰＯＰＬＡＲ＿Ｂのみ */
		if (CHK_ReadyModeCopy()) { /* コピーモードならば */
#if (0)	/* 画質の初期化はＦＡＸモードのみ行います by K.Watanabe 1999/01/21 */
	/* この処理があると、コピー動作の内、ジャムリカバーで中止・放置した時の画質のみ
	** 初期化されると言う中途半端な仕様になるので止めます
	** （基本的に、コピー後の設定値の初期化は、１分間キー入力が無かった時のみです）
	*/
//			if (CHK_UNI_HyperFineON()) { /** ハイパーファインである場合 */
//				SYB_CopyModeSw = SYS_HFINE;;
//			}
//			else { /** スーパーファインである場合 */
//				SYB_CopyModeSw = SYS_SFINE;;
//			}
//			SYB_ModeSw = SYB_CopyModeSw;
#endif
		}
		else {
			CMN_ResetPrimaryMode();
		}
 #else
		/* ＰＯＰＬＡＲ＿Ｂ以外 */
		CMN_ResetPrimaryMode();
 #endif

#endif

		CMN_ResetPrimaryContrast(); /** 濃度のリセット処理とLEDをリセット */
		CMN_ResetConfirmationReport(); /* By S.K Sep.19,1994 */
#if (PRO_RED_SCAN == ENABLE)	/* 朱色読み取り 2002/03/05 T.Takagi */
		CMN_ResetRedScan();
#endif
#if defined (KEISATSU)		/* 警察FAX DVT_ID33 Modify by SMuratec 夏 2005/11/12 */
		ResetKeisatsuAttribute();
#endif
		switch (SYS_DocumentStoreItem) {	/** 原稿の種別を解析 */
		case SYS_MEM_TX_FILE:			/** メモリ送信ファイル */
#if (PRO_BATCH_TX == ENABLE)
		case SYS_MEM_BATCH_TX_FILE1:	/** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE2:	/** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE3:	/** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE4:	/** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE5:	/** 一括送信原稿 */
#endif
		case SYS_MEM_POLLING_FILE:		/** ポーリング・ファイル */
		case SYS_MEM_DB_POLLING_FILE:	/** 検索ポーリング・ファイル */
#if (PRO_F_CODE == ENABLE)
		case SYS_MEM_SUB_BULLETIN_FILE:	/** Ｆコード */
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
		case MSG_STORE_MAIL_TX_DOC:		/* メール用送信原稿蓄積起動		*/
		case MSG_STORE_MIXED_TX_DOC:	/* メール＆ＦＡＸ混在同報原稿蓄積起動	*/
#endif
			CMN_ResetMemoyFeederTx();
			CMN_ResetStamp();
			CMN_ResetPrimaryMode();
			CMN_ResetPrimaryContrast();
			CMN_ResetConfirmationReport();
#if (PRO_RED_SCAN == ENABLE)	/* 朱色読み取り 2002/03/05 T.Takagi */
			CMN_ResetRedScan();
#endif
#if defined (KEISATSU)		/* 警察FAX DVT_ID33 Modify by SMuratec 夏 2005/11/12 */
			ResetKeisatsuAttribute();
#endif
			break;
		case SYS_MEM_MULTI_COPY_FILE:	/** マルチ・コピー・ファイル */
		case SYS_MEM_MANUAL_COPY_FILE:	/** 手差し・コピー・ファイル */
		default:
			break;
		}
		break;
	/**************************************************/
	/* ジャムリカバー／次原稿ＯＰ蓄積原稿取り消し処理 */
	/**************************************************/
	case MSG_SCAN_CONT_ABORT:	/* 蓄積原稿取消 */
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_JAM_RECOVER_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_FBS_RECOVER_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START_OPR;
		SYS_MachineStatus[SYS_SCANNER_STATUS] &= ~SYS_SCANNER_NEXT_SCAN_START;
#if (PRO_PANEL == KANJI) /* POPLAR_H で必要? T.Nose 1997/05/08 */
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_OPERATE)) {
			InitializeSoftKey(WAIT_STATE);
		}
#endif
		switch (SYS_DocumentStoreItem) { /** 原稿の種別を解析 */
		case SYS_MEM_TX_FILE: /** メモリ送信ファイル */
#if (PRO_CIPHER == ENABLE)
		case SYS_MEM_CIPHER_FILE: /** 暗号化前原稿 Add By T.Fukumoto 1998/03/27 */
			if ((SYS_DocumentStoreItem == SYS_MEM_CIPHER_FILE) && (ScrambleOn == 0)) {
				break;
			}
			if (SYS_DocumentStoreItem == SYS_MEM_CIPHER_FILE) {/* By Y.Suzuki 1998/04/15 */
				/* 送信原稿ジャム解除オペレーションでスクランブルのステータスがオフになってた */
				/* スクランブル処理中をクリア */
				SYS_CipherComExec = 0;
				SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_SCRAMBLE_EXEC;
			}
#endif
			/** メモリ送信コマンド・ファイルのキャンセル */
			MemoryTxDocStoreNG(SYS_COMMAND_TRX);
			/** 原稿消去 */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
			break;
#if (PRO_BATCH_TX == ENABLE)
		case SYS_MEM_BATCH_TX_FILE1: /** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE2: /** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE3: /** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE4: /** 一括送信原稿 */
		case SYS_MEM_BATCH_TX_FILE5: /** 一括送信原稿 */
			/** メモリ送信コマンド・ファイルのキャンセル */
			MemoryTxDocStoreNG(SYS_BATCH_TX);
			/** 原稿消去 */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
			break;
#endif
		case SYS_MEM_MULTI_COPY_FILE: /** マルチ・コピー・ファイル */
			MultiCopyDocStoreNG();
			/** 原稿消去 */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
			break;
		case SYS_MEM_MANUAL_COPY_FILE: /* 手差し・コピーファイル */
			ManualCopyDocStoreNG();
			/** 原稿消去 */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
			break;
		case SYS_MEM_POLLING_FILE: /** ポーリング・ファイル */
		case SYS_MEM_DB_POLLING_FILE: /** 検索ポーリング・ファイル */
			/** 原稿消去 */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
			break;
#if (PRO_F_CODE == ENABLE)
		case SYS_MEM_SUB_BULLETIN_FILE:	/* Ｆコード */
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber); /* 蓄積原稿の消去、作業中のファイルも含めて */
			FcodeDocStoreNG(SYS_DocumentStoreBoxNumber);
			break;
#endif

#if (PRO_CLASS1 == ENABLE) /* FBSからのﾛｰｶﾙｽｷｬﾝ処理追加  By S.Fukui Jan.27,1998 */
 #if (PRO_FBS == ENABLE)
		case SYS_MEM_CLASS1_TX_FILE:
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FAXMODEM; /** CLASS1動作中クリア	*/
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
			break;
 #endif
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
		case SYS_MEM_MAIL_TX_FILE:
			MEM_ClearDocAndFATArea(SYS_DocumentStoreItem, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
			MailTxDocStoreNG();
			break;
#endif

		default:
			break;
		}
		CMN_ResetMemoyFeederTx();
		CMN_ResetStamp();

#if (0)
** 		/* ＰＯＰＬＡＲ＿Ｈには、コピー待機モードは有りません。
** 		** ＲＯＭ容量も厳しいので、少しですが以下の処理は削除します。 By O.Kimoto 1998/08/31 */
** 		if (CHK_ReadyModeCopy()) {
** 			if (CHK_UNI_HyperFineON()) { /** ハイパーファインである場合 */
** 				SYB_CopyModeSw = SYS_SFINE;;
** 			}
** 			else { /** スーパーファインである場合 */
** 				SYB_CopyModeSw = SYS_HFINE;;
** 			}
** 			SYB_ModeSw = SYB_CopyModeSw;
** 		}
** 		else {
** 			CMN_ResetPrimaryMode();
** 		}
#else
 #if (PRO_COPY_FAX_MODE == ENABLE)
 		/* ＰＯＰＬＡＲ＿Ｂのみ */
		if (CHK_ReadyModeCopy()) {
#if (0)	/* 画質の初期化はＦＡＸモードのみ行います by K.Watanabe 1999/01/21 */
	/* この処理があると、コピー動作の内、ジャムリカバーで中止・放置した時の画質のみ
	** 初期化されると言う中途半端な仕様になるので止めます
	** （基本的に、コピー後の設定値の初期化は、１分間キー入力が無かった時のみです）
	*/
//			if (CHK_UNI_HyperFineON()) { /** ハイパーファインである場合 */
//				SYB_CopyModeSw = SYS_SFINE;;
//			}
//			else { /** スーパーファインである場合 */
//				SYB_CopyModeSw = SYS_HFINE;;
//			}
//			SYB_ModeSw = SYB_CopyModeSw;
#endif
		}
		else {
			CMN_ResetPrimaryMode();
		}
 #else
 		/* ＰＯＰＬＡＲ＿Ｂ以外 */
		CMN_ResetPrimaryMode();
 #endif
#endif

		CMN_ResetPrimaryContrast(); /** 濃度のリセット処理とLEDをリセット */
		CMN_ResetConfirmationReport(); /* By S.K Sep.19,1994 */
#if (PRO_RED_SCAN == ENABLE)	/* 朱色読み取り 2002/03/05 T.Takagi */
		CMN_ResetRedScan();
#endif
#if defined (KEISATSU)		/* 警察FAX DVT_ID33 Modify by SMuratec 夏 2005/11/12 */
		ResetKeisatsuAttribute();
#endif
		break;
#if (PRO_FBS == ENABLE)
	case MSG_FBS_TRANSPORT_SET:		/** FBS輸送モード設定 */
		/** ミラーキャリッジを輸送時の固定位置へ移動させる */
		MirrorTaskInstruction = MIRROR_TASK_TRANSPORT;
		MirrorTaskRequest = TRUE;
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
		SYS_MachineStatus[SYS_SCANNER_STATUS] |= (SYS_SCANNER_MIRROR_BUSY|SYS_SCANNER_MIRROR_INIT);
		break;
	case MSG_FBS_TRANSPORT_RESET:	/** FBS輸送モード解除 */	/* 1997/03/05 s.takeuchi */
		SYB_ScannerTransportMode = FALSE;		/** 輸送モードを解除 */
		MAN_InitializeScanner();				/** スキャナを初期化 */
		break;
#endif
#if (PRO_CIPHER == ENABLE)	/*	By Y.Suzuki 1997/07/11	*/
	case MSG_DECIPHER_START:
		if (ScrambleOn == 0) {/*	By Y.Suzuki 1997/09/04	*/
			break;
		}
		/*	復号化タスク起動	*/
		SYS_CipherComExec = SYS_DECIPHER_EXEC;
		SYS_MachineStatus[SYS_CIPHER_STATUS] = SYS_DESCRAMBLE_EXEC;
		if (opr_sub_message1 == SYS_MEM_TX_FILE) {
			SYS_CipherComExec = SYS_TX_DOC_DECIPHER_EXEC;
		}
		CipherReadIndex.No = opr_sub_message2;
		cre_tsk(&tskno_SCD_CipherTask,TSK_SCD_CIPHERTASK,0);
		break;
	case MSG_OPT_DECIPHER_FROM_OPR:
		/* デスクランブル中にキーエラー検出時の継続／中断 */
		if (ScrambleOn == 0) {/*	By Y.Suzuki 1997/09/04	*/
			break;
		}
		SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_WRONG_KEY_ERROR;
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = opr_message;
		MainTaskMessage.SubMessage1 = opr_sub_message1;
		snd_msg(mbxno.SCD_CipherResult,&MainTaskMessage);
		break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
	case MSG_MAIL_MANUAL_RX:	/* 手動受信起動　*/
		SYB_INF_MailCommandStatus[opr_sub_message1].UserNumber = SYS_INF_MailCommand[opr_sub_message1].UserNumber;
		SYB_INF_MailCommandStatus[opr_sub_message1].Status = SYS_INF_MAIL_CMD_WAITING;
		SYS_INF_MailCommand[opr_sub_message1].Status = SYS_INF_MAIL_CMD_WAITING;
		break;
	case MSG_MAILCOM_LIST_PRINT:
		if (CMN_CheckPrintEnable(SYS_LIST_PRINT) == TRUE) {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT;
			SYS_DocumentPrintItem = opr_sub_message1;	/*　リストの種類　*/
			SYS_DocumentPrintNo = opr_sub_message2;		/*　ユーザー番号　*/
			SYS_DocumentPrintPageNo = 1;
			cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0);
		}
		break;
	case MSG_MAIL_STORED_DOC_PRINT:	/* 送信予約原稿のプリント起動　*/
		if (CMN_CheckPrintEnable(SYS_IMAGE_PRINT) == TRUE) {
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT;
			SYS_DocumentPrintItem = SYS_MEM_MAIL_TX_FILE;
			SYS_DocumentPrintNo = opr_sub_message1;
			SYS_DocumentPrintPageNo = 1;
			SYS_DocumentPrintClass = SYS_PRINT_CLASS;
			cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0);
		}
		break;
	case MSG_MAIL_MANUAL_PRINT:	/* 手動受信起動　*/
		StartRxMailManualPrint((UBYTE)opr_sub_message1);
		break;
	case MSG_INF_TEST_FUNCTION:
		break;
	case MSG_INF_INIT_ENGINE_BOARD:	/*　設置オペレーション実行要求　*/
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_DIALUP_INTERNET_FAX)) {
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_DIALUP_INTERNET_FAX; /*Internet Fax 動作中セット */
			SYS_MachineStatus[SYS_ERROR_STATUS] &= ~SYS_ERROR_INF_INIT;
			SYS_INF_ExecStatus = SYS_INF_STATUS_INITIAL;
			cre_tsk(&tskno_INF_Task, TSK_INF_TASK, 0);
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = INF_INIT_ENGINE_BOARD;
			snd_msg(mbxno.INF_Task, &MainTaskMessage);
		}
		break;
#endif	/* PRO_DIALUP_INTERNET_FAX == ENABLE by Y.Tanimoto */

		/*-----------------------------------------------------------------
		** 記録タイプ変更後にイニシャルカットを起動する
		** 1998/08/19 H.Yoshikawa
		*/
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1998/08/19 H.Yoshikawa */
		case MSG_CHANGE_PRINT_TYPE:
			if (RIBON()) {
				SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~(SYS_PRINTER_NO_INK);
			}
			else {
				SYS_MachineStatus[SYS_PRINTER_STATUS1] |= (SYS_PRINTER_NO_INK);
			}
			if ((CMN_CheckPrintEnable(SYS_IMAGE_PRINT) == TRUE)
				&& (CHK_UNI_PowerON_InitialCut())
				&& (RIBON())) {
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中をセット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /* イメージ・プリント中セット */
				SYS_DocumentPrintClass = SYS_PRINT_CLASS_INITIAL; /* プリンター初期化 */
				cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* メモリ・プリント・タスク起動 */
			}
			break;
#endif

#if (PRO_PRINT_TYPE == THERMAL)	/* 1998/10/07 by T.Soneoka */
	case MSG_REALTIME_COPY:		/* リアルタイムコピー */
		if (CMN_CheckScanEnable()
			&& CMN_CheckFeederCommandEmpty()
			&& CMN_CheckPrintEnable(SYS_IMAGE_PRINT)) {
			SYS_DocumentStoreItem = SYS_MEM_MANUAL_COPY_FILE; /* 表示のため 1998/12/9 by T.Soneoka */
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FEED_IN;
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
#if (0) /* 1998/12/14 by T.Soneoka */
**			SYS_MachineStatus[SYS_MACHINE_STATUS]  |= SYS_DOC_STORE;
#endif
			/*
			** ジャーナルプリントストップキー処理後、リアルタイムコピーするとプリントしない不具合対策
			** 1999/02/04 by T.Soneoka
			*/
			InzPrinterParameter();

			cre_tsk(&tskno_SCN_CopyStoreTask, TSK_SCN_COPYSTORETASK, 0); /* リアルタイム蓄積タスク */

			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
			SYS_MachineStatus[SYS_MACHINE_STATUS]  |= SYS_SCANNER_COPY;
			SYS_DocumentPrintItem = MEM_REALTIME_COPY_FILE;
			SYS_DocumentPrintNo = 0;
			SYS_DocumentPrintPageNo = 1;
			SYS_DocumentPrintClass = SYS_PRINT_CLASS_REALTIMECOPY;

#if (0)
** 			/* 名前変更 By O.Kimoto 1998/10/27 */
** 			cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* メモリ・プリント・タスク起動 */
#else
			cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_COPYPRINTTASK, 0); /* メモリ・プリント・タスク起動 */
#endif

		}
#if (1)		/* リアルタイムコピーの時、プリント不可の場合、ナック音を鳴らす。by Y.kano 2005/03/18 */
		else {
			NackBuzzer();
		}
#endif

		break;
#endif
	default:
		break;
	}

#if (PRO_FBS == ENABLE)
	if ((opr_message == MSG_MEMORY_OVER_CANCEL)		/* メモリーオーバー時キャンセル操作				*/
	 || (opr_message == MSG_MEMORY_OVER_TIME_UP)	/* メモリーオーバー時タイムオーバー				*/
	 || (opr_message == MSG_SCAN_CONT_END)			/* ジャムリカバー／次原稿ＯＰ蓄積終了			*/
	 || (opr_message == MSG_SCAN_CONT_ABORT)) {		/* ジャムリカバー／次原稿ＯＰ蓄積原稿取り消し	*/
		SYS_NextBookDocument = FALSE;	/* 次原稿確認を無しに初期化 */
		IsBookDocSizeSet = FALSE;		/* ブック原稿サイズを未設定に初期化 */
	}
#endif

	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	snd_msg(mbxno.OPR_MAN_MessageTask, &MainTaskMessage);	/* 桐にも適用 Jan.18,1995 By T.Nose */
}



#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/21 Y.Murata for KAKI */
#if 0
UWORD	
{
	UBYTE	com_no;
	UBYTE	dummy;
	UWORD	i;
	UWORD	ret;

	ret = 0;
	com_no = 0xFF;
	for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++ ) {
		if (SYB_ExecQueue[i].Status == SYS_EXEC_ERASED) {
			if (SYB_ExecQueue[i].Kind == SYS_COMMAND_TRX) {
				com_no = SYB_ExecQueue[i].Number.Command;
				if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {
					if (SYS_DocumentStoreItem == SYS_MEM_TX_FILE) {
						if (SYS_DocumentStoreNo == (UWORD)com_no) {
							SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_DOC_STORE;
							ret++;
							if (ret >= 2) {
								dummy++;
							}
						}
					}
				}
			}
		}
	}

	return(ret);
}
#endif

#endif
