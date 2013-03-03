/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_MSGB.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚a ŒðMƒGƒ‰[
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysprint.h"	/* 94/07/01 ÓÆÀ°ÚÎß°ÄorÁª¯¸Ò¯¾°¼Þ”»’f‚Ì‚½‚ß’Ç‰Á –L“c */
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\sysexec.h"
#include	"\src\atlanta\define\sysmax.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\uni_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_v\rom_tbl.h"
#include	"\src\atlanta\ext_v\sys_data.h"

#if (PRO_RELAYED_REPORT == ENABLE)	/* ’†Œp”zM•s’B’Ê’m‚Ì‚½‚ß  ’|“à Feb.14.1995 */
#include	"\src\atlanta\define\syscomf.h"	/* ’|“à Feb.14.1995 */
#endif

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

#if defined (KEISATSU) /* ŒxŽ@FAX DVT_ID2 Added by SMuratec —› 2005/11/10 */
#include  "\src\atlanta\ext_v\fcm_data.h"
#endif /* defined (KEISATSU) */

/*************************************************************************
	module		:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWB ŒðMƒGƒ‰[ˆóü]
	function	:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWB ŒðMƒGƒ‰[‚ðˆóü‚·‚é]
	common		:[
		SYS_DocumentPrintNo	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD				Print_CommErr_ChkMsg(
						 void )				/*‚È‚µ*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	/*ˆóü*/
	if ( (ret = Print_CommErr_ChkMsg_Common( LST_COMMERR_CHECKMSG ) ) != OK ) {
		return ( ret );
	}
}
	/* ‚±‚±‚Å,CMN_ClearCommandArea()‚ðŒÄ‚ñ‚Å‚½‚¯‚Ç,*/
	/* Ò²Ý‚ÅÁ‚µ‚Ä‚à‚ç‚¤‚±‚Æ‚É‚È‚è‚Ü‚µ‚½. 94/7/7 */

/*************************************************************************
	module		:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWA,B ƒGƒ‰[ ÓÆÀ°ÚÎß°ÄOK ‚ðˆóü‚·‚é]
	function	:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWA,B ƒGƒ‰[ ‚ÆÓÆÀ°ÚÎß°ÄOK‚ðˆóü‚·‚é]
	common		:[]
	condition	:[
		’ •[Ží—Þ
		,	LST_DOC_CHECKMSG		ƒ`ƒFƒbƒNƒƒbƒZ[ƒWA ƒQƒ“ƒRƒE‚ÆÓÆÀ°ÚÎß°Ä(FXŽd—l)
		,	LST_COMMERR_CHECKMSG	ƒ`ƒFƒbƒNƒƒbƒZ[ƒWB ƒRƒEƒVƒ“
	]
	commment	:[
		"ƒ`ƒFƒbƒNƒƒbƒZ[ƒWA ƒQƒ“ƒRƒEh‚ÌŽž‚ÍAmain‚ªƒf[ƒ^‚Ìƒ`ƒFƒbƒN‚ðs‚¢A
		•K‚¸10ƒf[ƒ^ˆÈ‰º‚ÌŽž‚µ‚©ŒÄ‚Î‚ê‚È‚¢B‚à‚µAƒGƒ‰[ƒy[ƒW‚ª‚ ‚Á‚½ê‡
		ˆóü‚Å‚«‚È‚¢‰Â”\«‚ª‚ ‚é‚ªA‚±‚ê‚Í‰Â”\«‚ª¬‚³‚¢‚Æl‚¦A
		‘Î‰ž‚Ís‚í‚È‚¢B‘S‚Ä‚Ì‹@Ží‹¤’ÊŽd—l‚Æ‚·‚éB
		"ƒ`ƒFƒbƒNƒƒbƒZ[ƒWB ƒRƒEƒVƒ“h‚ÌŽž‚ÍA‚P•Å‚Éˆóü‰Â”\‚Èƒf[ƒ^”‚ð
		ƒJƒEƒ“ƒg‚µˆóü‚·‚éB‚½‚¾‚µAƒGƒ‰[ƒy[ƒW‚Ìs”‚Ü‚Å‚ÍÁª¯¸‚µ‚È‚¢‚½‚ßA
		‰ü•ÅðŒ‚ÍAŽc‚èˆóü‰Â”\s”‚ª‚UˆÈ‰º‚Æ‚È‚Á‚½Žž‚Æ‚·‚éB
		Œ´e‚ð•t‚¯‚éˆóü•”•ª‚ª‚P‚VsˆÈ‰º‚Æ‚È‚Á‚½ŽžA‰üƒy[ƒW‚·‚éB ** 97/11/25 By M.Kuwahara 
	]
	return		:[ˆóüŒ‹‰Ê‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD				Print_CommErr_ChkMsg_Common(
						 UBYTE PrnKind )	/*’ •[Ží—Þ*/
{
	UBYTE	i;					/*loop*/
	UBYTE	page;				/*Íß°¼Þ*/
	UBYTE	line_cnt;			/*Žc‚èˆóü‰Â”\s”*/
	UBYTE	exec_cnt;			/*ExecQueue¶³ÝÄ*/
	UBYTE	prn_mode;			/*ˆóüÓ°ÄÞ*/
										/*LST_ERR_CLOSE_NOT ´×°close‚µ‚È‚¢*/
										/*LST_ERR_CLOSE		´×°close‚·‚é*/
	register WORD	ret;				/*ŽÀsŒ‹‰Ê*/
	UBYTE	debug_sw;

	if ( PrnKind == LST_DOC_CHECKMSG ) {
/*		prn_mode = LST_ERR_CLOSE_NOT;*/
		prn_mode = LST_ERR_CLOSE;	/** ƒGƒ‰[‚É‚È‚Á‚½ŽžAŒÄ‚ÑŒ³‚Å‚ÌƒNƒ[ƒY‚Í	*/
									/** ’Ê‚ç‚È‚¢‚æ‚¤‚É•ÏX‚µ‚½‚½‚ß	97/12/09 By M.Kuwahara */
	}
	else {
		prn_mode = LST_ERR_CLOSE;
	}
	page = 1;
	exec_cnt = 0;
	debug_sw = 1;

	while ( exec_cnt != SYS_EXEC_QUEUE_MAX ) {
/*		if ( PrnKind == LST_COMMERR_CHECKMSG ) {*/	/* 97/11/25 By M.Kuwahara */
		if (( PrnKind == LST_COMMERR_CHECKMSG ) ||
			((PrnKind == LST_DOC_CHECKMSG ) &&
			 (page != 1 ))) {
			if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
				return ( ret );
			}
		}
		LST_CharacterLine = 0;	/**	ƒLƒƒƒ‰ƒNƒ^ˆóŽš•”‚Ìƒ‰ƒCƒ“”‚ÌƒNƒŠƒA	Add By Hirao 98/01/06 */

/*		line_cnt = (UBYTE)(LST_LETTER_LEN - 7);/*ˆóü‰Â”\s”¾¯Ä*/	/* 97/1125 By M.Kuwahara */
		line_cnt = (UBYTE)(PaperSizeLen() - 7);/*ˆóü‰Â”\s”¾¯Ä*/

		if ( (ret = Print_Err_ChkMsg_Head( 0, page, PrnKind ) ) != OK ) {	/*Í¯ÀÞˆóü*/
			return ( ret );
		}

		while ( 1 ) {
			ExecQueueNextSearch( &exec_cnt );					/*ŽŸÃÞ°À»°Á*/
			if ( exec_cnt == SYS_EXEC_QUEUE_MAX ) {
				if (debug_sw == 1) {
					debug_sw = 0;

#if (PRO_MULTI_LINE == ENABLE)	 /* Add By O.Kimoto 1997/06/26 */
					if (Print_LineNumber(exec_cnt, 0) == TRUE) {
						/* 1997/102/09 ‚±‚±‚Å ƒWƒƒƒ€‚ª”­¶‚µ‚½‚çƒNƒ[ƒYˆ—‚ª‚Q‰ñ‚Í‚µ‚Á‚Ä‚µ‚Ü‚¢BƒŠƒZƒbƒg‚É‚Æ‚ñ‚Å‚µ‚Ü‚¤ */
						/*if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {*/
						if ( (ret = CharacterPrint( LST_PRINT+prn_mode)) != OK ) {
	  						return ( ret );
						}
						line_cnt--;
					}
#endif

					/*–¾×‚ªˆóü‚³‚ê‚È‚¢Ž–‚ª‚ ‚éˆ×A–¾×‚ª‚È‚¢Žž‚Í*/
					/*ŒÅ’èÒ¯¾°¼Þ‚ðˆóü‚·‚éB««« 94/09/09 By j.masuda*/
					/*†®†¢†Î†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†²*/			/*94/09/09*/
					Print_CommErr_ChkMsg_Line( 0, List.S.Print, List.S.Attribute );	/*94/09/09*/
					if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {	/*94/09/09*/
						return ( ret );							/*94/09/09*/
					}											/*94/09/09*/
					/*†¤ XXXXX†¤XXXXXXXXX†¤XXXXXXXXXXX†¤*/
					/* ‘—MØ‚Å‚Í‚È‚¢‚Ìˆø”’Ç‰Á	1998/10/28 Y.Matsukuma */
					if ( (ret = Print_CommErr_ChkMsg_Specifi( SYS_EXEC_QUEUE_MAX, prn_mode, LST_PRINT_TCR_NOT )) != OK ) {	/*1–¾×ˆóü*/
						return ( ret );
					}
					/*†¶†¢†Ö†¢†¢†¢†Ö†¢†¢†¢†¢†¢†º*/				/*94/09/09*/
					Print_CommErr_ChkMsg_Line( 3, List.S.Print, List.S.Attribute );	/*94/09/09*/
					if ( (ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK ) {	/*94/09/09*/
						return ( ret );							/*94/09/09*/
					}											/*94/09/09*/
					line_cnt -= 3;								/*94/09/09*/
					/*ªªª 94/09/09 By j.masuda */
				}
				break;	/*94/09/07 By j.masuda*/
			}
			debug_sw = 0;

#if (0)
** /* ‘—MØ‚Æƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚Í’èŒ^’·‚ÅƒJƒbƒg‚·‚é‚æ‚¤‚É•ÏX By O.Kimoto 1999/02/22 */
** #if (PRO_PAPER_TYPE== CUT_PAPER)
** 			/* ‚r‚`‚j‚`‚j‚h^‚g‚h‚m‚n‚j‚h‚Í‹L˜^Ž†‚ªƒ[ƒ‹Ž†‚È‚Ì‚ÅA‘—MØ‚ÍŠª‚«•¨‚Æ‚µ‚Ü‚·B
** 			** by O.Kimoto 1999/01/26
** 			*/
** 			if ( line_cnt < 6 ) {
** 				break;
** 			}
** #endif
#else
			if ( line_cnt < 6 ) {
				break;
			}
#endif

#if (PRO_MULTI_LINE == ENABLE)	 /* Add By O.Kimoto 1997/06/26 */
			if (Print_LineNumber(exec_cnt, 0) == TRUE) {
				/* 1997/12/09 ‚±‚±‚ÅƒWƒƒƒ€‚ª”­¶‚µ‚½‚çƒNƒ[ƒYˆ—‚ª‚Q‰ñ‚Í‚µ‚Á‚Ä‚µ‚Ü‚¢BƒŠƒZƒbƒg‚É‚Æ‚ñ‚Å‚µ‚Ü‚¤ */
				/*if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {*/
				if ( (ret = CharacterPrint( LST_PRINT+prn_mode )) != OK ) {
	  				return ( ret );
				}
				line_cnt--;
			}
#endif

			/*†®†¢†Î†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†²*/
			Print_CommErr_ChkMsg_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
				return ( ret );
			}
			/*†¤ XXXXX†¤XXXXXXXXX†¤XXXXXXXXXXX†¤*/
			/* ‘—MØ‚Å‚È‚¢‚Ìˆø”’Ç‰Á	1998/10/28 Y.Matsukuma */
			if ( (ret = Print_CommErr_ChkMsg_Specifi( exec_cnt, prn_mode, LST_PRINT_TCR_NOT )) != OK ) {	/*1–¾×ˆóü*/
				return ( ret );
			}
			/*†¶†¢†Ö†¢†¢†¢†Ö†¢†¢†¢†¢†¢†º*/
			Print_CommErr_ChkMsg_Line( 3, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
				return ( ret );
			}
			line_cnt -= 3;
#if defined(DEU)	/* by M.H '97/03/22 DEU‚Ì‚Ý•œŠˆ *//* 97/11/26 By M.Kuwahara */
/* #if(0) ** PAT‚Ì‚½‚ß‚Í‚¸‚· By H.Hirao 1996/06/14 */
			/* ´×°Íß°¼Þ*/
			if ( (SYB_ExecQueue[exec_cnt].Result & DIALERROR) == TRANSMITERROR) {	/*TRANSMITERROR*/
				for ( i = 0; i < SYS_ERROR_PAGE; i++ ) {
					if ( SYB_ExecQueue[exec_cnt].ErrorPage[i] != 0 ) {
						if ( (ret = Print_ChkMsg_ErrorPages( prn_mode,
						  									 &SYB_ExecQueue[exec_cnt].ErrorPage[0],
						  									 SYS_ERROR_PAGE, &line_cnt )) != OK ) {
							return ( ret );
						}
						break;
					}
				}
			}
#endif
			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( (UBYTE)(LST_LINE_FEED+prn_mode+1) )) != OK ) {
				return ( ret );
			}
			line_cnt--;
			exec_cnt++;
		}
		LST_CharacterLine = (UBYTE)(PaperSizeLen() - line_cnt);	/**	ƒLƒƒƒ‰ƒNƒ^ˆóŽšƒ‰ƒCƒ“”‚ðƒZƒbƒg By Hirao 98/01/06 */
		if ( (ret = Print_Err_ChkMsg_Head( 1, page, PrnKind ) ) != OK ) {	/*Ì¯Àˆóü*/
			return ( ret );
		}
		LST_CharacterLine++; /** By Hirao 98/01/06 */
		if ( exec_cnt != SYS_EXEC_QUEUE_MAX ) {
			ExecQueueNextSearch( &exec_cnt );					/*ŽŸÃÞ°À»°Á*/
		}

