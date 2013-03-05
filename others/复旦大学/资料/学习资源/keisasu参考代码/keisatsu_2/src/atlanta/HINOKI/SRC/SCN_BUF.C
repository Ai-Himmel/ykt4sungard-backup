/*
 *	@(#)%W%
 *	FileName:	/home2/prj/Eva/Src/scn/scn_buf.c
 *	Create:	Tue Jan 13 19:54:21 1998	by	ishiyama
 *	Description:
 *		Scanner Buffer & Scanner Page Memory Control
 *		// Base Class
 *		class ImageRingBuf {
 *			const WORD	Width;					// 216 or 256 1ライン幅
 *			BOOL	EnableToWrite(void);		// 書込み可能？
 *			BOOL	EnableToRead(void);			// 読込み可能なデータあり？
 *			void	PutLine(UBYTE *Source, UWORD LineWidth);	// Source から1ライン分書込み
 *			UBYTE	GetLineAddress(void);		// 読出しアドレスの先頭番地を得る
 *		};
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\hinoki\ext_v\page_mem.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\scn_tbl.h"
#include "\src\atlanta\hinoki\ext_v\ga_buf.h"
#include "\src\atlanta\prt\iu_therm\define\prt_drv.h"
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\atlanta\define\mntsw_h.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\uni_pro.h" /* 1999/03/23 by T.Soneoka */
#include "\src\atlanta\define\mem_def.h" /* 1999/03/23 by T.Soneoka */
#include "\src\atlanta\ext_v\sys_data.h" /* 1999/03/23 by T.Soneoka */

static UBYTE	ScanBufWriteLine;		/* 次に書込むラインをポイント */
static UBYTE	ScanBufReadLine;		/* 次に読込むラインをポイント */
static UWORD	ScanBufReadableLine;	/* まだ読込まれてないライン数 */
static BYTE		ScanBufWriteClock;		/* GateArray が Write するタイミングを作る */
static UWORD	ScanPageMemWriteLine;	/* 次に書込むラインをポイント */

#if (0)
/* ソフトコーデック側でも参照しますので、大域変数に変更します。 By O.Kimoto 1998/10/02 */
static UWORD	ScanPageMemReadLine;	/* 次に読込むラインをポイント */
#else
UWORD	ScanPageMemReadLine = 0;	/* 次に読込むラインをポイント */
#endif

static UWORD	ScanPageMemReadableLine; /* まだ読込まれていないライン数 */
static UWORD	ScanPageMemDocWidth;	/* 原稿幅(転送バイト数) */

#if (0)	/* ゲートアレイ調査用  1998/09/02 by T.Soneoka */
**	UWORD GateArrayValue;
#endif
/****************************************************************************
 *	Scanner Buffer Control
 ****************************************************************************/
/*
 *	Name:	Initialize Scanner Buffer for Gate Array
 *	Create:	Wed Apr 22 11:49:05 GMT--9:00 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_buf.h"
 *		void	InzScanBuf4GateArray(void);
 *	Description:
 *		Scanner Buffer の設定情報を GateArray に書き込む
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	InzScanBuf4GateArray(void)
{
	if (CurrentPage->Size == SYS_DOCUMENT_A4_SIZE) {
		/* SH2.5ms, SPINT2.5ms, ImgBufEnable, 16本, A4 */
		GA_MWR_Status = ((UWORD)(((UDWORD)(&ScanBuf) & (MWR_IBADD << 1)) >> 1) | MWR_IBN_VALUE | MWR_IBEN);
	} else {
/*
** １．Ｇ／ＡへのデータがＡ４で、Ｇ／Ａ設定がＢ４の場合は、出力データが乱れる
** ２．Ｇ／ＡへのデータがＢ４で、Ｇ／Ａ設定がＡ４の場合の出力データは
**     １ライン先頭からＡ４分と、そこからＢ４分までのデータがずれる
**     <----------------B4------------>
**     <----------A4------------><---->
**     ○○○○○○○○○○○○○
**     ◎◎◎◎◎◎◎◎◎◎◎◎◎○○○
**     ●●●●●●●●●●●●●◎◎◎
**                               ●●●
** 1999/03/23 by T.Soneoka
*/
#if (0)
**		if (QueryRxPaperSize() == PAPER_SIZE_A4) {
**			/* SH2.5ms, SPINT2.5ms, ImgBufEnable, 16本, A4 */
**			GA_MWR_Status = ((UWORD)(((UDWORD)(&ScanBuf) & (MWR_IBADD << 1)) >> 1) | MWR_IBN_VALUE | MWR_IBEN);
**		} else {
**			/* SH2.5ms, SPINT2.5ms, ImgBufEnable, 16本, B4 */
**			GA_MWR_Status = ((UWORD)(((UDWORD)(&ScanBuf) & (MWR_IBADD << 1)) >> 1) | MWR_IBN_VALUE | MWR_IBEN | MWR_IBB4);
**		}
#else
		if (ScanReduction == REDUCTION_B4_A4) {
			/* SH2.5ms, SPINT2.5ms, ImgBufEnable, 16本, A4 */
			GA_MWR_Status = ((UWORD)(((UDWORD)(&ScanBuf) & (MWR_IBADD << 1)) >> 1) | MWR_IBN_VALUE | MWR_IBEN);
		} else {
			/* SH2.5ms, SPINT2.5ms, ImgBufEnable, 16本, B4 */
			GA_MWR_Status = ((UWORD)(((UDWORD)(&ScanBuf) & (MWR_IBADD << 1)) >> 1) | MWR_IBN_VALUE | MWR_IBEN | MWR_IBB4);
		}
#endif
	}
	OutputWORD(GA_MWR, GA_MWR_Status);
}


