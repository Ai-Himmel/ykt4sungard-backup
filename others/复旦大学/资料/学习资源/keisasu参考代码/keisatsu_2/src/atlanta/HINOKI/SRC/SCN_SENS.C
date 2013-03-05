/*
 *	@(#)%W%
 *	FileName:	/home2/prj/Eva/Src/scn/scn_sens.c
 *	Create:	Wed Dec 17 11:05:48 1997	by	ishiyama
 *	Description:
 *		Sensor for Scanner
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\hinoki\ext_v\scn_tbl.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\ext_v\sys_data.h"

/*
 *	Name:	Watch Raw Mode DS1
 *	Create:	Mon Dec 15 14:42:28 1997	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	Ds1Raw(void);
 *	Description:
 *		Raw Mode で DS1 をチェック
 *	Return Value:
 *		TRUE:	DS1 is ON(原稿有り)
 *		FALSE:	DS1 is OFF(原稿無し)
 *	Change Log:
 *		
 */
BOOL	Ds1Raw(void)
{
	BOOL	rtn;				/* Return Value */

#if (0)	/* 1998/10/18 by T.Soneoka */
**	if ((InputWORD(GA_PGBDR) & IO_BIT_TXIL) /* Scanner Cover Open */
**		|| (InputWORD(GA_PGBDR) & IO_BIT_XDS1)) {
		rtn = FALSE;
	} else {
		rtn = TRUE;
	}
#else
	if (!TXIL() && DS1()) {
		rtn = TRUE;
	} else {
		rtn = FALSE;
	}
#endif
	return	rtn;
}

/*
 *	Name:	Watch Raw Mode DS2
 *	Create:	Mon Dec 15 14:42:28 1997	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	Ds2Raw(void);
 *	Description:
 *		Raw Mode で DS2 をチェック
 *	Return Value:
 *		TRUE:	DS2 is ON(原稿有り)
 *		FALSE:	DS2 is OFF(原稿無し)
 *	Change Log:
 *		
 */
BOOL	Ds2Raw(void)
{
	BOOL	rtn;						/* Return Value */

#if (0)	/* 1998/10/18 by T.Soneoka */
**	if ((InputWORD(GA_PGBDR) & IO_BIT_TXIL) /* Scanner Cover Open */
**		|| (InputWORD(GA_PGBDR) & IO_BIT_XDS2)) {
		rtn = FALSE;
	} else {
		rtn = TRUE;
	}
#else
	if (!TXIL() && DS2()) {
		rtn = TRUE;
	} else {
		rtn = FALSE;
	}
#endif
	return	rtn;
}

/*
 *	Name:	Watch Raw Mode DSB4
 *	Create:	Mon Dec 15 14:42:28 1997	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	DsB4Raw(void);
 *	Description:
 *		Raw Mode で DSB4 をチェック
 *	Return Value:
 *		TRUE:	DSB4 is ON(原稿有り)
 *		FALSE:	DSB4 is OFF(原稿無し)
 *	Change Log:
 *		
 */
