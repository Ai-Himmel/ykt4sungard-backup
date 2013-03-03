/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_DMRY.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ‘ãsŽóMÁ‹Ž’Ê’m
*	Maintenance	: ‚Q‰ñü—p‚Éì‚è‘Ö‚¦‚Ü‚µ‚½ 1997/10/21 Y.Matsukuma
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
#include	"\src\atlanta\define\stng_pro.h" /*For ANZU 96/02/19 H.Hirao */

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"

/* #if (PRO_MULTI_LINE == ENABLE)	 /@ Add By O.Kimoto 1997/06/26 @/ */
#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34) /* ‚g‚h‚m‚n‚j‚h‚Å‘ãsŽóM‚Å‚u‚R‚S‚Ì”‚ª‚Å‚È‚¢•s‹ï‡C³ 1999/01/26 by T.Soneoka */
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\mlt_pro.h"
#endif

#if (PRO_MULTI_LINE == DISABLE)
/*************************************************************************
	module		:[‘ãsŽóMÁ‹Ž’Ê’mˆóü]
	functiom	:[‘ãsŽóMÁ‹Ž’Ê’m‚ðˆóü‚·‚é]
	common		:[
		List				:
		SYB_MemoryRxPrint	:
		SYB_JournalPoint	:
		SYB_JournalFile		:
	]
	condition	:[]
	commment	:[ƒf[ƒ^‚ÍŒÃ‚¢•¨‚©‚ç‡‚Éˆóü‚³‚ê‚é]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/14]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Print_DelMemoryRcv_Notice(
						 void )				/*‚È‚µ*/
{
	UBYTE	i;							/*loop*/
	UBYTE	point;						/*ˆÊ’u‚—*/
	UBYTE	rcv_cnt;					/*ÃÞ°À¶³ÝÄ*/
	UBYTE	page;						/*Íß°¼Þ*/
	UBYTE	line_cnt;					/*s”*/
	register WORD	ret;				/*ˆóüŒ‹‰Ê*/

	if ( Check_AnyList( LST_DELMEMORYRCV_NOTICE ) == MSG_PRN_LST_NO_LIST ) {
		return ( MSG_PRN_LST_NO_LIST );
	}

/*	point = SYB_MemoryRxPoint;*/
	/* ‘ãsŽóMƒoƒO Oct.5,1994 By S.K  */
	/* point = SYB_MemoryRxPrintReadPoint; */
	point = SYS_MemoryRxEraseReportPoint;
	rcv_cnt	= 0;
	page	= 1;
	while( rcv_cnt != SYS_MEMORY_RX_MAX ){
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}

		if ( page == 1 ) {
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		else {
			line_cnt = (UBYTE)(PaperSizeLen() - 4);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		if ( (ret = Print_DelMemoryRcv_Notice_Head( 0, page ) ) != OK ) {/*Í¯ÀÞˆóü*/
			return ( ret );
		}
		for(i = 0;line_cnt >= 2; i++ ){
			while( rcv_cnt < SYS_MEMORY_RX_MAX ){		/* ŽŸ‚ÌŽóMÁ‹ŽŒŸõ */
				if ( SYB_MemoryRxPrint[point].Status == SYS_MEMORY_RX_POWEROFF ) {
					break;
				}
				rcv_cnt++;
				point++;
				if ( point >= SYS_MEMORY_RX_MAX ) {
					point = 0;
				}
			}
			if( rcv_cnt >= SYS_MEMORY_RX_MAX ){
				break;
			}
			/*†¾†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†Æ*/
			if(( page == 1 ) ||					/* ‚Pƒy[ƒW–Ú‚ÌŽž */
			   (( page != 1 ) && ( i != 0 ))){	/* 1ƒy[ƒW,‚Ps–ÚˆÈŠO‚ÌŽž */
				Print_DelMemoryRcv_Line( 2, LST_RX, List.S.Print, List.S.Attribute );
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
			}
			/*†¤999 †¤xxxx†¤xxxx†¤Z9,Z9:99†¤Z9'99"†¤ZZ9 †¤9999†¤XXXX†¤XXXX†¤*/
			if ( (ret = Print_DelMemoryRcv_Specifi( LST_RX,		/*1–¾×ˆóü*/
			  (struct SYS_JournalData_t *)SYB_MemoryRxPrint[point].JournalPoint )) != OK ) {
				return ( ret );
			}
			SYB_MemoryRxPrint[point].Status = SYS_MEMORY_RX_EMPTY;
			line_cnt	-= 2;
			point++;
			rcv_cnt++;
			if ( point >= SYS_MEMORY_RX_MAX ) {
				point = 0;
			}
		}
		if ( (ret = Print_DelMemoryRcv_Notice_Head( 1, page) ) != OK ) {	/*Ì¯Àˆóü*/
			return ( ret );
		}
		while( rcv_cnt < SYS_MEMORY_RX_MAX ){		/* ŽŸ‚ÌŽóMÁ‹ŽŒŸõ */
			if ( SYB_MemoryRxPrint[point].Status == SYS_MEMORY_RX_POWEROFF ) {
				break;
			}
			rcv_cnt++;
			point++;
			if ( point >= SYS_MEMORY_RX_MAX ) {
				point = 0;
			}
		}
		if( rcv_cnt >= SYS_MEMORY_RX_MAX ){
			break;
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	/* ‘ãsŽóMƒoƒO Oct.5,1994 By S.K  */
	/* SYB_MemoryRxPrintWritePoint = 0;    */
	/* SYB_MemoryRxPrintReadPoint = 0;     */


	/*ÀÞ²º³¼Þ­¼Ý ¹ÞÝº³¶Þ ¼®³·® »ÚÏ¼À ...........*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1],
	  PWRD_ThisMemErased, LST_NOT );
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
#endif

#if (PRO_MULTI_LINE == ENABLE)		/** ‚Q‰ñüŽd—l‚ÌÁ‹Ž’Ê’m ƒCƒ`ƒ‡ƒE‚©‚ç 1997/10/22 Y.Matsukuma */
/*************************************************************************
	module		:[ˆóü‚·‚é‘ãsŽóM‚ðˆê‚Â“¾‚é]
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
	date		:[1997/08/20]
	author		:[´… ­‹M]
*************************************************************************/
UBYTE GetDelMemoryRcvData(UBYTE line_number,
						  UBYTE sub_line_number)	/* add By O.Kimoto 1998/05/13 */
{
	UBYTE	i;
	UBYTE	prt_ptr;
	UDWORD	min_time;

	/* ’Ê”Ô‚Å•À‚×‘Ö‚¦‚é‚ÆA“ú‚ª•Ï‰»‚µ‚½Žž‚©‚ç‚ÌŽóMƒf[ƒ^‚Æd‚È‚Á‚Ä‚µ‚Ü‚¤‚½‚ß‚É
	** ŠJŽnŽžŠÔ‚Å•À‚Ñ‘Ö‚¦‚é‚æ‚¤‚É‚·‚é
	** 1998/01/08 M.Shimizu -> ‹âˆÇ‚æ‚è 1998/01/13
	*/

	min_time = 0xFFFFFFFF;
	prt_ptr  = SYS_MEMORY_RX_MAX;

	for (i = 0; i < SYS_MEMORY_RX_MAX; i++) {
#if (PRO_LINENUMBER == TWICE_LINE)
		/* ‚p‚`‚s•s‹ï‡
		** Šg’£‰ñü‚ÅŽóM‚ª‚Å‚«‚È‚¢•s‹ï‡C³
		** Šg’£‰ñü‚Ìˆ—‚ª”²‚¯‚Ä‚¢‚½i "& 0x7f")
		** by O.Kimoto 1998/04/13
		*/
		if (OPT_GetMultiLinrNumber((SYB_MemoryRxPrint[i].StackNumber & 0x7f)) == line_number
		 && ((SYB_MemoryRxPrint[i].StackNumber & 0x80) == sub_line_number)	/* Add by O.Kimoto 1998/05/13 */
		 &&  SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_POWEROFF
		 &&  SYB_MemoryRxPrint[i].JournalPoint->StartTime < min_time ){
#else
		if ( OPT_GetMultiLinrNumber(SYB_MemoryRxPrint[i].StackNumber) == line_number
		 &&  SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_POWEROFF
		 &&  SYB_MemoryRxPrint[i].JournalPoint->StartTime < min_time ){
#endif
			min_time = SYB_MemoryRxPrint[i].JournalPoint->StartTime;
			prt_ptr = i;
		}
	}

#if 0
//	UBYTE i;
//	UBYTE prt_ptr;
//	UWORD num;
//
//	num     = 999;
//	prt_ptr = SYS_MEMORY_RX_MAX;
//
//	for (i = 0; i < SYS_MEMORY_RX_MAX; i++) {
//		if ( OPT_GetMultiLinrNumber(SYB_MemoryRxPrint[i].StackNumber) == line_number
//		 &&  SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_POWEROFF
//		 &&  SYB_MemoryRxPrint[i].JournalPoint->Number < num ){
//			num = SYB_MemoryRxPrint[i].JournalPoint->Number;
//			prt_ptr = i;
//		}
//	}
#endif

	return (prt_ptr);
}


/*************************************************************************
	module		:[‚Q‰ñüŽd—l‚Ì‘ãsŽóMÁ‹Ž’Ê’m]
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
	date		:[1997/10/23]
	author		:[¼ŒG]
*************************************************************************/
WORD	Print_DelMemoryRcv_Notice( void )				/*‚È‚µ*/
{
	UBYTE	max_line;
	UBYTE	page;
/*	UBYTE	i;	*/			/*loop*/
	UBYTE	cnt;
/* 	UBYTE	point;			*ˆÊ’u‚—*/
	UBYTE	is_find;		/* ŽŸ‚Ìƒy[ƒW‚Éˆóü‚·‚×‚«ƒtƒ@ƒCƒ‹‚ª‚ ‚é‚©‚Ìƒ`ƒFƒbƒN */
	UBYTE   prt_ptr;
	UBYTE	line_number;
	UBYTE	sub_line_number;	/* •W€‰ñü^Šg’£‰ñü‚Ì‹æ•Ê‚ª‚Å‚«‚Ä‚¢‚È‚¢BIIIIby O.Kimoto 1998/05/13 */
	register WORD	ret;	/* ˆóüŒ‹‰Ê */

	if ( Check_AnyList( LST_DELMEMORYRCV_NOTICE ) == MSG_PRN_LST_NO_LIST ) {
		return ( MSG_PRN_LST_NO_LIST );
	}

	page = 1;
/*	i = 0;	*/
	line_number = 1;	/* ƒ‰ƒCƒ“ƒiƒ“ƒo[‰Šú‰» 1998/03/13 Y.Matsukuma */
	sub_line_number = 0;		/* •W€‰ñü^Šg’£‰ñü‚Ì‹æ•Ê‚ª‚Å‚«‚Ä‚¢‚È‚¢BIIIIby O.Kimoto 1998/05/13 */


	/** ‰üƒy[ƒWˆ—’Ç‰Á */
/* 	point = SYS_MemoryRxEraseReportPoint; */

	/** ! ‚Ü‚¸A‚Ç‚±‚Ì‰ñü‚©‚çˆóŽš‚·‚é‚©Œˆ’è‚·‚éI ‚P‰ñü–Ú‚Ì‘ãsŽóM‚ª•K‚¸‚ ‚é‚Æ‚ÍŒÀ‚ç‚È‚¢!!! */

#if (PRO_LINENUMBER == TWICE_LINE)
	/* •W€‰ñü^Šg’£‰ñü‚Ì‹æ•Ê‚ª‚Å‚«‚Ä‚¢‚È‚¢BIIII
	** by O.Kimoto 1998/05/13
	*/
	for (cnt = 0; cnt < SYS_MEMORY_RX_MAX; cnt++) {		/** ˆ—‘ÎÛ‚Ìƒtƒ@ƒCƒ‹‚ª‚ ‚é‚©’²‚×‚é */
		if ((SYB_MemoryRxPrint[cnt].StackNumber == 0)
		 &&  SYB_MemoryRxPrint[cnt].Status == SYS_MEMORY_RX_POWEROFF) {
			sub_line_number |= 0x01;
		}
		else if ((SYB_MemoryRxPrint[cnt].StackNumber == 0x80)
		 &&  SYB_MemoryRxPrint[cnt].Status == SYS_MEMORY_RX_POWEROFF) {
			sub_line_number |= 0x80;
		}
	}
	
#endif

	if (OPT_CountModems() > 1) {
		is_find = FALSE;
		for (line_number = 1; line_number < OPT_CountModems(); line_number++) {
			for (cnt = 0; cnt < SYS_MEMORY_RX_MAX; cnt++) {		/** ˆ—‘ÎÛ‚Ìƒtƒ@ƒCƒ‹‚ª‚ ‚é‚©’²‚×‚é */
#if (PRO_LINENUMBER == TWICE_LINE)
				/* ‚p‚`‚s•s‹ï‡
				** Šg’£‰ñü‚ÅŽóM‚ª‚Å‚«‚È‚¢•s‹ï‡C³
				** Šg’£‰ñü‚Ìˆ—‚ª”²‚¯‚Ä‚¢‚½i "& 0x7f")
				** by O.Kimoto 1998/04/13
				*/
				if ( OPT_GetMultiLinrNumber((SYB_MemoryRxPrint[cnt].StackNumber & 0x7f)) == line_number
				 &&  SYB_MemoryRxPrint[cnt].Status == SYS_MEMORY_RX_POWEROFF) {
#else
				if ( OPT_GetMultiLinrNumber(SYB_MemoryRxPrint[cnt].StackNumber) == line_number
				 &&  SYB_MemoryRxPrint[cnt].Status == SYS_MEMORY_RX_POWEROFF) {
#endif
					is_find = TRUE;		/** ”­Œ©‚µ‚½ƒXƒ^ƒbƒN”Ô†‚ð—LŒø‚É‚·‚é */
					break;
				}
			}
			if (is_find == TRUE) {
				break;		/** ŠY“–ƒ‰ƒCƒ“‚Ì‘ãsŽóM‚ªŒ©‚Â‚©‚Á‚½‚Ì‚Å‘X‚É”²‚¯‚é */
			}
		}
	}

	while(1) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}

		if ( page == 1 ) {	/* ‚Pƒy[ƒW–Ú */
			max_line = (UBYTE)(PaperSizeLen() - 13);/*ˆóü‰Â”\s”¾¯Ä*/

			/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs*/
			if ( (ret = TTI_ID_Print_Feed()) != OK ) {
				return ( ret );
			}

			/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[18-1] = LST_KLINE7;
			CMN_MemorySet( &List.S.Print[19-1], 44, LST_KLINE_ );
			List.S.Print[63-1] = LST_KLINE9;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*	‘ãsŽóMÁ‹Ž’Ê’m  */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[18-1] = LST_KLINEI;

 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			AttributeSet( &List.S.Print[21-1], &List.S.Attribute[21-1],
			 PWRD_ErasedDocumemts_K, LST_NOT );		/* MES¨INV 94.7.20 ->NOT 8.10 */
 #else
			AttributeSet( &List.S.Print[21-1], &List.S.Attribute[21-1],
			 PWRD_ErasedDocumemts, LST_MES_TWI_XXX );
 #endif
			List.S.Print[63-1] = LST_KLINEI;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[18-1] = LST_KLINE1;
			CMN_MemorySet( &List.S.Print[19-1], 44, LST_KLINE_ );
			List.S.Print[63-1] = LST_KLINE3;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}

			/** ICHOU’Ç‰Á -- ƒy[ƒW‚ÆŒ»ÝŽžŠÔ‚ðƒvƒŠƒ“ƒg */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
#if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* “ú—§“Á‹–‰ñ”ð(ƒvƒŠƒ“ƒgŽžŠÔ‚ðˆóŽš‚µ‚È‚¢) By M.Tachibana 1998/04/22 */
			TimeDataAscii( OFF, SYB_CurrentTime, List.S.Work, 0 );
			CMN_StringCopy( &List.S.Print[59], List.S.Work );
#endif
			List.S.Print[1] = 'P';
			List.S.Print[2] = '.';
			CMN_UnsignedIntToASC(&List.S.Print[3], page, 0, ' ');
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/** ‰ñü”Ô†ˆóŽš 1997/07/25 M.Shimizu */

#if (PRO_LINENUMBER == TWICE_LINE)
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			CMN_StringCopy(&List.S.Print[1], PWRD_LineNumber);
			if (line_number == 1) {
				if ((sub_line_number & 0x01) == 0x01) {
					AttributeSet( &List.S.Print[13], &List.S.Attribute[13], PWRD_LineName[0], LST_NOT );
				}
				else {
					AttributeSet( &List.S.Print[13], &List.S.Attribute[13], PWRD_LineName[1], LST_NOT );
				}
			}
			else {
				AttributeSet( &List.S.Print[13], &List.S.Attribute[13], PWRD_LineName[2], LST_NOT );
			}
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			max_line--;
#else
			if (OPT_CountModems() > 1) {	/** ‘½‰ñü‘¶Ý‚·‚é */
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
				CMN_StringCopy(&List.S.Print[1], PWRD_LineNumber);
				CMN_UnsignedIntToASC(&List.S.Print[13], line_number, 1, '0');
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
				max_line--;
			}
#endif

			/*†®†¢†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†²*/
			Print_DelMemoryRcv_Line( 0, LST_RX, List.S.Print, List.S.Attribute	);
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤ Â³ÊÞÝ†¤±²Ã»·Ò² †¤Ó°ÄÞ†¤¶²¼¼Þº¸ †¤¼Þ¶Ý†¤Ï²½³†¤ÌÞÓÝ†¤¹¯¶ †¤ËÞº³†¤*/
			Print_DelMemoryRcv_Line( 1, LST_RX, List.S.Print, List.S.Attribute	);
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

		}
		else {	/* ‚Qƒy[ƒW–ÚˆÈ~ */
			max_line = (UBYTE)(PaperSizeLen() - 4);/*ˆóü‰Â”\s”¾¯Ä*/

			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}

			/* Page */
			if ( (ret = PagePrint( page, 2-1 )) != OK ) {
				return ( ret );
			}
		}

		for (;;) {
#if (0)	/* 1‰ñü‚ÌŽž‚àŠJŽnŽžŠÔ‚Åƒ\[ƒg‚·‚é By M.Tachibana 1998/05/13 */
//			/** ‚Q‰ñü‚ÌŽž‚Í‰ñü”Ô†‚²‚Æ‚É•ª‚¯‚é 1997/07/25 M.Shimizu */
//			if (OPT_CountModems() > 1) {	/** ‘½‰ñü‘¶Ý‚·‚éŽž‚Í‰ñü”Ô†‚ðŒ©‚é */
#endif

				/** ŽŸ‚ÌˆóŽš‘ÎÛ‚ð“¾‚éi’Ê”Ô‚ð˜A‘±‚³‚¹‚é‚½‚ßj*/
#if (PRO_LINENUMBER == TWICE_LINE)
				/* •W€‰ñü^Šg’£‰ñü‚Ì‹æ•Ê‚ª‚Å‚«‚Ä‚¢‚È‚¢BIIIIby O.Kimoto 1998/05/13 */					
				if (line_number == 1) {
					if ((sub_line_number & 0x01) == 0x01) {
						prt_ptr = GetDelMemoryRcvData(line_number,(UBYTE)0);	/* ˆø”’Ç‰Á by O.Kimoto 1998/05/13 */
					}
					else {
						prt_ptr = GetDelMemoryRcvData(line_number,(UBYTE)0x80);	/* ˆø”’Ç‰Á by O.Kimoto 1998/05/13 */
				}
				}
				else {
					prt_ptr = GetDelMemoryRcvData(line_number,(UBYTE)0);	/* ˆø”’Ç‰Á by O.Kimoto 1998/05/13 */
				}
#else
				prt_ptr = GetDelMemoryRcvData(line_number,(UBYTE)0);	/* ˆø”’Ç‰Á by O.Kimoto 1998/05/13 */
#endif

				if (prt_ptr != SYS_MEMORY_RX_MAX) {		/** Œ©‚Â‚©‚Á‚½ */
					/* ’Ç‰Á 1997/10/22 Y.Matsukuma */
					if (max_line == (UBYTE)(PaperSizeLen() - 4)) {
						/*†®†¢†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†²*/
						Print_DelMemoryRcv_Line( 0, LST_RX, List.S.Print, List.S.Attribute	);
						if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
							return ( ret );
						}
					}
					else {
						Print_DelMemoryRcv_Line( 2, LST_RX, List.S.Print, List.S.Attribute );
						if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
							return ( ret );
						}
					}
					/* --’Ç‰ÁI—¹-- */
					if ( (ret = Print_DelMemoryRcv_Specifi( LST_RX,		/*1–¾×ˆóü*/
					  (struct SYS_JournalData_t *)SYB_MemoryRxPrint[prt_ptr].JournalPoint )) != OK ) {
						return ( ret );
					}
					SYB_MemoryRxPrint[prt_ptr].Status = SYS_MEMORY_RX_EMPTY;

					/** ‰üƒy[ƒWˆ— */
					max_line -= 2;
					if (max_line <= 5) {
						break;
					}
				}
#if (0)	/* 1‰ñü‚ÌŽž‚àŠJŽnŽžŠÔ‚Åƒ\[ƒg‚·‚é By M.Tachibana 1998/05/13 */
//			}
//			else {
//				if ( SYB_MemoryRxPrint[point].Status == SYS_MEMORY_RX_POWEROFF ) {
//					/*†¾†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†Æ*/
//					/* ’Ç‰Á 1997/10/22 Y.Matsukuma */
//					if (max_line == (UBYTE)(PaperSizeLen() - 4)) {
//						/*†®†¢†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†²*/
//						Print_DelMemoryRcv_Line( 0, LST_RX, List.S.Print, List.S.Attribute	);
//						if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
//							return ( ret );
//						}
//					}
//					else {
//						Print_DelMemoryRcv_Line( 2, LST_RX, List.S.Print, List.S.Attribute );
//						if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
//							return ( ret );
//						}
//					}
//					/* --’Ç‰ÁI—¹-- */
//					/*†¤999 †¤xxxx†¤xxxx†¤Z9,Z9:99†¤Z9'99"†¤ZZ9 †¤9999†¤XXXX†¤XXXX†¤*/
//					if ( (ret = Print_DelMemoryRcv_Specifi( LST_RX,		/*1–¾×ˆóü*/
//					  (struct SYS_JournalData_t *)SYB_MemoryRxPrint[point].JournalPoint )) != OK ) {
//						return ( ret );
//					}
//					SYB_MemoryRxPrint[point].Status = SYS_MEMORY_RX_EMPTY;
//
//					/** ‰üƒy[ƒWˆ— */
//					max_line -= 2;
//					if (max_line <= 5) {
//						break;
//					}
//				}
//			}
//			point++;
//			if ( point >= SYS_MEMORY_RX_MAX ) {
//				point = 0;
//			}
//			i++;
#endif

			/** ‘½‰ñü‚ÌŽžAˆóŽš‚·‚×‚«ƒf[ƒ^‚ª‚È‚©‚Á‚½‚çŽŸ‚Ì‰ñü‚Ìƒf[ƒ^‚ðW‚ß‚é */
#if (0)
//			if (OPT_CountModems() > 1) [
#endif
				if (prt_ptr == SYS_MEMORY_RX_MAX) {		/** ŽŸ‚Ì‰ñü‚ð’²‚×‚És‚­ */

#if (PRO_LINENUMBER == TWICE_LINE)
					/* •W€‰ñü^Šg’£‰ñü‚Ì‹æ•Ê‚ª‚Å‚«‚Ä‚¢‚È‚¢BIIIIby O.Kimoto 1998/05/13 */					
					if ((line_number == 1) && (sub_line_number == 0x81)) {
						sub_line_number = 0x80;
					}
					else {
						sub_line_number = 0;
						line_number++;
					}
#else
					line_number++;
#endif

					if (line_number > OPT_CountModems()) {	/** ‚·‚×‚Ä‚Ì‰ñü‚ð’²‚×‚¨‚í‚Á‚½Žž */
						break;	/** ƒ‹[ƒv‚ð”²‚¯‚é */
					}
					if (max_line <= 9) {	/** ‚XsˆÈ‰º‚Å‚Í‰üƒy[ƒW‚³‚¹‚È‚¢‚Æ‚Pƒy[ƒW‚©‚ç‚Í‚Ýo‚µ‚Ä‚µ‚Ü‚¤ */
						break;
					}

					/** ICHOU’Ç‰Á -- ŽŸƒy[ƒW‚Ì‘¶Ýƒ`ƒFƒbƒN */
					is_find = FALSE;
					for (cnt = 0; cnt < SYS_MEMORY_RX_MAX; cnt++) {		/** ‚Ü‚¾ˆ—‘ÎÛ‚Ìƒtƒ@ƒCƒ‹‚ª‚ ‚é‚©’²‚×‚é */
						/** ˆ—‚µ‚½–¾×‚ÌƒXƒe[ƒ^ƒX‚Í SYS_MEMORY_RX_EMPTY ‚É‚È‚Á‚Ä‚¢‚é‚½‚ßAˆÈ‰º‚ÌðŒ‚Å”»’f‚·‚é */
						if ( SYB_MemoryRxPrint[cnt].Status == SYS_MEMORY_RX_POWEROFF ) {
							is_find = TRUE;		/** ‚Ü‚¾‚ ‚é */
							break;
						}
					}
					if (is_find == FALSE) {
						break;
					}

					if (max_line != (UBYTE)(PaperSizeLen() - 4)) {
						/*†¶†¢†¢†Ö†¢†¢†¢†Ö†¢†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†¢†Ö†¢†¢†Ö†¢†¢†Ö†¢†¢†Ö†¢†¢†¢†º*/
						Print_DelMemoryRcv_Line( 4, LST_RX, List.S.Print, List.S.Attribute	);
						if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
							return ( ret );
						}
						/*‚PsˆóŽši‰üsj*/
						if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
							return ( ret );
						}
					}
					else {
						max_line += 2;
					}

					/** ‰ñü”Ô†‚ðˆóŽš‚·‚é */

#if (PRO_LINENUMBER == TWICE_LINE)
					Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
					CMN_StringCopy(&List.S.Print[1], PWRD_LineNumber);
					if (line_number == 1) {
						if ((sub_line_number & 0x01) == 0x01) {
							AttributeSet( &List.S.Print[13], &List.S.Attribute[13], PWRD_LineName[0], LST_NOT );
						}
						else {
							AttributeSet( &List.S.Print[13], &List.S.Attribute[13], PWRD_LineName[1], LST_NOT );
						}
					}
					else {
						AttributeSet( &List.S.Print[13], &List.S.Attribute[13], PWRD_LineName[2], LST_NOT );
					}
					if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
						return ( ret );
					}
#else
					Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
					CMN_StringCopy(&List.S.Print[1], PWRD_LineNumber);
					CMN_UnsignedIntToASC(&List.S.Print[13], line_number, 1, '0');
					if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
						return ( ret );
					}
