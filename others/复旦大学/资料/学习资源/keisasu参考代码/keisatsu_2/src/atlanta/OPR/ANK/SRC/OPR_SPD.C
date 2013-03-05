/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_SPD.C
*	Author		: “n•ÓˆêÍ
*	Date		: 1996/10/23
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ’Zkƒ_ƒCƒAƒ‹ƒIƒyƒŒ[ƒVƒ‡ƒ“
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysonet.h"
#include	"\src\atlanta\define\sysspeed.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\memsw\define\mem_sw_b.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\ini_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

/* Prototype
void	EnterSpeedDial(void);
void	EraseSpeedDial(void);
void	PrintSpeedDialList(void);
UBYTE	SelectSpeedNumber(void);
UBYTE	InputSpeedOptionalNumber(void);
void	SpeedForwordOperation(void);
void	SpeedBackOperation(void);
void	SpeedOperationInitial(void);
void	SpeedSelectDisplay(void);
void	SpeedSelectOptionalDisplay(void);
UWORD	GetRecordFromNumber(UWORD);
UBYTE	SetOptionalSpeedStatus(UWORD);
UBYTE	GetSpeedEntryCount(void);
UBYTE	GetSpeedDialRecord(void);
void	SetSpeedControlTable(void);
void	DeleteSpeedControlTable(void);
UBYTE	CheckSpeedStoreStatus(UBYTE);
*/

/*************************************************************************
	module		:[’Zkƒ_ƒCƒ„ƒ‹“o˜^‹@”\]
	function	:[
		1.’Zkƒ_ƒCƒ„ƒ‹“o˜^‚Ì‹@”\‚ğÀs‚·‚é
		2.”CˆÓ’Zk”Ô†‘I‘ğ‚Å‚Ì’¼Ú“ü—Í‚Ì‚İ‚Ì•\¦‚ÍÅ‰‚¾‚¯
		  ‚Q“x–ÚˆÈ~‚Í•’Ê‚Ì’Zk”Ô†‘I‘ğ‰æ–Ê‚Æ“¯‚¶
	]
	common		:[]
	condition	:[]
	comment		:[
		“à•”‚©‚çŒ©‚½’Zk”Ô† 000`
		ŠO•”‚©‚çŒ©‚½’Zk”Ô† 001`
		“à•”ˆ—‚Å‚Íƒƒ“ƒ^ƒbƒ`’Zk‚ğ‚P‘±‚«‚Ìƒf[ƒ^‚Æl‚¦
		SYS_ONETOUCH_MAX ` SYS_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX - 1‚ª’Zk000`169‚Æ‚µ‚Äˆ—
		ƒ_ƒCƒAƒ‹ƒf[ƒ^‚Ì“o˜^“™‚Ì‰ºˆÊƒ‚ƒWƒ…[ƒ‹‚ÍOPR_DIAL.C‚É‚Ü‚Æ‚ß‚Ä‚ ‚é
		ƒƒ“ƒ^ƒbƒ`{’Zk‚ª‚Q‚T‚T‚ğ‰z‚¦‚éê‡Aì‚è‘Ö‚¦‚é•K—v‚ ‚è
	]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/19]
	author		:[]Œû]
*************************************************************************/
void EnterSpeedDial(void)
{
	SpeedOperationInitial();

	if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚Ì */
		if (InputSpeedOptionalNumber() == OPR_END) { /* ‚r‚s‚n‚o */
			return;
		}
	}
	/* ’Zk”Ô†‘I‘ğƒ‹[ƒv*/
	while (1) {
		/** “o˜^’Zkƒ_ƒCƒ„ƒ‹‚ğ‘I‘ğ‚·‚é */
		if (SelectSpeedNumber() == OPR_END) { /* ‚r‚s‚n‚o */
			return;
		}
		/** ’Zkƒ_ƒCƒAƒ‹ƒf[ƒ^ƒZƒbƒg‚ğs‚¤ */
		if (OnetouchSpeedInput() == OPR_END) { /* ‚r‚s‚n‚o */
			return;
		}

		/* Ÿ‚Ì“o˜^‚É”õ‚¦‚Ä’Zk”Ô†‚ği‚ß‚é */
		SpeedForwordOperation();
	}
}

