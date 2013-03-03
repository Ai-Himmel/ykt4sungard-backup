/*
 *	@(#)$Id: PRT_DATA.H,v 1.1.1.1 2005/04/04 04:24:06 mi93007 Exp $
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
 #if defined(SATSUKI2)
#include "\src\atlanta\satsuki2\define\scn_def.h"
 #else
#include "\src\atlanta\hinoki\define\scn_def.h"
 #endif
#include "\src\atlanta\prt\iu_therm\define\prt_drv.h"
#include "\src\atlanta\prt\iu_therm\define\prtqueue.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"



/* extern UBYTE	PrinterStatusBuf; */
/* extern UBYTE	PrinterStatus[PRT_STATUS_MAX]; */
extern UWORD	PrinterError;			/* PRTERROR_* (see Printer.h) */
extern UWORD	PrePrinterError;
extern UWORD	PrintImageLine;
/* extern UWORD	*PrintImageStartPtr; */
/* extern BOOL	InhibitScanPrinterStatus; */
/* extern BOOL	EnablePrinterPause; */			/* Pause コマンドを休止中にださないため */

/* extern struct PageBlockAlloc	PageMemBlock[NUM_OF_PAGE_MEMORY_BLOCK]; */

extern UDWORD	CurrentVReductionPattern;	/* 副走査方向間引きパターン */
extern UDWORD	VRductionBit;			/* 副走査方向間引きチェックビット */
extern BYTE	ThinOutCount;				/* 副走査方向引きのためのカウンタ */
/* extern UBYTE	ListVMode; */				/* List Print 副操作方向モード(SYS_NORMAL,SYS_FINE...) */

extern struct CassetteAttribute	CassetteAttr;

/* extern BOOL	ExistCassetteUnitFlag; */		/* カセットユニットの有無 */
/* extern BOOL	PrinterCoverOpened; */			/* Printer Cover が開いたことを記憶 */

/* extern UDWORD	PrinterDmaRestSize; */		/* Printer DMA 残りサイズ */
extern BOOL	PrinterDmaPermission;		/* Printer DMA 許可 */

extern BOOL	EnablePrinterTimerInterrupt; /* Printer Timer 割込み許可/禁止 */
extern UBYTE	StrobeTime;				/* Current Strobe Time */
extern UBYTE	ContinuousStrobeCount;	/* 連続印可時間(5msec毎にCountup) */
extern BYTE	PrinterRewriteCount;		/* リライトカウント */


extern struct PaperAtr Paper;
extern BOOL	Request1StepRxMotor;		/* Rx Motor 1 step request in Print Phase */
extern BOOL	PrinterCloseRequest;		/* Printer Close Request */
extern BOOL	PrinterCloseRequestReal;	/* Printer Close Request for Interrupt */
extern BOOL	PrintBufferClearMode;

/* extern BOOL	CookedRibbon; */				/* Ink Ribbon Cooked Mode(チャタリング対策済み) */
extern BOOL	CookedPs1;					/* PS1 Cooked Mode(チャタリング対策済み) */
extern BOOL	CookedPs2;					/* PS2 Cooked Mode(チャタリング対策済み) */
/* extern BOOL	CookedPs3; */					/* PS3 Cooked Mode(チャタリング対策済み) */
extern BOOL	CookedInterLock4Print;		/* InterLock Cooked Mode(チャタリング対策済み) */
extern UBYTE	Ps1CookCounter;			/* PS1 チャタリング防止用カウンタ */
extern UBYTE	Ps2CookCounter;			/* PS2 チャタリング防止用カウンタ */
/* extern UBYTE	Ps3CookCounter; */			/* PS3 チャタリング防止用カウンタ */
extern UBYTE	InterLock4PrintCookCounter;	/* InterLock チャタリング防止用カウンタ */

/* for Rx Motor */
extern BOOL	EnableIntRxMotor;			/* Rx Motor 用割込み処理イネーブル */
extern const struct MotorCtrl	*RxMotorCtrlPtr; /* Rx Motor Control Pointer */
extern const struct ThroughUpDown *RxMotorSpeedPtr; /* Rx Motor Speed Table for ThroughUp/Down */
extern BYTE	RxMotorTransCount;			/* Rx Motor State Transision Counter */
extern BYTE	RxMotorRequest;				/* MOTOR_SPEED_* (motor.h) */
/* extern WORD	StretchCount; */				/* Stretch Ink Ribbon Counter  */

/* for Analog Fucntion Checker */
/* extern UBYTE	PrinterTestMode; */		/* Printer Test Mode(see prt_drv.h PRINTER_TEST_MODE_*) */

/* for Copy */
extern BOOL	IsPrintFinish;		/* Scan Finished for Printer */

extern BOOL	PrinterStopProcess;			/* Printer が StopSwitch による終了処理を実行中 */

/* for Memory Control */
#if (0)	/* 1998/10/05 by T.Soneoka */
**struct IndexTableReadData	MemoryIndex4Print;/* Memory Index for Print */
**struct PixExecData	ExecBlock4Print; /* Memory Attribute for Print */
#endif
extern struct MEM_IndexData_t	MemoryIndex4Print;/* Memory Index for Print */
extern struct MEM_ExecData_t	ExecBlock4Print; /* Memory Attribute for Print */

extern UBYTE PrinterEventStatus;

extern UWORD	tskno_PRN_WatchPrinter;
/* extern UWORD	tskno_PRN_PrinterReset; 未使用 by O.Kimoto 1998/10/21 */
/* extern UWORD	tskno_PRN_AddIndexQueue; 未使用 By O.Kimoto 1998/10/22 */
extern UWORD	tskno_PRN_MakeImage;
extern UWORD	tskno_PRN_PrintImage;
/* extern UWORD	tskno_PRN_SetPrinterPause; 未使用 by O.Kimoto 1998/10/21 */

