/*************************************************************************
*	System			: POPLAR/ANZU-L
*	File Name		: man_prtm.c
*	Author			:
*	Date			: 1997/06/09
*	RealTimeOS		: RISCモニタ
*	Description		: メインタスクMAN_Task()のメッセージ処理部
*					: プリント関連部
*	Module Name		: MAN_FromPRN_LST_PrintTask()
*					: MAN_FromPRN_ImagePrintTask()
*					: MAN_FromPRN_ResetTask()
*					: MAN_FromPRN_WarmUpTask()
*					: MAN_FromPRN_ManualDocInTask()
*					: MAN_FromPRN_AllPagePrintTask()
*					: MAN_FromTestTest()
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
#include  "\src\atlanta\define\sysdoc.h"

/*MON*/
#include  "\src\atlanta\sh7043\define\def_tib.h"
#include  "\src\atlanta\sh7043\define\def_evtn.h"
/*MEM*/
#include  "\src\atlanta\define\mem_def.h"

/*参照ファイル*/
/*SYS*/
#include  "\src\atlanta\ext_v\bkupram.h"
#include  "\src\atlanta\ext_v\sys_data.h"
#include  "\src\atlanta\ext_v\man_data.h"
/*MON*/
#include  "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include  "\src\atlanta\sh7043\ext_v\extv_sem.h"
/*PRN*/
#if (PRO_PRINT_TYPE == LED)
#include  "\src\atlanta\prt\ph3\define\prn_pro.h"
#include  "\src\atlanta\prt\ph3\ext_v\prn_data.h"
#endif
#if (PRO_PRINT_TYPE == LASER)
#include  "\src\atlanta\prt\sp322\ext_v\prn_data.h"
#include  "\src\atlanta\prt\sp322\ext_v\prn_tbl.h"
#endif
#if (PRO_PC_PRINT == ENABLE)
#include  "\src\atlanta\ext_v\dpr_data.h"
#endif

/*プロトタイプ宣言*/
#include  "\src\memsw\define\mems_pro.h"
#include  "\src\atlanta\define\uni_pro.h"
#include  "\src\atlanta\define\mon_pro.h"
#include  "\src\atlanta\define\man_pro.h"
#include  "\src\atlanta\define\cmn_pro.h"
#include  "\src\atlanta\define\mem_pro.h"

#if (PRO_SECURITY_RX == ENABLE)
	/*#include  "\src\atlanta\opr\ank\define\opr_pro.h"*/
	void	ClearSecurityRxChkMsgPrint(void);
#endif

#if (PRO_RELAYED_REPORT == ENABLE) /* 95/02/21 Y.Suzuki */
	#include "\src\atlanta\ext_v\fcm_data.h"
#endif

/* 連続コピーテスト */
#include "\src\atlanta\define\mntsw_c.h"
#include "\src\atlanta\define\mntsw_h.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\sysscan.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\define\scn_pro.h"

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/13 */
#include "\src\atlanta\ext_v\sys_inf.h"
void	CMN_ReleaseMailBox(UBYTE);
void	CMN_ClearRxMailBox(UBYTE);
void	ReStartRxMailManualPrint(UBYTE);
void	CMN_ClearAllCommandCounter(void);
void	CMN_ClearPrintRequest(UBYTE,UBYTE);
void	CMN_ClearRxMailCounter(UBYTE);
#endif

#if (PRO_CIPHER == ENABLE) /*By Y.Suzuki 1998/07/24*/
#include "\src\atlanta\scd\ext_v\cph_data.h"
#endif

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/08/26 Y.Matsukuma */
#include  "\src\atlanta\opr\ank\define\opr_pro.h"
#include  "\src\atlanta\opr\ank\ext_v\opr_data.h"
#endif
void	ContCopyTest(void);	/* For Test By M.Tachiban 1997/11/06 */

/*************************************************************************
	module		:[リストプリントタスクからのメッセージ処理]
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
void	MAN_FromPRN_LST_PrintTask(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;
	UWORD	prt_item;
	UWORD	prt_message;
	UWORD	prt_sub_message1;
	UWORD	prt_sub_message2;

#if 0 /* (PRO_RELAYED_REPORT == ENABLE) */
	unsigned	int					h, k, l; /* h, k, l 追加 95.02.21 Y.Suzuki */
#endif

	prt_item = item;
	prt_message = message;
	prt_sub_message1 = sub_message1;
	prt_sub_message2 = sub_message2;

	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	snd_msg(mbxno.LST_Task, &MainTaskMessage);
#if (PRO_PRINT_TYPE == LASER)
	SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
	SYS_AutoShutOFF_Timer = CHK_UNI_PrinterAutoShutTime();	/* UNI :NEw MEMORY SWITCH 対応1996/04/16 Eguchi */
#endif
#if (PRO_PRINT_TYPE == LED)
	SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PRINT_END_WAIT;	/* By M.Tachibana 1997/10/13 */
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/09/02 H.Yoshikawa */
	SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif
	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_LIST_PRINT; /** リスト・プリント実行中をクリア */
	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT;
	/*
	** プリント枚数がドラムの寿命を超えていたら、ユーザーへドラム交換の表示出す。
	** ドラム寿命は５％の黒印字で２００００枚（ミノルタ仕様）
	** By S.Kawasaki 1996/06/20
	*/
#if (PRO_PRINT_TYPE == LASER)
	if (SYB_LifeMonitor.DrumLifeCount >= (UDWORD)PRN_DrumPrintMax) { /** ドラムの寿命 *//* UDWORDキャスト By M.Tachibana 1997/12/09 */
		SYS_MachineStatus[SYS_WARNING_STATUS] |= SYS_WARNING_DRUM_REPLACE;	/** ドラム交換表示／印字継続可能 */
	}
#endif
	switch (prt_message) {
	case MSG_PRN_LST_END: /** リストプリント終了 */
	case MSG_PRN_LST_PAPER_END: /* リストプリント終了で紙無し */
		switch (SYS_DocumentPrintItem) { /** リスト・プリントの種類 */
		case LST_SECURERCV_NOTICE:
			SYB_MailBox[SYS_DocumentPrintNo].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
			break;
		case LST_COMMERR_CHECKMSG:/* ﾁｪｯｸﾒｯｾｰｼﾞB ｺｳｼﾝ		 */
		case LST_MONITOR_REPORT:/* ﾁｪｯｸﾒｯｾｰｼﾞB ｺｳｼﾝ		 *//* By H.Y 1994/11/14 */
#if (PRO_RELAYED_REPORT == ENABLE) /* 95/02/21 Y.Suzuki */
#if 0 /* Changed by H.Kubo 1998/01/13 */
@@			if((SYB_CommandFile[SYS_DocumentPrintNo].Option.Item == SYS_RELAYED_TX) &&
@@				CHK_RelayedTxReport() ) {	  /** 不達通知送信がONで配信のチェックメッセージがプリントされた場合、 */
@@				h = RelayedTxDocumentStatus[SYS_DocumentPrintNo];/* 不達通知のコマンドNO */
@@				RelayedReportPrintStatus[SYS_DocumentPrintNo] |= PRINT_IS_OVER;	/* 竹内 Apr.10.1995 */
@@				if (SYB_CommandFile[h].Status == SYS_CMD_EXECUTE) {
@@					for (k = 0; k < SYS_EXEC_QUEUE_MAX; k++) {/** 実行終了の通信エラーチェック */
@@						if ((SYB_ExecQueue[k].Number.Command == (UBYTE)h) && /** ExecQueueのコマンド番号とコマンド・ファイルの番号が一致 */
@@							(SYB_ExecQueue[k].Status == SYS_EXEC_ERROR))  {	/* 通信エラー */
@@							break; /** 通信エラーがあった。 kはSYS_EXEC_QUEUE_MAXに達しない */
@@								   /** このパスを通らなければk==SYS_EXEC_QUEUE_MAXになる */
@@						}
@@					}
@@					if (k < SYS_EXEC_QUEUE_MAX) { /** 不達通知エラー終了 */
@@						if (CHK_RelayedReportPrint()) {		/** 不達通知プリントＯＮ */
@@							/** 不達通知の送信とプリント共に終了なら，コマンドファイルを消去する */
@@							if (RelayedReportPrintStatus[SYS_DocumentPrintNo] == (PRINT_IS_OVER | RELAYED_IS_OVER)) {
@@								/* 配信と不達通知のコマンドを消去 */
@@								CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)h);
@@								CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo);
@@							}
@@						}
@@						else {
@@							/* 配信と不達通知のコマンドを消去 */
@@							CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)h);
@@							CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo);
@@						}
@@					}
@@					else {		/** 不達通知ＯＫ終了 */
@@						if (CHK_RelayedReportPrint()) {		/** 不達通知プリントＯＮ */
@@							/** 不達通知の送信とプリント共に終了なら，コマンドファイルを消去する */
@@							if (RelayedReportPrintStatus[SYS_DocumentPrintNo] == (PRINT_IS_OVER | RELAYED_IS_OVER)) {
@@								/* 配信と不達通知のコマンドを消去 */
@@								CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)h);
@@								CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo);
@@							}
@@						}
@@					}
@@				}
@@			}
@@			else {
@@				CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo); /** 通常コマンドのクリア */
@@			}
#else
			MAN_ClearCommandAreaAfterLstPrt();
#endif /* 0 */
#else
			CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo); /** 通常コマンドのクリア */
