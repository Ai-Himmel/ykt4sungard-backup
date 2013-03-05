/************************************************************************
*				By : NOBUKO
*			  Date : Sat 25 Dec. 1993 (\SRC\RICE\SRC\MEMCLEAR.C)
*		 Copy Date : Tue 12 Sep. 1995
*				   : 1996/10/21 From \src\kobe\anzu\src\ By M.Kotani
*		 File Name : MEMCLEAR.C
*	   Module Name :
*		1. void MEM_ClearAll (void)
*		2. void MEM_ClearAllIndexArea (void)
*		3. UBYTE MEM_ClearPageAndFATArea (struct MEM_IndexData_t *IndexP)
*		4. UBYTE MEM_ClearPage (struct MEM_IndexData_t *IndexP)
*		5. UBYTE MEM_ClearDocAndFATArea (UBYTE Item, UWORD No)
*		6. UBYTE MEM_ClearDoc (UBYTE Item, UWORD No)
*		7. UBYTE MEM_ClearBreak (struct MEM_IndexData_t *IndexP)
*		8. UBYTE MEM_ClearPowerDown (void)
*		9. void ClearIndexAndFATAreaAppointNo(UWORD AppointIndexNo);
*	   10. void ClearIndex(UWORD IndexNo)
************************************************************************/

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\mem_data.h"

#define NO		0
#define YES		1
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
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/25]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void MEM_ClearAll (void)
{
	UBYTE i;
											/* DRAM容量自動判別にMEM_IndexTable[]を使用するので先にFATのクリアをしてしまいます */
	ClearAllFATArea();						/* FATエリアの初期化を行います */
	MEM_ClearAllIndexArea();				/* インデックス・テーブルの初期化を行います */
	for (i = 0; i < SYS_JOB_MAX; i++)
		MEM_MultiProgramOpenIndexNo[i] = 0xFF;
/*	InitializeDRAM_Parameter();*/				/* DRAMクリア時のパラメータのクリア (Sep.06,94) */

	return;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[インデックス・エリアの初期化]
	function	:[
		すべてのインデックスの初期化を行います
		一枚づつ、初期値を代入します
	]
	return		:[なし]
	common		:[なし]
	condition	:[なし]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/25]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void MEM_ClearAllIndexArea (void)
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* 一枚づつ全インデックス・テーブルを初期化します */
		MEM_IndexTable[index_no].Item = SYS_MEM_FILE_EMPTY;				/* Itemの初期値 (SYS_MEM_FILE_EMPTY == 0) */
		MEM_IndexTable[index_no].No = 0;								/* Noの初期値 (0) */
		MEM_IndexTable[index_no].Page = 0;								/* Pageの初期値 (0) */
		MEM_IndexTable[index_no].BoxNumber = 0;							/* BOXﾅﾝﾊﾞｰを入れる 1997/01/09	By T.Yamaguchi */
		MEM_IndexTable[index_no].Dummy = 0xFF;								/* 未使用 */
		MEM_IndexTable[index_no].Code = 0xFF;							/* Codeの初期値 (0xFF) */
		MEM_IndexTable[index_no].Mode = 0xFF;							/* Modeの初期値 (0xFF) */
		MEM_IndexTable[index_no].Size = 0xFF;							/* Sizeの初期値 (0xFF) */
/*#if (PRO_PC_PRINT == ENABLE)	@* 1996/09/03 By J.Miyazaki *//* 条件をはずす By M.Tachibana 1997/12/06 */
		MEM_IndexTable[index_no].Area = 0xFF;
		MEM_IndexTable[index_no].Cassette = 0xFF;
