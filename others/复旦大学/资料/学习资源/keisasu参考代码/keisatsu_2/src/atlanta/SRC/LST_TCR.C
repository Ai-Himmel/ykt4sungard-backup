/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_TCR.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ‘—MØ
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\mlt_pro.h"	/* ’Ç‰Á By O.Kimoto 1997/06/27 */
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\uni_pro.h"	/* Add By M.Kuwahara 97/09/08 */
#include	"\src\atlanta\define\sysprint.h"/* ’Ç‰Á	1998/10/28 Y.Matsukuma */

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_v\sys_data.h"

#include	"\src\memsw\define\mems_pro.h"

#if (PRO_PANEL == ANK)
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#endif

#if (PRO_PANEL == KANJI)
#include	"\src\atlanta\opr\kanji\define\opr_def.h"
#endif

#if (PRO_OKI == ENABLE)	/* by K.Watanabe 1999/02/09 */
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#endif
/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* ’†‘—X­‹Ç“ÁROM By O.Kimoto 2001/01/22 */
#include	"\src\atlanta\ext_v\ini_tbl.h"
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 2003/03/10 H.Yoshikawa */
#include "\src\atlanta\sakaki\define\gaio_pro.h"
#endif

UBYTE		TxConfYearPrint;		/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16	*/
									/* ICHOU‚©‚çˆÚA‚µ‚Ä‚«‚Ü‚µ‚½		*/

/*************************************************************************
	module		:[‘—MØˆóü]
	function	:[‘—MØ‚ðˆóü‚·‚é]
	common		:[
		List				:
		SYB_JournalFile		:
		SYB_TxJournalFile	:
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
#if ( PRO_TCR_PRINT == ENABLE )	/* MILAN‚ÍDISABLE */
WORD					Print_TxConf_List(
						 void )				/*‚È‚µ*/
{
	UBYTE	i;						/*loop*/
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	for ( i = 0; i < SYS_JOURNAL_MAX; i++ ) {
#if ( PRO_JOURNAL == SEPARATE )
		if ( (SYB_TxJournalFile[i].Option & SYS_TCR_REQUEST) == SYS_TCR_REQUEST ) {
			if ( (ret = Print_TxConf_One_List( i )) != OK ) {/*1•Åˆóü*/
				return ( ret );
			}
			/*SYB_TxJournalFile[i].Option &= !SYS_TCR_REQUEST;*/
			SYB_TxJournalFile[i].Option &= ~SYS_TCR_REQUEST;	/* By M.Tachibana 1997/01/29 */
		}
#else
		if ( (SYB_JournalFile[i].Option & SYS_TCR_REQUEST) == SYS_TCR_REQUEST ) {
			if ( (ret = Print_TxConf_One_List( i )) != OK ) {/*1•Åˆóü*/
				return ( ret );
			}
			/*SYB_JournalFile[i].Option &= !SYS_TCR_REQUEST;*/
			SYB_JournalFile[i].Option &= ~SYS_TCR_REQUEST;	/* By M.Tachibana 19967/01/29 */
		}
#endif
	}
	return ( OK );
}

/*************************************************************************
	module		:[‘—MØ‚P•Åˆóü]
	function	:[‘—MØ‚Ì‚P•Å•ª‚ðˆóü‚·‚é]
	common		:[
		List	:
		SYB_TTI_Buffer	:
		SYB_ID_Buffer	:
		SYB_JournalFile	:
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
WORD					Print_TxConf_One_List(
						 UBYTE TxJnNb )		/*‘—Mƒtƒ@ƒCƒ‹”Ô†*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/
	
	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs*/
	if ( (ret = TTI_ID_Print_Feed()) != OK ) {
		return ( ret );
	}

	/*––@ƒ\ƒEƒVƒ“ƒVƒ‡ƒE@––*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1],
		  PWRD_TransConfReport_K, LST_NOT );
#else
	AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1],
	  PWRD_TransConfReport, LST_XXX_TWI_XXX );
#endif
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/*Œ»ÝŽžŠÔ*/
	if ( (ret = CurrentTimePrint( 47-1 )) != OK ) {
		return ( ret );
	}

	/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
	Print_Conf_List_Line( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¤ ”­MŒ³–¼ ---> ”­Mæ–¼†¤*/
	Print_Conf_List_Line( 1, List.S.Print, List.S.Attribute );

/* ‚o‚n‚o‚k‚`‚qQ‚g •W€‚Q‰ñüŽû—e‘Î‰ž‚Ìˆ× By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
	if ( SYB_TTI_Buffer[0][0] != NULL ) {
		CMN_StringCopy( &List.S.Print[16-1], &SYB_TTI_Buffer[0][0]);
	}
#else
	if ( SYB_TTI_Buffer[0] != NULL ) {
		CMN_StringCopy( &List.S.Print[16-1], SYB_TTI_Buffer);
	}
#endif

	else {

/* ‚o‚n‚o‚k‚`‚qQ‚g •W€‚Q‰ñüŽû—e‘Î‰ž‚Ìˆ× By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
		CMN_StringCopy( &List.S.Print[16-1], &SYB_ID_Buffer[0][0]);
#else
		CMN_StringCopy( &List.S.Print[16-1], SYB_ID_Buffer);
#endif

	}
	AttributeSet( &List.S.Print[38-1], &List.S.Attribute[38-1], PWRD_FromTo,
	  LST_NOT );
	  
#if ( PRO_JOURNAL == SEPARATE )
	CMN_StringCopy( &List.S.Print[44-1], SYB_TxJournalFile[TxJnNb].RemoteID_TTI );
#else
	CMN_StringCopy( &List.S.Print[44-1], SYB_JournalFile[TxJnNb].RemoteID_TTI );
#endif
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¾†¢†¢†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†Æ*/
	Print_Conf_List_Line( 2, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¤ Â³¼ÝÊÞÝºÞ³@†¤999		   †¤*/
	Print_Conf_List_Line( 3, List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[16-1], &List.S.Attribute[16-1], PWRD_CommNo,
	  LST_NOT );
#if ( PRO_JOURNAL == SEPARATE )
	CMN_UnsignedIntToASC( &List.S.Print[36-1],
	  (UWORD)SYB_TxJournalFile[TxJnNb].Number, 3, '0' );
#else
	CMN_UnsignedIntToASC( &List.S.Print[36-1],
	  (UWORD)SYB_JournalFile[TxJnNb].Number, 3, '0' );
#endif
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¾†¢†¢†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Æ*/
	Print_Conf_List_Line( 4, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¤ Â³¼ÝÓ°ÄÞ@†¤XXXXXXXX	  †¤*/
	Print_Conf_List_Line( 3, List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[16-1], &List.S.Attribute[16-1], PWRD_CommMode,
	  LST_NOT );
#if ( PRO_JOURNAL == SEPARATE )
	CommunicationModeName( SYB_TxJournalFile[TxJnNb].Mode, &List.S.Print[36-1],
	  &List.S.Attribute[36-1] );
#else
	CommunicationModeName( SYB_JournalFile[TxJnNb].Mode, &List.S.Print[36-1],
	  &List.S.Attribute[36-1] );
#endif
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	if ( CHK_TCR_TimePrint() != 0 ) {
		/*†¾†¢†¢†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Æ*/
		Print_Conf_List_Line( 4, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*†¤ Â³¼Ý¼Þ¶Ý@†¤Z9'99"    †¤*/
		Print_Conf_List_Line( 3, List.S.Print, List.S.Attribute );
		AttributeSet( &List.S.Print[16-1], &List.S.Attribute[16-1],
		  PWRD_CommStartTime, LST_NOT );
#if ( PRO_JOURNAL == SEPARATE )
		SecondToMinuteSecondAsc( SYB_TxJournalFile[TxJnNb].TotalTime,
		  List.S.Work, 0 );
#else
		SecondToMinuteSecondAsc( SYB_JournalFile[TxJnNb].TotalTime,
		  List.S.Work, 0 );
#endif
		CMN_StringCopy( &List.S.Print[36-1], List.S.Work );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}

	/*†¾†¢†¢†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Æ*/
	Print_Conf_List_Line( 4, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¤ Â³¼ÝÏ²½³@†¤zz9Íß°¼Þ	 †¤*/
	Print_Conf_List_Line( 3, List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[16-1], &List.S.Attribute[16-1], PWRD_CommPages,
	  LST_NOT );
#if ( PRO_JOURNAL == SEPARATE )
	CMN_UnsignedIntToASC_NULL( List.S.Work,
	  (UWORD)SYB_TxJournalFile[TxJnNb].Page, 0 , 0 );
#else
	CMN_UnsignedIntToASC_NULL( List.S.Work,
	  (UWORD)SYB_JournalFile[TxJnNb].Page, 0 , 0 );
#endif
	CMN_StringCopy( &List.S.Print[36-1], List.S.Work );
	AttributeSet( &List.S.Print[36-1+CMN_StringLength(List.S.Work)+1],
	  &List.S.Attribute[36-1+CMN_StringLength(List.S.Work)+1], PWRD_Pages,
	  LST_NOT );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¾†¢†¢†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Æ*/
	Print_Conf_List_Line( 4, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¤ Â³¼Ý¹¯¶@†¤XXXXXXXX	 †¤*/
	Print_Conf_List_Line( 3, List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[16-1], &List.S.Attribute[16-1], PWRD_CommResult,
	  LST_NOT );
#if ( PRO_JOURNAL == SEPARATE )
	CommunicationResultName( SYB_TxJournalFile[TxJnNb].Result, LST_NAME_SHORT,
	  LST_RESULT_TX_CONF, &List.S.Print[36-1], &List.S.Attribute[36-1] );
#else
	CommunicationResultName( SYB_JournalFile[TxJnNb].Result, LST_NAME_SHORT,
	  LST_RESULT_TX_CONF, &List.S.Print[36-1], &List.S.Attribute[36-1] );
#endif
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¶†¢†¢†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†º*/
	Print_Conf_List_Line( 5, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	if ( CHK_TCR_TimePrint() != 0 ) {
		/*‚QsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED +2 )) != OK ) {
			return ( ret );
		}
	}
	else {
		/*‚SsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED +4 )) != OK ) {
			return ( ret );
		}
	}
	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	return ( OK );
}
#endif

/*************************************************************************
	module		:[‘—MØˆóü]
	function	:[Œ´e•t‚«‘—MØA–”‚ÍŒ´e–³‚µ‘—MØ‚ðˆóü‚·‚é]
	common		:[]
	condition	:[]
	commment	:[Žè“®‘—M‘—MØ‚Í‚±‚±‚ÅˆóŽš‚µ‚È‚¢]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[Apr.17,1996]
	author		:[•½”ö ‰p“T]
*************************************************************************/
WORD		 		Print_TxConf(
							UBYTE prn_mode )		/** ˆóüÓ°ÄÞ */
														/* LST_ERR_CLOSE_NOT ´×°close‚µ‚È‚¢ */
														/* LST_ERR_CLOSE		´×°close‚·‚é */
{
	UBYTE 	page;				/** Íß°¼Þ */
#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/4 K.Kawata  */
	UBYTE	line_feed_flag;	/* ‰üs‚·‚é */
	UBYTE	title_flag;	/* ƒ^ƒCƒgƒ‹‚ð‘‚­ */
	UBYTE	error_flag;	/* VÄ‘—ƒƒbƒZ[ƒW‚Ì‰ºü‚ð‘‚­ */
	UBYTE	line_number;
#endif
	UBYTE 	line_cnt;				/** Žc‚èˆóü‰Â”\s” */
	UBYTE 	exec_cnt;			/** ExecQueue¶³ÝÄ */
	UBYTE	flag;
	register WORD	ret;					/** ŽÀsŒ‹‰Ê */

#if (PRO_JOURNAL_PRINT_TIME == DISABLE)	/* “ú—§“Á‹–‰ñ”ð 1998/10/28 Y.Matsukuma */
	UDWORD	time;
#endif

	/* ˆÈ‰º‚Ws’Ç‰Á By O.Kimoto 1997/06/27 */
	UBYTE	line_max;

	TxConfYearPrint = CHK_JournalYearPrint();	/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16	*/
												/* ICHOU‚©‚çˆÚA‚µ‚Ä‚«‚Ü‚µ‚½		*/

#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^Ž—‚Q‰ñüŽd—l by T.Soneoka 1997/03/11 */
 #if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/4 K.Kawata */
	line_max = 5;
 #else
	line_max = 7;	/* “ñ‰ñüˆÈã‚ÌŽž‚ÍAƒ‰ƒCƒ“”Ô†ˆóŽš‚Ì‚½‚ß‚P‚Ó‚¦‚é */
 #endif
#else
 #if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/4 K.Kawata */
	line_max = 5;
 #else
	if (OPT_CountModems() < 2) {
		line_max = 6;	/* ˆê‰ñü‚ÌŽž‚ÍAƒ‰ƒCƒ“”Ô†‚ðˆóŽš‚µ‚È‚¢‚½‚ß */
	}
	else {
		line_max = 7;	/* “ñ‰ñüˆÈã‚ÌŽž‚ÍAƒ‰ƒCƒ“”Ô†ˆóŽš‚Ì‚½‚ß‚P‚Ó‚¦‚é */
	}
 #endif
#endif
	page = 1;
#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/4 K.Kawata */
	line_feed_flag = 0;
	title_flag = 1;
	line_number = 0;
#endif
	exec_cnt = 0;
	flag = 1;

#if (PRO_JOURNAL_PRINT_TIME == DISABLE)	/* “ú—§“Á‹–‰ñ”ð 1998/10/28 Y.Matsukuma */
	time = TranceTime();
#endif

	while ( exec_cnt != SYS_EXEC_QUEUE_MAX ) {
		if ( (prn_mode == LST_ERR_CLOSE) || ((prn_mode == LST_ERR_CLOSE_NOT) && (page != 1)) ) {
			if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
				return ( ret );
			}
		}

		LST_CharacterLine = 0;	/**	ƒLƒƒƒ‰ƒNƒ^ˆóŽš•”‚Ìƒ‰ƒCƒ“”‚ÌƒNƒŠƒA	*/

		if ( page == 1 ) {
#if (PRO_JOURNAL_PRINT_TIME == DISABLE)	/* “ú—§“Á‹–‰ñ”ð 1998/10/28 Y.Matsukuma */
			if ( (ret = Print_TxConf_Head( prn_mode, time )) != OK ) {		/** Í¯ÀÞˆóü */
#else
			if ( (ret = Print_TxConf_Head( prn_mode )) != OK ) {		/** Í¯ÀÞˆóü */
#endif
				return ( ret );
			}
			line_cnt = (UBYTE)(PaperSizeLen() - 7);	/** ˆóü‰Â”\s”¾¯Ä */
		} else {
			line_cnt = (UBYTE)(PaperSizeLen() - 2);	/** ˆóü‰Â”\s”¾¯Ä */
			if ( (ret = CharacterPrint( (UBYTE)(LST_LINE_FEED+prn_mode) )) != OK ) {
					return ( ret );
			}
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[1] = 'P';	/** ƒy[ƒW‚ðˆóŽš */
			List.S.Print[2] = '.';
			CMN_UnsignedIntToASC( &List.S.Print[3], (UWORD)page, 0, 0 );
			if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
				return ( ret );
			}
		}

		while ( 1 ) {
			ExecQueueNextSearch( &exec_cnt );					/** ŽŸÃÞ°À»°Á */

#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/4 K.Kawata */
			if (OPT_CountModems() >= 2) {
				if (exec_cnt == SYS_EXEC_QUEUE_MAX) {
					if (line_number != OPT_CountModems()+1) {
						line_number++;
						if (title_flag == 0) {
							line_feed_flag = 1;
							title_flag = 1;
						}
						exec_cnt = 0;
						continue;
					}
				}
				else {
					if ((SYB_ExecQueue[exec_cnt].StackNumber == 0xFF && line_number == OPT_CountModems()+1)
					 || (SYB_ExecQueue[exec_cnt].StackNumber != 0xFF && line_number == OPT_GetMultiLinrNumber(SYB_ExecQueue[exec_cnt].StackNumber))) {
						if (line_feed_flag == 1) {
							line_feed_flag = 0;
							if (line_cnt < 10) {
								break;
							}
							else {
								/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
								if (error_flag == 1) {
									Print_TxConf_Line(8, List.S.Print, List.S.Attribute);
									if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
										return (ret);
									}
								}
								else {
									Print_TxConf_Line(4, List.S.Print, List.S.Attribute);
									if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
										return (ret);
									}
								}

								/**sˆóŽši‰üsj*/
								if ((ret = CharacterPrint((UBYTE)(LST_LINE_FEED+prn_mode))) != OK) {
									return (ret);
								}
								line_cnt -= 2;
							}
						}
					}
					else {
						exec_cnt++;
						continue;
					}
				}
			}
#endif

#if (0)
** /* ‘—MØ‚Æƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚Í’èŒ^’·‚ÅƒJƒbƒg‚·‚é‚æ‚¤‚É•ÏX By O.Kimoto 1999/02/22 */
** #if (PRO_PAPER_TYPE== ROLL_PAPER)
** /* ‚r‚`‚j‚`‚j‚h^‚g‚h‚m‚n‚j‚h‚Í‹L˜^Ž†‚ªƒ[ƒ‹Ž†‚È‚Ì‚ÅA‘—MØ‚ÍŠª‚«•¨‚Æ‚µ‚Ü‚·B
** ** by O.Kimoto 1999/01/26
** */
** 			if ( exec_cnt == SYS_EXEC_QUEUE_MAX) [	/** ŽŸÃÞ°À–³‚µ */
** #else
** 			if ( (exec_cnt == SYS_EXEC_QUEUE_MAX) || (line_cnt < line_max ) ) [	/** ŽŸÃÞ°À–³‚µ or ˆóü‰Â”\s”‚ª6sˆÈ‰º *//* Change 6 to line_max By O.Kimoto 1997/06/27 */
** #endif
#else
			if ( (exec_cnt == SYS_EXEC_QUEUE_MAX) || (line_cnt < line_max ) ) {	/** ŽŸÃÞ°À–³‚µ or ˆóü‰Â”\s”‚ª6sˆÈ‰º *//* Change 6 to line_max By O.Kimoto 1997/06/27 */
#endif

				if ( flag == 1 ) {
					flag = 0;
#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/4 K.Kawata */
					if (Print_TTI_InsteadOfLineNumber(exec_cnt, 0) == TRUE) { /* ‚Q‰ñüFƒ‰ƒCƒ“”Ô† */
						if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
		  					return (ret);
						}
						line_cnt -= 1;
					}
					/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
					Print_TxConf_Line(0, List.S.Print, List.S.Attribute);
					if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
						return (ret);
					}
					/**ETelephone NumberEModeEStartETimeEPageEResultENoteE*/
					Print_TxConf_Line(1, List.S.Print, List.S.Attribute);
					if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
						return (ret);
					}
					/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
					Print_TxConf_Line(2, List.S.Print, List.S.Attribute);
					if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
						return (ret);
					}
					if ((ret = Print_TxConf_Detail(exec_cnt, prn_mode)) != OK) {	/**1–¾×ˆóü */
						return (ret);
					}
					/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
					Print_TxConf_Line(5, List.S.Print, List.S.Attribute);
					if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
						return (ret);
					}
					/* VÄ‘—ƒƒbƒZ[ƒW */
					NewSendDocumentMessage(exec_cnt);
					if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
						return (ret);
					}
					line_cnt -= 6;
					error_flag = 1;
#else
 #if defined(EUR)	/* DTS‘Îô[Bb5.1.1-4] Journal(TCR)‚Ì‹Lq•û–@ S.Fukui Nov.5,1999 */
					/* kaki‚©‚çˆÚA by M.Harada 1999/11/17 */
					if (Print_TTI_InsteadOfLineNumber(exec_cnt, 0) == TRUE) { /* ‚Q‰ñüFƒ‰ƒCƒ“”Ô† */
						if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
		  					return ( ret );
						}
						line_cnt -= 1;
					}
 #else	/* ]—ˆˆ— */
					/* ˆÈ‰º‚Us’Ç‰Á By O.Kimoto 1997/06/27 */
					if (Print_LineNumber(exec_cnt, 0) == TRUE) { /* ‚Q‰ñüFƒ‰ƒCƒ“”Ô†’Ç‰Á 1996/12/06 Y.Matsukuma */
						if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
		  					return ( ret );
						}
						line_cnt -= 1;
					}
 #endif
					/**	ƒXƒLƒƒƒi‘—MŽž‚ÉŒ´e‚ðˆø‚«”²‚­‚ÆTCR‚ªˆóŽš‚³‚ê‚È‚¢Žž‚ª‚ ‚é‚Ì‚Å
					*	SYB_ExecQueue[SYS_EXEC_QUEUE_MAX]‚ðˆóŽš‚·‚é
					*/
					/*†®†¢†Î†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†²*/
					Print_CommErr_ChkMsg_Line( 0, List.S.Print, List.S.Attribute );
					if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
						return ( ret );
					}
					/*†¤ XXXXX†¤XXXXXXXXX†¤XXXXXXXXXXX†¤*/
					if ( (ret = Print_CommErr_ChkMsg_Specifi( SYS_EXEC_QUEUE_MAX, prn_mode, LST_PRINT_TCR ))
					  != OK ) {		/* ‘—MØ‚n‚mŽž‚Ìˆø”’Ç‰Á	1998/10/26 Y.Matsukuma */
						return ( ret );
					}
					/*†¶†¢†Ö†¢†¢†¢†Ö†¢†¢†¢†¢†¢†º*/
					Print_CommErr_ChkMsg_Line( 3, List.S.Print, List.S.Attribute );						/*94/09/09*/
					if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {			/*94/09/09*/
						return ( ret );
					}
					line_cnt -= 3;
#endif
				}
				break;
			}
			flag = 0;

/*			if ( line_cnt < 6 ) {	*//* •ÏX 1997/09/05 Y.Matsukuma */

#if (0)
** /* ‘—MØ‚Æƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚Í’èŒ^’·‚ÅƒJƒbƒg‚·‚é‚æ‚¤‚É•ÏX By O.Kimoto 1999/02/22 */
** #if (PRO_PAPER_TYPE== CUT_PAPER)
** 			/* ‚r‚`‚j‚`‚j‚h^‚g‚h‚m‚n‚j‚h‚Í‹L˜^Ž†‚ªƒ[ƒ‹Ž†‚È‚Ì‚ÅA‘—MØ‚ÍŠª‚«•¨‚Æ‚µ‚Ü‚·B
** 			** by O.Kimoto 1999/01/26
** 			*/
** 			if ( line_cnt < line_max ) {
** 				break;
** 			}
** #endif
#else
			if ( line_cnt < line_max ) {
				break;
			}
#endif

			/**	TCR ON‚ÌŽžA–”‚ÍARCR ON‚Å‘ŠŽè‹@‚ÉRCR‚Ì”\—Í‚ª–³‚¢ê‡ ‚ÆˆêŠ‡‘—M‚Ìê‡	*/
/*			if ( ((SYB_CommandFile[SYB_ExecQueue[exec_cnt].Number.Command].Option.ConfirmationReport == TCR_REQUEST)	*/
			if ( (((SYB_CommandFile[SYB_ExecQueue[exec_cnt].Number.Command].Option.ConfirmationReport & SYS_RCR_REQUESTED) == SYS_TCR_REQUESTED)
			  || (((SYB_CommandFile[SYB_ExecQueue[exec_cnt].Number.Command].Option.ConfirmationReport & SYS_TCR_AND_RCR) == SYS_TCR_AND_RCR)
			  && ((SYB_ExecQueue[exec_cnt].Option & SYS_PARTNER_NOT_RCR) == SYS_PARTNER_NOT_RCR)))
			  || (SYB_ExecQueue[exec_cnt].Kind == SYS_BATCH_TX) ) {
#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/4 K.Kawata */
				if (title_flag == 1) {
					title_flag = 0;
					if (Print_TTI_InsteadOfLineNumber(exec_cnt, 0) == TRUE) {
						if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
		  					return (ret);
						}
						line_cnt -= 1;
					}
					/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
					Print_TxConf_Line(0, List.S.Print, List.S.Attribute);
					if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
						return (ret);
					}
					/**ETelephone NumberEModeEStartETimeEPageEResultENoteE*/
					Print_TxConf_Line(1, List.S.Print, List.S.Attribute);
					if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
						return (ret);
					}
					line_cnt -= 2;
					error_flag = 0;
				}
				/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
				if (error_flag == 1) {
					Print_TxConf_Line(7, List.S.Print, List.S.Attribute);
					if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
						return (ret);
					}
				}
				else {
					Print_TxConf_Line(2, List.S.Print, List.S.Attribute);
					if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
						return (ret);
					}
				}
				if ((ret = Print_TxConf_Detail(exec_cnt, prn_mode)) != OK) {	/**1–¾×ˆóü */
					return (ret);
				}
				line_cnt -= 2;
