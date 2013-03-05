/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_PRG.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\\define\keycode.h"
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
#endif

#if (PRO_PANEL == KANJI)
#include	"\src\atlanta\opr\kanji\define\opr_def.h"
#include	"\src\atlanta\opr\kanji\define\opr_pro.h"
#endif

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/06 By M.Kuwahara */
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\syspgone.h"
#include	"\src\atlanta\define\syslocal.h"
#endif

#if (PRO_OKI == ENABLE)	/* by K.Watanabe 1999/02/09 */
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#endif

/*************************************************************************
	module		:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒgˆóü]
	functiom	:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg‚ðˆóü‚·‚é]
	common		:[
		List				:
		SYB_ProgramOnetouch	:
			SYB_OnetouchDial	:
			SYB_BatchTxFile		:
	]
	condition	:[]
	commment	:[97/09/04 By M.Kuwahara 
					‰üƒy[ƒW‚ðƒvƒƒOƒ‰ƒ€–ˆ‚Å‚¨‚±‚È‚í‚¸Aƒ‰ƒCƒ“”‚Ì‚Ý‚ÅŽÀs
						—áFƒvƒƒOƒ‰ƒ€[‚V‚R]‚Ì“r’†‚Å‰üƒy[ƒW‚É‚È‚éŽžA
						    [‚V‚R]‚ðŽŸƒy[ƒW‚É‚·‚é‚Ì‚Å‚Í‚È‚­A“à—e‚Ì‘±‚«‚©‚çŽŸƒy[ƒW‚É‚È‚éB
]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 1]
	author		:[–L“c_Žq]
*************************************************************************/
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/17 By M.Kuwahara */
WORD				Print_Program_List(
						 void )			/*‚È‚µ*/
{
	UBYTE	i;						/*loop*/
	UBYTE	page;					/*Íß°¼Þ*/
	UBYTE	prog_cnt;				/*ÌßÛ¸Þ×ÑÃÞ°À”Ô†*/
	UBYTE	line_cnt;				/*Žc‚èˆóü‰Â”\s”*/
	UBYTE	opt_line;				/*µÌß¼®ÝÃÞ°Às”*/
	UBYTE	is_change_page;			/*Íß°¼Þ¸Û°½Þ”»•ÊÌ×¸Þ*/
	register WORD	ret;			/*ŽÀsŒ‹‰Ê*/
#if (PRO_EXT_P_ONETOUCH == ENABLE) && (PRO_PANEL == KANJI) /* by H.Kubo 1999/01/06 */
	UBYTE 	separator_of_entry;		/* ƒGƒ“ƒgƒŠŠÔ‚ÌŒrü‚ª“ü‚é‚©‚Ç‚¤‚©‚Ìƒtƒ‰ƒO added by H.Kubo 1999/01/06 */

	separator_of_entry = TRUE; /* added by H.Kubo 1999/01/06 */
#endif

	page = 1;
	prog_cnt = 0;

	i	= 0;
	opt_line	= 0;
	DialCheckPointer	= SYS_EMPTY_DIAL;
	DialCheckBitPointer	= 0;

	/* Œ©o‚µˆóŽš */
	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}
	is_change_page = TRUE;
	line_cnt = (UBYTE)(PaperSizeLen() - 12);/*ˆóü‰Â”\s”¾¯Ä*/
	if ( (ret = Print_Program_List_Head_Ext( 0, page, SYS_PROGRAM_EMPTY ) ) != OK ) {/*Í¯ÀÞˆóü*/
		return ( ret );
	}

	if (ProgDataEntryCheck( SYS_PROGRAM_COMMAND, 0) != SYS_PROGRAM_MAX) {	/* ’ÊM—\–ñ‚Ì“o˜^—L‚è‚ÌŽž */
		while ( prog_cnt != SYS_PROGRAM_MAX ) { /* ˆÈ‰ºSYS_ONETOUCH_MAX‚ðSYS_PROGRAM_MAX‚É•ÏX(ANZU) 95/12/15 •½”ö‰p“T */
			if (is_change_page == FALSE) {	/* ‰üƒy[ƒW‚ÌŽž */
				if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
					return ( ret );
				}
				is_change_page = TRUE;
				line_cnt = (UBYTE)(PaperSizeLen() - 4);/*ˆóü‰Â”\s”¾¯Ä*/
				if ( (ret = Print_Program_List_Head_Ext( 0, page, SYS_PROGRAM_COMMAND ) ) != OK ) {/*Œ©o‚µˆóü*/
					return ( ret );
				}
			}
			if (prog_cnt == 0) {	/* æ“ªŽž‚Ì‚Ý */
				if ( (ret = Print_Program_List_Head_Ext( 1, page, SYS_PROGRAM_COMMAND ) ) != OK ) {/*Í¯ÀÞˆóü*/
					return ( ret );
				}
			}

			while (1){
				if (( DialCheckPointer == SYS_EMPTY_DIAL ) &&	/* 97/09/03 By M.Kuwahara */
				    ( opt_line == 0 )) {
					ProgDataNextSearch( &prog_cnt );					/*ŽŸÃÞ°À»°Á*/
					DialCheckPointer    = SYS_DIRECT_DIAL;	/** Ží•Êƒ|ƒCƒ“ƒ^‚ð‰Šú‰»   */
					DialCheckBitPointer = 0;				/** ƒrƒbƒgƒ|ƒCƒ“ƒ^‚ð‰Šú‰» */
					/*”õl€–ÚÃÞ°À×²Ý”*/
#if ( PRO_MAKER == FX )
					opt_line = ProgOptionDataToString(
					  SYB_ProgramOnetouch[prog_cnt].EntryData.Command.Option.Item,
					  (WORD)SYB_ProgramOnetouch[prog_cnt].EntryData.Command.Option.OptionNumber.FX_Secure.Number,
					  SYB_ProgramOnetouch[prog_cnt].EntryData.Command.Option.OptionNumber.FX_Relay.Number,
					  SYB_ProgramOnetouch[prog_cnt].EntryData.Command.Option.OptionNumber.DatabaseNumber, List.S.Work, NULL );
#else
					opt_line = ProgOptionDataToString(
					  SYB_ProgramOnetouch[prog_cnt].EntryData.Command.Option.Item,
					  SYB_ProgramOnetouch[prog_cnt].EntryData.Command.Option.OptionNumber.SecureNumber,
					  SYB_ProgramOnetouch[prog_cnt].EntryData.Command.Option.OptionNumber.RelayGroupNumber,
					  SYB_ProgramOnetouch[prog_cnt].EntryData.Command.Option.OptionNumber.DatabaseNumber, List.S.Work, NULL );
#endif
				}
				if ( prog_cnt == SYS_PROGRAM_MAX ) {
					break;
				}

				if (SYB_ProgramOnetouch[prog_cnt].EntryData.Command.Option.Item == SYS_BATCH_MEMORY_TX) {
#if (PRO_EXT_P_ONETOUCH == ENABLE) && (PRO_PANEL == KANJI) /* ƒ|[ƒŠƒ“ƒOŽóM‚ÌˆóŽš‚Å‚ÍAƒL[ó‘Ô‚ð•\Ž¦‚µ‚È‚¢‚½‚ß‚ÌC³B Changed by H.Kubo 1999/01/06 */
					if (separator_of_entry) {
						if ( (ret = (UBYTE)PrintProgramBatchLineSeparator(page, &i, &line_cnt) ) != OK ) { /*1–¾×ˆóü*/
							return ( ret );
						}
					}
#endif
					if ( (ret = PrintProgramBatchLine(page, &i, prog_cnt, &line_cnt ) ) != OK ) {/*1–¾×ˆóü*/
						return ( ret );
					}
					DialCheckPointer    = SYS_EMPTY_DIAL;	/** Ží•Êƒ|ƒCƒ“ƒ^‚ð‰Šú‰»   */
					DialCheckBitPointer = 0;				/** ƒrƒbƒgƒ|ƒCƒ“ƒ^‚ð‰Šú‰» */
				}
				else {
					if (line_cnt <= 1) {	/* ‚Ps‚à–¾×‚ªo—Í‚Å‚«‚È‚¢Žž */
						break;
					}
#if (PRO_EXT_P_ONETOUCH == ENABLE) && (PRO_PANEL == KANJI) /* ƒ|[ƒŠƒ“ƒOŽóM‚ÌˆóŽš‚Å‚ÍAƒL[ó‘Ô‚ð•\Ž¦‚µ‚È‚¢‚½‚ß‚ÌC³B Changed by H.Kubo 1999/01/06 */
					if (separator_of_entry) {
						if ( (ret = (UBYTE)PrintProgramBatchLineSeparator(page, &i, &line_cnt) ) != OK ) { /*1–¾×ˆóü*/
							return ( ret );
						}
					}
#endif
					if ( (ret = (UBYTE)Print_Program_List_Specifi( page, &i, prog_cnt, &line_cnt) ) != OK ) { /*1–¾×ˆóü*/
						return ( ret );
					}
				}

				if ( opt_line <= i ){		/* ”õl—“‚ð‚·‚×‚Äo—Í‚µ‚½Žž */
					opt_line	= 0;
				}
				else{
					opt_line	-= i;
				}

				if ( line_cnt <= 1 ) {
					if (( DialCheckPointer != SYS_EMPTY_DIAL ) ||
					    ( opt_line != 0 )) {
						break;
					}
				}
				
				if (line_cnt <= 3) {	/* Žc‚ès‚ÅƒVƒ“ƒOƒ‹ƒL[‚Ìó‘Ôo—Í‚ªo—ˆ‚È‚¢Žž */
					if ( (ret = Print_Program_List_Head_Ext( 2, page, SYS_PROGRAM_COMMAND ) ) != OK ) {/*Ì¯Àˆóü*/
						return ( ret );
					}
					if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
						return ( ret );
					}
					page++;
					if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
						return ( ret );
					}
					is_change_page = TRUE;
					line_cnt = (UBYTE)(PaperSizeLen() - 4);/*ˆóü‰Â”\s”¾¯Ä*/
					if ( (ret = Print_Program_List_Head_Ext( 0, page, SYS_PROGRAM_COMMAND ) ) != OK ) {/*Œ©o‚µˆóü*/
						return ( ret );
					}
				}
#if (PRO_EXT_P_ONETOUCH == ENABLE) && (PRO_PANEL == KANJI) /* ƒ|[ƒŠƒ“ƒOŽóM‚ÌˆóŽš‚Å‚ÍAƒL[ó‘Ô‚ð•\Ž¦‚µ‚È‚¢‚½‚ß‚ÌC³B Changed by H.Kubo 1999/01/06 */
				{
					UBYTE next_prog_cnt;
					next_prog_cnt = prog_cnt + 1;
					ProgDataNextSearch( &next_prog_cnt );

					switch (SYB_ProgramOnetouch[prog_cnt].EntryData.Command.Option.Item) {
					case SYS_POLLING_RX:
					case SYS_DB_POLLING_RX:
					case SYS_SEQUENTIAL_POLLING:
					case SYS_CONTINUOUS_POLLING_RX:
					case SYS_SELECT_POLLING_RX:
						separator_of_entry = FALSE;
						break;
					default:
						separator_of_entry = TRUE;
						break;
					}
					if ((ret = EntrySingleKeySeparatorSpecifi(prog_cnt, next_prog_cnt, line_cnt, !separator_of_entry, SYS_PROGRAM_COMMAND)) != OK) {	/* ¼Ý¸ÞÙ·°‚Ìó‘Ôo—Í */
						return (ret);
					}
					line_cnt -= 1;
 #if 0 /* Changed by H.Kubo 1999/01/06 */
 @@					if ((ret = EntrySingleKeySpecifi( prog_cnt, line_cnt, SYS_PROGRAM_COMMAND)) != OK) {	/* ¼Ý¸ÞÙ·°‚Ìó‘Ôo—Í */
 @@						return (ret);
 @@					}
 @@					line_cnt -= 2;
 #else
					if ((ret = EntrySingleKeySpecifi( prog_cnt, &line_cnt, SYS_PROGRAM_COMMAND)) != OK) {	/* ¼Ý¸ÞÙ·°‚Ìó‘Ôo—Í */
						return (ret);
					}
 #endif
				}
#else
 #if 0 /* Changed by H.Kubo 1999/01/06 */
 @@				if (EntrySingleKeySpecifi( prog_cnt, line_cnt, SYS_PROGRAM_COMMAND) != OK) {	/* ¼Ý¸ÞÙ·°‚Ìó‘Ôo—Í */
 @@					return (ret);
 @@				}
 @@				line_cnt -= 3;
 #else
				if (EntrySingleKeySpecifi( prog_cnt, &line_cnt, SYS_PROGRAM_COMMAND) != OK) {	/* ¼Ý¸ÞÙ·°‚Ìó‘Ôo—Í */
					return (ret);
				}
 #endif
#endif
				prog_cnt++;
				i	= 0;
			}
#if (PRO_EXT_P_ONETOUCH == ENABLE) && (PRO_PANEL == KANJI) /* ƒ|[ƒŠƒ“ƒOŽóM‚ÌˆóŽš‚Å‚ÍAƒL[ó‘Ô‚ð•\Ž¦‚µ‚È‚¢‚½‚ß‚ÌC³B Changed by H.Kubo 1999/01/06 */
 #if 0 /* ŒrüŠÔˆá‚¢C³ by H.Kubo 1999/02/04 */
