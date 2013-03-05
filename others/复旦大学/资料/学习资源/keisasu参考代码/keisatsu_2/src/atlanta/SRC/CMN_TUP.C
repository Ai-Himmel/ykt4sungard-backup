/************************************************************************
*	System		: POPLAR/ANZU-L
*	File Name	: CMN_TUP.C
*	Author		: 橘正樹
*	Date		: 1996/11/02
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニタ
*	Description	:
*	Maintenance	:
*				: Original:\src\kobe\anzu\src\cmn_tup.c
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\timer10.h"
#include "\src\atlanta\define\evttomsg.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\ext_v\cmn_data.h"	/* For 10ms timer T.Nose 1996/11/19 */

/* １０ｍｓ割込みの処理移動 T.Nose 1998/01/27 */
#include "\src\atlanta\define\scn_io.h"
#if (PRO_SEPERATE_24V == DISABLE)
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\ext_v\man_data.h"
#endif
#if (PRO_FBS == ENABLE)
#include "\src\atlanta\define\mntsw_c.h"
#endif
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\lst_data.h"
#if (PRO_PRINT_TYPE == LASER)
#include "\src\atlanta\prt\sp322\ext_v\prn_data.h"
#endif
#include "\src\atlanta\ext_v\bkupram.h"

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#endif
#if (PRO_MODEM == R288F)
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#endif
#if (PRO_MODEM == ORANGE3)
#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif

void EventCheck(void);
void CMN_MultiTimerIntervalJob(void);
#if (PRO_SEPERATE_24V == DISABLE)
UBYTE RXIL(void);
#endif

#include "\src\atlanta\sh7043\define\def_mon.h"


/*************************************************************************
	module		:[標準10msタイマータスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[
		1.timer10ms_ptr->Time = ウエイトするタイマー値
		2.timer10ms_ptr->SendMBX = タイムアップ後に送信するメイルボックス
		3.timer10ms_ptr->ReturnValue = タイムアップ後に送信するデータ
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/18]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_WatchTimer10msTask(struct Timer10msData_t *timer10ms_ptr)
{
	WORD	return_mbxno;
	WORD	return_msg;

	return_mbxno = timer10ms_ptr->SendMBX;
	return_msg = timer10ms_ptr->ReturnValue;
	wai_tsk(timer10ms_ptr->Time);
	snd_msg(return_mbxno, &return_msg);
	wai_tsk(0xFFFF);
}

/*************************************************************************
	module		:[標準10msタイマーイベント発生タスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[
		1.timer10ms_ptr->Time = ウエイトするタイマー値
		3.timer10ms_ptr->Event = タイムアップ後に発生するイベント
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/13]
	author		:[奥村明]
*************************************************************************/
void	CMN_WatchTimer10msEventTask(struct Timer10msEventData_t *timer10ms_ptr)
{
	/*
	** HINOKIにて、下記 det_evt() でリセットがかかりました
	** しかし根本原因がわからないため、リセットするのを回避します
	** 回避策
	** ・引数を待避する
	** ・ウェイトが０のとき、無限ウェイトする
	** ・イベント番号がＭａｘ以上の値できた場合、無限ウェイトする
	** 1999/03/04 by T.Soneoka
	*/
    UWORD Time;
    WORD  Event;

	Time = timer10ms_ptr->Time;
	Event = timer10ms_ptr->Event;
	
	if ((Time == 0)
	||  (Event >= EVENT_MAX)) {
		wai_tsk(0xffff);
	}

#if (0)
**	wai_tsk(timer10ms_ptr->Time);
**	det_evt(timer10ms_ptr->Event);
#else
	wai_tsk(Time);
	det_evt(Event);
#endif
	wai_tsk(0xFFFF);
}

