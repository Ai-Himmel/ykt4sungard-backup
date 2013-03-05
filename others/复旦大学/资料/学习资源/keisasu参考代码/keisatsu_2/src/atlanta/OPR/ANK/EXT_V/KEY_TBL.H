/************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: KEY_TBL.H
*	Author		: 渡辺一章
*	Date		: 1996/10/17
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: キーテーブル定義
*	Maintenance	: 1997/07/17 PRO_PANEL==ANK専用ファイルなので、
*	                         \src\atlanta\opr\ank\defineに移動します。by O.Kimoto
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef KEY_TBL_H
	#define KEY_TBL_H	1

#include	"\src\atlanta\define\product.h"


/*********************************************
 * キーポートテーブル	22Byte
 ********************************************/
#if (PRO_CPU == SH7043)
extern CONST UDWORD KeyPortTable[KEY_MATRICS_COLUM_MAX];
#endif

/********************************************
 * キーテーブル
 ********************************************/
extern CONST UBYTE *(KeyTable[ONETOUCH_SHEET_MAX]);

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 1998/09/22 by T.Soneoka */
	/********************************************
	 * キーテーブル１（シート１）
	 *******************************************/
	extern CONST UBYTE KeyTableSheet1[11][KEY_MATRICS_COLUM_MAX];
#else
	/********************************************
	 * キーテーブル１（シート１）
	 *******************************************/
	extern CONST UBYTE KeyTableSheet1[8][KEY_MATRICS_COLUM_MAX];

	/********************************************
	 * キーテーブル２（シート２）
	 *******************************************/
	extern CONST UBYTE KeyTableSheet2[8][KEY_MATRICS_COLUM_MAX];
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* 1998/09/22 by T.Soneoka */
	/*******************************************
	 * キータイプテーブル１（シート１）
	 *******************************************/
	extern CONST UBYTE KeyTypeTable1[11][KEY_MATRICS_COLUM_MAX];
#else
	/*******************************************
	 * キータイプテーブル１（シート１）
	 *******************************************/
	extern CONST UBYTE KeyTypeTable1[8][KEY_MATRICS_COLUM_MAX];

	/*******************************************
	 * キータイプテーブル２（シート２）
	 *******************************************/
	extern CONST UBYTE KeyTypeTable2[8][KEY_MATRICS_COLUM_MAX];
#endif

#endif