@			if (separator_of_entry) {
@				if ( prog_cnt == SYS_PROGRAM_MAX ) {	/* ‘S–¾×o—ÍÏ */
@					if ( (ret = Print_Program_List_Head_Ext( 3, page, SYS_PROGRAM_COMMAND ) ) != OK ) {/*Ì¯Àˆóü*/
@						return ( ret );
@					}
@				}
@				else {
@					if ( (ret = Print_Program_List_Head_Ext( 2, page, SYS_PROGRAM_COMMAND ) ) != OK ) {/*Ì¯Àˆóü*/
@						return ( ret );
@					}
@				}
@			}
 #else
 			/* Œ»Ý•Å‚ÌÅŒã‚Ì Item ‚ªƒ|[ƒŠƒ“ƒO‚Ì‚Æ‚«‚Í‚±‚±‚Í”ò‚Î‚³‚ê‚é‚Ì‚Å‚±‚±‚Å‚Íl‚¦‚Ü‚¹‚ñB
 			** ‚»‚Ì‘¼‚Ìê‡‚ÍAˆê—¥‚Å‘S–¾×o—ÍŒã‚Æ“¯‚¶Œrü‚ðˆóŽš‚µ‚Ü‚·B
 			** by H.Kubo 1999/02/04
 			*/
			if (separator_of_entry) {
				if ( (ret = Print_Program_List_Head_Ext( 3, page, SYS_PROGRAM_COMMAND ) ) != OK ) {/*Ì¯Àˆóü*/
					return ( ret );
				}
			}
 #endif /* 0 */
#else
			if ( prog_cnt == SYS_PROGRAM_MAX ) {	/* ‘S–¾×o—ÍÏ */
				if ( (ret = Print_Program_List_Head_Ext( 3, page, SYS_PROGRAM_COMMAND ) ) != OK ) {/*Ì¯Àˆóü*/
					return ( ret );
				}
			}
			else {
				if ( (ret = Print_Program_List_Head_Ext( 2, page, SYS_PROGRAM_COMMAND ) ) != OK ) {/*Ì¯Àˆóü*/
					return ( ret );
				}
			}
#endif
			if ( line_cnt <= 1 ) {	/* ‚Pƒy[ƒW•ªˆóüI—¹‚ÌŽž */
				if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
					return ( ret );
				}
				is_change_page = FALSE;
				page++;
			}
		}
	}

	if (ProgDataEntryCheck( SYS_PROGRAM_LIST, 0 ) != SYS_PROGRAM_MAX) {	/* ƒŠƒXƒg‚Ì“o˜^—L‚è‚ÌŽž */
		if ( (ret = (UBYTE)PrintProgExtEntry( SYS_PROGRAM_LIST, &page, &is_change_page, &line_cnt) ) != OK ) { /*–¾×‚ðo—Í*/
			return ( ret );
		}
	}

	if (ProgDataEntryCheck( SYS_PROGRAM_STORE, 0 ) != SYS_PROGRAM_MAX) {	/* Œ´e’~Ï‚Ì“o˜^—L‚è‚ÌŽž */
		if ( (ret = (UBYTE)PrintProgExtEntry( SYS_PROGRAM_STORE, &page, &is_change_page, &line_cnt) ) != OK ) { /*–¾×‚ðo—Í*/
			return ( ret );
		}
	}

	if (is_change_page == TRUE) {	/* ƒNƒ[ƒY‚³‚ê‚Ä‚¢‚È‚¢Žž */
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
	}

	return ( OK );
}

#else	/* PRO_EXT_P_ONETOUCH == DISABLE */

WORD				Print_Program_List(
						 void )			/*‚È‚µ*/
{
	UBYTE	i;						/*loop*/
	UBYTE	page;					/*Íß°¼Þ*/
	UBYTE	prog_cnt;				/*ÌßÛ¸Þ×ÑÃÞ°À”Ô†*/
	UBYTE	line_cnt;				/*Žc‚èˆóü‰Â”\s”*/
	UBYTE	opt_line;				/*µÌß¼®ÝÃÞ°Às”*/
	register WORD	ret;			/*ŽÀsŒ‹‰Ê*/

	page = 1;
	prog_cnt = 0;

	i	= 0;
	opt_line	= 0;
	DialCheckPointer	= SYS_EMPTY_DIAL;
	DialCheckBitPointer	= 0;
	while ( prog_cnt != SYS_PROGRAM_MAX ) { /* ˆÈ‰ºSYS_ONETOUCH_MAX‚ðSYS_PROGRAM_MAX‚É•ÏX(ANZU) 95/12/15 •½”ö‰p“T */
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}

		if ( page == 1 ) {
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		else {
			line_cnt = (UBYTE)(PaperSizeLen() - 4);/*ˆóü‰Â”\s”¾¯Ä*/
		}

		if ( (ret = Print_Program_List_Head( 0, page ) ) != OK ) {/*Í¯ÀÞˆóü*/
			return ( ret );
		}
		while (1){
			if (( DialCheckPointer == SYS_EMPTY_DIAL ) &&	/* 97/09/03 By M.Kuwahara */
			    ( opt_line == 0 )) {
				ProgDataNextSearch( &prog_cnt );					/*ŽŸÃÞ°À»°Á*/
				DialCheckPointer    = SYS_DIRECT_DIAL;	/** Ží•Êƒ|ƒCƒ“ƒ^‚ð‰Šú‰»   */
				DialCheckBitPointer = 0;				/** ƒrƒbƒgƒ|ƒCƒ“ƒ^‚ð‰Šú‰» */
				/*”õl€–ÚÃÞ°À×²Ý”*/
#if ( PRO_MAKER == FX )
				opt_line = ProgOptionDataToString(
				  SYB_ProgramOnetouch[prog_cnt].Option.Item,
				  (WORD)SYB_ProgramOnetouch[prog_cnt].Option.OptionNumber.FX_Secure.Number,
				  SYB_ProgramOnetouch[prog_cnt].Option.OptionNumber.FX_Relay.Number,
				  SYB_ProgramOnetouch[prog_cnt].Option.OptionNumber.DatabaseNumber, List.S.Work, NULL );
#else
				opt_line = ProgOptionDataToString(
				  SYB_ProgramOnetouch[prog_cnt].Option.Item,
				  SYB_ProgramOnetouch[prog_cnt].Option.OptionNumber.SecureNumber,
				  SYB_ProgramOnetouch[prog_cnt].Option.OptionNumber.RelayGroupNumber,
				  SYB_ProgramOnetouch[prog_cnt].Option.OptionNumber.DatabaseNumber, List.S.Work, NULL );
#endif
			}
			if ( prog_cnt == SYS_PROGRAM_MAX ) {
				break;
			}

			if (SYB_ProgramOnetouch[prog_cnt].Option.Item == SYS_BATCH_MEMORY_TX) {
				if ( (ret = PrintProgramBatchLine(page, &i, prog_cnt, &line_cnt ) ) != OK ) {/*1–¾×ˆóü*/
					return ( ret );
				}
				DialCheckPointer    = SYS_EMPTY_DIAL;	/** Ží•Êƒ|ƒCƒ“ƒ^‚ð‰Šú‰»   */
				DialCheckBitPointer = 0;				/** ƒrƒbƒgƒ|ƒCƒ“ƒ^‚ð‰Šú‰» */
			}
			else {
				if ( (ret = (UBYTE)Print_Program_List_Specifi( page, &i, prog_cnt, &line_cnt) ) != OK ) { /*1–¾×ˆóü*/
					return ( ret );
				}
			}

			if ( opt_line <= i ){		/* ”õl—“‚ð‚·‚×‚Äo—Í‚µ‚½Žž */
				opt_line	= 0;
			}
			else{
				opt_line	-= i;
			}

			if ( line_cnt <= 1 ) {
				if (( DialCheckPointer == SYS_EMPTY_DIAL ) &&
				    ( opt_line == 0 )) {
					prog_cnt++;
					i	= 0;
					ProgDataNextSearch( &prog_cnt );			/*ŽŸÃÞ°À»°Á*/
					break;
				}
				if ( line_cnt <= 0 ){
					break;
				}
			}
			prog_cnt++;
			i	= 0;
		}

		if ( (ret = Print_Program_List_Head( 1, page ) ) != OK ) {/*Ì¯Àˆóü*/
			return ( ret );
		}

		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	return ( OK );
}
#endif	/* PRO_EXT_P_ONETOUCH */



/*************************************************************************
	module		:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒgƒwƒbƒ_ˆóü]
	functiom	:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
	common		:[
		List:
	]
	condition	:[
		Í¯ÀÞŽí—Þ
		,	0->Íß°¼Þæ“ªŒ©o‚µ
		,	1->Íß°¼Þ´ÝÄÞŒ©o‚µ
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 1]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Print_Program_List_Head(
						 UBYTE Category,	/*ƒwƒbƒ_Ží—Þ*/
						 UBYTE Page )		/*ƒy[ƒW*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Category == 0 ) {
		if ( Page == 1 ) {
			/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs{Œ©o‚µ{‚P‰üs*/
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			if ( (ret = Print_Head1_Common( PWRD_ProgOnetouchDir_K, 
							LST_NOT,10-1 )) != OK ) {
				return ( ret );
			}
#else
			if ( (ret = Print_Head1_Common( PWRD_ProgOnetouchDir,
						  	LST_XXX_TWI_XXX, 11-1 )) != OK ) { /* 20->11 For ANZU By H.Hirao 1996/02/07 */
				return ( ret );
			}
#endif

			/*Page Œ»ÝŽžŠÔ*/
			if ( (ret = PageTimePrint( Page, 2-1, 60-1 )) != OK ) {
				return ( ret );
			}

			/*†®†¢†Î†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢†¢†²*/
			Print_Program_List_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤ NO.†¤ÀÞ²ÔÙ”Ô††¤Žw’è“úŽž†¤‰ž—p‹@”\†¤”õlb*/
			Print_Program_List_Line( 1, List.S.Print, List.S.Attribute );
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
			if ( (ret = PagePrint( Page, 2-1 )) != OK ) {
				return ( ret );
			}
		}
	}
	else {
		/*†¶†¢†Ö†¢†Ö†¢†¢†Ö†¢†¢†¢†Ö†¢†¢†º*/
		Print_Program_List_Line( 4, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
	}
	return ( OK );
}

