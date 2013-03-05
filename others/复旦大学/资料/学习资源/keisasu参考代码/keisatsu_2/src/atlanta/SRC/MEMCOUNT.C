/************************************************************************
*				By : NOBUKO
*			  Date : Wed 22 Dec. 1993 (\SRC\RICE\SRC\MEMCOUNT.C)
*		 Copy Date : Tue 12 Sep. 1995
*				   : 1996/10/21 From \src\kobe\anzu\src\ By M.Kotani
*		 File Name : MEMCOUNT.C
*	   Module Name :
*		1. UWORD MEM_CountTotalPage(UBYTE Item, UWORD No)
*		2. UWORD MEM_CountTotalEmptyPage(void)
*		3. UWORD MEM_CountTotalStorePage(void)
*		4. UWORD MEM_CountTotalBlock(UBYTE Item, UWORD No)
*		5. UWORD MEM_CountPageBlock(struct MEM_IndexData_t *IndexP)
*		6. UWORD MEM_CountTotalEmptyBlock(void)
*		7. UWORD MEM_CountTotalStoreBlock(void)
*		8. UBYTE MEM_CountUseBlockRate(void)
*		9. UBYTE MEM_CountEmptyBlockRate(void)
*	   10. UWORD MEM_CountTotalCapacity(void)
*	   11. UWORD ChainBlockCounter(UWORD StartBlock)
*************************************************************************/

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\mem_data.h"

#include "\src\atlanta\define\mntsw_c.h" /* added by H.Kubo 1998/09/25 */

