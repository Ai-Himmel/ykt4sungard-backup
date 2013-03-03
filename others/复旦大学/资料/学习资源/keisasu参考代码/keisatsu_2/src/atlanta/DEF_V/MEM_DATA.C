/**********************************************************************************************
*		ANZU より移植 By Y.Suzuki 1996/10/11
*		File Name : MEMDATA.C
*		ﾒﾓﾘ管理使用ﾃﾞｰﾀ
*	   Module Name :
**********************************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\SYSMAX.H"

#if (0)		/* Moved to BKUPRAM.H */
/* 空ブロックの先頭 */
UWORD MEM_TopEmptyBlock = 0;

/* 空ブロックの最終 */
UWORD MEM_EndBlock = 0;

/* 蓄積済ブロックの総数 */
UWORD MEM_TotalStoreBlockCounter = 0;

/* 蓄積可能ブロックの総数 */
UWORD MEM_TotalAvailableStoreBlkCnt = 0;

/* 有効FATエリアの最終ブロック */
UWORD MEM_AvailableMaxFATArea = 0;

/** DMA終了時に使用 */
UBYTE MEM_DMAEndStatus = 0;

/** XEROX仕様 マルチ・プログラム送信 に使用 */
UWORD MEM_MultiProgramOpenIndexNo[SYS_JOB_MAX] = {0};

/** 使用ブロック数カウント時の最終ブロックの種別 */
UWORD MEM_BlockCounterEndStatus = 0;
#endif

/* #if (PRO_CODEC_TYPE == MN86063) By Y.Suzuki 1996/10/12 */
#if (PRO_SCN_CODEC_TYPE == MN86063) || (PRO_SCN_CODEC_TYPE == MN86064)
/** スキャン原稿蓄積フラグ */
UBYTE MEM_ScanFlag = 0;
#endif
