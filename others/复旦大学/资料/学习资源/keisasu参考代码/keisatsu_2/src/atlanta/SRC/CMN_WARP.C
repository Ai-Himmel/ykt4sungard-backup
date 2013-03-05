/************************************************************************
*	System		: SAKAKIL
*	File Name	: CMN_WARP.C
*	Author		: 桑原美紀
*	Date		: 1998/09/02
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニタ
*	Description	:
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\syswarp.h"

#if (PRO_RX_DOC_TRANSFER == ENABLE)
/*************************************************************************
	module		:[ワープ機能の指定時間内かを調べる]
	function	:[
	]
	return		:[
			TRUE	:指定時間範囲内
			FALSE	:指定時間範囲外
]
	common		:[
]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/08/28]
	author		:[桑原美紀]
*************************************************************************/
UBYTE	CMN_CheckWarpRange(
			struct SYS_SubDialData_t *Warp,
			UDWORD	ReceiveTime)
{
	UBYTE	rx_week;
	UBYTE	s_week;
	UBYTE	e_week;
	UBYTE	is_week;
	UWORD	rx_time;
	UWORD	s_time;
	UWORD	e_time;
	TIME_DATA_t set; /** セット時刻 */

	if (Warp->Status == SYS_WARP_EMPTY) {	/* 未使用の時 */
		return( FALSE );
	}

	/* 受信した時間をワークに展開 */
	CMN_LongTimeToBCD((TIME_DATA_t *)&set, ReceiveTime);
	rx_time = (UWORD)(CMN_BCD_ToDecimal( set.Hour ) * 60);
	rx_time += (UWORD)CMN_BCD_ToDecimal( set.Minute );
	rx_week = set.Week - 1;

	s_week = Warp->StartWeek;
	e_week = Warp->EndWeek;
	s_time = Warp->StartTime;
	e_time = Warp->EndTime;

	is_week	= 0;
	if (s_week == SYS_NO_DAY) {		/* 曜日指定無し */
		s_week = SYS_NICHI;
		e_week = SYS_DOU;
		is_week	= 1;
	}

	if (s_time == 0xFFFF) {	/* 時刻指定無し */
		s_time = 0;			/* "00:00"をセット */
		e_time = 1439;		/* "23:59"をセット */
	}

	if (is_week == 1) {		/** 曜日指定無し */
		if (s_time <= e_time) {
			if ((s_time <= rx_time) &&
				(rx_time <= e_time)) {
				return( TRUE );
			}
			else {
				return( FALSE );
			}
		}
		else {
			if ((s_time <= rx_time) ||
				(rx_time <= e_time)) {
				return( TRUE );
			}
			else {
				return( FALSE );
			}
		}
	}

	if (s_week == e_week) {		/** 開始曜日と終了曜日が同じ */
		if (s_time <= e_time) {
			if (s_week == rx_week) {
				if ((s_time <= rx_time) && (rx_time <= e_time)) {
					return( TRUE );
				}
				else {
					return( FALSE );
				}
			}
			else {
				return( FALSE );
			}
		}
		else {
			if (s_week == rx_week) {
				if ((s_time <= rx_time) || (rx_time <= e_time)) {
					return( TRUE );
				}
				else {
					return( FALSE );
				}
			}
			else {
				if (s_week == rx_week) {
					if ((s_time <= rx_time) && (rx_time <= e_time)) {
						return( TRUE );
					}
					else {
						return( FALSE );
					}
				}
				else {
					return( TRUE );
				}
			}
		}
	}
	else if (s_week < e_week) {	/** 開始曜日の方が先 */
		if ((s_week > rx_week ) || (rx_week > e_week)) {
			return( FALSE );
		}
		else {
			if (s_week == rx_week) {
				if (s_time <= rx_time) {
					return( TRUE );
				}
				else {
					return( FALSE );
				}
			}
			else {
				if (e_week == rx_week) {
					if (e_time >= rx_time) {
						return( TRUE );
					}
					else {
						return( FALSE );
					}
				}
				else {
					return( TRUE );
				}
			}
		}
	}
	else {						/** 終了曜日の方が先 */
		if ((s_week > rx_week) && (rx_week > e_week)) {
			return( FALSE );
		}
		else {
			if (s_week == rx_week) {
				if (s_time <= rx_time) {
					return( TRUE );
				}
				else {
					return( FALSE );
				}
			}
			else {
				if (e_week == rx_week) {
					if (e_time >= rx_time) {
						return( TRUE );
					}
					else {
						return( FALSE );
					}
				}
				else {
					return( TRUE );
				}
			}
		}
	}
}


/*************************************************************************
	module		:[コマンドデータの電話番号セット]
	function	:[
	]
	return		:[
]
	common		:[
]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/08/31]
	author		:[桑原美紀]
*************************************************************************/
void	CMN_SetDialData(
			struct	SYS_DialData_t	 *Dial,
			UBYTE	*Direct,
			UBYTE	*Onetouch,
			UBYTE	*Speed,
			UDWORD	Group)
{
	UBYTE	i;

	for (i = 0; i < SYS_DIRECT_DIAL_MAX; i++) {	/* 1998/10/06 By M.Kuwahara */
		Dial->Direct[0][i] = Direct[i];
	}
	for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
		Dial->Onetouch[i] = Onetouch[i];
	}
	for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
		Dial->Speed[i] = Speed[i];
	}
	Dial->Group = Group;
}



/*************************************************************************
	module		:[ワープ機能時の同時プリントＯＮ／ＯＦＦチェック]
	function	:[
	]
	return		:[
			TRUE	:同時プリントＯＮ
			FALSE	:同時プリントＯＦＦ
]
	common		:[
]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/09/02]
	author		:[桑原美紀]
*************************************************************************/
UBYTE	CMN_CheckWarpPrint(
				UBYTE	Option)		/* 同時プリントチェック項目値 */
{
	if (Option & WARP_OPTION_PRINT) {
		return(TRUE);
	}
	return(FALSE);
}


#endif	/* PRO_RX_DOC_TRANSFER == ENABLE */
