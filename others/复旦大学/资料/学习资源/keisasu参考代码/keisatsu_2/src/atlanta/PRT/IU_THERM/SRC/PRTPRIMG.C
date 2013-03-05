/*
 *	@(#)$Id: PRTPRIMG.C,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	/home2/prj/Eva/Src/prt/prtprimg.c
 *	Create:	Mon Apr  6 15:00:13 1998	by	ishiyama
 *	Description:
 *		Print Image Task
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\sysprint.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\ext_v\sys_data.h"
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\define\sysshad.h"
#include "\src\atlanta\satsuki2\ext_v\scn_dath.h"
 #else
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
 #endif
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"
#include "\src\cpu\sh7043_a\irom\define\def_evtn.h"

static BOOL	StartPagePrintProcedure(void);
#if (0)
**static void	StopPagePrintProcedure(void);
**static BOOL	QueryNoPaper(void);
#endif

/*
 *	Name:	Print Image Task
 *	Create:	Mon Apr  6 15:01:08 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_task.h"
 *		void	PrintImageTask(void);
 *	Description:
 *		Print Queue を読んで、イメージをプリントするタスク(常駐タスク)
 *	Notes:
 *		TxMessages:
 *			MSGL_PAGE_END			// プリント正常終了
 *			MSGL_PRINTER_ERROR		// プリントエラー終了
 *			MSGL_PRINTER_STOP		// STOPSW でプリント終了
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	PrintImageTask(void)
{
	MESSAGE_t	*RxMsg;
	MESSAGE_t	TxMsg;
	BOOL	Success;					/* ドライバ関数成功 or 失敗 失敗したらメッセージを送る */

	tskno_PRN_PrintDataTransTask = 0xffff;
	tskno_PRN_PrintImageEvent = 0xffff;

	/* 排出終了監視のため、パラメータを初期化した StartPagePrintのあとに起動 */
	if (tskno_PRN_PrintImageEvent == 0xffff) {
		cre_tsk(&tskno_PRN_PrintImageEvent, TSK_PRN_PRINTIMAGEEVENTTASK, &mbxno.PRN_PrintImageTask);
	}

	TxMsg.Item = FROM_PRINTIMAGE_TASK;

	for (;;) {
		Success = TRUE;
		rcv_msg(mbxno.PRN_PrintImageTask, &RxMsg);

		switch (RxMsg->Message) {
		case MSGL_PREPARE_MAKEIMAGE:	/* 記録紙引き戻し */

			PaperMoveCount = PrintReadySteps;	/* 10mm *//* EndMark By O.Kimoto 1999/02/09 */

			ChangeRxMotorPhase();
			EnableIntPrinterTimer();
			Paper.Phase = PAPER_PHASE_PRINT;
			break;

		case MSGL_START_MAKEIMAGE:		/* 印字開始 */
			/* Print Page Object 作成  */
			if (Success) {
				Success = OpenPrinter();
			}
#if (0)	/* 1998/12/15 by T.Soneoka */
**			if (Success) {
**				while (!(EnableToReadPrtImageBuf())) {	/* プリントイメージが揃うまでの待ち合わせ */
**					if (IsPrintFinish) {
**						Success = FALSE;
**					}
**					wai_tsk(1);
**				}
**			}
#endif
			if (Success) {
				SetDefaultPageQElements4Image();
				SetPaperAttribute();
				Success = StartPagePrintProcedure();
			}
			if (Success) {
				EnablePrintDataMake = TRUE; /* プリントデータ作成開始許可 1998/12/15 by T.Soneoka */
			}
			break;

		case MSGL_PRINT_CLOSE:		/* 記録紙待機位置へ移動、終了処理 */

			if (Paper.Position == PAPER_POS_PRINTING) {
				/* 記録紙が記録位置および記録位置移動中の場合は、印字位置からの記録紙排出（－＞待機位置まで）動かします */
				Paper.Phase = PAPER_PHASE_FEED;
				Paper.Route = ROUTE_PRINTING_TO_READY;
				Paper.Position = PAPER_POS_PRINTING_TO_FEED_OUT;
				ChangeRxMotorPhase();
			} else {
				SetPrinterCloseRequest();
			}
			break;
			
		case MSGL_READY_POS_COMP:	/* プリント１ＪＯＢ終了 */
			if (PrinterError) {
				Success = FALSE;
			} else {
				TxMsg.Message = MSGL_PAGE_END;
				snd_msg(mbxno.PRN_PrinterTask, &TxMsg);
			}
			break;

		case MSGL_PRINTER_ERROR:	/* プリンタエラー */
			Success = FALSE;
			break;

		default:
			break;
		}

		if (!Success) {
			Success = TRUE;
			if (PrinterError & PRT_ERROR_NO_PAPER) {			/* 記録紙なしエラー */
				SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER;
				TxMsg.Message = MSGL_PRINTER_ERROR;
				snd_msg(mbxno.PRN_PrinterTask, &TxMsg);

			} else 	if (PrinterError & PRT_ERROR_JAM) {			/* 記録紙ＪＡＭエラー */
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM;
				TxMsg.Message = MSGL_PRINTER_ERROR;
				snd_msg(mbxno.PRN_PrinterTask, &TxMsg);

			} else if (PrinterError & PRT_ERROR_CUT_ERROR) {	/* カッタエラー */
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_CUTTER_ERROR;
				TxMsg.Message = MSGL_PRINTER_ERROR;
				snd_msg(mbxno.PRN_PrinterTask, &TxMsg);

			} else if (PrinterError & PRT_ERROR_COVER_OPEN) {	/* カバーオープンエラー */
				SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_PRINTER_OPEN;
				TxMsg.Message = MSGL_PRINTER_ERROR;
				snd_msg(mbxno.PRN_PrinterTask, &TxMsg);

			} else if (PrinterError & PRT_ERROR_HIGH_TEMP) {	/* 高温印可不可 */
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
				TxMsg.Message = MSGL_PRINTER_ERROR;
				snd_msg(mbxno.PRN_PrinterTask, &TxMsg);
			}
		}
	} /* for end */
}

