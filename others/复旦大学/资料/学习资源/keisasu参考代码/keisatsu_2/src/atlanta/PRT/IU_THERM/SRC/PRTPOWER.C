/*
 *	@(#)$Id: PRTPOWER.C,v 1.1.1.1 2005/04/04 04:24:05 mi93007 Exp $
 *	FileName:	/prj/Eva/Src/prt/prtpower.c
 *	Create:	Wed Feb 25 16:55:50 1998	by	ishiyama
 *	Description:
 *		Printer 24V Power Control Routine
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\define\scn_def.h"
#include "\src\atlanta\satsuki2\ext_v\scn_dath.h"
 #else
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
 #endif

/*
 *	Name:	Printer Power On
 *	Create:	Wed Feb 25 18:07:32 1998	by	ishiyama
 *	Synopsis:
 *		#include	"power.h"
 *		void	PrinterPowerOn(void);
 *	Description:
 *		24V Power On for Printer
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	PrinterPowerOn(void)
{
	UBYTE	IntEnble;

	IntEnble = CheckInterruptEnable();
	CMN_DisableInterrupt();					/* Task Switching ñhé~ÇÃÇΩÇﬂ */
	PC_24V_On();
	PowerCtrl |= PRINTER_POWER;
	if (IntEnble) {
		CMN_EnableInterrupt();
	}
}

/*
 *	Name:	Printer Power Off
 *	Create:	Wed Feb 25 18:14:42 1998	by	ishiyama
 *	Synopsis:
 *		#include	"power.h"
 *		void	PrinterPowerOff(void);
 *	Description:
 *		24V Power Off for Printer
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	PrinterPowerOff(void)
{
	UBYTE	IntEnble;

	IntEnble = CheckInterruptEnable();
	CMN_DisableInterrupt();					/* Task Switching ñhé~ÇÃÇΩÇﬂ */
	PowerCtrl &= ~PRINTER_POWER;
	if (PowerCtrl == 0) {
	/* ä‘à·Ç¢ÅBÇ±ÇÍÇ™å¥àˆÇ≈ÉJÉoÅ[ÉIÅ[ÉvÉìéûÇ…24VÇ™ONÅAOFFÇåJÇËï‘ÇµÇƒÇ¢ÇΩ 2002/11/28 T.Takagi */
	/*	PC_24V_On(); */
	}
	if (IntEnble) {
		CMN_EnableInterrupt();
	}
}