/*************************************************************************
	module		:[’ZkÁ‹ƒIƒyƒŒ[ƒVƒ‡ƒ“]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-B2]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/07]
	author		:[]Œû]
*************************************************************************/
void EraseSpeedDial(void)
{
	UBYTE	speed_number;	/* ‘I‘ğ‚³‚ê‚½’Zk”Ô† */
	UBYTE	erase_step;		/* Á‹’iŠK */

	speed_number = 0;
	erase_step = ERASE_ITEM_SELECT_STEP;
	SpeedOperationInitial();

	if( CHK_UNI_OptionalSpeedDial() != 0 ){	/* ”CˆÓ’Zk‚Ì */
		if (InputSpeedOptionalNumber() == OPR_END) { /* ‚r‚s‚n‚o */
			return;
		}
	}

	while (1) {
		switch (erase_step) {
		case ERASE_ITEM_SELECT_STEP:	/* ‘I‘ğó‘Ô */
			if (SelectSpeedNumber() == OPR_END) { /* ‚r‚s‚n‚o */
				return;
			}
			speed_number = (UBYTE)(OPR_Buf.OntchSpdCtrl.SelectNumber - SYS_ONETOUCH_MAX);
			if (CheckSpeedStoreStatus(speed_number) == OK) {
				erase_step = ERASE_CONFIRM_STEP;
			}
			else {
				NackBuzzer();
			}
			break;
		case ERASE_CONFIRM_STEP:	/* ƒNƒŠƒAŠm”Fó‘Ô */
			switch (ConfirmKeyInputOperation((UBYTE *)D2W_EraseSpeedDial, D2W_CheckProgramEnter, ENTER, FUNCTION)) {
			case CONFIRM_EXEC:	/* Às */
				/* ’ZkÁ‹Às */
				ClearOnetouchSpeedRecord(&SYB_SpeedDial[speed_number]);
				DeleteTelBookData(OPR_Buf.OntchSpdCtrl.SelectNumber);   /* “d˜b’ ‚©‚ç‚àíœ */
				if( CHK_UNI_OptionalSpeedDial() != 0 ){		/* ”CˆÓ’Zk‚Ì */
					DeleteSpeedControlTable();
				}
				/* ƒ_ƒCƒŒƒNƒgƒ[ƒ‹–h~‹@”\—pˆ—i“o˜^‚µ‚½ÀŞ²ÔÙ‚Ì‰º‚SŒ…‚Ì‚İ•ÊÊŞ¯Ì§‚ÉŠi”[j by K.Watanabe 1997/10/22 */
				SYB_SpeedJunkDial[speed_number] = PickOutLastFourFigure(SYB_SpeedDial[speed_number].Dial, 40);
				erase_step = ERASE_COMPLETE_STEP;
				break;
			case CONFIRM_ABORT:	/* æ‚èÁ‚µ */
				erase_step = ERASE_ITEM_SELECT_STEP;
				break;
			case OPR_END:		/* ’†~Eƒ^ƒCƒ€ƒAƒbƒv */
				return;	
			default:
				break;
			}
			break;
		case ERASE_COMPLETE_STEP:	/* Á‹Š®—¹•\¦ */
			if (ClearCompleteDisplayOperation((UBYTE *)D2W_EraseSpeedDial) == OPR_CONTINUE) {
				erase_step = ERASE_ITEM_SELECT_STEP;
				SpeedForwordOperation();
			}
			else {
				return;
			}
			break;
		default:
			break;
		}
	}
}

/*************************************************************************
	module		:[’Zkƒ_ƒCƒAƒ‹ƒŠƒXƒg]
	function	:[
		1.’Zkƒ_ƒCƒAƒ‹ƒŠƒXƒg‚Ìˆóš‚Ì‹N“®‚ğ‚©‚¯‚é
		2.’Zkƒ_ƒCƒAƒ‹‚ª“o˜^‚³‚ê‚Ä‚¢‚é•K—v‚ª‚ ‚é
	]
	return		:[]
	common		:[SYB_SpeedDial]
	condition	:[]
	comment		:[‚g‚W‚©‚çˆÚA]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/19]
	author		:[]Œû]
*************************************************************************/
void PrintSpeedDialList(void)
{
	UBYTE	speed_number;	/*’ZkÀŞ²ÔÙ”Ô†*/

	for (speed_number = 0; speed_number < SYS_SPEED_DIAL_MAX; speed_number++ ){
		if (CheckSpeedStoreStatus(speed_number) == OK) {	/* “o˜^Ï‚İ */
			FinalListPrintOperation(LST_SPEEDDIAL_LIST);	/* ƒƒCƒ“‚ÉƒŠƒXƒg‹N“®ƒƒbƒZ[ƒW‘—M */
			return;
		}
	}
	NackBuzzer();
	OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
}

