/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_RX.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/04/16
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒTƒuƒAƒhƒŒƒXŽóM’Ê’m
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdial.h"

#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\lst_def.h"

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\lst_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\lst_data.h"
#include "\src\atlanta\ext_v\lst_wrd.h"

#if (PRO_F_CODE == ENABLE)
/*************************************************************************
	module		:[ƒTƒuƒAƒhƒŒƒXŒ´eŽóM’Ê’mˆóü]
	function	:[ƒTƒuƒAƒhƒŒƒXŒ´eŽóM’Ê’m‚ðˆóü‚·‚é]
	common		:[
		List					:
		SYB_SubAddressBoxTable	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/04/16]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD				Print_F_CodeBoxRcv_Notice(
						UBYTE	BoxNumber,				/*‚a‚‚˜*/
						UBYTE	FileNumber )			/*ƒtƒ@ƒCƒ‹”Ô†*/
{
	register WORD	ret;						/*ŽÀsŒ‹‰Ê*/

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs*/
	if ( (ret = TTI_ID_Print_Feed()) != OK ) {
		return ( ret );
	}

	/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[22-1] = LST_KLINE7;
	CMN_MemorySet( &List.S.Print[23-1], 35, LST_KLINE_ );
	List.S.Print[58-1] = LST_KLINE9;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* |‚eƒR[ƒhƒWƒ…ƒVƒ“  ƒcƒEƒ`| */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[22-1] = LST_KLINEI;
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
	AttributeSet( &List.S.Print[23-1], &List.S.Attribute[23-1],
		 PWRD_F_CodeBoxRsv_Notice_K, LST_NOT);
#else
	AttributeSet( &List.S.Print[23-1], &List.S.Attribute[23-1],
		 PWRD_F_CodeBoxRsv_Notice, LST_MES_TWI_XXX);
#endif

	List.S.Print[58-1] = LST_KLINEI;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[22-1] = LST_KLINE1;
	CMN_MemorySet( &List.S.Print[23-1], 35, LST_KLINE_ );
	List.S.Print[58-1] = LST_KLINE3;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* Œ»ÝŽžŠÔ */
	if (( ret = CurrentTimePrint( 47 - 1 )) != OK ) {
		return ( ret );
	}

	/* „¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„¦„Ÿ„Ÿ„¢ */
	Print_Del_F_Code_Notice_Line( 5, List.S.Print, List.S.Attribute );
	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* „ Box„ ÎÞ¯¸½–¼„  ‘ŠŽèæ–¼  	„ Ží—Þ„ Œ´eNo.„  */
	Print_Del_F_Code_Notice_Line( 6, List.S.Print, List.S.Attribute );
	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„©„Ÿ„Ÿ„§ */
	Print_Del_F_Code_Notice_Line( 7, List.S.Print, List.S.Attribute );
	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* „ 99„ xxxxxxx„ xxxxxxxxxxxxxxx„ xxxxxx„ xxxxxx„  */
	Print_Del_F_Code_Notice_Line( 8, List.S.Print, List.S.Attribute );
	/* ‚a‚‚˜ */
	CMN_UnsignedIntToASC( &List.S.Print[8-1], (UWORD)BoxNumber, 2, ' ' );
	/* ƒ{ƒbƒNƒX–¼ */
	CMN_StringCopy( &List.S.Print[12-1], SYB_SubAddressBoxTable[BoxNumber-1].BoxName );
	/* ‘ŠŽèæ–¼ */
	CMN_StringCopy( &List.S.Print[29-1], SYB_SubAddressBoxTable[BoxNumber-1].RemoteName );
	/* Ží—Þ */
	switch( SYB_SubAddressBoxTable[BoxNumber-1].Status ){
	case	SUB_ADDRESS_BULLETIN_BOX:		/* ŒfŽ¦”Â */
		CMN_StringCopy( &List.S.Print[51-1], PWRD_NoticeBoard );
		break;
	case	SUB_ADDRESS_SECURE_BOX:			/* e“W */
		CMN_StringCopy( &List.S.Print[51-1], PWRD_Secure );
		break;
	case	SUB_ADDRESS_RELAY_BOX:			/* ’†Œp */
		CMN_StringCopy( &List.S.Print[52-1], PWRD_Relay );
		break;
	default:
		break;
	}
	/* Œ´eNo. */
	CMN_UnsignedIntToASC( &List.S.Print[62-1], (UWORD)FileNumber, 2, ' ' );

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* „¤„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„¨„Ÿ„Ÿ„£	 */
	Print_Del_F_Code_Notice_Line( 9, List.S.Print, List.S.Attribute );
	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* "Fº°ÄÞÎÞ¯¸½¹ÞÝº³ ¦ ¼Þ­¼Ý ¼Ï¼À" */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_F_CodeReci, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	if( SYB_SubAddressBoxTable[BoxNumber-1].ErasedTime != 0xFFFFFFFF ){
		/* "(¼Þ­¼Ý ¹ÞÝº³ ·µ¸·¶Ý)" */
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_F_ReciDocMemory, LST_NOT );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*Á‹ŽŽžŠÔ*/
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		TimeDataAscii( OFF, SYB_SubAddressBoxTable[BoxNumber-1].ErasedTime, List.S.Work, 0 );
		CMN_StringCopy( &List.S.Print[7-1], List.S.Work );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}

	/* o—Íó‘Ô‚ðƒNƒŠƒA */
	/* ƒvƒŠƒ“ƒgI—¹Œã‚ÉƒƒCƒ“‚ÅƒNƒŠƒA‚·‚é 1997/04/24  By T.Yamaguchi */
/*	SYB_SubAddressBoxTable[BoxNumber].MessageStatus	= SYS_SUB_ADDRESS_BOX_MSG_EMPTY; */

	return ( OK );
}

#endif
