/*
 *	@(#)$Id: PRT_DRV.C,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	/home2/prj/Eva/Src/prt/prt_drv.c
 *	Create:	Thu Apr  2 10:04:55 1998	by	ishiyama
 *	Description:
 *		Printer Driver Interface
 *	Notes:
 *		関連ファイルとの違いは、
 *			prt_drv.c:	I/O 設定を含まない
 *			prtengin.c:	I/O 設定を含んで、プリンタ共通
 *			prtlaser.c:	Leser Beam Printer だけに使用するルーチン
 *			prtthrml.c:	Thermal Printer だけに使用するルーチン
 *	Change Log:
 *		1998/06/16
 *			レフトマージンが大きすぎるため、記録幅を210mm から 216mm に変更。
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\define\scn_def.h"
#include "\src\atlanta\satsuki2\define\mpr_pro.h"
 #else
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\define\mpr_pro.h"
 #endif

#include "\src\cpu\sh7043_a\irom\define\def_evtn.h"

#define	PRINTER_STOP_WAIT_BASE	(20/10)	/* 20msec */
#define LEGAL_EXITABLE_TIME	((((LEGAL_PAGE_LENGTH * 4) +2124+812+485+191) * 5) / 20)

static UWORD	*PrevImageStartPtr = 0;


void	InzPrinter(void)
{
	/* まず、これをしないとマルチプレックスしている端子が危険 */
	SetPrinterInterface();

	/* プリンタ関連割込み禁止 */
	DisableIntPrinterTimer();
	DisableIntPbrdy();
	DisableIntXtop();
	DisableIntXstwr();
	DisableIntPgend();
	DisableIntPrend();
}

/*
 *	Name:	Open Printer
 *	Create:	Thu Apr  2 10:04:46 1998	by	ishiyama
 *	Synopsis:
 *		#include	"printer.h"
 *		void	OpenPrinter();
 *	Description:
 *		プリント準備設定
 *	Return Value:
 *		TRUE:	準備完了
 *		FALSE:	準備失敗
 *	Change Log:
 *		
 */
BOOL	OpenPrinter(void)
{
	BOOL	Rslt;

	Rslt = TRUE;

	if (!QueryCanDoPrint()) {
		Rslt = FALSE;
	} else {
		PrinterPowerOn();
		SetPrinterInterface();
	}

	return	Rslt;
}


/*
 *	Name:	Start Print Page
 *	Create:	Thu Apr  2 10:11:08 1998	by	ishiyama
 *	Synopsis:
 *		#include	"printer.h"
 *		BOOL	StartPagePrint(void)
 *	Description:
 *		ページ毎の前処理
 *		用紙選択などの、ページ毎の設定
 *		Page Printer の場合:
 *			Image Queue から、DMA Queue 作成
 *	Return Value:
 *		TRUE:	正常終了
 *		FALSE:	エラー終了
 *	Change Log:
 *		
 */
BOOL	StartPagePrint(void)
{
	UWORD	LinesAtPrinter;				/* 23.1line/mm 換算のライン数 */
	UBYTE	RealReduction;				/* プリント時の縮小率 */
	BOOL	Rslt;						/* 戻り値 */
	BOOL	EnableInt;

	Rslt = TRUE;

	if (!QueryCanDoPrint()) {
		Rslt = FALSE;
	} else {

		/* 1999/01/12 by T.Soneoka */
		DisableIntPrinterTimer();

		IsPrintFinish = FALSE;	/* 1998/12/04 by T.Soneoka */
		RealReduction = 100;
		/* Printer Settings */
		SetDataSize(PageQ.Size);	/* 追加 1998/10/10 by T.Soneoka */
		SetPrinterVerticalMode(PageQ.Mode);
		SetHorizontalReduction(RealReduction);
		SetVerticalReduction(RealReduction);
		SetWhiteMaskWidth(CHK_PrinterMaskWhite());
		SetWhiteBlackAssign(FALSE);
		SetPrinterSmoothing(PageQ.Mode); /* Smoothing 設定 */

#if (0) /* 1998/12/15 by T.Soneoka */
**		/* リアルタイムコピー－＞スキャナ側／プリンタ受信－＞通信側で初期化します */
**		if (!((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT))) {
**			InzPrtImageBuf();	/* Add By O.Kimoto 1998/11/07 */
**		}
#endif
		InzPrtImageBuf();	/* Add By O.Kimoto 1998/11/07 */

		InzPrintBuffers(PageQ.Size);

		MakeDummyLine(); /* 1998/12/15 by T.Soneoka */
	}
	return	Rslt;
}


