/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_GRP.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1997/03/11
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ƒOƒ‹[ƒvƒŠƒXƒg
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysonep.h"
#include	"\src\atlanta\define\sysspeed.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\uni_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_v\rom_tbl.h"

#if (PRO_PANEL == ANK)
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#endif

#if (PRO_PANEL == KANJI)
#include	"\src\atlanta\opr\kanji\define\opr_def.h"
#include	"\src\atlanta\opr\KANJI\ext_v\opr_data.h"
#endif

#if (PRO_OKI == ENABLE)	/* by K.Watanabe 1999/02/09 */
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#endif

/*************************************************************************
	module		:[ƒOƒ‹[ƒvƒŠƒXƒgˆóü]
	functiom	:[ƒOƒ‹[ƒvƒŠƒXƒg‚ðˆóü‚·‚é]
	common		:[
		List				:
		SYB_OptionalSpeed	:
		SYB_OnetouchDial	:
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
WORD				Print_Group_List(
						 void )				/*‚È‚µ*/
{
	UBYTE	i;						/*loop*/
	UBYTE	page;					/*Íß°¼Þ*/
	UBYTE	group_cnt;				/*ÃÞ°À”Ô†*/
	UBYTE	soflag;					/*’Zk^ÜÝÀ¯Á Ì×¸Þ*/
											/*	LST_SPEED*/
											/*	LST_ONETOUCH*/
	UBYTE	line_cnt;				/*s”*/
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	soflag = LST_SPEED;
	page = 1;
	group_cnt = 0;
	while ( group_cnt != GROUP_END ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		if ( page == 1 ) {
			line_cnt = (UBYTE)(PaperSizeLen() - 11);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		else {
			line_cnt = (UBYTE)(PaperSizeLen() - 4);/*ˆóü‰Â”\s”¾¯Ä*/
		}
		if ( (ret = Print_Group_List_Head( 0, page ) ) != OK ) {/*Í¯ÀÞˆóü*/
			return ( ret );
		}
		for ( i = 0; line_cnt >= 2; i++, line_cnt -= 2 ) {
			GroupDataNextSearch( &soflag, &group_cnt );			/*ŽŸÃÞ°À»°Á*/
			if ( group_cnt == GROUP_END ) {
				break;
			}
			if ( (ret = Print_Group_List_Specifi( page ,i, soflag,
			  group_cnt) ) != OK ) {							/*1–¾×ˆóü*/
				return ( ret );
			}
			group_cnt++;
		}
		if ( (ret = Print_Group_List_Head( 1, page) ) != OK ) {	/*Ì¯Àˆóü*/
			return ( ret );
		}
		if ( group_cnt != GROUP_END ) {
			GroupDataNextSearch( &soflag, &group_cnt );			/*ŽŸÃÞ°À»°Á*/
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	return ( OK );
}

/*************************************************************************
	module		:[ƒOƒ‹[ƒvƒŠƒXƒgƒwƒbƒ_ˆóü]
	functiom	:[ƒOƒ‹[ƒvƒŠƒXƒg‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
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
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD				Print_Group_List_Head(
						 UBYTE Category,	/*ƒwƒbƒ_Ží—Þ*/
						 UBYTE Page )		/*ƒy[ƒW*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Category == 0 ) {
		if ( Page == 1 ) {

			/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs{Œ©o‚µ{‚P‰üs*/
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		if ( (ret = Print_Head1_Common(PWRD_GroupDirectory_K, LST_NOT, 21-1 )) != OK ) {
			return ( ret );
		}

#else
	if ( (ret = Print_Head1_Common(PWRD_GroupDirectory, LST_XXX_TWI_XXX, 21-1 )) != OK ) {
		return ( ret );
	}

#endif

			/*Œ»ÝŽžŠÔ*/
			/*Page Œ»ÝŽžŠÔ*/
			if ( (ret = PageTimePrint( Page, 2-1, 60-1 )) != OK ) {
				return ( ret );
			}

			/*†®†¢†Î†¢†¢†Î†¢†¢†¢†¢†¢†²*/
			Print_Group_List_Line( 0, List.S.Print, List.S.Attribute );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}

			/*†¤No.	 †¤±²Ã»·Ò²†¤1 2 3 4 5 6 7 8 9 0 ` 1 2 3 4 5 6 7 8 9 0†¤*/
			Print_Group_List_Line( 1, List.S.Print, List.S.Attribute );
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
		/*†¶†¢†Ö†¢†¢†Ö†¢†¢†¢†¢†¢†º*/
		Print_Group_List_Line( 3, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
	}
	return( OK );
}

/*************************************************************************
	module		:[ƒOƒ‹[ƒvƒŠƒXƒg ƒlƒNƒXƒg ƒT[ƒ`n
	functiom	:[ƒOƒ‹[ƒvƒŠƒXƒg‚ÌŽŸƒf|ƒ^‚ðƒT[ƒ`‚·‚é]
	common		:[
		SYB_SpeedDial		:
		SYB_OnetouchDial	:
	]
	condition	:[
		’Zk^ƒƒ“ƒ^ƒbƒ`ƒtƒ‰ƒO
			LST_SPEED
			LST_ONETOUCH
		ƒf[ƒ^”Ô†
			ƒf[ƒ^‚È‚µ->GROUP_END
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
void				GroupDataNextSearch(
						 register UBYTE *SoFlag,/*’Zk^ƒƒ“ƒ^ƒbƒ`ƒtƒ‰ƒO*/
						 register UBYTE *GroupCnt )	/*ƒf[ƒ^”Ô†*/
{
	UBYTE	i;						/*loop*/

	if ( *SoFlag == LST_SPEED
		&& *GroupCnt >= SYS_SPEED_DIAL_MAX+SYS_2ND_SPEED_DIAL_MAX ) {
		*SoFlag = LST_ONETOUCH;
		*GroupCnt = 0;
	}
	if ( *SoFlag == LST_SPEED ) {
		for ( i = (*GroupCnt); i < SYS_SPEED_DIAL_MAX+SYS_2ND_SPEED_DIAL_MAX; i++ ) {
			if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
				if ( SYB_OptionalSpeed[i].Number != 0xFFFF
				  && SYB_SpeedDial[SYB_OptionalSpeed[i].Record].Group != 0 ) {
					(*GroupCnt) = i;
					break;
				}
			}
			else{	/* ’Êí‚Ì’Zk‚ÌŽž */

#if (0)
** 				/* ‚h‚b‚g‚n‚t‚©‚ç‚ÌƒtƒB[ƒhƒoƒbƒN By O.Kimoto 1998/03/30 */
** 				/*
** 				** ƒŠƒ‚[ƒgf’f‚ª–¢“o˜^‚È‚ç‚e‚O‚ð‘‚­ê‡‚ª‚ ‚é‚Ì‚Å‚e‚e‚ÅŒ©‚Ä‚¢‚é‚Æ‚¨‚©‚µ‚­‚È‚é
** 				** 1997/10/03 M.Shimizu
** 				*/
** 				if ( SYB_SpeedDial[i].Dial[0] != LST_DIAL_NOT
** 				  && SYB_SpeedDial[i].Group != 0 ) {
** 					(*GroupCnt) = i;
** 					break;
** 				}
#else
				if ( (SYB_SpeedDial[i].Dial[0] & 0xF0) != 0xF0
				  && SYB_SpeedDial[i].Group != 0 ) {
					(*GroupCnt) = i;
					break;
				}
#endif
			}
		}
		if ( i == SYS_SPEED_DIAL_MAX+SYS_2ND_SPEED_DIAL_MAX ) {
			*SoFlag = LST_ONETOUCH;
			*GroupCnt = 0;
		}
	}

	if ( *SoFlag == LST_ONETOUCH ) {
		for ( i = (*GroupCnt); i < SYS_2ND_ONETOUCH_MAX+SYS_ONETOUCH_MAX; i++ ) {

#if (0)
** 			/* ‚h‚b‚g‚n‚t‚©‚ç‚ÌƒtƒB[ƒhƒoƒbƒN By O.Kimoto 1998/03/30 */
** 			/*
** 			** ƒŠƒ‚[ƒgf’f‚ª–¢“o˜^‚È‚ç‚e‚O‚ð‘‚­ê‡‚ª‚ ‚é‚Ì‚Å‚e‚e‚ÅŒ©‚Ä‚¢‚é‚Æ‚¨‚©‚µ‚­‚È‚é
** 			** 1997/10/03 M.Shimizu
** 			*/
** 			if ( SYB_OnetouchDial[i].Dial[0] != LST_DIAL_NOT
** 			  && SYB_OnetouchDial[i].Group != 0 ) { /* \‘¢‘Ì•Ï”‚Ì•ÏX For ANZU By H.Hirao 95/12/15 */
** 				(*GroupCnt) = i;
** 				break;
** 			}
#else
			if ( (SYB_OnetouchDial[i].Dial[0] & 0xF0) != 0xF0
			  && SYB_OnetouchDial[i].Group != 0 ) { /* \‘¢‘Ì•Ï”‚Ì•ÏX For ANZU By H.Hirao 95/12/15 */
				(*GroupCnt) = i;
				break;
			}
#endif

		}
	}

	if ( *SoFlag == LST_ONETOUCH && i == SYS_2ND_ONETOUCH_MAX+SYS_ONETOUCH_MAX ) {
		(*GroupCnt) = GROUP_END;
	}
}