#define NO		0
#define YES		1
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定蓄積原稿の蓄積枚数をカウントします]
	function	:[
		1.引数で原稿種別(Item)を渡します
		2.引数をもとに該当するインデックスを探します
		3.該当インデックスの見つかった分だけページ数をインクリメントします
		4.MEM_IndexTable[]内の検索がすべて終了したときの総ページ数を戻値として返します
	]
	return		:[
		(UWORD) 指定原稿の総ページ数
		#define MEM_NO_INDEX	0xFFFF		該当インデックスなし
	]
	common		:[なし]
	condition	:[
		1.蓄積の終了している原稿にのみ有効です
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1997/04/26]
	author		:[山口哲治]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_CountItemTotalPage (UBYTE Item)			/* 原稿指定のための原稿種別 */
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */
	UWORD total_page;										/* ページ数 */

	total_page = NO;												/* 初期化 (NO == 0) */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブル内をすべて検索し、該当するインデックスを確定します */
		if (MEM_IndexTable[index_no].Item == Item) {	/* MEM_IndexTable[]上原稿種別との指定原稿種別と */
			total_page++;											/* ページ数をインクリメントします */
		}
	}

	if (total_page == NO) {											/* ページ数がNO(0)ということは該当インデックスなしということです */
		return (MEM_NO_INDEX);										/* MEM_NO_INDEX を返します */
	}
	return (total_page);											/* 総ページ数を返します */
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定蓄積原稿の蓄積枚数をカウントします]
	function	:[
		1.引数で原稿種別(Item)、原稿No(No)、を渡します
		2.引数をもとに該当するインデックスを探します
		3.該当インデックスの見つかった分だけページ数をインクリメントします
		4.MEM_IndexTable[]内の検索がすべて終了したときの総ページ数を戻値として返します
	]
	return		:[
		(UWORD) 指定原稿の総ページ数
		#define MEM_NO_INDEX	0xFFFF		該当インデックスなし
	]
	common		:[なし]
	condition	:[
		1.蓄積の終了している原稿にのみ有効です
		2.BoxNumberを見る処理追加 1997/03/12  By T.Yamaguchi
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UWORD MEM_CountTotalPageFlsRom (UBYTE Item,			/* 原稿指定のための原稿種別 */
						  		UWORD	 No,			/* 原稿指定のためのインデックス・テーブル上のNo. */
						  		UBYTE BoxNumber)		/* 原稿指定のためのBox番号. */
#else
UWORD MEM_CountTotalPage (UBYTE Item,			/* 原稿指定のための原稿種別 */
						  UWORD	 No,			/* 原稿指定のためのインデックス・テーブル上のNo. */
						  UBYTE BoxNumber)		/* 原稿指定のためのBox番号. */
#endif
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */
	UWORD total_page;										/* ページ数 */

	total_page = NO;												/* 初期化 (NO == 0) */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブル内をすべて検索し、該当するインデックスを確定します */
		if ((MEM_IndexTable[index_no].Item == Item) &&				/* MEM_IndexTable[]上原稿種別との指定原稿種別と */
			(MEM_IndexTable[index_no].No   == No) &&
			((MEM_IndexTable[index_no].BoxNumber == BoxNumber) ||
		     (BoxNumber == MEM_IGNORE_BOX_NUMBER)) ) {	/* MEM_IndexTable[]上のNo.と指定原稿No.とBoxNumberが一致していたら */
			total_page++;											/* ページ数をインクリメントします */
		}
	}

	if (total_page == NO) {											/* ページ数がNO(0)ということは該当インデックスなしということです */
		return (MEM_NO_INDEX);										/* MEM_NO_INDEX を返します */
	}
	return (total_page);											/* 総ページ数を返します */
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定蓄積原稿の最終ページを探します]
	function	:[
		1.引数で原稿種別(Item)、原稿No(No)、を渡します
		2.引数をもとに該当するインデックスを探します
		3.該当インデックスのページ数の大きいものを抽出していきます
		4.MEM_IndexTable[]内の検索がすべて終了したときの最終ページ数を戻値として返します
	]
	return		:[
		(UWORD) 指定原稿の総ページ数
		#define MEM_NO_INDEX	0xFFFF		該当インデックスなし
	]
	common		:[なし]
	condition	:[
		1.蓄積の終了している原稿にのみ有効です
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[Dec.04.1996]
	author		:[T.Soneoka]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_CountFinalPage (UBYTE Item,			/* 原稿指定のための原稿種別 */
						  UWORD  No,			/* 原稿指定のためのインデックス・テーブル上のNo. */
						  UBYTE BoxNumber)		/* 原稿指定のためのBox番号. */
{
	UWORD  index_no;											/* MEM_IndexTable[]内のポインタ */
	UWORD  final_page;	/* 最終ページ */

	final_page = 0;

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブル内をすべて検索し、該当するインデックスを確定します */
		if ((MEM_IndexTable[index_no].Item == Item) &&				/* MEM_IndexTable[]上原稿種別との指定原稿種別と */
			(MEM_IndexTable[index_no].No   == No) 	&&				/* MEM_IndexTable[]上のNo.と指定原稿No.が一致していたら */
			((MEM_IndexTable[index_no].BoxNumber == BoxNumber) ||
		     (BoxNumber == MEM_IGNORE_BOX_NUMBER)) ) {	/* MEM_IndexTable[]上のNo.と指定原稿No.とBoxNumberが一致していたら */
			if (MEM_IndexTable[index_no].Page > final_page) {
				final_page = MEM_IndexTable[index_no].Page;
			}
		}
	}

	if (final_page == NO) {											/* ページ数がNO(0)ということは該当インデックスなしということです */
		return (MEM_NO_INDEX);										/* MEM_NO_INDEX を返します */
	}
	return (final_page);											/* 最終ページ数を返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定蓄積原稿の先頭ページを探します]
	function	:[
		1.引数で原稿種別(Item)、原稿No(No)、を渡します
		2.引数をもとに該当するインデックスを探します
		3.該当インデックスのページ数の小さいものを抽出していきます
		4.MEM_IndexTable[]内の検索がすべて終了したときの先頭ページ数を戻値として返します
	]
	return		:[
		(UWORD) 指定原稿の総ページ数
		#define MEM_NO_INDEX	0xFFFF		該当インデックスなし
	]
	common		:[受信原稿ポーリング取り出し修正分にて関数追加します by T.Soneoka 1997/02/21
	]
	condition	:[
		1.蓄積の終了している原稿にのみ有効です
	]
	comment		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[MEM]
	date		:[Dec.04.1996]
	author		:[T.Soneoka]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_CountTopPage (UBYTE Item,			/* 原稿指定のための原稿種別 */
						UWORD  No,				/* 原稿指定のためのインデックス・テーブル上のNo. */
						UBYTE BoxNumber)		/* 原稿指定のためのBox番号. */
{
	UWORD  index_no;											/* MEM_IndexTable[]内のポインタ */
	UWORD  top_page;	/* 最終ページ */

	top_page = 0xffff;

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブル内をすべて検索し、該当するインデックスを確定します */
		if ((MEM_IndexTable[index_no].Item == Item) &&				/* MEM_IndexTable[]上原稿種別との指定原稿種別と */
			(MEM_IndexTable[index_no].No   == No)	&&				/* MEM_IndexTable[]上のNo.と指定原稿No.が一致していたら */
			((MEM_IndexTable[index_no].BoxNumber == BoxNumber) ||
		     (BoxNumber == MEM_IGNORE_BOX_NUMBER)) ) {	/* MEM_IndexTable[]上のNo.と指定原稿No.とBoxNumberが一致していたら */
			if (MEM_IndexTable[index_no].Page < top_page) {
				top_page = MEM_IndexTable[index_no].Page;
			}
		}
	}

	if (top_page == 0xffff) {											/* ページ数が0xffffということは該当インデックスなしということです */
		return (MEM_NO_INDEX);										/* MEM_NO_INDEX を返します */
	}
	return (top_page);											/* 先頭ページを返します */
}



