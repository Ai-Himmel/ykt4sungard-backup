/************************************************************************
*				By : NOBUKO
*			  Date : Wed 22 Dec. 1993 (\SRC\RICE\SRC\MEMCHECK.C)
*		 Copy Date : Tue 12 Sep. 1995
*		           : 1996/10/18 From \src\kobe\anzu\src\ By M.Kotani
*		 File Name : MEMCHECK.C
*	   Module Name :
*		1. UBYTE MEM_CheckStoreCode (struct MEM_IndexData_t *IndexP)
*		2. UBYTE MEM_CheckStoreMode (struct MEM_IndexData_t *IndexP)
*		3. UBYTE MEM_CheckStoreSize (struct MEM_IndexData_t *IndexP)
*		4. UBYTE MEM_CheckMilliInch (struct MEM_IndexData_t *IndexP)
*		5. UWORD MEM_CheckStoreLineCount (struct MEM_IndexData_t *IndexP)
*		6. UWORD MEM_CheckIndexNo (struct MEM_IndexData_t *IndexP)
*		7. UWORD MEM_CheckMostSmallPage (UBYTE Item, UWORD	 No)
*		8. UBYTE MEM_CheckStoreDoc(UBYTE Item)
*		9. UBYTE MEM_CheckUseIndex(void)
*	   10. UBYTE MEM_CheckStoreArea(struct MEM_IndexData_t *IndexP)
*	   11. UBYTE MEM_CheckStoreCassette (struct MEM_IndexData_t *IndexP)
************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\mon_pro.h"	/* 1997/12/16 Y.M */
#include "\src\atlanta\sh7043\define\def_semn.h"	/* 1997/12/16 Y.M */
#include "\src\atlanta\sh7043\ext_v\extv_sem.h"	/* 1997/12/16 Y.M */
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\ext_v\mem_data.h"
#include "\src\atlanta\ext_v\bkupram.h"

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定蓄積原稿の蓄積符号を取り出します]
	function	:[
		引数でItem、No、Pageをセットしたデータのポインタを渡します
		Item、No、Pageをもとに該当するインデックスを探します
		該当インデックスのCodeを返します
	]
	return		:[
		SYS_IMAGE_DATA			0
		SYS_MH_CODE				1	MH符号
		SYS_MR_CODE				2	MR符号
		SYS_MMR_CODE			3	MMR符号
		SYS_MG3_CODE			4	MG3符号
		MEM_NO_INDEX		 0xFF	該当インデックスなし
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[]
	]
	condition	:[
		蓄積の終了している原稿にのみ有効です
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/12 Y.Murata for KAKI */

 #if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UBYTE MEM_CheckStoreCodeFlsRom (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定します */
 #else
UBYTE MEM_CheckStoreCode (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定します */
 #endif
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタに使用します */
	struct IndexTableData_t *index_table;

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* 全インデックス・テーブルの中を検索し、該当インデックスを確定します */
		if (((MEM_IndexTable[index_no].Item & ~MEM_NOW_STORING) == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			 (MEM_IndexTable[index_no].No   == IndexP -> No)	  &&	/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
			((MEM_IndexTable[index_no].BoxNumber   == IndexP -> BoxNumber) ||	/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
			return (MEM_IndexTable[index_no].Code);					/* 該当 MEM_IndexTable[]上の蓄積Codeを返します */
		}
	}

																	/* ここまでやって来たということは該当インデックスがなかったということです */
	return ((UBYTE)MEM_NO_INDEX);							/* MEM_NO_INDEX を返します */
}


#else

 #if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UBYTE MEM_CheckStoreCodeFlsRom (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定します */
 #else
UBYTE MEM_CheckStoreCode (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定します */
 #endif
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタに使用します */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* 全インデックス・テーブルの中を検索し、該当インデックスを確定します */
		if ((MEM_IndexTable[index_no].Item == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&	/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
/* #if (PRO_F_CODE == ENABLE) */
			((MEM_IndexTable[index_no].BoxNumber   == IndexP -> BoxNumber) ||	/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
/* #endif */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
			return (MEM_IndexTable[index_no].Code);					/* 該当 MEM_IndexTable[]上の蓄積Codeを返します */
		}
	}

																	/* ここまでやって来たということは該当インデックスがなかったということです */
	return ((UBYTE)MEM_NO_INDEX);							/* MEM_NO_INDEX を返します */
}
#endif /* if (PRO_QUICK_TX_TEST == ENABLE) */


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[蓄積原稿の蓄積モードを調べます]
	function	:[
		引数でItem、No、Pageをセットしたデータのポインタを渡します
		Item、No、Pageをもとに該当するインデックスを探します
		該当インデックスのModeを返します
	]
	return		:[
		SYS_NORMAL				0	普通
		SYS_FINE				1	高画質
		SYS_SFINE				2	超高画質
		SYS_HFINE				3	超超高画質 (桐のみ)
		SYS_GRAY16				4	16階調
		SYS_GRAY16_SEP			5	16階調、像域分離
		SYS_GRAY64				6	64階調
		SYS_GRAY64_SEP			7	64階調、像域分離
		MEM_NO_INDEX		 0xFF	該当インデックスなし
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[]
	]
	condition	:[
		蓄積の終了している原稿にのみ有効です
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/12 Y.Murata for KAKI */

 #if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UBYTE MEM_CheckStoreModeFlsRom (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
 #else
UBYTE MEM_CheckStoreMode (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
 #endif
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブルの中を検索し、該当インデックスを確定します */
		if (((MEM_IndexTable[index_no].Item & ~MEM_NOW_STORING) == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			 (MEM_IndexTable[index_no].No   == IndexP -> No)	  &&	/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
			((MEM_IndexTable[index_no].BoxNumber   == IndexP -> BoxNumber) ||	/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
			return (MEM_IndexTable[index_no].Mode);					/* 該当MEM_IndexTable[]上のModeを返します */
		}
	}

																	/* ここまでやって来たということは該当インデックスがなかったということです */
	return ((UBYTE)MEM_NO_INDEX);							/* MEM_NO_INDEX を返します */
}

#else

 #if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UBYTE MEM_CheckStoreModeFlsRom (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
 #else
UBYTE MEM_CheckStoreMode (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
 #endif
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブルの中を検索し、該当インデックスを確定します */
		if ((MEM_IndexTable[index_no].Item == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&	/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
/* #if (PRO_F_CODE == ENABLE) */
			((MEM_IndexTable[index_no].BoxNumber   == IndexP -> BoxNumber) ||	/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
/* #endif */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
			return (MEM_IndexTable[index_no].Mode);					/* 該当MEM_IndexTable[]上のModeを返します */
		}
	}

																	/* ここまでやって来たということは該当インデックスがなかったということです */
	return ((UBYTE)MEM_NO_INDEX);							/* MEM_NO_INDEX を返します */
}
#endif /* if (PRO_QUICK_TX_TEST == ENABLE) */


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[蓄積原稿の原稿幅を調べます]
	function	:[
		引数でItem、No、Pageをセットしたデータのポインタを渡します
		Item、No、Pageをもとに該当するインデックスを探します
		該当インデックスのSizeを返します
	]
	return		:[
		SYS_DOCUMENT_A4_SIZE	0	A4幅 (A5横､A4縦､LETTER､LEAGAL)
		SYS_DOCUMENT_B4_SIZE	1	B4幅 (B5横､B4縦)
		SYS_DOCUMENT_A3_SIZE	2	A3幅 (A4横､A3縦)
		MEM_NO_INDEX		 0xFF	該当インデックスなし
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[]
	]
	condition	:[
		蓄積の終了している原稿にのみ有効です
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/12 Y.Murata for KAKI */

 #if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UBYTE MEM_CheckStoreSizeFlsRom (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
 #else
UBYTE MEM_CheckStoreSize (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
 #endif
{
	UWORD index_no;		/* MEM_IndexTable[]内のポインタ */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* 全インデックス・テーブルの中を検索し、該当するインデックスを確定します */
		if (((MEM_IndexTable[index_no].Item & ~MEM_NOW_STORING) == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&	/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
			((MEM_IndexTable[index_no].BoxNumber   == IndexP -> BoxNumber) ||	/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
			return (UBYTE)(MEM_IndexTable[index_no].Size & ~MEM_MILLI_BIT);/* 該当MEM_IndexTable[]上のSizeを返します */
		}
	}

																	/* ここまでやって来たということは該当インデックスがなかったということです */
	return ((UBYTE)MEM_NO_INDEX);							/* MEM_NO_INDEX を返します */
}

#else

 #if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UBYTE MEM_CheckStoreSizeFlsRom (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
 #else
UBYTE MEM_CheckStoreSize (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
 #endif
{
	UWORD index_no;		/* MEM_IndexTable[]内のポインタ */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* 全インデックス・テーブルの中を検索し、該当するインデックスを確定します */
		if ((MEM_IndexTable[index_no].Item == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&	/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
/* #if (PRO_F_CODE == ENABLE) */
			((MEM_IndexTable[index_no].BoxNumber   == IndexP -> BoxNumber) ||	/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
/* #endif */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
			return (UBYTE)(MEM_IndexTable[index_no].Size & ~MEM_MILLI_BIT);/* 該当MEM_IndexTable[]上のSizeを返します */
		}
	}

																	/* ここまでやって来たということは該当インデックスがなかったということです */
	return ((UBYTE)MEM_NO_INDEX);							/* MEM_NO_INDEX を返します */
}
#endif /* if (PRO_QUICK_TX_TEST == ENABLE) */

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[蓄積原稿のミリ系／インチ系を調べます]
	function	:[
		引数でItem、No、Pageをセットしたデータのポインタを渡します
		Item、No、Pageをもとに該当するインデックスを探します
		該当インデックスのミリ系／インチ系を返します
	]
	return		:[
		MEM_INCH_MODE		   0		インチ系
		MEM_MILLI_MODE		   1		ミリ系
		MEM_NO_INDEX		0xFF		該当インデックスなし
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[]
	]
	condition	:[
		蓄積の終了している原稿にのみ有効です
	]
	comment		:[
		桐のみ戻り値にインチ系が加わります
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/06/08]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_CheckMilliInch (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブルの中を検索し、該当するインデックスを確定します */
		if ((MEM_IndexTable[index_no].Item == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&	/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
/* #if (PRO_F_CODE == ENABLE) */
			((MEM_IndexTable[index_no].BoxNumber == IndexP -> BoxNumber) ||	/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
/* #endif */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
			if ((MEM_IndexTable[index_no].Size & MEM_MILLI_BIT) == MEM_MILLI_BIT) {	/* 該当MEM_IndexTable[].Size上のInchBitをみます */
				return ((UBYTE)MEM_MILLI_MODE);
			}
			else
				return ((UBYTE)MEM_INCH_MODE);
		}
	}
																	/* ここまでやってきたということは該当インデックスがなかったということです */
	return ((UBYTE)MEM_NO_INDEX);							/* MEM_NO_INDEX を返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[蓄積原稿の蓄積ライン数を調べます]
	function	:[
		引数でItem、No、Pageをセットしたデータのポインタを渡します
		Item、No、Pageをもとに該当するインデックスを探します
		該当インデックスのLineCountを返します
	]
	return		:[
		0 ～ 4332(A3 400dpi)
		MEM_NO_INDEX		0xFFFF		該当インデックスなし
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[]
	]
	condition	:[
		蓄積の終了している原稿にのみ有効です
	]
	comment		:[
		戻値 0の場合は、”該当インデックスなし”の扱いにしてください
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_CheckStoreLineCount (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブルの中を検索し、該当するインデックスを確定します */
		if ((MEM_IndexTable[index_no].Item == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&	/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
/* #if (PRO_F_CODE == ENABLE) */
			((MEM_IndexTable[index_no].BoxNumber == IndexP -> BoxNumber) ||	/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
/* #endif */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
			return (MEM_IndexTable[index_no].LineCount);			/* 該当MEM_IndexTable[]上のLineCountを返します */
		}
	}

																	/* ここまでやって来たということは該当インデックスがなかったということです */
	return (MEM_NO_INDEX);											/* MEM_NO_INDEX を返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[蓄積原稿のインデックスNo.を調べます]
	function	:[
		引数でItem、No、Pageをセットしたデータのポインタを渡します
		Item、No、Pageをもとに該当するインデックスを探します
		該当インデックスのIndexNoを返します
	]
	return		:[
		IndexNo					0 ～ MEM_INDEX_TABLE_MAX
		MEM_NO_INDEX			0xFFFF		該当インデックスなし
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[]
	]
	condition	:[
		蓄積の終了している原稿にのみ有効です
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/14 Y.Murata for KAKI */

UWORD MEM_CheckIndexNo (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */
	UBYTE debug;
	UBYTE dummy;
	struct IndexTableData_t *index_table;

	debug = 1;
	if (debug) {
		dummy++;
		dummy++;
		dummy++;
		dummy++;
		for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブルの中を検索し、該当するインデックスを確定します */
			if (((MEM_IndexTable[index_no].Item & ~MEM_NOW_STORING) == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
				(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&	/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
				((MEM_IndexTable[index_no].BoxNumber == IndexP -> BoxNumber) ||	/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
				 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
				(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
				return (index_no);										/* 該当MEM_IndexTable[]上のインデックスNo.を返します */
			}
		}
		dummy++;
		dummy++;
		dummy++;
		dummy++;
	}
	else {
		dummy++;
		dummy++;
		dummy++;
		dummy++;
		index_table = &MEM_IndexTable[0];
		for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブルの中を検索し、該当するインデックスを確定します */
			if (((index_table->Item & ~MEM_NOW_STORING) == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
				(index_table->No   == IndexP -> No)	  &&	/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
				((index_table->BoxNumber == IndexP -> BoxNumber) ||	/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
				 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
				(index_table->Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
				return (index_no);										/* 該当MEM_IndexTable[]上のインデックスNo.を返します */
			}
		}
		dummy++;
		dummy++;
		dummy++;
		dummy++;
	}
																	/* ここまでやって来たということは該当インデックスがなかったということです */
	return (MEM_NO_INDEX);											/* MEM_NO_INDEX を返します */
}

#else

UWORD MEM_CheckIndexNo (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */


	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブルの中を検索し、該当するインデックスを確定します */
		if ((MEM_IndexTable[index_no].Item == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&	/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
/* #if (PRO_F_CODE == ENABLE) */
			((MEM_IndexTable[index_no].BoxNumber == IndexP -> BoxNumber) ||	/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
/* #endif */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
			return (index_no);										/* 該当MEM_IndexTable[]上のインデックスNo.を返します */
		}
	}

																	/* ここまでやって来たということは該当インデックスがなかったということです */
	return (MEM_NO_INDEX);											/* MEM_NO_INDEX を返します */
}

#endif /* if (PRO_QUICK_TX_TEST == ENABLE) */


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[蓄積原稿の最小ページを調べます]
	function	:[
		引数でItem、No、Pageをセットしたデータのポインタを渡します
		Item、No、Pageをもとに該当するインデックスを探します
		該当インデックスの最小ページを返します
	]
	return		:[
		ページ					0 ～ MEM_INDEX_TABLE_MAX
		MEM_NO_INDEX			0xFFFF		該当インデックスなし
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[]
	]
	condition	:[
		蓄積の終了している原稿にのみ有効です
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_CheckMostSmallPage (UBYTE Item,		/* 原稿指定のための原稿種別 */
							  UWORD	No)			/* 原稿指定のためのインデックス・テーブル上の No. */
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */
	UWORD page;												/* ページ数 */

	page = 0;														/* TEMPのページ数の初期化 */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* 全インデックス・テーブルの中を検索し、該当インデックスのページ数を調べます */
		if ((MEM_IndexTable[index_no].Item == Item) &&				/* MEM_IndexTable[]上のItemと指定されたのItemが一致していて */
			(MEM_IndexTable[index_no].No   == No)) {				/* MEM_IndexTable[]上のNoと指定されたのNoが一致していたら */
																	/* 最小ページの判断に入ります */
			if ((page > MEM_IndexTable[index_no].Page) ||			/* インデックスのページ数がTEMP上のページ数よりも小さいか */
				(page == 0)) {										/* TEMP上にページ数がコピーされていない場合は */
				page = MEM_IndexTable[index_no].Page;				/* TEMP上にインデックス上のページ数をコピーします */
			}
			if (page == 1) {										/* TEMP上のページ数が 1ページの場合は */
				return (page);										/* 無条件でページ数を返します */
			}
		}
	}
																	/* 全インデックス・テーブルの検索終了後の処理に入ります */
	if (page != 0) {												/* TEMP上のページ数が 0ページ以上(該当インデックスあり)ならば */
		return (page);												/* 最小ページ数を返します */
	}
																	/* ここまでやって来たということは該当インデックスがなかったということです */
	return (MEM_NO_INDEX);											/* MEM_NO_INDEX を返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定されたItemの原稿が蓄積されているかを調べます]
	function	:[
		引数でItemを渡します
		Itemをもとに該当するインデックスを探します
		該当インデックスの有無を返します
	]
	return		:[
		MEM_OK					0			該当原稿あり
		MEM_NO_INDEX			0xFFFF		該当原稿なし
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[]
	]
	condition	:[
		蓄積の終了している原稿にのみ有効です
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_CheckStoreDoc(UBYTE Item)
{
	UWORD index_no;

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {
		if (MEM_IndexTable[index_no].Item == Item) {
			return ((UBYTE)MEM_OK);
		}
	}
	return ((UBYTE)MEM_NO_INDEX);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[何か原稿が蓄積されているかを調べます]
	function	:[
		ItemがMEM_NO_INDEX以外のインデックスを探します
		該当インデックスがあればwhile()ループからすぐ抜けてMEM_OKを返します
		全インデックステーブル上を検索しおわっても蓄積原稿がなかったらMEM_NO_INDEXを返します
	]
	return		:[
		MEM_OK					0			蓄積原稿あり
		MEM_NO_INDEX			0xFFFF		蓄積原稿なし
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[]
	]
	condition	:[
		なし
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_CheckUseIndex(void)
{
	UWORD index_no;

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {
		if ((MEM_IndexTable[index_no].Item != SYS_MEM_FILE_EMPTY) &&
			((MEM_IndexTable[index_no].Item & MEM_NOW_DELETING) == 0)) {
			return ((UBYTE)MEM_OK);		/* MEM_OK == 0 */
		}
	}
	return ((UBYTE)MEM_NO_INDEX);		/* MEM_NO_INDEX == 0xFF */
}

#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/09/04 */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[蓄積原稿のデータサイズを調べます]
	function	:[
		引数でItem、No、Pageをセットしたデータのポインタを渡します
		Item、No、Pageをもとに該当するインデックスを探します
		該当インデックスのAreを返します
	]
	return		:[
		SYS_A5_PAPER		0			Ａ５縦
		SYS_LT_PAPER		1			レター縦
		SYS_A4_PAPER		2			Ａ４縦
		SYS_LG_PAPER		3			リーガル縦
		SYS_B5R_PAPER		4			ＪＩＳ Ｂ５横
		SYS_B4_PAPER		5			ＪＩＳ Ｂ４縦
		SYS_A3_PAPER		6			Ａ３縦
		SYS_A4R_PAPER		7			Ａ４横
		SYS_LTR_PAPER		8			レター横
		SYS_F4_PAPER		9			Ｆ４縦
		SYS_A5R_PAPER		10			Ａ５横
		SYS_POST_PAPER		11			はがき縦
		SYS_LD_PAPER		12			レジャー縦
		SYS_GLTR_PAPER		13			ガバメント・レター横
		SYS_EXER_PAPER		14			エグゼクティブ横
		SYS_HLTR_PAPER		15			ハーフレター横   added by honda 1997/10/04 POPLAR_B USA,GBR
		SYS_INVR_PAPER		15			インボイス横
		SYS_GLT_PAPER		17			ガバメントレター縦
		SYS_CARD_PAPER		18			カードストック紙
		SYS_EXE_PAPER		19			エグゼクティブ縦
		SYS_B5_PAPER		20			ＪＩＳ Ｂ５縦
		SYS_C5_PAPER		21			Ｃ５縦
		SYS_HLT_PAPER		22			ハーフ・レター縦
		SYS_INV_PAPER		23			インボイス縦
		SYS_B6_PAPER		24			ＪＩＳ Ｂ６縦
		SYS_DL_PAPER		25			ＤＬ縦
		SYS_CM10_PAPER		26			コマーシャル１０縦
		SYS_A6_PAPER		27			Ａ６縦
		SYS_MNC_PAPER		28			モナーク縦
		SYS_35_PAPER		29			３”×５”縦
		MEM_NO_INDEX		0xFF		該当インデックスなし
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[]
	]
	condition	:[
		蓄積の終了している原稿にのみ有効です
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1996/08/23]
	author		:[宮崎仁一]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_CheckStoreArea (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
{
	UWORD index_no;		/* MEM_IndexTable[]内のポインタ */

	/* 全インデックス・テーブルの中を検索し、該当するインデックスを確定します */
	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {
		if ((MEM_IndexTable[index_no].Item == IndexP -> Item) &&
			(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&
/* #if (PRO_F_CODE == ENABLE) */
			((MEM_IndexTable[index_no].BoxNumber == IndexP -> BoxNumber) ||	/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
/* #endif */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {
			return (UBYTE)(MEM_IndexTable[index_no].Area & ~MEM_MILLI_BIT);
		}
	}

	/* ここまでやって来たということは該当インデックスがなかったということです */
	return ((UBYTE)MEM_NO_INDEX);							/* MEM_NO_INDEX を返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[蓄積原稿をプリントするカセットを調べます]
	function	:[
		引数でItem、No、Pageをセットしたデータのポインタを渡します
		Item、No、Pageをもとに該当するインデックスを探します
		該当インデックスのAreを返します
	]
	return		:[
		SYS_AUTO_CASSETTE		0		自動選択
		SYS_UPPER_CASSETTE		1		上段カセット(手差し)選択
		SYS_LOWER_CASSETTE		2		下段カセット選択
		MEM_NO_INDEX			0xFF	該当インデックスなし
	]
	common		:[
		struct IndexTableData_t MEM_IndexTable[]
	]
	condition	:[
		蓄積の終了している原稿にのみ有効です
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1996/08/23]
	author		:[宮崎仁一]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_CheckStoreCassette (struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
{
	UWORD index_no;		/* MEM_IndexTable[]内のポインタ */

	/* 全インデックス・テーブルの中を検索し、該当するインデックスを確定します */
	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {
		if ((MEM_IndexTable[index_no].Item == IndexP -> Item) &&
			(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&
/* #if (PRO_F_CODE == ENABLE) */
			((MEM_IndexTable[index_no].BoxNumber == IndexP -> BoxNumber) ||	/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
/* #endif */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {
			return (UBYTE)(MEM_IndexTable[index_no].Cassette & ~MEM_MILLI_BIT);
		}
	}

	/* ここまでやって来たということは該当インデックスがなかったということです */
	return ((UBYTE)MEM_NO_INDEX);							/* MEM_NO_INDEX を返します */
}
#endif

#if (PRO_FBS == ENABLE)	/* M.Tachiban 1997/04/15 */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[蓄積原稿の蓄積モードを調べます]
	function	:[
		引数でItem、No、Pageをセットしたデータのポインタを渡します
		Item、No、Pageをもとに該当するインデックスを探します
		該当インデックスのModeを返します
	]
	return		:[
		SYS_NORMAL				0	普通
		SYS_FINE				1	高画質
		SYS_SFINE				2	超高画質
		SYS_HFINE				3	超超高画質 (桐のみ)
		SYS_GRAY16				4	16階調
		SYS_GRAY16_SEP			5	16階調、像域分離
		SYS_GRAY64				6	64階調
		SYS_GRAY64_SEP			7	64階調、像域分離
		MEM_NO_INDEX		 0xFF	該当インデックスなし
	]
	common		:[
		struct IndexTableData MEM_IndexTable[]
	]
	condition	:[
		蓄積中、蓄積の終了している原稿に有効です
	]
	comment		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[MEM]
	date		:[1993/12/22,1996/10/25]
	author		:[NOBUKO,吉川弘康]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_FCOT_CheckStoreMode(struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */
	struct IndexTableData_t *index_ptr;

	index_ptr = &MEM_IndexTable[0];
	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++, index_ptr++) {/* インデックス・テーブルの中を検索し、該当インデックスを確定します */
		if (((UBYTE)(index_ptr->Item & ~MEM_NOW_STORING) == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			(index_ptr->No   == IndexP -> No)   &&								/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
/* #if (PRO_F_CODE == ENABLE) */
			((index_ptr->BoxNumber == IndexP -> BoxNumber) ||					/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
/* #endif */
			(index_ptr->Page == IndexP -> Page)) {			/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
			return (index_ptr->Mode);						/* 該当MEM_IndexTable[]上のModeを返します */
		}
	}
	return ((UBYTE)MEM_NO_INDEX);							/* MEM_NO_INDEX を返します */
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[蓄積原稿の原稿幅を調べます]
	function	:[
		引数でItem、No、Pageをセットしたデータのポインタを渡します
		Item、No、Pageをもとに該当するインデックスを探します
		該当インデックスのSizeを返します
	]
	return		:[
		SYS_DOCUMENT_A4_SIZE	0	A4幅 (A5横､A4縦､LETTER､LEAGAL)
		SYS_DOCUMENT_B4_SIZE	1	B4幅 (B5横､B4縦)
		SYS_DOCUMENT_A3_SIZE	2	A3幅 (A4横､A3縦)
		MEM_NO_INDEX		 0xFF	該当インデックスなし
	]
	common		:[
		struct IndexTableData MEM_IndexTable[]
	]
	condition	:[
		蓄積中、蓄積の終了している原稿に有効です
	]
	comment		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[MEM]
	date		:[1993/12/22,1996/10/25]
	author		:[NOBUKO,吉川弘康]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_FCOT_CheckStoreSize(struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
{
	UWORD index_no;		/* MEM_IndexTable[]内のポインタ */
	struct IndexTableData_t *index_ptr;

	index_ptr = &MEM_IndexTable[0];
	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++, index_ptr++) {/* インデックス・テーブルの中を検索し、該当インデックスを確定します */
		if (((UBYTE)(index_ptr->Item & ~MEM_NOW_STORING) == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			(index_ptr->No   == IndexP -> No)   &&								/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
/* #if (PRO_F_CODE == ENABLE) */
			((index_ptr->BoxNumber == IndexP -> BoxNumber) ||					/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
/* #endif */
			(index_ptr->Page == IndexP -> Page)) {				/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
			return ((UBYTE)(index_ptr->Size & ~MEM_MILLI_BIT));	/* 該当MEM_IndexTable[]上のSizeを返します */
		}
	}
	return ((UBYTE)MEM_NO_INDEX);								/* MEM_NO_INDEX を返します */
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[蓄積原稿のインデックスNo.を調べます]
	function	:[
		引数でItem、No、Pageをセットしたデータのポインタを渡します
		Item、No、Pageをもとに該当するインデックスを探します
		該当インデックスのIndexNoを返します
	]
	return		:[
		IndexNo					0 ～ MEM_INDEX_TABLE_MAX
		MEM_NO_INDEX			0xFFFF		該当インデックスなし
	]
	common		:[
		struct IndexTableData MEM_IndexTable[]
	]
	condition	:[
		蓄積中、蓄積の終了している原稿に有効です
	]
	comment		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[MEM]
	date		:[1993/12/22,1996/10/25]
	author		:[NOBUKO,吉川弘康]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_FCOT_CheckIndexNo(struct MEM_IndexData_t *IndexP)	/* 蓄積されている原稿を指定 */
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */
	struct IndexTableData_t *index_ptr;

	index_ptr = &MEM_IndexTable[0];
	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++, index_ptr++) {/* インデックス・テーブルの中を検索し、該当するインデックスを確定します */
		if (((UBYTE)(index_ptr->Item & ~MEM_NOW_STORING) == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			(index_ptr->No   == IndexP -> No)   &&								/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
/* #if (PRO_F_CODE == ENABLE) */
			((index_ptr->BoxNumber == IndexP -> BoxNumber) ||					/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
/* #endif */
			(index_ptr->Page == IndexP -> Page)) {					/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
			return (index_no);										/* 該当MEM_IndexTable[]上のインデックスNo.を返します */
		}
	}
	return (MEM_NO_INDEX);											/* MEM_NO_INDEX を返します */
}
#endif



/*************************************************************************
	module		:[指定インデックスが使用されているか否か]
	function	:[
		1.マルチ回線での受信原稿競合の回避で使用します。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MEM]
	date		:[1997/01/09]
	author		:[村田]
*************************************************************************/
UWORD MEM_CheckConflictIndexNo (struct MEM_StoreData_t *IndexP)	/* 蓄積されている原稿を指定 */
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */
	UWORD result;

	UBYTE comp_item1;
	UBYTE comp_item2;
	UBYTE comp_item3;

	/*CMN_DisableInterrupt(); WRITE_OPEN_SEM 1997/12/16 Y.Murata */	/* DI */
	wai_sem(semno.MEM_WriteOpenSem);	/* WRITE_OPEN_SEM 1997/12/16 Y.Murata */

	result = MEM_NO_INDEX;
	comp_item1 = IndexP->Item;
	comp_item2 = (UBYTE)(IndexP->Item | MEM_NOW_DELETING);
	comp_item3 = (UBYTE)(IndexP->Item | MEM_NOW_STORING);

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブルの中を検索し、該当するインデックスを確定します */
		
		if (((MEM_IndexTable[index_no].Item == comp_item1) ||
			(MEM_IndexTable[index_no].Item == comp_item2) ||
			(MEM_IndexTable[index_no].Item == comp_item3)) &&
			(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {
			result = index_no;		/* 該当MEM_IndexTable[]上のインデックスNo.を返します */
			break;
		}
	}
	/*CMN_EnableInterrupt(); WRITE_OPEN_SEM 1997/12/16 Y.Murata */	/* EI */
	sig_sem(semno.MEM_WriteOpenSem);	/* WRITE_OPEN_SEM 1997/12/16 Y.Murata */
	return (result);
}

