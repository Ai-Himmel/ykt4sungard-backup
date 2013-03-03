/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_FNC.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ‹@”\Ø½Ä
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\apl_msg.h"
/** #include "\src\atlanta\define\keycode.h" */
#include "\src\atlanta\define\MNT_SW.H" /* By S.Kawasaki 1996/8/20 */
#include "\src\atlanta\define\std.h"

#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\lst_def.h"

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\ctry_pro.h"
#include "\src\atlanta\define\lst_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\lst_data.h"
#include "\src\atlanta\ext_v\lst_wrd.h"
#include "\src\atlanta\ext_v\rom_tbl.h"

#if (PRO_PANEL == ANK)
#include "\src\atlanta\opr\ank\define\opr_def.h"
#include "\src\atlanta\opr\ank\define\opr_pro.h"
#include "\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#endif
#if (PRO_PANEL == KANJI)
#include "\src\atlanta\\define\param.h"
#include "\src\atlanta\opr\kanji\define\opr_def.h"
#include "\src\atlanta\opr\kanji\define\opr_pro.h"
#include "\src\atlanta\opr\kanji\ext_v\opr_tbl.h"
#include "\src\atlanta\opr\kanji\ext_v\opr_data.h"
#include "\src\atlanta\opr\kanji\ext_v\wording.h"
#endif


CONST UBYTE LST_TEST = 0;	/* debug */

/*************************************************************************
	module		:[‹@”\ƒŠƒXƒgˆóü]
	function	:[‹@”\ƒŠƒXƒg‚ðˆóü‚·‚é]
	common		:[
		ROM_Revision	:
		FUNCTION_TABLE[]	:
				]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[96/01/17]
	author		:[•½”ö‰p“T]
*************************************************************************/
#define FUNCTION_HEAD	(9)
#define SETTING_HEAD	(42)

