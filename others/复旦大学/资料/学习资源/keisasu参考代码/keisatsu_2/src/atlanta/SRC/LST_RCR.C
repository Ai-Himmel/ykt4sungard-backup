/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_RCR.C
*	Author		: åKå¥ î¸ãI
*	Date		: 1997/03/11
*	RealTimeOS	: ÇqÇhÇrÇbÅiÇrÇgÇVÇOÇSÇRÅjÉÇÉjÉ^Å[
*	Description	: éÛóÃèÿ
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
#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_v\mlt_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"

#include	"\src\memsw\define\mems_pro.h"

/*************************************************************************
	module		:[éÛóÃèÿÉtÉHÅ[É}ÉbÉgçÏê¨]
	function	:[éÛóÃèÿÇàÛç¸Ç∑ÇÈà◊ÇÃï∂éöóÒÉfÅ[É^ÇçÏê¨Ç∑ÇÈ]
	common		:[
		SYB_TTI_Buffer	:
		SYB_ID_Buffer	:
		SYB_CurrentTime	:
		NonStandardID	:
		StandardID		:
		SYB_JournalPoint:
		SYB_JournalFile	:
		SYS_RxMode		:
		SYS_FaxComPeriod:
		SYS_RxTotalPage	:
	]
	condition	:[]
	commment	:[
		ëŒè€çsÇÃéwÇ∑çsÇÃçsÉfÅ[É^ÇÇPçsï∂éöóÒÇ…ÉZÉbÉgÇµï‘Ç∑ÅB
		94/10/06 By j.masuda
			í î‘ÇÇSåÖÇ©ÇÁÇRåÖÇ…èCê≥


	]
	return		:[Ç»Çµ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[ëùìcéüòY]
*************************************************************************/
void			Print_RxConf_List(
						 UBYTE *AscString,			/*àÛç¸ï∂éöóÒ*/
						 register UBYTE *AttString,	/*èCè¸ï∂éöóÒ*/
						 UBYTE Line,				/*ëŒè€çsÅiÇPÅ`Åj*/
						 UBYTE stack_number)
{
	UBYTE	work[21];			/*ï∂éöóÒÉèÅ[ÉN*/
	UWORD	time;

	if ( CHK_TCR_TimePrint() == 0 ) {	/** MemorySw:I-3-6Ç™0ÇÃéûÇÕí êMéûä‘ÇÕàÛéöÇµÇ»Ç¢ */
		if ( Line >= 14 ) {
			Line += 2;
		}
	}

	Prn_Att_Str_Clear( AscString, AttString );		/*àÛç¸ÅAèCè¸ï∂éöóÒ∏ÿ±∞*/
	switch ( Line ) {
		case	1:
		case	3:
		case	4:
		case	6:
		case	21:
		case	22:
		case	23:
		case	24:
			/*ÇPçsàÛéöÅiâ¸çsÅj*/
			break;
		case	2:
			/*î≠êMå≥ñºÅ{î≠êMå≥î‘çÜ*/
			/* å©ï˚ÇïÅí ÇÃí êMå¥çeÇ‚ÅAëóêMèÿÇ»Ç«Ç∆ÅAìØÇ∂Ç…ÇµÇ‹Ç∑ÅB1997/12/25 Y.Matsukuma */
			if (stack_number == 0) {
/* ÇoÇnÇoÇkÇ`ÇqÅQÇg ïWèÄÇQâÒê¸é˚óeëŒâûÇÃà◊ By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
				CMN_StringCopy( &AscString[1-1], &SYB_TTI_Buffer[SYS_InternalLineNumber][0] );	/* Nov.28.1994  Takeuchi */
				if ( SYB_ID_Buffer[SYS_InternalLineNumber][0] != NULL ) {
					AttributeSet( &AscString[24-1], &AttString[24-1], PWRD_FaxD, LST_NOT );
					CMN_StringCopy( &AscString[28-1], &SYB_ID_Buffer[SYS_InternalLineNumber][0] );
				}
#else
				CMN_StringCopy( &AscString[1-1], SYB_TTI_Buffer );	/* Nov.28.1994  Takeuchi */
				if ( SYB_ID_Buffer[0] != NULL ) {
					AttributeSet( &AscString[24-1], &AttString[24-1], PWRD_FaxD, LST_NOT );
					CMN_StringCopy( &AscString[28-1], SYB_ID_Buffer );
				}
#endif

			}
			else {
				CMN_StringCopy( &AscString[1-1], &SYB_Option_TTI_Buffer[stack_number][0] );	/* Nov.28.1994  Takeuchi */
				if ( SYB_Option_ID_Buffer[stack_number][0] != NULL ) {
					AttributeSet( &AscString[24-1], &AttString[24-1], PWRD_FaxD, LST_NOT );
					CMN_StringCopy( &AscString[28-1], &SYB_Option_ID_Buffer[stack_number][0] );
				}
			}
			break;
		case	5:
			/*ÅñÅñÅ@ÉWÉÖÉäÉáÉEÉVÉáÉEÅ@ÅñÅñ*/
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		AttributeSet( &AscString[15-1], &AttString[15-1], PWRD_RecConfReport_K, LST_NOT );
#else
	AttributeSet( &AscString[15-1], &AttString[15-1], PWRD_RecConfReport, LST_XXX_TWI_XXX );
#endif
			break;
		case	7:
			/*åªç›éûä‘*/
			TimeDataAscii( OFF, SYB_CurrentTime, work, stack_number );
			CMN_StringCopy( &AscString[47-1], work );
			break;
		case	8:
			/*ÜÆÜ¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü≤*/
			Print_Conf_List_Line( 0, AscString, AttString );
			break;
		case	9:
			/*Ü§ î≠êMå≥ñº ---> î≠êMêÊñºÜ§*/
			if (stack_number == 0) {
				Print_Conf_List_Line( 1, AscString, AttString );
				if ( NonStandardID[0] != NULL ) {/** åêMëäéËã@ÇÃë∫ìcÅiÅ^ÇnÇdÇlÅjÇhÇcÇ…âΩÇ©ìoò^Ç≥ÇÍÇƒÇ¢ÇÈ(ëäéËêÊñº) */
					CMN_StringCopy( &AscString[16-1], NonStandardID );
				}
				else {
					CMN_StringCopy( &AscString[16-1], StandardID );/** åêMëäéËã@ÇÃïWèÄÇhÇc(ëäéËêÊÇeÇ`Çwî‘çÜ) */
				}
				AttributeSet( &AscString[38-1], &AttString[38-1], PWRD_FromTo, LST_NOT );/* ---> */

/* ÇoÇnÇoÇkÇ`ÇqÅQÇg ïWèÄÇQâÒê¸é˚óeëŒâûÇÃà◊ By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
				if ( SYB_TTI_Buffer[SYS_InternalLineNumber][0] != NULL ) {
					CMN_StringCopy( &AscString[44-1], &SYB_TTI_Buffer[SYS_InternalLineNumber][0] );
				}
				else {
					CMN_StringCopy( &AscString[44-1], &SYB_ID_Buffer[SYS_InternalLineNumber][0] );
				}
#else
				if ( SYB_TTI_Buffer[0] != NULL ) {
					CMN_StringCopy( &AscString[44-1], SYB_TTI_Buffer );
				}
				else {
					CMN_StringCopy( &AscString[44-1], SYB_ID_Buffer );
				}
#endif

			}
			else {
				Print_Conf_List_Line( 1, AscString, AttString );
				if ( SYS_Opt[stack_number].NonStandardID[0] != NULL ) {/** åêMëäéËã@ÇÃë∫ìcÅiÅ^ÇnÇdÇlÅjÇhÇcÇ…âΩÇ©ìoò^Ç≥ÇÍÇƒÇ¢ÇÈ(ëäéËêÊñº) */
					CMN_StringCopy( &AscString[16-1], SYS_Opt[stack_number].NonStandardID );
				}
				else {
					CMN_StringCopy( &AscString[16-1], SYS_Opt[stack_number].StandardID );/** åêMëäéËã@ÇÃïWèÄÇhÇc(ëäéËêÊÇeÇ`Çwî‘çÜ) */
				}
				AttributeSet( &AscString[38-1], &AttString[38-1], PWRD_FromTo, LST_NOT );/* ---> */
				if (SYB_Option_TTI_Buffer[stack_number][0] != NULL ) {
					CMN_StringCopy( &AscString[44-1], &SYB_Option_TTI_Buffer[stack_number][0] );
				}
				else {
					CMN_StringCopy( &AscString[44-1], &SYB_Option_ID_Buffer[stack_number][0] );
				}
			}
			break;
		case	10:
			/*ÜæÜ¢Ü¢Ü¢Ü¢Ü¢Ü¢ÜŒÜ¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü∆*/
			Print_Conf_List_Line( 2, AscString, AttString );
			break;
		case	11:
			/*Ü§ ¬≥º› ﬁ›∫ﬁ≥Å@Ü§999		   Ü§*/
			if (stack_number == 0) {
				Print_Conf_List_Line( 3, AscString, AttString );
				AttributeSet( &AscString[16-1], &AttString[16-1], PWRD_CommNo, LST_NOT );
				CMN_UnsignedIntToASC( &AscString[36-1], JournalRxTotalCount,3,'0');	/*94/10/06 By j.masuda*/
			}
			else {
				Print_Conf_List_Line( 3, AscString, AttString );
				AttributeSet( &AscString[16-1], &AttString[16-1], PWRD_CommNo, LST_NOT );
				CMN_UnsignedIntToASC( (UBYTE *)&AscString[36-1], SYS_Opt[stack_number].JournalRxTotalCount,3,'0');	/*94/10/06 By j.masuda*/
			}
			break;
		case	12:
		case	14:
		case	16:
		case	18:
			/*ÜæÜ¢Ü¢Ü¢Ü¢Ü¢Ü¢ÜﬁÜ¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü∆*/
			Print_Conf_List_Line( 4, AscString, AttString );
			break;
		case	13:
			/*Ü§ ¬≥º›”∞ƒﬁÅ@Ü§XXXXXXXX	  Ü§*/
			if (stack_number == 0) {
				Print_Conf_List_Line( 3, AscString, AttString );
				AttributeSet( &AscString[16-1], &AttString[16-1], PWRD_CommMode, LST_NOT );
				CommunicationModeName( RxMode, &AscString[36-1], &AttString[36-1]);
			}
			else {
				Print_Conf_List_Line( 3, AscString, AttString );
				AttributeSet( &AscString[16-1], &AttString[16-1], PWRD_CommMode, LST_NOT );
				CommunicationModeName( SYS_Opt[stack_number].RxMode, &AscString[36-1], &AttString[36-1]);
			}
			break;
		case	15:
			/*Ü§ ¬≥º›ºﬁ∂›Å@Ü§Z9'99"    Ü§*/
			if (stack_number == 0) {
				Print_Conf_List_Line( 3, AscString, AttString );
				AttributeSet( &AscString[16-1], &AttString[16-1], PWRD_CommStartTime, LST_NOT );
				SecondToMinuteSecondAsc( FaxComPeriod, work, 0 );
				CMN_StringCopy( &AscString[36-1], work );
			}
			else {
				time = (UWORD)(SYS_OptionModemTime[stack_number].EndTime - SYS_OptionModemTime[stack_number].StartTime);				Print_Conf_List_Line( 3, AscString, AttString );
				AttributeSet( &AscString[16-1], &AttString[16-1], PWRD_CommStartTime, LST_NOT );
				SecondToMinuteSecondAsc( time, work, 0 );
				CMN_StringCopy( &AscString[36-1], work );
			}
			break;
		case	17:
			/*Ü§ ¬≥º›œ≤Ω≥Å@Ü§zz9Õﬂ∞ºﬁ	 Ü§*/
			if (stack_number == 0) {
				Print_Conf_List_Line( 3, AscString, AttString );
				AttributeSet( &AscString[16-1], &AttString[16-1], PWRD_CommPages, LST_NOT );
				CMN_UnsignedIntToASC_NULL( work, (UWORD)SYS_RxTotalPage, 0, 0 );
				CMN_StringCopy( &AscString[36-1], work );
				AttributeSet( &AscString[36-1+CMN_StringLength(work)+1],
				  &AttString[36-1+CMN_StringLength(work)+1], PWRD_Pages, LST_NOT );
			}
			else {
				Print_Conf_List_Line( 3, AscString, AttString );
				AttributeSet( &AscString[16-1], &AttString[16-1], PWRD_CommPages, LST_NOT );
				CMN_UnsignedIntToASC_NULL( work, (UWORD)SYS_Opt[stack_number].SYS_RxTotalPage, 0, 0 );
				CMN_StringCopy( &AscString[36-1], work );
				AttributeSet( &AscString[36-1+CMN_StringLength(work)+1],
				  &AttString[36-1+CMN_StringLength(work)+1], PWRD_Pages, LST_NOT );
			}
			break;
		case	19:
			/*Ü§ ¬≥º›πØ∂Å@Ü§XXXXXXXX	 Ü§*/
			Print_Conf_List_Line( 3, AscString, AttString );
			AttributeSet( &AscString[16-1], &AttString[16-1], PWRD_CommResult, LST_NOT );
			AttributeSet( &AscString[36-1], &AttString[36-1], PWRD_Ok, LST_NOT );
			break;
		case	20:
			/*Ü∂Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü÷Ü¢Ü¢Ü¢Ü¢Ü¢Ü¢Ü∫*/
			Print_Conf_List_Line( 5, AscString, AttString );
			break;
	}
}

