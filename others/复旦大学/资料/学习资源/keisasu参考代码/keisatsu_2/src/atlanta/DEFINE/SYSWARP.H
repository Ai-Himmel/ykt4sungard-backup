#ifndef syswarp_h
	#define syswarp_h

#include "\src\atlanta\define\sysmax.h"

/************************************************************************
 * 受信転送データ														*
 * extern struct SYS_SubDialData_t SYB_WarpFile[SYS_WARP_MAX]			*
 * 1998/06/15															*
 * 桑原美紀																*
 ************************************************************************/
struct SYS_SubDialData_t {
	UBYTE  Status;							/* 使用状況	*/	/* 1998/09/01 By M.Kuwahara	*/
	UBYTE  Direct[SYS_DIRECT_DIAL_MAX];		/* 転送先（直接）			*/
	UBYTE  Onetouch[SYS_ONETOUCH_BIT_FIELD_MAX];/* 転送先（ワンタッチ）	*/
	UBYTE  Speed[SYS_SPEED_BIT_FIELD_MAX];		/* 転送先（短縮）		*/
	UDWORD Group;								/* 転送先（グループ）	*/
	UBYTE  StartWeek;						/* 開始曜日					*/
	UBYTE  EndWeek;							/* 終了曜日					*/
	UWORD  StartTime;						/* 開始時間					*/
	UWORD  EndTime;							/* 終了時間					*/
	UBYTE  Option;							/* オプション設定			*/
};

/************************************************************************
 * 受信転送データの使用状況												*
 * struct SYS_SubDialData_t SYB_WarpFile[].Status						*
 * 1998/09/01															*
 * 桑原美紀																*
 ************************************************************************/
#define SYS_WARP_EMPTY		0	/* 未使用 */
#define SYS_WARP_SETTING	1	/* セット中 */

/************************************************************************
 * 受信転送指定曜日														*
 * 1998/06/15															*
 * 桑原美紀																*
 ************************************************************************/
#define	SYS_NICHI					0x00	/* 日曜日					*/
#define	SYS_GETU					0x01	/* 月曜日					*/
#define	SYS_KA						0x02	/* 火曜日					*/
#define	SYS_SUI						0x03	/* 水曜日					*/
#define	SYS_MOKU					0x04	/* 木曜日					*/
#define	SYS_KIN						0x05	/* 金曜日					*/
#define	SYS_DOU						0x06	/* 土曜日					*/
#define SYS_NO_DAY					0xFF	/* 曜日指定無し				*/

/************************************************************************
 * オプション設定														*
 * 1998/09/02															*
 * 桑原美紀																*
 ************************************************************************/
#define	WARP_OPTION_NONE			0x00	/* オプション設定なし 		*/
#define	WARP_OPTION_PRINT			0x01	/* ワープ時の同時プリント	*/

#endif
