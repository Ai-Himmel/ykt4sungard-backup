/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_SCR.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: e“WÒƒŠƒXƒg
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysmailb.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"

#if	( PRO_PANEL == ANK )
#include "\src\atlanta\opr\ank\define\opr_def.h"
#endif
#if	( PRO_PANEL == KANJI )
#include "\src\atlanta\opr\kanji\define\opr_def.h"
#endif

/*************************************************************************
	module		:[e“WÒØ½Ä]
	function	:[e“WÒØ½Ä‚ğˆóü‚·‚é]
	common		:[
		List		:
		SYB_MailBox	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŸ˜Y]
*************************************************************************/
WORD				Print_Mailbox_List(
						 void )				/*‚È‚µ*/
{
	UBYTE	i;						/*loop*/
	register WORD	ret;					/*ÀsŒ‹‰Ê*/

	/*ÃŞ°À‚È‚µÁª¯¸*/
	for ( i = 0; i < SYS_MAILBOX_MAX; i++ ) {
		if ( SYB_MailBox[i].Status != SYS_MAILBOX_NO_SET ) {
			break;
		}
	}
	if ( i == SYS_MAILBOX_MAX ) {
		return ( MSG_PRN_LST_NO_LIST );
	}

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs{Œ©o‚µ{‚P‰üs*/
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		if ( (ret = Print_Head1_Common( PWRD_SecureMailBList_K,
		 LST_NOT, 23 )) != OK ) {/** "1-1" -> "23" By M.Kuwahara 1997/02/12 */
			return ( ret );
		}
#else
	if ( (ret = Print_Head1_Common( PWRD_SecureMailBList,
	  LST_XXX_TWI_XXX, 18 )) != OK ) { /** "1-1" -> "18" By H.Hirao 1996/07/11 */
		return ( ret );
	}

#endif

	/*Œ»İŠÔ*/
	if ( (ret = CurrentTimePrint( 30 )) != OK ) { /** "8-1" -> "30" By H.Hirao 1996/07/11 */
		return ( ret );
	}

	/*†®†¢†Î†¢†¢†¢†¢†¢†²*/
	Print_Mailbox_List_Line( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¤ Box†¤¼İÃİ¼¬Ò²†¤*/
	Print_Mailbox_List_Line( 1, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	for ( i = 0; i < SYS_MAILBOX_MAX; i++ ) {
		if ( SYB_MailBox[i].Status != SYS_MAILBOX_NO_SET ) {
			/*†¾†¢†¢†Ş†¢†¢†¢†Æ*/
			Print_Mailbox_List_Line( 2, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤ 9 †¤xxxxxx†¤*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[29] = LST_KLINEI; /** "7-1" -> "29" By H.Hirao 1996/07/11 */
#if ( PRO_CPU == SH7043 )	/* FX,MML‚Åe“WBOXNo.‚ªA0`or1`‚Æˆá‚¤‚Ì‚½‚ß */
			if ( (i+(OPR_MAILBOX_MIN)) >= 10 ){
				CMN_UnsignedIntToASC( &List.S.Print[30],
				 (UWORD)i + ( OPR_MAILBOX_MIN ), 0, 0 ); /** "8-1" -> "30" By H.Hirao 1996/07/11 */
			}
			else {
				CMN_UnsignedIntToASC( &List.S.Print[31],
				 (UWORD)i + ( OPR_MAILBOX_MIN ), 0, 0 ); /** "9-1" -> "31" By H.Hirao 1996/07/11 */
			}
#else
			CMN_UnsignedIntToASC( &List.S.Print[9-1], (UWORD)i, 0, 0 );
#endif
			List.S.Print[33] = LST_KLINEI; /** "11-1" -> "33" By H.Hirao 1996/07/11 */
			/** "12-1" -> "34" By H.Hirao 1996/07/11 */
			CMN_StringCopy(&List.S.Print[34], SYB_MailBox[i].BoxName ); /*1996/03/12 Eguchi */
			List.S.Print[50] = LST_KLINEI; /** "28-1" -> "50" By H.Hirao 1996/07/11 */
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
	}
	/*†¶†¢†¢†Ö†¢†¢†¢†¢†º*/
	Print_Mailbox_List_Line( 3, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*‚Psˆóši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

/*************************************************************************
	module		:[e“WÒØ½Ä‚Ì‰¡‹æØ‚èŒrüì¬]
	function	:[e“WÒØ½Ä‚Ì‰¡‹æØ‚èŒrü‚ğì¬‚·‚éB
	common		:[]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŸ˜Y]
*************************************************************************/
void			Print_Mailbox_List_Line(
						 UBYTE Category,			/*Œrüí—Ş*/
						 register UBYTE *AscString,	/*ˆóü•¶š—ñ*/
						 register UBYTE *AttString )/*Cü•¶š—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†Î†¢†¢†¢†¢†¢†²*/
			AscString[29] = LST_KLINE7; /** "7-1" -> "29" By H.Hirao 1996/07/11 */
			CMN_MemorySet( &AscString[30], 20, LST_KLINE_ ); /** "8-1"-> "30" By H.Hirao */
			AscString[33] = LST_KLINE8; /** "11-1" -> "33" By H.Hirao 1996/07/11 */
			AscString[50] = LST_KLINE9; /** "28-1" -> "50" By H.Hirao 1996/07/11 */
			break;
		case 1:
			/*†¤ Box†¤¼İÃİ¼¬Ò²†¤*/
			AscString[29] = LST_KLINEI; /** "7-1" -> "29" By H.Hirao 1996/07/11 */
			AttributeSet( &AscString[30], &AttString[30], PWRD_Box,
			  LST_NOT ); /** "8-1" -> "30" By H.Hirao 1996/07/11 */
			AscString[33] = LST_KLINEI; /** "11-1" -> "33" By H.Hirao 1996/07/11 */
			AttributeSet( &AscString[38], &AttString[38], PWRD_UserName,
			  LST_NOT ); /** "16-1" -> "38" By H.Hirao 1996/07/11 */
			AscString[50] = LST_KLINEI; /** "28-1" -> "50" By H.Hirao 1996/07/11 */
			break;
		case 2:
			/*†¾†¢†¢†Ş†¢†¢†¢†Æ*/
			AscString[29] = LST_KLINE4; /** "7-1" -> "29" By H.Hirao 1996/07/11 */
			CMN_MemorySet( &AscString[30], 20, LST_KLINE_ ); /** "8-1" -> "30" By H.Hirao 1996/07/11 */
			AscString[33] = LST_KLINE5; /** "11-1" -> "33" By H.Hirao 1996/07/11 */
			AscString[50] = LST_KLINE6; /** "28-1" -> "50" By H.Hirao 1996/07/11 */
			break;
		case 3:
			/*†¶†¢†¢†Ö†¢†¢†¢†¢†º*/
			AscString[29] = LST_KLINE1; /** "7-1" -> "29" By H.Hirao 1996/07/11 */
			CMN_MemorySet( &AscString[30], 20, LST_KLINE_ ); /** "8-1" -> "30" By H.Hirao 1996/07/11 */
			AscString[33] = LST_KLINE2; /** "11-1" -> "33" By H.Hirao 1996/07/11 */
			AscString[50] = LST_KLINE3; /** "28-1" -> "50" By H.Hirao 1996/07/11 */
			break;
	}
}