#endif

					/** –¾×ƒwƒbƒ_ */
					/*†®†¢†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†²*/
					Print_DelMemoryRcv_Line( 0, LST_RX, List.S.Print, List.S.Attribute	);
					if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
						return ( ret );
					}
					/*†¤ Â³ÊÞÝ†¤±²Ã»·Ò² †¤Ó°ÄÞ†¤¶²¼¼Þº¸ †¤¼Þ¶Ý†¤Ï²½³†¤ÌÞÓÝ†¤¹¯¶ †¤ËÞº³†¤*/
					Print_DelMemoryRcv_Line( 1, LST_RX, List.S.Print, List.S.Attribute	);
					if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
						return ( ret );
					}
					max_line -= 5;
				}
#if (0)	/* 1‰ñü‚ÌŽž‚àŠJŽnŽžŠÔ‚Åƒ\[ƒg‚·‚é By M.Tachibana 1998/05/13 */
//			]
//			else [	/** ‚P‰ñü‚ÌŽž */
//				/** ‘ãsŽóMƒe[ƒuƒ‹‚ª‚PŽü‚µ‚½‚çŽŸ‚Ì‰ñü‚Ìƒf[ƒ^‚ðW‚ß‚é */
//				if (i > SYS_MEMORY_RX_MAX) {		/** ‚P‰ñü‚ÌŽž‚Í‚·‚®ƒ‹[ƒv‚ð”²‚¯‚é */
//					line_number++;
//					break;
//				}
//				if (prt_ptr == SYS_MEMORY_RX_MAX) {		/** ŽŸ‚Ì‰ñü‚ð’²‚×‚És‚­ */
//					line_number++;
//					break;
//				}
//			]
#endif
		}

		/* ‘ãsŽóMƒoƒO Oct.5,1994 By S.K  */
		/* MemoryRxPrintWritePoint = 0;    */
		/* MemoryRxPrintReadPoint = 0;     */

		/*†¶†¢†¢†Ö†¢†¢†¢†Ö†¢†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†¢†Ö†¢†¢†Ö†¢†¢†Ö†¢†¢†Ö†¢†¢†¢†º*/
		Print_DelMemoryRcv_Line( 4, LST_RX, List.S.Print, List.S.Attribute	);
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}

		is_find = FALSE;
		for (cnt = 0; cnt < SYS_MEMORY_RX_MAX; cnt++) {		/** ‚Ü‚¾ˆ—‘ÎÛ‚Ìƒtƒ@ƒCƒ‹‚ª‚ ‚é‚©’²‚×‚é */
			/** ˆ—‚µ‚½–¾×‚ÌƒXƒe[ƒ^ƒX‚Í SYS_MEMORY_RX_EMPTY ‚É‚È‚Á‚Ä‚¢‚é‚½‚ßAˆÈ‰º‚ÌðŒ‚Å”»’f‚·‚é */
			if ( SYB_MemoryRxPrint[cnt].Status == SYS_MEMORY_RX_POWEROFF ) {
				is_find = TRUE;		/** ‚Ü‚¾‚ ‚é */
				break;
			}
		}
		if (is_find == FALSE) {		/* ‚à‚¤‚È‚¢ */
			/*ÀÞ²º³¼Þ­¼Ý ¹ÞÝº³¶Þ ¼®³·® »ÚÏ¼À ...........*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1],
			  PWRD_ThisMemErased, LST_NOT );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
		}

		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}

		/*
		** ‘ãsŽóMƒe[ƒuƒ‹‚É‰½‚©ƒf[ƒ^‚ª‚ ‚é‚ªA‰½‚©‚ÌŒ´ˆö‚Åƒf[ƒ^‚ª‰»‚¯‚Ä‚µ‚Ü‚Á‚½Žž‚É‚Í
		** –³ŒÀƒvƒŠƒ“ƒg‚µ‚Ä‚µ‚Ü‚¤‚Ì‚ð‚±‚±‚ÅƒK[ƒhB‚f‚S‚Å”­¶‚µ‚½‚ªDDD
		** 1997/10/07 M.Shimizu
		*/

#if (PRO_LINENUMBER == TWICE_LINE)
		/* •W€‰ñü^Šg’£‰ñü‚Ì‹æ•Ê‚ª‚Å‚«‚Ä‚¢‚È‚¢BIIIIby O.Kimoto 1998/05/13 */					
		if (line_number == 1) {
			if ((sub_line_number & 0x01) == 0x01) {
				prt_ptr = GetDelMemoryRcvData(line_number,(UBYTE)0);	/* ˆø”’Ç‰Á by O.Kimoto 1998/05/13 */
			}
			else {
				prt_ptr = GetDelMemoryRcvData(line_number,(UBYTE)0x80);	/* ˆø”’Ç‰Á by O.Kimoto 1998/05/13 */
		}
		}
		else {
			prt_ptr = GetDelMemoryRcvData(line_number,(UBYTE)0);	/* ˆø”’Ç‰Á by O.Kimoto 1998/05/13 */
		}
#else
		prt_ptr = GetDelMemoryRcvData(line_number,(UBYTE)0);	/* ˆø”’Ç‰Á by O.Kimoto 1998/05/13 */
#endif

		if (prt_ptr == SYS_MEMORY_RX_MAX && line_number > OPT_CountModems()) {
			/** ÅI‰ñü‚Ìƒf[ƒ^‚ªŒ©‚Â‚©‚ç‚È‚¢‚Æ‚«‚ÍA‰½‚©ƒf[ƒ^‚ª‚ ‚Á‚Ä‚à–³Ž‹‚·‚é */
			break;
		}

		is_find = FALSE;
		for (cnt = 0; cnt < SYS_MEMORY_RX_MAX; cnt++) {		/** ‚Ü‚¾ˆ—‘ÎÛ‚Ìƒtƒ@ƒCƒ‹‚ª‚ ‚é‚©’²‚×‚é */
			/** ˆ—‚µ‚½–¾×‚ÌƒXƒe[ƒ^ƒX‚Í SYS_MEMORY_RX_EMPTY ‚É‚È‚Á‚Ä‚¢‚é‚½‚ßAˆÈ‰º‚ÌðŒ‚Å”»’f‚·‚é */
			if ( SYB_MemoryRxPrint[cnt].Status == SYS_MEMORY_RX_POWEROFF ) {
				is_find = TRUE;		/** ‚Ü‚¾‚ ‚é */
				break;
			}
		}
		if (is_find == FALSE) {
			break;
		}

		page++;
	}

	/*
	** –œ‚ªˆêƒXƒe[ƒ^ƒX‚ªŽc‚Á‚½‚±‚Æ‚ðl—¶‚µ‚Ä
	** POWEROFF‚ð‚·‚×‚Ä‚±‚©‚·
	** 1997/10/07 M.Shimizu
	*/

	for (cnt = 0; cnt < SYS_MEMORY_RX_MAX; cnt++) {
		if ( SYB_MemoryRxPrint[cnt].Status == SYS_MEMORY_RX_POWEROFF ) {
			SYB_MemoryRxPrint[cnt].Status = SYS_MEMORY_RX_EMPTY;
		}
	}

	return ( OK );
}
#endif

