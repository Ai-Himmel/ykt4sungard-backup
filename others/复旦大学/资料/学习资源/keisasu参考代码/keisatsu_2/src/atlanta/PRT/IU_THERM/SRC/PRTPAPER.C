/*
 *	@(#)$Id: PRTPAPER.C,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	/prj/Eva/Src/prt/prtpaper.c
 *	Create:	Fri May 15 11:49:32 1998	by	ishiyama
 *	Description:
 *		用紙選択
 *	Change Log:
 *		
 */

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\define\mpr_pro.h"
 #else
#include "\src\atlanta\hinoki\define\mpr_pro.h"
 #endif
#include "\src\atlanta\prt\iu_therm\ext_v\prn_data.h"
#include "\src\cpu\sh7043_a\irom\ext_v\ref_tbl.h"

static UWORD	CassetteScore[NUMBER_OF_CASSETTE];
static UWORD	PrtPageMemSizePrinterBase;

/*
 *	一枚にプリントできるときの幅による評価点
 *	短いほど評価が高い
 *	A4,Letter,Legal,F4 は、同じとして扱う
 */
static CONST UBYTE	PaperSizeScoreWidth[] = {
	0,									/* PAPER_SIZE_NONE */
	1,									/* PAPER_SIZE_A4(210.0mm) */
	1,									/* PAPER_SIZE_LETTER(215.9mm) */
	1,									/* PAPER_SIZE_LEGAL(215.9mm) */
	1,									/* PAPER_SIZE_F4(210.0mm) */
};

/*
 *	一枚にプリントできるときの長さによる評価点
 *	短いほど評価が高い
 */
static CONST UBYTE	PaperSizeScoreLength[] = {
	0,									/* PAPER_SIZE_NONE */
	3,									/* PAPER_SIZE_A4(297.0mm) */
	4,									/* PAPER_SIZE_LETTER(279.4mm) */
	1,									/* PAPER_SIZE_LEGAL(355.6mm) */
	2,									/* PAPER_SIZE_F4(330.0mm) */
};


/*
 *	分割プリント時の評価点
 *	長いほど評価が高い
 *	分割するなら、ページ数は少ない方がよいという発想
 */
static CONST UBYTE	PaperSizeScoreLengthDivide[] = {
	0,									/* PAPER_SIZE_NONE */
	2,									/* PAPER_SIZE_A4(297.0mm) */
	1,									/* PAPER_SIZE_LETTER(279.4mm) */
	4,									/* PAPER_SIZE_LEGAL(355.6mm) */
	3,									/* PAPER_SIZE_F4(330.0mm) */
};

/*
 *	カセット位置による優先
 *	ANZU に合わせて、MP_TRAY より CASSETTE 優先
 *	数字が大きい方が優先順位が高い
 */
static CONST UBYTE	CassettePriorityScore[] = {
	2,									/* PRT_MP_TRAY */
	1,									/* PRT_CASSETTE */
};


/*
 *	Name:	Set Print Paper Attribute
 *	Create:	Tue May 19 14:00:50 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	SetPaperAttribute(void);
 *	Description:
 *		各カセットの属性を設定する
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetPaperAttribute(void)
{
	BOOL	EnableInt;

	EnableInt = CheckInterruptEnable(); /* 割込み状態保存 */
	CMN_DisableInterrupt();					/* 割込み禁止 */

	if (PB4()) {
		CassetteAttr.PaperSize = PAPER_SIZE_B4;
	} else {
		CassetteAttr.PaperSize = PAPER_SIZE_A4;
	}

	/* 記録紙属性初期化 */
	Paper.Mode = SYS_NORMAL;			/* 記録モード:SYS_NORMAL...(doc.h) */
	Paper.Size = CassetteAttr.PaperSize; /* サイズ:PAPER_SIZE_*(prt_drv.h) */
	switch(Paper.Mode) {
	case SYS_NORMAL:
		Paper.VerticalMode = RX_MOTOR_NORMAL;
		break;
	case SYS_FINE:
	case SYS_GRAY64:
		Paper.VerticalMode = RX_MOTOR_FINE;
		break;
	case SYS_SFINE:
		Paper.VerticalMode = RX_MOTOR_SFINE;
		break;
	}
	Paper.RewriteCount = 4;				/* Normal ２度書き 4Phase */
	Paper.HolzReduction = 100;			/* プリント主走査縮小率 */
	Paper.VertReduction = 100;			/* プリント副操作縮小率 */
	Paper.TopMargin = QueryPrinterTopMargin();
	Paper.BottomMargin = QueryPrinterBottomMargin();
	Paper.StepsFromDocSet = 0;
	Paper.StepsFeedOut = 0;
	Paper.BackWardStepsFromFeedOut = 0;
	Paper.StepsFromPs2On = 0;
	Paper.StepsFromPrinting = 0;
	Paper.StepsToCutPosFromPlaten = 0;

	/* HINOKIはT/HはB4で記録紙はA4/B4がセットできる。
	** 記録紙がB4の時は問題ないがA4の場合は、記録紙が右寄せとなり、左側に余白を付けなければならない。
	** よって、ここで、PRN_PrinterBufferのポインターにオフセットを付けることにする。
	** 尚、スキャナーコピーは、イメージの貼り付けが既に右寄せ対応となっているので、注意が必要！
	** By O.Kimoto 1998/11/10
	*/
	if (CassetteAttr.PaperSize == PAPER_SIZE_A4) {
		if (PrinterUseMode != PRINT_SCOPY) {
			prn_imgbuf1_p = &PRN_ImageBuffer1[0][40];
			img_buffer1 = &PRN_ImageBuffer1[0][40];
			PRN_ImageBufferOffSet = 40;
		}
		else {
			prn_imgbuf1_p = &PRN_ImageBuffer1[0][0];
			img_buffer1 = &PRN_ImageBuffer1[0][0];
			PRN_ImageBufferOffSet = 0;
		}
	}
	else {
		prn_imgbuf1_p = &PRN_ImageBuffer1[0][0];
		img_buffer1 = &PRN_ImageBuffer1[0][0];
		PRN_ImageBufferOffSet = 0;
	}

	/* 割込み状態のリストア */
	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}


/*
 *	Name:	Query Smoothing On or OFF
 *	Create:	Fri Jun 19 10:39:55 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	QuerySmoothingOn(void);
 *	Description:
 *		スムージングが現在、有効かどうかを返す。
 *	Return Value:
 *		TRUE:	Smoothing 処理する
 *		FALSE:	Smoothing 処理しない
 *	Notes:
 *		SetPaperAttribute() をコールし、Paper.Mode がセットされたあとでのみ有効
 *	Change Log:
 *		
 */
BOOL	QuerySmoothingOn(void)
{
	BOOL	Rslt;

	Rslt = FALSE;
	if (Paper.Mode == SYS_NORMAL && CHK_UNI_SmoothingNormal()) {
		Rslt = TRUE;
	}
	return	Rslt;
}

