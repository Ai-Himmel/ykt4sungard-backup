/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_CODE.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: •”–åŠÇ—Ø½Ä
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
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_v\sys_data.h"


#if (PRO_COST == ENABLE) || (PRO_DEPART_NEW_LIST == ENABLE)	/* •”–åŠÇ—ƒŠƒXƒgiŠÇ——¿‹àŠÇ—ƒŠƒXƒgj By O.Kimoto 1997/11/29 */
/*************************************************************************
	module		:[•”–åŠÇ—ƒŠƒXƒgˆóü]
	functiom	:[•”–åŠÇ—ƒŠƒXƒg‚ðˆóü‚·‚é]
	common		:[
		List				:
		SYB_DepartFile		:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 9]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Print_DepartData_List(
						 void )		/* ‚È‚µ */
{
	register WORD	ret;							/*ŽÀsŒ‹‰Ê*/
	UBYTE	page;							/*Íß°¼Þ*/
	UBYTE 	i;								/*loop*/
	UBYTE	code_cnt;						/*º°ÄÞÃÞ°À”Ô†*/
	UBYTE	line_cnt;						/*Žc‚èˆóü‰Â”\s”*/

	page = 1;
	code_cnt = 0;
	DepartDataNextSearch( &code_cnt ); /*ÃÞ°À“ªo‚µ*/
	while ( code_cnt != SYS_DEPART_MAX ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		if ( page == 1 ) {
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		else {
			line_cnt = (UBYTE)(PaperSizeLen() - 4);/*ˆóü‰Â”\s”¾¯Ä*/
		}

		if ( (ret = Print_DepartData_List_Head( 0, page ) )
		  != OK ) {												/*Í¯ÀÞˆóü*/
			return ( ret );
		}
		for ( i = 0; line_cnt >= 2; i++, line_cnt -= 2 ) {
			if ( (ret = Print_DepartData_List_Specifi( page, i,
			  code_cnt ) ) != OK ) {/*1–¾×ˆóü*/
				return ( ret );
			}
			code_cnt++;
			DepartDataNextSearch( &code_cnt ); /*ŽŸÃÞ°À»°Á*/
			if ( code_cnt == SYS_DEPART_MAX ) {
				break;
			}
		}
		if ( (ret = Print_DepartData_List_Head( 1, page ))
		  != OK ) {												/*Ì¯Àˆóü*/
			return ( ret );
		}
		if ( code_cnt != SYS_DEPART_MAX ) {
			DepartDataNextSearch( &code_cnt );
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	
#if (0)  /* 97/02/18 by T.Soneoka */
//	if( SYS_DepartmentListRequest == 1 ) {	/* Ž©“®ÌßØÝÄ‚ÌŽž‚ÉA—¿‹à¤–‡”‚ð */
//		CMN_ClearCostData();				/* ¸Ø±‚·‚éB */
//		SYS_DepartmentListRequest = 0;
//	}
#else
	if( SYS_DepartmentClearRequest == 1 ) {	/* Ž©“®ÌßØÝÄ‚ÌŽž‚ÉA—¿‹à¤–‡”‚ð */

#if (PRO_COST == ENABLE)	/* Add By O.Kimoto 1997/11/29 */
		CMN_ClearCostData();				/* ¸Ø±‚·‚éB */
#endif

		SYS_DepartmentClearRequest = 0;
	}
#endif

	return ( OK );
}

/*************************************************************************
	module		:[•”–åŠÇ—ƒŠƒXƒgƒwƒbƒ_ˆóü]
	functiom	:[•”–åŠÇ—ƒŠƒXƒg‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
	common		:[
		List	:
	]
	condition	:[
		ƒwƒbƒ_Ží—Þ
		,	0->ƒy[ƒWæ“ªŒ©o‚µ
		,	1->ƒy[ƒWƒGƒ“ƒhŒ©o‚µ
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 9]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Print_DepartData_List_Head(
						 UBYTE Category,		/*ƒwƒbƒ_Ží—Þ*/
						 UBYTE Page )			/*ƒy[ƒW*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Category == 0 ) {
		if ( Page == 1 ) {
			/* ‚Ps‰üs{”­MŒ³–¼C”­MŒ³”Ô†{‚Qs‰üsˆóü{Œ©o‚µ{‚Ps‰üs */
  #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		if ( (ret = Print_Head1_Common( PWRD_DepartCodeList_K,
		 LST_NOT,10-1 )) != OK ) {
			return ( ret );
		}
  #else
	if ( (ret = Print_Head1_Common( PWRD_DepartTimeList,
	  LST_XXX_TWI_XXX, 12-1 )) != OK ) {
		return ( ret );
	}
  #endif

			/*Page Œ»ÝŽžŠÔ*/
			if ( (ret = LocateX_Page_Time_Print( 26-1, Page, 36-1 )) != OK ) {
				return ( ret );
			}

			/*†®†¢†Î†¢†¢„¦†¢†¢†¢†²*/
			Print_DepartData_List_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤•”–å†¤—¿‹à†¤’ÊM–‡”„ */
			Print_DepartData_List_Line( 1, List.S.Print, List.S.Attribute );
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
			if ( (ret = LocateX_Page_Print( 26-1, Page )) != OK ) {
				return ( ret );
			}
		}
	}
	else {
	/*†¶†¢†¢†Ö†¢†¢„¨„Ÿ†¢†¢†º*/
		Print_DepartData_List_Line( 4, List.S.Print, List.S.Attribute );
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
	module		:[•”–åŠÇ—ƒR[ƒh ƒlƒNƒXƒg ƒT[ƒ`n
	functiom	:[•”–åŠÇ—ƒR[ƒh‚ÌŽŸ‚ðƒT[ƒ`‚·‚é]
	common		:[
		SYS_DepartFile	:
	]
	condition	:[
		•”–åŠÇ—ƒf[ƒ^”Ô†
		,	ƒf[ƒ^ƒGƒ“ƒh->SYS_DEPART_MAX
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 9]
	author		:[–L“c_Žq]
*************************************************************************/
void			DepartDataNextSearch(
						 UBYTE* CodeCnt)				/*•”–åƒR[ƒhƒf[ƒ^”Ô†*/
{
	UBYTE	i;				/*loop*/

		for ( i = (*CodeCnt); i < SYS_DEPART_MAX; i++ ) {
			if ( SYB_DepartFile[i].Code != 0xffff ) {
				(*CodeCnt) = i;
				break;
			}
			else {		/* SYB_DepartFile[i].Code == 0xffff‚ÌŽž */
				(*CodeCnt) = SYS_DEPART_MAX;
				break;
			}
		}
}

/*************************************************************************
	module		:[•”–åŠÇ—ƒŠƒXƒg‚Ì‚P–¾×ˆóü]
	functiom	:[•”–åŠÇ—ƒŠƒXƒg‚Ì‚P–¾×‚ðˆóü‚·‚éB]
	common		:[
		List			:
		SYS_DepartFile	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 9]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Print_DepartData_List_Specifi(
						 UBYTE Page,				/*ƒy[ƒW*/
						 UBYTE Number,				/*s”Ô†*/
						 UBYTE CodeCnt)		/*•”–åŠÇ—º°ÄÞ”Ô†*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Page > 1 && Number == 0 ) {
		/*†®†¢†Î†¢†¢„¦„Ÿ†¢†²*/
		Print_DepartData_List_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	else {
		/*†¾†¢†Þ†¢†¢„©„Ÿ†¢†Æ*/
		Print_DepartData_List_Line( 2, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}

	/*†¤9999†¤xxxxxx„ xxxxxx„ */
	Print_DepartData_List_Line( 3, List.S.Print, List.S.Attribute );
	/* •”–å */
	CMN_UnsignedIntToASC((UBYTE *)&List.S.Print[27-1], SYB_DepartFile[CodeCnt].Code,
	  4, '0' );

	/* —¿‹à */
	CMN_MemorySetNULL( List.S.Work, 6, ' ');	/* Work¸Ø± */
	CMN_UnsignedLongToASC_NULL((UBYTE *)&List.S.Work[2-1], SYB_DepartFile[CodeCnt].Cost,
	  6, ' ' );
	if ( List.S.Work[4-1] != ' ' ) {
		List.S.Work[1-1] = List.S.Work[2-1];
		List.S.Work[2-1] = List.S.Work[3-1];
		List.S.Work[3-1] = List.S.Work[4-1];
		List.S.Work[4-1] = ',';
	}
	CMN_StringCopy( (UBYTE *)&List.S.Print[36-1], (UBYTE *)List.S.Work );

	/* ’ÊM–‡” */
	CMN_MemorySetNULL( List.S.Work, 6, ' ');
	CMN_UnsignedIntToASC_NULL((UBYTE *)&List.S.Work[2-1], SYB_DepartFile[CodeCnt].TxRxPage, 5, ' ' );
	if ( List.S.Work[3-1] != ' ' ) {
		List.S.Work[1-1] = List.S.Work[2-1];
		List.S.Work[2-1] = List.S.Work[3-1];
		List.S.Work[3-1] = ',';
	}
	CMN_StringCopy( (UBYTE *)&List.S.Print[48-1], (UBYTE *)List.S.Work );

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

/*************************************************************************
	module		:[•”–åŠÇ—ƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrüì¬]
	functiom	:[•”–åŠÇ—ƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
		,	0 = †®„Ÿ†¢†¢†Î†¢†¢„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ†¢†¢†²
		,	1 = †¤ •”–å †¤	—¿‹à  †¤ ’ÊM–‡” „ 
		,	2 = †¾„Ÿ†¢†¢†Þ†¢†¢„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ†¢†¢†Æ
		,	3 = †¤		†¤		  †¤		  „ 
		,	4 = †¶†¢„Ÿ†¢†Ö†¢†¢„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ†¢†¢†º
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 9]
	author		:[–L“c_Žq]
*************************************************************************/
void			Print_DepartData_List_Line(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( (UBYTE *)AscString, (UBYTE *)AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†Î†¢†¢„¦†¢†¢†¢†²*/
			AscString[24-1] = LST_KLINE7;
			CMN_MemorySet( (UBYTE *)&AscString[25-1], 30, LST_KLINE_ );
			AscString[33-1] = LST_KLINE8;
			AscString[44-1] = LST_KLINE8;
			AscString[55-1] = LST_KLINE9;
			break;
		case 1:
			/*†¤•”–å†¤—¿‹à†¤’ÊM–‡”„ */
			AscString[24-1] = LST_KLINEI;
			AttributeSet( (UBYTE *)&AscString[27-1], (UBYTE *)&AttString[27-1], PWRD_Code,
			  LST_NOT );
			AscString[33-1] = LST_KLINEI;
			AttributeSet( (UBYTE *)&AscString[35-1], (UBYTE *)&AttString[35-1], PWRD_Cost,
			  LST_NOT );
			AscString[44-1] = LST_KLINEI;
			AttributeSet( (UBYTE *)&AscString[46-1], (UBYTE *)&AttString[46-1], PWRD_CommPages,
			  LST_NOT );
			AscString[55-1] = LST_KLINEI;
			break;
		case 2:
			/*†¾†¢†¢†Þ†¢„Ÿ„©†¢„Ÿ†¢†Æ*/
			AscString[24-1] = LST_KLINE4;
			CMN_MemorySet( (UBYTE *)&AscString[25-1], 30, LST_KLINE_ );
			AscString[33-1] = LST_KLINE5;
			AscString[44-1] = LST_KLINE5;
			AscString[55-1] = LST_KLINE6;
			break;
		case 3:
			/*†¤	†¤	   „ 	  †¤*/
			AscString[24-1] = LST_KLINEI;
			AscString[33-1] = LST_KLINEI;
			AscString[44-1] = LST_KLINEI;
			AscString[55-1] = LST_KLINEI;
			break;
		case 4:
			/*†¶†¢†¢†Ö†¢†¢„¨„Ÿ†¢†¢†º*/
			AscString[24-1] = LST_KLINE1;
			CMN_MemorySet( (UBYTE *)&AscString[25-1], 30, LST_KLINE_ );
			AscString[33-1] = LST_KLINE2;
			AscString[44-1] = LST_KLINE2;
			AscString[55-1] = LST_KLINE3;
			break;
	}
}

/*************************************************************************
	module		:[ŠÇ——¿‹àŠÇ—ƒŠƒXƒgˆóü]
	functiom	:[ŠÇ——¿‹àŠÇ—ƒŠƒXƒg‚ðˆóü‚·‚é]
	common		:[
		List					:
		SYB_DepartManageTimeFile:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 9]
	author		:[–L“c_Žq]
*************************************************************************/
#if (PRO_DEPART_NEW_LIST == ENABLE)	/* ŠÇ——¿‹àŠÇ—ƒŠƒXƒg By thonda 1997/11/29 */
WORD				Print_DepartManage_List(
						 void )		/* ‚È‚µ */
{
	register WORD	ret;							/*ŽÀsŒ‹‰Ê*/
	UBYTE	page;							/*Íß°¼Þ*/
	UBYTE 	i;								/*loop*/
	UBYTE	code_cnt;						/*º°ÄÞÃÞ°À”Ô†*/
	UBYTE	line_cnt;						/*Žc‚èˆóü‰Â”\s”*/

	page = 1;
	code_cnt = 0;
	DepartManageNextSearch( &code_cnt ); /*ÃÞ°À“ªo‚µ*/
	while ( code_cnt != SYS_DEPART_MAX ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		if ( page == 1 ) {
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		else {
			line_cnt = (UBYTE)(PaperSizeLen() - 4);/*ˆóü‰Â”\s”¾¯Ä*/
		}

		if ( (ret = Print_DepartManage_List_Head( 0, page ) )
		  != OK ) {												/*Í¯ÀÞˆóü*/
			return ( ret );
		}
		for ( i = 0; line_cnt >= 2; i++, line_cnt -= 2 ) {
			if ( (ret = Print_DepartManage_List_Specifi( page, i,
			  code_cnt ) ) != OK ) {/*1–¾×ˆóü*/
				return ( ret );
			}
			code_cnt++;
			DepartManageNextSearch( &code_cnt ); /*ŽŸÃÞ°À»°Á*/
			if ( code_cnt == SYS_DEPART_MAX ) {
				break;
			}
		}
		if ( (ret = Print_DepartManage_List_Head( 1, page ))
		  != OK ) {												/*Ì¯Àˆóü*/
			return ( ret );
		}
		if ( code_cnt != SYS_DEPART_MAX ) {
			DepartManageNextSearch( &code_cnt );
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	if( SYS_DepartManageClearRequest == 1 ) {	/* Ž©“®ÌßØÝÄ‚ÌŽž‚ÉA—¿‹à¤–‡”‚ð */

#if (PRO_COST == ENABLE)	/* Add By O.Kimoto 1997/11/29 */
		CMN_ClearCostData();					/* ¸Ø±‚·‚éB */
#endif

		SYS_DepartManageClearRequest = 0;
	}

	return ( OK );
}
#endif

/*************************************************************************
	module		:[ŠÇ——¿‹àŠÇ—ƒŠƒXƒgƒwƒbƒ_ˆóü]
	functiom	:[ŠÇ——¿‹àŠÇ—ƒŠƒXƒg‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
	common		:[
		List	:
	]
	condition	:[
		ƒwƒbƒ_Ží—Þ
		,	0->ƒy[ƒWæ“ªŒ©o‚µ
		,	1->ƒy[ƒWƒGƒ“ƒhŒ©o‚µ
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 9]
	author		:[–L“c_Žq]
*************************************************************************/
#if (PRO_DEPART_NEW_LIST == ENABLE)	/* ŠÇ——¿‹àŠÇ—ƒŠƒXƒg By thonda 1997/11/29 */
WORD				Print_DepartManage_List_Head(
						 UBYTE Category,		/*ƒwƒbƒ_Ží—Þ*/
						 UBYTE Page )			/*ƒy[ƒW*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Category == 0 ) {
		if ( Page == 1 ) {
			/* ‚Ps‰üs{”­MŒ³–¼C”­MŒ³”Ô†{‚Qs‰üsˆóü{Œ©o‚µ{‚Ps‰üs */
  #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		if ( (ret = Print_Head1_Common( PWRD_DepartCodeList_K,
		 LST_NOT,10-1 )) != OK ) {
			return ( ret );
		}
  #else
	if ( (ret = Print_Head1_Common( PWRD_DepartTimeList,
	  LST_XXX_TWI_XXX, 12-1 )) != OK ) {
		return ( ret );
	}
  #endif


			/*Page •”–åŠÇ—ŠJŽnŽžŠÔ --> Œ»ÝŽžŠÔ */
			if ( (ret = LocateX_Page_Time_To_Time_Print( 17-1, Page, 49-1, 23-1 )) != OK ) {
				return ( ret );
			}

			/*†®†¢†Î†¢†¢„¦†¢†¢†¢†²*/
			Print_DepartManage_List_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤•”–å†¤’ÊMŽžŠÔ†¤’ÊM–‡”„ */
			Print_DepartManage_List_Line( 1, List.S.Print, List.S.Attribute );
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
			if ( (ret = LocateX_Page_Print( 26-1, Page )) != OK ) {
				return ( ret );
			}
		}
	}
	else {
	/*†¶†¢†¢†Ö†¢†¢„¨„Ÿ†¢†¢†º*/
		Print_DepartManage_List_Line( 4, List.S.Print, List.S.Attribute );
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
#endif
/*************************************************************************
	module		:[ŠÇ——¿‹àŠÇ—ƒR[ƒh ƒlƒNƒXƒg ƒT[ƒ`n
	functiom	:[ŠÇ——¿‹àŠÇ—ƒR[ƒh‚ÌŽŸ‚ðƒT[ƒ`‚·‚é]
	common		:[
		SYS_DepartManageTimeFile	:
	]
	condition	:[
		ŠÇ——¿‹àŠÇ—ƒf[ƒ^”Ô†
		,	ƒf[ƒ^ƒGƒ“ƒh->SYS_DEPART_MAX
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 9]
	author		:[–L“c_Žq]
*************************************************************************/
#if (PRO_DEPART_NEW_LIST == ENABLE)	/* ŠÇ——¿‹àŠÇ—ƒŠƒXƒg By thonda 1997/11/29 */
void			DepartManageNextSearch(
						 UBYTE* CodeCnt)				/*•”–åƒR[ƒhƒf[ƒ^”Ô†*/
{
	UBYTE	i;				/*loop*/

		for ( i = (*CodeCnt); i < SYS_DEPART_MAX; i++ ) {
 #if (0) /* bythonda 1997/12/12 */
			if ( SYB_DepartManageTimeFile[i].Code != 0xff ) {
 #endif
			if ( SYB_DepartmentCode[i] != 0xffff ) {
				(*CodeCnt) = i;
				break;
			}
			else {		/* SYB_DepartmentCode[i] == 0xffff‚ÌŽž */
				(*CodeCnt) = SYS_DEPART_MAX;
				break;
			}
		}
}
#endif
/*************************************************************************
	module		:[ŠÇ——¿‹àŠÇ—ƒŠƒXƒg‚Ì‚P–¾×ˆóü]
	functiom	:[ŠÇ——¿‹àŠÇ—ƒŠƒXƒg‚Ì‚P–¾×‚ðˆóü‚·‚éB]
	common		:[
		List			:
		SYS_DepartManageTimeFile	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 9]
	author		:[–L“c_Žq]
*************************************************************************/
#if (PRO_DEPART_NEW_LIST == ENABLE)	/* ŠÇ——¿‹àŠÇ—ƒŠƒXƒg By thonda 1997/11/29 */
WORD				Print_DepartManage_List_Specifi(
						 UBYTE Page,				/*ƒy[ƒW*/
						 UBYTE Number,				/*s”Ô†*/
						 UBYTE CodeCnt)		/*•”–åŠÇ—º°ÄÞ”Ô†*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Page > 1 && Number == 0 ) {
		/*†®†¢†Î†¢†¢„¦„Ÿ†¢†²*/
		Print_DepartManage_List_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	else {
		/*†¾†¢†Þ†¢†¢„©„Ÿ†¢†Æ*/
		Print_DepartManage_List_Line( 2, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}

	/*†¤9999†¤xxxxxx„ xxxxxx„ */
	Print_DepartManage_List_Line( 3, List.S.Print, List.S.Attribute );
	/* •”–å */
	CMN_UnsignedIntToASC((UBYTE *)&List.S.Print[27-1], 
	  SYB_DepartmentCode[CodeCnt], 4, '0' );

	/* ’ÊMŽžŠÔ */
	CMN_MemorySetNULL( List.S.Work, 6, ' ');	/* Work¸Ø± */
	SecondToHourMinuteSecondAsc( SYB_DepartManageTimeFile[CodeCnt].Timer, List.S.Work, ' ');
	CMN_StringCopy( (UBYTE *)&List.S.Print[36-1], (UBYTE *)List.S.Work );

	/* ’ÊM–‡” */
	CMN_MemorySetNULL( List.S.Work, 6, ' ');
	CMN_UnsignedIntToASC_NULL((UBYTE *)&List.S.Work[2-1], SYB_DepartManageTimeFile[CodeCnt].Page, 5, ' ' );
	if ( List.S.Work[3-1] != ' ' ) {
		List.S.Work[1-1] = List.S.Work[2-1];
		List.S.Work[2-1] = List.S.Work[3-1];
		List.S.Work[3-1] = ',';
	}
	CMN_StringCopy( (UBYTE *)&List.S.Print[48-1], (UBYTE *)List.S.Work );

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	return ( OK );
}
#endif
/*************************************************************************
	module		:[ŠÇ——¿‹àŠÇ—ƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrüì¬]
	functiom	:[ŠÇ——¿‹àŠÇ—ƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
		,	0 = †®„Ÿ†¢†¢†Î†¢†¢„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ†¢†¢†²
		,	1 = †¤ •”–å†¤ ’ÊMŽžŠÔ †¤’ÊM–‡” „ 
		,	2 = †¾„Ÿ†¢†¢†Þ†¢†¢„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ†¢†¢†Æ
		,	3 = †¤		†¤		  †¤		  „ 
		,	4 = †¶†¢„Ÿ†¢†Ö†¢†¢„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ†¢†¢†º
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/ 9]
	author		:[–L“c_Žq]
*************************************************************************/
#if (PRO_DEPART_NEW_LIST == ENABLE)	/* ŠÇ——¿‹àŠÇ—ƒŠƒXƒg By thonda 1997/11/29 */
void			Print_DepartManage_List_Line(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( (UBYTE *)AscString, (UBYTE *)AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†Î†¢†¢„¦†¢†¢†¢†²*/
			AscString[24-1] = LST_KLINE7;
			CMN_MemorySet( (UBYTE *)&AscString[25-1], 30, LST_KLINE_ );
			AscString[33-1] = LST_KLINE8;
			AscString[46-1] = LST_KLINE8;
			AscString[55-1] = LST_KLINE9;
			break;
		case 1:
			/*†¤•”–å†¤’ÊMŽžŠÔE’ÊM–‡”„ */
			AscString[24-1] = LST_KLINEI;
			AttributeSet( (UBYTE *)&AscString[27-1], (UBYTE *)&AttString[27-1], PWRD_Code,
			  LST_NOT );
			AscString[33-1] = LST_KLINEI;
			AttributeSet( (UBYTE *)&AscString[37-1], (UBYTE *)&AttString[37-1], PWRD_Time,
			  LST_NOT );
			AscString[46-1] = LST_KLINEI;
			AttributeSet( (UBYTE *)&AscString[48-1], (UBYTE *)&AttString[48-1], PWRD_CommPages,
			  LST_NOT );
			AscString[55-1] = LST_KLINEI;
			break;
		case 2:
			/*†¾†¢†¢†Þ†¢„Ÿ„©†¢„Ÿ†¢†Æ*/
			AscString[24-1] = LST_KLINE4;
			CMN_MemorySet( (UBYTE *)&AscString[25-1], 30, LST_KLINE_ );
			AscString[33-1] = LST_KLINE5;
			AscString[46-1] = LST_KLINE5;
			AscString[55-1] = LST_KLINE6;
			break;
		case 3:
			/*†¤	†¤	   „ 	  †¤*/
			AscString[24-1] = LST_KLINEI;
			AscString[33-1] = LST_KLINEI;
			AscString[46-1] = LST_KLINEI;
			AscString[55-1] = LST_KLINEI;
			break;
		case 4:
			/*†¶†¢†¢†Ö†¢†¢„¨„Ÿ†¢†¢†º*/
			AscString[24-1] = LST_KLINE1;
			CMN_MemorySet( (UBYTE *)&AscString[25-1], 30, LST_KLINE_ );
			AscString[33-1] = LST_KLINE2;
			AscString[46-1] = LST_KLINE2;
			AscString[55-1] = LST_KLINE3;
			break;
	}
}
#endif


/*************************************************************************
	module		:[ƒy[ƒWAŽžŠÔˆóü]
	functiom	:[ƒy[ƒWAŽžŠÔ‚ðˆóü‚·‚éB]
	common		:[
		List			:
		SYS_CurrentTime	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[V53]
	language	:[MS-C]
	keyword		:[LST]
	date		:[94/ 2/25]
	author		:[–L“c_Žq]
*************************************************************************/
WORD	LocateX_Page_Time_Print(
				 UBYTE LocateX1,	/* ˆóüŒ…ˆÊ’u-Page */
				 UBYTE Page,		/* ƒy[ƒW */
				 UBYTE LocateX2		/* ˆóüŒ…ˆÊ’u-Day */
		)
{
	Prn_Att_Str_Clear( (unsigned char far *)List.S.Print, (unsigned char far *)List.S.Attribute );
	CMN_MemorySetNULL( (unsigned char far *)List.S.Work, 80, ' ' );
	List.S.Print[LocateX1-2] = 'P';
	List.S.Print[LocateX1-1] = '.';
	CMN_UnsignedIntToASC( (UBYTE *)&List.S.Print[LocateX1], (UWORD)Page, 3, 0 );
	TimeDataAscii( OFF, SYB_CurrentTime, List.S.Work, 0 );
	CMN_StringCopy( (UBYTE *)&List.S.Print[LocateX2], (UBYTE *)List.S.Work );
	return ( CharacterPrint( LST_PRINT ) );
}

/*************************************************************************
	module		:[ƒy[ƒWAŠJŽnŽžŠÔ-->Œ»ŽžŠÔˆóü]
	functiom	:[ƒy[ƒWAŠJŽnŽžŠÔ-->Œ»ŽžŠÔ‚ðˆóü‚·‚éB]
	common		:[
		List			:
		SYB_CurrentTime	:
		SYB_DepartManageStartTime
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/12/12]
	author		:[–{‘½’qK]
*************************************************************************/
WORD	LocateX_Page_Time_To_Time_Print(
				 UBYTE LocateX1,	/* ˆóüŒ…ˆÊ’u-Page */
				 UBYTE Page,		/* ƒy[ƒW */
				 UBYTE LocateX2,	/* -->ˆóüŒ…ˆÊ’u-Day */
				 UBYTE LocateX3		/* ˆóüŒ…ˆÊ’u-Day */
		)
{
	Prn_Att_Str_Clear( (unsigned char far *)List.S.Print, (unsigned char far *)List.S.Attribute );
	CMN_MemorySetNULL( (unsigned char far *)List.S.Work, 80, ' ' );
	List.S.Print[LocateX1-2] = 'P';
	List.S.Print[LocateX1-1] = '.';
	CMN_UnsignedIntToASC( (UBYTE *)&List.S.Print[LocateX1], (UWORD)Page, 3, 0 );

	TimeDataAscii( OFF, SYB_DepartManageStartTime, List.S.Work, 0 );
	CMN_StringCopy( (UBYTE *)&List.S.Print[LocateX3], (UBYTE *)List.S.Work );
	List.S.Print[LocateX2-4] = '-';
	List.S.Print[LocateX2-3] = '-';
	List.S.Print[LocateX2-2] = '>';

	TimeDataAscii( OFF, SYB_CurrentTime, List.S.Work, 0 );
	CMN_StringCopy( (UBYTE *)&List.S.Print[LocateX2], (UBYTE *)List.S.Work );
	return ( CharacterPrint( LST_PRINT ) );
}

 #if (0) /* LST_JNL.C ‚ÅŠù‚ÉŽg—p‚Å‚·‚Ì‚Åíœ By S.Fukui Dec.1,1997 */
/*************************************************************************
	module		:[ƒy[ƒWˆóü]
	functiom	:[ƒy[ƒW‚ðˆóü‚·‚éB]
	common		:[
		List	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[V53]
	language	:[MS-C]
	keyword		:[LST]
	date		:[94/ 3/ 4]
	author		:[–L“c_Žq]
*************************************************************************/
//WORD				LocateX_Page_Print(
//						 UBYTE LocateX,		/*ˆóüŒ…ˆÊ’u-Page*/
//						 UBYTE Page )		/*ƒy[ƒW*/
//{
//	Prn_Att_Str_Clear( (UBYTE *)List.S.Print, (UBYTE *)List.S.Attribute );
//	CMN_MemorySetNULL( (UBYTE *)List.S.Work, 80, ' ' );
//	List.S.Print[LocateX-2] = 'P';
//	List.S.Print[LocateX-1] = '.';
//	CMN_UnsignedIntToASC( (UBYTE *)List.S.Work, (UWORD)Page, 0, 0 );
//	CMN_StringCopy( (UBYTE *)&List.S.Print[LocateX], (UBYTE *)List.S.Work );
//	return ( CharacterPrint( LST_PRINT ) );
//}
 #endif /* if (0) */

#endif  /* #if (PRO_COST == ENABLE) || (PRO_DEPART_NEW_LIST == ENABLE) */	/* •”–åŠÇ—ƒŠƒXƒgiŠÇ——¿‹àŠÇ—ƒŠƒXƒgj By thonda 1997/11/29 */
