/*******************************************************************
*	System		: SAKAKI
*	File Name	: PRN_INIT.C
*	Author		: K.Kawata
*	Date		: 1998/6/9
*	Description	:
*	Maintenance	:
*			: Original:\src\kobe\anzu\src\prn_drv.c
*             HINOKI用に変更 By O.Kimoto 1998/10/26
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
********************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sysmcopy.h"
#include "\src\atlanta\define\sysprint.h"
#include "\src\atlanta\define\syslifem.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\mntsw_a.h"
#include "\src\atlanta\define\mntsw_h.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\sh7043\define\sh_port.h"
#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"

#if (0)
** /* SAKAKI */
** #include "\src\atlanta\prt\thermal\define\prn_pro.h"
** #include "\src\atlanta\prt\thermal\define\prn_def.h"
** #include "\src\atlanta\prt\thermal\define\prn_stat.h"
** #include "\src\atlanta\prt\thermal\ext_v\prn_tbl.h"
** #include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
** #include "\src\atlanta\sakaki\define\sakiport.h"
** #include "\src\atlanta\sakaki\ext_v\ga_data.h"
#else
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"

#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"

#endif

#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\mntsw_h.h"	/* Endmark2 By O.Kimoto 1999/02/11 */

 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\define\sats_tib.h"
 #else
#include "\src\atlanta\hinoki\define\hino_tib.h"	/* HINOKIプリント中ループ対策 2002/04/17 by T.Soneoka */
 #endif


/* UBYTE	PRN_PrintNocutRequest(void); Delete by O.Kimoto 1998/12/07 */
void PRN_CheckPrinterError(void);
UBYTE	PRN_PrintErrorHaltRequest(void);	/** Add by O.Kimoto 1998/12/07 */

#if (0)
** /******************************************************************
** 	module		:[プリンタとプリンタ・コントローラの初期化]
** 	function	:[
** 		1.
** 	]
** 	return		:[なし]
** 	common		:[
** 	]
** 	condition	:[]
** 	comment		:[メインタスクから初期化時に一回コールされる]
** 	machine		:[SH7043]
** 	language	:[SHC]
** 	keyword		:[PRN]
** 	date		:[1998/6/9]
** 	author		:[K.Kawata]
** 	status		:[]
** ********************************************************************/
** void	PRN_InitPrinter(void)
** {
** #if (0)
** ** 	/* SAKAKI */
** ** 	SYS_MachineStatus[SYS_PRINTER_STATUS1] &= (~SYS_PRINTER_NO_PAPER);
** ** 	SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~(/*SYS_PRINTER_CUTTER_ERROR |*/ SYS_PRINTER_PAPER_JAM | SYS_PRINTER_HIGH_TEMP));
** ** 	SYS_MachineStatus[SYS_COVER_STATUS] &= (~SYS_COVER_PRINTER_OPEN);
** ** 	if (CutterPosition() == CUTTER_BUSY) {	/* カッターが待機位置にあるかチェックする */
** ** 		CutterOn();	/* カッターが待機位置にないときはカッター動作させてカッターを待機位置に置く */
** ** 		while (PRN_Control.CutterBusy) {	/* カッター動作終了待ち */
** ** 			wai_tsk(2);	/* 20ms */
** ** 		}
** ** 	}
** ** 	if (PS1() && (!PS2())) {
** ** 		SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM;
** ** 	}
** ** 	if (PB4()) {/*B4ｾﾝｻは記録紙を引き戻す前にﾁｪｯｸします*/
** ** 		PRN_PB4Sensor = 1;
** ** 	}
** ** 	else {
** ** 		PRN_PB4Sensor = 0;
** ** 	}
** ** 	B_MCR1_Status &= ~IO_BIT_BMEN;	/* RXﾓｰﾀｰ励磁断 */
** ** 	outpw(B_MCR1_PORT,B_MCR1_Status);
** ** 	C_MCR1_Status &= ~IO_BIT_CMEN;	/* IDFﾓｰﾀｰ励磁断 */
** ** 	outpw(C_MCR1_PORT,C_MCR1_Status);
** ** 	PRN_InitialRecoverCompleted = TRUE;
** #endif
** }
#endif


