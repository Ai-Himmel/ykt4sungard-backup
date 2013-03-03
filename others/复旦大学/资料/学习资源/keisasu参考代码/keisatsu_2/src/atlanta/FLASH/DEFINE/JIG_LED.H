/************************************************************************
*	System		: 
*	File Name	: JIG_LED.H
*	Author		: Masahiro Iida
*	Date		: 1999/10/15
*	Description	: 
*	Maintenance	:
*	Copyright (C) 1998 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#ifndef JIG_LED_H
 #define JIG_LED_H

#include	"\src\atlanta\define\product.h"

#if (PRO_NEW_JIG == ENABLE)		/* 白樺用梱包状態で書き換え可能治具 */
/* Write Port */
#define PORT_ROM_NO_LED				0x00080000
#define PORT_LEFT_SUM_LED_HIGH		0x00080002
#define PORT_LEFT_SUM_LED_LOW		0x00080004
#define PORT_RIGHT_SUM_LED_HIGH		0x00080006
#define PORT_RIGHT_SUM_LED_LOW		0x00080008

/* Read Port */
#define PORT_CGROM_SWITCH			0x00080018
	#define IS_CGROM_BIT			0x0001		/* 0:CGROM書換無 1:CGROMも書換 */
	#define DISPLAY_ROMSW_BIT		0x0002		/* 0:ROM0/1表示 1:ROM2/3表示 */
/* ROM Number define */
#define	ROM_NUMBER0		0
#define	ROM_NUMBER1		1
#define	ROM_NUMBER2		2
#define	ROM_NUMBER3		3
#define	CGROM_NUMBER0	4
#define	CGROM_NUMBER1	5

#define	JIG_LED_MAX		2

struct JIG_Led_t {
	UWORD *UpperAddress;
	UWORD *LowerAddress;
};

#endif	/* (PRO_NEW_JIG == ENABLE) */
#endif	/* JIG_LED_H */