#endif
				if ( (SYB_ExecQueue[exec_cnt].Status == SYS_EXEC_OK)
				  && ((SYB_ExecQueue[exec_cnt].Result & 0x0C00) == NO_ERROR) ) {	/**³íI—¹‚Ìê‡ */
#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/4 K.Kawata */
					error_flag = 0;
#else
					if ( (ret = Print_TxConf_Detail( exec_cnt, prn_mode )) != OK ) {	/**1–¾×ˆóü */
						return (ret );
					}
 #if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^Ž—‚Q‰ñüŽd—l by T.Soneoka 1997/03/11 */
					line_cnt -= 6;	/**6sŽg—p */
 #else
					/* ˆÈ‰º‚Us’Ç‰Á By O.Kimoto 1997/06/27 */
					if (OPT_CountModems() < 2) {
						line_cnt -= 5;	/**5sŽg—p */;
					}
					else {
						line_cnt -= 6;	/**6sŽg—p */
					}
 #endif
#endif
				} else {												/**ŒðM´×°‚Ìê‡ */
#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/4 K.Kawata */
					/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
					Print_TxConf_Line(5, List.S.Print, List.S.Attribute);
					if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
						return (ret);
					}

					/* VÄ‘—ƒƒbƒZ[ƒW */
					NewSendDocumentMessage(exec_cnt);
					if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
						return (ret);
					}
					line_cnt -= 2;	/**2sŽg—p */
					error_flag = 1;
#else
 #if defined(EUR)	/* DTS‘Îô[Bb5.1.1-4] Journal(TCR)‚Ì‹Lq•û–@ S.Fukui Nov.5,1999 */
					/* kaki‚©‚çˆÚA by M.Harada 1999/11/17 */
					if (Print_TTI_InsteadOfLineNumber(exec_cnt, 0) == TRUE) {
						if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
		  					return ( ret );
						}
						line_cnt -= 1;
					}
 #else	/* ]—ˆˆ— */
					/* ˆÈ‰º‚Us’Ç‰Á By O.Kimoto 1997/06/27 */
					if (Print_LineNumber(exec_cnt, 0) == TRUE) {
						if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
		  					return ( ret );
						}
						line_cnt -= 1;
					}
 #endif
					/**†®†¢†Î†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†²*/
					Print_CommErr_ChkMsg_Line( 0, List.S.Print, List.S.Attribute );
					if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
					return ( ret );
					}

					/**†¤ XXXXX†¤XXXXXXXXX†¤XXXXXXXXXXX†¤*/
					/* ‘—MØ‚n‚mŽž‚Ìˆø”’Ç‰Á	1998/10/27 Y.Matsukuma */
					if ( (ret = Print_CommErr_ChkMsg_Specifi( exec_cnt, prn_mode, LST_PRINT_TCR )) != OK ) {
						return ( ret );
					}

					/**†¶†¢†Ö†¢†¢†¢†Ö†¢†¢†¢†¢†¢†º*/
					Print_CommErr_ChkMsg_Line( 3, List.S.Print, List.S.Attribute );
					if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
						return ( ret );
					}
					line_cnt -= 3;	/**3sŽg—p */
#endif
				}
#if (PRO_NEW_TX_CONF == DISABLE) /* 2000/2/4 K.Kawata */
				/*
				** ‘—MØ•s‹ï‡
				** ã‹LAif•¶‚É“ü‚ç‚È‚¢‚Æ‚«AˆóŽš‚à‚µ‚Ä‚¢‚È‚¢‚Ì‚É‰üs‚¾‚¯“ü‚Á‚Ä‚µ‚Ü‚¤•s‹ï‡
				** if•¶‚Ì’†‚ÉˆÚ“®‚µ‚Ä‚«‚Ü‚µ‚½
				** 1999/03/05 by T.Soneoka
				*/
				/**sˆóŽši‰üsj*/
				if ( (ret = CharacterPrint( (UBYTE)(LST_LINE_FEED+prn_mode) )) != OK ) {
					return ( ret );
				}
				line_cnt--;
#endif
			}
/*
** ‘—MØ•s‹ï‡
** ã‹LAif•¶‚É“ü‚ç‚È‚¢‚Æ‚«AˆóŽš‚à‚µ‚Ä‚¢‚È‚¢‚Ì‚É‰üs‚¾‚¯“ü‚Á‚Ä‚µ‚Ü‚¤•s‹ï‡
** if•¶‚Ì’†‚ÉˆÚ“®‚µ‚Ü‚·
** 1999/03/05 by T.Soneoka
*/
#if (0)
**			/**sˆóŽši‰üsj*/
**			if ( (ret = CharacterPrint( (UBYTE)(LST_LINE_FEED+prn_mode) )) != OK ) {
**				return ( ret );
**			}
**			line_cnt--;
#endif
			exec_cnt++;
		}
#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/4 K.Kawata */
		/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
		if (error_flag == 1) {
			Print_TxConf_Line(8, List.S.Print, List.S.Attribute);
			if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
				return (ret);
			}
		}
		else {
			Print_TxConf_Line(4, List.S.Print, List.S.Attribute);
			if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
				return (ret);
			}
		}
		line_cnt -= 1;
#endif
		LST_CharacterLine = (UBYTE)(PaperSizeLen() - line_cnt);	/**	ƒLƒƒƒ‰ƒNƒ^ˆóŽšƒ‰ƒCƒ“”‚ðƒZƒbƒg	*/
		if ( (ret = CharacterPrint( (UBYTE)(LST_LINE_FEED+prn_mode) )) != OK ) {
			return ( ret );
		}
		LST_CharacterLine++;
		if ( exec_cnt != SYS_EXEC_QUEUE_MAX ) {			/**‚Ü‚¾ÃÞ°À‚ªŽc‚Á‚Ä‚¢‚é */
			if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
				return ( ret );
			}
		} else {

#if (0)
** /* ‘—MØ‚Æƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚Í’èŒ^’·‚ÅƒJƒbƒg‚·‚é‚æ‚¤‚É•ÏX By O.Kimoto 1999/02/22 */
** #if (PRO_PAPER_TYPE== ROLL_PAPER)
** /* ‚r‚`‚j‚`‚j‚h^‚g‚h‚m‚n‚j‚h‚Í‹L˜^Ž†‚ªƒ[ƒ‹Ž†‚È‚Ì‚ÅA‘—MØ‚ÍŠª‚«•¨‚Æ‚µ‚Ü‚·B
** ** by O.Kimoto 1999/01/26
** */
** 			if ( (ret = CharacterPrint( LST_LINE_FEED + 2 )) != OK ) {
** 				return ( ret );
** 			}
** 			if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
** 				return ( ret );
** 			}
** 			break;
** #else
** 			if ( prn_mode == LST_ERR_CLOSE ) { /**	’~ÏŒ´e‚ª–³‚¢ê‡	*/
** 				if ( (ret = CharacterPrint( LST_LINE_FEED + 2 )) != OK ) {
** 					return ( ret );
** 				}
** 				if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
** 					return ( ret );
** 				}
** 				break;
** 			}
** 			else if ( line_cnt < 17 ) {	/**Žc‚ès”‚ª17sˆÈ‰º‚Ìê‡AŽŸ‚ÌÍß°¼Þ‚É’~ÏŒ´e‚ðˆóŽš‚·‚éˆ× */
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
** #endif
#else
 /* ‘—MØ‚Æƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚Í’èŒ^’·‚ÅƒJƒbƒg‚·‚é‚æ‚¤‚É•ÏX By O.Kimoto 1999/02/22 */
 #if (PRO_PAPER_TYPE== ROLL_PAPER)
  #if (PRO_PRINT_TYPE == THERMAL) || (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.10 K.Kawata */
			/* Œ´e–³‚µ‘—MØ‚Ìê‡ */
			if (( SYS_DocumentPrintItem == LST_COMMERR_BATCH_CHECKMSG)	/**Áª¯¸Ò¯¾°¼ÞH@ˆêŠ‡‘—M’Ê’m(ÓÆÀ°ÚÎß°Äj */
				|| ( SYS_DocumentPrintItem ==LST_MONITOR_REPORT)) {			/**ÓÆÀ°ÚÎß°Ä**/
				if ( (ret = CharacterPrint( LST_LINE_FEED + 2 )) != OK ) {
					return ( ret );
				}
				if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
					return ( ret );
				}
				break;
			}
			else {
				/* Œ´e•t‚«‘—MØ‚Ìê‡ */
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
  #else
			if ( prn_mode == LST_ERR_CLOSE ) { /**	’~ÏŒ´e‚ª–³‚¢ê‡	*/
				if ( (ret = CharacterPrint( LST_LINE_FEED + 2 )) != OK ) {
					return ( ret );
				}
				if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
					return ( ret );
				}
				break;
			}
			else if ( line_cnt < 17 ) {	/**Žc‚ès”‚ª17sˆÈ‰º‚Ìê‡AŽŸ‚ÌÍß°¼Þ‚É’~ÏŒ´e‚ðˆóŽš‚·‚éˆ× */
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
  #endif
 #else
			if ( prn_mode == LST_ERR_CLOSE ) { /**	’~ÏŒ´e‚ª–³‚¢ê‡	*/
				if ( (ret = CharacterPrint( LST_LINE_FEED + 2 )) != OK ) {
					return ( ret );
				}
				if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
					return ( ret );
				}
				break;
			}
			else if ( line_cnt < 17 ) {	/**Žc‚ès”‚ª17sˆÈ‰º‚Ìê‡AŽŸ‚ÌÍß°¼Þ‚É’~ÏŒ´e‚ðˆóŽš‚·‚éˆ× */
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
 #endif
#endif

		}
		page++;
