/*
 *	@(#)$Id: PRTENGIN.C,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	/home2/prj/Eva/Src/prt/prtengin.c
 *	Create:	Tue Apr  7 14:58:46 1998	by	ishiyama
 *	Description:
 *		Printer Engine Interface Routine
 *	Notes:
 *		関連ファイルとの違いは、
 *			prt_drv.c:	I/O 設定を含まない
 *			prtengin.c:	I/O 設定を含んで、プリンタ共通
 *			prtlaser.c:	Leser Beam Printer だけに使用するルーチン
 *			prtthrml.c:	Thermal Printer だけに使用するルーチン
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\define\mpr_pro.h"
#include "\src\atlanta\satsuki2\ext_v\ga_buf.h"
 #else
#include "\src\atlanta\hinoki\define\mpr_pro.h"
#include "\src\atlanta\hinoki\ext_v\ga_buf.h"
 #endif
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\atlanta\define\mntsw_h.h"
#include "\src\atlanta\define\sys_stat.h"	/* Add By O.Kimoto 1999/02/24 */

/*
 *	Name:	Set Printer Mode
 *	Create:	Wed Mar 18 15:14:27 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	SetPrinterInterface(void);
 *	Description:
 *		Laser or Thermal Head Printer のインターフェースを切り替える
 *		Gate Array の都合
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetPrinterInterface(void)
{
	UBYTE	Work;
	BOOL	CurrentInt;

	CurrentInt = CheckInterruptEnable();
	CMN_DisableInterrupt();					/* Task Switching 防止のため */

	/* Thermal Head Printer */
	OutputWORD(GA_PMD, PMD_THERMAL_PRINTER);
#if !defined(SATSUKI2) /* SATSUKI2に合わせるため以下に変更します。2003/06/18 */
	if (SYB_MaintenanceSwitch[MNT_SW_H0] & RX_TEST_MODE) {
		if (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_TPH_SYNC) {
			GaTphStatus = (TPH_EN				/* Thermal Head Control */
						   |TPH_SIZE_B4			/* B4 Head */
						   |TPH_STRSEL_2		/* ストローブ２分割 */
						   |TPH_STRPOL_NEG		/* ストローブ負論理 */
						   |TPH_DPOL_BLACK1		/* データ極性 白=0,黒=1 */
						   |TPH_CKSEL_3_5		/* 転送クロック 3.5MHz */
						   |TPH_DSIZE_B4		/* データサイズ B4 */
						   |TPH_MAINRC_OFF		/* 主走査縮小 OFF(Default) */
						   |TPH_RC_KEEP			/* 縮小補正　画素保存 */
						   |TPH_WMSK_OFF		/* 両端マスク OFF(Default) */
						   |(0x02 << 11)		/* 両端マスク幅 2mm(Default) */
						   |TPH_SYNC			/* 印可パルス SP_INT と同期 */
						   |TPH_LATPOL_NEG);	/* Latch 極性 負論理 */
		} else {
			GaTphStatus = (TPH_EN				/* Thermal Head Control */
						   |TPH_SIZE_B4			/* B4 Head */
						   |TPH_STRSEL_2		/* ストローブ２分割 */
						   |TPH_STRPOL_NEG		/* ストローブ負論理 */
						   |TPH_DPOL_BLACK1		/* データ極性 白=0,黒=1 */
						   |TPH_CKSEL_3_5		/* 転送クロック 3.5MHz */
						   |TPH_DSIZE_B4		/* データサイズ B4 */
						   |TPH_MAINRC_OFF		/* 主走査縮小 OFF(Default) */
						   |TPH_RC_KEEP			/* 縮小補正　画素保存 */
						   |TPH_WMSK_OFF		/* 両端マスク OFF(Default) */
						   |(0x02 << 11)		/* 両端マスク幅 2mm(Default) */
						   |TPH_ASYNC			/* 印可パルス SP_INT と非同期 */
						   |TPH_LATPOL_NEG);	/* Latch 極性 負論理 */
		}
	} else {
		GaTphStatus = (TPH_EN				/* Thermal Head Control */
					   |TPH_SIZE_B4			/* B4 Head */
					   |TPH_STRSEL_2		/* ストローブ２分割 */
					   |TPH_STRPOL_NEG		/* ストローブ負論理 */
					   |TPH_DPOL_BLACK1		/* データ極性 白=0,黒=1 */
					   |TPH_CKSEL_3_5		/* 転送クロック 3.5MHz */
					   |TPH_DSIZE_B4		/* データサイズ B4 */
					   |TPH_MAINRC_OFF		/* 主走査縮小 OFF(Default) */
					   |TPH_RC_KEEP			/* 縮小補正　画素保存 */
					   |TPH_WMSK_OFF		/* 両端マスク OFF(Default) */
					   |(0x02 << 11)		/* 両端マスク幅 2mm(Default) */
					   |TPH_ASYNC			/* 印可パルス SP_INT と非同期 */
					   |TPH_LATPOL_NEG);	/* Latch 極性 負論理 */
	}