/*#if (PRO_F_CODE == ENABLE)*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定ＢＯＸ蓄積原稿の蓄積枚数をカウントします]
	function	:[
		1.引数で原稿種別(Item)、Box番号(BoxNumber)、を渡します
		2.引数をもとに該当するインデックスを探します
		3.該当インデックスの見つかった分だけページ数をインクリメントします
		4.MEM_IndexTable[]内の検索がすべて終了したときの総ページ数を戻値として返します
	]
	return		:[
		(UWORD) 指定原稿の総ページ数
		#define MEM_NO_INDEX	0xFFFF		該当インデックスなし
	]
	common		:[なし]
	condition	:[
		1.蓄積の終了している原稿にのみ有効です
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1997/01/24]
	author		:[山口 哲治]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_CountTotalBoxPage (UBYTE Item,			/* 原稿指定のための原稿種別 */
						  UBYTE	 BoxNumber)			/* 原稿指定のためのBox番号. */
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */
	UWORD total_page;										/* ページ数 */

	total_page = NO;												/* 初期化 (NO == 0) */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブル内をすべて検索し、該当するインデックスを確定します */
		if ((MEM_IndexTable[index_no].Item == Item) &&				/* MEM_IndexTable[]上原稿種別との指定原稿種別と */
			(MEM_IndexTable[index_no].BoxNumber == BoxNumber)) {				/* MEM_IndexTable[]上のNo.と指定原稿No.が一致していたら */
			total_page++;											/* ページ数をインクリメントします */
		}
	}

	if (total_page == NO) {											/* ページ数がNO(0)ということは該当インデックスなしということです */
		return (MEM_NO_INDEX);										/* MEM_NO_INDEX を返します */
	}
	return (total_page);											/* 総ページ数を返します */
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定蓄積原稿の蓄積枚数をカウントします]
	function	:[
		1.引数で原稿種別(Item)、原稿No(No)、ＢＯＸ番号(BoxNumber)を渡します
		2.引数をもとに該当するインデックスを探します
		3.該当インデックスの見つかった分だけページ数をインクリメントします
		4.MEM_IndexTable[]内の検索がすべて終了したときの総ページ数を戻値として返します
	]
	return		:[
		(UWORD) 指定原稿の総ページ数
		#define MEM_NO_INDEX	0xFFFF		該当インデックスなし
	]
	common		:[なし]
	condition	:[
		1.蓄積の終了している原稿にのみ有効です
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1997/02/03]
	author		:[山口哲治]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_CountTotalEachDocPage (UBYTE Item,			/* 原稿指定のための原稿種別 */
								 UWORD	 No,			/* 原稿指定のためのインデックス・テーブル上のNo. */
								 UBYTE	 BoxNumber)		/* 原稿指定のためのBox番号. */
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */
	UWORD total_page;										/* ページ数 */

	total_page = NO;												/* 初期化 (NO == 0) */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブル内をすべて検索し、該当するインデックスを確定します */
		if ((MEM_IndexTable[index_no].Item == Item) &&				/* MEM_IndexTable[]上原稿種別との指定原稿種別と */
			(MEM_IndexTable[index_no].No   == No)	&&				/* MEM_IndexTable[]上のNo.と指定原稿No.が一致していたら */
			(MEM_IndexTable[index_no].BoxNumber == BoxNumber))	{
			total_page++;											/* ページ数をインクリメントします */
		}
	}

	if (total_page == NO) {											/* ページ数がNO(0)ということは該当インデックスなしということです */
		return (MEM_NO_INDEX);										/* MEM_NO_INDEX を返します */
	}
	return (total_page);											/* 総ページ数を返します */
}

