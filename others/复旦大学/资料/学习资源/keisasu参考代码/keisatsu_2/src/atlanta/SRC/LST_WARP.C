/*************************************************************************
*	System		: SAKAKI
*	File Name	: LST_WARP.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1998/06/23
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒ[ƒv‹@”\ƒŠƒXƒg
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysdial.h"
#include	"\src\atlanta\define\syswarp.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\uni_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"


#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/24 By M.Kuwahara */

struct SYS_DialData_t	LST_WarpDial;	/* ”­Mæo—Íƒ[ƒN */

/*************************************************************************
	module		:[ƒ[ƒv‹@”\ƒŠƒXƒg]
	function	:[ƒ[ƒv‹@”\ƒŠƒXƒg‚ðˆóü‚·‚é]
	common		:[
		List		:
		SYB_WarpFile
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/06/23]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD				Print_Warp_List(
						 void )				/*‚È‚µ*/
{
	UBYTE	i;						/*loop*/
	UBYTE 	page;					/*Íß°¼Þ*/
	UBYTE	warp_cnt;				/*Ü°Ìß‹@”\ÃÞ°À”Ô†*/
	UBYTE 	line_cnt;				/*Žc‚èˆóü‰Â”\s”*/
	register WORD	ret;			/*ŽÀsŒ‹‰Ê*/

	i	= 0;
	page = 1;
	warp_cnt = 0;
	DialCheckPointer	= SYS_DIRECT_DIAL;
#if (1)		/* ‰Šú‰»–Y‚ê‘Î‰ž by Y.kano 2005/03/01 */
	DialCheckBitPointer = 0;		/** ƒrƒbƒgƒ|ƒCƒ“ƒ^‚ð‰Šú‰» */
#endif

	warp_cnt = WarpDataNextSearch( warp_cnt );	/*ŽŸÃÞ°À»°Á */
	if ( warp_cnt == SYS_WARP_MAX ) {
		return ( MSG_PRN_LST_NO_LIST );
	}
	while ( warp_cnt != SYS_WARP_MAX ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}

		if ( page == 1 ) {
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		else {
			line_cnt = (UBYTE)(PaperSizeLen() - 4);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		if ( (ret = PrintWarpList_Head( 0, page ) ) != OK ) {/*Í¯ÀÞˆóü*/
			return ( ret );
		}

		for(;;) {
			/*1–¾×ˆóü*/
			if ( (ret = PrintWarpList_Specifi( page ,&i, warp_cnt, &line_cnt) ) != OK ) {
				return ( ret );
			}

			if (DialCheckPointer == SYS_EMPTY_DIAL) {	/* ‘S–¾×“à—eo—Í */
				warp_cnt++;
				warp_cnt = WarpDataNextSearch( warp_cnt );	/*ŽŸÃÞ°À»°Á */
				if (warp_cnt == SYS_WARP_MAX) {
					break;
				}
				DialCheckPointer	= SYS_DIRECT_DIAL;
				DialCheckBitPointer	= 0;
			}
			if (line_cnt <= 0) {
				break;
			}
		}
		if ( (ret = PrintWarpList_Head( 1, page) ) != OK ) {	/*Ì¯Àˆóü*/
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
	module		:[ƒ[ƒv‹@”\ƒwƒbƒ_ˆóü]
	functiom	:[ƒ[ƒv‹@”\‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
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
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/06/23]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD				PrintWarpList_Head(
						 UBYTE Category,	/*ƒwƒbƒ_Ží—Þ*/
						 UBYTE Page )		/*ƒy[ƒW*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Category == 0 ) {
		if ( Page == 1 ) {

			/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs{Œ©o‚µ{‚P‰üs*/
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			if ( (ret = Print_Head1_Common( PWRD_WarpList_K,
			 LST_NOT, 21-1 )) != OK ) {
				return ( ret );
			}
#else
			if ( (ret = Print_Head1_Common( PWRD_WarpList,
			  LST_XXX_TWI_XXX, 22-1 )) != OK ) {
				return ( ret );
			}
#endif
			/*Œ»ÝŽžŠÔ*/
			/*Page Œ»ÝŽžŠÔ*/
			if ( (ret = PageTimePrint( Page, 3-1, 59-1 )) != OK ) {
				return ( ret );
			}

			/*†®†¢†Î†¢†¢†¢†¢†¢†²*/
			PrintWarpList_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/* |No.| ÀÞ²ÔÙ”Ô†   | Žw’èŽž|“¯ŽžÌßØÝÄ| */
			PrintWarpList_Line( 1, List.S.Print, List.S.Attribute );
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
			if ( (ret = PagePrint( Page, 3-1 )) != OK ) {
				return ( ret );
			}
		}
	}
	else {
		/*†¶†¢†¢†Ö†¢†¢†¢†¢†º*/
		PrintWarpList_Line( 4, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
	}
	return( OK );
}

/*************************************************************************
	module		:[ƒ[ƒv‹@”\ƒ_ƒCƒ„ƒ‹ ƒlƒNƒXƒg ƒT[ƒ`n
	functiom	:[ƒ[ƒvƒ_ƒCƒ„ƒ‹‚ÌŽŸ‚ðƒT[ƒ`‚·‚é]
	common		:[
		SYB_WarpFile	:
	]
	condition	:[
		,	ƒf[ƒ^ƒGƒ“ƒh->SYS_WARP_MAX
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/06/23]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
UBYTE		WarpDataNextSearch(
					 UBYTE WarpCnt)	/*ƒ_ƒCƒ„ƒ‹ƒf[ƒ^”Ô†*/
{
	UBYTE	i;

	for (i = WarpCnt; i < SYS_WARP_MAX; i++) {
		if (SYB_WarpFile[i].Status != SYS_WARP_EMPTY) {	/* ƒf[ƒ^‘¶ÝŽž */
			break;
		}
	}
	return( i );
}


/*************************************************************************
	module		:[ƒ[ƒv‹@”\‚Ì‚P–¾×ˆóü]
	functiom	:[ƒ[ƒv‹@”\‚Ì‚P–¾×‚ðˆóü‚·‚éB]
	common		:[
		List				:
		SYB_WarpFile		:
	]
	condition	:[
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/06/23]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD				PrintWarpList_Specifi(
					 UBYTE Page,		/*ƒy[ƒW*/
					 UBYTE *Line,		/*Œ»Ý–¾×”*/
					 UBYTE WarpCnt,		/*ƒf[ƒ^”Ô†*/
					 UBYTE *LineCnt )	/*ˆóŽšsˆÊ’u*/
{
	UBYTE	i;
	UBYTE	check_line;
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if (Page > 1) {
		if (*LineCnt == (PaperSizeLen() - 4) ) {
			/*†¾†¢†¢†Þ†¢†¢†¢†Æ*/
			PrintWarpList_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
		else {
			if (*Line == 0) {
				/*†¾†¢†¢†Þ†¢†¢†¢†Æ*/
				PrintWarpList_Line( 2, List.S.Print, List.S.Attribute );
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
			}
			(*LineCnt)--;
		}
	}
	else {
		if (*Line == 0) {
			/*†¾†¢†¢†Þ†¢†¢†¢†Æ*/
			PrintWarpList_Line( 2, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			(*LineCnt)--;
		}
	}

	/* ƒ[ƒN—p‚Ìƒf[ƒ^ƒZƒbƒg */
	for (i = 0; i < SYS_COM_DIRECT_DIAL_MAX ; i++) {
		LST_WarpDial.Direct[i][0] = 0xFF;
	}
	CMN_StringCopyNum((UBYTE *)&LST_WarpDial.Direct[0],
						   SYB_WarpFile[WarpCnt].Direct,
						   SYS_DIRECT_DIAL_MAX );
	
	for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
		LST_WarpDial.Onetouch[i] = SYB_WarpFile[WarpCnt].Onetouch[i];
	}
	for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
		LST_WarpDial.Speed[i] = SYB_WarpFile[WarpCnt].Speed[i];
	}
	LST_WarpDial.Group = SYB_WarpFile[WarpCnt].Group;

	while( *LineCnt != 0 ){
		/*|99|99999999999|XXXXXXXX|XX|*/
		PrintWarpList_Line( 3, List.S.Print, List.S.Attribute );

		/** “]‘—æ”Ô† */
		if (*Line == 0) {	/* –¾×‚Ìæ“ª‚ÌŽž */
			/** No. */
			CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)(WarpCnt+1), 2, ' ' );
			/** Žw’èŽž‚ðƒZƒbƒg */
			WarpTimeDataSet( &SYB_WarpFile[WarpCnt], &List.S.Print[48-1] );

			/** “¯ŽžƒvƒŠƒ“ƒg‚n‚m^‚n‚e‚eƒZƒbƒg */
			if (SYB_WarpFile[WarpCnt].Option & WARP_OPTION_PRINT) {
				AttributeSet( &List.S.Print[72-1], &List.S.Attribute[72-1], PWRD_On, LST_NOT );
			}
			else {
				AttributeSet( &List.S.Print[72-1], &List.S.Attribute[72-1], PWRD_Off, LST_NOT );
			}
		}
		/** ÀÞ²ÔÙ”Ô†‚Ì•¶Žš—ñ•ÏŠ· */
		ret = ProgramDataDialToString( (struct SYS_DialData_t *)&LST_WarpDial, SYS_PRG_DIAL_MAX, List.S.Work, *Line );
		CMN_StringCopy( &List.S.Print[7-1], List.S.Work );

		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		if (DialCheckPointer == SYS_EMPTY_DIAL) {	/* ‘S–¾×“à—eo—Í */
			(*Line)	= 0;
			(*LineCnt)--;
			break;
		}
		else {
			(*Line)++;
			(*LineCnt)--;
		}
	}
	return ( OK );
}


/*************************************************************************
	module		:[ƒ[ƒv‹@”\ƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrüì¬]
	function	:[ƒ[ƒv‹@”\ƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB
	common		:[]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/06/23]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
void			PrintWarpList_Line(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*„¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„¢*/
			AscString[2-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[3-1], 76, LST_KLINE_ );
			AscString[6-1] = LST_KLINE8;
			AscString[47-1] = LST_KLINE8;
			AscString[68-1] = LST_KLINE8;
			AscString[79-1] = LST_KLINE9;
			break;
		case 1:
			/*|No.|         ÀÞ²ÔÙ”Ô†           |Žw’èŽž|“¯ŽžÌßØÝÄ|*/
			AscString[2-1] = LST_KLINEI;
			AttributeSet( &AscString[3-1], &AttString[3-1], PWRD_No, LST_NOT );
			AscString[6-1] = LST_KLINEI;
			AttributeSet( &AscString[20-1], &AttString[20-1], PWRD_TelNum, LST_NOT );
			AscString[47-1] = LST_KLINEI;
			AttributeSet( &AscString[54-1], &AttString[54-1], PWRD_AppointedTime, LST_NOT );
			AscString[68-1] = LST_KLINEI;
			AttributeSet( &AscString[69-1], &AttString[69-1], PWRD_RxPrint, LST_NOT );
			AscString[79-1] = LST_KLINEI;
			break;
		case 2:
			/*„¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„§ */
			AscString[2-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[3-1], 76, LST_KLINE_ );
			AscString[6-1] = LST_KLINE5;
			AscString[47-1] = LST_KLINE5;
			AscString[68-1] = LST_KLINE5;
			AscString[79-1] = LST_KLINE6;
			break;
		case 3:
			/*|   |                            |          |      |*/
			AscString[2-1] = LST_KLINEI;
			AscString[6-1] = LST_KLINEI;
			AscString[47-1] = LST_KLINEI;
			AscString[68-1] = LST_KLINEI;
			AscString[79-1] = LST_KLINEI;
			break;
		case 4:
			/*„¤„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„£*/
			AscString[2-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[3-1], 76, LST_KLINE_ );
			AscString[6-1] = LST_KLINE2;
			AscString[47-1] = LST_KLINE2;
			AscString[68-1] = LST_KLINE2;
			AscString[79-1] = LST_KLINE3;
			break;
	}
}


