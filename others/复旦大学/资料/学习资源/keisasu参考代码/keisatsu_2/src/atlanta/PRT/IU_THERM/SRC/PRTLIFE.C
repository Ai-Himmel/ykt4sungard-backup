/*
 *	@(#)$Id: PRTLIFE.C,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	//jason/home2/prj/Eva/Src/prt/prtlife.c
 *	Create:	Thu Jul 23 17:18:47 1998	by	ishiyama
 *	Description:
 *		Printer Life Monitor
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"

/*
 *	Name:	Set Printer Page Count
 *	Create:	Thu Jul 23 19:55:08 1998	by	ishiyama
 *	Synopsis:
 *		#include	"prt_drv.h"
 *		void	SetPrinterPageCount(
 *			UBYTE	PaperSize);			// see prt_drv.h(PAPER_SIZE_*)
 *	Description:
 *		ƒvƒŠƒ“ƒ^ƒ‰ƒCƒtƒ‚ƒjƒ^‚Ìƒy[ƒWƒJƒEƒ“ƒg’l‚ðƒZƒbƒg‚·‚éB
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetPrinterPageCount(
	UBYTE	PaperSize)
{
	UBYTE	PageCount;

	PageCount = 1;
	SYB_LifeMonitor.PrintCount++;
	switch (PaperSize) {
	case PAPER_SIZE_A4:
		SYB_PrinterLifeMonitor.A4_TotalCount++;
		break;
	case PAPER_SIZE_B4:
		SYB_PrinterLifeMonitor.B4_TotalCount++;
		SYB_PrinterLifeMonitor.B4_PreCount++;

		/* ‚a‚S‚Í‚X–‡‚Å‚`‚S ‚P‚P–‡Š·ŽZ */
		if (SYB_PrinterLifeMonitor.B4_PreCount >= 9) {
			SYB_PrinterLifeMonitor.B4_PreCount = 0;
			PageCount += 2;
		}
		break;
	default:
		PageCount = 0;
		break;
	}

	if (PageCount != 0) {
		SYB_PrinterLifeMonitor.TotalPageCount += PageCount;
	}
}

