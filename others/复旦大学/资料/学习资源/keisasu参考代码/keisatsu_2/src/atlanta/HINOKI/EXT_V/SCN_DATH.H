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
#ifndef	SCN_DATH_H
	#define	SCN_DATH_H

#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\hinoki\define\scn_def.h"

extern BYTE		ScannerMode;				/* Scanner Mode */
extern BYTE		ScannerCopyMode;			/* Scanner Copy Mode */
extern UWORD	ScannerError;				/* Scanner Error */
extern BOOL		NowScanning;				/* TRUE:Opened Scanning FALSE:Closed Scanning */
extern BOOL		IsScanOpen;					/* 1998/12/10 by T.Soneoka */

/* for Interrupt */
extern BOOL		CheckScanLineInt;			/* 2.5msec 割り込みを LININT 信号の代りに使う */
extern BOOL		EnableScannerInt;			/* スキャナ割り込み許可(TRUE)/禁止(FALSE) */
extern BOOL		Make5msTiming4Scan;			/* 2.5ms 割込みで5ms のタイミングを作る TRUE:5msにあたるタイミング */
extern UBYTE	Make10msTiming4Scan;		/* 2.5ms 割込みで10ms のタイミングを作る TRUE:10msにあたるタイミング */
extern BYTE		ScanTimingBase;				/* 各モードでの読取りタイミングを決定するのに使用 */
extern BOOL		RequestScan;				/* 1998/12/10 add by T.Soneoka */

/* for feeder */
extern UBYTE	ScannerSavedMode;			/* Scanner Saved Mode(see doc.h) */
extern UBYTE	ScannerFeederMode; 			/* Scanner Feeder Mode(see feeder.h) */

/* for Sensor */
extern BOOL		CookedDs1;					/* DS1 Status(Cooked Mode) */
extern BOOL		CookedDs2;					/* DS2 Status(Cooked Mode) */
extern BOOL		CookedDsB4;					/* DSB4 Status(Cooked Mode) */
extern BOOL		CookedInterLock4Scan;		/* InterLock for Scanner Status(Cooked Mode) */
extern UBYTE	Ds1CookCounter;				/* DS1 チャタリング防止用カウンタ */
extern UBYTE	Ds2CookCounter;				/* DS2 チャタリング防止用カウンタ */
extern UBYTE	DsB4CookCounter;			/* DSB4 チャタリング防止用カウンタ */
extern UBYTE	InterLock4ScanCookCounter; /* InterLock for Scanner チャタリング防止用カウンタ */

/* for Tx Motor */
extern UBYTE	PowerCtrl;								/* 24V Power Control (see power.h) */
extern BOOL		EnableIntTxMotor;						/* Tx Motor 用割込み処理イネーブル */
extern BYTE		TxMotorTransCount;						/* Tx Motor State Transision Counter */
extern BYTE		TxMotorRequest;							/* MOTOR_SPEED_* (motor.h) */
extern const struct MotorCtrl		*TxMotorCtrlPtr;	/* Tx Motor Control Pointer */
extern const struct ThroughUpDown	*TxMotorSpeedPtr;	/* Tx Motor Speed Table for ThroughUp/Down */

/* for Documents */
extern struct ScanPageAtr	ScanPage[2];
extern struct ScanPageAtr	*CurrentPage;
extern struct ScanPageAtr	*NextPage;
extern BOOL	SCN_DocumentChanged;				/* 読取り原稿が次の原稿になったことを示す */

/* for Task Control */
extern BOOL		SleepDocStoreSubTask;		/* DocStore で Create される SubTask を Sleep にする */

/* for Document Store */
#if (0)
extern struct IndexTableWriteData	ScannerWriteIndex;
extern struct PixExecData			StorePageMemHandle;	/* 獲得したメモリブロックハンドラ */
#endif
extern UWORD	ScanningTotalLine;						/* 読取ったライン数 */

/* for Pickup Roller */
extern UWORD	PickupRollerCount;		/* Pickup Roller 引上げカウント */

/* for Class 1 */
extern UBYTE	PcDocumentSize;

/* for Load Shading Data */
extern BOOL		ScannerPowerOnInz;

extern BOOL		EnablePushStampEvent;	/* 済みスタンプ押下イベント許可フラグ */
extern BOOL		StampCount;				/* 済みスタンプ押下回数 */
extern BOOL		ExecutePushStamp;		/* 済みスタンプイベント空ぶり防止フラグ */
extern UWORD	StampOnTime;			/* 済みスタンプ保険タイマー */

extern UWORD	Ds2OnToOffErrorSteps; 		/* 原稿一枚分の排出エラー検出ステップ */

extern UBYTE	ScannerEventStatus;

extern UWORD	tskno_SCN_WatchDocFeedTask;
extern UWORD	tskno_SCN_ScanPage;
extern UWORD	tskno_SCN_StorePage;
extern UWORD	tskno_SCN_PageMemStore;
extern UWORD	tskno_SCN_DocOutTask;
extern UWORD	tskno_SCN_STxStoreTask;
extern UWORD	tskno_SCN_DummyTask;	/* エンコードタスクからのイベント待ちのタスク、リスケジューラを走らせるため 1999/03/16 by T.Soneoka */
/*
 *	IC 内蔵 RAM
 */
extern UBYTE Lc82103Ram[];

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様 ガンマ補正メモリ by Y.Kano 2003/11/28 */
extern UBYTE Lc821033GammaRam[];
#endif

extern	BOOL	IsDocument;			/* 1Page 読取り処理継続 TRUE:継続,FALSE:中断 */

extern UBYTE ReductionPos;

/* for scanner transmit added by H.Hirao */
extern UWORD	ScanPageMemEncodableLine; /* まだコーデックが符号変換していないライン数 */

extern UBYTE	ScannerSkipCount;

extern UBYTE	Debug_MoveToScan200pps;

extern UWORD	StepsTMSEL_1_2;

extern UBYTE	ScanTimingBaseMax;

extern UBYTE	DelayScan;

extern UDWORD	MotorExciteCount;

/*
** 原稿蓄積にて、１ページ読み取り完了する前に、原稿排出完了する仕様変更
**  1999/02/24 by T.Soneoka
*/
extern UWORD	Ds2ToPushStampSteps;					/* DS2 OFF からスタンプ押下位置までのステップ数 */

extern UBYTE	ScanReduction; /* 1999/03/04 by T.Soneoka */

extern UBYTE	NoNextDocument;	/* Add by O.Kimoto 1999/03/08 */

#endif /* SCN_DATA_H */