#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/4 K.Kawata */
		line_feed_flag = 0;
		title_flag = 1;
#endif
	}
	return ( OK );
}


/*************************************************************************
	module		:[Žè“®‘—M‘—MØ‚Ìˆóü]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ƒWƒƒ[ƒiƒ‹ƒf[ƒ^‚ðŽQÆ‚·‚é]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1996/06/24]
	author		:[•½”ö ‰p“T]
*************************************************************************/
WORD					Print_ManualTxConf( void )
{
	UBYTE	i;						/** ‘—Mƒtƒ@ƒCƒ‹”Ô† */
	register WORD	ret;					/** ŽÀsŒ‹‰Ê */

#if (PRO_JOURNAL_PRINT_TIME == DISABLE)	/* “ú—§“Á‹–‰ñ”ð 1998/10/28 Y.Matsukuma */
	UDWORD	time;
#endif

	TxConfYearPrint = CHK_JournalYearPrint();	/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16	*/
												/* ICHOU‚©‚çˆÚA‚µ‚Ä‚«‚Ü‚µ‚½		*/

	for (i = 0; i < SYS_JOURNAL_MAX; i++) {
		if ( (SYB_JournalFile[i].Kind == SYS_MANUAL_TRANSMIT)
#if (0)
**			&& (SYB_JournalFile[i].Option & SYS_TCR_REQUEST) ) [ /** ‘—MØƒvƒŠƒ“ƒg—v‹‚ÌŠm”F */
#endif
			&& ((SYB_JournalFile[i].Option & SYS_TCR_REQUEST) == SYS_TCR_REQUEST )) { /** ‘—MØƒvƒŠƒ“ƒg—v‹‚ÌŠm”F */
			break;
		}
	}

#if (PRO_JOURNAL_PRINT_TIME == DISABLE)	/* “ú—§“Á‹–‰ñ”ð 1998/10/28 Y.Matsukuma */
	time = SYB_JournalFile[i].StartTime;	/* ¼Þ¬°ÅÙ‚ÌƒXƒ^[ƒgƒ^ƒCƒ€‚ð‘ã“ü */
#endif

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

#if (PRO_JOURNAL_PRINT_TIME == DISABLE)	/* “ú—§“Á‹–‰ñ”ð 1998/10/28 Y.Matsukuma */
	if ( (ret = Print_TxConf_Head( LST_ERR_CLOSE, time )) != OK ) {		/**Í¯ÀÞˆóü*/
#else
	if ( (ret = Print_TxConf_Head( LST_ERR_CLOSE )) != OK ) {		/**Í¯ÀÞˆóü*/
#endif
		return ( ret );
	}

#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/03/16 M.Matsumoto */
	if ( (ret = Print_ManualTxConf_Detail(i)) != OK ) {
		return (ret);
	}
#else

	if ( (SYB_JournalFile[i].Result & 0x0C00) == NO_ERROR ) {
		if ( (ret = Print_ManualTxConf_Detail(i)) != OK ) {
			return (ret);
		}
	}
	else {

 #if defined(EUR)	/* DTS‘Îô[Bb5.1.1-4] Journal(TCR)‚Ì‹Lq•û–@ S.Fukui Nov.5,1999 */
					/* kaki‚©‚çˆÚA by M.Harada 1999/11/17 */
		if (Print_TTI_InsteadOfLineNumber(i, 1) == TRUE) {
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		  		return ( ret );
			}
		}
 #else	/* ]—ˆˆ— */
		/* ˆÈ‰º‚Ts’Ç‰Á By O.Kimoto 1997/06/27 */
		if (Print_LineNumber(i, 1) == TRUE) {
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		  		return ( ret );
			}
		}
 #endif

		/*†®†¢†¢†¢†Î†¢†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†²*/
		Print_CommErr_ChkMsg_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*†¤ XXXXX†¤XXXXXXXXX †¤XXXXXXXXXX†¤*/
		Print_CommErr_ChkMsg_Line( 1, List.S.Print, List.S.Attribute );

		/*Â³¼Ý¹¯¶”Ô†*/
		CommunicationResultName( SYB_JournalFile[i].Result, LST_NAME_SHORT,
		  LST_RESULT_COMMON, &List.S.Print[1], &List.S.Attribute[2-1] );

		/*Â³¼Ý¹¯¶ Ò¯¾°¼Þ*/
		CommunicationResultName( SYB_JournalFile[i].Result, LST_NAME_LONG,
		  LST_RESULT_COMMON, &List.S.Print[8], &List.S.Attribute[9-1] );

		/*±²Ã»·Ò²*/
		CMN_StringCopy( &List.S.Print[39], SYB_JournalFile[i].RemoteID_TTI );

		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*†¶†¢†¢†Ö†¢†¢†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†º*/
		Print_CommErr_ChkMsg_Line( 3, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
#endif

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}

	SYS_ManualFaxCommErrRequest = 0; /** Žè“®‘—ŽóMƒ`ƒFƒbƒNƒƒbƒZ[ƒWEƒvƒŠƒ“ƒg—v‹ƒNƒŠƒA */
	/*SYB_JournalFile[i].Option &= !SYS_TCR_REQUEST;*/ /** ‘—MØ—v‹‚ÌƒNƒŠƒA */
	SYB_JournalFile[i].Option &= ~SYS_TCR_REQUEST;	/* By M.Tachibana 19967/01/29 */
	return ( OK );
}


/*************************************************************************
	module		:[‘—MØ‚Ìƒwƒbƒ_ˆóü]
	function		:[‘—MØ‚Ì1–‡–Ú‚ÌTTI/ID‚ÆÀ²ÄÙ‚ÆŒ»Ý“úŽž‚ðˆóü‚·‚é]
	common		:[]
	condition		:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[Apr.16,1996]
	author		:[•½”ö ‰p“T]
*************************************************************************/
#if (PRO_JOURNAL_PRINT_TIME == DISABLE)	/* “ú—§“Á‹–‰ñ”ð 1998/10/28 Y.Matsukuma */
WORD					Print_TxConf_Head(
										UBYTE prn_mode,
										UDWORD time )		/** ÌßØÝÀÓ°ÄÞ */
#else
WORD					Print_TxConf_Head(
										UBYTE prn_mode )		/** ÌßØÝÀÓ°ÄÞ */
#endif
{
	WORD	ret;					/**ŽÀsŒ‹‰Ê */
	/**‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs */
	if ( (ret = CharacterPrint( (UBYTE)(LST_LINE_FEED+prn_mode) )) != OK ) {
		return ( ret );
	}

	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );

/* ‚o‚n‚o‚k‚`‚qQ‚g •W€‚Q‰ñüŽû—e‘Î‰ž‚Ìˆ× By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
	CMN_StringCopy( &List.S.Print[1-1], &SYB_TTI_Buffer[0][0]);
	if ( SYB_ID_Buffer[0][0] != NULL ) {
		AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD,
		  LST_NOT );
		CMN_StringCopy( &List.S.Print[28-1], &SYB_ID_Buffer[0][0]);
	}
#else
 #if defined(EUR)	/* DTS‘Îô[Bb5.1.1-4] Journal(TCR)‚Ì‹Lq•û–@ S.Fukui Nov.5,1999 */
					/* kaki‚©‚çˆÚA by M.Harada 1999/11/17 */
	if (OPT_CountModems() < 2) { /* •¡”‰ñü‚¶‚á‚È‚©‚Á‚½‚çA‚s‚s‚h‚ð‹LÚ‚·‚éBS.Fukui Nov.4,1999 */
		CMN_StringCopy( &List.S.Print[1-1], SYB_TTI_Buffer);
		if ( SYB_ID_Buffer[0] != NULL ) {
			AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD,
			  LST_NOT );
			CMN_StringCopy( &List.S.Print[28-1], SYB_ID_Buffer);
		}
	}
 #else
	CMN_StringCopy( &List.S.Print[1-1], SYB_TTI_Buffer);
	if ( SYB_ID_Buffer[0] != NULL ) {
		AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD,
		  LST_NOT );
		CMN_StringCopy( &List.S.Print[28-1], SYB_ID_Buffer);
	}
 #endif
#endif

	if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
		return ( ret );
	}

	if ( (ret = CharacterPrint( (UBYTE)(LST_LINE_FEED+prn_mode) )) != OK ) {
		return ( ret );
	}

	/**––@‚s‚’‚‚Ž‚“‚‚‰‚”  ‚b‚‚Ž‚†D‚q‚…‚‚‚’‚”@–– */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
	AttributeSet( &List.S.Print[14], &List.S.Attribute[14],
				  PWRD_TransConfReport_K, LST_NOT );
#else
	AttributeSet( &List.S.Print[14], &List.S.Attribute[14],
				  PWRD_TransConfReport, LST_XXX_TWI_XXX );
#endif
	if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
		return ( ret );
	}

	/**‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( (UBYTE)(LST_LINE_FEED+prn_mode) )) != OK ) {
		return ( ret );
	}

	/**Œ»ÝŽžŠÔ */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[1] = 'P';
	List.S.Print[2] = '.';
	List.S.Print[3] = '1';
#if (PRO_JOURNAL_PRINT_TIME == DISABLE)	/* “ú—§“Á‹–‰ñ”ð Œ»ÝŽžŠÔ‚ð‚Ì‚¹‚¸A’ÊM½À°ÄŽžŠÔ‚ð‚Ì‚¹‚é 1998/10/28 Y.Matsukuma */
	TimeDataAscii( OFF, time, List.S.Work, 0 );
	CMN_StringCopy( &List.S.Print[60-1], List.S.Work);
#else
	TimeDataAscii( OFF, SYB_CurrentTime, List.S.Work, 0 );
	CMN_StringCopy( &List.S.Print[60-1], List.S.Work);
#endif
	if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
		return (ret );
	}

	return ( OK );
}

/*************************************************************************
	module		:[‘—MØ‚Ì1’ÊM•ª‚ðˆóü]
	function	:[‘—MØ‚Ì1’ÊM•ª‚Ì–¾×‚ðˆóü‚·‚é]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[Apr.16,1996]
	author		:[•½”ö ‰p“T]
*************************************************************************/
WORD					Print_TxConf_Detail(
							UBYTE number,
							UBYTE prn_mode )
{
	WORD		ret;			/**ŽÀsŒ‹‰Ê */
	UBYTE		num_cnt;		/* ƒ_ƒCƒ„ƒ‹”Ô†‚ÌŒ…” 1998/10/28 Y.Matsukuma */

	unsigned char	dial_length;	/* ÀÞ²ÔÙ”Ô†‚Ì’·‚³ *//* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16	*/
														 /* ICHOU‚©‚çˆÚA‚µ‚Ä‚«‚Ü‚µ‚½		*/

#if 0	/* ƒvƒŒƒtƒBƒbƒNƒX{ƒ_ƒCƒ„ƒ‹”Ô†‚Å40Œ…‚ð’´‚¦‚Ä‚àÜ‚è•Ô‚µ‚ÄˆóŽš‚µ‚È‚¢‚Ì‚ÅA‘å“‡‚³‚ñŠm”F‚ÌãAƒŠƒXƒg‚Å‚Ì“WŠJ‚ÍŽ~‚ß‚Ü‚· by K.Watanabe 2004/11/12 */
//#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/10 *//* by K.Watanabe 2004/10/12 */
//	UWORD	length;
//	UBYTE	temp_str[LST_COLUM - 1];
#endif			/*	End of defined(STOCKHM2)	*/

#if (PRO_NEW_TX_CONF == DISABLE) /* 2000/2/4 K.Kawata */
 #if defined(EUR)	/* DTS‘Îô[Bb5.1.1-4] Journal(TCR)‚Ì‹Lq•û–@ S.Fukui Nov.5,1999 */
					/* kaki‚©‚çˆÚA by M.Harada 1999/11/17 */
	if (Print_TTI_InsteadOfLineNumber(number, 0) == TRUE) {
		if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
	 		return ( ret );
		}
	}
 #else	/* ]—ˆˆ— */
	/* ˆÈ‰º‚Ts’Ç‰Á By O.Kimoto 1997/06/27 */
	if (Print_LineNumber(number, 0) == TRUE) {
		if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
	 		return ( ret );
		}
	}
 #endif
	/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
	Print_TxConf_Line( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
		return ( ret );
	}

	/**ETelephone NumberEModeEStartETimeEPageEResultENoteE*/
	Print_TxConf_Line( 1, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
		return ( ret );
	}

	/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
	Print_TxConf_Line( 2, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
		return ( ret );
	}
#endif

	/**†¾                      †¢      E      E     E      E      E     E*/
	Print_TxConf_Line( 3, List.S.Print, List.S.Attribute );

	if ( TxConfYearPrint ) {	/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16	*/
								/* ICHOU‚©‚çˆÚA‚µ‚Ä‚«‚Ü‚µ‚½		*/
		dial_length = 24;
	}
	else {
		dial_length = 29;
	}

	/**Telephon Number */
	CMN_MemorySetNULL( List.S.Work, LST_COLUM-1, ' ' ); /**	ƒ[ƒNƒGƒŠƒA‚ÌƒNƒŠƒA	*/

#if 0	/* ƒvƒŒƒtƒBƒbƒNƒX{ƒ_ƒCƒ„ƒ‹”Ô†‚Å40Œ…‚ð’´‚¦‚Ä‚àÜ‚è•Ô‚µ‚ÄˆóŽš‚µ‚È‚¢‚Ì‚ÅA‘å“‡‚³‚ñŠm”F‚ÌãAƒŠƒXƒg‚Å‚Ì“WŠJ‚ÍŽ~‚ß‚Ü‚· by K.Watanabe 2004/11/12 */
//#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/10 *//* by K.Watanabe 2004/10/12 */
//	CMN_MemorySet( temp_str, LST_COLUM-1, ' ' ); /**	ƒ[ƒNƒGƒŠƒA‚ÌƒNƒŠƒA	*/
#endif

