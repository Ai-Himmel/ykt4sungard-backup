/*
 *	@(#)%W%
 *	FileName:	/home2/prj/Eva/Src/scn/scndocin.c
 *	Create:	Wed Dec 24 15:42:30 1997	by	ishiyama
 *	Description:
 *		Document In Task
 *	Change Log:
 *		\prj\eva\src\scn\scndocin.cからコピーして、HINOKI用に変更した  1998/09/28 by T.Soneoka
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\scn_tbl.h"
#include "\src\cpu\sh7043_a\irom\define\def_evtn.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"

static	MESSAGE_t		DocInTaskMessage;
static	MESSAGE_t		DocOutTaskMessage;

/*
 *	Name:	Scanner Document In Task
 *	Create:	Wed Dec 24 16:28:57 1997	by	ishiyama
 *	Synopsis:
 *		#include	"scn_task.h"
 *		void	DocInTask(void);
 *	Description:
 *		原稿繰り込みタスク
 *		原稿を DS2 が ON するまで繰り込む
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	DocInTask(void)
{
	/* 原稿排出中に原稿入力の要求がきたら、排出完了まで待つようにします  1999/02/12 by T.Soneoka */
	while (1) {
		if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT) {
			wai_tsk(10);
		} else {
			break;
		}
	}

	/* すでに原稿セット済みの場合 */
	/* 原稿イニシャルの保険をいれます
	** ScanPage[].ObjectがすでにTRUE状態でこのタスクがクリエイトされた場合、
	** ScanPage[0].ObjectもScanPage[1].Objectも
	** 両方ともTRUEにしてしまうことを避ける為
	** by T.Soneoka 1999/1/11 by T.Soneoka
	*/
	InzDocObj();
		
	if (!QueryCloseInterLock4Scan()) {
		/* スキャナカバーが開いてる */
		DocInTaskMessage.Message = MSG_DOCUMENT_IN_ERROR;
		DeleteDocObj(&CurrentPage);
	} else if (!QueryDs1On()) {
		/* 原稿がない */
		DocInTaskMessage.Message = MSG_DOCUMENT_IN_NOTHING;
		DeleteDocObj(&CurrentPage);
	} else if (QueryDs2On()) {
		CurrentPage = CreateDocObj();
		CurrentPage->StepsFromDs1On = Ds1ToDs2Steps+Ds2ToReadySteps;
		CurrentPage->StepsFromDs2On = Ds2ToReadySteps;
		CurrentPage->Position = DOC_POS_MOVE_TO_SCAN;
		DocInTaskMessage.Message = MSG_DOCUMENT_IN_SETUP;
	} else {
		ScannerMode = SCANNER_DOC_IN_MODE;
		CurrentPage = CreateDocObj();

		ClearMessageBody(&DocInTaskMessage); /* Clear Static Message Area */

		/* DS1 のみ ON なら原稿を繰り込む */

		/* 原稿繰り込み開始 */
		SetupTxMotor(FEEDER_DOC_IN);
#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */
		PC_24V_On();
#endif
		CluchOn();
		StartTxMotor();

		/* 割り込みからのイベント待ち */
		wai_evt(EVT_SCN_DOC);

		if (ScannerEventStatus & SCN_EVT_DOCIN_NO_DOC) {
			/* 原稿引き抜き検出 */
			DocInTaskMessage.Message = MSG_DOCUMENT_IN_NOTHING;
			DeleteDocObj(&CurrentPage);
		} else if (ScannerEventStatus & SCN_EVT_DOCIN_FEED_ERROR) {
			/* 原稿繰り込み不良検出 */
			DocInTaskMessage.Message = MSG_DOCUMENT_IN_ERROR;
			DeleteDocObj(&CurrentPage);
		} else if (ScannerEventStatus & SCN_EVT_DOCIN_COVER_OPEN) {
			/* スキャナカバーオープン検出 */
			DocInTaskMessage.Message = MSG_DOCUMENT_IN_ERROR;
			DeleteDocObj(&CurrentPage);
		} else if (ScannerEventStatus & SCN_EVT_DOCIN_SET_OK) {
			/* 原稿セット正常終了 */
			DocInTaskMessage.Message = MSG_DOCUMENT_IN_SETUP;
		} else {
			/* not reached */
			DocInTaskMessage.Message = MSG_DOCUMENT_IN_ERROR;
		}

		/*
		** 励磁しっぱなし不具合 2000/04/11 by T.Soneoka
		*/
		StopTxMotor();
	}

	DocInTaskMessage.Item = FROM_DOCUMENT_IN;
	snd_msg(mbxno.MAN_Task, &DocInTaskMessage);
	rcv_msg(mbxno.SCN_Task, &SCN_Msg);
	wai_tsk(0xffff);
}