/*************************************************************************
	module		:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg‚Ì‚P–¾×ˆóü]
	functiom	:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg‚Ì‚P–¾×‚ðˆóü‚·‚éB]
	common		:[
		List				:
		SYB_OnetouchDial	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 1]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Print_Program_List_Specifi(
						 UBYTE Page,		/*ƒy[ƒW*/
						 UBYTE *Line,		/*Œ»Ý–¾×”*/
						 UBYTE ProgCnt,		/*ƒvƒƒOƒ‰ƒ€ƒ_ƒCƒ„ƒ‹”Ô†*/
						 register UBYTE *LineCnt)	/*ˆóŽšsˆÊ’u*/
{
	UBYTE	opt_line;				/*µÌß¼®ÝÃÞ°Às”*/
	UBYTE	prog_set	= FALSE;	/*ÌßÛ¸Þ×ÑÜÝÀ¯ÁNo¾¯ÄÌ×¸Þ*/
	UBYTE	now_line;
	register WORD	ret;			/*ŽÀsŒ‹‰Ê*/

#if (PRO_EXT_P_ONETOUCH == ENABLE) && (PRO_PANEL == KANJI) /* ƒ|[ƒŠƒ“ƒO‚ÌŽŸ‚Ìê‡‚ÍÅ‰‚ÌŒrü‚Í“ü‚è‚Ü‚¹‚ñB by H.Kubo 1999/01/06  */
#else
	if ( Page > 1 ) {		/* 97/09/03 By M.Kuwahara */
		if ( *LineCnt == (PaperSizeLen() - 4) ) {
			/*†®†¢†Î†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢†¢†²*/
			Print_Program_List_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			prog_set	= TRUE;
		}
		else{
			/*†®†¢†Î†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢†¢†²*/
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/09/09 By M.Kuwahara */
			Print_Program_List_Line( 8, List.S.Print, List.S.Attribute );
#else
			Print_Program_List_Line( 2, List.S.Print, List.S.Attribute );
#endif
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
	}
	else{
		/*†®†¢†Î†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢†¢†²*/
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/09/11 By M.Kuwahara */
		now_line = (PaperSizeLen() - 12);
		if (*LineCnt == now_line) {
			Print_Program_List_Line( 2, List.S.Print, List.S.Attribute );
		}
		else {
			Print_Program_List_Line( 8, List.S.Print, List.S.Attribute );
		}
#else
		Print_Program_List_Line( 2, List.S.Print, List.S.Attribute );
#endif
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	(*LineCnt)--;
#endif

	/*†¤<‚w>†¤xxxxxxxxxxxx†¤Z9,Z9:99†¤xxxxxx†¤zzzz,zzzz,zzzz,zzzz†¤*/
		/*”õl€–ÚÃÞ°À×²Ý”*/
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/06 By M.Kuwahara */
 #if ( PRO_MAKER == FX )
	opt_line = ProgOptionDataToString(
	  SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.Item,
	  (WORD)SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.OptionNumber.FX_Secure.Number,
	  SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.OptionNumber.FX_Relay.Number,
	  SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.OptionNumber.DatabaseNumber, 
	  List.S.Work, 
	  NULL );
 #else
	opt_line = ProgOptionDataToString(
	  SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.Item,
	  SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.OptionNumber.SecureNumber,
	  SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.OptionNumber.RelayGroupNumber,
	  SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.OptionNumber.DatabaseNumber, 
	  List.S.Work,
 	  NULL );
 #endif
#else
 #if ( PRO_MAKER == FX )
	opt_line = ProgOptionDataToString(
	  SYB_ProgramOnetouch[ProgCnt].Option.Item,
	  (WORD)SYB_ProgramOnetouch[ProgCnt].Option.OptionNumber.FX_Secure.Number,
	  SYB_ProgramOnetouch[ProgCnt].Option.OptionNumber.FX_Relay.Number,
	  SYB_ProgramOnetouch[ProgCnt].Option.OptionNumber.DatabaseNumber, 
	  List.S.Work, 
	  NULL );
 #else
	opt_line = ProgOptionDataToString(
	  SYB_ProgramOnetouch[ProgCnt].Option.Item,
	  SYB_ProgramOnetouch[ProgCnt].Option.OptionNumber.SecureNumber,
	  SYB_ProgramOnetouch[ProgCnt].Option.OptionNumber.RelayGroupNumber,
	  SYB_ProgramOnetouch[ProgCnt].Option.OptionNumber.DatabaseNumber, 
	  List.S.Work,
 	  NULL );
 #endif
#endif
	if ( opt_line >= *Line ){		/* ”õl—“‚ª‚Ü‚¾‚ ‚éŽž */
		opt_line	-= *Line;
	}
	else{
		opt_line	= 0;
	}

	while ( *LineCnt != 0 ) {		/* 97/09/03 By M.Kuwahara */
		if(( DialCheckPointer == SYS_EMPTY_DIAL ) &&
		   ( opt_line == 0 )){
			break;
		}
		Print_Program_List_Line( 3, List.S.Print, List.S.Attribute );
		if ( (*Line == 0) ||	/* 97/09/03 By M.Kuwahara */
		     (prog_set == TRUE) ) {
			/* No. */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || defined(HINOKI3)	/* by K.Watanabe 2004/10/18 */
			List.S.Print[2-1] = 0x50;	/* 'P'‚ÌASCIIº-ÄÞ */	/* For ANZU By H.Hirao 1996/01/10 */
			CMN_UnsignedIntToASC( &List.S.Print[3-1], /* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†P1`P12‚ð‚Â‚­‚é */
			 ProgCnt+1, 0, '0' );
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_PANEL == ANK)
			List.S.Print[2-1] = '[';
			List.S.Print[5-1] = ']';
/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
  #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add By H.Fujimura 1998/11/12 */
			CMN_UnsignedIntToASC( &List.S.Print[3-1], /* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†25`30‚ð‚Â‚­‚é */
			 ProgCnt+25, 0, '0' );
  #else
			CMN_UnsignedIntToASC( &List.S.Print[3-1], /* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†73`80‚ð‚Â‚­‚é */
			 ProgCnt+73, 0, '0' );
  #endif
 #endif
 #if (PRO_PANEL == KANJI)
	 		/* ƒƒ“ƒ^ƒbƒ`‚Ì•\Ž¦‚ð[]->ŠG•¶Žš‚É•ÏX By O.Kimoto 1998/01/22 */
			List.S.Print[2-1] = LCD_PICFONT+3;
			List.S.Print[3-1] = LCD_PICFONT_LOWER;
  #if (PRO_KEYPANEL == PANEL_POPLAR_H)	/* 1998/07/16 By M.Kuwahara */
			CMN_UnsignedIntToASC( &List.S.Print[4-1], /* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†73`80‚ð‚Â‚­‚é */
			 ProgCnt+73, 0, '0' );
  #endif
  #if (PRO_KEYPANEL == PANEL_SAKAKI)
			CMN_UnsignedIntToASC( &List.S.Print[4-1], /* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†25`30‚ð‚Â‚­‚é */
			 ProgCnt+25, 0, '0' );
  #endif
 #endif
#endif
			if (*Line == 0) {		/* ÌßÛ¸Þ×ÑÜÝÀ¯Á–ˆ‚Ìæ“ª‚Ì‚Ý */
				/*Žw’è“úŽž*/

#if (0)
**				/* ANK‚ÆKANJI‚ÅŽž–¢“o˜^Žž‚Ì‰Šú’l‚ªˆÙ‚È‚è‚Ü‚·B
**				** by O.Kimoto 1998/06/25
**				*/
**				/* if ( SYB_OnetouchDial[ProgCnt].DialData.Program.ExecTime == 0xFFFFFFFF ) { *//* C³ Î‹´³˜a 94/08/02 */
**				if ( SYB_ProgramOnetouch[ProgCnt].ExecTime == 0x00000000 ) { /* For ANZU By H.Hirao 1995/12/15 */
#else
 #if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/06 By M.Kuwahara */
  #if (PRO_PANEL == KANJI)
				if ( SYB_ProgramOnetouch[ProgCnt].EntryData.Command.ExecTime == 0xFFFFFFFF ) {
  #else
				if ( SYB_ProgramOnetouch[ProgCnt].EntryData.Command.ExecTime == 0x00000000 ) { /* For ANZU By H.Hirao 1995/12/15 */
  #endif
 #else
  #if (PRO_PANEL == KANJI)
				if ( SYB_ProgramOnetouch[ProgCnt].ExecTime == 0xFFFFFFFF ) {
  #else
   #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/08/31 Y.Matsukuma */
				/* ƒ~ƒmƒ‹ƒ^ROM‚ÍAŽž‚ÍŠÖŒW‚È‚¢ */
				SYB_ProgramOnetouch[ProgCnt].ExecTime = 0x00000000;
   #endif
				if ( SYB_ProgramOnetouch[ProgCnt].ExecTime == 0x00000000 ) { /* For ANZU By H.Hirao 1995/12/15 */
  #endif
 #endif
#endif

					/** ‘¦Žž”­M‚Ìê‡ */
					AttributeSet( &List.S.Print[51-1], &List.S.Attribute[51-1], PWRD_NotTime, LST_NOT );
				}
				else { /** ŽžŽw’è‘—M‚Ìê‡ */
					/* CriterionMinuteToDayTimeAsc(
							(UDWORD)((SYB_OnetouchDial[ProgCnt].DialData.Program.ExecTime & 0x7FFFFFFF)/60),
							LST_DDHHMM, List.S.Work ); */ /** "& 0x7FFFFFFF","/60"’Ç‰Á Î‹´³˜a 94/08/03 */
					/*if (SYB_OnetouchDial[ProgCnt].DialData.Program.ExecTime & 0x80000000) { */

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/06 By M.Kuwahara */
 #if (PRO_PANEL == KANJI)
					/* ‚o‚n‚o‚k‚`‚qQ‚g‚Í‚h‚b‚g‚n‚t‚Ì—¬—p‚È‚Ì‚ÅA‚`‚m‚jŒn‚ÌŽž“o˜^‚Æ‚ÍA‚P“ú‚Ì‚¸‚ê‚ª¶‚¶‚Ü‚·B
					** ‚æ‚Á‚ÄA‚h‚b‚g‚n‚t‚Æ“¯‚¶—p‚Éˆ—‚µ‚Ü‚·B
					** by O.Kimoto
					*/
					CriterionMinuteToDayTimeAsc(
							(UDWORD)((SYB_ProgramOnetouch[ProgCnt].EntryData.Command.ExecTime & 0x7FFFFFFFUL)/60),
							LST_DDHHMM, List.S.Work );
 #else
					MinuteToDayHourMinuteAsc(
							(WORD)((SYB_ProgramOnetouch[ProgCnt].EntryData.Command.ExecTime & 0x7FFFFFFF)/60),
							List.S.Work, LST_DATE_HOUR_MINUTE);
 #endif

					if (SYB_ProgramOnetouch[ProgCnt].EntryData.Command.ExecTime & 0x80000000) { /* For ANZU By H.Hirao 1995/12/15 */
						/** –ˆ“ú‘—M‚Ìê‡ ’Ç‰Á Î‹´³˜a 94/08/03 */
						List.S.Work[1] = '0';
					}
#else	/** PRO_EXT_P_ONETOUCH == DISABLE */
 #if (PRO_PANEL == KANJI)
					/* ‚o‚n‚o‚k‚`‚qQ‚g‚Í‚h‚b‚g‚n‚t‚Ì—¬—p‚È‚Ì‚ÅA‚`‚m‚jŒn‚ÌŽž“o˜^‚Æ‚ÍA‚P“ú‚Ì‚¸‚ê‚ª¶‚¶‚Ü‚·B
					** ‚æ‚Á‚ÄA‚h‚b‚g‚n‚t‚Æ“¯‚¶—p‚Éˆ—‚µ‚Ü‚·B
					** by O.Kimoto
					*/
					CriterionMinuteToDayTimeAsc(
							(UDWORD)((SYB_ProgramOnetouch[ProgCnt].ExecTime & 0x7FFFFFFFUL)/60),
							LST_DDHHMM, List.S.Work );
 #else
					MinuteToDayHourMinuteAsc(
							(WORD)((SYB_ProgramOnetouch[ProgCnt].ExecTime & 0x7FFFFFFF)/60),
							List.S.Work, LST_DATE_HOUR_MINUTE);
 #endif

					if (SYB_ProgramOnetouch[ProgCnt].ExecTime & 0x80000000) { /* For ANZU By H.Hirao 1995/12/15 */
						/** –ˆ“ú‘—M‚Ìê‡ ’Ç‰Á Î‹´³˜a 94/08/03 */
						List.S.Work[1] = '0';
					}
#endif
					CMN_StringCopy( &List.S.Print[48-1], List.S.Work );
				}
				/*µ³Ö³·É³*/
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/06 By M.Kuwahara */
				CommunicationKindName(SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.Item,
					LST_NAME_2, &List.S.Print[57-1], &List.S.Attribute[57-1] ); /* For ANZU 1995/12/15 */
#else
				CommunicationKindName(SYB_ProgramOnetouch[ProgCnt].Option.Item,
					LST_NAME_2, &List.S.Print[57-1], &List.S.Attribute[57-1] ); /* For ANZU 1995/12/15 */
#endif
			}
			prog_set	= FALSE;
		}

		/*ÀÞ²ÔÙÊÞÝºÞ³€–ÚÃÞ°À*/
		now_line	= *Line;
		if ( DialCheckPointer != SYS_EMPTY_DIAL ) {
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/21 Y.Matsukuma */
			CMN_StringCopy( &List.S.Print[7-1], SYB_OnetouchDial[ProgCnt].Name );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			return( OK );
#else
 #if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/06 By M.Kuwahara */
			ProgramDataDialToString((struct SYS_DialData_t *)&SYB_ProgramOnetouch[ProgCnt].EntryData.Command.DialNumber,
										SYS_PRG_DIAL_MAX, List.S.Work, now_line );
 #else
			ProgramDataDialToString((struct SYS_DialData_t *)&SYB_ProgramOnetouch[ProgCnt].DialNumber,
										SYS_PRG_DIAL_MAX, List.S.Work, now_line );
 #endif
			CMN_StringCopy( &List.S.Print[7-1], List.S.Work );
#endif
		}

		/*”õl€–ÚÃÞ°À*/
		if( opt_line > 0 ){
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/06 By M.Kuwahara */
 #if ( PRO_MAKER == FX )	/* 97/09/03 By M.Kuwahara */
			ProgOptionDataToString(
			  SYB_ProgramOnetouch[ProgCnt].EntyrData.Command.Option.Item,
			  (WORD)SYB_ProgramOnetouch[ProgCnt].EntyrData.Command.Option.OptionNumber.FX_Secure.Number,
			  SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.OptionNumber.FX_Relay.Number,
			  SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.OptionNumber.DatabaseNumber, List.S.Work, now_line );
 #else
			ProgOptionDataToString(
			  SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.Item,
			  SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.OptionNumber.SecureNumber,
			  SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.OptionNumber.RelayGroupNumber,
			  SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.OptionNumber.DatabaseNumber, List.S.Work, now_line );
 #endif
#else
 #if ( PRO_MAKER == FX )	/* 97/09/03 By M.Kuwahara */
			ProgOptionDataToString(
			  SYB_ProgramOnetouch[ProgCnt].Option.Item,
			  (WORD)SYB_ProgramOnetouch[ProgCnt].Option.OptionNumber.FX_Secure.Number,
			  SYB_ProgramOnetouch[ProgCnt].Option.OptionNumber.FX_Relay.Number,
			  SYB_ProgramOnetouch[ProgCnt].Option.OptionNumber.DatabaseNumber, List.S.Work, now_line );
 #else
			ProgOptionDataToString(
			  SYB_ProgramOnetouch[ProgCnt].Option.Item,
			  SYB_ProgramOnetouch[ProgCnt].Option.OptionNumber.SecureNumber,
			  SYB_ProgramOnetouch[ProgCnt].Option.OptionNumber.RelayGroupNumber,
			  SYB_ProgramOnetouch[ProgCnt].Option.OptionNumber.DatabaseNumber, List.S.Work, now_line );
 #endif
#endif
			CMN_StringCopy( &List.S.Print[66-1], List.S.Work );
			opt_line--;
		}

		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*LineCnt)--;
		(*Line)++;
	}
	return ( OK );
}

/*************************************************************************
	module		:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg ƒlƒNƒXƒg ƒT[ƒ`n
	functiom	:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg‚ÌŽŸ‚ðƒT[ƒ`‚·‚é]
	common		:[
		SYB_OnetouchDial	:
	]
	condition	:[
		’Zkƒ_ƒCƒ„ƒ‹”Ô†
		,	ƒf[ƒ^ƒGƒ“ƒh|„SYS_ONETOUCH_MAX
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 1]
	author		:[–L“c_Žq]
*************************************************************************/
void				ProgDataNextSearch(
						 register UBYTE *ProgCnt )/*’Zkƒ_ƒCƒ„ƒ‹”Ô†*/
{
	UBYTE	i;						/*loop*/

	for ( i = (*ProgCnt); i < SYS_PROGRAM_MAX; i++ ) {
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/06 By M.Kuwahara */
		if ( SYB_ProgramOnetouch[i].Item == SYS_PROGRAM_COMMAND ) {
			(*ProgCnt) = i;
			break;
		}
#else
		if ( SYB_ProgramOnetouch[i].Status == SYS_CMD_SETTING ) { /* For ANZU By H.Hirao 1995/12/15 */
			(*ProgCnt) = i;
			break;
		}
#endif
	}
	if ( i == SYS_PROGRAM_MAX ) { /* For ANZU By H.Hirao 1995/12/15 */
		(*ProgCnt) = SYS_PROGRAM_MAX;
	}
}

/*************************************************************************
	module		:[PGƒƒ“ƒ^ƒbƒ`ƒ^ƒCƒv‚Ì‰¡‹æØ‚èŒrüì¬]
	functiom	:[
		PGƒƒ“ƒ^ƒbƒ`AƒcƒEƒVƒ“ƒˆƒ„ƒNAƒcƒEƒVƒ“ƒˆƒ„ƒNƒVƒ‡ƒEƒLƒ‡‚Ì
		‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB
	]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
		,	0 = †®†¢†¢†Î†¢†¢†¢†¢†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†¢†Î†Î†¢†¢†²
		,	1 = †¤NO. †¤ À Þ²ÔÙ”Ô†	†¤Žw’èŽžŠÔ†¤‰ž—p‹@”\†¤”õl†¤
		,	2 = †¾†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†Î†¢†Þ†¢†¢†Æ
		,	3 = †¤@  †¤			†¤		  †¤	    †¤	  †¤
		,	4 = †¶†¢†¢†Ö†¢†¢†¢†¢†¢†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†¢†Î†Ö†¢†¢†º
		,	5 = „     „¥„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„§
		,	6 = „     „                                       „ 
		,	7 = „¤„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„£
		,	8 = „¥„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„§
		,	9 = „¡„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢

		,	10= „¡„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢
		,	11= „ No. „        Ø½Ä–¼          „ 
		,	12= „¥„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§
		,	13= „     „                       „ 
		,	14= „¤„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„£

		,	15= „¡„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢
		,	16= „ No. „  Ží•Ê „   ÎÞ¯¸½–¼   „ ã‘‚«          „ 
		,	17= „¥„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§
		,	18= „     „       „             „                 „ 
		,	19= „     „¥„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§
		,	20= „     „                                       „ 
		,	21= „¤„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„£
		,	22= „¥„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§

	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 1]
	author		:[–L“c_Žq]
*************************************************************************/
void				Print_Program_List_Line(
						 UBYTE Category,				/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,		/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )	/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†¢†Î†¢†¢†¢†¢†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†¢†Î†¢†¢†²*/
			AscString[1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[6-1] = LST_KLINE8;
			AscString[47-1] = LST_KLINE8;
			AscString[56-1] = LST_KLINE8;
			AscString[65-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE9;
			break;
		case 1:
			/*†¤NO. †¤ÀÞ²ÔÙ”Ô† †¤Žw’è“úŽž †¤‰ž—p‹@”\†¤”õl†¤*/
			AscString[1-1] = LST_KLINEI;
			AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_No, LST_NOT );
			AscString[6-1] = LST_KLINEI;
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/21 Y.Matsukuma */
			AttributeSet( &AscString[18-1], &AttString[18-1], PWRD_Box, LST_NOT );
			AscString[22-1] = '&';
			AttributeSet( &AscString[24-1], &AttString[24-1], PWRD_Pages, LST_NOT );
#else
			AttributeSet( &AscString[18-1], &AttString[18-1], PWRD_TeleNumber, LST_NOT );
#endif
			AscString[47-1] = LST_KLINEI;
			AttributeSet( &AscString[48-1], &AttString[48-1], PWRD_DelyTime, LST_NOT );
			AscString[56-1] = LST_KLINEI;
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )	/* 97/02/06 M.Kuwahara */
			AttributeSet( &AscString[57-1], &AttString[57-1], PWRD_Option, LST_NOT );
#else
			AttributeSet( &AscString[57-1], &AttString[57-1], PWRD_Option, LST_NOT );
#endif
			AscString[65-1] = LST_KLINEI;
			AttributeSet( &AscString[70-1], &AttString[70-1], PWRD_Note, LST_NOT );
			AscString[80-1] = LST_KLINEI;
			break;
		case 2:
			/*†¾†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†¢†Þ†¢†¢†Æ*/
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[6-1] = LST_KLINE5;
			AscString[47-1] = LST_KLINE5;
			AscString[56-1] = LST_KLINE5;
			AscString[65-1] = LST_KLINE5;
			AscString[80-1] = LST_KLINE6;
			break;
		case 3:
			/*†¤@	†¤			  †¤		†¤		†¤	  †¤*/
			AscString[1-1] = LST_KLINEI;
			AscString[6-1] = LST_KLINEI;
			AscString[47-1] = LST_KLINEI;
			AscString[56-1] = LST_KLINEI;
			AscString[65-1] = LST_KLINEI;
			AscString[80-1] = LST_KLINEI;
			break;
		case 4:
			/*†¶†¢†¢†Ö†¢†¢†¢†¢†¢†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†¢†Ö†¢†¢†º*/
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[6-1] = LST_KLINE2;
			AscString[47-1] = LST_KLINE2;
			AscString[56-1] = LST_KLINE2;
			AscString[65-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE3;
			break;
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/17 By M.Kuwahara */
		case 5:
			/*„     „¥„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„§ */
			AscString[1-1] = LST_KLINEI;
			AscString[6-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[7-1], 73, LST_KLINE_ );
			AscString[47-1] = LST_KLINE2;
			AscString[56-1] = LST_KLINE2;
			AscString[65-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE6;
			break;
		case 6:
			/*„     „                                     „  */
			AscString[1-1] = LST_KLINEI;
			AscString[6-1] = LST_KLINEI;
			AscString[80-1] = LST_KLINEI;
			break;
		case 7:
			/*„¤„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„£ */
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[6-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE3;
			break;
		case 8:
			/*„¥„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„§ */
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[6-1] = LST_KLINE5;
			AscString[47-1] = LST_KLINE8;
			AscString[56-1] = LST_KLINE8;
			AscString[65-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE6;
			break;
		case 9:
			/*„¡„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢ */
			AscString[1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* “ñƒy[ƒW–Ú‚Ìæ“ª‚ÌŒrü‚ª‚¨‚©‚µ‚¢B fixed by H.Kubo 1999/01/06 */
			AscString[6-1] = LST_KLINE8;
#else
			AscString[6-1] = LST_KLINE5;
#endif
			AscString[80-1] = LST_KLINE9;
			break;
		case 10:
			/*„¡„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢ */
			AscString[1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 27, LST_KLINE_ );
			AscString[6-1] = LST_KLINE8;
			AscString[29-1] = LST_KLINE9;
			break;
		case 11:
			/*„  No.„        Ø½Ä–¼          „  */
			AscString[1-1] = LST_KLINEI;
			AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_No, LST_NOT );
			AscString[6-1] = LST_KLINEI;
			AttributeSet( &AscString[14-1], &AttString[14-1], PWRD_ListName, LST_NOT );	/* "Ø½Ä–¼" */
			AscString[29-1] = LST_KLINEI;
			break;
		case 12:
			/*„¥„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§ */
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 27, LST_KLINE_ );
			AscString[6-1] = LST_KLINE5;
			AscString[29-1] = LST_KLINE6;
			break;
		case 13:
			/*„     „                       „  */
			AscString[1-1] = LST_KLINEI;
			AscString[6-1] = LST_KLINEI;
			AscString[29-1] = LST_KLINEI;
			break;
		case 14:
			/*„¤„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„£ */
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 27, LST_KLINE_ );
			AscString[6-1] = LST_KLINE2;
			AscString[29-1] = LST_KLINE3;
			break;
		case 15:
			/*„¡„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢ */
			AscString[1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[6-1] = LST_KLINE8;
			AscString[14-1] = LST_KLINE8;
			AscString[34-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE9;
			break;
		case 16:
			/*„  No.„   Ží•Ê  „  ÎÞ¯¸½–¼   „ ã‘‚«                „  */
			AscString[1-1] = LST_KLINEI;
			AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_No, LST_NOT );
			AscString[6-1] = LST_KLINEI;
			AttributeSet( &AscString[8-1], &AttString[8-1], PWRD_Kind, LST_NOT );
			AscString[14-1] = LST_KLINEI;
			AttributeSet( &AscString[19-1], &AttString[19-1], PWRD_BoxName, LST_NOT );
			AscString[34-1] = LST_KLINEI;
			AttributeSet( &AscString[35-1], &AttString[35-1], PWRD_Replace, LST_NOT );
			AscString[80-1] = LST_KLINEI;
			break;
		case 17:
			/*„¥„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§ */
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[6-1] = LST_KLINE5;
			AscString[14-1] = LST_KLINE5;
			AscString[34-1] = LST_KLINE5;
			AscString[80-1] = LST_KLINE6;
			break;
		case 18:
			/*„     „           „           „                      „  */
			AscString[1-1] = LST_KLINEI;
			AscString[6-1] = LST_KLINEI;
			AscString[14-1] = LST_KLINEI;
			AscString[34-1] = LST_KLINEI;
			AscString[80-1] = LST_KLINEI;
			break;
		case 19:
			/*„     „¥„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§ */
			AscString[1-1] = LST_KLINEI;
			AscString[6-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[7-1], 73, LST_KLINE_ );
			AscString[14-1] = LST_KLINE2;
			AscString[34-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE6;
			break;
		case 20:
			/*„     „                                     „  */
			AscString[1-1] = LST_KLINEI;
			AscString[6-1] = LST_KLINEI;
			AscString[80-1] = LST_KLINEI;
			break;
		case 21:
			/*„¤„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„£ */
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[6-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE3;
			break;
		case 22:
			/*„¥„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§ */
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[6-1] = LST_KLINE5;
			AscString[14-1] = LST_KLINE8;
			AscString[34-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE6;
			break;
 #if (PRO_EXT_P_ONETOUCH == ENABLE) && (PRO_PANEL == KANJI) /* added by H.Kubo 1999/01/06 */
		case 23:
			/*„¥„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„§ */
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[6-1] = LST_KLINE5;
			AscString[47-1] = LST_KLINE5;
			AscString[56-1] = LST_KLINE5;
			AscString[65-1] = LST_KLINE5;
			AscString[80-1] = LST_KLINE6;
			break;
		case 24:
			/*„¤„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„£ */
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[6-1] = LST_KLINE2;
			AscString[47-1] = LST_KLINE2;
			AscString[56-1] = LST_KLINE2;
			AscString[65-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE3;
			break;
 #endif
#endif
	}
}

/*************************************************************************
	module		:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg‚Ì‚P–¾×ˆóüiˆêŠ‡‘—M—pj]
	functiom	:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg‚Ì‚P–¾×iˆêŠ‡‘—M—pj‚ðˆóü‚·‚éB]
	common		:[
		List				:
		SYB_OnetouchDial	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/05/22]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD		PrintProgramBatchLine(
						 UBYTE Page,		/*ƒy[ƒW*/
						 UBYTE *Line,		/*Œ»Ý–¾×”*/
						 UBYTE ProgCnt,		/*ƒvƒƒOƒ‰ƒ€ƒ_ƒCƒ„ƒ‹”Ô†*/
						 register UBYTE *LineCnt )	/*ˆóŽšsˆÊ’u*/
{
	UBYTE	box;
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/06 By M.Kuwahara */
	UBYTE	page_line;		/* ‚PÍß°¼Þ‚Ìs” */

	box = SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.OptionNumber.BatchNumber;
#else
	box = SYB_ProgramOnetouch[ProgCnt].Option.OptionNumber.BatchNumber;
#endif

	/* Œrü */
#if (PRO_EXT_P_ONETOUCH == ENABLE) && (PRO_PANEL == KANJI) /* Å‰‚ÌŒrü‚Í‚æ‚»‚Å‘‚«‚Ü‚·B by H.Kubo 1999/01/06  */
#else
	if (Page > 1) {		/* 97/09/03 By M.Kuwahara */
		if (*LineCnt == (PaperSizeLen() - 4)) {
			/*†®†¢†Î†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢†¢†²*/
			Print_Program_List_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
		else{
			/*†®†¢†Î†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢†¢†²*/
 #if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/09/09 By M.Kuwahara */
			Print_Program_List_Line( 8, List.S.Print, List.S.Attribute );
 #else
			Print_Program_List_Line( 2, List.S.Print, List.S.Attribute );
 #endif
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
	}
	else{
		/*†®†¢†Î†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢†¢†²*/
 #if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/09/09 By M.Kuwahara */
		page_line = (PaperSizeLen() - 12);
		if (*LineCnt == page_line) {
			Print_Program_List_Line( 2, List.S.Print, List.S.Attribute );
		}
		else {
			Print_Program_List_Line( 8, List.S.Print, List.S.Attribute );
		}
 #else
		Print_Program_List_Line( 2, List.S.Print, List.S.Attribute );
 #endif
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	(*LineCnt)--;
#endif /* (PRO_EXT_P_ONETOUCH == ENABLE) && (PRO_PANEL == KANJI) */

	/*†¤<‚w>†¤xxxxxxxxxxxx†¤Z9,Z9:99†¤xxxxxx†¤zzzz,zzzz,zzzz,zzzz†¤*/

	/*ÀÞ²ÔÙ”Ô†€–Úˆóü•K—vs”*/

	Print_Program_List_Line( 3, List.S.Print, List.S.Attribute );

	/* No. */
	/* List.S.Print[2-1] = '<';
	List.S.Print[3-1] = CMN_OffsetToOnetouchCode( ProgCnt );
	List.S.Print[4-1] = '>'; */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || defined(HINOKI3)	/* by K.Watanabe 2004/10/22 */
	List.S.Print[2-1] = 0x50;	/* 'P'‚ÌASCIIº-ÄÞ */	/* For ANZU By H.Hirao 1996/01/10 */
	CMN_UnsignedIntToASC( &List.S.Print[3-1], ProgCnt+1, 0, '0' ); /* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†P1`P12‚ð‚Â‚­‚é */
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_PANEL == ANK)
	List.S.Print[2-1] = '[';
	List.S.Print[5-1] = ']';
/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
  #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add By H.Fujimura 1998/11/12 */
	CMN_UnsignedIntToASC( &List.S.Print[3-1], ProgCnt+25, 0, '0' ); /* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†25`30‚ð‚Â‚­‚é */
  #else
	CMN_UnsignedIntToASC( &List.S.Print[3-1], ProgCnt+73, 0, '0' ); /* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†73`80‚ð‚Â‚­‚é */
  #endif
 #endif
 #if (PRO_PANEL == KANJI)
	/* ƒƒ“ƒ^ƒbƒ`‚Ì•\Ž¦‚ð[]->ŠG•¶Žš‚É•ÏX By O.Kimoto 1998/01/22 */
	List.S.Print[2-1] = LCD_PICFONT+3;
	List.S.Print[3-1] = LCD_PICFONT_LOWER;
  #if (PRO_KEYPANEL == PANEL_POPLAR_H)	/* 1998/07/16 By M.Kuwahara */
	CMN_UnsignedIntToASC( &List.S.Print[4-1], ProgCnt+73, 0, '0' ); /* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†73`80‚ð‚Â‚­‚é *//* 1998/07/16 By M.Kuwahara */
  #endif
  #if (PRO_KEYPANEL == PANEL_SAKAKI)	/* 1998/07/16 By M.Kuwahara */
	CMN_UnsignedIntToASC( &List.S.Print[4-1], ProgCnt+25, 0, '0' ); /* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†25`30‚ð‚Â‚­‚é */
  #endif
 #endif
#endif

	/** Žw’èŽž */

#if (PRO_PANEL == KANJI)
	/* ‚o‚n‚o‚k‚`‚qQ‚g‚Í‚h‚b‚g‚n‚t‚Ì—¬—p‚È‚Ì‚ÅA‚`‚m‚jŒn‚ÌŽž“o˜^‚Æ‚ÍA‚P“ú‚Ì‚¸‚ê‚ª¶‚¶‚Ü‚·B
	** ‚æ‚Á‚ÄA‚h‚b‚g‚n‚t‚Æ“¯‚¶—p‚Éˆ—‚µ‚Ü‚·B
	** by O.Kimoto
	*/
	CriterionMinuteToDayTimeAsc(
				(UDWORD)((SYB_BatchTxFile[box].ProgramTime & 0x7FFFFFFFUL)/60),
				LST_DDHHMM, List.S.Work );
#else
	MinuteToDayHourMinuteAsc(
			(WORD)((SYB_BatchTxFile[box].ProgramTime & 0x7FFFFFFF)/60),
			List.S.Work, LST_DATE_HOUR_MINUTE);
#endif

	if (SYB_BatchTxFile[box].ProgramTime & 0x80000000) { /* For ANZU By H.Hirao 1995/12/15 */
		List.S.Work[1] = '0';
	}
	CMN_StringCopy( &List.S.Print[48-1], List.S.Work );

	/*µ³Ö³·É³*/
	CommunicationKindName( SYS_BATCH_MEMORY_TX,
						   LST_NAME_2, 
						   &List.S.Print[57-1],
						   &List.S.Attribute[57-1] ); /* For ANZU 1995/12/15 */
	/*ÀÞ²ÔÙÊÞÝºÞ³€–ÚÃÞ°À*/
	switch (SYB_BatchTxFile[box].DialNumber[0].Item) {
	case SYS_DIRECT_DIAL:
		CMN_BCD_ToASC_String(List.S.Work,
							 &SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Direct[0]); 
		break;
	case SYS_SPEED_DIAL:
#if (0)
//		List.S.Work[0] = '(';
//		CMN_UnsignedIntToASC(&List.S.Work[1], 
//							 (SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Speed + OPR_SPEED_DIAL_MIN),
//							 3 ,'0');
//		List.S.Work[4] = ')';
//		List.S.Work[5] = NULL;
//		break;
#endif
		if ( SYS_SPEED_DIAL_MAX+SYS_2ND_SPEED_DIAL_MAX >= 100 ) {
#if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
			List.S.Work[0] = *CalculateStringAddress(&D2W_HeadCharacter_Speed);
#else
			List.S.Work[0] = 'S';
#endif
			if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
				if ( GetRecordFromNumber( SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Speed ) != 0xFFFF ) {
#if (1) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
					CMN_UnsignedIntToASC( &List.S.Work[1],
										  GetRecordFromNumber( SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Speed ),
										  OP_SPEED_FIGURE_MAX, '0' );
#else
//					CMN_UnsignedIntToASC( &List.S.Work[1],
//										  GetRecordFromNumber( SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Speed ),
//										  3, '0' );
#endif
				}
				else {
#if (1) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
					CMN_MemorySet( &List.S.Work[1], OP_SPEED_FIGURE_MAX,'*' );
#else
//					CMN_MemorySet( &List.S.Work[1], 3,'*' );
#endif
				}
			}
			else{	/* ’Êí‚Ì’Zk‚ÌŽž */
#if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ª000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
				CMN_UnsignedIntToASC( &List.S.Work[1], 
									  SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Speed+(OPR_SPEED_DIAL_MIN), 
									  3, '0' );
#else
				CMN_UnsignedIntToASC( &List.S.Work[1], 
									  SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Speed+1,
									  3, '0' );
#endif
			}
#if (1) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
			if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
				List.S.Work[OP_SPEED_FIGURE_MAX + 1] = NULL;
			}
			else {
				List.S.Work[4] = NULL;
			}
#else
//			List.S.Work[4] = NULL;
#endif
		}
		else {
#if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
			List.S.Work[0] = *CalculateStringAddress(&D2W_HeadCharacter_Speed);
#else
			List.S.Work[0] = 'S';
#endif
			if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
				if ( GetRecordFromNumber( SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Speed ) != 0xFFFF ) {
					CMN_UnsignedIntToASC( &List.S.Work[1], 
						GetRecordFromNumber( SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Speed ), 2, '0' );
				}
				else {
					CMN_MemorySet( &List.S.Work[1], 3,'*' );
				}
			}
			else{	/* ’Êí‚Ì’Zk‚ÌŽž */
#if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ª000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
				CMN_UnsignedIntToASC( &List.S.Work[1], 
									  SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Speed,
									  2, '0' );
#else
				CMN_UnsignedIntToASC( &List.S.Work[1], 
									  SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Speed + 1,
									  2, '0' );
#endif
			}
			List.S.Work[3] = NULL;
		}
		break;
	case SYS_ONETOUCH_DIAL:
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		List.S.Work[0] = '[';
		if (SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Onetouch >= CMN_OnetouchCodeToOffset(ONETOUCH_U1_KEY)) {
			List.S.Work[1] = 'U';
			List.S.Work[2] = 
				GetOnetouchSideCode(CMN_OffsetToOnetouchCode(SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Onetouch));
			List.S.Work[3] = ']';
			List.S.Work[4] = NULL;
		}
		else {
			List.S.Work[1] = CMN_OffsetToOnetouchCode(SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Onetouch);
			List.S.Work[2] = ']';
			List.S.Work[3] = NULL;
		}
#else
		CMN_MemorySet( List.S.Work, 4, ' ' );
		List.S.Work[4] = NULL;
 #if (PRO_PANEL == ANK)
		List.S.Work[0] = '[';
		CMN_UnsignedIntToASC( &List.S.Work[1], 	/* 01`72‹L†‚ð‚Â‚­‚é */
				(UWORD)(CMN_OffsetToOnetouchCode( SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Onetouch ) - 0x40),
				 2, '0' );
		List.S.Work[3] = ']';
 #endif
 #if (PRO_PANEL == KANJI)
  		/* ƒƒ“ƒ^ƒbƒ`‚Ì•\Ž¦‚ð[]->ŠG•¶Žš‚É•ÏX By O.Kimoto 1998/01/22 */
		List.S.Work[0] = LCD_PICFONT;
		List.S.Work[1] = LCD_PICFONT_LOWER;
		CMN_UnsignedIntToASC( &List.S.Work[2], 	/* 01`72‹L†‚ð‚Â‚­‚é */
				(UWORD)(CMN_OffsetToOnetouchCode( SYB_BatchTxFile[box].DialNumber[0].FaxNumber.Onetouch ) - 0x40),
				 2, '0' );
#endif
#endif
		break;
	default:
		break;
	}
	CMN_StringCopy(&List.S.Print[7-1], List.S.Work );
	
	/*”õl€–ÚÃÞ°À*/
	CMN_UnsignedIntToASC_NULL((UBYTE *)List.S.Work, (UWORD)(box + 1), 1, 0 );
	CMN_StringCopy(&List.S.Print[66-1], List.S.Work );
		
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	(*LineCnt)--;
	(*Line)++;

	return ( OK );
}


#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/17 By M.Kuwahara */
/*************************************************************************
	module		:[ƒvƒƒOƒ‰ƒ€ƒƒ“ƒ^ƒbƒ`“o˜^ƒ`ƒFƒbƒN]
	functiom	:[
		ƒvƒƒOƒ‰ƒ€ƒƒ“ƒ^ƒbƒ`‚É“o˜^‚³‚ê‚Ä‚¢‚éŽí—Þ‚Ìƒ`ƒFƒbƒN‚ðs‚È‚¤
		ƒ`ƒFƒbƒN‚Ìs‚È‚¢‚½‚¢Ží—Þ‚ðˆø”‚Å‚à‚ç‚¤]
	common		:[
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/08/17]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
UBYTE	ProgDataEntryCheck( 
			UBYTE	Type,
			UBYTE	ProgCnt)
{
	UBYTE	i;

	for ( i = ProgCnt; i < SYS_PROGRAM_MAX; i++ ) {
		if ( SYB_ProgramOnetouch[i].Item == Type ) {	/* ŠY“–Ží•Ê‚ª‚ ‚éŽž */
			break;
		}
	}
	return( i );
}


/*************************************************************************
	module		:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg‚Ì‚P–¾×o—ÍiŠg’£•ªj]
	functiom	:[
		ƒvƒƒOƒ‰ƒ€ƒƒ“ƒ^ƒbƒ`‚É“o˜^‚³‚ê‚Ä‚¢‚é’ÊM—\–ñˆÈŠO‚Ì‚à‚Ì‚ðo—Í
		‘Î‰žŽí•ÊFƒŠƒXƒgAŒ´e’~Ï]
	common		:[
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/08/17]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD	PrintProgExtEntry( 
				UBYTE Item,			/* “o˜^Ží•Ê */
				UBYTE *Page,		/*ƒy[ƒW*/
				UBYTE *IsChangePage,	/* Íß°¼Þ¸Û°½Þ”»•ÊÌ×¸Þ */
				register UBYTE *LineCnt )	/*ˆóŽšsˆÊ’u*/
{
	UBYTE	prog_cnt;		/* ÌßÛ¸Þ×ÑÃÞ°À”Ô† */
	UBYTE	rec_line;		/* 1–¾×‚Ì×²Ý” */
	UBYTE	page_cnt;		/* Ží•Ê–ˆ‚ÌÍß°¼Þ” */
	UBYTE	i;
	register WORD	ret;	/*ŽÀsŒ‹‰Ê*/

	page_cnt = 1;
	prog_cnt = 0;
	prog_cnt = ProgDataEntryCheck( Item, prog_cnt );	/*ŽŸÃÞ°À»°Á*/

	switch (Item) {		/* 1–¾×‚É•K—v‚È×²Ý”‚ð¾¯Ä */
	case	SYS_PROGRAM_LIST:	/* ƒŠƒXƒg */
		rec_line = 2;
		break;
	case	SYS_PROGRAM_STORE:	/* Œ´e’~Ï */
		rec_line = 4;
		break;
	}
	if (*IsChangePage == TRUE) {	/* ƒNƒ[ƒY‚³‚ê‚Ä‚¢‚È‚¢Žž */
		if (*LineCnt < (rec_line + 5) ) {	/* Žc‚ès‚ÅA‚P–¾×‚ào—Í‚Å‚«‚È‚¢Žž */
			if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
				return ( ret );
			}
			(*Page)++;
			*IsChangePage = FALSE;
		}
		else {
			*LineCnt -= 5;
		}
	}
	while ( prog_cnt != SYS_PROGRAM_MAX ) {
		if (*IsChangePage == FALSE) {	/* ƒNƒ[ƒY‚³‚ê‚Ä‚¢‚éŽž */
			if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
				return ( ret );
			}
			*LineCnt = (UBYTE)(PaperSizeLen() - 5);/*ˆóü‰Â”\s”¾¯Ä*/
			*IsChangePage = TRUE;
			if ( (ret = Print_Program_List_Head_Ext( 0, *Page, Item ) ) != OK ) {/*Œ©o‚µˆóü*/
				return ( ret );
			}
		}
		if (page_cnt == 1) {	/* æ“ªŽž‚Ì‚Ý */
			if ( (ret = Print_Program_List_Head_Ext( 1, *Page, Item ) ) != OK ) {/*Í¯ÀÞˆóü*/
				return ( ret );
			}
			page_cnt = 1;
		}

		for ( i = 0;; i++ ) {
			if (*LineCnt < rec_line ) {	/* Íß°¼ÞI—¹‚ÌŽž */
				break;
			}
			switch (Item) {
			case	SYS_PROGRAM_LIST:		/* ƒŠƒXƒg‚ÌŽž */
				if ( (ret = Print_ProgEntryList_Specifi( page_cnt ,i, prog_cnt) ) != OK ) {	/*1–¾×ˆóü*/
					return ( ret );
				}
				break;
			case	SYS_PROGRAM_STORE:		/* Œ´e’~Ï‚ÌŽž */
				if ( (ret = Print_ProgEntryStore_Specifi( page_cnt ,i, prog_cnt) ) != OK ) {	/*1–¾×ˆóü*/
					return ( ret );
				}
				break;
			}
			
			(*LineCnt) -= rec_line;
			prog_cnt++;
			prog_cnt = ProgDataEntryCheck( Item, prog_cnt );	/*ŽŸÃÞ°À»°Á*/
			if ( prog_cnt == SYS_PROGRAM_MAX ) {
				break;
			}
		}
		if ( (ret = Print_Program_List_Head_Ext( 2, *Page, Item )) != OK ) {	/*Ì¯Àˆóü*/
			return ( ret );
		}
#if (0)
		if ( prog_cnt != SYS_PROGRAM_MAX ) {		/* ƒf[ƒ^‘¶ÝŽž */
			prog_cnt = ProgDataEntryCheck( SYS_PROGRAM_LIST, prog_cnt );	/*ŽŸÃÞ°À»°Á*/
		}
#endif
		if ((*LineCnt - rec_line) < rec_line ) {	/* Íß°¼ÞI—¹‚ÌŽž */
			if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
				return ( ret );
			}
			*IsChangePage = FALSE;
			(*Page)++;
			page_cnt++;
		}
	}
	return ( OK );
}


/*************************************************************************
	module		:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒgƒwƒbƒ_ˆóüiŠg’£”Å—pj]
	functiom	:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
	common		:[
		List:
	]
	condition	:[
		Í¯ÀÞŽí—Þ
		,	0->Íß°¼Þæ“ªŒ©o‚µ
		,	1->Íß°¼Þ´ÝÄÞŒ©o‚µ
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/08/18]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD				Print_Program_List_Head_Ext(
						 UBYTE Category,	/*ƒwƒbƒ_Ží—Þ*/
						 UBYTE Page,		/*ƒy[ƒW*/
						 UBYTE Item)		/*“o˜^Ží•Ê*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	switch (Category) {
	case	0:		/* Œ©o‚µ */
		if ( Page == 1 ) {
			/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs{Œ©o‚µ{‚P‰üs*/
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			if ( (ret = Print_Head1_Common( PWRD_ProgOnetouchDir_K, 
							LST_NOT,10-1 )) != OK ) {
				return ( ret );
			}
#else
			if ( (ret = Print_Head1_Common( PWRD_ProgOnetouchDir,
						  	LST_XXX_TWI_XXX, 11-1 )) != OK ) { /* 20->11 For ANZU By H.Hirao 1996/02/07 */
				return ( ret );
			}
#endif

			/*Page Œ»ÝŽžŠÔ*/
			if ( (ret = PageTimePrint( Page, 2-1, 60-1 )) != OK ) {
				return ( ret );
			}

		}
		else {
			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
			/* Page */
			if ( (ret = PagePrint( Page, 2-1 )) != OK ) {
				return ( ret );
			}
		}
		break;
	case	1:	/* ƒwƒbƒ_ */
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		switch (Item) {
		case	SYS_PROGRAM_COMMAND:	/* ’ÊM—\–ñ */
			/* "’ÊM—\–ñ" */
			AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_CommReserved, LST_NOT );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†®†¢†Î†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢†¢†²*/
			Print_Program_List_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤ NO.†¤ÀÞ²ÔÙ”Ô††¤Žw’è“úŽž†¤‰ž—p‹@”\†¤”õlb*/
			Print_Program_List_Line( 1, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			break;
		case	SYS_PROGRAM_LIST:	/* ƒŠƒXƒg */
			/* "ƒŠƒXƒg" */
			AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_List, LST_NOT );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†®†¢†Î†¢†Î†¢†¢†Î†¢†¢†¢†¢†²*/
			Print_Program_List_Line( 10, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤ NO.†¤    Ø½Ä–¼       †¤*/
			Print_Program_List_Line( 11, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			break;
		case	SYS_PROGRAM_STORE:	/* Œ´e’~Ï */
			/* "Œ´e’~Ï" */
			AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_DocStore, LST_NOT );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†®†¢†Î†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢†¢†²*/
			Print_Program_List_Line( 15, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤ NO.†¤  ÎÞ¯¸½–¼    †¤ã‘‚«  †¤*/
			Print_Program_List_Line( 16, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			break;
		}
		break;
	case	2:	/* ƒtƒbƒ^iƒVƒ“ƒOƒ‹ƒL[–¢o—Íj */
		/*†¶†¢†Ö†¢†Ö†¢†¢†Ö†¢†¢†¢†Ö†¢†¢†º*/
		switch (Item) {
		case	SYS_PROGRAM_COMMAND:	/* ’ÊM—\–ñ */
			Print_Program_List_Line( 4, List.S.Print, List.S.Attribute );
			break;
		case	SYS_PROGRAM_LIST:	/* ƒŠƒXƒg */
			Print_Program_List_Line( 14, List.S.Print, List.S.Attribute );
			break;
		case	SYS_PROGRAM_STORE:	/* Œ´e’~Ï */
			Print_Program_List_Line( 21, List.S.Print, List.S.Attribute );
			break;
		}
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		break;
	case	3:	/* ƒtƒbƒ^iƒVƒ“ƒOƒ‹ƒL[o—ÍÏj */
		/*†¶†¢†Ö†¢†Ö†¢†¢†Ö†¢†¢†¢†Ö†¢†¢†º*/
		switch (Item) {
		case	SYS_PROGRAM_COMMAND:	/* ’ÊM—\–ñ */
			Print_Program_List_Line( 7, List.S.Print, List.S.Attribute );
			break;
		case	SYS_PROGRAM_LIST:	/* ƒŠƒXƒg */
			Print_Program_List_Line( 14, List.S.Print, List.S.Attribute );
			break;
		case	SYS_PROGRAM_STORE:	/* Œ´e’~Ï */
			Print_Program_List_Line( 21, List.S.Print, List.S.Attribute );
			break;
		}
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		break;
	}
	return ( OK );
}


/*************************************************************************
	module		:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg‚Ì‚P–¾×ˆóüiƒŠƒXƒg)]
	functiom	:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg‚É“o˜^‚³‚ê‚Ä‚¢‚éƒŠƒXƒg–¾×‚ðˆóü‚·‚éB]
	common		:[
	]
	condition	:[
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/08/18]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD		Print_ProgEntryList_Specifi(
						 UBYTE Page,		/*ƒy[ƒW*/
						 UBYTE Line,		/*Œ»Ý–¾×”*/
						 UBYTE ProgCnt )	/*ƒƒ“ƒ^ƒbƒ`”Ô†*/
{
	register WORD	ret;						/*ŽÀsŒ‹‰Ê*/

	if ( Page > 1 && Line == 0 ) {
		/* „¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢ */
		Print_Program_List_Line( 10, List.S.Print, List.S.Attribute );
		if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	else {
		/* „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§ */
		Print_Program_List_Line( 12, List.S.Print, List.S.Attribute );
		if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}

	/* „ ™99„ xxxxxxxxxxxxxxxxxxxxxx„  */
	Print_Program_List_Line( 13, List.S.Print, List.S.Attribute );
	/* No. */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || defined(HINOKI3)	/* by K.Watanabe 2004/10/22 */
	/* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†P1`P12‚ð‚Â‚­‚é */
	List.S.Print[2-1] = 0x50;	/* 'P'‚ÌASCIIº-ÄÞ */
	CMN_UnsignedIntToASC( &List.S.Print[3-1], ProgCnt+1, 0, '0' );
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_PANEL == ANK)
	List.S.Print[2-1] = '[';
	List.S.Print[5-1] = ']';
/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
  #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add By H.Fujimura 1998/11/12 */
	CMN_UnsignedIntToASC( &List.S.Print[3-1], ProgCnt+25, 0, '0' );	/* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†[25]`[30]‚ð‚Â‚­‚é */
  #else
	CMN_UnsignedIntToASC( &List.S.Print[3-1], ProgCnt+73, 0, '0' );	/* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†[73]`[80]‚ð‚Â‚­‚é */
  #endif
 #endif
 #if (PRO_PANEL == KANJI)
	/* ƒƒ“ƒ^ƒbƒ`‚Ì•\Ž¦‚ð[]->ŠG•¶Žš‚É•ÏX By O.Kimoto 1998/01/22 */
	/* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†™73`™80‚ð‚Â‚­‚é */
	List.S.Print[2-1] = LCD_PICFONT+3;
	List.S.Print[3-1] = LCD_PICFONT_LOWER;
 #if (PRO_KEYPANEL == PANEL_POPLAR_H)	/* 1998/07/16 By M.Kuwahara */
	CMN_UnsignedIntToASC( &List.S.Print[4-1], ProgCnt+73, 0, '0' );
 #endif
 #if (PRO_KEYPANEL == PANEL_SAKAKI)
	/* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†™25`™30‚ð‚Â‚­‚é */
	CMN_UnsignedIntToASC( &List.S.Print[4-1], ProgCnt+25, 0, '0' );
 #endif
 #endif
#endif
	/* ƒŠƒXƒg–¼ */
	CMN_StringCopy( &List.S.Print[7-1], EntryListWordingSet(SYB_ProgramOnetouch[ProgCnt].EntryData.ListItem) );

	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	return( OK );
}


/*************************************************************************
	module		:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg‚Ì‚P–¾×ˆóüiŒ´e’~Ï)]
	functiom	:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg‚É“o˜^‚³‚ê‚Ä‚¢‚éŒ´e’~Ï–¾×‚ðˆóü‚·‚éB]
	common		:[
	]
	condition	:[
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/08/19]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD		Print_ProgEntryStore_Specifi(
						 UBYTE Page,		/*ƒy[ƒW*/
						 UBYTE Line,		/*Œ»Ý–¾×”*/
						 UBYTE ProgCnt )	/*ƒƒ“ƒ^ƒbƒ`”Ô†*/
{
	UBYTE	chk_prog_cnt;
	register WORD	ret;						/*ŽÀsŒ‹‰Ê*/

	if ( Page > 1 && Line == 0 ) {
		/* „¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢ */
		Print_Program_List_Line( 15, List.S.Print, List.S.Attribute );
		if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	else {
		if (ProgCnt == ProgDataEntryCheck( SYS_PROGRAM_STORE, 0 )) {	/* ‚PŒ–Ú‚Ìƒf[ƒ^‚©ƒ`ƒFƒbƒN */
			/* „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§ */
			Print_Program_List_Line( 17, List.S.Print, List.S.Attribute );
		}
		else {
			/* „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§ */
			Print_Program_List_Line( 22, List.S.Print, List.S.Attribute );
		}
		if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}

	/* „ [99]„ xxxxxxx„ 99:xxxxxxxxxxxxxxxx„ XXX         „  */
	Print_Program_List_Line( 18, List.S.Print, List.S.Attribute );
	/* No. */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || defined(HINOKI3)	/* by K.Watanabe 2004/10/22 */
	/* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†P1`P12‚ð‚Â‚­‚é */
	List.S.Print[2-1] = 0x50;	/* 'P'‚ÌASCIIº-ÄÞ */
	CMN_UnsignedIntToASC( &List.S.Print[3-1], ProgCnt+1, 0, '0' );
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_PANEL == ANK)
	List.S.Print[2-1] = '[';
	List.S.Print[5-1] = ']';
/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
  #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add By H.Fujimura 1998/11/12 */
	CMN_UnsignedIntToASC( &List.S.Print[3-1], ProgCnt+25, 0, '0' );	/* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†[25]`[30]‚ð‚Â‚­‚é */
  #else
	CMN_UnsignedIntToASC( &List.S.Print[3-1], ProgCnt+73, 0, '0' );	/* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†[73]`[80]‚ð‚Â‚­‚é */
  #endif
 #endif
 #if (PRO_PANEL == KANJI)
	/* ƒƒ“ƒ^ƒbƒ`‚Ì•\Ž¦‚ð[]->ŠG•¶Žš‚É•ÏX By O.Kimoto 1998/01/22 */
	/* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†™73`™80‚ð‚Â‚­‚é */
	List.S.Print[2-1] = LCD_PICFONT+3;
	List.S.Print[3-1] = LCD_PICFONT_LOWER;
 #if (PRO_KEYPANEL == PANEL_POPLAR_H)	/* 1998/07/16 By M.Kuwahara */
	CMN_UnsignedIntToASC( &List.S.Print[4-1], ProgCnt+73, 0, '0' );
 #endif
 #if (PRO_KEYPANEL == PANEL_SAKAKI)
	/* ÌßÛ¸Þ×ÑÜÝÀ¯Á‹L†™25`™30‚ð‚Â‚­‚é */
	CMN_UnsignedIntToASC( &List.S.Print[4-1], ProgCnt+25, 0, '0' );
 #endif
 #endif
#endif
	/* Ží•ÊEÎÞ¯¸½–¼ */
	switch (SYB_ProgramOnetouch[ProgCnt].EntryData.StoreData.Item) {
	case	MSG_STORE_POLLING_DOC:		/* ƒ|[ƒŠƒ“ƒOŒ´e */
		CMN_StringCopy( &List.S.Print[7-1], PWRD_Polling );
		break;
	case	MSG_STORE_DBPOLLING_DOC:	/* ŒŸõƒ|[ƒŠƒ“ƒOŒ´e */
		CMN_StringCopy( &List.S.Print[7-1], PWRD_DbPolling );
		CMN_UnsignedIntToASC( &List.S.Print[15-1], SYB_ProgramOnetouch[ProgCnt].EntryData.StoreData.Point, 2, ' ' );
		break;
	case	MSG_STORE_FCODE_BOX_DOC:	/* ‚eƒR[ƒh‚a‚n‚wŒ´e */
		CMN_StringCopy( &List.S.Print[7-1], PWRD_SUB_Rx );
#if 0 /* Box ”Ô†‚ª‚P¬‚³‚¢‚Ì‚ÅC³B Changed by H.Kubo 1998/12/28 */
@@		CMN_UnsignedIntToASC( &List.S.Print[15-1], SYB_ProgramOnetouch[ProgCnt].EntryData.StoreData.Point, 2, ' ' );
#else
		CMN_UnsignedIntToASC( &List.S.Print[15-1], SYB_ProgramOnetouch[ProgCnt].EntryData.StoreData.Point + 1, 2, ' ' );
#endif
		List.S.Print[17-1] = ':';
		CMN_StringCopy( &List.S.Print[18-1], SYB_SubAddressBoxTable[SYB_ProgramOnetouch[ProgCnt].EntryData.StoreData.Point].BoxName );
		if (SYB_ProgramOnetouch[ProgCnt].EntryData.StoreData.AddType == SUB_ADDRESS_OPTION_DOC_ADD) {
			CMN_StringCopy( &List.S.Print[35-1], PWRD_On );
		}
		else {
			CMN_StringCopy( &List.S.Print[35-1], PWRD_Off );
		}
		break;
	default:
			CMN_StringCopy( &List.S.Print[35-1], (UBYTE *)"ERROR" );
	}
	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/* ’ÊMÓ°ÄÞE”Z“xEÏ½ÀÝÌßEÒÓØ‘—ME’ÊMØ */
#if 0 /* changed by H.Kubo 1999/01/06 */
	if (( ret = EntrySingleKeySpecifi( ProgCnt, 0, SYS_PROGRAM_STORE )) != OK ) {
		return( ret );
	}
#else
	if (( ret = EntrySingleKeySpecifi( ProgCnt, &Line, SYS_PROGRAM_STORE )) != OK ) {
		return( ret );
	}
#endif
	return( OK );
}


