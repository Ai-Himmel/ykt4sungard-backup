/*
 *	@(#)%W%
 *	FileName:	/home2/prj/Eva/Src/scn/scn_doc.c
 *	Create:	Tue Jan  6 11:15:20 1998	by	ishiyama
 *	Description:
 *		Feeder Document Class
 *	Change Log:
 *		\prj\eva\src\scn\scn_doc.cÇ©ÇÁÉRÉsÅ[ÇµÅAHINOKIópÇ…ÉÅÉìÉeÇµÇ‹ÇµÇΩ
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\mntsw_c.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\scn_tbl.h"
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"
#include "\src\atlanta\prt\iu_therm\define\prt_drv.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\ext_v\cl1_data.h" /* by H.Hirao 1999/01/26 */
#endif
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include "\src\atlanta\define\mntsw_h.h"

/*
 *	Name:	Query Feeder Document Width
 *	Create:	Tue Jan  6 11:16:38 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BYTE	QueryFeederDocSize(void);
 *	Description:
 *		Feeder ÇÃå¥çeïùÇï‘Ç∑ÅB
 *	Return Value:
 *		SYS_DOCUMENT_A4_SIZE		0	A4 Document
 *		SYS_DOCUMENT_B4_SIZE		1   B4 Document
 *		SYS_DOCUMENT_A3_SIZE		2	A3 Document //ñ¢égóp
 *	Change Log:
 *		
 */
BYTE	QueryFeederDocSize(void)
{
	BYTE	Size;

	Size = SYS_DOCUMENT_A4_SIZE;
#if (PRO_SCAN_WIDTH == B4WIDTH)
	/* ç≈ëÂå¥çeì«Ç›éÊÇËïù */
	/* B4 ÉZÉìÉTÇ™Ç†ÇÍÇŒÅAà»â∫Çê∂Ç©Ç∑ */
	if (QueryDsB4On()) {
		Size = SYS_DOCUMENT_B4_SIZE;
	}
#endif
	return	Size;
}

/*
 *	Name:	Query Current Document Size
 *	Create:	Mon Feb  23 13:56:38 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BYTE	QueryCurrentDocSize(void);
 *	Description:
 *		Feeder ÇÃå¥çeïùÇï‘Ç∑ÅB
 *	Return Value:
 *		SYS_DOCUMENT_A4_SIZE		0	A4 Document
 *		SYS_DOCUMENT_B4_SIZE		1   B4 Document
 *		SYS_DOCUMENT_A3_SIZE		2	A3 Document //ñ¢égóp
 *	Change Log:
 *		
 */
BYTE	QueryCurrentDocSize(void)
{
	return	CurrentPage->Size;
}


/*
 *	Name:	Query Current Document Resolution(Norm/Fine/Sfine)
 *	Create:	Fri Feb 13 14:44:38 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BYTE	QueryDocMode(void);	
 *	Description:
 *		åªç›ÇÃå¥çeÇÃëóêM(or COPY)ÉÇÅ[ÉhÇï‘Ç∑
 *	Return Value:
 *		(doc.h éQè∆)
 *		SYS_NORMAL
 *		SYS_FINE
 *		SYS_SFINE
 *		SYS_GRAY64
 *	Change Log:
 *		
 */
BYTE	QueryDocMode(void)
{
	BYTE	rtn;

	if (CurrentPage == NULL) {
		rtn = SYS_NORMAL;				/* for fail safe */
	} else {
		rtn = CurrentPage->Mode;
	}
	return	rtn;
}

/*
 *	Name:	Query More Document
 *	Create:	Mon Feb  2 16:56:37 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	QueryMoreDoc(void);
 *	Description:
 *		
 *	Return Value:
 *		TRUE:	Exist Next Page
 *		FALSE:	No more Pages
 *	Change Log:
 *		
 */
BOOL	QueryMoreDoc(void)
{
	if (NextPage != NULL) {
		return	TRUE;
	} else {
		return	FALSE;
	}
}


/*
 *	Name:	Query Document Current Position
 *	Create:	Mon Feb  2 17:00:49 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BYTE	QueryDocPosition(void);
 *	Description:
 *		Current Document ÇÃà íuÇï‘Ç∑
 *	Return Value:
 *		DOC_POS_*	(feeder.h)
 *	Change Log:
 *		
 */
BYTE	QueryDocPosition(void)
{
	if (CurrentPage == NULL) {
		return	DOC_POS_NO_DOCUMENT;
	} else {
		return	CurrentPage->Position;
	}
}

/*
 *	Name:	Query Document Scannable
 *	Create:	Mon Feb  9 16:10:31 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	QueryDocScannable(void);
 *	Description:
 *		å¥çeÇ™ì«éÊÇËâ¬î\Ç»à íuÇ…Ç†ÇÈÇ©ÅB
 *	Return Value:
 *		TRUE:	ì«éÊÇËâ¬î\
 *		FALSEÅF	ì«éÊÇËïsâ¬
 *	Change Log:
 *		
 */
BOOL	QueryDocScannable(void)
{
	BOOL	Rslt;
	BYTE	Pos;
	UBYTE	debug;
	
	Rslt = FALSE;

	Pos = QueryDocPosition();
	if (Pos == DOC_POS_SCANNING || Pos == DOC_POS_SCAN_FEEDOUT) {
		/*
		 * éüÉyÅ[ÉWÇ™Ç∑Ç≈Ç…ì«éÊÇËà íuÇ…Ç´ÇƒÇÈèÍçá
		 * àÍíUÅAì«éÊÇËÇí‚é~Ç∑ÇÈ
		 */
		if (!SCN_DocumentChanged) {
			Rslt = TRUE;
		}
	}
	return	Rslt;
}

/*
 *	Name:	Query Store Coding Mode
 *	Create:	Wed Jan  7 16:21:36 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		UBYTE	QueryStoreCode(void);
 *	Description:
 *		í~êœÇ∑ÇÈÉRÅ[ÉfÉBÉìÉOÉÇÅ[ÉhÇï‘Ç∑
 *	Return Value:
 *		doc.h éQè∆
 *		IMAGE_DATA	0	// ñ¢égóp
 *		MH_CODE		1	// ñ¢égóp
 *		MR_CODE		2
 *		MMR_CODE	3
 *	Change Log:
 *		
 */
UBYTE	QueryStoreCode(void)
{
#if (PRO_CLASS1 == ENABLE) /* by H.Hirao 1999/01/26 */
	if (QueryClass1Tx()) {
		CL1_Code = CL1_PCDocumentCode;
		return (CL1_Code);
	}
	else {
		switch (QueryStoreMode()) {
		case	SYS_NORMAL:
		case	SYS_FINE:
		case	SYS_SFINE:
		case	SYS_HFINE:
		case	SYS_EFINE:
			return((UBYTE)(SYB_MaintenanceSwitch[MNT_SW_C3] & DOC_STORE_CODING_METHOD));
			break;
		default:			/* ÇªÇÃëº(íÜä‘í≤) */
			return((UBYTE)((SYB_MaintenanceSwitch[MNT_SW_C3] & DOC_STORE_CODING_METHOD_GRAY)>>3));
		}
	}
#else
	switch (QueryStoreMode()) {
	case	SYS_NORMAL:
	case	SYS_FINE:
	case	SYS_SFINE:
	case	SYS_HFINE:
	case	SYS_EFINE:
		return((UBYTE)(SYB_MaintenanceSwitch[MNT_SW_C3] & DOC_STORE_CODING_METHOD));
		break;
	default:			/* ÇªÇÃëº(íÜä‘í≤) */
		return((UBYTE)((SYB_MaintenanceSwitch[MNT_SW_C3] & DOC_STORE_CODING_METHOD_GRAY)>>3));
	}
#endif
}



/*
 *	Name:	Query Stored Mode
 *	Create:	Wed Jan  7 16:29:24 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BYTE	QueryStoreMode(void);
 *	Description:
 *		å¥çeì«éÊÇËÉÇÅ[ÉhÇï‘Ç∑
 *	Return Value:
 *		doc.h éQè∆
 *		SYS_NORMAL		0  // ïÅí 	   200dpi:8 dot/m  100dpi:3.85ñ{/l
 *		SYS_FINE		1  // çÇâÊéø   200dpi:8 dot/m  200dpi:7.7 ñ{/l
 *		SYS_SFINE		2  // í¥çÇâÊéø 200dpi:8 dot/m  400dpi:15.5ñ{/l
 *		SYS_GRAY64		3  // 64äKí≤   200dpi:8 dot/m  200dpi:7.7 ñ{/l
 *	Change Log:
 *		
 */
