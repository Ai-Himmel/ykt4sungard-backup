/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_MSGC.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒ`ƒFƒbƒNƒƒbƒZ[ƒW‚b ƒƒ‚ƒŠƒI[ƒo[
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"
#include "\src\atlanta\define\sys_stat.h"	/* 98/02/12 By M.Kuwahara */

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_v\sys_data.h"

#if (PRO_PC_PRINT == ENABLE)	/* by T.Soneoka 1997/08/13 */
/*************************************************************************
	module		:[PCƒƒ‚ƒŠƒI[ƒo[ˆóü]
	function	:[PCƒƒ‚ƒŠƒI[ƒo[‚ðˆóü‚·‚é]
	common		:[
		SYS_PcMemoryOverListRequest	;
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[Aug.13.1997]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
WORD				Print_PcMryOver_ChkMsg(void)
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/* “ú•t’Ç‰Á‚µ‚Ü‚µ‚½ by T.Soneoka 1997/09/04 */
	/*Œ»ÝŽžŠÔ*/
	if ( (ret = CurrentTimePrint( 60-1 )) != OK ) {
		return ( ret );
	}
	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[26-1] = LST_KLINE7;
	CMN_MemorySet( &List.S.Print[27-1], 30, LST_KLINE_ );
	List.S.Print[56-1] = LST_KLINE9;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¤@ƒƒ‚ƒŠƒI[ƒo[@		†¤*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[26-1] = LST_KLINEI;
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
	AttributeSet( &List.S.Print[27-1], &List.S.Attribute[27-1],
	  PWRD_PcMemoryOver_K, LST_NOT );
#else
	AttributeSet( &List.S.Print[27-1], &List.S.Attribute[27-1],
	  PWRD_PcMemoryOver, LST_MES_TWI_XXX );
#endif

	List.S.Print[56-1] = LST_KLINEI;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[26-1] = LST_KLINE1;
	CMN_MemorySet( &List.S.Print[27-1], 30, LST_KLINE_ );
	List.S.Print[56-1] = LST_KLINE3;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}

	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}
	SYS_PcMemoryOverListRequest = 0;
	SYS_PcMemoryOverDispRequest = 0;
	SYS_MachineStatus[SYS_ERROR_STATUS] &= ~SYS_ERROR_PC_MEMORY_OVER;/* 1998/02/12 By M.Kuwahara */
	return ( OK );
}
#endif

/*************************************************************************
	module		:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWC ƒƒ‚ƒŠƒI[ƒo[ˆóü]
	function	:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWC ƒƒ‚ƒŠƒI[ƒo[‚ðˆóü‚·‚é]
	common		:[
		List						:
		SYB_CommandFile				:
		SYS_MemoryOverListRequest	;
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
WORD				Print_MryOver_ChkMsg(
						 UBYTE ComNumber )	/*ƒRƒ}ƒ“ƒhƒtƒ@ƒCƒ‹”Ô†(0-)*/
{
/*	UBYTE	prog_line;				/*ÌßÛ¸Þ×ÑÃÞ°Às”*/
	UBYTE	i;						/*loop*/
	UBYTE	page;
	UBYTE	line_cnt;
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	DialCheckPointer    = SYS_DIRECT_DIAL;	/** Ží•Êƒ|ƒCƒ“ƒ^‚ð‰Šú‰»   */
	DialCheckBitPointer = 0;				/** ƒrƒbƒgƒ|ƒCƒ“ƒ^‚ð‰Šú‰» */
	i		= 0;
	page	= 1;

	while( 1 ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}

		if ( page == 1 ) {
			line_cnt = (UBYTE)(PaperSizeLen() - 9); /** ˆóü‰Â”\s”¾¯Ä */
			/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[26-1] = LST_KLINE7;
			CMN_MemorySet( &List.S.Print[27-1], 26, LST_KLINE_ );
			List.S.Print[53-1] = LST_KLINE9;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤@ƒƒ‚ƒŠƒI[ƒo[@		†¤*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[26-1] = LST_KLINEI;
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
				AttributeSet( &List.S.Print[29-1], &List.S.Attribute[29-1],
				  PWRD_MemoryOver_K, LST_NOT );		/* MES¨INV 94.7.20 ->NOT 8.10 */
#else
			AttributeSet( &List.S.Print[29-1], &List.S.Attribute[29-1],
			  PWRD_MemoryOver, LST_MES_TWI_XXX );
#endif

			List.S.Print[53-1] = LST_KLINEI;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[26-1] = LST_KLINE1;
			CMN_MemorySet( &List.S.Print[27-1], 26, LST_KLINE_ );
			List.S.Print[53-1] = LST_KLINE3;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
			/*Œ»ÝŽžŠÔ*/
			if ( (ret = CurrentTimePrint( 60-1 )) != OK ) {
				return ( ret );
			}
		}
		else{
			line_cnt = (UBYTE)(PaperSizeLen() - 5); /** ˆóü‰Â”\s”¾¯Ä */
			/*‚QsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED + 2 )) != OK ) {
				return ( ret );
			}
		}
/*
** Œ´e’~Ï‚É‚ÄAÏ‚ÝƒXƒ^ƒ“ƒv‚ð‰Ÿ‚³‚È‚¢ê‡A‚Pƒy[ƒW“Ç‚ÝŽæ‚èŠ®—¹‚·‚é‘O‚ÉAŒ´e”roŠ®—¹‚·‚éŽd—l•ÏX‚Ì‚½‚ß
** ƒƒ‚ƒŠƒI[ƒo‚µ‚½ê‡Aƒƒ‚ƒŠƒI[ƒoƒƒbƒZ[ƒW‚ðƒvƒŠƒ“ƒg‚·‚é‚æ‚¤‚É‚È‚Á‚½
** ƒƒ‚ƒŠƒI[ƒoƒƒbƒZ[ƒW‚ª•K—v‚È‚Ì‚Í
** Eƒ}ƒ‹ƒ`ƒRƒs[
** Eƒƒ‚ƒŠ‚s‚˜
** Eƒ|[ƒŠƒ“ƒO’~Ï
** EˆêŠ‡‘—M
** E‚eƒR[ƒh’~Ï
** ‚ÅA‰º‹LAhƒtƒB[ƒ_‘—M‚µ‚Ä‚­‚¾‚³‚¢hƒƒbƒZ[ƒW‚ðo‚·‚ÆˆÓ–¡•s–¾‚É‚È‚é‚à‚Ì‚ª‚ ‚é‚Ì‚ÅÁ‹Ž‚µ‚Ü‚·
**  1999/02/24 by T.Soneoka
*/
#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)
		DialCheckPointer = SYS_EMPTY_DIAL;
#else
		/*†®†¢†¢†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†¢†²*/
		Print_MryOver_ChkMsg_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*†¤ÒÓØ¿³¼ÝÃÞ·Ï¾ÝÃÞ¼À@Ì¨°ÀÞ°¿³¼Ý¼Ã¸ÀÞ»²†¤xxxxxxxxxx†¤*/
		while (DialCheckPointer != SYS_EMPTY_DIAL) {	/* 97/09/08 By M.Kuwahara */
			if ( line_cnt <= 0 ) {
				break;
			}
			Print_MryOver_ChkMsg_Line( 1, List.S.Print, List.S.Attribute );
			if ((( page == 1 ) && (line_cnt == (PaperSizeLen() - 9))) || /* ƒy[ƒW‚Ìæ“ª */
			    (( page != 1 ) && (line_cnt == (PaperSizeLen() - 5)))) {
				AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1],
				  PWRD_MryOverFeeder, LST_NOT );
			}
			ProgramDataDialToString(
			  (struct SYS_DialData_t *)&SYB_CommandFile[ComNumber].DialNumber,
			  SYS_PRG_DIAL_MAX, List.S.Work, i );
			CMN_StringCopy( &List.S.Print[40-1], List.S.Work );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			line_cnt--;
			i++;
		}

		/*†¶†¢†¢†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†º*/
		Print_MryOver_ChkMsg_Line( 2, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
#endif

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}

		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}

		if (DialCheckPointer == SYS_EMPTY_DIAL) {
			break;
		}
		page++;
	}
	SYS_MemoryOverListRequest = 0;
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/19 Y.Murata for KAKI */
	SYS_MemoryOverListPage = 0;
#endif
	return ( OK );
}