/*************************************************************************
	module		:[ƒOƒ‹[ƒvƒŠƒXƒg‚Ì‚P–¾×ˆóü]
	functiom	:[ƒOƒ‹[ƒvƒŠƒXƒg‚Ì‚P–¾×‚ðˆóü‚·‚éB]
	common		:[
		List				:
		SYB_SpeedDial		:
		SYB_OnetouchDial	:
	]
	condition	:[
		’Zk^ƒƒ“ƒ^ƒbƒ` Ì×¸Þ
			LST_SPEED
			LST_ONETOUCH
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD					Print_Group_List_Specifi(
						 UBYTE Page,		/*ƒy[ƒW*/
						 UBYTE Line,		/*Œ»Ý–¾×”*/
						 UBYTE SoFlag,		/*’Zk^ƒƒ“ƒ^ƒbƒ`ƒtƒ‰ƒO*/
						 UBYTE GroupCnt )	/*ƒf[ƒ^”Ô†*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Page > 1 && Line == 0 ) {
		/*†®†¢†Î†¢†¢†Î†¢†¢†¢†¢†¢†²*/
		Print_Group_List_Line( 0, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	else {
		/*†¾†¢†Þ†¢†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†Æ*/
		Print_Group_List_Line( 2, List.S.Print, List.S.Attribute );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}

	if ( SoFlag == LST_SPEED ) {
		/*†¤999)†¤xxxxxx†¤x x x x x x ` x†¤*/
		if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
			if ( (ret = Print_Group_List_Common( SoFlag, GroupCnt, 
				SYB_SpeedDial[SYB_OptionalSpeed[GroupCnt].Record].Name, 
				SYB_SpeedDial[SYB_OptionalSpeed[GroupCnt].Record].Group )) != OK ) {
				return ( ret );
			}
		}
		else{	/* ’Êí‚Ì’Zk‚ÌŽž */
			if ( (ret = Print_Group_List_Common( SoFlag, GroupCnt,
			  SYB_SpeedDial[GroupCnt].Name, SYB_SpeedDial[GroupCnt].Group )) != OK ) {
				return ( ret );
			}
		}
	}
	else {
		/*†¤999)†¤xxxxxx†¤x x x x x x ` x†¤*/
		if ( (ret = Print_Group_List_Common( SoFlag, GroupCnt,
		  SYB_OnetouchDial[GroupCnt].Name, SYB_OnetouchDial[GroupCnt].Group )) != OK ) { 
			return ( ret );
		}
	}
	return ( OK );
}