/*#endif*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[インデックスの総残ページ数をカウントします]
	function	:[
		1.原稿種別が SYS_MEM_FILE_EMPTY のインデックスを探します
		2.該当インデックスの見つかった分だけページ数をインクリメントします
		3.MEM_IndexTable[]内の検索がすべて終了したときの総ページ数を戻値として返します
	]
	return		:[
		(UWORD) インデックスの総残ページ数
	]
	common		:[なし]
	condition	:[
		1.蓄積中の原稿は空インデックスとはみなしません
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_CountTotalEmptyPage (void)
{
/*	return ((UWORD)MEM_INDEX_TABLE_MAX - MEM_CountTotalStorePage());		５行下に移動　94/11/16 */

#if 0
//	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */
//	UWORD total_page;										/* ページ数 */
#endif

	return ((UWORD)MEM_INDEX_TABLE_MAX - MEM_CountTotalStorePage());

#if 0
//	total_page = NO;												/* 初期化 (NO == 0) */
//
//	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブル内をすべて検索し、該当するインデックスを確定します */
//		if ((MEM_IndexTable[index_no].Item == SYS_MEM_FILE_EMPTY) ||	/* MEM_IndexTable[]上の原稿種別がSYS_MEM_FILE_EMPTYなら空インデックスなので */
//			((MEM_IndexTable[index_no].Item & MEM_NOW_DELETING) == MEM_NOW_DELETING)) {
//			total_page++;											/* ページ数をインクリメントします */
//		}
//	}
//
//	return (total_page);											/* 総ページ数を返します */
#endif
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[インデックスの総使用ページ数をカウントします]
	function	:[
		1.原稿種別が SYS_MEM_FILE_EMPTY でないインデックスを探します
		2.該当インデックスの見つかった分だけページ数をインクリメントします
		3.MEM_IndexTable[]内の検索がすべて終了したときの総ページ数を戻値として返します
	]
	return		:[
		(UWORD) インデックスの総使用ページ数
	]
	common		:[なし]
	condition	:[
		1.蓄積中の原稿は空インデックスとはみなしません
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_CountTotalStorePage (void)
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */
	UWORD total_page;										/* ページ数 */

	total_page = NO;												/* 初期化 (NO == 0) */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブル内をすべて検索します */
		if ((MEM_IndexTable[index_no].Item != SYS_MEM_FILE_EMPTY) &&		/* MEM_IndexTable[]上の原稿種別がMEM_FILE_EMPTYでなくて */
			((MEM_IndexTable[index_no].Item & MEM_NOW_DELETING) == 0)) {	/* MEM_IndexTable[]上の原稿種別に消去中ステータスがたっていないなら */
			total_page++;											/* 蓄積済みのインデックスということで、ページ数をインクリメントします */
		}
	}

	return (total_page);											/* 総ページ数を返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定蓄積原稿の総使用ブロック数をカウントします]
	function	:[
		1.引数で原稿種別(Item)、原稿No(No)、を渡します
		2.引数をもとに該当するインデックスを探します
		3.該当インデックスが見つかったらその使用ブロック数をカウントします
		4.MEM_IndexTable[]内をすべて検索し該当インデックスの使用ブロック数をすべてカウントします
		5.総使用ブロック数を戻値として返します
	]
	return		:[
		(UWORD) 指定原稿の総使用ブロック数
		#define MEM_NO_INDEX	0xFFFF		該当インデックスなし
	]
	common		:[なし]
	condition	:[
		1.蓄積中の原稿はカウントしません
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_CountTotalBlock (UBYTE Item,			/* 原稿指定のための原稿種別 */
						   UWORD  No,			/* 原稿指定のためのインデックス・テーブル上のNo. */
						   UBYTE  BoxNumber)	/* 原稿指定のためのBox番号. */