#if (PRO_MULTI_LINE == DISABLE ) /* (0) */ /* Žg‚í‚È‚­‚È‚Á‚½ 1997/10/23 Y.Matsukuma */
/*************************************************************************
	module		:[‘ãsŽóMÁ‹Ž’Ê’mƒwƒbƒ_ˆóü]
	functiom	:[‘ãsŽóMÁ‹Ž’Ê’m‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
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
	date		:[97/05/08]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD				Print_DelMemoryRcv_Notice_Head(
						 UBYTE Category,	/*ƒwƒbƒ_Ží—Þ*/
						 UBYTE Page )		/*ƒy[ƒW*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Category == 0 ) {
		if ( Page == 1 ) {
			/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs*/
			if ( (ret = TTI_ID_Print_Feed()) != OK ) {
				return ( ret );
			}

			/*†®†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†²*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[18-1] = LST_KLINE7;
			CMN_MemorySet( &List.S.Print[19-1], 44, LST_KLINE_ );
			List.S.Print[63-1] = LST_KLINE9;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*	‘ãsŽóMÁ‹Ž’Ê’m  */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[18-1] = LST_KLINEI;

 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			AttributeSet( &List.S.Print[21-1], &List.S.Attribute[21-1],
				 PWRD_ErasedDocumemts_K, LST_NOT );		/* MES¨INV 94.7.20 ->NOT 8.10 */
 #else
			/* AttributeSet( &List.S.Print[31-1], &List.S.Attribute[31-1],
			  PWRD_ErasedDocumemts, LST_MES_TWI_XXX ); */ /* For ANZU By H.HIRAO 1995/01/06 */
			AttributeSet( &List.S.Print[21-1], &List.S.Attribute[21-1],
			  PWRD_ErasedDocumemts, LST_MES_TWI_XXX );
 #endif

			List.S.Print[63-1] = LST_KLINEI;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[18-1] = LST_KLINE1;
			CMN_MemorySet( &List.S.Print[19-1], 44, LST_KLINE_ );
			List.S.Print[63-1] = LST_KLINE3;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}

			/*Œ»ÝŽžŠÔ*/
			/*Page Œ»ÝŽžŠÔ*/
