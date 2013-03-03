/*
 *	@(#)$Id: TEMP.C,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	/mnt/jason/home2/prj/Eva/Src/prt/prtmainm.c
 *	Create:	Tue Mar 10 15:42:48 1998	by	ishiyama
 *	Description:
 *		Printer Control Main Message 処理
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\sysprint.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\man_data.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"
#include "\src\cpu\sh7043_a\irom\define\tib_pro.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"

/* static UBYTE AnalyzeMessageFromMain(MESSAGE_t *); */
/* static UBYTE AnalyzeMessageFromAddIndexQ(MESSAGE_t *); */
/* static UBYTE AnalyzeMessageFromMakeImage(MESSAGE_t *); */
static UBYTE AnalyzeMessageFromPrintImage(MESSAGE_t *);
/* static UBYTE AnalyzeMessageFromWatchPrinter(MESSAGE_t *); */


/*************************************************************************
	module		:[プリントメインタスク]
	function	:[メインタスクとイメージプリントタスクのインターフェースタスク
		１．ＬＯＴＵＳ／ＫＵＲＵＭＩの構造をＡＴＬＡＮＴＡ用に変更
		２．各プリントクラスによってプリント処理を行う
			・イニシャルカット
			・リアルタイムコピー
		３．プリンタ終了状態をメインタスクにメッセージを送る
	]
	return		:[
	]
	common		:[
	]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[PRN]
	date		:[1998/10/05]
	author		:[T.Soneoka]
*************************************************************************/
void	PRN_CopyPrintTask(void)	/* Rename PRN_ImagePrintTask to PRN_CopyPrintTask By O.Kimoto 1998/10/27 */
{
	MESSAGE_t	TxMsg;
	MESSAGE_t	*RxMsg;
	UBYTE	IsExitPrintLoop;
	UBYTE	rtn;
	
	InzPrinterParameter();				/* プリンタ関係大域変数初期化 */

	switch (SYS_DocumentPrintClass) {

	/*
	/* イニシャルカット
	*/
	case SYS_PRINT_CLASS_INITIAL:
		if (PS1() && PS2()) {
			SetPaperAttribute();
			IsDocument = FALSE;
			PrinterUseMode = PRINT_SCOPY;	/* Add By O.Kimoto 1998/10/26 */
			Paper.Phase = PAPER_PHASE_FEED;
			Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
			Paper.Position = PAPER_POS_MOVE_TO_MINI_DOC_EXIT;
			EnableIntPrinterTimer();
			cre_tsk(&tskno_PRN_PrintImageEvent, TSK_PRN_PRINTIMAGEEVENTTASK, &mbxno.PRN_Task);
			SetupRxMotor(RX_MOTOR_FORWARD);
			StartRxMotor();
			
			rcv_msg(mbxno.PRN_Task, &RxMsg);

			if (tskno_PRN_PrintImageEvent != 0xffff) {
				del_tsk(&tskno_PRN_PrintImageEvent);
			}
			DisableIntPrinterTimer();
		}
		TxMsg.Item = FROM_PRN_ALLPAGE_PRINT_TASK;
		TxMsg.Message = MSG_PRN_IMAGE_INITIAL_END;
		break;

	/*
	/* リアルタイムコピー
	*/
	case SYS_PRINT_CLASS_REALTIMECOPY:

		InzPrinterTaskNo();		/* TASK No.全初期化 */
		PrinterUseMode = PRINT_SCOPY;	/* Add By O.Kimoto 1998/10/26 */
		CreatePrinterTasks();	/* タスク生成 */

		TxMsg.Item = FROM_PRN_IMAGE_PRINT_TASK;
		TxMsg.Message = MSGL_PREPARE_MAKEIMAGE;
		snd_msg(mbxno.PRN_PrintImageTask, &TxMsg);

		do {
			rcv_msg(mbxno.PRN_PrinterTask, &RxMsg);

			IsExitPrintLoop = TRUE;
			/* メッセージ解析 */
			switch (RxMsg->Item) {
			case FROM_PRINTIMAGE_TASK:				/* Print Image Task からのメッセージ処理 */
				if (rtn = AnalyzeMessageFromPrintImage(RxMsg)) {
					IsExitPrintLoop = FALSE;
				}
				break;

			default:
				break;
			}
		} while (IsExitPrintLoop);

		DeletePrinterTasks();

		switch (rtn) {
		case MSG_PRINT_END:			/* プリント１ＪＯＢ終了 */
		case MSG_PRINT_STOPSW:		/* プリント停止 */
		case MSG_PRINT_ERROR:		/* プリントエラーで停止 */
		case MSG_PRINT_DETECT_ERROR:/* プリンタ・エラー発生通知(表示更新用) */
			TxMsg.Item = FROM_PRN_REALTIMECOPY_TASK;
			TxMsg.Message = MSG_PRN_REALTIMECOPY_END;
			break;

		default:
			break;
		}
		break;
	
	/*
	** プリンタ受信
	** by H.Hirao 1998/11/07
	*/
	case SYS_PRINT_CLASS_PRINTER_RX:
		
		InzPrtImageBuf();	/** Initialize Print Image Buffer */
		InzPrinterTaskNo();		/* TASK No.全初期化 */
		PrinterUseMode = PRINT_RXPRINT;
		CreatePrinterTasks();	/* タスク生成 */

		TxMsg.Item = FROM_PRN_IMAGE_PRINT_TASK;
		TxMsg.Message = MSGL_PREPARE_MAKEIMAGE;
		snd_msg(mbxno.PRN_PrintImageTask, &TxMsg);

		do {
			rcv_msg(mbxno.PRN_PrinterTask, &RxMsg);

			IsExitPrintLoop = TRUE;
			/* メッセージ解析 */
			switch (RxMsg->Item) {
			case FROM_PRINTIMAGE_TASK:				/* Print Image Task からのメッセージ処理 */
				if (rtn = AnalyzeMessageFromPrintImage(RxMsg)) {
					IsExitPrintLoop = FALSE;
				}
				break;

			default:
				break;
			}
		} while (IsExitPrintLoop);

		DeletePrinterTasks();

		switch (rtn) {
		case MSG_PRINT_END:			/* プリント１ＪＯＢ終了 */
		case MSG_PRINT_STOPSW:		/* プリント停止 */
		case MSG_PRINT_ERROR:		/* プリントエラーで停止 */
		case MSG_PRINT_DETECT_ERROR:/* プリンタ・エラー発生通知(表示更新用) */
			TxMsg.Item = FROM_PRN_REALTIMECOPY_TASK;
			TxMsg.Message = MSG_PRN_REALTIMECOPY_END;
			break;

		default:
			break;
		}

		break;

	default:
		break;
	}
	snd_msg(mbxno.MAN_Task, &TxMsg);
	wai_tsk(0xFFFF);
}