/*************************************************************************
	module		:[’ÊM—\–ñ^Œ´e’~ÏŽž‚ÌˆêŽžƒL[‚Ìo—Í]
	functiom	:[
			so—Í€–Út
				E’ÊM—\–ñ
					’ÊMƒ‚[ƒh
					—DæŒ´e”Z“x
					ÏƒXƒ^ƒ“ƒv
					ƒƒ‚ƒŠ‘—M
					’ÊMØ
				EˆêŠ‡‘—M
					’ÊMƒ‚[ƒh
					—DæŒ´e”Z“x
				EŒ´e’~Ï
					’ÊMƒ‚[ƒh
					—DæŒ´e”Z“x
			]
	common		:[
	]
	condition	:[
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/08/19]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD	EntrySingleKeySpecifi( 
				UBYTE	ProgCnt,
				/* UBYTE	LineCnt, */
				UBYTE	*line_count_ptr, /* s”‚ª‘«‚ç‚È‚¢ƒoƒO‚Ì‘ÎôB changed by H.Kubo 1999/01/06 */
				UBYTE	Item)
{
	UBYTE LineCnt;
	register WORD	ret;						/*ŽÀsŒ‹‰Ê*/

	if (line_count_ptr != NULL) {
		LineCnt = *line_count_ptr; /* s”‚ª‘«‚ç‚È‚¢ƒoƒO‚Ì‘ÎôB added by H.Kubo 1999/01/06 */
	}
	else { /* ‚ ‚Á‚Ä‚Í‚È‚ç‚È‚¢‚¯‚ÇAˆÀ‘S‚Ì‚½‚ß“ü‚ê‚Ü‚·B */
		line_count_ptr = &LineCnt;
		LineCnt = 0xff;
	}
	
	/* „     „ ’ÊMÓ°ÄÞ:          ”Z“x:         Ï½ÀÝÌß             „  */
	if (Item == SYS_PROGRAM_COMMAND) {	/* ’ÊM—\–ñ */
#if (PRO_EXT_P_ONETOUCH == ENABLE) && (PRO_PANEL == KANJI) /* ƒ|[ƒŠƒ“ƒOŽóM‚ÌˆóŽš‚Å‚ÍAƒL[ó‘Ô‚ð•\Ž¦‚µ‚È‚¢‚½‚ß‚ÌC³B Changed by H.Kubo 1999/01/06 */
		switch (SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.Item) {
		case SYS_POLLING_RX:
		case SYS_DB_POLLING_RX:
		case SYS_SEQUENTIAL_POLLING:
		case SYS_CONTINUOUS_POLLING_RX:
		case SYS_SELECT_POLLING_RX:
			/* Ý’è‚ª–³‚¢‚Ì‚Å•\Ž¦‚µ‚Ü‚¹‚ñB*/
			return OK;
			break;
		default:
			break;
		}
#else
		if (LineCnt == ((UBYTE)(PaperSizeLen() - 4))) {	/* Íß°¼Þ‚Ìæ“ªs‚ÌŽž */
			/* „¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¢ */
			Print_Program_List_Line( 9, List.S.Print, List.S.Attribute );
		}
		else {
			/* „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§ */
			Print_Program_List_Line( 5, List.S.Print, List.S.Attribute );
		}
		if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*line_count_ptr)--; /* s”‚ª‘«‚ç‚È‚¢ƒoƒO‚Ì‘ÎôBadded by H.Kubo 1999/01/06 */
#endif
		Print_Program_List_Line( 6, List.S.Print, List.S.Attribute );
	}
	else {								/* Œ´e’~Ï */
		/* „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§ */
		Print_Program_List_Line( 19, List.S.Print, List.S.Attribute );
		if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		(*line_count_ptr)--; /* s”‚ª‘«‚ç‚È‚¢ƒoƒO‚Ì‘ÎôBadded by H.Kubo 1999/01/06 */
		Print_Program_List_Line( 20, List.S.Print, List.S.Attribute );
	}

	/** ’ÊMÓ°ÄÞ */
	CMN_StringCopy( &List.S.Print[7-1], PWRD_CommMode );
	List.S.Print[22-1] = ':';
	if (SYB_ProgramOnetouch[ProgCnt].TxModeSW == 0xFF) {
		CMN_StringCopy( &List.S.Print[23-1], (UBYTE *)"-----" );
	}
	else {
		CommunicationModeName( 
				SYB_ProgramOnetouch[ProgCnt].TxModeSW, 
				&List.S.Print[23-1], 
				&List.S.Attribute[23-1] );
	}
	/** ”Z“x */
	CMN_StringCopy( &List.S.Print[32-1], PWRD_Contrast );
	List.S.Print[47-1] = ':';
	switch (SYB_ProgramOnetouch[ProgCnt].ContrastSW) {
	case	SYS_DARK_DENSITY:	/* ”Z‚­ */
		CMN_StringCopy( &List.S.Print[48-1], PWRD_Dark );
		break;
	case	SYS_NORMAL_DENSITY:	/* •’Ê */
		CMN_StringCopy( &List.S.Print[48-1], PWRD_NormalDark );
		break;
	case	SYS_LIGHT_DENSITY:	/* ”–‚­ */
		CMN_StringCopy( &List.S.Print[48-1], PWRD_Light );
		break;
	default:
		CMN_StringCopy( &List.S.Print[48-1], (UBYTE *)"-----" );
		break;
	}

	if (Item == SYS_PROGRAM_COMMAND) {	/* ’ÊM—\–ñ */
#if (PRO_PANEL == ANK)/* Add By H.Fujimura 1998/12/28 */
 #if !defined(KEISATSU) /* ŒxŽ@FAX Added by SMuratec ‰Ä 2005/08/24 */
		/** Ï½ÀÝÌß */
		CMN_StringCopy( &List.S.Print[57-1], PWRD_Stamp );
		List.S.Print[72-1] = ':';
		switch (SYB_ProgramOnetouch[ProgCnt].StampSW) {
		case	SYS_STAMP_ON:	/* Ï½ÀÝÌß‚n‚m */
			CMN_StringCopy( &List.S.Print[73-1], PWRD_On );
			break;
		case	0:				/* Ï½ÀÝÌß‚n‚e‚e */
			CMN_StringCopy( &List.S.Print[73-1], PWRD_Off );
			break;
		default:
			CMN_StringCopy( &List.S.Print[73-1], (UBYTE *)"-----" );
			break;
		}
 #endif
 		if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		/* „     „ ÒÓØ‘—M:          ’ÊMØ:                         „  */
		if (Item == SYS_PROGRAM_COMMAND) {	/* ’ÊM—\–ñ */
			Print_Program_List_Line( 6, List.S.Print, List.S.Attribute );
		}
		else {								/* Œ´e’~Ï */
			Print_Program_List_Line( 20, List.S.Print, List.S.Attribute );
		}
		/** ÒÓØ‘—M */
		CMN_StringCopy( &List.S.Print[7-1], PWRD_MemoryTx );
		List.S.Print[22-1] = ':';
		switch (SYB_ProgramOnetouch[ProgCnt].MemoryTxSW) {
		case	SYS_MEMORY_TX_ON:	/* ƒƒ‚ƒŠ‘—M‚n‚m */
			CMN_StringCopy( &List.S.Print[23-1], PWRD_On );
			break;
		case	0:				/* ƒƒ‚ƒŠ‘—M‚n‚e‚e */
			CMN_StringCopy( &List.S.Print[23-1], PWRD_Off );
			break;
		default:
			CMN_StringCopy( &List.S.Print[23-1], (UBYTE *)"-----" );
			break;
		}
		/** ’ÊMØ */
		CMN_StringCopy( &List.S.Print[32-1], PWRD_ConfReport );
		List.S.Print[47-1] = ':';
		switch (SYB_ProgramOnetouch[ProgCnt].ConfirmSW) {
		case	TCR_REQUEST:	/* ‘—MØ */
			CMN_StringCopy( &List.S.Print[48-1], PWRD_TxConf );
			break;
		case	RCR_REQUEST:	/* Žó—ÌØ */
			CMN_StringCopy( &List.S.Print[48-1], PWRD_RxConf );
			break;
		case	NO_CONFIRMATION_REPORT:	/* ‚n‚e‚e */
			CMN_StringCopy( &List.S.Print[48-1], PWRD_Off );
			break;
		default:
			CMN_StringCopy( &List.S.Print[48-1], (UBYTE *)"-----" );
			break;
		}
#else
		/* ÏƒXƒ^ƒ“ƒv‚ª–³‚¢’ÊM‚Å‚àÏƒXƒ^ƒ“ƒvÝ’è‚Ì•\Ž¦‚ªo‚é‚Ì‚ÅAC³‚µ‚Ü‚·BChanged by H.Kubo 1999/01/06 */
		switch (SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.Item) {
		case SYS_POLLING_RX:
		case SYS_DB_POLLING_RX:
		case SYS_SEQUENTIAL_POLLING:
		case SYS_CONTINUOUS_POLLING_RX:
		case SYS_SELECT_POLLING_RX:
			/* ÏƒXƒ^ƒ“ƒvÝ’è‚ª–³‚¢‚Ì‚Å•\Ž¦‚µ‚Ü‚¹‚ñB*/
			break;
		default:
			/* ÏƒXƒ^ƒ“ƒv‚ÍˆêŠ‡‘—M‚Å‚à•\Ž¦‚µ‚Ü‚·B Changed by H.Kubo 1999/01/06 */
			/** Ï½ÀÝÌß */
			CMN_StringCopy( &List.S.Print[57-1], PWRD_Stamp );
			List.S.Print[72-1] = ':';
			switch (SYB_ProgramOnetouch[ProgCnt].StampSW) {
			case	SYS_STAMP_ON:	/* Ï½ÀÝÌß‚n‚m */
				CMN_StringCopy( &List.S.Print[73-1], PWRD_On );
				break;
			case	0:				/* Ï½ÀÝÌß‚n‚e‚e */
				CMN_StringCopy( &List.S.Print[73-1], PWRD_Off );
				break;
			default:
				CMN_StringCopy( &List.S.Print[73-1], (UBYTE *)"-----" );
				break;
			}
			break;
		}

		/* ƒƒ‚ƒŠ‘—MA’ÊMØÝ’è‚ª–³‚¢’ÊM‚Å‚à•\Ž¦‚ªo‚é‚Ì‚ÅAC³‚µ‚Ü‚·BChanged by H.Kubo 1999/01/06 */
		switch (SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.Item) {
		case SYS_POLLING_RX:
		case SYS_DB_POLLING_RX:
		case SYS_SEQUENTIAL_POLLING:
		case SYS_CONTINUOUS_POLLING_RX:
		case SYS_SELECT_POLLING_RX:
		case SYS_BATCH_MEMORY_TX:
			/* ƒƒ‚ƒŠ‘—MA’ÊMØÝ’è‚Í‚È‚¢‚Ì‚Å•\Ž¦‚µ‚Ü‚¹‚ñB */
			break;
		default:
#if 0 /* ÏƒXƒ^ƒ“ƒv‚ÍˆêŠ‡‘—M‚Å‚à•\Ž¦‚µ‚Ü‚·B Changed by H.Kubo 1999/01/06 */
@		if (SYB_ProgramOnetouch[ProgCnt].EntryData.Command.Option.Item != SYS_BATCH_MEMORY_TX) {	/* ˆêŠ‡‘—MˆÈŠO */
@			/** Ï½ÀÝÌß */
@			CMN_StringCopy( &List.S.Print[57-1], PWRD_Stamp );
@			List.S.Print[72-1] = ':';
@			switch (SYB_ProgramOnetouch[ProgCnt].StampSW) {
@			case	SYS_STAMP_ON:	/* Ï½ÀÝÌß‚n‚m */
@				CMN_StringCopy( &List.S.Print[73-1], PWRD_On );
@				break;
@			case	0:				/* Ï½ÀÝÌß‚n‚e‚e */
@				CMN_StringCopy( &List.S.Print[73-1], PWRD_Off );
@				break;
@			default:
@				CMN_StringCopy( &List.S.Print[73-1], (UBYTE *)"-----" );
@				break;
@			}
#endif
			if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			(*line_count_ptr)--; /* s”‚ª‘«‚ç‚È‚¢ƒoƒO‚Ì‘ÎôBadded by H.Kubo 1999/01/06 */

			/* „     „ ÒÓØ‘—M:          ’ÊMØ:                         „  */
			if (Item == SYS_PROGRAM_COMMAND) {	/* ’ÊM—\–ñ */
				Print_Program_List_Line( 6, List.S.Print, List.S.Attribute );
			}
			else {								/* Œ´e’~Ï */
				Print_Program_List_Line( 20, List.S.Print, List.S.Attribute );
			}
			/** ÒÓØ‘—M */
			CMN_StringCopy( &List.S.Print[7-1], PWRD_MemoryTx );
			List.S.Print[22-1] = ':';
			switch (SYB_ProgramOnetouch[ProgCnt].MemoryTxSW) {
			case	SYS_MEMORY_TX_ON:	/* ƒƒ‚ƒŠ‘—M‚n‚m */
				CMN_StringCopy( &List.S.Print[23-1], PWRD_On );
				break;
			case	0:				/* ƒƒ‚ƒŠ‘—M‚n‚e‚e */
				CMN_StringCopy( &List.S.Print[23-1], PWRD_Off );
				break;
			default:
				CMN_StringCopy( &List.S.Print[23-1], (UBYTE *)"-----" );
				break;
			}
			/** ’ÊMØ */
			CMN_StringCopy( &List.S.Print[32-1], PWRD_ConfReport );
			List.S.Print[47-1] = ':';
			switch (SYB_ProgramOnetouch[ProgCnt].ConfirmSW) {
#if (0)	/* 1998/10/12 By M.Kuwahara */
//			case	TCR_REQUEST:	/* ‘—MØ */
//				CMN_StringCopy( &List.S.Print[48-1], PWRD_TxConf );
//				break;
//			case	RCR_REQUEST:	/* Žó—ÌØ */
//				CMN_StringCopy( &List.S.Print[48-1], PWRD_RxConf );
//				break;
#endif
			case	TCR_REQUEST:	/* ‘—MØ */
			case	RCR_REQUEST:	/* Žó—ÌØ */
				CMN_StringCopy( &List.S.Print[48-1], PWRD_On );
				break;
			case	NO_CONFIRMATION_REPORT:	/* ‚n‚e‚e */
				CMN_StringCopy( &List.S.Print[48-1], PWRD_Off );
				break;
			default:
				CMN_StringCopy( &List.S.Print[48-1], (UBYTE *)"-----" );
				break;
			}
		}
#endif
	}

	if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	(*line_count_ptr)--; /* s”‚ª‘«‚ç‚È‚¢ƒoƒO‚Ì‘ÎôBadded by H.Kubo 1999/01/06 */
	return (OK);
}


