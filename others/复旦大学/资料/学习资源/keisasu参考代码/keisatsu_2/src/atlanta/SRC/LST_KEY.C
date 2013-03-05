/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_CPH.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/06/13
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒL[ƒ[ƒhƒŠƒXƒg
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
#include	"\src\atlanta\ext_v\sys_data.h"

#if (PRO_CIPHER == ENABLE)
/*************************************************************************
	module		:[ƒL[ƒ[ƒhƒŠƒXƒgˆóü]
	function	:[ƒL[ƒ[ƒhƒŠƒXƒg‚ðˆóü‚·‚é]
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
WORD		Print_KeyWord_List( void )
{
	UBYTE	no;						/* ‚m‚ */
	register WORD	ret;			/*ŽÀsŒ‹‰Ê*/

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/* ‚Ps‰üs{”­MŒ³–¼C”­MŒ³”Ô†{‚Qs‰üsˆóü{Œ©o‚µ{‚Ps‰üs */
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
	if ( (ret = Print_Head1_Common( PWRD_KeyWordList_K, LST_NOT,26-1 )) != OK ) {
		return ( ret );
	}

#else
	if ( (ret = Print_Head1_Common( PWRD_KeyWordList, LST_XXX_TWI_XXX, 26-1 )) != OK ) {
		return ( ret );
	}

#endif
	no	= SYS_CipherKeyNo;
	/* "No.9     						Œ»ÝŽž" */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_No, LST_NOT );
	CMN_UnsignedIntToASC( &List.S.Print[5-1], (UWORD)no, 1, '0' );
	TimeDataAscii( OFF, SYB_CurrentTime, List.S.Work, 0 );
	CMN_StringCopy( &List.S.Print[58-1], List.S.Work );		/* 60-> 58 98/01/16 By M.Kuwahara */
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*„¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¢*/
	Print_KeyWord_List_Line( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*„ ‚m‚„ ƒL[‚Ì–¼‘O	„ ƒL[‚Ìƒqƒ“ƒg		„ ƒL[	„ */
	Print_KeyWord_List_Line( 1, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„§ */
	Print_KeyWord_List_Line( 2, List.S.Print, List.S.Attribute );
	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}


	/* „ xxxxxxxxxxxxxxxx„ xxxxxxxxxxxxxxxxxxxxxxxxxx„ xxxxxxxxxx„  */
	Print_KeyWord_List_Line( 3, List.S.Print, List.S.Attribute );
	CMN_StringCopy( &List.S.Print[2-1], SYB_KeyBookData.SYB_KeyData[no].KeyName );
	CMN_StringCopy( &List.S.Print[19-1], SYB_KeyBookData.SYB_KeyData[no].Key );
	CMN_StringCopy( &List.S.Print[44-1], SYB_KeyBookData.SYB_KeyData[no].KeyClue );	/* 45-> 44 98/01/16 By M.Kuwahara*/

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*„¤„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„£*/
	Print_KeyWord_List_Line( 4, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

/*************************************************************************
	module		:[ƒL[ƒŠƒXƒgŒrüì¬]
	functiom	:[ƒL[ƒŠƒXƒgŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
		,	0 = †®†¢†¢†Î†¢†¢†¢†¢†¢†¢†¢†¤†¤†¤†¤†¤†¤†¤†¤†¤†¤†¢†²
		,	1 = †¤‚m‚D†¤ƒL[‚Ì–¼‘O†¤ƒL[‚Ìƒqƒ“ƒg	†¤ƒL[	†¤
		,	2 = †¾†¢†¢†Þ| †¢†¢†¢†¢†¢†¢†¢†¢†¤†¤†¤†¤†¤†¤†¤†¤†¤†¤
		,	3 = †¾†¢†¢†Þ†¢†¢†¢†¢†¢†¤†¤†¤†¤†¤†¤†¤†¤†¤†¤†¢†¢†¢†Æ
			–ƒL[ƒ[ƒh‚Ìƒqƒ“ƒg‚ÆƒL[ƒ[ƒh‚ÌˆÊ’u‚ð“ü‚ê‘Ö‚¦ 97/12/12 By M.Kuwahara ***
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/ 6/13]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
void	Print_KeyWord_List_Line(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*„¡„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢*/
			List.S.Print[1-1]	= LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 77, LST_KLINE_ );	/* 79-> 77 98/01/16 By M.Kuwahara */
			AscString[18-1]	= LST_KLINE8;
			AscString[43-1]	= LST_KLINE8;		/* 44-> 43 98/01/16 By M.Kuwahara */
			AscString[78-1] = LST_KLINE9;		/* 80-> 78 98/01/16 By M.Kuwahara */
			break;
		case 1:
			/*„ ƒL[ƒ[ƒh‚Ì–¼‘O„ ƒL[ƒ[ƒh	„ ƒL[ƒ[ƒh‚Ìƒqƒ“ƒg „ */
			AscString[1-1]	= LST_KLINEI;
			AttributeSet( &AscString[4-1], &AttString[4-1], PWRD_KeyName, LST_NOT );
			AscString[18-1]	= LST_KLINEI;
			AttributeSet( &AscString[28-1], &AttString[28-1], PWRD_Key, LST_NOT );
			AscString[43-1]	= LST_KLINEI;		/* 44-> 43 98/01/16 By M.Kuwahara */
			AttributeSet( &AscString[56-1], &AttString[56-1], PWRD_KeyClue, LST_NOT );
			AscString[78-1]	= LST_KLINEI;		/* 80-> 78 98/01/16 By M.Kuwahara */
			break;
		case 2 :
			/*	„¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§ */
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 77, LST_KLINE_);	/* 79-> 77 98/01/16 By M.Kuwahara */
			AscString[18-1] = LST_KLINE5;
			AscString[43-1] = LST_KLINE5;		/* 44-> 43 98/01/16 By M.Kuwahara */
			AscString[78-1] = LST_KLINE6;		/* 80-> 78 98/01/16 By M.Kuwahara */
			break;
		case 3:
			/*„ 	„ 			    „ 				  „  				   „ */
			AscString[1-1]	= LST_KLINEI;
			AscString[18-1]	= LST_KLINEI;
			AscString[43-1]	= LST_KLINEI;		/* 44-> 43 98/01/16 By M.Kuwahara */
			AscString[78-1]	= LST_KLINEI;		/* 80-> 78 98/01/16 By M.Kuwahara */
			break;
		case 4:
			/*„¤„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„£*/
			List.S.Print[1-1]	= LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 77, LST_KLINE_ );	/* 79-> 77 98/01/16 By M.Kuwahara */
			AscString[18-1]	= LST_KLINE2;
			AscString[43-1]	= LST_KLINE2;		/* 44-> 43 98/01/16 By M.Kuwahara */
			AscString[78-1] = LST_KLINE3;		/* 80-> 78 98/01/16 By M.Kuwahara */
			break;
	}
}

#endif	/* #if (PRO_CIPHER == ENABLE) */