#else	/* SATSUKI2 */
	if (SYB_MaintenanceSwitch[MNT_SW_H0] & RX_TEST_MODE) {
		if (SYB_MaintenanceSwitch[MNT_SW_H0] & TEST_TPH_SYNC) {
			GaTphStatus = (TPH_EN				/* Thermal Head Control */
						   |TPH_SIZE_B4			/* B4 Head */
						   |TPH_STRSEL_4		/* ストローブ４分割 */
						   |TPH_STRPOL_NEG		/* ストローブ負論理 */
						   |TPH_DPOL_BLACK1		/* データ極性 白=0,黒=1 */
						   |TPH_CKSEL_3_5		/* 転送クロック 3.5MHz */
						   |TPH_DSIZE_B4		/* データサイズ B4 */
						   |TPH_MAINRC_OFF		/* 主走査縮小 OFF(Default) */
						   |TPH_RC_KEEP			/* 縮小補正　画素保存 */
						   |TPH_WMSK_OFF		/* 両端マスク OFF(Default) */
						   |(0x02 << 11)		/* 両端マスク幅 2mm(Default) */
						   |TPH_SYNC			/* 印可パルス SP_INT と同期 */
						   |TPH_LATPOL_NEG);	/* Latch 極性 負論理 */
		} else {
			GaTphStatus = (TPH_EN				/* Thermal Head Control */
						   |TPH_SIZE_B4			/* B4 Head */
						   |TPH_STRSEL_4		/* ストローブ４分割 */
						   |TPH_STRPOL_NEG		/* ストローブ負論理 */
						   |TPH_DPOL_BLACK1		/* データ極性 白=0,黒=1 */
						   |TPH_CKSEL_3_5		/* 転送クロック 3.5MHz */
						   |TPH_DSIZE_B4		/* データサイズ B4 */
						   |TPH_MAINRC_OFF		/* 主走査縮小 OFF(Default) */
						   |TPH_RC_KEEP			/* 縮小補正　画素保存 */
						   |TPH_WMSK_OFF		/* 両端マスク OFF(Default) */
						   |(0x02 << 11)		/* 両端マスク幅 2mm(Default) */
						   |TPH_ASYNC			/* 印可パルス SP_INT と非同期 */
						   |TPH_LATPOL_NEG);	/* Latch 極性 負論理 */
		}
	} else {
		GaTphStatus = (TPH_EN				/* Thermal Head Control */
					   |TPH_SIZE_B4			/* B4 Head */
					   |TPH_STRSEL_4		/* ストローブ４分割 */
					   |TPH_STRPOL_NEG		/* ストローブ負論理 */
					   |TPH_DPOL_BLACK1		/* データ極性 白=0,黒=1 */
					   |TPH_CKSEL_3_5		/* 転送クロック 3.5MHz */
					   |TPH_DSIZE_B4		/* データサイズ B4 */
					   |TPH_MAINRC_OFF		/* 主走査縮小 OFF(Default) */
					   |TPH_RC_KEEP			/* 縮小補正　画素保存 */
					   |TPH_WMSK_OFF		/* 両端マスク OFF(Default) */
					   |(0x02 << 11)		/* 両端マスク幅 2mm(Default) */
					   |TPH_ASYNC			/* 印可パルス SP_INT と非同期 */
					   |TPH_LATPOL_NEG);	/* Latch 極性 負論理 */
	}
