/*
 *	@(#)%W%
 *	FileName:	/mnt/jason/home2/prj/Eva/Src/scn/scn_mtr.c
 *	Create:	Wed Dec 17 11:08:31 1997	by	ishiyama
 *	Description:
 *		Tx Motor Control for Scanner
 *	Change Log:
 *		1998/06/09
 *			モーターを止めた時、レイジを切るように変更。
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\mntsw_h.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\scn_tbl.h"
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"

/*
 *	Attributes
 */
/*
 *	Name:	Initialize Tx Motor Parameter
 *	Create:	Thu Dec 18 10:58:41 1997	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		void	InzTxMotor(void);
 *	Description:
 *		Initialize Tx Motor Parameters
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	InzTxMotor(void)
{
	EnableIntTxMotor = FALSE;
	GaTmr0Status = InitGaTmr0;
	OutputWORD(GA_TMR0, GaTmr0Status);
	GaTmr1Status = InitGaTmr1;
	OutputWORD(GA_TMR1, GaTmr1Status);
}


/*
 *	Name:	Setup Tx Motor Parameters
 *	Create:	Wed Dec 17 11:25:15 1997	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		void	SetupTxMotor(VerticalMode);	// TX_MOTOR_* (scn_tbl.h)
 *	Description:
 *		送信モータの動作モードから必要なパラメータをセット
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetupTxMotor(
	BYTE	FeederMode)					/* Feeder Mode FEEDER_*(feeder.h) */
{
	UBYTE	VirticalMode;				/* 副操作モード */
	BOOL	CurrentInt;

	ScannerFeederMode = FeederMode;
	CurrentInt = CheckInterruptEnable();
	CMN_DisableInterrupt();	/* 割り込み禁止 */
	switch (FeederMode) {
	case FEEDER_MOVE_TO_SCAN:
		VirticalMode = TX_MOTOR_MOVE_TO_SCAN;
		break;
	case FEEDER_NORMAL_SCAN:
		VirticalMode = TX_MOTOR_NORMAL_SCAN;
		break;
	case FEEDER_FINE_SCAN:
		VirticalMode = TX_MOTOR_FINE_SCAN;
		break;
	case FEEDER_SFINE_SCAN:
		VirticalMode = TX_MOTOR_SFINE_SCAN;
		break;
	case FEEDER_FINE1_2_SCAN:
		VirticalMode = TX_MOTOR_FINE1_2_SCAN;
		break;
	case FEEDER_SFINE1_2_SCAN:
		VirticalMode = TX_MOTOR_SFINE1_2_SCAN;
		break;
	case FEEDER_DOC_IN:
		VirticalMode = TX_MOTOR_DOC_IN;
		break;
	case FEEDER_DOC_OUT:
	default:
		VirticalMode = TX_MOTOR_DOC_OUT;
		break;
	}

	TxMotorCtrlPtr = &TxMotorTable[VirticalMode];
	TxMotorSpeedPtr = TxMotorCtrlPtr->SpeedTable;
	TxMotorTransCount = TxMotorSpeedPtr->TransSteps;
	GaTmr0Status = (TxMotorCtrlPtr->Attribute | TxMotorSpeedPtr->ClockStep);

	ScanTimingBaseMax = ScanTimingTable[CurrentPage->VerticalMode];	/* 1998/12/04 by T.Soneoka */

#if (0) /* 1998/12/04 by T.Soneoka */
**	if (!Debug_MoveToScan200pps) {
**		OutputWORD(GA_TMR0, GaTmr0Status);
**	}
#endif

	GaTmr1Status = TxMotorCtrlPtr->ExtendAttribute;

#if (0) /* 1998/12/04 by T.Soneoka */
**	if (!Debug_MoveToScan200pps) {
**		OutputWORD(GA_TMR1, GaTmr1Status);
**	}
#endif
	if (CurrentInt) {
		CMN_EnableInterrupt();	/* 割り込み許可 */
	}
}


