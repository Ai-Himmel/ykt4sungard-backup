/************************************************************************
*	System		: POPLAR/ANZU-L
*	File Name	: INI_PRO.H
*	Author		: –ØŒ³C
*	Date		: 1998/08/24
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^
*	Description	: ‚b‚o‚t‰Šú‰»ŠÖ”ƒvƒƒgƒ^ƒCƒvéŒ¾
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#ifndef	INI_PRO2_H
	#define	INI_PRO2_H	1

#include "\src\atlanta\define\product.h"

/***************/
/* INI_CPU_I.C */
/***************/
/* void InitializeCPU(void); */
#define InitializeCPU_p	(*InitializeCPU_vec)

/***************/
/* INI_CPU_O.C */
/***************/
void InitializeInternalDevice(void);

void INI_Start10msTimer(void);

void InitializeSystemProcess(void);

/* void InitializeSystem(void); */
#define InitializeSystem_p (*InitializeSystem_vec)

#endif	/* End of File */