/*************************************************************************
	module		:[’Zk”Ô†‘I‘ğ]
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
	date		:[1995/07/24]
	author		:[]Œû]
*************************************************************************/
UBYTE SelectSpeedNumber(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	record_no;
	UWORD	speed_number;

	while (1) {
		SpeedSelectDisplay();
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case KEY_TIME_UP:
		case STOP:
			return (OPR_END);
		case ENTER:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition > 0) {
				NackBuzzer();
			}
			else {
				if( CHK_UNI_OptionalSpeedDial() != 0 ){		/* ”CˆÓ’Zk‚Ì */
					record_no = SetOptionalSpeedStatus( OPR_Buf.OntchSpdCtrl.SelectOptionalNumber );
					if( record_no != 0xff ){		/* ”CˆÓ’Zk”Ô‚ª‘¶İ‚·‚é */
						OPR_Buf.OntchSpdCtrl.SelectNumber = (UWORD)(SYS_ONETOUCH_MAX + record_no);
					}
					else{
						/** Œ”‚ªƒI[ƒo[‚µ‚Ä‚¢‚È‚¢‚©ƒ`ƒFƒbƒN */
						if( GetSpeedEntryCount() >= SYS_SPEED_DIAL_MAX ){
							NackBuzzer();
							OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
							return(OPR_END);
						}
						else{
							OPR_Buf.OntchSpdCtrl.SelectNumber = (UWORD)GetSpeedDialRecord();
							OPR_Buf.OntchSpdCtrl.SelectNumber += SYS_ONETOUCH_MAX;
						}
					}
				}
				return (OPR_CONTINUE);
			}
			break;
		case FUNCTION:
			/* ’Zk”Ô†‚ği‚ß‚é */
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition > 0) {
				/* ’Zk”Ô†‚ğƒeƒ“ƒL[‚Å“ü—Í’† */
				NackBuzzer();
			}
			else {
				SpeedForwordOperation();
			}
			break;
		case LEFT_ARROW:
			/* ’Zk”Ô†‚ğ–ß‚· */
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition > 0) {
				/* ’Zk”Ô†‚ğƒeƒ“ƒL[‚Å“ü—Í’† */
				NackBuzzer();
			}
			else {
				SpeedBackOperation();
			}
			break;
		case CLEAR:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition > 0) {/*’Zk”Ô†“ü—Í’† */
				/* ’Zk“ü—Íƒoƒbƒtƒ@‚Ìƒf[ƒ^‚ğ‚P•¶šƒNƒŠƒA */
				OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition--;
				OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer[OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition] = NULL;
			}
			else {
				NackBuzzer();
			}
			break;
		case NUMBER:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition >= SPEED_FIGURE_MAX) {	/* Œ…”ƒI[ƒo[(‚ ‚è“¾‚È‚¢) */
				NackBuzzer();
			}
			else {
				OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer[OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition++] = key;
				if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition >= SPEED_FIGURE_MAX) {
					speed_number = CMN_ASC_ToUnsignedInt(OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer,
														 OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition);
					if( CHK_UNI_OptionalSpeedDial() != 0 ){		/* ”CˆÓ’Zk‚Ì */
						if( speed_number > OPR_OPTIONAL_SPEED_MAX ){
							NackBuzzer();
							break;
						}
						else{
							OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = speed_number;
						}
						record_no = SetOptionalSpeedStatus( OPR_Buf.OntchSpdCtrl.SelectOptionalNumber );
						if( record_no != 0xff ){		/* ”CˆÓ’Zk”Ô‚ª‘¶İ‚·‚é */
							OPR_Buf.OntchSpdCtrl.SelectNumber = (UWORD)(SYS_ONETOUCH_MAX + record_no);
						}
						else{
							/** Œ”‚ªƒI[ƒo[‚µ‚Ä‚¢‚È‚¢‚©ƒ`ƒFƒbƒN */
							if( GetSpeedEntryCount() >= SYS_SPEED_DIAL_MAX ){
								NackBuzzer();
								OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
								return(OPR_END);
							}
							else{
								OPR_Buf.OntchSpdCtrl.SelectNumber = (UWORD)GetSpeedDialRecord();
								OPR_Buf.OntchSpdCtrl.SelectNumber += SYS_ONETOUCH_MAX;
							}
						}
					}else{										/* ’Êí‚Ì’Zk‚Ì */
						if ((speed_number < OPR_SPEED_DIAL_MIN) ||		/* •\¦‚Í‚P‚©‚ç */
						    (speed_number > SYS_SPEED_DIAL_MAX)){
							NackBuzzer();
						}
						else {
							OPR_Buf.OntchSpdCtrl.SelectNumber
							= (UWORD)((speed_number - OPR_SPEED_DIAL_MIN) + SYS_ONETOUCH_MAX);
						}
					}
					CMN_MemorySet(OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer, 4 , NULL);
					OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition = 0;
				}
			}
			break;
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* ƒAƒ“ƒY‚k‚¾‚¯‚ÍAƒAƒ“ƒY‚Æ“®ì‚ğ‡‚í‚¹‚Ü‚· by K.Watanabe 1997/11/28 */
		case SINGLE:		/* ’PˆêƒIƒyƒŒ[ƒVƒ‡ƒ“ƒL[ */
			SingleKeyOperation(key);
			break;
