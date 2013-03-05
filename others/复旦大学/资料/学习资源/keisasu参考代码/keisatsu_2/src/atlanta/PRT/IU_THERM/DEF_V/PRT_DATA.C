/*
 *	@(#)$Id: PRT_DATA.C,v 1.1.1.1 2005/04/04 04:24:06 mi93007 Exp $
 *	FileName:	/home2/prj/Eva/Src/inc/prt_data.h
 *	Create:	Mon Mar 16 11:38:26 1998	by	ishiyama
 *	Description:
 *		Printer Data
 *	Change Log:
 *		
 */
#ifndef PRT_DATA_H
	#define PRT_DATA_H

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\define\scn_def.h"
 #else
#include "\src\atlanta\hinoki\define\scn_def.h"
 #endif
#include "\src\atlanta\prt\iu_therm\define\prt_drv.h"
#include "\src\atlanta\prt\iu_therm\define\prtqueue.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"

/* UBYTE	PrinterStatusBuf = 0; */
/* UBYTE	PrinterStatus[PRT_STATUS_MAX] = {0}; */
UWORD	PrinterError = 0;			/* PRTERROR_* (see Printer.h) */
UWORD	PrePrinterError = 0;
UWORD	PrintImageLine = 0;
/* UWORD	*PrintImageStartPtr = 0; */
/* BOOL	InhibitScanPrinterStatus = 0; */
/* BOOL	EnablePrinterPause = 0; */			/* Pause コマンドを休止中にださないため */

/* struct PageBlockAlloc	PageMemBlock[NUM_OF_PAGE_MEMORY_BLOCK] = {0}; */

UDWORD	CurrentVReductionPattern = 0;	/* 副走査方向間引きパターン */
UDWORD	VRductionBit = 0;			/* 副走査方向間引きチェックビット */
BYTE	ThinOutCount = 0;				/* 副走査方向引きのためのカウンタ */
/* UBYTE	ListVMode = 0; */				/* List Print 副操作方向モード(SYS_NORMAL,SYS_FINE...) */

struct CassetteAttribute	CassetteAttr = {0};

/* BOOL	ExistCassetteUnitFlag = 0; */		/* カセットユニットの有無 */
/* BOOL	PrinterCoverOpened = 0; */			/* Printer Cover が開いたことを記憶 */

/* UDWORD	PrinterDmaRestSize = 0; */		/* Printer DMA 残りサイズ */
BOOL	PrinterDmaPermission = 0;		/* Printer DMA 許可 */

BOOL	EnablePrinterTimerInterrupt = 0; /* Printer Timer 割込み許可/禁止 */
UBYTE	StrobeTime = 0;				/* Current Strobe Time */
UBYTE	ContinuousStrobeCount = 0;	/* 連続印可時間(5msec毎にCountup) */
BYTE	PrinterRewriteCount = 0;		/* リライトカウント */

struct PaperAtr Paper = {0};
BOOL	Request1StepRxMotor = 0;		/* Rx Motor 1 step request in Print Phase */
BOOL	PrinterCloseRequest = 0;		/* Printer Close Request */
BOOL	PrinterCloseRequestReal = 0;	/* Printer Close Request for Interrupt */
BOOL	PrintBufferClearMode = 0;

/* BOOL	CookedRibbon = 0; */				/* Ink Ribbon Cooked Mode(チャタリング対策済み) */
BOOL	CookedPs1 = 0;					/* PS1 Cooked Mode(チャタリング対策済み) */
BOOL	CookedPs2 = 0;					/* PS2 Cooked Mode(チャタリング対策済み) */
/* BOOL	CookedPs3 = 0; */					/* PS3 Cooked Mode(チャタリング対策済み) */
BOOL	CookedInterLock4Print = 0;		/* InterLock Cooked Mode(チャタリング対策済み) */
UBYTE	Ps1CookCounter = 0;			/* PS1 チャタリング防止用カウンタ */
UBYTE	Ps2CookCounter = 0;			/* PS2 チャタリング防止用カウンタ */
/* UBYTE	Ps3CookCounter = 0; */			/* PS3 チャタリング防止用カウンタ */
UBYTE	InterLock4PrintCookCounter = 0;	/* InterLock チャタリング防止用カウンタ */

