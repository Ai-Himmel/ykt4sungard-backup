/***********************************************************************
*               BY:  T.Nose
*             DATE:  Apr.16,1998
*        FILE NAME:  fla_sube.c
*      DESCRIPTION:	 フラッシュ書換えチェック用モジュール群
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:
*        REFERENCE:
*      MODULE NAME:	UBYTE FLA_CheckSumROMData( void )
*					UBYTE FLA_CheckModelROMData( void )
*					void FLA_ClearSumROMData( void )
*					void FLA_ClearModelROMData(void)
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\sysmax.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\param.h"
#include "\src\atlanta\define\mntsw_e.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\mem_data.h"
#include "\src\atlanta\ext_v\rom_tbl.h"
#include "\src\atlanta\define\rom_def.h"

void FLA_ClearAllFATArea (void);

#pragma section INISYSPRO /* locate section name "PINISYSPRO" */

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
/************************************************************************
	module		:[ＲＯＭデータをサムチェックする]
	function	:[]
	return		:[
		0:サムチェック不一致
		1:サムチェック一致
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC(V.3.0C)]
	keyword		:[FLA]
	date		:[1998/04/15]
	author		:[野瀬敏弘]
************************************************************************/
UBYTE FLA_CheckSumROMData(void)
{
	UWORD *address;
	UWORD sum;

	sum = 0;
	address = (UWORD *)ROM_DATA_WRITE_ADDRESS;
	for (; address < (UWORD *)(ROM_DATA_WRITE_ADDRESS + 0x100000L); address++) {
		sum += *address;
	}
	if (sum == SYB_ROM_DataSumcheck) {
		return(1);
	}
	else {
		SYB_MaintenanceSwitch[MNT_SW_E4] += 0x01;
		return(0);
	}
}

/************************************************************************
	module		:[ＲＯＭデータのモデル名チェック]
	function	:[]
	return		:[
		0:モデル名不一致
		1:モデル名一致
	]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC(V.3.0C)]
	keyword		:[FLA]
	date		:[1998/04/15]
	author		:[野瀬敏弘]
************************************************************************/
UBYTE FLA_CheckModelROMData(void)
{
	UBYTE count;
	UBYTE *address;

	address = (UBYTE *)ROM_DATA_WRITE_ADDRESS;
	for (count = 0; count < SYS_BACKUP_RAM_TEST_AREA_MAX; count++) {
		if (ROM_Revision[count] != *address) {
			SYB_MaintenanceSwitch[MNT_SW_E2] |= 0x02;
			return(0);
		}
		address++;
	}
	return(1);
}

/************************************************************************
	module		:[ＲＯＭデータのチェックサムクリア]
	function	:[]
	return		:[なし]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC(V.3.0C)]
	keyword		:[FLA]
	date		:[1998/04/15]
	author		:[野瀬敏弘]
************************************************************************/
void FLA_ClearSumROMData(void)
{
	SYB_ROM_DataSumcheck = 0;
}

