/*
**	%W%
**	File Name:	\prj\Eva\src\def\buf.c
**	Create:	1997/12/24	by Masahiro,IIDA
**	Description:
**		G/Aが使用するバッファ
**	Changes:
**
*/
#include "\src\atlanta\define\product.h"

#pragma section GA_BUF		/* セクション指定 */
UBYTE SmoothingBuffer[3][256] = {0};		/* G/A使用スムージング・バッファ */
UBYTE PrinterBuffer[2][256] = {0}; 			/* G/A使用プリンタ・バッファ */
UBYTE ScanBuf[16][256] = {0};
#pragma section
