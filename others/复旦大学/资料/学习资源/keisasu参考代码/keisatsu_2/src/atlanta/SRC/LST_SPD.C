/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_SPD.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒ_ƒCƒ„ƒ‹ƒŠƒXƒgi’Zkj
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\uni_pro.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_v\rom_tbl.h"	/* Optional Speed Operation */

#include	"\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
/*#include	"\src\memsw\define\mem_sw_h.h" /*1996/04/17 Eguchi*/

#if (PRO_PANEL == ANK)
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h" /* Oct.2,1995 By S.K */
#endif

#if (PRO_PANEL == KANJI)
#include	"\src\atlanta\opr\kanji\ext_v\opr_data.h"
#include	"\src\atlanta\opr\kanji\define\opr_def.h" /* Oct.2,1995 By S.K */
#endif

#if (PRO_OKI == ENABLE)	/* by K.Watanabe 1999/02/09 */
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#endif

#if (PRO_OPTIONAL_SPEED == ENABLE) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
#include	"\src\atlanta\ext_v\sys_data.h"
#endif

/*************************************************************************
	module		:[ƒ_ƒCƒ„ƒ‹ƒŠƒXƒgi’Zkjˆóü]
	functiom	:[ƒ_ƒCƒ„ƒ‹ƒŠƒXƒgi’Zkj‚ðˆóü‚·‚é]
	common		:[
		List				:
		SYB_SpeedDial		:
		SYB_OptionalSpeed	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/25]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Print_SpeedDial_List(
						 void )				/*‚È‚µ*/
{
	UBYTE	i;						/*loop*/
	UBYTE	page;					/*Íß°¼Þ*/
	UBYTE	line_cnt;				/*Žc‚èˆóü‰Â”\s”*/
	UBYTE	speed_cnt;				/*’ZkÃÞ°À”Ô†*/
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/
	UBYTE	search_str[LST_COMP_LEN+1];/*»°Á•¶Žš—ñ*/
	UBYTE	kind;					/*»°ÁŽí—Þ*/
												/*LST_SEARCH_ASCII*/
												/*LST_SEARCH_NUMBER*/
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
	UBYTE	next_line;				/* »°Ás” */
#else
	UBYTE	sub_dial_flag;			/* “]‘—æ‚ª‚ ‚ê‚Î1 */
#endif

	page = 1;
	speed_cnt = -1;
	CMN_MemorySet( search_str, LST_COMP_LEN, ' ' );
	search_str[LST_COMP_LEN] = NULL;

	/*»°ÁŽí—Þ*/
	if ( CHK_DialListPrint() ) {		/* I:0-6 */
		kind = LST_SEARCH_ASCII;
	}
	else {
		kind = LST_SEARCH_NUMBER;
	}

#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
	next_line = SpeedDataNextSearch( kind, &speed_cnt, search_str );	/*ÃÞ°À“ªo‚µ (ˆø”’Ç‰Á 95/06/27 Î‹´³˜a) */
#else
	SpeedDataNextSearch( kind, &speed_cnt, search_str, &sub_dial_flag );	/*ÃÞ°À“ªo‚µ (ˆø”’Ç‰Á 95/06/27 Î‹´³˜a) */
#endif

	while ( speed_cnt != (WORD)SYS_SPEED_DIAL_MAX ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		if ( page == 1 ) {
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		else {
			line_cnt = (UBYTE)(PaperSizeLen() - 4);/*ˆóü‰Â”\s”¾¯Ä*/
		}

		if ( (ret = Print_SpeedDial_List_Head( 0, page, LST_SPEEDDIAL_LIST ) ) != OK ) {	/*Í¯ÀÞˆóü*/
			return ( ret );
		}

		for ( i = 0;; i++ ) {
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
			/*ˆóü—\’ès”‚ªˆóü‰Â”\‚©”»’f*/
			if (next_line >= line_cnt || line_cnt < 2 ) {
				break;
			}
			if ( (ret = Print_Dial_List_Specifi(LST_SPEED, page, i, speed_cnt, &line_cnt ) ) != OK ) {	/*1–¾×ˆóü*/
				return ( ret );
			}
			next_line = SpeedDataNextSearch( kind, &speed_cnt, search_str );	/*ŽŸÃÞ°À»°Á */
#else
			/*ˆóü—\’ès”‚ªˆóü‰Â”\‚©”»’f*/
			if ((sub_dial_flag && (line_cnt < 3)) || line_cnt < 2 ) { /* ðŒ•ÏX 95/06/27 Î‹´³˜a */
				break;
			}
			if ( (ret = Print_SpeedDial_List_Specifi( page, i, (UBYTE)speed_cnt, &line_cnt ) ) != OK ) {	/*1–¾×ˆóü*/
				return ( ret );
			}
			SpeedDataNextSearch( kind, &speed_cnt, search_str, &sub_dial_flag );	/*ŽŸÃÞ°À»°Á (ˆø”’Ç‰Á 95/06/27 Î‹´³˜a) */
#endif	/* (PRO_DIAL_LIST_GROUP == ENABLE) */

			if ( speed_cnt == (WORD)SYS_SPEED_DIAL_MAX ) {
				break;
			}
		}
		if ( (ret = Print_SpeedDial_List_Head( 1, page, LST_SPEEDDIAL_LIST) ) != OK ) {	/*Ì¯Àˆóü*/
			return ( ret );
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}

	/** ŒÂ•ÊÝ’è‚ÌŽž‚Í‘®«ƒŠƒXƒg‚ðo—Í‚·‚é */
	if (CHK_SpeedDialSparateSet()) {
		if ( (ret = PrintDialAttributeList(LST_SPEEDDIAL_LIST)) != OK) {
			return (ret);
		}
	}
	return ( OK );
}
/*************************************************************************
	module		:[ƒ_ƒCƒ„ƒ‹ƒŠƒXƒgi’Zkjƒwƒbƒ_ˆóü]
	functiom	:[ƒ_ƒCƒ„ƒ‹ƒŠƒXƒgi’Zkj‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
	common		:[
		List	:
	]
	condition	:[
		ƒwƒbƒ_Ží—Þ
		,	0->ƒy[ƒWæ“ªŒ©o‚µ
		,	1->ƒy[ƒWƒGƒ“ƒhŒ©o‚µ
		ƒXƒs[ƒhƒ_ƒCƒ„ƒ‹^ƒƒ“ƒ^ƒbƒ`ƒ_ƒCƒ„ƒ‹
		,	LST_SPEEDDIAL_LIST	’Zk
		,	LST_ONETOUCHDIAL_LIST	ƒƒ“ƒ^ƒbƒ`
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/25]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Print_SpeedDial_List_Head(
						 UBYTE Category,		/*ƒwƒbƒ_Ží—Þ*/
						 UBYTE Page,			/*ƒy[ƒW*/
						 UBYTE SpeedOnetouch )	/*ƒXƒs[ƒhƒ_ƒCƒ„ƒ‹^ƒƒ“ƒ^ƒbƒ`ƒ_ƒCƒ„ƒ‹*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Category == 0 ) {
		if ( Page == 1 ) {
			/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs{Œ©o‚µ{‚P‰üs*/
			if ( SpeedOnetouch == LST_SPEEDDIAL_LIST ) {
				/*––@’Zkƒ_ƒCƒ„ƒ‹@ƒŠƒXƒg@––*/
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
				if ( (ret = Print_Head1_Common( PWRD_TeleDirectory_K, LST_NOT,14-1 )) != OK ) {
					return ( ret );
				}
#else
				if ( (ret = Print_Head1_Common( PWRD_TeleDirectory, LST_XXX_TWI_XXX, 14-1 )) != OK ) { /* 20->14(For ANZU) 96/02/06 H.Hirao */
					return ( ret );
				}
#endif
			}
			else {
				/*––@ƒƒ“ƒ^ƒbƒ`ƒ_ƒCƒ„ƒ‹@ƒŠƒXƒg@––*/
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
				if ( (ret = Print_Head1_Common( PWRD_OneDirectory_K, LST_NOT,14-1 )) != OK ) {
					return ( ret );
				}
#else
				if ( (ret = Print_Head1_Common( PWRD_OneDirectory, LST_XXX_TWI_XXX, 14-1 )) != OK ) { /* 20->14(For ANZU) 96/02/06 H.Hirao */
				    return ( ret );
				}
#endif
			}

			/*Page Œ»ÝŽžŠÔ*/
#if (PRO_OPTIONAL_SPEED == ENABLE) && (PRO_OP_SPPED_4_FIGURE == ENABLE) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
			if ((CHK_UNI_OptionalSpeedDial() != 0)			/* ”CˆÓ’Zk‚ÌŽž */
			 && (SpeedOnetouch == LST_SPEEDDIAL_LIST)) {	/* ’Zkƒ_ƒCƒ„ƒ‹ƒŠƒXƒg‚ÌŽž */
 #if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_DIAL_LIST_GROUP == ENABLE)	/* PRO_DIAL_LIST_GROUP‚ÌðŒ’Ç‰Á by K.Watanabe 1999/05/25 */
				if ( (ret = PageTimePrint( Page, 2-1, 61-1 )) != OK ) {
					return ( ret );
				}
 #else
				if ( (ret = PageTimePrint( Page, 5-1, 56-1 )) != OK ) {
					return ( ret );
				}
 #endif
			}
			else {
 #if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_DIAL_LIST_GROUP == ENABLE)	/* PRO_DIAL_LIST_GROUP‚ÌðŒ’Ç‰Á by K.Watanabe 1999/05/25 */
				if ( (ret = PageTimePrint( Page, 2-1, 60-1 )) != OK ) {
					return ( ret );
				}
 #else
				if ( (ret = PageTimePrint( Page, 5-1, 55-1 )) != OK ) {
					return ( ret );
				}
 #endif
			}
#else	/* (PRO_OPTIONAL_SPEED == ENABLE) && (PRO_OP_SPPED_4_FIGURE == ENABLE) */
 #if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_DIAL_LIST_GROUP == ENABLE)	/* PRO_DIAL_LIST_GROUP‚ÌðŒ’Ç‰Á by K.Watanabe 1999/05/25 */
			if ( (ret = PageTimePrint( Page, 2-1, 60-1 )) != OK ) {
				return ( ret );
			}
 #else
			if ( (ret = PageTimePrint( Page, 5-1, 55-1 )) != OK ) {
				return ( ret );
			}
 #endif
#endif
			/*†®†¢†Î†¢†¢†Î†¢†¢†¢†Î„Ÿ†¢„¦„Ÿ†²*/
			Print_Dial_List_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤ NO.†¤‘ŠŽèæ–¼†¤ÀÞ²ÔÙ”Ô†„ ¸ÞÙ°ÌßNo†¤—¿‹à„ */
			Print_Dial_List_Line( 1, List.S.Print, List.S.Attribute );
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
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_DIAL_LIST_GROUP == ENABLE)	/* PRO_DIAL_LIST_GROUP‚ÌðŒ’Ç‰Á by K.Watanabe 1999/05/25 */
			if ( (ret = PagePrint( Page, 2-1 )) != OK ) {
				return ( ret );
			}
#else
			if ( (ret = PagePrint( Page, 5-1 )) != OK ) {
				return ( ret );
			}