{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */
	UWORD total_block;										/* 使用ブロック数 */

	total_block = NO;												/* 初期化 (NO == 0) */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブル内をすべて検索します */
		if ((MEM_IndexTable[index_no].Item == Item) &&				/* MEM_IndexTable[]上原稿種別との指定原稿種別と */
			(MEM_IndexTable[index_no].No   == No) &&				/* MEM_IndexTable[]上のNo.と指定原稿No.が一致していたら */
			((MEM_IndexTable[index_no].BoxNumber == BoxNumber) ||
		     (BoxNumber == MEM_IGNORE_BOX_NUMBER)) ) {					/* MEM_IndexTable[]上のBoxNumberが一致していたら */
																	/* 指定原稿の蓄積開始ブロックがわかります */
			total_block += ChainBlockCounter(MEM_IndexTable[index_no].StartBlockNo);/* 次のブロックをFATテーブルから持ってきます */
		}
	}

	if (total_block == NO) {										/* 使用ブロック数がNO(0)ということは該当インデックスなしということです */
		return (MEM_NO_INDEX);										/* MEM_NO_INDEX を返します */
	}

	return (total_block);											/* 使用ブロック数を返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定蓄積原稿の使用ブロック数をカウントします]
	function	:[
		1.引数で原稿種別(Item)、原稿No(No)、ページ(Page)をセットしたstructのポインタを渡します
		2.引数をもとに該当するインデックスを探します
		3.該当インデックスの見つかったら使用ブロック数をカウントします
		4.使用ブロック数を戻値として返します
	]
	return		:[
		(UWORD) インデックスの使用ブロック数
		#define MEM_NO_INDEX	0xFFFF		該当インデックスなし
	]
	common		:[なし]
	condition	:[
		1.蓄積中の原稿は指定できません
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_CountPageBlock (struct MEM_IndexData_t *IndexP)	/* 原稿を指定します */
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */
	UWORD total_block;										/* 使用ブロック数 */

	total_block = NO;												/* 初期化 (NO == 0) */

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブル内をすべて検索します */
		if ((MEM_IndexTable[index_no].Item == IndexP -> Item) &&	/* MEM_IndexTable[]上の原稿種別と指定原稿の原稿種別が一致していて */
			(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&	/* MEM_IndexTable[]上のNoと指定原稿のNoが一致していて */
			((MEM_IndexTable[index_no].BoxNumber == IndexP -> BoxNumber) ||					/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageと指定原稿のPageが一致していたら */
																	/* 指定原稿の蓄積開始ブロックがわかります */
			return (ChainBlockCounter(MEM_IndexTable[index_no].StartBlockNo));
		}
	}
																	/* 該当インデックスなしなら */
	return (MEM_NO_INDEX);											/* MEM_NO_INDEX を返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[総空ブロック数をカウントします]
	function	:[
		1.機器の蓄積可能総ブロック数から蓄積に使用されているブロック数を引きます
		2.その答えを戻値として返します
	]
	return		:[
		(UWORD) 総空ブロック数
	]
	common		:[なし]
	condition	:[
		1.この関数が呼ばれた時点での空ブロック数をカウントします
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UWORD MEM_CountTotalEmptyBlockFlsRom(void)
#else
UWORD MEM_CountTotalEmptyBlock (void)
#endif
{
	if ((MEM_TotalAvailableStoreBlkCnt - MEM_RX_BORDERLINE) > MEM_TotalStoreBlockCounter) {
		return ((UWORD)((MEM_TotalAvailableStoreBlkCnt - MEM_RX_BORDERLINE) - MEM_TotalStoreBlockCounter));/* その値を戻値(空ブロック数)として返します */
	}
	else {
		return(0);
	}