BYTE	QueryStoreMode(void)
{
	BYTE	Mode;

	Mode = SYB_ModeSw;
	/*
	 *	Real Time Copy ÇÕÅANormalÇÕÇ»Ç¢
	 */
	if (ScannerMode == SCANNER_COPY_MODE) {
		if (Mode == SYS_NORMAL) {
			Mode = SYS_FINE;
		}

		/* ãûÉZÉâÇsÇoÇgïsãÔçáëŒâû
		** ÇsÇoÇgÉTÅ[É~ÉXÉ^åüèoÇ™àÍíËâ∑ìxà»â∫ÅiílÇsà»è„ÅjÇÃéûÇÕÅAÇrÇeÇhÇmÇdÉÇÅ[ÉhÇ≈é¿çsÇ∑ÇÈ
		** ÅÅã≠êßìIÇ…ÉvÉäÉqÅ[ÉgÅiéûä‘ÇîÅjÇë}ì¸Ç∑ÇÈ
		** Çs Ç®ÇÊÇ— Çî ÇÕÉÅÉÇÉäÉXÉCÉbÉ`Ç…ÇÊÇËâ¬ïœÇ∆ÇµÇƒâ∫Ç≥Ç¢ÅD
		** ÉfÉtÉHÉãÉgílÇÕÅAà»â∫ÇÃílÇ∆ÇµÇƒâ∫Ç≥Ç¢
		** ÇsÅÅÇSÇUÅiÇQÇdÇàÅjÅ@Å@Å@ÇQÇOÅéÅiîªíËílÇSÇUà»è„Ç≈ÇQÇOÅéà»â∫Ç≈Ç∑Åj
		** ÇîÅÅÇTÇOÅiÇRÇQÇàÅjÅ@Å@Å@ÇOÅDÇTÇçÇì
		** 1999/03/15 í«â¡ by T.Soneoka
		*/
		if (Mode == SYS_FINE) {
			if (HeadMaker == HEAD_KYOCERA) {
				ThermistorValue = AD_Thermistor();
				if (ThermistorValue >= (SYB_MaintenanceSwitch[MNT_SW_H2]*4)) {
					Mode = SYS_SFINE;
				}
			}
		}
		/** Ç±Ç±Ç‹Ç≈ */
	}
#if (PRO_CLASS1 == ENABLE) /* by H.Hirao 1999/01/26 */
	if (QueryClass1Tx()) {
		CL1_Mode = CL1_PCDocumentMode;
		if (CL1_Mode < SYS_FINE) {
			Mode = CL1_Mode;
		}
		else if (CL1_Mode == SYS_FINE) {
			if ((Mode == SYS_GRAY64)
			 || (Mode == SYS_NORMAL)
			 || (Mode == SYS_FINE)) {
				CL1_Mode = Mode;
			}
			else {
				Mode = CL1_Mode;
			}
		}
		else {
			if ((Mode == SYS_GRAY64)
			 || (Mode == SYS_NORMAL)
			 || (Mode == SYS_FINE)) {
				CL1_Mode = Mode;
			}
			else {
				Mode = CL1_Mode;
			}
		}
	}
#endif
	return	Mode;
}


/*
 *	Name:	Query Class1 Tx
 *	Create:	Wed Feb  23 15:55:18 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	QueryClass1Tx(void);
 *	Description:
 *		ÉNÉâÉX1Ç©î€Ç©Çï‘Ç∑
 *	Return Value:
 *		TRUE:	Class 1
 *		FALSE:	Not Class 1
 *	Change Log:
 *		
 */
BOOL	QueryClass1Tx(void)
{
	/* TBD */
#if (PRO_CLASS1 == ENABLE) /* by H.Hirao 1999/01/26 */
	if (SYS_DocumentStoreItem == SYS_MEM_CLASS1_TX_FILE) {
		return TRUE;
	}
	else {
		return FALSE;
	}
#else
	return	FALSE;
#endif
}


/*
 *	Name:	Query Adjuct Document Size
 *	Create:	Wed Jan  7 16:36:18 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BYTE	QueryAdjustDocSize(void);
 *	Description:
 *		ÉNÉâÉXÇPÇ‡â¡ñ°ÇµÇΩÉhÉLÉÖÉÅÉìÉgÉTÉCÉYÇï‘Ç∑ÅB
 *		ÉNÉâÉX1Ç©î€Ç©,PC ë§ÇÃî\óÕÇ™ê›íËçœÇ≈Ç†ÇÈÇ±Ç∆ÅB
 *	Return Value:
 *		doc.h éQè∆
 *		SYS_DOCUMENT_A4_SIZE
 *		SYS_DOCUMENT_B4_SIZE
 *		SYS_DOCUMENT_A3_SIZE
 *	Change Log:
 *		
 */
BYTE	QueryAdjustDocSize(void)
{
	BYTE	Size;
	BYTE	FeederDocSize;

	FeederDocSize = QueryFeederDocSize();
#if (PRO_CLASS1 == ENABLE)
	if (QueryClass1Tx()) {				/* TBD */
		if (FeederDocSize == SYS_DOCUMENT_A4_SIZE
			|| PcDocumentSize == SYS_DOCUMENT_A4_SIZE) {	
			Size = SYS_DOCUMENT_A4_SIZE;
		} else if (FeederDocSize == SYS_DOCUMENT_B4_SIZE
				   || PcDocumentSize == SYS_DOCUMENT_B4_SIZE) {
			Size = SYS_DOCUMENT_B4_SIZE;
		} else {
			Size = SYS_DOCUMENT_A3_SIZE;
		}
	} else {
		Size = FeederDocSize;
	}
#else
	Size = QueryFeederDocSize();
#endif	/* PRO_CLASS1 == ENABLE */

	return	Size;
}



/*
 *	Name:	Query Stored Document Density
 *	Create:	Wed Jan  7 16:58:34 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BYTE	QueryStoreDensity(void);	
 *	Description:
 *		í~êœå¥çeÇÃîZìxÇï‘Ç∑
 *	Return Value:
 *		SYS_LIGHT_DENSITY			0	// îñÇ≠
 *		SYS_NORMAL_DENSITY			2	// ïÅí 
 *		SYS_DARK_DENSITY			4	// îZÇ≠
 *	Change Log:
 *		
 */
BYTE	QueryStoreDensity(void)
{
	return	SYB_DensitySw;
}


/*
 *	Name:	Query 1/2 Scan
 *	Create:	Thu Mar 05 15:25:40 1998	by	ishiyama
 *	Synopsis:
 *		#inlucde	"feeder.h"
 *		BOOL	Query1_2Scan(void);
 *	Description:
 *		1/2 Scan or not
 *	Return Value:
 *		TURE:	1/2 Scan
 *		FALSE:	Normal Scan
 *	Change Log:
 *		
 */
BOOL	Query1_2Scan(void)
{
	if (CurrentPage == NULL) {
		return	FALSE;					/* for Fail safe */
	}

	if (CurrentPage->VerticalMode == TX_MOTOR_FINE1_2_SCAN
		|| CurrentPage->VerticalMode == TX_MOTOR_SFINE1_2_SCAN) {
		return	TRUE;
	} else {
		return	FALSE;
	}
}



BOOL	QueryDocumentChanged(void)
{
	return	SCN_DocumentChanged;
}

	
/*
 *	method
 */
/*
 *	Name:	Initialize Document Objects
 *	Create:	Fri Jan 30 16:35:20 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		void	InzDocObj(void);
 *	Description:
 *		å¥çeÉIÉuÉWÉFÉNÉgÇèâä˙âª
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	InzDocObj(void)
{
	ScanPage[0].Object = FALSE;
	ScanPage[1].Object = FALSE;
	CurrentPage = NULL;
	NextPage = NULL;
}

/*
 *	Name:	Create Document Object
 *	Create:	Fri Jan 30 16:19:17 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		struct ScanPageAtr *	CreateDocObj(void);
 *	Description:
 *		Document Object ÇçÏê¨Çµ,ÇªÇÃÉ|ÉCÉìÉ^Çï‘Ç∑
 *	Return Value:
 *		struct ScanPageAtr *
 *	Change Log:
 *		
 */
struct ScanPageAtr *CreateDocObj(void)
{
	struct ScanPageAtr	*Page;
	BOOL	CurrentInt;