#endif
			break;
		case LST_COMMERR_BATCH_CHECKMSG:/* 一括送信ﾁｪｯｸﾒｯｾｰｼﾞB ｺｳｼﾝ By S.K 7/7/1994*/
			CMN_ClearCommandArea(SYS_BATCH_TX, (UBYTE)SYS_DocumentPrintNo); /** 一括送信コマンドのクリア */
			break;
#if (PRO_SECURITY_RX == ENABLE)
		/********** ↓追加　1996/06/28　Eguchi *************/
		case LST_SEC_RX_MEMOVER_CHKMSG: /* セキュリティ受信モード中、受信メモリーオーバーメッセージ */
			ClearSecurityRxChkMsgPrint();
			break;
		/********** ↑追加　1996/06/28　Eguchi *************/
#endif
		/** 以下のファイルのジャム・リカバーはどないすんの？ TBD */
		/** case LST_JOURNAL_LIST:
			case LST_TXCONF_REPORT:
			case LST_POWER_OFF_NOTICE:
			case LST_DELSECURE_NOTICE:
			case LST_DELMEMORYRCV_NOTICE:
			case LST_DELRESERVECMD_NOTICE:
			case LST_DELPOLLING_NOTICE:
			case LST_COMERR_CHECKMSG:
			case LST_MRYOVER_CHECKMSG:
			case LST_MNLERR_CHECKMSG:
			case LST_RXMRYOVER_CHECKMSG:
			case LST_CATCHPHONE_CHECKMSG:
			break;
		**/
#if (PRO_F_CODE == ENABLE)
		case LST_FCODE_BOXRCV_NOTICE:	/* ＦコードBOX受信通知 1997/03/12  By T.Yamaguchi */
			if (SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus != SYS_SUB_ADDRESS_BOX_RECEIVING) {
				SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].MessageStatus = SYS_SUB_ADDRESS_BOX_MSG_EMPTY;
				SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].RxStoringNo = 0;	/*	 受信中ファイル番号リセット */
			}
			break;
		case LST_DEL_FCODE_BOX_DOC_NOTICE:/* Ｆコード原稿消去通知 */
			SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].MessageStatus = SYS_SUB_ADDRESS_BOX_MSG_EMPTY;

			/* 保存期間が経過したときに、蓄積原稿ファイルビットは消去しているが、ボックス自身が記憶している、
			** 受信原稿の有無の情報がクリアされていない。
			** by O.Kimoto 1999/01/19
			*/
			SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;	/* 原稿未蓄積をセット */

			break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/13 */
		case LST_INF_TEXT_MAIL:	/*　ｲﾝﾀｰﾈｯﾄFAX　TEXTﾒｰﾙﾌﾟﾘﾝﾄ　*/
			if (SYS_INF_RxMailBox[SYS_DocumentPrintNo].PrintPolicy == SYS_INF_MANUAL_PRINT) {
				SYS_INF_ManualPrintUser = SYS_INF_RxMailBox[SYS_DocumentPrintNo].UserNumber;
			}
			else {
				SYS_INF_ManualPrintUser = SYS_INF_USER_MAX;
			}
			MEM_ClearDoc(SYS_MEM_MAIL_RX_FILE, SYS_DocumentPrintNo, MEM_IGNORE_BOX_NUMBER);
			CMN_ReleaseMailBox((UBYTE)SYS_DocumentPrintNo);
			CMN_ClearRxMailBox((UBYTE)SYS_DocumentPrintNo);
		 #if (PRO_PRINT_TYPE == LASER)
			ReStartRxMailManualPrint(SYS_INF_ManualPrintUser);
		 #endif
			break;
		case LST_INF_ERASED_COMMAND_NOTICE:
			/*　今のところ1枚書いたら全ユーザー分クリアする　*/
			CMN_ClearAllCommandCounter();
			break;
		case LST_INF_ERASED_MAIL_NOTICE:
			CMN_ClearRxMailCounter((UBYTE)SYS_DocumentPrintNo);
			break;
		case LST_INF_ERROR_NOTICE:
		case LST_INF_SECURE_NOTICE:
			CMN_ClearPrintRequest((UBYTE)SYS_DocumentPrintItem,(UBYTE)SYS_DocumentPrintNo);
			break;
		case LST_INF_ADDRESS_LIST:
		case LST_INF_GROUP_LIST:
		case LST_INF_SETTING_LIST:
		case LST_INF_MAILCOM_LIST:
		case LST_INF_JOURNAL_LIST:
			/*　何もする必要がないはず　*/
			break;
#endif	/* by Y.Tanimoto end of "PRO_DIALUP_INTERNET_FAX == ENABLE" */
		}
		if (prt_message == MSG_PRN_LST_PAPER_END) { /** プリント終了で紙無し */
			SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER; /** 紙無し検出をセット */
		}
#if (PRO_PANEL == ANK)
		if (tskno_print_complete == 0xffff) {
			cre_tsk(&tskno_print_complete, TSK_CMN_MAN_TIMER10MSTASK, &PrintCompleteMessage);
		}
#endif
#if (PRO_PANEL == KANJI)				/* 漢字対応操作パネル */
		if (timer_print_complete == 0xff) {
			CMN_MultiTimer10msStart(&timer_print_complete,&PrintCompleteMessage);
		}
#endif
		break;
	case MSG_PRN_LST_STOPSW_ON:/** リスト・プリント停止処理 TBD */
		break;
	case MSG_PRN_LST_NO_LIST: /** リストプリントデータがなくプリント動作そのものを行わなかった TBD */
		break;
	case MSG_PRN_LST_NO_ID:
		break;
	case MSG_PRN_LST_NO_PAPER:
		SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER; /** 記録紙エラーをセット */
		break;
	case MSG_PRN_LST_PAPER_ERROR:
		/*
		** リストプリント時に、記録紙を引き上げるまでの間にプリンターカバーを
		** 開けると一瞬JAM LEDが点灯するのを止める対策。
		** By S.Kawasaki 1996/07/22
		*/
#if (PRO_PRINT_TYPE == LASER)	/* ANZUのみ By M.Tachibana 1997/05/17 */
		if (!(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN)) { /* By S.Kawasaki 1996/07/22 */
			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM; /** ジャム・エラーをセット */
		}
#endif
		break;
	case MSG_PRN_LST_NO_INK:/* プリンター・エラー処理 */
		SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_INK; /** ドナー切れをセット */
		break;
#if (PRO_PRINT_TYPE == LED)
	case MSG_PRN_LST_PRINTER_END:
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
		SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_PRINT_END_WAIT;	/* By M.Tachibana 1997/10/13 */
		SYS_AutoShutOFF_Timer = CHK_UNI_PrinterAutoShutTime();	/* UNI :NEw MEMORY SWITCH 対応1996/04/16 Eguchi */

#if defined(POPLAR_F)	/* FAN騒音対策 */
		SYS_AutoFanOffTimer = (UWORD)CMN_GetFanStopTimer();
#elif (defined(POPLAR_H) && defined(JP0)) /* V851 ＦＡＮ制御 By H.Fujimura 2002/07/11 */
		SYS_AutoFanOffTimer = (UWORD)CHK_UNI_FanTime();								/* 単位：分 *//* FAN停止用最長タイマー */
		SYS_AutoFanOffTimer2 = (UWORD)CHK_UNI_InternalTempIntervalTimer();		/* 単位：分 *//* FAN停止用監視タイマー */
#else
		SYS_AutoFanOffTimer = SYB_MaintenanceSwitch[MNT_SW_H8];
#endif
#if (PRO_FAN_TEST == ENABLE)	/* By M.Tachibana 2000/02/14 */
		if (SYS_MemorySwitch[81] == 0) {	/* MemorySwitch[I1] */
			if (PRN_SaveEnvironmentTemp < (float)SYS_MemorySwitch[80]) {	/* MemorySwitch[I0] ??℃未満 */
				SYS_AutoFanOffTimer = 0;
				PRN_FanStop();
			}
		}
#endif
		SYS_PrinterWakeupTimer = 0;
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/13 */
		if (SYS_DocumentPrintItem == LST_INF_TEXT_MAIL) {
			ReStartRxMailManualPrint(SYS_INF_ManualPrintUser);
		}
 #endif
		break;
#endif
	default:
		break;
	}
	/*
	** ＵＳＡ仕様のみ通信エラー発生後のエラーは、チェックメッセージ印字終了と同時に
	** 消去する仕様とします。F-82/92で採用済み。 By S.Kawasaki 1996/04/26
	** 全ての仕向け先に対応します M.Tachibana 1997/04/17
	*/
/*#if defined(USA)*/
	if (CHK_UNI_ClearCommunicationError()) {
		MAN_ClearCommunicationError();
	}
/*#endif*/
}


/*************************************************************************
	module		:[画像付きチェックメッセージタスクからのメッセージ処理]
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
void	MAN_FromPRN_ImagePrintTask(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	struct MEM_IndexData_t		MemoryRxErasePoint;
#if (PRO_CLASS1 == ENABLE)
	struct MEM_IndexData_t		CL1_MemoryRxErasePoint;
#endif
	UWORD	prt_item;
	UWORD	prt_message;
	UWORD	prt_sub_message1;
	UWORD	prt_sub_message2;

#if (PRO_RELAYED_REPORT == ENABLE)
	UWORD	h, k, l; /* h, k, l 追加 95.02.21 Y.Suzuki */
#endif

	prt_item = item;
	prt_message = message;
	prt_sub_message1 = sub_message1;
	prt_sub_message2 = sub_message2;

