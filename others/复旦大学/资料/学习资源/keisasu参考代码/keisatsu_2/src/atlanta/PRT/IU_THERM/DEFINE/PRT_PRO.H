/*
 *	@(#)$Id: PRT_PRO.H,v 1.1.1.1 2005/04/04 04:24:06 mi93007 Exp $
 *	FileName:	/home2/prj/Eva/Src/inc/prt_task.h
 *	Create:	Tue Mar 17 10:39:48 1998	by	ishiyama
 *	Description:
 *		Printer Task 関連定義
 *	Change Log:
 *		
 */
#ifndef	PRT_TASK_H
	#define PRT_TASK_H

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\prt\iu_therm\define\prtqueue.h"

/*
 *	Function Prototypes
 */
void	EnableIntPbrdy(void);
void	DisableIntPbrdy(void);
void	PrinterPbreadyInt(void);
void	EnableIntXtop(void);
void	DisableIntXtop(void);
void	PrinterTopInt(void);
void	EnableIntXstwr(void);
void	DisableIntXstwr(void);
void	PrinterStatusInt(void);
void	EnableIntPgend(void);
void	DisableIntPgend(void);
void	PrinterPageEndInt(void);
void	EnableIntPrend(void);
void	DisableIntPrend(void);
void	PrinterPrintEndInt(void);
void	PrinterDmaEndInt(void);
void	EnableIntPrinterTimer(void);
void	DisableIntPrinterTimer(void);
BOOL	QueryPrinterTimerIntEnable(void);
void	PrinterTimerInt(void);

void	InzPrinter(void);
BOOL	OpenPrinter(void);
void	ClosePrinter(void);
BOOL	StartPagePrint(void);
void	StopPagePrint(void);
UWORD	CalcPrintLineCount(UWORD Lines, BYTE Mode);
void	SetPrinterError(UWORD ErrorBit);
void	ClearPrinterError(UWORD ErrorBit);
void	LoadPrinterError(UWORD Error);
UWORD	QueryPrinterError(void);
void	CheckThermalHighTemp(void);
BOOL	QueryCanDoPrint(void);
BOOL	QueryCanDoPrintByArg(UWORD	Error);
void	WaitPrintWork(void);
BOOL	PrintLine(void);
BOOL	PrintListLine(void);
UWORD	QueryImageLines(void);
void	SetImageStartPointer(UWORD	*Addr);
UWORD	*QueryImageStartPointer(void);
void	StartPrint(void);
void	StopPrint(void);
BOOL	QueryPrinterCoverOpen(void);
BOOL	QueryExitPaperJam(void);
UBYTE	CheckSelectedCassette(void);


void	InzPageEndCheck(void);
void	EnablePageEndCheck(void);
void	DisablePageEndCheck(void);
BOOL	CheckPageEnd(void);
BOOL	DetectPageEnd(void);
BOOL	TimeUpPageEnd(void);


void	PRN_InitPrinter(void);
void	InzPrinterParameter(void);
void	InzPrinterTaskNo(void);
void	CreatePrinterTasks(void);
void	DeletePrinterTasks(void);
BOOL	QueryPrinterTaskReady(void);

void	SetPrinterInterface(void);
void	SetPrinterVerticalMode(UBYTE	Mode);
void	SetDataSize(UBYTE	Size);
void	SetHorizontalReduction(UBYTE Reduction);
void	SetVerticalReduction(UBYTE Reduction);
BOOL	QueryPaperWidth216mm(UBYTE	PaperSize);
void	SetPrintWidth(BOOL	w210mm);
void	SetWhiteMaskWidth(UBYTE	Width);
void	SetWhiteMask(BOOL	On);
void	SetWhiteBlackAssign(BOOL	Black1);
WORD	QueryPrinterTopMargin(void);
WORD	QueryPrinterBottomMargin(void);
void	SetPrinterTopMargin(void);
void	SetSelectedCassette(UBYTE Cassette);
void	SelectPrinterDma(void);
UBYTE	CheckPrinterPaperSize(UBYTE Cassette);

UBYTE	QueryPrinterPaperSize(UBYTE Cassette);
UBYTE	QueryCassettePaperSize(void);
UBYTE	QueryMpTrayPaperSize(void);
BOOL	CheckExistCassetteUnit(void);
BOOL	ExistCassetteUnit(void);
BOOL	ExistCassette(void);
BOOL	ExistPrinterPaper(UBYTE Cassette);
BOOL	ExistCassettePaper(void);
BOOL	ExistMpTrayPaper(void);
BOOL	EmptyPrintQueue(void);
UBYTE	QuerySelectedCassette(void);

