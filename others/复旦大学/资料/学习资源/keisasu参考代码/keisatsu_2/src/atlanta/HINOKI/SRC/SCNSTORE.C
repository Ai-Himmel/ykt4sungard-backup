/*
 *	@(#)%W%
 *	FileName:	/home2/prj/Eva/Src/scn/scnstore.c
 *	Create:	Mon Dec 29 15:28:18 1997	by	ishiyama
 *	Description:
 *		原稿蓄積タスク
 *	Change Log:
 *		\prj\eva\src\scn\scnstore.cをＨＩＮＯＫＩ用にメンテしました
 */

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\sysdoc.h" /* 1999/02/17 by T.Soneoka */
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\scn_tbl.h"
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"
#include "\src\cpu\sh7043_a\irom\define\def_evtn.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#else
	#if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)
		#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
		#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
	#else
		#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
		#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
	#endif
#endif
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"

#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\unisw_c.h"

#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
#include "\src\atlanta\define\cl1_def.h"	/* added by H.Hirao 1999/03/04 */
#include "\src\atlanta\ext_v\cl1_data.h"	/* added by H.Hirao 1999/03/04 */
#endif

/*
 *	Name:	Document Store Task
 *	Create:	Mon Dec 29 15:29:01 1997	by	ishiyama
 *	Synopsis:
 *		#include	"scn_task.h"
 *		void	DocStorTask(void);
 *	Description:
 *		原稿蓄積タスク
 *		コピーの場合は,1スタックで原稿読取り幅を変えない仕様
 *		送信の場合は、ページごとに変える
 *	Return Value:
 *		void
 *	Change Log:
 */
void	DocStoreTask(void)
{
	MESSAGE_t	StoreTaskMsg;				/* 送信メッセージ用エリア */
	MESSAGE_t	*RcvMessage;				/* 受信メッセージ用エリア */
	BOOL	PageLoop;						/* 1Page 読取り処理継続 TRUE:継続,FALSE:中断 */

	tskno_SCN_WatchDocFeedTask = 0xffff;
	tskno_SCN_ScanPage = 0xffff;
	tskno_SCN_StorePage = 0xffff;
	tskno_SCN_DocOutTask = 0xffff;
	tskno_SCN_DummyTask = 0xffff;	/* エンコードタスクからのイベント待ちのタスク、リスケジューラを走らせるため 1999/03/16 by T.Soneoka */

	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~(SYS_STOP_DOC_STORE); /** 原稿蓄積の停止要求をクリア */

	SYS_DualRestrictionStatus &= ~0x04; /* 原稿蓄積中断中解除 1999/01/21 by T.Soneoka */

	SYS_StorePause = TRUE;	/* 表示用 1999/1/14 by T.Soneoka */
	
	ScannerMode = SCANNER_DOC_SCAN_MODE;

	OpenScanner();				/* 読取りのための初期設定 */

	ExecutePushStamp = FALSE;
#if (PRO_STAMP == ENABLE)
	SetStampExec();
#endif


	IniMemWriteParameter();		/* 画像メモリのオープンパラメータをセットします */

	PageLoop = QueryDs1On();
	if (!PageLoop) {	/* 先頭ページの読取り開始時に原稿が抜かれていた場合は繰込み不良で終了する */
		StoreTaskMsg.Message = MSG_DOCSTORE_FEED_ERROR;
	}
	while (PageLoop) {					/* Page Loop */

		/*
		** 受信中、原稿蓄積中をデュアル制限のため排他制御します added by H.Hirao 1998/12/26
		*/
		while (1) {
			CMN_DisableInterrupt();
			if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN) {
				CMN_EnableInterrupt();
				StoreTaskMsg.Item = FROM_DOCSTORE;

#if (0)
** 				/* D86-016 メインへ送るメッセージ間違いBy O.Kimoto 1999/02/08 */
** 				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_TOP_COVER_OPEN;
#else
				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;
#endif

				snd_msg(mbxno.MAN_Task, &StoreTaskMsg);
				rcv_msg(mbxno.SCN_Task, &SCN_Msg);
				wai_tsk(0xffff);
			}
			if (SYS_DocumentStoreStopSwitch()) {
				CMN_EnableInterrupt();
				StoreTaskMsg.Item = FROM_DOCSTORE;
				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_STOPSW_ON;
/*
** スキャンクローズで原稿排出中は回線引きっぱなしになる不具合
** 1999/02/01 by T.Soneoka
*/
#if (0)
**				/* 原稿排出処理 */
**				if (SCN_Close((UBYTE)0) != SCN_DOC_EXIT_OK) {
**					StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;
**				}
#else
				/* 原稿排出処理 */
				if (SCN_Close((UBYTE)FROM_DOCSTORE) != SCN_DOC_EXIT_OK) {
					StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;
				}
#endif

				snd_msg(mbxno.MAN_Task, &StoreTaskMsg);
				rcv_msg(mbxno.SCN_Task, &SCN_Msg);
				wai_tsk(0xffff);
			}
			/* if (((SYS_DualRestrictionStatus & 0x01) == 0x01) || (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRE_LINE_BUSY)) { @* 受信中 */
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/03/03 */
			/* CL1_RestrictionStatusResetTimer added by H.Hirao 1999/05/12 */
			if (((SYS_DualRestrictionStatus & 0x01) == 0x01) || (CL1_DualRestrictionStatus & CL1_CLASS1_IN_USE) || SYS_CalledRequestForDocStore
			  || (SYS_CL1_Status & (CL1_CALLED | CL1_FNET_CALLED | CL1_DIALIN_CALLED | CL1_RECEIVE | CL1_SEND | CL1_LOCALSCAN | CL1_LOCALPRINT | CL1_AUTOINIT)) || CL1_RestrictionStatusResetTimer) {
#else
			if (((SYS_DualRestrictionStatus & 0x01) == 0x01) || SYS_CalledRequestForDocStore) { /* 受信中 または 原稿蓄積中にＣＩ検出 changed by H.hirao 1998/12/28 */
#endif

#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* ローカルスキャン原稿は、待ちあわせしない by H.Hirao 1999/05/12 */
				if (SCN_StoreData.Item == SYS_MEM_CLASS1_TX_FILE) {
					CL1_DualRestrictionStatus |= CL1_SCANNER_IN_USE;
					CMN_EnableInterrupt();
					break;
				}
#endif
				/*
				** ＤＵＡＬ制限変更のため
				** 強制メモリ受信以外のときは、スキャナを停止処理をいれます
				** 1999/02/18 by T.Soneoka
				*/
#if (0)
**				SYS_DualRestrictionStatus |= 0x04; /* 原稿蓄積中断中セット 1999/01/21 by T.Soneoka */
#else
				if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) ||	(CHK_UNI_V34ReceiveType() != V34_MRX_TO_MRX)) {
					SYS_DualRestrictionStatus |= 0x04; /* 原稿蓄積中断中セット 1999/01/21 by T.Soneoka */
				}
#endif
				CMN_EnableInterrupt();
				wai_tsk(100);
			}
			else {
				/*
				** ＤＵＡＬ制限変更のため
				** 強制メモリ受信以外のときは、スキャナを停止処理をいれます
				** 1999/02/18 by T.Soneoka
				*/
#if (0)
**				SYS_DualRestrictionStatus |= 0x02; /* 原稿蓄積中セット */
#else
				if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) ||	(CHK_UNI_V34ReceiveType() != V34_MRX_TO_MRX)) {
					SYS_DualRestrictionStatus |= 0x02; /* 原稿蓄積中セット */
				}