/*#endif*/
		MEM_IndexTable[index_no].LineCount = 0;							/* LineCountの初期値 (0) */
		MEM_IndexTable[index_no].StartBlockNo = MEM_FAT_AREA_MAX;		/* StartBlockNoの初期値 (MEM_FAT_AREA_MAX) */
	}

	return;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定原稿の消去]
	function	:[
		指定原稿のインデックスを消去します
		指定原稿のFATエリアを共有しているインデックスが他にもあればそのインデックスも消去します
		指定原稿のFATエリアを消去します
	]
	return		:[
		MEM_OK					0	消去正常終了
		MEM_NO_INDEX		 0xFF	消去指定原稿なし
	]
	common		:[なし]
	condition	:[なし]
	comment		:[
		指定ページを消去します
		蓄積済みの原稿を消去したい場合にCALLしてください
		インデックスとFATを消去します
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/25]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UBYTE MEM_ClearPageAndFATAreaFlsRom (struct MEM_IndexData_t *IndexP)	/** 消去原稿を指定します */
#else
UBYTE MEM_ClearPageAndFATArea (struct MEM_IndexData_t *IndexP)	/** 消去原稿を指定します */
#endif
{
	UWORD i;												/** MEM_IndexTable[]内のポインタ */
	UWORD index_no;											/** MEM_IndexTable[]内のポインタ */
	UWORD start_block_no;									/** FAT消去のための消去開始ブロック指定データ */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/** 全インデックス・テーブル内を検索し、該当インデックスを確定します */
																	/** 該当インデックスを確定します */
		if ((MEM_IndexTable[index_no].Item == IndexP -> Item) &&	/** MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&	/** MEM_IndexTable[]上のNoと指定されたNoが一致していて */
/* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/24  By T.Yamaguchi */
			((MEM_IndexTable[index_no].BoxNumber == IndexP -> BoxNumber) ||
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
/* #endif */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/** MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
			start_block_no = MEM_IndexTable[index_no].StartBlockNo;	/** 該当インデックスのStartBlockNoが消去開始ブロック指定データとなります */

			ClearIndex(index_no);									/** 該当インデックス・テーブルを消去します */
			break;													/** 該当インデックスは1枚のみです */
		}
	}

	if (index_no >= MEM_INDEX_TABLE_MAX) {							/** 該当インデックスなしならば */
		return ((UBYTE)MEM_NO_INDEX);								/** MEM_NO_INDEX を返します */
	}

																	/** 二重定義しているインデックスが他にないか検索します */
	for (i = 0; i < MEM_INDEX_TABLE_MAX; i++) {						/** もう一度全インデックス・テーブル内を検索し、二重インデックスを探します */
		if ((MEM_IndexTable[i].Item != SYS_MEM_FILE_EMPTY) &&		/** MEM_IndexTable[]上のItemが蓄積済みで */
			(i != index_no) &&
			(MEM_IndexTable[i].StartBlockNo == start_block_no)) {	/** 該当インデックスと同じStartBlockNoを持つインデックスを検索します */
			ClearIndex(i);											/** 二重定義しているインデックスが見つかったらそのインデックスを消去します */
			break;													/** 二重定義のみ有効(三重定義以上は無効)です */
		}
	}

	ClearFATArea(start_block_no);									/** FATエリアを消去します */

	MEM_IndexTable[index_no].Item = SYS_MEM_FILE_EMPTY;				/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */
	if (i < MEM_INDEX_TABLE_MAX)
		MEM_IndexTable[i].Item = SYS_MEM_FILE_EMPTY;				/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */

	return ((UBYTE)MEM_OK);											/** MEM_OKを返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ページ毎の原稿の消去]
	function	:[

	]
	return		:[
		MEM_OK					0	消去正常終了
		MEM_NO_INDEX		 0xFF	消去指定原稿なし
	]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/25]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_ClearPage (struct MEM_IndexData_t *IndexP)		/* 消去原稿を指定します */
{
	UWORD i;												/* MEM_IndexTable[]内のポインタ */
	UWORD index_no;										/* MEM_IndexTable[]内のポインタ */
	UWORD start_block_no;									/* FAT消去のための消去開始ブロック指定データ */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* 全インデックス・テーブル内を検索します */
																	/* 該当インデックスを確定します */
		if ((MEM_IndexTable[index_no].Item == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&	/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
/* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/24  By T.Yamaguchi */
			((MEM_IndexTable[index_no].BoxNumber == IndexP -> BoxNumber) ||
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
/* #endif */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
			start_block_no = MEM_IndexTable[index_no].StartBlockNo;	/* 該当インデックスのStartBlockNoが消去開始ブロック指定データとなります */

			ClearIndex(index_no);									/* 該当インデックスを消去します */
			break;													/* 該当インデックスは1枚のみです */
		}
	}

	if (index_no >= MEM_INDEX_TABLE_MAX) {							/* 該当インデックスがないならば */
		return ((UBYTE)MEM_NO_INDEX);								/* MEM_NO_INDEXを返します */
	}

																	/* 二重定義しているインデックスが他にないか検索します */
	for (i = 0; i < MEM_INDEX_TABLE_MAX; i++) {						/* もう一度全インデックス・テーブル内を検索し、二重インデックスを探します */
		if ((MEM_IndexTable[i].Item != SYS_MEM_FILE_EMPTY) &&		/* MEM_IndexTable[]上のItemが空インデックスではなくて */
			(i != index_no) &&
			(MEM_IndexTable[i].StartBlockNo == start_block_no)) {	/* MEM_IndexTable[]上のStartBlockNoとstart_block_noが一致していたら */
																	/* それは二重インデックスなので、そのインデックスもFATも消去しません */
			MEM_IndexTable[index_no].Item = SYS_MEM_FILE_EMPTY;		/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */
			return ((UBYTE)MEM_OK);									/* MEM_OKを返します */
		}
	}

																	/* ここまできたら二重インデックスがないということなので */
	ClearFATArea(start_block_no);									/* FATエリアを消去します */
	MEM_IndexTable[index_no].Item = SYS_MEM_FILE_EMPTY;				/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */

	return ((UBYTE)MEM_OK);											/* MEM_OKを返します*/
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[インデックス毎の原稿の消去]
	function	:[
		1.
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
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UBYTE MEM_ClearDocAndFATAreaFlsRom (UBYTE Item,			/* 消去原稿の原稿種別を指定します */
							  		UWORD No,			/* 消去原稿のNoを指定します */
							  		UBYTE BoxNumber)	/* ボックス番号の指定をします */
#else
UBYTE MEM_ClearDocAndFATArea (UBYTE Item,		/* 消去原稿の原稿種別を指定します */
							  UWORD	 No,		/* 消去原稿のNoを指定します */
							  UBYTE BoxNumber)	/* ボックス番号の指定をします */
#endif
{
	UBYTE flag;												/* 消去原稿 有/無 のフラグ */
	UWORD index_no1;										/* MEM_IndexTable[]内のポインタ */
	UWORD index_no2;										/* MEM_IndexTable[]内のポインタ */
	UWORD start_block_no;									/* FAT消去のための消去開始ブロック指定データ */

	flag = NO;														/* 消去原稿なしに初期化 */

																	/* 全インデックス・テーブル上を検索し */
	for (index_no1 = 0; index_no1 < MEM_INDEX_TABLE_MAX; index_no1++) {/* 消去を指定されたインデックスNoを確定する (蓄積中の原稿も対象にする) */
		if ( ((MEM_IndexTable[index_no1].Item == (UBYTE)(Item | MEM_NOW_STORING))	/* MEM_IndexTable[]上のItemと指定されたItemが一致 */
			||(MEM_IndexTable[index_no1].Item == Item))			/* MEM_IndexTable[]上のNoと指定されたNoが一致 */
		   &&((MEM_IndexTable[index_no1].No	== No) || (No == MEM_ALL_NO))	/* MEM_IndexTable[]上のPageと指定されたPageが一致 */
		   &&((MEM_IndexTable[index_no1].BoxNumber == BoxNumber) || (BoxNumber == MEM_IGNORE_BOX_NUMBER)) )	{	/* BoxNumberも比較する様に変更 */
			flag = YES;												/* 消去原稿あり */
			start_block_no = MEM_IndexTable[index_no1].StartBlockNo;	/* 該当インデックスのStartBlockNoが消去開始ブロック指定データとなります */


			ClearIndex(index_no1);									/* 該当インデックスを消去します */

																	/* 二重定義しているインデックスが他にないか検索する */
			for (index_no2 = 0; index_no2 < MEM_INDEX_TABLE_MAX; index_no2++) {/* もう一度全インデックス・テーブル内を検索し二重インデックスを探す*/
				if ((MEM_IndexTable[index_no2].Item != SYS_MEM_FILE_EMPTY) &&/* MEM_IndexTable[]上のItemが空インデックスではなくて */
					(index_no1 != index_no2) &&
					(MEM_IndexTable[index_no2].StartBlockNo == start_block_no)) {/* 該当インデックスと同じStartBlockNoを持つインデックスを検索する */
					ClearIndex(index_no2);							/* 二重定義しているインデックスが見つかったら、そのインデックスも消去します */
					break;											/** 二重定義のみ有効(三重定義以上は無効)です */
				}
			}
			ClearFATArea(start_block_no);							/* FATエリアの消去をします */

			MEM_IndexTable[index_no1].Item = SYS_MEM_FILE_EMPTY;		/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */
			if (index_no2 < MEM_INDEX_TABLE_MAX)
				MEM_IndexTable[index_no2].Item = SYS_MEM_FILE_EMPTY;	/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */

		}
	}

	if (flag == NO) {												/* 消去原稿がなかったなら
		return ((UBYTE)MEM_NO_INDEX);								/* MEM_NO_INDEX を返します */
	}

	return ((UBYTE)MEM_OK);											/* MEM_OK を返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[インデックス毎の原稿の消去]
	function	:[
		1.
	]
	return		:[
		MEM_OK					0	消去正常終了
		MEM_NO_INDEX		 0xFF	消去指定原稿なし
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[]
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/25]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_ClearDoc (UBYTE Item,					/* 消去原稿の原稿種別を指定します */
					UWORD  No,					/* 消去原稿のNoを指定します */
					UBYTE BoxNumber)			/* ボックス番号の指定をします */
{
	UBYTE flag;												/* 消去原稿 有/無 のフラグ */
	UBYTE fat_delete;										/* FAT消去 許可/不許可 のフラグ */
	UWORD index_no1;										/* MEM_IndexTable[]内のポインタ */
	UWORD index_no2;										/* MEM_IndexTable[]内のポインタ */
	UWORD start_block_no;									/* FAT消去のための消去開始ブロック指定データ */

	flag = NO;														/* 消去原稿なしに初期化 */
	fat_delete = YES;												/* FAT消去許可に初期化 */
	start_block_no = MEM_EOB_BLOCK;									/* EOBブロックに初期化 */

																	/* 全インデックス・テーブル上を検索し */
	for (index_no1 = 0; index_no1 < MEM_INDEX_TABLE_MAX; index_no1++) {/* 消去指定インデックスを確定します(蓄積中の原稿も対象にします) */
		if ( ((MEM_IndexTable[index_no1].Item == (UBYTE)(Item | MEM_NOW_STORING))	/* MEM_IndexTable[]上のItemと指定されたItemが一致 */
			||(MEM_IndexTable[index_no1].Item == Item))			/* MEM_IndexTable[]上のNoと指定されたNoが一致 */
		   &&((MEM_IndexTable[index_no1].No	== No) || (No == MEM_ALL_NO))	/* MEM_IndexTable[]上のPageと指定されたPageが一致 */
		   &&((MEM_IndexTable[index_no1].BoxNumber == BoxNumber) || (BoxNumber == MEM_IGNORE_BOX_NUMBER)) )	{	/* BoxNumberも比較する様に変更 */
			flag = YES;												/* 消去原稿があるということです */
			start_block_no = MEM_IndexTable[index_no1].StartBlockNo;	/* 該当インデックスのStartBlockNoが消去開始ブロック指定データとなります */

			ClearIndex(index_no1);									/* 指定インデックスを消去します */

			/* 1999/08/27  NAGANOより 1999/10/21 Y.Murata
			 * このフラグの初期化が抜けてる～！
			 * このせいで、デゥアルオープン時の原稿消去がおかしくなる。インデックだけ消してＦＡＴを消さないことが起こってしまう。
			*/
			fat_delete = 1;
																	/* 二重定義しているインデックスが他にないか検索する */
			for (index_no2 = 0; index_no2 < MEM_INDEX_TABLE_MAX; index_no2++) {/* もう一度全インデックス・テーブル内を検索し二重インデックスを探す*/
				if ((MEM_IndexTable[index_no2].Item != SYS_MEM_FILE_EMPTY) &&/* MEM_IndexTable[]上のItemが空インデックスではなくて */
					(index_no1 != index_no2) &&
					(MEM_IndexTable[index_no2].StartBlockNo == start_block_no)) {/* 該当インデックスと同じStartBlockNoを持つインデックスを検索する */
																	/* 二重定義しているインデックスがあれば、そのインデックスもFATも消去しません */
					fat_delete = NO;								/* FAT消去 不許可 */
					break;											/* 二重インデックスがひとつでも見つかったら検索終了します */
				}
			}

			if (fat_delete == YES)									/* FAT消去不許可でなかったらFATを消去します */
				ClearFATArea(start_block_no);						/* 原稿の消去ROUTINEをCALLします */
			MEM_IndexTable[index_no1].Item = SYS_MEM_FILE_EMPTY;	/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */
		}
	}

	if (flag == NO) {												/* 消去原稿がなかったら */
		return ((UBYTE)MEM_NO_INDEX);						/* MEM_NO_INDEX を返します */
	}

	return ((UBYTE)MEM_OK);									/* MEM_OK を返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[インデックス毎の原稿の消去]
	function	:[
		蓄積途中の原稿の消去を行ないます
		指定された原稿が蓄積途中ならFATと共に消去します
		指定された原稿が蓄積途中でない又は、無かったなら指定原稿なしで返ります
	]
	return		:[
		MEM_OK					0	消去正常終了
		MEM_NO_INDEX		 0xFF	消去指定原稿なし
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[]
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/25]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_ClearBreak (struct MEM_IndexData_t *IndexP)		/* 消去原稿を指定します */
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */
	UBYTE flag;												/* 消去原稿の有無のflag */

	flag = NO;														/* 消去原稿なしに初期化 */
																	/* 全インデックス・テーブル上を検索し */
	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* 消去指定インデックスを確定します(蓄積中の原稿を対象にします) */
		if ((MEM_IndexTable[index_no].Item == (UBYTE)(IndexP -> Item | MEM_NOW_STORING)) &&	/* MEM_IndexTable[]上のItemが指定Itemと一致 */
			(MEM_IndexTable[index_no].No == IndexP -> No) &&		/* MEM_IndexTable[]上のNoが指定Noと一致 */
			((MEM_IndexTable[index_no].BoxNumber == IndexP -> BoxNumber) ||/* add 1997/03/13  By T.Yamaguchi */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER)) &&			/* add 1997/03/13  By T.Yamaguchi */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageが指定Pageと一致 */
			flag = YES;												/* 消去原稿あり */
			ClearIndexAndFATAreaAppointNo(index_no);				/* 指定及び該当インデックスとFATを消去します */
			break;
		}
	}

	if (flag == NO) {												/* 消去原稿なしなら */
		return ((UBYTE)MEM_NO_INDEX);						/* MEM_NO_INDEX を返します */
	}

	return ((UBYTE)MEM_OK);									/* 消去が終了したら MEM_OK を返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[停電検出後の処理]
	function	:[
		蓄積途中の原稿の消去を行ないます
		全インデックス内で蓄積途中のインデックスを検索します
		もし蓄積途中のインデックスがあれば、そのすべてをFATと共に消去します
	]
	return		:[
		MEM_NO_CLEAR_DOC		2	消去した原稿なし
		MEM_EXIST_CLEAR_DOC		3	消去した原稿あり
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[]
	]
	condition	:[なし]
	comment		:[
		電源投入時にCALLしてください
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/25]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_ClearPowerDown (void)
{
	/* 消去する/しないはDRAM BackUp仕様書を参照しﾌｧｲﾙ毎の管理も追加する事 */
	/* ｺﾏﾝﾄﾞﾌｧｲﾙとかの消去もここでしてしまいましょうか?? */
	UBYTE flag;											/* 消去原稿あり／なしのフラグ */
	UWORD index_no;										/* MEM_IndexTable[]内のポインタ */
	UWORD no;											/* MEM_IndexTable[]内のポインタ */

	flag = NO;														/* 消去原稿なしに初期化 */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブル内を全部検索して蓄積中の原稿を捜します */
		if ((MEM_IndexTable[index_no].Item & MEM_NOW_STORING) == MEM_NOW_STORING) {	/* 原稿種別が蓄積中か */
			flag = YES;												/* 消去原稿あり */
			ClearIndexAndFATAreaAppointNo(index_no);				/* 指定原稿の消去 */
		} else if ((MEM_IndexTable[index_no].Item & MEM_NOW_DELETING) == MEM_NOW_DELETING) {	/* 原稿種別が消去中ならば */
			for (no = 0; no < MEM_INDEX_TABLE_MAX; no++) {
				if (MEM_IndexTable[index_no].StartBlockNo == MEM_IndexTable[no].StartBlockNo) {
					flag = YES;
					MEM_IndexTable[index_no].Item = SYS_MEM_FILE_EMPTY;
					break;
				}
			}
			if (no < MEM_INDEX_TABLE_MAX) {
				;
			} else {
				flag = YES;												/* 消去原稿あり */
				ClearIndexAndFATAreaAppointNo(index_no);				/* 指定原稿の消去 */
			}
		}
	}

	if (flag == YES)												/* 消去原稿ありならば */
		return (MEM_EXIST_CLEAR_DOC);								/* MEM_EXIST_CLEAR_DOC を返します */

	return (MEM_NO_CLEAR_DOC);										/* MEM_NO_CLEAR_DOC を返します */
}


void ClearIndexAndFATAreaAppointNo (UWORD AppointIndexNo)	/* 消去原稿をｲﾝﾃﾞｯｸｽNo.で指定します */
{
	UWORD index_no;
	UWORD start_block_no;

	start_block_no = MEM_IndexTable[AppointIndexNo].StartBlockNo;
	MEM_TotalStoreBlockCounter++;
	ClearIndex(AppointIndexNo);										/* 指定インデックスを消去します */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {
		if ((start_block_no == MEM_IndexTable[index_no].StartBlockNo) &&
			(MEM_IndexTable[index_no].Item != SYS_MEM_FILE_EMPTY) && /* By S.Kawasaki 1996/08/23 */
			(AppointIndexNo != index_no)) {
			ClearIndex(index_no);									/* 該当インデックスを消去します */
		}
	}

	ClearFATArea(start_block_no);									/* 指定インデックスの使用FATエリアを消去します */

	MEM_IndexTable[AppointIndexNo].Item = SYS_MEM_FILE_EMPTY;		/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */
	if (index_no < MEM_INDEX_TABLE_MAX)
		MEM_IndexTable[index_no].Item = SYS_MEM_FILE_EMPTY;			/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */

	return;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定インデックス・テーブルの消去]
	function	:[
		指定されたMEM_IndexTable[指定No]の構成要素を初期化します
	]
	return		:[なし]
	common		:[
		struct IndexTableData_t MEM_IndexTable[]
	]
	condition	:[なし]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/25]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void ClearIndex (UWORD IndexNo)							/* 消去したいインデックスNoを指定します */
{
/*	MEM_IndexTable[IndexNo].Item = SYS_MEM_FILE_EMPTY;				/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */
	MEM_IndexTable[IndexNo].Item |= MEM_NOW_DELETING;				/* Itemを消去中ステータスに変更 */
	return;
}