#if (PRO_PRINT_TYPE == LASER)
	if (tskno_PRN_ImagePrintTask != 0xffff) {
		del_tsk(&tskno_PRN_ImagePrintTask); /** メモリ・プリント・タスク停止 */
	}
	SYS_AutoShutOFF_Timer = CHK_UNI_PrinterAutoShutTime();	/* By M.Tachibana 1997/12/04 */
	/*
	** プリント枚数がドラムの寿命を超えていたら、ユーザーへドラム交換の表示出す。
	** ドラム寿命は５％の黒印字で２００００枚（ミノルタ仕様）
	** By S.Kawasaki 1996/06/20
	*/
	if (SYB_LifeMonitor.DrumLifeCount >= (UDWORD)PRN_DrumPrintMax) { /** ドラムの寿命 *//* UDWORDキャスト By M.Tachibana 1997/12/09 */
		SYS_MachineStatus[SYS_WARNING_STATUS] |= SYS_WARNING_DRUM_REPLACE;	/** ドラム交換表示／印字継続可能 */
	}
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/09/02 H.Yoshikawa */
	if (tskno_PRN_ImagePrintTask != 0xffff) {
		del_tsk(&tskno_PRN_ImagePrintTask); /** メモリ・プリント・タスク停止 */
	}
#endif

	switch (prt_message) {
	case MSG_PRN_IMAGE_END: /** メモリプリント終了 */
#if (0)	/* M.Tachibana 1997/04/17 */
**	case MSG_PRN_IMAGE_WAIT: /** メモリプリント・キューに登録終了 */
**	case MSG_PRN_IMAGE_WAIT_END: /** メモリプリント終了＋プリント・キューに登録 */
**	case MSG_PRN_IMAGE_PAPER_END: /** メモリプリント終了で紙無し */
**	case MSG_PRN_IMAGE_PRINT_DEC_ERROR: /** 蓄積原稿プリント中のデコードエラー（椛のみ） By O.K Jan,22,1995 **/
#endif

		switch (SYS_DocumentPrintClass) {
		case SYS_PRINT_CLASS_LIST_MEMORY:
		case SYS_PRINT_CLASS_LIST_MONITOR: /** 7/7/1994 */
#if (PRO_PRINT_TYPE == LASER)
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif
#if (PRO_PRINT_TYPE == LED)
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PRINT_END_WAIT;	/* By M.Tachibana 1997/10/13 */
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/09/02 H.Yoshikawa */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT; /** メモリ・プリント実行中をクリア */
#if (PRO_RELAYED_REPORT == ENABLE) /* 95/02/21 Y.Suzuki */
#if 0 /* Changed by H.Kubo 1998/01/13 */
@@			if((SYB_CommandFile[SYS_DocumentPrintNo].Option.Item == SYS_RELAYED_TX) &&
@@				(CHK_RelayedTxReport() != 0)) {	  /** 不達通知送信がONで配信のチェックメッセージがプリントされた場合、 */
@@				h = RelayedTxDocumentStatus[SYS_DocumentPrintNo];/* 不達通知のコマンドNO */
@@				RelayedReportPrintStatus[SYS_DocumentPrintNo] |= PRINT_IS_OVER;	/* 竹内 Apr.10.1995 */
@@				if (SYB_CommandFile[h].Status == SYS_CMD_EXECUTE) {
@@					for (k = 0; k < SYS_EXEC_QUEUE_MAX; k++) {/** 実行終了の通信エラーチェック */
@@						if ((SYB_ExecQueue[k].Number.Command == (UBYTE)h) && /** ExecQueueのコマンド番号とコマンド・ファイルの番号が一致 */
@@							(SYB_ExecQueue[k].Status == SYS_EXEC_ERROR))  {	/* 通信エラー */
@@							break; /** 通信エラーがあった。 kはSYS_EXEC_QUEUE_MAXに達しない */
@@								   /** このパスを通らなければk==SYS_EXEC_QUEUE_MAXになる */
@@						}
@@					}
@@					if (k < SYS_EXEC_QUEUE_MAX) { /** 不達通知エラー終了 */
@@						if (CHK_RelayedReportPrint()) {		/** 不達通知プリントＯＮ */
@@							/** 不達通知の送信とプリント共に終了なら，コマンドファイルを消去する */
@@							if (RelayedReportPrintStatus[SYS_DocumentPrintNo] == (PRINT_IS_OVER | RELAYED_IS_OVER)) {
@@								/* 配信と不達通知のコマンドを消去 */
@@								CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)h);
@@								CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo);
@@							}
@@						}
@@						else {
@@							/* 配信と不達通知のコマンドを消去 */
@@							CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)h);
@@							CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo);
@@						}
@@					}
@@					else {		/** 不達通知ＯＫ終了 */
@@						if (CHK_RelayedReportPrint()) {		/** 不達通知プリントＯＮ */
@@							/** 不達通知の送信とプリント共に終了なら，コマンドファイルを消去する */
@@							if (RelayedReportPrintStatus[SYS_DocumentPrintNo] == (PRINT_IS_OVER | RELAYED_IS_OVER)) {
@@								/* 配信と不達通知のコマンドを消去 */
@@								CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)h);
@@								CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo);
@@							}
@@						}
@@					}
@@				}
@@			}
@@			else {
@@				CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo); /** 通常コマンドのクリア */
@@			}
#else
			MAN_ClearCommandAreaAfterLstPrt();
#endif
#else
			CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo); /** 通常コマンドのクリア */
#endif
#if (0)	/* このメッセージはこない M.Tachibana 1997/04/17 */
**			if (prt_message == MSG_PRN_IMAGE_PAPER_END) { /** プリント終了で紙無し */
**				SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER; /** 紙無し検出をセット */
**				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= (SYS_PRINTER_PAPER_JAM);
**			}
**			else { /** プリンター初期化正常終了 */
**				/* Feb.23,1996 SYS_MachineStatus[SYS_PRINTER_STATUS] &= ~(SYS_PRINTER_NO_PAPER+SYS_PRINTER_PAPER_JAM+SYS_PRINTER_CUTTER_ERROR+SYS_PRINTER_NO_INK); */
**				SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~(SYS_PRINTER_NO_PAPER+SYS_PRINTER_NO_INK);
**				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~(SYS_PRINTER_PAPER_JAM);
**			}
#endif

#if (PRO_PANEL == ANK)
			if (tskno_print_complete == 0xffff) {
				cre_tsk(&tskno_print_complete, TSK_CMN_MAN_TIMER10MSTASK, &PrintCompleteMessage);
			}
#endif
#if (PRO_PANEL == KANJI)
			if (timer_print_complete == 0xff) {
				CMN_MultiTimer10msStart(&timer_print_complete,&PrintCompleteMessage);
			}
#endif
			break;
		case SYS_PRINT_CLASS_LIST_BA_MEMORY:  /** 7/7/1994 */
		case SYS_PRINT_CLASS_LIST_BA_MONITOR: /** 7/7/1994 */
#if (PRO_PRINT_TYPE == LASER)
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif
#if (PRO_PRINT_TYPE == LED)
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PRINT_END_WAIT;	/* By M.Tachibana 1997/10/13 */
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/09/02 H.Yoshikawa */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif

			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT; /** メモリ・プリント実行中をクリア */
			CMN_ClearCommandArea(SYS_BATCH_TX, (UBYTE)SYS_DocumentPrintNo); /** 一括送信コマンドのクリア */
#if (0)	/* このメッセージはこない M.Tachibana 1997/04/17 */
//			if (prt_message == MSG_PRN_IMAGE_PAPER_END) { /** プリント終了で紙無し */
//				SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER; /** 紙無し検出をセット */
//				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= (SYS_PRINTER_PAPER_JAM);
//			}
//			else { /** プリンター初期化正常終了 */
//				/* Feb.23,1996 SYS_MachineStatus[SYS_PRINTER_STATUS] &= ~(SYS_PRINTER_NO_PAPER+SYS_PRINTER_PAPER_JAM+SYS_PRINTER_CUTTER_ERROR+SYS_PRINTER_NO_INK); */
//				SYS_MachineStatus[SYS_PRINTER_STATUS1] &= ~(SYS_PRINTER_NO_PAPER+SYS_PRINTER_NO_INK);
//				SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~(SYS_PRINTER_PAPER_JAM);
//			}
#endif

#if (PRO_PANEL == ANK)
			if (tskno_print_complete == 0xffff) {
				cre_tsk(&tskno_print_complete, TSK_CMN_MAN_TIMER10MSTASK, &PrintCompleteMessage);
			}
#endif
#if (PRO_PANEL == KANJI)
			if (timer_print_complete == 0xff) {
				CMN_MultiTimer10msStart(&timer_print_complete,&PrintCompleteMessage);
			}
#endif
			break;
#if (PRO_CIPHER == ENABLE)	/* 1997/06/19  By T.Yamaguchi */
		case SYS_PRINT_CLASS_LIST_CIPHER:
 #if (PRO_PRINT_TYPE == LASER)
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
 #endif
 #if (PRO_PRINT_TYPE == LED)
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PRINT_END_WAIT;	/* By M.Tachibana 1997/10/13 */
 #endif
 #if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/09/02 H.Yoshikawa */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
 #endif
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT; /** メモリ・プリント実行中をクリア */
			SYB_CipherBox[SYS_DocumentPrintNo].MessageStatus = SYS_CIPHERBOX_MSG_EMPTY;