WORD					Print_Function_List(
						 		void )				/* ‚È‚µ */
{
#if (PRO_PANEL == ANK)
	register WORD	ret;			/* ŽÀsŒ‹‰Ê */
	UBYTE	i;						/* loop ‹@”\ */
	UBYTE	j;						/* loop ‹@ŠíÝ’è */
	UBYTE	dummy;					/* ŽŸÊß×Ò°ÀŒŸõ—p */
	UBYTE	line;					/* ˆóü‰Â”\s” */
	UBYTE	pointer;				/* ‹@”\Ý’èƒpƒ‰ƒ[ƒ^‚ÌƒIƒtƒZƒbƒg */
	UBYTE	page;					/* ƒy[ƒW */

	/* ƒ[ƒJƒ‹•Ï”‰Šú‰» */
	i = 0;
	pointer = 0;
	page = 1;

	do {
		/** ƒvƒŠƒ“ƒ^[ƒXƒ^[ƒg */
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		/** ˆóü‰Â”\s”¾¯Ä */
		if( page == 1 ){
			line = (UBYTE)(PaperSizeLen() - 4);
		}
		else{
			line = (UBYTE)(PaperSizeLen() - 3);
		}

		/**‚Ps‰üs */
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		/** ƒLƒmƒEƒŠƒXƒg	  ROMÚËÞ¼Þ®Ý */
		if( page == 1 ){		/* ‚Pƒy[ƒW–Ú‚Ì‚Ýo—Í */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			CMN_StringCopy( &List.S.Print[40], ROM_Revision );

  #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )	/* ’Ç‰Á 97/02/12 M.Kuwahara */
			AttributeSet( &List.S.Print[5], &List.S.Attribute[5], PWRD_ProgramList_K, LST_NOT );
  #else
			AttributeSet( &List.S.Print[5], &List.S.Attribute[5], PWRD_ProgramList, LST_XXX_TWI_XXX );
  #endif
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

		}
		Print_Function_List_Line( 0, List.S.Print, List.S.Attribute ); /* ƒcƒŠ[•\Ž¦—pŒrü */
		/**‚Ps‰üs */
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		for ( ; ; i++ ) {
			/** ‹@”\ƒpƒ‰ƒ[ƒ^ */ /* —ájA.One-Touch Dial */
			if ( (MainFunction[i].Available == OPR_YES) && (MainFunction[i].FirstCode != '\0') ) {/** —˜—p‰Â”\‚©H &&
																						‘æ‚P“ü—ÍƒL[ƒR[ƒh‚ªƒkƒ‹‚©H*/
				/** ƒtƒ@ƒ“ƒNƒVƒ‡ƒ“ƒe[ƒuƒ‹‚Ì’è‹`‚¾‚¯‚Å‚ÍA–³Œø‚Éo—ˆ‚È‚¢‹@”\‚ÌÄƒ`ƒFƒbƒN **/
				/** 	—áFƒvƒŠƒ“ƒ^ƒIƒvƒVƒ‡ƒ“ƒŠƒZƒbƒg‚Ì‹@”\‚ª‚ ‚é‚©ƒ`ƒFƒbƒN 97/08/27 By M.Kuwahara **/
				if (CheckSelectFunctionEnable((struct FUNCTION_TABLE_t *)&MainFunction[i]) == FALSE) {	/* Œ»Ý‚Ì‹@”\‚ª—LŒø‚È‹@”\‚ÌŽž **/
					continue;
				}

				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute ); /** ƒI[ƒ‹ƒNƒŠƒA */
				if ( MainFunction[i].NextLevel != NULL ){
					Print_Function_List_Line( 1, List.S.Print, List.S.Attribute ); /* ƒcƒŠ[•\Ž¦—pŒrüˆóŽš */
				} else {
					Print_Function_List_Line( 3, List.S.Print, List.S.Attribute ); /* ƒcƒŠ[•\Ž¦—pŒrüˆóŽš */
				}
				CMN_StringCopy( &List.S.Print[FUNCTION_HEAD+1], MainFunction[i].Wording );
				CMN_StringCopy( &List.S.Print[FUNCTION_HEAD], &MainFunction[i].FirstCode );
				List.S.Print[FUNCTION_HEAD+1] = '.';

				/* ‹@”\Ý’èƒpƒ‰ƒ[ƒ^ */ /* —áj1.Enter One-Touch */
				if ( MainFunction[i].NextLevel != NULL ){
					for ( j = pointer; ; j++ ) {
						if ( ((MainFunction[i].NextLevel+j)->Available == OPR_YES) &&
							 ((MainFunction[i].NextLevel+j)->FirstCode != '\0') ) {
							if ( page == 1 ) {	/* ‚Pƒy[ƒW–Ú‚ÌŽž */
								if ( j && (MainFunction[i+1].Available == OPR_YES) &&
								  		  (MainFunction[i+1].FirstCode != '\0') && 
										  (line != (UBYTE)(PaperSizeLen() - 4)) ) { /* ƒcƒŠ[•\Ž¦—pŒrüˆóŽš */
									for ( dummy = 1; ; dummy++ ){
										if (MainFunction[i+dummy].FirstCode == '\0') {	/* ‘S‚ÄˆóŽš‚µ‚½‚©H */
											break;
										}

									    if (CheckSelectFunctionEnable(		/* Œ»Ý‚Ì‹@”\‚ª—LŒø‚È‹@”\‚ÌŽž */
													(struct FUNCTION_TABLE_t *)&MainFunction[i+dummy]) == TRUE) {
											Print_Function_List_Line( 2, List.S.Print, List.S.Attribute );
											break;
										}
									}
								} else if ( j && (MainFunction[i+1].Available != OPR_YES) && 
												 (MainFunction[i+1].FirstCode == '\0') && 
												 (line != (UBYTE)(PaperSizeLen() - 4)) ){
									Print_Function_List_Line( 4, List.S.Print, List.S.Attribute );
								}
							}
							else{
								if ( j && (MainFunction[i+1].Available == OPR_YES) && 
										  (MainFunction[i+1].FirstCode != '\0') &&
										  (line != (UBYTE)(PaperSizeLen() - 3)) ) { /* ƒcƒŠ[•\Ž¦—pŒrüˆóŽš */
									for ( dummy = 1; ; dummy++ ){
										if (MainFunction[i+dummy].FirstCode == '\0') {	/* ‘S‚ÄˆóŽš‚µ‚½‚©H */
											break;
										}

									    if (CheckSelectFunctionEnable(		/* Œ»Ý‚Ì‹@”\‚ª—LŒø‚È‹@”\‚ÌŽž */
													(struct FUNCTION_TABLE_t *)&MainFunction[i+dummy]) == TRUE) {
											Print_Function_List_Line( 2, List.S.Print, List.S.Attribute );
											break;
										}
									}
								} else if ( j && (MainFunction[i+1].Available != OPR_YES) && 
												 (MainFunction[i+1].FirstCode == '\0') &&
												 (line != (UBYTE)(PaperSizeLen() - 3)) ){
									Print_Function_List_Line( 4, List.S.Print, List.S.Attribute );
								}
							}
							LST_RemoveAscString1stSpace( &List.S.Print[SETTING_HEAD+4],
							  (UBYTE *) (MainFunction[i].NextLevel+j)->Wording );
							CMN_UnsignedIntToASC( &List.S.Print[SETTING_HEAD],
							  (UWORD)(MainFunction[i].NextLevel+j)->FirstCode, 2, 0x30 );
							List.S.Print[SETTING_HEAD+2] = '.';
							if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
								return ( ret );
							}
							Prn_Att_Str_Clear( List.S.Print, List.S.Attribute ); /* j=0‚ÌŽž‚Ì‹@”\Ý’è‚Í‹@”\‚Æ“¯‚¶s‚È‚Ì‚Å‚±‚±‚Å¸Ø± */
							line--;
							pointer = 0;
							if ( line == 0 ) { /*  1ƒy[ƒW‚ÉˆóŽš‚Å‚«‚È‚­‚È‚Á‚½Žž */
								pointer = (UBYTE)(j + 1);
								/** line‚ª0‚É‚È‚Á‚Ä‹@”\Ý’èƒpƒ‰ƒ[ƒ^‚ª‚È‚­A‹@”\ƒpƒ‰ƒ[ƒ^‚à–³‚¢‚Æ‚«‚ÉA **/
								/**	‰üƒy[ƒW‚³‚ê‚Ä‚µ‚Ü‚¤ƒoƒO BY M.Kuwahara 97/08/27 **/
								if ((MainFunction[i].NextLevel+pointer)->FirstCode == '\0') { /* ‹@”\Ý’èÊß×Ò°À—L‚èH*/
									pointer = 0;	/* Added by S.Fukui Oct.3,1997 */
									i++;
									for ( ; ; i++ ){
										if (MainFunction[i].FirstCode == '\0') {	/* ‘S‚ÄˆóŽš‚µ‚½‚©H */
											break;
										}

									    if (CheckSelectFunctionEnable(		/* Œ»Ý‚Ì‹@”\‚ª—LŒø‚È‹@”\‚ÌŽž */
													(struct FUNCTION_TABLE_t *)&MainFunction[i]) == TRUE) {
											break;
										}
									}
								}
								break;
							}
						} else{ /** ‹@”\Ý’èƒpƒ‰ƒ[ƒ^‚ð‘S‚ÄˆóŽš‚µ‚½ê‡ */
							break;
						}
					}
				} else{ /** ‹@”\Ý’èƒpƒ‰ƒ[ƒ^‚ª–³‚¢ê‡ */
					if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
						return ( ret );
					}
					line--;
					if ( line == 0 ) { /** 1ƒy[ƒW‚ÉˆóŽš‚Å‚«‚È‚­‚È‚Á‚½Žž */
						i++;
						for ( ; ; i++ ){
							if (MainFunction[i].FirstCode == '\0') {	/* ‘S‚ÄˆóŽš‚µ‚½‚©H */
								break;
							}
						    if (CheckSelectFunctionEnable(		/* Œ»Ý‚Ì‹@”\‚ª—LŒø‚È‹@”\‚ÌŽž */
									(struct FUNCTION_TABLE_t *)&MainFunction[i]) == TRUE) {
								break;
							}
						}
						break;
					}
				}
				if ( line == 0 ) { /** 1ƒy[ƒW‚ÉˆóŽš‚Å‚«‚È‚­‚È‚Á‚½Žž‚É‚Qdƒ‹[ƒv‚©‚ç”²‚¯‚é */
					break;
				}
			} else{ /** ‹@”\ƒpƒ‰ƒ[ƒ^‚ª–³‚¢ê‡ */
				break;
			}
		}
		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}

		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}while ((line == 0)
			 &&(((MainFunction[i].Available == OPR_YES) && (MainFunction[i].FirstCode != '\0'))
			 ||(((MainFunction[i].NextLevel+pointer)->Available == OPR_YES) && ((MainFunction[i].NextLevel+pointer)->FirstCode != '\0'))));
	return ( OK );
