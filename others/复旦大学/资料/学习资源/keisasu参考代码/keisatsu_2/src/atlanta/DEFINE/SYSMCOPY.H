/* By Y.Suzuki 1996/10/15 */
/* Original File : jun\usr2:\src\ichou\define\sysmcopy.h */
#ifndef SYSMCOPY_H
	#define SYSMCOPY_H

/************************************************************************
 * マルチコピー															*
 * struct SYS_MultiCopyData_t SYB_MultiCopyFile[SYS_MULTI_COPY_MAX]		*
 * sysmcopy.jsw参照														*
 * ﾌﾟﾘﾝﾀがﾌｪｲｽｱｯﾌﾟの場合、												*
 *  ①PrintPage = StorePage												*
 *  ②1ﾍﾟｰｼﾞｺﾋﾟｰする毎に、PrintPage--する。								*
 *  ③0ﾍﾟｰｼﾞになった場合は、ExecutiveNumber++し、①に戻る。				*
 * ﾌﾟﾘﾝﾀがﾌｪｲｽﾀﾞｳﾝの場合、												*
 *  ①PrintPage = 1														*
 *  ②1ﾍﾟｰｼﾞｺﾋﾟｰする毎に、PrintPage++する。								*
 *  ③(StorePage+1)ﾍﾟｰｼﾞになった場合は、ExecutiveNumber++し、①に戻る。	*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
struct	SYS_MultiCopyData_t	{
	UBYTE Status;			/* 動作状態 */
	UBYTE ReserveNumber;	/* 指定部数 */
	UBYTE ExecutiveNumber;	/* 実行済み部数 */
/*	UBYTE → UWORD 1997/05/09  By T.Yamaguchi */
/*	UBYTE StorePage;		/@ 蓄積済みページ */
/*	UBYTE PrintPage;		/@ 実行済みページ */
	UBYTE Cassette;			/* 自動/各段カセット*/
	UBYTE ManualSelect;		/* 手動でカセット選択されたか */
	UBYTE Size;				/* 手差し原稿サイズ */
	UBYTE SortType;			/* ソート/ノンソート */
	UBYTE Reduction;		/* 縮小率 */
	UBYTE ScanType;			/* ＦＢＳ/ＡＤＦスキャン */
	UBYTE ScanSize;			/* ＦＢＳの読み取りサイズ */
	UBYTE OHPMode;			/* ＯＨＰモード *//* By M.Tachibana 1997/12/17 */
	UBYTE Reserve;			/* リザーブ *//* By M.Tachibana 1997/12/17 */
	UWORD StorePage;		/* 蓄積済みページ */
	UWORD PrintPage;		/* 実行済みページ */
};

/************************************************************************
 * マルチコピーの動作状態												*
 * struct SYS_MultiCopyData_t.Status										*
 * sysmcopy.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_MCOPY_EMPTY			0	/* 未使用 */
#define SYS_MCOPY_STORE			1	/* コピー予約の確定から原稿蓄積終了まで */
#define SYS_MCOPY_PRINT			2	/* 原稿プリント中 */
#define SYS_MCOPY_MEMORY_OVER	3	/* ＦＢＳ読み取り時にメモリオーバーが発生 */

/************************************************************************
 * マルチコピーのカセットタイプ											*
 * struct SYS_MultiCopyData_t.Cassette									*
 * sysmcopy.jsw参照														*
 * sysdoc.hの指定カセットをセットする									*
 * 1994/04/26															*
 * 吉川弘康																*
 ************************************************************************/
#if (0) /* ●ICHOU変更 by T.Soneoka 1996/06/27 */
**	#define SYS_AUTO_CASSETTE		0	/* 自動選択 */
**	#define SYS_UPPER_CASSETTE		1	/* 上段カセット選択 */
**	#define SYS_LOWER_CASSETTE		2	/* 下段カセット選択 */
#endif
#if (0)	/* sysdoc.hに移動した By H.Yoshikawa 1996/08/14 */
**#define SYS_AUTO_CASSETTE		0	/* 自動選択 */
**#define SYS_1ST_CASSETTE		1	/* １段目カセット選択 */
**#define SYS_2ND_CASSETTE		2	/* ２段目カセット選択 */
**#define SYS_3RD_CASSETTE		3	/* ３段目カセット選択 */
**#define SYS_4TH_CASSETTE		4	/* ４段目カセット選択 */
**#define SYS_MANUAL_CASSETTE		5	/* 手差しカセット選択 */
#endif

/************************************************************************
 * 手差しコピー時の原稿サイズ											*
 * struct SYS_MultiCopyData_t.Size										*
 * sysdoc.hの記録紙サイズ・記録紙エリア（SYS_A4_PAPER)をセットする		*
 * 1996/08/08															*
 * 吉川弘康																*
 ************************************************************************/

/************************************************************************
 * マルチコピーのソートタイプ											*
 * struct SYS_MultiCopyData_t.SortType									*
 * sysmcopy.jsw参照														*
 * 1994/04/26															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_SORT		0	/* ソートコピー */
#define SYS_NONE_SORT	1	/* ノンソートコピー */

/************************************************************************
 * マルチコピーの縮小率													*
 * struct SYS_MultiCopyData_t.Reduction									*
 * 50～200:50%～200%													*
 * 255:自動																*
 * sysmcopy.jsw参照														*
 * 1994/04/26															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_AUTO_REDUCTION	0xFF

/************************************************************************
 * マルチコピーのスキャン方式											*
 * struct SYS_MultiCopyData_t.ScanType									*
 * 1996/07/22															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_ADF_SCAN	0	/* ＡＤＦスキャン */
#define SYS_FBS_SCAN	1	/* ＦＢＳスキャン */

#endif	/* End of File */
