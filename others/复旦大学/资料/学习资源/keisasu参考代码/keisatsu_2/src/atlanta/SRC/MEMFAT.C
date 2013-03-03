/************************************************************************
*				By : NOBUKO
*			  Date : Sat 08 Jan. 1994 (\SRC\RICE\SRC\MEMFAT.C)
*		 Copy Date : Tue 12 Sep. 1995
*		           : 1996/10/21 From \src\kobe\anzu\src\ By M.Kotani
*		 File Name : MEMFAT.C
*	   Module Name :
*			1. void	ClearAllFATArea(void)
*			2. void	ClearFATArea(UWORD StartBlock)
*			3. void InitFATAreaSetPageReg(UWORD pgr_no, UWORD data)
*			4. void CleaningFATArea(void)
*			5. void MEM_ClearAllFATAreaInTimer(void)
*			  履歴: S.Kawasaki 1996/05/20 標準１Ｍ仕様の対応
*										  MEMFAT.520へバックアップ
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\param.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\uni_pro.h"

#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\mem_data.h"
#if (PRO_CPU_VERSION == SH7043_A)
	#include "\src\cpu\sh7043_a\scd\ext_v\cph_data.h"
#else
	#include "\src\atlanta\scd\ext_v\cph_data.h"/*	By Y.Suzuki 1997/09/04	*/
#endif

#include "\src\atlanta\define\cmn_pro.h" /* By S.Kawasaki 1996/03/08 */
#include "\src\atlanta\define\unisw_h.h" /* By S.Kawasaki 1996/06/10 */

#include "\src\atlanta\define\mntsw_c.h" /* added by H.Kubo 1998/09/25 */
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 中国郵政局特ROM By O.Kimoto 2001/01/22 */
																		/* Add by Y.Kano 2003/07/11 */
#include	"\src\atlanta\ext_v\ini_tbl.h"
#endif

#define NO			0
#define YES			1


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
	comment		:[桐で動作確認済み	Oct.12,95]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/01/08]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*
** 増設されたＤＲＡＭの基盤枚数を数える
*/
static	UBYTE number_of_dram = 0;	/* By S.Kawasaki 1996/06/10 */

void ClearAllFATArea (void)
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
#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/14 */
	UBYTE	k;
#endif

	i = 0;
	j = 0;
	dram_ok_bit = 0;
	ok_bit = 0;
	start_block_no = 0;
	check_size = 0;
	dram_ex_ok = 0;

	CMN_DisableInterrupt();			/** 割込禁止期間開始 */
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
 #if defined(POPLAR_F)
		for (i = 0; i < (MEM_FAT_AREA_STANDARD - 1); i++) {	/** FATエリアを初期化する */
			MEM_FATArea[i] = i+1;						/** 有効FATエリアに1～有効FAT_AREAを順番に入れる */
			MEM_TotalAvailableStoreBlkCnt++;			/** 蓄積可能ブロック数をインクリメント */
		}
 #else
  #if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/14 */
		if (CHK_UNI_MultiT30Monitor()) {
			MEM_TopEmptyBlock = sizeof(struct SYS_T30MonitorData_t) * SYS_JOURNAL_MAX / MEM_BLOCK_SIZE + 1;	/* 空ブロックの先頭を示すグローバル変数の初期化 */
			for (i = 0; i < MEM_TopEmptyBlock; i++) {	/** FATエリアを初期化する */
				MEM_FATArea[i] = MEM_BAD_BLOCK;						/** アリロで使用する領域を無効領域とする */
			}
			for ( ; i < (MEM_FAT_AREA_STANDARD - 1); i++) {	/** FATエリアを初期化する */
				MEM_FATArea[i] = i+1;						/** 有効FATエリアに1～有効FAT_AREAを順番に入れる */
				MEM_TotalAvailableStoreBlkCnt++;			/** 蓄積可能ブロック数をインクリメント */
			}
			for (k = 0; k < SYS_JOURNAL_MAX; k++) {
				(SYS_T30Monitor + k)->JournalType = SYS_T30_EMPTY;
			}
		}
		else {
			for (i = 0; i < (MEM_FAT_AREA_STANDARD - 1); i++) {	/** FATエリアを初期化する */
				MEM_FATArea[i] = i+1;						/** 有効FATエリアに1～有効FAT_AREAを順番に入れる */
				MEM_TotalAvailableStoreBlkCnt++;			/** 蓄積可能ブロック数をインクリメント */
			}
		}
  #else
		for (i = 0; i < (MEM_FAT_AREA_STANDARD - 1); i++) {	/** FATエリアを初期化する */
			MEM_FATArea[i] = i+1;						/** 有効FATエリアに1～有効FAT_AREAを順番に入れる */
			MEM_TotalAvailableStoreBlkCnt++;			/** 蓄積可能ブロック数をインクリメント */
		}
  #endif
 #endif
	}