#endif
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
				CL1_DualRestrictionStatus |= CL1_SCANNER_IN_USE;	/* スキャン中セット added by H.Hirao 1999/03/04 */
#endif
				CMN_EnableInterrupt();
				break;
			}
		}
		SYS_DualRestrictionStatus &= ~0x04; /* 原稿蓄積中断中解除 1999/01/21 by T.Soneoka */

		PageLoop = FALSE;				/* default 設定 */

#if (PRO_STAMP == ENABLE)
		EnablePushStampEvent = TRUE;	/* 済みスタンプ押下イベント許可フラグ初期化 */
#endif

		/*
		 * コピーの読み取りではADFの1スタックで原稿サイズを変えないため、
		 *	コピーの場合は先頭ページの場合だけ、読取り原稿サイズをセットする
		 *	その他の場合は、毎ページ読取り原稿サイズをセットする
		 */
		if (SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE) {
			if (SYS_DocumentStorePage == 1) {
				SYS_DocumentScanSize = CMN_GetDocumentScanSize();
			}
		} else {
			SYS_DocumentScanSize = CMN_GetDocumentScanSize();
		}
		SetScanPageAttribute(CurrentPage); /* 現在の Document の属性を設定 */

		SCN_StoreData.Code		= CurrentPage->Code;
		SCN_StoreData.Mode		= CurrentPage->Mode;

		/*
		** メモリコピー、Ｂ４－＞Ａ４蓄積処理追加
		** 1999/02/17 by T.Soneoka
		*/
		if ((!CHK_UNI_ReductionPrint())
		&& (SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)) {
			if (SYS_DocumentStorePage == 1) {
				if (QueryReduction() == REDUCTION_B4_A4) {
					SCN_StoreData.Size = SYS_DOCUMENT_A4_SIZE;
				} else {
					SCN_StoreData.Size = CurrentPage->Size;
				}
			}
#if (PRO_CLASS1 == ENABLE)	/* by H.Hirao 1999/03/23 */
		} else if (QueryClass1Tx()) {
			if (QueryReduction() == REDUCTION_B4_A4) {
				SCN_StoreData.Size = SYS_DOCUMENT_A4_SIZE;
			} else {
				SCN_StoreData.Size = CurrentPage->Size;
			}
#endif
		} else {
			SCN_StoreData.Size		= CurrentPage->Size;
		}
		
		SleepDocStoreSubTask = FALSE;		/* Sub Task を Sleep 状態にするフラグ */
		cre_tsk(&tskno_SCN_WatchDocFeedTask, TSK_SCN_WATCHDOCUMENTFEEDTASK, &mbxno.SCN_Task);	/* フィーダーエラー監視タスク起動 */
		cre_tsk(&tskno_SCN_ScanPage, TSK_SCN_SCANPAGE, 0);	/* 原稿読取りタスク起動 */
		InzStorePageResource();								/* Task が途中で Delete されることを考慮 */
		cre_tsk(&tskno_SCN_StorePage, TSK_SCN_STOREPAGE, 0);/* 原稿1ページ蓄積タスク起動 */

		/* エンコードタスクからのイベント待ちをするタスク、リスケジューラを走らせるため 1999/03/16 by T.Soneoka */
		cre_tsk(&tskno_SCN_DummyTask, TSK_SCN_DUMMYTASK, 0);/* 原稿1ページ蓄積タスク起動 */

		SCN_Open();		/* 読取り開始 */
		
		rcv_msg(mbxno.SCN_Task, &RcvMessage); /* 蓄積関連タスクの状況をメッセージで待ち受け */
		
		CloseScanPage();	/* 読取り終了 */

		if (tskno_SCN_StorePage != 0xffff) {
			del_tsk(&tskno_SCN_StorePage);	/* 原稿1ページ蓄積タスク終了 */
		}
		if (tskno_SCN_ScanPage != 0xffff) {
			del_tsk(&tskno_SCN_ScanPage);	/* 原稿読取りタスク終了 */
		}
		if (tskno_SCN_WatchDocFeedTask != 0xffff) {
			del_tsk(&tskno_SCN_WatchDocFeedTask);	/* フィーダーエラー監視タスク終了 */
		}

		/* エンコードタスクからのイベント待ちをするタスク、リスケジューラを走らせるため 1999/03/16 by T.Soneoka */
		if (tskno_SCN_DummyTask != 0xffff) {
			del_tsk(&tskno_SCN_DummyTask);
		}

		CMN_DisableInterrupt();
		SYS_DualRestrictionStatus &= ~(0x02);
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
		CL1_DualRestrictionStatus &= ~CL1_SCANNER_IN_USE;	/* スキャン中リセット added by H.Hirao 1999/03/04 */
