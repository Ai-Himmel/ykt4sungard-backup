/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_PRM.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ‹@ŠíÝ’èƒŠƒXƒg
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysdoc.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\mlt_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\uni_pro.h"

#include	"\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
/*#include	"\src\memsw\define\mem_sw_b.h"*/ /*1996/04/17 Eguchi*/
/*#include	"\src\memsw\define\mem_sw_i.h"*/ /*1996/04/17 Eguchi*/

/*#include	"\src\atlanta\sim_lst\define\lst_pro.h"*/

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_tbl.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_v\rom_tbl.h"			/* By H.Y 1994/11/25 */
#include	"\src\atlanta\ext_v\sys_data.h"	/** For Momiji By O.K Sep,25,1995 **/

#if ( PRO_PANEL == ANK )
#include "\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#include "\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#endif
#if ( PRO_PANEL == KANJI )
#include "\src\atlanta\opr\kanji\ext_v\wording.h"
#include "\src\atlanta\opr\kanji\ext_v\opr_tbl.h"
#endif

#if ( PRO_MAKER == FX )	/* FX‚Í×²ÌÓÆÀ°ÃÞ°À‚ð‹LÚ‚·‚é 94.11.4 Toyoda */
#include	"\src\atlanta\define\syslifem.h"
#endif

#if (PRO_PC_PRINT == ENABLE)
#include  "\src\atlanta\ext_v\dpr_tbl.h"		/* 1996/09/25 by K.Watanabe */
#include  "\src\atlanta\ext_v\dpr_data.h"		/* 1996/10/08 by K.Watanabe */
#endif

#if defined(KEISATSU)	/* ŒxŽ@FAX Added by SMuratec ‰Ä 2005/07/21 */
#include  "\src\atlanta\HINOKI\DEFINE\M_PARAM.H"
#include	"\src\memsw\define\mem_sw_g.h"
#endif

#if defined (KEISATSU)		/* ŒxŽ@FAX Added by SMuratec K.W.Q 2005/06/14 */
#include	"\src\memsw\define\mem_sw_a.h"
#endif		/* End of (defined (KEISATSU)) */

UBYTE DPR_CheckOptionPrintBoardExist(void);		/* 1997/12/19 */

/* ƒXƒ^ƒbƒN‚ª‚ ‚Ó‚ê‚½‚Ì‚Åƒ[ƒJƒ‹‚©‚çstatic‚Ö•ÏX T.Nose 1998/02/13 */
#if (PRO_PC_PRINT == ENABLE)	/* 1996/09/25 by K.Watanabe */
static UBYTE	*support_paper_size[SYS_LAST_PAPER_SIZE + 1] = {0};	/* »Îß°Ä‹L˜^Ž†»²½Þ Ü°ÃÞ¨Ý¸ÞÎß²ÝÀ°Ši”[ */
#endif

/*************************************************************************
	module		:[‹@ŠíÝ’èƒŠƒXƒgn
	function	:[‹@ŠíÝ’èƒŠƒXƒg‚ðˆóü‚·‚é]
	common		:[
		List					:
		SYB_TTI_Buffer			:
		SYS_SYB_ID_Buffer		:
		SYB_CurrentTime			:
		SYB_JournalAutoStatus	:
		SettingsFunctionCountryTableSw	:
		SYB_SettingStatus		:
		SYB_Dialin				:
		SYB_PasscodeNumber		:
		SYB_MachineParameter	:
		SYS_MultiCopyNonSortFlag:
	]
	condition	:[]
	commment	:[
		1.Š‘B4“Ç‚ÝŽæ‚èƒ‚ƒfƒ‹Žd—l’Ç‰Á 1995/07/27 T.Nose

		2.ƒpƒ‰ƒ[ƒ^ŠÔ‚ÌŒrü–³‚­‚µA”ƒ‰ƒCƒ“‚ÌsŠÔŠu‚ðÝ‚¯‚éBBy H.Hirao Feb 29,1996

		3.‹@ŠíÝ’èƒŠƒXƒgƒpƒ‰ƒ[ƒ^’Ç‰ÁI’Ç‰ÁI  For ANZU
												By H.Hirao	Feb 29,1996
			¥ƒTƒCƒŒƒ“ƒgƒIƒyƒŒ[ƒVƒ‡ƒ“
			¥ƒ\[ƒeƒBƒ“ƒOƒRƒs[
			¥ƒRƒs[k¬—¦
			¥‹L˜^ƒy[ƒp[ƒTƒCƒY
			¥ŽóMŒ´eƒvƒŠƒ“ƒgƒvƒƒeƒNƒg
			¥•”–åŠÇ—ƒvƒƒeƒNƒg
			¥•”–åŠÇ—ƒZƒbƒg
			¥‚o‚h‚mƒAƒNƒZƒX
			¥‰ÄŽžŠÔŽ©“®Ø‚è‘Ö‚¦
			¥ƒIƒyƒŒ[ƒVƒ‡ƒ“ƒvƒƒeƒNƒg
			¥ƒvƒŠƒ“ƒ^[Ø‚è‘Ö‚¦
			¥ƒŠƒ“ƒOƒ}ƒXƒ^[

		4.ƒpƒ‰ƒ[ƒ^‚ð’Ç‰Á‚·‚éŽž‚ÍAƒŠƒXƒg‚ª‚P–‡‚ð‰z‚¦‚È‚¢‚æ‚¤‚É’ˆÓIBy H.Hirao Feb 29,1996
			<LETTER»²½ÞŽž>
				¥LST_PRM_SPACE = 4 ‚ÌŽž (Å‘åƒpƒ‰ƒ[ƒ^”) = 45
				¥LST_PRM_SPACE = 6 ‚ÌŽž (Å‘åƒpƒ‰ƒ[ƒ^”) = 41
			4.1 ‰üƒy[ƒW‚ðs‚¤‚æ‚¤‚É•ÏX‚µ‚½ˆ×AãˆÊŠÖ”ì¬	By M.Kuwahara 97/05/06
				ˆ—”Ô†
				1. ”­MŒ³–¼
				2. e“WŽóM‹L‰¯ŠúŠÔ
				3. ’ÊMŠÇ—‹L˜^Ž©“®
				4. ’ÊMØ
				5. ’ÊM‰ñü
				6. ŽóMƒ‚[ƒhØ‚è‘Ö‚¦
				7. “Ç‚ÝŽæ‚èƒTƒCƒY
				8. —Dæ•¶ŽšƒTƒCƒYƒZƒbƒg
				9. —DæŒ´e”Z“x
				10. ƒvƒŠƒ“ƒgk¬—¦
					‰ñ“]‚µ‚«‚¢’l				97/09/02 Add By M.Kuwahara
				11. ƒy[ƒW‡¬
					ƒRƒs[‹ÖŽ~					97/08/26 Add By M.Kuwahara
				12. ƒ|[ƒYŽžŠÔ
				13. ŒÄo‚µƒxƒ‹‰ñ”
				14. ƒŠƒ_ƒCƒ„ƒ‹‰ñ”^ŠÔŠu
				15. ‚d‚b‚lƒ‚[ƒh
				16. ƒpƒXƒR[ƒhƒZƒbƒg
				17. •Âˆæ’ÊM
				18. ƒpƒXƒ[ƒh‘—M
				19. ƒ_ƒCƒŒƒNƒgƒ[ƒ‹–hŽ~
				20. ƒŠƒ‚[ƒgf’fƒZƒbƒg
				21. ƒƒ‚ƒŠ‘—MƒZƒbƒg
				22. ÏƒXƒ^ƒ“ƒv
				23. ‚q‚r‚Q‚R‚Q‚b ƒ{[ƒŒ[ƒg  ƒpƒŠƒeƒB^ƒXƒgƒbƒv^ƒf[ƒ^
				24. ƒ_ƒCƒ„ƒ‹ƒCƒ“ ƒtƒ@ƒNƒX^“d˜b
				25. ƒIƒyƒŒ[ƒVƒ‡ƒ“ƒvƒƒeƒNƒg
				26. ƒƒbƒZ[ƒW‘—M
				27. ƒTƒCƒŒƒ“ƒgƒIƒyƒŒ[ƒVƒ‡ƒ“
				28. ƒRƒs[k¬—¦
				29. ‹L˜^Ž†ƒy[ƒp[ƒTƒCƒY
				30. •”–åŠÇ—ƒZƒbƒg
				31. •”–åŠÇ—ƒvƒƒeƒNƒg
				32. ƒZƒLƒ…ƒŠƒeƒBŽóM
				33. ‚o‚h‚mƒAƒNƒZƒX
				34. ‰ÄŽžŠÔŽ©“®Ø‚è‘Ö‚¦
				35. ƒŠƒ“ƒOƒ}ƒXƒ^ƒZƒbƒg
				36. ƒ}[ƒLƒ…ƒŠ[ƒ|[ƒY
				37. ŽóMŠ®—¹ƒAƒ‰[ƒ€
				38. “Ç‚ÝŽæ‚è–‡”
					•Û—¯ƒƒƒfƒB[ƒZƒbƒg		97/11/07 Add T.Fukumoto
					¿°Ã¨Ý¸ÞºËß°					97/11/13 Add T.Fukumoto
					ƒŠƒ‚[ƒgŽóM				98/03/13 Add T.Fukumoto
					ƒIƒ“ƒtƒbƒNŽóM				98/03/13 Add T.Fukumoto
		5.TTI‚Ì•t‰Á‚É‚æ‚èÅ‘åƒpƒ‰ƒ[ƒ^”‚Ì•ÏX
			<LETTER»²½ÞŽž>
				¥LST_PRM_SPACE = 4 ‚ÌŽž (Å‘åƒpƒ‰ƒ[ƒ^”) = 43
				¥LST_PRM_SPACE = 6 ‚ÌŽž (Å‘åƒpƒ‰ƒ[ƒ^”) = 39
	]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/05/20]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Print_Parameter_List(
						 void )				/*‚È‚µ*/
{
	UBYTE	set_no;		/* ˆ—”Ô† */
	UWORD	line_dot;	/* ƒhƒbƒg” */
	WORD	ret;
	UBYTE	w;						/*Ü°¸*/
	UBYTE	mode;					/*—Dæ•¶Žš»²½ÞŽž‚ÉŽg—p*/
	UBYTE	rxmode;					/*	ŽóMÓ°ÄÞØ‚è‘Ö‚¦Žž‚ÉŽg—p By H.Hirao 1996/05/22	*/
	UBYTE	*w_pt[8] = {0};			/*‘I‘ð€–Ú•¶Žš—ñ*/
	UBYTE	middle_char[3];			/* —DæŒ´e”Z“x‚Ì•¶Žš—ñ('--') 97/03/10 M.Kuwahara */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	UBYTE	prm_kind;				/* Ø½Ä‚ÌŽí—ÞŠi”[—p 1997/12/26 Y.Matsukuma */
#endif
#if (PRO_PC_PRINT == ENABLE)	/* 1996/09/25 by K.Watanabe */
	UBYTE	i;						/* Ù°Ìß•Ï” */
	UBYTE	w_loop;					/* Ù°Ìß•Ï” */
	UBYTE	loop_end;				/* Ù°ÌßI—¹•Ï” */
	UBYTE	max_line;				/* Å‘å•K—vs” */
	UBYTE	line_number;			/* 1sˆóüŒÂ” */
	UBYTE	w_paper_number;			/* Ü°¸•Ï” */
	UBYTE	support_paper_cnt;		/* »Îß°Ä‹L˜^Ž†»²½ÞŒÂ” */
	UBYTE	setting_paper_size;		/* µÍßÚ°¼®ÝÝ’è‹L˜^Ž†»²½Þ */
/*	UBYTE	*support_paper_size[SYS_LAST_PAPER_SIZE + 1] = {0};	@* »Îß°Ä‹L˜^Ž†»²½Þ Ü°ÃÞ¨Ý¸ÞÎß²ÝÀ°Ši”[ */
#endif
#if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1997/06/26 */
	UBYTE	bord_num;	/* ƒ‚ƒfƒ€” */
	UBYTE	line_chk;
	UBYTE	set_line;
	UBYTE	data;		/* ƒ‰ƒCƒ“•Ï” */
	UBYTE	board;		/* ƒIƒvƒVƒ‡ƒ“ƒ{[ƒh•Ï” */

	bord_num = OPT_CountModems();	/* Change CheckMultiLine() to OPT_CountModems() By O.Kimoto 1997/06/26 */

	/* ‚o‚n‚o‚k‚`‚qQ‚g•W€‚Q‰ñüŽû—e‘Î‰ž By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
	bord_num += 1;
#endif

#endif

	set_no	= 0;
	line_dot = 0;

	if ( (ret = Print_Parameter_Head( 0, &line_dot ) ) != OK ) {	/*Í¯ÀÞˆóü*/
		return ( ret );
	}

#if (PRO_KEYPANEL == PANEL_ANZU_L)
	/* F-101ì¬‚Ì‚½‚ßƒ[ƒJƒ‹•Ï”‚É‘ã“ü‚µ‚Ü‚· 1997/12/26 Y.Matsukuma */
	if (CMN_CheckCategory2()) {
		/* F-101 */
		prm_kind = List_ParameterTable_Category2[set_no];
	}
	else {
		/* F-120,F-100 */
		prm_kind = List_ParameterTable[set_no];
	}
	while( prm_kind != NULL ){
		switch( prm_kind ){
#else
	while( List_ParameterTable[set_no] != NULL ){
		switch( List_ParameterTable[set_no] ){
#endif
		case	LST_PRM_TTI_ID:			/* ”­MŒ³–¼*/
#if (PRO_MULTI_LINE == DISABLE)	/* Add By O.Kimoto 1997/06/26 */
 #if (PRO_PANEL == KANJI) || ( PRO_JIS_CODE == ENABLE ) /* By S.K Oct.4,1995 */
			/* ¶ÅID	   94.10.13 ’Ç‰Á */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_SubscriberKanaID, LST_NOT );
			CMN_StringCopy( &List.S.Print[27-1], SYB_TTI_ID_Buffer );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
 #endif /* 5sA‰º‚ÉˆÚ“® */
#else
 #if (PRO_PANEL == KANJI) || ( PRO_JIS_CODE == ENABLE ) /* By S.K Oct.4,1995 */
			if (bord_num == 1) {	/* ƒzƒXƒg‚µ‚©‰ñü‚ª–³‚¢H */
				Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
				AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1],PWRD_SubscriberKanaID, LST_NOT );
				CMN_StringCopy( &List.S.Print[27-1], SYB_TTI_ID_Buffer );
				if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
					return ( ret );
				}
			}
			else {

#if (0)	/* ‚o‚n‚o‚k‚`‚qQ‚g‚Í‚±‚±‚Å‚Í”­MŒ³–¼‚ÍˆóŽš‚µ‚È‚¢ By O.Kimoto 1997/12/20 */
**   /* ‚o‚n‚o‚k‚`‚qQ‚g•W€‚Q‰ñüŽû—e‘Î‰ž By O.Kimoto 1997/11/01 */
**   #if (PRO_LINENUMBER == TWICE_LINE)
**   				for (w = 0;w < 2; w++) {
** 					Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
** 					AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1],PWRD_SubscriberKanaID, LST_NOT );
** 					CMN_StringCopy( &List.S.Print[27-1], &SYB_TTI_ID_Buffer[w][0] );
** 					if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
** 						return ( ret );
** 					}
** 				}
**   #endif
#endif

#if (0)
** 				if (bord_num > 2) {
** 					for (i = 0; i < SYS_OPTION_BOARD_MAX; i++) {
** 						if ((set_line = OPT_GetMultiLinrNumber(i)) != line_chk) {
** 							line_chk = set_line;	/* ŽŸ‚Éƒ`ƒFƒbƒN‚·‚é‚½‚ß‘Ò”ð */
** 							if (i == 0) {
** 								Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
** 								AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1],PWRD_SubscriberKanaID, LST_NOT );
** 								CMN_StringCopy( &List.S.Print[27-1], SYB_TTI_ID_Buffer );
** 							}
** 							else {
** 								Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
** 								AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1],PWRD_SubscriberKanaID, LST_NOT );
** 								CMN_StringCopy( &List.S.Print[27-1], SYB_Option_TTI_ID_Buffer[i] );
** 							}
** 
** 							List.S.Print[22-1] = '(';
** 							List.S.Print[20] = (UBYTE)('0'+ set_line);
** 							List.S.Print[24-1] = ')';
** 
** 							if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
** 								return ( ret );
** 							}
** 						}
** 					}
** 				}
#endif

			}
 #endif
#endif
			break;
#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
		case	LST_PRM_MULTI_TTI_ID:			/* ƒ}ƒ‹ƒ`”­MŒ³–¼ */
 #if (PRO_MULTI_LINE == DISABLE)
			for (w = 1; w <= SYS_MULTI_MAX; w++) {
				Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
				List.S.Print[22-1]	= '(';
				List.S.Print[23-1]	= '0' + w;
				List.S.Print[24-1]	= ')';
				CMN_StringCopy( &List.S.Print[27-1], SYB_Multi_TTI_ID_Buffer[w-1] );
				if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
					return ( ret );
				}
			}
 #else
			if (bord_num == 1) {	/* ƒzƒXƒg‚µ‚©‰ñü‚ª–³‚¢H */
				for (w = 1; w <= SYS_MULTI_MAX; w++) {
					Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
					List.S.Print[22-1]	= '(';
					List.S.Print[23-1]	= '0' + w;
					List.S.Print[24-1]	= ')';
					CMN_StringCopy( &List.S.Print[27-1], SYB_Multi_TTI_ID_Buffer[w-1] );
					if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
						return ( ret );
					}
				}
			}
			else {
				for (w = 1; w <= SYS_MULTI_MAX; w++) {
					Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
					if (w == 1) {
						AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_SubscriberKanaID, LST_NOT );
					}
					List.S.Print[22-1]	= '(';
					List.S.Print[23-1]	= '0' + w;
					List.S.Print[24-1]	= ')';
					CMN_StringCopy( &List.S.Print[27-1], SYB_Multi_TTI_ID_Buffer[w-1] );
					if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
						return ( ret );
					}
				}
			}
 #endif
			break;