#if(0)
** /* ‘—MØ‚Æƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚Í’èŒ^’·‚ÅƒJƒbƒg‚·‚é‚æ‚¤‚É•ÏX By O.Kimoto 1999/02/22 */
** #if (PRO_PAPER_TYPE== ROLL_PAPER)
** /* ‚r‚`‚j‚`‚j‚h^‚g‚h‚m‚n‚j‚h‚Í‹L˜^Ž†‚ªƒ[ƒ‹Ž†‚È‚Ì‚ÅA‘—MØ‚ÍŠª‚«•¨‚Æ‚µ‚Ü‚·B
** ** by O.Kimoto 1999/01/26
** */
** 		if ( (ret = CharacterPrint( LST_LINE_FEED + 2 )) != OK ) {
** 			return ( ret );
** 		}
** 
** 		if ( PrnKind != LST_DOC_CHECKMSG ) {
** 			if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
** 				return ( ret );
** 			}
** 		}
** #else
** /*		if ( PrnKind == LST_COMMERR_CHECKMSG ) {*/	/* 97/11/25 By M.Kuwahara */
** 		if (( PrnKind == LST_COMMERR_CHECKMSG ) ||
** 		    ((PrnKind == LST_DOC_CHECKMSG ) &&
** 			 (exec_cnt != SYS_EXEC_QUEUE_MAX ))) {
** 			if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
** 				return ( ret );
** 			}
** 		}
** 		else {
** 			if ( line_cnt < 17 ) {	/**Žc‚ès”‚ª17sˆÈ‰º‚Ìê‡AŽŸ‚ÌÍß°¼Þ‚É’~ÏŒ´e‚ðˆóŽš‚·‚éˆ× */
** 				if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
** 					return ( ret );
** 				}
** 				if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
** 					return ( ret );
** 				}
** 				if ( (ret = CharacterPrint( (UBYTE)(LST_LINE_FEED+prn_mode + 2) )) != OK ) {
** 					return ( ret );
** 				}
** 				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
** 				List.S.Print[1] = 'P';	/** ƒy[ƒW‚ðˆóŽš */
** 				List.S.Print[2] = '.';
** 				CMN_UnsignedIntToASC( &List.S.Print[3], (UWORD)(page + 1), 0, 0 );
** 				if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
** 					return ( ret );
** 				}
** 				
** 				LST_CharacterLine = 3;	/**	ŽŸ‚Ìƒy[ƒW‚ÉƒCƒ[ƒWƒvƒŠƒ“ƒg‚·‚é‚Ì‚ÅƒLƒƒƒ‰ƒNƒ^ˆóŽš•”‚Í1ƒ‰ƒCƒ“‚É‚È‚é	*/
** 				
** 				break;
** 			}
** 		}
** 		page++;								/*94/09/07 By j.masuda*/
** #endif
#else
/*		if ( PrnKind == LST_COMMERR_CHECKMSG ) {*/	/* 97/11/25 By M.Kuwahara */
		if (( PrnKind == LST_COMMERR_CHECKMSG ) ||
		    ((PrnKind == LST_DOC_CHECKMSG ) &&
			 (exec_cnt != SYS_EXEC_QUEUE_MAX ))) {
			if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
				return ( ret );
			}
		}
		else {
			if ( line_cnt < 17 ) {	/**Žc‚ès”‚ª17sˆÈ‰º‚Ìê‡AŽŸ‚ÌÍß°¼Þ‚É’~ÏŒ´e‚ðˆóŽš‚·‚éˆ× */
				if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
					return ( ret );
				}
				if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
					return ( ret );
				}
				if ( (ret = CharacterPrint( (UBYTE)(LST_LINE_FEED+prn_mode + 2) )) != OK ) {
					return ( ret );
				}
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
				List.S.Print[1] = 'P';	/** ƒy[ƒW‚ðˆóŽš */
				List.S.Print[2] = '.';
				CMN_UnsignedIntToASC( &List.S.Print[3], (UWORD)(page + 1), 0, 0 );
				if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
					return ( ret );
				}
				
				LST_CharacterLine = 3;	/**	ŽŸ‚Ìƒy[ƒW‚ÉƒCƒ[ƒWƒvƒŠƒ“ƒg‚·‚é‚Ì‚ÅƒLƒƒƒ‰ƒNƒ^ˆóŽš•”‚Í1ƒ‰ƒCƒ“‚É‚È‚é	*/
				
				break;
			}
		}
		page++;								/*94/09/07 By j.masuda*/
#endif

	}
	return ( OK );
}