/************************************************************************
	module		:[ＲＯＭデータのモデル名クリア]
	function	:[]
	return		:[なし]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC(V.3.0C)]
	keyword		:[FLA]
	date		:[1998/04/15]
	author		:[野瀬敏弘]
************************************************************************/
void FLA_ClearModelROMData(void)
{
	UBYTE count;
	UBYTE *address;

	address = (UBYTE *)ROM_DATA_WRITE_ADDRESS;
	for (count = 0; count < SYS_BACKUP_RAM_TEST_AREA_MAX; count++) {
		*address = 0;
		address++;
	}
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[DRAMエリア内の初期化]
	function	:[
		全インデックス・エリアの初期化を行います
		全FATエリアの初期化を行います
	]
	return		:[なし]
	common		:[なし]
	condition	:[なし]
	comment		:[
		ALL RAM CLEAR 時に CALLしてください
		電源投入時にも必要に応じて CALLしてください
		DRAM容量自動判別も行ないます
		\src\atlanta\src\memclear.c からコピー
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/25]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void FLA_MEM_ClearAll (void)
{
	UBYTE i;
											/* DRAM容量自動判別にMEM_IndexTable[]を使用するので先にFATのクリアをしてしまいます */
	FLA_ClearAllFATArea();						/* FATエリアの初期化を行います */
	MEM_ClearAllIndexArea();				/* インデックス・テーブルの初期化を行います */
	for (i = 0; i < SYS_JOB_MAX; i++)
		MEM_MultiProgramOpenIndexNo[i] = 0xFF;
/*	InitializeDRAM_Parameter();*/				/* DRAMクリア時のパラメータのクリア (Sep.06,94) */

	return;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[FATエリアの初期化]
	function	:[
		FATエリアの初期化を行ないます
		有効FATエリアをチェーン化します
		DRAM容量の自動判別もここで行ないます

		MEM_TopEmptyBlock					初期化します
		MEM_TotalStoreBlockCounter			初期化します
		MEM_AvailableMaxFATArea				有効ブロック数が代入されます
	]
	return		:[なし]
	common		:[
		UWORD  MEM_FATArea[],
		UWORD  MEM_AvailableMaxFATArea,
		UWORD  MEM_TopEmptyBlock,
		UWORD  MEM_TotalStoreBlockCounter
	]
	condition	:[]
	comment		:[桐で動作確認済み	Oct.12,95
		\src\atlanta\src\memfat.c からコピー
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/01/08]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void FLA_ClearAllFATArea (void)
{
	UWORD i;					/* MEM_FATArea[i]中のﾎﾟｲﾝﾀ */
	UWORD j;					/* ﾁｪｰﾝ化するﾌﾞﾛｯｸNo.を示す */
	UWORD dram_ok_bit;			/* DRAMの初期化できたﾌﾞﾛｯｸを示すBITが1 */
	UWORD ok_bit;				/* dram_ok_bitのﾃﾝﾎﾟﾗﾘ */
	UWORD start_block_no;		/* 次に初期化するﾌﾞﾛｯｸNo. */
	UDWORD address;				/* 検出するアドレス */
	UDWORD check_size;			/* ﾃﾞｰﾀのｲﾝｸﾘﾒﾝﾄする単位 */
	UBYTE dram_ex_ok;			/* 拡張DRAMが存在していることを示すﾌﾗｸﾞ */
	struct IndexTableData_t	*mem_index;

	i = 0;
	j = 0;
	dram_ok_bit = 0;
	ok_bit = 0;
	start_block_no = 0;
	check_size = 0;
	dram_ex_ok = 0;

	/* 上位で割込み禁止にしたまま走ります */
	/* CMN_DisableInterrupt();	@** 割込禁止期間開始 */

	MEM_TotalAvailableStoreBlkCnt = 0;
	MEM_TopEmptyBlock = 0;							/* 空ブロックの先頭を示すグローバル変数の初期化 */
	MEM_TotalStoreBlockCounter = 0;					/* 使用ブロック数のトータルを示すグローバル変数の初期化 */
	MEM_BlockCounterEndStatus = MEM_EOP_BLOCK;		/* とりあえずEOPに初期化 *//*チェーンのブロックの最終の状態を示す*/
	MEM_ScanFlag = 0;
	MEM_DMAEndStatus = 0;

#if (PRO_CIPHER == DISABLE)/* By Y.Suzuki 1997/09/03 */
	if (CHK_UNI_MaskingDram()) {	/*By M.Kotani 1997/12/12*/
		MEM_TopEmptyBlock = MEM_DRAM_MASK_BLOCK;							/* 空ブロックの先頭を示すグローバル変数の初期化 */
		for (i = 0; i < MEM_DRAM_MASK_BLOCK; i++) {	/** FATエリアを初期化する */
			MEM_FATArea[i] = MEM_BAD_BLOCK;						/** アリロで使用する領域を無効領域とする */
		}
		for ( ; i < (MEM_FAT_AREA_STANDARD - 1); i++) {	/** FATエリアを初期化する */
			MEM_FATArea[i] = i+1;						/** 有効FATエリアに1～有効FAT_AREAを順番に入れる */
			MEM_TotalAvailableStoreBlkCnt++;			/** 蓄積可能ブロック数をインクリメント */
		}
	}
	else {
		for (i = 0; i < (MEM_FAT_AREA_STANDARD - 1); i++) {	/** FATエリアを初期化する */
			MEM_FATArea[i] = i+1;						/** 有効FATエリアに1～有効FAT_AREAを順番に入れる */
			MEM_TotalAvailableStoreBlkCnt++;			/** 蓄積可能ブロック数をインクリメント */
		}
	}
#else
	if ((EXT_ROM_Revision[ROM_EXT_SCRAMBLE][0] == 'D')
	 && (EXT_ROM_Revision[ROM_EXT_SCRAMBLE][1] == 'S')
	 && (EXT_ROM_Revision[ROM_EXT_SCRAMBLE][2] == '-')
	 && (EXT_ROM_Revision[ROM_EXT_SCRAMBLE][3] == '1')
	 && (EXT_ROM_Revision[ROM_EXT_SCRAMBLE][4] == '0')
	 && (EXT_ROM_Revision[ROM_EXT_SCRAMBLE][5] == '0')) {
		MEM_TopEmptyBlock = MEM_FAT_AREA_SCRAMBLE;							/* 空ブロックの先頭を示すグローバル変数の初期化 */
		for (i = 0; i < MEM_FAT_AREA_SCRAMBLE; i++) {	/** FATエリアを初期化する */
			MEM_FATArea[i] = MEM_BAD_BLOCK;						/** アリロで使用する領域を無効領域とする */
		}
		for ( ; i < (MEM_FAT_AREA_STANDARD - 1); i++) {	/** FATエリアを初期化する */
			MEM_FATArea[i] = i+1;						/** 有効FATエリアに1～有効FAT_AREAを順番に入れる */
			MEM_TotalAvailableStoreBlkCnt++;			/** 蓄積可能ブロック数をインクリメント */
		}
	}
	else {
		for (i = 0; i < (MEM_FAT_AREA_STANDARD - 1); i++) {	/** FATエリアを初期化する */
			MEM_FATArea[i] = i+1;						/** 有効FATエリアに1～有効FAT_AREAを順番に入れる */
			MEM_TotalAvailableStoreBlkCnt++;			/** 蓄積可能ブロック数をインクリメント */
		}
	}
#endif

	/*--------------------------------------------------------------------
	** 拡張メモリの仕様に合わせて変更する必要あり
	** 拡張メモリは１０ＭがＭＡＸなのでマシンパラメータのＡ７，Ａ８
	** の１ビット＝５１２Ｋを１Ｍに変更する必要あり
	** By M.Tachibana 1997/02/25
	*/

	/* dram_ok_bit |= 0x0003;		 POPLAR_B 標準２Ｍ Change By M.Kotani */
	dram_ok_bit = 1;				/* 1メガごとのすべてエリアののOKビット */
	ok_bit = 0x0002;				/* 拡張メモリ用 */
	for (j = 1; j < MEM_STANDARD_SIZE; j++) {
		dram_ok_bit <<= 1;
		dram_ok_bit++;
		ok_bit <<= 1;
	}
	start_block_no = MEM_FAT_AREA_STANDARD;
	j = start_block_no;

	/** メモリサイズ自動判別 */
/*	ok_bit = 0x0004; */
	check_size = (UDWORD)((UDWORD)MEM_SIZECHECK_BLOCK * (UDWORD)MEM_BLOCK_SIZE);	/* 1MByte毎にサイズチェックできます */

	for (address = MEM_SIZECHECK_START_ADDRESS; address < MEM_SIZECHECK_END_ADDRESS; address += check_size) {
		mem_index = (struct IndexTableData_t *)address;

		/** データ ライト ・・・ ライトデータはてきとーです */
		mem_index->Item = 0x01;
		mem_index->No = 0x2345;
		mem_index->BoxNumber = 0x01;
		mem_index->Page = 0x6789;
		mem_index->Code = 0xAB;
		mem_index->Mode = 0xCD;
		mem_index->Size = 0xEF;
		mem_index->LineCount = 0x5A96;
		mem_index->StartBlockNo = 0x965A;

		/** データ リード */
		if ((mem_index->Item == 0x01) &&
			(mem_index->No == 0x2345) &&
			(mem_index->BoxNumber == 0x01)&&
			(mem_index->Page == 0x6789) &&
			(mem_index->Code == 0xAB) &&
			(mem_index->Mode == 0xCD) &&
			(mem_index->Size == 0xEF) &&
			(mem_index->LineCount == 0x5A96) &&
			(mem_index->StartBlockNo == 0x965A)) {
			dram_ex_ok = 1;
			dram_ok_bit |= ok_bit;
		}
		ok_bit *= 2;

		if (dram_ex_ok == 1) {
			MEM_FATArea[i] = start_block_no;
			for ( ; j < ((UWORD)MEM_SIZECHECK_BLOCK + start_block_no); j++) {
				MEM_FATArea[j] = j+1;
				MEM_TotalAvailableStoreBlkCnt++;
				i = j;
			}
			dram_ex_ok = 0;
		} else {
			for ( ; j < ((UWORD)MEM_SIZECHECK_BLOCK + start_block_no); j++) {
				MEM_FATArea[j] = MEM_BAD_BLOCK;
			}
		}
		if (j >= MEM_FAT_AREA_MAX) {
			break;
		}
		start_block_no += MEM_SIZECHECK_BLOCK;
	}
	SYB_MachineParameter[MACHINE_PARA_7] = (UBYTE)dram_ok_bit;
	SYB_MachineParameter[MACHINE_PARA_8] = (UBYTE)(dram_ok_bit >> 8);

	MEM_FATArea[i] = MEM_EOB_BLOCK;					/** 最終ブロックはEOB */
	MEM_AvailableMaxFATArea = i+1;					/** 有効FATエリアの最終ブロックNo */
	MEM_EndBlock = i+1;								/** 空ブロックの最終を示すグローバル変数 */

	/* 割込み禁止のまま */
	/* CMN_EnableInterrupt();	@** 割込禁止期間終了 */

	return;
}

#endif

#pragma section