/*************************************************************************
	module		:[ƒvƒƒOƒ‰ƒ€ƒŠƒXƒg‚Éo—Í‚·‚éƒ[ƒfƒBƒ“ƒOƒ|ƒCƒ“ƒ^‚ð“¾‚é]
	functiom	:[
			]
	common		:[
	]
	condition	:[
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/08/19]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
UBYTE	*EntryListWordingSet(
				UBYTE	ListItem )	/* ƒŠƒXƒgŽí•Ê */
{
    UBYTE  *word_p;

	switch (ListItem) {
	case LST_ONETOUCHDIAL_LIST:		/* ÜÝÀ¯ÁÀÞ²ÔÙØ½Ä·°      	*/
		word_p = PWRD_PRG_Onetouch;
		break;
	case LST_SPEEDDIAL_LIST:		/* ’ZkÀÞ²ÔÙØ½Ä·°       	*/
		word_p = PWRD_PRG_Speed;
		break;
	case LST_PROGRAM_LIST:  		/* PÜÝÀ¯ÁÀÞ²ÔÙØ½Ä·°			*/
		word_p = PWRD_PRG_Program;
		break;
	case LST_MAILBOX_LIST:  		/* e“WŽÒØ½Ä·°				*/
		word_p = PWRD_PRG_SecureBox;
		break;
	case LST_RESERVECMD_LIST:    	/* ’ÊM—\–ñØ½Ä·°			*/
		word_p = PWRD_PRG_ComReserve;
		break;
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
	case LST_JOURNAL_LIST:   		/* ‘S’ÊMŠÇ—‹L˜^			*/
		word_p = PWRD_PRG_Journal;
		break;
	case LST_DAILY_REPORT:			/* ’ÊMŠÇ—‹L˜^“ú•ñ			*/
		word_p = PWRD_PRG_DailyReport;
		break;
#else
	case LST_JOURNAL_LIST:   		/* ’ÊMŠÇ—ÚÎß°Ä·°			*/
		word_p = PWRD_PRG_Journal;
		break;
#endif
	case LST_GROUP_LIST:  	  		/* ¸ÞÙ°ÌßØ½Ä·°				*/
		word_p = PWRD_PRG_Group;
		break;
	case LST_PARAMETER_LIST: 	   	/* ‹@ŠíÝ’èØ½Ä·°			*/
		word_p = PWRD_PRG_Setting;
		break;
	case LST_COVERPAGE_LIST:    	/* Ò¯¾°¼ÞØ½Ä·°				*/
		word_p = PWRD_PRG_Message;
		break;
	case LST_COSTTABLE_LIST:    	/* —¿‹à•\Ø½Ä·°				*/
		word_p = PWRD_PRG_CostBase;
		break;
#if (PRO_DEPART_NEW_LIST == ENABLE)	/* Add By H.Fujimura 1998/12/22 */
	case LST_DEPARTMANAGE_LIST:		/* ŠÈˆÕ—¿‹àŠÇ—Ø½Ä·°		*/
#else
	case LST_DEPARTDATACODE_LIST:	/* •”–åŠÇ—Ø½Ä·°			*/
#endif
		word_p = PWRD_PRG_DepartCode;
		break;
	case LST_BATCHTXBOX_LIST:		/* ˆêŠ‡‘—MBOXØ½Ä·°			*/
		word_p = PWRD_PRG_BatchBox;
		break;
	case LST_BATCHTXDOC_LIST:   	/* ˆêŠ‡‘—MŒ´eØ½Ä·°		*/
		word_p = PWRD_PRG_BatchDoc;
		break;
	case LST_F_CODE_BOX_LIST:    	/* Fº°ÄÞBOXØ½Ä·°			*/
		word_p = PWRD_PRG_F_CodeBox;
		break;
	case LST_F_CODE_DOC_LIST:    	/* Fº°ÄÞBOX’~ÏØ½Ä·°		*/
		word_p = PWRD_PRG_F_CodeDoc;
		break;
	case LST_BLOCK_JUNK_LIST:	    /* ÀÞ²Ú¸ÄÒ°Ù–hŽ~ÀÞ²ÔÙØ½Ä·°	*/
		word_p = PWRD_PRG_BlockJunk;
		break;
#if (PRO_NUMBER_DISPLAY == ENABLE)
	case LST_ND_LIST:    			/* ÅÝÊÞ°ÃÞ¨½ÌßÚ²ÀÞ²ÔÙØ½Ä·°	*/
		word_p = PWRD_PRG_ND_Dial;
		break;
	case LST_INF_ND_LIST:    		/* ÅÝÊÞ°ÃÞ¨½ÌßÚ²—š—ðÚÎß°Ä·°	*/
		word_p = PWRD_PRG_ND_Journal;
		break;
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)
	case LST_WARP_LIST:    			/* Ü°Ìß‹@”\Ø½Ä·°			*/
		word_p = PWRD_PRG_Warp;
		break;
#endif
#if defined(SAKAKI) && defined(JP0) /* 2002/08/26 By M.Maeda */
	case LST_JOURNAL_TX_LIST:		/* ’ÊMŠÇ—ƒŒƒ|[ƒg		*/
		word_p = PWRD_PRG_JournalTx;
		break;
	case LST_JOURNAL_RX_LIST:		/* ’ÊMŠÇ—ƒŒƒ|[ƒg		*/
		word_p = PWRD_PRG_JournalRx;
		break;
#endif
	default:
		break;
	}

    return(word_p);
}