void	PRN_ExitCopyPrintTask(void)		/* Remane PRN_ExitImagePrintTask to PRN_ExitCopyPrintTask By O.Kimoto 1998/10/27 */
{
	exi_tsk();
}

#if (0)
** /*
**  *	Name:	Analyze Message From Main task
**  *	Create:	Mon Mar 23 16:35:35 1998	by	ishiyama
**  *	Synopsis:
**  *		static void	AnalyzemessageFromMain(MESSAGE_t RxMsg);
**  *	Description:
**  *		Main Task からのメッセージを解析する
**  *	Return Value:
**  *		void
**  *	Change Log:
**  *		
**  */
** static UBYTE AnalyzeMessageFromMain(
** 	MESSAGE_t *RxMsg)
** {
** 	MESSAGE_t	TxMsg;
** 	UBYTE		rtn;
** 	
** 	rtn = MSG_CONTINUE;
** 
** 	TxMsg.Item = FROM_PRN_IMAGE_PRINT_TASK;
** 	switch (RxMsg->Message) {
** 	case MSGL_INDEX_QUEUE_ACK:			/* プリント要求（キューに登録） */
** 		/* Make Image Task に IndexQ 追加を通知 */
** 		TxMsg.Message = MSGL_INDEX_QUEUE_ACK;
** 		snd_msg(mbxno.PRN_MakeImageTask, &TxMsg);
** 
** #if (0)
** **	case MSG_TEST_PRINT:
** **		TestPrint4GA();
** **		break;
** #endif
** 	default:
** 		break;
** 	}
** 
** 	return rtn;
** }
** 
** 
** 
** /*
**  *	Name:	Analyze Message from Add Index Queue Task
**  *	Create:	Fri Mar 27 15:23:07 1998	by	ishiyama
**  *	Synopsis:
**  *		static void	AnalyzeMessageFromAddIndexQ(
**  *			MESSAGE_t RxMessage);
**  *	Description:
**  *		Add Index Queue Task からのメッセージ処理
**  *	Return Value:
**  *		void
**  *	Change Log:
**  *		
**  */
** static UBYTE AnalyzeMessageFromAddIndexQ(
** 	MESSAGE_t *RxMsg)						/* Rx Message */
** {
** 	MESSAGE_t	TxMsg;
** 	MESSAGE_t	TxMsgToMain;
** 	UBYTE		rtn;
** 	
** 	rtn = MSG_CONTINUE;
** 
** 	TxMsg.Item = FROM_PRN_IMAGE_PRINT_TASK;
** 	TxMsgToMain.Item = FROM_PRN_IMAGE_PRINT_TASK;
** 	switch (RxMsg->Message) {
** 	case MSGL_INDEX_QUEUE_ACK:			/* プリント要求（キューに登録） */
** 		/* Make Image Task に IndexQ 追加を通知 */
** 		TxMsg.Message = MSGL_INDEX_QUEUE_ACK;
** 		snd_msg(mbxno.PRN_MakeImageTask, &TxMsg);
** 		break;
** 	default:
** 		break;
** 	}
** 
** 	return rtn;
** }
** 
** 
** /*
**  *	Name:	Analyze Message From Make Print Image
**  *	Create:	Fri Apr  3 14:15:58 1998	by	ishiyama
**  *	Synopsis:
**  *		
**  *	Description:
**  *		Make Print Image Task からのメッセージ処理
**  *	Return Value:
**  *		void
**  *	Change Log:
**  *		
**  */
** static UBYTE AnalyzeMessageFromMakeImage(MESSAGE_t *RxMsg)
** {
** 	MESSAGE_t	TxMsg;
** 	UBYTE		rtn;
** 	
** 	rtn = MSG_CONTINUE;
** 
** 	TxMsg.Item = FROM_PRN_IMAGE_PRINT_TASK;
** 	switch (RxMsg->Message) {
** 	case MSGL_DEQUEUE_INDEX:
** 		/* Image 作成終了を通知 */
** 		TxMsg.Message = MSGL_DEQUEUE_INDEX;
** 		snd_msg(mbxno.PRN_PrintImageTask, &TxMsg);
** 		break;
** 
** 	case MSGL_START_MAKEIMAGE:			/* Image 作成開始 */
** 		/* Image 作成開始を通知 */
** 		TxMsg.Message = MSGL_START_MAKEIMAGE;
** 		snd_msg(mbxno.PRN_PrintImageTask, &TxMsg);
** 		break;
** 
** #if (0)	/* For Debug By O.Kimoto 1998/10/22 */
** ** 	case MSGL_DELETE_QUEUE:
** ** 		/* Print Image Task に PageQ初期化を通知 */
** ** 		TxMsg.Message = MSGL_DELETE_QUEUE;
** ** 		snd_msg(mbxno.PRN_PrintImageTask, &TxMsg);
** ** 		break;
** #endif
** 
** 	default:
** 		break;
** 	}
** 
** 	return rtn;
** }
#endif


