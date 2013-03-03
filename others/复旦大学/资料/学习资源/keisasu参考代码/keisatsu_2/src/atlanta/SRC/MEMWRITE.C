/************************************************************************
*				By : NOBUKO
*			  Date : Wed 05 Jan. 1994 (\SRC\RIVE\SRC\MEMWRITE.C)
*		 Copy Date : Tue 12 Sep. 1995
*				   : 1996/10/21 From \src\kobe\anzu\src\ By M.Kotani
*		 File Name : MEMWRITE.C
*	   Module Name :
*			1. UWORD MEM_WriteOpen(struct MEM_IndexData_t *IndexP, struct MEM_ExecData_t *ExecP)
*			2. UWORD MEM_MultiWriteOpen(struct MEM_StoreData_t *, struct MEM_ExecData_t *)
*			3. UWORD MEM_Write(UBYTE Item, struct MEM_ExecData_t *ExecP)
*			4. void MEM_MultiWriteClose(struct MEM_ExecData_t *, UWORD)
*			5. void MEM_WriteClose(struct MEM_ExecData_t *ExecP)
*			6. UWORD MEM_WriteGetNextBlockNo(UWORD BlockNo)
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\sh7043\define\def_semn.h"	/* 1997/12/16 Y.M */
#include "\src\atlanta\sh7043\ext_v\extv_sem.h"	/* 1997/12/16 Y.M */
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\sys_stat.h"			/* SYS_MachineStatus[] */
#include "\src\atlanta\ext_v\mem_data.h"
#include "\src\atlanta\ext_v\sys_data.h"			/* SYS_MachineStatus[] */
#include "\src\atlanta\ext_v\BKUPRAM.H"			/* SYS_MemorySwitch[] Feb.6,1995 By S.K	 */
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\mntsw_a.h" /* 1996/09/09 Eguchi */
#include "\src\atlanta\define\mntsw_c.h" /* 1998/01/30 Kubo */
#include "\src\atlanta\define\unisw_h.h" /* 1997/12/12 M.Kotani */
#include "\src\atlanta\sh7043\define\def_evtn.h" /* By S.Kawasaki 1996/03/08 */

#include "\src\atlanta\ext_v\dma_data.h" /* added by H.Kubo 1998/02/12 */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
#include "\src\atlanta\ext_v\sys_inf.h"
#endif

#if 0 /* defined (SAKAKI) */ /* added by H.Kubo 1998/08/07 */
UDWORD	DMA_ComCodecToDram_Debug = 0;
#endif


static UWORD store_buffer_point = 0;
static UBYTE MEM_WriteDebugSwitch = 0;
static UDWORD DEBUG_DMA_BaseAddress = 0;
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[メモリ・ライト・オープン]
	function	:[
		1.
	]
	return		:[
		#define MEM_INDEX_OVER	空インデックスなし
		#define MEM_BLOCK_OVER	蓄積可能ブロックがなし
		#define MEM_OK			インデックス、ブロック共 確保OK
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[],
		UWORD  MEM_FATArea[],
		UWORD  MEM_TotalAvailableStoreBlkCnt,
		UWORD  MEM_TopEmptyBlock,
		UWORD  MEM_TotalStoreBlockCounter
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/01/05]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UWORD MEM_WriteOpenFlsRom (struct MEM_StoreData_t *StoreP,						/* 原稿の蓄積情報を指定します */
					 	   struct MEM_ExecData_t	*ExecP)						/* 蓄積中のデータを格納するエリアを指定します */
#else
UWORD MEM_WriteOpen (struct MEM_StoreData_t *StoreP,						/* 原稿の蓄積情報を指定します */
					 struct MEM_ExecData_t	*ExecP)						/* 蓄積中のデータを格納するエリアを指定します */
