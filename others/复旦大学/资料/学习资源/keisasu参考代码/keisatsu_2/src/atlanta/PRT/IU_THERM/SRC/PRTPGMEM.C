/*
 *	@(#)$Id: PRTPGMEM.C,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	/home2/prj/Eva/Src/prt/prtpgmem.c
 *	Create:	Thu Mar 26 15:39:57 1998	by	ishiyama
 *	Description:
 *		Page Memory Control Routines
 *		Page Memory を4分割して管理する
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\sysprint.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prn_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\mntsw_h.h"
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\ext_v\scn_dath.h"
#include "\src\atlanta\satsuki2\ext_v\ga_buf.h"
 #else
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\ga_buf.h"
 #endif

/*
 *	File Static Value
 */
static UWORD	PrtImageBufWriteLine;		/* 次に書込むラインをポイント */
static UWORD	PrtImageBufReadLine;		/* 本来読込めるラインをポイント */
static UWORD	PrtImageBufUsedCount;	/* まだ読込まれてないライン数 */
/*
 *	Function Prototypes (Use this file Only)
 */


/*
 *	Name:	Free Page Memory Block
 *	Create:	Fri Mar 27 11:26:11 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prtqueue.h"
 *		void	FreePageMemoryBlock(BYTE	BlockHandle);
 *	Description:
 *		引数のブロックから始まる Page Memory のブロックを解放する
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */


/*----------------------------------------------------------------------
 *	Page Memory Control for Non Sort Copy and Real Time Copy
 *----------------------------------------------------------------------*/
/*
 *	Name:	Initialize Print Image Buffer
 *	Create:	Fri May 29 14:27:32 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	InzPrintImgBuf(void);
 *	Description:
 *		プリンタバッファ初期化
 *		ページ毎,記録開始前にコールされる
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	InzPrtImageBuf(void)
{
	UBYTE	loop;
	UBYTE	dummyline;
	
	/* 高速ＳＲＡＭ ３２本 プリンタバッファ初期化 */
	for (loop = 0; loop < PRINT_IMAGE_BUF_LINE; loop++) {
		(void)CMN_WordMemorySet((UWORD *)&PRN_ImageBuffer1[loop][0], (UWORD)PRTPAGE_COL, 0x00);
	}
	
	PrtImageBufWriteLine = 0;				/* 次に書込むラインをポイント */
	PrtImageBufReadLine = 0;				/* 本来読込めるラインをポイント */
	PrtImageBufUsedCount = 0;			/* まだ読込まれてないライン数 */
	
#if (0) /* 1998/12/15 by T.Soneoka */
**	dummyline = 16;
**	while (dummyline--) {
**		/* 全白データセット */
**		(void)GetWritePtrPrtImageBuf();
**		IncPrtImageReadableLine();
**	};
#endif
}

/* 追加 1999/03/03 by T.Soneoka */
void	InzPrtImageBufLine(void)
{
	PrtImageBufWriteLine = 0;				/* 次に書込むラインをポイント */
	PrtImageBufReadLine = 0;				/* 本来読込めるラインをポイント */
	PrtImageBufUsedCount = 0;			/* まだ読込まれてないライン数 */
}

void	MakeDummyLine(void)
{
	UBYTE	dummyline;

	/* モードによってダミーラインを設定します 1999/1/13 by T.Soneoka */
	switch (PageQ.Mode) {
	case SYS_NORMAL:
		dummyline = 8;
		break;
	case SYS_FINE:
	case SYS_GRAY64:
		dummyline = 16;
		break;
	case SYS_SFINE:
		dummyline = 32;
		break;
	default:
		break;
	}
	
	while (dummyline--) {
		/* 全白データセット */
		(void)GetWritePtrPrtImageBuf();
		IncPrtImageReadableLine();
	};
}

/*
 *	Name:	Enable to Write Print Image Buffer
 *	Create:	Fri May 29 14:29:14 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	EnableToWritePrtImageBuf(void);
 *	Description:
 *		Print Image Buffer に書込み可能か？
 *	Notes:
 *		1 or 5 Line は、マージン
 *		2 or 5 Line は、マージン	マージン変更 by O.Kimoto 1998/10/27
 *	Return Value:
 *		TURE:	書込み可
 *		FALSE:	書込み不可
 *	Change Log:
 *		
 */