/*
 *	Name:	Analyze Message from Print Image Task
 *	Create:	Fri Mar 27 15:47:46 1998	by	ishiyama
 *	Synopsis:
 *		static void	AnalyzeMessageFromPrintImage(MESSAGE_t RxMsg);
 *	Description:
 *		Print Image Task からのメッセージ処理
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
static UBYTE AnalyzeMessageFromPrintImage(
	MESSAGE_t	*Msg)						/* Rx Message */
{
	MESSAGE_t	TxMsg;
	MESSAGE_t	*RxMsg;
	UBYTE		rtn;
	
	rtn = MSG_CONTINUE;

	TxMsg.Item = FROM_PRN_IMAGE_PRINT_TASK;
	switch (Msg->Message) {
	case MSGL_PAGE_END:					/* １ページ正常にプリント完了 */
		/* Main Task に Print 終了を通知 */
		rtn = MSG_PRINT_END;
		break;

#if (0)	/* For Debug By O.Kimoto 1998/10/22 */
** 	case MSGL_PRINTER_STOP:				/* STOPSW でプリント終了 */
** #if (0)
** ** 		/* Add Index Queue Task にストップスイッチが押されたことを通知 */
** ** 		TxMsg.Message = MSGL_DELETE_QUEUE;
** ** 		snd_msg(mbxno.PRN_AddIndexQueueTask, &TxMsg);
** #endif
** 		/* Make Image Task にストップスイッチが押されたことを通知 */
** 		TxMsg.Message = MSGL_PRINTER_STOP;
** 		snd_msg(mbxno.PRN_MakeImageTask, &TxMsg);
** 
** 		/* すべての Queue を初期化 */
** 		InzPageMemoryControl();				/* Print Memory Control Block 初期化 */
** 
** 		/* Main Task に STOPSW でプリント終了を通知 */
** 		rtn = MSG_PRINT_STOPSW;
** 
** 		PrinterStopProcess = FALSE;
** 		break;
#endif

	case MSGL_PRINTER_ERROR:			/* エラーで停止 */
#if (0) /* 1998/10/05 by T.Soneoka */
** 		/* Add Index Queue Task にプリントできなくなった旨通知 */
** 		TxMsg.Message = MSGL_DELETE_QUEUE;
** 		snd_msg(mbxno.PRN_AddIndexQueueTask, &TxMsg);
** 
** 		/* Make Image Task にプリントできなくなった旨通知 */
** 		TxMsg.Message = MSGL_DELETE_QUEUE;
** 		snd_msg(mbxno.PRN_MakeImageTask, &TxMsg);
#endif

		/* Main Task にエラー終了を通知 */
		rtn = MSG_PRINT_ERROR;

		PrinterStopProcess = FALSE;
		break;

	default:
		break;
	}

	return rtn;
}


