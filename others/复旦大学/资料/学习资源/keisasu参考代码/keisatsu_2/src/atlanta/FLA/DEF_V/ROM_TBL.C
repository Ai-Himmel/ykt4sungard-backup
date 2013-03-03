/************************************************************************
 * 機種名ﾊﾞｰｼﾞｮﾝ名を定義 (16 Chars + NULL)								*
 * ROM_Revision[ROM_REVISION_MAX] = "0123456789ABCDEF";					*
 * 01234 : 機種名														*
 * 5	 : 空白															*
 * 678	 : 仕向国名(ISO参照)											*
 * 9	 : 空白															*
 * ABCDEF: バージョン名													*
 ************************************************************************/
#include "\src\atlanta\define\product.h"

#define ROM_REVISION_MAX	17		/* (16+NULL) */

/*------------------------------------------------------------------------
**	ポプラＢ
*/
#if defined(POPLAR_B)
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLAR_B  970519";
#endif


/*------------------------------------------------------------------------
**	ポプラＢＮ
*/
#if defined(POPLR_BN)
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLR_BN  990514";
#endif


/*------------------------------------------------------------------------
**	ポプラＬ
*/
#if defined(POPLAR_L)
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLAR_L  970519";
#endif

/*------------------------------------------------------------------------
**	ポプラＨ
*/
#if defined(POPLAR_H)
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLAR_H  970519";
#endif

/*------------------------------------------------------------------------
**	サカキ
*/
#if defined(SAKAKI)
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "SAKAKI    980518";
#endif

/*------------------------------------------------------------------------
**	アンズＬ
*/
#if defined(ANZU_L)
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "ANZU_L    970519";
#endif

/*------------------------------------------------------------------------
**	ＨＩＮＯＫＩ
*/
#if defined(HINOKI) || defined (HINOKI2) || defined (SATSUKI2) || defined (HINOKI3)	/* HINOKI2 2002/06/03 T.Takagi */
/* HINOKI By O.Kimoto 1998/09/04 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "HINOKI    98****";
#endif