BOOL	DsB4Raw(void)
{
	BOOL	rtn;						/* Return Value */


#if (0)	/* 1998/10/18 by T.Soneoka */
**	if ((InputWORD(GA_PGBDR) & IO_BIT_TXIL) /* Scanner Cover Open */
**		|| (InputWORD(GA_PGBDR) & IO_BIT_XDB4)) {
#else
	if (!TXIL() || PB4()) {
#endif
		rtn = FALSE;
	} else {
		rtn = TRUE;
	}
	return	rtn;
}

/*
 *	Name:	Query Ds1 is ON
 *	Create:	Wed Feb 18 19:28:18 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	QueryDs1On(void);
 *	Description:
 *		DS1 が ON してるかどうかを返す
 *		チャタリング対策済
 *	Return Value:
 *		TRUE:	DS1 is ON(原稿有り)
 *		FALSE:	DS1 is OFF(原稿無し)
 *	Change Log:
 *		
 */
BOOL	QueryDs1On(void)
{
	return	CookedDs1;
}

/*
 *	Name:	Query Ds2 is ON
 *	Create:	Wed Feb 18 19:28:18 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	QueryDs2On(void);
 *	Description:
 *		DS2 が ON してるかどうかを返す
 *		チャタリング対策済
 *	Return Value:
 *		TRUE:	DS2 is ON(原稿有り)
 *		FALSE:	DS2 is OFF(原稿無し)
 *	Change Log:
 *		
 */
BOOL	QueryDs2On(void)
{
	return	CookedDs2;
}

/*
 *	Name:	Query DS B4 is ON
 *	Create:	Wed Feb 18 19:28:18 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	QueryDsB4On(void);
 *	Description:
 *		DS B4 が ON してるかどうかを返す
 *		チャタリング対策済
 *	Return Value:
 *		TRUE:	DS B4 is ON(原稿有り)
 *		FALSE:	DS B4 is OFF(原稿無し)
 *	Change Log:
 *		
 */
BOOL	QueryDsB4On(void)
{
	return	CookedDsB4;
}

/*
 *	Name:	Watch Cooked Mode DS1
 *	Create:	Mon Dec 15 14:42:28 1997	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	Ds1Changed(void);
 *	Description:
 *		Cooked Mode で DS1 をチェック,結果は CookedDs1
 *		ただし、チャタリング防止時間はコールされるタイミングに依存
 *		チャタリング防止時間連続して以前記憶したステータスと違えば,
 *		記憶を更新。
 *	Return Value:
 *		TRUE:	DS1 変化あり
 *		FALSE:	DS1 変化無し
 *	Change Log:
 *		
 */
BOOL	Ds1Changed(void)
{
	BOOL	CurrentDs1;			/* 現在のセンサー状態 */
	BOOL	rtn;

	rtn = FALSE;
	CurrentDs1 = Ds1Raw();
	if (CookedDs1 != CurrentDs1) {
		if (--Ds1CookCounter <= 0) { /* チャタリング防止の為のカウンター減算 */
			Ds1CookCounter = ScanChatCount;
			CookedDs1 = CurrentDs1; /* 現在の状態を記憶 */
			rtn = TRUE;
		}
	} else {
		Ds1CookCounter = ScanChatCount;
	}
	return	rtn;
}

/*
 *	Name:	Watch Cooked Mode DS2
 *	Create:	Mon Dec 15 14:42:28 1997	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	Ds2Changed(void);
 *	Description:
 *		Cooked Mode で DS2 をチェック,結果は CookedDs2
 *		ただし、チャタリング防止時間はコールされるタイミングに依存
 *		チャタリング防止時間連続して以前記憶したステータスと違えば,
 *		記憶を更新。
 *	Return Value:
 *		TRUE:	DS2 変化あり
 *		FALSE:	DS2 変化無し
 *	Change Log:
 *		
 */
BOOL	Ds2Changed(void)
{
	BOOL	CurrentDs2;			/* 現在のセンサー状態 */
	BOOL	rtn;

	rtn = FALSE;
	CurrentDs2 = Ds2Raw();
	if (CookedDs2 != CurrentDs2) {
		if (--Ds2CookCounter <= 0) { /* チャタリング防止の為のカウンター減算 */
			Ds2CookCounter = ScanChatCount;
			CookedDs2 = CurrentDs2; /* 現在の状態を記憶 */
			rtn = TRUE;
		}
	} else {
		Ds2CookCounter = ScanChatCount;
	}
	return	rtn;
}

/*
 *	Name:	Watch Cooked Mode DSB4
 *	Create:	Mon Dec 15 14:42:28 1997	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	DsB4Changed(void);
 *	Description:
 *		Cooked Mode で DSB4 をチェック,結果は CookedDsB4
 *		ただし、チャタリング防止時間はコールされるタイミングに依存
 *		チャタリング防止時間連続して以前記憶したステータスと違えば,
 *		記憶を更新。
 *	Return Value:
 *		TRUE:	DSB4 変化あり
 *		FALSE:	DSB4 変化無し
 *	Change Log:
 *		
 */
BOOL	DsB4Changed(void)
{
	BOOL	CurrentDsB4;		/* 現在のセンサー状態 */
	BOOL	rtn;

	rtn = FALSE;
	CurrentDsB4 = DsB4Raw();
	if (CookedDsB4 != CurrentDsB4) {
		if (--DsB4CookCounter <= 0) { /* チャタリング防止の為のカウンター減算 */
			DsB4CookCounter = ScanChatCount;
			CookedDsB4 = CurrentDsB4; /* 現在の状態を記憶 */
			rtn = TRUE;
		}
	} else {
		DsB4CookCounter = ScanChatCount;
	}
	return	rtn;
}


/*
 *	Name:	Watch Raw Mode InterLock for Scanner
 *	Create:	Mon Dec 15 14:42:28 1997	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	InterLock4ScanRaw(void);
 *	Description:
 *		Raw Mode で Scanner 側 InterLock をチェック
 *	Return Value:
 *		TRUE:	InterLock is ON(Close)
 *		FALSE:	InterLock is OFF(Open)
 *	Change Log:
 *		
 */
BOOL	InterLock4ScanRaw(void)
{
	BOOL	rtn;				/* Return Value */

	if (TXIL()) {
		rtn = FALSE;
	} else {
		rtn = TRUE;
	}
	return	rtn;
}

/*
 *	Name:	Query Close Inter Lock for Scanner
 *	Create:	Wed Feb 18 19:28:18 1998	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	QueryCloseInterLock4Scan(void);
 *	Description:
 *		Scanner InterLock が ON してるかどうかを返す
 *		チャタリング対策済
 *	Return Value:
 *		TRUE:	InterLock is ON(Close)
 *		FALSE:	InterLock is OFF(Open)
 *	Change Log:
 *		
 */
BOOL	QueryCloseInterLock4Scan(void)
{
	/*
	** 原稿蓄積中にカバーオープンをすると、ＴＸモータがまわりっぱなしになる
	** マシンステータスをみるように変更します
	** 1999/02/26 by T.Soneoka
	*/
#if (0)
**	return	CookedInterLock4Scan;
#else
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN) {
		return (FALSE);
	} else {
		return (TRUE);
	}
#endif
}