/*************************************************************************
	module		:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWB@ŒðMƒGƒ‰[‚Æƒ‚ƒjƒ^[ƒŒƒ|[ƒg‘—MOK@ˆêŠ‡‘—M@–¾×ˆóü]
	function	:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWB ŒðMƒGƒ‰[‚Æƒ‚ƒjƒ^[ƒŒ‚Û[ƒg@‘—MOK@ˆêŠ‡‘—M@‚Ì–¾×•”•ª‚ðˆóü‚·‚é]
	common		:[
		List			:
		SYB_ExecQueue	:
		SYB_CommandFile	:
		SYB_BatchTxFile	:
	]
	condition	:[
		ˆóüƒ‚[ƒh
			LST_PRINT
			LST_PRINT_ECN
		ˆóüŽí—Þ
			LST_PRINT_TCR		:‘—MØON
			LST_PRINT_TCR_NOT	:‘—MØOFF
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD				Print_CommErr_ChkMsg_Specifi(
						 UBYTE Number,		/*”Ô†*/
						 UBYTE PrnMode,		/*ˆóüƒ‚[ƒh*/
						 UBYTE PrnKind )	/*ˆóüŽí—Þ‚Ìˆø”’Ç‰Á	1998/10/28 Y.Matsukuma */
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/
	UBYTE	num_cnt;						/*ÀÞ²ÔÙŒ…” 1998/10/28 Y.Matsukuma */

	Print_CommErr_ChkMsg_Line( 1, List.S.Print, List.S.Attribute );
	/*Â³¼Ý¹¯¶”Ô†*/
	CommunicationResultName( SYB_ExecQueue[Number].Result, LST_NAME_SHORT,
	  LST_RESULT_COMMON, &List.S.Print[2-1], &List.S.Attribute[2-1] );
	/*Â³¼Ý¹¯¶ Ò¯¾°¼Þ*/
	if ((SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_MONITOR)
	 || (SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_BA_MONITOR)){	/* ÓÆÀ°ÚÎß°ÄON ˆêŠ‡‘—M */
/*		if ( SYB_ExecQueue[Number].Status == SYS_EXEC_OK ) {		/* ³íI—¹Žž *kobe\anzu* By H.Y 1994/12/19 */
		if ((SYB_ExecQueue[Number].Result & ~ECM_MODE_SET) == NO_ERROR) { /* ³íI—¹Žž Anzu By H.Y 1994/12/19 */
			AttributeSet( &List.S.Print[9-1], &List.S.Attribute[9-1], PWRD_CheckMessage, LST_NOT );
		}
		else{														/* ´×°I—¹Žž */
			CommunicationResultName( SYB_ExecQueue[Number].Result, LST_NAME_LONG,
			  LST_RESULT_COMMON, &List.S.Print[9-1], &List.S.Attribute[9-1] );
		}
	}
	else{
		/* Áª¯¸Ò¯¾°¼Þ */
		CommunicationResultName( SYB_ExecQueue[Number].Result, LST_NAME_LONG,
		  LST_RESULT_COMMON, &List.S.Print[9-1], &List.S.Attribute[9-1] );
	}
	/*ÀÞ²ÔÙÊÞÝºÞ³*/
	CMN_MemorySetNULL( List.S.Work, LST_COLUM-1, ' ' ); /**	ƒ[ƒNƒGƒŠƒA‚ÌƒNƒŠƒA By H.Hirao 1996/06/04	*/
	if ( SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_BA_MONITOR ) {		/* ˆêŠ‡‘—M H8‚Íâ‘Îelse‚És‚­*/
#if ( PRO_BATCH_TX == ENABLE )
		if ( SYB_BatchTxFile[SYS_DocumentPrintNo].Name[0] != 0x00 ) {	/* BOX–¼—L‚è */
			CMN_StringCopy( &List.S.Print[40-1], SYB_BatchTxFile[SYS_DocumentPrintNo].Name );
		}
		else {																/* BOX–¼–³‚µ°>ÀÞ²ÔÙ”Ô† */
#if (0)	/* 97/09/25 By M.Kuwahara */
			ProgramDataDialToString( (struct SYS_DialData_t *)&SYB_BatchTxFile[SYS_DocumentPrintNo].DialNumber[0],
				1, List.S.Work, 0 );							   /*Œ»Ýs‚Í‚PsˆÈã‚É‚È‚ç‚È‚¢(1ˆ¶æ‚Ì‚Ý)‚Ì‚Å0‚Æ‚µ‚½*/
#endif
			BatchTxFileDialDataToString( &SYB_BatchTxFile[SYS_DocumentPrintNo].DialNumber[0],1,List.S.Work,0 );
			CMN_StringCopy( &List.S.Print[40-1], List.S.Work );
		}
#endif
	}
	else {
		/* ˆêŠ‡‘—MˆÈŠO */
		switch ( SYB_ExecQueue[Number].ExecDial.Item ) {
			case SYS_DIRECT_DIAL:
				CMN_BCD_ToASC_String( List.S.Work, SYB_CommandFile
				  [SYB_ExecQueue[Number].Number.Command].DialNumber.Direct
				  [SYB_ExecQueue[Number].ExecDial.ExecNumber.Command] );
				CMN_StringCopy( &List.S.Print[40-1], List.S.Work );
			break;
			case SYS_ONETOUCH_DIAL:
#if (0)
//				List.S.Print[40-1] = '[';
//				List.S.Print[42-1] = ']';
//				List.S.Print[41-1] =
//				  CMN_OffsetToOnetouchCode(SYB_ExecQueue[Number].ExecDial.
/					ExecNumber.Onetouch );
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
				if ( CMN_OffsetToOnetouchCode( SYB_ExecQueue[Number].ExecDial.
				  ExecNumber.Onetouch ) <= 0x7A ){ /* ÜÝÀ¯Á‹L†‚ª•ÏX(ANZU) By H.Hirao 1996/01/10 */
					List.S.Print[40-1] = '[';
					List.S.Print[42-1] = ']';
					List.S.Print[41-1] =
				  	  CMN_OffsetToOnetouchCode(SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch );
				} else{
					List.S.Print[40-1] = '[';
					List.S.Print[43-1] = ']';
					List.S.Print[41-1] = 0x55;	/* 'U'‚ÌASCIIº-ÄÞ */
					List.S.Print[42-1] = CMN_OffsetToOnetouchCode( SYB_ExecQueue[Number].ExecDial.
					    ExecNumber.Onetouch ) & (UBYTE)0x0F | (UBYTE)0x30; /* U1`U8‹L†‚ð‚Â‚­‚é */
				}
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_PANEL == ANK)
				List.S.Print[40-1] = '[';
				List.S.Print[43-1] = ']';
				CMN_UnsignedIntToASC(
 					&List.S.Print[41-1], 
					(UWORD)(CMN_OffsetToOnetouchCode( SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch ) - 0x40),
					2, 
					'0' );
 #endif
 #if (PRO_PANEL == KANJI)
		 		/* ƒƒ“ƒ^ƒbƒ`‚Ì•\Ž¦‚ð[]->ŠG•¶Žš‚É•ÏX By O.Kimoto 1998/01/22 */
				List.S.Print[40-1] = LCD_PICFONT;
				List.S.Print[41-1] = LCD_PICFONT_LOWER;
				CMN_UnsignedIntToASC(
 					&List.S.Print[42-1], 
					(UWORD)(CMN_OffsetToOnetouchCode( SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch ) - 0x40),
					2, 
					'0' );
 #endif
#endif
				/**	ÜÝÀ¯ÁÀÞ²±Ù‹L†‚É‰Á‚¦‚Ä‘ŠŽèæ–¼ –”‚Í “d˜b”Ô†‚ðˆóŽš‚·‚é ˆÈ‰º11s’Ç‰Á For ANZU By H.Hirao 1996/05/10
				*	“d˜b”Ô†‚Í40Œ…‚Ü‚Å“o˜^‚Å‚«‚é‚ª34Œ…‚Ü‚ÅˆóŽš‚·‚é
				*	’ÊM’†‚ÉÜÝÀ¯ÁÀÞ²±Ù‚ð“o˜^‚µ’¼‚·‰Â”\«‚Í‚ ‚é‚ªHHH
				*/

#if (0)
** 				/* ‚h‚b‚g‚n‚t‚©‚ç‚ÌƒtƒB[ƒhƒoƒbƒN By O.Kimoto 1998/03/30 */
** 				/*
** 				** ƒŠƒ‚[ƒgf’f‚ª–¢“o˜^‚È‚ç‚e‚O‚ð‘‚­ê‡‚ª‚ ‚é‚Ì‚Å‚e‚e‚ÅŒ©‚Ä‚¢‚é‚Æ‚¨‚©‚µ‚­‚È‚é
** 				** 1997/10/03 M.Shimizu
** 				*/
** 				if ( SYB_OnetouchDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch].Dial[0] != LST_DIAL_NOT ) [ /**	ÜÝÀ¯ÁÀÞ²±Ù‚ª“o˜^‚³‚ê‚Ä‚¢‚éê‡	*/
#else
 #if (0)
 **  				/* u‚cD‚OD‚Uv‚ð–³—‚É”­¶‚³‚¹‚ÄAƒ`ƒFƒbƒNƒƒbƒZ[ƒWƒvƒŠƒ“ƒg’¼‘O‚ÅÄ“o˜^‚·‚é‚ÆA¡“o˜^‚µ‚½î•ñ‚ª
 **  				** ƒvƒŠƒ“ƒg‚³‚ê‚éˆ×Au‚cD‚OD‚Uv‚ÌŽž‚Í“o˜^î•ñ‚ðƒvƒŠƒ“ƒg‚µ‚È‚¢‚æ‚¤‚É‚µ‚Ü‚·B
 **  				** D.0.6 By O.Kimoto 1998/09/07
 **  				*/
 ** 				if ( (SYB_OnetouchDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch].Dial[0] & 0xF0) != 0xF0 ) [ /**	ÜÝÀ¯ÁÀÞ²±Ù‚ª“o˜^‚³‚ê‚Ä‚¢‚éê‡	*/
 #else
				if ((SYB_ExecQueue[Number].Result != (UWORD)(DIALERROR + 0x0006))
					&& ((SYB_OnetouchDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch].Dial[0] & 0xF0) != 0xF0 )) { /**	ÜÝÀ¯ÁÀÞ²±Ù‚ª“o˜^‚³‚ê‚Ä‚¢‚éê‡	*/
				
 #endif
 
#endif

					if ( SYB_OnetouchDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch].Name[0] != NULL ) { /**	‘ŠŽèæ–¼‚ª“o˜^‚³‚ê‚Ä‚¢‚éê‡	*/
						CMN_StringCopy( &List.S.Print[45],
						  SYB_OnetouchDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch].Name );
					}
					else { /**	‘ŠŽèæ–¼‚ª“o˜^‚³‚ê‚Ä‚¢‚È‚¢ê‡“d˜b”Ô†‚ðˆóŽš‚·‚é	*/
						CMN_BCD_ToASC_String( List.S.Work,
						  SYB_OnetouchDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch].Dial );

						/* ÀÞ²ÔÙŒ…‚ª34•¶Žš‚ð‰z‚¦‚½‚çu¥¥‰º33Œ…v‚ðˆóŽš‚·‚éˆ—’Ç‰Á 1998/10/28 Y.Matsukuma */
						num_cnt = DialWithinCheck(List.S.Work);
						if (CHK_UNI_DialWithin() 	/* ÕÆ°¸SW I7-0 */
						&& PrnKind == LST_PRINT_TCR /* ‘—MØON */
						&& num_cnt > 34) {
							num_cnt = num_cnt - 34;
							List.S.Work[num_cnt] = LST_A_TENTEN;
							CMN_StringCopyNum( &List.S.Print[45], &List.S.Work[num_cnt], 34 );
						}
						else {
							CMN_StringCopyNum( &List.S.Print[45], List.S.Work, 34 );
						}
					}
				}
				break;
			case SYS_SPEED_DIAL:
#if defined(POPLAR_F)
				if ( SYS_SPEED_DIAL_MAX+SYS_2ND_SPEED_DIAL_MAX >= 100 ) {
#else
				if ( SYS_SPEED_DIAL_MAX+SYS_2ND_SPEED_DIAL_MAX > 100 ) {
#endif
/*					List.S.Print[40-1] = '(';*/
/*					List.S.Print[44-1] = ')';*/
#if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
					List.S.Print[40-1] = *CalculateStringAddress(&D2W_HeadCharacter_Speed);
#else
					List.S.Print[40-1] = 'S';
#endif
					if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
						if ( GetRecordFromNumber( (UWORD)SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed ) != 0xFFFF ){
#if (1) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
							CMN_UnsignedIntToASC( &List.S.Print[41-1],
								GetRecordFromNumber((UWORD)SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed), OP_SPEED_FIGURE_MAX, '0' );
#else
//							CMN_UnsignedIntToASC( &List.S.Print[41-1],
//								GetRecordFromNumber((UWORD)SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed), 3, '0' );
#endif
						}
						else {
#if (1) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
							CMN_MemorySet( &List.S.Print[41-1], OP_SPEED_FIGURE_MAX,'*' );
#else
//							CMN_MemorySet( &List.S.Print[41-1], 3,'*' );
#endif
						}
					}
					else{
#if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ª000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
						CMN_UnsignedIntToASC( 
							&List.S.Print[41-1],
						  	(UWORD)(SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed+OPR_SPEED_DIAL_MIN), 
							3, 
							'0' );
#else
						CMN_UnsignedIntToASC( 
							&List.S.Print[41-1],
						  	(UWORD)(SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed+1), 
							3, 
							'0' );
#endif
					}
				}
				else {
/*					List.S.Print[40-1] = '(';*/
/*					List.S.Print[43-1] = ')';*/
#if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
					List.S.Print[40-1] = *CalculateStringAddress(&D2W_HeadCharacter_Speed);
#else
					List.S.Print[40-1] = 'S';
#endif
					if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
						if ( GetRecordFromNumber( (UWORD)SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed ) != 0xFFFF ) {							CMN_UnsignedIntToASC( 
								&List.S.Print[41-1],
								GetRecordFromNumber((UWORD)SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed), 
								2, 
								'0' );
						}
						else {
							CMN_MemorySet( &List.S.Print[41-1], 2,'*' );
						}
					}
					else{	/* ’Êí‚Ì’Zk‚ÌŽž */
#if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ª000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
						CMN_UnsignedIntToASC( 
							&List.S.Print[41-1],
						  	(UWORD)(SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed+OPR_SPEED_DIAL_MIN), 
							2, 
							'0' );
#else
						CMN_UnsignedIntToASC( 
							&List.S.Print[41-1],
						  	(UWORD)(SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed+1), 
							2, 
							'0' );
#endif
					}
				}
				/**	’Zk”Ô†‚É‰Á‚¦‚Ä‘ŠŽèæ–¼ –”‚Í “d˜b”Ô†‚ðˆóŽš‚·‚é ˆÈ‰º11s’Ç‰Á For ANZU By H.Hirao 1996/05/10
				*	“d˜b”Ô†‚Í40Œ…‚Ü‚Å“o˜^‚Å‚«‚é‚ª34Œ…‚Ü‚ÅˆóŽš‚·‚é
				*/

#if (0)
** 				/* ‚h‚b‚g‚n‚t‚©‚ç‚ÌƒtƒB[ƒhƒoƒbƒN By O.Kimoto 1998/03/30 */
** 				/*
** 				** ƒŠƒ‚[ƒgf’f‚ª–¢“o˜^‚È‚ç‚e‚O‚ð‘‚­ê‡‚ª‚ ‚é‚Ì‚Å‚e‚e‚ÅŒ©‚Ä‚¢‚é‚Æ‚¨‚©‚µ‚­‚È‚é
** 				** 1997/10/03 M.Shimizu
** 				*/
** 				if ( SYB_SpeedDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed].Dial[0] != LST_DIAL_NOT ) [ /**	’ZkÀÞ²±Ù‚ª“o˜^‚³‚ê‚Ä‚¢‚éê‡	*/
#else
 #if (0)
 **  				/* u‚cD‚OD‚Uv‚ð–³—‚É”­¶‚³‚¹‚ÄAƒ`ƒFƒbƒNƒƒbƒZ[ƒWƒvƒŠƒ“ƒg’¼‘O‚ÅÄ“o˜^‚·‚é‚ÆA¡“o˜^‚µ‚½î•ñ‚ª
 **  				** ƒvƒŠƒ“ƒg‚³‚ê‚éˆ×Au‚cD‚OD‚Uv‚ÌŽž‚Í“o˜^î•ñ‚ðƒvƒŠƒ“ƒg‚µ‚È‚¢‚æ‚¤‚É‚µ‚Ü‚·B
 **  				** D.0.6 By O.Kimoto 1998/09/07
 **  				*/
 ** 				if ( (SYB_SpeedDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed].Dial[0] & 0xF0) != 0xF0 ) [ /**	’ZkÀÞ²±Ù‚ª“o˜^‚³‚ê‚Ä‚¢‚éê‡	*/
 #else
				if ((SYB_ExecQueue[Number].Result != (UWORD)(DIALERROR + 0x0006))
					&& ( (SYB_SpeedDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed].Dial[0] & 0xF0) != 0xF0 )) { /**	’ZkÀÞ²±Ù‚ª“o˜^‚³‚ê‚Ä‚¢‚éê‡	*/
 #endif
#endif
					if ( SYB_SpeedDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed].Name[0] != NULL ) { /**	‘ŠŽèæ–¼‚ª“o˜^‚³‚ê‚Ä‚¢‚éê‡	*/
#if (PRO_OP_SPPED_4_FIGURE == ENABLE) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */	/* if 1 ‚É‚È‚Á‚Ä‚¢‚½‚ªA‚RŒ…Žž‚É•¶Žš‚ª‚¸‚ê‚é‚Ì‚ÅðŒ‚Â‚¯‚Ü‚· 2003/01/07 T.Takagi */
						if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
							CMN_StringCopy( &List.S.Print[46], SYB_SpeedDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed].Name );
						}
						else {
							CMN_StringCopy( &List.S.Print[45], SYB_SpeedDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed].Name );
						}
#else
						CMN_StringCopy( &List.S.Print[45], SYB_SpeedDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed].Name );
#endif
					}
					else { /**	‘ŠŽèæ–¼‚ª“o˜^‚³‚ê‚Ä‚¢‚È‚¢ê‡“d˜b”Ô†‚ðˆóŽš‚·‚é	*/
						CMN_BCD_ToASC_String( List.S.Work,
						  SYB_SpeedDial[SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed].Dial );

						/* ÀÞ²ÔÙŒ…‚ª34•¶Žš‚ð‰z‚¦‚½‚çu¥¥‰º33Œ…v‚ðˆóŽš‚·‚éˆ—’Ç‰Á 1998/10/28 Y.Matsukuma */
						num_cnt = DialWithinCheck(List.S.Work);
						if (CHK_UNI_DialWithin() 	/* ÕÆ°¸SW I7-0 */
						&& PrnKind == LST_PRINT_TCR /* ‘—MØON */
						&& num_cnt > 34) {
							num_cnt = num_cnt - 34;
							List.S.Work[num_cnt] = LST_A_TENTEN;
#if (PRO_OP_SPPED_4_FIGURE == ENABLE) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */	/* if 1 ‚É‚È‚Á‚Ä‚¢‚½‚ªA‚RŒ…Žž‚É•¶Žš‚ª‚¸‚ê‚é‚Ì‚ÅðŒ‚Â‚¯‚Ü‚· 2003/01/07 T.Takagi */
							if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
								CMN_StringCopyNum( &List.S.Print[46], &List.S.Work[num_cnt], 33 );
							}
							else {
								CMN_StringCopyNum( &List.S.Print[45], &List.S.Work[num_cnt], 34 );
							}
#else
							CMN_StringCopyNum( &List.S.Print[45], &List.S.Work[num_cnt], 34 );
#endif
						}
						else {
#if (PRO_OP_SPPED_4_FIGURE == ENABLE) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */	/* if 1 ‚É‚È‚Á‚Ä‚¢‚½‚ªA‚RŒ…Žž‚É•¶Žš‚ª‚¸‚ê‚é‚Ì‚ÅðŒ‚Â‚¯‚Ü‚· 2003/01/07 T.Takagi */
							if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
								CMN_StringCopyNum( &List.S.Print[46], List.S.Work, 33 );
							}
							else {
								CMN_StringCopyNum( &List.S.Print[45], List.S.Work, 34 );
							}
#else
							CMN_StringCopyNum( &List.S.Print[45], List.S.Work, 34 );
#endif
						}
					}
				}
				break;
		}
	}
	if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+PrnMode) )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