#endif
{
	UWORD index_no;
	UBYTE auto_init_flag;	/* スキャナー位相ずれデバッグ */

	/*CMN_DisableInterrupt(); WRITE_OPEN_SEM 1997/12/16 Y.Murata */		/* By Y.Suzuki 1997/05/07 */
	wai_sem(semno.MEM_WriteOpenSem);

#if 0 /* defined (SAKAKI) /* added by H.Kubo 1998/08/07 */
	DMA_ComCodecToDram_Debug = 0;
#endif

#if (PRO_EXT_DMAC == ENABLE)
	auto_init_flag = 0; /* 1996/09/09 Eguchi */

/*	if ((SYB_MaintenanceSwitch[MNT_SW_C1] & 0x40)	bit変更	By M.Tachibana 1998/05/19 */
	if ((SYB_MaintenanceSwitch[MNT_SW_C1] & 0x01)
	 && (MEM_ScanFlag)) {
		if ((StoreP -> Item == SYS_MEM_TX_FILE)
		 || (StoreP -> Item == SYS_MEM_MULTI_COPY_FILE)
		 || (StoreP -> Item == SYS_MEM_MANUAL_COPY_FILE)
		 || (StoreP -> Item == SYS_MEM_POLLING_FILE)
		 || (StoreP -> Item == SYS_MEM_DB_POLLING_FILE)
		 || (StoreP -> Item == SYS_MEM_FIP_FILE)
		 || (StoreP -> Item == SYS_MEM_BATCH_TX_FILE1)
		 || (StoreP -> Item == SYS_MEM_BATCH_TX_FILE2)
		 || (StoreP -> Item == SYS_MEM_BATCH_TX_FILE3)
		 || (StoreP -> Item == SYS_MEM_BATCH_TX_FILE4)
#if (PRO_CLASS1 == ENABLE)
		 || (StoreP -> Item == SYS_MEM_CLASS1_TX_FILE)
#endif
#if (0)	/*　by Y.Tanimoto　1998/03/12　*/
/*	なぜ、昔のINTERNET FAXのﾊﾟｽが移植されてるのでしょうか？
**	ANZUからATLANTAへの移植ミス？？
**	PRO_INTERNET_FAXで切り分けられてANZUに入っているソースおよび
**	この条件コンパイル自体、移植しては駄目です。
*/
 #if (PRO_INTERNET_FAX == ENABLE) /* 1997/04/03 Eguchi */
		 || (StoreP -> Item == SYS_MEM_MAIL_TX_FILE)
		 || (StoreP -> Item == SYS_MEM_MAIL_RX_FILE)
 #endif
#endif
		 || (StoreP -> Item == SYS_MEM_BATCH_TX_FILE5)) {
			auto_init_flag = 1;
		}
		else {
			auto_init_flag = 0;
		}
	}
	MEM_ScanFlag = 0;
#endif /* PRO_EXT_DMAC end */

	MEM_WriteDebugSwitch = 0;

	/** 蓄積中に使用するデータの初期化 */
	ExecP -> IndexNo1 = MEM_NO_INDEX;
	ExecP -> IndexNo2 = MEM_NO_INDEX;
	ExecP -> ExecBlockNo = MEM_NO_INDEX;
	ExecP -> NextBlockNo = MEM_NO_INDEX;

	if (MEM_TopEmptyBlock == MEM_EOB_BLOCK) {	/** 空ブロックの先頭がEOB */
		/** 空ブロックなし終了 */
		/*CMN_EnableInterrupt(); WRITE_OPEN_SEM 1997/12/16 Y.Murata */	/* By Y.Suzuki 1997/05/07 */
		sig_sem(semno.MEM_WriteOpenSem);
		return (MEM_BLOCK_OVER);
	}

	/*-----------------------------------------------
	 * ブロックに空きがあるかどうか
	 * EOBブロックには蓄積しません
	 * NAGANOから移植 V851 By Y.Suzuki 2002/07/27
	*/
/*#if defined(POPLAR_H) && defined(JP0)*/
	if (auto_init_flag) {
		if (MEM_CheckTopEmptyBlock(MEM_TopEmptyBlock, 3) == 0) {
			sig_sem(semno.MEM_WriteOpenSem);
			return (MEM_BLOCK_OVER);
		}
	}
	else {
		if (MEM_CheckTopEmptyBlock(MEM_TopEmptyBlock, 2) == 0) {
			sig_sem(semno.MEM_WriteOpenSem);
			return (MEM_BLOCK_OVER);
		}
	}
/*#endif*/


	/** 蓄積可能ブロックの残量をチェック */
	if (StoreP -> Item == SYS_MEM_RX_FILE) {	/** 蓄積原稿が受信原稿 */
		if ((MEM_CountTotalEmptyBlock() + MEM_RX_BORDERLINE) <= 0) {	/** 使用可能ブロック数 + 裏メモリ(受信のみ使用可)のサイズが０ブロック以下 */
			/** 空ブロックなし終了 */
			/*CMN_EnableInterrupt(); WRITE_OPEN_SEM 1997/12/16 Y.Murata */	/* By Y.Suzuki 1997/05/07 */
			sig_sem(semno.MEM_WriteOpenSem);
			return (MEM_BLOCK_OVER);
		}
	} else {
		if (MEM_CountTotalEmptyBlock() <= 0) {							/** 使用可能ブロック数が０ブロック以下 */
			/** 空ブロックなし終了 */
			/*CMN_EnableInterrupt(); WRITE_OPEN_SEM 1997/12/16 Y.Murata */	/* By Y.Suzuki 1997/05/07 */
			sig_sem(semno.MEM_WriteOpenSem);
			return (MEM_BLOCK_OVER);
		}
	}

	/** 使用インデックスの確保 */
	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {	/** インデックス・テーブル内の検索 */
		if (MEM_IndexTable[index_no].Item == SYS_MEM_FILE_EMPTY) {	/** 空インデックス */
			/** インデックスNo.1を確保 */
			ExecP -> IndexNo1 = index_no;
			/** 検索終了 */
			break;
		}
	}
	if (ExecP -> IndexNo1 == MEM_NO_INDEX) {	/** 空インデックスなし */
		/** 空インデックスなし終了 */
		/*CMN_EnableInterrupt(); WRITE_OPEN_SEM 1997/12/16 Y.Murata */	/* By Y.Suzuki 1997/05/07 */
		sig_sem(semno.MEM_WriteOpenSem);
		return (MEM_INDEX_OVER);
	}

	/** 使用が確定したインデックスにデータを書き込む */
	MEM_IndexTable[ExecP -> IndexNo1].Item = (UBYTE)(StoreP -> Item | MEM_NOW_STORING);
	MEM_IndexTable[ExecP -> IndexNo1].No = StoreP -> No;
	MEM_IndexTable[ExecP -> IndexNo1].Page = StoreP -> Page;
/* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/29  By T.Yamaguchi */
	MEM_IndexTable[ExecP -> IndexNo1].BoxNumber = StoreP -> BoxNumber;
/* #endif */
	MEM_IndexTable[ExecP -> IndexNo1].Code = StoreP -> Code;
	MEM_IndexTable[ExecP -> IndexNo1].Mode = StoreP -> Mode;
	MEM_IndexTable[ExecP -> IndexNo1].Size = StoreP -> Size;
#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/09/04 */
	/*---------------------------------------------------------------------
	** ＰＣプリント以外では、Area、Cassetteにゴミがセットされていたのを修正した。
	** By M.Tachibana 1997/12/06
	*/
	if (StoreP -> Item == SYS_MEM_PC_RX_FILE) {
		MEM_IndexTable[ExecP -> IndexNo1].Area = StoreP -> Area;
		MEM_IndexTable[ExecP -> IndexNo1].Cassette = StoreP -> Cassette;
	}
	else {
		MEM_IndexTable[ExecP -> IndexNo1].Area = 0xFF;
		MEM_IndexTable[ExecP -> IndexNo1].Cassette = 0xFF;
	}
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/*　by Y.Tanimoto 1998/03/12　*/
	/*　蓄積されたページのデータ量を記憶するために使用が確定したインデックスの
	**	配列オフセットを以下の変数に記憶させておきます
	*/
	if (StoreP -> Item == SYS_MEM_MAIL_TX_FILE) {
		SYS_INF_IndexTableNo = (UWORD)ExecP -> IndexNo1;
		SYS_INF_StoredMailDataCount[SYS_INF_IndexTableNo] = 0;	/* 初期化 */
	}
#endif
	CMN_DisableInterrupt(); /* WRITE_OPEN_SEM 1997/12/16 Y.Murata */
	MEM_IndexTable[ExecP -> IndexNo1].StartBlockNo = MEM_TopEmptyBlock;

	/** 割込み禁止期間開始 */
	/*CMN_DisableInterrupt();*/
	/** 蓄積中に使用するデータにブロック情報を書き込む(Execデータ、FAT) */
	/** 蓄積ブロックは空ブロックの先頭 */
	ExecP -> ExecBlockNo = MEM_TopEmptyBlock;
	/** 空ブロックの先頭の更新 */
	MEM_TopEmptyBlock = MEM_FATArea[ExecP -> ExecBlockNo];
	/** 蓄積中のブロックは蓄積中であることを指示 */
	MEM_FATArea[ExecP -> ExecBlockNo] |= MEM_STORING_BLOCK;

#if (PRO_EXT_DMAC == ENABLE)
	/* スキャナー位相ずれデバッグ 1998/02/05 */
	if (auto_init_flag) {
		/** 次ブロックの予約は空ブロックの先頭 */
		ExecP -> NextBlockNo = MEM_TopEmptyBlock;
		/** 空ブロックの先頭の更新 */
		MEM_TopEmptyBlock = MEM_FATArea[ExecP -> NextBlockNo];
		/** FAT上の予約次ブロックは予約ブロックあることを指示 */
		MEM_FATArea[ExecP -> NextBlockNo] = MEM_RESERVED_BLOCK;
	}
#endif

	/*CMN_EnableInterrupt();*/
	/** 割込み禁止期間終了 */

	store_buffer_point = ExecP -> ExecBlockNo;

	/** 正常終了 */
	CMN_EnableInterrupt(); 	/* By Y.Suzuki 1997/05/07 */
	sig_sem(semno.MEM_WriteOpenSem);

	return (MEM_OK);
}


