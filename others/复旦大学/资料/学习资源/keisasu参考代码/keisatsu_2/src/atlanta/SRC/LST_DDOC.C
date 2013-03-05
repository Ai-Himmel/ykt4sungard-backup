/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_DDOC.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/04/15
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒTƒuƒAƒhƒŒƒXŒ´eÁ‹Ž’Ê’m
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdial.h"

#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\lst_def.h"

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\lst_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\lst_data.h"
#include "\src\atlanta\ext_v\lst_wrd.h"
#include "\src\atlanta\ext_v\sys_data.h"

#if (PRO_F_CODE == ENABLE)
/*************************************************************************
	module		:[ƒTƒuƒAƒhƒŒƒXŒ´eÁ‹Ž’Ê’mˆóü]
	function	:[ƒTƒuƒAƒhƒŒƒXŒ´eÁ‹Ž’Ê’m‚ðˆóü‚·‚é]
	common		:[
		List					:
		SYB_SubAddressBoxTable  :
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/04/15]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD					Print_Del_F_CodeBoxDoc_Notice(
						 UBYTE mode )
{
	UBYTE	i;							/*loop*/
	UBYTE	box_cnt;					/* BOX”Ô† */
	UBYTE	page;						/*Íß°¼Þ*/
	UBYTE	line_cnt;
	register WORD	ret;				/*ŽÀsŒ‹‰Ê*/

	/* 12Line add 1997/04/26  By T.Yamaguchi */
	/*Á‹ŽÃÞ°À‘¶ÝŒŸ¸*/
	if ( mode == LST_DEL_FCODE_BOX_DOC_NOTICE ) {
		if ( SYB_SubAddressBoxTable[SYS_DocumentPrintBoxNumber - 1].DataStatus == SYS_SUB_ADDRESS_BOX_NO_SET ) {
			return ( MSG_PRN_LST_NO_LIST );
		}
	}
	else {
		if ( Check_AnyList( LST_DEL_FCODE_BOX_DOC_NOTICE ) == MSG_PRN_LST_NO_LIST ) {
			return ( MSG_PRN_LST_NO_LIST );
		}
	}

	box_cnt	= 0;
	page	= 1;
	while ( box_cnt != SUB_ADDRESS_BOX_MAX ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}

		if ( page == 1 ) {
			line_cnt = (UBYTE)(PaperSizeLen() - 13);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		else {
			line_cnt = (UBYTE)(PaperSizeLen() - 5);/*ˆóü‰Â”\s”¾¯Ä*/
		}

		if ( (ret = Print_Del_F_Code_Notice_Head( 0, page ) ) != OK ) {/*Í¯ÀÞˆóü*/
			return ( ret );
		}

		for ( i = 0; line_cnt >= 2; i++ ) {
			F_CodeDataNextSearch( 2, &box_cnt );			/*ŽŸÃÞ°À»°Á*/
			if( box_cnt == SUB_ADDRESS_BOX_MAX ){
				break;
			}
			if(( page == 1 ) ||					/* ‚Pƒy[ƒW–Ú‚ÌŽž */
			   (( page != 1 ) && ( i != 0 ))){	/* 1ƒy[ƒW,‚Ps–ÚˆÈŠO‚ÌŽž */
				/* „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„§ */
				Print_Del_F_Code_Notice_Line( 2, List.S.Print, List.S.Attribute );
				if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
			}
			/* „ 99„ xxxxxxx„ xxxxxxxxxxxxxxx„ xxxxxx„  */
			Print_Del_F_Code_Notice_Line( 3, List.S.Print, List.S.Attribute );
			/* ‚a‚‚˜ */
			CMN_UnsignedIntToASC( &List.S.Print[15-1], (UWORD)(box_cnt + 1), 2, ' ' );
			/* ƒ{ƒbƒNƒX–¼ */
			CMN_StringCopy( &List.S.Print[19-1], SYB_SubAddressBoxTable[box_cnt].BoxName );
			/* ‘ŠŽèæ–¼ */
			CMN_StringCopy( &List.S.Print[36-1], SYB_SubAddressBoxTable[box_cnt].RemoteName );
			/* Ží—Þ */
			switch( SYB_SubAddressBoxTable[box_cnt].Status ){
			case	SUB_ADDRESS_BULLETIN_BOX:		/* ŒfŽ¦”Â */
				CMN_StringCopy( &List.S.Print[58-1], PWRD_NoticeBoard );
				break;
			case	SUB_ADDRESS_SECURE_BOX:			/* e“W */
				CMN_StringCopy( &List.S.Print[58-1], PWRD_Secure );
				break;
			case	SUB_ADDRESS_RELAY_BOX:			/* ’†Œp */
				CMN_StringCopy( &List.S.Print[59-1], PWRD_Relay );
				break;
			default:
				break;
			}

			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/* o—Íó‘Ô‚ðƒNƒŠƒA */
			SYB_SubAddressBoxTable[box_cnt].MessageStatus	= SYS_SUB_ADDRESS_BOX_MSG_EMPTY;

			/* ŽóMó‘ÔƒNƒŠƒA *//* 1999/10/21 Y.Murata NAGANO‚æ‚è */
			SYB_SubAddressBoxTable[box_cnt].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;

			line_cnt	-= 2;
			box_cnt++;
		}

		if ( (ret = Print_Del_F_Code_Notice_Head( 1, page ) ) != OK ) {/*Í¯ÀÞˆóü*/
			return ( ret );
		}

		F_CodeDataNextSearch( 2, &box_cnt );			/*ŽŸÃÞ°À»°Á*/
		if( box_cnt == SUB_ADDRESS_BOX_MAX ){
			break;
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}

	/* "Fº°ÄÞÎÞ¯¸½¹ÞÝº³ ¶Þ ¼®³·®»ÚÏ¼À......" */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[14-1], &List.S.Attribute[14-1], PWRD_ThisBoxErased, LST_NOT );
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
	module		:[e“WŽóMÁ‹Ž’Ê’mƒwƒbƒ_ˆóü]
	functiom	:[e“WŽóMÁ‹Ž’Ê’m‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
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
	date		:[97/10/13]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD				Print_Del_F_Code_Notice_Head(
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
			List.S.Print[14-1] = LST_KLINE7;
			CMN_MemorySet( &List.S.Print[15-1], 51, LST_KLINE_ );
			List.S.Print[66-1] = LST_KLINE9;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/* |‚eƒR[ƒh‚a‚n‚wƒQƒ“ƒRƒE  ƒVƒ‡ƒEƒLƒ‡  ƒcƒEƒ`| */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[14-1] = LST_KLINEI;
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1],
			 PWRD_Del_F_CodeBoxDoc_Notice_K, LST_NOT);