void	InformPrinterControlerReady(void);
void	SetVirtualVsync(BOOL	On);
void	SetTonerSaveMode(BOOL	Half);
void	SetTonerSave(BOOL	On);
void	SetPrinterSmoothing(UBYTE	Mode);
BOOL	TxPrinterCommand(UBYTE	CommandNo);
BOOL	TxPrinterExpandCommand(UBYTE	CommandNo, UBYTE	Param);
BOOL	TxPrinterCommandOnce(UBYTE	CommandNo);
BOOL	TxPrinterExpandCommandParam(UBYTE	Param);
void	WritePrinterCommand(UBYTE	Command);
BOOL	CheckRxPrinterStatus(UBYTE Data);
UBYTE	MakeOddParity(UBYTE Src);
UBYTE	CheckParity(UBYTE Data);
void	EnableScanPrinterStatus(void);
void	DisableScanPrinterStatus(void);
BOOL	QueryInhibitScanPrinterStatus(void);
void	ScanPrinterStatus(void);
BOOL	ScanPrinterAllStatus(void);
BOOL	IsPrinterPause(void);
void	ReleasePrinterPause(void);
void	SetPrinterPause(void);
void	SetLineCount4PrintEnd(UWORD PageLineCount, UBYTE Reduction, UBYTE Cassette);
void	SetLineCount4PageEnd(UWORD	Lines);
BOOL	QueryPrinterReady(void);
void	SetTransferCurrent(void);
void	SetBiasLevel(void);
BOOL	WaitPrinterWarmup(void);
BOOL	WaitPrinterEPReady(void);
void	ClearMisPrintStatus(void);

UBYTE	FindCassette(struct PrintPageQElement	*PageQPtr);
void	SetPaperAttribute(void);
/*UBYTE	SelectCassette(void); */
void	EvalCassette(UWORD Lines, UWORD Rate, BOOL Copy);
UWORD	CalcReductionLines(UWORD Lines, UBYTE Rate);
UWORD	CalcArcReductionLines(UWORD Lines, UBYTE Rate);
UWORD	QueryPrintableLine(UBYTE	Cassette);
UWORD	QueryPrintableLineByMode(UBYTE	Cassette, UBYTE	Mode, UBYTE	Rate);
UWORD	QueryPrintableLine4List(void);
UWORD	QueryPaperUserMargin(BOOL	Copy);
UWORD	QueryPaperMargin2(void);
UWORD	QueryPaperMargin(UBYTE	CassetteNumber);
UWORD	Mm2Line(UBYTE	Mm);
BOOL	EnablePrintOnePage(UBYTE	CassetteNumber);
UBYTE	QueryCassetteSelected(void);
UBYTE	FindMaxCassetteUp(void);
UBYTE	FindMaxCassetteDown(void);
UBYTE	CalcAutoReduction(UWORD Lines, UBYTE Cassette, BOOL Copy);
UDWORD	CalcPrinterLines2DmaCount(UWORD Lines, UBYTE Mode);
BOOL	QuerySmoothingOn(void);

BOOL	ExistInkRibbonRaw(void);
BOOL	ExistInkRibbon(void);
BOOL	InkRibbonChanged(void);
BOOL	Ps1Raw(void);
BOOL	QueryPs1On(void);
BOOL	Ps1Changed(void);
BOOL	Ps2Raw(void);
BOOL	QueryPs2On(void);
BOOL	Ps2Changed(void);
BOOL	Ps3Raw(void);
BOOL	QueryPs3On(void);
BOOL	Ps3Changed(void);
#if !defined(SATSUKI2)	/* ＲＸインターロック廃止の為、削除 by Y.Kano 2003/07/03 */
BOOL	InterLock4PrintRaw(void);
#endif
BOOL	QueryCloseInterLock4Print(void);
#if !defined(SATSUKI2)	/* ＲＸインターロック廃止の為、削除 by Y.Kano 2003/07/03 */
BOOL	InterLock4PrintChanged(void);
#endif
void	UpdatePaperPosition(void);
BOOL	CheckPrintablePosition(void);
void	Print1Line(void);
void	PritnerRestrobe(void);
BOOL	WatchContinuousStrobe(void);
BOOL	QueryStrobeOn(void);
UBYTE	CalcStrobeTime(void);
UBYTE	CalcPreHeatStrobeTime(void);
BOOL	QueryThinOutLine(void);
void	UpdateThinOutLine(void);
void	ClearPaperSizeError(void);
void	InzPrtImageBuf(void);
void	InzPrtImageBufLine(void); /* 1999/03/03 by T.Soneoka */
void	MakeDummyLine(void);
void	OpenPrtImageBuf4Copy(void);
void	ClosePrtImageBuf4Copy(void);
void	Wait4PrintFinish(void);
void	PutLinePrintPageMem(UBYTE *Source, UBYTE Size);
BOOL	EnableToWritePrtImageBuf(void);
BOOL	EnableToWritePrtImageBuf4Copy(void);
int		GetPrtImageBufWriteLineNo(void);
UWORD	GetPrtImageBufUsedCount(void); /* 1998/12/16 by T.Soneoka */
BOOL	EnableToReadPrtImageBuf(void);
UWORD	*GetWritePtrPrtImageBuf(void);
void	IncPrtImageReadableLine(void);
#if (0) /* 1999/1/5 by T.Soneoka */
**UWORD	*GetReadPtrPrtImageBuf(void);
#else
UBYTE	*GetReadPtrPrtImageBuf(void);
#endif
/* UWORD	*GetReadPtrPrintBuf(void); */
void	DecPrtImageReadableLine(void);
void	InzPrintBuffers(UBYTE	Size);
void	SqueezeImageBuffer(void);
void	StretchInkRibbon(void);
void	CountStretchSteps(void);
BOOL	QueryRibbonStreching(void);
void	SetPrinterCloseRequest(void);
#if (0)	/* カッタ不良追加 1999/04/13 by T.Soneoka */
** void	CheckCutter(void);
** void	ExecCutter(void);
#else
UBYTE	CheckCutter(void);
UBYTE	ExecCutter(void);
#endif
void	PrtGA_IO_Write(UWORD	*SRC_ptr,	UWORD	CopyCount);		/* コピー数 */
BOOL IsNextPrint(void);
BOOL CheckPrinteDmaPermission(void);
BOOL Check3mOver(void);		/* 1998/12/15 by T.Soneoka */