#endif
		case	LST_PRM_SECUREDOCHOLD:		 	/* e“WŽóM‹L‰¯ŠúŠÔ */
			/*†¤ ¼ÝÃÝÒÓØ·¶Ý†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_SecureDocHold, LST_NOT );
			CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)CHK_SecureMailHoldTime(), 2, '0' );
			CMN_StringCopy( &List.S.Print[27-1], List.S.Work );
			CMN_MemorySet( &List.S.Attribute[27-1], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
			AttributeSet( &List.S.Print[30-1], &List.S.Attribute[30-1], PWRD_Days, LST_NOT );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_JOURNALAUTOPRT:			/* ’ÊMŠÇ—‹L˜^Ž©“® */
			/*†¤Â³¼Ý·Û¸¼ÞÄÞ³†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_JournalAutoPrt, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			/* «ˆÈ‰º‚Ss’Ç‰Á@]Œû */
			if (CHK_JournalAutoPrintON() == 0){ /* Ž©“®ƒvƒŠƒ“ƒg‚n‚e‚e */
				w = 1;
			}else{
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_CONFREPORT:	 		/* ’ÊMØ */
			/*†¤Â³¼Ý¼®³¾¯Ä†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_ConfReport, LST_NOT );
#if ( PRO_MAKER == FX )
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = (UBYTE *)&NULL_PT;
			if ( CHK_ConfirmationReportON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
#else

 #if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/*Žó—Ì‘‚Ìíœ*//* Modify by SMuratec K.W.Q 2003/10/30 */
 			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_ConfirmationReportON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
 #else
			w_pt[0] = (UBYTE *)&PWRD_TxConf;
			w_pt[1] = (UBYTE *)&PWRD_RxConf;
			w_pt[2] = NULL_PT;
			if ( CHK_RCR_ON() == 0 ) {
				w = 0;
			}
			else {
				w = 1;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_ConfirmationReportON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[47], &List.S.Attribute[47], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
 #endif
 
#endif
			break;
		case	LST_PRM_PHONETYPE: 			/* ’ÊM‰ñü */
#if (PRO_MULTI_LINE == DISABLE)	 /* ‚Q‰ñü 1996/12/05 Y.Matsukuma */
			/*†¤Â³¼Ý¶²¾Ý†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_PhoneType, LST_NOT );
			w = (UBYTE)CHK_DialType();
 #if defined(JPN)
			w_pt[0] = (UBYTE *)&PWRD_ToneLine;
			w_pt[1] = (UBYTE *)&PWRD_Pps10;
			w_pt[2] = (UBYTE *)&PWRD_Pps20;
			w_pt[3] = NULL_PT;
			switch ( w ) {
			case DIAL_SPEED_10PPS:
				w = 1;
				break;
			case DIAL_SPEED_20PPS:
				w = 2;
				break;
			case LINE_TYPE_TONE:
				w = 0;
				break;
			}
 #else
  #if defined(FRA)	/* add by M.HARADA '97.1/17 */
			w_pt[0] = (UBYTE *)&PWRD_ToneLine;
			w_pt[1] = NULL_PT;
			w = 0;
  #else
   #if defined(EC1) || defined(EUR)	/* for DNK 97/05/06 by M.H. */
	#if defined(EUR)	/* ‰¢BŽd—l’Ç‰Á by M.H 1999/09/15 */
			if(CHK_DP_Enable()) {	/* DP‚Ì—LŒø/–³Œø‚ÅØ‚è•ª‚¯‚é 1999/12/20 by M.Harada */
				w_pt[0] = (UBYTE *)&PWRD_ToneLine;
				w_pt[1] = (UBYTE *)&PWRD_Pps10;
				w_pt[2] = NULL_PT;
				if (w != 0) {
					w = 0;
				}
				else {
					w = 1;
				}
			}else{
				w_pt[0] = (UBYTE *)&PWRD_ToneLine;
				w_pt[1] = NULL_PT;
				w = 0;
			}
	#else
			if(SYS_MachineParameter[0] != 7){
				w_pt[0] = (UBYTE *)&PWRD_ToneLine;
				w_pt[1] = (UBYTE *)&PWRD_Pps10;
				w_pt[2] = NULL_PT;
				if (w != 0) {
					w = 0;
				}
				else {
					w = 1;
				}
			}else{
				w_pt[0] = (UBYTE *)&PWRD_ToneLine;
				w_pt[1] = NULL_PT;
				w = 0;
			}
	#endif
   #else
			w_pt[0] = (UBYTE *)&PWRD_ToneLine;
			w_pt[1] = (UBYTE *)&PWRD_Pps10;
			w_pt[2] = NULL_PT;
			switch ( w ) {
			case LINE_TYPE_TONE:
				w = 0;
				break;
			default:
				w = 1;
				break;
			}
   #endif
  #endif
 #endif
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
#else
			if (bord_num == 1) {	/* ƒzƒXƒg‚µ‚©‰ñü‚ª–³‚¢H */
				/*†¤Â³¼Ý¶²¾Ý†¤XXXXXX†¤*/
				Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
				AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_PhoneType, LST_NOT );
				w = (UBYTE)CHK_DialType();
 #if defined(JPN)
				w_pt[0] = (UBYTE *)&PWRD_ToneLine;
				w_pt[1] = (UBYTE *)&PWRD_Pps10;
				w_pt[2] = (UBYTE *)&PWRD_Pps20;
				w_pt[3] = NULL_PT;
				switch ( w ) {
				case DIAL_SPEED_10PPS:
					w = 1;
					break;
				case DIAL_SPEED_20PPS:
					w = 2;
					break;
				case LINE_TYPE_TONE:
					w = 0;
					break;
				}
 #else
  #if defined(FRA)	/* add by M.HARADA '97.1/17 */
				w_pt[0] = (UBYTE *)&PWRD_ToneLine;
				w_pt[1] = NULL_PT;
				w = 0;
  #else
   #if defined(EC1) || defined(EUR)	/* for DNK 97/05/06 by M.H. */
	#if defined(EUR)	/* ‰¢BŽd—l’Ç‰Á by M.H 1999/09/15 */
				if(CHK_DP_Enable()) {	/* DP‚Ì—LŒø/–³Œø‚ÅØ‚è•ª‚¯‚é 1999/12/20 by M.Harada */
					w_pt[0] = (UBYTE *)&PWRD_ToneLine;
					w_pt[1] = (UBYTE *)&PWRD_Pps10;
					w_pt[2] = NULL_PT;
					if (w != 0) {
						w = 0;
					}
					else {
						w = 1;
					}
				}else{
					w_pt[0] = (UBYTE *)&PWRD_ToneLine;
					w_pt[1] = NULL_PT;
					w = 0;
				}
	#else
				if(SYB_MachineParameter[0] != 4 &&
				   SYB_MachineParameter[0] != 5 &&
				   SYB_MachineParameter[0] != 6 &&
				   SYB_MachineParameter[0] != 7){
					w_pt[0] = (UBYTE *)&PWRD_ToneLine;
					w_pt[1] = (UBYTE *)&PWRD_Pps10;
					w_pt[2] = NULL_PT;
					if (w != 0) {
						w = 0;
					}
					else {
						w = 1;
					}
				}else{
					w_pt[0] = (UBYTE *)&PWRD_ToneLine;
					w_pt[1] = NULL_PT;
					w = 0;
				}
	#endif
   #else
				w_pt[0] = (UBYTE *)&PWRD_ToneLine;
				w_pt[1] = (UBYTE *)&PWRD_Pps10;
				w_pt[2] = NULL_PT;
				switch ( w ) {
				case LINE_TYPE_TONE:
					w = 0;
					break;
				default:
					w = 1;
					break;
				}
   #endif
  #endif
 #endif
				Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
				if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
					return ( ret );
				}
			}
			else {
				/* ‚Q‰ñü‚Ìê‡‚ÍA‹@ŠíÝ’èƒŠƒXƒg‚ª•ÏX‚É‚È‚Á‚Ä‚¢‚Ü‚·
				** ŠÈ’P‚ÉŽ¦‚·‚Æ
				** b-----------------b---
				** b‰ñü”Ô†(X)      b
				** b  ”­iŒ³–¼(¶ÅID) b
				** b  ’ÊM‰ñü       b
				** b  ‘—M¥ŽóM      b
				** b  ŠOü¥“àüÝ’è  b
				** b-----------------b----
				** ‚Ì‚æ‚¤‚É‚È‚éB
				*/
				if ( (ret = Print_MultiParameter(&line_dot) ) != OK) {
					return(ret);
				}
			}
#endif
			break;
#if (0)
** 		case	LST_PRM_TXRXTYPE:
** 		/* For Debug */
** 			if ( (ret = Print_MultiParameter(&line_dot) ) != OK) {
** 				return(ret);
** 			}
** 			break;
#endif

#if defined (KEISATSU)		/* ŒxŽ@FAX Added by SMuratec K.W.Q 2005/10/10 */
		case	LST_PRM_DIALTONE_KEIDEN:
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_DialToneKeiden, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			if (SYS_MemorySwitch[MEMORY_SW_A1] & DIALTONE_OR_TIMEUP_EXT){ /* ƒ_ƒCƒ„ƒ‹ƒg[ƒ“ŒŸo‚µ‚È‚¢F‚n‚e‚e */
				w = 1;
			}else{
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
#endif		/* End of (defined (KEISATSU)) */

/* ƒ_ƒCƒ„ƒ‹ƒg[ƒ“ŒŸo‘Î‰ž Added start by SMuratec ‰Ä 2004/7/14 */
#if defined(STOCKHM2) || defined(HINOKI3)	/* Add by Y.kano 2004/12/08 */
		case	LST_PRM_DIALTONE:
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_DialTone, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			if (CHK_DialToneOrTimeupAvailable()){ /* ƒ_ƒCƒ„ƒ‹ƒg[ƒ“ŒŸo‚µ‚È‚¢F‚n‚e‚e */
				w = 1;
			}else{
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
#endif
/* ƒ_ƒCƒ„ƒ‹ƒg[ƒ“‘Î‰ž Added end by SMuratec ‰Ä 2004/7/14 */

		case	LST_PRM_RECEIVEMODE:			/* ŽóMƒ‚[ƒhØ‚è‘Ö‚¦ */
			/*†¤¼Þ­¼ÝÓ°ÄÞ·Ø¶´†¤XXXXXX†¤*/
#if (PRO_AUTO_RX_SWITCH == ENABLE)
	/*#if !defined(USA)*/	/* 1997/12/02 */
		/* 1997/12/19	F100R
		 * TEL/FAX,ANS/FAXØ‚è‘Ö‚¦‚ÍðŒƒRƒ“ƒpƒCƒ‹‚Å‚Í‚È‚­ ƒƒ“ƒe‚r‚v‚Å“ü‚ê‚Ü‚·
		*/
			if (CMN_CheckTelFaxSuport()) {	/* TEL/FAXAANS/FAXƒTƒ|[ƒg‚·‚é */

				Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
				AttributeSet(&List.S.Print[7-1], &List.S.Attribute[7-1],  PWRD_RecieveMode, LST_NOT );
				rxmode = CHK_AutoRxMode();
				if (rxmode) {
					rxmode --;
				}
				w_pt[0] = PWRD_Fax;
				w_pt[1] = PWRD_FaxTel;
				if ( CTRY_TelFaxPrimary() ) {
					w_pt[2] = PWRD_TelFax;
					if ( CTRY_AnsFaxReady() ) {
						w_pt[3] = PWRD_AnsFax;
						w_pt[4] = NULL_PT;
					}
					else {
						w_pt[3] = NULL_PT;
					}
				}
				else {
					if ( CTRY_AnsFaxReady() ) {
						w_pt[2] = PWRD_AnsFax;
						w_pt[3] = NULL_PT;
					}
					else {
						w_pt[2] = NULL_PT;
					}
					if ((CHK_AutoRxMode() & (AUTO_RX_MODE_ANSFAX >> 5)) == (AUTO_RX_MODE_ANSFAX >> 5)){
						rxmode = 2;
					}
				}
 
 #if (PRO_KEYPANEL == PANEL_SATSUKI2)/* Added by SMuratec K.W.Q 2003/11/28 *//* Del STOCKHM2 by SMuratec C.P 2004/07/23 */
				if (CHK_DialinModeON()) {
					rxmode = 0xFF;
				}
 #endif
				Param_set( &List.S.Print[27], &List.S.Attribute[27], rxmode, 10, w_pt );
				if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
					return ( ret );
				}

 #if (PRO_KEYPANEL == PANEL_SATSUKI2) /* Added by SMuratec K.W.Q 2003/11/28 *//* Del STOCKHM2 by SMuratec C.P 2004/07/23 */
				Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
				
				w_pt[0] = PWRD_DialInRx;
				w_pt[1] = NULL_PT;

				if (CHK_DialinModeON()) {
					rxmode = 0;
				}
				else{
					rxmode = 1;
				}
				Param_set( &List.S.Print[27], &List.S.Attribute[27], rxmode, 10, w_pt );

				if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
					return ( ret );
				}
 #endif
			}

#else
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_RecieveMode, LST_NOT );
			rxmode = CHK_AutoRxMode();
#if (0)
//			w_pt[0] = (UBYTE *)&PWRD_Tel;
//			w_pt[1] = (UBYTE *)&PWRD_Fax;
//			w_pt[2] = (UBYTE *)&PWRD_FaxTel;
//#if defined(USA)
//			w_pt[3]	= NULL_PT;
//#else
#endif
 /* Modified by S.Fukui Sep.16,1997 */
			w_pt[0] = (UBYTE *)&PWRD_Tel;
			w_pt[1] = (UBYTE *)&PWRD_Fax;
 #if defined(USA)
			w_pt[2]	= NULL_PT;
 #else
			w_pt[2] = (UBYTE *)&PWRD_FaxTel;

			if ( CTRY_TelFaxPrimary() ) {
				w_pt[3] = (UBYTE *)&PWRD_TelFax;
				if ( CTRY_AnsFaxReady() ) {
					w_pt[4] = (UBYTE *)&PWRD_AnsFax;
					w_pt[5] = NULL_PT;
				}
				else {
					w_pt[4] = NULL_PT;
				}
			}
			else {
				if ( CTRY_AnsFaxReady() ) {
					w_pt[3] = (UBYTE *)&PWRD_AnsFax;
					w_pt[4] = NULL_PT;
				}
				else {
					w_pt[3] = NULL_PT;
				}
				if ((CHK_AutoRxMode() & (AUTO_RX_MODE_ANSFAX >> 5)) == (AUTO_RX_MODE_ANSFAX >> 5)){
					rxmode = 3;
				}
			}
 #endif
 #if (PRO_DIALIN_SW == DISABLE) /* By H.Fujimura 2002/07/11 */
			if (CHK_DialinModeON()) {
				rxmode = 0xFF;
			}
 #endif
			Param_set( &List.S.Print[27], &List.S.Attribute[27], rxmode, 10, w_pt );
			/* Param_set( &List.S.Print[29], &List.S.Attribute[29], CHK_AutoRxMode(),
			  11, w_pt ); */ /**	For ANZU By H.Hirao 1996/05/22	*/
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
#endif
			break;
		case	LST_PRM_SCANNERWIDTH:		/* “Ç‚ÝŽæ‚èƒTƒCƒY */
#if (PRO_SCAN_WIDTH != A4WIDTH)
			/*†¤“ÇŽæ»²½Þ †¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_ScannerWidth, LST_NOT );

/*#if (PRO_KEYPANEL == PANEL_ANZU)*/ /* ’Ç‰Á ANZU‚ÍA4‚Ì‚Ý 96/01/11 H.HIRAO */
 #if (PRO_PITNEYBOWES == ENABLE) 	/* [‚o‚a—p“ÇŽæ‚èƒTƒCƒY•\Ž¦‘Î‰ž] By S.Fukui Aug.25,1998  */
			w_pt[0] = (UBYTE *)&PWRD_LETTER;	
 #else
			w_pt[0] = (UBYTE *)&PWRD_A4;
 #endif
			w_pt[1] = (UBYTE *)&PWRD_B4;
/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
 #if (PRO_KEYPANEL == PANEL_POPLAR_L ) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* POPLAR_L‚ÍA3–³‚µ 97/10/28 By M.Kuwahara */
			w_pt[2] = NULL_PT;
 #else
  #if (PRO_PITNEYBOWES == ENABLE) 	/* [‚o‚a—p“ÇŽæ‚èƒTƒCƒY•\Ž¦‘Î‰ž] By S.Fukui Aug.25,1998  */
			w_pt[2] = (UBYTE *)&PWRD_LEDGER;	
  #else
			w_pt[2] = (UBYTE *)&PWRD_A3;
  #endif
			w_pt[3] = NULL_PT;
 #endif
/*#endif*/
			w = CHK_ScanningWidth();
			switch ( w ) {
				case SYS_DOCUMENT_A4_SIZE:
					w = 0;
					break;
				case SYS_DOCUMENT_B4_SIZE:
					w = 1;
					break;
				case SYS_DOCUMENT_A3_SIZE:
					w = 2;
					break;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
#endif
			break;
		case	LST_PRM_PRIMARYMODE:		/* —Dæ•¶ŽšƒTƒCƒYƒZƒbƒg */
			/*†¤Õ³¾ÝÓ¼Þ»²½Þ¾¯Ä†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_PrimaryMode, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_Normal;
			w_pt[1] = (UBYTE *)&PWRD_Fine;
			w_pt[2] = (UBYTE *)&PWRD_SFine;
			w_pt[3] = (UBYTE *)&PWRD_Gray;
			w_pt[4] = NULL_PT;
			switch(CHK_PrimaryMode()) {
			case	SYS_NORMAL:
				mode = 0;
				break;
			case	SYS_FINE:
				mode = 1;
				break;
			case	SYS_SFINE:
			case	SYS_HFINE:
			case	SYS_EFINE:		/* 1996/06/17 by N.Sakamoto */
			case	SYS_E_HFINE:	/* 1997/11/27 */
				mode = 2;
				break;
			default:
				mode = 3;
				break;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], mode, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_CONTRAST: 			/* —DæŒ´e”Z“x */
			/*†¤—DæŒ´e”Z“x  †¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_Contrast, LST_NOT );
/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_ANZU_L) ||  (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* ANZU‚ÌŽž‚R’iŠK”Z“x 1997/03/10 M.Kuwahara */
			w_pt[0] = (UBYTE *)&PWRD_Dark;							/* •ÏX‚µ‚Ü‚µ‚½ 1997/06/18 Y.Matsukuma */
			w_pt[1] = (UBYTE *)&PWRD_NormalDark;					/* POPLAR_L‚ÌŽž‚R’iŠK”Z“x 97/10/28 By M.Kuwahara */
			w_pt[2] = (UBYTE *)&PWRD_Light;
			w_pt[3] = NULL_PT;
			w = CHK_PrimaryDensity();
			switch ( w ) {
				case SYS_DARK_DENSITY:
					w = 0;
					break;
				case SYS_NORMAL_DENSITY:
					w = 1;
					break;
				case SYS_LIGHT_DENSITY:
					w = 2;
					break;
			}