#else
			AttributeSet( &List.S.Print[15-1], &List.S.Attribute[15-1],
			  PWRD_Del_F_CodeBoxDoc_Notice, LST_MES_TWI_XXX);
#endif

			List.S.Print[66-1] = LST_KLINEI;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[14-1] = LST_KLINE1;
			CMN_MemorySet( &List.S.Print[15-1], 51, LST_KLINE_ );
			List.S.Print[66-1] = LST_KLINE3;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}

			/* Œ»ÝŽžŠÔ */
			if ( (ret = PageTimePrint( Page, 14-1, 46-1 )) != OK ) {
				return ( ret );
			}

			/* „¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„¢ */
			Print_Del_F_Code_Notice_Line( 0, List.S.Print, List.S.Attribute );
			if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/* „ Box„ ÎÞ¯¸½–¼„  ‘ŠŽèæ–¼  	„ Ží—Þ„  */
			Print_Del_F_Code_Notice_Line( 1, List.S.Print, List.S.Attribute );
			if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
		else{
			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}

			/* Page */
			if ( (ret = PagePrint( Page, 14-1 )) != OK ) {
				return ( ret );
			}

			/* „¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„¢ */
			Print_Del_F_Code_Notice_Line( 0, List.S.Print, List.S.Attribute );
			if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
	}
	else{
		/* „¤„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„£	 */
		Print_Del_F_Code_Notice_Line( 4, List.S.Print, List.S.Attribute );
		if (( ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
	}
}

/*************************************************************************
	module		:[ƒTƒuƒAƒhƒŒƒXŒ´eÁ‹Ž’Ê’m‚Ì‰¡‹æØ‚èŒrüì¬]
	function	:[ƒTƒuƒAƒhƒŒƒXŒ´eÁ‹Ž’Ê’m‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
			case	0:
			 „¡„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„¢

			case	1:
			 „ Box „ ÎÞ¯¸½–¼ „ ‘ŠŽèæ–¼„ Ží—Þ„ 

			case	2:
			 „¥„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„§ 

			case	3:
			 „ 	   „ 		 „ 		   „ 	 „ 

			case	4:
			 „¤„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„£
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/04/15]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
void				Print_Del_F_Code_Notice_Line( 
						 UBYTE Category,				 /*ŒrüŽí—Þ*/
						 register UBYTE *AscString,		 /*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString)		 /*Cü•¶Žš—ñ*/
{
	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0 :
			/* „¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„¢ @ƒTƒuƒAƒhƒŒƒXŒ´eÁ‹Ž’Ê’m@*/
			AscString[13-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[14-1], 53, LST_KLINE_);
			AscString[18-1] = LST_KLINE8;
			AscString[35-1] = LST_KLINE8;
			AscString[56-1] = LST_KLINE8;
			AscString[66-1] = LST_KLINE9;
			break;
		case 1 :
			/* „ Box„ ÎÞ¯¸½–¼„ ‘ŠŽèæ–¼„ Ží—Þ„ */
			AscString[13-1] = LST_KLINEI;
			AttributeSet( &AscString[14-1], &AttString[14-1]
					, PWRD_Box, LST_NOT );
			AscString[18-1] = LST_KLINEI;
			AttributeSet( &AscString[23-1], &AttString[23-1]
					,PWRD_BoxName, LST_NOT );
			AscString[35-1] = LST_KLINEI;
			AttributeSet( &AscString[41-1], &AttString[41-1]
					,PWRD_BoxLocation, LST_NOT );
			AscString[56-1] = LST_KLINEI;
			AttributeSet( &AscString[59-1], &AttString[59-1]
					,PWRD_Kind, LST_NOT );
			AscString[66-1] = LST_KLINEI;
			break;
		case 2 :
			/* „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„§ */
			AscString[13-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[14-1], 53, LST_KLINE_);
			AscString[18-1] = LST_KLINE5;
			AscString[35-1] = LST_KLINE5;
			AscString[56-1] = LST_KLINE5;
			AscString[66-1] = LST_KLINE6;
			break;
		case 3 :
			/* „   „ 		 „ 		   „     „  */
			AscString[13-1] = LST_KLINEI;
			AscString[18-1] = LST_KLINEI;
			AscString[35-1] = LST_KLINEI;
			AscString[56-1] = LST_KLINEI;
			AscString[66-1] = LST_KLINEI;
			break;
		case 4:
			/* „¤„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„£	 */
			AscString[13-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[14-1], 53, LST_KLINE_);
			AscString[18-1] = LST_KLINE2;
			AscString[35-1] = LST_KLINE2;
			AscString[56-1] = LST_KLINE2;
			AscString[66-1] = LST_KLINE3;
			break;
		case 5 :
			/* „¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„Ÿ„Ÿ„¦„Ÿ„Ÿ„¦„Ÿ„Ÿ„¢ @ƒTƒuƒAƒhƒŒƒXŽóM’Ê’m@*/
			AscString[6-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[7-1], 61, LST_KLINE_);
			AscString[11-1] = LST_KLINE8;
			AscString[28-1] = LST_KLINE8;
			AscString[49-1] = LST_KLINE8;
			AscString[58-1] = LST_KLINE8;
			AscString[67-1] = LST_KLINE9;
			break;
		case 6 :
			/* „ Box„ ÎÞ¯¸½–¼„ ‘ŠŽèæ–¼„ Ží—Þ„ Œ´eNo„ */
			AscString[6-1] = LST_KLINEI;
			AttributeSet( &AscString[7-1], &AttString[7-1]
					, PWRD_Box, LST_NOT );
			AscString[11-1] = LST_KLINEI;
			AttributeSet( &AscString[15-1], &AttString[15-1]
					,PWRD_BoxName, LST_NOT );
			AscString[28-1] = LST_KLINEI;
			AttributeSet( &AscString[34-1], &AttString[34-1]
					,PWRD_BoxLocation, LST_NOT );
			AscString[49-1] = LST_KLINEI;
			AttributeSet( &AscString[52-1], &AttString[52-1]
					,PWRD_Kind, LST_NOT );
			AscString[58-1] = LST_KLINEI;
			AttributeSet( &AscString[59-1], &AttString[59-1]
					,PWRD_DocumentsNo, LST_NOT );
			AscString[67-1] = LST_KLINEI;
			break;
		case 7 :
			/* „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„Ÿ„©„Ÿ„Ÿ„©„Ÿ„Ÿ„Ÿ„§ */
			AscString[6-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[7-1], 61, LST_KLINE_);
			AscString[11-1] = LST_KLINE5;
			AscString[28-1] = LST_KLINE5;
			AscString[49-1] = LST_KLINE5;
			AscString[58-1] = LST_KLINE5;
			AscString[67-1] = LST_KLINE6;
			break;
		case 8 :
			/* „   „ 		 „ 		   „ 	  „     „  */
			AscString[6-1] = LST_KLINEI;
			AscString[11-1] = LST_KLINEI;
			AscString[28-1] = LST_KLINEI;
			AscString[49-1] = LST_KLINEI;
			AscString[58-1] = LST_KLINEI;
			AscString[67-1] = LST_KLINEI;
			break;
		case 9:
			/* „¤„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„Ÿ„Ÿ„¨„Ÿ„Ÿ„¨„Ÿ„Ÿ„£	 */
			AscString[6-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[7-1], 61, LST_KLINE_);
			AscString[11-1] = LST_KLINE2;
			AscString[28-1] = LST_KLINE2;
			AscString[49-1] = LST_KLINE2;
			AscString[58-1] = LST_KLINE2;
			AscString[67-1] = LST_KLINE3;
			break;
	}
}

#endif
