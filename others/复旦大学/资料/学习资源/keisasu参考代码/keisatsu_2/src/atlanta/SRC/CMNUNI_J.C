/*	By Y.Suzuki 1996/10/21	*/
/*	Original File jun\usr2:\src\kobe\anzu\src\cmnuni_j.h	*/
/****************************************************************
 * CMNUNI_J.C
 * ‹@ŽíŒÅ—LƒXƒCƒbƒ`J‚ÌÝ’èó‘Ô‚ð“¾‚éŠÖ”‚½‚¿
 * 1996/03/06 Eguchi
 ****************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\unisw_j.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\ext_v\bkupram.h"
/* #if (PRO_COPY_FAX_MODE == ENABLE) */	/* by K.Watanabe 1999/01/21 *//* Delete By O.Kimoto 1999/08/06 */
#include "\src\atlanta\define\sysdoc.h"
/* #endif */


#if (PRO_PRINT_TYPE == LED)
/*************************************************************************
	module		:[‘Ò‹@ó‘Ô‚Å‚Ì’è’…‰·“x’²®]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ƒ|ƒvƒ‰‚Ì‚ÝŽg—p]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/05/12]
	author		:[‹k³Ž÷]
*************************************************************************/
UBYTE CHK_UNI_WaitTempAdjust(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J0]));
}


#if (PRO_FANLOCK_DETECT_TIME == ENABLE)
/*************************************************************************
	module		:[‹@“àFANÛ¯¸ŒŸoŽžŠÔ‰„’·]
	function	:[
		1. 0:400ms(‰Šú’l) 1:200ms
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ƒ|ƒvƒ‰‚Ì‚ÝŽg—p]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[2002/09/26]
	author		:[Y.Suzuki]
*************************************************************************/
UBYTE CHK_UNI_FanLockDetectTime(void)/*V851  ‹@“àFANÛ¯¸‘Îô By Y.Suzuki 2002/09/26 */
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J0] & DETECT_TIME_400MS));
}
#endif


/*************************************************************************
	module		:[ƒ‚[ƒ^[‹N“®Žž‚Ì’è’…‰·“x’²®]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ƒ|ƒvƒ‰‚Ì‚ÝŽg—p]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/05/12]
	author		:[‹k³Ž÷]
*************************************************************************/
UBYTE CHK_UNI_MotorStartTempAdjust(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J1]));
}

/*************************************************************************
	module		:[ƒvƒŠƒ“ƒgó‘Ô‚Å‚Ì’è’…‰·“x’²®]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ƒ|ƒvƒ‰‚Ì‚ÝŽg—p]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/05/12]
	author		:[‹k³Ž÷]
*************************************************************************/
UBYTE CHK_UNI_PrintTempAdjust(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J2]));
}

/*************************************************************************
	module		:[ƒJƒZƒbƒgƒTƒCƒYŒŸo‚Ì’²®]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ƒ|ƒvƒ‰‚Ì‚ÝŽg—p]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/05/12]
	author		:[‹k³Ž÷]
*************************************************************************/
UBYTE CHK_UNI_CassetteSizeAdjust(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J3]));
}
#endif	/* #if (PRO_PRINT_TYPE == LED) */

#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
/*************************************************************************
	module		:[Class1“®ì’†AƒŠƒ‚[ƒgFAX‚©‚ç‚ÌŒÄ‚Ño‚µ‚ÉFAX‚Å‰ž“š—LŒø^‹‘”Û‚ÌŠl“¾]
	function	:[]
	return		:[
					0:FAX’…M‹‘”Û
					1:FAX’…M—LŒø
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/06/19]
	author		:[•Ÿˆä’mŽj]
*************************************************************************/
UBYTE CHK_UNI_RxRemoteFaxOnClass1Busy(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J4] & CLASS1_AND_FAX_ANSWER_ENABLE));
}

#endif /* (PRO_CL1_TELFAX_LAN == ENABLE)

/*************************************************************************
	module		:[Class1“®ì’†ACIƒ^ƒCƒ€ƒAƒbƒv‰ñ”‚ÌŠl“¾]
	function	:[
		1.
	]
	return		:[
		0`15
	]
	common		:[]
	condition	:[]
	comment		:[ ‚h‚b‚g‚n‚t‚æ‚èˆÚA ]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/06/19]
	author		:[•Ÿˆä’mŽj]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* Šg’£‚q‚n‚l‚©‚ç‚ÌŽQÆƒ‹[ƒ`ƒ“ S.Fukui Jun 19,1998 */
