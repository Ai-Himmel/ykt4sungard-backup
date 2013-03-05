/*
 *	@(#)$Id: PRT_INZ.C,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	/mnt/jason/home2/prj/Eva/Src/prt/prt_inz.c
 *	Create:	Fri Mar 27 16:11:05 1998	by	ishiyama
 *	Description:
 *		Initialize Printer Parameters & Create Tasks
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\ext_v\dma_data.h"
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\ext_v\scn_dath.h"
 #else
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
 #endif
/* SATSUKI2 追加 start by Y.Kano 2003/06/24 */
#if defined (SATSUKI2)
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#endif
/* SATSUKI2 追加 end   by Y.Kano 2003/06/24 */
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prn_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"

#if defined(HINOKI2) || defined (HINOKI3)	/* ＰＳ２自動調整機能 by Y.kano 2004/04/05 */
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\hinoki\define\m_param.h"
#include "\src\atlanta\ext_v\ini_tbl.h"
#endif


void	PRN_InitPrinter(void)
{
	UWORD i,j;
	
	PrinterError = 0;
	PrePrinterError = 0;
	PrintImageLine = 0;
	CurrentVReductionPattern = 0;
	VRductionBit = 0;
	ThinOutCount = 0;
	CassetteAttr.PaperSize = 0;
	CassetteAttr.Margin = 0;
	PrinterDmaPermission = 0;
	EnablePrinterTimerInterrupt = 0;
	StrobeTime = 0;
	ContinuousStrobeCount = 0;
	PrinterRewriteCount = 0;
	Paper.Mode = 0;
	Paper.Size = 0;
	Paper.VerticalMode = 0;
	Paper.HolzReduction = 0;
	Paper.VertReduction = 0;
	Paper.RewriteCount = 0;
/* SATSUKI2 PRINTER-CONTROL クリア処理追加 start by Y.Kano 2003/06/24 */
#if defined (SATSUKI2)
	ClearPrinterControlParameter();
#endif
/* SATSUKI2 PRINTER-CONTROL クリア処理追加 end   by Y.Kano 2003/06/24 */
/*
** イニシャルカットを通らないときに、プリント中ループする不具合 1999/03/30 by T.Soneoka
** 下記値で初期化を行います
*/
#if (0)
**	Paper.Position = 0;
**	Paper.Route = 0;
**	Paper.Phase = 0;
#else
	Paper.Position = PAPER_POS_MOVE_TO_PS2;
	Paper.Route = ROUTE_PRINTING_TO_READY;
	Paper.Phase = PAPER_PHASE_READY;
	backward_step_error = BackWardStepError;
#endif
	Paper.TopMargin = 0;
	Paper.BottomMargin = 0;
	Paper.StepsFromDocSet = 0;
	Paper.StepsFeedOut = 0;
	Paper.BackWardStepsFromFeedOut = 0;
	Paper.StepsFromPs2On = 0;
	Paper.StepsFromPrinting = 0;
	Paper.StepsToCutPosFromPlaten = 0;
	Request1StepRxMotor = 0;
	PrinterCloseRequest = 0;
	PrinterCloseRequestReal = 0;
	PrintBufferClearMode = 0;
	EnableIntRxMotor = 0;
	RxMotorCtrlPtr = 0;
	RxMotorSpeedPtr = 0;
	RxMotorTransCount = 0;
	RxMotorRequest = 0;
	IsPrintFinish = 0;
	PrinterStopProcess = 0;

	MemoryIndex4Print.No = 0;
	MemoryIndex4Print.Page = 0;
	MemoryIndex4Print.Item = 0;
	MemoryIndex4Print.BoxNumber = 0;

	ExecBlock4Print.IndexNo1 = 0;
	ExecBlock4Print.IndexNo2 = 0;
	ExecBlock4Print.ExecBlockNo = 0;
	ExecBlock4Print.NextBlockNo = 0;

	PrinterEventStatus = 0;
	tskno_PRN_WatchPrinter = 0;
	tskno_PRN_MakeImage = 0;
	tskno_PRN_PrintImage = 0;
	tskno_PRN_MakeImageDirect = 0;
	tskno_PRN_PrintImageEvent = 0;
	tskno_PRN_WatchPrinter1Sec = 0;
	tskno_PRN_PrintDataTransTask = 0;
	PrtDataTrasCount = 0;
	IsEventPrintDataTras = 0;
	PageQ.Mode = 0;
	PageQ.Lines = 0;
	PageQ.Reduction = 0;
	PageQ.Start = 0;
	PageQ.Count = 0;
	PageQ.Size = 0;
	for (i = 0; i < PRINT_IMAGE_BUF_LINE; i++) {
		for (j = 0; j < PRINT_IMAGE_BUF_SIZE; j++) {
			PRN_ImageBuffer1[i][j] = 0x00;
		}
	}
	PrinterUseMode = 0;
	PrinterSkipCount = 0;
	ThermistorValue = 0;
	IsPrintWaitToPrtBufFul = 0;
	HeadMaker = 0;
	EnablePrintDataMake = 0;
	ExecPrintOnTiming = 0;
	PrintTiming = 0;
	PreHeatInsertForKyocera = 0;

	McopyPtr = 0;
	MRxPtr = 0;
	PRN_1PageReceived = 0;
	CutToPrintExecFlag = 0;
	PrinterEndMessage.Item = 0;
	PrinterEndMessage.Message = 0;
	PrinterEndMessage.SubMessage1 = 0;
	PrinterEndMessage.SubMessage2 = 0;
	PrinterEndMessage.SubMessage3 = 0;
	PrinterEndMessage.SubMessage4 = 0;

	PrintIndex.No = 0;
	PrintIndex.Page = 0;
	PrintIndex.Item = 0;
	PrintIndex.BoxNumber = 0;

	PrintExecReadData.IndexNo1 = 0;
	PrintExecReadData.IndexNo2 = 0;
	PrintExecReadData.ExecBlockNo = 0;
	PrintExecReadData.NextBlockNo = 0;

	PRN_PrintModeCount = 0;
	PrintModeCountWork = 0;
	DecodeWaitFlag = 0;
	DecodeWaitCommandFlag = 0;
	PRN_OriginalImageSize = 0;
	PRN_ReductionImageSize = 0;
	PRN_CompPageNo = 0;
	PRN_ReducData.MainReduction = 0;
	PRN_ReducData.CDCMainReduction = 0;
	PRN_ReducData.SubReduction = 0;
	PRN_ReducData.CDCSubReduction = 0;
	PRN_ReducData.CDCSubLineCount = 0;
	PRN_ReducData.GAReduction = 0;
	PRN_ReducData.GA_H_Reduction = 0;
	PRN_ReducData.GA_V_Reduction = 0;
	PRN_ReducData.CDC_H_Reduction = 0;
	PRN_ReducData.CDC_V_Reduction = 0;
	PrintStatusTime[0].Status = 0;
	for (i = 0; i < 7; i++) {
		PrintStatusTime[0].Time[i] = 0;
	};
	PRN_ListHight = 0;
	PRN_ImageBufferOffSet = 0;
	PRN_MemoryOpenResult = 0;

	CookedPs1 = TRUE;					/* PS1 Cooked Mode(チャタリング対策済み) */
	CookedPs2 = FALSE;					/* PS2 Cooked Mode(チャタリング対策済み) */
#if defined(SATSUKI2)	/* SATSUKI2の場合、強制的に’０’をセット by Y.Kano 2003/07/03 */
	CookedInterLock4Print = FALSE;		/* InterLock Cooked Mode(チャタリング対策済み) */
#else
	CookedInterLock4Print = TRUE;		/* InterLock Cooked Mode(チャタリング対策済み) */
#endif
	Ps1CookCounter = Ps1Exist2NonCount;	/* PS1 チャタリング防止用カウンタ */
	Ps2CookCounter = PsChatCount;
	InterLock4PrintCookCounter = PsChatCount; /* InterLock チャタリング防止用カウンタ */
	PrintDtc = TRUE;
	CutToPrintExecFlag = YES /* NO */;	/* Add by O.Kimoto 1999/01/06 */

	AD_PS2_Value = 1;	/* 初期値紙あり 1999/04/13 by T.Soneoka */
/* 追加 start 2003/06/23 by Y.Kano */
#if defined (SATSUKI2) || defined(HINOKI2) || defined (HINOKI3)	/* Add by Y.Kano 2004/01/16 */
	AD_PS1_Value = 1;	/* 初期値紙あり */
	AD_PB4_Value = 1;	/* 初期値Ｂ４ */
#endif
/* 追加 end   2003/06/23 by Y.Kano */

#if defined(HINOKI2) || defined (HINOKI3)	/* ＰＳ２自動調整機能 by Y.kano 2004/04/05 */
	SYB_PS2_SensorStatus = 0;	/* ＰＳ２自動調整機能実行済みフラグ */
	SensorRetryCount = 0;		/* ＰＳ２閾値再セットカウンタ by Y.Kano 2004/04/06 */
 #if (0)	/* イニシャルカット無しの場合、不具合が発生する為、削除します。by Y.Kano 2004/04/06 */
	SYB_MachineParameter[M_PARA_SW_J6] = MachineParameterInitialTable[M_PARA_SW_J6];	/* ＰＳ２センサー 実スライスレベル値（Ｖｓ）	*/
 #endif
 #if (PRO_PAPER_AD_SENSOR_INIT == DISABLE)
	PrtBackStepPS2Flag = FALSE;		/* ＰＳ２自動調整不具合対応 by Y.kano 2004/12/06 */
 #endif
#endif

}