/*************************************************************************
	module		:[メインタスクと同期をとるための10msタイマータスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[
		1.timer10ms_ptr->Time = ウエイトするタイマー値
		2.timer10ms_ptr->SendMBX = タイムアップ後に送信するメイルボックス
		3.timer10ms_ptr->ReturnValue = タイムアップ後に送信するデータ
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/02]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_MAN_Timer10msTask(struct Timer10msData_t *timer10ms_ptr)
{
	UWORD	return_mbxno;
	MESSAGE_t	return_msg;

	return_mbxno = timer10ms_ptr->SendMBX;
	return_msg.Item = FROM_10MS_TIMER;
	return_msg.Message = timer10ms_ptr->ReturnValue;
	wai_tsk(timer10ms_ptr->Time);
	snd_msg(return_mbxno, &return_msg);
	wai_tsk(0xFFFF);
}

/*************************************************************************
	module		:[イベントをメッセージに変換するタスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[
		1.timer10ms_ptr->DetEventNo = 検出するイベント番号
		2.timer10ms_ptr->SendMBX = タイムアップ後に送信するメイルボックス
		3.timer10ms_ptr->ReturnValue = タイムアップ後に送信するデータ
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/28]
	author		:[吉川弘康]
*************************************************************************/
void	CMN_EventToMessageTask(struct EventToMessageData_t *data_ptr)
{
	UWORD	event_no;
	UWORD	return_mbxno;
	MESSAGE_t	return_msg;

	return_mbxno = data_ptr->SendMBX;
	event_no = data_ptr->DetEventNo;
/*	return_msg.Item = FROM_EVENT_TO_MESSAGE;	*/
	return_msg.Message = data_ptr->ReturnValue;

	while (1) {
		wai_evt(event_no);
		snd_msg(return_mbxno, &return_msg);
	}
}


/*************************************************************************
	module		:[タイムアップメッセージを送るタスク]
	function	:[
		1.タイマーキューのタイマー値を減算する
		2.減算した結果タイマー値が0であれば指定のメールボックスへ
		  メッセージを送信する
	]
	return		:[]
	common		:[]
	condition	:[
		man_task() の初期化部でクリエイトされる常駐タスク
		クリエイトする前にTimer10msQueue[TIMER_MULTI10MS_MAX]を
		初期化する事
		CMN_MultiTimer10msStart() をコールしている全てのタスクより
		優先順位を高くすること（でないとタイマーが止まってしまう）
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/11/19]
	author		:[野瀬敏弘]
*************************************************************************/
void	CMN_MultiTimer10msTask(void)
{
	UBYTE queue_number;
	UBYTE loop_flag;
	struct Timer10msQueueData_t *Queue_ptr;
	struct Timer10msQueueData_t *SaveQueue_ptr;

	for (queue_number = 0; queue_number < TIMER_MULTI10MS_MAX; queue_number++) {
		CMN_ReturnMessage[queue_number].Item = FROM_MULTI_TIMER;
	}

	while(1) {
		wai_tsk(1);

		/* １０ｍｓ間隔で必要な処理を行う T.Nose 1998/01/27 */
		CMN_MultiTimerIntervalJob();

		if (CMN_TopTimerQueue == 0xFF) {
			continue;
		}
		CMN_DisableInterrupt();
		queue_number = CMN_TopTimerQueue;
		loop_flag = TRUE;
		while (loop_flag == TRUE) {
			Queue_ptr = &Timer10msQueue[queue_number];
			if ((Queue_ptr->Time != 0xFFFF) && (Queue_ptr->Time != 0)) {
				Queue_ptr->Time--;
			}
			if (Queue_ptr->Time == 0) {
				if (chk_rcv(Queue_ptr->SendMBX)) {
					/* リンクのつなぎ替え */
					if (queue_number == CMN_TopTimerQueue) { /* キューのトップならば */
						CMN_TopTimerQueue = Queue_ptr->Link;
					}
					else {
						SaveQueue_ptr->Link = Queue_ptr->Link;
					}

					/* 送信するメッセージデータのセット及び送信 */
					CMN_ReturnMessage[queue_number].Message = Queue_ptr->ReturnValue;
					Queue_ptr->Time = 0xFFFF;
					*Queue_ptr->TimerID = 0xFF;
					snd_msg(Queue_ptr->SendMBX,&CMN_ReturnMessage[queue_number]);
					CMN_DisableInterrupt();
				}
			}
			if (Queue_ptr->Link == 0xFF) { /* リンクの終端ならば */
				loop_flag = FALSE; /* ループをぬけて１０ｍＳの待ちに入る */
			}
			else {
				queue_number = Queue_ptr->Link;
				/* Queue_ptr が指しているタイマーキューが、メッセージ送信・キュー消去
				** されていなければ SaveQueue_ptr を更新する
				*/
				if (Queue_ptr->Time != 0xFFFF) {
					SaveQueue_ptr = Queue_ptr;
				}
			}
		}
		CMN_EnableInterrupt();
	}
#if (0)
	/* 下のようにキューの先頭から単純にタイムアップを検索するだけでは
	** 一つのタスクから複数のタイマーが起動された時に、大きい方のタイマーの
	** メッセージが永久に送信できなる事がある。T.Nose
	*/
	while (1) {
		wai_tsk(1);
		for (queue_number = 0; queue_number < TIMER_MULTI10MS_MAX; queue_number++) {
			Queue_ptr = &Timer10msQueue[queue_number];
			CMN_DisableInterrupt();
			if ((Queue_ptr->Time != 0xFFFF) && (Queue_ptr->Time != 0)) {
				Queue_ptr->Time--;
			}
			if (Queue_ptr->Time == 0) {
				if (chk_rcv(Queue_ptr->SendMBX)) {
					return_msg.Message = Queue_ptr->ReturnValue;
					Queue_ptr->Time = 0xFFFF;
					*Queue_ptr->TimerID = 0xFF;
					/* ＦＣＯＤＥ送信でリセットがかかる件 */
					DEBUG_SaveAddressBuffer[queue_number] = 0xFFFFFFFF;
					snd_msg(Queue_ptr->SendMBX,&return_msg);
				}
			}
			CMN_EnableInterrupt();
		}
	}
#endif
}

