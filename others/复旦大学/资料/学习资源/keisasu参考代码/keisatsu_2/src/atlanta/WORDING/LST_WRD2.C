/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_WRD2.C
*	Author		: ŒKŒ´”ü‹I
*	Date		: 1996/11/05
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒŠƒXƒg—pŒÅ’è•¶š—ñiÊ‘œ—Ìˆæ‚Q)
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h" /* T.Nose 1996/07/04 */
#include "\src\atlanta\define\wording.h"

#if (PRO_CPU == SH7043) /* T.Nose 1996/07/03 */
	#pragma section LST_WRD0	/* ƒZƒNƒVƒ‡ƒ“–¼‚Ìw’è LST_WRD0 */
#endif

#if defined(CHN) || (PRO_DUMMY_WORDING == DISABLE) /* By H.Fujimura 2002/07/11 */
	CONST UBYTE LST_DUMMY_WORD2[] = "\0";
#elif defined (KEISATSU) /* Œx@FAX 05/05/26 Î‹´³˜a */
	CONST UBYTE PWRD_2ndWordingTop[] = "\0";
#else
	#include LST_WORDING_2
#endif

#if (PRO_CPU == SH7043) /* T.Nose 1996/07/03 */
	#pragma section
#endif
