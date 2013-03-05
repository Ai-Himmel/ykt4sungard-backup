/*
 *	@(#)$Id: PRT_INT.C,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	/home2/prj/Eva/Src/prt/prt_int.c
 *	Create:	Mon Mar 16 16:17:17 1998	by	ishiyama
 *	Description:
 *		Printer Interrupt 関連 Routines
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prn_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\cpu\sh7043_a\irom\define\def_evtn.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"


void	UpdatePrinterSensorStatus(void);
void	PrinterStatusTrans(void);
static BOOL	QueryMotorStopError(void);
void	ChangeRxMotorPhase(void);

void	PrinterTimerInt(void)
{
	/**********************************************************************
	 * 5msec 間隔処理
	 * SATSUKI2は10msec間隔処理
	 **********************************************************************/

/* 
** 異常ストローブ処理は見ないようします 1998/12/26 by T.Soneoka
*/
#if (0)
**	(void)WatchContinuousStrobe();	/* 異常ストローブ監視 */
#endif
	UpdatePrinterSensorStatus(); /* PS センサのステータスを更新 */
	if (EnablePrinterTimerInterrupt) {
		if (!QueryMotorStopError()) {
			if (CheckPrintablePosition() || PrintBufferClearMode) {
				/* 記録紙はプリント可能な位置にある */
				Print1Line();		/* １ラインプリント */
			}
			if (QueryPaperMoveNow()) {
				IntRxMotor();			/*	Motor Control */
				UpdatePaperPosition();	/*  記録紙位置のステータスを更新 */
			}
		}
		PrinterStatusTrans();
	}

	/* 追加 By O.Kimoto 1998/10/27 *//* 下記イベントは１回／５ｍｓｅｃに出すことに変更します。 by O.Kimoto 1998/12/16 */
	if ((PrinterUseMode != PRINT_IDLE) && (PrinterUseMode != PRINT_SCOPY) || (PrinterUseMode != PRINT_RXPRINT)) { /* PRINT_RXPRINT added by H.Hirao 1998/11/07 */
		if (DecodeWaitFlag) {
			DecodeWaitFlag = FALSE;
			DecodeWaitCommandFlag = FALSE;
			idet_evt(EVT_PRINT_HEAT_1LINE_END);
		}
		else {
			DecodeWaitCommandFlag = TRUE;
		}
	}
}

/*********************************************************************
 *	PBRDY(Printer Buffer Ready) Interrupt
 *********************************************************************/
void	EnableIntPbrdy(void)
{
	UBYTE	CurrentIntEnable;

	CurrentIntEnable = CheckInterruptEnable();
	CMN_DisableInterrupt();

	GA_IntMaskStatus |= IMASK_PBRDY;
	OutputWORD(GA_INT_MASK, GA_IntMaskStatus);

	if (CurrentIntEnable) {
		CMN_EnableInterrupt();
	}
}

void	DisableIntPbrdy(void)
{
	UBYTE	CurrentIntEnable;

	CurrentIntEnable = CheckInterruptEnable();
	CMN_DisableInterrupt();

	GA_IntMaskStatus &= ~IMASK_PBRDY;
	OutputWORD(GA_INT_MASK, GA_IntMaskStatus);

	if (CurrentIntEnable) {
		CMN_EnableInterrupt();
	}
}

/*********************************************************************
 *	TOP(Page Printer TOD) Interrupt
 *********************************************************************/
/*
 *	Name:	Disable Interrupt XTOP(Printer Top Of Data)
 *	Create:	Tue Mar 31 13:06:32 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	DisableIntXtop(void);
 *	Description:
 *		Printer TOD 割込みの禁止
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	DisableIntXtop(void)
{
	UBYTE	CurrentIntEnable;

	CurrentIntEnable = CheckInterruptEnable();
	CMN_DisableInterrupt();

	GA_IntMaskStatus &= ~IMASK_XTOP;
	OutputWORD(GA_INT_MASK, GA_IntMaskStatus);

	if (CurrentIntEnable) {
		CMN_EnableInterrupt();
	}
}

/*********************************************************************
 *	XSTWR(Printer Status Write) Interrupt
 *********************************************************************/