#endif	/* PRO_PANEL == ANK */

#if (PRO_PANEL == KANJI)
	WORD	ret;

	/** ‘î•ñ‚ð“¾‚é */
#if (0)
** //	FuncCountryTableCopy(LST);	/* 94.11.09 By A.O */
** //	SettingsFuncCountryTableCopy(LST);	/* 94.11.09 By A.O */
#endif

	/** ‰ŠúÝ’è */
	ret = CharacterPrint( LST_OPEN );
	if (ret != OK) {
		return ( ret );
	}
	ret = CharacterPrint( LST_LINE_FEED );
	if (ret != OK) {
		return ( ret );
	}

	/** '‹@”\ƒŠƒXƒg'‚Æ‚q‚n‚lƒŠƒrƒWƒ‡ƒ“‚ðˆóü */
	Prn_Att_Str_Clear((UBYTE  *)List.S.Print, (UBYTE  *)List.S.Attribute );
#if (0)
** 	/* ‚o‚n‚o‚k‚`‚qQ‚g‚Í“ú–{Žd—l‚µ‚©‚È‚¢‚Ì‚ÅAˆÈ‰º‚Ìˆ—‚Í‚à‚Æ‚É–ß‚µ‚Ü‚·B By O.Kimoto 1997/08/09 */
** #if (0) /* Še‘‘Î‰ž‚Ìˆ×•ÏX by T.Soneoka 1997/07/25 */
** //	CMN_StringCopy((UBYTE  *)&List.S.Print[40], (UBYTE  *)ROM_Revision );
** #endif
** 	CMN_StringCopy((UBYTE  *)&List.S.Print[40], (UBYTE  *)&ROM_Revision[SYS_MachineParameter[COUNTRY_CODE]][0] );
#endif
	CMN_StringCopy((UBYTE  *)&List.S.Print[40], (UBYTE  *)ROM_Revision );
	CMN_StringCopy((UBYTE  *)&List.S.Print[5],  (UBYTE  *)PWRD_ProgramList_K);
	ret = CharacterPrint( LST_PRINT );
	if (ret != OK) {
		return ( ret );
	}

	/** –¾×ˆóŽš */
	ret = PrintFunctionListFunction();
	if (ret != OK) {
		return ( ret );
	}

	/** ŒãŽn–– */
	ret = CharacterPrint( LST_LINE_FEED );
	if (ret != OK) {
		return ( ret );
	}
	ret = CharacterPrint( LST_CLOSE );
	if (ret != OK) {
		return ( ret );
	}
#endif	/* PRO_PANEL == AKNJI */

}

