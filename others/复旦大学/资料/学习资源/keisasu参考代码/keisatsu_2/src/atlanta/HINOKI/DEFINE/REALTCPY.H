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

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
/*---------------------------------------------------------------------------------------
 * リアルタイム・コピー実行管理データの定義
 *--------------------------------------------------------------------------------------*/
struct RealTimeCopyData {
	UBYTE Status;				/* 使用状態 */
	UBYTE Reduction;			/* 縮小率 */
	UBYTE Mode;					/* 解像度 */
	UBYTE Size;					/* サイズ：現在A4固定 */
};

/* 使用状態 */
#define REALT_CPY_EMPTY		0 /* 未使用 */
#define REALT_CPY_USE	0x01	/* コピー中 */
#define REALT_CPY_SCAN_END	0x02	/* コピー中(Scannerから次原稿無しが来た場合) */

#if (0)
/* 縮小率：mcopy.h参照 */
#define AUTO_REDUCTION 0xFF /* 自動縮小 */
#endif

#ifndef DEF_REALT_COPY
extern struct RealTimeCopyData RealTimeCopyFile;
#endif	/* DEF_REALT_COPY */

/*
**	Macro Define
*/
#define	SetRealTimeCopyReduc(reduc)		(RealTimeCopyFile.Reduction = (UBYTE)reduc)
#define	GetRealTimePrintReduc()			(RealTimeCopyFile.Reduction)
#define	GetRealTimePrintMode()			(RealTimeCopyFile.Mode)


/* rt_copy.c */
void InitRealTimeCopyFile(void);
BOOL GetRealTimeCopyBlock(void);
void SetRealTimeCopyBlock(UWORD, UWORD);
#endif	/* REALT_COPY_H */