#if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* “ú—§“Á‹–‰ñ”ð(ƒvƒŠƒ“ƒgŽžŠÔ‚ðˆóŽš‚µ‚È‚¢) By M.Tachibana 1998/04/22 */
			if ( (ret = PageTimePrint( Page, 2-1, 60-1 )) != OK ) {
				return ( ret );
			}
#else
			if ( (ret = PagePrint( Page, 2-1 )) != OK ) {
				return ( ret );
			}
#endif

			/*†®†¢†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†²*/
			Print_DelMemoryRcv_Line( 0, LST_RX, List.S.Print, List.S.Attribute	);
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤ Â³ÊÞÝ†¤±²Ã»·Ò² †¤Ó°ÄÞ†¤¶²¼¼Þº¸ †¤¼Þ¶Ý†¤Ï²½³†¤ÌÞÓÝ†¤¹¯¶ †¤ËÞº³†¤*/
			Print_DelMemoryRcv_Line( 1, LST_RX, List.S.Print, List.S.Attribute	);
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
		else{
			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}

			/* Page */
			if ( (ret = PagePrint( Page, 2-1 )) != OK ) {
				return ( ret );
			}

			/*†®†¢†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†²*/
			Print_DelMemoryRcv_Line( 0, LST_RX, List.S.Print, List.S.Attribute	);
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
	}
	else{
		/*†¶†¢†¢†Ö†¢†¢†¢†Ö†¢†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†¢†Ö†¢†¢†Ö†¢†¢†Ö†¢†¢†Ö†¢†¢†¢†º*/
		Print_DelMemoryRcv_Line( 4, LST_RX, List.S.Print, List.S.Attribute	);
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
	}
}