#if (PRO_BATCH_TX == ENABLE)	/* By M.Tachibana 1996/11/21 */
	if ( (SYB_ExecQueue[number].Kind == SYS_BATCH_TX)
	  && (SYB_BatchTxFile[SYS_DocumentPrintNo].Name[0] != NULL)) { /**	ˆêŠ‡‘—M‚Å‚Í‚a‚n‚w–¼‚ð—Dæ	*/
/*			CMN_StringCopy( &List.S.Print[2-1], SYB_BatchTxFile[SYS_DocumentPrintNo].Name );*/
/*			CMN_StringCopyNum(&List.S.Print[2-1], &SYB_BatchTxFile[SYS_DocumentPrintNo].Name[0], dial_length - 5 );	 1999/12/02 Y.M *//* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/17 */
			CMN_StringCopyNumOrNULL(&List.S.Print[2-1], &SYB_BatchTxFile[SYS_DocumentPrintNo].Name[0], dial_length - 5 );	/* 1999/12/02 Y.M */
	}
	else {
#endif
		switch ( SYB_ExecQueue[number].ExecDial.Item ) {
		case SYS_DIRECT_DIAL:
			if ( SYB_ExecQueue[number].Kind == SYS_COMMAND_TRX ) {
#if (0)	/* ƒRƒ}ƒ“ƒhƒtƒ@ƒCƒ‹‚Ì•ÏX‚É‚æ‚é By M.Tachibana 1996/11/21 */
**				CMN_BCD_ToASC_String( List.S.Work, SYB_CommandFile
**				  [SYB_ExecQueue[number].Number.Command].DialNumber[SYB_ExecQueue
**				  [number].ExecDial.ExecNumber.Command].FaxNumber.Direct );
#endif

				CMN_BCD_ToASC_String( List.S.Work, SYB_CommandFile
				  [SYB_ExecQueue[number].Number.Command].DialNumber.
				  Direct[SYB_ExecQueue[number].ExecDial.ExecNumber.Command] );
				  
				/* ÀÞ²ÔÙŒ…‚ª26•¶Žš‚ð‰z‚¦‚½‚çu¥¥‰º25Œ…v‚ðˆóŽš‚·‚éˆ—’Ç‰Á 1998/10/28 Y.Matsukuma */
				num_cnt = DialWithinCheck(List.S.Work);
#if (0)
//				if (CHK_UNI_DialWithin() && num_cnt > 26) {	/* ÕÆ°¸SW I7-0 */
//					num_cnt = num_cnt - 26;
//					List.S.Work[num_cnt] = LST_A_TENTEN;
//					CMN_StringCopyNum( &List.S.Print[2-1], &List.S.Work[num_cnt], 26 );
//				}
//				else {
//					CMN_StringCopyNum( &List.S.Print[2-1], List.S.Work, 26 );
//				}
#else
 #if 0	/* ƒvƒŒƒtƒBƒbƒNƒX{ƒ_ƒCƒ„ƒ‹”Ô†‚Å40Œ…‚ð’´‚¦‚Ä‚àÜ‚è•Ô‚µ‚ÄˆóŽš‚µ‚È‚¢‚Ì‚ÅA‘å“‡‚³‚ñŠm”F‚ÌãAƒŠƒXƒg‚Å‚Ì“WŠJ‚ÍŽ~‚ß‚Ü‚· by K.Watanabe 2004/11/12 */
// #if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/09 *//* by K.Watanabe 2004/10/12 */
//				if (List.S.Work[0] == '!'){
//					length = CMN_StringLength(SYB_MercuryDialBuffer);	/* ƒ}ƒLƒ…ƒŠ[“o˜^Œ… */
//					List.S.Print[1] = '[';
//					
//					if (CHK_UNI_DialWithin() && (num_cnt > (dial_length - 4 - length))){	/* ÕÆ°¸SW I7-0 */
//						if (length > 3){
//							List.S.Print[2] = LST_A_TENTEN;
//							CMN_StringCopyNum( &List.S.Print[3], &SYB_MercuryDialBuffer[length - 3], 3);
//							List.S.Print[6] = ']';
//							
//							if (num_cnt > dial_length - 8){
//								List.S.Print[7] = LST_A_TENTEN;
//								CMN_StringCopyNum( &List.S.Print[8],
//									&List.S.Work[num_cnt - dial_length + 10], dial_length - 10);
//							}
//							else{
//								CMN_StringCopyNum( &List.S.Print[7], &List.S.Work[1], dial_length - 9);
//							}
//						}
//						else{
//							CMN_StringCopyNum( &List.S.Print[2], &SYB_MercuryDialBuffer, length);
//							List.S.Print[2 + length] = ']';
//					
//							List.S.Print[3 + length] = LST_A_TENTEN;
//							CMN_StringCopyNum( &List.S.Print[4 + length],
//								&List.S.Work[num_cnt - dial_length + 6 + length],
//								dial_length - 6 -length);
//						}
//					}
//					else{
//						CMN_StringCopyNum( temp_str, &SYB_MercuryDialBuffer, length);
//						temp_str[length] = ']';
//						CMN_StringCopyNum( &temp_str[1 + length], &List.S.Work[1], dial_length - 3);
//						CMN_StringCopyNum( &List.S.Print[2], temp_str, dial_length - 4);
//					}
//					
//				}
//				else{
//					/*
//					 * u¥¥‰º25Œ…v‚ðˆóŽš‚·‚éˆ—‚Æ¼—ï‚SŒ…‘Î‰ž‚Ìˆ—‚ª“¯Žž‚É‚ ‚é‚ÆA
//					 * ³‚µ‚­u¥¥‰º25Œ…v‚ðˆóŽš‚Å‚«‚È‚¢•s‹ï‡ bythonda2000/03/13
//					 */
//					if (CHK_UNI_DialWithin() && (num_cnt > (dial_length - 3))) {	/* ÕÆ°¸SW I7-0 */
//						num_cnt = num_cnt - dial_length + 3;
//						List.S.Work[num_cnt] = LST_A_TENTEN;
//
//						CMN_StringCopyNum( &List.S.Print[2-1], &List.S.Work[num_cnt], dial_length - 3 );
//					}
//					else {
//						CMN_StringCopyNum( &List.S.Print[2-1], List.S.Work, dial_length - 3 );
//					}
//				}
 #else
				/*
				 * u¥¥‰º25Œ…v‚ðˆóŽš‚·‚éˆ—‚Æ¼—ï‚SŒ…‘Î‰ž‚Ìˆ—‚ª“¯Žž‚É‚ ‚é‚ÆA
				 * ³‚µ‚­u¥¥‰º25Œ…v‚ðˆóŽš‚Å‚«‚È‚¢•s‹ï‡ bythonda2000/03/13
				 */
				if (CHK_UNI_DialWithin() && (num_cnt > (dial_length - 3))) {	/* ÕÆ°¸SW I7-0 */
					num_cnt = num_cnt - dial_length + 3;
					List.S.Work[num_cnt] = LST_A_TENTEN;

					/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
					CMN_StringCopyNum( &List.S.Print[2-1], &List.S.Work[num_cnt], dial_length - 3 );
				}
				else {
					/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
					CMN_StringCopyNum( &List.S.Print[2-1], List.S.Work, dial_length - 3 );
				}
 #endif			/*	End of defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE) */
#endif
			}
#if (PRO_BATCH_TX == ENABLE)	/* By M.Tachibana 1996/11/21 */
			else {
				CMN_BCD_ToASC_String( List.S.Work, SYB_BatchTxFile
				[SYS_DocumentPrintNo].DialNumber[0].FaxNumber.Direct );
/*					CMN_StringCopyNum( &List.S.Print[2-1], List.S.Work, 24 );*/
					/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
					CMN_StringCopyNum( &List.S.Print[2-1], List.S.Work, dial_length - 5 );
			}
#endif
			break;
		case SYS_ONETOUCH_DIAL:
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			if ( CMN_OffsetToOnetouchCode( SYB_ExecQueue[number].ExecDial.ExecNumber.Onetouch ) <= 0x7A ){
				List.S.Print[2-1] = '[';
				List.S.Print[4-1] = ']';
				List.S.Print[3-1] =CMN_OffsetToOnetouchCode(SYB_ExecQueue[number].ExecDial.ExecNumber.Onetouch );
			} else{
				List.S.Print[2-1] = '[';
				List.S.Print[5-1] = ']';
				List.S.Print[3-1] = 0x55;	/** 'U'‚ÌASCIIº-ÄÞ */
				List.S.Print[4-1] = CMN_OffsetToOnetouchCode( SYB_ExecQueue[number].ExecDial.ExecNumber.Onetouch ) &
								 (UBYTE)0x0F | (UBYTE)0x30; /** U1`U8‹L†‚ð‚Â‚­‚é */
			}
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_PANEL == ANK)
		List.S.Print[2-1] = '[';
		List.S.Print[5-1] = ']';
		CMN_UnsignedIntToASC( &List.S.Print[3-1],
							 (UWORD)(CMN_OffsetToOnetouchCode(
									SYB_ExecQueue[number].ExecDial.ExecNumber.Onetouch ) - 0x40), 2, '0' );
 #endif
 #if (PRO_PANEL == KANJI)
 		/* ƒƒ“ƒ^ƒbƒ`‚Ì•\Ž¦‚ð[]->ŠG•¶Žš‚É•ÏX By O.Kimoto 1998/01/22 */
		List.S.Print[2-1] = LCD_PICFONT;
		List.S.Print[3-1] = LCD_PICFONT_LOWER;
		CMN_UnsignedIntToASC( &List.S.Print[4-1],
							 (UWORD)(CMN_OffsetToOnetouchCode(
									SYB_ExecQueue[number].ExecDial.ExecNumber.Onetouch ) - 0x40), 2, '0' );
 #endif
#endif
			/**	ÜÝÀ¯ÁÀÞ²±Ù‹L†‚É‰Á‚¦‚Ä‘ŠŽèæ–¼ –”‚Í ÀÞ²±Ù”Ô†‚ðˆóŽš‚·‚é
			*	ÜÝÀ¯ÁÀÞ²±Ù”Ô†‚Í40Œ…‚Ü‚Å“o˜^‚Å‚«‚é‚ª18Œ…‚Ü‚ÅˆóŽš‚·‚é
			*	’ÊM’†‚ÉÜÝÀ¯ÁÀÞ²±Ù‚ð“o˜^‚µ’¼‚·‰Â”\«‚Í‚ ‚é‚ªHHH
			*/

#if (0)
** 			/* ‚h‚b‚g‚n‚t‚©‚ç‚ÌƒtƒB[ƒhƒoƒbƒN By O.Kimoto 1998/03/30 */
** 			/*
** 			** ƒŠƒ‚[ƒgf’f‚ª–¢“o˜^‚È‚ç‚e‚O‚ð‘‚­ê‡‚ª‚ ‚é‚Ì‚Å‚e‚e‚ÅŒ©‚Ä‚¢‚é‚Æ‚¨‚©‚µ‚­‚È‚é
** 			** 1997/10/03 M.Shimizu
** 			*/
** 			if ( SYB_OnetouchDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Onetouch].Dial[0] != LST_DIAL_NOT ) [ /**	ÜÝÀ¯ÁÀÞ²±Ù‚ª“o˜^‚³‚ê‚Ä‚¢‚éê‡	*/
#else
			if ( (SYB_OnetouchDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Onetouch].Dial[0] & 0xF0) != 0xF0 ) { /**	ÜÝÀ¯ÁÀÞ²±Ù‚ª“o˜^‚³‚ê‚Ä‚¢‚éê‡	*/
#endif

				if ( SYB_OnetouchDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Onetouch].Name[0] != NULL ) { /**	‘ŠŽèæ–¼‚ª“o˜^‚³‚ê‚Ä‚¢‚éê‡	*/
#if (0)		/* •¶Žš”‚ª‘½‚¢ˆ×AŒrü‚ðÁ‚µ‚Ä‚µ‚Ü‚¤ 1998/05/18 By M.Kuwahara */
//					CMN_StringCopy( &List.S.Print[7],
//					  SYB_OnetouchDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Onetouch].Name );
#endif
				/*	CMN_StringCopyNum( &List.S.Print[7-1],By Y.Suzuki 1998/05/19 */
				/* CMN_StringCopyNum ‚ÍANULL‚ðŒŸo‚µ‚Ä‚­‚ê‚È‚¢BƒSƒ~ƒf[ƒ^‚ªÚ‚é‚±‚Æ‚ª—L‚éB*/
					CMN_StringCopyNumUntilNull( &List.S.Print[7-1],
/*						  SYB_OnetouchDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Onetouch].Name, 21 );*/
						/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
						  SYB_OnetouchDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Onetouch].Name, dial_length - 8 );
				}
				else { /**	‘ŠŽèæ–¼‚ª“o˜^‚³‚ê‚Ä‚¢‚È‚¢ê‡“d˜b”Ô†‚ðˆóŽš‚·‚é	*/
					CMN_BCD_ToASC_String( List.S.Work,
					  SYB_OnetouchDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Onetouch].Dial );
/*					CMN_StringCopyNum( &List.S.Print[7], List.S.Work, 18 );*/	/* 1998/05/18 By M.Kuwahara */
				/*	CMN_StringCopyNum( &List.S.Print[7-1], List.S.Work, 18 );By Y.Suzuki 1998/05/19 */

					/* ÀÞ²ÔÙŒ…‚ª21•¶Žš‚ð‰z‚¦‚½‚çu¥¥‰º20Œ…v‚ðˆóŽš‚·‚éˆ—’Ç‰Á 1998/10/28 Y.Matsukuma */
					num_cnt = DialWithinCheck(List.S.Work);
#if (0)
//					if (CHK_UNI_DialWithin() && num_cnt > 21) {	/* ÕÆ°¸SW I7-0 */
//						num_cnt = num_cnt - 21;
//						List.S.Work[num_cnt] = LST_A_TENTEN;
//							CMN_StringCopyNum( &List.S.Print[7-1], &List.S.Work[num_cnt], 21 );
//					}
//					else {
//							CMN_StringCopyNum( &List.S.Print[7-1], List.S.Work, 21 );
//					}
#else
 #if 0	/* ƒvƒŒƒtƒBƒbƒNƒX{ƒ_ƒCƒ„ƒ‹”Ô†‚Å40Œ…‚ð’´‚¦‚Ä‚àÜ‚è•Ô‚µ‚ÄˆóŽš‚µ‚È‚¢‚Ì‚ÅA‘å“‡‚³‚ñŠm”F‚ÌãAƒŠƒXƒg‚Å‚Ì“WŠJ‚ÍŽ~‚ß‚Ü‚· by K.Watanabe 2004/11/12 */
// #if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/09 *//* by K.Watanabe 2004/10/12 */
//				if (List.S.Work[0] == '!'){
//					length = CMN_StringLength(SYB_MercuryDialBuffer);	/* ƒ}ƒLƒ…ƒŠ[“o˜^Œ… */
//					List.S.Print[6] = '[';
//					
//					if (CHK_UNI_DialWithin() && num_cnt > (dial_length - 9 - length)){	/* ÕÆ°¸SW I7-0 */
//						if (length > 3){
//							List.S.Print[7] = LST_A_TENTEN;
//							CMN_StringCopyNum( &List.S.Print[8], &SYB_MercuryDialBuffer[length - 3], 3);
//							List.S.Print[11] = ']';
//							
//							if (num_cnt > dial_length - 13){
//								List.S.Print[12] = LST_A_TENTEN;
//								CMN_StringCopyNum( &List.S.Print[13],
//									&List.S.Work[num_cnt - dial_length + 15], dial_length - 15);
//							}
//							else{
//								CMN_StringCopyNum( &List.S.Print[12], &List.S.Work[1], dial_length - 14);
//							}
//						}
//						else{
//							CMN_StringCopyNum( &List.S.Print[7], &SYB_MercuryDialBuffer, length);
//							List.S.Print[7 + length] = ']';
//					
//							List.S.Print[8 + length] = LST_A_TENTEN;
//							CMN_StringCopyNum( &List.S.Print[9 + length],
//								&List.S.Work[num_cnt - dial_length + 11 + length],
//								dial_length - 11 -length);
//						}
//					}
//					else{
//						CMN_StringCopyNum( temp_str, &SYB_MercuryDialBuffer, length);
//						temp_str[length] = ']';
//						CMN_StringCopyNum( &temp_str[1 + length], &List.S.Work[1], dial_length - 8);
//						CMN_StringCopyNum( &List.S.Print[7], temp_str, dial_length - 9);
//					}
//					
//				}
//				else{
//					/*
//					 * u¥¥‰º20Œ…v‚ðˆóŽš‚·‚éˆ—‚Æ¼—ï‚SŒ…‘Î‰ž‚Ìˆ—‚ª“¯Žž‚É‚ ‚é‚ÆA
//					 * ³‚µ‚­u¥¥‰º20Œ…v‚ðˆóŽš‚Å‚«‚È‚¢•s‹ï‡ bythonda2000/03/13
//					 */
//					if (CHK_UNI_DialWithin() && (num_cnt > (dial_length - 8))) {	/* ÕÆ°¸SW I7-0 */
//						num_cnt = num_cnt - dial_length + 8;
//						List.S.Work[num_cnt] = LST_A_TENTEN;
//
//						/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
//						CMN_StringCopyNum( &List.S.Print[7-1], &List.S.Work[num_cnt], dial_length - 8 );
//					}
//					else {
//						/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
//						CMN_StringCopyNum( &List.S.Print[7-1], List.S.Work, dial_length - 8 );
//					}
//				}
 #else
					/*
					 * u¥¥‰º20Œ…v‚ðˆóŽš‚·‚éˆ—‚Æ¼—ï‚SŒ…‘Î‰ž‚Ìˆ—‚ª“¯Žž‚É‚ ‚é‚ÆA
					 * ³‚µ‚­u¥¥‰º20Œ…v‚ðˆóŽš‚Å‚«‚È‚¢•s‹ï‡ bythonda2000/03/13
					 */
					if (CHK_UNI_DialWithin() && (num_cnt > (dial_length - 8))) {	/* ÕÆ°¸SW I7-0 */
						num_cnt = num_cnt - dial_length + 8;
						List.S.Work[num_cnt] = LST_A_TENTEN;
	
						/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
						CMN_StringCopyNum( &List.S.Print[7-1], &List.S.Work[num_cnt], dial_length - 8 );
					}
					else {
						/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
						CMN_StringCopyNum( &List.S.Print[7-1], List.S.Work, dial_length - 8 );
					}
 #endif			/*	End of defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE) */
#endif
				}
			}
			break;
		case SYS_SPEED_DIAL:
#if (0)	/* 97/09/08 By M.Kuwahara */
//			List.S.Print[1] = '(';
//			List.S.Print[5] = ')';
//			CMN_UnsignedIntToASC( &List.S.Print[2],
//			  (UWORD)(SYB_ExecQueue[number].ExecDial.ExecNumber
//			  .Speed+OPR_SPEED_DIAL_MIN), 3, '0' );
#endif
			if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
				if ( SYS_SPEED_DIAL_MAX+SYS_2ND_SPEED_DIAL_MAX >= 100 ) {
 #if (1) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
					CMN_UnsignedIntToASC( &List.S.Print[2-1],
										 (UWORD)SYB_OptionalSpeed[
														SYB_ExecQueue[number].ExecDial.ExecNumber.Speed].Number,
										  OP_SPEED_FIGURE_MAX, '0' );
 #else
//					CMN_UnsignedIntToASC( &List.S.Print[2-1],
//										 (UWORD)SYB_OptionalSpeed[
//														SYB_ExecQueue[number].ExecDial.ExecNumber.Speed].Number,
//										  3, '0' );
 #endif
				}
				else {
					CMN_UnsignedIntToASC( &List.S.Print[3-1],
										 (UWORD)SYB_OptionalSpeed[
														SYB_ExecQueue[number].ExecDial.ExecNumber.Speed].Number,
										  2, '0' );
				}
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
				List.S.Print[2-1]	= *CalculateStringAddress(&D2W_HeadCharacter_Speed);
 #else
				List.S.Print[2-1]	= 'S';
 #endif
 #if (1) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
				CMN_UnsignedIntToASC( &List.S.Print[3-1],
									 (UWORD)SYB_OptionalSpeed[
													SYB_ExecQueue[number].ExecDial.ExecNumber.Speed].Number,
									  OP_SPEED_FIGURE_MAX, '0' );
 #else
