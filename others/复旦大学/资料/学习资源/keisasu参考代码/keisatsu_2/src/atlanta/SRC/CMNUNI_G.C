/*	By Y.Suzuki 1996/10/21	*/
/*	Original File jun\usr2:\src\kobe\anzu\src\cmnuni_g.h	*/
/************************************************
 * CMNUNI_G.C
 * ‹@ŽíŒÅ—LƒXƒCƒbƒ`G‚ÌÝ’èó‘Ô‚ðŠl“¾‚·‚éŠÖ”
 * 1996/04/11 Eguchi
 ************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\unisw_g.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\ext_v\bkupram.h"

/*************************************************************************
	module		:[–³‰¹ŒŸo–³Œø/—LŒø‚ÌŠl“¾]
	function	:[
		1.
	]
	return		:[0    :–³Œø
				  0ˆÈŠO:—LŒø
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/11]
	author		:[‹gìON]
*************************************************************************/
UBYTE CHK_UNI_SilentDetectAvailable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G0] & TAD_SILENT_DETECT_AVAILABLE));
}

/*************************************************************************
	module		:[‚s‚d‚k‚QƒIƒtƒtƒbƒNŒã‚ÌƒXƒ^[ƒgƒL[‚É‚æ‚éŽè“®‘—MEŽè“®ŽóM–³Œø/—LŒø‚ÌŠl“¾]
	function	:[
		1.
	]
	return		:[0    :–³Œø
				  0ˆÈŠO:—LŒø
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(“ú—§ƒ}ƒCƒRƒ“)]
	keyword		:[CMN]
	date		:[1997/07/09]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
UBYTE CHK_UNI_TEL2_AvailableStartKey(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G0] & TEL2_AVAILABLE_STARTKEY));
}

/*************************************************************************
	module		:[‚s‚d‚k‚Q‚ð‚s‚d‚k‚P‚Æ“¯‚¶“®ì‚É‚·‚é/‚µ‚È‚¢‚ÌŠl“¾]
	function	:[
		1.
	]
	return		:[0    :–³Œø
				  0ˆÈŠO:—LŒø
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/09/25]
	author		:[‹k³Ž÷]
*************************************************************************/
UBYTE CHK_UNI_TEL2_TEL1Action(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G0] & TEL2_TEL1ACTION));
}

#if ( PRO_NCU_TYPE == ANZU_GBR_TYPE )	/*	#if defined(GBR) || defined(AUS) || defined(SGP)	1996/10/16 By N.Sakamoto */
/*************************************************************************
	module		:[ HOOK KEY‚Å‰ñü‚ð•â‘«‚·‚éÛ‚È‚Ç‚É24V‚ðí‚ÉON(GBR\¿—p)]
	function	:[
		1.
	]
	return		:[0    :–³Œø
				  0ˆÈŠO:—LŒø
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/07/05]
	author		:[â–{’¼Žj]
*************************************************************************/
UBYTE CHK_UNI_OnHook24V_Available(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G0] & ON_HOOK_TEL_24V_ON));
}
#endif


/* #if (PRO_LINENUMBER == TWICE_LINE) 1998/06/09 H.Yoshikawa *//* ‹^Ž—‚Q‰ñüŽd—l by T.Soneoka 1997/12/3 */
/*************************************************************************
	module		:[ƒIƒtƒtƒbƒNŽž‚Ìƒpƒlƒ‹ƒL[‚©‚ç‚Ìƒ_ƒCƒ„ƒ‹‘—o]
	function	:[
		1.
	]
	return		:[0    :ƒpƒlƒ‹‚©‚ç‚Ìƒ_ƒCƒ„ƒ‹‘—o•s‰Â‚É‚È‚è‚Ü‚·(‹^Ž—2‰ñüŽžA“d˜b’†‚É‚¨‚¯‚éA‘¼‚Ì‰ñü‚Å‚ÌŒðM‚Å‚«‚é)
				  0ˆÈŠO:ƒpƒlƒ‹‚©‚ç‚Ìƒ_ƒCƒ„ƒ‹‘—o‰Â‚É‚È‚è‚Ü‚·(‹^Ž—2‰ñüŽžA“d˜b’†‚É‚¨‚¯‚éA‘¼‚Ì‰ñü‚Å‚ÌŒðM‚Å‚«‚È‚¢j
	]
	common		:[]
	condition	:[POPLAR_H ‹^Ž—‚Q‰ñü‚Ì‚Ý]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/12/3]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
UBYTE CHK_UNI_TelOpeDialTx(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G0] & TEL_OPE_DIAL_TX));
}
/* #endif */

