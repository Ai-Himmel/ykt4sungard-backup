/**********************************************************************************************
*        ANZU より移植      By Y.Suzuki 1996/10/11
*        File Name : MEMINDEX.C
*                    ﾒﾓﾘ管理使用ﾃﾞｰﾀ
*      Module Name :
**********************************************************************************************/
#include "\src\atlanta\define\product.h"
/* #include "\src\atlanta\define\mem_max.h" */
#include "\src\atlanta\define\mem_def.h"

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/08/06 Y.Murata */


 #if (PRO_PRINT_TYPE == LASER)
#pragma	section	INDEX_TBL
/* インデックス・テーブル */
struct IndexTableData_t MEM_IndexTable[MEM_INDEX_TABLE_MAX] = {0};
#pragma	section
 #endif

#pragma	section	MEMINDEX
/* インデックス・テーブル */
#if (PRO_PRINT_TYPE == LASER)
struct IndexTableData_t MEM_IndexTable2[MEM_INDEX_TABLE_MAX2] = {0};
#else
struct IndexTableData_t MEM_IndexTable[MEM_INDEX_TABLE_MAX] = {0};		/* add #if() 1998/10/06 Y.Murata */
#endif

/* FATエリア */
UWORD MEM_FATArea[MEM_FAT_AREA_MAX] = {0};

#pragma	section


#if (PRO_CPU == SH7043)
	/*	RISC DRAM アクセスにDMAを使わない
	**	ソフトによるREAD/WRITEにバイトのポインタを使用する By Y.Suzuki 1996/07/03
	*/
	#pragma	section	MEMSTRAREA
/*	UBYTE MEM_StoreArea[]= {0};*/
	/* malloc()を使用するため宣言を変更 By Y.Suzuki 1997/09/10 */
	union {
		DWORD dummy;					/* 4バイト境界にすためのダミー */
		UBYTE MEM_StoreArea[MEM_SCRAMBLE_INTERNAL_BLOCK * MEM_BLOCK_SIZE];
	}HeapArea = {0};
	#pragma	section
/*	UBYTE *Brk = (UBYTE *)&HeapArea;	sbrk()で割り付けた領域の最終アドレス */
	UBYTE *brk = 0;
#endif


#else


#if (PRO_CPU == SH7043) /* By S.Kawasaki 1996/03/11 */
	/*
	** RISCコンパイラー用のデータセクションを設定します。
	** MEMINDEXはDMEMINDEXの名前が自動的に設定されます。
	** 86系のセグメント名に相当する。
	** By S.Kawasaki 1996/03/11
	*/
	#pragma	section	MEMINDEX
#endif

/* インデックス・テーブル */
struct IndexTableData_t MEM_IndexTable[MEM_INDEX_TABLE_MAX] = {0};

/* FATエリア */
UWORD MEM_FATArea[MEM_FAT_AREA_MAX] = {0};

#if (PRO_CPU == SH7043) /* By S.Kawasaki 1996/03/11 */
	#pragma	section
#endif

#if (PRO_CPU == SH7043)
	/*	RISC DRAM アクセスにDMAを使わない
	**	ソフトによるREAD/WRITEにバイトのポインタを使用する By Y.Suzuki 1996/07/03
	*/
	#pragma	section	MEMSTRAREA
/*	UBYTE MEM_StoreArea[]= {0};*/
	/* malloc()を使用するため宣言を変更 By Y.Suzuki 1997/09/10 */
	union {
		DWORD dummy;					/* 4バイト境界にすためのダミー */
		UBYTE MEM_StoreArea[MEM_SCRAMBLE_INTERNAL_BLOCK * MEM_BLOCK_SIZE];
	}HeapArea = {0};
	#pragma	section
/*	UBYTE *Brk = (UBYTE *)&HeapArea;	sbrk()で割り付けた領域の最終アドレス */
	UBYTE *brk = 0;
#endif

#endif /* End of #if (PRO_MINOLTA_TEST_FUNC == ENABLE) 1998/08/06 Y.Murata */

