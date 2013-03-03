/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_CPH.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/06/12
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ˆÃ†‰»óM’Ê’m
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
	module		:[ˆÃ†‰»óM’Ê’mˆóü]
	function	:[ˆÃ†‰»óM’Ê’m‚ğˆóü‚·‚é]
	common		:[
		List			:
		SYB_CipherBox	:
	]
	condition	:[
	]
	commment	:[
	]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[96/06/12]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD		Print_CipherRecieve_Notice( void )
{
	UBYTE	cipher_no;				/* óM‚m‚ */
	register WORD	ret;			/*ÀsŒ‹‰Ê*/

#if (0)			/* ‘®•ÏX 97/12/12 By M.Kuwahara */
	/* ‚Ps‰üs{”­MŒ³–¼C”­MŒ³”Ô†{‚Qs‰üsˆóü{Œ©o‚µ{‚Ps‰üs */
// #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
//	if ( (ret = Print_Head1_Common( PWRD_CipherReceiveNotice_K,
//	 LST_NOT,20-1 )) != OK ) {
//		return ( ret );
//	}
//
// #else
//	if ( (ret = Print_Head1_Common( PWRD_CipherReceiveNotice,
//	  LST_XXX_TWI_XXX, 14 )) != OK ) {
//		return ( ret );
//	}
//
// #endif
#endif

	/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[19-1] = LST_KLINE7;
	CMN_MemorySet( &List.S.Print[20-1], 41, LST_KLINE_ );
	List.S.Print[61-1] = LST_KLINE9;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* |ˆÃ†‰»óM’Ê’m| */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[19-1] = LST_KLINEI;
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
/*	AttributeSet( &List.S.Print[33-1], &List.S.Attribute[33-1],
		 PWRD_CipherReceiveNotice_K, LST_NOT);By Y.Suzuki 1998/04/24 */
	AttributeSet( &List.S.Print[21-1], &List.S.Attribute[21-1],
		 PWRD_CipherReceiveNotice_K, LST_NOT);
#else
	AttributeSet( &List.S.Print[20-1], &List.S.Attribute[20-1],
		 PWRD_CipherReceiveNotice, LST_MES_TWI_XXX);
#endif
	List.S.Print[61-1] = LST_KLINEI;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[19-1] = LST_KLINE1;
	CMN_MemorySet( &List.S.Print[20-1], 41, LST_KLINE_ );
	List.S.Print[61-1] = LST_KLINE3;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*„¡„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„¢*/
	Print_CipherRecieve_List_Line( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*„ óM‚m‚„ ‚R„ */
	Print_CipherRecieve_List_Line( 1, List.S.Print, List.S.Attribute );
	for( cipher_no = 0; cipher_no < SYS_CIPHERBOX_MAX; cipher_no++ ){
		if( SYB_CipherBox[cipher_no].MessageStatus == SYS_CIPHERBOX_RCV_MSG ){
			break;
		}
	}
	CMN_UnsignedIntToASC( &List.S.Print[24-1], cipher_no, 1, '0' );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*„¤„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„£*/
	Print_CipherRecieve_List_Line( 2, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	return ( OK );
}

/*************************************************************************
	module		:[ˆÃ†‰»óM’Ê’mƒŠƒXƒgŒrüì¬]
	functiom	:[ˆÃ†‰»óM’Ê’mƒŠƒXƒgŒrü‚ğì¬‚·‚éB]
	common		:[]
	condition	:[
		Œrüí—Ş
		,	0 = †®†¢†¢†Î†¢†¢†¢†¢†¢†¢†²
		,	1 = †¤óM‚m‚D †¤ 	†¤
		,	1 = †¾†¢†¢†Ş†¢†¢†¢†¢†¢†¢†Æ
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/ 6/12]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
void	Print_CipherRecieve_List_Line(
						 UBYTE Category,			/*Œrüí—Ş*/
						 register UBYTE *AscString,	/*ˆóü•¶š—ñ*/
						 register UBYTE *AttString )/*Cü•¶š—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*„¡„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„¢*/
			List.S.Print[10-1]	= LST_KLINE7;
			CMN_MemorySet( &AscString[11-1], 16, LST_KLINE_ );
			AscString[22-1]	= LST_KLINE8;
			AscString[26-1] = LST_KLINE9;
			break;
		case 1:
			/*„ óM‚m‚„ ‚R„ */
			AscString[10-1]	= LST_KLINEI;
			AttributeSet( &AscString[11-1], &AttString[11-1], PWRD_ReceiveNo, LST_NOT );
			AscString[22-1]	= LST_KLINEI;
			AscString[26-1]	= LST_KLINEI;
			break;
		case 2:
			/*„¤„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„£*/
			List.S.Print[10-1]	= LST_KLINE1;
			CMN_MemorySet( &AscString[11-1], 16, LST_KLINE_ );
			AscString[22-1]	= LST_KLINE2;
			AscString[26-1] = LST_KLINE3;
			break;
	}
}

#endif	/* #if (PRO_CIPHER == ENABLE) */