/*
 *	Name:	Tx Motor Moving now?
 *	Create:	Wed Dec 24 14:40:56 1997	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	QueryTxMotorMoving(void);
 *	Description:
 *		
 *	Return Value:
 *		TRUE:	Moving
 *		FALSE:	Stopping
 *	Change Log:
 *		
 */
BOOL	QueryTxMotorMoving(void)
{
	return	EnableIntTxMotor;
}

/* 
 *	Method
 */
/*
 *	Name:	Start Tx Motor
 *	Create:	Thu Dec 18 10:54:44 1997	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		void	StartTxMotor(void);
 *	Description:
 *		Move Tx Motor by Previsous Setuped Parameter
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	StartTxMotor(void)
{
	BOOL	CurrentInt;

	/* 保険、モータが完全に停止している状態からモータスタートさせます 1998/12/04 by T.Soneoka */
	EnableIntTxMotor = FALSE;
	wai_tsk(2);

	ScannerPowerOn();
	TxMotorRequest = MOTOR_SPEED_UP;
	EnableIntTxMotor = TRUE;
}

/*
 *	Name:	Stop Tx Motor
 *	Create:	Thu Dec 18 10:57:03 1997	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		void	StopTxMotor
 *	Description:
 *		Stop Tx Motor
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	StopTxMotor(void)
{
	TxMotorRequest = MOTOR_SPEED_DOWN;
	EnableIntTxMotor = FALSE;

	/* モータが完全に回りきるまで待ちます 1998/12/04 by T.Soneoka */
	wai_tsk(2);

	StopExciteTxMotor();
	ScannerPowerOff();
	/*
	** 励磁しっぱなし不具合 2000/04/11 by T.Soneoka
	** このStopTxMotor()内で、一括してCluchOff()を呼びます
	*/
	CluchOff();
}

void	PauseTxMotor(void)
{
}


void	CurrentDownTxMotor(void)
{
	if (GaTmr0Status & TMEXCT) {
		MotorExciteCount--;
		if (!MotorExciteCount) {
			StopExciteTxMotor();
			CluchOff(); /* 念の為 */
		}
	}
}

void	StopExciteTxMotor(void)
{
	BOOL	EnableInt;

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	GaTmr0Status &= ~(TMEXCT | TMSTART);			/* 非励磁・スタートＯＦＦ */
	OutputWORD(GA_TMR0, GaTmr0Status);
	
	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}


#if (0) /* 未使用です 1998/12/21 by T.Soneoka */
**/*
** *	Name:	Feed Out Document
** *	Create:	Tue Feb 10 16:55:43 1998	by	ishiyama
** *	Synopsis:
** *		#include	"feeder.h"
** *		void	FeedOutDoc(void);
** *	Description:
** *		全原稿排出
** *	Return Value:
** *		void
** *	Change Log:
** *		
** */
**void	FeedOutDoc(void)
**{
**	SetupTxMotor(FEEDER_DOC_OUT);
**	CluchOn();
**	StartTxMotor();
**}
#endif

/*
 *	Name:	Move Document 1 line
 *	Create:	Mon Feb  2 15:51:28 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		void	MoveScan1Line(void);
 *	Description:
 *		原稿を設定されたモードで1ライン分動かす
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	MoveScan1Line(void)
{
	UWORD	ss_status;
	
	GaTmr0Status = (TxMotorCtrlPtr->Attribute | TxMotorSpeedPtr->ClockStep | TMSTART);
	OutputWORD(GA_TMR0, GaTmr0Status);

	GaTmr1Status = TxMotorCtrlPtr->ExtendAttribute;
	ss_status = (UWORD)(SYB_MaintenanceSwitch[MNT_SW_H1] & SS_STATUS);
	if (ss_status) {
		if (!(GaTmr0Status & TMSEL_2)) {	/* １－２相の場合 */
			GaTmr1Status |= (SSEX | ss_status);
		}
	}
	OutputWORD(GA_TMR1, GaTmr1Status);
}