UBYTE	CHK_Cl1CiTimeupRingCntFlsRom(void)
#else
UBYTE	CHK_Class1CiTimeupRingCount(void)
#endif
{
	return ((UBYTE)((SYB_MachineUniqSwitch[UNIQ_SW_J4] & CLASS1_CI_TIMEUP_RING_COUNT) >> 4));
}

/*************************************************************************
	module		:[ƒ|ƒvƒ‰‚a‚Åƒ\[ƒgƒRƒs‚Ì‰Šú‚ð‚n‚m‚É‚·‚é]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[

	]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1999/2/15]
	author		:[—é–Øˆè“ñ]
*************************************************************************/
UBYTE CHK_UNI_SortCopyOn(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J5] & SORT_COPY_ON));
}

/*************************************************************************
	module		:[ƒƒ‚ƒŠ‘—M‚·‚éŽž‚ÉA‚P•”ƒRƒs[‚ðs‚¤]
	function	:[
		1.
	]
	return		:[]
	common		:[
		1.ŠÈˆÕ”ÅCopy&Fax
		2.ƒ[ƒ“ƒŠƒ“‚©‚ç‚ÌSAKAKI‚Ö‚Ì—v‹
	]
	condition	:[]
	comment		:[

	]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1999/02/17]
	author		:[‹gìON]
*************************************************************************/
UBYTE CHK_UNI_FaxAnd1Copy(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J5] & FAX_AND_1COPY));
}

/*************************************************************************
	module		:[‚s‚r‚h‚ð”»’f‚µA‚»‚Ì”Ô†‚É‚e‚`‚w‚ðÜ‚è•Ô‚·]
	function	:[
		1.
	]
	return		:[‚O		F‚n‚e‚e
				  ‚OˆÈŠO	F‚n‚m]
	common		:[]
	condition	:[]
	comment		:[“Á‚q‚n‚l—p(RDC-D83-002)		‰Šú’lF‚O]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[1999/04/14]
	author		:[•½”ö‰p“T]
*************************************************************************/
/* ˆÚA by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if (PRO_SPECIAL_REPLAY_TRANS == ENABLE)
UBYTE CHK_UNI_TSI_RelayTrans(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J5] & TSI_RELAY_TRANS));
}
 #endif
#endif

/*************************************************************************
	module		:[‘º“cˆÈŠO‚Ìƒ[ƒJ‚ÅÜ‚è•Ô‚µ]
	function	:[
		1.‚s‚r‚h‚ð”»’f‚µA‚»‚Ì”Ô†‚É‚e‚`‚w‚ðÜ‚è•Ô‚·Žž‚É‘º“cˆÈŠO‚Ìƒ[ƒJ‚ÅÜ‚è•Ô‚µ
	]
	return		:[‚O		F‚·‚é
				  ‚OˆÈŠO	F‚µ‚È‚¢]
	common		:[]
	condition	:[]
	comment		:[“Á‚q‚n‚l—p(RDC-D83-002)		‰Šú’lF‚O]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[1999/04/14]
	author		:[•½”ö‰p“T]
*************************************************************************/
/** #if (PRO_KEYPANEL == PANEL_HINOKI) **/	/**‘¼‚Ì‹@Ží‚à“Á‚q‚n‚l‘Î‰ž 1999.4.21 K.Kawata **/
 #if (PRO_SPECIAL_REPLAY_TRANS == ENABLE)
UBYTE CHK_UNI_TSI_MurataRelayTrans(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J5] & TSI_MURATA_RELAY_TRANS));
}
 #endif
/** #endif **/	/**‘¼‚Ì‹@Ží‚à“Á‚q‚n‚l‘Î‰ž 1999.4.21 K.Kawata **/
/*************************************************************************
	module		:[]
	function	:[
		1.
	]
	return		:[‚O		F‚·‚é
				  ‚OˆÈŠO	F‚µ‚È‚¢]
	common		:[]
	condition	:[]
	comment		:[	‰Šú’lF‚O]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[1999/06/14]
	author		:[K.Kawata]
*************************************************************************/
#if (PRO_CLASS1_EXT_FUNC == ENABLE)
UBYTE CHK_UNI_Class1_EXT_Function(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J5] & CLASS1_EXT_FUNCTION));
}
#endif
/*************************************************************************
	module		:[‰ñ“]ƒIƒvƒVƒ‡ƒ“c‰¡˜c‚Ý•â³‚ðs‚¤]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ƒXƒCƒbƒ`‚ðƒ}ƒXƒN‚µ‚Ä–ß‚è’l‚Æ‚·‚é‚æ‚¤‚É•ÏX T.Nose 1998/6/11
	]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/10/21]
	author		:[¬’J³Ž÷]
*************************************************************************/
UBYTE CHK_UNI_RotateAdjustDistortion(void)
{
	/* return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J6])); */
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J6] & ROT_ADJUST_DISTORTION));
}

