/*
 *	@(#)%W%
 *	FileName:	/mnt/jason/home2/prj/Eva/Src/inc/scn_tbl.h
 *	Create:	Wed Dec 17 11:17:49 1997	by	ishiyama
 *	Description:
 *		Scanner Constant Value
 *	Change Log:
 *		
 */
#ifndef	SCN_TBL_H
#define SCN_TBL_H

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\hinoki\define\scn_def.h"

/* for Tx Motor */
extern CONST UWORD	InitGaTmr0;
extern CONST UWORD	InitGaTmr1;

extern CONST BYTE	ScanTimingTable[];	/* Scan Timing */
extern CONST BYTE	DummyScanLine;		/* Dummy Scan Lines */
extern CONST UWORD	ScanStopTestCount;	/* Scan Stop Test */

/*Through Up/Down 用テーブル */
extern CONST struct ThroughUpDown TxMotorUpDownNormal[];
extern CONST struct ThroughUpDown TxMotorUpDownFine[];
extern CONST struct ThroughUpDown TxMotorUpDownFine1_2[];
extern CONST struct ThroughUpDown TxMotorUpDownSFine1_2[];
extern CONST struct ThroughUpDown TxMotorUpDownDocIn[];
extern CONST struct ThroughUpDown TxMotorUpDownDocOut[];
extern CONST struct ThroughUpDown TxMotorUpDownToScan[];
extern CONST struct MotorCtrl TxMotorTable[];
extern CONST ConstThroughUpDownPtr TxMotorSpeedTable[];

extern CONST UWORD	Ds1ToDs2Steps;
extern CONST UWORD	MoveToDs2ErrorSteps; 		/* DS1 ON から DS2 ON までの繰り込み不良検出ステップ数 */
extern CONST UWORD	Ds2ToReadySteps;			/* DS2 から待機位置までのステップ数 */
extern CONST WORD	Ds2ToScanSteps;				/* DS2 から読取り位置までのステップ数 */
extern CONST WORD	Ds2ToScanEndSteps;			/* DS2 OFF から読取り終了位置までのステップ数 */
#if (0)	/* 未使用 1998/11/13 by T.Soneoka */
**extern CONST UWORD	Ds2ToStampSteps;			/* DS2 ON からスタンプ位置までのステップ数 */
#endif
extern CONST UWORD	Ds2ToExitSteps;				/* DS2  から排出までのステップ数 */
extern CONST UWORD	SCN_FEED_OUT_ERROR_STEPS;	/* 原稿一枚分の排出エラー検出ステップ */
#if (PRO_STAMP == ENABLE)
/*
** 原稿蓄積にて、１ページ読み取り完了する前に、原稿排出完了する仕様変更
**  1999/02/24 by T.Soneoka
*/
#if (0)
**extern CONST UWORD	Ds2ToPushStampSteps;		/* DS2 ON からスタンプ押下位置までのステップ数 */
#endif
extern CONST UWORD	StampTestSteps;				/* スタンプテスト押下間隔 5cm */
#endif
extern CONST UWORD CluchOffCounter;


extern CONST UWORD PickupRollerLiftUpSteps;

extern CONST BYTE	ScanChatCount;				/* チャタリング防止タイマ初期値 */

/*
 *	Tables
 */
extern CONST UBYTE	IniSreg[];			/* レジスタ初期値 */

/* AGC 設定時に使用するパラメータ */
extern CONST UBYTE	AgcClampMode;
#if defined(HINOKI2) || defined(HINOKI3)	/* ＬＣ８２１０３３仕様 by Y.Kano 2004/01/21 */
extern CONST UBYTE	AgcClampMean;
#endif
extern CONST UBYTE	AgcClampPoint;
extern CONST UBYTE	AgcSes;
extern CONST UBYTE	AgcSel;
extern CONST UWORD	AgcPes;
extern CONST UBYTE	AgcPel;
/* 読取り時に使用するパラメータ */
extern CONST UBYTE	ScanClampMode;
extern CONST UBYTE	ScanClampPoint;
extern CONST UBYTE	ScanSesA4;
extern CONST UBYTE	ScanSelA4;
extern CONST UWORD	ScanPesA4;
extern CONST UBYTE	ScanPelA4;
extern CONST UBYTE	ScanSesB4;
extern CONST UBYTE	ScanSelB4;
extern CONST UWORD	ScanPesB4;
extern CONST UBYTE	ScanPelB4;

extern CONST UBYTE	ShadingRamInitTable[];

extern CONST UBYTE BinaryThresholdLevelValue[DENSITY][DENSITY_REVISE_TABLE_MAX];
extern CONST UBYTE GrayGammaValue[DENSITY][DENSITY_REVISE_TABLE_MAX][GAMMA_DATA_MAX];
 #if defined(HINOKI2) || defined(HINOKI3)	/* ＬＣ８２１０３３仕様 by Y.Kano 2004/04/01 */
extern CONST UBYTE LC821033_BinGammaValue[GAMMA_DATA_MAX];
 #endif	/* End of defined(HINOKI2) */
extern CONST UBYTE BinGammaValue[GAMMA_DATA_MAX];

extern CONST UDWORD ScanReductionTimingTableB4toA4;

#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
extern CONST UBYTE  LC821033_GrayGammaValue[DENSITY][DENSITY_REVISE_TABLE_MAX][GAMMA_DATA_MAX];
extern CONST UBYTE	LC821033_IniSreg[];			/* レジスタ初期値 */
#endif	/* End of defined(HINOKI2) */

#if defined(HINOKI3)	/* ２値ガンマ補正テーブルの車検証モードの新設 Y.Kano 2005/01/11 */
extern CONST UBYTE CarBinGammaValue[GAMMA_DATA_MAX];
extern CONST UBYTE  LC821033_BinGammaValue_ForRedScan[GAMMA_DATA_MAX];	/* 朱色読取り用２値ガンマ補正テーブルの新設 Add by Y.Kano 2005/01/24 */
#endif

#endif /* SCN_TBL_H */