#if (PRO_PANEL == KANJI) /* added by H.Kubo 1999/01/06 */
/*************************************************************************
	module		:[’ÊM—\–ñ^Œ´e’~ÏŽž‚ÌˆêŽžƒL[‚Ìã•”‚ÌŒrü]
	functiom	:[
			]
	common		:[
	]
	condition	:[
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[99/01/06]
	author		:[‹v•Û”Ž]
*************************************************************************/
WORD	EntrySingleKeySeparatorSpecifi(
				UBYTE	ProgCnt,
				UBYTE	NextProgCnt,
				UBYTE	LineCnt,
				UBYTE	is_next_separator_exists,
				UBYTE	Item)
{
	UBYTE 		separator;

	/* „     „ ’ÊMÓ°ÄÞ:          ”Z“x:         Ï½ÀÝÌß             „  */
	if (Item == SYS_PROGRAM_COMMAND) {	/* ’ÊM—\–ñ */
		if (LineCnt == ((UBYTE)(PaperSizeLen() - 4))) {	/* Íß°¼Þ‚Ìæ“ªs‚ÌŽž */
			if (NextProgCnt < SYS_PROGRAM_MAX) { /* added by H.Kubo 1999/01/07 */
					/*„¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„¢ */
				separator = 0;
			}
			else {
				return OK; /* ‰½‚à•\Ž¦‚µ‚È‚¢ by H.Kubo 1999/01/07 */
			}
		}
		else {
			if (is_next_separator_exists) {
				if (NextProgCnt < SYS_PROGRAM_MAX) {
					/*„¥„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„§ */
					separator = 23;
				}
				else {
					/*„¤„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„£ */
					separator = 24;
				}
			}
			else {
				/* „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§ */
				separator = 5;
			}
		}
	}
	else {								/* Œ´e’~Ï */
		/* „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„§ */
		separator = 19;
	}
	Print_Program_List_Line( separator, List.S.Print, List.S.Attribute );
	return CharacterPrint( LST_PRINT );
}