#if 0 /* (PRO_F_CODE == ENABLE)MEM_ClearDocAndFATArea で吸収した 1997/03/11  By T.Yamaguchi */
///*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	module		:[ボックスの原稿毎の消去]
//	function	:[
//		1.
//	]
//	return		:[なし]
//	common		:[なし]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[MEM]
//	date		:[1999/01/24]
//	author		:[山口 哲治]
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//UBYTE MEM_ClearBoxDocAndFATArea (UBYTE Item,		/* 消去原稿の原稿種別を指定します */
//								  UWORD	 No,		/* 消去原稿のNoを指定します  MEM_ALL_NOの時は全ファイル消去 */
//								  UBYTE BoxNumber)	/* 消去原稿のBoxNumberを指定します */
//{
//	UBYTE flag;												/* 消去原稿 有/無 のフラグ */
//	UWORD index_no1;										/* MEM_IndexTable[]内のポインタ */
//	UWORD index_no2;										/* MEM_IndexTable[]内のポインタ */
//	UWORD start_block_no;									/* FAT消去のための消去開始ブロック指定データ */
//
//	flag = NO;														/* 消去原稿なしに初期化 */
//
//																	/* 全インデックス・テーブル上を検索し */
//	for (index_no1 = 0; index_no1 < MEM_INDEX_TABLE_MAX; index_no1++) {/* 消去を指定されたインデックスNoを確定する (蓄積中の原稿も対象にする) */
//		if (  ((MEM_IndexTable[index_no1].Item == (UBYTE)(Item | MEM_NOW_STORING))	/* MEM_IndexTable[]上のItemと指定されたItemが一致 */
//			 ||(MEM_IndexTable[index_no1].Item == Item))			/* MEM_IndexTable[]上のNoと指定されたNoが一致 */
//			&&((MEM_IndexTable[index_no1].No	  == No) || (No == MEM_ALL_NO))		/* MEM_IndexTable[]上のPageと指定されたPageが一致 */
//			&&(MEM_IndexTable[index_no1].BoxNumber == BoxNumber))	{
//			flag = YES;												/* 消去原稿あり */
//			start_block_no = MEM_IndexTable[index_no1].StartBlockNo;	/* 該当インデックスのStartBlockNoが消去開始ブロック指定データとなります */
//
//
//			ClearIndex(index_no1);									/* 該当インデックスを消去します */
//
//																	/* 二重定義しているインデックスが他にないか検索する */
//			for (index_no2 = 0; index_no2 < MEM_INDEX_TABLE_MAX; index_no2++) {/* もう一度全インデックス・テーブル内を検索し二重インデックスを探す*/
//				if ((MEM_IndexTable[index_no2].Item != SYS_MEM_FILE_EMPTY) &&/* MEM_IndexTable[]上のItemが空インデックスではなくて */
//					(index_no1 != index_no2) &&
//					(MEM_IndexTable[index_no2].StartBlockNo == start_block_no)) {/* 該当インデックスと同じStartBlockNoを持つインデックスを検索する */
//					ClearIndex(index_no2);							/* 二重定義しているインデックスが見つかったら、そのインデックスも消去します */
//					break;											/** 二重定義のみ有効(三重定義以上は無効)です */
//				}
//			}
//			ClearFATArea(start_block_no);							/* FATエリアの消去をします */
//
//			MEM_IndexTable[index_no1].Item = SYS_MEM_FILE_EMPTY;		/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */
//			if (index_no2 < MEM_INDEX_TABLE_MAX)
//				MEM_IndexTable[index_no2].Item = SYS_MEM_FILE_EMPTY;	/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */
//
//		}
//	}
//
//	if (flag == NO) {												/* 消去原稿がなかったなら
//		return ((UBYTE)MEM_NO_INDEX);								/* MEM_NO_INDEX を返します */
//	}
//
//	return ((UBYTE)MEM_OK);											/* MEM_OK を返します */
//}
#endif

