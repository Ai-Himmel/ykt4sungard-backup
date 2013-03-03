/*******************************************************************
*	System		: SAKAKI
*	File Name	: PRN_TBL.H
*	Author		: K.Kawata
*	Date		: 1998/6/9
*	Description	:
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
********************************************************************/
#include "\src\atlanta\define\product.h"
#if (0) /*Smuratec H.C.H 2003.07.11*/
#include "\src\atlanta\prt\thermal\define\prn_def.h"
#else
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#endif

/* extern	CONST UBYTE HeatTable[2][64]; */

/* extern const UWORD  PRN_STEP_JAM_CHECK_LINE; */
/* extern const UWORD  PRN_STEP_MIN_LINE; */
/* extern const UWORD  PRN_STEP_HEAD_TO_CUTTER; */
/* extern const UWORD  PRN_STEP_CUTTER_TO_HEAD; */
/* extern const UWORD  PRN_STEP_STANDBY_TO_HEAD; */
/* extern const UWORD  PRN_STEP_HEAD_TO_STANDBY; */
/* extern const UWORD  PRN_STEP_BACKRUSH; */

/*POPLAR_H ÇÃÇΩÇﬂÇÃ¿ﬁ–∞*/
#if (0)
extern CONST UBYTE	PRN_SmoothingTable[4][3][10];
extern CONST UWORD	PRN_VSYNC_StartTimeTable;
extern CONST UWORD	PRN_HSYNC_StartTimeTable;
extern CONST UWORD	PRN_T1TimerTable;
extern CONST UWORD	PRN_T2TimerTable;
extern CONST UWORD	PRN_T20TimerTable;
extern CONST UWORD	PRN_T21TimerTable;
extern CONST UWORD	PRN_T22TimerTable;
extern CONST UWORD	PRN_T3TimerTable;
extern CONST UWORD	PRN_T7TimerTable;
extern CONST UWORD	PRN_T8TimerTable;
extern CONST UWORD	PRN_T9TimerTable;
extern CONST UWORD	PRN_T10TimerTable[31];
extern CONST UWORD	PRN_T10DelayTimerTable;
extern CONST UWORD	PRN_T11TimerTable;
extern CONST UWORD	PRN_T12TimerTable;
extern CONST UWORD	PRN_T13TimerTable;
extern CONST UWORD	PRN_TclTimerTable;
extern CONST UWORD	PRN_TmclTimerTable;
extern CONST UWORD	PRN_J1TimerTable[4];
extern CONST UWORD	PRN_J2TimerTable;
extern CONST UWORD	PRN_J3TimerTable[31];
extern CONST UWORD	PRN_PrintClockCounter[31][2];
extern CONST UWORD	PRN_PrintClockCounterInch[31][2];
extern CONST UWORD	PRN_HorizontalDataTable[31][6];
extern CONST UWORD	PRN_PrintScanningLineTable[3][2];
extern CONST UWORD	PRN_ScanScanningLineTable[3][4][2];
extern CONST UBYTE	PRN_PaperRankingTable[31];
extern CONST UBYTE	PRN_LongPaperRankingTable[31];
extern CONST UBYTE	PRN_WidthRankingTable[31][2];
extern CONST UBYTE	*(PaperSizeTable)[4];
extern CONST UBYTE	PRN_MulticopyCassetteTable[4];
extern CONST UBYTE	PRN_PrintCassetteTable[5];
#if (PRO_PC_PRINT == ENABLE)
extern CONST UBYTE	PRN_DPR_To_SYS_CassetteTable[6];
#endif
extern CONST UBYTE	PRN_NoPaperBitTable[4];
extern CONST UBYTE	PRN_ListPrintSizeTable[31];
extern CONST UBYTE	PRN_PatternPrintSizeTable[31];
extern CONST UBYTE	PRN_TotalCountConversion[31][2];
extern CONST UBYTE	PRN_FixReductionSizeTable[31];
extern CONST UWORD	PRN_PagePrintingTimeTable[31];
extern CONST UWORD	PRN_FuserTempTable[7];
extern CONST UWORD	PRN_CassetteSizeDetectTable[10];
extern CONST UWORD	PRN_TonerSliceTable;
extern CONST UBYTE	PRN_TonerCheckTable[2];
extern CONST UWORD	PRN_TonerRemainPrintMax;
extern CONST UWORD	PRN_DrumPrintMax;
extern CONST UWORD	PRN_DrumPrintStopMax;

#if (PRO_PRINTER == DPI400)
extern CONST UBYTE	PRN_StrobeTimeTable;		/* 1998/03/05 */
#endif
#if (PRO_PRINTER == DPI200)
extern CONST UBYTE	PRN_StrobeTimeTable;		/* 1998/03/05 */
extern CONST UBYTE	PRN_StrobeTimeGrayTable;	/* 1998/03/05 */
#endif
#endif