BOOL	EnableToWritePrtImageBuf(void)
{
	return	(PrtImageBufUsedCount < (PRT_BUF_WRITE_COUNT)) ? TRUE : FALSE;
}

/*
 *	Name:	Enable to Read Print Image Buffer
 *	Create:	Fri May 29 14:36:51 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		BOOL	EnableToReadPrtImageBuf(void);
 *	Description:
 *		Print Image Buffer から読込み可能か？
 *	Return Value:
 *		TURE:	読込み可
 *		FALSE:	読込み不可
 *	Change Log:
 *		
 */
BOOL	EnableToReadPrtImageBuf(void)
{
	BOOL	Rslt;

	Rslt = FALSE;
	if (QueryThinOutLine()) {
		/* 間引くときは、２ライン以上あること */
		if (PrtImageBufUsedCount >= 2) {
			Rslt = TRUE;
		}
	} else {
		/* プリント間欠印字テスト 1998/12/3 by T.Soneoka */
		if (SYB_MaintenanceSwitch[MNT_SW_H0] & RX_PRINT_OFF_AND_ON) {
			if (IsPrintWaitToPrtBufFul && (!IsPrintFinish)) {
				if (PrtImageBufUsedCount >= PRT_BUF_WRITE_COUNT) {
					IsPrintWaitToPrtBufFul = 0;
					Rslt = TRUE;
				}
			} else {
				if (PrtImageBufUsedCount > 1) {	/* 1998/10/29 by T.Soneoka 1ラインマージンを見る */
					Rslt = TRUE;
				} else {
					IsPrintWaitToPrtBufFul = 1;
				}
			}
		} else {
			if (PrtImageBufUsedCount > 1) {	/* 1998/10/29 by T.Soneoka 1ラインマージンを見る */
				Rslt = TRUE;
			}
		}
	}
	return	Rslt;
}


/*
 *	Name:	Query Write Address Print Image Buffer
 *	Create:	Fri May 29 14:43:44 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		UWORD	*QueryWritePtrPrtImageBuf(void);
 *	Description:
 *		Print Image Buffer の書込めるアドレスを獲る
 *	Notes:
 *		書込みが終れば、必ず IncPrtImageReadableLine(void) をコールすること
 *	Return Value:
 *		UWORD	*WritePointer
 *	Change Log:
 *		
 */
UWORD	*GetWritePtrPrtImageBuf(void)
{
	UWORD	*Dest;						/* Destination Address */
	BOOL	EnableInt;

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	Dest = ((UWORD *)&PRN_ImageBuffer1[PrtImageBufWriteLine][0+PRN_ImageBufferOffSet]);
	if (++PrtImageBufWriteLine >= PRINT_IMAGE_BUF_LINE) {
		PrtImageBufWriteLine = 0;
	}

	if (EnableInt) {
		CMN_EnableInterrupt();
	}

	return	Dest;
}


/*
 *	Name:	Increment Print Image Buffer Readable Line
 *	Create:	Fri May 29 14:50:08 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	IncPrtImageReadableLine(void);
 *	Description:
 *		読込めるライン数を増やす
 *	Notes:
 *		データ書込み完全終了後、コールすること
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	IncPrtImageReadableLine(void)
{
	BOOL	EnableInt;

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	PrtImageBufUsedCount++;

	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}


/*
 *	Name:	Get Read Pointer Printer Image Buffer
 *	Create:	Fri May 29 14:56:10 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		UWORD	*GetReadPtrPrtImageBuf(void);
 *	Description:
 *		Print Image Buffer から次のラインイメージのアドレスを得る。
 *	Notes:
 *		読み終ったら、必ず DecPrtImageReadableLine(void) をコールすること
 *		2 line 以上連続して読飛ばさないことを、前提条件としたルーチン。
 *		2 line 以上連続して間引く場合は、QueryThinOutLine() を if 文から for 文に換え、
 *		GetReadPtrPrtImageBuf 関数を呼び出す前のデータの有無の保証も変更する必要がある。
 *	Return Value:
 *		次のラインの先頭番地
 *	Change Log:
 *		
 */