#if 0	/* 1997/11/20 */
** 																	/* FATエリアの初期化の際にセットされている使用可能総ブロック数から */
** 																	/* 蓄積のたびに更新されている蓄積に使用しているブロック数を引きます */
** 	return ((UWORD)((MEM_TotalAvailableStoreBlkCnt - MEM_RX_BORDERLINE) - MEM_TotalStoreBlockCounter));/* その値を戻値(空ブロック数)として返します */
#endif
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[総使用ブロック数をカウントします]
	function	:[
		1.蓄積に使用されているブロック数を戻値として返します
	]
	return		:[
		(UWORD) 総使用ブロック数
	]
	common		:[なし]
	condition	:[
		1.この関数が呼ばれた時点での蓄積に使用されているブロック数をカウントします
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_CountTotalStoreBlock (void)
{
	return (MEM_TotalStoreBlockCounter);							/* 蓄積の度に更新されている蓄積に使用されているブロック数を返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[総使用ブロック数が蓄積可能総ブロック数に占める割合を調べます]
	function	:[
		1.総使用ブロック数が蓄積可能総ブロック数に占める割合を戻り値として返します
	]
	return		:[
		(UBYTE) 割合(??%)	0～100
	]
	common		:[なし]
	condition	:[
		1.この関数が呼ばれた時点での蓄積に使用されているブロック数を対象とします
		2.受信のみに使用可能な裏メモリは蓄積可能総ブロック数の対象外となります
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_CountUseBlockRate (void)
{
	DWORD total_block;										/* 総使用ブロック数(DWORDで取っているのは割合を出すので×100するため) */
	UBYTE rate;												/* 割合 (??%) */

	rate = NO;														/* 初期化 (NO == 0) */

	if (MEM_CheckUseIndex() == (UBYTE)MEM_NO_INDEX)
		return (rate);

	if (MEM_TotalStoreBlockCounter != 0) {							/* 蓄積に使用されているブロックの有無 */
																	/* 使用ブロックがあるなら割合の計算をします */
		total_block = (DWORD)((DWORD)MEM_TotalStoreBlockCounter * (DWORD)100);		/* 使用ブロック数を100倍します */
																	/* 割合を計算します */
																	/* 100倍した値を蓄積可能総ブロック数で割ります */
		rate = (UBYTE)(total_block / ((DWORD)((UWORD)MEM_TotalAvailableStoreBlkCnt - (UWORD)MEM_RX_BORDERLINE)));
																	/* 端数は切り上げます */
																	/* 100倍した値を蓄積可能総ブロック数で割って余りがあったら */
		if ((total_block % ((DWORD)((UWORD)MEM_TotalAvailableStoreBlkCnt - (UWORD)MEM_RX_BORDERLINE))) > 0) {
			rate++;													/* 割合を切り上げます */
		}
		if (rate > 100) {											/* 割合が 100以上の数になってしまった場合は */
			rate = 100;												/* 100 とします */
		}
	}
	return (rate);													/* 割合を返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[総空ブロック数が蓄積可能総ブロック数に占める割合を調べます]
	function	:[
		1.総空ブロック数が蓄積可能総ブロック数に占める割合を戻り値として返します
	]
	return		:[
		(UBYTE) 割合(??%)	0～100
	]
	common		:[なし]
	condition	:[
		1.この関数が呼ばれた時点での空ブロック数を対象とします
		2.受信のみに使用可能な裏メモリは蓄積可能総ブロック数の対象外となります
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/12/22]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_CountEmptyBlockRate (void)
{
	DWORD total_block;										/* 総使用ブロック数(DWORDで取っているのは割合を出すので×100するため) */
	UBYTE rate;												/* 割合 (??%) */

	rate = NO;														/* 初期化 (NO == 0) */

	if (MEM_CheckUseIndex() == (UBYTE)MEM_NO_INDEX)
		return (100);

	if (MEM_TotalStoreBlockCounter != 0) {							/* 蓄積に使用されているブロックの有無 */
																	/* 使用ブロックがあるなら割合の計算をします */
		total_block = (DWORD)((DWORD)MEM_TotalStoreBlockCounter * (DWORD)100);		/* 使用ブロック数を100倍します */
																	/* 割合を計算します */
																	/* 100倍した値を蓄積可能総ブロック数で割ります */
		rate = (UBYTE)(total_block / ((DWORD)((UWORD)MEM_TotalAvailableStoreBlkCnt - (UWORD)MEM_RX_BORDERLINE)));
																	/* 端数は切り捨てます */
																	/* 100倍した値を蓄積可能総ブロック数で割って余りがあったら */
		if (rate > 100) {											/* 割合が 100以上の数になってしまった場合は */
			rate = 100;												/* 100 とします */
		} else if (rate == 0) {										/* 端数は切り捨てなので0.xx%使用時は1%とします */
			rate = 1;
		}
	}
	return (UBYTE)(100 - rate);								/* 100から使用割合を引いて返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[拡張分も含めてTotalで何KByte蓄積可能かを調べる]
	function	:[
		1.拡張分を含めて全部で有効FATブロックが何ブロックあるか
		2.そのブロック数にFATブロック1単位分の容量をかけます
	]
	return		:[
		(UWORD) メモリ容量(KByte)
	]
	common		:[なし]
	condition	:[
		1.既蓄積ブロックと空ブロックの和になります
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/ 7/ 4]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_CountTotalCapacity(void)
{
	UWORD block_size;

	block_size = (UWORD)MEM_BLOCK_SIZE;
	if (block_size >= 1024) {
		return (MEM_TotalAvailableStoreBlkCnt * (block_size / 1024));
	} else {
		return (MEM_TotalAvailableStoreBlkCnt / (1024 / block_size));
	}
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定されたブロックからEOP/EOB迄チェーン化されているブロック数を数えます]
	function	:[
		1.指定されたブロックを先頭とし、EOP/EOB迄のチェーン化されているブロック数を返します
	]
	return		:[
		(UWORD) ブロック数
	]
	common		:[なし]
	condition	:[
		1.この関数が呼ばれた時点でのチェーン化されているブロックを対象とします
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1993/ 6/27]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD ChainBlockCounter (UWORD StartBlock)
{
	UWORD block;
	UWORD total_block;

	block = MEM_FATArea[StartBlock];						/* 次のブロックをFATテーブルから持ってきます */
	total_block = 1;										/* ブロック数はとりあえず 1 */

															/* 以下のループの中ではチェーン化されているブロック数(EOP,EOB,蓄積中or予約中まで)をカウントします */
	while (block < MEM_RESERVED_BLOCK) {					/* 有効FATエリア内をすべてチェックするループの中で */
		block = MEM_FATArea[block];							/* チェーン化されているブロックをカウントします */
		total_block++;										/* ブロック数をインクリメントします */

		/* 1997/11/28
		 * ＤＲＡＭバックアップで、バックアップの電池はＯＫだがＤＲＡＭが破壊されていた場合
		 * 立ち上げ時にここでループしてしまうことがある。そうなればキーもきかなくなるので
		 * リセットじゃ～！
		*/
		if (total_block > (MEM_FAT_AREA_MAX+1)) {
			NackBuzzerSound();
			outp((unsigned long)0,(unsigned char)0);/* WriteProtectError for ICE */
			NackBuzzerSound();
			NackBuzzerSound();
			SYB_MaintenanceSwitch[MNT_SW_C1] |= MEM_FAT_ILLEGAL;
			InitializeDRAM_Parameter();
			SaveReturnAddressAndJumpBegin();	/**リセットする*/
		}

	}
	MEM_BlockCounterEndStatus = block;	/*チェーンのブロックの最終の状態を示す*/
	return (total_block);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定蓄積原稿の最大蓄積ページ番号を獲得します]
	function	:[
		1.引数で原稿種別(Item)、原稿No(No)、を渡します
		2.引数をもとに該当するインデックスを探します
		3.該当インデックスの見つかった中で、一番大きいページ番号を探します。
		4.MEM_IndexTable[]内の検索がすべて終了したときの一番大きいページ番号を戻値として返します
	]
	return		:[
		(UWORD) 指定原稿の最大蓄積ページ番号
		#define MEM_NO_INDEX	0xFFFF		該当インデックスなし
	]
	common		:[なし]
	condition	:[
		1.蓄積の終了している原稿にのみ有効です
		2.ノンソートコピーのように、蓄積しながらプリントを行い、１ページプリント終了後にその原稿を蓄積する場合に、
		  蓄積終了後に、既に消去されたページを含め、何ページ蓄積したかをこの関数を使って知ることができます。
	]
	comment		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[MEM]
	date		:[1996/11/27]
	author		:[吉川弘康]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UWORD MEM_CountMaxPage (UBYTE Item,				/* 原稿指定のための原稿種別 */
						UWORD No,				/* 原稿指定のためのインデックス・テーブル上のNo. */
						UBYTE BoxNumber) 		/* 原稿指定のためのボックス番号 */
{
	UWORD  index_no;							/* MEM_IndexTable[]内のポインタ */
	UWORD  max_page;							/* ページ番号 */
	struct IndexTableData_t *index_ptr;

	max_page = 0;

	index_ptr = &MEM_IndexTable[0];
	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++, index_ptr++) {	/* インデックス・テーブル内をすべて検索し、該当するインデックスを確定します */
		if ((index_ptr->Item == Item) &&							/* MEM_IndexTable[]上原稿種別との指定原稿種別と */
			((index_ptr->BoxNumber == BoxNumber) ||
			 (BoxNumber == MEM_IGNORE_BOX_NUMBER)) &&
			(index_ptr->No	 == No)) {								/* MEM_IndexTable[]上のNo.と指定原稿No.が一致していたら */
			if (index_ptr->Page > max_page) {
				max_page = index_ptr->Page;
			}
		}
	}

	if (!max_page) {												/* 最大ページ数がNO(0)ということは該当インデックスなしということです */
		return (MEM_NO_INDEX);										/* MEM_NO_INDEX を返します */
	}
	return (max_page);												/* 最大ページ番号を返します */
}