/* スクランブル受信通知リスト プリント後のアラーム鳴動、ＬＣＤ表示のため By Y.Suzuki 1998/02/10 */
#if (PRO_PANEL == ANK)
			if (tskno_print_complete == 0xffff) {
				cre_tsk(&tskno_print_complete, TSK_CMN_MAN_TIMER10MSTASK, &PrintCompleteMessage);
			}
#endif
#if (PRO_PANEL == KANJI)
			if (timer_print_complete == 0xff) {
				CMN_MultiTimer10msStart(&timer_print_complete,&PrintCompleteMessage);
			}
#endif
			break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/13 */
		case SYS_PRINT_CLASS_RETURNED_MAIL:
			/****************************/
			/*　プリンター使用中を解除　*/
			/****************************/
		 #if (PRO_PRINT_TYPE == LASER)
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
		 #endif
		 #if (PRO_PRINT_TYPE == LED)
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PRINT_END_WAIT;	/* By M.Tachibana 1997/10/13 */
		 #endif
		 #if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/09/02 H.Yoshikawa */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
 		 #endif
		 
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT; /** メモリ・プリント実行中をクリア */
			/************************************************/
			/*　プリント終了した原稿と受信管理テーブル削除　*/
			/************************************************/
			if (SYS_INF_RxMailBox[SYS_DocumentPrintNo].PrintPolicy == SYS_INF_MANUAL_PRINT) {
				SYS_INF_ManualPrintUser = SYS_INF_RxMailBox[SYS_DocumentPrintNo].UserNumber;
			}
			else {
				SYS_INF_ManualPrintUser = SYS_INF_USER_MAX;
			}
			if (MEM_CountTotalPage(SYS_DocumentPrintItem, SYS_DocumentPrintNo, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {
				MEM_ClearDoc(SYS_DocumentPrintItem, SYS_DocumentPrintNo, MEM_IGNORE_BOX_NUMBER);
			}
			CMN_ReleaseMailBox((UBYTE)SYS_DocumentPrintNo);
			CMN_ClearRxMailBox((UBYTE)SYS_DocumentPrintNo);
		 #if (PRO_PRINT_TYPE == LASER)
			ReStartRxMailManualPrint(SYS_INF_ManualPrintUser);
		 #endif
			/**********************/
			/*　プリント完了表示　*/
			/**********************/
		 #if (PRO_PANEL == ANK)
			if (tskno_print_complete == 0xffff) {
				cre_tsk(&tskno_print_complete, TSK_CMN_MAN_TIMER10MSTASK, &PrintCompleteMessage);
			}
		 #endif
		 #if (PRO_PANEL == KANJI)
			if (timer_print_complete == 0xff) {
				CMN_MultiTimer10msStart(&timer_print_complete,&PrintCompleteMessage);
			}
		 #endif
			break;
#endif	/* by Y.Tanimoto end of "PRO_DIALUP_INTERNET_FAX == ENABLE" */
		default: /** ここに来たらバグ */
#if (PRO_PRINT_TYPE == LASER)
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif
#if (PRO_PRINT_TYPE == LED)
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PRINT_END_WAIT;	/* By M.Tachibana 1997/10/13 */
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/09/02 H.Yoshikawa */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif

			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT; /** メモリ・プリント実行中をクリア */
#if (0)	/* このメッセージはこない M.Tachibana 1997/04/17 */
//			if (prt_message == MSG_PRN_IMAGE_PAPER_END) { /** プリント終了で紙無し */
//				SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER; /** 紙無し検出をセット */
//			}
//			else  { /* TBD */ }
#endif

			break;
		}
#if (PRO_CIPHER == ENABLE)	/* By Y.Suzuki 1997/08/05 */
		if (((SYS_CipherComExec == SYS_DECIPHER_EXEC) || (SYS_CipherComExec == SYS_TX_DOC_DECIPHER_EXEC))
			&& ((SYS_DocumentPrintItem == SYS_MEM_TX_DECIPHER_FILE) || (SYS_DocumentPrintItem == SYS_MEM_TX_DECIPHER_FILE))) {
			/* 暗号化解除プリントが正常終了してからステータスをoffする */
			/* スクランブル解除プリント中にスクランブル受信があった場合、受信終了後のスクランブル解除プリントが不完全だった。
			スクランブル受信通知リストプリント後、SYS_CIPHERCOMEXECがOFFされていたため。
			By Y.Suzuki 1998/08/11 */
			SYS_CipherComExec = 0;
		}
#endif
		break;
	case MSG_PRN_IMAGE_STOPSW_ON: /** メモリ・プリント停止処理 */
		if ((SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_MEMORY) ||
			(SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_MONITOR)) { /* 7/7/1994 */
			if (CHK_StopMemCheckMsg()) {	/** 原稿付きCheckMsgで停止キー有効 *//* 竹内 Apr.25.1995 */
#if (PRO_RELAYED_REPORT == ENABLE)	/* 不達通知のため変更  竹内 Apr.25.1995 */
				if ((SYB_CommandFile[SYS_DocumentPrintNo].Option.Item == SYS_RELAYED_TX)
				&&	(CHK_RelayedTxReport() != 0)) {	  /** 不達通知ＯＮで配信のチェックメッセージプリントされた */
					h = RelayedTxDocumentStatus[SYS_DocumentPrintNo];	/* 不達通知のコマンドNO */
					RelayedReportPrintStatus[SYS_DocumentPrintNo] |= PRINT_IS_OVER;
					if (CHK_RelayedReportPrint()) {		/** 不達通知プリントＯＮ */
						/** 不達通知の送信とプリント共に終了なら，コマンドファイルを消去する */
						if (RelayedReportPrintStatus[SYS_DocumentPrintNo] == (PRINT_IS_OVER | RELAYED_IS_OVER)) {
							/* 配信と不達通知のコマンドを消去 */
							CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)h);
							CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo);
						}
					}
					else {
						/* 配信と不達通知のコマンドを消去 */
						CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)h);
						CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo);
					}
				}
				else {	/** 原稿付きCheckMsgで停止キー有効 *//* 竹内 Apr.25.1995 */
					CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo); /** 通常コマンドのクリア */
				}
#else
				CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo); /** 通常コマンドのクリア */
#endif
			}
#if (PRO_PRINT_TYPE == LASER)
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif
#if (PRO_PRINT_TYPE == LED)
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PRINT_END_WAIT;	/* By M.Tachibana 1997/10/13 */
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/09/02 H.Yoshikawa */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT; /** メモリ・プリント実行中をクリア */
			/** 完了通知? TBD  */
		}
		else if ((SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_BA_MEMORY) ||
				(SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_BA_MONITOR)) { /* 7/7/1994 */
			CMN_ClearCommandArea(SYS_BATCH_TX, (UBYTE)SYS_DocumentPrintNo); /** 一括送信コマンドのクリア */
#if (PRO_PRINT_TYPE == LASER)
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif
#if (PRO_PRINT_TYPE == LED)
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PRINT_END_WAIT;	/* By M.Tachibana 1997/10/13 */
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/09/02 H.Yoshikawa */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT; /** メモリ・プリント実行中をクリア */
			/** 完了通知? TBD  */
		}
		break;
	case MSG_PRN_IMAGE_PAPER_ERROR:
#if (0)	/* By M.Tachibana 1997/05/17 */
//#if (PRO_PRINT_TYPE != LASER)	/* Dec.01,94  by NOBUKO 桐のみジャム・エラーはセット済みです */
//		SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM; /** ジャム・エラーをセット */
//#endif
#endif
#if (PRO_PRINT_TYPE == LASER)
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif
#if (PRO_PRINT_TYPE == LED)
		SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PRINT_END_WAIT;	/* By M.Tachibana 1997/10/13 */
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/09/02 H.Yoshikawa */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_IMAGE_PRINT+SYS_MULTI_COPY); /** 7/19/1994 QAT SATSUKI メモリ・プリント実行中をクリア */
		break;
#if (PRO_PRINT_TYPE == LED)
	case MSG_PRN_IMAGE_PRT_END:
		if (tskno_PRN_ImagePrintTask != 0xffff) {
			del_tsk(&tskno_PRN_ImagePrintTask); /** メモリ・プリント・タスク停止 */
		}
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
		SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_PRINT_END_WAIT;	/* By M.Tachibana 1997/10/13 */
		SYS_AutoShutOFF_Timer = CHK_UNI_PrinterAutoShutTime();	/* By M.Tachibana 1997/12/04 */

#if defined(POPLAR_F)	/* FAN騒音対策 */
		SYS_AutoFanOffTimer = (UWORD)CMN_GetFanStopTimer();
#elif (defined(POPLAR_H) && defined(JP0)) /* V851 ＦＡＮ制御 By H.Fujimura 2002/07/11 */
		SYS_AutoFanOffTimer = (UWORD)CHK_UNI_FanTime();								/* 単位：分 *//* FAN停止用最長タイマー */
		SYS_AutoFanOffTimer2 = (UWORD)CHK_UNI_InternalTempIntervalTimer();		/* 単位：分 *//* FAN停止用監視タイマー */
#else
		SYS_AutoFanOffTimer = SYB_MaintenanceSwitch[MNT_SW_H8];
#endif
#if (PRO_FAN_TEST == ENABLE)	/* By M.Tachibana 2000/02/14 */
		if (SYS_MemorySwitch[81] == 0) {	/* MemorySwitch[I1] */
			if (PRN_SaveEnvironmentTemp < (float)SYS_MemorySwitch[80]) {	/* MemorySwitch[I0] ??℃未満 */
				SYS_AutoFanOffTimer = 0;
				PRN_FanStop();
			}
		}