/*************************************************************************
	module		:[ƒOƒ‹[ƒvƒŠƒXƒg–¾×ˆóü]
	functiom	:[ƒOƒ‹[ƒvƒŠƒXƒg‚Ì–¾×•”•ª‚ðˆóü‚·‚é]
	common		:[
		List	:
	]
	condition	:[
		’Zk^ƒƒ“ƒ^ƒbƒ`ƒtƒ‰ƒO
			LST_SPEED
			LST_ONETOUCH
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD					Print_Group_List_Common(
						 UBYTE SoFlag,		/*’Zk^ƒƒ“ƒ^ƒbƒ`ƒtƒ‰ƒO*/
						 UBYTE Number,		/*”Ô†*/
						 UBYTE *Name,	/*–¼Ì*/
						 UDWORD		Group )		/*ƒOƒ‹[ƒv*/
{
	UBYTE	j;						/*loop*/
	UBYTE	len;					/*•¶Žš”*/
	UDWORD	bit;					/*¸ÞÙ°ÌßËÞ¯Ä*/
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/
	UBYTE	figure;		/* 2002/02/08 By M.maeda */

	/*†¤999†¤xxxxxx†¤x x x x x x ` x†¤*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[1-1] = LST_KLINEI;
	/* No. */
	if ( SoFlag == LST_SPEED ) {
		if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			if ( SYS_SPEED_DIAL_MAX+SYS_2ND_SPEED_DIAL_MAX >= 100 ) {
 #if (1) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
				CMN_UnsignedIntToASC( &List.S.Print[2-1], (UWORD)SYB_OptionalSpeed[Number].Number,
				  OP_SPEED_FIGURE_MAX, '0' );
 #else
//				CMN_UnsignedIntToASC( &List.S.Print[2-1], (UWORD)SYB_OptionalSpeed[Number].Number,
//				  3, '0' );
 #endif
			}
			else {
				CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)SYB_OptionalSpeed[Number].Number,
				  2, '0' );
			}