/* extern UWORD	tskno_PRN_MakeImageDec;  未使用 By O.Kimoto 1998/10/21 */
/* extern UWORD	tskno_PRN_MakeImageList; 未使用 By O.Kimoto 1998/10/21 */
extern UWORD	tskno_PRN_MakeImageDirect;
/* extern UWORD	tskno_PRN_MakeImageListDec; 未使用 By O.Kimoto 1998/10/21 */
/* extern UWORD	tskno_PRN_WaitPrinterReady; 未使用 by O.Kimoto 1998/10/21 */
extern UWORD	tskno_PRN_PrintImageEvent;
/* extern UWORD	tskno_PRN_MakePrintExitTiming[2]; 未使用 by O.Kimoto 1998/10/21 */
/* extern UWORD	tskno_PRN_SetPrinterPause; 未使用 by O.Kimoto 1998/10/21 */
/* extern UWORD	tskno_PRN_WaitPrinterRead; 未使用 by O.Kimoto 1998/10/21 */
extern UWORD	tskno_PRN_WatchPrinter1Sec;
extern UWORD	tskno_PRN_PrintDataTransTask;

extern UBYTE	PRN_ImageBuffer1[PRINT_IMAGE_BUF_LINE][PRINT_IMAGE_BUF_SIZE];	/* 1 LINE ﾌﾟﾘﾝﾄ用ﾋﾞｯﾄｲﾒｰｼﾞﾊﾞｯﾌｧ */

/* extern UWORD	PrintBufferWriteLine; */
extern UWORD	PrtDataTrasCount;
extern UWORD	IsEventPrintDataTras;

/* extern struct PrintPageObject_t	PrintPageObj[NUM_OF_PAGES]; */
extern struct PrintPageQElement	PageQ;	/* 大域変数に変更 By O.Kimoto 1998/10/22 */

/* プリンターの使用状態を示す変数 */
extern UBYTE PrinterUseMode;

extern UBYTE PrintDtc;

extern UBYTE PrinterSkipCount;

extern UWORD	ThermistorValue;

extern UBYTE	IsPrintWaitToPrtBufFul;

extern UBYTE	HeadMaker;

extern UBYTE	EnablePrintDataMake; /* プリントデータ作成開始許可 1998/12/15 by T.Soneoka */

extern UBYTE	ExecPrintOnTiming;	/* 1998/12/16 by T.Soneoka */
extern UWORD	PrintTiming;		/* 1998/12/16 by T.Soneoka */

extern UBYTE	PreHeatInsertForKyocera; /* 京セラＴＰＨ不具合対応1998/12/21 by T.Soneoka */

extern WORD	backward_step_error;	/* 1999/1/14 by T.Soneoka */

extern UBYTE	PBRDY_Count;			/* ＧＩＮＴがとまる対策  1999/01/27 by T.Soneoka */

extern WORD	PaperMoveCount;			/* EndMark By O.Kimoto 1999/02/09 */

extern UBYTE	EndMarkDetect;		/* EndMark2 By O.Kimoto 1999/02/11 */

extern UBYTE	IsCutBack;			/* Ｂ４記録紙カット時、記録紙の端がいたむ不具合  1999/11/22 by T.Soneoka */

/* SATSUKI2 追加 start by Y.Kano 2003/06/24 */
#if defined(SATSUKI2)
extern	struct	PRN_Control_def	PRN_Control;
extern	UBYTE	AD_PS2_StoreValue;		/* 経年変化対応イニシャルカット前（モータ送り直前）Ａ／Ｄ取込み値 by Y.Kano 2003/10/31 */
/*extern	UBYTE	AD_PS2_Value1;*/		/* 経年変化対応イニシャルカット前（モータ送り直前）Ａ／Ｄ読取り値 by Y.Kano 2003/10/20 */
/*extern	UBYTE	AD_PS2_Value2;*/		/* 経年変化対応イニシャルカット前（カット直前）Ａ／Ｄ読取り値 by Y.Kano 2003/10/20 */
/*extern	UBYTE	AD_PS2_AveValue;*/	/* 経年変化対応平均値 by Y.Kano 2003/10/20 */
#endif
/* SATSUKI2 追加 end   by Y.Kano 2003/06/24 */

#if defined(HINOKI2) || defined (HINOKI3)	/* ＰＳ２の平均レベルを算出 by Y.kano 2004/03/01 					*/
extern UBYTE	PS2_Vp_Count;				/* ＰＳ２：Ｖｐ平均レベル算出用カウンタ 		*/
extern UBYTE	PS2_Vb_Value;				/* ＰＳ２：Ｖｂ（記録紙無しレベル）Ａ／Ｄ変換値	*/
extern UWORD	PS2_Vp_Value;				/* ＰＳ２：Ｖｐ平均レベル算出用バッファ 		*/
extern UBYTE	PS2_Count;					/* ＰＳ２：Ｖｐ平均レベル算出用ワークカウンタ 	*/
extern UBYTE	SensorRetryCount;			/* ＰＳ２閾値再セットカウンタ by Y.Kano 2004/04/06 */
  #if (0)	/* ＰＳ２自動調整機能 削除 by Y.Kano 2004/04/05 */
extern UBYTE	PS2_SensorStatus;			/* ＰＳ２のスライスレベルステータス 			*/
  #endif
 #if (PRO_PAPER_AD_SENSOR_INIT == DISABLE)
extern UBYTE	PrtBackStepPS2Flag;			/* ＰＳ２自動調整不具合対応 by Y.kano 2004/12/06 */
 #endif
#endif

#endif
