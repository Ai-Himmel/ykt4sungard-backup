/*************************************************************************
*	System		: SAKAKI
*	File Name	: LST_MCR.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1998/05/20
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒCƒŠƒXƒg
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

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* 1998/06/24 By M.Kuwahara */

struct SYS_DialData_t	LST_ND_Dial;	/* ƒ_ƒCƒ„ƒ‹”Ô†o—Íƒ[ƒN */

/*************************************************************************
	module		:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒCƒŠƒXƒg]
	function	:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒCƒŠƒXƒg‚ðˆóü‚·‚é]
	common		:[
		List		:
		SYB_KeyMacro
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/05/19]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD				Print_ND_List(
						 void )				/*‚È‚µ*/
{
	UBYTE	i;						/*loop*/
	UBYTE 	page;					/*Íß°¼Þ*/
	UBYTE	nd_cnt;					/*ÅÝÊÞ°ÃÞ¨½ÌßÚ²ÃÞ°À”Ô†*/
	UBYTE 	line_cnt;				/*Žc‚èˆóü‰Â”\s”*/
	UBYTE	item;					/* o—Íj–Ú”Ô† */
	register WORD	ret;			/*ŽÀsŒ‹‰Ê*/

	i		= 0;
	page 	= 1;
	nd_cnt	= 0;
	item	= 0;
	DialCheckPointer	= SYS_DIRECT_DIAL;
	DialCheckBitPointer	= 0;

	nd_cnt = ND_DataNextSearch( nd_cnt );	/*ŽŸÃÞ°À»°Á */
	if ( nd_cnt == SYS_ND_MAX ) {
		return ( MSG_PRN_LST_NO_LIST );
	}
	while ( nd_cnt != SYS_ND_MAX ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}

		if ( page == 1 ) {
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		else {
			line_cnt = (UBYTE)(PaperSizeLen() - 4);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		if ( (ret = Print_ND_List_Head( 0, page ) ) != OK ) {/*Í¯ÀÞˆóü*/
			return ( ret );
		}

		for (;;) {
			/*ˆóü—\’ès”‚ªˆóü‰Â”\‚©”»’f*/
			/* ‚P–¾×ˆóü */
			if ((item == 0) && 	/* ‚P–¾×‚Ìæ“ªs */
				(line_cnt <= 1)) {
				break;
			}
			if ( (ret = Print_ND_List_Specifi( &item, page ,&i, nd_cnt, &line_cnt) ) != OK ) {
				return (ret);
			}
			if (item == 0) {	/* ŽŸ‚Ì–¾×‚ðŒŸõ */
				nd_cnt++;
				nd_cnt = ND_DataNextSearch( nd_cnt );	/*ŽŸÃÞ°À»°Á */
				if (nd_cnt == SYS_ND_MAX) {
					break;
				}
				DialCheckPointer	= SYS_DIRECT_DIAL;
				i	= 0;
			}
			if (line_cnt <= 0) {
				break;
			}
		}
		if ( (ret = Print_ND_List_Head( 1, page) ) != OK ) {	/*Ì¯Àˆóü*/
			return (ret);
		}

		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return (ret);
		}
		page++;
	}
	return ( OK );
}

/*************************************************************************
	module		:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒCƒwƒbƒ_ˆóü]
	functiom	:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
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
	date		:[98/06/08]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD				Print_ND_List_Head(
						 UBYTE Category,	/*ƒwƒbƒ_Ží—Þ*/
						 UBYTE Page )		/*ƒy[ƒW*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Category == 0 ) {
		if ( Page == 1 ) {

			/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs{Œ©o‚µ{‚P‰üs*/
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			if ( (ret = Print_Head1_Common( PWRD_NumberDisplayList_K,
			 LST_NOT, 15-1 )) != OK ) {
				return ( ret );
			}
#else
			if ( (ret = Print_Head1_Common( PWRD_NumberDisplayList,
			  LST_XXX_TWI_XXX, 15-1 )) != OK ) {
				return ( ret );
			}