#else	/* PANEL_POPLA_B/L/H */
#if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
			List.S.Print[2-1]	= *CalculateStringAddress(&D2W_HeadCharacter_Speed);
#else
			List.S.Print[2-1]	= 'S';
#endif
 #if (1) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */
			CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)SYB_OptionalSpeed[Number].Number, OP_SPEED_FIGURE_MAX, '0' );
 #else
//			CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)SYB_OptionalSpeed[Number].Number, 3, '0' );
 #endif
#endif	/* PANEL_ANZU_L */
		}
		else{		/* ’Êí‚Ì’Zk‚ÌŽž */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			if ( SYS_SPEED_DIAL_MAX+SYS_2ND_SPEED_DIAL_MAX >= 100 ) {
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
				CMN_UnsignedIntToASC( &List.S.Print[2-1], (UWORD)Number+(OPR_SPEED_DIAL_MIN), 3, '0' );
 #else
				CMN_UnsignedIntToASC( &List.S.Print[2-1], (UWORD)Number+1, 3, '0' );
 #endif
			}
			else {
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
				CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)Number+(OPR_SPEED_DIAL_MIN), 2, '0' );
 #else
				CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)Number+1,2, '0' );
 #endif
			}
#elif (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (F250‚Í’Zkƒ_ƒCƒ„ƒ‹‚ÍÅ‘å80Œ‚Å‚·‚©‚çA’ZkÀÞ²ÔÙNoA‚ªS01AS02`S80‚Ü‚Å‚É•ÏX‚·‚é‚±‚Æ) Added by SMuratec L.Z.W 2003/10/09 */
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
  #if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
			List.S.Print[2-1]	= *CalculateStringAddress(&D2W_HeadCharacter_Speed);
  #else
			List.S.Print[2-1]	= 'S';
  #endif
			CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)Number+(OPR_SPEED_DIAL_MIN), OP_SPEED_FIGURE_MAX, '0' );
 #else
			CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)Number+1, OP_SPEED_FIGURE_MAX, '0' );
 #endif
#else	/* PANEL_POPLA_B/L/H */
 #if ( PRO_CPU == SH7043 )	/* FX,MML‚Å’ZkÀÞ²ÔÙNo.‚ªA000`or001`‚Æˆá‚¤Žž‚Ì‚½‚ß */
  #if (PRO_OKI == ENABLE)	/* ŠCŠO‚Å‚Í’Zk“™‚Ì“ª•¶Žš‚ª‰pŒê‚Æˆá‚¤‚Ì‚ÅA•ÏX‚Å‚«‚é‚æ‚¤‚É‚µ‚Ü‚· by K.Watanabe 1999/02/09 */
			List.S.Print[2-1]	= *CalculateStringAddress(&D2W_HeadCharacter_Speed);
  #else
			List.S.Print[2-1]	= 'S';
  #endif
			CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)Number+(OPR_SPEED_DIAL_MIN), 3, '0' );
 #else
			CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)Number+1, 3, '0' );
 #endif
