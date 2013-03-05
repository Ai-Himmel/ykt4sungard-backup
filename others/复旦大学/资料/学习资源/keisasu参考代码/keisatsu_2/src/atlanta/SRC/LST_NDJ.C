/*************************************************************************
*	System		: SAKAKI
*	File Name	: LST_NDJ.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1998/09/18
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC’…M—š—ð
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\syswarp.h"
#include	"\src\atlanta\define\sysnd.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\uni_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"

#include	"\src\atlanta\define\ncu_ret.h"

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* 1998/09/18 By M.Kuwahara */
/*************************************************************************
	module		:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC’…M—š—ð‚Ìˆóü]
	function	:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC’…M—š—ð‚ðˆóü‚·‚é]
	common		:[
		List		:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/09/18]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD				Print_INF_ND_List(
						 void )				/*‚È‚µ*/
{
	UBYTE	count;					/*—š—ðŒ”*/
	UBYTE 	page;					/*Íß°¼Þ*/
	UBYTE	point;					/*o—Íƒ|ƒCƒ“ƒg*/
	UBYTE 	line_cnt;				/*Žc‚èˆóü‰Â”\s”*/
	register WORD	ret;			/*ŽÀsŒ‹‰Ê*/

	count	= 0;
	page 	= 1;
/*	if (SYB_NumberDisplayJournal[point].Status == SYS_ND_EMPTY) {	/* –¢Žg—p */	/* 1998/10/16 By M.Kuwahara */
#if 0 /* Changed by H.Kubo 1998/10/17 */
@@	if (SYB_NumberDisplayJournal[SYB_NumberDisplayJournalPoint].Status == SYS_ND_EMPTY) {	/* –¢Žg—p */
@@		point = 0;
@@	}
@@	else {
@@		point	= SYB_NumberDisplayJournalPoint;
@@	}
#else
	/* ˆê”ÔŒÃ‚¢—š—ð‚ð’Tõ */
	point = SYB_NumberDisplayJournalPoint;
	for (count = 0; count < SYS_ND_JRNL_MAX; count++) {
		if (SYB_NumberDisplayJournal[point].Status & SYS_ND_SET) {	/* Žg—p */
			break;
		}
		point++;
		if (point == SYS_ND_JRNL_MAX) {
			point = 0;
		}
	}
#endif
	count	= 0;
	while (count < SYS_ND_JRNL_MAX) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}

		line_cnt = (UBYTE)(PaperSizeLen() - 11);/*ˆóü‰Â”\s”¾¯Ä*/

		if ( (ret = Print_INF_ND_Head( 0, page ) ) != OK ) {/*Í¯ÀÞˆóü*/
			return ( ret );
		}

		for (;;) {
			if (count >= SYS_ND_JRNL_MAX) {	/* ‘SŒo—Í‚µ‚½Žž */
				break;
			}

			if (SYB_NumberDisplayJournal[point].Status == SYS_ND_EMPTY) {	/* –¢Žg—p */
				count	= SYS_ND_JRNL_MAX;
				break;
			}

			/*ˆóü—\’ès”‚ªˆóü‰Â”\‚©”»’f*/
			if( line_cnt <= 2 ){		/* ‰üƒy[ƒW */
				break;
			}

			if ( (ret = Print_INF_ND_Specifi( count, point )) != OK ) {
				return (ret);
			}
			line_cnt -= 2;
			count++;
			point++;
			if (point >= SYS_ND_JRNL_MAX) {	/* ÊÞ¯Ì§‚ÌÅŒã‚Ü‚ÅŒŸõ‚³‚ê‚½Žž */
				point	= 0;
			}
		}
		if ( (ret = Print_INF_ND_Head( 1, page) ) != OK ) {	/*Ì¯Àˆóü*/
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
	module		:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC’ÊM—š—ðƒwƒbƒ_ˆóü]
	functiom	:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC’ÊM—š—ð‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
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
	date		:[98/09/18]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD			Print_INF_ND_Head(
						 UBYTE Category,	/*ƒwƒbƒ_Ží—Þ*/
						 UBYTE Page )		/*ƒy[ƒW*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Category == 0 ) {

		/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs{Œ©o‚µ{‚P‰üs*/
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		if ( (ret = Print_Head1_Common( PWRD_NumberDisplayJournal_K, 
										LST_NOT, 14-1 )) != OK ) {
			return ( ret );
		}