#if (PRO_F_CODE == ENABLE)

 #if 0
///*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	module		:[ボックスの原稿毎の消去]
//	function	:[
//		1.
//	]
//	return		:[なし]
//	common		:[なし]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[MEM]
//	date		:[1997/01/24]
//	author		:[山口 哲治]
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//UBYTE MEM_ClearBoxDoc(UBYTE Item,		/* 消去原稿の原稿種別を指定します */
//					  UWORD No,			/* 消去原稿のNoを指定します */
//					  UBYTE BoxNumber)	/* 消去原稿のBoxNumberを指定します */
//{
//	UBYTE flag;												/* 消去原稿 有/無 のフラグ */
//	UBYTE fat_delete;										/* FAT消去 許可/不許可 のフラグ */
//	UWORD index_no1;										/* MEM_IndexTable[]内のポインタ */
//	UWORD index_no2;										/* MEM_IndexTable[]内のポインタ */
//	UWORD start_block_no;									/* FAT消去のための消去開始ブロック指定データ */
//
//	flag = NO;														/* 消去原稿なしに初期化 */
//	fat_delete = YES;												/* FAT消去許可に初期化 */
//
//	for (index_no1 = 0; index_no1 < MEM_INDEX_TABLE_MAX; index_no1++) {/* 全インデックス・テーブル上を検索し */
//		if (  (	  (MEM_IndexTable[index_no1].Item == (UBYTE)(Item | MEM_NOW_STORING))	/* 消去を指定されたインデックスNoを確定する (蓄積中の原稿も対象にする) */
//			   || (MEM_IndexTable[index_no1].Item == Item))			/* MEM_IndexTable[]上のItemと指定されたItemが一致 */
//			&&(MEM_IndexTable[index_no1].No	  == No)				/* MEM_IndexTable[]上のNoと指定されたNoが一致 */
//			&&(MEM_IndexTable[index_no1].BoxNumber == BoxNumber)) { /* MEM_IndexTable[]上のBoxNumberと指定されたBoxNumberが一致 */
//			flag = YES;												/* 消去原稿あり */
//			start_block_no = MEM_IndexTable[index_no1].StartBlockNo;	/* 該当インデックスのStartBlockNoが消去開始ブロック指定データとなります */
//
//			ClearIndex(index_no1);									/* 該当インデックスを消去します */
//
//																	/* 二重定義しているインデックスが他にないか検索する */
//			for (index_no2 = 0; index_no2 < MEM_INDEX_TABLE_MAX; index_no2++) {/* もう一度全インデックス・テーブル内を検索し二重インデックスを探す*/
//				if ((MEM_IndexTable[index_no2].Item != SYS_MEM_FILE_EMPTY) &&/* MEM_IndexTable[]上のItemが空インデックスではなくて */
//					(index_no1 != index_no2) &&
//					(MEM_IndexTable[index_no2].StartBlockNo == start_block_no)) {/* 該当インデックスと同じStartBlockNoを持つインデックスを検索する */
//																	/* 二重定義しているインデックスがあれば、そのインデックスもFATも消去しません */
//					fat_delete = NO;								/* FAT消去 不許可 */
//					break;											/** 二重定義のみ有効(三重定義以上は無効)です */
//				}
//			}
//			if (fat_delete == YES) {									/* FAT消去不許可でなかったらFATを消去します */
//				ClearFATArea(start_block_no);							/* FATエリアの消去をします */
//			}
//			MEM_IndexTable[index_no1].Item = SYS_MEM_FILE_EMPTY;		/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */
//		}
//	}
//
//	if (flag == NO) {												/* 消去原稿がなかったなら
//		return ((UBYTE)MEM_NO_INDEX);								/* MEM_NO_INDEX を返します */
//	}
//
//	return ((UBYTE)MEM_OK);											/* MEM_OK を返します */
//}
//
///*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	module		:[ボックス毎の原稿消去]
//	function	:[
//		1.
//	]
//	return		:[なし]
//	common		:[なし]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[MEM]
//	date		:[1999/01/24]
//	author		:[山口 哲治]
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//UBYTE MEM_ClearBoxAllDocAndFATArea (UBYTE Item,		/* 消去原稿の原稿種別を指定します */
//									UBYTE BoxNumber)	/* 消去原稿のBoxNumberを指定します */
//{
//	UBYTE flag;												/* 消去原稿 有/無 のフラグ */
//	UWORD index_no1;										/* MEM_IndexTable[]内のポインタ */
//	UWORD index_no2;										/* MEM_IndexTable[]内のポインタ */
//	UWORD start_block_no;									/* FAT消去のための消去開始ブロック指定データ */
//
//	flag = NO;														/* 消去原稿なしに初期化 */
//
//																	/* 全インデックス・テーブル上を検索し */
//	for (index_no1 = 0; index_no1 < MEM_INDEX_TABLE_MAX; index_no1++) {/* 消去を指定されたインデックスNoを確定する (蓄積中の原稿も対象にする) */
//		if (  ((MEM_IndexTable[index_no1].Item == (UBYTE)(Item | MEM_NOW_STORING))	/* MEM_IndexTable[]上のItemと指定されたItemが一致 */
//			 ||(MEM_IndexTable[index_no1].Item == Item))			/* MEM_IndexTable[]上のNoと指定されたNoが一致 */
//			&&(MEM_IndexTable[index_no1].BoxNumber == BoxNumber))	{
//			flag = YES;												/* 消去原稿あり */
//			start_block_no = MEM_IndexTable[index_no1].StartBlockNo;	/* 該当インデックスのStartBlockNoが消去開始ブロック指定データとなります */
//
//			ClearIndex(index_no1);									/* 該当インデックスを消去します */
//
//																	/* 二重定義しているインデックスが他にないか検索する */
//			for (index_no2 = 0; index_no2 < MEM_INDEX_TABLE_MAX; index_no2++) {/* もう一度全インデックス・テーブル内を検索し二重インデックスを探す*/
//				if ((MEM_IndexTable[index_no2].Item != SYS_MEM_FILE_EMPTY) &&/* MEM_IndexTable[]上のItemが空インデックスではなくて */
//					(index_no1 != index_no2) &&
//					(MEM_IndexTable[index_no2].StartBlockNo == start_block_no)) {/* 該当インデックスと同じStartBlockNoを持つインデックスを検索する */
//					ClearIndex(index_no2);							/* 二重定義しているインデックスが見つかったら、そのインデックスも消去します */
//					break;											/** 二重定義のみ有効(三重定義以上は無効)です */
//				}
//			}
//			ClearFATArea(start_block_no);							/* FATエリアの消去をします */
//
//			MEM_IndexTable[index_no1].Item = SYS_MEM_FILE_EMPTY;		/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */
//			if (index_no2 < MEM_INDEX_TABLE_MAX) {
//				MEM_IndexTable[index_no2].Item = SYS_MEM_FILE_EMPTY;	/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */
//			}
//		}
//	}
//
//	if (flag == NO) {												/* 消去原稿がなかったなら
//		return ((UBYTE)MEM_NO_INDEX);								/* MEM_NO_INDEX を返します */
//	}
//
//	return ((UBYTE)MEM_OK);											/* MEM_OK を返します */
//}
 #endif

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ボックス毎の原稿消去(指定原稿以外 )	]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1999/01/24]
	author		:[山口 哲治]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_ClearBoxNoAppintDoc(UBYTE Item,		/* 消去原稿の原稿種別を指定します */
							UBYTE BoxNumber,	/* 消去原稿のBoxNumberを指定します */
							UWORD No)			/* 消去しない原稿のNoを指定します */
									
