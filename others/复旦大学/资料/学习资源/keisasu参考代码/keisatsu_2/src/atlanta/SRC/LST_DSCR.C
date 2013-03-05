/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_DSCR.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: e“WŽóMÁ‹Ž’Ê’m
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
#include	"\src\atlanta\define\mem_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\mem_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#if ( PRO_PANEL == ANK )
#include "\src\atlanta\opr\ank\define\opr_def.h"
#endif
#if ( PRO_PANEL == KANJI )
#include "\src\atlanta\opr\kanji\define\opr_def.h"
#endif

/*************************************************************************
	module		:[e“WŽóMÁ‹Ž’Ê’mˆóü]
	function	:[e“WŽóMÁ‹Ž’Ê’m‚ðˆóü‚·‚é]
	common		:[
		List		:
		SYB_MailBox	:
		SYS_DocumentPrintNo		:
	]
	condition	:[
		ˆóüƒ‚[ƒh
		'	LST_DELSECURE_NOTICE	e“WŽóMÁ‹Ž’Ê’m
		'	LST_POWEROFF_NOTICE		’â“dŒŸo’Ê’m
	]
	commment	:[
		94/11/26	By j.masuda
			e“WŽóMÁ‹Ž’Ê’m‚ÌƒXƒe[ƒ^ƒXƒNƒŠƒA[‚ðƒƒ‚ƒŠ‚ª‚È‚¢Žž‚Ì‚Ý
			SYS_MAIL_SET‚Æ‚·‚éB‚Ü‚½ƒƒ‚ƒŠ‚ÌƒNƒŠƒA[‚ÍƒƒCƒ“‚Ås‚¤Ž–‚Æ‚µ
			ƒŠƒXƒg‚Å‚Í‚¨‚±‚È‚í‚È‚¢Bi’â“dŽž‚Ì‚Ýj
		94/11/29	By j.masuda
			e“WŽóMÁ‹Ž’Ê’m‚ÍƒXƒe[ƒ^ƒX‚ªSYS_MAILBOX_RECEIVE‚ÅA‚©‚ÂA
			ƒƒ‚ƒŠ‚ª‚È‚¢Žž‚Ì‚Ýˆóü‚·‚éB

		1997/10/18 Y.Matsukuma 
			e“Wƒƒ‚ƒŠŠúŠÔ‚ª‰ß‚¬‚½‚Æ‚«‚ÌÁ‹Ž’Ê’m‚ª‚¨‚©‚µ‚­‚È‚é‚Ì‚Å
			Print_DelSecure_Notice_Specifi((UBYTE)SYS_DocumentPrintNo)
			‚Éƒ‚[ƒhiModej‚ð’Ç‰Á‚µ‚ÄƒRƒ“ƒyƒA‚³‚¹‚Ü‚µ‚½ iƒ|ƒvƒ‰AƒAƒ“ƒY‹¤’Êj
	]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD				Print_DelSecure_Notice(
						 UBYTE Mode )	/*ˆóüƒ‚[ƒh*/
{
	UBYTE	i;						/*loop*/
	UBYTE	mail_cnt;					/*ÃÞ°À¶³ÝÄ*/
	UBYTE	page;						/*Íß°¼Þ*/
	UBYTE	line_cnt;					/*s”*/
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	/*Á‹ŽÃÞ°À‘¶ÝŒŸ¸*/
	if ( Mode == LST_DELSECURE_NOTICE ) {
		if ( SYB_MailBox[SYS_DocumentPrintNo].Status != SYS_MAILBOX_RECEIVE ) {
			return ( MSG_PRN_LST_NO_LIST );
		}
	}
	else {
		if ( Check_AnyList( LST_DELSECURE_NOTICE ) == MSG_PRN_LST_NO_LIST ) {
			return ( MSG_PRN_LST_NO_LIST );
		}
	}

	mail_cnt	= 0;
	page		= 1;
	while( mail_cnt != SYS_MAILBOX_MAX ){
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}

		if ( page == 1 ) {
			line_cnt = (UBYTE)(PaperSizeLen() - 15);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		else {
			line_cnt = (UBYTE)(PaperSizeLen() - 6);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		if ( (ret = Print_DelSecure_Notice_Head( 0, page ) ) != OK ) {/*Í¯ÀÞˆóü*/
			return ( ret );
		}
		if ( Mode == LST_DELSECURE_NOTICE ) {
			if ( SYB_MailBox[SYS_DocumentPrintNo].Status == SYS_MAILBOX_RECEIVE ) {
				if ( (ret = Print_DelSecure_Notice_Specifi((UBYTE)SYS_DocumentPrintNo, Mode)) != OK ) {
					return ( ret );
				}
				if ( (ret = Print_DelSecure_Notice_Head( 1, page ) ) != OK ) {/*Í¯ÀÞˆóü*//* ’Ç‰Á1997/10/18 Y.Matsukuma */
					return ( ret );
				}
				SYB_MailBox[SYS_DocumentPrintNo].Status = SYS_MAILBOX_SET;
				MEM_ClearDocAndFATArea( (UBYTE)SYS_MEM_SECURE_RX_FILE, SYS_DocumentPrintNo, MEM_IGNORE_BOX_NUMBER);
				break;
			}
		}
		else {
			for ( i = 0; line_cnt >= 2; i++ ) {
				while ( mail_cnt < SYS_MAILBOX_MAX ) {
					if (( SYB_MailBox[mail_cnt].Status == SYS_MAILBOX_RECEIVE ) &&
						( MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE,mail_cnt, MEM_IGNORE_BOX_NUMBER)
																 == MEM_NO_INDEX )) {
						break;
					}
					mail_cnt++;
				}
				if( mail_cnt >= SYS_MAILBOX_MAX ){
					break;
				}
				/*†¾†¢†¢†¢†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†Æ*/
				if(( page == 1 ) ||					/* ‚Pƒy[ƒW–Ú‚ÌŽž */
				   (( page != 1 ) && ( i != 0 ))){	/* 1ƒy[ƒW,‚Ps–ÚˆÈŠO‚ÌŽž */
					Print_Secure_Notice_List( 2, List.S.Print, List.S.Attribute	 );
					if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
						return ( ret );
					}
				}
				if ( (ret = Print_DelSecure_Notice_Specifi( mail_cnt, Mode )) != OK ) {
					return ( ret );
				}
				SYB_MailBox[mail_cnt].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
				SYB_MailBox[mail_cnt].Status = SYS_MAILBOX_SET;
				line_cnt	-= 2;
				mail_cnt++;
			}
		}
		if ( (ret = Print_DelSecure_Notice_Head( 1, page ) ) != OK ) {/*Í¯ÀÞˆóü*/
			return ( ret );
		}
		while ( mail_cnt < SYS_MAILBOX_MAX ) {
			if (( SYB_MailBox[mail_cnt].Status == SYS_MAILBOX_RECEIVE ) &&
				( MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE,mail_cnt, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX )) {
				break;
			}
			mail_cnt++;
		}
		if( mail_cnt >= SYS_MAILBOX_MAX ){
			break;
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}

	/* ¼ÝÃÝ¼Þ­¼Ý ¹ÞÝº³¶Þ ¼®³·® »ÚÏ¼À ..*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	AttributeSet( &List.S.Print[21-1], &List.S.Attribute[21-1],
	  PWRD_ThisSecMailEra, LST_NOT );
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
WORD				Print_DelSecure_Notice_Head(
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
			List.S.Print[20-1] = LST_KLINE7;
			CMN_MemorySet( &List.S.Print[21-1], 40, LST_KLINE_ );
			List.S.Print[61-1] = LST_KLINE9;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤ƒVƒ“ƒeƒ“ƒWƒ…ƒVƒ“@ƒVƒ‡ƒEƒLƒ‡@ƒcƒEƒ`†¤*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[20-1] = LST_KLINEI;
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			AttributeSet( &List.S.Print[23-1], &List.S.Attribute[23-1],
			 PWRD_ErasedDocuments_K, LST_NOT );			/* MES¨INV 94.7.20 ->NOT 8.10 */
#else
			AttributeSet( &List.S.Print[23-1], &List.S.Attribute[23-1],
			  PWRD_ErasedDocuments, LST_MES_TWI_XXX );
#endif
			List.S.Print[61-1] = LST_KLINEI;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†¢†º*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[20-1] = LST_KLINE1;
			CMN_MemorySet( &List.S.Print[21-1], 40, LST_KLINE_ );
			List.S.Print[61-1] = LST_KLINE3;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}

			/*Œ»ÝŽžŠÔ*/
			if ( (ret = CurrentTimePrint( 41-1 )) != OK ) {
				return ( ret );
			}

			/*†®†¢†¢†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†²*/
			Print_Secure_Notice_List( 0, List.S.Print, List.S.Attribute	 );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤No†¤¼ÝÃÝ¼¬Ò²†¤ ±²Ã»·Ò²@@†¤*/
			Print_Secure_Notice_List( 1, List.S.Print, List.S.Attribute	 );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

		}
		else{
			/*‚QsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED +2 )) != OK ) {
				return ( ret );
			}

			/*†®†¢†¢†¢†¢†¢†¢†Î†¢†¢†¢†¢†¢†¢†²*/
			Print_Secure_Notice_List( 0, List.S.Print, List.S.Attribute	 );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
	}
	else{
		/*†¶†¢†¢†¢†¢†¢†¢†Ö†¢†¢†¢†¢†¢†¢†º*/
		Print_Secure_Notice_List( 4, List.S.Print, List.S.Attribute	 );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
	}
}

