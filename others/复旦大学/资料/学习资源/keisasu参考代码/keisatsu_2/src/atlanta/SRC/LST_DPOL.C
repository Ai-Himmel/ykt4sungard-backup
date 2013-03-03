/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_POL.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: Îß°ØÝ¸ÞŒ´eÁ‹Ž’Ê’m
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
	module		:[Îß°ØÝ¸ÞŒ´eÁ‹Ž’Ê’m]
	function	:[Îß°ØÝ¸ÞŒ´eÁ‹Ž’Ê’m‚ðˆóü‚·‚é]
	common		:[
		List				:
		SYB_PowerDownListStatus;
	]
	condition	:[]
	commment	:[
		94/11/26	By j.masuda
			ƒ|[ƒŠƒ“ƒOŒ´eÁ‹Ž’Ê’mAŒŸõƒ|[ƒŠƒ“ƒOŒ´eÁ‹Ž’Ê’mA
			‚ÌƒXƒe[ƒ^ƒX‚ðSYB_PowerDownListStatus‚É•ÏXB
	]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD					Print_DelPoll_List(
						 void )			/* ‚È‚µ */
{
	UBYTE	p_flg;					/*ˆóüÌ×¸Þ*/
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Check_AnyList( LST_DELPOLLING_NOTICE ) == MSG_PRN_LST_NO_LIST ) {
		return ( MSG_PRN_LST_NO_LIST );
	}

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs*/
	if ( (ret = TTI_ID_Print_Feed()) != OK ) {
		return ( ret );
	}

	/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[18-1] = LST_KLINE7;
	CMN_MemorySet( &List.S.Print[19-1], 44, LST_KLINE_ );
	List.S.Print[63-1] = LST_KLINE9;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¤Îß°ØÝ¸Þ¹ÞÝº³ ¼®³·® Â³Á†¤*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[18-1] = LST_KLINEI;
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		AttributeSet( &List.S.Print[19-1], &List.S.Attribute[19-1],
		  PWRD_ErasePollDoc_K, LST_NOT );		/* MES¨INV 94.7.20 ->NOT 8.10 */
#else
	AttributeSet( &List.S.Print[19-1], &List.S.Attribute[19-1], 
		  PWRD_ErasePollDoc, LST_MES_TWI_XXX );
#endif

	List.S.Print[63-1] = LST_KLINEI;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[18-1] = LST_KLINE1;
	CMN_MemorySet( &List.S.Print[19-1], 44, LST_KLINE_ );
	List.S.Print[63-1] = LST_KLINE3;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
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

	p_flg = OFF;
	if ( (SYB_PowerDownListStatus & SYS_POWER_POLLING ) != 0 ) {	/*94/11/26 By jmasuda*/
		p_flg = ON;
		/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
		Print_DelPoll_List_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*†¤Îß°ØÝ¸Þ ¹ÞÝº³¶Þ ¼®³·® »ÚÏ¼À †¤*/
		Print_DelPoll_List_Line( 1, List.S.Print, List.S.Attribute );
		AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1],
		  PWRD_PollErase, LST_NOT );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
		Print_DelPoll_List_Line( 2, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		SYB_PowerDownListStatus &= ~SYS_POWER_POLLING;	/*94/11/26 By jmasuda*/
	}

#if ( PRO_DB_POLLING_TX == ENABLE )
	if ( (SYB_PowerDownListStatus & SYS_POWER_DB_POLL ) != 0 ) {	/*94/11/26 By jmasuda*/
		if ( p_flg == ON ) {
			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
		}

		/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
		Print_DelPoll_List_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*†¤¹Ý»¸Îß°ØÝ¸Þ ¹ÞÝº³¶Þ ¼®³·® »ÚÏ¼À †¤*/
		Print_DelPoll_List_Line( 1, List.S.Print, List.S.Attribute );
		AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1],
		  PWRD_DbPollErase, LST_NOT );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
		Print_DelPoll_List_Line( 2, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		SYB_PowerDownListStatus &= ~SYS_POWER_DB_POLL;/*94/11/26 By jmasuda*/
	}
#endif

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

/*************************************************************************
	module		:[Îß°ØÝ¸ÞŒ´eÁ‹Ž’Ê’m‚Ì‰¡‹æØ‚èŒrüì¬]
	function	:[
		Îß°ØÝ¸ÞŒ´eÁ‹Ž’Ê’m‚ÌÒ¯¾°¼Þ•”•ª‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB
	]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
			0 = †®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²
			1 = †¤					  †¤
			2 = †¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
void				Print_DelPoll_List_Line(
						 UBYTE Category,				/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,		/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )	/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
			AscString[ 1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[80-1] = LST_KLINE9;
			break;
		case 1:
			/*†¤					†¤*/
			AscString[ 1-1] = LST_KLINEI;
			AscString[80-1] = LST_KLINEI;
			break;
		case 2:
			/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
			AscString[ 1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[80-1] = LST_KLINE3;
			break;
	}
}