void	InzRxMotor(void);
void	SetupRxMotor(UBYTE	MotorMode);
BOOL	QueryRxMotorMoving(void);
void	RequestToMoveRxMotor(void);
void	CancelToMoveRxMotor(void);
void	StartRxMotor(void);
void	StopRxMotor(void);
void	StopExciteRxMotor(void);
void	MovePrint1Line(void);
void	IntRxMotor(void);
BOOL	QueryPaperMoveNow(void);

void	SetDefaultPageQElements4List(struct PrintIndexQElement *IndexQPtr, struct PrintPageQElement *PageQ);
void	SetDefaultPageQElements4Decode(struct PrintIndexQElement *IndexQPtr, struct PrintPageQElement *PageQ);
void	SetDefaultPageQElements4Image(void);
void	SetDecodeParam4Print(struct CdcBlk_t *DecParam);
WORD	DecodeLine4Print(struct CdcBlk_t *DecParam, UBYTE *CurrentBuf, UBYTE *PreBuf);
BOOL	MakeImageLine4Print(void);
void	CloseDecode4Print(UBYTE	*CurrentBuf);
void	CloseImage4Print(void);

void	SetPrinterPageCount(UBYTE PaperSize);
void	SetPrinterJamCount(void);
void	SetInkRemainCount(UDWORD Count);

void	TestPrint4GA(void);
void	PrinterTestInterrupt(void);
void	AnalogFunctionMoveRxMotor(UBYTE	MotorMode);
void	AnalogFunctionTestThermal(void);


void	InzPrintPage(void);
int	QueryNumberOfPrintPageObject(void);
void	StepNextPhasePrintPage(UBYTE Phase,	struct PrintPageQElement *PageAtr);
struct PrintPageQElement	*QueryPrintingPage(UBYTE Phase);

BOOL	QueryIgnorePrinterError(void);

void PRN_PreOpen(void);
void PRN_PostClose(void);
void PRT_StartPrint(void);

void	PRN_StandbyToPrint(void);
UBYTE	PRN_CutToPrint(void);
void	PRN_PrintToStandby(void);
void	PRN_CutPosToStandbyPos(void);	/* 1999/04/14 by T.Soneoka */
void	PRN_CutPosToPrintPos(void);	/* 1999/04/14 by T.Soneoka */
UBYTE	PRN_PrintHaltRequest(void);
UBYTE	PRN_PrintErrorHaltRequest(void);
void	PRN_CheckPrinterError(void);
#if defined(SATSUKI2)
/* SATSUKI2 追加 start Y.Kano 2003/06/24 */
UBYTE	CutterPosition(void);
void 	CutterDrive1_On(void);
void 	CutterDrive1_Off(void);
void 	CutterDrive2_On(void);
void 	CutterDrive2_Off(void);
void	CutterOn(void);
void	CutterDrive(UBYTE);
void	Tim10msCutter(void);
void	ClearPrinterControlParameter(void);
#endif
/* SATSUKI2 追加 end   Y.Kano 2003/06/24 */

#endif /* PRT_TASK_H */