#else	/* ƒ|ƒvƒ‰	1997/06/18 Y.Matsukuma */
			middle_char[0] = '-';	/** ‚Q’i‰ñ–Ú‚Æ‚S’i‰ñ–Ú */
			middle_char[1] = '-';
			middle_char[2] = '\0';
			w_pt[0] = (UBYTE *)&PWRD_Dark;
			w_pt[1] = middle_char;
			w_pt[2] = (UBYTE *)&PWRD_NormalDark;
			w_pt[3] = middle_char;
			w_pt[4] = (UBYTE *)&PWRD_Light;
			w_pt[5] = NULL_PT;
			w = SYB_SettingStatus[SETTING_STATUS_26] & (PRIMARY_CONTRAST_DARK		  |
														PRIMARY_CONTRAST_DARK_NORMAL  |
														PRIMARY_CONTRAST_NORMAL		  |
														PRIMARY_CONTRAST_LIGHT_NORMAL |
														PRIMARY_CONTRAST_LIGHT);
			switch( w ){
			case	PRIMARY_CONTRAST_DARK:
				w	= 0;
				break;
			case	PRIMARY_CONTRAST_DARK_NORMAL:
				w	= 1;
				break;
			case	PRIMARY_CONTRAST_NORMAL:
				w	= 2;
				break;
			case	PRIMARY_CONTRAST_LIGHT_NORMAL:
				w	= 3;
				break;
			case	PRIMARY_CONTRAST_LIGHT:
				w	= 4;
				break;
			}
#endif
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w,
			  10, w_pt );

			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_REDUCTIONRATE: 		/* ƒvƒŠƒ“ƒgk¬—¦ */
			/*†¤ÌßØÝÄ¼­¸¼®³ØÂ†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_ReductionRate, LST_NOT );
#if ( PRO_MAKER == FX )
			w_pt[0] = (UBYTE *)&PWRD_Auto;
			w = CHK_FreeReduction();
			if ( w != 0xff ) {	/*Ž©“®‚©”CˆÓ‚©‚ð”»•Ê*/
				CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)w, 3, ' ' );
				w_pt[1] = List.S.Work;
				w_pt[2] = NULL_PT;
				w = 1;
			}
			else {
				w = 0;
				w_pt[1] = NULL_PT;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 11, w_pt );
			if ( w_pt[1] != NULL_PT ) {
				List.S.Print[42-1] = '%';
			}
			AttributeSet( &List.S.Print[49-1], &List.S.Attribute[49-1], PWRD_ThValue00mm, LST_NOT );
			CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)CHK_RxMargin(), 2, '0' );
			CMN_StringCopy( &List.S.Print[57-1], List.S.Work );
			CMN_MemorySet( &List.S.Attribute[57-1], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
#else
			w_pt[0] = (UBYTE *)&PWRD_Auto;
			w_pt[1] = (UBYTE *)&PWRD_P100;
 #if (PRO_FIXED_REDUCTION == ENABLE)	/* ‚k‚S‚O‚O‘Î‰ž‚ÅŒÅ’èk¬—¦–³‚µ‚Ìˆ—‚ð’Ç‰Á by K.Watanabe 1998/05/13 */
			w_pt[2] = (UBYTE *)&PWRD_P97;
			w_pt[3] = (UBYTE *)&PWRD_P91;
			w_pt[4] = (UBYTE *)&PWRD_P81;
			w_pt[5] = (UBYTE *)&PWRD_P75;
			w_pt[6] = NULL_PT;
 #else
			w_pt[2] = NULL_PT;
 #endif
			w = CHK_RxFixedReduction(); /**	ŒÄ‚ñ‚Å‚¢‚éŠÖ”“à‚Å‚Tƒrƒbƒg‰EƒVƒtƒg‚µ‚Ä‚¢‚é‚Ì‚Å By H.Hirao 1996/05/24	*/
			/* w = (UBYTE)(CHK_RxFixedReduction() >> 5); */

 #if (PRO_FIXED_REDUCTION == ENABLE)	/* ‚k‚S‚O‚O‘Î‰ž‚ÅŒÅ’èk¬—¦–³‚µ‚Ìˆ—‚ð’Ç‰Á by K.Watanabe 1998/05/13 */
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 5, w_pt );
			AttributeSet( &List.S.Print[62-1], &List.S.Attribute[62-1], PWRD_ThValue00mm, LST_NOT );
			CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)CHK_RxMargin(), 2, '0' );
			CMN_StringCopy( &List.S.Print[72-1], List.S.Work );
			CMN_MemorySet( &List.S.Attribute[72-1], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
 #else
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			AttributeSet( &List.S.Print[57-1], &List.S.Attribute[57-1], PWRD_ThValue00mm, LST_NOT );
			CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)CHK_RxMargin(), 2, '0' );
			CMN_StringCopy( &List.S.Print[67-1], List.S.Work );
			CMN_MemorySet( &List.S.Attribute[67-1], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
 #endif
#endif
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;

		/* ‰ñ“]ƒ{[ƒh‘Î‰ž By O.Kimoto 1997/07/09 */
		case LST_PRM_ROTATEMARGIN:
#if (PRO_ROTATE == ENABLE)				/* ‚c‚o‚q‚`‚lŒo—R‚Ì‰ñ“]ŽóM */
			/* ¬’J‚³‚ñA‹@ŠíÝ’èƒŠƒXƒg‚ÉÚ‚¹‚é“à—e‚É‚Â‚¢‚ÄAƒR[ƒh‚ð“ü‚ê‚Ä‚­‚¾‚³‚¢B*/
			if (DPR_CheckRotateBoardExist() == TRUE) {	/* ‰ñ“]ƒ{[ƒh‚ªÚ‘±‚³‚ê‚Ä‚¢‚éŽž *//* 97/09/01 By M.Kuwahara */
				Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
				AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_RotateMargin, LST_NOT );
				CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)SYB_SettingStatus[ROTATE_RX_MARGIN], 2, '0' );
				CMN_StringCopy( &List.S.Print[27-1], List.S.Work );
				CMN_MemorySet( &List.S.Attribute[27-1], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
				List.S.Print[30-1]	= 'm';
				List.S.Print[31-1]	= 'm';
				if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
					return ( ret );
				}
			}
#else
#endif
			break;
	 	case	LST_PRM_PAGECOMPOUND: 		/* ƒy[ƒW‡¬ */
			/*†¤Íß°¼Þ‡¬ †¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_PageCompound, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_PageCompoundON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_SORTCOPY: 		/* ƒ\[ƒeƒBƒ“ƒOƒRƒs[ */
#if (PRO_KEYPANEL == PANEL_POPLAR_L)		/* ’Ç‰Á 97/11/13 T.Fukumoto */
			/*†¤¿°Ã¨Ý¸ÞºËß°†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_SortingCopy, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_NonSortCopy() == 0 ) {
				w = 0;	/* ƒmƒ“ƒ\[ƒgƒRƒs[ */
			}
			else {
				w = 1;	/* ƒ\[ƒgƒRƒs[ 	*/
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
#endif
			break;
		case	LST_PRM_COPYPROTECT:		/* ƒRƒs[‹ÖŽ~ */	/* 97/08/26 Add By M.Kuwahara */
/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || ( PRO_KEYPANEL == PANEL_POPLAR_H ) || ( PRO_KEYPANEL == PANEL_SAKAKI ) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* POPLAR_B/POPLAR_L ‚Ì‚Ý */ /* Add by Y.Kano 2003/07/11 */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_CopyProtect, LST_NOT );
			w_pt[0] = (UBYTE *)PWRD_On;
			w_pt[1] = (UBYTE *)PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_CopyProtectON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
#endif
			break;
		case	LST_PRM_DIALINGPAUSE: 		/* ƒ|[ƒYŽžŠÔ */
			/*†¤Îß°½¼Þ¶Ý¾¯Ä†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_DialingPause, LST_NOT );
			CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)CHK_PauseTime(), 2, '0' );
			CMN_StringCopy( &List.S.Print[27-1], List.S.Work );
			CMN_MemorySet( &List.S.Attribute[27-1], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
			AttributeSet( &List.S.Print[30-1], &List.S.Attribute[30-1], PWRD_SecondMark, LST_NOT );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_RINGGINGTIMES: 		/* ŒÄo‚µƒxƒ‹‰ñ” */
			/*†¤ÖËÞÀÞ¼ÍÞÙ¶²½³†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_RinggingTimes, LST_NOT );
			CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)CHK_RingCount(), 2, '0' );
			CMN_StringCopy( &List.S.Print[27-1], List.S.Work );
			CMN_MemorySet( &List.S.Attribute[27-1], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
			AttributeSet( &List.S.Print[30-1], &List.S.Attribute[30-1], PWRD_Try, LST_NOT );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_REDIALTIMES: 		/* ƒŠƒ_ƒCƒ„ƒ‹‰ñ”^ŠÔŠu */
			/*†¤»²ÀÞ²ÔÙ¶²½³/¶Ý¶¸†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_RedialTimes, LST_NOT );
			CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)CHK_RedialCount(), 2, '0' );
			CMN_StringCopy( &List.S.Print[27-1], List.S.Work );
			CMN_MemorySet( &List.S.Attribute[27-1], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
			AttributeSet( &List.S.Print[30-1], &List.S.Attribute[30-1], PWRD_Attemps, LST_NOT );
			if ( CHK_RedialInterval() < 10 ) {
				CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)CHK_RedialInterval(), 1, '0' );
				CMN_StringCopy( &List.S.Print[47-1], List.S.Work );
				CMN_MemorySet( &List.S.Attribute[47-1], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
				AttributeSet( &List.S.Print[49-1], &List.S.Attribute[49-1], PWRD_MinuteMark, LST_NOT );
			}
			else {
				CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)CHK_RedialInterval(), 2, '0' );
				CMN_StringCopy( &List.S.Print[47-1], List.S.Work );
				CMN_MemorySet( &List.S.Attribute[47-1], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
				AttributeSet( &List.S.Print[49-1], &List.S.Attribute[49-1], PWRD_MinuteMark, LST_NOT );
			}
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_ECMMODE: 		/* ‚d‚b‚lƒ‚[ƒh */
			/*†¤ECMÓ°ÄÞ¾¯Ä†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_EcmMode, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_ECM_ON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt ); /* 29 -> 29-1 01/09/96 H.Hirao */
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_PASSCODE: 		/* ƒpƒXƒR[ƒhƒZƒbƒg */
			/*†¤Êß½º°ÄÞ¾¯Ä†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_Passcode, LST_NOT );
			CMN_StringCopyNum( &List.S.Print[27-1], SYB_PasscodeNumber, 4 );
			CMN_MemorySet( &List.S.Attribute[27-1], 4, LST_INV_XXX_XXX );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_CLOSEDNETWORK: 		/* •Âˆæ’ÊM */
			/*†¤Í²²·Â³³¼Ý¾¯Ä†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_CloseNetwork, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_ClosedNetworkON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_SECURITYTX: 		/* ƒpƒXƒ[ƒh‘—M */
			/*†¤Êß½Ü°ÄÞ‘—M	 †¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_SecurityTx, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_SecurityTxON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_BLOCKJUNKFAX: 		/* ƒ_ƒCƒŒƒNƒgƒ[ƒ‹–hŽ~ */
			/*†¤ÀÞ²Ú¸ÄÒ°ÙÎÞ³¼†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_BlockjunkFax, LST_NOT );
			if(!CHK_UNI_JunkMailProtectDial()){		/* ƒƒ‚ƒŠƒXƒCƒbƒ`‚Å•’Ê‚ÌÀÞ²Ú¸ÄÒ°Ù–hŽ~¾¯Ä‚É‚·‚é‚©Œˆ‚ß‚é */
				w_pt[0] = (UBYTE *)&PWRD_On;
				w_pt[1] = (UBYTE *)&PWRD_Off;
				w_pt[2] = NULL_PT;
				if ( CHK_BlockJunkFaxON() == 0 ) {
					w = 1;
				}
				else {
					w = 0;
				}
			}
			else{
				/* Off, Mode1, Mode2, Mode3 ‚Ì‡”Ô‚ð•ÏX 97/08/19 By M.Kuwahara */
				w_pt[0] = (UBYTE *)&PWRD_Mode1;
				w_pt[1] = (UBYTE *)&PWRD_Mode2;
				w_pt[2] = (UBYTE *)&PWRD_Mode3;
				w_pt[3] = (UBYTE *)&PWRD_Off;
				w_pt[4] = NULL_PT;
				switch( CHK_BlockJunkFaxMode() ){
				case	BLOCK_JUNK_FAX_MODE1:
					w	= 0;
					break;
				case	BLOCK_JUNK_FAX_MODE2:
					w	= 1;
					break;
				case	BLOCK_JUNK_FAX_MODE3:
					w	= 2;
					break;
				case	BLOCK_JUNK_FAX_OFF:
					w	= 3;
					break;
				}
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_REMOTEDIAGNOSTIC:		 	/* ƒŠƒ‚[ƒgf’fƒZƒbƒg */
			/*†¤ØÓ°ÄÞ¼ÝÀÞÝ¾¯Ä†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_RemoteDiagnostic, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_RemoteDiagON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_MEMORYTX:		/* ƒƒ‚ƒŠ‘—MƒZƒbƒg */
			/*†¤ÒÓØ¿³¼Ý¾¯Ä†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_MemoryTx, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_MemoryTxON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_STAMP: 		/* ÏƒXƒ^ƒ“ƒv */
			/*†¤Ï½ÀÝÌß	  †¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_Stamp, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_StampON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_RS232C:			/* ‚q‚r‚Q‚R‚Q‚b ƒ{[ƒŒ[ƒg  ƒpƒŠƒeƒB^ƒXƒgƒbƒv^ƒf[ƒ^ */
#if (PRO_CLASS1 == ENABLE)
			if (SYS_RS232C_Exist == 0) {	/* RS232CŠî”Õ‚ª‚È‚¯‚ê‚ÎˆóŽš‚³‚¹‚È‚¢ 1997/09/29 Y.Matsukuma */
				break;
			}
#endif
#if ( PRO_MAKER == FX )
			if ( PaperSizeLen() != LST_LETTER_LEN ) {
				/* if ( (SettingsFunctionCountryTableSw[3] & LST_S_RS232CPARAMETER) != 0 ) { */
					/*†¤RS232C	ÎÞ°Ú°Ä	†¤XXXXXX†¤*/
					/*†¤ÊßØÃ¨/½Ä¯Ìß/ÃÞ°À†¤XXXXXX†¤*/
				/*	if ( (ret = Machine_Setting_RS232C() ) != OK ) { */
					if ( (ret = Machine_Setting_RS232C( &line_dot ) ) != OK ) { /* Modified by S.Fukui Sep.17,1997 */
						return ( ret );
					}
				/* } */
			}
#endif
#if (PRO_CLASS1 == ENABLE)
			/*†¤RS232C	ÎÞ°Ú°Ä	†¤XXXXXX†¤*/
			/*†¤ÊßØÃ¨/½Ä¯Ìß/ÃÞ°À†¤XXXXXX†¤*/
/*			if ( (ret = Machine_Setting_RS232C() ) != OK ) {  */
			if ( (ret = Machine_Setting_RS232C( &line_dot ) ) != OK ) {  /* Modified by S.Fukui Sep.17,1997 */
				return ( ret );
			}
#endif
			break;
		case	LST_PRM_DIALIN:		 	/* ƒ_ƒCƒ„ƒ‹ƒCƒ“ ƒtƒ@ƒNƒX^“d˜b */
#if (PRO_DIALIN == ENABLE)
			/*†¤ÀÞ²ÔÙ²Ý Ì§¸½/ÃÞÝÜ†¤XXXXXX†¤*/
 #if ( PRO_PANEL == KANJI )
 			/* ‚b‚rƒtƒB[ƒ‹ƒh•]‰¿•s‹ï‡|‚U
 			** ‚o‚n‚o‚k‚`‚qQ‚g‚Å‚ÍA‚k‚b‚c‚É‘Ò‹@ƒ‚[ƒh‚Í•\Ž¦‚µ‚Ä‚¢‚È‚¢i‚u‚W‚S‚w‚â‚h‚b‚g‚n‚t‚©‚çj
 			** ‚µ‚©‚µAƒŠƒXƒg‚É‚à‚Å‚È‚¢‚Ì‚Å‚Í¡‚Ç‚Ìƒ‚[ƒh‚É‚È‚Á‚Ä‚¢‚é‚©‚ª‚í‚©‚ç‚È‚¢ˆ×A‚h‚b‚g‚n‚t‚Æ
 			** “¯—l‚ÉAƒŠƒXƒg‚ÉƒXƒCƒbƒ`‚Ì‚n‚m^‚n‚e‚e‚ðƒvƒŠƒ“ƒg‚·‚é‚æ‚¤‚É‚·‚éB By O.Kimoto 1998/03/02 */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
  #if (PRO_DIALIN_SW == ENABLE) /* By H.Fujimura 2002/07/11 */
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_DialIn, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
  #else
			w_pt[0] = (UBYTE *)&PWRD_DialIn;
			w_pt[1] = NULL_PT;
  #endif
			if ( CHK_DialinModeON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}

			/* ƒ_ƒCƒ„ƒ‹ƒCƒ““o˜^î•ñ‚ÌÚ×ˆóŽš */
			if (w == 0) {
				Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^Ž—‚Q‰ñüŽd—l 1998/09/03 By M.Kuwahara */
				if (CHK_Phone2ExtLineOn() == 0) {
					/* FAX/TEL1/TEL2 */
					AttributeSet( &List.S.Print[9-1], &List.S.Attribute[9-1], PWRD_DialIn_Item1, LST_NOT );
					AttributeSet( &List.S.Print[47-1], &List.S.Attribute[47-1], SYB_Dialin.Tel2Number, LST_INV_XXX_XXX );
				}
				else {
					/* FAX/TEL1 */
					AttributeSet( &List.S.Print[9-1], &List.S.Attribute[9-1], PWRD_DialIn_Item2, LST_NOT );
				}
#else
				/* FAX/TEL1/TEL2 */
				AttributeSet( &List.S.Print[9-1], &List.S.Attribute[9-1], PWRD_DialIn_Item1, LST_NOT );
				AttributeSet( &List.S.Print[47-1], &List.S.Attribute[47-1], SYB_Dialin.Tel2Number, LST_INV_XXX_XXX );
#endif
				AttributeSet( &List.S.Print[27-1], &List.S.Attribute[27-1], SYB_Dialin.FaxNumber,  LST_INV_XXX_XXX );
				AttributeSet( &List.S.Print[37-1], &List.S.Attribute[37-1], SYB_Dialin.Tel1Number, LST_INV_XXX_XXX );
				if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
					return ( ret );
				}

				Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
				AttributeSet( &List.S.Print[9-1], &List.S.Attribute[9-1], PWRD_BellTime, LST_NOT );
				CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)SYB_Dialin.BellTime, 2, '0' );
				CMN_StringCopy( &List.S.Print[27-1], List.S.Work );
				CMN_MemorySet( &List.S.Attribute[27-1], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
				AttributeSet( &List.S.Print[30-1], &List.S.Attribute[30-1], PWRD_SecondMark, LST_NOT );
				if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
					return ( ret );
				}
			}
 #else
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_DialIn, LST_NOT );
			AttributeSet( &List.S.Print[27-1], &List.S.Attribute[27-1], SYB_Dialin.FaxNumber,  LST_INV_XXX_XXX );
			AttributeSet( &List.S.Print[37-1], &List.S.Attribute[37-1], SYB_Dialin.Tel1Number, LST_INV_XXX_XXX );
			AttributeSet( &List.S.Print[47-1], &List.S.Attribute[47-1], SYB_Dialin.Tel2Number, LST_INV_XXX_XXX );
			AttributeSet( &List.S.Print[54-1], &List.S.Attribute[54-1], PWRD_BellTime, LST_NOT );
			CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)SYB_Dialin.BellTime, 2, '0' );
			CMN_StringCopy( &List.S.Print[63-1], List.S.Work );
			CMN_MemorySet( &List.S.Attribute[63-1], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
			AttributeSet( &List.S.Print[66-1], &List.S.Attribute[66-1], PWRD_SecondMark, LST_NOT );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
 #endif
#endif
			break;
		case	LST_PRM_OPERATIONPROTECT:		/* ƒIƒyƒŒ[ƒVƒ‡ƒ“ƒvƒƒeƒNƒg */
			/* ƒIƒyƒŒ[ƒVƒ‡ƒ“ƒvƒƒeƒNƒg */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[6], &List.S.Attribute[6], PWRD_OperationProtect, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_OperationProtect() == 0 ){
				w = 1;
			}else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_MESAGETRANS: 		/* ƒƒbƒZ[ƒW‘—M */
			/*†¤Ò¯¾°¼Þ¿³¼Ý†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_MesageTrans, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_MessageTxON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_SILENTOPERATION:		/* ƒTƒCƒŒƒ“ƒgƒIƒyƒŒ[ƒVƒ‡ƒ“ */
 /*#if defined(USA) 1998/02/23 Y.Murata */
 #if defined(JPN)
 #else
			/*†¤»²ÚÝÄµÍßÚ°¼®Ý†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_SilentOperation, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_SilentOperation() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
#endif
			break;
		case	LST_PRM_COPYREDUCTION:			/* ƒRƒs[k¬—¦ */