#endif
		}
	}
	else {
		/*†¶†¢†Ö†¢†¢†Ö†¢†¢†¢†Ö„Ÿ†¢„¨†¢†º*/
		Print_Dial_List_Line( 4, List.S.Print, List.S.Attribute );
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
	module		:[’Zkƒ_ƒCƒ„ƒ‹ ƒlƒNƒXƒg ƒT[ƒ`n
	functiom	:[’Zkƒ_ƒCƒ„ƒ‹‚ÌŽŸ‚ðƒT[ƒ`‚·‚é]
	common		:[
		SYB_SpeedDial	:
	]
	condition	:[
		ƒT[ƒ`•û–@
		,	LST_SEARCH_NUMBER
		,	LST_SEARCH_ASCII
		’Zkƒ_ƒCƒ„ƒ‹ƒf[ƒ^”Ô†
		,	ƒf[ƒ^ƒGƒ“ƒh->SYS_SPEED_DIAL_MAX
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/25]
	author		:[–L“c_Žq]
*************************************************************************/
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
UBYTE				SpeedDataNextSearch(
						 UBYTE Kind,		/*ƒT[ƒ`•û–@*/
						 UBYTE* SpeedCnt,	/*’Zkƒ_ƒCƒ„ƒ‹ƒf[ƒ^”Ô†*/
						 UBYTE *SearchStr)	/*Œ»ÝƒT[ƒ`•¶Žš*/
#else
void				SpeedDataNextSearch(
						 UBYTE Kind,		/*ƒT[ƒ`•û–@*/
						 UBYTE* SpeedCnt,	/*’Zkƒ_ƒCƒ„ƒ‹ƒf[ƒ^”Ô†*/
						 UBYTE *SearchStr,	/*Œ»ÝƒT[ƒ`•¶Žš*/
						 UBYTE *sub_dial_flag)	/* “]‘—æ‚ª‚ ‚ê‚Î1 */
#endif
{
	UBYTE	speed;			/*’ZkÀÞ²ÔÙÃÞ°À”Ô†*/
	UBYTE	i;				/*loop*/
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
	UBYTE	j;
	UBYTE	grp_cnt;
	UBYTE	length;
	UBYTE	next_line;
#endif

#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
	j = 1;
	next_line = 1;
	grp_cnt = 0;
#endif

	if ( Kind == LST_SEARCH_NUMBER ) {
		/*”z—ñ‡‚Ì»°Á*/
		for ( i = (UBYTE)((*SpeedCnt+1)); i < SYS_SPEED_DIAL_MAX; i++ ) {
			if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
				if ( SYB_OptionalSpeed[i].Number != 0xFFFF ) {
					break;
				}
			}
			else{		/* ’Êí‚Ì’Zk‚ÌŽž */

#if (0)
** 				/* ‚h‚b‚g‚n‚t‚©‚ç‚ÌƒtƒB[ƒhƒoƒbƒN By O.Kimoto 1998/03/30 */
** 				/*
** 				** ƒŠƒ‚[ƒgf’f‚ª–¢“o˜^‚È‚ç‚e‚O‚ð‘‚­ê‡‚ª‚ ‚é‚Ì‚Å‚e‚e‚ÅŒ©‚Ä‚¢‚é‚Æ‚¨‚©‚µ‚­‚È‚é
** 				** 1997/10/03 M.Shimizu
** 				*/
** 				if ( SYB_SpeedDial[i].Dial[0] != LST_DIAL_NOT ) {
** 					break;
** 				}
#else
				if ( (SYB_SpeedDial[i].Dial[0] & 0xF0) != 0xF0) {
					break;
				}
#endif
			}
		}
		speed = i;
	}
	else {
		/*–¼Ì±½·°‡‚Ì»°Á*/
		speed = (UBYTE)((*SpeedCnt+1));
		SpeedStrEqSearch( &speed, SearchStr ); /** ‘S‚­“¯‚¶‘ŠŽèæ‚ª‚Ü‚¾‚ ‚é‚©ƒ`ƒFƒbƒN‚·‚é */
		if ( speed == SYS_SPEED_DIAL_MAX ) { /** ŒŸõ•¶Žš—ñ‚ª‚È‚¢ê‡ */
			SpeedStrGtSearch( &speed, SearchStr );
		}
	}
	/*Œ‹‰Ê¾¯Ä*/
	*SpeedCnt = speed;

#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
	/* ŽŸ‚Éˆóü‚·‚é’Zk‚ª–³‚¢Žž‚É‚ÍAs”‚ÌŒvŽZ‚Í•K—v‚È‚¢‚Ì‚ÅÈ‚«‚Ü‚·
	** ’jÈ‚©‚È‚¢‚ÆAê‡‚É‚æ‚Á‚Ä‚ÍRAM‚ª‚Â‚Ô‚ê‚é‰Â”\«‚ª‚ ‚è‚Ü‚·
	*/
	if (*SpeedCnt != (WORD)SYS_SPEED_DIAL_MAX) {
		/* s”‚ðŒvŽZ */
		/* ÀÞ²ÔÙ */
		if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
			length = GetBCD_StringLength(SYB_SpeedDial[SYB_OptionalSpeed[speed].Record].Dial);
		}
		else {
			length = GetBCD_StringLength(SYB_SpeedDial[speed].Dial);
		}
		if (length > 20) {
			next_line++;
		}
#if !defined (KEISATSU) /* 05/04/12 Î‹´³˜a */
		/* »ÌÞÀÞ²ÔÙ */
		if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
			if ( SYB_SpeedDial[SYB_OptionalSpeed[speed].Record].SubDialPosition != 0xFF ) {
				next_line++;
				length = GetBCD_StringLength(SYB_SubDial[SYB_SpeedDial[SYB_OptionalSpeed[speed].Record].SubDialPosition]);
				if (length > 20) {
					next_line++;
				}
			}
		}
		else {
			if ( SYB_SpeedDial[speed].SubDialPosition != 0xFF ) {
				next_line++;
				length = GetBCD_StringLength(SYB_SubDial[SYB_SpeedDial[speed].SubDialPosition]);
				if (length > 20) {
					next_line++;
				}
			}
		}
#endif
		if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
			for ( i = 1; i <= SYS_GROUP_NUMBER_MAX; i++ ) {
				if ( (SYB_SpeedDial[SYB_OptionalSpeed[speed].Record].Group & j) == j ) {
					grp_cnt++;
				}
				j <<= 1;
			}
		}
		else {
			for ( i = 1; i <= SYS_GROUP_NUMBER_MAX; i++ ) {
				if ( (SYB_SpeedDial[speed].Group & j) == j ) {
					grp_cnt++;
				}
				j <<= 1;
			}
		}

		if (next_line < 2 && grp_cnt > 9) {
			next_line++;
		}
		if (next_line < 3 && grp_cnt > 18) {
			next_line++;
		}
		if (next_line < 4 && grp_cnt > 27) {
			next_line++;
		}
	}
	return(next_line);
#else
	if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
#if defined (KEISATSU) /* ŒxŽ@FAX 05/04/12 Î‹´³˜a */
		*sub_dial_flag = 0;
#else
		if (SYB_SpeedDial[SYB_OptionalSpeed[speed].Record].SubDialPosition == 0xFF) {
			/** “]‘—æ‚ª‚È‚¢ê‡ */
			*sub_dial_flag = 0;
		}
		else { /** “]‘—æ‚ª‚ ‚éê‡ */
			*sub_dial_flag = 1;
		}
#endif
	}
	else {
#if defined (KEISATSU) /* ŒxŽ@FAX 05/04/12 Î‹´³˜a */
		*sub_dial_flag = 0;
#else
		if (SYB_SpeedDial[speed].SubDialPosition == 0xFF) {
			/** “]‘—æ‚ª‚È‚¢ê‡ */
			*sub_dial_flag = 0;
		}
		else { /** “]‘—æ‚ª‚ ‚éê‡ */
			*sub_dial_flag = 1;
		}
#endif
	}
#endif	/* (PRO_DIAL_LIST_GROUP == ENABLE) */
}

/*************************************************************************
	module		:[’Zkƒ_ƒCƒ„ƒ‹“¯ˆê–¼ÌƒT[ƒ`]
	functiom	:[’Zkƒ_ƒCƒ„ƒ‹‚Ì“¯ˆê–¼Ì‚ðƒT[ƒ`‚·‚é]
	common		:[
		SYB_SpeedDial	:
	]
	condition	:[
		’Zkƒ_ƒCƒ„ƒ‹ƒf[ƒ^”Ô†
		,	ƒf[ƒ^ƒGƒ“ƒh->SYS_SPEED_DIAL_MAX
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/25]
	author		:[–L“c_Žq]
*************************************************************************/
void				SpeedStrEqSearch(
						 UBYTE* SpeedCnt,	/*’Zkƒ_ƒCƒ„ƒ‹ƒf[ƒ^”Ô†*/
						 UBYTE* SearchStr )	/*Œ»ÝƒT[ƒ`•¶Žš*/
{
	UBYTE	i;				/*loop*/

	for ( i = *SpeedCnt; i < SYS_SPEED_DIAL_MAX; i++ ) {
		if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
			if ( SYB_OptionalSpeed[i].Number != 0xFFFF ) {
				if ( CMN_StringCompare( SearchStr, SYB_SpeedDial[SYB_OptionalSpeed[i].Record].Name,
				  LST_COMP_LEN ) == STRCMP_EQUAL ){
					break;
				}
			}
		}
		else{		/* ’Êí‚Ì’Zk‚ÌŽž */

#if (0)
** 			/* ‚h‚b‚g‚n‚t‚©‚ç‚ÌƒtƒB[ƒhƒoƒbƒN By O.Kimoto 1998/03/30 */
** 			/*
** 			** ƒŠƒ‚[ƒgf’f‚ª–¢“o˜^‚È‚ç‚e‚O‚ð‘‚­ê‡‚ª‚ ‚é‚Ì‚Å‚e‚e‚ÅŒ©‚Ä‚¢‚é‚Æ‚¨‚©‚µ‚­‚È‚é
** 			** 1997/10/03 M.Shimizu
** 			*/
** 			if ( SYB_SpeedDial[i].Dial[0] != LST_DIAL_NOT ) { /** ’Zk”Ô†‚ª‚ ‚éê‡ */
#else
			if ( (SYB_SpeedDial[i].Dial[0] & 0xF0) != 0xF0 ) {
#endif

				if ( CMN_StringCompare( SearchStr, SYB_SpeedDial[i].Name,
				  LST_COMP_LEN ) == STRCMP_EQUAL ){
					/** ‘ŠŽèæ–¼‚ªˆê’v‚µ‚½ê‡ */
					break;
				}
			}
		}
	}
	*SpeedCnt = i; /** ˆø”•¶Žš—ñ‚ª‘ŠŽèæ–¼‚É“o˜^‚³‚ê‚Ä‚¢‚ê‚ÎA‚»‚Ì’Zkƒ_ƒCƒ„ƒ‹‚ÌƒIƒtƒZƒbƒg‚ª“ü‚éB‚³‚ê‚Ä‚È‚¯‚ê‚ÎSYS_SPEED_DIAL_MAX‚ª“ü‚é */
}
/*************************************************************************
	module		:[’Zkƒ_ƒCƒ„ƒ‹GREATER–¼ÌƒT[ƒ`]
	functiom	:[’Zkƒ_ƒCƒ„ƒ‹GREATER–¼Ì‚ðƒT[ƒ`‚·‚é]
	common		:[
		SYB_SpeedDial	:
	]
	condition	:[
		’Zkƒ_ƒCƒ„ƒ‹ƒf[ƒ^”Ô†
		,	ƒf[ƒ^ƒGƒ“ƒh->SYS_SPEED_DIAL_MAX
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/25]
	author		:[–L“c_Žq]
*************************************************************************/
void				SpeedStrGtSearch(
						 UBYTE* SpeedCnt,	/*’Zkƒ_ƒCƒ„ƒ‹ƒf[ƒ^”Ô†*/
						 UBYTE* SearchStr )	/*Œ»ÝƒT[ƒ`•¶Žš*/
{
	UBYTE	i;					/*loop*/
	UBYTE	j;					/*GT point*/
	UBYTE	set_f;				/*comp_pt set flag*/
											/*OFF - > –¢¾¯Ä*/
											/*ON  - > Ï¾¯Ä*/
	UBYTE	*comp_pt;		/*compear pointer*/

	*SpeedCnt = 0;
	j = 0xff;
	set_f = OFF;

	for ( i = *SpeedCnt; i < SYS_SPEED_DIAL_MAX; i++ ) {
		if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
			if ( SYB_OptionalSpeed[i].Number != 0xFFFF ) {
				if ( CMN_StringCompare( SearchStr, SYB_SpeedDial[SYB_OptionalSpeed[i].Record].Name,
				  LST_COMP_LEN ) == STRCMP_LOWER ){
					if ( set_f == OFF ) {
						comp_pt = SYB_SpeedDial[SYB_OptionalSpeed[i].Record].Name;
						j = i;
						set_f = ON;
					}
					else {
						if ( CMN_StringCompare( comp_pt, SYB_SpeedDial[SYB_OptionalSpeed[i].Record].Name,
						  LST_COMP_LEN ) == STRCMP_UPPER ) {
							comp_pt = SYB_SpeedDial[SYB_OptionalSpeed[i].Record].Name;
							j = i;
						}
					}
				}
			}
		}
		else{	/* ’Êí‚Ì’Zk‚ÌŽž */

#if (0)
** 			/* ‚h‚b‚g‚n‚t‚©‚ç‚ÌƒtƒB[ƒhƒoƒbƒN By O.Kimoto 1998/03/30 */
** 			/*
** 			** ƒŠƒ‚[ƒgf’f‚ª–¢“o˜^‚È‚ç‚e‚O‚ð‘‚­ê‡‚ª‚ ‚é‚Ì‚Å‚e‚e‚ÅŒ©‚Ä‚¢‚é‚Æ‚¨‚©‚µ‚­‚È‚é
** 			** 1997/10/03 M.Shimizu
** 			*/
** 			if ( SYB_SpeedDial[i].Dial[0] != LST_DIAL_NOT ) [
#else
			if ( (SYB_SpeedDial[i].Dial[0] & 0xF0) != 0xF0 ) {
#endif

				if ( CMN_StringCompare( SearchStr, SYB_SpeedDial[i].Name,
				  LST_COMP_LEN ) == STRCMP_LOWER ){
					if ( set_f == OFF ) {
						comp_pt = SYB_SpeedDial[i].Name;
						j = i;
						set_f = ON;
					}
					else {
						if ( CMN_StringCompare( comp_pt, SYB_SpeedDial[i].Name,
						  LST_COMP_LEN ) == STRCMP_UPPER ) {
							comp_pt = SYB_SpeedDial[i].Name;
							j = i;
						}
					}
				}
			}
		}
	}
	if ( j == 0xff ) {
		*SpeedCnt = SYS_SPEED_DIAL_MAX;
	}
	else {
		*SpeedCnt = j;
		CMN_StringCopyNum( SearchStr, comp_pt , LST_COMP_LEN );
		SearchStr[LST_COMP_LEN] = NULL;
	}
}