#endif	/* if(0)-end */

/*************************************************************************
	module		:[‘ãsŽóMÁ‹Ž’Ê’m–¾×ˆóü]
	functiom	:[‘ãsŽóMÁ‹Ž’Ê’m‚Ì–¾×•”•ª‚ðˆóü‚·‚é]
	common		:[
		List				:
	]
	condition	:[
		‘—ŽóM‹æ•ª
		,	TXTYPE
		,	LST_RX
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/14]
	author		:[–L“c_Žq]
*************************************************************************/
WORD				Print_DelMemoryRcv_Specifi(
						 UBYTE TxRx,				/*‘—ŽóM‹æ•ª*/
						 struct SYS_JournalData_t *JournalFile ) /*’ÊM‹L˜^ƒf[ƒ^*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	/*†¤9999†¤xxxxxx†¤xxxx†¤Z9,Z9:99†¤Z9'99"†¤ZZ9†¤9999†¤XXXX†¤XXXXXX†¤*/
	Print_DelMemoryRcv_Line( 3, TxRx, List.S.Print, List.S.Attribute );
	/*Â³ÊÞÝ*/
	CMN_UnsignedIntToASC( &List.S.Print[3-1],
	  (UWORD)JournalFile->Number, 3, '0' );
	/*±²Ã»·Ò²*/
	CMN_StringCopy( &List.S.Print[8-1], JournalFile->RemoteID_TTI );
	/*Ó°ÄÞ*/
	CommunicationModeName( JournalFile->Mode, &List.S.Print[29-1],
	   &List.S.Attribute[29-1] );
	/*¶²¼ ÆÁ¼Þ*/
	CriterionMinuteToDayTimeAsc( JournalFile->StartTime/60, LST_DDHHMM,
	  List.S.Work );
	CMN_StringCopy( &List.S.Print[39-1], List.S.Work );
	/*¼Þ¶Ý*/
	SecondToMinuteSecondAsc( JournalFile->TotalTime,
	  List.S.Work , ' ' );
	CMN_StringCopy( &List.S.Print[48-1], List.S.Work );
	/*Ï²½³*/
	CMN_UnsignedIntToASC( &List.S.Print[55-1],
	  (UWORD)JournalFile->Page, 3, ' ' );

