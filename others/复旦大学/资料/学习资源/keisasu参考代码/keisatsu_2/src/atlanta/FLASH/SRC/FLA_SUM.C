/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : fla_sum.c                                                */
/*  作成者       : 桑原美紀                                                 */
/*  日  付       : 1997/04/25                                               */
/*  概  要       : コマンド書込みチェック			                        */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\flash\define\fla_pro.h"
#include	"\src\atlanta\flash\define\fla_def.h"
#include	"\src\atlanta\flash\ext_v\fla_tbl.h"
#include	"\src\atlanta\flash\ext_v\rom_tbl.h"	/* 1998/08/06 Y.Murata */

#include	"\src\atlanta\flash\define\sys_pro.h"

/*************************************************************************
	module		:[コマンド書込みチェック（１６ビット・サムチェック]
	function	:[書込みチェックの為のデータ合計数を取得]
	return		:[データ合計数]
	common		:[]
	condition	:[]
	comment		:[ＲＯＭ０，ＲＯＭ１の各合計数も表示する為、値を返すように変更 ** 97/08/11 M.Kuwahara **
]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1997/04/25]
	author		:[桑原美紀]
*************************************************************************/
/*UWORD	GetWordSumCheck( void )*/
UWORD	GetWordSumCheck( UWORD *Rom0_sum,
						 UWORD *Rom1_sum )

{
	UBYTE	sector_cnt;			/* ｾｸﾀｶｳﾝﾀ */
	UWORD	*TopAddress;		/* 先頭ｱﾄﾞﾚｽ */
	UDWORD	SizeCounter;		/* ｻｲｽﾞｶｳﾝﾀ */
	UWORD	SumCheck;			/* ﾃﾞｰﾀ合計数 */
	UWORD	rom_sum;			/* ROM毎の合計数 */

	SumCheck = 0;
	*Rom0_sum = 0;
	*Rom1_sum = 0;

	for (sector_cnt = 0; sector_cnt < SECTOR_MAX; sector_cnt++) {
		rom_sum	= 0;
		if (SYS_RomMap[sector_cnt].Status == ROM_USE) {
			TopAddress = (UWORD *)((UDWORD)FLASH_MEM + SYS_RomMap[sector_cnt].StartAddress);
			for( SizeCounter = 0; SizeCounter < (UDWORD)SYS_RomMap[sector_cnt].Size; SizeCounter += 2 ){
				rom_sum		+= *TopAddress;
				SumCheck	+= *TopAddress;
				TopAddress ++;
/*				SumCheck	+= *TopAddress++;*/
			}
		}
		if (SYS_RomMap[sector_cnt].StartAddress < 0x00080000L) {	/* ROM0の合計数 */
			*Rom0_sum += rom_sum;
		}
		else{
			*Rom1_sum += rom_sum;
		}
	}

	return( SumCheck );

#if (0)
	UBYTE	RomMapNo;			/* ROM_MAPﾃｰﾌﾞﾙNo */
	UWORD	*TopAddress;		/* 先頭ｱﾄﾞﾚｽ */
	UDWORD	Size;				/* ﾌﾟﾛｸﾞﾗﾑｻｲｽﾞ */
	UDWORD	SizeCounter;		/* ｻｲｽﾞｶｳﾝﾀ */
	UWORD	SumCheck	= 0;	/* ﾃﾞｰﾀ合計数 */

	for( RomMapNo = 0; SYS_RomMap[RomMapNo].Status != NOT_ROM_USE; RomMapNo++ ){
		TopAddress = (UWORD *)(FLASH_MEM + SYS_RomMap[RomMapNo].StartAddress);
		Size = (UDWORD)( SYS_RomMap[RomMapNo].Size + 1 );
		for( SizeCounter = 0; SizeCounter < Size; SizeCounter++ ){
			SumCheck	+= *TopAddress++;
		}
	}

	return( SumCheck );
#endif

}

#if (PRO_NEW_JIG == ENABLE)	/* YAWARAより移植 2002/06/05 T.Takagi */
/*************************************************************************
	module		:[コマンド書込みチェック（１６ビット・サムチェック]
	function	:[指定セクタのチェックサムを獲得する]
	return		:[データ合計数]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1999/10/16]
	author		:[Masahiro Iida]
*************************************************************************/
UWORD	JIG_GetSumCheck(UBYTE sector_start,
					UBYTE sector_end)

{
	UBYTE	sector_cnt;			/* ｾｸﾀｶｳﾝﾀ */
	UWORD	*top_addr;			/* 先頭ｱﾄﾞﾚｽ */
	UDWORD	size_cntr;			/* ｻｲｽﾞｶｳﾝﾀ */
	UWORD	sum_check;			/* ﾃﾞｰﾀ合計数 */

	sum_check = 0;

	for (sector_cnt = sector_start; sector_cnt < sector_end; sector_cnt++) {
		if (SYS_RomMap[sector_cnt].Status == ROM_USE) {
			top_addr = (UWORD *)((UDWORD)FLASH_MEM + SYS_RomMap[sector_cnt].StartAddress);
			for( size_cntr = 0; size_cntr < (UDWORD)SYS_RomMap[sector_cnt].Size; size_cntr += 2 ){
				sum_check += *top_addr;
				top_addr++;
			}
		}
	}
	return(sum_check);
}
#endif