#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
/*************************************************************************
	module		:[ƒ_ƒCƒ„ƒ‹ƒŠƒXƒgiƒƒ“ƒ^ƒbƒ`E’Zkj‚Ì‚P–¾×ˆóü]
	functiom	:[ƒ_ƒCƒ„ƒ‹ƒŠƒXƒg‚Ì‚P–¾×‚ðˆóü‚·‚éB]
	common		:[
		List			:
		SYB_SpeedDial	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1999/01/22]
	author		:[¼ŒG]
*************************************************************************/
WORD	Print_Dial_List_Specifi(
				UBYTE Kind,				/*Ží—Þ*/
			 	UBYTE Page,				/*ƒy[ƒW*/
				UBYTE Line,				/*Œ»Ý–¾×”*/
				UWORD DialCnt,			/*ƒ_ƒCƒ„ƒ‹”Ô†*/
				UBYTE *LineCnt )		/*ˆóŽšsˆÊ’u*/
{
	struct	SYS_SpeedDialData_t		*ptr;

	WORD	ret;					/*ŽÀsŒ‹‰Ê*/
	UBYTE	dial_chk;
	UBYTE	sub_chk;
	UBYTE	grp_cnt;
	UBYTE	grp_one;
	UBYTE	grp_sec;
	UBYTE	grp_thr;
	UBYTE	line_cnt;
	UBYTE	length;
	UBYTE	i;
	UDWORD	j;

	dial_chk = 0;
	sub_chk = 0;
	grp_cnt = 0;
	grp_one = 0;
	grp_sec = 0;
	grp_thr = 0;
	line_cnt = 1;
	length = 0;
	j = 1;

	if (Kind == LST_ONETOUCH) {
		ptr = &SYB_OnetouchDial[DialCnt];
	}
	else {
		if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
			ptr = &SYB_SpeedDial[SYB_OptionalSpeed[DialCnt].Record];
		}
		else {
			ptr = &SYB_SpeedDial[DialCnt];
		}
	}

	if ( Page > 1 && Line == 0 ) {
		/*†®†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢„Ÿ†¢†²*/
		Print_Dial_List_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	else {
		/*†¾†¢†Þ†¢†¢†Þ†¢†¢†¢†Þ„Ÿ†¢†¢†Æ*/
		Print_Dial_List_Line( 2, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	/*†¤ 999†¤xxxxxx†¤xxxxxxxxx†¤xxxxxxxx„ */
	Print_Dial_List_Line( 3, List.S.Print, List.S.Attribute );

	/* s”‚ðŒvŽZ */
	/* ÀÞ²ÔÙ */
	length = GetBCD_StringLength(ptr->Dial);
	if (length > 20) {
		dial_chk = 1;
		line_cnt++;
	}

#if !defined (KEISATSU) /* 05/04/12 Î‹´³˜a */
	/* »ÌÞÀÞ²ÔÙ */
	if ( ptr->SubDialPosition != 0xFF ) {
		line_cnt++;
		sub_chk = 1;
		length = GetBCD_StringLength(SYB_SubDial[ptr->SubDialPosition]);
		if (length > 20) {
			line_cnt++;
			sub_chk = 2;
		}
	}
#endif

	/********************
	*	‚Ps–Ú			*
	********************/
	/* No. */
	if (Kind == LST_ONETOUCH) {
		List.S.Print[1] = '[';
		CMN_UnsignedIntToASC(&List.S.Print[2], (UWORD)(CMN_OffsetToOnetouchCode(DialCnt) - 0x40), 2, '0');
		List.S.Print[4] = ']';
	}
	else {
		List.S.Print[1]	= 'S';
		if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
			CMN_UnsignedIntToASC(&List.S.Print[2], (UWORD)SYB_OptionalSpeed[DialCnt].Number, 3, '0');
		}
		else {		/* ’Êí‚Ì’Zk‚ÌŽž */
			CMN_UnsignedIntToASC(&List.S.Print[2], (UWORD)(DialCnt)+(OPR_SPEED_DIAL_MIN), 3, '0');
		}
	}

	/*‘ŠŽèæ–¼*/
	CMN_StringCopy( &List.S.Print[6], ptr->Name );

	/*ÀÞ²ÔÙ”Ô† */
	CMN_BCD_ToASC_String( List.S.Work, ptr->Dial);
	CMN_StringCopyNumUntilNull( &List.S.Print[31], List.S.Work, 20 );

	/*¸ÞÙ°ÌßNo*/
	GroupToShortString( ptr->Group, List.S.Work, 0 );
	CMN_StringCopy( &List.S.Print[52], List.S.Work );
	for ( i = 1; i <= SYS_GROUP_NUMBER_MAX; i++ ) {
		if ( (ptr->Group & j) == j ) {
			grp_cnt++;
			if (grp_cnt == 9) {
				grp_one = i;
			}
			if (grp_cnt == 18) {
				grp_sec = i;
			}
			if (grp_cnt == 27) {
				grp_thr = i;
			}
		}
		j <<= 1;
	}

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	*LineCnt -= 2;

	/********************
	*	‚Qs–Ú			*
	********************/
	if ((line_cnt > 1) || ( grp_cnt > 9 )) {
		Print_Dial_List_Line( 3, List.S.Print, List.S.Attribute );
#if defined (KEISATSU) /* ŒxŽ@FAX 05/04/12 Î‹´³˜a */
		if (dial_chk != 0 ) {
			/*ÀÞ²ÔÙ”Ô†i‚Qs–Új */
			CMN_BCD_ToASC_String( List.S.Work, &ptr->Dial[10] );
			CMN_StringCopyNumUntilNull( &List.S.Print[31], List.S.Work, 20 );
		}
#else
		if (( sub_chk != 0 ) || ( dial_chk != 0 )) {
			if (dial_chk != 0 ) {
				/*ÀÞ²ÔÙ”Ô†i‚Qs–Új */
				CMN_BCD_ToASC_String( List.S.Work, &ptr->Dial[10] );
				CMN_StringCopyNumUntilNull( &List.S.Print[31], List.S.Work, 20 );
			}
			else {
				/*†¤	†¤i“]‘—æj†¤xxxxxxxxx†¤		„ */
				/*i“]‘—æj‚Ps–Ú */
				AttributeSet( &List.S.Print[6], &List.S.Attribute[6], PWRD_AltNo, LST_NOT );
				/*“]‘—æ*/
				CMN_BCD_ToASC_String( List.S.Work, &SYB_SubDial[ptr->SubDialPosition][0] );
				CMN_StringCopyNumUntilNull( &List.S.Print[31], List.S.Work, 20 );
			}
		}
#endif
		if ( grp_cnt > 9 ) {
			/*¸ÞÙ°ÌßNoi‚Qs–Új*/
			GroupToShortString( ptr->Group, List.S.Work, grp_one);
			CMN_StringCopy( &List.S.Print[52], List.S.Work );
		}

		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		*LineCnt -= 1;
	}

	/********************
	*	‚Rs–Ú			*
	********************/
	if ((line_cnt > 2) || ( grp_cnt > 18 )) {
		Print_Dial_List_Line( 3, List.S.Print, List.S.Attribute );
#if !defined (KEISATSU) /* 05/04/12 Î‹´³˜a */
		if (( sub_chk != 0 ) && ( dial_chk != 0 )) {
			/*†¤	†¤i“]‘—æj†¤xxxxxxxxx†¤		„ */
			/*i“]‘—æj‚Ps–Ú */
			AttributeSet( &List.S.Print[6], &List.S.Attribute[6], PWRD_AltNo, LST_NOT );
			/*“]‘—æ*/
			CMN_BCD_ToASC_String( List.S.Work, &SYB_SubDial[ptr->SubDialPosition][0] );
			CMN_StringCopyNumUntilNull( &List.S.Print[31], List.S.Work, 20 );
		}
		else {
			if ( sub_chk == 2 ) {
				/*“]‘—æ ‚Qs–Ú*/
				CMN_BCD_ToASC_String( List.S.Work, &SYB_SubDial[ptr->SubDialPosition][10] );
				CMN_StringCopyNumUntilNull( &List.S.Print[31], List.S.Work, 20 );
				sub_chk = 0;	/* “]‘—æI—¹ */
			}
		}
#endif
		if ( grp_cnt > 18 ) {
			/*¸ÞÙ°ÌßNoi‚Rs–Új*/
			GroupToShortString( ptr->Group, List.S.Work, grp_sec );
			CMN_StringCopy( &List.S.Print[52], List.S.Work );
		}

		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		*LineCnt -= 1;
	}

	/********************
	*	‚Ss–Ú			*
	********************/
	if ((line_cnt > 3) || ( grp_cnt > 27 )) {
		Print_Dial_List_Line( 3, List.S.Print, List.S.Attribute );
#if !defined (KEISATSU) /* ŒxŽ@FAX 05/04/12 Î‹´³˜a */
		if ( sub_chk == 2 ) {
			/*“]‘—æ ‚Qs–Ú*/
			CMN_BCD_ToASC_String( List.S.Work, &SYB_SubDial[ptr->SubDialPosition][10] );
			CMN_StringCopyNumUntilNull( &List.S.Print[31], List.S.Work, 20 );
		}
#endif
		if ( grp_cnt > 27 ) {
			/*¸ÞÙ°ÌßNoi‚Rs–Új*/
			GroupToShortString( ptr->Group, List.S.Work, grp_thr);
			CMN_StringCopy( &List.S.Print[52], List.S.Work );
		}

		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		*LineCnt -= 1;
	}
	return ( OK );
}

#else
/*************************************************************************
	module		:[ƒ_ƒCƒ„ƒ‹ƒŠƒXƒg‚Ì‚P–¾×ˆóü]
	functiom	:[ƒ_ƒCƒ„ƒ‹ƒŠƒXƒg‚Ì‚P–¾×‚ðˆóü‚·‚éB]
	common		:[
		List			:
		SYB_SpeedDial	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/25]
	author		:[–L“c_Žq]
*************************************************************************/
WORD					Print_SpeedDial_List_Specifi(
						 UBYTE Page,				/*ƒy[ƒW*/
						 UBYTE Line,				/*Œ»Ý–¾×”*/
						 UBYTE SpeedCnt,		/*’Zkƒ_ƒCƒ„ƒ‹”Ô†*/
						 register UBYTE *LineCnt )	/*ˆóŽšsˆÊ’u*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

#if defined(KEISATSU)		/* ŒxŽ@‚e‚`‚w‘®«’Ç‰Á Added by SMuratec ‰Ä 2005/07/21 */
	UBYTE	kei_buf[4];
	UBYTE	kei_pos;
	kei_pos = 0;
#endif
	
#if 0	/* ƒvƒŒƒtƒBƒbƒNƒX{ƒ_ƒCƒ„ƒ‹”Ô†‚Å40Œ…‚ð’´‚¦‚Ä‚àÜ‚è•Ô‚µ‚ÄˆóŽš‚µ‚È‚¢‚Ì‚ÅA‘å“‡‚³‚ñŠm”F‚ÌãAƒŠƒXƒg‚Å‚Ì“WŠJ‚ÍŽ~‚ß‚Ü‚· by K.Watanabe 2004/11/12 */
//#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/10 *//* by K.Watanabe 2004/10/12 */
//	UWORD	length;
#endif			/*	End of defined(STOCKHM2)	*/

	if ( Page > 1 && Line == 0 ) {
		/*†®†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢„Ÿ†¢†²*/
		Print_Dial_List_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	else {
		/*†¾†¢†Þ†¢†¢†Þ†¢†¢†¢†Þ„Ÿ†¢†¢†Æ*/
		Print_Dial_List_Line( 2, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	/*†¤ 999†¤xxxxxx†¤xxxxxxxxx†¤xxxxxxxx„ */
	Print_Dial_List_Line( 3, List.S.Print, List.S.Attribute );
	if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
		/* No. */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		if ( SYS_SPEED_DIAL_MAX > 100 ) {
 #if (1) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
			CMN_UnsignedIntToASC( &List.S.Print[2-1], (UWORD)SYB_OptionalSpeed[SpeedCnt].Number,
			  OP_SPEED_FIGURE_MAX, '0' );
 #else
//			CMN_UnsignedIntToASC( &List.S.Print[2-1], (UWORD)SYB_OptionalSpeed[SpeedCnt].Number,
//			  3, '0' );
 #endif
		}
		else {
			CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)SYB_OptionalSpeed[SpeedCnt].Number,
			  2, '0' );
		}
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
		List.S.Print[5-1]	= *CalculateStringAddress(&D2W_HeadCharacter_Speed);
 #else
		List.S.Print[5-1]	= 'S';
 #endif
 #if (1) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
		CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)SYB_OptionalSpeed[SpeedCnt].Number,
		  OP_SPEED_FIGURE_MAX, '0' );
 #else
