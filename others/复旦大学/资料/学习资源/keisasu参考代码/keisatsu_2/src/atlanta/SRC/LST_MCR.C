/*************************************************************************
*	System		: SAKAKI
*	File Name	: LST_MCR.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1998/05/19
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒL[ƒ}ƒNƒƒRƒƒ“ƒgƒŠƒXƒg
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysmailb.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"

#if	( PRO_PANEL == ANK )
#include "\src\atlanta\opr\ank\define\opr_def.h"
#endif
#if	( PRO_PANEL == KANJI )
#include "\src\atlanta\opr\kanji\define\opr_def.h"
#endif


#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/24 By M.Kuwahara */
/*************************************************************************
	module		:[ƒL[ƒ}ƒNƒƒRƒƒ“ƒgƒŠƒXƒg]
	function	:[ƒL[ƒ}ƒNƒƒRƒƒ“ƒgƒŠƒXƒg‚ðˆóü‚·‚é]
	common		:[
		List		:
		SYB_KeyMacro
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/05/19]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD				Print_KeyMacro_List(
						 void )				/*‚È‚µ*/
{
	UBYTE	i;						/*loop*/
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	/*ÃÞ°À‚È‚µÁª¯¸*/
	for ( i = 0; i < SYS_KEYMACRO_MAX; i++ ) {
		if (( SYB_KeyMacro[i].Step[0] != 0xFF ) ||	
			( SYB_KeyMacro[i].Title[0] != 0x00)) {
			break;
		}
	}
	if ( i == SYS_KEYMACRO_MAX ) {
		return ( MSG_PRN_LST_NO_LIST );
	}

	if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
		return ( ret );
	}

	/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs{Œ©o‚µ{‚P‰üs*/
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		if ( (ret = Print_Head1_Common( PWRD_KeyMacroList_K, LST_NOT, 23-1 )) != OK ) {
			return ( ret );
		}
#else
	if ( (ret = Print_Head1_Common( PWRD_KeyMacroList, LST_XXX_TWI_XXX, 18-1 )) != OK ) {
		return ( ret );
	}
#endif

	/*Œ»ÝŽžŠÔ*/
	if ( (ret = CurrentTimePrint( 42-1 )) != OK ) {
		return ( ret );
	}

	/*†®†¢†Î†¢†¢†¢†¢†¢†²*/
	Print_KeyMacroList_Line( 0, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¤ No.†¤  À²ÄÙ   †¤*/
	Print_KeyMacroList_Line( 1, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	for ( i = 0; i < SYS_KEYMACRO_MAX; i++ ) {
		if (( SYB_KeyMacro[i].Step[0] != 0xFF ) ||	/* ƒXƒeƒbƒv‚©ƒRƒƒ“ƒg‚ª“o˜^‚³‚ê‚Ä‚¢‚éŽž */
			( SYB_KeyMacro[i].Title[0] != 0x00 )) {
			/*†¾†¢†¢†Þ†¢†¢†¢†Æ*/
			Print_KeyMacroList_Line( 2, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤ 9 †¤xxxxxx†¤*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[19-1] = LST_KLINEI;
#if (PRO_PANEL == ANK)
			List.S.Print[20-1] = '[';
			List.S.Print[23-1] = ']';
			CMN_UnsignedIntToASC( &List.S.Print[21-1], (UWORD)i+26, 2, '0' );
#endif
#if (PRO_PANEL == KANJI)
			List.S.Print[20-1] = LCD_PICFONT;
			List.S.Print[23-1] = LCD_PICFONT_LOWER;
			CMN_UnsignedIntToASC( &List.S.Print[21-1], (UWORD)i+26, 2, '0' );
#endif
			List.S.Print[24-1] = LST_KLINEI;
			if (SYB_KeyMacro[i].Title[0] == 0x00) {		/* ƒ^ƒCƒgƒ‹–³‚µ‚ÌŽž */
				AttributeSet( &List.S.Print[25-1], &List.S.Attribute[25-1], PWRD_NoTitle, LST_NOT );
			}
			else{
				CMN_StringCopy(&List.S.Print[25-1], SYB_KeyMacro[i].Title );
			}
			List.S.Print[62-1] = LST_KLINEI;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
	}
	/*†¶†¢†¢†Ö†¢†¢†¢†¢†º*/
	Print_KeyMacroList_Line( 3, List.S.Print, List.S.Attribute );
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
	return ( OK );
}

/*************************************************************************
	module		:[ƒL[ƒ}ƒNƒƒ^ƒCƒgƒ‹ƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrüì¬]
	function	:[ƒL[ƒ}ƒNƒƒ^ƒCƒgƒ‹ƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB
	common		:[]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[98/05/19]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
void			Print_KeyMacroList_Line(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†Î†¢†¢†¢†¢†¢†²*/
			AscString[19-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[20-1], 43, LST_KLINE_ );
			AscString[24-1] = LST_KLINE8;
			AscString[62-1] = LST_KLINE9;
			break;
		case 1:
			/*†¤No.†¤  À²ÄÙ  †¤*/
			AscString[19-1] = LST_KLINEI;
			AttributeSet( &AscString[21-1], &AttString[21-1], PWRD_No, LST_NOT );
			AscString[24-1] = LST_KLINEI;
			AttributeSet( &AscString[40-1], &AttString[40-1], PWRD_Title, LST_NOT );
			AscString[62-1] = LST_KLINEI;
			break;
		case 2:
			/*†¾†¢†¢†Þ†¢†¢†¢†Æ*/
			AscString[19-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[20-1], 43, LST_KLINE_ );
			AscString[24-1] = LST_KLINE5;
			AscString[62-1] = LST_KLINE6;
			break;
		case 3:
			/*†¶†¢†¢†Ö†¢†¢†¢†¢†º*/
			AscString[19-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[20-1], 43, LST_KLINE_ );
			AscString[24-1] = LST_KLINE2;
			AscString[62-1] = LST_KLINE3;
			break;
	}
}

#endif