#endif
	OutputWORD(GA_TPH_REG, GaTphStatus);

#if (0) /* 未使用です 1998/11/16 by T.Soneoka */
**	CurrentInt = CheckInterruptEnable();
**	CMN_DisableInterrupt();					/* Task Switching 防止のため */
**	Work = Input(IP_PPDR);
**	Work |= IO_BIT_RXMOTOR;
**	Output(IP_PPDR, Work);
**	if (CurrentInt) {
**		CMN_EnableInterrupt();
**	}
#endif

	/* この関数の先頭で割り込み禁止にしているのに、抜けしなに許可にしていない！
	** by O.Kimoto 1999/02/04
	*/
	if (CurrentInt) {
		CMN_EnableInterrupt();
	}

}


/*
 *	Name:	Set Printer Vertical Mode
 *	Create:	Wed Mar 18 16:12:30 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	SetPrinterVertialMode(
 *			UBYTE	Mode);	// SYS_* (see doc.h/送信モード)
 *	Description:
 *		プリンタの副走査モードを設定する
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetPrinterVerticalMode(UBYTE	Mode)
{
	BOOL	EnableInt;

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	Paper.Mode = Mode;
	switch (Mode) {
	case SYS_NORMAL:
		Paper.RewriteCount = 2;
		break;
	case SYS_FINE:
	case SYS_GRAY64:
		Paper.RewriteCount = 1;
		break;
	case SYS_SFINE:
		Paper.RewriteCount = 1;
		break;
	default:
		/* not reached */
		Paper.RewriteCount = 2;			/* for failsafe */
		break;
	}
	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}

void	SetDataSize(UBYTE	Size)
{
	BOOL	EnableInt;

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	GaTphStatus &= ~(TPH_DSIZE_A4 | TPH_DSIZE_B4);
#if (0)
**	switch (Size) {
**	case SYS_A4_PAPER:
**		GaTphStatus |= TPH_DSIZE_A4;		/* データサイズ A4 */
**		break;
**	case SYS_B4_PAPER:
**		GaTphStatus |= TPH_DSIZE_B4;		/* データサイズ B4 */
**		break;
**	}
#endif
	GaTphStatus |= TPH_DSIZE_B4;		/* データサイズ B4 */
	OutputWORD(GA_TPH_REG, GaTphStatus);

	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}


/*
 *	Name:	Set Horizontal Reduction
 *	Create:	Wed Apr  8 14:59:55 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	SetHorizontalReduction(UBYTE Reduction);
 *	Description:
 *		主走査縮小制御
 *		レジスタ MRDC1-6 に縮小パターンを設定
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetHorizontalReduction(
	UBYTE	Reduction)
{
	BOOL	EnableInt;
	UBYTE	TableIndex;

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	/* Set Reduction Pattern */
	TableIndex = (100 - Reduction);
	OutputWORD(GA_LINE_RDC1, HReductionPattern[TableIndex][0]);
	OutputWORD(GA_LINE_RDC2, HReductionPattern[TableIndex][1]);
	OutputWORD(GA_LINE_RDC3, HReductionPattern[TableIndex][2]);
	OutputWORD(GA_LINE_RDC4, HReductionPattern[TableIndex][3]);
	OutputWORD(GA_LINE_RDC5, HReductionPattern[TableIndex][4]);
	OutputWORD(GA_LINE_RDC6, HReductionPattern[TableIndex][5]);

	/* Reduction On or OFF */
	/*
	 *	サーマルヘッドの場合、
	 *	100% で、縮小オンは、回路的に怪しいので、使わない。
	 *	レフトマージン設定には、影響しないとのこと。(桐田談)
	 */
	GaTphStatus &= ~TPH_MAINRC_ON;
	if (Reduction != 100) {
		GaTphStatus |= TPH_MAINRC_ON;
	}
	OutputWORD(GA_TPH_REG, GaTphStatus);

	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}