	CurrentInt = CheckInterruptEnable();	/* åªç›ÇÃäÑÇËçûÇ›èÛë‘Çï€ë∂ */
	CMN_DisableInterrupt();	/* äÑÇËçûÇ›ã÷é~ */
	Page = NULL;
	if (!ScanPage[0].Object) {
		Page = &ScanPage[0];
	} else if (!ScanPage[1].Object) {
		Page = &ScanPage[1];
	}
	if (Page != NULL) {
		Page->Object = TRUE;
		Page->Position = DOC_POS_MOVE_TO_DS2;
		Page->StepsFromDs1On = 0;
		Page->StepsFromDs2On = 0;
		Page->StepsFromDs2Off = 0;
		Page->Ds2ToScanSteps = Ds2ToScanSteps; /* default Value */
		Page->Ds2ToScanEndSteps = Ds2ToScanEndSteps; /* default Value */
	}
	if (CurrentInt) {
		CMN_EnableInterrupt();	/* äÑÇËçûÇ›ãñâ¬ */
	}

	return	Page;
}

/*
 *	Name:	Delete Document Object
 *	Create:	Fri Jan 30 16:27:44 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		void	DeleteDoc(struct ScanPageAtr **Page);
 *	Description:
 *		å¥çeÉIÉuÉWÉFÉNÉgÇçÌèú
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	DeleteDocObj(
	struct ScanPageAtr	**Page)
{
	if (*Page != NULL) {
		(*Page)->Object = FALSE;
		*Page = NULL;
	}
}


/*
 *	Name:	Save Scanning Mode
 *	Create:	Mon Jun 29 13:41:15 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		void	SaveScanningMode(UBYTE Mode)
 *	Description:
 *		ì«éÊÇËÉÇÅ[ÉhÇéwíËÇ∑ÇÈÅB
 *		SetScanPageAttribute() ÇÃëOÇ…ÉRÅ[ÉãÇ∑ÇÈÇ±Ç∆ÅB
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SaveScanningMode(
	UBYTE	Mode)						/* SYS_* see doc.h */
{
	UBYTE	Work;

	/* îOÇÃÇΩÇﬂÅAÉÇÅ[ÉhÇÉ`ÉFÉbÉNÇµÉZÅ[ÉuÇ∑ÇÈ */
	switch (Mode) {
	case SYS_NORMAL:
		Work = SYS_NORMAL;
		break;
	case SYS_FINE:
		Work = SYS_FINE;
		break;
	case SYS_SFINE:
		Work = SYS_SFINE;
		break;
	case SYS_GRAY64:
		Work = SYS_GRAY64;
		break;
	default:
		/* not reached */
		Work = SYS_FINE;				/* for fail safe */
		break;
	}
	ScannerSavedMode = Work;
}

/*
 *	Name:	Query Scanning Mode
 *	Create:	Mon Jun 29 13:52:58 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		UBYTE	QueryScanningMode(void);
 *	Description:
 *		ÉZÅ[ÉuÇµÇΩÉÇÅ[ÉhÇälÇÈ
 *	Return Value:
 *		SYS_* (see doc.h)
 *	Change Log:
 *		
 */
UBYTE	QueryScanningMode(void)
{
	return	ScannerSavedMode;
}

/*
 *	Name:	Set Scan Page Attributes
 *	Create:	Wed Jan  7 16:04:24 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		void	SetScanPageAttribute(struct ScanPageAtr *PageAtr);
 *	Description:
 *		å¥çeëÆê´Çê›íËÇ∑ÇÈ
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetScanPageAttribute(			/* å¥çeëÆê´ê›íË */
	struct ScanPageAtr *Page)			/* å¥çeëÆê´Ç÷ÇÃÉ|ÉCÉìÉ^ */
{
	Page->Code = QueryStoreCode();
	Page->Mode = QueryStoreMode();
	Page->Size = SYS_DocumentScanSize;
	Page->Density = QueryStoreDensity();

	ScanReduction = REDUCTION_NO; /* 1999/03/04 by T.Soneoka */