/*#if (PRO_F_CODE == ENABLE)*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定蓄積原稿の空き蓄積ＮＯを探します]
	function	:[
		1.引数で原稿種別(Item)、ＢＯＸNo(BoxNumber)、を渡します
		2.引数をもとに該当するインデックスを探します
		3.該当インデックスの見つかったＮｏ（６４まで）をローカル変数にセットします
		4.MEM_IndexTable[]内の検索がすべて終了したとき変数をチェックして最初の空きＮｏを返します
	]
	return		:[
		(UWORD) 最初の空き原稿Ｎｏ
	]
	common		:[なし]
	condition	:[
		1.蓄積の終了している原稿にのみ有効です
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1997/01/28]
	author		:[山口 哲治]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE MEM_DetectEmptyNo(UBYTE Item,				/* 原稿指定のための原稿種別 */
						UBYTE BoxNumber)		/* 原稿指定のためのＢＯＸ番号. */
{
	struct MEM_StoredNo_t *stored_data;
	UBYTE	i;

	stored_data = MEM_GetStoredIndexNo(Item, BoxNumber);

	if ((stored_data->stored_indexno_lower) || (stored_data->stored_indexno_uper)) {	/* 蓄積原稿がある */
		if (stored_data->stored_indexno_lower != 0xffff) {	/* 蓄積原稿Ｎｏが０～３１以内 */
			for (i = 0;i < 32;i++) {
				if ((stored_data->stored_indexno_lower >> i) & 0x0001) {
						/* Noが使われているなら次をチェック */
				}
				else {	/* 空きＮｏ発見 */
					return(i);	/* 最初の空きＮｏ */
				}
			}
		}
		else {	/* 蓄積Ｎｏが０～３１まで使用されているなら３２～６４までを探す */
			for (i = 0;i < 32;i++) {
				if ((stored_data->stored_indexno_uper >> i) & 0x0001) {
						/* Noが使われているなら次をチェック */
				}
				else {	/* 空きＮｏ発見 */
					return((UBYTE)(i + 32));	/* 最初の空きＮｏ */
				}
			}
		}
	}
	else {	/* 蓄積原稿が一枚もない*/
		return (0);							/* 全て空いているので０を返す */
	}
	return (0);	/* ここに来るのはおかしい MEM_NO_INDEX を返します */
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[指定ＢＯＸ番号の蓄積Noを探します]
	function	:[
		1.引数で原稿種別(Item)、ＢＯＸNo(BoxNumber)、を渡します
		2.引数をもとに該当するインデックスを探します
		3.該当インデックスの見つかったＮｏ（６４まで）をローカル変数にセットします
		4.MEM_IndexTable[]内の検索がすべて終了したとき変数のアドレスを返す
	]
	return		:[
		(UWORD) 最初の空き原稿Ｎｏ
	]
	common		:[なし]
	condition	:[
		1.蓄積の終了している原稿にのみ有効です
	]
	comment		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1997/01/28]
	author		:[山口 哲治]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