/*************************************************************************
	module		:[‚u‚V‚R‚O‚ÅƒRƒs[‰æŽ¿‚Ì‰Šú’l‚ð‘I‘ð‰Â”\‚É‚·‚é]
	function	:[
		1.UNISW J6-0 ‚ð1‚É‚·‚é‚ÆJ6-7/6‚ÅƒRƒs[‰æŽ¿‚Ì‰Šú’l‚ð•ÏX‚Å‚«‚éB
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		•W€‚ÅJ6-7/6‚ð“ü‚ê‚é‚ÆŽæà‚É‰e‹¿‚·‚éBV730‚ÍAƒRƒs[ŽžƒRƒs[ƒL[‚ð
		2‰ñ‰Ÿ‚·B1“x–Ú‚ÌƒRƒs[ƒL[‰Ÿ‰º‚ÅƒRƒs[‰æŽ¿‚ª‰Šú‰»‚³‚ê‚éB
		‚±‚Ì“_‚ªŽæà‚É‰e‹¿‚·‚éB‘å•ª‚©‚çŽw“E—L‚è By Y.Suzuki 1999/11/29
		J6-0‚Å‚±‚Ì‹@”\‚ð‰B‚µ‚É‚·‚éB
	]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1999/11/29]
	author		:[—é–Øˆè“ñ]
*************************************************************************/
UBYTE CHK_UNI_SelectableCopyMode(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J6] & SELECTABLE_COPY_MODE ));
}

/*************************************************************************
	module		:[‰ñ“]ƒIƒvƒVƒ‡ƒ“—L‚è‚Åƒy[ƒW‡¬‚ðs‚¤]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/06/11]
	author		:[–ì£•qO]
*************************************************************************/
UBYTE CHK_UNI_RotatePageCompound(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J6] & ROT_PAGE_COMPOUND));
}

/*************************************************************************
	module		:[‚o‚bƒvƒŠƒ“ƒg‚e‚‚˜‘¤‚ÅƒCƒ“ƒ`^ƒ~ƒŠ•ÏŠ·‚ðs‚¤]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/11/11]
	author		:[‹k³Ž÷]
*************************************************************************/
UBYTE CHK_UNI_PcPrintInchMmConvert(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J6] & PC_PRINT_INCH_MM_CONVERT));
}

/*************************************************************************
	module		:[Žè·‚µ‚`‚T‚q‚ðƒnƒKƒL‚Ì§Œä‚ÅˆóŽš‚·‚éi‰•œ‚Í‚ª‚«‘Î‰žj]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/12/07]
	author		:[‹k³Ž÷]
*************************************************************************/
UBYTE CHK_UNI_PostCardFeedback(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J6] & POSTCARD_FEEDBACK));
}

#if (PRO_COPY_FAX_MODE == ENABLE)	/* by K.Watanabe 1999/01/20 */
/*************************************************************************
	module		:[ƒtƒ@ƒNƒX^ƒRƒs[“®ìŒã‚Ì‘Ò‹@‰æ–Ê‚ÌŠl“¾]
	function	:[
		1.
	]
	return		:[
		PRIMARY_FAX_READY	:ƒtƒ@ƒNƒXƒ‚[ƒh
		PRIMARY_COPY_READY	:ƒRƒs[ƒ‚[ƒh
		‚O					:‚»‚Ì‚Ü‚Ü
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/03/10]
	author		:[‘]ª‰ª‘ñE“n•ÓˆêÍ]
*************************************************************************/
UBYTE CHK_UNI_PrimaryReadyMode(void)
{
	switch (SYB_MachineUniqSwitch[UNIQ_SW_J6] & (UBYTE)(PRIMARY_FAX_READY | PRIMARY_COPY_READY)) {
	case PRIMARY_FAX_READY:
		return(PRIMARY_FAX_READY);
	case PRIMARY_COPY_READY:
		return(PRIMARY_COPY_READY);
	default:
		return(0);
	}
}

