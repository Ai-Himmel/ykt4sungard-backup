/**********************************************************************************************
*				By : NOBUKO
*			  Date : Fri 03 Dec. 1993 (\SRC\RICE\DEFINE\MEM_PRO.H)
*		 Copy Date : Tue 12 Sep. 1995
*				   : 1996/10/18 From \src\kobe\anzu\define\mem_pro.h By M.Kotani
*		 File Name : MEM_PRO.H
*				メモリ管理関係プロトタイプ
**********************************************************************************************/
#ifndef MEM_PRO
	#define MEM_PRO

#include "\src\atlanta\ext_v\memertbl.h"

#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui June 19,1998 */
#include "\src\atlanta\define\cl1expro.h"
#endif

/* <MEMCHECK.C> */
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
UBYTE MEM_CheckStoreCode(struct MEM_IndexData_t *);
UBYTE MEM_CheckStoreMode(struct MEM_IndexData_t *);
UBYTE MEM_CheckStoreSize(struct MEM_IndexData_t *);
#endif
UBYTE MEM_CheckMilliInch(struct MEM_IndexData_t *);
UWORD MEM_CheckStoreLineCount(struct MEM_IndexData_t *);
UWORD MEM_CheckIndexNo(struct MEM_IndexData_t *);
UWORD MEM_CheckMostSmallPage(UBYTE Item, UWORD No);	/* ﾌﾟﾛﾄﾀｲﾌﾟの記述追加 1996/08/12 by K.Watanabe */
UBYTE MEM_CheckStoreDoc(UBYTE Item);
UBYTE MEM_CheckUseIndex(void);
#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/09/04 */
UBYTE MEM_CheckStoreArea(struct MEM_IndexData_t *);
UBYTE MEM_CheckStoreCassette(struct MEM_IndexData_t *);
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)
UBYTE MEM_FCOT_CheckStoreMode(struct MEM_IndexData_t *);
UBYTE MEM_FCOT_CheckStoreSize(struct MEM_IndexData_t *);
UWORD MEM_FCOT_CheckIndexNo(struct MEM_IndexData_t *);
#endif
UWORD MEM_CheckConflictIndexNo (struct MEM_StoreData_t *);

/* <MEMCLEAR.C> */
void MEM_ClearAll(void);
void MEM_ClearAllIndexArea(void);
UBYTE MEM_ClearPage(struct MEM_IndexData_t *);
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
UBYTE MEM_ClearDocAndFATArea(UBYTE, UWORD, UBYTE);
UBYTE MEM_ClearPageAndFATArea(struct MEM_IndexData_t *);
#endif
UBYTE MEM_ClearDoc(UBYTE, UWORD, UBYTE);
UBYTE MEM_ClearBreak(struct MEM_IndexData_t *);
UBYTE MEM_ClearPowerDown(void);
void ClearIndexAndFATAreaAppointNo(UWORD);
void ClearIndex(UWORD);
/* UBYTE MEM_ClearBoxDocAndFATArea (UBYTE ,UWORD,UBYTE); 1997/04/28  By T.Yamaguchi */
/* UBYTE MEM_ClearBoxDoc(UBYTE ,UWORD,UBYTE); 1997/04/28  By T.Yamaguchi *	/
/* UBYTE MEM_ClearBoxAllDocAndFATArea (UBYTE,UBYTE); 1997/04/28  By T.Yamaguchi */
UBYTE MEM_ClearBoxNoAppintDoc(UBYTE ,UBYTE,UWORD);
UBYTE MEM_IndexConvert(UBYTE,UBYTE,UWORD,UWORD);
UBYTE MEM_ClearStroingPCPrintFile (void);	/* 1998/04/08 Y.Murata MEM_PC_BUG*/