void	PrintDataTransTask(void)
{
#if (0) /* 1998/12/5 by T.Soneoka */
**	UWORD	*ImagePtr;
#else
	UBYTE	*ImagePtr;
#endif

	for (;;) {
		
		/* イベント空振りフラグ処理追加 by O.Kimoto 1998/10/12 */
		CMN_DisableInterrupt();
		if (IsEventPrintDataTras == 0) {
			wai_evt(EVT_PRT_DATA_TRANS);
		}
		IsEventPrintDataTras = 0;
		CMN_EnableInterrupt();
		ImagePtr = GetReadPtrPrtImageBuf();
#if (0) /* 1999/1/5 by T.Soneoka */
**		PrtGA_IO_Write(ImagePtr, PrtDataTrasCount);
#else
		PrtGA_IO_Write((UWORD *)ImagePtr, PrtDataTrasCount);
#endif
	}
	wai_tsk(0xffff);
}


#if (0)
**/*
** *	Name:	Stop Page Print
** *	Create:	Tue Jun 02 15:03:54 1998	by	ishiyama
** *	Synopsis:
** *		#include	"prt_drv.h"
** *		void	StopPagePrint(void);
** *	Description:
** *		１ページプリントの終了処理
** *	Return Value:
** *		void
** *	Change Log:
** *		
** */
**void	StopPagePrint(void)
**{
**	SetPrinterCloseRequest();
**	SqueezeImageBuffer();
**}
#endif

/*
 *	Name:	Caluculate Print Line Count
 *	Create:	Tue Apr 28 16:13:39 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		UWORD	CalcPrintLineCount(
 *			UWORD	Lines,						// 指定されたモードでのトータルライン数
 *			BYTE	Mode);						// モード (see doc.h)
 *	Description:
 *		GateArray のプリントラインレジスタに設定する数値を計算する。
 *		Lazer Printer のとき、23.1 line/mm 換算で何ラインあるか
 *		Thermal Printer のとき、15.4 line/mm 換算で何ラインあるか
 *	Return Value:
 *		ライン数
 *	Change Log:
 *		
 */
UWORD	CalcPrintLineCount(
	UWORD	Lines,						/* 指定されたモードでのトータルライン数 */
	BYTE	Mode)						/* モード */
{
	UWORD	Result;
	
	switch (Mode) {
	case SYS_NORMAL:
		Result = (Lines * 4);			/* 3.85 line/mm -> 15.4 line/mm */
		break;
	case SYS_FINE:
	case SYS_GRAY64:
		Result = (Lines * 2);			/* 7.7 line/mm -> 15.4 line/mm */
		break;
	case SYS_SFINE:						/* 15.4 line/mm -> 15.4 line/mm */
		Result = Lines;
		break;
	default:
		Result = (Lines * 2);			/* for failsafe */
		break;
	}
	return	Result;
}


