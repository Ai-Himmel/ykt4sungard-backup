/*
**	%W%
**	File Name:	\prj\Eva\src\inc\page_mem.h
**	Create:	1998/01/13	by Masahiro,IIDA
**	Description:
**		スキャナ＆プリンタ・ページメモリの定義
**	Changes:
**
*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\hinoki\define\scn_def.h"

#if (PRO_CPU == SH7043)
extern UBYTE	ScanPageMem[SCANPAGE_ROW][SCANPAGE_COL];
#endif
