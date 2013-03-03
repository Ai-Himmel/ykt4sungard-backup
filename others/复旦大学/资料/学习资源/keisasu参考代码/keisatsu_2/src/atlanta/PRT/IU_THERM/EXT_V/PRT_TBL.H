/*
 *	@(#)$Id: PRT_TBL.H,v 1.1.1.1 2005/04/04 04:24:06 mi93007 Exp $
 *	FileName:	/home2/prj/Eva/Src/inc/prt_tbl.h
 *	Create:	Thu Apr 09 21:17:59 1998	by	ishiyama
 *	Description:
 *		Printer Table Header File
 *	Change Log:
 *		
 */
#ifndef	PRT_TBL_H
	#define PRT_TBL_H

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
 #if defined(SATSUKI2)
#include "\src\atlanta\satsuki2\define\scn_def.h"
 #else
#include "\src\atlanta\hinoki\define\scn_def.h"
 #endif
#include "\src\atlanta\prt\iu_therm\define\prt_drv.h"

extern CONST UDWORD	PrinterDmaMaxSize;
extern CONST UBYTE	PrinterWhiteMaskWidth;		/* 両端白マスク幅(mm) */

extern CONST UWORD	PaperLength[];
extern CONST UBYTE	ReductionParam2Value[];

extern CONST UWORD	HReductionPattern[26][6];
extern CONST UWORD	VReductionPattern[26][2];

extern CONST UWORD	InitGaRmr;
extern CONST struct ThroughUpDown RxMotorUpDownNormal[];
extern CONST struct ThroughUpDown RxMotorUpDownFine[];
extern CONST struct ThroughUpDown RxMotorUpDownSFine[];
extern CONST struct ThroughUpDown RxMotorUpDownFarward[];
extern CONST struct ThroughUpDown RxMotorUpDownBackward[];
extern CONST struct MotorCtrl RxMotorTable[RX_MOTOR_TABLE_MAX];

#if (0) /* プリント原稿３ｍ以上に対応 1999/02/02/by T.Soneoka */
**	extern CONST WORD MinimumDocExitSteps;			/* 最小記録紙長排出ステップ １００ｍｍ */
#else
	extern CONST DWORD MinimumDocExitSteps;			/* 最小記録紙長排出ステップ １００ｍｍ */
#endif

extern CONST WORD FeedOutDocSteps;				/* 排出ステップ数 */
extern CONST WORD BackWardStepError;			/* 押し出し分４０ｍｍ＋カッタ位置からの距離２４ｍｍを引き戻してもＰＳ２センサがＯＦＦしない場合はカットエラー */
extern CONST WORD BackWardStepErrorFromReady;	/* ３０ｍｍ引き戻してもＰＳ２センサがＯＦＦしない場合はカットエラー */
extern CONST WORD PrintReadySteps;				/* 印字待機位置 １０ｍｍ */
extern CONST WORD PrintPostionSteps;			/* 印字位置 ＰＳ２から８ｍｍ分引き戻しす */
extern CONST WORD ToCutPosFromPlatenSteps;		/* 印字終了からカット位置までの距離 */
#if (0) /* プリント原稿３ｍ以上に対応 1999/02/02/by T.Soneoka */
**	extern CONST WORD JAM_CheckSteps;				/* ＪＡＭチェックステップ 印字開始からＣＵＴＴＥＲ位置からＰＳ２をチェックします */
#else
	extern CONST DWORD JAM_CheckSteps;				/* ＪＡＭチェックステップ 印字開始からＣＵＴＴＥＲ位置からＰＳ２をチェックします */
#endif
extern CONST WORD PrintingToFeedOutDocSteps;	/* 印字位置からの記録紙排出ステップ */

#if (0) /* プリント原稿３ｍ以上に対応 1999/02/02/by T.Soneoka */
**	extern CONST UWORD Print3M_Over;					/* ３ｍ印字オーバ 3000mm*15.4 */
#else
	extern CONST DWORD Print3M_Over;					/* ３ｍ印字オーバ 3000mm*15.4 */
#endif

extern CONST WORD COUNT_CUT_BACK_STEP;		/* 5mm分引き戻し 5/(1/15.4)=77step Ｂ４記録紙カット時、記録紙の端がいたむ不具合  1999/11/22 by T.Soneoka */

/* EndMark By O.Kimoto 1999/02/09 */
extern CONST WORD COUNT_CUTTER_TO_PS2;	/* 12.2mm * 15.4 */
extern CONST WORD COUNT_FEED_OUT;		/* 40.0mm * 15.4 */
extern CONST WORD COUNT_BOTTOM_MARGIN;	/*  4.0mm * 15.4 */

extern CONST UBYTE	PsChatCount;		/* PaperSensor チャタリング防止用カウント値 */
extern CONST UWORD	Ps1Exist2NonCount;	/* PaperSensor チャタリング防止用カウント値 */
extern CONST UWORD	Ps1Non2ExistCount;	/* PaperSensor チャタリング防止用カウント値 */
extern CONST UBYTE	AbnormalStrobeCount; /* 連続印可でエラーにする回数 */
extern CONST UWORD	HighTempUpper[2];		/* サーマルヘッド サーミスタ これ以上ならPlese wait */
extern CONST UWORD	HighTempLower[2];		/* サーマルヘッド サーミスタ これ以下になったら Ready*/
extern CONST UDWORD	InkInitialCount;	/* 200m x 15.4 */

extern CONST UBYTE	StrobeOffset;		/*  for test Strobe Pulse offsett */
extern CONST UBYTE	StrobeNormal[2][256];
extern CONST UBYTE	StrobeFine[2][256];
extern CONST UBYTE	StrobeSfine[2][256];
#if defined(SATSUKI2)	/* Add by Y.Kano 2003/09/17 */
extern CONST UBYTE	PreHeatTable[256];
#endif

#if (0)
**extern CONST UBYTE	PreHeatNormal[];
**extern CONST UBYTE	PreHeatFine[];
**extern CONST UBYTE	PreHeatSfine[];
#endif

extern CONST UBYTE head_preheat;

extern CONST UBYTE OffsetA4;

extern CONST UBYTE PrintThoughUpTable[20]; /* 1998/12/16 by T.Soneoka */
extern CONST UBYTE PrintThoughDownTable[20]; /* 1998/12/26 by T.Soneoka */

#endif /* PRT_TBL_H */
