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

#if (PRO_NEW_JIG == ENABLE)	/* 2002/06/05 T.Takagi */
#include "\src\atlanta\flash\define\fla_def.h"
#endif

#define ROM_REVISION_MAX	17		/* (16+NULL) */

/*------------------------------------------------------------------------
**	ポプラＢ
*/
#if defined(POPLAR_B)
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLAR_B  970519";
#endif

/*------------------------------------------------------------------------
**	ポプラＬ
*/
#if defined(POPLAR_L)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLAR_L  970519"; */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLAR_L  980415";	/* オーバイレーズ対応版 1998/04/15 by T.Soneoka */
#endif

/*------------------------------------------------------------------------
**	ポプラＨ
*/
#if defined(POPLAR_H)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLAR_H  970519";*/
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71H2 JG2 020702";
#endif

/*------------------------------------------------------------------------
**	アンズＬ
*/
#if defined(ANZU_L)
	/*CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "ANZU_L    970519";*/
	/*CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "ANZU_L    A0A0A0";*/	/*980427 正式バージョン*/
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "ANZU_L    B0A0A0";	/*980611 正式バージョン*/
#endif

/*------------------------------------------------------------------------
**	サカキ
*/
#if defined(SAKAKI)
 #if (PRO_NEW_JIG == DISABLE)		/* 白樺用梱包状態で書き換え可能治具以外 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "SAKAKI    980518";
 #else
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D83   JG2 020925";
 #endif
#endif

/*------------------------------------------------------------------------
**	ＨＩＮＯＫＩ
*/
#if defined(HINOKI) || defined (HINOKI2) || defined (HINOKI3)	/* HINOKI2 2002/06/04 T.Takagi */
/*        CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "HINOKI    981012"; */
 #if (PRO_NEW_JIG == DISABLE)		/* 白樺用梱包状態で書き換え可能治具以外 */
    CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "HINOKI    981115"; /* 受信モータ熱くなる不具合修正 1999/11/15 by T.Soneoka */
 #else	/* NEW JIG */
 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86   JG2 020614";
 #endif
#endif

/*------------------------------------------------------------------------
**	ＳＡＴＳＵＫＩ
*/
#if defined(SATSUKI2)
/*        CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "HINOKI    981012"; */
 #if (PRO_NEW_JIG == DISABLE)		/* 白樺用梱包状態で書き換え可能治具以外 */
    CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "HINOKI    981115"; /* 受信モータ熱くなる不具合修正 1999/11/15 by T.Soneoka */
 #else	/* NEW JIG */
 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86   JG2 020614";
 #endif
#endif

CONST UDWORD FLASH_MEM = 0x200000L;			/* 1998/08/06 Y.Murata */

#if (PRO_NEW_JIG == ENABLE)	/* 2002/06/04 T.Takagi */
CONST UBYTE CGROM_ENABLE = 0;				/* CGROMなし:0 CGROMあり:1 */
/* For New JIG */
CONST UDWORD JIG_MASTER_MEM = 0x100000L;

CONST struct FlashDev_t FlashDeviceCode[] = {
	{
		0x0004,	/* 富士通 */
		0x2258,	/* 8MbitFlash : 3V Flash */
	},
	{
		0x0020,	/* STマイクロエレクトロニクス */
		0x2249,	/* 16MbitFlash : 3V Flash  */
	},
	{
		0x0000,	/* 終了コード */
		0x0000,	/* 終了コード */
	},
};
#endif