#endif
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[’Zk”Ô†“ü—Í(”CˆÓ’Zk—p)]
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
	date		:[1997/04/01]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
UBYTE InputSpeedOptionalNumber(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	record_no;
	UWORD	option_number;

	while (1) {
		SpeedSelectOptionalDisplay();
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case KEY_TIME_UP:
		case STOP:
			return (OPR_END);
		case ENTER:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition <= 0) {
				NackBuzzer();
			}
			else{
				option_number = CMN_ASC_ToUnsignedInt(OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer,
													  OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition);
				if( option_number > OPR_OPTIONAL_SPEED_MAX ){
					NackBuzzer();
				}
				else{
					OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = option_number;
				}
				CMN_MemorySet(OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer, 4 , NULL);
				OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition = 0;
				return (OK);
			}
			break;
		case FUNCTION:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition > 0) {
				/* ’Zk”Ô†‚ğƒeƒ“ƒL[‚Å“ü—Í’† */
				NackBuzzer();
			}
			else {
				OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = 0;
				return (OPR_CONTINUE);
			}
			break;
		case LEFT_ARROW:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition > 0) {
				/* ’Zk”Ô†‚ğƒeƒ“ƒL[‚Å“ü—Í’† */
				NackBuzzer();
			}
			else {
				OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = 999;
				return (OPR_CONTINUE);
			}
			break;
		case CLEAR:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition > 0) {/*’Zk”Ô†“ü—Í’† */
				/* ’Zk“ü—Íƒoƒbƒtƒ@‚Ìƒf[ƒ^‚ğ‚P•¶šƒNƒŠƒA */
				OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition--;
				OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer[OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition] = NULL;
			}
			else {
				NackBuzzer();
			}
			break;
		case NUMBER:
			if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition >= SPEED_FIGURE_MAX) {	/* Œ…”ƒI[ƒo[(‚ ‚è“¾‚È‚¢) */
				NackBuzzer();
			}
			else {
				OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer[OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition++] = key;
				if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition >= SPEED_FIGURE_MAX) {
					option_number = CMN_ASC_ToUnsignedInt(OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer,
														  OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition);
					if( option_number > OPR_OPTIONAL_SPEED_MAX ){
						NackBuzzer();
						break;
					}
					else{
						OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = option_number;
					}
					record_no = SetOptionalSpeedStatus( OPR_Buf.OntchSpdCtrl.SelectOptionalNumber );
					/** ’Zkƒf[ƒ^‚É‘Î‰‚·‚éƒŒƒR[ƒh”Ô†‚ğƒZƒbƒg **/
					if( record_no != 0xff ){		/* ”CˆÓ’Zk‚ª‘¶İ‚·‚é */
						OPR_Buf.OntchSpdCtrl.SelectNumber = (UWORD)(SYS_ONETOUCH_MAX + record_no);
					}
					else{
						/** Œ”‚ªƒI[ƒo[‚µ‚Ä‚¢‚È‚¢‚©ƒ`ƒFƒbƒN */
						if( GetSpeedEntryCount() >= SYS_SPEED_DIAL_MAX ){
							NackBuzzer();
							OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
							return(OPR_END);
						}
						else{
							OPR_Buf.OntchSpdCtrl.SelectNumber = (UWORD)GetSpeedDialRecord();
							OPR_Buf.OntchSpdCtrl.SelectNumber += SYS_ONETOUCH_MAX;
						}
					}
					CMN_MemorySet(OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer, 4 , NULL);
					OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition = 0;
					return( OPR_CONTINUE );
				}
			}
			break;
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* ƒAƒ“ƒY‚k‚¾‚¯‚ÍAƒAƒ“ƒY‚Æ“®ì‚ğ‡‚í‚¹‚Ü‚· by K.Watanabe 1997/11/28 */
		case SINGLE:		/* ’PˆêƒIƒyƒŒ[ƒVƒ‡ƒ“ƒL[ */
			SingleKeyOperation(key);
			break;
#endif
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[’Zk”Ô†‚ğ‚·‚·‚ß‚é]
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
	date		:[1995/04/14]
	author		:[]Œû]
*************************************************************************/
void SpeedForwordOperation(void)
{
	/* ÅŒã‚Ü‚Å‚¢‚Á‚½‚ç–ß‚· */
	if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* ’Êí‚Ì’Zk‚Ì */
		if (OPR_Buf.OntchSpdCtrl.SelectNumber == SYS_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX - 1) {
			OPR_Buf.OntchSpdCtrl.SelectNumber = SYS_ONETOUCH_MAX;
		}
		else {
			OPR_Buf.OntchSpdCtrl.SelectNumber++;
		}
	}
	else{	/* ”CˆÓ’Zk‚Ì */
		if (OPR_Buf.OntchSpdCtrl.SelectOptionalNumber == OPR_OPTIONAL_SPEED_MAX ){
			OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = 0;
		}
		else {
			OPR_Buf.OntchSpdCtrl.SelectOptionalNumber++;
		}
	}
}

