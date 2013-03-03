/************************************************************************
*	System			: POPLAR_H
*	File Name		: LCD_BUF.C
*	Author			: 木元修
*	Date			: 1997/07/19
*	RealTimeOS		: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description		: LCD RAMアクセスのためのバッファ
*	Original File	: jun\usr1:\src\rice\v53\def_v\lcd_buf.c
*	Maintenance		: 1997/07/19 ICHOUより移植 By O.Kimoto
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
/*************************************************
	LCD RAMアクセスのためのバッファ
		lcd_buf.c
								石橋正和
*************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\opr\kanji\define\lcd_def.h"

#if (PRO_CPU == SH7043)
	/*
	** RISCコンパイラー用のデータセクションを設定します。
	** MEMINDEXはDMEMINDEXの名前が自動的に設定されます。
	** 86系のセグメント名に相当する。
	** By S.Kawasaki 1996/03/11
	*/
	#pragma	section	LCDBUF
#endif

struct LCD_DisplayData_t LCD_PageRAM[4] = {0};

#if (PRO_CPU == SH7043)
	#pragma	section
#endif

