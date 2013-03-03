/*
 *	@(#)$Id: PRTQUEUE.H,v 1.1.1.1 2005/04/04 04:24:06 mi93007 Exp $
 *	FileName:	/home2/prj/Eva/Src/inc/prtqueue.h
 *	Create:	Thu Mar 26 11:37:00 1998	by	ishiyama
 *	Description:
 *		Print Queue Header File
 *	Change Log:
 *		
 */
#ifndef	PRINTQUEUE_H
	#define PRINTQUEUE_H

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mem_def.h"

#define NUM_OF_PAGE_MEMORY_BLOCK	4
#define	PAGE_MEMORY_BLOCK_SIZE	(PRT_PAGEMEM_AREA / NUM_OF_PAGE_MEMORY_BLOCK)

#define PRINT_INDEX_QUEUE_SIZE	2
#define PRINT_PAGE_QUEUE_SIZE	1	/* 4 -> 1 By O.Kimoto 1998/10/21 */

/* 種別 */
#define PRTKIND_ENCODED			1
#define PRTKIND_LIST			2
#define PRTKIND_IMAGE			3

struct PrintIndexQElement {
	BYTE	Kind;						/* Image or List or List+Image */
	UWORD	ListNumber;					/* List の種別 (see lst_def.h) */
	UWORD	ListNumberSub;				/* List の種別 (see lst_def.h) */
#if (0)	/* 1998/10/05 by T.Soneoka */
**	struct IndexTableReadData	Index;	/* Memory Index for Read */
#endif
	struct MEM_IndexData_t		Index;	/* Memory Index for Read */
#if (0)	/* Delete By O.Kimoto 1998/10/22 */
** 	BOOL	Composit;					/* Page 合成する／しない */
#endif
};

struct PrintPageQElement {
	BYTE	Mode;						/* Vertical Mode SYS_* (see. doc.h) */
	UWORD	Lines;						/* Total Line */
	UBYTE	Reduction;					/* 縮小率 0:自動縮小 1-100:% */
/* 	BOOL	Copy; */						/* Copy or Rx */
/* 	BYTE	Handle; */						/* Page Block Handle Page Block Area を解放するとき必要 */
	UWORD	*Start;						/* Image Start Address */
	UDWORD	Count;						/* Image Size by UWORD count */
/* 	BOOL	Composit; */					/* Page 合成する／しない */
#if (0)	/* 1998/10/10 by T.Soneoka */
**	UBYTE	Cassette;					/* Cassette PRT_MP_TRAY or PRT_CASSETTE */
#endif
	UBYTE	Size;						/* Print Size A4/B4 */
};

struct PrintDmacQElement {
	UWORD	*Start;						/* Image Start Address */
	UDWORD	Count;					/* DMA Count */
};

struct PageBlockAlloc {
	BOOL	Used;						/* Used or Not Used */
	BOOL	Cont;						/* 続くブロックあり */
	struct PrintDmacQElement	Address; /* 管理エリア */
};

/*
 *	Print Page Control
 */
#define PG_DMA_YET	0
#define PG_DMA_NOW	1
#define PG_DMA_END	2

struct PrintPage {
	BOOL	Exist;						/* 割付けの有無 */
	struct PrintIndexQElement	Index;		/* Index Queue の要素 */
	BYTE	Decode;						/* Decode {未|中|完} */
	UBYTE	*Start;						/* Image Data Start Address */
	UBYTE	*End;						/* Image Data End Address */
	BYTE	Dma;						/* DMA {未|中|完} */
};

/*
 *	Function Prototypes
 */
void	InzPrintIndexQ(void);
BOOL	EmptyPrintIndexQ(void);
UBYTE	NumberOfPrintIndexQ(void);
void	PutPrintIndexQ(struct PrintIndexQElement Data);
struct PrintIndexQElement	*GetPrintIndexQ(void);
struct PrintIndexQElement	*PeekPrintIndexQ(void);
struct PrintIndexQElement	*QueryLastPrintIndexQ(void);
void	InzPrintPageQ(void);
BOOL	EmptyPrintPageQ(void);
UBYTE	NumberOfPrintPageQ(void);
void	PutPrintPageQ(struct PrintPageQElement Data);
struct PrintPageQElement	*GetPrintPageQ(void);
struct PrintPageQElement	*PeekPrintPageQ(void);
void	InzPrintDmacQ(void);
BOOL	EmptyPrintDmacQ(void);
UBYTE	NumberOfPrintDmacQ(void);
void	PutPrintDmacQ(struct PrintDmacQElement Datau);
struct PrintDmacQElement	*GetPrintDmacQ(void);
struct PrintDmacQElement	*PeekPrintDmacQ(void);
void	InzPrintLineImageQ(void);
BOOL	EmptyPrintLineImageQ(void);
UBYTE	NumberOfPrintLineImageQ(void);
void	PutPrintLineImageQ(UBYTE *Data);
UBYTE	*GetPrintLineImageQ(void);
UBYTE	*PeekPrintLineImageQ(void);

void	InzPageMemoryControl(void);
BYTE	AllocPageMemoryBlock(UWORD Lines, struct PrintDmacQElement *KeepArea);
void	FreeReadPageMemoryBlock(int	BlockHandle);

BOOL	QueryListWithImage(
	UWORD	ListNubmer);


#endif /* PRINTQUEUE_H */
