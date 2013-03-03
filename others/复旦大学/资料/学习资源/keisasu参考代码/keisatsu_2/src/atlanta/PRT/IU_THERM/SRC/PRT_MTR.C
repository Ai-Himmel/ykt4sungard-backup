/*
 *	@(#)$Id: PRT_MTR.C,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	/prj/Eva/Src/prt/prt_mtr.c
 *	Create:	Tue May 26 20:53:49 1998	by	ishiyama
 *	Description:
 *		Printer Motor Control
 *	Change Log:
 *		
 */

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\atlanta\define\mntsw_h.h"

/*
 *	Attributes
 */
/*
 *	Name:	Initialize Rx Motor Parameter
 *	Create:	Tue May 26 20:55:59 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	InzRxMotor(void);
 *	Description:
 *		Initialize Rx Motor Parameters
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	InzRxMotor(void)
{
	EnableIntRxMotor = FALSE;
	GaRmrStatus = InitGaRmr;

	/* プリント調査 1998/11/19 by T.Soneoka */
	if (SYB_MaintenanceSwitch[MNT_SW_H0] & RX_TEST_MODE) {
#if (0) /* 1999/1/11 by T.Soneoka */
**		GaRmrStatus &= ~(RMSPED1600 | RMSTEP8 | RMSEL_2);
**		if (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_Rx400_1_2) {
**			GaRmrStatus |= (RMSPED400 | RMSTEP2 | RMSEL_1_2);
**		} else {
**			GaRmrStatus |= (RMSPED400 | RMSTEP2 | RMSEL_2);
**		}
#else
		GaRmrStatus &= ~RMSEL_2;
		if (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_1_2) {
			GaRmrStatus |= RMSEL_1_2;
		} else {
			GaRmrStatus |= RMSEL_2;
		}
#endif
		GaRmrStatus &= ~RMSYNC;
		if (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_RMSYNC) {
			GaRmrStatus |= RMSYNC;
		}
		OutputWORD(GA_RMR, GaRmrStatus);
	} else {
		OutputWORD(GA_RMR, GaRmrStatus);
	}
}


/*
 *	Name:	Setup Rx Motor Parameters
 *	Create:	Tue May 26 21:03:45 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	SetupRxMotor(VerticalMode);	// RX_MOTOR_* (prt_tbl.h)
 *	Description:
 *		受信モータの動作モードから必要なパラメータをセット
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetupRxMotor(
	UBYTE	MotorMode)					/* Rx Motor Mode RX_MOTOR_*(see prt_drv.h) */
{
	BOOL	EnableInt;

	EnableInt = CheckInterruptEnable(); /* 割込み状態保存 */
	CMN_DisableInterrupt();					/* 割込み禁止 */

	RxMotorCtrlPtr = &RxMotorTable[MotorMode];
	RxMotorSpeedPtr = RxMotorCtrlPtr->SpeedTable;
	RxMotorTransCount = RxMotorSpeedPtr->TransSteps;
	GaRmrStatus = (RxMotorCtrlPtr->Attribute | RxMotorSpeedPtr->ClockStep);

	/* プリント調査 1998/11/19 by T.Soneoka */
	if (SYB_MaintenanceSwitch[MNT_SW_H0] & RX_TEST_MODE) {
#if (0) /* 1999/1/11 by T.Soneoka */
**		GaRmrStatus &= ~(RMSPED1600 | RMSTEP8 | RMSEL_2);
**		if (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_Rx400_1_2) {
**			GaRmrStatus |= (RMSPED400 | RMSTEP2 | RMSEL_1_2);
**		} else {
**			GaRmrStatus |= (RMSPED400 | RMSTEP2 | RMSEL_2);
**		}
#else
		GaRmrStatus &= ~RMSEL_2;
		if (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_1_2) {
			GaRmrStatus |= RMSEL_1_2;
		} else {
			GaRmrStatus |= RMSEL_2;
		}
#endif
		GaRmrStatus &= ~RMSYNC;
		if (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_RMSYNC) {
			GaRmrStatus |= RMSYNC;
		}
		OutputWORD(GA_RMR, GaRmrStatus);
	} else {
		OutputWORD(GA_RMR, GaRmrStatus);
	}
	/* 割込み状態のリストア */
	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}