#if (0) /* 1999/1/5 by T.Soneoka */
**UWORD	*GetReadPtrPrtImageBuf(void)
#else
UBYTE	*GetReadPtrPrtImageBuf(void)
#endif
{
#if (0) /* 1999/1/5 by T.Soneoka */
**	UWORD	*ReadLinePointer;
#else
	UBYTE	*ReadLinePointer;
#endif
	BOOL	EnableInt;		/* 割り込み禁止処理入れます  1998/12/09 by T.Soneoka */

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	if (QueryThinOutLine()) {
		/* 読み飛ばし処理 */
		if (++PrtImageBufReadLine >= PRINT_IMAGE_BUF_LINE) {
			PrtImageBufReadLine = 0;
		}
		UpdateThinOutLine();
		DecPrtImageReadableLine();
	}

#if (0) /* 1999/1/5 by T.Soneoka */
**	ReadLinePointer = ((UWORD *)&PRN_ImageBuffer1[PrtImageBufReadLine][0]);	/* このまま By O.Kimoto 1998/11/10 */
#else
	ReadLinePointer = ((UBYTE *)&PRN_ImageBuffer1[PrtImageBufReadLine][0]);	/* このまま By O.Kimoto 1998/11/10 */
#endif
	if (++PrtImageBufReadLine >= PRINT_IMAGE_BUF_LINE) {
		PrtImageBufReadLine = 0;
	}
	UpdateThinOutLine();

	if (EnableInt) {
		CMN_EnableInterrupt();
	}

	return	ReadLinePointer;
}


/*
 *	Name:	Decrement Print  Image Readable Line Count
 *	Create:	Fri May 29 14:59:12 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	DecPrtImageReadableLine(void);
 *	Description:
 *		読込み可能ライン数をデクリメント
 *	Notes:
 *		データ読込み完全終了後、コールすること
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	DecPrtImageReadableLine(void)
{
	BOOL	EnableInt; 	/* 割り込み禁止処理入れます  1998/12/09 by T.Soneoka */

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();

	if (PrtImageBufUsedCount > 0) {
		PrtImageBufUsedCount--;
	}

	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}


/*
 *	for Copy
 */