/*
 *	Name:	Initialize Scanner Buffer
 *	Create:	Wed Jan 14 10:16:41 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_buf.h"
 *		void	InzScannerBuffer(void);
 *	Description:
 *		スキャナバッファ初期化
 *		ページ毎,読取り開始前にコールされる
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	InzScanBuf(void)
{

	ScanBufWriteLine = 0;				/* 次に書込むラインをポイント */
	ScanBufReadLine = 0;				/* 本来読込めるラインをポイント */
	ScanBufReadableLine = 0;			/* まだ読込まれてないライン数 */
	ScanBufWriteClock = -1;
	InzScanBuf4GateArray();				/* GateArray 設定 */
}


/*
 *	Name:	Enable to Write Scanner Buffer
 *	Create:	Wed Jan 14 10:25:49 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_buf.h"
 *		BOOL	EnableToWriteScanBuf(void);
 *	Description:
 *		Scanner Buffer に書込み可能か？
 *	Notes:
 *		パイプライン処理になるため、
 *		7 line Margine を持つ。
 *	Return Value:
 *		TURE:	書込み可
 *		FALSE:	書込み不可
 *	Change Log:
 *		
 */
BOOL	EnableToWriteScanBuf(void)
{
	return	(ScanBufReadableLine < (SCANBUF_ROW - 7)) ? TRUE : FALSE;
}


/*
 *	Name:	Enable to Read Scanner Buffer
 *	Create:	Wed Jan 14 10:25:49 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_buf.h"
 *		BOOL	EnableToReadScanBuf(void);
 *	Description:
 *		Scanner Buffer から読込み可能か？
 *	Return Value:
 *		TURE:	読込み可
 *		FALSE:	読込み不可
 *	Change Log:
 *		
 */
BOOL	EnableToReadScanBuf(void)
{
	return	(ScanBufReadableLine > 0) ? TRUE : FALSE; /* 書込み終了のためのマージン１ライン */
}

BOOL	EnableStartToReadScanBuf(void)
{
	return	(ScanBufReadableLine > 2) ? TRUE : FALSE;
}



#if (0) /* 未使用 1998/12/09 by T.Soneoka */
**/*
** *	Name:	Put Line Scanner Buffer
** *	Create:	Wed Jan 14 13:42:31 1998	by	ishiyama
** *	Synopsis:
** *		#include	"scn_buf.h"
** *		void	PutLineScanBuf(
** *			UBYTE	*Source,	// ソースとなるイメージの先頭番地
** *			UWORD	LineWidth);	// 転送する1ラインのバイト数
** *	Description:
** *		Scanner Buffer に1ラインイメージを転送する。
** *	Return Value:
** *		void
** *	Change Log:
** *		
** */
**void	PutLineScanBuf(
**	UBYTE	*Source,					/* Source となる Image の先頭アドレス */
**	WORD	LineWidth)					/* 転送バイト数（1ラインの幅） */
**{
**	UBYTE	*Dest;						/* Destination Address */
**
**	Dest = &ScanBuf[ScanBufWriteLine][0];
**	if (++ScanBufWriteLine >= SCANBUF_ROW) {
**		ScanBufWriteLine = 0;
**	}
**	(void)MemoryCopy(Dest, Source, (UWORD)LineWidth);
**
**	ScanBufReadableLine++;
**}
#endif