/*
 *	Name:	Disable Interrupt XSTWR(Printer Status Int.)
 *	Create:	Mon Mar 16 16:30:50 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	DisableIntXstwr(void);
 *	Description:
 *		Printer Status 割込みの禁止
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	DisableIntXstwr(void)
{
	UBYTE	CurrentIntEnable;

	CurrentIntEnable = CheckInterruptEnable();
	CMN_DisableInterrupt();

	GA_IntMaskStatus &= ~IMASK_XSTWR;
	OutputWORD(GA_INT_MASK, GA_IntMaskStatus);

	if (CurrentIntEnable) {
		CMN_EnableInterrupt();
	}
}


/*********************************************************************
 *	Page End Interrupt
 *********************************************************************/
/*
 *	Name:	Disable Interrupt PGEND(Printer Page End Int.)
 *	Create:	Mon Apr  6 16:28:36 JST 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	DisableIntPgend(void);
 *	Description:
 *		Printer Page End 割込みの禁止
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	DisableIntPgend(void)
{
	UBYTE	CurrentIntEnable;

	CurrentIntEnable = CheckInterruptEnable();
	CMN_DisableInterrupt();

	GA_IntMaskStatus &= ~IMASK_PGEND;
	OutputWORD(GA_INT_MASK, GA_IntMaskStatus);

	if (CurrentIntEnable) {
		CMN_EnableInterrupt();
	}
}


/*********************************************************************
 *	Print End Interrupt
 *********************************************************************/
void	EnableIntPrend(void)
{
	UBYTE	CurrentIntEnable;

	CurrentIntEnable = CheckInterruptEnable();
	CMN_DisableInterrupt();

	GA_IntMaskStatus |= IMASK_PREND;
	OutputWORD(GA_INT_MASK, GA_IntMaskStatus);

	if (CurrentIntEnable) {
		CMN_EnableInterrupt();
	}
}

void	DisableIntPrend(void)
{
	UBYTE	CurrentIntEnable;

	CurrentIntEnable = CheckInterruptEnable();
	CMN_DisableInterrupt();

	GA_IntMaskStatus &= ~IMASK_PREND;
	OutputWORD(GA_INT_MASK, GA_IntMaskStatus);

	if (CurrentIntEnable) {
		CMN_EnableInterrupt();
	}
}


/*********************************************************************
 *	Printer 2.5msec Timer Interrupt
 *********************************************************************/
void	EnableIntPrinterTimer(void)
{
	UBYTE	CurrentIntEnable;

	CurrentIntEnable = CheckInterruptEnable();
	CMN_DisableInterrupt();

	EnablePrinterTimerInterrupt = TRUE;

	if (CurrentIntEnable) {
		CMN_EnableInterrupt();
	}
}

void	DisableIntPrinterTimer(void)
{
	UBYTE	CurrentIntEnable;

	CurrentIntEnable = CheckInterruptEnable();
	CMN_DisableInterrupt();

	EnablePrinterTimerInterrupt = FALSE;

	if (CurrentIntEnable) {
		CMN_EnableInterrupt();
	}
}

BOOL	QueryPrinterTimerIntEnable(void)
{
	return	EnablePrinterTimerInterrupt;
}



void	UpdatePrinterSensorStatus(void)
{
	(void)Ps1Changed();
	(void)Ps2Changed();
#if !defined(SATSUKI2)	/* ＲＸインターロック廃止の為、削除 by Y.Kano 2003/07/03 */
	(void)InterLock4PrintChanged();
#endif
}