#endif
		CMN_EnableInterrupt();

		/*
		 *	メッセージの変換と１ページの後処理
		 */
		switch (RcvMessage->Message) {
		case MSG_DOCSTORE_MEMORY_OVER: /* メモリオーバー from StorePageTask */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_MEM_OVER;
			break;
		case MSG_DOCSTORE_STOPSW_ON: /* 停止要求 from StorePageTask */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_STOPSW_ON;
			break;
		case MSG_DOCSTORE_OK:		/* 蓄積正常終了 from StorePageTask */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_OK;
			SYB_LifeMonitor.ScanCount++;	/** ライフモニタの読取り枚数加算 */
#if (PRO_STAMP == ENABLE)
			PushStamp();	/* 済みスタンプ処理 and モータ再スタート処理 */
#endif
			if (QueryDs1On()									/* DS1がOnで */
			&& (QueryDocPosition() != DOC_POS_NO_DOCUMENT)) {	/* 次ページが登録されていれば */

				/* 枚数指定されていて、且つ指定枚数以上の原稿がＡＤＦ上にある場合の処理が抜けていた by O.Kimoto 1998/12/17 */
				if (!CheckExceedDocPageNum()) {

					PageLoop = TRUE;	/* 次ページ処理継続 */
					IncPage();

					/*
					** 割り込みの中で次原稿の登録をここでやるように修正します
					** 割り込みの中で次原稿登録（CurrentPageとNextPageのつけ替え）した場合、
					** 次原稿登録したが、現在の原稿読み取り終了時に、次原稿読み取りしない場合（原稿枚数指定）、
					** SCN_Close()で排出処理をコールすると、次原稿まで排出されてしまう為
					** ここでしたほうがすっきりする
					** 1999/02/10 by T.Soneoka
					*/
					if (NextPage != NULL) {
						DeleteDocObj(&CurrentPage);
						CurrentPage = NextPage;
						NextPage = NULL;
					}
					else {
						/*
						** 最終原稿蓄積中に次の原稿をセットされると、
						** 次原稿の登録もされていないので読み取りにいってしまう
						** 次原稿ある場合は、ここで登録するようにします
						*/
						DeleteDocObj(&CurrentPage); /* 上記処理を３回するとCurrentPageが取れなくなる不具合 1999/03/05 by T.Soneoka */
						CurrentPage = CreateDocObj();
						NextPage = NULL;
					}
				}

				/* 仕様変更
				** 読み取り中において、ＤＳ２がＯＦＦした時点でＤＳ１もＯＦＦしていれば、今読んだ原稿が
				** 最終原稿であるという風に変更
				** by O.kimoto 1999/03/08
				*/
				else {
					if (!CheckNeedDocPageNum()) {
						StoreTaskMsg.Message = MSG_SCN_DOCSTORE_STR_PAGE_ERROR;
					}
				}

			} else {
				if (!CheckNeedDocPageNum()) {
					StoreTaskMsg.Message = MSG_SCN_DOCSTORE_STR_PAGE_ERROR;
				}
			}
			WaitDocChanged();	/* 原稿が切り替わるまで待ち合わせします */
			break;
		case MSG_DOCSTORE_MAXLINE_OVER:	/* 1m原稿長制限 from WatchDocFeedTask */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_MAXLINE_OVER;
			MEM_ClearBreak(&SCN_IndexData); /* 蓄積途中のファイルをクリア 1999/02/25 by T.Soneoka */
			break;
		case MSG_DOCSTORE_COVER_OPEN: /* カバーオープン from WatchDocFeedTask */

#if (0)
** 			/* 蓄積中にスキャナーカバーがあいた場合は、ＪＡＭリカバーオペレーションを起動させるために
** 			** メインへは、「MSG_SCN_DOCSTORE_DOC_ERROR」を通知しなければならない。
** 			** by O.Kimoto 1999/03/08
** 			*/
** 			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_TOP_COVER_OPEN;
#else
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;
#endif

			MEM_ClearBreak(&SCN_IndexData); /* 蓄積途中のファイルをクリア 1999/02/25 by T.Soneoka */
			break;
		case MSG_DOCSTORE_FEED_ERROR: /* 繰込み不良 from WatchDocFeedTask */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;
			MEM_ClearBreak(&SCN_IndexData); /* 蓄積途中のファイルをクリア 1999/02/25 by T.Soneoka */
			break;
		default:
			/* not reached */
			break;
		}
	} /* Page Loop End */
	
	SYS_StorePause = FALSE;	/* 表示用 1999/1/14 by T.Soneoka */

/*
** スキャンクローズで原稿排出中は回線引きっぱなしになる不具合
** 1999/02/01 by T.Soneoka
*/
#if (0)
**	/* 原稿排出処理 */
**	if (SCN_Close((UBYTE)0) != SCN_DOC_EXIT_OK) {
**		StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;
**	}
#else
	/*
	** 原稿蓄積中にカバーオープンをすると、ＴＸモータがまわりっぱなしになる
	** ＤＳ１、２がＯＦＦになると、メインタスクで原稿初期化が走るため、
	** その後、フィードアウトするとモータを止めるパスがなくなる
	** 1999/02/26 by T.Soneoka
	*/
#if (0)
**	/* 原稿排出処理 */
**	if (SCN_Close((UBYTE)FROM_DOCSTORE) != SCN_DOC_EXIT_OK) {
**		StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;
**	}
#else
	/* 原稿排出処理 */
	if (StoreTaskMsg.Message != MSG_SCN_DOCSTORE_TOP_COVER_OPEN) {
		if (SCN_Close((UBYTE)FROM_DOCSTORE) != SCN_DOC_EXIT_OK) {
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;
		}
	}
#endif
#endif
	StoreTaskMsg.Item = FROM_DOCSTORE;
	snd_msg(mbxno.MAN_Task, &StoreTaskMsg);
	rcv_msg(mbxno.SCN_Task, &SCN_Msg);
	wai_tsk(0xffff);
}


/*
 *	Name:	Exit Docuement Store Task
 *	Create:	Wed Feb 25 15:43:32 1998	by	ishiyama
 *	Synopsis:
 *		#inlcude	"scn_task.h"
 *		void	ExitDocStoreTask(void)
 *	Description:
 *		Document Store Task の終了関数
 *			リソースの開放が目的
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ExitDocStoreTask(void)
{
	ScannerMode = SCANNER_NEUTRAL_MODE;
	if (tskno_SCN_StorePage != 0xffff) {
		del_tsk(&tskno_SCN_StorePage);	/* 原稿1ページ蓄積タスク終了 */
	}
	if (tskno_SCN_ScanPage != 0xffff) {
		del_tsk(&tskno_SCN_ScanPage);	/* 原稿読取りタスク終了 */
	}
	if (tskno_SCN_WatchDocFeedTask != 0xffff) {
		del_tsk(&tskno_SCN_WatchDocFeedTask);	/* フィーダーエラー監視タスク終了 */
	}
	/* エンコードタスクからのイベント待ちをするタスク、リスケジューラを走らせるため 1999/03/16 by T.Soneoka */
	if (tskno_SCN_DummyTask != 0xffff) {
		del_tsk(&tskno_SCN_DummyTask);
	}

	/*
	** １ページ原稿蓄積中のステータスをリセット added by H.Hirao 1998/12/26
	*/
	CMN_DisableInterrupt();
	SYS_DualRestrictionStatus &= ~0x02;
	SYS_DualRestrictionStatus &= ~0x04; /* 原稿蓄積中断中解除 1999/01/21 by T.Soneoka */
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
	CL1_DualRestrictionStatus &= ~CL1_SCANNER_IN_USE;	/* スキャン中リセット added by H.Hirao 1999/03/04 */
#endif

/*
** NTTファネット不具合指摘 No.6 2002/10/30 by T.Soneoka
*/
#if (0)
**	/* 
**	** ＤＳ２に噛んだ状態でのストップキー連打でループ
**	** ここでSYS_FEED_OUTを落とした場合、このタイミングでストップキーが押下されると
**	** 原稿排出タスクがデリートされる前に、クリエイトされてしまう
**	** SCN_Close()でセットされたSYS_FEED_OUTを親タスクの終了処理ルーチンで落とすようにします
**	** 1999/03/09 by T.Soneoka
**	*/
**	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FEED_OUT;
#endif
	CMN_EnableInterrupt();

	/*
	** 原稿読み取り最後に、ＴＸモータ停止／ランプＯｆｆします
	** 1999/03/11 by T.Soneoka
	*/
	StopTxMotor();
	LampOff();

/*
** NTTファネット不具合指摘 No.6 2002/10/30 by T.Soneoka
** CluchOffしてからフィードアウトのマシンステータスをこかします 上から移動
*/

	/* 
	** ＤＳ２に噛んだ状態でのストップキー連打でループ
	** ここでSYS_FEED_OUTを落とした場合、このタイミングでストップキーが押下されると
	** 原稿排出タスクがデリートされる前に、クリエイトされてしまう
	** SCN_Close()でセットされたSYS_FEED_OUTを親タスクの終了処理ルーチンで落とすようにします
	** 1999/03/09 by T.Soneoka
	*/
	CMN_DisableInterrupt();
	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FEED_OUT;
	CMN_EnableInterrupt();

	exi_tsk();
}