#endif	/* (PRO_COPY_FAX_MODE == ENABLE) *//* Add By O.Kimoto 1999/08/06 */

/* ‰º‹LŠÖ”‚ÍPOPLAR_H‚Å‚à“¯—l‚ÈŽd—l•ÏX—v‹‚ª—ˆ‚Ä‚¢‚Ü‚·‚Ì‚ÅA‹¤’Ê‚ÅŽg—p‚·‚é‚æ‚¤‚É‚µ‚Ü‚·B
** ‚æ‚Á‚ÄAPRO_COPY_FAX_MODE‚ÌðŒŽ®‚Ì”ÍˆÍ‚ðˆÚ“®‚³‚¹‚Ü‚µ‚½B
** by O.Kimoto 1999/08/06
*/
/*************************************************************************
	module		:[ƒRƒs[ƒ‚[ƒh‚Ì‰æŽ¿‚Ì‰Šú’lŠl“¾]
	function	:[
		1.ƒ†ƒj[ƒN‚r‚v‚ÉŠ„‚è“–‚Ä‚ç‚ê‚½ƒRƒs[ƒ‚[ƒh‚Ì‰æŽ¿‚Ì‰Šú’l‚ð•Ô‚µ‚Ü‚·
	]
	return		:[
		SYS_NORMAL	:•W€
		SYS_FINE	:‚‰æŽ¿
		SYS_SFINE	:’´‚‰æŽ¿iƒX[ƒp[ƒtƒ@ƒCƒ“j
		SYS_HFINE	:’´‚‰æŽ¿iƒnƒCƒp[ƒtƒ@ƒCƒ“j
		SYS_GRAY64	:ŽÊ^i‚U‚SŠK’²j
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1999/01/21]
	author		:[“n•ÓˆêÍ]
*************************************************************************/
UBYTE CHK_UNI_CopyPrimaryMode(void)
{
	UBYTE	ret;

	switch (SYB_MachineUniqSwitch[UNIQ_SW_J6] & PRIMARY_COPY_MODE_GRAY) {
	case PRIMARY_COPY_MODE_NORMAL:	/* •’Ê */
		ret = SYS_NORMAL;
		break;
	case PRIMARY_COPY_MODE_FINE:	/* ‚‰æŽ¿ */
		ret = SYS_FINE;
		break;
	case PRIMARY_COPY_MODE_GRAY:	/* ŽÊ^ */
		ret = SYS_GRAY64;
		break;
	case PRIMARY_COPY_MODE_SFINE:	/* ’´‚‰æŽ¿ */
	default:
		if (CHK_UNI_HyperFineON()) {	/* ’´‚‰æŽ¿‚ªƒnƒCƒp[ƒtƒ@ƒCƒ“‚ÌŽž */
			ret = SYS_HFINE;
		}
		else {							/* ’´‚‰æŽ¿‚ªƒX[ƒp[ƒtƒ@ƒCƒ“‚ÌŽž */
			ret = SYS_SFINE;
		}
		break;
	}

	return(ret);
}
/* #endif	*//* (PRO_COPY_FAX_MODE == ENABLE) *//* Delete By O.Kimoto 1999/08/06 */

/*************************************************************************
	module		:[‰ñ“]ƒIƒvƒVƒ‡ƒ“‰ñ“]‘O‚ÌŽå‘–¸ƒ}[ƒWƒ“‚Ì’²®]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/10/21]
	author		:[¬’J³Ž÷]
*************************************************************************/
UBYTE CHK_UNI_RotateHorizontalMargin(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J7]));
}

/*************************************************************************
	module		:[ƒXƒNƒ‰ƒ“ƒuƒ‹’†‚Ì’…M‚ðs‚¤‚©H]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/5/27]
	author		:[—é–Øˆè“ñ]
*************************************************************************/
UBYTE CHK_UNI_PriorityReceive(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J9] & SCRAMBLE_RESET));
}