#if (PRO_PANEL == KANJI)
/*************************************************************************
	module		:[‘î•ñ‚É‚æ‚é‹@”\‚Ì—L–³‚Ì”»’f]
	function	:[
		1.‹âˆÇ‚Ìê‡‚Ì‚Ý
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[LST]
	date		:[1996/08/13]
	author		:[´…­‹M]
*************************************************************************/
UBYTE IsFunctionEnable(
	UBYTE func_no)		/** ‹@”\Ý’è”Ô† */
{
	switch (func_no) {
	case ONE_TOUCH_DIAL:			/* (1)  A ƒƒ“ƒ^ƒbƒ`ƒ_ƒCƒ„ƒ‹	*/
		return (TRUE);

	case SPEED_DIAL_MODE:			/* (2)  B ’Zkƒ_ƒCƒ„ƒ‹			*/
		return (TRUE);

	case PROGRAM_ONE_TOUCH:			/* (3)  C ƒvƒƒOƒ‰ƒ€ƒƒ“ƒ^ƒbƒ`	*/
		return (TRUE);

	case POLLING:				 	/* (4)  D ƒ|[ƒŠƒ“ƒO			*/
		return (TRUE);

	case SECURE_MAIL_MODE:			/* (5)  E e“W					*/
		if (CTRY_SecureRx()) {
			return (TRUE);
		}
		break;

	case DELAYED_COMMAND_MODE:		/* (6)  F ’ÊM—\–ñ				*/
		return (TRUE);

	case SET_JOURNAL_PRINT:		 	/* (7)  G ’ÊMŠÇ—				*/
		return (TRUE);

	case GROUP_SETTING:			 	/* (8)  H ƒOƒ‹[ƒv				*/
		return (TRUE);

	case SETTING_MODE:				/* (9)  I Ý’uƒ‚[ƒh 			*/
		return(TRUE);

	case USER_SETTINGS:			 	/* (10) J ‹@ŠíÝ’è				*/
		return(TRUE);

	case MESSAGE_MODE:			 	/* (11) K ƒƒbƒZ[ƒW			*/
		if (CTRY_MessageTx()) {
			return (TRUE);
		}
		break;

	case CHARGE:					/* (12) L —¿‹àŠÇ—				*/
		if (CTRY_Cost()) {
			return (TRUE);
		}
		break;

	case DEPART_MODE:				/* (13) M •”–åŠÇ—				*/
		if (CTRY_Department()) {
			return (TRUE);
		}
		break;

	case TOTAL:					 	/* (14) N ˆêŠ‡‘—M				*/
		if (CTRY_BatchTx()) {
			return (TRUE);
		}
		break;

	case SECURITY_RECEIVE_MODE:		/* (15) O ƒZƒLƒ…ƒŠƒeƒBŽóM		*/
		return(TRUE);

	case FCODE_BOX_MODE:			/* (16) P ‚eƒR[ƒhƒ{ƒbƒNƒX		*/
		return(TRUE);

	case PC_PRINT:					/* (17) Q ƒvƒŠƒ“ƒ^ƒIƒvƒVƒ‡ƒ“ƒŠƒZƒbƒg*/
		return(CheckSelectFunctionEnable(PC_PRINT));

	case CIPHER_MODE:				/* (18) R ƒXƒNƒ‰ƒ“ƒuƒ‹			*/
	case CIPHER_DOC_MODE:			/** ƒXƒNƒ‰ƒ“ƒuƒ‹ *//* Add By O.Kimoto 1998/04/06 */
		return(CheckSelectFunctionEnable(CIPHER_MODE));

	case CLASS1_MODE:				/* (19) S ‚b‚Œ‚‚“‚“‚P			*/
		return(CheckSelectFunctionEnable(CLASS1_MODE));
	}
	return (FALSE);
}

