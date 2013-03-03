/************************************************************************
*				By : NOBUKO
*			  Date : Sat 25 Dec. 1993 (\SRC\RICE\MEMDUAL.C)
*		 Copy Date : Tue 12 Sep. 1995
*				   : 1996/10/21 From \src\kobe\anzu\src\ By M.Kotani
*		 File Name : MEMDUAL.C
*	   Module Name : 1. UBYTE MEM_DualOpen(*StoreP, *IndexP, *ExecP)
*					 2. void MEM_DualClose(*ExecP)
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\mon_pro.h"	/* 1997/12/16 Y.M */
#include "\src\atlanta\sh7043\define\def_semn.h"
#include "\src\atlanta\sh7043\ext_v\extv_sem.h"	/* 1997/12/16 Y.M */
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\ext_v\mem_data.h"
#include "\src\atlanta\ext_v\bkupram.h"

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
#include "\src\atlanta\ext_v\sys_inf.h"
#endif

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[メモリ・二重・オープン]
	function	:[
		1. 蓄積時に二重インデックス作成のための領域を二枚分確保する
		2. 実際のイメージ・メモリ領域は共通
	]
	return		:[
		#define MEM_INDEX_OVER	二枚分のインデックスが確保できなかった
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
	date		:[1993/12/25]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_DualOpen (struct MEM_StoreData_t *StoreP,				/* 原稿の蓄積情報を指定します */
					struct MEM_IndexData_t *IndexP,				/* 二重インデックスの内容を指示します */
					struct MEM_ExecData_t	 *ExecP)				/* 蓄積中のデータを格納するエリアを指定します */
{
	UWORD index_no;

	wai_sem(semno.MEM_WriteOpenSem);	/* WRITE_OPEN_SEM 1997/12/16 Y.Murata */

	/** 蓄積中に使用するデータの初期化を行います */
	ExecP -> IndexNo1 = MEM_NO_INDEX;
	ExecP -> IndexNo2 = MEM_NO_INDEX;
	ExecP -> ExecBlockNo = MEM_NO_INDEX;
	ExecP -> NextBlockNo = MEM_NO_INDEX;

	if (MEM_TopEmptyBlock == MEM_EOB_BLOCK) {	/** 空ブロックの先頭がEOB */
		/** 空ブロックなし終了 */
		sig_sem(semno.MEM_WriteOpenSem);	/* WRITE_OPEN_SEM 1997/12/16 Y.Murata */
		return ((UBYTE)MEM_BLOCK_OVER);
	}

	/** 蓄積可能ブロックの残量をチェックします */
	if (StoreP -> Item == SYS_MEM_RX_FILE) {	/** 蓄積原稿が受信原稿 */
		if (MEM_TotalAvailableStoreBlkCnt - MEM_TotalStoreBlockCounter <= 0) {	/** 使用可能ブロック数－使用ブロック数が０ブロック以下 */
			/** 空ブロックなし終了 */
			sig_sem(semno.MEM_WriteOpenSem);	/* WRITE_OPEN_SEM 1997/12/16 Y.Murata */
			return ((UBYTE)MEM_BLOCK_OVER);
		}
	}
	else {
		if (MEM_TotalAvailableStoreBlkCnt - MEM_TotalStoreBlockCounter - MEM_RX_BORDERLINE <= 0) {	/** 使用可能ブロック数－使用ブロック数－
																										裏メモリ(受信のみ使用可)のサイズが０ブロック以下 */
			/** 空ブロックなし終了 */
			sig_sem(semno.MEM_WriteOpenSem);	/* WRITE_OPEN_SEM 1997/12/16 Y.Murata */
			return ((UBYTE)MEM_BLOCK_OVER);
		}
	}

	/** 使用インデックスの確保 */
	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {	/** インデックス・テーブル内の検索 */
		if (MEM_IndexTable[index_no].Item == SYS_MEM_FILE_EMPTY) {	/** 空インデックス */
			if ((ExecP -> IndexNo1 != MEM_NO_INDEX) &&
				(ExecP -> IndexNo2 == MEM_NO_INDEX)) {	/** インデックスNo.1の確保ができていて、インデックスNo.2の確保がまだ */
				/** インデックスNo,2を確保 */
				ExecP -> IndexNo2 = index_no;
				/** 検索終了 */
				break;
			}
			if (ExecP -> IndexNo1 == MEM_NO_INDEX) {	/** インデックスNo.1の確保がまだ */
				/** インデックスNo.1を確保 */
				ExecP -> IndexNo1 = index_no;
			}
		}
	}
	if ((ExecP -> IndexNo1 == MEM_NO_INDEX) && (ExecP -> IndexNo2 == MEM_NO_INDEX)) {	/** 二枚の空インデックスなし */
		/** 空インデックスなし終了 */
		sig_sem(semno.MEM_WriteOpenSem);	/* WRITE_OPEN_SEM 1997/12/16 Y.Murata */
		return ((UBYTE)MEM_INDEX_OVER);
	}

	CMN_DisableInterrupt(); /* WRITE_OPEN_SEM 1997/12/16 Y.Murata */
	/** 使用が確定したインデックスにデータを書き込む(インデックスNo.1) */
	MEM_IndexTable[ExecP -> IndexNo1].Item = (UBYTE)(StoreP -> Item | MEM_NOW_STORING);
	MEM_IndexTable[ExecP -> IndexNo1].No = StoreP -> No;
	MEM_IndexTable[ExecP -> IndexNo1].Page = StoreP -> Page;
/* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/29  By T.Yamaguchi */
	MEM_IndexTable[ExecP -> IndexNo1].BoxNumber = StoreP -> BoxNumber;
/* #endif */
	MEM_IndexTable[ExecP -> IndexNo1].Code = StoreP -> Code;
	MEM_IndexTable[ExecP -> IndexNo1].Mode = StoreP -> Mode;
	MEM_IndexTable[ExecP -> IndexNo1].Size = StoreP -> Size;
	MEM_IndexTable[ExecP -> IndexNo1].StartBlockNo = MEM_TopEmptyBlock;

	/** 使用が確定したインデックスにデータを書き込む(インデックスNo.2) */
	MEM_IndexTable[ExecP -> IndexNo2].Item = (UBYTE)(IndexP -> Item | MEM_NOW_STORING);
	MEM_IndexTable[ExecP -> IndexNo2].No = IndexP -> No;
	MEM_IndexTable[ExecP -> IndexNo2].Page = IndexP -> Page;
/* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/29  By T.Yamaguchi */
	MEM_IndexTable[ExecP -> IndexNo2].BoxNumber = IndexP -> BoxNumber;
/* #endif */
	MEM_IndexTable[ExecP -> IndexNo2].Code = StoreP -> Code;
	MEM_IndexTable[ExecP -> IndexNo2].Mode = StoreP -> Mode;
	MEM_IndexTable[ExecP -> IndexNo2].Size = StoreP -> Size;
	MEM_IndexTable[ExecP -> IndexNo2].StartBlockNo = MEM_TopEmptyBlock;

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
	/*　蓄積されたページのデータ量を記憶するために使用が確定したインデックスの
	**	配列オフセットを以下の変数に記憶させておきます
	*/
	if (StoreP -> Item == SYS_MEM_MAIL_TX_FILE) {
		SYS_INF_IndexTableNo = (UWORD)ExecP -> IndexNo1;
		SYS_INF_StoredMailDataCount[SYS_INF_IndexTableNo] = 0;	/* 初期化 */
	}
#endif

	/*CMN_DisableInterrupt(); WRITE_OPEN_SEM 1997/12/16 Y.Murata */
	/** 蓄積中に使用するデータにブロック情報を書き込む(Execデータ、FAT) */
	/** 蓄積ブロックは空ブロックの先頭 */
	ExecP -> ExecBlockNo = MEM_TopEmptyBlock;
	/** 空ブロックの先頭の更新 */
	MEM_TopEmptyBlock = MEM_FATArea[ExecP -> ExecBlockNo];
	/** 蓄積中のブロックは蓄積中であることをbitで指示 */
	MEM_FATArea[ExecP -> ExecBlockNo] |= MEM_STORING_BLOCK;
	CMN_EnableInterrupt(); /* WRITE_OPEN_SEM 1997/12/16 Y.Murata */

	sig_sem(semno.MEM_WriteOpenSem);	/* WRITE_OPEN_SEM 1997/12/16 Y.Murata */

	/** 正常終了 */
	return (MEM_OK);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[メモリ・二重・クローズ]
	function	:[
		1. 二重インデックスで蓄積していた原稿の蓄積終了時に 二枚分のインデックスと一枚分のFATエリアを確定します
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/25]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void MEM_DualClose (struct MEM_ExecData_t *ExecP,					/* 蓄積状況格納領域を指定します */
					UWORD LineCount)							/* 蓄積ライン数 */
{
	CMN_DisableInterrupt();		/* By Y.Suzuki 1998/02/05 */
	/** インデックスの確定 */
	/** 原稿種別の蓄積中bitのOFF */
	MEM_IndexTable[ExecP -> IndexNo1].Item &= ~MEM_NOW_STORING;
	MEM_IndexTable[ExecP -> IndexNo1].LineCount = LineCount;			/** コーデックからの蓄積ライン数の入力 */

	MEM_IndexTable[ExecP -> IndexNo2].Item &= ~MEM_NOW_STORING;
	MEM_IndexTable[ExecP -> IndexNo2].LineCount = LineCount;			/** コーデックからの蓄積ライン数の入力 */

	/** FATエリアの確定 */
	/** 蓄積最終ブロックにEOPをセット */
	MEM_FATArea[ExecP -> ExecBlockNo] = MEM_EOP_BLOCK;

	/** 蓄積中だったブロックはまだカウントされていません */
	MEM_TotalStoreBlockCounter++;

	CMN_EnableInterrupt();	/* By Y.Suzuki 1998/02/05 */
	/** メモリ・デュアル・ライト・クローズの終了 */
	return;
}