#if (PRO_CPU == SH7043)
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[メモリ・マルチ・ライト・オープン]
	function	:[
		1. マルチプログラム送信時の原稿蓄積に使用
		2. 一つの原稿を複数枚のインデックスでオープンする
		3. 原稿は一つなのでFATはオープンする全インデックス共通です
	]
	return		:[
		#define MEM_INDEX_OVER	空インデックスなし
		#define MEM_BLOCK_OVER	蓄積可能ブロックがなし
		#define MEM_OK			インデックス、ブロック共 確保OK
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[MEM_INDEX_TABLE_MAX],
		UWORD  MEM_FATArea[],
		UWORD  MEM_TotalAvailableStoreBlkCnt,
		UWORD  MEM_TopEmptyBlock,
		UWORD  MEM_TotalStoreBlockCounter,
		UWORD  MEM_MultiProgramOpenIndexNo[SYS_JOB_MAX]
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/07/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_MultiWriteOpen (struct MEM_StoreData_t *StoreP,				/* 原稿の蓄積情報を指定します */
						  struct MEM_ExecData_t	 *ExecP)				/* 蓄積中のデータを格納するエリアを指定します */
{
	UWORD  i;
	UWORD  n;

	/** 割込み禁止期間開始 */
	/*CMN_DisableInterrupt(); WRITE_OPEN_SEM 1997/12/16 Y.Murata */	/* By Y.Suzuki 1997/05/07 */
	wai_sem(semno.MEM_WriteOpenSem);

	MEM_ScanFlag = 0;
	MEM_WriteDebugSwitch = 0;

	/** 蓄積中に使用するデータの初期化 */
	ExecP -> IndexNo1 = MEM_NO_INDEX;
	ExecP -> IndexNo2 = MEM_NO_INDEX;
	ExecP -> ExecBlockNo = MEM_NO_INDEX;
	ExecP -> NextBlockNo = MEM_NO_INDEX;

	if (MEM_TopEmptyBlock == MEM_EOB_BLOCK) {	/** 空ブロックの先頭がEOB */
		/** 空ブロックなし終了 */
		/*CMN_EnableInterrupt(); WRITE_OPEN_SEM 1997/12/16 Y.Murata */		/* By Y.Suzuki 1997/05/07 */
		sig_sem(semno.MEM_WriteOpenSem);
		return (MEM_BLOCK_OVER);
	}

	/** 蓄積可能ブロックの残量をチェック */
	if (MEM_CountTotalEmptyBlock() <= 0) {	/** 使用可能ブロック数が０ブロック以下 */
		/** 空ブロックなし終了 */
		/*CMN_EnableInterrupt(); WRITE_OPEN_SEM 1997/12/16 Y.Murata */		/* By Y.Suzuki 1997/05/07 */
		sig_sem(semno.MEM_WriteOpenSem);
		return (MEM_BLOCK_OVER);
	}

	for (i = 0, n = 0; i < MEM_INDEX_TABLE_MAX; i++) {
		if (MEM_IndexTable[i].Item == SYS_MEM_FILE_EMPTY) {
			MEM_IndexTable[i].Item = (UBYTE)(StoreP -> Item | MEM_NOW_STORING);
			MEM_IndexTable[i].No = SYS_MultiProgramNo[n];
			MEM_IndexTable[i].Page = StoreP -> Page;
/* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/29  By T.Yamaguchi */
			MEM_IndexTable[i].BoxNumber = StoreP -> BoxNumber;
/* #endif */
			MEM_IndexTable[i].Code = StoreP -> Code;
			MEM_IndexTable[i].Mode = StoreP -> Mode;
			MEM_IndexTable[i].Size = StoreP -> Size;
#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/09/04 */
			/*---------------------------------------------------------------------
			** ＰＣプリント以外では、Area、Cassetteにゴミがセットされていたのを修正した。
			** By M.Tachibana 1997/12/06
			*/
			if (StoreP -> Item == SYS_MEM_PC_RX_FILE) {
				MEM_IndexTable[ExecP -> IndexNo1].Area = StoreP -> Area;
				MEM_IndexTable[ExecP -> IndexNo1].Cassette = StoreP -> Cassette;
			}
			else {
				MEM_IndexTable[ExecP -> IndexNo1].Area = 0xFF;
				MEM_IndexTable[ExecP -> IndexNo1].Cassette = 0xFF;
			}
#endif
			MEM_IndexTable[i].StartBlockNo = MEM_TopEmptyBlock;
			MEM_MultiProgramOpenIndexNo[n] = i;
			n++;
		}
		if ((SYS_MultiProgramNo[n] == 0xFF) || (n > SYS_JOB_MAX)) {
			break;
		}
	}
	if (i == MEM_INDEX_TABLE_MAX) {
		for (n = 0; n < SYS_JOB_MAX; n++) {
			if (MEM_MultiProgramOpenIndexNo[n] != 0xFF) {
				MEM_IndexTable[MEM_MultiProgramOpenIndexNo[n]].Item = SYS_MEM_FILE_EMPTY;
				MEM_MultiProgramOpenIndexNo[n] = MEM_NO_INDEX;
			}
			if (MEM_MultiProgramOpenIndexNo[n+1] == 0xFF) {
				break;
			}
		}
		/*CMN_EnableInterrupt(); WRITE_OPEN_SEM 1997/12/16 Y.Murata */		/* 1997/08/18 M.Kotani */
		sig_sem(semno.MEM_WriteOpenSem);
		return (MEM_INDEX_OVER);
	}

	/** 割込み禁止期間開始 */
	CMN_DisableInterrupt();	/* WRITE_OPEN_SEM 1997/12/16 Y.Murata */
	/** 蓄積中に使用するデータにブロック情報を書き込む(Execデータ、FAT) */
	/** 蓄積ブロックは空ブロックの先頭 */
	ExecP -> ExecBlockNo = MEM_TopEmptyBlock;
	/** 空ブロックの先頭の更新 */
	MEM_TopEmptyBlock = MEM_FATArea[ExecP -> ExecBlockNo];
	/** 蓄積中のブロックは蓄積中であることを指示 */
	MEM_FATArea[ExecP -> ExecBlockNo] |= MEM_STORING_BLOCK;

	store_buffer_point = ExecP -> ExecBlockNo;

	CMN_EnableInterrupt();	/* WRITE_OPEN_SEM 1997/12/16 Y.Murata */
	/** 割込み禁止期間終了 */
	sig_sem(semno.MEM_WriteOpenSem);

	/** 正常終了 */
	return (MEM_OK);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[原稿蓄積]
	function	:[
		1.
	]
	return		:[
		#define MEM_BLOCK_OVER		蓄積中に蓄積ブロックがなくなった
		#define MEM_STOP_SW			蓄積中にSTOP_SW押下
		#define MEM_OK				蓄積終了
	]
	common		:[
	]
	condition	:[]
	comment		:[
		DRAM書き込み時のDMAで､ 次ﾌﾞﾛｯｸの予約をしていないときは通常のV53 DMAを使用
		次ﾌﾞﾛｯｸの予約をしている時は､V53 DMA の ｵｰﾄｲﾆｼｬﾗｲｽﾞ機能を使用
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/01/05]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
CONST UBYTE MEM_Debug = 0;
#if (PRO_CPU == SH7043)
UBYTE MEM_DebugCount = 0;
#endif

UWORD MEM_Write (UBYTE Type,
				 struct MEM_ExecData_t *ExecP)
{
	UBYTE end_status;
	struct DMA_Data_t MEM_WriteDMA;

#if (PRO_MODEM == R288F) /* for debugging by H.Kubo 1998/01/30 */
	UWORD word_register_value;
#endif

	/* 位相ずれデバッグ */
	UBYTE Debug = 0;	/** 蓄積時のスルー・ダウンを強制的に実行させる為のスイッチ Sep.17,1994 */
	UBYTE DebugCount = 10;	/* For Test 1998/01/28 */

	UDWORD chk_wt_dma_address;	/* Add By O.Kimoto 1998/05/09 */

	chk_wt_dma_address = 0;	/*  By O.Kimoto 1998/05/09 */

/* スキャナー位相ずれデバッグ ＱＡＴの為の取り合えずの処置です。T.Nose 1998/02/05 */
#if (PRO_EXT_DMAC == ENABLE)
/*	if ((SYB_MaintenanceSwitch[MNT_SW_C1] & 0x40)	bit変更	By M.Tachibana 1998/05/19 */
	if ((SYB_MaintenanceSwitch[MNT_SW_C1] & 0x01)	/* オートイニシャライズを使用 */
	 && (ExecP -> NextBlockNo != MEM_NO_INDEX)) {
		if (Type == MEM_SCANNER) {				/** 呼び元がSCANNER */
			MEM_DMAEndStatus &= ~MEM_SCAN_PAGE_END;
			end_status = MEM_SCAN_PAGE_END;
			MEM_WriteDMA.Channel = DMA_SCNCDC_DRAM_CH;		/** DMA Channel指定 */
		} else {									/** 呼び元がMODEM */
			MEM_DMAEndStatus &= ~MEM_RX_PAGE_END;
			end_status = MEM_RX_PAGE_END;
			MEM_WriteDMA.Channel = DMA_COMCDC_DRAM_CH;		/** DMA Channel指定 */
		}

		/** DMA Initialize */

#if (0)
** 		/* MEM_CalculateDMAAddress()の戻り値はエラーの可能性がある。しかし、それを判断せずにＤＭＡアドレスを
** 		** セットしており、それは非常にまずい。
** 		** ということで上記関数の戻り値を判断しエラーの場合はメモリエラーで終わります。
** 		** By O.Kimoto 1998/05/09
** 		*/
** 		MEM_WriteDMA.SrcAddress = MEM_CalculateDMAAddress(ExecP -> ExecBlockNo);	/** DMA開始アドレス指定 */
#else
		chk_wt_dma_address = MEM_CalculateDMAAddress(ExecP -> ExecBlockNo);	/** DMA開始アドレス指定 */
		if (chk_wt_dma_address == (UDWORD)MEM_BLOCK_OVER) {
			DMA_RequestMask(MEM_WriteDMA.Channel);
			return (MEM_BLOCK_OVER);
		}
		MEM_WriteDMA.SrcAddress = chk_wt_dma_address;
#endif

		MEM_WriteDMA.Counter = (UWORD)(MEM_BLOCK_SIZE / 2);							/** 転送WORD数(N-1)指定 */
		MEM_WriteDMA.Unit = DMA_WORD_TRANSFER;										/** WORD転送指定 */
		MEM_WriteDMA.Direction = DMA_IO_TO_MEMORY;									/** 転送方向指定 */

		DMA_SetupDMAU(&MEM_WriteDMA);									/** DMAU Setup */
		DMA_AutoInitializeEnable(MEM_WriteDMA.Channel);					/** DMAU AutoInitializeMode Enable */
		DMA_RequestEnable(MEM_WriteDMA.Channel);						/** DMA Start (CODEC -> DRAM) */

		while ((MEM_DMAEndStatus & end_status) != end_status) {			/** MEM_DMAEndStatusが何も立っていない場合 */
			/** STOP SW の監視 蓄積を止める */
			if (Type == MEM_SCANNER) {
				if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & (SYS_STOP_DOC_STORE + SYS_STOP_MULTI_COPY)) {
					DMA_RequestMask(MEM_WriteDMA.Channel);
					DMA_AutoInitializeDisable(MEM_WriteDMA.Channel);	/** DMAU AutoInitializeMode Disable */
					return (MEM_STOP_SW);
				}
				/* 通信時のSTOP_SWの監視はMODEMの中でやっているのでここでは必要ありません */
			}

			/*********** この関数は外付け･内蔵共通の関数を作る ********/
			/** 蓄積ブロックのアドレス算出 */

#if (0)
** 			/* MEM_CalculateDMAAddress()の戻り値はエラーの可能性がある。しかし、それを判断せずにＤＭＡアドレスを
** 			** セットしており、それは非常にまずい。
** 			** ということで上記関数の戻り値を判断しエラーの場合はメモリエラーで終わります。
** 			** By O.Kimoto 1998/05/09
** 			*/
** 			DEBUG_DMA_BaseAddress = MEM_CalculateDMAAddress(ExecP -> NextBlockNo);
** 			DMA_SetDMA_BaseAddress(MEM_WriteDMA.Channel, DEBUG_DMA_BaseAddress);
#else
			DEBUG_DMA_BaseAddress = MEM_CalculateDMAAddress(ExecP -> NextBlockNo);
			if (DEBUG_DMA_BaseAddress == (UDWORD)MEM_BLOCK_OVER) {
				/** 空ブロックなし終了 */
				DMA_RequestMask(MEM_WriteDMA.Channel);
				DMA_AutoInitializeDisable(MEM_WriteDMA.Channel);	/** DMAU AutoInitializeMode Disable */
				return (MEM_BLOCK_OVER);
			}
			DMA_SetDMA_BaseAddress(MEM_WriteDMA.Channel, DEBUG_DMA_BaseAddress);
#endif

			/**********************************************************/

			/** 蓄積可能ブロックの残量をチェック */
			if (Type == MEM_SCANNER) {	/** 蓄積原稿が受信原稿以外 */
				if (MEM_TotalAvailableStoreBlkCnt - MEM_TotalStoreBlockCounter - MEM_RX_BORDERLINE <= 1) {	/** 使用可能ブロック数－使用ブロック数－
																											裏メモリ(受信のみ使用可)のサイズが１ブロック以下 */
					/** 空ブロックなし終了 */
					DMA_RequestMask(MEM_WriteDMA.Channel);
					DMA_AutoInitializeDisable(MEM_WriteDMA.Channel);	/** DMAU AutoInitializeMode Disable */
					return (MEM_BLOCK_OVER);
				}
			}

			/** DMATCのウエイト */
			if (Type == MEM_SCANNER)										/** 呼び元がSCANNER */
				wai_evt(EVT_DMA_SCNCDC_DRAM);
			else {
				wai_evt(EVT_DMA_COMCDC_DRAM);
			}

			/** 次の蓄積ブロックの獲得、更新 */
			if (MEM_WriteGetNextBlockNo(ExecP) == MEM_BLOCK_OVER) {
				DMA_RequestMask(MEM_WriteDMA.Channel);
				DMA_AutoInitializeDisable(MEM_WriteDMA.Channel);	/** DMAU AutoInitializeMode Disable */
				return (MEM_BLOCK_OVER);
			}

		}
		DMA_RequestMask(MEM_WriteDMA.Channel);
		DMA_AutoInitializeDisable(MEM_WriteDMA.Channel);				/** DMAU AutoInitializeMode Disable */
		return (MEM_OK);
	}
#endif /* (PRO_EXT_DMAC == ENABLE) */

	if (Type == MEM_SCANNER) {				/** 呼び元がSCANNER */
		MEM_DMAEndStatus &= ~MEM_SCAN_PAGE_END;
		end_status = MEM_SCAN_PAGE_END;
		MEM_WriteDMA.Channel = DMA_SCNCDC_DRAM_CH;		/** DMA Channel指定 */
	} else {								/** 呼び元がMODEM */
		MEM_DMAEndStatus &= ~MEM_RX_PAGE_END;
		end_status = MEM_RX_PAGE_END;
		MEM_WriteDMA.Channel = DMA_COMCDC_DRAM_CH;								/** DMA Channel指定 */
	}

	/** V53 DMA Initialize */

#if (0)
** 	/* MEM_CalculateDMAAddress()の戻り値はエラーの可能性がある。しかし、それを判断せずにＤＭＡアドレスを
** 	** セットしており、それは非常にまずい。
** 	** ということで上記関数の戻り値を判断しエラーの場合はメモリエラーで終わります。
** 	** By O.Kimoto 1998/05/09
** 	*/
** 	MEM_WriteDMA.SrcAddress = MEM_CalculateDMAAddress(ExecP -> ExecBlockNo);	/** DMA開始アドレス指定 */
#else
	chk_wt_dma_address = MEM_CalculateDMAAddress(ExecP -> ExecBlockNo);	/** DMA開始アドレス指定 */
	if(chk_wt_dma_address == (UDWORD)MEM_BLOCK_OVER) {
		DMA_RequestMask(MEM_WriteDMA.Channel);
		return (MEM_BLOCK_OVER);
	}
	MEM_WriteDMA.SrcAddress = chk_wt_dma_address;
#endif

	MEM_WriteDMA.Counter = (UWORD)(MEM_BLOCK_SIZE / 2);							/** 転送WORD数指定 １を引かなくしたM.Kotani1996/12/17*/
	MEM_WriteDMA.Unit = DMA_WORD_TRANSFER;										/** WORD転送指定 */
	MEM_WriteDMA.Direction = DMA_IO_TO_MEMORY;									/** 転送方向指定 */
#if 0 /* defined (SAKAKI) /* 通信コーデックの DMA のデバッグ用。For debug added by H.Kubo 1998/08/07 */
	if (Type == MEM_MODEM) {										/** 呼び元がモデム */
		DMA_ComCodecToDram_Debug = 1;
		MEM_WriteDMA.Counter = 4;
	}
#endif
	DMA_SetupDMAU(&MEM_WriteDMA);												/** DMAU Setup */

#if (PRO_CPU == SH7043)
	if (MEM_Debug)
		MEM_DebugCount = 16;
#endif

	while ((MEM_DMAEndStatus & end_status) != end_status) {						/** MEM_DMAEndStatusが何も立っていない場合 */
		/** STOP SW の監視 蓄積を止める */
		if (Type == MEM_SCANNER) {
			if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & (SYS_STOP_DOC_STORE + SYS_STOP_MULTI_COPY)) {
				DMA_RequestMask(MEM_WriteDMA.Channel);
				return (MEM_STOP_SW);
			}
			/* 通信時のSTOP_SWの監視はMODEMの中でやっているのでここでは必要ありません */
		}

		/** 割込み禁止期間開始 */
		CMN_DisableInterrupt();
#if 0 /* (PRO_COM_CODEC_TYPE == MN86064) && (PRO_EXT_DMAC == ENABLE) */ /* added by H.Kubo 1998/02/12 */
		DMA0_TC2Flag = 0;
#endif
		DMA_RequestEnable(MEM_WriteDMA.Channel);			/** DMA Start (CODEC -> DRAM) */
		/** DMATCのウエイト */
		#if (0) /* 受信原稿蓄積時にＦＡＴを一つ多く掴む対策 By S.Kawasaki 1996/09/10 */
		//if (Type == MEM_SCANNER)										/** 呼び元がSCANNER */
		//	wai_evt(EVT_DMA0_TC0);
		//else
		//	wai_evt(EVT_DMA0_TC2);
		#endif
		/*
		** 受信原稿蓄積時にＦＡＴを一つ多く掴む対策 By S.Kawasaki 1996/09/10
		*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
		if (Type == MEM_SCANNER) {										/** 呼び元がSCANNER */
			wai_evt(EVT_DMA_SCNCDC_DRAM);
			/*　蓄積されたページのデータ量を記憶するために、ここで4Kbyteづつバイト数を足し込んでいく */
			if (MEM_IndexTable[ExecP -> IndexNo1].Item == (UBYTE)(SYS_MEM_MAIL_TX_FILE | MEM_NOW_STORING)) {
				SYS_INF_StoredMailDataCount[SYS_INF_IndexTableNo] += (UDWORD)MEM_BLOCK_SIZE;
			}
		}
#endif
#if (PRO_DIALUP_INTERNET_FAX == DISABLE)
		if (Type == MEM_SCANNER)										/** 呼び元がSCANNER */
			wai_evt(EVT_DMA_SCNCDC_DRAM);
#endif
		else {
#if 0 /* (PRO_COM_CODEC_TYPE == MN86064) && (PRO_EXT_DMAC == ENABLE) */ /* added by H.Kubo 1998/02/12 */
			if (DMA0_TC2Flag == 0) { /* イベント空振り防止 H.Kubo 1998/02/12 */
#endif
				wai_evt(EVT_DMA_COMCDC_DRAM);
#if 0 /* (PRO_COM_CODEC_TYPE == MN86064) && (PRO_EXT_DMAC == ENABLE) */ /* added by H.Kubo 1998/02/12 */
@@			}
@@			else { /* イベント空振りがあった */
@@				DMA0_TC2Flag = 0;
@@				SYB_MaintenanceSwitch[MNT_SW_C1] |= DMA_CODEC_DRAM_TC_EVT_SKIP;
@@			}
#endif

#if 0 /* defined (SAKAKI) /* 通信コーデックの DMA のデバッグ用。For debug added by H.Kubo 1998/08/07 */
			while ( DMA_CheckDMA_Address(DMA_COMCDC_DRAM_CH, DMA_IO_TO_MEMORY) < (MEM_CalculateDMAAddress(ExecP -> ExecBlockNo) + MEM_BLOCK_SIZE)
			) {
				/* wai_tsk(1); */
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				DMA_RestartDMAU(DMA_COMCDC_DRAM_CH, DMA_IO_TO_MEMORY, 4, DMA_CheckDMA_Address(DMA_COMCDC_DRAM_CH, DMA_IO_TO_MEMORY));
				wai_evt(EVT_DMA_COMCDC_DRAM);
			}
#endif

#if 0 /*(PRO_MODEM == R288F) */ /* for debugging by H.Kubo 1998/01/30 */ /* deleted by H.Kubo 1998/07/08 */
@@			CMN_DisableInterrupt();
@@			word_register_value = DMA_CheckDMA_Counter(MEM_WriteDMA.Channel);
@@			if (0 == word_register_value) {
@@				/* 正常 */  /* uPD71021 は、カウンタ終了時 0xffff */
@@			}
@@			else { /* 不正ＤＭＡ ＴＣ */
@@				SYB_MaintenanceSwitch[MNT_SW_C1] |= DMA_CODEC_DRAM_TC_ILLEGAL;
@@				/* カウンタが終了しておらず、外部 DREQ がまだあるときは、
@@				** DMA 転送を継続する。
@@				*/
@@				if (DMA_CheckDreq(MEM_WriteDMA.Channel)) {
@@					continue;
@@				}
@@			}
@@			CMN_EnableInterrupt(); /* added by H.Kubo 1998/0122 これいれるの忘れてました。*/
#endif /* 0 */ /* (PRO_MODEM == R288F) */
			if (MEM_DMAEndStatus & MEM_RX_PAGE_END) {
				if (SYB_MaintenanceSwitch[MNT_SW_A9] & RX_FAT_SOLUTION) {/*FATを掴みすぎ対策*/
					DMA_RequestMask(MEM_WriteDMA.Channel);
					return (MEM_OK);
				}
			}
		}

		/** 割込み禁止期間終了 */
#if (PRO_CPU == SH7043)
		if ((MEM_Debug) && (--MEM_DebugCount==0)) {
			MEM_DebugCount = 16;
			/* Feb.6,1995 wai_tsk(1); */
			wai_tsk((UWORD )(SYS_MemorySwitch[95]*100)); /* Feb.6,1995 */
		}
#endif
		/** 蓄積可能ブロックの残量をチェック */
		if (Type == MEM_SCANNER) {	/** 蓄積原稿が受信原稿以外 */

#if (0)
** 			/* ＤＭＡをマスクしていない。 By O.Kimoto 1998/05/09 */
** 			if (MEM_CountTotalEmptyBlock() <= 0)							/** 使用可能ブロック数が０ブロック以下 */
** 				return (MEM_BLOCK_OVER);	/** 空ブロックなし終了 */
#else
			if (MEM_CountTotalEmptyBlock() <= 0) {							/** 使用可能ブロック数が０ブロック以下 */
				DMA_RequestMask(MEM_WriteDMA.Channel);
				return (MEM_BLOCK_OVER);	/** 空ブロックなし終了 */
			}
#endif

		} else {					/** 蓄積原稿が受信原稿 */

#if (0)
** 			/* ＤＭＡをマスクしていない。 By O.Kimoto 1998/05/09 */
** 			if ((MEM_CountTotalEmptyBlock() + MEM_RX_BORDERLINE) <= 0)		/** 使用可能ブロック数 + 裏メモリ(受信のみ使用可)のサイズが０ブロック以下 */
** 				return (MEM_BLOCK_OVER);	/** 空ブロックなし終了 */
#else
			if ((MEM_CountTotalEmptyBlock() + MEM_RX_BORDERLINE) <= 0) {		/** 使用可能ブロック数 + 裏メモリ(受信のみ使用可)のサイズが０ブロック以下 */
				DMA_RequestMask(MEM_WriteDMA.Channel);
				return (MEM_BLOCK_OVER);	/** 空ブロックなし終了 */
			}
#endif

		}

		/** 次の蓄積ブロックの獲得、更新 */
		if (MEM_WriteGetNextBlockNo(ExecP) == MEM_BLOCK_OVER) {
			/** 空ブロックなし終了 */
			DMA_RequestMask(MEM_WriteDMA.Channel);
			return (MEM_BLOCK_OVER);
		}
		/** 蓄積ブロックのアドレス算出 */

#if (0)
** 		/* MEM_CalculateDMAAddress()の戻り値はエラーの可能性がある。しかし、それを判断せずにＤＭＡアドレスを
** 		** セットしており、それは非常にまずい。
** 		** ということで上記関数の戻り値を判断しエラーの場合はメモリエラーで終わります。
** 		** By O.Kimoto 1998/05/09
** 		*/
** 		DMA_SetDMA_Address(MEM_WriteDMA.Channel, DMA_IO_TO_MEMORY, MEM_CalculateDMAAddress(ExecP -> ExecBlockNo));
#else
		chk_wt_dma_address = MEM_CalculateDMAAddress(ExecP -> ExecBlockNo);
		if(chk_wt_dma_address == (UDWORD)MEM_BLOCK_OVER) {
			DMA_RequestMask(MEM_WriteDMA.Channel);
			return (MEM_BLOCK_OVER);
		}
		DMA_SetDMA_Address(MEM_WriteDMA.Channel, DMA_IO_TO_MEMORY, chk_wt_dma_address);
#endif

		DMA_SetDMA_Counter(MEM_WriteDMA.Channel, MEM_WriteDMA.Counter);
		/* 位相ずれデバッグ */
		if (Debug) {
			if (--DebugCount == 0) {
				wai_tsk(1); /** DEBUG Sep.17,1994 */
				Debug = 0;
			}
		}
	}
	DMA_RequestMask(MEM_WriteDMA.Channel);
	return (MEM_OK);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[メモリ・マルチ・ライト・クローズ]
	function	:[
		1. 原稿の蓄積終了時にインデックスとFATエリアの情報を確定します
		2. メモリ・マルチ・ライト・オープンした原稿にのみ有効です
	]
	return		:[なし]
	common		:[
		struct IndexTableData_t MEM_IndexTable[],
		UWORD  MEM_FATArea[],
		UWORD  MEM_TopEmptyBlock,
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/01/05]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void MEM_MultiWriteClose (struct MEM_ExecData_t *ExecP,		/* 蓄積状況格納領域を指定します */
						  UWORD LineCount)			/* 蓄積ライン数 */
{
	UBYTE n;

	CMN_DisableInterrupt();		/* By Y.Suzuki 1997/05/07 */

	/** インデックスの確定 */
	/** インデックスNo.1の原稿種別の蓄積中bitのOFF */
	for (n = 0; n < SYS_JOB_MAX; n++) {
		if (MEM_MultiProgramOpenIndexNo[n] == 0xFF)
			break;
		MEM_IndexTable[MEM_MultiProgramOpenIndexNo[n]].Item &= ~MEM_NOW_STORING;
		MEM_IndexTable[MEM_MultiProgramOpenIndexNo[n]].LineCount = LineCount;			/** コーデックからの蓄積ライン数の入力 */
		MEM_MultiProgramOpenIndexNo[n] = 0xFF;
	}

	/** FATエリアの確定 */
	/** 蓄積最終ブロックにEOPをセット */
	/*CMN_DisableInterrupt();*/
	if (ExecP -> NextBlockNo != MEM_NO_INDEX) {
		MEM_FATArea[ExecP -> NextBlockNo] = MEM_TopEmptyBlock;
		MEM_TopEmptyBlock = ExecP -> NextBlockNo;
	}
	MEM_FATArea[ExecP -> ExecBlockNo] = MEM_EOP_BLOCK;

	/** 蓄積中だったブロックはまだカウントされていません */
	MEM_TotalStoreBlockCounter++;
	CMN_EnableInterrupt();

	/** 終了 */
	return;
}
#endif


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[メモリ・ライト・クローズ]
	function	:[
		1. 原稿の蓄積終了時にインデックスとFATエリアの情報を確定します
	]
	return		:[なし]
	common		:[
		struct IndexTableData_t MEM_IndexTable[],
		UWORD  MEM_FATArea[],
		UWORD  MEM_TopEmptyBlock,
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/01/05]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
void MEM_WriteCloseFlsRom (struct MEM_ExecData_t *ExecP,/* 蓄積状況格納領域を指定します */
					 		UWORD LineCount)			/* 蓄積ライン数 */