/*************************************************************************
	module		:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWC ƒƒ‚ƒŠƒI[ƒo[‰¡‹æØŒrüì¬]
	function	:[ƒ`ƒFƒbƒNƒƒbƒZ[ƒWC ƒƒ‚ƒŠƒI[ƒo[‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
			0 = †®†¢†¢†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†¢†²
			1 = †¤			  †¤			  †¤
			2 = †¶†¢†¢†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†¢†º
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
void			Print_MryOver_ChkMsg_Line(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†¢†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†¢†²*/
			List.S.Print[ 1-1] = LST_KLINE7;
			CMN_MemorySet( &List.S.Print[2-1], 78, LST_KLINE_ );
			List.S.Print[39-1] = LST_KLINE8;
			List.S.Print[80-1] = LST_KLINE9;
			break;
		case 1:
			/*†¤			†¤				†¤*/
			List.S.Print[ 1-1] = LST_KLINEI;
			List.S.Print[39-1] = LST_KLINEI;
			List.S.Print[80-1] = LST_KLINEI;
			break;
		case 2:
			/*†¶†¢†¢†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†¢†º*/
			List.S.Print[ 1-1] = LST_KLINE1;
			CMN_MemorySet( &List.S.Print[2-1], 78, LST_KLINE_ );
			List.S.Print[39-1] = LST_KLINE2;
			List.S.Print[80-1] = LST_KLINE3;
			break;
	}
}