/*************************************************************************
	module		:[—¯Žç^‚e‚`‚w‘Ò‹@Žž‚É”é˜b‹@”\‚ð—LŒø‚É‚·‚é]
	function	:[
		1.
	]
	return		:[0    :–³Œø
				  0ˆÈŠO:—LŒø
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/03/31]
	author		:[ŽRŒû]
*************************************************************************/
UBYTE CHK_UNI_SecretTelAnsFax(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G0] & SECRET_TEL_OPE_ANS_FAX));
}


/*************************************************************************
	module		:[]
	function	:[
		1.
	]
	return		:[0    :–³Œø
				  0ˆÈŠO:—LŒø
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/07/05]
	author		:[â–{’¼Žj]
*************************************************************************/
UBYTE CHK_UNI_FlashKeyOnOffTime(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G1]));
}

/*************************************************************************
	module		:[–³–Â“®’…M‘Ò‹@‚ÌŽž‚ÉA‚s‚d‚k‚Q‚Ì‹¤–Â‚è–hŽ~‚Ìˆ×‚É‚Q‚S‚u‚ð§Œä‚·‚é^‚µ‚È‚¢‚ÌŠl“¾]
	function	:[
		1.–³–Â“®’…MŽž‚Ì‘Ò‹@ó‘Ô‚Å‚s‚d‚k‚Q‚ÌƒŠƒŒ[‚ð‰ñü‚©‚çØ‚è—£‚·ˆ—‚à‚·‚éB
	]
	return		:[0    :‚µ‚È‚¢
				  0ˆÈŠO:‚·‚é
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(“ú—§ƒ}ƒCƒRƒ“)]
	keyword		:[CMN]
	date		:[1996/05/15]
	author		:[‹gìON]
*************************************************************************/
UBYTE CHK_UNI_NoRingTel2Detachable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G4] & NORING_TEL2_DETACHABLE));
}

/*************************************************************************
	module		:[‚c‚r‚d‚ÌŒŸo‚É‚æ‚è‹[Ž—ƒxƒ‹‚ð’âŽ~‚·‚é‚©‚Ç‚¤‚©‚ÌŠl“¾]
	function	:[
		1.
	]
	return		:[0    :–³Œøi’âŽ~‚µ‚È‚¢j
				  0ˆÈŠO:—LŒøi’âŽ~‚·‚éj
	]
	common		:[]
	condition	:[]
	comment		:[
		ƒ_ƒCƒ„ƒ‹ƒCƒ“‘Ò‹@‚ÆTEL/FAX‘Ò‹@
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(“ú—§ƒ}ƒCƒRƒ“)]
	keyword		:[CMN]
	date		:[1994/07/25]
	author		:[•½‰ª“O]
*************************************************************************/
UBYTE CHK_UNI_DetectDSE_Available(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G5] & DETECT_DSE_AVAILABLE));

}

/*************************************************************************
	module		:[TEL/FAX‘Ò‹@‚Ì‹[Ž—ƒxƒ‹’âŽ~ðŒ‚ÌŠl“¾]
	function	:[
		1.
	]
	return		:[0    :‹É”½
				  0ˆÈŠO:u’f
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(“ú—§ƒ}ƒCƒRƒ“)]
	keyword		:[CMN]
	date		:[1994/10/11]
	author		:[•½‰ª“O]
*************************************************************************/
UBYTE CHK_UNI_GenerateRingStopCond(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G5] & RING_STOP_CONDITION));
}

/*************************************************************************
	module		:[DSE‚Ì”½“]‚ðŒŸo‚·‚éŽüŠú‚ÌŠl“¾]
	function	:[
		1.
	]
	return		:[0x00  :  3ms
				  0x20  :  5ms
				  0x40  : 10ms
				  0x60  : 15ms
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(“ú—§ƒ}ƒCƒRƒ“)]
	keyword		:[CMN]
	date		:[1994/10/11]
	author		:[•½‰ª“O]
*************************************************************************/
UBYTE CHK_UNI_DSE_DetectCycle(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G5] & (DSE_CYCLE_L | DSE_CYCLE_H)));
}

/*************************************************************************
	module		:[ƒ_ƒCƒ„ƒ‹EƒCƒ“’…MŒã‚n‚e‚e@‚g‚n‚n‚jŒŸo‚Å‚b‚l‚kƒŠƒŒ[‚ð“|‚·]
	function	:[
		1.
	]
	return		:[0    :“|‚·
				  0ˆÈŠO:“|‚³‚È‚¢
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(“ú—§ƒ}ƒCƒRƒ“)]
	keyword		:[CMN]
	date		:[1994/07/19]
	author		:[â–{’¼Žj]
*************************************************************************/
UBYTE CHK_UNI_DialInCMLOnAfterOffHook(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G6] & DIALIN_CML_ON_AFTER_OFF_HOOK ));
}

