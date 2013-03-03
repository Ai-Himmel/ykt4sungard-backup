#ifndef CPU_TBL_H
 #define CPU_TBL_H 1
/************************************************************************
 * ＣＰＵﾊﾞｰｼﾞｮﾝ名を定義 (16 Chars + NULL)								*
 * CPU_Revision[ROM_REVISION_MAX] = "0123456789ABCDEF";					*
 * 01234 : 機種名														*
 * 5	 : 空白															*
 * 678	 : 仕向国名(ISO参照)											*
 * 9	 : 空白															*
 * ABCDEF: バージョン名													*
 ************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysmax.h"

extern CONST UBYTE CPU_Revision[ROM_REVISION_MAX];

#endif