/*
 *	Name:	Initialize Printer Parameters
 *	Create:	Fri Mar 27 16:13:52 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	InzPrinterParameter(void);
 *	Description:
 *		Printer 関連大域変数初期化
 *	Return Value:
 *		void 
*	Change Log:
 *		
 */
void	InzPrinterParameter(void)
{
#if (0) /* スキャナーコピー時紙つまりと表示の不具合の為、コメントアウトします。　by Smuratec 2003/11/21 */
** #if defined(SATSUKI2) /* SATSUKI2 カッター動作初期化 end   by Y.Kano 2003/06/24 */
**	UWORD CutterTimeOutCounter;/* 1999/04/13 by T.Soneoka */
**	CutterTimeOutCounter = 0;	/* 1999/04/13 by T.Soneoka */
** #endif
#endif

	SYS_MachineStatus[SYS_PRINTER_STATUS1] &= (~(SYS_PRINTER_NO_PAPER));
	SYS_MachineStatus[SYS_PRINTER_STATUS2] &= (~(SYS_PRINTER_PAPER_JAM | SYS_PRINTER_HIGH_TEMP | SYS_PRINTER_CUTTER_ERROR));
	SYS_MachineStatus[SYS_COVER_STATUS] &= (~SYS_COVER_PRINTER_OPEN);

	InzPrinter();						/* Priner 関連割込み禁止含む */
	InzThermistorRef();					/* Thermistor Reference 初期化 */
	InzRxMotor();						/* Initialize Rx Motor */

	PrinterDmaPermission = FALSE;
	PrinterError = 0;
	PrePrinterError = 0;
	PrintImageLine = 0;
	StrobeTime = 0;
	IsPrintFinish = FALSE;
	PrinterStopProcess = FALSE;
	Paper.Route = 0;
	Paper.StepsFromDocSet = 0;
	Paper.StepsFeedOut = 0;
	Paper.BackWardStepsFromFeedOut = 0;
	Paper.StepsFromPs2On = 0;
	Paper.StepsFromPrinting = 0;
	Paper.StepsToCutPosFromPlaten = 0;

	PrinterEventStatus = 0;
	Request1StepRxMotor = TRUE;

	PRN_ListHight = 0;	/* キャラクタープリント高さ指示変数 by O.Kimoto 1998/11/07 */ 
	PRN_ImageBufferOffSet = 0;	/* PRN_ImageBuffer1のOffSet By O.Kimoto 1998/11/10 */

	PrinterCloseRequest = 0;
	PrinterSkipCount = 0;

#if (0)
** #if !defined(SATSUKI2) /* カッタ不良チェック追加 1999/04/13 by T.Soneoka */
** **	CheckCutter();
** #else	/* SATSUKI2 カッター動作初期化 end   by Y.Kano 2003/06/24 */
** 	if (!CHK_WallHangSetting()) { /** 壁掛け設定用でない時 */	/* Add by Y.kano 2003/10/03 */
** 		if (CutterPosition() == CUTTER_BUSY) {	/* カッターが待機位置にあるかチェックする */
** 			CutterOn();	/* カッターが待機位置にないときはカッター動作させてカッターを待機位置に置く */
** 			while (PRN_Control.CutterBusy) {	/* カッター動作終了待ち */
** 				wai_tsk(2);	/* 20ms */
** 			}
** 		}
** 	}
** #endif
** /* SATSUKI2 カッター動作初期化 end   by Y.Kano 2003/06/24 */
** /* SATSUKI2では使用せず start by Y.Kano 2003/06/24 */
** #if !defined(SATSUKI2) /* SATSUKI2以外 */
** 	if (CheckCutter() == NG) {
** 		PrinterError |= PRT_ERROR_CUT_ERROR;
** 		SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_CUTTER_ERROR;
** 	}
** /* SATSUKI2では使用せず end   by Y.Kano 2003/06/24 */
** #endif
#else
 #if (0) /* カッタ不良チェック追加 1999/04/13 by T.Soneoka */
**	CheckCutter();
 #else
  #if defined(SATSUKI2) /* SATSUKI2 カッター動作初期化 end   by Y.Kano 2003/06/24 */
	if (!CHK_WallHangSetting()) { /** 壁掛け設定用でない時 */	/* Add by Y.kano 2003/10/03 */
		if (CutterPosition() == CUTTER_BUSY) {	/* カッターが待機位置にあるかチェックする */
			PC_24V_On();									 /* 24V ON 追加 by Y.kano 2003/12/16 */
			CutterOn();	/* カッターが待機位置にないときはカッター動作させてカッターを待機位置に置く */
			while (PRN_Control.CutterBusy) {	/* カッター動作終了待ち */
#if (0) /* スキャナーコピー時紙つまりと表示の不具合の為、コメントアウトします。　by Smuratec 2003/11/21 */
**				CutterTimeOutCounter++;
**				if (CutterTimeOutCounter > 100) {
**					PrinterError |= PRT_ERROR_CUT_ERROR;
**					SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_CUTTER_ERROR;
**					PRN_Control.CutterBusy = 0;
**				}
#endif
				wai_tsk(2);	/* 20ms */
			}
		}
	}
	PC_24V_Off();		/* 24V OFF 追加 by Y.kano 2003/12/16 */
  #else
	if (CheckCutter() == NG) {
		PrinterError |= PRT_ERROR_CUT_ERROR;
		SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_CUTTER_ERROR;
	}
  #endif
 #endif
#endif


	IsPrintWaitToPrtBufFul = 0;

	/*
	** 京セラＴＰＨ対応
	** リアルタイムコピー時のＦｉｎｅだけを処理することになったので、SCN_Init()の中でセットするようにします
	** 電源Ｏｎ直後に行われます
	** 1999/03/15 追加 by T.Soneoka
	*/
#if (0)
*:	/* 1998/12/03 by T.Soneoka */
*:	HeadMaker = HEAD_ROHM;
*:	if (ThermalHeadMaker()) {
*:		HeadMaker = HEAD_KYOCERA;
*:	}
#endif

	/* 1998/12/8 by T.Soneoka */
	DMA_RequestMask(DMA_GATEARRAYWRITE_CH);
	PrintDtc = TRUE;
	DtcPermission = FALSE;

	EnablePrintDataMake = FALSE; /* プリントデータ作成開始許可 1998/12/15 by T.Soneoka */

	/* 1998/12/16 by T.Soneoka */
	PrintTiming = PRINT_TIMING_MIN/2;
	ExecPrintOnTiming = PrintThoughUpTable[PrintTiming];

	PreHeatInsertForKyocera = TRUE; /* 京セラＴＰＨ不具合対応1998/12/21 by T.Soneoka */

	PBRDY_Count = 0;			/* ＧＩＮＴがとまる対策  1999/01/27 by T.Soneoka */

	PaperMoveCount = 0;			/* 0.0mm *//* EndMark By O.Kimoto 1999/02/09 */

	EndMarkDetect = FALSE;		/* EndMark2 By O.Kimoto 1999/02/11 */

	InzPrtImageBufLine();	/* 1999/03/03 by T.Soneoka */

	IsCutBack = 0;				/* Ｂ４記録紙カット時、記録紙の端がいたむ不具合  1999/11/22 by T.Soneoka */

#if defined(HINOKI2) || defined (HINOKI3)	/* ＰＳ２の実閾値を算出する為のフラグ等のクリア by Y.kano 2004/03/01 */
	PS2_Vp_Value = 0;
	PS2_Vb_Value = 0;
	PS2_Vp_Count = 0;
	PS2_Count = 0;
#endif

}

