/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_BATB.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ˆêŠ‡‘—MBOXØ½Ä
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\sysdial.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\uni_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"

#if (PRO_PANEL == ANK)
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#endif

#if (PRO_PANEL == KANJI)
#include	"\src\atlanta\opr\kanji\define\opr_def.h"
#endif

#if (PRO_OKI == ENABLE)	/* by K.Watanabe 1999/02/09 */
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#endif

#if (PRO_BATCH_TX == ENABLE)
/*************************************************************************
	module		:[ˆêŠ‡‘—M‚a‚n‚wƒŠƒXƒgˆóü]
	function	:[ˆêŠ‡‘—M‚a‚n‚wƒŠƒXƒg‚ðˆóü‚·‚é]
	common		:[
		List				:
		SYB_BatchTxFile		:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 7]
	author		:[–L“c_Žq]
*************************************************************************/
WORD					Print_BatchTxBox_List(
						 void )					/*‚È‚µ*/
{
	register WORD	ret;						/*ŽÀsŒ‹‰Ê*/
	UBYTE	i;							/*loop*/

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/* ‚Ps‰üs{”­MŒ³–¼C”­MŒ³”Ô†{‚Qs‰üsˆóü{Œ©o‚µ{‚Ps‰üs */
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
	if ( (ret = Print_Head1_Common( PWRD_BatchTxBoxList_K,
	 LST_NOT,20-1 )) != OK ) {
		return ( ret );
	}

 #else
	if ( (ret = Print_Head1_Common( PWRD_BatchTxBoxList,
	  LST_XXX_TWI_XXX, 14 )) != OK ) {
		return ( ret );
	}

 #endif

	/* Œ»ÝŽžŠÔ */
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
	if (( ret = CurrentTimePrint( 60 - 1 )) != OK ) {
		return ( ret );
	}
 #else
	if (( ret = CurrentTimePrint( 56 - 1 )) != OK ) {
		return ( ret );
	}
 #endif

	/* „¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„¢†O †S */
	Print_BatchTxBox_List_Line( 5, List.S.Print, List.S.Attribute );
	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* „ No.„ ‘ŠŽèæ–¼„  †EÌ§¸½”Ô†	  „ Žw’è“úŽž„ †E */
	Print_BatchTxBox_List_Line( 6, List.S.Print, List.S.Attribute );
	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	for ( i = 0; i < SYS_BATCH_FILE_MAX; i++ ) {
		if ( SYB_BatchTxFile[i].DialNumber[0].Item != SYS_EMPTY_DIAL ) {
			/* „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„§†g */
			Print_BatchTxBox_List_Line( 7, List.S.Print, List.S.Attribute );
			if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			/* „ 99 „ xxxxxxx„ xxxxxxxxxxxxxxx„ xxxxx„ †E */
			Print_BatchTxBox_List_Line( 8, List.S.Print, List.S.Attribute );
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(i+OPR_BATCH_FILE_MIN), 2, ' ' );
			/*CMN_StringCopyNum( &List.S.Print[10-1], SYB_BatchTxFile[i].Name, 16 ); 1997/11/28 */
			CMN_StringCopyNumNotNULL( &List.S.Print[10-1], SYB_BatchTxFile[i].Name, 16 );
 #else
			CMN_UnsignedIntToASC( &List.S.Print[2-1], (UWORD)(i+OPR_BATCH_FILE_MIN), 2, ' ' );
			/*CMN_StringCopyNum( &List.S.Print[6-1], SYB_BatchTxFile[i].Name, 24 ); 1997/11/28 */
			CMN_StringCopyNumNotNULL( &List.S.Print[6-1], SYB_BatchTxFile[i].Name, 24 );
 #endif
			BatchTxFileDialDataToString( &SYB_BatchTxFile[i].DialNumber[0],1,List.S.Work,0 );
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			CMN_StringCopy( &List.S.Print[27-1], List.S.Work );
 #else
			CMN_StringCopy( &List.S.Print[31-1], List.S.Work );
 #endif
			/** Žw’è“úŽž‚ÌƒZƒbƒg C³ Î‹´³˜a 94/08/03 */
			/* CriterionMinuteToDayTimeAsc( (UDWORD)((SYB_BatchTxFile[i].ProgramTime & 0x7FFFFFFFUL)/60)
						, LST_DDHHMM, List.S.Work ); */ /** For ANZU By H.Hirao 1996/02/19 */

 #if (PRO_PANEL == KANJI)
			/* ‚o‚n‚o‚k‚`‚qQ‚g‚Í‚h‚b‚g‚n‚t‚Ì—¬—p‚È‚Ì‚ÅA‚`‚m‚jŒn‚ÌŽž“o˜^‚Æ‚ÍA‚P“ú‚Ì‚¸‚ê‚ª¶‚¶‚Ü‚·B
			** ‚æ‚Á‚ÄA‚h‚b‚g‚n‚t‚Æ“¯‚¶—p‚Éˆ—‚µ‚Ü‚·B
			** by O.Kimoto
			*/
			CriterionMinuteToDayTimeAsc(
						(UDWORD)((SYB_BatchTxFile[i].ProgramTime & 0x7FFFFFFFUL)/60),
						LST_DDHHMM, List.S.Work );
 #else
			MinuteToDayHourMinuteAsc(
						(WORD)((SYB_BatchTxFile[i].ProgramTime & 0x7FFFFFFF)/60),
						List.S.Work, LST_DATE_HOUR_MINUTE);
 #endif

			if (SYB_BatchTxFile[i].ProgramTime & 0x80000000UL) { /** –ˆ“ú‘—M‚Ìê‡ */
				List.S.Work[0] = ' ';
				List.S.Work[1] = '0';
			}
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			CMN_StringCopy( &List.S.Print[68-1], List.S.Work );
 #else
			CMN_StringCopy( &List.S.Print[72-1], List.S.Work );
 #endif
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
	}

	/* „¤„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„£	 */
	Print_BatchTxBox_List_Line( 9, List.S.Print, List.S.Attribute );
	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

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
	module		:[ˆêŠ‡‘—MŒ´e^‚a‚n‚wƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrüì¬]
	function	:[ˆêŠ‡‘—MŒ´e^‚a‚n‚wƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
		,	0 = †®†¢†¢†Î†¢†¢†¢„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ†¢†²
		,	1 = †¤ NO.†¤‘ŠŽèæ–¼†¤		   Žó•t”Ô†		  „ 
		,	2 = †¾†¢†¢†Þ†¢„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ†¢„Ÿ„Ÿ„Ÿ„Ÿ†¢†Æ
		,	3 = †¤	  †¤		†¤						  „ 
		,	4 = †¶†¢†¢†Ö†¢†¢„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ†¢„Ÿ„Ÿ†¢†º
		,	5 = †®†¢†¢†Î†¢†¢†¢„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ†¢†²
		,	6 = †¤ NO.†¤‘ŠŽèæ–¼†¤ÀÞ²ÔÙ”Ô† „ Žw’è“úŽž„ 
		,	7 = †¾†¢†¢†Þ†¢„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ†¢„Ÿ„©„Ÿ„Ÿ„Ÿ†¢†Æ
		,	8 = †¤	  †¤		†¤			„ 		  „ 
		,	9 = †¶†¢†¢†Ö†¢†¢„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨†¢„Ÿ„Ÿ†¢†º
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 7]
	author		:[–L“c_Žq]
*************************************************************************/
void					Print_BatchTxBox_List_Line( UBYTE Category		 /*ŒrüŽí—Þ*/
						, register UBYTE *AscString						 /*ˆóü•¶Žš—ñ*/
						, register UBYTE *AttString)					 /*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0 :
			/* „¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢†O †S @ˆêŠ‡‘—MŒ´eƒŠƒXƒg@*/
			AscString[1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_);
			AscString[5-1] = LST_KLINE8;
			AscString[22-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE9;
			break;
		case 1 :
			/* „ No.„ ‘ŠŽèæ–¼„ †E@@Žó•t”Ô†@@	„ †E */
			AscString[1-1] = LST_KLINEI;
			AttributeSet( &AscString[2-1], &AttString[2-1]
					, PWRD_No, LST_NOT );
			AscString[5-1] = LST_KLINEI;
			AttributeSet( &AscString[6-1], &AttString[6-1]
					, PWRD_RemoteLocation, LST_NOT ); /* 7->6 For ANZU By H.Hirao 1996/02/13 */
			AscString[22-1] = LST_KLINEI;
			AttributeSet( &AscString[45-1], &AttString[45-1]
					, PWRD_IndexNo, LST_NOT );		/* 48->45 For POPLA 97/03/11 M.Kuwahara */
			AscString[80-1] = LST_KLINEI;
			break;
		case 2 :
			/*	„¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§†g */
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_);
			AscString[5-1] = LST_KLINE5;
			AscString[22-1] = LST_KLINE5;
			AscString[80-1] = LST_KLINE6;
			break;
		case 3 :
			/* †E„ 	 „ †E	   „ 					„ 	 */
			AscString[1-1] = LST_KLINEI;
			AscString[5-1] = LST_KLINEI;
			AscString[22-1] = LST_KLINEI;
			AscString[80-1] = LST_KLINEI;
			break;
		case 4 :
			/* †W„¤„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„£	 */
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_);
			AscString[5-1] = LST_KLINE2;
			AscString[22-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE3;
			break;
		case 5 :
			/* „¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„¢†O †S @ˆêŠ‡‘—M‚a‚n‚wƒŠƒXƒg@*/
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			AscString[5-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[6-1], 70, LST_KLINE_);
			AscString[9-1] = LST_KLINE8;
			AscString[26-1] = LST_KLINE8;
			AscString[67-1] = LST_KLINE8;
			AscString[76-1] = LST_KLINE9;
 #else
			AscString[1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_);
			AscString[5-1] = LST_KLINE8;
			AscString[30-1] = LST_KLINE8;
			AscString[71-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE9;
 #endif
			break;
		case 6 :
			/* „ No.„ ‘ŠŽèæ–¼„   ÀÞ²ÔÙ”Ô†	  „ Žw’è“úŽž„ †E */
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			AscString[5-1] = LST_KLINEI;
			AttributeSet( &AscString[6-1], &AttString[6-1]
					, PWRD_No, LST_NOT );
			AscString[9-1] = LST_KLINEI;
			AttributeSet( &AscString[10-1], &AttString[10-1]
					,PWRD_RemoteLocation, LST_NOT );
			AscString[26-1] = LST_KLINEI; /* 11->10 For ANZU By H.Hirao 1996/02/13 */
			AttributeSet( &AscString[38-1], &AttString[38-1]
					,PWRD_TeleNumber, LST_NOT );
			AscString[67-1] = LST_KLINEI;
			AttributeSet( &AscString[68-1], &AttString[68-1]
					,PWRD_DelyTime, LST_NOT );
			AscString[76-1] = LST_KLINEI;
 #else
			AscString[1-1] = LST_KLINEI;
			AttributeSet( &AscString[2-1], &AttString[2-1]
					, PWRD_No, LST_NOT );
			AscString[5-1] = LST_KLINEI;
			AttributeSet( &AscString[9-1], &AttString[9-1]
					,PWRD_RemoteLocation, LST_NOT );
			AscString[30-1] = LST_KLINEI;
			AttributeSet( &AscString[42-1], &AttString[42-1]
					,PWRD_TeleNumber, LST_NOT );
			AscString[71-1] = LST_KLINEI;
			AttributeSet( &AscString[72-1], &AttString[72-1]
					,PWRD_DelyTime, LST_NOT );
			AscString[80-1] = LST_KLINEI;
 #endif
			break;
		case 7 :
			/* „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„§†g */
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			AscString[5-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[6-1], 70, LST_KLINE_);
			AscString[9-1] = LST_KLINE5;
			AscString[26-1] = LST_KLINE5;
			AscString[67-1] = LST_KLINE5;
			AscString[76-1] = LST_KLINE6;
 #else
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_);
			AscString[5-1] = LST_KLINE5;
			AscString[30-1] = LST_KLINE5;
			AscString[71-1] = LST_KLINE5;
			AscString[80-1] = LST_KLINE6;
 #endif
			break;
		case 8 :
				/* „ 	„ 		 „  †E			  „ 	 „ †E */
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			AscString[5-1] = LST_KLINEI;
			AscString[9-1] = LST_KLINEI;
			AscString[26-1] = LST_KLINEI;
			AscString[67-1] = LST_KLINEI;
			AscString[76-1] = LST_KLINEI;
 #else
			AscString[1-1] = LST_KLINEI;
			AscString[5-1] = LST_KLINEI;
			AscString[30-1] = LST_KLINEI;
			AscString[71-1] = LST_KLINEI;
			AscString[80-1] = LST_KLINEI;
 #endif
			break;
		case 9:
			/* „¤„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„£	 */
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			AscString[5-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[6-1], 70, LST_KLINE_);
			AscString[9-1] = LST_KLINE2;
			AscString[26-1] = LST_KLINE2;
			AscString[67-1] = LST_KLINE2;
			AscString[76-1] = LST_KLINE3;
 #else
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_);
			AscString[5-1] = LST_KLINE2;
			AscString[30-1] = LST_KLINE2;
			AscString[71-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE3;
 #endif
			break;
	}
}
#endif	/* (PRO_BATCH_TX == ENABLE) */