/*************************************************************************
	module		:[‘î•ñ‚É‚æ‚é‹@ŠíÝ’è‚Ì—L–³‚Ì”»’f]
	function	:[
		1.‹âˆÇ‚Ìê‡‚Ì‚Ý
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[LST]
	date		:[1996/08/13]
	author		:[´…­‹M]
*************************************************************************/
UBYTE IsSettingEnable(
	UBYTE func_no)		/** ‹@ŠíÝ’è”Ô† */
{
	switch(func_no) {
	case SCANNER_PARAMETER_MODE:		/* 01 ½·¬ÝÊß×Ò°À   */
		return(TRUE);

	case PRINT_PARAMETER_MODE:			/* 02 ÌßØÝÄÊß×Ò°À  */
		return(TRUE);
#if (0)
** /* ‚o‚n‚o‚k‚`‚qQ‚g‚ÍƒRƒs[‹ÖŽ~‚ª‚ ‚è‚Ü‚·B By O.Kimoto 1998/03/02 */
** #if (PRO_PANEL == ANK) /* #if is added by H.Kubo 1997/12/15 */
** 	case COPY_PARAMETER_MODE:			/* 02 ÌßØÝÄÊß×Ò°À  */
** 		return(TRUE);
** #endif /* (PRO_PANEL == ANK) */
#else
	case COPY_PROTECT:					/* 02 ºËß°‹ÖŽ~Ý’è  */
		return(TRUE);
#endif
	case DIALING_PAUSE_MODE:			/* 03 Îß°½ÞŽžŠÔ    */
		if (CTRY_Pause()) {
			return (TRUE);
		}
		break;

	case NUMBER_OF_RINGS_MODE:			/* 04 ŒÄoÍÞÙ‰ñ”  */
		if (CTRY_BellCount()) {
			return (TRUE);
		}
		break;

	case REDIAL_MODE:					/* 05 ØÀÞ²ÔÙ       */
		if (CTRY_RedialNumber() && CTRY_RedialInterval()) {
			return(TRUE);
		}
		break;

	case ECM_SET_MODE:						/* 06 ECMÓ°ÄÞ      */
		return (TRUE);

	case PASSCODE:						/* 07 Êß½º°ÄÞ      */
		if (CTRY_SecurityTx()) {
			return (TRUE);
		}
		break;

	case CLOSED_NETWORK_MODE:			/* 08 •Âˆæ’ÊM     */
		if (CTRY_ClosedNetwork()) {
			return (TRUE);
		}
		break;

	case SECURITY_TRANSMISSION_MODE:	/* 09 Êß½Ü°ÄÞ‘—M  */
		if (CTRY_SecurityTx()) {
			return (TRUE);
		}
		break;

	case BLOCK_JUNK_FAX_MODE:			/* 10 ÀÞ²Ú¸ÄÒ°Ù    */
		if (CTRY_BlockJunkFax()) {
			return (TRUE);
		}
		break;

	case REMOTE_DIAGNOSTIC:				/* 11 »°ËÞ½Ó°ÄÞ (ØÓ°Äf’f) */
		if (CTRY_RemoteDiag()) {
			return (TRUE);
		}
		break;
	case MEMORY_TRANSMISSION:			/* 12 ÒÓØ‘—M      */
		return (TRUE);

	case STAMP_MODE:					/* 13 Ï½ÀÝÌß      */
		if (CTRY_Stamp()) {
			return (TRUE);
		}
		break;
	case DIAL_IN_MODE:					/* 14 ÀÞ²ÔÙ²Ý      */
		if (CTRY_Dialin()) {
			return (TRUE);
		}
		break;
	case HOLD_MELODY_MODE:				/* 15 •Û—¯ÒÛÃÞ¨    */
		if (CTRY_HoldMelody()) {
			return (TRUE);
		}
		break;
	case RELAYED_RELAY_TX_MODE:			/* 16 ’†XŒp       */
		if (CTRY_RelayedTx()) {
			return (TRUE);
		}
		break;

#if (0)
** /* ‚o‚n‚o‚k‚`‚qQ‚g‚É‚Í‚ ‚è‚Ü‚¹‚ñB By O.Kimoto 1997/11/13 */
** 	case CONNECT_PC_FAX_MODE:			/* 17 PCFAXÚ‘±    */
** 		return(TRUE);
** 	case CHANGE_CARTRIDGE:				/* 18 ¶°ÄØ¯¼ÞŒðŠ·  */
** 		return(TRUE);
** 	case PC_PRINT:						/* 19 ‚o‚bƒvƒŠƒ“ƒg */
** #if (PRO_PC_PRINT == ENABLE)
** 		return (DPR_CheckOptionPrintBoardExist());	/** ICHOU•ÏX -- 1997/05/13 M.Shimizu */
** #else
** 		return (FALSE);
** #endif
#endif
	case PIN_CODE_MODE:					/* 18 PINº°ÄÞ      */	/* Add By O.Kimoto 1997/11/13 */
			return (TRUE);
	case PROTECT_PASSCODE_MODE:			/* 19 ÌßÛÃ¸Äº°ÄÞ   */	/* Add By O.Kimoto 1997/11/13 */
			return (TRUE);
	case OPERATION_PROTECT_MODE:		/* 20 µÍßÚ°¼®Ý ÌßÛÃ¸Ä *//* Add By O.Kimoto 1997/11/13 */
			return (TRUE);
	case PRINT_SETTINGS:				/* 21 ‹@ŠíÝ’èØ½Ä ÌßØÝÄ *//* Add By O.Kimoto 1997/12/27 */
			return (TRUE);
	}

	return(FALSE);
}