//		CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)SYB_OptionalSpeed[SpeedCnt].Number,
//		  3, '0' );
 #endif
#endif
		/*‘ŠŽèæ–¼*/
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		CMN_StringCopy( &List.S.Print[7-1], SYB_SpeedDial[SYB_OptionalSpeed[SpeedCnt].Record].Name );
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_OP_SPPED_4_FIGURE == ENABLE) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */	/* if 1 ‚É‚È‚Á‚Ä‚¢‚½‚ªA‚RŒ…Žž‚É•¶Žš‚ª‚¸‚ê‚é‚Ì‚ÅðŒ‚Â‚¯‚Ü‚· 2003/01/07 T.Takagi */
		CMN_StringCopy( &List.S.Print[11-1], SYB_SpeedDial[SYB_OptionalSpeed[SpeedCnt].Record].Name );
 #else
		CMN_StringCopy( &List.S.Print[10-1], SYB_SpeedDial[SYB_OptionalSpeed[SpeedCnt].Record].Name );
 #endif
#endif
		/*ÀÞ²ÔÙ”Ô† */
		CMN_BCD_ToASC_String( List.S.Work, SYB_SpeedDial[SYB_OptionalSpeed[SpeedCnt].Record].Dial );
		
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		CMN_StringCopy( &List.S.Print[24-1], List.S.Work );
		/*¸ÞÙ°ÌßNo*/
		GroupToShortString( SYB_SpeedDial[SYB_OptionalSpeed[SpeedCnt].Record].Group, List.S.Work );
		CMN_StringCopy( &List.S.Print[65-1], List.S.Work );
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_OP_SPPED_4_FIGURE == ENABLE) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */	/* if 1 ‚É‚È‚Á‚Ä‚¢‚½‚ªA‚RŒ…Žž‚É•¶Žš‚ª‚¸‚ê‚é‚Ì‚ÅðŒ‚Â‚¯‚Ü‚· 2003/01/07 T.Takagi */
		CMN_StringCopy( &List.S.Print[36-1], List.S.Work );
 #else
		CMN_StringCopy( &List.S.Print[35-1], List.S.Work );
 #endif
#endif
	}
	else{		/* ’Êí‚Ì’Zk‚ÌŽž */
		/* No. */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		if ( SYS_SPEED_DIAL_MAX > 100 ) {
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
			CMN_UnsignedIntToASC( &List.S.Print[2-1], (UWORD)(SpeedCnt)+(OPR_SPEED_DIAL_MIN), 3, '0' );
 #else
			CMN_UnsignedIntToASC( &List.S.Print[2-1], (UWORD)(SpeedCnt), 3, '0' );
 #endif
		}
		else {
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
			CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)(SpeedCnt)+(OPR_SPEED_DIAL_MIN), 2, '0' );
 #else
			CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)(SpeedCnt), 2, '0' );
 #endif
		}
#elif (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (F250‚Í’Zkƒ_ƒCƒ„ƒ‹‚ÍÅ‘å80Œ‚Å‚·‚©‚çA’ZkÀÞ²ÔÙNoA‚ªS01AS02`S80‚Ü‚Å‚É•ÏX‚·‚é‚±‚Æ) Added by SMuratec L.Z.W 2003/10/09 */
 #if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
		List.S.Print[5-1]	= *CalculateStringAddress(&D2W_HeadCharacter_Speed);
 #else
		List.S.Print[5-1]	= 'S';
 #endif
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
		CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(SpeedCnt)+(OPR_SPEED_DIAL_MIN), OP_SPEED_FIGURE_MAX, '0' );
 #else
		CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(SpeedCnt), OP_SPEED_FIGURE_MAX, '0' );
 #endif
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
		List.S.Print[5-1]	= *CalculateStringAddress(&D2W_HeadCharacter_Speed);
 #else
		List.S.Print[5-1]	= 'S';
 #endif
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
		CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(SpeedCnt)+(OPR_SPEED_DIAL_MIN), 3, '0' );
 #else
		CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(SpeedCnt), 3, '0' );
 #endif
#endif
		/*‘ŠŽèæ–¼*/
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		CMN_StringCopy( &List.S.Print[7-1], SYB_SpeedDial[SpeedCnt].Name ); /* By M.Kuwahara 1997/01/22*/
#else	/* PANEL_POPLA_B/L/H */
		CMN_StringCopy( &List.S.Print[10-1], SYB_SpeedDial[SpeedCnt].Name );
#endif
#if defined(KEISATSU)	/* ŒxŽ@‚e‚`‚w‘®«’Ç‰Á Added by SMuratec ‰Ä 2005/07/21 */
	/* SYB_OnetouchDial[OnetouchCnt].Keisatsu ‚©‚çA‘®«ƒoƒbƒtƒ@‚ðì¬ */
	if (SYB_SpeedDial[SpeedCnt].Keisatsu & SYS_KEISATSU_KEIDEN){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "¹", 1);
		kei_pos++;
	}
	else if (SYB_SpeedDial[SpeedCnt].Keisatsu & SYS_KEISATSU_KANYU){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "¶", 1);
		kei_pos++;
	}

	if (SYB_SpeedDial[SpeedCnt].Keisatsu & SYS_KEISATSU_ISSEI){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "²", 1);
		kei_pos++;
	}
	else if (SYB_SpeedDial[SpeedCnt].Keisatsu & SYS_KEISATSU_KOBETSU){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "º", 1);
		kei_pos++;
	}

	if (SYB_SpeedDial[SpeedCnt].Keisatsu & SYS_KEISATSU_SCRAMBLE_ON){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "S", 1);
		kei_pos++;
	}
	else if (SYB_SpeedDial[SpeedCnt].Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "N", 1);
		kei_pos++;
	}

	if (SYB_SpeedDial[SpeedCnt].Keisatsu & SYS_KEISATSU_KYOTSU){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "·", 1);
		kei_pos++;
	}
	else if (SYB_SpeedDial[SpeedCnt].Keisatsu & SYS_KEISATSU_SENYO){
		CMN_StringCopyNumNotNULL(&kei_buf[kei_pos], "¾", 1);
		kei_pos++;
	}
	
	if(kei_pos > 0){
		CMN_StringCopy( &List.S.Print[35-1], kei_buf ); 
		/*ÀÞ²ÔÙ”Ô†*/
		CMN_BCD_ToASC_String( List.S.Work, SYB_SpeedDial[SpeedCnt].Dial ); /* •ÏX(ANZU) 95/12/14 H.HIRAO */
		CMN_StringCopy( &List.S.Print[35+kei_pos-1], List.S.Work );
	}
	else{
		/*ÀÞ²ÔÙ”Ô†*/
		CMN_BCD_ToASC_String( List.S.Work, SYB_SpeedDial[SpeedCnt].Dial ); /* •ÏX(ANZU) 95/12/14 H.HIRAO */
		CMN_StringCopy( &List.S.Print[35-1], List.S.Work );
	}

#else	
		/*ÀÞ²ÔÙ”Ô† */
		CMN_BCD_ToASC_String( List.S.Work,  SYB_SpeedDial[SpeedCnt].Dial );
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		CMN_StringCopy( &List.S.Print[24-1], List.S.Work );
		/*¸ÞÙ°ÌßNo*/
		GroupToShortString( SYB_SpeedDial[SpeedCnt].Group, List.S.Work );
		CMN_StringCopy( &List.S.Print[65-1], List.S.Work );
#else	/* PANEL_POPLA_B/L/H */
 #if 0	/* ƒvƒŒƒtƒBƒbƒNƒX{ƒ_ƒCƒ„ƒ‹”Ô†‚Å40Œ…‚ð’´‚¦‚Ä‚àÜ‚è•Ô‚µ‚ÄˆóŽš‚µ‚È‚¢‚Ì‚ÅA‘å“‡‚³‚ñŠm”F‚ÌãAƒŠƒXƒg‚Å‚Ì“WŠJ‚ÍŽ~‚ß‚Ü‚· by K.Watanabe 2004/11/12 */