//				CMN_UnsignedIntToASC( &List.S.Print[3-1],
//									 (UWORD)SYB_OptionalSpeed[
//													SYB_ExecQueue[number].ExecDial.ExecNumber.Speed].Number,
//									  3, '0' );
 #endif
#endif	/* PANEL_ANZU_L */
			}
			else{		/* ’Êí‚Ì’Zk‚ÌŽž */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
				if ( SYS_SPEED_DIAL_MAX+SYS_2ND_SPEED_DIAL_MAX >= 100 ) {
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
					CMN_UnsignedIntToASC( &List.S.Print[2-1],
										  (UWORD)(SYB_ExecQueue[number].ExecDial.ExecNumber.Speed+OPR_SPEED_DIAL_MIN),										  3, '0' );
 #else
					CMN_UnsignedIntToASC( &List.S.Print[2-1],
										 (UWORD)(SYB_ExecQueue[number].ExecDial.ExecNumber.Speed + 1),
										 3, '0' );
 #endif
				}
				else {
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
					CMN_UnsignedIntToASC( &List.S.Print[3-1],
										 (UWORD)(SYB_ExecQueue[number].ExecDial.ExecNumber.Speed+OPR_SPEED_DIAL_MIN),
										 2, '0' );
 #else
					CMN_UnsignedIntToASC( &List.S.Print[3-1],
										 (UWORD)(SYB_ExecQueue[number].ExecDial.ExecNumber.Speed + 1),
										 2, '0' );
 #endif
				}
#elif (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (F250‚Í’Zkƒ_ƒCƒ„ƒ‹‚ÍÅ‘å80Œ‚Å‚·‚©‚çA’ZkÀÞ²ÔÙNoA‚ªS01AS02`S80‚Ü‚Å‚É•ÏX‚·‚é‚±‚Æ) Added by SMuratec L.Z.W 2003/10/09 */
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
  #if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
				List.S.Print[2-1]	= *CalculateStringAddress(&D2W_HeadCharacter_Speed);
  #else
				List.S.Print[2-1]	= 'S';
  #endif
				CMN_UnsignedIntToASC( &List.S.Print[3-1], 
									 (UWORD)(SYB_ExecQueue[number].ExecDial.ExecNumber.Speed+OPR_SPEED_DIAL_MIN), 
									 OP_SPEED_FIGURE_MAX, '0' );
 #else
				CMN_UnsignedIntToASC( &List.S.Print[3-1],
									 (UWORD)(SYB_ExecQueue[number].ExecDial.ExecNumber.Speed + 1),
									 OP_SPEED_FIGURE_MAX, '0' );
 #endif
#else	/* PANEL_POPLA_B/L/H */
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
  #if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
				List.S.Print[2-1]	= *CalculateStringAddress(&D2W_HeadCharacter_Speed);
  #else
				List.S.Print[2-1]	= 'S';
  #endif
				CMN_UnsignedIntToASC( &List.S.Print[3-1],
									 (UWORD)(SYB_ExecQueue[number].ExecDial.ExecNumber.Speed+OPR_SPEED_DIAL_MIN),
									 3, '0' );
 #else
				CMN_UnsignedIntToASC( &List.S.Print[3-1],
									 (UWORD)(SYB_ExecQueue[number].ExecDial.ExecNumber.Speed + 1),
 									 3, '0' );
 #endif
#endif	/* PANEL_ANZU_L */
			}

			/**	’Zk”Ô†‚É‰Á‚¦‚Ä‘ŠŽèæ–¼ –”‚Í ÀÞ²±Ù”Ô†‚ðˆóŽš‚·‚é
			*	’ZkÀÞ²±Ù”Ô†‚Í40Œ…‚Ü‚Å“o˜^‚Å‚«‚é‚ª18Œ…‚Ü‚ÅˆóŽš‚·‚é
			*/

#if (0)
** 			/* ‚h‚b‚g‚n‚t‚©‚ç‚ÌƒtƒB[ƒhƒoƒbƒN By O.Kimoto 1998/03/30 */
** 			/*
** 			** ƒŠƒ‚[ƒgf’f‚ª–¢“o˜^‚È‚ç‚e‚O‚ð‘‚­ê‡‚ª‚ ‚é‚Ì‚Å‚e‚e‚ÅŒ©‚Ä‚¢‚é‚Æ‚¨‚©‚µ‚­‚È‚é
** 			** 1997/10/03 M.Shimizu
** 			*/
** 			if ( SYB_SpeedDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Speed].Dial[0] != LST_DIAL_NOT ) [ /**	’ZkÀÞ²±Ù‚ª“o˜^‚³‚ê‚Ä‚¢‚éê‡	*/
#else
			if ( (SYB_SpeedDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Speed].Dial[0] & 0xF0) != 0xF0 ) { /**	’ZkÀÞ²±Ù‚ª“o˜^‚³‚ê‚Ä‚¢‚éê‡	*/
#endif
				if ( SYB_SpeedDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Speed].Name[0] != NULL ) { /**	‘ŠŽèæ–¼‚ª“o˜^‚³‚ê‚Ä‚¢‚éê‡	*/
#if (0)	/* •¶Žš”‚ª‘½‚¢ˆ×AŒrü‚ªÁ‚³‚ê‚é 1998/05/18 By M.Kuwahara */
//					CMN_StringCopy( &List.S.Print[7],
//					  SYB_SpeedDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Speed].Name );
#endif
				/*	CMN_StringCopyNum( &List.S.Print[7-1],By Y.Suzuki 1998/05/19 */
				/* CMN_StringCopyNum ‚ÍANULL‚ðŒŸo‚µ‚Ä‚­‚ê‚È‚¢BƒSƒ~ƒf[ƒ^‚ªÚ‚é‚±‚Æ‚ª—L‚éB*/
#if (PRO_OP_SPPED_4_FIGURE == ENABLE) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */	/* if 1 ‚É‚È‚Á‚Ä‚¢‚½‚ªA‚RŒ…Žž‚É•¶Žš‚ª‚¸‚ê‚é‚Ì‚ÅðŒ‚Â‚¯‚Ü‚· 2003/01/07 T.Takagi */
					if (CHK_UNI_OptionalSpeedDial() != 0) {
						CMN_StringCopyNumUntilNull(&List.S.Print[8-1],
							  SYB_SpeedDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Speed].Name, dial_length - 9);
					}
					else {
						CMN_StringCopyNumUntilNull( &List.S.Print[7-1],
/*							  SYB_SpeedDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Speed].Name, 21 );*/
							/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
							  SYB_SpeedDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Speed].Name, dial_length - 8 );
					}
#else
					CMN_StringCopyNumUntilNull( &List.S.Print[7-1],
/*						  SYB_SpeedDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Speed].Name, 21 );*/
						/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
						  SYB_SpeedDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Speed].Name, dial_length - 8 );
#endif
				}
				else { /**	‘ŠŽèæ–¼‚ª“o˜^‚³‚ê‚Ä‚¢‚È‚¢ê‡“d˜b”Ô†‚ðˆóŽš‚·‚é	*/
					CMN_BCD_ToASC_String( List.S.Work,
					  SYB_SpeedDial[SYB_ExecQueue[number].ExecDial.ExecNumber.Speed].Dial );
/*					CMN_StringCopyNum( &List.S.Print[7], List.S.Work, 18 );*/	/* 1998/05/18 By M.Kuwahara */
				/*	CMN_StringCopyNum( &List.S.Print[7-1], List.S.Work, 18 );By Y.Suzuki 1998/05/19 */

					/* ÀÞ²ÔÙŒ…‚ª21•¶Žš‚ð‰z‚¦‚½‚çu¥¥‰º20Œ…v‚ðˆóŽš‚·‚éˆ—’Ç‰Á 1998/10/28 Y.Matsukuma */
					num_cnt = DialWithinCheck(List.S.Work);
#if (0)
//					if (CHK_UNI_DialWithin() && num_cnt > 21) {	/* ÕÆ°¸SW I7-0 */
//						num_cnt = num_cnt - 21;
//						List.S.Work[num_cnt] = LST_A_TENTEN;
//							CMN_StringCopyNum( &List.S.Print[7-1], &List.S.Work[num_cnt], 21 );
//					}
//					else {
//							CMN_StringCopyNum( &List.S.Print[7-1], List.S.Work, 21 );
//					}
#else
					/*
					 * u¥¥‰º20Œ…v‚ðˆóŽš‚·‚éˆ—‚Æ¼—ï‚SŒ…‘Î‰ž‚Ìˆ—‚ª“¯Žž‚É‚ ‚é‚ÆA
					 * ³‚µ‚­u¥¥‰º20Œ…v‚ðˆóŽš‚Å‚«‚È‚¢•s‹ï‡ bythonda2000/03/13
					 */
 #if (PRO_OP_SPPED_4_FIGURE == ENABLE) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */	/* if 1 ‚É‚È‚Á‚Ä‚¢‚½‚ªA‚RŒ…Žž‚É•¶Žš‚ª‚¸‚ê‚é‚Ì‚ÅðŒ‚Â‚¯‚Ü‚· 2003/01/07 T.Takagi */
					if (CHK_UNI_OptionalSpeedDial() != 0) {
						if (CHK_UNI_DialWithin() && (num_cnt > (dial_length - 9))) {	/* ÕÆ°¸SW I7-0 */
							num_cnt = num_cnt - dial_length + 9;
							List.S.Work[num_cnt] = LST_A_TENTEN;
							/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
							CMN_StringCopyNum( &List.S.Print[8-1], &List.S.Work[num_cnt], dial_length - 9 );
						}
						else {
							/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
							CMN_StringCopyNum( &List.S.Print[8-1], List.S.Work, dial_length - 9 );
						}
					}
					else {
						if (CHK_UNI_DialWithin() && (num_cnt > (dial_length - 8))) {	/* ÕÆ°¸SW I7-0 */
							num_cnt = num_cnt - dial_length + 8;
							List.S.Work[num_cnt] = LST_A_TENTEN;
							/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
							CMN_StringCopyNum( &List.S.Print[7-1], &List.S.Work[num_cnt], dial_length - 8 );
						}
						else {
							/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
							CMN_StringCopyNum( &List.S.Print[7-1], List.S.Work, dial_length - 8 );
						}
					}
 #else
  #if 0	/* ƒvƒŒƒtƒBƒbƒNƒX{ƒ_ƒCƒ„ƒ‹”Ô†‚Å40Œ…‚ð’´‚¦‚Ä‚àÜ‚è•Ô‚µ‚ÄˆóŽš‚µ‚È‚¢‚Ì‚ÅA‘å“‡‚³‚ñŠm”F‚ÌãAƒŠƒXƒg‚Å‚Ì“WŠJ‚ÍŽ~‚ß‚Ü‚· by K.Watanabe 2004/11/12 */
//  #if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/09 *//* by K.Watanabe 2004/10/12 */
//				if (List.S.Work[0] == '!'){
//					length = CMN_StringLength(SYB_MercuryDialBuffer);	/* ƒ}ƒLƒ…ƒŠ[“o˜^Œ… */
//					List.S.Print[6] = '[';
//					
//					if (CHK_UNI_DialWithin() && num_cnt > (dial_length - 9 - length)){	/* ÕÆ°¸SW I7-0 */
//						if (length > 3){
//							List.S.Print[7] = LST_A_TENTEN;
//							CMN_StringCopyNum( &List.S.Print[8], &SYB_MercuryDialBuffer[length - 3], 3);
//							List.S.Print[11] = ']';
//							
//							if (num_cnt > dial_length - 13){
//								List.S.Print[12] = LST_A_TENTEN;
//								CMN_StringCopyNum( &List.S.Print[13],
//									&List.S.Work[num_cnt - dial_length + 15], dial_length - 15);
//							}
//							else{
//								CMN_StringCopyNum( &List.S.Print[12], &List.S.Work[1], dial_length - 14);
//							}
//						}
//						else{
//							CMN_StringCopyNum( &List.S.Print[7], &SYB_MercuryDialBuffer, length);
//							List.S.Print[7 + length] = ']';
//					
//							List.S.Print[8 + length] = LST_A_TENTEN;
//							CMN_StringCopyNum( &List.S.Print[9 + length],
//								&List.S.Work[num_cnt - dial_length + 11 + length],
//								dial_length - 11 -length);
//						}
//					}
//					else{
//						CMN_StringCopyNum( temp_str, &SYB_MercuryDialBuffer, length);
//						temp_str[length] = ']';
//						CMN_StringCopyNum( &temp_str[1 + length], &List.S.Work[1], dial_length - 8);
//						CMN_StringCopyNum( &List.S.Print[7], temp_str, dial_length - 9);
//					}
//					
//				}
//				else{
//					if (CHK_UNI_DialWithin() && (num_cnt > (dial_length - 8))) {	/* ÕÆ°¸SW I7-0 */
//						num_cnt = num_cnt - dial_length + 8;
//						List.S.Work[num_cnt] = LST_A_TENTEN;
//
//						CMN_StringCopyNum( &List.S.Print[7-1], &List.S.Work[num_cnt], dial_length - 8 );
//					}
//					else {
//						CMN_StringCopyNum( &List.S.Print[7-1], List.S.Work, dial_length - 8 );
//					}
//				}
  #else
 					if (CHK_UNI_DialWithin() && (num_cnt > (dial_length - 8))) {	/* ÕÆ°¸SW I7-0 */
						num_cnt = num_cnt - dial_length + 8;
						List.S.Work[num_cnt] = LST_A_TENTEN;
						/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
						CMN_StringCopyNum( &List.S.Print[7-1], &List.S.Work[num_cnt], dial_length - 8 );
					}
					else {
						/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
						CMN_StringCopyNum( &List.S.Print[7-1], List.S.Work, dial_length - 8 );
					}
  #endif 			/*	End of defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE) */
 #endif
#endif
				}
			}
			break;
		}
#if (PRO_BATCH_TX == ENABLE)
	}
#endif

	/**Mode */
		/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
		if (TxConfYearPrint) {
			CommunicationModeName( SYB_ExecQueue[number].Mode, &List.S.Print[24 - 1],
			  &List.S.Attribute[22 - 1] );
		}
		else {
			CommunicationModeName( SYB_ExecQueue[number].Mode, &List.S.Print[29 - 1],
			  &List.S.Attribute[29 - 1] );
		}

	/**Start */
		/* ¼—ï‚SŒ…‘Î‰ž bythonda1999/11/16 */
		if (TxConfYearPrint) {
			CriterionMinuteToDayTimeAsc( SYB_ExecQueue[number].StartTime/60, LST_YYYYMMDDHHMM1,
			  List.S.Work );
			CMN_StringCopy( &List.S.Print[33 - 1], List.S.Work );
		}
		else {
			CriterionMinuteToDayTimeAsc( SYB_ExecQueue[number].StartTime/60, LST_DDHHMM,
			  List.S.Work );
			CMN_StringCopy( &List.S.Print[39 - 1], List.S.Work );
		}

	/**Time */
	if (CHK_UNI_TCR_NoneTxTime() == FALSE) {	/* 1998/10/06 By M.Kuwahara */
		SecondToMinuteSecondAsc( SYB_ExecQueue[number].TotalTime,
		  List.S.Work , ' ' );

		if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.matsumoto */
			CMN_StringCopy( &List.S.Print[50-1], List.S.Work );
		}
		else {
			CMN_StringCopy( &List.S.Print[48-1], List.S.Work );
		}
	}

	/**Pages */
	CMN_UnsignedIntToASC_NULL( List.S.Work,
	  ((UWORD)SYB_ExecQueue[number].Page ), 3, ' ' );

		if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.matsumoto */
			CMN_StringCopy( &List.S.Print[57-1], List.S.Work );
		}
		else {
			CMN_StringCopy( &List.S.Print[55-1], List.S.Work );
		}

	/**Result */
	if ( (SYB_ExecQueue[number].Result & ECM_MODE_SET) != 0 ) {

		if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.matsumoto */
			List.S.Print[62-1] = '*';
		}
		else {
			List.S.Print[60-1] = '*';
		}
	}

	/* ˆÈ‰º3s’Ç‰Á By O.Kimoto 1997/06/27 */
	if ( (SYB_ExecQueue[number].Result & V34_MODE_SET) != 0 ) {	/* ‚u‚R‚SŒðMŽž */

		if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.matsumoto */
			List.S.Print[62-1] = '#';
		}
		else {
			List.S.Print[60-1] = '#';
		}
	}

#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/4 K.Kawata */
	if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.matsumoto */
		CommunicationResultName(SYB_ExecQueue[number].Result, LST_NAME_SHORT,
		LST_RESULT_COMMON, &List.S.Print[63-1], &List.S.Attribute[61-1]);
	}
	else {
		CommunicationResultName(SYB_ExecQueue[number].Result, LST_NAME_SHORT,
		LST_RESULT_COMMON, &List.S.Print[61-1], &List.S.Attribute[61-1]);
	}
