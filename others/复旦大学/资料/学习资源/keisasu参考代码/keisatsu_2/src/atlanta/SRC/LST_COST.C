/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_COST.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: —¿‹à•\
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
#include	"\src\atlanta\define\sysmax.h"

#if (PRO_COST == ENABLE) /* For ANZU By S.K Dec.15,1995 */
/*************************************************************************
	module		:[—¿‹à•\ˆóü]
	functiom	:[—¿‹à•\‚ðˆóü‚·‚é]
	common		:[
		List				:
		SYS_CostTable	:
		SYS_NTT_AccessFile	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[V53]
	language	:[MS-C]
	keyword		:[LST]
	date		:[94/ 6/ 29]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Print_CostTable_List(
						 void )				/*‚È‚µ*/
{
	UBYTE	i;						/*loop*/
	UBYTE	page;					/*Íß°¼Þ*/
	UBYTE	cost_cnt;				/*ÃÞ°À”Ô†*/
	UBYTE	line_cnt;				/*s”*/
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	page = 1;
	cost_cnt = 0;
	CostDataNextSearch( &cost_cnt );					/*ÃÞ°Àhead*/
	while ( cost_cnt < SYS_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX + SYS_2ND_SPEED_DIAL_MAX + SYS_2ND_ONETOUCH_MAX ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		if ( page == 1 ) {
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		else {
			line_cnt = (UBYTE)(PaperSizeLen() - 4);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		if ( (ret = Print_CostTable_List_Head( 0, page ) ) != OK ) {/*Í¯ÀÞˆóü*/
			return ( ret );
		}
		for ( i = 0; line_cnt >= 2; i++, line_cnt -= 2 ) {
			if ( (ret = Print_CostTable_List_Specifi( page, i, cost_cnt) ) != OK ) {		/*1–¾×ˆóü*/
				return ( ret );
			}
			cost_cnt++;	/* ’Ç‰Á Î‹´³˜a 94/10/27 */
			CostDataNextSearch( &cost_cnt );					/*ŽŸÃÞ°À»°Á*/
			if ( cost_cnt >= SYS_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX + SYS_2ND_ONETOUCH_MAX + SYS_2ND_SPEED_DIAL_MAX ) {
				break;
			}
			/* cost_cnt++; */	/* ƒRƒƒ“ƒg‰» Î‹´³˜a 94/10/27 */
		}
		if ( (ret = Print_CostTable_List_Head( 1, page) ) != OK ) {	/*Ì¯Àˆóü*/
			return ( ret );
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	return ( OK );
}

/*************************************************************************
	module		:[—¿‹à•\ƒwƒbƒ_ˆóü]
	functiom	:[—¿‹à•\‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
	common		:[
		List	:
	]
	condition	:[
		Í¯ÀÞŽí—Þ
			0->Íß°¼Þæ“ªŒ©o‚µ
			1->Íß°¼Þ´ÝÄÞŒ©o‚µ
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[V53]
	language	:[MS-C]
	keyword		:[LST]
	date		:[94/06/30]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Print_CostTable_List_Head(
						 UBYTE Category,	/*ƒwƒbƒ_Ží—Þ*/
						 UBYTE Page )		/*ƒy[ƒW*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Category == 0 ) {
		if ( Page == 1 ) {

			/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs{Œ©o‚µ{‚P‰üs*/
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		if ( (ret = Print_Head1_Common( PWRD_CostBase_K,
		 LST_NOT,30-1 )) != OK ) {
			return ( ret );
		}

#else
	if ( (ret = Print_Head1_Common( PWRD_CostBase,
	  LST_XXX_TWI_XXX, 20-1 )) != OK ) {
		return ( ret );
	}

#endif

			/* Page Œ»ÝŽžŠÔ */
			if ( (ret = LocateX_Page_Time_Print( 14-1, Page, 51-1 )) != OK ) {
				return ( ret );
			}

			/*†®†¢†Î†¢†¢†Î†¢†¢†¢†¢†¢†²*/
			Print_CostTable_List_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤No.†¤’‹ŠÔ(•b/‰~)†¤–éŠÔ(•b/‰~)„ [–é(•b/‰~)„  */
			Print_CostTable_List_Line( 1, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}

		else {
			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
			/* Page */
			if ( (ret = LocateX_Page_Print( 14-1, Page )) != OK ) {
				return ( ret );
			}
		}
	}
	else {
		/*†¶†¢†Ö†¢†¢†Ö†¢†¢†¢†¢†¢†º*/
		Print_CostTable_List_Line( 4, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
	}
	return ( OK );
}

/*************************************************************************
	module		:[—¿‹à‹Ç”ÔƒlƒNƒXƒg ƒT[ƒ`n
	functiom	:[—¿‹àŠÇ—‚Ì‹Ç”Ô‚ÌŽŸ‚ðƒT[ƒ`‚·‚é]
	common		:[
		List				:
		SYS_CostTable		:
		SYS_NTT_AccessFile	:
	]
	condition	:[
00		,	ƒf[ƒ^ƒGƒ“ƒh|„SYS_ONETOUCH_MAX+SYS_SPEED_DIAL_MAX+SYS_2ND_ONETOUCH_MAX+SYS_2ND_SPEED_DIAL_MAX
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[V53]
	language	:[MS-C]
	keyword		:[LST]
	date		:[94/ 7/ 28]
	author		:[–L“c_Žq]
*************************************************************************/
void			CostDataNextSearch(
						 UBYTE *CostCnt )/*‹Ç”Ô*/
{
	UBYTE	i;						/*loop*/

	for ( i = (*CostCnt); i < (SYS_ONETOUCH_MAX+SYS_SPEED_DIAL_MAX+SYS_2ND_ONETOUCH_MAX+SYS_2ND_SPEED_DIAL_MAX); i++ ) {
		if ( SYB_NTT_AccessFile[ i ].Number[0] != 0xff ) {
			(*CostCnt) = i;
			break;
		}
	}
	if ( i == (SYS_ONETOUCH_MAX+SYS_SPEED_DIAL_MAX+SYS_2ND_ONETOUCH_MAX+SYS_2ND_SPEED_DIAL_MAX) ) {
		(*CostCnt) = (SYS_ONETOUCH_MAX+SYS_SPEED_DIAL_MAX+SYS_2ND_ONETOUCH_MAX+SYS_2ND_SPEED_DIAL_MAX);
	}
}

/*************************************************************************
	module		:[—¿‹à•\‚Ì‚P–¾×ˆóü]
	functiom	:[—¿‹à•\‚Ì‚P–¾×‚ðˆóü‚·‚éB]
	common		:[
		List				:
		SYS_CostTable		:
		SYS_NTT_AccessFile	:
	]
	condition	:[
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[V53]
	language	:[MS-C]
	keyword		:[LST]
	date		:[94/06/30]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Print_CostTable_List_Specifi(
						 UBYTE Page,				/*ƒy[ƒW*/
						 UBYTE Line,				/*Œ»Ý–¾×”*/
						 UWORD CostCnt  )			/*ÃÞ°À”Ô†*/
{
	register WORD	ret;				/*ŽÀsŒ‹‰Ê*/
	UBYTE	i;					/*•¶Žš—ñ’·*/

	i = 0;

	if ( SYB_NTT_AccessFile[ CostCnt ].Number[0] != 0xff ) {
		if ( Page > 1 && Line == 0 ) {
			/*†®†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢„Ÿ†¢†²*/
			Print_CostTable_List_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
		else {
			/*†¾†¢†¢†Þ†¢„Ÿ†¢„©†¢„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ†Æ*/
			Print_CostTable_List_Line( 2, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
		/*†¤999999†¤Z99.9 †¤Z99.9  „ Z99.9„ */
		Print_CostTable_List_Line( 3, List.S.Print, List.S.Attribute );
		if ( CostCnt == 0 ) {
			AttributeSet( (UBYTE *)&List.S.Print[12-1], (UBYTE *)&List.S.Attribute[12-1], PWRD_WithinArea,
			 LST_NOT );	/* —¿‹à•\”Ô†00‚ÌŽž‚ÍŽs“à */
		}
		else {
			CMN_StringCopy( (UBYTE *)&List.S.Print[13-1], (UBYTE *)SYB_NTT_AccessFile[ CostCnt ].Number );
		}
		/* ’‹ */
		CMN_UnsignedIntToASC_NULL( (UBYTE *)List.S.Work,
		 (UWORD)SYB_CostTable[ SYB_NTT_AccessFile[ CostCnt ].CostTable].Daytime,
		  4, ' ');
		Print_Cost_Keta( List.S.Work );
		CMN_StringCopy( (UBYTE *)&List.S.Print[26-1], ( UBYTE *)List.S.Work );

		/* –é */
		CMN_UnsignedIntToASC_NULL( (UBYTE *)List.S.Work,
		 (UWORD)SYB_CostTable[ SYB_NTT_AccessFile[ CostCnt ].CostTable].Night,
		  4, ' ');
		Print_Cost_Keta( List.S.Work );
		CMN_StringCopy( (UBYTE *)&List.S.Print[43-1], (UBYTE *)List.S.Work );

		/* [–é */
		CMN_UnsignedIntToASC_NULL( (UBYTE *)List.S.Work,
		 (UWORD)SYB_CostTable[ SYB_NTT_AccessFile[ CostCnt ].CostTable].Midnight,
		  4, ' ');
		Print_Cost_Keta( List.S.Work );
		CMN_StringCopy( (UBYTE *)&List.S.Print[60-1], (UBYTE *)List.S.Work );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	return ( OK );
}

/*************************************************************************
	module		:[—¿‹à•\‚Ì’‹ŠÔ¤–éŠÔ¤[–é‚ÌŒ…ˆÊ’u‚ð‚¸‚ç‚·]
	functiom	:[—¿‹à•\‚Ì’‹ŠÔ¤–éŠÔ¤[–é‚Ì3Œ…–Ú‚ð4Œ…–Ú‚É‚¸‚ç‚·B]
	common		:[]
	condition	:[
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[V53]
	language	:[MS-C]
	keyword		:[LST]
	date		:[94/ 8/ 9]
	author		:[–L“c_Žq]
*************************************************************************/
void		Print_Cost_Keta( register UBYTE *AscString )	/*ˆóü•¶Žš—ñ*/
{
		AscString[ 3+1 ] = AscString[ 3 ];	/* 3Œ…–Ú‚Í¤¬”“_‘æ1ˆÊ‚Ì”Ô†‚ª‚Í‚¢‚Á‚Ä‚¢‚é*/
		AscString[ 3 ] = '.';
		AscString[ 3+2 ] = NULL;
		if ( AscString[2] == ' ' ) {
			AscString[2] = '0';		/* ¬”“_‘æ1ˆÊ‚Ì‚Ý‚ÌŽž‚Ìˆ— 0.? */
		}
}

/*************************************************************************
	module		:[—¿‹à•\‚Ì‰¡‹æØ‚èŒrüì¬]
	functiom	:[—¿‹à•\‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
		,	0 = †®†¢†¢†Î†¢†¢†¢„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ†¢†²
		,	1 = †¤ NO.†¤  ’‹ŠÔ	†¤	–éŠÔ  „   [–é	„ 
		,	2 = †¾†¢†¢†Þ†¢„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ†¢†¢†¢†Æ
		,	3 = †¤	  †¤		†¤		  „ 		„ 
		,	4 = †¶†¢†¢†Ö†¢„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ†¢†¢†¢†º
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[V53]
	language	:[MS-C]
	keyword		:[LST]
	date		:[94/ 3/ 9]
	author		:[–L“c_Žq]
*************************************************************************/
void				Print_CostTable_List_Line(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( (UBYTE *)AscString, (UBYTE *)AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†Î†¢†¢†¢„¦„Ÿ„Ÿ„Ÿ„¦„Ÿ†¢†¢†²*/
			AscString[11-1] = LST_KLINE7;
			CMN_MemorySet( (UBYTE *)&AscString[12-1], 59, LST_KLINE_ );
			AscString[20-1] = LST_KLINE8;
			AscString[37-1] = LST_KLINE8;
			AscString[54-1] = LST_KLINE8;
			AscString[71-1] = LST_KLINE9;
			break;
		case 1:
			/*†¤‹Ç”Ô†¤’‹ŠÔ(•b/10‰~)†¤–éŠÔ(•b/10‰~)„ [–é(•b/10‰~)„  */
			AscString[11-1] = LST_KLINEI;
			AttributeSet( (UBYTE *)&AscString[12-1], (UBYTE *)&AttString[12-1], PWRD_DialingCode,
			  LST_NOT );
			AscString[20-1] = LST_KLINEI;
			AttributeSet( (UBYTE *)&AscString[21-1], (UBYTE *)&AttString[22-1], PWRD_Daytime,
			  LST_NOT );
			AscString[37-1] = LST_KLINEI;
			AttributeSet( (UBYTE *)&AscString[38-1], (UBYTE *)&AttString[39-1], PWRD_Night,
			  LST_NOT );
			AscString[54-1] = LST_KLINEI;
			AttributeSet( (UBYTE *)&AscString[55-1], (UBYTE *)&AttString[56-1], PWRD_Midnight,
			  LST_NOT );
			AscString[71-1] = LST_KLINEI;
			break;
		case 2:
			/*†¾†¢†¢†Þ†¢„Ÿ†¢„©†¢„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ†Æ*/
			AscString[11-1] = LST_KLINE4;
			CMN_MemorySet( (UBYTE *)&AscString[12-1], 59, LST_KLINE_ );
			AscString[20-1] = LST_KLINE5;
			AscString[37-1] = LST_KLINE5;
			AscString[54-1] = LST_KLINE5;
			AscString[71-1] = LST_KLINE6;
			break;
		case 3:
			/*†¤	†¤		†¤		 „ 		 „ */
			AscString[11-1] = LST_KLINEI;
			AscString[20-1] = LST_KLINEI;
			AscString[37-1] = LST_KLINEI;
			AscString[54-1] = LST_KLINEI;
			AscString[71-1] = LST_KLINEI;
			break;
		case 4:
			/*†¶†¢†¢†Ö†¢†¢†¢„¨„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ†¢†º*/
			AscString[11-1] = LST_KLINE1;
			CMN_MemorySet( (UBYTE *)&AscString[12-1], 59, LST_KLINE_ );
			AscString[20-1] = LST_KLINE2;
			AscString[37-1] = LST_KLINE2;
			AscString[54-1] = LST_KLINE2;
			AscString[71-1] = LST_KLINE3;
			break;
	}
}
#endif