#endif
		SYS_PrinterWakeupTimer = 0;
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/13 */
		if (SYS_DocumentPrintClass == SYS_PRINT_CLASS_RETURNED_MAIL) {
			ReStartRxMailManualPrint(SYS_INF_ManualPrintUser);
		}
 #endif
		break;
#endif
	default:
#if (PRO_PRINT_TYPE == LASER)
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif
#if (PRO_PRINT_TYPE == LED)
		SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PRINT_END_WAIT;	/* By M.Tachibana 1997/10/13 */
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/09/02 H.Yoshikawa */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_IMAGE_PRINT+SYS_MULTI_COPY); /** QAT SATSUKI 7/19/1994 メモリ・プリント実行中/Multi Copy をクリア */
		break;
	}
	/*
	** ＵＳＡ仕様のみ通信エラー発生後のエラーは、チェックメッセージ印字終了と同時に
	** 消去する仕様とします。F-82/92で採用済み。 By S.Kawasaki 1996/04/26
	** 全ての仕向け先に対応します M.Tachibana 1997/04/17
	*/
/*#if defined(USA)*/
	if (CHK_UNI_ClearCommunicationError()) {
		MAN_ClearCommunicationError();
	}
/*#endif*/
}


/*************************************************************************
	module		:[プリンターリセットタスクからのメッセージ処理]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/12]
	author		:[小谷正樹]
*************************************************************************/
void	MAN_FromPRN_ResetTask(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	UWORD	prt_item;
	UWORD	prt_message;
	UWORD	prt_sub_message1;
	UWORD	prt_sub_message2;

	prt_item = item;
	prt_message = message;
	prt_sub_message1 = sub_message1;
	prt_sub_message2 = sub_message2;

	switch (prt_message) {
	case MSG_PRN_RESET_END:
		/*
		** プリンターリセットタスクの停止
		** By S.Kawasaki 1996/07/16
		*/
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY;
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_PRINT_JAM_RECOVER);
		if (tskno_PRN_PrinterResetTask != 0xffff) {
			del_tsk(&tskno_PRN_PrinterResetTask);
		}
		break;
	default:
		break;
	}
}


#if (PRO_PRINT_TYPE == LED)
/*************************************************************************
	module		:[プリンターウォームアップタスクからのメッセージ処理]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/11/18]
	author		:[橘正樹]
*************************************************************************/
void	MAN_FromPRN_WarmUpTask(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	UWORD	prt_item;
	UWORD	prt_message;
	UWORD	prt_sub_message1;
	UWORD	prt_sub_message2;

	prt_item = item;
	prt_message = message;
	prt_sub_message1 = sub_message1;
	prt_sub_message2 = sub_message2;

	switch (prt_message) {
	case MSG_PRN_WARMUP_END:
		if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PRINTER_POWER_ON) {
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_PRINTER_POWER_ON;
		}
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY;
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_PRINT_WARMUP;
		if (tskno_PRN_PrinterWarmUpTask != 0xffff) {
			del_tsk(&tskno_PRN_PrinterWarmUpTask);
		}
		SYS_AutoShutOFF_Timer = CHK_UNI_PrinterAutoShutTime();	/* Add 3line By M.Tachibana 1998/01/24 */

#if defined(POPLAR_F)	/* FAN騒音対策 */
		SYS_AutoFanOffTimer = (UWORD)CMN_GetFanStopTimer();
#elif (defined(POPLAR_H) && defined(JP0)) /* V851 ＦＡＮ制御 By H.Fujimura 2002/07/11 */
		SYS_AutoFanOffTimer = (UWORD)CHK_UNI_FanTime();								/* 単位：分 *//* FAN停止用最長タイマー */
		SYS_AutoFanOffTimer2 = (UWORD)CHK_UNI_InternalTempIntervalTimer();		/* 単位：分 *//* FAN停止用監視タイマー */
#else
		SYS_AutoFanOffTimer = SYB_MaintenanceSwitch[MNT_SW_H8];
#endif
		SYS_PrinterWakeupTimer = 0;
		break;
	case MSG_PRN_WAKEUP_END:
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY;
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_PRINT_WARMUP;
		SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_PRINTER_WAKEUP;
		if (tskno_PRN_PrinterWarmUpTask != 0xffff) {
			del_tsk(&tskno_PRN_PrinterWarmUpTask);
		}
		PRN_PrinterSleep();
/*		PRN_FanStop();	By M.Tachibana 1998/02/20 */
		SYS_PrinterWakeupTimer = SYB_MaintenanceSwitch[MNT_SW_H9];
		break;
	default:
		break;
	}
}
#endif

#if (PRO_PRINT_TYPE == LED)
/*************************************************************************
	module		:[手差し原稿繰込みタスクからのメッセージ処理]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1997/11/25]
	author		:[橘正樹]
*************************************************************************/
void	MAN_FromPRN_ManualDocInTask(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	UWORD	prt_item;
	UWORD	prt_message;
	UWORD	prt_sub_message1;
	UWORD	prt_sub_message2;

	prt_item = item;
	prt_message = message;
	prt_sub_message1 = sub_message1;
	prt_sub_message2 = sub_message2;

	switch (prt_message) {
	case MSG_PRN_MANUAL_DOC_IN_OK:
	case MSG_PRN_MANUAL_DOC_IN_ERROR:
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY;
		if (tskno_PRN_ManualDocInTask != 0xffff) {
			del_tsk(&tskno_PRN_ManualDocInTask);
		}
		break;
	default:
		break;
	}
}
#endif