#endif	/* PANEL_ANZU_L */
		}
	}
	else {
		/* List.S.Print[2-1] = '[';
		List.S.Print[3-1] = CMN_OffsetToOnetouchCode( Number );
		List.S.Print[4-1] = ']'; */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		if ( CMN_OffsetToOnetouchCode( Number ) <= 0x7A ){ /* ÜÝÀ¯Á‹L†‚ª•ÏX For ANZU By H.Hirao 1996/01/10 */
			List.S.Print[2-1] = CMN_OffsetToOnetouchCode( Number );
		} else{
			List.S.Print[2-1] = 0x55;	/* 'U'‚ÌASCIIº-ÄÞ */
			List.S.Print[3-1] = CMN_OffsetToOnetouchCode( Number ) & (UBYTE)0x0F | (UBYTE)0x30; /* U1`U8‹L†‚ð‚Â‚­‚é */
		}
#else	/* PANEL_POPLA_B/L/H */
 #if (PRO_PANEL == ANK)
		List.S.Print[2-1] = '[';
		List.S.Print[5-1] = ']';
		CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)(CMN_OffsetToOnetouchCode( Number ) - 0x40), 2, '0' );
 #endif
 #if (PRO_PANEL == KANJI)
 		/* ƒƒ“ƒ^ƒbƒ`‚Ì•\Ž¦‚ð[]->ŠG•¶Žš‚É•ÏX By O.Kimoto 1998/01/22 */
		List.S.Print[2-1] = LCD_PICFONT;
		List.S.Print[3-1] = LCD_PICFONT_LOWER;
		CMN_UnsignedIntToASC( &List.S.Print[4-1], (UWORD)(CMN_OffsetToOnetouchCode( Number ) - 0x40), 2, '0' );
 #endif
#endif	/* PANEL_ANZU_L */
	}
#if (PRO_OP_SPPED_4_FIGURE == ENABLE) /* ”CˆÓ’Zk‚SŒ…‰» 2002/02/13 By M.Maeda */	/* if 1 ‚É‚È‚Á‚Ä‚¢‚½‚ªA‚RŒ…Žž‚É•¶Žš‚ª‚¸‚ê‚é‚Ì‚ÅðŒ‚Â‚¯‚Ü‚· 2003/01/07 T.Takagi */
	if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
		List.S.Print[7-1] = LST_KLINEI;
	}
	else {
		List.S.Print[6-1] = LST_KLINEI;
	}
	/*±²Ã»·Ò²*/
	if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
		figure = 8;
	}
	else {
		figure = 9;
	}

	len = (UBYTE)CMN_StringLength(Name);
	if ( len > figure ) {
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		for (j = 0; j <= figure - 1; j++) {
			if ( (0x80 <= *(Name+j)) && (0x9f >= *(Name+j)) ) {
				if (j == figure - 1) {
					break;
				}
				else {
					j++;
				}
			}
		}
		len = j;
 #else
		len = figure;
 #endif
	}
	if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
		CMN_StringCopyNum( &List.S.Print[8-1], Name, len );
	}
	else {
		CMN_StringCopyNum( &List.S.Print[7-1], Name, len );
	}
#else
	List.S.Print[6-1] = LST_KLINEI;
	/*±²Ã»·Ò²*/
	len = (UBYTE)CMN_StringLength(Name);
	if ( len > 9 ) {
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		for (j = 0; j <= 7; j++) {
			if ( (0x80 <= *(Name+j)) && (0x9f >= *(Name+j)) ) {
				if (j == 7) {
					break;
				}
				else {
					j++;
				}
			}
		}
		len = j;
 #else
		len = 9;
 #endif
	}
	CMN_StringCopyNum( &List.S.Print[7-1], Name, len );
#endif
	List.S.Print[16-1] = LST_KLINEI;
	/*¸ÞÙ°Ìß*/
	bit = 1;
	for ( j = 0; j < LST_GROUP_BIT; j++ ) {
		if ( (Group & bit) == bit) {
			List.S.Print[17-1+j*2] = (UBYTE)(0x30+((j+1) % 10));
		}
		bit <<= 1;
	}
	List.S.Print[80-1] = LST_KLINEI;
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	return ( OK );
}

