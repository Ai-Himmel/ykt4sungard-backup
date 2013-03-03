/************************************************************************
*	System			: POPLAR_H
*	File Name		: LCD_BUF.H
*	Author			: 木元修
*	Date			: 1997/07/19
*	RealTimeOS		: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description		: LCD RAMアクセスのためのバッファ
*	Original File	: jun\usr1:\src\rice\v53\ext_v\lcd_buf.hv
*	Maintenance		: 1997/07/19 ICHOUより移植 by O.Kimoto
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
/*************************************************
	LCD RAMアクセスのためのバッファ
		lcd_buf.h
								石橋正和
*************************************************/
/* #include "\src\ichou\define\lcd_def.hv" */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\opr\kanji\define\lcd_def.h"

extern struct LCD_DisplayData_t LCD_PageRAM[4];