/*
 *	Name:	Watch Cooked Mode InterLock for Scanner
 *	Create:	Mon Dec 15 14:42:28 1997	by	ishiyama
 *	Synopsis:
 *		#include	"feeder.h"
 *		BOOL	InterLock4ScanChanged(void);
 *	Description:
 *		Cooked Mode で スキャナ側InterLock をチェック,結果は CookedInterLock4Scan
 *		ただし、チャタリング防止時間はコールされるタイミングに依存
 *		チャタリング防止時間連続して以前記憶したステータスと違えば,
 *		記憶を更新。
 *	Return Value:
 *		TRUE:	InterLock 変化あり
 *		FALSE:	InterLock 変化無し
 *	Change Log:
 *		
 */
BOOL	InterLock4ScanChanged(void)
{
	BOOL	CurrentInterLock;			/* 現在のセンサー状態 */
	BOOL	rtn;

	rtn = FALSE;
	CurrentInterLock= InterLock4ScanRaw();
	if (CookedInterLock4Scan != CurrentInterLock) {
		if (--InterLock4ScanCookCounter <= 0) { /* チャタリング防止の為のカウンター減算 */
			InterLock4ScanCookCounter = ScanChatCount;
			CookedInterLock4Scan = CurrentInterLock; /* 現在の状態を記憶 */
			rtn = TRUE;
		}
	} else {
		InterLock4ScanCookCounter = ScanChatCount;
	}
	return	rtn;
}