/*************************************************************************
	module		:[ƒOƒ‹[ƒvƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrüì¬]
	functiom	:[ƒOƒ‹[ƒvƒŠƒXƒg‚Ì‰¡‹æØ‚èŒrü‚ðì¬‚·‚éB]
	common		:[]
	condition	:[
		ŒrüŽí—Þ
			0 = †®†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†²
			1 = †¤No. †¤		†¤ 00 †¤ 10 †¤ 20 †¤ 30 †¤
			2 = †¾†¢†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†Æ
			3 = †¶†¢†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†Ö†¢†¢†Ö†¢†¢†Ö†¢†¢†º
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
void				Print_Group_List_Line(
						 UBYTE Category,				/*ŒrüŽí—Þ*/
						 register UBYTE *AscString,		/*ˆóü•¶Žš—ñ*/
						 register UBYTE *AttString )	/*Cü•¶Žš—ñ*/
{
#if (PRO_OPTIONAL_SPEED == ENABLE) && (PRO_OP_SPPED_4_FIGURE == ENABLE)
	if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚ÌŽž */
		Prn_Att_Str_Clear( AscString, AttString );
		switch ( Category ) {
		case 0:
			/*†®†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†²*/
			AscString[1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_ );
			AscString[7-1] = LST_KLINE8;
			AscString[16-1] = LST_KLINE8;
			AscString[34-1] = LST_KLINE8;
			AscString[54-1] = LST_KLINE8;
			AscString[74-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE9;
			break;
		case 1:
			/*†¤No. †¤±²Ã»·Ò² †¤ 00 †¤ 10 †¤ 20 †¤ 30 †¤*/
			AscString[1-1] = LST_KLINEI;
			AscString[7-1] = LST_KLINEI;
	/*			AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_No, LST_NOT );*/
			AttributeSet( &AscString[3-1], &AttString[3-1], PWRD_No, LST_NOT );		/* 2 -> 3 97/03/07 M.Kuwahara */
			AttributeSet( &AscString[8-1], &AttString[8-1], PWRD_Location, LST_NOT );
			AscString[16-1] = LST_KLINEI;
			AscString[34-1] = LST_KLINEI;
			AscString[54-1] = LST_KLINEI;
			AscString[74-1] = LST_KLINEI;
			AscString[80-1] = LST_KLINEI;
			AscString[24-1] = '0';
			AscString[25-1] = '0';
 #if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )		/* MES¨INV 94.7.20 ->NOT 8.10 */
			CMN_MemorySet( &AttString[23-1], 4, LST_NOT );
			AscString[44-1] = '1';
			AscString[45-1] = '0';
			CMN_MemorySet( &AttString[43-1], 4, LST_NOT );
			AscString[64-1] = '2';
			AscString[65-1] = '0';
			CMN_MemorySet( &AttString[63-1], 4, LST_NOT );
			AscString[77-1] = '3';
			AscString[78-1] = '0';
			CMN_MemorySet( &AttString[76-1], 4, LST_NOT );
 #else
			CMN_MemorySet( &AttString[23-1], 4, LST_MES_XXX_XXX );
			AscString[44-1] = '1';
			AscString[45-1] = '0';
			CMN_MemorySet( &AttString[43-1], 4, LST_MES_XXX_XXX );
			AscString[64-1] = '2';
			AscString[65-1] = '0';
			CMN_MemorySet( &AttString[63-1], 4, LST_MES_XXX_XXX );
			AscString[77-1] = '3';
			AscString[78-1] = '0';
			CMN_MemorySet( &AttString[76-1], 4, LST_MES_XXX_XXX );
 #endif
			break;
		case 2:
			/*†¾†¢†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†Æ*/
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_ );
			AscString[7-1] = LST_KLINE5;
			AscString[16-1] = LST_KLINE5;
			AscString[34-1] = LST_KLINE5;
			AscString[54-1] = LST_KLINE5;
			AscString[74-1] = LST_KLINE5;
			AscString[80-1] = LST_KLINE6;
			break;
		case 3:
			/*†¶†¢†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†Ö†¢†¢†Ö†¢†¢†Ö†¢†¢†º*/
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 79, LST_KLINE_ );
			AscString[7-1] = LST_KLINE2;
			AscString[16-1] = LST_KLINE2;
			AscString[34-1] = LST_KLINE2; /* ’Ç‰Á Î‹´³˜a 94/10/19 */
			AscString[54-1] = LST_KLINE2; /* ’Ç‰Á Î‹´³˜a 94/10/19 */
			AscString[74-1] = LST_KLINE2; /* ’Ç‰Á Î‹´³˜a 94/10/19 */
			AscString[80-1] = LST_KLINE3;
			break;
		}
		return;
	}