#if (PRO_KEYPANEL == PANEL_ANZU_L) ||  (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec K.W.Q 2004/06/28 */
			/*†¤ºËß°¼­¸¼®³ØÂ†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_CopyReduction, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_Auto;
			w_pt[1] = (UBYTE *)&PWRD_P100;
 #if (PRO_FIXED_REDUCTION == ENABLE)	/* ‚k‚S‚O‚O‘Î‰ž‚ÅŒÅ’èk¬—¦–³‚µ‚Ìˆ—‚ð’Ç‰Á by K.Watanabe 1998/05/13 */
			w_pt[2] = (UBYTE *)&PWRD_P97;
			w_pt[3] = (UBYTE *)&PWRD_P91;
			w_pt[4] = (UBYTE *)&PWRD_P81;
			w_pt[5] = (UBYTE *)&PWRD_P75;
			w_pt[6] = NULL_PT;
 #else
			w_pt[2] = NULL_PT;
 #endif
			w = (UBYTE)(CHK_CopyFixedReduction());
 #if (PRO_FIXED_REDUCTION == ENABLE)	/* ‚k‚S‚O‚O‘Î‰ž‚ÅŒÅ’èk¬—¦–³‚µ‚Ìˆ—‚ð’Ç‰Á by K.Watanabe 1998/05/13 */
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 5, w_pt );
			AttributeSet( &List.S.Print[62-1], &List.S.Attribute[62-1], PWRD_ThValue00mm, LST_NOT );
			CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)CHK_CopyMargin(), 2, '0' );
			CMN_StringCopy( &List.S.Print[72-1], List.S.Work );
			CMN_MemorySet( &List.S.Attribute[72-1], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
 #else
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			AttributeSet( &List.S.Print[57-1], &List.S.Attribute[57-1], PWRD_ThValue00mm, LST_NOT );
			CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)CHK_CopyMargin(), 2, '0' );
			CMN_StringCopy( &List.S.Print[67-1], List.S.Work );
			CMN_MemorySet( &List.S.Attribute[67-1], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
 #endif
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
#endif
			break;
		case	LST_PRM_PAPERSIZE:			/* ‹L˜^Ž†ƒy[ƒp[ƒTƒCƒY */
#if (PRO_PC_PRINT == DISABLE)	/* DPRAMŒo—R‚ÌPCÌßØÝÄ‹@”\‚È‚µ */
 #if defined(USA)  /* 1996/08/30 by H.Yagi */
			/*†¤·Û¸¼Íß°Êß°»²½Þ†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_PaperSize, LST_NOT );
			/* ’j‚o‚bƒvƒŠƒ“ƒg‹@”\‚ ‚è‚Å‚àƒvƒŠƒ“ƒ^ƒIƒvƒVƒ‡ƒ“ƒ{[ƒh‚ª–¢‘•’…‚ÌŽž‚ÍA
			**     ‚o‚bƒvƒŠƒ“ƒg‹@”\‚È‚µ‚ÌŽž‚Æ“¯‚¶ˆ—‚ðs‚¤‚Ì‚ÅA•ÏX“™‚ðs‚Á‚½ê‡‚ÍA
			**     ‡‚í‚¹‚ÄƒvƒŠƒ“ƒ^ƒIƒvƒVƒ‡ƒ“ƒ{[ƒh–¢‘•’…‚ÌŽž‚ÌŠ‚à•ÏX‚µ‚Ä‰º‚³‚¢
			*/
			w_pt[0] = (UBYTE *)&PWRD_Letter;
			w_pt[1] = (UBYTE *)&PWRD_Legal;
			w_pt[2] = NULL_PT;
			if( CHK_UpperManualCassete() == 3 ) {
				w = 0;
			} else if (CHK_UpperManualCassete() == 4) {
				w = 1;
			} else {
				w = 2;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( CHK_LowerManualCassete() != 0 ) {	/*‰º’i¶¾¯Ä‚ ‚è*/
				if ( CHK_LowerManualCassete() == 3 ) {
					w = 0;
				}
				else {
					w = 2;
				}
				Param_set( &List.S.Print[49], &List.S.Attribute[49], w, 10, w_pt );
			}
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
 #endif
#else							/* DPRAMŒo—R‚ÌPCÌßØÝÄ‹@”\‚ ‚è 1996/09/18 by K.Watanabe */
 #if (PRO_PRINT_TYPE == LASER)	/* 97/09/24 By M.Kuwahara */
			if (DPR_CheckOptionPrintBoardExist()/*DPR_PCR_Enable 1997/01/14 By J.Miyazaki*/) {	/** ƒvƒŠƒ“ƒ^ƒIƒvƒVƒ‡ƒ“ƒ{[ƒh‚ª‘•’…‚³‚ê‚Ä‚¢‚éŽž*/

				/*†¤·Û¸¼Íß°Êß°»²½Þ†¤XXXXXX†¤*/
				Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
  #if (PRO_KEYPANEL == PANEL_ANZU_L)
				AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_PaperSize, LST_NOT );
  #else
				AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_PC_PaperManual, LST_NOT );
  #endif
				/* Œ»ÝAƒIƒyƒŒ[ƒVƒ‡ƒ“‚ÅÝ’è‚³‚ê‚Ä‚¢‚éŽè·‚µ‚Ì‹L˜^Ž†ƒTƒCƒY‚ðŠl“¾‚µ‚Ü‚·
				** ’jSYB_SettingStatus[PCR_UPPER_SIZE]‚ÆSYS_Paper1size‚Ìdefine‚ªˆá‚¤‚Ì‚ÅA
				**     SYS_Paper1size‚Ìdefine‚É‡‚í‚¹‚é‚½‚ß‚ÉCHK_PCR_UpperManualCassete()‚©‚ç1‚ðˆø‚«‚Ü‚·
				*/
/*				setting_paper_size = (UBYTE)(CHK_PCR_UpperManualCassete() - 1);*/
				setting_paper_size = (UBYTE)(CHK_PCR_ManualCassetteSize() - 1);

				/* ‘S‹L˜^Ž†ƒTƒCƒY‚Ì“à,ƒTƒ|[ƒg‚³‚ê‚Ä‚¢‚é‹L˜^Ž†‚¾‚¯‚ð’Šo‚µ,‚»‚Ìƒ[ƒfƒBƒ“ƒO‚Ìƒ|ƒCƒ“ƒ^[‚ðƒZƒbƒg‚µ‚Ü‚· */
				support_paper_cnt = 0;
  #if (PRO_KEYPANEL == PANEL_POPLAR_B)
				support_paper_size[support_paper_cnt++]	= PWRD_None;	/* 97/07/09 Add by M.Kuwahara */
  #endif
				for (i = SYS_FIRST_PAPER_SIZE; i <= SYS_LAST_PAPER_SIZE; i++) {
					if (DPR_PCR_SupportPaperSizeTable[i][DPR_PCR_MANUAL_CASSETTE] == 1) {	/* »Îß°Ä‚³‚ê‚Ä‚¢‚é‹L˜^Ž†‚ÌŽž */
						/* ‹L˜^Ž†ƒTƒCƒY‚Ìƒ[ƒfƒBƒ“ƒO‚Ìƒ|ƒCƒ“ƒ^[‚ðƒZƒbƒg‚µ‚Ü‚· */
  #if (PRO_KEYPANEL == PANEL_ANZU_L)  /* ANZU‚Ì‚Ý */
						support_paper_size[support_paper_cnt] = PWRD_Paper_A5 + (i * 8);
  #else
						support_paper_size[support_paper_cnt] = PWRD_PaperSize_A5 + (i * 8);
  #endif
						/* Šl“¾‚µ‚½‹L˜^Ž†ƒTƒCƒY‚ÍA‘S‹L˜^Ž†‚Ì’†‚Ì’l‚È‚Ì‚ÅA
						** ƒTƒ|[ƒg‚³‚ê‚Ä‚¢‚é‹L˜^Ž†‚Ì’†‚Å‚Ì‡”Ô‚ÉƒZƒbƒg‚µ‚È‚¨‚µ‚Ü‚·
						*/
  #if (PRO_KEYPANEL == PANEL_POPLAR_B)
						if (setting_paper_size == SYS_NO_CASSETTE){	/* "Å¼"‚ÌÜ°ÃÞ¨Ý¸Þ‚ð¾¯Ä‚·‚éˆ× 97/07/09 Add by M.Kuwahara */
							setting_paper_size	= 0;
						}else
  #endif
						if (i == setting_paper_size) {	/* µÍßÚ°¼®Ý‚ÅÝ’è‚³‚ê‚Ä‚¢‚é‹L˜^Ž†‚ÌŽž */
							setting_paper_size = support_paper_cnt;
						}
						support_paper_cnt++;
					}
				}
				support_paper_cnt--;	/* ÅŒã‚É{‚P‚³‚ê‚ÄI‚í‚Á‚Ä‚¢‚é‚Ì‚ÅA‚P‚ðˆø‚¢‚Ä‚¨‚­ */

				loop_end = 0;
				line_number = 5;	/* ƒ[ƒfƒBƒ“ƒO‚Ì“s‡ãA‚Pƒ‰ƒCƒ“‚É‚ÍA‚TŒÂ‚µ‚©ˆóü‚Å‚«‚Ü‚¹‚ñ */
				max_line = 7;		/* ‘S‹L˜^Ž†ƒTƒCƒY‚ª‚R‚PŽí—Þ‚ ‚èA‚Pƒ‰ƒCƒ“‚É‚TŒÂˆóü‚·‚é‚Ì‚ÅAÅ‘å‚Vs•K—v */
				for (i = 0; i < max_line; i++) {
					w = 0xFF;
					/* Param_set()‚ð‚»‚Ì‚Ü‚ÜŽg—p‚·‚é‚æ‚¤‚ÉAƒTƒ|[ƒg‚³‚ê‚Ä‚¢‚é‹L˜^Ž†‚Ì‚¤‚¿A
					** ‚Ps‚Éˆóü‚Å‚«‚éŒÂ”•ª‚¾‚¯‚ðw_pt[]‚É‡”Ô‚ÉƒZƒbƒg‚µ‚Ä‚¢‚«‚Ü‚·
					*/
					for (w_loop = 0; w_loop < line_number; w_loop++) {
						w_paper_number = (line_number * i) + w_loop;	/* ŽŸ‚Ì»Îß°Ä‚³‚ê‚Ä‚¢‚é‹L˜^Ž†‚Ì‡”Ô‚ðŒvŽZ‚µ‚Ü‚·*/
						w_pt[w_loop] = support_paper_size[w_paper_number];	/* ‹L˜^Ž†‚ÌÜ°ÃÞ¨Ý¸Þ‚ÌÎß²ÝÀ°‚ð¾¯Ä‚µ‚Ü‚· */
						/* ƒ[ƒfƒBƒ“ƒO‚ðƒZƒbƒg‚µ‚½‹L˜^Ž†‚ªAƒIƒyƒŒ[ƒVƒ‡ƒ“‚ÅÝ’è‚³‚ê‚Ä‚¢‚é‹L˜^Ž†‚ÌŽž */
						if (w_paper_number == setting_paper_size) {
							w = w_loop;		/* ˆóüŽž‚É•¶Žš‚ð”½“]‚É‚µ‚Ü‚· */
						}

						/* ƒ[ƒfƒBƒ“ƒO‚ðƒZƒbƒg‚µ‚½‹L˜^Ž†‚ªAƒTƒ|[ƒg‚³‚ê‚Ä‚¢‚éÅŒã‚Ì‹L˜^Ž†‚ÌŽž */
						if (w_paper_number == support_paper_cnt) {
							loop_end = 1;
							/* forƒ‹[ƒv‚ÌI—¹ðŒ‚Åƒ‹[ƒv‚ðI‚í‚Á‚½Žž‚ÍAƒ‹[ƒv•Ï”‚ÍA
							** ƒ[ƒfƒBƒ“ƒO‚Ìƒ|ƒCƒ“ƒ^[‚ðƒZƒbƒg‚µ‚½ŽŸ‚Ì”z—ñ‚É•Ï‚í‚Á‚Ä‚¢‚é‚Ì‚ÅA
							** “¯‚¶‚æ‚¤‚ÉNULL_PT‚ð‚»‚Ì‚Ü‚ÜƒZƒbƒg‚Å‚«‚é‚æ‚¤‚É{‚P‚µ‚Ä‚¨‚­
							*/
							w_loop++;
							break;
						}
					}
					w_pt[w_loop] = NULL_PT;

					Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
					if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
						return ( ret );
					}
					Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
					if (loop_end == 1) {	/* ƒTƒ|[ƒg‚³‚ê‚Ä‚¢‚é‹L˜^Ž†‚ðA‘S‚Äˆóü‚µ‚½Žž */
						break;
					}
				}
			}
			else {					/** ƒvƒŠƒ“ƒ^ƒIƒvƒVƒ‡ƒ“ƒ{[ƒh‚ª–¢‘•’…‚ÌŽž 1996/10/08 by K.Watanabe*/
			/* ƒvƒŠƒ“ƒ^ƒIƒvƒVƒ‡ƒ“ƒ{[ƒh‚ª–¢‘•’…‚ÌŽž‚ÍA’Êí‚Ì‹L˜^Ž†ƒTƒCƒYÝ’è‚ÌŽž‚Æ“¯‚¶‚Å‚· */
				Machine_Setting_Line( 1, List.S.Print, List.S.Attribute ); /* ’Ç‰Á 1997/09/17 Y.Matsukuma */
				AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_PaperSize, LST_NOT ); /* Added by S.Fukui Sep.17,1997 */

				if (CMN_CheckAramcoSuportA4Paper()) {	/* 1998/06/03 Y.Murata ±×Ñº“ÁŽê‘Î‰ž LT,LG,A4‘Î‰ž ARM_A4*/

					w_pt[0] = (UBYTE *)&PWRD_Letter;
					w_pt[1] = (UBYTE *)&PWRD_Legal;
					w_pt[2] = (UBYTE *)&PWRD_A4;
					w_pt[3] = NULL_PT;

					switch (CHK_UpperManualCassete()) {
					case UPPER_SIZE_LETTER:
						w = 0;
						break;
					case UPPER_SIZE_LEGAL:
						w = 1;
						break;
					case UPPER_SIZE_A4:
						w = 2;
						break;
					default:
						w = 3;
						break;
					}

				}
				else {

  #if defined(USA)	/* ‘•Ê‚Å•ª‚¯‚Ü‚µ‚½ 1998/01/08 Y.Matsukuma */
					w_pt[0] = (UBYTE *)&PWRD_Letter;
					w_pt[1] = (UBYTE *)&PWRD_Legal;
					w_pt[2] = NULL_PT;

					switch (CHK_UpperManualCassete()) {
					case UPPER_SIZE_LETTER:
						w = 0;
						break;
					case UPPER_SIZE_LEGAL:
						w = 1;
						break;
					default:
						w = 2;
						break;
					}
  #endif
  #if defined(TWN)  /* 1997/01/30 Eguchi */
					w_pt[0] = (UBYTE *)&PWRD_A4;
					w_pt[1] = (UBYTE *)&PWRD_F4;
					w_pt[2] = NULL_PT;

					switch (CHK_UpperManualCassete()) {
					case UPPER_SIZE_A4:
						w = 0;
						break;
					case UPPER_SIZE_F4:
						w = 1;
						break;
					default:
						w = 2;
						break;
					}
  #endif
  #if defined(GBR) || defined(JPN)  /* 1997/04/03 M.H */ /* JPN’Ç‰Á1997/06/24 Eguchi */
					w_pt[0] = (UBYTE *)&PWRD_A4;
					w_pt[1] = NULL_PT;

					switch (CHK_UpperManualCassete()) {
					case UPPER_SIZE_A4:
						w = 0;
						break;
					default:
						w = 1;
						break;
					}
  #endif
  #if defined(AUS) /* 1997/01/31 */
					w_pt[0] = (UBYTE *)&PWRD_A4;
					w_pt[1] = (UBYTE *)&PWRD_F4;
					w_pt[2] = NULL_PT;

					switch (CHK_UpperManualCassete()) {
					case UPPER_SIZE_A4:
						w = 0;
						break;
					case UPPER_SIZE_F4:
						w = 1;
						break;
					default:
						w = 2;
						break;
					}
  #endif
				}	/* End of ARM_A4 disable */

				Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );

				if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
					return ( ret );
				}
			}
 #endif