/*************************************************************************
	module		:[タイマーキューにタイマーを登録する]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		タイマーキューに空きがない場合リセットへ飛びます
		1997/10/06 タイマーキューのリンクを作るようにした T.Nose
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/11/19]
	author		:[野瀬敏弘]
*************************************************************************/
void	CMN_MultiTimer10msStart(UBYTE *timer_id, struct Timer10msData_t *timer10ms_ptr)
{
	UBYTE queue_number;
	UBYTE next_queue;
	UWORD int_status;

	int_status = CheckInterruptEnable();
	CMN_DisableInterrupt();
	for (queue_number = 0; queue_number < TIMER_MULTI10MS_MAX; queue_number++) {
		if (Timer10msQueue[queue_number].Time == 0xFFFF) {
			*timer_id = queue_number;
			Timer10msQueue[queue_number].Time = timer10ms_ptr->Time;
			Timer10msQueue[queue_number].SendMBX = timer10ms_ptr->SendMBX;
			Timer10msQueue[queue_number].ReturnValue = timer10ms_ptr->ReturnValue;
			Timer10msQueue[queue_number].TimerID = timer_id;

			/* キューのリンクにつなぐ
			** 後から起動されたタイマーはリンクの後ろにつなぐ
			*/
			Timer10msQueue[queue_number].Link = 0xFF; /* リンクの最後とする */
			if (CMN_TopTimerQueue == 0xFF) {
				CMN_TopTimerQueue = queue_number;
			}
			else {
				next_queue = CMN_TopTimerQueue;
				while (Timer10msQueue[next_queue].Link != 0xFF) {
					next_queue = Timer10msQueue[next_queue].Link;
				}
				Timer10msQueue[next_queue].Link = queue_number;
			}

			if (int_status) {
				CMN_EnableInterrupt();
			}
			return;
		}
	}
	SaveReturnAddressAndJumpBegin();	/* タイマーの数が最大数をオーバーしたら */
}

/*************************************************************************
	module		:[タイマーキューからタイマーを削除する]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/11/19]
	author		:[野瀬敏弘]
*************************************************************************/
void	CMN_MultiTimer10msStop(UBYTE *timer_id)
{
	UWORD int_status;
	UBYTE queue_number;

	if (*timer_id >= TIMER_MULTI10MS_MAX) {
		SaveReturnAddressAndJumpBegin();
	}

	int_status = CheckInterruptEnable();
	CMN_DisableInterrupt();
	if (*timer_id == CMN_TopTimerQueue) { /* リンクの先頭ならば */
		CMN_TopTimerQueue = Timer10msQueue[*timer_id].Link;
	}
	else {
		queue_number = CMN_TopTimerQueue;
		while (Timer10msQueue[queue_number].Link != *timer_id) {
			queue_number = Timer10msQueue[queue_number].Link;
		}
		Timer10msQueue[queue_number].Link = Timer10msQueue[*timer_id].Link;
	}
	Timer10msQueue[*timer_id].Time = 0xFFFF;
	*timer_id = 0xFF;
	if (int_status) {
		CMN_EnableInterrupt();
	}
#if (0)
	if (*timer_id < TIMER_MULTI10MS_MAX) {
		Timer10msQueue[*timer_id].Time = 0xFFFF;
		/* ＦＣＯＤＥ送信でリセットがかかる件 */
		DEBUG_SaveAddressBuffer[*timer_id] = 0xFFFFFFFF;
		*timer_id = 0xFF;
		if (int_status) {
			CMN_EnableInterrupt();
		}
		return;
	}
	SaveReturnAddressAndJumpBegin();
#endif
}


