/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_STR.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ”’lA•¶š—ñ‘€ì
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include 	"\src\atlanta\define\std.h"

#include	"\src\atlanta\define\lst_def.h"
#include	"\src\atlanta\define\lst_pro.h"

#if (0)
/*@-s**************************************************************************
**@-1	”’lA‚P‚Ui•¶š•Ï
**@-2	”’l‚ğ‚P‚Ui‚Ì•¶š‚É•ÏŠ·‚·‚é
**@-3	CharToHexString()
**@-4	uchar		OneChar			•ÏŠ·”’l
**@-5	UBYTE	‚P‚Ui•¶š—ñ
**@-6	—áFOnechar =  1‚ÌAØÀ°İ‚Í'1'(0x31)
**@-6		onechar = 10‚ÌAØÀ°İ‚Í'A'(0x41)
**@-e*************************************************************************/
UBYTE	CharToHexString( UBYTE OneChar )
{
	if ( OneChar < 10 ) {
		return ( (UBYTE)( OneChar+'0' ) );
	}
	else {
		return ( (UBYTE)( OneChar+'A'-10 ) );
	}
	return ( 0 );
}

/*@-s**************************************************************************
**@-1	‚WËŞ¯ÄMSB,LSB”½“]•¶š•ÏŠ·
**@-2	‚WËŞ¯ÄÃŞ°À‚ÌMSB,LSB‚ğ”½“]
**@-3	BitRoll()
**@-4	uchar		Data			T30ÃŞ°À
**@-5	uchar	•ÏŠ·Œ‹‰Ê•¶š
**@-6	—áFData=0x38(00111000B)‚È‚çAØÀ°İ‚Í0x1c(00011100B)
**@-e*************************************************************************/
UBYTE		BitRoll( UBYTE Data )
{
	UBYTE	ret;

	ret = 0;
	/*‰ºˆÊ‚SËŞ¯Ä*/
	if ( (Data & 0x01) != 0 ) {
		ret += 0x08;
	}
	if ( (Data & 0x02) != 0 ) {
		ret += 0x04;
	}
	if ( (Data & 0x04) != 0 ) {
		ret += 0x02;
	}
	if ( (Data & 0x08) != 0 ) {
		ret += 0x01;
	}
	/*ãˆÊ‚SËŞ¯Ä*/
	if ( (Data & 0x10) != 0 ) {
		ret += 0x80;
	}
	if ( (Data & 0x20) != 0 ) {
		ret += 0x40;
	}
	if ( (Data & 0x40) != 0 ) {
		ret += 0x20;
	}
	if ( (Data & 0x80) != 0 ) {
		ret += 0x10;
	}
	return ( ret );
}

#endif