/*
 *	Name:	Interrupt Routine for Tx Motor Control
 *	Create:	Wed Dec 24 14:38:47 1997	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		void	IntTxMotor(void);
 *	Description:
 *		5msec Timer に同期して割込みルーチン内で使用
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	IntTxMotor(void)
{
	BYTE	Pos;

	MoveScan1Line();				/*  原稿移動 */

	Pos = QueryDocPosition();
/*
** 原稿蓄積中にクラッチがＯＦＦしてしまう不具合
** 現在、１ページ読み取り、原稿が停止した時点で、MotorExciteCountの減算が始まり
** またそのカウンタもSTOP_EXCITE_COUNT（１秒）となっていました。
** 原稿読み取り動作中は１秒のカウンタをやめます、STOP_EXCITE_COUNT_SCAN（30分）を使用するようにします
**
** 不具合の経過
** 1ページ読み取り、原稿が停止した時点で、MotorExciteCountの減算が始まり
** またそのカウンタも１秒となっている
** 原稿停止後、上位ルーチンで、エンコードが終了し、次ページの読み取り開始時に
** CluchOn()->StartTxMotor()とコールされるのだが、CluchOn()とStartTxMotor()との間に割り込みが走った場合
** ここでCluchOff()がコールされてしまう為、繰り込み不良が発生する
** 1999/02/10 by T.Soneoka
*/
#if (0)
**	if (Pos == DOC_POS_SCANNING || Pos == DOC_POS_SCAN_FEEDOUT) {
#else
	if (Pos == DOC_POS_MOVE_TO_DS2
	|| Pos == DOC_POS_MOVE_TO_READY
	|| Pos == DOC_POS_MOVE_TO_SCAN
	|| Pos == DOC_POS_SCANNING
	|| Pos == DOC_POS_SCAN_FEEDOUT
	|| Pos == DOC_POS_MOVE_TO_PUSH_STAMP) {
#endif
		MotorExciteCount = STOP_EXCITE_COUNT_SCAN;
	} else {
		MotorExciteCount = STOP_EXCITE_COUNT;
	}

	/*  送信モータステータスを更新(Through Up/Down Stop etc.) */
	if (TxMotorRequest == MOTOR_SPEED_UP) {
		if (TxMotorTransCount > 0) {
			TxMotorTransCount--;
			if (TxMotorTransCount == 0) {
				TxMotorSpeedPtr++;
				TxMotorTransCount = TxMotorSpeedPtr->TransSteps;
			}
		}
	} else if (TxMotorRequest == MOTOR_SPEED_DOWN) { /* for Through Down */
		TxMotorTransCount++;
		if (TxMotorTransCount > TxMotorSpeedPtr->TransSteps) {
			TxMotorTransCount = 1;
			if (TxMotorSpeedPtr != TxMotorCtrlPtr->SpeedTable) {
				TxMotorSpeedPtr--;
			}
		}
	} else {
		/* not reached */
	}
}


/*
 *	Name:	Query Document Move Now
 *	Create:	Wed Jan 28 15:48:42 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		BOOL	QueryDocMoveNow(void);
 *	Description:
 *		スキャナモータを動かすかどうかを判断
 *		割込みルーチンでコール
 *		取敢えず、Through Down は未対応
 *	Return Value:
 *		TRUE:	モーター送り
 *		FALSE:	現状維持
 *	Change Log:
 *		
 */