/*************************************************************************
	module		:[’Zk”Ô†‚ğ–ß‚·]
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
	date		:[1995/04/14]
	author		:[]Œû]
*************************************************************************/
void SpeedBackOperation(void)
{
	/* æ“ª‚Ü‚Å‚«‚½‚çÅŒã‚É‚·‚é(‰ñ‚é) */
	if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* ’Êí‚Ì’Zk‚Ì */
		if (OPR_Buf.OntchSpdCtrl.SelectNumber == SYS_ONETOUCH_MAX) {
			OPR_Buf.OntchSpdCtrl.SelectNumber = SYS_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX - 1;
		}
		else {
			OPR_Buf.OntchSpdCtrl.SelectNumber--;
		}
	}
	else{	/* ”CˆÓ’Zk‚Ì */
		if (OPR_Buf.OntchSpdCtrl.SelectOptionalNumber == 0 ) {
			OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = OPR_OPTIONAL_SPEED_MAX;
		}
		else {
			OPR_Buf.OntchSpdCtrl.SelectOptionalNumber--;
		}
	}
}

/*************************************************************************
	module		:[’ZkƒIƒyƒŒ[ƒVƒ‡ƒ“‰Šú‰»]
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
	date		:[1995/07/17]
	author		:[]Œû]
*************************************************************************/
void SpeedOperationInitial(void)
{
	/* ’Zk”Ô†•\¦—pƒoƒbƒtƒ@‚ğì¬(’Zk”Ô†‚Í‚Ü‚¾)*/
	CMN_MemorySet(OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer, 5, NULL);	/*‚Æ‚è‚ ‚¦‚¸ƒNƒŠƒA‚µ‚Ä‚¨‚­*/
	OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer[SPEED_FIGURE_MAX] = ':';

	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');		/* ã’i•\¦•¶š—ñ‚ğ‰Šú‰» */
	CMN_MemorySetNULL(FunctionDisplayBufferLow,  OPR_DISPLAY_MAX, ' ');		/* ‰º’i•\¦•¶š—ñ‚ğ‰Šú‰» */
	CMN_MemorySet(OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer, 4, NULL);	/* ’Zk”Ô†“ü—Í—pƒoƒbƒtƒ@‚ğ‰Šú‰» */
	OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition = 0;						/* ’Zk”Ô†“ü—ÍˆÊ’u‚ğ‰Šú‰» */
	OPR_Buf.OntchSpdCtrl.SelectNumber = SYS_ONETOUCH_MAX;
	OPR_Buf.OntchSpdCtrl.SelectOptionalNumber = 0;
}