	if (ScannerMode == SCANNER_COPY_MODE) {
		/*
		** ÇPÉyÅ[ÉWÇÃêÊì™Ç≈èkè¨ó¶ÇéÊÇËçûÇÒÇ≈Ç®Ç´Ç‹Ç∑
		** Ç±ÇÃå„ÇÕÅAéÊÇËçûÇÒÇæílÇégópÇµÇ‹Ç∑
		** É}ÉãÉ`ÉRÉsÅ[ÇÃå„ÇÃÇaÇSÅ|ÅÑÇ`ÇSëóêMïsãÔçá
		** 1999/03/04 by T.Soneoka
		*/
		if ((SYS_DocumentScanSize == SYS_DOCUMENT_B4_SIZE)
		&& (!PB4())) {
			ScanReduction = REDUCTION_B4_A4;
		}
#if (0) /* É}ÉãÉ`ÉRÉsÅ[ÇÃå„ÇÃÇaÇSÅ|ÅÑÇ`ÇSëóêMïsãÔçá 1999/03/04 by T.Soneoka */
**		switch (QueryReduction()) {
#else
		switch (ScanReduction) {
#endif
		case REDUCTION_B4_A4:
			/* 
			** 1728/2048=0.84375%Ç≈ê›íË
			** (RC+1)/256 = èkè¨ó¶ÇÊÇË (RC+1)/256 = 0.84375 -> RC = 215
			*/
			Page->HolzReduction = 215;			/* éÂëñç∏èkè¨Ç†ÇË */
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033édólëŒâû Y.Kano 2003/12/01 */
			if (SYB_LC821033_Flg) {					/* LC821033ëŒâûÉtÉâÉO Y.Kano 2003/12/01 */
				Page->VertReduction = IP_SUBM_NON_LC33;	/* ïõëÄçÏèkè¨ñ≥Çµ */
			}
			else {	/* LC82103édól */
				Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
			}
#else	/* HINOKI2ãå ﬁ∞ºﬁÆ› */
			Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
#endif	/* End of defined(HINOKI2) */
			break;
		case REDUCTION_NO:
		default:
			Page->HolzReduction = 255;			/* éÂëñç∏èkè¨ñ≥Çµ */
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033édólëŒâû Y.Kano 2003/12/01 */
			if (SYB_LC821033_Flg) {					/* LC821033ëŒâûÉtÉâÉO Y.Kano 2003/12/01 */
				Page->VertReduction = IP_SUBM_NON_LC33;	/* ïõëÄçÏèkè¨ñ≥Çµ */
			}
			else {	/* LC82103édól */
				Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
			}
#else	/* HINOKI2ãå ﬁ∞ºﬁÆ› */
			Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
#endif	/* End of defined(HINOKI2) */
			break;
		}
	} else {
#if (PRO_CLASS1 == ENABLE)	/* by H.Hirao 1999/01/26 */
		if (QueryClass1Tx()) {
			switch (Page->Size) {
			case SYS_DOCUMENT_B4_SIZE:
				switch (CL1_PCDocumentSize) {	/* PCÇÃãLò^ïùî\óÕ */
				case SYS_DOCUMENT_A3_SIZE:
				case SYS_DOCUMENT_B4_SIZE:
					Page->HolzReduction = 255;	/* éÂëñç∏èkè¨ñ≥Çµ */
					break;
				case SYS_DOCUMENT_A4_SIZE:
					ScanReduction = REDUCTION_B4_A4;	/* 1999/03/23 by H.Hirao */
					Page->HolzReduction = 215;	/* éÂëñç∏èkè¨Ç†ÇË */
					break;
				}
				Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
				break;
			case SYS_DOCUMENT_A4_SIZE:
				Page->HolzReduction = 255;			/* éÂëñç∏èkè¨ñ≥Çµ */
				Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
				break;
			}
		}
		else {
			/*
			** ÉÅÉÇÉäÉRÉsÅ[ÅAÇaÇSÅ|ÅÑÇ`ÇSí~êœèàóùí«â¡
			** 1999/02/17 by T.Soneoka
			*/
			if ((!CHK_UNI_ReductionPrint())
			&& (SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)) {
				/*
				** ÇPÉyÅ[ÉWÇÃêÊì™Ç≈èkè¨ó¶ÇéÊÇËçûÇÒÇ≈Ç®Ç´Ç‹Ç∑
				** Ç±ÇÃå„ÇÕÅAéÊÇËçûÇÒÇæílÇégópÇµÇ‹Ç∑
				** É}ÉãÉ`ÉRÉsÅ[ÇÃå„ÇÃÇaÇSÅ|ÅÑÇ`ÇSëóêMïsãÔçá
				** 1999/03/04 by T.Soneoka
				*/
				if ((SYS_DocumentScanSize == SYS_DOCUMENT_B4_SIZE)
				&& (!PB4())) {
					ScanReduction = REDUCTION_B4_A4;
				}

#if (0) /* É}ÉãÉ`ÉRÉsÅ[ÇÃå„ÇÃÇaÇSÅ|ÅÑÇ`ÇSëóêMïsãÔçá 1999/03/04 by T.Soneoka */
**				switch (QueryReduction()) {
#else
				switch (ScanReduction) {
#endif
				case REDUCTION_B4_A4:
					/* 
					** 1728/2048=0.84375%Ç≈ê›íË
					** (RC+1)/256 = èkè¨ó¶ÇÊÇË (RC+1)/256 = 0.84375 -> RC = 215
					*/
					Page->HolzReduction = 215;			/* éÂëñç∏èkè¨Ç†ÇË */
					Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
					break;
				case REDUCTION_NO:
				default:
					Page->HolzReduction = 255;			/* éÂëñç∏èkè¨ñ≥Çµ */
					Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
					break;
				}
			} else {
				Page->HolzReduction = 255;			/* éÂëñç∏èkè¨ñ≥Çµ */
				Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
			}
		}
#else
		/*
		** ÉÅÉÇÉäÉRÉsÅ[ÅAÇaÇSÅ|ÅÑÇ`ÇSí~êœèàóùí«â¡
		** 1999/02/17 by T.Soneoka
		*/
		if ((!CHK_UNI_ReductionPrint())
		&& (SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)) {
			/*
			** ÇPÉyÅ[ÉWÇÃêÊì™Ç≈èkè¨ó¶ÇéÊÇËçûÇÒÇ≈Ç®Ç´Ç‹Ç∑
			** Ç±ÇÃå„ÇÕÅAéÊÇËçûÇÒÇæílÇégópÇµÇ‹Ç∑
			** É}ÉãÉ`ÉRÉsÅ[ÇÃå„ÇÃÇaÇSÅ|ÅÑÇ`ÇSëóêMïsãÔçá
			** 1999/03/04 by T.Soneoka
			*/
#if defined(KEISATSU) /* B4Ç2ñáÇÃ1ñáñ⁄ì«Ç›éÊÇËíÜÇ…ñ{ëÃÉIÅ[ÉvÉìÇ≈2ñáñ⁄Ç™èkè¨Ç≥ÇÍÇƒÉSÉ~Ç™àÛéöÇ≥ÇÍÇÈåèÅBO.Oshima 2005/12/12 */
			if ((SYS_DocumentScanSize == SYS_DOCUMENT_B4_SIZE)
			&& (!PB4())
			&& (!RXIL())) { /* (SYS_DocumentStorePage == 1) Ç≈å©ÇÈÇ∆B4->A4èkè¨ÇÃ2ñáñ⁄Ç™ê≥ÇµÇ≠çsÇÌÇÍÇ»Ç¢ÅB */
#else
			if ((SYS_DocumentScanSize == SYS_DOCUMENT_B4_SIZE)
			&& (!PB4())) {
#endif
				ScanReduction = REDUCTION_B4_A4;
			}

#if (0) /* É}ÉãÉ`ÉRÉsÅ[ÇÃå„ÇÃÇaÇSÅ|ÅÑÇ`ÇSëóêMïsãÔçá 1999/03/04 by T.Soneoka */
**			switch (QueryReduction()) {
#else
			switch (ScanReduction) {
#endif
			case REDUCTION_B4_A4:
				/* 
				** 1728/2048=0.84375%Ç≈ê›íË
				** (RC+1)/256 = èkè¨ó¶ÇÊÇË (RC+1)/256 = 0.84375 -> RC = 215
				*/
				Page->HolzReduction = 215;			/* éÂëñç∏èkè¨Ç†ÇË */
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033édólëŒâû Y.Kano 2003/12/01 */
				if (SYB_LC821033_Flg) {					/* LC821033ëŒâûÉtÉâÉO Y.Kano 2003/12/01 */
					Page->VertReduction = IP_SUBM_NON_LC33;	/* ïõëÄçÏèkè¨ñ≥Çµ */
				}
				else {	/* LC82103édól */
					Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
				}
#else	/* HINOKI2ãå ﬁ∞ºﬁÆ› */
				Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
#endif	/* End of defined(HINOKI2) */
				break;
			case REDUCTION_NO:
			default:
				Page->HolzReduction = 255;			/* éÂëñç∏èkè¨ñ≥Çµ */
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033édólëŒâû Y.Kano 2003/12/01 */
				if (SYB_LC821033_Flg) {					/* LC821033ëŒâûÉtÉâÉO Y.Kano 2003/12/01 */
					Page->VertReduction = IP_SUBM_NON_LC33;	/* ïõëÄçÏèkè¨ñ≥Çµ */
				}
				else {	/* LC82103édól */
					Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
				}
#else	/* HINOPKI2ãå ﬁ∞ºﬁÆ› */
				Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
#endif	/* End of defined(HINOKI2) */
				break;
			}
		} else {
			Page->HolzReduction = 255;			/* éÂëñç∏èkè¨ñ≥Çµ */
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033édólëŒâû Y.Kano 2003/12/01 */
			if (SYB_LC821033_Flg) {					/* LC821033ëŒâûÉtÉâÉO Y.Kano 2003/12/01 */
				Page->VertReduction = IP_SUBM_NON_LC33;	/* ïõëÄçÏèkè¨ñ≥Çµ */
			}
			else {	/* LC82103édól */
				Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
			}
#else	/* HINOKI2ãå ﬁ∞ºﬁÆ› */
			Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
#endif	/* End of defined(HINOKI2) */
		}
#endif
	}
#if (0) /* 1998/10/31 by T.Soneoka */
**	if (CHK_QueryScanTopAdjust() & 0x80) {
**		Page->Ds2ToScanSteps = (Ds2ToScanSteps - (CHK_QueryScanTopAdjust() & 0x7f));
**	} else {
**		Page->Ds2ToScanSteps = (Ds2ToScanSteps + (CHK_QueryScanTopAdjust() & 0x7f));
**	}
#else
#if (0) /* 1999/02/22 by T.Soneoka */
**	if ((Ds2ToScanSteps + CHK_QueryScanTopAdjust()) < 0) {
**		Page->Ds2ToScanSteps = (UWORD)Ds2ToScanSteps;
**	} else {
**		Page->Ds2ToScanSteps = (UWORD)(Ds2ToScanSteps + CHK_QueryScanTopAdjust());
**	}
#else
	if (CHK_QueryScanTopAdjust() & 0x80) {
		Page->Ds2ToScanSteps = (UWORD)(Ds2ToScanSteps + (CHK_QueryScanTopAdjust() & 0x7f));
	} else {
		if ((Ds2ToScanSteps - (CHK_QueryScanTopAdjust() & 0x7f)) < 0) {
#if (0) /* 1999/02/24 by T.Soneoka */
**			Page->Ds2ToScanSteps = (UWORD)Ds2ToScanSteps;
#else
			Page->Ds2ToScanSteps = (UWORD)0;
#endif
		} else {
			Page->Ds2ToScanSteps = (UWORD)(Ds2ToScanSteps - (CHK_QueryScanTopAdjust() & 0x7f));
		}
	}
#endif
#endif

#if (0) /* 1998/10/31 by T.Soneoka */
**	if (CHK_QueryScanEndAdjust() & 0x80) {
**		Page->Ds2ToScanEndSteps = (Ds2ToScanEndSteps - (CHK_QueryScanEndAdjust() & 0x7f));
**	} else {
**		Page->Ds2ToScanEndSteps = (Ds2ToScanEndSteps + (CHK_QueryScanEndAdjust() & 0x7f));
**	}
#else
#if (0) /* 1999/02/22 by T.Soneoka */
**	if ((Ds2ToScanEndSteps + CHK_QueryScanEndAdjust()) < 0) {
**		Page->Ds2ToScanEndSteps = (UWORD)Ds2ToScanEndSteps;
**	} else {
**		Page->Ds2ToScanEndSteps = (UWORD)(Ds2ToScanEndSteps + CHK_QueryScanEndAdjust());
**	}
#else
	if (CHK_QueryScanEndAdjust() & 0x80) {
		Page->Ds2ToScanEndSteps = (UWORD)(Ds2ToScanEndSteps + (CHK_QueryScanEndAdjust() & 0x7f));
	} else {
		if ((Ds2ToScanEndSteps - (CHK_QueryScanEndAdjust() & 0x7f)) < 0) {
#if (0) /* 1999/02/24 by T.Soneoka */
**			Page->Ds2ToScanEndSteps = (UWORD)Ds2ToScanEndSteps;
#else
			Page->Ds2ToScanEndSteps = (UWORD)0;
#endif
		} else {
			Page->Ds2ToScanEndSteps = (UWORD)(Ds2ToScanEndSteps - (CHK_QueryScanEndAdjust() & 0x7f));
		}
	}
#endif
#endif
	switch (Page->Mode) {
	case SYS_NORMAL:					/* ïÅí 	   200dpi:8 dot/m  100dpi:3.85ñ{/l */
		if (CHK_UNI_NormFineScan()) {
			Page->VerticalMode = TX_MOTOR_FINE1_2_SCAN;
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033édólëŒâû Y.Kano 2003/12/01 */
			if (SYB_LC821033_Flg) {					/* LC821033ëŒâûÉtÉâÉO Y.Kano 2003/12/01 */
				Page->VertReduction = IP_SUBM_1_2_LC33; /* ïõëÄçÏ1/2èkè¨ */
			}
			else {	/* LC82103édól */
				Page->VertReduction = IP_SUBM_1_2; /* ïõëÄçÏ1/2èkè¨ */
			}
#else	/* HINOKI2ãå ﬁ∞ºﬁÆ› */
			Page->VertReduction = IP_SUBM_1_2; /* ïõëÄçÏ1/2èkè¨ */
#endif	/* End of defined(HINOKI2) */
		} else {
			Page->VerticalMode = TX_MOTOR_NORMAL_SCAN;
		}
		break;
	case SYS_FINE:						/* çÇâÊéø   200dpi:8 dot/m  200dpi:7.7 ñ{/l */
	case SYS_GRAY16:					/* 16äKí≤   200dpi:8 dot/m  200dpi:7.7 ñ{/l */
	case SYS_GRAY32:					/* 32äKí≤   200dpi:8 dot/m  200dpi:7.7 ñ{/l */
	case SYS_GRAY64:					/* 64äKí≤   200dpi:8 dot/m  200dpi:7.7 ñ{/l */
		Page->VerticalMode = TX_MOTOR_FINE_SCAN;
		break;
	case SYS_SFINE:						/* í¥çÇâÊéø 200dpi:8 dot/m  400dpi:15.5ñ{/l */
	case SYS_HFINE:						/* í¥çÇâÊéø 400dpi:16dot/m  400dpi:15.5ñ{/l */
		Page->VerticalMode = TX_MOTOR_SFINE_SCAN;
		break;
	default:
		/* not reached */
		break;
	}
}


/*
 *	Name:	Set Scan Page Attributes (for scanner transmit)
 *	Create:	Wed Jan  7 16:04:24 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		void	SetScanPageAttribute2(struct ScanPageAtr *PageAtr);
 *	Description:
 *		å¥çeëÆê´Çê›íËÇ∑ÇÈ
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	SetScanPageAttribute2(			/* å¥çeëÆê´ê›íË */
	struct ScanPageAtr *Page)			/* å¥çeëÆê´Ç÷ÇÃÉ|ÉCÉìÉ^ */
{

	/*
	** ÇPÉyÅ[ÉWÇÃêÊì™Ç≈èkè¨ó¶ÇéÊÇËçûÇÒÇ≈Ç®Ç´Ç‹Ç∑
	** Ç±ÇÃå„ÇÕÅAéÊÇËçûÇÒÇæílÇégópÇµÇ‹Ç∑
	** É}ÉãÉ`ÉRÉsÅ[ÇÃå„ÇÃÇaÇSÅ|ÅÑÇ`ÇSëóêMïsãÔçá
	** 1999/03/04 by T.Soneoka
	*/
	ScanReduction = REDUCTION_NO;

	Page->Code = QueryStoreCode();
	
	switch (SYS_DocBlock.Src.Mode) {	/**	é©ã@ÇÃå¥çeÉÇÅ[Éh */
	case	SYS_GRAY16:					/**	äeéÌÉnÅ[ÉtÉgÅ[Éì */
	case	SYS_GRAY16_SEP:
	case	SYS_GRAY32:
	case	SYS_GRAY32_SEP:
	case	SYS_GRAY64:
	case	SYS_GRAY64_SEP:
		if (SYS_DocBlock.Dst.Mode == SYS_NORMAL) {		/**	ëäéËã@Ç™ÉmÅ[É}Éã */
			/**	ì«Ç›éÊÇËÉÇÅ[ÉhÇ…ëäéËã@ÇÃéÛêMÉÇÅ[ÉhÇÉZÉbÉg */
			/*
			** åêMëäéËÇÃî\óÕÇ™ÉmÅ[É}ÉãÇÃÉ}ÉVÉìÇ…ÅAÉXÉLÉÉÉiíÜä‘í≤ëóêMÇÇ®Ç±Ç»Ç§Ç∆ÅA
			** ì«Ç›éÊÇËÇ≈ÉmÅ[É}Éãì«Ç›ÇµÇƒÅAÉRÅ[ÉfÉbÉNÇ≈ÇPÅ^ÇQÇ…èkè¨Ç≥ÇÍÇÈÇΩÇﬂ
			** ÉtÉ@ÉCÉìì«Ç›ÇµÇ‹Ç∑ by H.Hirao 1999/01/28
			*/
#if (0)
			Page->Mode = SYS_NORMAL;
#else
			Page->Mode = SYS_FINE;
#endif
		}
		else {
			/**	ì«Ç›éÊÇËÉÇÅ[ÉhÇ…é©ã@ÇÃå¥çeÉÇÅ[ÉhÇÉZÉbÉg */
			Page->Mode = SYS_DocBlock.Src.Mode;
		}
		break;
	default:
/*
** ÇlÅ|ÇTÇ…ÉXÉLÉÉÉiÇrÇeÇhÇmÇdëóêMÇçsÇ§Ç∆ÅAÉvÉäÉìÉgÇ™ÇPÅ^ÇQÇ…Ç»Ç¡ÇƒÇµÇ‹Ç§
** ì«Ç›éÊÇËÇ≈ÇeÇhÇmÇdì«Ç›ÇÇµÇƒÅAÉRÅ[ÉfÉbÉNÇ≈ÇPÅ^ÇQèkè¨Ç≥ÇÍÇÈÇΩÇﬂ
** ì«Ç›éÊÇËÇÕèÌÇ…é©ã@ÇÃÉÇÅ[ÉhÇ≈ÉXÉLÉÉÉìÇµÇƒÅAÉRÅ[ÉfÉbÉNÇ≈èkè¨èàóùÇçsÇ§ÇÊÇ§Ç…Ç∑ÇÈ
** 1999/01/28 by T.Soneoka
*/
#if (0)
**		/**	ì«Ç›éÊÇËÉÇÅ[ÉhÇ…ëäéËã@ÇÃå¥çeÉÇÅ[ÉhÇÉZÉbÉg */
**		Page->Mode = SYS_DocBlock.Dst.Mode;
#else
		Page->Mode = SYS_DocBlock.Src.Mode;
#endif
		break;
	}

	Page->Size = SYS_DocumentScanSize;
	Page->Density = SYB_DensitySw;
	Page->HolzReduction = 255;			/* éÂëñç∏èkè¨ñ≥Çµ */
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033édólëŒâû Y.Kano 2003/12/01 */
	if (SYB_LC821033_Flg) {					/* LC821033ëŒâûÉtÉâÉO Y.Kano 2003/12/01 */
		Page->VertReduction = IP_SUBM_NON_LC33;	/* ïõëÄçÏèkè¨ñ≥Çµ */
	}
	else {	/* LC82103édól */
		Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
	}
#else	/* HINOKI2ãå ﬁ∞ºﬁÆ› */
	Page->VertReduction = IP_SUBM_NON;	/* ïõëÄçÏèkè¨ñ≥Çµ */
#endif	/* End of defined(HINOKI2) */
	
#if (0) /* 1999/02/22 by T.Soneoka */
**	if ((Ds2ToScanSteps + CHK_QueryScanTopAdjust()) < 0) {
**		Page->Ds2ToScanSteps = (UWORD)Ds2ToScanSteps;
**	} else {
**		Page->Ds2ToScanSteps = (UWORD)(Ds2ToScanSteps + CHK_QueryScanTopAdjust());
**	}
#else
	if (CHK_QueryScanTopAdjust() & 0x80) {
		Page->Ds2ToScanSteps = (UWORD)(Ds2ToScanSteps + (CHK_QueryScanTopAdjust() & 0x7f));
	} else {
		if ((Ds2ToScanSteps - (CHK_QueryScanTopAdjust() & 0x7f)) < 0) {
#if (0) /* 1999/02/24 by T.Soneoka */
**			Page->Ds2ToScanSteps = (UWORD)Ds2ToScanSteps;
#else
			Page->Ds2ToScanSteps = (UWORD)0;
#endif
		} else {
			Page->Ds2ToScanSteps = (UWORD)(Ds2ToScanSteps - (CHK_QueryScanTopAdjust() & 0x7f));
		}
	}
#endif

#if (0) /* 1999/02/22 by T.Soneoka */
**	if ((Ds2ToScanEndSteps + CHK_QueryScanEndAdjust()) < 0) {
**		Page->Ds2ToScanEndSteps = (UWORD)Ds2ToScanEndSteps;
**	} else {
**		Page->Ds2ToScanEndSteps = (UWORD)(Ds2ToScanEndSteps + CHK_QueryScanEndAdjust());
**	}
#else
	if (CHK_QueryScanEndAdjust() & 0x80) {
		Page->Ds2ToScanEndSteps = (UWORD)(Ds2ToScanEndSteps + (CHK_QueryScanEndAdjust() & 0x7f));
	} else {
		if ((Ds2ToScanEndSteps - (CHK_QueryScanEndAdjust() & 0x7f)) < 0) {
#if (0) /* 1999/02/24 by T.Soneoka */
**			Page->Ds2ToScanEndSteps = (UWORD)Ds2ToScanEndSteps;
#else
			Page->Ds2ToScanEndSteps = (UWORD)0;
#endif
		} else {
			Page->Ds2ToScanEndSteps = (UWORD)(Ds2ToScanEndSteps - (CHK_QueryScanEndAdjust() & 0x7f));
		}
	}
#endif

	switch (Page->Mode) {
	case SYS_NORMAL:					/* ïÅí 	   200dpi:8 dot/m  100dpi:3.85ñ{/l */
		if (CHK_UNI_NormFineScan()) {
			Page->VerticalMode = TX_MOTOR_FINE1_2_SCAN;
#if defined(HINOKI2) || defined(HINOKI3)	/* LC821033édólëŒâû Y.Kano 2003/12/01 */
			if (SYB_LC821033_Flg) {					/* LC821033ëŒâûÉtÉâÉO Y.Kano 2003/12/01 */
				Page->VertReduction = IP_SUBM_1_2_LC33; /* ïõëÄçÏ1/2èkè¨ */
			}
			else {	/* LC82103édól */
				Page->VertReduction = IP_SUBM_1_2; /* ïõëÄçÏ1/2èkè¨ */
			}
#else	/* HINOKI2ãå ﬁ∞ºﬁÆ› */
			Page->VertReduction = IP_SUBM_1_2; /* ïõëÄçÏ1/2èkè¨ */
#endif	/* End of defined(HINOKI2) */
		} else {
			Page->VerticalMode = TX_MOTOR_NORMAL_SCAN;
		}
		break;
	case SYS_FINE:						/* çÇâÊéø   200dpi:8 dot/m  200dpi:7.7 ñ{/l */
	case SYS_GRAY16:					/* 16äKí≤   200dpi:8 dot/m  200dpi:7.7 ñ{/l */
	case SYS_GRAY32:					/* 32äKí≤   200dpi:8 dot/m  200dpi:7.7 ñ{/l */
	case SYS_GRAY64:					/* 64äKí≤   200dpi:8 dot/m  200dpi:7.7 ñ{/l */
		Page->VerticalMode = TX_MOTOR_FINE_SCAN;
		break;
	case SYS_SFINE:						/* í¥çÇâÊéø 200dpi:8 dot/m  400dpi:15.5ñ{/l */
	case SYS_HFINE:						/* í¥çÇâÊéø 400dpi:16dot/m  400dpi:15.5ñ{/l */
		Page->VerticalMode = TX_MOTOR_SFINE_SCAN;
		break;
	default:
		/* not reached */
		break;
	}
}


/*
 *	Name:	Update Document Postion Status
 *	Create:	Mon Feb  9 16:26:46 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		void	UpdateDocPostion(void);
 *	Description:
 *      äÑÇËçûÇ›Ç©ÇÁÉRÅ[ÉãÇ≥ÇÍÇ‹Ç∑
 *		å¥çeëóÇËó ÉJÉEÉìÉgÉAÉbÉv å¥çeà íuÉXÉeÅ[É^ÉXçXêV
 *		ëóêMÉÇÅ[É^Å[ìÆçÏå„ÉRÅ[ÉãÇ∑ÇÈÇ±Ç∆ÅB
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	UpdateDocPosition(void)
{

	BYTE	FeederMode;

	switch (CurrentPage->Position) {
	case DOC_POS_MOVE_TO_DS2:			/* DS2 Ç…à⁄ìÆíÜ */
		CurrentPage->StepsFromDs1On += TxMotorSpeedPtr->MoveLines;

		if (Ds2Raw()) {
			CurrentPage->Position = DOC_POS_MOVE_TO_READY;
		}
		break;
	case DOC_POS_MOVE_TO_READY:			/* ë“ã@à íuÇ…à⁄ìÆíÜ */
		CurrentPage->StepsFromDs1On += TxMotorSpeedPtr->MoveLines;
		CurrentPage->StepsFromDs2On += TxMotorSpeedPtr->MoveLines; 

		if (CurrentPage->StepsFromDs2On > Ds2ToReadySteps) {
			CurrentPage->Position = DOC_POS_MOVE_TO_SCAN;
			if (ScannerMode == SCANNER_DOC_IN_MODE) {
				CluchOff();
			}
		}
		break;
	case DOC_POS_MOVE_TO_SCAN:			/* ì«éÊÇËà íuÇ…à⁄ìÆíÜ */
		CurrentPage->StepsFromDs1On += TxMotorSpeedPtr->MoveLines;
		CurrentPage->StepsFromDs2On += TxMotorSpeedPtr->MoveLines; 

		if (CurrentPage->StepsFromDs2On > CurrentPage->Ds2ToScanSteps) {
			CurrentPage->Position = DOC_POS_SCANNING;
/*
** ÇfÇRëóêMéûÇ…ÉtÉBÉãÇ™èoâﬂÇ¨ÇƒÅAéÛêMë§Ç™âÒê¸ífÇ∑ÇÈïsãÔçáÅiLaser FaxÇ≈î≠ê∂Åj
** Ç±ÇÃèàóùÇÇµÇƒÇ¢Ç»Ç¢Ç∆ÅAÇrÇeÇhÇmÇdÇ≈ÅAå¥çeä‘ÇSïbã≠ÇÃÇeÇhÇkÇkÇ™èoÇƒÇ¢ÇΩ
** 1999/02/25 by T.Soneoka
*/
#if (0)
**			if (Debug_MoveToScan200pps) {
**				switch (CurrentPage->VerticalMode) {
**				case TX_MOTOR_NORMAL_SCAN:
**					FeederMode = FEEDER_NORMAL_SCAN;
**					break;
**				case TX_MOTOR_FINE_SCAN:
**					FeederMode = FEEDER_FINE_SCAN;
**					break;
**				case TX_MOTOR_SFINE_SCAN:
**					FeederMode = FEEDER_SFINE_SCAN;
**					break;
**				case TX_MOTOR_FINE1_2_SCAN:
**					FeederMode = FEEDER_FINE1_2_SCAN;
**					break;
**				case TX_MOTOR_SFINE1_2_SCAN:
**					FeederMode = FEEDER_SFINE1_2_SCAN;
**					break;
**				default:
**					/* not reached */
**					break;
**				}
**				SetupTxMotor(FeederMode);
**			}
#else
			/*
			** å¥çeîrèoÇÃÇsÇwÉÇÅ[É^ÇÃëóÇËë¨ìxÇ™ÅAëOÇÃÉRÉsÅ[ÇÃÉÇÅ[ÉhÇ…Ç»Ç¡ÇƒÇµÇ‹Ç§ïsãÔçá
			** ifï∂í«â¡ 1999/02/26 by T.Soneoka
			*/
			if ((ScannerMode == SCANNER_DOC_SCAN_MODE)
			||  (ScannerMode == SCANNER_COPY_MODE)) {
				switch (CurrentPage->VerticalMode) {
				case TX_MOTOR_NORMAL_SCAN:
					FeederMode = FEEDER_NORMAL_SCAN;
					break;
				case TX_MOTOR_FINE_SCAN:
					FeederMode = FEEDER_FINE_SCAN;
					break;
				case TX_MOTOR_SFINE_SCAN:
					FeederMode = FEEDER_SFINE_SCAN;
					break;
				case TX_MOTOR_FINE1_2_SCAN:
					FeederMode = FEEDER_FINE1_2_SCAN;
					break;
				case TX_MOTOR_SFINE1_2_SCAN:
					FeederMode = FEEDER_SFINE1_2_SCAN;
					break;
				default:
					/* not reached */
					break;
				}
				SetupTxMotor(FeederMode);
			}
#endif
		}
		break;
	case DOC_POS_SCANNING:				/* ì«Ç›éÊÇËâ¬î\ */
		CurrentPage->StepsFromDs1On += TxMotorSpeedPtr->MoveLines;
		CurrentPage->StepsFromDs2On += TxMotorSpeedPtr->MoveLines; 

		if (!QueryDs2On()) {
			CurrentPage->Position = DOC_POS_SCAN_FEEDOUT;

			/* édólïœçX
			** ì«Ç›éÊÇËíÜÇ…Ç®Ç¢ÇƒÅAÇcÇrÇQÇ™ÇnÇeÇeÇµÇΩéûì_Ç≈ÇcÇrÇPÇ‡ÇnÇeÇeÇµÇƒÇ¢ÇÍÇŒÅAç°ì«ÇÒÇæå¥çeÇ™
			** ç≈èIå¥çeÇ≈Ç†ÇÈÇ∆Ç¢Ç§ïóÇ…ïœçX
			** by O.kimoto 1999/03/08
			*/
			if (!QueryDs1On()) {
				NoNextDocument = TRUE;
			}

		}
		break;
	case DOC_POS_SCAN_FEEDOUT:			/* ì«éÊÇËÇ»Ç™ÇÁîrèo */
		CurrentPage->StepsFromDs1On += TxMotorSpeedPtr->MoveLines;
		CurrentPage->StepsFromDs2On += TxMotorSpeedPtr->MoveLines; 
		CurrentPage->StepsFromDs2Off += TxMotorSpeedPtr->MoveLines;

		if (CurrentPage->StepsFromDs2Off > CurrentPage->Ds2ToScanEndSteps) {

#if (PRO_STAMP == ENABLE)
			CurrentPage->Position = DOC_POS_MOVE_TO_PUSH_STAMP;
#else
			CurrentPage->Position = DOC_POS_FEED_OUT;
#endif
		}
		UpdateNextDocPosition();		/* éüÇÃå¥çeà íuÇçXêV */
		break;
#if (PRO_STAMP == ENABLE)
	case DOC_POS_MOVE_TO_PUSH_STAMP:	/* ÉXÉ^ÉìÉvâüâ∫à íuÇ÷à⁄ìÆíÜ */
		CurrentPage->StepsFromDs1On += TxMotorSpeedPtr->MoveLines;
		CurrentPage->StepsFromDs2On += TxMotorSpeedPtr->MoveLines; 
		CurrentPage->StepsFromDs2Off += TxMotorSpeedPtr->MoveLines;

		if (CurrentPage->StepsFromDs2Off > Ds2ToPushStampSteps) {
			CurrentPage->Position = DOC_POS_FEED_OUT;
			/*
			** éüå¥çeÇÃìoò^Ç∑ÇÈëOÇ…ÉÇÅ[É^ÇàÍíUí‚é~ÇµÇ‹Ç∑ 
			** ÉyÅ[ÉWä‘Ç≈éÛêMë§Ç©ÇÁÇÃâÔòbó\ñÒê¨óßéûÅAéüÇÃå¥çeÇ‹Ç≈åJÇËçûÇÒÇ≈ÇµÇ‹Ç¢Ç‹Ç∑
			** Added next 1 line 1999/1/11 by T.Soneoka
			*/
			SCN_DocumentChanged = TRUE;

/*
** äÑÇËçûÇ›ÇÃíÜÇ≈éüå¥çeÇÃìoò^ÇÇ‚Çﬂè„à Ç≈çsÇ»Ç§ÇÊÇ§Ç…ÇµÇ‹Ç∑(éüå¥çeÇ†ÇËéû)
** äÑÇËçûÇ›ÇÃíÜÇ≈éüå¥çeìoò^ÇµÇΩèÍçáÅA
** éüå¥çeìoò^ÇµÇΩÇ™ÅAåªç›ÇÃå¥çeì«Ç›éÊÇËèIóπéûÇ…ÅAéüå¥çeì«Ç›éÊÇËÇµÇ»Ç¢èÍçáÅiå¥çeñáêîéwíËÅjÅA
** SCN_Close()Ç≈îrèoèàóùÇÉRÅ[ÉãÇ∑ÇÈÇ∆ÅAéüå¥çeÇ‹Ç≈îrèoÇ≥ÇÍÇƒÇµÇ‹Ç§à◊
** Ç±Ç±Ç≈ÇµÇ»Ç¢ÇŸÇ§Ç™Ç∑Ç¡Ç´ÇËÇ∑ÇÈ
** 1999/02/10 by T.Soneoka
*/
#if (0)
**			/*
**			** å¥çeÇ™êÿÇËë÷ÇÌÇ¡ÇΩÇ∆Ç´Ç…ÅAéüå¥çeÇÃìoò^ÇÇµÇ»Ç¢Ç∆ÅA
**			** åªç›ÇÃå¥çeÇÃê›íËÇ≈ÅAéüå¥çeÇ™ìÆçÏÇµÇƒÇµÇ‹Ç§
**			** 1999/01/30 by T.Soneoka
**			*/
**			if ((NextPage != NULL) &&
**				(ScannerMode != SCANNER_DOC_OUT_MODE)) { /* å¥çeîrèoÉÇÅ[ÉhÇÕéüå¥çeÇÇ›Ç‹ÇπÇÒ */
**				DeleteDocObj(&CurrentPage);
**				CurrentPage = NextPage;
**				NextPage = NULL;
**			}
#endif
		}
		UpdateNextDocPosition();		/* éüÇÃå¥çeà íuÇçXêV */
		break;
#endif
	case DOC_POS_FEED_OUT:				/* îrèoíÜ */
		CurrentPage->StepsFromDs1On += TxMotorSpeedPtr->MoveLines;
		CurrentPage->StepsFromDs2On += TxMotorSpeedPtr->MoveLines; 
		CurrentPage->StepsFromDs2Off += TxMotorSpeedPtr->MoveLines; 

		if (CurrentPage->StepsFromDs2Off > Ds2ToExitSteps) {
			CurrentPage->Position = DOC_POS_NO_DOCUMENT;
		}
		UpdateNextDocPosition();		/* éüÇÃå¥çeà íuÇçXêV */

/*
** éüå¥çeÇÃìoò^Ç∑ÇÈëOÇ…ÉÇÅ[É^ÇàÍíUí‚é~ÇµÇ‹Ç∑ 
** ÉyÅ[ÉWä‘Ç≈éÛêMë§Ç©ÇÁÇÃâÔòbó\ñÒê¨óßéûÅAéüÇÃå¥çeÇ‹Ç≈åJÇËçûÇÒÇ≈ÇµÇ‹Ç¢Ç‹Ç∑
** è„ãLDOC_POS_MOVE_TO_PUSH_STAMPÉtÉFÅ[ÉYÇ…ÇƒçsÇ¢Ç‹Ç∑
** Deleted Next 1 line 1999/1/11 by T.Soneoka
*/
#if (0) 
**		/* 1998/11/10 îrèoÉtÉFÅ[ÉYÇ≈àÍíUÉÇÅ[É^Çí‚é~Ç≥ÇπÇÈÇÊÇ§Ç…ïœçX by T.Soneoka */
**		SCN_DocumentChanged = TRUE;
#endif



/*
** äÑÇËçûÇ›ÇÃíÜÇ≈éüå¥çeÇÃìoò^ÇÇ‚Çﬂè„à Ç≈çsÇ»Ç§ÇÊÇ§Ç…ÇµÇ‹Ç∑(éüå¥çeÇ†ÇËéû)
** äÑÇËçûÇ›ÇÃíÜÇ≈éüå¥çeìoò^ÇµÇΩèÍçáÅA
** éüå¥çeìoò^ÇµÇΩÇ™ÅAåªç›ÇÃå¥çeì«Ç›éÊÇËèIóπéûÇ…ÅAéüå¥çeì«Ç›éÊÇËÇµÇ»Ç¢èÍçáÅiå¥çeñáêîéwíËÅjÅA
** SCN_Close()Ç≈îrèoèàóùÇÉRÅ[ÉãÇ∑ÇÈÇ∆ÅAéüå¥çeÇ‹Ç≈îrèoÇ≥ÇÍÇƒÇµÇ‹Ç§à◊
** Ç±Ç±Ç≈ÇµÇ»Ç¢ÇŸÇ§Ç™Ç∑Ç¡Ç´ÇËÇ∑ÇÈ
** 1999/02/10 by T.Soneoka
*/
#if (0)
**/*
**** Ç±Ç±Ç≈éüå¥çeÇìoò^Ç∑ÇÈÇ∆íxÇ¢ÅA
**** è„ãLÉtÉFÅ[ÉYDOC_POS_MOVE_TO_PUSH_STAMPÇÃSCN_DocumentChanged = TRUEÇ≈â∫ãLèàóùÇçsÇÌÇ»Ç¢Ç‹Ç∑
**** 1999/01/30 by T.Soneoka
***/
**		/* éüÇÃå¥çeÇåªç›ÇÃå¥çeÇ∆Ç∑ÇÈ */
**#if (0) /* 1998/11/18 by T.Soneoka */
****		if (NextPage != NULL) {
**#else
**		if ((NextPage != NULL) &&
**			(ScannerMode != SCANNER_DOC_OUT_MODE)) { /* å¥çeîrèoÉÇÅ[ÉhÇÕéüå¥çeÇÇ›Ç‹ÇπÇÒ */
**#endif
**			DeleteDocObj(&CurrentPage);
**			CurrentPage = NextPage;
**			NextPage = NULL;
**#if (0) /* 1998/12/21 by T.Soneoka */
****			CluchOn();
**#endif
**		}
#endif


		break;
	case DOC_POS_NO_DOCUMENT:			/* å¥çeñ≥Çµ */
	default:
		/* not Reached */
		break;
	}

	/* ÉNÉâÉbÉ`ÇnÇeÇeêßå‰ */
#if (0) /* 1998/12/21 by T.Soneoka */
**	if ((CurrentPage->StepsFromDs1On >= CluchOffCounter) && (CluchSetting())) {
**		CluchOff();
**	}
#else
	if (!((CurrentPage->Position == DOC_POS_MOVE_TO_DS2) || (CurrentPage->Position == DOC_POS_MOVE_TO_READY))) {
		if ((CurrentPage->StepsFromDs2On >= CluchOffCounter) && (CluchSetting())) {
			CluchOff();
		}
	}
#endif
}

/*
 *	Name:	Update Next Document Postion Status
 *	Create:	Wed Feb 18 16:41:34 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		void	UpdateNextDocPostion(void);
 *	Description:
 *      äÑÇËçûÇ›Ç©ÇÁÉRÅ[ÉãÇ≥ÇÍÇ‹Ç∑
 *		éüÇÃå¥çeÇÃÉIÉuÉWÉFÉNÉgçÏê¨
 *		ëóÇËó ÉJÉEÉìÉgÉAÉbÉv å¥çeà íuÉXÉeÅ[É^ÉXçXêV
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	UpdateNextDocPosition(void)
{
	if (QueryDs1On()) {
		/* éüÇÃå¥çeÇ™Ç†ÇÈÇ∆Ç´ */
		if (NextPage == NULL) {
			NextPage = CreateDocObj();
		} else {
			switch (NextPage->Position) {
			case DOC_POS_MOVE_TO_DS2:
				NextPage->StepsFromDs1On += TxMotorSpeedPtr->MoveLines;
				if (QueryDs2On()) {
					NextPage->Position = DOC_POS_MOVE_TO_READY;
				}
				break;
			case DOC_POS_MOVE_TO_READY:			/* ë“ã@à íuÇ…à⁄ìÆíÜ */
				NextPage->StepsFromDs1On += TxMotorSpeedPtr->MoveLines;
				NextPage->StepsFromDs2On += TxMotorSpeedPtr->MoveLines; 
				if (NextPage->StepsFromDs2On > Ds2ToReadySteps) {
					NextPage->Position = DOC_POS_MOVE_TO_SCAN;
				}
				break;
			case DOC_POS_MOVE_TO_SCAN:			/* ì«éÊÇËà íuÇ…à⁄ìÆíÜ */
				NextPage->StepsFromDs1On += TxMotorSpeedPtr->MoveLines;
				NextPage->StepsFromDs2On += TxMotorSpeedPtr->MoveLines; 
				if (NextPage->StepsFromDs2On > NextPage->Ds2ToScanSteps) {
					NextPage->Position = DOC_POS_SCANNING;
				}
				break;
			default:
				/* not reached */
				break;
			}
		}
	} else {
		/* éüÇÃå¥çeÇà¯î≤Ç¢ÇΩèÍçá */
		if (NextPage != NULL) {
			DeleteDocObj(&NextPage);
		}
	}
}