#if (0) /* 1998/10/31 by T.Soneoka */
**/*
** *	Name:	Query Printer Error
** *	Create:	Thu Apr  2 10:14:22 1998	by	ishiyama
** *	Synopsis:
** *		#include	"prt_drv.h"
** *		UWORD	QueryPrinterError(void);
** *	Description:
** *		プリンタエラーステータスの更新とエラーステータスの通知
** *	Return Value:
** *		0:	No Error
** *		PRT_ERROR_*	(see prt_drv.h)
** *	Change Log:
** *		
** */
**UWORD	QueryPrinterError(void)
**{
**	UWORD	PrinterErrorTmp;			/* PrinterError の変更回数を減らすため使用 */
**	BOOL	EnableInt;
**
**	/*
**	 *	PrinterError は、あるタイミングでないと
**	 *	エラーを検出できない場合があるので、
**	 *	ゼロクリアしない。
**	 */
**	EnableInt = CheckInterruptEnable(); /* 割込み状態保存 */
**	CMN_DisableInterrupt();					/* 割込み禁止 */
**
**	PrinterErrorTmp = PrinterError;
**	if (QueryPrinterCoverOpen()) {
**		/* ジャム関係エラークリア */
**		PrinterErrorTmp &= ~(PRT_ERROR_JAM|PRT_ERROR_CUT_ERROR);
**		PrinterErrorTmp |= PRT_ERROR_COVER_OPEN; /* カバーオープン */
**	} else {
**		PrinterErrorTmp &= ~PRT_ERROR_COVER_OPEN; /* カバークローズ */
**	}
**
**	/*
**	 *	サーマルヘッドの熱くなり過ぎチェック
**	 *	サーミスタの数値は、温度が高いほど小さい
**	 */
**	if (PrinterErrorTmp & PRT_ERROR_HIGH_TEMP) {
**		if (AD_Thermistor() > HighTempLower) {
**			PrinterErrorTmp &= ~PRT_ERROR_HIGH_TEMP;	/* 高温印可不可解除 */
**		}
**	} else {
**		if (AD_Thermistor() < HighTempUpper) {
**			PrinterErrorTmp |= PRT_ERROR_HIGH_TEMP;	/* 高温印可不可 */
**		}
**	}
**
**	if (ExistRxPaper()) {
**		PrinterErrorTmp &= ~PRT_ERROR_NO_PAPER; /* 用紙あり */
**	} else {
**		PrinterErrorTmp |= PRT_ERROR_NO_PAPER; /* 用紙なし */
**	}
**
**	PrinterError = PrinterErrorTmp;
**
**	if (EnableInt) {
**		CMN_EnableInterrupt();
**	}
**#if (0) /* TBD 1998/10/06 by T.Soneoka */
**	SetServiceError2UniqSwitch();
**#endif
**	return	PrinterError;
**}
#endif


/*
 *	Name:	Query Can Do Print
 *	Create:	Thu Jul 23 21:41:48 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	QueryCanDoPrint(void);
 *	Description:
 *		プリンタエラーを見て、プリント可能かどうかを返す。
 *	Return Value:
 *		TRUE:	プリント可能
 *		FALSE:	プリント不可
 *	Change Log:
 *		
 */
BOOL	QueryCanDoPrint(void)
{
	BOOL	Rslt;
	
	Rslt = QueryCanDoPrintByArg(PrinterError);

	return	Rslt;
}	

/*
 *	Name:	Query Can Do Print By Argument
 *	Create:	Thu Sep 17 18:47:29 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	QueryCanDoPrintByArg(
 *			UWORD	Error);
 *	Description:
 *		引数のプリンタエラーを見て、プリント可能かどうかを返す。
 *	Return Value:
 *		TRUE:	プリント可能
 *		FALSE:	プリント不可
 *	Change Log:
 *		
 */
BOOL	QueryCanDoPrintByArg(
	UWORD	Error)
{
	BOOL	Rslt;


	Rslt = TRUE;
	if (Error & PRT_ERROR_NO_PAPER) {		/* 記録紙がカセットにない */
		Rslt = FALSE;
	}
	if (Error & PRT_ERROR_JAM) {		/* どこかでジャムってる */
		Rslt = FALSE;
	}
	
	if (Error & PRT_ERROR_COVER_OPEN) {		/* カバーオープン */
		Rslt = FALSE;
	}

	if (Error & PRT_ERROR_HIGH_TEMP) {		/* サーマルヘッドの温度がまだ高い */
		Rslt = FALSE;
	}

	if (Error & PRT_ERROR_CUT_ERROR) {		/* カッターエラー */
		Rslt = FALSE;
	}

	return	Rslt;
}

/*
 *	Name:	Wait Print Work
 *	Create:	Fri Jul 31 11:45:08 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	WaitPrintWork(void);
 *	Description:
 *		ページメモリがないとき、プリンタの仕事が終わるのを待つ
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */

void	WaitPrintWork(void)
{
	while (QueryPrinterTimerIntEnable()) {
		wai_tsk(10);					/* 100msec Wait */
	}
}

