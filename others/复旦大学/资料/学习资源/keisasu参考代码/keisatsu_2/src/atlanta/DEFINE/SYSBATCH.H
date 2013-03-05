/* By Y.Suzuki 1996/10/16 */
/*	Original File jun\usr2:\src\kobe\anzu\define\sysbatch.h	*/
#ifndef sysbatch_h
	#define sysbatch_h

#include "\src\atlanta\define\sysdial.h"

/************************************************************************
 * 一括送信																*
 * struct SYS_BatchTxData_t SYB_BatchTxFile[SYS_BATCH_FILE_MAX]			*
 * sysbatch.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
struct SYS_BatchTxData_t {
	UBYTE Status;						/* 使用状況 */
#if (0)
	struct SYS_DialData_t DialNumber[1];			/* 電話番号 By S.K */
#endif
	struct SYS_BatchTxDialData_t DialNumber[1];		/* 電話番号	 一括送信は１宛て先のみ有効です 1996/11/27	By T.Yamaguchi */

	UDWORD ExecTime;					/* 発信時刻 */
										/* 1992年1月1日0時0分0秒からの蓄積秒数 */
	UDWORD ProgramTime;					/* 発信指定時刻 By 野瀬 */
	UWORD Page;							/* 送信ページ数 */
/*	UBYTE Page;	1997/05/09  By T.Yamaguchi	/@ 送信ページ数 */
	UBYTE Name[SYS_BATCH_NAME_MAX];		/* 宛先名(NULL含む) */
	UWORD IndexNo[SYS_BATCH_INDEX_MAX];	/* 送信原稿番号 */
};

/**************************************************************************
 * 一括送信の使用状況													  *
 * struct SYS_BatchTxData_t.Status										  *
 * 1993/11/19															  *
 * 吉川弘康																  *
 * S.Kawasaki 94/2/1 Statusの定義はSYB_CommandFile.Statusと同じものを使用 *
 **************************************************************************/
/**************************************************************************
#define SYS_BAT_EMPTY		0	@* 未使用 *@
#define SYS_BAT_SETTING		1	@* 原稿蓄積中 *@
#define SYS_BAT_WAITING		2	@* 予約中 *@
#define SYS_BAT_EXECUTE		3	@* 実行中 *@
#define SYS_BAT_ERASED		4	@* 予約取消 *@
#define SYS_BAT_POWER_OFF	5	@* 電源断 *@
***************************************************************************/

/**************************************************************************
 * 一括送信の送信原稿情報												  *
 * struct SYS_BatchTxData_t.IndexNo[]										  *
 * 1994/08/15															  *
 * 吉川弘康																  *
 **************************************************************************/
#define SYS_BAT_DOC_EMPTY	0	/* 原稿なし */
#define SYS_BAT_DOC_STORE	1	/* 原稿あり */
#define SYS_BAT_DOC_STORING	2	/* 原稿蓄積中 */

#endif
