/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/01/24
*        FILE NAME:  jbg_tpb.c
*       Task ID No:
*      DESCRIPTION:  ‚s‚o‚a(Typical Prediction (Bottom))
*                    T.82(JBIG)‚É‚æ‚é“TŒ^“I—\‘ªiƒ{ƒgƒ€j‚ğs‚¤ˆ×‚Ìƒtƒ@ƒCƒ‹ŒQ
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:
*        REFERENCE:
*************************************************************************/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\jbg_def.h"
#include "\src\cpu\sh7043_a\scd\define\jbg_pro.h"
#include "\src\cpu\sh7043_a\scd\ext_v\jbg_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\jbg_tbl.h"
#else
#include "\src\atlanta\scd\define\jbg_def.h"
#include "\src\atlanta\scd\define\jbg_pro.h"
#include "\src\atlanta\scd\ext_v\jbg_data.h"
#include "\src\atlanta\scd\ext_v\jbg_tbl.h"
#endif

/*************************************************************************
	module		:[
		T.82(JBIG)‚É‚æ‚é•„†‰»‚s‚o‚aƒƒCƒ“ˆ—
	]
	function	:[
		1.‚s‚o‚a‚n‚m‚ª‚P‚Ìê‡‚Ì‚İ‚Í‚s‚o‚a‚ğg—p‚·‚é
	]
	return		:[‚È‚µ]
	common		:[]
	condition	:[
		ƒCƒ[ƒWƒf[ƒ^‚ÌƒXƒ^[ƒgƒAƒhƒŒƒX‚ªŠm’è‚µ‚Ä‚¢‚é‚±‚Æ
		•„†ƒf[ƒ^‚ÌƒXƒ^[ƒgƒAƒhƒŒƒX‚ªŠm’è‚µ‚Ä‚¢‚é‚±‚Æ
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/27]
	author		:[¬’J³÷]
*************************************************************************/
void JBG_EncodeTPB(void)
{
	if (JBG_BIH.Options & JBG_BIT_TPBON) {	/** ‚s‚o‚a‚n‚m‚ª‚P‚Ìê‡‚Í‚r‚k‚m‚s‚o‚ğg—p‚·‚é */
		JBG_MakeLNTP();		/** ‚k‚m‚s‚o‚Ìì¬ */
		JBG_MakeSLNTP();	/** ‚r‚k‚m‚s‚o‚Ìì¬ */
	}
	else {
		JBG_LntpY = 1;	/** Zp‰‰Z‚ğg—p‚·‚é */
	}
}


/*************************************************************************
	module		:[
		T.82(JBIG)‚É‚æ‚é‚k‚m‚s‚o‚ğƒZƒbƒg‚·‚é
	]
	function	:[
		1.QÆƒ‰ƒCƒ“”Ô†‚ğƒZƒbƒg‚·‚é
		2.Œ»İƒ‰ƒCƒ“‚ÆQÆƒ‰ƒCƒ“‚Ì‚ª‚¼‚ğ”äŠr‚·‚é
		3.‚k‚m‚s‚o‚ğ‹Œ‚k‚m‚s‚o‚Æ‚µ‚Ä•Û‘¶‚·‚é
		4.V‚µ‚¢‚k‚m‚s‚o‚ğƒZƒbƒg‚·‚é
	]
	return		:[‚È‚µ]
	common		:[
	]
	condition	:[
		V‚µ‚¢ƒCƒ[ƒWƒf[ƒ^‚ª‚Pƒ‰ƒCƒ“•ªQÆƒ‰ƒCƒ“‚É“Ç‚İ‚Ü‚ê‚Ä‚¢‚é‚±‚Æ
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/27]
	author		:[¬’J³÷]
*************************************************************************/
void JBG_MakeLNTP(void)
{
	UDWORD loop;

	JBG_LntpY_1 = JBG_LntpY;	/** ‚k‚m‚s‚o‚ğ‹Œ‚k‚m‚s‚o‚Æ‚µ‚Ä•Û‘¶‚·‚é */
	JBG_LntpY = 0;	/** ‚O‚Å‰Šú‰» */
	for (loop = 0; loop < JBG_BIH.XD; loop++) {
		if (JBG_ReferenceLineBuffer[JBG_ReferenceLineY_Ptr][loop] != JBG_ReferenceLineBuffer[JBG_PreLineY_Ptr][loop]) {
			JBG_LntpY = 1;	/** •sˆê’v‚È‚Ì‚Å‚P‚ğƒZƒbƒg */
			break;
		}
	}
}


/*************************************************************************
	module		:[
		T.82(JBIG)‚É‚æ‚é‚r‚k‚m‚s‚o‚ğƒZƒbƒg‚·‚é
	]
	function	:[
		1.‚sD‚W‚Q‚ÌŠ©‚Ì’è‹`‚É]‚¤
	]
	return		:[‚È‚µ]
	common		:[
	]
	condition	:[
		V‚µ‚¢‚k‚m‚s‚o‚ªì¬‚³‚ê‚Ä‚¢‚é‚±‚Æ
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/27]
	author		:[¬’J³÷]
*************************************************************************/
void JBG_MakeSLNTP(void)
{
	JBG_SlntpY = (UBYTE)(1 - (JBG_LntpY ^ JBG_LntpY_1));	/** ‚r‚k‚m‚s‚o‚Ì’è‹` */
}


/*************************************************************************
	module		:[
		T.82(JBIG)‚É‚æ‚éƒfƒR[ƒh‚É‚k‚m‚s‚o‚ğŠl“¾‚·‚é
	]
	function	:[
		1.‚sD‚W‚Q‚ÌŠ©‚Ì’è‹`‚É]‚¤
	]
	return		:[‚È‚µ]
	common		:[
	]
	condition	:[
		ƒ‰ƒCƒ“æ“ª‰æ‘f‚ªƒfƒR[ƒh‚³‚êA‚r‚k‚m‚s‚o‚ªì¬‚³‚ê‚Ä‚¢‚é‚±‚Æ
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/02/03]
	author		:[¬’J³÷]
*************************************************************************/
void JBG_GetLNTP(void)
{
	JBG_LntpY = (UBYTE)(1 - (JBG_SlntpY ^ JBG_LntpY_1));	/** ‚k‚m‚s‚o‚Ì’è‹` */
}


/*************************************************************************
	module		:[
		T.82(JBIG)‚É‚æ‚é•œ†‰»‚s‚o‚aƒƒCƒ“ˆ—
	]
	function	:[
		1.‚s‚o‚a‚n‚m‚ª‚P‚Ìê‡‚Ì‚İ‚Í‚s‚o‚a‚ğg—p‚·‚é
	]
	return		:[‚È‚µ]
	common		:[]
	condition	:[
		AAD_InitDec();‚ªƒR[ƒ‹‚³‚ê‚Ä‚¢‚é‚±‚Æ
		ƒCƒ[ƒWƒf[ƒ^‚ÌƒXƒ^[ƒgƒAƒhƒŒƒX‚ªŠm’è‚µ‚Ä‚¢‚é‚±‚Æ
		•„†ƒf[ƒ^‚ÌƒXƒ^[ƒgƒAƒhƒŒƒX‚ªŠm’è‚µ‚Ä‚¢‚é‚±‚Æ
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/27]
	author		:[¬’J³÷]
*************************************************************************/
void JBG_DecodeTPB(void)
{
	if (JBG_BIH.Options & JBG_BIT_TPBON) {	/** ‚s‚o‚a‚n‚m‚ª‚P‚Ìê‡‚Í‚r‚k‚m‚s‚o‚ğg—p‚·‚é */
		JBG_GetSlntpCx();	/** ‚r‚k‚m‚s‚o‚Ì‚b‚wŠl“¾ */
		AAD_Decode();		/** è‡‚c‚d‚b‚n‚c‚d‚ğŒÄ‚Ô */
		JBG_SlntpY = JBG_Pix;	/** ‚r‚k‚m‚s‚o‚ğƒZƒbƒg */
		JBG_GetLNTP();			/** ‚k‚m‚s‚o‚ÌŠl“¾ */
	}
	else {
		JBG_LntpY = 1;
	}
}