#endif
			break;
 #if !defined(STOCKHM2) /* Mod by SMuratec C.P 2004/07/23 */
		case	LST_PRM_DEPARTMENT:			/* •”–åŠÇ—ƒZƒbƒg */
			/* •”–åŠÇ—ƒZƒbƒg */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[6], &List.S.Attribute[6], PWRD_Department, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_DepartmentON() == 0 ) {
				w = 1;
			} else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_DEPARTMENTPROTECT:			/* •”–åŠÇ—ƒvƒƒeƒNƒg */
			/* •”–åŠÇ—ƒvƒƒeƒNƒg */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[6], &List.S.Attribute[6], PWRD_DepartmentProtect, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_SectionCheckProtect() == 0 ) {
				w = 1;
			} else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
 #endif /* !defined(STOCKHM2) */
		case	LST_PRM_REMOTESECURITYRX: 		/* ƒZƒLƒ…ƒŠƒeƒBŽóM */
			/* ŽóMŒ´eƒvƒŠƒ“ƒgƒvƒƒeƒNƒg */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_RemoteSecurityRx, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;

	/*		if ( CHK_MemoryRxPrintProtect() == 0 ) { @*Comment By Eguchi 1996/04/27 */
			if (CHK_SecurityReceiveON() == 0) {
				w = 1;
			} else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_PIN_ACCESSMODE: 		/* ‚o‚h‚mƒAƒNƒZƒX */
#if (PRO_PIN_ACCESS == ENABLE)
 #if (PRO_MULTI_TTI == DISABLE) /* By H.Fujimura 1999/03/25 */
			/* PINƒAƒNƒZƒX */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[6], &List.S.Attribute[6], PWRD_PINAccessMode, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_Mode1;
			w_pt[1] = (UBYTE *)&PWRD_Mode2;
			w_pt[2] = (UBYTE *)&PWRD_Off;
			w_pt[3] = NULL_PT;
			if ( CHK_PIN_AccessMode() == 0 ) {
				w = 2;
			} else if (CHK_PIN_AccessMode() == 0x10 ) {
				w = 0;
			} else {
				w = 1;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
 #endif
#endif
			break;
		case	LST_PRM_DAYLIGHTSAVING: 		/* ‰ÄŽžŠÔŽ©“®Ø‚è‘Ö‚¦ */
#if defined(USA) /* 1996/08/19 Eguchi */
			/* ‰ÄŽžŠÔŽ©“®Ø‚è‘Ö‚¦ */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[6], &List.S.Attribute[6], PWRD_DayLightSaving, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_DayLightSavingAuto() == 0 ) {
				w = 1;
			} else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
#endif
			break;
		case	LST_PRM_RINGMASTR: 		/* ƒŠƒ“ƒOƒ}ƒXƒ^ƒZƒbƒg */
#if defined(USA)
			/*†¤ØÝ¸ÞÏ½À°¾¯Ä†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_RingMastr, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_RingMasterON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			AttributeSet( &List.S.Print[49-1], &List.S.Attribute[49-1], PWRD_Pattern, LST_NOT );
			List.S.Print[59-1] = (UBYTE)('A' + CHK_RingMasterPattern() );
/*			CMN_MemorySet( &List.S.Attribute[57-1], 1, LST_INV_XXX_XXX ); */
			CMN_MemorySet( &List.S.Attribute[59-1], 1, LST_INV_XXX_XXX );  /* Modified by S.Fukui  Sep.16,1997 */
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
#endif
#if defined(AUS)	/* DUET 1997/05/21 Y.Murata */
		if (SYB_MachineParameter[0] == 0x00) {	/* AUS */
/*			if ( (ret = Machine_Setting_Middle()) != OK ) {
**				return ( ret );
**			}*/
			/*†¤ØÝ¸ÞÏ½À°¾¯Ä†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_RingMastr, LST_NOT );
			w_pt[0] = PWRD_On;
			w_pt[1] = PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_RingMasterON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			/*if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {*/
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
		}
#endif
			break;
		case	LST_PRM_MERCURYPAUSE: 		/* ƒ}[ƒLƒ…ƒŠ[ƒ|[ƒY */
#if defined(GBR)/** Add By H.H 1996/08/28 */
			/* Mercury Pause */
			Machine_Setting_Line(1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[6], &List.S.Attribute[6], PWRD_MercuryPause, LST_NOT );
			CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)SYB_SettingStatus[MERCURY_PAUSE], 2, '0' );
			CMN_StringCopy( &List.S.Print[26], List.S.Work );
			CMN_MemorySet( &List.S.Attribute[26], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
			AttributeSet( &List.S.Print[30-1], &List.S.Attribute[30-1], PWRD_SecondMark, LST_NOT );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
#endif
			break;
		case	LST_PRM_RXALARM: 		/* ŽóMŠ®—¹ƒAƒ‰[ƒ€ */
#if defined(GBR) /** Add By H.H 1996/08/28 */
			/* Rx Alarm */
			Machine_Setting_Line(1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[6], &List.S.Attribute[6], PWRD_RxAlarm, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_AudibleAlarmON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
#endif /** By H.H 1996/08/28 */
			break;
		case	LST_PRM_COMPAGES: 		/* –‡” */
#if ( PRO_MAKER == FX )		/* FX‚Ì‚Ý×²ÌÓÆÀ°ÃÞ°À‚ð‹LÚ‚·‚é 94.11.4 Toyoda */
			if (FX_Model == 1) {	/** ‘º“c^‚e‚wŽ¯•Ê‚q‚n‚lƒXƒCƒbƒ`‚ª‚e‚w‚È‚ç */
				/* “Ç‚ÝŽæ‚è–‡” */
				Prn_Att_Str_Clear( &List.S.Print[0], &List.S.Attribute[0] );
				List.S.Print[7-1] = 'S';
				List.S.Print[8-1] = ':';
				CMN_UnsignedLongToASC( &List.S.Print[9-1],	/* Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
					 SYB_LifeMonitor.ScanCount, 6, '0' );
				if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
					return ( ret );
				}
				/* ‘—M–‡” */
				Prn_Att_Str_Clear( &List.S.Print[0], &List.S.Attribute[0] );
				List.S.Print[7-1] = 'T';
				List.S.Print[8-1] = ':';
				CMN_UnsignedLongToASC( &List.S.Print[9-1],	/* Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
					 SYB_LifeMonitor.TransmitCount, 6, '0' );
				if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
					return ( ret );
				}
				/* ƒvƒŠƒ“ƒg–‡” */
				Prn_Att_Str_Clear( &List.S.Print[0], &List.S.Attribute[0] );
				List.S.Print[7-1] = 'P';
				List.S.Print[8-1] = ':';
				CMN_UnsignedLongToASC( &List.S.Print[9-1],	/* Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
					 SYB_LifeMonitor.PrintCount, 6, '0' );
				if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
					return ( ret );
				}
				/* ŽóM–‡” */
				Prn_Att_Str_Clear( &List.S.Print[0], &List.S.Attribute[0] );
				List.S.Print[7-1] = 'R';
				List.S.Print[8-1] = ':';
				CMN_UnsignedLongToASC( &List.S.Print[9-1],	/* Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
				 SYB_LifeMonitor.ReceiveCount, 6, '0' );
				if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
					return ( ret );
				}
			}
#endif
			break;
		case	LST_PRM_HOLDMELODY: 		/* •Û—¯ÒÛÃÞ¨° */
/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* ’Ç‰Á 97/11/07 T.Fukumoto */
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
  #if defined (JPN) /* ‚s‚v‚m‚Í•Û—¯ƒƒƒfƒB‚È‚µ by H.Hirao 1999/02/04 */
			/*†¤ÎØ­³ÒÛÃÞ¨°¾¯Ä†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_Holdmelody, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_HoldMelodyON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
  #endif
 #else
			/*†¤ÎØ­³ÒÛÃÞ¨°¾¯Ä†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_Holdmelody, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_HoldMelodyON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
 #endif
#endif
#if ( PRO_PANEL == KANJI )
			/* ‚o‚n‚o‚k‚`‚qQ‚g‚¾‚¯ðŒ‚©‚çŠO‚ê‚Ä‚¢‚Ü‚µ‚½B By O.Kimoto 1998/03/02 */
			/*†¤ÎØ­³ÒÛÃÞ¨°¾¯Ä†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_Holdmelody, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_HoldMelodyON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
#endif
			break;
#if ( PRO_PANEL == KANJI )
		case LST_PRM_RELAYED_RELAY_TX:	/* ’†XŒp */
			/* ’Ç‰Á˜R‚ê By O.Kimoto 1998/03/02 */
			/*†¤’†XŒp†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_RelayedRelayTx, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_RelayedRelayTxON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
#endif
#if (PRO_REMOTE_RX == ENABLE)
		case	LST_PRM_REMOTE_RX: 		/* ƒŠƒ‚[ƒgŽóM */
			/*†¤ØÓ°Ä ¼Þ­¼Ý†¤XXXXXX†¤*//* ‚m‚s‚sŽd—l‚Ìƒ|ƒvƒ‰‚k‚ÅŽg—p 98/03/13 Add By T.Fukumoto */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_RemoteReceive, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_RemoteRxON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
#endif
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
		case	LST_PRM_ONHOOK_RX: 		/* ƒIƒ“ƒtƒbƒNŽóM */
			/*†¤µÝÌ¯¸ ¼Þ­¼Ý†¤XXXXXX†¤*//* ‚m‚s‚sŽd—l‚Ìƒ|ƒvƒ‰‚k‚ÅŽg—p 98/03/13 Add By T.Fukumoto */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_OnHookReceive, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if ( CHK_OnHookRX_ON() == 0 ) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1998/06/26 Add By M.Kuwahara */
		case	LST_PRM_PAPERTYPE:	/* ‹L˜^Ž†À²Ìß */
			/*†¤‹L˜^Ž†À²Ìß†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_PaperType, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_NormalPaper;
			w_pt[1] = (UBYTE *)&PWRD_ThermalPaper;
			w_pt[2] = NULL_PT;
			if (CHK_HeatTransferON() != 0) { /** •’ÊŽ†‚Æ‚È‚Á‚Ä‚¢‚éê‡ */
				w = 0;
			}
			else {
				w = 1;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/24 Add By M.Kuwahara */
 #if !defined(STOCKHM2) /*  Mod by SMuratec C.P 2004/08/20 */
		case	LST_PRM_WARP:		/* Ü°Ìß‹@”\					*/
			/*†¤Ü°Ìß‹@”\†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_WarpFunction, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if (CHK_WarpFunctionON() == 0) { /** ‚n‚e‚e‚Ìê‡ */
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
 #endif
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE)	/* 1998/06/24 By M.Kuwahara */
		case	LST_PRM_NUMBERDISPLAY:	/* ÅÝÊÞ°ÃÞ¨½ÌßÚ²			*/
			/*†¤ÅÝÊÞ°ÃÞ¨½ÌßÚ²†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_NumberDisplay, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_NoConnect;
			w_pt[1] = (UBYTE *)&PWRD_Tel2Connect;
			w_pt[2] = NULL_PT;
#if (0)	/* 1998/11/26 By M.Kuwahara */
//			switch( SYB_NumberDisplayTel ) {
//			case	ND_NO_CONNECTING:
//				w = 0;
//				break;
//			case	ND_TEL2_CONNECTING:
//				w = 1;
//				break;
//			default:
//				break;
//			}
#else
			if (SYB_SettingStatus[SETTING_STATUS_30] & ND_TEL2_ND_ON) {
				w = 1;
			}
			else {
				w = 0;
			}
#endif
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if (CHK_NumberDisplayON() == 0) { /** ‚n‚e‚e‚Ìê‡ */
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[47], &List.S.Attribute[47], w, 10, w_pt );

			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
#endif
#if (PRO_NUMBER_DISPLAY_WARP == ENABLE) /* By H.Fujimura 1999/01/07 */
		case	LST_PRM_ND_WARP:		/* ‚m‚cƒ[ƒv				*/
			/*†¤NDÜ°Ìß†¤XXXXXX†¤*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_ND_Warp, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if (CHK_ND_WarpON() == 0) { /** ‚n‚e‚e‚Ìê‡ */
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
#endif
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
		case	LST_PRM_MERCURYNUMBER:		/* ƒ}[ƒLƒ…ƒŠ[ƒiƒ“ƒo[ */
			/* Mercury Number */
			Machine_Setting_Line(1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[6], &List.S.Attribute[6], PWRD_MercuryNumber, LST_NOT );
			CMN_StringCopy( &List.S.Print[26], SYB_MercuryDialBuffer );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
#endif
#if defined(KEISATSU)	/* ŒxŽ@FAX‘Î‰ž Added by SMuratec ‰Ä 2005/07/21 */
		case	LST_PRM_PHONETYPE_EXT:			/* Œx“d’ÊM‰ñü				*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_EXTPhoneType, LST_NOT );
			mode = (UBYTE)CHK_DialTypeExt();
			w_pt[0] = (UBYTE *)&PWRD_ToneLine;
			w_pt[1] = (UBYTE *)&PWRD_Pps10;
			w_pt[2] = (UBYTE *)&PWRD_Pps20;
			w_pt[3] = NULL_PT;
			switch ( mode ) {
			case DIAL_SPEED_10PPS_EXT:
				mode = 1;
				break;
			case DIAL_SPEED_20PPS_EXT:
				mode = 2;
				break;
			case LINE_TYPE_TONE_EXT:
				mode = 0;
				break;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], mode, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
			
		case	LST_PRM_RINGGINGTIMES_EXT:		/* Œx“d‰ñü‘¤ŒÄoƒxƒ‹‰ñ”	*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_EXTRinggingTimes, LST_NOT );
			CMN_UnsignedIntToASC_NULL( List.S.Work, (UWORD)CHK_ExtRingCount(), 2, '0' );
			CMN_StringCopy( &List.S.Print[27-1], List.S.Work );
			CMN_MemorySet( &List.S.Attribute[27-1], CMN_StringLength(List.S.Work), LST_INV_XXX_XXX );
			AttributeSet( &List.S.Print[30-1], &List.S.Attribute[30-1], PWRD_Try, LST_NOT );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_SETTING_LINE:			/* —Dæ’ÊM‰ñü 			*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_SettingLine, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_KeidenLine;
			w_pt[1] = (UBYTE *)&PWRD_KanyuLine;
			w_pt[2] = (UBYTE *)&PWRD_SettingSave;
			w_pt[3] = NULL_PT;
			switch(SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_LINE_MASK){
			case DEFAULT_LINE_KEIDEN:
				mode = 0;
				break;
			case DEFAULT_LINE_KANYU:
				mode = 1;
				break;
#if 0 /* ŒxŽ@FAX DVT_ID86 Modify by SMuratec ‰Ä 2006/01/12 */
			case DEFAULT_LINE_HOJI:
#else
			case DEFAULT_LINE_HOJI|DEFAULT_LINE_KEIDEN:
			case DEFAULT_LINE_HOJI|DEFAULT_LINE_KANYU:
#endif
				mode = 2;
				break;
			default:
				mode = 0;
				break;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], mode, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_SETTING_FAXMODE:		/* —Dæ’ÊM•ûŽ® 			*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_SettingFaxMode, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_IsseiFaxcom;
			w_pt[1] = (UBYTE *)&PWRD_KobetuFaxcom;
			w_pt[2] = (UBYTE *)&PWRD_SettingSave;
			w_pt[3] = NULL_PT;
			switch(SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_COM_METHOD_MASK){
			case DEFAULT_COM_METHOD_ISSEI:
				mode = 0;
				break;
			case DEFAULT_COM_METHOD_KOBETSU:
				mode = 1;
				break;
#if 0 /* ŒxŽ@FAX DVT_ID86 Modify by SMuratec ‰Ä 2006/01/12 */
			case DEFAULT_COM_METHOD_HOJI:
#else
			case DEFAULT_COM_METHOD_HOJI|DEFAULT_COM_METHOD_ISSEI:
			case DEFAULT_COM_METHOD_HOJI|DEFAULT_COM_METHOD_KOBETSU:
#endif
				mode = 2;
				break;
			default:
				mode = 0;
				break;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], mode, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_SCRAMBLE_KEIDEN:		/* Œx“d‰ñü‘¤ƒXƒNƒ‰ƒ“ƒuƒ‹	*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_ScrambleKeiden, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_KEIDEN_SCRAMLE_ON) {
				w = 0;
			}
			else {
				w = 1;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_SCRAMBLE_KANYU:			/* ‰Á“ü‰ñü‘¤ƒXƒNƒ‰ƒ“ƒuƒ‹	*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_ScrambleKanyu, LST_NOT );
			w_pt[0] = (UBYTE *)&PWRD_On;
			w_pt[1] = (UBYTE *)&PWRD_Off;
			w_pt[2] = NULL_PT;
			if (SYB_MachineParameter[M_PARA_SW_I0] & DEFAULT_KANYU_SCRAMLE_ON) {
				w = 0;
			}
			else {
				w = 1;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_REMOTE_NUM_ISSEI:		/* ˆêÄ’ÊM‚ÌƒŠƒ‚[ƒg“Á”Ô	*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_RemoteNumIssei, LST_NOT );
			if( CHK_RemoteTransferDialOne() ){
				w_pt[0] = (UBYTE *)"7";
				w_pt[1] = (UBYTE *)"8";
				w_pt[2] = (UBYTE *)"9";
				w_pt[3] = NULL_PT;
			}
			else{
				w_pt[0] = (UBYTE *)"77";
				w_pt[1] = (UBYTE *)"88";
				w_pt[2] = (UBYTE *)"99";
				w_pt[3] = NULL_PT;
			}
			switch( (SYS_MemorySwitch[MEMORY_SW_G9] & REMOTE_TRANSFER_DIAL_NUM1) >> 4 ){
			case 7	:
				w = 0;
				break;
			case 8:
				w = 1;
				break;
			case 9:
				w = 2;
				break;
			default:
				w = 2;
				break;
			}
			
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
		case	LST_PRM_REMOTE_NUM_KOBETSU:		/* ŒÂ•Ê’ÊM‚ÌƒŠƒ‚[ƒg“Á”Ô	*/
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_RemoteNumKobetu, LST_NOT );
			if( CHK_RemoteTransferDialOne() ){
				w_pt[0] = (UBYTE *)"1";
				w_pt[1] = (UBYTE *)"2";
				w_pt[2] = (UBYTE *)"3";
				w_pt[3] = NULL_PT;
			}
			else{
				w_pt[0] = (UBYTE *)"11";
				w_pt[1] = (UBYTE *)"22";
				w_pt[2] = (UBYTE *)"33";
				w_pt[3] = NULL_PT;
			}
			switch( (SYS_MemorySwitch[MEMORY_SW_G7] & REMOTE_TRANSFER_DIAL_NUM1) >> 4 ){
			case 1	:
				w = 0;
				break;
			case 2:
				w = 1;
				break;
			case 3:
				w = 2;
				break;
			default:
				w = 2;
				break;
			}
			
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) {
				return ( ret );
			}
			break;
#endif
		default:
			break;
		}
		set_no++;
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/12/26 Y.Matsukuma */
		if (CMN_CheckCategory2()) { /* F-101 */
			prm_kind = List_ParameterTable_Category2[set_no];
		}
		else {
			prm_kind = List_ParameterTable[set_no];
		}
#endif
	}
	if ( (ret = Print_Parameter_Head( 3, &line_dot ) ) != OK ) {	/*Ì¯Àˆóü*/
		return ( ret );
	}


	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	return( OK );
}

