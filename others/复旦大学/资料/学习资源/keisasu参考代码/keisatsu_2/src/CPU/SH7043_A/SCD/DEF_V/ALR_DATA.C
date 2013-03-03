/************************************************************************
*	System		: POPLAR
*	File Name	: ALR_DATA.C
*	Author		: Y.Suzuki
*	Date		: 1998/3/9
*	Description	: These parameters are used by Aliroo's module.
*				maximum size of sram is 64 byte.
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#pragma section ALR2 /* locate section name "DALR2" By Y.Suzuki 1998/03/09 */

/* initialized data section name is DALR2 */
DWORD AlrTempData = 0;

/* non-initialized data section name is BALR2 By Y.Suzuki 1998/04/28 */
DWORD AlrTempData2;

#pragma section /* locate section name "DALR2" "BALR2 */