/*
 *	Name:	Scan Page Task
 *	Create:	Tue Jan 13 14:09:09 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		void	ScanPageTask(void);
 *	Description:
 *		GateArray が書いた ScannerBuffer(SRAM)を読んで、
 *		Scanner Page Memory に張る
 *	Notes:
 *		このタスクがクリエートされるときは、
 *		原稿が読取り可能な位置にあることが前提。
 *		メッセージは投げない
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ScanPageTask(void)
{
	UBYTE	*ScanBufPtr;
	BYTE	DummyScanCount;
	UWORD	StopLineCount;		/* Stop Test のためのカウンタ */
	
	/* Scanner Page Memory 初期化 */
	InzScanPageMem();
	DummyScanCount = DummyScanLine;		/* 読み飛ばすライン数 */
	StopLineCount = 0;
	
	while (!SleepDocStoreSubTask) {
		if (QueryDocScannable()) {
			if (EnableToReadScanBuf()) {
				if (EnableToWriteScanPageMem()) {
					/* 1 Line 単位で Scanner Buffer から Page Memory に転送 */
					ScanBufPtr = GetLineAddress4ReadScanBuf();
					if (DummyScanCount <= 0) {
						PutLineScanPageMem(ScanBufPtr);
					} else {
						DummyScanCount--;
					}
					DecScanBufReadableLine();
				} else {
					/*
					 *	Encode 処理待ち
					 *	Encode の処理速度が十分であれば,
					 *	ここは通らないパスになる。
					 */
/*
** ページメモリＦＵＬＬになった場合、次の転送はブロック単位で行なうようにします
** 1999/02/08 by T.Soneoka
*/
#if (0)
**					wai_tsk(10);		/* Wait 100msec */
#else
					while (1) {
						if (QueryScanPageMemReadableLine() > (SCANPAGE_ROW/2)) {
							wai_tsk(10);		/* Wait 100msec */
						} else {
							break;
						}
					}
#endif
				}
			} else {
				/* Scanner Buffer Data 待ち 5msec で入るはず */
				wai_tsk(1);			/* Wait 10msec */
			}
		} else {
#if (0) /* 1998/12/09 by T.Soneoka */
**			/* モータ起動要求がなく、励磁状態にある場合は、励磁ＯＦＦします  1998/12/08 by T.Soneoka */
**			if (!QueryTxMotorMoving()
**			&& (GaTmr0Status & TMEXCT)) {
**				StopTxMotor();
**			}
#endif
			/* 原稿搬送待ち */
			wai_tsk(1);			/* Wait 10msec */
		}
	}
	wai_tsk(0xffff);
}


/*
 *	Name:	Watch Document Feed Error Task
 *	Create:	Tue Feb 17 15:45:44 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		void	WatchDocFeedTask(void);
 *	Description:
 *		蓄積中のフィーダーエラーを検出
 *			繰込み不良
 *			スキャナカバーオープン
 *			最長原稿長エラー
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	WatchDocFeedTask(WORD *tx_mail_box_no)
{
	MESSAGE_t Msg;
	UBYTE	EventFlag;

	wai_evt(EVT_SCN_DOC);

	if (ScannerEventStatus & SCN_EVT_DOCSTORE_FEED_ERROR) {
		Msg.Message = MSG_DOCSTORE_FEED_ERROR;
	} else if (ScannerEventStatus & SCN_EVT_DOCSTORE_COVER_OPEN) {
		Msg.Message = MSG_DOCSTORE_COVER_OPEN;
	} else if (ScannerEventStatus & SCN_EVT_DOCSTORE_MAXLINE_OVER) {
		Msg.Message = MSG_DOCSTORE_MAXLINE_OVER;
	}
	
	SleepDocStoreSubTask = TRUE;		/* 兄弟タスクをスリープ状態にし、親タスクを走らせるため */
	Msg.Item = FROM_WATCH_DOC_FEED_TASK;
	snd_msg(*tx_mail_box_no, &Msg);

	wai_tsk(0xffff);
}

/*
 *	Name:	Exit Watch Document Feed Error Task
 *	Create:	Thu Feb 19 13:47:34 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		void	ExitWatchDocFeedTask(void);
 *	Description:
 *		WatchDocFeedTask の終了処理
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ExitWatchDocFeedTask(void)
{
	exi_tsk();
}


/*
 *	Name:	Real Time Copy Task
 *	Create:	 1998/07/25 by T.Soneoka
 *	Synopsis:
 *	Description:
 *		リアルタイムコピー原稿蓄積タスク
 *		エンコード処理および画像メモリへの転送は行わない
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	CopyStoreTask(void)
{
	MESSAGE_t	StoreTaskMsg;				/* 送信メッセージ用エリア */
	MESSAGE_t	*RcvMessage;				/* 受信メッセージ用エリア */

	tskno_SCN_WatchDocFeedTask = 0xffff;
	tskno_SCN_PageMemStore = 0xffff;

	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_SCANNER_COPY;

	ScannerMode = SCANNER_COPY_MODE;

	/*
	** 原稿蓄積にて、１ページ読み取り完了する前に、原稿排出完了する仕様変更
	** 念のためリアルタイムコピーは済みスタンプなしなので初期化しときます
	**  1999/02/25 by T.Soneoka
	*/
	SYS_StampFlag = 0;

	OpenScanner();						/* 読取りのための初期設定 */

	/*
	 * コピーの読み取りではADFの1スタックで原稿サイズを変えないため、
	 *	コピーの場合は先頭ページの場合だけ、読取り原稿サイズをセットする
	 *	その他の場合は、毎ページ読取り原稿サイズをセットする
	 */
	SYS_DocumentScanSize = CMN_GetDocumentScanSize();

	/* 
	** IsDocumentはプリンタでも監視しており、
	** このフラグがＦＡＬＳＥになった時点で
	** プリンタも終了処理に移行します
	*/
	IsDocument = QueryDs1On();
	if (!IsDocument) {	/* 先頭ページの読取り開始時に原稿が抜かれていた場合は繰込み不良で終了する */
		StoreTaskMsg.Message = MSG_DOCSTORE_FEED_ERROR;
	}
	while (IsDocument) {					/* Page Loop */

#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/03/03 */
		while (1) {
			CMN_DisableInterrupt();
			if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN) {
				CMN_EnableInterrupt();
				StoreTaskMsg.Item = FROM_SCN_REALTIMECOPY_TASK;
				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_TOP_COVER_OPEN;
				snd_msg(mbxno.MAN_Task, &StoreTaskMsg);
				rcv_msg(mbxno.SCN_Task, &SCN_Msg);
				PRN_PostClose();
				wai_tsk(0xffff);
			}
			if (SYS_ScannerCopyStopSwitch()) {
				CMN_EnableInterrupt();
				StoreTaskMsg.Item = FROM_SCN_REALTIMECOPY_TASK;
				StoreTaskMsg.Message = MSG_SCN_DOCSTORE_STOPSW_ON;
				snd_msg(mbxno.MAN_Task, &StoreTaskMsg);
				rcv_msg(mbxno.SCN_Task, &SCN_Msg);
				PRN_PostClose();
				wai_tsk(0xffff);
			}
			/* CL1_RestrictionStatusResetTimer added by H.Hirao 1999/05/12 */
			if ((CL1_DualRestrictionStatus & CL1_CLASS1_IN_USE) || SYS_CalledRequestForDocStore || CL1_RestrictionStatusResetTimer) { /* 受信中 または 原稿蓄積中にＣＩ検出 changed by H.hirao 1998/12/28 */
				CL1_DualRestrictionStatus &= ~CL1_SCANNER_IN_USE;	/* スキャン中リセット */
				CMN_EnableInterrupt();
				wai_tsk(100);
			}
			else {
				CL1_DualRestrictionStatus |= CL1_SCANNER_IN_USE;	/* スキャン中セット */
				CMN_EnableInterrupt();
				break;
			}
		}