/*************************************************************************
	module		:[’Zkƒ_ƒCƒ„ƒ‹‘I‘ğ•\¦]
	function	:[’Zkƒ_ƒCƒ„ƒ‹‚Ì‘I‘ğ•\¦‚ğs‚¤B]
	return		:[‚È‚µ]
	common		:[
		OPR_Buf:
	]
	condition	:[]
	comment		:[’Zk”Ô†‚Í‚P‚©‚ç•\¦‚·‚é]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/20]
	author		:[]Œû]
*************************************************************************/
void SpeedSelectDisplay(void)
{
	/* ã’iuSelect Speed Dial   v*/
	/* ‰º’iu001:No Stored       vu001:1234456789      vu12                 v*/

	UBYTE	speed_number;

#if defined (KEISATSU)		/* Œx@FAX Added by SMuratec K.W.Q 2005/06/17 */
	UBYTE	kei_pos;
#endif		/* End of (defined (KEISATSU)) */

	CMN_StringCopy(FunctionDisplayBufferHigh,D2W_InputSpeedDialNumber);		/*"Àİ¼­¸ ÊŞİºŞ³ ¦ ÄŞ³¿Ş"*/

	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	/** ’Êí“ü—Í’† */
	if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition == 0) {
		/* ’j•\¦‚Í001‚©‚çn‚ß‚é */
		if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* ’Êí‚Ì’Zk */
			speed_number = (UBYTE)(OPR_Buf.OntchSpdCtrl.SelectNumber - SYS_ONETOUCH_MAX);
			CMN_UnsignedIntToASC(OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer,
								 speed_number + OPR_SPEED_DIAL_MIN,
								 SPEED_FIGURE_MAX,
								 '0');
		}
		else{			/* ”CˆÓ’Zk‚Ì */
			speed_number = SetOptionalSpeedStatus( OPR_Buf.OntchSpdCtrl.SelectOptionalNumber );
			CMN_UnsignedIntToASC(OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer,
								 OPR_Buf.OntchSpdCtrl.SelectOptionalNumber,
								 SPEED_FIGURE_MAX,
								 '0');
		}
		OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer[SPEED_FIGURE_MAX] = ':';
		CMN_StringCopy(FunctionDisplayBufferLow, OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer);
		/* ’Zkƒ_ƒCƒAƒ‹İ’èó‹µ‚ğ’²‚×‚é */
		if ((CheckSpeedStoreStatus(speed_number) == OK) && (speed_number != 0xFF)) {	/* ƒZƒbƒgÏ‚İ */
			/** ƒ_ƒCƒAƒ‹”Ô†‚ğæ‚èo‚µAASCII‚É‚È‚¨‚µ‚Ä•\¦ƒoƒbƒtƒ@‚ÉƒRƒs[*/

#if defined (KEISATSU)		/* Œx@FAX Added by SMuratec K.W.Q 2005/06/17 */
 /* Œx@İ’è•\¦ */
		 	kei_pos = SPEED_FIGURE_MAX + 1;
			if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_KEIDEN){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "¹", 1);
				kei_pos++;
			}
			else if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_KANYU){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "¶", 1);
				kei_pos++;
			}

			if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_ISSEI){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "²", 1);
				kei_pos++;
			}
			else if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_KOBETSU){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "º", 1);
				kei_pos++;
			}

			if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_SCRAMBLE_ON){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "S", 1);
				kei_pos++;
			}
			else if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "N", 1);
				kei_pos++;
			}

			if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_KYOTSU){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "·", 1);
				kei_pos++;
			}
			else if (SYB_SpeedDial[speed_number].Keisatsu & SYS_KEISATSU_SENYO){
				CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "¾", 1);
				kei_pos++;
			}

			CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferLow[kei_pos],
									&SYB_SpeedDial[speed_number].Dial[0],
									(UBYTE)(OPR_DISPLAY_MAX - kei_pos));
#else
			CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferLow[SPEED_FIGURE_MAX + 1],
									&SYB_SpeedDial[speed_number].Dial[0],
									(UBYTE)(OPR_DISPLAY_MAX - SPEED_FIGURE_MAX - 1));
#endif 		/* End of (defined (KEISATSU)) */

		}
		else { /* ƒZƒbƒg‚³‚ê‚Ä‚¢‚È‚¢ */
			CMN_StringCopy(&FunctionDisplayBufferLow[SPEED_FIGURE_MAX + 1], D2W_NoNumberStored);
		}
	}
	else {
		CMN_StringCopy(&FunctionDisplayBufferLow[0], OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer);
	}

	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	ClearDisplayLow();
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P 2004/07/14 for prefix *//* by K.Watanabe 2004/11/12 */
	ChangeDisplayBuffer(FunctionDisplayBufferLow);
#endif
	DisplayStringLow(0, FunctionDisplayBufferLow);
}

/*************************************************************************
	module		:[’Zkƒ_ƒCƒ„ƒ‹‘I‘ğ•\¦(’Zk”Ô†“o˜^‰æ–Ê)]
	function	:[’Zkƒ_ƒCƒ„ƒ‹‚Ì‘I‘ğ•\¦‚ğs‚¤B]
	return		:[‚È‚µ]
	common		:[
		OPR_Buf:
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[97/04/01]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
void SpeedSelectOptionalDisplay(void)
{
	UBYTE	speed_number;
	UBYTE	entry_count;	/* Œ»İ’Zk“o˜^” */
	UWORD	option_number;	/* ”CˆÓ’Zk—p */

	if (CheckChildErrorDisplayReq() == TRUE) {
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay() == TRUE) {
		return;
	}

	CMN_StringCopy(FunctionDisplayBufferHigh,D2W_InputSpeedDialNumber);			/*"Àİ¼­¸ ÊŞİºŞ³ ¦ ÄŞ³¿Ş"*/

	CMN_StringCopy(FunctionDisplayBufferLow,D2W_SelectOptionalSpeedNumber);	/*"   /     (0-999):   "*/

	entry_count = GetSpeedEntryCount();						/* Œ»İ’Zk“o˜^” */
	CMN_UnsignedIntToASC_NULL(OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer,
							  entry_count,
							  SPEED_FIGURE_MAX,
							  '0');
	CMN_StringCopy(FunctionDisplayBufferLow, OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer);

	CMN_UnsignedIntToASC_NULL(OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer,	/* Å‘å’Zk“o˜^” */
							  SYS_SPEED_DIAL_MAX,
							  SPEED_FIGURE_MAX,
							  '0');
	CMN_StringCopy(&FunctionDisplayBufferLow[4], OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer);

	if (OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition == 0) {	/* ”’l“ü—Í’† */
		CMN_StringCopy(&FunctionDisplayBufferLow[17], OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer);
	}
	else{
		speed_number = (UBYTE)(OPR_Buf.OntchSpdCtrl.SelectNumber - SYS_ONETOUCH_MAX);
		option_number = GetRecordFromNumber(OPR_Buf.OntchSpdCtrl.SelectNumber - SYS_ONETOUCH_MAX);
		CMN_UnsignedIntToASC(OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer,
							 option_number,
							 SPEED_FIGURE_MAX,
							 '0');
		CMN_StringCopy(&FunctionDisplayBufferLow[17], OPR_Buf.OntchSpdCtrl.SpeedNumberInputBuffer);
	}

	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	ClearDisplayLow();
	DisplayStringLow(0, FunctionDisplayBufferLow);
	CharacterInput.LcdDisplayPosition = 18;
	CursorOn((UBYTE)(OPR_LCD_LOWER_ADD
					 + OPR_Buf.OntchSpdCtrl.SpeedNumberInputPosition
					 + CharacterInput.LcdDisplayPosition
					 - 1));
}