/*************************************************************************
	module		:[e“WŽóMÁ‹Ž’Ê’m‚Ì–¾×•”ˆóü]
	function	:[e“WŽóMÁ‹Ž’Ê’m‚Ì–¾×•”•ª‚ðˆóü‚·‚é]
	common		:[
		List		:
		SYB_MailBox	:
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
WORD				Print_DelSecure_Notice_Specifi(UBYTE MailNumber , /*e“WŽóMƒf[ƒ^”Ô†*/
												   UBYTE mode)		  /*ˆóüƒ‚[ƒh*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if (mode == LST_DELSECURE_NOTICE) {	/* ’Ç‰Á	1997/10/18 Y.Matsukuma */
		/*†¾†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†¢†¢†¢†¢†Æ*/
		Print_Secure_Notice_List( 2, List.S.Print, List.S.Attribute	 );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}

	/*†¤9†¤xxxxxxxx†¤xxxxxxxxxxxx†¤*/
	Print_Secure_Notice_List( 3, List.S.Print, List.S.Attribute	 );
	/* No. */
#if ( PRO_CPU == SH7043 )	/* FX,MML‚Åe“WBOXNo.‚ªA0`or1`‚Æˆá‚¤Žž‚Ì‚½‚ß */
	CMN_UnsignedIntToASC( &List.S.Print[21-1], (UWORD)MailNumber + ( OPR_MAILBOX_MIN ), 2, ' ' );
#else
	CMN_UnsignedIntToASC( &List.S.Print[22-1], (UWORD)MailNumber, 1, '0' );
#endif
	/*¼ÝÃÝ¼¬Ò²*/
	CMN_StringCopy( &List.S.Print[24-1], &SYB_MailBox[MailNumber].BoxName[0] );
	/*±²Ã»·Ò²*/
	CMN_StringCopy( &List.S.Print[41-1], &SYB_MailBox[MailNumber].RemoteName[0]);
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