/*************************************************************************
	module		:[連続プリントタスクからのメッセージ処理]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/12]
	author		:[小谷正樹]
*************************************************************************/
void	MAN_FromPRN_AllPagePrintTask(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	UWORD	prt_item;
	UWORD	prt_message;
	UWORD	prt_sub_message1;
	UWORD	prt_sub_message2;

#if (PRO_CIPHER == ENABLE)
	MESSAGE_t	MainTaskMessage;/*By Y.Suzuki 1998/07/10*/
	MESSAGE_t	*MessageControl;
#endif

	prt_item = item;
	prt_message = message;
	prt_sub_message1 = sub_message1;
	prt_sub_message2 = sub_message2;

#if (PRO_PRINT_TYPE == LASER)
	if (SYB_LifeMonitor.DrumLifeCount >= (UDWORD)PRN_DrumPrintMax) { /** ドラムの寿命 *//* UDWORDキャスト By M.Tachibana 1997/12/09 */
		SYS_MachineStatus[SYS_WARNING_STATUS] |= SYS_WARNING_DRUM_REPLACE;	/** ドラム交換表示／印字継続可能 */
	}
#endif

	switch (prt_message) {
	case MSG_PRN_IMAGE_ALLPAGE_END:	/** 連続プリント実行時に全ページ正常にプリントできた */
	case MSG_PRN_IMAGE_STOP:		/** ストップボタンが押された */
#if (PRO_PRINT_TYPE == LASER)
		if (tskno_PRN_ImagePrintTask != 0xffff) {
			del_tsk(&tskno_PRN_ImagePrintTask); /** メモリ・プリント・タスク停止 */
		}
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
		SYS_AutoShutOFF_Timer = CHK_UNI_PrinterAutoShutTime();	/* UNI :NEw MEMORY SWITCH 対応1996/04/16 Eguchi */
#endif
#if (PRO_PRINT_TYPE == LED)
		SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PRINT_END_WAIT;	/* By M.Tachibana 1997/10/13 */
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)
		if (tskno_PRN_ImagePrintTask != 0xffff) {
			del_tsk(&tskno_PRN_ImagePrintTask); /** メモリ・プリント・タスク停止 */
		}
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif
		switch (SYS_DocumentPrintItem) { /** 原稿の種別 */
		case SYS_MEM_MULTI_COPY_FILE: /** マルチコピー原稿 */
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_MULTI_COPY; /** マルチ・コピー実行中をクリア */
			SYB_MultiCopyFile[SYB_MultiCopyReadPoint].Status = SYS_MCOPY_EMPTY;
			SYB_MultiCopyReadPoint++;														/** マルチ・コピ－原稿読みだし用ポインタ－を進める */
			if (SYB_MultiCopyReadPoint >= SYS_MULTI_COPY_MAX) {
				SYB_MultiCopyReadPoint = 0;
			}
			break;
		case SYS_MEM_MANUAL_COPY_FILE: /* 手差しコピー原稿 */
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_MANUAL_COPY;	/* 手差しコピー中クリア */
			SYB_ManualCopyFile.Status = SYS_MCOPY_EMPTY;
			break;
		case SYS_MEM_RX_FILE: /** メモリ受信原稿 */
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT; /** メモリ・プリント実行中をクリア */
			/* メモリ受信テーブル再初期化 */
			MemoryRxPrintPoint = &SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint];
			MemoryRxPrintPoint->Status = SYS_MEMORY_RX_EMPTY;
			MemoryRxPrintPoint->StorePage = 0;
			MemoryRxPrintPoint->RotatePage = 1;
			MemoryRxPrintPoint->PrintPage = 1;
			MemoryRxPrintPoint->ErasePage = 1;
			MemoryRxPrintPoint->Protect	  = SYS_PROTECT_OFF; /* 受信原稿プリントプロテクトＯＦＦ 1995/12/22 Eguchi */
#if 0	/* POPLAR変更 1997/03/07  By T.Yamaguchi */
//			SYB_MemoryRxPrintReadPoint++;
//			if (SYB_MemoryRxPrintReadPoint >= SYS_MEMORY_RX_MAX) {
//				SYB_MemoryRxPrintReadPoint = 0;
//			}
#endif
			MemoryRxPrintPoint->StackNumber = 0;
			MemoryRxPrintPoint->ReceiveTime = 0;
			MemoryRxPrintPoint->JournalPoint = 0;
/* 1997/03/07  By T.Yamaguchi */
			break;
#if (PRO_CLASS1 == ENABLE)
		case SYS_MEM_CL1_RX_FILE: /** メモリ受信原稿 */
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT; /** メモリ・プリント実行中をクリア */
			/* メモリ受信テーブル再初期化 */
			CL1_MemoryRxPrintPoint = &SYB_CL1_MemoryRxPrint[CL1_MemoryRxPrintReadPoint];
			CL1_MemoryRxPrintPoint->Status = SYS_MEMORY_RX_EMPTY;
			CL1_MemoryRxPrintPoint->StorePage = 0;
			CL1_MemoryRxPrintPoint->PrintPage = 1;
			CL1_MemoryRxPrintPoint->ErasePage = 1;
			CL1_MemoryRxPrintPoint->Protect	  = SYS_PROTECT_OFF; /* 受信原稿プリントプロテクトＯＦＦ 1995/12/22 Eguchi */
			CL1_MemoryRxPrintReadPoint++;
			if (CL1_MemoryRxPrintReadPoint >= SYS_MEMORY_RX_MAX) {
				CL1_MemoryRxPrintReadPoint = 0;
			}
			break;
#endif
		case SYS_MEM_SECURE_RX_FILE: /** 親展受信原稿 */
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT; /** メモリ・プリント実行中をクリア */
/** #if (PRO_PRINT_TYPE == THERMAL) **/
#if (PRO_PRINT_TYPE == THERMAL) || (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.26 K.Kawata */
			/*
			** 記録開始待機位置から記録紙待機位置へ移動中（この時間がラインプリンタの場合、長い）に、同一親展ボックスに対しての受信が、完了した場合、
			** すべての親展受信原稿が消去されてしまう。
			** 本当に親展受信原稿を全て印字した場合、イメージプリントメインで以下の処理を行っています by H.Hirao 1999/03/02
			*/
 #else
			if (SYB_MailBox[SYS_DocumentPrintNo].Status != SYS_MAILBOX_NO_SET)	{
				SYB_MailBox[SYS_DocumentPrintNo].Status = SYS_MAILBOX_SET;
			}
			SYB_MailBox[SYS_DocumentPrintNo].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
 #endif
			break;
#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/08/10 */
		case SYS_MEM_PC_RX_FILE: /** ＰＣプリント受信原稿 */
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT;
			SYB_PcRxPrint.Status = SYS_PC_RX_EMPTY;
			break;
#endif	/* #if (PRO_PC_PRINT == ENABLE) */
#if (PRO_F_CODE == ENABLE)	/* 1997/03/11  By T.Yamaguchi */
		case SYS_MEM_SUB_SECURE_FILE:
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT; /** メモリ・プリント実行中をクリア */
/*			MEM_ClearDocAndFATArea(SYS_MEM_SUB_SECURE_FILE, MEM_ALL_NO, (UBYTE)SYS_DocumentPrintBoxNumber); */
/*			SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET; */
/*			SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].StoredDocBit = 0; */
			break;
#endif
#if (PRO_CIPHER == ENABLE)
		case SYS_MEM_TX_DECIPHER_FILE:
		case SYS_MEM_DECIPHER_FILE:
		SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DESCRAMBLE_PRINT;
		SYB_CPH_RxPrint[0].Status = SYS_MCOPY_EMPTY;
		break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
		case SYS_MEM_MAIL_RX_FILE:
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT;
			if (SYS_INF_RxMailBox[SYS_DocumentPrintNo].PrintPolicy == SYS_INF_MANUAL_PRINT) {
				SYS_INF_ManualPrintUser = SYS_INF_RxMailBox[SYS_DocumentPrintNo].UserNumber;
			}
			else {
				SYS_INF_ManualPrintUser = SYS_INF_USER_MAX;
			}
			CMN_ReleaseMailBox((UBYTE)SYS_DocumentPrintNo);
			CMN_ClearRxMailBox((UBYTE)SYS_DocumentPrintNo);
		 #if (PRO_PRINT_TYPE == LASER)
			ReStartRxMailManualPrint(SYS_INF_ManualPrintUser);
		 #endif
			break;
		case SYS_MEM_MAIL_TX_FILE:
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT;
			break;
#endif
		default:	/** その他のメモリファイル */
			SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT; /** メモリ・プリント実行中をクリア */
			break;
		}
		if (prt_message == MSG_PRN_IMAGE_ALLPAGE_END) {
#if (PRO_PANEL == ANK)
			if (tskno_print_complete == 0xffff) {
				cre_tsk(&tskno_print_complete, TSK_CMN_MAN_TIMER10MSTASK, &PrintCompleteMessage);

 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/08/27 Y.Matsukuma */
				if (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) {
					if (OPR_MinoltaPatternCheck != 0xFF) {
						MinoltaTestPatternPrintCheck();
					}
					else {
						OPR_MinoltaPatternItem = 0xFF;	/* 1998/08/31 Y.Matsukuma */
						OPR_MinoltaDisplayCheck = 0xFF;
					}
				}
 #endif

			}
#endif
#if (PRO_PANEL == KANJI)
			if (timer_print_complete == 0xff) {
				CMN_MultiTimer10msStart(&timer_print_complete,&PrintCompleteMessage);
			}
#endif
		}
		break;
	case MSG_PRN_IMAGE_1PAGE_END:	/** 連続プリント実行時に１ページ正常にプリントできた */
#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/10/03 */
		if (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) {
			/** マルチプリントで指定部数分プリント終了したら */
			SYB_PcRxPrint.PrintEndPage = SYB_PcRxPrint.PrintPage-1;
		}
#endif
#if (PRO_CIPHER == ENABLE)/* By Y.Suzuki 1998/07/10 */
		if (SYS_DocumentPrintItem == SYS_MEM_DECIPHER_FILE) {
			if ((McopyPtr->PrintPage == 2) && (McopyPtr->StorePage == 1)) {
				/*1ページ目のプリント終了*/
				if (CipherReadPageNo == CipherData.PageNo) {/*１ページ目が最終ページのとき*/
					SYB_CPH_RxPrint[0].Status = SYS_MCOPY_EMPTY;/* By Y.Suzuki 1998/07/24 */
					SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DESCRAMBLE_PRINT;/*By Y.Suzuki 1998/07/24*/
				}
				if (!CipherStopOn) {/*ストップキーがおされてなければ By Y.Suzuki 1998/07/31*/
					/*ＯＰＲにてスクランブル原稿消去／消去しない選択 */
					MainTaskMessage.Item = FROM_MAIN;
					SYS_MachineStatus[SYS_CIPHER_STATUS] |= SYS_DESCRAMBLE_FIRST_PAGE;
					MainTaskMessage.Message = MSG_EXIT;
					snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
					/* 上のメッセージ受信部で下のメッセージを送信してくるので受信する。他の処理は特になし */
					rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
				}
				else {
					/* 1ページプリント中にスクランブル解除が停止された By Y.Suzuki 1998/08/04 */
					/* スクランブル受信原稿消去ｏｐｒを出さずにスクランブルタスクを停止させるための処理 */
					MainTaskMessage.Item = FROM_MAIN;
					MainTaskMessage.Message = MSG_OPT_DECIPHER_FROM_OPR;
					MainTaskMessage.SubMessage1 = FALSE;
					snd_msg(mbxno.SCD_CipherResult,&MainTaskMessage);
				}
			}
			/* スクランブル解除原稿が２ページしかない場合、全ページプリント完了時ここにくる。
			** エンドブザーを鳴らす処理をいれる。 By Y.Suzuki 98/07/23 */
			if ((McopyPtr->PrintPage == 2) && (McopyPtr->StorePage == 2)) {
				SYB_CPH_RxPrint[0].Status = SYS_MCOPY_EMPTY;/* By Y.Suzuki 1998/07/24 */
				SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DESCRAMBLE_PRINT;/*By Y.Suzuki 1998/07/24*/
				if (tskno_print_complete == 0xffff) {
					cre_tsk(&tskno_print_complete, TSK_CMN_MAN_TIMER10MSTASK, &PrintCompleteMessage);
				}
			}
		}
#endif
		break;
#if (PRO_PRINT_TYPE == LED)
	case MSG_PRN_IMAGE_PRINTER_END:
		if (tskno_PRN_ImagePrintTask != 0xffff) {
			del_tsk(&tskno_PRN_ImagePrintTask); /** メモリ・プリント・タスク停止 */
		}
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
		SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_PRINT_END_WAIT;	/* By M.Tachibana 1997/10/13 */
		SYS_AutoShutOFF_Timer = CHK_UNI_PrinterAutoShutTime();	/* UNI :NEw MEMORY SWITCH 対応1996/04/16 Eguchi */

#if defined(POPLAR_F)	/* FAN騒音対策 */
		SYS_AutoFanOffTimer = (UWORD)CMN_GetFanStopTimer();