/*
 *	Name:	
 *	Create:	Thu Mar 05 14:43:24 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_buf.h"
 *		void	AutoPutLineScanBuf(void);
 *	Description:
 *		GateArray による自動転送
 *		整合を取るために使用。
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	AutoPutLineScanBuf(void)
{
	BOOL	EnableInt;	/* 割り込み禁止処理入れます  1998/12/09 by T.Soneoka */

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	if (++ScanBufWriteLine >= SCANBUF_ROW) {
		ScanBufWriteLine = 0;
	}
	ScanBufReadableLine++;

	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}

/*
 *	Name:	Count Up ScanBuf Index
 *	Create:	Thu Mar 05 16:18:37 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_buf.h"
 *		void	CountUpScanBufIndex(void);
 *	Description:
 *		GateArray によるScanBuf への書込みに対応して
 *		カウントアップタイミングをはかり、更新する
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	CountUpScanBufIndex(void)
{
	if (!Query1_2Scan()) {
		if (ScanBufWriteClock <= 0) {
			ScanBufWriteClock++;
		} else {
			AutoPutLineScanBuf();
		}
	} else {
		if (ScanBufWriteClock <= 2) {	/* 初回はデータがまだ入ってない */
			ScanBufWriteClock++;
		} else {
			ScanBufWriteClock = 2;		/* 2回に1回だけカウントアップ */
			AutoPutLineScanBuf();
		}
	}
}


/*
 *	Name:	Get Line Address Scanner Buffer
 *	Create:	Wed Jan 14 13:42:31 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_buf.h"
 *		UBYTE	*GetLineAddress4ReadScanBuf(void);
 *	Description:
 *		Scanner Buffer から次のラインイメージのアドレスを得る。
 *	Return Value:
 *		次のラインの先頭番地
 *	Change Log:
 *		
 */
UBYTE	*GetLineAddress4ReadScanBuf(void)
{
	UBYTE	*ReadLinePointer;
	BOOL	EnableInt; 	/* 割り込み禁止処理入れます  1998/12/09 by T.Soneoka */

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	ReadLinePointer = &ScanBuf[ScanBufReadLine][0];
	if (++ScanBufReadLine >= SCANBUF_ROW) {
		ScanBufReadLine = 0;
	}

	if (EnableInt) {
		CMN_EnableInterrupt();
	}
	return	ReadLinePointer;
}


/****************************************************************************
 *	Scanner Page Memory Control
 ****************************************************************************/
/*
 *	Name:	Initialize Scanner Page Memory
 *	Create:	Tue Jan 13 19:55:20 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_buf.h"
 *		void	InzScanPageMem(void);
 *	Description:a
 *		Scanner Page Memory 初期化
 *		ページ毎,読取り開始前にコールされる
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	InzScanPageMem(void)
{
	ScanPageMemWriteLine = 0;
	ScanPageMemReadLine = 0;
	ScanPageMemReadableLine = 0;
	ScanPageMemEncodableLine = 0;	/* added by H.Hirao 1998/10/30 */
	switch (QueryCurrentDocSize()) {
	case SYS_DOCUMENT_A4_SIZE:
		ScanPageMemDocWidth = SYS_A4_PAGE_WIDTH;
		break;
	case SYS_DOCUMENT_B4_SIZE:
		ScanPageMemDocWidth = SYS_B4_PAGE_WIDTH;
		break;
	case SYS_DOCUMENT_A3_SIZE:
		ScanPageMemDocWidth = SYS_A3_PAGE_WIDTH;
		break;
	default:
		/* not reachable */
		break;
	}
}


/*
 *	Name:	Enable to Write Scanner Page Memory
 *	Create:	Wed Jan 14 10:25:49 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_buf.h"
 *		BOOL	EnableToWriteScanPageMem(void);
 *	Description:
 *		Scanner Page Memory に書込み可能か？
 *	Notes:
 *		追い越さないように 5 line マージンとして持つ
 *	Return Value:
 *		TURE:	書込み可
 *		FALSE:	書込み不可
 *	Change Log:
 *		
 */