/* <MEMCOUNT.C> */
UWORD MEM_CountItemTotalPage (UBYTE);			/* 原稿指定のための原稿種別 */
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998 */
UWORD MEM_CountTotalPage(UBYTE, UWORD, UBYTE);	/* 変更 1997/03/12  By T.Yamaguchi */
#endif
UWORD MEM_CountFinalPage (UBYTE, UWORD, UBYTE);		/* 原稿指定のための原稿種別 1997/04/01  By T.Yamaguchi */
UWORD MEM_CountTopPage (UBYTE, UWORD, UBYTE);			/* 原稿指定のための原稿種別 1997/04/01  By T.Yamaguchi */
UWORD MEM_CountTotalEmptyPage(void);
UWORD MEM_CountTotalStorePage(void);
UWORD MEM_CountTotalBlock(UBYTE, UWORD,UBYTE);
UWORD MEM_CountPageBlock(struct MEM_IndexData_t *);

#if (0)/*	By Y.Suzuki 1996/10/24	*/
**#if (PRO_MEM_CONTROL_TYPE == RESERVED) /* By S.K Dec.16,1995 */
**	WORD MEM_CountTotalEmptyBlock(void);
**#else
**	UWORD MEM_CountTotalEmptyBlock(void);
**#endif
#endif

#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998 */
UWORD MEM_CountTotalEmptyBlock(void);
#endif
UWORD MEM_CountTotalStoreBlock(void);
UBYTE MEM_CountUseBlockRate(void);
UBYTE MEM_CountEmptyBlockRate(void);
UWORD MEM_CountTotalCapacity(void);
UWORD ChainBlockCounter(UWORD);
UWORD MEM_CountMaxPage(UBYTE, UWORD, UBYTE);
UBYTE MEM_DetectEmptyNo(UBYTE ,UBYTE);
struct MEM_StoredNo_t *MEM_GetStoredIndexNo(UBYTE ,UBYTE);
UWORD MEM_CountTotalBoxPage (UBYTE,UBYTE);
UWORD MEM_CountTotalEachDocPage (UBYTE ,UWORD ,UBYTE);

/* <MEMDUAL.C> */
UBYTE MEM_DualOpen(struct MEM_StoreData_t *, struct MEM_IndexData_t *, struct MEM_ExecData_t *);
void MEM_DualClose(struct MEM_ExecData_t *, UWORD);

/* <MEMFAT.C> */
void ClearAllFATArea(void);
void ClearFATArea(UWORD);
void InitFATAreaSetPageReg(UWORD, UWORD);
void CleaningFATArea(void);
void MEM_ClearAllFATAreaInTimer(void);

/* <MEMREAD.C> */
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
UWORD MEM_ReadOpen(struct MEM_IndexData_t *, struct MEM_ExecData_t *);
#endif
UBYTE MEM_Read(UBYTE, struct MEM_ExecData_t *);
#define	MEM_ReadGetNextBlockNo	(*mem_read_get_next_blk_no_exttbl)
/* UWORD MEM_ReadGetNextBlockNo(UWORD);By Y.Suzuki 1997/04/01 */
UDWORD MEM_CalculateDMAAddress(UWORD);
#if (PRO_CPU == SH7043)
#define	MEM_CalculateSoftAddress	(*mem_calculate_softaddr_exttbl)
/* UBYTE *MEM_CalculateSoftAddress (UWORD);	 先頭アドレスを知りたいブロックNoを指定します By Y.Suzuki 1997/04/01 */
#endif

/* <MEMWRITE.C> */
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
UWORD MEM_WriteOpen(struct MEM_StoreData_t *, struct MEM_ExecData_t *);
void MEM_WriteClose(struct MEM_ExecData_t *, UWORD);
#endif
#if (PRO_CPU == SH7043)
UWORD MEM_MultiWriteOpen(struct MEM_StoreData_t *, struct MEM_ExecData_t *);
UWORD MEM_Write(UBYTE, struct MEM_ExecData_t *);
void MEM_MultiWriteClose(struct MEM_ExecData_t *, UWORD);
#endif
#define	MEM_WriteGetNextBlockNo	(*mem_write_get_nextblk_no_exttbl)
/* UWORD MEM_WriteGetNextBlockNo(struct MEM_ExecData_t *); By Y.Suzuki 1997/04/01 */

#endif
/*#if defined(POPLAR_H) && defined(JP0)*/
UWORD MEM_CheckTopEmptyBlock(UWORD , UWORD );/* NAGANO から移植 V851 By Y.Suzuki 2002/07/27 */
/*#endif*/