#else
	if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.matsumoto */
		CommunicationResultName( SYB_ExecQueue[number].Result, LST_NAME_SHORT,
		  LST_RESULT_TX_CONF, &List.S.Print[64-1], &List.S.Attribute[62-1] );
	}
	else {
		CommunicationResultName( SYB_ExecQueue[number].Result, LST_NAME_SHORT,
		  LST_RESULT_TX_CONF, &List.S.Print[62-1], &List.S.Attribute[62-1] );
		/* CMN_StringCopyNULL( &List.S.Print[63] , PWRD_Ok); */ /* For debug 1996/05/20 */
	}
#endif

	/**Note */

	if ( SYB_ExecQueue[number].Kind == SYS_COMMAND_TRX ) {
		if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.matsumoto */
			CommunicationKindName( SYB_CommandFile[SYS_DocumentPrintNo].Option.Item, LST_NAME_1,
			  &List.S.Print[71-1], &List.S.Attribute[71-1] );
		}
		else {
			CommunicationKindName( SYB_CommandFile[SYS_DocumentPrintNo].Option.Item, LST_NAME_1,
			  &List.S.Print[71-1], &List.S.Attribute[71-1] );
		}
	}
#if (PRO_BATCH_TX == ENABLE)	/* 97/10/15 By M.Kuwahara */
	else{
 #if defined(POPLAR_F)
		if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.matsumoto */
			AttributeSet( &List.S.Print[71-1], &List.S.Attribute[71-1], PWRD_Batch, LST_NOT );
		}
		else {
			AttributeSet( &List.S.Print[71-1], &List.S.Attribute[71-1], PWRD_Batch, LST_NOT );
		}
 #else
		AttributeSet( &List.S.Print[68-1], &List.S.Attribute[68-1], PWRD_Batch, LST_NOT );
 #endif
	}
#endif
	if ( (ret = CharacterPrint( (UBYTE)(LST_PRINT+prn_mode) )) != OK ) {
		return ( ret );
	}

#if (PRO_NEW_TX_CONF == DISABLE) /* By H.Fujimura 2000/01/28 */
	/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
	Print_TxConf_Line(4, List.S.Print, List.S.Attribute);
	if ((ret = CharacterPrint((UBYTE)(LST_PRINT+prn_mode))) != OK) {
		return (ret);
	}
#endif

	return (OK);
}



/*************************************************************************
	module		:[Žè“®‘—M‚Ì‘—MØ‚ð‚P’ÊMˆóü]
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
	date		:[1996/06/24]
	author		:[•½”ö ‰p“T]
*************************************************************************/
WORD					Print_ManualTxConf_Detail(
								UBYTE number )	/*‘—Mƒtƒ@ƒCƒ‹”Ô†*/
{
	WORD	ret;			/**ŽÀsŒ‹‰Ê */

#if defined(EUR)	/* DTS‘Îô[Bb5.1.1-4] Journal(TCR)‚Ì‹Lq•û–@ S.Fukui Nov.5,1999 */
					/* kaki‚©‚çˆÚA by M.Harada 1999/11/17 */
	if (Print_TTI_InsteadOfLineNumber(number, 1) == TRUE) {
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
	  		return ( ret );
		}
	}
#else	/* ]—ˆˆ— */
	/* ˆÈ‰º‚Ts’Ç‰Á By O.Kimoto 1997/06/27 */
 #if !defined(KEISATSU)	/* ŒxŽ@FAX DVT_ID60 Modify by SMuratec ‰Ä 2005/12/07 */
	if (Print_LineNumber(number, 1) == TRUE) {
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
	  		return ( ret );
		}
	}
 #endif
#endif

	/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
	Print_TxConf_Line( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint(LST_PRINT)) != OK ) {
		return ( ret );
	}

	/**ETelephone NumberEModeEStartETimeEPageEResultENoteE*/
	Print_TxConf_Line( 1, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint(LST_PRINT)) != OK ) {
		return ( ret );
	}

	/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
	Print_TxConf_Line( 2, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint(LST_PRINT)) != OK ) {
		return ( ret );
	}

	/**†¾                      †¢      E      E     E      E      E     E*/
	Print_TxConf_Line( 3, List.S.Print, List.S.Attribute );

	/**Location*/
	CMN_StringCopy( &List.S.Print[2-1], SYB_JournalFile[number].RemoteID_TTI );

	if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.Matsumoto */
		/**Mode */
		CommunicationModeName( SYB_JournalFile[number].Mode, &List.S.Print[24-1], &List.S.Attribute[24-1] );
		/**Start */
		CriterionMinuteToDayTimeAsc( SYB_JournalFile[number].StartTime/60, LST_YYYYMMDDHHMM1, List.S.Work );
		CMN_StringCopy( &List.S.Print[33-1], List.S.Work );
	}
	else {
		/**Mode */
		CommunicationModeName( SYB_JournalFile[number].Mode, &List.S.Print[29-1], &List.S.Attribute[29-1] );
		/**Start */
		CriterionMinuteToDayTimeAsc( SYB_JournalFile[number].StartTime/60, LST_DDHHMM, List.S.Work );
		CMN_StringCopy( &List.S.Print[39-1], List.S.Work );
	}

	/**Time */
	if (CHK_UNI_TCR_NoneTxTime() == FALSE) {	/* 1998/11/10 By M.Kuwahara */
		SecondToMinuteSecondAsc( SYB_JournalFile[number].TotalTime, List.S.Work , ' ' );
	
		if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.Matsumoto */
			CMN_StringCopy( &List.S.Print[50-1], List.S.Work );
		}
		else {
			CMN_StringCopy( &List.S.Print[48-1], List.S.Work );
		}
	}

	/**Pages */
	CMN_UnsignedIntToASC_NULL( List.S.Work, ((UWORD)SYB_JournalFile[number].Page ), 3, ' ' );

	if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.Matsumoto */
		CMN_StringCopy( &List.S.Print[57-1], List.S.Work );
	}
	else {
		CMN_StringCopy( &List.S.Print[55-1], List.S.Work );
	}
	
	/**Result */
	if ( (SYB_JournalFile[number].Result & ECM_MODE_SET) != 0 ) {
		if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.Matsumoto */
			List.S.Print[62-1] = '*';
		}
		else {
			List.S.Print[60-1] = '*';
		}
	}
#if defined(POPLAR_F) || (defined(POPLAR_H) && defined(JP0)) || defined(SAKAKI) /* SAKAKI’Ç‰Á By M.Maeda 2002/12/11 */
	if ( (SYB_JournalFile[number].Result & V34_MODE_SET) != 0 ) {	/* ‚u‚R‚SŒðMŽž */
		if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.Matsumoto */
			List.S.Print[62-1] = '#';
		}
		else {
			List.S.Print[60-1] = '#';
		}
	}
#elif defined(STOCKHM2)		/* DVT: Added by SMuratec K.W.Q 2004/09/17 */
	if ( (SYB_JournalFile[number].Result & V34_MODE_SET) != 0 ) {	/* ‚u‚R‚SŒðMŽž */
		if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.Matsumoto */
			List.S.Print[62-1] = '#';
		}
		else {
			List.S.Print[60-1] = '#';
		}
	}
#endif

#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000/03/16 M.Matsumoto */
	if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.Matsumoto */
		CommunicationResultName( SYB_JournalFile[number].Result, LST_NAME_SHORT,
	  LST_RESULT_COMMON, &List.S.Print[63-1], &List.S.Attribute[61-1] );
	}
	else {
			CommunicationResultName( SYB_JournalFile[number].Result, LST_NAME_SHORT,
		  LST_RESULT_COMMON, &List.S.Print[61-1], &List.S.Attribute[61-1] );
	}
#else
	if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.Matsumoto */
		CommunicationResultName( SYB_JournalFile[number].Result, LST_NAME_SHORT,
		  LST_RESULT_TX_CONF, &List.S.Print[64-1], &List.S.Attribute[62-1] );
	}
	else {
		CommunicationResultName( SYB_JournalFile[number].Result, LST_NAME_SHORT,
		  LST_RESULT_TX_CONF, &List.S.Print[62-1], &List.S.Attribute[62-1] );
	}
#endif

	/**Note */
	if (TxConfYearPrint) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/03/16 M.Matsumoto */
		CommunicationKindName( SYB_JournalFile[number].Kind, LST_NAME_1,
		  &List.S.Print[71-1], &List.S.Attribute[71-1] );
	}
	else {
		CommunicationKindName( SYB_JournalFile[number].Kind, LST_NAME_1,
		  &List.S.Print[71-1], &List.S.Attribute[71-1] );
	}
	
	if ( (ret = CharacterPrint(LST_PRINT)) != OK ) {
		return ( ret );
	}

#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/03/16 M.Matsumoto */
	if ( (SYB_JournalFile[number].Result & 0x0C00) == NO_ERROR ) {
		/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
		Print_TxConf_Line( 4, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint(LST_PRINT)) != OK ) {
			return ( ret );
		}
	}
	else {
		Print_TxConf_Line( 5, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint(LST_PRINT)) != OK ) {
			return ( ret );
		}
		if ( (ret = MunualTxDocumentMessage(number)) != OK ) {
			return (ret);
		}
	}

#else

	/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
	Print_TxConf_Line( 4, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint(LST_PRINT)) != OK ) {
		return ( ret );
	}
#endif

	return ( OK );
}

/*************************************************************************
	module		:[‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs]
	function	:[‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs‚ðs‚¤B]
	common		:[
		SYB_TTI_Buffer	:
		SYB_ID_Buffer	:
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
WORD			TTI_ID_Print_Feed(
						 void )		/*‚È‚µ*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
	/*”­MŒ³–¼{”­MŒ³”Ô†*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );

#if (0)
** /* ƒWƒƒ[ƒiƒ‹ƒvƒŠƒ“ƒgŽžA‰ñü–ˆ‚Ì”­MŒ³î•ñˆóŽš‘Î‰ž By O.Kimoto 1999/11/09 */
** /* ‚o‚n‚o‚k‚`‚qQ‚g •W€‚Q‰ñüŽû—e‘Î‰ž‚Ìˆ× By O.Kimoto 1997/11/01 */
** #if (PRO_LINENUMBER == TWICE_LINE)
** 	CMN_StringCopy( &List.S.Print[1-1], &SYB_TTI_Buffer[0][0]);
** 	if ( SYB_ID_Buffer[0][0] != NULL ) {
** 		AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD,
** 		  LST_NOT );
** 		CMN_StringCopy( &List.S.Print[28-1], &SYB_ID_Buffer[0][0]);
** 	}
** #else
** 	CMN_StringCopy( &List.S.Print[1-1], SYB_TTI_Buffer);
** 	if ( SYB_ID_Buffer[0] != NULL ) {
** 		AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD,
** 		  LST_NOT );
** 		CMN_StringCopy( &List.S.Print[28-1], SYB_ID_Buffer);
** 	}
** #endif
#else
 #if (PRO_COM_RESULT == ENABLE) /* 2002/08/22 By M.Maeda */
	if ((SYS_DocumentPrintItem == LST_JOURNAL_LIST) 				/**’ÊMŠÇ—ƒŒƒ|[ƒgu‘—ŽóMv*/
	 || (SYS_DocumentPrintItem == LST_COM_RESULT_LIST)) {
 #else
	if (SYS_DocumentPrintItem == LST_JOURNAL_LIST) {				/**’ÊMŠÇ—ƒŒƒ|[ƒgu‘—ŽóMv*/
 #endif
		/* ƒWƒƒ[ƒiƒ‹‚Ìê‡ */
 #if (PRO_MULTI_LINE == ENABLE)
  #if (PRO_LINENUMBER == TWICE_LINE)
		if (JournalLineNumber == 1) {	/* “à‘ ‰ñü‚Å‚· */
			CMN_StringCopy( &List.S.Print[1-1], &SYB_TTI_Buffer[InternalLineNumber][0]);
			if ( SYB_ID_Buffer[InternalLineNumber][0] != NULL ) {
				AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD,LST_NOT );
				CMN_StringCopy( &List.S.Print[28-1], &SYB_ID_Buffer[InternalLineNumber][0]);
			}
		}
		else {	/* ŠO•t‚¯‰ñü‚Å‚· */
			CMN_StringCopy( &List.S.Print[1-1], &SYB_Option_TTI_Buffer[(JournalLineNumber - 1)][0]);
			if ( SYB_Option_ID_Buffer[(JournalLineNumber -1)][0] != NULL ) {
				AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD, LST_NOT );
				CMN_StringCopy( &List.S.Print[28-1], &SYB_Option_ID_Buffer[(JournalLineNumber -1)][0]);
			}
		}
  #else
		if (JournalLineNumber == 1) {	/* “à‘ ‰ñü‚Å‚· */
			CMN_StringCopy( &List.S.Print[1-1], SYB_TTI_Buffer);
			if ( SYB_ID_Buffer[0] != NULL ) {
				AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD,LST_NOT );
				CMN_StringCopy( &List.S.Print[28-1], SYB_ID_Buffer);
			}
		}
		else {	/* ŠO•t‚¯‰ñü‚Å‚· */
			CMN_StringCopy( &List.S.Print[1-1], &SYB_Option_TTI_Buffer[(JournalLineNumber - 1)][0]);
			if ( SYB_Option_ID_Buffer[(JournalLineNumber -1)][0] != NULL ) {
				AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD, LST_NOT );
				CMN_StringCopy( &List.S.Print[28-1], &SYB_Option_ID_Buffer[(JournalLineNumber -1)][0]);
			}
		}
  #endif
 #else
  /* ]—ˆ‚Ìƒpƒ^[ƒ“ */
  #if (PRO_LINENUMBER == TWICE_LINE)
		CMN_StringCopy( &List.S.Print[1-1], &SYB_TTI_Buffer[0][0]);
		if ( SYB_ID_Buffer[0][0] != NULL ) {
			AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD,
			  LST_NOT );
			CMN_StringCopy( &List.S.Print[28-1], &SYB_ID_Buffer[0][0]);
		}
  #else
	 #if defined(EUR)		/* addedbythonda1999/11/04 */
							/* kaki‚©‚çˆÚA by M.Harada 1999/11/17 */
		/* ‚Q‰ñüŽd—l‚ÌƒWƒƒ[ƒiƒ‹‚Ìƒwƒbƒ_[•”•ª‚ÉÚ‚¹‚é”­MŒ³–¼E”­MŒ³”Ô†‚Í	*/
		/* ‚Q‰ñü–Ú‚Ì”­MŒ³‚Ìî•ñ‚ðÚ‚¹‚éŽ–‚É‚µ‚Ü‚·B							*/
		if ( JournalLineNumber == 1 ) {
			CMN_StringCopy( &List.S.Print[1-1], SYB_TTI_Buffer);
			if ( SYB_ID_Buffer[0] != NULL ) {
				AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD, LST_NOT );
				CMN_StringCopy( &List.S.Print[28-1], SYB_ID_Buffer);
			}
		}
		else {
			CMN_StringCopy( &List.S.Print[1-1], &SYB_Option_TTI_Buffer[JournalLineNumber - 1][0]);
			if ( SYB_Option_ID_Buffer[JournalLineNumber - 1][0] != NULL ) {
				AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD, LST_NOT );
				CMN_StringCopy( &List.S.Print[28-1], &SYB_Option_ID_Buffer[JournalLineNumber -1][0]);
			}
		}

	 #else
			CMN_StringCopy( &List.S.Print[1-1], SYB_TTI_Buffer);
			if ( SYB_ID_Buffer[0] != NULL ) {
				AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD,
				  LST_NOT );
				CMN_StringCopy( &List.S.Print[28-1], SYB_ID_Buffer);
			}
	 #endif
  #endif
 #endif

	}
	else {
	/* ƒWƒƒ[ƒiƒ‹ˆÈŠO‚Ìê‡ */
 #if (PRO_LINENUMBER == TWICE_LINE)
		CMN_StringCopy( &List.S.Print[1-1], &SYB_TTI_Buffer[0][0]);
		if ( SYB_ID_Buffer[0][0] != NULL ) {
			AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD,
			  LST_NOT );
			CMN_StringCopy( &List.S.Print[28-1], &SYB_ID_Buffer[0][0]);
		}
 #else
		CMN_StringCopy( &List.S.Print[1-1], SYB_TTI_Buffer);
		if ( SYB_ID_Buffer[0] != NULL ) {
			AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD,
			  LST_NOT );
			CMN_StringCopy( &List.S.Print[28-1], SYB_ID_Buffer);
		}
 #endif
	}
#endif


#if ( PRO_MAKER == FX )		/* FX‚Í”­MŒ³ƒŠƒXƒg‚ÅŒ»Ý“úŽž‚à•t‚¯‚é 94.09.14 */
	if (SYS_DocumentPrintItem == LST_TTI_LIST) {
		TimeDataAscii( ON, SYB_CurrentTime, &List.S.Print[49-1], 0 );
	}
#endif
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*‚QsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED +2)) != OK ) {
		return ( ret );
	}
	return ( OK );
}