#else
	if(ScrambleOn == 1) {
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


#if (0)
** 	/*
** 	** 増設されたＤＲＡＭの個数を数え、フル充電時のバックアップ可能時間
** 	** を設定する。S.Kawasaki 1996/06/10
** 	*/
** 	number_of_dram = 0;
** 	if (SYB_MachineParameter[MACHINE_PARA_7] & 0xF0) {
** 		++number_of_dram;
** 	}
** 	if (SYB_MachineParameter[MACHINE_PARA_8] & 0x0F) {
** 		++number_of_dram;
** 	}
** 	if (SYB_MachineParameter[MACHINE_PARA_8] & 0xF0) {
** 		++number_of_dram;
** 	}
** 	switch (number_of_dram) {
** 	case 0: /** 標準ＤＲＡＭのみ */
** 		SYB_MachineUniqSwitch[UNIQ_SW_H2] = 108;
** 		break;
** 	case 1: /** 増設ＤＲＡＭ１個 */
** 		SYB_MachineUniqSwitch[UNIQ_SW_H2] = 54;
** 		break;
** 	case 2: /** 増設ＤＲＡＭ２個 */
** 		SYB_MachineUniqSwitch[UNIQ_SW_H2] = 36;
** 		break;
** 	case 3: /** 増設ＤＲＡＭ３個 */
** 		SYB_MachineUniqSwitch[UNIQ_SW_H2] = 27;
** 		break;
** 	default:/** 増設ＤＲＡＭ？個 */
** 		SYB_MachineUniqSwitch[UNIQ_SW_H2] = 27;
** 		break;
** 	}
#endif


	MEM_FATArea[i] = MEM_EOB_BLOCK;					/** 最終ブロックはEOB */
	MEM_AvailableMaxFATArea = i+1;					/** 有効FATエリアの最終ブロックNo */
	MEM_EndBlock = i+1;								/** 空ブロックの最終を示すグローバル変数 */
	CMN_EnableInterrupt();			/** 割込禁止期間終了 */

	return;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定FATエリアの消去]
	function	:[
		MEM_TopEmptyBlockの更新を行ないます
		指定されたブロックを先頭としてチェーン化されているFATエリアを解放します
		FATの空エリアと解放したエリアとをチェーン化します

		MEM_TopEmptyBlock					更新します
		MEM_TotalStoreBlockCounter			更新します
	]
	return		:[なし]
	common		:[
		UWORD  MEM_FATArea[],
		UWORD  MEM_TopEmptyBlock,
		UWORD  MEM_TotalStoreBlockCounter
	]
	condition	:[なし]
	comment		:[
		蓄積の終了している原稿と、蓄積中の原稿の両方の消去に使用します
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/01/08]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void ClearFATArea (UWORD StartBlock)					/* 消去指定FATエリアの先頭のBlockNo */
{
	UWORD  block_no;
	UWORD  block;
	UWORD  storing_block_count;
	UBYTE end_status;
#if 1 /* added by H.Kubo 1998/09/25 */
	UWORD  block_count;
#endif

	end_status = 0;

	block_no = StartBlock;
	storing_block_count = ChainBlockCounter(StartBlock);			/* 消去するブロック数 */

	/* 消去中に電源OFF対策です  消去成立後にもう一度callされたらFATは操作しません */
	if (MEM_BlockCounterEndStatus == MEM_EOB_BLOCK) {	/*チェーンのブロックの最終の状態を示す*/
		return;
	}

	if ((MEM_FATArea[block_no] & MEM_STORING_BLOCK) == MEM_STORING_BLOCK) {	/*最初のFATが蓄積中状態だったら終了とする*/
		MEM_FATArea[block_no] = MEM_FATArea[block_no] & ~MEM_STORING_BLOCK;
		end_status = 1;
	}
	block = MEM_FATArea[block_no] & ~MEM_STORING_BLOCK;	/*次のFATの番号をセットする*/

#if 0 /* FAT チェーンのループができたとき、無限ループに陥るのを防ぎます。Changed by H.Kubo 1998/09/25 */
@	for ( ; ; ) {
#else
	for (block_count = 1; block_count <= storing_block_count; block_count++) {
#endif
		if ((block == MEM_EOP_BLOCK) ||
			(end_status == 1) ||
			(block == MEM_EOB_BLOCK)) {
			break;
		}
		block_no = block;	/*次のFATの番号を現在の番号とする*/
		if ((MEM_FATArea[block_no] & MEM_STORING_BLOCK) == MEM_STORING_BLOCK) {	/*現在のFATが蓄積中状態だったら終了とする*/
			MEM_FATArea[block_no] = MEM_FATArea[block_no] & ~MEM_STORING_BLOCK;
			end_status = 1;
		}
		block = MEM_FATArea[block_no] & ~MEM_STORING_BLOCK;	/*次のFATの番号をセットする*/
	}

#if 1 /* FAT に無限ループがあったので、DRAM をクリアします。 added by H.Kubo 1998/09/25 */
	if (block_count > storing_block_count) {
		NackBuzzerSound();
		outp((UDWORD)0,(UBYTE)0);/* WriteProtectError for ICE */
		NackBuzzerSound();
		NackBuzzerSound();
		NackBuzzerSound();
		SYB_MaintenanceSwitch[MNT_SW_C1] |= MEM_FAT_LOOP_DETECTED;
		InitializeDRAM_Parameter();
		SaveReturnAddressAndJumpBegin();	/**リセットする*/
	}
#endif

	/** 割込み禁止期間開始 */
	CMN_DisableInterrupt();

	if ((MEM_TopEmptyBlock == MEM_EOB_BLOCK) ||	(MEM_TotalStoreBlockCounter == MEM_TotalAvailableStoreBlkCnt)) {/* 空ブロックなし */
		MEM_FATArea[block_no] = MEM_EOB_BLOCK;	/*最後のブロックの状態*/
	}
	else {
		if (MEM_FATArea[MEM_FATArea[block_no]] == MEM_RESERVED_BLOCK) {	/*次の次のFATの状態が予約*/
			MEM_FATArea[MEM_FATArea[block_no]] = MEM_TopEmptyBlock;
		}
		else {
			MEM_FATArea[block_no] = MEM_TopEmptyBlock;	/*消したい原稿の最後のブロックの次のブロックを現在の先頭蓄積開始ブロックとする*/
		}
	}
	MEM_TopEmptyBlock = StartBlock;	/*蓄積開始ブロックを消去する原稿の先頭とする*/
	MEM_TotalStoreBlockCounter -= storing_block_count;				/* 現在（消去前）の総使用ブロック数から消去したブロック数を引きます */

	/* 原因不明のBUG対策 */
	/* すべての原稿を消去しているのに､ﾒﾓﾘ残量が100%にならないことがある */
	/* MEM_TotalStoreBlockCounter == 1, -1のことがある */
#if (PRO_CPU == SH7043) /* S.Kawasaki 1996/03/07 */
	/*#if (0) * By S.Kawasaki 1996/08/23 復活 By Y.Suzuki 1998/04/15 */

	if (MEM_TotalStoreBlockCounter != 0) {	/* Nov.02,94 */
		if (MEM_CheckUseIndex() == (UBYTE)MEM_NO_INDEX)
			MEM_TotalStoreBlockCounter = 0;
	}

	/*#endif * By S.Kawasaki 1996/08/23 */
#endif
	CMN_EnableInterrupt();
	/** 割込み禁止期間終了 */

	return;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定されたV53ﾍﾟｰｼﾞﾚｼﾞｽﾀを指定されたﾃﾞｰﾀで設定する]
	function	:[
		拡張ｱﾄﾞﾚｽﾓｰﾄﾞの時は､拡張ｱﾄﾞﾚｽﾓｰﾄﾞを解除する
		拡張ｱﾄﾞﾚｽﾓｰﾄﾞになっていないときは､拡張ｱﾄﾞﾚｽﾓｰﾄﾞになるまで wai_tsk(1)する
		指定されたﾍﾟｰｼﾞﾚｼﾞｽﾀを指定されたｱﾄﾞﾚｽﾃﾞｰﾀに書き換える
		拡張ｱﾄﾞﾚｽモードに設定する
		ﾍﾟｰｼﾞﾚｼﾞｽﾀ書換期間は割込禁止とする
	]
	return		:[なし]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/01/08]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void InitFATAreaSetPageReg(UWORD pgr_no, UWORD data)
{
#if (PRO_CPU == SH7043)
#else
	for ( ; ; ) {
		if ((inp(XAM) & 0x01) == 0x01) {	/** 拡張アドレスモードになっている事の確認 */
			/** 割込み禁止期間開始 */
			CMN_DisableInterrupt();
			ReturnXA();					/** 拡張アドレスモード解除 */
			outpw(pgr_no, data);		/** ページレジスタの書き換え */
			BreakXA();					/** 拡張アドレスモード設定 */
			CMN_EnableInterrupt();
			/** 割込み禁止期間終了 */
			break;
		} else {
			wai_tsk(1);
		}
	}
#endif
	return;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[FATエリアの初期化(お掃除)]
	function	:[
		"ClearFATArea()"の最後で､蓄積原稿が1枚もなくなったときに､CALLされます
		FATエリアの初期化を行ないます
		有効FATエリアをチェーン化します

		MEM_TopEmptyBlock					初期化します
		MEM_TotalStoreBlockCounter			初期化します
		MEM_TotalAvailableStoreBlkCnt		有効ブロック数が代入されます
		MEM_AvailableMaxFATArea				有効ブロック数が代入されます
		MEM_EndBlock						有効ブロック数が代入されます
	]
	return		:[なし]
	common		:[
		UWORD  MEM_FATArea[]
		UWORD  MEM_TopEmptyBlock
		UWORD  MEM_TotalStoreBlockCounter
		UWORD  MEM_TotalAvailableStoreBlkCnt
		UWORD  MEM_AvailableMaxFATArea
		UWORD  MEM_EndBlock
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/12/14]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** FATのおそうじ関数 */
/** H8(ｻﾂｷ､ﾗﾍﾞﾝﾀﾞ)のみ使用 */
/** 蓄積原稿がないのに､MEM_TotalStoreBlockCounterが0でなかったらCALLされます */
void CleaningFATArea(void)
{
#if (PRO_CPU == SH7043)
	UWORD i;

	MEM_TotalAvailableStoreBlkCnt = 0;
	MEM_TopEmptyBlock = 0;							/* 空ブロックの先頭を示すグローバル変数の初期化 */
	MEM_TotalStoreBlockCounter = 0;					/* 使用ブロック数のトータルを示すグローバル変数の初期化 */

	for (i = 0; i+1 < MEM_FAT_AREA_STANDARD; i++) {	/** FATエリアを初期化する */
		MEM_TotalAvailableStoreBlkCnt++;			/** 蓄積可能ブロック数をインクリメント */
		MEM_FATArea[i] = i+1;						/** 有効FATエリアに1～有効FAT_AREAを順番に入れる */
	}
	MEM_TotalAvailableStoreBlkCnt++;				/** 蓄積可能ブロック数をインクリメント */
	MEM_FATArea[i] = MEM_EOB_BLOCK;					/** 最終ブロックはEOB */
	MEM_AvailableMaxFATArea = i+1;					/** 有効FATエリアの最終ブロックNo */
	MEM_EndBlock = i+1;								/** 空ブロックの最終を示すグローバル変数 */
#endif
	return;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[FATエリアの初期化]
	function	:[
		"MAN_TimerTask()"(1秒ﾀｲﾏ)の中で､通信中､ﾌﾟﾘﾝﾄ中､ｽｷｬﾝ中
		でなくて､蓄積原稿が1枚もないときに､CALLされます
		もちろん､処理中は割込禁止です

		FATエリアの初期化を行ないます
		有効FATエリアをチェーン化します

		MEM_TopEmptyBlock					初期化します
		MEM_TotalStoreBlockCounter			初期化します
		MEM_TotalAvailableStoreBlkCnt		有効ブロック数が代入されます
		MEM_AvailableMaxFATArea				有効ブロック数が代入されます
		MEM_EndBlock						有効ブロック数が代入されます
	]
	return		:[なし]
	common		:[
		UWORD  MEM_FATArea[]
		UWORD  MEM_TopEmptyBlock
		UWORD  MEM_TotalStoreBlockCounter
		UWORD  MEM_TotalAvailableStoreBlkCnt
		UWORD  MEM_AvailableMaxFATArea
		UWORD  MEM_EndBlock
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/12/14]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void MEM_ClearAllFATAreaInTimer (void)
{
#if (PRO_CPU == SH7043)
	UWORD  i;
	UWORD  j;
	UWORD  dram_ok_bit;
	UWORD  ok_bit;
	UWORD  start_block_no;

	CMN_DisableInterrupt();
	MEM_TotalAvailableStoreBlkCnt = 0;
	MEM_TopEmptyBlock = 0;											/* 空ブロックの先頭を示すグローバル変数の初期化 */
	MEM_TotalStoreBlockCounter = 0;									/* 使用ブロック数のトータルを示すグローバル変数の初期化 */
	MEM_BlockCounterEndStatus = MEM_EOP_BLOCK;						/* とりあえずEOPに初期化 *//*チェーンのブロックの最終の状態を示す*/

	/** 電源立ち上げ時にｾｯﾄしたSYB_MachineParameter:A:7,8を元にDRAM(FAT)の初期化を行います */
	dram_ok_bit = (UWORD)(SYB_MachineParameter[MACHINE_PARA_7] + ((UWORD)SYB_MachineParameter[MACHINE_PARA_8] * 256));

	/** 標準エリアの初期化 */
#if (0)	/*	By Y.Suzuki 1997/09/11	*/
**	for (i = 0; i < (MEM_FAT_AREA_STANDARD - 1); i++) {	/** 先頭1M分のFAT_AREAの初期化 */
**		MEM_FATArea[i] = i+1;
**		MEM_TotalAvailableStoreBlkCnt++;
**	}
#endif
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
	if(ScrambleOn == 1) {
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

#if (0)	/* By M.Tachibana 1997/12/19 */
//	start_block_no = MEM_FAT_AREA_STANDARD;
//	ok_bit = 0x0002;
//	j = start_block_no;
#endif

	ok_bit = 0x0002;				/* 拡張メモリ用 */
	for (j = 1; j < MEM_STANDARD_SIZE; j++) {
		ok_bit <<= 1;
	}
	start_block_no = MEM_FAT_AREA_STANDARD;
	j = start_block_no;

	for ( /*ok_bit = 0x0002*/ ; ok_bit <= 0x8000; ok_bit *= 2) {
		if ((dram_ok_bit & ok_bit) == ok_bit) {
			MEM_FATArea[i] = start_block_no;
			for ( ; j < ((UWORD)MEM_SIZECHECK_BLOCK + start_block_no); j++) {
				MEM_FATArea[j] = j+1;
				MEM_TotalAvailableStoreBlkCnt++;
				i = j;
			}
		} else {
			for ( ; j < ((UWORD)MEM_SIZECHECK_BLOCK + start_block_no); j++) {
				MEM_FATArea[j] = MEM_BAD_BLOCK;
			}
		}
		if (j >= MEM_FAT_AREA_MAX) {
			break;
		}
		start_block_no += MEM_SIZECHECK_BLOCK;
		dram_ok_bit &= ~ok_bit;
		if (dram_ok_bit == 0) {
			break;
		}
	}
	MEM_FATArea[i] = MEM_EOB_BLOCK;					/** 最終ブロックはEOB */
	MEM_AvailableMaxFATArea = i+1;					/** 有効FATエリアの最終ブロックNo */
	MEM_EndBlock = i+1;								/** 空ブロックの最終を示すグローバル変数 */

	CMN_EnableInterrupt();
#endif
	return;
}