/*
 *	Name:	Print 1 Line
 *	Create:	Thu Apr 23 15:46:50 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	PrintLine(void);
 *	Description:
 *		1 Line Print 処理
 *	Return Value:
 *		TRUE:	Print 可能
 *		FALSE:	Print 不可
 *	Change Log:
 *		
 */
BOOL	PrintLine(void)
{
	BOOL	Rslt;

	Rslt = TRUE;

#if (0)	/* 1998/10/30 by T.Soneoka */
**	PrintImageLine++;
**	if (Paper.Phase == PAPER_PHASE_FEED || PrinterStopProcess) {
**		Rslt = FALSE;
**	} else {
**		IncPrtImageReadableLine();
**	}
#endif

#if (0) /* 1998/12/10 by T.Soneoka */
**	PrintImageLine++;
#endif
	IncPrtImageReadableLine();
	return	Rslt;
}

#if (0) /* 1998/10/30 by T.Soneoka */
**/*
** *	Name:	Set Image Start Address Pointer
** *	Create:	Mon Jul 06 15:09:19 1998	by	ishiyama
** *	Synopsis:
** *		#include	"prt_drv.h"
** *		void	SetImageStartPointer(
** *			UWORD	*Addr);
** *	Description:
** *		Image Memory の先頭アドレスをセットする
** *	Return Value:
** *		void
** *	Change Log:
** *		
** */
**void	SetImageStartPointer(
**	UWORD	*Addr)
**{
**	PrintImageLine = 0;
**	/* PrintImageStartPtr = Addr; */
**}
#endif

/*
 *	Name:	Query Image Start Address Pointer
 *	Create:	Thu Apr 23 15:49:35 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		UWORD	*QueryImageStartPointer(void);
 *	Description:
 *		確保したページメモリのラインの先頭アドレスを返す
 *	Return Value:
 *		確保したページメモリのラインの先頭アドレス
 *	Change Log:
 *		
 */
UWORD	*QueryImageStartPointer(void)
{
	UWORD	*Rslt;

#if (0) /* 1998/12/10 by T.Soneoka */
**	if (PrintImageLine == 0) {
**		while (Paper.Phase != PAPER_PHASE_PRINT) {
**			if (PrinterError != 0 || PrinterStopProcess) {
**				/* Error またはストップならば抜ける */
**				break;
**			}
**			wai_tsk(10);
**		}
**	} else {
**		while (!EnableToWritePrtImageBuf() && (Paper.Phase != PAPER_PHASE_FEED)) {
**			if (PrinterError != 0 || PrinterStopProcess) {
**				/* Error またはストップならば抜ける */
**				break;
**			}
**			wai_tsk(1);
**		}
**	}
#else
	while (!EnableToWritePrtImageBuf() && (Paper.Phase != PAPER_PHASE_FEED)) {
		if (PrinterError != 0 || PrinterStopProcess) {
			/* Error またはストップならば抜ける */
			break;
		}
		wai_tsk(1);
	}
#endif
	Rslt = GetWritePtrPrtImageBuf();
	PrevImageStartPtr = Rslt;
	return	Rslt;
}


/*
 *	Name:	Get Thin Out Line
 *	Create:	Mon Jul 27 16:49:58 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	QueryThinOutLine(void);
 *	Description:
 *		縮小により間引くラインか否か
 *	Return Value:
 *		TRUE:	間引くライン
 *		FALSE:	間引かないライン
 *	Change Log:
 *		
 */
BOOL	QueryThinOutLine(void)
{
	BOOL	Rslt;

	Rslt = FALSE;
	if (CurrentVReductionPattern & VRductionBit) {
		if (ThinOutCount == 2) {		/* 3 line に 1 Line 間引くテーブル故 */
			Rslt = TRUE;
		}
	}
	return	Rslt;
}

/*
 *	Name:	Update Thin Out Line Status
 *	Create:	Thu Jul 30 10:55:36 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	UpdateThinOutLine(void);
 *	Description:
 *		間引きラインを決定する条件を更新する
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	UpdateThinOutLine(void)
{
	if (VRductionBit & 0x80000000) {
		VRductionBit = 0x00000001;
	} else {
		VRductionBit <<= 1;
	}
	if (CurrentVReductionPattern & VRductionBit) {
		if (++ThinOutCount >= 3) {
			ThinOutCount = 0;
		}
	}
}


