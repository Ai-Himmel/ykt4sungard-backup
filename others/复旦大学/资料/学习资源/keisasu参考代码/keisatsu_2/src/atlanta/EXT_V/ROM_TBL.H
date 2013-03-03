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
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysmax.h"

extern CONST UBYTE ROM_Revision[ROM_REVISION_MAX];
extern CONST UBYTE AIFUL_Model;	/* 2002/02/13 H.Yoshikawa */

#if (PRO_EXT_ROM == ENABLE)
extern CONST UWORD ExtRomType;
extern CONST UBYTE EXT_ROM_Revision[SYS_EXT_ROM_MAX][ROM_REVISION_MAX];
#endif

#endif
