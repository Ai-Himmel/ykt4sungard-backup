/* By S.K Spe.21,1995 */
#ifndef ROM_TBL_H
 #define ROM_TBL_H 1
/************************************************************************
 * 機種名ﾊﾞｰｼﾞｮﾝ名を定義 (16 Chars + NULL)								*
 * ROM_Revision[ROM_REVISION_MAX] = "0123456789ABCDEF";					*
 * 01234 : 機種名														*
 * 5     : 空白															*
 * 678   : 仕向国名(ISO参照)											*
 * 9     : 空白															*
 * ABCDEF: バージョン名													*
 ************************************************************************/
/* 新規にこのファイルを追加しました。フラッシュのアドレスをdefineじゃなくﾃｰﾌﾞﾙにするため 1998/08/06 Y.Murata */

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysmax.h"

extern CONST UBYTE ROM_Revision[ROM_REVISION_MAX];

#if (PRO_NEW_JIG == ENABLE)	/* 2002/06/04 T.Takagi */
extern UDWORD FLASH_MEM;
extern CONST UDWORD JIG_MASTER_MEM;
extern CONST UBYTE CGROM_ENABLE;
extern CONST struct FlashDev_t FlashDeviceCode[];
#else
extern CONST UDWORD FLASH_MEM;			/* 1998/08/06 Y.Murata */
#endif


#endif
