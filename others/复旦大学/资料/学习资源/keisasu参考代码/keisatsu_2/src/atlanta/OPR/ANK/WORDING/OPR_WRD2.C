/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_WRD2.C
*	Author		: “n•ÓˆêÍ
*	Date		: 1996/10/23
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ‚k‚b‚c—pŒÅ’è•¶š—ñiÊ‘œ—Ìˆæ‚Q)
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\wording.h"

#if (PRO_CPU == SH7043)
	#pragma section OPR_WRD0	/* ƒZƒNƒVƒ‡ƒ“–¼‚Ìw’è COPR_WRD0 */
#endif

#if defined (KEISATSU) /* Œx@FAX 05/05/26 Î‹´³˜a */
	CONST UBYTE D2W_2ndWordingTop[]				= "\0";
#else
	#include D2W_WORDING_2
#endif

#if (PRO_CPU == SH7043)
	#pragma section
#endif