/*************************************************************************
	module		:[ƒ_ƒCƒ„ƒ‹ƒCƒ“‚ÅDTMFŒŸoŒã“àüŽw’èŠ®—¹M†(CML OFF)‚Ü‚Å‚ÌŽžŠÔ‚ÌŠl“¾]
	function	:[
		1.
	]
	return		:[40 :400ms
				  70 :700m•b
				  100:1000m•b
				  130:1300m•b
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(“ú—§ƒ}ƒCƒRƒ“)]
	keyword		:[CMN]
	date		:[1994/03/11]
	author		:[‹gìON]
*************************************************************************/
UBYTE CHK_UNI_DialinPBX_RxSignalTime(void)
{
	return((UBYTE)(((SYB_MachineUniqSwitch[UNIQ_SW_G6] & ( DIALIN_PBX_RX_SIGNAL_TIME1 | DIALIN_PBX_RX_SIGNAL_TIME2 )) >> 6) * 30 + 40));
}


#if (PRO_LINENUMBER == TWICE_LINE)/* V851 By Y.Suzuki 2002/09/19 */
/*************************************************************************
	module		:[CIŒŸoŽžŠÔ‚ð10•b‚©‚ç•ÏX‚·‚éB]
	function	:[
		1.G6-0 1 7•b  0 5•b
		  G6-1 0      1
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[]
	author		:[]
*************************************************************************/
UBYTE CHK_UNI_CHG_CI_DetectTime(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G6] & 0x03));
}
#endif


/*************************************************************************
	module		:[—¯Žç^‚e‚`‚w‘Ò‹@Žž‚Ì‚o‚aM†ŒŸoŒ…”]
	function	:[
		1.
	]
	return		:[‚O`‚P‚TF‚O‚ÌŽž‚ÍŒŸo–³Œø
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/11/13]
	author		:[ŽRŒû“NŽ¡]
*************************************************************************/
UBYTE CHK_UNI_AnsFaxDTMFDetect(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G7] & 0x0F));
}

#if (PRO_REMOTE_RX == ENABLE)	/* 1998/01/24  By T.Yamaguchi */
/*************************************************************************
	module		:[ƒŠƒ‚[ƒgŽóMŽž‚Ì‚c‚oM†ŒŸoŽžŒŸo”Ô†ˆÈã‚ÅƒŠƒ‚[ƒgŽóM‚·‚é]
	function	:[
		1.
	]
	return		:[‚OF–³ŒøA‚PF—LŒø
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/11/13]
	author		:[ŽRŒû“NŽ¡]
*************************************************************************/
UBYTE CHK_UNI_DP_DetectMore(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G8] & DP_DETECT_MORE));
}

/*************************************************************************
	module		:[ƒŠƒ‚[ƒgŽóMŽž‚Ì‚c‚oM†ŒŸo”Ô†Šl“¾]
	function	:[
		1.
	]
	return		:[‚O`‚P‚TF‰Šú’l‚T
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/11/13]
	author		:[ŽRŒû“NŽ¡]
*************************************************************************/
UBYTE CHK_UNI_DP_DetectNumber(void)
{
	return((UBYTE)((SYB_MachineUniqSwitch[UNIQ_SW_G8] & 0xF0) >> 4));
}

/*************************************************************************
	module		:[ƒŠƒ‚[ƒgŽóMŽž‚Ì‚o‚aM†‚RŒ…–ÚŒŸo”Ô†Šl“¾]
	function	:[
		1.
	]
	return		:[0,*(0xb),#(0xc)F‰Šú’l@‚Oi–³Œø)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/11/13]
	author		:[ŽRŒû“NŽ¡]
*************************************************************************/
UBYTE CHK_UNI_DTMF_ThirdNumber(void)
{
	switch(SYB_MachineUniqSwitch[UNIQ_SW_G9] & DTMF_THIRD_NUMBER) {
	case 0:
		return(0);		/* ‚QŒ…‚Ì‚ÝŒŸo */
	case 1:
	case 3:
		return(0xB);	/* ‚RŒ…–Ú‚ÌŒŸo”Ô†– */
	case 2:
		return(0xC);	/* ‚RŒ…–Ú‚ÌŒŸo”Ô†” */
	}
}

