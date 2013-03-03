/************************************************************************
*	System		: ＥＶＡ
*	File Name	: key_scn.c
*	Author		: 石橋正俊
*	Date		: 1997/10/24
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: キースキャン
*	Maintenance	: \prj\eva\src\pnl\key_scn.cからコピーし、HINOKI用にメンテしました
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\opr\ank\ext_v\opr_data.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"

/*************************************************************************
	module		:[キースキャン]
	function	:[1.5msecに一回キー入力があるかないかポートをスキャンする。
				  2.2回のスキャンで同じキー入力があった場合に入力ありと判断し
					イベントを発行する。
	]
	return		:[]
	common		:[]
	comment		:[旧key_int.c]
*************************************************************************/
void KeyScan(void)
{
	/*----------------------*/
	/* キーポートのスキャン */
	/*----------------------*/
#if (0)
** 	/* 読み取り中に連続的にキーを入力すると、NackBuzzerがなることがある。
** 	** 実際は、パネルから”００”をもらってきているためである。
** 	** よって、ここで、NewKeyが”００”の場合は以下の処理を行わないこととする。
** 	** by O.Kimoto 1999/01/12
** 	*/
** 	if (NewKeyData != NewKey) {
** 		/*------------------------*/
** 		/* キーが同じでない		  */
** 		/*------------------------*/
** 		NewKeyData = NewKey;		/* キーデータのセーブ */
** 		if (NewKeyData & 0x7F) {	/* ShiftKeyをマスク */
** 			idet_evt(EVT_KEY_DECIDE);
** 		}
** 	}
#else

#if (0)
** 		/* 連続的にキーを押すとなぜかナックブザーが鳴る？
** 		** 大域変数のセット位置を変更
** 		** by O.kimoto 1999/02/26
** 		*/
	if (NewKeyData != NewKey) {
		/*------------------------*/
		/* キーが同じでない		  */
		/*------------------------*/
		NewKeyData = NewKey;		/* キーデータのセーブ */
		if (NewKey != 0x00) {
			if (NewKeyData & 0x7F) {	/* ShiftKeyをマスク */
				idet_evt(EVT_KEY_DECIDE);
			}
		}
	}
#else
	if (BeforeNewKey != NewKey) {
		/*------------------------*/
		/* キーが同じでない		  */
		/*------------------------*/
		BeforeNewKey = NewKey;		/* キーデータのセーブ */
		if (NewKey != 0x00) {
			NewKeyData = NewKey;		/* キーデータのセーブ */
			if (NewKeyData & 0x7F) {	/* ShiftKeyをマスク */
				idet_evt(EVT_KEY_DECIDE);
			}
		}
	}
#endif

#endif

}