#else
		if ( (ret = Print_Head1_Common( PWRD_NumberDisplayJournal,
										LST_XXX_TWI_XXX, 22-1 )) != OK ) {
			return ( ret );
		}
#endif
#if (0)
		/*Page Œ»ÝŽžŠÔ*/
		if ( (ret = PageTimePrint( Page, 8-1, 53-1 )) != OK ) {
			return ( ret );
		}
#endif
		/* ƒy[ƒW”Ô†ˆóŽš */
		if ( (ret = PagePrint( Page, 4-1 )) != OK ) {
			return ( ret );
		}

		/* No. ”­MŽÒ”Ô†      ‘ŠŽèæ–¼        ’…M“úŽž    ”õl*/
		Print_INF_ND_Line( 1, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	else {
		/*†¶†¢†¢†Ö†¢†¢†¢†¢†º*/
		Print_INF_ND_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED+1 )) != OK ) {
			return ( ret );
		}
	}
	return( OK );
}


/*************************************************************************
	module		:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC’ÊM—š—ð‚Ì‚P–¾×ˆóü]
	functiom	:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC’ÊM—š—ð‚Ì‚P–¾×‚ðˆóü‚·‚éB]
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
	date		:[98/09/18]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD			Print_INF_ND_Specifi(
					 UBYTE Count,		/*ƒf[ƒ^”*/
					 UBYTE Point)		/*ƒf[ƒ^ˆÊ’u*/
{
	UBYTE	i;
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/


	/*†¶†¢†¢†Ö†¢†¢†¢†¢†º*/
	Print_INF_ND_Line( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	/* ‚m‚D*/
	CMN_UnsignedIntToASC( &List.S.Print[4-1], (UWORD)(Count + 1), 2, '0' );

	/* ”­MŽÒ”Ô† */
	
#if (0)	/* 1998/10/26 By M.Kuwahara */
	/* CMN_StringCopyNULL( List.S.Work, SYB_NumberDisplayJournal[Point].Dial ); */ /* Changed by H.Kubo 1998/10/26 */
	CMN_StringCopyNumOrNULL( List.S.Work, SYB_NumberDisplayJournal[Point].Dial,
							 (SYS_DIRECT_DIAL_MAX  > LST_COLUM) ? LST_COLUM :SYS_DIRECT_DIAL_MAX );
	if ((List.S.Work[0] == NULL) &&		/* ”ñ’Ê’m‚ÌŽž */
#endif
	if ((SYB_NumberDisplayJournal[Point].Dial[0] == NULL) &&		/* ”ñ’Ê’m‚ÌŽž */
		(SYB_NumberDisplayJournal[Point].Reason != SYS_ND_NONE)) {
		/** ”­MŽÒ”Ô†‚É”ñ’Ê’m——R‚ðo—Í */
		switch (SYB_NumberDisplayJournal[Point].Reason) {
		case	SYS_ND_REJECTION:	/* ƒ†[ƒU‹‘”Û w”ñ’Ê’mx•\Ž¦ */
			CMN_StringCopy( &List.S.Print[8-1], PWRD_NoNotice );
			break;
		case	SYS_ND_NONE_AREA:	/* ƒT[ƒrƒX•s‰Â w•\Ž¦Œ—ŠOx•\Ž¦ */
			CMN_StringCopy( &List.S.Print[8-1], PWRD_OutOfDisp );
			break;
		case	SYS_ND_PUBLIC_TEL:	/* ŒöO“d˜b wŒöO“d˜bx•\Ž¦ */
			CMN_StringCopy( &List.S.Print[8-1], PWRD_PublicTel );
			break;
		case	SYS_ND_COLLISION:	/* ƒT[ƒrƒX‹£‡ w•\Ž¦Œ—“àx•\Ž¦ */
			CMN_StringCopy( &List.S.Print[8-1], PWRD_OutOfDisp );
			break;
		case	SYS_ND_F_NET:		/* F –Ô‚©‚ç‚Ì–³–Â“®’…M */
			CMN_StringCopy( &List.S.Print[8-1], PWRD_FNetCall );
			break;
		default:
			break;
		}
	}
	else {
		/* ”­MŒ³”Ô† */
/*		CMN_StringCopyNumNotNULL( &List.S.Print[8-1], &List.S.Work[0], SYS_DIRECT_DIAL_MAX );*/
		CMN_StringCopyNumNotNULL( &List.S.Print[8-1], SYB_NumberDisplayJournal[Point].Dial, SYS_DIRECT_DIAL_MAX );
		/* ‘ŠŽèæ–¼ */
		CMN_StringCopyNumNotNULL( &List.S.Print[30-1], SYB_NumberDisplayJournal[Point].Name, SYS_DIAL_NAME_MAX );
	}

	/* ’…M“úŽž */
	CriterionMinuteToDayTimeAsc( SYB_NumberDisplayJournal[Point].CalledTime/60, LST_MMDDHHMM, List.S.Work );
	CMN_StringCopy( &List.S.Print[56-1], List.S.Work );

	/* ”õl */
	if (SYB_NumberDisplayJournal[Point].Note & SYS_ND_FAX) {	/* FAXŽóM */
		CMN_StringCopy( &List.S.Print[72-1], PWRD_Fax );
	}
	/** ‚±‚±‚Éƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒCŽóMó‹µ‚ð¾¯Ä‚·‚é‚æ‚¤‚É‚µ‚Ü‚· 1998/10/23 */
	if (CHK_UNI_ND_JournalErrorReport()) {
		switch (SYB_NumberDisplayJournal[Point].InformationRxError) {
		case	ND_V23_DATA_RECEIVED:
			List.S.Print[79-1]	= 'o';
			break;
		case	ND_V23_TONE_NOT_DETECTED:
			List.S.Print[79-1]	= '-';
			break;
		case	ND_V23_TONE_WITH_NO_DATA:
			List.S.Print[79-1]	= '?';
			break;
		case	ND_V23_ABORT:
			List.S.Print[79-1]	= '!';
			break;
		case	ND_V23_RECEIVE_ERROR:
			List.S.Print[79-1]	= '*';
			break;
		case	ND_V23_ILLEGAL_FORMAT:
			List.S.Print[79-1]	= '#';
			break;
		default:
			List.S.Print[79-1]	= '.';
			break;
		}
	}

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	return( OK );
}


/*************************************************************************
	module		:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC’ÊM—š—ð‚Ì‰¡‹æØ‚èŒrüì¬]
	function	:[ƒiƒ“ƒo[ƒfƒBƒXƒvƒŒƒC’ÊM—š—ð‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB
	common		:[]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/09/19]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
void	Print_INF_ND_Line(
			UBYTE	Category,
			register UBYTE *AscString,
			register UBYTE *AttString )
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
	case 0:
		/*†®†¢†Î†¢†¢†¢†¢†¢†²*/
		CMN_MemorySet( &AscString[4-1], 75, LST_KLINE_ );
		break;
	case 1:
		/* No.   ”­MŽÒ”Ô†      ‘ŠŽèæ–¼  ’…M“úŽž  ”õl */
		AttributeSet( &AscString[4-1], &AttString[4-1], PWRD_No, LST_NOT );
		AttributeSet( &AscString[14-1], &AttString[14-1], PWRD_SubscriberNumber, LST_NOT );
		AttributeSet( &AscString[37-1], &AttString[37-1], PWRD_Location, LST_NOT );
		AttributeSet( &AscString[60-1], &AttString[60-1], PWRD_Time, LST_NOT );
		AttributeSet( &AscString[71-1], &AttString[71-1], PWRD_Note, LST_NOT );
		break;
	}
}
#endif