#endif
			/*Œ»ÝŽžŠÔ*/
			/*Page Œ»ÝŽžŠÔ*/
			if ( (ret = PageTimePrint( Page, 6-1, 55-1 )) != OK ) {
				return ( ret );
			}

			/*†®†¢†Î†¢†¢†¢†¢†¢†²*/
			Print_ND_List_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤‘ŠŽèæ–¼†¤  ÀÞ²ÔÙ”Ô†   †¤*/
			Print_ND_List_Line( 1, List.S.Print, List.S.Attribute );
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
			if ( (ret = PagePrint( Page, 6-1 )) != OK ) {
				return ( ret );
			}
		}
	}
	else {
		/*†¶†¢†¢†Ö†¢†¢†¢†¢†º*/
		Print_ND_List_Line( 4, List.S.Print, List.S.Attribute );
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
	module		:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒCƒ_ƒCƒ„ƒ‹ ƒlƒNƒXƒg ƒT[ƒ`n
	functiom	:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒCƒ_ƒCƒ„ƒ‹‚ÌŽŸ‚ðƒT[ƒ`‚·‚é]
	common		:[
		SYB_NumberDisplay	:
	]
	condition	:[
		,	ƒf[ƒ^ƒGƒ“ƒh->SYS_ND_MAX
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/06/08]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
UBYTE		ND_DataNextSearch(
					 UBYTE ND_Cnt)	/*ƒƒ“ƒ^ƒbƒ`ƒ_ƒCƒ„ƒ‹ƒf[ƒ^”Ô†*/
{
	UBYTE	i;

	for (i = ND_Cnt; i < SYS_ND_MAX; i++) {
		if (SYB_NumberDisplay[i].Dial[0] != '\0') {
			break;
		}
	}
	return (i);
}


/*************************************************************************
	module		:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC‚Ì‚P–¾×ˆóü]
	functiom	:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC‚Ì‚P–¾×‚ðˆóü‚·‚éB]
	common		:[
		List				:
		SYB_NumberDisplay		:
	]
	condition	:[
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/06/08]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD			Print_ND_List_Specifi(
					 UBYTE *Item,		/* o—Í€–Ú */
					 UBYTE Page,		/*ƒy[ƒW*/
					 UBYTE *Line,		/*Œ»Ý–¾×”*/
					 UBYTE ND_Cnt,		/*ƒf[ƒ^”Ô†*/
					 UBYTE *LineCnt )	/*ˆóŽšsˆÊ’u*/
{
	UBYTE	i;
	UBYTE	check_line;
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	check_line = (UBYTE)(PaperSizeLen() - 4);

	if ((Page > 1) &&	/* ‚Qƒy[ƒW–ÚˆÈ~‚Ìæ“ªs‚ÌŽž */
		(*LineCnt == (PaperSizeLen() - 4))) {
		/*†¾†¢†¢†Þ†¢†¢†¢†Æ*/
		Print_ND_List_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*LineCnt)--;
	}
	else {
		if (*Item == 0) {	/* ‘ŠŽèæ–¼AÀÞ²ÔÙ”Ô†o—Í */
			/*†¾†¢†¢†Þ†¢†¢†¢†Æ*/
			Print_ND_List_Line( 2, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			(*LineCnt)--;
		}
	}

	/* ƒ[ƒN—p‚Ìƒf[ƒ^ƒZƒbƒg */
	for (i = 0; i < SYS_COM_DIRECT_DIAL_MAX ; i++) {
		LST_ND_Dial.Direct[i][0] = 0xFF;
	}
	CMN_StringCopyNum((UBYTE *)&LST_ND_Dial.Direct[0],
						   SYB_NumberDisplay[ND_Cnt].WarpData.Direct,
						   SYS_DIRECT_DIAL_MAX );

	for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
		LST_ND_Dial.Onetouch[i] = SYB_NumberDisplay[ND_Cnt].WarpData.Onetouch[i];
	}
	for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
		LST_ND_Dial.Speed[i] = SYB_NumberDisplay[ND_Cnt].WarpData.Speed[i];
	}
	LST_ND_Dial.Group = SYB_NumberDisplay[ND_Cnt].WarpData.Group;

	while( *LineCnt != 0 ){
		Print_ND_List_Line( 3, List.S.Print, List.S.Attribute );
		switch (*Item) {		/* o—Í€–Ú”Ô† */
		case	0:	/* No, ‘ŠŽèæ–¼AÀÞ²ÔÙ”Ô†o—Í */
			/*†¤xx†¤xxxxxxx†¤99999999999†¤*/
			/** No. */
			CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(ND_Cnt+1), 2, ' ' );
			/** ‘ŠŽèæ–¼ */
			CMN_StringCopy( &List.S.Print[10-1], SYB_NumberDisplay[ND_Cnt].Name );
			/** ƒ_ƒCƒ„ƒ‹”Ô† */
			CMN_StringCopy( &List.S.Print[35-1], SYB_NumberDisplay[ND_Cnt].Dial );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			(*LineCnt)--;
			if (SYB_NumberDisplay[ND_Cnt].WarpData.Status == SYS_WARP_EMPTY) {
				(*Item) = 0;
				return( OK );
			}
			*Item = 1;
			break;
		case	1:	/* “]‘—æo—Í */
			if (*Line == 0) {
				AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_AltNo, LST_NOT );
			}
			/** ÀÞ²ÔÙ”Ô†‚Ì•¶Žš—ñ•ÏŠ· */
			ret = ProgramDataDialToString( (struct SYS_DialData_t *)&LST_ND_Dial, SYS_PRG_DIAL_MAX, List.S.Work, *Line );
			CMN_StringCopy( &List.S.Print[35-1], List.S.Work );
			if (DialCheckPointer == SYS_EMPTY_DIAL) {	/* ‘S–¾×“à—eo—Í */
				(*Item) = 2;
			}
			else {
				(*Line)++;
			}
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			(*LineCnt)--;
			break;
		case	2:	/* Žw’èŽžo—Í */
			/*†¤(Žw’èŽž)†¤XXXXXXXXXXXXXXXXXXXX†¤*/
			List.S.Print[10-1] = '(';
			AttributeSet( &List.S.Print[11-1], &List.S.Attribute[11-1], PWRD_AppointedTime, LST_NOT );
			List.S.Print[19-1] = ')';
			WarpTimeDataSet((struct SYS_SubDialData_t *)&SYB_NumberDisplay[ND_Cnt].WarpData, &List.S.Print[35-1] );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			(*LineCnt)--;
			(*Item) = 3;
			break;
		case	3:	/* “¯ŽžÌßØÝÄ */
			/*†¤(“¯ŽžÌßØÝÄ)†¤XXX                †¤*/
			List.S.Print[10-1] = '(';
			AttributeSet( &List.S.Print[11-1], &List.S.Attribute[11-1], PWRD_RxPrint, LST_NOT );
			List.S.Print[21-1] = ')';
			if (SYB_NumberDisplay[ND_Cnt].WarpData.Option & WARP_OPTION_PRINT) {
				AttributeSet( &List.S.Print[35-1], &List.S.Attribute[35-1], PWRD_On, LST_NOT );
			}
			else {
				AttributeSet( &List.S.Print[35-1], &List.S.Attribute[35-1], PWRD_Off, LST_NOT );
			}
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			(*LineCnt)--;
			(*Item) = 0;
			return( OK );
			break;
		default:
			break;
		}
	}
	return( OK );
}