/*************************************************************************
	module		:[‹@ŠíÝ’èƒŠƒXƒgƒwƒbƒ_ˆóü]
	functiom	:[‹@ŠíÝ’èƒŠƒXƒg‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
	common		:[
		List	:
	]
	condition	:[
		Í¯ÀÞŽí—Þ
			0->Íß°¼Þæ“ªŒ©o‚µ
			1->–¾×o—Í’†
			2->–¾×o—Í’†(sŠÔ–³‚µ)
			3->Íß°¼Þ´ÝÄÞŒ©o‚µ
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/04/20]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
/* ‰üƒy[ƒWˆ——p‚É’Ç‰Á by K.Watanabe 1998/02/19 */
static UBYTE	list_attribute[LST_COLUM];

WORD				Print_Parameter_Head(
						 UBYTE Category,			/*ƒwƒbƒ_Ží—Þ*/
						 UWORD *LineDot)			/*Žc‚èƒ‰ƒCƒ“ƒhƒbƒg”*/
{

	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
	UBYTE	w;						/*Ü°¸*/
#endif
#if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1997/06/26 */
	UBYTE	board;		/* ƒIƒvƒVƒ‡ƒ“ƒ{[ƒh•Ï” */
	UBYTE	set_line;	/* ƒ‰ƒCƒ“” 1998/03/03 Add By M.Kuwahara */

	set_line	= 1;
#endif

	switch( Category ){
	case	0:
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}

#if (PRO_MULTI_LINE == DISABLE)	/*  By O.Kimoto 1997/06/26 */
		*LineDot = (UWORD)((PaperSizeLen() * 16) - (11 * 16));/*ˆóü‰Â”\s”¾¯Ä*/
#else
		board = OPT_CountModems();

#if (0)	/* Œ³‚É–ß‚µ‚Ü‚· by T.Soneoka 1998/03/10 */
#if (0)
** /* ‰º‹Lˆ—‚ÍAOPT_CountModems()“à‚Åˆ—‚·‚é‚±‚Æ‚É•ÏX‚µ‚Ü‚µ‚½‚Ì‚ÅA•s—v‚Å‚·B
**  #if (PRO_LINENUMBER == TWICE_LINE)	/* Add By O.Kimoto 1997/12/19 */
** 		board += 1;
**  #endif
#endif
#else
 #if (PRO_LINENUMBER == TWICE_LINE)	/* Add By O.Kimoto 1997/12/19 */
		board += 1;
 #endif
#endif

 #if (0)
 **		/* ŒvŽZŽ®‚ªŠÔˆá‚¦‚Ä‚¢‚éB By O.Kimoto 1998/01/08 */
 **		*LineDot = (UWORD)((PaperSizeLen() * 16) - ((11 - board + 1) * 16));/*ˆóü‰Â”\s”¾¯Ä*/
 #else
		*LineDot = (UWORD)((PaperSizeLen() * 16) - ((11 + board - 1) * 16));/*ˆóü‰Â”\s”¾¯Ä*/
 #endif
#endif
		/*”­MŒ³–¼{”­MŒ³”Ô†*/ /* TTI’Ç‰Á(ˆÈ‰º17s) for anzu  By H.Hirao Mar,15.1996 */
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );

/* ‚o‚n‚o‚k‚`‚qQ‚g •W€‚Q‰ñüŽû—e‘Î‰ž‚Ìˆ× By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
		CMN_StringCopy( &List.S.Print[1-1], &SYB_TTI_Buffer[0][0]);
		if ( SYB_ID_Buffer[0][0] != NULL ) {
			AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD, LST_NOT );
			CMN_StringCopy( &List.S.Print[28-1], &SYB_ID_Buffer[0][0]);
		}
#else
		CMN_StringCopy( &List.S.Print[1-1], SYB_TTI_Buffer);
		if ( SYB_ID_Buffer[0] != NULL ) {
			AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD, LST_NOT );
			CMN_StringCopy( &List.S.Print[28-1], SYB_ID_Buffer);
		}
#endif

		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		} /* ‚±‚±‚Ü‚Å’Ç‰Á for anzu */

		/*––@ƒLƒLƒZƒbƒeƒCƒŠƒXƒg@––*/
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) 	/* 1998/03/03 By M.Kuwahara */
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		AttributeSet( &List.S.Print[21-1], &List.S.Attribute[21-1], PWRD_MachineSettings_K, LST_NOT );
 #else
		AttributeSet( &List.S.Print[21-1], &List.S.Attribute[21-1], PWRD_MachineSettings, LST_XXX_TWI_XXX );
 #endif
#else
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		AttributeSet( &List.S.Print[19-1], &List.S.Attribute[19-1], PWRD_MachineSettings_K, LST_NOT );
 #else
		AttributeSet( &List.S.Print[19-1], &List.S.Attribute[19-1], PWRD_MachineSettings, LST_XXX_TWI_XXX );
 #endif
#endif
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*†®†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†¢†²*/
		Machine_Setting_Line( 4, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

#if (PRO_MULTI_LINE == DISABLE)	/* Add By O.Kimoto 1997/06/26 */
		/*†¤Ê¯¼ÝÓÄÒ²†¤xxxx†¤Ì§¸½ÊÞÝºÞ³†¤xxxxxx†¤*/
		Machine_Setting_Line( 5, List.S.Print, List.S.Attribute );
 #if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) 	/* 1998/03/10 By M.Kuwahara */
		AttributeSet( &List.S.Print[6-1], &List.S.Attribute[6-1], PWRD_SubscriberID, LST_NOT );
		CMN_StringCopy( &List.S.Print[21-1], SYB_TTI_Buffer );
		AttributeSet( &List.S.Print[44-1], &List.S.Attribute[44-1], PWRD_SubscriberNb, LST_NOT );
		CMN_StringCopy( &List.S.Print[60-1], SYB_ID_Buffer );
 #else
		AttributeSet( &List.S.Print[8-1], &List.S.Attribute[8-1], PWRD_SubscriberID, LST_NOT );
		CMN_StringCopy( &List.S.Print[19-1], SYB_TTI_Buffer );
		AttributeSet( &List.S.Print[42-1], &List.S.Attribute[42-1], PWRD_SubscriberNb, LST_NOT );
		CMN_StringCopy( &List.S.Print[55-1], SYB_ID_Buffer );
 #endif
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
		for (w = 1; w <= SYS_MULTI_MAX; w++) {
			Machine_Setting_Line( 5, List.S.Print, List.S.Attribute );
  #if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
			List.S.Print[17-1]	= '(';
			List.S.Print[18-1]	= '0' + w;
			List.S.Print[19-1]	= ')';
			CMN_StringCopy( &List.S.Print[21-1], SYB_Multi_TTI_Buffer[w-1] );
			List.S.Print[56-1]	= '(';
			List.S.Print[57-1]	= '0' + w;
			List.S.Print[58-1]	= ')';
			CMN_StringCopy( &List.S.Print[60-1], SYB_Multi_ID_Buffer[w-1] );
  #else
			List.S.Print[15-1]	= '(';
			List.S.Print[16-1]	= '0' + w;
			List.S.Print[17-1]	= ')';
			CMN_StringCopy( &List.S.Print[19-1], SYB_Multi_TTI_Buffer[w-1] );
			List.S.Print[51-1]	= '(';
			List.S.Print[52-1]	= '0' + w;
			List.S.Print[53-1]	= ')';
			CMN_StringCopy( &List.S.Print[55-1], SYB_Multi_ID_Buffer[w-1] );
  #endif
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			*LineDot -= 16;
		}
 #endif
		Machine_Setting_Line( 6, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
#else
 /* ‚o‚n‚o‚k‚`‚qQ‚g •W€‚Q‰ñüŽû—e‘Î‰ž‚Ìˆ× By O.Kimoto 1997/11/01 */
 #if (PRO_LINENUMBER == TWICE_LINE)
		for (board = 0; board <= 1; board++) {
			Machine_Setting_Line( 5, List.S.Print, List.S.Attribute );
			if (set_line == 1) {			/* ‚Q‰ñüˆÈã‚ÌŽž‚Í‰ñü”Ô†‚Ì‚Ý */
				AttributeSet( &List.S.Print[6-1], &List.S.Attribute[6-1], PWRD_SubscriberID, LST_NOT );
				AttributeSet( &List.S.Print[44-1], &List.S.Attribute[44-1], PWRD_SubscriberNb, LST_NOT );
			}
			CMN_StringCopy( &List.S.Print[21-1], &SYB_TTI_Buffer[board][0] );
			CMN_StringCopy( &List.S.Print[60-1], &SYB_ID_Buffer[board][0] );
			AttributeSet( &List.S.Print[16-1], &List.S.Attribute[16-1],&PWRD_LineName[(set_line - 1)][0], LST_NOT );
			AttributeSet( &List.S.Print[55-1], &List.S.Attribute[55-1],&PWRD_LineName[(set_line - 1)][0], LST_NOT );
			set_line++;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
 #else
		Machine_Setting_Line( 5, List.S.Print, List.S.Attribute );
  #if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) 	/* 1998/03/10 By M.Kuwahara */
		AttributeSet( &List.S.Print[6-1], &List.S.Attribute[6-1], PWRD_SubscriberID, LST_NOT );
		CMN_StringCopy( &List.S.Print[21-1], SYB_TTI_Buffer );
		AttributeSet( &List.S.Print[44-1], &List.S.Attribute[44-1], PWRD_SubscriberNb, LST_NOT );
		CMN_StringCopy( &List.S.Print[60-1], SYB_ID_Buffer );
		if (board > 1) {			/* ‚Q‰ñüˆÈã‚Ì‚Æ‚«‚Í‰½‰ñü–Ú‚©‚ðo—Í */
			List.S.Print[17-1]	= '(';
			List.S.Print[18-1]	= '0' + set_line;
			List.S.Print[19-1]	= ')';
			List.S.Print[56-1]	= '(';
			List.S.Print[57-1]	= '0' + set_line;
			List.S.Print[58-1]	= ')';
			set_line++;
		}
  #else
		AttributeSet( &List.S.Print[8-1], &List.S.Attribute[8-1], PWRD_SubscriberID, LST_NOT );
		CMN_StringCopy( &List.S.Print[19-1], SYB_TTI_Buffer );
		AttributeSet( &List.S.Print[42-1], &List.S.Attribute[42-1], PWRD_SubscriberNb, LST_NOT );
		CMN_StringCopy( &List.S.Print[55-1], SYB_ID_Buffer );
  #endif
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
 #endif

		for (board = 1; board <= SYS_OPTION_BOARD_MAX - 1; board++) {
			if (CHK_OptionLineExist(board) == 1) {
				Machine_Setting_Line( 5, List.S.Print, List.S.Attribute );
#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) 	/* 1998/03/010 By M.Kuwahara */
#if (0)		/* ‚Q‰ñüˆÈã‚ÌŽž‚Í‰ñü”Ô†‚Ì‚Ý */
//				AttributeSet( &List.S.Print[8-1], &List.S.Attribute[8-1], PWRD_SubscriberID, LST_NOT );
//				AttributeSet( &List.S.Print[44-1], &List.S.Attribute[44-1], PWRD_SubscriberNb, LST_NOT );
#endif
				CMN_StringCopy( &List.S.Print[21-1], SYB_Option_TTI_Buffer[board] );
				CMN_StringCopy( &List.S.Print[60-1], SYB_Option_ID_Buffer[board] );

 #if ( PRO_PANEL == KANJI )
				/* ‹@ŠíÝ’èƒŠƒXƒg‚Ìã’i‚Ì˜g“à‚Éƒ‰ƒxƒ‹’Ç‰Á
				** ‚½‚¾‚µAŒ…”‚ÌŠÖŒW‚ÅAŠO•t‚¯‚Q‰ñüˆÈã‚Å‚àƒ‰ƒxƒ‹‚É‚Í”Ô†‚ÍˆóŽš‚³‚ê‚Ü‚¹‚ñB
				** By O.Kimoto 1998/03/12
				*/
				AttributeSet( &List.S.Print[16-1], &List.S.Attribute[16-1],&PWRD_LineName[2][0], LST_NOT );
				AttributeSet( &List.S.Print[55-1], &List.S.Attribute[55-1],&PWRD_LineName[2][0], LST_NOT );
 #else
				List.S.Print[17-1]	= '(';
				List.S.Print[18-1]	= '0' + set_line;
				List.S.Print[19-1]	= ')';
				List.S.Print[56-1]	= '(';
				List.S.Print[57-1]	= '0' + set_line;
				List.S.Print[58-1]	= ')';
 #endif
				set_line++;
#else
				AttributeSet( &List.S.Print[8-1], &List.S.Attribute[8-1], PWRD_SubscriberID, LST_NOT );
				CMN_StringCopy( &List.S.Print[19-1], SYB_Option_TTI_Buffer[board] );
				AttributeSet( &List.S.Print[42-1], &List.S.Attribute[42-1], PWRD_SubscriberNb, LST_NOT );
				CMN_StringCopy( &List.S.Print[55-1], SYB_Option_ID_Buffer[board] );
#endif
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
			}
		}
 #if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
		for (w = 1; w <= SYS_MULTI_MAX; w++) {
			Machine_Setting_Line( 5, List.S.Print, List.S.Attribute );
  #if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
			List.S.Print[17-1]	= '(';
			List.S.Print[18-1]	= '0' + w;
			List.S.Print[19-1]	= ')';
			CMN_StringCopy( &List.S.Print[21-1], SYB_Multi_TTI_Buffer[w-1] );
			List.S.Print[56-1]	= '(';
			List.S.Print[57-1]	= '0' + w;
			List.S.Print[58-1]	= ')';
			CMN_StringCopy( &List.S.Print[60-1], SYB_Multi_ID_Buffer[w-1] );
  #else
			List.S.Print[15-1]	= '(';
			List.S.Print[16-1]	= '0' + w;
			List.S.Print[17-1]	= ')';
			CMN_StringCopy( &List.S.Print[19-1], SYB_Multi_TTI_Buffer[w-1] );
			List.S.Print[51-1]	= '(';
			List.S.Print[52-1]	= '0' + w;
			List.S.Print[53-1]	= ')';
			CMN_StringCopy( &List.S.Print[55-1], SYB_Multi_ID_Buffer[w-1] );
  #endif
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			*LineDot -= 16;
		}
 #endif
		Machine_Setting_Line( 6, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
#endif
		/*DRAMÒÓØ@Œ»ÝŽžŠÔ*/
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		MemoryEmptyBkString( List.S.Work );
		CMN_StringCopy( &List.S.Print[8-1], List.S.Work );
		TimeDataAscii( OFF, SYB_CurrentTime, List.S.Work, 0 );
#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) 	/* 1998/03/10 By M.Kuwahara */
		CMN_StringCopy( &List.S.Print[59-1], List.S.Work );
#else
		CMN_StringCopy( &List.S.Print[55-1], List.S.Work );
#endif
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*†®†¢†¢†Î†¢†¢†¢†¢†¢†²*/
		Machine_Setting_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		break;
	case	1:				/* o—Í’† */
		/* Œ³X‚ÍA‚PsˆóŽš’¼Œã‚És”‚Ì”»’f‚¾‚¯‚ÅA‰üƒy[ƒW‚Ìˆ—‚ðs‚Á‚Ä‚¢‚½ˆ×‚ÉAŽŸƒy[ƒW‚É
		** ˆóŽš‚·‚é“à—e‚ª‚È‚¢Žž‚Å‚à‰üƒy[ƒW‚µ‚Ä‚µ‚Ü‚¢A‚Qƒy[ƒW–Ú‚ÍŒrü‚¾‚¯‚É‚È‚Á‚Ä‚¢‚½‚Ì‚ÅA
		** ‰üƒy[ƒW‚Ì”»’f‚ð–¾×ˆóŽš‘O‚ÉˆÚ“®‚µ‚Ü‚µ‚½ by K.Watanabe 1998/02/19
		*/
		if ((*LineDot - (UWORD)(16 + LST_PRM_SPACE)) <= 0) {
			/* –¾×‚Ì“à—e‚ð‘Ò”ð‚µ‚Ü‚· by K.Watanabe 1998/02/19 */
			CMN_StringCopyNum(List.S.Work, List.S.Print, LST_COLUM);
			CMN_StringCopyNum(list_attribute, List.S.Attribute, LST_COLUM);

			/*†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢*/	/* ƒy[ƒWI—¹ */
			Machine_Setting_Line( 3, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/* ‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED + 1 )) != OK ) {
				return ( ret );
			}
			if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
				return ( ret );
			}
			if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {				/* ŽŸƒy[ƒWŠJŽn */
				return ( ret );
			}
			*LineDot = (UWORD)((PaperSizeLen() * 16) - (4 * 16));			/* ˆóü‰Â”\s”ƒZƒbƒg */

			/* ‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}

			/*†®†¢†¢†Î†¢†¢†¢†¢†¢†²*/
			Machine_Setting_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/* –¾×‚Ì“à—e‚ð•œŒ³‚µ‚Ü‚· by K.Watanabe 1998/02/19 */
			CMN_StringCopyNum(List.S.Print, List.S.Work, LST_COLUM);
			CMN_StringCopyNum(List.S.Attribute, list_attribute, LST_COLUM);
		}

		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		if ( (ret = Machine_Setting_Middle()) != OK ) {
			return ( ret );
		}
		*LineDot -= 16 + LST_PRM_SPACE;
		break;
	case	2:				/* o—Í’†(sŠÔ–³‚µ) */
		/* Œ³X‚ÍA‚PsˆóŽš’¼Œã‚És”‚Ì”»’f‚¾‚¯‚ÅA‰üƒy[ƒW‚Ìˆ—‚ðs‚Á‚Ä‚¢‚½ˆ×‚ÉAŽŸƒy[ƒW‚É
		** ˆóŽš‚·‚é“à—e‚ª‚È‚¢Žž‚Å‚à‰üƒy[ƒW‚µ‚Ä‚µ‚Ü‚¢A‚Qƒy[ƒW–Ú‚ÍŒrü‚¾‚¯‚É‚È‚Á‚Ä‚¢‚½‚Ì‚ÅA
		** ‰üƒy[ƒW‚Ì”»’f‚ð–¾×ˆóŽš‘O‚ÉˆÚ“®‚µ‚Ü‚µ‚½ by K.Watanabe 1998/02/19
		*/
		if ((*LineDot - 16) <= 0) {
			/* –¾×‚Ì“à—e‚ð‘Ò”ð‚µ‚Ü‚· by K.Watanabe 1998/02/19 */
			CMN_StringCopyNum(List.S.Work, List.S.Print, LST_COLUM);
			CMN_StringCopyNum(list_attribute, List.S.Attribute, LST_COLUM);

			/*†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢*/	/* ƒy[ƒWI—¹ */
			Machine_Setting_Line( 3, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/* ‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED + 1 )) != OK ) {
				return ( ret );
			}
			if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
				return ( ret );
			}
			if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {				/* ŽŸƒy[ƒWŠJŽn */
				return ( ret );
			}
			*LineDot = (UWORD)((PaperSizeLen() * 16) - (4 * 16));			/* ˆóü‰Â”\s”ƒZƒbƒg */

			/* ‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}

			/*†®†¢†¢†Î†¢†¢†¢†¢†¢†²*/
			Machine_Setting_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/* –¾×‚Ì“à—e‚ð•œŒ³‚µ‚Ü‚· by K.Watanabe 1998/02/19 */
			CMN_StringCopyNum(List.S.Print, List.S.Work, LST_COLUM);
			CMN_StringCopyNum(List.S.Attribute, list_attribute, LST_COLUM);
		}

		if ( (ret = CharacterPrint( LST_PRINT )) != OK) {
			return ( ret );
		}
		*LineDot -= 16;
		break;
	case	3:				/* o—ÍI—¹ */
		/*†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢*/
		Machine_Setting_Line( 3, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED + 1 )) != OK ) {
			return ( ret );
		}
		break;
	}
	return( OK );
}