/*************************************************************************
	module		:[‹@”\Ý’è“à—eˆóü]
	function	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[V53]
	language	:[MS-C]
	keyword		:[LST]
	date		:[1996/07/09]
	author		:[´…­‹M]
*************************************************************************/
WORD PrintFunctionListFunction( void )
{
	WORD				ret;
	UBYTE		i, tail;

	/* USA•ÏX by T.Soneoka 1997/04/24 */
	UBYTE	setting_no;
	setting_no = 0;

	for(i = 0; ; i++) {
		/** –³ŒøAI—¹ƒ`ƒFƒbƒN */
		if (FunctionTable[i][1] == '\0') {
			break;
		}
#if (0) /* USA•ÏX by T.Soneoka 1997/04/24 */
** //		if (FunctionTable[i][0] == 0 || IsFunctionEnable(FunctionTable[i][1]) == FALSE) {
** //			continue;
** //		}
#endif
		/* ‹@ŠíÝ’è€–Úƒ`ƒFƒbƒN */
		if (FunctionTable[i][0] == 0) {
			continue;
		}
		/* Ž•”²‚¯ˆ— */
		if (IsFunctionEnable(FunctionTable[i][1]) == FALSE) {
			++setting_no;
			continue;
		}

		/** ‹@”\ˆóü */
		Prn_Att_Str_Clear((UBYTE  *)List.S.Print, (UBYTE  *)List.S.Attribute);
#if (0) /* USA•ÏX by T.Soneoka 1997/04/24 */
** //		List.S.Print[ 9] = (UBYTE)('A' + i);
#endif
		List.S.Print[ 9] = (UBYTE)('A' + setting_no);
		++setting_no;

		List.S.Print[10] = '.';
		CMN_StringCopy((UBYTE  *)&List.S.Print[12],
					   (UBYTE  *)&D4W_Function[FunctionTable[i][1]][0]);

		/** ‹@”\ˆÈ‰º‚Ì€–Ú‚ðˆóü */
		switch(FunctionTable[i][1]) {
		case GROUP_SETTING:		/** ƒOƒ‹[ƒvƒŠƒXƒg‚ÆÝ’uƒ‚[ƒh‚Í‘f‚Åo—Í */
		case SETTING_MODE:
		case PC_PRINT:
			ret = CharacterPrint( LST_PRINT );
			if (ret != OK) {
				return ( ret );
			}
			break;

#if (0)
** 		/* ‰º‹Lˆ—‚Í‚`‚S‚É‚µ‚©‘Î‰ž‚Å‚«‚Ä‚¨‚ç‚¸A•ûŽè—Ž‚¿‚È‚Ì‚ÅA
** 		** Šî–{“I‚É‚Í‚¸‚µ‚Ü‚·B
** 		** By O.Kimoto 1998/03/31
** 		*/
** 		case FCODE_BOX_MODE:	/* ‚eƒR[ƒhƒ{ƒbƒNƒX‚ÌŽè‘O‚Å‚Q–‡‚É•ªŠ„‚µ‚Ü‚·B By O.Kimoto 1998/02/06 */
** 			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
** 				return ( ret );
** 			}
** 			if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
** 				return ( ret );
** 			}
** 			if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
** 				return ( ret );
** 			}
** 			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
** 				return ( ret );
** 			}
#endif

		default:
			/** Œrü‚ÌƒZƒbƒg */
			for(tail = 24; ; tail--) {	/** ‹@”\Ý’è€–Ú‚Ì––”ö‚ð’T‚· */
				if (List.S.Print[tail] != ' ') {
					break;
				}
			}
			CMN_MemorySet((UBYTE  *)&List.S.Print[tail + 2], 39 - tail, LST_KLINE_);

			if (FunctionTable[i][1] == USER_SETTINGS) {			/** ‹@ŠíÝ’è */
				ret = PrintFunctionListSettingFunc(USER_SETTINGS);
			}
			else {					/** ‚»‚Ì‘¼‚Ì€–Ú */
				ret = PrintFunctionListFuncMenu(FunctionTable[i][1]);
			}
			if (ret != OK) {
				return ( ret );
			}
			break;
		}
	}
	return(OK);
}



/*************************************************************************
	module		:[‹@ŠíÝ’è“à—eˆóü]
	function	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[V53]
	language	:[MS-C]
	keyword		:[LST]
	date		:[1996/07/09]
	author		:[´…­‹M]
*************************************************************************/
WORD PrintFunctionListSettingFunc(
	UBYTE func_no)		/** ‹@”\”Ô† */
{
	WORD			ret;
	UBYTE	i;

	/* USA•ÏX by T.Soneoka 1997/04/24 */
	UBYTE	setting_no;
	setting_no = 0;
	
	switch(func_no) {
	case USER_SETTINGS:		/** ‹@ŠíÝ’è */
		for(i = 0; ; i++) {
			/** –³ŒøAI—¹ƒ`ƒFƒbƒN */
			if (SettingsFunctionTable[i][1] == '\0') {
				break;
			}
#if (0) /* USA•ÏX by T.Soneoka 1997/04/24 */
** //			if (SettingsFunctionTable[i][0] == 0 || IsSettingEnable(SettingsFunctionTable[i][1]) == FALSE) {
** //				continue;
** //			}
** //			/** ‹@ŠíÝ’èƒZƒbƒg */
** //			CMN_UnsignedIntToASC((UBYTE  *)&List.S.Print[42], (UWORD)(i + 1), 2, '0');
#endif
			/* ‹@ŠíÝ’è€–Úƒ`ƒFƒbƒN */
			if (SettingsFunctionTable[i][0] == 0) {
				continue;
			}
			/* Ž•”²‚¯ˆ— */
			if (IsSettingEnable(SettingsFunctionTable[i][1]) == FALSE) {
				++setting_no;
				continue;
			}
			/** ‹@ŠíÝ’èƒZƒbƒg */
			CMN_UnsignedIntToASC((UBYTE  *)&List.S.Print[42], (UWORD)(setting_no + 1), 2, '0');
			++setting_no;
			
			List.S.Print[44] = '.';
			CMN_StringCopy((UBYTE  *)&List.S.Print[45], &D4W_Function[SettingsFunctionTable[i][1]][0]);

			/** ˆóüŽÀs */
			ret = CharacterPrint( LST_PRINT );
			if (ret != OK) {
				return ( ret );
			}
			Prn_Att_Str_Clear((UBYTE  *)List.S.Print, (UBYTE  *)List.S.Attribute);
		}
		break;
	}
	return(OK);
}

