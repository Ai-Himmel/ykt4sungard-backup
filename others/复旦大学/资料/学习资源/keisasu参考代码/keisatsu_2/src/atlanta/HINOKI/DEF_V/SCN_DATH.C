/*
 *	@(#)%W%
 *	FileName:	/mnt/jason/home2/prj/Eva/Src/inc/scn_data.h
 *	Create:	Wed Dec 17 11:10:42 1997	by	ishiyama
 *	Description:
 *		Scanner Control Data Header File
 *	Change Log:
 *		\src\eva\incからスキャナ関係の参照変数をとってきて一つにまとまました 1998/09/26 by T.Soneoka
 *		
 */
#ifndef	SCN_DATA_H
	#define	SCN_DATA_H

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\hinoki\define\scn_def.h"

BYTE	ScannerMode = 0;				/* Scanner Mode */
BYTE	ScannerCopyMode = 0;			/* Scanner Copy Mode */
UWORD	ScannerError = 0;				/* Scanner Error */
BOOL	NowScanning = 0;				/* TRUE:Opened Scanning FALSE:Closed Scanning */
BOOL	IsScanOpen = 0;					/* 1998/12/10 by T.Soneoka */

/* for Interrupt */
BOOL	CheckScanLineInt = 0;			/* 2.5msec 割り込みを LININT 信号の代りに使う */
BOOL	EnableScannerInt = 0;			/* スキャナ割り込み許可(TRUE)/禁止(FALSE) */
BOOL	Make5msTiming4Scan = 0;			/* 2.5ms 割込みで5ms のタイミングを作る TRUE:5msにあたるタイミング */
UBYTE	Make10msTiming4Scan = 0;			/* 2.5ms 割込みで10ms のタイミングを作る TRUE:10msにあたるタイミング 1998/12/10 add by T.Soneoka */
BYTE	ScanTimingBase = 0;				/* 各モードでの読取りタイミングを決定するのに使用 */
BOOL	RequestScan = 0;	/* 1998/12/10 add by T.Soneoka */


/* for feeder */
UBYTE	ScannerSavedMode = 0;			/* Scanner Saved Mode(see doc.h) */
UBYTE	ScannerFeederMode = 0; 			/* Scanner Feeder Mode(see feeder.h) */

/* for Sensor */
BOOL	CookedDs1 = 0;					/* DS1 Status(Cooked Mode) */
BOOL	CookedDs2 = 0;					/* DS2 Status(Cooked Mode) */
BOOL	CookedDsB4 = 0;					/* DSB4 Status(Cooked Mode) */
BOOL	CookedInterLock4Scan = 0;		/* InterLock for Scanner Status(Cooked Mode) */
UBYTE	Ds1CookCounter = 0;				/* DS1 チャタリング防止用カウンタ */
UBYTE	Ds2CookCounter = 0;				/* DS2 チャタリング防止用カウンタ */
UBYTE	DsB4CookCounter = 0;			/* DSB4 チャタリング防止用カウンタ */
UBYTE	InterLock4ScanCookCounter = 0; /* InterLock for Scanner チャタリング防止用カウンタ */

/* for Tx Motor */
UBYTE	PowerCtrl = 0;								/* 24V Power Control (see power.h) */
BOOL	EnableIntTxMotor = 0;						/* Tx Motor 用割込み処理イネーブル */
BYTE	TxMotorTransCount = 0;						/* Tx Motor State Transision Counter */
BYTE	TxMotorRequest = 0;							/* MOTOR_SPEED_* (motor.h) */
const struct MotorCtrl		*TxMotorCtrlPtr = {0};	/* Tx Motor Control Pointer */
const struct ThroughUpDown	*TxMotorSpeedPtr = {0};	/* Tx Motor Speed Table for ThroughUp/Down */

/* for Documents */
struct ScanPageAtr	ScanPage[2] = {0};
struct ScanPageAtr	*CurrentPage = {0};
struct ScanPageAtr	*NextPage = {0};
BOOL	SCN_DocumentChanged = 0;				/* 読取り原稿が次の原稿になったことを示す */

/* for Task Control */
BOOL		SleepDocStoreSubTask = 0;		/* DocStore で Create される SubTask を Sleep にする */

/* for Document Store */
#if (0)
struct IndexTableWriteData	ScannerWriteIndex = {0};
struct PixExecData			StorePageMemHandle = {0};	/* 獲得したメモリブロックハンドラ */
#endif
UWORD	ScanningTotalLine = 0;						/* 読取ったライン数 */

/* for Pickup Roller */
UWORD	PickupRollerCount = 0;		/* Pickup Roller 引上げカウント */

/* for Class 1 */
UBYTE	PcDocumentSize = 0;

/* for Load Shading Data */
BOOL	ScannerPowerOnInz = 0;

BOOL	EnablePushStampEvent = 0;	/* 済みスタンプ押下イベント許可フラグ */
BOOL	StampCount = 0;				/* 済みスタンプ押下回数 */
BOOL	ExecutePushStamp = 0;		/* 済みスタンプイベント空ぶり防止フラグ */
UWORD	StampOnTime = 0;			/* 済みスタンプ保険タイマー */

UWORD	Ds2OnToOffErrorSteps = 0; 		/* 原稿一枚分の排出エラー検出ステップ */

UBYTE	ScannerEventStatus = 0;

UWORD	tskno_SCN_ScanPage = 0;
UWORD	tskno_SCN_StorePage = 0;
UWORD	tskno_SCN_PageMemStore = 0;
UWORD	tskno_SCN_DocOutTask = 0;
UWORD	tskno_SCN_STxStoreTask = 0;
UWORD	tskno_SCN_DummyTask = 0;	/* エンコードタスクからのイベント待ちのタスク、リスケジューラを走らせるため 1999/03/16 by T.Soneoka */

BOOL	IsDocument = 0;			/* 1Page 読取り処理継続 TRUE:継続,FALSE:中断 */

UBYTE ReductionPos = 0;

/* for scanner transmit added by H.Hirao */
UWORD	ScanPageMemEncodableLine = 0; /* まだコーデックが符号変換していないライン数 */

UBYTE	ScannerSkipCount = 0;

UBYTE	Debug_MoveToScan200pps = 0;

UWORD	StepsTMSEL_1_2 = 0;

UBYTE	ScanTimingBaseMax = 0;

UBYTE	DelayScan = 0;

UDWORD	MotorExciteCount = 0;

/*
** 原稿蓄積にて、１ページ読み取り完了する前に、原稿排出完了する仕様変更
**  1999/02/24 by T.Soneoka
*/
UWORD	Ds2ToPushStampSteps 	= 0;					/* DS2 OFF からスタンプ押下位置までのステップ数 */

UBYTE	ScanReduction = 0; /* 1999/03/04 by T.Soneoka */

UBYTE	NoNextDocument = 0;	/* Add by O.Kimoto 1999/03/08 */

#endif /* SCN_DATA_H */