/*************************************************************************
	module		:[ŽóM“]‘—ŽžŽw’èƒf[ƒ^‚ÌƒZƒbƒg]
	function	:[ŽóM“]‘—‚ÌŽžŽw’èƒf[ƒ^‚ðƒZƒbƒg‚·‚é
					Œ`Ž®F(-)**:** ` (-)**:**
	common		:[]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/05/19]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
void 	WarpTimeDataSet(
			 struct SYS_SubDialData_t *Data,	/* Žw’èŽž	*/
 			 register UBYTE *prn_string)	/* ˆóü•¶Žš—ñ */
{
#if (0)	/* —j“ú‚ðƒ[ƒfƒBƒ“ƒO‚É‚µ‚Ü‚·BBy H.Fujimura 1999/01/25 */
**	prn_string[0]	= '(';
**	SetLstWeekData( Data->StartWeek, &prn_string[1] );
**	prn_string[2]	= ')';
**	prn_string[12]	= '(';
**	SetLstWeekData( Data->EndWeek, &prn_string[13] );
**	prn_string[14]	= ')';
#else
	if (Data->StartWeek == SYS_NO_DAY) {
		CMN_StringCopyNumNotNULL(&prn_string[0], PWRD_WarpWeek[7], 3);
	}
	else {
		CMN_StringCopyNumNotNULL(&prn_string[0], PWRD_WarpWeek[Data->StartWeek], 3);
	}
	if (Data->EndWeek == SYS_NO_DAY) {
		CMN_StringCopyNumNotNULL(&prn_string[12], PWRD_WarpWeek[7], 3);
	}
	else {
		CMN_StringCopyNumNotNULL(&prn_string[12], PWRD_WarpWeek[Data->EndWeek], 3);
	}
#endif
#if (0)	/* Š¿Žš‚b‚f‚q‚n‚l‘Î‰ž‚Å‚È‚¢ê‡‚Ìˆ—‚ª”²‚¯‚Ä‚¢‚½‚Ì‚Å’Ç‰Á‚µ‚Ü‚·BBy H.Fujimura 1999/03/15 */
**	CMN_StringCopy( &prn_string[9], (UBYTE *)"`" );
#else
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
	CMN_StringCopy( &prn_string[9], (UBYTE *)"`" );
 #else
	prn_string[9]	= '-';
	prn_string[10]	= '-';
 #endif
#endif
	if (Data->StartTime == 0xFFFF) {	/* ŽžŽw’è–³‚µ‚ÌŽž */
		CMN_StringCopy( &prn_string[3], (UBYTE *)"**:**" );
		CMN_StringCopy( &prn_string[15], (UBYTE *)"**:**" );
	}
	else {
		CMN_UnsignedIntToASC( &prn_string[3], (UWORD)(Data->StartTime/60), 2, '0' );
		prn_string[5]	= ':';
		CMN_UnsignedIntToASC( &prn_string[6], (UWORD)(Data->StartTime%60), 2, '0' );
		CMN_UnsignedIntToASC( &prn_string[15], (UWORD)(Data->EndTime/60), 2, '0' );
		prn_string[17]	= ':';
		CMN_UnsignedIntToASC( &prn_string[18], (UWORD)(Data->EndTime%60), 2, '0' );
	}
}

/*************************************************************************
	module		:[—j“ú‚ðo—Í—p‚É•ÏŠ·]
	function	:[]
	return		:[
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1998/06/09]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
void SetLstWeekData(
			UBYTE	Day,
			UBYTE	*Pos )
{
	switch(Day) { 
	case	SYS_NICHI:				/* “ú—j“ú			*/
		*Pos	= LST_A_NICHI;
		break;
 	case	SYS_GETU:				/* ŒŽ—j“ú			*/
		*Pos	= LST_A_GETU;
		break;
	case	SYS_KA:					/* ‰Î—j“ú			*/
		*Pos	= LST_A_KA;
		break;
	case	SYS_SUI:				/* …—j“ú			*/
		*Pos	= LST_A_SUI;
		break;
	case	SYS_MOKU:				/* –Ø—j“ú			*/
		*Pos	= LST_A_MOKU;
		break;
	case	SYS_KIN:				/* ‹à—j“ú			*/
		*Pos	= LST_A_KIN;
		break;
	case	SYS_DOU:				/* “y—j“ú			*/
		*Pos	= LST_A_DOU;
		break;
	default:
		*Pos	= '-';
		break;
	}
}

#endif
