/*
 *	@(#)%W%
 *	FileName:	h:/prj/Eva/Src/scn/scnpower.c
 *	Create:	Wed Feb 25 16:55:50 1998	by	ishiyama
 *	Description:
 *		24V Power Control Routine
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\scn_tbl.h"
#include "\src\atlanta\define\cmn_pro.h"
/*
 *	Name:	Scanner Power On
 *	Create:	Wed Feb 25 18:07:32 1998	by	ishiyama
 *	Synopsis:
 *		#include	"power.h"
 *		void	ScannerPowerOn(void);
 *	Description:
 *		24V Power On for Scanner
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ScannerPowerOn(void)
{
	UBYTE	Work;
	BOOL	CurrentInt;

	CurrentInt = CheckInterruptEnable();
	CMN_DisableInterrupt();					/* Task Switching ñhé~ÇÃÇΩÇﬂ */
	PC_24V_On();
	PowerCtrl |= SCANNER_POWER;
	if (CurrentInt) {
		CMN_EnableInterrupt();
	}
}

/*
 *	Name:	Scanner Power Off
 *	Create:	Wed Feb 25 18:14:42 1998	by	ishiyama
 *	Synopsis:
 *		#include	"power.h"
 *		void	ScannerPowerOff(void);
 *	Description:
 *		24V Power Off for Scanner
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ScannerPowerOff(void)
{
	UBYTE	Work;

	BOOL	EnableInt;

	EnableInt = CheckInterruptEnable();
	CMN_DisableInterrupt();					/* Task Switching ñhé~ÇÃÇΩÇﬂ */
	PowerCtrl &= ~SCANNER_POWER;
	if (PowerCtrl == 0) {
	/* ä‘à·Ç¢ÅBÇ±ÇÍÇ™å¥àˆÇ≈ÉJÉoÅ[ÉIÅ[ÉvÉìéûÇ…24VÇ™ONÅAOFFÇåJÇËï‘ÇµÇƒÇ¢ÇΩ 2002/11/28 T.Takagi */
	/*	PC_24V_On(); */
	}
	if (EnableInt) {
		CMN_EnableInterrupt();
	}
}