/*************************************************************************
	module		:[ˆóüACü•¶Žš—ñƒNƒŠƒA[n
	function	:[ˆóüACü•¶Žš—ñ‚ðƒNƒŠƒA[‚·‚éB]
	common		:[]
	condition	:[
		ˆóü•¶Žš—ñ
		,	•K—v‚È‚¢Žž‚ÍAƒ|ƒCƒ“ƒ^[‚Éƒkƒ‹ƒ|ƒCƒ“ƒ^[‚ðƒZƒbƒg
		Cü•¶Žš—ñ
		,	•K—v‚È‚¢Žž‚ÍAƒ|ƒCƒ“ƒ^[‚Éƒkƒ‹ƒ|ƒCƒ“ƒ^[‚ðƒZƒbƒg
	]
	commment	:[
		near call ‚ð far call ‚É•ÏX	Line 346
	]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
void			Prn_Att_Str_Clear(	/* '94.09/09 By M.mannnami */
						 register UBYTE *prn_str,/*ˆóü•¶Žš—ñ*/
						 register UBYTE *att_str )	/*Cü•¶Žš—ñ*/
{
	if ( prn_str != NULL_PT ) {
		CMN_MemorySetNULL( prn_str, LST_COLUM-1, ' ' );
	}
	if ( att_str != NULL_PT ) {
		CMN_MemorySetNULL( att_str, LST_COLUM-1, ' ' );
	}
}

/*************************************************************************
	module		:[Œ»Ý“úŽžˆóü]
	function	:[Œ»Ý“úŽž‚ðŽw’èŒ…ˆÊ’u‚Éˆóü‚·‚éB]
	common		:[
		List			:
		SYB_CurrentTime	:
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
WORD				CurrentTimePrint(
						 UBYTE LocateX )	/*ˆóüŒ…ˆÊ’u*/
{

	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	TimeDataAscii( OFF, SYB_CurrentTime, List.S.Work, 0 );
	CMN_StringCopy( &List.S.Print[LocateX], List.S.Work);
	return ( CharacterPrint( LST_PRINT ) );
}

/*************************************************************************
	module		:[‘—MØAŽó—ÌØ‚Ì‰¡‹æØ‚èŒrüì¬]
	function	:[‘—MØAŽó—ÌØ‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
		,	0 = †®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²
		,	1 = †¤						  †¤
		,	2 = †¾†¢†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†Æ
		,	3 = †¤			†¤			  †¤
		,	4 = †¾†¢†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Æ
		,	5 = †¶†¢†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†º
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
void				Print_Conf_List_Line(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
			AscString[13-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[14-1], 53, LST_KLINE_ );
			AscString[67-1] = LST_KLINE9;
			break;
		case 1:
			/*†¤						†¤*/
			AscString[13-1] = LST_KLINEI;
			AscString[67-1] = LST_KLINEI;
			break;
		case 2:
			/*†¾†¢†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†Æ*/
			AscString[13-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[14-1], 53, LST_KLINE_ );
			AscString[33-1] = LST_KLINE8;
			AscString[67-1] = LST_KLINE6;
			break;
		case 3:
			/*†¤		  †¤			†¤*/
			AscString[13-1] = LST_KLINEI;
			AscString[33-1] = LST_KLINEI;
			AscString[67-1] = LST_KLINEI;
			break;
		case 4:
			/*†¾†¢†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Æ*/
			AscString[13-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[14-1], 53, LST_KLINE_ );
			AscString[33-1] = LST_KLINE5;
			AscString[67-1] = LST_KLINE6;
			break;
		case 5:
			/*†¶†¢†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†º*/
			AscString[13-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[14-1], 53, LST_KLINE_ );
			AscString[33-1] = LST_KLINE2;
			AscString[67-1] = LST_KLINE3;
			break;
#if (PRO_COM_RESULT == ENABLE) /* 2002/08/22 By M.Maeda */
		case 6:
			/*†¢†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†Æ*/
			AscString[13-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[14-1], 53, LST_KLINE_ );
			AscString[33-1] = LST_KLINE8;
			AscString[67-1] = LST_KLINE9;
			break;
#endif
	}
}

/*************************************************************************
	module		:[‘—MØ‚Ì‰¡‹æØ‚èŒrüì¬]
	function		:[‘—MØ‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition		:[
				  ŒrüŽí—Þ
		,			0 = EEEEEEEEEEEEEEEEEEEEEEEEEEEEE
		,			1 = ETelephone NumberEModeEStartETimeEPageEResultENoteE
		,			2 = EEEEEEEEEEEEEEEEEEEEEEEEEEEEE
		,			3 = †¾                      †¢      E      E     E      E      E     E
					4 = EEEEEEEEEEEEEEEEEEEEEEEEEEEEE
					5 = E   Location     EModeEStartETimeEPageEResultENoteE
					ƒ‰ƒCƒ“‚T‚ð’Ç‰Á‚µ‚Ü‚· 1997/11/12 Y.Matsukuma
					]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[Apr.16,1996]
	author		:[•½”ö ‰p“T]
*************************************************************************/
void				Print_TxConf_Line(
								UBYTE Category,			/**ŒrüŽí—Þ */
						 		UBYTE *AscString,			/**ˆóü•¶Žš—ñ */
						 		UBYTE *AttString )			/**Cü•¶Žš—ñ */
{

	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
			AscString[1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );

			if( TxConfYearPrint ) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/3/16 M.Matsumoto	*/
				AscString[23-1] = LST_KLINE8;
				AscString[32-1] = LST_KLINE8;
				AscString[49-1] = LST_KLINE8;
				AscString[56-1] = LST_KLINE8;
				AscString[61-1] = LST_KLINE8;
				AscString[69-1] = LST_KLINE8;
				AscString[80-1] = LST_KLINE9;

			}
			else {
				AscString[28-1] = LST_KLINE8;
				AscString[38-1] = LST_KLINE8;
				AscString[47-1] = LST_KLINE8;
				AscString[54-1] = LST_KLINE8;
				AscString[59-1] = LST_KLINE8;
				AscString[67-1] = LST_KLINE8;
				AscString[80-1] = LST_KLINE9;

			}
			break;
		case 1:
			/**ETelephone NumberEModeEStartETimeEPageEResultENoteE*/
			AscString[1-1] = LST_KLINEI;

			if( TxConfYearPrint ) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/3/16 M.Matsumoto	*/
				AttributeSet( &AscString[4 - 1], &AttString[4 - 1], PWRD_TeleNumber, LST_NOT );
				AttributeSet( &AscString[23 - 1], &AttString[23 - 1], PWRD_Mode, LST_NOT );
				AscString[22] = LST_KLINEI;
				AscString[31] = LST_KLINEI;
				AttributeSet( &AscString[37 - 1], &AttString[37 - 1], PWRD_Start, LST_NOT );
				AscString[49-1] = LST_KLINEI;
				AttributeSet( &AscString[50-1], &AttString[50-1], PWRD_Time, LST_NOT );
				AscString[56-1] = LST_KLINEI;
				AttributeSet( &AscString[57-1], &AttString[57-1], PWRD_Page, LST_NOT );
				AscString[61-1] = LST_KLINEI;
				AttributeSet( &AscString[62-1], &AttString[62-1], PWRD_Result, LST_NOT );
				AscString[69-1] = LST_KLINEI;
				AttributeSet( &AscString[71-1], &AttString[71-1], PWRD_Note, LST_NOT );
				AscString[80-1] = LST_KLINEI;

			}
			else {
				AttributeSet( &AscString[5 - 1], &AttString[5 - 1], PWRD_TeleNumber, LST_NOT );
				AscString[27] = LST_KLINEI;
				AttributeSet( &AscString[29 - 1], &AttString[29 - 1], PWRD_Mode, LST_NOT );
				AscString[37] = LST_KLINEI;
				AttributeSet( &AscString[39 - 1], &AttString[39 - 1], PWRD_Start, LST_NOT );
				AscString[47-1] = LST_KLINEI;
				AttributeSet( &AscString[48-1], &AttString[48-1], PWRD_Time, LST_NOT );
				AscString[54-1] = LST_KLINEI;
				AttributeSet( &AscString[55-1], &AttString[55-1], PWRD_Page, LST_NOT );
				AscString[59-1] = LST_KLINEI;
				AttributeSet( &AscString[60-1], &AttString[60-1], PWRD_Result, LST_NOT );
				AscString[67-1] = LST_KLINEI;
				AttributeSet( &AscString[71-1], &AttString[71-1], PWRD_Note, LST_NOT );
				AscString[80-1] = LST_KLINEI;

			}

			break;
		case 2:
			/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[1], 78, LST_KLINE_ );

			if( TxConfYearPrint ) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/3/16 M.Matsumoto	*/
				AscString[23-1] = LST_KLINE5;
				AscString[32-1] = LST_KLINE5;
				AscString[49-1] = LST_KLINE5;
				AscString[56-1] = LST_KLINE5;
				AscString[61-1] = LST_KLINE5;
				AscString[69-1] = LST_KLINE5;
				AscString[80-1] = LST_KLINE6;

			}
			else {
				AscString[28-1] = LST_KLINE5;
				AscString[38-1] = LST_KLINE5;
				AscString[47-1] = LST_KLINE5;
				AscString[54-1] = LST_KLINE5;
				AscString[59-1] = LST_KLINE5;
				AscString[67-1] = LST_KLINE5;
				AscString[80-1] = LST_KLINE6;
			}
			break;
		case 3:
			/**†¾                      †¢      E      E     E      E      E     E*/
			AscString[1-1] = LST_KLINEI;

			if( TxConfYearPrint ) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/3/16 M.Matsumoto	*/
				AscString[23-1] = LST_KLINEI;
				AscString[32-1] = LST_KLINEI;
				AscString[49-1] = LST_KLINEI;
				AscString[56-1] = LST_KLINEI;
				AscString[61-1] = LST_KLINEI;
				AscString[69-1] = LST_KLINEI;
				AscString[80-1] = LST_KLINEI;

			}
			else {
				AscString[28-1] = LST_KLINEI;
				AscString[38-1] = LST_KLINEI;
				AscString[47-1] = LST_KLINEI;
				AscString[54-1] = LST_KLINEI;
				AscString[59-1] = LST_KLINEI;
				AscString[67-1] = LST_KLINEI;
				AscString[80-1] = LST_KLINEI;
			}
			break;
		case 4:
			/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[1], 78, LST_KLINE_ );

			if( TxConfYearPrint ) {		/* ¼—ï‚SŒ…‘Î‰ž 2000/3/16 M.Matsumoto	*/
				AscString[23-1] = LST_KLINE2;
				AscString[32-1] = LST_KLINE2;
				AscString[49-1] = LST_KLINE2;
				AscString[56-1] = LST_KLINE2;
				AscString[61-1] = LST_KLINE2;
				AscString[69-1] = LST_KLINE2;
				AscString[80-1] = LST_KLINE3;

			}
			else {
				AscString[28-1] = LST_KLINE2;
				AscString[38-1] = LST_KLINE2;
				AscString[47-1] = LST_KLINE2;
				AscString[54-1] = LST_KLINE2;
				AscString[59-1] = LST_KLINE2;
				AscString[67-1] = LST_KLINE2;
				AscString[80-1] = LST_KLINE3;
			}
			break;
#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/4 K.Kawata */
	case 5:
		/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
		AscString[1-1] = LST_KLINE4;
		CMN_MemorySet(&AscString[1], 78, LST_KLINE_);

		if( TxConfYearPrint ) {		/* ¼—ï‚SŒ…‘Î‰ž M.matsumoto 2000/03/16	*/
			AscString[23-1] = LST_KLINE2;
			AscString[32-1] = LST_KLINE2;
			AscString[49-1] = LST_KLINE2;
			AscString[56-1] = LST_KLINE2;
			AscString[61-1] = LST_KLINE2;
			AscString[69-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE6;

		}
		else {
			AscString[28-1] = LST_KLINE2;
			AscString[38-1] = LST_KLINE2;
			AscString[47-1] = LST_KLINE2;
			AscString[54-1] = LST_KLINE2;
			AscString[59-1] = LST_KLINE2;
			AscString[67-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE6;
		}
		break;
	case 6:
		/**E@@@@@@@@@@@@@@@@@@@@@@@@@@@E*/
		AscString[1-1] = LST_KLINEI;
		AscString[80-1] = LST_KLINEI;
		break;
	case 7:
		/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
		AscString[1-1] = LST_KLINE4;
		CMN_MemorySet(&AscString[2-1], 78, LST_KLINE_);
		if( TxConfYearPrint ) {		/* ¼—ï‚SŒ…‘Î‰ž M.matsumoto 2000/03/16	*/
			AscString[23-1] = LST_KLINE8;
			AscString[32-1] = LST_KLINE8;
			AscString[49-1] = LST_KLINE8;
			AscString[56-1] = LST_KLINE8;
			AscString[61-1] = LST_KLINE8;
			AscString[69-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE6;
		}
		else {
			AscString[28-1] = LST_KLINE8;
			AscString[38-1] = LST_KLINE8;
			AscString[47-1] = LST_KLINE8;
			AscString[54-1] = LST_KLINE8;
			AscString[59-1] = LST_KLINE8;
			AscString[67-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE6;
		}
		break;
	case 8:
		/**EEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
		AscString[1-1] = LST_KLINE1;
		CMN_MemorySet(&AscString[1], 78, LST_KLINE_);
		AscString[80-1] = LST_KLINE3;
		break;
#endif
#if (0)
** 		case 5:	/* Location‚É•ÏX 1998/01/08 Y.Matsukuma */
** 			/**ELocationEModeEStartETimeEPageEResultENoteE*/
** 			AscString[1-1] = LST_KLINEI;
** 			AttributeSet( &AscString[4], &AttString[4], PWRD_RemoteLocation, LST_NOT );
** 			AscString[28-1] = LST_KLINEI;
** 			AttributeSet( &AscString[29-1], &AttString[29-1], PWRD_Mode, LST_NOT );
** 			AscString[38-1] = LST_KLINEI;
** 			AttributeSet( &AscString[39-1], &AttString[39-1], PWRD_Start, LST_NOT );
** 			AscString[47-1] = LST_KLINEI;
** 			AttributeSet( &AscString[48-1], &AttString[48-1], PWRD_Time, LST_NOT );
** 			AscString[54-1] = LST_KLINEI;
** 			AttributeSet( &AscString[55-1], &AttString[55-1], PWRD_Page, LST_NOT );
** 			AscString[59-1] = LST_KLINEI;
** 			AttributeSet( &AscString[60-1], &AttString[60-1], PWRD_Result, LST_NOT );
** 			AscString[67-1] = LST_KLINEI;
** 			AttributeSet( &AscString[71-1], &AttString[71-1], PWRD_Note, LST_NOT );
** 			AscString[80-1] = LST_KLINEI;
** 			break;
#endif
	}
}

/*************************************************************************
	module		:[ƒ‰ƒCƒ“”Ô†ˆóŽš]
	function	:[
		1.
	]
	return		:[TRUE: •\Ž¦‚·‚é
				  FALSE:•\Ž¦‚µ‚È‚¢]
	common		:[]
	condition	:[]
	comment		:[check‚ª‚OFSYS_ExecQueue[number]
				  check‚ª‚PFSYS_JournalFile[number]
				]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1996/12/28]
	author		:[¼ŒG]
*************************************************************************/
UBYTE	Print_LineNumber(UBYTE number, UBYTE check)
{
	UBYTE	line_number;
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^Ž—‚Q‰ñüŽd—l by T.Soneoka 1997/11/20 */
	UBYTE	option;
#endif

#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^Ž—‚Q‰ñüŽd—l by T.Soneoka 1997/03/11 */
#else
	if (OPT_CountModems() < 2) { /* Žn‚ß‚ÉA•¡”‰ñü‚¶‚á‚È‚©‚Á‚½‚çA‚Í‚¶‚­‚æ‚¤‚É‚µ‚Ü‚·B1997/03/12 Y.Matsukuma */
		return(FALSE);
	}
#endif

	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );

#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^Ž—‚Q‰ñüŽd—l by T.Soneoka 1997/11/20 */
	if (check == 0) {
		option = SYB_ExecQueue[number].Option;
	}
	else {
		option = (UBYTE)SYB_JournalFile[number].Option;
	}
#endif

/* Œ³‚É–ß‚µ‚Ü‚· by T.Soneoka 1998/03/18 */
/* ‰º‹LA‘Î‰ž‚³‚ê‚½•ûI ã‹Lˆ—‚Æ“à—e‚ªˆÙ‚È‚Á‚Ä‚¢‚Ü‚·B•ÏXƒƒO‚É‚Í‹LÚ‚µ‚Ä‰º‚³‚¢B S.Fukui */
/* ã‹Lˆ—‚É‚Ü‚Æ‚ß‚Ü‚·A‚â‚Á‚Ä‚é‚±‚Æ‚Í“¯‚¶ */
	if (check == 0) {
		if (SYB_ExecQueue[number].StackNumber == 0xFF) {	/* ‰Šú’l‚Ì‚Ü‚Ü‚È‚ç•\Ž¦‚µ‚È‚¢ */
			return(FALSE);
		}
		line_number = OPT_GetMultiLinrNumber(SYB_ExecQueue[number].StackNumber);
	}
	else {
		if (SYB_ExecQueue[number].StackNumber == 0xFF) {	/* ‰Šú’l‚Ì‚Ü‚Ü‚È‚ç•\Ž¦‚µ‚È‚¢ */
			return(FALSE);
		}
		line_number = OPT_GetMultiLinrNumber((UBYTE)SYB_JournalFile[number].StackNumber);
	}

	AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1],
	  				PWRD_LineNumber, LST_NOT );