/*************************************************************************
	module		:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWB ŒðMƒGƒ‰[‰¡‹æØ‚èŒrüì¬]
	function	:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWB ŒðMƒGƒ‰[‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
			0 = †®†¢†Î†¢†¢†¢†¢†Î†¢†¢†¢†¢†²
			1 = †¤	†¤		  †¤		†¤
			2 = †¾†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†¢†¢†Æ
			3 = †¶†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†¢†¢†º
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
void			Print_CommErr_ChkMsg_Line(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†Î†¢†¢†¢†¢†Î†¢†¢†¢†¢†²*/
			AscString[ 1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 78 , LST_KLINE_);
			AscString[ 8-1] = LST_KLINE8;
			AscString[39-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE9;
			break;
		case 1:
			/*†¤  †¤		†¤		  †¤*/
			AscString[ 1-1] = LST_KLINEI;
			AscString[ 8-1] = LST_KLINEI;
			AscString[39-1] = LST_KLINEI;
			AscString[80-1] = LST_KLINEI;
			break;
		case 2:
			/*†¾†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†¢†¢†Æ*/
			AscString[ 1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[ 8-1] = LST_KLINE5;
			AscString[39-1] = LST_KLINE5;
			AscString[80-1] = LST_KLINE6;
			break;
		case 3:
			/*†¶†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†¢†¢†º*/
			AscString[ 1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[ 8-1] = LST_KLINE2;
			AscString[39-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE3;
			break;

#if (PRO_RESULT_REPORT_TX == ENABLE)	/* Add By O.Kimoto 1998/12/10 */
		case 4:
			/*†¶†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†¢†¢†º*/
			AscString[ 1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[ 8-1] = LST_KLINE5;
			AscString[39-1] = LST_KLINE5;
			AscString[80-1] = LST_KLINE6;
			break;
#endif

	}
}

/*************************************************************************
	module		:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWŒ©oˆóü]
	function	:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWŒ©o‚ðˆóü‚·‚éB]
	common		:[
		List	:
	]
	condition	:[
		ˆóüÓ°ÄÞ
		,		LST_ERR_CLOSE
		,		LST_ERR_CLOSE_NOT
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD					Print_ChkMsg_Head(
						 UBYTE PrnMode )	/*ˆóüƒ‚[ƒh*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[25-1] = LST_KLINE7;
	CMN_MemorySet( &List.S.Print[26-1], 30, LST_KLINE_ );
	List.S.Print[56-1] = LST_KLINE9;
	if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+PrnMode) )) != OK ) {
		return ( ret );
	}

	/*@ƒ`ƒFƒbƒNƒƒbƒZ[ƒW@*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[25-1] = LST_KLINEI;
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
	AttributeSet( &List.S.Print[28-1], &List.S.Attribute[28-1],
		PWRD_CheckMessage_K, LST_NOT );		/* MES¨INV 94.7.20 -> NOT 8.10 */
#if (0)
//	/* Žè“®‘—ŽóMƒ`ƒFƒbƒNƒƒbƒZ[ƒWAƒZƒLƒ…ƒŠƒeƒBŽóMƒƒ‚ƒŠƒI[ƒo[ƒvƒŠƒ“ƒgŽž
//	** SYS_DocumentPrintClass‚ÌÝ’è‚ª‚È‚¢B‚±‚Ì”»’f‚Å‚Í‚Ü‚¸‚¢B
//	** ƒ‚ƒjƒ^[ƒŒƒ|[ƒg‚Í‚e‚wŽd—l‚Ì‚½‚ßƒRƒƒ“ƒg‚É‚·‚é
//	** By M.Tachibana 1997/05/06
//	*/
//	if ( (SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_MONITOR ) ||
//		   (SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_BA_MONITOR )) {
//		AttributeSet( &List.S.Print[28-1], &List.S.Attribute[28-1],		/* ÓÆÀ°ON¤ˆêŠ‡‘—M */
//		  PWRD_MonitorReport_K, LST_NOT );		/* MES¨INV 94.7.20 ->NOT 8.10 */
//	}
//	else {
//		AttributeSet( &List.S.Print[28-1], &List.S.Attribute[28-1],
//		  PWRD_CheckMessage_K, LST_NOT );		/* MES¨INV 94.7.20 -> NOT 8.10 */
//	}
#endif
#else		/* »Â·¤×ÍÞÝÀÞ°‚Í‚±‚Á‚¿‚ð’Ê‚éB¡‚Ì‚Æ‚±‚ëˆêŠ‡‘—M¤ÓÆÀ°ÚÎß°Ä‹@”\‚ª–³‚¢ˆ×‚±‚ê‚Å—Ç‚¢‚ªA*/
	AttributeSet( &List.S.Print[28-1], &List.S.Attribute[28-1],
		PWRD_CheckMessage, LST_MES_TWI_XXX );
#if (0)
//	  		/* ˆêŠ‡‘—M¤ÓÆÀ°ÚÎß°Ä‹@”\’Ç‰Á(ANZU) 95/12/25 •½”ö‰p“T */
//	if ( (SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_MONITOR ) ||
//		   (SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_BA_MONITOR )) {
//		AttributeSet( &List.S.Print[28-1], &List.S.Attribute[28-1],	/* ÓÆÀ°ON¤ˆêŠ‡‘—M */
//		  PWRD_CheckMessage, LST_MES_TWI_XXX );
//	}
//	else {
//		AttributeSet( &List.S.Print[28-1], &List.S.Attribute[28-1],
//		  PWRD_CheckMessage, LST_MES_TWI_XXX );
//	}
#endif
#endif
	List.S.Print[56-1] = LST_KLINEI;
	if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+PrnMode) )) != OK ) {
		return ( ret );
	}

	/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[25-1] = LST_KLINE1;
	CMN_MemorySet( &List.S.Print[26-1], 30, LST_KLINE_ );
	List.S.Print[56-1] = LST_KLINE3;
	if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+PrnMode) )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

/*************************************************************************
	module		:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒW ƒGƒ‰[ ƒy[ƒWˆóü]
	function	:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒW ƒGƒ‰[ ƒy[ƒW‚ðˆóü‚·‚éB]
	common		:[
		List	:
	]
	condition	:[
		ˆóüÓ°ÄÞ
			LST_PRINT
			LST_PRINT_ECN
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300(“ú—§ƒ}ƒCƒRƒ“)]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
#if defined(DEU)	/* by M.H '97/03/22 DEU‚Ì‚Ý•œŠˆ *//* 97/11/26 By M.Kuwahara */
/* #if (0) ** PAT‚Ì‚½‚ßƒRƒƒ“ƒg‚É‚µ‚Ü‚· By H.Hirao 1996/06/14 */
WORD			Print_ChkMsg_ErrorPages(
						 UBYTE PrnMode,			/*ˆóüƒ‚[ƒh*/
						 UBYTE *ErrPageData,	/*ƒGƒ‰[ƒy[ƒWƒf[ƒ^*/
						 UBYTE ErrPageSize,		/*ƒGƒ‰[ƒy[ƒWƒf[ƒ^”*/
						 UBYTE *LineCnt )		/*Žc‚èˆóü‰Â”\s”*/
{
	UBYTE	i;					/*ErrPageData loop*/
	UWORD	j;					/*Err Page Number*/
	UBYTE	k;					/*Err Bit Check*/
	UBYTE	len;				/*ˆóü•¶Žš—ñˆÊ’u*/
	register WORD	ret;		/*ŽÀsŒ‹‰Ê*/

	i = 0;
	j = 1;
	k = 0x01;
	len = 0;
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	while ( 1 ) {
		if ( (*ErrPageData & k) != 0 ) {
			switch ( len ) {
				case	0:
					AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_ErrorPages, LST_NOT );
					len = 16;
					break;
				case	16:
					break;
				default:
					List.S.Print[len] = ',';
					len++;
					break;
			}
			if ( j < 100 ) {
				CMN_UnsignedIntToASC( &List.S.Print[len], (UWORD)j, 2, ' ' );
				len += 2;	/* ’Ç‰Á  ’|“à Apr.24.1995 */
			}
			else {
				CMN_UnsignedIntToASC( &List.S.Print[len], (UWORD)j, 3, ' ' );
				len += 3;	/* ’Ç‰Á  ’|“à Apr.24.1995 */
			}
			/* len += CMN_StringLength((unsigned char far *)List.S.Work);	íœ(ã‚Å+2or+3‚·‚é)  ’|“à Apr.24.1995 */
			if ( len > 74 ) {
				if ( (ret = CharacterPrint( LST_PRINT+PrnMode )) != OK ) {
					return ( ret );
				}
				(*LineCnt)--;
				len = 16;
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			}
		}
		if ( k == 0x80 ) {
			k = 0x01;
			i++;
			ErrPageData++;
			if ( i >= ErrPageSize ) {
				break;
			}
		}
		else {
			k <<= 1;
		}
		j++;
	}
	if ( len > 16 ) {
		if ( (ret = CharacterPrint( LST_PRINT+PrnMode )) != OK ) {
			return ( ret );
		}
		(*LineCnt)--;
	}
	return ( OK );
}
#endif

/*************************************************************************
	module		:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWA,B ƒGƒ‰[ƒwƒbƒ_ˆóü]
	function	:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWA,B ƒGƒ‰[‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
	common		:[
		List			:
		SYB_CurrentTime	:
	]
	condition	:[
		ƒwƒbƒ_Ží—Þ
		,	0->ƒy[ƒWæ“ªŒ©o‚µ
		,	1->ƒy[ƒWƒGƒ“ƒhŒ©o‚µ
		’ •[Ží—Þ
		,	LST_DOC_CHECKMSG		ƒ`ƒFƒbƒNƒƒbƒZ[ƒWA ƒQƒ“ƒRƒE
		,	LST_COMMERR_CHECKMSG	ƒ`ƒFƒbƒNƒƒbƒZ[ƒWB ƒRƒEƒVƒ“
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD					Print_Err_ChkMsg_Head(
						 UBYTE Category,	/*ƒwƒbƒ_Ží—Þ*/
						 UBYTE Page,		/*ƒy[ƒW*/
						 UBYTE PrnKind )	/*’ •[Ží—Þ*/
{
	UBYTE	prn_mode;			/*ˆóüÓ°ÄÞ*/
										/*LST_ERR_CLOSE_NOT ´×°close‚µ‚È‚¢*/
										/*LST_ERR_CLOSE		´×°close‚·‚é*/
	register WORD	ret;				/*ŽÀsŒ‹‰Ê*/

	if ( PrnKind == LST_DOC_CHECKMSG ) {
		prn_mode = LST_ERR_CLOSE_NOT;
	}
	else {
		prn_mode = LST_ERR_CLOSE;
	}

	if ( Category == 0 ) {
		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( (UBYTE)(LST_LINE_FEED+prn_mode) )) != OK ) {
			return ( ret );
		}

		/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
		/*†¤@ƒ`ƒFƒbƒNƒƒbƒZ[ƒW@	  †¤*/
		/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
		if ( (ret = Print_ChkMsg_Head( prn_mode )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( (UBYTE)(LST_LINE_FEED+prn_mode) )) != OK ) {
			return ( ret );
		}