/*
 *	Name:	Exit Document In Task
 *	Create:	Wed Feb 25 15:59:20 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_task.h"
 *		void	ExitDocInTask(void);
 *	Description:
 *		原稿繰込みタスク終了関数
 *		リソースの開放を目的とする
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ExitDocInTask(void)
{
	ScannerMode = SCANNER_NEUTRAL_MODE;
	exi_tsk();
}


/*
 *	Name:	Document Out Task
 *	Create:	Tue Jan 13 11:23:33 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_task.h"
 *		void	DocOutTask(void);
 *	Description:
 *		原稿排出タスク
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
/*
** スキャンクローズで原稿排出中は回線引きっぱなしになる不具合
** 1999/02/01 by T.Soneoka
*/
#if (0)
** void	DocOutTask(void)
#else
void	DocOutTask(UBYTE *type)
#endif
{
	/* アドレス引き渡しの後で上位の関数が消えるので上位タスクでそのアドレスが使用されます。
	   よってローカルに内容をコピーします。O.Oshima 2003/11/07 */
	UBYTE docout_type;
	docout_type = *type;

	ScannerMode = SCANNER_DOC_OUT_MODE;

	ClearMessageBody(&DocOutTaskMessage); /* Clear Static Message Area */

	/* 原稿排出開始 */
#if (0) /* 1998/12/21 by T.Soneoka */
**	CluchOn();
#else
	/* クラッチカウンタが残っている場合のみクラッチＯｎします */
	if (CurrentPage->StepsFromDs2On < CluchOffCounter) {
 #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/12/3 T.Takagi */
		PC_24V_On();
 #endif
		CluchOn();
	}
#endif
	SetupTxMotor(FEEDER_DOC_OUT);
	StartTxMotor();

/*
** スキャンクローズで原稿排出中は回線引きっぱなしになる不具合
** 1999/02/01 by T.Soneoka
*/
#if (0)
**	/* 割り込みからのイベント待ち */
**	wai_evt(EVT_SCN_DOC);
**
**	/* Event の解析 */
**	if (ScannerEventStatus & SCN_EVT_DOCOUT_FEED_ERROR) {
**		/* 原稿繰り込み不良検出 */
**		DocOutTaskMessage.Message = MSG_DOCOUT_FEED_ERROR;
**	} else if (ScannerEventStatus & SCN_EVT_DOCOUT_COVER_OPEN) {
**		/* スキャナカバーオープン検出 */
**		DocOutTaskMessage.Message = MSG_DOCOUT_COVER_OPEN;
**	} else if (ScannerEventStatus & SCN_EVT_DOCOUT_EXIT_OK) {
**		/* 原稿排出正常終了 */
**		DocOutTaskMessage.Message = MSG_DOCOUT_EXIT;
**	} else {
**		/* not reached */
**		DocOutTaskMessage.Message = MSG_DOCOUT_COVER_OPEN;
**	}
**	
**	/* Scanner Page Object 削除 */
**	DeleteDocObj(&CurrentPage);
**	DeleteDocObj(&NextPage);
**
**	DocOutTaskMessage.Item = FROM_DOCUMENT_OUT;
**	snd_msg(mbxno.SCN_Task, &DocOutTaskMessage);
**	wai_tsk(0xffff);
#else
	/* 割り込みからのイベント待ち */
	wai_evt(EVT_SCN_DOC);

	/* Event の解析 */
	if (ScannerEventStatus & SCN_EVT_DOCOUT_FEED_ERROR) {
		/* 原稿繰り込み不良検出 */
		DocOutTaskMessage.Message = MSG_DOCOUT_FEED_ERROR;
	} else if (ScannerEventStatus & SCN_EVT_DOCOUT_COVER_OPEN) {
		/* スキャナカバーオープン検出 */
		DocOutTaskMessage.Message = MSG_DOCOUT_COVER_OPEN;
	} else if (ScannerEventStatus & SCN_EVT_DOCOUT_EXIT_OK) {
		/* 原稿排出正常終了 */
		DocOutTaskMessage.Message = MSG_DOCOUT_EXIT;
	} else {
		/* not reached */
		DocOutTaskMessage.Message = MSG_DOCOUT_COVER_OPEN;
	}
	
	/* Scanner Page Object 削除 */
	DeleteDocObj(&CurrentPage);
	DeleteDocObj(&NextPage);

	/*
	** 原稿蓄積中にカバーオープンをすると、ＴＸモータがまわりっぱなしになる
	** 念のため、モータストップをコールします
	** 1999/02/26 by T.Soneoka
	*/
	StopTxMotor();

/* アドレス引き渡しの後で上位の関数が消えるので上位タスクでそのアドレスが使用されます。
   よってローカルに内容をコピーします。O.Oshima 2003/11/07 */
#if (0)
** 	if (*type == FEED_CHECK) [
#else
	if (docout_type == FEED_CHECK) {
#endif
		DocOutTaskMessage.Item = FROM_DOCUMENT_OUT;
		snd_msg(mbxno.SCN_Task, &DocOutTaskMessage);
/* 
** ＤＳ２に噛んだ状態でのストップキー連打でループ
** ここでSYS_FEED_OUTを落とした場合、このタイミングでストップキーが押下されると
** 原稿排出タスクがデリートされる前に、クリエイトされてしまう
** 親タスクでSYS_FEED_OUTを落すように修正
** 1999/03/09 by T.Soneoka
*/
#if (0)
**		/* 排出中を落とします  1999/02/12 by T.Soneoka */
**		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FEED_OUT;
#endif

		wai_tsk(0xffff);

	} else {	/* *close_type == FROM_FCOM */
		/* 原稿排出途中で止まる不具合 1999/2/1 by T.Soneoka */
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FEED_OUT;
		/* ＦＣＭから起動されているときは自滅します */
		exi_tsk();

	}
#endif
}

/*
 *	Name:	Exit Document Out Task
 *	Create:	Wed Feb 25 15:59:20 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_task.h"
 *		void	ExitDocOutTask(void);
 *	Description:
 *		原稿排出タスク終了関数
 *		リソースの開放を目的とする
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ExitDocOutTask(void)
{
	ScannerMode = SCANNER_NEUTRAL_MODE;
	exi_tsk();
}