// #if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/09 *//* by K.Watanabe 2004/10/12 */
//			if (List.S.Work[0] == '!'){
//				length = CMN_StringLength(SYB_MercuryDialBuffer);	/* ƒ}ƒLƒ…ƒŠ[“o˜^Œ… */
//
//				List.S.Print[34] = '[';
//				if (length > 38){
//					CMN_StringCopyNumUntilNull( &List.S.Print[35], SYB_MercuryDialBuffer, 39);
//				}
//				else{
//					List.S.Print[35 + length] = ']';
//					
//					CMN_StringCopyNumUntilNull( &List.S.Print[35], SYB_MercuryDialBuffer, length);
//					CMN_StringCopyNumUntilNull( &List.S.Print[36 + length], &List.S.Work[1],
//						(38 - length) );
//				}
//			}
//			else{
//				CMN_StringCopy( &List.S.Print[35-1], List.S.Work );
//			}
 #else
  #if !defined(KEISATSU)	/* ŒxŽ@‚e‚`‚w‘®«’Ç‰Á Added by SMuratec ‰Ä 2005/07/21 */
		CMN_StringCopy( &List.S.Print[35-1], List.S.Work );
  #endif
 #endif		/*	End of defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE) */
#endif
	}

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	*LineCnt -= 2;

#if !defined (KEISATSU) /* 05/04/12 Î‹´³˜a */
	if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
		if ( SYB_SpeedDial[SYB_OptionalSpeed[SpeedCnt].Record].SubDialPosition != 0xFF ) {
			/*†¤	†¤i“]‘—æj†¤xxxxxxxxx†¤		„ */
			Print_Dial_List_Line( 3, List.S.Print, List.S.Attribute );
			/*i“]‘—æj*/
#if (PRO_KEYPANEL == PANEL_ANZU_L)						/* POPLA_L‘Î‰ž 1997/03/07 M.Kuwahara */
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_AltNo, LST_NOT );
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_OP_SPPED_4_FIGURE == ENABLE) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */	/* if 1 ‚É‚È‚Á‚Ä‚¢‚½‚ªA‚RŒ…Žž‚É•¶Žš‚ª‚¸‚ê‚é‚Ì‚ÅðŒ‚Â‚¯‚Ü‚· 2003/01/07 T.Takagi */
			AttributeSet( &List.S.Print[11-1], &List.S.Attribute[11-1], PWRD_AltNo, LST_NOT );
 #else
			AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_AltNo, LST_NOT );
 #endif
#endif
			/*“]‘—æ*/
			CMN_BCD_ToASC_String( List.S.Work,
			  &SYB_SubDial[SYB_SpeedDial[SYB_OptionalSpeed[SpeedCnt].Record].SubDialPosition][0] );
#if (PRO_KEYPANEL == PANEL_ANZU_L)						/* POPLA_L‘Î‰ž 1997/03/07 M.Kuwahara */
			CMN_StringCopy( &List.S.Print[24-1], List.S.Work );
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_OP_SPPED_4_FIGURE == ENABLE) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */	/* if 1 ‚É‚È‚Á‚Ä‚¢‚½‚ªA‚RŒ…Žž‚É•¶Žš‚ª‚¸‚ê‚é‚Ì‚ÅðŒ‚Â‚¯‚Ü‚· 2003/01/07 T.Takagi */
			CMN_StringCopy( &List.S.Print[36-1], List.S.Work );
 #else
			CMN_StringCopy( &List.S.Print[35-1], List.S.Work );
 #endif
#endif
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			*LineCnt -= 1;
		}
	}
	else{		/* ’Êí‚Ì’Zk‚ÌŽž */
		if ( SYB_SpeedDial[SpeedCnt].SubDialPosition != 0xFF ) {
			/*†¤	†¤i“]‘—æj†¤xxxxxxxxx†¤		„ */
			Print_Dial_List_Line( 3, List.S.Print, List.S.Attribute );
			/*i“]‘—æj*/
#if (PRO_KEYPANEL == PANEL_ANZU_L)						/* POPLA_L‘Î‰ž 1997/03/07 M.Kuwahara */
			AttributeSet( &List.S.Print[7-1], &List.S.Attribute[7-1], PWRD_AltNo, LST_NOT );
#else	/* PANEL_POPLA_B/L/H */
			AttributeSet( &List.S.Print[10-1], &List.S.Attribute[10-1], PWRD_AltNo, LST_NOT );
#endif
			/*“]‘—æ*/
			CMN_BCD_ToASC_String( List.S.Work,
			  &SYB_SubDial[SYB_SpeedDial[SpeedCnt].SubDialPosition][0] );
#if (PRO_KEYPANEL == PANEL_ANZU_L)						/* POPLA_L‘Î‰ž 1997/03/07 M.Kuwahara */
			CMN_StringCopy( &List.S.Print[24-1], List.S.Work );
#else	/* PANEL_POPLA_B/L/H */
 #if 0	/* ƒvƒŒƒtƒBƒbƒNƒX{ƒ_ƒCƒ„ƒ‹”Ô†‚Å40Œ…‚ð’´‚¦‚Ä‚àÜ‚è•Ô‚µ‚ÄˆóŽš‚µ‚È‚¢‚Ì‚ÅA‘å“‡‚³‚ñŠm”F‚ÌãAƒŠƒXƒg‚Å‚Ì“WŠJ‚ÍŽ~‚ß‚Ü‚· by K.Watanabe 2004/11/12 */
// #if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/09 *//* by K.Watanabe 2004/10/12 */
//			if (List.S.Work[0] == '!'){
//				length = CMN_StringLength(SYB_MercuryDialBuffer);	/* ƒ}ƒLƒ…ƒŠ[“o˜^Œ… */
//
//				List.S.Print[34] = '[';
//				if (length > 38){
//					CMN_StringCopyNumUntilNull( &List.S.Print[35], SYB_MercuryDialBuffer, 39);
//				}
//				else{
//					List.S.Print[35 + length] = ']';
//					
//					CMN_StringCopyNumUntilNull( &List.S.Print[35], SYB_MercuryDialBuffer, length);
//					CMN_StringCopyNumUntilNull( &List.S.Print[36 + length], &List.S.Work[1],
//						(38 - length) );
//				}
//			}
//			else{
//				CMN_StringCopy( &List.S.Print[35-1], List.S.Work );
//			}
 #else
			CMN_StringCopy( &List.S.Print[35-1], List.S.Work );
 #endif		/*	End of defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE) */
#endif
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			*LineCnt -= 1;
		}
	}
#endif /* !defined (KEISATSU) */
	
	return ( OK );
}
#endif	/* (PRO_DIAL_LIST_GROUP == ENABLE) */

/*************************************************************************
	module		:[ƒ_ƒCƒ„ƒ‹ƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrüì¬]
	functiom	:[ƒ_ƒCƒ„ƒ‹ƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
		,	0 = †®†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†²
		,	1 = †¤ NO.†¤		†¤			  †¤			†¤
		,	2 = †¾†¢†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Æ
		,	3 = †¤	  †¤		†¤			  †¤			†¤
		,	4 = †¶†¢†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†º
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/25]
	author		:[–L“c_Žq]
*************************************************************************/
void				Print_Dial_List_Line(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	UBYTE	i;

#if (PRO_OPTIONAL_SPEED == ENABLE) && (PRO_OP_SPPED_4_FIGURE == ENABLE) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
	if ((CHK_UNI_OptionalSpeedDial() != 0)					/* ”CˆÓ’Zk‚ÌŽž */
	 && (SYS_DocumentPrintItem == LST_SPEEDDIAL_LIST)) {	/* ’ZkƒŠƒXƒg‚ÌŽž */
		Prn_Att_Str_Clear( AscString, AttString );
		switch ( Category ) {
			case 0:
				/*†®†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†Î†¢†¢„Ÿ†¢„Ÿ†¢†²*/
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
				AscString[1-1] = LST_KLINE7;
				CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_ );
				AscString[7-1] = LST_KLINE8;
				AscString[23-1] = LST_KLINE8;
				AscString[64-1] = LST_KLINE8;
				AscString[80-1] = LST_KLINE9;
 #else	/* PANEL_POPLA_B/L/H */
				AscString[4-1] = LST_KLINE7;
				CMN_MemorySet( &AscString[5-1], 71, LST_KLINE_ );
				AscString[10-1] = LST_KLINE8;
				AscString[35-1] = LST_KLINE8;
				AscString[76-1] = LST_KLINE9;
 #endif
				break;
			case 1:
				/*†¤ NO.†¤±²Ã»·Ò² †¤ÀÞ²ÔÙÊÞÝºÞ³ †¤¸ÞÙ°ÌßNo	 „ */
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
				AscString[1-1] = LST_KLINEI;
				AttributeSet( &AscString[3-1], &AttString[3-1], PWRD_No, LST_NOT );
				AscString[7-1] = LST_KLINEI;
				AttributeSet( &AscString[8-1], &AttString[8-1], PWRD_RemoteLocation, LST_NOT );
				AscString[23-1] = LST_KLINEI;
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/23 Y.Matsukuma */
				AttributeSet( &AscString[36-1], &AttString[36-1], PWRD_Pages, LST_NOT );
 #else
				AttributeSet( &AscString[36-1], &AttString[36-1], PWRD_TeleNumber, LST_NOT );
 #endif
				AscString[64-1] = LST_KLINEI;
				AttributeSet( &AscString[65-1], &AttString[65-1], PWRD_GroupNumber, LST_NOT );
				AscString[80-1] = LST_KLINEI;
 #else	/* PANEL_POPLA_B/L/H */
				AscString[4-1] = LST_KLINEI;
				AttributeSet( &AscString[6-1], &AttString[6-1], PWRD_No, LST_NOT );
				AscString[10-1] = LST_KLINEI;
				AttributeSet( &AscString[15-1], &AttString[15-1], PWRD_RemoteLocation, LST_NOT );
				AscString[35-1] = LST_KLINEI;
				AttributeSet( &AscString[47-1], &AttString[47-1], PWRD_TeleNumber, LST_NOT );
				AscString[76-1] = LST_KLINEI;
 #endif
				break;
			case 2:
				/*†¾†¢†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Æ*/
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
				AscString[1-1] = LST_KLINE4;
				CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_ );
				AscString[7-1] = LST_KLINE5;
				AscString[23-1] = LST_KLINE5;
				AscString[64-1] = LST_KLINE5;
				AscString[80-1] = LST_KLINE6;
 #else	/* PANEL_POPLA_B/L/H */
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
				AscString[4-1] = LST_KLINE4;
				CMN_MemorySet( &AscString[5-1], 72, LST_KLINE_ );
				AscString[10-1] = LST_KLINE5;
				AscString[35-1] = LST_KLINE5;
				AscString[76-1] = LST_KLINE6;
 #endif
				break;
			case 3:
				/*†¤	†¤		  †¤			†¤			  †¤*/
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
				AscString[1-1] = LST_KLINEI;
				AscString[7-1] = LST_KLINEI;
				AscString[23-1] = LST_KLINEI;
				AscString[64-1] = LST_KLINEI;
				AscString[80-1] = LST_KLINEI;
 #else	/* PANEL_POPLA_B/L/H */
				AscString[4-1] = LST_KLINEI;
				AscString[10-1] = LST_KLINEI;
				AscString[35-1] = LST_KLINEI;
				AscString[76-1] = LST_KLINEI;
 #endif
				break;
			case 4:
				/*†¶†¢†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†º*/
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
				AscString[1-1] = LST_KLINE1;
				CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_ );
				AscString[7-1] = LST_KLINE2;
				AscString[23-1] = LST_KLINE2;
				AscString[64-1] = LST_KLINE2;
				AscString[80-1] = LST_KLINE3;
 #else	/* PANEL_POPLA_B/L/H */
				AscString[4-1] = LST_KLINE1;
				CMN_MemorySet( &AscString[5-1], 72, LST_KLINE_ );
				AscString[10-1] = LST_KLINE2;
				AscString[35-1] = LST_KLINE2;
				AscString[76-1] = LST_KLINE3;
 #endif
				break;
			case 5:
				/*†¤ NO.†¤±²Ã»·Ò² †¤¿Þ¸¾² 1 ¿Þ¸¾² 2 ¿Þ¸¾² 3 ¿Þ¸¾² 4†¤*/
				AscString[4-1] = LST_KLINEI;
				AttributeSet( &AscString[6-1], &AttString[6-1], PWRD_No, LST_NOT );
				AscString[10-1] = LST_KLINEI;
				AttributeSet( &AscString[15-1], &AttString[15-1], PWRD_RemoteLocation, LST_NOT );
				AscString[35-1] = LST_KLINEI;
				for (i = 0; i < 4; i++) {
					CMN_StringCopy(&List.S.Print[38-1+(i * 10)], PWRD_Attribute);
					List.S.Print[44-1+(i * 10)] = (UBYTE)('1' + i);
				}
				AscString[76-1] = LST_KLINEI;
				break;
 #if (PRO_KEYPANEL == PANEL_ANZU_L)	/* ANZU_L ‚Ì‘®«ƒŠƒXƒg’Ç‰Á‚Ì‚½‚ß Oct.17.1997 Y.Matsukuma */
			case 6:
				AscString[4-1] = LST_KLINE7;
				CMN_MemorySet( &AscString[5-1], 71, LST_KLINE_ );
				AscString[9-1] = LST_KLINE8;
				AscString[34-1] = LST_KLINE8;
				AscString[75-1] = LST_KLINE9;
				break;
			case 7:
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
				AscString[4-1] = LST_KLINE4;
				CMN_MemorySet( &AscString[5-1], 71, LST_KLINE_ );
				AscString[9-1] = LST_KLINE5;
				AscString[34-1] = LST_KLINE5;
				AscString[75-1] = LST_KLINE6;
				break;
			case 8:
				AscString[4-1] = LST_KLINEI;
				AscString[9-1] = LST_KLINEI;
				AscString[34-1] = LST_KLINEI;
				AscString[75-1] = LST_KLINEI;
				break;
			case 9:
				AscString[4-1] = LST_KLINE1;
				CMN_MemorySet( &AscString[5-1], 71, LST_KLINE_ );
				AscString[9-1] = LST_KLINE2;
				AscString[34-1] = LST_KLINE2;
				AscString[75-1] = LST_KLINE3;
				break;
 #endif
		}
		return;
	}