#endif /* #if (PRO_OPTIONAL_SPEED == ENABLE) && (PRO_OP_SPPED_4_FIGURE == ENABLE) */

	Prn_Att_Str_Clear( AscString, AttString );
	switch ( Category ) {
		case 0:
			/*†®†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†²*/
			AscString[1-1] = LST_KLINE7;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[6-1] = LST_KLINE8;
			AscString[16-1] = LST_KLINE8;
			AscString[34-1] = LST_KLINE8;
			AscString[54-1] = LST_KLINE8;
			AscString[74-1] = LST_KLINE8;
			AscString[80-1] = LST_KLINE9;
			break;
		case 1:
			/*†¤No. †¤±²Ã»·Ò² †¤ 00 †¤ 10 †¤ 20 †¤ 30 †¤*/
			AscString[1-1] = LST_KLINEI;
			AscString[6-1] = LST_KLINEI;
/*			AttributeSet( &AscString[2-1], &AttString[2-1], PWRD_No, LST_NOT );*/
			AttributeSet( &AscString[3-1], &AttString[3-1], PWRD_No, LST_NOT );		/* 2 -> 3 97/03/07 M.Kuwahara */
			AttributeSet( &AscString[7-1], &AttString[7-1], PWRD_Location, LST_NOT );
			AscString[16-1] = LST_KLINEI;
			AscString[34-1] = LST_KLINEI;
			AscString[54-1] = LST_KLINEI;
			AscString[74-1] = LST_KLINEI;
			AscString[80-1] = LST_KLINEI;
			AscString[24-1] = '0';
			AscString[25-1] = '0';
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )		/* MES¨INV 94.7.20 ->NOT 8.10 */
			CMN_MemorySet( &AttString[23-1], 4, LST_NOT );
			AscString[44-1] = '1';
			AscString[45-1] = '0';
			CMN_MemorySet( &AttString[43-1], 4, LST_NOT );
			AscString[64-1] = '2';
			AscString[65-1] = '0';
			CMN_MemorySet( &AttString[63-1], 4, LST_NOT );
			AscString[77-1] = '3';
			AscString[78-1] = '0';
			CMN_MemorySet( &AttString[76-1], 4, LST_NOT );
#else
			CMN_MemorySet( &AttString[23-1], 4, LST_MES_XXX_XXX );
			AscString[44-1] = '1';
			AscString[45-1] = '0';
			CMN_MemorySet( &AttString[43-1], 4, LST_MES_XXX_XXX );
			AscString[64-1] = '2';
			AscString[65-1] = '0';
			CMN_MemorySet( &AttString[63-1], 4, LST_MES_XXX_XXX );
			AscString[77-1] = '3';
			AscString[78-1] = '0';
			CMN_MemorySet( &AttString[76-1], 4, LST_MES_XXX_XXX );
#endif
			break;
		case 2:
			/*†¾†¢†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†Þ†¢†¢†Æ*/
			AscString[1-1] = LST_KLINE4;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[6-1] = LST_KLINE5;
			AscString[16-1] = LST_KLINE5;
			AscString[34-1] = LST_KLINE5;
			AscString[54-1] = LST_KLINE5;
			AscString[74-1] = LST_KLINE5;
			AscString[80-1] = LST_KLINE6;
			break;
		case 3:
			/*†¶†¢†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†Ö†¢†¢†Ö†¢†¢†Ö†¢†¢†º*/
			AscString[1-1] = LST_KLINE1;
			CMN_MemorySet( &AscString[2-1], 78, LST_KLINE_ );
			AscString[6-1] = LST_KLINE2;
			AscString[16-1] = LST_KLINE2;
			AscString[34-1] = LST_KLINE2; /* ’Ç‰Á Î‹´³˜a 94/10/19 */
			AscString[54-1] = LST_KLINE2; /* ’Ç‰Á Î‹´³˜a 94/10/19 */
			AscString[74-1] = LST_KLINE2; /* ’Ç‰Á Î‹´³˜a 94/10/19 */
			AscString[80-1] = LST_KLINE3;
			break;
	}
}

