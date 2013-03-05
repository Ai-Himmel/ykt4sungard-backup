/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_MSGS.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒZƒLƒ…ƒŠƒeƒB[ŽóMƒƒ‚ƒŠƒI[ƒo[ƒ`ƒFƒbƒNƒƒbƒZ[ƒW
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


/*************************************************************************
	module		:[ƒZƒLƒ…ƒŠƒeƒB[ŽóMƒƒ‚ƒŠƒI[ƒo[ƒ`ƒFƒbƒNƒƒbƒZ[ƒW]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1996/06/27]
	author		:[•½”ö ‰p“T]
*************************************************************************/
WORD		Print_SecurityRx_MemOver(
								void )		/** –³‚µ */
{
	WORD			ret;	/** ŽÀsŒ‹‰Ê */
	
	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/**‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs*/
	if ( (ret = TTI_ID_Print_Feed()) != OK ) {
		return ( ret );
	}
	
	/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
	/*†¤@ƒ`ƒFƒbƒNƒƒbƒZ[ƒW@	  †¤*/
	/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
	if ( (ret = Print_ChkMsg_Head( LST_ERR_CLOSE )) != OK ) {
		return ( ret );
	}
	
	/**‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
	
	/*Œ»ÝŽžŠÔ*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	TimeDataAscii( OFF, SYB_CurrentTime, List.S.Work, 0 );
	CMN_StringCopy( &List.S.Print[59], List.S.Work );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	
	/**†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†² */
	Print_DelPoll_List_Line( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	
	/**†¤ƒZƒLƒ…ƒŠƒeƒB[ŽóM‚ªƒƒ‚ƒŠƒI[ƒo[‚É‚È‚Á‚½‚Æ‚«‚ÌƒƒbƒZ[ƒW †¤*/
	Print_DelPoll_List_Line( 1, List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[1], &List.S.Attribute[1], PWRD_SecurityMemOver, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/**†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º */
	Print_DelPoll_List_Line( 2, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 1997/10/21 Y.Matsukuma */
	/*‚QsˆóŽši‰üsj*/						/* 97/08/25 Add By M.Kuwahara */
	if ( (ret = CharacterPrint( LST_LINE_FEED +2)) != OK ) {
		return ( ret );
	}

	/** "‘€ìF‹@”\¨ƒƒ“ƒ^ƒbƒ`‚n¨‚Q¨ƒZƒbƒg‚ð‰Ÿ‚µ" **/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1], PWRD_SecurityOperation1, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/** "      ‚SŒ…‚ÌƒvƒƒeƒNƒgƒpƒXƒR[ƒh‚ð“ü—Í‚µ‚Ä‰º‚³‚¢" **/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1], PWRD_SecurityOperation2, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
#endif

	/**‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	return ( OK );
}