#elif (defined(POPLAR_H) && defined(JP0)) /* V851 ＦＡＮ制御 By H.Fujimura 2002/07/11 */
		SYS_AutoFanOffTimer = (UWORD)CHK_UNI_FanTime();								/* 単位：分 *//* FAN停止用最長タイマー */
		SYS_AutoFanOffTimer2 = (UWORD)CHK_UNI_InternalTempIntervalTimer();		/* 単位：分 *//* FAN停止用監視タイマー */
#else
		SYS_AutoFanOffTimer = SYB_MaintenanceSwitch[MNT_SW_H8];
#endif
#if (PRO_FAN_TEST == ENABLE)	/* By M.Tachibana 2000/02/14 */
		if (SYS_MemorySwitch[81] == 0) {	/* MemorySwitch[I1] */
			if (PRN_SaveEnvironmentTemp < (float)SYS_MemorySwitch[80]) {	/* MemorySwitch[I0] ??℃未満 */
				SYS_AutoFanOffTimer = 0;
				PRN_FanStop();
			}
		}
#endif
		SYS_PrinterWakeupTimer = 0;

		/******** 連続コピーテスト *********/
		if (SYB_MaintenanceSwitch[MNT_SW_C6] & 0x02) {
			if (SYB_MaintenanceSwitch[MNT_SW_C9] & 0x40) {
				/* メモリー送信原稿後端が縮む件
				** 連続コピーにて再現テストを行う
				** T.Nose 1997/11/03
				*/
				break; /* 次のコピー蓄積を行わない */
			}
			if (CMN_CheckPrintEnable(SYS_MULTI_COPY) && SYS_ImagePrintStopSwitch() == 0) {
				ContCopyTest();
			}

		}
		/******** 連続コピーテスト（１０分インターバル） *********/
		if (SYB_MaintenanceSwitch[MNT_SW_H5] & 0x80) {
			SYB_MaintenanceSwitch[MNT_SW_H1] = SYB_MaintenanceSwitch[MNT_SW_H2];
		}
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/13 */
		if (SYS_DocumentPrintItem == SYS_MEM_MAIL_RX_FILE) {
			ReStartRxMailManualPrint(SYS_INF_ManualPrintUser);
		}
 #endif
		break;
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)

	/*---------------------------------------------------------------------
	** イニシャルカット終了時の処理(SAKAKI)
	** 1998/08/19 H.Yoshikawa
	*/
	case MSG_PRN_IMAGE_INITIAL_END:
		if (tskno_PRN_ImagePrintTask != 0xffff) {
			del_tsk(&tskno_PRN_ImagePrintTask); /** メモリ・プリント・タスク停止 */
		}
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /* プリンター使用中をクリア */
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT; /* イメージ・プリント中クリア */
#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* Modify by SMuratec 李 2004/07/07 */
 #if (PRO_PRINT_TYPE == THERMAL) && (PRO_DISPLAY_PRN_INITIALIZE == ENABLE) /* Added by SMuratec 李 2004/7/7 */
 /* 
 	DVT修正：プリンタ状態退避用変量が使用されので
 			  ここでは初期化動作を禁止必要です。
 			  SMuratec L.Z.W 2004/08/25
 */
/*		InitializeSensor();*/ 
 #endif
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
		break;
#endif
	default:	/** case MSG_PRN_ILLEGAL_ERROR		シリアル通信エラー */
#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/12/13 */
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)
		if (CMN_CheckMinoltaTestFuncEnable()) {
			if (SYS_MinoltaTestFuncData[SYS_DocumentPrintNo].Status == SYS_FUNC_TEST_DATA_PRINT) {		/* テストプリントしてる時 */
				/* Nothing */
			}
			else {
				if (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) {
					/** ジャムリカバリなしの時は，PrintPageをインクリメントする為 */
					SYB_PcRxPrint.PrintEndPage = SYB_PcRxPrint.PrintPage-1;
					if (!DPR_PCR_DataReceiving) {	/* By J.Miyazaki 1997/04/07 */
						if (SYB_PcRxPrint.StorePage < SYB_PcRxPrint.PrintPage) {
							MEM_ClearDoc(SYS_MEM_PC_RX_FILE, 0, MEM_IGNORE_BOX_NUMBER);
							SYB_PcRxPrint.Status = SYS_PC_RX_EMPTY;
							DPR_PCR_JamStatus = 0;
						}
					}
				}
			}
		}
		else {
			if (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) {
				/** ジャムリカバリなしの時は，PrintPageをインクリメントする為 */
				SYB_PcRxPrint.PrintEndPage = SYB_PcRxPrint.PrintPage-1;
				if (!DPR_PCR_DataReceiving) {	/* By J.Miyazaki 1997/04/07 */
					if (SYB_PcRxPrint.StorePage < SYB_PcRxPrint.PrintPage) {
						MEM_ClearDoc(SYS_MEM_PC_RX_FILE, 0, MEM_IGNORE_BOX_NUMBER);
						SYB_PcRxPrint.Status = SYS_PC_RX_EMPTY;
						DPR_PCR_JamStatus = 0;
					}
				}
			}
		}
 #else
		if (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) {
			/** ジャムリカバリなしの時は，PrintPageをインクリメントする為 */
			SYB_PcRxPrint.PrintEndPage = SYB_PcRxPrint.PrintPage-1;
			if (!DPR_PCR_DataReceiving) {	/* By J.Miyazaki 1997/04/07 */
				if (SYB_PcRxPrint.StorePage < SYB_PcRxPrint.PrintPage) {
					MEM_ClearDoc(SYS_MEM_PC_RX_FILE, 0, MEM_IGNORE_BOX_NUMBER);
					SYB_PcRxPrint.Status = SYS_PC_RX_EMPTY;
					DPR_PCR_JamStatus = 0;
				}
			}
		}
 #endif
#endif
#if (PRO_PRINT_TYPE == LASER)
		if (tskno_PRN_ImagePrintTask != 0xffff) {
			del_tsk(&tskno_PRN_ImagePrintTask); /** メモリ・プリント・タスク停止 */
		}
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
		SYS_AutoShutOFF_Timer = CHK_UNI_PrinterAutoShutTime();	/* UNI :NEw MEMORY SWITCH 対応1996/04/16 Eguchi */
#endif
#if (PRO_PRINT_TYPE == LED)
		SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PRINT_END_WAIT;	/* By M.Tachibana 1997/10/13 */
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998/09/16 H.Yoshikawa */
		if (tskno_PRN_ImagePrintTask != 0xffff) {
			del_tsk(&tskno_PRN_ImagePrintTask); /** メモリ・プリント・タスク停止 */
		}

  #if (PRO_PRINT_TYPE == THERMAL)	/* HINOKIプリント中ループ対策 2002/04/17 by T.Soneoka */
  		if (SYB_MaintenanceSwitch[MNT_SW_H8] & 0x10) {	/* 0x30->0x10 2002/04/18 by T.Soneoka */
			if (SYS_DocumentPrintItem == SYS_MEM_RX_FILE) { /** メモリ受信原稿 */
				/* メモリ受信テーブル再初期化 */
				MemoryRxPrintPoint = &SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint];
				MemoryRxPrintPoint->Status = SYS_MEMORY_RX_EMPTY;
				MemoryRxPrintPoint->StorePage = 0;
				MemoryRxPrintPoint->RotatePage = 1;
				MemoryRxPrintPoint->PrintPage = 1;
				MemoryRxPrintPoint->ErasePage = 1;
				MemoryRxPrintPoint->Protect	  = SYS_PROTECT_OFF; /* 受信原稿プリントプロテクトＯＦＦ 1995/12/22 Eguchi */
				MemoryRxPrintPoint->StackNumber = 0;
				MemoryRxPrintPoint->ReceiveTime = 0;
				MemoryRxPrintPoint->JournalPoint = 0;
			}
	  		SYB_MaintenanceSwitch[MNT_SW_H8] &= 0xEF;
		}
  #endif

		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
#endif

		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_IMAGE_PRINT; /** メモリ・プリント実行中をクリア *//* By H.Y 1994/10/31 */
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_MULTI_COPY; /** マルチ・コピー実行中をクリア *//* By H.Y 1994/10/31 */
		SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_MANUAL_COPY;	/* 手差しコピー中クリア */
		break;
	}
}


#if (PRO_PRINT_TYPE == LASER) /** TEST TEST */
/*************************************************************************
	module		:[テスト用のメッセージ処理]
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
void	MAN_FromTestTest(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;
	UWORD	prt_item;
	UWORD	prt_message;
	UWORD	prt_sub_message1;
	UWORD	prt_sub_message2;

	prt_item = item;
	prt_message = message;
	prt_sub_message1 = sub_message1;
	prt_sub_message2 = sub_message2;

	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	snd_msg(mbxno.SCN_Task, &MainTaskMessage); /** 同期用メッセージ */
	/* SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; */ /* プリンタ使用中セット */
	/* SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_MULTI_COPY;	 *//* Multi Copy使用中セット */
#if (0)
	if ((MDM_DebugSw == MDM_TEST_MEM_TX_G3) ||
		(MDM_DebugSw == MDM_TEST_MEM_TX_G3_ALL1)) {
		ModemMessage.Message = MSG_TEST_PIX_GO;
		snd_msg(mbxno.MDM_TaskSub, &ModemMessage);
		rcv_msg(mbxno.MAN_Task, &ModemMessage); /** タスクからメッセージ受信 */
	}