/*************************************************************************
	module		:[’ÊM—\–ñ^Œ´e’~Ï‚Ìã•”‚ÌŒrü]
	functiom	:[
			]
	common		:[
	]
	condition	:[
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[99/01/06]
	author		:[‹v•Û”Ž]
*************************************************************************/
WORD		PrintProgramBatchLineSeparator(
						 UBYTE Page,		/*ƒy[ƒW*/
						 UBYTE *Line,		/*Œ»Ý–¾×”*/
						 register UBYTE *LineCnt )	/*ˆóŽšsˆÊ’u*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/
	UBYTE	page_line;		/* ‚PÍß°¼Þ‚Ìs” */

	/* Œrü */
	if (Page > 1) {		/* 97/09/03 By M.Kuwahara */
		if (*LineCnt == (PaperSizeLen() - 4)) {
			/*†®†¢†Î†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢†¢†²*/
			Print_Program_List_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
		else{
			/*†®†¢†Î†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢†¢†²*/
			Print_Program_List_Line( 8, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
	}
	else{
		/*†®†¢†Î†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢†¢†²*/
		page_line = (PaperSizeLen() - 12);
		if (*LineCnt == page_line) {
			Print_Program_List_Line( 2, List.S.Print, List.S.Attribute );
		}
		else {
			Print_Program_List_Line( 8, List.S.Print, List.S.Attribute );
		}
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	(*LineCnt)--;
	return ret;
}
#endif /* (PRO_PANEL == KANJI) */ /* added by H.Kubo 1999/01/06 */

#endif