/*************************************************************************
	module		:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒCƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrüì¬]
	function	:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒCƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB
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
void			Print_ND_List_Line(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†¤†¤†¤†¤†¤†¤†¤†Î†¢†¢†¢†¢†¢†²*/
			AscString[5-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[6-1], 69, LST_KLINE_ );
			AscString[9-1] = LST_KLINE8;
			AscString[34-1] = LST_KLINE8;
			AscString[75-1] = LST_KLINE9;
			break;
		case 1:
			/*†¤No.†¤‘ŠŽèæ–¼†¤  ÀÞ²ÔÙ”Ô†  †¤*/
			AscString[5-1] = LST_KLINEI;
			AttributeSet( &AscString[6-1], &AttString[6-1], PWRD_No, LST_NOT );
			AscString[9-1] = LST_KLINEI;
			AttributeSet( &AscString[16-1], &AttString[16-1], PWRD_BoxLocation, LST_NOT );
			AscString[34-1] = LST_KLINEI;
			AttributeSet( &AscString[49-1], &AttString[49-1], PWRD_TelNum, LST_NOT );
			AscString[75-1] = LST_KLINEI;
			break;
		case 2:
			/*†¾†¤†¤†¤†¤†¤†¢†¢†Þ†¢†¢†¢†Æ*/
			AscString[5-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[6-1], 69, LST_KLINE_ );
			AscString[9-1] = LST_KLINE5;
			AscString[34-1] = LST_KLINE5;
			AscString[75-1] = LST_KLINE6;
			break;
		case 3:
			/*†¤ †¤       †¤          †¤*/
			AscString[5-1] = LST_KLINEI;
			AscString[9-1] = LST_KLINEI;
			AscString[34-1] = LST_KLINEI;
			AscString[75-1] = LST_KLINEI;
			break;
		case 4:
			/*†¶†¢†¢†Ö†¢†¢†¢†¢†º†¤†¤†¤†¤*/
			AscString[5-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[6-1], 69, LST_KLINE_ );
			AscString[9-1] = LST_KLINE2;
			AscString[34-1] = LST_KLINE2;
			AscString[75-1] = LST_KLINE3;
			break;
	}
}

#endif