/*
 *	Name:	Rx Motor Moving now?
 *	Create:	Thu May 28 11:04:01 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	QueryRxMotorMoving(void);
 *	Description:
 *		
 *	Return Value:
 *		TRUE:	Moving
 *		FALSE:	Stopping
 *	Change Log:
 *		
 */
BOOL	QueryRxMotorMoving(void)
{
	return	EnableIntRxMotor;
}

/*
 *	Name:	Request to Move Rx Motor
 *	Create:	Tue Jun 02 14:41:24 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	RequestToMoveRxMotor(void);
 *	Description:
 *		Rx Motor に動くようリクエストを出す
 *	Notes:
 *		記録に同期して１ラインづつ動かすときに使用。
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	RequestToMoveRxMotor(void)
{
	Request1StepRxMotor = TRUE;
}

/*
 *	Name:	Cancel to Move Rx Motor
 *	Create:	Tue Jun 02 14:42:58 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	CancelToMoveRxMotor(void);
 *	Description:
 *		記録に同期して動かすときに使用
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	CancelToMoveRxMotor(void)
{
	Request1StepRxMotor = FALSE;
}

/* 
 *	Method
 */
/*
 *	Name:	Start Rx Motor
 *	Create:	Thu May 28 11:04:40 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	StartRxMotor(void);
 *	Description:
 *		Move Rx Motor by Previsous Setuped Parameter
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	StartRxMotor(void)
{
	BOOL	EnableInt;

	EnableInt = CheckInterruptEnable(); /* 割込み状態保存 */
	CMN_DisableInterrupt();					/* 割込み禁止 */

	PrinterPowerOn();
	RxMotorRequest = MOTOR_SPEED_UP;
	EnableIntRxMotor = TRUE;

	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}

/*
 *	Name:	Stop Rx Motor
 *	Create:	Thu May 28 11:05:20 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	StopRxMotor
 *	Description:
 *		Stop Rx Motor
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	StopRxMotor(void)
{
	BOOL	EnableInt;

	EnableInt = CheckInterruptEnable(); /* 割込み状態保存 */
	CMN_DisableInterrupt();					/* 割込み禁止 */

	RxMotorRequest = MOTOR_SPEED_DOWN;
	EnableIntRxMotor = FALSE;
	GaRmrStatus &= ~RMEXCT;			/* 非励磁 */

	/* プリント調査 1998/11/19 by T.Soneoka */
	if (SYB_MaintenanceSwitch[MNT_SW_H0] & RX_TEST_MODE) {
#if (0) /* 1999/1/11 by T.Soneoka */
**		GaRmrStatus &= ~(RMSPED1600 | RMSTEP8 | RMSEL_2);
**		if (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_Rx400_1_2) {
**			GaRmrStatus |= (RMSPED400 | RMSTEP2 | RMSEL_1_2);
**		} else {
**			GaRmrStatus |= (RMSPED400 | RMSTEP2 | RMSEL_2);
**		}
#else
		GaRmrStatus &= ~RMSEL_2;
		if (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_1_2) {
			GaRmrStatus |= RMSEL_1_2;
		} else {
			GaRmrStatus |= RMSEL_2;
		}
#endif
		GaRmrStatus &= ~RMSYNC;
		if (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_RMSYNC) {
			GaRmrStatus |= RMSYNC;
		}
		OutputWORD(GA_RMR, GaRmrStatus);
	} else {
		OutputWORD(GA_RMR, GaRmrStatus);
	}
	PrinterPowerOff();

	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}