/*************************************************************************
	module		:[ˆêŠ‡‘—MboxÀÞ²ÔÙÃÞ°À•¶Žš—ñ•ÏŠ·B]
	function	:[ÀÞ²ÔÙÃÞ°À‚ð•¶Žš—ñ‚É•ÏŠ·‚·‚éB]
	common		:[
		•ÏŠ·æÌßÛ¸Þ×ÑÃÞ°À•¶Žš—ñ
			•K—v‚È‚¢Žž‚ÍAÇÙÎß²ÝÀ‚Æ‚·‚éB
	]
	condition	:[]
	commment	:[
		ÀÞ²ÔÙ‚ÌŽí•Ê‚ð”»•Ê‚µA•ÏŠ·Œ³ÀÞ²ÔÙÃÞ°À‚ðA‚Ps‚ÌÅ‘å•¶Žš”‚ð‚S‚O‚Æ‚µ‚½ŽžAs”Ô†‚ÅŽ¦‚³‚ê‚és‚É‚Í‚¢‚é•¶Žš—ñ‚ðA
		•ÏŠ·æÌßÛ¸Þ×ÑÃÞ°À•¶Žš—ñ‚ÉƒZƒbƒg‚·‚éB
	]
	return		:[
		‚Ps‚ÌÅ‘å•¶Žš”‚ð‚S‚O‚Æ‚µ‚½ŽžAÌßÛ¸Þ×ÑÃÞ°À‚ð‘S‚Äˆóü‚·‚é‚Ì‚É
		‰½s•K—v‚©‚ð•Ô‚·Bi‚P`j
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/02/19]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
#define	LN	40		/*‚Ps‚Ì•¶Žš”*/
UBYTE				BatchTxFileDialDataToString(
						 struct SYS_BatchTxDialData_t *DialData,/*•ÏŠ·Œ³ƒvƒƒOƒ‰ƒ€ƒf[ƒ^*/
						 UBYTE	DialDataMax,					/*•ÏŠ·Œ³ƒvƒƒOƒ‰ƒ€ƒf[ƒ^”*/
						 register UBYTE *DialString,			/*•ÏŠ·æƒvƒƒOƒ‰ƒ€ƒf[ƒ^•¶Žš—ñ*/
						 UBYTE	LineNumber )					/*s”Ô†*/
{
	UBYTE	i;								/*ÀÞ²ÔÙÃÞ°ÀˆÊ’uw*/
	UBYTE	j;								/*Œ»Ýs”Ô†w*/
	UBYTE	str_one[LN+1];					/*‚Ps•¶Žš—ñw*/
	UBYTE	string[SYS_DIRECT_DIAL_MAX*2+1];/*•¶Žš—ñw*/
	
	i = 0;
	j = 0;
	
	CMN_MemorySet( (UBYTE *)str_one, (LN+1), NULL );
	CMN_MemorySet( (UBYTE *)DialString, (LN+1), NULL );
	
	while ( DialData[i].Item != SYS_EMPTY_DIAL && i < DialDataMax ) {
		switch ( DialData[i].Item ) {
			case SYS_DIRECT_DIAL:
				CMN_BCD_ToASC_String( (UBYTE *)string, (UBYTE *)DialData[i].FaxNumber.Direct );
				L_string_over_chk( str_one, DialString, string, &j, LineNumber
				  , LN, LST_COMMA_STR_FRONT );
				break;
			case SYS_ONETOUCH_DIAL:
#if (PRO_KEYPANEL == PANEL_ANZU_L)
				/*CMN_UnsignedIntToASC(&string[0], DialData[i].FaxNumber.Onetouch, 2, '0');1997/11/27*/
				/*string[2] 	= NULL;*/

				if ( CMN_OffsetToOnetouchCode( DialData[i].FaxNumber.Onetouch ) <= 0x7A ){ /* •ÏX(ANZU) 96/01/10 H.HIRAO */
					CMN_MemorySet( (unsigned char far *)string, 3, ' ' );
					string[3] = NULL;
					string[0] = '[';
					string[1] = CMN_OffsetToOnetouchCode(
					  DialData[i].FaxNumber.Onetouch );
					string[2] = ']';
				} else{																/* 'U1'`'U2' */
					CMN_MemorySet( (unsigned char far *)string, 4, ' ' );
					string[4] = NULL;
					string[0] = '[';
					string[1] = 0x55; /* 'U'‚ÌASCIIº-ÄÞ */
					string[2] = CMN_OffsetToOnetouchCode( DialData[i].FaxNumber.Onetouch )
					 & (unsigned char)0x0F | (unsigned char)0x30; /* U1`U8‹L†‚ð‚Â‚­‚é */
					string[3] = ']';
				}

#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_PANEL == ANK)
				string[0]	= '[';
				CMN_UnsignedIntToASC( &string[1], 
									 (UWORD)(CMN_OffsetToOnetouchCode( DialData[i].FaxNumber.Onetouch ) - 0x40),
									 2, '0');
				string[3]	= ']';
 #endif
 #if (PRO_PANEL == KANJI)
		 		/* ƒƒ“ƒ^ƒbƒ`‚Ì•\Ž¦‚ð[]->ŠG•¶Žš‚É•ÏX By O.Kimoto 1998/01/22 */
				string[0]	= LCD_PICFONT;
				string[1]	= LCD_PICFONT_LOWER;
				CMN_UnsignedIntToASC( &string[2], 
									 (UWORD)(CMN_OffsetToOnetouchCode( DialData[i].FaxNumber.Onetouch ) - 0x40),
									 2, '0');
 #endif
				string[4] 	= NULL;
#endif
				L_string_over_chk( str_one, DialString, string, &j, LineNumber
				  , LN, LST_COMMA_STR_FRONT );
				break;
			case SYS_SPEED_DIAL:
				if (( SYS_SPEED_DIAL_MAX+SYS_2ND_SPEED_DIAL_MAX ) >= 100 ) {
#if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
					string[0] = *CalculateStringAddress(&D2W_HeadCharacter_Speed);
#else
					string[0] = 'S';
#endif
#if (1) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
					if (CHK_UNI_OptionalSpeedDial() != 0){	/* ”CˆÓ’Zk‚ÌŽž */
						if (GetRecordFromNumber((UWORD)DialData[i].FaxNumber.Speed) != 0xFFFF) {
							CMN_UnsignedIntToASC((UBYTE*)&string[1], GetRecordFromNumber((UWORD)DialData[i].FaxNumber.Speed), OP_SPEED_FIGURE_MAX, '0');
						}
						else {
							CMN_MemorySet((UBYTE*)&string[1], OP_SPEED_FIGURE_MAX, '*');
						}
						string[1 + OP_SPEED_FIGURE_MAX] = NULL;
					}
					else{	/* ’Êí‚Ì’Zk‚ÌŽž */
						CMN_UnsignedIntToASC((UBYTE*)&string[1], DialData[i].FaxNumber.Speed+(OPR_SPEED_DIAL_MIN), 3, '0');
						string[4] = NULL;
					}
#else
//					if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
//						if ( GetRecordFromNumber( (UWORD)DialData[i].FaxNumber.Speed ) != 0xFFFF ) {
//							CMN_UnsignedIntToASC( (UBYTE *)&string[1],
//							  GetRecordFromNumber((UWORD)DialData[i].FaxNumber.Speed), 3, '0' );
//						}
//						else {
//							CMN_MemorySet( (UBYTE *)&string[1], 3,'*' );
//						}
//					}
//					else{	/* ’Êí‚Ì’Zk‚ÌŽž */
//						CMN_UnsignedIntToASC( (UBYTE *)&string[1],
//						  DialData[i].FaxNumber.Speed+(OPR_SPEED_DIAL_MIN), 3, '0' );
//					}
//					string[4] = NULL;
#endif
				}
				else {
					string[0] = '(';
					if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
						if ( GetRecordFromNumber( (UWORD)DialData[i].FaxNumber.Speed ) != 0xFFFF ) {
							CMN_UnsignedIntToASC( (UBYTE *)&string[1],
							  GetRecordFromNumber((UWORD)DialData[i].FaxNumber.Speed), 2, '0' );
						}
						else {
							CMN_MemorySet( (UBYTE *)&string[1], 3,'*' );
						}
					}
					else{		/* ’Êí‚Ì’Zk‚ÌŽž */
						CMN_UnsignedIntToASC( (UBYTE *)&string[1],
						  DialData[i].FaxNumber.Speed+(OPR_SPEED_DIAL_MIN), 2, '0' );
					}
					string[3] = NULL;
				}
				L_string_over_chk( str_one, DialString, string, &j, LineNumber
				  , LN, LST_COMMA_STR_FRONT );
				break;

			case SYS_GROUP_DIAL:
				string[0] = 'G';
				CMN_UnsignedIntToASC_NULL( (UBYTE *)&string[1],
				  DialData[i].FaxNumber.Group, 0, 0 );
				L_string_over_chk( str_one, DialString, string, &j, LineNumber
				  , LN, LST_COMMA_STR_FRONT );
				break;
		}
		i++;
	}
	return ( (UBYTE)( j+1 ) );
}
#undef	LN