#endif

	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†Î†¢†¢„Ÿ†¢„Ÿ†¢†²*/
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
			AscString[0] = LST_KLINE7;
			CMN_MemorySet( &AscString[1], 79, LST_KLINE_ );
			AscString[5] = LST_KLINE8;
			AscString[30] = LST_KLINE8;
			AscString[51] = LST_KLINE8;
			AscString[79] = LST_KLINE9;
#else
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			AscString[1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_ );
			AscString[6-1] = LST_KLINE8;
			AscString[23-1] = LST_KLINE8;
			AscString[64-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE9;
 #else	/* PANEL_POPLA_B/L/H */
			AscString[4-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[5-1], 71, LST_KLINE_ );
			AscString[9-1] = LST_KLINE8;
			AscString[34-1] = LST_KLINE8;
			AscString[75-1] = LST_KLINE9;
 #endif
#endif	/* (PRO_DIAL_LIST_GROUP == ENABLE) */
			break;
		case 1:
			/*†¤ NO.†¤±²Ã»·Ò² †¤ÀÞ²ÔÙÊÞÝºÞ³ †¤¸ÞÙ°ÌßNo	 „ */
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
			AscString[0] = LST_KLINEI;
			AttributeSet( &AscString[2], &AttString[2], PWRD_No, LST_NOT );
			AscString[5] = LST_KLINEI;
			AttributeSet( &AscString[10], &AttString[10], PWRD_RemoteLocation, LST_NOT );
			AscString[30] = LST_KLINEI;
			AttributeSet( &AscString[32], &AttString[32], PWRD_TeleNumber, LST_NOT );
			AscString[51] = LST_KLINEI;
			AttributeSet( &AscString[57], &AttString[57], PWRD_GroupNumber, LST_NOT );
			AscString[79] = LST_KLINEI;
#else
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			AscString[1-1] = LST_KLINEI;
			AttributeSet( &AscString[3-1], &AttString[3-1], PWRD_No, LST_NOT );
			AscString[6-1] = LST_KLINEI;
			AttributeSet( &AscString[7-1], &AttString[7-1], PWRD_RemoteLocation, LST_NOT );
			AscString[23-1] = LST_KLINEI;
  #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/23 Y.Matsukuma */
			AttributeSet( &AscString[36-1], &AttString[36-1], PWRD_Pages, LST_NOT );
  #else
			AttributeSet( &AscString[36-1], &AttString[36-1], PWRD_TeleNumber, LST_NOT );
  #endif
			AscString[64-1] = LST_KLINEI;
			AttributeSet( &AscString[65-1], &AttString[65-1], PWRD_GroupNumber, LST_NOT );
			AscString[80-1] = LST_KLINEI;
 #else	/* PANEL_POPLA_B/L/H */
			AscString[4-1] = LST_KLINEI;
			AttributeSet( &AscString[6-1], &AttString[6-1], PWRD_No, LST_NOT );
			AscString[9-1] = LST_KLINEI;
			AttributeSet( &AscString[14-1], &AttString[14-1], PWRD_RemoteLocation, LST_NOT );
			AscString[34-1] = LST_KLINEI;
			AttributeSet( &AscString[46-1], &AttString[46-1], PWRD_TeleNumber, LST_NOT );
			AscString[75-1] = LST_KLINEI;
 #endif
#endif	/* (PRO_DIAL_LIST_GROUP == ENABLE) */
			break;
		case 2:
			/*†¾†¢†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Æ*/
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			AscString[0] = LST_KLINE4;
			CMN_MemorySet( &AscString[1], 79, LST_KLINE_ );
			AscString[5] = LST_KLINE5;
			AscString[30] = LST_KLINE5;
			AscString[51] = LST_KLINE5;
			AscString[79] = LST_KLINE6;
#else
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_ );
			AscString[6-1] = LST_KLINE5;
			AscString[23-1] = LST_KLINE5;
			AscString[64-1] = LST_KLINE5;
			AscString[80-1] = LST_KLINE6;
 #else	/* PANEL_POPLA_B/L/H */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			AscString[4-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[5-1], 71, LST_KLINE_ );
			AscString[9-1] = LST_KLINE5;
			AscString[34-1] = LST_KLINE5;
			AscString[75-1] = LST_KLINE6;
 #endif
#endif	/* (PRO_DIAL_LIST_GROUP == ENABLE) */
			break;
		case 3:
			/*†¤	†¤		  †¤			†¤			  †¤*/
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
			AscString[0] = LST_KLINEI;
			AscString[5] = LST_KLINEI;
			AscString[30] = LST_KLINEI;
			AscString[51] = LST_KLINEI;
			AscString[79] = LST_KLINEI;
#else
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			AscString[1-1] = LST_KLINEI;
			AscString[6-1] = LST_KLINEI;
			AscString[23-1] = LST_KLINEI;
			AscString[64-1] = LST_KLINEI;
			AscString[80-1] = LST_KLINEI;
 #else	/* PANEL_POPLA_B/L/H */
			AscString[4-1] = LST_KLINEI;
			AscString[9-1] = LST_KLINEI;
			AscString[34-1] = LST_KLINEI;
			AscString[75-1] = LST_KLINEI;
 #endif
#endif	/* (PRO_DIAL_LIST_GROUP == ENABLE) */
			break;
		case 4:
			/*†¶†¢†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†º*/
#if (PRO_DIAL_LIST_GROUP == ENABLE)	/* by K.Watanabe 1999/05/24 */
			AscString[0] = LST_KLINE1;
			CMN_MemorySet( &AscString[1], 79, LST_KLINE_ );
			AscString[5] = LST_KLINE2;
			AscString[30] = LST_KLINE2;
			AscString[51] = LST_KLINE2;
			AscString[79] = LST_KLINE3;
#else
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_ );
			AscString[6-1] = LST_KLINE2;
			AscString[23-1] = LST_KLINE2;
			AscString[64-1] = LST_KLINE2;
			AscString[80-1] = LST_KLINE3;
 #else	/* PANEL_POPLA_B/L/H */
			AscString[4-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[5-1], 71, LST_KLINE_ );
			AscString[9-1] = LST_KLINE2;
			AscString[34-1] = LST_KLINE2;
			AscString[75-1] = LST_KLINE3;
 #endif
#endif	/* (PRO_DIAL_LIST_GROUP == ENABLE) */
			break;
		case 5:
			/*†¤ NO.†¤±²Ã»·Ò² †¤¿Þ¸¾² 1 ¿Þ¸¾² 2 ¿Þ¸¾² 3 ¿Þ¸¾² 4†¤*/
			AscString[4-1] = LST_KLINEI;
			AttributeSet( &AscString[6-1], &AttString[6-1], PWRD_No, LST_NOT );
			AscString[9-1] = LST_KLINEI;
			AttributeSet( &AscString[14-1], &AttString[14-1], PWRD_RemoteLocation, LST_NOT );
			AscString[34-1] = LST_KLINEI;
			for (i = 0; i < 4; i++) {
				CMN_StringCopy(&List.S.Print[37-1+(i * 10)], PWRD_Attribute);
				List.S.Print[43-1+(i * 10)] = (UBYTE)('1' + i);
			}
			AscString[75-1] = LST_KLINEI;
			break;
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* ANZU_L ‚Ì‘®«ƒŠƒXƒg’Ç‰Á‚Ì‚½‚ß Oct.17.1997 Y.Matsukuma */
		case 6:
			AscString[4-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[5-1], 71, LST_KLINE_ );
			AscString[9-1] = LST_KLINE8;
			AscString[34-1] = LST_KLINE8;
			AscString[75-1] = LST_KLINE9;
			break;
		case 7:
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			AscString[4-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[5-1], 71, LST_KLINE_ );
			AscString[9-1] = LST_KLINE5;
			AscString[34-1] = LST_KLINE5;
			AscString[75-1] = LST_KLINE6;
			break;
		case 8:
			AscString[4-1] = LST_KLINEI;
			AscString[9-1] = LST_KLINEI;
			AscString[34-1] = LST_KLINEI;
			AscString[75-1] = LST_KLINEI;
			break;
		case 9:
			AscString[4-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[5-1], 71, LST_KLINE_ );
			AscString[9-1] = LST_KLINE2;
			AscString[34-1] = LST_KLINE2;
			AscString[75-1] = LST_KLINE3;
			break;
#endif
	}
}

/*************************************************************************
	module		:[ƒy[ƒWAŽžŠÔˆóü]
	functiom	:[ƒy[ƒWAŽžŠÔ‚ðˆóü‚·‚éB]
	common		:[
				List			:
				SYB_CurrentTime	:
				Eƒy[ƒWAŽžŠÔˆóüêŠ‚ðŽw’è‚Å‚«‚é‚æ‚¤‚É•ÏX	** 97/06/04 By M.Kuwahara **
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/25]
	author		:[–L“c_Žq]
*************************************************************************/
WORD					PageTimePrint(
						 UBYTE Page,		/*ƒy[ƒW*/
						 UBYTE PagePos,		/*ƒy[ƒWˆóŽšêŠ*/
						 UBYTE TimePos )	/*ŽžŠÔˆóŽšêŠ*/
{
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_MemorySetNULL( List.S.Work, 20, ' ' );
	List.S.Print[PagePos] 	= 'P';
	List.S.Print[PagePos+1] = '.';
	CMN_UnsignedIntToASC( &List.S.Print[PagePos+2], (UWORD)Page, 3, 0 );
	TimeDataAscii( OFF, SYB_CurrentTime, List.S.Work, 0 );
	CMN_StringCopy( &List.S.Print[TimePos], List.S.Work );
	return ( CharacterPrint( LST_PRINT ) );
}