{
	UBYTE flag;												/* 消去原稿 有/無 のフラグ */
	UWORD index_no1;										/* MEM_IndexTable[]内のポインタ */
	UWORD index_no2;										/* MEM_IndexTable[]内のポインタ */
	UWORD start_block_no;									/* FAT消去のための消去開始ブロック指定データ */

	flag = NO;														/* 消去原稿なしに初期化 */

																	/* 全インデックス・テーブル上を検索し */
	for (index_no1 = 0; index_no1 < MEM_INDEX_TABLE_MAX; index_no1++) {/* 消去を指定されたインデックスNoを確定する (蓄積中の原稿も対象にする) */
		if (  ((MEM_IndexTable[index_no1].Item == (UBYTE)(Item | MEM_NOW_STORING))	/* MEM_IndexTable[]上のItemと指定されたItemが一致 */
			 ||(MEM_IndexTable[index_no1].Item == Item))			/* MEM_IndexTable[]上のNoと指定されたNoが一致 */
			&&(MEM_IndexTable[index_no1].BoxNumber == BoxNumber)
			&&(MEM_IndexTable[index_no1].No != No))	{	/* 指定原稿でない */
			flag = YES;												/* 消去原稿あり */
			start_block_no = MEM_IndexTable[index_no1].StartBlockNo;	/* 該当インデックスのStartBlockNoが消去開始ブロック指定データとなります */

			ClearIndex(index_no1);									/* 該当インデックスを消去します */

																	/* 二重定義しているインデックスが他にないか検索する */
			for (index_no2 = 0; index_no2 < MEM_INDEX_TABLE_MAX; index_no2++) {/* もう一度全インデックス・テーブル内を検索し二重インデックスを探す*/
				if ((MEM_IndexTable[index_no2].Item != SYS_MEM_FILE_EMPTY) &&/* MEM_IndexTable[]上のItemが空インデックスではなくて */
					(index_no1 != index_no2) &&
					(MEM_IndexTable[index_no2].StartBlockNo == start_block_no)) {/* 該当インデックスと同じStartBlockNoを持つインデックスを検索する */
					ClearIndex(index_no2);							/* 二重定義しているインデックスが見つかったら、そのインデックスも消去します */
					break;											/** 二重定義のみ有効(三重定義以上は無効)です */
				}
			}
			ClearFATArea(start_block_no);							/* FATエリアの消去をします */

			MEM_IndexTable[index_no1].Item = SYS_MEM_FILE_EMPTY;		/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */
			if (index_no2 < MEM_INDEX_TABLE_MAX) {
				MEM_IndexTable[index_no2].Item = SYS_MEM_FILE_EMPTY;	/* Itemの初期値 (SYS_MEM_FILE_EMPTY) */
			}
		}
	}

	if (flag == NO) {												/* 消去原稿がなかったなら
		return ((UBYTE)MEM_NO_INDEX);								/* MEM_NO_INDEX を返します */
	}

	return ((UBYTE)MEM_OK);											/* MEM_OK を返します */
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[原稿番号の変換(指定原稿番号、変換原稿番号 )]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1999/01/24]
	author		:[山口 哲治]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_IndexConvert(UBYTE Item,			/* 変換する原稿の原稿種別を指定します */
						UBYTE BoxNumber,	/* 変換する原稿のBoxNumberを指定します */
						UWORD No,			/* 変換する原稿のNoを指定します */
						UWORD convert_no)	/* 変換後の原稿のNoを指定します */
{
	UBYTE flag;												/* 消去原稿 有/無 のフラグ */
	UWORD index_no1;										/* MEM_IndexTable[]内のポインタ */

	flag = NO;														/* 消去原稿なしに初期化 */

																	/* 全インデックス・テーブル上を検索し */
	for (index_no1 = 0; index_no1 < MEM_INDEX_TABLE_MAX; index_no1++) {/* 消去を指定されたインデックスNoを確定する (蓄積中の原稿も対象にする) */
		if (  ((MEM_IndexTable[index_no1].Item == (UBYTE)(Item | MEM_NOW_STORING))	/* MEM_IndexTable[]上のItemと指定されたItemが一致 */
			 ||(MEM_IndexTable[index_no1].Item == Item))			/* MEM_IndexTable[]上のNoと指定されたNoが一致 */
			&&(MEM_IndexTable[index_no1].BoxNumber == BoxNumber)
			&&(MEM_IndexTable[index_no1].No == No))	{		/* 指定原稿である */
			flag = YES;												/* 消去原稿あり */

			MEM_IndexTable[index_no1].No = convert_no;		/* Noを変更 */

		}
	}

	if (flag == NO) {						/* 変換する原稿がなかったなら
		return ((UBYTE)MEM_NO_INDEX);		/* MEM_NO_INDEX を返します */
	}

	return ((UBYTE)MEM_OK);					/* MEM_OK を返します */
}