BOOL	QueryDocMoveNow(void)
{
	UWORD Status;

	RequestScan = FALSE;

	if (!QueryTxMotorMoving()) {
		/* モーター駆動要求がない */
		return	FALSE;
	}

	if (!InterLock4ScanRaw()) {
		/* Scanner Cover Open */
		return	FALSE;
	}

#if (0) /* 1998/12/05 by T.Soneoka */
**	if (QueryScanning() && !EnableToWriteScanBuf()) {
**		/* Scanner Buffer が一杯なので読取れない */
**		return	FALSE;
**	}
#else
#if (0) /* 1998/12/10 by T.Soneoka */
**	if (QueryDocScannable() && !EnableToWriteScanBuf()) {
**		return	FALSE;
**	}
#else
	if (QueryScanning()) {

/*
** 読み取るべき位置をチェックできていなかった
** 1999/03/03 by T.Soneoka
*/
#if (0)
**		if (QueryDocScannable() && !EnableToWriteScanBuf()) {
**			RequestScan = FALSE;
**			return	FALSE;
**		} else {
**			RequestScan = TRUE;
**		}
#else
		if (QueryDocScannable()) {
			if (!EnableToWriteScanBuf()) {
				RequestScan = FALSE;
				return	FALSE;
			} else {
				RequestScan = TRUE;
			}
		} else {
			RequestScan = FALSE;
		}
#endif

	} else {
		RequestScan = FALSE;
	}
#endif
#endif

	return	TRUE;
}

BOOL CheckMotorStop(void)
{
	if (((GaTmr1Status & IV_ZERO) == IV_ZERO)
	&& (!(EnableIntTxMotor))) {
		return TRUE;
	}
	return FALSE;
}

#if (0) /* 1998/12/04 by T.Soneoka */
**/* 
**** １－２相対策
**** １－２相でスキャンする場合、１相からスキャンすると画質がかなり悪くなる
**** そこで、電源Ｏｎ時に１－２相で１ステップ分進めた状態から、１－２相スキャンするようにします
***/
**void TxMotor200_1_2_1StepStart(void)
**{
**	/* ＴＸモータ２００／１－２相で１ステップ分進めます（相を一定にする為） 1998/12/03 by T.Soneoka */
**	GaTmr0Status = (TMSPED200|TMSTEP1|TMSTART|TMSYNC|TMCCW|TMEXCT|TMSEL_1_2);
**	OutputWORD(GA_TMR0, GaTmr0Status);
**#if (0) /* 1998/12/4 by T.Soneoka */
****	StartTxMotor();
**#else
**	ScannerPowerOn();
**#endif
**	wai_tsk(1);
**	StopTxMotor();
**}
**
**void AdjustTxMotor(void)
**{
**	/* １－２相で回したステップを計算します 1998/12/03 by T.Soneoka */
**	if (StepsTMSEL_1_2 % 2) {
**		TxMotor200_1_2_1StepStart();
**	}
**	StepsTMSEL_1_2 = 0;
**}
**
**void CheckTxMotorTMSEL_1_2(void)
**{
**	/* １－２相で回したステップを計算します
**	** モータが回るときのみコールする
**	** 1998/12/03 by T.Soneoka */
**	
**	if (!(GaTmr0Status & TMSEL_2)) {	/* １－２相の場合 */
**		switch (GaTmr0Status & 0x0038) {
**		case TMSTEP1:	/* 1-2相:1Step */
**			StepsTMSEL_1_2 += 1;
**			break;
**		case TMSTEP2:	/* 1-2相:2Step */
**			StepsTMSEL_1_2 += 2;
**			break;
**		case TMSTEP4:	/* 1-2相:4Step */
**			StepsTMSEL_1_2 += 4;
**			break;
**		case TMSTEP8:	/* 1-2相:8Step */
**			StepsTMSEL_1_2 += 8;
**			break;
**		case TMSTEP16:	/* 1-2相:16Step*/
**			StepsTMSEL_1_2 += 16;
**			break;
**		case TMSTEP32:	/* 1-2相:32Step*/
**			StepsTMSEL_1_2 += 32;
**			break;
**		case TMSTEP64:	/* 1-2相:64Step*/
**			StepsTMSEL_1_2 += 64;
**			break;
**		default:
**			break;
**		}
**	}
**}
#endif