#endif
		SYS_StampFlag = 0;
		EnablePushStampEvent = TRUE;		/* 済みスタンプ押下イベント許可フラグ初期化（読み取り終了で一旦モータ停止させる為） */

		SleepDocStoreSubTask = FALSE;		/* Sub Task を Sleep 状態にするフラグ */

		InzScanPageMem();					/* Scanner Page Memory 初期化 */

		SetScanPageAttribute(CurrentPage);	/* 現在の Document の属性を設定 */
		SetRealTimeCopyBlock(CurrentPage->Mode, CurrentPage->Size);

		OpenPrtImageBuf4Copy();

		SCN_Open();						/* 読取り開始 */

		cre_tsk(&tskno_SCN_WatchDocFeedTask, TSK_SCN_WATCHDOCUMENTFEEDTASK, &mbxno.SCN_Task);	/* フィーダーエラー監視タスク起動 */
		cre_tsk(&tskno_SCN_PageMemStore, TSK_SCN_PAGEMEMSTORETASK, 0);	/* ページメモリ原稿蓄積タスク起動 */
		
		rcv_msg(mbxno.SCN_Task, &RcvMessage); /* 蓄積関連タスクの状況をメッセージで待ち受け */
		
		if (tskno_SCN_PageMemStore != 0xffff) {
			del_tsk(&tskno_SCN_PageMemStore);	/* ページメモリ原稿蓄積タスク終了 */
		}
		if (tskno_SCN_WatchDocFeedTask != 0xffff) {
			del_tsk(&tskno_SCN_WatchDocFeedTask);	/* フィーダーエラー監視タスク終了 */
		}
		CloseScanPage();				/* 読取り終了 */
		
		/*
		 *	メッセージの変換と１ページの後処理
		 */
		switch (RcvMessage->Message) {
		case MSG_DOCSTORE_STOPSW_ON: /* 停止要求 from PageMemoryStoreTask */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_STOPSW_ON;
			IsDocument = FALSE;
			break;
		case MSG_DOCSTORE_OK:		/* 蓄積正常終了 from PageMemoryStoreTask */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_OK;
			/* リアルタイムコピー時のライフモニタ、スキャン枚数をセットするように変更 1999/1/22 by T.Soneoka */
			SYB_LifeMonitor.ScanCount++;	/** ライフモニタの読取り枚数加算 */
#if (0)	/* ClosePrtImageBuf4Copy()の中で、次の原稿があるかないか見るようにします 1999/1/19 by T.Soneoka */
**			if (QueryDs1On()									/* DS1がOnで */
**			&& (QueryDocPosition() != DOC_POS_NO_DOCUMENT)) {	/* 次ページが登録されていれば */
**				IsDocument = TRUE;
**			} else {
**				IsDocument = FALSE;
**			}
#endif
			break;
		case MSG_DOCSTORE_MAXLINE_OVER:	/* 1m原稿長制限 from WatchDocFeedTask */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_MAXLINE_OVER;
			IsDocument = FALSE;
			break;
		case MSG_DOCSTORE_COVER_OPEN: /* カバーオープン from WatchDocFeedTask */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_TOP_COVER_OPEN;
			IsDocument = FALSE;
			break;
		case MSG_DOCSTORE_FEED_ERROR: /* 繰込み不良 from WatchDocFeedTask */
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;
			IsDocument = FALSE;
			break;
		default:
			/* not reached */
			break;
		}
		ClosePrtImageBuf4Copy();

		/*
		** 割り込みの中で次原稿の登録をここでやるように修正します
		** 割り込みの中で次原稿登録（CurrentPageとNextPageのつけ替え）した場合、
		** 次原稿登録したが、現在の原稿読み取り終了時に、次原稿読み取りしない場合（原稿枚数指定）、
		** SCN_Close()で排出処理をコールすると、次原稿まで排出されてしまう為
		** ここでしたほうがすっきりする
		** 1999/02/10 by T.Soneoka
		*/
		if (IsDocument) {
			if (NextPage != NULL) {
				DeleteDocObj(&CurrentPage);
				CurrentPage = NextPage;
				NextPage = NULL;
			}
		}
	}

/*
** スキャンクローズで原稿排出中は回線引きっぱなしになる不具合
** 1999/02/01 by T.Soneoka
*/
#if (0)
**	/* 原稿排出処理 */
**	if (SCN_Close((UBYTE)0) != SCN_DOC_EXIT_OK) {
**		StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;
**	}
#else
	/*
	** 原稿蓄積中にカバーオープンをすると、ＴＸモータがまわりっぱなしになる
	** ＤＳ１、２がＯＦＦになると、メインタスクで原稿初期化が走るため、
	** その後、フィードアウトするとモータを止めるパスがなくなる
	** 1999/02/26 by T.Soneoka
	*/
#if (0)
**	/* 原稿排出処理 */
**	if (SCN_Close((UBYTE)FROM_DOCSTORE) != SCN_DOC_EXIT_OK) {
**		StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;
**	}
#else
	/* 原稿排出処理 */
	if (StoreTaskMsg.Message != MSG_SCN_DOCSTORE_TOP_COVER_OPEN) {
		if (SCN_Close((UBYTE)FROM_DOCSTORE) != SCN_DOC_EXIT_OK) {
			StoreTaskMsg.Message = MSG_SCN_DOCSTORE_DOC_ERROR;
		}
	}
#endif
#endif
	StoreTaskMsg.Item = FROM_SCN_REALTIMECOPY_TASK;
	snd_msg(mbxno.MAN_Task, &StoreTaskMsg);
	rcv_msg(mbxno.SCN_Task, &SCN_Msg);
	wai_tsk(0xffff);
}


/*
 *	Name:	Exit RealTimeCopy Store Task
 *	Create:	Wed Feb 25 15:43:32 1998	by	ishiyama
 *	Synopsis:
 *		#inlcude	"scn_task.h"
 *		void	ExitRealTimeCopyStoreTask(void)
 *	Description:
 *		RealTimeCopy Store Task の終了関数
 *			リソースの開放が目的
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ExitCopyStoreTask(void)
{
	if (tskno_SCN_PageMemStore != 0xffff) {
		del_tsk(&tskno_SCN_PageMemStore);	/* ページメモリ原稿蓄積タスク終了 */
	}
	if (tskno_SCN_WatchDocFeedTask != 0xffff) {
		del_tsk(&tskno_SCN_WatchDocFeedTask);	/* フィーダーエラー監視タスク終了 */
	}