/*************************************************************************
	module		:[ƒy[ƒWˆóü]
	functiom	:[ƒy[ƒW‚ðˆóü‚·‚éB]
	common		:[
				List	:
				Eƒy[ƒWˆóüêŠ‚ðŽw’è‚Å‚«‚é‚æ‚¤‚É•ÏX	** 97/06/04 By M.Kuwahara **
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/25]
	author		:[–L“c_Žq]
*************************************************************************/
WORD					PagePrint(
						 UBYTE Page,		/*ƒy[ƒW*/
						 UBYTE PagePos )	/*ƒy[ƒWˆóŽšêŠ */
{
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_MemorySetNULL( List.S.Work, 20, ' ' );
	List.S.Print[PagePos] = 'P';
	List.S.Print[PagePos+1] = '.';
	CMN_UnsignedIntToASC( List.S.Work, (UWORD)Page, 0, 0 );
	CMN_StringCopy( &List.S.Print[PagePos+2], List.S.Work );
	return ( CharacterPrint( LST_PRINT ) );
}

/*************************************************************************
	module		:[Œ©o‚µˆóüiTTI+ID,‚Qs‰üs+Œ©o‚µ+‚Ps‰üsj]
	functiom	:[Œ©o‚ðˆóü‚·‚éiTTI+ID,‚Qs‰üs+Œ©o‚µ+‚Ps‰üsj]
	common		:[
		List:
	]
	condition	:[]
	commment	:[ƒƒ‚ƒŠß–ñ‚Ìˆ×]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 2/25]
	author		:[–L“c_Žq]
*************************************************************************/
WORD					Print_Head1_Common(
						 CONST UBYTE *PrnString,	/*ƒZƒbƒgŒ³•¶Žš—ñ*/
						 UBYTE Attribute,		/*Cü*/
						 UBYTE LocateX )		/*ƒZƒbƒgŒ³•¶Žš—ñ‚˜•ûŒüƒZƒbƒgˆÊ’u*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs*/
	if ( (ret = TTI_ID_Print_Feed()) != OK ) {
		return ( ret );
	}

	/*Œ©o‚µ*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[LocateX], &List.S.Attribute[LocateX],
	  PrnString, Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

/*************************************************************************
	module		:[‘®«ƒŠƒXƒg‚Ìˆóü]
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
	date		:[1997/05/15]
	author		:[´… ­‹M, ŒKŒ´]
*************************************************************************/
WORD PrintDialAttributeList(
					UBYTE dial_type)		/** ƒƒ“ƒ^ƒbƒ`‚©’Zk‚ÌØ‚è‘Ö‚¦ */
{
	UBYTE max_line;		/** ‚Pƒy[ƒWˆóü‰Â”\s” */
	UBYTE is_1stline;
	UBYTE dial_cnt;
	UBYTE page;
	WORD  ret;

	page     = 0;

	/** “ü—Í‚³‚ê‚Ä‚¢‚éƒf[ƒ^‚ÌŒŸõ */
	switch (dial_type) {
	case LST_SPEEDDIAL_LIST:
		if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
			 for (dial_cnt = 0; dial_cnt < SYS_SPEED_DIAL_MAX; dial_cnt++) {
				if ( SYB_OptionalSpeed[dial_cnt].Number != 0xFFFF ) {
					break;
				}
			}
		}
		else{									/* ’Êí‚Ì’Zk‚ÌŽž */
			for (dial_cnt = 0; dial_cnt < SYS_SPEED_DIAL_MAX; dial_cnt++) {

#if (0)
** 				/* ‚h‚b‚g‚n‚t‚©‚ç‚ÌƒtƒB[ƒhƒoƒbƒN By O.Kimoto 1998/03/30 */
** 				/*
** 				** ƒŠƒ‚[ƒgf’f‚ª–¢“o˜^‚È‚ç‚e‚O‚ð‘‚­ê‡‚ª‚ ‚é‚Ì‚Å‚e‚e‚ÅŒ©‚Ä‚¢‚é‚Æ‚¨‚©‚µ‚­‚È‚é
** 				** 1997/10/03 M.Shimizu
** 				*/
** 				if ( SYB_SpeedDial[dial_cnt].Dial[0] != LST_DIAL_NOT ) [
** 					break;
** 				]
#else
			if ( (SYB_SpeedDial[dial_cnt].Dial[0] & 0xF0) != 0xF0 ) {
				break;
			}
#endif
			}
		}
		break;
	case LST_ONETOUCHDIAL_LIST:
	default:
		for (dial_cnt = 0; dial_cnt < SYS_ONETOUCH_MAX; dial_cnt++) {

#if (0)
** 			/* ‚h‚b‚g‚n‚t‚©‚ç‚ÌƒtƒB[ƒhƒoƒbƒN By O.Kimoto 1998/03/30 */
** 			/*
** 			** ƒŠƒ‚[ƒgf’f‚ª–¢“o˜^‚È‚ç‚e‚O‚ð‘‚­ê‡‚ª‚ ‚é‚Ì‚Å‚e‚e‚ÅŒ©‚Ä‚¢‚é‚Æ‚¨‚©‚µ‚­‚È‚é
** 			** 1997/10/03 M.Shimizu
** 			*/
** 			if ( SYB_OnetouchDial[dial_cnt].Dial[0] != LST_DIAL_NOT ) [
** 				break;
** 			]
#else
 #if (0)
 //			’Zkƒ_ƒCƒ„ƒ‹‚ª‚PŒ‚à“o˜^‚³‚ê‚Ä‚¢‚È‚¢ŽžA
 //			ƒƒ“ƒ^ƒbƒ`ƒ_ƒCƒ„ƒ‹‘®«ƒŠƒXƒg‚Ì–¾×‚ªˆóü‚³‚ê‚È‚¢•s‹ï‡C³BBy H.Fujimura 2003/05/20
 //
 //			if ( (SYB_SpeedDial[dial_cnt].Dial[0] & 0xF0) != 0xF0 ) {
 #else
			if ( (SYB_OnetouchDial[dial_cnt].Dial[0] & 0xF0) != 0xF0 ) {
 #endif
				break;
			}
#endif
		}
		break;
	}

	while (1) {
		page++;
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		if ( page == 1 ) {
			/** ƒwƒbƒ_ˆóü */
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			if ( (ret = Print_Head1_Common( PWRD_AttributeList_K,
			 LST_NOT,19-1 )) != OK ) {
				return ( ret );
			}
#else
			if ( (ret = Print_Head1_Common( PWRD_AttributeList,
			  LST_XXX_TWI_XXX, 19-1 )) != OK ) {
			    return ( ret );
			}
#endif
			/*Page Œ»ÝŽžŠÔ*/
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			if ( (ret = PageTimePrint( page, 5-1, 55-1 )) != OK ) {
				return ( ret );
			}
			Print_Dial_List_Line( 6, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
#else
			if ( (ret = PageTimePrint( page, 5-1, 55-1 )) != OK ) {
				return ( ret );
			}
			Print_Dial_List_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
#endif
			Print_Dial_List_Line( 5, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			max_line = (UBYTE)(PaperSizeLen() - 11);
		}
		else {
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
			if ( (ret = PagePrint( page, 5 - 1 )) != OK ) {
				return ( ret );
			}
			max_line = (UBYTE)(PaperSizeLen() - 4);
		}
		is_1stline = TRUE;

		switch (dial_type) {
		case LST_SPEEDDIAL_LIST:
			while (dial_cnt < SYS_SPEED_DIAL_MAX) {
				if ( (ret = PrintSpeedDialAttrSpecifi(is_1stline, page, dial_cnt)) != OK) {
					return (ret);
				}
				dial_cnt++;
				is_1stline = FALSE;

				/** ŽŸ‚Ìƒf[ƒ^‚ðŒŸõ */
				if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
					for (; dial_cnt < SYS_SPEED_DIAL_MAX; dial_cnt++) {
						if ( SYB_OptionalSpeed[dial_cnt].Number != 0xFFFF ) {
							break;
						}
					}
				}
				else{									/* ’Êí‚Ì’Zk‚ÌŽž */
					for (; dial_cnt < SYS_SPEED_DIAL_MAX; dial_cnt++) {

#if (0)
** 						/* ‚h‚b‚g‚n‚t‚©‚ç‚ÌƒtƒB[ƒhƒoƒbƒN By O.Kimoto 1998/03/30 */
** 						/*
** 						** ƒŠƒ‚[ƒgf’f‚ª–¢“o˜^‚È‚ç‚e‚O‚ð‘‚­ê‡‚ª‚ ‚é‚Ì‚Å‚e‚e‚ÅŒ©‚Ä‚¢‚é‚Æ‚¨‚©‚µ‚­‚È‚é
** 						** 1997/10/03 M.Shimizu
** 						*/
** 						if ( SYB_SpeedDial[dial_cnt].Dial[0] != LST_DIAL_NOT ) [
** 							break;
** 						]
#else
						if ( (SYB_SpeedDial[dial_cnt].Dial[0] & 0xF0) != 0xF0 ) {
							break;
						}
#endif

					}
				}
				max_line -= 2;
				if ((char)max_line < 2) {
					break;
				}
			}

#if (PRO_KEYPANEL == PANEL_ANZU_L)
			Print_Dial_List_Line( 9, List.S.Print, List.S.Attribute );
#else
			Print_Dial_List_Line( 4, List.S.Print, List.S.Attribute );
#endif
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
				return ( ret );
			}
			if (dial_cnt >= SYS_SPEED_DIAL_MAX) {
				return(OK);
			}
			break;

		case LST_ONETOUCHDIAL_LIST:
		default:
			while(dial_cnt < SYS_ONETOUCH_MAX) {
				if ( (ret = PrintOnetouchDialAttrSpecifi(is_1stline, page, dial_cnt)) != OK) {
					return (ret);
				}
				dial_cnt++;
				is_1stline = FALSE;

				/** ŽŸ‚Ìƒf[ƒ^‚ðŒŸõ */
				for (; dial_cnt < SYS_ONETOUCH_MAX; dial_cnt++) {

#if (0)
** 					/* ‚h‚b‚g‚n‚t‚©‚ç‚ÌƒtƒB[ƒhƒoƒbƒN By O.Kimoto 1998/03/30 */
** 					/*
** 					** ƒŠƒ‚[ƒgf’f‚ª–¢“o˜^‚È‚ç‚e‚O‚ð‘‚­ê‡‚ª‚ ‚é‚Ì‚Å‚e‚e‚ÅŒ©‚Ä‚¢‚é‚Æ‚¨‚©‚µ‚­‚È‚é
** 					** 1997/10/03 M.Shimizu
** 					*/
** 					if ( SYB_OnetouchDial[dial_cnt].Dial[0] != LST_DIAL_NOT ) [
** 						break;
** 					]
#else
					if ( (SYB_OnetouchDial[dial_cnt].Dial[0] & 0xF0) != 0xF0 ) {
						break;
					}
#endif

				}
				max_line -= 2;
				if ((char)max_line < 2) {
					break;
				}
			}

#if (PRO_KEYPANEL == PANEL_ANZU_L)
			Print_Dial_List_Line( 9, List.S.Print, List.S.Attribute );
#else
			Print_Dial_List_Line( 4, List.S.Print, List.S.Attribute );
#endif
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
				return ( ret );
			}
			if (dial_cnt >= SYS_ONETOUCH_MAX) {
				return(OK);
			}
		}
	}

}

