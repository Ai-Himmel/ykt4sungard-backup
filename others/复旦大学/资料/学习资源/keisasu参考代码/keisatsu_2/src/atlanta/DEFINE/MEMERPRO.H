/************************************************************************
*	System		: POPLAR
*	File Name	: MEMERPRO.C
*	Author		: Y.Suzuki
*	Date		: 1997/3/31
*	Description	:内蔵部ＲＯＭから外部ＲＯＭ内のモジュールを参照するため
*				 外部ＲＯＭの固定アドレスでコールするため
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\MEM_DEF.H"

/* memread.c */
UWORD MEM_ReadGetNextBlockNoERom(UWORD);
UBYTE *MEM_CalculateSoftAddressERom(UWORD);
/* memwrite.c */
UWORD MEM_WriteGetNextBlkNoERom(struct MEM_ExecData_t *);