/*************************************************************************
	module		:[‹@”\Ý’è‚Ì‚P’i‰º‚Ì“à—eˆóü]
	function	:[]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[V53]
	language	:[MS-C]
	keyword		:[LST]
	date		:[1996/07/09]
	author		:[´…­‹M]
*************************************************************************/
WORD PrintFunctionListFuncMenu(
	UBYTE func_no)	/* ‹@”\”Ô† */
{
	WORD				ret;
	UBYTE		menu_no, i, head;
	UBYTE 	*ptr;

	/** ˆóü‚·‚×‚«ƒƒjƒ…[‚ÌŒŸõ */
	switch (func_no) {
	case ONE_TOUCH_DIAL:		/** ƒƒ“ƒ^ƒbƒ`ƒ_ƒCƒ„ƒ‹ */
	case SPEED_DIAL_MODE:		/** ’Zkƒ_ƒCƒ„ƒ‹ */
	case PROGRAM_ONE_TOUCH:		/** ƒvƒƒOƒ‰ƒ€ƒƒ“ƒ^ƒbƒ` */
	case CHARGE:				/** —¿‹àŠÇ— */
		menu_no = ENTER_LIST_DELETE;
		break;
	case POLLING:				/** ƒ|[ƒŠƒ“ƒO */
		menu_no = DOC_STORE_PRT_CLEAR;
		break;
	case SECURE_MAIL_MODE:		/** e“W */
		menu_no = SECURE_COMMAND;
		break;
	case DELAYED_COMMAND_MODE:	/** ’ÊM—\–ñ */
		menu_no = DELAYED_COMMAND;
		break;
	case SET_JOURNAL_PRINT:		/** ’ÊMŠÇ— */
		menu_no = JOURNAL_COMMAND;
		break;
	case MESSAGE_MODE:			/** ƒƒbƒZ[ƒW */
		menu_no = MESSAGE_COMMAND;
		break;
	case DEPART_MODE:			/** •”–åŠÇ— */
		/* ‚t‚r‚`Žd—l’Ç‰Á by T.Soneoka 1997/04/08 */
		if (SYB_MachineParameter[COUNTRY_CODE] == COUNTRY_CODE_JPN) {
			menu_no = DEPT_CODE_MODE;
		}
		else {
			menu_no = DEPT_CODE_MODE_USA;
		}
		break;
	case TOTAL:					/** ˆêŠ‡‘—M */
		menu_no = BATCH_TX_COMMAND;
		break;

	case SECURITY_RECEIVE_MODE:		/* (15) O ƒZƒLƒ…ƒŠƒeƒBŽóM		*/
		menu_no = SECURITY_MODE_MENU;
		break;

	case FCODE_BOX_MODE:			/* (16) P ‚eƒR[ƒhƒ{ƒbƒNƒX		*/
		menu_no = FCODE_TOP_MENU;
		break;


	case CIPHER_MODE:				/* (18) R ƒXƒNƒ‰ƒ“ƒuƒ‹			*/
		menu_no = CIPHER_TOP_MENU;
		break;

	case CLASS1_MODE:				/* (19) S ‚b‚Œ‚‚“‚“‚P			*/
		menu_no = CLASS1_MODE_MENU;
		break;

	case PC_PRINT:					/* (17) Q ƒvƒŠƒ“ƒ^ƒIƒvƒVƒ‡ƒ“ƒŠƒZƒbƒg*/
	default:
		break;
	}

	/** €–Ú‚ðƒZƒbƒg */
	for (i = 0;; i++) {
		/** €–Ú‚Ì—]•ª‚È‹ó”’‚ðŽæ‚é */
		if (menu_no < RS232C_SPEED_MENU) {
			if (SoftKeyTable[menu_no][i] == 0) {	/** ‹@”\€–ÚI—¹ */
				break;
			}
			ptr = (UBYTE  *)&D4W_SoftKey[SoftKeyTable[menu_no][i] - 0x80][0];
		}
		else {
			menu_no -= RS232C_SPEED_MENU;
			if (SoftKeyTable2[menu_no][i] == 0) {
				break;
			}
			ptr = (UBYTE  *)&D4W_SoftKey2[SoftKeyTable[menu_no][i] - 0x80][0];
		}

		/* –{—ˆ‚Í‚±‚ñ‚ÈŠ‚Åƒ[ƒfƒBƒ“ƒOƒAƒhƒŒƒX‚ð•ÏŠ·‚·‚é•K—v‚Í‚È‚¢‚Ì‚Å‚·‚ª
		** ‚h‚b‚g‚n‚t‚ÌƒvƒƒOƒ‰ƒ€‚ð—¬—p‚·‚é‚½‚ßAŽb’è“I‚Éˆ—‚µ‚Ü‚·
		** ŽÀÛ‚É•\Ž¦‚·‚é‚Æ‚«‚Í‚k‚b‚cƒhƒ‰ƒCƒo[‚Ì•û‚Ås‚¢‚Ü‚·B
		** By O.Kimoto 1997/10/24
		*/
		ptr = CalculateStringAddress(ptr);

		for (head = 0; ; head++) {
			if ( *(ptr + head) != ' ' ) {
				break;
			}
		}
		CMN_StringCopy((UBYTE  *)&List.S.Print[42], (UBYTE  *)ptr + head);

		/** ˆóüŽÀs */
		ret = CharacterPrint( LST_PRINT );
		if (ret != OK) {
			return ( ret );
		}
		Prn_Att_Str_Clear((UBYTE  *)List.S.Print, (UBYTE  *)List.S.Attribute);
	}

	return (OK);
}



