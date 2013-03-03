/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_CVR.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒJƒo[ƒy[ƒWƒvƒŠƒ“ƒg
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
#include	"\src\atlanta\ext_v\sys_data.h"
/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if(PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* ˆãŽt‰ï“Á‚q‚n‚l By O.Kimoto 1999/04/01 */
#include	"\src\atlanta\ext_v\fcm_data.h"
 #endif
#endif

/*************************************************************************
	module		:[ƒJƒo[ƒy[ƒWˆóü]
	function	:[ƒJƒo[ƒy[ƒWƒg‚ðˆóü‚·‚é]
	common		:[
		SYB_CurrentTime	:
		SYB_TTI_Buffer	:
		SYB_ID_Buffer	:
	]
	condition	:[
		ŽÀsÓ°ÄÞ		LST_MODE_PRINT	ˆóü
		,				LST_MODE_LINE		‚Psì¬
		,	ŽÀsƒ‚[ƒh‚ªˆóü‚ÌŽž‚ÍA‘—MˆÄ“àØ‚ðˆóü‚·‚éBŽÀsƒ‚[ƒh‚ª
		,	‚Psì¬‚ÌŽž‚ÍA‘ÎÛs‚ÌŽw‚·s‚Ìsƒf[ƒ^‚ð‚Ps•¶Žš—ñ‚É
		,	ƒZƒbƒg‚µ•Ô‚·B
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD				Print_CoverPage_List(
					    UBYTE Mode,				/*ŽÀsƒ‚[ƒh*/
						UBYTE *AscString,		/*ˆóü•¶Žš—ñ*/
						UBYTE *AttString,		/*Cü•¶Žš—ñ*/
						UBYTE Line,				/*‘ÎÛsi‚P`j*/
						UBYTE stack_number)
{
	UBYTE	start_i;				/*ˆóüŠJŽns*/
	UBYTE	end_i;					/*ˆóüI—¹s*/
	UBYTE	i;						/*loop*/
	UBYTE	work[21];				/*•¶Žš—ñƒ[ƒN*/
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

#if (PRO_QUICK_TX_TEST == ENABLE)
	Line = 14;
#endif

	if ( Mode == LST_MODE_PRINT ) {
		start_i = 0;
		end_i = CVR_LINES+1;				/*LIST_MSG.H*/
	}
	else {
		start_i = Line;
		end_i = Line;
	}
	for ( i = start_i; i <= end_i; i++ ) {
		Prn_Att_Str_Clear( AscString, AttString );
		switch ( i ) {
			case	0:
				if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
					return ( ret );
				}
				break;
			case	1:
			case	2:
			case	17:
			case	18:
				/*‚PsˆóŽši‰üsj*/
				break;
			case	3:
				/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
				Print_CoverPage_List_Line( 0, AscString, AttString );
				break;
			case	4:
			case	6:
			case	8:
			case	9:
			case	12:
			case	13:
			case	15:
				/*†¤						†¤*/
				Print_CoverPage_List_Line( 1, AscString, AttString );
				break;
			case	5:
				/*†¤  ¿³¼Ý±ÝÅ²¼®³			†¤*/
				Print_CoverPage_List_Line( 1, AscString, AscString );
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		AttributeSet( (AscString + 20), (AttString + 20),
			PWRD_CoverPageMes_K, LST_NOT );
			/* C³ Î‹´³˜a 94/08/24 (V53‚Ìê‡AƒŠƒXƒg‚Æ‘—M—p‚Ìƒoƒbƒtƒ@‚ªˆÙ‚È‚é) */
		/* AttributeSet( &List.S.Print[21-1], &List.S.Attribute[21-1],
		  PWRD_CoverPageMes_K, LST_NOT ); */
#else
		AttributeSet( (AscString + 22), (AttString + 22),
			PWRD_CoverPageMes, LST_XXX_TWI_XXX );
		/**	ƒŠƒXƒg‚Æ‘—M—p‚Ìƒoƒbƒtƒ@‚ªˆÙ‚È‚é By H.Hirao 1996/03/01	*/
		/* AttributeSet( &List.S.Print[23-1], &List.S.Attribute[23-1],
		  PWRD_CoverPageMes, LST_XXX_TWI_XXX ); */

#endif
				break;
			case	7:
				/*†¤  Œ»Ý“úŽž				†¤*/
				Print_CoverPage_List_Line( 1, AscString, AttString );
				TimeDataAscii( OFF, SYB_CurrentTime, work, 0 );
				CMN_StringCopy( &AscString[31-1], work );
				break;
			case	10:
				/*†¤  Ê¯¼ÝÓÄÒ²				†¤*/
				Print_CoverPage_List_Line( 1, AscString, AttString );
				AttributeSet( &AscString[27-1], &AttString[27-1],
				  PWRD_SubscriberID, LST_NOT );
				if (stack_number == 0) {

/* ‚o‚n‚o‚k‚`‚qQ‚g •W€‚Q‰ñüŽû—e‘Î‰ž‚Ìˆ× By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
					if (Mode == LST_MODE_PRINT) {
						CMN_StringCopy( &AscString[41-1], &SYB_TTI_Buffer[0][0] );
					}
					else {
						if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
							CMN_StringCopy( &AscString[41-1], &SYB_Multi_TTI_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][0] );
						}
						else {
							CMN_StringCopy( &AscString[41-1], &SYB_TTI_Buffer[SYS_InternalLineNumber][0] );
						}
					}
 #else
					if (Mode == LST_MODE_PRINT) {
						CMN_StringCopy( &AscString[41-1], &SYB_TTI_Buffer[0][0] );
					}
					else {
						CMN_StringCopy( &AscString[41-1], &SYB_TTI_Buffer[SYS_InternalLineNumber][0] );
					}
 #endif
#else
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
					if (Mode == LST_MODE_PRINT) {
						CMN_StringCopy( &AscString[41-1], &SYB_TTI_Buffer[0] );
					}
					else {
						if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
							CMN_StringCopy( &AscString[41-1], &SYB_Multi_TTI_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][0] );
						}
						else {
							CMN_StringCopy( &AscString[41-1], &SYB_TTI_Buffer[0] );
						}
					}
 #else
					CMN_StringCopy( &AscString[41-1], &SYB_TTI_Buffer[0] );
 #endif
#endif

				}
				else {
					CMN_StringCopy( &AscString[41-1], &SYB_Option_TTI_Buffer[stack_number][0] );
				}
				break;
			case	11:
				/*†¤  Ì§¯¸½ÊÞÝºÞ³			†¤*/
				Print_CoverPage_List_Line( 1, AscString, AttString );
				AttributeSet( &AscString[27-1], &AttString[27-1],
				  PWRD_SubscriberNb, LST_NOT );
				if (stack_number == 0) {

/* ‚o‚n‚o‚k‚`‚qQ‚g •W€‚Q‰ñüŽû—e‘Î‰ž‚Ìˆ× By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
					if (Mode == LST_MODE_PRINT) {
						CMN_StringCopy( &AscString[41-1], &SYB_ID_Buffer[0][0] );
					}
					else {
						if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
							CMN_StringCopy( &AscString[41-1], &SYB_Multi_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][0] );
						}
						else {
							CMN_StringCopy( &AscString[41-1], &SYB_ID_Buffer[SYS_InternalLineNumber][0] );
						}
					}
 #else
					if (Mode == LST_MODE_PRINT) {
						CMN_StringCopy( &AscString[41-1], &SYB_ID_Buffer[0][0] );
					}
					else {
						CMN_StringCopy( &AscString[41-1], &SYB_ID_Buffer[SYS_InternalLineNumber][0] );
					}
 #endif
#else
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
					if (Mode == LST_MODE_PRINT) {
						CMN_StringCopy( &AscString[41-1], &SYB_ID_Buffer[0] );
					}
					else {
						if ('1' <= SYS_Multi_PinBuffer[0] && SYS_Multi_PinBuffer[0] <= '9') {
							CMN_StringCopy( &AscString[41-1], &SYB_Multi_ID_Buffer[SYS_Multi_PinBuffer[0]-'0'-1][0] );
						}
						else {
							CMN_StringCopy( &AscString[41-1], &SYB_ID_Buffer[0] );
						}
					}
 #else
					CMN_StringCopy( &AscString[41-1], &SYB_ID_Buffer[0] );
 #endif
#endif

				}
				else {
					CMN_StringCopy( &AscString[41-1], &SYB_Option_ID_Buffer[stack_number][0] );
				}
				break;
			case	14:

#if (PRO_QUICK_TX_TEST == ENABLE)
				/*†¤  [					]	†¤*/
				Print_CoverPage_List_Line( 1, AscString, AttString );
				/**	ˆÇ‚Å‚ÍA"[ ]"‚ð‚È‚­‚·Žd—l By H.Hirao 1996/04/01	*/
				/**	ƒ|ƒvƒ‰‚Å‚ÍA"[ ]"‚ð“ü‚ê‚éŽd—l 1997/10/27  By T.Yamaguchi	*/

				CMN_StringCopy( &AscString[1], SYB_CoverPageMessage );
				CMN_StringCopy( &AscString[40], SYB_CoverPageMessage );
	/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
	#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)  || (PRO_KEYPANEL == PANEL_SAKAKI) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)							/* Add by Y.Kano 2003/07/11 */
				AscString[0] = '[';
				AscString[80] = ']';
	#endif

#else
				/*†¤  [					]	†¤*/
				Print_CoverPage_List_Line( 1, AscString, AttString );
				/**	ˆÇ‚Å‚ÍA"[ ]"‚ð‚È‚­‚·Žd—l By H.Hirao 1996/04/01	*/
				/**	ƒ|ƒvƒ‰‚Å‚ÍA"[ ]"‚ð“ü‚ê‚éŽd—l 1997/10/27  By T.Yamaguchi	*/
	/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
	#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)  || (PRO_KEYPANEL == PANEL_SAKAKI) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)							/* Add by Y.Kano 2003/07/11 */
				AscString[20-1] = '[';
				AscString[61-1] = ']';
	#endif
				CMN_StringCopy( &AscString[21-1], SYB_CoverPageMessage );
#endif
				break;
			case	16:
				/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
				Print_CoverPage_List_Line( 2, AscString, AttString );
				break;
			case	19:
				if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
					return ( ret );
				}
				break;
		}
		if ( Mode == LST_MODE_PRINT ) {
			if ( i != start_i && i != end_i ) {
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
			}
		}
	}
	return ( OK );
}

/*************************************************************************
	module		:[ƒJƒo[ƒy[ƒWƒvƒŠƒ“ƒg‚Ì‰¡‹æØ‚èŒrüì¬]
	function	:[ƒJƒo[ƒy[ƒWƒvƒŠƒ“ƒg‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
		,	0 = †®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²
		,	1 = †¤						  †¤
		,	2 = †¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
void				Print_CoverPage_List_Line(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
			AscString[11-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[12-1], 58, LST_KLINE_ );
			AscString[70-1] = LST_KLINE9;
			break;
		case 1:
			/*†¤						†¤*/
			AscString[11-1] = LST_KLINEI;
			AscString[70-1] = LST_KLINEI;
			break;
		case 2:
			/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
			AscString[11-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[12-1], 58, LST_KLINE_ );
			AscString[70-1] = LST_KLINE3;
			break;
	}
}
/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if(PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* ˆãŽt‰ï“Á‚q‚n‚l By O.Kimoto 1999/04/01 */
/*************************************************************************
	module		:[ƒJƒo[ƒy[ƒWˆóü]
	function	:[ƒJƒo[ƒy[ƒWƒg‚ðˆóü‚·‚é]
	common		:[
		SYB_CurrentTime	:
		SYB_TTI_Buffer	:
		SYB_ID_Buffer	:
	]
	condition	:[
		ŽÀsÓ°ÄÞ		LST_MODE_PRINT	ˆóü
		,				LST_MODE_LINE		‚Psì¬
		,	ŽÀsƒ‚[ƒh‚ªˆóü‚ÌŽž‚ÍA‘—MˆÄ“àØ‚ðˆóü‚·‚éBŽÀsƒ‚[ƒh‚ª
		,	‚Psì¬‚ÌŽž‚ÍA‘ÎÛs‚ÌŽw‚·s‚Ìsƒf[ƒ^‚ð‚Ps•¶Žš—ñ‚É
		,	ƒZƒbƒg‚µ•Ô‚·B
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD				Print_EmergencyReport_List(
					    UBYTE Mode,				/*ŽÀsƒ‚[ƒh*/
						UBYTE *AscString,		/*ˆóü•¶Žš—ñ*/
						UBYTE *AttString,		/*Cü•¶Žš—ñ*/
						UBYTE Line,				/*‘ÎÛsi‚P`j*/
						UBYTE stack_number)
{
	UBYTE	start_i;				/*ˆóüŠJŽns*/
	UBYTE	end_i;					/*ˆóüI—¹s*/
	UBYTE	i;						/*loop*/
	UBYTE	work[21];				/*•¶Žš—ñƒ[ƒN*/
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Mode == LST_MODE_PRINT ) {
		start_i = 0;
		end_i = CVR_LINES+1;				/*LIST_MSG.H*/
	}
	else {
		start_i = Line;
		end_i = Line;
	}
	for ( i = start_i; i <= end_i; i++ ) {
		Prn_Att_Str_Clear( AscString, AttString );
		switch ( i ) {
			case	0:
				if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
					return ( ret );
				}
				break;
			case	1:
			case	2:
				/*‚PsˆóŽši‰üsj*/
				break;
			case	3:
				/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
				Print_CoverPage_List_Line( 0, AscString, AttString );
				break;
			case	4:
				/*†¤  ¿³¼Ý±ÝÅ²¼®³			†¤*/
				Print_CoverPage_List_Line( 1, AscString, AscString );

				if ((CommandFileTitleMessage & 0xf0) == 0x10) {
					AttributeSet( (AscString + 15), (AttString + 15),PWRD_EmergencyTitle_Emergency_K, LST_NOT );
				}
				else {
					AttributeSet( (AscString + 15), (AttString + 15),PWRD_EmergencyTitle_Normal_K, LST_NOT );
				}

				/*†¤  Œ»Ý“úŽž				†¤*/
				TimeDataAscii( OFF, SYB_CurrentTime, work, 0 );
				CMN_StringCopy( &AscString[48-1], work );
				break;
			case	5:
				/*†¤  Ê¯¼ÝÓÄÒ²				†¤*/
				Print_CoverPage_List_Line( 1, AscString, AttString );
				AttributeSet( &AscString[27-1], &AttString[27-1],
				  PWRD_SubscriberID, LST_NOT );
				if (stack_number == 0) {

					CMN_StringCopy( &AscString[41-1], &SYB_TTI_Buffer[0] );
				}
				else {
					CMN_StringCopy( &AscString[41-1], &SYB_Option_TTI_Buffer[stack_number][0] );
				}
				break;
			case	6:
				/*†¤  Ì§¯¸½ÊÞÝºÞ³			†¤*/
				Print_CoverPage_List_Line( 1, AscString, AttString );
				AttributeSet( &AscString[27-1], &AttString[27-1],
				  PWRD_SubscriberNb, LST_NOT );
				if (stack_number == 0) {

					CMN_StringCopy( &AscString[41-1], &SYB_ID_Buffer[0] );
				}
				else {
					CMN_StringCopy( &AscString[41-1], &SYB_Option_ID_Buffer[stack_number][0] );
				}
				break;
			case	7:

				/*†¤  [					]	†¤*/
				Print_CoverPage_List_Line( 1, AscString, AttString );
				/**	ˆÇ‚Å‚ÍA"[ ]"‚ð‚È‚­‚·Žd—l By H.Hirao 1996/04/01	*/
				/**	ƒ|ƒvƒ‰‚Å‚ÍA"[ ]"‚ð“ü‚ê‚éŽd—l 1997/10/27  By T.Yamaguchi	*/
	/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
	#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)  || (PRO_KEYPANEL == PANEL_SAKAKI) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)								/* Add by Y.Kano 2003/07/11 */
				AscString[20-1] = '[';
				AscString[61-1] = ']';
	#endif
				CMN_StringCopy( &AscString[21-1], SYB_CoverPageMessage );
				break;
			case	8:
				/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
				Print_CoverPage_List_Line( 2, AscString, AttString );
				break;
			case	9:
				if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
					return ( ret );
				}
				break;
		}
		if ( Mode == LST_MODE_PRINT ) {
			if ( i != start_i && i != end_i ) {
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
			}
		}
	}
	return ( OK );
}
 #endif
#endif