void	PrinterStatusTrans(void)
{
	BOOL	PositionChanged;

#if (0)	/* 1998/10/31 by T.Soneoka */
**	/*
**	 *	プリント終了要求受け付け
**	 *	終了処理中は要求を受付けない
**	 */
**	if (!PrinterCloseRequestReal) {
**		PrinterCloseRequestReal = PrinterCloseRequest;
**	}
**	PrinterCloseRequest = FALSE;
**
**	PositionChanged = FALSE;
**	if (PrvPosition != Paper.Position) {
**		PositionChanged = TRUE;
**		PrvPosition = Paper.Position;
**	}
#endif

	switch (Paper.Phase) {
	case PAPER_PHASE_FEED:
		if (Paper.Position == PAPER_POS_MOVE_TO_READY) {
			Paper.Phase = PAPER_PHASE_READY;
		}
		else if (Paper.Position == PAPER_POS_PRINTING) {
			Paper.Phase = PAPER_PHASE_PRINT;
		}
		break;

	case PAPER_PHASE_READY:
		if (Paper.Position == PAPER_POS_PRINTING) {
			Paper.Phase = PAPER_PHASE_PRINT;
		}
		break;

	case PAPER_PHASE_PRINT:
		if (Paper.Position != PAPER_POS_PRINTING) {
			Paper.Phase = PAPER_PHASE_FEED;
		}
		break;

	default:
		break;

	}

#if (0)
**	if (PositionChanged) {
**		if (Paper.Position == PAPER_POS_NO_PAPER || QueryMotorStopError()) {
**			StopRxMotor();
**		} else {
**			ChangeRxMotorPhase();
**		}
**	}
#endif
}

void	CheckThermalHighTemp(void)
{
	/*
	 *	サーマルヘッドの熱くなり過ぎチェック
	 *	サーミスタの数値は、温度が高いほど小さい
	 */
	 
	ThermistorValue = AD_Thermistor();
	if (PrinterError & PRT_ERROR_HIGH_TEMP) {
		if (ThermistorValue >= HighTempUpper[HeadMaker]) {
			PrinterError &= ~PRT_ERROR_HIGH_TEMP;	/* 高温印可不可解除 */
		}
	}
	else {
#if defined (HINOKI2) || defined (SATSUKI2) || defined (HINOKI3)	/* 2002/02/21 T.Takagi */
		/* スキャナーコピーとプリンター受信時は従来どおりの動作にします */
		if ((PrinterUseMode == PRINT_SCOPY) || (PrinterUseMode == PRINT_RXPRINT)) {
			if (ThermistorValue <= HighTempLower[HeadMaker]) {
				PrinterError |= PRT_ERROR_HIGH_TEMP;	/* 高温印可不可 */
			}
		}
		else if (!(Paper.Position == PAPER_POS_PRINTING)) {		/* 印字中以外 */
			/** 機械がオーバーヒート状態にない場合は、６５度[サーミスタ出力１１Ｈ]以上でオーバーヒート */
			if (ThermistorValue <= HighTempLower[HeadMaker]) {
				PrinterError |= PRT_ERROR_HIGH_TEMP;	/* 高温印可不可 */
			}
		}
#else
		if (ThermistorValue <= HighTempLower[HeadMaker]) {
			PrinterError |= PRT_ERROR_HIGH_TEMP;	/* 高温印可不可 */
		}
#endif
	}
}


/*
 *	Name:	Query Motor Stop Printer Error
 *	Create:	Tue Jun 23 16:41:11 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		static BOOL	QueryMotorStopError(void);
 *	Description:
 *		モーターを停止すべきエラーがある/なし
 *	Return Value:
 *		TRUE:	該当エラーあり
 *		FALSE:	該当エラーなし
 *	Change Log:
 *		
 */
static BOOL	QueryMotorStopError(void)
{
	BOOL	Rslt;

	Rslt = FALSE;

	if (PrinterError & (
		PRT_ERROR_JAM |
		PRT_ERROR_CUT_ERROR |
		PRT_ERROR_COVER_OPEN
		)) {
		Rslt = TRUE;
	}
	return	Rslt;
}