#endif
	SYS_DocumentPrintItem	= SYS_MEM_MULTI_COPY_FILE;
	SYS_DocumentPrintNo		= 0;
	SYS_DocumentPrintPageNo = 1;
	SYS_DocumentPrintClass	= SYS_PRINT_CLASS;
	cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /* 蓄積原稿プリント・タスク起動 */
}
#endif	/* #if (PRO_PRINT_TYPE == LASER) */


#if (PRO_PRINT_TYPE == LED)
/*************************************************************************
	module		:[連続コピーテスト用]
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
	date		:[1997/11/06]
	author		:[橘正樹]
*************************************************************************/
void	ContCopyTest(void)
{
	UBYTE	point;

	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FEED_IN;
	SYS_MachineStatus[SYS_RESOURCE_STATUS] |= (SYS_SCANNER_BUSY); /* スキャナー資源確保*/
	SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_DOC_STORE; /* 原稿蓄積をセット */

	SYS_FCOT_PrintStartRequest = FALSE;
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Status = SYS_MCOPY_STORE; /* 蓄積開始～蓄積完了までのステータス登録 */
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].StorePage = 0;
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].PrintPage = 1;
	if (SYB_MultiCopyWritePoint == 0) {
		point = SYS_MULTI_COPY_MAX - 1;		/* - 1 を追加 By M.Tachibana 1998/01/14 */
	}
	else {
		point = SYB_MultiCopyWritePoint - 1;
	}
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].ReserveNumber = SYB_MultiCopyFile[point].ReserveNumber;
/****
	if (SYB_MaintenanceSwitch[MNT_SW_H5] & 0x80) {
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].ReserveNumber = 2;
	}
	else {
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].ReserveNumber = 1;
	}
****/

	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].ExecutiveNumber = 1;
/*	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].SortType = SYS_NONE_SORT; */
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].SortType = SYB_MultiCopyFile[point].SortType;
/*	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Reduction = 100; */
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Reduction = SYB_MultiCopyFile[point].Reduction;
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].ScanType = SYS_FBS_SCAN;

/****************
	if (SYS_Paper1Size != SYS_NO_PAPER) {
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Cassette = 1;
		SCN_RegularDocumentSize = SYS_Paper1Size;
	}
	else if (SYS_Paper2Size != SYS_NO_PAPER) {
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Cassette = 2;
		SCN_RegularDocumentSize = SYS_Paper2Size;
	}
	else {
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Cassette = 3;
		SCN_RegularDocumentSize = SYS_Paper3Size;
	}
	switch (SCN_RegularDocumentSize) {
	case	SYS_B4_PAPER:
		SCN_RegularDocumentSize = SYS_REGULAR_SIZE_B4;
		break;
	case	SYS_B5R_PAPER:
		SCN_RegularDocumentSize = SYS_REGULAR_SIZE_B5R;
		break;
	case	SYS_A5R_PAPER:
		SCN_RegularDocumentSize = SYS_REGULAR_SIZE_A5R;
		break;
	default:
		SCN_RegularDocumentSize = SYS_REGULAR_SIZE_A4;
		break;
	}
*******************/
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Cassette = SYB_MultiCopyFile[point].Cassette;
	SCN_RegularDocumentSize = SYB_MultiCopyFile[point].ScanSize;
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].ScanSize = SCN_RegularDocumentSize;

	SYS_DocumentStoreItem = SYS_MEM_MULTI_COPY_FILE;
	SYS_DocumentStoreNo	  = (UWORD)SYB_MultiCopyWritePoint;
	SYS_DocumentStorePage = 1;
	SYS_DocumentStoreBoxNumber = 0;	/* 1997/03/13  By T.Yamaguchi */
	SYS_MultiProgramFlag = 0;

#if (PRO_FBS == ENABLE)
	/* FBS読取りのみ */
	SYS_ScannerExecMode = SCN_FBS;
	MirrorTaskInstruction = MIRROR_TASK_TO_FBS;
	SCN_MirrorReadyPosition = READY_POSITION_FBS;

	/** ミラーを読み取り開始位置へ移動させる */
	SYS_IsMirrorScanReady = FALSE;
	MirrorTaskRequest = TRUE;

#endif /* (PRO_FBS == ENABLE) */

	/* スキャン開始時にモーターが動かなくなることがあるため
	*  起動前にスキャナを初期化する
	*		1997/06/02 s.takeuchi
	*/
	SCN_Init();

	cre_tsk(&tskno_SCN_DocumentStoreTask, TSK_SCN_TASK, 0); /* 原稿蓄積タスク起動 */
}
#endif

#if (PRO_RELAYED_REPORT == ENABLE)	/*  H.Kubo 1998/01/13   */
/*************************************************************************
	module		:[中継送信の不達通知に対応した
					通信予約番号に対する発信スケジューラの消去
				]
	function	:[
		1. コマンドが不達通知を消去のときは、親の中継送信コマンドも消去。
		2. 不達通知でなければ、普通に消去。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/01/13]
	author		:[久保博]
*************************************************************************/
void	MAN_ClearCommandAreaAfterLstPrt( void )
{
	UBYTE h, k;
	if((SYB_CommandFile[SYS_DocumentPrintNo].Option.Item == SYS_RELAYED_TX) &&
		CHK_RelayedTxReport() ) {	  /** 不達通知送信がONで配信のチェックメッセージがプリントされた場合、 */
		h = RelayedTxDocumentStatus[SYS_DocumentPrintNo];/* 不達通知のコマンドNO */
		RelayedReportPrintStatus[SYS_DocumentPrintNo] |= PRINT_IS_OVER;	/* 竹内 Apr.10.1995 */
		if (SYB_CommandFile[h].Status == SYS_CMD_EXECUTE) {
			for (k = 0; k < SYS_EXEC_QUEUE_MAX; k++) {/** 実行終了の通信エラーチェック */
				if ((SYB_ExecQueue[k].Number.Command == (UBYTE)h) && /** ExecQueueのコマンド番号とコマンド・ファイルの番号が一致 */
					(SYB_ExecQueue[k].Status == SYS_EXEC_ERROR))  {	/* 通信エラー */
					break; /** 通信エラーがあった。 kはSYS_EXEC_QUEUE_MAXに達しない */
						   /** このパスを通らなければk==SYS_EXEC_QUEUE_MAXになる */
				}
			}
			if (k < SYS_EXEC_QUEUE_MAX) { /** 不達通知エラー終了 */
				if (CHK_RelayedReportPrint()) {		/** 不達通知プリントＯＮ */
					/** 不達通知の送信とプリント共に終了なら，コマンドファイルを消去する */
					if (RelayedReportPrintStatus[SYS_DocumentPrintNo] == (PRINT_IS_OVER | RELAYED_IS_OVER)) {
						/* 配信と不達通知のコマンドを消去 */
						CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)h);
						CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo);
					}
				}
				else {
					/* 配信と不達通知のコマンドを消去 */
					CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)h);
					CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo);
				}
			}
			else {		/** 不達通知ＯＫ終了 */
				if (CHK_RelayedReportPrint()) {		/** 不達通知プリントＯＮ */
					/** 不達通知の送信とプリント共に終了なら，コマンドファイルを消去する */
					if (RelayedReportPrintStatus[SYS_DocumentPrintNo] == (PRINT_IS_OVER | RELAYED_IS_OVER)) {
						/* 配信と不達通知のコマンドを消去 */
						CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)h);
						CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo);
					}
				}
			}
		}
	}
	else {
		CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)SYS_DocumentPrintNo); /** 通常コマンドのクリア */
	}
}
#endif

#if (PRO_PRINT_TYPE == THERMAL)
/*************************************************************************
	module		:[リアルタイムコピープリントタスクからのメッセージ処理]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1998/10/08]
	author		:[T.Soneoka]
*************************************************************************/
void	MAN_FromPRN_RealTimeCopyTask(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	UWORD	prt_item;
	UWORD	prt_message;
	UWORD	prt_sub_message1;
	UWORD	prt_sub_message2;

	prt_item = item;
	prt_message = message;
	prt_sub_message1 = sub_message1;
	prt_sub_message2 = sub_message2;


	switch (prt_message) {
	case MSG_PRN_REALTIMECOPY_END:
		if (!((SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_FEED_ERROR)
		||    (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN))) {
#if (PRO_PANEL == ANK)
			if (tskno_print_complete == 0xffff) {
				cre_tsk(&tskno_print_complete, TSK_CMN_MAN_TIMER10MSTASK, &PrintCompleteMessage);
			}
#endif
		}
#if defined(STOCKHM2)/* Added by SMuratec C.P 2004/07/05 for scanner copy display */
		CMN_ResetPrimaryMode();
		CMN_ResetPrimaryContrast();
#endif
		/* No Break */
	case MSG_PRN_REALTIMECOPY_ERROR:
		if (tskno_PRN_ImagePrintTask != 0xffff) {
			del_tsk(&tskno_PRN_ImagePrintTask); /** メモリ・プリント・タスク停止 */
		}
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRINTER_BUSY; /** プリンタ使用中をクリア */
		SYS_MachineStatus[SYS_MACHINE_STATUS]  &= ~SYS_SCANNER_COPY;
#if defined(STOCKHM2)/* Added by SMuratec C.P 2004/07/05 for scanner copy display */
		CMN_ResetPrimaryMode();
		CMN_ResetPrimaryContrast();
#endif
		break;

	case MSG_PRN_REALTIMECOPY_CONTI:
	default:
		break;
	}
}
#endif
