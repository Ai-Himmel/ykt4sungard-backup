/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_CPH.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/06/13
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒL[ƒoƒ“ƒNƒŠƒXƒg
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysmax.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"

#if (PRO_CIPHER == ENABLE)
/*************************************************************************
	module		:[ƒL[ƒoƒ“ƒNƒŠƒXƒgˆóü]
	function	:[ƒL[ƒoƒ“ƒNƒŠƒXƒg‚ðˆóü‚·‚é]
	common		:[
		List			:
		SYB_KeyBookData	:
	]
	condition	:[
	]
	commment	:[
	]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[96/06/13]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD		Print_KeyBook_List( void )
{
	UBYTE	i;						/* ‚m‚ */
	register WORD	ret;			/*ŽÀsŒ‹‰Ê*/

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/* ‚Ps‰üs{”­MŒ³–¼C”­MŒ³”Ô†{‚Qs‰üsˆóü{Œ©o‚µ{‚Ps‰üs */
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
/*	if ( (ret = Print_Head1_Common( PWRD_KeyBookList_K, LST_NOT,29-1 )) != OK ) { @* 26 -> 29 98/01/13 By M.Kuwahara */
	if ( (ret = Print_Head1_Common( PWRD_KeyBookList_K, LST_NOT,23-1 )) != OK ) { /* 29 -> 23 98/04/24 By Suzuki */
		return ( ret );
	}

#else
	if ( (ret = Print_Head1_Common( PWRD_KeyBookList, LST_XXX_TWI_XXX, 20-1 )) != OK ) {
		return ( ret );
	}

#endif

	/* Œ»ÝŽž */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	TimeDataAscii( OFF, SYB_CurrentTime, List.S.Work, 0 );
	CMN_StringCopy( &List.S.Print[30-1], List.S.Work );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*„¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢*/
	Print_KeyBook_List_Line( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*„ ‚m‚„ ƒL[‚Ì–¼‘O	„ */
	Print_KeyBook_List_Line( 1, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	for ( i = 0; i < SYS_KEY_BOOK_MAX; i++ ) {
		if ( SYB_KeyBookData.SYB_KeyData[i].Key[0] != 0x00 ){
			/* „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§ */
			Print_KeyBook_List_Line( 2, List.S.Print, List.S.Attribute );
			if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			/* „  9„ xxxxxxxxxxxxxxxx„  */
			Print_KeyBook_List_Line( 3, List.S.Print, List.S.Attribute );
			CMN_UnsignedIntToASC( &List.S.Print[32-1], (UWORD)i, 1, '0' );
			CMN_StringCopy( &List.S.Print[34-1], SYB_KeyBookData.SYB_KeyData[i].KeyName );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
	}

	/*„¤„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„£*/
	Print_KeyBook_List_Line( 4, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

/*************************************************************************
	module		:[ƒL[ƒuƒbƒNƒŠƒXƒgŒrüì¬]
	functiom	:[ƒL[ƒuƒbƒNƒŠƒXƒgŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
		,	0 = †®†¢†¢†Î†¢†¢†¢†¢†¢†¢†¢†¢†²
		,	1 = †¤‚m‚D†¤ƒL[‚Ì–¼‘O 	†¤
		,	2 = †¾†¢†¢†Þ|†¢†¢†¢†¢†¢†¢†¢†¢
		,	2 = †¾†¢†¢†Þ†¢†¢†¢†¢†¢†¢†¢†¢†Æ
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/ 6/13]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
void	Print_KeyBook_List_Line(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*„¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢*/
			List.S.Print[29-1]	= LST_KLINE7;
			CMN_MemorySet( &AscString[30-1], 20, LST_KLINE_ );
			AscString[33-1]	= LST_KLINE8;
			AscString[50-1] = LST_KLINE9;
			break;
		case 1:
			/*„ ‚m‚.„ ƒL[‚Ì–¼‘O        „ */
			AscString[29-1]	= LST_KLINEI;
			AttributeSet( &AscString[30-1], &AttString[30-1], PWRD_No, LST_NOT );
			AscString[33-1]	= LST_KLINEI;
			AttributeSet( &AscString[36-1], &AttString[36-1], PWRD_KeyName, LST_NOT );
			AscString[50-1]	= LST_KLINEI;
			break;
		case 2 :
			/*	„¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§ */
			AscString[29-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[30-1], 20, LST_KLINE_);
			AscString[33-1] = LST_KLINE5;
			AscString[50-1] = LST_KLINE6;
			break;
		case 3:
			/*„  	„ 			        „ */
			AscString[29-1]	= LST_KLINEI;
			AscString[33-1]	= LST_KLINEI;
			AscString[50-1]	= LST_KLINEI;
			break;
		case 4:
			/*„¤„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„£*/
			List.S.Print[29-1]	= LST_KLINE1;
			CMN_MemorySet( &AscString[30-1], 20, LST_KLINE_ );
			AscString[33-1]	= LST_KLINE2;
			AscString[50-1] = LST_KLINE3;
			break;
	}
}

#endif	/* #if (PRO_CIPHER == ENABLE) */
