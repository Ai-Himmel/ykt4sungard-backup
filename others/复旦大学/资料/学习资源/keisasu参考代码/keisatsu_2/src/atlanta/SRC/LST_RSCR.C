/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_RCR.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: e“WŽóM’Ê’m
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"

#if ( PRO_PANEL == ANK )
#include "\src\atlanta\opr\ank\define\opr_def.h"
#endif
#if ( PRO_PANEL == KANJI )
#include "\src\atlanta\opr\kanji\define\opr_def.h"
#endif

/*************************************************************************
	module		:[e“WŽóM’Ê’mˆóü]
	function	:[e“WŽóM’Ê’m‚ðˆóü‚·‚é]
	common		:[
		SYB_MailBox	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD					Print_SecureRcv_Notice(
						 UBYTE MailboxNumber )/*e“WŽóMƒ{ƒbƒNƒX”Ô†*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs*/
	if ( (ret = TTI_ID_Print_Feed()) != OK ) {
		return ( ret );
	}

	/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[25-1] = LST_KLINE7;
	CMN_MemorySet( &List.S.Print[26-1], 31, LST_KLINE_ );
	List.S.Print[56-1] = LST_KLINE9;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¤ƒVƒ“ƒeƒ“ƒWƒ…ƒVƒ“@ƒcƒEƒ`†¤*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[25-1] = LST_KLINEI;
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		AttributeSet( &List.S.Print[28-1], &List.S.Attribute[28-1],
		 PWRD_SecureMailNotice_K, LST_NOT);		/* MES¨INV 94.7.20 ->NOT 8.10 */
#else
	AttributeSet( &List.S.Print[28-1], &List.S.Attribute[28-1],
	  PWRD_SecureMailNotice, LST_MES_TWI_XXX);

#endif

	List.S.Print[56-1] = LST_KLINEI;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[25-1] = LST_KLINE1;
	CMN_MemorySet( &List.S.Print[26-1], 31, LST_KLINE_ );
	List.S.Print[56-1] = LST_KLINE3;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/*Œ»ÝŽžŠÔ*/
	if ( (ret = CurrentTimePrint( 41-1 )) != OK ) {
		return ( ret );
	}

	/*†®†¢†¢†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†²*/
	Print_Secure_Notice_List( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¤No†¤¼ÝÃÝ¼¬Ò²†¤ ±²Ã»·Ò²@@†¤*/
	Print_Secure_Notice_List( 1, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¾†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Æ*/
	Print_Secure_Notice_List( 2, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¤9†¤xxxxxxxx†¤xxxxxxxxxxxx†¤*/
	Print_Secure_Notice_List( 3, List.S.Print, List.S.Attribute );
	/* No. */
#if ( PRO_CPU == SH7043 )	/* FX,MML‚Åe“WBOXNo.‚ªA0`or1`‚Æˆá‚¤Žž‚Ì‚½‚ß */
	CMN_UnsignedIntToASC( &List.S.Print[21-1], (UWORD)(MailboxNumber) + ( OPR_MAILBOX_MIN ),
	  2, ' ' );
#else
	CMN_UnsignedIntToASC( &List.S.Print[22-1], (UWORD)(MailboxNumber),
	  1, '0' );
#endif

	/*¼ÝÃÝ¼¬Ò²*/
	CMN_StringCopy( &List.S.Print[24-1], &SYB_MailBox[MailboxNumber].BoxName[0] );

	/*±²Ã»·Ò²*/
	CMN_StringCopy( &List.S.Print[41-1], &SYB_MailBox[MailboxNumber].RemoteName[0] );

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¶†¢†¢†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†º*/
	Print_Secure_Notice_List( 4, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* ¼ÝÃÝ ¹ÞÝº³¦ ¼Þ­¼Ý ¼Ï¼À ................*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[21-1], &List.S.Attribute[21-1],
	  PWRD_SecureMailReci, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* (¹ÞÝº³ Î¶Ý ·¶Ý)*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[21-1], &List.S.Attribute[21-1],
	  PWRD_MemHoldDate, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*yy-mm-dd (x) hh:mm */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CriterionMinuteToDayTimeAsc( SYB_MailBox[MailboxNumber].ErasedTime/60,
	  LST_YYMMDD, List.S.Work );
	if ( DateTypeGet() == JPN_CLOCK_TYPE ) {	/* JPN‚ÌŽž‚ÆA‚»‚êˆÈŠO‚ÌŠJŽnˆÊ’u‚ªˆÙ‚È‚é 1998/01/23 By M.Kuwahara */
		CMN_StringCopy( &List.S.Print[20], List.S.Work ); /** "18" -> "20" By M.Kuwahara 1998/01/23 */
		/*hh:mm*/
		CriterionMinuteToDayTimeAsc( SYB_MailBox[MailboxNumber].ErasedTime/60,
		  LST_DDHHMM, List.S.Work );
		CMN_StringCopy( &List.S.Print[35], &List.S.Work[3] ); /** "33" -> "35" By M.Kuwahara 1998/01/23 */
	}
	else {
		CMN_StringCopy( &List.S.Print[18], List.S.Work ); /** "21-1" -> "18" By H.Hirao 1996/07/09 */
		/*hh:mm*/
		CriterionMinuteToDayTimeAsc( SYB_MailBox[MailboxNumber].ErasedTime/60,
		  LST_DDHHMM, List.S.Work );
		CMN_StringCopy( &List.S.Print[33], &List.S.Work[3] ); /** "36-1" -> "33" By H.Hirao 1996/07/09 */
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	SYB_MailBox[MailboxNumber].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
	return ( OK );
}

/*************************************************************************
	module		:[e“W’Ê’m‚Ì‰¡‹æØ‚èŒrüì¬]
	function	:[e“W’Ê’m‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
		,	0 = †®†¢†Î†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†²
		,	1  =†¤No†¤		  †¤		@@†¤
		,	2 = †¾†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Æ
		,	3 = †¤	†¤		  †¤@@@@@@†¤
		,	4 = †¶†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†º
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
void			Print_Secure_Notice_List(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†Î†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†²*/
			AscString[20-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[21-1], 40, LST_KLINE_ );
			AscString[23-1] = LST_KLINE8;
			AscString[40-1] = LST_KLINE8;
			AscString[61-1] = LST_KLINE9;
			break;
		case 1:
			/*†¤No†¤¼ÝÃÝ¼¬Ò²†¤ ±²Ã»·Ò²@@†¤*/
			AttributeSet( &AscString[21-1], &AttString[21-1], PWRD_No,
			  LST_NOT );
			AttributeSet( &AscString[28-1], &AttString[28-1], PWRD_UserName,
			  LST_NOT );
			AttributeSet( &AscString[47-1], &AttString[47-1], PWRD_RemoteFrom,
			  LST_NOT );
			AscString[20-1] = LST_KLINEI;
			AscString[23-1] = LST_KLINEI;
			AscString[40-1] = LST_KLINEI;
			AscString[61-1] = LST_KLINEI;
			break;
		case 2:
			/*†¾†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Æ*/
			AscString[20-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[21-1], 40, LST_KLINE_ );
			AscString[23-1] = LST_KLINE5;
			AscString[40-1] = LST_KLINE5;
			AscString[61-1] = LST_KLINE6;
			break;
		case 3:
			/*†¤  †¤		†¤@@@@@@†¤*/
			AscString[20-1] = LST_KLINEI;
			AscString[23-1] = LST_KLINEI;
			AscString[40-1] = LST_KLINEI;
			AscString[61-1] = LST_KLINEI;
			break;
		case 4:
			/*†¶†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†º*/
			AscString[20-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[21-1], 40, LST_KLINE_ );
			AscString[23-1] = LST_KLINE2;
			AscString[40-1] = LST_KLINE2;
			AscString[61-1] = LST_KLINE3;
			break;
	}
}