/*************************************************************************
	module		:[’Zk”Ô†‚É‘Î‰‚·‚é”­M—p’Zk”Ô†‚ğŒŸõ‚·‚é]
	function	:[
		1.
	]
	return		:[	0xFFFF    :	“o˜^ƒf[ƒ^–³‚µ
					0xFFFFˆÈŠO:	“o˜^—L‚è
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/31]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
UWORD GetRecordFromNumber(UWORD record)
{
	UBYTE count;
	UBYTE rcd_no;

	for (count = 0; count < SYS_SPEED_DIAL_MAX; count++) {
		rcd_no = SYB_OptionalSpeed[count].Record;
		if (record == rcd_no) {
			return(SYB_OptionalSpeed[count].Number);
		}
		else if (rcd_no == 0xFF) {
			break;
		}
	}
	return(0xFFFF);
}

/*************************************************************************
	module		:[”CˆÓ’Zk‚Ìƒ_ƒCƒ„ƒ‹ƒŒƒR[ƒhƒIƒtƒZƒbƒg‚ÌƒZƒbƒg]
	function	:[
	]
	return		:[
				  ]
	common		:[	SYS_SpeedDial[].Dial[]
	]
	condition	:[]
	comment		:[”CˆÓ’Zk”Ô†d—l]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1997/04/01]
	auther		:[ŒKŒ´”ü‹I]
*************************************************************************/
UBYTE SetOptionalSpeedStatus(UWORD optional_no)	/* ”­M—p”CˆÓ’Zk”Ô† */
{
	UBYTE count;
	UBYTE record_no;
	UWORD opt_no;

	record_no	= 0xFF;
	for (count = 0; count < SYS_SPEED_DIAL_MAX; count++) {
		opt_no = SYB_OptionalSpeed[count].Number;
		if (optional_no == opt_no) {
			record_no = SYB_OptionalSpeed[count].Record;
			break;
		}
		else if (opt_no == 0xFFFF) {
			break;
		}
	}
	return( record_no );
}

/*************************************************************************
	module		:[Œ»İ‚Ì’Zk“o˜^”‚Ìæ“¾]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[”CˆÓ’Zk”Ô†d—l]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[OPR]
	date		:[1997/04/01]
	auther		:[ŒKŒ´”ü‹I]
*************************************************************************/
UBYTE GetSpeedEntryCount(void)
{
	UBYTE	count;

	for (count = 0; count < SYS_SPEED_DIAL_MAX; count++) {
		if (SYB_OptionalSpeed[count].Number == 0xFFFF) {
			break;
		}
	}
	return(count);
}

/*************************************************************************
	module		:[ƒ_ƒCƒ„ƒ‹ƒf[ƒ^‚ğ“o˜^‚·‚é’Zkƒ_ƒCƒ„ƒ‹ƒŒƒR[ƒh‚ğŠl“¾‚·‚é]
	function	:[
		1.
	]
	return		:[’Zkƒ_ƒCƒ„ƒ‹‚ÌƒŒƒR[ƒh”Ô†]
	common		:[SYB_SpeedDial.Dial]
	condition	:[]
	comment		:[”CˆÓ’Zk”Ô†d—l]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/02]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
UBYTE GetSpeedDialRecord(void)
{
	UBYTE count;

	for (count = 0; count < SYS_SPEED_DIAL_MAX; count++) {
		/* ƒŠƒ‚[ƒgf’f‚Å‚ÍAƒ_ƒCƒ„ƒ‹”Ô†Á‹‚Å 0xF0‚ğ‘‚­‚Ì‚ÅA”»’f‚ğ•ÏX‚µ‚Ü‚· 1998/04/01 by K.Watanabe */
