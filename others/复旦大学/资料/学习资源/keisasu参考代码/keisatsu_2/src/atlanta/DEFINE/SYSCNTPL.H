/*****************************************************:
 * SYSCNTPL.H
 * 連続ポーリング用コマンドデータ
 * 1996/10/17 Eguchi
 ******************************************************/
#ifndef	SYSCNTPL_H
 #define	SYSCNTPL_H	1

#include	"\src\atlanta\define\sysdial.h"

struct	SYS_ContinuousPollingData_t	{
	UBYTE	Status;				/* 使用状況 （コマンドファイルの使用状況と同じ値がはいる) */
	UWORD	DepartmentCode;		/* 部門コード */
	UDWORD	StartTime;			/* 連続ポーリング開始時刻 (1992年1月1日0時0分0秒からの累積秒数) */
	UDWORD	EndTime;			/* 連続ポーリング終了時刻 (1992年1月1日0時0分0秒からの累積秒数) */
	struct	SYS_DialData_t	DialNumber; /* 電話番号 */
/*#if (PRO_PIN_ACCESS == ENABLE)*/
	UBYTE	PIN_AccessMode;		/*  コマンド登録時のＰＩＮアクセスモード */
	UBYTE	PIN_AccessNumber[SYS_PIN_MAX]; /* ＰＩＮ番号 BCDで８桁まで*/
/*#endif*/
};
#endif