#if (PRO_DEPARTMENT == ENABLE)
	/*•”–å*/
	/* •”–åŠÇ—ON‚ÅAƒvƒƒeƒNƒgON‚ÌŽžA•”–åƒR[ƒh‚ðƒ}ƒXƒN‚·‚é‚½‚ß‚Ìif else•¶’Ç‰Á For ANZU By H.HIRAO 1996/08/13 */
	if ( (CHK_DepartmentON() == ON) && (CHK_SectionCheckProtect() == ON) ) {
		List.S.Print[60-1] = '*';
		List.S.Print[61-1] = '*';
		List.S.Print[62-1] = '*';
		List.S.Print[63-1] = '*';
	}
	else {
		if (JournalFile->DepartmentCode != 0xffff) { /*  ‰Šú’l‚ª0xffff‚É•ÏX‚Ì‚½‚ß */
			CMN_UnsignedIntToASC( &List.S.Print[60-1],
	  	  	  (UWORD)JournalFile->DepartmentCode, 4, '0' );
	  	}
	}

	/*ECM*/
	if ( (JournalFile->Result & LST_ECM) != 0 ) {
		List.S.Print[65-1] = '*';
	}
/* #if (PRO_MULTI_LINE == ENABLE)	 /@ Add By O.Kimoto 1997/06/26 @/  */
#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34) /* ‚g‚h‚m‚n‚j‚h‚Å‘ãsŽóM‚Å‚u‚R‚S‚Ì”‚ª‚Å‚È‚¢•s‹ï‡C³ 1999/01/26 by T.Soneoka */
	if ( (JournalFile->Result & V34_MODE_SET) != 0 ) {	/* ‚u‚R‚SŒðMŽž */
		List.S.Print[65-1] = '#';
	}