/*
 *	Name:	Move Document 1 line
 *	Create:	Wed May 27 17:30:47 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	MovePrint1Line(void);
 *	Description:
 *		記録紙を設定されたモードで1ライン分動かす
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	MovePrint1Line(void)
{
	GaRmrStatus = (RxMotorCtrlPtr->Attribute | RxMotorSpeedPtr->ClockStep | RMSTART);
	/* プリント調査 1998/11/19 by T.Soneoka */
	if (SYB_MaintenanceSwitch[MNT_SW_H0] & RX_TEST_MODE) {
#if (0) /* 1999/1/11 by T.Soneoka */
**		GaRmrStatus &= ~(RMSPED1600 | RMSTEP8 | RMSEL_2);
**		if (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_Rx400_1_2) {
**			GaRmrStatus |= (RMSPED400 | RMSTEP2 | RMSEL_1_2);
**		} else {
**			GaRmrStatus |= (RMSPED400 | RMSTEP2 | RMSEL_2);
**		}
#else
		GaRmrStatus &= ~RMSEL_2;
		if (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_1_2) {
			GaRmrStatus |= RMSEL_1_2;
		} else {
			GaRmrStatus |= RMSEL_2;
		}
#endif
		GaRmrStatus &= ~RMSYNC;
		if (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_RMSYNC) {
			GaRmrStatus |= RMSYNC;
		}
		OutputWORD(GA_RMR, GaRmrStatus);
	} else {
		OutputWORD(GA_RMR, GaRmrStatus);
	}
}


/*
 *	Name:	Interrupt Routine for Rx Motor Control
 *	Create:	Thu May 28 11:16:28 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	IntRxMotor(void);
 *	Description:
 *		5msec Timer に同期して割込みルーチン内で使用
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	IntRxMotor(void)
{
	MovePrint1Line();				/*  記録紙移動 */

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 熱転写記録方式 */
	/* プリンタライフモニタの更新 */
	if ((RxMotorCtrlPtr->Attribute & (RMCCW|RMCW)) == RMCCW) {
		/* インクリボンが動く方向のときのみ */
		if (SYB_PrinterLifeMonitor.InkRemainCount >= RxMotorSpeedPtr->MoveLines) {
			SYB_PrinterLifeMonitor.InkRemainCount -= RxMotorSpeedPtr->MoveLines;
		} else {
			SYB_PrinterLifeMonitor.InkRemainCount = 0;
		}
	}
#endif

	/*  受信モータステータスを更新(Through Up/Down Stop etc.) */
	if (RxMotorRequest == MOTOR_SPEED_UP) {
		if (RxMotorTransCount > 0) {
			RxMotorTransCount--;
			if (RxMotorTransCount == 0) {
				RxMotorSpeedPtr++;
				RxMotorTransCount = RxMotorSpeedPtr->TransSteps;
			}
		}
	} else if (RxMotorRequest == MOTOR_SPEED_DOWN) { /* for Through Down */
		RxMotorTransCount++;
		if (RxMotorTransCount > RxMotorSpeedPtr->TransSteps) {
			RxMotorTransCount = 1;
			if (RxMotorSpeedPtr != RxMotorCtrlPtr->SpeedTable) {
				RxMotorSpeedPtr--;
			}
		}
	} else {
		/* not reached */
	}
}


/*
 *	Name:	Query Document Move Now
 *	Create:	Thu May 28 11:18:42 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	QueryPaperMoveNow(void);
 *	Description:
 *		受信モータを動かすかどうかを判断
 *		割込みルーチンでコール
 *		取敢えず、Through Down は未対応
 *	Return Value:
 *		TRUE:	モーター送り
 *		FALSE:	現状維持
 *	Change Log:
 *		
 */
BOOL	QueryPaperMoveNow(void)
{
	BOOL	Rslt;

	Rslt = TRUE;
	if (!QueryRxMotorMoving()) {
		/* モーター駆動要求がない */
		Rslt = FALSE;
	}
#if (0) /* UpdatePaperPosition()の中で見るように変更した 1998/11/12 by T.Soneoka */
**	if (!InterLock4PrintRaw()) {
**		/* Printer Cover Open */
**		Rslt = FALSE;
**	}
#endif
	if (Paper.Phase == PAPER_PHASE_PRINT) {
		if (!Request1StepRxMotor) {
			Rslt = FALSE;
		}
	}
	return	Rslt;
}


