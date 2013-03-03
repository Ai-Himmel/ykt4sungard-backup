/************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: KEYCODE.H
*	Author		: 渡辺一章
*	Date		: 1996/10/17
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: キーコード定義
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
/* POPLAR_Hと共通化するために、従来の定義文を下記ディレクトリに移動しました。
**     \src\atlanta\opr\ank\define\keycode.h"
** By O.Kimoto 1997/07/16*/

#if (PRO_PANEL == ANK)					/* ANK対応操作パネル */
#include "\src\atlanta\opr\ank\define\keycode.h"
#endif
#if (PRO_PANEL == KANJI)				/* 漢字対応操作パネル */
#include "\src\atlanta\opr\kanji\define\keycode.h"
#endif