/*
 *	Name:	Create Printer Tasks
 *	Create:	Mon Mar 23 16:28:45 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prn_drv.h"
 *		void	CreatePrinterTasks(void);
 *	Description:
 *		常駐するタスクを起動
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	InzPrinterTaskNo(void)
{
	tskno_PRN_PrintImage		= 0xffff;	/* Print Image Task */

#if (0)	/* for Debug By O.Kimoto 1998/10/22 */
** 	tskno_PRN_MakeImage			= 0xffff;	/* Make Image Task */
** 	tskno_PRN_WatchPrinter		= 0xffff;	/* Watch Printer Task */
#endif

}

/*************************************************************************
	module		:[プリンターコントロール変数クリア]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[PRN]
	date		:[2003/06/25]
	author		:[Y.Kano]
*************************************************************************/
#if defined (SATSUKI2)
void	ClearPrinterControlParameter()
{
	PRN_Control.CutterPhase = 0;           /* 17 :カッターの動作状況             */
	PRN_Control.CutterBusy = 0;            /* 18 :カッター動作中                 */
	PRN_Control.CutterJamCount = 0;        /* 28 :カッタージャム検出カウンタ     */
	PRN_Control.CutterBrakeCount = 0;      /* 30 :カッターブレーキ時間カウンタ   */
}
#endif