/*
 *	Name:	Set Vertical Reduction
 *	Create:	Wed Apr  8 14:59:55 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	SetVerticalReduction(UBYTE Reduction);
 *	Description:
 *		副走査縮小制御
 *		レジスタ SRDC1-6 に縮小パターンを設定
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetVerticalReduction(
	UBYTE	Reduction)
{
	BOOL	EnableInt;
	UBYTE	TableIndex;

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	/* Set Reduction Pattern */
	TableIndex = (100 - Reduction);

	/* 副走査方向の縮小をソフトで間引いて実現するとき使用する変数 */
	CurrentVReductionPattern = (VReductionPattern[TableIndex][0] << 16);
	CurrentVReductionPattern |= VReductionPattern[TableIndex][1];
	VRductionBit = 0x00000001;
	ThinOutCount = 0;

	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}


/*
 *	Name:	Set White Mask Width
 *	Create:	Wed Apr  8 15:18:03 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	SetWhiteMaskWidth(UBYTE	Witdh);
 *	Description:
 *		両端マスク幅、2-15mm が設定可能
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetWhiteMaskWidth(
	UBYTE	Width)
{
	BOOL	EnableInt;

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	GaTphStatus &= ~TPH_WMSK_ON;
	if (Width != 0) {
		GaTphStatus |= TPH_WMSK_ON;
	}

	GaTphStatus &= ~TPH_WMSKW;
	if (Width <= 1) {
		Width = 2;
	}
	if (Width > 7) {
		Width = 7;
	}
	GaTphStatus |= (Width << 11);
	OutputWORD(GA_TPH_REG, GaTphStatus);

	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}


/*
 *	Name:	Set White Black Assign
 *	Create:	Wed Apr  8 15:24:51 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_if.h"
 *		void	SetWhiteBlackAssign(BOOL	Black1);
 *	Description:
 *		引数によって、黒と白の割当てを変える
 *		TRUE:	白(1),黒(0)
 *		FALSE:	白(0),黒(1)
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetWhiteBlackAssign(
	BOOL	Black0)
{
	BOOL	EnableInt;

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	GaTphStatus &= ~(TPH_DPOL_BLACK0|TPH_DPOL_BLACK1);
	if (Black0) {
		GaTphStatus |= TPH_DPOL_BLACK0;
	} else {
		GaTphStatus |= TPH_DPOL_BLACK1;
	}
	
	OutputWORD(GA_TPH_REG, GaTphStatus);

	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}


/*
 *	Name:	Query Printer Top Margin
 *	Create:	Mon May 18 14:25:53 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		UWORD	QueryPrinterTopMargin(void);
 *	Description:
 *		先端余白を設定値を獲る
 *		Laser Printer
 *			30 <= 設定値 = X(mm) x 23.1(line/mm) <= 255
 *		Thermal Head Printer
 *			制限無し。ただし、15.4line/mm(SFINE)換算
 *	Return Value:
 *		UWORD lines
 *	Change Log:
 *		
 */
WORD	QueryPrinterTopMargin(void)
{
	WORD	Margin;						/* DON'T Use Unsigned */

	Margin = 0;
	Margin += (WORD)(CHK_PrinterTopMergin() - 0x80);
	return	Margin;
}


/*
 *	Name:	Query Printer Bottom Margin
 *	Create:	Mon Jun 29 19:32:43 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		UWORD	QueryPrinterBottomMargin(void);
 *	Description:
 *		プリンタ後端余白の設定値を返す
 *	Return Value:
 *		UWORD
 *	Change Log:
 *		
 */