BOOL	EnableToWriteScanPageMem(void)
{
	return	(ScanPageMemReadableLine < (SCANPAGE_ROW - 5)) ? TRUE : FALSE;
}


/*
 *	Name:	Enable to Read Scanner Page Memory
 *	Create:	Wed Jan 14 10:25:49 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_buf.h"
 *		BOOL	EnableToReadScanPageMem(void);
 *	Description:
 *		Scanner Page Memory から読込み可能か？
 *	Return Value:
 *		TURE:	読込み可
 *		FALSE:	読込み不可
 *	Change Log:
 *		
 */
BOOL	EnableToReadScanPageMem(void)
{
	return	(ScanPageMemReadableLine != 0) ? TRUE : FALSE;
}


/*
 *	Name:	Put Line Scanner Page Memory
 *	Create:	Tue Jan 13 20:02:48 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_buf.h"
 *		void	PutLineScanPageMem(
 *			UBYTE *Source);			// Image Data Source Address
 *	Description:
 *		Scanner Page Memory に Image を Write する
 *	Return Value:
 *		void
 *	Change Log:
 *		1998/05/20
 *			ループでの転送をやめ、アセンブラ化した転送ルーチンを使用。
 */
void	PutLineScanPageMem(
	UBYTE *Source)						/* Image Data Source Address */
{
	UBYTE	*Dest;						/* Destination Address */
	BOOL	EnableInt;

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();
	Dest = &ScanPageMem[ScanPageMemWriteLine][0];
	if (++ScanPageMemWriteLine >= SCANPAGE_ROW) {
		ScanPageMemWriteLine = 0;
	}
	if (EnableInt) {
		CMN_EnableInterrupt();
	}

	(void)MemoryCopy(Dest, Source, ScanPageMemDocWidth);

	CMN_DisableInterrupt();
	ScanPageMemReadableLine++;
	ScanPageMemEncodableLine++; /* added by H.Hirao 1998/10/30 */
	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}


/*
 *	Name:	Get Line Address Scanner Page Memory
 *	Create:	Tue Jan 13 20:02:48 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_buf.h"
 *		UBYTE	GetLineScanPageMem(void);
 *	Description:
 *		Scanner Page Memory から次のラインのアドレスを得る
 *	Return Value:
 *		次のラインの先頭番地
 *	Change Log:
 *		
 */
UBYTE	*GetLineAddress4ReadScanPageMem(void)
{
	UBYTE	*Address;
	BOOL	EnableInt; 	/* 割り込み禁止処理入れます  1998/12/09 by T.Soneoka */

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	if (ScanPageMemReadableLine > 0) {
		Address = &ScanPageMem[ScanPageMemReadLine][0];
		if (++ScanPageMemReadLine >= SCANPAGE_ROW) {
			ScanPageMemReadLine = 0;
		}
	} else {
		Address = (UBYTE *)0;
	}

	if (EnableInt) {
		CMN_EnableInterrupt();
	}

	return	Address;
}

void DecScanPageMemReadableLine(void)
{
	BOOL	EnableInt; 	/* 割り込み禁止処理入れます  1998/12/09 by T.Soneoka */

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	if (ScanPageMemReadableLine > 0) {
		ScanPageMemReadableLine--;
	}

	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}

void DecScanBufReadableLine(void)
{
	BOOL	EnableInt; 	/* 割り込み禁止処理入れます  1998/12/09 by T.Soneoka */

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	if (ScanBufReadableLine > 0) {
		ScanBufReadableLine--;
	}

	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}

void IncScanBufReadableLine(void)
{
	BOOL	EnableInt;	/* 割り込み禁止処理入れます  1998/12/09 by T.Soneoka */

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	ScanBufReadableLine++;

	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}

UBYTE *MemoryCopy(
UBYTE	*DST_ptr,	/* コピー先の先頭アドレス */
UBYTE	*SRC_ptr,	/* コピー元の先頭アドレス */
UWORD	CopyCount)		/* コピー数 */
{
	for ( ; CopyCount > 0; CopyCount--) {
			*DST_ptr++ = *SRC_ptr++;
	}
	return(DST_ptr);
}

UWORD QueryScanPageMemReadableLine(void)
{
	return (ScanPageMemReadableLine);
}