/*
 *	Name:	Exit Print Image Task
 *	Create:	Mon Apr  6 15:06:35 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_task.h"
 *		void	ExitPrintImageTask(void);
 *	Description:
 *		Print Image Task 終了関数
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ExitPrintImageTask(void)
{
	if (tskno_PRN_PrintImageEvent != 0xffff) {
		del_tsk(&tskno_PRN_PrintImageEvent);
	}
	if (tskno_PRN_PrintDataTransTask != 0xffff) {
		del_tsk(&tskno_PRN_PrintDataTransTask);
	}
	exi_tsk();
}


/*
 *	Name:	Print Image Event Task
 *	Create:	Fri Apr 17 15:32:14 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_task.h"
 *		void	PrintImageEventTask(void);
 *	Description:
 *		割込みからのイベントをメッセージに変換し,
 *		PrintImageTask に送る
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	PrintImageEventTask(WORD *tx_mail_box_no)
{
	MESSAGE_t	TxMsg;

	TxMsg.Item = FROM_PRINT_IMAGE_EVENT_TASK;

	for (;;) {

		CMN_DisableInterrupt();
		if (!PrinterEventStatus) {
			wai_evt(EVT_PRT_IMAGE);
		}
		CMN_EnableInterrupt();

		if (PrinterEventStatus & PRT_EVT_ERROR) {
			PrinterEventStatus &= ~PRT_EVT_ERROR;
			TxMsg.Message = MSGL_PRINTER_ERROR;
			snd_msg(*tx_mail_box_no, &TxMsg);

		} else if (PrinterEventStatus & PRT_EVT_CUT_ON) {
			PrinterEventStatus &= ~PRT_EVT_CUT_ON;
#if (0) /* カッタ不良チェック追加 1999/04/13 by T.Soneoka */
**			ExecCutter();
#else
			if (ExecCutter() == NG) {
				PrinterError |= PRT_ERROR_CUT_ERROR;
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_CUTTER_ERROR;
#if defined(SATSUKI2) /* スキャナーコピー時紙つまりとエラー表示時間長いの不具合の為、追加します。 by Smuratec 2003/11/24 */
				TxMsg.Message = MSGL_PRINTER_ERROR;
				snd_msg(*tx_mail_box_no, &TxMsg);
#endif
			}
