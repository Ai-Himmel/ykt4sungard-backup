/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_MSGE.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚d Žè“®‘—MƒGƒ‰[
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include 	"\src\atlanta\define\apl_msg.h"
#include 	"\src\atlanta\define\std.h"

#include 	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include 	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include 	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"

/*************************************************************************
	module		:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWE Žè“®‘—MƒGƒ‰[ˆóü]
	function	:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWE Žè“®‘—MƒGƒ‰[‚ðˆóü‚·‚é]
	common		:[
		List						:
		BackUpFaxComResult		:
		BackUpStandardID		:
		TxResponsedRTN_PageSign	:
		SYS_ManualFaxCommErrRequest	;
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
WORD 				Print_MnlErr_ChkMsg(
						 void )			/*‚È‚µ*/
{
	UBYTE	i;					/*loop*/
	UBYTE dummy;				/*ÀÞÐ-*/
	register WORD	ret;		/*ŽÀsŒ‹‰Ê*/

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
	/*†¤@ƒ`ƒFƒbƒNƒƒbƒZ[ƒW@    †¤*/
	/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
	if ( (ret = Print_ChkMsg_Head( LST_ERR_CLOSE )) != OK ) {
		return ( ret );
	}

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/*Œ»ÝŽžŠÔ*/
	if ( (ret = CurrentTimePrint( 60-1 )) != OK ) {
		return ( ret );
	}

	/*†®†¢†¢†¢†Î†¢†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†²*/
	Print_CommErr_ChkMsg_Line( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¤ XXXXX†¤XXXXXXXXX †¤XXXXXXXXXX†¤*/
	Print_CommErr_ChkMsg_Line( 1, List.S.Print, List.S.Attribute );
	/*Â³¼Ý¹¯¶”Ô†*/
	CommunicationResultName( BackUpFaxComResult, LST_NAME_SHORT,
	  LST_RESULT_COMMON, &List.S.Print[2-1], &List.S.Attribute[2-1] );
	/*Â³¼Ý¹¯¶ Ò¯¾°¼Þ*/
	/*ÀÞ²ÔÙÊÞÝºÞ³*/
	CommunicationResultName( BackUpFaxComResult, LST_NAME_LONG,
	  LST_RESULT_COMMON, &List.S.Print[9-1], &List.S.Attribute[9-1] );
	CMN_StringCopy( &List.S.Print[40-1], BackUpStandardID );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¶†¢†¢†Ö†¢†¢†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†º*/
	Print_CommErr_ChkMsg_Line( 3, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

#if defined (DEU)	/* DEU‚ÌŽž‚Ì‚Ý•œ‹A 97/11/26 By M.Kuwahara */
/*#if(0) /** PAT‚Ì‚½‚ß‚Í‚¸‚· By H.Hirao 1996/06/14 */
	/*´×°Íß°¼ÞˆóŽš‚ÍÄÞ²Â—pB*/
	/* ´×°Íß°¼Þ*/
	if ( (BackUpFaxComResult & DIALERROR) == TRANSMITERROR) {
		for ( i = 0; i < SYS_ERROR_PAGE; i++ ) {
			if ( TxResponsedRTN_PageSign[i] != 0 ) {
				if ( (ret = Print_ChkMsg_ErrorPages( LST_ERR_CLOSE, 
													 (UBYTE *)TxResponsedRTN_PageSign,
				  									  SYS_ERROR_PAGE, 
													  &dummy )) != OK ) {
					return ( ret );
				}
				break;
			}
		}
	}
#endif

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	SYS_ManualFaxCommErrRequest = 0;
	return ( OK );
}