/*
 *	Name:	Wait Document Changed
 *	Create:	 1998/09/01 by T.Soneoka
 *	Synopsis:
 *		void	WaitDocChanged(void);
 *	Description:
 *		å¥çeÇ™êÿÇËë÷ÇÌÇÈÇ‹Ç≈ë“ÇøçáÇÌÇπÇµÇ‹Ç∑
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	WaitDocChanged(void)
{
	while (!QueryDocumentChanged()) {
		wai_tsk(1);
	}
	SCN_DocumentChanged = FALSE;
}


#if (0) /* ñ¢égóp 1998/12/21 by T.Soneoka */
**void	WaitNextDoc(void)
**{
**	/* ÉXÉLÉÉÉìå¥çeä‘Ç≈ÉXÉgÉbÉvÇ≥ÇÍÇΩéûÇÃëŒçÙÇ≈Ç∑ 1998/09/11 by T.Soneoka */
**	if (QueryDs1On()
**	&& (CurrentPage != NULL)
**	&& (CurrentPage->Position < DOC_POS_MOVE_TO_SCAN)) {
**		CluchOn();
**		StartTxMotor();
**		while (CurrentPage->Position < DOC_POS_MOVE_TO_SCAN) {
**			wai_tsk(1);
**		}
**	}
**}
#endif