/*@-s**************************************************************************
**@-1	RS232CÝ’èˆóü
**@-2	RS232C‚ÌÝ’è‚ðˆóü‚·‚é
**@-3	Machine_Setting_RS232C()
**@-4	void
**@-5	WORD		ŽÀsŒ‹‰Ê
**@-6	RS232C‚ÉÝ’èˆóü‚ª‚QƒJŠ‚ ‚é‚½‚ßA‚±‚Ì•”•ª‚Ì‚ÝŠÖ”‚Æ‚µ‚Ä‚¢‚éB
**@-e*************************************************************************/
#if (PRO_CLASS1 == ENABLE)	/**	By H.H 1996/09/17 */
WORD	Machine_Setting_RS232C(UWORD *LineDot)  /* ƒ‰ƒCƒ“ƒhƒbƒg‚ðˆø”‚Æ‚·‚é S.Fukui Sep.17,1997 */
{
	UBYTE			w;					/*Ü°¸*/
/*	UWORD			line_dot;   */
	register WORD	ret;				/*ŽÀsŒ‹‰Ê*/
	UBYTE			*w_pt[8] = {0};		/*‘I‘ð€–Ú•¶Žš—ñ*/

	/*†¤RS232C	ÎÞ°Ú°Ä†¤XXXXXX†¤*/
	Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_Rs232c, LST_NOT );
/*	w_pt[0] = (UBYTE *)&PWRD_Bps300;	/* ’¼Ú Variable ƒZƒbƒg 1997/03/05 M.Kuwahara */
	w_pt[0] = (UBYTE *)&PWRD_BpsVariable;
	w_pt[1] = (UBYTE *)&PWRD_Bps600;
	w_pt[2] = (UBYTE *)&PWRD_Bps1200;
	w_pt[3] = (UBYTE *)&PWRD_Bps2400;
	w_pt[4] = (UBYTE *)&PWRD_Bps4800;
	w_pt[5] = (UBYTE *)&PWRD_Bps9600;
	w_pt[6] = (UBYTE *)&PWRD_Bps19200;
	w_pt[7] = NULL_PT;
	/* w = (UBYTE)(6 - (SYB_SettingStatus[5] &
	  (RS232C_SPEED_600+RS232C_SPEED_1200+RS232C_SPEED_4800))); */
	w = (UBYTE)(CHK_RS232C_Speed());	/** By H.H 1996/09/17	*/
/*	Param_set( &List.S.Print[33], &List.S.Attribute[33], w, 6, w_pt );/* 29 -> 33 By H.H 1996/09/17 */
	Param_set( &List.S.Print[30], &List.S.Attribute[30], w, 6, w_pt );/* 33 -> 32 By M.K 1997/03/05 */
	w_pt[1] = NULL_PT;								/* "Variable"‚Ì‚ÝƒZƒbƒg By M.Kuwahara 1997/03/05 */
	CMN_MemorySet( &List.S.Print[27], 8, ' ' );
	CMN_MemorySet( &List.S.Attribute[27], 8, ' ' );
	Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 9, w_pt );
	/**	Add By H.H 1996/09/17 ‚±‚±‚©‚ç	*/
#if 0	/* 97/03/05 M.Kuwahara */
** 	if ( w == 0 ) {	/** 300bps -> Variable	 */
** 		CMN_MemorySet( List.S.Work, (UWORD)LST_COLUM, 0 );
** 		LST_RemoveAscString1stSpace( List.S.Work, D2W_RS232CVariable );
** 		List.S.Work[8] = NULL;	/**	•¶Žš—ñ‚ÌÅŒã‚Éƒkƒ‹‚ð“ü‚ê‚é‚½‚ß	*/
** 		AttributeSet( &List.S.Print[28], &List.S.Attribute[28],
** 		  List.S.Work, LST_INV_XXX_XXX );
** 	}
** 	else {
** 		LST_RemoveAscString1stSpace( &List.S.Print[28], D2W_RS232CVariable );
** 	}
#endif
	/**	Add By H.H 1996/09/17 ‚±‚±‚Ü‚Å */

/*	if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) { */
	if ( (ret = Print_Parameter_Head( 1, LineDot ) ) != OK ) {  /* Modified by S.Fukui Sep.17,1997 */
		return ( ret );
	}

	/*†¤ÊßØÃ¨/½Ä¯Ìß/ÃÞ°À†¤XXXXXX†¤*/
	Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
	/* AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_Parity, LST_NOT ); */
	w_pt[0] = (UBYTE *)&PWRD_None;							/* For ANZU By H.Hirao Mar.05,1996 */
	w_pt[1] = (UBYTE *)&PWRD_Odd;
	w_pt[2] = (UBYTE *)&PWRD_Even;
	w_pt[3] = NULL_PT;
	/* w = (UBYTE)( (SYB_SettingStatus[5] &
	  (RS232C_PARITY_ODD+RS232C_PARITY_EVEN)) >> 4 ); */
	w = (UBYTE)(((UBYTE)(CHK_RS232C_Parity())) >> 4);	/**	By H.H 1996/09/17 */
	Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 6, w_pt );
	w_pt[0] = (UBYTE *)&PWRD_S1bit;
	w_pt[1] = (UBYTE *)&PWRD_S2bit;
	w_pt[2] = NULL_PT;
	/* w = (UBYTE)( (SYB_SettingStatus[5] & RS232C_STOP_LENGTH_2) >> 6 ); */
	/** By H.H 1996/09/17 ‚±‚±‚©‚ç	*/
	w = (UBYTE)(CHK_RS232C_StopLength2());
	if ( w == 0 ) {
		w = 0;
	}
	else {
		w = 1;
	}
	/**	By H.H 1996/09/17 ‚±‚±‚Ü‚Å	*/
	Param_set( &List.S.Print[45], &List.S.Attribute[45], w, 6, w_pt );
	w_pt[0] = (UBYTE *)&PWRD_P7bit;
	w_pt[1] = (UBYTE *)&PWRD_P8bit;
	w_pt[2] = NULL_PT;
	w = (UBYTE)( (SYB_SettingStatus[5] & RS232C_DATA_LENGTH_8) >> 3 );
	if ( w == 0 ) {
		/* w = 1; */
		w = 0;	/** By H.H 1996/09/17 */
	}
	else {
		/* w = 0; */
		w = 1;	/** By H.H 1996/09/17 */
	}
	Param_set( &List.S.Print[57], &List.S.Attribute[57], w, 6, w_pt );
/*			if ( (ret = Print_Parameter_Head( 1, &line_dot ) ) != OK ) { */
			if ( (ret = Print_Parameter_Head( 1, LineDot ) ) != OK ) {  /* Modified by S.Fukui Sep.17,1997 */
				return ( ret );
			}
	return ( OK );
}
#endif	/** PRO_CLASS1 == ENABLE By H.H 1996/09/17 */
/*************************************************************************
	module		:[ƒpƒ‰ƒ[ƒ^Ý’è]
	function	:[‹@ŠíÝ’èƒŠƒXƒg‚Ìƒpƒ‰ƒ[ƒ^‚ðÝ’è‚·‚é]
	common		:[]
	condition	:[]
	commment	:[
		€–Ú–¼ÌA€–ÚCüA‚É‚Ä€–Ú‚Ì•¶Žš—ñ‚ðì¬‚µAˆóü•¶Žš—ñACü•¶Žš—ñ‚É
		ƒZƒbƒg‚·‚éB€–Ú‚ÌŠÔŠu‚Í‚P€–Ú‚ÌŠÔŠu‚É‚ÄŽ¦‚³‚êA€–Ú”Ô†‚ÅŽ¦‚³‚ê‚é€–Ú
		‚ð–ÔŠ|‚¯‚Æ‚·‚éB
	]
	return		:[ˆóüŒ‹‰Ê‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/05/20]
	author		:[–L“c_Žq]
*************************************************************************/
#define	TOP_X	0
void				Param_set(
						 register UBYTE *Prn_Str,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *Att_Str,	/*Cü•¶Žš—ñ*/
						 UBYTE Status,				/*€–Ú”Ô†*/
						 UBYTE WideX,				/*‚P€–Ú‚ÌŠÔŠu*/
						 UBYTE *W_Pt[] )			/*€–Ú–¼Ì*/
{
	UBYTE	i;				/*loop*/
	UBYTE	attr;			/*Cü*/

	for ( i = 0; W_Pt[i] != NULL_PT && i < 8; i++ ) {
		if ( i == Status ) {
			attr = LST_INV_XXX_XXX;	/* –ÔŠ|‚¯‚ÍŒ©“ï‚¢‚Ì‚Å¤”½“]‚É‚µ‚½B 94.7.20 */
		}
		else {
			attr = LST_NOT;
		}
		AttributeSet( &Prn_Str[TOP_X+WideX*i-1],
		  &Att_Str[TOP_X+WideX*i-1], W_Pt[i], attr );
	}
}
#undef	TOP_X