#endif
	/*¹¯¶*/
	CommunicationResultName( (JournalFile->Result),
	  LST_NAME_SHORT, LST_RESULT_COMMON, &List.S.Print[66-1], &List.S.Attribute[66-1] );
	/*ËÞº³*/
	CommunicationKindName( JournalFile->Kind, LST_NAME_1,
	  &List.S.Print[73-1], &List.S.Attribute[73-1] );

#else
	/*ECM*/
	if ( (JournalFile->Result & LST_ECM) != 0 ) {
		List.S.Print[60-1] = '*';
	}
/* #if (PRO_MULTI_LINE == ENABLE)	 /@ Add By O.Kimoto 1997/06/26 @/ */
#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34) /* ‚g‚h‚m‚n‚j‚h‚Å‘ãsŽóM‚Å‚u‚R‚S‚Ì”‚ª‚Å‚È‚¢•s‹ï‡C³ 1999/01/26 by T.Soneoka */
	if ( (JournalFile->Result & V34_MODE_SET) != 0 ) {	/* ‚u‚R‚SŒðMŽž */
		List.S.Print[60-1] = '#';
	}
#endif
	/*¹¯¶*/
	CommunicationResultName( (JournalFile->Result),
							  LST_NAME_SHORT, 
							  LST_RESULT_COMMON,
							  &List.S.Print[61-1],
							  &List.S.Attribute[61-1] );
	/*ËÞº³*/
	CommunicationKindName( JournalFile->Kind, LST_NAME_1, &List.S.Print[68-1], &List.S.Attribute[68-1] );