UBYTE QueryReduction(void)
{
/*
** ÉÅÉÇÉäÉRÉsÅ[ÅAÇaÇSÅ|ÅÑÇ`ÇSí~êœèàóùí«â¡
** 1999/02/17 by T.Soneoka
*/
#if (0)
**	if (ScannerMode == SCANNER_COPY_MODE) {
**		if ((SYS_DocumentScanSize == SYS_DOCUMENT_B4_SIZE)
**		&& (!PB4())) {
**			return (REDUCTION_B4_A4);
**		}
**	}
**	return (REDUCTION_NO);
#else
#if (0)
**	if (ScannerMode == SCANNER_COPY_MODE) {
**		if ((SYS_DocumentScanSize == SYS_DOCUMENT_B4_SIZE)
**		&& (!PB4())) {
**			return (REDUCTION_B4_A4);
**		}
**	} else {
**		if ((!CHK_UNI_ReductionPrint())
**		&& (SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)) {
**			if ((SYS_DocumentScanSize == SYS_DOCUMENT_B4_SIZE)
**			&& (!PB4())) {
**				return (REDUCTION_B4_A4);
**			}
**		}
**	}
**	return (REDUCTION_NO);
#else
	/*
	** É}ÉãÉ`ÉRÉsÅ[ÇÃå„ÇÃÇaÇSÅ|ÅÑÇ`ÇSëóêMïsãÔçá
	** 1999/03/04 by T.Soneoka
	*/
	return (ScanReduction);
#endif
#endif
}
