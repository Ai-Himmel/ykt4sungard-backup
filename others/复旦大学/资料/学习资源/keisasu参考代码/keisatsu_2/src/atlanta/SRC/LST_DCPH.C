/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_POL.C
*	Author		: åKå¥ î¸ãI
*	Date		: 1997/11/21
*	RealTimeOS	: ÇqÇhÇrÇbÅiÇrÇgÇVÇOÇSÇRÅjÉÇÉjÉ^Å[
*	Description	: ÉXÉNÉâÉìÉuÉãéÛêMå¥çeè¡ãéí ím
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"
#include 	"\src\atlanta\define\sys_pdwn.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"

/*************************************************************************
	module		:[ÉXÉNÉâÉìÉuÉãéÛêMå¥çeè¡ãéí ím]
	function	:[ÉXÉNÉâÉìÉuÉãéÛêMå¥çeè¡ãéí ímÇàÛç¸Ç∑ÇÈ]
	common		:[
		List				:
	]
	condition	:[]
	commment	:[
	]
	return		:[àÛç¸åãâ ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/11/21]
	author		:[åKå¥î¸ãI]
*************************************************************************/
WORD					Print_DelScrambleRx_List(
						 void )			/* Ç»Çµ */
{
	register WORD	ret;					/*é¿çsåãâ */

	if ( Check_AnyList( LST_DEL_SCRAMBLE_RX_NOTICE ) == MSG_PRN_LST_NO_LIST ) {
		return ( MSG_PRN_LST_NO_LIST );
	}

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/*ÇPâ¸çsÅ{î≠êMå≥ñºÅAî‘çÜàÛç¸Å{ÇQâ¸çs*/
	if ( (ret = TTI_ID_Print_Feed()) != OK ) {
		return ( ret );
	}

	/*ÜÆÜ¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü≤*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[18-1] = LST_KLINE7;
	CMN_MemorySet( &List.S.Print[19-1], 44, LST_KLINE_ );
	List.S.Print[63-1] = LST_KLINE9;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*Ü§Ω∏◊›ÃﬁŸπﬁ›∫≥ ºÆ≥∑Æ ¬≥¡Ü§*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[18-1] = LST_KLINEI;
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
/*		AttributeSet( &List.S.Print[29-1], &List.S.Attribute[29-1],	@* 19 -> 29 97/12/12 By M.Kuwahara *@
		  PWRD_EraseScrambleRxDoc_K, LST_NOT );By Y.Suzuki 1998/04/24 */
		AttributeSet( &List.S.Print[19-1], &List.S.Attribute[19-1],	/* 29 -> 19 By Y.Suzuki 1998/04/24 */
		  PWRD_EraseScrambleRxDoc_K, LST_NOT );
#else
	AttributeSet( &List.S.Print[19-1], &List.S.Attribute[19-1],
		  PWRD_EraseScrambleRxDoc, LST_MES_TWI_XXX );
#endif

	List.S.Print[63-1] = LST_KLINEI;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*Ü∂Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü∫*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[18-1] = LST_KLINE1;
	CMN_MemorySet( &List.S.Print[19-1], 44, LST_KLINE_ );
	List.S.Print[63-1] = LST_KLINE3;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*ÇPçsàÛéöÅiâ¸çsÅj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/*åªç›éûä‘*/
	if ( (ret = CurrentTimePrint( 60-1 )) != OK ) {
		return ( ret );
	}

	/*ÜÆÜ¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü≤*/
	Print_DelPoll_List_Line( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*Ü§Ω∏◊›ÃﬁŸ πﬁ›∫≥∂ﬁ ºÆ≥∑Æ ª⁄œº¿ Ü§*/
	Print_DelPoll_List_Line( 1, List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1],
	  PWRD_ScrambleRxErase, LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*Ü∂Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü∫*/
	Print_DelPoll_List_Line( 2, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*ÇPçsàÛéöÅiâ¸çsÅj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