/******************************************************************************
	module		:[１０ｍｓ間隔で必要な処理を行う]
	function	:[
				1.
	]
	return		:[なし]
	common		:[なし]
	comment		:[
		１０ｍｓ割込みの処理時間軽減のため、割り込みに登録してあった処理のなかで
		厳密に１０ｍｓ間隔でなくても構わないものをマルチタイマーで処理します
	]
	machine		:[SH(SH7034/SH704X)]
	language	:[SHC(V.3.0C)]
	keyword		:[INT]
	date		:[1998/01/27]
	author		:[野瀬]
******************************************************************************/
void CMN_MultiTimerIntervalJob(void)
{
;/*************************************************************
; * ＱＡＴ中に通信記録の通信時間が実際の時間と異なる不具合対策用
; * 原因：通信記録の開始時刻が正常に印字されているため、通信終了
; *       時に読み込んだＲＴＣのデータが化けていた可能性がある。
; *       ＲＴＣが化ける可能性としては、リード中にＣＥがローレベル
; *       になる等があるが、実際の原因は不明。
; * 対策：通信時間の算出用に次のデータを追加
; *       UWORD SYS_1SecBaseCounter（０～１００）
; *       UWORD SYS_1SecGeneralTimer（０～６５５３５）
; *		 UWORD SYS_FCM_StartTime
; * 1996/09/02 S.Kawasaki
; *************************************************************/
	CMN_DisableInterrupt();
	SYS_1SecBaseCounter++;
	if (SYS_1SecBaseCounter == 100) { /* １秒経過したか？ */
		SYS_1SecBaseCounter = 0;	/* １秒計測用カウンターをリセット */
		SYS_1SecGeneralTimer++;		/* １秒単位のタイマー加算 */
	}
	CMN_EnableInterrupt();

/*--------------------------------------------------------------------------------------*/
/*	 モーターを停止時にはモーター・パルスだけを止め、励磁はかかったままになるのでここで */
/*	 励磁をきります。T.Nose 1996/08/06													*/
/*--------------------------------------------------------------------------------------*/
	CMN_DisableInterrupt();
	if (SCN_MotorCurrentStopCounter != 0) { /** モーターの励磁停止を遅らせるカウンター */
		SCN_MotorCurrentStopCounter--;
		if (SCN_MotorCurrentStopCounter == 0) {
			SCN_MTP1_Status &= ~(IO_BIT_CURRENT_POWER_D5 + IO_BIT_CURRENT_POWER_D6); /** 電流ビットをクリア（０％） */
			outp(MTP1_PORT, SCN_MTP1_Status);
		}
	}
	CMN_EnableInterrupt();

/*------------------------------------------------------------------ */
/*	ＥＣＭ受信中ループ対策											*/
/*	MDM_RxPix()でMDM_RXECMCONTROLTASKをクリエイトし、その後のsnd_msgでのループをなくす */
/*	snd_msgする前にMDM_ResetCounterを500（５秒間）にセットします */
/*	snd_msg完了する間、この割り込み内で上記変数をデクリメントし、0になったときリセットします */
/*	96.2.13		by T.Soneoka	Add By T.Y	*/
/*------------------------------------------------------------------ */
	CMN_DisableInterrupt();
	if (MDM_ResetCounter) {
		MDM_ResetCounter--;
		if (MDM_ResetCounter == 0) {
			if (FaxComPerformingFlag == 1) {	/* 条件追加 1997/06/10  By T.Yamaguchi */
				SaveReturnAddressAndJumpBegin();
			}
		}
	}
	CMN_EnableInterrupt();

	/*---------------------------------------------------------------
	** リストプリント時に１ブロックのＤＭＡ転送が終了しない場合はＪＡＭ発生とする
	** By M.Tachibana 1997/09/09
	*/
	CMN_DisableInterrupt();
	if (LST_JAM_DetectCounter) {
		LST_JAM_DetectCounter--;
		if (LST_JAM_DetectCounter == 0) {
#if (PRO_PRINT_TYPE == LASER)
			det_evt(EVT_PAPER_JAM);
#endif
#if (PRO_PRINT_TYPE == LED)
			det_evt(EVT_PRN_PRINTER_ERROR);
#endif
		}
	}
	CMN_EnableInterrupt();



#if (PRO_PRINT_TYPE == LASER)
	/*
	**;	プリンタ･シリアル時の/SBSY発生しないときの保険処理追加
	**;	S.Kawasaki 1996/04/11
	*/
	CMN_DisableInterrupt();
	if (PRN_SerialTimeCounter != 0) { /** プリンタ･シリアル通信でコマンド発行後にカウント値をセットします */
		if (--PRN_SerialTimeCounter == 0) {
			PRN_SBSYINTErrorFlag = 1; /** 指定時間タイムアップ時のエラーフラグセット */
			det_evt(EVT_PRN_XSBSY); /** イベント発行 */
			outp(PRN_IO_PCINTR_ADDRESS,PRN_PCINTR_CXSBSY); /** 割込みステータス解除 */
		}
	}
	CMN_EnableInterrupt();
#endif

	EventCheck(); /** By S.Kawasaki 1996/04/11 */

	SCN_GearBacklashTimeOutCheck(); /* ｷﾞｱﾊﾞｯｸﾗｯｼｭﾀｽｸﾀｲﾑｱｳﾄ処理 T.Nose 1997/08/12 */

#if (PRO_SEPERATE_24V == DISABLE)
	CMN_DisableInterrupt();
	/* プリンタカバー開をスキャナー関連タスクに通知 T.Nose 1997/08/25 */
#if (0)
//	if (tskno_SCN_WatchPrinterCoverTask != 0xFFFF) { /* プリンタカバー監視タスク */
//		if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
//			det_evt(EVT_SCN_TOP_COVER_OPEN);
//		}
//	}
//
//	if ((tskno_SCN_DocumentStoreTask != 0xFFFF)		/* 原稿蓄積タスク */
//	 || (tskno_SCN_MirrorMoveTask != 0xFFFF)) {		/* ミラーキャリッジ移動タスク */
//		if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
//			det_evt(EVT_MIRROR_MOVE_END);
//		}
//	}
#endif
	if (tskno_SCN_WatchPrinterCoverTask != 0xFFFF) { /* プリンタカバー監視タスク */
#if (PRO_FBS == ENABLE)
		if ((SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN)
		 || RXIL()) {
			SCN_MirrorMoveStatus = MIRROR_MOVE_RXIL_ABORT;
			det_evt(EVT_SCN_TOP_COVER_OPEN);
		}
#else
		if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
			det_evt(EVT_SCN_TOP_COVER_OPEN);
		}
#endif
	}

