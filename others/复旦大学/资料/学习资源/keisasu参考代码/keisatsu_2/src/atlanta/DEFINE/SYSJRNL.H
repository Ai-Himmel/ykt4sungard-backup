/* By Y.Suzuki 1996/10/14 */
#ifndef sysjrnl_h
	#define sysjrnl_h

#include  "\src\atlanta\define\sysmax.h"
/************************************************************************
 * 通信管理記録															*
 * struct SYS_JournalData_t SYB_TxJournalFile[SYS_JOURNAL_MAX]			*
 * struct SYS_JournalData_t SYB_RxJournalFile[SYS_JOURNAL_MAX]			*
 * struct SYS_JournalData_t SYB_JournalFile[SYS_JOURNAL_MAX]			*
 * sysjrnl.jsw参照														*
 * 1993/11/19															*
 ************************************************************************/
struct SYS_JournalData_t {
	UWORD Number;			/* 通番(0～999) */
	UWORD Result;			/* 通信結果 */
	UDWORD StartTime;		/* 通信開始時間 */
							/* 1992年1月1日0時0分0秒からの蓄積秒数 */
	UWORD TotalTime;		/* 通信時間(秒) */
	UWORD DepartmentCode;	/* 部門コード */
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/15 */
	UBYTE KeisatsuID[5];
#endif /* defined (KEISATSU) */
	UBYTE RemoteID_TTI[SYS_JOURNAL_RMT_MAX];
							/* 相手先名(NULL含む) */
	UBYTE Mode;				/* 通信モード */
							/* 最終のモードを記憶 */
/*	UBYTE → UWORD */
/*	UBYTE Page;				/@ 通信ページ数 */
	UWORD Page;				/* 通信ページ数 */
	UBYTE Type;				/* 送信/受信の識別 */
	UBYTE Kind;				/* 通信種類 */
	UBYTE Option;			/* 付加情報 */
	UBYTE StackNumber;		/* 回線番号(Multi Line) */
};

/************************************************************************
 * 通信管理記録の付加情報												*
 * struct SYS_JournalData_t.Option										*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_TCR_REQUEST			0x01	/* 通信証プリント要求有り */

#define SYS_EXT_LINE			0x10	/* 拡張回線での送信時にセットする。By T.Soneoka 1998/02/04 */

/************************************************************************
 * 送信/受信の識別														*
 * struct SYS_JournalData_t.Type										*
 * 1994/01/18															*
 * 村田																	*
 ************************************************************************/
#define TXTYPE			1
#define RXTYPE			2
#if defined(STOCKHM2) || (PRO_JOURNAL_VER_UP == ENABLE)	/* Added by SMuratec C.P 2004/06/07 *//* by K.Watanabe 2004/10/15 */
#define BOTHTYPE		3
#endif

#endif
