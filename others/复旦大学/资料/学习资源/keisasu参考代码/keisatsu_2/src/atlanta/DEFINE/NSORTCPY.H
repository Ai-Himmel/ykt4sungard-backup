/*
**	%W%
**	File Name:	\prj\Eva\src\inc\nsortcpy.h
**	Create:	1998/07/13	by Masahiro,IIDA
**	Description:
**		ノン・ソート・コピー実行管理データの定義
**	Changes:
**
*/
#ifndef	NSORT_CPY_H
	#define	NSORT_CPY_H

#include "\src\atlanta\define\std.h"
/*---------------------------------------------------------------------------------------
 * ノン・ソートコピー実行管理データの定義
 *--------------------------------------------------------------------------------------*/
struct NonSortCopyData {
	UBYTE Status;				/* 使用状態 */
	UBYTE ReserveNumber;		/* 指定部数 */
	UBYTE Reduction;			/* 縮小率 */
	UBYTE Code;					/* 符号化方式：現在Image固定 */
	UBYTE Mode;					/* 解像度 */
	UBYTE Size;					/* サイズ：現在A4固定 */
	UWORD TotalLine;			/* 現在イメージメモリにある画像のトータルライン数 */
	UWORD ErrorLine;			/* 現在イメージメモリにある画像のエラーライン数(常時０) */
	UWORD StorePage;			/* 蓄積しているページ数 */
	UWORD PrintPage;			/* プリント済ページ数 */
};

/* 使用状態 */
#define NSORT_CPY_EMPTY		0 /* 未使用 */
#define NSORT_CPY_SETTING	0x01 /* コピー予約の確定から蓄積開始まで */
#define NSORT_CPY_STORE		0x02 /* コピー予約の確定から蓄積中、または、蓄積完了でまだ原稿あり */
#define NSORT_CPY_PRINT		0x04 /* 原稿プリント中 */
#define NSORT_CPY_SCAN_CONTI_PRINT	0x06 /* 読み取り原稿残しながらプリント中 */

#if (0)
/* 縮小率：mcopy.h参照 */
#define AUTO_REDUCTION 0xFF /* 自動縮小 */
#endif

#ifndef DEF_NONSORT_COPY
extern struct NonSortCopyData NonSortCopyFile;
#endif	/* DEF_NONSORT_COPY */

/*
**	Macro Define
*/
#define	IncNonSortCopyPrintPage()		(NonSortCopyFile.PrintPage++)
#define	GetNonSortCopyPrintPage()		(NonSortCopyFile.PrintPage)
#define	GetNonSortCopyStorePage()		(NonSortCopyFile.StorePage)
#define	ResetNonSortCopyPrintPage()		(NonSortCopyFile.PrintPage = 0)
#define	GetNonSortCopyReserveNumber()	(NonSortCopyFile.ReserveNumber)
#define	GetNonSortPrintReduc()			(NonSortCopyFile.Reduction)

/* nsort_cpy.c */
void InitNonSortCopyData(void);
BOOL GetNonSortCopyBlock(void);
void SetNonSortCopyBlock(UBYTE Number, UBYTE Reduction);
void OpenNonSortCopyBlock(UWORD mode, UWORD size);
void CloseNonSortCopyBlock(UWORD line, UWORD errline);
void IncNonSortCopyStorePage(void);
void NonSortCopyStoreEnd(void);
BOOL CheckEndNonSortCopy1Job(void);
#endif	/* MCOPY_H */