#if (0) /* 1999/03/09 by T.Soneoka */
**#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/03/03 */
**	CMN_DisableInterrupt();
**	CL1_DualRestrictionStatus &= ~CL1_SCANNER_IN_USE;	/* スキャン中リセット */
**	CMN_EnableInterrupt();
**#endif
#else
	CMN_DisableInterrupt();
 #if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/03/03 */
	CL1_DualRestrictionStatus &= ~CL1_SCANNER_IN_USE;	/* スキャン中リセット */
 #endif
/*
** NTTファネット不具合指摘 No.6 2002/10/30 by T.Soneoka
*/
#if (0)
**	/* 
**	** ＤＳ２に噛んだ状態でのストップキー連打でループ
**	** ここでSYS_FEED_OUTを落とした場合、このタイミングでストップキーが押下されると
**	** 原稿排出タスクがデリートされる前に、クリエイトされてしまう
**	** SCN_Close()でセットされたSYS_FEED_OUTを親タスクの終了処理ルーチンで落とすようにします
**	** 1999/03/09 by T.Soneoka
**	*/
**	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FEED_OUT;
#endif
	CMN_EnableInterrupt();
#endif

	/*
	** 原稿読み取り最後に、ＴＸモータ停止／ランプＯｆｆします
	** 1999/03/11 by T.Soneoka
	*/
	StopTxMotor();
	LampOff();

/*
** NTTファネット不具合指摘 No.6 2002/10/30 by T.Soneoka
** CluchOffしてからフィードアウトのマシンステータスをこかします 上から移動
*/
	/* 
	** ＤＳ２に噛んだ状態でのストップキー連打でループ
	** ここでSYS_FEED_OUTを落とした場合、このタイミングでストップキーが押下されると
	** 原稿排出タスクがデリートされる前に、クリエイトされてしまう
	** SCN_Close()でセットされたSYS_FEED_OUTを親タスクの終了処理ルーチンで落とすようにします
	** 1999/03/09 by T.Soneoka
	*/
	CMN_DisableInterrupt();
	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FEED_OUT;
	CMN_EnableInterrupt();

	exi_tsk();
}


/*
 *	Name:	Page Memory Store Task
 *	Create:	Tue Jan 13 14:09:09 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		void	PageMemoryStoreTask(void);
 *	Description:
 *		GateArray が書いた ScannerBuffer(SRAM)を読んで、
 *		Printer Page Memory に張る
 *	Notes:
 *		このタスクがクリエートされるときは、
 *		原稿が読取り可能な位置にあることが前提。
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	PageMemStoreTask(void)
{
	MESSAGE_t	Msg;						/* 親タスクへのメッセージ */

	UBYTE	*ScanBufPtr;
	BYTE	DummyScanCount;
	
	DummyScanCount = DummyScanLine;		/* 読み飛ばすライン数 */

#if (0) /* 効果なしのため削除 1999/03/01 by T.Soneoka */
**	while (!SleepDocStoreSubTask) { /* Ｂ４－＞Ａ４白筋対策、転送開始を一定にするため 1999/03/01 by T.Soneoka */
**		if ((SYS_ScannerCopyStopSwitch())
**		|| (!QueryIgnorePrinterError())) {
**			Msg.Message = MSG_DOCSTORE_STOPSW_ON;
**			break;
**		}
**		if (EnableStartToReadScanBuf()) {
**			break;
**		}
**		wai_tsk(1);
**	}
#endif

	while (!SleepDocStoreSubTask) {
		if ((SYS_ScannerCopyStopSwitch())
		|| (!QueryIgnorePrinterError())) {
			Msg.Message = MSG_DOCSTORE_STOPSW_ON;
			break;
		}

		if (EnableToReadScanBuf()) {
			if (EnableToWritePrtImageBuf4Copy()) {
				/* 1 Line 単位で Scanner Buffer から Page Memory に転送 */
				ScanBufPtr = GetLineAddress4ReadScanBuf();
				if (DummyScanCount <= 0) {
					PutLinePrintPageMem(ScanBufPtr, CurrentPage->Size); /* Include Readable Line Increment */
				} else {
					DummyScanCount--;
				}
				DecScanBufReadableLine();
			} else {
				wai_tsk(1);
			}
		} else {
#if (0) /* 1998/12/09 by T.Soneoka */
**			/* モータ起動要求がなく、励磁状態にある場合は、励磁ＯＦＦします  1998/12/08 by T.Soneoka */
**			if (!QueryTxMotorMoving()
**			&& (GaTmr0Status & TMEXCT)) {
**				StopTxMotor();
**			}
#endif
			/*
			** 原稿蓄積にて、１ページ読み取り完了する前に、原稿排出完了する仕様変更
			** で発見したバグ
			**  1999/02/25 by T.Soneoka
			*/
#if (0)
**			if (SCN_DocumentChanged == TRUE) {
#else
			if (CurrentPage->Position == DOC_POS_MOVE_TO_PUSH_STAMP) {
#endif
				Msg.Message = MSG_DOCSTORE_OK;
				break;
			} else {
				wai_tsk(1);
			}
		}
	}
	SleepDocStoreSubTask = TRUE;		/* 兄弟タスクを停止し、親タスクに制御を移すため */
	snd_msg (mbxno.SCN_Task, &Msg);
	wai_tsk(0xffff);
}

/*
 *	Name:	Exit Docuement Store Task
 *	Create:	Wed Feb 25 15:43:32 1998	by	ishiyama
 *	Synopsis:
 *		#inlcude	"scn_task.h"
 *		void	ExitPageMemoryStoreTask(void)
 *	Description:
 *		Page Memory Store Task の終了関数
 *			リソースの開放が目的
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ExitPageMemStoreTask(void)
{
	exi_tsk();
}


/*
 *	Name:	Check Document Page
 *	Create:	 1998/10/01 by T.Soneoka
 *	Description:
 *		ADF送信原稿蓄積で正常終了したが指定枚数に満たない時は
 *		枚数指定エラーとする
 *	Return Value:
 *		TRUE:	枚数チェックＯＫ
 *		FALSE:	枚数チェックＮＧ
 *	Change Log:
 *		
 */
UBYTE CheckNeedDocPageNum(void)
{
	if ((SCN_StoreData.Item == SYS_MEM_TX_FILE)
	&&	(SYB_CommandFile[SCN_StoreData.No].Page != 0)
	&&	(SCN_StoreData.Page < SYB_CommandFile[SCN_StoreData.No].Page)) {
		return(FALSE);
	}
	return (TRUE);
}

UBYTE CheckExceedDocPageNum(void)
{
	/* 仕様変更
	** 読み取り中において、ＤＳ２がＯＦＦした時点でＤＳ１もＯＦＦしていれば、今読んだ原稿が
	** 最終原稿であるという風に変更
	** by O.kimoto 1999/03/08
	*/
	if (NoNextDocument == TRUE) {
		return(TRUE);
	}
	
	if ((SCN_StoreData.Item == SYS_MEM_TX_FILE) && (SYB_CommandFile[SCN_StoreData.No].Page != 0)) {
		if (SCN_StoreData.Page < SYB_CommandFile[SCN_StoreData.No].Page) {
			return(FALSE);
		}
		else {
			return(TRUE);
		}
	}
	return (FALSE);
}