#endif

	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

/*************************************************************************
	module		:[’ÊMŠÇ—‚Ì‰¡‹æØ‚èŒrüì¬]
	functiom	:[’ÊMŠÇ—‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/ 3/14]
	author		:[–L“c_Žq]
*************************************************************************/
void				Print_DelMemoryRcv_Line(
						 UBYTE Category,			/*ŒrüŽí—Þ*/
						 UBYTE TxRx,				/*‘—ŽóM‹æ•ª*/
						 register UBYTE *AscString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )/*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†Î†¢†Î†¢†Î†¢†Î†¢†Î†¢†Î†¢†Î†¢†²*/
			AscString[1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[7-1] = LST_KLINE8;
			AscString[28-1] = LST_KLINE8;
			AscString[38-1] = LST_KLINE8;
			AscString[47-1] = LST_KLINE8;
			AscString[54-1] = LST_KLINE8;
			AscString[59-1] = LST_KLINE8;
#if (PRO_DEPARTMENT == ENABLE)
			AscString[64-1] = LST_KLINE8;
			AscString[72-1] = LST_KLINE8;
#else
			AscString[67-1] = LST_KLINE8;
#endif
			AscString[80-1] = LST_KLINE9;
			break;
		case 1:
			/*†¤ Â³ÊÞÝ†¤±²Ã»·Ò²†¤Ó°ÄÞ†¤¶²¼¼Þº¸†¤¼Þ¶Ý†¤Ï²½³†¤ÌÞÓÝ„ ¹¯¶†¤ËÞº³†¤*/
			AscString[1-1] = LST_KLINEI;
			AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_ContNo,
			  LST_NOT );
			AscString[7-1] = LST_KLINEI;
			if ( TxRx == LST_TX ) {
				AttributeSet( &AscString[14-1], &AttString[14-1],
				  PWRD_RemoteTo, LST_NOT );
			}
			else {
				AttributeSet( &AscString[14-1], &AttString[14-1],
				  PWRD_RemoteFrom, LST_NOT );
			}
			AscString[28-1] = LST_KLINEI;
			AttributeSet( &AscString[29-1], &AttString[29-1], PWRD_Mode,
			  LST_NOT );
			AscString[38-1] = LST_KLINEI;
			if ( TxRx == LST_TX ) {
				AttributeSet( &AscString[39-1], &AttString[39-1], PWRD_Start,
				  LST_NOT );
			}
			else {
				AttributeSet( &AscString[39-1], &AttString[39-1],
				  PWRD_Received, LST_NOT );
			}
			AscString[47-1] = LST_KLINEI;
			AttributeSet( &AscString[48-1], &AttString[48-1], PWRD_Time,
			  LST_NOT );
			AscString[54-1] = LST_KLINEI;
			AttributeSet( &AscString[55-1], &AttString[55-1], PWRD_Page,
			  LST_NOT );
			AscString[59-1] = LST_KLINEI;

#if (PRO_DEPARTMENT == ENABLE)
			AttributeSet( &AscString[60-1], &AttString[60-1], PWRD_Code,
			  LST_NOT );
			AscString[64-1] = LST_KLINEI;
			AttributeSet( &AscString[65-1], &AttString[65-1], PWRD_Result,
			  LST_NOT );
			AscString[72-1] = LST_KLINEI;
			AttributeSet( &AscString[73-1], &AttString[73-1], PWRD_Note,
			  LST_NOT );
#else
			AttributeSet( &AscString[60-1], &AttString[60-1], PWRD_Result,
			  LST_NOT );
			AscString[67-1] = LST_KLINEI;
			AttributeSet( &AscString[68-1], &AttString[68-1], PWRD_Note,
			  LST_NOT );

#endif
			AscString[80-1] = LST_KLINEI;
			break;
		case 2:
			/*†¾†¢†Þ†¢†Þ†¢†Þ†¢†Þ†¢†Þ†¢†Þ„Ÿ„©†¢†Þ†¢†Æ*/
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[7-1] = LST_KLINE5;
			AscString[28-1] = LST_KLINE5;
			AscString[38-1] = LST_KLINE5;
			AscString[47-1] = LST_KLINE5;
			AscString[54-1] = LST_KLINE5;
			AscString[59-1] = LST_KLINE5;
#if (PRO_DEPARTMENT == ENABLE)
			AscString[64-1] = LST_KLINE5;
			AscString[72-1] = LST_KLINE5;
#else
			AscString[67-1] = LST_KLINE5;
#endif
			AscString[80-1] = LST_KLINE6;
			break;
		case 3:
			/*†¤   †¤	†¤	 †¤	  †¤   †¤	„ 	 †¤	  †¤   †¤*/
			AscString[1-1] = LST_KLINEI;
			AscString[7-1] = LST_KLINEI;
			AscString[28-1] = LST_KLINEI;
			AscString[38-1] = LST_KLINEI;
			AscString[47-1] = LST_KLINEI;
			AscString[54-1] = LST_KLINEI;
			AscString[59-1] = LST_KLINEI;
#if (PRO_DEPARTMENT == ENABLE)
			AscString[64-1] = LST_KLINEI;
			AscString[72-1] = LST_KLINEI;
#else
			AscString[67-1] = LST_KLINEI;
#endif
			AscString[80-1] = LST_KLINEI;
			break;
		case 4:
			/*†¶†¢†Ö†¢†Ö†¢†Ö†¢†Ö†¢†Ö†¢†Ö„Ÿ„¨†¢†Ö†¢†º*/
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[7-1] = LST_KLINE2;
			AscString[28-1] = LST_KLINE2;
			AscString[38-1] = LST_KLINE2;
			AscString[47-1] = LST_KLINE2;
			AscString[54-1] = LST_KLINE2;
			AscString[59-1] = LST_KLINE2;
#if (PRO_DEPARTMENT == ENABLE)
			AscString[64-1] = LST_KLINE2;
			AscString[72-1] = LST_KLINE2;
#else
			AscString[67-1] = LST_KLINE2;
#endif
			AscString[80-1] = LST_KLINE3;
			break;
	}
}

