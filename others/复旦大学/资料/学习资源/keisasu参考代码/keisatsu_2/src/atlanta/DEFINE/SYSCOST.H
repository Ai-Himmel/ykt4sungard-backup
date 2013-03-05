/* By Y.Suzuki 1996/10/15 */
/* Original File : jun\usr2:\src\kobe\anzu\define\syscost.h */
#ifndef syscost_h
	#define syscost_h

/************************************************************************
 * 料金管理テーブル														*
 * struct SYS_CostBaseTable_t SYB_CostTable[SYS_COST_TABLE_MAX]			*
 * syscost.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
struct SYS_CostBaseTable_t {
	UWORD Daytime;		/* 単位時間当たりの昼間の通話時間 */
						/* 入力値×10の値をセット */
	UWORD Night;		/* 単位時間当たりの夜間の通話時間 */
						/* 入力値×10の値をセット */
	UWORD Midnight;		/* 単位時間当たりの深夜の通話時間 */
						/* 入力値×10の値をセット */
};

struct SYS_NTT_AccessData_t {
	UBYTE Number[7];	/* 局番 */
						/* アスキーコードをセット、最終番号＋１にNULLをセット */
	UBYTE CostTable;	/* SYB_CostTable[]の配列オフセット値 */
};

#endif