/*
 *	Name:	Increment Document Page
 *	Create:	 1998/10/01 by T.Soneoka
 *	Description:
 *		次原稿がある場合、ページを管理している変数をインクリメントする
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void IncPage(void)
{
	SCN_StoreData.Page++;
	SCN_IndexData.Page++;
	SYS_DocumentStorePage++;
}


/*
 *	Name:	Memory Write Parameter Initial
 *	Create:	 1998/10/01 by T.Soneoka
 *	Description:
 *		メモリライトの管理の初期化を行います
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void IniMemWriteParameter(void)
{
	/* 画像メモリのオープンパラメータをセットします */
	SCN_StoreData.Item		= SYS_DocumentStoreItem;
	SCN_StoreData.No		= SYS_DocumentStoreNo;
	SCN_StoreData.Page		= SYS_DocumentStorePage;
	SCN_StoreData.BoxNumber	= SYS_DocumentStoreBoxNumber;

	/* 画像メモリのブレーク用のパラメータをセットします */
	SCN_IndexData.Item		= SYS_DocumentStoreItem;
	SCN_IndexData.No		= SYS_DocumentStoreNo;
	SCN_IndexData.Page		= SYS_DocumentStorePage;
	SCN_IndexData.BoxNumber	= SYS_DocumentStoreBoxNumber;
}


/** Module Header For CIM-E ********************************************
		module		:	[セットされている原稿の排出監視タスク]
		function	:	[
						]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[
							#define	MSG_DOCUMENT_OUT_OK					1
							#define	MSG_DOCUMENT_OUT_ERROR				2
							#define	MSG_DOCUMENT_OUT_NEXTPAGE_OK		3
							#define	MSG_DOCUMENT_OUT_NEXTPAGE_ERROR		4
						]
		machine		:	[]
		language	:	[MSC(V53)]
		keyword		:	[]
		date		:	[94/6/27]
		author		:	[川崎真史]
************************************************************************/
void MAN_DocumentOutTask( void )
{
	UBYTE doc_stat;

	tskno_SCN_DocOutTask = 0xffff;

	StoreTaskMsg.Item = FROM_DOCUMENT_OUT;

	/* 原稿排出処理 */
	/*
	** スキャンクローズで原稿排出中は回線引きっぱなしになる不具合
	** 1999/02/01 by T.Soneoka
	*/
#if (0)
**	switch (SCN_Close((UBYTE)0)) {
#else
	switch (SCN_Close((UBYTE)FROM_MAIN)) {
#endif
	case	SCN_SCANNER_COVER_OPEN:	/** 排出中にカバーが開けれれた */
	case	SCN_DOC_FEED_ERROR:		/** 排出エラー */
		StoreTaskMsg.Message = MSG_DOCUMENT_OUT_ERROR;
		break;
	case	SCN_DOC_EXIT_OK:		/** 排出正常終了 */
		StoreTaskMsg.Message = MSG_DOCUMENT_OUT_OK;
		break;
	}

	wai_tsk( 10 );	/* MAN_Taskでカバーオープンにならないため待つ  1996/10/31 */

	snd_msg(mbxno.MAN_Task, &StoreTaskMsg);
	rcv_msg(mbxno.SCN_Task, &SCN_Msg);
	wai_tsk(0xFFFF);
}

void MAN_DocumentOutTaskExit( void )
{
	if (tskno_SCN_DocOutTask != 0xffff) {
		del_tsk(&tskno_SCN_DocOutTask);
	}
	exi_tsk();
}


/*
 *	Name:	Scanner Transmit Task
 *	Create:	 1998/10/29 by H.Hirao
 *	Synopsis:
 *	Description:
 *		スキャナ送信原稿蓄積タスク
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SCN_STxStoreTask(void)
{
	MESSAGE_t	*RcvMessage;				/* 受信メッセージ用エリア */
	BOOL	PageLoop;						/* 1Page 読取り処理継続 TRUE:継続,FALSE:中断 */

	tskno_SCN_WatchDocFeedTask = 0xffff;
	tskno_SCN_ScanPage = 0xffff;
	tskno_CDC_STxDMA_Task = 0xffff;

	SYS_DocumentStoreItem = SYS_MEM_FILE_EMPTY;	/* スキャナ送信を区別するために入れます 1999/06/29 by T.Soneoka */

	ScannerMode = SCANNER_DOC_SCAN_MODE;

	OpenScanner();				/* 読取りのための初期設定 */

	ExecutePushStamp = FALSE;
#if (PRO_STAMP == ENABLE)
	CMN_EvacuateStampSetting();
#endif

/*
** ここではDS1を見ないようにして、原稿搬送を実行します
** スキャナ割り込みの中で原稿引き抜きを見るようにします
** 1999/1/12 by T.Soneoka
*/
#if (0)
**	PageLoop = QueryDs1On();
**	if (!PageLoop) {	/* 先頭ページの読取り開始時に原稿が抜かれていた場合は繰込み不良で終了する */
**		CodecPageStatus = CDC_DOC_ERROR;
**	}
#else
	PageLoop = TRUE;
#endif
	while (PageLoop) {					/* Page Loop */
		PageLoop = FALSE;				/* default 設定 */

#if (PRO_STAMP == ENABLE)
		EnablePushStampEvent = TRUE;	/* 済みスタンプ押下イベント許可フラグ初期化 */
#endif

#if (0)
** 		/* ここでは、SYS_DocumentScanSizeを見るのはまずい！
** 		** この変数は、スキャナー単独で判断している変数であり、通信で判断している値とは
** 		** 必ず一致する保証はない！
** 		** by O.Kimoto 1999/01/12
** 		*/
** 		SYS_DocumentScanSize = CMN_GetDocumentScanSize();
#else
		SYS_DocumentScanSize = SYS_DocBlock.Src.Size;
#endif
		
		SetScanPageAttribute2(CurrentPage); /* 現在の Document の属性を設定 */

		SCN_StoreData.Code		= CurrentPage->Code;
		SCN_StoreData.Mode		= CurrentPage->Mode;
		SCN_StoreData.Size		= CurrentPage->Size;
		
		SleepDocStoreSubTask = FALSE;		/* Sub Task を Sleep 状態にするフラグ */
		cre_tsk(&tskno_SCN_WatchDocFeedTask, TSK_SCN_WATCHDOCUMENTFEEDTASK, &mbxno.SCN_Task);	/* フィーダーエラー監視タスク起動 */
		cre_tsk(&tskno_SCN_ScanPage, TSK_SCN_SCANPAGE, 0);	/* 原稿読取りタスク起動 */
		InzStorePageResource();								/* Task が途中で Delete されることを考慮 */
		/* cre_tsk(&tskno_CDC_STxDMA_Task, TSK_CDC_STXDMA_TASK, 0); */
		
		SCN_Open();		/* 読取り開始 */
		
		rcv_msg(mbxno.SCN_Task, &RcvMessage); /* 蓄積関連タスクの状況をメッセージで待ち受け */
		
		CloseScanPage();	/* 読取り終了 */

		if (tskno_CDC_STxDMA_Task != 0xffff) {
			del_tsk(&tskno_CDC_STxDMA_Task);
		}
		if (tskno_SCN_ScanPage != 0xffff) {
			del_tsk(&tskno_SCN_ScanPage);	/* 原稿読取りタスク終了 */
		}
		if (tskno_SCN_WatchDocFeedTask != 0xffff) {
			del_tsk(&tskno_SCN_WatchDocFeedTask);	/* フィーダーエラー監視タスク終了 */
		}

		/*
		 *	メッセージの変換と１ページの後処理
		 */
#if (0) /* changed by H.Hirao 1998/12/21 */
//		switch (RcvMessage->Message) {
//		case MSG_DOCSTORE_STOPSW_ON: /* 停止要求 from CDC_STxEncodePageTask */
//			CodecPageStatus = CDC_STOPPED;
//			TxStartFlag = 1; /* 
//			break;
//		case MSG_DOCSTORE_OK:		/* 蓄積正常終了 from CDC_STxEncodePageTask */
//			CodecPageStatus = CDC_RTC_DET;
//			TxStartFlag = 1;
//			SYB_LifeMonitor.ScanCount++;	/** ライフモニタの読取り枚数加算 */
//			PageLoop = TRUE;	/* 次ページ処理継続 */
//			/* SCN_DocumentChanged = FALSE; ちょっと戻します by H.Hirao 1998/12/21 */
//			CMN_EnableInterrupt();
//			rcv_msg(mbxno.SCN_Task, &RcvMessage); 	/* ＦＣＭと同期をとります */
//#if (0) /* RCV_MSGする前にクリアします 1998/12/9 by T.Soneoka */
//**			SCN_DocumentChanged = FALSE;
//#endif
//			SCN_DocumentChanged = FALSE;
//			break;
//		case MSG_DOCSTORE_MAXLINE_OVER:	/* 1m原稿長制限 from WatchDocFeedTask */
//			CodecPageStatus = CDC_DOC_OVER;
//			break;
//		case MSG_DOCSTORE_COVER_OPEN: /* カバーオープン from WatchDocFeedTask */
//		case MSG_DOCSTORE_FEED_ERROR: /* 繰込み不良 from WatchDocFeedTask */
//			CodecPageStatus = CDC_DOC_ERROR;
//			break;
//		default:
//			/* not reached */
//			break;
//		}
#else
		CMN_DisableInterrupt();
		switch (RcvMessage->Message) {
		case MSG_DOCSTORE_STOPSW_ON: /* 停止要求 from CDC_STxEncodePageTask */
			CodecPageStatus = CDC_STOPPED;
			TxStartFlag = 1;
			break;
		case MSG_DOCSTORE_OK:		/* 蓄積正常終了 from CDC_STxEncodePageTask */
			CodecPageStatus = CDC_RTC_DET;
			TxStartFlag = 1;
			SYB_LifeMonitor.ScanCount++;	/** ライフモニタの読取り枚数加算 */
			PageLoop = TRUE;	/* 次ページ処理継続 */
			SCN_DocumentChanged = FALSE;
			rcv_msg(mbxno.SCN_Task, &RcvMessage); 	/* ＦＣＭと同期をとります */
#if (0) /* RCV_MSGする前にクリアします 1998/12/9 by T.Soneoka */
**			SCN_DocumentChanged = FALSE;
#endif

#if (0)
** 			/* 仕様変更
** 			** 読み取り中において、ＤＳ２がＯＦＦした時点でＤＳ１もＯＦＦしていれば、今読んだ原稿が
** 			** 最終原稿であるという風に変更
** 			** by O.kimoto 1999/03/08
** 			*/
** 
** 			/*
** 			** 割り込みの中で次原稿の登録をここでやるように修正します
** 			** 割り込みの中で次原稿登録（CurrentPageとNextPageのつけ替え）した場合、
** 			** 次原稿登録したが、現在の原稿読み取り終了時に、次原稿読み取りしない場合（原稿枚数指定）、
** 			** SCN_Close()で排出処理をコールすると、次原稿まで排出されてしまう為
** 			** ここでしたほうがすっきりする
** 			** 1999/02/10 by T.Soneoka
** 			*/
** 			if (NextPage != NULL) {
** 				DeleteDocObj(&CurrentPage);
** 				CurrentPage = NextPage;
** 				NextPage = NULL;
** 			}
#else
			if (NoNextDocument == FALSE) {
				if (NextPage != NULL) {
					DeleteDocObj(&CurrentPage);
					CurrentPage = NextPage;
					NextPage = NULL;
				}
			}
#endif

			break;
		case MSG_DOCSTORE_MAXLINE_OVER:	/* 1m原稿長制限 from WatchDocFeedTask */
			CodecPageStatus = CDC_DOC_OVER;
			break;
		case MSG_DOCSTORE_COVER_OPEN: /* カバーオープン from WatchDocFeedTask */
		case MSG_DOCSTORE_FEED_ERROR: /* 繰込み不良 from WatchDocFeedTask */
			CodecPageStatus = CDC_DOC_ERROR;
			break;
		default:
			/* not reached */
			break;
		}
		CMN_EnableInterrupt();
#endif
	} /* Page Loop End */

	wai_tsk(0xffff);
}