/*
 *	Name:	Create Printer Tasks
 *	Create:	Mon Mar 23 16:28:45 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prn_drv.h"
 *		void	CreatePrinterTasks(void);
 *	Description:
 *		常駐するタスクを起動
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	CreatePrinterTasks(void)
{
	cre_tsk(&tskno_PRN_PrintImage, TSK_PRN_PRINTIMAGETASK, (void *)0);	/* Print Image Task */

#if (0) /* For Debug By O.Kimoto 1998/10/22 */
** 	cre_tsk(&tskno_PRN_MakeImage, TSK_PRN_MAKEIMAGETASK, (void *)0);	/* Make Image Task */
** 	cre_tsk(&tskno_PRN_WatchPrinter, TSK_PRN_WATCHPRINTERTASK, (void *)0);	/* Watch Printer Task */
#endif

}

void	DeletePrinterTasks(void)
{
	if (tskno_PRN_PrintImage != 0xffff) {	/* Print Image Task */
		del_tsk(&tskno_PRN_PrintImage);
	}

#if (0)	/* For Deug By O.Kimoto 1998/10/22 */
** 	if (tskno_PRN_MakeImage != 0xffff) {	/* Make Image Task */
** 		del_tsk(&tskno_PRN_MakeImage);
** 	}
** 	if (tskno_PRN_WatchPrinter != 0xffff) {	/* Watch Printer Task */
** 		del_tsk(&tskno_PRN_WatchPrinter);
** 	}
#endif

}

