/*
**	%W%
**	File Name:	\prj\Eva\src\inc\realtcpy.h
**	Create:	1998/08/20	by Masahiro,IIDA
**	Description:
**		リアル・タイム・コピー実行管理データの定義
**	Changes:
**
*/
#ifndef	REALT_CPY_H
	#define	REALT_CPY_H

#include "\src\atlanta\define\std.h"
/*---------------------------------------------------------------------------------------
 * リアルタイム・コピー実行管理データの定義
 *--------------------------------------------------------------------------------------*/
struct RealTimeCopyData {
	UBYTE Reduction;			/* 縮小率 */
	UBYTE Mode;					/* 解像度 */
	UBYTE Size;					/* サイズ：現在A4固定 */
};

extern struct RealTimeCopyData RealTimeCopyFile;
void SetRealTimeCopyBlock(UWORD, UWORD);

#endif	/* REALT_COPY_H */