#else
void MEM_WriteClose (struct MEM_ExecData_t *ExecP,/* 蓄積状況格納領域を指定します */
					 UWORD LineCount)			/* 蓄積ライン数 */
#endif
{
	CMN_DisableInterrupt();		/* By Y.Suzuki 1997/05/07 */

	/** インデックスの確定 */
	/** インデックスNo.1の原稿種別の蓄積中bitのOFF */
	MEM_IndexTable[ExecP -> IndexNo1].Item &= ~MEM_NOW_STORING;
	MEM_IndexTable[ExecP -> IndexNo1].LineCount = LineCount;			/** コーデックからの蓄積ライン数の入力 */

	/** FATエリアの確定 */
	/** 蓄積最終ブロックにEOPをセット */
	CMN_DisableInterrupt();
	if (ExecP -> NextBlockNo != MEM_NO_INDEX) {
		MEM_FATArea[ExecP -> NextBlockNo] = MEM_TopEmptyBlock;
		MEM_TopEmptyBlock = ExecP -> NextBlockNo;
	}
	MEM_FATArea[ExecP -> ExecBlockNo] = MEM_EOP_BLOCK;

	/** 蓄積中だったブロックはまだカウントされていません */
	MEM_TotalStoreBlockCounter++;
	CMN_EnableInterrupt();

#if 0 /* defined (SAKAKI) /* added by H.Kubo 1998/08/07 */
	DMA_ComCodecToDram_Debug = 0;
#endif

	/** 終了 */
	return;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[次の蓄積ブロックの獲得]
	function	:[
		1. 指定されたブロックのチェーン化されている次の空ブロックを獲得する
	]
	return		:[
		#define MEM_OK					次ブロック獲得正常終了
		#define MEM_BLOCK_OVER			次ブロックがない(指定ブロックがEOBだった)
	]
	common		:[
		UWORD  MEM_FATArea[],
		UWORD  MEM_AvailableMaxFATArea,
		UWORD  MEM_TopEmptyBlock,
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/01/05]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* UWORD MEM_WriteGetNextBlockNo (struct MEM_ExecData_t *ExecP) */
UWORD MEM_WriteGetNextBlkNoERom(struct MEM_ExecData_t *ExecP)
{
	/** 割込み禁止期間開始 */
	CMN_DisableInterrupt();		/* By Y.Suzuki 1997/05/07 */

	/*if ((MEM_TopEmptyBlock == MEM_EOB_BLOCK) || (MEM_TotalStoreBlockCounter == MEM_TotalAvailableStoreBlkCnt)) {*//** 空ブロックの先頭がEOBか

	/* 1997/11/20
	 *
	*/
	if ((MEM_TopEmptyBlock == MEM_EOB_BLOCK) || ((MEM_TotalStoreBlockCounter + 1) >= MEM_TotalAvailableStoreBlkCnt)) {/** 空ブロックの先頭がEOBか
																													蓄積可能ブロック数より蓄積ブロック数が多い*/
		/** 空ブロックなし終了 */
		CMN_EnableInterrupt();		/* 1997/08/18 M.Kotani */
		return (MEM_BLOCK_OVER);
	}

	/*-----------------------------------------------
	 * ブロックに空きがあるかどうか
	 * EOBブロックには蓄積しません
	 * NAGANOから移植 V851 By Y.Suzuki 2002/07/27
	*/
/*#if defined(POPLAR_H) && defined(JP0)*/
	if (MEM_CheckTopEmptyBlock(MEM_TopEmptyBlock, 2) == 0) {
		CMN_EnableInterrupt();
		return (MEM_BLOCK_OVER);
	}
/*#endif*/


#if (PRO_EXT_DMAC == ENABLE)
	/* スキャナー位相ずれデバッグ T.Nose 1998/02/05 */
/*	if ((SYB_MaintenanceSwitch[MNT_SW_C1] & 0x40)	bit変更	By M.Tachibana 1998/05/19 */
	if ((SYB_MaintenanceSwitch[MNT_SW_C1] & 0x01)
	 && (ExecP -> NextBlockNo != MEM_NO_INDEX)) {		/* AutoInitialize */

		/** 蓄積ブロックと予約済みブロックをチェーン化 */
		MEM_FATArea[ExecP -> ExecBlockNo] = ExecP -> NextBlockNo;

		/** 蓄積ブロックの更新 (予約済み次ブロック) */
		ExecP -> ExecBlockNo = ExecP -> NextBlockNo;

		/** 予約次ブロックと空ブロックの先頭をチェーン化 */
		MEM_FATArea[ExecP -> NextBlockNo] = MEM_TopEmptyBlock;

		/** 予約次ブロックの更新 (空ブロックの先頭) */
		ExecP -> NextBlockNo = MEM_FATArea[ExecP -> NextBlockNo];

		/** 空ブロックの先頭の更新 */
		MEM_TopEmptyBlock = MEM_FATArea[ExecP -> NextBlockNo];

		/** 空ブロックの最終の更新 */
		if (ExecP -> NextBlockNo == MEM_EndBlock) {	/** 予約次ブロックと空ブロックの最終とが一致 */
			/** 空ブロックの最終はEOB */
			MEM_EndBlock = MEM_EOB_BLOCK;
		}

		/** FAT上の予約次ブロックは予約ブロックであることを指示 */
		MEM_FATArea[ExecP -> NextBlockNo] = MEM_RESERVED_BLOCK;

#if (0)	/* メモリオーバーするたびにRESERVEDブロックが増えていく By M.Tachibana 1998/05/18 */
		/** 空ブロックの最終の更新 */
		if (MEM_TopEmptyBlock != MEM_EOB_BLOCK) {	/** 予約次ブロックと空ブロックの最終とが一致 */
			/** FAT上の予約次ブロックは予約ブロックであることを指示 */
			MEM_FATArea[ExecP -> NextBlockNo] = MEM_RESERVED_BLOCK;
		}
#endif

		/** 蓄積中のブロックは蓄積中であることを指示 */
		MEM_FATArea[ExecP -> ExecBlockNo] |= MEM_STORING_BLOCK;
	}
	else {
#endif

		/** 蓄積ブロックと空ブロックの先頭をチェーン化 */
		MEM_FATArea[ExecP -> ExecBlockNo] = MEM_TopEmptyBlock;

		/** 蓄積ブロックの更新 (空ブロックの先頭) */
		ExecP -> ExecBlockNo = MEM_TopEmptyBlock;

		/** 空ブロックの先頭の更新 */
		MEM_TopEmptyBlock = MEM_FATArea[ExecP -> ExecBlockNo];

		/** 空ブロックの最終の更新 */
		if (ExecP -> ExecBlockNo == MEM_EndBlock) {	/** 蓄積ブロックと空ブロックの最終とが一致 */
			/** 空ブロックの最終はEOB */
			MEM_EndBlock = MEM_EOB_BLOCK;
		}
		/** 蓄積中のブロックは蓄積中であることを指示 */
		MEM_FATArea[ExecP -> ExecBlockNo] |= MEM_STORING_BLOCK;
		/*CMN_EnableInterrupt();*/
		/** 割込み禁止期間終了 */

#if (PRO_EXT_DMAC == ENABLE)
	}
#endif

	/** 総蓄積ブロック数の更新 */
	MEM_TotalStoreBlockCounter++;

	store_buffer_point = ExecP -> ExecBlockNo;

	/** 割込み禁止期間終了 */
	CMN_EnableInterrupt();		/* By Y.Suzuki 1997/05/07 */

	/** 正常終了 */
	return (MEM_OK);
}


/* NAGANO から移植 ｽﾀｰﾄﾌﾞﾛｯｸに最大ﾌﾞﾛｯｸ+1(9DA)が入った。(8MB増設接続時) V851 By Y.Suzuki 2002/07/27*/
/*#if defined(POPLAR_H) && defined(JP0)*/
/*************************************************************************
	module		:[メモリブロックに空きがあるかどうかのチェック]
	function	:[
		1.指定されたブロック数の先まで空きを見ます
	]
	return		:[
			1:空きがある
			0:空きがない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1998/11/10]
	author		:[]
*************************************************************************
	module		:[check whether the memory block has free space]
	function	:[
		1.指定されたブロック数の先まで空きを見ます
	]
	return		:[
			1:free space exists
			0:no free space exists
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1998/11/10]
	author		:[]
*************************************************************************/
UWORD MEM_CheckTopEmptyBlock(UWORD start_block_no, UWORD next_cnt)
{
	UWORD	top_block;
	UWORD	i;
	UWORD	eob_detect;

	eob_detect = 0;
	top_block = start_block_no;

	for (i = 0; i < next_cnt; i++) {
		if (top_block == MEM_EOB_BLOCK) {
			eob_detect = 1;
			break;
		}
		else {
			if ((top_block == MEM_BAD_BLOCK)
			 || (top_block == MEM_RESERVED_BLOCK)
			 || (top_block & MEM_STORING_BLOCK)) {
				NackBuzzerSound();
				NackBuzzerSound();
				outp((UDWORD)0,(UBYTE)0);	/* WriteProtectError for ICE */
				InitializeDRAM_Parameter();
				SaveReturnAddressAndJumpBegin();
			}
		}
		top_block = MEM_FATArea[top_block];
	}
	if (eob_detect) {
		return(0);
	}
	else {
		return(1);
	}
}
/*#endif*/