/*************************************************************************
	module		:[’Zkƒ_ƒCƒ„ƒ‹‘®«ˆê–¾×ˆóü]
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
	date		:[1997/05/15]
	author		:[´… ­‹M]
*************************************************************************/
WORD	PrintSpeedDialAttrSpecifi(
					UBYTE is_page1st,	/** ƒy[ƒW‚Ìæ“ª */
					UBYTE page,
					UBYTE pos)
{
	WORD  ret;
	UBYTE i;
	UBYTE bit;

#if (PRO_KEYPANEL == PANEL_ANZU_L) /* 1997/10/17 Y.Matsukuma */
	Print_Dial_List_Line( 7, List.S.Print, List.S.Attribute );
	if (page > 1 && is_page1st == TRUE) {	/** ‚Qƒy[ƒWˆÈ~‚Ìæ“ª‚È‚ç */
		Print_Dial_List_Line( 6, List.S.Print, List.S.Attribute );
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	Print_Dial_List_Line( 8, List.S.Print, List.S.Attribute );
	if ( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
		if ( SYS_SPEED_DIAL_MAX > 100 ) {
			CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)SYB_OptionalSpeed[pos].Number, 3, '0' );
		}
		else {
			CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)SYB_OptionalSpeed[pos].Number, 2, '0' );
		}
		/*‘ŠŽèæ–¼*/
		CMN_StringCopy( &List.S.Print[10-1], SYB_SpeedDial[SYB_OptionalSpeed[pos].Record].Name );
	}
	else {
		/* No. */
		if ( SYS_SPEED_DIAL_MAX > 100 ) {
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
			CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(pos)+(OPR_SPEED_DIAL_MIN), 3, '0' );
 #else
			CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(pos), 3, '0' );
 #endif
		}
		else {
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
			CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(pos)+(OPR_SPEED_DIAL_MIN), 2, '0' );
 #else
			CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(pos), 2, '0' );
 #endif
		}
		/*‘ŠŽèæ–¼*/
		CMN_StringCopy( &List.S.Print[10-1], SYB_SpeedDial[pos].Name ); /* By M.Kuwahara 1997/01/22*/
	}

#elif (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (F250‚Í’Zkƒ_ƒCƒ„ƒ‹‚ÍÅ‘å80Œ‚Å‚·‚©‚çA’ZkÀÞ²ÔÙNoA‚ªS01AS02`S80‚Ü‚Å‚É•ÏX‚·‚é‚±‚Æ) Added by SMuratec L.Z.W 2003/10/09 */

	Print_Dial_List_Line( 2, List.S.Print, List.S.Attribute );
	if (page > 1 && is_page1st == TRUE) {	/** ‚Qƒy[ƒWˆÈ~‚Ìæ“ª‚È‚ç */
		Print_Dial_List_Line( 0, List.S.Print, List.S.Attribute );
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	Print_Dial_List_Line( 3, List.S.Print, List.S.Attribute );

	if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
 #if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
		List.S.Print[5-1]	= *CalculateStringAddress(&D2W_HeadCharacter_Speed);
 #else
		List.S.Print[5-1]	= 'S';
 #endif
		CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)SYB_OptionalSpeed[pos].Number, OP_SPEED_FIGURE_MAX, '0' );
		/*‘ŠŽèæ–¼*/
		CMN_StringCopy( &List.S.Print[10-1], SYB_SpeedDial[SYB_OptionalSpeed[pos].Record].Name );
	}
	else {
		/* No. */
 #if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
		List.S.Print[5-1] = *CalculateStringAddress(&D2W_HeadCharacter_Speed);
 #else
		List.S.Print[5-1] = 'S';
 #endif
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
		CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(pos)+(OPR_SPEED_DIAL_MIN), OP_SPEED_FIGURE_MAX, '0' );
 #else
		CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(pos), OP_SPEED_FIGURE_MAX, '0' );
 #endif
		/*‘ŠŽèæ–¼*/
		CMN_StringCopy( &List.S.Print[10-1], SYB_SpeedDial[pos].Name );
	}
#else/* PANEL_POPLA_B/L/H */

	Print_Dial_List_Line( 2, List.S.Print, List.S.Attribute );
	if (page > 1 && is_page1st == TRUE) {	/** ‚Qƒy[ƒWˆÈ~‚Ìæ“ª‚È‚ç */
		Print_Dial_List_Line( 0, List.S.Print, List.S.Attribute );
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	Print_Dial_List_Line( 3, List.S.Print, List.S.Attribute );

	if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
 #if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
		List.S.Print[5-1]	= *CalculateStringAddress(&D2W_HeadCharacter_Speed);
 #else
		List.S.Print[5-1]	= 'S';
 #endif
		CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)SYB_OptionalSpeed[pos].Number, 3, '0' );
		/*‘ŠŽèæ–¼*/
		CMN_StringCopy( &List.S.Print[10-1], SYB_SpeedDial[SYB_OptionalSpeed[pos].Record].Name );
	}
	else {
		/* No. */
 #if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
		List.S.Print[5-1] = *CalculateStringAddress(&D2W_HeadCharacter_Speed);
 #else
		List.S.Print[5-1] = 'S';
 #endif
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
		CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(pos)+(OPR_SPEED_DIAL_MIN), 3, '0' );
 #else
		CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(pos), 3, '0' );
 #endif
		/*‘ŠŽèæ–¼*/
		CMN_StringCopy( &List.S.Print[10-1], SYB_SpeedDial[pos].Name );
	}
#endif

	/* ‘®«ƒZƒbƒg */
	bit = 0x80;
	for (i = 0; i < 8; i++) {
#if (0)	/* ”CˆÓ’Zk‚ÌŽž‚Ìˆ—‚ª“ü‚Á‚Ä‚È‚©‚Á‚½‚Ì‚ÅA’Ç‰Á‚µ‚Ü‚· by K.Watanabe 1998/07/02 */
//		List.S.Print[36-1 + i] = (UBYTE)((SYB_SpeedDial[pos].Attribute1 & bit) ? '1' : '0');
//		List.S.Print[46-1 + i] = (UBYTE)((SYB_SpeedDial[pos].Attribute2 & bit) ? '1' : '0');
//		List.S.Print[56-1 + i] = (UBYTE)((SYB_SpeedDial[pos].Attribute3 & bit) ? '1' : '0');
//		List.S.Print[66-1 + i] = (UBYTE)((SYB_SpeedDial[pos].Attribute4 & bit) ? '1' : '0');
#endif
		if (CHK_UNI_OptionalSpeedDial()) {	/* ”CˆÓ’Zk‚ÌŽž */
			List.S.Print[36-1 + i] = (UBYTE)((SYB_SpeedDial[SYB_OptionalSpeed[pos].Record].Attribute1 & bit) ? '1' : '0');
			List.S.Print[46-1 + i] = (UBYTE)((SYB_SpeedDial[SYB_OptionalSpeed[pos].Record].Attribute2 & bit) ? '1' : '0');
			List.S.Print[56-1 + i] = (UBYTE)((SYB_SpeedDial[SYB_OptionalSpeed[pos].Record].Attribute3 & bit) ? '1' : '0');
			List.S.Print[66-1 + i] = (UBYTE)((SYB_SpeedDial[SYB_OptionalSpeed[pos].Record].Attribute4 & bit) ? '1' : '0');
		}
		else {								/* ’Êí’Zk‚ÌŽž */
			List.S.Print[36-1 + i] = (UBYTE)((SYB_SpeedDial[pos].Attribute1 & bit) ? '1' : '0');
			List.S.Print[46-1 + i] = (UBYTE)((SYB_SpeedDial[pos].Attribute2 & bit) ? '1' : '0');
			List.S.Print[56-1 + i] = (UBYTE)((SYB_SpeedDial[pos].Attribute3 & bit) ? '1' : '0');
			List.S.Print[66-1 + i] = (UBYTE)((SYB_SpeedDial[pos].Attribute4 & bit) ? '1' : '0');
		}
		bit >>= 1;
	}

	return (CharacterPrint( LST_PRINT ));
}


/*************************************************************************
	module		:[ƒƒ“ƒ^ƒbƒ`ƒ_ƒCƒ„ƒ‹‘®«ˆê–¾×ˆóü]
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
	date		:[1997/05/15]
	author		:[´… ­‹M]
*************************************************************************/
WORD PrintOnetouchDialAttrSpecifi(
			UBYTE	is_page1st,	/** ƒy[ƒW‚Ìæ“ª */
			UBYTE	page,		/** ƒy[ƒW */
			UBYTE	pos)		/** ƒƒ“ƒ^ƒbƒ`”Ô† */
{
	WORD 	ret;
	UBYTE 	i;
	UBYTE	bit;

#if (PRO_KEYPANEL == PANEL_ANZU_L) /* 1997/10/17 Y.Matsukuma */
	Print_Dial_List_Line( 7, List.S.Print, List.S.Attribute );
	if (page > 1 && is_page1st == TRUE) {	/** ‚Qƒy[ƒWˆÈ~‚Ìæ“ª‚È‚ç */
		Print_Dial_List_Line( 6, List.S.Print, List.S.Attribute );
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	Print_Dial_List_Line( 8, List.S.Print, List.S.Attribute );
	if ( CMN_OffsetToOnetouchCode( pos ) <= 0x7A ){ /* ÜÝÀ¯Á‹L†‚ª•ÏX(ANZU) 96/01/10 H.HIRAO */
		List.S.Print[5-1] = CMN_OffsetToOnetouchCode( pos );
	} else{
		List.S.Print[5-1] = 0x55;	/* 'U'‚ÌASCIIº-ÄÞ */
		List.S.Print[6-1] = CMN_OffsetToOnetouchCode( pos ) & (UBYTE)0x0F | (UBYTE)0x30; /* U1`U8‹L†‚ð‚Â‚­‚é */
	}
	/*‘ŠŽèæ–¼*/
	CMN_StringCopy( &List.S.Print[10-1], SYB_OnetouchDial[pos].Name ); /* 97/01/22 M.Kuwahara */

#else /* PANEL_POPLA_B/L/H */
	Print_Dial_List_Line( 2, List.S.Print, List.S.Attribute );
	if (page > 1 && is_page1st == TRUE) {	/** ‚Qƒy[ƒWˆÈ~‚Ìæ“ª‚È‚ç */
		Print_Dial_List_Line( 0, List.S.Print, List.S.Attribute );
	}
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	Print_Dial_List_Line( 3, List.S.Print, List.S.Attribute );
 #if (PRO_PANEL == ANK)
	List.S.Print[5-1] = '[';
	List.S.Print[8-1] = ']';
	CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)(CMN_OffsetToOnetouchCode( pos ) - 0x40), 2, '0' );
 #endif
 #if (PRO_PANEL == KANJI)
	/* ƒƒ“ƒ^ƒbƒ`‚Ì•\Ž¦‚ð[]->ŠG•¶Žš‚É•ÏX By O.Kimoto 1998/01/22 */
	List.S.Print[5-1] = LCD_PICFONT;
	List.S.Print[6-1] = LCD_PICFONT_LOWER;
	CMN_UnsignedIntToASC( &List.S.Print[7-1], (UWORD)(CMN_OffsetToOnetouchCode( pos ) - 0x40), 2, '0' );
 #endif

	/*‘ŠŽèæ–¼*/
	CMN_StringCopy( &List.S.Print[10-1], SYB_OnetouchDial[pos].Name ); /* •ÏX(ANZU) 95/12/14 H.HIRAO */
#endif

	/* ‘®« */
	bit = 0x80;
	for (i = 0; i < 8; i++) {
		List.S.Print[36-1 + i] = (UBYTE)((SYB_OnetouchDial[pos].Attribute1 & bit) ? '1' : '0');
		List.S.Print[46-1 + i] = (UBYTE)((SYB_OnetouchDial[pos].Attribute2 & bit) ? '1' : '0');
		List.S.Print[56-1 + i] = (UBYTE)((SYB_OnetouchDial[pos].Attribute3 & bit) ? '1' : '0');
		List.S.Print[66-1 + i] = (UBYTE)((SYB_OnetouchDial[pos].Attribute4 & bit) ? '1' : '0');
		bit >>= 1;
	}
	return (CharacterPrint( LST_PRINT ));
}
