/*
 *	@(#)$Id: PRTWATCH.C,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	/home2/prj/Eva/Src/prt/prtwatch.c
 *	Create:	Mon Apr  6 18:20:18 1998	by	ishiyama
 *	Description:
 *		Printer Watch Task
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"
#include "\src\cpu\sh7043_a\irom\define\def_evtn.h"


#if (0)	/* For Debug By O.Kimoto 1998/10/22 */
** /*
**  *	Name:	Watch Printer Task
**  *	Create:	Mon Apr  6 18:20:52 1998	by	ishiyama
**  *	Synopsis:
**  *		#include	"prt_task.h"
**  *		void	WatchPrinterTask(void);
**  *	Description:
**  *		プリンタ監視タスク
**  *	Notes:
**  *		TxMessages:
**  *		MSG_PRINT_ERRRO				// プリンタカバーオープン
**  *		MSGL_PRINTER_READY			// プリンタエラーから復帰
**  *		MSGL_PRINTER_STOP			// ストップスイッチ
**  *	Return Value:
**  *		void
**  *	Change Log:
**  *		
**  */
** void	WatchPrinterTask(void)
** {
** 	MESSAGE_t	TxMsg;
** 	MESSAGE_t	*RxMsg;
** 
** 	tskno_PRN_WatchPrinter1Sec = 0xffff;
** 
** #if (0)	/* 暫定 1998/10/18 by T.Soneoka */
** **	cre_tsk(&tskno_PRN_WatchPrinter1Sec, TSK_PRN_WATCHPRINTER1SECTASK, (void *)0);
** #endif
** 
** 	TxMsg.Item = FROM_WATCHPRINTER_TASK;
** 	for (;;) {
** 		rcv_msg(mbxno.PRN_WatchPrinterTask, &RxMsg);
** 
** 		switch (RxMsg->Message) {
** 		case MSGL_PRINTER_ERROR:			/* Printer Errorで停止 */
** 			TxMsg.Message = MSGL_PRINTER_ERROR;
** 			snd_msg(mbxno.PRN_PrinterTask, &TxMsg);
** 			break;
** 
** #if (0)	/* For Debug By O.Kimoto 1998/10/22 */
** ** 		case MSGL_PRINTER_STOP:		/* ストップスイッチ */
** ** 			TxMsg.Message = MSGL_PRINTER_STOP;
** ** 			snd_msg(mbxno.PRN_PrinterTask, &TxMsg);
** ** 			break;
** #endif
** 
** 		default:
** 			break;
** 		}
** 	} /* for end */
** }
** 
** /*
**  *	Name:	Exit Watch Printer  Task
**  *	Create:	Mon Apr  6 15:06:35 1998	by	ishiyama
**  *	Synopsis:
**  *		#include	"prt_task.h"
**  *		void	ExitWatchPrinterTask(void);
**  *	Description:
**  *		Watch Printer Task 終了関数
**  *	Notes:
**  *		常駐する場合、コールされない
**  *	Return Value:
**  *		void
**  *	Change Log:
**  *		
**  */
** void	ExitWatchPrinterTask(void)
** {
** 	if (tskno_PRN_WatchPrinter1Sec != 0xffff) {
** 		del_tsk(&tskno_PRN_WatchPrinter1Sec);
** 	}
** 	exi_tsk();
** }
** 
** 
** 
** /*
**  *	Name:	Watch Printer by 1 sec Timer Task
**  *	Create:	Mon Apr  6 18:41:06 1998	by	ishiyama
**  *	Synopsis:
**  *		#include	"prt_task.h"
**  *		void	WatchPrinter1SecTask(void);
**  *	Description:
**  *		1秒ごとにプリンタ関連ステータスを監視
**  *	Return Value:
**  *		void
**  *	Change Log:
**  *		
**  */
** void	WatchPrinter1SecTask(void)
** {
** 	MESSAGE_t	TxMsg;
** 	UWORD	PrevError;
** 	UWORD	CurrentError;
** 	BOOL	EnableInt;
** 
** 	/* Power ON でインクリボンを張るために送る */
** 	if (QueryPrinterCoverOpen()) {
** 		PrinterCoverOpened = TRUE;
** 	} else {
** 		PrinterCoverOpened = FALSE;
** 	}
** 
** 	PrevError = 0;
** 	TxMsg.Item = FROM_WATCHPRINTER1SEC_TASK;
** 	for (;;) {
** 
** 		/* ストップスイッチチェック */
** 		if (!PrinterStopProcess) {
** 			if (SYS_ImagePrintStopSwitch()) {
** 				EnableInt = CheckInterruptEnable(); /* 割込み状態保存 */
** 				CMN_DisableInterrupt();					/* 割込み禁止 */
** 				PrinterStopProcess = TRUE;
** 				if (EnableInt) {		/* 割込み状態リストア */
** 					CMN_EnableInterrupt();
** 				}
** 				TxMsg.Message = MSGL_PRINTER_STOP;	/* ストップスイッチ */
** 				snd_msg(mbxno.PRN_WatchPrinterTask, &TxMsg);
** 			}
** 		}
** 
** 		/* Printer Cover Open */
** 		if (QueryPrinterCoverOpen()) {
** 			StopRxMotor();
** 		}
** 
** 		/* Printer Error Status の更新 */
** 		CurrentError = QueryPrinterError();
** 
** 		if (CurrentError != PrevError) {
** 			/* プリンタエラー状態変化 */
** 			TxMsg.Message = MSGL_PRINTER_ERROR;
** 			snd_msg(mbxno.PRN_WatchPrinterTask, &TxMsg);
** 			
** 			if (CurrentError & PRT_ERROR_COVER_OPEN) {
** 				PrinterCoverOpened = TRUE;
** 			}
** 			if (PrinterCoverOpened && !(CurrentError & PRT_ERROR_COVER_OPEN)) {
** 				PrinterCoverOpened = FALSE;
** 				/* カバーが閉じた */
** 			}
** 			PrevError = CurrentError;
** 		}
** 
** 		wai_tsk(1000 / 10);			/* 1000msec -> 1sec */
** 	}
** }
#endif

