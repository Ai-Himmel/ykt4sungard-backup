/*	By Y.Suzuki 1996/10/12	*/
/**********************************************************************************************
*				By : NOBUKO
*			  Date : Fri 03 Dec. 1993 (\SRC\RICE\EXT_V\MEM_DATA.H)
*		 Copy Date : Tue 13 Sep. 1995
*		 File Name : MEM_DATA.H
*						ﾒﾓﾘ管理使用ﾃﾞｰﾀ
**********************************************************************************************/
#ifndef mem_data_h
	#define	mem_data_h

#include "\src\atlanta\define\MEM_DEF.H"


#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/08/06 Y.Murata */
extern struct IndexTableData_t MEM_IndexTable2[MEM_INDEX_TABLE_MAX];
#endif

/** インデックス・テーブル */
extern struct IndexTableData_t MEM_IndexTable[MEM_INDEX_TABLE_MAX];
/** FATエリア */
extern UWORD MEM_FATArea[MEM_FAT_AREA_MAX];

/* #if (PRO_CPU == SH704X) || (PRO_CPU == SH7034) */
#if (PRO_CPU == SH7043)	/*	By Y.Suzuki 1996/10/12	*/
	/*	RISC DRAM アクセスにDMAを使わない
	**	ソフトによるREAD/WRITEにバイトのポインタを使用する By Y.Suzuki 1996/07/03
	*/
/*	extern UBYTE MEM_StoreArea[];*/
	extern union {
		DWORD dummy;					/* 4バイト境界にすためのダミー */
		UBYTE MEM_StoreArea[MEM_SCRAMBLE_INTERNAL_BLOCK * MEM_BLOCK_SIZE];
	}HeapArea;

	extern UBYTE *brk;	/* sbrk()で割り付けた領域の最終アドレス */

#endif

#if (0)		/* Moved to BKUPRAM.H */
/** 空ブロックの先頭 */
extern unsigned int  MEM_TopEmptyBlock;

/** 空ブロックの最終 */
extern unsigned int  MEM_EndBlock;

/** 蓄積済ブロックの総数 */
extern unsigned int  MEM_TotalStoreBlockCounter;

/** 蓄積可能ブロックの総数 */
extern unsigned int  MEM_TotalAvailableStoreBlkCnt;

/** 有効FATエリアの最終ブロック */
extern unsigned int  MEM_AvailableMaxFATArea;

/** DMA終了時に使用 */
extern UBYTE MEM_DMAEndStatus;

/** XEROX仕様 マルチ・プログラム送信 に使用 */
extern unsigned int  MEM_MultiProgramOpenIndexNo[SYS_JOB_MAX];

/** 使用ブロック数カウント時の最終ブロックの種別 */
extern unsigned int  MEM_BlockCounterEndStatus;

#endif

/* スキャナー位相ずれデバッグにつき復活 T.Nose 1998/02/05 */
/** スキャン原稿蓄積フラグ */
extern UBYTE MEM_ScanFlag;

#endif