#if (PRO_FBS == ENABLE)
	if ((tskno_SCN_DocumentStoreTask != 0xFFFF)		/* 原稿蓄積タスク */
	 || (tskno_SCN_MirrorMoveTask != 0xFFFF)) {		/* ミラーキャリッジ移動タスク */
		if ((SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN)
		 || RXIL()) {
			SCN_MirrorMoveStatus = MIRROR_MOVE_RXIL_ABORT;
			det_evt(EVT_MIRROR_MOVE_END);
		}
	}
#else
	if (tskno_SCN_DocumentStoreTask != 0xFFFF) {	/* 原稿蓄積タスク */
		if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
			det_evt(EVT_MIRROR_MOVE_END);
		}
	}
#endif
	CMN_EnableInterrupt();
#endif

#if (PRO_FBS == ENABLE)
	/* ＡＤＦに原稿をセットした時、ＡＤＦ側でミラーが止まらなくなる件 T.Nose 1997/12/17 */
	if (SYB_MaintenanceSwitch[MNT_SW_C0] & MIRROR_MOVE_FORCE_END) {
		SCN_WatchMotorInterrupt();
	}
#endif

}

/******************************************************************************
	module		:[イベントチェック]
	function	:[
				1.
	]
	return		:[なし]
	common		:[なし]
	comment		:[]
	machine		:[SH(SH7034/SH704X)]
	language	:[SHC(V.3.0C)]
	keyword		:[INT]
	date		:[1996/4/11]
	author		:[川崎真史]
******************************************************************************/
void EventCheck( void )
{
#if (PRO_PRINT_TYPE == LASER)
	UBYTE status;

	CMN_DisableInterrupt();
	status = inp((UDWORD)PRN_IO_PSINTR_ADDRESS); /** ﾌﾟﾘﾝﾀLSI 割込みﾁｪｯｸ */

	if (status & PRN_PSINTR_XPPRDY) { /** PPRDY */
		det_evt(EVT_PRN_XPPRDY_OFF);
	}
	else {
		det_evt(EVT_PRN_XPPRDY_ON);
	}

	if (status & PRN_PSINTR_XRDY) { /** RDY */
		det_evt(EVT_PRN_XRDY_OFF);
	}
	else {
		det_evt(EVT_PRN_XRDY_OFF);
	}
	CMN_EnableInterrupt();
#endif
}