WORD	QueryPrinterBottomMargin(void)
{
	WORD	Margin;						/* DON'T Use Unsigned */

	Margin = 0;
	Margin += (WORD)(CHK_PrinterBottomMergin() - 0x80);
	return	Margin;
}


/*
 *	Name:	Inialize Printer Buffer
 *	Create:	Thu May 21 11:55:56 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	SetPriterSmoothing(UBYTE	Mode);
 *	Description:
 *		プリンタバッファ、スムージングバッファのアドレスカウンタを初期化し、
 *		スムージングバッファをクリアする。
 *		スムージングの有効無効を設定する。
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetPrinterSmoothing(
	UBYTE	Mode)
{
	UBYTE	*SmoothingBuf;
	WORD	Count;
	UBYTE	debug;
	
	debug = FALSE;
	
	/* Clear Smoothing Buffer */
	SmoothingBuf = &SmoothingBuffer[1][0];
	for (Count = 0; Count < 512; Count++) {
		*SmoothingBuf++ = 0x00;
	}
	GaPstartStatus = GA_PRINT_START;
	if (Mode == SYS_NORMAL && CHK_UNI_SmoothingNormal()) {
		GaPstartStatus |= (GA_PRINT_SMTH|GA_PRINT_SMTH2);
	}
	if (debug) {
		OutputWORD(GA_PSTART, GaPstartStatus);
	}
}

/*
 *	Name:	Select Printer DMA
 *	Create:	Thu May 21 13:42:51 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	SelectPrinterDma(void);
 *	Description:
 *		GateArray 設定 DMA Scanner/Printer 切替えをプリンタにする
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SelectPrinterDma(void)
{
	OutputWORD(GA_DMAR, (GA_DMA_ENABLE|GA_DMA_PRINTER));
}


/*
 *	Name:	Query Cassette Paper Size
 *	Create:	Tue Mar 17 16:46:52 1998	by	ishiyama
 *	Synopsis:
 *	Description:
 *	Return Value:
 *	Change Log:
 * 
 */
UBYTE	QueryRxPaperSize(void)
{
	return ((UBYTE)Paper.Size);
}



/*
 *	Name:	Query Exist Cassette Paper
 *	Create:	Tue Mar 17 16:12:07 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	ExistRxPaper(void);
 *	Description:
 *		Cassette Unit に記録紙があるか
 *	Return Value:
 *		TRUE:	ある
 *		FALSE:	ない
 *	Change Log:
 *		
 */
BOOL	ExistRxPaper(void)
{
	BOOL	Rslt;

	Rslt = FALSE;
	/*
	 *	Print 中はチェックすると、
	 *	最後の記録紙の半ばで紙なしを検出してしまうので、
	 *	プリント中はチェックしない
	 */
	if (CheckPrintablePosition()) {
		Rslt = TRUE;					
	}
	if (QueryPs1On()) {
		Rslt = TRUE;
	}
	return	Rslt;
}


/*
 *	Name:	Query Printer Cover Open
 *	Create:	Thu Apr 23 16:00:13 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	QueryPrinterCoverOpen(void);
 *	Description:
 *		プリンタのカバーをチェック
 *	Return Value:
 *		TRUE:	カバーが空いてる
 *		FALSE:	カバーが閉まってる
 *	Change Log:
 *		
 */
BOOL	QueryPrinterCoverOpen(void)
{
	BOOL	Rslt;

	Rslt = FALSE;

#if (0)
** 	/* トップカバーを開け閉めを連続的に繰り返すと、カバーがしまっているのに、
** 	** 「カバーを閉めてください」となり、マシーンステータスがたちっぱなしになる。
** 	** By O.Kimoto 1999/02/24
** 	*/
** 	if (InputWORD(GA_PGBDR) & IO_BIT_TOPOP) {
** 		Rslt = TRUE;
** 	}
#else
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {
		Rslt = TRUE;
	}
#endif


	return	Rslt;
}


