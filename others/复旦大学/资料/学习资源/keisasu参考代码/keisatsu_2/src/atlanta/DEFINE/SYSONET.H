/* ICHOU より移植 By Y.Suzuki 1996/10/14 */
#ifndef sysonet_h
	#define sysonet_h

#include "\src\atlanta\define\sysspeed.h"
#include "\src\atlanta\define\syscomf.h"

/************************************************************************
 * 標準ワンタッチダイヤル												*
 * struct SYS_OnetouchDialData_t SYB_OnetouchDial[SYS_ONETOUCH_MAX]		*
 * sysonet.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
/* ↓●ICHOUワンタッチ／プログラムワンタッチ独立の為未使用にする by T.Soneoka 1996/05/10 */
#if (0)	/*	By Y.Suzuki 1996/10/14	*/
**#if defined(KIRI)|| defined(MOMIJI)|| defined(MILAN) || defined(MOMIJI2) || defined(KIRI288) || defined(KIRI_P)
**struct SYS_OnetouchDialData_t {
**	char Status;					/* 登録状態 */
**	union {
**		struct SYS_SpeedDialData_t Onetouch;	/* 短縮ダイヤルと同じ */
**		struct SYS_CommandData_t Program;		/* 通信予約と同じ */
**		unsigned char Job[SYS_JOB_MAX];		/* ジョブメモリ */
**								/* SYB_OnetouchDial[]の配列オフセット値 */
**								/* 最終データに続く配列に-1をセット */
**	} DialData;
**};
**#endif
#endif


/************************************************************************
 * ワンタッチダイヤル						    						*
 * struct SYS_OnetouchDialData_t SYB_OnetouchDial[SYS_ONETOUCH_MAX]		*
 * sysonet.jsw参照														*
 * 1993/12/27															*
 * 田中　　																*
 ***********************************************************************/

#if (0)	/*	By Y.Suzuki 1996/10/14	*/
**#if defined(SATUKI_H) || defined(SATUKI_M) || defined(SATUKI_L) || defined(LVNDR_H)|| defined(LVNDR_L)

/*★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★*/
/*SYS_ProgDialDataを削除し、SYS_DialDataで統一します masuda '95/02/08 */
/*★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★*/
#if 0
**struct SYS_ProgDialData_t {
**    unsigned char         Item;
**    unsigned char         rvs;
**    union {
**        unsigned char     Direct[SYS_DIRECT_DIAL_MAX];
**                 char     Onetouch;
**        UWORD      Speed;
**        UWORD      Group;
**    }FaxNumber;
**    unsigned char         rvs1;
**};
#endif
#if 0
**struct SYS_ProgOptionData_t {
**    unsigned char         Item;
**    unsigned char         rvs;
**    union {
**        UWORD      SecureNumber;
**        unsigned long     RelayGroupNumber;
**       UWORD      DatabaseNumber[SYS_DATA_BASE_MAX];
**    }OptionNo;
**};
#endif
#if 0
**struct SYS_ProgramDialData_t {
**    unsigned char         Status;
**    unsigned char         rvs;
**    struct SYS_DialData_t   DialNumber[SYS_PRG_DIAL_MAX];
**		/*SYS_ProgDialData -> SYS_DialData変更 masuda '95/02/08 */
**    UWORD          ProgTimes;
**    struct SYS_ProgOptionData_t Option;
**};
#endif
#if 0
**struct SYS_OnetouchDialData_t {
**	unsigned char Status;					          /* 登録状態 */
**	unsigned char rsv;
**	union {
**		struct SYS_SpeedDialData_t   Onetouch;  /* 短縮ダイヤルと同じ */
**		struct SYS_ProgramDialData_t Program;	  /* 通信予約と同じ */
**	} DialData;
**};
**#endif
#endif
#endif


/************************************************************************
 * 標準ワンタッチダイヤルの登録状態										*
 * struct SYS_OnetouchDialData_t.Status									*
 * sysonet.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_NO_STORED		0		/* 未使用 */
#define SYS_ONETOUCH_STORED	1		/* ワンタッチダイヤル登録 */
#define SYS_PROGRAM_STORED	2		/* プログラムワンタッチダイヤル登録 */
#define	SYS_JOB_STORED		3		/* ジョブメモリ登録 */

#endif