#if (0)	/* For Debug By O.Kimoto 1998/10/22 */
** /*
**  *	Name:	Analyze Message From Watch Printer Task
**  *	Create:	Fri Apr  3 15:14:33 1998	by	ishiyama
**  *	Synopsis:
**  *		static void	AnalyzeMessageFromWatchPrinter(MESSAGE_t RxMsg);
**  *	Description:
**  *		Watch Printer Task からのメッセージを処理
**  *	Return 
**  *		void
**  *	Change Log:
**  *		
**  */
** static UBYTE AnalyzeMessageFromWatchPrinter(
** 	MESSAGE_t *RxMsg)
** {
** 	MESSAGE_t	TxMsg;
** 	UBYTE		rtn;
** 	
** 	rtn = MSG_CONTINUE;
** 
** 	TxMsg.Item = FROM_PRN_IMAGE_PRINT_TASK;
** 	switch (RxMsg->Message) {
** 	case MSGL_PRINTER_ERROR:			/* エラーで停止 */
** 		if (PrinterError) {
** 			/* Print Image Task にエラーを通知 */
** 			TxMsg.Message = MSGL_PRINTER_ERROR;
** 			snd_msg(mbxno.PRN_MakeImageTask, &TxMsg);
** 		}
** 
** 		/* Main Task に エラーを通知 */
** 		rtn = MSG_PRINT_DETECT_ERROR;
** 
** 		break;
** 
** #if (0)	/* For Debug  By O.Kimoto 1998/10/22 */
** ** 	case MSGL_PRINTER_STOP:
** ** 		/* Print Image Task にストップスイッチが押されたことを通知 */
** ** 		TxMsg.Message = MSGL_PRINTER_STOP;
** ** 		snd_msg(mbxno.PRN_PrintImageTask, &TxMsg);
** ** 		/*
** ** 		 *	メインタスクへの通知は、PrintImage タスク処理後行う
** ** 		 */
** ** 		break;
** #endif
** 
** 	default:
** 		break;
** 	}
** 
** 	return rtn;
** }
#endif

void PRN_PreOpen(void)
{
	SYS_DocumentPrintClass = SYS_PRINT_CLASS_PRINTER_RX;
	cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_COPYPRINTTASK, 0);
}

void PRN_PostClose(void)
{
	MESSAGE_t	TxMsg;

	TxMsg.Message = MSGL_PRINT_CLOSE;
	snd_msg(mbxno.PRN_PrintImageTask, &TxMsg);
}

void PRT_StartPrint(void)
{
	MESSAGE_t	TxMsg;

	TxMsg.Message = MSGL_START_MAKEIMAGE;
	snd_msg(mbxno.PRN_PrintImageTask, &TxMsg);
}

