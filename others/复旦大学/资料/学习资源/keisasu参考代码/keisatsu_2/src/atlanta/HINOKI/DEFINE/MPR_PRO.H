/*
**	%W%
**	File Name:	\prj\Eva\src\inc\cmnuni_e.h
**	Create:	1998/01/05	by Masahiro,IIDA
**	Description:
**		ã@éÌå≈óLÉXÉCÉbÉ`EÇÃê›íËèÛë‘ÇälìæÇ∑ÇÈä÷êî
**		êèéûí«â¡ÇµÇƒÇ¢Ç¡ÇƒÇ≠ÇæÇ≥Ç¢ 1998/09/30 by T.Soneoka
**	Changes:
**
*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"

UBYTE	CHK_PrinterTopMergin(void);
#if (0) /* 1998/12/25 by T.Soneoka */
**UBYTE	CHK_PrinterLeftMergin(void);
#endif
UBYTE	CHK_PrinterMask(void);
UBYTE	CHK_FeedAfterPS2On(void);
UBYTE	CHK_PrinterBottomMergin(void);
UBYTE	CHK_PrinterMaskWhite(void);
BOOL	CHK_2ChiEmphasizeFilter(void);
BOOL	CHK_GrayEmphasizeFilter(void);
BOOL	CHK_GosaMoveMatrix(void);
UBYTE	CHK_WeightValue(void);
BOOL	CHK_ZouikiBunri(void);
BOOL	CHK_ZouikiSelector(void);
BOOL	CHK_CharAreaWindowExtend(void);
BOOL	CHK_AmitenDetect(void);
BOOL	CHK_HalfToneSwitch(void);
UBYTE	CHK_PreFilter(void);
UBYTE	CHK_Transform(void);
UBYTE	CHK_HReductionMethod(void);
BOOL	CHK_VReductionMethod(void);
UBYTE	CHK_Hfmy(void);
UBYTE	CHK_Hfmx(void);
UBYTE	CHK_Bfmy(void);
UBYTE	CHK_Bfmx(void);
UBYTE	CHK_EdgeDetectLevel(void);
UBYTE	CHK_AmitenThresholdLevel(void);
UBYTE	CHK_AmitenEdgePare(void);
BOOL	CHK_BinaryThresholdMethod(void);
UBYTE	CHK_QueryGammaValue(
	BOOL	Gray,						/* Gray Scale or not */
	UBYTE	Density,					/* îZìxê›íË */
	UBYTE	Point);						/* 00h-ffh */
BYTE	CHK_QueryAgcHighRefOffset(void);
BYTE	CHK_QueryAgcLowRefOffset(void);
WORD	CHK_QueryScanTopAdjust(void);
WORD	CHK_QueryScanEndAdjust(void);
UBYTE	CHK_QueryScanMaskAdjust(void);
UBYTE	CHK_SP_Test(void);
BYTE	CHK_GammaShift(void); /* 1999/06/29 by T.Soneoka */
UBYTE	CHK_QueryGammaDataSpecial(void); /* 1999/06/29 by T.Soneoka */
BYTE	CHK_SliceLevelForNormTx(void); /* 1999/06/29 by T.Soneoka */
#if (PRO_RED_SCAN == ENABLE)	/* éÈêFå¥çeì«Ç›éÊÇË 2002/03/23 T.Takagi */
BYTE	CHK_AgcHighRefOffsetForRedScan(void);
UBYTE	CHK_BfmyForRedScan(void);
UBYTE	CHK_BfmxForRedScan(void);
BYTE	CHK_GammaShiftForRedScan(void);
#endif

#if defined (KEISATSU) /* åxé@FAX 05/06/17 êŒã¥ê≥òa */
BOOL CHK_ScrambleAvailabe(void);
BOOL CHK_BypassS1(void);
BOOL CHK_IgnoreS1Error(void);
UBYTE CHK_IsseiSpeed(void);
UBYTE CHK_IsseiCodingMethod(void);
UBYTE CHK_IsseiMinimumScanningTime(void);
UWORD CHK_IsseiRxTimeout(void);
#endif