void	SCN_STxStoreTaskExit(void)
{
	/*
	** スキャナ送信、強制終了時に子タスクからＳＴＯＰメッセージが来ずに
	** 強制的にSCN_STxStoreTaskがＤＥＬされた場合、CloseScanPage()が通らないので
	** その後、排出処理がコールされても、まだスキャン中ということで排出できない不具合
	** add 1 line 1999/2/1 by T.Soneoka
	*/
	CloseScanPage();

	if (tskno_CDC_STxDMA_Task != 0xffff) {
		del_tsk(&tskno_CDC_STxDMA_Task);
	}
	if (tskno_SCN_ScanPage != 0xffff) {
		del_tsk(&tskno_SCN_ScanPage);	/* 原稿読取りタスク終了 */
	}
	if (tskno_SCN_WatchDocFeedTask != 0xffff) {
		del_tsk(&tskno_SCN_WatchDocFeedTask);	/* フィーダーエラー監視タスク終了 */
	}

	/*
	** 原稿読み取り最後に、ＴＸモータ停止／ランプＯｆｆします
	** 1999/03/11 by T.Soneoka
	*/
	StopTxMotor();
	LampOff();
	
	exi_tsk();
}


/*-------------------------------------------------------------------------
** ATLANTAと共通のソースコードを使用するために、
** HINOKIでは不要な関数をここで定義だけします。
** 1998/06/10
*/
void SCN_GearBackLashTask(void)
{
	MESSAGE_t StoreTaskMsg; /* extern is added by h.kubo 1998/07/07 */

	StoreTaskMsg.Item = FROM_SCN_GEAR_BACK_LASH_TASK;
	StoreTaskMsg.Message = MSG_SCN_GEAR_BACK_LASH_END;

	snd_msg(mbxno.MAN_Task, &StoreTaskMsg);
	rcv_msg(mbxno.SCN_GearBackLashTask, &SCN_Msg);
	wai_tsk(0xFFFF);
}

void SCN_DocumentOutTestTask(void)
{
	wai_tsk(0xffff);
}


/* エンコードタスクからのイベント待ちのタスク、リスケジューラを走らせるため 1999/03/16 by T.Soneoka */
void SCN_DummyTask(void)
{
	while (1) {
		wai_evt(SCN_DUMMY_EVT);
	}
}