struct MEM_StoredNo_t *MEM_GetStoredIndexNo(UBYTE Item,			/* 原稿指定のための原稿種別 */
											UBYTE BoxNumber)		/* 原稿指定のためのＢＯＸ番号. */
{
	UWORD index_no;											/* MEM_IndexTable[]内のポインタ */

	struct MEM_StoredNo_t *stored_number;

	stored_number->stored_indexno_lower = 0;
	stored_number->stored_indexno_uper = 0;

	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* インデックス・テーブル内をすべて検索し、該当するインデックスを確定します */
		if ((MEM_IndexTable[index_no].Item == Item) &&				/* MEM_IndexTable[]上原稿種別との指定原稿種別と */
			(MEM_IndexTable[index_no].BoxNumber == BoxNumber)) {	/* MEM_IndexTable[]上のNo.と指定原稿No.が一致していたら */
			if (MEM_IndexTable[index_no].No < 32) {
				stored_number->stored_indexno_lower |= (1 << MEM_IndexTable[index_no].No);
			}
			else if ((32 <= MEM_IndexTable[index_no].No) || (MEM_IndexTable[index_no].No < 64)) {
				stored_number->stored_indexno_uper |= (1 << (MEM_IndexTable[index_no].No - 32));
			}
		}
	}

	return(stored_number);
}
/*#endif*/