#if (0)
** 	/* 未使用（イニシャルカットはコピープリントタスク使用） By O.Kimoto 1999/02/08 */
** /*************************************************************************
** 	module		:[イニシャルカット処理]
** 	function	:[
** 		1.イニシャルカット分（１０ｃｍ）記録紙を搬送しカットします。
** 	]
** 	return		:[]
** 	common		:[]
** 	condition	:[]
** 	comment		:[]
** 	machine		:[V53]
** 	language	:[CH38(V.2.0B)]
** 	keyword		:[PRN]
** 	ProtoType	:[void PRN_Paper10cmCut(void){}]
** 	date		:[1998/10/26]
** 	author		:[木元  修]
** *************************************************************************/
** void	PRN_Paper10cmCut(void)
** {
** #if (0)
** ** 	/* SAKAKI */
** ** 
** ** UWORD	i;
** ** 
** ** 	if (PRN_PrintErrorHaltRequest() == OK) {
** ** 		PRN_Control.MinLineCount = PRN_STEP_MIN_LINE - PRN_STEP_STANDBY_TO_HEAD;
** ** 		PrintMotorFw();
** ** 		PrintMotorPhase12();
** ** 		PrintMotorSpeed(PRINT_200PPS);
** ** 		PrintMotorStepSet(4);
** ** 		PrintMotor((PRN_Control.MinLineCount + PRN_STEP_HEAD_TO_CUTTER) / 2);
** ** 		PRN_Control.PageCutPhase = 0;
** ** 		PRN_Control.Command = PRN_PAGECUT_REQ;
** ** 		PRN_Control.Status = PRN_PAGE_CUT;
** ** 		PRN_PrintToStandby();	/* 記録紙先端を待機位置にセット */
** ** 
** ** 		if (PB4()) {/*P4ｾﾝｻは記録紙を引き戻す前にﾁｪｯｸします*/
** ** 			PRN_PB4Sensor = 1;
** ** 		}
** ** 		else {
** ** 			PRN_PB4Sensor = 0;
** ** 		}
** ** 
** ** 		B_MCR1_Status &= ~IO_BIT_BMEN;	/* RXﾓｰﾀｰ励磁断 */
** ** 		outpw(B_MCR1_PORT,B_MCR1_Status);
** ** 		C_MCR1_Status &= ~IO_BIT_CMEN;	/* IDFﾓｰﾀｰ励磁断 */
** ** 		outpw(C_MCR1_PORT,C_MCR1_Status);
** ** 		PRN_InitialRecoverCompleted = TRUE;
** ** 	}
** #else
** 	/* HINOKI */
** 
** #if (0)
** ** 	/* プリンターエラーをチェックする関数が同一内容で関数名違いが２つも在るので、
** ** 	** １つに統一します。
** ** 	** by O.Kimoto 1998/12/07
** ** 	*/
** ** 	if (PRN_PrintNocutRequest() == OK) [
** #else
** 	if (PRN_PrintErrorHaltRequest() == OK) {
** 
** #endif
** 
** 		if (PS1() && PS2()) {
** 			PrinterUseMode = PRINT_IMAGE;
** 			SetPaperAttribute();
** 			Paper.Phase = PAPER_PHASE_FEED;
** 			Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
** 			Paper.Position = PAPER_POS_MOVE_TO_MINI_DOC_EXIT;
** 			EnableIntPrinterTimer();
** 			/* cre_tsk(&tskno_PRN_PrintImageEvent, TSK_PRN_PRINTIMAGEEVENTTASK, &mbxno.PRN_Task); */
** 			SetupRxMotor(RX_MOTOR_FORWARD);
** 			StartRxMotor();
** 
** 			CMN_DisableInterrupt();
** 			if (!(PrinterEventStatus & PRT_EVT_CUT_ON)) {
** 				wai_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_CUT_ON to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
** 			}
** 			PrinterEventStatus &= ~PRT_EVT_CUT_ON;
** 			PrinterEventStatus &= ~PRT_EVT_ERROR;	/* Add by O.Kimoto 1998/12/18 */
** 			CMN_EnableInterrupt();
** 
** 			ExecCutter();
** 			Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
** 			/* Add 2 line 1999/1/14 by T.Soneoka */
** 			backward_step_error = BackWardStepErrorFromReady;
** 			Paper.BackWardStepsFromFeedOut = 0;
** 			Paper.Position = PAPER_POS_MOVE_TO_PS2;
** 			ChangeRxMotorPhase();
** 
** 			CMN_DisableInterrupt();
** 			if (!(PrinterEventStatus & PRT_EVT_DOC_PRINT_POS)) {
** 				wai_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_READY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
** 			}
** 			PrinterEventStatus &= ~PRT_EVT_DOC_PRINT_POS;
** 			PrinterEventStatus &= ~PRT_EVT_ERROR;	/* Add by O.Kimoto 1998/12/18 */
** 			CMN_EnableInterrupt();
** 
** 			Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
** 			Paper.Position = PAPER_POS_MOVE_TO_READY;
** 			ChangeRxMotorPhase();
** 
** 			CMN_DisableInterrupt();
** 			if (!(PrinterEventStatus & PRT_EVT_DOC_READY_COMPLETE)) {
** 				wai_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_STANDBY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
** 			}
** 			PrinterEventStatus &= ~PRT_EVT_DOC_READY_COMPLETE;
** 			CMN_EnableInterrupt();
** 
** #if (0)
** ** 		if (tskno_PRN_PrintImageEvent != 0xffff) {
** ** 			del_tsk(&tskno_PRN_PrintImageEvent);
** ** 		}
** #endif
** 
** 			DisableIntPrinterTimer();
** 		}
** 	}
** #endif
** 
** }
#endif


/*************************************************************************
	module		:[記録紙を待機位置から印字待機位置へ移動]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[void PRN_StandbyToPrint(void){}]
	date		:[1998/10/26]
	author		:[木元  修]
*************************************************************************/
void	PRN_StandbyToPrint(void)
{
#if (0)
** 	/* SAKAKI */
** 	/* ＰＢ４センサーが不安定な為記録紙を引き戻す前にＰＢ４センサーをチェックします。*/
** 	if (PB4()) {
** 		PRN_PB4Sensor = 1;
** 	}
** 	else {
** 		PRN_PB4Sensor = 0;
** 	}
** 	/* カッターの位置をチェックし待機位置にない場合は待機位置に戻し１回カットする */
** 	if (CutterPosition() == CUTTER_BUSY) {
** 		CutterOn();
** 		while (PRN_Control.CutterBusy) {
** 			wai_tsk(2);	/* 20ms */
** 		}
** 	}
** 	if (!PS2()) {
** 		SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM;
** 	}
** 	if (PRN_PrintErrorHaltRequest() == OK) {
** 		/* 待機位置－＞記録位置(先端余白3-1mm)にセット */
** 		PrintMotorSpeed(PRINT_200PPS);
** 		PrintMotorStepSet(4);
** 		PrintMotorPhase12();
** 		PrintMotorRev();
** 		PaperMargin = (UWORD)((UWORD)(SYB_MachineParameter[16])-PRN_STEP_BACKRUSH);	/* 感熱 */
** 		PrintMotor((PRN_STEP_STANDBY_TO_HEAD - PaperMargin+128)/2);
** 		PRN_Control.FeedInPhase = 0;
** 		PRN_Control.Status = PRN_PAPER_FEED_IN;
** 		PRN_Control.Command = PRN_FEED_IN_REQ;
** 		ps2_off_count = 2;	/* 先端余白ばらつき対策 */
** 		ps2_off_flag = 0;	/* 先端余白ばらつき対策 */
** 	} else {
** 		PRN_Control.Command = PRN_IDLE_REQ;
** 		PRN_Control.Status = PRN_IDLE;
** 	}
#else
	/* HINOKI */
	Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
	Paper.Position = PAPER_POS_MOVE_TO_PS2;
#if defined(SATSUKI2)	/* 壁掛設定用 追加 by Y.Kano 2003/10/07 */
	if (CHK_WallHangSetting()) { /** 壁掛け設定用 */	/* Add by Y.kano 2003/10/06 */
		Paper.StepsFromPs2On = 0;
		backward_step_error = BackWardStepErrorFromReady;
		Paper.BackWardStepsFromFeedOut = 0;
	}
	else
	{
		backward_step_error = BackWardStepErrorFromReady;
		Paper.BackWardStepsFromFeedOut = 0;
	}
#else
	/* Add 2 line 1999/1/14 by T.Soneoka */
	backward_step_error = BackWardStepErrorFromReady;
	Paper.BackWardStepsFromFeedOut = 0;
#endif
	Paper.Phase = PAPER_PHASE_PRINT;

	PaperMoveCount = PrintReadySteps;	/* 10mm *//* EndMark By O.Kimoto 1999/02/09 */

	ChangeRxMotorPhase();
	EnableIntPrinterTimer();

	CMN_DisableInterrupt();

#if (0)
** 		/* イベント空振りフラグの見方を変更します。
** 		** by O.Kimoto 1999/02/18
** 		*/
** 	if (!(PrinterEventStatus & PRT_EVT_DOC_PRINT_POS)) {
** 		wai_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_READY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
** 	}
#else
	if (!PrinterEventStatus) {
		wai_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_READY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
	}
	PrinterEventStatus = 0; /* 1999/05/07 by T.Soneoka イベントを受け取ったら初期化します */
#endif

	PrinterEventStatus &= ~PRT_EVT_DOC_PRINT_POS;
	PrinterEventStatus &= ~PRT_EVT_ERROR;	/* Add by O.Kimoto 1998/12/18 */
	Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
	Paper.Position = PAPER_POS_PRINTING;
	CMN_EnableInterrupt();
#endif
}


/*************************************************************************
	module		:[記録紙をカット位置まで搬送し、カットします]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[void PRN_CutToPrint(void){}]
	date		:[1998/10/26]
	author		:[木元  修]
*************************************************************************/
UBYTE	PRN_CutToPrint(void)	/* Change void to UBYTE By O.Kimoto 1998/12/07 */
{
#if (0)
** 	/* SAKAKI */
** 
** /* 記録紙ページカット処理起動 */
** 	PaperMargin = (UWORD)((UWORD)(SYB_MachineParameter[18])-PRN_STEP_BACKRUSH);
** 	PrintMotorPhase12();
** 	PrintMotorSpeed(PRINT_200PPS);
** 	PrintMotorStepSet(4);
** 	if (PRN_STEP_MIN_LINE > PRN_Control.PrintLineCount) {
** 		PrintMotor(((PRN_STEP_MIN_LINE - PRN_Control.PrintLineCount) + PRN_STEP_HEAD_TO_CUTTER + PaperMargin - 128) / 2);
** 	}
** 	else {
** 		PrintMotor((PRN_STEP_HEAD_TO_CUTTER + PaperMargin - 128) / 2);
** 	}
** 	PRN_Control.PageCutPhase = 0;
** 	PRN_Control.Command = PRN_PAGECUT_REQ;
** 	PRN_Control.Status = PRN_PAGE_CUT;
** /* プリントタイプがプリンター受信以外の場合はページカット終了を待ちます */
** 	if (1 /*PRN_Control.UseType != IDP_PRINTER_RX*/) {
** 		while (PRN_Control.Status == PRN_PAGE_CUT) {
** 			wai_tsk(10);
** 		}
** 		PRN_Control.Command = PRN_IDLE_REQ;
** 		PRN_Control.Status = PRN_IDLE;
** 		if (PS2()) {
** 			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM;
** 		}
** 	}
** 	SYB_LifeMonitor.PrintCount++;
#else
	/* HINOKI */
	/* Paper.StepsFromPrinting = 0; */
	Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
	Paper.Position = PAPER_POS_MOVE_TO_CUT;
	/* Paper.StepsToCutPosFromPlaten = 0; */
	StopRxMotor();
	ChangeRxMotorPhase();

	/* プリントタイプがプリンター受信以外の場合はページカット終了を待ちます */
	if (PrinterUseMode != PRINT_RXPRINT) {
		CMN_DisableInterrupt();

#if (0)
** 		/* イベント空振りフラグの見方を変更します。
** 		** by O.Kimoto 1999/02/18
** 		*/
** 		if (!(PrinterEventStatus & PRT_EVT_CUT_ON)) {
** 			wai_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_CUT_ON to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
** 		}
#else
		if (!PrinterEventStatus) {
			wai_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_READY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
		}
		PrinterEventStatus = 0; /* 1999/05/07 by T.Soneoka イベントを受け取ったら初期化します */
#endif

		PrinterEventStatus &= ~PRT_EVT_CUT_ON;
		PrinterEventStatus &= ~PRT_EVT_ERROR;	/*  By O.Kimoto 1998/12/07 */
		CMN_EnableInterrupt();

		if (PRN_PrintErrorHaltRequest() == OK) {	/* プリンターエラーチェック */

#if (0) /* カッタ不良チェック追加 1999/04/13 by T.Soneoka */
**			ExecCutter();
#else
			if (ExecCutter() == NG) {
				PrinterError |= PRT_ERROR_CUT_ERROR;
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_CUTTER_ERROR;
				return (NG);
			}
#endif

#if (0)
** 			/* EndMark4
** 			** 印字中にすでにエンドマークを検出している場合は、PS2を見るのと変更でフラグもチェックします。
** 			** by O.Kimoto 1999/03/04
** 			*/
** 			/* Endmark2 By O.Kimoto 1999/02/11 */
** 			if (!QueryPs2On()) {
#else
 #if defined(SATSUKI2)	/* エンドマークチェック用ＰＳ２チェックの追加  2003/10/23 */
			if ((!EndMarkPS2Cehck()) || (EndMarkDetect == TRUE)) {
 #else
			if ((!QueryPs2On()) || (EndMarkDetect == TRUE)) {
 #endif	/* End of defined(SATSUKI2) */
#endif

				EndMarkDetect = TRUE;
				if ((SYB_MaintenanceSwitch[MNT_SW_H8] & ENDMARK_DETECT_ERROR) == ENDMARK_DETECT_ERROR) {

#if (0)
** 					/* EndMark検出時、いまカットした分は排出するように変更
** 					** by O.Kimoto 1999/02/19
** 					*/
** 					PrinterError |= PRT_ERROR_JAM;
** 					return(NG);
#else
					Paper.Route = ROUTE_PRINTING_TO_READY;
					Paper.Position = PAPER_POS_FEED_OUT;
					Paper.StepsFeedOut = 0;
					ChangeRxMotorPhase();

					CMN_DisableInterrupt();
					if (!PrinterEventStatus) {
						wai_evt(EVT_PRT_IMAGE);
					}
					PrinterEventStatus = 0; /* 1999/05/07 by T.Soneoka イベントを受け取ったら初期化します */
					PrinterEventStatus &= ~PRT_EVT_DOC_READY_COMPLETE;
					PrinterEventStatus &= ~PRT_EVT_ERROR;

#if (0)
** 					/* エンドマーク検出とＪＡＭの区別ができないので、エラーメッセージ変更
** 					** by O.Kimoto 1999/03/09
** 					*/
** 					PrinterError |= PRT_ERROR_NO_PAPER;
** 					SYS_MachineStatus[SYS_PRINTER_STATUS1] |=SYS_PRINTER_NO_PAPER; /* マシーンステータスもあわせてセットします。 by O.Kimoto 1999/02/24 */
#else
					PrinterError |= PRT_ERROR_JAM;
					SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM;
#endif

					CMN_EnableInterrupt();
					return(NG);
#endif

				}
			}

/*
** 紙搬送変更 1999/04/13 by T.Soneoka
*/
#if (0)
**			Paper.Route = ROUTE_NONE;
**			/* Add 2 line 1999/1/14 by T.Soneoka */
**			backward_step_error = BackWardStepErrorFromReady;
**			Paper.BackWardStepsFromFeedOut = 0;
**			Paper.Position = PAPER_POS_MOVE_TO_PS2;
**
**			PaperMoveCount = (WORD)(COUNT_CUTTER_TO_PS2 + SYB_MaintenanceSwitch[MNT_SW_H9]);	/* 12.2mm + 3.5mm *//* EndMark By O.Kimoto 1999/02/09 */
**
**			ChangeRxMotorPhase();
**
**			CMN_DisableInterrupt();
**
**#if (0)
**** 		/* イベント空振りフラグの見方を変更します。
**** 		** by O.Kimoto 1999/02/18
**** 		*/
**** 			if(!(PrinterEventStatus & PRT_EVT_DOC_PRINT_POS)) {
**** 				wai_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_READY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
**** 			}
**#else
**			if(!PrinterEventStatus) {
**				wai_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_READY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
**			}
**#endif
**
**			PrinterEventStatus &= ~PRT_EVT_DOC_PRINT_POS;
**			PrinterEventStatus &= ~PRT_EVT_ERROR;	/* Add By O.Kimoto 1998/12/07 */
**			CMN_EnableInterrupt();
**			if (PRN_PrintErrorHaltRequest() == NG) {	/* プリンターエラーチェック */
**				return(NG);
**			}
#endif
		}
		else {
			return(NG);	/* ライフモニターは更新しません。by O.Kimoto 1998/12/07 */
		}
	}
	SetPrinterPageCount(PageQ.Size);	/* LifeMonitor */	/* Add by O.Kimoto 1998/12/01 */
	return(OK);
#endif
}


/*************************************************************************
	module		:[記録開始待機位置から記録紙待機位置へ移動]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[void PRN_PrintToStandby(void){}]
	date		:[1998/10/26]
	author		:[木元  修]
*************************************************************************/
void	PRN_PrintToStandby(void)
{
#if (0)
** 	/* SAKAKI */
** 	while ( ( (PRN_Control.Command == PRN_PAGECUT_REQ) || (PRN_Control.Command == PRN_FEED_IN_REQ) )
** 		&& !(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) ) {
** 		wai_tsk(2);
** 	}
** 	PRN_Control.Command = PRN_FEED_OUT_REQ;
** 	PRN_Control.Status = PRN_PAPER_FEED_OUT;
** 	PaperMargin = (UWORD)(SYB_MachineParameter[16]);
** 	if ((PRN_PrintErrorHaltRequest() == OK) && (!PS2())) {
** 		/* 記録紙詰まり等の機械的プリンタエラーが無ければ記録位置から待機位置まで送る(約20mm) */
** 		PrintMotorPhase12();
** 		PrintMotorSpeed(PRINT_200PPS);
** 	   	PrintMotorStepSet(4);
** 		PrintMotor((PRN_STEP_HEAD_TO_STANDBY-PaperMargin+128)/2);
** 		WaitPrintMotorBusy(); /** モーターの終了を待つ */
** 	}
** 	PmenOff();	/** ＲＸモーター励磁ＯＦＦ */
** 	PRN_Control.Command = PRN_IDLE_REQ;
** 	PRN_Control.Status = PRN_IDLE;
#else
	/* HINOKI */
#if (0) /* 最終ページの終了処理をいれます 1998/11/13 by T.Soneoka */
**	Paper.Phase = PAPER_PHASE_PRINT;
**	Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
**	Paper.Position = PAPER_POS_MOVE_TO_READY;
#else
	Paper.Phase = PAPER_PHASE_FEED;
	Paper.Route = ROUTE_PRINTING_TO_READY;	/* 1998/11/12 by T.Soneoka */
	Paper.Position = PAPER_POS_PRINTING_TO_FEED_OUT;
#endif

#if (0)
** 	/* プリンターエラーをチェックする関数が同一内容で関数名違いが２つも在るので、
** 	** １つに統一します。
** 	** by O.Kimoto 1998/12/07
** 	*/
** 	if ((PRN_PrintNocutRequest() == OK) && (!PS2())) [	/* 記録紙詰まり等の機械的プリンタエラーが無ければ記録位置から待機位置まで送る(約20mm) */
#else
	if ((PRN_PrintErrorHaltRequest() == OK) && (!PS2())) {	/* 記録紙詰まり等の機械的プリンタエラーが無ければ記録位置から待機位置まで送る(約20mm) */
#endif
		ChangeRxMotorPhase();
		EnableIntPrinterTimer();

		CMN_DisableInterrupt();

#if (0)
** 		/* イベント空振りフラグの見方を変更します。
** 		** by O.Kimoto 1999/02/18
** 		*/
** 		if (!(PrinterEventStatus & PRT_EVT_DOC_READY_COMPLETE)) {
** 			wai_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_STANDBY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
** 		}
#else
		if (!PrinterEventStatus) {
			wai_evt(EVT_PRT_IMAGE);	/* Change Event EVT_PRT_DOC_POS_STANDBY to EVT_PRT_IMAGE by O.Kimoto 1998/12/25 */
		}
		PrinterEventStatus = 0; /* 1999/05/07 by T.Soneoka イベントを受け取ったら初期化します */
#endif

		PrinterEventStatus &= ~PRT_EVT_ERROR;	/* Add By O.Kimoto 1999/02/18 */
		PrinterEventStatus &= ~PRT_EVT_DOC_READY_COMPLETE;

		/* プリント最終ページでＥｎｄＭａｒｋ検出時、エラーのセットがぬけている
		** by O.Kimoto 1999/03/09
		*/
		if (EndMarkDetect == TRUE) {
			PrinterError |= PRT_ERROR_JAM;

			/* EndMark6 
			** ここでも、エラーステータスを立てるようにします。
			** by O.Kimoto 1999/03/11
			*/
			SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_PAPER_JAM;

		}

		CMN_EnableInterrupt();
	}
#endif
}



/*************************************************************************
	module		:[カット位置から記録紙待機位置へ移動]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[void PRN_CutPosToStandby(void){}]
	date		:[1999/04/13]
	author		:[曽根岡拓]
*************************************************************************/
void	PRN_CutPosToStandbyPos(void)
{
	struct Timer10msEventData_t timer;	/* HINOKIプリント中ループ対策 2002/04/17 by T.Soneoka */
	UWORD	tskno_timer;				/* HINOKIプリント中ループ対策 2002/04/17 by T.Soneoka */
	
	/* HINOKIプリント中ループ対策 2002/04/17 by T.Soneoka */
	EnableIntPrinterTimer();
	timer.Time = 1500;  /* 15秒 */
	timer.Event = EVT_PRT_IMAGE;
	tskno_timer = 0xffff;
	cre_tsk(&tskno_timer, TSK_CMN_WATCHTIMER10MSEVENTTASK, &timer);
	/* ここまで */

	Paper.Route = ROUTE_PRINTING_TO_READY;
	Paper.Position = PAPER_POS_FEED_OUT;
	Paper.StepsFeedOut = 0;
	ChangeRxMotorPhase();

	CMN_DisableInterrupt();
	if (!PrinterEventStatus) {
		wai_evt(EVT_PRT_IMAGE);
	}
	PrinterEventStatus = 0; /* 1999/05/07 by T.Soneoka イベントを受け取ったら初期化します */
	CMN_EnableInterrupt();

	/* HINOKIプリント中ループ対策 2002/04/17 by T.Soneoka */
	if (tskno_timer != 0xffff) {
		del_tsk(&tskno_timer);
	}
	/* ここまで */
	
}

/*************************************************************************
	module		:[カット位置からプリント位置へ移動]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[void PRN_CutPosToStandby(void){}]
	date		:[1999/04/13]
	author		:[曽根岡拓]
*************************************************************************/
void	PRN_CutPosToPrintPos(void)
{
	struct Timer10msEventData_t timer;	/* HINOKIプリント中ループ対策 2002/04/17 by T.Soneoka */
	UWORD	tskno_timer;				/* HINOKIプリント中ループ対策 2002/04/17 by T.Soneoka */
	
	/* HINOKIプリント中ループ対策 2002/04/17 by T.Soneoka */
	EnableIntPrinterTimer();
	timer.Time = 1500;  /* 15秒 */
	timer.Event = EVT_PRT_IMAGE;
	tskno_timer = 0xffff;
	cre_tsk(&tskno_timer, TSK_CMN_WATCHTIMER10MSEVENTTASK, &timer);
	/* ここまで */


	Paper.Route = ROUTE_NONE;
 	Paper.Position = PAPER_POS_MOVE_TO_PS2;
#if defined(SATSUKI2)	/* 壁掛け設定用 追加 by Y.Kano 2003/10/07 */
	if ( CHK_WallHangSetting() ) { /** 壁掛け設定用 */	/* Add by Y.kano 2003/10/06 */
		Paper.StepsFromPs2On = 0;
		Paper.BackWardStepsFromFeedOut = 0;
		backward_step_error = BackWardStepErrorFromReady;
	}
	else
	{
		Paper.BackWardStepsFromFeedOut = 0;
		backward_step_error = BackWardStepErrorFromReady;
	}
#else
	Paper.BackWardStepsFromFeedOut = 0;
	backward_step_error = BackWardStepErrorFromReady;
#endif

/* 移植 by SMuratec K.W.Q 2003/07/29 */
#if defined(SATSUKI2)	/* SATSUKI2の場合は、印字待機位置 PS2から8.5のところ 先端のSTEPに変更 by Y.Kano 2003/07/26 */
	PaperMoveCount = PrintReadySteps;				/* 10mm *//* EndMark By O.Kimoto 1999/02/09 */
#else
	PaperMoveCount = (WORD)(COUNT_CUTTER_TO_PS2 + SYB_MaintenanceSwitch[MNT_SW_H9]);
#endif

	ChangeRxMotorPhase();

	CMN_DisableInterrupt();
	if (!PrinterEventStatus) {
		wai_evt(EVT_PRT_IMAGE);
	}
	PrinterEventStatus = 0; /* 1999/05/07 by T.Soneoka イベントを受け取ったら初期化します */
	CMN_EnableInterrupt();

	/* HINOKIプリント中ループ対策 2002/04/17 by T.Soneoka */
	if (tskno_timer != 0xffff) {
		del_tsk(&tskno_timer);
	}
	/* ここまで */

	if (PRN_PrintErrorHaltRequest() == NG) {	/* プリンターエラーチェック */
		return;
	}
	PrinterEventStatus &= ~PRT_EVT_DOC_PRINT_POS;
	PrinterEventStatus &= ~PRT_EVT_ERROR;
	Paper.Route = ROUTE_NONE;	/* 1998/11/12 by T.Soneoka */
	Paper.Position = PAPER_POS_PRINTING;
}

/*************************************************************************
	module		:[停止要求の有無チェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[COMMON]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[UBYTE PRN_PrintHaltRequest(void){}]
	date		:[1998/10/26]
	author		:[木元  修]
*************************************************************************/
UBYTE	PRN_PrintHaltRequest(void)
{
	if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & (SYS_STOP_IMAGE_PRINT | SYS_STOP_LIST_PRINT)) {
		return(NG);
	}
	return(OK);
}


/*************************************************************************
	module		:[プリンターエラーの有無チェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[COMMON]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[UBYTE PRN_PrintErrorHaltRequest(void){}]
	date		:[1998/10/26]
	author		:[木元  修]
*************************************************************************/
UBYTE	PRN_PrintErrorHaltRequest(void)
{
	PRN_CheckPrinterError();	/* Add By O.Kimoto 1998/12/04 */
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER) {
		return(NG);
	}
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM) {
		return(NG);
	}
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
		return(NG);
	}

	/* カッターエラーが見れていない！
	** by O.kimoto 1999/03/09
	*/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] &SYS_PRINTER_CUTTER_ERROR) {
		return(NG);
	}

	return(OK);
}