/* for Rx Motor */
BOOL	EnableIntRxMotor = 0;			/* Rx Motor 用割込み処理イネーブル */
const struct MotorCtrl	*RxMotorCtrlPtr = {0}; /* Rx Motor Control Pointer */
const struct ThroughUpDown *RxMotorSpeedPtr = {0}; /* Rx Motor Speed Table for ThroughUp/Down */
BYTE	RxMotorTransCount = 0;			/* Rx Motor State Transision Counter */
BYTE	RxMotorRequest = 0;				/* MOTOR_SPEED_* (motor.h) */
/* WORD	StretchCount = 0; */				/* Stretch Ink Ribbon Counter  */

/* for Analog Fucntion Checker */
/* UBYTE	PrinterTestMode = 0; */		/* Printer Test Mode(see prt_drv.h PRINTER_TEST_MODE_*) */

/* for Copy */
BOOL	IsPrintFinish = 0;		/* Scan Finished for Printer */

BOOL	PrinterStopProcess = 0;			/* Printer が StopSwitch による終了処理を実行中 */

/* for Memory Control */
#if (0)	/* 1998/10/05 by T.Soneoka */
**struct IndexTableReadData	MemoryIndex4Print = {0};/* Memory Index for Print */
**struct PixExecData	ExecBlock4Print = {0}; /* Memory Attribute for Print */
#endif
struct MEM_IndexData_t	MemoryIndex4Print = {0};/* Memory Index for Print */
struct MEM_ExecData_t	ExecBlock4Print = {0}; /* Memory Attribute for Print */

UBYTE PrinterEventStatus = 0;

UWORD	tskno_PRN_WatchPrinter = 0;
/* UWORD	tskno_PRN_PrinterReset = 0;	未使用 by O.Kimoto 1998/10/21 */
/*UWORD	tskno_PRN_AddIndexQueue = 0; 未使用 by O.Kimoto 1998/10/22 */
UWORD	tskno_PRN_MakeImage = 0;
UWORD	tskno_PRN_PrintImage = 0;
/* UWORD	tskno_PRN_SetPrinterPause = 0; 未使用 by O.Kimoto 1998/10/21 */

/* UWORD	tskno_PRN_MakeImageDec = 0;  未使用 By O.Kimoto 1998/10/21 */
/* UWORD	tskno_PRN_MakeImageList = 0; 未使用 By O.Kimoto 1998/10/21 */
UWORD	tskno_PRN_MakeImageDirect = 0;
/* UWORD	tskno_PRN_MakeImageListDec = 0; 未使用 By O.Kimoto 1998/10/21 */
/* UWORD	tskno_PRN_WaitPrinterReady = 0; 未使用 by O.Kimoto 1998/10/21 */
UWORD	tskno_PRN_PrintImageEvent = 0;
/* UWORD	tskno_PRN_MakePrintExitTiming[2] = {0}; 未使用 by O.Kimoto 1998/10/21 */
/* UWORD	tskno_PRN_SetPrinterPause = 0; 未使用 by O.Kimoto 1998/10/21 */
/* UWORD	tskno_PRN_WaitPrinterRead = 0; 未使用 by O.Kimoto 1998/10/21 */
UWORD	tskno_PRN_WatchPrinter1Sec = 0;
UWORD	tskno_PRN_PrintDataTransTask = 0;

/* UWORD	PrintBufferWriteLine = 0; */
UWORD	PrtDataTrasCount = 0;
UWORD	IsEventPrintDataTras = 0;

/* struct PrintPageObject_t	PrintPageObj[NUM_OF_PAGES] = {0}; */
struct PrintPageQElement	PageQ = {0};	/* 大域変数に変更 By O.Kimoto 1998/10/22 */