#endif

			ChangeRxMotorPhase();

		} else if (PrinterEventStatus & PRT_EVT_DOC_READY_COMPLETE) {

			PrinterEventStatus &= ~PRT_EVT_DOC_READY_COMPLETE;

#if (0)
** 			/* EndMark3 スキャナーコピー時、EndMarkが見れていなかった
** 			** by O.Kimoto 1999/02/19
** 			*/
** 			TxMsg.Message = MSGL_READY_POS_COMP;
#else
			if (EndMarkDetect == TRUE) {

#if (0)
** 				/* エンドマーク検出とＪＡＭの区別ができないので、エラーメッセージ変更
** 				** by O.Kimoto 1999/03/09
** 				*/
** 				PrinterError |= PRT_ERROR_NO_PAPER;
** 				SYS_MachineStatus[SYS_PRINTER_STATUS1] |=SYS_PRINTER_NO_PAPER; /* マシーンステータスもあわせてセットします。 by O.Kimoto 1999/02/24 */
#else
				PrinterError |= PRT_ERROR_JAM;
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM;
#endif

				TxMsg.Message = MSGL_PRINTER_ERROR;
			}
			else {
				TxMsg.Message = MSGL_READY_POS_COMP;
			}
#endif

			snd_msg(*tx_mail_box_no, &TxMsg);

		} else if (PrinterEventStatus & PRT_EVT_DOC_PRINT_POS) {
			PrinterEventStatus &= ~PRT_EVT_DOC_PRINT_POS;
			if (PrinterUseMode == PRINT_SCOPY) {
				Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
				Paper.Position = PAPER_POS_PRINTING;
				TxMsg.Message = MSGL_START_MAKEIMAGE;
				snd_msg(*tx_mail_box_no, &TxMsg);
			} else if (PrinterUseMode == PRINT_RXPRINT) {
				Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
				Paper.Position = PAPER_POS_PRINTING;
			}
		}
	} /* for end */
}

void	ExitPrintImageEventTask(void)
{
	exi_tsk();
}


/*
 *	Name:	Start Page Print Procedure
 *	Create:	Mon Aug 24 19:53:45 1998	by	ishiyama
 *	Synopsis:
 *		static void	StartPagePrintProcedure(void);
 *	Description:
 *		ページプリントスタートの手続きをまとめた関数
 *	Return Value:
 *		TRUE:	Start 成功
 *		FALSE:	Start 失敗
 *	Change Log:
 *		
 */
static BOOL	StartPagePrintProcedure(void)
{
	BOOL	Success;

	Success = TRUE;
	Success = StartPagePrint();
	if (Success) {
		SetPrinterPageCount(PageQ.Size);	/* LifeMonitor */
	}
	return	Success;
}

#if (0) /* 1998/10/31 by T.Soneoka */
**/*
** *	Name:	Stop Page Print Procedure
** *	Create:	Mon Aug 24 20:31:54 1998	by	ishiyama
** *	Synopsis:
** *		static void	StopPagePrintProcedure(void);
** *	Description:
** *		ページプリント中断手続きをまとめた関数
** *	Return Value:
** *		void
** *	Change Log:
** *		
** */
**static void	StopPagePrintProcedure(void)
**{
**	if (tskno_PRN_PrintImageEvent != 0xffff) {
**		del_tsk(&tskno_PRN_PrintImageEvent);
**	}
**	StopPagePrint();
**}
#endif

/*
 *	Name:	Query Ignore Printer Error in Print Image
 *	Create:	Mon Jul 20 17:38:32 1998	by	ishiyama
 *	Synopsis:
 *		static BOOL QueryIgnorePrinterError(void);
 *	Description:
 *		プリント中は無視すべきプリンタエラーかどうかを判断する
 *		サーマルヘッド温度上昇
 *		リアルタイムコピーのスキャナモジュールで監視する
 *	Return Value:
 *		TRUE:	無視すべきエラー
 *		FALSE:	無視しちゃダメ
 *	Change Log:
 *		
 */
BOOL	QueryIgnorePrinterError(void)
{
	BOOL	Rslt;

	Rslt = TRUE;
	if (PrinterError & PRT_ERROR_NO_PAPER) {		/* 記録紙なしエラー */
		Rslt = FALSE;
	}
	if (PrinterError & PRT_ERROR_JAM) {				/* ジャム */
		Rslt = FALSE;
	}
	if (PrinterError & PRT_ERROR_CUT_ERROR) {		/* カットエラー */
		Rslt = FALSE;
	}
	if (PrinterError & PRT_ERROR_COVER_OPEN) {		/* カバーオープン */
		Rslt = FALSE;
	}

	/* 追加 1998/12/01 by T.Soneoka */
	if (PrinterError & PRT_ERROR_HIGH_TEMP) {	/* 高温印可不可 */
		Rslt = FALSE;
	}
	return	Rslt;
}


#if (0) /* 1998/10/31 by T.Soneoka */
**/*
** *	Name:	Query No Paper
** *	Create:	Mon Sep 21 21:04:12 1998	by	ishiyama
** *	Synopsis:
** *		static BOOL	QueryNoPaper(void);
** *	Description:
** *		記録紙がない
** *	Return Value:
** *		TRUE:	記録紙なし
** *		FALSE:	記録しあり
** *	Change Log:
** *		
** */
**static BOOL	QueryNoPaper(void)
**{
**	BOOL	Rslt;
**
**	Rslt = FALSE;
**	if (PrinterError & PRT_ERROR_NO_PAPER) {		/* 記録紙がカセットにない */
**		Rslt = TRUE;
**	}
**	return	Rslt;
**}
#endif
