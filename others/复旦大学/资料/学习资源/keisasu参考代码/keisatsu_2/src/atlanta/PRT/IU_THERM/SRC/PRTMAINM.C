/*
 *	@(#)$Id: PRTMAINM.C,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
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
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\man_data.h"
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\ext_v\scn_dath.h"
 #else
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
 #endif
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"
#include "\src\cpu\sh7043_a\irom\define\tib_pro.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"

#if defined(HINOKI2) || defined (HINOKI3)	/* ＰＳ２自動調整機能 by Y.kano 2004/04/05 */
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\hinoki\define\m_param.h"
#include "\src\atlanta\ext_v\ini_tbl.h"	/* Add by Y.kano 2004/04/06 */
 #if (PRO_PAPER_AD_SENSOR_INIT == DISABLE)
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"	/* ＰＳ２自動調整不具合対応 by Y.kano 2004/12/06 */
 #endif
#endif

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
	
	UBYTE	i;			/* 移植 by SMuratec K.W.Q 2003/07/29 */
	
	InzPrinterParameter();				/* プリンタ関係大域変数初期化 */

	switch (SYS_DocumentPrintClass) {

	/*
	/* イニシャルカット
	*/
	case SYS_PRINT_CLASS_INITIAL:

#if defined(SATSUKI2)
/* 移植 by SMuratec K.W.Q 2003/07/29 */
/**************** 元のSATSUKI仕様ではイニシャルカットする前に１秒間待たせている為、追加します。by Y.Kano 2003/07/24 */
		/** 1秒間待ちます */
		for( i = 0 ; i < 50 ; i ++ ) {
			wai_tsk(2); /* 20msec */
			if (!PRN_PrintErrorHaltRequest()) {	/* エラーが発生したら抜けます。by Y.Kano 2003/07/24 */
				break;
			}
		}
/***********************************************************************************/
#endif
		if (PS1() && PS2()) {
			SetPaperAttribute();
			IsDocument = FALSE;
			PrinterUseMode = PRINT_SCOPY;	/* Add By O.Kimoto 1998/10/26 */
			Paper.Phase = PAPER_PHASE_FEED;
/*
** イニシャルカットにて、余分な動きをするのを修正
** 1999/04/09 by T.Soneoka
*/
#if (0)
**			Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
#else
			Paper.Route = ROUTE_PRINTING_TO_READY;
#endif
#if defined(HINOKI2) && (PRO_PAPER_AD_SENSOR_INIT == DISABLE)	/* ＰＳ２自動調整不具合対応 by Y.kano 2004/12/06 */
			PrtBackStepPS2Flag = FALSE;
#endif
			Paper.Position = PAPER_POS_MOVE_TO_MINI_DOC_EXIT;
			EnableIntPrinterTimer();
			cre_tsk(&tskno_PRN_PrintImageEvent, TSK_PRN_PRINTIMAGEEVENTTASK, &mbxno.PRN_Task);
			SetupRxMotor(RX_MOTOR_FORWARD);
			StartRxMotor();
			
			rcv_msg(mbxno.PRN_Task, &RxMsg);

			/* EndMark5
			** イニシャルカット時のエンドマークチェックが抜けていた
			** by O.Kimoto 1999/03/09
			*/
			if (EndMarkDetect == TRUE) {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM;
			}

			if (RxMsg->Message == MSGL_PRINTER_ERROR) {
				if (PrinterError & PRT_ERROR_NO_PAPER) {			/* 記録紙なしエラー */
					SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER;

				} else 	if (PrinterError & PRT_ERROR_JAM) {			/* 記録紙ＪＡＭエラー */
					SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM;

				} else if (PrinterError & PRT_ERROR_CUT_ERROR) {	/* カッタエラー */
					SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_CUTTER_ERROR;

				} else if (PrinterError & PRT_ERROR_COVER_OPEN) {	/* カバーオープンエラー */
					SYS_MachineStatus[SYS_COVER_STATUS] |= SYS_COVER_PRINTER_OPEN;

				} else if (PrinterError & PRT_ERROR_HIGH_TEMP) {	/* 高温印可不可 */
					SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;

				} else {											/* 高温印字解除 */
					SYS_MachineStatus[SYS_PRINTER_STATUS2] &= ~SYS_PRINTER_HIGH_TEMP;

				}
			}

#if defined (HINOKI2) || defined (HINOKI3) || defined (SATSUKI2)	/* 2002/02/25 T.Takagi */
			if (PRN_OverHeatCheck() == TRUE) {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
			}
#endif
#if (0)	/* ここで実閾値を算出するのをやめます。by Y.kano 2004/12/10 */
#if defined(HINOKI2) || defined (HINOKI3)	/* ＰＳ２自動調整機能 by Y.Kano 2004/04/05 */
			if (!((SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM)
				|| (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_CUTTER_ERROR)
				|| (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_HIGH_TEMP)
				|| (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER)
				|| (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN))) {
				if (PS2()) {
					if (!SYB_PS2_SensorStatus) {
						/* ＰＳ２の実スライスレベル（Ｖｓ）の算出 */
						SYB_MachineParameter[M_PARA_SW_J6] = (UBYTE)(((PS2_Vb_Value + SYB_MachineParameter[M_PARA_SW_J3]) / 2));
						SYB_PS2_SensorStatus = TRUE;	/* ＰＳ２自動調整機能実行済みフラグＯＮ */
						SensorRetryCount = 0;
					}
				}
			}
#endif
#endif
			if (tskno_PRN_PrintImageEvent != 0xffff) {
				del_tsk(&tskno_PRN_PrintImageEvent);
			}
			DisableIntPrinterTimer();
		}
		else {
			/* 追加 by O.Kimoto 1998/12/07 */
			if (!PS1()) {
				SYS_MachineStatus[SYS_PRINTER_STATUS1] |= SYS_PRINTER_NO_PAPER;
			}
			else {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM;
			}
#if defined(HINOKI2) && (PRO_PAPER_AD_SENSOR_INIT == DISABLE)	/* ＰＳ２自動調整機能 by Y.Kano 2004/04/06 */
			/* 連続してエラーが発生した場合、ＰＳ２の実スライスレベルを０ｘＢ３にセットしなおします。by Y.Kano 2004/04/06 */
			if (!SYB_PS2_SensorStatus) {
				if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM) {
					SensorRetryCount++;
					if (SensorRetryCount >= 0x02) {
						SYB_MachineParameter[M_PARA_SW_J6] = MachineParameterInitialTable[M_PARA_SW_J6];
						SensorRetryCount = 0;
					}
				}
			}
#endif
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

#if (0) /* 1998/11/19 by T.Soneoka */
**			/* メッセージ解析 */
**			switch (RxMsg->Item) {
**			case FROM_PRINTIMAGE_TASK:				/* Print Image Task からのメッセージ処理 */
**				if (rtn = AnalyzeMessageFromPrintImage(RxMsg)) {
**					IsExitPrintLoop = FALSE;
**				}
**				break;
**
**			default:
**				break;
**			}
#else
			if (rtn = AnalyzeMessageFromPrintImage(RxMsg)) {
				IsExitPrintLoop = FALSE;
			}
#endif
		} while (IsExitPrintLoop);

		DeletePrinterTasks();

		switch (rtn) {
		case MSG_PRINT_END:			/* プリント１ＪＯＢ終了 */
			TxMsg.Item = FROM_PRN_REALTIMECOPY_TASK;
			TxMsg.Message = MSG_PRN_REALTIMECOPY_END;
			break;
		case MSG_PRINT_STOPSW:		/* プリント停止 */
		case MSG_PRINT_ERROR:		/* プリントエラーで停止 */
			TxMsg.Item = FROM_PRN_REALTIMECOPY_TASK;
			TxMsg.Message = MSG_PRN_REALTIMECOPY_ERROR;
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
		
#if (0) /* コーデック側で行います 1998/12/10 by T.Soneoka */
**		InzPrtImageBuf();	/** Initialize Print Image Buffer */
#endif
		InzPrinterTaskNo();		/* TASK No.全初期化 */
		PrinterUseMode = PRINT_RXPRINT;
		CreatePrinterTasks();	/* タスク生成 */

		TxMsg.Item = FROM_PRN_IMAGE_PRINT_TASK;
		TxMsg.Message = MSGL_PREPARE_MAKEIMAGE;
		snd_msg(mbxno.PRN_PrintImageTask, &TxMsg);

		do {
			rcv_msg(mbxno.PRN_PrinterTask, &RxMsg);

			IsExitPrintLoop = TRUE;

#if (0) /* 1998/11/19 by T.Soneoka */
**			/* メッセージ解析 */
**			switch (RxMsg->Item) {
**			case FROM_PRINTIMAGE_TASK:				/* Print Image Task からのメッセージ処理 */
**				if (rtn = AnalyzeMessageFromPrintImage(RxMsg)) {
**					IsExitPrintLoop = FALSE;
**				}
**				break;
**
**			default:
**				break;
**			}
#else
			if (rtn = AnalyzeMessageFromPrintImage(RxMsg)) {
				IsExitPrintLoop = FALSE;
			}
#endif
			break;
		} while (IsExitPrintLoop);

		DeletePrinterTasks();

		switch (rtn) {
		case MSG_PRINT_END:			/* プリント１ＪＯＢ終了 */
			TxMsg.Item = FROM_PRN_REALTIMECOPY_TASK;
			TxMsg.Message = MSG_PRN_REALTIMECOPY_END;
			break;

		case MSG_PRINT_STOPSW:		/* プリント停止 */
		case MSG_PRINT_ERROR:		/* プリントエラーで停止 */
			TxMsg.Item = FROM_PRN_REALTIMECOPY_TASK;
			TxMsg.Message = MSG_PRN_REALTIMECOPY_ERROR;
			break;
		default:
			break;
		}

		break;

	default:
		break;
	}
	
	/* 1998/12/8 by T.Soneoka */
	DMA_RequestMask(DMA_GATEARRAYWRITE_CH);
	DisableIntPrinterTimer();

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
#if (0) /* ストップSwもみるように変更します 1999/1/18 by T.Soneoka */
**		rtn = MSG_PRINT_END;
#else
		if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_SCANNER_COPY) {
			rtn = MSG_PRINT_STOPSW;
		} else {
			rtn = MSG_PRINT_END;
		}
#endif
		break;

	case MSGL_PRINTER_ERROR:			/* エラーで停止 */
		rtn = MSG_PRINT_ERROR;
		PrinterStopProcess = FALSE;
		break;

	case MSGL_PRINTER_ERROR_CONTI:
		TxMsg.Item = FROM_PRN_REALTIMECOPY_TASK;
		TxMsg.Message = MSG_PRN_REALTIMECOPY_CONTI;
		snd_msg(mbxno.MAN_Task, &TxMsg);

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

	if (tskno_PRN_ImagePrintTask != 0xffff) {
		TxMsg.Message = MSGL_PRINT_CLOSE;
		snd_msg(mbxno.PRN_PrintImageTask, &TxMsg);
	}
}

void PRT_StartPrint(void)
{
	MESSAGE_t	TxMsg;

	/* 追加 1998/12/05 by T.Soneoka */
	DisableIntPrinterTimer();

	if (tskno_PRN_ImagePrintTask != 0xffff) {
		EnablePrintDataMake = FALSE; /* 1998/12/15 by T.Soneoka */
		TxMsg.Message = MSGL_START_MAKEIMAGE;
		snd_msg(mbxno.PRN_PrintImageTask, &TxMsg);
	}
}