/*************************************************************************
	module		:[ƒXƒNƒ‰ƒ“ƒuƒ‹Œ³Œ´e’~Ï’†‚ÌŒ´e’·ƒGƒ‰[‚µ‚È‚¢]
	function	:[
		1.‚`‚S‹Ð‚ÌŒ´e‚ð“Ç‚ÝŽæ‚è’†‚`‚S’·‚ð’´‚¦‚½ê‡AƒGƒ‰[‚É‚µ‚È‚¢B
		2.‚a‚SŒ´e‚Ìê‡‚±‚ÌƒXƒCƒbƒ`‚É‚æ‚ç‚¸AƒGƒ‰[‚É‚·‚éB
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/6/11]
	author		:[—é–Øˆè“ñ]
*************************************************************************/
UBYTE CHK_UNI_NoLengthError(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J9] & NO_LENGTH_ERROR));
}

/*************************************************************************
	module		:[Ü‚è•Ô‚µ“Á‚q‚n‚l‚ÅƒZƒ“ƒ^[‚Å‚àˆóŽš‚·‚é^‚µ‚È‚¢]
	function	:[
		1.
	]
	return		:[‚O		F‚µ‚È‚¢i‰Šú’lj
				  ‚OˆÈŠO	F‚·‚é
	common		:[]
	condition	:[]
	comment		:[“Á‚q‚n‚l—p(RDC200100059)		‰Šú’lF‚O]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[2001/02/22]
	author		:[•½”ö‰p“T]
*************************************************************************/
#if (PRO_SPECIAL_REPLAY_TRANS == ENABLE)
UBYTE CHK_UNI_TSI_RelayTxCenterPrint(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J5] & TSI_RELAY_TRANS_LOCAL_PRINT));
}
#endif

/*************************************************************************
	module		:[A5RŽóMŒ´e‚ðB5R‹L˜^Ž†‚ÉˆóŽš‚·‚éE‚µ‚È‚¢]
	function	:[
		1.
	]
	return		:[‚O		F‚µ‚È‚¢i‰Šú’lj
				  ‚OˆÈŠO	F‚·‚éi“ÁROMj
	common		:[]
	condition	:[]
	comment		:[“Á‚q‚n‚l—p(RDC)		‰Šú’lF‚O]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[2004/04/7]
	author		:[—é–Øˆè“ñ]
*************************************************************************/
#if defined(POPLAR_H) && defined(JP0)
UBYTE CHK_UNI_PrimaryPaperForB5R_Doc(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J5] & PRIMARY_PAPER_B5R));
}
#endif

/*************************************************************************
	module		:[SAKAKI2(F551)‚ÅOKIŽd—l‚É•ÏX‚·‚éE‚µ‚È‚¢]
	function	:[
		1.
	]
	return		:[‚O		F‚µ‚È‚¢i‰Šú’lj
				  ‚OˆÈŠO	F‚·‚é
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[2003/09/20]
	author		:[‹gìON]
*************************************************************************/
#if defined(SAKAKI)
UBYTE CHK_UNI_OCA_ForSAKAKI2(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J5] & OCA_FOR_SAKAKI2));
}
#endif

/*************************************************************************
	module		:[ƒtƒ@ƒ“§Œäƒ^ƒCƒ}[’l‚ÌŠl“¾]
	function	:[
		1.
	]
	return		:[0`255:0`255•ª]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2000/07/12]
	author		:[‹k³Ž÷]
*************************************************************************/
#if (defined(POPLAR_H) && defined(JP0)) /* V851 ‚e‚`‚m§Œä By H.Fujimura 2002/07/11 */
UBYTE CHK_UNI_FanTime(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_J8] & FAN_TIMER));
}
#endif

/*************************************************************************
	module		:[ƒvƒŠƒ“ƒ^[ƒtƒ@ƒ“’âŽ~—p‹@“à‰·“xŠÄŽ‹ƒ^ƒCƒ}[’l]
	function	:[]
	return		:[
		0`15(min)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH]
	language	:[C]
	keyword		:[CMN]
	date		:[2001/11/14]
	author		:[–ØŒ³C]
*************************************************************************/
#if (defined(POPLAR_H) && defined(JP0)) /* V851 ‚e‚`‚m§Œä By H.Fujimura 2002/07/11 */
UBYTE CHK_UNI_InternalTempIntervalTimer(void)
{
	if (!(SYB_MachineUniqSwitch[UNIQ_SW_J9] & CHECK_INTERNAL_TEMP_INTERVAL)) {
		return(1);
	}
	return((UBYTE)((SYB_MachineUniqSwitch[UNIQ_SW_J9] & CHECK_INTERNAL_TEMP_INTERVAL) >> 4));
}
#endif