#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^Ž—‚Q‰ñüŽd—l by T.Soneoka 1997/11/20 */
	if (line_number == 1) {
		if (!(option & SYS_EXT_LINE_TX)) {
			AttributeSet( &List.S.Print[13-1], &List.S.Attribute[13-1], PWRD_LineName[0], LST_NOT );
		}
		else {
			AttributeSet( &List.S.Print[13-1], &List.S.Attribute[13-1], PWRD_LineName[1], LST_NOT );
		}
	}
	else {
		AttributeSet( &List.S.Print[13-1], &List.S.Attribute[13-1], PWRD_LineName[2], LST_NOT );
	}
#else
	CMN_UnsignedIntToASC( &List.S.Print[13-1], line_number, 1, '0' );
	/* ‰ñü”Ô†•\Ž¦‚ð –{‘Ì‚PA‚`‚k|‚P‚O‚O‚Q‚Æ‚È‚é‚æ‚¤‚É‚·‚éBBy S.Fukui Mar.18,1998 */
	/* ã‹L‚ðŒ³‚É–ß‚µ‚½‚Ì‚Å‚±‚Ìˆ—‚à–ß‚µ‚Ü‚· by T.Soneoka 1998/03/18 */
/* CMN_UnsignedIntToASC( &List.S.Print[13-1], line_number + 1, 1, '0' ); */
#endif
	return(TRUE);
}


#if (PRO_JOURNAL_PRINT_TIME == DISABLE)	/* “ú—§“Á‹–‰ñ”ð 1998/10/28 Y.Matsukuma */
/*************************************************************************
	module		:[ƒLƒ…[‚Ì‘—MƒXƒ^[ƒgŽžŠÔ‚ð“¾‚é]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1998/10/22]
	author		:[¼ŒG]
*************************************************************************/
UDWORD	TranceTime()
{
	UBYTE	i;
	UBYTE	j;

	j = 0xFF;

	for ( i = 0; i < SYS_EXEC_QUEUE_MAX; i++ ) {
		if ( (SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_MONITOR)			/* ÓÆÀ°ÚÎß°Ä */
		&&((SYB_ExecQueue[i].Kind == SYS_COMMAND_TRX) || (SYB_ExecQueue[i].Kind == SYS_BATCH_TX))
		&&(SYB_ExecQueue[i].Number.Command == (UBYTE)SYS_DocumentPrintNo)
		&&((SYB_ExecQueue[i].Status == SYS_EXEC_ERROR) || (SYB_ExecQueue[i].Status == SYS_EXEC_OK)) ) {
			if (j == 0xFF) {
				j = i;
			}
			/* ˆê”ÔŽn‚ß‚É‘—M‚µ‚½ŽžŠÔ‚ð’²‚×‚é */
			if (SYB_ExecQueue[i].StartTime < SYB_ExecQueue[j].StartTime 
				&& SYB_ExecQueue[i].StartTime != 0) {
				j = i;
			}
		}
	}

	/* ‚O‚Æ‚¢‚¤’l‚ÍAl‚¦‚ç‚ê‚È‚¢‚ªA”O‚Ì‚½‚ß‚O‚Ì‚Æ‚«Œ»ÝŽž‚ð“ü‚ê‚Æ‚«‚Ü‚· */
	if (SYB_ExecQueue[j].StartTime == 0 || j == 0xFF) {
		SYB_ExecQueue[j].StartTime = SYB_CurrentTime;
	}
	return(SYB_ExecQueue[j].StartTime);
}

#endif

/*************************************************************************
	module		:[ƒ_ƒCƒ„ƒ‹”Ô†ˆóŽš”ÍˆÍ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1998/10/23]
	author		:[¼ŒG]
*************************************************************************/
UBYTE	DialWithinCheck(CONST UBYTE *work)
{
	UBYTE i;

	for(i = 0; i < LST_COLUM; i++) {
		if (work[i] == NULL) {
			return(i);
		}
	}
	return(i);
}
			/* 2000/2/4 K.Kawata */
#if defined(EUR) || (PRO_NEW_TX_CONF == ENABLE)	/* DTS‘Îô[Bb5.1.1-4] Journal(TCR)‚Ì‹Lq•û–@ S.Fukui Nov.5,1999 */
					/* kaki‚©‚çˆÚA by M.Harada 1999/11/17 */
/*************************************************************************
	module		:[’ÊM‰ñü–ˆ‚Ì”­MŒ³–¼ˆóŽš]
	function	:[
		‚PDLine Number:x ‚Ì‘ã‚í‚è‚ÉŽg—p‚µ‚½‰ñü‚Ì”­MŒ³–¼‚ðˆóŽš‚·‚éB
	]
	return		:[TRUE: •\Ž¦‚·‚é
				  FALSE:•\Ž¦‚µ‚È‚¢]
	common		:[]
	condition	:[]
	comment		:[check‚ª‚OFSYS_ExecQueue[number]	  F Murata Machinery   Fax:075-672-1234
				  check‚ª‚PFSYS_JournalFile[number]  F Murata Machinery   Fax:075-672-1234
				]
	machine		:[SH7043]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1999/11/04]
	author		:[•Ÿˆä]
*************************************************************************/
UBYTE	Print_TTI_InsteadOfLineNumber(UWORD number, UBYTE check)
{
	UBYTE	line_number;

	if (OPT_CountModems() < 2) { /* Žn‚ß‚ÉA•¡”‰ñü‚¶‚á‚È‚©‚Á‚½‚çA‚Í‚¶‚­‚æ‚¤‚É‚µ‚Ü‚·B */
		return(FALSE);
	}

	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );

	if (check == 0) {
		if (SYB_ExecQueue[number].StackNumber == 0xFF) {	/* ‰Šú’l‚Ì‚Ü‚Ü‚È‚ç•\Ž¦‚µ‚È‚¢ */
			return(FALSE);
		}
		line_number = OPT_GetMultiLinrNumber(SYB_ExecQueue[number].StackNumber);
	}
	else {
		if (SYB_ExecQueue[number].StackNumber == 0xFF) {	/* ‰Šú’l‚Ì‚Ü‚Ü‚È‚ç•\Ž¦‚µ‚È‚¢ */
			return(FALSE);
		}
		line_number = OPT_GetMultiLinrNumber((UBYTE)SYB_JournalFile[number].StackNumber);
	}

	if ( line_number == 1 ) {
		CMN_StringCopy( &List.S.Print[1-1], SYB_TTI_Buffer);
		if ( SYB_ID_Buffer[0] != NULL ) {
			AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD, LST_NOT );
			CMN_StringCopy( &List.S.Print[28-1], SYB_ID_Buffer);
		}
	}
	else {
		CMN_StringCopy( &List.S.Print[1-1], &SYB_Option_TTI_Buffer[line_number - 1][0]);
		if ( SYB_Option_ID_Buffer[line_number - 1][0] != NULL ) {
			AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_FaxD, LST_NOT );
			CMN_StringCopy( &List.S.Print[28-1], &SYB_Option_ID_Buffer[line_number - 1][0]);
		}
	}

	return(TRUE);
}

#endif /* defined(EUR) (PRO_NEW_TX_CONF == ENABLE) 2000.2.9 K.Kawata */
#if (PRO_NEW_TX_CONF == ENABLE) /* 2000/2/16 K.Kawata */
/*************************************************************************
	module		:[VÄ‘—ƒƒbƒZ[ƒW]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2000/2/16]
	author		:[K.Kawata]
*************************************************************************/
void	NewSendDocumentMessage(UWORD exec_cnt)
{
	UBYTE	batch_no;
	UBYTE	check_poll;
	UBYTE	is_total_page_prt;
	UBYTE	page_prt_pos;		/* ƒy[ƒWˆóŽšˆÊ’u	*/
	UWORD	tx_page;			/* •ªŽq				*/
	UWORD	total_page;			/* •ª•ê				*/
	UWORD 	index_no;

	total_page = (UWORD)0;

	/**E@@@@@@@@@@@@@@@@@@@@@@@@@@@E*/
	Print_TxConf_Line(6, List.S.Print, List.S.Attribute);
 #if (PRO_JIS_CODE == ENABLE)
	CMN_StringCopy(&List.S.Print[1], (UBYTE *)"ª");
 #else
	CMN_StringCopy(&List.S.Print[1], (UBYTE *)"Ð");
 #endif
	/*Â³¼Ý¹¯¶ Ò¯¾°¼Þ*/
	if ((SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_MONITOR)
	 || (SYS_DocumentPrintClass == SYS_PRINT_CLASS_LIST_BA_MONITOR)) {	/* ÓÆÀ°ÚÎß°ÄON ˆêŠ‡‘—M */
		if ((SYB_ExecQueue[exec_cnt].Result & ~ECM_MODE_SET) == NO_ERROR) { /* ³íI—¹Žž  */
			AttributeSet(&List.S.Print[3], &List.S.Attribute[3], PWRD_CheckMessage, LST_NOT);
		}
		else {														/* ´×°I—¹Žž */
			CommunicationResultName(SYB_ExecQueue[exec_cnt].Result, LST_NAME_LONG,
			  LST_RESULT_COMMON, &List.S.Print[3], &List.S.Attribute[3]);
		}
	}
	else {
		/* Áª¯¸Ò¯¾°¼Þ */
		CommunicationResultName(SYB_ExecQueue[exec_cnt].Result, LST_NAME_LONG,
		  LST_RESULT_COMMON, &List.S.Print[3], &List.S.Attribute[3]);
	}

	/* T.4.2‚ÆT.5.3‚ÍAˆóŽš‚µ‚½‚ç‚¢‚¯‚È‚¢ */
	if ((SYB_ExecQueue[exec_cnt].Result & 0x0cff) == (TRANSMITERROR | 0x0042) 
	 || (SYB_ExecQueue[exec_cnt].Result & 0x0cff) == (TRANSMITERROR | 0x0053)) {
		return;
	}

	switch (SYB_ExecQueue[exec_cnt].Kind) {
	case SYS_COMMAND_TRX:
		total_page = SYB_CommandFile[SYB_ExecQueue[exec_cnt].Number.Command].Page;
		check_poll = SYB_CommandFile[SYB_ExecQueue[exec_cnt].Number.Command].Option.Item;
		if ((check_poll == SYS_POLLING_RX) 
		 || (check_poll == SYS_DB_POLLING_RX) 
		 || (check_poll == SYS_SELECT_POLLING_RX)) {
			/* ƒ|[ƒŠƒ“ƒO‚Ìê‡‚ÍAˆóŽš‚µ‚È‚¢ */
			return;
		}
		break;
	case SYS_BATCH_TX:
		batch_no = SYB_ExecQueue[exec_cnt].Number.Batch;
		for (index_no = 0;  index_no < SYS_BATCH_INDEX_MAX; index_no++) {
			if (SYB_BatchTxFile[batch_no].IndexNo[index_no] == SYS_BAT_DOC_STORE) {
				total_page += MEM_CountFinalPage(SYS_MEM_BATCH_TX_FILE1 + batch_no, index_no, MEM_IGNORE_BOX_NUMBER);
			}
		}
		break;
	default:
		return;
	}

	/* R.*.*‚ÍAˆóŽš‚µ‚½‚ç‚¢‚¯‚È‚¢ */
	if ((SYB_ExecQueue[exec_cnt].Result & RECEIVEERROR) == RECEIVEERROR) {
		return;
	}

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 2003/03/10 H.Yoshikawa */
	/*---------------------------------------------------------------
	 * OCAŽd—l‚É‚Â‚¢‚Ä‚ÍAŽóM‘¤OCR_Host‚Å‚ÍA’ÊMƒGƒ‰[‚Í”pŠü‚³‚ê‚éŽd—l‚Æ‚È‚Á‚Ä‚¢‚Ü‚·B
	 * ’ÊMƒGƒ‰[‚ª”­¶‚µ‚½ê‡‚É‚ÍA‚Pƒy[ƒW–Ú‚©‚ç‘—M‚µ‚È‚¨‚·•K—v‚ª‚ ‚è‚Ü‚·B
	 * OCA‚©‚ç‚Ì—v‹‚É‚æ‚èuxƒy[ƒW‚©‚ç¥¥¥v‚ðˆóŽš‚µ‚Ü‚¹‚ñB
	 * 2003/03/10 H.Yoshikawa
	 */
	if (CHK_OCA_Specification()) {
		return;
	}
#endif

	/* “ú–{Œê‚ÌŽž‚¾‚¯‚ÍAƒy[ƒW”‚ðæ‚ÉˆóŽš‚·‚é‚Ì‚Å’ˆÓ‚ª•K—v‚Å‚· */
 #if defined(JPN)
	if (SYB_WordingNumber == 1) {	/* ‘I‘ð‚³‚ê‚Ä‚¢‚éƒ[ƒfƒBƒ“ƒO‚ª“ú–{Œê‚ÌŽž */
		page_prt_pos = 38;
	}
	else {
		CMN_StringCopy(&List.S.Print[38], PWRD_SendDocument);	/* "Send the document(s) from page" */
		page_prt_pos = (UBYTE)(CMN_StringLength(CalculateStringAddress(PWRD_SendDocument)) + 39);
	}
 #else
	CMN_StringCopy(&List.S.Print[38], PWRD_SendDocument);	/* "Send the document(s) from page" */
	page_prt_pos = (UBYTE)(CMN_StringLength(CalculateStringAddress(PWRD_SendDocument)) + 39);
 #endif

	/* •ª•ê‚ª‚OiƒXƒLƒƒƒi‘—Mj‚©A•ª•ê‚æ‚è•ªŽq‚ª¬‚³‚¢Žž‚ÍA•ªŽq‚Ì‚ÝˆóŽš */
	tx_page = SYB_ExecQueue[exec_cnt].Page;

	if ((total_page == 0) || (total_page < tx_page)) {
		is_total_page_prt = FALSE;
	}
	else {
		is_total_page_prt = TRUE;
	}

	/* Ä‘—ŽžƒƒbƒZ[ƒW */
	if (tx_page < 100) {
		CMN_UnsignedIntToASC(&List.S.Print[page_prt_pos], tx_page + 1, 2, ' ');
		page_prt_pos += 2;
		if (is_total_page_prt) {
			List.S.Print[page_prt_pos] = '/';
			page_prt_pos += 1;
			if (total_page < 100) {
				CMN_UnsignedIntToASC(&List.S.Print[page_prt_pos], total_page, 2, ' ');
				page_prt_pos += 2;
			}
			else {
				CMN_UnsignedIntToASC(&List.S.Print[page_prt_pos], total_page, 3, ' ');
				page_prt_pos += 3;
			}
		}
	}
	else {
		CMN_UnsignedIntToASC(&List.S.Print[page_prt_pos], tx_page + 1, 3, ' ');
		page_prt_pos += 3;
		if (is_total_page_prt) {
			List.S.Print[page_prt_pos] = '/';
			page_prt_pos += 1;
			CMN_UnsignedIntToASC(&List.S.Print[page_prt_pos], total_page, 3, ' ');
			page_prt_pos += 3;
		}
	}
 #if defined(JPN)
	if (SYB_WordingNumber == 1) {	/* ‘I‘ð‚³‚ê‚Ä‚¢‚éƒ[ƒfƒBƒ“ƒO‚ª“ú–{Œê‚ÌŽž */
		CMN_StringCopy(&List.S.Print[page_prt_pos + 1], PWRD_SendDocument);	/* "Íß°¼Þ‚©‚ç‘—‚è’¼‚µ‚Ä‚­‚¾‚³‚¢B " */
	}
 #endif
}
/*************************************************************************
	module		:[Žè“®‘—ŽžVÄ‘—ƒƒbƒZ[ƒW]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2000/3/16]
	author		:[¼–{³K]
*************************************************************************/
WORD	MunualTxDocumentMessage(UWORD journal_num)
{
	WORD	ret;			/**ŽÀsŒ‹‰Ê */

	/**E@@@@@@@@@@@@@@@@@@@@@@@@@@@E*/
	Print_TxConf_Line(6, List.S.Print, List.S.Attribute);
#if (PRO_JIS_CODE == ENABLE)
	CMN_StringCopy(&List.S.Print[1], (UBYTE *)"ª");
#else
	CMN_StringCopy(&List.S.Print[1], (UBYTE *)"Ð");
#endif
	/*Â³¼Ý¹¯¶ Ò¯¾°¼Þ*/			
	CommunicationResultName(SYB_JournalFile[journal_num].Result, LST_NAME_LONG,
	  LST_RESULT_COMMON, &List.S.Print[3], &List.S.Attribute[3]);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return (ret);
	}
	Print_TxConf_Line( 8, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return (ret);
	}
	return ( OK );

}
#endif