/*		if (SYB_SpeedDial[count].Dial[0] == 0xFF) {*/
		if ((SYB_SpeedDial[count].Dial[0] & 0xF0) == 0xF0) {
			return(count);
		}
	}
	return(count);
}

/*************************************************************************
	module		:[’Zk”Ô†ŠÇ—ƒe[ƒuƒ‹‚Ö‚Ì“o˜^‚ğs‚¤]
	function	:[
		1.
	]
	return		:[‚È‚µ]
	common		:[
		SYS_OptionalSpeed.Number
		SYS_OptionalSpeed.Record
		OPR_Buf.OntchSpdCtrl.SelectOptionalNumber
		OPR_Buf.OntchSpdCtrl.SelectNumber
	]
	condition	:[]
	comment		:[”CˆÓ’Zk”Ô†d—l]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/02]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
void SetSpeedControlTable(void)
{
	UBYTE input_pos;
	UBYTE move_point;

	for (input_pos = 0; input_pos < SYS_SPEED_DIAL_MAX; input_pos++) {
		if (OPR_Buf.OntchSpdCtrl.SelectOptionalNumber < SYB_OptionalSpeed[input_pos].Number) {
			for (move_point = (UBYTE)(SYS_SPEED_DIAL_MAX - 1); move_point >= 0; move_point--) {
				if (SYB_OptionalSpeed[move_point].Number != 0xFFFF) {
					if (move_point < (UBYTE)(SYS_SPEED_DIAL_MAX - 1)) {
						SYB_OptionalSpeed[move_point + 1].Number = SYB_OptionalSpeed[move_point].Number;
						SYB_OptionalSpeed[move_point + 1].Record = SYB_OptionalSpeed[move_point].Record;
					}
				}
				if (move_point == input_pos) {
					SYB_OptionalSpeed[move_point].Number = OPR_Buf.OntchSpdCtrl.SelectOptionalNumber;
					SYB_OptionalSpeed[move_point].Record = 
								(UBYTE)(OPR_Buf.OntchSpdCtrl.SelectNumber - SYS_ONETOUCH_MAX);
					return;
				}
			}
		}
	}
}

/*************************************************************************
	module		:[’Zk”Ô†ŠÇ—ƒe[ƒuƒ‹‚©‚ç‚Ìíœ‚ğs‚¤]
	function	:[
		1.
	]
	return		:[–³‚µ]
	common		:[
		SYS_OptionalSpeed.Number
		SYS_OptionalSpeed.Record
		OPR_Buf.OntchSpdCtrl.SelectOptionalNumber
	]
	condition	:[]
	comment		:[”CˆÓ’Zk”Ô†d—l]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/01]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
void DeleteSpeedControlTable(void)
{
	UBYTE serach;
	UBYTE move_point;

	for (serach = 0; serach < SYS_SPEED_DIAL_MAX; serach++) {
		if (SYB_OptionalSpeed[serach].Number == OPR_Buf.OntchSpdCtrl.SelectOptionalNumber) {
			for (move_point = serach; move_point < SYS_SPEED_DIAL_MAX; move_point++) {
				if (move_point == (UBYTE)(SYS_SPEED_DIAL_MAX - 1)) {
					SYB_OptionalSpeed[move_point].Number = 0xFFFF;
					SYB_OptionalSpeed[move_point].Record = 0xFF;
					return;
				}
				SYB_OptionalSpeed[move_point].Number = SYB_OptionalSpeed[move_point + 1].Number;
				SYB_OptionalSpeed[move_point].Record = SYB_OptionalSpeed[move_point + 1].Record;
				if (SYB_OptionalSpeed[move_point].Number == 0xFFFF) {
					return;
				}
			}
		}
	}
}

/*************************************************************************
	module		:[’Zkƒ_ƒCƒAƒ‹“o˜^ó‘Ô‚ğ“¾‚é]
	function	:[
		1.w’è‚³‚ê‚½’Zk”Ô†‚Ì“o˜^ó‘Ô‚ğ“¾‚é
		2.ˆø”‚Å’Zk”Ô†‚ğ“¾‚é
	]
	return		:[
		NG:–¢“o˜^
		OK:“o˜^Ï‚İ
	]
	common		:[SYB_SpeedDial]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/17]
	author		:[]Œû]
*************************************************************************/
UBYTE CheckSpeedStoreStatus(UBYTE speed)
{
	if ((SYB_SpeedDial[speed].Dial[0] & 0xF0) == 0xF0) {
		return (NG);
	}
	return (OK);
}