#endif




#undef FUNCTION_HEAD
#undef SETTING_HEAD
/*************************************************************************
	module		:[‹@”\ƒŠƒXƒgŒrüì¬]
	function	:[‹@”\ƒŠƒXƒg‚ÌŒrü‚ðì¬‚·‚é]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
		'	0 = †¤
		'	1 = †¶†¢†¢†¢†¢†¢†¢†¢†¢
		'	2 = †¤			  †¶†¢
		'	3 = †¶†¢†¢
		'	4 =				  †¶†¢
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[96/07/22]
	author		:[•½”ö ‰p“T]
*************************************************************************/
void				Print_Function_List_Line(
						 UBYTE Category,				/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,		/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )	/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*†¤*/
			AscString[5] = LST_KLINEI;
			break;
		case 1:
			/*†¶†¢†¢†¢†¢†¢†¢†¢†¢*/
			AscString[5] = LST_KLINE1;
			CMN_MemorySet( &AscString[6], 35, LST_KLINE_ );
			break;
		case 2:
			/*†¤			†¶†¢*/
			AscString[5] = LST_KLINEI;
			if (SYB_MaintenanceSwitch[MNT_SW_C0]&LST_OLD_PROGRAM_FORMAT) { /* By S.Kawasaki 1996/08/20 */
				AscString[34] = LST_KLINE1;
				CMN_MemorySet( &AscString[35], 6, LST_KLINE_ );
			}
			break;
		case 3:
			/*†¶†¢†¢*/
			AscString[5] = LST_KLINE1;
			CMN_MemorySet( &AscString[6], 2, LST_KLINE_ );
			break;
		case 4:
			if (SYB_MaintenanceSwitch[MNT_SW_C0]&LST_OLD_PROGRAM_FORMAT) { /* By S.Kawasaki 1996/08/20 */
				/*			  †¶†¢*/
				AscString[34] = LST_KLINE1;
				CMN_MemorySet( &AscString[35], 6, LST_KLINE_ );
			}
			break;
	}
}

/*************************************************************************
	module		:[ƒAƒXƒL[•¶Žš—ñ‚ÌÅ‰‚ÌƒXƒy[ƒX‚ðŽæ‚èœ‚­]
	function	:[]
	common		:[]
	condition	:[]
	commment	:[ƒAƒXƒL[•¶Žš—ñ‚Ì‚P•¶Žš–Ú‚ÌƒLƒƒƒ‰ƒNƒ^‚ªƒXƒy[ƒX‚È‚çA
				@‚Q•¶Žš–ÚˆÈ~‚ÉƒXƒy[ƒXˆÈŠO‚ÌƒLƒƒƒ‰ƒNƒ^‚ªŒ»‚ê‚é‚Ü‚ÅA
				@ƒXƒy[ƒX‚ðŽæ‚èœ‚­
				  ƒIƒyƒŒ[ƒVƒ‡ƒ“‚Ìƒ[ƒfƒBƒ“ƒO‚ð‚µ‚æ‚¤‚·‚é‚Æ‚«‚ÉƒXƒy[ƒX‚ð
				  Žæ‚èœ‚«‚½‚¢Žž‚ÉƒR[ƒ‹‚µ‚Ä‚¢‚é
				96/12/26	ˆé•Ó	‘å••ÏX
]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[96/12/26]
	author		:[ˆé•Ó‹B]
*************************************************************************/
void	  LST_RemoveAscString1stSpace(
					UBYTE  *NoSpaceAscString,	/* ƒXƒy[ƒX‚ðŽæ‚èœ‚¢‚½Œã‚ÌƒAƒXƒL[•¶Žš—ñ */
					UBYTE  *AscString			/* ƒLƒƒƒ‰ƒNƒ^•¶Žš—ñ */
					)
{
#if (0)			/*1996/12/28 T.Isobe Ì‚ÌƒŠƒXƒg wording‚É‚æ‚Á‚Ä½Íß°½‚ªŽæ‚ê‚È‚¢ˆ×*/
	UWORD	i;	/** ”z—ñ‚ÌƒIƒtƒZƒbƒg */

	if ( *AscString == ' ' ) {
		for ( i=1; ; i++ ) {
			if ( *(AscString + i) != ' ' ) {
				CMN_StringCopy( NoSpaceAscString, (AscString + i) );
				break;
			}
		}
	} else {
		CMN_StringCopy( NoSpaceAscString, AscString );
	}
#endif

	UWORD	i;	/** ”z—ñ‚ÌƒIƒtƒZƒbƒg */
	UBYTE	*j;
	/*1996/12/26 T.Isobe	wrd0‚Æw???‚Ì¾¯ÄˆÊ’uˆá‚¢‚Ìˆ× */
	j = CalculateStringAddress( AscString );
	for ( i = 0; ; i++ ) {
		if ( *( j + i ) != ' ' ) {
			break;
		}
	}
	CMN_StringCopy( NoSpaceAscString, (AscString + i) );
}