/*************************************************************************
	module		:[‹@ŠíÝ’èƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrüì¬]
	function	:[‹@ŠíÝ’èƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
		,	0 = †®†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†²
		,	1 = †¤		  †¤		  †¤
		,	2 = †¾†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†Æ
		,	3 = †¶†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†º
		,	4 = †®†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†¢†²
		,	5 = †¤	  †¤	†¤	  †¤	  †¤
		,	6 = †¶†¢†¢†Ö†¢†¢†Ö†¢†¢†Ö†¢†¢†¢†º
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/05/20]
	author		:[–L“c_Žq]
*************************************************************************/
void				Machine_Setting_Line(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†²*/
#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) 	/* 1998/03/03 By M.Kuwahara */
			AscString[5-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[6-1], 74, LST_KLINE_ );
			AscString[25-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE9;
#else
			AscString[5-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[6-1], 71, LST_KLINE_ );
			AscString[25-1] = LST_KLINE8;
			AscString[77-1] = LST_KLINE9;
#endif
			break;
		case 1:
			/*†¤		†¤			†¤*/
			AscString[5-1] = LST_KLINEI;
			AscString[25-1] = LST_KLINEI;
#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) 	/* 1998/03/03 By M.Kuwahara */
			AscString[80-1] = LST_KLINEI;
#else
			AscString[77-1] = LST_KLINEI;
#endif
			break;
		/* case 2: */
			/*†¾†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†Æ*/
			/* AscString[7-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[6-1], 71, LST_KLINE_ );
			AscString[25-1] = LST_KLINE5;
			AscString[75-1] = LST_KLINE6;
			break; */ /* ‹æØ‚èü‚ð‚â‚ß‚é (ANZU) By H.Hirao Feb 28,1996 */
		case 3:
			/*†¶†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†º*/
#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) 	/* 1998/03/03 By M.Kuwahara */
			AscString[5-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[6-1], 74, LST_KLINE_ );
			AscString[25-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE3;
#else
			AscString[5-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[6-1], 71, LST_KLINE_ );
			AscString[25-1] = LST_KLINE2;
			AscString[77-1] = LST_KLINE3;
#endif
			break;
		case 4:
			/*†®†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†¢†²*/
#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) 	/* 1998/03/10 By M.Kuwahara */
			AscString[5-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[6-1], 74, LST_KLINE_ );
			AscString[20-1] = LST_KLINE8;
			AscString[43-1] = LST_KLINE8;
			AscString[59-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE9;
#else
			AscString[7-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[8-1], 67, LST_KLINE_ );
			AscString[18-1] = LST_KLINE8;
			AscString[41-1] = LST_KLINE8;
			AscString[54-1] = LST_KLINE8;
			AscString[75-1] = LST_KLINE9;
#endif
			break;
		case 5:
			/*†¤	†¤	  †¤	†¤		†¤*/
#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) 	/* 1998/03/10 By M.Kuwahara */
			AscString[5-1] = LST_KLINEI;
			AscString[20-1] = LST_KLINEI;
			AscString[43-1] = LST_KLINEI;
			AscString[59-1] = LST_KLINEI;
			AscString[80-1] = LST_KLINEI;
#else
			AscString[7-1] = LST_KLINEI;
			AscString[18-1] = LST_KLINEI;
			AscString[41-1] = LST_KLINEI;
			AscString[54-1] = LST_KLINEI;
			AscString[75-1] = LST_KLINEI;
#endif
			break;
		case 6:
			/*†¶†¢†¢†Ö†¢†¢†Ö†¢†¢†Ö†¢†¢†¢†º*/
#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) 	/* 1998/03/10 By M.Kuwahara */
			AscString[5-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[6-1], 74, LST_KLINE_ );
			AscString[20-1] = LST_KLINE2;
			AscString[43-1] = LST_KLINE2;
			AscString[59-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE3;
#else
			AscString[7-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[8-1], 67, LST_KLINE_ );
			AscString[18-1] = LST_KLINE2;
			AscString[41-1] = LST_KLINE2;
			AscString[54-1] = LST_KLINE2;
			AscString[75-1] = LST_KLINE3;
#endif
			break;
	}
}

/*************************************************************************
	module		:[‹@ŠíÝ’èƒŠƒXƒg‹æØ‚èüˆóü]
	function	:[‹@ŠíÝ’èƒŠƒXƒg‚Ì†¾†¢†¢†¢†Þ†¢†¢†¢†¢†Æ‚ðˆóü‚·‚é]
	common		:[]
	condition	:[]
	commment	:[
	              1.ƒƒ‚ƒŠß–ñ‚Ìˆ×

	              2.‹æØ‚èü‚ð‚â‚ß‚Ä‹ó”’‚Æc‚ÌŒrü‚Ì‚Ý‚É‚·‚é By H.Hirao Feb 19,1996
	              ]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/05/20]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Machine_Setting_Middle(
						 void )				/*‚È‚µ*/
{

	WORD			result;
	UBYTE	line;

	CMN_WordMemorySet((UWORD *)&FontImageBuffer.ByteImage[0][0], (LST_PRM_SPACE * 40), 0); /** ƒCƒjƒVƒƒƒ‰ƒCƒY */

	for (line = 0; line < LST_PRM_SPACE; line++) { /* cŒrü‚ð•`‚­ */
#if (0)	/* By M.Tachibana 1996/12/25 */
**		CMN_WordMemorySet( &FontImageBuffer.ByteImage[line][3], 1, 0x0008);
**		CMN_WordMemorySet( &FontImageBuffer.ByteImage[line][13], 1, 0x0008);
**		CMN_WordMemorySet( &FontImageBuffer.ByteImage[line][37], 1, 0x0008);
#endif
#if (PRO_CPU == SH7043)
#if (0)	/* 97/03/22 */
**		FontImageBuffer.ByteImage[line][3] = 0x0800;
**		FontImageBuffer.ByteImage[line][13] = 0x0800;
**		FontImageBuffer.ByteImage[line][37] = 0x0800;
#endif
		FontImageBuffer.ByteImage[line][2] = 0x0800;
		FontImageBuffer.ByteImage[line][12] = 0x0800;
 #if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) 	/* 1998/03/03 By M.Kuwahara */
		FontImageBuffer.ByteImage[line][39] = 0x0008;
 #else
		FontImageBuffer.ByteImage[line][38] = 0x0800;
 #endif
#endif
	}
	result = ListSpacePrint();
	return (result);
}


/** #if (PRO_MULTI_LINE == ENABLE) */
/*************************************************************************
	module		:[‹@ŠíÝ’èƒŠƒXƒgi‚Q‰ñüê—p•”•ª‚Ì‚Ýj]
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
	ProtoType	:[WORD Print_MultiParameter(UWORD){}]
	date		:[1997/07/11]
	author		:[–ØŒ³C]
*************************************************************************/
WORD Print_MultiParameter(UWORD *LineDot)			/*Žc‚èƒ‰ƒCƒ“ƒhƒbƒg”*/
{
#if (PRO_LINENUMBER == TWICE_LINE)
	WORD ret;
	UBYTE i,j;
	UBYTE set_line;
	UBYTE line_chk;
	UBYTE w;
	UBYTE	*w_pt[8] = {0};			/*‘I‘ð€–Ú•¶Žš—ñ*/

	line_chk = 0;
	ret = OK;

	/* for (i = 0; i < SYS_OPTION_BOARD_MAX; i++)  */
	i = 0;
	j = 0;
	while (i < SYS_OPTION_BOARD_MAX) {
		if ((i == 0) || ((i != 0) && ((set_line = OPT_GetMultiLinrNumber(i)) != line_chk))) {

			if (i != 0) {
				line_chk = set_line;	/* ŽŸ‚Éƒ`ƒFƒbƒN‚·‚é‚½‚ß‘Ò”ð */
			}
			else {
				set_line = 1;
				line_chk = set_line;	/* ŽŸ‚Éƒ`ƒFƒbƒN‚·‚é‚½‚ß‘Ò”ð */
			}

			/* ‰ñü”Ô† */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1],PWRD_LineNumber, LST_NOT );

			if (i == 0) {
				AttributeSet( &List.S.Print[19-1], &List.S.Attribute[19-1],&PWRD_LineName[j][0], LST_NOT );
			}
			else {
				AttributeSet( &List.S.Print[19-1], &List.S.Attribute[19-1],&PWRD_LineName[2][0], LST_NOT );
			}

			if ( (ret = Print_Parameter_Head( 1, LineDot ) ) != OK ) {
				return ( ret );
			}

 #if (PRO_PANEL == KANJI) || ( PRO_JIS_CODE == ENABLE ) /* add 1997/09/16 Y.Matsukuma */
			/* ”­iŒ³–¼(¶ÅID) */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[9-1], &List.S.Attribute[9-1],PWRD_SubscriberKanaID, LST_NOT );
			if (i == 0) {
				CMN_StringCopy( &List.S.Print[27-1], &SYB_TTI_ID_Buffer[j][0] );
			}
			else {
				CMN_StringCopy( &List.S.Print[27-1], SYB_Option_TTI_ID_Buffer[i] );
			}
			if ( (ret = Print_Parameter_Head( 1, LineDot ) ) != OK ) {
				return ( ret );
			}
 #endif

			/* ’ÊM‰ñü */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet(&List.S.Print[9-1], &List.S.Attribute[9-1],PWRD_PhoneType, LST_NOT );
			if (i == 0) {
				w = (UBYTE)CHK_MultiPhoneType((UBYTE)(j * 0x10));
			}
			else {
				w = (UBYTE)CHK_MultiPhoneType(i);
			}
 #if defined(JPN)
			w_pt[0] = (UBYTE *)&PWRD_ToneLine;
			w_pt[1] = (UBYTE *)&PWRD_Pps10;
			w_pt[2] = (UBYTE *)&PWRD_Pps20;
			w_pt[3] = NULL_PT;
			switch ( w ) {
			case DIAL_SPEED_10PPS:
				w = 1;
				break;
			case DIAL_SPEED_20PPS:
			case DIAL_SPEED_20PPS_1:	/* 97/09/24 Add By M.Kuwahara */
			case DIAL_SPEED_20PPS_2:
			case DIAL_SPEED_20PPS_EXT:
				w = 2;
				break;
			case LINE_TYPE_TONE:
			case LINE_TYPE_TONE_1:
			case LINE_TYPE_TONE_2:
			case LINE_TYPE_TONE_EXT:
				w = 0;
				break;
			}
 #else
  #if defined(FRA)	/* add by M.HARADA '97.1/17 */
			w_pt[0] = (UBYTE *)&PWRD_ToneLine;
			w_pt[1] = NULL_PT;
			w = 0;
  #else
   #if defined(EC1) || defined(EUR)	/* for DNK 97/05/06 by M.H. */
	#if defined(EUR)	/* ‰¢BŽd—l’Ç‰Á by M.H 1999/09/15 */
			if(CHK_DP_Enable()) {	/* DP‚Ì—LŒø/–³Œø‚ÅØ‚è•ª‚¯‚é 1999/12/20 by M.Harada */
				w_pt[0] = (UBYTE *)&PWRD_ToneLine;
				w_pt[1] = (UBYTE *)&PWRD_Pps10;
				w_pt[2] = NULL_PT;
				if (w != 0) {
					w = 0;
				}
				else {
					w = 1;
				}
			}else{
				w_pt[0] = (UBYTE *)&PWRD_ToneLine;
				w_pt[1] = NULL_PT;
				w = 0;
			}
	#else
			if(SYS_MachineParameter[0] != 7){
				w_pt[0] = (UBYTE *)&PWRD_ToneLine;
				w_pt[1] = (UBYTE *)&PWRD_Pps10;
				w_pt[2] = NULL_PT;
				if (w != 0) {
					w = 0;
				}
				else {
					w = 1;
				}
			}else{
				w_pt[0] = (UBYTE *)&PWRD_ToneLine;
				w_pt[1] = NULL_PT;
				w = 0;
			}
	#endif
   #else
			w_pt[0] = (UBYTE *)&PWRD_ToneLine;
			w_pt[1] = (UBYTE *)&PWRD_Pps10;
			w_pt[2] = NULL_PT;
			if (w != 0) {
				w = 0;
			}
			else {
				w = 1;
			}
   #endif
  #endif
 #endif
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, LineDot ) ) != OK ) {
				return ( ret );
			}

			/* ‘—M¥ŽóM */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[9-1], &List.S.Attribute[9-1],PWRD_MultiTxRxType, LST_NOT );

			if (i == 0) {
				w = (UBYTE)CHK_MultiTxRxType((UBYTE)(j * 0x10));
			}
			else {
				w = (UBYTE)CHK_MultiTxRxType(i);
			}

			w_pt[0] = (UBYTE *)&PWRD_TxRx;
			w_pt[1] = (UBYTE *)&PWRD_Tx;
			w_pt[2] = (UBYTE *)&PWRD_Rx;
			w_pt[3] = NULL_PT;
			switch ( w ) {
			case 0:
				w = 0;
				break;
			case 1:
				w = 1;
				break;
			case 2:
				w = 2;
				break;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, LineDot ) ) != OK ) {
				return ( ret );
			}

			/* ŠOü¥“àüÝ’è */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[9-1], &List.S.Attribute[9-1],PWRD_MultiLineType, LST_NOT );

			if (i == 0) {
				w = (UBYTE)CHK_MultiLineType((UBYTE)(j * 0x10));
			}
			else {
				w = (UBYTE)CHK_MultiLineType(i);
			}

			w_pt[0] = (UBYTE *)&PWRD_PstnLine;
			w_pt[1] = (UBYTE *)&PWRD_PbxLine;
			w_pt[2] = NULL_PT;
			if (w != 0) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );

			if (w == 1) {
			    /* ƒAƒNƒZƒX”Ô†ˆóŽš */
#if (0)	/* ƒ[ƒfƒBƒ“ƒOŠJŽnˆÊ’u‚ª‚QƒoƒCƒg‘O‚É‚¸‚ê‚Ä‚¢‚½‚Ì‚Å’¼‚µ‚Ü‚· by K.Watanabe 1998/02/18 */
//				AttributeSet( &List.S.Print[45-1], &List.S.Attribute[45-1],PWRD_PstnAccessNumber, LST_NOT );
#endif
				AttributeSet( &List.S.Print[47-1], &List.S.Attribute[47-1], PWRD_PstnAccessNumber, LST_NOT );

				if (i == 0) {
					CMN_BCD_ToASC_StringNum(&List.S.Print[64-1],SYB_PbxAccessNumber[i][j], 10);
				}
				else {
					CMN_BCD_ToASC_StringNum(&List.S.Print[64-1],SYB_PbxAccessNumber[i][0], 10);
				}
			}
			if ( (ret = Print_Parameter_Head( 1, LineDot ) ) != OK ) {
				return ( ret );
			}
		}

		if (i == 0) {
			if (j == 0) {
				j ++;
			}
			else {
				i ++;
				j = 0;
			}
		}
		else {
			i ++;
		}
	}
	return(ret);
#else
	WORD ret;
	UBYTE i;
	UBYTE set_line;
	UBYTE line_chk;
	UBYTE w;
	UBYTE	*w_pt[8] = {0};			/*‘I‘ð€–Ú•¶Žš—ñ*/

	line_chk = 0;
	ret = OK;

	for (i = 0; i < SYS_OPTION_BOARD_MAX; i++) {
		if ((set_line = OPT_GetMultiLinrNumber(i)) != line_chk) {
			line_chk = set_line;	/* ŽŸ‚Éƒ`ƒFƒbƒN‚·‚é‚½‚ß‘Ò”ð */

			/* ‰ñü”Ô† */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1],PWRD_LineNumber, LST_NOT );

			/* [15-1]‚©‚çˆóŽš‚ð[19-1]‚É•ÏX 1998/01/09 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) 	/* 1998/03/03 By M.Kuwahara */
			List.S.Print[18-1] = '(';
			List.S.Print[19-1] = (UBYTE)('0'+ set_line); /* •ÏX 1997/09/17 Y.Matsukuma */
			List.S.Print[20-1] = ')';
#else
			List.S.Print[19-1] = '(';
			List.S.Print[20-1] = (UBYTE)('0'+ set_line); /* •ÏX 1997/09/17 Y.Matsukuma */
			List.S.Print[21-1] = ')';
#endif
			if ( (ret = Print_Parameter_Head( 1, LineDot ) ) != OK ) {
				return ( ret );
			}

 #if (PRO_PANEL == KANJI) || ( PRO_JIS_CODE == ENABLE ) /* add 1997/09/16 Y.Matsukuma */
			/* ”­iŒ³–¼(¶ÅID) */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[9-1], &List.S.Attribute[9-1],PWRD_SubscriberKanaID, LST_NOT );
			if (i == 0) {
				CMN_StringCopy( &List.S.Print[27-1], SYB_TTI_ID_Buffer );
			}
			else {
				CMN_StringCopy( &List.S.Print[27-1], SYB_Option_TTI_ID_Buffer[i] );
			}
			if ( (ret = Print_Parameter_Head( 1, LineDot ) ) != OK ) {
				return ( ret );
			}
 #endif

			/* ’ÊM‰ñü */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet(&List.S.Print[9-1], &List.S.Attribute[9-1],PWRD_PhoneType, LST_NOT );
			w = (UBYTE)CHK_MultiPhoneType(i);
 #if defined(JPN)
			w_pt[0] = (UBYTE *)&PWRD_ToneLine;
			w_pt[1] = (UBYTE *)&PWRD_Pps10;
			w_pt[2] = (UBYTE *)&PWRD_Pps20;
			w_pt[3] = NULL_PT;
			switch ( w ) {
			case DIAL_SPEED_10PPS:
				w = 1;
				break;
			case DIAL_SPEED_20PPS:
			case DIAL_SPEED_20PPS_1:	/* 97/09/24 Add By M.Kuwahara */
			case DIAL_SPEED_20PPS_2:
				w = 2;
				break;
			case LINE_TYPE_TONE:
			case LINE_TYPE_TONE_1:
			case LINE_TYPE_TONE_2:
				w = 0;
				break;
			}
 #else
  #if defined(FRA)	/* add by M.HARADA '97.1/17 */
			w_pt[0] = (UBYTE *)&PWRD_ToneLine;
			w_pt[1] = NULL_PT;
			w = 0;
  #else
   #if defined(EC1) || defined(EUR)	/* for DNK 97/05/06 by M.H. */
	#if defined(EUR)	/* ‰¢BŽd—l’Ç‰Á by M.H 1999/09/15 */
			if(CHK_DP_Enable()) {	/* DP‚Ì—LŒø/–³Œø‚ÅØ‚è•ª‚¯‚é 1999/12/20 by M.Harada */
				w_pt[0] = (UBYTE *)&PWRD_ToneLine;
				w_pt[1] = (UBYTE *)&PWRD_Pps10;
				w_pt[2] = NULL_PT;
				if (w != 0) {
					w = 0;
				}
				else {
					w = 1;
				}
			}else{
				w_pt[0] = (UBYTE *)&PWRD_ToneLine;
				w_pt[1] = NULL_PT;
				w = 0;
			}
	#else
			if(SYB_MachineParameter[0] != 4 &&
			   SYB_MachineParameter[0] != 5 &&
			   SYB_MachineParameter[0] != 6 &&
			   SYB_MachineParameter[0] != 7){
				w_pt[0] = (UBYTE *)&PWRD_ToneLine;
				w_pt[1] = (UBYTE *)&PWRD_Pps10;
				w_pt[2] = NULL_PT;
				if (w != 0) {
					w = 0;
				}
				else {
					w = 1;
				}
			}else{
				w_pt[0] = (UBYTE *)&PWRD_ToneLine;
				w_pt[1] = NULL_PT;
				w = 0;
			}
	#endif
   #else
			w_pt[0] = (UBYTE *)&PWRD_ToneLine;
			w_pt[1] = (UBYTE *)&PWRD_Pps10;
			w_pt[2] = NULL_PT;
			if (w != 0) {
				w = 0;
			}
			else {
				w = 1;
			}
   #endif
  #endif
 #endif
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, LineDot ) ) != OK ) {
				return ( ret );
			}

			/* ‘—M¥ŽóM */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[9-1], &List.S.Attribute[9-1],PWRD_MultiTxRxType, LST_NOT );
			w = (UBYTE)CHK_MultiTxRxType(i);

			w_pt[0] = (UBYTE *)&PWRD_TxRx;
			w_pt[1] = (UBYTE *)&PWRD_Tx;
			w_pt[2] = (UBYTE *)&PWRD_Rx;
			w_pt[3] = NULL_PT;
			switch ( w ) {
			case 0:
				w = 0;
				break;
			case 1:
				w = 1;
				break;
			case 2:
				w = 2;
				break;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );
			if ( (ret = Print_Parameter_Head( 1, LineDot ) ) != OK ) {
				return ( ret );
			}

			/* ŠOü¥“àüÝ’è */
			Machine_Setting_Line( 1, List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[9-1], &List.S.Attribute[9-1],PWRD_MultiLineType, LST_NOT );
			w = (UBYTE)CHK_MultiLineType(i);

			w_pt[0] = (UBYTE *)&PWRD_PstnLine;
			w_pt[1] = (UBYTE *)&PWRD_PbxLine;
			w_pt[2] = NULL_PT;
			if (w != 0) {
				w = 1;
			}
			else {
				w = 0;
			}
			Param_set( &List.S.Print[27], &List.S.Attribute[27], w, 10, w_pt );

			if (w == 1) {
			    /* ƒAƒNƒZƒX”Ô†ˆóŽš */
#if (0)	/* ƒ[ƒfƒBƒ“ƒOŠJŽnˆÊ’u‚ª‚QƒoƒCƒg‘O‚É‚¸‚ê‚Ä‚¢‚½‚Ì‚Å’¼‚µ‚Ü‚· by K.Watanabe 1998/02/18 */
//				AttributeSet( &List.S.Print[45-1], &List.S.Attribute[45-1],PWRD_PstnAccessNumber, LST_NOT );
#endif
				AttributeSet( &List.S.Print[47-1], &List.S.Attribute[47-1], PWRD_PstnAccessNumber, LST_NOT );
				CMN_BCD_ToASC_StringNum(&List.S.Print[64-1],SYB_PbxAccessNumber[i], 10);
			}
			if ( (ret = Print_Parameter_Head( 1, LineDot ) ) != OK ) {
				return ( ret );
			}
		}
	}
	return (ret);
#endif
}
/** #endif */