/*
 *	Name:	Change Rx Motor Phase
 *	Create:	Fri Jul 10 17:50:46 1998	by	ishiyama
 *	Synopsis:
 *		
 *	Description:
 *		記録紙位置によって受信モータのセットアップを行う
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ChangeRxMotorPhase(void)
{
	switch (Paper.Position) {
	case PAPER_POS_NO_PAPER:
		break;

	case PAPER_POS_MOVE_TO_MINI_DOC_EXIT:
		SetupRxMotor(RX_MOTOR_FORWARD);
		StartRxMotor();

	case PAPER_POS_FEED_OUT:
		/*
		** Ｂ４記録紙カット時、記録紙の端がいたむ不具合
		** 1999/11/22 by T.Soneoka
		*/
#if (0)
**		SetupRxMotor(RX_MOTOR_FORWARD);
#else
		IsCutBack = TRUE;
		SetupRxMotor(RX_MOTOR_BACKWARD);
#endif
		StartRxMotor();
		break;

	case PAPER_POS_MOVE_TO_PS2:
		SetupRxMotor(RX_MOTOR_BACKWARD);
		StartRxMotor();
		break;

	case PAPER_POS_MOVE_TO_READY:
		SetupRxMotor(RX_MOTOR_FORWARD);
		StartRxMotor();
		break;
	
	case PAPER_POS_MOVE_TO_PRINTING:
		SetupRxMotor(RX_MOTOR_BACKWARD);
		StartRxMotor();
		break;

	case PAPER_POS_PRINTING:
		switch (Paper.Mode) {
		case SYS_NORMAL:
			SetupRxMotor(RX_MOTOR_NORMAL);
			break;
		case SYS_FINE:
		case SYS_GRAY64:
			SetupRxMotor(RX_MOTOR_FINE);
			break;
		case SYS_SFINE:
			SetupRxMotor(RX_MOTOR_SFINE);
			break;
		default:
			SetupRxMotor(RX_MOTOR_FINE);
			break;
		}
		StartRxMotor();
		break;
		
	case PAPER_POS_MOVE_TO_CUT:
		SetupRxMotor(RX_MOTOR_FORWARD);
		StartRxMotor();
		break;

	case PAPER_POS_PRINTING_TO_FEED_OUT:
		SetupRxMotor(RX_MOTOR_FORWARD);
		StartRxMotor();
		break;
	
	default:
		break;
	}
}

/*
 *	Name:	Printer Print Buffer Ready Interrupt
 *	Create:	Fri May 29 13:39:14 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	PrinterPbReadyInt(void);
 *	Description:
 *		GateArray 内の PrintBuffer が Ready になったときの処理
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	PrinterPbreadyInt(void)
{
#if (0) /* 1998/11/24 by T.Soneoka */
**	if (PrinterDmaPermission == FALSE) {
**		if (!PrintBufferClearMode && QuerySmoothingOn()) {
**			if (PrinterRewriteCount == 2) {	/* 2 は、DMA 起動時のカウンタ値にあたる */
**				DecPrtImageReadableLine();	/* １ラインデータ転送終了 */
**			}
**		} else {
**			DecPrtImageReadableLine();		/* １ラインデータ転送終了 */
**		}
**		PrinterDmaPermission = TRUE;		/* Printer DMA 許可 */
**	}
#endif

	if (!PrintBufferClearMode && QuerySmoothingOn()) {
		if (PrinterRewriteCount == 2) {	/* 2 は、DMA 起動時のカウンタ値にあたる */
			DecPrtImageReadableLine();	/* １ラインデータ転送終了 */
		}
	} else {
		DecPrtImageReadableLine();		/* １ラインデータ転送終了 */
	}
	PrinterDmaPermission = TRUE;		/* Printer DMA 許可 */
}

