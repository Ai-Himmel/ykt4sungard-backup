/*
**	%W%
**	File Name:	\prj\Eva\src\main\rt_copy.c
**	Create:	1998/08/20	by Masahiro,IIDA
**	Description:
**		リアルタイム・コピー・プリント管理
**	Changes:
**
*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\realtcpy.h"

void SetRealTimeCopyBlock(UWORD mode,		/* 解像度 */
							UWORD size)		/* 原稿サイズ */
{
	RealTimeCopyFile.Mode = mode;
	RealTimeCopyFile.Size = size;
}