#if (0)	/* 97/11/25 By M.Kuwahara */
//		if ( (PrnKind == LST_DOC_CHECKMSG) || (SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_BA_MONITOR)  ) {
//			/*Œ»ÝŽžŠÔ*/
//			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
//			TimeDataAscii( OFF, SYB_CurrentTime, List.S.Work, 0 );
//			CMN_StringCopy( &List.S.Print[60-1], List.S.Work );
//			if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
//				return ( ret );
//			}
//		}
//		else {
#endif
			/*Page Œ»ÝŽžŠÔ*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[2-1] = 'P';
			List.S.Print[3-1] = '.';
			CMN_UnsignedIntToASC( &List.S.Print[4-1], (UWORD)Page, 0, 0 );
			TimeDataAscii( OFF, SYB_CurrentTime, List.S.Work, 0 );
			CMN_StringCopy( &List.S.Print[60-1], List.S.Work );
			if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT +prn_mode) )) != OK ) {
				return ( ret );
			}
/*		}*/
	}
	else {
		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( (UBYTE)(LST_LINE_FEED+prn_mode) )) != OK ) {
			return ( ret );
		}
	}
	return ( OK );
}

/*************************************************************************
	module		:[ExecQueue ƒGƒ‰[ƒf[ƒ^ ƒlƒNƒXƒg ƒT[ƒ`n
	function	:[ExecQueue‚ÌŽŸ‚ÉƒGƒ‰[‚Æ‚È‚Á‚Ä‚¢‚éƒf[ƒ^‚ðƒT[ƒ`‚·‚é]
	common		:[
		SYB_ExecQueue:
	]
	condition	:[
		ExecQueue¶³ÝÄ
		,	ƒf[ƒ^ƒGƒ“ƒh->EXEC_QUEUE_MAX
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
void				ExecQueueNextSearch(
						 register UBYTE* ExecCnt )/*ExecQueueƒJƒEƒ“ƒg*/
{
	UBYTE	i;						/*loop*/

	for ( i = (*ExecCnt); i < SYS_EXEC_QUEUE_MAX; i++ ) {
		if ( (SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_MONITOR)			/* ÓÆÀ°ÚÎß°Ä */
			&&(SYB_ExecQueue[i].Kind == SYS_COMMAND_TRX)						/* Add By Hirao 1997/11/28 */
			&&(SYB_ExecQueue[i].Number.Command == (UBYTE)SYS_DocumentPrintNo)
			&&((SYB_ExecQueue[i].Status == SYS_EXEC_ERROR) || (SYB_ExecQueue[i].Status == SYS_EXEC_OK)) ) {
			(*ExecCnt) = i;
			break;
		}
#if (PRO_BATCH_TX == ENABLE)
		else if ((SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_BA_MONITOR )	/* ˆêŠ‡‘—M ÓÆÀÚÎß°Ä */
			&&(SYB_ExecQueue[i].Kind == SYS_BATCH_TX)							/* Add By Hirao 1997/11/28 */
			 && (SYB_ExecQueue[i].Number.Batch == (UBYTE)SYS_DocumentPrintNo)
			 &&( (SYB_ExecQueue[i].Status == SYS_EXEC_ERROR)||(SYB_ExecQueue[i].Status == SYS_EXEC_OK)) ) {
			(*ExecCnt) = i;
			break;
		}
#endif
		else if ((SYB_ExecQueue[i].Kind == SYS_COMMAND_TRX)						/* Add By Hirao 1997/11/28 */
			&& (SYB_ExecQueue[i].Number.Command == (UBYTE)SYS_DocumentPrintNo)	/* Áª¯¸Ò¯¾°¼Þ */
			&& (SYB_ExecQueue[i].Status == SYS_EXEC_ERROR )) {
			(*ExecCnt) = i;
			break;
		}
	}
	if ( i == SYS_EXEC_QUEUE_MAX ) {
		(*ExecCnt) = SYS_EXEC_QUEUE_MAX;
	}
}



#if (PRO_RELAYED_REPORT == ENABLE)	/* ’†Œp”zM•s’B’Ê’m‚Ì‚½‚ß  ’|“à Feb.14.1995 */

/* ‘åˆæ•Ï” */
/* Œ»ó‚Í SYS_EXEC_QUEUE_MAX = 209 ‚Å‚·‚ªC‘‚¦‚½‚Æ‚«‚ðl—¶‚µ‚Ä word ‚É‚µ‚Ä‚¨‚«‚Ü‚· */
UWORD	ChkMsgCurrentQueueNo = 0;	/*	’ÊMƒGƒ‰[‚ÌExecQueue”Ô†	*/
UWORD	ChkMsgNextQueueNo = 0;		/*	ŽŸ‚ÉŒŸõ‚·‚é‚ÌExecQueue”Ô†	*/
UBYTE	ChkMsgErrPageNo = 0;		/*	ƒGƒ‰[ƒy[ƒW”Ô†	*/
UBYTE	ChkMsgErrPage1stLine = 0;	/*	ƒGƒ‰[ƒy[ƒWs‚Ì‚Ps–Ú	*/
UBYTE	ChkMsgEmptyRecordFlag = 0;	/*	‹óƒŒƒR[ƒhƒtƒ‰ƒO	*/

/*************************************************************************
	module		:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚aì¬]
	function	:[
		1.	ƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚Ìƒ^ƒCƒgƒ‹•”^ƒƒbƒZ[ƒW•”‚ðì¬‚·‚é
		2.	ƒ^ƒCƒgƒ‹•”‚Ìê‡‚Í,ƒ^ƒCƒgƒ‹‚ðì¬‚·‚é (‚Us)
		3.	ƒƒbƒZ[ƒW•”‚Ìê‡‚Í,ExecQueue‚ðƒT[ƒ`‚µ‚Ä,’ÊMƒGƒ‰[‚ð’T‚·
		4.	Œ©‚Â‚©‚ê‚Î,Žw’ès‚ðƒoƒbƒtƒ@‚ÉƒZƒbƒg‚·‚é (‚Ts)
	]
	common		:[]
	condition	:[]
	commment	:[
		Print_CommErr_ChkMsg_Common()‚ð•ÏX
	]
	return		:[
		0	ŽŸƒf[ƒ^‚È‚µ
		1	’Êíƒ‰ƒCƒ“
		2	ƒGƒ‰[ƒy[ƒWs‚È‚µ
		3	ƒGƒ‰[ƒy[ƒWs‚Ì‘±‚«‚ ‚è
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1995/02/15]
	author		:[’|“à–ÎŽ÷]
*************************************************************************/
UBYTE		Set_CommErr_ChkMsg(
	UBYTE	kind,			/*	REPORT_TITLE / REPORT_MESSAGE	*/
	UBYTE	*chr_buffer,	/*	ƒLƒƒƒ‰ƒNƒ^“WŠJƒoƒbƒtƒ@	*/
	UBYTE	*atr_buffer,	/*	ƒAƒgƒŠƒrƒ…[ƒgƒoƒbƒtƒ@	*/
	UBYTE	line)			/*	“WŠJ‚·‚és	*/
{
	UBYTE	rule_no;	/*	ŒrüŽí‚Ì”Ô†	*/
	UBYTE	ret_value;	/*	ƒŠƒ^[ƒ“’l (0=ŽŸƒf[ƒ^‚È‚µ / 1=ŽŸƒf[ƒ^‚ ‚è / 2=ƒGƒ‰[ƒy[ƒW‚ÌŽŸs‚ ‚è)	*/

	ret_value = 1;

	if (kind == REPORT_TITLE) {		/**	ƒ^ƒCƒgƒ‹•”	*/
		/**	ƒ^ƒCƒgƒ‹•”‚ðì‚Á‚ÄƒŠƒ^[ƒ“	*/
		Set_ChkMsg_Head( chr_buffer, atr_buffer, line );
		return (1);
	}

	if (line == 1) {	/**	‚PŒ‚²‚Æ‚ÌÅ‰‚Ìƒ‰ƒCƒ“‚È‚ç	*/
		if (ChkMsgEmptyRecordFlag) {
			return (0);
		}
		ChkMsgCurrentQueueNo = ChkMsgNextQueueNo;
		SearchNextRelayedError( &ChkMsgCurrentQueueNo );	/**	’ÊMƒGƒ‰[‚ÌƒLƒ…[‚ð’T‚·	*/
		if (ChkMsgCurrentQueueNo == SYS_EXEC_QUEUE_MAX) {	/**	ExecQueue‚Éƒf[ƒ^‚È‚µ	*/
			if (ChkMsgNextQueueNo == 0) {						/**	ˆêŒ‚à‚È‚¢	*/
				ChkMsgEmptyRecordFlag = 1;							/**	‹ó‚Ìƒ`ƒFƒbƒNƒƒbƒZ[ƒW—pƒtƒ‰ƒO‚ð—§‚Ä‚é	*/
			}
			else {
				return (0);											/**	ŽŸƒf[ƒ^‚È‚µ‚ÅƒŠƒ^[ƒ“	*/
			}
		}
		/**	ŒŸõƒLƒ…[‚Ì”Ô†‚ði‚ß,’ÊMƒGƒ‰[ƒy[ƒWs‚ð‰Šú‰»	*/
		ChkMsgNextQueueNo = ChkMsgCurrentQueueNo + 1;
		ChkMsgErrPageNo = 1;
		ChkMsgErrPage1stLine = 1;
	}

	/**	“WŠJ‚·‚és‚©‚çŒrüŽí‚Ì”Ô†‚ðƒZƒbƒg	*/
	if (line == 3) {
		rule_no = line;
	}
	else {
		rule_no = (UBYTE)(line - 1);
	}

	switch (line) {

	case	1:	/* †®†¢†Î†¢†¢†¢†¢†Î†¢†¢†¢†¢†² */
	case	2:	/* †¤@†¤@@@@†¤@@@@†¤ */
	case	3:	/* †¶†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†¢†¢†º */
		/**	Œrü‚ðˆø‚­	*/
		Print_CommErr_ChkMsg_Line( rule_no, chr_buffer, atr_buffer );
		/**	‚Qs–Ú‚È‚ç’†g‚ðì‚é	*/
		if ((!ChkMsgEmptyRecordFlag) && (line == 2)) {
			Set_CommErr_MessageLine( ChkMsgCurrentQueueNo, chr_buffer, atr_buffer );
		}
		break;

	case	4:
		/**	ƒoƒbƒtƒ@‚ðƒNƒŠƒA‚µ‚Ä,ƒGƒ‰[ƒy[ƒW‚Ìs‚ðì‚é	*/
		Prn_Att_Str_Clear( chr_buffer, atr_buffer );
		if ((!ChkMsgEmptyRecordFlag) && ((SYB_ExecQueue[ChkMsgCurrentQueueNo].Result & DIALERROR) == TRANSMITERROR)) {
			ret_value = Set_ChkMsg_ErrorPages( &SYB_ExecQueue[ChkMsgCurrentQueueNo].ErrorPage[0], SYS_ERROR_PAGE,
												 chr_buffer, atr_buffer );
		}
		else {
			ret_value = 3;	/* ƒGƒ‰[ƒy[ƒWs‚È‚µ */
		}
		break;

	case	5:
	default:
		/**	ƒoƒbƒtƒ@‚ðƒNƒŠƒA‚µ‚Ä‹ó”’s‚É‚·‚é	*/
		Prn_Att_Str_Clear( chr_buffer, atr_buffer );
		break;
	}

	return ( ret_value );
}