#endif


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[MEM_PC_BUG]
	function	:[
		ＰＣファイルの蓄積途中の原稿の消去を行ないます
		全インデックス内でＰＣファイルの蓄積途中のインデックスを検索します
		もしＰＣファイルの蓄積途中のインデックスがあれば、そのすべてをFATと共に消去します
	]
	return		:[
		MEM_NO_CLEAR_DOC		2	消去した原稿なし
		MEM_EXIST_CLEAR_DOC		3	消去した原稿あり
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[MEM]
	date		:[1998/04/08]
	author		:[村田]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_ClearStroingPCPrintFile (void)
{
	UBYTE flag;				/* 消去原稿あり／なしのフラグ */
	UWORD  index_no;		/* MEM_IndexTable[]内のポインタ */

	flag = NO;				/* 消去原稿なしに初期化 */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブル内を全部検索して蓄積中の原稿を捜します */
		if (MEM_IndexTable[index_no].Item == (SYS_MEM_PC_RX_FILE | MEM_NOW_STORING)) {
			flag = YES;												/* 消去原稿あり */
			ClearIndexAndFATAreaAppointNo(index_no);				/* 指定原稿の消去 */
		}
	}

	if (flag == YES) {												/* 消去原稿ありならば */
		return (MEM_EXIST_CLEAR_DOC);								/* MEM_EXIST_CLEAR_DOC を返します */
	}

	return (MEM_NO_CLEAR_DOC);										/* MEM_NO_CLEAR_DOC を返します */
}