#if (0)
** 	/* プリンターエラーをチェックする関数が同一内容で関数名違いが２つも在るので、
** 	** １つに統一します。
** 	** by O.Kimoto 1998/12/07
** 	*/
** /*************************************************************************
** 	module		:[記録紙をカットして良いかどうかの判断]
** 	function	:[
** 		1.
** 	]
** 	return		:[]
** 	common		:[]
** 	condition	:[]
** 	comment		:[COMMON]
** 	machine		:[V53]
** 	language	:[CH38(V.2.0B)]
** 	keyword		:[PRN]
** 	ProtoType	:[UBYTE PRN_PrintNocutRequest(void){}]
** 	date		:[1998/10/26]
** 	author		:[木元  修]
** *************************************************************************/
** UBYTE	PRN_PrintNocutRequest(void)
** {
** 	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER) {
** 		return(NG);
** 	}
** 	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM) {
** 		return(NG);
** 	}
** 	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
** 		return(NG);
** 	}
** 	return(OK);
** }
#endif


/*************************************************************************
	module		:[プリンターエラーが発生しているかどうかのチェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[CH38(V.2.0B)]
	keyword		:[PRN]
	ProtoType	:[void PRN_CheckPrinterError(void){}]
	date		:[1998/12/04]
	author		:[木元  修]
*************************************************************************/
void PRN_CheckPrinterError(void)
{
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
	}
}