/* 最終的には、高速ＳＲＡＭにマッピングしてください。*/
#pragma section PRNBUF /* locate section name "DPRNBUF" */
UBYTE	PRN_ImageBuffer1[PRINT_IMAGE_BUF_LINE][PRINT_IMAGE_BUF_SIZE] = {0};	/* 1 LINE ﾌﾟﾘﾝﾄ用ﾋﾞｯﾄｲﾒｰｼﾞﾊﾞｯﾌｧ */
#pragma section

/* プリンターの使用状態を示す変数 */
UBYTE PrinterUseMode = 0;

UBYTE PrintDtc = 0;

UBYTE PrinterSkipCount = 0;

UWORD	ThermistorValue = 0;

UBYTE	IsPrintWaitToPrtBufFul = 0;

UBYTE	HeadMaker = 0;

UBYTE	EnablePrintDataMake = 0; /* プリントデータ作成開始許可 1998/12/15 by T.Soneoka */

UBYTE	ExecPrintOnTiming = 0;	/* 1998/12/16 by T.Soneoka */
UWORD	PrintTiming = 0;		/* 1998/12/16 by T.Soneoka */

UBYTE	PreHeatInsertForKyocera = 0; /* 京セラＴＰＨ不具合対応1998/12/21 by T.Soneoka */

WORD	backward_step_error = 0;	/* 1999/1/14 by T.Soneoka */

UBYTE	PBRDY_Count = 0;			/* ＧＩＮＴがとまる対策  1999/01/27 by T.Soneoka */

WORD	PaperMoveCount = 0;			/* EndMark By O.Kimoto 1999/02/09 */
UBYTE	EndMarkDetect = 0;			/* EndMark2 By O.Kimoto 1999/02/11 */

UBYTE	IsCutBack = 0;				/* Ｂ４記録紙カット時、記録紙の端がいたむ不具合  1999/11/22 by T.Soneoka */

/* SATSUKI2 追加 start by Y.Kano 2003/06/26 */
#if defined(SATSUKI2)
struct	PRN_Control_def	PRN_Control = {0};
UBYTE	AD_PS2_StoreValue = 0;			/* 経年変化対応イニシャルカット前（カット直前）Ａ／Ｄ取込み値 by Y.Kano 2003/10/31 */
/*UBYTE	AD_PS2_Value1 = 0;*/			/* 経年変化対応イニシャルカット前（モータ送り直前）Ａ／Ｄ読取り値 by Y.Kano 2003/10/20 */
/*UBYTE	AD_PS2_Value2 = 0;*/			/* 経年変化対応イニシャルカット前（カット直前）Ａ／Ｄ読取り値 by Y.Kano 2003/10/20 */
/*UBYTE	AD_PS2_AveValue = 0;*/		/* 経年変化対応平均値 by Y.Kano 2003/10/20 */
#endif
/* SATSUKI2 追加 end   by Y.Kano 2003/06/24 */

#if defined(HINOKI2) || defined (HINOKI3)	/* ＰＳ２の平均レベルを算出 by Y.kano 2004/03/01 				*/
UBYTE	PS2_Vp_Count = 0;				/* ＰＳ２：Ｖｐ平均レベル算出用カウンタ 		*/
UBYTE	PS2_Vb_Value = 0;				/* ＰＳ２：Ｖｂ（記録紙無しレベル）Ａ／Ｄ変換値	*/
UWORD	PS2_Vp_Value = 0;				/* ＰＳ２：Ｖｐ平均レベル算出用バッファ 		*/
UBYTE	PS2_Count = 0;					/* ＰＳ２：Ｖｐ平均レベル算出用ワークカウンタ 	*/
UBYTE	SensorRetryCount = 0;			/* ＰＳ２閾値再セットカウンタ by Y.Kano 2004/04/06 */
  #if (0)	/* ＰＳ２自動調整機能 削除 by Y.Kano 2004/04/05 */
UBYTE	PS2_SensorStatus = 0;			/* ＰＳ２のスライスレベルステータス 			*/
  #endif
 #if (PRO_PAPER_AD_SENSOR_INIT == DISABLE)
UBYTE	PrtBackStepPS2Flag = FALSE;		/* ＰＳ２自動調整不具合対応 by Y.kano 2004/12/06 */
 #endif
#endif

#endif /* PRT_DATA_H */
