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

#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\hinoki\define\scn_def.h"

extern BYTE		ScannerMode;				/* Scanner Mode */
extern BYTE		ScannerCopyMode;			/* Scanner Copy Mode */
extern UWORD	ScannerError;				/* Scanner Error */
extern BOOL		NowScanning;				/* TRUE:Opened Scanning FALSE:Closed Scanning */

/* for Interrupt */
extern BOOL		CheckScanLineInt;			/* 2.5msec 割り込みを LININT 信号の代りに使う */
extern BOOL		EnableScannerInt;			/* スキャナ割り込み許可(TRUE)/禁止(FALSE) */
extern BOOL		Make5msTiming4Scan;			/* 2.5ms 割込みで5ms のタイミングを作る TRUE:5msにあたるタイミング */
extern BYTE		ScanTimingBase;				/* 各モードでの読取りタイミングを決定するのに使用 */

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
extern BOOL	DocumentChanged;				/* 読取り原稿が次の原稿になったことを示す */

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

extern BOOL		EnableExecStamp;		/* 済みスタンプ実行フラグ */
extern BOOL		EnablePushStampEvent;	/* 済みスタンプ押下イベント許可フラグ */
extern BOOL		StampCount;				/* 済みスタンプ押下回数 */

extern UWORD	Ds2OnToOffErrorSteps; 		/* 原稿一枚分の排出エラー検出ステップ */

extern UBYTE	ScannerEventStatus;

extern UWORD	tskno_SCN_WatchDocFeedTask;
extern UWORD	tskno_SCN_ScanPage;
extern UWORD	tskno_SCN_StorePage;
extern UWORD	tskno_SCN_PageMemStore;

/*
 *	IC 内蔵 RAM
 */
extern UBYTE Lc82103Ram[];

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様 ガンマ補正メモリ by Y.Kano 2003/11/28 */
extern UBYTE Lc821033GammaRam[];
#endif

#endif /* SCN_DATA_H */