/*************************************************************************
	module		:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWƒ^ƒCƒgƒ‹ì¬]
	function	:[
		1.	ƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚Ìƒ^ƒCƒgƒ‹‚ðì¬‚·‚é
		2.	Žw’ès‚ðŽw’è‚³‚ê‚½ƒoƒbƒtƒ@‚ÉƒZƒbƒg‚·‚é
		3.	s‚Í‚P`‚U‚ÅŽw’è‚·‚é
	]
	common		:[]
	condition	:[]
	commment	:[
		Print_ChkMsg_Head()‚ð•ÏX
		†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²
		†¤@@ƒ`ƒFƒbƒNƒƒbƒZ[ƒW@@†¤
		†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º
		@@@@@@@@@@“ú•t,Žž ©‚Í‚s‚s‚h‚Æƒ_ƒu‚é‚Ì‚Å‚È‚µI
	]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1995/02/15]
	author		:[’|“à–ÎŽ÷]
*************************************************************************/
void		Set_ChkMsg_Head(
	UBYTE	*chr_buffer,	/*	ƒLƒƒƒ‰ƒNƒ^“WŠJƒoƒbƒtƒ@	*/
	UBYTE	*atr_buffer,	/*	ƒAƒgƒŠƒrƒ…[ƒgƒoƒbƒtƒ@	*/
	UBYTE	line)			/*	“WŠJ‚·‚és	*/
{
	/**	ƒLƒƒƒ‰ƒNƒ^ƒoƒbƒtƒ@‚ÆƒAƒgƒŠƒrƒ…[ƒgƒoƒbƒtƒ@‚ðƒNƒŠƒA	*/
	Prn_Att_Str_Clear( chr_buffer, atr_buffer );

	switch (line) {

	case	2:
	case	4:
		CMN_MemorySet( (chr_buffer + 26-1), 30, LST_KLINE_ );
		if (line == 2) {
			/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
			*(chr_buffer + 25-1) = LST_KLINE7;
			*(chr_buffer + 56-1) = LST_KLINE9;
		}
		else {
			/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
			*(chr_buffer + 25-1) = LST_KLINE1;
			*(chr_buffer + 56-1) = LST_KLINE3;
		}
		break;

	case	3:
		/*†¤@@ƒ`ƒFƒbƒNƒƒbƒZ[ƒW@@†¤*/
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )	/* by H.Hirao 1999/01/13 */
		AttributeSet( (chr_buffer + 28-1),
		              (atr_buffer + 28-1),
		              PWRD_CheckMessage_K, LST_NOT );
#else
		AttributeSet( (chr_buffer + 28-1),
					  (atr_buffer + 28-1),
					  PWRD_CheckMessage, LST_MES_TWI_XXX );
#endif
		*(chr_buffer + 25-1) = LST_KLINEI;
		*(chr_buffer + 56-1) = LST_KLINEI;
		break;

	case	6:
		/* “ú•t,Žž */
		TimeDataAscii( OFF, SYB_CurrentTime, chr_buffer + 60-1, 0 );
		break;

	default:	/* ‚Ps–ÚC‚Ts–Ú */
		/**	‚»‚Ì‚Ü‚Ü(‹ó”’s)	*/
		break;
	}

	ChkMsgNextQueueNo = 0;		/**	ŒŸõ‚·‚éExecQueue”Ô†‚ð‰Šú‰»	*/
	ChkMsgEmptyRecordFlag = 0;
}


/*************************************************************************
	module		:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWsì¬]
	function	:[
		ƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚Ì“à—e‚ðŽw’èƒoƒbƒtƒ@‚ÉƒZƒbƒg‚·‚é
	]
	common		:[
		SYB_ExecQueue		SYB_CommandFile
	]
	condition	:[]
	commment	:[
		Print_CommErr_ChkMsg_Specifi()‚ð•ÏX
	]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1995/02/15]
	author		:[’|“à–ÎŽ÷]
*************************************************************************/
void		Set_CommErr_MessageLine(
	UWORD	Number,			/*	ExecQueue‚Ì”Ô†	*/
	UBYTE	*chr_buffer,		/*	ƒLƒƒƒ‰ƒNƒ^“WŠJƒoƒbƒtƒ@	*/
	UBYTE	*atr_buffer)		/*	ƒAƒgƒŠƒrƒ…[ƒgƒoƒbƒtƒ@	*/
{
	UBYTE	spd_no_digit;	/*	’Zkƒ_ƒCƒ„ƒ‹”Ô†‚ÌŒ…”	*/

	/**	ƒGƒ‰[ƒR[ƒh	*/
	CommunicationResultName( SYB_ExecQueue[Number].Result, LST_NAME_SHORT, LST_RESULT_COMMON,
							 (chr_buffer + 2-1),
							 (atr_buffer + 2-1) );

	/**	ƒƒbƒZ[ƒW	*/
	CommunicationResultName( SYB_ExecQueue[Number].Result, LST_NAME_LONG, LST_RESULT_COMMON,
							 (chr_buffer + 9-1),
							 (atr_buffer + 9-1) );

	/**	ƒ_ƒCƒ„ƒ‹”Ô†	*/
	switch ( SYB_ExecQueue[Number].ExecDial.Item ) {

	case SYS_DIRECT_DIAL:
		CMN_BCD_ToASC_String( (chr_buffer + 40-1),
							  SYB_CommandFile[SYB_ExecQueue[Number].Number.Command]
							  .DialNumber.Direct[SYB_ExecQueue[Number].ExecDial.ExecNumber.Command] );
		break;

	case SYS_ONETOUCH_DIAL:
#if (PRO_PANEL == ANK)
		*(chr_buffer + 40-1) = '[';
		*(chr_buffer + 41-1) = CMN_OffsetToOnetouchCode( SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch );
		*(chr_buffer + 42-1) = ']';
#endif
#if (PRO_PANEL == KANJI)
 		/* ƒƒ“ƒ^ƒbƒ`‚Ì•\Ž¦‚ð[]->ŠG•¶Žš‚É•ÏX By O.Kimoto 1998/01/22 */
		*(chr_buffer + 40-1) = LCD_PICFONT;
		*(chr_buffer + 41-1) = LCD_PICFONT_LOWER;
		*(chr_buffer + 42-1) = CMN_OffsetToOnetouchCode( SYB_ExecQueue[Number].ExecDial.ExecNumber.Onetouch );
#endif
		break;

	case SYS_SPEED_DIAL:
		if ( SYS_SPEED_DIAL_MAX + SYS_2ND_SPEED_DIAL_MAX >= 100 ) {
#if (1) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
			spd_no_digit = OP_SPEED_FIGURE_MAX;
#else
//			spd_no_digit = 3;
#endif
		}
		else {
			spd_no_digit = 2;
		}
		*(chr_buffer + 40-1) = '(';
		if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
			if (GetRecordFromNumber( (UWORD)SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed ) != 0xFFFF) {
				CMN_UnsignedIntToASC( (chr_buffer + 41-1),
									  GetRecordFromNumber( (UWORD)SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed ),
									  spd_no_digit, '0' );
			}
			else {
				CMN_MemorySet( &List.S.Print[41-1], spd_no_digit, '*' );
			}
		}
		else{	/* ’Êí‚Ì’Zk‚ÌŽž */
			CMN_UnsignedIntToASC( (chr_buffer + 41-1),
								  (UWORD)(SYB_ExecQueue[Number].ExecDial.ExecNumber.Speed + OPR_SPEED_DIAL_MIN),
								  spd_no_digit, '0' );
		}
		*(chr_buffer + 41-1 + spd_no_digit) = ')';
		break;
	}
}