void	OpenPrtImageBuf4Copy(void)
{
	IsPrintFinish = FALSE;
#if (0) /* 1998/12/15 by T.Soneoka */
**	InzPrtImageBuf();
#endif
#if (0) /* 1998/12/15 by T.Soneoka */
**	while (Paper.Position != PAPER_POS_PRINTING) {
#else
	while (!EnablePrintDataMake) {/* プリントデータ作成開始許可になるまで待ちます 1998/12/15 by T.Soneoka */
#endif
		if (PrinterError != 0 || PrinterStopProcess) {
			/* Error またはストップならば抜ける */
			break;
		}
		wai_tsk(10);
	}
}


void	ClosePrtImageBuf4Copy(void)
{
	UBYTE nextpage_check;
	
	nextpage_check = FALSE;

	if (PrinterUseMode == PRINT_SCOPY) {
		if (IsDocument) {
			nextpage_check = TRUE;
		}

		IsPrintFinish = TRUE;

#if defined(SATSUKI2)	/* 壁掛け設定用に追加 by Y.Kano 2003/10/08 */
		if (CHK_WallHangSetting()) { /** 壁掛け設定 */	/* Add by Y.kano 2003/10/08 */
			do {
				if (PrinterError != 0 || PrinterStopProcess) {
					/* Error またはストップならば抜ける */
					break;
				} else {
					wai_tsk(1);
				}
				/* リアルタイムコピー時は、ここで次の原稿があるかないか見るようにします 1999/1/19 by T.Soneoka */
				if (nextpage_check) {
					if (QueryDs1On()) {
						if (NoNextDocument == TRUE) {
							IsDocument = FALSE;
						}
						else {
							IsDocument = TRUE;
						}
					} else {
						IsDocument = FALSE;
					}

				}
			} while ((Paper.Position == PAPER_POS_PRINTING)
		    	 ||  (Paper.Position == PAPER_POS_MOVE_TO_CUT));
		}
		else {
			do {
				if (PrinterError != 0 || PrinterStopProcess) {
					/* Error またはストップならば抜ける */
					break;
				} else {
					wai_tsk(1);
				}
				/* リアルタイムコピー時は、ここで次の原稿があるかないか見るようにします 1999/1/19 by T.Soneoka */
				if (nextpage_check) {
					if (QueryDs1On()) {
						if (NoNextDocument == TRUE) {
							IsDocument = FALSE;
						}
						else {
							IsDocument = TRUE;
						}
					} else {
						IsDocument = FALSE;
					}

				}
			} while ((Paper.Position == PAPER_POS_PRINTING)
		    	 ||  (Paper.Position == PAPER_POS_MOVE_TO_CUT)
			     ||  (Paper.Position == PAPER_POS_MOVE_TO_PS2));
		}
#else	/* SATSUKI2以外 */
		do {
			if (PrinterError != 0 || PrinterStopProcess) {
				/* Error またはストップならば抜ける */
				break;
			} else {
				wai_tsk(1);
			}
			/* リアルタイムコピー時は、ここで次の原稿があるかないか見るようにします 1999/1/19 by T.Soneoka */
			if (nextpage_check) {

#if (0)
** 				/* 仕様変更
** 				** 読み取り中において、ＤＳ２がＯＦＦした時点でＤＳ１もＯＦＦしていれば、今読んだ原稿が
** 				** 最終原稿であるという風に変更
** 				** by O.kimoto 1999/03/08
** 				*/
** 				if (QueryDs1On()) {
** 					IsDocument = TRUE;
** 				} else {
** 					IsDocument = FALSE;
** 				}
#else
				if (QueryDs1On()) {
					if (NoNextDocument == TRUE) {
						IsDocument = FALSE;
					}
					else {
						IsDocument = TRUE;
					}
				} else {
					IsDocument = FALSE;
				}
#endif

			}
		} while ((Paper.Position == PAPER_POS_PRINTING)
		     ||  (Paper.Position == PAPER_POS_MOVE_TO_CUT)
		     ||  (Paper.Position == PAPER_POS_MOVE_TO_PS2));
#endif	/* End of defined(SATSUKI2) */
		/* Endmark3 
		** エンドマーク検出時に、１ページ余分に排出されるので、ここで、次原稿無しに強制的にします。
		** by O.Kimoto 1999/02/19
		*/
		if (EndMarkDetect == TRUE) {
			IsDocument = FALSE;
		}
		
	} else {
		if (Paper.Phase == PAPER_PHASE_PRINT) {
			IsPrintFinish = TRUE;
			do {
				if (PrinterError != 0 || PrinterStopProcess) {
					/* Error またはストップならば抜ける */
					break;
				} else {
					wai_tsk(1);
				}
			} while (Paper.Phase == PAPER_PHASE_PRINT);
		}
	}
}


void	PutLinePrintPageMem(
	UBYTE	*Source,
	UBYTE	Size)
{
	if (Size == SYS_DOCUMENT_A4_SIZE) {
		if (Paper.Size == PAPER_SIZE_A4) {
			/* Scan:A4 Print:A4の場合はB4-A4分オフセットをつけます */
			(void)MemoryCopy((UBYTE *)QueryImageStartPointer()+OffsetA4, Source, (UWORD)SYS_A4_PAGE_WIDTH);
		} else {
			/* Scan:A4 Print:B4の場合は左詰めにします */
			(void)MemoryCopy((UBYTE *)QueryImageStartPointer(), Source, (UWORD)SYS_A4_PAGE_WIDTH);
		}
	} else {
		if (Paper.Size == PAPER_SIZE_A4) {
			/* Scan:B4 Print:A4の場合はB4-A4分オフセットをつけます */
			(void)MemoryCopy((UBYTE *)QueryImageStartPointer()+OffsetA4, Source, (UWORD)SYS_A4_PAGE_WIDTH);
		} else {
			/* Scan:B4 Print:B4の場合 */
			(void)MemoryCopy((UBYTE *)QueryImageStartPointer(), Source, (UWORD)SYS_B4_PAGE_WIDTH);
		}
	}
	(void)PrintLine();
}

#if (0)
** BOOL	EnableToReadPrintImageBuf(void)
** {
** 	return	(PrtImageBufReadLine > 0) ? TRUE : FALSE;
** }
#endif


BOOL	EnableToWritePrtImageBuf4Copy(void)
{
	return	(PrtImageBufUsedCount < (PRINT_IMAGE_BUF_LINE - 5)) ? TRUE : FALSE;
}	

int GetPrtImageBufWriteLineNo(void)
{
	return((int)PrtImageBufWriteLine);
}

UWORD GetPrtImageBufUsedCount(void)
{
	return (PrtImageBufUsedCount);
}