/*************************************************************************
	module		:[ƒŠƒ‚[ƒgŽóMŽž‚Ì‚o‚aM†ŠÔ‚ÌŽžŠÔŠl“¾]
	function	:[
		1.
	]
	return		:[‚O`‚P‚TF•b’PˆÊ@‰Šú’l‚R•b
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/11/13]
	author		:[ŽRŒû“NŽ¡]
*************************************************************************/
UBYTE CHK_UNI_Between_DTMFandDTMF(void)
{
	return((UBYTE)((SYB_MachineUniqSwitch[UNIQ_SW_G9] & 0xF0) >> 4));
}
#endif	/* (PRO_REMOTE_RX == ENABLE) */

#if (PRO_CSDR_ITEM == ENABLE)
/*************************************************************************
	module		:[’…Mƒxƒ‹‰ñ”Šg’£]
	function	:[
		1.
	]
	return		:[
				‚O    FŠg’£‚È‚µi‚P`‚P‚Oj
				‚OˆÈŠOFŠg’£—L‚èi‚P‚©‚ç‚P‚Tj
	]
	common		:[]
	condition	:[]
	comment		:[
			yCSDR-No.86z’…Mƒxƒ‹‰ñ”‚ð‚P‚©‚ç‚P‚T‰ñ‚ÉŠg’£iJPN Onlyj
	]
	machine		:[V53,H8/300]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_ExtendedCallCount(void){}]
	date		:[1998/12/15]
	author		:[–ØŒ³  C]
*************************************************************************/
UBYTE CHK_UNI_ExtendedCallCount(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_G3] & CSDR_EXTENDED_CALL_COUNT));
}
#endif

#if (PRO_BT_DET_WHILE_RBT == ENABLE) /* ‹^Ž—ƒxƒ‹–Â“®’†‚ÌBusyToneŒŸo 2001/10/03 M.Matsumoto *//* Add By O.Kimoto 2002/03/11 */
/*************************************************************************
	module		:[]
	function	:[
		1.
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2001/10/03]
	author		:[¼–{³K]
*************************************************************************/
UBYTE CHK_UNI_DetectBusyTone(void)
{
	if (SYB_MachineUniqSwitch[UNIQ_SW_G7] & DET_BT_WHILE_RBT) {
		return (1);
	}
	else {
		return (0);
	}

}
/*************************************************************************
	module		:[]
	function	:[ƒrƒW[ƒg[ƒ“ŒŸo‚ðRBT1‰ñ–Â“®‚ÌŒã‚É‚·‚é‚©‚Ç‚¤‚©]
	return		:[TRUE:‹[Ž—ƒxƒ‹–Â“®‘O, FALSE:‹[Ž—ƒxƒ‹1‰ñ–Â“®Œã]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2001/12/20]
	author		:[‘å“‡C]
*************************************************************************/
UBYTE CHK_UNI_DetectBusySameTime(void)
{
	if (SYB_MachineUniqSwitch[UNIQ_SW_G7] & DET_BT_SAME_TIME) {
		return (1);
	}
	else {
		return (0);
	}
}
#endif

#if (PRO_VOICE_ANSWER == ENABLE)/* ‹^Ž—ƒxƒ‹–Â“®’†‚ÌBusyToneŒŸo By O.Kimoto 2003/12/01 */
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGEˆÈŠO‚Ìƒ‚ƒfƒ€ Modified by J.Kishida 2002/09/10 */
/*************************************************************************
	module		:[]
	function	:[
		1.
	]
	return		:[0:BusyToneŒŸo‚·‚é	1:BusyToneŒŸo‚µ‚È‚¢
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2001/10/03]
	author		:[¼–{³K]
*************************************************************************/
UBYTE CHK_UNI_IgnoreBusyTone(void)
{
	if (SYB_MachineUniqSwitch[UNIQ_SW_G7] & IGNORE_BT_ON_VOICE_MODE) {
		return (1);
	}
	else {
		return (0);
	}

}

 #endif
#endif

#if (PRO_BT_DET_WHILE_RBT == ENABLE) || (PRO_VOICE_ANSWER == ENABLE)
/*************************************************************************
	module		:[TEL/FAX,FAX/TELŽž‚ÌBusyToneŒŸoŽüŠú‰„’·]
	function	:[
		1.
	]
	return		:[‚O`‚P‚T
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2003/12/05]
	author		:[–ØŒ³C]
*************************************************************************/
UBYTE CHK_UNI_ExtendBusyToneDetectTime(void)
{
	return((UBYTE)((SYB_MachineUniqSwitch[UNIQ_SW_G2] & 0xF0) >> 4));
}
#endif