/*************************************************************************
	module		:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚ÌƒGƒ‰[ƒy[ƒWsì¬]
	function	:[
		ƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚ÌƒGƒ‰[ƒy[ƒWs‚ðCŽw’è‚³‚ê‚½ƒoƒbƒtƒ@‚ÉƒZƒbƒg‚·‚é
	]
	common		:[]
	condition	:[]
	commment	:[
		Print_ChkMsg_ErrorPages()‚ð•ÏX
	]
	return		:[
		1	ƒGƒ‰[ƒy[ƒWs‚ÌŽŸƒ‰ƒCƒ“‚È‚µ
		2	ƒGƒ‰[ƒy[ƒWs‚ÌŽŸƒ‰ƒCƒ“‚ ‚è
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1995/02/15]
	author		:[’|“à–ÎŽ÷]
*************************************************************************/
UBYTE	Set_ChkMsg_ErrorPages(
	UBYTE	*ptr_err_page,	/*	ƒGƒ‰[ƒy[ƒWƒf[ƒ^	*/
	UBYTE	err_page_size,	/*	ƒGƒ‰[ƒy[ƒWƒoƒbƒtƒ@ƒTƒCƒY	*/
	UBYTE	*chr_buffer,		/*	ƒLƒƒƒ‰ƒNƒ^“WŠJƒoƒbƒtƒ@	*/
	UBYTE	*atr_buffer)		/*	ƒAƒgƒŠƒrƒ…[ƒgƒoƒbƒtƒ@	*/
{
	UBYTE	err_page_byte;	/*	*ptr_err_page‚ÌƒoƒCƒgˆÊ’u	*/
	UBYTE	mask;			/*	ƒGƒ‰[ƒrƒbƒg‚Ìƒ}ƒXƒNƒpƒ^[ƒ“	*/
	UBYTE	column;			/*	ƒLƒƒƒ‰ƒNƒ^ƒoƒbƒtƒ@‚ÌˆÊ’u	*/
	UBYTE	ret_value;		/*	ƒŠƒ^[ƒ“Žž‚ÌŽŸƒ‰ƒCƒ“‚Ì—L–³	*/
	UBYTE	err_page_init;	/*		*/
	UBYTE	f_err_page;		/*		*/

	mask = 0x01;
	column = 0;
	ret_value = 1;

	/**	‚Qs–ÚˆÈ~‚ÌƒGƒ‰[ƒy[ƒW‚ðl—¶‚µ‚Äƒ|ƒCƒ“ƒ^‚ðƒZƒbƒg	*/
	ptr_err_page += (ChkMsgErrPageNo - 1) / 8;
	err_page_byte = (UBYTE)((ChkMsgErrPageNo - 1) / 8);
	err_page_init = ChkMsgErrPageNo;
	f_err_page = 0;

	while ( 1 ) {
		if (*ptr_err_page & mask) {	/**	ƒGƒ‰[ƒy[ƒW‚ ‚è	*/
			f_err_page = 1;

			switch (column) {
			case	0:
				/**	ƒGƒ‰[ƒy[ƒWs‚Ì‚Ps–Ú‚¾‚¯"<Error Pages>:"‚ð‘‚­	*/
				if (ChkMsgErrPage1stLine) {
					AttributeSet( (chr_buffer + 2-1), (atr_buffer + 2-1), PWRD_ErrorPages, LST_NOT );
					ChkMsgErrPage1stLine = 0;
				}
				column = 16;
				break;
			case	16:
				break;
			default:
				*(chr_buffer + column) = ',';
				column++;
				break;
			}

			/**	ƒy[ƒW”Ô†‚ðƒZƒbƒg	*/
			if ( ChkMsgErrPageNo < 100 ) {
				CMN_UnsignedIntToASC( (chr_buffer + column), (UWORD)ChkMsgErrPageNo, 2, ' ' );
				column += 2;
			}
			else {
				CMN_UnsignedIntToASC( (chr_buffer + column), (UWORD)ChkMsgErrPageNo, 3, ' ' );
				column += 3;
			}

			if ( column > 74 ) {	/**	‚Ps•ªƒZƒbƒg‚µ‚½	*/
				/**	ŽŸƒ‰ƒCƒ“‚É‘‚­‚×‚«ƒGƒ‰[ƒ‰ƒCƒ“‚Ì—L–³‚ðƒ`ƒFƒbƒN	*/
				mask = 0xFF;		/* ƒ}ƒXƒNƒpƒ^[ƒ“‚ð‰Šú‰» */
				if (ChkMsgErrPageNo % 8) {
					mask <<= (ChkMsgErrPageNo % 8);
				}
				else {
					err_page_byte++;
				}

				/* ‚PƒoƒCƒg’PˆÊ‚Åƒ`ƒFƒbƒN‚·‚é */
				while (err_page_byte < err_page_size) {
					if (*ptr_err_page & mask) {
						ret_value = 2;			/* ŽŸƒ‰ƒCƒ“‚ ‚è */
						break;
					}
					err_page_byte++;
					mask = 0xFF;
				}

				ChkMsgErrPageNo++;
				return ( ret_value );
				break;
			}
		}

		/**	ƒ}ƒXƒNƒpƒ^[ƒ“‚ðXV	*/
		if ( mask == 0x80 ) {
			mask = 0x01;
			err_page_byte++;
			ptr_err_page++;
			if ( err_page_byte >= err_page_size ) {
				break;
			}
		}
		else {
			mask <<= 1;
		}

		ChkMsgErrPageNo++;
	}

	if ((err_page_init == 1) && (!f_err_page)) {	/**	ƒGƒ‰[ƒy[ƒW‚È‚µ	*/
		ret_value = 3;
	}

	return ( ret_value );
}


/*************************************************************************
	module		:[ŽŸ‚Ì’†Œp”zMƒGƒ‰[‚ÌExecQueue‚ðƒT[ƒ`n
	function	:[
		Žw’è‚³‚ê‚½ExecQueue”Ô†ˆÈ~‚©‚ç,Œ»ÝŽÀs’†‚Ì’†Œp”zMCommandFile
		‚ÌQueue‚Å,ŽÀsŒ‹‰Ê‚ª’ÊMƒGƒ‰[‚ÌQueue‚ð’T‚·
	]
	common		:[
		SYB_ExecQueue:
	]
	condition	:[
		exec_queue_no
		ƒf[ƒ^ƒGƒ“ƒh->EXEC_QUEUE_MAX
	]
	commment	:[
		ExecQueueNextSearch()‚ð•ÏX
	]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1995/02/15]
	author		:[’|“à–ÎŽ÷]
*************************************************************************/
void		SearchNextRelayedError(
	UWORD *	exec_queue_no)	/*	ExecQueue”Ô†	*/
{
	UWORD	i;	/*	loop counter	*/
	UBYTE	relay_comfile_no;

	/**	’†Œp”zM‚ÌƒRƒ}ƒ“ƒhƒtƒ@ƒCƒ‹ƒiƒ“ƒo[‚ðŽæ“¾	*/
	relay_comfile_no = 
		SYB_CommandFile[SYS_CurrentExecutingCommand->Number.Command].Option.OptionNumber.RelaySourceID[0];

	for (i = *exec_queue_no; i < SYS_EXEC_QUEUE_MAX; i++) {
		if ((SYB_ExecQueue[i].Number.Command == relay_comfile_no)	/* ’†Œp”zM‚ÌƒRƒ}ƒ“ƒhƒtƒ@ƒCƒ‹ && */
		&&	(SYB_ExecQueue[i].Status == SYS_EXEC_ERROR)) {			/* ŽÀsŒ‹‰Ê‚ªƒGƒ‰[‚ÌƒLƒ…[ */
			*exec_queue_no = i;
			break;
		}
	}

	if (i == SYS_EXEC_QUEUE_MAX) {
		*exec_queue_no = SYS_EXEC_QUEUE_MAX;
	}
}

#endif	/* PRO_RELAYED_REPORT  ’|“à Feb.14.1995 */

#if defined (KEISATSU) /* ŒxŽ@FAX DVT_ID2 Added by SMuratec —› 2005/11/10 */
/*************************************************************************
	module		:[‹­§’†’fƒ`ƒFƒbƒNƒƒbƒZ[ƒWˆóü]
	function	:[‹­§’†’fƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚ðˆóü‚·‚é]
	common		:[
		SYS_DocumentPrintNo	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[2005/11/10]
	author		:[SMuratec —›]
*************************************************************************/
WORD				Print_ForceStopComm_ChkMsg(
						 void )				/*‚È‚µ*/
{
	UBYTE	i;					/*loop*/
	UBYTE	page;				/*Íß°¼Þ*/
	UBYTE	line_cnt;			/*Žc‚èˆóü‰Â”\s”*/
	UBYTE	exec_cnt;			/*ExecQueue¶³ÝÄ*/
	UBYTE	prn_mode;			/*ˆóüÓ°ÄÞ*/
	UBYTE	wk[6];			/*Œ‹‰Êº°ÄÞ*/
										/*LST_ERR_CLOSE_NOT ´×°close‚µ‚È‚¢*/
										/*LST_ERR_CLOSE		´×°close‚·‚é*/
	register WORD	ret;				/*ŽÀsŒ‹‰Ê*/

	CMN_MemorySet( wk, 5, ' ' );
	prn_mode = LST_ERR_CLOSE;
	page = 1;
	exec_cnt = 0;

	line_cnt = (UBYTE)(PaperSizeLen() - 7);/*ˆóü‰Â”\s”¾¯Ä*/
	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}
	if (FaxComTXorRX_Flag == RX_COM_MODE) {
		wk[0] = 'R';
	}
	else {
		wk[0] = 'T';
	}
	
	FaxComTXorRX_Flag = 0;
	
	wk[1] = '.';
	wk[2] = '9';
	wk[3] = '.';
	wk[4] = '1';
	wk[5] = NULL;

	LST_CharacterLine = 0;	/**	ƒLƒƒƒ‰ƒNƒ^ˆóŽš•”‚Ìƒ‰ƒCƒ“”‚ÌƒNƒŠƒA	Add By Hirao 98/01/06 */

	if ( (ret = Print_Err_ChkMsg_Head( 0, page, LST_COMMERR_CHECKMSG ) ) != OK ) {	/*Í¯ÀÞˆóü*/
		return ( ret );
	}

	/*†®†¢†Î†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†²*/
	Print_CommErr_ChkMsg_Line( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
		return ( ret );
	}
	Print_CommErr_ChkMsg_Line( 1, List.S.Print, List.S.Attribute );
	
	CMN_StringCopyNum( &List.S.Print[2-1],	wk, CMN_StringLength(wk));
	
	AttributeSet( &List.S.Print[9-1], &List.S.Attribute[9-1], &PWRD_ResultName[7][0], LST_NOT );
	
	if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
		return ( ret );
	}
	
	/*†¶†¢†Ö†¢†¢†¢†Ö†¢†¢†¢†¢†¢†º*/
	Print_CommErr_ChkMsg_Line( 3, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
		return ( ret );
	}
	line_cnt -= 3;
	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( (UBYTE)(LST_LINE_FEED+prn_mode+1) )) != OK ) {
		return ( ret );
	}
	line_cnt--;
	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}

	return ( OK );
}
#endif /* defined (KEISATSU) */
